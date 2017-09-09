/*
 * flatsize.c -  Chestnut Run-Time Library entry for function flatsize
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern SI_Area Local_area;
DECLARE_VARIABLE(Print_array);
DECLARE_VARIABLE(Print_base);
DECLARE_VARIABLE(Print_case);
DECLARE_VARIABLE(Print_circle);
DECLARE_VARIABLE(Print_escape);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_pretty);
DECLARE_VARIABLE(Print_radix);
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern long SI_gc_count;

#if SI_USE_PROTOTYPES

extern void restore_frontier(SI_Segment *seg, void *frontier);
extern Object write_to_string(Object object, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);

#else

extern void restore_frontier();
extern Object write_to_string();

#endif



Object flatsize(arg)
    Object	arg;
{
    Declare_local_temp;
    FIXNUM len;
    Object temp;
    DECLARE_AREA(prev_area); DECLARE_FRONTIER(prev_pos);

    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
    temp = write_to_string(arg,
	Print_escape, Print_radix, Print_base, Print_circle, Print_pretty,
	Print_level, Print_length, Print_case, Print_gensym, Print_array);
    len = FIX(ISSIZE(temp));
    END_LOCAL_ALLOCATION(prev_area, prev_pos);
    return VALUES_1(len);
}
