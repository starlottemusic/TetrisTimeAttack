#include "../TetrisTimeAttack.h"

int slide = 0, frame = 0; //Automate

void mainTutorial() {
    int frame;
    initGameGlobals();
    startNCursesScreen();
    clear();

    // increase frame every second (delta time?)

    // create back and next buttons
    // increase slide when user presses next
    // decrease slide when user presses back
    // replace back with exit on slide 0 and next with exit on slide 3

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
            drawFrame(slide, frame);
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
    refresh();
}

void drawFrame(int s, int f) {
    switch (s) {
        case 0: // Tetris slide
            switch (f) {
                case 0:
                    attron(COLOR_PAIR(7) | A_STANDOUT);
                    mvprintw(16, 31, "▒▒");
                    mvprintw(17, 29, "▒▒▒▒▒▒▒▒▒▒");
                    mvprintw(18, 29, "▒▒▒▒▒▒▒▒▒▒▒▒");
                    attron(COLOR_PAIR(6) | A_STANDOUT);
                    mvprintw(14, 41, "▒▒"); // TODO change to "▒▒" in prc
                    mvprintw(15, 39, "▒▒▒▒");
                    mvprintw(16, 41, "▒▒");
                    mvprintw(17, 33, "▒▒");
                    mvprintw(18, 31, "▒▒▒▒▒▒");
                    attron(COLOR_PAIR(4) | A_STANDOUT);
                    mvprintw(17,23,"▒▒▒▒");
                    mvprintw(18,23,"▒▒▒▒");
                    attroff(COLOR_PAIR(4) | A_STANDOUT);
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
        case 1: // 4 Moves slide
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
        case 2: // Play old moves slide
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
        case 3: // Clear moves slide
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