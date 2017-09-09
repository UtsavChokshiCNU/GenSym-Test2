/* osfrgn.c
 * Input file:  os-foreign.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "osfrgn.h"


Object Maximum_gensym_environment_variable_length = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_environment_variable_buffer, Qgensym_environment_variable_buffer);

Object Gensym_environment_variable_success = UNBOUND;

Object Gensym_environment_variable_failure = UNBOUND;

Object Null_character_for_c_strings = UNBOUND;

/* LOAD-FOREIGN-LIBRARIES */
Object load_foreign_libraries(libraries)
    Object libraries;
{
    x_note_fn_call(8,0);
    if (libraries)
	format((SI_Long)3L,T,"~&;;; Loading foreign libraries: ~{~A ~}~%",
		libraries);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Is_g2_enterprise_qm, Qis_g2_enterprise_qm);

/* G2-ENTERPRISE-P */
Object g2_enterprise_p()
{
    x_note_fn_call(8,1);
    return VALUES_1(Is_g2_enterprise_qm);
}

void os_foreign_INIT()
{
    Object Qnull_character_for_c_strings, AB_package;

    x_note_fn_call(8,2);
    SET_PACKAGE("AB");
    Maximum_gensym_environment_variable_length = FIX((SI_Long)1023L);
    if (Gensym_environment_variable_buffer == UNBOUND)
	Gensym_environment_variable_buffer = make_string(1,
		FIX((SI_Long)1023L));
    Gensym_environment_variable_success = FIX((SI_Long)0L);
    Gensym_environment_variable_failure = FIX((SI_Long)-1L);
    AB_package = STATIC_PACKAGE("AB");
    Qnull_character_for_c_strings = 
	    STATIC_SYMBOL("NULL-CHARACTER-FOR-C-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnull_character_for_c_strings,
	    Null_character_for_c_strings);
    SET_SYMBOL_VALUE(Qnull_character_for_c_strings,
	    CODE_CHAR(FIX((SI_Long)0L)));
    if (Is_g2_enterprise_qm == UNBOUND)
	Is_g2_enterprise_qm = isG2Enterprise() == (SI_Long)0L ? Nil : T;
}
