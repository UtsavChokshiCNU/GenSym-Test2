/*
 * yornpn.c -  Chestnut Run-Time Library entry for function y_or_n_pn
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "svargs.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void SI_y_or_n_p_aux(long v, char *format_string, VA_LIST ap);
extern Object SI_y_or_n_p_query(void);

#else

extern char *SI_istring();
extern void SI_y_or_n_p_aux();
extern Object SI_y_or_n_p_query();

#endif


/* &optional 0 1 */
Object y_or_n_pn varargs_1(int, n)
{
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object result;
    Object format_string;

    if (n) {
	VA_START(ap,n);
    
	format_string = VA_ARG(ap,Object);
	SI_y_or_n_p_aux(n-1, ISTRING(format_string),ap);
	VA_END(ap);
    }
    result = SI_y_or_n_p_query();
    return result;
}
