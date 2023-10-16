import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;


public class MyHttpServer {
    public static void main(String[] args) throws IOException {
        ServerSocket server;
        try {
            server = new ServerSocket(8080);
        }
        catch (IOException ex) {
            try{
            server = new ServerSocket(8090);
            }
            catch (IOException eh){
                System.out.println("can not open" + eh.getMessage());
                throw new RuntimeException();
            }
        }
        while (true) {//use while to wait the client to accept
            Socket client = server.accept();
            InputStream clientRequestStream = client.getInputStream();
            OutputStream clientResponseStream = client.getOutputStream();
            HTTPRequest hct = new HTTPRequest(clientRequestStream);
            String filePath = hct.getTheFileName();
            HTTPResponse hr1 = new HTTPResponse(filePath,clientResponseStream);
            hr1.sendTheExistingFile(filePath);
        }
//        catch(IOException e) {
//            try{
//                ServerSocket server = new ServerSocket(8090);
//                while (true) {//use while to wait the client to accept
//                    Socket client = server.accept();
//                    InputStream clientRequestStream = client.getInputStream();
//                    OutputStream clientResponseStream = client.getOutputStream();
//                    HTTPRequest hct = new HTTPRequest(clientRequestStream);
//                    String filePath = hct.getTheFileName();
//                    HTTPResponse hr1 = new HTTPResponse(filePath,clientResponseStream);
//                    hr1.sendTheExistingFile(filePath);
//
//                }
//            }
//            catch (IOException eh){
//                System.out.println("can not open" + eh.getMessage());
//            }

        }
    }