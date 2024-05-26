/*
 * SAN.h
 *      Implementation of SAN (Standard Algebraic Notation) related operations for chess games.
 *
 * This file includes functions for processing and manipulating chess game data
 * represented in SAN format. It's part of a PostgreSQL extension for storing and
 * querying chess games.
 * 
 */

#include <ctype.h>
#include <string.h>

#ifndef SAN_H
#define SAN_H  

//---------------------------------------------------------------------DATA TYPE DECLARATION--------------------------------------------------------------------//

// Define the maximum length for a PGN (Portable Game Notation) string.
#define MAX_PGN_LENGTH 1000

/**
 * Structure to represent a Standard Algebraic Notation (SAN) of a chess game.
 *
 * This structure holds a single chess game's moves in SAN format.
 * The data array is sized to accommodate typical chess games, including annotations.
 */
typedef struct {
    char data[MAX_PGN_LENGTH]; // Array to store the SAN string.
} SAN;

//------------------------------------------------------------------END DATA TYPE DECLARATION--------------------------------------------------------------------//



//---------------------------------------------------------------------FUNCTIONS DECLARATION--------------------------------------------------------------------//

char* skipCommentsAndAnnotations(char* str);
void parsePGN_ToStr(SAN *game, char **result);
void parseStr_ToPGN(const char *pgn, SAN *game);
SAN *truncate_san(SAN *inputGame, int nHalfMoves);

//-----------------------------------------------------------------END FUNCTIONS DECLARATION--------------------------------------------------------------------//



//------------------------------------------------------------------FUNCTIONS IMPLEMENTATION--------------------------------------------------------------------//

/**
 * Parses a string into the SAN structure.
 *
 * This function copies a given PGN string into a SAN structure,
 * ensuring the string is properly null-terminated.
 *
 * @param pgn The PGN string to parse.
 * @param game The SAN structure to populate.
 */
void parseStr_ToPGN(const char *pgn, SAN *game) {
    game->data[MAX_PGN_LENGTH - 1] = '\0'; // Ensure null-termination.
    strncpy(game->data, pgn, MAX_PGN_LENGTH - 1); // Copy the string.
}

/**
 * Converts SAN structure data to a string.
 *
 * This function allocates memory for and returns a copy of the SAN data.
 * The caller is responsible for freeing the allocated memory.
 *
 * @param game The SAN structure to convert.
 * @param result Pointer to the resulting string.
 */
void parsePGN_ToStr(SAN *game, char **result){
    *result = (char *)palloc(strlen(game->data) + 1); // Allocate memory for the string.
    strcpy(*result, game->data); // Copy the SAN data.
}

/**
 * Skips comments and annotations in a chess game string.
 *
 * This function processes a string containing a chess game and skips
 * over comments and annotations, which are typically enclosed in
 * curly braces {} or parentheses ().
 *
 * @param str A pointer to the string to be processed.
 * @return A pointer to the string, positioned after any comments or annotations.
 */
char *skipCommentsAndAnnotations(char *str) {
    char *p = str; // Pointer to traverse the string.

    while (*p) { // Loop through each character in the string.
        if (*p == '{') { // Start of a comment block.
            while (*p && *p != '}') p++; // Skip until the end of the comment block.
            if (*p) p++; // Move past the closing brace.
        } else if (*p == '(') { // Start of an annotation block.
            while (*p && *p != ')') p++; // Skip until the end of the annotation block.
            if (*p) p++; // Move past the closing parenthesis.
        } else if (!isspace((unsigned char)*p)) { // Non-space character marks the end of comments/annotations.
            break;
        } else {
            p++; // Move to the next character.
        }
    }
    return p; // Return the position in the string after comments and annotations.
}

/**
 * 
 * Truncates a SAN string to a specified number of half-moves.
 *
 * This function takes a SAN structure representing a chess game and
 * truncates it to the first n half-moves. A half-move in chess is a single
 * move by either player.
 *
 * @param inputGame A pointer to the SAN structure representing the chess game.
 * @param nHalfMoves The number of half-moves to which the game is to be truncated.
 * @return A pointer to a new SAN structure containing the truncated game.
 *         Returns NULL if the game is shorter than the requested number of half-moves.
 */
SAN *truncate_san(SAN *inputGame , int nHalfMoves) {
    SAN *resultGame = (SAN *) palloc(sizeof(SAN)); // Allocate memory for the result SAN structure.
    int halfMoveCount = 0; // Counter for the number of half-moves processed.
    char *token, *rest, *inputCopy; // Pointers for string tokenization.
    bool isMoveNumber; // Flag to check if the token is a move number.

    // Create a copy of the input SAN string to tokenize.
    inputCopy = palloc(strlen(inputGame->data) + 1);
    strcpy(inputCopy, inputGame->data); // Copy the SAN string.
    rest = inputCopy; // Set the rest pointer for strtok_r usage.

    resultGame->data[0] = '\0'; // Initialize the result SAN string.

    // Tokenize the SAN string and process each token.
    while ((token = strtok_r(rest, " ", &rest)) && halfMoveCount < nHalfMoves) {
        rest = skipCommentsAndAnnotations(rest); // Skip any comments and annotations.
        isMoveNumber = (strchr(token, '.') != NULL); // Check if the token is a move number.
        strcat(resultGame->data, token); // Append the token to the result SAN string.
        strcat(resultGame->data, " "); // Append a space after the token.

        // Increment the half-move count if the token is not a move number.
        if (!isMoveNumber)
            halfMoveCount++;
    }

    // Free the memory allocated for the input copy.
    pfree(inputCopy);

    // Check if the desired number of half-moves was reached.
    if (halfMoveCount < nHalfMoves){
        pfree(resultGame); // Free the result structure if not.
        return NULL; // Return NULL to indicate insufficient half-moves.
    }

    return resultGame; // Return the truncated SAN structure.
}

//--------------------------------------------------------------END FUNCTIONS IMPLEMENTATION--------------------------------------------------------------------//

#endif