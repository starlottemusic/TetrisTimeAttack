#include "TetrisTimeAttack.h"

#include "Initialize.c"
#include "Render.c"
#include "FileManager.c"
#include "MovementHandler.c"
#include "PieceManager.c"

/**
 * Called once per delta time, used for any time-dependent game functionality (ie. handling piece movement)
 */
void tick() {
}

int main() {
	initscr(); // start ncurses
  noecho(); // don't write keyboard input to screen
  cbreak(); // allow input w/o needing to press enter (CTRL+C still passes)
  curs_set(0); // hide cursor
  keypad(stdscr, TRUE); // set keypad mode to true (allow arrow keys to give inputs)
  timeout(0); // make user input timeout immediately

  initGlobals();
  initPalette();

  int lastIn, temp;
  clock_t tickCounter = clock();
  long i = 0;

  newTurnPlayerPiece(0);

  placePiece(activePiece);
  redrawScreen();

  while (1) {
    if ((temp = getch()) != ERR) {
      lastIn = temp;
    }

    if ((float) tickCounter / CLOCKS_PER_SEC <  (float) clock() / CLOCKS_PER_SEC - DELTA_TIME) {
      tickCounter = clock();
      i++;
      tick();

      if (i < -1) {
        endwin();
        printf("You have been playing for 414 days consecutively. Frankly, this crash is for your own good.\n");
        exit(-1);
      }
    }

    switch (lastIn) {
      case KEY_LEFT:
        attemptMovement(KEY_LEFT);
        lastIn = ERR;
        usleep(10000);
        break;
      case KEY_RIGHT:
        attemptMovement(KEY_RIGHT);
        lastIn = ERR;
        usleep(10000);
        break;
      case KEY_UP:
        attemptMovement(KEY_UP);
        lastIn = ERR;
        usleep(10000);
        break;
      case KEY_DOWN:
        attemptMovement(KEY_DOWN);
        lastIn = ERR;
        usleep(10000);
        break;
      case 'd': case 'D':
        clearPiece(activePiece);
        rotate(activePiece.tetronimo, activePiece.tetronimoIndex, true);
        placePiece(activePiece);
        redrawScreen();
        lastIn = ERR;
        usleep(10000);
        break;
      case 'a': case 'A':
        clearPiece(activePiece);
        rotate(activePiece.tetronimo, activePiece.tetronimoIndex, false);
        placePiece(activePiece);
        redrawScreen();
        lastIn = ERR;
        usleep(10000);
        break;
      case ' ':
        clearPiece(activePiece);
        newTurnPlayerPiece(activePiece.tetronimoIndex >= 6 ? activePiece.tetronimoIndex - 6 : activePiece.tetronimoIndex + 1);
        redrawScreen();
        lastIn = ERR;
        usleep(10000);
        break;
    }
  }
}