package assignment06;


import javax.print.attribute.standard.NumberUp;
import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;

public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T>{

    private BinaryNode root;
    private int size;

    private class BinaryNode{
        T data;
        BinaryNode left;
        BinaryNode right;

        public BinaryNode(T data){
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    public BinarySearchTree(){
        this.root = null;
        this.size = 0;
    }
    /**
     * Ensures that this set contains the specified item.
     *
     * @param item - the item whose presence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * the input item was actually inserted); otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean add(T item) {
        if (item == null){
            throw new NullPointerException();
        }
        if(contains(item)){
            return false;
        }
        root = addHelper(root, (T) item);
        size++;
        return true;
    }

    public BinaryNode addHelper(BinaryNode root, T item){
        if(root == null){
            return new BinaryNode(item);
        }
        if (item.compareTo(root.data) < 0) {
            root.left = addHelper(root.left, item);
        } else {
            root.right = addHelper(root.right, item);
        }
        return root;
    }

    /**
     * Ensures that this set contains all items in the specified collection.
     *
     * @param items - the collection of items whose presence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * any item in the input collection was actually inserted); otherwise,
     * returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean addAll(Collection<? extends T> items) {
        boolean indicator = false;
        for (T item : items){
            if(add(item)){
                indicator = true;
            }
        }
        return indicator;
    }


    /**
     * Removes all items from this set. The set will be empty after this method
     * call.
     */
    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    /**
     * Determines if there is an item in this set that is equal to the specified
     * item.
     *
     * @param item - the item sought in this set
     * @return true if there is an item in this set that is equal to the input item;
     * otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean contains(T item) {
        if(item == null){
            throw new NullPointerException();
        }
        return containsHelper(root, (T) item);
    }

    public boolean containsHelper(BinaryNode root, T item){
        if(root == null){
            return false;
        }

        if(item.compareTo(root.data) < 0){
            return containsHelper(root.left, item);
        } else if (item.compareTo(root.data) > 0) {
            return containsHelper(root.right, item);
        }else{
            return true;
        }
    }

    /**
     * Determines if for each item in the specified collection, there is an item in
     * this set that is equal to it.
     *
     * @param items - the collection of items sought in this set
     * @return true if for each item in the specified collection, there is an item
     * in this set that is equal to it; otherwise, returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean containsAll(Collection<? extends T> items){
        for (T item : items){
            if (!contains(item)){
                return false;
            }
        }
        return true;
    }

    /**
     * Returns the first (i.e., smallest) item in this set.
     *
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public T first() throws NoSuchElementException {
        BinaryNode root_ = root;
        if(isEmpty()){
            throw new NoSuchElementException();
        }
        while (root_.left != null){
            root_ = root_.left;
        }
        return root_.data;
    }

    /**
     * Returns true if this set contains no items.
     */
    @Override
    public boolean isEmpty() {
        if(size == 0) {
            return true;
        }
        else{
            return false;
        }
    }

    /**
     * Returns the last (i.e., largest) item in this set.
     *
     * @throws NoSuchElementException if the set is empty
     */
    @Override
    public T last() throws NoSuchElementException {
        BinaryNode root_ = root;
        if(isEmpty()){
            throw new NoSuchElementException();
        }
        while (root_.right != null){
            root_ = root_.right;
        }
        return root_.data;
    }

    /**
     * Ensures that this set does not contain the specified item.
     *
     * @param item - the item whose absence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * the input item was actually removed); otherwise, returns false
     * @throws NullPointerException if the item is null
     */
    @Override
    public boolean remove(T item) {
        if (item == null){
            throw new NullPointerException();
        }
        if(!contains(item)){
            return false;
        }
        root = removeHelper(root, item);
        size--;
        return true;
    }

    public BinaryNode removeHelper(BinaryNode root, T item){
        if(root == null){
            return null;
        }
        if(item.compareTo(root.data) < 0){
            root.left = removeHelper(root.left, item);
        }
        else if(item.compareTo(root.data) > 0){
            root.right = removeHelper(root.right, item);
        }
        else{
            //one child
            if(root.left == null){
                return root.right;
            }else if(root.right == null){
                return root.left;
            }

            //two children
            root.data = findMin(root.right).data;
            root.right = removeHelper(root.right, root.data);
        }
        return root;
    }

    private BinaryNode findMin(BinaryNode node){
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }

    /**
     * Ensures that this set does not contain any of the items in the specified
     * collection.
     *
     * @param items - the collection of items whose absence is ensured in this set
     * @return true if this set changed as a result of this method call (that is, if
     * any item in the input collection was actually removed); otherwise,
     * returns false
     * @throws NullPointerException if any of the items is null
     */
    @Override
    public boolean removeAll(Collection<? extends T> items) {
        boolean removed = false;
        for(T item : items){
            if(item == null){
                throw new NullPointerException();
            }
            if(remove(item)){
                removed = true;
            }
        }
        return removed;
    }

    /**
     * Returns the number of items in this set.
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * Returns an ArrayList containing all of the items in this set, in sorted
     * order.
     */
    @Override
    public ArrayList<T> toArrayList() {
        ArrayList<T> list = new ArrayList<>();
        inOrderTraversal(root, list);
        return list;
    }

    private void inOrderTraversal(BinaryNode root, ArrayList<T> list) {
        if (root != null) {
            inOrderTraversal(root.left, list);
            list.add(root.data);
            inOrderTraversal(root.right, list);
        }
    }
}
