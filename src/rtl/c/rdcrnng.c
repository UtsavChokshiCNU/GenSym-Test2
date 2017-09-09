/*
 * rdcrnng.c -  Chestnut Run-Time Library entry for function read_char_no_hang
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object chase_input_stream(Object stream);
extern Object llisten(Object);
extern Object read_char(Object,Object,Object,Object);

#else

extern Object chase_input_stream();
extern Object llisten();
extern Object read_char();

#endif


/* &optional 0 4 */
Object read_char_no_hang (input_stream, eof_error_p, eof_value, recursive_p)
    Object input_stream, eof_error_p, eof_value, recursive_p;
{
    Declare_local_temp;
    Object ostream;

    MVS_2(chase_input_stream(input_stream), input_stream, ostream);
    if (llisten(input_stream))
	return(read_char(input_stream, eof_error_p, eof_value, recursive_p));
    return VALUES_1(NIL);
}
