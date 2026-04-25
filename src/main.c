#include <stdio.h>
#include <stdlib.h>
#include "logique/board.h"
#include "logique/move.h"
#include "logique/generation.h"
#include "logique/piece.h"
#include "structdata/dynamic_array.h"
void PrintPiece(char* name,piece_t piece){
   printf("%s type : ",name);
   switch(get_type(piece)){
      case EMPTY: printf("EMPTY"); break;
      case PAWN : printf("PAWN"); break;
      case KNIGHT : printf("KNIGHT"); break;
      case BISHOP : printf("BISHOP"); break;
      case ROOK : printf("ROOK"); break;
      case QUEEN : printf("QUEEN"); break;
      case KING : printf("KING"); break;
   }
   printf(" color :");
   switch(get_color(piece)){
      case NO_COLOR: printf("NO COLOR"); break;
      case WHITE : printf("WHITE"); break;
      case BLACK : printf("BLACK"); break;
   }
   putchar('\n');


}
void PrintMove(movement_t* move){
   printf("from | x : %d y: %d|\n",move->from.x,move->from.y);
   printf("to | x : %d y: %d|\n",move->to.x,move->to.y);
   PrintPiece("MOVED PIECE",move->moved_piece);
   PrintPiece("CAPTURED PIECE",move->captured_piece);
   switch(move->type){
      case NORMAL_MOVEMENT: printf("NORMAL MOVEMENT\n"); break;
      case ATTACK_MOVEMENT: printf("ATTACK MOVEMENT\n"); break;
   }
   
   
}
int main(){
   chessboard_t board;
   init_board(board);
   vector_t position={.x=4,.y=3};
   piece_t* piece=get_piece(board,&position);
   *piece=init_piece(QUEEN,WHITE);
   array_t* array=generation(board,&position);
   printf("SIZE : %lu\n\n",array->length);
   for(size_t i=0;i<array->length;i++){
      PrintMove(array_at(array,i));
      putchar('\n');
   }
   return 0;
}