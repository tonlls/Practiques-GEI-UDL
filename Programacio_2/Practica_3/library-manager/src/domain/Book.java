
package domain;

import utils.PackUtils;

public class Book {
    /**
     * the limit size the title field can have
     */
    public static final int TITLE_LIMIT = 20;
    /**
     * the size a whole Book object will fit in the file
     */
    public static final int SIZE = 8+(TITLE_LIMIT*2)+8;
    
    private final long id;
    private final String title;
    private long idMember;

    /**
     * Book class constructor, initialize all the needed variables
     * @param id Book object wanted id
     * @param title Book object wanted title
     */
    public Book(long id, String title) {
        this.id=id;
        this.title=title;
        this.idMember=-1L;
    }

    private Book(long id, String title, long idSoci) {
        this.id=id;
        this.title=title;
        this.idMember=idSoci;
    }

    /**
     * gets the id from a Book object
     * @return a long containing the id
     */
    public long getId() {
        return this.id;
    }

    /**
     * gets the title from a Book object
     * @return a string containing the title
     */
    public String getTitle() {
        return this.title;
    }

    /**
     * gets the Member object id which has borrowed the book
     * @return a long id of a Member object
     */
    public long getIdMember() {
        return this.idMember;
    }

    /**
     * sets the idMember to a specified Member id
     * @param idMember the desired Member id
     */
    public void setIdMember(long idMember) {
        this.idMember=idMember;
    }

    /**
     * converts an array of bytes to a Book object
     * @param record the needed information to create a Book object (the output of toBytes)
     * @return a new Book object
     */
    public static Book fromBytes(byte[] record) {
        int offset=0;
        long idMember,id;
        id=PackUtils.unpackLong(record,offset);
        offset+=8;
        String title=PackUtils.unpackLimitedString(TITLE_LIMIT,record,offset);
        offset+=2*TITLE_LIMIT;
        idMember=PackUtils.unpackLong(record,offset);
        return new Book(id,title,idMember);
    }

    /**
     * transforms the Book object to an array of bytes
     * @return an array of bytes with size = Book.SIZE
     */
    public byte[] toBytes() {
        byte[] record = new byte[SIZE];
        int offset = 0;
        PackUtils.packLong(id, record, offset);
        offset += 8;
        PackUtils.packLimitedString(title, TITLE_LIMIT, record, offset);
        offset += 2 * TITLE_LIMIT;
        PackUtils.packLong(idMember, record, offset);
        return record;
    }
}
