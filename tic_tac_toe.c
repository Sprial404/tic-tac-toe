#include <stdio.h>
#include <stdlib.h>

#include "ansi.h"
#include "game.h"

int main(void)
{
    char buffer[10];
    char choice;

    do {
        play_game();
        printf("\n");
        printf(ANSI_COLOR_YELLOW  "Enter 'q' if you wish to quit: " ANSI_COLOR_RESET);
        if (fgets(buffer, 10, stdin) != NULL)
        {
            choice = buffer[0];
        }

    } while (choice != 'q');

    return 0;
}
