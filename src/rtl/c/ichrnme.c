/*
 * ichrnme.c -  Chestnut Run-Time Library entry for function ichar_name
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#include "chars.h"

/* Store character's name, if any, into buffer; return index in SI_Char_names
   table, or -1 */

long ichar_name(c, buffer)
    Object c;
    char *buffer;
{
    long code;
    register long i;

    if (ICHAR_BITS(c) != 0)
	return -1L;
    code = ICHAR_CODE(c);
    for (i = 0; SI_Char_names[i].iname != NULL; ++i)
	if (code == SI_Char_names[i].code) {
	    strcpy(buffer, SI_Char_names[i].iname);
	    return i;
	}
    if (isprint(code))
	return -1L;
    sprintf(buffer, "c%2X", code); /* Mimic Lucid */
    return i;
}
