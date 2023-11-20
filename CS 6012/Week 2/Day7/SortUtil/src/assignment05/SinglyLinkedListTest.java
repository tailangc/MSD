package assignment05;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.*;

class SinglyLinkedListTest {

    @Test
    void insertFirst() {
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        list.insertFirst(0);
        Assertions.assertEquals(0, list.getFirst());
        list.insert(0, -1);
        list.deleteFirst();
        Assertions.assertEquals(0, list.getFirst());
    }

    @Test
    void insert(){
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        list.insertFirst(0);

    }

    @Test
    void testIndexOf(){
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        list.insert(0, 1);
        list.insert(1, 2);

        assertEquals(list.indexOf(1), 0);
        assertEquals(list.indexOf(2), 1);
    }

    @Test
    void testToArray() {
        SinglyLinkedList<Integer> list = new SinglyLinkedList<>();
        list.insert(0, 1);
        list.insert(1, 2);
        list.insert(2, 3);

        Object[] arr = list.toArray();
        Assertions.assertEquals(1, arr[0]);
        Assertions.assertEquals(2, arr[1]);
        Assertions.assertEquals(3, arr[2]);
    }

    @org.junit.jupiter.api.Test
    void iterator() {
        SinglyLinkedList<Integer> intList = new SinglyLinkedList<>();
        intList.insertFirst(1);
        intList.insertFirst(2);
        intList.insertFirst(3);


        Iterator<Integer> iterator = intList.iterator();
        Assertions.assertTrue(iterator.hasNext());
        Assertions.assertEquals(3, iterator.next());
        Assertions.assertTrue(iterator.hasNext());
        Assertions.assertEquals(2, iterator.next());
        iterator.remove();

        assertEquals(1, intList.get(1));
        assertEquals(1, iterator.next());
        assertFalse(iterator.hasNext());

    }

}