# HPC Assignment

TODO

## Table of Contents:

1. Prerequisites
2. How to use:


## Prerequisites
### OpenMP
install with:
```
sudo apt-get install libomp-dev
```

## How to use:

To run the HPCQuick you first need to compile the application with 'make' and then run the executable as follows:
```
./bin/quick algorithm implementation n [-o output] [-t threads] [-cut cutoff]
algorithm - The algorithm to be used
implementation - The implementation to be used
n - The number of randomly generated numbers to sort. (Numbers generated are [0-N])
o - (Optional) The name of the file to write the results too. (Defaults to STDOUT)
t - (Optional) The number of threads/nodes you want for your parallel code. (default = 2)
cut - (Optional) The threshold at which serial work should be done (default = 1000)
val - (Optional) Validates the array. (Used to check correctness)
reps - (Optional) The number of the times to repeat the algorithm. (default = 1)
```
To use HPCQuick you need to first choose which algorithm you want. The options you have are as follows:

* Quicksort (quick)
* Parallel Pivot (psrs)



