/* intrp.c
 * Input file:  interop.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "intrp.h"


/* C-LOAD-DYNAMIC-LIBRARY */
Object c_load_dynamic_library(file_name)
    Object file_name;
{
    Object temp;

    x_note_fn_call(237,0);
    temp = 
	    FIX(g2ext_load_dynamic_library(UBYTE_16_SARRAY_TO_USHORT_PTR(file_name)));
    return VALUES_1(temp);
}

/* G2-LOAD-DYNAMIC-LIBRARY */
Object g2_load_dynamic_library(file_name_as_evaluation_value)
    Object file_name_as_evaluation_value;
{
    Object file_name, value_1, temp;

    x_note_fn_call(237,1);
    file_name = file_name_as_evaluation_value;
    value_1 = Nil;
    temp = c_load_dynamic_library(file_name);
    value_1 = temp;
    reclaim_text_string(file_name_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

void interop_INIT()
{
    Object gensymed_symbol;
    Object Qg2_load_dynamic_library;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;

    x_note_fn_call(237,2);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_load_dynamic_library = STATIC_SYMBOL("G2-LOAD-DYNAMIC-LIBRARY",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_load_dynamic_library,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_load_dynamic_library,
	    STATIC_FUNCTION(g2_load_dynamic_library,NIL,FALSE,1,1));
}
