#ifndef MOVE_H
#define MOVE_H
#include "./piece.h"
#include "vector.h"
typedef enum{
    NORMAL_MOVEMENT,
    ATTACK_MOVEMENT
}movement_type_t;
typedef struct{
    vector_t to;
    vector_t from;
    piece_t moved_piece;
    piece_t captured_piece;
    movement_type_t type;
}movement_t;
void init_move(movement_t* move,vector_t* from,vector_t* to,piece_t moved_piece,piece_t captured_piece,movement_type_t type);
#endif