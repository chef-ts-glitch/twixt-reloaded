#ifndef LINKS_H
#define LINKS_H

#include "board.h"

extern int links[BOARD_SIZE][BOARD_SIZE][8];
extern int moveshorizontal[8];
extern int movesvertical[8];

int linkchecker(int a1, int b1, int a2, int b2);
int crosses_existing_links(int a1, int b1, int a2, int b2);
int linkmaker(int a1, int b1, int a2, int b2);

#endif
