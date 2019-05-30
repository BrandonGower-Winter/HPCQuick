 #!/bin/sh

#SBATCH --account=icts
#SBATCH --partition=curie

# The line below means you need 1 worker node and a total of 2 cores
#SBATCH --nodes=1 --ntasks=1
#  To evenly split over two nodes use: --ntasks-per-node=2

#SBATCH --time=10:00

#SBATCH --mem-per-cpu=2000

#SBATCH --job-name="GWRRBRA001_QOPENMPBATCH"

#SBATCH --mail-user=gwrbra001@myuct.ac.za
#SBATCH --mail-type=BEGIN,END,FAIL

module load compilers/gcc820
make
./bin/quick quick openmp 10 -reps 10 -avg
./bin/quick quick openmp 100 -reps 10 -avg
./bin/quick quick openmp 1000 -reps 10 -avg
./bin/quick quick openmp 10000 -reps 10 -avg
./bin/quick quick openmp 100000 -reps 10 -avg
./bin/quick quick openmp 1000000 -reps 10 -avg
./bin/quick quick openmp 10000000 -reps 10 -avg
./bin/quick quick openmp 100000000 -reps 10 -avg