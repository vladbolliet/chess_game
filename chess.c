#include <stdio.h>
#include "functions.h" //functions
#include "constants.h" //constants
#include "player.h" //player
#include "ui.h" //ui

int main() {
    char board[BOARD_SIZE][BOARD_SIZE] =
    {   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {EMPTY, 'K', EMPTY, 'B', EMPTY, EMPTY, EMPTY, 'N'},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 'r', EMPTY},
        {'b', EMPTY, EMPTY, 'n', EMPTY, EMPTY, EMPTY, EMPTY},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };
    player player1, player2;
    random_choose_sides(&player1, &player2);
    ui(player1, player2, board);
    return 0;
}
