
package librarymanager;

import acm.program.CommandLineProgram;
import domain.Book;
import domain.Member;
import files.BooksFile;
import files.LogFile;
import files.MembersFile;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.StringTokenizer;

public class LibraryManager extends CommandLineProgram {

    private static final String BOOKS = "llibres.dat";
    private static final String MEMBERS = "socis.dat";
    private static final String LOG = "manager.log";
    private static final String MOVEMENTS = "movements.csv";

    private BufferedReader movements;

    private BooksFile booksFile;
    private MembersFile membersFile;
    private LogFile logFile;

    private int movementNumber;

    // Entry points

    /**
     * starts the program by actually calling to the run function
     * @param args the arguments the program will need to be executed, actually the command line arguments
     */
    public static void main(String[] args) { new LibraryManager().start(args); }

    /**
     * the main function in our program, it will execute all the needed functions to run our program
     */
    public void run() {
        try {
            openFiles();
            processMovements();
            closeFiles();
        } catch (IOException ex) {
            println("ERROR (something about the files)");
        }
    }

    // Opening and closing

    private void openFiles() throws IOException {
        this.booksFile=new BooksFile(BOOKS);
        this.membersFile=new MembersFile(MEMBERS);
        this.logFile=new LogFile(LOG);
        this.movements=new BufferedReader(new FileReader(MOVEMENTS));
        this.movementNumber=0;
    }

    private void closeFiles() throws IOException {
        this.booksFile.close();
        this.membersFile.close();
        this.logFile.close();
        this.movements.close();
    }

    // Movements processing
    private void checkMemberId(long id) throws Exception {
        if(id<0||id>(int)membersFile.length()){
            throw new Exception("el codi de membre:'"+id+"' no es valid");
        }
    }

    private void checkBookId(long id) throws Exception {
        if(id<0||id>(int)booksFile.length()){
            throw new Exception("el codi del llibre:'"+id+"' no es valid");
        }
    }

    private void addBook(StringTokenizer args) throws IOException {
        try {
            long id=this.booksFile.length()+1;
            this.booksFile.write(new Book(id,args.nextToken()));
            logFile.ok("s'ha afegit correctament el llibre amb id="+id,movementNumber);
        } catch (Exception e){
            logFile.error("error al afegir el llibre",movementNumber);
        }
    }
    private void addMember(StringTokenizer args) throws IOException {
        try {
            long id=this.membersFile.length()+1;
            this.membersFile.write(new Member(id,args.nextToken(), args.nextToken()));
            logFile.ok("s'ha afegit correctament el membre amb id="+id,movementNumber);
        } catch (IOException e) {
            logFile.error("error al afegir el membre",movementNumber);
        }
    }
    private void borrowBook(StringTokenizer args) throws IOException {
        long idBook,idMember;
        Book book;
        Member member;
        idBook=Long.valueOf(args.nextToken());
        idMember=Long.valueOf(args.nextToken());
        try {
            checkBookId(idBook);
            checkMemberId(idMember);
            book = booksFile.read(idBook);
            if (book.getIdMember() != -1L) {
                throw new Exception("el llibre ja està deixat");
            }
            member = membersFile.read(idMember);
            if (!member.canBorrow()) {
                throw new Exception("el membre no pot demanar llibres");
            }
            book.setIdMember(idMember);
            member.addBook(idBook);
            booksFile.write(book);
            membersFile.write(member);
            logFile.ok("prestam del llibre amb id="+idBook+" al membre amb id="+idMember+" realitzat correctament", movementNumber);
        } catch(IOException e){
            logFile.error("error en fer el prestam",movementNumber);
        } catch (Exception e){
            logFile.error(e.getMessage(),movementNumber);
        }
    }

    private void returnBook(StringTokenizer args) throws IOException {
        Book book;
        Member member;
        long idBook=Long.parseLong(args.nextToken());
        try {
            checkBookId(idBook);
            book=booksFile.read(idBook);
            checkMemberId(book.getIdMember());
            member=membersFile.read(book.getIdMember());
            if(!member.containsBook(idBook)){
                throw new Exception("aquest membre no te aquest llibre");
            }
            book.setIdMember(-1L);
            member.removeBook(idBook);
            booksFile.write(book);
            membersFile.write(member);
            logFile.ok("",movementNumber);
        }catch (Exception e){
            logFile.error(e.getMessage(),movementNumber);
        }
    }

    private void runInstruction(StringTokenizer args) throws IOException {
        switch (args.nextToken()){
            case "ALTALIBRO":addBook(args);break;
            case "ALTASOCIO":addMember(args);break;
            case "PRÉSTAMO":borrowBook(args);break;
            case "DEVOLUCIÓN":returnBook(args);break;
        }
    }

    private void processMovements() throws IOException {
        StringTokenizer args;
        String line=this.movements.readLine();
        while(line!=null){
            args=new StringTokenizer(line,",");
            runInstruction(args);
            this.movementNumber++;
            line=this.movements.readLine();

        }
    }
}