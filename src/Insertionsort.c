#include "../include/Quicksort.h"
#include "../include/Insertionsort.h"

void insertionsort(int* arr, int start, int end)
{
	for(int i = start + 1; i < end; ++i)
	{
		int v = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > v)
		{
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = v;
	}
}
