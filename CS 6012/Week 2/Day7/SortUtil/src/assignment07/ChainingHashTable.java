package assignment07;

import javax.swing.*;
import java.util.Collection;
import java.util.LinkedList;

public class ChainingHashTable implements Set<String>{

    private LinkedList<String>[] storage;
    private HashFunctor functor_;
    public int collision_;

    public ChainingHashTable(int capacity, HashFunctor functor){
        storage = (LinkedList<String>[]) new LinkedList[capacity];
        functor_ = functor;
        collision_ = 0;

        for (int i = 0; i < capacity; i++) {
            storage[i] = new LinkedList<>();
        }

    }

//    private LinkedList<String> getChain(int index) {
//        if (storage[index] == null) {
//            storage[index] = new LinkedList<>();
//        }
//        return storage[index];
//    }


    public int getCollision(){
        return collision_;
    }

    /**
     * Ensures that this set contains the specified item.
     *
     * @param item - the item whose presence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * the input item was actually inserted); otherwise, returns false
     */



    @Override
    public boolean add(String item) {
        int index = Math.abs(functor_.hash(item) % storage.length);
        if(!storage[index].isEmpty()) {
            collision_++;
        }
        if (!storage[index].contains(item)) {
            storage[index].add(item);
            return true;
        }
        return false;
    }

    /**
     * Ensures that this set contains all items in the specified collection.
     *
     * @param items - the collection of items whose presence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * any item in the input collection was actually inserted); otherwise,
     * returns false
     */
    @Override
    public boolean addAll(Collection<? extends String> items) {
        boolean changed = false;
        for (String item : items) {
            if (add(item)) {
                changed = true;
            }
        }
        return changed;
    }

    /**
     * Removes all items from this set. The set will be empty after this method
     * call.
     */
    @Override
    public void clear() {
        for (LinkedList<String> list : storage) {
            list.clear();
        }
        collision_ = 0;
    }

    /**
     * Determines if there is an item in this set that is equal to the specified
     * item.
     *
     * @param item - the item sought in this set
     * @return true if there is an item in this set that is equal to the input item;
     * otherwise, returns false
     */
    @Override
    public boolean contains(String item) {
        int index = Math.abs(functor_.hash(item) % storage.length);
        return storage[index].contains(item);
    }

    /**
     * Determines if for each item in the specified collection, there is an item in
     * this set that is equal to it.
     *
     * @param items - the collection of items sought in this set
     * @return true if for each item in the specified collection, there is an item
     * in this set that is equal to it; otherwise, returns false
     */
    @Override
    public boolean containsAll(Collection<? extends String> items) {
        for (String item : items) {
            if (!contains(item)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns true if this set contains no items.
     */
    @Override
    public boolean isEmpty() {
        for(LinkedList<String> list : storage){
            if (!list.isEmpty()){
                return false;
            }
        }
        return true;
    }

    /**
     * Ensures that this set does not contain the specified item.
     *
     * @param item - the item whose absence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * the input item was actually removed); otherwise, returns false
     */
    @Override
    public boolean remove(String item) {
        int index = Math.abs(functor_.hash(item) % storage.length);
        return storage[index].remove(item);
    }

    /**
     * Ensures that this set does not contain any of the items in the specified
     * collection.
     *
     * @param items - the collection of items whose absence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * any item in the input collection was actually removed); otherwise,
     * returns false
     */
    @Override
    public boolean removeAll(Collection<? extends String> items) {
        boolean changed = false;
        for (String item : items) {
            if (remove(item)) {
                changed = true;
            }
        }
        return changed;
    }

    /**
     * Returns the number of items in this set.
     */
    @Override
    public int size() {
        int size = 0;
        for (LinkedList<String> list : storage) {
            size += list.size();
        }
        return size;
    }
}
