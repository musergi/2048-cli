#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"

void boardInit(Board *board) {
    Index row, column;
    srand(time(NULL));
    for (row = 0; row < ROW_COUNT; row++) {
        for (column = 0; column < COL_COUNT; column++) {
            boardSetTile(board, row, column, 0);
        }
    }
    boardAddRandom(board);
    boardAddRandom(board);
}

void boardAddRandom(Board *board) {
    Index row, column;
    unsigned int empty_count = 0, position;
    
    /* Get the number of empty tiles */
    for (row = 0; row < ROW_COUNT; row++) {
        for (column = 0; column < COL_COUNT; column++) {
            if (boardGetTile(board, row, column) == 0)
                empty_count++;
        }
    }

    /* Choose tile index base on empty tile position */
    position = rand() % empty_count;

    /* Place on selected empty tile */
    /* TODO: Convert to while to save iterations */
    empty_count = 0;
    for (row = 0; row < ROW_COUNT; row++) {
        for (column = 0; column < COL_COUNT; column++) {
            if (boardGetTile(board, row, column) == 0) {
                if (empty_count == position)
                    boardSetTile(board, row, column, 2);
                empty_count++;
            }
        }
    }
}

void boardShow(Board *board) {
    Index row, column;
    printf("+----+----+----+----+\n");
    for (row = 0; row < ROW_COUNT; row++) {
        printf("|    |    |    |    |\n");
        for (column = 0; column < COL_COUNT; column++) {
            printf("|%4d", boardGetTile(board, row, column));
        }
        printf("|\n|    |    |    |    |\n");
        printf("+----+----+----+----+\n");
    }
}

int boardGetPossibleMoves(Board *board) {
    int move = 0;
    Index row, column;
    Index last_non_zero;
    bool has_empty_tile;
    /* Up move */
    for (column = 0; column < COL_COUNT; column++) {
        last_non_zero = 0;
        has_empty_tile = false;
        for (row = 0; row < ROW_COUNT; row++) {
            Tile value = boardGetTile(board, row, column);
            if (value == 0) {
                has_empty_tile = true;
            } else {
                if (has_empty_tile) {
                    move |= UP_MOVE;
                }
                if (row != 0) {
                    if (value == boardGetTile(board, last_non_zero, column)) {
                        move |= UP_MOVE;
                    }
                    last_non_zero = row;
                }
            }
        }
    }
    /* Down move */
    for (column = 0; column < COL_COUNT; column++) {
        last_non_zero = ROW_COUNT - 1;
        has_empty_tile = false;
        for (row = ROW_COUNT - 1; row >= 0; row--) {
            Tile value = boardGetTile(board, row, column);
            if (value == 0) {
                has_empty_tile = true;
            } else {
                if (has_empty_tile) {
                    move |= DOWN_MOVE;
                }
                if (row != ROW_COUNT - 1) {
                    if (value == boardGetTile(board, last_non_zero, column)) {
                        move |= DOWN_MOVE;
                    }
                    last_non_zero = row;
                }
            }
        }
    }
    /* Left move */
    for (row = 0; row < ROW_COUNT; row++) {
        last_non_zero = 0;
        has_empty_tile = false;
        for (column = 0; column < COL_COUNT; column++) {
            Tile value = boardGetTile(board, row, column);
            if (value == 0) {
                has_empty_tile = true;
            } else {
                if (has_empty_tile) {
                    move |= LEFT_MOVE;
                }
                if (column != 0) {
                    if (value == boardGetTile(board, row, last_non_zero)) {
                        move |= LEFT_MOVE;
                    }
                    last_non_zero = column;
                }
            }
        }
    }
    /* Right move */
    for (row = 0; row < ROW_COUNT; row++) {
        last_non_zero = COL_COUNT - 1;
        has_empty_tile = false;
        for (column = COL_COUNT - 1; column >= 0; column--) {
            Tile value = boardGetTile(board, row, column);
            if (value == 0) {
                has_empty_tile = true;
            } else {
                if (has_empty_tile) {
                    move |= RIGHT_MOVE;
                }
                if (column != COL_COUNT - 1) {
                    if (value == boardGetTile(board, row, last_non_zero)) {
                        move |= RIGHT_MOVE;
                    }
                    last_non_zero = column;
                }
            }
        }
    }
    return move;
}

