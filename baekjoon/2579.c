#include <stdio.h>

int main(void)
{
	int n, steps[300+1] = {0}, i, temp1, temp2, sums[300+1] = {0};

	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &steps[i]);
		sums[i] = steps[i];
	}
	if (n == 1) {
		printf("%d\n", steps[1]);
	} else if (n == 2) {
		printf("%d\n", steps[1] + steps[2]);
	} else {
		sums[2] += steps[1];
		for (i = 3; i <= n; i++) {
			temp1 = sums[i-2];
			temp2 = steps[i-1] + sums[i-3];
			sums[i] += temp1 > temp2 ? temp1 : temp2;
		}
		printf("%d\n", sums[n]);
	}

	return 0;
}