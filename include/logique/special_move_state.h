#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H
#include "stdint.h"
#include "stdbool.h"
typedef enum{
    BLACK_BIG_ROQUE,
    BLACK_LITTLE_ROQUE,
    WHITE_BIG_ROQUE,
    WHITE_LITTLE_ROQUE
}roque_type_t;
typedef struct {
  uint8_t roque;
  uint8_t in_passing;
} special_move_state_t;
void init_state(special_move_state_t* state);
int get_in_passing(special_move_state_t* state);
void set_in_passing(special_move_state_t* state,int collum);
bool get_roque(special_move_state_t* state,roque_type_t type_roque);
void set_roque(special_move_state_t* state,roque_type_t type_roque,bool possible);
void copy_state(special_move_state_t* dest,special_move_state_t* src);

#endif