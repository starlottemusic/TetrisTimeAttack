#include "../TetrisTimeAttack.h"

byte selectedOption;
byte menuCooldown;

/**
 * Cycles the selected menu option depending on
 * @param keyInput ncurses macro for movement direction (should be KEY_UP or KEY_DOWN)
 */
void cycleMenu(int keyInput) {
    if (keyInput == KEY_UP)
        selectedOption--;
    else
        selectedOption++;

    if (selectedOption < 0) selectedOption = MENU_LENGTH - 1;
    selectedOption = selectedOption % MENU_LENGTH;
}

/**
 * Sets the screen state to the desired state depending on the highlighted menu option
 */
void selectMenuOption() {
    switch (selectedOption) {
        case 0:
            screenState = 'G';
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            screenState = 'E';
            break;
        default:
            break;
    }
}

/**
 * Main class for the menu screen
 */
void mainMenu() {
    screenState = 'M';
    startNCursesScreen();
    initMenuGlobals();
    selectedOption = 0;

    while (screenState != 'E') {
        readInput();
        tickMenu();
        redrawMenu(selectedOption);

        if (menuCooldown <= 0) {
            switch (screenState) {
                case 'G':
                    endwin();
                    mainGame();
                    startNCursesScreen();
                    clear();
                    menuCooldown = 120;
                    break;
                case 'M': default:
                    break;
            }
        } else {
            screenState = 'M';
            lastInput = ERR;
        }
    }
    endwin();
    exit(0);
}

/**
 * Time-based inputs for menu, called once per delta time
 */
void tickMenu() {
    handleMenuInput();

    if (menuCooldown > 0) {
        menuCooldown--;
    }
}
