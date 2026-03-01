import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent


df = pd.read_csv(BASE_DIR / "results.csv")

# Header of data
versions = df["version"].unique()

for version in versions:
    # Print basic information
    data = df[df["version"] == version]
    print(f"=== {version} Performance ===")
    print(f"Matrix sizes: {data['size'].tolist()}")
    print(f"Average GFLOPS: {data['gflops'].mean():.2f}")
    print(f"Min GFLOPS: {data['gflops'].min():.2f}")
    print(f"Max GFLOPS: {data['gflops'].max():.2f}")
    print()

    # Figure 1: time-taken vs matrix sizes
    plt.figure(figsize=(10, 6))
    plt.plot(data["size"], data["time_ms"], "o-", linewidth=2, label=f"Measured ({version})")
    # Draw reference line
    n0 = data["size"].iloc[0]
    t0 = data["time_ms"].iloc[0]
    theoretical_n3 = t0 * (data["size"] / n0) ** 3
    plt.plot(
        data["size"],
        theoretical_n3,
        "--",
        color="gray",
        alpha=0.6,
        label="Theoretical $O(n^3)$",
    )
    # Adjust scales
    plt.xscale("log")
    plt.yscale("log")
    # Add labels, title, grid, legend
    plt.xlabel("Matrix Size")
    plt.ylabel("Execution Time (ms)")
    plt.title(f"Matrix Multiplication: Execution Time vs Size ({version})")
    plt.grid(True, which="both", ls="-", alpha=0.2)
    plt.legend()
    # Save
    plt.savefig(
        BASE_DIR / "figures" / f"time_vs_size_{version}.png",
        dpi=300,
        bbox_inches="tight",
    )

    # Figure 2: GFLOPS vs matrix sizes
    plt.figure(figsize=(10, 6))
    plt.plot(data["size"], data["gflops"], "o-", linewidth=2)
    plt.xlabel("Matrix Size")
    plt.ylabel("GFLOPS")
    plt.title(f"Matrix Multiplication: GFLOPS vs Size ({version})")
    plt.grid(True)
    plt.savefig(
        BASE_DIR / "figures" / f"gflops_vs_size_{version}.png",
        dpi=300,
        bbox_inches="tight",
    )

    plt.close('all')

# plt.show()
