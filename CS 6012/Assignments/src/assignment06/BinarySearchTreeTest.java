package assignment06;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class BinarySearchTreeTest {

    private BinarySearchTree<Integer> binarySearchTree;

    @BeforeEach
    void setUp() {
        binarySearchTree = new BinarySearchTree<>();
    }

    @Test
    void testAdd() {
        assertTrue(binarySearchTree.add(5));
        assertTrue(binarySearchTree.add(3));
        assertTrue(binarySearchTree.add(7));
        assertFalse(binarySearchTree.add(5)); // Duplicate, should return false

        assertTrue(binarySearchTree.contains(5));
        assertTrue(binarySearchTree.contains(3));
        assertTrue(binarySearchTree.contains(7));
        assertFalse(binarySearchTree.contains(10));
    }

    @Test
    void testAddAll() {
        List<Integer> numbers = Arrays.asList(5, 3, 7, 1, 4);

        assertTrue(binarySearchTree.addAll(numbers));
        assertFalse(binarySearchTree.addAll(numbers)); // No change, should return false

        assertTrue(binarySearchTree.containsAll(numbers));
        assertFalse(binarySearchTree.contains(10));
    }

    @Test
    void testRemove() {
        binarySearchTree.add(5);
        binarySearchTree.add(3);
        binarySearchTree.add(7);

        assertTrue(binarySearchTree.remove(5));
        assertFalse(binarySearchTree.remove(5)); // Already removed, should return false

        assertFalse(binarySearchTree.contains(5));
        assertTrue(binarySearchTree.contains(3));
        assertTrue(binarySearchTree.contains(7));
    }

    @Test
    void testRemoveAll() {
        List<Integer> numbers = Arrays.asList(5, 3, 7, 1, 4);

        binarySearchTree.addAll(numbers);

        List<Integer> removedNumbers = Arrays.asList(5, 1);

        assertTrue(binarySearchTree.removeAll(removedNumbers));
        assertFalse(binarySearchTree.removeAll(removedNumbers)); // No change, should return false

        assertFalse(binarySearchTree.contains(5));
        assertFalse(binarySearchTree.contains(1));
        assertTrue(binarySearchTree.containsAll(Arrays.asList(3, 7, 4)));
    }

    @Test
    void testClear() {
        binarySearchTree.add(5);
        binarySearchTree.add(3);
        binarySearchTree.add(7);

        assertFalse(binarySearchTree.isEmpty());

        binarySearchTree.clear();

        assertTrue(binarySearchTree.isEmpty());
    }

    @Test
    void testSize() {
        assertEquals(0, binarySearchTree.size());

        binarySearchTree.add(5);
        binarySearchTree.add(3);
        binarySearchTree.add(7);

        assertEquals(3, binarySearchTree.size());

        binarySearchTree.remove(5);

        assertEquals(2, binarySearchTree.size());

        binarySearchTree.clear();

        assertEquals(0, binarySearchTree.size());
    }

    @Test
    void testFirst() {
        binarySearchTree.add(5);
        binarySearchTree.add(3);
        binarySearchTree.add(7);

        assertEquals(3, binarySearchTree.first());
    }

    @Test
    void testLast() {
        binarySearchTree.add(5);
        binarySearchTree.add(3);
        binarySearchTree.add(7);

        assertEquals(7, binarySearchTree.last());
    }

    @Test
    void testToArrayList() {
        List<Integer> numbers = Arrays.asList(5, 3, 7, 1, 4);

        binarySearchTree.addAll(numbers);

        List<Integer> sortedList = binarySearchTree.toArrayList();

        assertEquals(Arrays.asList(1, 3, 4, 5, 7), sortedList);
    }
}
