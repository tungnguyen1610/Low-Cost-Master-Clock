// Reference: https://github.com/nwtime/linuxptp/blob/master/clockadj.h 
/**
 * @file clockadj.h
 * @brief Wraps clock_adjtime functionality.
 * @note Copyright (C) 2013 Miroslav Lichvar <mlichvar@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef HAVE_CLOCKADJ_H
#define HAVE_CLOCKADJ_H

#include <inttypes.h>
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize state needed when adjusting or reading the clock.
 * @param clkid A clock ID obtained using phc_open() or CLOCK_REALTIME.
 */
void clockadj_init(clockid_t clkid);

/**
 * Set clock's frequency offset.
 * @param clkid A clock ID obtained using phc_open() or CLOCK_REALTIME.
 * @param freq  The frequency offset in parts per billion (ppb).
 * @return      0 on success, -1 on failure
 */
int clockadj_set_freq(clockid_t clkid, double freq);

/**
 * Read clock's frequency offset.
 * @param clkid A clock ID obtained using phc_open() or CLOCK_REALTIME.
 * @return      The frequency offset in parts per billion (ppb).
 */
double clockadj_get_freq(clockid_t clkid);

/**
 * Set clock's phase offset.
 * @param clkid  A clock ID obtained using phc_open() or CLOCK_REALTIME.
 * @param offset The phase offset in nanoseconds.
 * @return       0 on success, -1 on failure
 */
int clockadj_set_phase(clockid_t clkid, long offset);

/**
 * Step clock's time.
 * @param clkid A clock ID obtained using phc_open() or CLOCK_REALTIME.
 * @param step  The time step in nanoseconds.
 * @return      0 on success, -1 on failure
 */
int clockadj_step(clockid_t clkid, int64_t step);

/**
 * Read maximum frequency adjustment of the target clock.
 * @return The maximum frequency adjustment in parts per billion (ppb).
 */
int clockadj_max_freq(clockid_t clkid);

/**
 * Compare offset between two clocks
 * @param clkid     A clock ID obtained using phc_open() or CLOCK_REALTIME
 * @param sysclk    A clock ID obtained using phc_open() or CLOCK_REALTIME
 * @param readings  Number of readings to try
 * @param offset    On return, the nanoseconds offset between the clocks
 * @param ts        On return, the time of sysclk in nanoseconds that was used
 * @param delay     On return, the interval between two reads of sysclk
 * @return Zero on success, or negative error code on failure.
 *
 * Compare the offset between two clocks in a similar manner as the
 * PTP_SYS_OFFSET ioctls. Performs multiple reads of sysclk with a read of
 * clkid between in order to calculate the time difference of sysclk minus
 * clkid.
 */
int clockadj_compare(clockid_t clkid, clockid_t sysclk, int readings,
		     int64_t *offset, uint64_t *ts, int64_t *delay);

/**
 * Set the system clock to insert/delete leap second at midnight.
 * @param leap  +1 to insert leap second, -1 to delete leap second,
 *              0 to reset the leap state.
 */
void sysclk_set_leap(int leap);

/**
 * Set the TAI offset of the system clock to have correct CLOCK_TAI.
 * @param offset The TAI-UTC offset in seconds.
 */
void sysclk_set_tai_offset(int offset);

/**
 * Read maximum frequency adjustment of the system clock (CLOCK_REALTIME).
 * @return The maximum frequency adjustment in parts per billion (ppb).
 */
int sysclk_max_freq(void);

/**
 * Mark the system clock as synchronized to let the kernel synchronize
 * the real-time clock (RTC) to it.
 */
void sysclk_set_sync(void);
#ifdef __cplusplus
}
#endif
#endif

