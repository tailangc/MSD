package assignment03;
// student : Tailang Cao

import org.junit.Assert;
import org.junit.jupiter.api.Test;

import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

class BinarySearchSetTest {
    ArrayList<String> cars = new ArrayList<>();
    BinarySearchSet test  = new BinarySearchSet();

    @Test
    public void BinarySearchAddTest() {
        BinarySearchSet<Integer> searchSet = new BinarySearchSet<>();
        //test if is empty
        Assert.assertEquals(true, searchSet.isEmpty());
        searchSet.add(1);
        searchSet.add(2);
        searchSet.add(3);
        searchSet.add(4);
        searchSet.add(5);
        searchSet.add(6);
        searchSet.add(8);
        searchSet.add(9);
        searchSet.add(4);
        searchSet.add(3);
        searchSet.add(7);
        searchSet.add(-1);
        assertEquals(searchSet.first(), -1);

        searchSet.remove(4);
        Assert.assertEquals(false, searchSet.contains(4));
        //test the first number
        Integer firstElement = searchSet.first();
        Assert.assertEquals(Integer.valueOf(-1), firstElement);
        //test the last number
        Integer lastElement = searchSet.last();
        Assert.assertEquals(Integer.valueOf(9), lastElement);
        //test the size
        Assert.assertEquals(9, searchSet.size());

        System.out.println("Done");
    }
    @Test
    void first() {
        test.add("Hello");
        test.add("Apple");
        assertSame("Apple", test.first());
        System.out.println(test.first());
    }
    @Test
    void last() {
        test.add(10);
        test.add(1);
        test.add(2);
        assertSame(test.last(), 10);
        System.out.println(test.last());
    }
    @Test
    public void addAllTest() {

        BinarySearchSet<Integer> searchSet = new BinarySearchSet<>();
        searchSet.add(1);
        searchSet.add(2);
        searchSet.add(3);

        ArrayList<Integer> t = new ArrayList<>();
        t.add(7);
        t.add(9);
        t.add(1);
        ArrayList<Integer> t2 = new ArrayList<>();
        t2.add(0);
        t2.add(8);
        t2.add(4);
        t2.add(6);
        t2.add(3);

        searchSet.addAll(t);
        searchSet.addAll(t2);
        assertSame(searchSet.last(), 9);
        assertSame(searchSet.first(), 0);
        searchSet.comparator();
        Iterator it = searchSet.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }
    @Test
    void contains() {
        test.add("Hello");
        assertTrue(test.contains("Hello"));
    }
    @Test
    void containsAll() {
        test.add("Honda");
        test.add("volvo");
        assertTrue(test.containsAll(cars));
        Iterator it = test.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }
    @Test
    void clear() {
        test.add("Something");
        test.add("is");
        test.add("going on");
        test.clear();
//       assertEquals(test.first(),null);
        assertThrows(NoSuchElementException.class, () -> { test.first();});
    }
    @Test
    void iterator() {
        test.add("one");
        test.add("two");
        test.add("three");
        var testI = test.iterator();

        assertSame("one", testI.next());
        testI.remove();
        assertSame( 2, test.size());
        for(Object s: test){
            System.out.println(s);
        }
        assertSame( "three", test.first());
        assertSame( "two", test.last());
        assertSame("three", testI.next());
        testI.remove();
        assertSame("two", testI.next());
        testI.remove();
        assertThrows(IllegalStateException.class, () -> { testI.remove();});
        assertThrows(NoSuchElementException.class, () -> {  testI.next();});

    }
    @Test
    void removeAll() {
        test.add(1);
        test.add(2);
        test.add(3);
        test.add(4);
        ArrayList<Integer> t = new ArrayList<>();
        t.add(1);
        t.add(3);
        t.add(5);
        t.add(7);
        t.add(9);
        ArrayList<Integer> t2 = new ArrayList<>();
        t2.add(2);
        t2.add(8);

        test.removeAll(t);
        test.removeAll(t2);
        assertEquals(test.size(), 1);
        assertEquals(test.first(), 4);
        assertEquals(test.last(), 4);
        System.out.println("Remove all pass");
    }
    @Test
    public void toArrayTest() {
        BinarySearchSet<Integer> set = new BinarySearchSet<>();
        set.add(5);
        set.add(3);
        set.add(8);
        set.add(1);
//        for(int i : set){
//            System.out.println(i);
//        }
        Object[] expected = {1, 3, 5, 8};
        Object[] result = set.toArray();

        Arrays.equals(expected, result);
    }


    @Test
    public void libraryBookTest(){
        class reverseComp implements Comparator<Integer> {
            public int compare(Integer lhs,
                               Integer rhs) {
                return rhs - lhs;
            }
        }
        BinarySearchSet<Integer> reverse = new BinarySearchSet<>(new reverseComp());
        reverse.add(1);
        reverse.add(3);
        reverse.add(4);
        reverse.add(9);
        reverse.add(10);

        assertEquals(reverse.first(), 10);
        assertEquals(reverse.last(), 1);



    }
}