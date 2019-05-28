#ifndef HPC_QUICKSORT
#define HPC_QUICKSORT

void swap(int* arr, int a, int b);

int partition(int* arr, int lo, int hi);

void quicksort_serial_unoptimized_entry(int* arr, int len);
void quicksort_serial_unoptimized(int* arr, int lo, int hi);

void quicksort_openmp_unoptimized_entry(int* arr, int len);
void quicksort_openmp_unoptimized(int* arr, int lo, int hi);

#endif