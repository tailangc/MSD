package assignment09;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.SortedSet;
import java.util.TreeSet;

public class ContainsTimingExperiment {

    private static final int ITER_COUNT = 100;

    public static ArrayList<Segment> generateVerticalSegments(int size) {
        ArrayList<Segment> res = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            res.add(new Segment(1, i, 5, 2 * i));
        }
        return res;
    }

    public static void main(String[] args) {
        // you spin me round baby, right round
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        try (FileWriter fw = new FileWriter(new File("contains_experiment.tsv"))) { // open up a file writer so we can write
            // to file.
            Random random = new Random();
            System.out.println("in the try");
            for (int exp = 5; exp <= 9; exp++) { // This is used as the exponent to calculate the size of the set.
                int size = (int) Math.pow(2, exp); // or ..
                // Do the experiment multiple times, and average out the results
                ArrayList<Segment> segments = generateVerticalSegments(size);
                long totalTime = 0;
                for (int iter = 0; iter < ITER_COUNT; iter++) {
                    // SET UP!
                    long start = System.nanoTime();
                    BSPTree bspTree = new BSPTree();
                    for(int i = 0 ; i< size ;i++) {
                        bspTree.insert(segments.get(i));
                    }
                    long stop = System.nanoTime();
                    totalTime += stop - start;
                }
//                System.out.println("out of the ITER_COUNT for loop");
                double averageTime = totalTime / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime); // print to console
                fw.write(size + "\t" + averageTime + "\n"); // write to file.
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}