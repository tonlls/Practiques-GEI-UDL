
package sorting;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 *
 * @author jmgimeno
 */
public class IsSortedTest {
    
    private IntArraySorter sorting;
    
    @Test
    public void empty() {
        int[] array = new int[0];
        sorting = new IntArraySorter(array);
        assertTrue(sorting.isSorted());
    }

    @Test
    public void singleton() {
        int[] array = new int[] { 42 };
        sorting = new IntArraySorter(array);
        assertTrue(sorting.isSorted());
    }
    
    @Test
    public void sortedPair() {
        int[] array = new int[] { 21, 42 };
        sorting = new IntArraySorter(array);
        assertTrue(sorting.isSorted());
    }
    
    @Test
    public void unsortedPair() {
        int[] array = new int[] { 42, 21 };
        sorting = new IntArraySorter(array);
        assertFalse(sorting.isSorted());
    }
    
    @Test
    public void fibonacci() {
        int[] array = new int[] { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
        sorting = new IntArraySorter(array);
        assertTrue(sorting.isSorted());
    }
    
    @Test
    public void reverseFibonacci() {
        int[] array = new int[] { 21, 13, 8, 5, 3, 2, 1, 1, 0 };
        sorting = new IntArraySorter(array);
        assertFalse(sorting.isSorted());
    }
    
    @Test
    public void unsorted() {
        int[] array = new int[] { 12, 7, 21, 34, 3, 8, 21, 17 };
        sorting = new IntArraySorter(array);
        assertFalse(sorting.isSorted());
    }
    
}
