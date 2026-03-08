#include <string.h>

#include "TetrisTimeAttack.h"

/**
 * Initialize the color pairs for each Tetronimo used in rendering
 * On render pass, chars which match the pair index will render w/ the provided colors
 */
void initPalette() {
    start_color();
    init_pair('+', COLOR_WHITE, COLOR_WHITE);
    init_pair('I', COLOR_CYAN, COLOR_CYAN);
    init_pair('J', COLOR_BLUE, COLOR_BLUE);
    init_pair('L', COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair('O', COLOR_YELLOW, COLOR_YELLOW);
    init_pair('S', COLOR_GREEN, COLOR_GREEN);
    init_pair('T', COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair('Z', COLOR_RED, COLOR_RED);
}

/**
 * Draw all Tetronimos in a 4x4 array & write to the global set
 */
void initTetronimos() {
    int i, j, k;

    char pieceDefinition[7][4][4] = {
        {
            {"    "},
            {"IIII"},
            {"    "},
            {"    "}
        },
        {
            {"    "},
            {"JJJ "},
            {"  J "},
            {"    "}
        },
        {
            {"    "},
            {"LLL "},
            {"L   "},
            {"    "}
        },
        {
            {"    "},
            {" OO "},
            {" OO "},
            {"    "}
        },
        {
            {"    "},
            {" SS "},
            {"SS  "},
            {"    "}
        },
        {
            {"    "},
            {"TTT "},
            {" T  "},
            {"    "}
        },
        {
            {"    "},
            {"ZZ  "},
            {" ZZ "},
            {"    "}
        }
    };

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                tetronimos[i][j][k] = pieceDefinition[i][j][k];
            }
        }
    }
}

/**
 * Initialize all global variables
 */
void initGlobals() {
    initTetronimos();

    int i, j;

    char tempBoard[20][10] =
    {
        {"  SSSS    "},
        {"  Z       "},
        {"  ZZ      "},
        {"   Z      "},
        {"      JJJ "},
        {"L       J "},
        {"LLL       "},
        {"      OO  "},
        {"  L   OO  "},
        {"  L       "},
        {"  LL      "},
        {"       I  "},
        {"       I  "},
        {"  T    I  "},
        {" TT    I  "},
        {"  T       "},
        {"     SS   "},
        {"    SS    "},
        {"SSSSSSSSSJ"},
        {"++++++++++"}
    };

    currentPiece = 0;

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 10; j++) {
            screen[i][j] = tempBoard[i][j];
        }
    }
}
