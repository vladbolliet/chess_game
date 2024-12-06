# Chess Game

Author: Vlad Bolliet

## Description

This is a simple chess game made in C. The game allows two players to play chess on a standard 8x8 board. The game includes functionality for moving pieces, checking the validity of moves, and displaying the board.

## Project Structure

The project consists of the following files:

- `chess.c`: The main entry point of the program.
- `constants.h`: Defines constants used throughout the program, such as board size and piece colors.
- `functions.c` and `functions.h`: Contains functions for game logic, such as moving pieces and checking move validity.
- `player.h`: Defines the `player` struct and related functions.
- `piece_identifier.c` and `piece_identifier.h`: Contains functions to identify different types of pieces on the board.
- `ui.c` and `ui.h`: Handles the user interface, including displaying the board and getting user input.
- `valid_moves.c` and `valid_moves.h`: Contains functions to validate moves based on chess rules.

## How It Works

### Main Program (`chess.c`)

The main program initializes the board and players, and then enters a loop where it repeatedly gets moves from the players, checks their validity, and updates the board.

### Constants (`constants.h`)

Defines constants such as:
- `BOARD_SIZE`: The size of the chess board (8x8).
- `WHITE` and `BLACK`: Represent the two sides.
- `EMPTY`: Represents an empty square on the board.
- `TRUE` and `FALSE`: Boolean values used for logic.

### Functions (`functions.c` and `functions.h`)

- `random_choose_sides`: Randomly assigns sides (white or black) to the players.
- `move_piece`: Moves a piece from the start position to the end position on the board.
- `check_move`: Checks if a move is valid based on the rules of chess.
- `everything_in_between_vertically_and_horizontally_is_empty`: Checks if all squares between two positions are empty.

### Player (`player.h`)

Defines the `player` struct, which includes:
- `name`: The name of the player.
- `side`: The side the player is playing (white or black).

### Piece Identifier (`piece_identifier.c` and `piece_identifier.h`)

Contains functions to identify different types of pieces on the board:
- `piece_is_knight`
- `piece_is_pawn`
- `piece_is_rook`
- `piece_is_bishop`
- `piece_is_queen`
- `piece_is_king`

### User Interface (`ui.c` and `ui.h`)

Handles the user interface:
- `welcome_message`: Displays a welcome message and gets player names.
- `ui`: Main UI function that runs the game loop.
- `print_board`: Prints the current state of the board.
- `get_move`: Gets a move from the player.

### Valid Moves (`valid_moves.c` and `valid_moves.h`)

Contains functions to validate moves:
- `starting_position_same_as_ending_position`: Checks if the starting position is the same as the ending position.
- `starting_or_ending_position_out_of_bounds`: Checks if the starting or ending position is out of bounds.
- `starting_position_is_empty`: Checks if the starting position is empty.

## How to Run

1. Compile the program using a C compiler (e.g., `gcc`).
2. Run the compiled executable.
3. Follow the on-screen instructions to play the game.

## Example

```sh
gcc -o chess [chess.c](http://_vscodecontentref_/2) [functions.c](http://_vscodecontentref_/3) [piece_identifier.c](http://_vscodecontentref_/4) [ui.c](http://_vscodecontentref_/5) [valid_moves.c](http://_vscodecontentref_/6)
./chess


//also make sure to include if the piece that you want to move is pinned
//also make sure to include if the king is in check
//also make sure to include if the king is in checkmate
//also make sure to include if the king is in stalemate

//also make sure to include if the pawn can be en passant
//player shouldn't be able to move piece from the other side