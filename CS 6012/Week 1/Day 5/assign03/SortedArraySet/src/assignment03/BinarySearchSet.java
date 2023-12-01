package assignment03;
// student : Tailang Cao
import javax.swing.plaf.IconUIResource;
import java.util.*;

public class BinarySearchSet<E> implements SortedSet<E>, Iterable<E> {
    private E[] data;
    private int capacity;
    private int size;
    private Comparator<? super E> comparator;

    public BinarySearchSet() {
        capacity = 10;
        data = (E[]) new Object[capacity];
        size = 0;
        comparator = null;
    }

    public BinarySearchSet(Comparator<? super E> comparator) {
        capacity = 10;
        data = (E[]) new Object[capacity];
        size = 0;
        this.comparator = comparator;
    }


    /**
     * @return The comparator used to order the elements in this set, or null if
     * this set uses the natural ordering of its elements (i.e., uses
     * Comparable).
     */
    @Override
    public Comparator<? super E> comparator() {
        return comparator;
    }

    /**
     * @return the first (lowest, smallest) element currently in this set
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public E first() throws NoSuchElementException {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        //E firstElement = data[0];
        return data[0];
    }

    /**
     * @return the last (highest, largest) element currently in this set
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public E last() throws NoSuchElementException {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        //E largestElement = data[size - 1];
        return data[size - 1];
    }

    /**
     * Adds the specified element to this set if it is not already present and
     * not set to null.
     *
     * @param element element to be added to this set
     * @return true if this set did not already contain the specified element
     */
    @Override
    public boolean add(E element) {
        if (contains(element)) {
            return false;
        } else {

            if (size == capacity) {
                capacity = capacity * 2;
                E[] newarray = (E[]) new Object[capacity];
                for (int i = 0; i < data.length; i++) {
                    newarray[i] = data[i];
                }
                data = newarray;
            }

            if(isEmpty()){
                data[0] = element;
            }
            else{
                //[2, 4, 6, 8, 10], add(5)
                //binarySearch(5) -> 2
                //[2, 4, 6, 6, 8, 10]
                int index = binarySearch(element);
//                //size = 5
                for(int i = size -1  ; i >= index; --i){
                    data[i + 1] = data[i];
                }
//                //arr[2] = 5
                data[index] = element;
            }
            size++;

        }
        return true;
    }

    /**
     * Adds all of the elements in the specified collection to this set if they
     * are not already present and not set to null.
     *
     * @param elements collection containing elements to be added to this set
     * @return true if this set changed as a result of the call
     */
    @Override
    public boolean addAll(Collection<? extends E> elements) {
        boolean isAdded = false;
        for (E eachElement : elements) {
            if(this.add(eachElement)){
                isAdded = true;
            }
        }
        return isAdded;
    }

    /**
     * Removes all of the elements from this set. The set will be empty after
     * this call returns.
     */
    @Override
    public void clear() {
        capacity = 10;
        data = (E[]) new Object[capacity];
        size = 0;
        comparator = null;
    }

