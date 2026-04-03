#include "../TetrisTimeAttack.h"

byte menuCooldown;
byte textCooldown;
byte textIndex;

/**
 * Sets the screen state to the desired state depending on the highlighted menu option
 */
void selectControlOption() {
    if (selectedOption == 7) {
        screenState = 'M';
        return;
    }
    startRebind(selectedOption);
}

void updateConfigText() {
    appendKeyName(0, keyMap.moveLeft);
    appendKeyName(1, keyMap.moveDown);
    appendKeyName(2, keyMap.moveRight);
    appendKeyName(3, keyMap.rotateCCW);
    appendKeyName(4, keyMap.rotateCW);
    appendKeyName(5, keyMap.hardDrop);
    appendKeyName(6, keyMap.holdPiece);
}

/**
 * Main class for the controls screen
 */
void mainControls() {
    screenState = 'C';
    startNCursesScreen();
    selectedOption = 0;
    menuCooldown = 120;
    textCooldown = 0;
    clear();
    refresh();

    while (screenState == 'C') {
        inputListener();
        tick();
        redrawControls(textCooldown > 0, textIndex);
    }
}

void appendKeyName(int configIndex, int key) {
    char fixedName[40] = "";
    char keyName[20];

    byte nameLength = strlen(controlConfigs[configIndex]) - strlen(strchr(controlConfigs[configIndex], '-')) + 2;
    strncat(fixedName, controlConfigs[configIndex], nameLength);

    if (key <= 256 && key != ' ') {
        sprintf(keyName, "%c", key);
        keyName[0] = toupper(keyName[0]);
        strcat(fixedName, keyName);
    } else {
        getNcursesKeyName(key, keyName);
        strcat(fixedName, keyName);
    }

    strcpy(controlConfigs[configIndex], fixedName);
}

/**
 * Returns the name of an extended char as defined by NCurses
 * @param keyIndex The index of the NCurses key (usually defined by a macro
 * @param nameOut
 */
void getNcursesKeyName(int keyIndex, char *nameOut) {
    switch (keyIndex) {
        case ' ':
            strcpy(nameOut, "SPACE");
            break;
        case KEY_DOWN:
            strcpy(nameOut, "DOWN");
            break;
        case KEY_UP:
            strcpy(nameOut, "UP");
            break;
        case KEY_LEFT:
            strcpy(nameOut, "LEFT");
            break;
        case KEY_RIGHT:
            strcpy(nameOut, "RIGHT");
            break;
        default:
            sprintf(nameOut, "%d", keyIndex);
            break;
    }
}

void startRebind(byte index) {
    bool waiting = true;
    lastInput = ERR;
    byte messageLength = strlen(controlConfigs[index]);

    mvprintw(10, LOGO_WIDTH - messageLength / 2 - 6, controlFeedback[0], controlConfigs[index]);
    mvprintw(11, LOGO_WIDTH - 6, controlFeedback[1]);

    while (waiting) {
        inputListener();
        if (lastInput != ERR) {
            waiting = false;
            if (lastInput == 27) {
                textIndex = 3;
            } else {
                textIndex = 2;
                bindKey(index, lastInput);
                updateConfigText();
                saveConfig();
            }
        }
    }
    clear();
    textCooldown = 120;
    redrawControls(textCooldown > 0, textIndex);
    lastInput = ERR;
    refresh();
}

void bindKey(byte index, int key) {
    switch (index) {
        case 0:
            keyMap.moveLeft = key;
            break;
        case 1:
            keyMap.moveDown = key;
            break;
        case 2:
            keyMap.moveRight = key;
            break;
        case 3:
            keyMap.rotateCCW = key;
            break;
        case 4:
            keyMap.rotateCW = key;
            break;
        case 5:
            keyMap.hardDrop = key;
            break;
        case 6:
            keyMap.holdPiece = key;
            break;
        default:
            endwin();
            printf("ERROR: Attempted to bind invalid key.");
            exit(-1);
    }
}

/**
 * Time-based inputs for menu, called once per delta time
 */
void tickControls() {
    handleMenuInput(CONTROLS_LENGTH);

    if (textCooldown >= 0) {
        textCooldown--;
    }

    if (textCooldown == 0) {
        clear();
        redrawControls(false, textIndex);
    }

    if (menuCooldown > 0) {
        menuCooldown--;
    }
}
