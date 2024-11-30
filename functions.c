#include <stdlib.h> //for random number generation
#include <time.h> //for time
#include "constants.h"
#include "player.h"
#include "functions.h"

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

void board_init(char board[BOARD_SIZE][BOARD_SIZE]){
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(i == BOARD_SIZE - 1){
                board[i][j] = j + 'A';
            } else if(j == 0){
                board[i][j] = i + '0';
            } else {
                board[i][j] = ' ';
            }
        }
    }
}
