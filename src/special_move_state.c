#include "logique/special_move_state.h"
typedef enum{
    MASK_BLACK_LITTLE_ROQUE=1<<0,
    MASK_BLACK_BIG_ROQUE=1<<1,
    MASK_WHITE_LITTLE_ROQUE=1<<2,
    MASK_WHITE_BIG_ROQUE=1<<3,
}special_move_state_bitmask_t;
int get_roque_bitmask(roque_type_t type_roque){
    switch(type_roque){
        case BLACK_BIG_ROQUE:  return MASK_BLACK_BIG_ROQUE; 
           
        case BLACK_LITTLE_ROQUE: return MASK_BLACK_LITTLE_ROQUE; 
           
        case WHITE_BIG_ROQUE:  return MASK_WHITE_BIG_ROQUE; 
           
        case WHITE_LITTLE_ROQUE:  return MASK_WHITE_LITTLE_ROQUE; 

        default : return 0;
    }
}
void init_state(special_move_state_t* state){
    state->in_passing=0;
    state->roque=0x0F;
}
int get_in_passing(special_move_state_t* state){
    switch(state->in_passing){
        case 1<<0: return 0;
        case 1<<1: return 1;
        case 1<<2: return 2;
        case 1<<3: return 3;
        case 1<<4: return 4;
        case 1<<5: return 5;
        case 1<<6: return 6;
        case 1<<7: return 7;
        default : return -1;
    }
}
void set_in_passing(special_move_state_t* state,int column){
    if(column<0 || column>7){
        state->in_passing=0;
    }else{
       state->in_passing = 1<<column;
    }
   
}
bool get_roque(special_move_state_t* state,roque_type_t type_roque){
   
    return ( (state->roque) & get_roque_bitmask(type_roque) ); 
    
}
void set_roque(special_move_state_t* state,roque_type_t type_roque,bool possible){
        if(possible){
           state->roque|= get_roque_bitmask(type_roque);
        }else{
           state->roque&= ~(get_roque_bitmask(type_roque));
        }
}
void copy_state(special_move_state_t* dest,special_move_state_t* src){
    dest->in_passing=src->in_passing;
    dest->roque=src->roque;
}