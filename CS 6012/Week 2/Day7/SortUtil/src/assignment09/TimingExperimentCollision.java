package assignment09;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;


public class TimingExperimentCollision {
    public static int ITER_COUNT = 1000;

    private static ArrayList<Segment> createVerticalSegments(int size) {
        ArrayList<Segment> res = new ArrayList();
        for (int i = 0; i < size; i++) {
            res.add(new Segment(i, 0, i, 10));
        }
        return res;
    }
    //vertical segments dont have intersections so the no of segments wont change after the tree is built.


    public static void main(String[] args) {
        // you spin me round baby, right round
        long startTime = System.nanoTime();
        while (System.nanoTime() - startTime < 1_000_000_000);

        for (int exp = 10; exp <= 20; exp++) { // This is used as the exponent to calculate the size of the set.
            int size = (int) Math.pow(2, exp); // or ..

            ArrayList<Segment> data = createVerticalSegments(size);
            int index = new Random().nextInt(size);
            Segment query = data.get(index);
            BSPTree tree = new BSPTree(data);


            long totalTime1 = 0;
            long totalTime2 = 0;
            for (int iter = 0; iter < ITER_COUNT; iter++) {
                // TIME IT!
                long start1 = System.nanoTime();
                tree.collision(query);
                long stop1 = System.nanoTime();
                long start2 = System.nanoTime();
                AtomicBoolean collisionFound = new AtomicBoolean(false);
                tree.traverseFarToNear(0, 0, //they don't matter
                        (segment) -> {
                            if(segment.intersects(query)){
                                collisionFound.set(true);
                            }
                        }
                );
                long stop2 = System.nanoTime();
                totalTime1 += stop1 - start1;
                totalTime2 += stop2 - start2;

            }
            System.out.println(size + "\t" + totalTime1 / ITER_COUNT + "\t" + totalTime2 / ITER_COUNT); // print to console
            // System.out.println(size + "\t" + collisions); // print to console
        }

    }
}