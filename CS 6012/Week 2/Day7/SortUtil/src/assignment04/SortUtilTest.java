package assignment04;
//Partner : Yuyao Tu



import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

class SortUtilTest {
    ArrayList<Integer> TESTList = new ArrayList<>();
    ArrayList<Integer> EXPECTEDList = new ArrayList<>();

    Comparator<Integer> naturalOrderComparator = Comparator.naturalOrder();

    @Test
    void insertionSortTest(){
        Integer[] testlist = new Integer[]{5,2,8,1,3};
        TESTList = new ArrayList<>(List.of(testlist));

        Integer[] expected = new Integer[]{1,2,3,5,8};
        EXPECTEDList = new ArrayList<>(List.of(expected));

        SortUtil.insertionSort(TESTList,naturalOrderComparator);

        Assertions.assertEquals(EXPECTEDList, TESTList);


    }


    @Test
    void mergesortTest() {
//        Integer[] testlist = new Integer[]{5,2,8,1,3};
//        TESTList = new ArrayList<>(List.of(testlist));
//
//        Integer[] expected = new Integer[]{1,2,3,5,8};
//        EXPECTEDList = new ArrayList<>(List.of(expected));
//
//        SortUtil.mergesort(TESTList, naturalOrderComparator);

        String[] testlist = new String[]{"ben", "terry", "spencer"};
        ArrayList<String> TESTList = new ArrayList<>(Arrays.asList(testlist));

        // Create an expected sorted smallList
        String[] expected = new String[]{"ben", "spencer", "terry"};
        ArrayList<String> EXPECTEDList = new ArrayList<>(Arrays.asList(expected));

        SortUtil.mergesort(TESTList, Comparator.naturalOrder());

        Assertions.assertEquals(EXPECTEDList, TESTList);

        //CASE: LARGE (AVG CASE) LIST
        ArrayList<Integer> myList = SortUtil.generateAverageCase(20);
        System.out.println(myList);
        SortUtil.mergesort(myList, naturalOrderComparator);
        System.out.println(myList);

        // Assert that the list is sorted
        for (int i = 0; i < myList.size() - 1; i++) {
            assertTrue(naturalOrderComparator.compare(myList.get(i), myList.get(i + 1)) <= 0);
        }
    }

    @Test
    void quicksortTest() {
//        Integer[] testlist = new Integer[]{5,2,8,1,3};
//        TESTList = new ArrayList<>(List.of(testlist));
//
//        // Create an expected sorted smallList
//        Integer[] expected = new Integer[]{1,2,3,5,8};
//        EXPECTEDList = new ArrayList<>(List.of(expected));

        String[] testlist = new String[]{"ben", "terry", "spencer"};
        ArrayList<String> TESTList = new ArrayList<>(Arrays.asList(testlist));

        // Create an expected sorted smallList
        String[] expected = new String[]{"ben", "spencer", "terry"};
        ArrayList<String> EXPECTEDList = new ArrayList<>(Arrays.asList(expected));

        SortUtil.quicksort(TESTList, Comparator.naturalOrder());

        Assertions.assertEquals(EXPECTEDList, TESTList);
    }

    @Test
    void generateWorstCaseTest() {
        ArrayList<Integer> TESTList = SortUtil.generateWorstCase(10);

        Integer[] expected = new Integer[]{10,9,8,7,6,5,4,3,2,1};
        EXPECTEDList = new ArrayList<>(List.of(expected));

        Assertions.assertEquals(EXPECTEDList, TESTList);
    }

    @Test
    void generateBestCaseTest() {
        ArrayList<Integer> TESTList = SortUtil.generateBestCase(10);

        Integer[] expected = new Integer[]{1,2,3,4,5,6,7,8,9,10};
        EXPECTEDList = new ArrayList<>(List.of(expected));

        Assertions.assertEquals(EXPECTEDList, TESTList);
    }

}