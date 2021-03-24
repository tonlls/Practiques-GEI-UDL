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
        public boolean has2Childs(){
            return left!=null&&right!=null;
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

    private Node<K,V> containsKeyRec(Node<K,V> n,K key ){
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

    private Node<K,V> getNodeRec(Node<K,V> n,K key){
        int cmp;
        if(n==null)throw new NoSuchElementException();
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return getNodeRec(n.right,key);
        else if(cmp<0)return getNodeRec(n.left,key);
        else return n;
    }
    private Node getNode(K key) {
        return getNodeRec(this.root,key);
    }
    @Override
    public V get(K key) {
        if(key==null)throw new NullPointerException();
        return getNodeRec(this.root,key).value;
    }
    private Node<K,V> addRec(Node<K,V> n,Node<K,V> ne){
        int cmp;
        if(n==null) return ne;
        cmp=comparator.compare(ne.key,n.key);
        if(cmp>0)return new Node<K,V>(n.key,n.value,n.left,addRec(n.right,ne));
        else if(cmp<0)return new Node<K,V>(n.key,n.value,addRec(n.left,ne),n.right);
        else return ne;
    }
    private LinkedBinarySearchTree<K,V> add(Node<K,V> node){
        return new LinkedBinarySearchTree<K,V>(this.comparator,addRec(this.root,node));
    }
    private Node<K,V> putRec(Node<K,V> n,K key,V val){
        int cmp;
        if(n==null) return new Node<K,V>(key,val);//hem arribat al final, retornem la creació del nou node
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return new Node<K,V>(n.key,n.value,n.left,putRec(n.right,key,val));//ens movem cap a la dreta
        else if(cmp<0)return new Node<K,V>(n.key,n.value,putRec(n.left,key,val),n.right);//ens movem cap a l'esquerra
        else return new Node<K,V>(key,val,n.left,n.right);//actualitzem el valor, ja que el node ja existeix
    }
    @Override
    public LinkedBinarySearchTree<K, V> put(K key, V value) {
        if(key==null||value==null)throw new NoSuchElementException();

        return new LinkedBinarySearchTree<K,V>(this.comparator,putRec(root,key,value));
    }
    private Node<K,V> remRec(Node<K,V> n,K key){
        int cmp;
        cmp=comparator.compare(key,n.key);
        if(cmp>0)return new Node<K,V>(n.key,n.value,n.left,remRec(n.right,key));//ens movem cap a la dreta
        else if(cmp<0)return new Node<K,V>(n.key,n.value,remRec(n.left,key),n.right);//ens movem cap a l'esquerra
        else { //hem arribat al node que volem eliminar
            if(n.right!=null)return n.right; //retornem el fill de la dreta per tal de suplantar al seu pare
            else if(n.left!=null)return n.left;//retornem el fill de l'esquerra per tal de suplantar al seu pare
            else return null;//no te fills per tant retornem null
        }
    }
    @Override
    public LinkedBinarySearchTree<K, V> remove(K key) {
        if(this.isEmpty())throw new NullPointerException();

        Node<K,V> n=getNode(key);
        if(n.has2Childs())return new LinkedBinarySearchTree<K,V>(this.comparator,remRec(root,key)).add(n.left);
        return new LinkedBinarySearchTree<K,V>(this.comparator,remRec(root,key));
    }
}