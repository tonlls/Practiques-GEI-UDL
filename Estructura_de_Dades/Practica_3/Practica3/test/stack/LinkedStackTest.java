package stack;
import fibonacci.Fibonacci;
import org.junit.jupiter.api.Test;

import java.util.NoSuchElementException;

import static org.junit.jupiter.api.Assertions.*;
class LinkedStackTest {
    @Test
    public void pushTest(){
        Stack<Integer> ls=new LinkedStack<Integer>();
        ls.push(10);
        ls.push(2);
        assertEquals(false,ls.isEmpty());
        assertEquals(2,ls.top());
        ls.push(89);
        ls.push(9);
        ls.push(5);
        assertEquals(false,ls.isEmpty());
        assertEquals(5,ls.top());

    }
    @Test
    public void topTest(){
        Stack<Integer> ls=new LinkedStack<Integer>();
        assertThrows(NoSuchElementException.class, ls::top);
        ls.push(21);
        assertEquals(21,ls.top());
        ls.push(10);
        assertEquals(10,ls.top());
    }
    @Test
    public void popTest(){
        Stack<Integer> ls=new LinkedStack<Integer>();
        assertThrows(NoSuchElementException.class, ls::top);
        ls.push(5);
        ls.push(1);
        assertEquals(1,ls.top());
        ls.pop();
        assertEquals(5,ls.top());
    }
    @Test
    public void isEmptyTest(){
        Stack<Integer> ls =new LinkedStack<Integer>();
        assertEquals(true,ls.isEmpty());
        ls.push(1);
        assertEquals(false,ls.isEmpty());
        ls.pop();
        assertEquals(true,ls.isEmpty());
       System.out.println(Fibonacci.fibonacciIter(5));
    }
    @Test
    public void exceptionTest(){
        Stack<Integer> empty = new LinkedStack<>();
        assertThrows(NoSuchElementException.class, () -> { empty.top(); });
        assertThrows(NoSuchElementException.class, () -> { empty.pop(); });
    }

}