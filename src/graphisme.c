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
void TraductCordo(vector_t* position,char cordo[2],bool reverse){
    switch(cordo[0]){
        case 'A' : position->x=0; break;
        case 'B' : position->x=1; break;
        case 'C' : position->x=2; break;
        case 'D' : position->x=3; break;
        case 'E' : position->x=4; break;
        case 'F' : position->x=5; break;
        case 'G' : position->x=6; break;
        case 'H' : position->x=7; break;
    }
    switch(cordo[1]){
        case '1' : position->y=7; break;
        case '2' : position->y=6; break;
        case '3' : position->y=5; break;
        case '4' : position->y=4; break;
        case '5' : position->y=3; break;
        case '6' : position->y=2; break;
        case '7' : position->y=1; break;
        case '8' : position->y=0; break;
    }
    if (reverse) vector_set(position,7-position->x,7-position->y); 
}
void TraductVector(char cordo[2],vector_t* position,bool reverse){
    if (reverse) vector_set(position,7-position->x,7-position->y); 
    switch(position->x){
        case 0 : cordo[0]='A'; break;
        case 1 : cordo[0]='B'; break;
        case 2 : cordo[0]='C'; break;
        case 3 : cordo[0]='D'; break;
        case 4 : cordo[0]='E'; break;
        case 5 : cordo[0]='F'; break;
        case 6 : cordo[0]='G'; break;
        case 7 : cordo[0]='H'; break;
    }
    switch(position->y){
        case 0 : cordo[1]='8'; break;
        case 1 : cordo[1]='7'; break;
        case 2 : cordo[1]='6'; break;
        case 3 : cordo[1]='5'; break;
        case 4 : cordo[1]='4'; break;
        case 5 : cordo[1]='3'; break;
        case 6 : cordo[1]='2'; break;
        case 7 : cordo[1]='1'; break;
    }
}