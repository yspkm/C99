/* 자료구조개론 HW2 */
/* 2017312605 김요셉*/

#include "queue.h"

/* FYI, predefined macro and data types are as below.  */
/*
#define MAX_QUEUE	100

typedef int DATA_TYPE

typedef struct queue_t{
	int front, rear;
	DATA_TYPE items[MAX_QUEUE];
}queue_t;
*/

void init_queue(queue_t* q_ptr){

	/* write your own code here. */
	q_ptr->front = 0;
	q_ptr->rear = 0;
}

bool is_full(queue_t* q_ptr){
	bool res;
	/* write your own code here. */
	if (q_ptr->front == 0) res = (q_ptr->rear == MAX_QUEUE-1);
	else res = ((q_ptr->front - q_ptr->rear) == 1);

	return res;
}

bool is_empty(queue_t* q_ptr){
	bool res;
	/* write your own code here. */
	res = (q_ptr->rear == q_ptr->front);
	return res;
}

DATA_TYPE peek(queue_t* q_ptr){
	DATA_TYPE res;
	/* write your own code here. */
	int index = (q_ptr->front + 1) % MAX_QUEUE;
	res = q_ptr->items[index];
	return res;
}
void enqueue(queue_t* q_ptr, DATA_TYPE item){
	/* write your own code here. */
	if (is_full(q_ptr)){/*printf("the queue is full\n");*/ return;}
	q_ptr->rear = (q_ptr->rear+1) % MAX_QUEUE;
	q_ptr->items[q_ptr->rear] = item;
}
void dequeue(queue_t* q_ptr){
	/* write your own code here. */
	if (is_empty(q_ptr)){/*printf("the queue is empty\n");*/ return;}
	q_ptr->front = (q_ptr->front + 1) % MAX_QUEUE;
}
//DO NOT define main function 
