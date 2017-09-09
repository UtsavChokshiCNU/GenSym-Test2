/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 +
 + Module:      ctime.c
 +
 + Author(s):   John Hodgkinson
 +
 + Description: This module contains system time functions
 + 
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following: 
 +      Multiply Defined    Function appears multiple times, each definition
 +                          for an #ifdef specified platform.
 +      Mixed Ifdefs        Single definition for function containing platform
 +                          specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES 
 +   Section:      DEFINES
 +   Section:      FUNCTION GROUP - Time Functions
 +      g2ext_g2_clock_ticks_per_second()      0000000 Mixed Ifdefs
 +      g2ext_g2_clock_ticks()                 0000000 Multiply Defined
 +      g2ext_time_zone()                      0000000 Mixed Ifdefs
 +      g2ext_decode_unix_time()             0000000 Mixed Ifdefs
 +      g2ext_unix_time_as_float()          0000000 Multiply Defined
 +      g2ext_infer_encoded_unix_time()     0000000 Multiply Defined
 +      g2ext_current_time()                   0000000 
 +
 +   Section:      TESTING
 +
 + External Interface:
 +      long   g2ext_g2_clock_ticks_per_second(void)
 +               Return number of clock tick per second
 +
 +      Gensym_Long g2ext_g2_clock_ticks(long mask)
 +               Returns a value from 0 through mask for measuring subsecond
 +               intervals.  It wraps around less than once per 24 hours.
 +
 +      long   g2ext_time_zone(long choice)
 +               Returns system timezone or daylight savings information
 +
 +      long   g2ext_decode_unix_time(double seconds_from_1970,
 +                        unsigned short response[])
 +               Convert number of seconds since 1970 to calendar components.
 +
 +      double g2ext_unix_time_as_float(void)
 +               Returns number of elapsed seconds since January 1, 1970
 +
 +      double g2ext_get_encoded_unix_time(long sec, long min, long hour, long mday,
 *                               long mon, long year)
 +               Takes time components as inputs and returns the number of
 +               elapsed seconds since 1970.
 +
 +      double g2ext_infer_encoded_unix_time( double time_since_1970_no_dst )
 +               Takes as argument the approximate seconds since 1970. Returns
 +               the encoded universal time as a long, additionally corrected
 +               for daylight savings, in a less efficient way than
 +               c_get_encoded_time().
 +
 +      char *g2ext_current_time(void)
 +               Returns a char* to a string containing the current date and
 +               time.  This function merely wraps a call to ctime.
 +
 + Dependencies:
 +      This file has no external dependencies.
 +
 + Notes:
 +   12/27/93, mpc: On the RS6000, this file must be compiled with the
 +                "-lbsd" flag. This is to link in ftime(), and perhaps others.
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   4/10/2012, jingtao: add g2ext_get_current_time_zone implementation for linux.
 +
 +   3/9/98, ajs: Modification to g2ext_g2_clock_ticks, for alphaosf, fixing
 +                the backwards tick problem. This fix could easily
 +                be applied to many other platforms, only I have no
 +                reason to believe it is necessary.
 +
 +   11/30/94, jra: Removed obsolete functions in favor of the UNIX time
 +                  versions.
 +
 +   3/15/94, jra: Extensive modifications to g2ext_g2_clock_ticks, fixing the
 +                 backwards tick problem.
 +
 +   3/7/94, jra: Added g2ext_decode_unix_time.
 +
 +   3/1/94, jra: Removed unused function get_chestnut_time, added comments to
 +                g2ext_g2_clock_ticks documentation.
 +
 +   12/23/93,mpc: Structural reorganization to improve code legibility,
 +                portability, and maintainability.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include <limits.h>
#include "cprim.h"
#include <stdlib.h>
#include <string.h>

#if defined(__STDC__)
#  include <unistd.h>
#endif

#include <sys/types.h>

