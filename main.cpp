#include <stdio.h>
#include <omp.h>
#include <cmath>

#define TOTAL 200

int main()
{
	int a[TOTAL];
	for (int i = 0; i < TOTAL; i++)
	{
		a[i] = i;
	}

	int total_threads = omp_get_num_procs();
	printf("Total number of threads: %d\n", total_threads);

	int data_per_thread = (int)std::ceil((float)TOTAL / (float)total_threads);
	printf("Data processing per thread %d\n", data_per_thread);

#pragma omp parallel
	{
		int i = omp_get_thread_num();
		for (int j = 0; j < data_per_thread; j++)
		{
			int idx = data_per_thread * i + j;
			if (idx < TOTAL)
				printf("(%d) %d", i, a[idx]);
		}
	}
}