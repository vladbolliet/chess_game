#include "valid_moves.h"
#include "constants.h"
#include "functions.h"
#include "check.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int starting_position_same_as_ending_position(char start_pos[2], char end_pos[2]){
    if(strcmp(start_pos, end_pos) == 0){
        return TRUE;
    }
    return FALSE;
}

int starting_or_ending_position_out_of_bounds(char start_pos[2], char end_pos[2]){
    if(start_pos[0] < 'a' || start_pos[0] > 'h' || start_pos[1] < '1' || start_pos[1] > '8' || end_pos[0] < 'a' || end_pos[0] > 'h' || end_pos[1] < '1' || end_pos[1] > '8'){
        return TRUE;
    }
    return FALSE;
}

int starting_position_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    if(board[start_row][start_column] == EMPTY){
        return TRUE;
    }
    return FALSE;
}

int ending_position_is_occupied_by_same_side_piece(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int end_column = end_pos[0] - 'a';
    if ((board[start_row][start_column] >= 'a' && board[start_row][start_column] <= 'z' && board[end_row][end_column] >= 'a' && board[end_row][end_column] <= 'z')
     || (board[start_row][start_column] >= 'A' && board[start_row][start_column] <= 'Z' && board[end_row][end_column] >= 'A' && board[end_row][end_column] <= 'Z'))
    {
        return TRUE;
    }
    return FALSE;
}

int valid_knight_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if((abs(start_pos[0] - end_pos[0]) == 2 && abs(start_pos[1] - end_pos[1]) == 1) || (abs(start_pos[0] - end_pos[0]) == 1 && abs(start_pos[1] - end_pos[1]) == 2)){
        return TRUE;
    }
    return FALSE;
}

int valid_pawn_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_column = end_pos[0] - 'a';

    //forward pawn move
    if(start_column == end_column){
        //pawn moves 2 squares
        if(start_row == 6 && end_row == 4 && board[5][start_column] == EMPTY){ //white
            return TRUE;
        }
        if(start_row == 1 && end_row == 3 && board[2][start_column] == EMPTY){ //black
            return TRUE;
        }
        //pawn moves 1 square
        if(start_row + 1 == end_row && board[end_row][end_column] == EMPTY){ //white
            return TRUE;
        }
        if(start_row - 1 == end_row && board[end_row][end_column] == EMPTY){ //black
            return TRUE;
        }
    }

    //diagonal pawn move
    if(end_row - start_row == -1 && board[end_row][end_column] >= 'A' && board[end_row][end_column] <= 'Z'){ //for white pawn
        return TRUE;
    }
    if(end_row - start_row == 1 && board[end_row][end_column] >= 'a' && board[end_row][end_column] <= 'z'){ //for black pawn
        return TRUE;
    }
    return FALSE;
}

int valid_rook_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if((start_pos[0] == end_pos[0] || start_pos[1] == end_pos[1]) && everything_in_between_vertically_and_horizontally_is_empty(board, start_pos, end_pos)){
        return TRUE;
    }
    return FALSE;
}

int valid_bishop_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if(abs(start_pos[0] - end_pos[0]) == abs(start_pos[1] - end_pos[1]) && everything_in_between_diagonally_is_empty(board, start_pos, end_pos)){
        return TRUE;
    }
    return FALSE;
}

int valid_queen_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if(valid_rook_move(board, start_pos, end_pos) || valid_bishop_move(board, start_pos, end_pos)){
        return TRUE;
    }
    return FALSE;
}

int valid_king_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){

    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_column = end_pos[0] - 'a'; 

    //king moves 1 square at a time

    if(abs(start_column - end_column) > 1 || abs(start_row - end_row) > 1){
        return FALSE;
    }

    //if opposing piece is attacking square where king wants to move

    char temporary_start_pos[2], temporary_end_pos[2];
    strcpy(temporary_end_pos, end_pos);
    strcpy(temporary_start_pos, start_pos);
    if(other_side_piece_can_move_to_square(board, temporary_start_pos, temporary_end_pos)){
        return FALSE;
    }

    //castling

    
    
    return TRUE;
}



//also make sure to include if the piece that you want to move is pinned
//also make sure to include if the king is in check
//also make sure to include if the king is in checkmate
//also make sure to include if the king is in stalemate

//also make sure to include if the pawn can be promoted
//also make sure to include if the pawn can be en passant
//also make sure to include if the king can castle
