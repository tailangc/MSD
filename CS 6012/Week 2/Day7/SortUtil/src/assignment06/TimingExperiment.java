package assignment06;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Random;

public class TimingExperiment {
    private static final int ITER_COUNT = 100;

    public static void main(String[] args) {

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter(new File("Contains_Experiment.tsv"))) { // open up a file writer so we can write
            Random random = new Random(123);

            for (int exp = 5; exp <= 15; exp++) { // This is used as the exponent to calculate the size of the set.


                int size = (int) Math.pow(2, exp);
                // Do the experiment multiple times, and average out the results
                long totalTime = 0;

                BinarySearchTree<Integer> bst = new BinarySearchTree<>();

                ArrayList<Integer> aL = new ArrayList<>();

                for ( int i = 0; i < size; i++){
                    aL.add(i);
                }

                Collections.shuffle(aL, random);

                bst.addAll(aL);


                for (int iter = 0; iter < ITER_COUNT; iter++) {


                    // TIME IT!
                    long start = System.nanoTime();

//                    bst.containsAll(aL); //does
                    for ( int i = 0; i < size; i++){
                        bst.contains(i);
                    }

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