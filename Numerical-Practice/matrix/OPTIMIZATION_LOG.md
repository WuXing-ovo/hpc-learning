# Matrix Multiplication Optimization Log

## Baseline

### Implementation

The native `matrix_multiply()` implementation relies on an i-j-k loop structure, which leads to suboptimal performance as matrix dimensions scale. Benchmarks accross sizes 64 to 1024 reveal that efficiency peaks at $N=128$ or $256$, followed by a sharp decline. Then the efficiency quickly decreases with larger sizes.

This is due to the non-squential memory access patters of the i-j-k loop, which hinder effective CPU caching. Since the data is not contiguous, the CPU frequently encounters cache misses and must stall while fetching data from main memory. As dimensions increases, the cache miss rate also scales rapidly.

### Performance Data

| Matrix Size | Time (ms)   | GFLOPS |
| ----------- | ----------- | ------ |
| 64          | 0.493348    | 1.06   |
| 128         | 3.669852    | 1.14   |
| 256         | 29.749145   | 1.13   |
| 512         | 318.380984  | 0.84   |
| 1024        | 4133.360043 | 0.52   |

Average GFLOPS: 0.94

Max GFLOPS: 1.14

### Visualization

![time vs size of baseline](results/figures/time_vs_size_baseline.png)
![GFLOPS vs size of baseline](results/figures/gflops_vs_size_baseline.png)
