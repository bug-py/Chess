#ifndef _BOARD_H
#define _BOARD_H
#include "./piece.h"
#include "vector.h"
typedef piece_t chessboard_t[8][8] ;
void init_board(chessboard_t board);
#endif