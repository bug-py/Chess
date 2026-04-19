#include "logique/piece.h"
void init_piece(piece_t* piece,piece_color_t color,piece_type_t type,bool has_moved){
    piece->color=color;
    piece->type=type;
    piece->has_moved=has_moved;
}
void clear_piece(piece_t* piece){
    init_piece(piece,NO_COLOR,EMPTY,false);
}
bool is_empty(piece_t* piece){
    return piece->color==NO_COLOR && piece->type==EMPTY;
}