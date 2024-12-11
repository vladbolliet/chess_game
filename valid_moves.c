#include "valid_moves.h" //for linking
#include "constants.h" //for BOARD_SIZE
#include "piece_identifier.h" //for identifying pieces
#include "functions.h" //for is_upper and is_lower
#include "check.h" //for other_side_piece_can_move_to_target
#include <stdio.h> //for printf
#include <stdlib.h> //for abs

//functions used in ui() from functions.c

int tried_moving_an_opposite_side_piece(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int side){
    if(side == WHITE){
        if(board[start_row][start_column] >= 'A' && board[start_row][start_column] <= 'Z'){
            return TRUE;
        }
    }
    else{
        if(board[start_row][start_column] >= 'a' && board[start_row][start_column] <= 'z'){
            return TRUE;
        }
    }
    return FALSE;
}

int valid_en_passant(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int opponent_last_start_row, int opponent_last_start_column, int opponent_last_end_row, int opponent_last_end_column){
    //for white
    if(board[start_row][start_column] == 'p'){
        if(start_row == 3 && end_row == 2 && abs(start_column - end_column) == 1 && board[opponent_last_end_row][opponent_last_end_column] == 'P' && opponent_last_start_row == 1 && opponent_last_end_row == 3 && abs(start_column - opponent_last_start_column) ==1 ){
            return TRUE;
        }
    }
    //for black
    else if (board[start_row][start_column] == 'P'){
        if(start_row == 4 && end_row == 5 && abs(start_column - end_column) == 1 && board[opponent_last_end_row][opponent_last_end_column] == 'p' & opponent_last_start_row == 6 && opponent_last_end_row == 4 && abs(start_column - opponent_last_start_column) == 1){
            return TRUE;
        }
    }
    return FALSE;
}

int can_castle(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int king_moved, int rook_a_moved, int rook_h_moved, int side){
    if(king_moved == TRUE || (rook_a_moved == TRUE && rook_h_moved == TRUE)){
        printf("DEBUG: king or rook moved\n");
        return FALSE;
    }
    //white
    if(side == WHITE){
        //white king side castle
        if(start_row == 7 && start_column == 4 && end_row == 7 && end_column == 6 && board[7][5] == EMPTY && board[7][6] == EMPTY && rook_h_moved == FALSE && !other_side_pieces_can_move_to_target(board, 7, 5, WHITE, TRUE) && !other_side_pieces_can_move_to_target(board, 7, 6, WHITE, TRUE)){
            return TRUE;
        }
        //white queen side castle
        if(start_row == 7 && start_column == 4 && end_row == 7 && end_column == 2 && board[7][1] == EMPTY && board[7][2] == EMPTY && board[7][3] == EMPTY && rook_a_moved == FALSE && !other_side_pieces_can_move_to_target(board, 7, 1, WHITE, TRUE) && !other_side_pieces_can_move_to_target(board, 7, 2, WHITE, TRUE) && !other_side_pieces_can_move_to_target(board, 7, 3, WHITE, TRUE)){
            return TRUE;
        }
    }
    //black
    else{
        //black king side castle
        if(start_row == 0 && start_column == 4 && end_row == 0 && end_column == 6 && board[0][5] == EMPTY && board[0][6] == EMPTY && !other_side_pieces_can_move_to_target(board, 0, 5, BLACK, TRUE) && !other_side_pieces_can_move_to_target(board, 0, 6, BLACK, TRUE)){
            return TRUE;
        }
        //black queen side castle
        if(start_row == 0 && start_column == 4 && end_row == 0 && end_column == 2 && board[0][1] == EMPTY && board[0][2] == EMPTY && board[0][3] == EMPTY && !other_side_pieces_can_move_to_target(board, 0, 1, BLACK, TRUE) && !other_side_pieces_can_move_to_target(board, 0, 2, BLACK, TRUE) && !other_side_pieces_can_move_to_target(board, 0, 3, BLACK, TRUE)){
            return TRUE;
        }
    }
    return FALSE;
}

//tests used in valid_move()

int starting_or_ending_position_out_of_bounds(int start_row, int start_column, int end_row, int end_column){
    if(start_row < 0 || start_row >= BOARD_SIZE || start_column < 0 || start_column >= BOARD_SIZE
       || end_row < 0 || end_row >= BOARD_SIZE || end_column < 0 || end_column >= BOARD_SIZE){return TRUE;}
    return FALSE;
}

int ending_position_occupied_by_piece_from_same_side(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    if(board[start_row][start_column] >='a' && board[start_row][start_column] <= 'z' && 
       board[end_row][end_column] >='a' && board[end_row][end_column] <= 'z'){
        return TRUE;
    }
    if(board[start_row][start_column] >='A' && board[start_row][start_column] <= 'Z' && 
       board[end_row][end_column] >='A' && board[end_row][end_column] <= 'Z'){
        return TRUE;
    }
    return FALSE;
}

