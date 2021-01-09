package test.apartado3;

import apartado3.Comparisons;
import apartado3.Employee;
import apartado3.Person;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;
class ComparisonsTest {
    @Test
    void mixed1() {
        List<Employee> employees = List.of(
                new Employee("John Doe", 150_000),
                new Employee("Peter Parker", 12_000),
                new Employee("Bruce Wayne", 999_999),
                new Employee("Clark Kent", 45_000)
        );
        assertEquals(3,Comparisons.countLower(employees.iterator(), new Person("Noname")));
    }
    @Test
    void mixed2() {
        List<Person> employees = List.of(
                new Employee("John Doe", 150_000),
                new Employee("Peter Parker", 12_000),
                new Employee("Bruce Wayne", 999_999),
                new Employee("Clark Kent", 45_000)
        );
        assertEquals(3, Comparisons.countLower(employees.iterator(), new Employee("Noname", 0)));
    }
    @Test
    void employees() {
        List<Employee> employees = List.of(
                new Employee("John Doe", 150_000),
                new Employee("Peter Parker", 12_000),
                new Employee("Bruce Wayne", 999_999),
                new Employee("Clark Kent", 45_000)
        );
        assertEquals(3, Comparisons.countLower(employees.iterator(), new Employee("Noname", 0)));
    }
}