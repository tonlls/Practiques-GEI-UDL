package Apartat2;

public interface BinaryTree<E> {
    boolean isEmpty();
    E root();
    BinaryTree<E> left();
    BinaryTree<E> right();
}