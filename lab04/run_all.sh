#!/bin/bash
THREADS="1 2 4 8 16"
echo "=== serial ===" > results.txt
./pi_serial 2>&1 | tee -a results.txt

for PROG in lab04_race lab04_critical lab04_atomic lab04_reduction; do
  echo "==== $PROG ====" >> results.txt
  for t in $THREADS; do
    export OMP_NUM_THREADS=$t
    echo "threads=$t" >> results.txt
    ./"$PROG" 2>&1 | tee -a results.txt
  done
done
