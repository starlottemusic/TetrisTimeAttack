#include "TetrisTimeAttack.h"

bool isPlayerPiece; // Set true if the piece being rendered is actively controlled by the player

/**
 * Formats & redraws the screen based off the global screen array
 * Colors are determined via chars w/ respect to the color pair table
 */
void redrawBoard(int rows, int cols, char renderArray[][rows], byte x, byte y) {
    int i, j;

    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            if (renderArray[i][j] == ' ') continue;

            // Convert player pieces to their color name for rendering
            if (renderArray[i][j] == 'p') {
                renderArray[i][j] = pieceColorName(activePiece.tetronimoIndex);
                isPlayerPiece = true;
            }

            byte color = pieceColorID(renderArray[i][j]);
            attron(COLOR_PAIR(color) | A_STANDOUT);
            mvprintw(y + i, 2 * (x + j), "  "); // TODO change to "▒▒" in prc
            attroff(COLOR_PAIR(color) | A_STANDOUT);

            // Return player pieces to expected value
            if (isPlayerPiece) {
                renderArray[i][j] = 'p';
                isPlayerPiece = false;
            }
            refresh(); //TODO Only call once in prclab1 (have to call every pixel due to issue w/ clion terminal)
        }
    }
}

/**
 * Redraws all game relevant boards
 */
void redrawGame() {
    clear();
    redrawBoard(GAMEBOARD_HEIGHT, GAMEBOARD_WIDTH, gameBoard, 1, 1);
    redrawBoard(HOLD_HEIGHT, HOLD_WIDTH, holdSlot, 14, 1);
}