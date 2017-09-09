/* btstrp.c
 * Input file:  bootstrap.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "btstrp.h"


Object Allow_development_compile_p = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_system_being_loaded, Qcurrent_system_being_loaded);

DEFINE_VARIABLE_WITH_SYMBOL(Override_eliminate_for_gsi_p, Qoverride_eliminate_for_gsi_p);

DEFINE_VARIABLE_WITH_SYMBOL(Override_eliminate_for_gsi_no_utf_g_p, Qoverride_eliminate_for_gsi_no_utf_g_p);

DEFINE_VARIABLE_WITH_SYMBOL(Macroexpanding_for_instruction_expander, Qmacroexpanding_for_instruction_expander);

static Object Kchestnut_3;         /* :chestnut-3 */

static Object string_constant;     /* "GENSYMED-SYMBOL" */

/* GENSYM */
Object ab_gensym varargs_1(int, n)
{
    Object x;
    char x_supplied_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,0);
    INIT_ARGS_nonrelocating();
    x_supplied_p = OPTIONAL_ARG_P_nonrelocating();
    x = x_supplied_p ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (member_eq(Kchestnut_3,Features)) {
	if (STRINGP(x))
	    return make_symbol(x);
	else
	    return make_symbol(string_constant);
    }
    else if (x_supplied_p)
	return gensym(x);
    else
	return gensym(_);
}

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_defun_warned_for_catch_qm, Qmost_recent_defun_warned_for_catch_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_defun_warned_for_unwind_protect_qm, Qmost_recent_defun_warned_for_unwind_protect_qm);

/* STRING-OR-SYMBOL-EQUAL */
Object string_or_symbol_equal(symbol_or_string_1,symbol_or_string_2)
    Object symbol_or_string_1, symbol_or_string_2;
{
    x_note_fn_call(1,1);
    if ((SYMBOLP(symbol_or_string_1) || STRINGP(symbol_or_string_1)) && 
	    (SYMBOLP(symbol_or_string_2) || STRINGP(symbol_or_string_2)))
	return string_equal(2,string(symbol_or_string_1),
		string(symbol_or_string_2));
    else
	return VALUES_1(Nil);
}

static Object Qstring_or_symbol_equal;  /* string-or-symbol-equal */

static Object Qab_or;              /* or */

/* EVAL-FEATURE */
Object eval_feature(feature)
    Object feature;
{
    Object temp, feature_old_value, features;

    x_note_fn_call(1,2);
    if (ATOM(feature)) {
	if (EQ(feature,T))
	    return VALUES_1(feature);
	else
	    return member(4,feature,Features,Ktest,
		    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
    }
    else {
	temp = CAR(feature);
	if (EQ(temp,Qand)) {
	    feature_old_value = feature;
	    feature = REST(feature_old_value);
	    if (feature) {
		features = feature;
		feature = CAR(features);
		for (;;) {
		    if ( !TRUEP(features))
			return VALUES_1(T);
		    if ( !TRUEP(eval_feature(feature)))
			return VALUES_1(Nil);
		    features = CDR(features);
		    feature = CAR(features);
		}
	    }
	    else
		return VALUES_1(T);
	}
	else if (EQ(temp,Qab_or)) {
	    feature_old_value = feature;
	    feature = REST(feature_old_value);
	    if (feature) {
		features = feature;
		feature = CAR(features);
		for (;;) {
		    if ( !TRUEP(features))
			return VALUES_1(Nil);
		    if (eval_feature(feature))
			return VALUES_1(T);
		    features = CDR(features);
		    feature = CAR(features);
		}
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qnot))
	    return VALUES_1( !TRUEP(eval_feature(CADR(feature))) ? T : Nil);
	else
	    return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_qm, Qcurrent_module_qm);

/* SIGNAL-FORWARD-REFERENCE */
Object signal_forward_reference(name_of_function_qm)
    Object name_of_function_qm;
{
    x_note_fn_call(1,3);
    if (name_of_function_qm)
	return cerror((SI_Long)3L,"Ignore this problem and proceed.",
		"The forwardly referenced function ~a is still undefined!",
		name_of_function_qm);
    else
	return cerror((SI_Long)2L,"Ignore this problem and proceed.",
		"This forwardly referenced function is still undefined!");
}

/* STAND-IN-FOR-FORWARDLY-REFERENCED-FUNCTION */
Object stand_in_for_forwardly_referenced_function varargs_1(int, n)
{
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,4);
    INIT_ARGS_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return signal_forward_reference(Nil);
}

/* PATHNAMES-SIMILAR-P */
Object pathnames_similar_p(pathname_1,pathname_2)
    Object pathname_1, pathname_2;
{
    Object temp, temp_1;
    char temp_2;

    x_note_fn_call(1,5);
    temp = string_upcase(1,string(directory_namestring(pathname_1)));
    temp_1 = string_upcase(1,string(directory_namestring(pathname_2)));
    if (EQUAL(temp,temp_1)) {
	temp_1 = string_upcase(1,string(pathname_name(pathname_1)));
	temp = string_upcase(1,string(pathname_name(pathname_2)));
	temp_2 = EQUAL(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp_1 = string_upcase(1,string(pathname_type(pathname_1)));
	temp = string_upcase(1,string(pathname_type(pathname_2)));
	return VALUES_1(EQUAL(temp_1,temp) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_directory_of_source_truenames_qm, Qcurrent_directory_of_source_truenames_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_directory_of_binary_truenames, Qcurrent_directory_of_binary_truenames);

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_distribution_binaries_qm, Qpathname_for_distribution_binaries_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Use_directory_lists_for_bootstrapping_qm, Quse_directory_lists_for_bootstrapping_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Last_bootstrap_mode_qm, Qlast_bootstrap_mode_qm);

Object Positive_bits_per_fixnum = UNBOUND;

Object Least_positive_normalized_gensym_float = UNBOUND;

Object Most_negative_gensym_float = UNBOUND;

Object Most_positive_gensym_float = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Ab_package_1, Qab_package_1);

DEFINE_VARIABLE_WITH_SYMBOL(All_systems, Qall_systems);

/* SYSTEM-P */
Object system_p(system_name)
    Object system_name;
{
    x_note_fn_call(1,6);
    return member(4,system_name,All_systems,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
}

static Object Qreal_system_name;   /* real-system-name */

/* NORMALIZE-SYSTEM-NAME */
Object normalize_system_name(system_name)
    Object system_name;
{
    Object gensymed_symbol, internable_string, temp;

    x_note_fn_call(1,7);
    if (system_p(system_name)) {
	gensymed_symbol = system_name;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		Ab_package_1))
	    return VALUES_1(gensymed_symbol);
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else if (NUMBERP(gensymed_symbol))
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    else
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    temp = intern(internable_string,Ab_package_1);
	    return VALUES_1(temp);
	}
    }
    else {
	gensymed_symbol = system_name;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		Ab_package_1))
	    temp = gensymed_symbol;
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else if (NUMBERP(gensymed_symbol))
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    else
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    temp = intern(internable_string,Ab_package_1);
	}
	temp = get(temp,Qreal_system_name,_);
	if (temp)
	    return VALUES_1(temp);
	else {
	    gensymed_symbol = system_name;
	    if (SYMBOLP(gensymed_symbol) && 
		    EQ(SYMBOL_PACKAGE(gensymed_symbol),Ab_package_1))
		return VALUES_1(gensymed_symbol);
	    else {
		if (SYMBOLP(gensymed_symbol))
		    internable_string = SYMBOL_NAME(gensymed_symbol);
		else if (STRINGP(gensymed_symbol))
		    internable_string = gensymed_symbol;
		else if (NUMBERP(gensymed_symbol))
		    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			    gensymed_symbol);
		else
		    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			    gensymed_symbol);
		temp = intern(internable_string,Ab_package_1);
		return VALUES_1(temp);
	    }
	}
    }
}

static Object Knon_development_macros;  /* :non-development-macros */

static Object Qlocal_macro_directory;  /* local-macro-directory */

static Object Qab;                 /* ab */

static Object Kno_macros;          /* :no-macros */

static Object Qlocal_chestnut_dst_directory;  /* local-chestnut-dst-directory */

static Object Qlocal_dst_directory;  /* local-dst-directory */

static Object Qsystem_binary_pathname_qm;  /* system-binary-pathname? */

/* SYSTEM-BINARY-PATHNAME? */
Object system_binary_pathname_qm(system_1)
    Object system_1;
{
    Object pathname_qm, temp;

    x_note_fn_call(1,8);
    pathname_qm = Nil;
    if (eval_feature(Knon_development_macros)) {
	temp = get(system_1,Qlocal_macro_directory,_);
	if (temp);
	else
	    temp = get(Qab,Qlocal_macro_directory,_);
	pathname_qm = temp;
    }
    else if (eval_feature(Kno_macros)) {
	if (eval_feature(Kchestnut)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp);
	    else
		temp = get(Qab,Qlocal_chestnut_dst_directory,_);
	    pathname_qm = temp;
	}
	else if (eval_feature(Kchestnut_3)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp);
	    else
		temp = get(Qab,Qlocal_chestnut_dst_directory,_);
	    pathname_qm = temp;
	}
	else {
	    temp = get(system_1,Qlocal_dst_directory,_);
	    if (temp);
	    else
		temp = get(Qab,Qlocal_dst_directory,_);
	    pathname_qm = temp;
	}
    }
    else
	pathname_qm = Nil;
    temp = pathname_qm;
    if (temp);
    else
	temp = get(system_1,Qsystem_binary_pathname_qm,_);
    if (temp)
	return VALUES_1(temp);
    else
	return get(Qab,Qsystem_binary_pathname_qm,_);
}

/* An output stream used by Boot-System as a `null device' when silent operation is needed. */
Object Null_io = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Filename_of_module_being_loaded_qm, Qfilename_of_module_being_loaded_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_source_filename, Qcurrent_module_source_filename);

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_lisp_binary_filename, Qcurrent_module_lisp_binary_filename);

Object Alist_of_file_property_base_defaults = UNBOUND;

static Object Koptional_module_p;  /* :optional-module-p */

static Object Qall_optional_modules;  /* all-optional-modules */

/* SET-FILE-PROPERTY */
Object set_file_property(file_symbol,file_class,system_1,property_name,
	    property_value)
    Object file_symbol, file_class, system_1, property_name, property_value;
{
    Object file_symbol_plist, file_class_plist, pushnew_arg, get_new_value;

    x_note_fn_call(1,9);
    file_symbol_plist = get(file_symbol,property_name,_);
    file_class_plist = getf(file_symbol_plist,file_class,_);
    if (EQ(property_name,Koptional_module_p)) {
	if (property_value) {
	    pushnew_arg = file_symbol;
	    get_new_value = adjoin(2,pushnew_arg,get(system_1,
		    Qall_optional_modules,Nil));
	    set_get(system_1,Qall_optional_modules,get_new_value);
	}
	else {
	    get_new_value = ldelete(4,file_symbol,get(system_1,
		    Qall_optional_modules,_),Ktest,
		    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
	    set_get(system_1,Qall_optional_modules,get_new_value);
	}
    }
    file_class_plist = set_getf(file_class_plist,system_1,property_value);
    file_symbol_plist = set_getf(file_symbol_plist,file_class,
	    file_class_plist);
    return set_get(file_symbol,property_name,file_symbol_plist);
}

/* GET-FILE-PROPERTY */
Object get_file_property(file_symbol,file_class,system_1,property_name)
    Object file_symbol, file_class, system_1, property_name;
{
    Object file_symbol_plist, file_class_plist;

    x_note_fn_call(1,10);
    file_symbol_plist = get(file_symbol,property_name,_);
    file_class_plist = getf(file_symbol_plist,file_class,_);
    return getf(file_class_plist,system_1,_);
}

static Object Koverriding_include_test;  /* :overriding-include-test */

/* GET-DEFAULT-INCLUDE-TEST */
Object get_default_include_test(file_symbol,file_class,system_1,
	    situatation_property_name)
    Object file_symbol, file_class, system_1, situatation_property_name;
{
    Object temp;

    x_note_fn_call(1,11);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Koverriding_include_test);
    if (temp)
	return VALUES_1(temp);
    else
	return get_file_property(file_symbol,file_class,system_1,
		situatation_property_name);
}

static Object Qoptional_modules;   /* optional-modules */

/* NON-OPTIONAL-OR-INCLUDED-OPTIONAL-MODULE-P */
Object non_optional_or_included_optional_module_p(file_symbol,file_class,
	    system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,12);
    temp =  !TRUEP(get_file_property(file_symbol,file_class,system_1,
	    Koptional_module_p)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return member_eql(file_symbol,get(system_1,Qoptional_modules,_));
}

static Object Kinclude_test_for_load;  /* :include-test-for-load */

/* INCLUDE-FOR-LOAD-P */
Object include_for_load_p(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    x_note_fn_call(1,13);
    if (eval_feature(get_default_include_test(file_symbol,file_class,
	    system_1,Kinclude_test_for_load)))
	return non_optional_or_included_optional_module_p(file_symbol,
		file_class,system_1);
    else
	return VALUES_1(Nil);
}

static Object Kmaster_directory_namestring;  /* :master-directory-namestring */

static Object Qmaster_source_directory;  /* master-source-directory */

/* GET-DEFAULT-MASTER-DIRECTORY-NAMESTRING */
Object get_default_master_directory_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,14);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kmaster_directory_namestring);
    if (temp);
    else
	temp = get(system_1,Qmaster_source_directory,_);
    if (temp);
    else
	temp = get_file_property(file_symbol,file_class,Qab,
		Kmaster_directory_namestring);
    if (temp)
	return VALUES_1(temp);
    else
	return get(Qab,Qmaster_source_directory,_);
}

static Object Klocal_directory_namestring;  /* :local-directory-namestring */

static Object Qlocal_source_directory;  /* local-source-directory */

/* GET-DEFAULT-LOCAL-DIRECTORY-NAMESTRING */
Object get_default_local_directory_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,15);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Klocal_directory_namestring);
    if (temp);
    else
	temp = get(system_1,Qlocal_source_directory,_);
    if (temp);
    else
	temp = get_file_property(file_symbol,file_class,Qab,
		Klocal_directory_namestring);
    if (temp)
	return VALUES_1(temp);
    else
	return get(Qab,Qlocal_source_directory,_);
}

static Object Kdistribution;       /* :distribution */

