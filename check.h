#ifndef CHECK_H
#define CHECK_H
#include "constants.h" //for board size

int other_side_pieces_can_move_to_target(char board[BOARD_SIZE][BOARD_SIZE], int target_square_row, int target_square_column, int side_of_whos_calling, int pinned_flag);
int someone_got_checkmated(char board[BOARD_SIZE][BOARD_SIZE]);
int piece_is_pinned(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);

#endif