#!/bin/bash
BIN=./pi_parallel_sched
THREADS=24
SCHEDULES=("static" "dynamic,1000" "guided,1000")
OUT="schedule_results_24.csv"
echo "schedule,avg_time" > $OUT
for sched in "${SCHEDULES[@]}"; do
  rm -f tmp_times.txt
  echo "Testing schedule=$sched ..."
  for run in $(seq 1 10); do
    export OMP_NUM_THREADS=$THREADS
    export OMP_SCHEDULE=$sched
    time_val=$($BIN 2>/dev/null | awk -F'=' '/Time taken/ {gsub(" seconds","",$2); gsub("^ +| +$","",$2); print $2}')
    echo $time_val >> tmp_times.txt
    sleep 0.05
  done
  avg=$(tail -n +4 tmp_times.txt | awk '{sum+=$1} END {print sum/NR}')
  echo "$sched,$avg" >> $OUT
  echo "-> $sched avg=$avg"
done
echo "Done. schedule results in $OUT"
