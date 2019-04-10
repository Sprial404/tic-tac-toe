#include <stdio.h>
#include <stdlib.h>

#include "ansi.h"
#include "game.h"

const char PIECE_CHARS[3] = " XO";

void play_game(void)
{
    Board board;

    Piece winner = EMPTY;
    Piece player = X;

    Score score = {0};

    size_t row, col;
    int moves_left = GRID_SIZE * GRID_SIZE;

    init_board(board);

    do
    {
        /* print the board each turn */
        printf("\n" ANSI_COLOR_WHITE "-- Player %c's Turn --" ANSI_COLOR_RESET "\n", PIECE_CHARS[player]);
        print_board(board);

        input_move(&row, &col);
        if (make_move(board, player, row, col))
        {
            moves_left -= 1;
            update_score(player, row, col, &score); 

            if (check_score(row, col, score))
            {
                /* so that the winner can glot about their win */
                printf("\n" ANSI_COLOR_WHITE "-- Player %c Won --" ANSI_COLOR_RESET "\n", PIECE_CHARS[player]);
                print_board(board);
                winner = player;
            }

            /* switch to the next player */
            player = (player == X) ? O : X;
        }
    } while (moves_left != 0 && winner == EMPTY);

    if (winner == X)
    {
        printf(ANSI_COLOR_BLUE "Bamm! Seems like X won." ANSI_COLOR_RESET "\n");
    }
    else if (winner == O)
    {
        printf(ANSI_COLOR_RED "Whoopie! Look likes O won." ANSI_COLOR_RESET "\n");
    }
    else
    {
        printf(ANSI_COLOR_WHITE "Ahh, It's a draw!" ANSI_COLOR_RESET "\n");
    }
}

int is_valid_move(size_t row, size_t col)
{
    return (row >= 0 && row < GRID_SIZE) &&
        (col >= 0 && col < GRID_SIZE);
}

int make_move(Board board, Piece player, size_t row, size_t col)
{
    int valid = FALSE;

    if (board[row][col] == EMPTY && is_valid_move(row, col))
    {
        valid = TRUE;
        board[row][col] = player;
    }

    return valid;
}

void input_move(size_t* row, size_t* col)
{
    char buffer[10];
    int move = -1;

    do
    {
        printf("Enter a move (0-%d): ", GRID_SIZE * GRID_SIZE - 1);
        if (fgets(buffer, 10, stdin) != NULL)
        {
            move = atoi(buffer);
            *row = move / GRID_SIZE;
            *col = move % GRID_SIZE;
        }
    } while (!is_valid_move(*row, *col));
}

void update_score(Piece player, size_t row, size_t col, Score* score)
{
    int point = 0;

    if (player == X)
    {
        point = X_POINT;
    }

    if (player == O)
    {
        point = O_POINT;
    }

    score->row[row] += point;
    score->col[col] += point;
    if (row == col)
    {
        score->diag += point;
    }

    if (row + col == GRID_SIZE - 1)
    {
        score->diag2 += point;
    }
}

int check_score(size_t row, size_t col, Score score)
{
    return (abs(score.row[row]) == GRID_SIZE ||
            abs(score.col[col]) == GRID_SIZE ||
            abs(score.diag) == GRID_SIZE ||
            abs(score.diag2) == GRID_SIZE);
}

void init_board(Board board)
{
    int r, c;
    for (r = 0; r < GRID_SIZE; r++)
    {
        for (c = 0; c < GRID_SIZE; c++)
        {
            board[r][c] = EMPTY;
        }
    }
}

void print_board(Board board)
{
    size_t r, c;
    Piece piece;

    for (r = 0; r < GRID_SIZE; r++)
    {
        if (r > 0)
        {
            printf("---+---+---\n");
        }

        for (c = 0; c < GRID_SIZE; c++)
        {
            piece = board[r][c];

            if (c > 0)
            {
                printf("|");
            }

            switch (piece)
            {
                case EMPTY:
                    printf(" %lu ", r * GRID_SIZE + c);
                    break;
                case X:
                    printf(ANSI_COLOR_BLUE " X " ANSI_COLOR_RESET);
                    break;
                case O:
                    printf(ANSI_COLOR_RED " O " ANSI_COLOR_RESET);
                    break;
            }
        }
        printf("\n");
    }
}
