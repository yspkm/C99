#include <stdio.h>
#include <stdlib.h>

void sort(int* arr, int l, int r);
int split(int* arr, int l, int r);

int main(void) 
{
    int N;
    int* arr;
    scanf("%d", &N);
    arr = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    sort(arr, 0, N-1);
    for (int i = 0; i < N; i++)
        printf("%d\n", arr[i]);

    return 0;
}

void sort(int* arr, int l, int r)
{
	int middle;

	if (l >= r) return;
	middle = split(arr, l, r);
	sort(arr, l, middle - 1);
	sort(arr, middle + 1, r);
}

int split(int* arr, int l, int r)
{
	int part_element = arr[l];
	
	for (;;) {
		while (l < r && part_element <= arr[r])
			r--;
		if (l >= r && arr[l] <= part_element) break;
		arr[l++] = arr[r];

		while (l < r && arr[l] <= part_element)
			l++;
		if (l >= r) break;
		arr[r--] = arr[l];
	}

	arr[r] = part_element;
	return r;
}