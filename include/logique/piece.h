#ifndef _PIECE_H
#define _PIECE_H
#include <stdbool.h>
#include <stdint.h>
#define NULL_PIECE 0
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

typedef uint8_t piece_t;
piece_t init_piece(piece_type_t type,piece_color_t color);
piece_type_t get_type(piece_t piece);
piece_color_t get_color(piece_t piece);
bool is_empty(const piece_t piece);
#endif