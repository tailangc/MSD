package assignment05;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class TimingExperimentPeek {

    private static final int ITER_COUNT = 100;

    public static void main(String[] args) {

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter(new File("ArrayStackPeek3.tsv"))) { // open up a file writer so we can write
            // to file.
            for (int exp = 10; exp <= 20; exp++) { // This is used as the exponent to calculate the size of the set.

                int size = (int) Math.pow(2, exp);
                // Do the experiment multiple times, and average out the results
                long totalTime = 0;
                long totalTimeArr = 0;

                //Array list stack fill
                ArrayStack<Integer> arrayStack = new ArrayStack<>();
                //Linked list stack fill
                LinkedListStack<Integer> listStack = new LinkedListStack<>();

                for (int i = 0; i < size; i++){
                    listStack.push(i);
                    arrayStack.push(i);
                }






                for (int iter = 0; iter < ITER_COUNT; iter++) {


                    // TIME IT!
                    long start = System.nanoTime();
                    arrayStack.peek();
                    long stop = System.nanoTime();
                    totalTime += stop - start;

                    long start2 = System.nanoTime();
                    arrayStack.push(0);
                    long stop2 = System.nanoTime();
                    totalTimeArr += stop2 - start2;
                }

                double averageTime = totalTime / (double) ITER_COUNT;
                double averageArr = totalTimeArr / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime  + "\t" + averageArr); // print to console

                fw.write(size + "\t" + averageTime + "\n"); // write to file.
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}