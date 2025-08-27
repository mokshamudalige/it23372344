#!/bin/bash
BIN=./pi_parallel_sched
THREADS="1 4 8 12 16 20 24"
SCHEDULE="static"   # main experiment schedule (change later if you want)
OUT="avg_times.csv"
echo "threads,avg_time" > $OUT

for t in $THREADS; do
  rm -f times_${t}.txt
  echo "Running threads=$t (schedule=$SCHEDULE)..."
  for run in $(seq 1 10); do
    export OMP_NUM_THREADS=$t
    export OMP_SCHEDULE=$SCHEDULE
    # run program and capture Time taken numeric value
    time_val=$($BIN 2>/dev/null | awk -F'=' '/Time taken/ {gsub(" seconds","",$2); gsub("^ +| +$","",$2); print $2}')
    echo $time_val >> times_${t}.txt
    sleep 0.05
  done
  # average last 7 runs (ignore first 3)
  avg=$(tail -n +4 times_${t}.txt | awk '{sum+=$1} END {print sum/NR}')
  echo "$t,$avg" >> $OUT
  echo "-> threads=$t avg_time=$avg"
done

echo "All done. Averages written to $OUT"
