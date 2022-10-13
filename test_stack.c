#include <stdbool.h>
#include <stdio.h>

#include "stack.h"

bool ok = true;

#define XTEST(expr, errmsg)                                                    \
  if (!expr) {                                                                 \
    printf("Failure: %s on line %d of %s\n", errmsg, __LINE__, __FILE__);      \
    ok = false;                                                                \
  }

int main() {
  struct square sqA = { EMPTY, EXPLORED, 0, 0, NULL };
  struct square sqB = { WALL, EXPLORED, 1, 1, NULL };
  struct square sqC = { START, EXPLORED, 2, 2, NULL };
  
  struct stack *stk = stack_new();
  XTEST((stk != NULL), "Stack should not be NULL");
  XTEST((stk->top == NULL), "Stack top not initially NULL");
  printf("Initial stack:\n");
  stack_print(stk);

  stack_push(stk, &sqA);
  XTEST((stk->top != NULL),
        "Stack top shouldn't be NULL after pushing one element");
  XTEST((stk->top->next == NULL),
        "With one element in the stack, its next should point to NULL");
  XTEST((stk->top->sq == &sqA), "Top of stack should be square[0,0]");
  printf("Stack after one square pushed:\n");
  stack_print(stk);

  stack_push(stk, &sqB);
  XTEST((stk->top->sq == &sqB),
        "Pushing another element should modify the top of the stack to square[1,1]");
  XTEST((stk->top->next != NULL),
      "With two elements on the stack, the top's next should not point to NULL");
  struct node *second = stk->top->next;
  XTEST((second->sq == &sqA), "Pushing a second element should not modify bottom of stack; should still point to square[0,0]");
  XTEST((second->next == NULL), 
      "With two nodes in the stack, the second node's next should point to NULL");
  printf("Stack after another square pushed:\n");
  stack_print(stk);

  struct square *sq = stack_pop(stk);
  XTEST((sq == &sqB), "Poping should return square[1,1]");
  XTEST((stk->top->sq == &sqA), "Value of top should be square[0,0]");
  printf("Stack after pop:\n");
  stack_print(stk);

  stack_push(stk, &sqC);
  XTEST((stk->top->sq == &sqC),
        "Pushing another element should modify the top of the stack to square[2,2]");
  XTEST(
      (stk->top->next != NULL),
      "With two elements in the stack, the top's next should not point to NULL");
  printf("Stack after another square pushed:\n");
  stack_print(stk);
  
  stack_free(stk);

  printf("Run valgrind on test_stack to check for memory errors and leaks\n");
}