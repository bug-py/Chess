#ifndef _VECTOR_H
#define _VECTOR_H
#include <stdbool.h>
typedef struct{
    int x;
    int y;
}vector_t;
void vector_set(vector_t* vector,int x,int y);
void vector_add(const vector_t* main,const vector_t* other,vector_t* new);
bool vector_cmp(const vector_t* one ,const vector_t* two);
#endif