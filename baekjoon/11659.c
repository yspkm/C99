#include <stdio.h>

int main(){
    int n=0, m=0, idx=0, temp=0, dp[100001]={0}, ans[100001] = {0}, i=0, j=0;
    scanf("%d %d", &n, &m);
    for(idx = 0; idx < n; idx++){
        scanf("%d", &temp);
        dp[idx+1] = dp[idx] + temp;
    }
    for(idx = 1; idx <= m; idx++){
        scanf("%d %d", &i, &j);
        ans[idx] = dp[j] - dp[i-1];
    }
    for (idx = 1; idx <= m; idx++) {
        printf("%d\n", ans[idx]);
    }
}