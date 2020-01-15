# stencil3D
An accelerated 3-dimensional stencil.

## Usage
### Compile
Use [CMake](https://cmake.org) build system.
```bash
mkdir build
cd build
cmake ..
make
```

### Test
```bash
make tests
```

### Benchmarks
```bash
make bench
```

### To do
[x] openmp
[x] simd
[ ] openacc
[ ] tiled
[ ] cuda

## Speedup results
![Speedup results](./data/plot/compare_speedup.png)
