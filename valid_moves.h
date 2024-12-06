#ifndef VALID_MOVES_H
#define VALID_MOVES_H

#include "constants.h"
#include "player.h"

//starting position is same as ending position
int starting_position_same_as_ending_position(char start_pos[2], char end_pos[2]);

//starting or ending position is out of bounds
int starting_or_ending_position_out_of_bounds(char start_pos[2], char end_pos[2]);

//starting position is empty
int starting_position_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);

//ending position is occupied by a piece from the same side
int ending_position_is_occupied_by_same_side_piece(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);

//valid moves for each piece
int valid_knight_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
int valid_pawn_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player);
int valid_rook_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
int valid_bishop_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
int valid_queen_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]);
int valid_king_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player);

#endif