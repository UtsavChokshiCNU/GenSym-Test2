/*
 * conctnt.c -  Chestnut Run-Time Library entry for function concatenate
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qlist;

#if SI_USE_PROTOTYPES

extern Object clong_to_bignum(SI_Long a);
extern Object cons(Object,Object);
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object make_sequence(Object type, Object lsize, Object initial_element);
extern Object nreverse(Object);
extern Object set_elt(Object,Object,Object);

#else

extern Object clong_to_bignum();
extern Object cons();
extern Object elt();
extern long ilength();
extern Object make_sequence();
extern Object nreverse();
extern Object set_elt();

#endif


#include "concatnt.h"

Object concatenate varargs_1(int, n)
{
    Declare_local_temp;
    Object result = NIL, last = NIL, temp, seq;
    Object result_type;
    long k, j, ssize = 0L; long i;
    Declare_stack_pointer;
    Object *args;
    va_list ap;

    SI_va_start(ap,n);
    SAVE_STACK();
    PROTECT_2(result,last);
    PROTECTI_3(result_type,temp,seq);

    result_type = va_arg(ap, Object);
    --n;

    SPREAD_ARGS(n, ap, args);

    if (EQ(result_type, Qlist)) {
	for (i = 0; i < n; i++) {
	    seq = args[i];
	    ssize = ilength(seq);
	    for (j = 0; j < ssize; j++) {
		temp = elt(seq, FIX(j));
		result = cons(temp, result);
	    }
	}
	result = nreverse(result); /* !!!! */
    }
    else {
	for (i = 0; i < n; i++)
	    ssize += ilength(args[i]);
	result = make_sequence(result_type, LONG_TO_INTEGER(ssize), KOPT);
	for (k = 0, i = 0; i < n; i++) {
	    seq = args[i];
	    ssize = ilength(seq);
	    for (j = 0; j < ssize; j++, k++) {
		temp = elt(seq, FIX(j));
		set_elt(result, FIX(k), temp);
	    }
	}
    }
    va_end(ap);
    RESTORE_STACK();
    return VALUES_1(result);
}
