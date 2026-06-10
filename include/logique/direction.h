#ifndef DIRECTION_H
#define DIRECTION_H
#include "vector.h"
#include <stddef.h>
#define SIZE_KNIGHT 8
#define SIZE_BISHOP 4
#define SIZE_ROOK 4
#define SIZE_QUEEN 8
#define SIZE_KING 8
typedef struct{
    vector_t start_king;
    vector_t start_rook;
    vector_t end_king;
    vector_t end_rook;

    vector_t empty_case[3];
    size_t count_empty_case;
    vector_t path_king[3];
    size_t count_path_king;
}roque_data_t;
extern const vector_t pawn[2][4];
extern const vector_t knight[SIZE_KNIGHT];
extern const vector_t bishop[SIZE_BISHOP];
extern const vector_t rook[SIZE_ROOK];
extern const vector_t queen[SIZE_QUEEN];
extern const vector_t king[SIZE_KING];
extern const roque_data_t white_big_roque;
extern const roque_data_t white_little_roque;
extern const roque_data_t black_big_roque;
extern const roque_data_t black_little_roque;
#endif