package quickSort;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class QuickSortTest {
    public static boolean compare(int[] l1,int []l2){
        int i;
        if(l1.length==l2.length){
            for(i=0;i<l1.length;i++)
                if(l1[i]!=l2[i])break;
            if(i==l1.length)return true;
        }
        return false;
    }
    @Test
    public void test1(){
        int[] ls=new int[]{1,4,6,8,12,34,2};
        int[] ls1=new int[]{1,12,8,6,4,34,2};
        QuickSort.quickSort(ls,0,ls.length);
        QuickSort.quickSortIter(ls1,0,ls.length);
        assertEquals(true,compare(ls1,new int[]{1,2,4,6,8,12,34}));
    }
    @Test
    public void test2(){
        int[] ls2=new int[]{1,4,6,8,12,34,2};
        QuickSort.quickSort2(ls2,0,ls2.length);
        //assertEquals(true,compare(ls2,new int[]{1,2,4,6,8,12,34}));
    }
    @Test
    public void test3(){
        int[] ls1=new int[]{};
        int[] ls2=new int[]{1,2,3};
        int[] ls3=new int[]{109,345,2,145,8,70,4,22,3};
        QuickSort.quickSort2(ls1,0,ls1.length);
        assertEquals(true,compare(ls1,new int[]{}));
        QuickSort.quickSort2(ls2,0,ls2.length);
        assertEquals(true,compare(ls2,new int[]{1,2,3}));
        QuickSort.quickSort2(ls3,0,ls3.length);
        assertEquals(true,compare(ls3,new int[]{2,3,4,8,22,70,109,145,345}));
    }
}
