/*
 * pprint.c -  Chestnut Run-Time Library entry for function pprint
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
DECLARE_VARIABLE(Print_escape);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_radix);

#if SI_USE_PROTOTYPES

extern Object lwrite(Object object, Object stream, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);
extern Object terpri(Object);

#else

extern Object lwrite();
extern Object terpri();

#endif




/* &optional 1 1 calls &key */
Object pprint (object, output_stream)
    Object object, output_stream;
{
    Declare_local_temp;
    terpri(output_stream);
    lwrite(object, output_stream,
	   Print_escape, Print_radix, Print_base, Print_circle, T,
	   Print_level, Print_length, Print_case, Print_gensym, Print_array);
    return VALUES_1(NIL);
}
