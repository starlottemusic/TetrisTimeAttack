#include "TetrisTimeAttack.h"

bool isPlayerPiece; // Set true if the piece being rendered is actively controlled by the player

/**
 * Formats & redraws the screen based off the global screen array
 * Colors are determined via chars w/ respect to the color pair table
 */
void redrawScreen() {
    clear();
    int i, j;

    for (i = 0; i < BOARD_WIDTH + 2; i++) {
        for (j = 0; j < BOARD_HEIGHT + 2; j++) {
            if (gameBoard[i][j] == ' ') continue;

            // Convert player pieces to their colorethe
            if (gameBoard[i][j] == 'p') {
                gameBoard[i][j] = pieceColor(activePiece.tetronimoIndex);
                isPlayerPiece = true;
            }

            if (gameBoard[i][j] == 'T') attron(COLOR_PAIR(gameBoard[i][j]));
            else attron(COLOR_PAIR(gameBoard[i][j]) | A_STANDOUT);

            mvprintw(i, 2 * j, "  ");
            attroff(COLOR_PAIR(gameBoard[i][j]) | A_STANDOUT);

            // Return player pieces to a detectable value
            if (isPlayerPiece) {
                gameBoard[i][j] = 'p';
                isPlayerPiece = false;
            }
            refresh(); // Ideally we'd only call this one but it freaks out if we have more than 4 of one char in a row otherwise
        }
    }
}