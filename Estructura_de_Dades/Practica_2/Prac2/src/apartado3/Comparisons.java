package apartado3;

import java.util.Iterator;

public class Comparisons {
    public static <E extends Person,N extends Comparable<E>> int countLower(Iterator<N> it,E element){
        int i = 0;
        while(it.hasNext())
            if(it.next().compareTo(element)<0)
                i++;
        return i;
    }
}

