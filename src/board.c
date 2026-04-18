#include "logique/board.h"
#include "stddef.h"



void init_board(chessboard_t board){
    piece_type_t mapping[8]={
        ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK
    };
    for(int i=0;i<8;i++){
        init_piece(&(board[0][i]),BLACK,mapping[i],false);
        init_piece(&(board[1][i]),BLACK,PAWN,false);
       
        init_piece(&(board[7][i]),WHITE,mapping[i],false);
        init_piece(&(board[6][i]),WHITE,PAWN,false);

    }
    for(int row=2;row<6;row++){
        for(int column=0;column<8;column++){
           clear_piece(&(board[row][column]));
        }
    }
    
}
bool is_inside(vector_t* position){
    if(position->x<0 || position->y<0 || position->x>7 || position->y>7){
        return false;
    }
    return true;
}
piece_t* get_piece(chessboard_t board,vector_t* position){
    if(!is_inside(position)) return NULL;
    return (&board[position->y][position->x]);
}

piece_t* move_piece(chessboard_t board,vector_t* old,vector_t* new){
    if(!is_inside(old) || !is_inside(new)) return NULL;
    piece_t* begin=&(board[old->y][old->x]);
    piece_t* end=&(board[new->y][new->x]);
    *end=*begin;
    clear_piece(begin);
    end->has_moved=true;
    return begin;
}