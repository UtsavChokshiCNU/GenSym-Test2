/*
 * schrrlpn.c -  Chestnut Run-Time Library entry for function SI_char_relopn
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "chars.h"

/* Object SI_char_relopn() {} */

Object SI_char_relopn(f, n, ap)
    Object (*f)();
    long n;
    va_list ap;
{
    Declare_local_temp;
    Object n1, n2, result = T;

    if (n > 0) {
	n1 = va_arg(ap,Object);
	while (--n) {
	    n2 = va_arg(ap, Object);
	    if (!(*f)(n1,n2)) {
		result = NIL;
		break;
	    }
	    n1 = n2;
        }
    }
    return VALUES_1(result);
}
