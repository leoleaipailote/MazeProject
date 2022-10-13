CC = gcc
CFLAGS = -g -Wall -std=c11
LIBS = libmaze.so libstack.so
BINS = test_stack test_maze
.PHONY : clean

all: $(LIBS) $(BINS)

test_%: test_%.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $< -L. -lmaze -lstack

clean:
	rm -f $(BINS) $(LIBS)

lib%.so: %.c
	$(CC) $(CFLAGS) -shared -o $@ $<