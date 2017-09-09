/*
 * gtprprts.c -  Chestnut Run-Time Library entry for function get_properties
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object member(Object item, Object list, Object test, Object test_not, Object key);

#else

extern Object member();

#endif




Object get_properties (place, indicator_list)
    Object place, indicator_list;
{
    while (TRUEP(place)) {
	if (TRUEP(member(M_CAR(place), indicator_list, KOPT, KOPT, KOPT))) {
	    return VALUES_3(M_CAR(place), M_CADR(place), place);
	}
 	place = M_CDDR(place);
    }
    return VALUES_3(NIL,NIL,NIL);
}
