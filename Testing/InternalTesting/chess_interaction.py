import io
import sys
import chess
import chess.pgn

def get_board_state(pgn_str, half_moves):
    # Load the PGN string into a chess game
    game = chess.pgn.read_game(io.StringIO(pgn_str))

    # Create a new board
    board = game.board()

    # Play the moves up to the specified half-move
    for move_num, move in enumerate(game.mainline_moves()):
        if move_num == half_moves:
            break
        board.push(move)

    # Get the FEN string of the current position
    fen_string = board.fen()

    print(fen_string)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python chess_interaction.py <PGN string> <half moves>")
        sys.exit(1)

    pgn_string = sys.argv[1]
    half_moves = int(sys.argv[2])

    get_board_state(pgn_string, half_moves)