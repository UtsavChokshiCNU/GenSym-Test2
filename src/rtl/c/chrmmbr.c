/*
 * chrmmbr.c -  Chestnut Run-Time Library entry for function char_member
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_string_base(Object o);
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object make_string(Object size, Object initial_element);
extern Object string(Object);
extern Object string_trim(Object char_bag, Object str);
extern Object string_left_trim(Object char_bag, Object str);
extern Object string_right_trim(Object char_bag, Object str);

#else

extern char *SI_string_base();
extern Object elt();
extern long ilength();
extern Object make_string();
extern Object string();
extern Object string_trim();
extern Object string_left_trim();
extern Object string_right_trim();
#endif



/* The implementation of the trim functions could be improved significantly.
 * Here is an outline of an alternative implementation for someone to do
 * someday.
 *
 * 1. Initialize an array of bits to all zero.  The number of bits needed is
 * UCHAR_MAX (the maximum number of possible character codes).
 *
 * 2. Map over the bag, turning on the bit in the bit-array for each character
 * in the bag.
 *
 * 3. Use this bit array in the scanning predicate for the trim functions in
 * the obvious way.
 */

static long char_member (c, char_bag)
    char c;
    Object char_bag;
{
    long i, len;

    len = ilength(char_bag);

    for (i = 0; i < len; ++i) {
	if (c == ICHAR_CODE(elt(char_bag, FIX(i))))
	    return(TRUE);
    }
    return(FALSE);
}


Object string_trim (char_bag, str)  /* char bag immed? can be a list, too */
    Object char_bag;
    Object str;
{
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(char_bag, str);
    str = string_right_trim(char_bag, str);
    str = string_left_trim(char_bag, str); /* nstring_left_trim ? */
    RESTORE_STACK();
    return(str);
}

Object string_left_trim (char_bag, ostr)
    Object char_bag, ostr;
{
    Declare_local_temp;
    long i, len;
    char *str;
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(char_bag,ostr);
    PROTECTI_1(result);

    ostr = STRING(ostr);	/* conses if ostr is a character */
    len = ilength(ostr);
    str = SI_string_base(ostr);

    for (i = 0; i < len && char_member(str[i], char_bag); i++)
	;
    result = make_string(FIX(len - i), KOPT);

    /* Don't use str here - the garbage collector relocates strings */
    (void)strncpy(&SI_ISCHAR(result, 0), SI_string_base(ostr) + i, len-i);
    RESTORE_STACK();
    return VALUES_1(result);
}

Object string_right_trim (char_bag, ostr)
    Object char_bag, ostr;
{
    Declare_local_temp;
    long i, len;
    char *str;
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(char_bag,ostr);
    PROTECTI_1(result);

    ostr = STRING(ostr);
    len = ilength(ostr);
    str = SI_string_base(ostr);

    for (i = len; i > 0 && char_member(str[i-1], char_bag); i--)
	;
    result = make_string(FIX(i), KOPT);

    /* Don't use str here - the garbage collector relocates strings */
    (void)strncpy(&SI_ISCHAR(result, 0), SI_string_base(ostr), i);
    RESTORE_STACK();
    return VALUES_1(result);
}

