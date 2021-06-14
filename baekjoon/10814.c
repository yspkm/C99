#include <stdio.h>
#include <stdlib.h>

typedef struct _Data {
    int age;
    char name[101];
} Data;

int main(void)
{
    int N;
    int count[201] = {0};

    scanf("%d", &N);
    Data *arr = (Data*) malloc(sizeof(Data) * N);
    Data *out = (Data*) malloc(sizeof(Data) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %s", &arr[i].age, arr[i].name);
        count[arr[i].age]++;
    }
    for (int i = 1; i < 201; i++)
        count[i] += count[i-1];
    for (int i = N-1; i >= 0; i--) {
        out[count[arr[i].age] - 1] = arr[i];
        count[arr[i].age]--;
    }
    for (int i = 0; i < N; i++)
        printf("%d %s\n", out[i].age, out[i].name);

    return 0;
}