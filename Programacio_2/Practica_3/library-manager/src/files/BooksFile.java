
package files;

import domain.Book;
import java.io.IOException;
import java.io.RandomAccessFile;

public class BooksFile {
    
    private final RandomAccessFile raf;

    /**
     * BooksFile class constructor
     * @param fname string name of the file which store Books
     * @throws IOException in case of opening error
     */
    public BooksFile(String fname) throws IOException {
        this.raf =new RandomAccessFile(fname, "rw");
    }

    /**
     * clears a BookFile by setting it's length to 0
     * @throws IOException in case of any error clearing the file
     */
    public void clear() throws IOException {
        this.raf.setLength(0);
    }

    /**
     * reads a Book object from the file with the specified id
     * @param id of the Book object the function will return
     * @return the required Book object
     * @throws IOException in case of any file error
     */
    public Book read(long id) throws IOException {
        byte[] out=new byte[Book.SIZE];
        this.raf.seek(id*Book.SIZE);
        this.raf.read(out);
        return Book.fromBytes(out);
    }

    /**
     * writes a Book object to the file
     * @param book the book we want to save
     * @throws IOException in case of any file error
     */
    public void write(Book book) throws IOException {
        this.raf.seek(book.getId()*Book.SIZE);
        this.raf.write(book.toBytes());
    }

    /**
     * get the number of books into the file
     * @return a long
     * @throws IOException in case of any file error
     */
    public long length() throws IOException {
        return (this.raf.length()-1)/Book.SIZE;
    }

    /**
     * closes the books file
     * @throws IOException in case of any file error
     */
    public void close() throws IOException {
        this.raf.close();
    }
}