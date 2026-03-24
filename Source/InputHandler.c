#include "TetrisTimeAttack.h"

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
            //TODO add hold
            break;
        case KEY_DOWN:
            attemptMovement(KEY_DOWN);
            lastIn = ERR;
            break;
        case 'd': case 'D':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
            placePiece(activePiece);
            redrawScreen();
            lastIn = ERR;
            break;
        case 'a': case 'A':
            clearPiece(activePiece);
            rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
            placePiece(activePiece);
            redrawScreen();
            lastIn = ERR;
            break;
    }
}