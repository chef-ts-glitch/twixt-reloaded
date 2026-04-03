#include <string.h>
#include "wincheck.h"
#include "links.h"

int visited[BOARD_SIZE][BOARD_SIZE];

int is_winner(int r, int c, int player) {
    if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE) return 0;
    if (visited[r][c]) return 0;
    if (board[r][c] != player) return 0;

    visited[r][c] = 1;

    if (player == P_BLUE   && r == BOARD_SIZE - 1) return 1;
    if (player == P_PURPLE && c == BOARD_SIZE - 1) return 1;

    for (int d = 0; d < 8; d++) {
        if (links[r][c][d]) {
            int nr = r + moveshorizontal[d];
            int nc = c + movesvertical[d];
            if (is_winner(nr, nc, player)) return 1;
        }
    }
    return 0;
}

int blue_win(void) {
    memset(visited, 0, sizeof(visited));
    for (int c = 0; c < BOARD_SIZE; c++) {
        if (board[0][c] == P_BLUE) {
            if (is_winner(0, c, P_BLUE)) return 1;
        }
    }
    return 0;
}

int purple_win(void) {
    memset(visited, 0, sizeof(visited));
    for (int r = 0; r < BOARD_SIZE; r++) {
        if (board[r][0] == P_PURPLE) {
            if (is_winner(r, 0, P_PURPLE)) return 1;
        }
    }
    return 0;
}
