/* f-keys.c
 * Input file:  f-keys.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "f-keys.h"


static Object Qany;                /* any */

static Object Qmouse_down;         /* mouse-down */

static Object Qleft;               /* left */

static Object Qmouse_left_down;    /* mouse-left-down */

static Object Qmiddle;             /* middle */

static Object Qmouse_middle_down;  /* mouse-middle-down */

static Object Qright;              /* right */

static Object Qmouse_right_down;   /* mouse-right-down */

static Object Qkey_code_for_key_symbol;  /* key-code-for-key-symbol */

/* CONVERT-KEY-SYMBOL-TO-KEY-CODE */
Object convert_key_symbol_to_key_code varargs_1(int, n)
{
    Object key_symbol_1;
    Object is_mouse_button_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(35,0);
    INIT_ARGS_nonrelocating();
    key_symbol_1 = REQUIRED_ARG_nonrelocating();
    is_mouse_button_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (is_mouse_button_qm) {
	if (EQ(key_symbol_1,Qany))
	    key_symbol_1 = Qmouse_down;
	else if (EQ(key_symbol_1,Qleft))
	    key_symbol_1 = Qmouse_left_down;
	else if (EQ(key_symbol_1,Qmiddle))
	    key_symbol_1 = Qmouse_middle_down;
	else if (EQ(key_symbol_1,Qright))
	    key_symbol_1 = Qmouse_right_down;
    }
    if (EQ(SYMBOL_PACKAGE(key_symbol_1),Keyword_package_1))
	key_symbol_1 = intern(SYMBOL_NAME(key_symbol_1),Ab_package_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(key_symbol_1),
	    Qkey_code_for_key_symbol);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Illegal_key_code);
}

/* CANONICALIZE-GENSYM-KEY-CODE */
Object canonicalize_gensym_key_code(key_code)
    Object key_code;
{
    Object unicode, key_code_1;
    SI_Long arg, arg_1, arg_2, space, temp_1;
    char temp;

    x_note_fn_call(35,1);
    if (IFIX(key_code) == (SI_Long)16777248L)
	return VALUES_1(FIX((SI_Long)32L));
    else if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L)
	return VALUES_1(key_code);
    else {
	arg = (SI_Long)65L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)90L;
	if ((arg <= arg_1 && arg_1 <= arg_2 ? IFIX(FIXNUM_LOGAND(key_code,
		Caps_lock_bit)) != (SI_Long)0L : TRUEP(Nil)) ? 
		IFIX(FIXNUM_LOGAND(key_code,Control_bit)) != (SI_Long)0L 
		|| IFIX(FIXNUM_LOGAND(key_code,Meta_bit)) != (SI_Long)0L 
		|| IFIX(FIXNUM_LOGAND(key_code,Alternate_bit)) != 
		(SI_Long)0L : TRUEP(Nil))
	    key_code = FIX(IFIX(key_code) ^ (SI_Long)32L);
	key_code = FIXNUM_LOGAND(key_code,FIXNUM_LOGNOT(Caps_lock_bit));
	if (IFIX(FIXNUM_LOGAND(key_code,Shift_bit)) != (SI_Long)0L) {
	    arg = (SI_Long)97L;
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? IFIX(unicode) : 
			IFIX(Illegal_key_index);
	    }
	    else
		arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	    arg_2 = (SI_Long)122L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    arg = (SI_Long)97L;
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? IFIX(unicode) : 
			IFIX(Illegal_key_index);
	    }
	    else
		arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	    arg_2 = (SI_Long)122L;
	    key_code = arg <= arg_1 && arg_1 <= arg_2 ? FIX(IFIX(key_code) 
		    ^ (SI_Long)32L) : key_code;
	}
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    key_code_1 = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    key_code_1 = FIXNUM_LOGAND(Key_index_bits,key_code);
	if (printable_character_key_code_p(key_code_1) &&  
		!((IFIX(FIXNUM_LOGAND(key_code_1,Unicode_bit)) != 
		(SI_Long)0L ? IFIX(FIXNUM_LOGAND(Unicode_character_bits,
		key_code_1)) : IFIX(key_code_1)) == (SI_Long)32L))
	    key_code = FIXNUM_LOGAND(key_code,FIXNUM_LOGNOT(Shift_bit));
	space = (SI_Long)32L;
	if (FIXNUM_EQ(FIXNUM_LOGAND(Key_modifier_bits,key_code),Shift_bit)) {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		temp_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? IFIX(unicode) : 
			IFIX(Illegal_key_index);
	    }
	    else
		temp_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	    temp = temp_1 == space;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    key_code = FIX(space);
	if (IFIX(FIXNUM_LOGAND(key_code,Control_bit)) != (SI_Long)0L) {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		key_code_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		key_code_1 = FIXNUM_LOGAND(Key_index_bits,key_code);
	    arg = (SI_Long)97L;
	    if (IFIX(FIXNUM_LOGAND(key_code_1,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code_1);
		arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? IFIX(unicode) : 
			IFIX(Illegal_key_index);
	    }
	    else
		arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code_1));
	    arg_2 = (SI_Long)122L;
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    if (temp);
	    else
		temp = IFIX(key_code_1) == (SI_Long)64L;
	    if (temp);
	    else
		temp = (SI_Long)91L <= IFIX(key_code_1) ? IFIX(key_code_1) 
			<= (SI_Long)95L : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    key_code = FIX(IFIX(FIXNUM_LOGAND(key_code,
		    FIXNUM_LOGNOT(Control_bit))) &  ~(IFIX(Key_index_bits) 
		    ^ (SI_Long)31L));
	return VALUES_1(key_code);
    }
}

static Object Qcontrol;            /* control */

static Object Qshift;              /* shift */

static Object Qalternate;          /* alternate */

static Object Qalt;                /* alt */

static Object Qmeta;               /* meta */

static Object Qdouble;             /* double */

