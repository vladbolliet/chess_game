#ifndef PIECE_IDENTIFIER_H
#define PIECE_IDENTIFIER_H
#include "constants.h" //for BOARD_SIZE

int piece_is_pawn(char piece);
int piece_is_rook(char piece);
int piece_is_knight(char piece);
int piece_is_bishop(char piece);
int piece_is_queen(char piece);
int piece_is_king(char piece);

#endif