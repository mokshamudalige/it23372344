# plot_ex4.py
import matplotlib.pyplot as plt

threads = []
times = []
speedups = []

with open("results_ex4.txt", "r") as f:
    header_seen = False
    for line in f:
        line = line.strip()
        if not line:
            continue
        # skip header if present
        if not header_seen and line.lower().startswith("threads"):
            header_seen = True
            continue
        parts = line.split()
        # expect: Threads  Avg_Time(s)  Speedup
        if len(parts) >= 3:
            threads.append(int(parts[0]))
            times.append(float(parts[1]))
            speedups.append(float(parts[2]))

# 1) Threads vs Time
plt.figure()
plt.plot(threads, times, marker="o")
plt.title("Threads vs Time")
plt.xlabel("Threads")
plt.ylabel("Time (s)")
plt.grid(True)
plt.savefig("time_vs_threads.png", dpi=150, bbox_inches="tight")

# 2) Threads vs Speedup
plt.figure()
plt.plot(threads, speedups, marker="o")
plt.title("Threads vs Speedup")
plt.xlabel("Threads")
plt.ylabel("Speedup (×)")
plt.grid(True)
plt.savefig("speedup_vs_threads.png", dpi=150, bbox_inches="tight")

print("Saved: time_vs_threads.png and speedup_vs_threads.png")
