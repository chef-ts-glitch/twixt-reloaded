#ifndef WINCHECK_H
#define WINCHECK_H

#include "board.h"

extern int visited[BOARD_SIZE][BOARD_SIZE];

int is_winner(int r, int c, int player);
int blue_win(void);
int purple_win(void);

#endif
