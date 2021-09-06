#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h> //memset

#define MAX_HEAP 20 * 20 - 1
#define MAX_QUEUE	1024

typedef struct _SData {
	int dist;
	int i;			
	int j;
} Data;

typedef struct _HNode
{
	Data data;
	Data priority; 
} HNode;

typedef struct _Heap
{
	HNode items[MAX_HEAP + 1];
	int num;
} heap_t;

typedef struct queue_t{
	int front, rear;
	Data items[MAX_QUEUE];
}queue_t;


void initHeap(heap_t *ptr_heap); // Make a heap empty.
bool isEmpty(heap_t *ptr_heap); // check whether a heap is empty.
bool isFull(heap_t *ptr_heap);  // Check whether a heap is full.
void insertData(heap_t*ptr_heap, Data data, Data priority); // Insert a node to the heap.
Data deleteData(heap_t* ptr_heap); // Remove the maximum data from the heap.
int getParent(int idx); // Get a parent index for a given index.
int getLChild(int idx); // Get a left child index for a given index.
int getRChild(int idx); // Get a right child index for a given index.
int getHighPrioityChild(heap_t *ptr_heap, int idx);// Get a child index with high priority between two child nodes.

void init_queue(queue_t*);	// Make a queue empty.
bool is_full(queue_t*);	// Check wheter a queue is full.
bool is_empty(queue_t*);	// Check wheter a queue is empty.
Data peek(queue_t*);	// Read the item at the front. This function will be called only if the queue is not empty.
void enqueue(queue_t*, Data);	// Insert an item at the rear.
void dequeue(queue_t*);		// Delete an item at the front
bool cmpData(Data a, Data b);

////////////////////////////////////////////////////
//global variables
int board[20][20] = {0};
bool mark[20][20] = {false};
int N = 0, size = 2, eat_n = 0, dist=0;
Data data = {0};


const int di[4] = {-1, 0, 1, 0};
const int dj[4] = {0, -1, 0, 1};

int main(void) {
	queue_t q; init_queue(&q);
	heap_t h; initHeap(&h);
	int ni, nj, tmp_pr, old_i, old_j, old_dist; 
	Data cur;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] == 9) {//shark
				data.i = i;
				data.j = j;
				data.dist = 0;
				enqueue(&q, data);
				mark[i][j] = true;
				board[i][j] = 0;
			}

		}
	}

	for (;;) {
		init_queue(&q);
		enqueue(&q, data);
		initHeap(&h);
		for (;!is_empty(&q);) {
			cur = peek(&q);
			dequeue(&q);
			for (int i = 0;  i < 4; i++) {
				ni = cur.i + di[i];
				nj = cur.j + dj[i];
				if (board[ni][nj] > size || ni < 0 || ni >= N || nj < 0 || nj >= N) {
					continue;
				}
				if (!mark[ni][nj]) {
					data.i = ni;
					data.j = nj;
					data.dist = cur.dist + 1; 
					enqueue(&q, data);
					mark[ni][nj] = true;
					if (0 < board[ni][nj] && board[ni][nj] < size) {
						//tmp_pr = -(data.dist); //negation
						insertData(&h, data, data);
					}
				}
			}
		}

		if (!isEmpty(&h)) {
			eat_n++;
			cur = deleteData(&h);
			board[cur.i][cur.j] = 0;
			data.i = cur.i;
			data.j = cur.j;
			data.dist = cur.dist;
			//enqueue(&q, data);
			dist = data.dist;
			mark[data.i][data.j] = true;
			old_dist = data.dist;
		} else {
			break;
		}
		if (eat_n == size) {
			eat_n = 0;
			size++;
		}
		memset(mark, false, sizeof(mark));
	}
	printf("%d\n", dist);
}

void initHeap(heap_t *ptr_heap) // Make a heap empty.
{
	ptr_heap->num = 0;
}

bool isEmpty(heap_t *ptr_heap) // check whether a heap is empty.
{
	return ptr_heap->num == 0;
}

bool isFull(heap_t *ptr_heap)  // Check whether a heap is full.
{
	return ptr_heap->num == MAX_HEAP;
}

void insertData(heap_t* ptr_heap, Data data, Data priority) // Insert a node to the heap.
{
	HNode new_node;
	int idx = ptr_heap->num + 1;
	if (isFull(ptr_heap)) exit(1);
	//Compare the new node with its parent.
	while(idx > 1) {  
		int parent = getParent(idx);
		if (cmpData(priority, ptr_heap->items[parent].priority)) {
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

Data deleteData(heap_t* ptr_heap) // Remove the maximum data from the heap.
{
	Data max = ptr_heap->items[1].data;
	HNode last = ptr_heap->items[ptr_heap->num];
	int parent = 1, child;
	//Compare the root with its child nodes.
	while(child = getHighPrioityChild(ptr_heap, parent)) {
		if (cmpData(ptr_heap->items[child].priority, last.priority)) {
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

int getHighPrioityChild(heap_t *ptr_heap, int idx)// Get a child index with high priority between two child nodes.
{
	if (getLChild(idx) > ptr_heap->num) // No child nodes exist.
		return 0;
	else if (getLChild(idx) == ptr_heap->num) // Exist a left child only
		return getLChild(idx);
	else {
		int left = getLChild(idx), right = getRChild(idx);
		if (cmpData(ptr_heap->items[left].priority, ptr_heap->items[right].priority))
			return left;
		else 
			return right;
	}
}

void init_queue(queue_t* q_ptr){

	/* write your own code here. */
	q_ptr->front = 0;
	q_ptr->rear = 0;
}

bool is_full(queue_t* q_ptr){
	bool res;
	if (q_ptr->front == 0) res = (q_ptr->rear == MAX_QUEUE-1);
	else res = ((q_ptr->front - q_ptr->rear) == 1);

	return res;
}

bool is_empty(queue_t* q_ptr){
	bool res;
	res = (q_ptr->rear == q_ptr->front);
	return res;
}

Data peek(queue_t* q_ptr){
	Data res;
	int index = (q_ptr->front + 1) % MAX_QUEUE;
	res = q_ptr->items[index];
	return res;
}
void enqueue(queue_t* q_ptr, Data item){
	if (is_full(q_ptr)){/*printf("the queue is full\n");*/ return;}
	q_ptr->rear = (q_ptr->rear+1) % MAX_QUEUE;
	q_ptr->items[q_ptr->rear] = item;
}
void dequeue(queue_t* q_ptr){
	if (is_empty(q_ptr)){/*printf("the queue is empty\n");*/ return;}
	q_ptr->front = (q_ptr->front + 1) % MAX_QUEUE;
}

bool cmpData(Data a, Data b) // if  a > b
{
	if (a.dist > b.dist) {
		return false;
	} else if (a.dist == b.dist){
		if (a.i > b.i) {
			return false;
		} else if (a.i == b.i){
			if (a.j > b.j) {
				return false;
			} else {
				return true;
			}
		} else {
			return true;
		}
	} else {
		return true;
	}
}