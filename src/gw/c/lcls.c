/* lcls.c
 * Input file:  locales.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lcls.h"


/* GET-CODE-PAGE-INFORMATION-IF-AVAILABLE */
Object g2000_get_code_page_information()
{
    x_note_fn_call(28,0);
    return VALUES_1(Nil);
}

void locales_INIT()
{
    x_note_fn_call(28,1);
    SET_PACKAGE("AB");
}
