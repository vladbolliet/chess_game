#include <stdio.h> //for printf
#include "functions.h" //for random_choose_sides and initialize_players
#include "player.h" //for player struct
#include "constants.h" //for board size and empty square


int main() {
    char board[BOARD_SIZE][BOARD_SIZE] =
    {   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };
    player player1, player2;
    random_choose_sides(&player1, &player2); //randomly choose the side of each player
    initialize_players(&player1, &player2); //initialize the players for castling
    ui(&player1, &player2, board);
    return 0;
}
