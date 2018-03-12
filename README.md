# plf_list
A drop-in replacement for std::list with (on average):
* 333% faster insertion
* 81% faster erasure
* 16% faster iteration
* 72% faster sorting
* 492% faster reversal
* 100% faster remove/remove_if
* 62% faster unique
* 826% faster clear (1122550% for trivially-destructible types)
* 618% faster destruction.

- Benchmarks performed on a haswell-based CPU under GCC 7.1.