/* KEY-CODE-FUNCTION */
Object key_code_function(key_spec,mouse_qm,invert_symbol_letter_case_qm)
    Object key_spec, mouse_qm, invert_symbol_letter_case_qm;
{
    Object key_code, unicode, modifier_bits, token, ab_loop_list_;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(35,2);
    if (SYMBOLP(key_spec)) {
	key_code = convert_key_symbol_to_key_code(1,key_spec);
	if (FIXNUM_EQ(Illegal_key_code,key_code))
	    return VALUES_1(key_code);
	else {
	    if (invert_symbol_letter_case_qm) {
		arg = (SI_Long)65L;
		if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
			    FIX((SI_Long)127L)) ? IFIX(unicode) : 
			    IFIX(Illegal_key_index);
		}
		else
		    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
		arg_2 = (SI_Long)90L;
		temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		if (temp);
		else {
		    arg = (SI_Long)97L;
		    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != 
			    (SI_Long)0L) {
			unicode = FIXNUM_LOGAND(Unicode_character_bits,
				key_code);
			arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
				FIX((SI_Long)127L)) ? IFIX(unicode) : 
				IFIX(Illegal_key_index);
		    }
		    else
			arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
		    arg_2 = (SI_Long)122L;
		    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(FIX(IFIX(key_code) ^ (SI_Long)32L));
	    else
		return VALUES_1(key_code);
	}
    }
    else if (STRINGP(key_spec))
	return convert_key_symbol_to_key_code(1,intern(key_spec,_));
    else if (text_string_p(key_spec))
	return convert_key_symbol_to_key_code(1,intern_text_string(1,
		key_spec));
    else if (CHARACTERP(key_spec))
	return key_code_from_character(key_spec);
    else if (FIXNUMP(key_spec))
	return VALUES_1(key_spec);
    else if (ATOM(key_spec))
	return VALUES_1(Illegal_key_code);
    else {
	key_code = Illegal_key_code;
	modifier_bits = FIX((SI_Long)0L);
	token = Nil;
	ab_loop_list_ = key_spec;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	token = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(token,Qcontrol))
	    modifier_bits = FIXNUM_LOGIOR(modifier_bits,Control_bit);
	else if (EQ(token,Qshift))
	    modifier_bits = FIXNUM_LOGIOR(modifier_bits,Shift_bit);
	else if (EQ(token,Qalternate) || EQ(token,Qalt))
	    modifier_bits = FIXNUM_LOGIOR(modifier_bits,Alternate_bit);
	else if (EQ(token,Qmeta))
	    modifier_bits = FIXNUM_LOGIOR(modifier_bits,Meta_bit);
	else if (EQ(token,Qdouble))
	    modifier_bits = FIXNUM_LOGIOR(modifier_bits,Double_bit);
	else
	    key_code = key_code_function(token,Nil,
		    invert_symbol_letter_case_qm);
	goto next_loop;
      end_loop:;
	if (FIXNUM_EQ(Illegal_key_code,key_code))
	    return VALUES_1(key_code);
	else
	    return canonicalize_gensym_key_code(FIXNUM_LOGIOR(key_code,
		    modifier_bits));
    }
}

/* KEY-CODE-FROM-LIST */
Object key_code_from_list(key_spec)
    Object key_spec;
{
    x_note_fn_call(35,3);
    if (SYMBOLP(key_spec))
	return key_code_from_symbol(key_spec);
    else if (text_string_p(key_spec))
	return key_code_from_symbol(intern_text_string(1,
		string_upcasew(key_spec)));
    else if (ATOM(key_spec))
	return VALUES_1(Illegal_key_code);
    else
	return key_code_function(key_spec,Nil,T);
}

/* KEY-CODE-FROM-SYMBOL */
Object key_code_from_symbol(symbol)
    Object symbol;
{
    Object symbols, key_spec, temp;

    x_note_fn_call(35,4);
    symbols = split_symbol(symbol,CHR('+'));
    key_spec = CONSP(symbols) &&  !TRUEP(CDR(symbols)) ? FIRST(symbols) : 
	    symbols;
    temp = key_code_function(key_spec,Nil,T);
    reclaim_gensym_list_1(symbols);
    return VALUES_1(temp);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* SYMBOL-FROM-KEY-CODE */
Object symbol_from_key_code(key_code)
    Object key_code;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(35,5);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_key_code(key_code);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return intern_text_string(1,nstring_upcasew(temp));
}

/* PARSEABLE-SYMBOL-FROM-KEY-CODE */
Object parseable_symbol_from_key_code(key_code)
    Object key_code;
{
    Object write_symbols_parsably_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(35,6);
    write_symbols_parsably_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
	    5);
      current_wide_string_list = Qdo_not_use;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	      4);
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	current_wide_string = wide_string_bv16;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		3);
	  fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		  2);
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	    total_length_of_current_wide_string = 
		    FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		twrite_key_code(key_code);
		temp = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      result = intern_text_string(1,nstring_upcasew(temp));
    POP_SPECIAL();
    return result;
}

Object Characters_requiring_quotation_in_key_symbols = UNBOUND;

static Object Qfor_filters;        /* for-filters */

/* TWRITE-CHARACTER-OF-KEYSYM */
Object twrite_character_of_keysym(char_1,first_char_qm,case_1)
    Object char_1, first_char_qm, case_1;
{
    Object code, pretty_char, temp_1, temp_2, temp_3, schar_arg_2;
    Object schar_new_value, thing_1;
    SI_Long gensymed_symbol, code_1, thing;
    char temp;

    x_note_fn_call(35,7);
    if (EQ(case_1,Kdowncase)) {
	code = char_1;
	if (IFIX(code) < (SI_Long)127L)
	    pretty_char = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    pretty_char = unicode_lowercase_if_uppercase(code);
	    if (pretty_char);
	    else
		pretty_char = code;
	}
    }
    else if (EQ(case_1,Kupcase)) {
	code = char_1;
	if (IFIX(code) < (SI_Long)127L)
	    pretty_char = (SI_Long)97L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)122L ? FIX(IFIX(code) + (SI_Long)-32L) : code;
	else {
	    pretty_char = unicode_uppercase_if_lowercase(code);
	    if (pretty_char);
	    else
		pretty_char = code;
	}
    }
    else if (EQ(case_1,Kcapitalize)) {
	if (first_char_qm) {
	    code = char_1;
	    if (IFIX(code) < (SI_Long)127L)
		pretty_char = (SI_Long)97L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)122L ? FIX(IFIX(code) + (SI_Long)-32L) : code;
	    else {
		pretty_char = unicode_uppercase_if_lowercase(code);
		if (pretty_char);
		else
		    pretty_char = code;
	    }
	}
	else {
	    code = char_1;
	    if (IFIX(code) < (SI_Long)127L)
		pretty_char = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		pretty_char = unicode_lowercase_if_uppercase(code);
		if (pretty_char);
		else
		    pretty_char = code;
	    }
	}
    }
    else
	pretty_char = char_1;
    if ( !TRUEP(Write_symbols_parsably_qm));
    else {
	if (EQ(Write_symbols_parsably_qm,Qfor_filters)) {
	    temp = TRUEP(find_in_text_string(char_1,
		    Characters_requiring_quotation_in_key_symbols));
	    if (temp);
	    else if (first_char_qm) {
		gensymed_symbol = IFIX(char_1);
		temp = (SI_Long)48L <= gensymed_symbol && gensymed_symbol 
			<= (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
			(SI_Long)48L)) : TRUEP(Nil);
		if (temp);
		else {
		    code = char_1;
		    if (IFIX(code) < (SI_Long)127L)
			temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) 
				<= (SI_Long)90L ? FIX(IFIX(code) + 
				(SI_Long)32L) : code;
		    else {
			temp_1 = unicode_lowercase_if_uppercase(code);
			if (temp_1);
			else
			    temp_1 = code;
		    }
		    code_1 = (SI_Long)45L;
		    if (code_1 < (SI_Long)127L)
			temp_2 = (SI_Long)65L <= code_1 && code_1 <= 
				(SI_Long)90L ? FIX(code_1 + (SI_Long)32L) :
				 FIX(code_1);
		    else {
			temp_2 = unicode_lowercase_if_uppercase(FIX(code_1));
			if (temp_2);
			else
			    temp_2 = FIX(code_1);
		    }
		    temp = NUM_EQ(temp_1,temp_2);
		}
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = (SI_Long)64L;
		twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = (SI_Long)64L;
		schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			CHAR_CODE(FIX(thing)) : FIX(thing));
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	}
    }
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing_1 = pretty_char;
	return twrite_wide_character(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp_3 = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing_1 = pretty_char;
	schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		CHAR_CODE(thing_1) : thing_1);
	SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp_3;
	return VALUES_1(Fill_pointer_for_current_gensym_string);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Twrite_control_as_ctrl, Qtwrite_control_as_ctrl);