    /**
     * @param element element whose presence in this set is to be tested
     * @return true if this set contains the specified element
     */
    @Override
    public boolean contains(E element) {
//        for (int i=0; i< size; i++){
//            if(((Comparable<E>)data[i]).compareTo(element) == 0){
//                return true;
//            }
//        }
//        return false;
//    }
//        if (element == null) {
//            return false; // 或者抛出异常，取决于您的设计决策
//        }
//        if(binarySearch(element)== -1){
//            return false;
//        }
//        else {
//            return true;
//        }
        int low = 0;
        int high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2; // 防止溢出的计算中点方式
            if(comparator == null) {
                int cmp = ((Comparable<E>) element).compareTo(data[mid]);
                if (cmp > 0) {
                    low = mid + 1;
                } else if (cmp < 0) {
                    high = mid - 1;
                } else {
                    return true; // 找到元素
                }
            }
            else {
                int cmp = comparator.compare(element, data[mid]);
                if (cmp > 0) {
                    low = mid + 1;
                } else if (cmp < 0) {
                    high = mid - 1;
                } else {
                    return true; // 找到元素
                }
            }
        }
        return false; // 没有找到元素
    }

    /**
     * @param elements collection to be checked for containment in this set
     * @return true if this set contains all of the elements of the specified
     * collection
     */
    @Override
    public boolean containsAll(Collection<? extends E> elements) {
        for ( E eachElement : elements ) {
            if (!contains(eachElement)) {
                return false;
            }
        }
        return true;
    }

    /**
     * @return true if this set contains no elements
     */
    @Override
    public boolean isEmpty() {
        if (size == 0) {
            return true;
        }
        return false;
    }

    /**
     * @return an iterator over the elements in this set, where the elements are
     * returned in sorted (ascending) order
     */
    @Override
    public Iterator<E> iterator() {
        Iterator<E> iterator = new Iterator<E>() {
            int index = 0;
            boolean callNext = false;
            @Override
            public boolean hasNext() {
                return size > index ;
            }
            @Override
            public E next() {
                if (!hasNext()) {
                    throw new NoSuchElementException();}
                E result = (E) data[index];
                index++;
                callNext = true;
                return result;
            }
            @Override
            public void remove(){
                if(callNext) {
                    index--;
                    size--;
                    for(int i = index  ; i < size ; i++){
                        data[i] = data[i+1];}
                    callNext = false;
                } else {
                    throw new IllegalStateException();}
            }
        };
        return iterator;
    }

    /**
     * Removes the specified element from this set if it is present.
     *
     * @param element element to be removed from this set, if present
     * @return true if this set contained the specified element
     */
    @Override
    public boolean remove(E element) {
        if (contains(element)) {
            int index = binarySearch(element);
            for(int i = index  ; i < size-1; i++){
                data[i] = data[i+1];
            }
            size = size - 1;
            return true;
        }

        return false;
    }

    /**
     * Removes from this set all of its elements that are contained in the
     * specified collection.
     *
     * @param elements collection containing elements to be removed from this set
     * @return true if this set changed as a result of the call
     */
    @Override
    public boolean removeAll(Collection<? extends E> elements) {
        boolean result = false;
        if(elements != null){
            for(E ele: elements){
                if(remove(ele)){
                    result = true;
                }
            }
        }
        return result;
    }

    /**
     * @return the number of elements in this set
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * @return an array containing all of the elements in this set, in sorted
     * (ascending) order.
     */
    @Override
    public E[] toArray() {
        E[] newArray = (E[]) new Object[size];
        System.arraycopy(data, 0, newArray, 0, size);
        return newArray;

    }

    public int binarySearch(E element ){
        return binarySearch(element,0,size-1,data);
    }
    //[2, 4, 6, 8, 10] -> add(8)
    //element = 8, start= 0, end = 4
    //mid =(0 + 4) /2 = 2
    //data[mid] vs 8
    //element = 8, start= 3, end = 4
    // mid = (3+4) /2 = 3
    //data[3] vs 8
    //retrun 3
    private int binarySearch(E element, int start , int end , E[] array){
        if (start <= end) {
            int mid = (start + end) / 2; // 防止溢出的计算中点方式
            if(comparator == null) {
                int cmp = ((Comparable<E>) element).compareTo(array[mid]);
                if (cmp == 0) {
                    return mid;
                } else if (cmp < 0) {
                    return binarySearch(element, start, mid - 1, array);
                } else {
                    return binarySearch(element, mid + 1, end, array);
                }
            }else{
                int cmp = comparator.compare(element, array[mid]);
                if (cmp == 0) {
                    return mid;
                } else if (cmp < 0) {
                    return binarySearch(element, start, mid - 1, array);
                } else {
                    return binarySearch(element, mid + 1, end, array);
                }
            }

        }
        else if(end < 0){
            return 0;
        }
        else if(start > end) {
            return start;
        }

        return -1;

    }
}