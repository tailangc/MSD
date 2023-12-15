//package assignment04;
//
//public class TimingExperimentSortComparison {
//    //pivot being the best pivot
//    //threshold being the best threshold
//// }

package assignment04;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class TimingExperimentSortComparison {

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
                long totalTimeQuick = 0;
                long totalTimeMerge = 0;

                ArrayList<Integer> testArray = SortUtil.generateWorstCase(size);
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
                    totalTimeQuick += stop - start;

                    long start_merge = System.nanoTime();
                    SortUtil.mergesort(copyArray, Integer::compareTo);
                    long stop_merge = System.nanoTime();
                    totalTimeMerge += stop_merge - start_merge;


                }
                double averageTime_quick = totalTimeQuick / (double) ITER_COUNT;
                double averageTime_merge = totalTimeMerge / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime_merge + "\t" + averageTime_quick); // print to console
                fw.write(size + "\t" + averageTime_merge + "\n"); // write to file.
//                if(averageTime_quick < averageTime_merge){
//                    System.out.println("Merge Sort for size ::"+size+" took "+averageTime_merge+ " Which is greater than quick sort time "+averageTime_quick);
//                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}