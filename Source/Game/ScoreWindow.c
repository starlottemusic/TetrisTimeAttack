#include "../TetrisTimeAttack.h"

char windowBorder[9][15] = {
    "+++++++++++++++",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+BBBBBBBBBBBBB+",
    "+++++++++++++++"
};

void scoreWindow() {
    redrawBoard(15, 9, windowBorder, 4, SCORE_WINDOW_OFFSET);
    char scoreText[50];

    sprintf(scoreText, "Your score was: %d", score);

    mvprintw(SCORE_WINDOW_OFFSET + 2, 23 + centered("Game Over!"), "Game Over!");
    mvprintw(SCORE_WINDOW_OFFSET + 3, 23 + centered(scoreText), scoreText);
    mvprintw(SCORE_WINDOW_OFFSET + 5, 23 + centered("Enter your initials:"), "Enter your initials:");

    while (screenState == 'S') {
        inputListener();
        tick();
    }
}

void tickScoreWindow() {
    static byte textLength = 0;
    static char name[3];

    if (isValidCharacter(lastInput) && textLength < 3) {
        lastInput = toupper(lastInput);
        name[textLength] = lastInput;
        textLength++;
        lastInput = ERR;
    } else if ((lastInput == 263 || lastInput == 8) /*backspace*/ && textLength > 0) {
        textLength--;
        name[textLength] = ' ';
        lastInput = ERR;
    }

    if (lastInput == '\n' && textLength == 3) {
        lastInput = ERR;
        saveScore(name);
        screenState = 'M';
    }

    mvprintw(SCORE_WINDOW_OFFSET + 6, 21, "%s", name);
}

void saveScore(char* name) {
    char formattedName[50];

    sprintf(formattedName, "%s - %d\n", name, score);

    encryptText(formattedName);

    FILE* leaderboard = openLeaderboard("a");
    if (leaderboard == NULL)
        return;
    fputs(formattedName, leaderboard);
    fclose(leaderboard);
}