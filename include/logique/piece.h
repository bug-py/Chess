#ifndef _PIECE_H
#define _PIECE_H
#include <stdbool.h>

typedef enum{
    NO_COLOR,
    WHITE,
    BLACK
}piece_color_t;

typedef enum{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
}piece_type_t;

typedef struct{
    piece_color_t color;
    piece_type_t type;
    bool has_moved;
}piece_t;
void init_piece(piece_t* piece,piece_color_t color,piece_type_t type,bool has_moved);
void clear_piece(piece_t* piece);
#endif