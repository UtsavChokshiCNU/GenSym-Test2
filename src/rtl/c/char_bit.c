/*
 * char_bit.c -  Chestnut Run-Time Library entry for function char_bit
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif


#include "chars.h"

FORWARD_STATIC int bitname_to_bit();

Object char_bit(c, bitname)
    Object c, bitname;
{
    Declare_local_temp;
    return VALUES_1(ICHAR_BITS(c) & bitname_to_bit(bitname) ? T : NIL);
}

Object setf_char_bit(c, bitname, newvalue)
    Object c, bitname, newvalue;
{
    Declare_local_temp;
    long bits = ICHAR_BITS(c);
    long code = ICHAR_CODE(c);
    long bit = bitname_to_bit(bitname);

    if (newvalue)
	bits |= bit;
    else
	bits &= ~bit;
    return VALUES_1(MAKE_CHR(code, bits));
}
static int bitname_to_bit(bitname)
    Object bitname;
{
/****  or remove or add keywords in symbols.lisp
    if (EQ(bitname, Kcontrol))
	return ICHAR_CONTROL_BIT;
    else if (EQ(bitname, Kmeta))
	return ICHAR_META_BIT;
    else if (EQ(bitname, Ksuper))
	return ICHAR_SUPER_BIT;
    else if (EQ(bitname, Khyper))
	return ICHAR_HYPER_BIT;
    else
    */
    {
	(void)error(2, "char_bit: unrecognized bit - ~S", bitname);
	/*NOTREACHED*/
    }
}

Object set_char_bit(c, name, newvalue)
    Object c, name, newvalue;
{
    /* ? */
    return setf_char_bit(c, name, newvalue);
}

