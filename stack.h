#ifndef __STACK_H__
#define __STACK_H__

#include "maze.h"

struct node {
    struct node *next;
    struct square *sq;
};

struct stack {
    struct node *top;
};

// TODO: complete in stack.c
struct stack *stack_new();
void stack_push(struct stack*, struct square*);
struct square *stack_pop(struct stack*);
void stack_free(struct stack*);

// Provided in stack.c
void stack_print(struct stack*);

#endif // __STACK_H__