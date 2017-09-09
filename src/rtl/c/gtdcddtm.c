/*
 * gtdcddtm.c -  Chestnut Run-Time Library entry for function get_decoded_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object clong_to_bignum(SI_Long a);

#else

extern Object clong_to_bignum();

#endif




/*
 * Common Lisp decoded time:
 *   second (0 - 59)
 *   minute (0 - 59)
 *   hour (0 - 23)
 *   date (1 - 31)
 *   month(1 - 12)
 *   year (e.g. 1991)
 *   day of week (Monday = 0)
 *   dst-p (T/NIL)
 *   time-zone (hours west of GMT)
 *
 * Unix decoded time:
 *   int tm_sec;       seconds (0 - 59)
 *   int tm_min;       minutes (0 - 59)
 *   int tm_hour;      hours (0 - 23)
 *   int tm_mday;      day of month (1 - 31)
 *   int tm_mon;       month of year (0 - 11)
 *   int tm_year;      year - 1900
 *   int tm_wday;      day of week (Sunday = 0)
 *   int tm_yday;      day of year (0 - 365)
 *   int tm_isdst;     1 if DST in effect
 *   char *tm_zone;    abbreviation of timezone name
 *   long tm_gmtoff;   seconds east of GMT      - Sun only
 */

#if defined(sun) && !defined(__SVR4)
#define GET_TIME_ZONE(newtime) \
    xmake_canonical_rational(FIX((newtime)->tm_gmtoff), FIX(-3600))
#else
/* What to do?  Assume EST? */
#define GET_TIME_ZONE(newtime) FIX(5L)
#endif

/*
 * (get-decoded-time)  should return the same values as
 *   (decode-universal-time (get-universal-time)).
 */

Object get_decoded_time()
{
    time_t ltime;		/* long */
    struct tm *newtime;
    Object t1,t2,t3,t4,t5,t6,t7,tz;
    extern Object xmake_canonical_rational();
    Declare_stack_pointer;
    long temp;

    SAVE_STACK();
    PROTECTI_8(t1,t2,t3,t4,t5,t6,t7,tz);
    time(&ltime);
    newtime = localtime(&ltime);
    temp = newtime->tm_sec; t1 = INT_TO_INTEGER(temp);
    temp = newtime->tm_min; t2 = INT_TO_INTEGER(temp);
    temp = newtime->tm_hour; t3 = INT_TO_INTEGER(temp);
    temp = newtime->tm_mday; t4 = INT_TO_INTEGER(temp);
    temp = newtime->tm_mon + 1; t5 = INT_TO_INTEGER(temp);
    temp = newtime->tm_year + 1900; t6 = INT_TO_INTEGER(temp);
    temp = (newtime->tm_wday + 6) % 7; t7 = INT_TO_INTEGER(temp);
    /* long tm_gmtoff is offset east of GMT in seconds */
    tz = GET_TIME_ZONE(newtime);
    RESTORE_STACK();
    return VALUES_9(t1,t2,t3,t4,t5,t6,t7,
		    (newtime->tm_isdst ? T : NIL),
		    tz);
}
