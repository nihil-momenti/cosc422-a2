#include "time.hpp"

#ifdef WIN32

double time_get() {
    return GetTickCount();
}

#else

#include <sys/time.h>
double time_get() {
    timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
}

#endif
