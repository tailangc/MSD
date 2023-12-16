package assignment07;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Random;

public class TimingExperiment2 {
    private static final int ITER_COUNT = 10;

    public static void main(String[] args) {

        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000) ;

        try (FileWriter fw = new FileWriter(new File("Functor_Timing.tsv"))) { // open up a file writer so we can write
            Random random = new Random(123);
            System.out.println("size\tBadHash\tMedHash\tGoodHash");
            for (int exp = 5; exp <= 18; exp++) { // This is used as the exponent to calculate the size of the set.
                int size = (int) Math.pow(2, exp);

                //Initialize hash functors to test
                GoodHashFunctor goodFunctor = new GoodHashFunctor();
                MediocreHashFunctor mediocreHashFunctor = new MediocreHashFunctor();
                BadHashFunctor badFunctor = new BadHashFunctor();

                ChainingHashTable goodTable = new ChainingHashTable(size, goodFunctor);
                ChainingHashTable medTable = new ChainingHashTable(size, mediocreHashFunctor);
                ChainingHashTable badTable = new ChainingHashTable(size, badFunctor);


                //ArrayList to store random strings
                ArrayList<String> aL = new ArrayList<>();
                for ( int i = 0; i < size; i++ ){
                    aL.add(generateRandomString());
                }

                goodTable.addAll(aL);
                medTable.addAll(aL);
                badTable.addAll(aL);

                // Do the experiment multiple times, and average out the results
                long totalTime1 = 0, totalTime2 = 0, totalTime3 = 0;
                for (int iter = 0; iter < ITER_COUNT; iter++) {
                    //String value to check for containment/removal
                    String key = aL.get(random.nextInt(size));

                    ////////////////////TEST ADD/CONTAINS/REMOVE //////////////////////////

                    long start1 = System.nanoTime();
//                     badTable.contains(key);
//                    badTable.remove(key);
                    badTable.add(key);
                    long stop1 = System.nanoTime();
                    badTable.remove(key);
                    totalTime1 += stop1 - start1;

                    long start2 = System.nanoTime();
//                     medTable.contains(key);
//                    medTable.remove(key);
                    medTable.add(key);
                    long stop2 = System.nanoTime();
                    medTable.remove(key);
                    totalTime2 += stop2 - start2;

                    long start3 = System.nanoTime();
//                     goodTable.contains(key);
//                    goodTable.remove(key);
                    goodTable.add(key);
                    long stop3 = System.nanoTime();
                    goodTable.remove(key);
                    totalTime3 += stop3 - start3;


                }

                double averageTime1 = totalTime1 / (double) ITER_COUNT;
                double averageTime2 = totalTime2 / (double) ITER_COUNT;
                double averageTime3 = totalTime3 / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime1 + "\t" + averageTime2 + "\t" +averageTime3); // print to console

                fw.write(size + "\t" + averageTime1 + "\t" + averageTime2 + "\t" + averageTime3 + "\n"); // write to file.
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     *
     * @return a randomly generated string
     * void function that prouces a randomly generated string
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