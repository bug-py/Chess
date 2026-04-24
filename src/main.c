#include <stdio.h>
#include <stdlib.h>
#include "logique/board.h"
#include "structdata/dynamic_array.h"

int main(){
   chessboard_t board;
   init_board(board);
   movement_t move={.from={1,1} ,.to={7,7},.type=ATTACK_MOVEMENT };
  
   printf("%i\n",apply_move(board,&move));
   printf("%i\n",get_type(move.captured_piece));
   printf("%i\n",undo_move(board,&move));
   
   return 0;
}