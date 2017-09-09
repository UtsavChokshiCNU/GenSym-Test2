/* delta.c
 * Input file:  delta.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "delta.h"


Object G2int_build_identification_string = UNBOUND;

Object G2int_build_comment_string = UNBOUND;

Object G2int_system_version_of_current_gensym_product_line = UNBOUND;

Object G2int_systems_in_gensym_product_line = UNBOUND;

void delta_INIT()
{
    Object tail, system_1;
    Object list_constant, Qg2int_gw, Qg2int_gsi, Qg2int_ab, Qg2int_telewindows;
    Object AB_package, Qg2int_brief_description, string_constant_2;
    Object Qg2int_alpha_or_beta, string_constant_1, string_constant;
    Object Qg2int_external_version;
    Object Qg2int_patch_number_of_current_gensym_product_lineqm;
    Object Qg2int_revision_number_of_current_gensym_product_line;
    Object Qg2int_release_quality_of_current_gensym_product_line;
    Object Qg2int_minor_version_number_of_current_gensym_product_line;
    Object Qg2int_major_version_number_of_current_gensym_product_line;

    x_note_fn_call(3,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_major_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MAJOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_major_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)12L));
    Qg2int_minor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MINOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_minor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
    Qg2int_release_quality_of_current_gensym_product_line = 
	    STATIC_SYMBOL("RELEASE-QUALITY-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_quality_of_current_gensym_product_line,
	    G2int_beta_release_quality);
    Qg2int_revision_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("REVISION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_revision_number_of_current_gensym_product_line,
	    FIX((SI_Long)20L));
    Qg2int_patch_number_of_current_gensym_product_lineqm = 
	    STATIC_SYMBOL("PATCH-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE\?",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_patch_number_of_current_gensym_product_lineqm,Nil);
    Qg2int_external_version = STATIC_SYMBOL("EXTERNAL-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_external_version,FIX((SI_Long)2015L));
    string_constant = STATIC_STRING("TH27");
    G2int_build_identification_string = string_constant;
    string_constant_1 = STATIC_STRING("2017.08.W0");
    G2int_build_comment_string = string_constant_1;
    Qg2int_alpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    string_constant_2 = STATIC_STRING("Beta Rev. 20");
    Qg2int_brief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    if (G2int_system_version_of_current_gensym_product_line == UNBOUND)
	G2int_system_version_of_current_gensym_product_line = list(6,
		FIX((SI_Long)12L),FIX((SI_Long)0L),Qg2int_alpha_or_beta,
		string_constant_2,Qg2int_brief_description,
		g2int_machine_model());
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_gw = STATIC_SYMBOL("GW",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qg2int_telewindows,Qg2int_ab,
	    Qg2int_gsi,Qg2int_gw);
    if (G2int_systems_in_gensym_product_line == UNBOUND)
	G2int_systems_in_gensym_product_line = list_constant;
    tail = G2int_systems_in_gensym_product_line;
    system_1 = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	system_1 = CAR(tail);
	g2int_set_system_version(system_1,
		G2int_system_version_of_current_gensym_product_line);
    }
}
