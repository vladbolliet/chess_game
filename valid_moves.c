#include "valid_moves.h"
#include "constants.h"
#include <string.h>

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
    if(board[start_pos[1] - '1'][start_pos[0] - 'a'] == EMPTY){
        return TRUE;
    }
    return FALSE;
}

int ending_position_is_occupied_by_same_side_piece(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if ((board[start_pos[1] - '1'][start_pos[0] - 'a'] >= 'a' && board[start_pos[1] - '1'][start_pos[0] - 'a'] <= 'z' && board[end_pos[1] - '1'][end_pos[0] - 'a'] >= 'a' && board[end_pos[1] - '1'][end_pos[0] - 'a'] <= 'z')
     || (board[start_pos[1] - '1'][start_pos[0] - 'a'] >= 'A' && board[start_pos[1] - '1'][start_pos[0] - 'a'] <= 'Z' && board[end_pos[1] - '1'][end_pos[0] - 'a'] >= 'A' && board[end_pos[1] - '1'][end_pos[0] - 'a'] <= 'Z'))
    {
        return TRUE;
    }
    return FALSE;
}
