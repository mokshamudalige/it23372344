import csv
import matplotlib.pyplot as plt

threads = []
times = []
with open('avg_times.csv','r') as f:
    rdr = csv.reader(f)
    next(rdr)  # header
    for row in rdr:
        if not row: continue
        threads.append(int(row[0]))
        times.append(float(row[1]))

t1 = times[0]
speedups = [t1 / tm for tm in times]
efficiency = [ (s / th) * 100.0 for s, th in zip(speedups, threads) ]

plt.figure()
plt.plot(threads, times, marker='o')
plt.title('Threads vs Avg Time')
plt.xlabel('Threads')
plt.ylabel('Avg Time (s)')
plt.grid(True)
plt.savefig('time_vs_threads.png', dpi=150, bbox_inches='tight')

plt.figure()
plt.plot(threads, speedups, marker='o')
plt.title('Threads vs Speedup')
plt.xlabel('Threads')
plt.ylabel('Speedup (T1 / TN)')
plt.grid(True)
plt.savefig('speedup_vs_threads.png', dpi=150, bbox_inches='tight')

plt.figure()
plt.plot(threads, efficiency, marker='o')
plt.title('Threads vs Efficiency (%)')
plt.xlabel('Threads')
plt.ylabel('Efficiency (%)')
plt.grid(True)
plt.savefig('efficiency_vs_threads.png', dpi=150, bbox_inches='tight')

print('Saved: time_vs_threads.png, speedup_vs_threads.png, efficiency_vs_threads.png')