#if defined(unix)
#  include <sys/time.h>
#  include <sys/times.h>
#endif
#if !defined(sgi)
#  include <sys/timeb.h>
#endif

#if defined(WIN32)
#  include <windows.h>
#  include <winsock.h>
#endif

/* The following are the only platforms which do NOT include <stdlib.h> */
/*  Should check if this is for an explicit reason.                     */
#if  !defined(sun) && !defined(__osf__)
#  include <stdlib.h>
#endif

//#include "atlbase.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define SECONDS_FROM_1970_TO_1990 631152000
#define SECONDS_IN_HOUR 3600
#define MAX_CHAR_TZI 64


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Time Functions
 %
 % Description:
 %      These functions retrieve system time information
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long g2ext_g2_clock_ticks_per_second(void)
 *
 *   Description:
 *     Return number of clock tick per second
 *   Input Arguments:
 *     none
 *   Returns: 
 *     return value: (long) number of clock tick per second
 *   Notes:
 *     12/23/93, mpc: It appears this value is used in conjunction with
 *         the return value of g2ext_g2_clock_ticks(). Currently g2ext_g2_clock_ticks()
 *         returns a value received from gettimeofday(), which is 
 *         passed back in 1/1000th of a second. If this method changes
 *         for any platform it must be reflected here as well.
 *   Modifications:
 *     12/16/07, jv: Newer versions of Linux do not define CLK_TCK as a constant.
 *         Maybe because it isn't a constant?  Does it change while the machine
 *         is running?  I don't know.  But the code below is the recommended
 *         alternative I found on the web.  This doesn't affect any of our build
 *         machines, only an installation of Linux I did on my laptop, but
 *         presumably newer machines will run into this.
 *
 *****************************************************************************/

/*000000000000000000000000000 Mixed Ifdefs 0000000000000000000000000000000000*/

long g2ext_g2_clock_ticks_per_second()
{
#   if defined(WIN32) || defined(sun4)
      return(1000);
#   else
#     if defined(CLK_TCK)
      return((long)CLK_TCK);
#     else
        return((long)sysconf(_SC_CLK_TCK));
#     endif
#   endif
}

/*000000000000000000000000000 Mixed Ifdefs 0000000000000000000000000000000000*/


