/* g2fnl.c
 * Input file:  g2-final.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2fnl.h"


Object Ensure_expanded_instruction_macros_has_run_p = UNBOUND;

/* ENSURE-EXPANDED-INSTRUCTION-MACROS */
Object ensure_expanded_instruction_macros()
{
    x_note_fn_call(257,0);
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

    x_note_fn_call(257,1);
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
