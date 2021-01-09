package Apartat1;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.NoSuchElementException;

public class LinkedBinarySearchTree<K, V> implements BinarySearchTree<K, V> {
    private final Node<K, V> root;
    private final Comparator<? super K> comparator;
    private static class Node<K, V> {
        private final K key;
        private final V value;
        private final Node<K, V> left;
        private final Node<K, V> right;

        public Node(K key,V val){
            this.key=key;
            this.value=val;
            this.right=null;
            this.left=null;
        }
        public Node(K key,V val,Node<K,V> left,Node<K,V> right) {
            this.key = key;
            this.value = val;
            this.right = right;
            this.left = left;
        }
    }
    public LinkedBinarySearchTree(Comparator<? super K> comparator) {
        this.root=null;
        this.comparator=comparator;
    }
    private LinkedBinarySearchTree(Comparator<? super K> comparator,Node<K, V> root) {
        this.root=root;
        this.comparator=comparator;
    }
    @Override
    public boolean isEmpty() {
        return root==null;
    }
    @Override
    public boolean containsKey(K key) {
        if(key==null)throw new NullPointerException();
        Node actual=this.root;
        int cmp=this.comparator.compare(key,(K)actual.key);
        while(cmp!=0){
            if(cmp<0)actual=this.root.left;
            else if(cmp>0)actual=this.root.right;
            if(actual==null)return false;
            cmp=this.comparator.compare(key,(K)actual.key);
        }
        return true;
    }
    @Override
    public V get(K key) {
        if(key==null)throw new NullPointerException();
        Node actual=this.root;
        int cmp=this.comparator.compare(key,(K)actual.key);
        while(cmp!=0){
            if(cmp<0)actual=this.root.left;
            else if(cmp>0)actual=this.root.right;
            if(actual==null)throw new NoSuchElementException();
            cmp=this.comparator.compare(key,(K)actual.key);
        }
        return (V)actual.value;
    }
    private Node getNode(K key) {
        if(key==null)throw new NullPointerException();
        Node actual=this.root;
        int cmp=this.comparator.compare(key,(K)actual.key);
        while(cmp!=0){
            if(cmp<0)actual=this.root.left;
            else if(cmp>0)actual=this.root.right;
            if(actual==null)throw new NoSuchElementException();
            cmp=this.comparator.compare(key,(K)actual.key);
        }
        return actual;
    }
    private static Node copy(Node n){
        return new Node(n.key,n.value);
    }
    private LinkedBinarySearchTree<K,V> modifyValue(K key,V value){
        return null;
    }
    @Override
    public LinkedBinarySearchTree<K, V> put(K key, V value) {
        if(containsKey(key))
            return modifyValue(key,value);

        List<Node> toModify=new ArrayList<Node>();
        Node actual=this.root;
        int cmp=this.comparator.compare(key,(K)actual.key);
        while(cmp!=0){
            toModify.add(actual);
            if(cmp<0)actual=this.root.left;
            else if(cmp>0)actual=this.root.right;
            if(actual==null)throw new NoSuchElementException();
            cmp=this.comparator.compare(key,(K)actual.key);
        }
        toModify.add(new Node(key,value));
        int i=toModify.size()-1;
        Node next,tmp;
        next=toModify.get(i--);
        do{
            actual=toModify.get(i--);
            if(comparator.compare((K)next.key,(K)actual.key)>0)tmp=new Node(actual.key,actual.value,actual.left,next);
            else tmp=new Node(actual.key,actual.value,next,actual.right);
            next=tmp;
        }while(i>=0);

        return new LinkedBinarySearchTree<K,V>(this.comparator,next);
    }
    @Override
    public LinkedBinarySearchTree<K, V> remove(K key) {
        return null;
    }
}