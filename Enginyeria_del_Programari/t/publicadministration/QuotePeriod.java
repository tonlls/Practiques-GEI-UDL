package publicadministration;

import java.util.Date;

public class QuotePeriod {
    // Represents a quote period as a registered worker
    private Date initDay;
    private int numDays;
    public QuotePeriod (Date date, int ndays){
        // Initializes attributes
        initDay = date;
        numDays = ndays;
    }
    // the getters
    public Date getInitDay(){ return initDay; }
    public int getNumDays(){ return numDays; }

    public String toString () {
        // converts to String
        return "initDay: " + initDay + " numDays: " + numDays;
    }
}