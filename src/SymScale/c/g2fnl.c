/* g2fnl.c
 * Input file:  g2-final.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2fnl.h"


DEFINE_VARIABLE_WITH_SYMBOL(Ensure_expanded_instruction_macros_has_run_p, Qensure_expanded_instruction_macros_has_run_p);

/* ENSURE-EXPANDED-INSTRUCTION-MACROS */
Object ensure_expanded_instruction_macros()
{
    x_note_fn_call(254,0);
    if ( !TRUEP(Ensure_expanded_instruction_macros_has_run_p)) {
	Ensure_expanded_instruction_macros_has_run_p = T;
	return VALUES_1(Ensure_expanded_instruction_macros_has_run_p);
    }
    else
	return VALUES_1(Nil);
}

void g2_final_INIT()
{
    Object Qroot, AB_package;

    x_note_fn_call(254,1);
    SET_PACKAGE("AB");
    if (Ensure_expanded_instruction_macros_has_run_p == UNBOUND)
	Ensure_expanded_instruction_macros_has_run_p = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    initialize_or_update_method_tables_of_class_descriptions(Qroot);
    System_class_method_tables_processed_qm = T;
    System_class_method_tables_processed_qm = T;
    validate_static_evaulate_role_dispatcher();
}
