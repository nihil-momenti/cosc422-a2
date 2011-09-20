#include "time.hpp"

#ifdef WIN32

#include <windows.h>

BOOL time_high_res = false;
double time_freq;

double time_get() {
    if (time_high_res) {
        LARGE_INTEGER time_count;
        QueryPerformanceCounter(&time_count);
        return time_count.QuadPart / time_freq;
    } else {
        return GetTickCount() / 1000.0;
    }
}

void time_init() {
    if (! time_high_res) {
        LARGE_INTEGER time_freq_li;
        time_high_res = QueryPerformanceFrequency(&time_freq_li);
        time_freq = time_freq_li.QuadPart;
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
