#include <stdio.h>

#define U 0
#define R 1
#define D 2
#define L 3
#define DL 4
#define DR 5
#define UR 6
#define UL 7
#define STAY {0, 0, 0}

#define I 0
#define J 1

typedef struct {
    int rot; 
    int didj_idx[8][3];
} Shape;

const int g_didj[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}, {0, 0}};
const Shape g_directions[5] = {
    {2, {{R, R, R}, {D, D, D}, STAY, STAY, STAY, STAY, STAY, STAY}},
    {1, {{D, R, U}, STAY, STAY, STAY, STAY, STAY, STAY, STAY}},
    {8, {{D, D, R}, {R, R, U}, {U, U, L}, {L, L, D}, {D, D, L}, {R, R, D}, {U, U, R}, {L, L, U}}},
    {4, {{D, R, D}, {R, U, R}, {D, L, D}, {R, D, R}, STAY, STAY, STAY, STAY}},
    {4, {{R, R, DL}, {U, U, DR}, {L, L, UR}, {D, D, UL}, STAY, STAY, STAY, STAY}}
};

int g_n=0, g_m=0;
short g_board[500][500] = {0};

int getMaxSum(int i, int j, int shape) {
    int rot_idx=0, ret=0, temp=0, dn=0, row=0, col=0, dir_idx=0;
    for (rot_idx = 0; rot_idx < g_directions[shape].rot; rot_idx++) {
        temp = g_board[i][j];
        row = i;
        col = j;
        for (dn=0; dn < 3; dn++) {
            dir_idx = g_directions[shape].didj_idx[rot_idx][dn];
            row += g_didj[dir_idx][I];
            col += g_didj[dir_idx][J];
            if ((0 <= row && row < g_n ) && (0 <= col && col < g_m)) {
                temp += g_board[row][col];
            } else {
                temp = 0;
                break;
            }
        }
        ret = temp > ret ? temp : ret;
    }
    return (ret == g_board[i][j] ? 0 : ret);
}

int main(void) 
{
    int i, j, k, temp=0, ans=0;  
    scanf("%d %d", &g_n, &g_m);

    for (i = 0; i < g_n; i++) {
        for (j = 0; j < g_m; j++) {
            scanf("%hd", &g_board[i][j]);
        }
    }

    for (i = 0; i < g_n; i++) {
        for (j = 0; j < g_m; j++) {
            for (k = 0; k < 5; k++) {
                temp = getMaxSum(i, j, k);
                ans = temp > ans ? temp : ans;
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}