static Object array_constant;      /* # */

static Object string_constant;     /* "Ctrl+" */

static Object string_constant_1;   /* "ctrl+" */

static Object string_constant_2;   /* "Control+" */

static Object string_constant_3;   /* "control+" */

static Object string_constant_4;   /* "Alt+" */

static Object string_constant_5;   /* "alt+" */

static Object string_constant_6;   /* "Shift+" */

static Object string_constant_7;   /* "shift+" */

/* TWRITE-KEY-MODIFIER-BITS */
Object twrite_key_modifier_bits(key_code,capitalize_qm)
    Object key_code, capitalize_qm;
{
    Object unicode;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(35,8);
    if (IFIX(FIXNUM_LOGAND(key_code,Double_bit)) != (SI_Long)0L)
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)7L));
    temp = IFIX(FIXNUM_LOGAND(key_code,Control_bit)) != (SI_Long)0L;
    if (temp);
    else {
	arg = (SI_Long)0L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)31L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    if (temp)
	twrite_general_string(Twrite_control_as_ctrl ? (capitalize_qm ? 
		string_constant : string_constant_1) : capitalize_qm ? 
		string_constant_2 : string_constant_3);
    if (IFIX(FIXNUM_LOGAND(key_code,Alternate_bit)) != (SI_Long)0L)
	twrite_general_string(capitalize_qm ? string_constant_4 : 
		string_constant_5);
    if (IFIX(FIXNUM_LOGAND(key_code,Shift_bit)) != (SI_Long)0L)
	twrite_general_string(capitalize_qm ? string_constant_6 : 
		string_constant_7);
    return VALUES_1(key_code);
}

static Object array_constant_1;    /* # */

/* TWRITE-KEY-CODE */
Object twrite_key_code(key_code)
    Object key_code;
{
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;
    Object unicode, key_symbol_qm, string_1, char_2;
    SI_Long arg, arg_1, arg_2, char_1, ab_loop_bind_, i;

    x_note_fn_call(35,9);
    if ( !FIXNUMP(key_code))
	return twrite(key_code);
    else if (FIXNUM_EQ(Illegal_key_code,key_code))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)11L));
    else if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	simple_or_wide_character = FIXNUM_LOGAND(Unicode_character_bits,
		key_code);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    return twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else {
	arg = (SI_Long)65L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)90L;
	if (arg <= arg_1 && arg_1 <= arg_2)
	    key_code = FIX(IFIX(key_code) ^ (SI_Long)32L | IFIX(Shift_bit));
	key_symbol_qm = convert_key_code_to_key_symbol(key_code);
	if ( !TRUEP(key_symbol_qm))
	    return twrite_beginning_of_wide_string(array_constant_1,
		    FIX((SI_Long)11L));
	else {
	    twrite_key_modifier_bits(key_code,T);
	    arg = (SI_Long)0L;
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? IFIX(unicode) : 
			IFIX(Illegal_key_index);
	    }
	    else
		arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	    arg_2 = (SI_Long)31L;
	    if (arg <= arg_1 && arg_1 <= arg_2) {
		string_1 = symbol_name_text_string(key_symbol_qm);
		char_1 = UBYTE_16_ISAREF_1(string_1,
			IFIX(FIXNUM_SUB1(lengthw(string_1))));
		return twrite_character_of_keysym(FIX(char_1),T,Kcapitalize);
	    }
	    else {
		string_1 = symbol_name_text_string(key_symbol_qm);
		ab_loop_bind_ = IFIX(lengthw(string_1));
		i = (SI_Long)0L;
		char_2 = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		char_2 = FIX(UBYTE_16_ISAREF_1(string_1,i));
		twrite_character_of_keysym(char_2,i == (SI_Long)0L ? T : 
			Nil,Kcapitalize);
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	}
    }
}

Object Key_pattern_named_prop = UNBOUND;

Object Key_pattern_abbreviation_prop = UNBOUND;

static Object Qkey_pattern_named;  /* key-pattern-named */

static Object Qab_or;              /* or */

/* KEY-CODE-MATCHES-KEY-PATTERN-P-FUNCTION */
Object key_code_matches_key_pattern_p_function(key_code,key_pattern)
    Object key_code, key_pattern;
{
    Object gensymed_symbol, gensymed_symbol_1, disjunct, ab_loop_list_;
    Object ab_loop_it_;

    x_note_fn_call(35,10);
    if (FIXNUMP(key_pattern))
	return VALUES_1(FIXNUM_EQ(key_pattern,key_code) ? T : Nil);
    else if (SYMBOLP(key_pattern)) {
	gensymed_symbol = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(key_pattern),
		Qkey_pattern_named);
	gensymed_symbol_1 = key_code;
	return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    else if (CONSP(key_pattern) && FIXNUMP(CAR(key_pattern)))
	return VALUES_1(FIXNUM_EQ(FIXNUM_LOGAND(key_code,CDR(key_pattern)),
		CAR(key_pattern)) ? T : Nil);
    else if (CONSP(key_pattern) && EQ(FIRST(key_pattern),Qab_or)) {
	disjunct = Nil;
	ab_loop_list_ = REST(key_pattern);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	disjunct = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = key_code_matches_key_pattern_p_function(key_code,
		disjunct);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* OTHERWISE-KEY-PATTERN */
Object otherwise_key_pattern(key_code)
    Object key_code;
{
    x_note_fn_call(35,11);
    return VALUES_1(T);
}

/* <PSEUDO-KEYCODE>-KEY-PATTERN */
Object lt_pseudo_keycode_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,12);
    temp = pseudo_key_code_p(key_code);
    return VALUES_1(temp);
}

