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

            // Convert player pieces to their color name for rendering
            if (gameBoard[i][j] == 'p') {
                gameBoard[i][j] = pieceColorName(activePiece.tetronimoIndex);
                isPlayerPiece = true;
            }

            byte color = pieceColorID(gameBoard[i][j]);
            attron(COLOR_PAIR(color) | A_STANDOUT);
            mvprintw(i, 2 * j, "%c", activePiece.rotation); //TODO Replace w/ ¦¦ in prc
            attroff(COLOR_PAIR(color) | A_STANDOUT);

            // Return player pieces to expected value
            if (isPlayerPiece) {
                gameBoard[i][j] = 'p';
                isPlayerPiece = false;
            }
            refresh(); //TODO Only call once in prclab1 (have to call every pixel due to issue w/ clion terminal)
        }
    }
}