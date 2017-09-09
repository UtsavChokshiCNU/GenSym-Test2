/* os-set.c
 * Input file:  os-settings.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "os-set.h"


DEFINE_VARIABLE_WITH_SYMBOL(Unix_command_line_arguments, Qunix_command_line_arguments);

DEFINE_VARIABLE_WITH_SYMBOL(Unix_command_line_arguments_as_text_strings, Qunix_command_line_arguments_as_text_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Unix_command_line_argument_count, Qunix_command_line_argument_count);

/* CACHE-COMMAND-LINE-IF-NECESSARY */
Object cache_command_line_if_necessary()
{
    Object argument, result_1, ab_loopvar_, ab_loopvar__1;
    SI_Long argument_number;

    x_note_fn_call(11,0);
    if (EQ(Unix_command_line_arguments_as_text_strings,T) || 
	    EQ(Unix_command_line_arguments,T)) {
	argument_number = (SI_Long)0L;
	argument = Nil;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	argument = foreign_get_command_line_argument(FIX(argument_number));
	if ( !TRUEP(argument))
	    goto end_loop;
	ab_loopvar__1 = gensym_cons_function(argument,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	argument_number = argument_number + (SI_Long)1L;
	goto next_loop;
      end_loop:
	Unix_command_line_arguments = result_1;
	Unix_command_line_argument_count = FIX(argument_number);
	return copy_unix_line_arguments_as_text_strings();
    }
    else
	return VALUES_1(Nil);
}

static Object Qcommand_line_argument;  /* command-line-argument */

/* COPY-UNIX-LINE-ARGUMENTS-AS-TEXT-STRINGS */
Object copy_unix_line_arguments_as_text_strings()
{
    Object string_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(11,1);
    string_1 = Nil;
    ab_loop_list_ = Unix_command_line_arguments;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_function(import_text_string(2,string_1,
	    Qcommand_line_argument),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    Unix_command_line_arguments_as_text_strings = ab_loopvar_;
    goto end_1;
    Unix_command_line_arguments_as_text_strings = Qnil;
  end_1:;
    return VALUES_1(Unix_command_line_arguments_as_text_strings);
}

/* C-RETURN-ARGV-N */
Object c_return_argv_n(buff,arg_number)
    Object buff, arg_number;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(11,2);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_return_argv(ISTRING(temp),IFIX(arg_number)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* FOREIGN-GET-COMMAND-LINE-ARGUMENT */
Object foreign_get_command_line_argument(argument_number)
    Object argument_number;
{
    Object buffer, result_code, temp;
    SI_Long length_1;

    x_note_fn_call(11,3);
    length_1 = g2ext_argv_strlen(IFIX(argument_number));
    if (length_1 == IFIX(C_argv_n_strlen_failure))
	return VALUES_1(Nil);
    else {
	buffer = obtain_simple_gensym_string(FIX(length_1));
	result_code = c_return_argv_n(buffer,argument_number);
	if (FIXNUM_EQ(result_code,Gensym_environment_variable_success)) {
	    temp = copy_null_terminated_string_as_text_string(buffer);
	    reclaim_gensym_string(buffer);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GET-GENSYM-COMMAND-LINE-ARGUMENT */
Object get_gensym_command_line_argument(arg_number)
    Object arg_number;
{
    x_note_fn_call(11,4);
    if (LISTP(Unix_command_line_arguments))
	return nth(arg_number,Unix_command_line_arguments);
    else
	return VALUES_1(Nil);
}

/* GET-GENSYM-COMMAND-LINE-ARGUMENT-AS-TEXT-STRING */
Object get_gensym_command_line_argument_as_text_string(arg_number)
    Object arg_number;
{
    x_note_fn_call(11,5);
    if (LISTP(Unix_command_line_arguments_as_text_strings))
	return nth(arg_number,Unix_command_line_arguments_as_text_strings);
    else
	return VALUES_1(Nil);
}

/* C-ENVIRONMENT-VAR-STRLEN */
Object c_environment_var_strlen(name)
    Object name;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(11,6);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp = FIX(g2ext_environment_variable_strlen(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-RETURN-ENVIRONMENT-VAR */
Object c_return_environment_var(name,buff)
    Object name, buff;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(11,7);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(buff);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* FOREIGN-GET-ENVIRONMENT-VARIABLE */
Object foreign_get_environment_variable(name)
    Object name;
{
    Object length_1, buffer, result_code, temp;

    x_note_fn_call(11,8);
    length_1 = c_environment_var_strlen(name);
    if (FIXNUM_EQ(length_1,C_environment_var_strlen_failure))
	return VALUES_1(Nil);
    else {
	buffer = obtain_simple_gensym_string(length_1);
	result_code = c_return_environment_var(name,buffer);
	if (FIXNUM_EQ(result_code,Gensym_environment_variable_success)) {
	    temp = copy_null_terminated_string_as_text_string(buffer);
	    reclaim_gensym_string(buffer);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qintelnt;            /* intelnt */

static Object Qwindows;            /* windows */

static Object Qalphant;            /* alphant */

static Object Qwindows95;          /* windows95 */

static Object Qdos;                /* dos */

/* WINDOWS-PLATFORM-P */
Object windows_platform_p()
{
    Object temp;

    x_note_fn_call(11,9);
    temp = EQ(G2_machine_type,Qintelnt) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2_machine_type,Qwindows) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2_machine_type,Qalphant) ? T : Nil;
    if (temp);
    else
	temp = EQ(G2_machine_type,Qwindows95) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(G2_machine_type,Qdos) ? T : Nil);
}

void os_settings_INIT()
{
    Object AB_package;

    x_note_fn_call(11,10);
    SET_PACKAGE("AB");
    if (Unix_command_line_arguments == UNBOUND)
	Unix_command_line_arguments = T;
    if (Unix_command_line_arguments_as_text_strings == UNBOUND)
	Unix_command_line_arguments_as_text_strings = T;
    if (Unix_command_line_argument_count == UNBOUND)
	Unix_command_line_argument_count = FIX((SI_Long)0L);
    AB_package = STATIC_PACKAGE("AB");
    Qcommand_line_argument = STATIC_SYMBOL("COMMAND-LINE-ARGUMENT",AB_package);
    Qintelnt = STATIC_SYMBOL("INTELNT",AB_package);
    Qwindows = STATIC_SYMBOL("WINDOWS",AB_package);
    Qalphant = STATIC_SYMBOL("ALPHANT",AB_package);
    Qwindows95 = STATIC_SYMBOL("WINDOWS95",AB_package);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
}
