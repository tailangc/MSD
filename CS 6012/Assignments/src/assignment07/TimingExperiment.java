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

            for (int exp = 5; exp <= 15; exp++) { // This is used as the exponent to calculate the size of the set.
                int size = (int) Math.pow(2, exp);

                //Initialize hash functors to test
                GoodHashFunctor goodFunctor = new GoodHashFunctor();
                MediocreHashFunctor mediocreHashFunctor = new MediocreHashFunctor();
                BadHashFunctor badFunctor = new BadHashFunctor();

                //Initialize hash tables with each hash functor with varying capacities
                ChainingHashTable goodTable = new ChainingHashTable(size, goodFunctor);
                ChainingHashTable medTable = new ChainingHashTable(size, mediocreHashFunctor);
                ChainingHashTable badTable = new ChainingHashTable(size, badFunctor);

                // Do the experiment multiple times, and average out the results
                int badTotal = 0, medTotal = 0, goodTotal = 0;
                for ( int iter = 0; iter < ITER_COUNT; iter++) {
                    //Fill hash table with random string for size
                    for (int i = 0; i < size; i++) {
                        String s = generateRandomString();
                        badTable.add(s);
                        medTable.add(s);
                        goodTable.add(s);
                    }

                    badTotal += badTable.collision_;
                    medTotal += medTable.collision_;
                    goodTotal += goodTable.collision_;

                    badTable.clear();
                    medTable.clear();
                    goodTable.clear();
                }
                System.out.println(size  + "\t" +  (badTotal / ITER_COUNT) + "\t" +  (medTotal / ITER_COUNT) + "\t" +  (goodTotal/ ITER_COUNT)); // print to console

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