#include "TetrisTimeAttack.h"

#include "Initialize.c"
#include "Render.c"
#include "FileManager.c"
#include "MovementHandler.c"
#include "PieceManager.c"
#include "InputHandler.c"

long tickTimer = 0;

/**
 * Called once per delta time, used for any time-dependent game functionality (ie. handling piece movement)
 */
void tick() {
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

int main() {
    setlocale(LC_ALL, "");
    initscr(); // start ncurses
    noecho(); // don't write keyboard input to screen
    cbreak(); // allow input w/o needing to press enter (CTRL+C still passes)
    curs_set(0); // hide cursor
    keypad(stdscr, TRUE); // set keypad mode to true (allow arrow keys to give inputs)
    timeout(0); // make user input timeout immediately

    initGameGlobals();
    initPalette();
    initKickTable();
    srand(time(NULL));

    int temp;
    clock_t tickCounter = clock();

    attemptNewTurn(false, false);

    placePiece(activePiece);
    redrawGame();

    while (1) {
        if ((temp = getch()) != ERR) {
            lastIn = temp;
        }

        if ((float) tickCounter / CLOCKS_PER_SEC < (float) clock() / CLOCKS_PER_SEC - DELTA_TIME) {
            tickCounter = clock();
            tick();
        }
    }
}
