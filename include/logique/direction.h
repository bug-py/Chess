#ifndef DIRECTION_H
#define DIRECTION_H
#include "vector.h"
#define SIZE_KNIGHT 8
#define SIZE_BISHOP 4
#define SIZE_ROOK 4
#define SIZE_QUEEN 8
#define SIZE_KING 8
extern const vector_t pawn[2][4];
extern const vector_t knight[SIZE_KNIGHT];
extern const vector_t bishop[SIZE_BISHOP];
extern const vector_t rook[SIZE_ROOK];
extern const vector_t queen[SIZE_QUEEN];
extern const vector_t king[SIZE_KING];
#endif