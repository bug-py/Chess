#include "structdata/dynamic_array.h"
#include "structdata/alloc.h"
#include <string.h>
#include <stdlib.h>
void* get_ptr_index(void* base,size_t element_size,size_t index){
    return ((char*)base)+(element_size*index);
}

void array_init(array_t* array,size_t element_size,size_t init_capacity){
    if(!element_size) element_size=1;
    if(!init_capacity) init_capacity=1;
    array->element_size=element_size;
    array->capacity=init_capacity;
    array->length=0;
    array->body=safe_alloc(element_size,init_capacity,NULL);
}
void array_append(array_t* array,void* element){
    if(array->length>=array->capacity){
        array->capacity=array->length*2;
        array->body=safe_alloc(array->element_size,array->capacity,array->body);
    }
    memcpy(get_ptr_index(array->body,array->element_size,array->length),element,array->element_size);
    array->length++;
}
void array_remove(array_t* array,size_t index){
    if(index>=array->length){
        return;
    }
    for(size_t i=index+1;i<array->length;i++){
        memcpy(get_ptr_index(array->body,array->element_size,i-1),get_ptr_index(array->body,array->element_size,i),array->element_size);
    }
    array->length--;
    
}
void* array_at(array_t* array,size_t index){
    if(index<array->length){
        return get_ptr_index(array->body,array->element_size,index);
    }
    return NULL;
}
void* array_get(array_t* array){
    return array->body;
}
size_t array_lenght(array_t* array){
    return array->length;
}
void array_destroy(array_t* array){
    array->element_size=0;
    array->length=0;
    array->capacity=0;
    free(array->body);
}