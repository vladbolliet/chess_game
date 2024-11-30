#include <stdio.h>
#include "functions.h" //functions
#include "constants.h" //constants
#include "player.h" //player
#include "ui.h" //ui
int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    player player1, player2;
    random_choose_sides(&player1, &player2);
    board_init(board);
    ui(player1, player2, board);
    return 0;
}
