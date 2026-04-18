#ifndef _VECTOR_H
#define _VECTOR_H
typedef struct{
    int x;
    int y;
}vector_t;
void VECTOR_set(vector_t* vector,int x,int y);
void VECTOR_add(vector_t* main,vector_t* new,int x,int y);
#endif