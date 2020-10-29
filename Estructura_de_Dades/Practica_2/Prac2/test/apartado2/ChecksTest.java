package test.apartado2;

import apartado2.Check;
import apartado2.Checks;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.junit.jupiter.api.Assertions.assertEquals;
class ChecksTest {
    @Test
    void countEvenLocalClass() {
        class CheckEven implements Check<Integer> {
            @Override
            public boolean test(Integer n) {
                return n % 2 == 0;
            }
        }
        var it = List.of(1, 2, 3, 4, 5, 6, 7).iterator();
        assertEquals(3, Checks.countIf(it, new CheckEven()));
    }
    @Test
    void countAnonymousClass() {
        var it = List.of(1, 2, 3, 4, 5, 6, 7).iterator();
        assertEquals(3, Checks.countIf(it, new Check<Integer>() {
            @Override
            public boolean test(Integer n) {
                return n % 2 == 0;
            }
        }));
    }
    @Test
    void countLambda() {
        var it = List.of(1, 2, 3, 4, 5, 6, 7).iterator();
        assertEquals(3, Checks.countIf(it, n -> n % 2 == 0));
    }
}