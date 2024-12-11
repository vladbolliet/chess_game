#include "constants.h" //for board size
#include "check.h" //for linking
#include "functions.h" //for is_upper and is_lower and move_piece
#include "valid_moves.h" //for valid_move
#include <stdio.h> //for printf
#include <stdlib.h> //for abs
#include "piece_identifier.h" //for piece_is_pawn, piece_is_rook, piece_is_knight, piece_is_bishop, piece_is_queen

int other_side_pieces_can_move_to_target(char board[BOARD_SIZE][BOARD_SIZE], int target_square_row, int target_square_column, int side_of_whos_calling, int pinned_flag){
    //check validity for white's move, so looping through all black pieces
    if(side_of_whos_calling == WHITE){
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(is_upper(board[i][j]) && board[i][j] != 'K'){ //if piece is black and not king
                    if(valid_move(board, i, j, target_square_row, target_square_column, pinned_flag)){
                        return TRUE;
                    }
                }
                else if (board[i][j] == 'K'){ //if piece is black king
                    if(abs(i - target_square_row) <= 1 && abs(j - target_square_column) <= 1){
                        return TRUE;
                    }
                }
            }
        }
    }
    //check validity for black's move, so looping through all white pieces
    else{
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(is_lower(board[i][j]) && board[i][j]!='k'){
                    if(valid_move(board, i, j, target_square_row, target_square_column, pinned_flag)){
                        return TRUE;
                    }
                }
                else if (board[i][j] == 'k'){ //if piece is black king
                    if(abs(i - target_square_row) <= 1 && abs(j - target_square_column) <= 1){
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

int someone_got_checkmated(char board[BOARD_SIZE][BOARD_SIZE]) {
    //this function returns 0 if false, 2(WHITE constant) if white is checkmated, 3(BLACK constant) if black is checkmated
    int white_king_row, white_king_column, black_king_row, black_king_column;
    //find white king
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j] == 'k'){
                white_king_row = i;
                white_king_column = j;
            }
        }
    }
        
    //find black king
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j] == 'K'){
                black_king_row = i;
                black_king_column = j;
            }
        }
    }

    //check if white has been checkmated
    //check if king is in check right now
    //if(other_side_pieces_can_move_to_target(board, white_king_row, white_king_column, WHITE, FALSE)){
        //count how many valid moves there are
        int counter=0;
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(is_lower(board[i][j])){ //if piece is white
                    for(int k=0; k<BOARD_SIZE; k++){
                        for(int l=0; l<BOARD_SIZE; l++){
                            if(valid_move(board,i,j,k,l, TRUE)){
                                counter++;
                            }
                        }
                    }           
                }
            }
        }
        if(counter==0 && other_side_pieces_can_move_to_target(board, white_king_row, white_king_column, WHITE, FALSE)){
            //no valid moves for white
            return WHITE;
        }
        else if(counter==0){
            //white has no valid moves but isn't in check in the current position
            return WHITE_STALEMATE;
        }
    //}
    //check if black has been checkmated
    //check if king is in check right now
    //if(other_side_pieces_can_move_to_target(board, black_king_row, black_king_column, BLACK, FALSE)){
        //count how many valid moves there are
        counter=0;
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(is_upper(board[i][j])){ //if piece is black
                    for(int k=0; k<BOARD_SIZE; k++){
                        for(int l=0; l<BOARD_SIZE; l++){
                            if(valid_move(board,i,j,k,l,TRUE)){
                                counter++;
                            }
                        }
                    }           
                }
            }
        }
        if(counter==0 && other_side_pieces_can_move_to_target(board, black_king_row, black_king_column, BLACK, FALSE)){
            //no valid moves for black
            return BLACK;
        }
        else if(counter==0){
            //black has no valid moves but isn't in check in the current position
            return BLACK_STALEMATE;
        }
    //}

    return FALSE;
        
}

int piece_is_pinned(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    int side;
    //determine side of king (whose piece is moving)
    if(is_lower(board[start_row][start_column])){
        side = WHITE;
    }
    else{
        side = BLACK;
    }
    //simulate piece (from same side as king) moving, check if opposite side piece can attack king
    char temp_board[BOARD_SIZE][BOARD_SIZE];
    for(int i=0; i<BOARD_SIZE; i++){ //copy board
        for(int j=0; j<BOARD_SIZE; j++){
            temp_board[i][j] = board[i][j];
        }
    }
    move_piece(temp_board, start_row, start_column, end_row, end_column);
    int king_row, king_column;
    if(side == WHITE){ //find white king
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(temp_board[i][j] == 'k'){
                    king_row = i;
                    king_column = j;
                }
            }
        }
    }
    else{ //find black king
        for(int i=0; i<BOARD_SIZE; i++){
            for(int j=0; j<BOARD_SIZE; j++){
                if(temp_board[i][j] == 'K'){
                    king_row = i;
                    king_column = j;
                }
            }
        }
    }
    //check if opposite side pieces can move to king's position after the move
    if(other_side_pieces_can_move_to_target(temp_board, king_row, king_column, side, FALSE)){
        return TRUE;
    }

    return FALSE;
}

