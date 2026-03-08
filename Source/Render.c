#include "TetrisTimeAttack.h"

bool isPlayerPiece;

/**
 * Formats & redraws the screen based off the global screen array. Colors are determined via characters
 */
void redrawScreen() {
    clear();
    int i, j;

    for (i = 0; i < BOARD_WIDTH + 2; i++) {
        for (j = 0; j < BOARD_HEIGHT + 2; j++) {
            if (gameBoard[i][j] == ' ') continue;

            if (gameBoard[i][j] == 'p') {
                gameBoard[i][j] = pieceColor(activePiece.tetronimoIndex);
                isPlayerPiece = true;
            }

            if (gameBoard[i][j] == 'T') attron(COLOR_PAIR(gameBoard[i][j]));
            else attron(COLOR_PAIR(gameBoard[i][j]) | A_STANDOUT);

            mvprintw(i, 2 * j, "  ");
            attroff(COLOR_PAIR(gameBoard[i][j]) | A_STANDOUT);
            if (isPlayerPiece) {
                gameBoard[i][j] = 'p';
                isPlayerPiece = false;
            }
            refresh(); // Ideally we'd only call this one but it freaks out if we have more than 4 of one char in a row otherwise
        }
    }
}