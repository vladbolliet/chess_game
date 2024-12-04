
#ifndef PLAYER_H
#define PLAYER_H

typedef struct player{
    char name[20];
    int side;
    int king_moved;
    int rook_a_moved;
    int rook_h_moved;
} player;

#endif