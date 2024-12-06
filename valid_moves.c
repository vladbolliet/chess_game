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

#include <stdio.h>

int valid_pawn_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player) {
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_column = end_pos[0] - 'a';

    printf("DEBUG: Pawn move from %c%c to %c%c\n", start_pos[0], start_pos[1], end_pos[0], end_pos[1]);
    printf("DEBUG: start_row=%d, start_column=%d, end_row=%d, end_column=%d\n", start_row, start_column, end_row, end_column);
    
    // Forward pawn move
    if (start_column == end_column) {
        // Pawn moves 2 squares
        if (start_row == 6 && end_row == 4 && board[5][start_column] == EMPTY) { // White
            printf("DEBUG: Valid white pawn move - 2 squares\n");
            return TRUE;
        }
        if (start_row == 1 && end_row == 3 && board[2][start_column] == EMPTY) { // Black
            printf("DEBUG: Valid black pawn move - 2 squares\n");
            return TRUE;
        }
        // Pawn moves 1 square
        if (start_row - 1 == end_row && board[end_row][end_column] == EMPTY) { // White
            printf("DEBUG: Valid white pawn move - 1 square\n");
            return TRUE;
        }
        if (start_row + 1 == end_row && board[end_row][end_column] == EMPTY) { // Black
            printf("DEBUG: Valid black pawn move - 1 square\n");
            return TRUE;
        }
    }

    //en passant

    //white pawn en passant
    printf("DEBUG: inside valid_pawn_move ; DEBUG: last pieces moved by oppoennt: %c %d %d\n", opponent_player->last_piece_moved, opponent_player->last_move_start_row, opponent_player->last_move_end_row);
    if(start_row == 3 && end_row == 2 && abs(start_column - end_column) == 1 && 
       opponent_player->last_move_start_row == 1 && opponent_player->last_move_end_row == 3 &&
       opponent_player->last_piece_moved == 'P' && board[3][end_column] == 'P'){
            printf("DEBUG: Valid white pawn en passant\n");
            board[3][end_column] = EMPTY;
            return TRUE;
    }
    //black pawn en passant
    if(start_row == 4 && end_row == 5 && abs(start_column - end_column) == 1 && 
       opponent_player->last_move_start_row == 6 && opponent_player->last_move_end_row == 4 &&
       opponent_player->last_piece_moved == 'p' && board[4][end_column] == 'p'){
            printf("DEBUG: Valid black pawn en passant\n");
            board[4][end_column] = EMPTY;
            return TRUE;
       }
    
    // Diagonal pawn move
    if (start_row - end_row == 1 && abs(start_column - end_column) == 1 && board[end_row][end_column]>='A' &&
        board[end_row][end_column]<='Z') { // White pawn capturing
        printf("DEBUG: Valid white pawn capture\n");
        return TRUE;
    }
    if (start_row - end_row == -1 && abs(start_column - end_column) == 1 && board[end_row][end_column]>='a' &&
        board[end_row][end_column]<='z') { // Black pawn capturing
        printf("DEBUG: Valid black pawn capture\n");
        return TRUE;
    }
    
    printf("DEBUG: Invalid pawn move\n");
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

#include <stdio.h>

int valid_king_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player) {
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_column = end_pos[0] - 'a';

    printf("DEBUG: King move from %c%c to %c%c\n", start_pos[0], start_pos[1], end_pos[0], end_pos[1]);
    printf("DEBUG: start_row=%d, start_column=%d, end_row=%d, end_column=%d\n", start_row, start_column, end_row, end_column);

    // If opposing piece is attacking square where king wants to move
    if (other_side_piece_can_move_to_square(board, start_pos, end_pos, current_player, opponent_player)) {
        printf("DEBUG: Invalid king move - square under attack\n");
        return FALSE;
    }
    printf("DEBUG: before castling\n");
    // Castling
    if (current_player->king_moved == FALSE) {
        printf("DEBUG: King has not moved\n");
        printf("current player side: %d\n", current_player->side);
        // White king side castle
        if (current_player->side == WHITE && start_row == 7 && start_column == 4 && end_row == 7 && end_column == 6) {
            printf("DEBUG: Attempting white king side castle\n");
            if (current_player->rook_h_moved == FALSE) {
                if (board[7][5] == EMPTY && board[7][6] == EMPTY) {
                    if (!other_side_piece_can_move_to_square(board, start_pos, "f1", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "g1", current_player, opponent_player)) {
                        printf("DEBUG: White king side castle successful\n");
                        move_piece(board, "h1", "f1", current_player);
                        return TRUE;
                    } else {
                        printf("DEBUG: White king side castle failed - squares under attack\n");
                    }
                } else {
                    printf("DEBUG: White king side castle failed - squares not empty\n");
                }
            } else {
                printf("DEBUG: White king side castle failed - rook has moved\n");
            }
        }
        // White queen side castle
        if (current_player->side == WHITE && start_row == 7 && start_column == 4 && end_row == 7 && end_column == 2) {
            printf("DEBUG: Attempting white queen side castle\n");
            if (current_player->rook_a_moved == FALSE) {
                if (board[7][1] == EMPTY && board[7][2] == EMPTY && board[7][3] == EMPTY) {
                    if (!other_side_piece_can_move_to_square(board, start_pos, "b1", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "c1", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "d1", current_player, opponent_player)) {
                        printf("DEBUG: White queen side castle successful\n");
                        move_piece(board, "a1", "d1", current_player);
                        return TRUE;
                    } else {
                        printf("DEBUG: White queen side castle failed - squares under attack\n");
                    }
                } else {
                    printf("DEBUG: White queen side castle failed - squares not empty\n");
                }
            } else {
                printf("DEBUG: White queen side castle failed - rook has moved\n");
            }
        }
        // Black king side castle
        if (current_player->side == BLACK && start_row == 0 && start_column == 4 && end_row == 0 && end_column == 6) {
            printf("DEBUG: Attempting black king side castle\n");
            if (current_player->rook_h_moved == FALSE) {
                if (board[0][5] == EMPTY && board[0][6] == EMPTY) {
                    if (!other_side_piece_can_move_to_square(board, start_pos, "f8", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "g8", current_player, opponent_player)) {
                        printf("DEBUG: Black king side castle successful\n");
                        move_piece(board, "h8", "f8", current_player);
                        return TRUE;
                    } else {
                        printf("DEBUG: Black king side castle failed - squares under attack\n");
                    }
                } else {
                    printf("DEBUG: Black king side castle failed - squares not empty\n");
                }
            } else {
                printf("DEBUG: Black king side castle failed - rook has moved\n");
            }
        }
        // Black queen side castle
        if (current_player->side == BLACK && start_row == 0 && start_column == 4 && end_row == 0 && end_column == 2) {
            printf("DEBUG: Attempting black queen side castle\n");
            printf("current player side: %d\n", current_player->side);
            if (current_player->rook_a_moved == FALSE) {
                if (board[0][1] == EMPTY && board[0][2] == EMPTY && board[0][3] == EMPTY) {
                    if (!other_side_piece_can_move_to_square(board, start_pos, "b8", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "c8", current_player, opponent_player) &&
                        !other_side_piece_can_move_to_square(board, start_pos, "d8", current_player, opponent_player)) {
                        printf("DEBUG: Black queen side castle successful\n");
                        move_piece(board, "a8", "d8", current_player);
                        return TRUE;
                    } else {
                        printf("DEBUG: Black queen side castle failed - squares under attack\n");
                    }
                } else {
                    printf("DEBUG: Black queen side castle failed - squares not empty\n");
                }
            } else {
                printf("DEBUG: Black queen side castle failed - rook has moved\n");
            }
        }
        printf("DEBUG: went past all castling ifs\n");
    }

    // King moves 1 square at a time
    if (abs(start_column - end_column) > 1 || abs(start_row - end_row) > 1) {
        printf("DEBUG: Invalid king move - moving more than 1 square\n");
        return FALSE;
    }

    printf("DEBUG: Valid king move\n");
    return TRUE;
}

