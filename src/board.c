#include "logique/board.h"
#include "stddef.h"

bool is_inside(vector_t* position){
    if(position->x<0 || position->y<0 || position->x>7 || position->y>7){
        return false;
    }
    return true;
}
void InitPiece(piece_t* piece,piece_color_t color,piece_type_t type,bool has_moved){
    piece->color=color;
    piece->type=type;
    piece->has_moved=has_moved;
}
void ClearPiece(piece_t* piece){
    InitPiece(piece,NO_COLOR,EMPTY,false);
}

void init_board(chessboard_t board){
    piece_type_t mapping[8]={
        ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK
    };
    for(int i=0;i<8;i++){
        InitPiece(&(board[0][i]),BLACK,mapping[i],false);
        InitPiece(&(board[1][i]),BLACK,PAWN,false);
       
        InitPiece(&(board[7][i]),WHITE,mapping[i],false);
        InitPiece(&(board[6][i]),WHITE,PAWN,false);

    }
    for(int row=2;row<6;row++){
        for(int column=0;column<8;column++){
           ClearPiece(&(board[row][column]));
        }
    }
    
}

piece_t* GetPiece(chessboard_t board,vector_t* position){
    if(!is_inside(position)) return NULL;
    return (&board[position->y][position->x]);
}
int MovePiece(chessboard_t board,vector_t* old,vector_t* new){
    if(!is_inside(old) || !is_inside(new)) return -1;
    piece_t* begin=&(board[old->y][old->x]);
    piece_t* end=&(board[new->y][new->x]);
    *end=*begin;
    ClearPiece(begin);
    end->has_moved=true;
    return 0;
}