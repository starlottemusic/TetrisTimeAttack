#include "TetrisTimeAttack.h"

void initGlobals() {
    char* temp[4][4] = {{" ","l"," "," "},
                        {" ","l"," "," "},
                        {" ","l","l"," "},
                        {" "," "," "," "}};
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tetronimo[i][j] = temp[i][j];
        }
    }
}