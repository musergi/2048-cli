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
    ASSERT_FALSE(boardGetPossibleMoves(&non_up_board) & UP_MOVE);
    Board can_fall_up_board = {.tiles = {
        2, 0, 2, 2,
        0, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_fall_up_board) & UP_MOVE);
    Board can_combine_up_board = {.tiles = {
        2, 4, 2, 2,
        0, 4, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_combine_up_board) & UP_MOVE);
    Board non_right_board = {.tiles = {
        0, 0, 0, 2,
        0, 0, 0, 0,
        0, 0, 0, 2,
        0, 0, 0, 0
    }};
    ASSERT_FALSE(boardGetPossibleMoves(&non_right_board) & RIGHT_MOVE);
    Board can_fall_right_board = {.tiles = {
        0, 0, 2, 0,
        0, 0, 0, 2,
        0, 0, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_fall_right_board) & RIGHT_MOVE);
    Board can_combine_right = {.tiles = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 8, 8, 2,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_combine_right) & RIGHT_MOVE);
    Board non_left_board = {.tiles = {
        8, 2, 0, 0,
        4, 8, 2, 0,
        8, 4, 2, 0,
        8, 0, 0, 0
    }};
    ASSERT_FALSE(boardGetPossibleMoves(&non_left_board) & LEFT_MOVE);
    Board can_fall_left_board = {.tiles = {
        0, 0, 0, 2,
        2, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_fall_left_board) & LEFT_MOVE);
    Board can_combine_left_board = {.tiles = {
        0, 0, 0, 0,
        2, 2, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_combine_left_board) & LEFT_MOVE);
    Board non_down_board = {.tiles = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 2, 0, 2
    }};
    ASSERT_FALSE(boardGetPossibleMoves(&non_down_board) & DOWN_MOVE);
    Board can_fall_down_board = {.tiles = {
        0, 0, 2, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 2, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_fall_down_board) & DOWN_MOVE);
    Board can_combine_down_board = {.tiles = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        2, 0, 0, 0,
        2, 0, 0, 0
    }};
    ASSERT_TRUE(boardGetPossibleMoves(&can_combine_down_board) & DOWN_MOVE);
    Board no_move_board = {.tiles = {
         2,  4,  8, 16,
         4,  8, 16,  2,
         8, 16,  2,  4,
        16,  2,  4,  8
    }};
    ASSERT_EQ(boardGetPossibleMoves(&no_move_board), 0);
}
