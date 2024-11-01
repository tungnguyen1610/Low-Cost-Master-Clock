#ifndef PHC_CONTROL_H
#define PHC_CONTROL_H
#include <time.h>
/* Define limits for frequency adjustment */
#define NSEC2SEC 1000000000.0  // For converting nanoseconds to seconds
#ifdef __cplusplus
extern "C" {
#endif
/* Function to adjust the frequency of the clock */
int do_freq(clockid_t clkid, double ppb);
void double_to_timespec(double d, struct timespec *ts);
void do_set(clockid_t clkid, long custom_nsec);
#ifdef __cplusplus
}
#endif
#endif 
