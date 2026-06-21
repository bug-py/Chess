#include "logique/move.h"
#include <string.h>

void init_move(movement_t* move,const vector_t* from,const vector_t* to,piece_t moved_piece,piece_t captured_piece,piece_t promotion,uint8_t flag){
        memcpy(&(move->from),from,sizeof(vector_t));
        memcpy(&(move->to),to,sizeof(vector_t));
        move->moved_piece=moved_piece;
        move->captured_piece=captured_piece;
        move->promotion=promotion;
        move->flag=flag;
}