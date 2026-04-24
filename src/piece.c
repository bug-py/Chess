#include "logique/piece.h"
typedef enum{
    MASK_PAWN=1<<0,
    MASK_KNIGHT=1<<1,
    MASK_BISHOP=1<<2,
    MASK_ROOK=1<<3,
    MASK_QUEEN=1<<4,
    MASK_KING=1<<5,

    MASK_BLACK=1<<6
}piece_bitmask_t;
piece_t init_piece(piece_type_t type,piece_color_t color){
    piece_t piece;
    switch(type){
        case EMPTY: return NULL_PIECE;
        case PAWN:  piece=MASK_PAWN; break;
        case KNIGHT: piece=MASK_KNIGHT; break;
        case BISHOP: piece=MASK_BISHOP; break;
        case ROOK: piece=MASK_ROOK; break;
        case QUEEN: piece=MASK_QUEEN; break;
        case KING: piece=MASK_KING;  break;
    }
    if(color==BLACK) piece|=MASK_BLACK;
    return piece;
}
piece_type_t get_type(piece_t piece){
    if(!piece) return EMPTY;
    switch(piece&(~MASK_BLACK)){
        case MASK_PAWN : return PAWN;
        case MASK_KNIGHT : return KNIGHT;
        case MASK_BISHOP : return BISHOP;
        case MASK_ROOK : return ROOK;
        case MASK_QUEEN : return QUEEN;
        case MASK_KING : return KING;
    }
}
piece_color_t get_color(piece_t piece){
    if(!piece) return NO_COLOR;
    return (piece&(MASK_BLACK))? BLACK : WHITE;
}
bool is_empty(const piece_t piece){
    return !piece;
}

