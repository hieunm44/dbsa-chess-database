import io
import sys
import chess
import chess.pgn

def get_board_state(pgn_str):
    # Load the PGN string into a chess game
    game = chess.pgn.read_game(io.StringIO(pgn_str))

    # Create a new board
    board = game.board()

    # Play the moves up to the specified half-move
    for move_num, move in enumerate(game.mainline_moves()):
        board.push(move)

    # Get the FEN string of the current position
    fen_string = board.fen()

    print(fen_string)


def get_fen_from_san(san):
    if not san.strip():
        return 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'  # Default FEN for empty input\n"
    
    game = chess.pgn.read_game(io.StringIO(san))
    board = game.board()
    for move in game.mainline_moves():
        board.push(move)


    fen_string = board.fen()
    print(fen_string)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python SanToFen.py <PGN string>")
        sys.exit(1)

    pgn_string = sys.argv[1]

    get_board_state(pgn_string + '\n')
    get_fen_from_san(pgn_string)