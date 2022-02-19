package publicadministration;

import data.Nif;
import data.NotValidPINException;
import data.PINcode;
import data.Password;
import services.*;

import java.net.ConnectException;
import java.util.Date;

public class CertificationAuthorityFake implements CertificationAuthority {
    boolean pin_sent=false;

    @Override
    public boolean sendPIN(Nif nif, Date date) throws NifNotRegisteredException, IncorrectValDateException, AnyMobileRegisteredException, ConnectException {
        if(nif.getNif().equals("12345678A")) throw new NifNotRegisteredException();
        if(nif.getNif().equals("12345678B")) throw new IncorrectValDateException();
        if(nif.getNif().equals("12345678C")) throw new AnyMobileRegisteredException();
        System.out.println("PIN enviado");
        pin_sent=true;
        return true;
    }

    @Override
    public boolean checkPIN(Nif nif, PINcode pin) throws NotValidPINException, ConnectException {
        if(pin_sent){
            System.out.println("PIN correcto");
            return true;
        }
        throw new NotValidPINException("User not registered");
    }

    @Override
    public byte ckeckCredent(Nif nif, Password passw) throws NifNotRegisteredException, NotValidCredException, AnyMobileRegisteredException, ConnectException {
        if(nif.getNif().equals("12345678A")) throw new NifNotRegisteredException();
        if(nif.getNif().equals("12345678B")) throw new NotValidCredException();
        if(nif.getNif().equals("12345678C")) throw new AnyMobileRegisteredException();
        System.out.println("Credenciales correctas");
        return 1;
    }
}