/* <PRINTING-CHARACTER>-KEY-PATTERN */
Object lt_printing_character_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,13);
    temp = printable_character_key_code_p(key_code);
    return VALUES_1(temp);
}

/* <UNICODE-CHARACTER>-KEY-PATTERN */
Object lt_unicode_character_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,14);
    temp = IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* <ALPHABETIC>-KEY-PATTERN */
Object lt_alphabetic_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(35,15);
    arg = (SI_Long)65L;
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    arg_2 = (SI_Long)90L;
    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    if (temp);
    else {
	arg = (SI_Long)97L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)122L;
	temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* <ANY-KEYBOARD-EVENT>-KEY-PATTERN */
Object lt_any_keyboard_event_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, gensymed_symbol, temp_1;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(35,16);
    arg = (SI_Long)769L;
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    arg_2 = (SI_Long)779L;
    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    if (temp);
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	temp = IFIX(gensymed_symbol) == (SI_Long)779L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)812L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)813L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)814L;
    }
    if (temp);
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	temp = IFIX(gensymed_symbol) == (SI_Long)778L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)815L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)816L;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)817L;
    }
    temp_1 =  !temp ? ( !TRUEP(pseudo_key_code_p(key_code)) ? T : Nil) : Nil;
    return VALUES_1(temp_1);
}

/* <MOUSE-GESTURE>-KEY-PATTERN */
Object lt_mouse_gesture_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp, gensymed_symbol;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(35,17);
    arg = (SI_Long)769L;
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    arg_2 = (SI_Long)779L;
    temp = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    if (temp);
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	temp = IFIX(gensymed_symbol) == (SI_Long)779L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)812L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)813L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)814L ? T : Nil;
    }
    if (temp);
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	temp = IFIX(gensymed_symbol) == (SI_Long)778L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)815L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)816L ? T : Nil;
	if (temp);
	else
	    temp = IFIX(gensymed_symbol) == (SI_Long)817L ? T : Nil;
    }
    return VALUES_1(temp);
}

/* <MOUSE-UP>-KEY-PATTERN */
Object lt_mouse_up_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp, temp_1;

    x_note_fn_call(35,18);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp_1 = EQ(temp,FIX((SI_Long)769L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)773L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)775L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)777L)) ? T : Nil;
    return VALUES_1(temp_1);
}

/* <MOUSE-DOWN>-KEY-PATTERN */
Object lt_mouse_down_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp, temp_1;

    x_note_fn_call(35,19);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp_1 = EQ(temp,FIX((SI_Long)770L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)772L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)774L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)776L)) ? T : Nil;
    return VALUES_1(temp_1);
}

/* <MOUSE-LEFT-DOWN>-KEY-PATTERN */
Object lt_mouse_left_down_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp, temp_1;

    x_note_fn_call(35,20);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp_1 = EQ(temp,FIX((SI_Long)770L)) ? T : Nil;
    if (temp_1);
    else
	temp_1 = EQ(temp,FIX((SI_Long)772L)) ? T : Nil;
    return VALUES_1(temp_1);
}

/* <MOUSE-MIDDLE-DOWN>-KEY-PATTERN */
Object lt_mouse_middle_down_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,21);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = EQ(temp,FIX((SI_Long)774L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-RIGHT-DOWN>-KEY-PATTERN */
Object lt_mouse_right_down_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,22);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = EQ(temp,FIX((SI_Long)776L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-MOTION>-KEY-PATTERN */
Object lt_mouse_motion_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode;
    SI_Long temp;

    x_note_fn_call(35,23);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	temp = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    return VALUES_1(temp == (SI_Long)771L ? T : Nil);
}

/* <MOUSE-HOVER>-KEY-PATTERN */
Object lt_mouse_hover_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode;
    SI_Long temp;

    x_note_fn_call(35,24);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	temp = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    return VALUES_1(temp == (SI_Long)782L ? T : Nil);
}

/* <MOUSE-DRAG>-KEY-PATTERN */
Object lt_mouse_drag_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, gensymed_symbol, temp;

    x_note_fn_call(35,25);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
    }
    else
	gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = IFIX(gensymed_symbol) == (SI_Long)778L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)815L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)816L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)817L ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-SELECT>-KEY-PATTERN */
Object lt_mouse_select_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, gensymed_symbol, temp;

    x_note_fn_call(35,26);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
    }
    else
	gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = IFIX(gensymed_symbol) == (SI_Long)779L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)812L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)813L ? T : Nil;
    if (temp);
    else
	temp = IFIX(gensymed_symbol) == (SI_Long)814L ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-LEFT-SELECT>-KEY-PATTERN */
Object lt_mouse_left_select_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,27);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = FIXNUM_EQ(temp,FIX((SI_Long)812L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-MIDDLE-SELECT>-KEY-PATTERN */
Object lt_mouse_middle_select_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,28);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = FIXNUM_EQ(temp,FIX((SI_Long)813L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-RIGHT-SELECT>-KEY-PATTERN */
Object lt_mouse_right_select_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,29);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = FIXNUM_EQ(temp,FIX((SI_Long)814L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-LEFT-DRAG>-KEY-PATTERN */
Object lt_mouse_left_drag_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,30);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = FIXNUM_EQ(temp,FIX((SI_Long)815L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <MOUSE-RIGHT-DRAG>-KEY-PATTERN */
Object lt_mouse_right_drag_gt_key_pattern(key_code)
    Object key_code;
{
    Object unicode, temp;

    x_note_fn_call(35,31);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	temp = FIXNUM_LOGAND(Key_index_bits,key_code);
    temp = FIXNUM_EQ(temp,FIX((SI_Long)817L)) ? T : Nil;
    return VALUES_1(temp);
}

/* <NATIVE-MENU-CHOICE>-KEY-PATTERN */
Object lt_native_menu_choice_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,32);
    temp = IFIX(FIXNUM_LOGAND(Menu_bit,key_code)) != (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

/* <STANDARD-NEWLINE-KEYS>-KEY-PATTERN */
Object lt_standard_newline_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,33);
    temp = IFIX(key_code) == (SI_Long)280L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)394L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)10L ? T : Nil;
    return VALUES_1(temp);
}

/* <STANDARD-HELP-KEYS>-KEY-PATTERN */
Object lt_standard_help_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,34);
    temp = IFIX(key_code) == (SI_Long)8388671L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)390L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)8388655L ? T : Nil;
    return VALUES_1(temp);
}

