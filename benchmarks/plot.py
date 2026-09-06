from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

CSV_PATH = Path(__file__).parent / "results.csv"

with open(CSV_PATH) as f:
    lines = f.readlines()
header_idx = next(i for i, line in enumerate(lines) if line.startswith("name,"))

df = pd.read_csv(CSV_PATH, skiprows=header_idx)

# extract N only from "_mean" rows; everything else becomes NaN
df["N"] = df["name"].str.extract(r"/(\d+)_median")

# drop rows that didn't match (raw iterations, _median, _stddev, _cv)
df = df.dropna(subset=["N"]).copy()
df["N"] = df["N"].astype(int)

df["reserved"] = df["name"].str.contains("reserved")
df["impl"] = df["name"].str.contains("mini").map({True: "mini", False: "std"})

# use cpu_time, not real_time -- less noisy, immune to scheduling jitter
df["ns_per_elem"] = df["cpu_time"] / df["N"]

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5), sharey=True)

for ax, reserved, title in [(ax1, False, "no reserve"), (ax2, True, "reserved")]:
    sub = df[df["reserved"] == reserved]
    for impl in ["mini", "std"]:
        s = sub[sub["impl"] == impl].sort_values("N")
        ax.plot(s["N"] / 1e6, s["ns_per_elem"], marker="o", label=impl)
    ax.set_title(f"push_back ({title})")
    ax.set_xlabel("N (millions)")
    ax.legend()
    ax.grid(True, alpha=0.3)

ax1.set_ylabel("ns per element (cpu_time)")
fig.tight_layout()
fig.savefig("bench.png", dpi=130)
print("wrote bench.png")