/* ntrrr.c
 * Input file:  neterror.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntrrr.h"


Object The_type_description_of_error_code = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_error_codes, Qchain_of_available_error_codes);

DEFINE_VARIABLE_WITH_SYMBOL(Error_code_count, Qerror_code_count);

Object Chain_of_available_error_codes_vector = UNBOUND;

/* ERROR-CODE-STRUCTURE-MEMORY-USAGE */
Object error_code_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(48,0);
    temp = Error_code_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ERROR-CODE-COUNT */
Object outstanding_error_code_count()
{
    Object def_structure_error_code_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(48,1);
    gensymed_symbol = IFIX(Error_code_count);
    def_structure_error_code_variable = Chain_of_available_error_codes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_error_code_variable))
	goto end_loop;
    def_structure_error_code_variable = 
	    ISVREF(def_structure_error_code_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ERROR-CODE-1 */
Object reclaim_error_code_1(error_code)
    Object error_code;
{
    Object temp, svref_arg_2;

    x_note_fn_call(48,2);
    inline_note_reclaim_cons(error_code,Nil);
    temp = ISVREF(Chain_of_available_error_codes_vector,
	    IFIX(Current_thread_index));
    SVREF(error_code,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_error_codes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = error_code;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ERROR-CODE */
Object reclaim_structure_for_error_code(error_code)
    Object error_code;
{
    x_note_fn_call(48,3);
    return reclaim_error_code_1(error_code);
}

static Object Qg2_defstruct_structure_name_error_code_g2_struct;  /* g2-defstruct-structure-name::error-code-g2-struct */

/* MAKE-PERMANENT-ERROR-CODE-STRUCTURE-INTERNAL */
Object make_permanent_error_code_structure_internal()
{
    Object def_structure_error_code_variable, defstruct_g2_error_code_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(48,4);
    def_structure_error_code_variable = Nil;
    atomic_incff_symval(Qerror_code_count,FIX((SI_Long)1L));
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
Object make_error_code_1(error_severity,error_format_string)
    Object error_severity, error_format_string;
{
    Object def_structure_error_code_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(48,5);
    def_structure_error_code_variable = 
	    ISVREF(Chain_of_available_error_codes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_error_code_variable) {
	svref_arg_1 = Chain_of_available_error_codes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_error_code_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_error_code_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_error_code_g2_struct;
    }
    else
	def_structure_error_code_variable = 
		make_permanent_error_code_structure_internal();
    inline_note_allocate_cons(def_structure_error_code_variable,Nil);
    SVREF(def_structure_error_code_variable,FIX((SI_Long)2L)) = error_severity;
    SVREF(def_structure_error_code_variable,FIX((SI_Long)1L)) = 
	    error_format_string;
    return VALUES_1(def_structure_error_code_variable);
}

Object Error_severity_success = UNBOUND;

Object Error_severity_informational = UNBOUND;

Object Error_severity_warning = UNBOUND;

Object Error_severity_fatal = UNBOUND;

void neterror_INIT()
{
    Object temp, reclaim_structure_for_error_code_1;
    Object Qerror_code, Qreclaim_structure, AB_package;
    Object Qoutstanding_error_code_count, Qerror_code_structure_memory_usage;
    Object Qutilities2, string_constant_1, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(48,6);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_error_code_g2_struct = 
	    STATIC_SYMBOL("ERROR-CODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qerror_code = STATIC_SYMBOL("ERROR-CODE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_error_code_g2_struct,
	    Qerror_code,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qerror_code,
	    Qg2_defstruct_structure_name_error_code_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_error_code == UNBOUND)
	The_type_description_of_error_code = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m83h5y1n83h5y8n8k1l8n0000001l1n8y83-3Yy1m83vcy83vbyknk0k0");
    temp = The_type_description_of_error_code;
    The_type_description_of_error_code = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_error_code_g2_struct,
	    The_type_description_of_error_code,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qerror_code,The_type_description_of_error_code,
	    Qtype_description_of_type);
    Qoutstanding_error_code_count = 
	    STATIC_SYMBOL("OUTSTANDING-ERROR-CODE-COUNT",AB_package);
    Qerror_code_structure_memory_usage = 
	    STATIC_SYMBOL("ERROR-CODE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_1 = STATIC_STRING("1q83h5y8s83-Sxy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_error_code_count);
    push_optimized_constant(Qerror_code_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_error_codes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ERROR-CODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_error_codes,
	    Chain_of_available_error_codes);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_error_codes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qerror_code_count = STATIC_SYMBOL("ERROR-CODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qerror_code_count,Error_code_count);
    record_system_variable(Qerror_code_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_error_codes_vector == UNBOUND)
	Chain_of_available_error_codes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qerror_code_structure_memory_usage,
	    STATIC_FUNCTION(error_code_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_error_code_count,
	    STATIC_FUNCTION(outstanding_error_code_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_error_code_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_error_code,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qerror_code,
	    reclaim_structure_for_error_code_1);
    Error_severity_success = FIX((SI_Long)0L);
    Error_severity_informational = FIX((SI_Long)1L);
    Error_severity_warning = FIX((SI_Long)2L);
    Error_severity_fatal = FIX((SI_Long)3L);
}
