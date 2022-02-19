package data;

public class NullPinException extends Throwable {
    public NullPinException(String s) {
        super(s);
    }
    public NullPinException() {
        super();
    }
    public NullPinException(String s, Throwable throwable) {
        super(s, throwable);
    }
}
