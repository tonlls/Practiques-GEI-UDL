package quickSort;

import factorial.Factorial;
import fibonacci.Fibonacci;
import stack.LinkedStack;
import stack.Stack;

public class QuickSort {
    private enum EntryPoint {
        CALL, RESUME
    }
    private static class Context {
        int f1,f2;
        EntryPoint entryPoint;
        Context(int f1, int f2, EntryPoint entryPoint) {
            this.f1 = f1;
            this.f2 = f2;
            this.entryPoint = entryPoint;
        }
    }
    private static void swap(int[] v, int inf, int i) {
        int a=v[inf];
        v[inf]=v[i];
        v[i]=a;
    }

    public static int partition(int[] v,int pivot,int inf,int sup){
        //0<=left<=inf<=sup<=right<=v.length
        if(inf==sup){
            return inf;
        }else if(v[inf]<=pivot){
            return partition(v,pivot,inf+1,sup);
        }else if(v[sup-1]>pivot){
            return partition(v,pivot,inf,sup-1);
        }else{
            swap(v,inf,sup-1);
            return partition(v,pivot,inf+1,sup-1);
        }
    }
    public static int partition2(int[]v, int pivot, int inf,int sup){
        while(inf!=sup){
            if(v[inf]<=pivot)
                inf++;
            else if(v[sup-1]>pivot)
                sup--;
            else{
                swap(v,inf,sup-1);
                inf++;
                sup--;
            }
        }
        return inf;
    }
    public static void quickSort(int[] v,int left,int right){
        //0<=left<=right<=v.length
        if(right-left>1){
            int pivotPos=choosePivotPosition(v,left,right);
            int pivotValue=v[pivotPos];
            swap(v,left,pivotPos);
            int pos=partition(v,pivotValue,left+1,right);
            swap(v,left,pos-1);
            quickSort(v,left,pos-1);
            quickSort(v,pos,right);
        }
    }
    public static void quickSort2(int[] v,int left,int right){
        //0<=left<=right<=v.length
        if(right-left>1){
            int pivotPos=choosePivotPosition(v,left,right);
            int pivotValue=v[pivotPos];
            swap(v,left,pivotPos);
            int pos=partition2(v,pivotValue,left+1,right);
            swap(v,left,pos-1);
            quickSort(v,left,pos-1);
            quickSort(v,pos,right);
        }
    }
    public static void quickSortIter(int[] v,int left,int right){
        //0<=left<=right<=v.length
        Stack<Context> stack = new LinkedStack<>();
        int pos=0,pivotPos=0,pivotValue=0;
        stack.push(new Context(left, right, EntryPoint.CALL));
        while (!stack.isEmpty()) {
            Context context = stack.top();
            switch (context.entryPoint) {
                case CALL:
                    if(context.f2-context.f1<=1){
                        stack.pop();
                    }else{
                        context.entryPoint = EntryPoint.RESUME;
                        pivotPos=choosePivotPosition(v,context.f1,context.f2);
                        pivotValue=v[pivotPos];
                        swap(v,context.f1,pivotPos);
                        pos=partition(v,pivotValue,context.f1+1,context.f2);
                        swap(v, context.f1, pos-1);
                    }
                    break;
                case RESUME:
                    stack.pop();
                    stack.push(new Context(pos, context.f2, EntryPoint.CALL));
                    stack.push(new Context(context.f1, pos-1, EntryPoint.CALL));
                    break;
            }
        }
    }
    public static int choosePivotPosition(int[]v,int left,int right){
        return left+(right-left)/2;
    }
}
