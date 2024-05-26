#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[1000];
} ChessGame;

int main() {

    ChessGame* x = malloc(sizeof(ChessGame));

    // Your PGN string and half moves
    const char *pgnString = "1. e4 e5 2. Nf3";
    int halfMoves = 2;

    strncpy(x->data, pgnString,1000);

    // Construct the command to run the Python script
    char command[256];
    snprintf(command, sizeof(command), "python3 chess_interaction.py \"%s\" %d", x->data, halfMoves);

    // Open a pipe to read the output of the command
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("Error opening pipe");
        return -1;
    }

    char result[1024] = ""; 
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Process the output as needed
        //printf("Received from Python: %s", buffer);
        strcat(result, buffer);
    }


    // Close the pipe
    pclose(pipe);

    printf("%s", result);

    return 0;
}