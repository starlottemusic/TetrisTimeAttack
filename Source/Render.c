#include "TetrisTimeAttack.h"

/**
 * Formats & redraws the screen based off the global screen array. Colors are determined via characters
 */
void redrawScreen(int x, int y) {
    clear();
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (tetronimos[currentPiece][i][j] == ' ') continue;

            if (tetronimos[currentPiece][i][j] == 'T') attron(COLOR_PAIR(tetronimos[currentPiece][i][j]));
            else attron(COLOR_PAIR(tetronimos[currentPiece][i][j]) | A_STANDOUT);

            mvprintw(y + i, x + 2 * j, "  ");
            attroff(COLOR_PAIR(tetronimos[currentPiece][i][j]) | A_STANDOUT);
            refresh(); // Ideally we'd only call this one but it freaks out if we have more than 4 of one char in a row otherwise
        }
    }
}