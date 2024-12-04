
#include "piece_identifier.h"
#include "constants.h"
#include <stdio.h>

int piece_is_knight(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'N' || board[row][col] == 'n'){
        return TRUE;
    }
    return FALSE;
}

int piece_is_pawn(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'P' || board[row][col] == 'p'){
        return TRUE;
    }
    
    return FALSE;
}

int piece_is_rook(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'R' || board[row][col] == 'r'){
        return TRUE;
    }
    return FALSE;
}

int piece_is_bishop(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'B' || board[row][col] == 'b'){
        return TRUE;
    }
    return FALSE;
}

int piece_is_queen(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'Q' || board[row][col] == 'q'){
        return TRUE;
    }
    return FALSE;
}

int piece_is_king(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2]){
    int row = BOARD_SIZE - (start_pos[1] - '0');
    int col = start_pos[0] - 'a';
    if(board[row][col] == 'K' || board[row][col] == 'k'){
        return TRUE;
    }
    return FALSE;
}