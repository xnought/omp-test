#include <stdio.h>
#include <omp.h>
#include <cmath>
#include <string>
#include <unordered_map>

#define TOTAL 200
using namespace std;

template <typename K, typename V>
bool map_has(unordered_map<K, V> &m, K &check)
{
	return m.find(check) != m.end();
}

void merge_maps(unordered_map<string, int> &dst, unordered_map<string, int> &src)
{
	for (auto const &[key, val] : src)
	{
		if (dst.find(key) != dst.end())
		{
			dst[key] += src[key];
		}
		else
		{
			dst[key] = src[key];
		}
	}
}

int main()
{
	int a[TOTAL];
	for (int i = 0; i < TOTAL; i++)
	{
		a[i] = i;
	}

	int total_threads = omp_get_num_procs();
	printf("Total number of threads: %d\n", total_threads);

	int data_per_thread = (int)ceil((float)TOTAL / (float)total_threads);
	printf("Data processing per thread %d\n", data_per_thread);

	unordered_map<string, int> global_map;
	omp_lock_t writelock;
	omp_init_lock(&writelock);
#pragma omp parallel
	{
		unordered_map<string, int> local_map;
		int i = omp_get_thread_num();
		for (int j = 0; j < data_per_thread; j++)
		{
			int idx = data_per_thread * i + j;
			if (idx < TOTAL)
			{
				local_map["hi" + to_string(j)] = 1;
			}
		}

		// then take the global map and update it with what this thread computed
		omp_set_lock(&writelock);
		merge_maps(global_map, local_map);
		omp_unset_lock(&writelock);
	}
	omp_destroy_lock(&writelock);

	for (auto const &[key, val] : global_map)
	{
		printf("%s %d\n", key.c_str(), val);
	}
}