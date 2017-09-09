/*
 * rdrmsrng.c -  Chestnut Run-Time Library entry for function read_from_string
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object lread(Object,Object,Object,Object);
extern Object make_string_input_stream(Object,Object,Object);
extern Object read_preserving_whitespace(Object,Object,Object,Object);

#else

extern Object lread();
extern Object make_string_input_stream();
extern Object read_preserving_whitespace();

#endif



/* &optional 1 2 */
Object read_from_string (string, eof_error_p, eof_value, start, end, 
			preserve_whitespace)
    Object string;
    Object eof_error_p, eof_value;  /* &optional */
    Object start, end, preserve_whitespace;
{
    Declare_local_temp;
    Object stream = make_string_input_stream(string, start, end);
    Object result, index;

/*
format(3, t, "read_from_string: string=~s~%", string);
format(7, t, "rfs: eof_error_p=~s, eofval=~s, start=~s, end=~s, pw=~s~%",
eof_error_p, eof_value, start, end, preserve_whitespace);
*/

    if (UNSUPPLIED_P(preserve_whitespace)) preserve_whitespace = NIL;

    if (TRUEP(preserve_whitespace))
	result = read_preserving_whitespace(stream,eof_error_p, eof_value, NIL);
    else
	result = lread(stream, eof_error_p, eof_value, NIL);
    index = SECOND(STREAM_OBJ(stream));

/* format(4, t, "rfs: returning result=~s, index=~s~%", result, index); */

    return(VALUES_2(result, index));
}
