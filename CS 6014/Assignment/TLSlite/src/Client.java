import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.Mac;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.net.Socket;
import java.security.*;
import java.security.cert.CertificateException;
import java.security.cert.Certificate;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class Client {
    static byte[] serverEncrypt;
    static byte[] clientEncrypt;
    static byte[] serverMAC;
    static byte[] clientMAC;
    static byte[] serverIV;
    static byte[] clientIV;
    static byte[] clientNonce;
    public static Certificate clientCert;
    static PublicKey clientCaPublicKey;
    static BigInteger DHPrivateKeyClient;
    static BigInteger DHPublicKeyClient;
    static PrivateKey privateKeyFromFile;
    static BigInteger signedDHPublicKeyClient;

    static BigInteger sharedSecretKey;
    static Socket socketToServer;

    public Client() throws IOException, CertificateException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException {
        // initialize nonce
        clientNonce = new SecureRandom().generateSeed(32);
        // get signed CA client cert
        clientCert = Helpers.generateCertificate("CASignedClientCertificate.pem");
        clientCaPublicKey = clientCert.getPublicKey();

        // generate private key to get DH public key
        DHPrivateKeyClient = new BigInteger( new SecureRandom().generateSeed(32));
        DHPublicKeyClient = Helpers.getDHPublicKey(DHPrivateKeyClient);

        // now get signed DHPublicKeyClient
        privateKeyFromFile = Helpers.getKeyFromFile("clientPrivateKey.der");
        signedDHPublicKeyClient = Helpers.getSignedKey(privateKeyFromFile, DHPublicKeyClient);

        socketToServer = new Socket("127.0.0.1", 3333);
    }

    public void makeSecretKeys(byte[] nonce, BigInteger sharedSecretKey) throws NoSuchAlgorithmException, InvalidKeyException {
        Mac HMAC = Mac.getInstance("HmacSHA256");
        SecretKeySpec secretKeySpec = new SecretKeySpec(nonce, "HmacSHA256");
        HMAC.init(secretKeySpec);
        HMAC.update(sharedSecretKey.toByteArray());
        byte[] prk = HMAC.doFinal(sharedSecretKey.toByteArray());
        serverEncrypt = Helpers.hkdfExpand(prk, "server encrypt");
        clientEncrypt = Helpers.hkdfExpand(serverEncrypt, "client encrypt");
        serverMAC = Helpers.hkdfExpand(clientEncrypt, "server MAC");
        clientMAC = Helpers.hkdfExpand(serverMAC, "client MAC");
        serverIV = Helpers.hkdfExpand(clientMAC, "server IV");
        clientIV = Helpers.hkdfExpand(serverIV, "client IV");
    }

    public static void main(String[] args) throws IOException, CertificateException, ClassNotFoundException, NoSuchAlgorithmException, InvalidKeySpecException, SignatureException, InvalidKeyException, InvalidAlgorithmParameterException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
        System.out.println("initialize client");
        Client myClient = new Client();
        System.out.println("done initialize client");
        // CA stuff
        Certificate caCertificate = Helpers.generateCertificate("CAcertificate.pem");
        PublicKey caCertPublicKey = caCertificate.getPublicKey();
        System.out.println("making IO streams in client!: " + caCertPublicKey);

        // make input and output streams to use with socket to talk to server
        System.out.println("making IO streams in client!");
        ObjectOutputStream clientOutputStream = new ObjectOutputStream(myClient.socketToServer.getOutputStream());
        ObjectInputStream clientInputStream = new ObjectInputStream(myClient.socketToServer.getInputStream());

        // where we will store msg
        ByteArrayOutputStream messageLog = new ByteArrayOutputStream();
        System.out.println("done");




        /********************************************HANDSHAKE*********************************************/
        //send client hello
        clientOutputStream.flush();
        clientOutputStream.writeObject(myClient.clientNonce);
        messageLog.write(myClient.clientNonce);

        Certificate serverCert = (Certificate) clientInputStream.readObject();
        BigInteger DHPublicKeyServer = (BigInteger) clientInputStream.readObject();
        BigInteger signedDHPublicKeyServer = (BigInteger) clientInputStream.readObject();

        // verify server cert
        try {
            serverCert.verify(caCertPublicKey);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        } catch (InvalidKeyException e) {
            throw new RuntimeException(e);
        } catch (NoSuchProviderException e) {
            throw new RuntimeException(e);
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }

        // Add to message log after verification
        messageLog.write(serverCert.getEncoded());
        messageLog.write(DHPublicKeyServer.toByteArray());
        messageLog.write(signedDHPublicKeyServer.toByteArray());

        //Respond to server
        clientOutputStream.writeObject(myClient.clientCert);
        clientOutputStream.writeObject(myClient.DHPublicKeyClient);
        clientOutputStream.writeObject(myClient.signedDHPublicKeyClient);

        // Add to log
        messageLog.write(myClient.clientCert.getEncoded());
        messageLog.write(myClient.DHPublicKeyClient.toByteArray());
        messageLog.write(myClient.signedDHPublicKeyClient.toByteArray());

        myClient.sharedSecretKey = Helpers.getSharedSecretKey(DHPublicKeyServer, myClient.DHPrivateKeyClient);
        System.out.println("stored shared secret in client!");
        //make the other secret keys
        myClient.makeSecretKeys(myClient.clientNonce, myClient.sharedSecretKey);

        // compare history/mac
        byte[] macServer = (byte[]) clientInputStream.readObject();
        byte[] macClientToCompare = Helpers.getMessageToCompare(messageLog.toByteArray(), myClient.serverMAC);

        assert Arrays.equals(macServer, macClientToCompare);
        messageLog.write(macServer);
        byte[] clientSendBack = Helpers.getMessageToCompare(messageLog.toByteArray(), myClient.clientMAC);
        clientOutputStream.writeObject(clientSendBack);
        /************************************* Handshake Complete******************************************/


        /********************************************First Decrypt******************************************/
        byte[] encryptedMsg = (byte[]) clientInputStream.readObject();
        System.out.println("the encrypted message is: " + Arrays.toString(encryptedMsg));

        //decrypt message
        byte[] decrypted = Helpers.decrypt(encryptedMsg, myClient.serverEncrypt, myClient.serverIV, myClient.serverMAC);
        // length -32 to make a 256 bit mac
        byte[] noMac = Arrays.copyOf(decrypted, decrypted.length - 32);

        //Check if mac matches
        if (Helpers.doMacsMatch(decrypted, myClient.serverMAC)) {
            System.out.println("First decrypted message: " +  new String(noMac));
        } else {
            throw new RuntimeException("macs dont match");
        }




        /********************************************Second Decrypt******************************************/
        // Send back ack
        byte[] encryptAck = Helpers.encrypt("ack-one".getBytes(), myClient.clientEncrypt, myClient.clientIV, myClient.clientMAC);
        clientOutputStream.writeObject(encryptAck);

        byte[] encryptedMsg2 = (byte[]) clientInputStream.readObject(); //get next encrypted message from server
        System.out.println("the second encrypted message is: " + Arrays.toString(encryptedMsg2));

        //decrypt message
        byte[] decrypted2 = Helpers.decrypt(encryptedMsg2, myClient.serverEncrypt, myClient.serverIV, myClient.serverMAC);
        byte[] noMac2 = Arrays.copyOf(decrypted2, decrypted2.length - 32);

        // Mac Second check
        if (Helpers.doMacsMatch(decrypted2, myClient.serverMAC)) {
            System.out.println("Second decrypted message: " +  new String(noMac2));
        } else {
            throw new RuntimeException("macs dont match");
        }

        byte[] encryptAck2 = Helpers.encrypt("ack-two".getBytes(), myClient.clientEncrypt, myClient.clientIV, myClient.clientMAC);
        clientOutputStream.writeObject(encryptAck2); // now send encrypted acknowledgment back
    }

}