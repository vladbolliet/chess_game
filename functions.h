#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "player.h"
#include "constants.h"

void random_choose_sides(struct player *player1, struct player *player2);
void move_piece(char (*board)[BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player);
int check_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player);
int everything_in_between_vertically_and_horizontally_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
int everything_in_between_diagonally_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
void initialize_players(player *player1, player *player2);


#endif