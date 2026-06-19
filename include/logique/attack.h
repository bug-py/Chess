#ifndef ATTACK_H
#define  ATTACK_H
#include "./board.h"
#include "./piece.h"
#include "vector.h"
#include <stdbool.h>
int is_attack(chessboard_t board,const vector_t* position,piece_color_t color_enemy);
int is_echec(chessboard_t board,piece_color_t color_enemy);
#endif