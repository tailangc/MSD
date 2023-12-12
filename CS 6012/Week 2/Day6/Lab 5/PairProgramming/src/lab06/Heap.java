package lab06;

import java.util.ArrayList;

public class Heap<T extends Comparable<T>> implements priorityQueue<T> {

    private ArrayList<T> heap;

    public Heap() {
        heap = new ArrayList<>();
    }

    public Heap(ArrayList<T> unorderedList) {
        heap = new ArrayList<>(unorderedList);
        buildHeap();
    }

    @Override
    public void add(T element) {
        heap.add(element);
        percolateUp(heap.size() - 1);
    }

    @Override
    public T removeMin() {
        if (isEmpty()) {
            throw new IllegalStateException("PriorityQueue is empty");
        }

        T min = heap.get(0);
        int lastIdx = heap.size() - 1;
        heap.set(0, heap.get(lastIdx));
        heap.remove(lastIdx);
        percolateDown(0);

        return min;
    }

    @Override
    public boolean isEmpty() {
        return heap.isEmpty();
    }

    private void percolateUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap.get(index).compareTo(heap.get(parentIndex)) < 0) {
                swap(index, parentIndex);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    private void percolateDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap.get(leftChild).compareTo(heap.get(smallest)) < 0) {
            smallest = leftChild;
        }

        if (rightChild < heap.size() && heap.get(rightChild).compareTo(heap.get(smallest)) < 0) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swap(index, smallest);
            percolateDown(smallest);
        }
    }

    private void buildHeap() {
        int startIndex = (heap.size() / 2) - 1;
        for (int i = startIndex; i >= 0; i--) {
            percolateDown(i);
        }
    }

    private void swap(int i, int j) {
        T temp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, temp);
    }
}
