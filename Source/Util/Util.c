#include "../TetrisTimeAttack.h"

/**
 * Takes the base to the power of the exponent
 * @param base Base of the exponent (A -> A^B)
 * @param exp Power of the exponent (B -> A^B)
 * @return base^exp
 */
int scorePow(int base, int exp) {
    long powOut = base;
    while (exp > 1) {
        powOut *= base;
        exp--;
    }
    return powOut;
}

/**
 * Attempts to call the active screen's tick method once per delta time. If the tick counter overflows, crash the program.
 */
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
            case 'C':
                tickControls();
                break;
            case 'S':
                tickScoreWindow();
                break;
            case 'T':
                tickTutorial();
                break;
        }

        // Crash on overflow
        if (tickTimer < -1) {
            endwin();
            printf("You have been playing for 414 days consecutively. Frankly, this crash is for your own good.\n");
            exit(-1);
        }
    }
}

/**
 * Initializes a new ncurses screen and configures it with desired default values
 */
void startNCursesScreen() {
    setlocale(LC_ALL, ""); // Necessary for dithered characters to be printed
    initscr(); // start ncurses
    noecho(); // don't write keyboard input to screen
    cbreak(); // allow input w/o needing to press enter (CTRL+C still passes)
    curs_set(0); // hide cursor
    keypad(stdscr, TRUE); // set keypad mode to true (allow arrow keys to give inputs)
    timeout(0); // make user input timeout immediately
    initPalette();
}

/**
 * Cycles the selected menu option depending on
 * @param keyInput ncurses macro for movement direction (should be KEY_UP or KEY_DOWN)
 */
void cycleMenu(int keyInput, byte menuLength) {
    if (keyInput == KEY_UP)
        selectedOption--;
    else
        selectedOption++;

    if (selectedOption < 0) selectedOption = menuLength - 1;
    selectedOption = selectedOption % menuLength;
}

byte centered(char* text) {
    return -strlen(text) / 2;
}

bool isValidCharacter(int ncursesChar) {
    if (ncursesChar > 32 && ncursesChar < 128) return 1;
    return 0;
}