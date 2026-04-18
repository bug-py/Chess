#include "logique/board.h"
void init_board(chessboard_t board){
    piece_type_t mapping[8]={
        ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK
    };
    for(int i=0;i<8;i++){
        board[0][i].has_moved=false;
        board[0][i].color=BLACK;
        board[0][i].type=mapping[i];

        board[1][i].has_moved=false;
        board[1][i].color=BLACK;
        board[1][i].type=PAWN;


        board[7][i].has_moved=false;
        board[7][i].color=WHITE;
        board[7][i].type=mapping[i];

        board[6][i].has_moved=false;
        board[6][i].color=WHITE;
        board[6][i].type=PAWN;

    }
    for(int row=2;row<6;row++){
        for(int collum=0;collum<8;collum++){
            board[row][collum].type=EMPTY;
        }
    }
    
}