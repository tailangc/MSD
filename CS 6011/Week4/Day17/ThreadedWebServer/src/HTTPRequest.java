import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.Scanner;

public class HTTPRequest {
    public InputStream clientRequest;
    String key;
    String filePath;
    boolean isWebSocketRequest;
    HashMap<String, String> hs_;
    Socket client;


    public HTTPRequest(Socket client) throws IOException {
        this.client = client;
//        this.clientRequest = new Scanner(client.getInputStream());
        isWebSocketRequest = false;
        hs_ = new HashMap<>();
        getTheFileName();

    }

    public void getTheFileName() throws IOException {
        Scanner sc = new Scanner(client.getInputStream());
        int lineCount = 0;
        String line = sc.nextLine();
        System.out.println(line);
        String fileName = line.split(" ")[1];

        while (sc.hasNextLine()) {
            String requestLine = sc.nextLine();
            if (requestLine.isEmpty()) {
                break;
            }
            System.out.println(requestLine);
            String[] parts = requestLine.split(": ", 2);
            String key = parts[0];
            String value = parts[1];
            hs_.put(key, value);
        }
        isWebSocketRequest = hs_.containsKey("Sec-WebSocket-Key");
        if (isWebSocketRequest) {
            key = hs_.get("Sec-WebSocket-Key");
        } else {
            if (fileName.equals("/")) {// if client input "/" just return to the index.html
                fileName = "/index.html";
            }
            filePath = "Resources" + fileName;
            System.out.println(filePath); //cout the file path we can see how many web page shows,Not important though
        }
//        if(fileName.equals("/")){// if client input "/" just return to the index.html
//            fileName = "/index.html";
//        }
    }
    public String getKey(){
        return key;
    }

    public String getFilePath(){
        return filePath;
    }

    public boolean isWebSocketRequest() {
        return isWebSocketRequest;
    }

    public Socket getClient() {
        return client;
    }
}