int valid_pawn_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    
    //pawn wants to move 2 squares forward
    //white
    if(is_lower(board[start_row][start_column]) && start_row == 6 && end_row == 4 && start_column == end_column && board[5][end_column] == EMPTY && board[4][end_column] == EMPTY){
        return TRUE;
    }
    //black
    else if(is_upper(board[start_row][start_column]) && start_row == 1 && end_row == 3 && start_column == end_column && board[2][end_column] == EMPTY && board[3][end_column] == EMPTY){
        return TRUE;
    }
    //pawn wants to move 1 square forward
    //white
    else if(is_lower(board[start_row][start_column]) && start_row - 1 == end_row && start_column == end_column && board[end_row][end_column] == EMPTY){
        return TRUE;
    }
    //black
    else if(is_upper(board[start_row][start_column]) && start_row + 1 == end_row && start_column == end_column && board[end_row][end_column] == EMPTY){
        return TRUE;
    }
    //pawn wants to capture
    //white
    else if(is_lower(board[start_row][start_column]) && start_row - 1 == end_row && abs(start_column - end_column) == 1 && is_upper(board[end_row][end_column])){
        return TRUE;
    }
    //black
    else if(is_upper(board[start_row][start_column]) && start_row + 1 == end_row && abs(start_column - end_column) == 1 && is_lower(board[end_row][end_column])){
        return TRUE;
    }
    //en passant

    //TO BE IMPLEMENTED

    return FALSE;
}   

int valid_rook_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    if(start_row != end_row && start_column != end_column){ //not a rook move
        return FALSE;
    }
    else if(start_row == end_row){ //horizontal move
        if(start_column < end_column){ //right
            for(int i = start_column + 1; i < end_column; i++){
                if(board[start_row][i] != EMPTY){
                    return FALSE;
                }
            }
        }
        else{ //left
            for(int i = start_column - 1; i > end_column; i--){
                if(board[start_row][i] != EMPTY){
                    return FALSE;
                }
            }
        }
    }
    else if(start_column == end_column){ //vertical move
        if(start_row < end_row){ //down
            for(int i = start_row + 1; i < end_row; i++){
                if(board[i][start_column] != EMPTY){
                    return FALSE;
                }
            }
        }
        else{ //up
            for(int i = start_row - 1; i > end_row; i--){
                if(board[i][start_column] != EMPTY){
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

int valid_knight_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    if((abs(start_row - end_row) == 2 && abs(start_column - end_column) == 1) || (abs(start_row - end_row) == 1 && abs(start_column - end_column) == 2)){
        return TRUE;
    }
    return FALSE;
}

int valid_bishop_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    if(abs(start_row - end_row) != abs(start_column - end_column)){ //not a bishop move
        return FALSE;
    }
    if(start_row < end_row && start_column < end_column){ //down right
        for(int i = 1; i < abs(start_row - end_row); i++){
            if(board[start_row + i][start_column + i] != EMPTY){
                return FALSE;
            }
        }
    }
    else if(start_row < end_row && start_column > end_column){ //down left
        for(int i = 1; i < abs(start_row - end_row); i++){
            if(board[start_row + i][start_column - i] != EMPTY){
                return FALSE;
            }
        }
    }
    else if(start_row > end_row && start_column < end_column){ //up right
        for(int i = 1; i < abs(start_row - end_row); i++){
            if(board[start_row - i][start_column + i] != EMPTY){
                return FALSE;
            }
        }
    }
    else if(start_row > end_row && start_column > end_column){ //up left
        for(int i = 1; i < abs(start_row - end_row); i++){
            if(board[start_row - i][start_column - i] != EMPTY){
                return FALSE;
            }
        }
    }
    return TRUE;
}

int valid_queen_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    if(valid_rook_move(board, start_row, start_column, end_row, end_column) || valid_bishop_move(board, start_row, start_column, end_row, end_column)){
        return TRUE;
    }
    return FALSE;
}

int valid_king_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    int side;
    //determine side of king
    if(is_lower(board[start_row][start_column])){
        side = WHITE;
    }
    else{
        side = BLACK;
    }

    //if opposing piece can move to target square, then king cannot move there
    if(other_side_pieces_can_move_to_target(board, end_row, end_column, side, FALSE)){
        return FALSE;
    }

    //king can move 1 square in any direction
    if(abs(start_row - end_row) > 1 || abs(start_column - end_column) > 1){
        return FALSE;
    }

    return TRUE;
}

//MAIN VALID_MOVE FUNCTION

int valid_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int pinned_flag){

    //verifying basic rules

    if(start_row == end_row && start_column == end_column){ //starting position same as ending position
        return FALSE;
    }
    if(starting_or_ending_position_out_of_bounds(start_row, start_column, end_row, end_column)){ //starting position out of bounds
        return FALSE;
    } 
    if(board[start_row][start_column] == EMPTY){ //starting position is empty
        return FALSE;
    } 
    if(ending_position_occupied_by_piece_from_same_side(board, start_row, start_column, end_row, end_column)){ //ending position occupied by piece from same side
        return FALSE;
    } 

    //chess specific rule verifications

    if(piece_is_pawn(board[start_row][start_column]) && !valid_pawn_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }
    if(piece_is_rook(board[start_row][start_column]) && !valid_rook_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }
    if(piece_is_knight(board[start_row][start_column]) && !valid_knight_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }
    if(piece_is_bishop(board[start_row][start_column]) && !valid_bishop_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }
    if(piece_is_queen(board[start_row][start_column]) && !valid_queen_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }
    
    if(piece_is_king(board[start_row][start_column]) && !valid_king_move(board, start_row, start_column, end_row, end_column)){
        return FALSE;
    }

    //pinned 
    if(piece_is_pinned(board, start_row, start_column, end_row, end_column) && pinned_flag == TRUE){
        return FALSE;
    }


    return TRUE;
}