# Chess Game

This project is a simple console-based chess game implemented in C. It allows two players to play a game of chess with basic functionalities such as move validation, castling, en passant, and checkmate detection.

## Author

Vlad-Louis Bolliet

## How To Play

The white and black players will take turns, by typing a move made of the origin and the destination. For example,
```c
e2 e4
```

## How It Was Coded

The project is structured into multiple C files, each handling different aspects of the game. The main components include:

- **Main Game Logic**: The main game loop and user interface.
- **Move Validation**: Functions to validate the legality of moves.
- **Check and Checkmate Detection**: Functions to detect check and checkmate conditions.
- **Piece Identification**: Functions to identify different types of pieces.
- **Player Management**: Structures to manage player information.

## Important Functions

### `welcome_screen`

```c
void welcome_screen(player *player1, player *player2);
```

Displays the welcome screen and prompts players to enter their names.

### `get_move`

```c
void get_move(char *start_pos, char *end_pos, int side, player *current_player);
```

Prompts the current player to enter their move.

### `print_board`

```c
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
```

Prints the current state of the chessboard.

### `move_piece`

```c
void move_piece(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column);
```

Moves a piece from the start position to the end position on the board.

### `valid_move`

```c
int valid_move(char board[BOARD_SIZE][BOARD_SIZE], int start_row, int start_column, int end_row, int end_column, int pinned_flag);
```

Checks if a move is valid according to the rules of chess. This function is critical for the game functionality.

### `someone_got_checkmated`

```c
int someone_got_checkmated(char board[BOARD_SIZE][BOARD_SIZE]);
```

Checks if either player is in checkmate.

## How It Works

1. **Initialization**: The game initializes the board and players, randomly assigning sides.
2. **Game Loop**: The game enters a loop where players take turns making moves.
3. **Check and Checkmate**: The game checks for check and current checkmate conditions.
4. **Move Validation**: Each move is validated to ensure it follows the rules of chess.
5. **End Game**: The game ends when a player is checkmated or a stalemate is reached.

Enjoy playing this simple yet functional chess game!
