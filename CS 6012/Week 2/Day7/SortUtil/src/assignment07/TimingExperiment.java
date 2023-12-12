package assignment07;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Random;

public class TimingExperiment {
    private static final int ITER_COUNT = 10;

    public static void main(String[] args) {

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter(new File("Collisions_Experiment.tsv"))) { // open up a file writer so we can write
            System.out.println("size\tBadHash\tMedHash\tGoodHash");

            for (int exp = 1; exp <= 9; exp++) { // This is used as the exponent to calculate the size of the set.

                int size = exp * 100;


                //Initialize hash functors to test
                GoodHashFunctor goodFunctor = new GoodHashFunctor();
                MediocreHashFunctor mediocreHashFunctor = new MediocreHashFunctor();
                BadHashFunctor badFunctor = new BadHashFunctor();

                //Initialize hash tables with each hash functor with varying capacities
                ChainingHashTable goodTable = new ChainingHashTable(10000, goodFunctor);
                ChainingHashTable medTable = new ChainingHashTable(10000, mediocreHashFunctor);
                ChainingHashTable badTable = new ChainingHashTable(10000, badFunctor);

                // Do the experiment multiple times, and average out the results
                for ( int iter = 0; iter < ITER_COUNT; iter++) {




                    // TIME IT!
                    long start = System.nanoTime();

                    //Fill hash table with random string for size
                    for (int i = 0; i < size; i++) {
                        badTable.add(generateRandomString());
                        medTable.add(generateRandomString());
                        goodTable.add(generateRandomString());

                    }
                    long stop = System.nanoTime();
                }
                System.out.println(size  + "\t" +  (badTable.collision_ / ITER_COUNT) + "\t" +  (medTable.collision_ / ITER_COUNT) + "\t" +  (goodTable.collision_ / ITER_COUNT)); // print to console

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    /**
     *
     * @return a randomly generated string
     * void function that produces a randomly generated string
     * with possibilities of lowercase, uppercase, or numbers values in the form of a string
     */
    private static String generateRandomString() {

        Random randomInt = new Random();

        int length = randomInt.nextInt(20) ; // Adjust the length of the random strings as needed
        String characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        StringBuilder randomString = new StringBuilder();

        Random random = new Random();
        for (int i = 0; i < length; i++) {
            int index = random.nextInt(characters.length());
            randomString.append(characters.charAt(index));
        }

        return randomString.toString();
    }
}