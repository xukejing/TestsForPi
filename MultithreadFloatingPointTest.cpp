#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "unistd.h"
#include <math.h>
#define MICRO_IN_SEC 1000000.00
double microtime();
int main()
{
	double s = 1;
	double pi = 0;
	double i = 1.0;
	double n = 1.0;
	double dt_err;
	double dt;
	double p;
	double start_time, end_time;
	long cnt = 0;
	start_time = microtime();
	dt_err = microtime() - start_time;

	printf("baseline\n");
	start_time = microtime();
	for (cnt = 0; cnt<100000000; cnt++)
	{
		pi += i;
		n = n + 2;
		s = -s;
		i = s / n;
	}
	pi = 4 * pi;
	dt = microtime() - start_time - dt_err;
	printf("time = %lf s\n", dt);

	s = 1;
	pi = 0;
	i = 1.0;
	n = 1.0;
	printf("2threads\n");
	start_time = microtime();
#pragma omp parallel for num_threads(2)
	for (cnt = 0; cnt<100000000; cnt++)
	{
		pi += i;
		n = n + 2;
		s = -s;
		i = s / n;
	}
	
	pi = 4 * pi;
	dt = microtime() - start_time - dt_err;
	printf("time = %lf s\n", dt);

	s = 1;
	pi = 0;
	i = 1.0;
	n = 1.0;
	printf("4threads\n");
	start_time = microtime();
#pragma omp parallel for num_threads(4)
	for (cnt = 0; cnt<100000000; cnt++)
	{
		pi += i;
		n = n + 2;
		s = -s;
		i = s / n;
	}
	
	pi = 4 * pi;
	dt = microtime() - start_time - dt_err;
	printf("time = %lf s\n", dt);
	return 1;
}
double microtime() {
	int tv_sec, tv_usec;
	double time;
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	return tv.tv_sec + tv.tv_usec / MICRO_IN_SEC;
}
