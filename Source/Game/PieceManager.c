#include "../TetrisTimeAttack.h"

/**
 * Returns the size of a piece from the Tetronimos array
 * @param index The index of the piece in the array
 * @return The size of the piece
 */
byte pieceSize(byte index) {
    if (index == 0) return 4; // I piece
    if (index == 3) return 2; // O piece
    return 3; // other pieces
}

/**
 * Returns if the piece is an even size (2 wide, 4 wide)
 * @param index The index of the piece in the array
 * @return True if piece is even, else return false
 */
bool isEven(byte index) {
    if (pieceSize(index) % 2 == 0) return true;
    return false;
}

/**
 * Returns if the piece should be offset vertically when placed
 * @param index The index of the piece in the array
 * @return True if piece should be offset, else return false
 */
bool shouldOffset(byte index) {
    if (index == 1 || index == 2 || index == 5) return true;
    return false;
}

/**
 * Gets the color of a piece from its respective index in the tetronimos array
 * @param index The index of the tetronimo in the array
 * @return The color pair index
 */
char pieceColorName(byte index) {
    switch (index) {
        case 0:
            return 'I';
        case 1:
            return 'J';
        case 2:
            return 'L';
        case 3:
            return 'O';
        case 4:
            return 'S';
        case 5:
            return 'T';
        case 6:
            return 'Z';
        default:
            return '+';
    }
}

/**
 * Gets the color pair ID of a piece from it's char name in the tetronimos array
 * @param colorName The piece name used to identify color (ie. 'L', 'T', etc)
 * @return The color pair ID for rendering
 */
byte pieceColorID(char colorName) {
    //TODO consider just updating the array so we dont have to run this constantly
    switch (colorName) {
        case 'B':
            return 10;
        case 'I':
            return 1;
        case 'J':
            return 2;
        case 'L':
            return 3;
        case 'O':
            return 4;
        case 'S':
            return 5;
        case 'T':
            return 6;
        case 'Z':
            return 7;
        default:
            return 8;
    }
}

/**
 *
 * @param piecePtr Pointer to the playerPiece to be settled
 * @param x x position to settle at
 * @param y y position to settle at
 * @param shouldClear If the piece should be placed or removed
 * @param boardHeight Height of the board the piece is placed on
 * @param boardWidth Width of the board the piece is placed on
 * @param boardPtr Pointer to the board array the piece is placed on
 */
void settlePiece(PlayerPiece *piecePtr, byte x, byte y, bool shouldClear, byte boardHeight, byte boardWidth,
                 char (*boardPtr)[boardWidth][boardHeight]) {
    char color = pieceColorName(piecePtr->tetronimoIndex);
    byte i, j;
    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4; j++) {
            if ((*boardPtr)[i + y][j + x] == 'p')
                (*boardPtr)[i + y][j + x] = shouldClear ? ' ' : color;
        }
    }
};

/**
 * Attempts to end the active turn and spawn the next piece
 * @param placePiece If activePiece should be placed on the board
 * @param isHold Whether a piece should be brought from the hold slot
 */
void attemptNewTurn(bool placePiece, bool isHold) {
    byte nextPiece;

    if (isTimeAttack && placePiece && !isHold) {
        extendPast();
    }

    settlePiece(&activePiece, activePiece.x, activePiece.y, !placePiece, GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT, &gameBoard);

    if (isHold && heldPiece.tetronimoIndex != -1) {
        nextPiece = heldPiece.tetronimoIndex;
    } else {
        nextPiece = upNext();
    }

    if (isTimeAttack && placePiece && !isHold) {
        taActiveChannel++;
        if (taActiveChannel > 3) {
            taActiveChannel = 0;
            initGameboard();
        }

        redrawGame();
        usleep(100000);
        PastPiece lastPast;
        lastPast = nextPast(0, false);

        int i = 0;
        while (lastPast.tetronimoIndex != -1) {
            dropPast(lastPast);
            i++;
            lastPast = nextPast(i, false);
        }

        updatePastBoard();
    }

    lineClear();

    if (!newTurnPlayerPiece(nextPiece)) {
        if (isTimeAttack) {
            free(pieces1);
            free(pieces2);
            free(pieces3);
            free(pieces4);
        }
        redrawGame();
        usleep(1000000);
        screenState = 'S';
        lastInput = ERR;
        scoreWindow();
        endwin();
    }

    if (!isHold) {
        canHold = true;
        usleep(100000);
    }

    if (isTimeAttack) {
        if (taActiveChannel == 3) {
            init_pair(8, COLOR_RED, COLOR_WHITE);
            init_pair(9, COLOR_RED, COLOR_BLACK);
        } else
            init_pair(8, COLOR_WHITE, COLOR_WHITE);
            init_pair(9, COLOR_WHITE, COLOR_BLACK);
    }

    redrawGame();
    turnCooldown = 15;
}

