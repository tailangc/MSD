package assignment07;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

class ChainingHashTableTest {

    private ChainingHashTable hashTable;

    @BeforeEach
    void setUp() {
        HashFunctor hashFunctor = new GoodHashFunctor();
        hashTable = new ChainingHashTable(10, hashFunctor);
    }

    @Test
    void testAdd() {
        assertTrue(hashTable.add("apple"));
        assertFalse(hashTable.add("apple")); // Duplicate, should return false
        assertTrue(hashTable.contains("apple"));
    }

    @Test
    void testAddAll() {
        Set<String> itemsToAdd = new HashSet<>(Arrays.asList("kiwi", "pear"));
        assertTrue(hashTable.addAll(itemsToAdd));
        assertTrue(hashTable.contains("kiwi"));
        assertTrue(hashTable.contains("pear"));
    }

    @Test
    void testClear() {
        hashTable.add("apple");
        assertFalse(hashTable.isEmpty());
        hashTable.clear();
        assertTrue(hashTable.isEmpty());
    }

    @Test
    void testContains() {
        assertFalse(hashTable.contains("watermelon"));
        hashTable.add("watermelon");
        assertTrue(hashTable.contains("watermelon"));
    }

    @Test
    void testContainsAll() {
        hashTable.add("apple");
        hashTable.add("banana");
        Set<String> itemsToCheck = new HashSet<>(Arrays.asList("apple", "banana"));
        assertTrue(hashTable.containsAll(itemsToCheck));
    }

    @Test
    void testIsEmpty() {
        assertTrue(hashTable.isEmpty());
        hashTable.add("apple");
        assertFalse(hashTable.isEmpty());
    }

    @Test
    void testRemove() {
        hashTable.add("banana");
        assertTrue(hashTable.contains("banana"));
        assertTrue(hashTable.remove("banana"));
        assertFalse(hashTable.contains("banana"));
    }

    @Test
    void testRemoveAll() {
        hashTable.add("apple");
        hashTable.add("banana");
        Set<String> itemsToRemove = new HashSet<>(Arrays.asList("banana", "orange"));
        assertTrue(hashTable.removeAll(itemsToRemove));
        assertFalse(hashTable.contains("banana"));
        assertFalse(hashTable.contains("orange"));
    }

    @Test
    void testSize() {
        assertEquals(0, hashTable.size());
        hashTable.add("kiwi");
        assertEquals(1, hashTable.size());
    }
}