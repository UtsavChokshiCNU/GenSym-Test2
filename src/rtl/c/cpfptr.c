/*
 * cpfptr.c -  Chestnut Run-Time Library entry for function copy_foreign_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kalignment;
extern Object Kmalloc;
extern Object Kstatic;
extern Object Ktype;

#if SI_USE_PROTOTYPES

extern Object SI_keyword_arg_p(Object key, Object *args, long n);
extern Object make_foreign_pointer(int,...);
extern Object malloc_foreign_pointer(int,...);

#else

extern Object SI_keyword_arg_p();
extern Object make_foreign_pointer();
extern Object malloc_foreign_pointer();

#endif



Object copy_foreign_pointer varargs_1(int, n)
{
    Object foreign_pointer = UNBOUND;
    Object static_p, malloc_p, malloc = UNBOUND, alignment_p;
    Object alignment = UNBOUND, type, new = UNBOUND;
    Declare_varargs;
    Declare_stack_pointer;

    SAVE_STACK();
    INIT_ARGS();
    foreign_pointer = REQUIRED_ARG();
    SAVE_ARGS();
    static_p = KEYWORD_ARG_P(Kstatic);
    malloc_p = KEYWORD_ARG_P(Kmalloc);
    malloc = malloc_p ? KEYWORD_ARG(malloc_p) : Nil;
    alignment_p = KEYWORD_ARG_P(Kalignment);
    alignment = alignment_p ? KEYWORD_ARG(alignment_p) : FIX(1);
    PROTECT_4(foreign_pointer,malloc,alignment,new);
    type = FOREIGN_POINTER_TYPE(foreign_pointer);
    new = (malloc ? 
	   malloc_foreign_pointer(8,Ktype,type,Kalignment,alignment) :
	   make_foreign_pointer(8,Ktype,type,Kalignment,alignment));
    MEMCPY((char *)FOREIGN_POINTER_ADDRESS(new),
	   (char *)FOREIGN_POINTER_ADDRESS(foreign_pointer),
	   FOREIGN_TYPE_SIZE(type));
    RESTORE_STACK();
    return VALUES_1(new);
}
