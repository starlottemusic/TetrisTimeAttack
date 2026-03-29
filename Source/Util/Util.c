#include "../TetrisTimeAttack.h"

/**
 * Takes the base to the power of the exponent
 * @param base Base of the exponent (A -> A^B)
 * @param exp Power of the exponent (B -> A^B)
 * @return base^exp
 */
long scorePow(int base, int exp) {
    long powOut = base;
    while (exp > 1) {
        powOut *= base;
        exp--;
    }
    return powOut;
}

void tick() {
    static clock_t tickCounter = -RAND_MAX;

    if ((float) tickCounter / CLOCKS_PER_SEC < (float) clock() / CLOCKS_PER_SEC - DELTA_TIME) {
        tickCounter = clock();
        switch (screenState) {
            case 'G':
                tickGame();
                break;
            case 'M':
                tickMenu();
                break;
        }
    }
}

void startNCursesScreen() {
    setlocale(LC_ALL, "");
    initscr(); // start ncurses
    noecho(); // don't write keyboard input to screen
    cbreak(); // allow input w/o needing to press enter (CTRL+C still passes)
    curs_set(0); // hide cursor
    keypad(stdscr, TRUE); // set keypad mode to true (allow arrow keys to give inputs)
    timeout(0); // make user input timeout immediately
    initPalette();
}