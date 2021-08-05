#include <stdio.h>

typedef struct _SDp {
    short num; 
    short for_len;
    short back_len;
} Dp;

int main(void)
{
    int N, i, j, max, temp;
    Dp dp[1001] = {{0, 0, 0}};

    scanf("%d", &N);
    for (i = 1; i <= N; i++) {
        scanf("%hd", &dp[i].num);
        dp[i].for_len = 1;
        dp[i].back_len = 1;
    }

    // forward checking
    for (i = 1; i <= N; i++) {
        temp = 0;
        for (j = 1; j < i; j++) {
            if (dp[i].num > dp[j].num && temp < dp[j].for_len) {
                temp = dp[j].for_len;
            }
        }
        dp[i].for_len += temp;
    }
    
    // backward checking
    for (i = N; i >= 1 ;i--) {
        temp = 0;
        for (j = N; j > i; j--) {
            if (dp[i].num > dp[j].num && temp < dp[j].back_len) {
                temp = dp[j].back_len;
            }
        }
        dp[i].back_len += temp;
    }

    // test printing
    /* for (i = 1; i <= N; i++) {
        printf("num: %hd\tfor: %hd\tback: %hd\n", dp[i].num, dp[i].for_len, dp[i].back_len);
    } */

    max = 0;
    for (i = 1; i <= N; i++) {
        temp = dp[i].for_len + dp[i].back_len - 1;
        if (max < temp) 
            max = temp;
    }
    printf("%d\n", max);

    return 0;
}