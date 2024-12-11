#ifndef PLAYER_H
#define PLAYER_H

typedef struct player{
    char name[20];
    int side; //2 for white, 3 for black
    int king_moved; //for castling
    int rook_a_moved; //for castling
    int rook_h_moved; //for castling
    int last_start_row; //for en passant
    int last_start_column; //for en passant
    int last_end_row; //for en passant
    int last_end_column; //for en passant
} player;

#endif