/*
 * ingrlng.c -  Chestnut Run-Time Library entry for function integer_to_long
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern int bignum_fits_in_word_p (bignum_type, long word_length, int twos_complement_p);
extern SI_Long bignum_to_long (bignum_type);

#else

extern Object (*SI_warn_fptr) ();
extern int bignum_fits_in_word_p ();
extern SI_Long bignum_to_long ();

#endif




SI_Long integer_to_long (n)	/* formerly object_to_clong */
    Object n;
{
    SI_int64 i, lower, upper;

    if (FIXNUMP(n))
	return IFIX(n);
    else
	switch (SI_STORED_OBJECT_TYPE(n)) {
	case OBIGNUM_TYPE:
	    return BIGNUM_VALUE(n);
	case XBIGNUM_TYPE:
	    if (!bignum_fits_in_word_p(n, 64, 1))
		goto LOSE;
	    return bignum_to_long(n);
	case LONG64_TYPE:
	    i = ILONG64(n);
	    upper = (SI_int64) IMOST_POSITIVE_FIXNUM;
	    lower = (SI_int64) IMOST_NEGATIVE_FIXNUM;
	    if (i > upper || i < lower)
		goto LOSE;
	    return (SI_Long) i;
	}
 LOSE:
    warn(2, "integer_to_long: invalid argument - ~S", n);
    return 0L;
}
