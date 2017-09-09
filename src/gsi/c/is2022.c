/* is2022.c
 * Input file:  iso2022.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "is2022.h"


Object G2int_all_supported_2022_escape_sequences = UNBOUND;

/* LENGTH-OF-WIDE-STRING-GREATER-P */
Object g2int_length_of_wide_string_greater_p(wide_string_1,wide_string_2)
    Object wide_string_1, wide_string_2;
{
    Object temp;
    SI_Long length_1, length_2;

    x_note_fn_call(25,0);
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
    Object Qg2int_length_of_wide_string_greater_p, Qg2int_equalw, Qg2int_right;
    Object Qg2int_ks_c_5601, string_constant_22, Qg2int_jis_x_0208;
    Object string_constant_21, Qg2int_gb_2312, string_constant_20, Qg2int_left;
    Object string_constant_19, AB_package, string_constant_16;
    Object string_constant_18, string_constant_17, string_constant_15;
    Object string_constant_14, string_constant_13, Qg2int_iso_8859_9;
    Object string_constant_12, Qg2int_iso_8859_8, string_constant_11;
    Object Qg2int_iso_8859_7, string_constant_10, Qg2int_iso_8859_6;
    Object string_constant_9, Qg2int_iso_8859_5, string_constant_8;
    Object Qg2int_iso_8859_4, string_constant_7, Qg2int_iso_8859_3;
    Object string_constant_6, Qg2int_iso_8859_2, string_constant_5;
    Object Qg2int_iso_8859_1, string_constant_4, Qg2int_iso_646;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant;

    x_note_fn_call(25,1);
    SET_PACKAGE("AB");
    if (G2int_all_supported_2022_escape_sequences == UNBOUND)
	G2int_all_supported_2022_escape_sequences = Nil;
    string_constant = STATIC_STRING("(B");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_iso_646 = STATIC_SYMBOL("ISO-646",AB_package);
    Qg2int_left = STATIC_SYMBOL("LEFT",AB_package);
    Qg2int_equalw = STATIC_SYMBOL("EQUALW",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_equalw,STATIC_FUNCTION(g2int_equalw,NIL,
	    FALSE,2,2));
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant),Qg2int_iso_646,
	    Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    Qg2int_length_of_wide_string_greater_p = 
	    STATIC_SYMBOL("LENGTH-OF-WIDE-STRING-GREATER-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p,
	    STATIC_FUNCTION(g2int_length_of_wide_string_greater_p,NIL,
	    FALSE,2,2));
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_1 = STATIC_STRING("(A");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_1),Qg2int_iso_646,
	    Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_2 = STATIC_STRING("(@");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_2),Qg2int_iso_646,
	    Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_3 = STATIC_STRING("(J");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_3),Qg2int_iso_646,
	    Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_4 = STATIC_STRING("-A");
    Qg2int_iso_8859_1 = STATIC_SYMBOL("ISO-8859-1",AB_package);
    Qg2int_right = STATIC_SYMBOL("RIGHT",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_4),
	    Qg2int_iso_8859_1,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_5 = STATIC_STRING("-B");
    Qg2int_iso_8859_2 = STATIC_SYMBOL("ISO-8859-2",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_5),
	    Qg2int_iso_8859_2,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_6 = STATIC_STRING("-C");
    Qg2int_iso_8859_3 = STATIC_SYMBOL("ISO-8859-3",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_6),
	    Qg2int_iso_8859_3,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_7 = STATIC_STRING("-D");
    Qg2int_iso_8859_4 = STATIC_SYMBOL("ISO-8859-4",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_7),
	    Qg2int_iso_8859_4,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_8 = STATIC_STRING("-L");
    Qg2int_iso_8859_5 = STATIC_SYMBOL("ISO-8859-5",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_8),
	    Qg2int_iso_8859_5,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_9 = STATIC_STRING("-G");
    Qg2int_iso_8859_6 = STATIC_SYMBOL("ISO-8859-6",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_9),
	    Qg2int_iso_8859_6,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_10 = STATIC_STRING("-F");
    Qg2int_iso_8859_7 = STATIC_SYMBOL("ISO-8859-7",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_10),
	    Qg2int_iso_8859_7,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_11 = STATIC_STRING("-H");
    Qg2int_iso_8859_8 = STATIC_SYMBOL("ISO-8859-8",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_11),
	    Qg2int_iso_8859_8,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_12 = STATIC_STRING("-M");
    Qg2int_iso_8859_9 = STATIC_SYMBOL("ISO-8859-9",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_12),
	    Qg2int_iso_8859_9,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_13 = STATIC_STRING("$A");
    Qg2int_gb_2312 = STATIC_SYMBOL("GB-2312",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_13),
	    Qg2int_gb_2312,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_14 = STATIC_STRING("$(A");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_14),
	    Qg2int_gb_2312,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_15 = STATIC_STRING("$(B");
    Qg2int_jis_x_0208 = STATIC_SYMBOL("JIS-X-0208",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_15),
	    Qg2int_jis_x_0208,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_16 = STATIC_STRING("$B");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_16),
	    Qg2int_jis_x_0208,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_17 = STATIC_STRING("&@\033$B");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_17),
	    Qg2int_jis_x_0208,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_18 = STATIC_STRING("$@");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_18),
	    Qg2int_jis_x_0208,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_16),
	    Qg2int_jis_x_0208,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_19 = STATIC_STRING("$(C");
    Qg2int_ks_c_5601 = STATIC_SYMBOL("KS-C-5601",AB_package);
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_19),
	    Qg2int_ks_c_5601,Qg2int_left);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_20 = STATIC_STRING("$)A");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_20),
	    Qg2int_gb_2312,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_21 = STATIC_STRING("$)B");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_21),
	    Qg2int_jis_x_0208,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
    string_constant_22 = STATIC_STRING("$)C");
    pushnew_arg_1 = LIST_3(g2int_stringw(string_constant_22),
	    Qg2int_ks_c_5601,Qg2int_right);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qg2int_equalw);
    all_supported_2022_escape_sequences_new_value = adjoin(4,pushnew_arg_1,
	    G2int_all_supported_2022_escape_sequences,Ktest,pushnew_arg_3);
    G2int_all_supported_2022_escape_sequences = 
	    all_supported_2022_escape_sequences_new_value;
    G2int_all_supported_2022_escape_sequences = 
	    g2int_sort_list(G2int_all_supported_2022_escape_sequences,
	    SYMBOL_FUNCTION(Qg2int_length_of_wide_string_greater_p),
	    SYMBOL_FUNCTION(Qcar));
}
