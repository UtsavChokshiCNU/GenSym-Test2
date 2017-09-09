/*
 * gnrnlrlm.c -  Chestnut Run-Time Library entry for function get_internal_real_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if defined(WIN32)
#include <windows.h>
#endif


#if SI_USE_PROTOTYPES

extern Object add(Object a, Object b);
extern Object clong_to_bignum(SI_Long a);
extern Object ltimes(Object a, Object b);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object add();
extern Object clong_to_bignum();
extern Object ltimes();

#endif


#include "ltime.h"



/*
   get_internal_real_time and get_internal_run_time

   These functions are a pain, because there are no good operating
   system interface functions that are widely available.

    OS                units per   interval before
    function          second        wraparound      availability

    Real time
      gettimeofday()  1000000         69 years        BSD
      ftime()	      1000	      25 days	      BSD
      times()(result) 60             415 days         System V
      time()	      1		      69 years        All unixes (ancient)

    Run time
      times()         60             415 days         BSD, System V, others
      clock()         1000000         36 minutes      BSD, others
      clock()         CLOCKS_PER_SEC  ?               ANSI C
      getrusage()     1000000         69 years        Berkeley/Sun

   The Sun documentation says that the true resolution of clock() is
   only 16.667 ms, so maybe it's not such a good idea to use it.
 */

/* gettimeofday() returns time as microseconds + seconds; use it when
   available.  Otherwise, revert to the more widely available ftime()
   function, which gives time of day in milliseconds.  If neither is
   available, one could in principle use time(), which gives the time
   in seconds, but that would be unfortunate. */

#ifndef USE_GETTIMEOFDAY
#ifdef VMS
/* I'm just guessing about this one - is this the right file? */
#include <timeb.h>
#else
#if !defined(__ZTC__)
#include <sys/timeb.h>
#endif /* __ZTC__ */
#endif /* not VMS */
#endif /* not USE_GETTIMEOFDAY */


#if defined (WIN32)
	unsigned long (_stdcall *g_real_time_provider) (void) = &GetTickCount;
	unsigned long g_real_time_base_value = 0;
#endif

Object get_internal_real_time()
{
    Declare_local_temp;
    Object result;
    static unsigned long saved_internal_sec = 0L;
#if defined (WIN32)
    unsigned long t;
#endif
#ifdef USE_GETTIMEOFDAY
    struct timeval tp;
    long time_difference;

    gettimeofday(&tp, NULL);
    result = FIX(tp.tv_usec / (1000000L / IINTERNAL_TIME_UNITS_PER_SECOND));
    if (!saved_internal_sec) 
	saved_internal_sec = tp.tv_sec;
    else
	{
	  time_difference = tp.tv_sec - saved_internal_sec;
	  result = add(result, 
		       ltimes(LONG_TO_INTEGER(time_difference),
			      FIX(IINTERNAL_TIME_UNITS_PER_SECOND)));
	}
#else

#if defined(WIN32)
	t = (g_real_time_provider)();
    if (g_real_time_base_value == 0) {
		result = FIX(0L); //initially, 0ms
		g_real_time_base_value = t;
	} else {
		result = FIX((t - g_real_time_base_value) & IMOST_POSITIVE_FIXNUM);	
	}
#else
    struct timeb tp;  /* time_t time;  unsigned short millitm; */
    long time_difference;

    ftime(&tp);  /* returns status only on some systems */
    result = FIX(IMOST_POSITIVE_FIXNUM & (tp.millitm * (IINTERNAL_TIME_UNITS_PER_SECOND / 1000L)));
    if (!saved_internal_sec)
	saved_internal_sec = tp.time;
    else
	{
	  time_difference = tp.time - saved_internal_sec;
	  result = add(result, 
		       ltimes(LONG_TO_INTEGER(time_difference),
			      FIX(IINTERNAL_TIME_UNITS_PER_SECOND)));
	}
#endif /* WIN32 */

#endif /* not USE_GETTIMEOFDAY */
    return VALUES_1(result);
}
