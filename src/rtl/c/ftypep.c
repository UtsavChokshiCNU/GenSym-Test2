/*
 * ftypep.c -  Chestnut Run-Time Library entry for function foreign_typep
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qforeign_type;

#if SI_USE_PROTOTYPES

extern Object get_foreign_type(Object,Object);

#else

extern Object get_foreign_type();

#endif



Object foreign_typep(foreign_pointer,foreign_type)
    Object foreign_pointer, foreign_type;
{
    Object fptype;
    Declare_stack_pointer;

    fptype = FOREIGN_POINTER_TYPE(foreign_pointer);
    SAVE_STACK();
    PROTECT_1(fptype);
    foreign_type = FOREIGN_TYPE(foreign_type);
    RESTORE_STACK();
    return VALUES_1(EQ(fptype,foreign_type) ? T : Nil);
}
