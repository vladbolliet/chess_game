#include "check.h"
#include "constants.h"
#include "functions.h"
#include "player.h"
#include <string.h>
#include <stdio.h>

int other_side_piece_can_move_to_square(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    char temporary_start_pos[2];

    printf("DEBUG: Checking if other side piece can move to square %c%c\n", end_pos[0], end_pos[1]);

    // If king is white
    if(board[start_row][start_column] == 'k'){
        printf("DEBUG: King is white\n");
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                if(board[i][j] >= 'A' && board[i][j] <= 'Z' && board[i][j] != 'K'){
                    temporary_start_pos[0] = j + 'a'; // Column character
                    temporary_start_pos[1] = '8' - i; // Row character
                    printf("DEBUG: CHECKing move from %c%c to %c%c\n", temporary_start_pos[0], temporary_start_pos[1], end_pos[0], end_pos[1]);
                    if(check_move(board, temporary_start_pos, end_pos, current_player, opponent_player)){
                        printf("DEBUG: Move is valid\n");
                        return TRUE;
                    }
                    else{
                        printf("DEBUG: Move is invalid\n");
                    }
                }
            }
        }
    }

    // If king is black
    if(board[start_row][start_column] == 'K'){
        printf("DEBUG: King is black\n");
        for(int i = 0; i < BOARD_SIZE; i++){
            for(int j = 0; j < BOARD_SIZE; j++){
                if(board[i][j] >= 'a' && board[i][j] <= 'z' && board[i][j] != 'k'){
                    temporary_start_pos[0] = j + 'a'; // Column character
                    temporary_start_pos[1] = '8' - i; // Row character
                    printf("DEBUG: Checking move from %c%c to %c%c\n", temporary_start_pos[0], temporary_start_pos[1], end_pos[0], end_pos[1]);
                    if(check_move(board, temporary_start_pos, end_pos, opponent_player, current_player)){
                        printf("DEBUG: Move is valid\n");
                        return TRUE;
                    }
                }
            }
        }
    }

    printf("DEBUG: No valid moves found\n");
    return FALSE;
}

int piece_is_pinned(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], player *current_player, player *opponent_player){
    char temp_board[BOARD_SIZE][BOARD_SIZE];
    int king_row, king_column;
    printf("DEBUG: Checking if piece is pinned\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            temp_board[i][j] = board[i][j];
            if(current_player->side == WHITE && board[i][j] == 'k'){
                king_row = i;
                king_column = j;
            }
            else if(current_player->side == BLACK && board[i][j] == 'K'){
                king_row = i;
                king_column = j;
            }
        }
    }
    char king_pos[2] = {king_column + 'a', '8' - king_row};
    printf("DEBUG: King position is %c%c\n", king_pos[0], king_pos[1]);
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    temp_board[start_row][start_column] = EMPTY;
    if(other_side_piece_can_move_to_square(temp_board, king_pos, king_pos, current_player, opponent_player)){
        printf("DEBUG: Piece is pinned\n");
        return TRUE;
    }
    printf("DEBUG: Piece is not pinned\n");
    return FALSE;
}