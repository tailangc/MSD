package assignment05;


import java.util.Iterator;
import java.util.NoSuchElementException;

public class SinglyLinkedList<T> implements List<T>{
    private Node<T> head;
    private int size;

    private static class Node<T> {
        T data;
        Node<T> next;

        Node(T data){
            this.data = data;
            this.next = null;
        }
    }

    public SinglyLinkedList(){
        this.head = null;
        this.size = 0;
    }


    /**
     * Inserts an element at the beginning of the list.
     * O(1) for a singly-linked list.
     *
     * @param element - the element to add
     */
    @Override
    public void insertFirst(T element) {
        Node<T> node = new Node<>(element);
        node.next = head;
        head = node;
        size++;
    }

    /**
     * Inserts an element at a specific position in the list.
     * O(N) for a singly-linked list.
     *
     * @param index   - the specified position
     * @param element - the element to add
     * @throws IndexOutOfBoundsException if index is out of range (index < 0 || index > size())
     */
    @Override
    public void insert(int index, T element) throws IndexOutOfBoundsException {
        Node<T> target = head;
        for(int i = 0; i < index - 1; i++){
            target = target.next;
        }

        Node<T> node = new Node<>(element);
        node.next = target.next;
        target.next = node;
        size++;
    }

    /**
     * Gets the first element in the list.
     * O(1) for a singly-linked list.
     *
     * @return the first element in the list
     * @throws NoSuchElementException if the list is empty
     */
    @Override
    public T getFirst() throws NoSuchElementException {
        if (size == 0){
            throw new NoSuchElementException();
        }
        return head.data;
    }

    /**
     * Gets the element at a specific position in the list.
     * O(N) for a singly-linked list.
     *
     * @param index - the specified position
     * @return the element at the position
     * @throws IndexOutOfBoundsException if index is out of range (index < 0 || index >= size())
     */
    @Override
    public T get(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size()){
            throw new IndexOutOfBoundsException();
        }
        Node<T> target = head;
        for (int i = 0; i < index; i++){
            target = target.next;
        }
        return target.data;
    }

    /**
     * Deletes and returns the first element from the list.
     * O(1) for a singly-linked list.
     *
     * @return the first element
     * @throws NoSuchElementException if the list is empty
     */
    @Override
    public T deleteFirst() throws NoSuchElementException {
        if (size == 0){
            throw new NoSuchElementException();
        }
        T data = head.data;
        head = head.next;
        size--;
        return data;
    }

    /**
     * Deletes and returns the element at a specific position in the list.
     * O(N) for a singly-linked list.
     *
     * @param index - the specified position
     * @return the element at the position
     * @throws IndexOutOfBoundsException if index is out of range (index < 0 || index >= size())
     */
    @Override
    public T delete(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index >= size()){
            throw new IndexOutOfBoundsException();
        }
        Node<T> target = head;
        for(int i = 0; i < index - 1; i++){
            target = target.next;
        }
        T data  = target.next.data;
        target.next = target.next.next;
        size--;
        return data;
    }

    /**
     * Determines the index of the first occurrence of the specified element in the list,
     * or -1 if this list does not contain the element.
     * O(N) for a singly-linked list.
     *
     * @param element - the element to search for
     * @return the index of the first occurrence; -1 if the element is not found
     */
    @Override
    public int indexOf(T element) {
        Node<T> node = head;
        for(int i = 0; i < size; i++){
            node = node.next;
            if (node.data == element) {
                return i;
            }
        }
        return -1;
    }

    /**
     * O(1) for a singly-linked list.
     *
     * @return the number of elements in this list
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * O(1) for a singly-linked list.
     *
     * @return true if this collection contains no elements; false, otherwise
     */
    @Override
    public boolean isEmpty() {
        if (size == 0) {
            return true;
        }
        else{
            return false;
            }
    }

    /**
     * Removes all of the elements from this list.
     * O(1) for a singly-linked list.
     */
    @Override
    public void clear() {
        head = null;
    }

    /**
     * Generates an array containing all of the elements in this list in proper sequence
     * (from first element to last element).
     * O(N) for a singly-linked list.
     *
     * @return an array containing all of the elements in this list, in order
     */
    @Override
    public T[] toArray() {
        Node<T> node = head;
        T[] array = (T[]) new Object[size];
        for(int i = 0; i < size; i++){
            node = node.next;
            array[i] = node.data;
        }
        return array;
    }

    /**
     * @return an iterator over the elements in this list in proper sequence (from first
     * element to last element)
     */
    @Override
    public Iterator iterator() {
        return new Iterator() {
            Node<T> current = head;
            Node<T> last = null;
            Node<T> previous = null;
            @Override
            public boolean hasNext() {
                if(current.next != null) {
                    return true;
                }
                else{
                    return false;
                }
            }

            @Override
            public T next() {
                if(!hasNext()) throw new NoSuchElementException();
                T data = current.data;
                previous = (last == head) ? null : previous.next;
                current = current.next;

                return data;
            }

            @Override
            public void remove() {
                if(last == null){
                    throw new IllegalStateException();
                }


            }
        };
    }
}
