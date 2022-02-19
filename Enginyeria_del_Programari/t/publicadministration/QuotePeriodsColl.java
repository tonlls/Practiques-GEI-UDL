package publicadministration;

import java.util.Date;
import java.util.SortedMap;
import java.util.TreeMap;

public class QuotePeriodsColl {
    SortedMap<Date,QuotePeriod> periods;
    // Represents the total quote periods known as a registered worker
    // Its components, that is, the set of quote periods
    public QuotePeriodsColl () {
        // Initializes the object
        periods = new TreeMap<>();
    }
    // the getters
    public SortedMap<Date,QuotePeriod> getPeriods() {return periods;}
    public void addQuotePeriod (QuotePeriod qPd) {
        // Adds a quote period, always respecting the sorting by date, from oldest to later in time
        periods.put(qPd.getInitDay(),qPd);
    }
    public String toString () {
        // Converts to String
        return periods.toString();
    }
}
