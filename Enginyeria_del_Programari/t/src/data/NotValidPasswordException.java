package data;

public class NotValidPasswordException extends Throwable {
    public NotValidPasswordException(String s) {
        super(s);
    }
    public NotValidPasswordException(String s, Throwable throwable) {
        super(s, throwable);
    }
    public NotValidPasswordException() {
    }
}
