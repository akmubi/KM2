#include <math.h>

#include "poisson_process.h"
#include "MLKG/distributions.h"

void homogeneous_generate(double T, double lambda, int k, int *I, struct UnrolledList *S, unsigned int *N)
{
	double t = 0.0;
	int count =  0;
	// Нахождение времен событий
	while (1)
	{
		// Генерирование случайного числа
		double U = 0.0;
		uniform(&U, 1, 0.0, 1.0);

		// Расчёт времени появляения следующего события
		double time = 1 / lambda * log(U);
		if (t - time > T) break;
		t -= time;

		// Добавление времени в список
		list_push(S, t);
		count++;
	}

	// Сохраняем число событий
	*I = count;

	// Расчёт частот поялвления событий в интервалах
	for (int j = 0; j < count; ++j)
	{
		int m = (int)(list_get_by(S, j) / k);
		N[m]++;
	}
}
