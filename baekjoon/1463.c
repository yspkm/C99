#include <stdio.h>
#include <stdlib.h>
#define MIN(A, B) (A)<(B)?(A):(B)
int main(void)
{
	int N, *arr, i, temp; 
	scanf("%d", &N);
	arr = (int*) malloc(sizeof(int) * (N+1));
	arr[1] = 0;
	for (i = 2; i < N+1; i++) {
		temp = arr[i-1]+1;
		if (!(i%2)) temp = MIN(temp, arr[i/2]+1);
		if (!(i%3)) temp = MIN(temp, arr[i/3]+1);
		arr[i] = temp;
	}
	printf("%d", arr[i-1]);
	return 0;
}