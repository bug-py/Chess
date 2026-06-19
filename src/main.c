#include <stdio.h>
#include "graphisme.h"
#include "logique/game.h"
#include "logique/generation.h"
#include <stdlib.h>
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
   switch(move->flag){
      case NORMAL_MOVEMENT: printf("NORMAL MOVEMENT\n"); break;
      case ATTACK_MOVEMENT: printf("ATTACK MOVEMENT\n"); break;
      case BIG_ROQUE : printf("BIG-ROQUE MOVEMENT\n"); break;
      case LITTLE_ROQUE : printf("LITTLE-ROQUE MOVEMENT\n"); break;
   }  
}
int main(){
   game_t game;
   
   init_game(&game);
   vector_t position={4,0};
   array_t* array=brut_generation(game.board,&position,&(game.state),false);
   for(size_t i=0;i<array->length;i++){
      PrintMove(((movement_t*)array->body)+i);
   }
   printf("END\n");
  
   while(1){
      switch(GetGameResult(&game)){
         case GAME_IN_PROGRESS :
            printf("PROGRESS...\n");
            break;
         case GAME_VICTORY_BLACK :
            printf("VICTORY BLACK !\n");
            return 0;
         case GAME_VICTORY_WHITE :
            printf("VICTORY WHITE !\n");
            return 0;
         case GAME_DRAWN :
            printf("DRAWN \n");
            return 0;
      }
      bool reverse=(game.turn==BLACK);
      ShownBoard(game.board,reverse);
      char from[3]="  ";
      char to[3]="  ";
      scanf(" %c%c => %c%c",&(from[0]),&(from[1]),&(to[0]),&(to[1]));
      vector_t begin;
      vector_t end;

      TraductCordo(from,&begin,false);
      TraductCordo(to,&end,false);
      array_t* coup=legal_generation(&game,&begin,false);
      for(size_t i=0;i<coup->length;i++){
         movement_t* move=array_at(coup,i);
         if(vector_cmp(&begin,&(move->from)) && vector_cmp(&end,&(move->to))){
            
            apply_move(&game,move);
            break;
         }
   }
   array_destroy(coup);
   free(coup);
   }
 
}