
package files;

import domain.Member;
import java.io.IOException;
import java.io.RandomAccessFile;

public class MembersFile {
    
    private final RandomAccessFile raf;

    /**
     * MembersFile constructor
     * @param fname the name we want the Members file to have
     * @throws IOException in case of any error creating/opening the file
     */
    public MembersFile(String fname) throws IOException {
        this.raf=new RandomAccessFile(fname,"rw");
    }

    /**
     * empties the file content
     * @throws IOException if an error with the file
     */
    public void clear() throws IOException {
        this.raf.setLength(0);
    }

    /**
     * reads a Member from the file and with the specified id
     * @param id the wanted member id
     * @return a Member object
     * @throws IOException if there is any problem with the file
     */
    public Member read(long id) throws IOException {
        byte[] out=new byte[Member.SIZE];
        this.raf.seek(id*Member.SIZE);
        this.raf.read(out);
        return Member.fromBytes(out);
    }

    /**
     * writes a Member object to the file to the specific position
     * @param member the member object to write
     * @throws IOException if there's any problem with the file
     */
    public void write(Member member) throws IOException {
        this.raf.seek(member.getId()*Member.SIZE);
        this.raf.write(member.toBytes());
    }

    /**
     * returns the number of member in the file
     * @return long
     * @throws IOException if there is an error with the file
     */
    public long length() throws IOException {
        return (this.raf.length()-1)/Member.SIZE;
    }

    /**
     * actually closes the file
     * @throws IOException if there is an error with the file
     */
    public void close() throws IOException {
        this.raf.close();
    }   
}