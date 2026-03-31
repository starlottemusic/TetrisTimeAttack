#include <ctype.h>

#include "../TetrisTimeAttack.h"

/**
 * Reads keyboard input and stores it in lastInput
 */
void readInput() {
    int temp;
    if ((temp = getch()) != ERR) {
        temp = tolower(temp);
        lastInput = temp;
    }
}

/**
 * Handles specific key inputs for menus
 */
void handleMenuInput(byte menuLength) {
    switch (lastInput) {
        case KEY_UP:
            cycleMenu(KEY_UP, menuLength);
            lastInput = ERR;
            break;
        case KEY_DOWN:
            cycleMenu(KEY_DOWN, menuLength);
            lastInput = ERR;
            break;
        case KEY_ENTER:
        case ' ':
        case 10: // Enter, space, or line feed
            if (screenState == 'C') {
                selectControlOption();
            } else {
                selectMenuOption();
            }
            lastInput = ERR;
            break;
    }
}

/**
 * Handles specific key inputs during gameplay
 */
void handleGameInput() {
    // Horrible giant if statement because switch cases are constant at compilation
    if (lastInput == keyMap.holdPiece) {
        holdPiece();
    } else if (lastInput == keyMap.moveLeft) {
        attemptMovement(KEY_LEFT);
    } else if (lastInput == keyMap.moveRight) {
        attemptMovement(KEY_RIGHT);
    } else if (lastInput == keyMap.moveDown) {
        attemptMovement(KEY_DOWN);
        score++;
    } else if (lastInput == keyMap.rotateCW) {
        clearPiece(activePiece);
        rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
        placePiece(activePiece);
        redrawGame();
    } else if (lastInput == keyMap.rotateCCW) {
        clearPiece(activePiece);
        rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
        placePiece(activePiece);
        redrawGame();
    } else if (lastInput == keyMap.hardDrop) {
        while (turnCooldown <= 0) {
            attemptMovement(KEY_DOWN);
            score++;
        }
        turnCooldown = 0;
    } else return;
    lastInput = ERR;
}
