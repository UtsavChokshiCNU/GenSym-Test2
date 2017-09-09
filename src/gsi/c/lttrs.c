/* lttrs.c
 * Input file:  letters.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lttrs.h"


Object G2int_the_type_description_of_unicode_block = UNBOUND;

Object G2int_chain_of_available_unicode_blocks = UNBOUND;

Object G2int_unicode_block_count = UNBOUND;

/* RECLAIM-UNICODE-BLOCK-1 */
Object g2int_reclaim_unicode_block_1(unicode_block)
    Object unicode_block;
{
    Object svref_new_value;

    x_note_fn_call(23,0);
    inline_note_reclaim_cons(unicode_block,Nil);
    svref_new_value = G2int_chain_of_available_unicode_blocks;
    SVREF(unicode_block,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_unicode_blocks = unicode_block;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-BLOCK */
Object g2int_reclaim_structure_for_unicode_block(unicode_block)
    Object unicode_block;
{
    x_note_fn_call(23,1);
    return g2int_reclaim_unicode_block_1(unicode_block);
}

static Object Qg2_defstruct_structure_name_unicode_block_g2_struct;  /* g2-defstruct-structure-name::unicode-block-g2-struct */

/* MAKE-PERMANENT-UNICODE-BLOCK-STRUCTURE-INTERNAL */
Object g2int_make_permanent_unicode_block_structure_internal()
{
    Object def_structure_unicode_block_variable, unicode_block_count_new_value;
    Object defstruct_g2_unicode_block_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(23,2);
    def_structure_unicode_block_variable = Nil;
    unicode_block_count_new_value = FIXNUM_ADD1(G2int_unicode_block_count);
    G2int_unicode_block_count = unicode_block_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_unicode_block_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_unicode_block_variable = the_array;
	SVREF(defstruct_g2_unicode_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_block_g2_struct;
	def_structure_unicode_block_variable = 
		defstruct_g2_unicode_block_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_unicode_block_variable);
}

/* MAKE-UNICODE-BLOCK-1 */
Object g2int_make_unicode_block_1()
{
    Object def_structure_unicode_block_variable;

    x_note_fn_call(23,3);
    def_structure_unicode_block_variable = 
	    G2int_chain_of_available_unicode_blocks;
    if (def_structure_unicode_block_variable) {
	G2int_chain_of_available_unicode_blocks = 
		ISVREF(def_structure_unicode_block_variable,(SI_Long)0L);
	SVREF(def_structure_unicode_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_block_g2_struct;
    }
    else
	def_structure_unicode_block_variable = 
		g2int_make_permanent_unicode_block_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_block_variable,Nil);
    return VALUES_1(def_structure_unicode_block_variable);
}

Object G2int_unicode_block_prop = UNBOUND;

Object G2int_all_unicode_block_names = UNBOUND;

/* UNICODE-BLOCK-< */
Object g2int_unicode_block_lt(unicode_block_1,unicode_block_2)
    Object unicode_block_1, unicode_block_2;
{
    Object temp, temp_1;

    x_note_fn_call(23,4);
    temp = ISVREF(unicode_block_1,(SI_Long)2L);
    temp_1 = ISVREF(unicode_block_2,(SI_Long)2L);
    return VALUES_1(FIXNUM_LT(FIRST(temp),FIRST(temp_1)) ? T : Nil);
}

void letters_INIT()
{
    Object temp, reclaim_structure_for_unicode_block;
    Object all_unicode_block_names_new_value, unicode_block;
    Object Qg2int_unicode_block, Qg2int_greek_extended, list_constant_53;
    Object AB_package, Qg2int_latin_extended_additional, list_constant_52;
    Object Qg2int_hangul_jamo, list_constant_51, Qg2int_georgian;
    Object list_constant_50, list_constant_49, list_constant_48;
    Object list_constant_47, list_constant_46, Klower_range, Koffset_to_upper;
    Object Qg2int_miscellaneous_2, list_constant_45, Qg2int_armenian;
    Object list_constant_44, list_constant_43, list_constant_42;
    Object list_constant_41, Qg2int_cyrillic_extended, list_constant_40;
    Object Qg2int_cyrillic, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_13, list_constant_34, Klower_odd_range;
    Object list_constant_31, list_constant_33, list_constant_5;
    Object list_constant_32, Qg2int_greek_symbols_and_coptic, list_constant_30;
    Object Qg2int_basic_greek, list_constant_29, list_constant_28;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object list_constant_24, Qg2int_miscellaneous, list_constant_23;
    Object Qg2int_latin_extended_a, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, Klower_even_range;
    Object list_constant_15, list_constant_14, list_constant_12;
    Object Qg2int_latin_1_supplement, list_constant_11, list_constant_10;
    Object list_constant_9, list_constant_8, list_constant_7, Kuppercase_code;
    Object Klowercase_code, list_constant_6, list_constant_4;
    Object Qg2int_basic_latin, list_constant_3, list_constant_2;
    Object list_constant_1, list_constant, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_unicode_block_count;
    Object Qg2int_chain_of_available_unicode_blocks;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(23,5);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_unicode_block_g2_struct = 
	    STATIC_SYMBOL("UNICODE-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_unicode_block = STATIC_SYMBOL("UNICODE-BLOCK",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    Qg2int_unicode_block,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_unicode_block,
	    Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_unicode_block == UNBOUND)
	G2int_the_type_description_of_unicode_block = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8l8305y1n8305y8m8k1l8m0000001l1m8n83=-ykpk0k0");
    temp = G2int_the_type_description_of_unicode_block;
    G2int_the_type_description_of_unicode_block = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    G2int_the_type_description_of_unicode_block,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_unicode_block,
	    G2int_the_type_description_of_unicode_block,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_unicode_blocks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-BLOCKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_unicode_blocks,
	    G2int_chain_of_available_unicode_blocks);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_unicode_blocks,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_unicode_block_count = STATIC_SYMBOL("UNICODE-BLOCK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_unicode_block_count,
	    G2int_unicode_block_count);
    g2int_record_system_variable(Qg2int_unicode_block_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_unicode_block = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_unicode_block,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_unicode_block,reclaim_structure_for_unicode_block);
    G2int_unicode_block_prop = Qg2int_unicode_block;
    if (G2int_all_unicode_block_names == UNBOUND)
	G2int_all_unicode_block_names = Nil;
    Qg2int_basic_latin = STATIC_SYMBOL("BASIC-LATIN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_basic_latin,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_2 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)127L));
    Klower_range = STATIC_SYMBOL("LOWER-RANGE",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)97L),
	    FIX((SI_Long)122L));
    Koffset_to_upper = STATIC_SYMBOL("OFFSET-TO-UPPER",Pkeyword);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Klower_range,list_constant,
	    Koffset_to_upper,FIX((SI_Long)-32L));
    list_constant_3 = STATIC_CONS(list_constant_1,Qnil);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_basic_latin;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_2;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_3;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_basic_latin,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_latin_1_supplement = STATIC_SYMBOL("LATIN-1-SUPPLEMENT",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_latin_1_supplement,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_10 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)128L),
	    FIX((SI_Long)255L));
    list_constant_4 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)224L),
	    FIX((SI_Long)246L));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Koffset_to_upper,
	    FIX((SI_Long)-32L));
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_4,list_constant_5);
    list_constant_6 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)248L),
	    FIX((SI_Long)254L));
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_6,list_constant_5);
    Klowercase_code = STATIC_SYMBOL("LOWERCASE-CODE",Pkeyword);
    Kuppercase_code = STATIC_SYMBOL("UPPERCASE-CODE",Pkeyword);
    list_constant_9 = STATIC_LIST((SI_Long)4L,Klowercase_code,
	    FIX((SI_Long)255L),Kuppercase_code,FIX((SI_Long)376L));
    list_constant_11 = STATIC_LIST((SI_Long)3L,list_constant_7,
	    list_constant_8,list_constant_9);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_latin_1_supplement;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_10;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_11;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_latin_1_supplement,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_latin_extended_a = STATIC_SYMBOL("LATIN-EXTENDED-A",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_latin_extended_a,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)256L),
	    FIX((SI_Long)383L));
    Klower_odd_range = STATIC_SYMBOL("LOWER-ODD-RANGE",Pkeyword);
    list_constant_12 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)256L),
	    FIX((SI_Long)311L));
    list_constant_13 = STATIC_LIST((SI_Long)2L,Koffset_to_upper,
	    FIX((SI_Long)-1L));
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,Klower_odd_range,
	    list_constant_12,list_constant_13);
    Klower_even_range = STATIC_SYMBOL("LOWER-EVEN-RANGE",Pkeyword);
    list_constant_14 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)313L),
	    FIX((SI_Long)328L));
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Klower_even_range,
	    list_constant_14,list_constant_13);
    list_constant_15 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)330L),
	    FIX((SI_Long)375L));
    list_constant_19 = STATIC_LIST_STAR((SI_Long)3L,Klower_odd_range,
	    list_constant_15,list_constant_13);
    list_constant_16 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)377L),
	    FIX((SI_Long)382L));
    list_constant_20 = STATIC_LIST_STAR((SI_Long)3L,Klower_even_range,
	    list_constant_16,list_constant_13);
    list_constant_22 = STATIC_LIST((SI_Long)4L,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_latin_extended_a;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_21;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_22;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_latin_extended_a,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_miscellaneous = STATIC_SYMBOL("MISCELLANEOUS",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_miscellaneous,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)384L),
	    FIX((SI_Long)879L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_miscellaneous;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_23;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_miscellaneous,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_basic_greek = STATIC_SYMBOL("BASIC-GREEK",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_basic_greek,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_28 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)880L),
	    FIX((SI_Long)975L));
    list_constant_24 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)945L),
	    FIX((SI_Long)961L));
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_24,list_constant_5);
    list_constant_25 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)963L),
	    FIX((SI_Long)969L));
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_25,list_constant_5);
    list_constant_29 = STATIC_LIST((SI_Long)2L,list_constant_26,
	    list_constant_27);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_basic_greek;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_28;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_29;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_basic_greek,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_greek_symbols_and_coptic = 
	    STATIC_SYMBOL("GREEK-SYMBOLS-AND-COPTIC",AB_package);
    all_unicode_block_names_new_value = adjoin(2,
	    Qg2int_greek_symbols_and_coptic,G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_30 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)976L),
	    FIX((SI_Long)1023L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_greek_symbols_and_coptic;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_30;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_greek_symbols_and_coptic,
	    unicode_block,Qg2int_unicode_block);
    Qg2int_cyrillic = STATIC_SYMBOL("CYRILLIC",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_cyrillic,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_31 = STATIC_CONS(FIX((SI_Long)1151L),Qnil);
    list_constant_38 = STATIC_CONS(FIX((SI_Long)1024L),list_constant_31);
    list_constant_32 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1072L),
	    FIX((SI_Long)1103L));
    list_constant_35 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_32,list_constant_5);
    list_constant_33 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1105L),
	    FIX((SI_Long)1119L));
    list_constant_36 = STATIC_LIST((SI_Long)4L,Klower_range,
	    list_constant_33,Koffset_to_upper,FIX((SI_Long)-80L));
    list_constant_34 = STATIC_CONS(FIX((SI_Long)1120L),list_constant_31);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)3L,Klower_odd_range,
	    list_constant_34,list_constant_13);
    list_constant_39 = STATIC_LIST((SI_Long)3L,list_constant_35,
	    list_constant_36,list_constant_37);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_cyrillic;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_38;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_39;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_cyrillic,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_cyrillic_extended = STATIC_SYMBOL("CYRILLIC-EXTENDED",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_cyrillic_extended,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_40 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1152L),
	    FIX((SI_Long)1279L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_cyrillic_extended;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_40;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_cyrillic_extended,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_armenian = STATIC_SYMBOL("ARMENIAN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_armenian,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_43 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1280L),
	    FIX((SI_Long)1423L));
    list_constant_41 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1377L),
	    FIX((SI_Long)1414L));
    list_constant_42 = STATIC_LIST((SI_Long)4L,Klower_range,
	    list_constant_41,Koffset_to_upper,FIX((SI_Long)-48L));
    list_constant_44 = STATIC_CONS(list_constant_42,Qnil);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_armenian;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_43;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_44;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_armenian,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_miscellaneous_2 = STATIC_SYMBOL("MISCELLANEOUS-2",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_miscellaneous_2,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_45 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1424L),
	    FIX((SI_Long)3839L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_miscellaneous_2;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_45;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_miscellaneous_2,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_georgian = STATIC_SYMBOL("GEORGIAN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_georgian,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_49 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4256L),
	    FIX((SI_Long)4351L));
    list_constant_46 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4304L),
	    FIX((SI_Long)4342L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Koffset_to_upper,
	    FIX((SI_Long)-48L));
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_46,list_constant_47);
    list_constant_50 = STATIC_CONS(list_constant_48,Qnil);
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_georgian;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_49;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_50;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qt;
    g2int_mutate_global_property(Qg2int_georgian,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_hangul_jamo = STATIC_SYMBOL("HANGUL-JAMO",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_hangul_jamo,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_51 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4352L),
	    FIX((SI_Long)4607L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_hangul_jamo;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_51;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_hangul_jamo,unicode_block,
	    Qg2int_unicode_block);
    Qg2int_latin_extended_additional = 
	    STATIC_SYMBOL("LATIN-EXTENDED-ADDITIONAL",AB_package);
    all_unicode_block_names_new_value = adjoin(2,
	    Qg2int_latin_extended_additional,G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_52 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7680L),
	    FIX((SI_Long)7935L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_latin_extended_additional;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_52;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_latin_extended_additional,
	    unicode_block,Qg2int_unicode_block);
    Qg2int_greek_extended = STATIC_SYMBOL("GREEK-EXTENDED",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qg2int_greek_extended,
	    G2int_all_unicode_block_names);
    G2int_all_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_53 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7936L),
	    FIX((SI_Long)8191L));
    unicode_block = g2int_make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qg2int_greek_extended;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_53;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    g2int_mutate_global_property(Qg2int_greek_extended,unicode_block,
	    Qg2int_unicode_block);
}
