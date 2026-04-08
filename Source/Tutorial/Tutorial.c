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

    assignMatrix(slide, frame);
    redrawBoard(6,10,mat,23,12);
    refresh();
}

char assignMatrix(int s, int f) {
    switch (s) {
        case 0:
            switch (f) {
                case 0:
                    char temp[6][10] = {
                    "    OO    ",
                    "    OO    ",
                    "  S       ",
                    " ZSS      ",
                    "ZZTS  LLLJ",
                    "ZTTT  LJJJ",
                    };
                    memcpy(mat, temp, 60);
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;

        case 1:
            switch (f) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;

        case 2:
            switch (f) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;

        case 3:
            switch (f) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;

        default:
            break;

    }
}