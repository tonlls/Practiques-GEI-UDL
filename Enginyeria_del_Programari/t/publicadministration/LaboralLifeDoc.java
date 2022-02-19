package publicadministration;

import data.Nif;

public class LaboralLifeDoc extends PDFDocument { // Represents the laboral life
    private Nif nif;
    private QuotePeriodsColl quotePds;
    public LaboralLifeDoc (Nif nif, QuotePeriodsColl qtP) {
        // Initializes attributes7
        this.nif = nif;
        this.quotePds = qtP;
    }
    // the getters
    public Nif getNif () {
        return nif;
    }
    public QuotePeriodsColl getQuotePds () {
        return quotePds;
    }
}
