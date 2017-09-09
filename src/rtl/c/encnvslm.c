/*
 * encnvslm.c -  Chestnut Run-Time Library entry for function encode_universal_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object add(Object a, Object b);
extern Object ltimes(Object a, Object b);
extern Object ltruncate(Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern Object add();
extern Object ltimes();
extern Object ltruncate();

#endif


#include "utime.h"

/* entry name: encode_universal_time (){} */

static int      month_offsets[12] = 
           {0,31,59,90,120,151,181,212,243,273,304,334};
static int leap_month_offsets[12] = 
           {0,31,60,91,121,152,182,213,244,274,305,335};

 

Object encode_universal_time (obj_sec, obj_min, obj_hour, 
			      obj_date, obj_month, obj_year, obj_zone)
    Object obj_sec, obj_min, obj_hour, obj_date, obj_month, obj_year, obj_zone;
{
    Declare_local_temp;
    int sec, min, hour, date, month, year;
    long  zone;
    /* nothing should be protected */
    /* all arguments must be of type fixnum */

    if (FIXNUM_LT(obj_year, FIX(100)))
	/* Nearest year to present equal to year mod 100. */
	/* THIS WON'T WORK FOR YEARS AFTER 2000 (i.e. year < 41) - FIX LATER */
	obj_year = FIXNUM_ADD(obj_year, FIX(1900));

    if (!(
	  (sec  = FIXNUM_TO_INT(obj_sec))    >= 0 && sec   <= 59 &&
	  (min  = FIXNUM_TO_INT(obj_min))    >= 0 && min   <= 59 &&
	  (hour = FIXNUM_TO_INT(obj_hour))   >= 0 && hour  <= 23 &&
	  (date = FIXNUM_TO_INT(obj_date))   >= 1 && date  <= 31 &&
	  (month= FIXNUM_TO_INT(obj_month)) >= 1 && month <= 12 &&
	  (year = FIXNUM_TO_INT(obj_year))   >= 1900 &&
	  (zone = (SUPPLIED_P(obj_zone) && obj_zone != NIL) 
	     ? IFIX(ltruncate(ltimes(obj_zone,
				     FIX(HOUR_LENGTH)),FIX(1L)))
	       % DAY_LENGTH
	     : get_local_time_zone()) >=   - DAY_LENGTH && 
	  zone <= DAY_LENGTH))
	error(1, "bad time or zone");

    return VALUES_1(add(ltimes(FIX(DAY_LENGTH),
			       FIX((year - 1900) * 365 +
				   leap_days_since_1900(year-1) +
				   (leap_year_p(year) 
				   ? leap_month_offsets[month-1]
				   : month_offsets[month-1]) + date-1)),
			FIX( hour * HOUR_LENGTH + min * 60 + zone + sec)));
}
