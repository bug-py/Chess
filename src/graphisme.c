#include "graphisme.h"
char GetCharColor(piece_t piece){
    switch(get_color(piece)){
        case NO_COLOR : return ' ';
        case BLACK : return 'B';
        case WHITE : return 'W';
    }
}
char GetCharType(piece_t piece){
    switch(get_type(piece)){
        case EMPTY : return ' ';
        case PAWN : return 'P';
        case KNIGHT : return 'K';
        case BISHOP : return 'B';
        case ROOK: return 'R';
        case QUEEN : return 'Q';
        case KING : return '@';
    }
}
void ShownCase(piece_t piece){
    printf("[ %c %c ]  ",GetCharColor(piece),GetCharType(piece));
}

void ShownLettre(chessboard_t board,bool reverse){
    char map[8]={'A','B','C','D','E','F','G','H'};
    printf("    ");
    for(int i=0;i<8;i++){
        printf("   %c     ",map[(reverse ? 7-i : i )]);
    }
    printf("\n");
}
void ShownBoard(chessboard_t board,bool reverse){
    vector_t position;
    for(int y=0;y<8;y++){
        printf(" %i  ",(reverse ? y : 7-y)+1);
        for(int x=0;x<8;x++){
            reverse ? vector_set(&position,7-x,7-y) : vector_set(&position,x,y);
            ShownCase(*get_piece(board,&position));
        }   
        printf("\n\n");
    }
    ShownLettre(board,reverse);
}