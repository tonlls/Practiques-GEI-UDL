
package domain;

import utils.PackUtils;

public class Member {
    
    private static final int MAX_BOOKS = 3;
    /**
     * the limit size the name field can have
     */
    public static final int NAME_LIMIT = 20;
    /**
     * the limit size the address field can have
     */
    public static final int ADDRESS_LIMIT = 30;
    /**
     * the size the whole Member object will fit in the file
     */
    public static final int SIZE = 8+(NAME_LIMIT*2)+(ADDRESS_LIMIT*2)+(MAX_BOOKS*8);
    
    private final long id;
    private final String name;
    private final String address;
    private final long[] idBooks;

    /**
     * Member class constructor, initialize all the needed variables
     * @param id the Member id
     * @param name the Member name
     * @param address the Member address
     */
    public Member(long id, String name, String address) {
        this.id=id;
        this.name=name;
        this.address=address;
        this.idBooks = new long[]{-1L,-1L,-1L};
    }

    private Member(long id, String name, String address, long[] idBooks) {
        this.id=id;
        this.name=name;
        this.address=address;
        this.idBooks=idBooks;
    }

    /**
     * gets the id from a Member object
     * @return a long containing the id
     */
    public long getId() { return this.id; }

    /**
     * gets the name from a Member object
     * @return a string containing the name
     */
    public String getName() { return this.name; }

    /**
     * gets the adress from a Member object
     * @return a string containing the adress
     */
    public String getAddress() {
        return this.address;
    }

    /**
     * counts the number of books a Member have
     * @return integer containing the number of books
     */
    public int countBooks() {
        int len=0;
        for(long l:this.idBooks){
            if(l!=-1L)len++;
        }
        return len;
    }

    /**
     * checks if a member has the limit of books so he can borrow or not
     * @return a boolean indicating if the member can borrow
     */
    public boolean canBorrow() {
        return countBooks()<MAX_BOOKS;
    }

    private int find_empty(){
        for(int i=0;i<MAX_BOOKS;i++){
            if(idBooks[i]==-1L)
                return i;
        }
        return -1;
    }

    /**
     * adds a book to de Member Book list
     * @param idBook the book id to add
     */
    public void addBook(long idBook) {
        if(canBorrow())
            this.idBooks[find_empty()]=idBook;
    }

    /**
     * removes a book from the file
     * @param idBook the Book id we want to remove
     */
    public void removeBook(long idBook) {
        for(int i=0;i<MAX_BOOKS;i++){
            if(idBooks[i]==idBook)
                idBooks[i]=-1L;
        }
    }

    /**
     * checks if a Member has borrowed the Book object with specified id
     * @param idBook the Book id to check
     * @return true if found, false otherwise
     */
    public boolean containsBook(long idBook) {
        for(long b:this.idBooks){
            if(b==idBook)return true;
        }
        return false;
    }

    /**
     * creates a Member object from an array of bytes
     * @param record the byte array containing all the data for a Member object (the output of toBytes)
     * @return a new Member object
     */
    public static Member fromBytes(byte[] record) {
        int offset=0;
        long id=PackUtils.unpackLong(record,offset);
        offset+=8;
        String name=PackUtils.unpackLimitedString(NAME_LIMIT,record,offset);
        offset+=2*NAME_LIMIT;
        String address=PackUtils.unpackLimitedString(ADDRESS_LIMIT,record,offset);
        offset+=2*ADDRESS_LIMIT;
        long idBooks[]=new long[MAX_BOOKS];
        for(int i=0;i<MAX_BOOKS;i++){
            idBooks[i]=PackUtils.unpackLong(record,offset);
            offset+=8;
        }
        return new Member(id,name,address,idBooks);
    }

    /**
     * transforms the Member object to an array of bytes
     * @return an array of bytes with size = Member.SIZE
     */
    public byte[] toBytes() {
        byte[] record = new byte[SIZE];
        int offset = 0;
        PackUtils.packLong(id, record, offset);
        offset += 8;
        PackUtils.packLimitedString(name, NAME_LIMIT, record, offset);
        offset += 2 * NAME_LIMIT;
        PackUtils.packLimitedString(address, ADDRESS_LIMIT, record, offset);
        offset+= 2 * ADDRESS_LIMIT;
        for(int i=0;i<MAX_BOOKS;i++){
            PackUtils.packLong(idBooks[i], record, offset);
            offset+=8;
        }
        return record;
    }
}
