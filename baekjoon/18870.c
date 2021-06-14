#include <stdio.h>
#include <stdlib.h>

typedef struct _Data {int x; int xp;} Data;

void compress(Data** sorted_list, int n);
int cmp(const void* v1, const void * v2);


int main(void)
{
    int N;
    int tmp;
    scanf("%d", &N);

    Data** new_arr = (Data**) malloc(sizeof(Data*)*N);
    Data** old_arr = (Data**) malloc(sizeof(Data*)*N);
    Data* temp;

    for (int i = 0; i < N; i++) {
        temp = (Data*) malloc(sizeof(Data));
        temp->xp = 0;
        scanf("%d", &tmp);
        temp->x = tmp; 
        old_arr[i] = temp;
        new_arr[i] = temp;
    }
    qsort(new_arr, N, sizeof(Data*), cmp);
    compress(new_arr, N);
    for (int i = 0; i < N; i++)
        printf("%d ", old_arr[i]->xp);
    printf("\n");
}

void compress(Data** sorted_list, int n) 
{
    int i = 0;
    int l = sorted_list[i]->x;
    int r = l;
    int cnt = 0;
    while(i < n-1) {
        sorted_list[i]->xp = cnt;
        if (sorted_list[++i]->x != l) {
            r = sorted_list[i]->x;
            sorted_list[i]->xp = ++cnt;
            break;
        }
    }
    while(i < n-1) {
        if (sorted_list[++i]->x == r)
            sorted_list[i]->xp = cnt;
        else {
            l = r;
            r = sorted_list[i]->x;
            sorted_list[i]->xp = ++cnt;
        }
    }
}

int cmp(const void* v1, const void * v2) 
{
    Data** x1 = (Data**) v1;
    Data** x2 = (Data**) v2;
    return (*x1)->x - (*x2)->x;
}
