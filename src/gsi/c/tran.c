/* tran.c
 * Input file:  translate.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "tran.h"


Object G2int_modules_to_translate_verbosely = UNBOUND;

Object G2int_dummy_place_for_chestnut_internals = UNBOUND;

Object G2int_the_standard_mnemonics = UNBOUND;

void translate_INIT()
{
    x_note_fn_call(50,0);
    SET_PACKAGE("AB");
    if (G2int_modules_to_translate_verbosely == UNBOUND)
	G2int_modules_to_translate_verbosely = Qnil;
    if (G2int_dummy_place_for_chestnut_internals == UNBOUND)
	G2int_dummy_place_for_chestnut_internals = Nil;
    G2int_the_standard_mnemonics = Nil;
}
