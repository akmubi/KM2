#include <malloc.h>
#include <stdio.h>
#include "poisson_process.h"
#include "unrolled_list.h"

int main(void)
{
	double T = 100.0;
	double lambda = 1.0;
	int k = 5;
	int I = 0;
	struct UnrolledList list;
	list_init(&list);
	int intervals = (int)(T / k);
	unsigned int *N = malloc(intervals * sizeof(unsigned int));
	homogeneous_generate(T, lambda, k, &I, &list, N);

	puts("List:");
	list_print(&list);

	puts("N:");
	for (int i = 0; i < intervals; ++i)
		printf(" %u", N[i]);
	putchar('\n');
	free(N);
	
	printf("I = %d\n", I);
	list_terminate(&list);
	return 0;
}