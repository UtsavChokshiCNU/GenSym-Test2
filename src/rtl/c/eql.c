/*
 * eql.c -  Chestnut Run-Time Library entry for function eql
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

extern enum bignum_comparison (*SI_bignum_compare)();

#else

extern enum bignum_comparison (*SI_bignum_compare)();

#endif




/*
 * Assume that EQ will handle all character and fixnum comparisons.
 * Assume that bignums are never within fixnum range.
 * Assume that rationals are in lowest terms.
 */
Object eql (a, b)
    Object a, b;
{
    Declare_local_temp;
    enum SI_type type;
    Object result;
    double d_a;

    if (EQ(a, b))
	result = T;
    else if (IMMEDIATE_P(a) || IMMEDIATE_P(b))
	result = NIL;
    else if ((type = SI_STORED_OBJECT_TYPE(a)) != SI_STORED_OBJECT_TYPE(b))
	result = NIL;
    else
	switch (type) {
	case DOUBLE_TYPE:	
	    result = (d_a = IDOUBLE(a)) == IDOUBLE(b) ? T : NIL;
	    break;
	case XBIGNUM_TYPE:
	    result = (*SI_bignum_compare)(a, b) == bignum_comparison_equal ? T : NIL;
	    break;
	case OBIGNUM_TYPE:
	    result = BIGNUM_VALUE(a) == BIGNUM_VALUE(b) ? T : NIL;
	    break;
	case RATIO_TYPE:
	    result = (TRUEP(eql(RATIO_NUMERATOR(a),   RATIO_NUMERATOR(b))) &&
		      TRUEP(eql(RATIO_DENOMINATOR(a), RATIO_DENOMINATOR(b))))
		? T : NIL;
	    break;
	case COMPLEX_TYPE:
	    result = (TRUEP(eql(COMPLEX_REAL(a), COMPLEX_REAL(b))) &&
		      TRUEP(eql(COMPLEX_IMAG(a), COMPLEX_IMAG(b))))
		? T : NIL;
	    break;
	default:
	    result = NIL;
	}
    return VALUES_1(result);
}
