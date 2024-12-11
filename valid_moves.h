#ifndef VALID_MOVES_H
#define VALID_MOVES_H

#include "constants.h" //for BOARD_SIZE

int tried_moving_an_opposite_side_piece(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int side);
int valid_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int pinned_flag);
int starting_or_ending_position_out_of_bounds(int start_row, int start_column, int end_row, int end_column);
int ending_position_occupied_by_piece_from_same_side(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_en_passant(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int opponent_last_start_row, int opponent_last_start_column, int opponent_last_end_row, int opponent_last_end_column);
int valid_pawn_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_rook_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_knight_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_bishop_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_queen_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int valid_king_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
int can_castle(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int king_moved, int rook_a_moved, int rook_h_moved, int side);

#endif