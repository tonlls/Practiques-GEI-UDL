package services;

public class NotAffiliatedException extends Exception {
    public NotAffiliatedException(String message) {
        super(message);
    }
    public NotAffiliatedException(String message, Throwable cause) {
        super(message, cause);
    }
    public NotAffiliatedException() {
        super();
    }
}
