package assignment04;
//Partner : Yuyao Tu

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

import static java.util.Collections.swap;

public class SortUtil {
    private static int threshold_ = 0;
    private static int size_ = 0;
    //DRIVER METHOD
    public static <T> void mergesort(ArrayList<T> array, Comparator<? super T> comparator) {
        int start = 0;
        int end = array.size() - 1;
        Mergesort(array, start, end, comparator);
    }

    /**
     *
     * @param array
     * @param start
     * @param end
     * @param comparator
     * @param <T>
     */
    //MERGE-SORT METHOD
    private static <T> void Mergesort(ArrayList<T> array, int start, int end, Comparator<? super T> comparator) {
        int threshold = 6;
        if (end - start <= threshold) {
            insertionSort(array,comparator);
        } else {
            int middle = (start + end) / 2;
            Mergesort(array, start, middle, comparator);
            Mergesort(array, middle + 1, end, comparator);
            merge(array, start, middle, end, comparator);
        }
    }

    /**
     *
     * @param array
     * @param start
     * @param middle
     * @param end
     * @param comparator
     * @param <T>
     */
    //MERGE METHOD
    private static <T> void merge(ArrayList<T> array, int start, int middle, int end, Comparator<? super T> comparator) {
        T[] leftArray = (T[]) new Comparable[middle - start + 1];
        T[] rightArray = (T[]) new Comparable[end - middle];

        for (int i = 0; i < leftArray.length; i++) {
            leftArray[i] = array.get(start + i);
        }

        for (int i = 0; i < rightArray.length; i++) {
            rightArray[i] = array.get(middle + 1 + i);
        }

        int leftIndex = 0, rightIndex = 0;

        int currentIndex = start;

        while (leftIndex < leftArray.length && rightIndex < rightArray.length) {

            if (comparator.compare(leftArray[leftIndex], rightArray[rightIndex]) <= 0) {
                array.set(currentIndex, leftArray[leftIndex]);
                leftIndex++;
            } else {
                array.set(currentIndex, rightArray[rightIndex]);
                rightIndex++;
            }

            currentIndex++;
        }

        while (leftIndex < leftArray.length) {
            array.set(currentIndex++, leftArray[leftIndex++]);
        }

        while (rightIndex < rightArray.length) {
            array.set(currentIndex++, rightArray[rightIndex++]);
        }
    }

    /**
     *
     * @param arrayList
     * @param comparator<T>
     */
    //INSERTION SORT
    public static <T> void insertionSort(ArrayList<T> arrayList, Comparator<? super T> comparator) {
        int length = arrayList.size();

        for (int i = 1; i < length; i++) {
            T current = arrayList.get(i);
            int j = i - 1;

            // Keep moving elements to the right until the correct position is found
            while (j >= 0 && comparator.compare(arrayList.get(j), current) > 0) {
                // Shift elements to the right
                arrayList.set(j + 1, arrayList.get(j));
                j--;
            }
            // Set the correct position for the current element
            arrayList.set(j + 1, current);
        }
    }

    /**
     *
     * @param array
     * @param comparator
     * @param <T>
     */
    public static <T> void quicksort(ArrayList<T> array , Comparator<? super T> comparator){

        Quicksort(array,0,array.size() - 1,comparator);
    }
    /**
     *
     * @param array
     * @param start
     * @param end
     * @param comparator
     * @param <T>
     */
    public static<T> void Quicksort(ArrayList<T> array, int start, int end, Comparator<? super T> comparator){
        if(start>=end){
            return;
        }
        int pivot = partition(array, start, end, comparator);


        Quicksort(array,start,pivot - 1 ,comparator);
        Quicksort(array,pivot + 1, end ,comparator);

    }

    /**
     *
     * @param array
     * @param start
     * @param end
     * @param comparator
     * @return current pivot position
     * @param <T>
     */
    public static  <T>  int partition(ArrayList<T> array, int start, int end,Comparator<? super T> comparator){

        int pivot = (end+start)/2; // middle
        T pValue =  array.get(pivot);
        swap(array,pivot,end);

        int left = start;
        int right = end - 1;
        while(left < right){
            while(left < right &&  comparator.compare(array.get(left), pValue) <= 0){
                left++;
            }
            while(right > left && comparator.compare(array.get(right),pValue) >= 0 ){
                right--;
            }
            swap(array, left, right);
        }
        if(comparator.compare(array.get(right),pValue)>0) {
            swap(array, right, end);
        }
        else {
            return end;
        }
        return right;
    }

    /**
     *
     * @param size
     * @return sorted list
     */
    //public static void quicksort(ArrayList, Comparator<? super T>){}
    //This method generates and returns an ArrayList of integers 1 to size in ascending order.
    public static ArrayList<Integer> generateBestCase(int size){
        ArrayList<Integer> bestCaseArray = new ArrayList<>();
        for (int i = 1; i <= size; i++) {
            bestCaseArray.add(i);
        }
        return bestCaseArray;
    }
    /**
     *
     * @param size
     * @return random list
     */
    //This method generates and returns an ArrayList of integers 1 to size in permuted order (i,e., randomly ordered).
    public static ArrayList<Integer> generateAverageCase(int size){
        Random rand = new Random();
        ArrayList<Integer> avgCaseArray = new ArrayList<>();
        for (int i = 1; i <= size; i++) {
            avgCaseArray.add(i);
        }
        for (int i = 0; i < size; i++) {
            int j = rand.nextInt(size);
            int temp = avgCaseArray.get(i);
            avgCaseArray.set(i, avgCaseArray.get(j));
            avgCaseArray.set(j, temp);
        }
        return avgCaseArray;
    }

    /**
     *
     * @param size
     * @return a reverse order list
     */
    //This method generates and returns an ArrayList of integers 1 to size in descending order.
    public static ArrayList<Integer> generateWorstCase(int size){
        ArrayList<Integer> worstCaseArray = new ArrayList<>();
        for (int i = 1; i <= size; i++) {
            worstCaseArray.add(i);
        }
        Collections.sort(worstCaseArray, Collections.reverseOrder());
        return worstCaseArray;

    }

}