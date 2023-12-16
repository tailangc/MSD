package assignment06;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class TimingExperiment2 {
    private static final int ITER_COUNT = 100;
    public static void main(String[] args) {

        long startTime = System.nanoTime();

        while (System.nanoTime() - startTime < 1_000_000_000)
            ;

        try (FileWriter fw = new FileWriter( ".tsv") ) {
            Random random = new Random( 123 );


            for (int exp = 5; exp <= 15; exp++) {

                int size = (int) Math.pow(2, exp);

                long totalTime_contain = 0;
                long totalTime_add = 0;
                long totalTime_remove = 0;


                ArrayList<Integer> permutedAL = new ArrayList<>();

                for ( int i = 0 ; i < size ; i++ ) {
                    permutedAL.add( i );
                }

//                Collections.shuffle( permutedAL, random );

                TreeSet<Integer> treeset = new TreeSet<>();
                BinarySearchTree<Integer> bst = new BinarySearchTree<>();

//                bst.addAll(permutedAL);

                for (int iter = 0; iter < ITER_COUNT; iter++) {

                    int ran = random.nextInt();

                    // TIME IT!
                    long start_contain = System.nanoTime();
                    treeset.contains(ran);
                    long stop_contain = System.nanoTime();
                    totalTime_contain += stop_contain - start_contain;


                    long start_add = System.nanoTime();
                    treeset.add(ran);
                    long stop_add = System.nanoTime();
                    totalTime_add += stop_add - start_add;
                    treeset.remove(ran);

                    boolean removeRes;
                    long start_remove = System.nanoTime();
                    removeRes= treeset.remove(ran);
                    long stop_remove = System.nanoTime();
                    totalTime_remove += stop_remove - start_remove;
                    if(removeRes){
                        treeset.add(ran);
                    }
                }
                double averageTime_contain = totalTime_contain / (double) ITER_COUNT;
                double averageTime_add = totalTime_add / (double) ITER_COUNT;
                double averageTime_remove = totalTime_remove / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime_contain + "\t" + averageTime_add + "\t" + averageTime_remove);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}