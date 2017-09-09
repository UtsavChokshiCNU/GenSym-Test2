/* kfep1.c
 * Input file:  kfep1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kfep1.h"


/* COPY-MANAGED-LISP-STRING */
Object copy_managed_lisp_string(string_1,start_index,number_of_characters)
    Object string_1, start_index, number_of_characters;
{
    x_note_fn_call(120,0);
    return gensym_string_substring(string_1,start_index,
	    FIXNUM_ADD(start_index,number_of_characters));
}

/* COPY-TEXT-STRING-AS-MANAGED-LISP-STRING */
Object copy_text_string_as_managed_lisp_string(text_string,start_index,
	    number_of_characters)
    Object text_string, start_index, number_of_characters;
{
    Object length_1, string_1, char_1;
    SI_Long i, ab_loop_repeat_;
    char simple_p;

    x_note_fn_call(120,1);
    length_1 = FIXNUM_MINUS(number_of_characters,start_index);
    string_1 = obtain_simple_gensym_string(length_1);
    simple_p =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    i = IFIX(start_index);
    ab_loop_repeat_ = IFIX(length_1);
    char_1 = Nil;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    char_1 = CODE_CHAR(FIX(UBYTE_16_ISAREF_1(text_string,i)));
    if (simple_p)
	SET_ISCHAR(string_1,i,ICHAR_CODE(char_1));
    else
	SET_ICHAR(string_1,i,ICHAR_CODE(char_1));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(string_1);
}

/* COPY-LISP-STRING-TO-TARGET */
Object copy_lisp_string_to_target(source_string,target_string,
	    source_start_index,target_start_index,number_of_characters)
    Object source_string, target_string, source_start_index;
    Object target_start_index, number_of_characters;
{
    Object source_char, ab_loop_iter_flag_;
    SI_Long ab_loop_repeat_, i, j;
    char source_string_is_simple_qm, target_string_is_simple_qm;

    x_note_fn_call(120,2);
    source_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(source_string);
    target_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(target_string);
    ab_loop_repeat_ = IFIX(number_of_characters);
    i = IFIX(source_start_index);
    j = IFIX(target_start_index);
    source_char = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ab_loop_iter_flag_)) {
	i = i + (SI_Long)1L;
	j = j + (SI_Long)1L;
    }
    source_char = source_string_is_simple_qm ? CHR(ISCHAR(source_string,
	    i)) : CHR(ICHAR(source_string,i));
    if (target_string_is_simple_qm)
	SET_ISCHAR(target_string,j,ICHAR_CODE(source_char));
    else
	SET_ICHAR(target_string,j,ICHAR_CODE(source_char));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(number_of_characters);
}

/* COPY-LISP-STRING-WITH-CHANGE-TO-UPPER-CASE */
Object copy_lisp_string_with_change_to_upper_case(string_1)
    Object string_1;
{
    Object new_string, temp, schar_new_value;
    SI_Long string_length, i, ab_loop_bind_;
    char string_is_simple_qm;

    x_note_fn_call(120,3);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_length = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    new_string = obtain_simple_gensym_string(FIX(string_length));
    i = (SI_Long)0L;
    ab_loop_bind_ = string_length;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    temp = string_is_simple_qm ? CHR(ISCHAR(string_1,i)) : 
	    CHR(ICHAR(string_1,i));
    schar_new_value = CHAR_UPCASE(temp);
    SET_ISCHAR(new_string,i,ICHAR_CODE(schar_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(new_string);
    return VALUES_1(Qnil);
}

/* CONVERT-N-BYTES-TO-JIS-STRING */
Object convert_n_bytes_to_jis_string(string_1,number_of_bytes_to_convert)
    Object string_1, number_of_bytes_to_convert;
{
    Object new_string;
    SI_Long i, ab_loop_bind_;
    char string_is_simple_qm;
    char schar_new_value;

    x_note_fn_call(120,4);
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    new_string = obtain_simple_gensym_string(number_of_bytes_to_convert);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_bytes_to_convert);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    schar_new_value = string_is_simple_qm ? ISCHAR(string_1,i) : 
	    ICHAR(string_1,i);
    SET_ISCHAR(new_string,i,schar_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(new_string);
    return VALUES_1(Qnil);
}

/* READ-32-BIT-BIG-ENDIAN-NUMBER-FROM-STRING */
Object read_32_bit_big_endian_number_from_string(string_1,start_index)
    Object string_1, start_index;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(120,5);
    if (PUSH_AREA(Dynamic_area,0))
	result = add(FIX((IFIX(CHAR_CODE(CHAR(string_1,
		FIXNUM_ADD1(start_index)))) << (SI_Long)16L) + 
		(IFIX(CHAR_CODE(CHR(ICHAR(string_1,IFIX(start_index) + 
		(SI_Long)2L)))) << (SI_Long)8L) + 
		IFIX(CHAR_CODE(CHR(ICHAR(string_1,IFIX(start_index) + 
		(SI_Long)3L))))),ash(CHAR_CODE(CHAR(string_1,start_index)),
		FIX((SI_Long)24L)));
    POP_AREA(0);
    return result;
}

/* READ-32-BIT-BIG-ENDIAN-NUMBER-FROM-STRING-WITH-FIXNUM-LIMIT */
Object read_32_bit_big_endian_number_from_string_with_fixnum_limit(string_1,
	    start_index,fixnum_limit)
    Object string_1, start_index, fixnum_limit;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(120,6);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = lmin(add(FIX((IFIX(CHAR_CODE(CHAR(string_1,
		FIXNUM_ADD1(start_index)))) << (SI_Long)16L) + 
		(IFIX(CHAR_CODE(CHR(ICHAR(string_1,IFIX(start_index) + 
		(SI_Long)2L)))) << (SI_Long)8L) + 
		IFIX(CHAR_CODE(CHR(ICHAR(string_1,IFIX(start_index) + 
		(SI_Long)3L))))),ash(CHAR_CODE(CHAR(string_1,start_index)),
		FIX((SI_Long)24L))),fixnum_limit);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* STRNCMP-FUNCTION */
Object strncmp_function(string_1,string_2,n_1,start_1,start_2)
    Object string_1, string_2, n_1, start_1, start_2;
{
    Object char_1, char_2, gensym_string;
    SI_Long gensymed_symbol, gensymed_symbol_1, limit_1, limit_2, index_1;
    SI_Long ab_loop_bind_, index_2;
    char string_1_is_simple_qm, string_2_is_simple_qm, string_is_simple_qm;

    x_note_fn_call(120,7);
    string_1_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_2_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_2);
    gensymed_symbol = string_1_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    gensymed_symbol_1 = IFIX(start_1);
    limit_1 = gensymed_symbol - gensymed_symbol_1;
    gensymed_symbol = string_2_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_2)) : IFIX(length(string_2));
    gensymed_symbol_1 = IFIX(start_2);
    limit_2 = gensymed_symbol - gensymed_symbol_1;
    char_1 = Nil;
    char_2 = Nil;
    if ( !TRUEP(n_1))
	n_1 = FIX(MAX(limit_1,limit_2));
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (index_1 >= limit_1) {
	if (index_1 >= limit_2)
	    return VALUES_1(FIX((SI_Long)0L));
	else {
	    gensym_string = string_2;
	    index_1 = index_1 + IFIX(start_2);
	    string_is_simple_qm = string_2_is_simple_qm;
	    return VALUES_1(FIXNUM_NEGATE(CHAR_CODE(string_is_simple_qm ? 
		    CHR(ISCHAR(gensym_string,index_1)) : 
		    CHR(ICHAR(gensym_string,index_1)))));
	}
    }
    else if (index_1 >= limit_2) {
	gensym_string = string_1;
	index_1 = index_1 + IFIX(start_1);
	string_is_simple_qm = string_1_is_simple_qm;
	return VALUES_1(CHAR_CODE(string_is_simple_qm ? 
		CHR(ISCHAR(gensym_string,index_1)) : 
		CHR(ICHAR(gensym_string,index_1))));
    }
    else {
	gensym_string = string_1;
	index_2 = index_1 + IFIX(start_1);
	string_is_simple_qm = string_1_is_simple_qm;
	char_1 = CHAR_CODE(string_is_simple_qm ? CHR(ISCHAR(gensym_string,
		index_2)) : CHR(ICHAR(gensym_string,index_2)));
	gensym_string = string_2;
	index_2 = index_1 + IFIX(start_2);
	string_is_simple_qm = string_2_is_simple_qm;
	char_2 = CHAR_CODE(string_is_simple_qm ? CHR(ISCHAR(gensym_string,
		index_2)) : CHR(ICHAR(gensym_string,index_2)));
	if (IFIX(char_1) == (SI_Long)0L) {
	    if (IFIX(char_2) == (SI_Long)0L)
		return VALUES_1(FIX((SI_Long)0L));
	    else
		return VALUES_1(FIXNUM_NEGATE(char_2));
	}
	else if (IFIX(char_2) == (SI_Long)0L)
	    return VALUES_1(char_1);
	else if (FIXNUM_NE(char_1,char_2))
	    return VALUES_1(FIXNUM_MINUS(char_1,char_2));
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX((SI_Long)0L));
    return VALUES_1(Qnil);
}

/* STRCAT-1 */
Object strcat_1(string_1,string_2,offset_1,offset_2)
    Object string_1, string_2, offset_1, offset_2;
{
    Object start_index, character_1;
    SI_Long length_of_string_1, i, j;
    char string_1_is_simple_qm, string_2_is_simple_qm;

    x_note_fn_call(120,8);
    string_1_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_1);
    string_2_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(string_2);
    length_of_string_1 = string_1_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1)) : IFIX(length(string_1));
    start_index = offset_1;
  next_loop:
    if ( ! !EQ(string_1_is_simple_qm ? SCHAR(string_1,start_index) : 
	    CHAR(string_1,start_index),CHR('\000')))
	goto end_loop;
    start_index = FIXNUM_ADD1(start_index);
    goto next_loop;
  end_loop:
    i = IFIX(offset_2);
    j = IFIX(start_index);
    character_1 = Nil;
  next_loop_1:
    character_1 = string_2_is_simple_qm ? CHR(ISCHAR(string_2,i)) : 
	    CHR(ICHAR(string_2,i));
    if (j >= length_of_string_1)
	error((SI_Long)3L,"Index ~d is past the end of string ~s!",FIX(j),
		string_1);
    if (string_1_is_simple_qm)
	SET_ISCHAR(string_1,j,ICHAR_CODE(character_1));
    else
	SET_ICHAR(string_1,j,ICHAR_CODE(character_1));
    if (EQ(character_1,CHR('\000')))
	goto end_loop_1;
    i = i + (SI_Long)1L;
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(string_1);
}

/* G2-STREAM-READ-32-BIT-BIG-ENDIAN-NUMBER */
Object g2_stream_read_32_bit_big_endian_number(stream,require_fixnum_qm)
    Object stream, require_fixnum_qm;
{
    Object char_1, char_2, char_3, char_4, byte_1, byte_2, byte_3, byte_4;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(120,9);
    char_1 = Nil;
    char_2 = Nil;
    char_3 = Nil;
    char_4 = Nil;
    byte_1 = Nil;
    byte_2 = Nil;
    byte_3 = Nil;
    byte_4 = Nil;
    char_1 = g2_stream_read_char(stream);
    if (char_1) {
	char_2 = g2_stream_read_char(stream);
	temp = TRUEP(char_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	char_3 = g2_stream_read_char(stream);
	temp = TRUEP(char_3);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	char_4 = g2_stream_read_char(stream);
	temp = TRUEP(char_4);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	byte_1 = CHAR_CODE(char_1);
	byte_2 = CHAR_CODE(char_2);
	byte_3 = CHAR_CODE(char_3);
	byte_4 = CHAR_CODE(char_4);
	if (require_fixnum_qm) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		result = logand(add(FIX(IFIX(byte_4) + (IFIX(byte_3) << 
			(SI_Long)8L) + (IFIX(byte_2) << (SI_Long)16L)),
			ash(byte_1,FIX((SI_Long)24L))),Most_positive_fixnum);
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else {
	    if (PUSH_AREA(Dynamic_area,0))
		result = add(FIX(IFIX(byte_4) + (IFIX(byte_3) << 
			(SI_Long)8L) + (IFIX(byte_2) << (SI_Long)16L)),
			ash(byte_1,FIX((SI_Long)24L)));
	    POP_AREA(0);
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_master_header, Qkfep_master_header);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_master_header_in_characters, Qkfep_master_header_in_characters);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_header, Qkfep_kojin_header);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_tablemax, Qkfep_tablemax);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_m_table, Qkfep_m_table);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_index_file_stream, Qkfep_index_file_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_main_file_stream, Qkfep_main_file_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_file_stream, Qkfep_kojin_file_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_usedbits, Qkfep_kojin_usedbits);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_bunpobits, Qkfep_kojin_bunpobits);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_index, Qkfep_kojin_index);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kojin_hyolen, Qkfep_kojin_hyolen);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_batchyomi, Qkfep_batchyomi);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_battable, Qkfep_battable);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_batchyomilen, Qkfep_batchyomilen);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kka_usetblnum, Qkfep_kka_usetblnum);

Object Kfep_ta_index = UNBOUND;

Object Kfep_sa_index = UNBOUND;

Object Kfep_jd_index = UNBOUND;

Object Kfep_jy_index = UNBOUND;

Object Kfep_kk_index = UNBOUND;

Object The_type_description_of_kfep_master = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_kfep_masters, Qchain_of_available_kfep_masters);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_master_count, Qkfep_master_count);

Object Chain_of_available_kfep_masters_vector = UNBOUND;

/* KFEP-MASTER-STRUCTURE-MEMORY-USAGE */
Object kfep_master_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(120,10);
    temp = Kfep_master_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-KFEP-MASTER-COUNT */
