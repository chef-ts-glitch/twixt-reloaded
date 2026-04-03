#include <stdio.h>
#include "links.h"

int moveshorizontal[8] = {  2,  2,  1, -1, -2, -2, -1,  1 };
int movesvertical[8]   = {  1, -1,  2,  2,  1, -1, -2, -2 };

int links[BOARD_SIZE][BOARD_SIZE][8];

int linkchecker(int a1, int b1, int a2, int b2) {
    for (int i = 0; i < 8; i++) {
        if (moveshorizontal[i] == a2 - a1 &&
            movesvertical[i]   == b2 - b1) {
            return i;
        }
    }
    return -1;
}

//intersecttt or nott

int orientation(int px, int py, int qx, int qy, int rx, int ry) {
    int val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

int onSegment(int px, int py, int qx, int qy, int rx, int ry) {
    if (qx <= (px > rx ? px : rx) && qx >= (px < rx ? px : rx) &&
        qy <= (py > ry ? py : ry) && qy >= (py < ry ? py : ry)) {
        return 1;
    }
    return 0;
}

int doIntersect(int p1x, int p1y, int q1x, int q1y,
                       int p2x, int p2y, int q2x, int q2y) {
    int o1 = orientation(p1x, p1y, q1x, q1y, p2x, p2y);
    int o2 = orientation(p1x, p1y, q1x, q1y, q2x, q2y);
    int o3 = orientation(p2x, p2y, q2x, q2y, p1x, p1y);
    int o4 = orientation(p2x, p2y, q2x, q2y, q1x, q1y);

    if (o1 != o2 && o3 != o4) return 1;
    if (o1 == 0 && onSegment(p1x, p1y, p2x, p2y, q1x, q1y)) return 1;
    if (o2 == 0 && onSegment(p1x, p1y, q2x, q2y, q1x, q1y)) return 1;
    if (o3 == 0 && onSegment(p2x, p2y, p1x, p1y, q2x, q2y)) return 1;
    if (o4 == 0 && onSegment(p2x, p2y, q1x, q1y, q2x, q2y)) return 1;

    return 0;
}

int crosses_existing_links(int a1, int b1, int a2, int b2) {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int d = 0; d < 8; d++) {
                if (!links[x][y][d]) continue;

                int x2 = x + moveshorizontal[d];
                int y2 = y + movesvertical[d];

                if (x2 < 0 || x2 >= BOARD_SIZE ||
                    y2 < 0 || y2 >= BOARD_SIZE) {
                    continue;
                }

                if ((x  == a1 && y  == b1) ||
                    (x  == a2 && y  == b2) ||
                    (x2 == a1 && y2 == b1) ||
                    (x2 == a2 && y2 == b2)) {
                    continue;
                }

                if (doIntersect(a1, b1, a2, b2, x, y, x2, y2)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int linkmaker(int a1, int b1, int a2, int b2) {
    int player = board[a1][b1];
    if (player == EMPTY || board[a2][b2] != player) return 0;

    int dir = linkchecker(a1, b1, a2, b2);
    if (dir == -1) return 0;
    if (crosses_existing_links(a1, b1, a2, b2)) return 0;

    // link forward
    links[a1][b1][dir] = 1;

    // link reverse
    int opp_dir = -1;
    int target_dx = -moveshorizontal[dir];
    int target_dy = -movesvertical[dir];

    for (int k = 0; k < 8; k++) {
        if (moveshorizontal[k] == target_dx &&
            movesvertical[k]   == target_dy) {
            opp_dir = k;
            break;
        }
    }
    if (opp_dir != -1) {
        links[a2][b2][opp_dir] = 1;
    }

    return 1;
}
