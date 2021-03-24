package Apartat2;

import Apartat1.BinarySearchTree;

import java.util.Comparator;
import java.util.NoSuchElementException;

public class LinkedBinarySearchTree<K, V> implements BinarySearchTree<K, V>, BinaryTree<LinkedBinarySearchTree.Pair<K, V>> {
    private final Pair<K,V> root;
    private final Comparator<? super K> comparator;
    protected static class Pair<K,V>{
        public final K key;
        public final V value;
        public final Pair<K,V> left;
        public final Pair<K,V> right;
        public Pair(K key,V value){
            this.key=key;
            this.value=value;
            this.left=null;
            this.right=null;
        }
        public Pair(K key,V value,Pair<K,V> left,Pair<K,V> right){
            this.key=key;
            this.value=value;
            this.left=left;
            this.right=right;
        }
        private boolean  has2Childs(){
            return left!=null&&right!=null;
        }
    }
    public LinkedBinarySearchTree(Comparator<? super K> comparator,Pair<K,V> root){
        this.root=root;
        this.comparator=comparator;
    }
    @Override
    public Pair<K, V> root() {
        return this.root;
    }

    @Override
    public LinkedBinarySearchTree<K, V> left() {
        return new LinkedBinarySearchTree<>(comparator,this.root.left);
    }

    @Override
    public LinkedBinarySearchTree<K, V> right() {
        return new LinkedBinarySearchTree<>(comparator,this.root.right);
// ¿?
    }

    @Override
    public boolean isEmpty() {
        return this.root==null;
    }
    private Pair<K,V> containsKeyRec(Pair<K,V> n, K key ){
        int cmp;
        if(n==null)return null;
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return containsKeyRec(n.right,key);
        else if(cmp<0)return containsKeyRec(n.left,key);
        else return n;
    }
    @Override
    public boolean containsKey(K key) {
        if(key==null)throw new NullPointerException();
        if(containsKeyRec(this.root,key)==null)return false;
        return true;
    }
    private Pair<K,V> getPairRec(Pair<K,V> n, K key){
        int cmp;
        if(n==null)throw new NoSuchElementException();
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return getPairRec(n.right,key);
        else if(cmp<0)return getPairRec(n.left,key);
        else return n;
    }
    private Pair<K, V> getPair(K key) {
        return getPairRec(this.root,key);
    }
    @Override
    public V get(K key) {
        return getPairRec(this.root,key).value;
    }
    private Pair<K,V> addRec(Pair<K,V> n, Pair<K,V> ne){
        int cmp;
        if(n==null) return ne;
        cmp=comparator.compare(ne.key,n.key);
        if(cmp>0)return new Pair<K,V>(n.key,n.value,n.left,addRec(n.right,ne));
        else if(cmp<0)return new Pair<K,V>(n.key,n.value,addRec(n.left,ne),n.right);
        else return ne;
    }
    private LinkedBinarySearchTree<K,V> add(Pair<K,V> pair){
        return new LinkedBinarySearchTree<K,V>(this.comparator,addRec(this.root,pair));
    }
    private Pair<K,V> putRec(Pair<K,V> n,K key,V val){
        int cmp;
        if(n==null) return new Pair<K,V>(key,val);
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return new Pair<K,V>(n.key,n.value,n.left,putRec(n.right,key,val));
        else if(cmp<0)return new Pair<K,V>(n.key,n.value,putRec(n.left,key,val),n.right);
        else return new Pair<K,V>(key,val,n.left,n.right);
    }
    @Override
    public BinarySearchTree<K, V> put(K key, V value) {
        return new LinkedBinarySearchTree<K,V>(this.comparator,putRec(this.root,key,value));
    }
    private Pair<K,V> remRec(Pair<K,V> n, K key){
        int cmp;
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return new Pair<K,V>(n.key,n.value,n.left,remRec(n.right,key));
        else if(cmp<0)return new Pair<K,V>(n.key,n.value,remRec(n.left,key),n.right);
        else {
            if(n.right!=null)return n.right;
            else if(n.left!=null)return n.left;
            else return null;
        }
    }
    @Override
    public BinarySearchTree<K, V> remove(K key) {
        if(this.isEmpty())throw new NullPointerException();

        Pair<K,V> n=getPair(key);
        if(n.has2Childs())return new LinkedBinarySearchTree<K,V>(this.comparator,remRec(root,key)).add(n.left);
        return new LinkedBinarySearchTree<K,V>(this.comparator,remRec(root,key));
    }
}