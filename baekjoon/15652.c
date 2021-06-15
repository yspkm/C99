#include <stdio.h>
#include <stdlib.h>

int* g_arr = NULL;
int g_n =0, g_m=0; 

void printLine(int num, int idx) 
{
	int i;
	if (idx == g_m) {
		for (i = 0; i < g_m-1; i++)
			printf("%d ", g_arr[i]);
		printf("%d\n", g_arr[i]);
		return;
	} 
	for (i = num; i <= g_n; i++) {
		g_arr[idx] = i;
		printLine(i, idx+1);
	}
}

int main(void)
{
	scanf("%d %d", &g_n, &g_m);
	g_arr = (int*) malloc(sizeof(int) * g_m);
	printLine(1, 0);
	return 0;
}