/* is2022.c
 * Input file:  iso2022.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "is2022.h"


DEFINE_VARIABLE_WITH_SYMBOL(All_supported_2022_escape_sequences, Qall_supported_2022_escape_sequences);

/* LENGTH-OF-WIDE-STRING-GREATER-P */
Object length_of_wide_string_greater_p(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;
    SI_Long length_1, length_2;

    x_note_fn_call(27,0);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_1));
    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_2));
    temp = FIXNUM_GT(FIX(UBYTE_16_ISAREF_1(wide_string_1,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_1,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
	    FIX(UBYTE_16_ISAREF_1(wide_string_2,length_2 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(wide_string_2,length_2 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L))) ? T : Nil;
    return VALUES_1(temp);
}

void iso2022_INIT()
{
    Object pushnew_arg_1, pushnew_arg_3;
    Object all_supported_2022_escape_sequences_new_value;
    Object Qlength_of_wide_string_greater_p, Qequalw, Qright, Qks_c_5601;
    Object string_constant_22, Qjis_x_0208, string_constant_21, Qgb_2312;
    Object string_constant_20, Qleft, string_constant_19, AB_package;
    Object string_constant_16, string_constant_18, string_constant_17;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object Qiso_8859_9, string_constant_12, Qiso_8859_8, string_constant_11;
    Object Qiso_8859_7, string_constant_10, Qiso_8859_6, string_constant_9;
    Object Qiso_8859_5, string_constant_8, Qiso_8859_4, string_constant_7;
    Object Qiso_8859_3, string_constant_6, Qiso_8859_2, string_constant_5;
    Object Qiso_8859_1, string_constant_4, Qiso_646, string_constant_3;
    Object string_constant_2, string_constant_1, string_constant;

    x_note_fn_call(27,1);
    SET_PACKAGE("AB");
    if (All_supported_2022_escape_sequences == UNBOUND)
	All_supported_2022_escape_sequences = Nil;
    string_constant = STATIC_STRING("(B");
    AB_package = STATIC_PACKAGE("AB");
    Qiso_646 = STATIC_SYMBOL("ISO-646",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qequalw = STATIC_SYMBOL("EQUALW",AB_package);
    SET_SYMBOL_FUNCTION(Qequalw,STATIC_FUNCTION(equalw,NIL,FALSE,2,2));
    pushnew_arg_1 = LIST_3(stringw(string_constant),Qiso_646,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    Qlength_of_wide_string_greater_p = 
	    STATIC_SYMBOL("LENGTH-OF-WIDE-STRING-GREATER-P",AB_package);
    SET_SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p,
	    STATIC_FUNCTION(length_of_wide_string_greater_p,NIL,FALSE,2,2));
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_1 = STATIC_STRING("(A");
    pushnew_arg_1 = LIST_3(stringw(string_constant_1),Qiso_646,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_2 = STATIC_STRING("(@");
    pushnew_arg_1 = LIST_3(stringw(string_constant_2),Qiso_646,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_3 = STATIC_STRING("(J");
    pushnew_arg_1 = LIST_3(stringw(string_constant_3),Qiso_646,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_4 = STATIC_STRING("-A");
    Qiso_8859_1 = STATIC_SYMBOL("ISO-8859-1",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_4),Qiso_8859_1,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_5 = STATIC_STRING("-B");
    Qiso_8859_2 = STATIC_SYMBOL("ISO-8859-2",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_5),Qiso_8859_2,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_6 = STATIC_STRING("-C");
    Qiso_8859_3 = STATIC_SYMBOL("ISO-8859-3",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_6),Qiso_8859_3,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_7 = STATIC_STRING("-D");
    Qiso_8859_4 = STATIC_SYMBOL("ISO-8859-4",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_7),Qiso_8859_4,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_8 = STATIC_STRING("-L");
    Qiso_8859_5 = STATIC_SYMBOL("ISO-8859-5",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_8),Qiso_8859_5,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_9 = STATIC_STRING("-G");
    Qiso_8859_6 = STATIC_SYMBOL("ISO-8859-6",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_9),Qiso_8859_6,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_10 = STATIC_STRING("-F");
    Qiso_8859_7 = STATIC_SYMBOL("ISO-8859-7",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_10),Qiso_8859_7,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_11 = STATIC_STRING("-H");
    Qiso_8859_8 = STATIC_SYMBOL("ISO-8859-8",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_11),Qiso_8859_8,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_12 = STATIC_STRING("-M");
    Qiso_8859_9 = STATIC_SYMBOL("ISO-8859-9",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_12),Qiso_8859_9,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_13 = STATIC_STRING("$A");
    Qgb_2312 = STATIC_SYMBOL("GB-2312",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_13),Qgb_2312,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_14 = STATIC_STRING("$(A");
    pushnew_arg_1 = LIST_3(stringw(string_constant_14),Qgb_2312,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_15 = STATIC_STRING("$(B");
    Qjis_x_0208 = STATIC_SYMBOL("JIS-X-0208",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_15),Qjis_x_0208,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_16 = STATIC_STRING("$B");
    pushnew_arg_1 = LIST_3(stringw(string_constant_16),Qjis_x_0208,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_17 = STATIC_STRING("&@\033$B");
    pushnew_arg_1 = LIST_3(stringw(string_constant_17),Qjis_x_0208,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_18 = STATIC_STRING("$@");
    pushnew_arg_1 = LIST_3(stringw(string_constant_18),Qjis_x_0208,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    pushnew_arg_1 = LIST_3(stringw(string_constant_16),Qjis_x_0208,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_19 = STATIC_STRING("$(C");
    Qks_c_5601 = STATIC_SYMBOL("KS-C-5601",AB_package);
    pushnew_arg_1 = LIST_3(stringw(string_constant_19),Qks_c_5601,Qleft);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_20 = STATIC_STRING("$)A");
    pushnew_arg_1 = LIST_3(stringw(string_constant_20),Qgb_2312,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_21 = STATIC_STRING("$)B");
    pushnew_arg_1 = LIST_3(stringw(string_constant_21),Qjis_x_0208,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_22 = STATIC_STRING("$)C");
    pushnew_arg_1 = LIST_3(stringw(string_constant_22),Qks_c_5601,Qright);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qequalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    All_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    All_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    All_supported_2022_escape_sequences = 
	    sort_list(All_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qlength_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
}
