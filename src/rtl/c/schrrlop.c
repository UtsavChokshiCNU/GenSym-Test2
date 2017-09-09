/*
 * schrrlop.c -  Chestnut Run-Time Library entry for function SI_char_relop
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "chars.h"

/* Object SI_char_relop() {} */

Object SI_char_relop(f, a, b)
    Object (*f)();
    Object a, b;
{
    Declare_local_temp;
    Object temp, n1, n2;

    for (n1 = a, temp = b; temp; temp = M_CDR(temp)) {
	n2 = M_CAR(temp);
	if (!(*f)(n1,n2))
	    return VALUES_1(NIL);
	n1 = n2;
    }
    return VALUES_1(T);
}
