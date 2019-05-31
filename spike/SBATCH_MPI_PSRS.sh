#!/bin/sh

#SBATCH --account=icts
#SBATCH --partition=curie

# The line below means you need 1 worker node and a total of 2 cores
#SBATCH --nodes=2 --ntasks=2
#  To evenly split over two nodes use: --ntasks-per-node=2

#SBATCH --time=20:00

#SBATCH --mem-per-cpu=2000

#SBATCH --job-name="GWRRBRA001_POPENMPBATCH"

#SBATCH --mail-user=gwrbra001@myuct.ac.za
#SBATCH --mail-type=BEGIN,END,FAIL

module load compilers/gcc820
module load mpi/openmpi-4.0.1
make mpi_psrs
mpirun -n 2 ./bin/psrs_mpi 10
mpirun -n 2 ./bin/psrs_mpi 100
mpirun -n 2 ./bin/psrs_mpi 1000
mpirun -n 2 ./bin/psrs_mpi 10000
mpirun -n 2 ./bin/psrs_mpi 100000
mpirun -n 2 ./bin/psrs_mpi 1000000
mpirun -n 2 ./bin/psrs_mpi 10000000
mpirun -n 2 ./bin/psrs_mpi 100000000