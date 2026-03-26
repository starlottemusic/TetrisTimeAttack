#include "TetrisTimeAttack.h"

extern void holdPiece();

/**
 * Handles keyboard input during gameplay
 */
void handleGameInput() {
    switch (lastIn) {
        case KEY_LEFT:
            attemptMovement(KEY_LEFT);
            lastIn = ERR;
            break;
        case KEY_RIGHT:
            attemptMovement(KEY_RIGHT);
            lastIn = ERR;
            break;
        case KEY_UP:
            holdPiece();
            lastIn = ERR;
            break;
        case KEY_DOWN:
            attemptMovement(KEY_DOWN);
            lastIn = ERR;
            break;
        case 'd': case 'D':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
            placePiece(activePiece);
            redrawGame();
            lastIn = ERR;
            break;
        case 'a': case 'A':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
            placePiece(activePiece);
            redrawGame();
            lastIn = ERR;
            break;
        case ' ':
            while (turnCooldown <= 0)
                attemptMovement(KEY_DOWN);
            turnCooldown = 0;
            lastIn = ERR;
            break;
    }
}