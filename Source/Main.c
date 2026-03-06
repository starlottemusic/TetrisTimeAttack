#include "TetrisTimeAttack.h"

#include "Initialize.c"
#include "Render.c"
#include "FileManager.c"

short int pieceSize(char type) {
  if (type == 'O' || type == 'I') return 4;
  else return 3;
}

void rotate(char test[4][4], char type, bool clockwise) {
  short int size = pieceSize(type);
  char temp[4][4];
  short int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      temp[i][j] = clockwise ? test[j][(size - 1) - i] : test[(size - 1) - j][i];
    }
  }

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      test[i][j] = temp[i][j];
    }
  }
}

int main(int argc, char *argv[]) {
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
  int x = 0, y = 0;
        redrawScreen(x, y);
  while (1) {
    if ((temp = getch()) != ERR) {
      lastIn = temp;
    }

    switch (lastIn) {
      case KEY_LEFT:
        x -= 1;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_RIGHT:
        x += 1;
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_UP:
        rotate(tetronimo, 'L', true);
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
      case KEY_DOWN:
        rotate(tetronimo, 'L', false);
        lastIn = ERR;
        redrawScreen(x, y);
        usleep(10000);
        break;
    }
  }
}