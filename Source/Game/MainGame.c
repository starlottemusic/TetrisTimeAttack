#include "../TetrisTimeAttack.h"

/**
 * Called once per delta time, used for any time-dependent game functionality (ie. handling piece movement)
 */
void tickGame() {
    int difficulty = 10;
    tickTimer++;

    if (tickTimer % 2 == 0)
        handleGameInput();

    if (tickTimer % difficulty == 0)
        attemptMovement(KEY_DOWN);

    if (turnCooldown > 0)
        turnCooldown--;
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
    srand(time(NULL));

    attemptNewTurn(false, false);

    placePiece(activePiece);
    redrawGame();

    while (screenState == 'G') {
        inputListener();
        tick();
    }

    if (isTimeAttack) {
        free(pieces1);
        free(pieces2);
        free(pieces3);
        free(pieces4);
    }
}