
import acm.program.CommandLineProgram;

import java.util.Arrays;

/**
 * @author jmgimeno
 */
public class IntegralTypes extends CommandLineProgram {

    public int BYTE_SIZE = 8;
    public int SHORT_SIZE = 16;
    public int INTEGER_SIZE = 32;
    public int LONG_SIZE = 64;

    // Creation methods (zero bytes)

    public int[] zeroOfSize(int size) {
        return new int[size];
    }

    public int[] zeroByte() {
        return zeroOfSize(BYTE_SIZE);
    }

    public int[] zeroShort() {
        return zeroOfSize(SHORT_SIZE);
    }

    public int[] zeroInteger() {
        return zeroOfSize(INTEGER_SIZE);
    }

    public int[] zeroLong() {
        return zeroOfSize(LONG_SIZE);
    }

    // toString

    public String toString(int[] num) {
        char[] chars = new char[num.length + num.length / 8];
        int iChars = 0;
        for (int iNum = num.length - 1; iNum >= 0; iNum--) {
            chars[iChars] = (char) ('0' + num[iNum]);
            iChars = iChars + 1;
            if (iNum != 0 && iNum % 8 == 0) {
                chars[iChars] = ' ';
                iChars = iChars + 1;
            }
        }
        return new String(chars, 0, iChars);
    }

    // Classifier methods

    /**
     * checks if a given integer is a 0 or a 1
     * @param num the integer to check
     * @return a boolean representing if the integer is a bit
     */
    public boolean isBit(int num){
        return num==0||num==1;
    }

    /**
     * checks if all positions of the array are ones or zeros
     * @param num the integer array to check
     * @return a boolean representing if all integers are bits
     */
    public boolean allBits(int[] num) {
        for(int i=0;i<num.length;i++){
            if(!isBit(num[i])){
                return false;
            }
        }
        return true;
    }

    public boolean hasSize(int[] num, int size) {
        return num.length == size;
    }

    public boolean isByte(int[] num) {
        return hasSize(num, BYTE_SIZE) && allBits(num);
    }

    public boolean isShort(int[] num) {
        return hasSize(num, SHORT_SIZE) && allBits(num);
    }

    public boolean isInteger(int[] num) {
        return hasSize(num, INTEGER_SIZE) && allBits(num);
    }

    public boolean isLong(int[] num) {
        return hasSize(num, LONG_SIZE) && allBits(num);
    }


    // Creation methods from String (only takes into account correct bits)

    /**
     * copies from a given string representing a binary number with the most significant bit at the 0 position to an
     * integer array with the most significant bit at the last position, if the string contains a non bit character it's ignored
     * @param from the input string
     * @param to the output integer array
     */
    public void copy(String from, int[] to) {
        int num, toPos=0, fromPos=from.length()-1;
        while(fromPos>=0 && toPos<to.length){
            num=from.charAt(fromPos)-'0';
            if(isBit(num)){
                to[toPos++]=num;
            }
            fromPos--;
        }
    }

    public int[] newByte(String from) {
        int[] num = zeroByte();
        copy(from, num);
        return num;
    }

    public int[] newShort(String from) {
        int[] num = zeroShort();
        copy(from, num);
        return num;
    }

    public int[] newInteger(String from) {
        int[] num = zeroInteger();
        copy(from, num);
        return num;
    }

    public int[] newLong(String from) {
        int[] num = zeroLong();
        copy(from, num);
        return num;
    }

    // Narrow

    /**
     * shorten a bit array to the desired length only if the desired length is shorter or equal to the actual input array length and grather than or equal to 0
     * @param from bit array to be shorten
     * @param toLength desired output length
     * @return a shortened array with the values in the from array
     */
    public int[] narrow(int[] from, int toLength) {
        int[] out=new int[toLength];
        if(toLength>=0 && toLength<=from.length) {
            copy(toString(from),out);
        }
        return out;
    }

