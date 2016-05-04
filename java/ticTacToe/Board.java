import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

/**
 * Created by crisoti on 02/05/16.
 */
public class Board {
    public enum Player { NOT_SET, PLAYER_1, PLAYER_2};

    private int dim = 3;
    private Player[][] positions = new Player[dim][dim];

    public Board() {
        reset();
    }

    private void reset() {
        positions =
                IntStream.range(0, dim)
                .mapToObj(x -> IntStream.range(0, dim)
                                      .mapToObj(y -> Player.NOT_SET)
                                      .toArray(Player[]::new))
                .toArray(Player[][]::new);
    }

    private int getNumMoves() {
        int movesMade = 0;
        for (Player[] boardRow: positions) {
            for (Player p: boardRow) {
                if ((p != null) && (p != Player.NOT_SET)) {
                    ++movesMade;
                }
            }
        }
        return movesMade;
    }

    private Integer getMatchScore(Player winner, Player current) {
        //pre: called if we have a winner`:
        if (winner == current) {
            return 1;
        }
        return -1;
    }

    private Integer horizontalScore(Player currentPlayer) {
        Integer score = null;
        for (int x = 0; x < dim; ++x) {
            // row i
            Player p = positions[x][0];
            if (p != Player.NOT_SET) {
                int y;
                for (y = 1; y < dim; ++y) {
                    if (positions[x][y] != p) {
                        break;
                    }
                }
                if (y == dim) {
                    return getMatchScore(p, currentPlayer);

                }
            }
        }
        return score;
    }

    private Integer verticalScore(Player currentPlayer) {
        Integer score = null;
        for (int y = 0; y < dim; ++y) {
            // row i
            Player p = positions[0][y];
            if (p != Player.NOT_SET) {
                int x;
                for (x = 1; x < dim; ++x) {
                    if (positions[x][y] != p) {
                        break;
                    }
                }
                if (x == dim) {
                    return getMatchScore(p, currentPlayer);
                }
            }
        }
        return score;
    }

    private Integer diagonalScore(Player currentPlayer) {
        Integer score = null;

        Player p = positions[0][0];
        if (p != Player.NOT_SET) {
            int x;
            for (x = 1; x < dim; ++x) {
                // row i
                if (positions[x][x] != p) {
                    break;
                }
            }
            if (x == dim) {
                return getMatchScore(p, currentPlayer);
            }
        }

        p = positions[0][dim-1];
        if (p != Player.NOT_SET) {
            int x;
            for (x = 1; x < dim; ++x) {
                // row i
                if (positions[x][dim-1-x] != p) {
                    break;
                }
            }
            if (x == dim) {
                return getMatchScore(p, currentPlayer);
            }
        }

        return score;
    }

    public Integer computeMatchScore(Player currentPlayer) {
        Integer score = null;
        score = horizontalScore(currentPlayer);
        if (score == null) {
            score = verticalScore(currentPlayer);
        }
        if (score == null) {
            score = diagonalScore(currentPlayer);
        }

        if ((score == null) && (getNumMoves() == dim * dim)) {
            // draw
            score = 0;
        }

        return score;
    }
    private void setBoard(Player[][] source) {
        dim = source.length;
        positions = Arrays.stream(source)
                .map((Player[] row) -> row.clone())
                .toArray( (int length) -> new Player[length][]);
    }

    public Board clone() {
        Board b = new Board();
        b.setBoard(positions);
        return b;
    }

    public int getDim() {
        return dim;
    }

    public Player get(int x, int y) {
        return positions[x][y];
    }


    public void set(int x, int y, Player p) {
        positions[x][y] = p;
    }


    public static Player getNextPlayer(Player p) {
        switch(p) {
            case PLAYER_1:
                return Player.PLAYER_2;
            case PLAYER_2:
                return Player.PLAYER_1;
            default:
                return null;
        }
    }

    private static int score(final Board b, final Player p) {
        Integer score = b.computeMatchScore(p);
        if (score != null) {
            return score;
        }

        final AtomicInteger totalScore = new AtomicInteger(0);
        int dim = b.getDim();
        Player nextPlayer = Board.getNextPlayer(p);
        IntStream.range(0, dim * dim).forEach(
            n -> {
                int x = n / dim;
                int y = n % dim;
                Player pCur = b.get(x, y);
                if (pCur == Player.NOT_SET) {
                    Board nextBoard = b.clone();
                    nextBoard.set(x, y, p);

                    // compute other's player score of winning * (-1)
                    // to get p's winning score
                    totalScore.addAndGet(-score(nextBoard, nextPlayer));
                }
            }
        );
        return totalScore.get();
    }

    public static Board min(Board b1, Board b2, Player p) {
        if (Board.score(b1,p) < Board.score(b2, p)) {
            return b1;
        }
        return b2;
    }

    public static Board bestMove(final Board board, final Player p) {
        Integer score = board.computeMatchScore(p);
        if (score != null) {
            // no more moves
            return null;
        }

        int dim = board.getDim();
        ArrayList<Board> nextBoards = new ArrayList<Board>();
        IntStream.range(0, dim * dim).forEach(
                n -> {
                    int x = n / dim;
                    int y = n % dim;
                    Player pCur = board.get(x, y);
                    if (pCur == Player.NOT_SET) {
                        Board nextBoard = board.clone();
                        nextBoard.set(x, y, p);
                        nextBoards.add(nextBoard);
                    }
                }
        );

        final Player nextPlayer = Board.getNextPlayer(p);
        Board bestBoard = nextBoards.stream().min(
                // want to pick the one where other player's score is lowest
                (Board b1, Board b2) ->
                    score(b2, nextPlayer) - score(b1, nextPlayer)
        ).get();
        bestBoard = bestBoard.clone();
        return bestBoard;
    }

    public void print() {
        for(Player[] boardRow: positions) {
            for (Player p: boardRow) {
                char c;
                switch (p) {
                    case PLAYER_1:
                        c = 'X';
                        break;
                    case PLAYER_2:
                        c = 'O';
                        break;
                    case NOT_SET:
                        c = '_';
                        break;
                    default:
                        c = '!';
                        break;
                }
                System.out.print(c + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Board board = new Board();
        Player[][] b = {
                {Player.PLAYER_1, Player.NOT_SET, Player.PLAYER_2},
                {Player.NOT_SET, Player.PLAYER_1, Player.PLAYER_2},
                {Player.NOT_SET, Player.NOT_SET, Player.NOT_SET}
        };
        System.out.println("Initial state:");
        board.setBoard(b);
        board.print();

        Board bestBoard = Board.bestMove(board, Player.PLAYER_1);
        System.out.println("Player 1's best move:");
        bestBoard.print();
    }
}


