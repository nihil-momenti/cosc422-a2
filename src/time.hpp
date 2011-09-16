#ifndef TIME_HPP
#define TIME_HPP

// Re-entrant
extern void time_init();

// Returns the current time in seconds.
// Uses high precision timers if possible.
extern double time_get();

#endif
