# Project 03: Heapify maze solver

## Overview
In this project, you'll implement the heap-based data structures required for a maze solver. 

### Learning objectives
After completing this project, you should be able to:
* Implement linked data structures (e.g., a stack) using dynamically allocate heap memory in C
* Implement 2D arrays using dynamically allocated heap memory in C
* Write functions in C that take pointers as parameters and/or return pointers
* Use valgrind to diagnose memory errors/leaks in C programs 

### Important tips
* Read the entirety of the project description before you write any code.
* Work on the project over multiple sessions. Do not try to complete the project in a single session on the day (before) each part of the project is due. This will give you time to think about how to solve problems, allow you to ask questions, and result in better outcomes.
* Ensure you follow good program design, coding, testing, and debugging practices (details below).

## Getting started 
Clone your repository on your RPi. The code you need to write for this project will be added to the `maze.c` and `stack.c` files included in your repository. Compile your code using `make`.

To run the maze solver on the first maze, run:
```bash
$ LD_LIBRARY_PATH=. ./solver maze/maze1
```

## Maze data structure

### maze representation
A maze is a 2D grid defined in a file, such as those found in the `maze` folder. The file format is as follows:
* the first line contains two integers: number of rows (R) followed by number of columns (C) for the 2D grid, 
* each R line thereafter provides C characters (`.`, `#`, `S`, `E`).  

For example, `maze/maze2` contains the following data
```
7 13
......#......
##.#######.#.
.#.........#.
.#.##..###.#.
...#.....#.#.
.#####.#.#.#.
....S..#..#E.
```

The character values of the maze encode four *types*:
```
`.` - empty 
`#` - wall
`S` - start
`E` - exit
```

### maze structs 
The maze representation is made of two structures in C: `struct square` and `struct maze`, which are defined in `maze.h`. 

A `struct square` consists of 5 fields: 
1. its row in the maze (using zero-based indexing)
2. its column in the maze (using zero-based indexing)
3. a type - a character (as defined in the maze file and explained above; does not change after initialization)
4. a standing with respect to the solver - a character (initialized as `'t'` meaning _to be explored_, and updated by the path finding algorithm to `'e'` when it has been _explored_ and `'x'` when it is _on the path_ connecting the start to the exit of the maze)
5. a parent - a reference to the square before it on the connecting path (initialized to `NULL`, and updated by the path finding algorithm)

A `struct maze` has also 5 fields
1. the total number of rows
2. the total number of columns
3. a reference to the starting `struct square`
4. a reference to the exit `struct square`
5. a dynamically allocated array of `struct squares` which define the maze

### `maze` functions 
You need to complete three functions in `maze.c`:

1. `maze_new` takes a filename (e.g., `"maze/maze1"`) and returns the corresponding
heap allocated `struct maze*` representation. Its `struct square**` field should be a dynamically allocated 2D array (using method 2, "the programmer-friendly way," from _Dive Into Systems_ [Section 2.5.2](https://diveintosystems.org/book/C2-C_depth/arrays.html#_method_2_the_programmer_friendly_way)).
2. `maze_fill_squares` is a helper function used by `maze_new` to read the character grid of the provided file. For now, those values are echoed at the console. You need to store them to initialize the `struct square` of the maze with the appropriate row, column, type, standing, and parent values, as defined above.
3. `maze_free` deallocates the heap memory for the `struct maze*` allocated by `maze_new`.

A `maze_print` function is provided in `maze.c`; use it to debug and display the maze.

## Stack data structure

### stack structs 
Similar to the linked list you implemented in lab 6, your stack uses two structs, which are defined in `stack.h`. The `struct stack` contains a `struct node` field, which is a self-referential structure. 

A `struct stack` holds a pointer to the top of the `stack`—i.e., the last `struct node` pushed on the stack.  If the stack is empty, then the top of the stack should be `NULL`. A `struct node` holds a pointer to a square and a pointer to the next `struct node` in the stack. The bottom node on the stack should not point to anything—i.e., its `next` field should be `NULL`.

For example, the following memory diagram depicts a stack for which `square[0,0]` was first pushed, followed by `square[1,1]`. 

```
  struct stack            struct node                   struct node
┌--------------------┐  ┌------------------------┐  ┌------------------------┐
| struct node *top ~~~~>| struct node *next ~~~~~~~>| struct node *next=NULL |
|                    |  | struct square *sq ~~~┐ |  | struct square *sq ~~~┐ |
└--------------------┘  └----------------------|-┘  └----------------------|-┘
                                               |   ┌-------------┐         |   ┌-------------┐
                                               └~~>| square[1][1]|         └~~>| square[0][0]|
                                                   └-------------┘             └-------------┘
```

### `stack` functions

You need to complete four functions in `stack.c`:

1. `stack_new` allocates and initializes a `struct stack` on the heap. The fields in the `struct stack` should be initialized to represent an empty stack.
2. `stack_push` pushes a heap allocated `struct node` to the top of the passed stack. The `sq` field of this new node is made to point to the `struct square` provided by the user.
3. `stack_pop` removes the `struct node` at the top of the stack and returns the `struct square` previously residing at the top of the stack.   
4. `stack_free` frees all memory consumed by a stack, including each `struct node` and the `struct stack`.

A `stack_print` function is provided in `stack.c`; use it to debug and display the stack.

## Testing and debugging  
We have provided two test programs—`test_maze` and `test_stack`—to help you test your implementations of the above maze and stack functions, respectively. Run them as follows:
```bash
$ LD_LIBRARY_PATH=. ./test_maze
$ LD_LIBRARY_PATH=. ./test_stack
```

These test programs cover the basic behavior, but they are not comprehensive. You should add additional testing code in each of the test programs to cover more cases and run `valgrind` to ensure you have no memory errors or leaks.

If the program compiles without errors or warnings but still doesn't work as expected, then run your code with valgrind. To help diagnose memory leaks, include the command line options `--track-origins=yes` and `--leak-check=full`. For example:
```bash
$ LD_LIBRARY_PATH=. valgrind --track-origins=yes --leak-check=full ./test_maze
```
Valgrind **should not report any leaks or memory errors** when you run `test_maze` or `test_stack` with it.

## Program design

You **must follow good program design and coding practices**, including:
* Using constants — Use the constants defined in `maze.h`. Do not put constant values directly in your code.
* Making multiple commits to your git repository — Do not wait until your entire program is working before you commit it to your git repository. You should commit your code each time you write and debug a piece of functionality (e.g., after writing and testing code to check the binary formula, after writing and testing the code for extending the length of operands, etc.)
* Properly indenting your code — Recall that indentation is not semantically significant in C, but it makes your code much easier to read.
* Include comments — The body of the function must include comments; generally, you should include a comment before each conditional statement, loop, and set of statements that perform some calculation. **Do not** include a comment for every line of code, and **do not** simply restate the code.

## Submission instructions
You should **commit and push** your updated files to your git repository by the deadline.