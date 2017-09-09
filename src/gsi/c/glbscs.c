/* glbscs.c
 * Input file:  glbasics.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "glbscs.h"


Object G2int_debug_1 = UNBOUND;

Object G2int_debug_2 = UNBOUND;

Object G2int_debug_3 = UNBOUND;

Object G2int_debug_4 = UNBOUND;

Object G2int_debug_5 = UNBOUND;

Object G2int_debug_6 = UNBOUND;

Object G2int_debug_7 = UNBOUND;

Object G2int_debug_8 = UNBOUND;

Object G2int_debug_9 = UNBOUND;

Object G2int_debug_10 = UNBOUND;

Object G2int_debug_11 = UNBOUND;

Object G2int_debug_12 = UNBOUND;

Object G2int_lisp_package_1 = UNBOUND;

Object G2int_keyword_package_1 = UNBOUND;

Object G2int_within_managed_object_scope = UNBOUND;

Object G2int_reusable_gensyms = UNBOUND;

Object G2int_available_reusable_gensyms = UNBOUND;

Object G2int_most_positive_fixnum32_plus_one = UNBOUND;

Object G2int_negative_fifty_million = UNBOUND;

static Object float_constant;      /* 0.0 */

/* COERCE-TO-GENSYM-FLOAT-FUNCTION */
Object g2int_coerce_to_gensym_float_function(x)
    Object x;
{
    x_note_fn_call(7,0);
    return lfloat(x,float_constant);
}

Object G2int_most_positive_fixnum_as_float = UNBOUND;

Object G2int_most_negative_fixnum_as_float = UNBOUND;

Object G2int_most_positive_fixnum32_as_float = UNBOUND;

Object G2int_most_positive_fixnum32_plus_one_as_float = UNBOUND;

Object G2int_rational_float_epsilon = UNBOUND;

Object G2int_most_positive_int64 = UNBOUND;

Object G2int_most_negative_int64 = UNBOUND;

Object G2int_destination_for_symbol_with_preserved_cells = UNBOUND;

Object G2int_starlist_of_symbols_for_symbol_valuestar = UNBOUND;

Object G2int_starlist_of_funcalled_functionsstar = UNBOUND;

/* MEMQ-FUNCTION */
Object g2int_memq_function(key,list_1)
    Object key, list_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(7,1);
    gensymed_symbol = list_1;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    if (EQ(M_CAR(gensymed_symbol),key)) {
	temp = gensymed_symbol;
	goto end;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* ASSQ-FUNCTION */
Object g2int_assq_function(key,a_list)
    Object key, a_list;
{
    Object gensymed_symbol, ab_loop_list_, temp;

    x_note_fn_call(7,2);
    gensymed_symbol = Nil;
    ab_loop_list_ = a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),key)) {
	temp = gensymed_symbol;
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* ASSOC-EQUAL */
Object g2int_assoc_equal(key,list_1)
    Object key, list_1;
{
    Object alist_entry, ab_loop_list_, temp;

    x_note_fn_call(7,3);
    alist_entry = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = M_CAR(alist_entry);
    if (EQUAL(temp,key))
	return VALUES_1(alist_entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GETFQ-FUNCTION-NO-DEFAULT */
Object g2int_getfq_function_no_default(plist,indicator)
    Object plist, indicator;
{
    Object list_1;

    x_note_fn_call(7,4);
    list_1 = plist;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),indicator))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : Nil);
}

/* GETFQ-FUNCTION */
Object g2int_getfq_function(plist,indicator,default_1)
    Object plist, indicator, default_1;
{
    Object list_1;

    x_note_fn_call(7,5);
    list_1 = plist;
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),indicator))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:;
    return VALUES_1(list_1 ? M_CAR(M_CDR(list_1)) : default_1);
}

/* *F-SAFE */
Object g2int_starf_safe(arg1,arg2)
    Object arg1, arg2;
{
    Object temp;
    char temp_3;
    double temp_1, temp_2, float_result, arg, arg_1;

    x_note_fn_call(7,6);
    temp = lfloat(arg1,float_constant);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = lfloat(arg2,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    float_result = temp_1 * temp_2;
    arg = float_result;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_negative_fixnum_as_float);
    temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_3);
    else {
	arg = float_result;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum_as_float);
	temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    temp = temp_3 ? Nil : LONG_TO_FIXNUM(inline_floor_1(float_result));
    return VALUES_1(temp);
}

Object G2int_special_variable_for_use_value_macro = UNBOUND;

/* %POINTER */
Object g2int_pctpointer(lisp_object)
    Object lisp_object;
{
    x_note_fn_call(7,7);
    return VALUES_1(PCT_POINTER_1(lisp_object));
}

/* PRINT-RANDOM-OBJECT-PREFIX-FOR-GSI */
Object g2int_print_random_object_prefix_for_gsi(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,8);
    return format((SI_Long)2L,T,"#<");
}

/* PRINT-RANDOM-OBJECT-SUFFIX-FOR-GSI */
Object g2int_print_random_object_suffix_for_gsi(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,9);
    return format((SI_Long)3L,T," ~x>",g2int_pctpointer(object));
}

Object G2int_optimized_constant_vector = UNBOUND;

Object G2int_optimized_constant_vector_index = UNBOUND;

Object G2int_optimized_constant_pc = UNBOUND;

Object G2int_optimized_constant_op_codes = UNBOUND;

