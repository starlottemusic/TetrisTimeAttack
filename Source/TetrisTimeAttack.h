#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h> // not needed in prclab1

short int createOrOpenFile(FILE *filePtr, char *filePath);
void loadConfig();
void redrawScreen(int x, int y);
void initGlobals();

// Global Variables
char tetronimo[4][4];

typedef struct leaderboard {
    char name[3];
    int score;
} leaderboard;

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H