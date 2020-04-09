import javafx.geometry.Pos;

public class Position {

    private final int x;
    private final int y;

    public Position(int x, int y) {
        this.x=x;
        this.y=y;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }
    public boolean same(Position other){
        return this.getX() == other.getX() && this.getY() == other.getY();
    }

    public boolean sameDiagonalAs(Position other) {
        if((this.getX() == other.getX() || this.getY() == other.getY()) && !this.same(other))
            return false;
        return Math.abs(this.getX() - other.getX()) == Math.abs(this.getY() - other.getY());
    }

    public static int distance(Position pos1, Position pos2) {
        return Math.abs(pos1.getX() - pos2.getX()) + Math.abs(pos1.getY() - pos2.getY());
    }

    public static Position middle(Position pos1, Position pos2) {
        return new Position((pos1.getX() + pos2.getX()) / 2,(pos1.getY() + pos2.getY()) / 2);
    }

    // Needed for testing and debugging

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Position position = (Position) o;
        return x == position.x && y == position.y;
    }

    @Override
    public String toString() {
        return "Position{" +
                "x=" + x +
                ", y=" + y +
                '}';
    }
}

