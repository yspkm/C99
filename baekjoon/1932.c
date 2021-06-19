#include <stdio.h>

int arr[501][501] = {0};
int dp[501][501] = {0};

int main(void) 
{
	int N, i, j, max, temp1,temp2; 
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		for (j = 0; j <= i; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	dp[0][0] = arr[0][0];
	for (int i = 1; i<N; i++){
		for (int j = 0; j <= i; j++){
			if (j == 0) {
				dp[i][j] = dp[i - 1][j] + arr[i][j];
			} else if (i == j) {
				dp[i][j] = dp[i - 1][j - 1] + arr[i][j];
			} else {
				temp1 = dp[i-1][j-1] + arr[i][j];
				temp2 = dp[i-1][j] + arr[i][j];
				dp[i][j] =  temp1 > temp2 ? temp1 : temp2;
			}
		}
	}
	max = 0;
	for (i = 0; i < N; i++) {
		if (max < dp[N-1][i]) {
			max = dp[N-1][i];
		}
	}
	printf("%d\n", max);

	return 0;
}