/* <STANDARD-ENTER-KEYS>-KEY-PATTERN */
Object lt_standard_enter_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,35);
    temp = IFIX(key_code) == (SI_Long)660L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)281L ? T : Nil;
    return VALUES_1(temp);
}

/* <DELETE-BACKWARD-KEYS>-KEY-PATTERN */
Object lt_delete_backward_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,36);
    temp = IFIX(key_code) == (SI_Long)278L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)262422L ? T : Nil;
    return VALUES_1(temp);
}

/* <DELETE-FORWARD-KEYS>-KEY-PATTERN */
Object lt_delete_forward_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,37);
    temp = IFIX(key_code) == (SI_Long)127L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)262271L ? T : Nil;
    return VALUES_1(temp);
}

/* <STANDARD-ABORT-KEYS>-KEY-PATTERN */
Object lt_standard_abort_keys_gt_key_pattern(key_code)
    Object key_code;
{
    Object temp;

    x_note_fn_call(35,38);
    temp = IFIX(key_code) == (SI_Long)401L ? T : Nil;
    if (temp);
    else
	temp = IFIX(key_code) == (SI_Long)1L ? T : Nil;
    return VALUES_1(temp);
}

static Object Qkey_pattern_abbreviation;  /* key-pattern-abbreviation */

static Object string_constant_8;   /* "any+" */

static Object string_constant_9;   /* "[0~o,0~o]" */

/* TWRITE-KEY-PATTERN */
Object twrite_key_pattern(key_pattern)
    Object key_pattern;
{
    Object abbreviation_qm, value, mask;

    x_note_fn_call(35,39);
    if (FIXNUMP(key_pattern))
	return twrite_key_code(key_pattern);
    else if (SYMBOLP(key_pattern)) {
	abbreviation_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(key_pattern),
		Qkey_pattern_abbreviation);
	if (abbreviation_qm)
	    return twrite_key_pattern(abbreviation_qm);
	else
	    return twrite_symbol(1,key_pattern);
    }
    else if (CONSP(key_pattern) && FIXNUMP(CAR(key_pattern))) {
	value = CAR(key_pattern);
	mask = CDR(key_pattern);
	if (FIXNUM_EQ(mask,Key_index_bits)) {
	    tformat(1,string_constant_8);
	    return twrite_key_pattern(value);
	}
	else
	    return tformat(3,string_constant_9,value,mask);
    }
    else if (CONSP(key_pattern) && EQ(FIRST(key_pattern),Qab_or))
	return twrite_key_patterns(REST(key_pattern));
    else
	return VALUES_1(Qnil);
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* TWRITE-KEY-PATTERNS */
Object twrite_key_patterns(key_patterns)
    Object key_patterns;
{
    Object sublist;

    x_note_fn_call(35,40);
    sublist = key_patterns;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    twrite_key_pattern(CAR(sublist));
    if ( !TRUEP(CDR(sublist)));
    else if ( !TRUEP(CDDR(sublist)))
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)4L));
    else
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TWRITE-SYMBOL-SIMPLY */
Object twrite_symbol_simply(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(35,41);
    temp = twrite_symbol(1,symbol);
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

static Object Qtwrite_symbol_simply;  /* twrite-symbol-simply */

static Object string_constant_10;  /* " or " */

static Object string_constant_11;  /* ", " */

/* TWRITE-KEY-PATTERNS-AND-CLASSES */
Object twrite_key_patterns_and_classes(key_patterns_and_classes)
    Object key_patterns_and_classes;
{
    Object write_symbols_parsably_qm, sublist, key_pattern, class_or_classes;
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(35,42);
    write_symbols_parsably_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
	    0);
      sublist = key_patterns_and_classes;
      key_pattern = Nil;
      class_or_classes = Nil;
    next_loop:
      if ( !TRUEP(sublist))
	  goto end_loop;
      temp = CAR(sublist);
      key_pattern = CAR(temp);
      temp = CAR(sublist);
      class_or_classes = CDR(temp);
      twrite_key_pattern(key_pattern);
      if (class_or_classes &&  !EQ(class_or_classes,T)) {
	  twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)4L));
	  if (CONSP(class_or_classes))
	      twrite_list_function(class_or_classes,
		      SYMBOL_FUNCTION(Qtwrite_symbol_simply),Nil,
		      string_constant_10,string_constant_11);
	  else
	      twrite_symbol(1,class_or_classes);
      }
      if ( !TRUEP(CDR(sublist)));
      else if ( !TRUEP(CDDR(sublist)))
	  twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)4L));
      else
	  twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
      sublist = M_CDR(sublist);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qmouse_hover;        /* mouse-hover */

/* KEY-CODE-MOUSE-BUTTON-NAME */
Object key_code_mouse_button_name(key_code)
    Object key_code;
{
    Object unicode, key;

    x_note_fn_call(35,43);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)772L || IFIX(key) == (SI_Long)773L || 
	    IFIX(key) == (SI_Long)812L || IFIX(key) == (SI_Long)815L)
	return VALUES_1(Qleft);
    else if (IFIX(key) == (SI_Long)774L || IFIX(key) == (SI_Long)775L || 
	    IFIX(key) == (SI_Long)813L || IFIX(key) == (SI_Long)816L)
	return VALUES_1(Qmiddle);
    else if (IFIX(key) == (SI_Long)776L || IFIX(key) == (SI_Long)777L || 
	    IFIX(key) == (SI_Long)814L || IFIX(key) == (SI_Long)817L)
	return VALUES_1(Qright);
    else if (IFIX(key) == (SI_Long)770L || IFIX(key) == (SI_Long)769L || 
	    IFIX(key) == (SI_Long)779L || IFIX(key) == (SI_Long)778L)
	return VALUES_1(Qany);
    else if (IFIX(key) == (SI_Long)782L)
	return VALUES_1(Qmouse_hover);
    else
	return VALUES_1(Qnil);
}

