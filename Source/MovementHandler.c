#include "TetrisTimeAttack.h"

/**
 * Attempts to move a piece in a given direction. If movement fails, block movement, else move piece and update screen
 * @param direction The direction the movement is attempted in, via ncurses arrow key macros (ie. KEY_UP)
 */
void attemptMovement(int direction) {
    lastActivePiece = activePiece;
    switch (direction) {
        case KEY_UP:
            activePiece.y--;
            break;
        case KEY_DOWN:
            activePiece.y++;
            break;
        case KEY_LEFT:
            activePiece.x--;
            break;
        case KEY_RIGHT:
            activePiece.x++;
            break;
    }

    if (safeMove()) {
        redrawScreen();
    } else {
        clearPiece(activePiece);
        placePiece(lastActivePiece);
        activePiece = lastActivePiece;
    }
}

/**
 * Places a piece onto the game board at coordinate (piece.x, piece.y)
 * @param piece
 */
void placePiece(PlayerPiece piece) {
    byte i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (gameBoard[piece.y + i][piece.x + j] != ' ') continue;
            gameBoard[piece.y + i][piece.x + j] = piece.tetronimo[i][j];
        }
    }
}

/**
 * Removes a piece from the game board at coordinate (piece.x, piece.y)
 * @param piece
 */
void clearPiece(PlayerPiece piece) {
    byte i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (gameBoard[piece.y + i][piece.x + j] != 'p') continue;
            gameBoard[piece.y + i][piece.x + j] = ' ';
        }
    }
}

/**
 * Rotates a piece clockwise or counterclockwise
 * @param piece The array of the piece to be rotated
 * @param index The index of the piece from the Tetronimos global array
 * @param clockwise If true, rotate CW. If false, rotate CCW
 */
void rotate(char piece[4][4], byte index, bool clockwise) {
    byte size = pieceSize(index);
    char temp[4][4];
    byte i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            temp[i][j] = clockwise ? piece[j][(size - 1) - i] : piece[(size - 1) - j][i];
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            piece[i][j] = temp[i][j];
        }
    }
}

/**
 * Checks if a piece translation is valid (doesn't collide w/ pieces, doesn't exceed board bounds)
 * @return True - Valid move, False - Invalid move
 */
bool safeMove() {
    clearPiece(lastActivePiece);
    placePiece(activePiece);

    if (getOpenSpaces() == openSpace) return true;
    return false;
}

/**
 * Counts how many unfilled spaces are on the screen
 * @return Number of open spaces
 */
int getOpenSpaces() {
    int sum = 0;

    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (gameBoard[i + 1][j + 1] == ' ') sum++;
        }
    }

    return sum;
}