    /**
     * creates an array whith the desired length and fills with 1's
     * @param size desired size of the output
     * @return an array full of 1's
     */
    public int[] oneOfSize(int size){
        int[] out=new int[size];
        for(int i=0;i<size;i++){
            out[i]=1;
        }
        return out;
    }

    // Widen

    /**
     * extend an integer array to the desired length conserving the sign
     * @param from input array
     * @param toLength desired length
     * @return extended array
     */
    public int[] widen(int[] from, int toLength) {
        int[] out=null;
        if(from.length>=0 && from.length<=toLength){
            if(from.length>0 && from[from.length-1]==1)
                out=oneOfSize(toLength);
            else
                out=zeroOfSize(toLength);
            copy(toString(from),out);
        }
        return out;
    }

    // Cast

    /**
     * converts a given array of integers to an array of integers with the specified length
     * @param from
     * @param toLength
     * @return te result integer array
     */
    public int[] cast(int[] from, int toLength) {
        return toLength>=from.length?widen(from,toLength):narrow(from,toLength);
    }

    public int[] toByte(int[] from) {
        return cast(from, BYTE_SIZE);
    }

    public int[] toShort(int[] from) {
        return cast(from, SHORT_SIZE);
    }

    public int[] toInteger(int[] from) {
        return cast(from, INTEGER_SIZE);
    }

    public int[] toLong(int[] from) {
        return cast(from, LONG_SIZE);
    }

    public boolean toBool(int num){
        return !(num==0);
    }
    public int toInt(boolean val){
        return val?1:0;
    }

    /**
     * and operation assuming both parameters have the same length
     * @param arg1 array of bits
     * @param arg2 array of bits
     * @return and operation result
     */
    public int[] andSameLen(int[] arg1,int[] arg2){
        int[] out=new int[arg1.length];
        for(int i=0;i<out.length;i++){
            //out[i]=toInt(toBool(arg1[i])&&toBool(arg2[i]));
            out[i]=arg1[i]&arg2[i];
        }
        return out;
    }

    /**
     * returns the apropiated length wich can be used to trate both parameters
     * @param arg1 a bit array
     * @param arg2 a bit array
     * @return useful length
     */
    public int getResultLen(int[] arg1,int[] arg2){
        return arg1.length>INTEGER_SIZE||arg2.length>INTEGER_SIZE?LONG_SIZE:INTEGER_SIZE;
    }
    // And &

    /**
     * calculates the and operation of the given arrays
     * @param arg1
     * @param arg2
     * @return result
     */
    public int[] and(int[] arg1, int[] arg2) {
        int len=getResultLen(arg1,arg2);
        return andSameLen(cast(arg1,len),cast(arg2,len));
    }

    /**
     * calculates the or operation assuming both parameters have the same length
     * @param arg1 array of bits
     * @param arg2 array of bits
     * @return or operation result
     */
    public int[] orSameLen(int[] arg1,int[] arg2){
        int[] out=new int[arg1.length];
        for(int i=0;i<out.length;i++){
//            out[i]=toInt(toBool(arg1[i])||toBool(arg2[i]));
            out[i]=arg1[i]|arg2[i];
        }
        return out;
    }
    // Or |

    /**
     * claculates the or operation of the given arrays, if they have diferent sizes the result would be adapted
     * @param arg1 integer array as the first operator
     * @param arg2 integer array as the second operator
     * @return
     */
    public int[] or(int[] arg1, int[] arg2) {
        int len=getResultLen(arg1,arg2);
        return orSameLen(cast(arg1,len),cast(arg2,len));
    }

    /**
     * gets ideal size to work
     * @param arg input integer array
     * @return the desired length
     */
    public int getResultLen(int[] arg){
        return arg.length<=INTEGER_SIZE?INTEGER_SIZE:LONG_SIZE;
    }
    /**
     * shifts array values one position to the left and fills with 0
     * [1,1,0,1] -> [0,1,1,0]
     *    "1011" -> "0110"
     * @param num
     */
    public void leftOneShift(int[] num){
        for(int i=num.length-1;i>0;i--){
            num[i]=num[i-1];
        }
        num[0]=0;
    }
    // Left shift <<

