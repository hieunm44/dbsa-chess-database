/*
 * Implementation of chess game-related functions for a PostgreSQL extension.
 *
 * This source file contains functions to handle chess data types SAN and FEN.
 * It includes input and output functions for these data types, along with utilities
 * for processing chess game notations and board states.
 *
 */

#include "chess.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <access/gin.h>
#include "utils/array.h"
#include <catalog/pg_type_d.h>
#include "Utils/mapping_san_to_fan.h"

/**
 * Compares two SAN (Standard Algebraic Notation) structures.
 *
 * This function compares two SAN structures using string comparison. It uses strncmp 
 * to compare the data fields of two SAN structures up to MAX_PGN_LENGTH characters. 
 * The comparison is performed lexicographically. The function normalizes the return 
 * value to -1, 0, or 1 to indicate the result of the comparison: less than, equal to, 
 * or greater than, respectively. This normalized result is useful for various sorting 
 * and searching algorithms, especially those used in B-tree operations.
 *
 * @param a A pointer to the first SAN structure.
 * @param b A pointer to the second SAN structure.
 * @return An integer value: -1 if 'a' is less than 'b', 1 if 'a' is greater than 'b',
 *         or 0 if 'a' and 'b' are equal.
 */
static int san_compare(SAN *a, SAN *b)
{
    int cmp_result;

    cmp_result =  strncmp(a->data, b->data, MAX_PGN_LENGTH);

    if (cmp_result < 0)
        return -1;
    else if (cmp_result > 0)
        return 1;
    else
        return 0;
}
/**
 * Inputs a SAN string into PostgreSQL.
 *
 * This function takes a SAN string as input and allocates a SAN structure
 * to store the string. It sets the varlena length of the result and copies
 * the PGN string into the flexible array member of the SAN structure.
 *
 * @param fcinfo Function call info containing arguments.
 * @return A SAN structure containing the input string.
 */
Datum san_in(PG_FUNCTION_ARGS)
{
    SAN *result;
    char *pgn_str;

    if (PG_ARGISNULL(0))
        ereport(ERROR, (errmsg("san_in: Argument(0) is null")));

    pgn_str = PG_GETARG_CSTRING(0);

    result = (SAN *) palloc(sizeof(SAN));

    parseStr_ToPGN(pgn_str, result);

    PG_FREE_IF_COPY(pgn_str, 0);

    PG_RETURN_POINTER(result);
}
/**
 * Outputs a SAN string from PostgreSQL.
 *
 * This function retrieves a SAN structure from PostgreSQL and returns
 * the stored SAN string. It duplicates the SAN string to ensure that the
 * returned value is a null-terminated C string.
 *
 * @param fcinfo Function call info containing arguments.
 * @return The SAN string contained in the SAN structure.
 */
Datum san_out(PG_FUNCTION_ARGS)
{
    SAN *game;
    char *result;

    if (PG_ARGISNULL(0))
        ereport(ERROR, (errmsg("san_out: Argument(0) is null")));

    game = PG_GETARG_CHESSGAME_P(0);

    parsePGN_ToStr(game, &result);

    PG_FREE_IF_COPY(game, 0);

    PG_RETURN_CSTRING(result);
}
/**
 * Inputs a FEN string into PostgreSQL.
 *
 * This function takes a FEN string as input, validates it using the 
 * isValidFEN function, and then allocates and populates a FEN structure.
 * If the input FEN string is invalid, an error is reported.
 *
 * @param fcinfo Function call info containing arguments.
 * @return A FEN structure populated based on the input FEN string.
 */
Datum fen_in(PG_FUNCTION_ARGS)
{
    char *str;
    FEN *result;

    if (PG_ARGISNULL(0))
        ereport(ERROR, (errmsg("fen_in: Argument(0) is null")));

    str = PG_GETARG_CSTRING(0);

    if (!isValidFEN(str))
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid FEN representation: %s", str)));

    result = (FEN *)palloc(sizeof(FEN));

    parseStr_ToFEN(str, result);

    PG_FREE_IF_COPY(str, 0);

    PG_RETURN_POINTER(result);
}
/**
 * Outputs a FEN structure as a string in PostgreSQL.
 *
 * This function takes a FEN structure as input and converts it to a string
 * using the parseFEN_ToStr function. The result is duplicated to ensure
 * it is a null-terminated C string suitable for returning to PostgreSQL.
 *
 * @param fcinfo Function call info containing arguments.
 * @return A string representing the FEN structure.
 */
