#include <stdio.h>
#include <omp.h>

int main()
{
	int total_threads = omp_get_num_procs();
	printf("Total number of threads: %d\n", total_threads);

#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf("Hello from %d\n", id);
	}
}