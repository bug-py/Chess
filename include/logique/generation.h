#ifndef GENERATION_H
#define GENERATION_H
#include "./move.h"
#include "./board.h"
#include "./piece.h"
#include "./special_move_state.h"
#include "vector.h"
#include "structdata/dynamic_array.h"
array_t* brut_generation(chessboard_t board,vector_t* position,special_move_state_t* state,bool promotion);
#endif