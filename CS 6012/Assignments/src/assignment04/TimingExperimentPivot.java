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
            for (int exp = 5; exp <= 15; exp++) { // This is used as the exponent to calculate the size of the set.
                int size = (int) Math.pow(2, exp); // or ..
                //first as pivot in best case is super slow, stop in advance
//                int size = exp;
                // Do the experiment multiple times, and average out the results
                long totalQuickSort = 0;
//                long totalTimeMerge = 0;

                ArrayList<Integer> testArray = SortUtil.generateBestCase(size);
                //try both best and average case
                //2 figures 3 plots
//                Collections.shuffle(testArray, random);

                for (int iter = 0; iter < ITER_COUNT; iter++) {
                    // SET UP!
                    ArrayList<Integer> copyArray = new ArrayList<>(testArray);

                    // TIME IT!
                    long start = System.nanoTime();
                    SortUtil.quicksort(copyArray, Integer::compareTo);
                    long stop = System.nanoTime();
                    totalQuickSort += stop - start;


                }
                double averageTime = totalQuickSort / (double) ITER_COUNT;

                System.out.println(size + "\t" + averageTime); // print to console

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}