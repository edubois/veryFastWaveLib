# Very Fast Wavelet Library (proof of concept)
Proof of concept of a very fast wavelet encoder library (lossless CDF 5/3 - the one that jpeg2000 uses).

This shows how I use SIMD instructions to vectorize the computations of the CDF 5/3 wavelet process.

* Compilation:
make


* Run:

- slow_test1: benchmark without SIMD

```******************* Very Fast Wavelet Codec ****************
* BENCHMARK WITHOUT OPTIMIZATIONS                          *
************************************************************
>Encoding...
Benchmark encoding: 972.629 (ms)
>Decoding...
Benchmark decoding: 851.818 (ms)
Benchmark total: 1824.447 (ms)
>Reconstruction ok```


- fast_test1: benchmark with SIMD on the same algorithm.

```******************* Very Fast Wavelet Codec ****************
* BENCHMARK ON SIMD VECTORIZATION                          *
************************************************************
>Encoding...
Benchmark encoding: 22.604 (ms)
>Decoding...
Benchmark decoding: 15.141 (ms)
Benchmark total: 37.745 (ms)
>Reconstruction ok```


