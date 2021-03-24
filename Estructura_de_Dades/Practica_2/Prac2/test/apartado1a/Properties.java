package test.apartado1a;

import apartado1a.Employee;
import apartado1a.Person;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class Properties {
    @Test
    void reflexivity() {
        Person p = new Person("John Doe");
        assertEquals(p, p);
    }
    @Test
    void symmetry1() {
        Person p1 = new Person("John Doe");
        Person p2 = new Person("John Doe");
        assertEquals(p1, p2);
        assertEquals(p2, p1);
    }
    @Test
    void symmetry2() {
        Person p1 = new Person("John Doe");
        Person p2 = new Person("Jane Doe");
        assertNotEquals(p1, p2);
        assertNotEquals(p2, p1);
    }
    @Test
    void transitivity() {
        Person p1 = new Person("John Doe");
        Person p2 = new Person("John Doe");
        Person p3 = new Person("John Doe");
        assertEquals(p1, p2);
        assertEquals(p2, p3);
        assertEquals(p1, p3);
    }
    @Test
    void nullParameter() {
        Person p = new Person("John Doe");
        assertNotEquals(p, null);
    }
    @Test
    void notInteroperable() {
        Person p = new Person("John Doe");
        Employee e = new Employee("John Doe", 25_000);
        assertNotEquals(p, e);
        assertNotEquals(e, p);
    }
}