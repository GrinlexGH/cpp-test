import subprocess
import json
import matplotlib.pyplot as plt
import sys
import os

EXECUTABLE = "../../build/win32-x64-GCC/.output/Release/bitfields.exe"
JSON_FILE = "benchmark.json"
PNG_FILE = "benchmark_plot.png"

if len(sys.argv) > 1:
    EXECUTABLE = sys.argv[1]

if not os.path.isfile(EXECUTABLE):
    print(f"Executable not found: {EXECUTABLE}")
    sys.exit(1)

try:
    print(f"Executing: {EXECUTABLE}")
    result = subprocess.run([EXECUTABLE, "--benchmark_format=json"], capture_output=True, text=True, check=True)
except subprocess.CalledProcessError as e:
    print("Error while running benchmark:")
    print(e.stderr)
    sys.exit(1)

try:
    with open(JSON_FILE, "w") as f:
        f.write(result.stdout)
    data = json.loads(result.stdout)
except Exception as e:
    print("Error while JSON parsing:")
    print(e)
    sys.exit(1)

benchmarks = data.get("benchmarks", [])
entries = []

for b in benchmarks:
    if b.get("run_type") == "aggregate" and b.get("name", "").endswith("_mean"):
        base_name = b["name"].replace("_mean", "")
        struct_name = base_name.split("<")[1].split(">")[0] if "<" in base_name else base_name
        real_time = b["real_time"]

        stddev = next(
            (x["real_time"] for x in benchmarks if x["name"] == f"{base_name}_stddev"),
            0.0
        )
        entries.append((struct_name, real_time, stddev))

if not entries:
    print("There is no aggregate fields in JSON. Make sure you use ->Repetitions(N)->ReportAggregatesOnly(true).")
    sys.exit(1)

labels, times, stddevs = zip(*entries)
plt.figure(figsize=(8, 5))
bars = plt.bar(labels, times, yerr=stddevs, capsize=6, color=["#2980b9", "#c0392b", "#27ae60"])

plt.ylabel("Time (ms)")
plt.title("Bitfields performance comparison")
plt.grid(axis="y", linestyle="--", alpha=0.6)
plt.tight_layout()

for bar, t in zip(bars, times):
    plt.text(bar.get_x() + bar.get_width() / 2, t, f"{t:.1f}", ha="center", va="bottom")

plt.savefig(PNG_FILE, format="png")
print(f"Figure saved: {PNG_FILE}")
