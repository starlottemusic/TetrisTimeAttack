#include "../TetrisTimeAttack.h"

/**
 * Attempts to read a file to the input pointer. If it doesn't exist, attempt to create it.
 *  RETURN: 1 if file exists, 0 if created, -1 if could not be created
 **/
byte createOrOpenFile(FILE *filePtr, char *filePath) {
    filePtr = fopen(filePath, "r");
    if (filePtr == NULL) {
        filePtr = fopen(filePath, "w");
        if (filePtr == NULL) {
            printf("DEBUG: Error creating file.\n");
            return -1;
        }
        printf("DEBUG: File opened successfully.\n");
        return 0;
    }
    printf("DEBUG: File created successfully.\n");
    return 1;
}

void loadConfig() {
    FILE* configFile;
    //TODO: Set default config values
    if (createOrOpenFile(configFile, "config.txt") == 1) {
        //TODO: Read config values
    }
}
