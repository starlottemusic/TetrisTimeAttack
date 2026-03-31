#include "../TetrisTimeAttack.h"

/**
 * Reads keyboard input and stores it in lastInput
 */
void readInput() {
    int temp;
    if ((temp = getch()) != ERR) {
        lastInput = temp;
    }
}

/**
 * Handles specific key inputs in the menu
 */
void handleMenuInput() {
    switch (lastInput) {
        case KEY_UP:
            cycleMenu(KEY_UP);
            lastInput = ERR;
            break;
        case KEY_DOWN:
            cycleMenu(KEY_DOWN);
            lastInput = ERR;
            break;
        case KEY_ENTER: case ' ': case 10: // Enter, space, or line feed
            selectMenuOption();
            lastInput = ERR;
            break;
    }
}

/**
 * Handles specific key inputs during gameplay
 */
void handleGameInput() {
    switch (lastInput) {
        case KEY_LEFT:
            attemptMovement(KEY_LEFT);
            lastInput = ERR;
            break;
        case KEY_RIGHT:
            attemptMovement(KEY_RIGHT);
            lastInput = ERR;
            break;
        case KEY_UP:
            holdPiece();
            lastInput = ERR;
            break;
        case KEY_DOWN:
            attemptMovement(KEY_DOWN);
            score++;
            lastInput = ERR;
            break;
        case 'd':
        case 'D':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
            placePiece(activePiece);
            redrawGame();
            lastInput = ERR;
            break;
        case 'a':
        case 'A':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
            placePiece(activePiece);
            redrawGame();
            lastInput = ERR;
            break;
        case ' ':
            while (turnCooldown <= 0) {
                attemptMovement(KEY_DOWN);
                score++;
            }
            turnCooldown = 0;
            lastInput = ERR;
            break;
    }
}
