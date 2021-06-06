#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Data {
    char word[51]; 
    int len;
} Data;

int wordCmp(const void* d1, const void* d2);

int main(void) 
{
    int N;
    scanf("%d", &N);
    Data* arr = (Data*) malloc(N * sizeof(Data));
    Data* output = (Data*) malloc(N * sizeof(Data));
    int cnt[51] = {0};

    for (int i = 0; i <N; i++) {
        scanf("%s", arr[i].word);
        arr[i].len = strlen(arr[i].word);
        cnt[arr[i].len]++;
    }

    qsort(arr, N, sizeof(Data), wordCmp);

    for (int i = 1; i < 51; i++)
        cnt[i] += cnt[i-1];

    for (int i = N-1; i >= 0; i--)  {
        output[cnt[arr[i].len] - 1] = arr[i];
        cnt[arr[i].len]--;
    }
    int i;
    for (i = 0; i < N-1; i++) {
        if (strcmp(output[i].word, output[i+1].word))
           puts(output[i].word);
    }
    puts(output[i].word);

    return 0;
}

int wordCmp(const void* d1, const void* d2) 
{
    return strcmp(((Data*) d1)->word, ((Data*) d2)->word);
}