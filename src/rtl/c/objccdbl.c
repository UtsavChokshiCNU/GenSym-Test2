/*
 * objccdbl.c -  Chestnut Run-Time Library entry for function object_to_cdouble
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif

#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern double bignum_to_double (bignum_type);

#else

extern Object (*SI_warn_fptr) ();
extern double bignum_to_double ();

#endif




/* Double-float */
/* This should be renamed to double_float_to_double() */

double object_to_cdouble (n)	/* Cf. IDOUBLE, DOUBLE_FLOAT_TO_DOUBLE */
    Object n;
{
    double num, den;
    double result;
    SI_int64 long_value;

    if (FIXNUMP(n))
	return (double) IFIX(n);
    else
	switch (SI_STORED_OBJECT_TYPE(n)) {
	case DOUBLE_TYPE:
	    return IDOUBLE(n);
	case OBIGNUM_TYPE:
	    return (double) BIGNUM_VALUE(n);
	case XBIGNUM_TYPE:
	    return bignum_to_double(n);
	case RATIO_TYPE:
	    num = object_to_cdouble(RATIO_NUMERATOR(n));
	    den = object_to_cdouble(RATIO_DENOMINATOR(n));
	    return num / den;
	case LONG64_TYPE:
	    long_value = ILONG64(n);
	    result = (double) long_value;
	    return result;
	default:
	    warn(2, "object_to_cdouble: invalid argument - ~S", n);
	    return 0.0;
	}
}
