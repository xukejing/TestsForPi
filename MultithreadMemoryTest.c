#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "unistd.h"

#define MICRO_IN_SEC 1000000.00
double microtime();
int main()
{
	int i = 25000000;
	int ii = 0;
	int *p1,*p2;
	
	double start_time, end_time, dt, dt_err;
	start_time = microtime();
	dt_err = microtime() - start_time;

	printf("baseline\n");
	start_time = microtime();
	p1 = malloc(sizeof(int)*i);
	for (ii = 0; ii<i; ii++)
		*(p1 + ii) = 2147483647;
	dt = microtime() - start_time - dt_err;
	free(p1);
	printf("time = %lf s\n", dt);

	printf("6threads\n");
	start_time = microtime();
	p2 = malloc(sizeof(int)*i);
#pragma omp parallel for num_threads(6)
	for (ii = 0; ii<i; ii++)
		*(p2 + ii) = 2147483647;
	dt = microtime() - start_time - dt_err;
	free(p2);
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