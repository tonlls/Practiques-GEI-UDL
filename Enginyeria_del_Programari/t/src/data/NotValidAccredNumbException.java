package data;

public class NotValidAccredNumbException extends Throwable {
    public NotValidAccredNumbException(String s) {
        super(s);
    }
    public NotValidAccredNumbException() {
        super();
    }
    public NotValidAccredNumbException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
