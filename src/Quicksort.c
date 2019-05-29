#include "../include/Quicksort.h"
#include "../include/Insertionsort.h"
#include "omp.h"


void swap(int* arr, int a, int b)
{
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
}

int bestofthree(int* arr, int i, int j, int k)
{
	int pivots[3] = {arr[i],arr[j],arr[k]};
	insertionsort(arr,0,3);
	return pivots[1];
}

int parition(int* arr, int lo, int hi)
{
	int pivot = arr[hi];
	int i = lo -1;

	for (int j = lo; j < hi; ++j)
	{
		if(arr[j] <= pivot)
		{
			++i;
			swap(arr,i,j);
		}
	}
	swap(arr,i+1,hi);
	return (i+1);
}

int parition_optimized(int* arr, int lo, int hi)
{
	int pivot = bestofthree(arr,lo,hi,(hi-lo)/2);
	int i = lo -1;

	for (int j = lo; j < hi; ++j)
	{
		if(arr[j] <= pivot)
		{
			++i;
			swap(arr,i,j);
		}
	}
	swap(arr,i+1,hi);
	return (i+1);
}

void quicksort_serial_unoptimized_entry(int* arr, int len)
{
	quicksort_serial_unoptimized(arr,0,len-1);
}

void quicksort_serial_unoptimized(int* arr, int lo, int hi)
{
	if(lo < hi)
	{
		int part = parition(arr,lo,hi);

		quicksort_serial_unoptimized(arr,lo,part-1);
		quicksort_serial_unoptimized(arr,part+1,hi);
	}
}

void quicksort_serial_optimized_entry(int* arr, int len)
{
	quicksort_serial_optimized(arr,0,len-1);
}

void quicksort_serial_optimized(int* arr, int lo, int hi)
{
	if(lo < hi)
	{
		if(hi -lo < 50)
		{
			insertionsort(arr,lo,hi+1);
		}
		else
		{
			int part = parition_optimized(arr,lo,hi);

			quicksort_serial_optimized(arr,lo,part-1);
			quicksort_serial_optimized(arr,part+1,hi);
		}
	}
}

void quicksort_openmp_unoptimized_entry(int* arr, int len)
{
	#pragma omp parallel
	{
		#pragma omp single nowait
		{			
			quicksort_openmp_unoptimized(arr,0,len-1);
		}
	}
}

void quicksort_openmp_unoptimized(int* arr, int lo, int hi)
{
	if(lo < hi)
	{
		int part = parition(arr,lo,hi);

		#pragma omp task
		{
			quicksort_openmp_unoptimized(arr,lo,part-1);
		}
		#pragma omp task
		{
			quicksort_openmp_unoptimized(arr,part+1,hi);
		}
	}
}

void quicksort_openmp_optimized_entry(int* arr, int len, int cutoff)
{
	#pragma omp parallel
	{
			#pragma omp single nowait
			{			
				quicksort_openmp_optimized(arr,0,len-1,cutoff);
			}
	}
}

void quicksort_openmp_optimized(int* arr, int lo, int hi, int cutoff)
{
	if(lo < hi)
	{
		int part = parition_optimized(arr,lo,hi);

		if(hi-lo < cutoff)
		{
			quicksort_serial_optimized(arr,lo,part-1);
			quicksort_serial_optimized(arr,part+1,hi);
		}
		else
		{
			#pragma omp task
			{
				quicksort_openmp_optimized(arr,lo,part-1,cutoff);
			}
			#pragma omp task
			{
				quicksort_openmp_optimized(arr,part+1,hi,cutoff);
			}
		}
	}
}