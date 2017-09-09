/*
 * smkscrr.c -  Chestnut Run-Time Library entry for function SI_make_static_array
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object cons();
extern Object make_array();

#endif




/*VARARGS*/
Object SI_make_static_array (type, n, ap)
    Object type;
    long n;
    va_list ap;
{
    Object dimensions = NIL, tail, item, result;
    Declare_area(a);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(type, dimensions, tail);

    if (n == 1) dimensions = va_arg(ap, Object);
    else if (n > 1) {
	item = va_arg(ap, Object);
	dimensions = cons(item, NIL);
	tail = dimensions;
	while (n--) {
	    item = va_arg(ap, Object);
	    item = cons(item, NIL);
	    SET_CDR(tail, item);
	    tail = item;
	}
    }	
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = make_array(dimensions,type,KOPT,KOPT,KOPT,KOPT,KOPT,KOPT);
    RESTORE_CURRENT_AREA(a);
    RESTORE_STACK();
    return result;
}
