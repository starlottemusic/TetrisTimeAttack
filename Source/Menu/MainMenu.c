#include "../TetrisTimeAttack.h"

byte menuCooldown;

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
            screenState = 'T';
            break;
        case 3:
            screenState = 'C';
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

    while (screenState != 'E') {
        inputListener();
        tick();
        redrawMenu();

        if (menuCooldown <= 0) {
            switch (screenState) {
                case 'G':
                    endwin();
                    mainGame();
                    startNCursesScreen();
                    clear();
                    menuCooldown = 30;
                    break;
                case 'T':
                    endwin();
                    startNCursesScreen();
                    clear();
                    runAnim();
                case 'C':
                    endwin();
                    mainControls();
                    selectedOption = 0;
                    startNCursesScreen();
                    clear();
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
    handleMenuInput(MENU_LENGTH);

    if (menuCooldown > 0) {
        menuCooldown--;
    }
}
