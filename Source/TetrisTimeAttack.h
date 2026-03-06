#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h> // not needed in prclab1

void loadConfig();
short int createOrOpenFile(FILE *filePtr, char *filePath);
void redrawScreen(int x, int y);

// Global Variables
char* tetronimo[4][4] = {{" ","l"," "," "},
                         {" ","l"," "," "},
                         {" ","l","l"," "},
                         {" "," "," "," "}};

typedef struct leaderboard {
    char name[3];
    int score;
} leaderboard;

#include "Render.c"
#include "FileManager.c"

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H