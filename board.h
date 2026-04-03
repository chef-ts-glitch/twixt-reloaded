#ifndef BOARD_H
#define BOARD_H

#include "color.h"

#define BOARD_SIZE 24

typedef enum { EMPTY = 0, P_BLUE = 1, P_PURPLE = 2 } Player;

extern int board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]);
void displayboard(int board[BOARD_SIZE][BOARD_SIZE]);

#endif
