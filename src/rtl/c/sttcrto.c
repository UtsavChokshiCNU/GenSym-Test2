/*
 * sttcrto.c -  Chestnut Run-Time Library entry for function STATIC_RATIO
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
extern Object xmake_canonical_rational();

Object  STATIC_RATIO (numerator, denominator)
    Object numerator;
    Object denominator;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = xmake_canonical_rational(numerator, denominator);
    RESTORE_CURRENT_AREA(a);
    return result;
}