/*****************************************************************************
 * Gensym_Long g2ext_g2_clock_ticks(int mask)
 *
 *   Description:
 *     Returns an integer value from 0 through mask which increases as real time
 *     passes at the rate given by the function g2ext_g2_clock_ticks_per_second.  This
 *     value will wrap around, but not more than once within 24 hours.
 *   Input Arguments:
 *     mask: 
 *   Returns: 
 *     return value: (long) Elapsed real time
 *   Notes:
 *     The range of g2ext_g2_clock_ticks_per_second should be within 60 through 6000
 *     to meet this criterion, given the mask values passed from G2.
 *     
 *     In systems which implement an elapsed time system call, like "times" in
 *     POSIX, that may be used directly to implement this operation.  In systems
 *     where such an operation is not available, this function must be based on
 *     a calendar clock time, which poses a problem for this operation The value
 *     returned by this function must never "go backwards in time", even though
 *     it can wrap around its most positive value.  This value serves the role
 *     of a chronometer, used to measure the passage of real time as a stopwatch
 *     would.  In cases where this value is based a time which can be set by the
 *     user of a computer (such as the calendar time), then the basis for this
 *     value can appear to move backwards in time.
 *     
 *     If we allow that value to be propagated to the caller of this function,
 *     then that program must assume that the amount of time that has passed is
 *     an interval just under the length of time that it takes for this value to
 *     wrap around.  Such wildly inaccurate results from this function can cause
 *     these programs to behave erratically.  Since this function is called very
 *     often, the better approach is to return a value which shows a zero time
 *     increment from the last value returned, and then to have this value
 *     continue to proceed forward in time from that that moment.  In order to
 *     implement this functionality, two sets of values will be stored when
 *     basing this function on a calendar time.  The first set of values will be
 *     the most recent previous calendar time returned to this function by the
 *     system.  The second set of values will be a forward adjustment to take to
 *     the calendar time.  When a time received from the system is less than the
 *     most recent previous time received, then the amount by which the new time
 *     is less than the previous time should be added to the time adjustment.
 *     Then all calendar times received from the system should be adjusted
 *     forward by the adjustment amount before being used to compute a return
 *     value.  If multiple adjustments are made, each new adjustment must be
 *     added to the previous adjustment value.
 *   Modifications:
 *     7/8/94, jh: Changed the mask argument of this function to long as part of
 *     the project to ensure that foreign functions get the correct argument and
 *     return types.  For further details (including informarion that may mollify
 *     the fears expressed in jra's 3/7/94 modification below), see my note this
 *     date in /bt/ab/rtl/c/gensym.h.
 *
 *     3/14/94, jra: Added the backwards time warnings in doc, changed so that
 *     most systems use the value of times.
 *     
 *     3/7/94, jra: The argument mask should be given as type long, but I am not
 *     sure that all arguments are given in the translated code as longs.  This
 *     is potentially a bug in this function.
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

#if defined(WIN32)

Gensym_Long g2ext_g2_clock_ticks(mask)
  Gensym_Long mask;
{
#ifdef Platform_32bit
    return(GetTickCount() & (Gensym_Ulong)mask);
#else
    return(GetTickCount64() & (Gensym_Ulong)mask);
#endif
}

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#else
#  if defined(Platform_Solaris)

Gensym_Long g2ext_g2_clock_ticks(mask)
  Gensym_Long mask;
{
    struct timeval   buffer;
    long             seconds, useconds;
    static long      previous_seconds = -1;
    static long      previous_useconds = -1;
    static long      seconds_adjustment = 0;
    static long      useconds_adjustment = 0;
    static long      new_time;

    if (gettimeofday(&buffer, NULL) != -1 ) {
        seconds = (long)buffer.tv_sec;
        useconds = (long)buffer.tv_usec;
        if (previous_seconds > seconds ||
            (previous_seconds == seconds && previous_useconds > useconds)) {
            if (previous_useconds > useconds) {
                seconds_adjustment += previous_seconds - seconds;
                useconds_adjustment += previous_useconds - useconds;
            } else {
                seconds_adjustment += (previous_seconds - seconds) - 1;
                useconds_adjustment += 1000000 + (previous_useconds - useconds);
            }
            if (useconds_adjustment > 1000000) {
                seconds_adjustment++;
                useconds_adjustment -= 1000000;
            }
        }
        previous_seconds = seconds;
        previous_useconds = useconds;
        new_time = (((1000L * (((1L<<20) - 1L) & (seconds + seconds_adjustment)))
                     + (useconds + useconds_adjustment) / 1000L)
                    & (long)mask);
        return new_time;
    } else { 
        printf("gettimeofday failed\n");
        return new_time;
    }
}

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

#  else
#    if defined(__osf__)

Gensym_Long g2ext_g2_clock_ticks(mask)
  Gensym_Long mask;  
{
  struct tms buffer;
  long ticks;
  static long      previous_ticks = -1;
  static long      ticks_adjustment = 0;

  ticks = (long)times(&buffer);
  if (ticks == -1) {
    printf("Times failed.\n");
    return 0;
  } else {
  if (previous_ticks > ticks)
    ticks_adjustment += previous_ticks - ticks;   
  previous_ticks = ticks;
  return  ((ticks + ticks_adjustment) & (long)mask);
  }
}

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

#    else

Gensym_Long g2ext_g2_clock_ticks(mask)
  Gensym_Long mask;
{
    struct tms buffer;
    long ticks;

    ticks = (long)times(&buffer);
    if (ticks == -1) {
        printf("Times failed.\n");
        return 0;
    } else {
        return (ticks & (long)mask);
    }
}

#    endif
#  endif
#endif
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * long g2ext_time_zone(long choice)
 *
 *   Description:
 *     Returns system timezone or daylight savings information
 *   Input Arguments:
 *     choice: If value is 0 then return timezone information,
 +             otherwise return daylight savings information.
 *   Returns: 
 *     return value: 
 *   Notes:
 *     See OS-TIME.LISP for details.  Note that VMS systems always return 0
 *     for daylight savings time and 0 for the timezone.  This function may be
 *     obsolete, since it only works on platforms using ftime(), itself 
 *     obsolescent.
 *     
 *   Modifications:
 *     7/8/94, jh: Changed the choice argument of this function to long as part of
 *     the project to ensure that foreign functions get the correct argument and
 *     return types.  For further details see my note this date in 
 *     /bt/ab/rtl/c/gensym.h.
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_time_zone(choice)
     long      choice;
{
    if (choice == 0) {
#       if defined(sgi) || defined(Platform_Solaris) || defined(__osf__) || defined(__hpux) || defined(__APPLE__)
             return FAILURE;
#       else
             struct timeb buffer;

             ftime(&(buffer));
             return (long) (buffer).timezone;
#       endif
    } else { 
        time_t timet_buffer;
        struct tm     *tm_buffer;
        
        time(&timet_buffer);
        tm_buffer = localtime(&timet_buffer);
        return (long)tm_buffer->tm_isdst;
    }
}
/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_is_dst_used()
{
	tzset();
    #ifdef WIN32
        return _daylight;
    #else
        return daylight;
    #endif
}   
/*****************************************************************************
 * long g2ext_get_current_time_zone(unsigned short *buffer, long buflen)
 *
 *   Description:
 *     Returns current system time zone information
 *   Input Arguments:
 *     buffer: input string buffer for storing time zone information. 
			   Buffer memory has been managed on called side.
 *   Returns: 
 *     return value: 
 *   Notes:
 *     When error occurred returns -1. Otherwise returns time zone information bytes count 
 *     
 *****************************************************************************/

