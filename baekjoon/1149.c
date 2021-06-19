#include <stdio.h>
int main(void){
	int sum[3]={0}, temp_sum[3];
	short i, j, N, val[3] = {0};
	char col1, col2;
	scanf("%hd", &N);
	for (i = 0; i < N; i++) {
		scanf("%hd %hd %hd", &val[0], &val[1], &val[2]);
		for (j = 0; j < 3; j++) {
			if (j == 0) {col1 = 1; col2 = 2;}
			else if (j == 1) {col1 = 0; col2 = 2;}
			else {col1 = 0; col2 = 1;}
			if (sum[col1] < sum[col2]) temp_sum[j] = sum[col1] + val[j];
			else temp_sum[j] = sum[col2] + val[j];
		}
		sum[0] = temp_sum[0]; sum[1] = temp_sum[1]; sum[2] = temp_sum[2];
	} 
	printf("%d\n", sum[0] < sum[1] ? (sum[0] < sum[2] ? sum[0] : sum[2]) : (sum[1] < sum[2] ? sum[1] : sum[2]));
}