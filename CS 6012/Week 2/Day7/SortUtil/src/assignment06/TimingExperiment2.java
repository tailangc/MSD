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

                long totalTime = 0;


                ArrayList<Integer> permutedAL = new ArrayList<>();

                for ( int i = 0 ; i < size ; i++ ) {
                    permutedAL.add( i );
                }

                Collections.shuffle( permutedAL, random );

                TreeSet<Integer> treeset = new TreeSet<>();
                BinarySearchTree<Integer> bst = new BinarySearchTree<>();


                for (int iter = 0; iter < ITER_COUNT; iter++) {

                    long start = System.nanoTime();

                    //1.Tree set permuted add
                    for ( int i = 0 ; i < size ; i++ ) {
                        treeset.add( permutedAL.get( i ) );
                    }

                    //2. Tree set permuted contains
                    treeset.containsAll( permutedAL );
                    treeset.addAll( permutedAL );
                    for ( int i = 0 ; i < size ; i++ ) {
                        treeset.contains( i );
                    }

//                  3. BST add permuted
                    for ( int i = 0 ; i < size ; i++ ) {
                        bst.add( permutedAL.get( i ) );
                    }

//                  4. BST permuted contains
                    bst.addAll( permutedAL );
                    bst.containsAll( permutedAL );
                    for ( int i = 0 ; i < size ; i++ ) {
                        bst.contains( i );
                    }
                    long stop = System.nanoTime();
                    totalTime += stop - start;
                }
                double averageTime = totalTime / (double) ITER_COUNT;
                System.out.println(size + "\t" + averageTime);
                fw.write(size + "\t" + averageTime + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}