#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* g_arr = NULL;
bool* g_mark = NULL;
int g_m = 0;
int g_n = 0;

void printLine(int idx)
{
	int i;
	if (idx == g_m) {
		for (i = 0; i < g_m-1; i++)
			printf("%d ", g_arr[i]);
		printf("%d\n", g_arr[i]);
		return;
	}
	for (i = 0; i < g_n; i++) {
		g_arr[idx] = i+1;
		printLine(idx+1);
	}
}

int main(void)
{
	scanf("%d %d", &g_n, &g_m);

	g_arr = (int*) malloc(sizeof(int) * g_m);
	g_mark = (bool*) malloc(sizeof(bool) * g_n);

	for (int i = 0; i < g_m; i++) 
		g_mark[i] = false;

	printLine(0);
	return 0;
}