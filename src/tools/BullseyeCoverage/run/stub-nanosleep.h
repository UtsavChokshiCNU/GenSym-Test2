/* $Revision: 10267 $ $Date: 2009-08-06 14:44:36 -0700 (Thu, 06 Aug 2009) $
 * Copyright (c) Bullseye Testing Technology
 */

#define timespec Libcov_timespec
struct timespec {
	long tv_sec;
	long tv_nsec;
};

#define nanosleep Libcov_nanosleep
static int nanosleep(const struct timespec* rqt, struct timespec* rmt)
{
	rqt = rqt;
	rmt = rmt;
	errno = ENOSYS;
	return -1;
}
