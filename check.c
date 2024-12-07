#include "check.h"
#include "constants.h"
#include "functions.h"
#include "player.h"
#include "valid_moves.h"
#include <string.h>
#include <stdio.h>

int other_side_piece_can_move_to_square(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player){
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int end_column = end_pos[0] - 'a';
    char temporary_start_pos[2];
    char temp_board[BOARD_SIZE][BOARD_SIZE];
    for(int i=0; i<BOARD_SIZE; i++){for(int j=0; j<BOARD_SIZE; j++){temp_board[i][j]=board[i][j];}} // copy board
    temp_board[end_row][end_column] = temp_board[start_row][start_column];
    temp_board[start_row][start_column] = EMPTY;
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
                    /* if is pawn and valid pawn move returned 3 (diagonal), return TRUE ; else return false */
                    if(board[i][j]=='P'){                        
                        if(valid_pawn_move(temp_board, temporary_start_pos, end_pos, current_player, opponent_player)==3){
                            printf("DEBUG: pawn Move is valid so returned true\n");
                            return TRUE;
                        }
                    }
                    else if(check_move(board, temporary_start_pos, end_pos, current_player, opponent_player, 0)){
                        printf("DEBUG: g Move is valid so returned true\n");
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
                     if(board[i][j]=='p'){
                        if(valid_pawn_move(board, temporary_start_pos, end_pos, current_player, opponent_player)==3){
                            printf("DEBUG: pawn Move is valid so returned true\n");
                            return TRUE;
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else if(check_move(board, temporary_start_pos, end_pos, current_player, opponent_player, 0)){
                        printf("DEBUG: Move is valid so returned true\n");
                        return TRUE;
                    }
                    else{
                        printf("DEBUG: Move is invalid\n");
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
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    if(board[start_row][start_column] == 'k' || board[start_row][start_column] == 'K'){
        printf("DEBUG: Piece is king so can't be pinned\n");
        return FALSE;
    }
    printf("DEBUG: Checking if %c is pinned\n", board[start_row][start_column]);
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
    
    temp_board[start_row][start_column] = EMPTY;
    if(other_side_piece_can_move_to_square(temp_board, king_pos, king_pos, current_player, opponent_player)){
        printf("DEBUG: Piece is pinned\n");
        return TRUE;
    }
    printf("DEBUG: Piece is not pinned\n");
    return FALSE;
}

/*int king_is_in_check(char board[BOARD_SIZE][BOARD_SIZE], player *current_player, player *opponent_player){
    char king_pos[2];
    int king_row, king_column;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
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
    king_pos[0] = king_column + 'a';
    king_pos[1] = '8' - king_row;
    printf("DEBUG: King position is %c%c\n", king_pos[0], king_pos[1]);
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(opponent_player->side == WHITE && board[i][j] >= 'A' && board[i][j] <= 'Z'){
                char start_pos[2] = {j + 'a', '8' - i};
                if(check_move(board, start_pos, king_pos, opponent_player, current_player)){
                    printf("DEBUG: King is in check\n");
                    return TRUE;
                }
            }
            else if(opponent_player->side == BLACK && board[i][j] >= 'a' && board[i][j] <= 'z'){
                char start_pos[2] = {j + 'a', '8' - i};
                if(check_move(board, start_pos, king_pos, opponent_player, current_player)){
                    printf("DEBUG: King is in check\n");
                    return TRUE;
                }
            }
        }
    }
    printf("DEBUG: King is not in check\n");
    return FALSE;
}*/

/*int checkmate(char board[BOARD_SIZE][BOARD_SIZE], player *current_player, player *opponent_player) {
    char king_pos[2];
    int king_row = -1, king_column = -1;
    int attacking_pieces[BOARD_SIZE * BOARD_SIZE][2]; // To store positions of attacking pieces
    int num_attacking_pieces = 0;

    // Find the king's position
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((current_player->side == WHITE && board[i][j] == 'K') || 
                (current_player->side == BLACK && board[i][j] == 'k')) {
                king_row = i;
                king_column = j;
                break;
            }
        }
        if (king_row != -1) break;
    }

    if (king_row == -1 || king_column == -1) {
        printf("DEBUG: King not found on the board\n");
        return FALSE; // King not found, should not happen in a valid game
    }

    king_pos[0] = king_column + 'a';
    king_pos[1] = '8' - king_row;
    printf("DEBUG: King position is %c%c\n", king_pos[0], king_pos[1]);

    // Check if the king can move to a safe square
    char king_moves[8][2] = {
        {king_pos[0], king_pos[1] + 1}, {king_pos[0] + 1, king_pos[1] + 1}, {king_pos[0] + 1, king_pos[1]},
        {king_pos[0] + 1, king_pos[1] - 1}, {king_pos[0], king_pos[1] - 1}, {king_pos[0] - 1, king_pos[1] - 1},
        {king_pos[0] - 1, king_pos[1]}, {king_pos[0] - 1, king_pos[1] + 1}
    };

    for (int i = 0; i < 8; i++) {
        if (check_move(board, king_pos, king_moves[i], current_player, opponent_player)) {
            printf("DEBUG: King can move to %c%c\n", king_moves[i][0], king_moves[i][1]);
            return FALSE;
        }
    }

    // Identify attacking pieces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char pos[2] = {j + 'a', '8' - i};
            if (check_move(board, pos, king_pos, opponent_player, current_player)) {
                attacking_pieces[num_attacking_pieces][0] = i;
                attacking_pieces[num_attacking_pieces][1] = j;
                num_attacking_pieces++;
            }
        }
    }

    // Check if any piece can capture the attacking piece
    for (int k = 0; k < num_attacking_pieces; k++) {
        int attack_row = attacking_pieces[k][0];
        int attack_column = attacking_pieces[k][1];
        char attack_pos[2] = {attack_column + 'a', '8' - attack_row};
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                char pos[2] = {j + 'a', '8' - i};
                if (board[i][j] != EMPTY && board[i][j] != 'K' && board[i][j] != 'k' && 
                    check_move(board, pos, attack_pos, current_player, opponent_player)) {
                    printf("DEBUG: Piece at %c%c can capture attacking piece at %c%c\n", pos[0], pos[1], attack_pos[0], attack_pos[1]);
                    return FALSE;
                }
            }
        }
    }

    // Check if any piece can block the check
    for (int k = 0; k < num_attacking_pieces; k++) {
        int attack_row = attacking_pieces[k][0];
        int attack_column = attacking_pieces[k][1];
        char attack_pos[2] = {attack_column + 'a', '8' - attack_row};
        if (board[attack_row][attack_column] == 'R' || board[attack_row][attack_column] == 'r' ||
            board[attack_row][attack_column] == 'B' || board[attack_row][attack_column] == 'b' ||
            board[attack_row][attack_column] == 'Q' || board[attack_row][attack_column] == 'q') {
            int row_step = (attack_row > king_row) ? -1 : 1;
            int col_step = (attack_column > king_column) ? -1 : 1;
            if (attack_row == king_row) row_step = 0;
            if (attack_column == king_column) col_step = 0;
            for (int i = king_row + row_step, j = king_column + col_step; i != attack_row || j != attack_column; i += row_step, j += col_step) {
                char block_pos[2] = {j + 'a', '8' - i};
                for (int m = 0; m < BOARD_SIZE; m++) {
                    for (int n = 0; n < BOARD_SIZE; n++) {
                        char pos[2] = {n + 'a', '8' - m};
                        if (board[m][n] != EMPTY && board[m][n] != 'K' && board[m][n] != 'k' && 
                            check_move(board, pos, block_pos, current_player, opponent_player)) {
                            printf("DEBUG: Piece at %c%c can block check at %c%c\n", pos[0], pos[1], block_pos[0], block_pos[1]);
                            return FALSE;
                        }
                    }
                }
            }
        }
    }

    return TRUE; // Checkmate
}*/