#include <stdio.h>
#include <stdlib.h>

typedef struct _SDp {
    short idx;
    short val;
    short len; 
} Dp;

int idxCmp(const void *a, const void *b)   
{
    return (*(Dp*) a).idx - (*(Dp*) b).idx;
}

int main(void)
{
    int N, i, j, temp, max;
    Dp dp[101] = {0};
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        scanf("%hd %hd", &dp[i].idx, &dp[i].val);
        dp[i].len = 1;
    }
    qsort(dp, N+1, sizeof(Dp), idxCmp); //sort
    max = 0;
    for (i = 1; i <= N; i++) {
        temp = 0; 
        for (j = 1; j < i; j++) {
            if (dp[i].val > dp[j].val && dp[j].len > temp) 
                temp = dp[j].len;
        }
        dp[i].len += temp; // original value is 1
        max = dp[i].len > max ? dp[i].len : max;
    }
    printf("%d\n", N - max);
    return 0;
}