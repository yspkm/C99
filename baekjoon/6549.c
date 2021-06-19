#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 100000

typedef struct _Node {long long item; struct _Node *next;} Node;
typedef struct _List {Node *head; int len;} List;

typedef int Data;
typedef struct {Data* items; int top; int len;} Stack;

void pop(Stack* pstack);
void push(Stack* pstack, Data item);
bool isEmpty(Stack* pstack);
bool isFull(Stack* pstack);
void initStack(Stack** pstack);
Data peek(Stack* pstack);

void initList(List **lptrptr);
void addNode(List *lptr, long long item);
void printAllNode(List *lptr);

int main(void) 
{
	int n=0, h[LEN]={0}, i;
	long long height, width, area=0;
	List* ans; initList(&ans);
	Stack* stack; initStack(&stack);
	scanf("%d", &n);
	while(n) {
		for (i = 0; i < n; i++){
			scanf("%d", &h[i]);
		}
		area = 0;
        	for (i = 0; i < n; i++) {
            		while (!isEmpty(stack) && (h[peek(stack)] > h[i])) {
                		height = h[peek(stack)];
                		pop(stack);
                		width = i;
                		if (!isEmpty(stack)) width = i - peek(stack) -1;
                		if (width*height > area) area = width * height;
            		}
            		push(stack, i);
        	}
 
        	while (!isEmpty(stack)) {
            		height = h[peek(stack)];
            		pop(stack);
            		width = n;
            		if (!isEmpty(stack)) width = n - peek(stack) -1;
            		if (width*height > area) area = width * height;
		}
		stack->top = -1;
		addNode(ans, area);
		scanf("%d", &n);
        }	
	printAllNode(ans);

	return 0;
}

void addNode(List *lptr, long long item)
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

void initStack(Stack** pstack)
{
	*pstack = (Stack*) malloc(sizeof(Stack));
	(*pstack)->items = (Data*) malloc(sizeof(Data));
	(*pstack)->top = -1;
	(*pstack)->len = 1;
}

bool isFull(Stack* pstack)
{
    return pstack->top == pstack->len -1;
}

bool isEmpty(Stack* pstack)
{
	return pstack->top == -1;
}

void push(Stack* pstack, Data item)
{
	if (isFull(pstack)) {
		Data* temp = (Data*) malloc(sizeof(Data) * pstack->len * 2);
		for (int i = 0; i < pstack->len; i++) {
			temp[i] = pstack->items[i];
		}
		free(pstack->items);
		pstack->items = temp;
		pstack->len *= 2;
	}

	pstack->items[++(pstack->top)] = item;
}

void pop(Stack* pstack)
{
	if (isEmpty(pstack))
		return;

	--(pstack->top);
}

Data peek(Stack* pstack)
{
	if (isEmpty(pstack))
		return '\0';
	return pstack->items[pstack->top];
}