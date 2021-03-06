#ifndef HPC_QUICKSORT
#define HPC_QUICKSORT

void swap(int* arr, int a, int b);

int bestofthree(int* arr, int i,int j, int k);
int partition(int* arr, int lo, int hi);
int partition_optimized(int* arr, int lo, int hi);

void quicksort_serial_unoptimized_entry(int* arr, int len);
void quicksort_serial_unoptimized(int* arr, int lo, int hi);

void quicksort_serial_optimized_entry(int* arr, int len);
void quicksort_serial_optimized(int* arr, int lo, int hi);

void quicksort_openmp_unoptimized_entry(int* arr, int len);
void quicksort_openmp_unoptimized(int* arr, int lo, int hi);

void quicksort_openmp_optimized_entry(int* arr, int len, int cutoff);
void quicksort_openmp_optimized(int* arr, int lo, int hi, int cutoff);

#endif