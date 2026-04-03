#include "../TetrisTimeAttack.h"

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
            refresh(); //Remove in prc (have to call every pixel due to issue w/ clion terminal)
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
    attron(COLOR_PAIR(9) | A_STANDOUT);
    mvprintw(1, 5, "SCORE: %d", score);
    mvprintw(1, 34, "HOLD");
    mvprintw(HOLD_HEIGHT, 34, "NEXT");
    attroff(COLOR_PAIR(9) | A_STANDOUT);
    refresh();
}

/**
 * Redraw the main menu (options & logo) with selected option highlighted
 * @param selectedOption The index of the selected option
 */
void redrawMenu() {
    byte i;

    redrawBoard(LOGO_WIDTH, LOGO_HEIGHT, menuLogo, 1, 1);

    for (i = 0; i < MENU_LENGTH; i++) {
        if (i == selectedOption)
            attron(A_STANDOUT);
        mvprintw(i + LOGO_HEIGHT + 4, LOGO_WIDTH - 6, "%s", menuOptions[i]);
        attroff(A_STANDOUT);
    }

    refresh();
}

/**
 * Redraw the control config screen with selected option highlighted
 * @param selectedOption The index of the selected option
 */
void redrawControls(bool drawTextOut, int textOutIndex) {
    byte i;

    for (i = 0; i < CONTROLS_LENGTH; i++) {
        if (i == selectedOption)
            attron(A_STANDOUT);

        mvprintw(i + LOGO_HEIGHT + 4, LOGO_WIDTH - 6, "%s", controlConfigs[i]);
        attroff(A_STANDOUT);
    }

    if (drawTextOut) {
        mvprintw(11, LOGO_WIDTH - 6, controlFeedback[textOutIndex]);
    }

    refresh();
}