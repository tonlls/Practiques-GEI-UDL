package data;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestNif {
    @Test
    public void testNullNifException(){
        assertThrows(NullNifException.class, () -> {
            Nif nif = new Nif(null);
        });
    }
    @Test
    public void testNotValidNifException(){
        assertThrows(NotValidNifException.class, () -> {
            Nif nif = new Nif("123456789");
        });
        assertThrows(NotValidNifException.class, () -> {
            Nif nif = new Nif("123456789A");
        });
        assertThrows(NotValidNifException.class, () -> {
            Nif nif = new Nif("12345678");
        });
        assertThrows(NotValidNifException.class, () -> {
            Nif nif = new Nif("A2345678A");
        });
    }
}