long g2ext_get_current_time_zone(buffer, buflen)
	unsigned short *buffer;	/* returned time zone information */
	long buflen;		/* length of buffer */
{
#if defined(WIN32)
	DWORD dwRet;
	TIME_ZONE_INFORMATION obj_tzi;

	dwRet = GetTimeZoneInformation(&obj_tzi);
	if(dwRet == TIME_ZONE_ID_STANDARD || dwRet == TIME_ZONE_ID_UNKNOWN)
		wcscpy_s((LPWSTR)buffer, buflen, obj_tzi.StandardName);
	else if(dwRet == TIME_ZONE_ID_DAYLIGHT)
		wcscpy_s((LPWSTR)buffer, buflen, obj_tzi.DaylightName);
	else
		return -1;

	return wcslen((LPCWSTR)buffer);
#else
	size_t count;
	char *p_tzi;
	int i;

	tzset(); /* to ensure tzname is filled. */

	if (daylight != 0) {
		/* use daylight time zone if it is available. */
		count = strlen (tzname[1]);
		if (count > 0) {
			p_tzi = tzname[1];
		} else {
			/* use standard time zone if daylight time zone is not available. */
			p_tzi = tzname[0];
		}
	} else {
		/* use standard time zone if daylight time zone is not available. */
		p_tzi = tzname[0];
	}

	count = strlen (p_tzi);
	if (count >= buflen)
		count = buflen - 1;

	/* Transform ASCII string to UCS2 wide string */
	for (i = 0; i < count; ++i)
		buffer[i] = p_tzi[i];
	buffer[count] = 0;
	return count;
#endif
}

