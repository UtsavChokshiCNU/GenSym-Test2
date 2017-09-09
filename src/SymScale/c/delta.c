/* delta.c
 * Input file:  delta.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "delta.h"


Object Build_identification_string = UNBOUND;

Object Build_comment_string = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(System_version_of_current_gensym_product_line, Qsystem_version_of_current_gensym_product_line);

DEFINE_VARIABLE_WITH_SYMBOL(Systems_in_gensym_product_line, Qsystems_in_gensym_product_line);

void delta_INIT()
{
    Object tail, system_1;
    Object list_constant, Qgw, Qgsi, Qab, Qtelewindows, AB_package;
    Object Qbrief_description, string_constant_2, Qalpha_or_beta;
    Object string_constant_1, string_constant, Qexternal_version;
    Object Qpatch_number_of_current_gensym_product_line_qm;
    Object Qrevision_number_of_current_gensym_product_line;
    Object Qrelease_quality_of_current_gensym_product_line;
    Object Qminor_version_number_of_current_gensym_product_line;
    Object Qmajor_version_number_of_current_gensym_product_line;

    x_note_fn_call(3,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qmajor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MAJOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qmajor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)12L));
    Qminor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MINOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qminor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
    Qrelease_quality_of_current_gensym_product_line = 
	    STATIC_SYMBOL("RELEASE-QUALITY-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qrelease_quality_of_current_gensym_product_line,
	    Release_quality);
    Qrevision_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("REVISION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    SET_SYMBOL_VALUE(Qrevision_number_of_current_gensym_product_line,
	    FIX((SI_Long)9L));
    Qpatch_number_of_current_gensym_product_line_qm = 
	    STATIC_SYMBOL("PATCH-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE\?",
	    AB_package);
    SET_SYMBOL_VALUE(Qpatch_number_of_current_gensym_product_line_qm,Nil);
    Qexternal_version = STATIC_SYMBOL("EXTERNAL-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qexternal_version,FIX((SI_Long)2015L));
    string_constant = STATIC_STRING("SJ01");
    Build_identification_string = string_constant;
    string_constant_1 = STATIC_STRING("2016.10");
    Build_comment_string = string_constant_1;
    Qalpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    string_constant_2 = STATIC_STRING("Rev. 9");
    Qbrief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    if (System_version_of_current_gensym_product_line == UNBOUND)
	System_version_of_current_gensym_product_line = list(6,
		FIX((SI_Long)12L),FIX((SI_Long)0L),Qalpha_or_beta,
		string_constant_2,Qbrief_description,machine_model());
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qgw = STATIC_SYMBOL("GW",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qtelewindows,Qab,Qgsi,Qgw);
    if (Systems_in_gensym_product_line == UNBOUND)
	Systems_in_gensym_product_line = list_constant;
    tail = Systems_in_gensym_product_line;
    system_1 = Nil;
    for ( ; !ENDP(tail); tail = CDR(tail)) {
	system_1 = CAR(tail);
	set_system_version(system_1,
		System_version_of_current_gensym_product_line);
    }
}
