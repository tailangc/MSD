package lab06;

import java.util.ArrayList;
import java.util.Collections;

public class PriorityQueueExperiments {

    public static void main(String[] args) {
        // Experiment 1: Timing data structure creation

        // Varying sizes of N
        int[] sizes = {100, 1000, 10000, 100000};

        // Experiment with in-order data
        for (int size : sizes) {
            ArrayList<Integer> inOrderData = generateInOrderData(size);

            // Time TreeSetPriorityQueue creation
            long startTime = System.currentTimeMillis();
            Treeset<Integer> treeSetPriorityQueue = new Treeset<>();
            for (Integer element : inOrderData) {
                treeSetPriorityQueue.add(element);
            }
            long endTime = System.currentTimeMillis();
            System.out.println("TreeSetPriorityQueue with in-order data, size " + size + ": " + (endTime - startTime) + " ms");

            // Time HeapPriorityQueue creation
            startTime = System.currentTimeMillis();
            Heap<Integer> heapPriorityQueue = new Heap<>(inOrderData);
            endTime = System.currentTimeMillis();
            System.out.println("HeapPriorityQueue with in-order data, size " + size + ": " + (endTime - startTime) + " ms");
        }

        // Experiment with permuted data
        for (int size : sizes) {
            ArrayList<Integer> permutedData = generateInOrderData(size);
            Collections.shuffle(permutedData);

            // Time TreeSetPriorityQueue creation
            long startTime = System.currentTimeMillis();
            Treeset<Integer> treeSetPriorityQueue = new Treeset<>();
            for (Integer element : permutedData) {
                treeSetPriorityQueue.add(element);
            }
            long endTime = System.currentTimeMillis();
            System.out.println("TreeSetPriorityQueue with permuted data, size " + size + ": " + (endTime - startTime) + " ms");

            // Time HeapPriorityQueue creation
            startTime = System.currentTimeMillis();
            Heap<Integer> heapPriorityQueue = new Heap<>(permutedData);
            endTime = System.currentTimeMillis();
            System.out.println("HeapPriorityQueue with permuted data, size " + size + ": " + (endTime - startTime) + " ms");
        }

        // Experiment 2: Timing removeMin operation

        // Continue with the existing priority queues
        for (int size : sizes) {
            ArrayList<Integer> permutedData = generateInOrderData(size);
            Treeset<Integer> treeSetPriorityQueue = new Treeset<>();
            Heap<Integer> heapPriorityQueue = new Heap<>(permutedData);
            // Time TreeSetPriorityQueue removeMin
            long startTime = System.currentTimeMillis();
            while (!treeSetPriorityQueue.isEmpty()) {
                treeSetPriorityQueue.removeMin();
            }
            long endTime = System.currentTimeMillis();
            System.out.println("TreeSetPriorityQueue removeMin, size " + size + ": " + (endTime - startTime) + " ms");

            // Time HeapPriorityQueue removeMin
            startTime = System.currentTimeMillis();
            while (!heapPriorityQueue.isEmpty()) {
                heapPriorityQueue.removeMin();
            }
            endTime = System.currentTimeMillis();
            System.out.println("HeapPriorityQueue removeMin, size " + size + ": " + (endTime - startTime) + " ms");
        }
    }

    private static ArrayList<Integer> generateInOrderData(int size) {
        ArrayList<Integer> data = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            data.add(i);
        }
        return data;
    }
}
