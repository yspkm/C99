#include "heap.h"

void initHeap(Heap *ptr_heap) // Make a heap empty.
{
	ptr_heap->num = 0;
}

bool isEmpty(Heap *ptr_heap) // check whether a heap is empty.
{
	return ptr_heap->num == 0;
}

bool isFull(Heap *ptr_heap)  // Check whether a heap is full.
{
	return ptr_heap->num == MAX_HEAP;
}

void insertData(Heap * ptr_heap, Data data,int priority) // Insert a node to the heap.
{
	HNode new_node;
	int idx = ptr_heap->num + 1;
	if (IsFull(ptr_heap)) exit(1);
	//Compare the new node with its parent.
	while(idx > 1) { 
		int parent = GetParent(idx);
		if (priority > ptr_heap->items[parent].priority) {
			ptr_heap->items[idx] = ptr_heap->items[parent];
			idx = parent;
		}
		else break;
	}
	new_node.data = data;
	new_node.priority = priority;

	ptr_heap->items[idx] = new_node;
	ptr_heap->num++;
}

Data deleteData(Heap* ptr_heap) // Remove the maximum data from the heap.
{
	Data max = ptr_heap->items[1].data;
	HNode last = ptr_heap->items[ptr_heap->num];
	int parent = 1, child;
	//Compare the root with its child nodes.
	while(child = GetHighPrioityChild(ptr_heap, parent)) {
		if (last.priority < ptr_heap->items[child].priority) {
			ptr_heap->items[parent] = ptr_heap->items[child];
			parent = child;
		}
		else break;
	} 

	ptr_heap->items[parent] = last;
	ptr_heap->num--;
	
	return max;
}

//Utility functions
int getParent(int idx) // Get a parent index for a given index.
{
	return idx / 2;
}

int getLChild(int idx) // Get a left child index for a given index.
{
	return idx * 2;
}

int getRChild(int idx) // Get a right child index for a given index.
{
	return idx * 2 + 1;
}

int getHighPrioityChild(Heap *ptr_heap, int idx)// Get a child index with high priority between two child nodes.
{
	if (getLChild(idx) > ptr_heap->num) // No child nodes exist.
		return 0;
	else if (getLChild(idx) == ptr_heap->num) // Exist a left child only
		return getLChild(idx);
	else {
		int left = getLChild(idx), right = getRChild(idx);
		if (ptr_heap->items[left].priority > ptr_heap->items[right].priority)
			return left;
		else 
			return right;
	}
}