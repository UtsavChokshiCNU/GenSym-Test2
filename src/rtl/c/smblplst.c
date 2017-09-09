/*
 * smblplst.c -  Chestnut Run-Time Library entry for function symbol_plist
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);

#else

extern Object SI_symbol_field();

#endif




Object symbol_plist (sym)
    Object sym;
{
    Declare_local_temp;
    return VALUES_1(SYMBOL_PLIST(sym));
}
