package data;

public class NullDocPathException extends Throwable {
    public NullDocPathException(String s) {
        super(s);
    }
    public NullDocPathException() {
        super();
    }
    public NullDocPathException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
