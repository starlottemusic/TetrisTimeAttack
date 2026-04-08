#ifndef TETRISTIMEATTACK_TETRISTIMEATTACK_H
#define TETRISTIMEATTACK_TETRISTIMEATTACK_H

// Standard Plugins
#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h> // not needed in prclab1

//Macros
#define DELTA_TIME ((float) 1 / 60) // Length of one frame
#define GAMEBOARD_HEIGHT  22
#define GAMEBOARD_WIDTH 12
#define HOLD_HEIGHT 7
#define NEXT_HEIGHT 16
#define INFO_WIDTH 8
#define MENU_LENGTH 6
#define LOGO_WIDTH 46
#define LOGO_HEIGHT 15
#define CONTROLS_LENGTH 8
#define SCORE_WINDOW_OFFSET 9

// Structs & Datatype Aliases
typedef char byte;

typedef struct MainLeaderboard {
    char name[4];
    int score;
} Leaderboard;

typedef struct PlayerPiece {
    byte x;
    byte y;
    byte tetronimoIndex;
    char rotation;
    char tetronimo[4][4];
} PlayerPiece;

typedef struct PastPiece {
    byte x;
    byte tetronimoIndex;
    char rotation;
} PastPiece;

typedef struct pastChannel {
    PastPiece* pieces;
    byte pieceCount;
} Channel;

typedef struct KeyMap {
    int holdPiece;
    int moveDown;
    int moveLeft;
    int moveRight;
    int rotateCW;
    int rotateCCW;
    int hardDrop;
} KeyMap;

// Function Headers
byte createOrOpenFile(FILE **filePtrPtr, char *filePath);
void loadConfig();
void redrawBoard(int cols, int rows, char renderArray[][rows], byte x, byte y);
void initKickTable();
void initGameGlobals();
byte pieceSize(byte index);
bool isEven(byte index);
void attemptMovement(int direction);
void placePiece(PlayerPiece piece);
void clearPiece(PlayerPiece piece);
char pieceColorName(byte index);
byte pieceColorID(char colorName);
bool wallKick(byte index, char orient, bool clockwise);
bool safeMove();
short getOpenSpaces();
bool newTurnPlayerPiece(byte index);
void rotate(char piece[4][4], byte index, bool clockwise);
void lineClear();
void redrawGame();
int scorePow(int base, int exp);
byte upNext();
void updateNext();
bool shouldOffset(byte index);
void startNCursesScreen();
void tick();
void initPalette();
void attemptNewTurn(bool placePiece, bool isHold);
void tickGame();
void tickMenu();
void inputListener();
void handleGameInput();
void handleMenuInput(byte menuLength);
void cycleMenu(int keyInput, byte menuLength);
void mainGame();
void mainMenu();
void initMenuGlobals();
void redrawMenu();
void selectMenuOption();
void holdPiece();
void encryptText(char *text);
void setDefaultConfig();
void writeConfig(FILE* filePtr);
void mainControls();
void tickControls();
void redrawControls(bool drawTextOut, int textOutIndex);
void selectControlOption();
void appendKeyName(int configIndex, int key);
void getNcursesKeyName(int keyIndex, char *nameOut);
void updateConfigText();
void startRebind(byte index);
void bindKey(byte index, int key);
void saveConfig();
FILE* openLeaderboard(char accessMode[3]);
void scoreWindow();
void tickScoreWindow();
byte centered(char* text);
bool isValidCharacter(int ncursesChar);
void initLeaderboard();
void saveScore(char* name);
void mainLeaderboard();
void decryptText(char *text);
void redrawLeaderboard(Leaderboard* leaderboard, int page, int length);
void mainTutorial();
void tickTutorial();
void handleTutorialInput();
char assignMatrix(int s, int f);
void drawMatrix(int rows, int cols, int renderArray[][cols], byte x, byte y);
void extendPast();
void initializePastChannels();
PastPiece nextPast(byte fromIndex, bool shouldRemove);
void dropPast(PastPiece piece);
void drawFrame(int s, int f);

// Global Variables
extern char tetronimos[7][4][4]; // Array of all tetronimos
extern char gameBoard[GAMEBOARD_HEIGHT][GAMEBOARD_WIDTH]; // Working array of the current game board
extern char holdBoard[HOLD_HEIGHT][INFO_WIDTH]; // Working array of the hold board
extern char nextBoard[NEXT_HEIGHT][INFO_WIDTH]; // Working array for the "Up Next" board
extern short openSpace;
extern int kickTable[3][8][5][2];
extern PlayerPiece activePiece;
extern PlayerPiece lastActivePiece;
extern PlayerPiece heldPiece;
extern int lastInput;
extern byte turnCooldown;
extern bool canHold;
extern int score;
extern byte nextQueue[4];
extern char screenState;
extern long tickTimer;
extern char menuOptions[MENU_LENGTH][100];
extern char menuLogo[LOGO_HEIGHT][LOGO_WIDTH];
extern KeyMap keyMap;

extern char controlConfigs[CONTROLS_LENGTH][40];
extern char controlFeedback[4][40];
extern byte selectedOption;
extern char initScores[60];
extern bool isTimeAttack;
extern char pastBoard[GAMEBOARD_HEIGHT][INFO_WIDTH];
extern byte taActiveChannel;

extern PastPiece* pieces1;
extern PastPiece* pieces2;
extern PastPiece* pieces3;
extern PastPiece* pieces4;
extern Channel past[4];

extern char mat[6][10];

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H