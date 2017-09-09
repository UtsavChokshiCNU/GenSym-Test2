/*
 * m_nthcdr.c -  Chestnut Run-Time Library entry for function m_nthcdr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

/* extension - does not check for NIL */
Object m_nthcdr(n, list)
    long	n;
    Object	list;
{
    Declare_local_temp;
    while(n--) {
	list = M_CDR(list);
    }
    return list;
}
