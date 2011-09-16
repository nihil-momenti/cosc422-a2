#include "time.hpp"

#ifdef WIN32

BOOL time_high_res;
LARGE_INTEGER time_freq;
LARGE_INTEGER time_count;

double time_get() {
    if (time_high_res) {
        QueryPerformanceCount(&time_count);
        return (time_count * 1.0) / time_freq * 1000000.0;
    } else {
        return GetTickCount() * 1000.0;
    }
}

void time_init() {
    high_res = QueryPerformanceFrequency(&freq);
}

#else

#include <sys/time.h>
double time_get() {
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000.0 + time.tv_usec;
}

void time_init() {
}

#endif
