/*
 * mmbrql.c -  Chestnut Run-Time Library entry for function member_eql
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object eql(Object,Object);

#else

extern Object eql();

#endif


#include "lists.h"

Object member_eql(item, list)
    Object item, list;
{
    Declare_local_temp;
    Object entry;
    char not_simple_p;

    /* from NUMBERP */
    not_simple_p = !IMMEDIATE_P(item) &&
      SI_ENUM_LE(SI_STORED_OBJECT_TYPE(item), COMPLEX_TYPE);

    while (!ENDP(list)) {
	entry = M_CAR(list);
	if (EQ(item, entry) ||
	    (not_simple_p && eql(item, entry)))
	    return VALUES_1(list);
	else
	    list = M_CDR(list);
    }
    return VALUES_1(NIL);
}
