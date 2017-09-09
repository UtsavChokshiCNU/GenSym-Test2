/*
 * sttcpckg.c -  Chestnut Run-Time Library entry for function STATIC_PACKAGE
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

extern Object ifind_package(char *name);
extern Object istring_to_string(char *istring);
extern Object make_package(Object pkg_name, Object nicknames, Object use);

#else

extern Object ifind_package();
extern Object istring_to_string();
extern Object make_package();

#endif




Object STATIC_PACKAGE (name)
    char *name;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = ifind_package(name);
    if (result == NIL)
	result = make_package(istring_to_string(name), NIL, NIL);
    RESTORE_CURRENT_AREA(a);
    return result;
}
