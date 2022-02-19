package data;

public class NotValidPINException extends Throwable {
    public NotValidPINException(String s) {
        super(s);
    }
    public NotValidPINException() {
        super();
    }
    public NotValidPINException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
