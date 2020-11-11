#include <malloc.h>
#include <stdio.h>
#include <math.h>

#include "MLKG/statistical_tests.h"
#include "poisson_process.h"
#include "unrolled_list.h"

// #define HOMOGENEOUS

#if !defined(HOMOGENEOUS)
static double lambda_func(double t, double lambda)
{
	return lambda * fabs(sin(t));
}
#endif


int main(void)
{
	double T = 20.0;
	double lambda = 1.0;
	int k = 1;
	printf("T = %7.4lf\n", T);
	printf("lambda = %7.4lf\n", lambda);
	printf("k = %d\n", k);

	int I = 0;
	struct UnrolledList list, N;
	list_init(&list);
	list_init(&N);

#if defined(HOMOGENEOUS)
	homogeneous_generate(T, lambda, k, &I, &list, &N);
#else
	inhomogeneous_generate(T, lambda, &lambda_func, k, &I, &list, &N);
	puts("lambda_func = lambda * |sin(t)|");
#endif

	puts("S:");
	int i = 0;
	struct Node *iterator = list.root;
	do
	{
		for (int j = 0; j < iterator->count; ++j)
			printf("%3d : %6.4lf\n", i * ARRAY_SIZE + j + 1, iterator->array[j]);
		iterator = iterator->next;
		++i;
	}
	while (iterator != list.root);

	puts("N:");
	int freq_count = list_get_size(&N);
	unsigned int *freq = malloc(freq_count * sizeof(unsigned int));
	for (int i = 0; i < freq_count; ++i)
	{
		freq[i] = (unsigned int)list_get_by(&N, i);
		printf("%u\n", freq[i]);
	}
	
	printf("I = %d\n", I);
	list_terminate(&list);

	double chi_square = 0.0;
	int deg_freedom = 0;

	pearson_poisson(freq, freq_count, I, &chi_square, &deg_freedom);
	free(freq);
	list_terminate(&N);
	return 0;
}