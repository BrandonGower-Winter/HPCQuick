# HPC Assignment


## Prerequisites
### OpenMP
install with:
```
sudo apt-get install libomp-dev
```

I did not create the mersenne twister and all credit is given to the original author credited at the top of the .c file

## How to use (SERIAL & OPENMP):

To run the HPCQuick you first need to compile the application with 'make' and then run the executable as follows:
```
./bin/quick algorithm implementation n [-t threads] [-cut cutoff] [-val] [-reps x] [-avg]
algorithm - The algorithm to be used
implementation - The implementation to be used
n - The number of randomly generated numbers to sort. (Numbers generated are [0-N])
t - (Optional) The number of threads/nodes you want for your parallel code. (default = 2)
cut - (Optional) The threshold at which serial work should be done (default = 1000)
val - (Optional) Validates the array. (Used to check correctness)
reps - (Optional) The number of the times to repeat the algorithm. (default = 1)
avg - (Optional) Calculates the average time of a given implementation and prints it out.
```
To use HPCQuick you need to first choose which algorithm you want. The options you have are as follows:

* Quicksort (quick)
* Regular Sampled Parallel Sort(psrs)

You then need to choose an implementation.

For Quicksort you have access to:

* std (Serial Quicksort)
* openmp (OpenMp Quicksort)

For psrs you have access to:

* openmp (OpenMP PSRS)

## How to use (MPI Quicksort)

For quicksort compile with 'make mpi'

To run:

```
mpirun -n {num tasks} ./bin/quick quick stub n [-val] [-cut cutoff]
```
## How to use (MPI PSRS)

For quicksort compile with 'make mpi_psrs'
This was not created by me and all credit to the original author is at the top of the .c file.

To run:

```
mpirun -n {num tasks} ./bin/psrs n
```

## How to use (HPC Cluster)
A number of SBATCH scripts have been included in spike/. Run any of them on the cluster to get results.
Please make sure you have a ./bin/ directory before running the scripts.





