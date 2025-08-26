CC = gcc
CFLAGS = -Wall -fopenmp

all: pi_serial pi_parallel

pi_serial: pi_serial.c
	$(CC) $(CFLAGS) pi_serial.c -o pi_serial

pi_parallel: pi_parallel.c
	$(CC) $(CFLAGS) pi_parallel.c -o pi_parallel

clean:
	rm -f pi_serial pi_parallel
