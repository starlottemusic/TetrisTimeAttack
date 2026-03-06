#include "TetrisTimeAttack.h"

void redrawScreen(int x, int y) {
    clear();
    mvprintw(y, x, "%s%s%s%s", tetronimo[0][0], tetronimo[0][1], tetronimo[0][2], tetronimo[0][3]);
    mvprintw(y+1, x, "%s%s%s%s", tetronimo[1][0], tetronimo[1][1], tetronimo[1][2], tetronimo[1][3]);
    mvprintw(y+2, x, "%s%s%s%s", tetronimo[2][0], tetronimo[2][1], tetronimo[2][2], tetronimo[2][3]);
    mvprintw(y+3, x, "%s%s%s%s", tetronimo[3][0], tetronimo[3][1], tetronimo[3][2], tetronimo[3][3]);
    refresh();
}