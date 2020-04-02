import java.util.StringTokenizer;

// Only a rectangle of cells. Does not know the game rules.

public class Board {

    private final int width;
    private final int height;
    private final Cell[][] cells;
    private int numBlacks;
    private int numWhites;

    public Board(int width, int height, String board) {
        Cell cell;
        this.width=width;
        this.height=height;
        this.cells=new Cell[height][width];
        int x=0,y=0;
        for(char c:board.toCharArray()){
            if(c=='\n'){
                y++;
                x=0;
            }
            else{
                cell=Cell.fromChar(c);
                this.cells[y][x++]=cell;
                countCell(cell);
            }
        }
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    private void countCell(Cell c){
        if(c.isWhite())this.numWhites++;
        else if(c.isBlack())this.numBlacks++;
    }
    public int getWidth() {
        return this.width;
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public int getHeight() {
        return this.height;
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public int getNumBlacks() {
        return this.numBlacks;
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public int getNumWhites() {
        return this.numWhites;
        //throw new UnsupportedOperationException("TODO: Step4");
    }
    public boolean isOutOfBounds(Position pos){
        return pos.getY()<0||pos.getY()>=this.getHeight()||pos.getX()<0||pos.getX()>=this.getWidth();
    }
    public boolean isForbidden(Position pos) {
        return this.isOutOfBounds(pos)||this.cells[pos.getY()][pos.getX()].isForbidden();
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public boolean isBlack(Position pos) {
        return !this.isOutOfBounds(pos)&&this.cells[pos.getY()][pos.getX()].isBlack();
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public boolean isWhite(Position pos) {
        return !this.isOutOfBounds(pos)&&this.cells[pos.getY()][pos.getX()].isWhite();
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public boolean isEmpty(Position pos) {
        return !this.isOutOfBounds(pos)&&this.cells[pos.getY()][pos.getX()].isEmpty();

        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public void positionEdited(Position pos){
        if(isWhite(pos))numWhites--;
        else if(isBlack(pos))numBlacks--;
    }

    public void setBlack(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.BLACK;
        numBlacks++;
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public void setWhite(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.WHITE;
        numWhites++;
        //throw new UnsupportedOperationException("TODO: Step4");
    }

    public void setEmpty(Position pos) {
        positionEdited(pos);
        this.cells[pos.getY()][pos.getX()]=Cell.EMPTY;
        //throw new UnsupportedOperationException("TODO: Step4");
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