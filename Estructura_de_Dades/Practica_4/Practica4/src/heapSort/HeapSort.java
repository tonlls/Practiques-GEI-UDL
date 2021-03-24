package heapSort;

import java.util.ArrayList;
import java.util.Comparator;

public class HeapSort {
    static class BinaryHeap<E> {
        private final ArrayList<E> elements;
        private final Comparator<? super E> comparator;
        int heapSize = 0;
        BinaryHeap(ArrayList<E> ele, Comparator<? super E> comparator) {
            this.elements = ele;
            this.comparator = comparator;
            for(int i=0;i<elements.size();i++){
                heapifyUp(i);
                heapSize++;
            }
        }
        static int parent(int index) {
            return (index-1)/2;
        }
        static int left(int index) {
            return 2*index+1;
        }
        static int right(int index) {
            return 2*index+2;
        }
        boolean hasLeft(int index) {
            return  left(index)<heapSize;
        }
        boolean hasRight(int index) {
            return  right(index)<heapSize;
        }
        boolean hasParent(int index) {
            return  index!=0&&parent(index)<heapSize;
        }
        private void swap(int p1, int p2)
        {
            E tmp=this.elements.set(p1,this.elements.get(p2));
            this.elements.set(p2,tmp);
        }
        void heapifyDown(int index){
            int swap,left,right;
            while (index < heapSize) {
                left = left(index);
                right = right(index);
                if(left>=heapSize-1&&right>=heapSize-1)
                    break;
                swap = (comparator.compare(elements.get(left), elements.get(right)) > 0 ? left:right);
                if (comparator.compare(elements.get(index), elements.get(swap)) < 0)
                    swap(index,swap);
                else
                    break;
                index = swap;
            }
        }
        private void heapifyUp(int pos){
            E elem=this.elements.get(pos);
            while(pos>0&&this.comparator.compare(elem,this.elements.get(parent(pos)))>0) {
                swap(pos,parent(pos));
                pos=parent(pos);
            }
        }

        public void add(E elem) {
            this.elements.add(elem);
            this.heapifyUp(this.heapSize++);
        }
        public E remove() {
            E el=this.elements.get(0);
            this.elements.set(0,elements.get(heapSize-1));
            this.elements.remove(--heapSize);
            this.heapifyDown(0);
            return el;
        }
    }
    public static <E> void sort(ArrayList<E> list,Comparator<? super E> cmp){
        BinaryHeap bh=new BinaryHeap(list,cmp);
        for(int i=list.size()-1;i>0;i--){
            list.add(i,(E)bh.remove());
        }
    }

    public static <E extends Comparable<? super E>> void sort(ArrayList<E> list) {
        sort(list, new Comparator<E>() {
            @Override
             public int compare(E o1, E o2) {
                return o1.compareTo(o2);
            }
        });
    }
}