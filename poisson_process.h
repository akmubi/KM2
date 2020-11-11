#ifndef ___POISSON_PROCESS_H___
#	define ___POISSON_PROCESS_H___

#	include "unrolled_list.h"

// ОДНОРОДНЫЙ ПУАССОНОВСКИЙ ПРОЦЕСС

// T		- время процесса
// lambda 	- интенсивность
// k		- длина интервала
// I		- число событий, которые произойдут к моменту времени T
// S		- времена I событий
// N		- частоты попадания событий на интервалах
extern void homogeneous_generate(	double T,
					double lambda,
					int k,
					int *I,
					struct UnrolledList *S,
					struct UnrolledList *N);


// НЕОДНОРОДНЫЙ ПУАССОНОВСКИЙ ПРОЦЕСС

// T		- время процесса
// lambda 	- интенсивность
// lambda_func	- функция интенсивности (0 <= lambda_func() / lambda <= 1)
// k		- длина интервала
// I		- число событий, которые произойдут к моменту времени T
// S		- времена I событий
// N		- частоты попадания событий на интервалах
extern void inhomogeneous_generate(	double T,
					double lambda,
					double (*lambda_func)(double, double),
					int k,
					int *I,
					struct UnrolledList *S,
					struct UnrolledList *N);

#endif // ___POISSON_PROCESS_H___