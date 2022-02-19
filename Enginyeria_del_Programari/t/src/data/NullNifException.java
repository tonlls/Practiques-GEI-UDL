package data;

public class NullNifException extends Throwable {
    public NullNifException(String s) {
        super(s);
    }
    public NullNifException() {
        super();
    }
    public NullNifException(String s, Throwable cause) {
        super(s, cause);
    }
}
