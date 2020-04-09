import javafx.geometry.Pos;

import java.util.ArrayList;
import java.util.List;

public class Game {

    private static final Direction[] WHITE_DIRECTIONS = {Direction.NW, Direction.NE};
    private static final Direction[] BLACK_DIRECTIONS = {Direction.SW, Direction.SE};

    private final Board board;
    private Player currentPlayer;
    private boolean hasWon;

    public Game(Board board) {
        this.board=board;
        this.currentPlayer=Player.WHITE;
        this.hasWon=false;
    }

    public Player getCurrentPlayer() {
        return this.currentPlayer;
    }

    //el isValidFrom depen del jugador per aixo falla
    public boolean whiteHasNoMoves(){
        Position pos;
        for(int y=0;y<board.getHeight();y++){
            for(int x=0;x<board.getWidth();x++){
                pos=new Position(x,y);
                if(board.isWhite(pos)&&isValidFrom(pos))return false;
            }
        }
        return true;
    }

    public boolean whiteHasWon(){
        int y=0;
        if(board.getNumBlacks() == 0)return true;
        for(int x=0;x < board.getWidth();x++){
            if(board.isWhite(new Position(x,y)))return true;
        }
        //return blackHasNoMoves();
        return false;
    }
    public boolean blackHasNoMoves(){
        Position pos;
        for(int y=0;y<board.getHeight();y++){
            for(int x=0;x<board.getWidth();x++){
                pos=new Position(x,y);
                if(board.isBlack(pos)&&isValidFrom(pos))return false;
            }
        }
        return true;
    }
    public boolean blackHasWon(){
        int y=board.getHeight() - 1;
        if(board.getNumWhites() == 0)return true;
        for(int x=0;x < board.getWidth();x++){
            if(board.isBlack(new Position(x,y)))return true;
        }
        //return !whiteHasNoMoves();
        return false;
    }

    public boolean hasWon() {
        return getCurrentPlayer() == Player.WHITE ? whiteHasWon() : blackHasWon();
    }

    //tocheck
    public boolean isValidFromOcupatedPos(Position position){
        List<Position> positions=new ArrayList<Position>();
        for(Direction d : board.isBlack(position) ? BLACK_DIRECTIONS : WHITE_DIRECTIONS){
            positions.add(d.apply(position));
            positions.add(d.apply(positions.get(positions.size() - 1)));
        }
        return isValidToArray(position,positions);
    }

    public boolean isValidFrom(Position position) {
        if(board.isBlack(position) || board.isWhite(position))
            return isValidFromOcupatedPos(position);
        return false;
    }

    public boolean isValidToArray(Position start, List<Position> end){
        for(Position pos : end){
            if(isValidTo(start,pos))return true;
        }
        return false;
    }

    // Assumes validFrom is a valid starting position
    public boolean isValidTo(Position validFrom, Position to) {
        Position mid=Position.middle(validFrom,to);
        int dist=Position.distance(validFrom,to);
        if(!this.board.isEmpty(to) || !validFrom.sameDiagonalAs(to) || !(getCurrentPlayer() == Player.WHITE ?
                to.getY() < validFrom.getY() : to.getY() > validFrom.getY())) return false;
        return dist == 2 || (dist == 4 && (this.getCurrentPlayer() == Player.WHITE ? this.board.isBlack(mid) : this.board.isWhite(mid)));
    }

    // Assumes both positions are valid
    public Move move(Position validFrom, Position validTo) {
        Position mid=null;
        if(Position.distance(validFrom,validTo) > 2){
            mid=Position.middle(validFrom,validTo);
            board.setEmpty(mid);
        }
        if(board.isWhite(validFrom))
            board.setWhite(validTo);
        else
            board.setBlack(validTo);
        board.setEmpty(validFrom);
        if(!hasWon())
            currentPlayer=getCurrentPlayer()==Player.WHITE?Player.BLACK:Player.WHITE;
        return new Move(validFrom,mid,validTo);
    }

    // Only for testing

    public void setPlayerForTest(Player player) {
        this.currentPlayer = player;
    }
}
