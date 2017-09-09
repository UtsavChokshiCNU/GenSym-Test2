/*
 * chars-aux.c - various character-handling helper data and functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"
#include "chars.h"

struct char_name 
  SI_Char_names[] = {

    /* Standard */
    {' ', "Space", NIL},
    {'\n', "Newline", NIL},

    /* Semi-standard */
    {'\b', "Backspace", NIL},
    {'\t', "Tab", NIL},
    {'\12', "Linefeed", NIL},	/* ASCII assumed */
    {'\f', "Page", NIL},
    {'\r', "Return", NIL},
    {'\177', "Rubout", NIL},

    /* Nonstandard (Lucid) */
    {'\0', "Null", NIL},
    {7, "Bell", NIL},

    /* Nonstandard (Lucid / ASCII) */
    {0, "NUL", NIL},
    {1, "SOH", NIL},
    {2, "STX", NIL},
    {3, "ETX", NIL},
    {4, "EOT", NIL},
    {5, "ENQ", NIL},
    {6, "ACK", NIL},
    {7, "BEL", NIL},
    {8, "BS", NIL},
    {9, "TAB", NIL},
    {10, "LF", NIL},
    {11, "VT", NIL},
    {12, "FF", NIL},
    {13, "CR", NIL},
    {14, "SO", NIL},
    {15, "SI", NIL},
    {16, "DLE", NIL},
    {17, "DC1", NIL},
    {18, "DC2", NIL},
    {19, "DC3", NIL},
    {20, "DC4", NIL},
    {21, "NAK", NIL},
    {22, "SYN", NIL},
    {23, "ETB", NIL},
    {24, "CAN", NIL},
    {25, "EM", NIL},
    {26, "SUB", NIL},
    {27, "ESC", NIL},
    {28, "FS", NIL},
    {29, "GS", NIL},
    {30, "RS", NIL},
    {31, "US", NIL},

    /* Nonstandard (Chestnut) */
    {'\n', "Enter", NIL},
    {143, "Backtab", NIL},

    /* end of list */
    {0, NULL, NIL}
};


Object iname_char(iname)
    char *iname;
{
    register long i;
    long code;

    for (i = 0; SI_Char_names[i].iname != NULL; i++)
	if (!strcmp(iname, SI_Char_names[i].iname))
	    return CHR(SI_Char_names[i].code);

    /* Mimic Lucid */
    if ((iname[0] == 'c' || iname[0] == 'C') &&
	isxdigit(iname[1]) &&
	isxdigit(iname[2]) &&
	iname[3] == '\0') {
	sscanf(&iname[1], "%X", &code);
	return CHR(code);
    }

    return NIL;
}

