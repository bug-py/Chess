#include <stdio.h>
#include "logique/board.h"

int main(){
    chessboard_t board;
    printf("%lu\n",sizeof(board));
    init_board(board);
    vector_t position={.x=3,.y=1};
    piece_t* piece=GetPiece(board,&position);
    if(!piece){
        printf("Limit");
        return 1;
    }
    printf("%i %i %i\n",piece->color,piece->type,piece->has_moved);
    vector_t end={.x=3,.y=2};
    if(MovePiece(board,&position,&end)<0){
        printf("Limit");
        return -1;
    }
    piece=GetPiece(board,&end);
    if(!piece){
        printf("Limit");
        return 1;
    }
    printf("%i %i %i\n",piece->color,piece->type,piece->has_moved);
    return 0;
}