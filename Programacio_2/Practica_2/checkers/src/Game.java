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
                if(board.isWhite(pos)&&canMove(pos))return false;
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

        return blackHasNoMoves();
    }
    public boolean blackHasNoMoves(){
        Position pos;
        for(int y=0;y<board.getHeight();y++){
            for(int x=0;x<board.getWidth();x++){
                pos=new Position(x,y);
                if(board.isBlack(pos)&&canMove(pos))return false;
            }
        }
        return true;
    }
    private boolean blackHasWon(){
        int y=board.getHeight() - 1;
        if(board.getNumWhites() == 0)return true;
        for(int x=0;x < board.getWidth();x++){
            if(board.isBlack(new Position(x,y)))return true;
        }
        return whiteHasNoMoves();
    }

    public boolean hasWon() {
        return this.hasWon;
    }


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
    private boolean canMove(Position pos){
            if(board.isWhite(pos)){
                return board.isEmpty(WHITE_DIRECTIONS[0].apply(pos))
                || board.isEmpty(WHITE_DIRECTIONS[1].apply(pos))
                || (board.isBlack(WHITE_DIRECTIONS[0].apply(pos)) && board.isEmpty(WHITE_DIRECTIONS[0].apply(WHITE_DIRECTIONS[0].apply(pos))))
                || (board.isBlack(WHITE_DIRECTIONS[1].apply(pos)) && board.isEmpty(WHITE_DIRECTIONS[1].apply(WHITE_DIRECTIONS[1].apply(pos))));
            }else if(board.isBlack(pos)){
                return board.isEmpty(BLACK_DIRECTIONS[0].apply(pos))
                || board.isEmpty(BLACK_DIRECTIONS[1].apply(pos))
                || (board.isWhite(BLACK_DIRECTIONS[0].apply(pos)) && board.isEmpty(BLACK_DIRECTIONS[0].apply(BLACK_DIRECTIONS[0].apply(pos))))
                || (board.isWhite(BLACK_DIRECTIONS[1].apply(pos)) && board.isEmpty(BLACK_DIRECTIONS[1].apply(BLACK_DIRECTIONS[1].apply(pos))));
            }
            return false;
    }


    public boolean isValidToArray(Position start, List<Position> end){
        for(Position pos : end){
            if(isValidTo(start,pos))
                return true;
        }
        return false;
    }

    // Assumes validFrom is a valid starting position
    public boolean isValidTo(Position validFrom,Position to){
        boolean isWhite=getCurrentPlayer()==Player.WHITE;
        //boolean isWhite=board.isWhite(validFrom);
        Position mid=Position.middle(validFrom,to);
        int dist=Position.distance(validFrom,to);
        if(!this.board.isEmpty(to) || !validFrom.sameDiagonalAs(to) || !( isWhite ?
                to.getY() < validFrom.getY() : to.getY() > validFrom.getY())) return false;
        return dist == 2 || (dist == 4 && (isWhite ? this.board.isBlack(mid) : this.board.isWhite(mid)));
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
        this.hasWon=getCurrentPlayer() == Player.WHITE ? whiteHasWon() : blackHasWon();
        if(!hasWon()) {
            currentPlayer=getCurrentPlayer()==Player.WHITE?Player.BLACK:Player.WHITE;
        }
        return new Move(validFrom,mid,validTo);
    }

    // Only for testing

    public void setPlayerForTest(Player player) {
        this.currentPlayer = player;
    }
}