/* REGENERATE-STANDARD-SYMBOLS */
Object g2int_regenerate_standard_symbols(standard_symbols_input)
    Object standard_symbols_input;
{
    Object optimized_constant_pc, optimized_constant_op_codes, new_array;
    Object package_name_1, package, symbol_name_1, svref_new_value;
    SI_Long index_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(7,10);
    if (standard_symbols_input) {
	optimized_constant_pc = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_optimized_constant_pc,optimized_constant_pc,1);
	  optimized_constant_op_codes = standard_symbols_input;
	  PUSH_SPECIAL(G2int_optimized_constant_op_codes,optimized_constant_op_codes,
		  0);
	    new_array = make_array(1,g2int_read_optimized_constant());
	    index_1 = (SI_Long)0L;
	    package_name_1 = Nil;
	    package = Nil;
	  next_loop:
	    package_name_1 = g2int_read_optimized_constant();
	    if (FIXNUMP(package_name_1))
		goto end_loop;
	    package = find_package(package_name_1);
	    symbol_name_1 = Nil;
	  next_loop_1:
	    symbol_name_1 = g2int_read_optimized_constant();
	    if (FIXNUMP(symbol_name_1))
		goto end_loop_1;
	    svref_new_value = intern(symbol_name_1,package);
	    ISVREF(new_array,index_1) = svref_new_value;
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(new_array);
	    goto end;
	    result = VALUES_1(Qnil);
	  end:;
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

Object G2int_standard_symbols_for_optimized_constantqm = UNBOUND;

/* CLEAR-OPTIMIZED-CONSTANTS */
Object g2int_clear_optimized_constants()
{
    x_note_fn_call(7,11);
    G2int_optimized_constant_vector_index = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

/* PUSH-OPTIMIZED-CONSTANT */
Object g2int_push_optimized_constant(constant)
    Object constant;
{
    Object temp, svref_arg_2;

    x_note_fn_call(7,12);
    if (FIXNUM_GE(G2int_optimized_constant_vector_index,
	    SIMPLE_ARRAY_ANY_1_LENGTH(G2int_optimized_constant_vector))) {
	format((SI_Long)3L,T,
		"Error initializing constants, vector overflow at ~a.",
		G2int_optimized_constant_vector_index);
	g2int_exit_lisp_process(1,FIX((SI_Long)0L));
    }
    temp = G2int_optimized_constant_vector;
    svref_arg_2 = G2int_optimized_constant_vector_index;
    SVREF(temp,svref_arg_2) = constant;
    temp = FIXNUM_ADD1(G2int_optimized_constant_vector_index);
    G2int_optimized_constant_vector_index = temp;
    return VALUES_1(Nil);
}

/* REGENERATE-OPTIMIZED-CONSTANT */
Object g2int_regenerate_optimized_constant(op_codes)
    Object op_codes;
{
    Object temp;

    x_note_fn_call(7,13);
    G2int_optimized_constant_pc = FIX((SI_Long)0L);
    G2int_optimized_constant_op_codes = op_codes;
    temp = g2int_read_optimized_constant();
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* READ-OPTIMIZED-CONSTANT */
Object g2int_read_optimized_constant()
{
    Object op_code_string, temp, temp_1, new_list, cons_1, trailer;
    Object digit_char_1, new_vector, new_string;
    SI_Long new_fixnum, new_bits, vector_length, index_1, ab_loop_bind_;
    SI_Long string_length, aref_new_value;
    char op_code_char, dispatch_char;

    x_note_fn_call(7,14);
    op_code_string = CONSP(G2int_optimized_constant_op_codes) ? 
	    M_CAR(G2int_optimized_constant_op_codes) : 
	    G2int_optimized_constant_op_codes;
    op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
	    G2int_optimized_constant_pc));
    temp = FIXNUM_ADD1(G2int_optimized_constant_pc);
    G2int_optimized_constant_pc = temp;
    if (FIXNUM_GE(G2int_optimized_constant_pc,
	    SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	G2int_optimized_constant_pc = FIX((SI_Long)0L);
	if (CONSP(G2int_optimized_constant_op_codes))
	    G2int_optimized_constant_op_codes = 
		    M_CDR(G2int_optimized_constant_op_codes);
	else
	    G2int_optimized_constant_op_codes = Nil;
    }
    dispatch_char = op_code_char;
    switch (dispatch_char) {
      case '0':
	temp_1 = Nil;
	break;
      case '1':
	new_list = make_list(1,g2int_read_optimized_constant());
	cons_1 = new_list;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	temp = g2int_read_optimized_constant();
	M_CAR(cons_1) = temp;
	cons_1 = M_CDR(cons_1);
	goto next_loop;
      end_loop:
	temp_1 = new_list;
	goto end;
	temp_1 = Qnil;
      end:;
	break;
      case '2':
	new_list = make_list(1,g2int_read_optimized_constant());
	trailer = Nil;
	cons_1 = new_list;
      next_loop_1:
	if ( !TRUEP(cons_1))
	    goto end_loop_1;
	temp = g2int_read_optimized_constant();
	M_CAR(cons_1) = temp;
	trailer = cons_1;
	cons_1 = M_CDR(cons_1);
	goto next_loop_1;
      end_loop_1:
	temp = g2int_read_optimized_constant();
	M_CDR(trailer) = temp;
	temp_1 = new_list;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	break;
      case '3':
	new_fixnum = (SI_Long)0L;
	digit_char_1 = Nil;
	new_bits = (SI_Long)0L;
      next_loop_2:
	op_code_string = CONSP(G2int_optimized_constant_op_codes) ? 
		M_CAR(G2int_optimized_constant_op_codes) : 
		G2int_optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		G2int_optimized_constant_pc));
	temp = FIXNUM_ADD1(G2int_optimized_constant_pc);
	G2int_optimized_constant_pc = temp;
	if (FIXNUM_GE(G2int_optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    G2int_optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(G2int_optimized_constant_op_codes))
		G2int_optimized_constant_op_codes = 
			M_CDR(G2int_optimized_constant_op_codes);
	    else
		G2int_optimized_constant_op_codes = Nil;
	}
	digit_char_1 = CHAR_TO_CHARACTER(op_code_char);
	if (CHAR_EQ(digit_char_1,CHR('y')) || CHAR_EQ(digit_char_1,CHR('z')))
	    goto end_loop_2;
	switch (ICHAR_CODE(digit_char_1)) {
	  case '+':
	    new_bits = (SI_Long)0L;
	    break;
	  case '-':
	    new_bits = (SI_Long)1L;
	    break;
	  case '*':
	    new_bits = (SI_Long)2L;
	    break;
	  case '=':
	    new_bits = (SI_Long)3L;
	    break;
	  case '0':
	    new_bits = (SI_Long)4L;
	    break;
	  case '1':
	    new_bits = (SI_Long)5L;
	    break;
	  case '2':
	    new_bits = (SI_Long)6L;
	    break;
	  case '3':
	    new_bits = (SI_Long)7L;
	    break;
	  case '4':
	    new_bits = (SI_Long)8L;
	    break;
	  case '5':
	    new_bits = (SI_Long)9L;
	    break;
	  case '6':
	    new_bits = (SI_Long)10L;
	    break;
	  case '7':
	    new_bits = (SI_Long)11L;
	    break;
	  case '8':
	    new_bits = (SI_Long)12L;
	    break;
	  case '9':
	    new_bits = (SI_Long)13L;
	    break;
	  case 'A':
	    new_bits = (SI_Long)14L;
	    break;
	  case 'B':
	    new_bits = (SI_Long)15L;
	    break;
	  case 'C':
	    new_bits = (SI_Long)16L;
	    break;
	  case 'D':
	    new_bits = (SI_Long)17L;
	    break;
	  case 'E':
	    new_bits = (SI_Long)18L;
	    break;
	  case 'F':
	    new_bits = (SI_Long)19L;
	    break;
	  case 'G':
	    new_bits = (SI_Long)20L;
	    break;
	  case 'H':
	    new_bits = (SI_Long)21L;
	    break;
	  case 'I':
	    new_bits = (SI_Long)22L;
	    break;
	  case 'J':
	    new_bits = (SI_Long)23L;
	    break;
	  case 'K':
	    new_bits = (SI_Long)24L;
	    break;
	  case 'L':
	    new_bits = (SI_Long)25L;
	    break;
	  case 'M':
	    new_bits = (SI_Long)26L;
	    break;
	  case 'N':
	    new_bits = (SI_Long)27L;
	    break;
	  case 'O':
	    new_bits = (SI_Long)28L;
	    break;
	  case 'P':
	    new_bits = (SI_Long)29L;
	    break;
	  case 'Q':
	    new_bits = (SI_Long)30L;
	    break;
	  case 'R':
	    new_bits = (SI_Long)31L;
	    break;
	  case 'S':
	    new_bits = (SI_Long)32L;
	    break;
	  case 'T':
	    new_bits = (SI_Long)33L;
	    break;
	  case 'U':
	    new_bits = (SI_Long)34L;
	    break;
	  case 'V':
	    new_bits = (SI_Long)35L;
	    break;
	  case 'W':
	    new_bits = (SI_Long)36L;
	    break;
	  case 'X':
	    new_bits = (SI_Long)37L;
	    break;
	  case 'Y':
	    new_bits = (SI_Long)38L;
	    break;
	  case 'Z':
	    new_bits = (SI_Long)39L;
	    break;
	  case 'a':
	    new_bits = (SI_Long)40L;
	    break;
	  case 'b':
	    new_bits = (SI_Long)41L;
	    break;
	  case 'c':
	    new_bits = (SI_Long)42L;
	    break;
	  case 'd':
	    new_bits = (SI_Long)43L;
	    break;
	  case 'e':
	    new_bits = (SI_Long)44L;
	    break;
	  case 'f':
	    new_bits = (SI_Long)45L;
	    break;
	  case 'g':
	    new_bits = (SI_Long)46L;
	    break;
	  case 'h':
	    new_bits = (SI_Long)47L;
	    break;
	  case 'i':
	    new_bits = (SI_Long)48L;
	    break;
	  case 'j':
	    new_bits = (SI_Long)49L;
	    break;
	  case 'k':
	    new_bits = (SI_Long)50L;
	    break;
	  case 'l':
	    new_bits = (SI_Long)51L;
	    break;
	  case 'm':
	    new_bits = (SI_Long)52L;
	    break;
	  case 'n':
	    new_bits = (SI_Long)53L;
	    break;
	  case 'o':
	    new_bits = (SI_Long)54L;
	    break;
	  case 'p':
	    new_bits = (SI_Long)55L;
	    break;
	  case 'q':
	    new_bits = (SI_Long)56L;
	    break;
	  case 'r':
	    new_bits = (SI_Long)57L;
	    break;
	  case 's':
	    new_bits = (SI_Long)58L;
	    break;
	  case 't':
	    new_bits = (SI_Long)59L;
	    break;
	  case 'u':
	    new_bits = (SI_Long)60L;
	    break;
	  case 'v':
	    new_bits = (SI_Long)61L;
	    break;
	  case 'w':
	    new_bits = (SI_Long)62L;
	    break;
	  case 'x':
	    new_bits = (SI_Long)63L;
	    break;
	  default:
	    new_bits = (SI_Long)64L;
	    break;
	}
	new_fixnum = (new_fixnum << (SI_Long)6L) + new_bits;
	goto next_loop_2;
      end_loop_2:
	temp_1 = CHAR_EQ(digit_char_1,CHR('y')) ? FIX(new_fixnum) : FIX( - 
		new_fixnum);
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	break;
      case '4':
	vector_length = IFIX(g2int_read_optimized_constant());
	new_vector = make_array(1,FIX(vector_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = vector_length;
      next_loop_3:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_3;
	temp = g2int_read_optimized_constant();
	ISVREF(new_vector,index_1) = temp;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	temp_1 = new_vector;
	goto end_3;
	temp_1 = Qnil;
      end_3:;
	break;
      case '5':
	string_length = IFIX(g2int_read_optimized_constant());
	new_string = make_string(1,FIX(string_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_4:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_4;
	op_code_string = CONSP(G2int_optimized_constant_op_codes) ? 
		M_CAR(G2int_optimized_constant_op_codes) : 
		G2int_optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		G2int_optimized_constant_pc));
	temp = FIXNUM_ADD1(G2int_optimized_constant_pc);
	G2int_optimized_constant_pc = temp;
	if (FIXNUM_GE(G2int_optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    G2int_optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(G2int_optimized_constant_op_codes))
		G2int_optimized_constant_op_codes = 
			M_CDR(G2int_optimized_constant_op_codes);
	    else
		G2int_optimized_constant_op_codes = Nil;
	}
	SET_ISCHAR(new_string,index_1,op_code_char);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	temp_1 = new_string;
	goto end_4;
	temp_1 = Qnil;
      end_4:;
	break;
      case '6':
	op_code_string = CONSP(G2int_optimized_constant_op_codes) ? 
		M_CAR(G2int_optimized_constant_op_codes) : 
		G2int_optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		G2int_optimized_constant_pc));
	temp = FIXNUM_ADD1(G2int_optimized_constant_pc);
	G2int_optimized_constant_pc = temp;
	if (FIXNUM_GE(G2int_optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    G2int_optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(G2int_optimized_constant_op_codes))
		G2int_optimized_constant_op_codes = 
			M_CDR(G2int_optimized_constant_op_codes);
	    else
		G2int_optimized_constant_op_codes = Nil;
	}
	temp_1 = CHAR_TO_CHARACTER(op_code_char);
	break;
      case '7':
	string_length = IFIX(g2int_read_optimized_constant());
	new_string = make_string(1,FIX(string_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_5:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_5;
	temp = CODE_CHAR(g2int_read_optimized_constant());
	SET_ISCHAR(new_string,index_1,ICHAR_CODE(temp));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:
	temp_1 = new_string;
	goto end_5;
	temp_1 = Qnil;
      end_5:;
	break;
      case '8':
	temp_1 = G2int_standard_symbols_for_optimized_constantqm;
	temp_1 = ISVREF(temp_1,IFIX(g2int_read_optimized_constant()));
	break;
      case '9':
	temp_1 = G2int_optimized_constant_vector;
	temp_1 = ISVREF(temp_1,IFIX(g2int_read_optimized_constant()));
	break;
      case '+':
	vector_length = IFIX(g2int_read_optimized_constant());
	new_vector = make_array(3,FIX(vector_length),Kelement_type,
		list_constant);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = vector_length;
      next_loop_6:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_6;
	aref_new_value = IFIX(g2int_read_optimized_constant());
	set_aref1(new_vector,FIX(index_1),FIX(aref_new_value));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:
	temp_1 = new_vector;
	goto end_6;
	temp_1 = Qnil;
      end_6:;
	break;
      case 'A':
	temp_1 = Most_negative_fixnum;
	break;
      default:
	if (CHAR_GE(CHAR_TO_CHARACTER(dispatch_char),CHR('a')) && 
		CHAR_LE(CHAR_TO_CHARACTER(dispatch_char),CHR('z')))
	    temp_1 = 
		    FIX(IFIX(FIXNUM_MINUS(CHAR_CODE(CHAR_TO_CHARACTER(dispatch_char)),
		    CHAR_CODE(CHR('a')))) - (SI_Long)10L);
	else {
	    format((SI_Long)3L,T,
		    "Error reading constant, bad dispatch char = ~s",
		    CHAR_TO_CHARACTER(dispatch_char));
	    g2int_exit_lisp_process(1,FIX((SI_Long)0L));
	    temp_1 = Nil;
	}
	break;
    }
    return VALUES_1(temp_1);
}

void glbasics_INIT()
{
    Object integer;
    SI_int64 long_1, zero;
    double temp;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object string_constant_2, Qg2int_optimized_constant_vector_length;
    Object AB_package, float_constant_1, Qg2int_rational_float_epsilon;
    Object Qg2int_most_negative_fixnum32, Qg2int_most_positive_fixnum32;
    Object string_constant_1, string_constant;

    x_note_fn_call(7,15);
    SET_PACKAGE("AB");
    if (G2int_debug_1 == UNBOUND)
	G2int_debug_1 = Nil;
    if (G2int_debug_2 == UNBOUND)
	G2int_debug_2 = Nil;
    if (G2int_debug_3 == UNBOUND)
	G2int_debug_3 = Nil;
    if (G2int_debug_4 == UNBOUND)
	G2int_debug_4 = Nil;
    if (G2int_debug_5 == UNBOUND)
	G2int_debug_5 = Nil;
    if (G2int_debug_6 == UNBOUND)
	G2int_debug_6 = Nil;
    if (G2int_debug_7 == UNBOUND)
	G2int_debug_7 = Nil;
    if (G2int_debug_8 == UNBOUND)
	G2int_debug_8 = Nil;
    if (G2int_debug_9 == UNBOUND)
	G2int_debug_9 = Nil;
    if (G2int_debug_10 == UNBOUND)
	G2int_debug_10 = Nil;
    if (G2int_debug_11 == UNBOUND)
	G2int_debug_11 = Nil;
    if (G2int_debug_12 == UNBOUND)
	G2int_debug_12 = Nil;
    string_constant = STATIC_STRING("COMMON-LISP");
    if (G2int_lisp_package_1 == UNBOUND)
	G2int_lisp_package_1 = find_package(string_constant);
    string_constant_1 = STATIC_STRING("KEYWORD");
    if (G2int_keyword_package_1 == UNBOUND)
	G2int_keyword_package_1 = find_package(string_constant_1);
    if (G2int_within_managed_object_scope == UNBOUND)
	G2int_within_managed_object_scope = Nil;
    if (G2int_available_reusable_gensyms == UNBOUND)
	G2int_available_reusable_gensyms = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_most_positive_fixnum32 = STATIC_SYMBOL("MOST-POSITIVE-FIXNUM32",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_positive_fixnum32,FIX((SI_Long)536870911L));
    Qg2int_most_negative_fixnum32 = STATIC_SYMBOL("MOST-NEGATIVE-FIXNUM32",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_negative_fixnum32,FIX((SI_Long)-536870912L));
    G2int_most_positive_fixnum32_plus_one = add1(G2int_most_positive_fixnum32);
    G2int_negative_fifty_million = FIX((SI_Long)-50000000L);
    float_constant = STATIC_FLOAT(0.0);
    G2int_most_positive_fixnum_as_float = 
	    g2int_coerce_to_gensym_float_function(Most_positive_fixnum);
    G2int_most_negative_fixnum_as_float = 
	    g2int_coerce_to_gensym_float_function(Most_negative_fixnum);
    G2int_most_positive_fixnum32_as_float = 
	    g2int_coerce_to_gensym_float_function(G2int_most_positive_fixnum32);
    temp = DOUBLE_FLOAT_TO_DOUBLE(G2int_most_positive_fixnum32_as_float);
    G2int_most_positive_fixnum32_plus_one_as_float = 
	    DOUBLE_TO_DOUBLE_FLOAT(temp + 1.0);
    Qg2int_rational_float_epsilon = STATIC_SYMBOL("RATIONAL-FLOAT-EPSILON",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rational_float_epsilon,
	    G2int_rational_float_epsilon);
    float_constant_1 = STATIC_FLOAT(1.0E-6);
    SET_SYMBOL_VALUE(Qg2int_rational_float_epsilon,float_constant_1);
    integer = sub1(ltimes(FIX((SI_Long)2097152L),
	    ltimes(FIX((SI_Long)2097152L),FIX((SI_Long)2097152L))));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    G2int_most_positive_int64 = add(INT64_TO_INTEGER(long_1),
	    INT64_TO_INTEGER(zero));
    G2int_most_negative_int64 = sub1(negate(G2int_most_positive_int64));
    if (G2int_destination_for_symbol_with_preserved_cells == UNBOUND)
	G2int_destination_for_symbol_with_preserved_cells = Nil;
    if (G2int_starlist_of_symbols_for_symbol_valuestar == UNBOUND)
	G2int_starlist_of_symbols_for_symbol_valuestar = Nil;
    if (G2int_starlist_of_funcalled_functionsstar == UNBOUND)
	G2int_starlist_of_funcalled_functionsstar = Nil;
    if (G2int_special_variable_for_use_value_macro == UNBOUND)
	G2int_special_variable_for_use_value_macro = Nil;
    Qg2int_optimized_constant_vector_length = 
	    STATIC_SYMBOL("OPTIMIZED-CONSTANT-VECTOR-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_optimized_constant_vector_length,
	    FIX((SI_Long)1300L));
    if (G2int_optimized_constant_vector == UNBOUND)
	G2int_optimized_constant_vector = make_array(1,
		G2int_optimized_constant_vector_length);
    if (G2int_optimized_constant_vector_index == UNBOUND)
	G2int_optimized_constant_vector_index = FIX((SI_Long)0L);
    if (G2int_optimized_constant_pc == UNBOUND)
	G2int_optimized_constant_pc = FIX((SI_Long)0L);
    if (G2int_optimized_constant_op_codes == UNBOUND)
	G2int_optimized_constant_op_codes = Nil;
    string_constant_2 = 
	    STATIC_STRING("314y5vCOMMON-LISP5lTk53NyG2-DEFSTRUCT-STRUCTURE-NAME53MyTYPE-DESCRIPTION-G2-STRUCTk5mAB53IyNAMED-GENSYM-STRUCTUREk5rKEYWORD5vCON");
    string_constant_3 = 
	    STATIC_STRING("STRUCTOR5rINCLUDE5tRECLAIMERk5mAB53HyGRAPHIC-CHARACTER-SET53cyGRAPHIC-CHARACTER-SET-CHARACTERS-PER-OCTET53QyGRAPHIC-CHARACTER-SE");
    string_constant_4 = 
	    STATIC_STRING("T-N-OCTETS53MyGRAPHIC-CHARACTER-SET-NAME53dyGRAPHIC-CHARACTER-SET-REGISTRATION-SEQUENCE53QyGRAPHIC-CHARACTER-SET-SYNONYMS53DyISO");
    string_constant_5 = 
	    STATIC_STRING("-8859-ABSTRACT5uTRANSCODER53Cy8859-PART-NUMBER53DyASIAN-DOUBLE-BYTEk5rKEYWORD53FyCREATIONS-AT-A-TIME5oTYPEk5mAB53UyREMOTE-PROCED");
    string_constant_6 = 
	    STATIC_STRING("URE-ITEM-PASSING-INFO53IyRESUMABLE-OBJECT-MIXIN5xTEXT-SEQUENCE53-=yREMOTE-PROCEDURE-ITEM-PASSING-INFO-INTERNED-VARARGSP+ITEM-INF");
    string_constant_7 = 
	    STATIC_STRING("O-LIST53GyRESUMABLE-NODE-MIXIN5qSOCKET53LyTEXT-SEQUENCE-STRING-TYPE53CyUTF-G-TRANSCODER5mAE5rANSI3.45pASCII5qAacute5vAcircumflex");
    string_constant_8 = 
	    STATIC_STRING("5uAdiaeresis5tAdieresis5qAgrave5pAring5qAtilde5yBALANCE-FACTOR53GyBINARY-ELEMENT-ALIST53MyBINARY-ELEMENT-HASH-NUMBER53FyBINARY-T");
    string_constant_9 = 
	    STATIC_STRING("REE-ELEMENT5xCONSTANT-TYPE53JyCONSTANT-VALUE-INTERNAL53TyCONTINUATION-OF-PENDING-ACTIVITY\?5sCcedillak5rKEYWORD53IyELIMINATE-FOR-");
    string_constant_10 = 
	    STATIC_STRING("PRODUCTSk5mAB5xEQ-HASH-TABLE5uERROR-CODE53FyERROR-FORMAT-STRING5yERROR-SEVERITY5qEacute5vEcircumflex5uEdiaeresis5tEdieresis5qEgr");
    string_constant_11 = 
	    STATIC_STRING("ave53FyFOREIGN-STRUCT-INFO53KyFUTURE-TASK-QUEUE-HOLDER5mGB5rGB-23125qGB231253IyGENSYM-PATHNAME-DEVICE53LyGENSYM-PATHNAME-DIRECTO");
    string_constant_12 = 
	    STATIC_STRING("RY53GyGENSYM-PATHNAME-HOST53GyGENSYM-PATHNAME-NAME53GyGENSYM-PATHNAME-TYPE53JyGENSYM-PATHNAME-VERSION5xGENSYM-STRING53GyGENSYM-S");
    string_constant_13 = 
	    STATIC_STRING("TRING-STREAM53NyGENSYM-STRING-TEXT-SEQUENCE53FyGREATER-THAN-BRANCHk5rKEYWORD5nGSIk5mAB5zGSI-APPLICATION53NyGSI-APPLICATION-NAME-");
    string_constant_14 = 
	    STATIC_STRING("SYMBOL5tGSI-ARRAY5yGSI-ARRAY-TYPE53DyGSI-ARRAY-WRAPPER5xGSI-ATTRIBUTE53IyGSI-ATTRIBUTE-INSTANCE53FyGSI-ATTRIBUTE-OWNER53EyGSI-AT");
    string_constant_15 = 
	    STATIC_STRING("TRIBUTE-SPEC53EyGSI-EXTENSION-DATA5vGSI-HISTORY53FyGSI-HISTORY-COUNTER53EyGSI-HISTORY-LENGTH53IyGSI-HISTORY-TIMESTAMPS53EyGSI-HI");
    string_constant_16 = 
	    STATIC_STRING("STORY-VALUES5wGSI-INSTANCE53IyGSI-INSTANCE-EXTENSION53EyGSI-LOCAL-FUNCTION53GyGSI-REMOTE-PROCEDURE53HyGSI-TRANSFER-INSTANCE53EyG");
    string_constant_17 = 
	    STATIC_STRING("SI-TRANSFER-OWNER53OyGSI-TRANSFER-SENSOR-OR-INDEX53FyGSI-TRANSFER-STATUS53OyGSI-TRANSFER-UPDATE-INTERVAL53GyGSI-TRANSFER-WRAPPER");
    string_constant_18 = 
	    STATIC_STRING("5uICP-BUFFER53DyICP-BUFFER-VECTOR53HyICP-CONNECTION-HANDLE53FyICP-CONNECTION-NAME53GyICP-CONNECTION-STATE5sICP-PORT53EyICP-PORT-");
    string_constant_19 = 
	    STATIC_STRING("DIRECTION5xICP-READ-TASK53eyICP-READ-TASK-CORRESPONDING-ICP-OBJECT-INDEX5uICP-SOCKET53OyICP-SOCKET-LOCAL-SYSTEM-NAME5yICP-WRITE-");
    string_constant_20 = 
	    STATIC_STRING("TASK53OyICP-WRITE-TASK-ARGUMENT-LIST53ZyICP-WRITE-TASK-COMPLETION-ARGUMENT-LIST53UyICP-WRITE-TASK-COMPLETION-FUNCTION53fyICP-WRI");
    string_constant_21 = 
	    STATIC_STRING("TE-TASK-CORRESPONDING-ICP-OBJECT-INDEX53JyICP-WRITE-TASK-FUNCTION53UyICP-WRITE-TASK-RESUMABLE-ICP-STATE53HyICP-WRITE-TASK-STARTP");
    string_constant_22 = 
	    STATIC_STRING("5vINDEX-SPACE53CyINDEX-SPACE-NAME53PyINDEX-SPACE-OBJECT-RECLAIMER\?5xINTERNED-LIST53FyINTERNED-LIST--LIST53dyINTERNED-REMOTE-PROC");
    string_constant_23 = 
	    STATIC_STRING("EDURE-ITEM-PASSING-INFO53FyISO-2022-TRANSCODER5rISO-6465vISO-646-IRV5uISO-8859-15vISO-8859-105uISO-8859-25uISO-8859-35uISO-8859-");
    string_constant_24 = 
	    STATIC_STRING("45uISO-8859-55uISO-8859-65uISO-8859-75uISO-8859-85uISO-8859-953QyISO-8859-GRAPHIC-CHARACTER-SET53GyISO-8859-PART-NUMBER53FyISO-8");
    string_constant_25 = 
	    STATIC_STRING("859-TRANSCODER5qIacute5vIcircumflex5uIdiaeresis5tIdieresis5qIgrave5nJIS5uJIS-X-02085mKS5tKS-C-56015nKSC5rLATIN-15rLATIN-25rLATIN");
    string_constant_26 = 
	    STATIC_STRING("-35rLATIN-45rLATIN-55rLATIN-65wLATIN-ARABIC5yLATIN-CYRILLIC5vLATIN-GREEK5wLATIN-HEBREW53CyLESS-THAN-BRANCH5zLISTENER-SOCKET53KyM");
    string_constant_27 = 
	    STATIC_STRING("AKE-BINARY-TREE-ELEMENT53NyMAKE-EQ-HASH-TABLE-INTERNAL5zMAKE-ERROR-CODE53RyMAKE-FUTURE-TASK-QUEUE-HOLDER-153WyMAKE-GENSYM-PATHNA");
    string_constant_28 = 
	    STATIC_STRING("ME-STRUCTURE-MACRO53UyMAKE-GENSYM-STRING-STREAM-INTERNAL53GyMAKE-GSI-APPLICATION53IyMAKE-GSI-ARRAY-WRAPPER53GyMAKE-GSI-ATTRIBUTE");
    string_constant_29 = 
	    STATIC_STRING("-153EyMAKE-GSI-HISTORY-153FyMAKE-GSI-INSTANCE-153NyMAKE-GSI-INSTANCE-EXTENSION53NyMAKE-GSI-TRANSFER-WRAPPER-153KyMAKE-ICP-BUFFER");
    string_constant_30 = 
	    STATIC_STRING("-INTERNAL53JyMAKE-ICP-PORT-STRUCTURE53EyMAKE-ICP-READ-TASK53LyMAKE-ICP-SOCKET-STRUCTURE53FyMAKE-ICP-WRITE-TASK53CyMAKE-INDEX-SPA");
    string_constant_31 = 
	    STATIC_STRING("CE53EyMAKE-INTERNED-LIST53kyMAKE-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-153KyMAKE-ISO-8859-TRANSCODER53OyMAKE-OBJECT-BUILDI");
    string_constant_32 = 
	    STATIC_STRING("NG-PROBLEM53HyMAKE-PENDING-ACTIVITY53EyMAKE-QUEUE-ELEMENT53FyMAKE-QUEUE-INTERNAL53RyMAKE-RECEIVING-RESUMABLE-OBJECT53SyMAKE-REMO");
    string_constant_33 = 
	    STATIC_STRING("TE-PROCEDURE-IDENTIFIER53byMAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-153MyMAKE-REMOTE-PROCEDURE-NAME53EyMAKE-SCHEDULE-TASK53IyMAKE");
    string_constant_34 = 
	    STATIC_STRING("-SKIP-LIST-ELEMENT53CyMAKE-SYMBOL-TREE53LyMAKE-TEMPORARY-CONSTANT-153NyMAKE-TEXT-SEQUENCE-INTERNAL53EyMAKE-UNICODE-BLOCK53KyNAME");
    string_constant_35 = 
	    STATIC_STRING("-OF-PENDING-ACTIVITY5qNtilde53JyOBJECT-BUILDING-PROBLEM53UyOBJECT-BUILDING-PROBLEM-ATTRIBUTE\?53VyOBJECT-BUILDING-PROBLEM-CLASS-N");
    string_constant_36 = 
	    STATIC_STRING("AME\?53UyOBJECT-BUILDING-PROBLEM-EXTRA-INFO53jyOBJECT-BUILDING-PROBLEM-EXTRA-INFO-FORMAT-STRING\?53fyOBJECT-BUILDING-PROBLEM-EXTRA");
    string_constant_37 = 
	    STATIC_STRING("-INFO-RECLAIMER\?53OyOBJECT-BUILDING-PROBLEM-NAME5mOE5qOacute5vOcircumflex5tOdieresis5qOgrave5qOslash5qOtilde53DyPARENT-ICP-SOCKE");
    string_constant_38 = 
	    STATIC_STRING("T53NyPARENT-OF-PENDING-ACTIVITY\?53CyPENDING-ACTIVITYk5rKEYWORD5yPRINT-FUNCTIONk5mAB5vPRINT-QUEUE5pQUEUE5vQUEUE-DATUM5xQUEUE-ELEM");
    string_constant_39 = 
	    STATIC_STRING("ENT53FyQUEUE-HEAD-INTERNAL53EyQUEUE-NEXT-ELEMENT53IyQUEUE-PREVIOUS-ELEMENT53FyQUEUE-TAIL-INTERNAL53PyRECEIVE-OR-TRANSMIT-DIRECTL");
    string_constant_40 = 
	    STATIC_STRING("Y\?53MyRECEIVING-RESUMABLE-OBJECT53RyRECEIVING-RPC-ARGLIST-STRUCTURE53QyRECLAIM-EQ-HASH-TABLE-INTERNAL53UyRECLAIM-FUTURE-TASK-QUE");
    string_constant_41 = 
	    STATIC_STRING("UE-HOLDER-153ZyRECLAIM-GENSYM-PATHNAME-STRUCTURE-MACRO53JyRECLAIM-GSI-ATTRIBUTE-153VyRECLAIM-GSI-EXTENSION-DATA-INTERNAL53HyRECL");
    string_constant_42 = 
	    STATIC_STRING("AIM-GSI-HISTORY-153IyRECLAIM-GSI-INSTANCE-153SyRECLAIM-GSI-INSTANCE-EXTENSION-153XyRECLAIM-GSI-REMOTE-PROCEDURE-INTERNAL53QyRECL");
    string_constant_43 = 
	    STATIC_STRING("AIM-GSI-TRANSFER-WRAPPER-153NyRECLAIM-ICP-BUFFER-INTERNAL53LyRECLAIM-ICP-PORT-INTERNAL53NyRECLAIM-ICP-SOCKET-INTERNAL53IyRECLAIM");
    string_constant_44 = 
	    STATIC_STRING("-QUEUE-INTERNAL53dyRECLAIM-RECEIVING-RESUMABLE-OBJECT-INTERNAL53eyRECLAIM-REMOTE-PROCEDURE-ITEM-PASSING-INFO-153YyRECLAIM-REMOTE");
    string_constant_45 = 
	    STATIC_STRING("-PROCEDURE-NAME-INTERNAL53UyRECLAIM-SKIP-LIST-ELEMENT-INTERNAL53QyRECLAIM-TEXT-SEQUENCE-INTERNAL53NyREMOTE-PROCEDURE-IDENTIFIER5");
    string_constant_46 = 
	    STATIC_STRING("3RyREMOTE-PROCEDURE-IDENTIFIER-TAG53HyREMOTE-PROCEDURE-NAME53OyREMOTE-PROCEDURE-NAME-SYMBOL53KyRESUMABLE-ICP-NODE-MIXIN53MyRESUM");
    string_constant_47 = 
	    STATIC_STRING("ABLE-ICP-OBJECT-MIXIN5xSCHEDULE-TASK53FySCHEDULE-TASK-ARG-153KySCHEDULE-TASK-ARG-OFFSET53aySCHEDULE-TASK-RECLAIMABLE-BY-SCHEDULE");
    string_constant_48 = 
	    STATIC_STRING("R-P53GySHIFT-JIS-TRANSCODER53DySKIP-LIST-ELEMENT53JySKIP-LIST-ELEMENT-ENTRY53PySKIP-LIST-ELEMENT-HASH-NUMBER53HySKIP-LIST-ELEMEN");
    string_constant_49 = 
	    STATIC_STRING("T-KEY53NySKIP-LIST-ELEMENT-TOP-LEVELk5rKEYWORD5vSLOT-OFFSETk5mAB5vSYMBOL-TREE53EyTEMPORARY-CONSTANT53RyTRANSCODE-TEXT-CONVERSION");
    string_constant_50 = 
	    STATIC_STRING("-STYLE53IyTYPE-OF-ICP-CONNECTION5xUNICODE-BLOCK53RyUNICODE-BYTE-SWAPPED-TRANSCODER53EyUNICODE-TRANSCODER53KyUNICODE-UCS-2-TRANSC");
    string_constant_51 = 
	    STATIC_STRING("ODER5sUS-ASCII53CyUTF-7-TRANSCODER53CyUTF-8-TRANSCODER53cyUTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER5qUacute5vUcircumflex5uUdiae");
    string_constant_52 = 
	    STATIC_STRING("resis5tUdieresis5qUgrave5vWIDE-STRING53LyWIDE-STRING-TEXT-SEQUENCE5qaacute5vacircumflex5uadiaeresis5tadieresis5mae5qagrave5parin");
    string_constant_53 = 
	    STATIC_STRING("g5uasciitilde5mat5qatilde5tbackslash5qbullet5sccedilla5ocent5tcopyright5qeacute5vecircumflex5uediaeresis5tedieresis5qegrave5uexc");
    string_constant_54 = 
	    STATIC_STRING("lamdown5qflorin5ugermandbls5xguillemotleft5yguillemotright5qiacute5vicircumflex5uidiaeresis5tidieresis5qigrave5qntilde5qoacute5v");
    string_constant_55 = 
	    STATIC_STRING("ocircumflex5todieresis5moe5qograve5qoslash5qotilde5wquestiondown5uregistered5ssterling5ttrademark5quacute5vucircumflex5uudiaeres");
    string_constant_56 = STATIC_STRING("is5tudieresis5qugrave5nyenkk");
    G2int_standard_symbols_for_optimized_constantqm = 
	    g2int_regenerate_standard_symbols(nconc2(list(50,
	    string_constant_2,string_constant_3,string_constant_4,
	    string_constant_5,string_constant_6,string_constant_7,
	    string_constant_8,string_constant_9,string_constant_10,
	    string_constant_11,string_constant_12,string_constant_13,
	    string_constant_14,string_constant_15,string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37,
	    string_constant_38,string_constant_39,string_constant_40,
	    string_constant_41,string_constant_42,string_constant_43,
	    string_constant_44,string_constant_45,string_constant_46,
	    string_constant_47,string_constant_48,string_constant_49,
	    string_constant_50,string_constant_51),
	    LIST_5(string_constant_52,string_constant_53,
	    string_constant_54,string_constant_55,string_constant_56)));
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
}
