#ifndef MOVE_H
#define MOVE_H
#include "./piece.h"
#include "vector.h"
typedef enum{
    NORMAL_MOVEMENT=0,
    ATTACK_MOVEMENT=1<<0,
    LITTLE_ROQUE=1<<1,
    BIG_ROQUE=1<<2,
    PROMOTION_MOVEMENT=1<<3,
    IN_PASSING=1<<4
}movement_type_t;
typedef struct{
    vector_t to;
    vector_t from;

    piece_t moved_piece;
    piece_t captured_piece;

    piece_t promotion;

    uint8_t flag;

}movement_t;
void init_move(movement_t* move,const vector_t* from,const vector_t* to,piece_t moved_piece,piece_t captured_piece,piece_t promotion,uint8_t flag);
#endif