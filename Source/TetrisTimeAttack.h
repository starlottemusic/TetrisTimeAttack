#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // not needed in prclab1

//Macros
#define DELTA_TIME ((float) 1 / 60) // Length of one frame
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 10

// Structs & Datatype Aliases
typedef char byte;

typedef struct Leaderboard {
    char name[3];
    long score;
} Leaderboard;

typedef struct PlayerPiece {
    byte x;
    byte y;
    byte tetronimoIndex;
    char tetronimo[4][4];
} PlayerPiece;

typedef struct PastPiece {
    byte x;
    byte tetronimoIndex;
    byte rotation;
} PastPiece;

// Function Headers
byte createOrOpenFile(FILE *filePtr, char *filePath);
void loadConfig();
void redrawScreen();
void initGlobals();
byte pieceSize(byte index);
void attemptMovement(int direction);
void placePiece(PlayerPiece piece);
void clearPiece(PlayerPiece piece);
char pieceColorName(byte index);
byte pieceColorID(char colorName);
bool safeMove();
short getOpenSpaces();

// Global Variables
char tetronimos[7][4][4]; // Array of all tetronimos
char gameBoard[BOARD_WIDTH + 2][BOARD_HEIGHT + 2]; // Array of the current game board
short openSpace;
PlayerPiece activePiece;
PlayerPiece lastActivePiece;

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H