#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

/* FYI, predefined macro and data types are as below.  */
/*
typedef char DATA_TYPE;

typedef struct node_t
{
	DATA_TYPE item;
	struct node_t* next;
} node;

typedef struct
{
	node* head;
	int len;
} linkedlist_t;
*/

void init_list(linkedlist_t* plist)
{
	/* write your own code here. */
	plist->len = 0;
	plist->head = 0x0;
}

bool is_empty(linkedlist_t* plist)
{
	bool ret;
	/* write your own code here. */
	if (plist->len == 0) ret = true;
	else ret = false;

	return ret;
}

void insert_first(linkedlist_t* plist, DATA_TYPE item)
{
	/* write your own code here. */
	node* new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	if (is_empty(plist)) {
		new_node->next = 0x0;
		(plist->head) = new_node;
	} else {
		new_node->next = (plist->head);
		(plist->head) = new_node;
	}
	(plist->len)++;
}

void insert_middle(linkedlist_t* plist, int pos, DATA_TYPE item)
{
	/* write your own code here. */
	if (pos==0) insert_first(plist, item);
	else if (pos==plist->len) insert_last(plist, item);
	else {
		if (pos<0 || pos > plist->len) exit(1); //error: there's no positinon ('pos' th)
		int k;
		node *cur_node, *new_node, *temp_node_ptr;
		cur_node = plist->head;
		for (k=0; k<pos-1 && cur_node->next; k++)
			cur_node = cur_node->next; // move to pos-1 th;
		if (cur_node->next){ //it isn't last
			new_node = (node*)malloc(sizeof(node));
			new_node->item = item;
			temp_node_ptr = cur_node->next;
			cur_node->next = new_node;
			new_node->next = temp_node_ptr;
			(plist->len)++;
		}  
	}
}

void insert_last(linkedlist_t* plist, DATA_TYPE item)
{
	/* write your own code here. */
	if (is_empty(plist)) 
		insert_first(plist, item);
	else  {
		node *cur_node, *new_node;
		cur_node = plist->head;
		for (;cur_node->next;)
			cur_node = cur_node->next;
			; // move to last position 
		new_node = (node*)malloc(sizeof(node));
		new_node->item = item;
		new_node->next = 0x0;
		cur_node->next = new_node;
		(plist->len)++;
	}
}

void remove_first(linkedlist_t* plist)
{
	/* write your own code here. */
	if (is_empty(plist)) return; // error: empty list
	node* rmed_node = plist->head;
	plist->head = (plist->head)->next;
	(plist->len)--;
	free(rmed_node);
}

void remove_middle(linkedlist_t* plist, int pos)
{
	/* write your own code here. */
	if (pos==0) remove_first(plist);
	else {
		if (pos<0 || plist->len-1<pos) exit(1); // error: there's no position pos
		int k;
		node *cur_node, *rmed_node;
		cur_node = plist->head;
		rmed_node = plist->head;
		for (k=0; k<pos-1; k++)
			cur_node = cur_node->next; // move to pos-1 th;
		for (k=0; k<pos; k++)	 //move to pos th;
			rmed_node = rmed_node->next;
		cur_node->next = rmed_node->next;
		free(rmed_node);
		(plist->len)--;
	}
}

DATA_TYPE read_item(linkedlist_t* plist, int pos)
{
	DATA_TYPE ret;
	/* write your own code here. */
		/* write your own code here. */
		if (pos<0 || plist->len <= pos) exit(1);// error: ther's no postion pos
		int k;
		node *cur_node;
		cur_node = plist->head;
		for (k=0; k<pos; k++)
			cur_node = cur_node->next; // move to pos th;
		ret = cur_node->item;
	return ret;
}

void replace_item (linkedlist_t* plist, int pos, DATA_TYPE orig, DATA_TYPE rep)
{
	/* write your own code here. */
	if (read_item(plist, pos) == orig){
		remove_middle(plist, pos);
		insert_middle(plist, pos, rep);
	}; // error: didn't match list item
}

void print(linkedlist_t* plist)
{
	/* write your own code here. */
	int i;
	int len = plist->len;
	for (i=0; i<len; i++) 
		printf("%c", read_item(plist, i));
	printf("\n");
}

void clear(linkedlist_t* plist)
{
	/* write your own code here. */
	int i;
	for (;!is_empty(plist); )
		remove_first(plist);
}

//NOTE: DO NOT define main function 