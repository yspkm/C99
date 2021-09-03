#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000000

int main(void)
{
    int i=0, n=0, m=0, num_O=0, ans=0;
    char s[MAX_LEN + 1];
    scanf("%d\n%d\n%s", &n, &m, s);

	for (i = 0; i < m; i++) {
		if (s[i] == 'O') 
            continue;
		num_O = 0;
		while (s[i + 1] == 'O' && s[i + 2] == 'I') {
			num_O++;
			i += 2;
			if (num_O == n) {
				num_O--;
				ans++;
			}
		}
	}
    printf("%d\n", ans);
    return 0;
}