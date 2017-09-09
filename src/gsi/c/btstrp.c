/* btstrp.c
 * Input file:  bootstrap.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "btstrp.h"


Object G2int_allow_development_compile_p = UNBOUND;

Object G2int_current_system_being_loaded = UNBOUND;

Object G2int_override_eliminate_for_gsi_p = UNBOUND;

Object G2int_override_eliminate_for_gsi_no_utf_g_p = UNBOUND;

Object G2int_macroexpanding_for_instruction_expander = UNBOUND;

static Object Kchestnut_3;         /* :chestnut-3 */

static Object string_constant;     /* "GENSYMED-SYMBOL" */

/* GENSYM */
Object g2int_gensym varargs_1(int, n)
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

Object G2int_most_recent_defun_warned_for_catchqm = UNBOUND;

Object G2int_most_recent_defun_warned_for_unwind_protectqm = UNBOUND;

/* STRING-OR-SYMBOL-EQUAL */
Object g2int_string_or_symbol_equal(symbol_or_string_1,symbol_or_string_2)
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

static Object Qg2int_string_or_symbol_equal;  /* string-or-symbol-equal */

static Object Qg2int_or;           /* or */

/* EVAL-FEATURE */
Object g2int_eval_feature(feature)
    Object feature;
{
    Object temp, feature_old_value, features;

    x_note_fn_call(1,2);
    if (ATOM(feature)) {
	if (EQ(feature,T))
	    return VALUES_1(feature);
	else
	    return member(4,feature,Features,Ktest,
		    SYMBOL_FUNCTION(Qg2int_string_or_symbol_equal));
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
		    if ( !TRUEP(g2int_eval_feature(feature)))
			return VALUES_1(Nil);
		    features = CDR(features);
		    feature = CAR(features);
		}
	    }
	    else
		return VALUES_1(T);
	}
	else if (EQ(temp,Qg2int_or)) {
	    feature_old_value = feature;
	    feature = REST(feature_old_value);
	    if (feature) {
		features = feature;
		feature = CAR(features);
		for (;;) {
		    if ( !TRUEP(features))
			return VALUES_1(Nil);
		    if (g2int_eval_feature(feature))
			return VALUES_1(T);
		    features = CDR(features);
		    feature = CAR(features);
		}
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qnot))
	    return VALUES_1( !TRUEP(g2int_eval_feature(CADR(feature))) ? T 
		    : Nil);
	else
	    return VALUES_1(Qnil);
    }
}

Object G2int_current_moduleqm = UNBOUND;

Object G2int_current_directory_of_source_truenamesqm = UNBOUND;

Object G2int_current_directory_of_binary_truenames = UNBOUND;

Object G2int_pathname_for_distribution_binariesqm = UNBOUND;

Object G2int_use_directory_lists_for_bootstrappingqm = UNBOUND;

Object G2int_last_bootstrap_modeqm = UNBOUND;

Object G2int_least_positive_normalized_gensym_float = UNBOUND;

Object G2int_most_negative_gensym_float = UNBOUND;

Object G2int_most_positive_gensym_float = UNBOUND;

Object G2int_ab_package_1 = UNBOUND;

Object G2int_all_systems = UNBOUND;

/* SYSTEM-P */
Object g2int_system_p(system_name)
    Object system_name;
{
    x_note_fn_call(1,3);
    return member(4,system_name,G2int_all_systems,Ktest,
	    SYMBOL_FUNCTION(Qg2int_string_or_symbol_equal));
}

/* An output stream used by Boot-System as a `null device' when silent operation is needed. */
Object G2int_null_io = UNBOUND;

Object G2int_filename_of_module_being_loadedqm = UNBOUND;

Object G2int_current_module_source_filename = UNBOUND;

Object G2int_current_module_lisp_binary_filename = UNBOUND;

Object G2int_alist_of_file_property_base_defaults = UNBOUND;

/* SET-FILE-PROPERTY */
Object g2int_set_file_property(file_symbol,file_class,system_1,
	    property_name,property_value)
    Object file_symbol, file_class, system_1, property_name, property_value;
{
    x_note_fn_call(1,4);
    return VALUES_1(Nil);
}

/* GET-FILE-PROPERTY */
Object g2int_get_file_property(file_symbol,file_class,system_1,property_name)
    Object file_symbol, file_class, system_1, property_name;
{
    Object file_symbol_plist, file_class_plist;

    x_note_fn_call(1,5);
    file_symbol_plist = get(file_symbol,property_name,_);
    file_class_plist = getf(file_symbol_plist,file_class,_);
    return getf(file_class_plist,system_1,_);
}

static Object Koverriding_include_test;  /* :overriding-include-test */

/* GET-DEFAULT-INCLUDE-TEST */
Object g2int_get_default_include_test(file_symbol,file_class,system_1,
	    situatation_property_name)
    Object file_symbol, file_class, system_1, situatation_property_name;
{
    Object temp;

    x_note_fn_call(1,6);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Koverriding_include_test);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_get_file_property(file_symbol,file_class,system_1,
		situatation_property_name);
}

static Object Koptional_module_p;  /* :optional-module-p */

static Object Qg2int_optional_modules;  /* optional-modules */

/* NON-OPTIONAL-OR-INCLUDED-OPTIONAL-MODULE-P */
Object g2int_non_optional_or_included_optional_module_p(file_symbol,
	    file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,7);
    temp =  !TRUEP(g2int_get_file_property(file_symbol,file_class,system_1,
	    Koptional_module_p)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return member_eql(file_symbol,get(system_1,Qg2int_optional_modules,_));
}

static Object Kmaster_directory_namestring;  /* :master-directory-namestring */

static Object Qg2int_master_source_directory;  /* master-source-directory */

static Object Qg2int_ab;           /* ab */

/* GET-DEFAULT-MASTER-DIRECTORY-NAMESTRING */
Object g2int_get_default_master_directory_namestring(file_symbol,
	    file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,8);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Kmaster_directory_namestring);
    if (temp);
    else
	temp = get(system_1,Qg2int_master_source_directory,_);
    if (temp);
    else
	temp = g2int_get_file_property(file_symbol,file_class,Qg2int_ab,
		Kmaster_directory_namestring);
    if (temp)
	return VALUES_1(temp);
    else
	return get(Qg2int_ab,Qg2int_master_source_directory,_);
}

static Object Klocal_directory_namestring;  /* :local-directory-namestring */

static Object Qg2int_local_source_directory;  /* local-source-directory */

/* GET-DEFAULT-LOCAL-DIRECTORY-NAMESTRING */
Object g2int_get_default_local_directory_namestring(file_symbol,file_class,
	    system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,9);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Klocal_directory_namestring);
    if (temp);
    else
	temp = get(system_1,Qg2int_local_source_directory,_);
    if (temp);
    else
	temp = g2int_get_file_property(file_symbol,file_class,Qg2int_ab,
		Klocal_directory_namestring);
    if (temp)
	return VALUES_1(temp);
    else
	return get(Qg2int_ab,Qg2int_local_source_directory,_);
}

static Object Kmaster_pathname_name;  /* :master-pathname-name */

/* GET-DEFAULT-MASTER-PATHNAME-NAME */
Object g2int_get_default_master_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,10);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Kmaster_pathname_name);
    if (temp);
    else
	temp = string_downcase(1,file_symbol);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_get_file_property(file_symbol,file_class,Qg2int_ab,
		Kmaster_pathname_name);
}

static Object Klocal_pathname_name;  /* :local-pathname-name */

