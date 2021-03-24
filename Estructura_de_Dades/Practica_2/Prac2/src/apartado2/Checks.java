package apartado2;

import java.util.Iterator;

public class Checks {
    public static <E> int countIf(Iterator<E> it, Check<E> test) {
        int i = 0;
        while(it.hasNext())
            if(test.test(it.next()))
                i++;
        return i;
    }
}
