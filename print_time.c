#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char buf[64];
	struct timespec timeout;
	/* struct timespec {
               time_t   tv_sec;        * seconds *
               long     tv_nsec;       * nanoseconds *
           };
	*/
	struct tm *tmp;
	/* struct tm {
               int tm_sec;    ** Seconds (0-60) *
               int tm_min;    ** Minutes (0-59) *
               int tm_hour;   ** Hours (0-23) *
               int tm_mday;   * Day of the month (1-31) *
               int tm_mon;    * Month (0-11) *
               int tm_year;   * Year - 1900 *
               int tm_wday;   * Day of the week (0-6, Sunday = 0) *
               int tm_yday;   * Day in the year (0-365, 1 Jan = 0) *
               int tm_isdst;  * Daylight saving time *
           };
	*/
	/* int clock_gettime(clockid_t clk_id, struct timespec *tp); */
	clock_gettime(CLOCK_REALTIME, &timeout);
	/* CLOCK_REALTIME
              System-wide clock that measures real (i.e., wall-clock) time.
	      Setting this clock requires appropriate privileges.
	      This clock is affected by discontinuous jumps in the system time
	      (e.g., if the system administrator manually changes the clock),
	      and by the incremental adjustments performed by adjtime(3) and NTP.*
	*/
	/* struct tm *localtime(const time_t *timep); */
	// transform date and time to broken-down time or ASCII
	tmp = localtime(&timeout.tv_sec); //
	/* size_t strftime(char *s, size_t max, const char *format,
                       const struct tm *tm); */
	strftime(buf, sizeof(buf), "%r", tmp);
	/* %r     The time in a.m. or p.m. notation.
	 In the POSIX locale this is equivalent to %I:%M:%S %p. */

	printf("current time is %s\n", buf);
	exit(0);
}
