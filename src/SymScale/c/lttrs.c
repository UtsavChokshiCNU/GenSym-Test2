/* lttrs.c
 * Input file:  letters.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "lttrs.h"


Object The_type_description_of_unicode_block = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_unicode_blocks, Qchain_of_available_unicode_blocks);

DEFINE_VARIABLE_WITH_SYMBOL(Unicode_block_count, Qunicode_block_count);

Object Chain_of_available_unicode_blocks_vector = UNBOUND;

/* UNICODE-BLOCK-STRUCTURE-MEMORY-USAGE */
Object unicode_block_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(25,0);
    temp = Unicode_block_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-UNICODE-BLOCK-COUNT */
Object outstanding_unicode_block_count()
{
    Object def_structure_unicode_block_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(25,1);
    gensymed_symbol = IFIX(Unicode_block_count);
    def_structure_unicode_block_variable = Chain_of_available_unicode_blocks;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_unicode_block_variable))
	goto end_loop;
    def_structure_unicode_block_variable = 
	    ISVREF(def_structure_unicode_block_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-UNICODE-BLOCK-1 */
Object reclaim_unicode_block_1(unicode_block)
    Object unicode_block;
{
    Object temp, svref_arg_2;

    x_note_fn_call(25,2);
    inline_note_reclaim_cons(unicode_block,Nil);
    temp = ISVREF(Chain_of_available_unicode_blocks_vector,
	    IFIX(Current_thread_index));
    SVREF(unicode_block,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_unicode_blocks_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = unicode_block;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-UNICODE-BLOCK */
Object reclaim_structure_for_unicode_block(unicode_block)
    Object unicode_block;
{
    x_note_fn_call(25,3);
    return reclaim_unicode_block_1(unicode_block);
}

static Object Qg2_defstruct_structure_name_unicode_block_g2_struct;  /* g2-defstruct-structure-name::unicode-block-g2-struct */

/* MAKE-PERMANENT-UNICODE-BLOCK-STRUCTURE-INTERNAL */
Object make_permanent_unicode_block_structure_internal()
{
    Object def_structure_unicode_block_variable;
    Object defstruct_g2_unicode_block_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(25,4);
    def_structure_unicode_block_variable = Nil;
    atomic_incff_symval(Qunicode_block_count,FIX((SI_Long)1L));
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
Object make_unicode_block_1()
{
    Object def_structure_unicode_block_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(25,5);
    def_structure_unicode_block_variable = 
	    ISVREF(Chain_of_available_unicode_blocks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_unicode_block_variable) {
	svref_arg_1 = Chain_of_available_unicode_blocks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_unicode_block_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_unicode_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_unicode_block_g2_struct;
    }
    else
	def_structure_unicode_block_variable = 
		make_permanent_unicode_block_structure_internal();
    inline_note_allocate_cons(def_structure_unicode_block_variable,Nil);
    return VALUES_1(def_structure_unicode_block_variable);
}

Object Unicode_block_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_unicode_block_names, Qall_unicode_block_names);

/* UNICODE-BLOCK-< */
Object unicode_block_lt(unicode_block_1,unicode_block_2)
    Object unicode_block_1, unicode_block_2;
{
    Object temp, temp_1;

    x_note_fn_call(25,6);
    temp = ISVREF(unicode_block_1,(SI_Long)2L);
    temp_1 = ISVREF(unicode_block_2,(SI_Long)2L);
    return VALUES_1(FIXNUM_LT(FIRST(temp),FIRST(temp_1)) ? T : Nil);
}

void letters_INIT()
{
    Object temp, reclaim_structure_for_unicode_block_1;
    Object all_unicode_block_names_new_value, unicode_block;
    Object Qunicode_block, Qgreek_extended, list_constant_53, AB_package;
    Object Qlatin_extended_additional, list_constant_52, Qhangul_jamo;
    Object list_constant_51, Qgeorgian, list_constant_50, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_46, Klower_range;
    Object Koffset_to_upper, Qmiscellaneous_2, list_constant_45, Qarmenian;
    Object list_constant_44, list_constant_43, list_constant_42;
    Object list_constant_41, Qcyrillic_extended, list_constant_40, Qcyrillic;
    Object list_constant_39, list_constant_38, list_constant_37;
    Object list_constant_36, list_constant_35, list_constant_13;
    Object list_constant_34, Klower_odd_range, list_constant_31;
    Object list_constant_33, list_constant_5, list_constant_32;
    Object Qgreek_symbols_and_coptic, list_constant_30, Qbasic_greek;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object Qmiscellaneous, list_constant_23, Qlatin_extended_a;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_16, Klower_even_range, list_constant_15;
    Object list_constant_14, list_constant_12, Qlatin_1_supplement;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_8, list_constant_7, Kuppercase_code, Klowercase_code;
    Object list_constant_6, list_constant_4, Qbasic_latin, list_constant_3;
    Object list_constant_2, list_constant_1, list_constant, Qreclaim_structure;
    Object Qoutstanding_unicode_block_count;
    Object Qunicode_block_structure_memory_usage, Qutilities2;
    Object string_constant_1, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(25,7);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_unicode_block_g2_struct = 
	    STATIC_SYMBOL("UNICODE-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qunicode_block = STATIC_SYMBOL("UNICODE-BLOCK",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    Qunicode_block,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qunicode_block,
	    Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_unicode_block == UNBOUND)
	The_type_description_of_unicode_block = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m83o7y1n83o7y8n8k1l8n0000001l1m8y83-6Dykpk0k0");
    temp = The_type_description_of_unicode_block;
    The_type_description_of_unicode_block = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_unicode_block_g2_struct,
	    The_type_description_of_unicode_block,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qunicode_block,
	    The_type_description_of_unicode_block,Qtype_description_of_type);
    Qoutstanding_unicode_block_count = 
	    STATIC_SYMBOL("OUTSTANDING-UNICODE-BLOCK-COUNT",AB_package);
    Qunicode_block_structure_memory_usage = 
	    STATIC_SYMBOL("UNICODE-BLOCK-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_1 = STATIC_STRING("1q83o7y8s83-uoy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_unicode_block_count);
    push_optimized_constant(Qunicode_block_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_unicode_blocks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-UNICODE-BLOCKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_unicode_blocks,
	    Chain_of_available_unicode_blocks);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_unicode_blocks,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qunicode_block_count = STATIC_SYMBOL("UNICODE-BLOCK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunicode_block_count,Unicode_block_count);
    record_system_variable(Qunicode_block_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_unicode_blocks_vector == UNBOUND)
	Chain_of_available_unicode_blocks_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qunicode_block_structure_memory_usage,
	    STATIC_FUNCTION(unicode_block_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_unicode_block_count,
	    STATIC_FUNCTION(outstanding_unicode_block_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_unicode_block_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_unicode_block,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qunicode_block,
	    reclaim_structure_for_unicode_block_1);
    Unicode_block_prop = Qunicode_block;
    if (All_unicode_block_names == UNBOUND)
	All_unicode_block_names = Nil;
    Qbasic_latin = STATIC_SYMBOL("BASIC-LATIN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qbasic_latin,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_2 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)127L));
    Klower_range = STATIC_SYMBOL("LOWER-RANGE",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,FIX((SI_Long)97L),
	    FIX((SI_Long)122L));
    Koffset_to_upper = STATIC_SYMBOL("OFFSET-TO-UPPER",Pkeyword);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Klower_range,list_constant,
	    Koffset_to_upper,FIX((SI_Long)-32L));
    list_constant_3 = STATIC_CONS(list_constant_1,Qnil);
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qbasic_latin;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_2;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_3;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qbasic_latin,unicode_block,Qunicode_block);
    Qlatin_1_supplement = STATIC_SYMBOL("LATIN-1-SUPPLEMENT",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qlatin_1_supplement,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
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
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qlatin_1_supplement;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_10;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_11;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qlatin_1_supplement,unicode_block,Qunicode_block);
    Qlatin_extended_a = STATIC_SYMBOL("LATIN-EXTENDED-A",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qlatin_extended_a,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
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
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qlatin_extended_a;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_21;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_22;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qlatin_extended_a,unicode_block,Qunicode_block);
    Qmiscellaneous = STATIC_SYMBOL("MISCELLANEOUS",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qmiscellaneous,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)384L),
	    FIX((SI_Long)879L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qmiscellaneous;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_23;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qmiscellaneous,unicode_block,Qunicode_block);
    Qbasic_greek = STATIC_SYMBOL("BASIC-GREEK",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qbasic_greek,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
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
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qbasic_greek;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_28;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_29;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qbasic_greek,unicode_block,Qunicode_block);
    Qgreek_symbols_and_coptic = STATIC_SYMBOL("GREEK-SYMBOLS-AND-COPTIC",
	    AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qgreek_symbols_and_coptic,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_30 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)976L),
	    FIX((SI_Long)1023L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qgreek_symbols_and_coptic;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_30;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qgreek_symbols_and_coptic,unicode_block,
	    Qunicode_block);
    Qcyrillic = STATIC_SYMBOL("CYRILLIC",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qcyrillic,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
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
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qcyrillic;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_38;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_39;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qcyrillic,unicode_block,Qunicode_block);
    Qcyrillic_extended = STATIC_SYMBOL("CYRILLIC-EXTENDED",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qcyrillic_extended,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_40 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1152L),
	    FIX((SI_Long)1279L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qcyrillic_extended;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_40;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qcyrillic_extended,unicode_block,Qunicode_block);
    Qarmenian = STATIC_SYMBOL("ARMENIAN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qarmenian,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_43 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1280L),
	    FIX((SI_Long)1423L));
    list_constant_41 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1377L),
	    FIX((SI_Long)1414L));
    list_constant_42 = STATIC_LIST((SI_Long)4L,Klower_range,
	    list_constant_41,Koffset_to_upper,FIX((SI_Long)-48L));
    list_constant_44 = STATIC_CONS(list_constant_42,Qnil);
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qarmenian;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_43;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_44;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qarmenian,unicode_block,Qunicode_block);
    Qmiscellaneous_2 = STATIC_SYMBOL("MISCELLANEOUS-2",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qmiscellaneous_2,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_45 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1424L),
	    FIX((SI_Long)3839L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qmiscellaneous_2;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_45;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qmiscellaneous_2,unicode_block,Qunicode_block);
    Qgeorgian = STATIC_SYMBOL("GEORGIAN",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qgeorgian,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_49 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4256L),
	    FIX((SI_Long)4351L));
    list_constant_46 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4304L),
	    FIX((SI_Long)4342L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Koffset_to_upper,
	    FIX((SI_Long)-48L));
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Klower_range,
	    list_constant_46,list_constant_47);
    list_constant_50 = STATIC_CONS(list_constant_48,Qnil);
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qgeorgian;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_49;
    SVREF(unicode_block,FIX((SI_Long)3L)) = list_constant_50;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qt;
    mutate_global_property(Qgeorgian,unicode_block,Qunicode_block);
    Qhangul_jamo = STATIC_SYMBOL("HANGUL-JAMO",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qhangul_jamo,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_51 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4352L),
	    FIX((SI_Long)4607L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qhangul_jamo;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_51;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qhangul_jamo,unicode_block,Qunicode_block);
    Qlatin_extended_additional = STATIC_SYMBOL("LATIN-EXTENDED-ADDITIONAL",
	    AB_package);
    all_unicode_block_names_new_value = adjoin(2,
	    Qlatin_extended_additional,All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_52 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7680L),
	    FIX((SI_Long)7935L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qlatin_extended_additional;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_52;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qlatin_extended_additional,unicode_block,
	    Qunicode_block);
    Qgreek_extended = STATIC_SYMBOL("GREEK-EXTENDED",AB_package);
    all_unicode_block_names_new_value = adjoin(2,Qgreek_extended,
	    All_unicode_block_names);
    All_unicode_block_names = all_unicode_block_names_new_value;
    list_constant_53 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7936L),
	    FIX((SI_Long)8191L));
    unicode_block = make_unicode_block_1();
    SVREF(unicode_block,FIX((SI_Long)1L)) = Qgreek_extended;
    SVREF(unicode_block,FIX((SI_Long)2L)) = list_constant_53;
    SVREF(unicode_block,FIX((SI_Long)3L)) = Qnil;
    SVREF(unicode_block,FIX((SI_Long)4L)) = Qnil;
    mutate_global_property(Qgreek_extended,unicode_block,Qunicode_block);
}
