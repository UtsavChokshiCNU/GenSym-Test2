/*
 * sttcsmbl.c -  Chestnut Run-Time Library entry for function STATIC_SYMBOL
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object iintern(char *name, Object pkg);
extern Object istring_to_string(char *istring);
extern Object make_symbol(Object);

#else

extern Object iintern();
extern Object istring_to_string();
extern Object make_symbol();

#endif





Object STATIC_SYMBOL (name, pkg)
    char *name;
    Object pkg;
{
    Object res;
    Declare_area(a);

    if (pkg == NIL) {
	SAVE_CURRENT_AREA(a);
	SET_CURRENT_AREA(Static_area);
	res = make_symbol(istring_to_string(name));
        RESTORE_CURRENT_AREA(a);
    }
    else
	res =  iintern(name, pkg); /* always allocates static symbols */

    return res;
}
