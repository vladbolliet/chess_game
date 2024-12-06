#include <stdio.h>
#include "ui.h"
#include "player.h"
#include "constants.h"
#include "functions.h"
#include "piece_identifier.h"
#include "check.h"
#include "valid_moves.h"

void ui(player *player1, player *player2, char board[BOARD_SIZE][BOARD_SIZE]){
    char start_pos[3], end_pos[3];
    initialize_players(player1, player2);
    welcome_message(player1, player2);
    printf("\n");
    if(player1->side == BLACK){ //decides who starts the game
        player *aux;
        aux = player1;
        player1 = player2;
        player2 = aux;
    }
    int start_row, start_column;
    while(1){
        //white player turn
        while(1){
            print_board(board);
            printf("UI : %s (white) turn\n", player1->name);
            get_move(start_pos, end_pos);
            start_row = BOARD_SIZE - (start_pos[1] - '0');
            start_column = start_pos[0] - 'a';
            if(board[start_row][start_column] >= 'A' && board[start_row][start_column] <= 'Z'){ //if the piece is not white
                printf("Invalid move, can't move other side piece\n");
            }
            else if(ending_position_is_occupied_by_same_side_piece(board, start_pos, end_pos)){
                printf("Invalid move, can't move to same side piece\n");
            }
            /*else if(king_is_in_check(board, player1, player2)){
                char temp_board[BOARD_SIZE][BOARD_SIZE];
                for(int i = 0; i < BOARD_SIZE; i++){
                    for(int j = 0; j < BOARD_SIZE; j++){
                        temp_board[i][j] = board[i][j];
                    }
                }
                move_piece(temp_board, start_pos, end_pos, player1);
                if(king_is_in_check(temp_board, player1, player2)){
                    printf("Invalid move, king is in check\n");
                }
            }*/ //the pinned piece function might be enough
            else if(check_move(board, start_pos, end_pos, player1, player2, 1)){
                move_piece(board, start_pos, end_pos, player1);
                break;
            } else {
                printf("Invalid move, try again\n");
            }
        }
        printf("DEBUG: last pieces moved by oppoennt: %c %d %d\n", player2->last_piece_moved, player2->last_move_start_row, player2->last_move_end_row);
        //black player turn
        while(1){
            print_board(board);
            printf("UI : %s (black) turn\n", player2->name);
            get_move(start_pos, end_pos);
            start_row = BOARD_SIZE - (start_pos[1] - '0');
            start_column = start_pos[0] - 'a';
            if(board[start_row][start_column] >= 'a' && board[start_row][start_column] <= 'z'){ //if the piece is not black
                printf("Invalid move, can't move other side piece\n");
            }
            /*else if(king_is_in_check(board, player2, player1)){
                char temp_board[BOARD_SIZE][BOARD_SIZE];
                for(int i = 0; i < BOARD_SIZE; i++){
                    for(int j = 0; j < BOARD_SIZE; j++){
                        temp_board[i][j] = board[i][j];
                    }
                }
                move_piece(temp_board, start_pos, end_pos, player2);
                if(king_is_in_check(temp_board, player2, player1)){
                    printf("Invalid move, king is in check\n");
                }
            }*/
            else if(check_move(board, start_pos, end_pos, player2, player1, 1)){
                move_piece(board, start_pos, end_pos, player2);
                break;
            } else {
                printf("Invalid move, try again\n");
            }
        }
        printf("DEBUG: last pieces moved by oppoennt: %c %d %d\n", player1->last_piece_moved, player1->last_move_start_row, player1->last_move_end_row);
    }
    printf("Game over\n");
}

void welcome_message(player *player1, player *player2){
    printf("Welcome to the chess game!\n");
    printf("Who is playing? (give 2 names)\n");
    scanf("%s %s", player1->name, player2->name);
    if(player1->side == WHITE){
        printf("%s is white\n", player1->name);
        printf("%s is black\n", player2->name);
    } else {
        printf("%s is black\n", player1->name);
        printf("%s is white\n", player2->name);
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]){
    for(int i = 0; i < BOARD_SIZE; i++){
        // Print row numbers with reset color
        printf("\033[0m\033[38;5;88m%d\033[0m ", 8 - i);
        for(int j = 0; j < BOARD_SIZE; j++){
            if((i + j) % 2 == 0){ //setup board square color which next character will print along with
                printf("\033[48;5;94m");
            } else {
                printf("\033[48;5;208m");
            }
            // Print uppercase letters in black
            if(board[i][j] >= 'A' && board[i][j] <= 'Z'){
                printf("\033[30m%c \033[0m", board[i][j]);
            } else {
                printf("%c ", board[i][j]);
            }
        }
        // Reset color after each row
        printf("\033[0m\n");
    }
    // Print column letters with reset color
    printf("\033[0m  ");
    for(int i = 0; i < BOARD_SIZE; i++){
        printf("\033[38;5;88m%c\033[0m ", i + 'A');
    }
    printf("\033[0m\n");
}

void get_move(char start_pos[2], char end_pos[2]){
    printf("Enter your move: ");
    scanf("%2s %2s", start_pos, end_pos);
}