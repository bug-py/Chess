#include "logique/generation.h"
#include "structdata/alloc.h"
#include "logique/direction.h"
#include <stdio.h>
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
bool in_passing(chessboard_t board,vector_t* position,piece_t piece,movement_t* move,int column){
    if (column<0) return false;
    bool is_white=(get_color(piece)==WHITE);
    vector_t position_in_passing_right;
    vector_t position_in_passing_left;
    vector_t position_in_passing_to;
    vector_set(&position_in_passing_right,column-1,is_white ? 4 : 3 );
    vector_set(&position_in_passing_left,column+1,is_white ? 4 : 3 );
    vector_set(&position_in_passing_to,column,is_white ? 3 : 5 );
    if(vector_cmp(position,&position_in_passing_left) || vector_cmp(position,&position_in_passing_right) ){
        init_move(move,position,&position_in_passing_to,piece,NULL_PIECE,IN_PASSING);
        return true;
    }
    return false;

}
void special_pawn(chessboard_t board,vector_t* position,piece_t piece,special_move_state_t* state,array_t* array){
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
    movement_t move_passing;
    if(in_passing(board,position,piece,&move_passing,get_in_passing(state))){
        array_append(array,&move_passing);
    }
    

}
bool roque(chessboard_t board,piece_color_t color,movement_t* move,const roque_data_t* brut_info){
    
    piece_t* king=get_piece(board,&(brut_info->start_king));
    if(  !(king && get_type(*king)==KING && get_color(*king)==color) ) return false;
    piece_t* rook=get_piece(board,&(brut_info->start_rook));
    if( ! (rook && get_type(*rook)==ROOK &&  get_color(*rook)==color)) return false;
    for(size_t i=0;i<brut_info->count_empty_case;i++){
        piece_t* piece=get_piece(board,&(brut_info->empty_case[i]));
        if (! (piece && is_empty(*piece))) return false;
    }
    init_move(move,&(brut_info->start_king),&(brut_info->end_king),*king,NULL_PIECE,NORMAL_MOVEMENT);
    return true;
}
void special_king(chessboard_t board,vector_t* position,piece_t piece,special_move_state_t* state,array_t* array){
    step_movement(board,position,piece,array,king,SIZE_KING);
   
    movement_t move_roque;
    switch(get_color(piece)){
        case BLACK:
            if(get_roque(state,BLACK_BIG_ROQUE) && roque(board,BLACK,&move_roque,&black_big_roque)){
                    move_roque.flag=BIG_ROQUE;
                    array_append(array,&move_roque);
            }
            if(get_roque(state,BLACK_LITTLE_ROQUE) && roque(board,BLACK,&move_roque,&black_little_roque)){
                    move_roque.flag=LITTLE_ROQUE;
                    array_append(array,&move_roque);
            }
            break;
        case WHITE :
            if(get_roque(state, WHITE_BIG_ROQUE) && roque(board,WHITE,&move_roque,&white_big_roque)){
                   move_roque.flag=BIG_ROQUE;
                    array_append(array,&move_roque);
            }
            if(get_roque(state,WHITE_LITTLE_ROQUE) && roque(board,WHITE,&move_roque,&white_little_roque)){
                    move_roque.flag=LITTLE_ROQUE;
                    array_append(array,&move_roque);
            }
            break;
        case NO_COLOR:
            return;
    }
}


array_t* brut_generation(chessboard_t board,vector_t* position,special_move_state_t* state,bool promotion){
   
    piece_t* piece=get_piece(board,position);
    if(!piece) return NULL;
    array_t* array=safe_alloc(sizeof(array_t),1,NULL);
    array_init(array,sizeof(movement_t),5);
    switch(get_type(*piece)){
        case EMPTY :   break;
        case PAWN :   special_pawn(board,position,*piece,state,array); break;
        case KNIGHT : step_movement(board,position,*piece,array,knight,SIZE_KNIGHT); break;
        case BISHOP : ray_movement(board,position,*piece,array,bishop,SIZE_BISHOP); break;
        case ROOK :   ray_movement(board,position,*piece,array,rook,SIZE_ROOK); break;
        case QUEEN :  ray_movement(board,position,*piece,array,queen,SIZE_QUEEN); break;
        case KING :   special_king(board,position,*piece,state,array);  break;
    }
    return array;
}