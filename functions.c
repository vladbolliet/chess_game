#include <stdlib.h> //for random number generation
#include <stdio.h> //for printf
#include <time.h> //for time
#include "constants.h"
#include "player.h"
#include "functions.h"
#include "valid_moves.h"
#include "piece_identifier.h"

void random_choose_sides(player *player1, player *player2) { //randomly choose the side of each player
    srand(time(NULL));
    int random_number = rand() % 2;
    if (random_number == 0) {
        player1->side = WHITE;
        player2->side = BLACK;
    } else {
        player1->side = BLACK;
        player2->side = WHITE;
    }
}

void move_piece(char (*board)[BOARD_SIZE], char start_pos[2], char end_pos[2]){
    int start_column = start_pos[0] - 'a';
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_column = end_pos[0] - 'a';
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    board[end_row][end_column] = board[start_row][start_column];
    board[start_row][start_column] = EMPTY;
}

int check_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    //basic cases
    if (starting_position_same_as_ending_position(start_pos, end_pos)){
        return FALSE;
    }
    if(starting_or_ending_position_out_of_bounds(start_pos, end_pos)){
        return FALSE;
    }
    if(starting_position_is_empty(board, start_pos)){
        return FALSE;
    }
    if(ending_position_is_occupied_by_same_side_piece(board, start_pos, end_pos)){
        return FALSE;
    }
    

    //piece specific cases
    if(piece_is_knight(board, start_pos) && !valid_knight_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_pawn(board, start_pos) && !valid_pawn_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_rook(board, start_pos) && !valid_rook_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_bishop(board, start_pos) && !valid_bishop_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_queen(board, start_pos) && !valid_queen_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_king(board, start_pos) && !valid_king_move(board, start_pos, end_pos)){
        return FALSE;
    }

    return TRUE;
}

int everything_in_between_vertically_and_horizontally_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    if(start_pos[0] == end_pos[0]){ //if the move is vertical
        if(start_pos[1] < end_pos[1]){ //if the move is upwards
            for(int i = start_pos[1] - '0' + 1; i < end_pos[1] - '0'; i++){
                if(board[BOARD_SIZE - i][start_pos[0] - 'a'] != EMPTY){
                    return FALSE;
                }
            }
        } else { //if the move is downwards
            for(int i = end_pos[1] - '0' + 1; i < start_pos[1] - '0'; i++){
                if(board[BOARD_SIZE - i][start_pos[0] - 'a'] != EMPTY){
                    return FALSE;
                }
            }
        }
    }
    if(start_pos[1] == end_pos[1]){ //if the move is horizontal
        if(start_pos[0] < end_pos[0]){ //if the move is to the right
            for(int i = start_pos[0] - 'a' + 1; i < end_pos[0] - 'a'; i++){
                if(board[BOARD_SIZE - (start_pos[1] - '0')][i] != EMPTY){
                    return FALSE;
                }
            }
        } else { //if the move is to the left
            for(int i = end_pos[0] - 'a' + 1; i < start_pos[0] - 'a'; i++){
                if(board[BOARD_SIZE - (start_pos[1] - '0')][i] != EMPTY){
                    return FALSE;
                }
            }
        }
    }
}

int everything_in_between_diagonally_is_empty(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2]){
    int start_column = start_pos[0] - 'a';
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_column = end_pos[0] - 'a';
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    // Towards top right
    if (start_column < end_column && start_row > end_row) {
        for (int i = 1; i < abs(start_column - end_column); i++) {
            if (board[start_row - i][start_column + i] != EMPTY) {
                return FALSE;
            }
        }
    }
    // Towards bottom left
    if (start_column > end_column && start_row < end_row) {
        for (int i = 1; i < abs(start_column - end_column); i++) {
            if (board[start_row + i][start_column - i] != EMPTY) {
                return FALSE;
            }
        }
    }
    // Towards top left
    if (start_column > end_column && start_row > end_row) {
        for (int i = 1; i < abs(start_column - end_column); i++) {
            if (board[start_row - i][start_column - i] != EMPTY) {
                return FALSE;
            }
        }
    }
    // Towards bottom right
    if (start_column < end_column && start_row < end_row) {
        for (int i = 1; i < abs(start_column - end_column); i++) {
            if (board[start_row + i][start_column + i] != EMPTY) {
                return FALSE;
            }
        }
    }
    return TRUE;
}