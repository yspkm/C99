#include "myheader.h"

#define MAXSIZE 1000
void printMatrix(int matrix[][MAXSIZE], int rows, int cols) //p.35
{
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) 
			printf("%d", matrix[i][j]);
		printf("\n");
	}
}

void scanMatrix(int matrix[][MAXSIZE], int rows, int cols) //p.35
{
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) 
			scanf("%d", &matrix[i][j]);
		printf("\n");
	}
}

void mult(int a[][MAXSIZE], int b[][MAXSIZE], int c[][MAXSIZE])
{
	int i, j, k;
	for (j = 0; j <M)
}