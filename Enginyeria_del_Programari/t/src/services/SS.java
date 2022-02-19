package services;

import data.Nif;
import publicadministration.LaboralLifeDoc;
import publicadministration.MemberAccreditationDoc;

import java.net.ConnectException;

public interface SS {
    LaboralLifeDoc getLaboralLife (Nif nif) throws NotAffiliatedException, ConnectException;
    MemberAccreditationDoc getMembAccred (Nif nif) throws NotAffiliatedException, ConnectException;

}