/* CHOOSE-APPROPRIATE-BINARY-DIRECTORY */
Object choose_appropriate_binary_directory(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(1,16);
    if (eval_feature(Kdistribution)) {
	if (eval_feature(Kchestnut)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else if (eval_feature(Kchestnut_3)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else {
	    temp = get(system_1,Qlocal_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_dst_directory,_);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Kbinary_directory_namestring;  /* :binary-directory-namestring */

/* GET-DEFAULT-BINARY-DIRECTORY-NAMESTRING */
Object get_default_binary_directory_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,17);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kbinary_directory_namestring);
    if (temp);
    else
	temp = choose_appropriate_binary_directory(system_1);
    if (temp)
	return VALUES_1(temp);
    else
	return get_file_property(file_symbol,file_class,Qab,
		Kbinary_directory_namestring);
}

static Object Kmaster_pathname_name;  /* :master-pathname-name */

/* GET-DEFAULT-MASTER-PATHNAME-NAME */
Object get_default_master_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,18);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kmaster_pathname_name);
    if (temp);
    else
	temp = string_downcase(1,file_symbol);
    if (temp)
	return VALUES_1(temp);
    else
	return get_file_property(file_symbol,file_class,Qab,
		Kmaster_pathname_name);
}

static Object Klocal_pathname_name;  /* :local-pathname-name */

/* GET-DEFAULT-LOCAL-PATHNAME-NAME */
Object get_default_local_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,19);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Klocal_pathname_name);
    if (temp);
    else
	temp = string_downcase(1,file_symbol);
    if (temp)
	return VALUES_1(temp);
    else
	return get_file_property(file_symbol,file_class,Qab,
		Klocal_pathname_name);
}

static Object Kbinary_pathname_name;  /* :binary-pathname-name */

/* GET-DEFAULT-BINARY-PATHNAME-NAME */
Object get_default_binary_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,20);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kbinary_pathname_name);
    if (temp)
	return VALUES_1(temp);
    else
	return get_default_local_pathname_name(file_symbol,file_class,
		system_1);
}

static Object Kmaster_file_type;   /* :master-file-type */

static Object Kdefault_file_type;  /* :default-file-type */

static Object string_constant_1;   /* "" */

/* GET-DEFAULT-MASTER-FILE-TYPE */
Object get_default_master_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,21);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kmaster_file_type);
    if (temp);
    else
	temp = get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Klocal_file_type;    /* :local-file-type */

/* GET-LOCAL-FILE-TYPE */
Object get_local_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,22);
    temp = get_file_property(file_symbol,file_class,system_1,Klocal_file_type);
    if (temp);
    else
	temp = get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Kbinary_file_type;   /* :binary-file-type */

/* GET-BINARY-FILE-TYPE */
Object get_binary_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,23);
    temp = get_file_property(file_symbol,file_class,system_1,
	    Kbinary_file_type);
    if (temp);
    else
	temp = get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Kmaintained_as_a_binary_file_p;  /* :maintained-as-a-binary-file-p */

/* GET-DEFAULT-LOCAL-FILE-TYPE */
Object get_default_local_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    x_note_fn_call(1,24);
    if (get_file_property(file_symbol,file_class,system_1,
	    Kmaintained_as_a_binary_file_p))
	return get_binary_file_type(file_symbol,file_class,system_1);
    else
	return get_local_file_type(file_symbol,file_class,system_1);
}

static Object Kno_lisp_binary_produced_p;  /* :no-lisp-binary-produced-p */

/* GET-DEFAULT-BINARY-FILE-TYPE */
Object get_default_binary_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    x_note_fn_call(1,25);
    if (get_file_property(file_symbol,file_class,system_1,
	    Kno_lisp_binary_produced_p))
	return get_local_file_type(file_symbol,file_class,system_1);
    else
	return get_binary_file_type(file_symbol,file_class,system_1);
}

static Object Kunix;               /* :unix */

static Object Qmaster;             /* master */

/* STRING-FOR-FILE-NAME-AND-TYPE */
Object string_for_file_name_and_type(pathname_name_1,pathname_type_1,host_type)
    Object pathname_name_1, pathname_type_1, host_type;
{
    x_note_fn_call(1,26);
    if ( !TRUEP(pathname_type_1))
	pathname_type_1 = string_constant_1;
    if ( !TRUEP(eval_feature(Kunix))) {
	pathname_name_1 = string_downcase(1,pathname_name_1);
	pathname_type_1 = string_downcase(1,pathname_type_1);
    }
    if ( !EQUAL(host_type,Qmaster) && eval_feature(Kunix) && ( 
	    !TRUEP(pathname_type_1) || EQUAL(pathname_type_1,
	    string_constant_1)))
	return format((SI_Long)3L,Nil,"~A",pathname_name_1);
    else
	return format((SI_Long)4L,Nil,"~A.~A",pathname_name_1,pathname_type_1);
}

/* STRING-FOR-MASTER-FILE-NAME-AND-TYPE */
Object string_for_master_file_name_and_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,27);
    temp = get_default_master_pathname_name(file_symbol,file_class,system_1);
    return string_for_file_name_and_type(temp,
	    get_default_master_file_type(file_symbol,file_class,system_1),
	    Qmaster);
}

static Object Qbinary;             /* binary */

/* STRING-FOR-BINARY-FILE-NAME-AND-TYPE */
Object string_for_binary_file_name_and_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,28);
    temp = get_default_binary_pathname_name(file_symbol,file_class,system_1);
    return string_for_file_name_and_type(temp,
	    get_default_binary_file_type(file_symbol,file_class,system_1),
	    Qbinary);
}

/* STRING-FOR-FILE-NAMESTRING */
Object string_for_file_namestring(directory_namestring_1,pathname_name_1,
	    pathname_type_1,host_type)
    Object directory_namestring_1, pathname_name_1, pathname_type_1, host_type;
{
    x_note_fn_call(1,29);
    return format((SI_Long)4L,Nil,"~A~A",directory_namestring_1,
	    string_for_file_name_and_type(pathname_name_1,pathname_type_1,
	    host_type));
}

static Object string_constant_2;   /* "*" */

/* STRING-FOR-MASTER-FILE-NAMESTRING */
Object string_for_master_file_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp, temp_1;

    x_note_fn_call(1,30);
    temp = get_default_master_directory_namestring(file_symbol,file_class,
	    system_1);
    temp_1 = EQ(file_symbol,Kwild) ? string_constant_2 : 
	    get_default_master_pathname_name(file_symbol,file_class,system_1);
    return string_for_file_namestring(temp,temp_1,
	    get_default_master_file_type(file_symbol,file_class,system_1),
	    Qmaster);
}

static Object Qlocal;              /* local */

/* STRING-FOR-LOCAL-FILE-NAMESTRING */
Object string_for_local_file_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp, temp_1;

    x_note_fn_call(1,31);
    temp = get_default_local_directory_namestring(file_symbol,file_class,
	    system_1);
    temp_1 = EQ(file_symbol,Kwild) ? string_constant_2 : 
	    get_default_local_pathname_name(file_symbol,file_class,system_1);
    return string_for_file_namestring(temp,temp_1,
	    get_default_local_file_type(file_symbol,file_class,system_1),
	    Qlocal);
}

/* STRING-FOR-BINARY-FILE-NAMESTRING */
Object string_for_binary_file_namestring(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp, temp_1;

    x_note_fn_call(1,32);
    temp = get_default_binary_directory_namestring(file_symbol,file_class,
	    system_1);
    temp_1 = EQ(file_symbol,Kwild) ? string_constant_2 : 
	    get_default_binary_pathname_name(file_symbol,file_class,system_1);
    return string_for_file_namestring(temp,temp_1,
	    get_default_binary_file_type(file_symbol,file_class,system_1),
	    Qbinary);
}

Object Alist_of_system_file_class_descriptions = UNBOUND;

