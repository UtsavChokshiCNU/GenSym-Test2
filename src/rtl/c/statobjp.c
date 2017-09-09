/*
 * statobjp.c -  Chestnut Run-Time Library entry for function stationary_object_p
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

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif


#include "gc.h"

Object stationary_object_p(object)
    Object object;
{
    SI_Area  ar;
    SI_Segment *seg;
    SI_Ulong addr = (SI_Ulong)SI_UNTAG_STORED(object, char);

    ar = Dynamic_area;
    if (SI_IMMEDIATEP(object))
	return VALUES_1(T);
    for (seg = ar.first_segment; seg != NULL; seg = seg->next)
	if (addr >= (SI_Ulong)(seg->start) &&
	    addr <  (SI_Ulong)(seg->limit))
	    return VALUES_1(NIL);
#if SI_COPYING_COLLECTOR
    ar = Dynamic_area_copy;
    for (seg = ar.first_segment; seg != NULL; seg = seg->next)
	if (addr >= (SI_Ulong)(seg)->start && 
	    addr <  (SI_Ulong)(seg->limit))
	  return VALUES_1(NIL);
#endif

  return VALUES_1(T);
}