Datum fen_out(PG_FUNCTION_ARGS)
{
    FEN *cb;
    char* result;

    if (PG_ARGISNULL(0))
        ereport(ERROR, (errmsg("fen_out: Argument(0) is null")));

    cb = (FEN *)PG_GETARG_POINTER(0);

    result = parseFEN_ToStr(cb);

    PG_FREE_IF_COPY(cb, 0);

    PG_RETURN_CSTRING(pstrdup(result));
}
/**
 * Checks if a chess game has a specific opening sequence.
 *
 * This function compares two SAN structures to determine if the first one
 * starts with the same set of moves as the second one. It is used to check
 * if a chess game contains a specific opening sequence.
 *
 * @param fcinfo Function call info containing arguments.
 * @return True if the first game starts with the same moves as the second game; false otherwise.
 */
Datum has_opening(PG_FUNCTION_ARGS) 
{
    bool result;
    SAN *game1, *game2;
    int opening_length, full_game_length;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("has_opening: One of the arguments is null")));

    game1 = (SAN*)PG_GETARG_POINTER(0);
    game2 = (SAN*)PG_GETARG_POINTER(1);

    full_game_length = strlen(game1->data);
    opening_length = strlen(game2->data);

    if (full_game_length < opening_length)
        ereport(ERROR, (errmsg("has_opening: game is shorter than opening moves")));

    result = (strncmp(game1->data, game2->data, opening_length) == 0);

    PG_FREE_IF_COPY(game1, 0);
    PG_FREE_IF_COPY(game2, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Retrieves the first N half-moves of a chess game.
 *
 * This function truncates a SAN structure representing a chess game to its
 * first N half-moves. It uses the truncate_san function to create a new SAN
 * structure containing only the specified initial moves.
 *
 * @param fcinfo Function call info containing arguments.
 * @return A new SAN structure containing the first N half-moves of the game.
 */
Datum get_FirstMoves(PG_FUNCTION_ARGS) 
{
    SAN *result, *inputGame;
    int nHalfMoves;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("get_FirstMoves: One of the arguments is null")));
   
    inputGame = (SAN *) PG_GETARG_POINTER(0);
    nHalfMoves = PG_GETARG_INT32(1);

    if (nHalfMoves < 0) 
        ereport(ERROR,(errmsg("get_FirstMoves: Non-positive number of half moves")));

    result = truncate_san(inputGame, nHalfMoves); 

    if (result == NULL)
        ereport(ERROR, (errmsg("Game is incomplete or shorter than the requested number of half-moves")));

    PG_FREE_IF_COPY(inputGame, 0);

    PG_RETURN_POINTER(result);
}
/**
 * Retrieves the board state at a specific half-move in a chess game.
 *
 * This function takes a SAN structure and an integer representing half-moves,
 * truncates the game to the specified number of half-moves, converts it to FEN format,
 * and then returns the resulting board state as a FEN structure.
 *
 * @param fcinfo Function call info containing arguments.
 * @return A FEN structure representing the board state at the specified half-move.
 */
Datum get_board_state(PG_FUNCTION_ARGS) {
    FEN *fen;
    SAN *gameTruncated, *game;

    int half_moves;
    const char *fenConversionStrResult;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("get_board_state: One of the arguments is null")));

    game = (SAN *) PG_GETARG_POINTER(0);
    half_moves = PG_GETARG_INT32(1);

    if (half_moves < 0) 
        ereport(ERROR,(errmsg("get_board_state: Non-positive number of half moves")));

    gameTruncated = truncate_san(game, half_moves); 

    if (gameTruncated == NULL)
        ereport(ERROR, (errmsg("get_board_state: Game is incomplete or shorter than the requested number of half-moves")));

    fenConversionStrResult = san_to_fen(gameTruncated);

    if (fenConversionStrResult == NULL) {
        ereport(ERROR, (errmsg("get_board_state: No FEN result returned from mapping san to fen")));
    }

    fen = (FEN *)palloc(sizeof(FEN));

    parseStr_ToFEN(fenConversionStrResult, fen);

    PG_FREE_IF_COPY(game, 0);

    PG_RETURN_POINTER(fen);
}
/**
 * Checks if a chess game contains a specific board state within the first N half-moves.
 *
 * This function compares the board state of a chess game at a specified number
 * of half-moves with a given board state. It is used to check if a specific
 * board configuration occurs within the first N half-moves of the game.
 *
 * @param fcinfo Function call info containing arguments.
 * @return True if the game contains the given board state within the first N half-moves; false otherwise.
 */
