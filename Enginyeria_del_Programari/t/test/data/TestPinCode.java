package data;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestPinCode {
    @Test
    public void testNullPinCodeException() {
        assertThrows(NullPinException.class, () -> {
            new PINcode(null);
        });
    }
    @Test
    public void testNotValidPinCodeException() {
        assertThrows(NotValidPINException.class, () -> {
            new PINcode("1234");
        });
        assertThrows(NotValidPINException.class, () -> {
            new PINcode("12");
        });
        assertThrows(NotValidPINException.class, () -> {
            new PINcode("12.");
        });
        assertThrows(NotValidPINException.class, () -> {
            new PINcode("12a");
        });
        assertThrows(NotValidPINException.class, () -> {
            new PINcode("abc");
        });
    }
}
