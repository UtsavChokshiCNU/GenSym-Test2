/* load.c
 * Input file:  load.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "load.h"


Object ab_G2int_dummy_var = UNBOUND;

Object G2int_user_package_in_this_lisp = UNBOUND;

Object G2int_list_for_import = UNBOUND;

Object G2int_bootstrap_information = UNBOUND;

Object G2int_ab_system_pathname = UNBOUND;

Object G2int_file_naming_spin_id = UNBOUND;

Object G2int_file_naming_specific_source_directory = UNBOUND;

Object G2int_file_naming_specific_dest_directory = UNBOUND;

Object G2int_file_naming_tools_directory = UNBOUND;

Object G2int_default_sandbox_location = UNBOUND;

Object G2int_default_spin_id = UNBOUND;

Object G2int_default_sandbox_name = UNBOUND;

Object G2int_source_directory_name = UNBOUND;

Object G2int_dest_directory_name = UNBOUND;

Object G2int_toolsdir_name = UNBOUND;

Object G2int_starfasl_extensionstar = UNBOUND;

/* USE-DATES-INSTEAD-OF-VERSIONS-P */
Object g2int_use_dates_instead_of_versions_p()
{
    x_note_fn_call(0,0);
    return VALUES_1( !TRUEP(SIXTH(G2int_bootstrap_information)) ? T : Nil);
}

Object G2int_lisp_memory_expandedqm = UNBOUND;

void load_INIT()
{
    Object tcl_user_ab_package_name, tcl_user_ab_package_use_list;
    Object tcl_user_extant_ab_package_qm, star_features_star_new_value;
    Object list_constant_3, Qg2int_downcase, string_constant_15;
    Object string_constant_14, string_constant_13, AB_package;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, Kvanilla, Kno_macros, string_constant_5;
    Object string_constant_4, string_constant_2, string_constant_1;
    Object string_constant_3, list_constant_2, list_constant_1, list_constant;
    Object string_constant;

    x_note_fn_call(0,1);
    SET_PACKAGE("TCL-USER");
    if (ab_G2int_dummy_var == UNBOUND)
	ab_G2int_dummy_var = adjust_area_target_sizes(FIX((SI_Long)500L),
		FIX((SI_Long)700L),"GSI");
    string_constant_1 = STATIC_STRING("AB-LISP");
    string_constant = STATIC_STRING("TCL");
    list_constant = STATIC_CONS(string_constant,Qnil);
    if ( !TRUEP(find_package(string_constant_1)))
	make_package(5,string_constant_1,Knicknames,Nil,Kuse,list_constant);
    list_constant_1 = STATIC_LIST((SI_Long)6L,Qt,Qfloat,Qinteger,Qsymbol,
	    Qlist,Qarray);
    export(list_constant_1,find_package(string_constant_1));
    string_constant_2 = STATIC_STRING("AB");
    list_constant_2 = STATIC_CONS(string_constant_1,Qnil);
    tcl_user_ab_package_name = string_constant_2;
    tcl_user_ab_package_use_list = list_constant_2;
    tcl_user_extant_ab_package_qm = find_package(string_constant_2);
    if (!tcl_user_extant_ab_package_qm)
	make_package(5,tcl_user_ab_package_name,Knicknames,Nil,Kuse,
		tcl_user_ab_package_use_list);
    string_constant_3 = STATIC_STRING("NIL");
    import(LIST_1(find_symbol(string_constant_3,string_constant_1)),
	    find_package(string_constant_2));
    SET_PACKAGE("AB");
    string_constant_4 = STATIC_STRING("TCL-USER");
    if (G2int_user_package_in_this_lisp == UNBOUND)
	G2int_user_package_in_this_lisp = find_package(string_constant_4);
    if (G2int_list_for_import == UNBOUND)
	G2int_list_for_import = make_list(1,FIX((SI_Long)1L));
    string_constant_5 = STATIC_STRING("G2-DEFSTRUCT-STRUCTURE-NAME");
    if ( !TRUEP(find_package(string_constant_5)))
	make_package(5,string_constant_5,Knicknames,Nil,Kuse,Nil);
    Kno_macros = STATIC_SYMBOL("NO-MACROS",Pkeyword);
    star_features_star_new_value = adjoin(2,Kno_macros,Features);
    Features = star_features_star_new_value;
    Kvanilla = STATIC_SYMBOL("VANILLA",Pkeyword);
    star_features_star_new_value = adjoin(2,Kvanilla,Features);
    Features = star_features_star_new_value;
    import(Qload_pathname,_);
    string_constant_6 = STATIC_STRING("buildroot.dat");
    G2int_file_naming_spin_id = string_constant_6;
    string_constant_7 = STATIC_STRING("srcbox.dat");
    G2int_file_naming_specific_source_directory = string_constant_7;
    string_constant_8 = STATIC_STRING("dstbox.dat");
    G2int_file_naming_specific_dest_directory = string_constant_8;
    string_constant_9 = STATIC_STRING("toolsdir.dat");
    G2int_file_naming_tools_directory = string_constant_9;
    string_constant_10 = STATIC_STRING("/bt");
    G2int_default_sandbox_location = string_constant_10;
    string_constant_11 = STATIC_STRING("ab");
    G2int_default_spin_id = string_constant_11;
    G2int_default_sandbox_name = format((SI_Long)4L,Nil,"~A/~A",
	    G2int_default_sandbox_location,G2int_default_spin_id);
    G2int_source_directory_name = Nil;
    G2int_dest_directory_name = Nil;
    G2int_toolsdir_name = Nil;
    string_constant_12 = STATIC_STRING("lx64fsl");
    if (G2int_starfasl_extensionstar == UNBOUND)
	G2int_starfasl_extensionstar = string_constant_12;
    string_constant_13 = STATIC_STRING("lisp");
    string_constant_14 = STATIC_STRING("kb");
    string_constant_15 = STATIC_STRING("kl");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_downcase = STATIC_SYMBOL("DOWNCASE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnil,Qnil);
    G2int_bootstrap_information = list_star(8,G2int_starfasl_extensionstar,
	    string_constant_13,string_constant_14,string_constant_15,
	    Qg2int_downcase,Qnil,Load_pathname,list_constant_3);
    if (G2int_lisp_memory_expandedqm == UNBOUND)
	G2int_lisp_memory_expandedqm = Nil;
}
