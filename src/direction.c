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
const roque_data_t white_big_roque={
    .start_king={4,7},
    .end_king={2,7},

    .start_rook={0,7},
    .end_rook={3,7},

    .empty_case={{1,7},{2,7},{3,7}},
    .count_empty_case=3,

    .path_king={{4,7},{3,7},{2,7}},
    .count_path_king=3
};
const roque_data_t white_little_roque={
    .start_king={4,7},
    .end_king={6,7},

    .start_rook={7,7},
    .end_rook={5,7},

    .empty_case={{5,7},{6,7}},
    .count_empty_case=2,

    .path_king={{4,7},{5,7},{6,7}},
    .count_path_king=3
};
const roque_data_t black_big_roque={
    .start_king={4,0},
    .end_king={2,0},

    .start_rook={0,0},
    .end_rook={3,0},

    .empty_case={{1,0},{2,0},{3,0}},
    .count_empty_case=3,

    .path_king={{4,0},{3,0},{2,0}},
    .count_path_king=3
};
const roque_data_t black_little_roque={
    .start_king={4,0},
    .end_king={6,0},

    .start_rook={7,0},
    .end_rook={5,0},

    .empty_case={{5,0},{6,0}},
    .count_empty_case=2,

    .path_king={{4,0},{5,0},{6,0}},
    .count_path_king=3
};