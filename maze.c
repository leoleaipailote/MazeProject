/*****
 * Project 03: Maze
 * COSC 208, Introduction to Computer Systems, Fall 2022
 *****/

#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

//helper function prototype 
void maze_squares_fill(struct maze*, FILE *);

/*
 * Return a newly-heap-allocated maze struct filled with data from the passed 
 * file.
 * 
 * The provided starter code only echos the content of the file at the console
 * using the partially implemented helper function called maze_squares_fill.
 * Make sure to allocate the struct maze and fill its content according to the * content of the file.
 */
struct maze *maze_new(const char *filename) {     
  //TOUPDATE/COMPLETE
  int rows, cols;
  FILE *in_file;
  in_file = fopen(filename, "r");

  struct maze *ret = malloc( sizeof(struct maze) );
    
  if (in_file == NULL) {
    printf("Can't open file for reading.\n");
  }
  else {
    fscanf(in_file, "%d %d\n", &rows, &cols);
    printf("rows %d and columns %d \n", rows, cols);

    (*ret).rows = rows;
    ret->cols = cols;

    struct square **gr = malloc( sizeof( struct square *) * rows);

    //creating space for the columns ; making space for the pointers to the squares 
    for (int i = 0; i < rows; i++){
        gr[i] = malloc( sizeof( struct square ) * cols);
    }

    ret->grid = gr;

    maze_squares_fill(ret, in_file);
    fclose(in_file);
  }

  return ret;
}

/*
 * Populate the struct maze with grid data from the file.
 *
 * The provided starter only echos the content of the file maze1 at the 
 * console. 
 * 
 * Notice:
 *  - mz is NULL when called by incomplete maze_new function <- change once you 
 *    allocate the struct
 *  - Hard-coded nested loop to read the cols of each row: 3x3 which works with
 *    maze1
 *  - Code should use and update the passed struct maze 
 */
void maze_squares_fill(struct maze* mz, FILE *fptr) {     

  //going through each space on the 2-D array and filling them with squares
  for(int i = 0; i < mz->rows; i++) {
	  for(int j = 0; j < mz->cols; j++){
   	  char ch = fgetc(fptr);
      printf("%c ", ch);

      //creating the square and the corresponding pointer that will hold the information for each 
      //space on the array. Also filling out the grid from the maze
      struct square holder = {EMPTY, TOEXPLORE, i, j, NULL};
      struct square *ptr = &holder;

      ptr->type = ch;
    
      (*mz).grid[i][j] = *ptr;

      //setting the start and exit squares if the corresponding types are shown in the file 
      if( ch == START){
        mz->start = &(*mz).grid[i][j];
      }else if( ch == EXIT){
        mz->exit = &(*mz).grid[i][j];
      }
    }
    
    printf("\n");
   	fgetc(fptr); // Consume newline
  }
}

//freeing heap space so we don't have memory leak
void maze_free(struct maze *mz) {     

  //freeing the cols ; freeing the pointers to the square structs
  for(int i = 0; i < mz->rows; i++){
    free( (*mz).grid[i] );
  }
  
  //freeing the rows ; freeing the pointers to the pointers to square structs
  free( mz->grid );

  //freeing the maze pointer
  free( mz );
}

/*
 * Print the content of a struct square (for debugging purposes).
 */
void square_print(const struct square *sq) {     
  if (sq != NULL) {
    printf("Square at %d %d ", sq->row, sq->col);
    printf("is of type %c, and has standing '%c'\n", sq->type, sq->standing);
  } else {
    printf("square_print: the square provided is NULL\n"); 
  }
}

/*
 * Print the grid array of the struct maze passed at the console. 
 */
void maze_print(const struct maze* mz) {     
  if (mz != NULL) {
    int i, j;
    // print row of column numbers 
    printf("  ");
    for(i = 0; i < mz->cols; i++)
        printf("%d ", i % 10);   // digit only
    printf("\n");

    // print maze starting w/ row numbers
    for(i = 0; i < mz->rows; i++) {
            printf("%d ", i % 10);
        for(j = 0; j < mz->cols; j++) {
            struct square* sq = &mz->grid[i][j]; 
            if (sq->standing == ONPATH) {
                printf("X ");
            } else {
                printf("%c ", sq->type);
            } 
        }
        printf("\n");
    } 
  } else {
    printf("maze not allocated\n");
  }
}
