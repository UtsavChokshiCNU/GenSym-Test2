/* ntrrr.c
 * Input file:  neterror.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntrrr.h"


Object G2int_the_type_description_of_error_code = UNBOUND;

Object G2int_chain_of_available_error_codes = UNBOUND;

Object G2int_error_code_count = UNBOUND;

/* RECLAIM-ERROR-CODE-1 */
Object g2int_reclaim_error_code_1(error_code)
    Object error_code;
{
    Object svref_new_value;

    x_note_fn_call(37,0);
    inline_note_reclaim_cons(error_code,Nil);
    svref_new_value = G2int_chain_of_available_error_codes;
    SVREF(error_code,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_error_codes = error_code;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ERROR-CODE */
Object g2int_reclaim_structure_for_error_code(error_code)
    Object error_code;
{
    x_note_fn_call(37,1);
    return g2int_reclaim_error_code_1(error_code);
}

static Object Qg2_defstruct_structure_name_error_code_g2_struct;  /* g2-defstruct-structure-name::error-code-g2-struct */

/* MAKE-PERMANENT-ERROR-CODE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_error_code_structure_internal()
{
    Object def_structure_error_code_variable, error_code_count_new_value;
    Object defstruct_g2_error_code_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(37,2);
    def_structure_error_code_variable = Nil;
    error_code_count_new_value = FIXNUM_ADD1(G2int_error_code_count);
    G2int_error_code_count = error_code_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_error_code_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_error_code_variable = the_array;
	SVREF(defstruct_g2_error_code_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_error_code_g2_struct;
	def_structure_error_code_variable = defstruct_g2_error_code_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_error_code_variable);
}

/* MAKE-ERROR-CODE-1 */
Object g2int_make_error_code_1(error_severity,error_format_string)
    Object error_severity, error_format_string;
{
    Object def_structure_error_code_variable;

    x_note_fn_call(37,3);
    def_structure_error_code_variable = G2int_chain_of_available_error_codes;
    if (def_structure_error_code_variable) {
	G2int_chain_of_available_error_codes = 
		ISVREF(def_structure_error_code_variable,(SI_Long)0L);
	SVREF(def_structure_error_code_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_error_code_g2_struct;
    }
    else
	def_structure_error_code_variable = 
		g2int_make_permanent_error_code_structure_internal();
    inline_note_allocate_cons(def_structure_error_code_variable,Nil);
    SVREF(def_structure_error_code_variable,FIX((SI_Long)2L)) = error_severity;
    SVREF(def_structure_error_code_variable,FIX((SI_Long)1L)) = 
	    error_format_string;
    return VALUES_1(def_structure_error_code_variable);
}

Object G2int_error_severity_success = UNBOUND;

Object G2int_error_severity_informational = UNBOUND;

Object G2int_error_severity_warning = UNBOUND;

Object G2int_error_severity_fatal = UNBOUND;

void neterror_INIT()
{
    Object temp, reclaim_structure_for_error_code;
    Object Qg2int_error_code, Qg2int_reclaim_structure, AB_package;
    Object Qg2int_utilities2, Qg2int_error_code_count;
    Object Qg2int_chain_of_available_error_codes;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(37,4);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_error_code_g2_struct = 
	    STATIC_SYMBOL("ERROR-CODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_error_code = STATIC_SYMBOL("ERROR-CODE",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_error_code_g2_struct,
	    Qg2int_error_code,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_error_code,
	    Qg2_defstruct_structure_name_error_code_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_error_code == UNBOUND)
	G2int_the_type_description_of_error_code = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8l83gy1n83gy8m8k1l8m0000001l1n8n83*Sy1m83iy83hyknk0k0");
    temp = G2int_the_type_description_of_error_code;
    G2int_the_type_description_of_error_code = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_error_code_g2_struct,
	    G2int_the_type_description_of_error_code,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_error_code,
	    G2int_the_type_description_of_error_code,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_error_codes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ERROR-CODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_error_codes,
	    G2int_chain_of_available_error_codes);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_error_codes,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_error_code_count = STATIC_SYMBOL("ERROR-CODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_error_code_count,G2int_error_code_count);
    g2int_record_system_variable(Qg2int_error_code_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_error_code = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_error_code,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_error_code,reclaim_structure_for_error_code);
    G2int_error_severity_success = FIX((SI_Long)0L);
    G2int_error_severity_informational = FIX((SI_Long)1L);
    G2int_error_severity_warning = FIX((SI_Long)2L);
    G2int_error_severity_fatal = FIX((SI_Long)3L);
}
