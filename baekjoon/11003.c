#include <stdio.h>
#include <stdlib.h>

#define MAX 5000000

typedef struct s_deque_node {
	int idx, val;
	struct s_deque_node *next;
	struct s_deque_node *prev;
} t_deque_node;

typedef struct s_deque {
	struct s_deque_node *first;
	struct s_deque_node *last;
} t_deque;

t_deque *dequeInit(void);
int isEmpty(t_deque *deque);
void pushFront(t_deque *deque, int idx, int val);
void pushBack(t_deque *deque, int idx, int val);
void popFront(t_deque *deque);
void popBack(t_deque *deque);
int peekFrontIdx(t_deque *deque);
int peekFrontVal(t_deque *deque);
int peekBackIdx(t_deque *deque);
int peekBackVal(t_deque *deque);

int ans[MAX] = {0};

int main(void)
{
        int N, L, A, i;
	scanf("%d %d", &N, &L);
	t_deque *dq = dequeInit(); 

        for (i = 0; i < N; i++)
        {
		scanf("%d", &A);
                if (!isEmpty(dq) && peekFrontIdx(dq) <= i - L)
                        popFront(dq);
                while (!isEmpty(dq) && peekBackVal(dq) > A)
                        popBack(dq);
                pushBack(dq, i, A);
                ans[i] = peekFrontVal(dq);
        }

	for (i = 0; i < N-1; i++) {
		printf("%d ", ans[i]);
	}
	printf("%d\n", ans[i]);

        return 0;
}

t_deque *dequeInit(void)
{
	t_deque *deque;

	deque = malloc(sizeof(t_deque));
	deque->first = NULL;
	deque->last = NULL;
	return deque;
}

int isEmpty(t_deque *deque)
{
	return !deque->first || !deque->last;
}

void pushFront(t_deque *deque, int idx, int val)
{
	t_deque_node *node = malloc(sizeof(t_deque_node));
	node->idx = idx;
	node->val = val;
	node->prev = NULL;
	node->next = deque->first;
	if (isEmpty(deque))
		deque->last = node;
	else
		deque->first->prev = node;
	deque->first = node;
}

void pushBack(t_deque *deque, int idx, int val)
{
	t_deque_node *node = malloc(sizeof(t_deque_node));
	node->idx = idx;
	node->val = val;
	node->prev = deque->last;
	node->next = NULL;
	if (isEmpty(deque))
		deque->first = node;
	else
		deque->last->next = node;
	deque->last = node;
}

void popFront(t_deque *deque)
{
	t_deque_node *node;
	node = deque->first;
	deque->first = node->next;
	if (!deque->first)
		deque->last = NULL;
	else
		deque->first->prev = NULL;
	free(node);
}

void popBack(t_deque *deque)
{
	t_deque_node *node;
	node = deque->last;
	deque->last = node->prev;
	if (!deque->last)
		deque->first = NULL;
	else
		deque->last->next = NULL;
	free(node);
}

int peekFrontIdx(t_deque *deque)
{
	if(isEmpty(deque))
		exit(1);
	return deque->first->idx;
}
int peekFrontVal(t_deque *deque)
{
	if(isEmpty(deque))
		exit(1);
	return deque->first->val;
}

int peekBackIdx(t_deque *deque)
{
	if(isEmpty(deque))
		exit(1);
	return deque->last->idx;
}

int peekBackVal(t_deque *deque)
{
	if(isEmpty(deque))
		exit(1);
	return deque->last->val;
}