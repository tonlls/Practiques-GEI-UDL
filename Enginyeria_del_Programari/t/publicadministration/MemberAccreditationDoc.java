package publicadministration;

import data.AccredNumb;
import data.Nif;

public class MemberAccreditationDoc extends PDFDocument {
    // Represents the member accreditation document
    private Nif nif;
    private AccredNumb numAffil;
    public MemberAccreditationDoc (Nif nif, AccredNumb nAff) {
        super();
        // Initializes attributes
        this.nif = nif;
        this.numAffil = nAff;
    }
    // the getters
    public Nif getNif () {
        return this.nif;
    }
    public AccredNumb getNumAffil () {
        return this.numAffil;
    }
}