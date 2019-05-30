#HPC Makefile
UNAME_S := $(shell uname -s)

COMPILER = gcc
MPI_COMPILER = mpicc
FLAGS = -fopenmp
MPI_FLAGS= -DMPI
FILES = $(shell find src/ -name "*.c")
APP_NAME = bin/quick

all: main

main: $(FILES)
	$(COMPILER) $(FLAGS) $(FILES) -o $(APP_NAME)

mpi: $(FILES)
	$(MPI_COMPILER) $(FLAGS) $(MPI_FLAGS) $(FILES) -o $(APP_NAME)

mpi_psrs:
	$(MPI_COMPILER) $(MPI_FLAGS) ./lib/PSRS.c -o ./bin/psrs_mpi

clean:
	rm $(APP_NAME)

