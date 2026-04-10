#include "../TetrisTimeAttack.h"

/**
 * Called once per delta time, used for any time-dependent game functionality (ie. handling piece movement)
 */
void tickGame() {
    tickTimer++;

    if (tickTimer % 2 == 0)
        handleGameInput();

    if (tickTimer % getDifficulty() == 0)
        attemptMovement(KEY_DOWN);

    if (turnCooldown > 0)
        turnCooldown--;
}

int getDifficulty() {
    int difficulty = 30;
    float scoreMultiplier = ((float) score) / 25000.0f;
    if (scoreMultiplier > 1) scoreMultiplier = 1;
    difficulty -= (int) (25.0f * scoreMultiplier);
    if (isTimeAttack)
        difficulty *= 2;
    return difficulty;
}

/**
 * The "main()" function the game, called from the menu. Runs until gamestate is changed from 'G'
 */
void mainGame() {
    startNCursesScreen();

    if (isTimeAttack)
        initializePastChannels();
    initGameGlobals();
    initPalette();
    initKickTable();

    attemptNewTurn(false, false);

    placePiece(activePiece);
    redrawGame();

    while (screenState == 'G') {
        inputListener();
        tick();
    }

    if (isTimeAttack) {
        past->pieceCount = 0;
        free(pieces1);
        free(pieces2);
        free(pieces3);
        free(pieces4);
    }
}