/*****************************************************************************
 * long g2ext_decode_unix_time(double seconds_from_1970, unsigned short response[])
 *
 *   Description:
 *     Convert number of seconds since 1970 to calendar form, modifies response
 *     with result.
 *   Input Arguments:
 *     seconds_from_1970: A double
 *     response: An array to hold the components of the decoded time
 *   Returns:
 *     return value: Always zero
 *   Notes:
 *     Any subsecond portion of the double is truncated before decoding.  The
 *     following values will be placed into elements of response.
 *       0 : second (0-59)
 *       1 : minute (0-59)
 *       2 : hour (0-23)
 *       3 : date (1-31)
 *       4 : month (1-12)
 *       5 : year (years since 1900)
 *       6 : day-of-week (0=Monday-6=Sunday)
 *       7 : daylight-savings (1 = yes, 0 = no)
 *   Modifications:
 *      jv, 10/29/98 - On Intel NT, localtime returns NULL if given a 
 *      negative value.  We happily dereference it, and get a segmentation
 *      violation.  There are two reasons why we might be calling localtime
 *      with a negative value: (1) we are passed a negative value; (2) we
 *      are passed a large positive value, and the cast to long produces
 *      an overflow.  
 *          If float_seconds_from_1970 was greater than zero, but after
 *      the cast, the resulting long is less than zero, we must have 
 *      overflowed.  (Note that C's behavior when casting into an integer data
 *      type with a value which is much too large to fit into that data type 
 *      is implementation dependent [Harbison & Steele, 4th Ed, p170].)  
 *      Solaris gcc gives the long the value of LONG_MAX, while MSDEV does 
 *      some other conversion that may result in a large negative value.)
 *      When we detect the overflow, use LONG_MAX instead.
 *         On the other hand, if we receive a negative value as an argument,
 *      we're just going to have to go ahead and fail.  Adding default
 *      behavior to return Thursday, January 1, 1970, at 00:00.
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

long g2ext_decode_unix_time(float_seconds_from_1970, response)
     double float_seconds_from_1970;
     unsigned short response[];
{
    struct tm    *local_time_struct;
    time_t        seconds_from_1970;

    seconds_from_1970 = (long)float_seconds_from_1970;
    if ((seconds_from_1970 < 0L) &&
        (float_seconds_from_1970 > 0.0))
      seconds_from_1970 = LONG_MAX;

    local_time_struct = localtime(&seconds_from_1970);

    if (local_time_struct) {
      response[0] = (unsigned short) local_time_struct->tm_sec;
      response[1] = (unsigned short) local_time_struct->tm_min;
      response[2] = (unsigned short) local_time_struct->tm_hour;
      response[3] = (unsigned short) local_time_struct->tm_mday; 
      response[4] = (unsigned short) local_time_struct->tm_mon + 1;
      response[5] = (unsigned short) local_time_struct->tm_year;
      response[6] = (unsigned short) ((6 + local_time_struct->tm_wday) % 7);
      response[7] = (unsigned short) (local_time_struct->tm_isdst ? 1 : 0);
    } else {
      /* In this case, localtime failed to return a structure.  We know
       * that that is the case on Intel NT when given a negative value,
       * for example.  This default behavior may not be the greatest,
       * but it's better than a segmentation violation.   - jv, 10/29/98
       */
      response[0] = (unsigned short) 0;  /* seconds */
      response[1] = (unsigned short) 0;  /* minutes */
      response[2] = (unsigned short) 0;  /* hours   */
      response[3] = (unsigned short) 1;  /* mday    */
      response[4] = (unsigned short) 1;  /* month   */
      response[5] = (unsigned short) 70; /* year    */
      response[6] = (unsigned short) 4;  /* day -Th */
      response[7] = (unsigned short) 0;  /* dst     */
    }

    return 0;
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/


/*****************************************************************************
 * double g2ext_unix_time_as_float(void)
 *
 *   Description:
 *     Get "UNIX time" from the system.
 *   Input Arguments:
 *     none.
 *   Returns:
 *     return value: number of seconds since Midnight, January 1, 1970
 *   Notes:
 *
 *   Modifications:
 *
 *****************************************************************************/

