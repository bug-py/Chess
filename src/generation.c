#include "logique/generation.h"
#include "structdata/alloc.h"
#include "logique/direction.h"

void step_movement(chessboard_t board,vector_t* position,piece_t piece,array_t* array,const vector_t* vector,size_t length){
    vector_t to;
    for(size_t i=0;i<length;i++){
        vector_add(position,&(vector[i]),&to);
        piece_t* other=get_piece(board,&to);
        if(!other) continue;
        if(is_empty(*other)){
            array_append(array,NULL);
            init_move(array_at(array,array->length-1), position,&to, piece,NULL_PIECE,NORMAL_MOVEMENT);
        }else if(get_color(piece)!=get_color(*other)){
            array_append(array,NULL);
            init_move(array_at(array,array->length-1), position,&to, piece,*other,ATTACK_MOVEMENT);
        }
    }   
}
void ray_movement(chessboard_t board,vector_t* position,piece_t piece,array_t* array,const vector_t* vector,size_t length){
   
    for(size_t i=0;i<length;i++){
        vector_t to=*position;
        while(true){
            vector_add(&to,&(vector[i]),&to);
            piece_t*other=get_piece(board,&to);
            if(!other) break;
            if(is_empty(*other)){
                array_append(array,NULL);
                init_move(array_at(array,array->length-1), position,&to, piece,NULL_PIECE,NORMAL_MOVEMENT);
                continue;
            }
            if(get_color(piece)!=get_color(*other)){
                array_append(array,NULL);
                init_move(array_at(array,array->length-1), position,&to, piece,*other,ATTACK_MOVEMENT);
            } 
            break;

        }
    }
}
void special_pawn(chessboard_t board,vector_t* position,piece_t piece,array_t* array){
    int color=(get_color(piece)==WHITE) ? 0 : 1;
    piece_t* other;
    vector_t to;
    vector_add(position,&(pawn[color][0]),&to);
    other=get_piece(board,&to);
    if(other && is_empty(*other)){
        array_append(array,NULL);
        init_move( array_at(array,array->length-1), position,&to, piece,NULL_PIECE, NORMAL_MOVEMENT );
        if(position->y== (color ? 1 : 6)){
            vector_add(position,&(pawn[color][1]),&to);
            other=get_piece(board,&to);
            if(other && is_empty(*other)){
                array_append(array,NULL);
                init_move( array_at(array,array->length-1), position,&to, piece,NULL_PIECE, NORMAL_MOVEMENT );
            }
        }
         
    }  
    for(int i=2;i<4;i++){
        vector_add(position,&(pawn[color][i]),&to);
        other=get_piece(board,&to);
        if(other && !is_empty(*other) && get_color(*other)!=get_color(piece)){
            array_append(array,NULL);
            init_move( array_at(array,array->length-1), position,&to, piece,*other, ATTACK_MOVEMENT );
        }

    } 
}



array_t* brut_generation(chessboard_t board,vector_t* position){
    piece_t* piece=get_piece(board,position);
    if(!piece) return NULL;
    array_t* array=safe_alloc(sizeof(array_t),1,NULL);
    array_init(array,sizeof(movement_t),5);
    switch(get_type(*piece)){
        case EMPTY :  break;
        case PAWN :   special_pawn(board,position,*piece,array); break;
        case KNIGHT : step_movement(board,position,*piece,array,knight,SIZE_KNIGHT); break;
        case BISHOP : ray_movement(board,position,*piece,array,bishop,SIZE_BISHOP); break;
        case ROOK :   ray_movement(board,position,*piece,array,rook,SIZE_ROOK); break;
        case QUEEN :  ray_movement(board,position,*piece,array,queen,SIZE_QUEEN); break;
        case KING :   step_movement(board,position,*piece,array,king,SIZE_KING); break;
    }
    return array;
}