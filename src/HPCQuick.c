#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/random.h"
#include "../include/Quicksort.h"
#include "omp.h"

void printHelp();

void printHelp()
{
	printf("./bin/quick algorithm implementation n [-o output]\n"
		"\talgorithm - The algorithm to be used\n"
		"\timplementation - The implementation to be used\n"
		"\tn - The number of randomly generated numbers to sort. (Numbers generated are [0-N])\n"
		"\to - (Optional) The name of the file to write the results too. (Defaults to STDOUT)\n");
}



int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Incorrect Args:\n");
		printHelp();
		return 1;
	}

	char* algorithm = argv[1];
	char* impl = argv[2];
	int n = atoi(argv[3]);
	int threads = 2;
	int cutoff = 1000;

	for (int i = 4; i < argc; ++i)
	{
		if(strcmp(argv[i],"-t") == 0)
		{
			++i;
			threads = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-cut") == 0)
		{
			++i;
			cutoff = atoi(argv[i]);
		}
	}

	printf("%s%d\n", "Length of the array: ",n);
	printf("Generating Array...\n");
	int* arr = malloc(sizeof(int) * n);
	if(!arr)
	{
		printf("Not enough memory of the heap for %d ints\n", n);
	}
	populateArr(arr,n);
	printf("Array Created\n");
	if(strcmp(algorithm,"quick") == 0)
	{
		printf("%s\n", "Sorting Algorithm: Quicksort");

		if(strcmp(impl,"std") == 0)
		{
			printf("%s\n", "Version Implementation: Standard");
			clock_t start = clock(), diff;
			quicksort_serial_unoptimized_entry(arr,n);
			diff = clock() - start;
			printf("%f\n",(diff*1000)/(float)CLOCKS_PER_SEC);
		}
		else if(strcmp(impl,"openmp") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMP");
			omp_set_num_threads(threads);
			printf("%s: %d\n", "Number of threads", omp_get_max_threads());
			double time = omp_get_wtime();
			quicksort_openmp_optimized_entry(arr,n,cutoff);
			time = omp_get_wtime() - time;
			printf("%lf\n",(time*1000));
		}
		else if(strcmp(impl,"uopenmp") == 0)
		{
			printf("%s\n", "Version Implementation: Unoptimized OpenMP");
			omp_set_num_threads(threads);
			printf("%s: %d\n", "Number of threads", omp_get_max_threads());
			double time = omp_get_wtime();
			quicksort_openmp_unoptimized_entry(arr,n);
			time = omp_get_wtime() - time;
			printf("%lf\n",(time*1000));
		}
		else if(strcmp(impl,"mpi") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMPI");
		}
		else
		{
			printf("%s\n", "Version not recognized. Please see README.md for a list of available versions.");
		}

	}
	else if (strcmp(algorithm,"parapivot") == 0)
	{
		printf("%s\n", "Sorting Algorithm: Parallel Pivot...");

		if(strcmp(impl,"std") == 0)
		{
			printf("%s\n", "Version Implementation: Standard");
		}
		else if(strcmp(impl,"openmp") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMP");
		}
		else if(strcmp(impl,"mpi") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMPI");
		}
		else
		{
			printf("%s\n", "Version not recognized. Please see README.md for a list of available versions.");
		}

	}
	else
	{
		printf("Algorithm not recognized. Please see README.md for a list of available algorithms\n");
	}
	free(arr);
	return 0;
}