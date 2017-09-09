/*
 * writechr.c -  Chestnut Run-Time Library entry for function write_char
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

DECLARE_VARIABLE(Print_array);
DECLARE_VARIABLE(Print_base);
DECLARE_VARIABLE(Print_case);
DECLARE_VARIABLE(Print_circle);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_pretty);
DECLARE_VARIABLE(Print_radix);

#if SI_USE_PROTOTYPES

extern Object lwrite(Object object, Object stream, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);

#else

extern Object lwrite();

#endif




/* &optional 1 1 calls &key */
Object write_char(ch, output_stream)
    Object ch;
    Object output_stream;
{
    /* pass NIL as Print_escape --Steele does not specify */
    return(lwrite(ch, output_stream,
	NIL, Print_radix, Print_base, Print_circle, Print_pretty,
	Print_level, Print_length, Print_case, Print_gensym, Print_array));
}
