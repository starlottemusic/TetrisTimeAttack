#include "TetrisTimeAttack.h"

/**
 * Initialize the color pairs for each Tetronimo used in rendering
 * Color IDs can be retrieved from pieceColorID during render pass
 */
void initPalette() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_CYAN);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_RED, COLOR_YELLOW);
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(5, COLOR_GREEN, COLOR_GREEN);
    init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(7, COLOR_RED, COLOR_RED);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);

}

/**
 * Draw all Tetronimos in a 4x4 array & write to the global array
 */
void initTetronimos() {
    byte i, j, k;

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

    byte i, j;

    openSpace = 196 - 15;

    char tempBoard[BOARD_WIDTH + 2][BOARD_HEIGHT + 2] =
    {
        {"++++++++++++"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+     ++++++"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+++        +"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+    +++   +"},
        {"+    + +   +"},
        {"+    +++   +"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"+          +"},
        {"++++++++++++"}
    };

    for (i = 0; i < BOARD_WIDTH + 2; i++) {
        for (j = 0; j < BOARD_HEIGHT + 2; j++) {
            gameBoard[i][j] = tempBoard[i][j];
        }
    }
}
