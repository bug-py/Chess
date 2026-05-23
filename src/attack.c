#include "logique/attack.h"
#include "logique/direction.h"
#include <stddef.h>
bool check_ray_movement(chessboard_t board,vector_t* position,piece_t enemy,const vector_t* vector,size_t size){ 
    for(size_t i=0;i<size;i++){
        vector_t to=*position;
        while(true){
            vector_add(&to,&(vector[i]),&to);
            piece_t* piece=get_piece(board,&to);
            if(!piece) break;
            if((*piece)==enemy) return true;
            if(!is_empty(*piece)) break;
        }
    }
    return false;
}
bool check_step_movement(chessboard_t board,vector_t* position,piece_t enemy,const vector_t* vector,size_t size){
    vector_t to;
    for(size_t i=0;i<size;i++){
        vector_add(position,&(vector[i]),&to);
        piece_t* piece=get_piece(board,&to);
        if(!piece) continue;
        if((*piece)==enemy) return true;
    }
    return false;
}
bool check_PAWN(chessboard_t board,vector_t* position,piece_color_t color_enemy){
    int color=(color_enemy==WHITE)? 1 : 0;
    piece_t enemy=init_piece(PAWN,color_enemy);
    vector_t to;
    for(int i=2;i<4;i++){
        vector_add(position,&(pawn[color][i]),&to);
        piece_t* piece=get_piece(board,&to);
        if(!piece) continue;
        if((*piece)==enemy) return true;
    }
    return false;

}


int is_attack(chessboard_t board,vector_t* position,piece_color_t color_enemy){
    if(!is_inside(position)) return -1;
    if(
        check_PAWN(board,position,color_enemy) ||
        check_step_movement(board,position,init_piece(KNIGHT,color_enemy),knight,SIZE_KNIGHT) ||
        check_ray_movement(board,position,init_piece(BISHOP,color_enemy),bishop,SIZE_BISHOP) ||
        check_ray_movement(board,position,init_piece(ROOK,color_enemy),rook,SIZE_ROOK) ||
        check_ray_movement(board,position,init_piece(QUEEN,color_enemy),queen,SIZE_QUEEN) ||
        check_step_movement(board,position,init_piece(KING,color_enemy),king,SIZE_KING)
    ) return 1;
    return 0;
}

int search_king(chessboard_t board,piece_color_t color,vector_t* position){
    piece_t target=init_piece(KING,color);
    vector_t element;
    for(int y=0;y<8;y++){
        for(int x=0;x<8;x++){
            vector_set(&element,x,y);
            piece_t* piece=get_piece(board,&element);
            if(piece && (*piece)==target) {
                *position=element;
                return 0;
            }
        }
    }
    return -1;
}

int is_echec(chessboard_t board,piece_color_t color_enemy){
    vector_t position;
    piece_color_t color_king;
    switch(color_enemy){
        case NO_COLOR: return -1;
        case BLACK : color_king=WHITE; break;
        case WHITE : color_king=BLACK; break;
    }
    if(search_king(board,color_king,&position)<0) return -1;
    return is_attack(board,&position,color_enemy);
}