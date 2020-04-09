public class Cell {

    private static final char C_FORBIDDEN = '·';
    private static final char C_EMPTY = ' ';
    private static final char C_WHITE = 'w';
    private static final char C_BLACK = 'b';

    public static final Cell FORBIDDEN = new Cell(C_FORBIDDEN);
    public static final Cell EMPTY = new Cell(C_EMPTY);
    public static final Cell WHITE = new Cell(C_WHITE);
    public static final Cell BLACK = new Cell(C_BLACK);

    private final char status;

    private Cell(char status) {
        this.status=status;
    }

    public static Cell fromChar(char status) {
        switch (status){
            case C_FORBIDDEN: return Cell.FORBIDDEN;
            case C_EMPTY: return Cell.EMPTY;
            case C_BLACK: return Cell.BLACK;
            case C_WHITE: return Cell.WHITE;
        }
        return null;
    }

    public boolean isForbidden() {
        return this.status == C_FORBIDDEN;
    }

    public boolean isEmpty() {
        return this.status == C_EMPTY;
    }

    public boolean isWhite() {
        return this.status == C_WHITE;
    }

    public boolean isBlack() {
        return this.status == C_BLACK;
    }

    @Override
    public String toString() {
        return String.valueOf(status);
    }
}