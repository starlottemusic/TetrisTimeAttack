#include "TetrisTimeAttack.h"

#include "Initialize.c"
#include "Render.c"
#include "FileManager.c"
#include "MovementHandler.c"

/**
 * Returns the size of a piece from the Tetronimos array
 * @param index The index of the piece in the array
 * @return The size of the piece
 */
short int pieceSize(short int index) {
  if (index ==  0 || index ==  3) return 4; // I & O pieces
  return 3; // other pieces
}

/**
 * Rotates a piece clockwise or counterclockwise
 * @param piece The array of the piece to be rotated
 * @param index The index of the piece from the Tetronimos global array
 * @param clockwise If true, rotate CW. If false, rotate CCW
 */
void rotate(char piece[4][4], short int index, bool clockwise) {
  short int size = pieceSize(index);
  char temp[4][4];
  short int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      temp[i][j] = clockwise ? piece[j][(size - 1) - i] : piece[(size - 1) - j][i];
    }
  }

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      piece[i][j] = temp[i][j];
    }
  }
}

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
  redrawScreen(0, 0);

  int lastIn, temp;
  clock_t tickCounter = clock();
  int x = 0, y = -1;
  long i = 0;
        redrawScreen(x, y);

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
        printf("You have been playing for 414 days consecutively. Frankly, this is for your own good.\n");
        exit(-1);
      }
    }

    switch (lastIn) {
      case KEY_LEFT:
        x -= 2;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_RIGHT:
        x += 2;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_UP:
        y -= 1;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_DOWN:
        y += 1;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case 'a': case 'A':
        rotate(tetronimos[currentPiece], currentPiece, false);
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case 'd': case 'D':
        rotate(tetronimos[currentPiece], currentPiece, true);
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case ' ':
        currentPiece = currentPiece >= 6 ? currentPiece - 6 : currentPiece + 1;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
    }
  }
}