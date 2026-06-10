#ifndef MOVE_H
#define MOVE_H
#include "./piece.h"
#include "vector.h"
typedef enum{
    UNDEFINED,
    NORMAL_MOVEMENT,
    ATTACK_MOVEMENT,

    PROMOTION_ATTACK_MOVEMENT,
    PROMOTION_MOVEMENT,

    LITTLE_ROQUE,
    BIG_ROQUE,

    IN_PASSING
    
}movement_type_t;
typedef struct{
    vector_t to;
    vector_t from;

    piece_t moved_piece;
    piece_t captured_piece;

    piece_t promotion;

    movement_type_t type;

}movement_t;
void init_move(movement_t* move,const vector_t* from,const vector_t* to,piece_t moved_piece,piece_t captured_piece,movement_type_t type);
#endif