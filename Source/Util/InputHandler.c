#include "../TetrisTimeAttack.h"

extern void holdPiece();

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
 * Handles keyboard input during gameplay
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
            lastInput = ERR;
            break;
        case 'd': case 'D':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
            placePiece(activePiece);
            redrawGame();
            lastInput = ERR;
            break;
        case 'a': case 'A':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
            placePiece(activePiece);
            redrawGame();
            lastInput = ERR;
            break;
        case ' ':
            while (turnCooldown <= 0)
                attemptMovement(KEY_DOWN);
            turnCooldown = 0;
            lastInput = ERR;
            break;
    }
}