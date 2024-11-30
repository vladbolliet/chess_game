#include <stdio.h>
#include "ui.h"
#include "player.h"
#include "constants.h"
#include "functions.h"


void ui(player player1, player player2, char board[BOARD_SIZE][BOARD_SIZE]){
       welcome_message(player1, player2);

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