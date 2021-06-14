#include <stdio.h>
#include <stdbool.h>

#define MAX_HEAP 100

typedef char Data;
typedef struct _HNode
{
	Data data;
	int priority;
} HNode;

typedef struct _Heap
{
	HNode items[MAX_HEAP + 1];
	int num;
} Heap;

void initHeap(Heap *ptr_heap); // Make a heap empty.
bool isEmpty(Heap *ptr_heap); // check whether a heap is empty.
bool isFull(Heap *ptr_heap);  // Check whether a heap is full.
void insertData(Heap*ptr_heap, Data data,int priority); // Insert a node to the heap.
Data deleteData(Heap* ptr_heap); // Remove the maximum data from the heap.
int getParent(int idx); // Get a parent index for a given index.
int getLChild(int idx); // Get a left child index for a given index.
int getRChild(int idx); // Get a right child index for a given index.
int getHighPrioityChild(Heap *ptr_heap, int idx);// Get a child index with high priority between two child nodes.