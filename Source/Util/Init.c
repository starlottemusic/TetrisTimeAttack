#include "../TetrisTimeAttack.h"

char tetronimos[7][4][4]; // Array of all tetronimos
char gameBoard[GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH]; // Working array of the current game board
char holdBoard[HOLD_HEIGHT][INFO_WIDTH]; // Working array of the hold board
char nextBoard[NEXT_HEIGHT][INFO_WIDTH]; // Working array for the "Up Next" board
short openSpace;
int kickTable[3][8][5][2];
PlayerPiece activePiece;
PlayerPiece lastActivePiece;
PlayerPiece heldPiece;
int lastInput;
byte turnCooldown;
bool canHold;
int score;
byte nextQueue[4];
char screenState;
long tickTimer;
char menuLogo[LOGO_HEIGHT][LOGO_WIDTH];
KeyMap keyMap;
bool isTimeAttack = true;
byte taActiveChannel = 0;

// Separate due to memory shenanigans
PastPiece *pieces1;
PastPiece *pieces2;
PastPiece *pieces3;
PastPiece *pieces4;

Channel past[4];

void initializePastChannels() {
    int i;
    for (i = 0; i < 4; i++)
        past[i].pieceCount = 0;
    past[0].pieces = pieces1;
    past[1].pieces = pieces2;
    past[2].pieces = pieces3;
    past[3].pieces = pieces4;
}

char menuOptions[MENU_LENGTH][100] = {
    "+  TIME ATTACK!  +",
    "+   START GAME   +",
    "+  LEADERBOARDS  +",
    "+    TUTORIAL    +",
    "+    CONTROLS    +",
    "+      QUIT      +"
};

char pastBoard[GAMEBOARD_HEIGHT][INFO_WIDTH] = {
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
    "+      +",
    "+      +",
    "+      +",
    "+      +",
    "+      +",
    "+      +",
    "++++++++"
};

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
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
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

char controlConfigs[CONTROLS_LENGTH][40] = {
    "MOVE LEFT - ",
    "MOVE DOWN - ",
    "MOVE RIGHT - WHAT",
    "ROTATE CCW - ",
    "ROTATE CW - ",
    "HARD DROP - ",
    "HOLD PIECE - ",
    "Exit to Menu"
};

char controlFeedback[4][40] = {
    "Press any key to rebind %s",
    "(Press ESC to cancel)",
    "Key successfully bound!",
    "Key binding canceled."
};

byte selectedOption = 0;

char initScores[60] = "HSM - 119736\nCHR - 60684\nDEA - 22765\nCOL - 11498\nHAM - 600\n";

/**
 * If global leaderboard DNE, attempts to create with initial values. If global leaderboard cannot be accessed,
 * checks if local leaderboard exists and attempts to load.
 */
void initLeaderboard() {
    encryptText(initScores);
    FILE *leaderboard = fopen("TTA_Data/TTA_LDBGLB.sav", "r"); // Check if global ldb exists
    if (leaderboard == NULL) {
        leaderboard = fopen("TTA_Data/TTA_LDBGLB.sav", "w"); // Check if global ldb can be created
        if (leaderboard == NULL) {
            leaderboard = fopen("TTA_Data/TTA_LDBGLB.sav", "r"); // Check if local ldb exists
            if (leaderboard == NULL) {
                leaderboard = fopen("TTA_Data/TTA_LDBGLB.sav", "w"); // Check if local ldb can be created
                if (leaderboard != NULL) {
                    fprintf(leaderboard, initScores);
                    fclose(leaderboard);
                }
            }
            return;
        }
        fprintf(leaderboard, initScores);
        fclose(leaderboard);
    }
}
