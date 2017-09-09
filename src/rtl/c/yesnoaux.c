/*
 * yesnoaux.c -  Chestnut Run-Time Library entry for function yes_no_aux
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "svargs.h"

extern Object Query_io;

#if SI_USE_PROTOTYPES

extern Object char_equal(Object a, Object b);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object fresh_line(Object);
extern Object read_char(Object,Object,Object,Object);
extern Object unread_char(Object,Object);
extern Object do_format(long nvar, Object stream, char *lstr,
			Stack_item_ptr vargs);

#else

extern Object char_equal();
extern Object format();
extern Object fresh_line();
extern Object read_char();
extern Object unread_char();
extern Object do_format();

#endif


/* yes_no_aux() {} */

void SI_clear_whitespace_input(stream)
    Object stream;
{
    Object ch;

    while((ch = read_char(stream,NIL,NIL,NIL))) {
	if (!(WHITESPACE_CHAR_P(ch))) {
	    unread_char(ch, stream);
	    break;
	}
    }
}

void SI_y_or_n_p_aux (v, format_string, ap)
    long v;
    char *format_string;
    VA_LIST ap;
{
	fresh_line(Query_io);
	do_format(v, Query_io, format_string, ap);
}

Object SI_y_or_n_p_query ()
{
    Declare_local_temp;
    Object ans;
/*
    Object name;
*/

    FOREVER {
	format(2, Query_io, "(Y or N) ");
	SI_clear_whitespace_input(Query_io);
/*
	ans = lread(Query_io,NIL,NIL,NIL);
	if (SYMBOLP(ans) && (name = symbol_name(ans)))
	    ans = elt(name, ZERO);
 */
	ans = read_char(Query_io, NIL,NIL,NIL);
	if (CHARACTERP(ans)) {
	    if (char_equal(ans, CHR('Y'))) {
		fresh_line(Query_io);
		return VALUES_1(T);
	    }
	    else if (char_equal(ans, CHR('N'))) {
		fresh_line(Query_io);
		return VALUES_1(NIL);
	    }
	}
	format(2, Query_io, "~%Please type one of Y or N.~%");
    }
}