Object outstanding_kfep_master_count()
{
    Object def_structure_kfep_master_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(120,11);
    gensymed_symbol = IFIX(Kfep_master_count);
    def_structure_kfep_master_variable = Chain_of_available_kfep_masters;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_kfep_master_variable))
	goto end_loop;
    def_structure_kfep_master_variable = 
	    ISVREF(def_structure_kfep_master_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-KFEP-MASTER-1 */
Object reclaim_kfep_master_1(kfep_master)
    Object kfep_master;
{
    Object temp, svref_arg_2;

    x_note_fn_call(120,12);
    inline_note_reclaim_cons(kfep_master,Nil);
    temp = ISVREF(Chain_of_available_kfep_masters_vector,
	    IFIX(Current_thread_index));
    SVREF(kfep_master,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_kfep_masters_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = kfep_master;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KFEP-MASTER */
Object reclaim_structure_for_kfep_master(kfep_master)
    Object kfep_master;
{
    x_note_fn_call(120,13);
    return reclaim_kfep_master_1(kfep_master);
}

static Object Qg2_defstruct_structure_name_kfep_master_g2_struct;  /* g2-defstruct-structure-name::kfep-master-g2-struct */

/* MAKE-PERMANENT-KFEP-MASTER-STRUCTURE-INTERNAL */
Object make_permanent_kfep_master_structure_internal()
{
    Object def_structure_kfep_master_variable;
    Object defstruct_g2_kfep_master_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(120,14);
    def_structure_kfep_master_variable = Nil;
    atomic_incff_symval(Qkfep_master_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_kfep_master_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_kfep_master_variable = the_array;
	SVREF(defstruct_g2_kfep_master_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kfep_master_g2_struct;
	def_structure_kfep_master_variable = defstruct_g2_kfep_master_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_kfep_master_variable);
}

/* MAKE-KFEP-MASTER-1 */
Object make_kfep_master_1()
{
    Object def_structure_kfep_master_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(120,15);
    def_structure_kfep_master_variable = 
	    ISVREF(Chain_of_available_kfep_masters_vector,
	    IFIX(Current_thread_index));
    if (def_structure_kfep_master_variable) {
	svref_arg_1 = Chain_of_available_kfep_masters_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_kfep_master_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_kfep_master_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kfep_master_g2_struct;
    }
    else
	def_structure_kfep_master_variable = 
		make_permanent_kfep_master_structure_internal();
    inline_note_allocate_cons(def_structure_kfep_master_variable,Nil);
    return VALUES_1(def_structure_kfep_master_variable);
}

Object The_type_description_of_kfep_batch = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_kfep_batchs, Qchain_of_available_kfep_batchs);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_batch_count, Qkfep_batch_count);

Object Chain_of_available_kfep_batchs_vector = UNBOUND;

/* KFEP-BATCH-STRUCTURE-MEMORY-USAGE */
Object kfep_batch_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(120,16);
    temp = Kfep_batch_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-KFEP-BATCH-COUNT */
Object outstanding_kfep_batch_count()
{
    Object def_structure_kfep_batch_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(120,17);
    gensymed_symbol = IFIX(Kfep_batch_count);
    def_structure_kfep_batch_variable = Chain_of_available_kfep_batchs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_kfep_batch_variable))
	goto end_loop;
    def_structure_kfep_batch_variable = 
	    ISVREF(def_structure_kfep_batch_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-KFEP-BATCH-1 */
Object reclaim_kfep_batch_1(kfep_batch)
    Object kfep_batch;
{
    Object temp, svref_arg_2;

    x_note_fn_call(120,18);
    inline_note_reclaim_cons(kfep_batch,Nil);
    temp = ISVREF(Chain_of_available_kfep_batchs_vector,
	    IFIX(Current_thread_index));
    SVREF(kfep_batch,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_kfep_batchs_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = kfep_batch;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-KFEP-BATCH */
Object reclaim_structure_for_kfep_batch(kfep_batch)
    Object kfep_batch;
{
    x_note_fn_call(120,19);
    return reclaim_kfep_batch_1(kfep_batch);
}

static Object Qg2_defstruct_structure_name_kfep_batch_g2_struct;  /* g2-defstruct-structure-name::kfep-batch-g2-struct */

/* MAKE-PERMANENT-KFEP-BATCH-STRUCTURE-INTERNAL */
Object make_permanent_kfep_batch_structure_internal()
{
    Object def_structure_kfep_batch_variable, defstruct_g2_kfep_batch_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(120,20);
    def_structure_kfep_batch_variable = Nil;
    atomic_incff_symval(Qkfep_batch_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_kfep_batch_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_kfep_batch_variable = the_array;
	SVREF(defstruct_g2_kfep_batch_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kfep_batch_g2_struct;
	def_structure_kfep_batch_variable = defstruct_g2_kfep_batch_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_kfep_batch_variable);
}

/* MAKE-KFEP-BATCH-1 */
Object make_kfep_batch_1()
{
    Object def_structure_kfep_batch_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(120,21);
    def_structure_kfep_batch_variable = 
	    ISVREF(Chain_of_available_kfep_batchs_vector,
	    IFIX(Current_thread_index));
    if (def_structure_kfep_batch_variable) {
	svref_arg_1 = Chain_of_available_kfep_batchs_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_kfep_batch_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_kfep_batch_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_kfep_batch_g2_struct;
    }
    else
	def_structure_kfep_batch_variable = 
		make_permanent_kfep_batch_structure_internal();
    inline_note_allocate_cons(def_structure_kfep_batch_variable,Nil);
    return VALUES_1(def_structure_kfep_batch_variable);
}

Object Kfep_gobisetu1 = UNBOUND;

Object Kfep_gobisetu2 = UNBOUND;

Object Kfep_jyodou_array = UNBOUND;

Object Kfep_jyosi_array = UNBOUND;

Object Kfep_keiyo_array = UNBOUND;

Object Kfep_taigen_array = UNBOUND;

Object Kfep_sahen_array = UNBOUND;

/* KFEP-G-GENERIC-FUNCTION */
Object kfep_g_generic_function(string_1,start_index,len,bun,index_array,
	    main_array,main_array_length)
    Object string_1, start_index, len, bun, index_array, main_array;
    Object main_array_length;
{
    Object index_1, st, ed, result_1, index_entry, entry;

    x_note_fn_call(120,22);
    index_1 = FIX((SI_Long)0L);
    st = FIX((SI_Long)-1L);
    ed = FIX((SI_Long)-1L);
    result_1 = FIX((SI_Long)-1L);
    index_entry = Nil;
  next_loop:
    if ( !FIXNUM_LT(index_1,main_array_length))
	goto end_loop;
    index_entry = ISVREF(index_array,IFIX(index_1));
    if (FIXNUM_EQ(ISVREF(index_entry,(SI_Long)0L),len)) {
	st = ISVREF(index_entry,(SI_Long)1L);
	ed = ISVREF(index_entry,(SI_Long)2L);
    }
    index_1 = FIXNUM_ADD1(index_1);
    goto next_loop;
  end_loop:;
    if (IFIX(st) != (SI_Long)-1L) {
	index_1 = st;
	entry = Nil;
      next_loop_1:
	if ( !FIXNUM_LE(index_1,ed))
	    goto end_loop_1;
	entry = ISVREF(main_array,IFIX(index_1));
	if (IFIX(kfep_kkastrncmp(string_1,ISVREF(entry,(SI_Long)0L),len,
		start_index,FIX((SI_Long)0L))) == (SI_Long)0L) {
	    bun = ISVREF(entry,(SI_Long)3L);
	    result_1 = FIX((SI_Long)0L);
	    goto end_1;
	}
	index_1 = FIXNUM_ADD1(index_1);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    return VALUES_2(result_1,bun);
}

/* KFEP-CHKCATTR */
Object kfep_chkcattr(ch,start_index_init)
    Object ch, start_index_init;
{
    Object char_0, char_1;
    SI_Long start_index;

    x_note_fn_call(120,23);
    start_index = IFIX(start_index_init);
    char_0 = CHAR_CODE(CHR(ICHAR(ch,(SI_Long)0L + start_index)));
    char_1 = CHAR_CODE(CHR(ICHAR(ch,start_index + (SI_Long)1L)));
    if (IFIX(char_0) == (SI_Long)36L && IFIX(char_1) == (SI_Long)115L)
	return VALUES_1(FIX((SI_Long)1L));
    else if (IFIX(char_0) == (SI_Long)36L && (IFIX(char_1) == (SI_Long)33L 
	    || IFIX(char_1) == (SI_Long)35L || IFIX(char_1) == 
	    (SI_Long)37L || IFIX(char_1) == (SI_Long)39L || IFIX(char_1) 
	    == (SI_Long)41L || IFIX(char_1) == (SI_Long)67L || 
	    IFIX(char_1) == (SI_Long)99L || IFIX(char_1) == (SI_Long)101L 
	    || IFIX(char_1) == (SI_Long)103L || IFIX(char_1) == (SI_Long)110L))
	return VALUES_1(FIX((SI_Long)2L));
    else if (IFIX(char_0) == (SI_Long)33L && (IFIX(char_1) == (SI_Long)34L 
	    || IFIX(char_1) == (SI_Long)35L))
	return VALUES_1(FIX((SI_Long)3L));
    else if (IFIX(char_0) >= (SI_Long)33L && IFIX(char_0) <= (SI_Long)35L 
	    && IFIX(char_1) >= (SI_Long)33L && IFIX(char_1) <= (SI_Long)126L)
	return VALUES_1(FIX((SI_Long)4L));
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* KFEP-G-DOUSI */
Object kfep_g_dousi(string_1,start_index,len,bun)
    Object string_1, start_index, len, bun;
{
    Object gobisetu, gobitype_qm, temp;
    SI_Long gobisetu_length, index_1, ab_loop_bind_;

    x_note_fn_call(120,24);
    if (IFIX(len) > (SI_Long)4L)
	return VALUES_2(FIX((SI_Long)-1L),bun);
    else {
	gobisetu = IFIX(len) == (SI_Long)4L ? Kfep_gobisetu2 : Kfep_gobisetu1;
	gobisetu_length = IFIX(len) == (SI_Long)4L ? (SI_Long)111L : 
		(SI_Long)110L;
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = gobisetu_length;
	gobitype_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	gobitype_qm = ISVREF(gobisetu,index_1);
	if (gobitype_qm && IFIX(kfep_kkastrncmp(string_1,
		ISVREF(gobitype_qm,(SI_Long)0L),len,start_index,
		FIX((SI_Long)0L))) == (SI_Long)0L) {
	    temp = ISVREF(gobitype_qm,(SI_Long)1L);
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 4:
		    bun = FIX((SI_Long)1L | IFIX(bun));
		    break;
		  case 7:
		    bun = FIX((SI_Long)2L | IFIX(bun));
		    break;
		  case 8:
		    bun = FIX((SI_Long)4L | IFIX(bun));
		    break;
		  case 14:
		    bun = FIX((SI_Long)8L | IFIX(bun));
		    break;
		  case 15:
		    bun = FIX((SI_Long)16L | IFIX(bun));
		    break;
		  default:
		    break;
		}
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	return VALUES_2(FIX((SI_Long)1L),bun);
    }
}

static Object string_constant;     /* "$H" */

static Object string_constant_1;   /* "$?$k" */

/* KFEP-CHKBUNPO */
Object kfep_chkbunpo(hyoki,hlen_init,substring,len_init)
    Object hyoki, hlen_init, substring, len_init;
{
    Object result_qm, n_1, total, ok, t_var, i, d, sbun, wbun, g_sahen;
    Object g_taigen, g_keiyou, g_jyodou, g_jyosi, incff_1_arg;
    SI_Long hlen, len, bunpo, pat, sav, n_new_value;
    char hyoki_string_is_simple_qm;
    Object result;

    x_note_fn_call(120,25);
    hlen = IFIX(hlen_init);
    len = IFIX(len_init);
    result_qm = Nil;
    bunpo = (SI_Long)0L;
    pat = (SI_Long)0L;
    n_1 = FIX(len);
    total = FIX((SI_Long)0L);
    sav = len;
    ok = FIX((SI_Long)0L);
    t_var = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
    d = FIX((SI_Long)0L);
    sbun = FIX((SI_Long)0L);
    wbun = FIX((SI_Long)0L);
    hyoki_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(hyoki);
    bunpo = (SI_Long)134217727L;
    sbun = FIX((SI_Long)134217727L);
    if (len == (SI_Long)0L)
	result_qm = FIX((SI_Long)0L);
    else
      retry: {
      next_loop:
	if ( !(IFIX(n_1) > (SI_Long)0L))
	    goto end_loop;
	t_var = FIX((SI_Long)0L);
	i = kfep_chkcattr(substring,total);
	if (IFIX(ok) == (SI_Long)0L) {
	    result = kfep_g_dousi(substring,total,n_1,wbun);
	    MVS_2(result,d,wbun);
	    if (IFIX(d) > (SI_Long)0L) {
		sbun = FIX((SI_Long)32L | IFIX(sbun));
		sbun = FIX((SI_Long)64L | IFIX(sbun));
		sbun = FIX((SI_Long)128L | IFIX(sbun));
		sbun = FIX((SI_Long)256L | IFIX(sbun));
		sbun = FIX((SI_Long)512L | IFIX(sbun));
		sbun = FIX((SI_Long)1024L | IFIX(sbun));
		t_var = FIX((SI_Long)1L);
		ok = FIX((SI_Long)0L);
		pat = (SI_Long)3L;
		if ((SI_Long)0L != ((SI_Long)1L & IFIX(wbun))) {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)4L),
			    hyoki_string_is_simple_qm ? T : Nil)) {
			sbun = FIX((SI_Long)1L | IFIX(sbun));
			ok = FIXNUM_ADD1(ok);
		    }
		}
		if ((SI_Long)0L != ((SI_Long)2L & IFIX(wbun))) {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)7L),
			    hyoki_string_is_simple_qm ? T : Nil)) {
			sbun = FIX((SI_Long)2L | IFIX(sbun));
			ok = FIXNUM_ADD1(ok);
		    }
		}
		if ((SI_Long)0L != ((SI_Long)4L & IFIX(wbun))) {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)8L),
			    hyoki_string_is_simple_qm ? T : Nil)) {
			sbun = FIX((SI_Long)4L | IFIX(sbun));
			ok = FIXNUM_ADD1(ok);
		    }
		}
		if ((SI_Long)0L != ((SI_Long)8L & IFIX(wbun))) {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)14L),
			    hyoki_string_is_simple_qm ? T : Nil)) {
			sbun = FIX((SI_Long)8L | IFIX(sbun));
			ok = FIXNUM_ADD1(ok);
		    }
		}
		if ((SI_Long)0L != ((SI_Long)16L & IFIX(wbun))) {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)15L),
			    hyoki_string_is_simple_qm ? T : Nil)) {
			sbun = FIX((SI_Long)16L | IFIX(sbun));
			ok = FIXNUM_ADD1(ok);
		    }
		}
		if (IFIX(ok) != (SI_Long)0L) {
		    result_qm = n_1;
		    goto end_break;
		}
		else {
		    sbun = FIX((SI_Long)134217695L & IFIX(sbun));
		    sbun = FIX((SI_Long)134217663L & IFIX(sbun));
		    sbun = FIX((SI_Long)134217599L & IFIX(sbun));
		    sbun = FIX((SI_Long)134217471L & IFIX(sbun));
		    sbun = FIX((SI_Long)134217215L & IFIX(sbun));
		    sbun = FIX((SI_Long)134216703L & IFIX(sbun));
		    pat = (SI_Long)0L;
		    ok = FIX((SI_Long)0L);
		}
	    }
	}
      sasasa:
	if (IFIX(ok) == (SI_Long)0L) {
	    g_sahen = FIX((SI_Long)0L);
	    result = kfep_g_generic_function(substring,total,n_1,wbun,
		    Kfep_sa_index,Kfep_sahen_array,FIX((SI_Long)4L));
	    MVS_2(result,g_sahen,wbun);
	    if (IFIX(g_sahen) == (SI_Long)0L) {
		if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)2L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)14L),
			hyoki_string_is_simple_qm ? T : Nil)) {
		    t_var = FIX((SI_Long)1L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)2L;
		    sbun = wbun;
		    bunpo = IFIX(sbun);
		    result_qm = n_1;
		    goto end_break;
		}
	    }
	}
	if (IFIX(ok) == (SI_Long)0L) {
	    g_taigen = FIX((SI_Long)0L);
	    result = kfep_g_generic_function(substring,total,n_1,wbun,
		    Kfep_ta_index,Kfep_taigen_array,FIX((SI_Long)4L));
	    MVS_2(result,g_taigen,wbun);
	    if (IFIX(g_taigen) == (SI_Long)0L) {
		if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)2L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)21L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)9L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)2L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)20L),
			hyoki_string_is_simple_qm ? T : Nil) || 
			kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)1L),
			hyoki_string_is_simple_qm ? T : Nil)) {
		    if (IFIX(i) == (SI_Long)0L || IFIX(i) == (SI_Long)3L) {
			t_var = FIX((SI_Long)1L);
			ok = FIXNUM_ADD1(ok);
			pat = (SI_Long)1L;
			sbun = wbun;
			bunpo = IFIX(sbun);
			result_qm = n_1;
			goto end_break;
		    }
		}
	    }
	}
	if (IFIX(ok) == (SI_Long)0L) {
	    if (IFIX(kfep_kkastrncmp(substring,string_constant,n_1,total,
		    FIX((SI_Long)0L))) == (SI_Long)0L || 
		    IFIX(kfep_kkastrncmp(substring,string_constant_1,n_1,
		    total,FIX((SI_Long)0L))) == (SI_Long)0L) {
		if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)6L),
			hyoki_string_is_simple_qm ? T : Nil)) {
		    t_var = FIX((SI_Long)1L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)1L;
		    sbun = FIX((SI_Long)16777216L | IFIX(sbun));
		    bunpo = IFIX(sbun);
		    result_qm = n_1;
		    goto end_break;
		}
	    }
	}
	if (IFIX(ok) == (SI_Long)0L) {
	    g_keiyou = FIX((SI_Long)0L);
	    result = kfep_g_generic_function(substring,total,n_1,wbun,
		    Kfep_kk_index,Kfep_keiyo_array,FIX((SI_Long)5L));
	    MVS_2(result,g_keiyou,wbun);
	    if (IFIX(g_keiyou) == (SI_Long)0L) {
		if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)5L),
			hyoki_string_is_simple_qm ? T : Nil)) {
		    t_var = FIX((SI_Long)1L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)2L;
		    sbun = wbun;
		    bunpo = IFIX(sbun);
		    result_qm = n_1;
		    goto end_break;
		}
	    }
	}
      jyo:
	g_jyodou = FIX((SI_Long)0L);
	result = kfep_g_generic_function(substring,total,n_1,wbun,
		Kfep_jd_index,Kfep_jyodou_array,FIX((SI_Long)5L));
	MVS_2(result,g_jyodou,wbun);
	if (IFIX(g_jyodou) == (SI_Long)0L) {
	    if ( !TRUEP(kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)3L),
		    hyoki_string_is_simple_qm ? T : Nil)) &&  
		    !TRUEP(kfep_kka_evalbun(hyoki,FIX(hlen),
		    FIX((SI_Long)1L),hyoki_string_is_simple_qm ? T : Nil))) {
		if (IFIX(ok) == (SI_Long)0L) {
		    t_var = FIX((SI_Long)0L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)2L;
		    sbun = wbun;
		}
	    }
	    goto end_break;
	}
	g_jyosi = FIX((SI_Long)0L);
	result = kfep_g_generic_function(substring,total,n_1,wbun,
		Kfep_jy_index,Kfep_jyosi_array,FIX((SI_Long)4L));
	MVS_2(result,g_jyosi,wbun);
	if (IFIX(g_jyosi) == (SI_Long)0L) {
	    if ( !TRUEP(kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)3L),
		    hyoki_string_is_simple_qm ? T : Nil)) &&  
		    !TRUEP(kfep_kka_evalbun(hyoki,FIX(hlen),
		    FIX((SI_Long)1L),hyoki_string_is_simple_qm ? T : Nil))) {
		if (IFIX(ok) == (SI_Long)0L) {
		    t_var = FIX((SI_Long)0L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)2L;
		}
		else {
		    t_var = FIX((SI_Long)1L);
		    ok = FIXNUM_ADD1(ok);
		    pat = (SI_Long)1L;
		    sbun = wbun;
		    bunpo = IFIX(sbun);
		    result_qm = n_1;
		    goto end_break;
		}
	    }
	    goto end_break;
	}
	if (IFIX(t_var) == (SI_Long)1L && pat == (SI_Long)1L) {
	    bunpo = IFIX(sbun);
	    result_qm = n_1;
	    goto end_break;
	}
	n_new_value = IFIX(n_1) - (SI_Long)2L;
	n_1 = FIX(n_new_value);
	goto next_loop;
      end_loop:
      end_break:
	if ( !TRUEP(result_qm)) {
	    if (IFIX(n_1) <= (SI_Long)0L) {
		if (IFIX(ok) != (SI_Long)0L) {
		    bunpo = IFIX(sbun);
		    result_qm = FIX((SI_Long)0L);
		}
		else {
		    if (kfep_kka_evalbun(hyoki,FIX(hlen),FIX((SI_Long)3L),
			    hyoki_string_is_simple_qm ? T : Nil) || 
			    kfep_kka_evalbun(hyoki,FIX(hlen),
			    FIX((SI_Long)1L),hyoki_string_is_simple_qm ? T 
			    : Nil))
			bunpo = (SI_Long)134217727L;
		    result_qm = FIX((SI_Long)0L);
		}
	    }
	    else {
		incff_1_arg = n_1;
		total = FIXNUM_ADD(total,incff_1_arg);
		n_1 = FIX(sav - IFIX(total));
		goto retry;
	    }
	}
    }
    return VALUES_3(result_qm,FIX(bunpo),FIX(pat));
}

/* KFEP-KKA-EVALBUN */
Object kfep_kka_evalbun(string_1,stringlen,hinsi,string_is_simple_qm)
    Object string_1, stringlen, hinsi, string_is_simple_qm;
{
    Object index_1, golen, count_1, bun, incff_1_arg;

    x_note_fn_call(120,26);
    index_1 = FIX((SI_Long)0L);
    golen = FIX((SI_Long)0L);
    count_1 = FIX((SI_Long)0L);
    bun = FIX((SI_Long)0L);
  next_loop:
    if ( !FIXNUM_LT(index_1,stringlen))
	goto end_loop;
    golen = CHAR_CODE(string_is_simple_qm ? SCHAR(string_1,index_1) : 
	    CHAR(string_1,index_1));
    incff_1_arg = FIXNUM_ADD1(golen);
    index_1 = FIXNUM_ADD(index_1,incff_1_arg);
    bun = CHAR_CODE(string_is_simple_qm ? SCHAR(string_1,index_1) : 
	    CHAR(string_1,index_1));
    if (FIXNUM_EQ(bun,hinsi))
	return VALUES_1(T);
    index_1 = FIXNUM_ADD1(index_1);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* KFEP-KKA-MAINIT */
Object kfep_kka_mainit(switch_1,index_filename,hyoki_filename,kojin_filename)
    Object switch_1, index_filename, hyoki_filename, kojin_filename;
{
    Object temp, svref_new_value, new_kfep_batch, string_1, stream;
    Object kfep_master, new_string, number_of_characters_read_1;
    SI_Long index_1, ab_loop_bind_, number_of_characters_read, string_index;
    SI_Long array_index, incff_1_arg;
    char temp_1;
    XDeclare_area(1);

    x_note_fn_call(120,27);
    if ( !TRUEP(Kfep_m_table)) {
	if (PUSH_AREA(Dynamic_area,0))
	    Kfep_m_table = make_array(1,FIX((SI_Long)370L));
	POP_AREA(0);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)370L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	temp = Kfep_m_table;
	svref_new_value = make_kfep_master_1();
	ISVREF(temp,index_1) = svref_new_value;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    if ( !TRUEP(Kfep_battable)) {
	if (PUSH_AREA(Dynamic_area,0))
	    Kfep_battable = make_array(1,FIX((SI_Long)15L));
	POP_AREA(0);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)15L;
	new_kfep_batch = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	new_kfep_batch = make_kfep_batch_1();
	temp = obtain_simple_gensym_string(FIX((SI_Long)4L));
	SVREF(new_kfep_batch,FIX((SI_Long)3L)) = temp;
	temp = Kfep_battable;
	ISVREF(temp,index_1) = new_kfep_batch;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    Kfep_batchyomi = obtain_simple_gensym_string(FIX((SI_Long)80L));
    Kfep_index_file_stream = 
	    g2_stream_open_for_random_access_binary_input(index_filename);
    temp_1 =  !TRUEP(Kfep_index_file_stream);
    if (temp_1);
    else {
	Kfep_main_file_stream = 
		g2_stream_open_for_random_access_binary_input(hyoki_filename);
	temp_1 =  !TRUEP(Kfep_main_file_stream);
    }
    if (temp_1);
    else {
	Kfep_kojin_file_stream = 
		g2_stream_open_for_random_access_binary_input(kojin_filename);
	temp_1 =  !TRUEP(Kfep_kojin_file_stream);
    }
    if (temp_1) {
	notify_user_of_error_opening_kfep_dictionary_file( 
		!TRUEP(Kfep_index_file_stream) ? index_filename :  
		!TRUEP(Kfep_main_file_stream) ? hyoki_filename : 
		kojin_filename);
	return VALUES_1(Nil);
    }
    else {
	reset_fep_file_stream(Kfep_index_file_stream);
	reset_fep_file_stream(Kfep_main_file_stream);
	string_1 = Kfep_master_header_in_characters;
	number_of_characters_read = (SI_Long)0L;
	string_index = (SI_Long)0L;
	array_index = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)13L;
      next_loop_2:
	if (array_index >= ab_loop_bind_)
	    goto end_loop_2;
	number_of_characters_read = 
		IFIX(g2_stream_read_into_string(Kfep_index_file_stream,
		string_1,FIX((SI_Long)4L),FIX(string_index)));
	temp = Kfep_master_header;
	svref_new_value = 
		read_32_bit_big_endian_number_from_string_with_fixnum_limit(string_1,
		FIX(string_index),Most_positive_fixnum);
	ISVREF(temp,array_index) = svref_new_value;
	incff_1_arg = number_of_characters_read;
	string_index = string_index + incff_1_arg;
	array_index = array_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	Kfep_tablemax = ISVREF(Kfep_master_header,(SI_Long)12L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)370L;
      next_loop_3:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_3;
	stream = Kfep_index_file_stream;
	kfep_master = ISVREF(Kfep_m_table,index_1);
	new_string = Nil;
	number_of_characters_read_1 = Nil;
	new_string = obtain_simple_gensym_string(FIX((SI_Long)20L));
	number_of_characters_read_1 = g2_stream_read_into_string(stream,
		new_string,FIX((SI_Long)20L),FIX((SI_Long)0L));
	if (IFIX(number_of_characters_read_1) == (SI_Long)20L) {
	    SVREF(kfep_master,FIX((SI_Long)1L)) = new_string;
	    new_string = obtain_simple_gensym_string(FIX((SI_Long)4L));
	    number_of_characters_read_1 = 
		    g2_stream_read_into_string(stream,new_string,
		    FIX((SI_Long)4L),FIX((SI_Long)0L));
	    if (IFIX(number_of_characters_read_1) == (SI_Long)4L) {
		SVREF(kfep_master,FIX((SI_Long)2L)) = new_string;
		new_string = obtain_simple_gensym_string(FIX((SI_Long)2L));
		number_of_characters_read_1 = 
			g2_stream_read_into_string(stream,new_string,
			FIX((SI_Long)2L),FIX((SI_Long)0L));
		if (IFIX(number_of_characters_read_1) == (SI_Long)2L)
		    SVREF(kfep_master,FIX((SI_Long)3L)) = new_string;
		else
		    reclaim_gensym_string(new_string);
	    }
	    else
		reclaim_gensym_string(new_string);
	}
	else
	    reclaim_gensym_string(new_string);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	reset_fep_file_stream(Kfep_kojin_file_stream);
	reset_fep_file_stream(Kfep_kojin_file_stream);
	return VALUES_1(T);
    }
}