/**
 * Resets activePlayerPiece at the initial spawn point if possible (no collisions)
 * @param index The index of the piece to be spawned from the tetronimos array
 * @return True - Piece can be placed safely; False - Piece will collide
 */
bool newTurnPlayerPiece(byte index) {
    openSpace = getOpenSpaces() - 4;

    byte i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            activePiece.tetronimo[i][j] = tetronimos[index][i][j] == ' ' ? tetronimos[index][i][j] : 'p';
        }
    }

    activePiece.tetronimoIndex = index;
    activePiece.x = 4;
    activePiece.y = shouldOffset(index) ? 1 : 0;
    // L, J, and T pieces need to spawn 1 position lower
    activePiece.rotation = '0';

    placePiece(activePiece);

    if (openSpace != getOpenSpaces())
        return false;
    return true;
}

/**
 * Attempts to put activePiece in the hold slot, starting a new turn. Fails if a hold has already occurred this move
 */
void holdPiece() {
    if (!canHold) return;
    canHold = false;

    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            holdBoard[i + 2][j + 2] = activePiece.tetronimo[i][j];
        }
    }

    settlePiece(&activePiece, 2, 2, false, 8, 8, &holdBoard);

    PlayerPiece tempHeldPiece = activePiece;
    attemptNewTurn(false, true);
    heldPiece = tempHeldPiece;

    redrawGame();
}

/**
 * Cycles the "up next" queue and generates the next random piece
 * @return The most recent piece index from the cycle
 */
byte upNext() {
    byte nextPiece = nextQueue[0];
    nextQueue[0] = nextQueue[1];
    nextQueue[1] = nextQueue[2];
    nextQueue[2] = nextQueue[3];
    nextQueue[3] = rand() % 7;
    updateNext();
    return nextPiece;
}

/**
 * Adjusts the pieces in the up next board to match the list
 */
void updateNext() {
    int i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                nextBoard[j + 3 * i + shouldOffset(nextQueue[i]) + 1][k + 2] = tetronimos[nextQueue[i]][j][k];
            }
        }
    }
}

/**
 * Clears any complete lines on screen.
 */
void lineClear() {
    byte x, y, i;
    byte linesCleared = 0;
    bool clear[20];

    // Check which lines need to be cleared
    for (y = 0; y < 20; y++) {
        clear[y] = true;
        for (x = 0; x < 10; x++) {
            if (gameBoard[y + 1][x + 1] == ' ') {
                clear[y] = false;
            }
        }
    }

    // Clear lines
    for (i = 0; i < 20; i++) {
        if (clear[i]) {
            // Clear the targeted line
            memcpy(gameBoard[i + 1], "x          x", 12);
            redrawGame();

            // Shift all future lines & clear targets down
            for (y = i; y > 0; y--)
                memcpy(gameBoard[y + 1], gameBoard[y], 12);
            // Clear top of buffer
            memcpy(gameBoard[1], "x          x", 12);

            linesCleared++;

            if (isTimeAttack) {
                erasePast();
            }
        }
    }

    if (linesCleared > 0)
        score += 100 * scorePow(2, linesCleared);
}
