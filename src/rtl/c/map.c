/*
 * map.c -  Chestnut Run-Time Library entry for function map
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qlist;

#if SI_USE_PROTOTYPES

extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);
extern Object cons(Object,Object);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern long ilength(Object sequence);
extern Object make_sequence(Object type, Object lsize, Object initial_element);

#else

extern Object SI_internal_funcall();
extern Object cons();
extern Object do_aref_1();
extern Object do_setf_aref();
extern long ilength();
extern Object make_sequence();

#endif




/* stack-based map */
Object map varargs_1(int, n)
{
    Declare_local_temp;
    long iterate, length;
    long i, j, arity;
    Object result, last, temp;
    Object result_type, function;
    Declare_stack_pointer;
    Stack_item *temp_ptr;
    va_list ap;

    SI_va_start(ap,n);
    SAVE_STACK();
    PROTECTI_3(result_type,function,result);
    PROTECTI_1(last); /* only for reallocating GC */
 
    result = NIL;
    result_type = va_arg(ap, Object);
    function = va_arg(ap, Object);
    arity = n - 2;
    /* spread the sequences onto the stack, find the 
       length of the shortest  one  and arity of function call */
    for (i = 1, temp_ptr = Stack,
	 iterate = ilength((STACK_PUSH(va_arg(ap,Object)), STACK_REF(-1)));
	 i < arity ; i++) 
	if ((length = ilength((STACK_PUSH(va_arg(ap,Object)), STACK_REF(-1)))) < iterate)
	    iterate = length;
    
    va_end(ap);
    /* iterate the function application with corresponding arrguments */
    for (i = 0; i < iterate; i++) {

	/* push arguments onto the stack */
	for (j = 0; j < arity; j++) {
	    temp = temp_ptr[j].object;
 	    if (ARRAYP(temp)) 
		STACK_PUSH(do_aref_1(temp,i));
	    else {
		temp_ptr[j].object = M_CDR(temp);
		STACK_PUSH(M_CAR(temp));
	    }
	}
	
	if (result_type == Qlist) {
	    if (result == NIL)
		result = last = cons(NIL,NIL);
	    else {
		temp = cons(NIL,NIL);
		RPLACD(last, temp);
		last = M_CDR(last);
	    }
	    temp = internal_funcall(function,arity,NIL);
	    RPLACA(last, temp);
	}
	else if (result_type == NIL) /* let result be NIL, but do call */
	    temp = internal_funcall(function,arity,NIL);
	else {       /* should be array or vector or string */
	    if (result == NIL)
		result = make_sequence(result_type, FIX(iterate), KOPT);
	    do_setf_aref(result, i, internal_funcall(function, arity, NIL));
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
