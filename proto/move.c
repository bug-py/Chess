#include "logique/move.h"
#include "structdata/alloc.h"
#include <stdio.h>

const vector_t pawn[2][4]={
    {{0,-1},{0,-2},{1,-1},{-1,-1}},
    { {0,1},{0,2},{1,1},{-1,1}}
};
const vector_t knight[8]={
    {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}
};
const vector_t bishop[4]={
    {1,1},{-1,1},{1,-1},{-1,-1}
};
const vector_t rook[4]={
    {1,0},{-1,0},{0,1},{0,-1}
};
const vector_t queen[8]={
    {1,1},{-1,1},{1,-1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}
};
const vector_t king[8]={
    {1,1},{-1,1},{1,-1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}
};



void step_movement(chessboard_t board,vector_t* position,piece_t* piece,array_t* result,const vector_t* movement,size_t size){
    vector_t to;
    for(size_t i=0;i<size;i++){
        
        vector_add(position,movement+i,&to);
        piece_t* other=get_piece(board,&to);
        // case valid et pièce non-allié 
        if(other && other->color!=piece->color){
            array_append(result,&to);
        }

    }
}
void ray_movement(chessboard_t board,vector_t* position,piece_t* piece,array_t* result,const vector_t* movement,size_t size){
    for(size_t i=0;i<size;i++){
        vector_t to=*position;
        while(true){
            vector_add(&to,movement+i,&to);
            piece_t* other=get_piece(board,&to);
            // case non valid exit
            if(!other) break;
            // case vide continue
            if(is_empty(other)){
                array_append(result,&to);
                continue;
            }
            // case avec une pièce non-allié ajout puis exit
            if(other->color!=piece->color){
                array_append(result,&to);
                break;
            }
           // case avec un allié exit
            break;
            
        }
    }
}
void pawn_movement(chessboard_t board,vector_t* position,piece_t* piece,array_t* result){
    
    int i= (piece->color==WHITE) ? 0 : 1;
    vector_t to;
    piece_t* other;
    vector_add(position,pawn[i]+0,&to);
    other=get_piece(board,&to);

    if(other && is_empty(other)){

        array_append(result,&to);
        if(!piece->has_moved){
            vector_add(position,pawn[i]+1,&to);
            other=get_piece(board,&to);
            if(other && is_empty(other)) array_append(result,&to);
        }
    }
    for(int move=2;move<4;move++){
        vector_add(position,pawn[i]+move,&to);
        other=get_piece(board,&to);
        if(other && !is_empty(other) && other->color!=piece->color) array_append(result,&to);
    }
     
}

array_t* generation_coup(chessboard_t board,vector_t* position){
    piece_t* piece=get_piece(board,position);
    if(!piece) return NULL;
    array_t* array=safe_alloc(sizeof(array_t),1,NULL);
    array_init(array,sizeof(vector_t),4);
    switch(piece->type){
        case EMPTY:
            break;
        case PAWN:
            pawn_movement(board,position,piece,array);
            break;
        case KNIGHT:
            step_movement(board,position,piece,array,knight,sizeof(knight)/sizeof(vector_t));
            break;
        case ROOK:
            ray_movement(board,position,piece,array,rook,sizeof(rook)/sizeof(vector_t));
            break;
        case BISHOP:
            ray_movement(board,position,piece,array,bishop,sizeof(bishop)/sizeof(vector_t));
            break;
        case QUEEN:
            ray_movement(board,position,piece,array,queen,sizeof(queen)/sizeof(vector_t));
            break;
        case KING :
            step_movement(board,position,piece,array,king,sizeof(king)/sizeof(vector_t));
            break;        
    }
    return array;
}
