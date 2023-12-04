package lab06;

import java.util.TreeSet;

public class TreeSet <T extends Comparable<T>> implements priorityQueue<T>{

    private TreeSet<T> treeset;
    public TreeSet(){
        treeset=new TreeSet<>();
    }
    /**
     * @param element
     */
    @Override
    public void add(T element) {
        treeset.add(element);
    }
    /**
     * @return
     */
    @Override
    public T removeMin() {
        return treeset.pollFirst();
    }

    /**
     * @return
     */
    @Override
    public boolean isEmpty() {
        return treeset.isEmpty();
    }


}
