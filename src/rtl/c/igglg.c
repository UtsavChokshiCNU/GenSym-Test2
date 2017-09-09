/*
 * igglg.c -  Chestnut Run-Time Library entry for function integer_to_unsigned_long
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
extern unsigned long bignum_to_unsigned_long (bignum_type);

#else

extern Object (*SI_warn_fptr) ();
extern int bignum_fits_in_word_p ();
extern unsigned long bignum_to_unsigned_long ();

#endif




SI_Ulong integer_to_unsigned_long (n)
    Object n;
{
    SI_Long l;

    if (FIXNUMP(n)) {
	if (FIXNUM_MINUSP(n)) goto LOSE;
	return (SI_Ulong) IFIX(n);
    } else
	switch (SI_STORED_OBJECT_TYPE(n)) {
	case OBIGNUM_TYPE:
	    l = BIGNUM_VALUE(n);
	    if (l < 0) goto LOSE;
	    return l;
	case XBIGNUM_TYPE:
	    if (!bignum_fits_in_word_p(n, (long)64, 0))
		goto LOSE;
	    return bignum_to_unsigned_long(n);
	}
 LOSE:
    warn(2, "integer_to_unsigned_long: invalid argument - ~S", n);
    return 0L;
}
