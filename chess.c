#include <stdbool.h>

#include <stdio.h>

typedef enum {
    NOT_COLOR,
    BLACK,
    WHITE
}piece_color_t;
typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
}piece_type_t;
typedef struct {
    int x;
    int y;
}vector_t;
typedef struct{
    piece_color_t color;
    piece_type_t type;
    bool playing;
}piece_t;

void add(vector_t* main,vector_t* new,int x,int y){
        if(new==NULL){
            main->x+=x;
            main->y+=y;
        }else{
            new->x=main->x+x;
            new->y=main->y+y;
        }
}
bool limit(vector_t* vector){
    if(vector->x>7 || vector->x>7 || vector->x<0 || vector->y<0){
        return true;
    }
    return false;
}
piece_t* GetPiece(piece_t game[8][8],vector_t* position){
    if(limit(position)){
        return NULL;
    }
    return &(game[position->y][position->x]);
}
void push(vector_t* current,vector_t* array,size_t* size){
        array[*size]=*current;
        *size+=1;
}

size_t position(piece_t game[8][8],vector_t* actual,vector_t array[8*8]){
    piece_t* piece=GetPiece(game,actual);
    if(piece==NULL) return 0;
    size_t size=0;
    vector_t vector;
    piece_t* current;
    switch(piece->type){
        case EMPTY:
            return 0;
        case PAWN:
            if(piece->color==WHITE){
                add(actual,&vector,0,-1);
                current=GetPiece(game,&vector);
                if(current && current->type==EMPTY){
                    push(&vector,array,&size);

                    if(!piece->playing){
                        add(actual,&vector,0,-2);
                        current=GetPiece(game,&vector);
                        if(current && current->type==EMPTY){
                            push(&vector,array,&size);
                        }
                    }
        
                }
                add(actual,&vector,-1,-1);
                current=GetPiece(game,&vector);
                if(current && current->type!=EMPTY && current->color==BLACK){
                    push(&vector,array,&size);
                }
                add(actual,&vector,1,-1);
                current=GetPiece(game,&vector);
                if(current && current->type!=EMPTY && current->color==BLACK){
                    push(&vector,array,&size);
                }
               

            }else{
                add(actual,&vector,0,1);
                current=GetPiece(game,&vector);
                if(current && current->type==EMPTY){
                    push(&vector,array,&size);

                    if(!piece->playing){
                        add(actual,&vector,0,2);
                        current=GetPiece(game,&vector);
                        if(current && current->type==EMPTY){
                            push(&vector,array,&size);
                        }
                    }
        
                }
                add(actual,&vector,-1,1);
                current=GetPiece(game,&vector);
                if(current && current->type!=EMPTY && current->color==BLACK){
                    push(&vector,array,&size);
                }
                add(actual,&vector,1,1);
                current=GetPiece(game,&vector);
                if(current && current->type!=EMPTY && current->color==BLACK){
                    push(&vector,array,&size);
                }
            }
            break;
        case KNIGHT:
             add(actual,&vector,1,2);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,-1,2);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,1,-2);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,-1,-2);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,2,1);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,2,-1);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,-2,1);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             add(actual,&vector,-2,-1);
             if(GetPiece(game,&vector)){
                    push(&vector,array,&size);
             }
             break;
        
    }
    return size;
}
int main(){
    piece_t game[8][8]={{{BLACK,ROOK,false},{BLACK,KNIGHT,false},{BLACK,BISHOP,false},{BLACK,QUEEN,false},{BLACK,KING,false},{BLACK,BISHOP,false},{BLACK,KNIGHT,false},{BLACK,ROOK,false}},
                        {{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false},{BLACK,PAWN,false}},
                        {{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false}},
                        {{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,BISHOP,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false}},
                        {{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false}},
                        {{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false},{NOT_COLOR,EMPTY,false}},
                        {{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false},{WHITE,PAWN,false}},
                        {{WHITE,ROOK,false},{WHITE,KNIGHT,false},{WHITE,BISHOP,false},{WHITE,QUEEN,false},{WHITE,KING,false},{WHITE,BISHOP,false},{WHITE,KNIGHT,false},{WHITE,ROOK,false}}
                        };
    vector_t all[8*8];
    vector_t vector={.y=3,.x=2};
    printf("%llu",position(game,&vector,all));
}

