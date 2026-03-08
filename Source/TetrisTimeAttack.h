#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // not needed in prclab1

//Macros
#define DELTA_TIME ((float) 1 / 60)

// Function Headers
short int createOrOpenFile(FILE *filePtr, char *filePath);
void loadConfig();
void redrawScreen(int x, int y);
void initGlobals();

// Global Variables
int currentPiece;
char tetronimos[7][4][4];
char screen[20][10];

typedef struct leaderboard {
    char name[3];
    int score;
} leaderboard;

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H