    /**
     * moves numPos positions left the binary number into the integer array
     * @param num the integer array representing a binary number
     * @param numPos positions to shift
     * @return shifted integer array
     */
    public int[] leftShift(int[] num, int numPos) {
        int len=getResultLen(num);
        int bitsToShift=numPos%len;
        int[] out=cast(num,len);
        for(int i=0;i<bitsToShift;i++){
            leftOneShift(out);
        }
        return out;
    }

    /**
     * shifts one position to the right and fills with 0 when negative is false and with 1 when negative is true
     * negative=false
     *      |-  [0,1,1,0,1,0] -> [1,1,0,1,0,0]
     *      |-       "010110" -> "0010011"
     *      |
     *      |-  [1,0,0,1,1,1] -> [0,0,1,1,1,0]
     *      |-       "111001" -> "011100"
     * negative=true
     *      |-  [0,1,1,0,1,0] -> [1,1,0,1,0,1]
     *      |-       "010110" -> "101011"
     *      |
     *      |-  [1,0,0,1,1,1] -> [0,0,1,1,1,1]
     *      |-       "111001" -> "111100"
     *
     * @param num the array to work with
     * @param negative bollean specifing if the empti positions should be filled with 1 or 0
     */
    public void rightOneShift(int[] num,boolean negative){
        for(int i=1;i<num.length;i++){
            num[i-1]=num[i];
        }
        num[num.length-1]=negative?1:0;
    }
    // Unsigned right shift >>>

    /**
     * shifts the given array to the right without conserving the sign
     * @param num the integer array representing a binary number
     * @param numPos number of positions to shift
     * @return original but shifted array
     */
    public int[] unsignedRightShift(int[] num, int numPos) {
        int len=getResultLen(num);
        int bitsToShift=numPos%len;
        int[] out=cast(num,len);

        for(int i=0;i<bitsToShift;i++){
            rightOneShift(out,false);
        }
        return out;
    }

    // Signed right shift >>

    /**
     * shifts an array of integers representing a binary number numPos positions to the right taking into account the
     * original number sign
     * @param num the original integer array
     * @param numPos positions to shifts
     * @return the original array but shifted
     */
    public int[] signedRightShift(int[] num, int numPos) {
        boolean negative=num[num.length-1]==1;
        int len=getResultLen(num);
        int bitsToShift=numPos%len;
        int[] out=cast(num,len);

        for(int i=0;i<bitsToShift;i++){
            rightOneShift(out,negative);
        }
        return out;
    }

    /**********************************************************************
     * TESTING
     **********************************************************************/

    public void run() {
        testToString();
        testAllBits();
        testCopy();
        testNarrow();
        testWiden();
        testCast();
        testAnd();
        testOr();
        testLeftShift();
        testUnsignedRightShift();
        testSignedRightShift();
    }

    // Test functions

    public void testToString() {
        checkToString("00000000",
                "toString(zeroByte())",
                zeroByte());
        checkToString("00000000 00000000",
                "toString(zeroShort())",
                zeroShort());
        checkToString("00000000 00000000 00000000 00000000",
                "toString(zeroInteger())",
                zeroInteger());
        checkToString("00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000",
                "toString(zeroLong())",
                zeroLong());
        checkToString("10 11001010",
                "toString(new int[]{0, 1, 0, 1, 0, 0, 1, 1, 0, 1})",
                new int[]{0, 1, 0, 1, 0, 0, 1, 1, 0, 1});
        printBar();
    }

    public void testAllBits() {
        checkTrue("allBits(new int[] {0, 1, 0, 1, 1})",
                allBits(new int[]{0, 1, 0, 1, 1}));
        checkTrue("allBits(new int[] {})",
                allBits(new int[]{}));
        checkFalse("allBits(new int[] {1, 2, 0})",
                allBits(new int[]{1, 2, 0}));
        printBar();
    }

