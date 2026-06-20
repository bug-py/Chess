#include "logique/game.h"
#include "logique/generation.h"
#include "logique/attack.h"
#include "structdata/alloc.h"
#include "logique/direction.h"
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
    init_state(&(game->state));
    game->turn=WHITE;
    game->black_score=(8*1)+(2*3)+(2*3)+(2*5)+9;
    game->white_score=(8*1)+(2*3)+(2*3)+(2*5)+9;
}
void update_state(special_move_state_t* state,piece_t piece,vector_t* from,vector_t* to){
    set_in_passing(state,-1);
    bool is_white=(get_color(piece)==WHITE);
    switch(get_type(piece)){
        case KING :
            set_roque(state,(is_white ? WHITE_BIG_ROQUE : BLACK_BIG_ROQUE),false);
            set_roque(state,(is_white ? WHITE_LITTLE_ROQUE : BLACK_LITTLE_ROQUE),false);
            break;
        case ROOK:
            const vector_t* rook_roque;
            rook_roque= is_white ? &(white_big_roque.start_rook) : &(black_big_roque.start_rook);
            if(vector_cmp(from,rook_roque)){
                 set_roque(state,(is_white ? WHITE_BIG_ROQUE : BLACK_BIG_ROQUE),false);
                 break;
            }
            rook_roque= is_white ? &(white_little_roque.start_rook) : &(black_little_roque.start_rook);
            if(vector_cmp(from,rook_roque)){
                set_roque(state,(is_white ? WHITE_LITTLE_ROQUE : BLACK_LITTLE_ROQUE),false);
                break;
            }
            break;
        case PAWN:
            if( is_white ? (from->y==6 && to->y==4) : (from->y==1 && to->y==3)){
                set_in_passing(state,from->x);
            }
            break;
        default : 
            break;
    }
   
}
int apply_move(game_t* game,movement_t* move){
    piece_t* from=get_piece(game->board,&(move->from));
    piece_t* to=get_piece(game->board,&(move->to));
    if(!from || !to ) return -1;
    if(is_empty(*from)) return -1;
    move->moved_piece=*from;
    move->captured_piece=NULL_PIECE;
    if(move->flag & ATTACK_MOVEMENT){
        if(is_empty(*to) || get_color(*from)==get_color(*to)) return -1;
        move->captured_piece=*to;
    }
    if(move->flag & (BIG_ROQUE | LITTLE_ROQUE)){
        if( get_type(*from)!=KING ) return -1;
        bool is_white=(get_color(*from)==WHITE);

        const roque_data_t* roque_data;
        if(move->flag & BIG_ROQUE){
            roque_data= is_white ? &(white_big_roque) : &(black_big_roque);
        }else if (move->flag & LITTLE_ROQUE){
            roque_data= is_white ? &(white_little_roque) : &(black_little_roque);
        }
            
        piece_t* rook_piece=get_piece(game->board,&(roque_data->start_rook));
        if(!rook_piece || get_type(*rook_piece)!=ROOK) return -1;
        piece_t* empty_piece=get_piece(game->board,&(roque_data->end_rook));
        if(!empty_piece|| !is_empty(*empty_piece)) return -1;

        move_piece(rook_piece,empty_piece,NULL_PIECE);
    }
    update_state(&(game->state),*from,&(move->from),&(move->to));
    move_piece(from,to,NULL_PIECE);

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

int undo_move(game_t* game,movement_t* move,special_move_state_t* reset){
    piece_t* from=get_piece(game->board,&(move->from));
    piece_t* to=get_piece(game->board,&(move->to));
    if(!from || !to ) return -1;
    if(!is_empty(*from) ||is_empty(*to) || move->moved_piece!=*to) return -1;
    move_piece(to,from,NULL_PIECE);
    if(move->flag & ATTACK_MOVEMENT){
        if(move->captured_piece==NULL_PIECE) return -1;
        *to=move->captured_piece;
        
    }
    if(move->flag & (BIG_ROQUE | LITTLE_ROQUE)){
        if( get_type(*from)!=KING ) return -1;
        bool is_white=(get_color(*from)==WHITE);

        const roque_data_t* roque_data;
        if(move->flag & BIG_ROQUE){
            roque_data= is_white ? &(white_big_roque) : &(black_big_roque);
        }else if (move->flag & LITTLE_ROQUE){
            roque_data= is_white ? &(white_little_roque) : &(black_little_roque);
        }
            
        piece_t* empty_piece=get_piece(game->board,&(roque_data->start_rook));
        if(!empty_piece || !is_empty(*empty_piece)) return -1;
        piece_t* rook_piece=get_piece(game->board,&(roque_data->end_rook));
        if(!rook_piece || get_type(*rook_piece)!=ROOK) return -1;

        move_piece(rook_piece,empty_piece,NULL_PIECE);
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
    copy_state(&(game->state),reset);
    return 0;
}
bool check_roque_legality(movement_t* move,chessboard_t board){
    if(!(move->flag & (BIG_ROQUE | LITTLE_ROQUE))) return true;

    bool is_white=get_color(move->moved_piece)==WHITE;
    const roque_data_t* roque_data;
    if(move->flag & BIG_ROQUE) roque_data= is_white ? &(white_big_roque) : &(black_big_roque);
    if(move->flag & LITTLE_ROQUE) roque_data= is_white ? &(white_little_roque) : &(black_little_roque);
    piece_color_t color_enemy= is_white ? BLACK : WHITE;
    for(size_t i=0;i<roque_data->count_path_king;i++){
        if (is_attack(board,&(roque_data->path_king[i]),color_enemy)) return false;
    }
    return true ;         
      
}
array_t* legal_generation(game_t* game,vector_t* position,bool promotion){
  array_t* legal_moves=safe_alloc(sizeof(array_t),1,NULL);
  array_init(legal_moves,sizeof(movement_t),5);
  array_t* brut_moves=brut_generation(game->board,position,&(game->state),promotion);
  piece_t color_king=game->turn;
  special_move_state_t main_state;
  copy_state(&main_state,&(game->state));
  for(size_t i=0;i<array_length(brut_moves);i++){
    movement_t* move=array_at(brut_moves,i);
    if (!check_roque_legality(move,game->board)) continue;
    apply_move(game,move);
    if(!is_echec(game->board,color_king)) array_append(legal_moves,move);
    undo_move(game,move,&main_state);
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
                array_t* array=legal_generation(game,&position,false);
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
