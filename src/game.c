#include "logique/game.h"
#include "logique/generation.h"
#include "logique/attack.h"
#include "structdata/alloc.h"
#include  <stdlib.h>

int get_score(piece_t piece){
    switch(get_type(piece)){
        case EMPTY : return 0;
        case PAWN : return 1;
        case KNIGHT : return 3; 
        case BISHOP:  return 3;
        case ROOK : return 5;
        case QUEEN : return 9;
        case KING : return -1;
    }
}
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
    switch(game->turn){
        case WHITE :
            game->black_score-=get_score(move->captured_piece);
            game->turn=BLACK;
            break;
        case BLACK :
            game->white_score-=get_score(move->captured_piece);
            game->turn=WHITE;
            break;
        case NO_COLOR:
            return -1;
    }
    return 0;
}

int undo_move(game_t* game,movement_t* move){
    piece_t* from=get_piece(game->board,&(move->from));
    piece_t* to=get_piece(game->board,&(move->to));
    if(!from || !to || is_empty(*to) || move->moved_piece!=*to) return -1;
    switch(move->type){
        case NORMAL_MOVEMENT:
            if(!is_empty(*from) || move->captured_piece!=NULL_PIECE) return -1;
            move_piece(to,from,NULL_PIECE);
            break;
        case ATTACK_MOVEMENT:
            if(!is_empty(*from) || move->captured_piece==NULL_PIECE ) return -1;
            move_piece(to,from,move->captured_piece);
            break;
    }
    switch(game->turn){
        case WHITE :
            game->black_score+=get_score(move->captured_piece);
            game->turn=BLACK;
            break;
        case BLACK :
            game->white_score+=get_score(move->captured_piece);
            game->turn=WHITE;
            break;
        case NO_COLOR:  
            return -1;
    }
    return 0;
}

array_t* legal_generation(game_t* game,vector_t* position){
  array_t* legal_moves=safe_alloc(sizeof(array_t),1,NULL);
  array_init(legal_moves,sizeof(movement_t),5);
  array_t* brut_moves=brut_generation(game->board,position);
  piece_t color_king=game->turn;
  for(size_t i=0;i<array_length(brut_moves);i++){
    movement_t* move=array_at(brut_moves,i);
    apply_move(game,move);
    if(!is_echec(game->board,color_king)) array_append(legal_moves,move);
    undo_move(game,move);
  }
  array_destroy(brut_moves);
  free(brut_moves);

  return legal_moves;
}
GameResult_t GetGameResult(game_t* game){
    vector_t position;
    for(size_t y=0;y<8;y++){
        for (size_t x=0;x<8;x++){
            vector_set(&position,x,y);
            piece_t* piece=get_piece(game->board,&position);
            if(piece && game->turn==get_color(*piece)){
                array_t* array=legal_generation(game,&position);
                size_t length=array_length(array);
                array_destroy(array);
                free(array);
                if(length>0) return GAME_IN_PROGRESS;
            }
        }
    }
    if(is_echec(game->board,game->turn)){
        switch(game->turn){
            case BLACK : return GAME_VICTORY_WHITE;
            case WHITE : return GAME_VICTORY_BLACK;
        }
    }else{
        return GAME_DRAWN;
    }
   
   
}
