#include <stdio.h>

int main(void) 
{
	int t1, t2, next_term, n, i;
	scanf("%d", &n); 
	switch (n) {
		case 1:
			next_term = 1;
			break;
		case 2:
			next_term = 2;
			break;
		default:
			t2 = 1; next_term = 2;
			for (i = 3; i <= n; i++) {
        			t1 = t2;
        			t2 = next_term;
        			next_term = (t1 + t2) % 15746;
    			}
	}
	printf("%d\n", next_term);
}