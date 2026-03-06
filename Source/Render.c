#include "TetrisTimeAttack.h"

void redrawScreen(int x, int y) {
    clear();
    int i, j;

    attron(COLOR_PAIR(1) | A_STANDOUT);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tetronimo[i][j] == ' ') continue;
            mvprintw(y + j, x + 2 * i, "  ");
        }
    }
    attroff(COLOR_PAIR(1) | A_STANDOUT);

    refresh();
}