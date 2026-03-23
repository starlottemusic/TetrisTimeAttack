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
    char orient = activePiece.rotation;
    byte rotSize = isEven(index) ? 4 : 3;
    char temp[4][4], oldPiece[4][4];
    byte i, j;

    // Copy piece to oldPiece
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            oldPiece[i][j] = piece[i][j];
        }
    }

    // Apply rotation to piece
    for (i = 0; i < rotSize; i++) {
        for (j = 0; j < rotSize; j++) {
            temp[i][j] = !clockwise ? piece[j][(rotSize - 1) - i] : piece[(rotSize - 1) - j][i];
        }
    }

    for (i = 0; i < rotSize; i++) {
        for (j = 0; j < rotSize; j++) {
            piece[i][j] = temp[i][j];
        }
    }

    // Run wallKick(), if wall kick cannot be performed then copy oldPiece to piece
    if (!wallKick(index, orient, clockwise)) {
        clearPiece(activePiece);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                piece[i][j] = oldPiece[i][j];
            }
        }
        return;
    }

    // Assign new orient to active piece
    switch (orient) {
        case '0':
            activePiece.rotation = clockwise ? 'R' : 'L';
            break;
        case 'R':
            activePiece.rotation = clockwise ? '2' : '0';
            break;
        case '2':
            activePiece.rotation = clockwise ? 'L' : 'R';
            break;
        case 'L':
            activePiece.rotation = clockwise ? '0' : '2';
            break;
        default:
            break;
    }
}

/**
 * On invalid rotation, nudges a piece in a predetermined sequence to the next available position.
 * @param index The index of the piece from the Tetrominos global array
 * @param orient The current orientation of the piece
 * @param clockwise If true, rotate CW. If false, rotate CCW
 */
bool wallKick(byte index, char orient, bool clockwise) {
    int i;
    int kickSize = pieceSize(index) % 3; // Checks if piece is I (== 1) or O (== 2), else == 0

    for (i = 0; i < 4; i++) {
        lastActivePiece = activePiece;

        switch (orient) {
            case '0':
                activePiece.x += clockwise ? kickTable[kickSize][0][i][0] : kickTable[kickSize][7][i][0];
                activePiece.y += clockwise ? kickTable[kickSize][0][i][1] : kickTable[kickSize][7][i][1];
                break;
            case 'R':
                activePiece.x += clockwise ? kickTable[kickSize][2][i][0] : kickTable[kickSize][1][i][0];
                activePiece.y += clockwise ? kickTable[kickSize][2][i][1] : kickTable[kickSize][1][i][1];
                break;
            case '2':
                activePiece.x += clockwise ? kickTable[kickSize][4][i][0] : kickTable[kickSize][3][i][0];
                activePiece.y += clockwise ? kickTable[kickSize][4][i][1] : kickTable[kickSize][3][i][1];
                break;
            case 'L':
                activePiece.x += clockwise ? kickTable[kickSize][6][i][0] : kickTable[kickSize][5][i][0];
                activePiece.y += clockwise ? kickTable[kickSize][6][i][1] : kickTable[kickSize][5][i][1];
                break;
            default:
                break;
        }

        if (safeMove())
            return true;
    }
    activePiece = lastActivePiece;
    return false;
}

/**
 * Moves active piece if valid (doesn't collide w/ pieces, doesn't exceed board bounds)
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
short getOpenSpaces() {
    short sum = 0;
    byte i, j;

    for (i = 0; i < BOARD_WIDTH; i++) {
        for (j = 0; j < BOARD_HEIGHT; j++) {
            if (gameBoard[i + 1][j + 1] == ' ') sum++;
        }
    }

    return sum;
}