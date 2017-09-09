/*
 * gnvrslm.c -  Chestnut Run-Time Library entry for function get_universal_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern void SET_BIGNUM_DIGIT(Object bignum, SI_Dimension number, SI_Long high, SI_Long low);
extern Object STATIC_POSITIVE_BIGNUM(SI_Dimension length);
extern Object add(Object a, Object b);
extern Object clong_to_bignum(SI_Long a);

#else

extern void SET_BIGNUM_DIGIT();
extern Object STATIC_POSITIVE_BIGNUM();
extern Object add();
extern Object clong_to_bignum();

#endif




/* Relying on Unix's time encoding/decoding is definitely a bad idea.
   These routines need a rewrite. */

/*
 * Unix's epoch is 70 years later than Common Lisps, which is a difference of 
 * 2208988800 seconds (= (encode-universal-time 0 0 0 1 1 1970 0)).
 */

static Object Unix_epoch = UNBOUND;
#define UNIX_EPOCH_LOW	0x3AA7E80
#define UNIX_EPOCH_HIGH	0x2

Object get_universal_time ()
{
    Declare_local_temp;
    time_t ltime;
			       
    if (Unix_epoch == UNBOUND) {
#ifdef NEW_BIGNUMS
      Unix_epoch = STATIC_POSITIVE_BIGNUM(2);
      SET_BIGNUM_DIGIT(Unix_epoch, 0,
		       (UNIX_EPOCH_LOW >> 15),
		       (UNIX_EPOCH_LOW & 0x7FFF));
      SET_BIGNUM_DIGIT(Unix_epoch, 1,
		       (UNIX_EPOCH_HIGH >> 15),
		       (UNIX_EPOCH_HIGH & 0x7FFF));
#else
      error(1, "get-universal-time unimplemented without new bignums.");
      /*NOTREACHED*/
#endif
    }

    time(&ltime);
    return VALUES_1(add(LONG_TO_INTEGER((SI_Long)ltime), Unix_epoch));
}
