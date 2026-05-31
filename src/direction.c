#include "logique/direction.h"
const vector_t pawn[2][4]={
    {{0,-1},{0,-2},{1,-1},{-1,-1}},
    { {0,1},{0,2},{1,1},{-1,1}}
};
const vector_t knight[SIZE_KNIGHT]={
    {1,2},{-1,2},{1,-2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}
};
const vector_t bishop[SIZE_BISHOP]={
    {1,1},{-1,1},{1,-1},{-1,-1}
};
const vector_t rook[SIZE_ROOK]={
    {1,0},{-1,0},{0,1},{0,-1}
};
const vector_t queen[SIZE_QUEEN]={
    {1,1},{-1,1},{1,-1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}
};
const vector_t king[SIZE_KING]={
    {1,1},{-1,1},{1,-1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1}
};