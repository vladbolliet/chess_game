#include <time.h> //for srand
#include <stdlib.h> //for rand
#include <stdio.h> //for printf
#include "player.h" //for player struct
#include "constants.h" //for side constants
#include "check.h" //for someone_got_checkmated
#include "functions.h" //for linking
#include "valid_moves.h" //for tried_moving_an_opposite_side_piece
#include "piece_identifier.h" //for piece_is_pawn

//functions used in ui()

void welcome_screen(player *player1, player *player2) {
    printf("Welcome to the game of chess!\n");
    printf("Player 1, please enter your name: ");
    scanf("%s", player1->name);
    printf("Player 2, please enter your name: ");
    scanf("%s", player2->name);
    printf("\nPlayer 1: %s, you are playing as %s\n", player1->name, player1->side == WHITE ? "WHITE" : "BLACK");
    printf("Player 2: %s, you are playing as %s\n", player2->name, player2->side == WHITE ? "WHITE" : "BLACK");
    printf("\nLet the game begin!\n\n");
}

void switch_players(player **player1, player **player2) {
    player *temp = *player1;
    *player1 = *player2;
    *player2 = temp;
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

void get_move(char *start_pos, char *end_pos, int side, player *current_player){ //get move from user
    if(side == WHITE) { printf("%s (WHITE) please enter your move: ", current_player->name); }
    else { printf("%s (BLACK) please enter your move: ", current_player->name); }
    scanf("%2s %2s", start_pos, end_pos);
}

void move_piece(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column){
    board[end_row][end_column] = board[start_row][start_column];
    board[start_row][start_column] = EMPTY;
}

//MAIN UI FUNCTION

void ui(player *player1, player *player2, char board[BOARD_SIZE][BOARD_SIZE]){ //main user interface
    welcome_screen(player1, player2); //player1 and player2 are pointers, so no need to use & operator
    if(player1->side == BLACK){switch_players(&player1, &player2);} //if player1 is black, switch the players, so white player will start
    char start_pos[3], end_pos[3]; //2 for characters, 1 for null character
    
    while(1){ //0 if false, 2 if WHITE got checkmated, 3 if BLACK got checkmated
        //white's turn
        if(someone_got_checkmated(board) == WHITE){
            print_board(board);
            printf("Checkmate! %s (BLACK) wins!\n", player2->name);
            break;
        }
        else if(someone_got_checkmated(board) == WHITE_STALEMATE){
            print_board(board);
            printf("Stalemate! It is a draw!\n");
            break;
        }
        while(1){
            print_board(board);
            get_move(start_pos, end_pos, WHITE, player1); //passing player1 for the name
            int start_row = BOARD_SIZE - (start_pos[1] - '0');
            int start_column = start_pos[0] - 'a';
            int end_row = BOARD_SIZE - (end_pos[1] - '0');
            int end_column = end_pos[0] - 'a';
            if(tried_moving_an_opposite_side_piece(board, start_row, start_column, WHITE)){
                printf("Move is not valid ; can't move piece from other side\n");
                continue;
            }
            //check en passant ; we do it here and not in valid_pawn_move function so we don't have to pass around last_move_parameters throughout functions
            else if(board[start_row][start_column]=='p' && valid_en_passant(board, start_row, start_column, end_row, end_column, player2->last_start_row, player2->last_start_column, player2->last_end_row, player2->last_end_column)) {
                board[player2->last_end_row][player2->last_end_column] = EMPTY;
                goto move_white_piece_tag;
            }

            //castling (we do it here because here's where we keep track of king and rook moves)
            else if(can_castle(board, start_row, start_column, end_row, end_column, player1->king_moved, player1->rook_a_moved, player1->rook_h_moved, WHITE)){
                if(start_row == 7 && start_column == 4 && end_row == 7 && end_column == 6){ //white king side castle
                    move_piece(board, 7, 7, 7, 5);
                    goto move_white_piece_tag;
                }
                else if(start_row == 7 && start_column == 4 && end_row == 7 && end_column == 2){ //white queen side castle
                    move_piece(board, 7, 0, 7, 3);
                    goto move_white_piece_tag;
                }
            }
            //check if normal move is invalid
            else if(valid_move(board, start_row, start_column, end_row, end_column, TRUE) == FALSE){
                printf("Move is not valid\n");
                continue;
            }
            else{
                //pawn promotion
                if(board[start_row][start_column] == 'p' && end_row == 0){
                    char piece;
                    while(1){
                        printf("Enter the piece you want to promote to (q,r,n,b): ");
                        scanf(" %c", &piece);
                        if(piece == 'q' || piece == 'Q' || piece == 'r' || piece == 'R' || piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N'){
                            if(is_upper(piece)){ board[start_row][start_column] = piece + 32; } //convert to lowercase
                            else{ board[start_row][start_column] = piece; }
                            break;
                        }
                        else{
                            printf("Invalid piece\n");
                        }
                    }
                }
                move_white_piece_tag:
                move_piece(board, start_row, start_column, end_row, end_column);
                //update last move parameters for en passant
                player1->last_start_row = start_row;
                player1->last_start_column = start_column;
                player1->last_end_row = end_row;
                player1->last_end_column = end_column;
                //update castling parameters
                if(board[end_row][end_column] == 'k'){ player1->king_moved = TRUE; }
                else if(board[end_row][end_column] == 'r' && start_row == 7 && start_column == 0){ player1->rook_a_moved = TRUE; }
                else if(board[end_row][end_column] == 'r' && start_row == 7 && start_column == 7){ player1->rook_h_moved = TRUE; }
                break;
            }
        }
        //black's turn
        if(someone_got_checkmated(board) == BLACK){
            print_board(board);
            printf("Checkmate! %s (WHITE) wins!\n", player1->name);
            break;
        }
        else if(someone_got_checkmated(board) ==BLACK_STALEMATE){
            print_board(board);
            printf("Stalemate! It is a draw!\n");
            break;
        }
        while(1){
            print_board(board);
            get_move(start_pos, end_pos, BLACK, player2); //passing player2 for the name
            int start_row = BOARD_SIZE - (start_pos[1] - '0');
            int start_column = start_pos[0] - 'a';
            int end_row = BOARD_SIZE - (end_pos[1] - '0');
            int end_column = end_pos[0] - 'a';
            if(tried_moving_an_opposite_side_piece(board, start_row, start_column, BLACK)){
                printf("Move is not valid ; can't move piece from other side\n");
                continue;
            }
            //check en passant ; we do it here and not in valid_pawn_move function so we don't have to pass around last_move_parameters throughout functions
            else if(board[start_row][start_column]=='P' && valid_en_passant(board, start_row, start_column, end_row, end_column, player1->last_start_row, player1->last_start_column, player1->last_end_row, player1->last_end_column)) {
                board[player1->last_end_row][player1->last_end_column] = EMPTY;
                goto move_black_piece_tag;
            }
            //castling (we do it here because here's where we keep track of king and rook moves)
            else if(can_castle(board, start_row, start_column, end_row, end_column, player2->king_moved, player2->rook_a_moved, player2->rook_h_moved, BLACK)){
                if(start_row == 0 && start_column == 4 && end_row == 0 && end_column == 6){ //black king side castle
                    move_piece(board, 0, 7, 0, 5);
                    goto move_black_piece_tag;
                }
                else if(start_row == 0 && start_column == 4 && end_row == 0 && end_column == 2){ //black queen side castle
                    move_piece(board, 0, 0, 0, 3);
                    goto move_black_piece_tag;
                }
            }
            //check if normal move is invalid
            else if(valid_move(board, start_row, start_column, end_row, end_column, TRUE) == FALSE){
                printf("Move is not valid\n");
                continue;
            }
            else{
                //pawn promotion
                if(board[start_row][start_column] == 'P' && end_row == 7){
                    char piece;
                    while(1){
                        printf("Enter the piece you want to promote to (q,r,n,b): ");
                        scanf(" %c", &piece);
                        if(piece == 'q' || piece == 'Q' || piece == 'r' || piece == 'R' || piece == 'b' || piece == 'B' || piece == 'n' || piece == 'N'){
                            if(is_lower(piece)){ board[start_row][start_column] = piece - 32; } //convert to uppercase
                            else{ board[start_row][start_column] = piece; }
                            break;
                        }
                        else{
                            printf("Invalid piece\n");
                        }
                    }
                }
                move_black_piece_tag:
                move_piece(board, start_row, start_column, end_row, end_column);
                //update last move parameters for en passant
                player2->last_start_row = start_row;
                player2->last_start_column = start_column;
                player2->last_end_row = end_row;
                player2->last_end_column = end_column;
                //update castling parameters
                if(board[end_row][end_column] == 'K'){ player1->king_moved = TRUE; }
                else if(board[end_row][end_column] == 'R' && start_row == 0 && start_column == 0){ player1->rook_a_moved = TRUE; }
                else if(board[end_row][end_column] == 'R' && start_row == 0 && start_column == 7){ player1->rook_h_moved = TRUE; }
                break;
            }
        }
    }
    
}

//functions used in chess.c

void random_choose_sides(player *player1, player *player2) { //randomly choose the side of each player
    srand(time(NULL));
    int random_number = rand() % 2; //random number will be either 0 and 1
    if (random_number == 0) {
        player1->side = WHITE;
        player2->side = BLACK;
    }
    else {
        player1->side = BLACK;
        player2->side = WHITE;
    }
}

void initialize_players(player *player1, player *player2) { //for castling
    player1->king_moved = FALSE;
    player1->rook_a_moved = FALSE;
    player1->rook_h_moved = FALSE;
    player2->king_moved = FALSE;
    player2->rook_a_moved = FALSE;
    player2->rook_h_moved = FALSE;
    player1->last_start_row = -1;
    player1->last_start_column = -1;
    player1->last_end_row = -1;
    player1->last_end_column = -1;
    player2->last_start_row = -1;
    player2->last_start_column = -1;
    player2->last_end_row = -1;
    player2->last_end_column = -1;
}

//functions used in valid_moves.c

int is_upper(char c){
    if(c >= 'A' && c <= 'Z'){return TRUE;}
    return FALSE;
}

int is_lower(char c){
    if(c >= 'a' && c <= 'z'){return TRUE;}
    return FALSE;
}