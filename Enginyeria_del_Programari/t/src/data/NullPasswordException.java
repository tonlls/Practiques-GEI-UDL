package data;

public class NullPasswordException extends Throwable {
    public NullPasswordException(String s) {
        super(s);
    }
    public NullPasswordException() {
        super();
    }
    public NullPasswordException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