/* CONVERT-MOUSE-CODE-TO-MOUSE-SELECT */
Object convert_mouse_code_to_mouse_select(key_code)
    Object key_code;
{
    Object unicode, key;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(35,44);
    gensymed_symbol = IFIX(FIXNUM_LOGAND(Key_modifier_bits,key_code));
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)772L || IFIX(key) == (SI_Long)773L)
	gensymed_symbol_1 = (SI_Long)812L;
    else if (IFIX(key) == (SI_Long)774L || IFIX(key) == (SI_Long)775L)
	gensymed_symbol_1 = (SI_Long)813L;
    else if (IFIX(key) == (SI_Long)776L || IFIX(key) == (SI_Long)777L)
	gensymed_symbol_1 = (SI_Long)814L;
    else
	gensymed_symbol_1 = (SI_Long)779L;
    return VALUES_1(FIX(gensymed_symbol | gensymed_symbol_1));
}

/* CONVERT-MOUSE-CODE-TO-MOUSE-DRAG */
Object convert_mouse_code_to_mouse_drag(key_code)
    Object key_code;
{
    Object unicode, key;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(35,45);
    gensymed_symbol = IFIX(FIXNUM_LOGAND(FIXNUM_LOGAND(Key_modifier_bits,
	    key_code),Double_mask));
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)772L || IFIX(key) == (SI_Long)773L)
	gensymed_symbol_1 = (SI_Long)815L;
    else if (IFIX(key) == (SI_Long)774L || IFIX(key) == (SI_Long)775L)
	gensymed_symbol_1 = (SI_Long)816L;
    else if (IFIX(key) == (SI_Long)776L || IFIX(key) == (SI_Long)777L)
	gensymed_symbol_1 = (SI_Long)817L;
    else
	gensymed_symbol_1 = (SI_Long)778L;
    return VALUES_1(FIX(gensymed_symbol | gensymed_symbol_1));
}

/* MOUSE-MOTION-KEY-CODE */
Object mouse_motion_key_code(modifier_bits)
    Object modifier_bits;
{
    x_note_fn_call(35,46);
    return VALUES_1(FIXNUM_LOGIOR(FIXNUM_LOGAND(FIXNUM_LOGAND(modifier_bits,
	    Double_mask),Unicode_mask),FIX((SI_Long)771L)));
}

static Object array_constant_5;    /* # */

/* TWRITE-SHORTCUT-KEY */
Object twrite_shortcut_key(key_code)
    Object key_code;
{
    Object twrite_control_as_ctrl;
    Declare_special(1);
    Object result;

    x_note_fn_call(35,47);
    if (IFIX(key_code) == (SI_Long)127L)
	return twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)3L));
    else {
	twrite_control_as_ctrl = T;
	PUSH_SPECIAL_WITH_SYMBOL(Twrite_control_as_ctrl,Qtwrite_control_as_ctrl,twrite_control_as_ctrl,
		0);
	  result = twrite_key_code(key_code);
	POP_SPECIAL();
	return result;
    }
}

