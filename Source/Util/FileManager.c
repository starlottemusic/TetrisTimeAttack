#include "../TetrisTimeAttack.h"

byte encryptionKey = 67;

/**
 * Attempts to read a file to the input pointer. If it doesn't exist, attempt to create it.
 *  RETURN: 1 if file exists, 0 if created, -1 if could not be created
 **/
byte createOrOpenFile(FILE **filePtrPtr, char *filePath) {
    mkdir("TTA_Data", 0777);
    *filePtrPtr = fopen(filePath, "r");
    if (*filePtrPtr == NULL) {
        *filePtrPtr = fopen(filePath, "w");
        if (*filePtrPtr == NULL) {
            return -1;
        }
        return 0;
    }
    return 1;
}

void loadConfig() {
    FILE *configFile;
    char temp[10];

    switch (createOrOpenFile(&configFile, "TTA_Data/config.ini")) {
        case 0: // Config file newly created
            setDefaultConfig();
            writeConfig(configFile);
            fclose(configFile);
            break;
        case 1: // Config file opened from existing
            fgets(temp, 10, configFile);
            keyMap.hardDrop = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.holdPiece = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.moveDown = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.moveRight = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.moveLeft = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.rotateCCW = atoi(temp);
            fgets(temp, 10, configFile);
            keyMap.rotateCW = atoi(temp);
            fclose(configFile);
            break;
        case -1: // Could not create or open config file
            setDefaultConfig();
            break;
        default:
            endwin();
            printf("ERROR: Config file createOrOpen returned OOB.");
            exit(-1);
    }
    updateConfigText();
}

void setDefaultConfig() {
    keyMap.hardDrop = ' ';
    keyMap.holdPiece = KEY_UP;
    keyMap.moveDown = KEY_DOWN;
    keyMap.moveRight = KEY_RIGHT;
    keyMap.moveLeft = KEY_LEFT;
    keyMap.rotateCCW = 'a';
    keyMap.rotateCW = 'd';
}

void saveConfig() {
    FILE *configFile = fopen("TTA_Data/config.ini", "w");

    if (configFile != NULL) {
        writeConfig(configFile);
        fclose(configFile);
    };
}

void writeConfig(FILE* filePtr) {
    char temp[10];

    sprintf(temp, "%d\n", keyMap.hardDrop);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.holdPiece);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.moveDown);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.moveRight);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.moveLeft);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.rotateCCW);
    fputs(temp, filePtr);
    sprintf(temp, "%d\n", keyMap.rotateCW);
    fputs(temp, filePtr);
}

/**
 * Encrypts a string for printing to leaderboards
 * @param text string to be encrypted
 */
void encryptText(char *text) {
    byte i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] == '\n') continue;
        text[i] += encryptionKey;
    }
}

/**
 * Decrypts a string for reading from leaderboards
 * @param text string to be decrypted
 */
void decryptText(char *text) {
    byte i;
    for (i = 0; i < strlen(text); i++) {
        if (text[i] == '\n') continue;
        text[i] -= encryptionKey;
    }
}

FILE* openLeaderboard(char accessMode[3]) {
    initLeaderboard();
    FILE *leaderboard = fopen("TTA_Data/TTA_LDBGLB.sav", accessMode);
    if (leaderboard == NULL) {
        leaderboard = fopen("TTA_Data/LDBLOC.sav", accessMode);
    }
    return leaderboard;
}