void boardApplyMove(Board *board, int move) {
    Index row, column;
    Index insert_index;
    if (move & UP_MOVE) {
        for (column = 0; column < COL_COUNT; column++) {
            insert_index = 0;
            for (row = 1; row < ROW_COUNT; row++) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    if (value == boardGetTile(board, insert_index, column)) {
                        boardSetTile(board, insert_index, column, value * 2);
                        boardSetTile(board, row, column, 0);
                    }
                    insert_index = row;
                }
            }
            insert_index = 0;
            for (row = 0; row < ROW_COUNT; row++) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    boardSetTile(board, row, column, 0);
                    /* Delete first in case the row and insert_index are equal */
                    boardSetTile(board, insert_index, column, value);
                    insert_index++;
                }
            }
        }
    } else if (move & DOWN_MOVE) {
        for (column = 0; column < COL_COUNT; column++) {
            insert_index = 3;
            for (row = ROW_COUNT - 2; row >= 0; row--) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    if (value == boardGetTile(board, insert_index, column)) {
                        boardSetTile(board, insert_index, column, value * 2);
                        boardSetTile(board, row, column, 0);
                    }
                    insert_index = row;
                }
            }
            insert_index = 3;
            for (row = ROW_COUNT - 1; row >= 0; row--) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    boardSetTile(board, row, column, 0);
                    /* Delete first in case the row and insert_index are equal */
                    boardSetTile(board, insert_index, column, value);
                    insert_index--;
                }
            }
        }
    } else if (move & LEFT_MOVE) {
        for (row = 0; row < ROW_COUNT; row++) {
            insert_index = 0;
            for (column = 1; column < COL_COUNT; column++) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    if (value == boardGetTile(board, row, insert_index)) {
                        boardSetTile(board, row, insert_index, value * 2);
                        boardSetTile(board, row, column, 0);
                    }
                    insert_index = column;
                }
            }
            insert_index = 0;
            for (column = 0; column < COL_COUNT; column++) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    boardSetTile(board, row, column, 0);
                    /* Delete first in case the row and insert_index are equal */
                    boardSetTile(board, row, insert_index, value);
                    insert_index++;
                }
            }
        }
    } else if (move & RIGHT_MOVE) {
        for (row = 0; row < ROW_COUNT; row++) {
            insert_index = 3;
            for (column = COL_COUNT - 2; column >= 0; column--) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    if (value == boardGetTile(board, row, insert_index)) {
                        boardSetTile(board, row, insert_index, value * 2);
                        boardSetTile(board, row, column, 0);
                    }
                    insert_index = column;
                }
            }
            insert_index = 3;
            for (column = COL_COUNT - 1; column >= 0; column--) {
                Tile value = boardGetTile(board, row, column);
                if (value != 0) {
                    boardSetTile(board, row, column, 0);
                    /* Delete first in case the row and insert_index are equal */
                    boardSetTile(board, row, insert_index, value);
                    insert_index--;
                }
            }
        }
    }
    boardAddRandom(board);
}

void displayOptions(int options) {
    printf("Possible moves:\n");
    if (options & UP_MOVE) printf("\t[u] go up\n");
    if (options & DOWN_MOVE) printf("\t[d] go down\n");
    if (options & LEFT_MOVE) printf("\t[l] go left\n");
    if (options & RIGHT_MOVE) printf("\t[r] go right\n");
}

int getMove(int options) {
    int move;
    char inChar;
    do {
        printf("Enter your move: ");
        scanf("%c%*c", &inChar);
        switch (inChar) {
            case 'u': move = UP_MOVE; break;
            case 'd': move = DOWN_MOVE; break;
            case 'l': move = LEFT_MOVE; break;
            case 'r': move = RIGHT_MOVE; break;
            default: move = 0;
        }
        if (move & options == 0)
            printf("Invalid move.");
    } while (move & options == 0);
    return move;
}

void boardSetTile(Board *board, Index row, Index column, Tile value) {
    board->tiles[row * COL_COUNT + column] = value;
}

Tile boardGetTile(Board *board, Index row, Index column) {
    return board->tiles[row * COL_COUNT + column];
}