Datum has_Board(PG_FUNCTION_ARGS){
    FEN *current_board, *input_board;
    SAN *gameTruncated, *input_game;

    int input_half_moves;
    bool positions_match;
    const char *fenConversionStrResult;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1) || PG_ARGISNULL(2))
        ereport(ERROR, (errmsg("has_Board: One of the arguments is null")));

    input_game = (SAN*) PG_GETARG_POINTER(0);
    input_board = (FEN*) PG_GETARG_POINTER(1);
    input_half_moves = PG_GETARG_INT32(2);

    if (input_half_moves < 0) 
        ereport(ERROR,(errmsg("hasBoard: Non-positive number of half moves")));

    gameTruncated = truncate_san(input_game, input_half_moves); 

    if (gameTruncated == NULL)
        ereport(ERROR, (errmsg("Game is incomplete or shorter than the requested number of half-moves")));

    fenConversionStrResult = san_to_fen(gameTruncated);

    if (fenConversionStrResult == NULL)
        ereport(ERROR, (errmsg("No FEN result returned from mapping san to fen")));

    current_board = (FEN *)palloc(sizeof(FEN));

    parseStr_ToFEN(fenConversionStrResult, current_board);

    positions_match = strcmp(input_board->positions, current_board->positions) == 0;

    PG_FREE_IF_COPY(input_game, 0);
    PG_FREE_IF_COPY(input_board, 1);

    PG_RETURN_BOOL(positions_match);
}
/**
 * Determines if one SAN type is less than another.
 *
 * Compares two SAN types to check if one is less than the other based on a custom comparison function.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the first SAN type is less than the second; false otherwise.
 */
