#ifndef HPC_PSRS
#define HPC_PSRS


// Recursively dividearray[start:end] intopsublists withpivots[f p:lp] as splitters.
//The final demarcations for the  sublists are stored insubsizestarting from indexat.
void sublists(int* arr, int start, int end, int* subsize, int at, int* pivots, int fp, int lp);

void PSRS_openmp_unoptimized(int* arr, int n, int p);

void PSRS_openmp_optimized(int* arr, int n, int p, int cutoff);
#endif