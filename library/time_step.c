#include "time_step.h"
#include <sys/time.h>
#include <stddef.h>

double time_step_sec_ms (void)
{
    struct timeval time;
    gettimeofday (&time, NULL);
    double value = (double) time.tv_sec + (double) time.tv_usec / 1000000;
    return value;
}

long time_step_sec (void)
{
    struct timeval time;
    gettimeofday (&time, NULL);
    long value = (long) time.tv_sec;
    return value;
}