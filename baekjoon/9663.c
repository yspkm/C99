#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* g_cols = NULL; 
bool* g_mark = NULL;
int g_cnt = 0, g_n = 0;

bool isRight(int row, int col)
{
	int i;
	if (g_mark[col])
		return false; for (i = 0; i < row; i++) {
		if (abs(row - i) == abs(col - g_cols[i])) {
			return false;
		}
	}
	return true;
}

void checker(int idx)
{
	if (idx == g_n) {
		g_cnt++;
		return;
	}
	for (int i = 0; i < g_n; i++) {
		if (isRight(idx, i)) {
			g_mark[i] = true;
			g_cols[idx] = i;
			checker(idx+1);
			g_mark[i] = false;
		}
	}
}

int main(void) 
{
	scanf("%d", &g_n);
	g_cols = (int*) malloc(sizeof(int) * g_n);
	g_mark = (bool*) malloc(sizeof(bool) * g_n);

	for (int i = 0; i < g_n; i++) {
		g_mark[i] = false;
	}

	checker(0);
	printf("%d\n", g_cnt);

	return 0;
}