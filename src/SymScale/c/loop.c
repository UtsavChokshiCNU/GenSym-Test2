/* loop.c
 * Input file:  loop.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "loop.h"


void loop_INIT()
{
    x_note_fn_call(6,0);
    SET_PACKAGE("AB");
}
