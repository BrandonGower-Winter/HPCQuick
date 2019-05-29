#include <stdlib.h>
#include "omp.h"

#include "../include/PSRS.h"
#include "../include/Quicksort.h"
#include "../include/Insertionsort.h"
#include "../include/Mergesort.h"

void sublists(int* arr, int start, int end, int* subsize, int at, int* pivots, int fp, int lp)
{
	int mid = (fp+lp)/2;
	int pv = pivots[mid];
	int lb = start;
	int ub = end;

	while(lb <= ub)
	{
		int center = (lb+ub)/2;
		
		if(arr[center] > pv)
		{
			ub = center - 1;
		}
		else
		{
			lb = center + 1;
		}
	}
	subsize[at+mid] = lb;
	if(fp < mid)
	{
		sublists(arr,start,lb-1,subsize,at,pivots,fp,mid-1);
	}
	if(mid < lp)
	{
		sublists(arr,lb,end,subsize,at,pivots,mid+1,lp);
	}
}

void PSRS_openmp_unoptimized(int* arr, int n, int p)
{
	int size = (n+p-1)/p;
	int rsize = (size + p-1)/p;
	int* sample = malloc(sizeof(int) * (p * (p-1)));
	int* pivots = malloc(sizeof(int) * (p-1));
	int* subsize = malloc(sizeof(int) * (p*(p+1)));
	int* bucksize = malloc(sizeof(int) * p);
	#pragma omp parallel shared(size,rsize,sample,pivots,subsize,bucksize) num_threads(p)
	{
		int thread_id = omp_get_thread_num();
		int start = thread_id * size;
		int end = (thread_id+1)* size - 1;

		if(end >= n) end = n-1;
		quicksort_serial_unoptimized(arr,start,end);

		int offset = thread_id * (p-1) - 1;
		for (int j = 1; j < p; ++j)
		{
			if(j*rsize <= end)
			{
				sample[offset + j] = arr[j*rsize-1];
			}
			else
			{
				sample[offset + j] = arr[end];
			}
		}

		#pragma omp barrier

		#pragma omp single
		{
			quicksort_serial_unoptimized(sample,0,p*(p-1));
			for (int i = 0; i < p-1; ++i)
			{
				pivots[i] = sample[i*p + p/2];
			}
		}

		#pragma omp barrier

		offset = thread_id * (p + 1);
		subsize[offset] = start;
		subsize[offset+p] = end+1;
		sublists(arr,start,end,subsize,offset,pivots,1,p-1);

		#pragma omp barrier

		int max = p * (p + 1);
    	bucksize[thread_id] = 0;
    	for(int i = thread_id; i < max; i += p + 1) {
      		bucksize[thread_id] += subsize[i + 1] - subsize[i];
		}

		#pragma omp barrier

		#pragma omp single
		{
			for (int i = 1; i < p; ++i)
			{
				bucksize[i] = bucksize[i] + bucksize[i-1];
			}
			bucksize[0] = 0;
		}

		#pragma omp barrier

		start = bucksize[thread_id];
		if(thread_id == p-1)
		{
			end = n -1; 
		}
		else
		{
			end = bucksize[thread_id+1]-1;
		}
		mergesort_serial(arr,start,end);
	}

	free(sample);
	free(pivots);
	free(subsize);
	free(bucksize);

}

void PSRS_openmp_optimized(int* arr, int n, int p, int cutoff)
{

	if(n < 50)
	{
		insertionsort(arr,0,n);
		return;
	}

	if(n < cutoff)
	{
		mergesort_serial(arr,0,n-1);
		return;
	}

	int size = (n+p-1)/p;
	int rsize = (size + p-1)/p;
	int* sample = malloc(sizeof(int) * (p * (p-1)));
	int* pivots = malloc(sizeof(int) * (p-1));
	int* subsize = malloc(sizeof(int) * (p*(p+1)));
	int* bucksize = malloc(sizeof(int) * p);
	#pragma omp parallel shared(size,rsize,sample,pivots,subsize,bucksize) num_threads(p)
	{
		int thread_id = omp_get_thread_num();
		int start = thread_id * size;
		int end = (thread_id+1)* size - 1;

		if(end >= n) end = n-1;
		
		if(end-start < 50)
		{
			insertionsort(arr,start,end+1);
		}
		else if(end-start < cutoff)
		{
			mergesort_serial(arr,start,end);
		}
		else
		{
			quicksort_serial_optimized(arr,start,end);
		}
		

		int offset = thread_id * (p-1) - 1;
		for (int j = 1; j < p; ++j)
		{
			if(j*rsize <= end)
			{
				sample[offset + j] = arr[j*rsize-1];
			}
			else
			{
				sample[offset + j] = arr[end];
			}
		}

		#pragma omp barrier

		#pragma omp single
		{
			
			mergesort_serial(sample,0,p*(p-1));
			for (int i = 0; i < p-1; ++i)
			{
				pivots[i] = sample[i*p + p/2];
			}
		}

		#pragma omp barrier

		offset = thread_id * (p + 1);
		subsize[offset] = start;
		subsize[offset+p] = end+1;
		sublists(arr,start,end,subsize,offset,pivots,1,p-1);

		#pragma omp barrier

		int max = p * (p + 1);
    	bucksize[thread_id] = 0;
    	for(int i = thread_id; i < max; i += p + 1) {
      		bucksize[thread_id] += subsize[i + 1] - subsize[i];
		}

		#pragma omp barrier

		#pragma omp single
		{
			for (int i = 1; i < p; ++i)
			{
				bucksize[i] = bucksize[i] + bucksize[i-1];
			}
			bucksize[0] = 0;
		}

		#pragma omp barrier

		start = bucksize[thread_id];
		if(thread_id == p-1)
		{
			end = n -1; 
		}
		else
		{
			end = bucksize[thread_id+1]-1;
		}
		mergesort_serial(arr,start,end);
	}

	free(sample);
	free(pivots);
	free(subsize);
	free(bucksize);

}