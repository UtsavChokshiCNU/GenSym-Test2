/*
 * gnrnlrnm.c -  Chestnut Run-Time Library entry for function get_internal_run_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object clong_to_bignum(SI_Long a);
extern Object ltimes(Object a, Object b);

#else

extern Object (*SI_warn_fptr) ();
extern Object clong_to_bignum();
extern Object ltimes();

#endif


#include "ltime.h"


#ifdef VMS
#define tms tbuffer
#define tms_utime proc_user_time
#define tms_stime proc_system_time
#endif

#ifdef USE_GETRUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#endif /* USE_GETRUSAGE */

Object get_internal_run_time()
{
    Declare_local_temp;
    static long saved_internal_cputicks = 0L;
    long cputicks;

#ifdef USE_GETRUSAGE
    /* The code which deals with cputicks in TICKS_PER_SECOND
       only works is TICKS_PER_SECOND <= IINTERNAL_TIME_UNITS_PER_SECOND,
       so for sources with higher resolut, scale down early. */
#define TICKS_PER_SECOND IINTERNAL_TIME_UNITS_PER_SECOND
    struct rusage rusage;

    getrusage(RUSAGE_SELF, &rusage);
    cputicks = rusage.ru_utime.tv_sec * TICKS_PER_SECOND
	+ (rusage.ru_utime.tv_usec / (1000000L / TICKS_PER_SECOND))
	+ rusage.ru_stime.tv_sec * TICKS_PER_SECOND
	+ (rusage.ru_stime.tv_usec / (1000000L / TICKS_PER_SECOND));
#else /* not USE_GETRUSAGE */
#ifdef USE_CLOCK
#define TICKS_PER_SECOND IINTERNAL_TIME_UNITS_PER_SECOND
    cputicks = clock() / (1000000L / TICKS_PER_SECOND);
#else
#define TICKS_PER_SECOND 60L	/* what about Australia? */
    struct tms tp;

    /* tms_utime = user time, tms_stime = system time */
    times(&tp);
    cputicks = tp.tms_utime + tp.tms_stime;
#endif /* not USE_CLOCK */
#endif /* not USE_GETRUSAGE */
    if (saved_internal_cputicks == 0)
	saved_internal_cputicks = cputicks;
    if (cputicks < saved_internal_cputicks)
	warn(1, "get_internal_run_time: clock wrapped around");
    cputicks -= saved_internal_cputicks;

    /* If you're worried about bignum consing, and can tolerate frequent
       wraparound, try #defining AVOID_BIGNUM_TIME. */

#ifdef AVOID_BIGNUM_TIME
    return VALUES_1(FIX(cputicks * (IINTERNAL_TIME_UNITS_PER_SECOND /
				    TICKS_PER_SECOND)));
#else
    return ltimes(LONG_TO_INTEGER(cputicks),
		  FIX(IINTERNAL_TIME_UNITS_PER_SECOND / TICKS_PER_SECOND));
#endif
}
