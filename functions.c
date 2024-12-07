#include <stdlib.h> //for random number generation
#include <stdio.h> //for printf
#include <time.h> //for time
#include "constants.h"
#include "player.h"
#include "functions.h"
#include "valid_moves.h"
#include "piece_identifier.h"
#include "check.h"

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

void initialize_players(player *player1, player *player2) {
    player1->king_moved = FALSE;
    player1->rook_a_moved = FALSE;
    player1->rook_h_moved = FALSE;
    player2->king_moved = FALSE;
    player2->rook_a_moved = FALSE;
    player2->rook_h_moved = FALSE;
}

void move_piece(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player) {
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int end_column = end_pos[0] - 'a';

    char piece = board[start_row][start_column];

    // Move the piece
    board[end_row][end_column] = piece;
    board[start_row][start_column] = EMPTY;

    // pawn promotion

    if (piece == 'p' && end_row == 0 || piece == 'P' && end_row == 7) {
        while(1){
            printf("Choose a piece to promote to (q,r,n,b): ");
            char promotion_piece;
            scanf(" %c", &promotion_piece);
            if(promotion_piece != 'q' && promotion_piece != 'r' && promotion_piece != 'n' && promotion_piece != 'b'){
                printf("Invalid piece\n");
                continue;
            }
            if(current_player->side == WHITE){board[end_row][end_column] = promotion_piece;} //small leter
            else{board[end_row][end_column] = promotion_piece - 32;} //capital letter
            
            break;
        }
    }

    // Update flags
    if (piece == 'K' || piece == 'k') {
        current_player->king_moved = TRUE;
    } else if (piece == 'R' || piece == 'r') {
        if (start_column == 0) {
            current_player->rook_a_moved = TRUE;
        } else if (start_column == 7) {
            current_player->rook_h_moved = TRUE;
        }
    }
}

int check_move(char board[BOARD_SIZE][BOARD_SIZE], char start_pos[2], char end_pos[2], player *current_player, player *opponent_player, int pinned_flag) {
    //basic cases
    int start_row = BOARD_SIZE - (start_pos[1] - '0');
    int end_row = BOARD_SIZE - (end_pos[1] - '0');
    int start_column = start_pos[0] - 'a';
    int end_column = end_pos[0] - 'a';
    printf("1\n");
    if (starting_position_same_as_ending_position(start_pos, end_pos)){
        return FALSE;
    }
    printf("2\n");
    if(starting_or_ending_position_out_of_bounds(start_pos, end_pos)){
        printf("Invalid move, out of bounds\n");
        return FALSE;
    }
    printf("3\n");
    if(starting_position_is_empty(board, start_pos)){
        return FALSE;
    }
    printf("4\n");
        

    //piece specific cases
    if(piece_is_knight(board, start_pos) && !valid_knight_move(board, start_pos, end_pos)){
        return FALSE;
    }
    if(piece_is_pawn(board, start_pos) && !valid_pawn_move(board, start_pos, end_pos, current_player, opponent_player)){
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
    if(piece_is_king(board, start_pos) && !valid_king_move(board, start_pos, end_pos, current_player, opponent_player)){
        return FALSE;
    }

    printf("5\n");

    //check if piece is pinned
    if(pinned_flag && piece_is_pinned(board, start_pos, current_player, opponent_player)){
        return FALSE;
    }
    printf("6\n");

    // update last player's move for en passant
    current_player->last_move_start_row = start_row;
    current_player->last_move_end_row = end_row;
    current_player->last_piece_moved = board[start_row][start_column];
    // check if the king or rooks moved (for castling)
    if(board[start_row][start_column] == 'K' || board[start_row][start_column] == 'k'){current_player->king_moved = TRUE;}
    if((board[start_row][start_column] == 'R' || board[start_row][start_column] == 'r')){
        if(start_column == 0) current_player->rook_a_moved = TRUE;
        if(start_column == 7) current_player->rook_h_moved = TRUE;
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