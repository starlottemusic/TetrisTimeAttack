#include "TetrisTimeAttack.h"

void initPalette() {
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
}

void initGlobals() {
    char temp[3][3] = {{" l "},
                       {" l "},
                       {"ll "}};
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tetronimo[i][j] = temp[i][j];
        }
    }
}