void f_keys_INIT()
{
    Object list_constant, AB_package, Qlt_standard_abort_keys_gt_key_pattern;
    Object Qlt_standard_abort_keys_gt, list_constant_6;
    Object Qlt_delete_forward_keys_gt_key_pattern, Qlt_delete_forward_keys_gt;
    Object list_constant_5, Qlt_delete_backward_keys_gt_key_pattern;
    Object Qlt_delete_backward_keys_gt, list_constant_4;
    Object Qlt_standard_enter_keys_gt_key_pattern, Qlt_standard_enter_keys_gt;
    Object list_constant_3, Qlt_standard_help_keys_gt_key_pattern;
    Object Qlt_standard_help_keys_gt, list_constant_2;
    Object Qlt_standard_newline_keys_gt_key_pattern;
    Object Qlt_standard_newline_keys_gt, list_constant_1;
    Object Qlt_native_menu_choice_gt_key_pattern, Qlt_native_menu_choice_gt;
    Object Qlt_mouse_right_drag_gt_key_pattern, Qlt_mouse_right_drag_gt;
    Object Qlt_mouse_left_drag_gt_key_pattern, Qlt_mouse_left_drag_gt;
    Object Qlt_mouse_right_select_gt_key_pattern, Qlt_mouse_right_select_gt;
    Object Qlt_mouse_middle_select_gt_key_pattern, Qlt_mouse_middle_select_gt;
    Object Qlt_mouse_left_select_gt_key_pattern, Qlt_mouse_left_select_gt;
    Object Qlt_mouse_select_gt_key_pattern, Qlt_mouse_select_gt;
    Object Qlt_mouse_drag_gt_key_pattern, Qlt_mouse_drag_gt;
    Object Qlt_mouse_hover_gt_key_pattern, Qlt_mouse_hover_gt;
    Object Qlt_mouse_motion_gt_key_pattern, Qlt_mouse_motion_gt;
    Object Qlt_mouse_right_down_gt_key_pattern, Qlt_mouse_right_down_gt;
    Object Qlt_mouse_middle_down_gt_key_pattern, Qlt_mouse_middle_down_gt;
    Object Qlt_mouse_left_down_gt_key_pattern, Qlt_mouse_left_down_gt;
    Object Qlt_mouse_down_gt_key_pattern, Qlt_mouse_down_gt;
    Object Qlt_mouse_up_gt_key_pattern, Qlt_mouse_up_gt;
    Object Qlt_mouse_gesture_gt_key_pattern, Qlt_mouse_gesture_gt;
    Object Qlt_any_keyboard_event_gt_key_pattern, Qlt_any_keyboard_event_gt;
    Object Qlt_alphabetic_gt_key_pattern, Qlt_alphabetic_gt;
    Object Qlt_unicode_character_gt_key_pattern, Qlt_unicode_character_gt;
    Object Qlt_printing_character_gt_key_pattern, Qlt_printing_character_gt;
    Object Qlt_pseudo_keycode_gt_key_pattern, Qlt_pseudo_keycode_gt;
    Object Qotherwise_key_pattern, array_constant_6;

    x_note_fn_call(35,48);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qmouse_down = STATIC_SYMBOL("MOUSE-DOWN",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qmouse_left_down = STATIC_SYMBOL("MOUSE-LEFT-DOWN",AB_package);
    Qmiddle = STATIC_SYMBOL("MIDDLE",AB_package);
    Qmouse_middle_down = STATIC_SYMBOL("MOUSE-MIDDLE-DOWN",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qmouse_right_down = STATIC_SYMBOL("MOUSE-RIGHT-DOWN",AB_package);
    Qkey_code_for_key_symbol = STATIC_SYMBOL("KEY-CODE-FOR-KEY-SYMBOL",
	    AB_package);
    Qcontrol = STATIC_SYMBOL("CONTROL",AB_package);
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    Qalternate = STATIC_SYMBOL("ALTERNATE",AB_package);
    Qalt = STATIC_SYMBOL("ALT",AB_package);
    Qmeta = STATIC_SYMBOL("META",AB_package);
    Qdouble = STATIC_SYMBOL("DOUBLE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant_6 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)94L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)94L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)124L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)96L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    Characters_requiring_quotation_in_key_symbols = array_constant_6;
    Qfor_filters = STATIC_SYMBOL("FOR-FILTERS",AB_package);
    if (Twrite_control_as_ctrl == UNBOUND)
	Twrite_control_as_ctrl = Nil;
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    string_constant = STATIC_STRING("Ctrl+");
    string_constant_1 = STATIC_STRING("ctrl+");
    string_constant_2 = STATIC_STRING("Control+");
    string_constant_3 = STATIC_STRING("control+");
    string_constant_4 = STATIC_STRING("Alt+");
    string_constant_5 = STATIC_STRING("alt+");
    string_constant_6 = STATIC_STRING("Shift+");
    string_constant_7 = STATIC_STRING("shift+");
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qkey_pattern_named = STATIC_SYMBOL("KEY-PATTERN-NAMED",AB_package);
    Key_pattern_named_prop = Qkey_pattern_named;
    Qkey_pattern_abbreviation = STATIC_SYMBOL("KEY-PATTERN-ABBREVIATION",
	    AB_package);
    Key_pattern_abbreviation_prop = Qkey_pattern_abbreviation;
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qotherwise_key_pattern = STATIC_SYMBOL("OTHERWISE-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qotherwise_key_pattern,
	    STATIC_FUNCTION(otherwise_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qotherwise,
	    SYMBOL_FUNCTION(Qotherwise_key_pattern),Qkey_pattern_named);
    Qlt_pseudo_keycode_gt = STATIC_SYMBOL("<PSEUDO-KEYCODE>",AB_package);
    Qlt_pseudo_keycode_gt_key_pattern = 
	    STATIC_SYMBOL("<PSEUDO-KEYCODE>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_pseudo_keycode_gt_key_pattern,
	    STATIC_FUNCTION(lt_pseudo_keycode_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_pseudo_keycode_gt,
	    SYMBOL_FUNCTION(Qlt_pseudo_keycode_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_printing_character_gt = STATIC_SYMBOL("<PRINTING-CHARACTER>",
	    AB_package);
    Qlt_printing_character_gt_key_pattern = 
	    STATIC_SYMBOL("<PRINTING-CHARACTER>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_printing_character_gt_key_pattern,
	    STATIC_FUNCTION(lt_printing_character_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_printing_character_gt,
	    SYMBOL_FUNCTION(Qlt_printing_character_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_unicode_character_gt = STATIC_SYMBOL("<UNICODE-CHARACTER>",AB_package);
    Qlt_unicode_character_gt_key_pattern = 
	    STATIC_SYMBOL("<UNICODE-CHARACTER>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_unicode_character_gt_key_pattern,
	    STATIC_FUNCTION(lt_unicode_character_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_unicode_character_gt,
	    SYMBOL_FUNCTION(Qlt_unicode_character_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_alphabetic_gt = STATIC_SYMBOL("<ALPHABETIC>",AB_package);
    Qlt_alphabetic_gt_key_pattern = 
	    STATIC_SYMBOL("<ALPHABETIC>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_alphabetic_gt_key_pattern,
	    STATIC_FUNCTION(lt_alphabetic_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_alphabetic_gt,
	    SYMBOL_FUNCTION(Qlt_alphabetic_gt_key_pattern),Qkey_pattern_named);
    Qlt_any_keyboard_event_gt = STATIC_SYMBOL("<ANY-KEYBOARD-EVENT>",
	    AB_package);
    Qlt_any_keyboard_event_gt_key_pattern = 
	    STATIC_SYMBOL("<ANY-KEYBOARD-EVENT>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_any_keyboard_event_gt_key_pattern,
	    STATIC_FUNCTION(lt_any_keyboard_event_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_any_keyboard_event_gt,
	    SYMBOL_FUNCTION(Qlt_any_keyboard_event_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_gesture_gt = STATIC_SYMBOL("<MOUSE-GESTURE>",AB_package);
    Qlt_mouse_gesture_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-GESTURE>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_gesture_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_gesture_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_gesture_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_gesture_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_up_gt = STATIC_SYMBOL("<MOUSE-UP>",AB_package);
    Qlt_mouse_up_gt_key_pattern = STATIC_SYMBOL("<MOUSE-UP>-KEY-PATTERN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_up_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_up_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_up_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_up_gt_key_pattern),Qkey_pattern_named);
    Qlt_mouse_down_gt = STATIC_SYMBOL("<MOUSE-DOWN>",AB_package);
    Qlt_mouse_down_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-DOWN>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_down_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_down_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_down_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_down_gt_key_pattern),Qkey_pattern_named);
    Qlt_mouse_left_down_gt = STATIC_SYMBOL("<MOUSE-LEFT-DOWN>",AB_package);
    Qlt_mouse_left_down_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-LEFT-DOWN>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_left_down_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_left_down_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_left_down_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_left_down_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_middle_down_gt = STATIC_SYMBOL("<MOUSE-MIDDLE-DOWN>",AB_package);
    Qlt_mouse_middle_down_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-MIDDLE-DOWN>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_middle_down_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_middle_down_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_mouse_middle_down_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_middle_down_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_right_down_gt = STATIC_SYMBOL("<MOUSE-RIGHT-DOWN>",AB_package);
    Qlt_mouse_right_down_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-RIGHT-DOWN>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_right_down_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_right_down_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_right_down_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_right_down_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_motion_gt = STATIC_SYMBOL("<MOUSE-MOTION>",AB_package);
    Qlt_mouse_motion_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-MOTION>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_motion_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_motion_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_motion_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_motion_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_hover_gt = STATIC_SYMBOL("<MOUSE-HOVER>",AB_package);
    Qlt_mouse_hover_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-HOVER>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_hover_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_hover_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_hover_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_hover_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_drag_gt = STATIC_SYMBOL("<MOUSE-DRAG>",AB_package);
    Qlt_mouse_drag_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-DRAG>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_drag_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_drag_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_drag_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_drag_gt_key_pattern),Qkey_pattern_named);
    Qlt_mouse_select_gt = STATIC_SYMBOL("<MOUSE-SELECT>",AB_package);
    Qlt_mouse_select_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-SELECT>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_select_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_select_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_select_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_select_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_left_select_gt = STATIC_SYMBOL("<MOUSE-LEFT-SELECT>",AB_package);
    Qlt_mouse_left_select_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-LEFT-SELECT>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_left_select_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_left_select_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_mouse_left_select_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_left_select_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_middle_select_gt = STATIC_SYMBOL("<MOUSE-MIDDLE-SELECT>",
	    AB_package);
    Qlt_mouse_middle_select_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-MIDDLE-SELECT>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_middle_select_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_middle_select_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_mouse_middle_select_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_middle_select_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_right_select_gt = STATIC_SYMBOL("<MOUSE-RIGHT-SELECT>",
	    AB_package);
    Qlt_mouse_right_select_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-RIGHT-SELECT>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_right_select_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_right_select_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_mouse_right_select_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_right_select_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_left_drag_gt = STATIC_SYMBOL("<MOUSE-LEFT-DRAG>",AB_package);
    Qlt_mouse_left_drag_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-LEFT-DRAG>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_left_drag_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_left_drag_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_left_drag_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_left_drag_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_mouse_right_drag_gt = STATIC_SYMBOL("<MOUSE-RIGHT-DRAG>",AB_package);
    Qlt_mouse_right_drag_gt_key_pattern = 
	    STATIC_SYMBOL("<MOUSE-RIGHT-DRAG>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_mouse_right_drag_gt_key_pattern,
	    STATIC_FUNCTION(lt_mouse_right_drag_gt_key_pattern,NIL,FALSE,1,1));
    mutate_global_property(Qlt_mouse_right_drag_gt,
	    SYMBOL_FUNCTION(Qlt_mouse_right_drag_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_native_menu_choice_gt = STATIC_SYMBOL("<NATIVE-MENU-CHOICE>",
	    AB_package);
    Qlt_native_menu_choice_gt_key_pattern = 
	    STATIC_SYMBOL("<NATIVE-MENU-CHOICE>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_native_menu_choice_gt_key_pattern,
	    STATIC_FUNCTION(lt_native_menu_choice_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_native_menu_choice_gt,
	    SYMBOL_FUNCTION(Qlt_native_menu_choice_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_standard_newline_keys_gt = STATIC_SYMBOL("<STANDARD-NEWLINE-KEYS>",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qab_or,FIX((SI_Long)280L),
	    FIX((SI_Long)394L),FIX((SI_Long)10L));
    mutate_global_property(Qlt_standard_newline_keys_gt,list_constant_1,
	    Qkey_pattern_abbreviation);
    Qlt_standard_newline_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<STANDARD-NEWLINE-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_standard_newline_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_standard_newline_keys_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_standard_newline_keys_gt,
	    SYMBOL_FUNCTION(Qlt_standard_newline_keys_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_standard_help_keys_gt = STATIC_SYMBOL("<STANDARD-HELP-KEYS>",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)4L,Qab_or,
	    FIX((SI_Long)8388671L),FIX((SI_Long)390L),FIX((SI_Long)8388655L));
    mutate_global_property(Qlt_standard_help_keys_gt,list_constant_2,
	    Qkey_pattern_abbreviation);
    Qlt_standard_help_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<STANDARD-HELP-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_standard_help_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_standard_help_keys_gt_key_pattern,NIL,FALSE,
	    1,1));
    mutate_global_property(Qlt_standard_help_keys_gt,
	    SYMBOL_FUNCTION(Qlt_standard_help_keys_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_standard_enter_keys_gt = STATIC_SYMBOL("<STANDARD-ENTER-KEYS>",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,FIX((SI_Long)660L),
	    FIX((SI_Long)281L));
    mutate_global_property(Qlt_standard_enter_keys_gt,list_constant_3,
	    Qkey_pattern_abbreviation);
    Qlt_standard_enter_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<STANDARD-ENTER-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_standard_enter_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_standard_enter_keys_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_standard_enter_keys_gt,
	    SYMBOL_FUNCTION(Qlt_standard_enter_keys_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_delete_backward_keys_gt = STATIC_SYMBOL("<DELETE-BACKWARD-KEYS>",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_or,FIX((SI_Long)278L),
	    FIX((SI_Long)262422L));
    mutate_global_property(Qlt_delete_backward_keys_gt,list_constant_4,
	    Qkey_pattern_abbreviation);
    Qlt_delete_backward_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<DELETE-BACKWARD-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_delete_backward_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_delete_backward_keys_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_delete_backward_keys_gt,
	    SYMBOL_FUNCTION(Qlt_delete_backward_keys_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_delete_forward_keys_gt = STATIC_SYMBOL("<DELETE-FORWARD-KEYS>",
	    AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qab_or,FIX((SI_Long)127L),
	    FIX((SI_Long)262271L));
    mutate_global_property(Qlt_delete_forward_keys_gt,list_constant_5,
	    Qkey_pattern_abbreviation);
    Qlt_delete_forward_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<DELETE-FORWARD-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_delete_forward_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_delete_forward_keys_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_delete_forward_keys_gt,
	    SYMBOL_FUNCTION(Qlt_delete_forward_keys_gt_key_pattern),
	    Qkey_pattern_named);
    Qlt_standard_abort_keys_gt = STATIC_SYMBOL("<STANDARD-ABORT-KEYS>",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,FIX((SI_Long)401L),
	    FIX((SI_Long)1L));
    mutate_global_property(Qlt_standard_abort_keys_gt,list_constant_6,
	    Qkey_pattern_abbreviation);
    Qlt_standard_abort_keys_gt_key_pattern = 
	    STATIC_SYMBOL("<STANDARD-ABORT-KEYS>-KEY-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qlt_standard_abort_keys_gt_key_pattern,
	    STATIC_FUNCTION(lt_standard_abort_keys_gt_key_pattern,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlt_standard_abort_keys_gt,
	    SYMBOL_FUNCTION(Qlt_standard_abort_keys_gt_key_pattern),
	    Qkey_pattern_named);
    string_constant_8 = STATIC_STRING("any+");
    string_constant_9 = STATIC_STRING("[0~o,0~o]");
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qtwrite_symbol_simply = STATIC_SYMBOL("TWRITE-SYMBOL-SIMPLY",AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite_symbol_simply,
	    STATIC_FUNCTION(twrite_symbol_simply,NIL,FALSE,1,1));
    string_constant_10 = STATIC_STRING(" or ");
    string_constant_11 = STATIC_STRING(", ");
    Qmouse_hover = STATIC_SYMBOL("MOUSE-HOVER",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
}
