#ifndef _PIECE_H
#define _PIECE_H
#include <stdbool.h>

typedef enum{
    NO_COLOR=0,
    BLACK=1,
    WHITE=2
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
bool is_empty(piece_t* piece);
#endif