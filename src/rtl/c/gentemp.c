/*
 * gentemp.c -  Chestnut Run-Time Library entry for function gentemp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object ifind_symbol(char *name, Object pkg);
extern Object iintern(char *name, Object pkg);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object ifind_symbol();
extern Object iintern();

#endif


#define MAXGENTEMP 40

/* &optional 0 2 */
/*ARGSUSED*/
Object gentemp (prefix, package)
    Object prefix;
    Object package;  /* ignored */
{
    char gentemp_name[MAXGENTEMP+11];  /* room for counter */
    long gentemp_prefix_len;
    static long gentemp_counter = 1L;

    if (STRINGP(prefix)) {
	(void)strncpy(gentemp_name, ISTRING(prefix), MAXGENTEMP);
	gentemp_name[MAXGENTEMP] = '\0';
	gentemp_prefix_len = (long)strlen(gentemp_name);
    }
    else {
	(void)strcpy(gentemp_name, "T");
	gentemp_prefix_len = 1;
    }

    while(TRUE) {
	(void)sprintf(&gentemp_name[gentemp_prefix_len], "%ld", gentemp_counter);
	gentemp_counter++;
	if (!TRUEP(ifind_symbol(gentemp_name,KOPT)))
	    return iintern(gentemp_name,KOPT);
	if (gentemp_counter < 0)
	    error(1, "Out of gentemp symbols");
    }
}    
