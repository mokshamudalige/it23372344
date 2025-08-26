CC = gcc
CFLAGS = -Wall -fopenmp

all: parallel_add

parallel_add: parallel_add.c
	$(CC) $(CFLAGS) -o parallel_add parallel_add.c

clean:
	rm -f parallel_add
