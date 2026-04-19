#include "vector.h"
#include <stddef.h>
void vector_set(vector_t* vector,int x,int y){
    vector->x=x;
    vector->y=y;
}
void vector_add(const vector_t* main,const vector_t* other,vector_t* new){
    new->x=main->x+other->x;
    new->y=main->y+other->y;
}