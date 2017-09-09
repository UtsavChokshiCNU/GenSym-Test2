/*
 * utime_aux.h - time functions include file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */
#ifndef _CN_UTIME_INCLUDED  /* standard trick to prevent multiple inclusion */
#define _CN_UTIME_INCLUDED

#define DAY_LENGTH 86400
#define HOUR_LENGTH 3600
#define TWELVE_HOURS  43200

static long get_local_time_zone ()
{
#if defined(sun) && !defined(__SVR4)
    time_t ltime;
    struct tm *here;
    time(&ltime);
    here = localtime(&ltime); /* obtain data structure & time zone */
    return( - here->tm_gmtoff);
#else
    return(5L);
#endif
}

static int leap_days_since_1900 (year)
    int year;
{
    year -= 1900;
    return( year / 4 + (year+300)/400 - year / 100);
}

static int leap_year_p(year)
    int year;
{
    return( (year%4 == 0 && (year%100 != 0 || year%400 == 0)) ? 1 : 0);
}

#endif /* _CN_UTIME_INCLUDED */
