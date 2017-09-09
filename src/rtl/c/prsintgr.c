/*
 * prsintgr.c -  Chestnut Run-Time Library entry for function parse_integer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object digit_char_p(Object,Object);
extern long ilength(Object sequence);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object digit_char_p();
extern long ilength();

#endif


/* autor:  JAR 12-14-90 */

#define issign(c)		(((c) == '+') || ((c) == '-'))
#define isdigitchar(c, iradix)   (digit_char_p(CHR(c), FIX(iradix)))


/* &keyword 1 0 */
Object parse_integer (string, start, end, radix, junk_allowed)
    Object string, start, end, radix, junk_allowed;
{
    long istart =  UNSUPPLIED_P(start) ? 0 :IFIX(start);
    long iend   =  UNSUPPLIED_P(end)   ? ilength(string) : IFIX(end);
    long iradix =   UNSUPPLIED_P(radix) ? 10 : IFIX(radix);
    Object result;
    long i = istart;
    char c;
    char *istring = ISTRING(string);
    extern Object read_integer();

    /* Locate true beginning and end of the integer */
    /* Compare this with parse_number */

 STATE1:        /* start */
    if (i >= iend)
	goto REJECTSTATE;
    c = istring[i++];
    if (issign(c))
	goto STATE2;
    if (isdigitchar(c, iradix))
	goto STATE3;
    if (isspace(c))
	goto STATE1;
    goto REJECTSTATE;

 STATE2:	/* sign */
    if (i >= iend)
	goto REJECTSTATE;
    c = istring[i++];
    if (isdigitchar(c, iradix))
	goto STATE3;
    goto REJECTSTATE;

 STATE3:	/* [sign] digit+ */
    if (i >= iend)
	goto ACCEPTSTATE;
    c = istring[i++];
    if (isdigitchar(c, iradix))
	goto STATE3;
    --i;

 ACCEPTSTATE:
    result = read_integer(&istring[istart], i, iradix);
    return VALUES_2(result, FIX(i));

    /*
     * We fail to signal an error in the case where junk is not supposed
     * to be allowed and some junk (non-whitespace) follows the number.
     * This shouldn't affect working programs (until the condition system
     * is implemented).
     */

 REJECTSTATE:
    if (junk_allowed != NIL && SUPPLIED_P(junk_allowed))
	return VALUES_2(NIL, FIX(i));
    else {
	error(2, "PARSE-INTEGER:  Invalid string ~S", string);
        return VALUES_1(NIL); /* NOT REACHED */
}
}
