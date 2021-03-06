#!/bin/sh

#SBATCH --account=icts
#SBATCH --partition=curie

# The line below means you need 1 worker node and a total of 2 cores
#SBATCH --nodes=1 --ntasks=1
#  To evenly split over two nodes use: --ntasks-per-node=2

#SBATCH --time=20:00

#SBATCH --mem-per-cpu=2000

#SBATCH --job-name="GWRRBRA001_SEQBATCH"

#SBATCH --mail-user=gwrbra001@myuct.ac.za
#SBATCH --mail-type=BEGIN,END,FAIL

module load compilers/gcc820
make
./bin/quick quick std 10
./bin/quick quick std 100
./bin/quick quick std 1000
./bin/quick quick std 10000
./bin/quick quick std 100000
./bin/quick quick std 1000000
./bin/quick quick std 10000000
./bin/quick quick std 100000000