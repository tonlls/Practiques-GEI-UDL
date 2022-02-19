package data;

import java.util.Objects;

final public class Password {
    private String password;

    public Password(String password) throws NotValidPasswordException, NullPasswordException {
        //check if password is valid and not null
        if (password == null) throw new NullPasswordException("Password cannot be null");
        if (!isValid(password)) throw new NotValidPasswordException("Password must be at least 8 characters long");
        this.password = password;
    }

    private boolean isValid(String password) {
        //password must have one capital letter a lower case letter a number and a special char
        if (password.length() < 8) return false;
        boolean hasUpper = false;
        boolean hasLower = false;
        boolean hasNumber = false;
        boolean hasSpecial = false;
        for (int i = 0; i < password.length(); i++) {
            char c = password.charAt(i);
            if (Character.isUpperCase(c)) hasUpper = true;
            if (Character.isLowerCase(c)) hasLower = true;
            if (Character.isDigit(c)) hasNumber = true;
            if (!Character.isLetterOrDigit(c)) hasSpecial = true;
        }
        return hasUpper && hasLower && hasNumber && hasSpecial;
    }

    public String getPassword() { return password; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Password password1 = (Password) o;
        return password.equals(password1.password);
    }

    @Override
    public int hashCode() { return Objects.hash(password); }
    public String toString(){
        return "Password{ password = " + password + " }";
    }
}
