#ifndef _VECTOR_H
#define _VECTOR_H
typedef struct{
    int x;
    int y;
}vector_t;
void vector_set(vector_t* vector,int x,int y);
void vector_add(const vector_t* main,const vector_t* other,vector_t* new);
#endif