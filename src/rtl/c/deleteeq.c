/*
 * deleteeq.c -  Chestnut Run-Time Library entry for function delete_eq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_fp_eq_1;

#if SI_USE_PROTOTYPES

extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object eq(Object,Object);
extern Object ldelete(Object item, Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object lcount, Object key);

#else

extern Object STATIC_FUNCTION1();
extern Object eq();
extern Object ldelete();

#endif


#include "seqmodi.h"
#include "del-eq.h"

/* entry delete_eq (){} */

DEFINE_LIST_DELETE(delete_eq, EQ, FP_EQ)

