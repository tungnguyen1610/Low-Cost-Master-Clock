#include "phc_ctl.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "clockadj.h"
#include <math.h>
/* Main function to adjust the frequency directly by passing a clock id and ppb value */
int do_freq(clockid_t clkid, double ppb) 
{
    /* Range check for the frequency adjustment value */
    if (ppb < -NSEC2SEC || ppb > NSEC2SEC) {
                fprintf(stderr, "failed to adjust the clock: %s\n", strerror(errno));
        return -2;
    }
    /* Initialize the clock adjustment (if needed) */
    clockadj_init(clkid);
    /* Set the frequency adjustment */
    clockadj_set_freq(clkid, ppb);
    printf("adjusted clock frequency offset to %lfppb\n",ppb);
    return 0;  // Success
}
void double_to_timespec(double d, struct timespec *ts)
{
	double fraction, whole;

	fraction = modf(d, &whole);

	/* cast the whole value to a time_t to store as seconds */
	ts->tv_sec = (time_t)whole;
	/* tv_nsec is a long, so we multiply the nanoseconds per second double
	 * value by our fractional component. This results in a correct
	 * timespec from the double representing seconds.
	 */
	ts->tv_nsec = (long)(NSEC2SEC * fraction);
} 
void do_set(clockid_t clkid,long custom_nsec)
{
    struct timespec ts;
    memset(&ts, 0, sizeof(ts));

    /* Get the current time from CLOCK_REALTIME */
    if (clock_gettime(CLOCK_REALTIME, &ts)) {
        fprintf(stderr,"set: failed to get CLOCK_REALTIME time: %s", strerror(errno));
        return;  // Exit the function on failure
    }

    /* Modify the nanoseconds part with the custom value provided */
    if (custom_nsec < 0 || custom_nsec >= 1000000000) {
        printf("set: nanoseconds part is out of valid range (0 to 999999999)");
        return;  // Exit the function if nanoseconds value is invalid
    }
    ts.tv_nsec = custom_nsec;

    /* Set the PHC clock (or any other clock specified by clkid) */
    if (clock_settime(clkid, &ts)) {
                        fprintf(stderr, "failed to set the PHC clock: %s\n", strerror(errno));
    } else {
       printf("Set PHC clock time to %lld.%09ld (custom nsec: %ld)",
                  (long long)ts.tv_sec, ts.tv_nsec, custom_nsec);
    }
}
