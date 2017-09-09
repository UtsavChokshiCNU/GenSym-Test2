/*
 * writlin.c -  Chestnut Run-Time Library entry for function write_line
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

extern Object lwrite(Object object, Object stream, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);
extern void restore_frontier(SI_Segment *seg, void *frontier);
extern Object subseq(Object,Object,Object);
extern Object terpri(Object);

#else

extern Object lwrite();
extern void restore_frontier();
extern Object subseq();
extern Object terpri();

#endif




/* &optional 1 1 2  &key */
Object write_line (string, output_stream, start, end)
    Object string, output_stream, start, end;
{
    Declare_local_temp;
    DECLARE_AREA(prev_area); DECLARE_FRONTIER(prev_pos);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(string,output_stream);
    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
    lwrite(subseq(string, start, end), output_stream,
	NIL, Print_radix, Print_base, Print_circle, Print_pretty,
	Print_level, Print_length, Print_case, Print_gensym, Print_array);
    terpri(output_stream);
    END_LOCAL_ALLOCATION(prev_area, prev_pos);
    RESTORE_STACK();
    return VALUES_1(string);
}
