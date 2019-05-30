#!/bin/sh

#SBATCH --account=icts
#SBATCH --partition=curie

# The line below means you need 1 worker node and a total of 2 cores
#SBATCH --nodes=1 --ntasks=1
#  To evenly split over two nodes use: --ntasks-per-node=2

#SBATCH --time=20:00

#SBATCH --mem-per-cpu=2000

#SBATCH --job-name="GWRRBRA001_QOPENMPBATCH"

#SBATCH --mail-user=gwrbra001@myuct.ac.za
#SBATCH --mail-type=BEGIN,END,FAIL

module load compilers/gcc820
make
echo *****2 threads*****
./bin/quick quick openmp 10 
./bin/quick quick openmp 100 
./bin/quick quick openmp 1000
./bin/quick quick openmp 10000
./bin/quick quick openmp 100000
./bin/quick quick openmp 1000000
./bin/quick quick openmp 10000000
./bin/quick quick openmp 100000000
echo *****4 threads*****
./bin/quick quick openmp 10 -t 4
./bin/quick quick openmp 100-t 4
./bin/quick quick openmp 1000 -t 4
./bin/quick quick openmp 10000 -t 4
./bin/quick quick openmp 100000 -t 4
./bin/quick quick openmp 1000000 -t 4
./bin/quick quick openmp 10000000 -t 4
./bin/quick quick openmp 100000000 -t 4
echo *****8 threads*****
./bin/quick quick openmp 10 -t 8
./bin/quick quick openmp 100 -t 8
./bin/quick quick openmp 1000 -t 8
./bin/quick quick openmp 10000 -t 8
./bin/quick quick openmp 100000 -t 8
./bin/quick quick openmp 1000000 -t 8
./bin/quick quick openmp 10000000 -t 8
./bin/quick quick openmp 100000000 -t 8