/* RESET-FEP-FILE-STREAM */
Object reset_fep_file_stream(stream)
    Object stream;
{
    x_note_fn_call(120,28);
    return g2_stream_set_file_position(stream,FIX((SI_Long)0L),
	    FIX((SI_Long)0L));
}

static Object Qkfep_filename;      /* kfep-filename */

static Object string_constant_2;   /* "Error (#~d) opening ~s for input: ~s" */

/* NOTIFY-USER-OF-ERROR-OPENING-KFEP-DICTIONARY-FILE */
Object notify_user_of_error_opening_kfep_dictionary_file(ascii_filename)
    Object ascii_filename;
{
    Object file_name_text_string, error_text_string, temp;

    x_note_fn_call(120,29);
    file_name_text_string = import_text_string(2,ascii_filename,
	    Qkfep_filename);
    error_text_string = most_recent_file_operation_status_as_text();
    temp = Internal_status_of_most_recent_file_operation;
    if (temp);
    else
	temp = FIX((SI_Long)-100000L);
    notify_user(4,string_constant_2,temp,file_name_text_string,
	    error_text_string);
    reclaim_text_string(file_name_text_string);
    return reclaim_text_string(error_text_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Specified_kfep_index_filename_qm, Qspecified_kfep_index_filename_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Specified_kfep_main_filename_qm, Qspecified_kfep_main_filename_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Specified_kfep_kojin_filename_qm, Qspecified_kfep_kojin_filename_qm);

Object Kfep_index_filename = UNBOUND;

Object Kfep_main_filename = UNBOUND;

Object Kfep_kojin_filename = UNBOUND;

/* KFEP-KKASTRNCMP */
Object kfep_kkastrncmp(string_1,string_2,n_1,string_1_start,string_2_start)
    Object string_1, string_2, n_1, string_1_start, string_2_start;
{
    Object index_1_1, index_2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(120,30);
    if (FIXNUM_GT(n_1,FIXNUM_MINUS(length(string_1),string_1_start)) || 
	    FIXNUM_GT(n_1,FIXNUM_MINUS(length(string_2),string_2_start)))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
	index_1_1 = Nil;
	index_2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	index_1_1 = FIX(index_1 + IFIX(string_1_start));
	index_2 = FIX(index_1 + IFIX(string_2_start));
	if (IFIX(CHAR_CODE(CHAR(string_1,index_1_1))) != 
		(IFIX(CHAR_CODE(CHAR(string_2,index_2))) & (SI_Long)127L))
	    return VALUES_1(FIX((SI_Long)1L));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(FIX((SI_Long)0L));
	return VALUES_1(Qnil);
    }
}

/* KFEP-READ-KOJIN-USEDBITS */
Object kfep_read_kojin_usedbits(stream)
    Object stream;
{
    Object char_arg_1, char_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(120,31);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(Kfep_kojin_header,(SI_Long)2L));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    char_arg_1 = Kfep_kojin_usedbits;
    char_new_value = g2_stream_read_char(stream);
    SET_ICHAR(char_arg_1,index_1,ICHAR_CODE(char_new_value));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* KFEP-READ-KOJIN-BUNPOBITS */
Object kfep_read_kojin_bunpobits(stream)
    Object stream;
{
    Object char_arg_1, char_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(120,32);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(Kfep_kojin_header,(SI_Long)2L));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    char_arg_1 = Kfep_kojin_bunpobits;
    char_new_value = g2_stream_read_char(stream);
    SET_ICHAR(char_arg_1,index_1,ICHAR_CODE(char_new_value));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* KFEP-READ-KOJIN-HEADER */
