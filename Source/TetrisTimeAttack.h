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
#include <unistd.h> // not needed in prclab1

//Macros
#define DELTA_TIME ((float) 1 / 60) // Length of one frame
#define GAMEBOARD_HEIGHT  22
#define GAMEBOARD_WIDTH 12
#define HOLD_HEIGHT 7
#define NEXT_HEIGHT 16
#define INFO_WIDTH 8
#define MENU_LENGTH 5
#define LOGO_WIDTH 46
#define LOGO_HEIGHT 15
#define CONTROLS_LENGTH 8
#define SCORE_WINDOW_OFFSET 9

// Structs & Datatype Aliases
typedef char byte;

typedef struct Leaderboard {
    char name[3];
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
void runAnim();

// Global Variables
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
char menuOptions[5][100];
char menuLogo[LOGO_HEIGHT][LOGO_WIDTH];
KeyMap keyMap;

extern char controlConfigs[CONTROLS_LENGTH][40];
extern char controlFeedback[4][40];
extern byte selectedOption;
extern char initScores[60];

#endif //TETRISTIMEATTACK_TETRISTIMEATTACK_H