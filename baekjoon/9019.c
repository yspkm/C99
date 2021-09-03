#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN_QUEUE 4096
#define MAXLEN_OPTS 16 

typedef struct _sdata_t {
	short n;
	char opt_str[MAXLEN_OPTS+1];
}data_t; 

typedef struct queue_t{
	int front, rear;
	data_t items[MAXLEN_QUEUE];
}queue_t;

void BFS (void);
short evalExpr (char opt, short opd);
void dequeue(queue_t* q_ptr);
void enqueue(queue_t* q_ptr, short n, char* prev_str, char new_opt);
data_t* peek(queue_t* q_ptr);
bool is_empty(queue_t* q_ptr);
bool is_full(queue_t* q_ptr);
void init_queue(queue_t* q_ptr, short n);

queue_t g_bfs_queue = {0, 0, {0}};
bool g_bfs_mark[10000] = {false};
short g_a=0, g_b=0;
char* g_res_opt_str = NULL;
char g_printfBuffer[10000 * 17] = {0};
int g_idx = 0;

int main(void) {
	int t=0, i=0;

	scanf("%d", &t);
	for (i = 0; i < t; i++) {
		scanf("%hd %hd", &g_a, &g_b);
		BFS();
	}
	g_printfBuffer[g_idx] = '\0';
	printf("%s", g_printfBuffer);

	return 0;
}

void init_queue(queue_t* q_ptr, short n) {
	q_ptr->front = 0;
	q_ptr->rear = 1;
	q_ptr->items[q_ptr->rear].n = n; 
	q_ptr->items[q_ptr->rear].opt_str[0] = '\0'; 
}

bool is_full(queue_t* q_ptr){
	bool res;
	if (q_ptr->front == 0) res = (q_ptr->rear == MAXLEN_QUEUE-1);
	else res = ((q_ptr->front - q_ptr->rear) == 1);
	return res;
}

bool is_empty(queue_t* q_ptr){
	bool res = false;
	if (q_ptr->rear == q_ptr->front)
		res = true;
	return res;
}

data_t* peek(queue_t* q_ptr){
	data_t* res;
	int index = (q_ptr->front + 1) % MAXLEN_QUEUE;
	res = &(q_ptr->items[index]);
	return res;
}

void enqueue(queue_t* q_ptr, short n, char* prev_str, char new_opt){
	if (is_full(q_ptr)){/*printf("the queue is full\n");*/ return;}
	q_ptr->rear = (q_ptr->rear+1) % MAXLEN_QUEUE;
	q_ptr->items[q_ptr->rear].n = n;
	strcpy(q_ptr->items[q_ptr->rear].opt_str, prev_str);
	int i = strlen(prev_str);
	q_ptr->items[q_ptr->rear].opt_str[i] = new_opt;
	q_ptr->items[q_ptr->rear].opt_str[i+1] = '\0';
}

void dequeue(queue_t* q_ptr){
	if (is_empty(q_ptr)){/*printf("the queue is empty\n");*/ return;}
	q_ptr->front = (q_ptr->front + 1) % MAXLEN_QUEUE;
}

short evalExpr (char opt, short opd){
	switch (opt) {
		case 'D':
			return (2 * opd ) % 10000;
		case 'S':
			return opd == 0 ? 9999 : opd - 1;
		case 'L':
			return (opd % 1000) * 10 + opd / 1000;
		case 'R':
			return (opd % 10) * 1000 + (opd / 10);
	}
	return -1; //error
}

void BFS (void)
{
	char temp[17] = {'\0'};
	init_queue(&g_bfs_queue, g_a);
	memset(g_bfs_mark, false, 10000);
	g_bfs_mark[g_a]	= true;
	int i;
	short new_n;
	char opt;
	data_t* cur_item = NULL;

	for (;!is_empty(&g_bfs_queue);) {
		cur_item = peek(&g_bfs_queue);
		if (cur_item->n == g_b) {
			for (i = 0; i < strlen(cur_item->opt_str); i++) {
				g_printfBuffer[g_idx++] = cur_item->opt_str[i];
			}
			g_printfBuffer[g_idx++] = '\n';
			break;
		}
		dequeue(&g_bfs_queue);
		for (i = 0; i < 4; i++) {
			switch (i) {
				case 0: opt = 'D'; break;
				case 1: opt = 'S'; break;
				case 2: opt = 'L'; break;
				case 3: opt = 'R'; break;
			}
			new_n = evalExpr(opt, cur_item->n);
			if (g_bfs_mark[new_n] == false) {
				g_bfs_mark[new_n] = true;
				enqueue(&g_bfs_queue, new_n, cur_item->opt_str, opt);
			}
		}
	}
}