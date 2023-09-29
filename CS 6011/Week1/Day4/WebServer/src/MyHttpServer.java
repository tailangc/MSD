import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

//yuyao tu / Thu Sep 28/ Week1/Day4, HW Project Name: MyHttpServer
public class MyHttpServer {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(8080);
        while (true) {
            Socket client = server.accept();
//            System.out.println(client.getInputStream().read());
            Scanner sc = new Scanner(client.getInputStream());
            String fileName = "";
            if (sc.hasNext()) {

                String[] lines = sc.nextLine().split(" ");
                if (!lines[1].isEmpty()) {
                    fileName = lines[1];
                }
            }
            if (fileName.equals("/")) {
                fileName = "/index.html";
            }
            String filePath = "/Users/tailangcao/myGithubRepo/CS 6011/Week1/Day4/WebServer/Resources" + fileName;

//            System.out.println(filePath);

            File file = new File(filePath);
            if (file.exists()) {
                FileInputStream fileToRead = new FileInputStream(file);
                OutputStream outputStream = client.getOutputStream();
                outputStream.write("HTTP/1.1 200\n".getBytes());
                outputStream.write("Content-Type: text/html\n".getBytes());
                outputStream.write("\n".getBytes());
                fileToRead.transferTo(outputStream);
                outputStream.flush();
                outputStream.close();
            } else {
                FileInputStream fileToRead = new FileInputStream("/Users/yuyaotu/Desktop/cs6011-labs/week1/day4/MyHttpServer/resources/error.html");
                OutputStream outputStream = client.getOutputStream();
                outputStream.write("HTTP/1.1 404\n".getBytes());
                outputStream.write("Content-Type: text/html\n".getBytes());
                outputStream.write("\n".getBytes());
                fileToRead.transferTo(outputStream);
                outputStream.flush();
                outputStream.close();
            }

        }
    }
}







