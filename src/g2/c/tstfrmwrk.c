/* tstfrmwrk.c
 * Input file:  test-framework.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "tstfrmwrk.h"


Object Evaluation_false_value = UNBOUND;

/* G2-ARE-LISP-UNIT-TESTS-INCLUDED-P */
Object g2_are_lisp_unit_tests_included_p()
{
    x_note_fn_call(34,0);
    return VALUES_1(Evaluation_false_value);
}

void test_framework_INIT()
{
    Object gensymed_symbol;
    Object Qg2_are_lisp_unit_tests_included_p;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;

    x_note_fn_call(34,1);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_are_lisp_unit_tests_included_p = 
	    STATIC_SYMBOL("G2-ARE-LISP-UNIT-TESTS-INCLUDED-P",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_are_lisp_unit_tests_included_p,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_are_lisp_unit_tests_included_p,
	    STATIC_FUNCTION(g2_are_lisp_unit_tests_included_p,NIL,FALSE,0,0));
}
