#ifndef __MAZE_H__
#define __MAZE_H__

#define EMPTY '.'
#define WALL '#'
#define START 'S'
#define EXIT 'E'

#define TOEXPLORE 't'
#define EXPLORED 'e'
#define ONPATH 'x'

#include "stack.h"

struct square {
    char type; // Use the constants #defined above
    char standing; // Use the constants #defined above
    int row;
    int col;
    struct square *parent;
};

struct maze{
    int rows;
    int cols;
    struct square *start;
    struct square *exit;
    struct square **grid;   
};

// TODO: complete in maze.c
struct maze* maze_new(const char*);
void maze_free(struct maze*);

// Provided in maze.c
void square_print(const struct square*);
void maze_print(const struct maze*);

#endif // __MAZE_H__