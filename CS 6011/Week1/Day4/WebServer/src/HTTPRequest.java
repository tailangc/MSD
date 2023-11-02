import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class HTTPRequest {
    InputStream clientRequest;
    public HTTPRequest(InputStream clientRequest_)  {
        this.clientRequest = clientRequest_;
    }

    public  String getTheFileName(){
        try {

        }
        catch (Exception ex) {
            System.out.println(ex);
        }
        Scanner sc = new Scanner(clientRequest);
        String fileName = "";
        if (sc.hasNext()) {//if sc do had next. get the next line and split the blank get each string

            String[] lines = sc.nextLine().split(" ");
            if(!lines[1].isEmpty()){ //if the lines 1 is not empty,then the filename = to lines 1
                fileName = lines[1];
            }
        }
        System.out.println("filename:"+fileName);
        if(fileName.equals("/")){// if client input "/" just return to the index.html
            fileName = "/index.html";
        }
        String filePath = "/Users/tailangcao/myGithubRepo/CS 6011/Week1/Day4/WebServer/Resources/"+fileName;
        System.out.println(filePath); //cout the file path we can see how many web page shows,Not important though
        return  filePath;
    }

}