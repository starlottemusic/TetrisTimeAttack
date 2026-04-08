#include "TetrisTimeAttack.h"

#include "Util/Init.c"
#include "Util/Render.c"
#include "Util/FileManager.c"
#include "Game/MovementHandler.c"
#include "Game/PieceManager.c"
#include "Util/InputHandler.c"
#include "Util/Util.c"
#include "Game/MainGame.c"
#include "Menu/MainMenu.c"
#include "Controls/MainControls.c"
#include "Game/ScoreWindow.c"
#include "Leaderboard/MainLeaderboard.c"
#include "Tutorial/Tutorial.c"

int main() {
    loadConfig();
    mainMenu();
}