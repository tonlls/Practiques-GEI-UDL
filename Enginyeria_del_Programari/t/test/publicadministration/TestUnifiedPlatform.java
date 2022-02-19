package publicadministration;

import data.*;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import services.*;

import java.net.ConnectException;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestUnifiedPlatform {
    CertificationAuthority ca;
    SS ss;
    UnifiedPlatform unifiedPlatform;

    @BeforeEach
    public void initialize(){
        ca=new CertificationAuthorityFake();
        unifiedPlatform=new UnifiedPlatform(ss,ca);
    }

    @Test
    public void testCorrectCase() throws AnyKeyWordProcedureException, NotValidNifException, NullNifException, IncorrectValDateException, NifNotRegisteredException, AnyMobileRegisteredException, ConnectException, NotValidPINException, NullPinException, NotAffiliatedException {
        unifiedPlatform.processSearcher();
        unifiedPlatform.enterKeyWords("vida laboral");
        unifiedPlatform.selectSS();
        unifiedPlatform.selectCitizens();
        unifiedPlatform.selectReports();
        unifiedPlatform.selectCertificationReport("a".getBytes()[0]);
        unifiedPlatform.selectAuthMethod("a".getBytes()[0]);
        unifiedPlatform.enterNIFPINobt(new Nif("00000000A"),new Date());
        unifiedPlatform.enterPIN(new PINcode("000"));
    }
    @Test
    public void testNifNotRegisteredException() throws AnyKeyWordProcedureException {
        unifiedPlatform.processSearcher();
        unifiedPlatform.enterKeyWords("vida laboral");
        unifiedPlatform.selectSS();
        unifiedPlatform.selectCitizens();
        unifiedPlatform.selectReports();
        unifiedPlatform.selectCertificationReport("a".getBytes()[0]);
        unifiedPlatform.selectAuthMethod("a".getBytes()[0]);
        assertThrows(NifNotRegisteredException.class,()-> {
            unifiedPlatform.enterNIFPINobt(new Nif("12345678A"), new Date());
        });
    }
    @Test
    public void testIncorrectValDateException() throws AnyKeyWordProcedureException {
        unifiedPlatform.processSearcher();
        unifiedPlatform.enterKeyWords("vida laboral");
        unifiedPlatform.selectSS();
        unifiedPlatform.selectCitizens();
        unifiedPlatform.selectReports();
        unifiedPlatform.selectCertificationReport("a".getBytes()[0]);
        unifiedPlatform.selectAuthMethod("a".getBytes()[0]);
        assertThrows(IncorrectValDateException.class,()-> {
            unifiedPlatform.enterNIFPINobt(new Nif("12345678B"), new Date());
        });
    }
    @Test
    public void testAnyMobileRegisteredException() throws AnyKeyWordProcedureException {
        unifiedPlatform.processSearcher();
        unifiedPlatform.enterKeyWords("vida laboral");
        unifiedPlatform.selectSS();
        unifiedPlatform.selectCitizens();
        unifiedPlatform.selectReports();
        unifiedPlatform.selectCertificationReport("a".getBytes()[0]);
        unifiedPlatform.selectAuthMethod("a".getBytes()[0]);
        assertThrows(AnyMobileRegisteredException.class,()-> {
            unifiedPlatform.enterNIFPINobt(new Nif("12345678C"), new Date());
        });
    }
    @Test
    public void testNotValidPINException() throws AnyKeyWordProcedureException, NotValidNifException, NullNifException, NotValidPINException, NullPinException, NotAffiliatedException, ConnectException {
        unifiedPlatform.processSearcher();
        unifiedPlatform.enterKeyWords("vida laboral");
        unifiedPlatform.selectSS();
        unifiedPlatform.selectCitizens();
        unifiedPlatform.selectReports();
        unifiedPlatform.selectCertificationReport("a".getBytes()[0]);
        unifiedPlatform.selectAuthMethod("a".getBytes()[0]);
        assertThrows(NotValidPINException.class,()-> {
            unifiedPlatform.enterPIN(new PINcode("000"));
        });
    }
}
