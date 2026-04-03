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
    redrawBoard(15, 9, windowBorder, 4, 10);
    char scoreText[50];

    sprintf(scoreText, "Your score was: %lu", score);

    mvprintw(12, 23 + centered("Game Over!"), "Game Over!");
    mvprintw(13, 23 + centered(scoreText), scoreText);
    mvprintw(15, 23 + centered("Enter your initials:"), "Enter your initials:");

    while (screenState == 'S') {
        inputListener();
        tick();
    }
}

void tickScoreWindow() {
    if (lastInput == '\n') {
        lastInput = ERR;
        screenState = 'M';
    }
}