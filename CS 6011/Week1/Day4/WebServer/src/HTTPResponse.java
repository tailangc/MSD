import java.io.*;

public class HTTPResponse {
    String filePath;
    OutputStream clientStream;

    public HTTPResponse(String filePath, OutputStream clientStream) {
        this.clientStream = clientStream;
        this.filePath = filePath;
    }


    public void sendTheExistingFile(String filePath) {
        try {
            FileInputStream fileToRead = new FileInputStream(filePath);
            clientStream.write("HTTP/1.1 200\n".getBytes());
            clientStream.write("Content-Type: text/html\n".getBytes());
            clientStream.write("\n".getBytes());
            fileToRead.transferTo(clientStream);
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
}









