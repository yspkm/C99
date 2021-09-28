/* 자료구조개론 HW2 */
/* 2017312605 김요셉*/

//implementation of dynamic circular queue
#include "queue.h"

void initQueue(queue_t* q){
	q->items = (data_t*) malloc(sizeof(data_t));
	q->max_queue = 1;
	q->front = 0;
	q->rear = 0;
}

bool isFullQueue(queue_t* q){
	if (q->front == 0) {
		return (q->rear == q->max_queue-1);
	}
	return ((q->front - q->rear) == 1);
}

bool isEmptyQueue(queue_t* q){
	return q->rear == q->front;
}

void pushQueue(queue_t* q, data_t item){
	if (isFullQueue(q)) { // full of array
		data_t* tmp_items = (data_t*) malloc(2 * q->max_queue * sizeof(data_t));
		if (q->front == 0) {
			memcpy(tmp_items, q->items, q->max_queue * sizeof(data_t));
		} else {
			// [0:r]
			memcpy(tmp_items, q->items, (q->rear + 1) * sizeof(data_t));
			// [m*2 - (m-f):m]
			memcpy(&(tmp_items[2 * q->max_queue - (q->max_queue - q->front)]), &(q->items[q->front]), (q->max_queue - q->front) * sizeof(data_t));
			q->front = 2 * q->max_queue - (q->max_queue - q->front);
		}
		free (q->items);
		q->items = tmp_items;
		q->max_queue *= 2;
	}
	q->rear = (q->rear+1) % q->max_queue;
	q->items[q->rear] = item;
}

data_t popQueue(queue_t* q){
	if (isEmptyQueue(q)) {
		printf("error: empty queue\n");
		return NULL;
	}
	data_t ret = q->items[(q->front + 1) % q->max_queue];
	q->front = (q->front + 1) % q->max_queue;
	return ret;
}