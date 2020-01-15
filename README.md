# stencil3D
Acceleration of a 3-dimensional stencil.

## Usage
Compile project with [CMake](https://cmake.org) build system.
```bash
mkdir build
cd build
cmake ..
make
```

Perform benchmarks.
```bash
make bench
```

Run test suite.
```bash
make test
```

## Speedup results
Speedups compared to baseline version.
![Speedup results](./data/plot/compare_speedup.png)

**Processor:** Intel(R) Xeon(R) CPU E5-2670 v2 @ 2.50GZ

**Compiler:** gcc 4.8.5

### To do
- [x] openmp
- [x] simd
- [ ] openacc
- [ ] tiled
- [ ] cuda
