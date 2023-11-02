import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.security.NoSuchAlgorithmException;

public class MyRunnable implements Runnable{
    Socket client_;
    MyRunnable (Socket client){
        client_ = client;
    }
    @Override
    public void run() {
        InputStream clientRequestStream = null;
        try {
            clientRequestStream = client_.getInputStream();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream clientResponseStream = null;
        try {
            clientResponseStream = client_.getOutputStream();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        HTTPRequest hct = null;
        try {
            hct = new HTTPRequest(client_);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        String filePath = hct.getFilePath();
        HTTPResponse hr1 = new HTTPResponse(filePath, clientResponseStream, hct);
        try {
            hr1.sendResponse();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
//        hr1.sendTheExistingFile(filePath);
    }
}
