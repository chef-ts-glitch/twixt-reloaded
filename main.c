#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "links.h"
#include "wincheck.h"

int main(void) {
    initializeBoard(board);
    memset(links, 0, sizeof(links));

    printf("TWIXT RELOADED.\n");
    printf(BLUE_COLOR "BLUE (O) connects Row 0 to Row 23.\n" RESET_COLOR);
    printf(PURP_COLOR "PURPLE (X) connects Col 0 to Col 23.\n" RESET_COLOR);

    displayboard(board);

    int i, j;
    for (int k = 1; k < BOARD_SIZE * BOARD_SIZE; k++) {

        if (k % 2 == 1) {
            // Player 1: BLUE (O) – vertical
            printf(BLUE_COLOR "BLUE'S TURN (Row Col): " RESET_COLOR);
            if (scanf("%d %d", &i, &j) != 2) {
                while (getchar() != '\n');
                k--;
                continue;
            }

            if (i < 0 || i >= BOARD_SIZE ||
                j <= 0 || j >= BOARD_SIZE - 1 ||
                board[i][j] != EMPTY) {
                printf("INVALID MOVE (Blue cannot play in cols 0 or 23).\n");
                k--;
                continue;
            }

            board[i][j] = P_BLUE;

            for (int d = 0; d < 8; d++) {
                int ni = i + moveshorizontal[d];
                int nj = j + movesvertical[d];
                if (ni >= 0 && ni < BOARD_SIZE &&
                    nj >= 0 && nj < BOARD_SIZE) {
                    if (board[ni][nj] == P_BLUE) {
                        linkmaker(i, j, ni, nj);
                    }
                }
            }
        } else {
            // Player 2: PURPLE (X) – horizontal
            printf(PURP_COLOR "PURPLE'S TURN (Row Col): " RESET_COLOR);
            if (scanf("%d %d", &i, &j) != 2) {
                while (getchar() != '\n');
                k--;
                continue;
            }

            if (i <= 0 || i >= BOARD_SIZE - 1 ||
                j < 0 || j >= BOARD_SIZE ||
                board[i][j] != EMPTY) {
                printf("INVALID MOVE (Purple cannot play in rows 0 or 23).\n");
                k--;
                continue;
            }

            board[i][j] = P_PURPLE;

            for (int d = 0; d < 8; d++) {
                int ni = i + moveshorizontal[d];
                int nj = j + movesvertical[d];
                if (ni >= 0 && ni < BOARD_SIZE &&
                    nj >= 0 && nj < BOARD_SIZE) {
                    if (board[ni][nj] == P_PURPLE) {
                        linkmaker(i, j, ni, nj);
                    }
                }
            }
        }

        displayboard(board);

        if (blue_win()) {
            printf(BLUE_COLOR "\n*** BLUE (O) WINS! (Top to Bottom) ***\n" RESET_COLOR);
            break;
        }
        if (purple_win()) {
            printf(PURP_COLOR "\n*** PURPLE (X) WINS! (Left to Right) ***\n" RESET_COLOR);
            break;
        }
    }

    return 0;
}
