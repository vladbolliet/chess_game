#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "player.h"
#include "constants.h"

void random_choose_sides(struct player *player1, struct player *player2);
void board_init(char board[BOARD_SIZE][BOARD_SIZE]);

#endif