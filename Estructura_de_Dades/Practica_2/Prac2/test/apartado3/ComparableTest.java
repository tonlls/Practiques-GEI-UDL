package test.apartado3;

import static org.junit.jupiter.api.Assertions.*;

import apartado3.Employee;
import apartado3.Person;
import org.junit.jupiter.api.Test;

public class ComparableTest {
    private boolean lowerThan(int compare,int to) {
        return compare<to;
    }
    private boolean greaterThan(int compare,int to) {
        return compare>to;
    }
    @Test
    void upper(){
        Person p1 = new Person("JHON DOE");
        Person p2 = new Person("HATTY HATTY");
        Employee e1 = new Employee("HATTY HATTY",1000000000);
        Employee e2 = new Employee("ABIGAIL TONLLS",0);
        assertEquals(true,greaterThan(p1.compareTo(p2),0));
        assertEquals(true,lowerThan(e1.compareTo(p1),0));
        assertEquals(0,e1.compareTo(p2));
        assertEquals(true,greaterThan(e1.compareTo(e2),0));
    }
    @Test
    void lower(){
        Person p1 = new Person("jhon doe");
        Person p2 = new Person("hatty hatty");
        Employee e1 = new Employee("hatty hatty",1000000000);
        Employee e2 = new Employee("abigail tonlls",0);
        assertEquals(true,greaterThan(p1.compareTo(p2),0));
        assertEquals(true,lowerThan(e1.compareTo(p1),0));
        assertEquals(0,e1.compareTo(p2));
        assertEquals(true,greaterThan(e1.compareTo(e2),0));
    }
    @Test
    void mixed(){
        Person p1 = new Person("jHoN doE");
        Person p2 = new Person("HaTTy hAtTy");
        Employee e1 = new Employee("hatty HATTY",1000000000);
        Employee e2 = new Employee("AbigAil tonLLs",0);
        assertEquals(true,greaterThan(p1.compareTo(p2),0));
        assertEquals(true,lowerThan(e1.compareTo(p1),0));
        assertEquals(0,e1.compareTo(p2));
        assertEquals(true,greaterThan(e1.compareTo(e2),0));
    }
}
