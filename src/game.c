#include "logique/game.h"
#include "logique/generation.h"
#include "logique/attack.h"
#include "structdata/alloc.h"
#include  <stdlib.h>
void init_game(game_t* game){
    init_board(game->board);
    game->turn=WHITE;
    game->black_score=(8*1)+(2*3)+(2*3)+(2*5)+9;
    game->white_score=(8*1)+(2*3)+(2*3)+(2*5)+9;
}

int apply_move(game_t* game,movement_t* move){
    piece_t* from=get_piece(game->board,&(move->from));
    piece_t* to=get_piece(game->board,&(move->to));
    if(!from || !to || is_empty(*from)) return -1;
    switch(move->type){
        case NORMAL_MOVEMENT:
            if(!is_empty(*to)) return -1;
            move->moved_piece=*from;
            move->captured_piece=NULL_PIECE;
            move_piece(from,to,NULL_PIECE);
            break;
        case ATTACK_MOVEMENT:
            if(is_empty(*to) || get_color(*from)==get_color(*to)) return -1;
            move->moved_piece=*from;
            move->captured_piece=*to;
            move_piece(from,to,NULL_PIECE);
            break;
    }
    return 0;
}

int undo_move(game_t* game,movement_t* move){
    piece_t* from=get_piece(game->board,&(move->from));
    piece_t* to=get_piece(game->board,&(move->to));
    if(!from || !to || is_empty(*to) || move->moved_piece!=*to) return -1;
    switch(move->type){
        case NORMAL_MOVEMENT:
            if(!is_empty(*from) ) return -1;
            move_piece(to,from,NULL_PIECE);
            break;
        case ATTACK_MOVEMENT:
            if(!is_empty(*from) ) return -1;
            move_piece(to,from,move->captured_piece);
            break;
    }
    return 0;
}

array_t* legal_generation(game_t* game,vector_t* position){
  array_t* legal_moves=safe_alloc(sizeof(array_t),1,NULL);
  array_init(legal_moves,sizeof(movement_t),5);
  array_t* brut_moves=brut_generation(game->board,position);
  for(size_t i=0;i<array_length(brut_moves);i++){
    movement_t* move=array_at(brut_moves,i);
    apply_move(game,move);
    if(!is_echec(game->board,game->turn)) array_append(legal_moves,move);
    undo_move(game,move);
  }
  array_destroy(brut_moves);
  free(brut_moves);

  return legal_moves;
}