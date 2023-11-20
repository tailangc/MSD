package assignment05;

import org.w3c.dom.Node;

import java.util.NoSuchElementException;

public class LinkedListStack<T> implements Stack<T>{

    private SinglyLinkedList<T> list;

    public LinkedListStack(){
        list = new SinglyLinkedList<>();
    }
    /**
     * Removes all of the elements from the stack.
     */
    @Override
    public void clear() {
        list.clear();
    }

    /**
     * @return true if the stack contains no elements; false, otherwise.
     */
    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    /**
     * Returns, but does not remove, the element at the top of the stack.
     *
     * @return the element at the top of the stack
     * @throws NoSuchElementException if the stack is empty
     */
    @Override
    public T peek() throws NoSuchElementException {
        if(list.isEmpty()){
            throw new NoSuchElementException();
        }
        return list.getFirst();
    }

    /**
     * Returns and removes the item at the top of the stack.
     *
     * @return the element at the top of the stack
     * @throws NoSuchElementException if the stack is empty
     */
    @Override
    public T pop() throws NoSuchElementException {
        if(list.isEmpty()){
            throw new NoSuchElementException();
        }
        return list.deleteFirst();
    }

    /**
     * Adds a given element to the stack, putting it at the top of the stack.
     *
     * @param element - the element to be added
     */
    @Override
    public void push(T element) {
        list.insertFirst(element);
    }

    /**
     * @return the number of elements in the stack
     */
    @Override
    public int size() {
        return list.size();
    }
}
