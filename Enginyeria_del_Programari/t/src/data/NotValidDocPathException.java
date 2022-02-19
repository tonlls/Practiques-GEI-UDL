package data;

public class NotValidDocPathException extends Throwable {
    public NotValidDocPathException(String s) {
        super(s);
    }
    public NotValidDocPathException() {
        super();
    }
    public NotValidDocPathException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
