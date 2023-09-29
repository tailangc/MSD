import java.util.ArrayList;
import java.util.*;
import java.util.ArrayList;
import java.io.*;
import java.text.DecimalFormat;
public class Raindata {
    private String cityName;
    private ArrayList<Double> rainfallData = new ArrayList<>();

    private static final String[] months = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
    };



    public Raindata(String filename)throws FileNotFoundException{
        String line;
        Scanner fileReader = new Scanner(new FileInputStream(filename));
        cityName = fileReader.nextLine();
        while (fileReader.hasNextLine()){
            fileReader.next();
            fileReader.nextInt();
            rainfallData.add(fileReader.nextDouble());
        }
    }




    public double getTotalRainFall (){
        double sum = 0.0;
        for (double rainfall : rainfallData) {
            sum += rainfall;
        }
        return sum / rainfallData.size();
    }

    public double getMonthlyAverage (int month){
        double sum = 0;
        for (int i = month - 1; i < rainfallData.size(); i += 12) {
            sum += rainfallData.get(i);
        }
        return sum / 20;
    }



    public void generateReport() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream("rainfall_results.txt"));
        DecimalFormat df = new DecimalFormat("#.##");

        pw.println("The overall average rainfall amount is " + df.format(getTotalRainFall()) + " inches.");

        for (int i = 0; i < 12; i++) {
            pw.println("The average rainfall amount for " + months[i] + " is " + df.format(getMonthlyAverage(i + 1)) + " inches.");
        }
        pw.close();
    }


}

