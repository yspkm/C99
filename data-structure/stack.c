#include "stack.h"

// Make stack empty.
void initStack(stack_t* s)
{
	s->top = -1;
	s->items = (data_t*) malloc(sizeof(data_t));
	s->max_stack = 1;
}

// Check whether stack is full.
bool isFullStack(stack_t* s)
{
    return s->top == s->max_stack - 1;
}

// check whether stack is empty.
bool isEmptyStack(stack_t* s)
{
	return s->top == -1;
}

// Insert an item(node) at the top.
void pushStack(stack_t* s, data_t item)
{
	if (isFullStack(s)) {
		data_t* tmp_items = (data_t*) malloc(2 * s->max_stack * sizeof(data_t));
		memcpy(tmp_items, s->items, s->max_stack * sizeof(data_t));
		free(s->items);
		s->items = tmp_items;
		s->max_stack *= 2;
	}

	s->items[++(s->top)] = item;
}

// Remove the item at the top.
data_t popStack(stack_t* s)
{
	if (isEmptyStack(s)) {
		printf("error: empty stack\n");
		return NULL;
	}
	return s->items[(s->top)--];
}
