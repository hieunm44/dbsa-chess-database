import chess
import chess.pgn
import random
import psycopg2
import psycopg2.extras

# Database connection parameters
db_params = {
    "dbname": "ExtensionTest",
    "user": "postgres",
    "password": "1122",
    "host": "localhost",  # or your database server address
    "port": "5432"
}

def generate_chess_game():
    game = chess.pgn.Game()
    board = chess.Board()

    # Randomize the length of the game
    max_moves = random.randint(10, 70)

    while not board.is_game_over(claim_draw=True) and board.fullmove_number < max_moves:
        # Generate a list of all legal moves
        legal_moves = list(board.legal_moves)
        if legal_moves:
            # Select a random legal move
            move = random.choice(legal_moves)
            # Play the move
            board.push(move)
            # Add the move to the game
            game.end().add_variation(move)
        else:
            # No legal moves available, break out of the loop
            break

    return game

def game_to_pgn_string(game):
    # Exporting the game to PGN string
    exporter = chess.pgn.StringExporter(headers=True, variations=True, comments=False)
    pgn_string = game.accept(exporter)
    
    # Extracting only the moves from the PGN string
    lines = pgn_string.split('\n')
    move_lines = [line for line in lines if not line.startswith('[') and line.strip()]
    moves_only = ' '.join(move_lines)
    return moves_only

def insert_games_to_db(games, table):
    connection = None
    try:
        # Connect to the database
        connection = psycopg2.connect(**db_params)
        cursor = connection.cursor()

        # Prepare the INSERT query based on the table name
        insert_query = f"INSERT INTO {table} (game_notation) VALUES %s"

        # Execute the query in batches
        psycopg2.extras.execute_values(cursor, insert_query, games, template=None, page_size=100)
        connection.commit()
        print(f"{len(games)} games inserted into {table} successfully.")

    except psycopg2.DatabaseError as error:
        print(f"Error: {error}")
        connection.rollback()
    finally:
        # Close the connection
        if connection is not None:
            connection.close()

# Function to ask the user for input
def ask_user():
    populate_chess_games = input("Do you want to populate the chess_games table? (yes/no): ").lower() == 'yes'
    chess_games_count = int(input("How many chess games do you want to insert? ")) if populate_chess_games else 0

    populate_favorite_games = input("Do you want to populate the favorite_games table? (yes/no): ").lower() == 'yes'
    favorite_games_count = int(input("How many favorite games do you want to insert? ")) if populate_favorite_games else 0

    return chess_games_count, favorite_games_count

# Main execution
chess_games_count, favorite_games_count = ask_user()

if chess_games_count > 0:
    chess_games = [(game_to_pgn_string(generate_chess_game()),) for _ in range(chess_games_count)]
    insert_games_to_db(chess_games, 'chess_games')

if favorite_games_count > 0:
    favorite_games = [(game_to_pgn_string(generate_chess_game()),) for _ in range(favorite_games_count)]
    insert_games_to_db(favorite_games, 'favorite_games')
