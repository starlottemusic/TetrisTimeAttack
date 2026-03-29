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

    // Crash on overflow
    if (tickTimer < -1) {
        endwin();
        printf("You have been playing for 414 days consecutively. Frankly, this crash is for your own good.\n");
        exit(-1);
    }
}

void mainGame() {
    screenState = 'G';
    startNCursesScreen();

    initGameGlobals();
    initPalette();
    initKickTable();
    srand(time(NULL));

    attemptNewTurn(false, false);

    placePiece(activePiece);
    redrawGame();

    while (1) {
        readInput();
        tick();
    }
}