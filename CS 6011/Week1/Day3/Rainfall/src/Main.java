import java.io.FileNotFoundException;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) throws FileNotFoundException {


        Raindata rainData = new Raindata("src/rainfall_data.txt");
        rainData.generateReport();
            try {
                    //Raindata rainData = new Raindata("src/rainfall_data.txt");
                    //rainData.generateReport();
                System.out.printf("Hello");
            }

            catch (Exception e) {
                    System.out.println("Error: " + e.toString());
            }
    }
}