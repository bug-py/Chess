#include <stdio.h>
#include "logique/board.h"
#include "structdata/dynamic_array.h"
void PrintArray(array_t* array){
    int* list=array_get(array);
    for(size_t i=0;i<array_lenght(array);i++){
        printf("|%i|",list[i]);
    }
    putchar('\n');
}

int main(){
    chessboard_t board;
    printf("%lu\n",sizeof(board));
    init_board(board);
    vector_t position={.x=3,.y=1};
    piece_t* piece=get_piece(board,&position);
    if(!piece){
        printf("Limit");
        return 1;
    }
    printf("%i %i %i\n",piece->color,piece->type,piece->has_moved);
    vector_t end={.x=3,.y=2};
    piece=move_piece(board,&position,&end);
    if(!piece){
        printf("Limit");
        return -1;
    }
    printf("%i %i %i\n",piece->color,piece->type,piece->has_moved);
    array_t array;
    int number;
    array_init(&array,sizeof(int),1);
    number=-100;
    array_append(&array,&number);
    number=-200;
    array_append(&array,&number);
    number=67;
    array_append(&array,&number);
    number=1999;
    array_append(&array,&number);
    PrintArray(&array);
    array_remove(&array,0);
    PrintArray(&array);
    printf("%i\n",*(int*)array_at(&array,1));
    array_destroy(&array);
    return 0;
}