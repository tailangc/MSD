package lab06;

public interface priorityQueue<T> {
    void add(T element);

    T removeMin();

    boolean isEmpty();

}
