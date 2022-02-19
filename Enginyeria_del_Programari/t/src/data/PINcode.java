package data;

final public class PINcode {
    private final String pin;
    public PINcode(String pin) throws NotValidPINException, NullPinException {
        //check if pin is valid and not null
        if (pin==null) throw new NullPinException("PINcode cannot be null");
        if (!isValid(pin)) throw new NotValidPINException("PINcode must be 3 digits long");
        this.pin = pin;
    }
    private boolean isValid(String pin) {
        //pin must have 3 digits
        return pin.length() == 3 && pin.matches("[0-9]+");
    }
    public String getPIN() {return pin;}
    public boolean equals(Object o) {
        if (o instanceof PINcode) {
            PINcode p = (PINcode) o;
            return p.getPIN().equals(pin);
        }
        return false;
    }
    public int hashCode() {return pin.hashCode();}
    public String toString() {
        return "PINcode{pin='" + pin + "'}";
    }
}
