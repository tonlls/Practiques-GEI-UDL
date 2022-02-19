package data;

final public class AccredNumb {
    private final String accredNumb;

    public AccredNumb(String accredNumb) throws NotValidAccredNumbException, NullAccredNumbException {
        if(accredNumb==null)throw new NullAccredNumbException("accredNumb is null");
        if(!isValid(accredNumb))throw new NotValidAccredNumbException("Invalid accred number");
        this.accredNumb = accredNumb;
    }
    private boolean isValid(String num){
        //check the number of 12 digits
        if(num.length() != 12)return false;
        if(!num.matches("[0-9]+"))return false;
        return true;
    }
    public boolean equals(Object o){
        if(o==null)return false;
        if(o.getClass()!=this.getClass())return false;
        AccredNumb a = (AccredNumb)o;
        return this.accredNumb.equals(a.accredNumb);
    }
    public String getAccredNumb() {
        return accredNumb;
    }
}
