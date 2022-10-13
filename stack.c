/*****
 * Project 03: Maze
 * COSC 208, Introduction to Computer Systems, Spring 2022
 *****/

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Return a pointer to a newly-heap-allocated struct stack. Don't forget to
 * initialize the contents of the struct!
 */
struct stack *stack_new() {     
  // TODO
  printf("TODO: implement stack_new\n"); 
  return NULL;
}

/*
 * Create a new heap-allocated struct node to store the square passed as a 
 * parameter. The square has already been allocated on the heap; do NOT create
 * another copy of the square on the heap.
 */
void stack_push(struct stack *stk, struct square *sq) {     
  // TODO
  printf("TODO: implement stack_push\n"); 
}

/*
 * Returns a reference to the square stored on the heap.
 * Deallocate the heap-allocated struct node that is popped from stk. 
 */
struct square *stack_pop(struct stack *stk) {      
  // TODO
  printf("TODO: implement stack_pop\n"); 
  return NULL;
}

/*
 * Completely free the memory consumed by a struct stack, including each node 
 * and the struct stack itself. Do NOT deallocate the squares referenced by
 * the nodes on the stack; this will be handled elsewhere.
 */
void stack_free(struct stack *stk) {     
  //TODO
  printf("TODO: implement stack_free\n");        
}

/*
 * Print content of stack passed as a parameter from top to bottom.
 */
void stack_print(struct stack *s) {     
  if (s == NULL) {
      printf("Stack not allocated\n");
      return;
  } else {
    struct node *iter = s->top;

    if (iter == NULL) {
      printf("Empty stack\n");
    }

    while (iter != NULL) {
      struct square *sq = iter->sq;
      printf("Square[type=%c,standing=%c,row=%d,col=%d,parent=%p]\n", 
        sq->type, sq->standing, sq->row, sq->col, sq->parent);
      iter = iter->next;
    }
  } 
}