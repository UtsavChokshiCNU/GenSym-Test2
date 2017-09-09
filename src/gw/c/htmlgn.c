/* htmlgn.c
 * Input file:  htmlgen.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "htmlgn.h"


Object G2int_current_html_insert_mark = UNBOUND;

void htmlgen_INIT()
{
    x_note_fn_call(56,0);
    SET_PACKAGE("AB");
}
