#ifndef _BOARD_H
#define _BOARD_H
#include "./piece.h"
#include "vector.h"
typedef piece_t chessboard_t[8][8];

void init_board(chessboard_t board);
bool is_inside(vector_t* position);
piece_t* get_piece(chessboard_t board,vector_t* position);
void move_piece(piece_t* from,piece_t* to,piece_t init);

#endif