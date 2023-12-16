package assignment04;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class TimingExperimentThreshold {
    private static final int ITER_COUNT = 100;

    public static void main(String[] args) {
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter(new File("threshold_experiment.tsv"))) { // open up a file writer so we can write to file.
            Random random = new Random();
            for (int exp = 5; exp <= 15; exp++) { // This is used as the exponent to calculate the size of the set.
                //int size = (int) Math.pow(2, exp); // or ..
                int size = (int) Math.pow(2, exp);

                // Do the experiment multiple times, and average out the results
                long totalTime = 0;

                ArrayList<Integer> testArray = SortUtil.generateAverageCase(size);
                Collections.shuffle(testArray, random);

                for (int iter = 0; iter < ITER_COUNT; iter++) {
                    // SET UP!
                    ArrayList<Integer> copyArray = new ArrayList<>(testArray);

                    // TIME IT!
                    long start = System.nanoTime();
                    SortUtil.mergesort(copyArray, Integer::compareTo);
                    long stop = System.nanoTime();
                    totalTime += stop - start;
                }
                double averageTime = totalTime / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime); // print to console
                fw.write(size + "\t" + averageTime + "\n"); // write to file.
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}