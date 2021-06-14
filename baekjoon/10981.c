#include <stdio.h>

int main(void)
{
    int N, temp;
    int cnt[10001] = {0};
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &temp);
        cnt[temp]++;
    }

    for (int i = 1; i < 10001; i++){
        while (cnt[i] > 0)        {
            printf("%d\n", i);
            cnt[i]--;
        }
    }

    return 0;
}