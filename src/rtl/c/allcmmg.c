/*
 * allcmmg.c -  Chestnut Run-Time Library entry for function allocate_memory_to_target
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern SI_Area Dynamic_area_copy;
extern SI_Area Dynamic_area;

#if SI_USE_PROTOTYPES

extern SI_Area *SI_area_name_to_area(Object area_name);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern SI_Long integer_to_long(Object n);
extern SI_Ulong integer_to_unsigned_long(Object n);

#else

extern SI_Area *SI_area_name_to_area();
extern Object (*SI_warn_fptr) ();
extern SI_Long integer_to_long();
extern SI_Ulong integer_to_unsigned_long();

#endif

Object allocate_memory_to_target(area_name, target)
    Object area_name, target;
{

    Object temp1;
    extern int alloc_memory_to_target();
    SI_Area *area = SI_area_name_to_area(area_name);

    if (area == NULL)
	return warn(2, "allocate_memory_to_target: unrecognized area - ~S",
		    area_name);

    if (TRUEP(target)) {
        if (INTEGERP(target))
	  area->target_size = INTEGER_TO_UNSIGNED_LONG(target);
	else if (FLOATP(target))
	  area->target_size = (SI_Ulong)DOUBLE_FLOAT_TO_DOUBLE(target);
#if SI_COPYING_COLLECTOR
	if (area == &Dynamic_area)
	    Dynamic_area_copy.target_size = Dynamic_area.target_size;
#endif /* SI_COPYING_COLLECTOR */
    }

    temp1 = alloc_memory_to_target(area) ? T : NIL;
    return temp1;
}
