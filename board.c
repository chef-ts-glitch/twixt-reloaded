#include <stdio.h>
#include <string.h>
#include "board.h"

int board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void displayboard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i != 1) {
            printf("%2d ", i);
        }

        // Top border 
        if (i == 1) {
            printf(BLUE_COLOR);
            for (int z = 0; z < BOARD_SIZE + 3; z++) {
                printf("--");
            }
            printf(RESET_COLOR "\n");
            printf("%2d ", i);
        }

        for (int j = 0; j < BOARD_SIZE; j++) {
            // Left border 
            if (j == 1 && i >= 0 && i < BOARD_SIZE) {
                printf(PURP_COLOR "| " RESET_COLOR);
            }

            if (board[i][j] == EMPTY) {
                printf(". ");
            } else if (board[i][j] == P_BLUE) {
                printf(BLUE_COLOR "O " RESET_COLOR);
            } else if (board[i][j] == P_PURPLE) {
                printf(PURP_COLOR "X " RESET_COLOR);
            }

            // Right border
            if (j == BOARD_SIZE - 2 && i >= 0 && i < BOARD_SIZE) {
                printf(PURP_COLOR "|" RESET_COLOR);
            }
        }

        printf("\n");

        // Bottom border 
        if (i == BOARD_SIZE - 2) {
            printf("   ");
            printf(BLUE_COLOR);
            for (int z = 0; z < BOARD_SIZE; z++) {
                printf("--");
            }
            printf(RESET_COLOR "\n");
        }
    }
}
