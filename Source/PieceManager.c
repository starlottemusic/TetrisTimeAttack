#include "TetrisTimeAttack.h"

/**
 * Returns the size of a piece from the Tetronimos array
 * @param index The index of the piece in the array
 * @return The size of the piece
 */
byte pieceSize(byte index) {
    if (index == 0 || index == 3) return 4; // I & O pieces
    return 3; // other pieces
}

/**
 * Gets the color of a piece from its respective index in the tetronimos array
 * @param index The index of the tetronimo in the array
 * @return The color pair index
 */
char pieceColor(byte index) {
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
 * Resets activePlayerPiece at the initial spawn point
 * @param index The index of the piece to be spawned from the tetronimos array
 */
void newTurnPlayerPiece(byte index) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            activePiece.tetronimo[i][j] = tetronimos[index][i][j] == ' ' ? tetronimos[index][i][j] : 'p';
        }
    }
    activePiece.tetronimoIndex = index;
    activePiece.x = 1;
    activePiece.y = 0;
}
