package assignment04;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class TimingExperimentPivot {

    private static final int ITER_COUNT = 100;

    public static void main(String[] args) {
        // you spin me round baby, right round
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        try (FileWriter fw = new FileWriter(new File("threshold_experiment.tsv"))) { // open up a file writer
            Random random = new Random();
            for (int exp = 0; exp <= 500; exp++) { // This is used as the exponent to calculate the size of the set.
                //int size = (int) Math.pow(2, exp); // or ..
                int size = exp;
                // Do the experiment multiple times, and average out the results
                long totalTimeInsertion = 0;
                long totalTimeMerge = 0;

                ArrayList<Integer> testArray = SortUtil.generateBestCase(size);
                Collections.shuffle(testArray, random);

                for (int iter = 0; iter < ITER_COUNT; iter++) {
                    // SET UP!
                    ArrayList<Integer> copyArray = new ArrayList<>(testArray);

                    // TIME IT!
                    long start = System.nanoTime();
                    SortUtil.insertionSort(copyArray, Integer::compareTo);
                    long stop = System.nanoTime();
                    totalTimeInsertion += stop - start;

                    long start_merge = System.nanoTime();
                    SortUtil.mergesort(copyArray, Integer::compareTo);
                    long stop_merge = System.nanoTime();
                    totalTimeMerge += stop_merge - start_merge;


                }
                double averageTime = totalTimeInsertion / (double) ITER_COUNT;
                double averageTime_merge = totalTimeMerge / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime_merge); // print to console
                fw.write(size + "\t" + averageTime_merge + "\n"); // write to file.
                if(averageTime < averageTime_merge){
                    System.out.println("Merge Sort for size ::"+size+" took "+averageTime_merge+ " Which is greater than insertion sort time "+averageTime);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}