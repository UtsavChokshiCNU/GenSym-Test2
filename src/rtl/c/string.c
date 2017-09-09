/*
 * string.c -  Chestnut Run-Time Library entry for function string
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object make_string(Object size, Object initial_element);
extern Object symbol_name(Object);

#else

extern Object (*SI_error_fptr) ();
extern Object make_string();
extern Object symbol_name();

#endif

Object string (x)
    Object x;
{
    extern void g2ext_print_backtrace();
    Declare_local_temp;
    SI_Declare_static_string(unbound_str, d, "UNBOUND");

    if (STRINGP(x))
	return VALUES_1(x);
    else if (SYMBOLP(x))
	return SYMBOL_NAME(x);
    else if (CHARACTERP(x))
	return make_string(FIX(1L), x);
    /* AT&T workaround for ODBC bridge -binghe, 2013/11/21 */
    else if (UNBOUND == x)
        return VALUES_1(unbound_str);
    else {
	g2ext_print_backtrace();
	return error(2, "string: invalid argument - ~S", x);
    }
}
