#include "../TetrisTimeAttack.h"
int slide = 0, frame=0;

void mainTutorial() {
    initGameGlobals();
    startNCursesScreen();
    clear();

    while (slide >= 0 && slide <= 4) {
        inputListener();
        tick();
    }

    endwin();
    screenState = 'M';
}

void tickTutorial(byte tickCounter) {
    if (tickCounter % 30 == 0) {
        frame++;
        if (frame == 4)
            frame = 0;
    }
    if (slide==0)
        mvprintw(22,3,"Exit");
    else
        mvprintw(22,3,"Back");

    if (slide==3)
        mvprintw(22,60,"Exit");
    else
        mvprintw(22,60,"Next");

    mvprintw(22,12,"Move left and right to navigate tutorial");

    switch (slide) {
        case 0:
            mvprintw(18, 8, "Complete lines to clear the board and score points.");
            break;
        case 1:
            mvprintw(18, 17, "After 4 moves, the board resets.");
            break;
        case 2:
            mvprintw(18, 4, "The next run, your previous moves play over your new ones.");
            break;
        case 3:
            mvprintw(18, 9, "Clearing lines removes old moves from the queue.");
            break;
        default:
            break;
    }

    assignMatrix(slide, frame);
    redrawBoard(SLIDE_WIDTH,SLIDE_HEIGHT,mat,11,10);
    refresh();
}

char assignMatrix(int s, int f) {
    switch (s) {
        case 0:
            switch (f) {
                case 0: {
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBOOBBBB",
                        "BBBBOOBBBB",
                        "BBSBBBBBBB",
                        "BZSSBBBBBB",
                        "ZZTSBBLLLJ",
                        "ZTTTBBLJJJ",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
                }
                case 1: {
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBSBBBBBBB",
                        "BZSSBBBBBB",
                        "ZZTSOOLLLJ",
                        "ZTTTOOLJJJ",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
                }
                case 2: {
                    break;
                }
                case 3: {
                    break;
                }
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