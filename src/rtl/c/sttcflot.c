/*
 * sttcflot.c -  Chestnut Run-Time Library entry for function STATIC_FLOAT
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

extern Object cdouble_to_double(double a);

#else

extern Object cdouble_to_double();

#endif




Object STATIC_FLOAT (d)
    DOUBLE d;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = cdouble_to_double(d);
    RESTORE_CURRENT_AREA(a);
    return result;
}
