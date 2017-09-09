/* lspfxs.c
 * Input file:  lisp-fixes.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lspfxs.h"


void lisp_fixes_INIT()
{
    x_note_fn_call(6,0);
    SET_PACKAGE("AB");
}
