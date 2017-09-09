/*
 * cpysymbl.c -  Chestnut Run-Time Library entry for function copy_symbol
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object copy_list(Object);
extern Object make_symbol(Object);
extern Object symbol_name(Object);

#else

extern Object SI_symbol_field();
extern Object copy_list();
extern Object make_symbol();
extern Object symbol_name();

#endif




/* &optional 1 1 */
Object copy_symbol (sym, copy_props)
    Object sym, copy_props;
{
    Declare_local_temp;
    Object newsym;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECTI_1(newsym);
    newsym = make_symbol(symbol_name(sym));
    if (SUPPLIED_P(copy_props) && TRUEP(copy_props)) {
    	copy_props = copy_list(SYMBOL_PLIST(sym));
	USYMBOL_PLIST(newsym) = copy_props;
    }
    RESTORE_STACK();
    return VALUES_1(newsym);
}
