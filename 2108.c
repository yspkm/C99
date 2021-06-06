#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct _Data2 {Data num; short idx;} Data2;
void countingFirst(Data* list, Data2* cnt2, int n);
void counting(Data2* list, int n, int exp);
void rdxSort(Data2* list, int n);
void count(Data* list, int n, int exp);
void rdx(Data* list, int n);
int* output = NULL;

void printarr(Data2* arr) {
    for (int i = 8000; i >= 7980; i--)
        printf("%d %d\n", arr[i].idx, arr[i].num);
    printf("\n");
}

int main(void)
{
    int N, temp, sum =0, max = -4000, min = 4000;
    int* arr;
    scanf("%d", &N);
    arr = (int*) malloc(N * sizeof(int));
    output = (int*) malloc(N * sizeof(int));
    Data2 cnt[8001] = {0};
    for (int i = 0; i < 8001; i++)
        cnt[i].idx = i;
    //printf("%d %d", cnt2[30].idx, cnt2[50].num);

    for (int i = 0; i < N; i++) {
        scanf("%d", &temp);
        arr[i] = 4000 + temp;
        cnt[temp+4000].num++;

        sum += temp;
        if (min > temp)
            min = temp;
        if (max < temp)
            max = temp;
    }
    //printarr(cnt);
    rdx(arr, N);
    rdxSort(cnt, 8001);

    printf("%.0f\n", sum/(double)N);
    printf("%d\n", arr[(N+1)/2 -1] - 4000);

    //printarr(cnt);
    if (cnt[8000].num == cnt[7999].num)
        for (int i = 7998; i >= 0; i--) {
            if (cnt[i].num != cnt[8000].num) {
                cnt[8000] = cnt[i+2];
                break;
            }
        }
    //printarr(cnt);

    printf("%d\n", cnt[8000].idx - 4000);
    printf("%d\n", max-min);
	return 0;
}

void count(Data* list, int n, int exp)
{
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(list[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(list[i]/ exp) % 10] - 1] = list[i];
        count[(list[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = output[i];
}

void rdx(Data* list, int n) 
{
    int max = list[0];
    for (int i = 1; i < n; i++) {
        if (list[i]> max)
            max = list[i];
    }
    for (int exp = 1; max / exp > 0; exp *= 10)
        count(list, n, exp);
}

void counting(Data2* list, int n, int exp)
{
    int count[10] = {0};
    Data2 out[8001] = {0};
    
    for (int i = 0; i < n; i++)
        count[(list[i].num / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n-1; i >= 0; i--) {
        out[count[(list[i].num / exp) % 10] - 1] = list[i];
        count[(list[i].num/ exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = out[i];
}

void rdxSort(Data2* list, int n) 
{
    int max = list[0].num;
    for (int i = 1; i < n; i++) {
        if (list[i].num > max)
            max = list[i].num;
    }
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting(list, n, exp);
}