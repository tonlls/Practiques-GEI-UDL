import java.util.StringTokenizer;

// Only a rectangle of cells. Does not know the game rules.

public class Board {

    private final int width;
    private final int height;
    private final Cell[][] cells;
    private int numBlacks;
    private int numWhites;

    public Board(int width, int height, String board) {
        this.width=width;
        this.height=height;
        this.cells=new Cell[height][width];
        this.buildCells(board);

    }

    private void buildCells(String board) {
        int x=0,y=0;
        Cell cell;
        for(char c:board.toCharArray()){
            if(c == '\n'){
                y++;
                x=0;
            }
            else{
                cell=Cell.fromChar(c);
                this.cells[y][x++]=cell;
                countCell(cell);
            }
        }
    }

    private void countCell(Cell c){
        if(c.isWhite())this.numWhites++;
        else if(c.isBlack())this.numBlacks++;
    }
    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public int getNumBlacks() {
        return this.numBlacks;
    }

    public int getNumWhites() {
        return this.numWhites;
    }

    public boolean isOutOfBounds(Position pos){
        return pos.getY() < 0 || pos.getY() >= this.getHeight() || pos.getX() < 0 || pos.getX() >= this.getWidth();
    }

    public boolean isForbidden(Position pos) {
        return this.isOutOfBounds(pos) || this.cells[pos.getY()][pos.getX()].isForbidden();
    }

    public boolean isBlack(Position pos) {
        return !this.isOutOfBounds(pos) && this.cells[pos.getY()][pos.getX()].isBlack();
    }

    public boolean isWhite(Position pos) {
        return !this.isOutOfBounds(pos) && this.cells[pos.getY()][pos.getX()].isWhite();
    }

    public boolean isEmpty(Position pos) {
        return !this.isOutOfBounds(pos) && this.cells[pos.getY()][pos.getX()].isEmpty();
    }

    private void positionEdited(Position pos){
        if(isWhite(pos))numWhites--;
        else if(isBlack(pos))numBlacks--;
    }

    public void setBlack(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.BLACK;
        numBlacks++;
    }

    public void setWhite(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.WHITE;
        numWhites++;
    }

    public void setEmpty(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.EMPTY;
    }

    // For testing and debugging

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                sb.append(cells[y][x].toString());
            }
            if (y != height - 1) {
                sb.append("\n");
            }
        }
        return sb.toString();
    }
}