/* GET-DEFAULT-LOCAL-PATHNAME-NAME */
Object g2int_get_default_local_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,11);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Klocal_pathname_name);
    if (temp);
    else
	temp = string_downcase(1,file_symbol);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_get_file_property(file_symbol,file_class,Qg2int_ab,
		Klocal_pathname_name);
}

static Object Kbinary_pathname_name;  /* :binary-pathname-name */

/* GET-DEFAULT-BINARY-PATHNAME-NAME */
Object g2int_get_default_binary_pathname_name(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,12);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Kbinary_pathname_name);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_get_default_local_pathname_name(file_symbol,
		file_class,system_1);
}

static Object Kmaster_file_type;   /* :master-file-type */

static Object Kdefault_file_type;  /* :default-file-type */

static Object string_constant_1;   /* "" */

/* GET-DEFAULT-MASTER-FILE-TYPE */
Object g2int_get_default_master_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,13);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Kmaster_file_type);
    if (temp);
    else
	temp = g2int_get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Klocal_file_type;    /* :local-file-type */

/* GET-LOCAL-FILE-TYPE */
Object g2int_get_local_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,14);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Klocal_file_type);
    if (temp);
    else
	temp = g2int_get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Kbinary_file_type;   /* :binary-file-type */

/* GET-BINARY-FILE-TYPE */
Object g2int_get_binary_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    Object temp;

    x_note_fn_call(1,15);
    temp = g2int_get_file_property(file_symbol,file_class,system_1,
	    Kbinary_file_type);
    if (temp);
    else
	temp = g2int_get_file_property(file_symbol,file_class,system_1,
		Kdefault_file_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_1);
}

static Object Kmaintained_as_a_binary_file_p;  /* :maintained-as-a-binary-file-p */

/* GET-DEFAULT-LOCAL-FILE-TYPE */
Object g2int_get_default_local_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    x_note_fn_call(1,16);
    if (g2int_get_file_property(file_symbol,file_class,system_1,
	    Kmaintained_as_a_binary_file_p))
	return g2int_get_binary_file_type(file_symbol,file_class,system_1);
    else
	return g2int_get_local_file_type(file_symbol,file_class,system_1);
}

static Object Kno_lisp_binary_produced_p;  /* :no-lisp-binary-produced-p */

/* GET-DEFAULT-BINARY-FILE-TYPE */
Object g2int_get_default_binary_file_type(file_symbol,file_class,system_1)
    Object file_symbol, file_class, system_1;
{
    x_note_fn_call(1,17);
    if (g2int_get_file_property(file_symbol,file_class,system_1,
	    Kno_lisp_binary_produced_p))
	return g2int_get_local_file_type(file_symbol,file_class,system_1);
    else
	return g2int_get_binary_file_type(file_symbol,file_class,system_1);
}

Object G2int_alist_of_system_file_class_descriptions = UNBOUND;

static Object Qg2int_alpha_or_beta;  /* alpha-or-beta */

static Object Qg2int_brief_description;  /* brief-description */

static Object Qg2int_patch_level;  /* patch-level */