/* SYSTEM-VERSION-GREATER-P */
Object system_version_greater_p(system_version_1,system_version_2)
    Object system_version_1, system_version_2;
{
    Object minor_version_1, minor_version_2, temp, temp_1;

    x_note_fn_call(1,33);
    minor_version_1 = SECOND(system_version_1);
    minor_version_2 = SECOND(system_version_2);
    temp = FIRST(system_version_1);
    temp_1 = FIRST(system_version_2);
    temp_1 = NUM_GT(temp,temp_1) ? T : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	temp_1 = FIRST(system_version_1);
	temp = FIRST(system_version_2);
	if (NUM_EQ(temp_1,temp))
	    return VALUES_1(NUM_GT(minor_version_1,minor_version_2) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
}

/* SYSTEM-REVISION-GREATER-P */
Object system_revision_greater_p(system_version_1,system_version_2)
    Object system_version_1, system_version_2;
{
    Object temp, quality_1, revision_1, quality_2, revision_2;
    Object result;

    x_note_fn_call(1,34);
    temp = system_version_greater_p(system_version_1,system_version_2);
    if (temp)
	return VALUES_1(temp);
    else if ( !TRUEP(system_version_greater_p(system_version_2,
	    system_version_1))) {
	result = get_quality_and_revision_of_system_version(system_version_1);
	MVS_2(result,quality_1,revision_1);
	result = get_quality_and_revision_of_system_version(system_version_2);
	MVS_2(result,quality_2,revision_2);
	temp = NUM_GT(quality_1,quality_2) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (NUM_EQ(quality_1,quality_2))
	    return VALUES_1(NUM_GT(revision_1,revision_2) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qalpha_or_beta;      /* alpha-or-beta */

/* GET-QUALITY-AND-REVISION-OF-SYSTEM-VERSION */
Object get_quality_and_revision_of_system_version(system_version)
    Object system_version;
{
    Object revision_string_qm, quality, revision;
    Object result;

    x_note_fn_call(1,35);
    revision_string_qm = getf(CDDR(system_version),Qalpha_or_beta,_);
    quality = FIX((SI_Long)0L);
    revision = FIX((SI_Long)0L);
    if (STRINGP(revision_string_qm) || text_string_p(revision_string_qm)) {
	result = get_quality_and_revision_of_revision_string(revision_string_qm);
	MVS_2(result,quality,revision);
    }
    return VALUES_2(quality,revision);
}

static Object Qbrief_description;  /* brief-description */

static Object Qpatch_level;        /* patch-level */

/* WRITE-SYSTEM-VERSION */
Object write_system_version(system_version_qm)
    Object system_version_qm;
{
    Object major_number, minor_number, alpha_or_beta_qm, brief_description_qm;
    Object patch_level_qm;
    SI_Long tenths, hundredths;

    x_note_fn_call(1,36);
    major_number = FIRST(system_version_qm);
    if (major_number);
    else
	major_number = FIX((SI_Long)0L);
    minor_number = SECOND(system_version_qm);
    if (minor_number);
    else
	minor_number = FIX((SI_Long)0L);
    alpha_or_beta_qm = getf(CDDR(system_version_qm),Qalpha_or_beta,_);
    brief_description_qm = getf(CDDR(system_version_qm),Qbrief_description,_);
    patch_level_qm = getf(CDDR(system_version_qm),Qpatch_level,_);
    format((SI_Long)3L,T,"Version ~d.",major_number);
    tenths = IFIX(lfloor(minor_number,FIX((SI_Long)10L)));
    hundredths = IFIX(mod(minor_number,FIX((SI_Long)10L)));
    format((SI_Long)3L,T,"~d",FIX(tenths));
    if (hundredths != (SI_Long)0L)
	format((SI_Long)3L,T,"~d",FIX(hundredths));
    if (alpha_or_beta_qm) {
	if (patch_level_qm)
	    format((SI_Long)4L,T," ~a~c",alpha_or_beta_qm,
		    CODE_CHAR(add(patch_level_qm,FIX((SI_Long)96L))));
	else
	    format((SI_Long)3L,T," ~a",alpha_or_beta_qm);
    }
    if (brief_description_qm)
	return format((SI_Long)3L,T,"~a",brief_description_qm);
    else
	return VALUES_1(Nil);
}

/* WRITE-SYSTEM-VERSION-TO-STRING */
Object write_system_version_to_string(system_version)
    Object system_version;
{
    Object standard_output;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(1,37);
    SAVE_STACK();
    standard_output = make_string_output_stream();
    PUSH_SPECIAL_WITH_SYMBOL(Standard_output,Qstandard_output,standard_output,
	    0);
      if (PUSH_UNWIND_PROTECT(0)) {
	  write_system_version(system_version);
	  SAVE_VALUES(get_output_stream_string(Standard_output));
      }
      POP_UNWIND_PROTECT(0);
      lclose(1,Standard_output);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qsystem_version;     /* system-version */

/* SET-SYSTEM-VERSION */
Object set_system_version(system_1,system_version)
    Object system_1, system_version;
{
    x_note_fn_call(1,38);
    return set_get(system_1,Qsystem_version,system_version);
}

/* GET-SYSTEM-MAJOR-VERSION */
Object get_system_major_version(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(1,39);
    temp = get(system_1,Qsystem_version,_);
    return VALUES_1(FIRST(temp));
}

/* GET-SYSTEM-MINOR-VERSION */
Object get_system_minor_version(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(1,40);
    temp = get(system_1,Qsystem_version,_);
    return VALUES_1(SECOND(temp));
}

/* OPEN-EDITOR-STREAM-OR-BITSINK */
Object open_editor_stream_or_bitsink(namestring_1)
    Object namestring_1;
{
    Object temp;

    x_note_fn_call(1,41);
    temp = make_broadcast_stream(0);
    return VALUES_2(temp,Nil);
}

/* SUPPORTS-EDITOR-STREAM-P */
Object supports_editor_stream_p()
{
    x_note_fn_call(1,42);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "none" */

/* CHECK-LAST-BOOTSTRAP-MODE */
Object check_last_bootstrap_mode(pathname_for_distribution_binaries_qm,
	    pathname_for_non_distribution_binaries_qm)
    Object pathname_for_distribution_binaries_qm;
    Object pathname_for_non_distribution_binaries_qm;
{
    Object temp, temp_2, temp_3, temp_4;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(1,43);
    PUSH_SPECIAL_WITH_SYMBOL(Pathname_for_distribution_binaries_qm,Qpathname_for_distribution_binaries_qm,pathname_for_distribution_binaries_qm,
	    0);
      if (Last_bootstrap_mode_qm) {
	  temp = FIRST(Last_bootstrap_mode_qm);
	  temp_1 =  !EQUAL(Pathname_for_distribution_binaries_qm,temp);
	  if (temp_1);
	  else {
	      temp = SECOND(Last_bootstrap_mode_qm);
	      temp_1 =  !EQUAL(pathname_for_non_distribution_binaries_qm,temp);
	  }
	  if (temp_1) {
	      temp = FIRST(Last_bootstrap_mode_qm);
	      if (temp);
	      else
		  temp = string_constant_3;
	      temp_2 = SECOND(Last_bootstrap_mode_qm);
	      if (temp_2);
	      else
		  temp_2 = string_constant_3;
	      temp_3 = Pathname_for_distribution_binaries_qm;
	      if (temp_3);
	      else
		  temp_3 = string_constant_3;
	      temp_4 = pathname_for_non_distribution_binaries_qm;
	      if (temp_4);
	      else
		  temp_4 = string_constant_3;
	      cerror((SI_Long)6L,"Proceed in spite of great risk.",
		      "Attempt to compile in a different mode than before:\nBefore:\n  Distribution Pathname: ~s\n  Macro Pathname: ~s\nNow:\n  Distribution Pathname: ~s\n  Macro Pathname: ~s",
		      temp,temp_2,temp_3,temp_4);
	  }
      }
      Last_bootstrap_mode_qm = 
	      LIST_2(Pathname_for_distribution_binaries_qm,
	      pathname_for_non_distribution_binaries_qm);
      result = VALUES_1(Last_bootstrap_mode_qm);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_operating_system, Qg2_operating_system);

DEFINE_VARIABLE_WITH_SYMBOL(G2_machine_type, Qg2_machine_type);

DEFINE_VARIABLE_WITH_SYMBOL(Machine_model_var, Qmachine_model_var);

static Object Qaviion;             /* aviion */

static Object string_constant_4;   /* " Data General AViiON" */

static Object Qmotorola;           /* motorola */

static Object string_constant_5;   /* " Motorola 88000" */

static Object Qnext;               /* next */

static Object string_constant_6;   /* " NeXT" */

static Object Qsgi;                /* sgi */

static Object string_constant_7;   /* " Silicon Graphics" */

static Object Qsequent;            /* sequent */

static Object string_constant_8;   /* " Sequent" */

static Object Qdecstation;         /* decstation */

static Object string_constant_9;   /* " DECstation" */

static Object Qmasscomp;           /* masscomp */

static Object string_constant_10;  /* " Concurrent 6000s" */

static Object Qhp9000s300;         /* hp9000s300 */

static Object string_constant_11;  /* " HP9000/300s" */

static Object Qhp9000s400;         /* hp9000s400 */

static Object string_constant_12;  /* " HP9000/400s" */

static Object Qhp9000s700;         /* hp9000s700 */

static Object string_constant_13;  /* " PA-RISC HP-UX" */

static Object Qhp9000s800;         /* hp9000s800 */

static Object string_constant_14;  /* " HP9000/800s" */

static Object Qi386;               /* i386 */

static Object Qcompaq;             /* compaq */

static Object string_constant_15;  /* " '386" */

static Object Qrs6000;             /* rs6000 */

static Object string_constant_16;  /* " IBM POWERstation" */

static Object Qsun3;               /* sun3 */

static Object string_constant_17;  /* " Sun 3" */

static Object Qvms;                /* vms */

static Object string_constant_18;  /* " Vax VMS" */

static Object Qalphavms;           /* alphavms */

static Object string_constant_19;  /* " DEC Alpha AXP/OpenVMS" */

static Object Qsparcsol;           /* sparcsol */

static Object string_constant_20;  /* " Sun 4/SPARCstation Solaris" */

static Object Qintelsol;           /* intelsol */

static Object string_constant_21;  /* " x86 Solaris" */

static Object Qsun4;               /* sun4 */

static Object string_constant_22;  /* " Sun 4/SPARCstation" */

static Object Qharris;             /* harris */

static Object string_constant_23;  /* " Harris Night Hawk" */

static Object Qstratus;            /* stratus */

static Object string_constant_24;  /* " Stratus FTX" */

static Object Qnec;                /* nec */

static Object string_constant_25;  /* " NEC EWS4800 Series" */

static Object Qalphaosf;           /* alphaosf */

static Object string_constant_26;  /* " DEC OSF/1 AXP" */

static Object Qalphant;            /* alphant */

static Object string_constant_27;  /* " Alpha NT" */

static Object Qintelnt;            /* intelnt */

static Object string_constant_28;  /* " Windows" */

static Object Qdos;                /* dos */

static Object string_constant_29;  /* " MS Windows 3.1" */

static Object Qncr;                /* ncr */

static Object string_constant_30;  /* " NCR 386/486" */

static Object Qwindows95;          /* windows95 */

static Object string_constant_31;  /* " Windows 95/98" */

static Object Qlinux;              /* linux */

static Object string_constant_32;  /* " Linux" */

static Object Qmac;                /* mac */

static Object string_constant_33;  /* " Mac OS X" */

static Object Qhpia64;             /* hpia64 */

static Object string_constant_34;  /* " Itanium HP-UX" */

static Object string_constant_35;  /* " Experimental Port" */

/* MACHINE-MODEL */
Object machine_model()
{
    x_note_fn_call(1,44);
    if (Machine_model_var)
	return VALUES_1(Machine_model_var);
    else {
	if (EQ(G2_machine_type,Qaviion))
	    Machine_model_var = string_constant_4;
	else if (EQ(G2_machine_type,Qmotorola))
	    Machine_model_var = string_constant_5;
	else if (EQ(G2_machine_type,Qnext))
	    Machine_model_var = string_constant_6;
	else if (EQ(G2_machine_type,Qsgi))
	    Machine_model_var = string_constant_7;
	else if (EQ(G2_machine_type,Qsequent))
	    Machine_model_var = string_constant_8;
	else if (EQ(G2_machine_type,Qdecstation))
	    Machine_model_var = string_constant_9;
	else if (EQ(G2_machine_type,Qmasscomp))
	    Machine_model_var = string_constant_10;
	else if (EQ(G2_machine_type,Qhp9000s300))
	    Machine_model_var = string_constant_11;
	else if (EQ(G2_machine_type,Qhp9000s400))
	    Machine_model_var = string_constant_12;
	else if (EQ(G2_machine_type,Qhp9000s700))
	    Machine_model_var = string_constant_13;
	else if (EQ(G2_machine_type,Qhp9000s800))
	    Machine_model_var = string_constant_14;
	else if (EQ(G2_machine_type,Qi386) || EQ(G2_machine_type,Qcompaq))
	    Machine_model_var = string_constant_15;
	else if (EQ(G2_machine_type,Qrs6000))
	    Machine_model_var = string_constant_16;
	else if (EQ(G2_machine_type,Qsun3))
	    Machine_model_var = string_constant_17;
	else if (EQ(G2_machine_type,Qvms))
	    Machine_model_var = string_constant_18;
	else if (EQ(G2_machine_type,Qalphavms))
	    Machine_model_var = string_constant_19;
	else if (EQ(G2_machine_type,Qsparcsol))
	    Machine_model_var = string_constant_20;
	else if (EQ(G2_machine_type,Qintelsol))
	    Machine_model_var = string_constant_21;
	else if (EQ(G2_machine_type,Qsun4))
	    Machine_model_var = string_constant_22;
	else if (EQ(G2_machine_type,Qharris))
	    Machine_model_var = string_constant_23;
	else if (EQ(G2_machine_type,Qstratus))
	    Machine_model_var = string_constant_24;
	else if (EQ(G2_machine_type,Qnec))
	    Machine_model_var = string_constant_25;
	else if (EQ(G2_machine_type,Qalphaosf))
	    Machine_model_var = string_constant_26;
	else if (EQ(G2_machine_type,Qalphant))
	    Machine_model_var = string_constant_27;
	else if (EQ(G2_machine_type,Qintelnt))
	    Machine_model_var = string_constant_28;
	else if (EQ(G2_machine_type,Qdos))
	    Machine_model_var = string_constant_29;
	else if (EQ(G2_machine_type,Qncr))
	    Machine_model_var = string_constant_30;
	else if (EQ(G2_machine_type,Qwindows95))
	    Machine_model_var = string_constant_31;
	else if (EQ(G2_machine_type,Qlinux))
	    Machine_model_var = string_constant_32;
	else if (EQ(G2_machine_type,Qmac))
	    Machine_model_var = string_constant_33;
	else if (EQ(G2_machine_type,Qhpia64))
	    Machine_model_var = string_constant_34;
	else
	    Machine_model_var = string_constant_35;
	return VALUES_1(Machine_model_var);
    }
}

static Object Qsystem_lisp_source_files;  /* system-lisp-source-files */

static Object Qsystem_pathname;    /* system-pathname */

/* MAKE-SYSTEM-PATHNAME */
Object make_system_pathname varargs_1(int, n)
{
    Object system_name, file_symbol_or_string, overriding_file_type_qm;
    Object version_qm;
    Object override_pathname_qm, file_class_qm, local_or_binary;
    Object gensymed_symbol, system_1, internable_string, temp, file_symbol;
    Object namestring_1, defaults, name, type, system_pathname, temp_1, temp_2;
    Object temp_3, temp_4;
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,45);
    INIT_ARGS_nonrelocating();
    system_name = REQUIRED_ARG_nonrelocating();
    file_symbol_or_string = REQUIRED_ARG_nonrelocating();
    overriding_file_type_qm = REQUIRED_ARG_nonrelocating();
    version_qm = REQUIRED_ARG_nonrelocating();
    override_pathname_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    file_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Qsystem_lisp_source_files;
    local_or_binary = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Qlocal;
    END_ARGS_nonrelocating();
    gensymed_symbol = system_name;
    if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
	    Ab_package_1))
	system_1 = gensymed_symbol;
    else {
	if (SYMBOLP(gensymed_symbol))
	    internable_string = SYMBOL_NAME(gensymed_symbol);
	else if (STRINGP(gensymed_symbol))
	    internable_string = gensymed_symbol;
	else if (NUMBERP(gensymed_symbol))
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	else
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	temp = intern(internable_string,Ab_package_1);
	system_1 = temp;
    }
    if (SYMBOLP(file_symbol_or_string))
	file_symbol = file_symbol_or_string;
    else {
	temp = string_upcase(1,file_symbol_or_string);
	file_symbol = intern(temp,find_package(Qab));
    }
    if (EQ(local_or_binary,Qlocal))
	namestring_1 = string_for_local_file_namestring(file_symbol,
		file_class_qm,system_1);
    else if (EQ(local_or_binary,Qbinary))
	namestring_1 = string_for_binary_file_namestring(file_symbol,
		file_class_qm,system_1);
    else
	namestring_1 = Qnil;
    defaults = file_class_qm && namestring_1 &&  !EQUAL(namestring_1,
	    string_constant_1) ? pathname(namestring_1) : get(system_1,
	    Qsystem_pathname,_);
    if (EQ(file_symbol,Kwild))
	name = Kwild;
    else if (file_class_qm) {
	if (EQ(local_or_binary,Qlocal))
	    name = get_default_local_pathname_name(file_symbol,
		    file_class_qm,system_1);
	else if (EQ(local_or_binary,Qbinary))
	    name = get_default_binary_pathname_name(file_symbol,
		    file_class_qm,system_1);
	else
	    name = Qnil;
    }
    else
	name = string_downcase(1,file_symbol);
    if (EQUAL(overriding_file_type_qm,Kwild))
	type = Kwild;
    else if ( !TRUEP(overriding_file_type_qm) && file_class_qm) {
	if (EQ(local_or_binary,Qlocal))
	    type = get_default_local_file_type(file_symbol,file_class_qm,
		    system_1);
	else if (EQ(local_or_binary,Qbinary))
	    type = get_default_binary_file_type(file_symbol,file_class_qm,
		    system_1);
	else
	    type = Qnil;
    }
    else
	type = string_downcase(1,overriding_file_type_qm);
    system_pathname = version_qm && SIXTH(Bootstrap_information) ? 
	    make_pathname(8,Kdefaults,defaults,Kname,name,Ktype,type,
	    Kversion,version_qm) : make_pathname(6,Kdefaults,defaults,
	    Kname,name,Ktype,type);
    if (override_pathname_qm) {
	temp_1 = pathname_name(system_pathname);
	if (temp_1);
	else
	    temp_1 =  !EQ(pathname_name(override_pathname_qm),Kwild) ? 
		    pathname_name(override_pathname_qm) : Qnil;
	temp_2 = pathname_type(system_pathname);
	if (temp_2);
	else
	    temp_2 =  !EQ(pathname_type(override_pathname_qm),Kwild) ? 
		    pathname_type(override_pathname_qm) : Qnil;
	temp_3 = pathname_directory(override_pathname_qm);
	if (temp_3);
	else
	    temp_3 = pathname_directory(system_pathname);
	temp_4 = PATHNAME_HOST(override_pathname_qm);
	if (temp_4);
	else
	    temp_4 = PATHNAME_HOST(system_pathname);
	temp = pathname_version(override_pathname_qm);
	temp = NUMBERP(temp) ? pathname_version(override_pathname_qm) : Nil;
	if (temp);
	else
	    temp = pathname_version(system_pathname);
	return make_pathname(12,Kdefaults,override_pathname_qm,Kname,
		temp_1,Ktype,temp_2,Kdirectory,temp_3,Khost,temp_4,
		Kversion,temp);
    }
    else
	return VALUES_1(system_pathname);
}

static Object Qsystem_c_files;     /* system-c-files */

/* MAKE-SYSTEM-C-FILE-OBJECT-NAMESTRING */
Object make_system_c_file_object_namestring varargs_1(int, n)
{
    Object file_symbol_or_string;
    Object system_name, temp, gensymed_symbol, temp_1, internable_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,46);
    INIT_ARGS_nonrelocating();
    file_symbol_or_string = REQUIRED_ARG_nonrelocating();
    system_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(file_symbol_or_string))
	temp = file_symbol_or_string;
    else {
	temp = string_upcase(1,file_symbol_or_string);
	temp = intern(temp,find_package(Qab));
    }
    gensymed_symbol = system_name;
    if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
	    Ab_package_1))
	temp_1 = gensymed_symbol;
    else {
	if (SYMBOLP(gensymed_symbol))
	    internable_string = SYMBOL_NAME(gensymed_symbol);
	else if (STRINGP(gensymed_symbol))
	    internable_string = gensymed_symbol;
	else if (NUMBERP(gensymed_symbol))
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	else
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	temp_1 = intern(internable_string,Ab_package_1);
    }
    if (temp_1);
    else
	temp_1 = Qab;
    return string_for_binary_file_namestring(temp,Qsystem_c_files,temp_1);
}

