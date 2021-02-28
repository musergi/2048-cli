#ifndef __BOARD_H__
#define __BOARD_H__

#define TILE_COUNT 16
#define ROW_COUNT 4
#define COL_COUNT 4

#define UP_MOVE     0b0001
#define DOWN_MOVE   0b0010
#define LEFT_MOVE   0b0100
#define RIGHT_MOVE  0b1000

typedef int Tile;
typedef int Index;

typedef struct {
    Tile tiles[TILE_COUNT];
} Board;

void boardInit(Board *board);
void boardShow(Board *board);
void boardSetTile(Board *board, Index row, Index column, Tile value);
Tile boardGetTile(Board *board, Index row, Index column);
void boardAddRandom(Board *board);

int boardGetPossibleMoves(Board *board);
void boardApplyMove(Board *board, int move);
void boardCombineColumn(Board *board, int column);

void displayOptions(int options);
int getMove(int options);

#endif
