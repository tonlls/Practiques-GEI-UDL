package data;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestPassword {
    @Test
    public void testNullPasswordException(){
        assertThrows(NullPasswordException.class, () -> {
            Password pass = new Password(null);
        });
    }
    @Test
    public void testNotValidPasswordException(){
        assertThrows(NotValidPasswordException.class, () -> {
            Password pass = new Password("1234");
        });
        assertThrows(NotValidPasswordException.class, () -> {
            Password pass = new Password("12345678");
        });
        assertThrows(NotValidPasswordException.class, () -> {
            Password pass = new Password("1aB.");
        });
    }
}
