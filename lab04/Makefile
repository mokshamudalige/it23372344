CC = gcc
CFLAGS = -Wall -fopenmp

all: pi_serial lab04_race lab04_critical lab04_atomic lab04_reduction

pi_serial: pi_serial.c
	$(CC) $(CFLAGS) -o pi_serial pi_serial.c

lab04_race: lab04_race.c
	$(CC) $(CFLAGS) -o lab04_race lab04_race.c

lab04_critical: lab04_critical.c
	$(CC) $(CFLAGS) -o lab04_critical lab04_critical.c

lab04_atomic: lab04_atomic.c
	$(CC) $(CFLAGS) -o lab04_atomic lab04_atomic.c

lab04_reduction: lab04_reduction.c
	$(CC) $(CFLAGS) -o lab04_reduction lab04_reduction.c

clean:
	rm -f pi_serial lab04_race lab04_critical lab04_atomic lab04_reduction results.txt
