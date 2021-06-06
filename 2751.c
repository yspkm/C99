#include <stdio.h>
#include <stdlib.h>

typedef int Data;
void counting(Data* list, int n, int exp);
void rdxSort(Data* list, int n);
int* output = NULL;

int main(void)
{
    int N, temp;
    int* arr;
    scanf("%d", &N);
    arr = (int*) malloc(N * sizeof(int));
    output = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &temp);
        arr[i] = 1000000 + temp;
    }
    rdxSort(arr, N);
    for (int i = 0; i < N; i++)
        printf("%d\n", arr[i] - 1000000);

	return 0;
}

void counting(Data* list, int n, int exp)
{
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(list[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(list[i] / exp) % 10] - 1] = list[i];
        count[(list[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = output[i];
}

void rdxSort(Data* list, int n) 
{
    int max = list[0];
    for (int i = 1; i < n; i++) {
        if (list[i] > max)
            max = list [i];
    }
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting(list, n, exp);
}