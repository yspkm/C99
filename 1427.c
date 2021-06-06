#include <stdio.h>
int main(void)
{
    int N, temp;
    char c;
    char count[10] = {0};
    while((c = getchar()) != '\n') {
        count[c-'0']++;
    }

    for (int i = 9; i >= 0; i--){
        while (count[i] > 0)        {
            putchar(i+'0');
            count[i]--;
        }
    }
    printf("\n");

    return 0;
}