#include <stdio.h>
#include <stdlib.h>
#include "logique/move.h"
#include "structdata/dynamic_array.h"
void PrintVector(array_t* array){
    vector_t* list=array_get(array);
    for(size_t i=0;i<array_lenght(array);i++){
        printf("|x :%i y :%i|",list[i].x,list[i].y);
    }
    putchar('\n');
}

int main(){
    chessboard_t board;
    vector_t p={.x=4,.y=3};
    printf("%lu\n",sizeof(board));
    init_board(board);
    init_piece(get_piece(board,&p),WHITE,QUEEN,false);
    array_t* array=generation_coup(board,&p);
    PrintVector(array);
    array_destroy(array);
    free(array);

    return 0;
}