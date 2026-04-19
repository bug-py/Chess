#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stddef.h>
typedef struct{
    size_t element_size;
    size_t length;
    size_t capacity;
    void* body;
}array_t;
void array_init(array_t* array,size_t element_size,size_t init_capacity);
void array_append(array_t* array,void* element);
void array_remove(array_t* array,size_t index);
void* array_at(array_t* array,size_t index);
void* array_get(array_t* array);
size_t array_lenght(array_t* array);
void array_destroy(array_t* array);
#endif