double
g2ext_unix_time_as_float()
{
#if defined(WIN32)
  __int64 x;
  FILETIME f;
  GetSystemTimeAsFileTime (&f); /* 100ns intervals since Jan-01-1601 */
  x = ((__int64)f.dwHighDateTime << 32) + f.dwLowDateTime;
  x -= (__int64)0x19db1ded53e8000; /* subtract unix epoch, Jan-01-1970 */
  return (double)x / 10000000.0;
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.0);
#endif
}


/*****************************************************************************
 * double g2ext_get_encoded_unix_time(long sec, long min, long hour,
 *                                 long mday, long mon, long year)
 *
 *   Description:
 *     Takes time components as inputs and returns the number of
 *     elapsed seconds since 1970, as a double precision floating point
 *     value.
 *
 *   Input Arguments:
 *     sec:   Seconds
 *     min:   Minutes
 *     hour:  Hours
 *     mday:  day of the month
 *     mon:   1-based month
 *     year:  complete year (i.e., not mod 1900)
 *   Returns:
 *     return value: number of seconds since 1970.
 *                   (may be negative! -1 INDICATES FAILURE, and so the time
 *                    23:59:59 31 December 1969 is excluded; it will encode to -1.)
 *
 *   Notes:
 *
 *     jh, 11/17/94.  Note that, between rev 1.12 and 1.13 of this file,
 *     cc_get_encoded_time() (on which this was based)was modified to use
 *     mktime() on all platforms, obviating the need for cc_infer_encoded_unix_
 *     time(), unless mktime fails.  I assume that mktime() was proven to do the
 *     right thing on all platforms at that time, although I can find no
 *     comments to that effect.  The original reason for
 *     g2ext_infer_encoded_unix_time() was that mktime() was misbehaving on the
 *     SGI, VMS, Solaris, and AlphaOSF platforms around the time of the G2
 *     3.0 rev 0 release.
 *
 *       This routine is a mutated version of cc_get_encoded_time, which
 *     returns a result as a fixnum.  This routine returns a double, which can
 *     represent larger values of time than fixnums, and can also represent
 *     sub-second times as used in 4.0 G2.  -ncc, 7/19/94
 *
 *       !!! mhd points out that we should determine what the limits of these
 *     time conversions are, especially, what is the largest time that can be
 *     converted to a "broken down time" and back again to an "encoded unix time".
 *
 *       ANOTHER IMPORTANT NOTE: mktime() is specified by both ANSI C and POSIX;
 *     FURTHER, Harbison & Steele declares that programmers should not depend on
 *     the return type, time_t, being a "scalar value such as a number of
 *     microseconds."  On the other hand, Donald Lewine's "POSIX Programmers
 *     Guide" states that "The type time_t is defined in <time.h>.  While it is
 *     typically an unsigned long, it can be a double or a long double."
 * 
 *     I SUPPOSE we can assume that POSIX wins here, but that still leaves open
 *     whether or not time_t is an integer or a floating point value.
 *
 *     Currently, this routine converts the result to type double via a cast, so
 *     this point is moot, but it should be noted nonetheless.  -ncc, 7/19/94
 *
 *     Note that cc_get_encoded_time has been removed in favor of this function.
 *     -jra 11/29/94
 *
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

double g2ext_get_encoded_unix_time(sec, min, hour, mday, mon, year)
     long     sec, min, hour, mday, mon, year;
{
    struct tm     time_buffer;
    time_t encoded_time;
    
    time_buffer.tm_sec = (sec);
    time_buffer.tm_min = (min); 
    time_buffer.tm_hour = (hour);
    time_buffer.tm_mday = (mday);
    time_buffer.tm_mon = (mon) - 1;
    time_buffer.tm_year = (year) - 1900;
    time_buffer.tm_isdst = -1;

    encoded_time = mktime(&time_buffer); /*  see note above about interpreting this return value. */
    return (double)encoded_time;
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/


