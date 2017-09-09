/* os-set.c
 * Input file:  os-settings.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "os-set.h"


Object G2int_unix_command_line_arguments = UNBOUND;

Object G2int_unix_command_line_arguments_as_text_strings = UNBOUND;

Object G2int_unix_command_line_argument_count = UNBOUND;

/* CACHE-COMMAND-LINE-IF-NECESSARY */
Object g2int_cache_command_line_if_necessary()
{
    Object argument, result_1, ab_loopvar_, ab_loopvar__1;
    SI_Long argument_number;

    x_note_fn_call(11,0);
    if (EQ(G2int_unix_command_line_arguments_as_text_strings,T) || 
	    EQ(G2int_unix_command_line_arguments,T)) {
	argument_number = (SI_Long)0L;
	argument = Nil;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	argument = 
		g2int_foreign_get_command_line_argument(FIX(argument_number));
	if ( !TRUEP(argument))
	    goto end_loop;
	ab_loopvar__1 = g2int_gensym_cons_function(argument,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	argument_number = argument_number + (SI_Long)1L;
	goto next_loop;
      end_loop:
	G2int_unix_command_line_arguments = result_1;
	G2int_unix_command_line_argument_count = FIX(argument_number);
	return g2int_copy_unix_line_arguments_as_text_strings();
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_command_line_argument;  /* command-line-argument */

/* COPY-UNIX-LINE-ARGUMENTS-AS-TEXT-STRINGS */
Object g2int_copy_unix_line_arguments_as_text_strings()
{
    Object string_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(11,1);
    string_1 = Nil;
    ab_loop_list_ = G2int_unix_command_line_arguments;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = g2int_gensym_cons_function(g2int_import_text_string(2,
	    string_1,Qg2int_command_line_argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    G2int_unix_command_line_arguments_as_text_strings = ab_loopvar_;
    goto end;
    G2int_unix_command_line_arguments_as_text_strings = Qnil;
  end:;
    return VALUES_1(G2int_unix_command_line_arguments_as_text_strings);
}

/* C-RETURN-ARGV-N */
Object g2int_c_return_argv_n(buff,arg_number)
    Object buff, arg_number;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(11,2);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_return_argv(ISTRING(temp),IFIX(arg_number)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* FOREIGN-GET-COMMAND-LINE-ARGUMENT */
Object g2int_foreign_get_command_line_argument(argument_number)
    Object argument_number;
{
    Object buffer, result_code, temp;
    SI_Long length_1;

    x_note_fn_call(11,3);
    length_1 = g2ext_argv_strlen(IFIX(argument_number));
    if (length_1 == IFIX(G2int_c_argv_n_strlen_failure))
	return VALUES_1(Nil);
    else {
	buffer = g2int_obtain_simple_gensym_string(FIX(length_1));
	result_code = g2int_c_return_argv_n(buffer,argument_number);
	if (FIXNUM_EQ(result_code,G2int_gensym_environment_variable_success)) {
	    temp = g2int_copy_null_terminated_string_as_text_string(buffer);
	    g2int_reclaim_gensym_string(buffer);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GET-GENSYM-COMMAND-LINE-ARGUMENT */
Object g2int_get_gensym_command_line_argument(arg_number)
    Object arg_number;
{
    x_note_fn_call(11,4);
    if (LISTP(G2int_unix_command_line_arguments))
	return nth(arg_number,G2int_unix_command_line_arguments);
    else
	return VALUES_1(Nil);
}

/* GET-GENSYM-COMMAND-LINE-ARGUMENT-AS-TEXT-STRING */
Object g2int_get_gensym_command_line_argument_as_text_string(arg_number)
    Object arg_number;
{
    x_note_fn_call(11,5);
    if (LISTP(G2int_unix_command_line_arguments_as_text_strings))
	return nth(arg_number,
		G2int_unix_command_line_arguments_as_text_strings);
    else
	return VALUES_1(Nil);
}

/* C-ENVIRONMENT-VAR-STRLEN */
Object g2int_c_environment_var_strlen(name)
    Object name;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(11,6);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp = FIX(g2ext_environment_variable_strlen(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-RETURN-ENVIRONMENT-VAR */
Object g2int_c_return_environment_var(name,buff)
    Object name, buff;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(11,7);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_return_environment_variable(temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* FOREIGN-GET-ENVIRONMENT-VARIABLE */
Object g2int_foreign_get_environment_variable(name)
    Object name;
{
    Object length_1, buffer, result_code, temp;

    x_note_fn_call(11,8);
    length_1 = g2int_c_environment_var_strlen(name);
    if (FIXNUM_EQ(length_1,G2int_c_environment_var_strlen_failure))
	return VALUES_1(Nil);
    else {
	buffer = g2int_obtain_simple_gensym_string(length_1);
	result_code = g2int_c_return_environment_var(name,buffer);
	if (FIXNUM_EQ(result_code,G2int_gensym_environment_variable_success)) {
	    temp = g2int_copy_null_terminated_string_as_text_string(buffer);
	    g2int_reclaim_gensym_string(buffer);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qg2int_intelnt;      /* intelnt */

static Object Qg2int_windows;      /* windows */

static Object Qg2int_alphant;      /* alphant */

static Object Qg2int_windows95;    /* windows95 */

static Object Qg2int_dos;          /* dos */

/* WINDOWS-PLATFORM-P */
Object g2int_windows_platform_p()
{
    Object temp;

    x_note_fn_call(11,9);
    temp = EQ(G2int_g2_machine_type,Qg2int_intelnt) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2int_g2_machine_type,Qg2int_windows) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2int_g2_machine_type,Qg2int_alphant) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2int_g2_machine_type,Qg2int_windows95) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(G2int_g2_machine_type,Qg2int_dos) ? T : Nil);
}

void os_settings_INIT()
{
    Object AB_package;

    x_note_fn_call(11,10);
    SET_PACKAGE("AB");
    if (G2int_unix_command_line_arguments == UNBOUND)
	G2int_unix_command_line_arguments = T;
    if (G2int_unix_command_line_arguments_as_text_strings == UNBOUND)
	G2int_unix_command_line_arguments_as_text_strings = T;
    if (G2int_unix_command_line_argument_count == UNBOUND)
	G2int_unix_command_line_argument_count = FIX((SI_Long)0L);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_command_line_argument = STATIC_SYMBOL("COMMAND-LINE-ARGUMENT",
	    AB_package);
    Qg2int_intelnt = STATIC_SYMBOL("INTELNT",AB_package);
    Qg2int_windows = STATIC_SYMBOL("WINDOWS",AB_package);
    Qg2int_alphant = STATIC_SYMBOL("ALPHANT",AB_package);
    Qg2int_windows95 = STATIC_SYMBOL("WINDOWS95",AB_package);
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
}
