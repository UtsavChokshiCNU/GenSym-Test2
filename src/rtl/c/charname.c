/*
 * charname.c -  Chestnut Run-Time Library entry for function char_name
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

extern Object imake_duplicate_string(char *oldstring);

#else

extern Object imake_duplicate_string();

#endif


#include "chars.h"
/* Find a name for a character, e.g. #\newline => "Newline" */

Object char_name(c)
    Object c;
{
    Declare_local_temp;
    char buffer[8];
    Object result = NIL;
    long code, i;

    if (ICHAR_BITS(c) != 0)
	return VALUES_1(NIL);
    code = ICHAR_CODE(c);
    for (i = 0; SI_Char_names[i].iname != NULL; ++i)
	if (code == SI_Char_names[i].code) {
	    DECLARE_AREA(a);
	    SAVE_CURRENT_AREA(a);
	    SET_CURRENT_AREA(Static_area);
	    result = SI_Char_names[i].name =
		imake_duplicate_string(SI_Char_names[i].iname);
	    RESTORE_CURRENT_AREA(a);
	    return VALUES_1(result);
	}
    if (isprint(code))
	return VALUES_1(NIL);
    sprintf(buffer, "c%2X", code); /* Mimic Lucid */
    return VALUES_1(imake_duplicate_string(buffer));
}