/*****************************************************************************
 * double g2ext_infer_encoded_unix_time( double time_since_1970_no_dst )
 *
 *   Description:
 *     Takes as argument the approximate unix time since 1970,
 *     without daylight savings correction, as a double.  Returns the 
 *     encoded unix time as a double, additionally corrected for
 *     daylight savings, in a less efficient way than c_get_encoded_unix_time().
 *     If unable to do so, or if any error occurs, returns (double) -1.0
 *     
 *   Input Arguments:
 *     time_since_1970_no_dst: Number of elapsed seconds since 1970. 
 *   Returns: 
 *     return value: encoded time as double, or -1.0 if unable or error
 *   Notes:
 *     It is up to the Lisp side to decide to call this function if
 *     c_get_encoded_unix_time() fails.  If efficiency is a consideration, Lisp
 *     may simply decide to do the best it can with the current timezone and
 *     daylight savings setting without calling infer_encoded_time.
 *   Modifications:
 *     This entire function is a modification of c_infer_encoded_time, created
 *     to support gensym-encode-unix-time, which deals in unix times represented
 *     as floating point numbers.  That function was removed in favor of this
 *     one in November, 1994
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(unix) || defined(WIN32)

double g2ext_infer_encoded_unix_time(time_since_1970_no_dst)
     double     time_since_1970_no_dst;
{ 
    time_t         g2ext_current_time, time_since_1970;
    long           desired_dst, current_dst, dst_correction;
    struct tm     *time_struct;
 
    time_since_1970 = (time_t) time_since_1970_no_dst;

    time_struct = localtime(&time_since_1970); 
    if (time_struct == NULL)
        return (double) FAILURE;

    desired_dst = (long) time_struct->tm_isdst;
    if (desired_dst < 0)
        return (double)FAILURE;

    time(&g2ext_current_time);
    time_struct = localtime(&g2ext_current_time);
    if (time_struct == NULL)
        return (double)FAILURE;

    current_dst = (long) time_struct->tm_isdst;
    if (current_dst < 0)
        return (double)FAILURE;

    dst_correction = SECONDS_IN_HOUR * (desired_dst - current_dst);
    return time_since_1970_no_dst - (double) dst_correction;
}
#endif /* unix || Windows */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/


/*****************************************************************************
 * char *g2ext_current_time (void)
 *
 *   Description:
 *     Wraps the ISO C function ctime(), which returns a char pointer to a
 *     string printing the current time.  The string is overwritten by the next
 *     call to this routine, so it's value should be copied or printed
 *     immediately after this call.
 *   Input Arguments:
 *     None
 *   Returns: 
 *     return value: string of the current time, followed by a newline
 *   Notes:
 *     
 *   Modifications:
 *     
 *****************************************************************************/

char *g2ext_current_time()
{
  time_t now;

  now = time(NULL);
  return ctime(&now);
}


static TLS char time_string_buffer[50];

