#include "../TetrisTimeAttack.h"

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
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
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
            {"J   "},
            {"JJJ "},
            {"    "},
            {"    "}
        },
        {
            {"  L "},
            {"LLL "},
            {"    "},
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
            {" T  "},
            {"TTT "},
            {"    "},
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
 * Initializes the kick table (via https://tetris.wiki/Super_Rotation_System)
 * @var p piece type
 * @var r rotation
 * @var t test
 * @var c coordinate
 */
void initKickTable() {
    int i, j, k, l;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 5; k++) {
                for (l = 0; l < 2; l++) {
                    kickTable[i][j][k][l] = 0;
                }
            }
        }
    }

    // Populate default table
    int temp[8] = {-1, 1, 1, -1, 1, -1, -1, 1};
    for (i = 0; i < 8; i++) {
        kickTable[0][i][1][0] = temp[i];
        kickTable[0][i][2][0] = temp[i];
        kickTable[0][i][2][1] = temp[i] * -1;
        kickTable[0][i][3][1] = temp[i] * 2;
        kickTable[0][i][4][0] = temp[i];
        kickTable[0][i][4][1] = temp[i] * 2;
    }

    // Populate I table
    int tempI[4][8][2] = {
        {{-2, 0}, {2, 0}, {-1, 0}, {1, 0}, {2, 0}, {-2, 0}, {1, 0}, {-1, 0}},
        {{1, 0}, {-1, 0}, {2, 0}, {-2, 0}, {-1, 0}, {1, 0}, {-2, 0}, {2, 0}},
        {{-2, -1}, {2, 1}, {-1, 2}, {1, -2}, {2, 1}, {-2, -1}, {1, -2}, {-1, 2}},
        {{1, 2}, {-1, -2}, {2, -1}, {-2, 1}, {-1, -2}, {1, 2}, {-2, 1}, {2, -1}},
    };

    for (i = 0; i < 8; i++) {
        kickTable[1][i][1][0] = tempI[0][i][0];
        kickTable[1][i][2][0] = tempI[1][i][0];
        kickTable[1][i][3][0] = tempI[2][i][0];
        kickTable[1][i][4][0] = tempI[3][i][0];

        kickTable[1][i][1][1] = tempI[0][i][1];
        kickTable[1][i][2][1] = tempI[1][i][1];
        kickTable[1][i][3][1] = tempI[2][i][1];
        kickTable[1][i][4][1] = tempI[3][i][1];
    }

    // O table contains all 0s
}

/**
 * Initialize all global variables
 */
void initGameGlobals() {
    initTetronimos();

    byte i, j;

    openSpace = 196 - 15;

    char tempGameBoard[GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH] =
    {
        "++++++++++++",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "+          +",
        "++++++++++++"
    };

    memcpy(gameBoard, tempGameBoard, sizeof(gameBoard));

    char tempHoldBoard[HOLD_HEIGHT][INFO_WIDTH] = {
        "++++++++",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "++++++++"
    };

    memcpy(holdBoard, tempHoldBoard, sizeof(holdBoard));

    char tempNextBoard[NEXT_HEIGHT][INFO_WIDTH] = {
        "++++++++",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "+      +",
        "++++++++"
    };

    memcpy(nextBoard, tempNextBoard, sizeof(nextBoard));

    score = 0;

    for (i = 0; i < 4; i++)
        nextQueue[i] = rand() % 7;

    heldPiece.tetronimoIndex = -1;
    canHold = true;
    lastInput = ERR;
    tickTimer = 0;
}

/**
 * Initialize global variables for menu
 */
void initMenuGlobals() {
    strcpy(menuOptions[0], "+   START GAME   +");
    strcpy(menuOptions[2], "+    TUTORIAL    +");
    strcpy(menuOptions[1], "+  LEADERBOARDS  +");
    strcpy(menuOptions[3], "+    CONTROLS    +");
    strcpy(menuOptions[4], "+      QUIT      +");

    char tempLogo[LOGO_HEIGHT][LOGO_WIDTH] = {
        " SS  ZZTTT OOJJJ  SS  ZZTTT  ZJJJ IIIISS  IIII",
        "SSJJJIZZT  OOZ J SSJJJIZZT  ZZ  J  OOSS  OOJ  ",
        "    JI      ZZ       JI     ZT OO  OOJJ  OOJ  ",
        "    LI      ZLLL     LI     TT OO   LJ    JJSS",
        "    LI      SL       LI     ITLLL   LJ     SSZ",
        "    LL     TSS       LL     I LS    LL      ZZ",
        "    OO     TTS       OO     I  SS  TZZ   TTTZL",
        "    OO     TIIII     OO     I   S TTTZZ   TLLL",
        "                                              ",
        "                                              ",
        " +++ +++ +   + +++    +++ +++ +++ +++ +++ + + ",
        "  +   +  ++ ++ +      + +  +   +  + + +   + + ",
        "  +   +  + + + ++     +++  +   +  +++ +   ++  ",
        "  +   +  + + + +      + +  +   +  + + +   + + ",
        "  +  +++ +   + +++    + +  +   +  + + +++ + + "
    };

    memcpy(menuLogo, tempLogo, 690);
}

char inputArray[7][20] = {
    "MOVE LEFT - ",
    "MOVE DOWN - ",
    "MOVE RIGHT - ",
    "ROTATE CCW - ",
    "ROTATE CW - ",
    "HARD DROP - ",
    "HOLD PIECE - "
};
