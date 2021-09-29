#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* data_t;
typedef struct {
    data_t* items;
    int top;
    int max_stack;
} stack_t;

// Make stack empty.
void initStack(stack_t* pstack);
// Check whether stack is full.
bool isFullStack(stack_t* pstack);
// check whether stack is empty.
bool isEmptyStack(stack_t* pstack);
// Insert an item(DATA_TYPE) at the top.
void pushStack(stack_t* pstack, data_t item);
// Remove the item at the top.
data_t popStack(stack_t* pstack);

#endif