#include "../TetrisTimeAttack.h"

void runAnim() {
    int frame, slide=0;

    // increase frame every second (delta time?)

    // create back and next buttons
        // increase slide when user presses next
        // decrease slide when user presses back
        // replace back with exit on slide 0 and next with exit on slide 3

    while (slide>=0 && slide<=4) {
        switch (slide) {
            case 0:
                mvprintw(67,67,"Complete lines to clear the board and score points.");
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
    }
}