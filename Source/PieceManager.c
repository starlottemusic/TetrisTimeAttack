#include "TetrisTimeAttack.h"

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
byte pieceColorID(char colorName) { //TODO consider just updating the array so we dont have to run this constantly
    switch (colorName) {
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

void attemptNewTurn() {
    byte i, j;
    char color = pieceColorName(activePiece.tetronimoIndex);
    for (i = 1; i <= BOARD_WIDTH; i++) {
        for (j = 1; j <= BOARD_HEIGHT; j++) {
            if (gameBoard[i][j] == 'p')
                gameBoard[i][j] = color;
        }
    }

    newTurnPlayerPiece(rand() % 7);
}

/**
 * Resets activePlayerPiece at the initial spawn point if possible (no collisions)
 * @param index The index of the piece to be spawned from the tetronimos array
 * @return True - Piece can be placed safely; False - Piece will collide
 */
bool newTurnPlayerPiece(byte index) {
    openSpace = getOpenSpaces() - 4;
    byte x, y;

    byte i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            activePiece.tetronimo[i][j] = tetronimos[index][i][j] == ' ' ? tetronimos[index][i][j] : 'p';
        }
    }

    activePiece.tetronimoIndex = index;
    activePiece.x = 4;
    activePiece.y = (index == 1 || index == 2 || index == 5) ? 1 : 0; // L, J, and T pieces need to spaw
    activePiece.rotation = '0';

    placePiece(activePiece);

    if (openSpace != getOpenSpaces())
        return false;
    return true;
}
