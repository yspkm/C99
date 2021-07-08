#include <stdio.h>

#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

typedef struct _SGlassSum {
    int with;
    int without;
} GlassSum;

int main(void)
{
    int i;
    GlassSum sum[10001] = {{0,0}};
    short n, arr[10001] = {0};

    scanf("%hd", &n);
    for (i = 1; i <= n; i++) {
        scanf("%hd", &arr[i]);
    }
    sum[1].with= arr[1];
    sum[1].without = 0;
    sum[2].with = arr[2] + arr[1];
    sum[2].without = arr[1];
    for (i = 3; i <= n; i++) {
        sum[i].with = arr[i] + max(arr[i-1]+sum[i-2].without, sum[i-1].without);
        sum[i].without = max(sum[i-1].with, sum[i-1].without);
    }
    printf("%d\n", max(sum[n].with, sum[n].without));

    return 0;
}