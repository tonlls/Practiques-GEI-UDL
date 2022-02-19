package data;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestDocPath {
    @Test
    public void testNullDocPathException(){
        assertThrows(NullDocPathException.class, () -> {
            new DocPath(null);
        });
    }
    @Test
    public void testNotValidDocPathException(){
        assertThrows(NotValidDocPathException.class, () -> {
            new DocPath("");
        });
    }
}
