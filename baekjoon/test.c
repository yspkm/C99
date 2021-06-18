#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXSIZE 500

int matrix[MAXSIZE][MAXSIZE];
int rows, cols;

int rowFactors[100];
int colFactors[100];
int nr, nc;

typedef int Data;
typedef struct _Node
{
	int item;
	struct _Node *next;
} Node;
typedef struct _List
{
	Node *head;
	int len;
} List;

void initList(List **lptrptr);
void addNode(List *lptr, Data item);
void printAllNode(List *lptr);

int gcd(int a, int b);
void setFactors(int val, int factors[], int *num);
int getFactors(int val);
int countTensor(int r, int c);

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

void setFactors(int val, int factors[], int *num)
{
	*num = 0;
	int f = 1;
	while (f <= val / 2)
	{
		if (val % f == 0)
			factors[(*num)++] = f;
		f++;
	}
	factors[(*num)++] = val;
}

int getFactors(int val)
{
	int num = 0;
	int f = 1;
	int sq = (int)sqrt((double)val);
	while (f <= sq)
	{
		if (val % f == 0)
			num += 2;
		f++;
	}
	f--;
	if (f * f == val)
		num--;
	return num;
}

int countTensor(int r, int c)
{
	if (r == 1 && c == 1)
		return false;
	if (r == rows && c == cols)
		return false;
	int i, j, k, l;
	int val1 = matrix[0][0];
	int gcd1 = matrix[0][0];
	for (i = 0; i < rows / r; i++)
	{
		for (j = 0; j < cols / c; j++)
		{
			int val2 = matrix[i * r][j * c];
			for (k = 0; k < r; k++)
			{
				for (l = 0; l < c; l++)
				{
					gcd1 = gcd(gcd1, matrix[k][l]);
					if (val1 * matrix[i * r + k][j * c + l] != val2 * matrix[k][l])
						return 0;
				}
			}
		}
	}
	int baseVal = matrix[0][0] / gcd1;
	for (i = 0; i < rows; i += r)
		for (j = 0; j < cols; j += c)
		{
			gcd1 = gcd(gcd1, matrix[i][j] / baseVal);
		}

	return getFactors(gcd1);
}

int main(void)
{
	int i, j;
	List *res;
	initList(&res);

	scanf("%d %d", &rows, &cols);
	while (rows != 0 && cols != 0)
	{
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				scanf("%d", &matrix[i][j]);
			}
		}

		setFactors(rows, rowFactors, &nr);
		setFactors(cols, colFactors, &nc);

		int numTensor = 0;
		for (i = 0; i < nr; i++)
		{
			for (j = 0; j < nc; j++)
			{
				numTensor += countTensor(rowFactors[i], colFactors[j]);
			}
		}
		addNode(res, numTensor);
		scanf("%d %d", &rows, &cols);
	}
	printAllNode(res);

	return 0;
}

void addNode(List *lptr, Data item)
{
	Node *temp;
	if (!lptr->head->next)
	{
		temp = (Node *)malloc(sizeof(Node));
		temp->item = item;
		temp->next = NULL;
		lptr->head->next = temp;
	}
	else
	{
		Node *cur;
		for (cur = lptr->head; cur->next; cur = cur->next)
			;
		temp = (Node *)malloc(sizeof(Node));
		temp->item = item;
		temp->next = NULL;
		cur->next = temp;
	}
	lptr->len++;
}

void printAllNode(List *lptr)
{
	if (lptr->len == 0)
		exit(1);
	Node *cur = lptr->head->next;
	for (; cur;)
	{
		printf("%d\n", cur->item);
		cur = cur->next;
	}
}

void initList(List **lptrptr)
{
	*lptrptr = (List *)malloc(sizeof(List));
	(*lptrptr)->head = (Node *)malloc(sizeof(Node));
	(*lptrptr)->head->next = NULL;
	(*lptrptr)->len = 0;
}