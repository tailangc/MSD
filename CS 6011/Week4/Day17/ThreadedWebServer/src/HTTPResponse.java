import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.HashMap;
import java.util.Map;

public class HTTPResponse {
    String filePath;
    OutputStream clientStream;
    HTTPRequest request;
    private String echoMessage_;
    private String messageType_;
    private String roomname_;
    private String username_;
    private String message_;
    private Room room;

    public HTTPResponse(String filePath, OutputStream clientStream, HTTPRequest request) {
        this.clientStream = clientStream;
        this.filePath = filePath;
        this.request = request;
    }

    public void sendResponse() throws NoSuchAlgorithmException, IOException {
        System.out.println("send resopnse:" + request.isWebSocketRequest);

        if (request.isWebSocketRequest()) {
            sendWsHandshakeHeader(request.getKey());
            while( true ) {
                DataInputStream in = new DataInputStream( request.getClient().getInputStream() );
                boolean isMask = true;
                byte[] header = in.readNBytes(2);
                byte b0 = header[0];
                byte b1 = header[1];
                int opcode = b0 & 0x0F;
                int length = b1 & 0x7F;
                if (length == 126) {
                    length = in.readShort();
                } else if (length == 127) {
                    length = (int) in.readLong();
                }
                if((b1 >> 7) == 0){ //not masked
                    isMask = false;
                }
                System.out.println("length: " + length);
                byte[] DECODED;

                if(isMask){
                    System.out.println("The message is masked!");
                    DECODED = new byte[length];
                    byte[] MASK = in.readNBytes(4);
                    byte[] ENCODED = in.readNBytes(length);
                    for(int i = 0; i < ENCODED.length; i++){
                        DECODED[i] = (byte) (ENCODED[i] ^ MASK[i%4]);
                    }
                }
                else{
                    DECODED = in.readNBytes(length);
                }

                echoMessage_ = new String(DECODED);
                System.out.println("This is the decoded message" + echoMessage_);

//                writeMessage(echoMessage_, clientStream);

                messageType_ = getMessageType();
                System.out.println("msg type : " + messageType_);
                roomname_ = getRoomname();
                username_ = getUsername();
                if (messageType_.equals("message")) {
                    message_ = getMessage();
                    room.sendMessageToAllUsers( echoMessage_ );
                }

                room = Room.getRoom( roomname_ );

                if ( messageType_.equals("join") ) {

                    if (!room.getUsersMap_().containsKey(username_)) {

                        room.sendMessageToAllUsers( echoMessage_ );
                        room.addClient(username_, request.getClient());
                        for (String message : room.getMessagesList()) {
                            writeMessage(message, clientStream);
                        }

                    }
                    else {

                        System.out.println(username_ + " is already in the room.");
                    }
                }

                if ( messageType_.equals("leave") ) {
                    room.removeClient(username_, request.getClient());
                    room.sendMessageToAllUsers( echoMessage_ );
                }


//
            }

        } else {
            File file = new File(request.getFilePath());
            if (file.exists()) {
                sendTheExistingFile(request.getFilePath());
            }
            else{
                String errorFilePath = "/Users/tailangcao/myGithubRepo/CS 6011/Week1/Day4/WebServer/Resources/error.html";
                sendErrorFile(errorFilePath);
            }
        }
    }




    public static void writeMessage(String message, OutputStream out) throws IOException {
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        byte b0 =(byte) 0b10000001;
        dataOutputStream.write(b0);
        int len = message.length();
        if(len < 126){
            byte b1 = (byte) len;
            dataOutputStream.write(b1);
        }else if(len < (Math.pow(2,16))){
            byte b1 = (byte) 126;
            dataOutputStream.write(b1);
            dataOutputStream.writeShort(len);
        }else{
            byte b1 = (byte) 127;
            dataOutputStream.write(b1);
            dataOutputStream.writeLong(len);
        }
        dataOutputStream.writeBytes(message);
        dataOutputStream.flush();
    }


    public void sendTheExistingFile(String filePath) {
        try {
            FileInputStream fileToRead = new FileInputStream(filePath);
            clientStream.write("HTTP/1.1 200\n".getBytes());
//            clientStream.write("Content-Type: text/html\n".getBytes());
            clientStream.write("\n".getBytes());
            File file = new File(filePath);
            fileToRead.transferTo(clientStream);
//            for( int i = 0; i < file.length(); i++ ) {
//                clientStream.write( fileToRead.read() );
//                clientStream.flush();
////                try {
////                    Thread.sleep( 1 ); // Maybe add <- if images are still loading too quickly...
////                } catch (InterruptedException e) {
////                    throw new RuntimeException(e);
////                }
//            }
            clientStream.flush();
            clientStream.close();
        } catch (FileNotFoundException fe) {
            System.out.println(fe.getMessage());
            String errorFilePath = "/Users/tailangcao/myGithubRepo/CS 6011/Week1/Day4/WebServer/Resources/error.html";
            sendErrorFile(errorFilePath);
        } catch (IOException io) {
            System.out.println(io.getMessage());
        }
    }

    public void sendErrorFile(String errorFilePath) {
        try {
            FileInputStream fileToRead = new FileInputStream(errorFilePath);
            clientStream.write("HTTP/1.1 404\n".getBytes());
            clientStream.write("Content-Type: text/html\n".getBytes());
            clientStream.write("\n".getBytes());
            fileToRead.transferTo(clientStream);
            clientStream.flush();
            clientStream.close();
        } catch (FileNotFoundException fe) {
            System.out.println(fe.getMessage());
        } catch (IOException io) {
            System.out.println(io.getMessage());
        }
    }

    public void sendWsHandshakeHeader(String key) throws NoSuchAlgorithmException, IOException {
        String webSocketKey = "POyWHx5sH7G0wKq+XaQhRg==";// 客户端发送的Sec-WebSocket-Key
        String magicString = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

        String combined = key + magicString;

        // 使用SHA-1哈希算法进行散列
        MessageDigest sha1 = MessageDigest.getInstance("SHA-1");
        byte[] hashBytes = sha1.digest(combined.getBytes("UTF-8"));

        // 对哈希结果进行Base64编码
        String secWebSocketAccept = Base64.getEncoder().encodeToString(MessageDigest.getInstance("SHA-1").digest((key + magicString).getBytes("UTF-8")));
        System.out.println("HTTP/1.1 101 Switching Protocols");
        System.out.println("Upgrade: websocket");
        System.out.println("Connection: Upgrade");
        System.out.println("Sec-WebSocket-Accept: " + secWebSocketAccept);
        PrintWriter pw = new PrintWriter(clientStream);
        pw.println("HTTP/1.1 101 Switching Protocols");
        pw.println("Upgrade: websocket");
        pw.println("Connection: Upgrade");
        pw.println("Sec-WebSocket-Accept: " + secWebSocketAccept);
        pw.print("\n");
        pw.flush();
    }

    public String getMessageType() {

        String roomname = echoMessage_.split("\"type\":\"") [1];
        roomname = roomname.split("\"")[0];
        return roomname;
    }

    public String getUsername() {

        String roomname = echoMessage_.split("\"user\":\"")[1];
        roomname = roomname.split("\"")[0];
        return roomname;

    }

    public String getRoomname() {

        String roomname = echoMessage_.split("\"room\":\"")[1];
        roomname = roomname.split("\"")[0];
        return roomname;

    }

    public String getMessage() {

        String roomname = echoMessage_.split("\"message\":\"")[1];
        roomname = roomname.split("\"")[0];
        return roomname;

    }
}











