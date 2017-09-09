/*
 * mkfptri.c -  Chestnut Run-Time Library entry for function make_foreign_pointer_internal
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);

#else

extern Object SI_alloc();

#endif



Object make_foreign_pointer_internal(address,type)
     unsigned long address;
     Object type;
{
    Object new_foreign_pointer;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(type);
    MAKE_FOREIGN_POINTER(new_foreign_pointer,address,type);
    RESTORE_STACK();
    return new_foreign_pointer;
}
