typedef struct{
    chessboard_t board;
    piece_t* piece;
    vector_t* position;
    vector_t* array;
    size_t 
}movement_context_t;
void static_movement(chessboard_t board,piece_t* piece,vector_t* position,array_t* array,vector_t* movement,size_t size)
typedef enum{
    NORMAL_MOVE,
    ELIMATED_MOVE,
    PROMOTION_MOVE,
    PASSANT_MOVE,
    ROQUE_MOVE
}movement_type_t;

typedef struct{
    piece_t piece;
    vector_t from;
    vector_t to;
    piece_t eliminated_piece;
    
    movement_type_t type;
    movement_state_t state;
    enum {
        vector_t pawn_passant_position;
        piece_t promotion;
    }special;
}movement_t;
bool case_attack(chessboard_t* board,vector_t* position,piece_color_t color){
        
}

void pawn(chessboard_t board,piece_t* piece,vector_t* position,array_t* array){
    if(piece->type!=PAWN) return;
    if(piece->color==WHITE){
        vector_t movement[4]={
        {0,-1},{0,-2},{1,-1},{-1,-1}
        };
    }else{
       vector_t movement[4]={
        {0,1},{0,2},{1,1},{-1,1}
       }
    }
    vector_t to;
    vector_add(position,&(movement[0]),&to);
        if(check_case(board,&to)==CASE_EMPTY){
            array_push(array,&to)
        if(!piece->has_moved){
            vector_add(position,&(movement[1]),&to)
            if(check_case(board,&to)==CASE_EMPTY) array_push(array,&to);
        }
    }
    
    vector_add(position,&(movement[3]),&to);
    if(check_case(board,&to)==piece->color) array_push(array,&to);
    vector_add(position,&(movement[4]),&to);
    if(check_case(board,&to)==piece->color) array_push(array,&to);
    
    
}
void kinght(chessboard_t board,piece_t* piece,vector_t* position,array_t* array){
    if(piece->type!=KNIGHT) return;
    vector_t movement[8]={
        {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}
    };
    vector_t to;
    for(int i=0;i<sizeof(movement);i++){
        vector_add(position,&(movement[i]),&to);
        switch(check_case(board,&to)){
             case piece->color:
             case CASE_LIMIT:
                break
             default :
                array_push(array,&to)
        }
    }
}