#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct _Node
{
    int i;
    int j;
    struct _Node *next;
} Node;
typedef struct _List
{
    Node *head;
    int len;
} List;

void initList(List **lptrptr);
void addNode(List *lptr, Data i, Data j);
void printAllNode(List *lptr);

List* res = NULL;

int fibonacci(int n);
int main(void) 
{	
	initList(&res);
	int T, N;	
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		fibonacci(N);
	}
	printAllNode(res);
	return 0;
}

int fibonacci(int n) 
{
        switch(n) {
                case 0: addNode(res, 1, 0); break;
                case 1: addNode(res, 0, 1); break;
                case 2: addNode(res, 1, 1); break;
                case 3: addNode(res, 1, 2); break;
                case 4: addNode(res, 2, 3); break;
                case 5: addNode(res, 3, 5); break;
                case 6: addNode(res, 5, 8); break;
                case 7: addNode(res, 8, 13); break;
                case 8: addNode(res, 13, 21); break;
                case 9: addNode(res, 21, 34); break;
                case 10: addNode(res, 34, 55); break;
                case 11: addNode(res, 55, 89); break;
                case 12: addNode(res, 89, 144); break;
                case 13: addNode(res, 144, 233); break;
                case 14: addNode(res, 233, 377); break;
                case 15: addNode(res, 377, 610); break;
                case 16: addNode(res, 610, 987); break;
                case 17: addNode(res, 987, 1597); break;
                case 18: addNode(res, 1597, 2584); break;
                case 19: addNode(res, 2584, 4181); break;
                case 20: addNode(res, 4181, 6765); break;
                case 21: addNode(res, 6765, 10946); break;
                case 22: addNode(res, 10946, 17711); break;
                case 23: addNode(res, 17711, 28657); break;
                case 24: addNode(res, 28657, 46368); break;
                case 25: addNode(res, 46368, 75025); break;
                case 26: addNode(res, 75025, 121393); break;
                case 27: addNode(res, 121393, 196418); break;
                case 28: addNode(res, 196418, 317811); break;
                case 29: addNode(res, 317811, 514229); break;
                case 30: addNode(res, 514229, 832040); break;
                case 31: addNode(res, 832040, 1346269); break;
                case 32: addNode(res, 1346269, 2178309); break;
                case 33: addNode(res, 2178309, 3524578); break;
                case 34: addNode(res, 3524578, 5702887); break;
                case 35: addNode(res, 5702887, 9227465); break;
                case 36: addNode(res, 9227465, 14930352); break;
                case 37: addNode(res, 14930352, 24157817); break;
                case 38: addNode(res, 24157817, 39088169); break;
                case 39: addNode(res, 39088169, 63245986); break;
                case 40: addNode(res, 63245986, 102334155); break;
        }
}

void addNode(List *lptr, Data i, Data j)
{
    Node *temp;
    if (!lptr->head->next)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->i = i;
        temp->j = j;
        temp->next = NULL;
        lptr->head->next = temp;
    }
    else
    {
        Node *cur;
        for (cur = lptr->head; cur->next; cur = cur->next)
            ;
        temp = (Node *)malloc(sizeof(Node));
        temp->i = i;
        temp->j = j;
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
        printf("%d %d\n", cur->i, cur->j);
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