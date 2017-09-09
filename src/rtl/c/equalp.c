/*
 * equalp.c -  Chestnut Run-Time Library entry for function equalp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object array_dimensions(Object);
extern Object array_rank(Object);
extern Object array_total_size(Object);
extern Object do_aref_1(Object arr, long i);
extern Object equal(Object,Object);
extern Object length(Object);
extern Object num_eq(Object a, Object b);
extern Object numberp(Object);
extern Object string_equal(Object string1, Object string2, Object start1, Object end1, Object start2, Object end2);
extern Object equalp(Object,Object);

#else

extern Object array_dimensions();
extern Object array_rank();
extern Object array_total_size();
extern Object do_aref_1();
extern Object equal();
extern Object length();
extern Object num_eq();
extern Object numberp();
extern Object string_equal();
extern Object equalp();

#endif

#include "equal.h"

/* entry name: equalp(){} */

static Object array_equalp (x, y)
    Object x, y;
{
    Declare_local_temp;
    long i, size;
    Object xrank, yrank, xsize, ysize, xdim, ydim;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    PROTECTI_6(xrank,yrank,xsize,ysize,xdim,ydim);
    if (EQ((xrank = array_rank(x)), (yrank = array_rank(y))) &&
	((xdim = array_dimensions(x)), /* array_dimensions conses */
	 (ydim = array_dimensions(y)), /* prevent hidden arg temp */
	 TRUEP(equal(xdim, ydim)))) {
	if (VECTORP(x) || VECTORP(y)) {
	    xsize = length(x);
	    if (xsize != length(y)) {
		RESTORE_STACK();
		return VALUES_1(NIL);
	    }
	}
	else {
	    xsize = array_total_size(x);
	}
	size = IFIX(xsize);
	for (i = 0L; i < size; i++) {
	    if (equalp(do_aref_1(x, (i)), do_aref_1(y, (i))) == NIL) {
		RESTORE_STACK();
		return VALUES_1(NIL);
	    }
	}
	RESTORE_STACK();
	return VALUES_1(T);
    }
    RESTORE_STACK();
    return VALUES_1(NIL);
}

#define STRUCTURE_SIZE(o) SI_INSTANCE_FIELD(o,SI_Header,gclength)
#define STRUCTURE_NUMBER_OF_FIELDS(o,sz) \
    (sz - (((SI_Ulong) &STRUCTURE_ELEMENT(o,0)) -((SI_Ulong)o))/sizeof(Object))

static Object structure_equalp(x, y)
    Object x, y;
{
    Declare_stack_pointer;
    SI_Dimension sz_x, i_x, d_x;
    short still_equalp;

    SAVE_STACK();
    PROTECT_2(x,y);

    if (!((sz_x = STRUCTURE_SIZE(x)) == STRUCTURE_SIZE(y))) {
	RESTORE_STACK();
	return VALUES_1(NIL);
    }
    if (!(SI_STRUCTURE_HEADER(x) == SI_STRUCTURE_HEADER(y))) {
	RESTORE_STACK();
	return VALUES_1(NIL);
    }
    for (d_x = STRUCTURE_NUMBER_OF_FIELDS(x,sz_x),
	 i_x = 0,
	 still_equalp = 1;
	 i_x < d_x && still_equalp;
	 i_x++) 
	still_equalp = TRUEP(equalp(STRUCTURE_ELEMENT(x,i_x),
				    STRUCTURE_ELEMENT(y,i_x)));
    RESTORE_STACK();
    return VALUES_1(still_equalp ? T : NIL);
}

#undef STRUCTURE_SIZE
#undef STRUCTURE_NUMBER_OF_FIELDS

Object equalp (x, y)
    Object x, y;
{
    Declare_local_temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    /* Gc protection appears necessary because of the loop in the
       case of lists, which contains recursive calls to equalp,
       which might call array_equalp, which conses because the
       function array_dimensions conses.
       */

    if (EQ(x, y)) {
	RESTORE_STACK();
	return VALUES_1(T);
    }
    if (CHARACTERP(x)) { 
	RESTORE_STACK();
	return(VALUES_1(CHARACTERP(y) && CHAR_EQUAL(x, y)) ? T : NIL);
	}
    if (TRUEP(numberp(x))) {
	RESTORE_STACK();
	return(TRUEP(numberp(y)) ? num_eq(x, y) : VALUES_1(NIL));
    }
    if (CONSP(x)) {
	if (!CONSP(y)) {
	    RESTORE_STACK();
	    return VALUES_1(NIL);
	}
	/* two CONSes:  do element wise comparison */
	while(!(ATOM(x) || ATOM(y))) {
	    if (equalp(M_CAR(x), M_CAR(y)) == NIL) {
		RESTORE_STACK();
		return VALUES_1(NIL);
	    }
	    x = M_CDR(x);
	    y = M_CDR(y);
	}
	/* test last cell in case dotted pair or lengths unequal */
	RESTORE_STACK();
	return(equalp(x, y));
    }
    else if (STRINGP(x) && STRINGP(y)) {
	RESTORE_STACK();
	return(string_equal(x, y, NIL,NIL,NIL,NIL));
    } else if (ARRAYP(x)) {
	RESTORE_STACK();
	return(ARRAYP(y) ? array_equalp(x, y) : VALUES_1(NIL));
    } else if (STRUCTURE_OBJECT_P(x)) {
	RESTORE_STACK();
	return (STRUCTURE_OBJECT_P(y) ? structure_equalp(x,y) : VALUES_1(NIL));
    } else {
	RESTORE_STACK();
	return(equal(x, y));
    }
}