static Object Qsystem_lisp_binary_type;  /* system-lisp-binary-type */

static Object Qsource;             /* source */

static Object Qsystem_lisp_source_type;  /* system-lisp-source-type */

static Object Qkb;                 /* kb */

static Object Qsystem_kb_type;     /* system-kb-type */

static Object Qkl;                 /* kl */

static Object Qsystem_kl_type;     /* system-kl-type */

static Object Qc;                  /* c */

static Object Qh;                  /* h */

/* MAKE-MODULE-FILENAME */
Object make_module_filename varargs_1(int, n)
{
    Object module, system_1;
    Object pathname_type_1, override_pathname_qm, gensymed_symbol, type;
    Object internable_string, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,47);
    INIT_ARGS_nonrelocating();
    module = REQUIRED_ARG_nonrelocating();
    system_1 = REQUIRED_ARG_nonrelocating();
    pathname_type_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Qbinary;
    override_pathname_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = pathname_type_1;
    if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
	    Ab_package_1))
	type = gensymed_symbol;
    else {
	if (SYMBOLP(gensymed_symbol))
	    internable_string = SYMBOL_NAME(gensymed_symbol);
	else if (STRINGP(gensymed_symbol))
	    internable_string = gensymed_symbol;
	else if (NUMBERP(gensymed_symbol))
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	else
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	temp = intern(internable_string,Ab_package_1);
	type = temp;
    }
    gensymed_symbol = pathname_type_1;
    if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
	    Ab_package_1))
	temp = gensymed_symbol;
    else {
	if (SYMBOLP(gensymed_symbol))
	    internable_string = SYMBOL_NAME(gensymed_symbol);
	else if (STRINGP(gensymed_symbol))
	    internable_string = gensymed_symbol;
	else if (NUMBERP(gensymed_symbol))
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	else
	    internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
		    gensymed_symbol);
	temp = intern(internable_string,Ab_package_1);
    }
    if (EQ(temp,Qbinary))
	temp = get(system_1,Qsystem_lisp_binary_type,_);
    else if (EQ(temp,Qsource))
	temp = get(system_1,Qsystem_lisp_source_type,_);
    else if (EQ(temp,Qkb))
	temp = get(system_1,Qsystem_kb_type,_);
    else if (EQ(temp,Qkl))
	temp = get(system_1,Qsystem_kl_type,_);
    else if (EQ(temp,Qc))
	temp = Qc;
    else if (EQ(temp,Qh))
	temp = Qh;
    else
	temp = error((SI_Long)2L,"Bad type ~a in make-module-filename",type);
    return make_system_pathname(5,system_1,module,temp,Knewest,
	    override_pathname_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_load_modules_p, Qdo_not_load_modules_p);

DEFINE_VARIABLE_WITH_SYMBOL(Making_distribution_system_qm, Qmaking_distribution_system_qm);

/* DIRECTORY-FOR-BOOTSTRAP */
Object directory_for_bootstrap(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(1,48);
    return directory(1,pathname_1);
}

/* NEW-DIRECTORY-FOR-BOOTSTRAP */
Object new_directory_for_bootstrap(pathname_1)
    Object pathname_1;
{
    Object list0, result_1, last_1, temp, new_last;

    x_note_fn_call(1,49);
    list0 = directory(1,pathname_1);
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp = LIST_1(CAR(list0));
	new_last = CONS(temp,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    return VALUES_1(result_1);
}

static Object Qlaunch_function_qm;  /* launch-function? */

/* LAUNCH-SYSTEM */
Object launch_system(system_1)
    Object system_1;
{
    Object launch_function_qm;

    x_note_fn_call(1,50);
    launch_function_qm = get(system_1,Qlaunch_function_qm,_);
    if (launch_function_qm)
	return FUNCALL_0(launch_function_qm);
    else
	return error((SI_Long)2L,"Unable to launch system ~a.",system_1);
}

static Object Kcreation_date;      /* :creation-date */

/* GET-FILE-WRITE-DATE-FROM-DIRECTORY-LIST */
Object get_file_write_date_from_directory_list(goal_truename,directory_list)
    Object goal_truename, directory_list;
{
    Object tail, directory_entry, truename_qm, temp;

    x_note_fn_call(1,51);
    tail = directory_list;
    directory_entry = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	directory_entry = CAR(tail);
	truename_qm = FIRST(directory_entry);
	if (EQ(truename_qm,goal_truename)) {
	    temp = getf(CDR(directory_entry),Kcreation_date,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return file_write_date(goal_truename);
	}
    }
    return VALUES_1(Nil);
}

/* ADD-TO-DIRECTORY-LIST-FOR-BOOTSTRAPPING */
Object add_to_directory_list_for_bootstrapping(truename_1,
	    directory_list_special_variable)
    Object truename_1, directory_list_special_variable;
{
    Object temp;

    x_note_fn_call(1,52);
    temp = new_directory_for_bootstrap(truename_1);
    return set(directory_list_special_variable,nconc2(temp,
	    SYMBOL_VALUE(directory_list_special_variable)));
}

/* OLDER-OR-SAME-VERSION-P */
Object older_or_same_version_p varargs_1(int, n)
{
    Object pathname_1, pathname_2;
    Object directory_list_1_qm, directory_list_2_qm, version_1, version_2;
    Object temp_1;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(1,53);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    pathname_2 = REQUIRED_ARG_nonrelocating();
    directory_list_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    directory_list_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    version_1 = Nil;
    version_2 = Nil;
    temp = TRUEP(use_dates_instead_of_versions_p());
    if (temp);
    else {
	temp_1 = pathname_version(pathname_1);
	temp =  !NUMBERP(temp_1);
    }
    if (temp);
    else {
	temp_1 = pathname_version(pathname_2);
	temp =  !NUMBERP(temp_1);
    }
    if (temp) {
	version_1 = directory_list_1_qm ? 
		get_file_write_date_from_directory_list(pathname_1,
		directory_list_1_qm) : file_write_date(pathname_1);
	version_2 = directory_list_2_qm ? 
		get_file_write_date_from_directory_list(pathname_2,
		directory_list_2_qm) : file_write_date(pathname_2);
    }
    else {
	version_1 = pathname_version(pathname_1);
	version_2 = pathname_version(pathname_2);
    }
    if (NUMBERP(version_1) && NUMBERP(version_2))
	return VALUES_1(NUM_LE(version_1,version_2) ? T : Nil);
    else
	return VALUES_1(EQL(version_1,version_2) ? T : Nil);
}

Object All_modules_of_all_systems = UNBOUND;

/* NORMALIZE-MODULE-NAME-OR-DESCRIPTION */
Object normalize_module_name_or_description(module_name_or_description)
    Object module_name_or_description;
{
    Object gensymed_symbol, temp, internable_string;

    x_note_fn_call(1,54);
    if (CONSP(module_name_or_description)) {
	gensymed_symbol = CAR(module_name_or_description);
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		Ab_package_1))
	    temp = gensymed_symbol;
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else if (NUMBERP(gensymed_symbol))
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    else
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    temp = intern(internable_string,Ab_package_1);
	}
	M_CAR(module_name_or_description) = temp;
	return VALUES_1(module_name_or_description);
    }
    else {
	gensymed_symbol = module_name_or_description;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		Ab_package_1))
	    return VALUES_1(gensymed_symbol);
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else if (NUMBERP(gensymed_symbol))
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    else
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    temp = intern(internable_string,Ab_package_1);
	    return VALUES_1(temp);
	}
    }
}

static Object list_constant;       /* # */

static Object Qdestination;        /* destination */

static Object Qdistribute;         /* distribute */

static Object Qbinary_directory;   /* binary-directory */

static Object Qcommand_line;       /* command-line */

static Object Kdefault_dst_directory;  /* :default-dst-directory */

static Object Kdefault_macro_directory;  /* :default-macro-directory */

static Object Kdefault_development_binary_directory;  /* :default-development-binary-directory */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

