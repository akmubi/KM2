#include <math.h>
#include <malloc.h>

#include "poisson_process.h"
#include "MLKG/distributions.h"

/*
	Генератор времен появления событий в однородном Пуассоновском процессе
	Вход:	T - время процесса
		lambda - интенсивность
		k - длина интервала
	Выход:	I - число событий, котоыре произойдут к моменту времени T
		S - времена событий
		N - частоты появления событий на интервалах
*/
void homogeneous_generate(double T, double lambda, int k, int *I, struct UnrolledList *S, struct UnrolledList *N)
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

	// Расчёт числа поялвления событий в интервалах
	int c = (int)(T / k);
	unsigned int *L = malloc(c * sizeof(unsigned int));
	for (int i = 0; i < c; ++i)
		L[i] = 0;

	for (int j = 0; j < count; ++j)
	{
		int m = (int)(list_get_by(S, j) / k);
		L[m]++;
	}

	// puts("L:");
	// for (int i = 0; i < c; ++i)
	// 	printf("%u\n", L[i]);

	// Расчёт количества частот
	unsigned int max = 0;
	for (int i = 0; i < c; ++i)
		if (L[i] > max) max = L[i];
	
	// Расчёт самих частот
	int n = max + 1;
	for (int j = 0; j < n; ++j)
		list_push(N, 0.0);

	// Заполняем список частот 
	for (int j = 0; j < c; ++j)
	{
		double *value = list_get_ref_by(N, L[j]);
		*value += 1;
	}
	free(L);
}

/*
	Генератор времен появления событий в однородном Пуассоновском процессе
	Вход:	T - время процесса
		lambda - интенсивность
		lambda_func - функция интенсивности
		k - длина интервала
	Выход:	I - число событий, котоыре произойдут к моменту времени T
		S - времена событий
		N - частоты появления событий на интервалах
*/
void inhomogeneous_generate(double T, double lambda, double (*lambda_func)(double, double), int k, int *I, struct UnrolledList *S, struct UnrolledList *N)
{
	double t = 0.0;
	int count =  0;
	// Нахождение времен событий
	while (1)
	{
		// Генерирование случайного числа
		double U1 = 0.0;
		uniform(&U1, 1, 0.0, 1.0);

		// Расчёт времени появляения следующего события
		double time = 1 / lambda * log(U1);
		if (t - time > T) break;
		t -= time;

		// Генерирование другого случайного числа
		double U2 = 0.0;
		uniform(&U2, 1, 0.0, 1.0);
		if (U2 <= lambda_func(t, lambda) / lambda)
		{
			// Добавление времени в список
			list_push(S, t);
			count++;
		}
	}

	// Сохраняем число событий
	*I = count;

	// Расчёт числа поялвления событий в интервалах
	int c = (int)(T / k);
	unsigned int *L = malloc(c * sizeof(unsigned int));
	for (int i = 0; i < c; ++i)
		L[i] = 0;

	for (int j = 0; j < count; ++j)
	{
		int m = (int)(list_get_by(S, j) / k);
		L[m]++;
	}

	// Находим максимальное число поялений события
	unsigned int max = 0;
	for (int i = 0; i < c; ++i)
		if (L[i] > max) max = L[i];
	
	// Расчёт самих частот
	int n = max + 1;
	for (int j = 0; j < n; ++j)
		list_push(N, 0.0);

	// Заполняем список частот 
	for (int j = 0; j < c; ++j)
	{
		double *value = list_get_ref_by(N, L[j]);
		*value += 1;
	}
	free(L);
}