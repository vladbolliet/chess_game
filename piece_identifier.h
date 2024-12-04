#ifndef PIECE_IDENTIFIER_H
#define PIECE_IDENTIFIER_H

#include "constants.h"

int piece_is_knight(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);
int piece_is_pawn(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);
int piece_is_rook(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);
int piece_is_bishop(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);
int piece_is_queen(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);
int piece_is_king(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]);

#endif