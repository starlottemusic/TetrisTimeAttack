#include "../TetrisTimeAttack.h"

void dropPast(PastPiece piece) {
    openSpace = getOpenSpaces();

    PlayerPiece dropPiece = {piece.x, 0 + shouldOffset(piece.tetronimoIndex), piece.tetronimoIndex, piece.rotation};
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            dropPiece.tetronimo[i][j] = tetronimos[piece.tetronimoIndex][i][j] == ' ' ? ' ' : 'p';
        }
    }

    switch (piece.rotation) {
        case '0':
            break;
        case 'R':
            rotate(dropPiece.tetronimo, dropPiece.tetronimoIndex, true, true);
            dropPiece.y += 2;
            break;
        case '2':
            rotate(dropPiece.tetronimo, dropPiece.tetronimoIndex, true, true);
            rotate(dropPiece.tetronimo, dropPiece.tetronimoIndex, true, true);
            dropPiece.y += 2;
            break;
        case 'L':
            rotate(dropPiece.tetronimo, dropPiece.tetronimoIndex, false, true);
            dropPiece.y += 2;
            break;
        default:
            endwin();
            printf("ERROR: Past piece rotation OOB\n");
            exit(-1);
    }

    for (i = 0; i < 20; i++) {
        placePiece(dropPiece);
        if (getOpenSpaces() == openSpace - 4) {
            clearPiece(dropPiece);
            dropPiece.y++;
        }
    }
    clearPiece(dropPiece);
    dropPiece.y--;
    placePiece(dropPiece);
    settlePiece(&dropPiece, dropPiece.x, dropPiece.y, false, GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT, &gameBoard);
    redrawGame();
    usleep(100000);
}

PastPiece nextPast(byte fromIndex, bool shouldRemove) {
    PastPiece nextPiece;

    if (fromIndex >= past[taActiveChannel].pieceCount) {
        nextPiece.tetronimoIndex = -1;
        return nextPiece;
    }

    nextPiece = past[taActiveChannel].pieces[fromIndex];

    if (shouldRemove) {
        int i;
        for (i = fromIndex; i < past[taActiveChannel].pieceCount; i++) {
            past[taActiveChannel].pieces[i] = past[taActiveChannel].pieces[i + 1];
        }
        past[taActiveChannel].pieceCount--;
        past[taActiveChannel].pieces = realloc(past[taActiveChannel].pieces,
                                               sizeof(PastPiece) * (past[taActiveChannel].pieceCount + 1));
    }

    return nextPiece;
}

void extendPast() {
    past[taActiveChannel].pieces = realloc(past[taActiveChannel].pieces,
                                           sizeof(PastPiece) * (past[taActiveChannel].pieceCount + 1));

    past[taActiveChannel].pieces[past[taActiveChannel].pieceCount].tetronimoIndex = activePiece.tetronimoIndex;
    past[taActiveChannel].pieces[past[taActiveChannel].pieceCount].rotation = activePiece.rotation;
    past[taActiveChannel].pieces[past[taActiveChannel].pieceCount].x = activePiece.x;

    past[taActiveChannel].pieceCount++;
}

void erasePast() {
    byte channel = (taActiveChannel == 0) ? 3 : taActiveChannel - 1;
    byte count = past[taActiveChannel].pieceCount;
    byte i;

    if (count < 0) count = 0;

    for (i = 0; i < count - 1; i++) {
        past[channel].pieces[i].tetronimoIndex = past[channel].pieces[i + 1].tetronimoIndex;
        past[channel].pieces[i].rotation = past[channel].pieces[i + 1].rotation;
        past[channel].pieces[i].x = past[channel].pieces[i + 1].x;
    }

    past[channel].pieceCount--;

    past[channel].pieces = realloc(past[channel].pieces,
                                   sizeof(PastPiece) * (past[channel].pieceCount));
}

/**
 * Adjusts the pieces in the up next board to match the list
 */
void updatePastBoard() {
    int i, j, k;
    byte channel = (taActiveChannel == 3) ? 0 : taActiveChannel + 1;
    byte max = past[channel].pieceCount;

    if (max > 6) max = 6;

    for (i = 0; i < max; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                pastBoard[j + 3 * i + shouldOffset(past[channel].pieces[i].tetronimoIndex) + 1][k + 2] = tetronimos[past[channel].pieces[i].tetronimoIndex][j][k];
            }
        }
    }
}
