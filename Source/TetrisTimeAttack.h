#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // not needed in prclab1

//Macros
#define DELTA_TIME ((float) 1 / 60) // Length of one frame

// Function Headers
short int createOrOpenFile(FILE *filePtr, char *filePath);
void loadConfig();
void redrawScreen(int x, int y);
void initGlobals();

// Global Variables
int currentPiece; // The index of the currently selected piece
char tetronimos[7][4][4]; // Array of all tetronimos
char screen[20][10]; // The current screen state

typedef struct leaderboard {
    char name[3];
    int score;
} leaderboard;

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H