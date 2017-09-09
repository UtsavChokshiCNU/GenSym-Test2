/*
 * listvlus.c -  Chestnut Run-Time Library entry for function list_values
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object SI_cons(void);
extern Object cons(Object,Object);

#else

extern Object SI_cons();
extern Object cons();

#endif




Object list_values (x)
    Object x;
{
    Declare_local_temp;
    /* build a list of Values_count values; if Values_count > 0,
     * the first value is x, and the remaining values are in the 
     * Values buffer
     */
    register long i;
    Object result = NIL ;
    Object temp = NIL ;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(x,result,temp);    
    if (Values_count) {
	for (i = Values_count-1; i > 0; i--) {
	    temp = SI_cons();
	    M_CAR(temp) = Values[i-1];
	    M_CDR(temp) = result;
	    result = temp;
	    /* result = cons(Values[i-1], result);  would modify Values_count, not gc safe */
	}
        result = cons(x, result);
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
