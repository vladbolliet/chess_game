#include <stdio.h>
#include "ui.h"
#include "player.h"
#include "constants.h"
#include "functions.h"


void ui(player player1, player player2, char board[BOARD_SIZE][BOARD_SIZE]){
       welcome_message(player1, player2);
       printf("\n");
       print_board(board);
       if(check_move(board, "a1", "g3") == TRUE){
        printf("Valid move\n");
       }
       else{
        printf("Invalid move\n");
       }
       print_board(board);
}

void welcome_message(player player1, player player2){
    printf("Welcome to the chess game!\n");
    printf("Who is playing? (give 2 names)\n");
    scanf("%s %s", player1.name, player2.name);
    if(player1.side == WHITE){
        printf("%s is white\n", player1.name);
        printf("%s is black\n", player2.name);
    } else {
        printf("%s is black\n", player1.name);
        printf("%s is white\n", player2.name);
    }
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]){
    for(int i = 0; i < BOARD_SIZE; i++){
        printf("\033[38;5;88m%d\033[0m ", 8 - i);
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int i = 0; i < BOARD_SIZE; i++){
        printf("\033[38;5;88m%c\033[0m ", i + 'A');
    }
    printf("\n");
}
