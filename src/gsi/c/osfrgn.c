/* osfrgn.c
 * Input file:  os-foreign.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "osfrgn.h"


Object G2int_maximum_gensym_environment_variable_length = UNBOUND;

Object G2int_gensym_environment_variable_buffer = UNBOUND;

Object G2int_gensym_environment_variable_success = UNBOUND;

Object G2int_gensym_environment_variable_failure = UNBOUND;

Object G2int_null_character_for_c_strings = UNBOUND;

/* LOAD-FOREIGN-LIBRARIES */
Object g2int_load_foreign_libraries(libraries)
    Object libraries;
{
    x_note_fn_call(8,0);
    if (libraries)
	format((SI_Long)3L,T,"~&;;; Loading foreign libraries: ~{~A ~}~%",
		libraries);
    return VALUES_1(Nil);
}

Object G2int_staris_g2_enterpriseqmstar = UNBOUND;

/* G2-ENTERPRISE-P */
Object g2int_g2_enterprise_p()
{
    x_note_fn_call(8,1);
    return VALUES_1(G2int_staris_g2_enterpriseqmstar);
}

void os_foreign_INIT()
{
    Object Qg2int_null_character_for_c_strings, AB_package;

    x_note_fn_call(8,2);
    SET_PACKAGE("AB");
    G2int_maximum_gensym_environment_variable_length = FIX((SI_Long)1023L);
    if (G2int_gensym_environment_variable_buffer == UNBOUND)
	G2int_gensym_environment_variable_buffer = make_string(1,
		FIX((SI_Long)1023L));
    G2int_gensym_environment_variable_success = FIX((SI_Long)0L);
    G2int_gensym_environment_variable_failure = FIX((SI_Long)-1L);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_null_character_for_c_strings = 
	    STATIC_SYMBOL("NULL-CHARACTER-FOR-C-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_null_character_for_c_strings,
	    G2int_null_character_for_c_strings);
    SET_SYMBOL_VALUE(Qg2int_null_character_for_c_strings,
	    CODE_CHAR(FIX((SI_Long)0L)));
    if (G2int_staris_g2_enterpriseqmstar == UNBOUND)
	G2int_staris_g2_enterpriseqmstar = isG2Enterprise() == (SI_Long)0L 
		? Nil : T;
}