Object kfep_read_kojin_header(stream)
    Object stream;
{
    Object svref_arg_1, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(120,33);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = (SI_Long)20L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    svref_arg_1 = Kfep_kojin_header;
    svref_new_value = g2_stream_read_32_bit_big_endian_number(stream,T);
    ISVREF(svref_arg_1,index_1) = svref_new_value;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* KFEP-KKA-KOINIT */
Object kfep_kka_koinit()
{
    x_note_fn_call(120,34);
    kfep_read_kojin_header(Kfep_kojin_file_stream);
    if (FIXNUM_LT(ISVREF(Kfep_kojin_header,(SI_Long)2L),
	    Maximum_gensym_string_length)) {
	Kfep_kojin_usedbits = 
		obtain_simple_gensym_string(ISVREF(Kfep_kojin_header,
		(SI_Long)2L));
	Kfep_kojin_bunpobits = 
		obtain_simple_gensym_string(ISVREF(Kfep_kojin_header,
		(SI_Long)2L));
	Kfep_kojin_index = make_kojin_index();
	kfep_read_kojin_usedbits(Kfep_kojin_file_stream);
	kfep_read_kojin_bunpobits(Kfep_kojin_file_stream);
	kfep_read_kojin_index(Kfep_kojin_file_stream);
	Kfep_kojin_hyolen = ISVREF(Kfep_kojin_header,(SI_Long)4L);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* KFEP-FIND-USED */
Object kfep_find_used(num)
    Object num;
{
    Object page, pos;
    SI_Long gensymed_symbol, gensymed_symbol_1, mask, shift;

    x_note_fn_call(120,35);
    page = FIXNUM_ADD1(chestnut_floorf_function(num,FIX((SI_Long)4L)));
    pos = chestnut_modf_function(num,FIX((SI_Long)4L));
    gensymed_symbol = (SI_Long)255L;
    gensymed_symbol_1 =  - (IFIX(pos) << (SI_Long)1L);
    mask = IFIX(ash(FIX(gensymed_symbol),FIX(gensymed_symbol_1)));
    shift = (SI_Long)3L - IFIX(pos) << (SI_Long)1L;
    gensymed_symbol = IFIX(CHAR_CODE(CHAR(Kfep_kojin_usedbits,
	    FIXNUM_SUB1(page)))) & mask;
    gensymed_symbol_1 =  - shift;
    return ash(FIX(gensymed_symbol),FIX(gensymed_symbol_1));
}

/* KFEP-FIND-BUNPO */
Object kfep_find_bunpo(num)
    Object num;
{
    Object page, pos;
    SI_Long gensymed_symbol, gensymed_symbol_1, mask, shift, bit2_1;

    x_note_fn_call(120,36);
    page = FIXNUM_ADD1(chestnut_floorf_function(num,FIX((SI_Long)4L)));
    pos = chestnut_modf_function(num,FIX((SI_Long)4L));
    gensymed_symbol = (SI_Long)255L;
    gensymed_symbol_1 =  - (IFIX(pos) << (SI_Long)1L);
    mask = IFIX(ash(FIX(gensymed_symbol),FIX(gensymed_symbol_1)));
    shift = (SI_Long)3L - IFIX(pos) << (SI_Long)1L;
    gensymed_symbol = IFIX(CHAR_CODE(CHAR(Kfep_kojin_bunpobits,
	    FIXNUM_SUB1(page)))) & mask;
    gensymed_symbol_1 =  - shift;
    bit2_1 = IFIX(ash(FIX(gensymed_symbol),FIX(gensymed_symbol_1)));
    if (bit2_1 == (SI_Long)0L)
	return VALUES_1(FIX((SI_Long)1L));
    else
	return VALUES_1(FIX(bit2_1));
}

static Object string_constant_3;   /* "                        " */

/* KFEP-KKA-GTNUM */
Object kfep_kka_gtnum(string_1,string_start_index,len)
    Object string_1, string_start_index, len;
{
    Object result_qm, c, i, ok, buf, a, b, strncmp_1;
    SI_Long n_1, start_a, start_b;

    x_note_fn_call(120,37);
    result_qm = Nil;
    c = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
    ok = FIX((SI_Long)0L);
    buf = obtain_simple_gensym_string(FIX((SI_Long)20L));
    copy_lisp_string_to_target(string_1,buf,string_start_index,
	    FIX((SI_Long)0L),len);
    copy_lisp_string_to_target(string_constant_3,buf,FIX((SI_Long)0L),len,
	    FIX((SI_Long)20L - IFIX(len)));
  next_loop:
    if ( !FIXNUM_LT(i,Kfep_tablemax))
	goto end_loop;
    a = buf;
    b = ISVREF(ISVREF(Kfep_m_table,IFIX(i)),(SI_Long)1L);
    n_1 = (SI_Long)20L;
    start_a = (SI_Long)0L;
    start_b = (SI_Long)0L;
    strncmp_1 = strncmp_function(a,b,FIX(n_1),FIX(start_a),FIX(start_b));
    c = IFIX(strncmp_1) == (SI_Long)0L ? FIX((SI_Long)61L) : 
	    IFIX(strncmp_1) > (SI_Long)0L ? FIX((SI_Long)62L) : 
	    FIX((SI_Long)60L);
    if (IFIX(c) == (SI_Long)60L || IFIX(c) == (SI_Long)61L) {
	ok = FIX((SI_Long)1L);
	goto end_1;
    }
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
  end_1:
    if (IFIX(ok) != (SI_Long)0L) {
	if (IFIX(c) == (SI_Long)61L)
	    result_qm = i;
	else
	    result_qm = FIXNUM_SUB1(i);
    }
    else {
	a = buf;
	b = Kfep_master_header_in_characters;
	n_1 = (SI_Long)20L;
	start_a = (SI_Long)0L;
	start_b = (SI_Long)16L;
	strncmp_1 = strncmp_function(a,b,FIX(n_1),FIX(start_a),FIX(start_b));
	c = IFIX(strncmp_1) == (SI_Long)0L ? FIX((SI_Long)61L) : 
		IFIX(strncmp_1) > (SI_Long)0L ? FIX((SI_Long)62L) : 
		FIX((SI_Long)60L);
	if (IFIX(c) != (SI_Long)62L)
	    result_qm = FIXNUM_SUB1(Kfep_tablemax);
	else
	    result_qm = FIX((SI_Long)-1L);
    }
    reclaim_gensym_string(buf);
    if (result_qm)
	return VALUES_1(result_qm);
    else
	return VALUES_1(FIX((SI_Long)0L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_ghyoki_idxbuf, Qkfep_ghyoki_idxbuf);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_ghyoki_hptr, Qkfep_ghyoki_hptr);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_ghyoki_savtblnum, Qkfep_ghyoki_savtblnum);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_ghyoki_idxbuf_cache_alist, Qkfep_ghyoki_idxbuf_cache_alist);

/* KFEP-KKA-GHYOKI */
Object kfep_kka_ghyoki(yomi,yomi_start_index_init,len_init)
    Object yomi, yomi_start_index_init, len_init;
{
    Object hoffset, tblnum, i, j, k, golen, locgonum, hlen, doonlen, idxptr;
    Object nbyte, offset, result_qm, result_set_qm, rhlen, entry, number;
    Object string_1, tail_qm, rest_of_alist, index_item, index_1;
    Object ab_loop_iter_flag_, cdr_new_value, cached_item_qm, entry_1;
    Object ab_loop_list_, temporary_buffer, incff_1_arg;
    SI_Long yomi_start_index, len, start_index, count_1, idxptr_new_value;

    x_note_fn_call(120,38);
    yomi_start_index = IFIX(yomi_start_index_init);
    len = IFIX(len_init);
    hoffset = FIX((SI_Long)0L);
    tblnum = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
    j = FIX((SI_Long)0L);
    k = FIX((SI_Long)0L);
    golen = FIX((SI_Long)0L);
    locgonum = FIX((SI_Long)0L);
    hlen = FIX((SI_Long)0L);
    doonlen = FIX((SI_Long)0L);
    idxptr = Nil;
    nbyte = FIX((SI_Long)0L);
    offset = FIX((SI_Long)0L);
    result_qm = Nil;
    result_set_qm = Nil;
    rhlen = FIX((SI_Long)0L);
    entry = FIX((SI_Long)0L);
    number = FIX((SI_Long)0L);
    if (len > (SI_Long)20L) {
	result_qm = Nil;
	result_set_qm = T;
    }
    else {
	tblnum = kfep_kka_gtnum(yomi,FIX(yomi_start_index),FIX(len));
	if (IFIX(tblnum) < (SI_Long)0L) {
	    result_qm = Nil;
	    result_set_qm = T;
	}
	else {
	    string_1 = ISVREF(ISVREF(Kfep_m_table,IFIX(tblnum)),(SI_Long)3L);
	    start_index = (SI_Long)0L;
	    nbyte = FIX(IFIX(CHAR_CODE(CHR(ICHAR(string_1,start_index)))) 
		    << (SI_Long)8L | IFIX(CHAR_CODE(CHR(ICHAR(string_1,
		    start_index + (SI_Long)1L)))));
	    offset = 
		    read_32_bit_big_endian_number_from_string(ISVREF(ISVREF(Kfep_m_table,
		    IFIX(tblnum)),(SI_Long)2L),FIX((SI_Long)0L));
	    if (!FIXNUM_EQ(tblnum,Kfep_ghyoki_savtblnum)) {
		tail_qm = Nil;
		rest_of_alist = Kfep_ghyoki_idxbuf_cache_alist;
		index_item = Nil;
		index_1 = Nil;
		count_1 = (SI_Long)1L;
		ab_loop_iter_flag_ = T;
	      next_loop:
		if ( !TRUEP(rest_of_alist))
		    goto end_loop;
		index_item = CAR(rest_of_alist);
		index_1 = CAR(index_item);
		if ( !TRUEP(ab_loop_iter_flag_))
		    count_1 = count_1 + (SI_Long)1L;
		if (FIXNUM_EQ(tblnum,index_1)) {
		    if (tail_qm) {
			cdr_new_value = CDR(rest_of_alist);
			M_CDR(tail_qm) = cdr_new_value;
			cdr_new_value = Kfep_ghyoki_idxbuf_cache_alist;
			M_CDR(rest_of_alist) = cdr_new_value;
			Kfep_ghyoki_idxbuf_cache_alist = rest_of_alist;
		    }
		    cached_item_qm = CDR(index_item);
		    goto end_1;
		}
		if (count_1 >= (SI_Long)25L) {
		    M_CDR(tail_qm) = Nil;
		    entry_1 = Nil;
		    ab_loop_list_ = rest_of_alist;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    entry_1 = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    reclaim_gensym_string(CDR(entry_1));
		    reclaim_gensym_cons_1(entry_1);
		    goto next_loop_1;
		  end_loop_1:;
		    reclaim_gensym_list_1(rest_of_alist);
		    cached_item_qm = Nil;
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		tail_qm = rest_of_alist;
		rest_of_alist = M_CDR(rest_of_alist);
		goto next_loop;
	      end_loop:
		cached_item_qm = Qnil;
	      end_1:;
		if (cached_item_qm) {
		    Kfep_ghyoki_idxbuf = cached_item_qm;
		    Kfep_ghyoki_savtblnum = tblnum;
		}
		else {
		    Kfep_ghyoki_idxbuf = obtain_simple_gensym_string(nbyte);
		    g2_stream_set_file_position(Kfep_index_file_stream,
			    FIX(IFIX(offset) + (SI_Long)9672L),
			    FIX((SI_Long)0L));
		    g2_stream_read_into_string(Kfep_index_file_stream,
			    Kfep_ghyoki_idxbuf,nbyte,FIX((SI_Long)0L));
		    Kfep_ghyoki_savtblnum = tblnum;
		    Kfep_ghyoki_idxbuf_cache_alist = 
			    gensym_cons_1(gensym_cons_1(tblnum,
			    Kfep_ghyoki_idxbuf),
			    Kfep_ghyoki_idxbuf_cache_alist);
		}
	    }
	    idxptr = FIX((SI_Long)0L);
	    i = FIX((SI_Long)0L);
	    locgonum = FIX((SI_Long)0L);
	  next_loop_2:
	    if ( !FIXNUM_LT(i,nbyte))
		goto end_loop_2;
	    hlen = CHAR_CODE(CHAR(Kfep_ghyoki_idxbuf,idxptr));
	    idxptr = FIXNUM_ADD1(idxptr);
	    if (IFIX(hlen) - (SI_Long)5L != len || 
		    IFIX(strncmp_function(yomi,Kfep_ghyoki_idxbuf,FIX(len),
		    FIX(yomi_start_index),idxptr)) != (SI_Long)0L) {
		locgonum = FIXNUM_ADD1(locgonum);
	      next_loop_3:
		if ( !(IFIX(hlen) > (SI_Long)1L))
		    goto end_loop_3;
		idxptr = FIXNUM_ADD1(idxptr);
		i = FIXNUM_ADD1(i);
		hlen = FIXNUM_SUB1(hlen);
		goto next_loop_3;
	      end_loop_3:
		goto end_continue;
	    }
	    number = FIX((SI_Long)256L * IFIX(tblnum) + IFIX(locgonum));
	    i = FIX((SI_Long)0L);
	  next_loop_4:
	    if ( !(IFIX(i) < IFIX(hlen) - (SI_Long)5L))
		goto end_loop_4;
	    idxptr = FIXNUM_ADD1(idxptr);
	    i = FIXNUM_ADD1(i);
	    goto next_loop_4;
	  end_loop_4:
	    hoffset = 
		    read_32_bit_big_endian_number_from_string(Kfep_ghyoki_idxbuf,
		    idxptr);
	    idxptr_new_value = IFIX(idxptr) + (SI_Long)4L;
	    idxptr = FIX(idxptr_new_value);
	    g2_stream_set_file_position(Kfep_main_file_stream,hoffset,
		    FIX((SI_Long)0L));
	    temporary_buffer = obtain_simple_gensym_string(FIX((SI_Long)2L));
	    g2_stream_read_into_string(Kfep_main_file_stream,
		    temporary_buffer,FIX((SI_Long)2L),FIX((SI_Long)0L));
	    doonlen = FIX(IFIX(CHAR_CODE(CHAR(temporary_buffer,
		    FIX((SI_Long)0L)))) << (SI_Long)8L | 
		    IFIX(CHAR_CODE(CHR(ICHAR(temporary_buffer,(SI_Long)0L 
		    + (SI_Long)1L)))));
	    reclaim_gensym_string(temporary_buffer);
	    if (Kfep_ghyoki_hptr)
		reclaim_gensym_string(Kfep_ghyoki_hptr);
	    Kfep_ghyoki_hptr = obtain_simple_gensym_string(doonlen);
	    g2_stream_read_into_string(Kfep_main_file_stream,
		    Kfep_ghyoki_hptr,doonlen,FIX((SI_Long)0L));
	    rhlen = doonlen;
	    j = FIX((SI_Long)0L);
	    k = FIX((SI_Long)0L);
	  next_loop_5:
	    if ( !FIXNUM_LT(j,doonlen))
		goto end_loop_5;
	    golen = CHAR_CODE(CHAR(Kfep_ghyoki_hptr,j));
	    incff_1_arg = FIXNUM_ADD1(golen);
	    j = FIXNUM_ADD(j,incff_1_arg);
	    j = FIXNUM_ADD1(j);
	    k = FIXNUM_ADD1(k);
	    goto next_loop_5;
	  end_loop_5:
	    entry = k;
	    result_qm = Kfep_ghyoki_hptr;
	    result_set_qm = T;
	    goto end_2;
	  end_continue:
	    i = FIXNUM_ADD1(i);
	    goto next_loop_2;
	  end_loop_2:
	  end_2:
	    if ( !TRUEP(result_set_qm)) {
		number = FIX((SI_Long)-1L);
		result_qm = Nil;
		result_set_qm = T;
	    }
	}
    }
    return VALUES_4(result_qm,rhlen,entry,number);
}

/* KFEP-KKA-GTANGO */
Object kfep_kka_gtango(array_string,arraylen_init,pos_init,obuf_string)
    Object array_string, arraylen_init, pos_init, obuf_string;
{
    SI_Long arraylen, pos, olen, count_1, golen, index_1, ab_loop_bind_;
    SI_Long incff_1_arg;
    char array_string_is_simple_qm;

    x_note_fn_call(120,39);
    arraylen = IFIX(arraylen_init);
    pos = IFIX(pos_init);
    olen = (SI_Long)0L;
    count_1 = (SI_Long)0L;
    golen = (SI_Long)0L;
    array_string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(array_string);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = arraylen;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    golen = IFIX(CHAR_CODE(array_string_is_simple_qm ? 
	    CHR(ISCHAR(array_string,index_1)) : CHR(ICHAR(array_string,
	    index_1))));
    if (pos == count_1) {
	copy_lisp_string_to_target(array_string,obuf_string,FIX(index_1 + 
		(SI_Long)1L),FIX((SI_Long)0L),FIX(golen));
	olen = golen;
	goto end_1;
    }
    else {
	incff_1_arg = golen + (SI_Long)1L;
	index_1 = index_1 + incff_1_arg;
    }
    count_1 = count_1 + (SI_Long)1L;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
  end_1:;
    if (pos > count_1)
	return VALUES_2(FIX((SI_Long)-1L),FIX(olen));
    else
	return VALUES_2(FIX((SI_Long)0L),FIX(olen));
}

/* KFEP-KKA-ISHOUKI */
Object kfep_kka_ishouki(yomi,yomi_start_index,chkcnt_init,len_init)
    Object yomi, yomi_start_index, chkcnt_init, len_init;
{
    Object result_qm, length_index, index_1, go, ok, ghyoki_result;
    Object gensymed_symbol, temp, gensymed_symbol_1;
    SI_Long chkcnt, len, anslen, length_index_new_value;
    Object result;

    x_note_fn_call(120,40);
    chkcnt = IFIX(chkcnt_init);
    len = IFIX(len_init);
    result_qm = Nil;
    anslen = (SI_Long)0L;
    length_index = FIX(len);
    index_1 = FIX((SI_Long)0L);
    go = FIX((SI_Long)0L);
    ok = FIX((SI_Long)0L);
    ghyoki_result = Nil;
  next_loop:
    if ( !(IFIX(index_1) < chkcnt))
	goto end_loop;
    result = kfep_kka_ghyoki(yomi,FIXNUM_ADD(yomi_start_index,index_1),
	    length_index);
    MVS_4(result,gensymed_symbol,temp,temp,gensymed_symbol_1);
    go = gensymed_symbol_1;
    ghyoki_result = gensymed_symbol;
    if (ghyoki_result) {
	ok = FIXNUM_ADD1(ok);
	goto end_1;
    }
    if (IFIX(length_index) < (SI_Long)0L) {
	index_1 = FIXNUM_ADD1(index_1);
	length_index = FIX(len);
    }
    length_index_new_value = IFIX(length_index) - (SI_Long)2L;
    length_index = FIX(length_index_new_value);
    goto next_loop;
  end_loop:
  end_1:
    anslen = IFIX(length_index);
    if (IFIX(ok) == (SI_Long)0L)
	result_qm = FIX((SI_Long)-1L);
    else if (IFIX(kfep_find_used(go)) == (SI_Long)3L)
	result_qm = FIX((SI_Long)1L);
    else
	result_qm = FIX((SI_Long)0L);
    return VALUES_2(result_qm,FIX(anslen));
}

Object Maximum_kojin_entry_subvector_length = UNBOUND;

Object Most_positive_fixnum_ash_minus_24 = UNBOUND;

/* MAP-TO-KOJIN-ENTRY */
Object map_to_kojin_entry(kfep_kojin_index,indexno)
    Object kfep_kojin_index, indexno;
{
    Object subvector_index, byte_index, byte_vector, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(120,41);
    PUSH_SPECIAL_WITH_SYMBOL(Kfep_kojin_index,Qkfep_kojin_index,kfep_kojin_index,
	    0);
      result = chestnut_floorf_function(indexno,
	      Maximum_kojin_entry_subvector_length);
      MVS_2(result,subvector_index,byte_index);
      byte_vector = ISVREF(Kfep_kojin_index,IFIX(subvector_index));
      temp = FIX(UBYTE_8_ISAREF_1(byte_vector,IFIX(byte_index) + 
	      (SI_Long)3L) + (UBYTE_8_ISAREF_1(byte_vector,
	      IFIX(byte_index) + (SI_Long)2L) << (SI_Long)8L) + 
	      (UBYTE_8_ISAREF_1(byte_vector,IFIX(FIXNUM_ADD1(byte_index))) 
	      << (SI_Long)16L) + ((UBYTE_8_ISAREF_1(byte_vector,
	      IFIX(byte_index) + (SI_Long)0L) & 
	      IFIX(Most_positive_fixnum_ash_minus_24)) << (SI_Long)24L));
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* MAKE-KOJIN-INDEX */
Object make_kojin_index()
{
    Object total_byte_count, vector_length, vector_1, svref_new_value;
    SI_Long i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(120,42);
    total_byte_count = ISVREF(Kfep_kojin_header,(SI_Long)3L);
    vector_length = ceiling(total_byte_count,
	    Maximum_kojin_entry_subvector_length);
    if (PUSH_AREA(Dynamic_area,0))
	vector_1 = make_array(1,vector_length);
    POP_AREA(0);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(vector_length);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = allocate_byte_vector(i == 
	    IFIX(FIXNUM_SUB1(vector_length)) ? 
	    chestnut_modf_function(total_byte_count,
	    Maximum_kojin_entry_subvector_length) : 
	    Maximum_kojin_entry_subvector_length);
    ISVREF(vector_1,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(vector_1);
}

/* READ-KOJIN-STREAM-INTO-BYTE-VECTOR */
Object read_kojin_stream_into_byte_vector(stream,byte_vector,
	    number_of_characters,start_index)
    Object stream, byte_vector, number_of_characters, start_index;
{
    x_note_fn_call(120,43);
    g2_stream_read_into_byte_vector(stream,byte_vector,
	    number_of_characters,start_index);
    return VALUES_1(Nil);
}

/* KFEP-READ-KOJIN-INDEX */
Object kfep_read_kojin_index(stream)
    Object stream;
{
    Object total_byte_count, vector_length, vector_1, byte_vector;
    Object number_of_characters;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(120,44);
    total_byte_count = ISVREF(Kfep_kojin_header,(SI_Long)3L);
    vector_length = ceiling(total_byte_count,
	    Maximum_kojin_entry_subvector_length);
    vector_1 = Kfep_kojin_index;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(vector_length);
    byte_vector = Nil;
    number_of_characters = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    byte_vector = ISVREF(vector_1,i);
    number_of_characters = i == IFIX(FIXNUM_SUB1(vector_length)) ? 
	    chestnut_modf_function(total_byte_count,
	    Maximum_kojin_entry_subvector_length) : 
	    Maximum_kojin_entry_subvector_length;
    read_kojin_stream_into_byte_vector(stream,byte_vector,
	    number_of_characters,FIX((SI_Long)0L));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* KFEP-KKA-KOFIND */
Object kfep_kka_kofind(indexno,byteno)
    Object indexno, byteno;
{
    Object result_qm, kojin_entry, hptr;

    x_note_fn_call(120,45);
    result_qm = Nil;
    kojin_entry = map_to_kojin_entry(Kfep_kojin_index,indexno);
    if (FIXNUM_EQ(kojin_entry,Most_positive_fixnum))
	result_qm = Nil;
    else {
	hptr = obtain_simple_gensym_string(byteno);
	g2_stream_set_file_position(Kfep_kojin_file_stream,
		FIX(IFIX(FIXNUM_ADD(kojin_entry,FIX((SI_Long)80L))) + 
		(IFIX(ISVREF(Kfep_kojin_header,(SI_Long)2L)) << 
		(SI_Long)1L) + IFIX(ISVREF(Kfep_kojin_header,
		(SI_Long)3L))),FIX((SI_Long)0L));
	g2_stream_read_into_string(Kfep_kojin_file_stream,hptr,byteno,
		FIX((SI_Long)0L));
	result_qm = hptr;
    }
    return VALUES_1(result_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_hensaisyo_getpos, Qkfep_hensaisyo_getpos);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_hensaisyo_tno, Qkfep_hensaisyo_tno);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_hensaisyo_gonum, Qkfep_hensaisyo_gonum);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_hensaisyo_saventry, Qkfep_hensaisyo_saventry);

/* KFEP-KKA-HENSAISYO */
Object kfep_kka_hensaisyo(sp,inbuf,inlen)
    Object sp, inbuf, inlen;
{
    Object result_qm, ii, battable_entry, hyoki, kohyoki, bunpo, temp, temp_1;
    Object temp_2, cur_0, battable_tno, old_hyoki, batchyomi_substring, ho;
    SI_Long hyolen, hukalen, entry, loclen, scanpos, ava, dum, index_1;
    SI_Long ab_loop_bind_, incff_1_arg, svref_new_value, temp_3;
    Object result;

    x_note_fn_call(120,46);
    result_qm = Nil;
    ii = FIX((SI_Long)0L);
    hyolen = (SI_Long)0L;
    hukalen = (SI_Long)0L;
    entry = (SI_Long)0L;
    loclen = (SI_Long)0L;
    scanpos = (SI_Long)0L;
    ava = (SI_Long)0L;
    dum = (SI_Long)0L;
    battable_entry = Nil;
    hyoki = Nil;
    kohyoki = Nil;
    bunpo = FIX((SI_Long)0L);
    if (IFIX(inlen) <= (SI_Long)0L)
	result_qm = FIX((SI_Long)-1L);
    else if (IFIX(inlen) > (SI_Long)80L)
	result_qm = FIX((SI_Long)1L);
    else {
	Kfep_batchyomilen = inlen;
	copy_lisp_string_to_target(inbuf,Kfep_batchyomi,FIX((SI_Long)0L),
		FIX((SI_Long)0L),inlen);
	temp = Kfep_batchyomi;
	temp_1 = CHR('\000');
	SET_CHAR(temp,inlen,temp_1);
	Kfep_hensaisyo_gonum = FIX((SI_Long)0L);
	Kfep_hensaisyo_getpos = FIX((SI_Long)0L);
	Kfep_hensaisyo_saventry = FIX((SI_Long)0L);
	scanpos = (SI_Long)0L;
	Kfep_hensaisyo_tno = FIX((SI_Long)0L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)15L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	battable_entry = ISVREF(Kfep_battable,index_1);
	ISVREF(battable_entry,(SI_Long)2L) = FIX((SI_Long)0L);
	ISVREF(battable_entry,(SI_Long)4L) = FIX((SI_Long)0L);
	ISVREF(battable_entry,(SI_Long)1L) = FIX((SI_Long)0L);
	ISVREF(battable_entry,(SI_Long)5L) = FIX((SI_Long)0L);
	ISVREF(battable_entry,(SI_Long)7L) = FIX((SI_Long)0L);
	ISVREF(battable_entry,(SI_Long)8L) = FIX((SI_Long)0L);
	temp = ISVREF(battable_entry,(SI_Long)3L);
	temp_1 = CHR('\000');
	SET_CHAR(temp,FIX((SI_Long)0L),temp_1);
	ISVREF(battable_entry,(SI_Long)10L) = FIX((SI_Long)3L);
	ISVREF(battable_entry,(SI_Long)15L) = FIX((SI_Long)134217727L);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	hyolen = (SI_Long)0L;
	hukalen = (SI_Long)0L;
	entry = (SI_Long)0L;
	ava = (SI_Long)0L;
	loclen = IFIX(Kfep_batchyomilen);
      next_loop_1:
	if ( !(scanpos <= IFIX(Kfep_batchyomilen)))
	    goto end_loop_1;
	temp_1 = FIX((SI_Long)15L);
	if (NUM_GE(Kfep_hensaisyo_tno,temp_1)) {
	    result_qm = FIX((SI_Long)-1L);
	    goto end_1;
	}
	result = kfep_kka_ghyoki(Kfep_batchyomi,FIX(scanpos),FIX(loclen));
	MVS_4(result,hyoki,temp_1,temp_2,Kfep_hensaisyo_gonum);
	entry = IFIX(temp_2);
	hyolen = IFIX(temp_1);
	if ( !TRUEP(hyoki)) {
	    loclen = loclen - (SI_Long)2L;
	    if (loclen >= (SI_Long)0L)
		goto end_continue;
	    if (loclen < (SI_Long)0L) {
		scanpos = scanpos + (SI_Long)2L;
		ava = ava + (SI_Long)2L;
		loclen = IFIX(Kfep_batchyomilen) - scanpos;
	    }
	}
	else {
	    if (IFIX(kfep_find_used(Kfep_hensaisyo_gonum)) == (SI_Long)3L) {
		loclen = loclen - (SI_Long)-2L;
		goto end_continue;
	    }
	    if (ava > (SI_Long)0L) {
		if (IFIX(Kfep_hensaisyo_tno) > (SI_Long)0L) {
		    temp = ISVREF(Kfep_battable,
			    IFIX(FIXNUM_SUB1(Kfep_hensaisyo_tno)));
		    incff_1_arg = ava;
		    svref_new_value = IFIX(ISVREF(temp,(SI_Long)5L)) + 
			    incff_1_arg;
		    ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value);
		}
		else {
		    cur_0 = ISVREF(Kfep_battable,(SI_Long)0L);
		    if (IFIX(ISVREF(cur_0,(SI_Long)4L)) > (SI_Long)0L) {
			incff_1_arg = ava;
			svref_new_value = IFIX(ISVREF(cur_0,(SI_Long)5L)) 
				+ incff_1_arg;
			ISVREF(cur_0,(SI_Long)5L) = FIX(svref_new_value);
		    }
		    else
			ISVREF(cur_0,(SI_Long)5L) = FIX(ava);
		    hyolen = (SI_Long)0L;
		    ava = (SI_Long)0L;
		    temp = FIXNUM_ADD1(Kfep_hensaisyo_tno);
		    Kfep_hensaisyo_tno = temp;
		    goto end_continue;
		}
		ava = (SI_Long)0L;
	    }
	    if (!(IFIX(Kfep_hensaisyo_tno) == (SI_Long)0L && hyolen == 
		    (SI_Long)0L)) {
		battable_tno = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
		old_hyoki = ISVREF(battable_tno,(SI_Long)3L);
		reclaim_gensym_string(old_hyoki);
		temp = copy_managed_lisp_string(hyoki,FIX((SI_Long)0L),
			FIX(hyolen));
		SVREF(battable_tno,FIX((SI_Long)3L)) = temp;
		ISVREF(battable_tno,(SI_Long)4L) = FIX(hyolen);
		ISVREF(battable_tno,(SI_Long)2L) = FIX(loclen);
	    }
	    battable_tno = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    if (IFIX(Kfep_hensaisyo_tno) == (SI_Long)0L)
		ISVREF(battable_tno,(SI_Long)1L) = FIX((SI_Long)0L);
	    else
		ISVREF(battable_tno,(SI_Long)1L) = FIX(scanpos);
	    temp = Kfep_hensaisyo_gonum;
	    SVREF(battable_tno,FIX((SI_Long)9L)) = temp;
	    temp = kfep_find_used(Kfep_hensaisyo_gonum);
	    SVREF(battable_tno,FIX((SI_Long)10L)) = temp;
	    temp = kfep_find_bunpo(Kfep_hensaisyo_gonum);
	    SVREF(battable_tno,FIX((SI_Long)11L)) = temp;
	    ISVREF(battable_tno,(SI_Long)7L) = FIX(entry);
	    ISVREF(battable_tno,(SI_Long)8L) = FIX((SI_Long)0L);
	    incff_1_arg = loclen;
	    scanpos = scanpos + incff_1_arg;
	    loclen = IFIX(Kfep_batchyomilen) - scanpos;
	    if (scanpos >= IFIX(Kfep_batchyomilen))
		goto end_break;
	    hukalen = loclen;
	    battable_tno = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    batchyomi_substring = copy_managed_lisp_string(Kfep_batchyomi,
		    FIX(scanpos),FIX((SI_Long)80L - scanpos));
	    result = kfep_chkbunpo(ISVREF(battable_tno,(SI_Long)3L),
		    ISVREF(battable_tno,(SI_Long)4L),batchyomi_substring,
		    FIX(hukalen));
	    MVS_2(result,temp_1,bunpo);
	    dum = IFIX(temp_1);
	    reclaim_gensym_string(batchyomi_substring);
	    hukalen = dum;
	    SVREF(battable_tno,FIX((SI_Long)15L)) = bunpo;
	    if ( !(hukalen > (SI_Long)0L && IFIX(sp) != scanpos))
		goto skip;
	    if (IFIX(ISVREF(ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno)),
		    (SI_Long)11L)) == (SI_Long)0L)
		goto skip;
	    ho = Nil;
	    ho = kfep_chkcattr(Kfep_batchyomi,FIX(scanpos + hukalen));
	    if (IFIX(ho) == (SI_Long)1L || IFIX(ho) == (SI_Long)2L)
		goto skip;
	    temp = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    ISVREF(temp,(SI_Long)5L) = FIX(hukalen);
	    incff_1_arg = hukalen;
	    scanpos = scanpos + incff_1_arg;
	    loclen = IFIX(Kfep_batchyomilen) - scanpos;
	    if (scanpos >= IFIX(Kfep_batchyomilen))
		goto end_break;
	    goto finish;
	  skip:
	    temp = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    ISVREF(temp,(SI_Long)5L) = FIX((SI_Long)0L);
	  finish:
	    battable_tno = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    kohyoki = kfep_kka_kofind(ISVREF(battable_tno,(SI_Long)9L),
		    ISVREF(battable_tno,(SI_Long)4L));
	    if (kohyoki) {
		copy_lisp_string_to_target(kohyoki,ISVREF(battable_tno,
			(SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)0L),
			ISVREF(battable_tno,(SI_Long)4L));
		reclaim_gensym_string(kohyoki);
	    }
	    temp = FIXNUM_ADD1(Kfep_hensaisyo_tno);
	    Kfep_hensaisyo_tno = temp;
	}
      end_continue:
	goto next_loop_1;
      end_loop_1:
      end_1:
      end_break:
	if ( !TRUEP(result_qm)) {
	    if (ava > (SI_Long)0L) {
		if (IFIX(Kfep_hensaisyo_tno) <= (SI_Long)0L) {
		    battable_entry = ISVREF(Kfep_battable,(SI_Long)0L);
		    ISVREF(battable_entry,(SI_Long)2L) = FIX((SI_Long)0L);
		    ISVREF(battable_entry,(SI_Long)1L) = FIX((SI_Long)0L);
		    incff_1_arg = ava;
		    svref_new_value = IFIX(ISVREF(battable_entry,
			    (SI_Long)5L)) + incff_1_arg;
		    ISVREF(battable_entry,(SI_Long)5L) = FIX(svref_new_value);
		}
		else {
		    battable_entry = ISVREF(Kfep_battable,
			    IFIX(FIXNUM_SUB1(Kfep_hensaisyo_tno)));
		    incff_1_arg = ava;
		    svref_new_value = IFIX(ISVREF(battable_entry,
			    (SI_Long)5L)) + incff_1_arg;
		    ISVREF(battable_entry,(SI_Long)5L) = FIX(svref_new_value);
		    temp = FIXNUM_SUB1(Kfep_hensaisyo_tno);
		    Kfep_hensaisyo_tno = temp;
		}
	    }
	    battable_entry = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    ava = IFIX(FIXNUM_ADD(FIXNUM_ADD(ISVREF(battable_entry,
		    (SI_Long)1L),ISVREF(battable_entry,(SI_Long)2L)),
		    ISVREF(battable_entry,(SI_Long)5L)));
	    if (ava < IFIX(Kfep_batchyomilen)) {
		incff_1_arg = IFIX(Kfep_batchyomilen) - ava;
		svref_new_value = IFIX(ISVREF(battable_entry,(SI_Long)5L)) 
			+ incff_1_arg;
		ISVREF(battable_entry,(SI_Long)5L) = FIX(svref_new_value);
	    }
	    if (IFIX(Kfep_hensaisyo_tno) > (SI_Long)0L && 
		    IFIX(ISVREF(battable_entry,(SI_Long)2L)) == 
		    (SI_Long)0L && IFIX(ISVREF(battable_entry,
		    (SI_Long)5L)) == (SI_Long)0L) {
		temp = FIXNUM_SUB1(Kfep_hensaisyo_tno);
		Kfep_hensaisyo_tno = temp;
	    }
	    if (scanpos > IFIX(Kfep_batchyomilen)) {
		battable_entry = ISVREF(Kfep_battable,
			IFIX(Kfep_hensaisyo_tno));
		if (IFIX(ISVREF(battable_entry,(SI_Long)5L)) > (SI_Long)0L) {
		    ii = ISVREF(battable_entry,(SI_Long)5L);
		    temp_3 = IFIX(ii) - (scanpos - IFIX(Kfep_batchyomilen));
		    svref_new_value = MAX(temp_3,(SI_Long)0L);
		    ISVREF(battable_entry,(SI_Long)5L) = FIX(svref_new_value);
		}
		else {
		    ii = ISVREF(battable_entry,(SI_Long)2L);
		    temp_3 = IFIX(ii) - (scanpos - IFIX(Kfep_batchyomilen));
		    svref_new_value = MAX(temp_3,(SI_Long)0L);
		    ISVREF(battable_entry,(SI_Long)2L) = FIX(svref_new_value);
		}
	    }
	    battable_entry = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
	    if (IFIX(ISVREF(battable_entry,(SI_Long)10L)) != (SI_Long)3L 
		    && IFIX(ISVREF(battable_entry,(SI_Long)4L)) > 
			(SI_Long)0L) {
		battable_tno = ISVREF(Kfep_battable,IFIX(Kfep_hensaisyo_tno));
		kohyoki = kfep_kka_kofind(ISVREF(battable_tno,(SI_Long)9L),
			ISVREF(battable_tno,(SI_Long)4L));
		if (kohyoki) {
		    copy_lisp_string_to_target(kohyoki,ISVREF(battable_tno,
			    (SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)0L),
			    ISVREF(battable_tno,(SI_Long)4L));
		    reclaim_gensym_string(kohyoki);
		}
	    }
	    Kfep_kka_usetblnum = FIXNUM_ADD1(Kfep_hensaisyo_tno);
	    if (FIXNUM_NE(Kfep_batchyomilen,inlen) ||  !TRUEP(string_eq(6,
		    Kfep_batchyomi,inbuf,Kend1,Kfep_batchyomilen,Kend2,
		    Kfep_batchyomilen))) {
		Kfep_kka_usetblnum = FIX((SI_Long)0L);
		Kfep_hensaisyo_gonum = FIX((SI_Long)0L);
		Kfep_hensaisyo_getpos = FIX((SI_Long)0L);
		Kfep_hensaisyo_saventry = FIX((SI_Long)0L);
		scanpos = (SI_Long)0L;
		Kfep_hensaisyo_tno = FIX((SI_Long)0L);
		result_qm = FIX((SI_Long)-1L);
	    }
	    else {
		index_1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(Kfep_hensaisyo_tno);
	      next_loop_2:
		if (index_1 > ab_loop_bind_)
		    goto end_loop_2;
		battable_entry = ISVREF(Kfep_battable,index_1);
		temp = FIXNUM_ADD(ISVREF(battable_entry,(SI_Long)2L),
			ISVREF(battable_entry,(SI_Long)5L));
		SVREF(battable_entry,FIX((SI_Long)6L)) = temp;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
		result_qm = FIX((SI_Long)0L);
	    }
	}
    }
    if (result_qm)
	return VALUES_1(result_qm);
    else
	return VALUES_1(FIX((SI_Long)0L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_kka_p_batkanakan_position, Qkfep_kka_p_batkanakan_position);

/* KFEP-KKA-P-BATKANAKAN */
Object kfep_kka_p_batkanakan(switch_1,inbuf,inlen,outbuf)
    Object switch_1, inbuf, inlen, outbuf;
{
    Object first_battable_entry, temp, temp_1, fill_index, increment_index;
    Object outlen, number_of_candidates, gensymed_symbol, gensymed_symbol_1;
    Object incff_1_arg;
    Object result;

    x_note_fn_call(120,47);
    first_battable_entry = ISVREF(Kfep_battable,(SI_Long)0L);
    if ( !(FIXNUMP(switch_1) && FIXNUM_LE(FIX((SI_Long)-128L),switch_1) && 
	    FIXNUM_LE(switch_1,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(switch_1)) {
	  case 0:
	    temp_1 = FIXNUM_ADD1(Kfep_kka_p_batkanakan_position);
	    Kfep_kka_p_batkanakan_position = temp_1;
	    temp =  !FIXNUM_GT(Kfep_kka_p_batkanakan_position,
		    ISVREF(first_battable_entry,(SI_Long)7L)) ? T : Nil;
	    break;
	  case 1:
	    if (IFIX(kfep_kka_hensaisyo(FIX((SI_Long)0L),inbuf,inlen)) < 
		    (SI_Long)0L)
		temp = Nil;
	    else {
		Kfep_kka_p_batkanakan_position = FIX((SI_Long)0L);
		temp = Kfep_kka_p_batkanakan_position;
	    }
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    if ( !(temp ?  !(IFIX(Kfep_kka_usetblnum) == (SI_Long)0L) : TRUEP(Nil)))
	return VALUES_3(FIX((SI_Long)-1L),FIX((SI_Long)0L),FIX((SI_Long)0L));
    else {
	fill_index = Nil;
	increment_index = Nil;
	outlen = Nil;
	number_of_candidates = Nil;
	result = kfep_kka_gtango(ISVREF(first_battable_entry,(SI_Long)3L),
		ISVREF(first_battable_entry,(SI_Long)4L),
		Kfep_kka_p_batkanakan_position,outbuf);
	MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	fill_index = gensymed_symbol_1;
	increment_index = FIXNUM_MINUS(Kfep_batchyomilen,
		ISVREF(first_battable_entry,(SI_Long)2L));
	if (IFIX(increment_index) > (SI_Long)0L) {
	    temp = CHR('\000');
	    SET_CHAR(outbuf,fill_index,temp);
	    strcat_1(outbuf,Kfep_batchyomi,FIX((SI_Long)0L),
		    ISVREF(first_battable_entry,(SI_Long)2L));
	    incff_1_arg = increment_index;
	    fill_index = FIXNUM_ADD(fill_index,incff_1_arg);
	}
	outlen = fill_index;
	ISVREF(first_battable_entry,(SI_Long)10L) = FIX((SI_Long)2L);
	temp_1 = Kfep_kka_p_batkanakan_position;
	SVREF(first_battable_entry,FIX((SI_Long)8L)) = temp_1;
	number_of_candidates = 
		FIXNUM_SUB1(FIXNUM_MINUS(ISVREF(first_battable_entry,
		(SI_Long)7L),Kfep_kka_p_batkanakan_position));
	temp = ISVREF(first_battable_entry,(SI_Long)2L);
	return VALUES_3(temp,outlen,number_of_candidates);
    }
}

/* KFEP-KKA-P-UPDATE-KOJIN */
Object kfep_kka_p_update_kojin(candidate_index)
    Object candidate_index;
{
    x_note_fn_call(120,48);
    return VALUES_1(candidate_index);
}

/* KFEP-KKA-KODONE */
Object kfep_kka_kodone()
{
    x_note_fn_call(120,49);
    return VALUES_1(Nil);
}

/* KFEP-KKA-MADONE */
Object kfep_kka_madone()
{
    x_note_fn_call(120,50);
    return VALUES_1(Nil);
}

void kfep1_INIT()
{
    Object get_new_value, temp, reclaim_structure_for_kfep_master_1;
    Object reclaim_structure_for_kfep_batch_1;
    Object Qkfep1, AB_package, Qmost_positive_fixnum_ash_minus_24;
    Object Qmaximum_kojin_entry_subvector_length, string_constant_173;
    Object string_constant_172, string_constant_171, string_constant_170;
    Object string_constant_169, string_constant_168, string_constant_167;
    Object string_constant_166, Qkfep_sahen_array, string_constant_165;
    Object string_constant_164, string_constant_163, string_constant_162;
    Object string_constant_161, string_constant_160, string_constant_159;
    Object string_constant_158, string_constant_157, string_constant_156;
    Object string_constant_155, string_constant_154, string_constant_153;
    Object Qkfep_taigen_array, string_constant_152, string_constant_151;
    Object string_constant_150, string_constant_149, string_constant_148;
    Object string_constant_147, string_constant_146, string_constant_145;
    Object string_constant_144, string_constant_143, string_constant_142;
    Object string_constant_141, string_constant_140, string_constant_139;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, Qkfep_keiyo_array;
    Object string_constant_127, string_constant_126, string_constant_125;
    Object string_constant_124, string_constant_123, string_constant_122;
    Object string_constant_121, string_constant_120, string_constant_119;
    Object string_constant_118, string_constant_117, string_constant_116;
    Object Qkfep_jyosi_array, string_constant_115, string_constant_114;
    Object string_constant_113, string_constant_112, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object Qkfep_jyodou_array, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object Qkfep_gobisetu2, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, Qkfep_gobisetu1, Qkfep_batch;
    Object Qreclaim_structure, Qoutstanding_kfep_batch_count;
    Object Qkfep_batch_structure_memory_usage, Qutilities2, string_constant_12;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_11, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qkfep_master;
    Object Qoutstanding_kfep_master_count, Qkfep_master_structure_memory_usage;
    Object string_constant_10, string_constant_9, string_constant_8;
    Object Qkfep_kk_index, string_constant_7, Qkfep_jy_index;
    Object string_constant_6, Qkfep_jd_index, string_constant_5;
    Object Qkfep_sa_index, string_constant_4, Qkfep_ta_index;
    Object Kno_initial_value, list_constant_2, Kfuncall, list_constant_1;
    Object list_constant, Qoptional_modules, Qab, Qkfep;

    x_note_fn_call(120,51);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qkfep = STATIC_SYMBOL("KFEP",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qoptional_modules = STATIC_SYMBOL("OPTIONAL-MODULES",AB_package);
    get_new_value = adjoin(2,Qkfep,get(Qab,Qoptional_modules,Nil));
    set_get(Qab,Qoptional_modules,get_new_value);
    Qkfep_master_header = STATIC_SYMBOL("KFEP-MASTER-HEADER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_master_header,Kfep_master_header);
    Qkfep1 = STATIC_SYMBOL("KFEP1",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_array,
	    FIX((SI_Long)13L));
    record_system_variable(Qkfep_master_header,Qkfep1,list_constant,Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_master_header_in_characters = 
	    STATIC_SYMBOL("KFEP-MASTER-HEADER-IN-CHARACTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_master_header_in_characters,
	    Kfep_master_header_in_characters);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_string,
	    FIX((SI_Long)52L));
    record_system_variable(Qkfep_master_header_in_characters,Qkfep1,
	    list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qkfep_kojin_header = STATIC_SYMBOL("KFEP-KOJIN-HEADER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_header,Kfep_kojin_header);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_array,
	    FIX((SI_Long)20L));
    record_system_variable(Qkfep_kojin_header,Qkfep1,list_constant_2,Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_tablemax = STATIC_SYMBOL("KFEP-TABLEMAX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_tablemax,Kfep_tablemax);
    record_system_variable(Qkfep_tablemax,Qkfep1,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_m_table = STATIC_SYMBOL("KFEP-M-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_m_table,Kfep_m_table);
    record_system_variable(Qkfep_m_table,Qkfep1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qkfep_index_file_stream = STATIC_SYMBOL("KFEP-INDEX-FILE-STREAM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_index_file_stream,Kfep_index_file_stream);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    record_system_variable(Qkfep_index_file_stream,Qkfep1,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qkfep_main_file_stream = STATIC_SYMBOL("KFEP-MAIN-FILE-STREAM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_main_file_stream,Kfep_main_file_stream);
    record_system_variable(Qkfep_main_file_stream,Qkfep1,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_kojin_file_stream = STATIC_SYMBOL("KFEP-KOJIN-FILE-STREAM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_file_stream,Kfep_kojin_file_stream);
    record_system_variable(Qkfep_kojin_file_stream,Qkfep1,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qkfep_kojin_usedbits = STATIC_SYMBOL("KFEP-KOJIN-USEDBITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_usedbits,Kfep_kojin_usedbits);
    record_system_variable(Qkfep_kojin_usedbits,Qkfep1,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_kojin_bunpobits = STATIC_SYMBOL("KFEP-KOJIN-BUNPOBITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_bunpobits,Kfep_kojin_bunpobits);
    record_system_variable(Qkfep_kojin_bunpobits,Qkfep1,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_kojin_index = STATIC_SYMBOL("KFEP-KOJIN-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_index,Kfep_kojin_index);
    record_system_variable(Qkfep_kojin_index,Qkfep1,Kno_initial_value,Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_kojin_hyolen = STATIC_SYMBOL("KFEP-KOJIN-HYOLEN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kojin_hyolen,Kfep_kojin_hyolen);
    record_system_variable(Qkfep_kojin_hyolen,Qkfep1,Kno_initial_value,
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_batchyomi = STATIC_SYMBOL("KFEP-BATCHYOMI",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_batchyomi,Kfep_batchyomi);
    record_system_variable(Qkfep_batchyomi,Qkfep1,Kno_initial_value,Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_battable = STATIC_SYMBOL("KFEP-BATTABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_battable,Kfep_battable);
    record_system_variable(Qkfep_battable,Qkfep1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qkfep_batchyomilen = STATIC_SYMBOL("KFEP-BATCHYOMILEN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_batchyomilen,Kfep_batchyomilen);
    record_system_variable(Qkfep_batchyomilen,Qkfep1,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qkfep_kka_usetblnum = STATIC_SYMBOL("KFEP-KKA-USETBLNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kka_usetblnum,Kfep_kka_usetblnum);
    record_system_variable(Qkfep_kka_usetblnum,Qkfep1,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_ta_index = STATIC_SYMBOL("KFEP-TA-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_ta_index,Kfep_ta_index);
    string_constant_4 = STATIC_STRING("4o4nskk4nqlo4nop3Iy4nm3Jy3Xy");
    SET_SYMBOL_VALUE(Qkfep_ta_index,
	    regenerate_optimized_constant(string_constant_4));
    Qkfep_sa_index = STATIC_SYMBOL("KFEP-SA-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_sa_index,Kfep_sa_index);
    string_constant_5 = STATIC_STRING("4o4nskn4nqos4notx4nmyy");
    SET_SYMBOL_VALUE(Qkfep_sa_index,
	    regenerate_optimized_constant(string_constant_5));
    Qkfep_jd_index = STATIC_SYMBOL("KFEP-JD-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_jd_index,Kfep_jd_index);
    string_constant_6 = 
	    STATIC_STRING("4p4nuk3Ry4ns3Sy3-Ay4nq3-By3*=y4no3*0y3*Ny4nm3*Oy3*Sy");
    SET_SYMBOL_VALUE(Qkfep_jd_index,
	    regenerate_optimized_constant(string_constant_6));
    Qkfep_jy_index = STATIC_SYMBOL("KFEP-JY-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_jy_index,Kfep_jy_index);
    string_constant_7 = STATIC_STRING("4o4nskk4nqlp4noq3Hy4nm3Iy3Uy");
    SET_SYMBOL_VALUE(Qkfep_jy_index,
	    regenerate_optimized_constant(string_constant_7));
    Qkfep_kk_index = STATIC_SYMBOL("KFEP-KK-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kk_index,Kfep_kk_index);
    string_constant_8 = 
	    STATIC_STRING("4p4nukk4nslx4nqy3cy4no3dy3-*y4nm3-=y3-3y");
    SET_SYMBOL_VALUE(Qkfep_kk_index,
	    regenerate_optimized_constant(string_constant_8));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_kfep_master_g2_struct = 
	    STATIC_SYMBOL("KFEP-MASTER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qkfep_master = STATIC_SYMBOL("KFEP-MASTER",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kfep_master_g2_struct,
	    Qkfep_master,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qkfep_master,
	    Qg2_defstruct_structure_name_kfep_master_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_kfep_master == UNBOUND)
	The_type_description_of_kfep_master = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m83kCy1n83kCy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_kfep_master;
    The_type_description_of_kfep_master = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_9));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kfep_master_g2_struct,
	    The_type_description_of_kfep_master,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qkfep_master,
	    The_type_description_of_kfep_master,Qtype_description_of_type);
    Qoutstanding_kfep_master_count = 
	    STATIC_SYMBOL("OUTSTANDING-KFEP-MASTER-COUNT",AB_package);
    Qkfep_master_structure_memory_usage = 
	    STATIC_SYMBOL("KFEP-MASTER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_10 = STATIC_STRING("1q83kCy8s83-c3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_kfep_master_count);
    push_optimized_constant(Qkfep_master_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qchain_of_available_kfep_masters = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KFEP-MASTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_kfep_masters,
	    Chain_of_available_kfep_masters);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_kfep_masters,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qkfep_master_count = STATIC_SYMBOL("KFEP-MASTER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_master_count,Kfep_master_count);
    record_system_variable(Qkfep_master_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_kfep_masters_vector == UNBOUND)
	Chain_of_available_kfep_masters_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qkfep_master_structure_memory_usage,
	    STATIC_FUNCTION(kfep_master_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_kfep_master_count,
	    STATIC_FUNCTION(outstanding_kfep_master_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_kfep_master_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_kfep_master,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qkfep_master,
	    reclaim_structure_for_kfep_master_1);
    Qg2_defstruct_structure_name_kfep_batch_g2_struct = 
	    STATIC_SYMBOL("KFEP-BATCH-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qkfep_batch = STATIC_SYMBOL("KFEP-BATCH",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_kfep_batch_g2_struct,
	    Qkfep_batch,Qab_name_of_unique_structure_type);
    mutate_global_property(Qkfep_batch,
	    Qg2_defstruct_structure_name_kfep_batch_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_kfep_batch == UNBOUND)
	The_type_description_of_kfep_batch = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83kAy1n83kAy8n8k1l8n0000000k3Cyk0k0");
    temp = The_type_description_of_kfep_batch;
    The_type_description_of_kfep_batch = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    mutate_global_property(Qg2_defstruct_structure_name_kfep_batch_g2_struct,
	    The_type_description_of_kfep_batch,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qkfep_batch,The_type_description_of_kfep_batch,
	    Qtype_description_of_type);
    Qoutstanding_kfep_batch_count = 
	    STATIC_SYMBOL("OUTSTANDING-KFEP-BATCH-COUNT",AB_package);
    Qkfep_batch_structure_memory_usage = 
	    STATIC_SYMBOL("KFEP-BATCH-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_12 = STATIC_STRING("1q83kAy8s83-c1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_kfep_batch_count);
    push_optimized_constant(Qkfep_batch_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_kfep_batchs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-KFEP-BATCHS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_kfep_batchs,
	    Chain_of_available_kfep_batchs);
    record_system_variable(Qchain_of_available_kfep_batchs,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qkfep_batch_count = STATIC_SYMBOL("KFEP-BATCH-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_batch_count,Kfep_batch_count);
    record_system_variable(Qkfep_batch_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_kfep_batchs_vector == UNBOUND)
	Chain_of_available_kfep_batchs_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qkfep_batch_structure_memory_usage,
	    STATIC_FUNCTION(kfep_batch_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_kfep_batch_count,
	    STATIC_FUNCTION(outstanding_kfep_batch_count,NIL,FALSE,0,0));
    reclaim_structure_for_kfep_batch_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_kfep_batch,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qkfep_batch,
	    reclaim_structure_for_kfep_batch_1);
    Qkfep_gobisetu1 = STATIC_SYMBOL("KFEP-GOBISETU1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_gobisetu1,Kfep_gobisetu1);
    string_constant_13 = 
	    STATIC_STRING("43-gy4n7s3*Wy3*dykkkkkkok4n7s3*Wy3*jykkkkkkop4n7s3*Wy3*lykkkkkkok4n7s3*Wy3*eykkkkkkok4n7s3*Wy3*mykkkkkkok4n7s3*Wy3*nykkkkkkok4n7");
    string_constant_14 = 
	    STATIC_STRING("s3*Wy3*vykkkkkkok4n7s3*Wy3*xykkkkkkok4n7s3*Wy3=4ykkkkkkok4n7s3*Wy3=6ykkkkkkok4n7s3*Wy3=Aykkkkkkok4n7s3*Wy3=Cykkkkkkok4n7s3*Wy3=O");
    string_constant_15 = 
	    STATIC_STRING("ykkkkkkok4n7s3*Wy3=Qykkkkkkok4n7s3*Wy3=Uykkkkkkok4n7s3*Wy3=bykkkkkkok4n7s3*Wy3=fykkkkkkok4n7s3*Wy3=hykkkkkkok4n7s3*Wy3*cykkkkkko");
    string_constant_16 = 
	    STATIC_STRING("k4n7s3*Wy3*Wykkkkkksk4n7s3*Wy3*fykkkkkksk4n7s3*Wy3*gykkkkkksk4n7s3*Wy3*qykkkkkksk4n7s3*Wy3=-ykkkkkksk4n7s3*Wy3=7ykkkkkksk4n7s3*W");
    string_constant_17 = 
	    STATIC_STRING("y3=Eykkkkkksk4n7s3*Wy3=Fykkkkkksk4n7s3*Wy3=Rykkkkkksk4n7s3*Wy3=cykkkkkksk4n7s3*Wy3*aykkkkkkrk4n7s3*Wy3*jykkkkkkrk4n7s3*Wy3*kykkk");
    string_constant_18 = 
	    STATIC_STRING("kkkrk4n7s3*Wy3*tykkkkkkrk4n7s3*Wy3*uykkkkkkrk4n7s3*Wy3=2ykkkkkkrk4n7s3*Wy3=3ykkkkkkrk4n7s3*Wy3=9ykkkkkkrk4n7s3*Wy3=Kykkkkkkrk4n7");
    string_constant_19 = 
	    STATIC_STRING("s3*Wy3=Lykkkkkkrk4n7s3*Wy3=Tykkkkkkrk4n7s3*Wy3=eykkkkkkrk4n7s3*Wy3==ykkkkkkol4n7s3*Wy3*fykkkkkkol4n7s3*Wy3*Wykkkkkkol4n7s3*Wy3*g");
    string_constant_20 = 
	    STATIC_STRING("ykkkkkkol4n7s3*Wy3*pykkkkkkol4n7s3*Wy3=-ykkkkkkol4n7s3*Wy3==ykkkkkkol4n7s3*Wy3=7ykkkkkkol4n7s3*Wy3=lykkkkkkol4n7s3*Wy3=Fykkkkkko");
    string_constant_21 = 
	    STATIC_STRING("l4n7s3*Wy3=cykkkkkkol4n7s3*Wy3*Wykkkkkksl4n7s3*Wy3*fykkkkkksl4n7s3*Wy3*gykkkkkksl4n7s3*Wy3*qykkkkkksl4n7s3*Wy3=-ykkkkkksl4n7s3*W");
    string_constant_22 = 
	    STATIC_STRING("y3=7ykkkkkksl4n7s3*Wy3=Eykkkkkksl4n7s3*Wy3=Fykkkkkksl4n7s3*Wy3=Rykkkkkksl4n7s3*Wy3=cykkkkkksl4n7s3*Wy3*aykkkkkkrl4n7s3*Wy3*jykkk");
    string_constant_23 = 
	    STATIC_STRING("kkkrl4n7s3*Wy3*kykkkkkkrl4n7s3*Wy3*tykkkkkkrl4n7s3*Wy3*uykkkkkkrl4n7s3*Wy3=2ykkkkkkrl4n7s3*Wy3=3ykkkkkkrl4n7s3*Wy3=9ykkkkkkrl4n7");
    string_constant_24 = 
	    STATIC_STRING("s3*Wy3=Kykkkkkkrl4n7s3*Wy3=Lykkkkkkrl4n7s3*Wy3=Tykkkkkkrl4n7s3*Wy3=eykkkkkkrl4n7s3*Wy3*hykkkkkkom4n7s3*Wy3*iykkkkkkom4n7s3*Wy3*r");
    string_constant_25 = 
	    STATIC_STRING("ykkkkkkom4n7s3*Wy3=0ykkkkkkom4n7s3*Wy3=8ykkkkkkom4n7s3*Wy3=Iykkkkkkom4n7s3*Wy3=Sykkkkkkom4n7s3*Wy3=dykkkkkkom4n7s3*Wy3*Yykkkkkko");
    string_constant_26 = 
	    STATIC_STRING("m4n7s3*Wy3*hykkkkkkon4n7s3*Wy3*iykkkkkkon4n7s3*Wy3*rykkkkkkon4n7s3*Wy3=0ykkkkkkon4n7s3*Wy3=8ykkkkkkon4n7s3*Wy3=Iykkkkkkon4n7s3*W");
    string_constant_27 = 
	    STATIC_STRING("y3=Sykkkkkkon4n7s3*Wy3=dykkkkkkon4n7s3*Wy3*Yykkkkkkon4n7s3*Wy3*jykkkkkkoo4n7s3*Wy3*kykkkkkkoo4n7s3*Wy3*tykkkkkkoo4n7s3*Wy3=2ykkk");
    string_constant_28 = 
	    STATIC_STRING("kkkoo4n7s3*Wy3=9ykkkkkkoo4n7s3*Wy3=Lykkkkkkoo4n7s3*Wy3=Tykkkkkkoo4n7s3*Wy3=eykkkkkkoo4n7s3*Wy3*aykkkkkkoo4n7s3*Wy3*kykkkkkkop4n7");
    string_constant_29 = 
	    STATIC_STRING("s3*Wy3*tykkkkkkop4n7s3*Wy3=2ykkkkkkop4n7s3*Wy3=9ykkkkkkop4n7s3*Wy3=Lykkkkkkop4n7s3*Wy3=Tykkkkkkop4n7s3*Wy3=eykkkkkkop4n7s3*Wy3*a");
    string_constant_30 = STATIC_STRING("ykkkkkkop0");
    SET_SYMBOL_VALUE(Qkfep_gobisetu1,regenerate_optimized_constant(list(18,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30)));
    Qkfep_gobisetu2 = STATIC_SYMBOL("KFEP-GOBISETU2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_gobisetu2,Kfep_gobisetu2);
    string_constant_31 = 
	    STATIC_STRING("43-hy4n7s3*Wy3*Wy3*Wy3=dykkkksm4n7s3*Wy3*fy3*Wy3=dykkkksm4n7s3*Wy3*gy3*Wy3=dykkkksm4n7s3*Wy3*qy3*Wy3=dykkkksm4n7s3*Wy3=-y3*Wy3=d");
    string_constant_32 = 
	    STATIC_STRING("ykkkksm4n7s3*Wy3=7y3*Wy3=dykkkksm4n7s3*Wy3=Ey3*Wy3=dykkkksm4n7s3*Wy3=Fy3*Wy3=dykkkksm4n7s3*Wy3=Ry3*Wy3=dykkkksm4n7s3*Wy3=cy3*Wy3");
    string_constant_33 = 
	    STATIC_STRING("=dykkkksm4n7s3*Wy3*ay3*Wy3=dykkkkrm4n7s3*Wy3*jy3*Wy3=dykkkkrm4n7s3*Wy3*ky3*Wy3=dykkkkrm4n7s3*Wy3*ty3*Wy3=dykkkkrm4n7s3*Wy3*uy3*W");
    string_constant_34 = 
	    STATIC_STRING("y3=dykkkkrm4n7s3*Wy3=2y3*Wy3=dykkkkrm4n7s3*Wy3=3y3*Wy3=dykkkkrm4n7s3*Wy3=9y3*Wy3=dykkkkrm4n7s3*Wy3=Ky3*Wy3=dykkkkrm4n7s3*Wy3=Ly3");
    string_constant_35 = 
	    STATIC_STRING("*Wy3=dykkkkrm4n7s3*Wy3=Ty3*Wy3=dykkkkrm4n7s3*Wy3=ey3*Wy3=dykkkkrm4n7s3*Wy3*Wy3*Wy3=dykkkksn4n7s3*Wy3*fy3*Wy3=dykkkksn4n7s3*Wy3*g");
    string_constant_36 = 
	    STATIC_STRING("y3*Wy3=dykkkksn4n7s3*Wy3*qy3*Wy3=dykkkksn4n7s3*Wy3=-y3*Wy3=dykkkksn4n7s3*Wy3=7y3*Wy3=dykkkksn4n7s3*Wy3=Ey3*Wy3=dykkkksn4n7s3*Wy3");
    string_constant_37 = 
	    STATIC_STRING("=Fy3*Wy3=dykkkksn4n7s3*Wy3=Ry3*Wy3=dykkkksn4n7s3*Wy3=cy3*Wy3=dykkkksn4n7s3*Wy3*ay3*Wy3=dykkkkrn4n7s3*Wy3*jy3*Wy3=dykkkkrn4n7s3*W");
    string_constant_38 = 
	    STATIC_STRING("y3*ky3*Wy3=dykkkkrn4n7s3*Wy3*ty3*Wy3=dykkkkrn4n7s3*Wy3*uy3*Wy3=dykkkkrn4n7s3*Wy3=2y3*Wy3=dykkkkrn4n7s3*Wy3=3y3*Wy3=dykkkkrn4n7s3");
    string_constant_39 = 
	    STATIC_STRING("*Wy3=9y3*Wy3=dykkkkrn4n7s3*Wy3=Ky3*Wy3=dykkkkrn4n7s3*Wy3=Ly3*Wy3=dykkkkrn4n7s3*Wy3=Ty3*Wy3=dykkkkrn4n7s3*Wy3=ey3*Wy3=dykkkkrn4n7");
    string_constant_40 = 
	    STATIC_STRING("s3*Wy3*Wy3*Wy3=eykkkkso4n7s3*Wy3*fy3*Wy3=eykkkkso4n7s3*Wy3*gy3*Wy3=eykkkkso4n7s3*Wy3*qy3*Wy3=eykkkkso4n7s3*Wy3=-y3*Wy3=eykkkkso4");
    string_constant_41 = 
	    STATIC_STRING("n7s3*Wy3=7y3*Wy3=eykkkkso4n7s3*Wy3=Ey3*Wy3=eykkkkso4n7s3*Wy3=Fy3*Wy3=eykkkkso4n7s3*Wy3=Ry3*Wy3=eykkkkso4n7s3*Wy3=cy3*Wy3=eykkkks");
    string_constant_42 = 
	    STATIC_STRING("o4n7s3*Wy3*ay3*Wy3=eykkkkro4n7s3*Wy3*jy3*Wy3=eykkkkro4n7s3*Wy3*ky3*Wy3=eykkkkro4n7s3*Wy3*ty3*Wy3=eykkkkro4n7s3*Wy3*uy3*Wy3=eykkk");
    string_constant_43 = 
	    STATIC_STRING("kro4n7s3*Wy3=2y3*Wy3=eykkkkro4n7s3*Wy3=3y3*Wy3=eykkkkro4n7s3*Wy3=9y3*Wy3=eykkkkro4n7s3*Wy3=Ky3*Wy3=eykkkkro4n7s3*Wy3=Ly3*Wy3=eyk");
    string_constant_44 = 
	    STATIC_STRING("kkkro4n7s3*Wy3=Ty3*Wy3=eykkkkro4n7s3*Wy3=ey3*Wy3=eykkkkro4n7s3*Wy3*Wy3*Wy3=fykkkksp4n7s3*Wy3*fy3*Wy3=fykkkksp4n7s3*Wy3*gy3*Wy3=f");
    string_constant_45 = 
	    STATIC_STRING("ykkkksp4n7s3*Wy3*qy3*Wy3=fykkkksp4n7s3*Wy3=-y3*Wy3=fykkkksp4n7s3*Wy3=7y3*Wy3=fykkkksp4n7s3*Wy3=Ey3*Wy3=fykkkksp4n7s3*Wy3=Fy3*Wy3");
    string_constant_46 = 
	    STATIC_STRING("=fykkkksp4n7s3*Wy3=Ry3*Wy3=fykkkksp4n7s3*Wy3=cy3*Wy3=fykkkksp4n7s3*Wy3*Wy3*Wy3=aykkkksp4n7s3*Wy3*fy3*Wy3=aykkkksp4n7s3*Wy3*gy3*W");
    string_constant_47 = 
	    STATIC_STRING("y3=aykkkksp4n7s3*Wy3*qy3*Wy3=aykkkksp4n7s3*Wy3=-y3*Wy3=aykkkksp4n7s3*Wy3=7y3*Wy3=aykkkksp4n7s3*Wy3=Ey3*Wy3=aykkkksp4n7s3*Wy3=Fy3");
    string_constant_48 = 
	    STATIC_STRING("*Wy3=aykkkksp4n7s3*Wy3=Ry3*Wy3=aykkkksp4n7s3*Wy3=cy3*Wy3=aykkkksp4n7s3*Wy3*ay3*Wy3=fykkkkrp4n7s3*Wy3*jy3*Wy3=fykkkkrp4n7s3*Wy3*k");
    string_constant_49 = 
	    STATIC_STRING("y3*Wy3=fykkkkrp4n7s3*Wy3*ty3*Wy3=fykkkkrp4n7s3*Wy3*uy3*Wy3=fykkkkrp4n7s3*Wy3=2y3*Wy3=fykkkkrp4n7s3*Wy3=3y3*Wy3=fykkkkrp4n7s3*Wy3");
    string_constant_50 = 
	    STATIC_STRING("=9y3*Wy3=fykkkkrp4n7s3*Wy3=Ky3*Wy3=fykkkkrp4n7s3*Wy3=Ly3*Wy3=fykkkkrp4n7s3*Wy3*ay3*Wy3=aykkkkrp4n7s3*Wy3*jy3*Wy3=aykkkkrp4n7s3*W");
    string_constant_51 = 
	    STATIC_STRING("y3*ky3*Wy3=aykkkkrp4n7s3*Wy3*ty3*Wy3=aykkkkrp4n7s3*Wy3*uy3*Wy3=aykkkkrp4n7s3*Wy3=2y3*Wy3=aykkkkrp4n7s3*Wy3=3y3*Wy3=aykkkkrp4n7s3");
    string_constant_52 = 
	    STATIC_STRING("*Wy3=9y3*Wy3=aykkkkrp4n7s3*Wy3=Ky3*Wy3=aykkkkrp4n7s3*Wy3=Ly3*Wy3=aykkkkrp4n7s3*Wy3=Ty3*Wy3=fykkkkrp4n7s3*Wy3=ey3*Wy3=fykkkkrp4n7");
    string_constant_53 = 
	    STATIC_STRING("s3*Wy3=Ty3*Wy3=aykkkkrp4n7s3*Wy3=ey3*Wy3=aykkkkrp0");
    SET_SYMBOL_VALUE(Qkfep_gobisetu2,regenerate_optimized_constant(list(23,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51,
	    string_constant_52,string_constant_53)));
    Qkfep_jyodou_array = STATIC_SYMBOL("KFEP-JYODOU-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_jyodou_array,Kfep_jyodou_array);
    string_constant_54 = 
	    STATIC_STRING("43*Ty4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=dy3*Wy3*ly3*Wy3=4ykkkkkkln3wy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=dy3*Wy3=4y3*Wy3*fykkkkkkln3wy4o73Cy3*W");
    string_constant_55 = 
	    STATIC_STRING("y3*ny3*Wy3*ty3*Wy3=dy3*Wy3=Ay3*Wy3=3ykkkkkkln3wy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=dy3*Wy3=Ay3*Wy3=7ykkkkkkln3wy4o73Cy3*Wy3*vy3*Wy3*Yy3");
    string_constant_56 = 
	    STATIC_STRING("*Wy3=+y3*Wy3==y3*Wy3*xykkkkkkll3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=+y3*Wy3=fy3*Wy3*Yykkkkkklk3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=3y3");
    string_constant_57 = 
	    STATIC_STRING("*Wy3*Uy3*Wy3=dykkkkkkll3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3*ly3*Wy3=4ykkkkkkln3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3=4y3");
    string_constant_58 = 
	    STATIC_STRING("*Wy3*fykkkkkkln3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3=Ay3*Wy3=3ykkkkkkln3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3=Ay3*Wy3=7yk");
    string_constant_59 = 
	    STATIC_STRING("kkkkkln3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3=by3*Wy3=Cykkkkkklo3U*=Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=7y3*Wy3=6y3*Wy3=dykkkkkkll3");
    string_constant_60 = 
	    STATIC_STRING("U*=Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=+y3*Wy3==y3*Wy3*xykkkkkkll3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=+y3*Wy3=fy3*Wy3*Yykkkkkklk3000Ry4o7");
    string_constant_61 = 
	    STATIC_STRING("3Cy3*Wy3=ay3*Wy3*Yy3*Wy3=3y3*Wy3*Uy3*Wy3=dykkkkkkll3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=6y3*Wy3*ly3*Wy3=4ykkkkkkln3000Ry4o73Cy3*Wy3");
    string_constant_62 = 
	    STATIC_STRING("=ay3*Wy3*Yy3*Wy3=6y3*Wy3=4y3*Wy3*fykkkkkkln3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=6y3*Wy3=Ay3*Wy3=3ykkkkkkln3000Ry4o73Cy3*Wy3=ay3*Wy3");
    string_constant_63 = 
	    STATIC_STRING("*Yy3*Wy3=6y3*Wy3=Ay3*Wy3=7ykkkkkkln3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=6y3*Wy3=by3*Wy3=Cykkkkkklo3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3");
    string_constant_64 = 
	    STATIC_STRING("=7y3*Wy3=6y3*Wy3=dykkkkkkll3000Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wy3*Wy3*ly3*Wy3=4ykkkkkkln3=+**Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wy3*Wy");
    string_constant_65 = 
	    STATIC_STRING("3=4y3*Wy3*fykkkkkkln3=+**Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wy3*Wy3=Ay3*Wy3=3ykkkkkkln3=+**Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wy3*Wy3=Ay3*");
    string_constant_66 = 
	    STATIC_STRING("Wy3=7ykkkkkkln3=+**Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*dy3*Wy3==y3*Wy3*xykkkkkkll3=+**Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*jy3*Wy3=ey3*Wy3=Cy");
    string_constant_67 = 
	    STATIC_STRING("kkkkkklo3=+**Ry4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dy3*Wy3*ly3*Wy3=4ykkkkkkln3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dy3*Wy3=4y3*Wy3*fykkkkkkln3o");
    string_constant_68 = 
	    STATIC_STRING("y4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dy3*Wy3=Ay3*Wy3=3ykkkkkkln3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dy3*Wy3=Ay3*Wy3=7ykkkkkkln3oy4o73Cy3*Wy3*n");
    string_constant_69 = 
	    STATIC_STRING("y3*Wy3*ty3*Wy3=6y3*Wy3*Wykkkkkkkklk3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=Qy3*Wy3*rykkkkkkkkll3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=dy3*ty3=wyk");
    string_constant_70 = 
	    STATIC_STRING("kkkkkkklk3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=ey3*Wy3=Cykkkkkkkklo3oy4o73Cy3*Wy3*ty3*Wy3=dy3*Wy3*ly3*Wy3=4ykkkkkkkkln3by4o73Cy3*Wy3*ty");
    string_constant_71 = 
	    STATIC_STRING("3*Wy3=dy3*Wy3=4y3*Wy3*fykkkkkkkkln3by4o73Cy3*Wy3*ty3*Wy3=dy3*Wy3=Ay3*Wy3=3ykkkkkkkkln3by4o73Cy3*Wy3*ty3*Wy3=dy3*Wy3=Ay3*Wy3=7ykk");
    string_constant_72 = 
	    STATIC_STRING("kkkkkkln3by4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*Wy3=bykkkkkkkkln3S+-Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6y3*ty3=wykkkkkkkkln3S+-Ry4o73Cy3*W");
    string_constant_73 = 
	    STATIC_STRING("y3*xy3*Wy3*Wy3*Wy3*ly3*Wy3=4ykkkkkkkkln3-Ry4o73Cy3*Wy3*xy3*Wy3*Wy3*Wy3=4y3*Wy3*fykkkkkkkkln3-Ry4o73Cy3*Wy3*xy3*Wy3*Wy3*Wy3=Ay3*W");
    string_constant_74 = 
	    STATIC_STRING("y3=3ykkkkkkkkln3-Ry4o73Cy3*Wy3*xy3*Wy3*Wy3*Wy3=Ay3*Wy3=7ykkkkkkkkln3-Ry4o73Cy3*Wy3*xy3*Wy3*dy3*Wy3==y3*Wy3*xykkkkkkkkll3-Ry4o73C");
    string_constant_75 = 
	    STATIC_STRING("y3*Wy3*xy3*Wy3*dy3*Wy3=fy3*Wy3*Yykkkkkkkklk3-Ry4o73Cy3*Wy3*xy3*Wy3*hy3*Wy3=6y3*Wy3*Wykkkkkkkklk3-Ry4o73Cy3*Wy3*xy3*Wy3*jy3*Wy3=e");
    string_constant_76 = 
	    STATIC_STRING("y3*Wy3=Cykkkkkkkklo3-Ry4o73Cy3*Wy3=3y3*Wy3*ry3*Wy3*ly3*Wy3=4ykkkkkkkkln3-+**Ry4o73Cy3*Wy3=3y3*Wy3*ry3*Wy3=4y3*Wy3*fykkkkkkkkln3-");
    string_constant_77 = 
	    STATIC_STRING("+**Ry4o73Cy3*Wy3=3y3*Wy3*ry3*Wy3=Ay3*Wy3=3ykkkkkkkkln3-+**Ry4o73Cy3*Wy3=3y3*Wy3*ry3*Wy3=Ay3*Wy3=7ykkkkkkkkln3-+**Ry4o73Cy3*Wy3=6");
    string_constant_78 = 
	    STATIC_STRING("y3*Wy3*Wy3*Wy3*ly3*Wy3=4ykkkkkkkkln3xy4o73Cy3*Wy3=6y3*Wy3*Wy3*Wy3=4y3*Wy3*fykkkkkkkkln3xy4o73Cy3*Wy3=6y3*Wy3*Wy3*Wy3=Ay3*Wy3=3yk");
    string_constant_79 = 
	    STATIC_STRING("kkkkkkkln3xy4o73Cy3*Wy3=6y3*Wy3*Wy3*Wy3=Ay3*Wy3=7ykkkkkkkkln3xy4o73Cy3*Wy3=6y3*Wy3*dy3*Wy3==y3*Wy3*xykkkkkkkkll3xy4o73Cy3*Wy3=6y");
    string_constant_80 = 
	    STATIC_STRING("3*Wy3*dy3*Wy3=fy3*Wy3*Yykkkkkkkklk3xy4o73Cy3*Wy3=6y3*Wy3*hy3*Wy3=6y3*Wy3=dykkkkkkkkll3xy4o73Cy3*Wy3=6y3*Wy3*jy3*Wy3=ey3*Wy3=Cykk");
    string_constant_81 = 
	    STATIC_STRING("kkkkkklo3xy4o73Cy3*Wy3=Qy3*Wy3*py3*Wy3=Zy3*Wy3*Yykkkkkkkklk3-Ry4o73Cy3*Wy3=Qy3*Wy3*ry3*Wy3*ly3*Wy3=4ykkkkkkkkln3-Ry4o73Cy3*Wy3=Q");
    string_constant_82 = 
	    STATIC_STRING("y3*Wy3*ry3*Wy3=4y3*Wy3*fykkkkkkkkln3-Ry4o73Cy3*Wy3=Qy3*Wy3*ry3*Wy3=Ay3*Wy3=3ykkkkkkkkln3-Ry4o73Cy3*Wy3=Qy3*Wy3*ry3*Wy3=Ay3*Wy3=7");
    string_constant_83 = 
	    STATIC_STRING("ykkkkkkkkln3-Ry4o73Cy3*Wy3=Qy3*Wy3*ry3*Wy3=ey3*Wy3=Cykkkkkkkklo3-Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=6y3*Wy3=bykkkkkkkklo3000Ry4o73Cy3");
    string_constant_84 = 
	    STATIC_STRING("*Wy3=ay3*Wy3*Yy3*Wy3=6y3*ty3=wykkkkkkkkln3000Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wy3*ty3=wykkkkkkkkln3*+**Ry4o73Cy3*Wy3=by3*Wy3=ey3*Wy");
    string_constant_85 = 
	    STATIC_STRING("3=6y3*Wy3*Wykkkkkkkklk3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=Qy3*Wy3*rykkkkkkkkll3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dy3*ty3=wykkkkkkkkln3oy4");
    string_constant_86 = 
	    STATIC_STRING("o73Cy3*Wy3=by3*Wy3=ey3*Wy3=ey3*Wy3=Cykkkkkkkklo3oy4o73Cy3*Wy3=ey3*Wy3=dy3*Wy3*ly3*Wy3=4ykkkkkkkkln3by4o73Cy3*Wy3=ey3*Wy3=dy3*Wy3");
    string_constant_87 = 
	    STATIC_STRING("=4y3*Wy3*fykkkkkkkkln3by4o73Cy3*Wy3=ey3*Wy3=dy3*Wy3=Ay3*Wy3=3ykkkkkkkkln3by4o73Cy3*Wy3=ey3*Wy3=dy3*Wy3=Ay3*Wy3=7ykkkkkkkkln3by4o");
    string_constant_88 = 
	    STATIC_STRING("73Cy3*Wy3*Yy3*Wy3*ly3*Wy3=4ykkkkkkkkkkln3Ty4o73Cy3*Wy3*Yy3*Wy3=4y3*Wy3*fykkkkkkkkkkln3Ty4o73Cy3*Wy3*Yy3*Wy3=Ay3*Wy3=3ykkkkkkkkkk");
    string_constant_89 = 
	    STATIC_STRING("ln3Ty4o73Cy3*Wy3*Yy3*Wy3=Ay3*Wy3=7ykkkkkkkkkkln3Ty4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3*xykkkkkkkkkkll3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=aykkk");
    string_constant_90 = 
	    STATIC_STRING("kkkkkkklp3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=dykkkkkkkkkklm3oy4o73Cy3*Wy3*ny3*Wy3*ty3*Wy3=fykkkkkkkkkklp3oy4o73Cy3*Wy3*ty3*Wy3=6y3*Wy");
    string_constant_91 = 
	    STATIC_STRING("3*Wykkkkkkkkkklk3by4o73Cy3*Wy3*ty3*Wy3=Qy3*Wy3*rykkkkkkkkkkll3by4o73Cy3*Wy3*ty3*Wy3=dy3*ty3=wykkkkkkkkkklk3by4o73Cy3*Wy3*ty3*Wy3");
    string_constant_92 = 
	    STATIC_STRING("=ey3*Wy3=Cykkkkkkkkkklo3by4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=+ykkkkkkkkkklm3001Ry4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=6ykkkkkkkkkkln3001Ry4o73Cy");
    string_constant_93 = 
	    STATIC_STRING("3*Wy3*xy3*Wy3*Wy3*ty3=wykkkkkkkkkkln3-Ry4o73Cy3*Wy3*xy3*Wy3*ly3*Wy3=4ykkkkkkkkkkln3---Ry4o73Cy3*Wy3*xy3*Wy3=4y3*Wy3*fykkkkkkkkkk");
    string_constant_94 = 
	    STATIC_STRING("ln3---Ry4o73Cy3*Wy3*xy3*Wy3=Ay3*Wy3=3ykkkkkkkkkkln3---Ry4o73Cy3*Wy3*xy3*Wy3=Ay3*Wy3=7ykkkkkkkkkkln3---Ry4o73Cy3*Wy3*xy3*Wy3=by3*");
    string_constant_95 = 
	    STATIC_STRING("Wy3=Cykkkkkkkkkklo3---Ry4o73Cy3*Wy3*xy3*Wy3=fy3*Wy3*Yykkkkkkkkkklk3---Ry4o73Cy3*Wy3=+y3*Wy3==y3*Wy3*xykkkkkkkkkkll3-+++y4o73Cy3*");
    string_constant_96 = 
	    STATIC_STRING("Wy3=+y3*Wy3=fy3*Wy3*Yykkkkkkkkkklk3S++y4o73Cy3*Wy3=3y3*Wy3*Uy3*Wy3=dykkkkkkkkkkll3-+++y4o73Cy3*Wy3=3y3*Wy3*py3*Wy3*xykkkkkkkkkkl");
    string_constant_97 = 
	    STATIC_STRING("l3-+++y4o73Cy3*Wy3=3y3*Wy3*ry3*ty3=wykkkkkkkkkkln3-+++y4o73Cy3*Wy3=6y3*Wy3*Wy3*ty3=wykkkkkkkkkkln3xy4o73Cy3*Wy3=6y3*Wy3*ly3*Wy3=");
    string_constant_98 = 
	    STATIC_STRING("4ykkkkkkkkkkln30+++y4o73Cy3*Wy3=6y3*Wy3=4y3*Wy3*fykkkkkkkkkkln30+++y4o73Cy3*Wy3=6y3*Wy3=Ay3*Wy3=3ykkkkkkkkkkln30+++y4o73Cy3*Wy3=");
    string_constant_99 = 
	    STATIC_STRING("6y3*Wy3=Ay3*Wy3=7ykkkkkkkkkkln30+++y4o73Cy3*Wy3=6y3*Wy3=by3*Wy3=Cykkkkkkkkkklo34+++y4o73Cy3*Wy3=8y3*Wy3*ly3*Wy3=4ykkkkkkkkkkln3x");
    string_constant_100 = 
	    STATIC_STRING("y4o73Cy3*Wy3=8y3*Wy3=4y3*Wy3*fykkkkkkkkkkln3xy4o73Cy3*Wy3=8y3*Wy3=Ay3*Wy3=3ykkkkkkkkkkln3xy4o73Cy3*Wy3=8y3*Wy3=Ay3*Wy3=7ykkkkkkk");
    string_constant_101 = 
	    STATIC_STRING("kkkln3xy4o73Cy3*Wy3=Qy3*Wy3*py3*Wy3*xykkkkkkkkkkll3-Ry4o73Cy3*Wy3=Qy3*Wy3*ry3*ty3=wykkkkkkkkkkln3-Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=");
    string_constant_102 = 
	    STATIC_STRING("+ykkkkkkkkkklm3000Ry4o73Cy3*Wy3=ay3*Wy3*Yy3*Wy3=6ykkkkkkkkkkll3000Ry4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wykkkkkkkkkklm3-+**Ry4o73Cy3*Wy3");
    string_constant_103 = 
	    STATIC_STRING("=by3*Wy3=ey3*Wy3*xykkkkkkkkkkll3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=aykkkkkkkkkklp3oy4o73Cy3*Wy3=by3*Wy3=ey3*Wy3=dykkkkkkkkkklm3oy4o73");
    string_constant_104 = 
	    STATIC_STRING("Cy3*Wy3=by3*Wy3=ey3*Wy3=fykkkkkkkkkklp3oy4o73Cy3*Wy3=ey3*Wy3=6y3*Wy3*Wykkkkkkkkkklk3by4o73Cy3*Wy3=ey3*Wy3=Qy3*Wy3*rykkkkkkkkkkll");
    string_constant_105 = 
	    STATIC_STRING("3by4o73Cy3*Wy3=ey3*Wy3=dy3*ty3=wykkkkkkkkkkln3by4o73Cy3*Wy3=ey3*Wy3=ey3*Wy3=Cykkkkkkkkkklo3by4o73Cy3*Wy3=ly3*Wy3*ly3*Wy3=4ykkkkk");
    string_constant_106 = 
	    STATIC_STRING("kkkkklk3xy4o73Cy3*Wy3=ly3*Wy3=4y3*Wy3*fykkkkkkkkkkln3xy4o73Cy3*Wy3=ly3*Wy3=Ay3*Wy3=3ykkkkkkkkkkln3xy4o73Cy3*Wy3=ly3*Wy3=Ay3*Wy3=");
    string_constant_107 = 
	    STATIC_STRING("7ykkkkkkkkkkln3xy4o73Cy3*Wy3*Yy3*ty3=wykkkkkkkkkkkkln3SSTy4o73Cy3*Wy3*ty3*Wy3*xykkkkkkkkkkkkll3by4o73Cy3*Wy3*ty3*Wy3=aykkkkkkkkk");
    string_constant_108 = 
	    STATIC_STRING("kkklp3by4o73Cy3*Wy3*ty3*Wy3=dykkkkkkkkkkkklm3by4o73Cy3*Wy3*ty3*Wy3=fykkkkkkkkkkkklp3by4o73Cy3*Wy3*xy3*Wy3*Wykkkkkkkkkkkklm3-Ry4o");
    string_constant_109 = 
	    STATIC_STRING("73Cy3*Wy3*xy3*Wy3=bykkkkkkkkkkkklo3-Ry4o73Cy3*Wy3*xy3*ty3=wykkkkkkkkkkkkln3-Ry4o73Cy3*Wy3=3y3*Wy3*rykkkkkkkkkkkklm3-+**Ry4o73Cy3");
    string_constant_110 = 
	    STATIC_STRING("*Wy3=6y3*Wy3*Wykkkkkkkkkkkklm3xy4o73Cy3*Wy3=6y3*Wy3=bykkkkkkkkkkkklo34+++y4o73Cy3*Wy3=6y3*ty3=wykkkkkkkkkkkkln34+++y4o73Cy3*Wy3=");
    string_constant_111 = 
	    STATIC_STRING("8y3*ty3=wykkkkkkkkkkkkln3xy4o73Cy3*Wy3=9y3*Wy3=Cykkkkkkkkkkkklo3xy4o73Cy3*Wy3=Qy3*Wy3*Wykkkkkkkkkkkklm3*xy4o73Cy3*Wy3=Qy3*Wy3*py");
    string_constant_112 = 
	    STATIC_STRING("kkkkkkkkkkkklp3-Ry4o73Cy3*Wy3=Qy3*Wy3*rykkkkkkkkkkkkll3-Ry4o73Cy3*Wy3=Qy3*Wy3*tykkkkkkkkkkkklp3-Ry4o73Cy3*Wy3=ay3*Wy3*Yykkkkkkkk");
    string_constant_113 = 
	    STATIC_STRING("kkkklm3xy4o73Cy3*Wy3=ey3*Wy3*xykkkkkkkkkkkkll3xy4o73Cy3*Wy3=ey3*Wy3=aykkkkkkkkkkkklp3xy4o73Cy3*Wy3=ey3*Wy3=dykkkkkkkkkkkklm3xy4o");
    string_constant_114 = 
	    STATIC_STRING("73Cy3*Wy3=ey3*Wy3=fykkkkkkkkkkkklp3xy4o73Cy3*Wy3=ly3*ty3=wykkkkkkkkkkkkln3xy4o73Cy3*Wy3*Yykkkkkkkkkkkkkklm3SSTy4o73Cy3*Wy3*xykkk");
    string_constant_115 = 
	    STATIC_STRING("kkkkkkkkkkklm3-Ry4o73Cy3*Wy3=+ykkkkkkkkkkkkkklm3**Ry4o73Cy3*Wy3=8ykkkkkkkkkkkkkklm3xy4o73Cy3*Wy3=lykkkkkkkkkkkkkklmk");
    SET_SYMBOL_VALUE(Qkfep_jyodou_array,
	    regenerate_optimized_constant(nconc2(list(50,
	    string_constant_54,string_constant_55,string_constant_56,
	    string_constant_57,string_constant_58,string_constant_59,
	    string_constant_60,string_constant_61,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69,string_constant_70,string_constant_71,
	    string_constant_72,string_constant_73,string_constant_74,
	    string_constant_75,string_constant_76,string_constant_77,
	    string_constant_78,string_constant_79,string_constant_80,
	    string_constant_81,string_constant_82,string_constant_83,
	    string_constant_84,string_constant_85,string_constant_86,
	    string_constant_87,string_constant_88,string_constant_89,
	    string_constant_90,string_constant_91,string_constant_92,
	    string_constant_93,string_constant_94,string_constant_95,
	    string_constant_96,string_constant_97,string_constant_98,
	    string_constant_99,string_constant_100,string_constant_101,
	    string_constant_102,string_constant_103),list(12,
	    string_constant_104,string_constant_105,string_constant_106,
	    string_constant_107,string_constant_108,string_constant_109,
	    string_constant_110,string_constant_111,string_constant_112,
	    string_constant_113,string_constant_114,string_constant_115))));
    Qkfep_jyosi_array = STATIC_SYMBOL("KFEP-JYOSI-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_jyosi_array,Kfep_jyosi_array);
    string_constant_116 = 
	    STATIC_STRING("43Vy4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2y3*Wy3=Uykkkkkkkkkr3---+y4o73Cy3*Wy3*hy3*Wy3=by3*Wy3*Wykkkkkkkkkkkr3000+y4o73Cy3*Wy3*iy3*Wy3=by");
    string_constant_117 = 
	    STATIC_STRING("3*Wy3*Wykkkkkkkkkkkr3000+y4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2ykkkkkkkkkkkr3---+y4o73Cy3*Wy3=6y3*Wy3*ey3*Wy3=bykkkkkkkkkkkr3*++y4o73Cy3");
    string_constant_118 = 
	    STATIC_STRING("*Wy3=Cy3*Wy3*dy3*Wy3=cykkkkkkkkkkkr3000+y4o73Cy3*Wy3*dy3*Wy3=bykkkkkkkkkkkkkr3***+y4o73Cy3*Wy3*fy3*Wy3=cykkkkkkkkkkkkkr3000+y4o7");
    string_constant_119 = 
	    STATIC_STRING("3Cy3*Wy3*gy3*Wy3=cykkkkkkkkkkkkkr3000+y4o73Cy3*Wy3*ly3*Wy3*vykkkkkkkkkkkkkr3000+y4o73Cy3*Wy3*ny3*Wy3*aykkkkkkkkkkkkkr3000+y4o73C");
    string_constant_120 = 
	    STATIC_STRING("y3*Wy3*py3*Wy3*dykkkkkkkkkkkkkr3--++y4o73Cy3*Wy3=+y3*Wy3*jykkkkkkkkkkkkkr3000+y4o73Cy3*Wy3=+y3*Wy3=Aykkkkkkkkkkkkkr3***+y4o73Cy3");
    string_constant_121 = 
	    STATIC_STRING("*Wy3=3y3*Wy3=Uykkkkkkkkkkkkkr3---+y4o73Cy3*Wy3=6y3*Wy3=5ykkkkkkkkkkkkkr3***+y4o73Cy3*Wy3=9y3*Wy3*aykkkkkkkkkkkkkr3***+y4o73Cy3*W");
    string_constant_122 = 
	    STATIC_STRING("y3=Ny3*Wy3*dykkkkkkkkkkkkkr3--++y4o73Cy3*Wy3=Ny3*Wy3=5ykkkkkkkkkkkkkr3000+y4o73Cy3*Wy3=Qy3*Wy3=3ykkkkkkkkkkkkkr32000+y4o73Cy3*Wy");
    string_constant_123 = 
	    STATIC_STRING("3=Wy3*Wy3=bykkkkkkkkkkkkkr32***+y4o73Cy3*Wy3=ay3*Wy3=cykkkkkkkkkkkkkr32000+y4o73Cy3*Wy3*dykkkkkkkkkkkkkkkr3***+y4o73Cy3*Wy3*eykk");
    string_constant_124 = 
	    STATIC_STRING("kkkkkkkkkkkkkr32***+y4o73Cy3*Wy3*nykkkkkkkkkkkkkkkr32***+y4o73Cy3*Wy3=3ykkkkkkkkkkkkkkkr32---+y4o73Cy3*Wy3=4ykkkkkkkkkkkkkkkr32-");
    string_constant_125 = 
	    STATIC_STRING("--+y4o73Cy3*Wy3=7ykkkkkkkkkkkkkkkr32000+y4o73Cy3*Wy3=9ykkkkkkkkkkkkkkkr3***+y4o73Cy3*Wy3=Aykkkkkkkkkkkkkkkr32000+y4o73Cy3*Wy3=By");
    string_constant_126 = 
	    STATIC_STRING("kkkkkkkkkkkkkkkr32---+y4o73Cy3*Wy3=Cykkkkkkkkkkkkkkkr3444+y4o73Cy3*Wy3=Uykkkkkkkkkkkkkkkr32---+y4o73Cy3*Wy3=aykkkkkkkkkkkkkkkr3*");
    string_constant_127 = 
	    STATIC_STRING("**+y4o73Cy3*Wy3=kykkkkkkkkkkkkkkkr32000+y");
    SET_SYMBOL_VALUE(Qkfep_jyosi_array,
	    regenerate_optimized_constant(list(12,string_constant_116,
	    string_constant_117,string_constant_118,string_constant_119,
	    string_constant_120,string_constant_121,string_constant_122,
	    string_constant_123,string_constant_124,string_constant_125,
	    string_constant_126,string_constant_127)));
    Qkfep_keiyo_array = STATIC_SYMBOL("KFEP-KEIYO-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_keiyo_array,Kfep_keiyo_array);
    string_constant_128 = 
	    STATIC_STRING("43-4y4o73Cy3*Wy3=+y3*Wy3*jy3*Wy3=ey3*Wy3=3y3*Wy3=Uykkkkkknmk4o73Cy3*Wy3*Wy3*Wy3*hy3*Wy3=by3*Wy3*Wykkkkkkkkmn3RS+y4o73Cy3*Wy3*Wy3");
    string_constant_129 = 
	    STATIC_STRING("*Wy3*jy3*Wy3=ey3*Wy3=5ykkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3*vy3*Wy3*Yy3*Wy3=+ykkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=3y3*Wy3*py3*Wy3=Z");
    string_constant_130 = 
	    STATIC_STRING("ykkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=by3*Wy3*py3*Wy3*Wykkkkkkkkmm3RS+y4o73Cy3*Wy3*dy3*Wy3==y3*Wy3*xy3*Wy3=cykkkkkkkkml3RS+y4o73Cy");
    string_constant_131 = 
	    STATIC_STRING("3*Wy3=+y3*Wy3*jy3*Wy3=ey3*Wy3=5ykkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3*vy3*Wy3*Yy3*Wy3=+ykkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3==y3*Wy3*xy3*Wy3=");
    string_constant_132 = 
	    STATIC_STRING("cykkkkkkkknlk4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2y3*Wy3=Uykkkkkkkknlk4o73Cy3*Wy3=6y3*Wy3*hy3*Wy3=by3*Wy3*Wykkkkkkkknnk4o73Cy3*Wy3=6y3*W");
    string_constant_133 = 
	    STATIC_STRING("y3=Cy3*Wy3*dy3*Wy3=cykkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=ay3*Wy3*Yy3*Wy3=+ykkkkkkkknnk4o73Cy3*Wy3*Wy3*Wy3*dy3*Wy3=bykkkkkkkkkkmm3RS+y");
    string_constant_134 = 
	    STATIC_STRING("4o73Cy3*Wy3*Wy3*Wy3=+y3*Wy3*jykkkkkkkkkkmn3RS+y4o73Cy3*Wy3*Wy3*Wy3=+y3*Wy3=fykkkkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=6y3*Wy3=bykkkk");
    string_constant_135 = 
	    STATIC_STRING("kkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=Ay3*Wy3=3ykkkkkkkkkkmn3RS+y4o73Cy3*Wy3*Wy3*Wy3=Ay3*Wy3=7ykkkkkkkkkkmn3RS+y4o73Cy3*Wy3*dy3*Wy3==");
    string_constant_136 = 
	    STATIC_STRING("y3*Wy3*xykkkkkkkkkkml3RS+y4o73Cy3*Wy3*dy3*Wy3=fy3*Wy3*Yykkkkkkkkkkmk3RS+y4o73Cy3*Wy3*hy3*Wy3*Uy3*Wy3=dykkkkkkkkkkml3RS+y4o73Cy3*");
    string_constant_137 = 
	    STATIC_STRING("Wy3*hy3*Wy3*ny3*Wy3*aykkkkkkkkkkml3RS+y4o73Cy3*Wy3*hy3*Wy3=2y3*Wy3=Uykkkkkkkkkkml3RS+y4o73Cy3*Wy3*hy3*Wy3=6y3*Wy3*Wykkkkkkkkkkml");
    string_constant_138 = 
	    STATIC_STRING("3RS+y4o73Cy3*Wy3*jy3*Wy3=ey3*Wy3=Cykkkkkkkkkkmo3RS+y4o73Cy3*Wy3*vy3*Wy3*Yy3*Wy3=+ykkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3*dy3*Wy3=bykkk");
    string_constant_139 = 
	    STATIC_STRING("kkkkkkknmk4o73Cy3*Wy3=+y3*Wy3*ly3*Wy3=4ykkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3==y3*Wy3*xykkkkkkkkkknlk4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2ykk");
    string_constant_140 = 
	    STATIC_STRING("kkkkkkkknlk4o73Cy3*Wy3=+y3*Wy3=6y3*Wy3*Uykkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=Uy3*Wy3=Aykkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=fy3*Wy3*Yyk");
    string_constant_141 = 
	    STATIC_STRING("kkkkkkkkknkk4o73Cy3*Wy3=3y3*Wy3*ny3*Wy3*aykkkkkkkkkknlk4o73Cy3*Wy3=6y3*Wy3=+y3*Wy3*jykkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=Ay3*Wy3=3y");
    string_constant_142 = 
	    STATIC_STRING("kkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=Ay3*Wy3=7ykkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=Ny3*Wy3=5ykkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=Qy3*Wy3=3");
    string_constant_143 = 
	    STATIC_STRING("ykkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=by3*Wy3=Cykkkkkkkkkknok4o73Cy3*Wy3=by3*Wy3*py3*Wy3*Wykkkkkkkkkknqk4o73Cy3*Wy3*Wy3*Wy3*dykkkkkk");
    string_constant_144 = 
	    STATIC_STRING("kkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3*eykkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3*pykkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=4ykkkkkkkkkkk");
    string_constant_145 = 
	    STATIC_STRING("kmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=6ykkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=9ykkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*Wy3*Wy3=Aykkkkkkkkkkkkmn3R");
    string_constant_146 = 
	    STATIC_STRING("S+y4o73Cy3*Wy3*Wy3*Wy3=aykkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*hy3*Wy3=2ykkkkkkkkkkkkml3RS+y4o73Cy3*Wy3=+y3*Wy3*eykkkkkkkkkkkknmk4o73Cy");
    string_constant_147 = 
	    STATIC_STRING("3*Wy3=+y3*Wy3*nykkkkkkkkkkkknqk4o73Cy3*Wy3=+y3*Wy3*pykkkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3*uykkkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3*wyk");
    string_constant_148 = 
	    STATIC_STRING("kkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=4ykkkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=6ykkkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=9ykkkkkkkkkkkknmk4o7");
    string_constant_149 = 
	    STATIC_STRING("3Cy3*Wy3=+y3*Wy3=aykkkkkkkkkkkknmk4o73Cy3*Wy3=+y3*Wy3=hykkkkkkkkkkkknmk4o73Cy3*Wy3=3y3*Wy3*rykkkkkkkkkkkknqk4o73Cy3*Wy3=3y3*Wy3=");
    string_constant_150 = 
	    STATIC_STRING("Bykkkkkkkkkkkknlk4o73Cy3*Wy3=3y3*Wy3=Uykkkkkkkkkkkknlk4o73Cy3*Wy3=6y3*Wy3=Aykkkkkkkkkkkknnk4o73Cy3*Wy3=6y3*Wy3=bykkkkkkkkkkkknok");
    string_constant_151 = 
	    STATIC_STRING("4o73Cy3*Wy3*Wykkkkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3*hykkkkkkkkkkkkkkmm3RS+y4o73Cy3*Wy3=3ykkkkkkkkkkkkkknlk4o73Cy3*Wy3=6ykkkkkkkkkkkkk");
    string_constant_152 = STATIC_STRING("knmk4o73Cy3*Wy3=7ykkkkkkkkkkkkkknlk");
    SET_SYMBOL_VALUE(Qkfep_keiyo_array,
	    regenerate_optimized_constant(list(25,string_constant_128,
	    string_constant_129,string_constant_130,string_constant_131,
	    string_constant_132,string_constant_133,string_constant_134,
	    string_constant_135,string_constant_136,string_constant_137,
	    string_constant_138,string_constant_139,string_constant_140,
	    string_constant_141,string_constant_142,string_constant_143,
	    string_constant_144,string_constant_145,string_constant_146,
	    string_constant_147,string_constant_148,string_constant_149,
	    string_constant_150,string_constant_151,string_constant_152)));
    Qkfep_taigen_array = STATIC_SYMBOL("KFEP-TAIGEN-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_taigen_array,Kfep_taigen_array);
    string_constant_153 = 
	    STATIC_STRING("43Yy4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2y3*Wy3=Uykkkkkkkkkr32++++y4o73Cy3*Wy3=+y3*Wy3==y3*Wy3=2ykkkkkkkkkkkr32++++y4o73Cy3*Wy3=by3*Wy3*");
    string_constant_154 = 
	    STATIC_STRING("py3*Wy3*Wykkkkkkkkkklr32++++y4o73Cy3*Wy3=Cy3*Wy3*dy3*Wy3=cykkkkkkkkkkkr32++++y4o73Cy3*Wy3*hy3*Wy3=by3*Wy3*Wykkkkkkkkkkkr32++++y4");
    string_constant_155 = 
	    STATIC_STRING("o73Cy3*Wy3*ey3*Wy3=bykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*ly3*Wy3*vykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*ny3*Wy3*aykkkkkkkkkkkkkr32++++y");
    string_constant_156 = 
	    STATIC_STRING("4o73Cy3*Wy3=3y3*Wy3*rykkkkkkkkkkkklr32++++y4o73Cy3*Wy3=3y3*Wy3=Uykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*py3*Wy3*dykkkkkkkkkkkkkr32++++");
    string_constant_157 = 
	    STATIC_STRING("y4o73Cy3*Wy3=Ny3*Wy3*dykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Qy3*Wy3=3ykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=+y3*Wy3*jykkkkkkkkkkkkkr32+++");
    string_constant_158 = 
	    STATIC_STRING("+y4o73Cy3*Wy3=Ny3*Wy3=5ykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*sy3*Wy3=0ykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*fy3*Wy3=cykkkkkkkkkkkkkr32++");
    string_constant_159 = 
	    STATIC_STRING("++y4o73Cy3*Wy3=6y3*Wy3=5ykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Wy3*Wy3=bykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=9y3*Wy3*aykkkkkkkkkkkkkr32+");
    string_constant_160 = 
	    STATIC_STRING("+++y4o73Cy3*Wy3=+y3*Wy3=Aykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3*dy3*Wy3=bykkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=ay3*Wy3=cykkkkkkkkkkkkkr32");
    string_constant_161 = 
	    STATIC_STRING("++++y4o73Cy3*Wy3*eykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Aykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=kykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=");
    string_constant_162 = 
	    STATIC_STRING("7ykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Kykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=+ykkkkkkkkkkkkkklr32++++y4o73Cy3*Wy3=4ykkkkkkkkkkkkkkk");
    string_constant_163 = 
	    STATIC_STRING("r32++++y4o73Cy3*Wy3=3ykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Wykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Bykkkkkkkkkkkkkkkr32++++y4o73Cy3*W");
    string_constant_164 = 
	    STATIC_STRING("y3*dykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=aykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=9ykkkkkkkkkkkkkkkr32++++y4o73Cy3*Wy3=Uykkkkkkkkkkkk");
    string_constant_165 = 
	    STATIC_STRING("kkkr32++++y4o73Cy3*Wy3*nykkkkkkkkkkkkkkkr32++++y");
    SET_SYMBOL_VALUE(Qkfep_taigen_array,
	    regenerate_optimized_constant(list(13,string_constant_153,
	    string_constant_154,string_constant_155,string_constant_156,
	    string_constant_157,string_constant_158,string_constant_159,
	    string_constant_160,string_constant_161,string_constant_162,
	    string_constant_163,string_constant_164,string_constant_165)));
    Qkfep_sahen_array = STATIC_SYMBOL("KFEP-SAHEN-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_sahen_array,Kfep_sahen_array);
    string_constant_166 = 
	    STATIC_STRING("43Cy4o7s3*Wy3*ny3*Wy3*ty3*Wy3=6y3*Wy3*Wykr30+++4y4o7s3*Wy3*ny3*Wy3*ty3*Wy3=ay3*Wy3*Yykr30+++4y4o7s3*Wy3*ry3*Wy3=dy3*Wy3=4y3*Wy3*");
    string_constant_167 = 
	    STATIC_STRING("fykr30+++4y4o7s3*Wy3*py3*Wy3=Qy3*Wy3*py3*Wy3*xykr30+++4y4o7s3*Wy3*py3*Wy3=Qy3*Wy3*rykkkr30+++4y4o7s3*Wy3*py3*Wy3=ay3*Wy3*Yykklr3");
    string_constant_168 = 
	    STATIC_STRING("0+++4y4o7s3*Wy3*ry3*Wy3=ey3*Wy3=Cykklr30+++4y4o7s3*Wy3*py3*Wy3=6y3*Wy3*Wykkkr30+++4y4o7s3*Wy3*py3*Wy3=2y3*Wy3*xykkkr30+++4y4o7s3");
    string_constant_169 = 
	    STATIC_STRING("*Wy3*py3*Wy3=2ykkkkkr30+++4y4o7s3*Wy3*py3*Wy3*xykkkkkr30+++4y4o7s3*Wy3*ry3*Wy3=dykkkkkr30+++4y4o7s3*Wy3*py3*Wy3=fykkkkkr30+++4y4");
    string_constant_170 = 
	    STATIC_STRING("o7s3*Wy3*ty3*Wy3=aykkkkkr30+++4y4o7s3*Wy3*pykkkkkkkr30+++4y4o7skkkkkkkkkkk");
    SET_SYMBOL_VALUE(Qkfep_sahen_array,
	    regenerate_optimized_constant(LIST_5(string_constant_166,
	    string_constant_167,string_constant_168,string_constant_169,
	    string_constant_170)));
    string_constant = STATIC_STRING("$H");
    string_constant_1 = STATIC_STRING("$\?$k");
    Qkfep_filename = STATIC_SYMBOL("KFEP-FILENAME",AB_package);
    string_constant_2 = STATIC_STRING("Error (#~d) opening ~s for input: ~s");
    Qspecified_kfep_index_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-INDEX-FILENAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspecified_kfep_index_filename_qm,
	    Specified_kfep_index_filename_qm);
    record_system_variable(Qspecified_kfep_index_filename_qm,Qkfep1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qspecified_kfep_main_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-MAIN-FILENAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspecified_kfep_main_filename_qm,
	    Specified_kfep_main_filename_qm);
    record_system_variable(Qspecified_kfep_main_filename_qm,Qkfep1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qspecified_kfep_kojin_filename_qm = 
	    STATIC_SYMBOL("SPECIFIED-KFEP-KOJIN-FILENAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspecified_kfep_kojin_filename_qm,
	    Specified_kfep_kojin_filename_qm);
    record_system_variable(Qspecified_kfep_kojin_filename_qm,Qkfep1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    string_constant_171 = STATIC_STRING("index.dic");
    Kfep_index_filename = string_constant_171;
    string_constant_172 = STATIC_STRING("main.dic");
    Kfep_main_filename = string_constant_172;
    string_constant_173 = STATIC_STRING("kojin.dic");
    Kfep_kojin_filename = string_constant_173;
    string_constant_3 = STATIC_STRING("                        ");
    Qkfep_ghyoki_idxbuf = STATIC_SYMBOL("KFEP-GHYOKI-IDXBUF",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_ghyoki_idxbuf,Kfep_ghyoki_idxbuf);
    record_system_variable(Qkfep_ghyoki_idxbuf,Qkfep1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qkfep_ghyoki_hptr = STATIC_SYMBOL("KFEP-GHYOKI-HPTR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_ghyoki_hptr,Kfep_ghyoki_hptr);
    record_system_variable(Qkfep_ghyoki_hptr,Qkfep1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qkfep_ghyoki_savtblnum = STATIC_SYMBOL("KFEP-GHYOKI-SAVTBLNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_ghyoki_savtblnum,Kfep_ghyoki_savtblnum);
    record_system_variable(Qkfep_ghyoki_savtblnum,Qkfep1,FIX((SI_Long)-1L),
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_ghyoki_idxbuf_cache_alist = 
	    STATIC_SYMBOL("KFEP-GHYOKI-IDXBUF-CACHE-ALIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_ghyoki_idxbuf_cache_alist,
	    Kfep_ghyoki_idxbuf_cache_alist);
    record_system_variable(Qkfep_ghyoki_idxbuf_cache_alist,Qkfep1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qmaximum_kojin_entry_subvector_length = 
	    STATIC_SYMBOL("MAXIMUM-KOJIN-ENTRY-SUBVECTOR-LENGTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_kojin_entry_subvector_length,
	    Maximum_kojin_entry_subvector_length);
    SET_SYMBOL_VALUE(Qmaximum_kojin_entry_subvector_length,
	    FIXNUM_SUB1(Maximum_byte_vector_length));
    Qmost_positive_fixnum_ash_minus_24 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-ASH-MINUS-24",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_ash_minus_24,
	    Most_positive_fixnum_ash_minus_24);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_ash_minus_24,
	    FIX(IFIX(Most_positive_fixnum) >>  -  - (SI_Long)24L));
    Qkfep_hensaisyo_getpos = STATIC_SYMBOL("KFEP-HENSAISYO-GETPOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_hensaisyo_getpos,Kfep_hensaisyo_getpos);
    record_system_variable(Qkfep_hensaisyo_getpos,Qkfep1,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_hensaisyo_tno = STATIC_SYMBOL("KFEP-HENSAISYO-TNO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_hensaisyo_tno,Kfep_hensaisyo_tno);
    record_system_variable(Qkfep_hensaisyo_tno,Qkfep1,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_hensaisyo_gonum = STATIC_SYMBOL("KFEP-HENSAISYO-GONUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_hensaisyo_gonum,Kfep_hensaisyo_gonum);
    record_system_variable(Qkfep_hensaisyo_gonum,Qkfep1,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qkfep_hensaisyo_saventry = STATIC_SYMBOL("KFEP-HENSAISYO-SAVENTRY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_hensaisyo_saventry,
	    Kfep_hensaisyo_saventry);
    record_system_variable(Qkfep_hensaisyo_saventry,Qkfep1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qkfep_kka_p_batkanakan_position = 
	    STATIC_SYMBOL("KFEP-KKA-P-BATKANAKAN-POSITION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkfep_kka_p_batkanakan_position,
	    Kfep_kka_p_batkanakan_position);
    record_system_variable(Qkfep_kka_p_batkanakan_position,Qkfep1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
}
