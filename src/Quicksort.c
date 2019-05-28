#include "../include/Quicksort.h"
#include "omp.h"


void swap(int* arr, int a, int b)
{
	int t = arr[a];
	arr[a] = arr[b];
	arr[b] = t;
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

void quicksort_openmp_unoptimized_entry(int* arr, int len)
{
	quicksort_openmp_unoptimized(arr,0,len-1);
}

void quicksort_openmp_unoptimized(int* arr, int lo, int hi)
{
	if(lo < hi)
	{
		int part = parition(arr,lo,hi);

		#pragma omp task default(none) firstprivate(arr,lo,part)
		{
			quicksort_serial_unoptimized(arr,lo,part-1);
		}
		#pragma omp task default(none) firstprivate(arr,hi,part)
		{
			quicksort_serial_unoptimized(arr,part+1,hi);
		}
	}
}