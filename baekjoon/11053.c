#include <stdio.h>

typedef struct _SSequence { short aj; short len;} Sequence;

int main(void) 
{
    short i, j, N, temp, max = -1;
    Sequence dp[1001] = {{0,0}};
    scanf("%hd", &N);
    for (i = 1; i <= N; i++) {
        scanf("%hd", &dp[i].aj);
        dp[i].len = 1;
    }

    for (i = 1; i <= N; i++) {
        temp = 0;
        for (j = 1; j < i; j++)
            if (dp[i].aj > dp[j].aj) 
                if (temp < dp[j].len)
                    temp = dp[j].len;
        dp[i].len += temp;
        if (max < dp[i].len) 
            max = dp[i].len;
    }
    printf("%d\n", max);

    return 0;
}