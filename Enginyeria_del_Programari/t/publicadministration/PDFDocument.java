package publicadministration;

import data.DocPath;

import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.Date;

public class PDFDocument { // Represents a PDF document
    private Date creatDate;
    private DocPath path;
    private File file;
    public PDFDocument () {
        // Initializes attributes and emulates the document download at a default path
        System.out.println("Document downloaded at default path");
    }
    // the getters
    public Date getCreatDate() {
        return creatDate;
    }
    public DocPath getPath() {
        return path;
    }
    public File getFile() {
        return file;
    }
    public String toString () {
        // Converts to String members Date and DocPath
        return "PFDocument{ " + creatDate + " " + path +" }";
    }
    // To implement only optionally
    public void moveDoc (DocPath destPath) throws IOException {
        // Moves the document to the destination path indicated
        File f=new File(destPath.getPath());
        f.renameTo(new File(destPath.getPath()));
    }
    public void openDoc () throws IOException{
        // Opens the document at the path indicated
        Desktop desktop = Desktop.getDesktop();
        if(file.exists()) desktop.open(file);

    }
}