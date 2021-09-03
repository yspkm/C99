#include <stdio.h>

int main(void) 
{
    int n, term, temp, num_5, num_2;
    scanf("%d", &n);
    num_5 = 0;
    num_2 = 0;
    for (term = 1; term <= n; term++) {
        for (temp = term; temp; temp /= 5) {
            if (!(temp % 5)) {
                num_5++;
            } else {
                break;
            }
        }
        for (temp = term; temp; temp /= 2) {
            if (!(temp % 2)) {
                num_2++;
            } else {
                break;
            }
        }

    }
    printf("%d\n", num_2 < num_5 ? num_2 : num_5);
    return 0;
}