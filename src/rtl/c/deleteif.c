/*
 * deleteif.c -  Chestnut Run-Time Library entry for function delete_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_delete_if(Object pred, Object seq, Object from_end, Object lstart, Object lend, Object lcount, Object key, Object not_p);

#else

extern Object SI_delete_if();

#endif


#include "seqmodi.h"

Object delete_if (test, seq, from_end, start, end, count, key)
    Object test, seq, from_end, start, end, count, key;
{
    return SI_delete_if(test, seq, from_end, start, end, count, key, NIL);
}
