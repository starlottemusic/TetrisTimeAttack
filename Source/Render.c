#include "TetrisTimeAttack.h"

bool isPlayerPiece; // Set true if the piece being rendered is actively controlled by the player

/**
 * Formats & redraws the screen based off the global screen array
 * Colors are determined via chars w/ respect to the color pair table
 */
void redrawBoard(int cols, int rows, char renderArray[][cols], byte x, byte y) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
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
    redrawBoard(GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT, gameBoard, 1, 1);
    redrawBoard(INFO_WIDTH, HOLD_HEIGHT, holdBoard, 14, 1);
    redrawBoard(INFO_WIDTH, NEXT_HEIGHT, nextBoard, 14, HOLD_HEIGHT);
}
