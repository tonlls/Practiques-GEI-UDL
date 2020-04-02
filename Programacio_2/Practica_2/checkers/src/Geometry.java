import acm.graphics.GDimension;
import acm.graphics.GPoint;

public class Geometry {

    private final int windowWidth;
    private final int windowHeight;
    private final int numCols;
    private final int numRows;
    private final double boardPadding;
    private final double cellPadding;

    public Geometry(int windowWidth, int windowHeight, int numCols, int numRows, double boardPadding, double cellPadding) {
        this.windowWidth=windowWidth;
        this.windowHeight=windowHeight;
        this.numCols=numCols;
        this.numRows=numRows;
        this.boardPadding=boardPadding;
        this.cellPadding=cellPadding;
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public int getRows() {
        return numRows;
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public int getColumns() {
        return numCols;
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GDimension boardDimension() {
        return new GDimension(windowWidth-(windowWidth*boardPadding*2),windowHeight-(windowHeight*boardPadding*2));
        //return new GDimension(getColumns(),getRows());
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GPoint boardTopLeft() {
        return new GPoint(windowWidth*boardPadding,windowHeight*boardPadding);
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GDimension cellDimension() {
        GDimension board=boardDimension();
        return new GDimension(board.getWidth()/getColumns(),board.getHeight()/getRows());
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GPoint cellTopLeft(int x, int y) {
        GDimension dim=cellDimension();
        GPoint start=boardTopLeft();
        return new GPoint(start.getX()+x*dim.getWidth(),start.getY()+y*dim.getHeight());
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GDimension tokenDimension() {
        GDimension dim=cellDimension();
        return new GDimension(dim.getWidth()-(dim.getWidth()*cellPadding*2),dim.getHeight()-(dim.getHeight()*cellPadding*2));
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GPoint tokenTopLeft(int x, int y) {
        GPoint cell=cellTopLeft(x,y);
        GDimension dim=cellDimension();
        return new GPoint(cell.getX()+(dim.getWidth()*cellPadding),cell.getY()+(dim.getHeight()*cellPadding));
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public GPoint centerAt(int x, int y) {
        GPoint pos=cellTopLeft(x,y);
        GDimension dim=cellDimension();
        return new GPoint(pos.getX()+(dim.getWidth()/2),pos.getY()+(dim.getHeight()/2));
        //throw new UnsupportedOperationException("TODO: Step6");
    }

    public Position xyToCell(double x, double y) {
        GPoint boardTopLeft = boardTopLeft();
        GDimension cellDimension = cellDimension();
        return new Position(
                (int) ((x - boardTopLeft.getX()) / cellDimension.getWidth()),
                (int) ((y - boardTopLeft.getY()) / cellDimension.getHeight()));
    }
}
