#include "../TetrisTimeAttack.h"

int slide = 3, frame;

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

    switch (slide) {
        case 0:
            mvprintw(20, 7, "Complete lines to clear the board and score points.");
            switch (frame) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
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
