import sys
from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt


def load(csv_path):
    """Shared: strip the benchmark preamble, keep per-N median rows."""
    with open(csv_path) as f:
        lines = f.readlines()
    header_idx = next(i for i, line in enumerate(lines) if line.startswith("name,"))
    df = pd.read_csv(csv_path, skiprows=header_idx)

    df["N"] = df["name"].str.extract(r"/(\d+)_median")
    df = df.dropna(subset=["N"]).copy()
    df["N"] = df["N"].astype(int)
    df["impl"] = df["name"].str.contains("mini").map({True: "mini", False: "std"})
    df["ns_per_elem"] = df["cpu_time"] / df["N"]
    return df


def plot_int(df, out):
    """int run: push_back vs push_back_reserved, mini vs std."""
    df["reserved"] = df["name"].str.contains("reserved")
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5), sharey=True)
    for ax, reserved, title in [(ax1, False, "no reserve"), (ax2, True, "reserved")]:
        sub = df[df["reserved"] == reserved]
        for impl in ["mini", "std"]:
            s = sub[sub["impl"] == impl].sort_values("N")
            ax.plot(s["N"] / 1e6, s["ns_per_elem"], marker="o", label=impl)
        ax.set_title(f"push_back ({title})")
        ax.set_xlabel("N (millions)")
        ax.legend(); ax.grid(True, alpha=0.3)
    ax1.set_ylabel("ns per element (cpu_time)")
    fig.tight_layout(); fig.savefig(out, dpi=130)


def plot_forwarding(df, out):
    """string/Heavy run: push_back vs emplace_back, one panel per impl."""
    df["op"] = df["name"].str.contains("emplace").map(
        {True: "emplace_back", False: "push_back"})
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5), sharey=True)
    for ax, impl in [(ax1, "mini"), (ax2, "std")]:
        sub = df[df["impl"] == impl]
        for op in ["push_back", "emplace_back"]:
            s = sub[sub["op"] == op].sort_values("N")
            ax.plot(s["N"], s["ns_per_elem"], marker="o", label=op)
        ax.set_title(f"{impl}::vector")
        ax.set_xlabel("N (elements)")
        ax.set_xscale("log", base=2)   # handles the 1K->256K span cleanly
        ax.legend(); ax.grid(True, alpha=0.3)
    ax1.set_ylabel("ns per element (cpu_time)")
    fig.tight_layout(); fig.savefig(out, dpi=130)


MODES = {"int": plot_int, "forwarding": plot_forwarding}

if __name__ == "__main__":
    if len(sys.argv) != 3 or sys.argv[1] not in MODES:
        sys.exit(f"usage: {sys.argv[0]} {{{'|'.join(MODES)}}} <results.csv>")
    mode, csv = sys.argv[1], Path(sys.argv[2])
    df = load(df_csv := csv)
    MODES[mode](df, csv.with_suffix(".png"))
    print(f"wrote {csv.with_suffix('.png')}")