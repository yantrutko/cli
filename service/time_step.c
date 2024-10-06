#include "time_step.h"
#include <sys/time.h>
#include <stddef.h>

double time_step_sec_ms (void)
{
	double value = 0.0;
	struct timeval time;
	gettimeofday (&time, NULL);
	value = (double) time.tv_sec + (double) time.tv_usec / 1000000;
	return value;
}

long time_step_sec (void)
{
	long value = 0;
	struct timeval time;
	gettimeofday (&time, NULL);
	value = (long) time.tv_sec;
	return value;
}
