#include <stdio.h>
#include <stdlib.h>

#define X 0
#define Y 1 

typedef struct _Point {
    int x;
    int y;
} Point;

int getCmp(Point* p, int type);
void counting(Point* list, int n, int exp, int type);
void rdxSort(Point* list, int n, int type);

Point* output = NULL;

int main(void)
{
    int N;
    scanf("%d", &N);
    Point* arr = (Point*) malloc(sizeof(Point) * N);
    output = (Point*) malloc(sizeof(Point) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
        arr[i].x += 100000;
        arr[i].y += 100000;
    }
    rdxSort(arr, N, Y);
    rdxSort(arr, N, X);
    for (int i = 0; i < N; i++)
        printf("%d %d\n", arr[i].x-100000, arr[i].y-100000);

    return 0;
}
int getCmp(Point* p, int type)
{
    return type == X ? p->x : p->y;
}

void counting(Point* list, int n, int exp, int type)
{
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(getCmp(&list[i], type) / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(getCmp(&list[i], type) / exp) % 10] - 1] = list[i];
        count[(getCmp(&list[i], type) / exp) % 10]--;
    }
    for (int i = 0; i < n; i++)
        list[i] = output[i];
}

void rdxSort(Point* list, int n, int type) 
{
    int max = getCmp(&list[0], type);
    for (int i = 1; i < n; i++) {
        if (getCmp(&list[i], type) > max)
            max = getCmp(&list [i], type);
    }
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting(list, n, exp, type);
}