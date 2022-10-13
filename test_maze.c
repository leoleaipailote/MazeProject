#include <stdbool.h>
#include <stdio.h>

#include "maze.h"

bool ok = true;

#define XTEST(expr, errmsg)                                                    \
  if (!expr) {                                                                 \
    printf("Failure: %s on line %d of %s\n", errmsg, __LINE__, __FILE__);      \
    ok = false;                                                                \
  }

int main() {
  struct maze *mz1 = maze_new("maze/maze1");
  XTEST((mz1 != NULL), "Maze should not be NULL");
  XTEST((mz1->rows == 3), "Maze 1 should have 3 rows");
  XTEST((mz1->cols == 3), "Maze 1 should have 3 columns");

  XTEST((mz1->start != NULL), "Maze 1's start square should not be NULL");
  XTEST((mz1->start->row == 0), "Maze 1's start square should be in row 0");
  XTEST((mz1->start->col == 0), "Maze 1's start square should be in column 0");
  XTEST((mz1->start->type == START), "Maze 1's start square should have type START ('S')");
  XTEST((mz1->start->standing == TOEXPLORE), "Maze 1's start square should have standing TOEXPLORE ('o')");
  XTEST((mz1->start->parent == NULL), "Maze 1's start square should have parent NULL");
  XTEST((mz1->start == &(mz1->grid[0][0])), "Maze 1's start square should point to the square at coordinates [0][0]");

  XTEST((mz1->exit != NULL), "Maze 1's exit square should not be NULL");
  XTEST((mz1->exit->row == 2), "Maze 1's exit square should be in row 2");
  XTEST((mz1->exit->col == 2), "Maze 1's exit square should be in column 2");
  XTEST((mz1->exit->type == EXIT), "Maze 1's exit square should have type EXIT ('E')");
  XTEST((mz1->exit == &(mz1->grid[2][2])), "Maze 1's exit square should point to the square at coordinates [2][2]");

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      char msg[100];
      sprintf(msg, "Maze 1's square at index %d show have coordinates %d,%d", r*3+c, r, c);
      struct square sq = mz1->grid[r][c];
      XTEST((sq.row == r && sq.col == c), msg);
    }
  }

  maze_free(mz1);

  printf("Run valgrind on test_maze to check for memory errors and leaks\n");
}