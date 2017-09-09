/* basics.c
 * Input file:  basics.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "basics.h"


/* CHESTNUT-FLOORF-FUNCTION */
Object chestnut_floorf_function(fixnum_init,divisor_fixnum_init)
    Object fixnum_init, divisor_fixnum_init;
{
    SI_Long fixnum, divisor_fixnum, floor_result, remainder_result, temp;
    SI_Long positive_fixnum, positive_divisor;

    x_note_fn_call(9,0);
    fixnum = IFIX(fixnum_init);
    divisor_fixnum = IFIX(divisor_fixnum_init);
    floor_result = (SI_Long)0L;
    remainder_result = (SI_Long)0L;
    if (divisor_fixnum > (SI_Long)0L) {
	if (fixnum >= (SI_Long)0L) {
	    temp = fixnum / divisor_fixnum;
	    floor_result = temp;
	    temp = fixnum % divisor_fixnum;
	    remainder_result = temp;
	}
	else {
	    positive_fixnum =  - fixnum;
	    temp = (positive_fixnum + (divisor_fixnum - (SI_Long)1L)) / 
		    divisor_fixnum;
	    floor_result = IFIX(FIXNUM_NEGATE(FIX(temp)));
	    temp = positive_fixnum % divisor_fixnum;
	    remainder_result = temp;
	    if ( !(remainder_result == (SI_Long)0L))
		remainder_result = divisor_fixnum - remainder_result;
	}
    }
    else {
	positive_divisor =  - divisor_fixnum;
	if (fixnum >= (SI_Long)0L) {
	    temp = (fixnum + (positive_divisor - (SI_Long)1L)) / 
		    positive_divisor;
	    floor_result = IFIX(FIXNUM_NEGATE(FIX(temp)));
	    temp = fixnum % positive_divisor;
	    remainder_result = temp;
	    if ( !(remainder_result == (SI_Long)0L))
		remainder_result = divisor_fixnum + remainder_result;
	}
	else {
	    positive_fixnum =  - fixnum;
	    temp = positive_fixnum / positive_divisor;
	    floor_result = temp;
	    temp = positive_fixnum % positive_divisor;
	    remainder_result = IFIX(FIXNUM_NEGATE(FIX(temp)));
	}
    }
    return VALUES_2(FIX(floor_result),FIX(remainder_result));
}

/* CHESTNUT-MODF-FUNCTION */
Object chestnut_modf_function(fixnum_init,divisor_fixnum_init)
    Object fixnum_init, divisor_fixnum_init;
{
    SI_Long fixnum, divisor_fixnum, remainder_result, temp, positive_fixnum;
    SI_Long positive_divisor;

    x_note_fn_call(9,1);
    fixnum = IFIX(fixnum_init);
    divisor_fixnum = IFIX(divisor_fixnum_init);
    remainder_result = (SI_Long)0L;
    if (divisor_fixnum > (SI_Long)0L) {
	if (fixnum >= (SI_Long)0L) {
	    temp = fixnum % divisor_fixnum;
	    remainder_result = temp;
	}
	else {
	    positive_fixnum =  - fixnum;
	    temp = positive_fixnum % divisor_fixnum;
	    remainder_result = temp;
	    if ( !(remainder_result == (SI_Long)0L))
		remainder_result = divisor_fixnum - remainder_result;
	}
    }
    else {
	positive_divisor =  - divisor_fixnum;
	if (fixnum >= (SI_Long)0L) {
	    temp = fixnum % positive_divisor;
	    remainder_result = temp;
	    if ( !(remainder_result == (SI_Long)0L))
		remainder_result = divisor_fixnum + remainder_result;
	}
	else {
	    positive_fixnum =  - fixnum;
	    temp = positive_fixnum % positive_divisor;
	    remainder_result = IFIX(FIXNUM_NEGATE(FIX(temp)));
	}
    }
    return VALUES_1(FIX(remainder_result));
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_capability_qm, Qkfep_capability_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Hfep_capability_qm, Qhfep_capability_qm);

void basics_INIT()
{
    x_note_fn_call(9,2);
    SET_PACKAGE("AB");
    if (Kfep_capability_qm == UNBOUND)
	Kfep_capability_qm = Nil;
    if (Hfep_capability_qm == UNBOUND)
	Hfep_capability_qm = Nil;
}
