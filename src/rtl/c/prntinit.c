/*
 * prntinit.c - global variables, initializer and helper routines
 *              for the Printer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern Object Kupcase;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);

#else

extern void SI_add_external_root();

#endif



/* Common lisp globals */
DEFINE_VARIABLE(Print_array);
DEFINE_VARIABLE(Print_base);
DEFINE_VARIABLE(Print_case);
DEFINE_VARIABLE(Print_circle);
DEFINE_VARIABLE(Print_escape);
DEFINE_VARIABLE(Print_gensym);
DEFINE_VARIABLE(Print_length);
DEFINE_VARIABLE(Print_level);
DEFINE_VARIABLE(Print_lines);
DEFINE_VARIABLE(Print_miser_width);
DEFINE_VARIABLE(Print_pprint_dispatch);
DEFINE_VARIABLE(Print_pretty);
DEFINE_VARIABLE(Print_radix);
DEFINE_VARIABLE(Print_readably);
DEFINE_VARIABLE(Print_right_margin);

DEFINE_VARIABLE(SI_Format_stream);

/*ARGSUSED*/
long SI_requires_escaping_short(iname, len)
    char *iname;
    int len;
{   /* quietly support escaping when reader is not initialized */
    return TRUE;
}

/* see SI_requires_escaping_full in lreader.c */
long (*SI_requires_escaping_fptr)() =  SI_requires_escaping_short;

void SI_INIT_print()
{

    PROTECT_GLOBAL(SI_Format_stream);
    /* Current_print_level is always a fixnum, so don't bother protecting. */

    PROTECT_GLOBAL(Print_array);

    Print_array = NIL;
    
    PROTECT_GLOBAL(Print_base);

    Print_base = FIX(10L);
    
    PROTECT_GLOBAL(Print_case);

    Print_case = Kupcase;
     
    PROTECT_GLOBAL(Print_circle);

    Print_circle = NIL;
    
    PROTECT_GLOBAL(Print_escape);

    Print_escape = T;
    
    PROTECT_GLOBAL(Print_gensym);

    Print_gensym = T;
    
    PROTECT_GLOBAL(Print_length);

    Print_length = NIL;
    
    PROTECT_GLOBAL(Print_level);

    Print_level = FIX(15);
    
    PROTECT_GLOBAL(Print_lines);

    Print_lines = NIL;
    
    PROTECT_GLOBAL(Print_miser_width);

    Print_miser_width = NIL;
    
    PROTECT_GLOBAL(Print_pprint_dispatch);

    Print_pprint_dispatch = NIL;
    
    PROTECT_GLOBAL(Print_pretty);

    Print_pretty = NIL;
    
    PROTECT_GLOBAL(Print_radix);

    Print_radix = NIL;
    
    PROTECT_GLOBAL(Print_readably);

    Print_readably = NIL;
    
    PROTECT_GLOBAL(Print_right_margin);

    Print_right_margin = NIL;

}

