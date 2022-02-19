package data;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

public class Node<T>{
    //a node of a tree data structure
    private T data;
    Node parent=null;
    List<Node<T>> children;
    public Node(T data){
        this.data=data;
        this.parent=parent;
        children=new ArrayList<>();
    }
    public T getData(){
        return data;
    }
    public List<Node<T>> getChildren(){
        return children;
    }
    public Node getParent(){
        return parent;
    }
    public void addChild(Node child) {
        children.add(child);
    }
    public Node getChild(int index){
        return children.get(index);
    }
    public Node getChild(T data){
        for(Node child:children){
            if(child.getData().equals(data)){
                return child;
            }
        }
        return null;
    }
    public T searchOnChilds(T data){
        for(Node child:children){
            for(Object grandChild:child.getChildren()) {
                Node c= (Node) grandChild;
                if (Pattern.matches(".*"+data+".*",(String) c.getData())) {
                    return (T) child.getData();
                }
            }
        }
        return null;
    }
}