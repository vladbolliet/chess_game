#include <stdlib.h> //for random number generation
#include <stdio.h> //for printf
#include <time.h> //for time
#include "constants.h"
#include "player.h"
#include "functions.h"
#include "valid_moves.h"

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

    if (starting_position_same_as_ending_position(start_pos, end_pos)){return FALSE;}
    if(starting_or_ending_position_out_of_bounds(start_pos, end_pos)){return FALSE;}
    if(starting_position_is_empty(board, start_pos)){return FALSE;}
    if(ending_position_is_occupied_by_same_side_piece(board, start_pos, end_pos)){return FALSE;}

    //piece specific cases

    

    return TRUE;
}