    public void testCopy() {
        checkCopy(new int[]{1, 1, 0, 0, 1},
                "10011",
                5);
        checkCopy(new int[]{1, 1, 0},
                "10011",
                3);
        checkCopy(new int[]{1, 1, 0, 0, 1, 0, 0},
                "10011",
                7);
        checkCopy(new int[]{0, 0, 0},
                "",
                3);
        checkCopy(new int[]{},
                "10011",
                0);
        checkCopy(new int[]{1, 1, 0, 0, 1, 0},
                "12050811",
                6);
        printBar();
    }

    public void testNarrow() {
        checkNarrow("10011", "10011", 5);
        checkNarrow("011", "10011", 3);
        checkNarrow("", "10011", 0);
        checkNarrowIsCopy();
        printBar();
    }

    public void testWiden() {
        checkWiden("000101", "0101", 6);
        checkWiden("111010", "1010", 6);
        checkWiden("0000", "", 4);
        checkWidenIsCopy();
        printBar();
    }

    private void testCast() {
        checkCast("01", "0101", 2);
        checkCast("000101", "0101", 6);
        checkCast("11", "1111", 2);
        checkCast("111111", "1111", 6);
        checkCast("000000", "", 6);
        checkCast("", "1111", 0);
        checkCastIsCopy();
        printBar();
    }

    private void testAnd() {
        checkAnd(newInteger("00000000 00000000 00000000 00100111"),
                newByte("01110111"),
                newByte("00100111"));
        checkAnd(newInteger("00000000 00000000 00000000 00100111"),
                newByte("01110111"),
                newByte("10100111"));
        checkAnd(newInteger("00000000 00000000 00000000 00100111"),
                newByte("11110111"),
                newByte("00100111"));
        checkAnd(newInteger("11111111 11111111 11111111 10100111"),
                newByte("11110111"),
                newByte("10100111"));
        checkAnd(newInteger("11111111 11111111 11111111 10100111"),
                newByte("11110111"),
                newByte("10100111"));

        checkAnd(newInteger("11111111 11111111 11111100 10100111"),
                newShort("11111100 11110111"),
                newByte("10100111"));

        checkAnd(newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 10100111"),
                newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"),
                newByte("10100111"));
        printBar();
    }

