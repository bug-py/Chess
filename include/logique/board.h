#ifndef _BOARD_H
#define _BOARD_H
#include "./move.h"
#include "./piece.h"
#include "vector.h"
typedef piece_t chessboard_t[8][8];

void init_board(chessboard_t board);
bool is_inside(vector_t* position);
piece_t* get_piece(chessboard_t board,vector_t* position);
int apply_move(chessboard_t board,movement_t* move);
int undo_move(chessboard_t board,movement_t* move);

#endif