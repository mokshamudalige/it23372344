#!/bin/bash
N=${1:-10000000}       # pass N as first arg; default 10,000,000
X=${2:-1.0}            # pass x as second arg
THREADS="1 2 4 8 16"
LOG=results_sum.txt
echo "Run started: $(date)" > $LOG
echo "Parameters: N=$N x=$X" >> $LOG

echo "=== Serial ===" | tee -a $LOG
./sum_serial $N $X 2>&1 | tee -a $LOG

for PROG in sum_race sum_critical sum_atomic sum_reduction; do
  echo "==== $PROG ====" | tee -a $LOG
  for t in $THREADS; do
    export OMP_NUM_THREADS=$t
    echo "--- threads=$t ---" | tee -a $LOG
    ./$PROG $N $X 2>&1 | tee -a $LOG
    sleep 0.2
  done
done

echo "Run finished: $(date)" | tee -a $LOG
