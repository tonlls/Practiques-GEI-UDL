package stack;

import java.util.NoSuchElementException;

public class LinkedStack<E> implements Stack<E> {
    private static class Node<E>{
        E data;
        Node<E> link;
    }
    Node<E> top;
    public LinkedStack(){
        top=null;
    }
    @Override
    public void push(E elem) {
        Node<E> node=new Node<E>();
        node.data=elem;
        node.link=top;
        top=node;
    }

    @Override
    public E top() {
        if(isEmpty())
            throw new NoSuchElementException("La llista esta buida");
        return top.data;
    }

    @Override
    public void pop() {
        if(isEmpty())
            throw new NoSuchElementException("La llista esta buida");
        top=top.link;
    }

    @Override
    public boolean isEmpty() {
        return top==null;
    }
}
