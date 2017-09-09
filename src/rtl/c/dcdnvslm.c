/*
 * dcdnvslm.c -  Chestnut Run-Time Library entry for function decode_universal_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object add(Object a, Object b);
extern Object ltimes(Object a, Object b);
extern Object ltruncate(Object,Object);

#else

extern Object add();
extern Object ltimes();
extern Object ltruncate();

#endif


#include "utime.h"

/* entry name: decode_universal_time (){} */

static int      month_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static int leap_month_days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

Object decode_universal_time (obj_time, obj_zone)
    Object obj_time, obj_zone;
{
    Object time, temp1;
    long year_length = DAY_LENGTH * 365;
    long year, month, date, day, hour, min, sec, zone;
    int d;
    extern Object xmake_canonical_rational();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(obj_time, obj_zone);
    
    if (!SUPPLIED_P(obj_zone) || obj_zone == NIL) zone = get_local_time_zone();
    else
	/* obj_zone might be a ratio, so need to truncate */
	/* it is simplier than check if it is an i.m. of 1/3600 */
	/* by the way, Lucid does not support ratio zone at all */
	zone = IFIX(ltruncate(ltimes(obj_zone, 
					  FIX(HOUR_LENGTH)),FIX(1L)))
	      /** GMT normalization **/
              /* Lucid does, and this is not a bad idea */
	      % DAY_LENGTH ;

    time = add(obj_time,FIX( - zone + year_length));

    MVS_2(ltruncate(time, FIX(year_length)), temp1, time);
    year = IFIX(temp1);

    /* should be a fixnum */
    sec = IFIX(time);
    day = (year*365 + sec/DAY_LENGTH - 1) % 7;
  
    year += 1899;
    sec -= (leap_days_since_1900(year-1) * DAY_LENGTH);
    while (sec < 0) sec = year_length + (leap_year_p(--year)
	                              ? DAY_LENGTH : 0) + sec;
    min = sec / 60;
    sec = sec % 60;
    hour = min / 60;
    min = min % 60;
    date = hour / 24;
    date++;
    hour = hour % 24;

    for (month = 1;
	 date > (d = leap_year_p(year) 
		 ? leap_month_days[month-1]
		 : month_days[month-1]); date -= d,month++);

    obj_zone = xmake_canonical_rational(FIX(zone),FIX(HOUR_LENGTH));
    RESTORE_STACK();
    return VALUES_9(FIX(sec),FIX(min),FIX(hour),FIX(date),
		    FIX(month),FIX(year),FIX(day),NIL,
		    obj_zone);

}
