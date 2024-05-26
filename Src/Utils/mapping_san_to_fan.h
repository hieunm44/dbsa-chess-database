/*
 * Mapping SAN to FEN
 *      Conversion of Standard Algebraic Notation (SAN) to Forsyth-Edwards Notation (FEN).
 *
 * This file contains a function to convert chess game data from SAN format to FEN format.
 * It uses embedded Python scripting to leverage the 'chess' library for the conversion.
 *
 */

#include "postgres.h"
#include "utils/elog.h"
#include "DataTypes/SAN/SAN.h"

#define PY_SSIZE_T_CLEAN
#include <python3.11/Python.h>


#ifndef MAPPING_SAN_TO_FAN
#define MAPPING_SAN_TO_FAN

//---------------------------------------------------------------------FUNCTION DECLARATION------------------------------------------------------------------------//

const char* san_to_fen(SAN *gameTruncated);

//---------------------------------------------------------------------FUNCTION IMPLEMENTATION---------------------------------------------------------------------//

/**
 * Converts a chess game from SAN to FEN format using Python.
 *
 * This function takes a SAN structure representing a chess game and uses embedded
 * Python with the 'chess' library to convert it into the FEN format. It initializes
 * the Python interpreter, defines a Python function for conversion, and executes it.
 *
 * @param gameTruncated A pointer to the SAN structure representing the chess game.
 * @return A pointer to a string containing the game in FEN format.
 *         Returns NULL if conversion fails.
 */
const char* san_to_fen(SAN *gameTruncated) 
{
    // Initialize variables for Python interaction.
    PyObject *pModule, *pFunc, *pArgs, *pValue;
    const char *result = NULL;

    // Initialize the Python interpreter.
    Py_Initialize();

    // Define the Python function for SAN to FEN conversion.
    PyRun_SimpleString(
        "import chess\n"
        "import chess.pgn\n"
        "import io\n"
        "def get_fen_from_san(san):\n"
        "    if not san.strip():\n"
        "       return 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'  # Default FEN for empty input\n"
        "    game = chess.pgn.read_game(io.StringIO(san))\n"
        "    board = game.board()\n"
        "    for move in game.mainline_moves():\n"
        "        board.push(move)\n"
        "    return board.fen()\n"
    );

    // Add the defined Python function to the '__main__' module.
    pModule = PyImport_AddModule("__main__");

    // Check if the Python function is loaded and callable.
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "get_fen_from_san");
        if (pFunc && PyCallable_Check(pFunc)) {
            // Prepare the arguments for the Python function call.
            pArgs = PyTuple_New(1);
            PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(gameTruncated->data));
            
            // Call the Python function and retrieve the result.
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                // Convert the Python string result to C string.
                result = PyUnicode_AsUTF8(pValue);
                Py_DECREF(pValue);
            } else {
                // Handle Python call failure.
                Py_DECREF(pFunc);
                PyErr_Print();
                ereport(ERROR, (errmsg("Call to 'get_fen_from_san' failed")));
            }
        } else {
            // Handle errors related to function loading or callability.
            if (PyErr_Occurred())
                PyErr_Print();
            ereport(ERROR, (errmsg("Cannot find function 'get_fen_from_san'")));
        }
        Py_XDECREF(pFunc);
    } else {
        // Handle errors in loading the '__main__' module.
        PyErr_Print();
        ereport(ERROR, (errmsg("Failed to load '__main__' module")));
    }

    // Finalize the Python interpreter.
    Py_Finalize();

    return result;
}

//--------------------------------------------------------------END FUNCTION IMPLEMENTATION--------------------------------------------------------------------//

#endif