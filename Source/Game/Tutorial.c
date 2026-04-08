#include "../TetrisTimeAttack.h"
int slide = 0, frame = 0; //Automate

void mainTutorial() {
    initGameGlobals();
    startNCursesScreen();
    clear();

    // increase frame every second (delta time?)

    while (slide >= 0 && slide <= 4) {
        inputListener();
        tick();
    }

    endwin();
    screenState = 'M';
}

void tickTutorial() {
    if (slide==0)
        mvprintw(22,3,"Exit");
    else
        mvprintw(22,3,"Back");

    if (slide==3)
        mvprintw(22,60,"Exit");
    else
        mvprintw(22,60,"Next");

    mvprintw(24,23,"23252729313335373941");

    switch (slide) {
        case 0:
            mvprintw(20, 7, "Complete lines to clear the board and score points.");
            break;
        case 1:
            mvprintw(20, 17, "After 4 moves, the board resets.");
            break;
        case 2:
            mvprintw(20, 4, "The next run, your previous moves play over your new ones.");
            break;
        case 3:
            mvprintw(20, 9, "Clearing lines removes old moves from the queue.");
            break;
        default:
            break;
    }

    char mat[6][10];

    drawMatrix(6,10,mat,23,12);
    refresh();
}

void drawMatrix(int rows, int cols, int renderArray[][cols], byte x, byte y) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (renderArray[i][j] == 0) continue;

            attron(COLOR_PAIR(renderArray[i][j]) | A_STANDOUT);
            mvprintw(y + i, 2 * (x + j), "  "); // TODO change to "▒▒" in prc
            attroff(COLOR_PAIR(renderArray[i][j]) | A_STANDOUT);

            refresh(); //Remove in prc (have to call every pixel due to issue w/ clion terminal)
        }
    }
}