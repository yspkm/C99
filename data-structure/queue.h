#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef void* data_t;
typedef struct _queue_s{
	data_t* items;
	int max_queue;
	int front;
	int rear;
}queue_t;

void initQueue(queue_t* q); // Make a queue empty.
bool isFullQueue(queue_t* q); // Check wheter a queue is full.
bool isEmptyQueue(queue_t* q); // Check wheter a queue is empty.

void pushQueue(queue_t* q, data_t item); // Insert an item at the rear.
data_t popQueue(queue_t* q); // Read and Delete an item at the front

#endif