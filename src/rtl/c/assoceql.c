/*
 * assoceql.c -  Chestnut Run-Time Library entry for function assoc_eql
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

Object assoc_eql(key, alist)
    Object key, alist;
{
    Declare_local_temp;
    Object elem, elemkey;
    char not_simple_p;

    /* from NUMBERP */
    not_simple_p = !IMMEDIATE_P(key) &&
      SI_ENUM_LE(SI_STORED_OBJECT_TYPE(key), COMPLEX_TYPE);

    for ( ; CONSP(alist); alist = M_CDR(alist)) {
      elem = M_CAR(alist);
      if (!ENDP(elem)) {
	elemkey = M_CAR(elem);
	if (EQ(elemkey, key) ||
	    (not_simple_p && eql(elemkey, key)))
	  return VALUES_1(elem);
      }
    }
    return VALUES_1(NIL);
}
