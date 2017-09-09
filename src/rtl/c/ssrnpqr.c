/*
 * ssrnpqr.c -  Chestnut Run-Time Library entry for function SI_yes_or_no_p_query
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Query_io;

#if SI_USE_PROTOTYPES

extern void SI_clear_whitespace_input(Object stream);
extern char *SI_istring(Object o);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object read_line(Object,Object,Object,Object);

#else

extern void SI_clear_whitespace_input();
extern char *SI_istring();
extern Object format();
extern Object read_line();

#endif


#include "svargs.h"

Object SI_yes_or_no_p_query()
{
    Declare_local_temp;
    Object ans;

    FOREVER {
	format(2, Query_io, " (Yes or No) ");
	SI_clear_whitespace_input(Query_io);
	ans = read_line(Query_io, NIL, NIL, NIL);
	if (STRINGP(ans)) {
	    if (!_stricmp(ISTRING(ans), "YES")) {
		return VALUES_1(T);
	    }
	    if (!_stricmp(ISTRING(ans), "NO")) {
		return VALUES_1(NIL);
	    }
	}
	format(2, Query_io, "Please type Yes or No.~%");
    }
}
