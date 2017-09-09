/*
 * lsleep.c -  Chestnut Run-Time Library entry for function lsleep
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#ifdef ultrix
#include <cursesX.h>
#endif

#if defined(WIN32)
#include <windows.h>
#endif

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern double object_to_cdouble(Object n);

#else

extern double object_to_cdouble();

#endif



#if defined(MSDOS) && defined(NEVER_USED)
FORWARD_STATIC long get_system_time();

Object lsleep(lsecs)
    Object lsecs;
{
    Declare_local_temp;
    long secs = IFIX(lsecs);
    long hsecs = 100L * secs;
    long time1, get_system_time();
    long nearmid = 0L, check_time;

    time1 = get_system_time();
    if ((time1 + hsecs) > 864000L)
	nearmid = (1 - (hsecs + 50L));
    check_time = hsecs + time1 + nearmid;
    while ((get_system_time() + nearmid) <= check_time) {
	if (kbhit()) {
	    getch();
	    return VALUES_1(NIL);
	}
    }
    return VALUES_1(NIL);
}

static long get_system_time()
{
    long	hsecs;
    union REGS regs;

    regs.x.ax = 0x2c00;
    int86(0x21, &regs, &regs);
    hsecs = ((((long) ((unsigned int) regs.x.cx >> 8)) * 360000L) + 
	     (((long) ((unsigned int) regs.x.cx & 0xff)) * 6000L) +
	     (((long) ((unsigned int) regs.x.dx >> 8)) * 100L) +
	     ((long) ((unsigned int) regs.x.dx & 0xff)));
    return (hsecs);
}

#else

/* Argument to lsleep may be a float.  It would be nice if this were 
   accurate to 100 ms. 
   Argument to Unix's "usleep" is in microseconds.
   Unix documentation vol. 2 says usleep requires 8 system calls.
   Eventually replace usleep with a select() loop. */

#ifdef NeXT
#include <sys/time.h>
#endif

void select_sleep (msec)
     long msec;
{
  
#ifdef vms
  float vms_sleep_time;

  vms_sleep_time = msec / 1000000.0;
  lib$wait (vms_sleep_time);
  return;
#endif

#ifdef unix
  struct timeval		timeout;

  if (msec > 0) {
    timeout.tv_sec = msec / 1000000;
    timeout.tv_usec = (msec - (1000000 * timeout.tv_sec));
    select(0, NULL, NULL, NULL, &timeout);
  }
  return;
#endif

#if defined(WIN32)
  Sleep( (msec/1000) );
#endif /* Win32 */


#if !defined(unix) && !defined(vms)
/* add sleep techniques for other platforms here */
#endif

}

#ifdef _INTELC32_
#define MICROSLEEP(a) /*Noop*/
#else
#define MICROSLEEP(a) (select_sleep(a))
#endif

Object lsleep(secs)
    Object secs;
{
    Declare_local_temp;
    double dsecs;

    if (FIXNUMP(secs))
#     if defined(WIN32)
	Sleep( ( IFIX(secs) * 1000 ) );
#     else
	sleep(IFIX(secs));
#     endif
    else {
	dsecs = object_to_cdouble(secs);
#ifdef VMS
	sleep ((unsigned)ceil(dsecs));
#else
	/* Assume unsigned = unsigned long */
	if (0.0 < dsecs && dsecs < 1073.741824)
	    MICROSLEEP((unsigned long)(dsecs * 1000000.0));
	else
#         if defined(WIN32)
	    Sleep( ((DWORD)dsecs * 1000) );
#         else
	    sleep ((unsigned)dsecs);
#         endif
#endif
    }
    return VALUES_1(NIL);
}
#endif

