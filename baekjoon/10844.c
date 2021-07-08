#include <stdio.h>
#define DIV 1000000000
int main(void)
{
	int N, i, j, arr[101][10]={0};
	scanf("%d", &N);

	for (i = 1; i <= 9; i++) {
		arr[1][i] = 1;
	}

	for (i = 2; i<=N; i++) {
		arr[i][0] += arr[i-1][1];
		arr[i][9] += arr[i-1][8];
		for (j = 1; j < 9; j++) {
			arr[i][j] += (arr[i-1][j-1] + arr[i-1][j+1]) % DIV;
		}
	}
	j = 0;
	for (i = 0; i <= 9; i++) {
		j += arr[N][i];
		j %= DIV;
	}
	printf("%d\n", j);

	return 0;
}