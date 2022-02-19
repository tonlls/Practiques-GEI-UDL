package data;

final public class Nif {
    // The tax identification number in the Spanish state.
    private final String nif;
    public Nif (String code) throws NotValidNifException, NullNifException {
        //check if the code is valid and not null
        if (code == null) throw new NullNifException("The code cannot be null");
        if (!isValid(code)) throw new NotValidNifException("The code is not valid");
        this.nif = code;
    }
    public String getNif () { return nif; }
    private boolean isValid(String code) {
        //check if the code is valid the code must have 8 numbers and a letter at the end
        if (code.length() != 9) return false;
        if (!Character.isLetter(code.charAt(8))) return false;
        if(!code.substring(0, 8).matches("[0-9]+")) return false;
        return true;
    }
    @Override
    public boolean equals (Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Nif niff = (Nif) o;
        return nif.equals(niff.nif);
    }
    @Override
    public int hashCode () { return nif.hashCode(); }
    @Override
    public String toString () {
        return "Nif{" + "nif ciudadano='" + nif + '\'' + '}';
    }
}
