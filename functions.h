#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "player.h" //for player struct
#include "constants.h" //for board size constants

void welcome_screen(player *player1, player *player2); //welcome screen
void switch_players(player **player1, player **player2); //switch the players
void ui(player *player1, player *player2, char board[BOARD_SIZE][BOARD_SIZE]); //function prototype
void random_choose_sides(player *player1, player *player2); //randomly choose the side of each player
void initialize_players(player *player1, player *player2); //initialize the players for castling
void get_move(char *start_pos, char *end_pos, int side, player *current_player); //get the move from the player
void print_board(char board[BOARD_SIZE][BOARD_SIZE]); //print the board
void move_piece(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column); //move the piece
int is_upper(char c); //check if the character is uppercase
int is_lower(char c); //check if the character is lowercase

#endif