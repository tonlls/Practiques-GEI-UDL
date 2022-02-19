package data;

public class NotValidNifException extends Throwable {
    public NotValidNifException(String s) {
        super(s);
    }
    public NotValidNifException() {
        super();
    }
    public NotValidNifException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
