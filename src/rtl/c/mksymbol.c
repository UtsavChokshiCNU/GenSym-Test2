/*
 * mksymbol.c -  Chestnut Run-Time Library entry for function make_symbol
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qstring;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern void SI_type_error(Object datum, Object expected_type);

#else

extern Object SI_alloc();
extern void SI_type_error();

#endif




Object make_symbol (name)
    Object name;
{
    Declare_local_temp;
    Object sym;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(name);
    if (!STRINGP(name)) { SI_type_error(name, Qstring); /*NOTREACHED*/ }

    sym = SI_ALLOC(SI_Uninterned_symbol,USYMBOL_TYPE,SI_SYMBOL_TAG,SI_NORMAL);
    USYMBOL_NAME(sym) = name;
    USYMBOL_PLIST(sym) = NIL;
    RESTORE_STACK();
    return VALUES_1(sym);
}
