#include "../TetrisTimeAttack.h"

void mainLeaderboard() {
    startNCursesScreen();
    clear();

    bool shouldRedraw = true;
    int page = 0;
    int maxPage;
    char buffer[16];
    Leaderboard *leaderboard = NULL;

    FILE *leaderboardFile = openLeaderboard("r");
    int entries = 0;
    while (fgets(buffer, 16, leaderboardFile) != NULL) {
        leaderboard = (Leaderboard *) realloc(leaderboard, sizeof(Leaderboard) * (entries + 1));
        decryptText(buffer);
        strncpy(leaderboard[entries].name, buffer, 3);
        leaderboard[entries].name[3] = '\0';
        strncpy(buffer, "     ", 5);
        leaderboard[entries].score = atoi(buffer);
        entries++;
    }
    fclose(leaderboardFile);

    if (leaderboard == NULL) {
        screenState = 'M';
        free(leaderboard);
        return;
    }

    int i, j;
    for (i = 0; i < entries; i++) {
        int highScore = -INT_MAX;
        int highScoreIndex = -1;

        for (j = i; j < entries; j++) {
            if (leaderboard[j].score > highScore) {
                highScore = leaderboard[j].score;
                highScoreIndex = j;
            }
        }

        if (highScoreIndex == i) continue;

        strcpy(buffer, leaderboard[i].name);
        strcpy(leaderboard[i].name, leaderboard[highScoreIndex].name);
        strcpy(leaderboard[highScoreIndex].name, buffer);

        leaderboard[i].score = leaderboard[highScoreIndex].score ^ leaderboard[i].score;
        leaderboard[highScoreIndex].score = leaderboard[i].score ^ leaderboard[highScoreIndex].score;
        leaderboard[i].score = leaderboard[highScoreIndex].score ^ leaderboard[i].score;
    }

    refresh();

    maxPage = ((int) (entries / 20));

    while (screenState == 'L') {
        if (shouldRedraw) {
            redrawLeaderboard(leaderboard, page, entries);
            shouldRedraw = false;
        }

        inputListener();
        switch (lastInput) {
            case KEY_LEFT:
                if (page > 0) {
                    page--;
                    shouldRedraw = true;
                }
                break;
            case KEY_RIGHT:
                if (page < maxPage) {
                    page++;
                    shouldRedraw = true;
                }
                break;
            case KEY_ENTER:
            case ' ':
            case '\n':
                screenState = 'M';
                break;
            default:
                break;
        }
        lastInput = ERR;
    }

    free(leaderboard);
    endwin();
}

void redrawLeaderboard(Leaderboard *leaderboard, int page, int length) {
    clear();
    int max = length - 20 * page;
    int i;

    if (max > 20)
        max = 20;

    for (i = 0; i < max; i++) {
        mvprintw(i, 0, "%s - %d", leaderboard[i + 20 * page].name, leaderboard[i + 20 * page].score);
    }
    refresh();
}
