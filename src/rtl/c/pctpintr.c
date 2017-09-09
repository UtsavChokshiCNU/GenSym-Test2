/*
 * pctpintr.c -  Chestnut Run-Time Library entry for function PCTpointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object clong_to_bignum(SI_Long a);

#else

extern Object clong_to_bignum();

#endif




/*  %pointer  */

Object PCTpointer (object)
    Object object;
{
    Declare_local_temp;
    Object newnode;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(object);
    newnode = MAKE_INTEGER((SI_Long) object);
    RESTORE_STACK();
    return VALUES_1(newnode);
}
