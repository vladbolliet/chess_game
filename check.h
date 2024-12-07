#ifndef CHECK_H
#define CHECK_H

#include "constants.h"
#include "player.h"

int other_side_piece_can_move_to_square(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player);
int piece_is_pinned(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], player *current_player, player *opponent_player);
//int king_is_in_check(char board[BOARD_SIZE][BOARD_SIZE], player *current_player, player *opponent_player);
int checkmate(char board[BOARD_SIZE][BOARD_SIZE], player *current_player, player *opponent_player);

#endif