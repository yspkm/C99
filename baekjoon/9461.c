#include <stdio.h>
#include <stdlib.h>

typedef long long Data;
typedef struct _Node
{
    Data item;
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

int main(void)
{
	List* ans; initList(&ans);
	int T, N, i, j;
	long long n1, n2, n3, res;
	scanf("%d", &T);
	for(i = 0; i < T; i++) {
		scanf("%d", &N);
		switch (N) {
			case 1: case 2: case 3: res = 1; break;
			default:
				n1 = 1; n2 = 1; n3 = 1;
				for (j = 4; j <= N; j++) {
					res = n1 + n2;	
					n1 = n2; n2 = n3; n3 = res;
				}

		}
		addNode(ans, res);
	}
	printAllNode(ans);

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
        printf("%lld\n", cur->item);
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