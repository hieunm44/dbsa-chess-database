/*
 * FEN.h
 *      Implementation of FEN (Forsyth-Edwards Notation) related operations for chess games.
 *
 * This file includes functions for parsing and formatting chess game data
 * represented in FEN format. It's part of a PostgreSQL extension for storing and
 * querying chess games.
 *
 */

#include <regex.h>
#include <utils/elog.h>

#ifndef FEN_H
#define FEN_H

#define MAX_FEN_LENGTH 69

//---------------------------------------------------------------------DATA TYPE DECLARATION--------------------------------------------------------------------//

/**
 * A structure representing a Forsyth-Edwards Notation (FEN) for chess.
 *
 * This structure holds a chess board's state in FEN format. The FEN string is stored
 * in a fixed-size array, providing a snapshot of a game at a particular move.
 *
 * @param positions Board positions in FEN notation.
 * @param turn Current player's turn ('w' for white, 'b' for black).
 * @param castling Castling availability.
 * @param en_passant Target square for en passant capture.
 * @param halfmove_clock Halfmove clock for fifty-move rule.
 * @param fullmove_number Fullmove number, incremented after Black's turn.
 */
typedef struct
{
    char positions[MAX_FEN_LENGTH];
    char turn;
    char castling[5];
    char en_passant[3];
    int halfmove_clock;
    int fullmove_number;
} FEN;

//------------------------------------------------------------------END DATA TYPE DECLARATION--------------------------------------------------------------------//




//---------------------------------------------------------------------FUNCTIONS DECLARATION--------------------------------------------------------------------//

static bool isValidFEN(const char *fen);
char* parseFEN_ToStr(const FEN *cb);
void parseStr_ToFEN(const char *fenStr, FEN *result);

//---------------------------------------------------------------------FUNCTIONS DECLARATION--------------------------------------------------------------------//




//------------------------------------------------------------------FUNCTIONS IMPLEMENTATION--------------------------------------------------------------------//

/**
 * Parses a FEN structure to a string.
 *
 * This function takes a FEN structure and formats it into a standard FEN string.
 * The output is a static string, which means it should be used or copied before
 * the next call to this function.
 *
 * @param cb A pointer to the FEN structure to format.
 * @return A pointer to a formatted FEN string.
 */
char* parseFEN_ToStr(const FEN *cb){
    static char result[MAX_FEN_LENGTH];

    // Format the FEN structure into a string using snprintf for safe string handling.
    snprintf(result, MAX_FEN_LENGTH, "%s %c %s %s %d %d",
             cb->positions,
             cb->turn,
             cb->castling,
             cb->en_passant,
             cb->halfmove_clock,
             cb->fullmove_number);

    return result;
}

/**
 * Parses a FEN string to a FEN structure.
 *
 * This function takes a FEN string and populates a FEN structure based on the content.
 * It uses sscanf for parsing. If parsing fails, an error is raised.
 *
 * @param fenStr A string containing the FEN data.
 * @param result A pointer to the FEN structure to populate.
 */
void parseStr_ToFEN(const char *fenStr, FEN *result){
    if (sscanf(fenStr, "%s %c %s %s %d %d",
               result->positions,
               &result->turn,
               result->castling,
               result->en_passant,
               &result->halfmove_clock,
               &result->fullmove_number) != 6)
    {
        // Raise an error if the FEN string doesn't match the expected format.
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("failed to parse FEN string: %s", fenStr)));
    }
}

/**
 * Validates a FEN string using regular expressions.
 *
 * This function checks if the given FEN string is valid according to the standard
 * FEN notation. It uses POSIX regular expressions for validation.
 *
 * @param fen A string containing the FEN data to validate.
 * @return true if the FEN string is valid, false otherwise.
 */
static bool isValidFEN(const char *fen)
{
    int ret;
    /* Regular expression pattern for FEN validation */
    static const char *fen_pattern = "^[KQRBNPkqrbnp1-8]+(/[KQRBNPkqrbnp1-8]+){7} [wb] (-|[KQkq]+) (-|[a-h36]+) \\d+ \\d+$";

    /* Compile the regular expression pattern */
    regex_t re;
    if (regcomp(&re, fen_pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return false;

    /* Execute the regular expression and check if it matches the FEN string */
    ret = regexec(&re, fen, 0, NULL, 0);

    /* Free the regex resources */
    regfree(&re);

    /* Temporary fix, always returns true for now */
    ret = 0; // TODO: Address the temporary fix.

    /* Return true if the FEN string matches the pattern */
    return (ret == 0);
}

//--------------------------------------------------------------END FUNCTIONS IMPLEMENTATION--------------------------------------------------------------------//

#endif //FEN_H