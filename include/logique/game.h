#ifndef GAME_H
#define GAME_H
#include "./piece.h"
#include "./board.h"

#include <stdbool.h>
#include <stdint.h>
typedef struct{
    chessboard_t board;
    bool tour;
    int black_score;
    int white_score;
}game_t;

#endif