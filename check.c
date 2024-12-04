#include "check.h"
#include "constants.h"
#include "functions.h"
#include <string.h>
#include <stdio.h>

int other_side_piece_can_move_to_square(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    char temporary_start_pos[2];
    //if king is white
    if(board[start_row][start_column] == 'k'){
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                if(board[i][j] >= 'A' && board[i][j] <= 'Z'){
                    temporary_start_pos[0] = j + 'a' ; // Column character
                    temporary_start_pos[1] = '8' - i; // Row character
                    if(check_move(board, temporary_start_pos, end_pos)){
                        return TRUE;
                    }
                }
            }
        }
    }
    //if king is black
    if(board[start_row][start_column] == 'K'){
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                if(board[i][j] >= 'a' && board[i][j] <= 'z'){
                    start_pos[0] = j + 'a'; // Column character
                    start_pos[1] = '8' - i; // Row character
                    if(check_move(board, start_pos, end_pos)){
                        return TRUE;
                    }
                }
            }
        }
    }
    
    return FALSE;
}

