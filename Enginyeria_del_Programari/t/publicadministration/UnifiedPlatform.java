package publicadministration;

import data.*;
import services.*;

import java.net.ConnectException;
import java.util.Date;
import java.util.Map;

public class UnifiedPlatform {
    private SS ss;
    Nif nif;
    private CertificationAuthority certificationAuthority;
    Node AAPP;

    public UnifiedPlatform(SS ss, CertificationAuthority certificationAuthority) {
        Node n;
        this.ss = ss;
        this.certificationAuthority = certificationAuthority;
        AAPP = new Node("root");

        n=new Node("SS");
        n.addChild(new Node("Solicitar informe de vida laboral"));
        n.addChild(new Node("obtenir nombre de afiliació a SS"));
        AAPP.addChild(n);

        n=new Node("AEAT");
        n.addChild(new Node("obtenir dades fiscals"));
        n.addChild(new Node("tramitar borrador de la declaració de la renta"));
        AAPP.addChild(n);

        n=new Node("Ministerio de Justicia");
        n.addChild(new Node("solicitar certificat de naixement"));
        AAPP.addChild(n);

        n=new Node("DGT");
        n.addChild(new Node("consultar punts carnet de conduir"));
        AAPP.addChild(n);
    }

    public void processSearcher () {
        System.out.println("Processing searcher");
    }
    public void enterKeyWords (String keyWord) throws AnyKeyWordProcedureException{
        String s= (String) AAPP.searchOnChilds(keyWord);
        if(s==null)throw new AnyKeyWordProcedureException("No existeix cap procés per aquesta paraula clau");
        System.out.println(s);
    }
    public void selectSS () {
        System.out.println("SS clicked");
    }
    public void selectCitizens () {
        System.out.println("Citizens clicked");
    }
    public void selectReports () {
        System.out.println("Reports clicked");
    }
    public void selectCertificationReport (byte opc) {
        System.out.println("Certification report "+ opc +" selected");
    }
    public void selectAuthMethod (byte opc) {
        System.out.println("Auth method "+ opc +" selected");
    }
    public void enterNIFPINobt (Nif nif, Date valDate) throws NifNotRegisteredException, IncorrectValDateException,
            AnyMobileRegisteredException, ConnectException {
        this.nif=nif;
        certificationAuthority.sendPIN(nif,valDate);
    }

    public void enterPIN(PINcode pin) throws NotValidPINException, NotAffiliatedException, ConnectException {
        certificationAuthority.checkPIN(nif,pin);
    }

    public void enterCred(Nif nif, Password passw) throws NifNotRegisteredException, NotValidCredException, AnyMobileRegisteredException, ConnectException {
        certificationAuthority.ckeckCredent(nif,passw);
    }

    private void printDocument() throws BadPathException, PrintingException {
        System.out.println("Printing document");
    }

    private void downloadDocument () {
        System.out.println("Downloading document");
    }

    private void selectPath(DocPath path) throws BadPathException {
        System.out.println("Selecting path("+path.getPath()+")");
    }

    // Other operations
    private String searchKeyWords(String keyWord) throws AnyKeyWordProcedureException {
        return (String) AAPP.searchOnChilds(keyWord);
    }

    private void OpenDocument(DocPath path) throws BadPathException {
        System.out.println("Opening document("+path.getPath()+")");
    }

    private void printDocument(DocPath path) throws BadPathException, PrintingException {
        System.out.println("Printing document("+path.getPath()+")");
    }

    private void downloadDocument(DocPath path) throws BadPathException {
        System.out.println("Downloading document("+path.getPath()+")");
    }
    // Possibly more operations
}
