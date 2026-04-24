#include "logique/move.h"
#include <string.h>

void init_move(movement_t* move,vector_t* from,vector_t* to,piece_t moved_piece,piece_t captured_piece,movement_type_t type){
        memcpy(&(move->from),from,sizeof(vector_t));
        memcpy(&(move->to),to,sizeof(vector_t));
        move->moved_piece=moved_piece;
        move->captured_piece=captured_piece;
        move->type=type;
}