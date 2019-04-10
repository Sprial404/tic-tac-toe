#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#define GRID_SIZE 3

#define FALSE 0
#define TRUE !FALSE

#define X_POINT +1
#define O_POINT -1

typedef enum {
    EMPTY,
    X,
    O
} Piece;
const char PIECE_CHARS[3];

typedef struct {
    int row[GRID_SIZE];
    int col[GRID_SIZE];
    int diag;
    int diag2;
} Score;

typedef Piece Board[GRID_SIZE][GRID_SIZE];

/* Play tic tac toe */
void play_game(void);

/* 
 * Check whether the move is within the bounds. 
 * Returns TRUE if the row and col is within the bounds
 */
int is_valid_move(size_t row, size_t col);

/* Input a valid move from the user */
void input_move(size_t* row, size_t* col);

/* 
 * Check the player's move and move their piece on the board.
 * Returns TRUE if the move occurred.
 */
int make_move(Board board, Piece player, size_t row, size_t col);

/* Update the score based of the player's move */
void update_score(Piece player, size_t row, size_t col, Score* score);

/*
 * Check if any score equals GRID_SIZE
 * Returns TRUE if a player won
 */
int check_score(size_t row, size_t col, Score score);

/* Initialize the board array with EMPTY */
void init_board(Board board);

/* Print the board to the screen */
void print_board(Board board);

#endif
