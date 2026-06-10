#ifndef GAME_H
#define GAME_H
#include "./piece.h"
#include "./board.h"
#include "./move.h"
#include "structdata/dynamic_array.h"
#include <stdbool.h>
#include <stdint.h>
typedef enum{
    GAME_BOARD_ILLEGAL=-1,
    GAME_IN_PROGRESS,
    GAME_VICTORY_WHITE,
    GAME_VICTORY_BLACK,
    GAME_DRAWN
}GameResult_t;
typedef struct{
    chessboard_t board;
    piece_color_t turn;
    int black_score;
    int white_score;
}game_t;
void init_game(game_t* game);
int apply_move(game_t* game,movement_t* move);
int undo_move(game_t* game,movement_t* move);
array_t* legal_generation(game_t* game,vector_t* position);
GameResult_t GetGameResult(game_t* game);
#endif