# Makefile for Linked List Symbol Table Testing

CC = gcc
CFLAGS = -Wall -Wextra -g
TARGETS = test_linkedlist compare_performance

all: $(TARGETS)

test_linkedlist: test_linkedlist.c symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -o test_linkedlist test_linkedlist.c symbol_table.c

compare_performance: compare_performance.c symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -o compare_performance compare_performance.c symbol_table.c

clean:
	rm -f $(TARGETS) *.o

run: test_linkedlist
	./test_linkedlist

.PHONY: all clean run