    private void testOr() {
        checkOr(newInteger("00000000 00000000 00000000 01110111"),
                newByte("01110111"),
                newByte("00100111"));
        checkOr(newInteger("11111111 11111111 11111111 11110111"),
                newByte("01110111"),
                newByte("10100111"));
        checkOr(newInteger("11111111 11111111 11111111 11110111"),
                newByte("11110111"),
                newByte("00100111"));
        checkOr(newInteger("11111111 11111111 11111111 11110111"),
                newByte("11110111"),
                newByte("10100111"));
        checkOr(newInteger("11111111 11111111 11111111 11110111"),
                newByte("11110111"),
                newByte("10100111"));

        checkOr(newInteger("11111111 11111111 11111111 11110111"),
                newShort("11111100 11110111"),
                newByte("10100111"));

        checkOr(newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"), newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"),
                newByte("00100111"));
        printBar();
    }

    public void testLeftShift() {
        checkLeftShift(newInteger("00000000 00000000 00000000 00110101"),
                newByte("00110101"),
                0);
        checkLeftShift(newInteger("00000000 00000000 00000110 10100000"),
                newByte("00110101"),
                5);
        checkLeftShift(newInteger("11111111 11111111 11110110 10100000"),
                newByte("10110101"),
                5);
        checkLeftShift(newInteger("11111111 11111111 11110110 10100000"),
                newByte("10110101"),
                69);
        checkLeftShift(newInteger("00000000 00100110 01011010 10000000"),
                newShort("01001100 10110101"),
                7);

        checkLeftShift(newLong("10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000"),
                newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"),
                63);
        checkLeftShiftIsCopy();
        printBar();
    }

    private void testUnsignedRightShift() {
        checkUnsignedRightShift(newInteger("00000000 00000000 00000000 00110101"),
                newByte("00110101"),
                0);
        checkUnsignedRightShift(newInteger("00000000 00000000 00000000 00000001"),
                newByte("00110101"),
                5);
        checkUnsignedRightShift(newInteger("00000111 11111111 11111111 11111101"),
                newByte("10110101"),
                5);
        checkUnsignedRightShift(newInteger("00000111 11111111 11111111 11111101"),
                newByte("10110101"),
                69);
        checkUnsignedRightShift(newInteger("00000000 00000000 00000000 10011001"),
                newShort("01001100 10110101"),
                7);

        checkUnsignedRightShift(newLong("00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001"),
                newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"),
                63);
        checkUnsignedRightShiftIsCopy();
        printBar();
    }

    private void testSignedRightShift() {
        checkSignedRightShift(newInteger("00000000 00000000 00000000 00110101"),
                newByte("00110101"),
                0);
        checkSignedRightShift(newInteger("00000000 00000000 00000000 00000001"),
                newByte("00110101"),
                5);
        checkSignedRightShift(newInteger("11111111 11111111 11111111 11111101"),
                newByte("10110101"),
                5);
        checkSignedRightShift(newInteger("11111111 11111111 11111111 11111101"),
                newByte("10110101"),
                69);
        checkSignedRightShift(newInteger("00000000 00000000 00000000 10011001"),
                newShort("01001100 10110101"),
                7);

        checkSignedRightShift(newLong("11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111"),
                newLong("11111111 00000000 11111111 00000000 11111111 00000000 11111100 11110111"),
                63);
        checkSignedRightShiftIsCopy();
        printBar();
    }

    // Checking functions

    public void checkToString(String expected, String expression, int[] num) {
        String actual = toString(num);
        if (expected.equals(actual)) {
            printlnOk(expression);
        } else {
            printlnError("\"" + expression + "\" should be \"" + expected + "\" but is \"" + actual + "\"");
        }
    }

    public void checkBoolean(boolean expected, String expression, boolean actual) {
        if (expected == actual) {
            printlnOk(expression);
        } else {
            printlnError("\"" + expression + "\" should be " + expected);
        }
    }

    public void checkTrue(String expression, boolean actual) {
        checkBoolean(true, expression, actual);
    }

    public void checkFalse(String expression, boolean actual) {
        checkBoolean(false, expression, actual);
    }

    private void checkCopy(int[] expected, String from, int arraySize) {
        String expression = "copy(\"" + from + "\", array of length " + arraySize + ")";
        int[] actual = new int[arraySize];
        copy(from, actual);
        if (Arrays.equals(expected, actual)) {
            printlnOk(expression);
        } else {
            printlnError(expression + " should be " + Arrays.toString(expected) + " but is " + Arrays.toString(actual));
        }
    }

    private void checkNarrow(String expected, String fromString, int toLength) {
        int[] from = zeroOfSize(fromString.length());
        copy(fromString, from);
        int[] actual = narrow(from, toLength);
        String expression = "narrow(\"" + fromString + "\", " + toLength + ")";
        report(expected, expression, actual);
    }

    private void checkNarrowIsCopy() {
        int[] from = new int[]{0, 1, 0};
        int[] to = narrow(from, from.length);
        checkIsCopy("Narrow", from, to);
    }

    private void checkWiden(String expected, String fromString, int toLength) {
        int[] from = zeroOfSize(fromString.length());
        copy(fromString, from);
        int[] actual = widen(from, toLength);
        String expression = "widen(\"" + fromString + "\", " + toLength + ")";
        report(expected, expression, actual);
    }

    private void checkWidenIsCopy() {
        int[] from = new int[]{0, 1, 0};
        int[] to = widen(from, from.length);
        checkIsCopy("Widen", from, to);
    }

    private void checkCast(String expected, String fromString, int toLength) {
        int[] from = zeroOfSize(fromString.length());
        copy(fromString, from);
        int[] actual = cast(from, toLength);
        String expression = "cast(\"" + fromString + "\", " + toLength + ")";
        report(expected, expression, actual);
    }

    public void report(String expected, String expression, int[] actual) {
        String actualString = toString(actual);
        if (expected.equals(actualString)) {
            printlnOk(expression);
        } else {
            printlnError(expression + " should be \"" + expected + "\" but is \"" + actualString + "\"");
        }
    }

    private void checkCastIsCopy() {
        int[] from = new int[]{0, 1, 0};
        int[] to = cast(from, from.length);
        checkIsCopy("Cast", from, to);
    }

    public void checkIsCopy(String op, int[] from, int[] to) {
        from[0] = 1 - from[0];
        if (from[0] != to[0]) {
            printlnOk(op + " does copy and does not return the same");
        } else {
            printlnError(op + " should copy and not return the same");
        }
    }

    private void checkAnd(int[] expected, int[] arg1, int[] arg2) {
        checkBinaryOp(expected, "and", arg1, arg2, and(arg1, arg2));
    }

    private void checkOr(int[] expected, int[] arg1, int[] arg2) {
        checkBinaryOp(expected, "or", arg1, arg2, or(arg1, arg2));
    }

    private void checkBinaryOp(int[] expected, String op, int[] arg1, int[] arg2, int[] actual) {
        String expression = op + "(\"" + toString(arg1) + "\", \"" + toString(arg2) + "\")";
        report(expected, expression, actual);
    }

    public void report(int[] expected, String expression, int[] actual) {
        if (Arrays.equals(expected, actual))
            printlnOk(expression +
                    "\n\tis \"" + toString(actual) + "\"");
        else
            printlnError(expression +
                    "\n\tshould be \"" + toString(expected) +
                    "\n\tbut is    \"" + toString(actual));
    }

    public void checkShift(int[] expected, String op, int[] num, int numPos, int[] actual) {
        String expression = op + "(\"" + toString(num) + "\", " + numPos + ")";
        report(expected, expression, actual);
    }

    public void checkLeftShift(int[] expected, int[] num, int numPos) {
        checkShift(expected, "leftShift", num, numPos, leftShift(num, numPos));
    }

    private void checkLeftShiftIsCopy() {
        int[] num = zeroByte();
        int[] result = leftShift(num, 0);
        checkIsCopy("leftShift", num, result);
    }

    public void checkUnsignedRightShift(int[] expected, int[] num, int numPos) {
        checkShift(expected, "unsignedRightShift", num, numPos, unsignedRightShift(num, numPos));
    }


    private void checkUnsignedRightShiftIsCopy() {
        int[] num = zeroByte();
        int[] result = unsignedRightShift(num, 0);
        checkIsCopy("unsignedRightShift", num, result);
    }

    public void checkSignedRightShift(int[] expected, int[] num, int numPos) {
        checkShift(expected, "signedRightShift", num, numPos, signedRightShift(num, numPos));
    }


    private void checkSignedRightShiftIsCopy() {
        int[] num = zeroByte();
        int[] result = signedRightShift(num, 0);
        checkIsCopy("signedRightShift", num, result);
    }

    // Colorize output for CommanLineProgram (visible in Netbeans Output)

    public String ANSI_RESET = "\u001B[0m";
    public String ANSI_RED = "\u001B[31m";
    public String ANSI_GREEN = "\u001B[32m";

    public void printlnOk(String message) {
        if (acm.program.CommandLineProgram.class.isInstance(this))
            println(ANSI_GREEN + "OK: " + message + ANSI_RESET);
        else
            println("OK: " + message);
    }

    public void printlnError(String message) {
        if (acm.program.CommandLineProgram.class.isInstance(this))
            println(ANSI_RED + "ERROR: " + message + ANSI_RESET);
        else
            println("ERROR: " + message);
    }

    public void printBar() {
        println("--------------------------------------------------");
    }

    // Entry point to avoid problems in some platforms

    public static void main(String[] args) {
        new IntegralTypes().start(args);
    }
}