#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node
{ 
    	struct _Node *next;
	int i, j;
} Node;

typedef struct _List
{
    	Node *head;
	int len;
} List;

int g_board[9][9] = {0};
bool g_mark_row[9][9] = {false};
bool g_mark_col[9][9] = {false};
bool g_mark_box[9][9] = {false};
List* g_zero_list = NULL;

bool checker(int idx);
bool isRightCell(int cell, int i, int j);
int getBox(int i, int j);
void printBoard(void);
void scanBoard(void);
void addNode(List *lptr, int i, int j);
Node* getNode(List *lptr, int idx);
void initList(List **lptrptr);

int main(void)
{
	scanBoard();
	checker(0);
	return 0;
}

void initList(List **lptrptr)
{
    *lptrptr = (List *)malloc(sizeof(List));
    (*lptrptr)->head = (Node*) malloc(sizeof(Node));
    (*lptrptr)->head->next = NULL;
    (*lptrptr)->len = 0;
}

Node* getNode(List *lptr, int idx)
{
    if (lptr->len == 0)
        exit(1);
    else
    {
        Node *cur;
        int i;
        for (cur = lptr->head->next, i= 0; i < idx; cur = cur->next, i++)
            ;
        return cur;
    }
}

void addNode(List *lptr, int i, int j)
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

void scanBoard(void)
{
	int cell, i, j, box;
	g_zero_list = (List*) malloc(sizeof(List));
	initList(&g_zero_list);
	for (i = 0; i < 9; i++) {
		scanf("%d %d %d %d %d %d %d %d %d", &g_board[i][0], &g_board[i][1], &g_board[i][2], &g_board[i][3], &g_board[i][4], &g_board[i][5], &g_board[i][6], &g_board[i][7], &g_board[i][8]);
		for (j = 0; j < 9; j++)
			g_board[i][j]--;
	}

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			cell = g_board[i][j]; // for indexing
			if (cell == -1) {
				addNode(g_zero_list, i, j);
				continue;
			}
			box = getBox(i, j);
			g_mark_box[box][cell] = true;
			g_mark_col[j][cell] = true;
			g_mark_row[i][cell] = true;
		}
	}
}

void printBoard(void)
{
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 8; j++) {
			printf("%d ", g_board[i][j]+1);
		}
		printf("%d\n", g_board[i][j]+1);
	}
}

int getBox(int i, int j)
{
	int ret;
	switch(i) {
		case 0: case 1: case 2: 
			switch(j) {
				case 0: case 1: case 2: ret = 0; break;
				case 3: case 4: case 5: ret = 1; break;
				default: ret = 2; 
			}
			break;
		case 3: case 4: case 5: 
			switch(j) {
				case 0: case 1: case 2: ret = 3; break;
				case 3: case 4: case 5: ret = 4; break;
				default: ret = 5; 
			}
			break;
		default:
			switch(j) {
				case 0: case 1: case 2: ret = 6; break;
				case 3: case 4: case 5: ret = 7; break;
				default: ret = 8; 
			}
	}

	return ret;
}


bool isRightCell(int cell, int i, int j)
{
	int box = getBox(i, j);
	return !(g_mark_box[box][cell] || g_mark_col[j][cell] || g_mark_row[i][cell]);
}

bool checker(int idx)
{
	int box;
	bool b, r, c;
	if (idx == g_zero_list->len) {
		printBoard();
		return true;
	}

	Node* cur = getNode(g_zero_list, idx);
	for (int cell = 0; cell < 9; cell++) {
		if (isRightCell(cell, cur->i, cur->j)) {
			b = false; r = false; c = false;
			box = getBox(cur->i, cur->j);
			g_board[cur->i][cur->j] = cell;
			if (!g_mark_box[box][cell]) {
				b = true;
				g_mark_box[box][cell] = true;
			}
			if (!g_mark_row[cur->i][cell]) {
				r = true;
				g_mark_row[cur->i][cell] = true;
			}
			if (!g_mark_col[cur->j][cell]) {
				c = true;
				g_mark_col[cur->j][cell] = true;
			}
			if (checker(idx+1)) return true;
			if (b) {
				g_mark_box[box][cell] = false;
			}
			if (r) {
				g_mark_row[cur->i][cell] = false;
			}
			if (c) {
				g_mark_col[cur->j][cell] = false;
			}
		} 
	}
	return false;
}