/* WRITE-SYSTEM-VERSION */
Object g2int_write_system_version(system_version_qm)
    Object system_version_qm;
{
    Object major_number, minor_number, alpha_or_beta_qm, brief_description_qm;
    Object patch_level_qm;
    SI_Long tenths, hundredths;

    x_note_fn_call(1,18);
    major_number = FIRST(system_version_qm);
    if (major_number);
    else
	major_number = FIX((SI_Long)0L);
    minor_number = SECOND(system_version_qm);
    if (minor_number);
    else
	minor_number = FIX((SI_Long)0L);
    alpha_or_beta_qm = getf(CDDR(system_version_qm),Qg2int_alpha_or_beta,_);
    brief_description_qm = getf(CDDR(system_version_qm),
	    Qg2int_brief_description,_);
    patch_level_qm = getf(CDDR(system_version_qm),Qg2int_patch_level,_);
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

static Object Qg2int_system_version;  /* system-version */

/* SET-SYSTEM-VERSION */
Object g2int_set_system_version(system_1,system_version)
    Object system_1, system_version;
{
    x_note_fn_call(1,19);
    return set_get(system_1,Qg2int_system_version,system_version);
}

/* GET-SYSTEM-MAJOR-VERSION */
Object g2int_get_system_major_version(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(1,20);
    temp = get(system_1,Qg2int_system_version,_);
    return VALUES_1(FIRST(temp));
}

/* GET-SYSTEM-MINOR-VERSION */
Object g2int_get_system_minor_version(system_1)
    Object system_1;
{
    Object temp;

    x_note_fn_call(1,21);
    temp = get(system_1,Qg2int_system_version,_);
    return VALUES_1(SECOND(temp));
}

/* OPEN-EDITOR-STREAM-OR-BITSINK */
Object g2int_open_editor_stream_or_bitsink(namestring_1)
    Object namestring_1;
{
    Object temp;

    x_note_fn_call(1,22);
    temp = make_broadcast_stream(0);
    return VALUES_2(temp,Nil);
}

/* SUPPORTS-EDITOR-STREAM-P */
Object g2int_supports_editor_stream_p()
{
    x_note_fn_call(1,23);
    return VALUES_1(Nil);
}

Object G2int_g2_operating_system = UNBOUND;

Object G2int_g2_machine_type = UNBOUND;

Object G2int_machine_model_var = UNBOUND;

static Object Qg2int_aviion;       /* aviion */

static Object string_constant_2;   /* " Data General AViiON" */

static Object Qmotorola;           /* motorola */

static Object string_constant_3;   /* " Motorola 88000" */

static Object Qg2int_next;         /* next */

static Object string_constant_4;   /* " NeXT" */

static Object Qsgi;                /* sgi */

static Object string_constant_5;   /* " Silicon Graphics" */

static Object Qsequent;            /* sequent */

static Object string_constant_6;   /* " Sequent" */

static Object Qg2int_decstation;   /* decstation */

static Object string_constant_7;   /* " DECstation" */

static Object Qg2int_masscomp;     /* masscomp */

static Object string_constant_8;   /* " Concurrent 6000s" */

static Object Qhp9000s300;         /* hp9000s300 */

static Object string_constant_9;   /* " HP9000/300s" */

static Object Qhp9000s400;         /* hp9000s400 */

static Object string_constant_10;  /* " HP9000/400s" */

static Object Qg2int_hp9000s700;   /* hp9000s700 */

static Object string_constant_11;  /* " PA-RISC HP-UX" */

static Object Qhp9000s800;         /* hp9000s800 */

static Object string_constant_12;  /* " HP9000/800s" */

static Object Qg2int_i386;         /* i386 */

static Object Qcompaq;             /* compaq */

static Object string_constant_13;  /* " '386" */

static Object Qg2int_rs6000;       /* rs6000 */

static Object string_constant_14;  /* " IBM POWERstation" */

static Object Qsun3;               /* sun3 */

static Object string_constant_15;  /* " Sun 3" */

static Object Qg2int_vms;          /* vms */

static Object string_constant_16;  /* " Vax VMS" */

static Object Qalphavms;           /* alphavms */

static Object string_constant_17;  /* " DEC Alpha AXP/OpenVMS" */

static Object Qg2int_sparcsol;     /* sparcsol */

static Object string_constant_18;  /* " Sun 4/SPARCstation Solaris" */

static Object Qg2int_intelsol;     /* intelsol */

static Object string_constant_19;  /* " x86 Solaris" */

static Object Qsun4;               /* sun4 */

static Object string_constant_20;  /* " Sun 4/SPARCstation" */

static Object Qharris;             /* harris */

static Object string_constant_21;  /* " Harris Night Hawk" */

static Object Qstratus;            /* stratus */

static Object string_constant_22;  /* " Stratus FTX" */

static Object Qnec;                /* nec */

static Object string_constant_23;  /* " NEC EWS4800 Series" */

static Object Qg2int_alphaosf;     /* alphaosf */

static Object string_constant_24;  /* " DEC OSF/1 AXP" */

static Object Qg2int_alphant;      /* alphant */

static Object string_constant_25;  /* " Alpha NT" */

static Object Qg2int_intelnt;      /* intelnt */

static Object string_constant_26;  /* " Windows" */

static Object Qg2int_dos;          /* dos */

static Object string_constant_27;  /* " MS Windows 3.1" */

static Object Qncr;                /* ncr */

static Object string_constant_28;  /* " NCR 386/486" */

static Object Qg2int_windows95;    /* windows95 */

static Object string_constant_29;  /* " Windows 95/98" */

static Object Qg2int_linux;        /* linux */

static Object string_constant_30;  /* " Linux" */

static Object Qmac;                /* mac */

static Object string_constant_31;  /* " Mac OS X" */

static Object Qhpia64;             /* hpia64 */

static Object string_constant_32;  /* " Itanium HP-UX" */

static Object string_constant_33;  /* " Experimental Port" */

/* MACHINE-MODEL */
Object g2int_machine_model()
{
    x_note_fn_call(1,24);
    if (G2int_machine_model_var)
	return VALUES_1(G2int_machine_model_var);
    else {
	if (EQ(G2int_g2_machine_type,Qg2int_aviion))
	    G2int_machine_model_var = string_constant_2;
	else if (EQ(G2int_g2_machine_type,Qmotorola))
	    G2int_machine_model_var = string_constant_3;
	else if (EQ(G2int_g2_machine_type,Qg2int_next))
	    G2int_machine_model_var = string_constant_4;
	else if (EQ(G2int_g2_machine_type,Qsgi))
	    G2int_machine_model_var = string_constant_5;
	else if (EQ(G2int_g2_machine_type,Qsequent))
	    G2int_machine_model_var = string_constant_6;
	else if (EQ(G2int_g2_machine_type,Qg2int_decstation))
	    G2int_machine_model_var = string_constant_7;
	else if (EQ(G2int_g2_machine_type,Qg2int_masscomp))
	    G2int_machine_model_var = string_constant_8;
	else if (EQ(G2int_g2_machine_type,Qhp9000s300))
	    G2int_machine_model_var = string_constant_9;
	else if (EQ(G2int_g2_machine_type,Qhp9000s400))
	    G2int_machine_model_var = string_constant_10;
	else if (EQ(G2int_g2_machine_type,Qg2int_hp9000s700))
	    G2int_machine_model_var = string_constant_11;
	else if (EQ(G2int_g2_machine_type,Qhp9000s800))
	    G2int_machine_model_var = string_constant_12;
	else if (EQ(G2int_g2_machine_type,Qg2int_i386) || 
		EQ(G2int_g2_machine_type,Qcompaq))
	    G2int_machine_model_var = string_constant_13;
	else if (EQ(G2int_g2_machine_type,Qg2int_rs6000))
	    G2int_machine_model_var = string_constant_14;
	else if (EQ(G2int_g2_machine_type,Qsun3))
	    G2int_machine_model_var = string_constant_15;
	else if (EQ(G2int_g2_machine_type,Qg2int_vms))
	    G2int_machine_model_var = string_constant_16;
	else if (EQ(G2int_g2_machine_type,Qalphavms))
	    G2int_machine_model_var = string_constant_17;
	else if (EQ(G2int_g2_machine_type,Qg2int_sparcsol))
	    G2int_machine_model_var = string_constant_18;
	else if (EQ(G2int_g2_machine_type,Qg2int_intelsol))
	    G2int_machine_model_var = string_constant_19;
	else if (EQ(G2int_g2_machine_type,Qsun4))
	    G2int_machine_model_var = string_constant_20;
	else if (EQ(G2int_g2_machine_type,Qharris))
	    G2int_machine_model_var = string_constant_21;
	else if (EQ(G2int_g2_machine_type,Qstratus))
	    G2int_machine_model_var = string_constant_22;
	else if (EQ(G2int_g2_machine_type,Qnec))
	    G2int_machine_model_var = string_constant_23;
	else if (EQ(G2int_g2_machine_type,Qg2int_alphaosf))
	    G2int_machine_model_var = string_constant_24;
	else if (EQ(G2int_g2_machine_type,Qg2int_alphant))
	    G2int_machine_model_var = string_constant_25;
	else if (EQ(G2int_g2_machine_type,Qg2int_intelnt))
	    G2int_machine_model_var = string_constant_26;
	else if (EQ(G2int_g2_machine_type,Qg2int_dos))
	    G2int_machine_model_var = string_constant_27;
	else if (EQ(G2int_g2_machine_type,Qncr))
	    G2int_machine_model_var = string_constant_28;
	else if (EQ(G2int_g2_machine_type,Qg2int_windows95))
	    G2int_machine_model_var = string_constant_29;
	else if (EQ(G2int_g2_machine_type,Qg2int_linux))
	    G2int_machine_model_var = string_constant_30;
	else if (EQ(G2int_g2_machine_type,Qmac))
	    G2int_machine_model_var = string_constant_31;
	else if (EQ(G2int_g2_machine_type,Qhpia64))
	    G2int_machine_model_var = string_constant_32;
	else
	    G2int_machine_model_var = string_constant_33;
	return VALUES_1(G2int_machine_model_var);
    }
}

Object G2int_do_not_load_modules_p = UNBOUND;

Object G2int_making_distribution_systemqm = UNBOUND;

/* DIRECTORY-FOR-BOOTSTRAP */
Object g2int_directory_for_bootstrap(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(1,25);
    return VALUES_1(pathname_1);
}

/* NEW-DIRECTORY-FOR-BOOTSTRAP */
Object g2int_new_directory_for_bootstrap(pathname_1)
    Object pathname_1;
{
    Object list0, result_1, last_1, temp, new_last;

    x_note_fn_call(1,26);
    list0 = pathname_1;
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

static Object Qg2int_launch_functionqm;  /* launch-function? */

/* LAUNCH-SYSTEM */
Object g2int_launch_system(system_1)
    Object system_1;
{
    Object launch_function_qm;

    x_note_fn_call(1,27);
    launch_function_qm = get(system_1,Qg2int_launch_functionqm,_);
    if (launch_function_qm)
	return FUNCALL_0(launch_function_qm);
    else
	return format((SI_Long)3L,T,"Unable to launch system ~a.",system_1);
}

/* ADD-TO-DIRECTORY-LIST-FOR-BOOTSTRAPPING */
Object g2int_add_to_directory_list_for_bootstrapping(truename_1,
	    directory_list_special_variable)
    Object truename_1, directory_list_special_variable;
{
    Object temp;

    x_note_fn_call(1,28);
    temp = g2int_new_directory_for_bootstrap(truename_1);
    return set(directory_list_special_variable,nconc2(temp,
	    SYMBOL_VALUE(directory_list_special_variable)));
}

Object G2int_all_modules_of_all_systems = UNBOUND;

static Object string_constant_34;  /* "BAD GSI MODULE" */

/* NORMALIZE-MODULE-NAME-OR-DESCRIPTION */
Object g2int_normalize_module_name_or_description(module_name_or_description)
    Object module_name_or_description;
{
    Object gensymed_symbol, temp, internable_string;

    x_note_fn_call(1,29);
    if (CONSP(module_name_or_description)) {
	gensymed_symbol = CAR(module_name_or_description);
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		G2int_ab_package_1))
	    temp = gensymed_symbol;
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else
		internable_string = string_constant_34;
	    temp = intern(internable_string,G2int_ab_package_1);
	}
	M_CAR(module_name_or_description) = temp;
	return VALUES_1(module_name_or_description);
    }
    else {
	gensymed_symbol = module_name_or_description;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		G2int_ab_package_1))
	    return VALUES_1(gensymed_symbol);
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else
		internable_string = string_constant_34;
	    temp = intern(internable_string,G2int_ab_package_1);
	    return VALUES_1(temp);
	}
    }
}

