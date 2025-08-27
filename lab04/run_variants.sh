#!/bin/bash
THREADS="1 2 4 8 16"
LOG=results_all.txt
echo "Run started: $(date)" > $LOG
echo "Serial run (baseline):" >> $LOG
./pi_serial 2>&1 | tee -a $LOG

for PROG in lab04_critical lab04_atomic lab04_reduction; do
  echo "==== $PROG ====" | tee -a $LOG
  for t in $THREADS; do
    export OMP_NUM_THREADS=$t
    echo "--- threads=$t ---" | tee -a $LOG
    ./$PROG 2>&1 | tee -a $LOG
    sleep 0.3
  done
done

echo "Run finished: $(date)" >> $LOG
