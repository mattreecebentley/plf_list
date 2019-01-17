# plf_list
A drop-in replacement for std::list with (on average):

* 393% faster insertion
* 57% faster erasure
* 17% faster iteration
* 77% faster sorting
* 70% faster reversal
* 91% faster remove/remove_if
* 63% faster unique
* 811% faster clear (1147900% for trivially-destructible types)
* 1248% faster destruction (6350% for trivially-destructible types)
* 20-24% faster performance overall in ordered use-case benchmarking(insertion, erasure and iteration on the fly and over time)

(Benchmarks performed on a haswell-based CPU under GCC 8.1: http://www.plflib.org/benchmarks_haswell_gcc.htm
Insertion, erasure, and iteration percentages obtained as average of performance across 5 types from char to very large struct)
