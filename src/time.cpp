#include "time.hpp"

#ifdef WIN32

BOOL time_high_res = false;
LARGE_INTEGER time_freq;
LARGE_INTEGER time_count;

double time_get() {
    if (time_high_res) {
        QueryPerformanceCount(&time_count);
        return (time_count * 1.0) / time_freq;
    } else {
        return GetTickCount() / 1000.0;
    }
}

void time_init() {
    if (! time_high_res) {
        time_high_res = QueryPerformanceFrequency(&time_freq);
    }
}

#else

#include <sys/time.h>
double time_get() {
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec + time.tv_usec / 1000000.0;
}

void time_init() {
}

#endif
