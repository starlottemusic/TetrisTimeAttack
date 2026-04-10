#include "../TetrisTimeAttack.h"
int slide = 0, frame=0;

void mainTutorial() {
    initGameGlobals();
    startNCursesScreen();
    clear();

    slide = 0;
    frame = 0;

    while (slide >= 0 && slide <= 3) {
        inputListener();
        tick();
    }

    endwin();
    screenState = 'M';
}

void tickTutorial() {
    static byte tickCounter = 0;
    tickCounter++;

    // Update current frame
    if (tickCounter >= 60) {
        frame++;
        if (frame > 3)
            frame = 0;
        tickCounter = 0;
    }

    // Update current slide
    if (lastInput == KEY_LEFT) {
        slide--;
        lastInput = ERR;
    }

    if (lastInput == KEY_RIGHT) {
        slide++;
        lastInput = ERR;
    }

    // Print next/back/exit buttons
    if (slide==0)
        mvprintw(22,3,"Exit");
    else
        mvprintw(22,3,"Back");

    if (slide==3)
        mvprintw(22,60,"Exit");
    else
        mvprintw(22,60,"Next");

    mvprintw(22,12,"Move left and right to navigate tutorial");

    // Print tutorial text depending on slide
    switch (slide) {
        case 0:
            mvprintw(18, 2, "                                                                                ");
            mvprintw(18, 8, "Complete lines to clear the board and score points.");
            break;
        case 1:
            mvprintw(18, 2, "                                                                                ");
            mvprintw(18, 17, "After 4 moves, the board resets.");
            break;
        case 2:
            mvprintw(18, 2, "                                                                                ");
            mvprintw(18, 4, "The next run, your previous moves play over your new ones.");
            break;
        case 3:
            mvprintw(18, 2, "                                                                                ");
            mvprintw(18, 9, "Clearing lines removes old moves from the queue.");
            break;
        default:
            break;
    }

    // Draw tutorial matrix to slide
    assignMatrix(slide, frame);
    redrawBoard(SLIDE_WIDTH,SLIDE_HEIGHT,mat,11,10);
    refresh();
}

char assignMatrix(int s, int f) {
    switch (s) {
        case 0: // Slide 0
            switch (f) {
                case 0: { // Frame 0
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
                case 1: { // Frame 1
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
                case 2: { // Frame 2
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBSBBBBBBB",
                        "BZSSBBBBBB",
                        "++++++++++",
                        "++++++++++",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
                }
                case 3: { // Frame 3
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBSBBBBBBB",
                        "BZSSBBBBBB",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
                }
                default:
                    break;
            }
            break;
        case 1: // Slide 1
            switch (f) {
            case 0: { // Frame 0
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBJBBBBB",
                    "BBBBJJJBBB",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                break;
            }
            case 1: { // Frame 1
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBBOOBBB",
                    "BBBBJOOBBB",
                    "BBBBJJJBBB",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                break;
            }
            case 2: { // Frame 2
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBBLLLBBB",
                    "BBBBLOOBBB",
                    "BBBBJOOBBB",
                    "BBBBJJJBBB",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                break;
            }
            case 3: { // Frame 3
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "BBBBBBBBBB",
                    "BBBBBBBBBB",
                    "BBBILLLBBB",
                    "BBBILOOBBB",
                    "BBBIJOOBBB",
                    "BBBIJJJBBB",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                break;
            }
                default:
                    break;
            }
            break;
        case 2: // Slide 2
            switch (f) {
                case 0: { // Frame 0
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBIIIIBBB",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
                }
            case 1: { // Frame 1
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBB+BBBBB",
                        "BBBB+++BBB",
                        "BBBIIIIBBB",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
            }
            case 2: { // Frame 2
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBBBBBBB",
                        "BBBBJBLLBB",
                        "BBBBJJJLBB",
                        "BBBIIIILBB",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
            }
            case 3: { // Frame 3
                    char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                        "BBBBBBBBBB",
                        "BBBBB++BBB",
                        "BBBBB++BBB",
                        "BBBBJBLLBB",
                        "BBBBJJJLBB",
                        "BBBIIIILBB",
                        };
                    memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                    break;
            }
            default:
                    break;
            }
            break;
        case 3: // Slide 3
            switch (f) {
            case 0: { // Frame 0
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "B+BJBBBB+",
                    "B+BJJJBB+",
                    "B+BBBBBB+",
                    "B+BIIIIB+",
                    "B+BBBBBB+",
                    "B+BTTTBB+",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                mvprintw(10,10,"Oldest ->");
                break;
            }
            case 1: { // Frame 1
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "B+BJBBBB+",
                    "B+BJJJBB+",
                    "B+BBBBBB+",
                    "B+BIIIIB+",
                    "B+BBBBBB+",
                    "B+BTTTBB+",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                mvprintw(10,10,"         ");
                mvprintw(13,10,"Newest ->");
                break;
            }
            case 2: { // Frame 2
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "B+BJBBBB+",
                    "B+BJJJBB+",
                    "B+BBBBBB+",
                    "B+BIIIIB+",
                    "B+BBBBBB+",
                    "B+BTTTBB+",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                mvprintw(13,10,"         ");
                mvprintw(8,26,"[LINE CLEAR]");
                break;
            }
            case 3: { // Frame 3
                char temp[SLIDE_HEIGHT][SLIDE_WIDTH] = {
                    "B+BIIIIB+",
                    "B+BBBBBB+",
                    "B+BTTTBB+",
                    "B+BBTBBB+",
                    "B+BBBBBB+",
                    "B+BZZBBB+",
                    };
                memcpy(mat, temp, SLIDE_HEIGHT*SLIDE_WIDTH);
                mvprintw(8,30,"            ");
                break;
            }
            default:
                    break;
            }
            break;
        default:
            break;
    }
}