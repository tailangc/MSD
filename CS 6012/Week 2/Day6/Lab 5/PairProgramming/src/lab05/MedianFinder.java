package lab05;

import java.util.Arrays;
import java.util.Comparator;

public class MedianFinder {

    // First method with Comparable constraint
    public static <T extends Comparable<T>> T findMedian(T[] array) {
        if(array == null){
            throw new IllegalArgumentException("Array cannot be empty");
        }

        Arrays.sort(array);
        int middle = array.length / 2;
        if (array.length % 2 == 0) {
            return array[middle - 1]; // Return the lower element in the middle for even-sized arrays
        } else {
            return array[middle];
        }
    }


    public static <T> T findMedian(T[] array, Comparator<T> comparator) {
        if(array == null){
            throw new IllegalArgumentException("Array cannot be empty");
        }
        if(comparator == null){
            throw new IllegalArgumentException("Comparator cannot be empty");
        }

        Arrays.sort(array, comparator);
        int middle = array.length / 2;
        if (array.length % 2 == 0) {
            return array[middle - 1];
        } else {
            return array[middle];
        }
    }
}

