package lab05;

import static org.junit.Assert.*;
import org.junit.Test;

import java.util.Comparator;

public class MedianFinderTest {

    @Test
    public void testFindMedianWithComparable() {
        Integer[] arrayOdd = {3, 1, 2};
        assertEquals(Integer.valueOf(2), MedianFinder.findMedian(arrayOdd));
        Integer[] arrayEven = {4, 1, 3, 2};
        assertEquals(Integer.valueOf(2), MedianFinder.findMedian(arrayEven)); // or 3
    }

    @Test
    public void testFindMedianWithComparator() {
        Integer[] arrayOdd = {3, 1, 2};
        Comparator<Integer> comparator = Integer::compare;
        assertEquals(Integer.valueOf(2), MedianFinder.findMedian(arrayOdd, comparator));
        Integer[] arrayEven = {4, 1, 3, 2};
        assertEquals(Integer.valueOf(2), MedianFinder.findMedian(arrayEven, comparator)); // or 3
    }


    @Test
    public void testFindMedianWithDuplicateValues() {
        Integer[] arrayDuplicates = {5, 2, 5, 1, 7};
        assertEquals(Integer.valueOf(5), MedianFinder.findMedian(arrayDuplicates));
    }

    @Test
    public void testFindMedianWithStrings() {
        String[] strArray = {"apple", "one", "banana", "kiwi", "go"};
        Comparator<String> lengthComparator = Comparator.comparing(String::length);
        assertEquals("kiwi", MedianFinder.findMedian(strArray, lengthComparator));
        assertEquals("go", MedianFinder.findMedian(strArray));

    }
}
