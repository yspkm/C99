#include <stdio.h>
#include <stdlib.h>

#define ST 0xABC
#define LK 0xCBA

typedef struct _Player {int name/*0 to g_N-1*/; int team/*ST or LK*/;} Player;

int g_N=0, g_S[20][20]={0}, g_diff = 1000;
Player player_list[20] = {0};

int getDiff(void)
{
	int st = 0, lk = 0, i, j;
	for (i = 0; i < g_N; i++) {
		for (j = 0; j < g_N; j++) {
			if (i == j || player_list[i].team != player_list[j].team) continue;
			if (player_list[i].team == ST) {
				st += g_S[i][j];
			} else { // LK
				lk += g_S[i][j];
			}
		}
	}
	return abs(st - lk);
}

void getMinDiff(int idx, int st_idx, int lk_idx) 
{
	int i, j, temp;
	if (st_idx == g_N/2 || lk_idx == g_N/2) { //
		if (st_idx < lk_idx) {
			for (i = idx; i < g_N; i++) {
				player_list[i].team = ST;
			}
		} else if (st_idx > lk_idx){
			for (i = idx; i < g_N; i++) {
				player_list[i].team = LK;
			}
		} 
		temp = getDiff();
		if (temp < g_diff) g_diff = temp;
		return;
	}
	player_list[idx].team = ST;
	getMinDiff(idx + 1, st_idx+1, lk_idx);
	player_list[idx].team = LK;
	getMinDiff(idx + 1, st_idx, lk_idx+1);
}

int main(void) 
{
	int i, j;
	scanf("%d", &g_N);
	for (i = 0; i < g_N; i++) {
		player_list[i].name = i;
		for (j = 0; j < g_N; j++) {
			scanf("%d", &g_S[i][j]);
		}
	}
	getMinDiff(0, 0, 0);
	printf("%d\n", g_diff);
	return 0;
}