Datum san_lt(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_lt: One of the arguments is null")));

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    result = san_compare(a, b) > 0;

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Determines if one SAN type is equal to another.
 *
 * Compares two SAN types to check if they are equal based on a custom comparison function.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the two SAN types are equal; false otherwise.
 */
Datum san_eq(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        PG_RETURN_BOOL(false);

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    result = san_compare(a, b) == 0;

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Determines if one SAN type is greater than another.
 *
 * Compares two SAN types to check if one is greater than the other based on a custom comparison function.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the first SAN type is greater than the second; false otherwise.
 */
Datum san_gt(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_gt: One of the arguments is null")));

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    result = san_compare(a, b) > 0;

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Determines if one SAN type is greater or equal than another.
 *
 * Compares two SAN types to check if one is greater or qeual than the other based on a custom comparison function.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the first SAN type is greater or equal than the second; false otherwise.
 */
Datum san_gt_eq(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_gt_eq: One of the arguments is null")));

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    result = san_compare(a, b) >= 0;

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Determines if one SAN type is less or equal than another.
 *
 * Compares two SAN types to check if one is less or equal than the other based on a custom comparison function.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the first SAN type is less or equal than the second; false otherwise.
 */
Datum san_lt_eq(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_gt_eq: One of the arguments is null")));

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    result = san_compare(a, b) <= 0;

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);    

    PG_RETURN_BOOL(result);
}
/**
 * Compares two SAN types and returns the result of the comparison.
 *
 * Compares two SAN types based on a custom comparison function and returns the result of the comparison as an integer.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Integer value: 0 if the two SAN types are equal, a positive value if the first is greater, and a negative value if the second is greater.
 */
Datum san_cmp(PG_FUNCTION_ARGS)
{
    SAN *a, *b;
    int cmp_result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_cmp: One of the arguments is null")));

    a = (SAN *) PG_GETARG_POINTER(0);
    b = (SAN *) PG_GETARG_POINTER(1);

    cmp_result = san_compare(a, b);

    PG_FREE_IF_COPY(a, 0);
    PG_FREE_IF_COPY(b, 1);    

    PG_RETURN_INT32(cmp_result);
}
/**
 * Determines if a SAN type matches a given pattern using the LIKE operation.
 *
 * Compares a SAN type's game notation to a text pattern. Useful for pattern matching operations in queries.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the SAN type matches the pattern; false otherwise.
 */
Datum san_like(PG_FUNCTION_ARGS)
{
    SAN *san;
    text *pattern, *san_text;

    bool result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_like: One of the arguments is null")));

    san = (SAN *) PG_GETARG_POINTER(0);
    pattern = PG_GETARG_TEXT_PP(1);
    san_text = cstring_to_text(san->data);

    result = DatumGetBool(DirectFunctionCall2(textlike, 
                                                   PointerGetDatum(san_text), 
                                                   PointerGetDatum(pattern)));

    pfree(san_text);

    PG_FREE_IF_COPY(san, 0);
    PG_FREE_IF_COPY(pattern, 1);

    PG_RETURN_BOOL(result);
}
/**
 * Determines if a SAN type does not match a given pattern using the NOT LIKE operation.
 *
 * Compares a SAN type's game notation to a text pattern and returns the opposite of the LIKE operation result.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if the SAN type does not match the pattern; false otherwise.
 */
Datum san_not_like(PG_FUNCTION_ARGS)
{
    SAN *san;
    text *pattern, *san_text;

    bool like_result;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("san_not_like: One of the arguments is null")));
    
    san = (SAN *) PG_GETARG_POINTER(0);
    pattern = PG_GETARG_TEXT_PP(1);
    san_text = cstring_to_text(san->data);

    like_result = DatumGetBool(DirectFunctionCall2(textlike, 
                                                        PointerGetDatum(san_text), 
                                                        PointerGetDatum(pattern)));

    pfree(san_text);

    PG_FREE_IF_COPY(san, 0);
    PG_FREE_IF_COPY(pattern, 1);

    PG_RETURN_BOOL(!like_result);
}
/**
 * Extracts FEN strings from a SAN type for each half-move up to the end of the game.
 * 
 * This function iterates over each half-move in a SAN representation of a chess game,
 * truncates the game at each half-move, converts it to FEN format, and accumulates
 * these FEN strings into an array.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Pointer to an array of Datum, each containing a FEN string; or NULL if no moves are available.
 */
Datum fens_from_san(PG_FUNCTION_ARGS){
    int32 *nkeys;
    ArrayBuildState *astate;
    SAN *san, *gameTruncated;

    int i;
    const char *fenConversionStrResult;

    san = (SAN *) PG_GETARG_POINTER(0);
    nkeys = (int32 *) PG_GETARG_POINTER(1);

    i = 0;
    *nkeys = 0;
    astate = NULL;

    while (true) {

        gameTruncated = truncate_san(san, i);

        if (gameTruncated == NULL)
            break;

        fenConversionStrResult = san_to_fen(gameTruncated);

        if (fenConversionStrResult == NULL)
            ereport(ERROR, (errmsg("No FEN result returned from mapping san to fen")));

        astate = accumArrayResult(astate, CStringGetTextDatum(fenConversionStrResult),
                                  false, TEXTOID, CurrentMemoryContext);

        (*nkeys)++;
        i++;
    }

    PG_FREE_IF_COPY(san, 0);

    if (*nkeys > 0) {

        Datum *keys = (Datum *) palloc(*nkeys * sizeof(Datum));

        for (i = 0; i < *nkeys; i++) {
            keys[i] = astate->dvalues[i];
        }

        PG_RETURN_POINTER(keys);

    } else {
        PG_RETURN_NULL();
    }
}
/**
 * Compares two text values for GIN indexing, specifically for chess game keys.
 * 
 * This function is used in the context of GIN index operations to compare two keys
 * (text values) and determine their ordering.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Integer representing the comparison result: -1, 0, or 1.
 */
Datum gin_compare(PG_FUNCTION_ARGS)
{
    text *key1 = PG_GETARG_TEXT_PP(0);
    text *key2 = PG_GETARG_TEXT_PP(1);

    char *key1Str = text_to_cstring(key1);
    char *key2Str = text_to_cstring(key2);

    int32 result = DatumGetInt32(DirectFunctionCall2Coll(btint4cmp,
                                                        PG_GET_COLLATION(),
                                                        PointerGetDatum(key1),
                                                        PointerGetDatum(key2)));

                                                         
    pfree(key1Str);
    pfree(key2Str);

    PG_FREE_IF_COPY(key1, 0);
    PG_FREE_IF_COPY(key2, 1);

    PG_RETURN_INT32(result);
}
/**
 * Extracts indexable keys from a SAN type for GIN indexing.
 * 
 * This function is used for GIN index operations. It extracts FEN representations
 * from a given SAN type and prepares them as keys for indexing.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Pointer to an array of keys (Datum) for GIN indexing.
 */
Datum gin_extract_value(PG_FUNCTION_ARGS) {

    SAN *san;
    Datum *keys;
    int32 *nkeys;
    bool **nullFlags;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1) || PG_ARGISNULL(2))
        ereport(ERROR, (errmsg("gin_extract_value: One of the arguments is null")));

    san = (SAN *) PG_GETARG_POINTER(0);
    nkeys = (int32 *) PG_GETARG_POINTER(1);
    nullFlags = (bool **) PG_GETARG_POINTER(2);

    *nkeys = 0;

    keys = (Datum *) DirectFunctionCall4Coll(fens_from_san, 
                                            PG_GET_COLLATION(), 
                                            PointerGetDatum(san),
                                            PointerGetDatum(nkeys),
                                            BoolGetDatum(false),
                                            PointerGetDatum(NULL)); 

    *nullFlags = NULL;

    PG_FREE_IF_COPY(san, 0);

    PG_RETURN_POINTER(keys);
}
/**
 * Extracts a query key from a FEN type for GIN indexing.
 * 
 * Used in GIN index search operations, this function takes a FEN type,
 * extracts its board position as a key, and prepares it for querying the GIN index.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Pointer to an array of one key (Datum) representing the query.
 */
