package assignment06;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Random;

public class TimingExperiment {
    private static final int ITER_COUNT = 1000;

    public static void main(String[] args) {

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter(new File("Contains_Experiment.tsv"))) { // open up a file writer so we can write
            Random random = new Random(123);

            for (int exp = 5; exp <= 15; exp++) { // This is used as the exponent to calculate the size of the set.


                int size = (int) Math.pow(2, exp);
                // Do the experiment multiple times, and average out the results
                long totalTime_contain = 0;
                long totalTime_add = 0;
                long totalTime_remove = 0;

                BinarySearchTree<Integer> bst = new BinarySearchTree<>();

                ArrayList<Integer> aL = new ArrayList<>();

                for ( int i = 0; i < size; i++){
                    aL.add(i);
                }

                Collections.shuffle(aL, random);

                bst.addAll(aL);


                for (int iter = 0; iter < ITER_COUNT; iter++) {

                    int ran = random.nextInt();

                    // TIME IT!
                    long start_contain = System.nanoTime();
                    bst.contains(ran);
                    long stop_contain = System.nanoTime();
                    totalTime_contain += stop_contain - start_contain;


                    long start_add = System.nanoTime();
                    bst.add(ran);
                    long stop_add = System.nanoTime();
                    totalTime_add += stop_add - start_add;
                    bst.remove(ran);

                    boolean removeRes;
                    long start_remove = System.nanoTime();
                     removeRes= bst.remove(ran);
                    long stop_remove = System.nanoTime();
                    totalTime_remove += stop_remove - start_remove;
                    if(removeRes){
                        bst.add(ran);
                    }

                }

                double averageTime_contain = totalTime_contain / (double) ITER_COUNT;
                double averageTime_add = totalTime_add / (double) ITER_COUNT;
                double averageTime_remove = totalTime_remove / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime_contain + "\t" + averageTime_add + "\t" + averageTime_remove); // print to console


//                fw.write(size + "\t" + averageTime + "\n"); // write to file.
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}