#ifndef GENERATION_H
#define GENERATION_H
#include "./move.h"
#include "./board.h"
#include "./piece.h"
#include "vector.h"
#include "structdata/dynamic_array.h"
array_t* generation(chessboard_t board,vector_t* position);
#endif