#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/random.h"

void printHelp();


void printHelp()
{
	printf("./bin/quick algorithm implementation n [-o output]\n"
		"\talgorithm - The algorithm to be used\n"
		"\timplementation - The implementation to be used\n"
		"\tn - The number of randomly generated numbers to sort. (Numbers generated are [0-N])\n"
		"\to - (Optional) The name of the file to write the results too. (Defaults to STDOUT)\n");
}



int main(int argc, char const *argv[])
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

	printf("%s%d\n", "Length of the array: ",n);
	printf("Generating Array...\n");
	int arr[n];
	populateArr(arr,n);
	printf("Array Created\n");

	if(strcmp(algorithm,"quick") == 0)
	{
		printf("%s\n", "Sorting Algorithm: Quicksort");

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
			return 1;
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
			return 1;
		}

	}
	else
	{
		printf("Algorithm not recognized. Please see README.md for a list of available algorithms\n");
		return 1;
	}

	return 0;
}