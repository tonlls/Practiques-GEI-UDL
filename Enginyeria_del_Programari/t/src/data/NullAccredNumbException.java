package data;

public class NullAccredNumbException extends Throwable {
    public NullAccredNumbException(String s) {
        super(s);
    }
    public NullAccredNumbException() {
        super();
    }
    public NullAccredNumbException(String s, Throwable t) {
        super(s, t);
    }
}
