#!/usr/bin/env python3
# parse_results.py
import re, sys, csv

fn = sys.argv[1] if len(sys.argv)>1 else "results_sum.txt"
text = open(fn).read().splitlines()

# find serial time (first 'Serial:' block)
serial_time = None
for i,line in enumerate(text):
    if line.strip().startswith("Serial:"):
        # look for Time taken within next 10 lines
        for j in range(i, min(i+12, len(text))):
            m = re.search(r"Time taken:\s*([0-9.]+)\s*seconds", text[j])
            if m:
                serial_time = float(m.group(1))
                break
        if serial_time is not None:
            break

if serial_time is None:
    # fallback: first "Time taken" in file
    for line in text:
        m = re.search(r"Time taken:\s*([0-9.]+)\s*seconds", line)
        if m:
            serial_time = float(m.group(1)); break

# parse program blocks
results = {}  # results[prog][threads] = time
prog = None
threads = None
prog_header_re = re.compile(r"^====\s*(\S+)\s*====")
thread_re = re.compile(r"---\s*threads=(\d+)\s*---")
time_re = re.compile(r"Time taken:\s*([0-9.]+)\s*seconds")

for line in text:
    h = prog_header_re.match(line)
    if h:
        prog = h.group(1)
        results.setdefault(prog, {})
        threads = None
        continue
    t = thread_re.match(line)
    if t:
        threads = int(t.group(1))
        continue
    m = time_re.search(line)
    if m and prog and threads is not None:
        tval = float(m.group(1))
        results[prog][threads] = tval
        threads = None

# write CSV: program,threads,time,speedup
out_csv = "speedups.csv"
with open(out_csv, "w", newline="") as f:
    w = csv.writer(f)
    w.writerow(["program","threads","time_seconds","speedup_vs_serial"])
    if serial_time is None:
        print("Warning: serial time not found, speedup column will be empty.")
    for prog in sorted(results.keys()):
        for thr in sorted(results[prog].keys()):
            timev = results[prog][thr]
            speed = round(serial_time / timev, 6) if serial_time else ""
            w.writerow([prog, thr, "{:.6f}".format(timev), speed])

# print summary to screen
print("Serial time (seconds):", serial_time)
print("Wrote", out_csv)
print("Summary (program threads time speedup):")
with open(out_csv) as f:
    for i,line in enumerate(f):
        if i<1: continue
        print(line.strip())

