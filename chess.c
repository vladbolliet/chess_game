#include <stdio.h>
#include "functions.h" //functions
#include "constants.h" //constants
#include "player.h" //player
#include "ui.h" //ui

int main() {
    char board[BOARD_SIZE][BOARD_SIZE] =
    {   {'R', EMPTY, EMPTY, EMPTY, 'K', EMPTY, EMPTY, 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 'N', EMPTY},
        {EMPTY, 'k', EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 'P', EMPTY, EMPTY},
        {'p', 'p', 'p', 'p', 'p', EMPTY, 'p', 'p'},
        {'r', EMPTY, EMPTY, EMPTY, 'k', EMPTY, EMPTY, 'r'}
    };
    player player1, player2;
    random_choose_sides(&player1, &player2);
    ui(&player1, &player2, board);
    return 0;
}
