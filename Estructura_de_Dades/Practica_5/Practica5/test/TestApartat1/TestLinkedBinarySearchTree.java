import Apartat1.LinkedBinarySearchTree;
import org.junit.jupiter.api.Test;

import java.util.Comparator;
import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TestLinkedBinarySearchTree {
    public class IntComparator implements Comparator<Integer>{

        @Override
        public int compare(Integer o1, Integer o2) {
            return Integer.compare(o1,o2);
        }
    }
    IntComparator cmp=new IntComparator();
    @Test
    public void testPut(){
        LinkedBinarySearchTree<Integer,Integer> nt,tree=new LinkedBinarySearchTree<>(cmp);
        assertTrue(tree.isEmpty()==true);
        tree=tree.put(2,2);
        assertTrue(tree.containsKey(2)==true);
        tree=tree.put(100,100);
        assertTrue(tree.containsKey(100)==true);
        tree=tree.put(2,20);
        assertTrue(tree.get(2)==20);
        nt=tree;
        assertThrows(NoSuchElementException.class,() ->{nt.put(null,6);});
        assertThrows(NoSuchElementException.class,() ->{nt.get(3);});

    }
    @Test
    public void testRemove(){
        LinkedBinarySearchTree<Integer,Integer> nt,tree=new LinkedBinarySearchTree<>(cmp);
        tree=tree.put(2,2);
        tree=tree.remove(2);
        assertTrue(tree.isEmpty()==true);
        ;
    }
    @Test
    public void Test1(){
        LinkedBinarySearchTree tree=new LinkedBinarySearchTree(new Comparator() {
            @Override
            public int compare(Object o1, Object o2) {
                return Integer.compare((int)o1,(int)o2);
            }
        });
        LinkedBinarySearchTree t=tree.put(10,100).put(6,60).put(5,50).put(7,70).put(20,200).put(15,150).put(12,120).put(16,60).put(23,230).put(22,220).put(24,240);
        LinkedBinarySearchTree tt=t.remove(20);
    }
}
