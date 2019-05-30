#include <stdio.h>
#include "../include/random.h"
#include "../include/mtwister.h"


void populateArr(int* arr, int n)
{
	MTRand r = seedRand(235489208);
	for (int i = 0; i < n; ++i)
	{
		arr[i] = ((int)(genRand(&r)*n));
	}
}

void printArr(int* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
