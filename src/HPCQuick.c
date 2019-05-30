#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "../include/random.h"
#include "../include/Quicksort.h"
#include "../include/Insertionsort.h"
#include "../include/Mergesort.h"
#include "../include/PSRS.h"
#include "omp.h"

#ifdef MPI
	#include "mpi.h"
#endif

void printHelp();

void printHelp()
{
	printf("Incorrect Args. Please see REAME for assistance\n");
}


#ifndef MPI
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
	int reps = 1;
	bool validate = false;
	bool avg = false;
	float avgsum = 0;

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
		else if(strcmp(argv[i],"-reps") == 0)
		{
			++i;
			reps = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-val") == 0)
		{
			validate = true;
		}
		else if(strcmp(argv[i],"-avg") == 0)
		{
			avg = true;
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
			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				clock_t start = clock(), diff;
				quicksort_serial_optimized_entry(arr,n);
				diff = clock() - start;

				if(!avg) printf("%f\n",(diff*1000)/(float)CLOCKS_PER_SEC);
				else avgsum += (diff*1000)/(float)CLOCKS_PER_SEC;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);
		}
		else if(strcmp(impl,"ustd") == 0)
		{
			printf("%s\n", "Version Implementation: Unoptimized Standard");
			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				clock_t start = clock(), diff;
				quicksort_serial_unoptimized_entry(arr,n);
				diff = clock() - start;

				if(!avg) printf("%f\n",(diff*1000)/(float)CLOCKS_PER_SEC);
				else avgsum += (diff*1000)/(float)CLOCKS_PER_SEC;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);
			
		}
		else if(strcmp(impl,"qsort") == 0)
		{
			printf("%s\n", "Version Implementation: qsort");

			int cmpfunc (const void * a, const void * b) {
   				return ( *(int*)a - *(int*)b );
			}

			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				clock_t start = clock(), diff;
				qsort(arr,n,sizeof(int),cmpfunc);
				diff = clock() - start;

				if(!avg) printf("%f\n",(diff*1000)/(float)CLOCKS_PER_SEC);
				else avgsum += (diff*1000)/(float)CLOCKS_PER_SEC;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);
		}
		else if(strcmp(impl,"openmp") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMP");
			omp_set_num_threads(threads);
			printf("%s: %d\n", "Number of threads", omp_get_max_threads());

			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				double time = omp_get_wtime();
				quicksort_openmp_optimized_entry(arr,n,cutoff);
				time = omp_get_wtime() - time;

				if(!avg) printf("%lf\n",(time*1000));
				else avgsum += time*1000;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);			
		}
		else if(strcmp(impl,"uopenmp") == 0)
		{
			printf("%s\n", "Version Implementation: Unoptimized OpenMP");
			omp_set_num_threads(threads);
			printf("%s: %d\n", "Number of threads", omp_get_max_threads());
			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				double time = omp_get_wtime();
				quicksort_openmp_unoptimized_entry(arr,n);
				time = omp_get_wtime() - time;

				if(!avg) printf("%lf\n",(time*1000));
				else avgsum += time*1000;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);
		}
		else
		{
			printf("%s\n", "Version not recognized. Please see README.md for a list of available versions.");
		}

	}
	else if (strcmp(algorithm,"psrs") == 0)
	{
		printf("%s\n", "Sorting Algorithm: PSRS...");
		if(strcmp(impl,"openmp") == 0)
		{
			printf("%s\n", "Version Implementation: OpenMP");
			printf("%s: %d\n", "Number of threads", threads);
			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				double time = omp_get_wtime();
				PSRS_openmp_optimized(arr,n,threads,cutoff);
				time = omp_get_wtime() - time;

				if(!avg) printf("%lf\n",(time*1000));
				else avgsum += time*1000;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);

		}
		else if(strcmp(impl,"uopenmp") == 0)
		{
			printf("%s\n", "Version Implementation: Unoptimized OpenMP");
			printf("%s: %d\n", "Number of threads", threads);

			for (int i = 0; i < reps; ++i)
			{
				if(i != 0)
				{
					populateArr(arr,n);
				}
				double time = omp_get_wtime();
				PSRS_openmp_unoptimized(arr,n,threads);
				time = omp_get_wtime() - time;

				if(!avg) printf("%lf\n",(time*1000));
				else avgsum += time*1000;
			}
			if(avg)
				printf("Average: %f\n", avgsum/reps);

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
	if(validate)
	{
		int comp = arr[0];
		for(int i = 1; i < n; ++i)
		{
			if(comp <= arr[i])
			{
				comp = arr[i];
			}
			else
			{
				validate = false;
				break;
			}
		}
		if(validate)
		{
			printf("Array is correct\n");
		}
		else
		{
			printf("Array is incorrect\n");
		}
	}
	free(arr);
	return 0;
}
#else
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
	int reps = 1;
	bool validate = false;
	bool avg = false;
	float avgsum = 0;

	double time;

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
		else if(strcmp(argv[i],"-val") == 0)
		{
			validate = true;
		}
	}

	int* arr;
	int* localdata;
	int localsize;
	int numProcs,rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  	if(rank == 0)
  	{
  		printf("%s%d\n", "Length of the array: ",n);
		printf("Generating Array...\n");
		arr = malloc(sizeof(int) * n);
		if(!arr)
		{
			printf("Not enough memory of the heap for %d ints\n", n);
		}
		populateArr(arr,n);
		printf("Array Created\n");
		time = MPI_Wtime();
  	}

  		localsize = n/numProcs;
  		localdata = malloc (sizeof(int) * localsize);
	   	if (localdata == NULL) {
	     	printf ("\nlocaldata Memory Allocation Failed\n");
	     exit (1);
	   }

	   MPI_Scatter(arr,localsize,MPI_INT,localdata,localsize,MPI_INT,0,MPI_COMM_WORLD);
	   quicksort_serial_optimized_entry(localdata,localsize);
	   MPI_Gather(localdata,localsize,MPI_INT,arr,localsize,MPI_INT,0,MPI_COMM_WORLD);
	   free(localdata);

	   if(rank == 0)
	   {
	   		mergesort_serial(arr,0,n-1);
	   		printf("%lf\n",(MPI_Wtime() -time) * 1000);
	   		if(validate)
			{
				int comp = arr[0];
				for(int i = 1; i < n; ++i)
				{
					if(comp <= arr[i])
					{
						comp = arr[i];
					}
					else
					{
						validate = false;
						break;
					}
				}
				if(validate)
				{
					printf("Array is correct\n");
				}
				else
				{
					printf("Array is incorrect\n");
				}
			}
	   		free(arr);
	   }

	   MPI_Finalize();

	return 0;
}
#endif