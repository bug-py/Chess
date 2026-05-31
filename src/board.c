#include "logique/board.h"
#include <stddef.h>
void init_board(chessboard_t board){
    piece_type_t mapping[8]={
        ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK
    };
    for(int i=0;i<8;i++){
        board[0][i]=init_piece(mapping[i],BLACK);
        board[1][i]=init_piece(PAWN,BLACK);
       
        board[7][i]=init_piece(mapping[i],WHITE);
        board[6][i]=init_piece(PAWN,WHITE);

    }
    for(int row=2;row<6;row++){
        for(int column=0;column<8;column++){
           board[row][column]=NULL_PIECE;
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
void move_piece(piece_t* from,piece_t* to,piece_t init){
    *to=*from;
    *from=init;
}
