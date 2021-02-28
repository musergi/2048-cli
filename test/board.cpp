#include "gtest/gtest.h"

extern "C" {
    #include "board.h"
}

TEST(Board, Initialization) {
    Board board;
    boardInit(&board);
    int zero_count = 0;
    for (int i = 0; i < TILE_COUNT; i++) {
        if (board.tiles[i] == 0)
            zero_count++;
    }
    ASSERT_EQ(zero_count, TILE_COUNT - 2);
}

TEST(Board, SetAndGet) {
    Board board;
    boardSetTile(&board, 3, 2, 4);
    ASSERT_EQ(boardGetTile(&board, 3, 2), 4);
}

TEST(Board, AddRandom) {
    Board board;
    for (int i = 0; i < TILE_COUNT; i++) {
        board.tiles[i] = 0;
    }
    boardAddRandom(&board);
    int zero_count = 0;
    for (int i = 0; i < TILE_COUNT; i++) {
        if (board.tiles[i] == 0)
            zero_count++;
    }
    ASSERT_EQ(zero_count, TILE_COUNT - 1);
}

TEST(Board, MoveChecking) {
    Board non_up_board = {.tiles = {
        2, 4, 2, 2,
        0, 2, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_EQ(boardGetPossibleMoves(&non_up_board),
            DOWN_MOVE | LEFT_MOVE | RIGHT_MOVE);
}