Datum gin_extract_query(PG_FUNCTION_ARGS) {

    FEN  *itemValue;
    Datum *keys, query;
    int32 *nkeys, *searchMode;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1) || PG_ARGISNULL(2) || PG_ARGISNULL(3) ||
        PG_ARGISNULL(4) || PG_ARGISNULL(5) || PG_ARGISNULL(6)) {
        ereport(ERROR, (errmsg("gin_extract_query: One of the arguments is null")));
    }

    query = PG_GETARG_DATUM(0);
    nkeys = (int32 *) PG_GETARG_POINTER(1);
    itemValue =(FEN *) DatumGetPointer(query);
    searchMode = (int32 *) PG_GETARG_POINTER(6);

    *nkeys = 1;
    keys = (Datum *) palloc(*nkeys * sizeof(Datum));
    keys[0] = CStringGetTextDatum(itemValue->positions);

    *searchMode = GIN_SEARCH_MODE_DEFAULT;

    PG_RETURN_POINTER(keys);
}
/**
 * Checks if indexed keys are consistent with a given query key in GIN index searches.
 * 
 * This function is used to determine if a particular GIN index entry matches the search condition,
 * specifically for chess game positions.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean indicating whether the indexed keys are consistent with the query key.
 */
Datum gin_consistent(PG_FUNCTION_ARGS)
{
    bool *check = (bool *) PG_GETARG_POINTER(0);
    Datum query = PG_GETARG_DATUM(2);
    int32 nkeys = PG_GETARG_INT32(3);
    bool *recheck = (bool *) PG_GETARG_POINTER(5);
    Datum *queryKeys = (Datum *) PG_GETARG_POINTER(6);

    FEN queryFen;
    char *queryFenStr = text_to_cstring(DatumGetTextP(query));
    parseStr_ToFEN(queryFenStr, &queryFen);
    pfree(queryFenStr);

    for (int i = 0; i < nkeys; i++) {
        if (check[i]) {
            FEN keyFen;
            char *keyFenStr = text_to_cstring(DatumGetTextP(queryKeys[i]));
            parseStr_ToFEN(keyFenStr, &keyFen);
            pfree(keyFenStr);

            if (strcmp(queryFen.positions, keyFen.positions) == 0) {
                *recheck = true;
                PG_RETURN_BOOL(true);
            }
        }
    }

    *recheck = true;
    PG_RETURN_BOOL(false);
}
/**
 * Performs a ternary consistency check for GIN index operations.
 * 
 * This function is used in GIN index searches to return a ternary value (MAYBE, TRUE, FALSE)
 * indicating the consistency of the index keys with a given query.
 *
 * @param fcinfo Function call info containing arguments.
 * @return GinTernaryValue indicating the consistency result.
 */
