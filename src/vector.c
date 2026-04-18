#include "vector.h"
#include <stddef.h>
void VECTOR_set(vector_t* vector,int x,int y){
    vector->x=x;
    vector->y=y;
}
void VECTOR_add(vector_t* main,vector_t* new,int x,int y){
    if(new==NULL){
        main->x+=x;
        main->y+=y;
    }else{
        new->x=main->x+x;
        new->y=main->y+y;
    }
}