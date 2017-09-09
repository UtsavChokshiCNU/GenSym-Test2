/*
 * cdbltdbl.c -  Chestnut Run-Time Library entry for function cdouble_to_double
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
extern SI_Area Local_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);

#else

extern Object SI_alloc();

#endif




/* This should be renamed to double_to_double_float() */

Object cdouble_to_double (a)	/* Cf. DOUBLE_TO_DOUBLE_FLOAT */
    double a;
{
    Object result;
    Declare_area(area);
#ifdef KLUDGE_DOUBLE_FLOATS
    Double_float_kludge_union u;
    u.number = a;
#endif
    SAVE_CURRENT_AREA(area);
    SET_CURRENT_AREA(Local_area);
#ifdef KLUDGE_DOUBLE_FLOATS
    result = SI_ALLOC(SI_Kludged_double_float, DOUBLE_TYPE, SI_NUMBER_TAG, SI_BORING);
#else
    result = SI_ALLOC(SI_Double_float, DOUBLE_TYPE, SI_NUMBER_TAG, SI_BORING);
#endif
    RESTORE_CURRENT_AREA(area);
    SI_UNTAG_DOUBLE_FLOAT(result) =
#ifdef KLUDGE_DOUBLE_FLOATS
	u.kludge;
#else
	a;
#endif
    return result;
}
