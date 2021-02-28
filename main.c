#include "board.h"

#define STATE_PLAYING 0
#define STATE_WIN 1
#define STATE_LOSE 2

int main() {
    int options, move;
    int state = STATE_PLAYING;
    Board board;
    boardInit(&board);
    while (state == STATE_PLAYING) {
        boardShow(&board);
        options = boardGetPossibleMoves(&board);
        if (options == 0) {
            state = STATE_LOSE;
        } else {
            displayOptions(options);
            move = getMove(options);
            boardApplyMove(&board, move);
        }
    }
}
