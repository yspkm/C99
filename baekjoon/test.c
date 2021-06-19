#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	int count = 0;
	long long max = 1000000+1000000000000;
	for (long long i = 0; i*i < max; i++) {
		count++;
	}
	printf("%d\n", count);
}