/*
 * ismblnm.c -  Chestnut Run-Time Library entry for function ismblnm
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern char *Initial_symbol_names[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();

#endif



/* entry name: ismblnm() {} */
char *isymbol_name (sym)
    Object sym;
{
    Object name;

    if (sym == NIL)
	return "NIL";
    switch (ISYMBOL_TYPE(sym)) {
    case USYMBOL_TYPE:
	name = USYMBOL_NAME(sym);
	return ISTRING(name);
    case MSYMBOL_TYPE:
    case EMSYMBOL_TYPE:
    case MKEYWORD_TYPE:
	return MSYMBOL_NAME(sym);
    case SYMBOL_TYPE:
    case ESYMBOL_TYPE:
    case KEYWORD_TYPE:
	return ISYMBOL_NAME(sym);
    default:
	(void)error(2, "symbol_name: not a symbol - ~S", sym);
	/*NOTREACHED*/
    }
	return NULL; //this function return somthing
}
