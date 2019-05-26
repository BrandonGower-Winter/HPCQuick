#include <stdio.h>
#include "../include/random.h"

void populateArr(int* arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		arr[i] = (rand() % n);
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
