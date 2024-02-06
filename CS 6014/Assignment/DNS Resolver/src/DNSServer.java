import java.io.IOException;
import java.net.*;

public class DNSServer {
    private final int maxSize = 512, localPort = 8053, serverPort = 53;
    private final String localHost = "127.0.0.1", serverHost = "8.8.8.8";
    private final DatagramPacket localPacket, serverPacket;
    private final DatagramSocket localSocket, serverSocket;

    public DNSServer() throws UnknownHostException, SocketException {
        localPacket = new DatagramPacket(new byte[maxSize], maxSize);
        serverPacket = new DatagramPacket(new byte[maxSize], maxSize, InetAddress.getByName(serverHost), serverPort);
        localSocket = new DatagramSocket(localPort);
        serverSocket = new DatagramSocket();
    }

    public void listen() throws IOException {
        while (true) {
            System.out.println("DNSServer listening for DNS request...");
            decodeLocalPacket();
        }
    }

    private void decodeLocalPacket() throws IOException {
        localSocket.receive(localPacket);
        System.out.println("DNS request packet ( " + localPacket.getLength() + " bytes ) received from " + localHost +
                " at port " + localPort + ".");
        //Decode packet into DNSMessage
        System.out.println("Decoding DNS request packet...");
        DNSMessage dnsMessage = DNSMessage.decodeMessage(localPacket.getData());
        System.out.println("Decoded DNS request packet: " + dnsMessage + ".");
        //Check DNSCache for any cached DNSQuestion
        for (DNSQuestion dnsQuestion : dnsMessage.getDnsQuestions()) {
            System.out.println("Searching DNSCache for possible record to question '" + dnsQuestion.getQName()
                    + "'...");
            DNSRecord dnsRecord = DNSCache.get(dnsQuestion);
            if (dnsRecord == null && (dnsRecord = decodeServerPacket()) != null) {
                DNSCache.put(dnsQuestion, dnsRecord);
            } else {
                System.out.println("Found a matching record.");
            }
            dnsMessage.setDnsRecord(dnsRecord);
            System.out.println("Decoded DNS response record for DNS request packet ID="
                    + dnsMessage.getDnsHeader().getId() + ": " + dnsRecord);
        }
        //write encoded DNSMessage into packet
        System.out.println("Encoding DNS response packet...");
        localPacket.setData(dnsMessage.writeMessage());
        System.out.println("Encoded DNS response packet: " + dnsMessage + ".");
        //Respond to DNS request
        localSocket.send(localPacket);
        System.out.println("DNS response packet ( " + localPacket.getLength() + " bytes ) sent to " + localHost +
                " at port " + localPort + ".");
    }

    private DNSRecord decodeServerPacket() throws IOException {
        System.out.println("No matching record.");
        //Forward DNS request to DNS server
        serverPacket.setData(localPacket.getData());
        System.out.println("Forwarding the DNS request package to " + serverHost + " at port " + serverPort + "...");
        serverSocket.send(serverPacket);
        //Await a DNS response
        serverSocket.receive(serverPacket);
        System.out.println("DNS response packet ( " + serverPacket.getLength() + " bytes ) received from " + serverHost +
                " at port " + serverPort + ".");
        //Decode packet into DNSMessage
        System.out.println("Decoding DNS response packet...");
        DNSMessage dnsMessage = DNSMessage.decodeMessage(serverPacket.getData());
        DNSRecord dnsRecord = null;
        if (dnsMessage.getDnsHeader().getRCode() == 0x3) {
            //Get the first DNSQuestion
            DNSQuestion dnsQuestion = dnsMessage.getDnsQuestions().get(0);
            //Get offset value and applies message compression scheme bits
            int offset = dnsQuestion.getOffset();
            offset = setNthBit(offset, 15);     //Most left bit of 2nd byte of message compression
            offset = setNthBit(offset, 14);     //Second left bit of 2nd byte of message compression
            byte[] bytes = new byte[2];
            bytes[0] = (byte) ((offset & 0xFF00) >> 8); //Get value of the 2nd byte from the right and shift it right to 1st byte
            bytes[1] = (byte) (offset & 0xFF);          //Get value of the 1st byte from the right;
            //Handle the name error
            dnsRecord = new DNSRecord(dnsQuestion.getQName(), bytes, dnsQuestion.getQType(),
                    dnsQuestion.getQClass(), 3600, 4, "0.0.0.0");
        }
        if (dnsRecord != null)
            return dnsRecord;
        else
            return dnsMessage.getDnsRecords().get(0);
    }

    public void close() {
        localSocket.close();
        serverSocket.close();
    }

    private static int setNthBit(int value, int nth) {
        //Set the bit at the nth position in int value (4 bytes)
        return ((1 << nth) | value);
    }
}