Datum gin_tri_consistent(PG_FUNCTION_ARGS)
{
    GinTernaryValue *check = (GinTernaryValue *) PG_GETARG_POINTER(0);
    Datum query = PG_GETARG_DATUM(2);
    int32 nkeys = PG_GETARG_INT32(3);
    Datum *queryKeys = (Datum *) PG_GETARG_POINTER(5);

    GinTernaryValue result = GIN_MAYBE;

    for (int i = 0; i < nkeys; i++) {
        if (check[i] == GIN_FALSE) 
            return GIN_FALSE;

        if (check[i] == GIN_TRUE) {

            char *queryFenStr = TextDatumGetCString(queryKeys[i]);
            char *gameFenStr = TextDatumGetCString(query);

            if (strcmp(queryFenStr, gameFenStr) == 0) 
                result = GIN_TRUE;
        }
    }

    PG_RETURN_GIN_TERNARY_VALUE(result);
}
/**
 * Determines if a given FEN type matches any board state in a SAN type.
 * 
 * This function iterates through each move of a SAN type, converts it to FEN, and checks
 * if it matches a given FEN type, representing a specific board state.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if a matching board state is found; false otherwise.
 */
Datum has_board_fn_operator(PG_FUNCTION_ARGS)
{
    FEN *input_fen, *result_fen;
    SAN *san, *gameTruncated;
    
    int i;
    bool result;
    const char *fenConversionStrResult;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("has_board_fn_operator: One of the arguments is null\n")));

    result_fen = (FEN *)palloc(sizeof(FEN)); 
    input_fen = (FEN *) PG_GETARG_POINTER(1);
    san = (SAN *) PG_GETARG_CHESSGAME_P(0);

    i=0;
    result = false;

    while (true) {

        gameTruncated = truncate_san(san, i);

        if (gameTruncated == NULL)
            break;

        fenConversionStrResult = san_to_fen(gameTruncated);

        if (fenConversionStrResult == NULL)
            ereport(ERROR, (errmsg("has_board_fn_operator: No FEN result returned from mapping san to fen")));

        parseStr_ToFEN(fenConversionStrResult, result_fen);

        if (strcmp(result_fen->positions, input_fen->positions) == 0)
        {
            result = true;
            break;
        }
        
        i++;
    }

    PG_RETURN_BOOL(result);
}
/**
 * Determines if a given FEN type matches any board state in a SAN type.
 * 
 * Similar to 'has_board_fn_operator', this function iterates through each move of a SAN type,
 * converts it to FEN, and checks if it matches the provided FEN type.
 *
 * @param fcinfo Function call info containing arguments.
 * @return Boolean value - true if a matching board state is found; false otherwise.
 */
Datum fen_in_san_eq(PG_FUNCTION_ARGS) {

    FEN *input_board, *result_fen;
    SAN *input_game, *gameTruncated;

    int i;
    bool result;
    const char *fenConversionStrResult;

    if (PG_ARGISNULL(0) || PG_ARGISNULL(1))
        ereport(ERROR, (errmsg("fen_in_san_eq: One of the arguments is null\n")));

    i=0;
    result = false;
    result_fen = (FEN *)palloc(sizeof(FEN));
    input_game = (SAN *)PG_GETARG_POINTER(1);
    input_board = (FEN *)PG_GETARG_POINTER(0);

    while (true) {

        gameTruncated = truncate_san(input_game, i);

        if (gameTruncated == NULL)
            break;

        fenConversionStrResult = san_to_fen(gameTruncated);

        if (fenConversionStrResult == NULL)
            ereport(ERROR, (errmsg("has_board_fn_operator: No FEN result returned from mapping san to fen")));

        parseStr_ToFEN(fenConversionStrResult, result_fen);

        if (strcmp(result_fen->positions, input_board->positions) == 0)
        {
            result = true;
            break;
        }
        
        i++;
    }

    PG_RETURN_BOOL(result);
}