package data;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAccredNumb {
    @Test
    public void testNullAccredNumb() {
        assertThrows(NullAccredNumbException.class, () -> {
            new AccredNumb(null);
        });
    }
    @Test
    public void testNotValidAccredNumb(){
        assertThrows(NotValidAccredNumbException.class, () -> {
            new AccredNumb("0123456789012");
        });
        assertThrows(NotValidAccredNumbException.class, () -> {
            new AccredNumb("01234567890");
        });
        assertThrows(NotValidAccredNumbException.class, () -> {
            new AccredNumb("01234567890A");
        });
    }
}
