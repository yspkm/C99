#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LEN 21

int w(int a, int b, int c);
int mem[LEN][LEN][LEN] = {0};

typedef int Data;
typedef struct _Node
{
    int a, b, c, w;
    struct _Node *next;
} Node;
typedef struct _List
{
    Node *head;
    int len;
} List;
void initList(List **lptrptr);
void addNode(List *lptr, Data a, Data b, Data c, Data w);
void printAllNode(List *lptr);

void addNode(List *lptr, Data a, Data b, Data c, Data w)
{
    Node *temp;
    if (!lptr->head->next)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->a = a;
        temp->b = b;
        temp->c = c;
        temp->w = w;
        temp->next = NULL;
        lptr->head->next = temp;
    }
    else
    {
        Node *cur;
        for (cur = lptr->head; cur->next; cur = cur->next)
            ;
        temp = (Node *)malloc(sizeof(Node));
        temp->a = a;
        temp->b = b;
        temp->c = c;
        temp->w = w;
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
        printf("w(%d, %d, %d) = %d\n", cur->a, cur->b, cur->c, cur->w);
        cur = cur->next;
    }
}

void initList(List **lptrptr)
{
    *lptrptr = (List *)malloc(sizeof(List));
    (*lptrptr)->head = (Node*) malloc(sizeof(Node));
    (*lptrptr)->head->next = NULL;
    (*lptrptr)->len = 0;
}

bool isInRange(int a, int b, int c) {
	return 0 <= a && a <= 20 && 0 <= b && b <= 20 && 0 <= c && c <=20;
}

int main(void) 
{
	int a, b, c;
	List* res; initList(&res);
	scanf("%d %d %d", &a, &b, &c);
	while(!(a==-1 && b ==-1 && c==-1)) {
		addNode(res, a, b, c, w(a,b,c));
		scanf("%d %d %d", &a, &b, &c);
	}
	printAllNode(res);
	
	return 0;
}

int w(int a, int b, int c)
{
	if (isInRange(a,b,c) && mem[a][b][c]) return mem[a][b][c];
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20)
		return  mem[20][20][20] = w(20, 20, 20);
	if (a < b && b < c) {
    		return mem[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
	}

	return  mem[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
}