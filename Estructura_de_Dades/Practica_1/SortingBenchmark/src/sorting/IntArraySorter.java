package sorting;

/**
 * @author jmgimeno
 */

public class IntArraySorter {

    private final int[] array;

    public IntArraySorter(int[] array) {
        this.array = array;
    }

    public boolean isSorted() {
        for (int i = 0; i < array.length - 1; i++) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }

    public void swap(int i, int j) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    public void insertionSort() {
        // Invariant: The prefix [0, end) is a sorted array
        for (int end = 1; end < array.length; end++) {
            // We insert element at end into this prefix

            // Invariant: arrays sorted in the ranges [0, insert)
            // and [insert, end] and all elements in [0, insert)
            // are lower than or equal to those in [insert+1, end]


            for (int insert = end; insert >= 1; insert--) {
                if (array[insert - 1] > array[insert]) {
                    swap(insert - 1, insert);
                } else {
                    break;
                }
            }
        }
    }

    public void bubbleSort() {
        for (int last = array.length - 1; last >= 1; last--)
            for (int i = 0; i + 1 <= last; i++)
                if (array[i + 1] < array[i])
                    swap(i, i + 1);
    }

    public void selectionSort() {
        for (int i = 0; i < array.length; i++)
            for (int j = i + 1; j < array.length; j++)
                if (array[j] < array[i])
                    swap(i, j);
    }

    public int choosePivotPosition(int left, int right) {
//        return (int) (Math.random() * (right - left) + left);
        return left + (right - left) / 2;
    }

    public int partition(int piv, int l, int r) {
        while(l != r) {
            if (array[l] <= piv)
                l++;
            else if (array[r - 1] > piv)
                r--;
            else {
                swap(l++, --r);
            }
        }
        return l;
    }
    private void quickSort(int left, int right) {
        if (right - left > 1) {
            int pivotPos = choosePivotPosition(left, right);
            int pivotValue = array[pivotPos];
            swap(left, pivotPos);
            int pos = partition(pivotValue, left + 1, right);
            swap(left, pos - 1);
            quickSort(left, pos - 1);
            quickSort(pos, right);
        }
    }

    public void quickSort() {
        quickSort(0,array.length);
    }
}
