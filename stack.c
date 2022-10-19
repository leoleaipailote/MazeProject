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

 //Creating a new stack means we must initialize top which is initially set to null
struct stack *stack_new() {       
  struct stack* l1 = malloc(sizeof(struct stack));
  l1->top = NULL;
  return l1;
}

/*
 * Create a new heap-allocated struct node to store the square passed as a 
 * parameter. The square has already been allocated on the heap; do NOT create
 * another copy of the square on the heap.
 */
void stack_push(struct stack *stk, struct square *sq) {     
   //create a new node which contains the square parameter to push onto the stack  
   struct node* n = malloc(sizeof(struct node));
   n->next = NULL;  
   n->sq = sq;
   //If the stack was previously empty then set the new node to be the top of the stack
   if(stk->top  == NULL){
       stk->top = n;
   }
   //Otherwise set the new node to point to the node that was previously on top of the stack, and set 
   //this new node to be the top of the stack
   else{
       n->next = stk->top;
       stk->top = n;   
   }
}

/*
 * Returns a reference to the square stored on the heap.
 * Deallocate the heap-allocated struct node that is popped from stk. 
 */
struct square *stack_pop(struct stack *stk) { 
  struct node* x = stk->top;
  //If stack is already empty, then nothing can be popped
  if(stk->top == NULL){
    return NULL;
  }
  else{   
    struct square* s = x->sq;
    //If the stack only contains one node, then pop that node and set the stack to be empty.
    if((*x).next == NULL){
      stk->top = NULL;
    }
    //Otherwise pop the top node and set the next node to be the top of the stack
    else{
      stk->top = x->next;
    }
    free(x);
    x = NULL;
    return s;
  }
}

/*
 * Completely free the memory consumed by a struct stack, including each node 
 * and the struct stack itself. Do NOT deallocate the squares referenced by
 * the nodes on the stack; this will be handled elsewhere.
 */
void stack_free(struct stack *stk) {     
  struct node* x = stk->top;
  //If the stack is already empty then we should just free the stack
    if(stk->top == NULL){
        free(stk);
        stk = NULL;
    }
    //Otherwise we have to free each node starting from the top of the stack all the way to the end. 
    //Once we have freed every nodein the stack then we can free the stack itself.
    else{
        struct node* temp = stk->top;
        while(x != NULL){
            x = (*x).next;
            free(temp);
            temp = x;
        }
        free(temp);
        free(stk);
    }      
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
int main(){
}