char *g2ext_current_time_no_newline()
{
  char *time_string = time_string_buffer;
  time_t now_universal_time;
  struct tm *now_local_time_structure;
  int result = 0;

  now_universal_time = time(NULL);

  if (now_universal_time != -1) {
    now_local_time_structure = localtime(&now_universal_time);
    if (now_local_time_structure) {
      result = strftime(time_string, 50, "%Y-%m-%d %H:%M:%S",
                        now_local_time_structure);
    }
  }
  if (!result) {
    time_string[0] = '\0';
  }
  return time_string;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      TESTING
 %
 % Description:  Module testing functions
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifdef TEST_CLOCK
exercise_time_suite()
{
  unsigned short     response[9];

  printf("g2ext_g2_clock_ticks: %ld\n", g2ext_g2_clock_ticks(536870911));
  printf("long time: %ld\n", time(NULL));
  printf("unix_time_as_float: %lf\n", g2ext_unix_time_as_float());
  c_decode_time(time(NULL) - SECONDS_FROM_1970_TO_1990, 5, 1, response);
  printf("decoded_time: %d/%d/%d, %02d:%02d:%02d, day #%d of week, %s in effect\n",
         response[4],
         response[3],
         response[5],
         response[2],
         response[1],
         response[0],
         response[6],
         response[7] ? "dst" : "dst not");

  printf("\n");
}

main(argc, argv)
     int     argc;
     char   *argv[];
{
    printf("ticks per second: %d\n\n", g2ext_g2_clock_ticks_per_second());
    
    if (argc < 2)
        exercise_time_suite();
    else
    {
        int     i, count;
     
        sscanf(argv[1], "%d", &count);
        for(i = 0; i < count; i++) {
            exercise_time_suite();
            sleep(1);
        }
    }
}
#endif /* TEST_CLOCK */



/* testing get_encoded_time() */

#ifdef TEST_ENCODE
main(argc, argv)
     int        argc;
     char      *argv[];
{
    long        sec, min, hour, date, mon, year;
    long        encoded_time;
    double      encoded_double_time;
    struct tm  *time_buffer_ptr;

    if (argc < 7) {
        printf("encode <sec> <min> <hour> <date> <1-based month> <full year, e.g. 1992>\n");
        return;
    }

    sscanf(argv[1], "%ld", &sec);
    sscanf(argv[2], "%ld", &min);
    sscanf(argv[3], "%ld", &hour);
    sscanf(argv[4], "%ld", &date);
    sscanf(argv[5], "%ld", &mon);
    sscanf(argv[6], "%ld", &year);

    printf("input: %d/%d/%d, %02d:%02d:%02d\n",
           mon, date, year - 1900, hour, min, sec);

    encoded_double_time = g2ext_get_encoded_unix_time(sec, min, hour, date, mon, year);
    encoded_time = (long)encoded_double_time;
    printf("encoded (since 1970): %ld\n", encoded_time);

    if (encoded_time == -1) return;

    time_buffer_ptr = localtime(&encoded_time);
    printf("encoded (since 1970): %ld\n", encoded_time);

    printf("output: %d/%d/%d, %02d:%02d:%02d\n",
           time_buffer_ptr->tm_mon + 1,
           time_buffer_ptr->tm_mday,
           time_buffer_ptr->tm_year,
           time_buffer_ptr->tm_hour,
           time_buffer_ptr->tm_min,
           time_buffer_ptr->tm_sec);
}
#endif /* TEST_ENCODE */



/* testing infer_encoded_time() */

#ifdef TEST_INFER
main(argc, argv)
     int     argc;
     char   *argv[];
{
    long       time_without_dst, inferred_encoded_time;
    struct tm *time_buffer_ptr;

    if (argc < 2) {
        printf("infer <time without dst correction>\n");
        return;
    }

    sscanf(argv[1], "%ld", &time_without_dst);
    printf("input: %ld\n", time_without_dst);

    inferred_encoded_time = cc_infer_encoded_time(time_without_dst);
    printf("inferred (since 1990): %ld\n", inferred_encoded_time);

    if (inferred_encoded_time == -1) return;

    inferred_encoded_time = inferred_encoded_time + SECONDS_FROM_1970_TO_1990;
    printf("inferred (since 1970): %ld\n", inferred_encoded_time);
    time_buffer_ptr = localtime(&inferred_encoded_time);
    printf("output: %d/%d/%d, %02d:%02d:%02d\n",
           time_buffer_ptr->tm_mon + 1,
           time_buffer_ptr->tm_mday,
           time_buffer_ptr->tm_year,
           time_buffer_ptr->tm_hour,
           time_buffer_ptr->tm_min,
           time_buffer_ptr->tm_sec);
}
#endif /* TEST_INFER */

