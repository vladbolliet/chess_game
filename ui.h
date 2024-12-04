#ifndef UI_H
#define UI_H

#include <stdio.h>
#include "player.h"
#include "constants.h"

void welcome_message(player player1, player player2);
void ui(player player1, player player2, char board[BOARD_SIZE][BOARD_SIZE]);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void get_move(char start_pos[2], char end_pos[2]);

#endif