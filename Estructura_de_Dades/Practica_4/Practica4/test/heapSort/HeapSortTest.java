package heapSort;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

public class HeapSortTest {
    @Test
    public void sortTest(){
        ArrayList<Integer> sorted=new ArrayList<Integer>(List.of(  1,3,5,7,9,13,18,19));
        ArrayList<Integer> unsorted=new ArrayList<Integer>(List.of(18,5,9,1,3,7,13,19));
        HeapSort.sort(unsorted);
        assertEquals(sorted,unsorted);
        sorted=new ArrayList<>(List.of(1,2,3));
        unsorted=new ArrayList<>(List.of(1,2,3));
        HeapSort.sort(unsorted);
        assertEquals(sorted,unsorted);
    }
    @Test
    public void binaryHeapTest(){
        HeapSort.BinaryHeap bh=new HeapSort.BinaryHeap(new ArrayList<Integer>(List.of(1,3,5)),new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        });
        int left=HeapSort.BinaryHeap.left(0);
        int right=HeapSort.BinaryHeap.right(0);
        assertEquals(1,left);
        assertEquals(2,right);
        int parentL= HeapSort.BinaryHeap.parent(left);
        int parentR= HeapSort.BinaryHeap.parent(right);
        assertEquals(0,parentL);
        assertEquals(0,parentR);
    }
    @Test
    public void operationTest(){
        Comparator cmp=new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        };
        ArrayList<Integer> sorted=new ArrayList<Integer>(List.of(  1,3,5,7,9,13,18,19));
        ArrayList<Integer> unsorted=new ArrayList<Integer>(List.of(18,5,9,1,3,7,13,19));
        HeapSort.BinaryHeap<Integer> bh=new HeapSort.BinaryHeap<Integer>(unsorted,cmp);
        bh.add(200);
        assertEquals(unsorted.get(0),200);
        Integer el=bh.remove();
        assertEquals(el,200);
        HeapSort.sort(unsorted);
        assertEquals(sorted,unsorted);
    }
}