/* INSTALL-ALL-FILE-PROPERTIES-FROM-ALIST */
Object g2int_install_all_file_properties_from_alist(file_symbol,file_class,
	    system_1,file_properties_alist)
    Object file_symbol, file_class, system_1, file_properties_alist;
{
    Object property_name, property_value, tail, property_description;

    x_note_fn_call(1,30);
    property_name = Nil;
    property_value = Nil;
    tail = file_properties_alist;
    property_description = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	property_description = CAR(tail);
	property_name = FIRST(property_description);
	property_value = SECOND(property_description);
	g2int_set_file_property(file_symbol,file_class,system_1,
		property_name,property_value);
    }
    return VALUES_1(Nil);
}

static Object Kinclude_test_for_compile;  /* :include-test-for-compile */

static Object Kinclude_test_for_load;  /* :include-test-for-load */

static Object Kinclude_test_for_update;  /* :include-test-for-update */

static Object list_constant;       /* # */

/* INSTALL-ALL-FILE-PROPERTIES-FROM-PLIST */
Object g2int_install_all_file_properties_from_plist(file_symbol,file_class,
	    system_1,file_properties_plist)
    Object file_symbol, file_class, system_1, file_properties_plist;
{
    Object property_name, property_value, rest_of_plist;

    x_note_fn_call(1,31);
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
	    property_value = list_constant;
	g2int_set_file_property(file_symbol,file_class,system_1,
		property_name,property_value);
    }
    return VALUES_1(Nil);
}

