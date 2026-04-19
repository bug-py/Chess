#ifndef MOVE_H
#define MOVE_H
#include "./board.h"
#include "./piece.h"
#include "vector.h"
#include "structdata/dynamic_array.h"

array_t* generation_coup(chessboard_t board,vector_t* position);
#endif