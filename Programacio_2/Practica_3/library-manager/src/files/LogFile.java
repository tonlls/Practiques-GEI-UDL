package files;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class LogFile {
    private final BufferedWriter log;

    /**
     * LogFile constructor, initializes all the needed variables
     * @param fileName the name we want the log file to have
     * @throws IOException in case of any error with the file creation/opening
     */
    public LogFile(String fileName) throws IOException {
        log = new BufferedWriter(new FileWriter(fileName));
    }

    /**
     * closes de file where we will store the logs
     * @throws IOException in case of error closing the file
     */
    public void close() throws IOException {
        log.close();
    }

    private void writeln(String message) throws IOException {
        log.write(message);
        log.newLine();
    }

    /**
     * writes a succesful operation in the log file
     * @param message the message we want to write
     * @param lineNumber te line number which has been executed
     * @throws IOException in case of any error writing to the file
     */
    public void ok(String message, int lineNumber) throws IOException {
        writeln(String.format("OK(%d): %s", lineNumber, message));
    }

    /**
     * writes a error message to the log file
     * @param message the message we want to write
     * @param lineNumber the line number which has been executed
     * @throws IOException in case of any error writing to the file
     */
    public void error(String message, int lineNumber) throws IOException {
        writeln(String.format("ERROR(%d): %s", lineNumber, message));
    }
}
