/*
 * ltime.h - time functions externals
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

/* IINTERNAL_TIME_UNITS_PER_SECOND is a true parameter; you can set it
   independent of which underlying OS routines are used in the
   implementation.  Valid values (given the way this code is written)
   are integers between 1000 and 1000000.  The smaller it is, the less
   likely you are to overflow from fixnums to bignums.  The larger it
   is, the better resolution you'll get, assuming the operating system
   can give you that resolution.

    Value      Bignum threshold
      1000       7 days
      10000      15 hours
      100000     90 minues
      1000000    9 minutes
 */

#define IINTERNAL_TIME_UNITS_PER_SECOND 1000L

#if defined (WIN32)
#	ifdef __cplusplus
extern "C" {
#	endif

extern unsigned long (__stdcall *g_real_time_provider) (void);
extern unsigned long g_real_time_base_value;

#	ifdef __cplusplus
}
#	endif
#endif