/* CHECK-BOOT-SYSTEM-OPTIONS */
Object check_boot_system_options(system_1,options)
    Object system_1, options;
{
    Object entry, temp_1, entry_old_value;
    char temp;

    x_note_fn_call(1,55);
    for ( entry = options; ! !TRUEP(entry); entry = CDR(entry))
	if (member(4,CAR(entry),list_constant,Ktest,
		SYMBOL_FUNCTION(Qstring_or_symbol_equal)) && T || member(4,
		CAR(entry),get(system_1,Qall_optional_modules,_),Ktest,
		SYMBOL_FUNCTION(Qstring_or_symbol_equal)));
	else {
	    temp = TRUEP(string_or_symbol_equal(CAR(entry),Qdestination));
	    if (temp);
	    else
		temp = TRUEP(string_or_symbol_equal(CAR(entry),Qdistribute));
	    if (temp);
	    else
		temp = TRUEP(string_or_symbol_equal(CAR(entry),
			Qbinary_directory));
	    if (temp);
	    else {
		temp_1 = CAR(entry);
		temp = STRINGP(temp_1);
		if (temp);
		else
		    temp = TRUEP(string_or_symbol_equal(CAR(entry),
			    Qcommand_line));
	    }
	    if (temp) {
		temp_1 = CAR(entry);
		if ( !STRINGP(temp_1)) {
		    entry_old_value = entry;
		    entry = REST(entry_old_value);
		}
		temp_1 = CAR(entry);
		temp = PATHNAMEP(temp_1);
		if (temp);
		else {
		    temp_1 = CAR(entry);
		    temp = STRINGP(temp_1);
		}
		if (temp);
		else {
		    temp_1 = CAR(entry);
		    temp = EQ(temp_1,Kdefault_dst_directory) || EQ(temp_1,
			    Kdefault_macro_directory) || EQ(temp_1,
			    Kdefault_development_binary_directory) ? 
			    TRUEP(T) : TRUEP(Nil);
		}
		if ( !temp)
		    cerror((SI_Long)3L,"Continue anyway",
			    "No destination pathname: ~a",CAR(entry));
	    }
	    else if (member(4,CAR(entry),list_constant_1,Ktest,
		    SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
		entry_old_value = entry;
		entry = REST(entry_old_value);
		if (member(4,CAR(entry),list_constant_2,Ktest,
			SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
		    entry_old_value = entry;
		    entry = REST(entry_old_value);
		    if ( !TRUEP(member(4,CAR(entry),get(system_1,
			    Qsystem_lisp_source_files,_),Ktest,
			    SYMBOL_FUNCTION(Qstring_or_symbol_equal)))) {
			cerror((SI_Long)3L,"Continue anyway",
				"Not a system module, AFTER, or BEFORE: ~a",
				CAR(entry));
			entry_old_value = entry;
			entry = REST(entry_old_value);
		    }
		}
	    }
	    else if (member(4,CAR(entry),list_constant_3,Ktest,
		    SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
		entry_old_value = entry;
		entry = REST(entry_old_value);
		entry_old_value = entry;
		entry = REST(entry_old_value);
	    }
	    else
		cerror((SI_Long)3L,"Continue anyway","Unknown Option: ~a",
			CAR(entry));
	}
    return VALUES_1(Nil);
}

static Object string_constant_36;  /* "Illegal 'distribute, 'destination, or 'binary-directory flag ~
				    *                ~a.  The legal flags are:   :default-dst-directory, ~
				    *                :default-macro-directory, and ~
				    *                :default-development-binary-directory."
				    */

/* TRANSLATE-BINARY-DIRECTORY-OR-DEFAULT */
Object translate_binary_directory_or_default(system_1,binary_directory_or_flag)
    Object system_1, binary_directory_or_flag;
{
    Object temp;

    x_note_fn_call(1,56);
    if (EQUAL(binary_directory_or_flag,Kdefault_dst_directory)) {
	if (eval_feature(Kchestnut)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else if (eval_feature(Kchestnut_3)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else {
	    temp = get(system_1,Qlocal_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_dst_directory,_);
	}
    }
    else if (EQUAL(binary_directory_or_flag,Kdefault_macro_directory)) {
	temp = get(system_1,Qlocal_macro_directory,_);
	if (temp)
	    return VALUES_1(temp);
	else
	    return get(Qab,Qlocal_macro_directory,_);
    }
    else if (STRINGP(binary_directory_or_flag) || 
	    PATHNAMEP(binary_directory_or_flag) ||  
	    !TRUEP(binary_directory_or_flag))
	return VALUES_1(binary_directory_or_flag);
    else
	return errorn(2,string_constant_36,binary_directory_or_flag);
}

/* EXTRACT-PATHNAME-FOR-DISTRIBUTION-BINARIES */
Object extract_pathname_for_distribution_binaries(system_1,options)
    Object system_1, options;
{
    Object distribute_list, distribute_pathname, temp;

    x_note_fn_call(1,57);
    distribute_list = member(4,Qdistribute,options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
    distribute_pathname = CADR(distribute_list);
    translate_binary_directory_or_default(system_1,distribute_pathname);
    if (distribute_list) {
	if (STRINGP(distribute_pathname) || PATHNAMEP(distribute_pathname))
	    return VALUES_1(distribute_pathname);
	else if (eval_feature(Kchestnut)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else if (eval_feature(Kchestnut_3)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else {
	    temp = get(system_1,Qlocal_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_dst_directory,_);
	}
    }
    else
	return VALUES_1(Nil);
}

/* EXTRACT-PATHNAME-FOR-NON-DISTRIBUTION-BINARIES */
Object extract_pathname_for_non_distribution_binaries(system_1,compile_p,
	    options)
    Object system_1, compile_p, options;
{
    Object destination_list, binary_directory_list, destination_qm;
    Object binary_directory_qm, temp;

    x_note_fn_call(1,58);
    destination_list = member(4,Qdestination,options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
    binary_directory_list = member(4,Qbinary_directory,options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal));
    destination_qm = CADR(destination_list);
    binary_directory_qm = CADR(binary_directory_list);
    if (destination_list && binary_directory_list &&  
	    !EQUAL(destination_qm,binary_directory_qm))
	cerror((SI_Long)4L,
		"Continue, using the binary-destination directory.",
		"Equivalent options \'destination and \'binary-directory-list have been specified but the values are not the same (~S amd ~S).",
		destination_qm,binary_directory_qm);
    if (destination_qm &&  !TRUEP(binary_directory_qm))
	binary_directory_qm = destination_qm;
    if (binary_directory_qm)
	binary_directory_qm = 
		translate_binary_directory_or_default(system_1,
		binary_directory_qm);
    if (STRINGP(binary_directory_qm) || PATHNAMEP(binary_directory_qm))
	return VALUES_1(binary_directory_qm);
    else if (member(4,Qdistribute,options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
	if (compile_p) {
	    temp = get(system_1,Qlocal_macro_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_macro_directory,_);
	}
	else if (eval_feature(Kchestnut)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else if (eval_feature(Kchestnut_3)) {
	    temp = get(system_1,Qlocal_chestnut_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_chestnut_dst_directory,_);
	}
	else {
	    temp = get(system_1,Qlocal_dst_directory,_);
	    if (temp)
		return VALUES_1(temp);
	    else
		return get(Qab,Qlocal_dst_directory,_);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qno_optional_modules;  /* no-optional-modules */

/* EXTRACT-LIST-OF-OPTIONAL-MODULES */
Object extract_list_of_optional_modules(system_1,user_options)
    Object system_1, user_options;
{
    Object all_optional_modules, optional_modules, tail, file_symbol;
    Object pushnew_arg;

    x_note_fn_call(1,59);
    all_optional_modules = get(system_1,Qall_optional_modules,_);
    optional_modules = Nil;
    if (member(4,Qall_optional_modules,user_options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
	if (member(4,Qno_optional_modules,user_options,Ktest,
		SYMBOL_FUNCTION(Qstring_or_symbol_equal)))
	    cerror((SI_Long)2L,"Continue without all optional modules.",
		    "You specified both \'no-optional-modules and all-optional-modules.");
	else {
	    tail = all_optional_modules;
	    file_symbol = Nil;
	    for ( ; !ENDP(tail); tail = CDR(tail)) {
		file_symbol = CAR(tail);
		pushnew_arg = file_symbol;
		optional_modules = adjoin(2,pushnew_arg,optional_modules);
	    }
	}
    }
    tail = all_optional_modules;
    file_symbol = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	file_symbol = CAR(tail);
	if (eval_feature(file_symbol) || member(4,file_symbol,user_options,
		Ktest,SYMBOL_FUNCTION(Qstring_or_symbol_equal))) {
	    pushnew_arg = file_symbol;
	    optional_modules = adjoin(2,pushnew_arg,optional_modules);
	}
	if (member(4,format((SI_Long)3L,Nil,"NO-~a",
		SYMBOL_NAME(file_symbol)),user_options,Ktest,
		SYMBOL_FUNCTION(Qstring_or_symbol_equal)))
	    optional_modules = ldelete(4,file_symbol,optional_modules,
		    Ktest,SYMBOL_FUNCTION(Qstring_or_symbol_equal));
    }
    if (member(4,Qno_optional_modules,user_options,Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal)))
	optional_modules = Nil;
    set_get(system_1,Qoptional_modules,optional_modules);
    return VALUES_1(optional_modules);
}

/* INSTALL-ALL-FILE-PROPERTIES-FROM-ALIST */
Object install_all_file_properties_from_alist(file_symbol,file_class,
	    system_1,file_properties_alist)
    Object file_symbol, file_class, system_1, file_properties_alist;
{
    Object property_name, property_value, tail, property_description;

    x_note_fn_call(1,60);
    property_name = Nil;
    property_value = Nil;
    tail = file_properties_alist;
    property_description = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	property_description = CAR(tail);
	property_name = FIRST(property_description);
	property_value = SECOND(property_description);
	set_file_property(file_symbol,file_class,system_1,property_name,
		property_value);
    }
    return VALUES_1(Nil);
}

static Object Kinclude_test_for_compile;  /* :include-test-for-compile */

static Object Kinclude_test_for_update;  /* :include-test-for-update */

static Object list_constant_4;     /* # */

/* INSTALL-ALL-FILE-PROPERTIES-FROM-PLIST */
Object install_all_file_properties_from_plist(file_symbol,file_class,
	    system_1,file_properties_plist)
    Object file_symbol, file_class, system_1, file_properties_plist;
{
    Object property_name, property_value, rest_of_plist;

    x_note_fn_call(1,61);
    property_name = Nil;
    property_value = Nil;
    for ( rest_of_plist = file_properties_plist; ! !TRUEP(rest_of_plist); 
	    rest_of_plist = CDDR(rest_of_plist)) {
	property_name = CAR(rest_of_plist);
	property_value = CADR(rest_of_plist);
	if ( !TRUEP(property_value) && (EQ(property_name,
		Kinclude_test_for_compile) || EQ(property_name,
		Kinclude_test_for_load) || EQ(property_name,
		Kinclude_test_for_update) || EQ(property_name,
		Koverriding_include_test)) && T)
	    property_value = list_constant_4;
	set_file_property(file_symbol,file_class,system_1,property_name,
		property_value);
    }
    return VALUES_1(Nil);
}

/* MAKE-AN-ALIST-OF-FILE-PROPERTY-DEFAULTS */
Object make_an_alist_of_file_property_defaults(fcd_alist_of_file_property_defaults)
    Object fcd_alist_of_file_property_defaults;
{
    Object file_property_defaults_alist, property_1, base_default, override;
    Object default_1, tail, property_description, push_arg;

    x_note_fn_call(1,62);
    file_property_defaults_alist = Nil;
    property_1 = Nil;
    base_default = Nil;
    override = Nil;
    default_1 = Nil;
    tail = Alist_of_file_property_base_defaults;
    property_description = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	property_description = CAR(tail);
	property_1 = FIRST(property_description);
	base_default = SECOND(property_description);
	override = assoc_eql(property_1,fcd_alist_of_file_property_defaults);
	if (override)
	    default_1 = SECOND(override);
	else
	    default_1 = base_default;
	if (default_1) {
	    push_arg = LIST_2(property_1,default_1);
	    file_property_defaults_alist = CONS(push_arg,
		    file_property_defaults_alist);
	}
    }
    return VALUES_1(file_property_defaults_alist);
}

/* INSTALL-FILE-PROPERTIES-FOR-FILE-NAME-OR-DESCRIPTION */
Object install_file_properties_for_file_name_or_description(file_name_or_description,
	    file_class,system_1,file_property_defaults_alist)
    Object file_name_or_description, file_class, system_1;
    Object file_property_defaults_alist;
{
    Object file_symbol, plist_of_properties;

    x_note_fn_call(1,63);
    if (CONSP(file_name_or_description)) {
	file_symbol = CAR(file_name_or_description);
	plist_of_properties = CDR(file_name_or_description);
	install_all_file_properties_from_alist(file_symbol,file_class,
		system_1,file_property_defaults_alist);
	install_all_file_properties_from_plist(file_symbol,file_class,
		system_1,plist_of_properties);
	return VALUES_1(file_symbol);
    }
    else {
	install_all_file_properties_from_alist(file_name_or_description,
		file_class,system_1,file_property_defaults_alist);
	return VALUES_1(file_name_or_description);
    }
}

static Object Qlisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

/* INSTALL-FILE-PROPERTIES-FOR-SYSTEM */
Object install_file_properties_for_system(file_names_or_descriptions_qm,
	    file_class,system_1,fcd_alist_of_file_property_defaults)
    Object file_names_or_descriptions_qm, file_class, system_1;
    Object fcd_alist_of_file_property_defaults;
{
    Object file_symbol, list_of_file_symbols, file_property_defaults_alist;
    Object tail, file_name_or_description, push_arg, temp, get_new_value;

    x_note_fn_call(1,64);
    if (file_names_or_descriptions_qm) {
	file_symbol = Nil;
	list_of_file_symbols = Nil;
	file_property_defaults_alist = 
		make_an_alist_of_file_property_defaults(fcd_alist_of_file_property_defaults);
	tail = file_names_or_descriptions_qm;
	file_name_or_description = Nil;
	for ( ; !ENDP(tail); tail = CDR(tail)) {
	    file_name_or_description = CAR(tail);
	    file_symbol = 
		    install_file_properties_for_file_name_or_description(file_name_or_description,
		    file_class,system_1,file_property_defaults_alist);
	    if (eval_feature(get_default_include_test(file_symbol,
		    file_class,system_1,Kinclude_test_for_load))) {
		push_arg = file_symbol;
		temp = get(system_1,Qlisp_modules_to_be_loaded,Nil);
		get_new_value = CONS(push_arg,temp);
		set_get(system_1,Qlisp_modules_to_be_loaded,get_new_value);
	    }
	    push_arg = file_symbol;
	    list_of_file_symbols = CONS(push_arg,list_of_file_symbols);
	}
	return nreverse(list_of_file_symbols);
    }
    else
	return VALUES_1(Nil);
}

/* STABLE-LIST-UNION */
Object stable_list_union(list_1,list_2)
    Object list_1, list_2;
{
    Object result_1;

    x_note_fn_call(1,65);
    result_1 = append2(list_1,list_2);
    return remove_duplicates(1,result_1);
}

static Object Kdevelopment;        /* :development */

static Object Kstandard_module_index;  /* :standard-module-index */

static Object Qalias;              /* alias */

static Object Qnicknames;          /* nicknames */

static Object Qsystem_package_name;  /* system-package-name */

static Object Qlisp_source_type;   /* lisp-source-type */

static Object Qlisp_binary_type;   /* lisp-binary-type */

static Object Qkb_type;            /* kb-type */

static Object Qkl_type;            /* kl-type */

static Object Qsystems_to_share_binary_files_with;  /* systems-to-share-binary-files-with */

static Object Qsystem_is_windowless_p;  /* system-is-windowless-p */

static Object Qsystem_alias;       /* system-alias */

/* DECLARE-SYSTEM-1 */
Object declare_system_1 varargs_1(int, n)
{
    Object system_1, file_names_or_descriptions;
    Object options, previous_module_index_qm, tail, module_description, module;
    Object module_index_qm, alias, nicknames, system_pathname;
    Object system_package_name, lisp_source_type, lisp_binary_type, kb_type;
    Object kl_type, systems_to_share_binary_files_with_qm;
    Object system_is_windowless_p, nickname, gensymed_symbol, temp;
    Object internable_string, file_class, file_class_indicator;
    Object file_class_module_property_defaults, file_class_description, list0;
    Object result_1, last_1, new_last, get_new_value;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(1,66);
    SAVE_STACK();
    INIT_ARGS();
    system_1 = REQUIRED_ARG();
    file_names_or_descriptions = REQUIRED_ARG();
    SAVE_ARGS();
    options = REST_ARG();
    if (member_eql(Kdevelopment,Features)) {
	previous_module_index_qm = FIX((SI_Long)0L);
	tail = file_names_or_descriptions;
	module_description = Nil;
	for ( ; !ENDP(tail); tail = CDR(tail)) {
	    module_description = CAR(tail);
	    module = SYMBOLP(module_description) ? module_description : 
		    FIRST(module_description);
	    module_index_qm = get(module,Kstandard_module_index,_);
	    if ( !TRUEP(module_index_qm))
		format((SI_Long)3L,T,
			"~&The module ~S unknown, see def-all-system-modules.",
			module);
	    if (previous_module_index_qm && module_index_qm &&  
		    !FIXNUM_LT(previous_module_index_qm,module_index_qm))
		format((SI_Long)3L,T,
			"~&Load order must be consistent across all systems.  The module ~S appears out of canonical order, see def-all-system-modules",
			module);
	    previous_module_index_qm = module_index_qm;
	}
    }
    alias = getf(options,Qalias,_);
    if (alias);
    else
	alias = Nil;
    nicknames = getf(options,Qnicknames,_);
    if (nicknames);
    else
	nicknames = Nil;
    system_pathname = getf(options,Qsystem_pathname,_);
    if (system_pathname);
    else
	system_pathname = Nil;
    system_package_name = getf(options,Qsystem_package_name,_);
    if (system_package_name);
    else
	system_package_name = system_1;
    lisp_source_type = getf(options,Qlisp_source_type,_);
    if (lisp_source_type);
    else
	lisp_source_type = SECOND(Bootstrap_information);
    lisp_binary_type = getf(options,Qlisp_binary_type,_);
    if (lisp_binary_type);
    else
	lisp_binary_type = FIRST(Bootstrap_information);
    kb_type = getf(options,Qkb_type,_);
    if (kb_type);
    else
	kb_type = THIRD(Bootstrap_information);
    kl_type = getf(options,Qkl_type,_);
    if (kl_type);
    else
	kl_type = FOURTH(Bootstrap_information);
    systems_to_share_binary_files_with_qm = getf(options,
	    Qsystems_to_share_binary_files_with,_);
    system_is_windowless_p = getf(options,Qsystem_is_windowless_p,_);
    system_pathname = system_pathname ? merge_pathnames(system_pathname,
	    Ab_system_pathname,_) : Ab_system_pathname;
    set_get(system_1,Qsystem_alias,alias);
    set_get(system_1,Qsystems_to_share_binary_files_with,
	    systems_to_share_binary_files_with_qm);
    tail = nicknames;
    nickname = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	nickname = CAR(tail);
	gensymed_symbol = nickname;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		Ab_package_1))
	    temp = gensymed_symbol;
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else if (NUMBERP(gensymed_symbol))
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    else
		internable_string = format((SI_Long)3L,Nil,"~:@(~a~)",
			gensymed_symbol);
	    temp = intern(internable_string,Ab_package_1);
	}
	set_get(temp,Qreal_system_name,system_1);
    }
    file_class = Nil;
    file_class_indicator = Nil;
    file_class_module_property_defaults = Nil;
    tail = Alist_of_system_file_class_descriptions;
    file_class_description = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	file_class_description = CAR(tail);
	file_class = FIRST(file_class_description);
	file_class_indicator = SECOND(file_class_description);
	file_class_module_property_defaults = THIRD(file_class_description);
	list0 = getf(options,file_class,_);
	result_1 = Nil;
	last_1 = Nil;
	for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	    temp = normalize_module_name_or_description(CAR(list0));
	    new_last = CONS(temp,Nil);
	    if (result_1)
		M_CDR(last_1) = new_last;
	    else
		result_1 = new_last;
	    last_1 = new_last;
	}
	temp = result_1;
	get_new_value = install_file_properties_for_system(temp,file_class,
		system_1,file_class_module_property_defaults);
	set_get(system_1,file_class_indicator,get_new_value);
    }
    set_get(system_1,Qlisp_modules_to_be_loaded,Nil);
    file_class = Qsystem_lisp_source_files;
    file_class_description = assoc_eql(file_class,
	    Alist_of_system_file_class_descriptions);
    file_class_indicator = SECOND(file_class_description);
    file_class_module_property_defaults = THIRD(file_class_description);
    temp = get(system_1,file_class_indicator,_);
    get_new_value = stable_list_union(temp,
	    install_file_properties_for_system(file_names_or_descriptions,
	    file_class,system_1,file_class_module_property_defaults));
    set_get(system_1,file_class_indicator,get_new_value);
    get_new_value = nreverse(get(system_1,Qlisp_modules_to_be_loaded,_));
    set_get(system_1,Qlisp_modules_to_be_loaded,get_new_value);
    set_get(system_1,Qsystem_lisp_source_type,lisp_source_type);
    set_get(system_1,Qsystem_lisp_binary_type,lisp_binary_type);
    set_get(system_1,Qsystem_kb_type,kb_type);
    set_get(system_1,Qsystem_kl_type,kl_type);
    set_get(system_1,Qsystem_pathname,system_pathname);
    set_get(system_1,Qsystem_package_name,system_package_name);
    result = set_get(system_1,Qsystem_is_windowless_p,system_is_windowless_p);
    RESTORE_STACK();
    return result;
}

void bootstrap_INIT()
{
    Object temp, temp_1, get_new_value;
    SI_Long platform_code;
    Object AB_package, list_constant_6, Qbefore, Qafter, Qto, Qfrom, Qlogfile;
    Object Qno_autolog, Qno_delete, Qno_make, Qanalyze_calls, Qprepare_only;
    Object Qmacros_only, Qsilent, Qverbose, Qno_gspan, Qno_gfi, Qno_gsi;
    Object Qdistribution, Qfor_distribution, Qreload_load, Qno_process;
    Object Qreload, Qincremental, Qrecompile, Qlaunch_only;
    Object Qlocal_platform_specific_directory, Qexperimental_port;
    Object Qsparcstation, Qunix, Qwin32, Qintelsol_code, Qhpia_code, Qmac_code;
    Object Qlinux_code, Qwindows95_code, Qncr_code, Qintelnt_code;
    Object Qalphant_code, Qalphaosf_code, Qnec_code, Qharris_code;
    Object Qstratus_code, Qvms_code, Qmotorola_code, Qalphavms_code;
    Object Qsparcsol_code, Qsun4_code, Qsun3_code, Qrs6000_code;
    Object Qhp9000s800_code, Qhp9000s700_code, Qhp9000s400_code;
    Object Qhp9000s300_code, Qmasscomp_code, Qdecstation_code, Qnext_code;
    Object Qsequent_code, Qsgi_code, Qaviion_code, Qdos_code, Qi386_code;
    Object Qrelease_quality, Qbeta_release_quality, Qalpha_release_quality;
    Object Qprototype_release_quality, list_constant_68, Qkl_files;
    Object list_constant_67, Qkb_files, list_constant_66, list_constant_65;
    Object list_constant_64, list_constant_63, list_constant_62;
    Object list_constant_61, string_constant_42, list_constant_60;
    Object list_constant_59, list_constant_53, Qsystem_lisp_binary_files;
    Object list_constant_58, list_constant_57, Kupdates_file_type_symbol;
    Object list_constant_56, list_constant_55, Qbinary_files, list_constant_54;
    Object list_constant_52, Qtext_files, list_constant_51, Qtext;
    Object list_constant_50, Qh_files, list_constant_49, list_constant_48;
    Object string_constant_41, list_constant_47, Qdistribution_c_files;
    Object list_constant_44, list_constant_46, list_constant_42;
    Object list_constant_41, list_constant_12, list_constant_45;
    Object list_constant_43, list_constant_40, string_constant_40, Qsystem_c;
    Object string_constant_39, string_constant_38, list_constant_37;
    Object list_constant_39, list_constant_38, Qlisp, list_constant_36;
    Object list_constant_35, Qlisp_binary, Klocal_file_p, Kbinary_file_p;
    Object list_constant_34, Qboot_files, list_constant_33, Qboot_file;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, list_constant_13, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object Kdevelopment_optional_module_p, list_constant_5;
    Object Klisp_update_function, Klisp_compile_function, Klisp_load_function;
    Object Knon_lisp_compile, string_constant_37, Qmost_positive_gensym_float;
    Object Qmost_negative_gensym_float, float_constant;
    Object Qleast_positive_normalized_gensym_float, Qpositive_bits_per_fixnum;

    x_note_fn_call(1,67);
    SET_PACKAGE("AB");
    Allow_development_compile_p = T;
    if (Current_system_being_loaded == UNBOUND)
	Current_system_being_loaded = Nil;
    if (Override_eliminate_for_gsi_p == UNBOUND)
	Override_eliminate_for_gsi_p = Nil;
    if (Override_eliminate_for_gsi_no_utf_g_p == UNBOUND)
	Override_eliminate_for_gsi_no_utf_g_p = T;
    if (Macroexpanding_for_instruction_expander == UNBOUND)
	Macroexpanding_for_instruction_expander = Nil;
    Kchestnut_3 = STATIC_SYMBOL("CHESTNUT-3",Pkeyword);
    string_constant = STATIC_STRING("GENSYMED-SYMBOL");
    if (Most_recent_defun_warned_for_catch_qm == UNBOUND)
	Most_recent_defun_warned_for_catch_qm = Nil;
    if (Most_recent_defun_warned_for_unwind_protect_qm == UNBOUND)
	Most_recent_defun_warned_for_unwind_protect_qm = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qstring_or_symbol_equal = STATIC_SYMBOL("STRING-OR-SYMBOL-EQUAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qstring_or_symbol_equal,
	    STATIC_FUNCTION(string_or_symbol_equal,NIL,FALSE,2,2));
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    if (Current_module_qm == UNBOUND)
	Current_module_qm = Nil;
    Load_pathname = SEVENTH(Bootstrap_information);
    if (Use_directory_lists_for_bootstrapping_qm == UNBOUND)
	Use_directory_lists_for_bootstrapping_qm = Nil;
    if (Last_bootstrap_mode_qm == UNBOUND)
	Last_bootstrap_mode_qm = Nil;
    Qpositive_bits_per_fixnum = STATIC_SYMBOL("POSITIVE-BITS-PER-FIXNUM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpositive_bits_per_fixnum,
	    Positive_bits_per_fixnum);
    SET_SYMBOL_VALUE(Qpositive_bits_per_fixnum,
	    integer_length(Most_positive_fixnum));
    Qleast_positive_normalized_gensym_float = 
	    STATIC_SYMBOL("LEAST-POSITIVE-NORMALIZED-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qleast_positive_normalized_gensym_float,
	    Least_positive_normalized_gensym_float);
    float_constant = STATIC_FLOAT(2.2250738585072014E-308);
    SET_SYMBOL_VALUE(Qleast_positive_normalized_gensym_float,float_constant);
    Qmost_negative_gensym_float = 
	    STATIC_SYMBOL("MOST-NEGATIVE-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_negative_gensym_float,
	    Most_negative_gensym_float);
    SET_SYMBOL_VALUE(Qmost_negative_gensym_float,Most_negative_double_float);
    Qmost_positive_gensym_float = 
	    STATIC_SYMBOL("MOST-POSITIVE-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_gensym_float,
	    Most_positive_gensym_float);
    SET_SYMBOL_VALUE(Qmost_positive_gensym_float,Most_positive_double_float);
    string_constant_37 = STATIC_STRING("AB");
    if (Ab_package_1 == UNBOUND)
	Ab_package_1 = find_package(string_constant_37);
    if (All_systems == UNBOUND)
	All_systems = Nil;
    Qreal_system_name = STATIC_SYMBOL("REAL-SYSTEM-NAME",AB_package);
    Knon_development_macros = STATIC_SYMBOL("NON-DEVELOPMENT-MACROS",Pkeyword);
    Qlocal_macro_directory = STATIC_SYMBOL("LOCAL-MACRO-DIRECTORY",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Kno_macros = STATIC_SYMBOL("NO-MACROS",Pkeyword);
    Qlocal_chestnut_dst_directory = 
	    STATIC_SYMBOL("LOCAL-CHESTNUT-DST-DIRECTORY",AB_package);
    Qlocal_dst_directory = STATIC_SYMBOL("LOCAL-DST-DIRECTORY",AB_package);
    Qsystem_binary_pathname_qm = STATIC_SYMBOL("SYSTEM-BINARY-PATHNAME\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_binary_pathname_qm,
	    STATIC_FUNCTION(system_binary_pathname_qm,NIL,FALSE,1,1));
    Null_io = make_broadcast_stream(0);
    if (Filename_of_module_being_loaded_qm == UNBOUND)
	Filename_of_module_being_loaded_qm = Nil;
    Kbinary_file_p = STATIC_SYMBOL("BINARY-FILE-P",Pkeyword);
    list_constant_5 = STATIC_CONS(Qnil,Qnil);
    list_constant_7 = STATIC_CONS(Kbinary_file_p,list_constant_5);
    Klocal_file_p = STATIC_SYMBOL("LOCAL-FILE-P",Pkeyword);
    list_constant_8 = STATIC_CONS(Klocal_file_p,list_constant_5);
    Kno_lisp_binary_produced_p = STATIC_SYMBOL("NO-LISP-BINARY-PRODUCED-P",
	    Pkeyword);
    list_constant_9 = STATIC_CONS(Kno_lisp_binary_produced_p,list_constant_5);
    Kmaintained_as_a_binary_file_p = 
	    STATIC_SYMBOL("MAINTAINED-AS-A-BINARY-FILE-P",Pkeyword);
    list_constant_10 = STATIC_CONS(Kmaintained_as_a_binary_file_p,
	    list_constant_5);
    Koptional_module_p = STATIC_SYMBOL("OPTIONAL-MODULE-P",Pkeyword);
    list_constant_11 = STATIC_CONS(Koptional_module_p,list_constant_5);
    Knon_lisp_compile = STATIC_SYMBOL("NON-LISP-COMPILE",Pkeyword);
    list_constant_12 = STATIC_CONS(Knon_lisp_compile,list_constant_5);
    Kmaster_directory_namestring = 
	    STATIC_SYMBOL("MASTER-DIRECTORY-NAMESTRING",Pkeyword);
    list_constant_13 = STATIC_CONS(Kmaster_directory_namestring,
	    list_constant_5);
    Klocal_directory_namestring = 
	    STATIC_SYMBOL("LOCAL-DIRECTORY-NAMESTRING",Pkeyword);
    list_constant_14 = STATIC_CONS(Klocal_directory_namestring,
	    list_constant_5);
    Kbinary_directory_namestring = 
	    STATIC_SYMBOL("BINARY-DIRECTORY-NAMESTRING",Pkeyword);
    list_constant_15 = STATIC_CONS(Kbinary_directory_namestring,
	    list_constant_5);
    Kmaster_pathname_name = STATIC_SYMBOL("MASTER-PATHNAME-NAME",Pkeyword);
    list_constant_16 = STATIC_CONS(Kmaster_pathname_name,list_constant_5);
    Klocal_pathname_name = STATIC_SYMBOL("LOCAL-PATHNAME-NAME",Pkeyword);
    list_constant_17 = STATIC_CONS(Klocal_pathname_name,list_constant_5);
    Kbinary_pathname_name = STATIC_SYMBOL("BINARY-PATHNAME-NAME",Pkeyword);
    list_constant_18 = STATIC_CONS(Kbinary_pathname_name,list_constant_5);
    Kmaster_file_type = STATIC_SYMBOL("MASTER-FILE-TYPE",Pkeyword);
    list_constant_19 = STATIC_CONS(Kmaster_file_type,list_constant_5);
    Klocal_file_type = STATIC_SYMBOL("LOCAL-FILE-TYPE",Pkeyword);
    list_constant_20 = STATIC_CONS(Klocal_file_type,list_constant_5);
    Kbinary_file_type = STATIC_SYMBOL("BINARY-FILE-TYPE",Pkeyword);
    list_constant_21 = STATIC_CONS(Kbinary_file_type,list_constant_5);
    Kdefault_file_type = STATIC_SYMBOL("DEFAULT-FILE-TYPE",Pkeyword);
    string_constant_1 = STATIC_STRING("");
    list_constant_22 = STATIC_LIST((SI_Long)2L,Kdefault_file_type,
	    string_constant_1);
    Kupdates_file_type_symbol = STATIC_SYMBOL("UPDATES-FILE-TYPE-SYMBOL",
	    Pkeyword);
    list_constant_23 = STATIC_CONS(Kupdates_file_type_symbol,list_constant_5);
    Klisp_load_function = STATIC_SYMBOL("LISP-LOAD-FUNCTION",Pkeyword);
    list_constant_24 = STATIC_CONS(Klisp_load_function,list_constant_5);
    Klisp_compile_function = STATIC_SYMBOL("LISP-COMPILE-FUNCTION",Pkeyword);
    list_constant_25 = STATIC_CONS(Klisp_compile_function,list_constant_5);
    Klisp_update_function = STATIC_SYMBOL("LISP-UPDATE-FUNCTION",Pkeyword);
    list_constant_26 = STATIC_CONS(Klisp_update_function,list_constant_5);
    Kinclude_test_for_compile = STATIC_SYMBOL("INCLUDE-TEST-FOR-COMPILE",
	    Pkeyword);
    list_constant_27 = STATIC_CONS(Kinclude_test_for_compile,list_constant_5);
    Kinclude_test_for_load = STATIC_SYMBOL("INCLUDE-TEST-FOR-LOAD",Pkeyword);
    list_constant_28 = STATIC_CONS(Kinclude_test_for_load,list_constant_5);
    Kinclude_test_for_update = STATIC_SYMBOL("INCLUDE-TEST-FOR-UPDATE",
	    Pkeyword);
    list_constant_6 = STATIC_CONS(Qt,Qnil);
    list_constant_29 = STATIC_CONS(Kinclude_test_for_update,list_constant_6);
    Koverriding_include_test = STATIC_SYMBOL("OVERRIDING-INCLUDE-TEST",
	    Pkeyword);
    list_constant_30 = STATIC_CONS(Koverriding_include_test,list_constant_5);
    Kdevelopment_optional_module_p = 
	    STATIC_SYMBOL("DEVELOPMENT-OPTIONAL-MODULE-P",Pkeyword);
    list_constant_31 = STATIC_CONS(Kdevelopment_optional_module_p,
	    list_constant_6);
    list_constant_32 = STATIC_LIST((SI_Long)25L,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14,list_constant_15,list_constant_16,
	    list_constant_17,list_constant_18,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23,list_constant_24,list_constant_25,
	    list_constant_26,list_constant_27,list_constant_28,
	    list_constant_29,list_constant_30,list_constant_31);
    Alist_of_file_property_base_defaults = list_constant_32;
    Qall_optional_modules = STATIC_SYMBOL("ALL-OPTIONAL-MODULES",AB_package);
    Qoptional_modules = STATIC_SYMBOL("OPTIONAL-MODULES",AB_package);
    Qmaster_source_directory = STATIC_SYMBOL("MASTER-SOURCE-DIRECTORY",
	    AB_package);
    Qlocal_source_directory = STATIC_SYMBOL("LOCAL-SOURCE-DIRECTORY",
	    AB_package);
    Kdistribution = STATIC_SYMBOL("DISTRIBUTION",Pkeyword);
    Kunix = STATIC_SYMBOL("UNIX",Pkeyword);
    Qmaster = STATIC_SYMBOL("MASTER",AB_package);
    Qbinary = STATIC_SYMBOL("BINARY",AB_package);
    string_constant_2 = STATIC_STRING("*");
    Qlocal = STATIC_SYMBOL("LOCAL",AB_package);
    Qboot_files = STATIC_SYMBOL("BOOT-FILES",AB_package);
    Qboot_file = STATIC_SYMBOL("BOOT-FILE",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qboot_file);
    list_constant_34 = STATIC_CONS(list_constant_33,Qnil);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qboot_files,Qboot_files,
	    list_constant_34);
    Qsystem_lisp_binary_files = STATIC_SYMBOL("SYSTEM-LISP-BINARY-FILES",
	    AB_package);
    list_constant_53 = STATIC_CONS(Kbinary_file_p,list_constant_6);
    list_constant_59 = STATIC_CONS(Klocal_file_p,list_constant_6);
    Qlisp_binary = STATIC_SYMBOL("LISP-BINARY",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qlisp_binary);
    list_constant_35 = STATIC_CONS(Kinclude_test_for_load,list_constant_6);
    list_constant_37 = STATIC_CONS(list_constant_35,Qnil);
    list_constant_60 = STATIC_CONS(list_constant_36,list_constant_37);
    Qsystem_lisp_source_files = STATIC_SYMBOL("SYSTEM-LISP-SOURCE-FILES",
	    AB_package);
    string_constant_42 = STATIC_STRING("LISP");
    Qlisp = STATIC_SYMBOL("LISP",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qlisp);
    list_constant_39 = STATIC_CONS(Kinclude_test_for_compile,list_constant_6);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,list_constant_38,
	    list_constant_39,list_constant_37);
    Qsystem_c_files = STATIC_SYMBOL("SYSTEM-C-FILES",AB_package);
    string_constant_38 = STATIC_STRING("o");
    list_constant_41 = STATIC_LIST((SI_Long)2L,Kbinary_file_type,
	    string_constant_38);
    string_constant_39 = STATIC_STRING("c");
    list_constant_42 = STATIC_LIST((SI_Long)2L,Kdefault_file_type,
	    string_constant_39);
    Qsystem_c = STATIC_SYMBOL("SYSTEM-C",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qsystem_c);
    string_constant_40 = STATIC_STRING("binary-directory-namestring");
    list_constant_40 = STATIC_LIST((SI_Long)2L,
	    Kbinary_directory_namestring,string_constant_40);
    list_constant_44 = STATIC_CONS(list_constant_40,Qnil);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)5L,list_constant_12,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44);
    list_constant_62 = STATIC_LIST((SI_Long)3L,Qsystem_c_files,
	    Qsystem_c_files,list_constant_45);
    Qdistribution_c_files = STATIC_SYMBOL("DISTRIBUTION-C-FILES",AB_package);
    Qc = STATIC_SYMBOL("C",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,Qc);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)5L,list_constant_12,
	    list_constant_41,list_constant_42,list_constant_46,
	    list_constant_44);
    list_constant_63 = STATIC_LIST((SI_Long)3L,Qdistribution_c_files,
	    Qdistribution_c_files,list_constant_47);
    Qh_files = STATIC_SYMBOL("H-FILES",AB_package);
    string_constant_41 = STATIC_STRING("h");
    list_constant_48 = STATIC_LIST((SI_Long)2L,Kdefault_file_type,
	    string_constant_41);
    Qh = STATIC_SYMBOL("H",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,Qh);
    list_constant_50 = STATIC_LIST((SI_Long)2L,list_constant_48,
	    list_constant_49);
    list_constant_64 = STATIC_LIST((SI_Long)3L,Qh_files,Qh_files,
	    list_constant_50);
    Qtext_files = STATIC_SYMBOL("TEXT-FILES",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qtext);
    list_constant_52 = STATIC_CONS(list_constant_51,Qnil);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qtext_files,Qtext_files,
	    list_constant_52);
    Qbinary_files = STATIC_SYMBOL("BINARY-FILES",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,
	    Qbinary);
    list_constant_55 = STATIC_LIST((SI_Long)2L,list_constant_53,
	    list_constant_54);
    list_constant_66 = STATIC_LIST((SI_Long)3L,Qbinary_files,Qbinary_files,
	    list_constant_55);
    Qkb_files = STATIC_SYMBOL("KB-FILES",AB_package);
    Qkb = STATIC_SYMBOL("KB",AB_package);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,Qkb);
    list_constant_67 = STATIC_CONS(list_constant_56,Qnil);
    Qkl_files = STATIC_SYMBOL("KL-FILES",AB_package);
    Qkl = STATIC_SYMBOL("KL",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Kupdates_file_type_symbol,Qkl);
    list_constant_68 = STATIC_CONS(list_constant_57,Qnil);
    temp = LIST_2(Kdefault_file_type,THIRD(Bootstrap_information));
    temp_1 = LIST_2(Kdefault_file_type,FOURTH(Bootstrap_information));
    Alist_of_system_file_class_descriptions = list(10,list_constant_58,
	    LIST_3(Qsystem_lisp_binary_files,Qsystem_lisp_binary_files,
	    list_star(4,list_constant_53,list_constant_59,
	    LIST_2(Kdefault_file_type,FIRST(Bootstrap_information)),
	    list_constant_60)),LIST_3(Qsystem_lisp_source_files,
	    Qsystem_lisp_source_files,list_star(4,LIST_2(Kmaster_file_type,
	    string_constant_42),LIST_2(Kdefault_file_type,
	    SECOND(Bootstrap_information)),LIST_2(Kbinary_file_type,
	    FIRST(Bootstrap_information)),list_constant_61)),
	    list_constant_62,list_constant_63,list_constant_64,
	    list_constant_65,list_constant_66,LIST_3(Qkb_files,Qkb_files,
	    CONS(temp,list_constant_67)),LIST_3(Qkl_files,Qkl_files,
	    CONS(temp_1,list_constant_68)));
    Qprototype_release_quality = STATIC_SYMBOL("PROTOTYPE-RELEASE-QUALITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qprototype_release_quality,FIX((SI_Long)0L));
    Qalpha_release_quality = STATIC_SYMBOL("ALPHA-RELEASE-QUALITY",AB_package);
    SET_SYMBOL_VALUE(Qalpha_release_quality,FIX((SI_Long)1L));
    Qbeta_release_quality = STATIC_SYMBOL("BETA-RELEASE-QUALITY",AB_package);
    SET_SYMBOL_VALUE(Qbeta_release_quality,FIX((SI_Long)2L));
    Qrelease_quality = STATIC_SYMBOL("RELEASE-QUALITY",AB_package);
    SET_SYMBOL_VALUE(Qrelease_quality,FIX((SI_Long)3L));
    Qalpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    Qbrief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    Qpatch_level = STATIC_SYMBOL("PATCH-LEVEL",AB_package);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    string_constant_3 = STATIC_STRING("none");
    Qi386_code = STATIC_SYMBOL("I386-CODE",AB_package);
    SET_SYMBOL_VALUE(Qi386_code,FIX((SI_Long)1L));
    Qdos_code = STATIC_SYMBOL("DOS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qdos_code,FIX((SI_Long)2L));
    Qaviion_code = STATIC_SYMBOL("AVIION-CODE",AB_package);
    SET_SYMBOL_VALUE(Qaviion_code,FIX((SI_Long)3L));
    Qsgi_code = STATIC_SYMBOL("SGI-CODE",AB_package);
    SET_SYMBOL_VALUE(Qsgi_code,FIX((SI_Long)4L));
    Qsequent_code = STATIC_SYMBOL("SEQUENT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qsequent_code,FIX((SI_Long)5L));
    Qnext_code = STATIC_SYMBOL("NEXT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qnext_code,FIX((SI_Long)6L));
    Qdecstation_code = STATIC_SYMBOL("DECSTATION-CODE",AB_package);
    SET_SYMBOL_VALUE(Qdecstation_code,FIX((SI_Long)7L));
    Qmasscomp_code = STATIC_SYMBOL("MASSCOMP-CODE",AB_package);
    SET_SYMBOL_VALUE(Qmasscomp_code,FIX((SI_Long)8L));
    Qhp9000s300_code = STATIC_SYMBOL("HP9000S300-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhp9000s300_code,FIX((SI_Long)9L));
    Qhp9000s400_code = STATIC_SYMBOL("HP9000S400-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhp9000s400_code,FIX((SI_Long)10L));
    Qhp9000s700_code = STATIC_SYMBOL("HP9000S700-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhp9000s700_code,FIX((SI_Long)11L));
    Qhp9000s800_code = STATIC_SYMBOL("HP9000S800-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhp9000s800_code,FIX((SI_Long)12L));
    Qrs6000_code = STATIC_SYMBOL("RS6000-CODE",AB_package);
    SET_SYMBOL_VALUE(Qrs6000_code,FIX((SI_Long)13L));
    Qsun3_code = STATIC_SYMBOL("SUN3-CODE",AB_package);
    SET_SYMBOL_VALUE(Qsun3_code,FIX((SI_Long)14L));
    Qsun4_code = STATIC_SYMBOL("SUN4-CODE",AB_package);
    SET_SYMBOL_VALUE(Qsun4_code,FIX((SI_Long)15L));
    Qsparcsol_code = STATIC_SYMBOL("SPARCSOL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qsparcsol_code,FIX((SI_Long)16L));
    Qalphavms_code = STATIC_SYMBOL("ALPHAVMS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qalphavms_code,FIX((SI_Long)17L));
    Qmotorola_code = STATIC_SYMBOL("MOTOROLA-CODE",AB_package);
    SET_SYMBOL_VALUE(Qmotorola_code,FIX((SI_Long)18L));
    Qvms_code = STATIC_SYMBOL("VMS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qvms_code,FIX((SI_Long)19L));
    Qstratus_code = STATIC_SYMBOL("STRATUS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qstratus_code,FIX((SI_Long)20L));
    Qharris_code = STATIC_SYMBOL("HARRIS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qharris_code,FIX((SI_Long)21L));
    Qnec_code = STATIC_SYMBOL("NEC-CODE",AB_package);
    SET_SYMBOL_VALUE(Qnec_code,FIX((SI_Long)22L));
    Qalphaosf_code = STATIC_SYMBOL("ALPHAOSF-CODE",AB_package);
    SET_SYMBOL_VALUE(Qalphaosf_code,FIX((SI_Long)23L));
    Qalphant_code = STATIC_SYMBOL("ALPHANT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qalphant_code,FIX((SI_Long)24L));
    Qintelnt_code = STATIC_SYMBOL("INTELNT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qintelnt_code,FIX((SI_Long)25L));
    Qncr_code = STATIC_SYMBOL("NCR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qncr_code,FIX((SI_Long)26L));
    Qwindows95_code = STATIC_SYMBOL("WINDOWS95-CODE",AB_package);
    SET_SYMBOL_VALUE(Qwindows95_code,FIX((SI_Long)27L));
    Qlinux_code = STATIC_SYMBOL("LINUX-CODE",AB_package);
    SET_SYMBOL_VALUE(Qlinux_code,FIX((SI_Long)28L));
    Qmac_code = STATIC_SYMBOL("MAC-CODE",AB_package);
    SET_SYMBOL_VALUE(Qmac_code,FIX((SI_Long)29L));
    Qhpia_code = STATIC_SYMBOL("HPIA-CODE",AB_package);
    SET_SYMBOL_VALUE(Qhpia_code,FIX((SI_Long)30L));
    Qintelsol_code = STATIC_SYMBOL("INTELSOL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qintelsol_code,FIX((SI_Long)31L));
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    if (G2_operating_system == UNBOUND) {
	platform_code = g2ext_get_platform_code();
	if ( !((SI_Long)-128L <= platform_code && platform_code <= 
		(SI_Long)127L)) {
	    format((SI_Long)3L,T,
		    "Unknown platform code ~a, assuming UNIX o/s",
		    FIX(platform_code));
	    G2_operating_system = Qunix;
	}
	else
	    switch ((char)platform_code) {
	      case 1:
		G2_operating_system = Qunix;
		break;
	      case 2:
		G2_operating_system = Qdos;
		break;
	      case 3:
		G2_operating_system = Qunix;
		break;
	      case 4:
		G2_operating_system = Qunix;
		break;
	      case 5:
		G2_operating_system = Qunix;
		break;
	      case 6:
		G2_operating_system = Qunix;
		break;
	      case 7:
		G2_operating_system = Qunix;
		break;
	      case 8:
		G2_operating_system = Qunix;
		break;
	      case 9:
		G2_operating_system = Qunix;
		break;
	      case 10:
		G2_operating_system = Qunix;
		break;
	      case 11:
		G2_operating_system = Qunix;
		break;
	      case 12:
		G2_operating_system = Qunix;
		break;
	      case 13:
		G2_operating_system = Qunix;
		break;
	      case 14:
		G2_operating_system = Qunix;
		break;
	      case 15:
		G2_operating_system = Qunix;
		break;
	      case 16:
		G2_operating_system = Qunix;
		break;
	      case 31:
		G2_operating_system = Qunix;
		break;
	      case 17:
		G2_operating_system = Qvms;
		break;
	      case 18:
		G2_operating_system = Qunix;
		break;
	      case 19:
		G2_operating_system = Qvms;
		break;
	      case 20:
		G2_operating_system = Qunix;
		break;
	      case 21:
		G2_operating_system = Qunix;
		break;
	      case 22:
		G2_operating_system = Qunix;
		break;
	      case 23:
		G2_operating_system = Qunix;
		break;
	      case 24:
		G2_operating_system = Qwin32;
		break;
	      case 25:
		G2_operating_system = Qwin32;
		break;
	      case 26:
		G2_operating_system = Qunix;
		break;
	      case 27:
		G2_operating_system = Qwin32;
		break;
	      case 28:
		G2_operating_system = Qunix;
		break;
	      case 29:
		G2_operating_system = Qunix;
		break;
	      case 30:
		G2_operating_system = Qunix;
		break;
	      default:
		format((SI_Long)3L,T,
			"Unknown platform code ~a, assuming UNIX o/s",
			FIX(platform_code));
		G2_operating_system = Qunix;
		break;
	    }
    }
    Qexperimental_port = STATIC_SYMBOL("EXPERIMENTAL-PORT",AB_package);
    Qi386 = STATIC_SYMBOL("I386",AB_package);
    Qaviion = STATIC_SYMBOL("AVIION",AB_package);
    Qsgi = STATIC_SYMBOL("SGI",AB_package);
    Qsequent = STATIC_SYMBOL("SEQUENT",AB_package);
    Qnext = STATIC_SYMBOL("NEXT",AB_package);
    Qdecstation = STATIC_SYMBOL("DECSTATION",AB_package);
    Qmasscomp = STATIC_SYMBOL("MASSCOMP",AB_package);
    Qhp9000s300 = STATIC_SYMBOL("HP9000S300",AB_package);
    Qhp9000s400 = STATIC_SYMBOL("HP9000S400",AB_package);
    Qhp9000s700 = STATIC_SYMBOL("HP9000S700",AB_package);
    Qhp9000s800 = STATIC_SYMBOL("HP9000S800",AB_package);
    Qrs6000 = STATIC_SYMBOL("RS6000",AB_package);
    Qsun3 = STATIC_SYMBOL("SUN3",AB_package);
    Qsparcstation = STATIC_SYMBOL("SPARCSTATION",AB_package);
    Qsparcsol = STATIC_SYMBOL("SPARCSOL",AB_package);
    Qintelsol = STATIC_SYMBOL("INTELSOL",AB_package);
    Qalphavms = STATIC_SYMBOL("ALPHAVMS",AB_package);
    Qmotorola = STATIC_SYMBOL("MOTOROLA",AB_package);
    Qstratus = STATIC_SYMBOL("STRATUS",AB_package);
    Qharris = STATIC_SYMBOL("HARRIS",AB_package);
    Qnec = STATIC_SYMBOL("NEC",AB_package);
    Qalphaosf = STATIC_SYMBOL("ALPHAOSF",AB_package);
    Qalphant = STATIC_SYMBOL("ALPHANT",AB_package);
    Qintelnt = STATIC_SYMBOL("INTELNT",AB_package);
    Qncr = STATIC_SYMBOL("NCR",AB_package);
    Qwindows95 = STATIC_SYMBOL("WINDOWS95",AB_package);
    Qlinux = STATIC_SYMBOL("LINUX",AB_package);
    Qmac = STATIC_SYMBOL("MAC",AB_package);
    Qhpia64 = STATIC_SYMBOL("HPIA64",AB_package);
    if (G2_machine_type == UNBOUND) {
	platform_code = g2ext_get_platform_code();
	if ( !((SI_Long)-128L <= platform_code && platform_code <= 
		(SI_Long)127L))
	    G2_machine_type = Qexperimental_port;
	else
	    switch ((char)platform_code) {
	      case 1:
		G2_machine_type = Qi386;
		break;
	      case 2:
		G2_machine_type = Qdos;
		break;
	      case 3:
		G2_machine_type = Qaviion;
		break;
	      case 4:
		G2_machine_type = Qsgi;
		break;
	      case 5:
		G2_machine_type = Qsequent;
		break;
	      case 6:
		G2_machine_type = Qnext;
		break;
	      case 7:
		G2_machine_type = Qdecstation;
		break;
	      case 8:
		G2_machine_type = Qmasscomp;
		break;
	      case 9:
		G2_machine_type = Qhp9000s300;
		break;
	      case 10:
		G2_machine_type = Qhp9000s400;
		break;
	      case 11:
		G2_machine_type = Qhp9000s700;
		break;
	      case 12:
		G2_machine_type = Qhp9000s800;
		break;
	      case 13:
		G2_machine_type = Qrs6000;
		break;
	      case 14:
		G2_machine_type = Qsun3;
		break;
	      case 15:
		G2_machine_type = Qsparcstation;
		break;
	      case 16:
		G2_machine_type = Qsparcsol;
		break;
	      case 31:
		G2_machine_type = Qintelsol;
		break;
	      case 17:
		G2_machine_type = Qalphavms;
		break;
	      case 18:
		G2_machine_type = Qmotorola;
		break;
	      case 19:
		G2_machine_type = Qvms;
		break;
	      case 20:
		G2_machine_type = Qstratus;
		break;
	      case 21:
		G2_machine_type = Qharris;
		break;
	      case 22:
		G2_machine_type = Qnec;
		break;
	      case 23:
		G2_machine_type = Qalphaosf;
		break;
	      case 24:
		G2_machine_type = Qalphant;
		break;
	      case 25:
		G2_machine_type = Qintelnt;
		break;
	      case 26:
		G2_machine_type = Qncr;
		break;
	      case 27:
		G2_machine_type = Qwindows95;
		break;
	      case 28:
		G2_machine_type = Qlinux;
		break;
	      case 29:
		G2_machine_type = Qmac;
		break;
	      case 30:
		G2_machine_type = Qhpia64;
		break;
	      default:
		G2_machine_type = Qexperimental_port;
		break;
	    }
    }
    if (Machine_model_var == UNBOUND)
	Machine_model_var = Nil;
    string_constant_4 = STATIC_STRING(" Data General AViiON");
    string_constant_5 = STATIC_STRING(" Motorola 88000");
    string_constant_6 = STATIC_STRING(" NeXT");
    string_constant_7 = STATIC_STRING(" Silicon Graphics");
    string_constant_8 = STATIC_STRING(" Sequent");
    string_constant_9 = STATIC_STRING(" DECstation");
    string_constant_10 = STATIC_STRING(" Concurrent 6000s");
    string_constant_11 = STATIC_STRING(" HP9000/300s");
    string_constant_12 = STATIC_STRING(" HP9000/400s");
    string_constant_13 = STATIC_STRING(" PA-RISC HP-UX");
    string_constant_14 = STATIC_STRING(" HP9000/800s");
    Qcompaq = STATIC_SYMBOL("COMPAQ",AB_package);
    string_constant_15 = STATIC_STRING(" \'386");
    string_constant_16 = STATIC_STRING(" IBM POWERstation");
    string_constant_17 = STATIC_STRING(" Sun 3");
    string_constant_18 = STATIC_STRING(" Vax VMS");
    string_constant_19 = STATIC_STRING(" DEC Alpha AXP/OpenVMS");
    string_constant_20 = STATIC_STRING(" Sun 4/SPARCstation Solaris");
    string_constant_21 = STATIC_STRING(" x86 Solaris");
    Qsun4 = STATIC_SYMBOL("SUN4",AB_package);
    string_constant_22 = STATIC_STRING(" Sun 4/SPARCstation");
    string_constant_23 = STATIC_STRING(" Harris Night Hawk");
    string_constant_24 = STATIC_STRING(" Stratus FTX");
    string_constant_25 = STATIC_STRING(" NEC EWS4800 Series");
    string_constant_26 = STATIC_STRING(" DEC OSF/1 AXP");
    string_constant_27 = STATIC_STRING(" Alpha NT");
    string_constant_28 = STATIC_STRING(" Windows");
    string_constant_29 = STATIC_STRING(" MS Windows 3.1");
    string_constant_30 = STATIC_STRING(" NCR 386/486");
    string_constant_31 = STATIC_STRING(" Windows 95/98");
    string_constant_32 = STATIC_STRING(" Linux");
    string_constant_33 = STATIC_STRING(" Mac OS X");
    string_constant_34 = STATIC_STRING(" Itanium HP-UX");
    string_constant_35 = STATIC_STRING(" Experimental Port");
    Qlocal_platform_specific_directory = 
	    STATIC_SYMBOL("LOCAL-PLATFORM-SPECIFIC-DIRECTORY",AB_package);
    get_new_value = format((SI_Long)4L,Nil,"~a/specific/~(~a~)/",
	    Source_directory_name,G2_machine_type);
    set_get(Qab,Qlocal_platform_specific_directory,get_new_value);
    Qsystem_pathname = STATIC_SYMBOL("SYSTEM-PATHNAME",AB_package);
    Qsystem_lisp_binary_type = STATIC_SYMBOL("SYSTEM-LISP-BINARY-TYPE",
	    AB_package);
    Qsource = STATIC_SYMBOL("SOURCE",AB_package);
    Qsystem_lisp_source_type = STATIC_SYMBOL("SYSTEM-LISP-SOURCE-TYPE",
	    AB_package);
    Qsystem_kb_type = STATIC_SYMBOL("SYSTEM-KB-TYPE",AB_package);
    Qsystem_kl_type = STATIC_SYMBOL("SYSTEM-KL-TYPE",AB_package);
    if (Making_distribution_system_qm == UNBOUND)
	Making_distribution_system_qm = T;
    Qlaunch_function_qm = STATIC_SYMBOL("LAUNCH-FUNCTION\?",AB_package);
    Kcreation_date = STATIC_SYMBOL("CREATION-DATE",Pkeyword);
    All_modules_of_all_systems = Nil;
    Qlaunch_only = STATIC_SYMBOL("LAUNCH-ONLY",AB_package);
    Qrecompile = STATIC_SYMBOL("RECOMPILE",AB_package);
    Qincremental = STATIC_SYMBOL("INCREMENTAL",AB_package);
    Qreload = STATIC_SYMBOL("RELOAD",AB_package);
    Qno_process = STATIC_SYMBOL("NO-PROCESS",AB_package);
    Qreload_load = STATIC_SYMBOL("RELOAD-LOAD",AB_package);
    Qfor_distribution = STATIC_SYMBOL("FOR-DISTRIBUTION",AB_package);
    Qdistribution = STATIC_SYMBOL("DISTRIBUTION",AB_package);
    Qno_gsi = STATIC_SYMBOL("NO-GSI",AB_package);
    Qno_gfi = STATIC_SYMBOL("NO-GFI",AB_package);
    Qno_gspan = STATIC_SYMBOL("NO-GSPAN",AB_package);
    Qno_optional_modules = STATIC_SYMBOL("NO-OPTIONAL-MODULES",AB_package);
    Qverbose = STATIC_SYMBOL("VERBOSE",AB_package);
    Qsilent = STATIC_SYMBOL("SILENT",AB_package);
    Qmacros_only = STATIC_SYMBOL("MACROS-ONLY",AB_package);
    Qprepare_only = STATIC_SYMBOL("PREPARE-ONLY",AB_package);
    Qanalyze_calls = STATIC_SYMBOL("ANALYZE-CALLS",AB_package);
    Qno_make = STATIC_SYMBOL("NO-MAKE",AB_package);
    Qno_delete = STATIC_SYMBOL("NO-DELETE",AB_package);
    Qno_autolog = STATIC_SYMBOL("NO-AUTOLOG",AB_package);
    Qlogfile = STATIC_SYMBOL("LOGFILE",AB_package);
    list_constant = STATIC_LIST((SI_Long)23L,Qcompile,Qlaunch_only,
	    Qrecompile,Qincremental,Qreload,Qno_process,Qreload_load,
	    Qfor_distribution,Qdistribution,Qno_gsi,Qno_gfi,Qno_gspan,
	    Qall_optional_modules,Qno_optional_modules,Qverbose,Qsilent,
	    Qmacros_only,Qprepare_only,Qanalyze_calls,Qno_make,Qno_delete,
	    Qno_autolog,Qlogfile);
    Qdestination = STATIC_SYMBOL("DESTINATION",AB_package);
    Qdistribute = STATIC_SYMBOL("DISTRIBUTE",AB_package);
    Qbinary_directory = STATIC_SYMBOL("BINARY-DIRECTORY",AB_package);
    Qcommand_line = STATIC_SYMBOL("COMMAND-LINE",AB_package);
    Kdefault_dst_directory = STATIC_SYMBOL("DEFAULT-DST-DIRECTORY",Pkeyword);
    Kdefault_macro_directory = STATIC_SYMBOL("DEFAULT-MACRO-DIRECTORY",
	    Pkeyword);
    Kdefault_development_binary_directory = 
	    STATIC_SYMBOL("DEFAULT-DEVELOPMENT-BINARY-DIRECTORY",Pkeyword);
    Qfrom = STATIC_SYMBOL("FROM",AB_package);
    Qto = STATIC_SYMBOL("TO",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qfrom,Qto);
    Qafter = STATIC_SYMBOL("AFTER",AB_package);
    Qbefore = STATIC_SYMBOL("BEFORE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qafter,Qbefore);
    list_constant_3 = STATIC_CONS(Qoptional_modules,Qnil);
    string_constant_36 = 
	    string_append2(STATIC_STRING("Illegal \'distribute, \'destination, or \'binary-directory flag ~\n               ~a.  The legal flags are:   :default-dst-directory, ~\n               :default-macro-directory, an"),
	    STATIC_STRING("d ~\n               :default-development-binary-directory."));
    list_constant_4 = STATIC_CONS(Qnot,list_constant_6);
    Qlisp_modules_to_be_loaded = STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",
	    AB_package);
    Kdevelopment = STATIC_SYMBOL("DEVELOPMENT",Pkeyword);
    Kstandard_module_index = STATIC_SYMBOL("STANDARD-MODULE-INDEX",Pkeyword);
    Qalias = STATIC_SYMBOL("ALIAS",AB_package);
    Qnicknames = STATIC_SYMBOL("NICKNAMES",AB_package);
    Qsystem_package_name = STATIC_SYMBOL("SYSTEM-PACKAGE-NAME",AB_package);
    Qlisp_source_type = STATIC_SYMBOL("LISP-SOURCE-TYPE",AB_package);
    Qlisp_binary_type = STATIC_SYMBOL("LISP-BINARY-TYPE",AB_package);
    Qkb_type = STATIC_SYMBOL("KB-TYPE",AB_package);
    Qkl_type = STATIC_SYMBOL("KL-TYPE",AB_package);
    Qsystems_to_share_binary_files_with = 
	    STATIC_SYMBOL("SYSTEMS-TO-SHARE-BINARY-FILES-WITH",AB_package);
    Qsystem_is_windowless_p = STATIC_SYMBOL("SYSTEM-IS-WINDOWLESS-P",
	    AB_package);
    Qsystem_alias = STATIC_SYMBOL("SYSTEM-ALIAS",AB_package);
}