/* MAKE-AN-ALIST-OF-FILE-PROPERTY-DEFAULTS */
Object g2int_make_an_alist_of_file_property_defaults(fcd_alist_of_file_property_defaults)
    Object fcd_alist_of_file_property_defaults;
{
    Object file_property_defaults_alist, property_1, base_default, override;
    Object default_1, tail, property_description, push_arg;

    x_note_fn_call(1,32);
    file_property_defaults_alist = Nil;
    property_1 = Nil;
    base_default = Nil;
    override = Nil;
    default_1 = Nil;
    tail = G2int_alist_of_file_property_base_defaults;
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
Object g2int_install_file_properties_for_file_name_or_description(file_name_or_description,
	    file_class,system_1,file_property_defaults_alist)
    Object file_name_or_description, file_class, system_1;
    Object file_property_defaults_alist;
{
    Object file_symbol, plist_of_properties;

    x_note_fn_call(1,33);
    if (CONSP(file_name_or_description)) {
	file_symbol = CAR(file_name_or_description);
	plist_of_properties = CDR(file_name_or_description);
	g2int_install_all_file_properties_from_alist(file_symbol,
		file_class,system_1,file_property_defaults_alist);
	g2int_install_all_file_properties_from_plist(file_symbol,
		file_class,system_1,plist_of_properties);
	return VALUES_1(file_symbol);
    }
    else {
	g2int_install_all_file_properties_from_alist(file_name_or_description,
		file_class,system_1,file_property_defaults_alist);
	return VALUES_1(file_name_or_description);
    }
}

static Object Qg2int_lisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

/* INSTALL-FILE-PROPERTIES-FOR-SYSTEM */
Object g2int_install_file_properties_for_system(file_names_or_descriptions_qm,
	    file_class,system_1,fcd_alist_of_file_property_defaults)
    Object file_names_or_descriptions_qm, file_class, system_1;
    Object fcd_alist_of_file_property_defaults;
{
    Object file_symbol, list_of_file_symbols, file_property_defaults_alist;
    Object tail, file_name_or_description, push_arg, temp, get_new_value;

    x_note_fn_call(1,34);
    if (file_names_or_descriptions_qm) {
	file_symbol = Nil;
	list_of_file_symbols = Nil;
	file_property_defaults_alist = 
		g2int_make_an_alist_of_file_property_defaults(fcd_alist_of_file_property_defaults);
	tail = file_names_or_descriptions_qm;
	file_name_or_description = Nil;
	for ( ; !ENDP(tail); tail = CDR(tail)) {
	    file_name_or_description = CAR(tail);
	    file_symbol = 
		    g2int_install_file_properties_for_file_name_or_description(file_name_or_description,
		    file_class,system_1,file_property_defaults_alist);
	    if (g2int_eval_feature(g2int_get_default_include_test(file_symbol,
		    file_class,system_1,Kinclude_test_for_load))) {
		push_arg = file_symbol;
		temp = get(system_1,Qg2int_lisp_modules_to_be_loaded,Nil);
		get_new_value = CONS(push_arg,temp);
		set_get(system_1,Qg2int_lisp_modules_to_be_loaded,
			get_new_value);
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
Object g2int_stable_list_union(list_1,list_2)
    Object list_1, list_2;
{
    Object result_1;

    x_note_fn_call(1,35);
    result_1 = append2(list_1,list_2);
    return remove_duplicates(1,result_1);
}

static Object Kdevelopment;        /* :development */

static Object Kstandard_module_index;  /* :standard-module-index */

static Object Qg2int_alias;        /* alias */

static Object Qg2int_nicknames;    /* nicknames */

static Object Qg2int_system_pathname;  /* system-pathname */

static Object Qg2int_system_package_name;  /* system-package-name */

static Object Qg2int_lisp_source_type;  /* lisp-source-type */

static Object Qg2int_lisp_binary_type;  /* lisp-binary-type */

static Object Qg2int_kb_type;      /* kb-type */

static Object Qg2int_kl_type;      /* kl-type */

static Object Qg2int_systems_to_share_binary_files_with;  /* systems-to-share-binary-files-with */

static Object Qg2int_system_is_windowless_p;  /* system-is-windowless-p */

static Object Qg2int_system_alias;  /* system-alias */

static Object Qg2int_real_system_name;  /* real-system-name */

static Object Qg2int_system_lisp_source_files;  /* system-lisp-source-files */

static Object Qg2int_system_lisp_source_type;  /* system-lisp-source-type */

static Object Qg2int_system_lisp_binary_type;  /* system-lisp-binary-type */

static Object Qg2int_system_kb_type;  /* system-kb-type */

static Object Qg2int_system_kl_type;  /* system-kl-type */

/* DECLARE-SYSTEM-1 */
Object g2int_declare_system_1 varargs_1(int, n)
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

    x_note_fn_call(1,36);
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
    alias = getf(options,Qg2int_alias,_);
    if (alias);
    else
	alias = Nil;
    nicknames = getf(options,Qg2int_nicknames,_);
    if (nicknames);
    else
	nicknames = Nil;
    system_pathname = getf(options,Qg2int_system_pathname,_);
    if (system_pathname);
    else
	system_pathname = Nil;
    system_package_name = getf(options,Qg2int_system_package_name,_);
    if (system_package_name);
    else
	system_package_name = system_1;
    lisp_source_type = getf(options,Qg2int_lisp_source_type,_);
    if (lisp_source_type);
    else
	lisp_source_type = SECOND(G2int_bootstrap_information);
    lisp_binary_type = getf(options,Qg2int_lisp_binary_type,_);
    if (lisp_binary_type);
    else
	lisp_binary_type = FIRST(G2int_bootstrap_information);
    kb_type = getf(options,Qg2int_kb_type,_);
    if (kb_type);
    else
	kb_type = THIRD(G2int_bootstrap_information);
    kl_type = getf(options,Qg2int_kl_type,_);
    if (kl_type);
    else
	kl_type = FOURTH(G2int_bootstrap_information);
    systems_to_share_binary_files_with_qm = getf(options,
	    Qg2int_systems_to_share_binary_files_with,_);
    system_is_windowless_p = getf(options,Qg2int_system_is_windowless_p,_);
    system_pathname = system_pathname ? G2int_ab_system_pathname : 
	    G2int_ab_system_pathname;
    set_get(system_1,Qg2int_system_alias,alias);
    set_get(system_1,Qg2int_systems_to_share_binary_files_with,
	    systems_to_share_binary_files_with_qm);
    tail = nicknames;
    nickname = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	nickname = CAR(tail);
	gensymed_symbol = nickname;
	if (SYMBOLP(gensymed_symbol) && EQ(SYMBOL_PACKAGE(gensymed_symbol),
		G2int_ab_package_1))
	    temp = gensymed_symbol;
	else {
	    if (SYMBOLP(gensymed_symbol))
		internable_string = SYMBOL_NAME(gensymed_symbol);
	    else if (STRINGP(gensymed_symbol))
		internable_string = gensymed_symbol;
	    else
		internable_string = string_constant_34;
	    temp = intern(internable_string,G2int_ab_package_1);
	}
	set_get(temp,Qg2int_real_system_name,system_1);
    }
    file_class = Nil;
    file_class_indicator = Nil;
    file_class_module_property_defaults = Nil;
    tail = G2int_alist_of_system_file_class_descriptions;
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
	    temp = g2int_normalize_module_name_or_description(CAR(list0));
	    new_last = CONS(temp,Nil);
	    if (result_1)
		M_CDR(last_1) = new_last;
	    else
		result_1 = new_last;
	    last_1 = new_last;
	}
	temp = result_1;
	get_new_value = g2int_install_file_properties_for_system(temp,
		file_class,system_1,file_class_module_property_defaults);
	set_get(system_1,file_class_indicator,get_new_value);
    }
    set_get(system_1,Qg2int_lisp_modules_to_be_loaded,Nil);
    file_class = Qg2int_system_lisp_source_files;
    file_class_description = assoc_eql(file_class,
	    G2int_alist_of_system_file_class_descriptions);
    file_class_indicator = SECOND(file_class_description);
    file_class_module_property_defaults = THIRD(file_class_description);
    temp = get(system_1,file_class_indicator,_);
    get_new_value = g2int_stable_list_union(temp,
	    g2int_install_file_properties_for_system(file_names_or_descriptions,
	    file_class,system_1,file_class_module_property_defaults));
    set_get(system_1,file_class_indicator,get_new_value);
    get_new_value = nreverse(get(system_1,Qg2int_lisp_modules_to_be_loaded,_));
    set_get(system_1,Qg2int_lisp_modules_to_be_loaded,get_new_value);
    set_get(system_1,Qg2int_system_lisp_source_type,lisp_source_type);
    set_get(system_1,Qg2int_system_lisp_binary_type,lisp_binary_type);
    set_get(system_1,Qg2int_system_kb_type,kb_type);
    set_get(system_1,Qg2int_system_kl_type,kl_type);
    set_get(system_1,Qg2int_system_pathname,system_pathname);
    set_get(system_1,Qg2int_system_package_name,system_package_name);
    result = set_get(system_1,Qg2int_system_is_windowless_p,
	    system_is_windowless_p);
    RESTORE_STACK();
    return result;
}

void bootstrap_INIT()
{
    Object get_new_value;
    SI_Long platform_code;
    Object AB_package, Qg2int_local_platform_specific_directory;
    Object Qexperimental_port, Qg2int_sparcstation, Qg2int_unix, Qg2int_win32;
    Object Qg2int_intelsol_code, Qg2int_hpia_code, Qg2int_mac_code;
    Object Qg2int_linux_code, Qg2int_windows95_code, Qg2int_ncr_code;
    Object Qg2int_intelnt_code, Qg2int_alphant_code, Qg2int_alphaosf_code;
    Object Qg2int_nec_code, Qg2int_harris_code, Qg2int_stratus_code;
    Object Qg2int_vms_code, Qg2int_motorola_code, Qg2int_alphavms_code;
    Object Qg2int_sparcsol_code, Qg2int_sun4_code, Qg2int_sun3_code;
    Object Qg2int_rs6000_code, Qg2int_hp9000s800_code, Qg2int_hp9000s700_code;
    Object Qg2int_hp9000s400_code, Qg2int_hp9000s300_code;
    Object Qg2int_masscomp_code, Qg2int_decstation_code, Qg2int_next_code;
    Object Qg2int_sequent_code, Qg2int_sgi_code, Qg2int_aviion_code;
    Object Qg2int_dos_code, Qg2int_i386_code, Qg2int_release_quality;
    Object Qg2int_beta_release_quality, Qg2int_alpha_release_quality;
    Object Qg2int_prototype_release_quality, string_constant_35;
    Object Qg2int_most_positive_gensym_float;
    Object Qg2int_most_negative_gensym_float, float_constant;
    Object Qg2int_least_positive_normalized_gensym_float;

    x_note_fn_call(1,37);
    SET_PACKAGE("AB");
    G2int_allow_development_compile_p = T;
    if (G2int_current_system_being_loaded == UNBOUND)
	G2int_current_system_being_loaded = Nil;
    if (G2int_override_eliminate_for_gsi_p == UNBOUND)
	G2int_override_eliminate_for_gsi_p = Nil;
    if (G2int_override_eliminate_for_gsi_no_utf_g_p == UNBOUND)
	G2int_override_eliminate_for_gsi_no_utf_g_p = T;
    if (G2int_macroexpanding_for_instruction_expander == UNBOUND)
	G2int_macroexpanding_for_instruction_expander = Nil;
    Kchestnut_3 = STATIC_SYMBOL("CHESTNUT-3",Pkeyword);
    string_constant = STATIC_STRING("GENSYMED-SYMBOL");
    if (G2int_most_recent_defun_warned_for_catchqm == UNBOUND)
	G2int_most_recent_defun_warned_for_catchqm = Nil;
    if (G2int_most_recent_defun_warned_for_unwind_protectqm == UNBOUND)
	G2int_most_recent_defun_warned_for_unwind_protectqm = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_string_or_symbol_equal = STATIC_SYMBOL("STRING-OR-SYMBOL-EQUAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_string_or_symbol_equal,
	    STATIC_FUNCTION(g2int_string_or_symbol_equal,NIL,FALSE,2,2));
    Qg2int_or = STATIC_SYMBOL("OR",AB_package);
    if (G2int_current_moduleqm == UNBOUND)
	G2int_current_moduleqm = Nil;
    Load_pathname = SEVENTH(G2int_bootstrap_information);
    if (G2int_use_directory_lists_for_bootstrappingqm == UNBOUND)
	G2int_use_directory_lists_for_bootstrappingqm = Nil;
    if (G2int_last_bootstrap_modeqm == UNBOUND)
	G2int_last_bootstrap_modeqm = Nil;
    Qg2int_least_positive_normalized_gensym_float = 
	    STATIC_SYMBOL("LEAST-POSITIVE-NORMALIZED-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_least_positive_normalized_gensym_float,
	    G2int_least_positive_normalized_gensym_float);
    float_constant = STATIC_FLOAT(2.2250738585072014E-308);
    SET_SYMBOL_VALUE(Qg2int_least_positive_normalized_gensym_float,
	    float_constant);
    Qg2int_most_negative_gensym_float = 
	    STATIC_SYMBOL("MOST-NEGATIVE-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_negative_gensym_float,
	    G2int_most_negative_gensym_float);
    SET_SYMBOL_VALUE(Qg2int_most_negative_gensym_float,
	    Most_negative_double_float);
    Qg2int_most_positive_gensym_float = 
	    STATIC_SYMBOL("MOST-POSITIVE-GENSYM-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_positive_gensym_float,
	    G2int_most_positive_gensym_float);
    SET_SYMBOL_VALUE(Qg2int_most_positive_gensym_float,
	    Most_positive_double_float);
    string_constant_35 = STATIC_STRING("AB");
    if (G2int_ab_package_1 == UNBOUND)
	G2int_ab_package_1 = find_package(string_constant_35);
    if (G2int_all_systems == UNBOUND)
	G2int_all_systems = Nil;
    G2int_null_io = make_broadcast_stream(0);
    if (G2int_filename_of_module_being_loadedqm == UNBOUND)
	G2int_filename_of_module_being_loadedqm = Nil;
    G2int_alist_of_file_property_base_defaults = Nil;
    Koverriding_include_test = STATIC_SYMBOL("OVERRIDING-INCLUDE-TEST",
	    Pkeyword);
    Koptional_module_p = STATIC_SYMBOL("OPTIONAL-MODULE-P",Pkeyword);
    Qg2int_optional_modules = STATIC_SYMBOL("OPTIONAL-MODULES",AB_package);
    Kmaster_directory_namestring = 
	    STATIC_SYMBOL("MASTER-DIRECTORY-NAMESTRING",Pkeyword);
    Qg2int_master_source_directory = 
	    STATIC_SYMBOL("MASTER-SOURCE-DIRECTORY",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Klocal_directory_namestring = 
	    STATIC_SYMBOL("LOCAL-DIRECTORY-NAMESTRING",Pkeyword);
    Qg2int_local_source_directory = STATIC_SYMBOL("LOCAL-SOURCE-DIRECTORY",
	    AB_package);
    Kmaster_pathname_name = STATIC_SYMBOL("MASTER-PATHNAME-NAME",Pkeyword);
    Klocal_pathname_name = STATIC_SYMBOL("LOCAL-PATHNAME-NAME",Pkeyword);
    Kbinary_pathname_name = STATIC_SYMBOL("BINARY-PATHNAME-NAME",Pkeyword);
    Kmaster_file_type = STATIC_SYMBOL("MASTER-FILE-TYPE",Pkeyword);
    Kdefault_file_type = STATIC_SYMBOL("DEFAULT-FILE-TYPE",Pkeyword);
    string_constant_1 = STATIC_STRING("");
    Klocal_file_type = STATIC_SYMBOL("LOCAL-FILE-TYPE",Pkeyword);
    Kbinary_file_type = STATIC_SYMBOL("BINARY-FILE-TYPE",Pkeyword);
    Kmaintained_as_a_binary_file_p = 
	    STATIC_SYMBOL("MAINTAINED-AS-A-BINARY-FILE-P",Pkeyword);
    Kno_lisp_binary_produced_p = STATIC_SYMBOL("NO-LISP-BINARY-PRODUCED-P",
	    Pkeyword);
    G2int_alist_of_system_file_class_descriptions = Nil;
    Qg2int_prototype_release_quality = 
	    STATIC_SYMBOL("PROTOTYPE-RELEASE-QUALITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_prototype_release_quality,FIX((SI_Long)0L));
    Qg2int_alpha_release_quality = STATIC_SYMBOL("ALPHA-RELEASE-QUALITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_alpha_release_quality,FIX((SI_Long)1L));
    Qg2int_beta_release_quality = STATIC_SYMBOL("BETA-RELEASE-QUALITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_beta_release_quality,FIX((SI_Long)2L));
    Qg2int_release_quality = STATIC_SYMBOL("RELEASE-QUALITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_quality,FIX((SI_Long)3L));
    Qg2int_alpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    Qg2int_brief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    Qg2int_patch_level = STATIC_SYMBOL("PATCH-LEVEL",AB_package);
    Qg2int_system_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    Qg2int_i386_code = STATIC_SYMBOL("I386-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_i386_code,FIX((SI_Long)1L));
    Qg2int_dos_code = STATIC_SYMBOL("DOS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dos_code,FIX((SI_Long)2L));
    Qg2int_aviion_code = STATIC_SYMBOL("AVIION-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_aviion_code,FIX((SI_Long)3L));
    Qg2int_sgi_code = STATIC_SYMBOL("SGI-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sgi_code,FIX((SI_Long)4L));
    Qg2int_sequent_code = STATIC_SYMBOL("SEQUENT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sequent_code,FIX((SI_Long)5L));
    Qg2int_next_code = STATIC_SYMBOL("NEXT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_next_code,FIX((SI_Long)6L));
    Qg2int_decstation_code = STATIC_SYMBOL("DECSTATION-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_decstation_code,FIX((SI_Long)7L));
    Qg2int_masscomp_code = STATIC_SYMBOL("MASSCOMP-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_masscomp_code,FIX((SI_Long)8L));
    Qg2int_hp9000s300_code = STATIC_SYMBOL("HP9000S300-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hp9000s300_code,FIX((SI_Long)9L));
    Qg2int_hp9000s400_code = STATIC_SYMBOL("HP9000S400-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hp9000s400_code,FIX((SI_Long)10L));
    Qg2int_hp9000s700_code = STATIC_SYMBOL("HP9000S700-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hp9000s700_code,FIX((SI_Long)11L));
    Qg2int_hp9000s800_code = STATIC_SYMBOL("HP9000S800-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hp9000s800_code,FIX((SI_Long)12L));
    Qg2int_rs6000_code = STATIC_SYMBOL("RS6000-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_rs6000_code,FIX((SI_Long)13L));
    Qg2int_sun3_code = STATIC_SYMBOL("SUN3-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sun3_code,FIX((SI_Long)14L));
    Qg2int_sun4_code = STATIC_SYMBOL("SUN4-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sun4_code,FIX((SI_Long)15L));
    Qg2int_sparcsol_code = STATIC_SYMBOL("SPARCSOL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_sparcsol_code,FIX((SI_Long)16L));
    Qg2int_alphavms_code = STATIC_SYMBOL("ALPHAVMS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_alphavms_code,FIX((SI_Long)17L));
    Qg2int_motorola_code = STATIC_SYMBOL("MOTOROLA-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_motorola_code,FIX((SI_Long)18L));
    Qg2int_vms_code = STATIC_SYMBOL("VMS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_vms_code,FIX((SI_Long)19L));
    Qg2int_stratus_code = STATIC_SYMBOL("STRATUS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_stratus_code,FIX((SI_Long)20L));
    Qg2int_harris_code = STATIC_SYMBOL("HARRIS-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_harris_code,FIX((SI_Long)21L));
    Qg2int_nec_code = STATIC_SYMBOL("NEC-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nec_code,FIX((SI_Long)22L));
    Qg2int_alphaosf_code = STATIC_SYMBOL("ALPHAOSF-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_alphaosf_code,FIX((SI_Long)23L));
    Qg2int_alphant_code = STATIC_SYMBOL("ALPHANT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_alphant_code,FIX((SI_Long)24L));
    Qg2int_intelnt_code = STATIC_SYMBOL("INTELNT-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_intelnt_code,FIX((SI_Long)25L));
    Qg2int_ncr_code = STATIC_SYMBOL("NCR-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_ncr_code,FIX((SI_Long)26L));
    Qg2int_windows95_code = STATIC_SYMBOL("WINDOWS95-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_windows95_code,FIX((SI_Long)27L));
    Qg2int_linux_code = STATIC_SYMBOL("LINUX-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_linux_code,FIX((SI_Long)28L));
    Qg2int_mac_code = STATIC_SYMBOL("MAC-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_mac_code,FIX((SI_Long)29L));
    Qg2int_hpia_code = STATIC_SYMBOL("HPIA-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_hpia_code,FIX((SI_Long)30L));
    Qg2int_intelsol_code = STATIC_SYMBOL("INTELSOL-CODE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_intelsol_code,FIX((SI_Long)31L));
    Qg2int_unix = STATIC_SYMBOL("UNIX",AB_package);
    Qg2int_dos = STATIC_SYMBOL("DOS",AB_package);
    Qg2int_vms = STATIC_SYMBOL("VMS",AB_package);
    Qg2int_win32 = STATIC_SYMBOL("WIN32",AB_package);
    if (G2int_g2_operating_system == UNBOUND) {
	platform_code = g2ext_get_platform_code();
	if ( !((SI_Long)-128L <= platform_code && platform_code <= 
		(SI_Long)127L)) {
	    format((SI_Long)3L,T,
		    "Unknown platform code ~a, assuming UNIX o/s",
		    FIX(platform_code));
	    G2int_g2_operating_system = Qg2int_unix;
	}
	else
	    switch ((char)platform_code) {
	      case 1:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 2:
		G2int_g2_operating_system = Qg2int_dos;
		break;
	      case 3:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 4:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 5:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 6:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 7:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 8:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 9:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 10:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 11:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 12:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 13:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 14:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 15:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 16:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 31:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 17:
		G2int_g2_operating_system = Qg2int_vms;
		break;
	      case 18:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 19:
		G2int_g2_operating_system = Qg2int_vms;
		break;
	      case 20:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 21:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 22:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 23:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 24:
		G2int_g2_operating_system = Qg2int_win32;
		break;
	      case 25:
		G2int_g2_operating_system = Qg2int_win32;
		break;
	      case 26:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 27:
		G2int_g2_operating_system = Qg2int_win32;
		break;
	      case 28:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 29:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      case 30:
		G2int_g2_operating_system = Qg2int_unix;
		break;
	      default:
		format((SI_Long)3L,T,
			"Unknown platform code ~a, assuming UNIX o/s",
			FIX(platform_code));
		G2int_g2_operating_system = Qg2int_unix;
		break;
	    }
    }
    Qexperimental_port = STATIC_SYMBOL("EXPERIMENTAL-PORT",AB_package);
    Qg2int_i386 = STATIC_SYMBOL("I386",AB_package);
    Qg2int_aviion = STATIC_SYMBOL("AVIION",AB_package);
    Qsgi = STATIC_SYMBOL("SGI",AB_package);
    Qsequent = STATIC_SYMBOL("SEQUENT",AB_package);
    Qg2int_next = STATIC_SYMBOL("NEXT",AB_package);
    Qg2int_decstation = STATIC_SYMBOL("DECSTATION",AB_package);
    Qg2int_masscomp = STATIC_SYMBOL("MASSCOMP",AB_package);
    Qhp9000s300 = STATIC_SYMBOL("HP9000S300",AB_package);
    Qhp9000s400 = STATIC_SYMBOL("HP9000S400",AB_package);
    Qg2int_hp9000s700 = STATIC_SYMBOL("HP9000S700",AB_package);
    Qhp9000s800 = STATIC_SYMBOL("HP9000S800",AB_package);
    Qg2int_rs6000 = STATIC_SYMBOL("RS6000",AB_package);
    Qsun3 = STATIC_SYMBOL("SUN3",AB_package);
    Qg2int_sparcstation = STATIC_SYMBOL("SPARCSTATION",AB_package);
    Qg2int_sparcsol = STATIC_SYMBOL("SPARCSOL",AB_package);
    Qg2int_intelsol = STATIC_SYMBOL("INTELSOL",AB_package);
    Qalphavms = STATIC_SYMBOL("ALPHAVMS",AB_package);
    Qmotorola = STATIC_SYMBOL("MOTOROLA",AB_package);
    Qstratus = STATIC_SYMBOL("STRATUS",AB_package);
    Qharris = STATIC_SYMBOL("HARRIS",AB_package);
    Qnec = STATIC_SYMBOL("NEC",AB_package);
    Qg2int_alphaosf = STATIC_SYMBOL("ALPHAOSF",AB_package);
    Qg2int_alphant = STATIC_SYMBOL("ALPHANT",AB_package);
    Qg2int_intelnt = STATIC_SYMBOL("INTELNT",AB_package);
    Qncr = STATIC_SYMBOL("NCR",AB_package);
    Qg2int_windows95 = STATIC_SYMBOL("WINDOWS95",AB_package);
    Qg2int_linux = STATIC_SYMBOL("LINUX",AB_package);
    Qmac = STATIC_SYMBOL("MAC",AB_package);
    Qhpia64 = STATIC_SYMBOL("HPIA64",AB_package);
    if (G2int_g2_machine_type == UNBOUND) {
	platform_code = g2ext_get_platform_code();
	if ( !((SI_Long)-128L <= platform_code && platform_code <= 
		(SI_Long)127L))
	    G2int_g2_machine_type = Qexperimental_port;
	else
	    switch ((char)platform_code) {
	      case 1:
		G2int_g2_machine_type = Qg2int_i386;
		break;
	      case 2:
		G2int_g2_machine_type = Qg2int_dos;
		break;
	      case 3:
		G2int_g2_machine_type = Qg2int_aviion;
		break;
	      case 4:
		G2int_g2_machine_type = Qsgi;
		break;
	      case 5:
		G2int_g2_machine_type = Qsequent;
		break;
	      case 6:
		G2int_g2_machine_type = Qg2int_next;
		break;
	      case 7:
		G2int_g2_machine_type = Qg2int_decstation;
		break;
	      case 8:
		G2int_g2_machine_type = Qg2int_masscomp;
		break;
	      case 9:
		G2int_g2_machine_type = Qhp9000s300;
		break;
	      case 10:
		G2int_g2_machine_type = Qhp9000s400;
		break;
	      case 11:
		G2int_g2_machine_type = Qg2int_hp9000s700;
		break;
	      case 12:
		G2int_g2_machine_type = Qhp9000s800;
		break;
	      case 13:
		G2int_g2_machine_type = Qg2int_rs6000;
		break;
	      case 14:
		G2int_g2_machine_type = Qsun3;
		break;
	      case 15:
		G2int_g2_machine_type = Qg2int_sparcstation;
		break;
	      case 16:
		G2int_g2_machine_type = Qg2int_sparcsol;
		break;
	      case 31:
		G2int_g2_machine_type = Qg2int_intelsol;
		break;
	      case 17:
		G2int_g2_machine_type = Qalphavms;
		break;
	      case 18:
		G2int_g2_machine_type = Qmotorola;
		break;
	      case 19:
		G2int_g2_machine_type = Qg2int_vms;
		break;
	      case 20:
		G2int_g2_machine_type = Qstratus;
		break;
	      case 21:
		G2int_g2_machine_type = Qharris;
		break;
	      case 22:
		G2int_g2_machine_type = Qnec;
		break;
	      case 23:
		G2int_g2_machine_type = Qg2int_alphaosf;
		break;
	      case 24:
		G2int_g2_machine_type = Qg2int_alphant;
		break;
	      case 25:
		G2int_g2_machine_type = Qg2int_intelnt;
		break;
	      case 26:
		G2int_g2_machine_type = Qncr;
		break;
	      case 27:
		G2int_g2_machine_type = Qg2int_windows95;
		break;
	      case 28:
		G2int_g2_machine_type = Qg2int_linux;
		break;
	      case 29:
		G2int_g2_machine_type = Qmac;
		break;
	      case 30:
		G2int_g2_machine_type = Qhpia64;
		break;
	      default:
		G2int_g2_machine_type = Qexperimental_port;
		break;
	    }
    }
    if (G2int_machine_model_var == UNBOUND)
	G2int_machine_model_var = Nil;
    string_constant_2 = STATIC_STRING(" Data General AViiON");
    string_constant_3 = STATIC_STRING(" Motorola 88000");
    string_constant_4 = STATIC_STRING(" NeXT");
    string_constant_5 = STATIC_STRING(" Silicon Graphics");
    string_constant_6 = STATIC_STRING(" Sequent");
    string_constant_7 = STATIC_STRING(" DECstation");
    string_constant_8 = STATIC_STRING(" Concurrent 6000s");
    string_constant_9 = STATIC_STRING(" HP9000/300s");
    string_constant_10 = STATIC_STRING(" HP9000/400s");
    string_constant_11 = STATIC_STRING(" PA-RISC HP-UX");
    string_constant_12 = STATIC_STRING(" HP9000/800s");
    Qcompaq = STATIC_SYMBOL("COMPAQ",AB_package);
    string_constant_13 = STATIC_STRING(" \'386");
    string_constant_14 = STATIC_STRING(" IBM POWERstation");
    string_constant_15 = STATIC_STRING(" Sun 3");
    string_constant_16 = STATIC_STRING(" Vax VMS");
    string_constant_17 = STATIC_STRING(" DEC Alpha AXP/OpenVMS");
    string_constant_18 = STATIC_STRING(" Sun 4/SPARCstation Solaris");
    string_constant_19 = STATIC_STRING(" x86 Solaris");
    Qsun4 = STATIC_SYMBOL("SUN4",AB_package);
    string_constant_20 = STATIC_STRING(" Sun 4/SPARCstation");
    string_constant_21 = STATIC_STRING(" Harris Night Hawk");
    string_constant_22 = STATIC_STRING(" Stratus FTX");
    string_constant_23 = STATIC_STRING(" NEC EWS4800 Series");
    string_constant_24 = STATIC_STRING(" DEC OSF/1 AXP");
    string_constant_25 = STATIC_STRING(" Alpha NT");
    string_constant_26 = STATIC_STRING(" Windows");
    string_constant_27 = STATIC_STRING(" MS Windows 3.1");
    string_constant_28 = STATIC_STRING(" NCR 386/486");
    string_constant_29 = STATIC_STRING(" Windows 95/98");
    string_constant_30 = STATIC_STRING(" Linux");
    string_constant_31 = STATIC_STRING(" Mac OS X");
    string_constant_32 = STATIC_STRING(" Itanium HP-UX");
    string_constant_33 = STATIC_STRING(" Experimental Port");
    Qg2int_local_platform_specific_directory = 
	    STATIC_SYMBOL("LOCAL-PLATFORM-SPECIFIC-DIRECTORY",AB_package);
    get_new_value = format((SI_Long)4L,Nil,"~a/specific/~(~a~)/",
	    G2int_source_directory_name,G2int_g2_machine_type);
    set_get(Qg2int_ab,Qg2int_local_platform_specific_directory,get_new_value);
    if (G2int_making_distribution_systemqm == UNBOUND)
	G2int_making_distribution_systemqm = T;
    Qg2int_launch_functionqm = STATIC_SYMBOL("LAUNCH-FUNCTION\?",AB_package);
    G2int_all_modules_of_all_systems = Nil;
    string_constant_34 = STATIC_STRING("BAD GSI MODULE");
    Kinclude_test_for_compile = STATIC_SYMBOL("INCLUDE-TEST-FOR-COMPILE",
	    Pkeyword);
    Kinclude_test_for_load = STATIC_SYMBOL("INCLUDE-TEST-FOR-LOAD",Pkeyword);
    Kinclude_test_for_update = STATIC_SYMBOL("INCLUDE-TEST-FOR-UPDATE",
	    Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,Qnot,Qt);
    Qg2int_lisp_modules_to_be_loaded = 
	    STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",AB_package);
    Kdevelopment = STATIC_SYMBOL("DEVELOPMENT",Pkeyword);
    Kstandard_module_index = STATIC_SYMBOL("STANDARD-MODULE-INDEX",Pkeyword);
    Qg2int_alias = STATIC_SYMBOL("ALIAS",AB_package);
    Qg2int_nicknames = STATIC_SYMBOL("NICKNAMES",AB_package);
    Qg2int_system_pathname = STATIC_SYMBOL("SYSTEM-PATHNAME",AB_package);
    Qg2int_system_package_name = STATIC_SYMBOL("SYSTEM-PACKAGE-NAME",
	    AB_package);
    Qg2int_lisp_source_type = STATIC_SYMBOL("LISP-SOURCE-TYPE",AB_package);
    Qg2int_lisp_binary_type = STATIC_SYMBOL("LISP-BINARY-TYPE",AB_package);
    Qg2int_kb_type = STATIC_SYMBOL("KB-TYPE",AB_package);
    Qg2int_kl_type = STATIC_SYMBOL("KL-TYPE",AB_package);
    Qg2int_systems_to_share_binary_files_with = 
	    STATIC_SYMBOL("SYSTEMS-TO-SHARE-BINARY-FILES-WITH",AB_package);
    Qg2int_system_is_windowless_p = STATIC_SYMBOL("SYSTEM-IS-WINDOWLESS-P",
	    AB_package);
    Qg2int_system_alias = STATIC_SYMBOL("SYSTEM-ALIAS",AB_package);
    Qg2int_real_system_name = STATIC_SYMBOL("REAL-SYSTEM-NAME",AB_package);
    Qg2int_system_lisp_source_files = 
	    STATIC_SYMBOL("SYSTEM-LISP-SOURCE-FILES",AB_package);
    Qg2int_system_lisp_source_type = 
	    STATIC_SYMBOL("SYSTEM-LISP-SOURCE-TYPE",AB_package);
    Qg2int_system_lisp_binary_type = 
	    STATIC_SYMBOL("SYSTEM-LISP-BINARY-TYPE",AB_package);
    Qg2int_system_kb_type = STATIC_SYMBOL("SYSTEM-KB-TYPE",AB_package);
    Qg2int_system_kl_type = STATIC_SYMBOL("SYSTEM-KL-TYPE",AB_package);
}
