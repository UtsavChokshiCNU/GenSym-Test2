/* glbscs.c
 * Input file:  glbasics.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "glbscs.h"


Object Debug_1 = UNBOUND;

Object Debug_2 = UNBOUND;

Object Debug_3 = UNBOUND;

Object Debug_4 = UNBOUND;

Object Debug_5 = UNBOUND;

Object Debug_6 = UNBOUND;

Object Debug_7 = UNBOUND;

Object Debug_8 = UNBOUND;

Object Debug_9 = UNBOUND;

Object Debug_10 = UNBOUND;

Object Debug_11 = UNBOUND;

Object Debug_12 = UNBOUND;

Object Lisp_package_1 = UNBOUND;

Object Keyword_package_1 = UNBOUND;

Object Within_managed_object_scope = UNBOUND;

Object Reusable_gensyms = UNBOUND;

static Object Qreusable_gensyms;   /* reusable-gensyms */

/* REUSABLE-GENSYMS */
Object reusable_gensyms()
{
    x_note_fn_call(7,0);
    if (BOUNDP(Qreusable_gensyms))
	return VALUES_1(Reusable_gensyms);
    else {
	Reusable_gensyms = LIST_1(ab_gensym(0));
	return VALUES_1(Reusable_gensyms);
    }
}

Object Available_reusable_gensyms = UNBOUND;

/* GENSYM-GENSYM */
Object gensym_gensym()
{
    Object temp, cdr_new_value, available_reusable_gensyms_old_value, temp_1;

    x_note_fn_call(7,1);
    if ( !TRUEP(Available_reusable_gensyms))
	return ab_gensym(0);
    else {
	if ( !TRUEP(CDR(Available_reusable_gensyms))) {
	    temp = Available_reusable_gensyms;
	    cdr_new_value = LIST_1(ab_gensym(0));
	    M_CDR(temp) = cdr_new_value;
	}
	available_reusable_gensyms_old_value = Available_reusable_gensyms;
	temp_1 = FIRST(available_reusable_gensyms_old_value);
	temp = REST(available_reusable_gensyms_old_value);
	Available_reusable_gensyms = temp;
	return VALUES_1(temp_1);
    }
}

/* FORMAT-SYMBOL */
Object format_symbol varargs_1(int, n)
{
    Object control_string;
    Object args, temp;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(7,2);
    SAVE_STACK();
    INIT_ARGS();
    control_string = REQUIRED_ARG();
    SAVE_ARGS();
    args = REST_ARG();
    temp = SYMBOL_FUNCTION(Qformat);
    result = intern(APPLY_3(temp,Nil,control_string,args),_);
    RESTORE_STACK();
    return result;
}

Object Most_positive_fixnum32_plus_one = UNBOUND;

/* TRUNCATEF-FIRST */
Object truncatef_first(fixnum_init,divisor_fixnum_init)
    Object fixnum_init, divisor_fixnum_init;
{
    SI_Long fixnum, divisor_fixnum, temp;

    x_note_fn_call(7,3);
    fixnum = IFIX(fixnum_init);
    divisor_fixnum = IFIX(divisor_fixnum_init);
    if ((SI_Long)0L == divisor_fixnum)
	return VALUES_1(FIX((SI_Long)0L));
    else if ((SI_Long)0L < fixnum) {
	if ((SI_Long)0L < divisor_fixnum)
	    return VALUES_1(FIX(fixnum / divisor_fixnum));
	else {
	    temp = fixnum /  - divisor_fixnum;
	    return VALUES_1(FIXNUM_NEGATE(FIX(temp)));
	}
    }
    else if ((SI_Long)0L < divisor_fixnum) {
	temp =  - fixnum / divisor_fixnum;
	return VALUES_1(FIXNUM_NEGATE(FIX(temp)));
    }
    else
	return VALUES_1(FIX( - fixnum /  - divisor_fixnum));
}

/* REM-FIXNUMS */
Object rem_fixnums(fixnum_init,fixnum_divisor_init)
    Object fixnum_init, fixnum_divisor_init;
{
    SI_Long fixnum, fixnum_divisor, temp;

    x_note_fn_call(7,4);
    fixnum = IFIX(fixnum_init);
    fixnum_divisor = IFIX(fixnum_divisor_init);
    if ((SI_Long)0L == fixnum_divisor)
	return VALUES_1(FIX(fixnum));
    else if ((SI_Long)0L > fixnum) {
	if ((SI_Long)0L > fixnum_divisor) {
	    temp =  - fixnum %  - fixnum_divisor;
	    return VALUES_1(FIXNUM_NEGATE(FIX(temp)));
	}
	else {
	    temp =  - fixnum % fixnum_divisor;
	    return VALUES_1(FIXNUM_NEGATE(FIX(temp)));
	}
    }
    else if ((SI_Long)0L > fixnum_divisor)
	return VALUES_1(FIX(fixnum %  - fixnum_divisor));
    else
	return VALUES_1(FIX(fixnum % fixnum_divisor));
}

/* TWO-ARG-LCMF */
Object two_arg_lcmf(n_init,m_init)
    Object n_init, m_init;
{
    Object temp;
    SI_Long n_1, m, temp_1;

    x_note_fn_call(7,5);
    n_1 = IFIX(n_init);
    m = IFIX(m_init);
    temp = FIX(MAX(n_1,m));
    temp_1 = IFIX(truncatef_first(temp,two_arg_gcdf(FIX(n_1),FIX(m))));
    return VALUES_1(FIX(temp_1 * MIN(n_1,m)));
}

/* TWO-ARG-GCDF */
Object two_arg_gcdf(u_init,v_init)
    Object u_init, v_init;
{
    SI_Long u_1, v, k, temp;

    x_note_fn_call(7,6);
    u_1 = IFIX(u_init);
    v = IFIX(v_init);
    if (u_1 == (SI_Long)0L)
	return VALUES_1(FIX(v));
    else if (v == (SI_Long)0L)
	return VALUES_1(FIX(u_1));
    else {
	k = (SI_Long)0L;
	u_1 = ABS(u_1);
	v = ABS(v);
      next_loop:
	if ((SI_Long)1L == ((SI_Long)1L & (u_1 | v)))
	    goto end_loop;
	k = k + (SI_Long)1L;
	u_1 = u_1 >>  -  - (SI_Long)1L;
	v = v >>  -  - (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = (SI_Long)1L == ((SI_Long)1L & u_1) ?  - v : u_1 >>  -  - 
		(SI_Long)1L;
      next_loop_1:
	if ((SI_Long)1L == ((SI_Long)1L & temp)) {
	    if ((SI_Long)0L < temp)
		u_1 = temp;
	    else
		v =  - temp;
	    temp = u_1 - v;
	    if ((SI_Long)0L == temp)
		return VALUES_1(FIX(u_1 << k));
	}
	temp = temp >>  -  - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	return VALUES_1(Qnil);
    }
}

/* G-LOGF */
Object g_logf(y_init)
    Object y_init;
{
    Object n_1;
    SI_Long y, i;

    x_note_fn_call(7,7);
    y = IFIX(y_init);
    i = (SI_Long)0L;
    n_1 = FIX(y >>  -  - (SI_Long)1L);
  next_loop:
    if (IFIX(n_1) >= (SI_Long)1L)
	i = i + (SI_Long)1L;
    else
	goto end_loop;
    n_1 = FIX(IFIX(n_1) >>  -  - (SI_Long)1L);
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(i));
    return VALUES_1(Qnil);
}

Object Negative_fifty_million = UNBOUND;

/* FTRUNCATEE-UP */
Object ftruncatee_up(float_1)
    Object float_1;
{
    double arg, arg_1;

    x_note_fn_call(7,8);
    arg = DOUBLE_FLOAT_TO_DOUBLE(float_1);
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return fceiling(float_1,_);
    else
	return lffloor(float_1,_);
}

static Object float_constant;      /* 0.0 */

/* COERCE-TO-GENSYM-FLOAT-FUNCTION */
Object coerce_to_gensym_float_function(x)
    Object x;
{
    x_note_fn_call(7,9);
    return lfloat(x,float_constant);
}

Object Most_positive_fixnum_as_float = UNBOUND;

Object Most_negative_fixnum_as_float = UNBOUND;

Object Most_positive_fixnum32_as_float = UNBOUND;

Object Most_positive_fixnum32_plus_one_as_float = UNBOUND;

Object Rational_float_epsilon = UNBOUND;

Object Most_positive_int64 = UNBOUND;

Object Most_negative_int64 = UNBOUND;

Object Destination_for_symbol_with_preserved_cells = UNBOUND;

Object List_of_symbols_for_symbol_value = UNBOUND;

Object List_of_funcalled_functions = UNBOUND;

/* MEMQ-FUNCTION */
Object memq_function(key,list_1)
    Object key, list_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(7,10);
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

/* EQ-OR-MEMQ */
Object eq_or_memq(x,y)
    Object x, y;
{
    x_note_fn_call(7,11);
    if (ATOM(y))
	return VALUES_1(EQ(x,y) ? T : Nil);
    else
	return memq_function(x,y);
}

/* MEMBER-EQUAL */
Object ab_member_equal(key,list_1)
    Object key, list_1;
{
    Object current_cons, temp;

    x_note_fn_call(7,12);
    current_cons = list_1;
  next_loop:
    if ( !TRUEP(current_cons))
	goto end_loop;
    temp = M_CAR(current_cons);
    if (EQUAL(temp,key))
	return VALUES_1(current_cons);
    current_cons = M_CDR(current_cons);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ASSQ-FUNCTION */
Object assq_function(key,a_list)
    Object key, a_list;
{
    Object gensymed_symbol, ab_loop_list_, temp;

    x_note_fn_call(7,13);
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
Object ab_assoc_equal(key,list_1)
    Object key, list_1;
{
    Object alist_entry, ab_loop_list_, temp;

    x_note_fn_call(7,14);
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

/* ASSOC-EQL */
Object ab_assoc_eql(key,list_1)
    Object key, list_1;
{
    Object alist_entry, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(7,15);
    alist_entry = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (alist_entry) {
	temp = M_CAR(alist_entry);
	temp_1 = EQL(temp,key);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(alist_entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GETFQ-FUNCTION-NO-DEFAULT */
Object getfq_function_no_default(plist,indicator)
    Object plist, indicator;
{
    Object list_1;

    x_note_fn_call(7,16);
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
Object getfq_function(plist,indicator,default_1)
    Object plist, indicator, default_1;
{
    Object list_1;

    x_note_fn_call(7,17);
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
Object star_f_safe(arg1,arg2)
    Object arg1, arg2;
{
    Object temp;
    char temp_3;
    double temp_1, temp_2, float_result, arg, arg_1;

    x_note_fn_call(7,18);
    temp = lfloat(arg1,float_constant);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = lfloat(arg2,float_constant);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    float_result = temp_1 * temp_2;
    arg = float_result;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
    temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_3);
    else {
	arg = float_result;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    temp = temp_3 ? Nil : LONG_TO_FIXNUM(inline_floor_1(float_result));
    return VALUES_1(temp);
}

Object Special_variable_for_use_value_macro = UNBOUND;

/* %POINTER */
Object pct_pointer(lisp_object)
    Object lisp_object;
{
    x_note_fn_call(7,19);
    return VALUES_1(PCT_POINTER_1(lisp_object));
}

/* PRINT-RANDOM-OBJECT-PREFIX */
Object print_random_object_prefix(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,20);
    return format((SI_Long)2L,stream,"#<");
}

/* PRINT-RANDOM-OBJECT-SUFFIX */
Object print_random_object_suffix(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,21);
    return format((SI_Long)3L,stream," ~x>",pct_pointer(object));
}

/* PRINT-RANDOM-OBJECT-PREFIX-FOR-GSI */
Object print_random_object_prefix_for_gsi(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,22);
    return format((SI_Long)2L,T,"#<");
}

/* PRINT-RANDOM-OBJECT-SUFFIX-FOR-GSI */
Object print_random_object_suffix_for_gsi(object,stream)
    Object object, stream;
{
    x_note_fn_call(7,23);
    return format((SI_Long)3L,T," ~x>",pct_pointer(object));
}

Object Optimized_constant_vector = UNBOUND;

Object Optimized_constant_vector_index = UNBOUND;

Object Optimized_constant_pc = UNBOUND;

Object Optimized_constant_op_codes = UNBOUND;

/* REGENERATE-STANDARD-SYMBOLS */
Object regenerate_standard_symbols(standard_symbols_input)
    Object standard_symbols_input;
{
    Object optimized_constant_pc, optimized_constant_op_codes, new_array;
    Object package_name_1, package, symbol_name_1, svref_new_value;
    SI_Long index_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(7,24);
    if (standard_symbols_input) {
	optimized_constant_pc = FIX((SI_Long)0L);
	PUSH_SPECIAL(Optimized_constant_pc,optimized_constant_pc,1);
	  optimized_constant_op_codes = standard_symbols_input;
	  PUSH_SPECIAL(Optimized_constant_op_codes,optimized_constant_op_codes,
		  0);
	    new_array = make_array(1,read_optimized_constant());
	    index_1 = (SI_Long)0L;
	    package_name_1 = Nil;
	    package = Nil;
	  next_loop:
	    package_name_1 = read_optimized_constant();
	    if (FIXNUMP(package_name_1))
		goto end_loop;
	    package = find_package(package_name_1);
	    symbol_name_1 = Nil;
	  next_loop_1:
	    symbol_name_1 = read_optimized_constant();
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

Object Standard_symbols_for_optimized_constant_qm = UNBOUND;

/* CLEAR-OPTIMIZED-CONSTANTS */
Object clear_optimized_constants()
{
    x_note_fn_call(7,25);
    Optimized_constant_vector_index = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

/* PUSH-OPTIMIZED-CONSTANT */
Object push_optimized_constant(constant)
    Object constant;
{
    Object temp, svref_arg_2;

    x_note_fn_call(7,26);
    if (FIXNUM_GE(Optimized_constant_vector_index,
	    SIMPLE_ARRAY_ANY_1_LENGTH(Optimized_constant_vector)))
	error((SI_Long)2L,
		"Error initializing constants, vector overflow at ~a.",
		Optimized_constant_vector_index);
    temp = Optimized_constant_vector;
    svref_arg_2 = Optimized_constant_vector_index;
    SVREF(temp,svref_arg_2) = constant;
    temp = FIXNUM_ADD1(Optimized_constant_vector_index);
    Optimized_constant_vector_index = temp;
    return VALUES_1(Nil);
}

/* REGENERATE-OPTIMIZED-CONSTANT */
Object regenerate_optimized_constant(op_codes)
    Object op_codes;
{
    Object temp;

    x_note_fn_call(7,27);
    Optimized_constant_pc = FIX((SI_Long)0L);
    Optimized_constant_op_codes = op_codes;
    temp = read_optimized_constant();
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* READ-OPTIMIZED-CONSTANT */
Object read_optimized_constant()
{
    Object op_code_string, temp, temp_1, new_list, cons_1, trailer;
    Object digit_char_1, new_vector, new_string;
    SI_Long new_fixnum, new_bits, vector_length, index_1, ab_loop_bind_;
    SI_Long string_length, aref_new_value;
    char op_code_char, dispatch_char;

    x_note_fn_call(7,28);
    op_code_string = CONSP(Optimized_constant_op_codes) ? 
	    M_CAR(Optimized_constant_op_codes) : Optimized_constant_op_codes;
    op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
	    Optimized_constant_pc));
    temp = FIXNUM_ADD1(Optimized_constant_pc);
    Optimized_constant_pc = temp;
    if (FIXNUM_GE(Optimized_constant_pc,
	    SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	Optimized_constant_pc = FIX((SI_Long)0L);
	if (CONSP(Optimized_constant_op_codes))
	    Optimized_constant_op_codes = M_CDR(Optimized_constant_op_codes);
	else
	    Optimized_constant_op_codes = Nil;
    }
    dispatch_char = op_code_char;
    switch (dispatch_char) {
      case '0':
	temp_1 = Nil;
	break;
      case '1':
	new_list = make_list(1,read_optimized_constant());
	cons_1 = new_list;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	temp = read_optimized_constant();
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
	new_list = make_list(1,read_optimized_constant());
	trailer = Nil;
	cons_1 = new_list;
      next_loop_1:
	if ( !TRUEP(cons_1))
	    goto end_loop_1;
	temp = read_optimized_constant();
	M_CAR(cons_1) = temp;
	trailer = cons_1;
	cons_1 = M_CDR(cons_1);
	goto next_loop_1;
      end_loop_1:
	temp = read_optimized_constant();
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
	op_code_string = CONSP(Optimized_constant_op_codes) ? 
		M_CAR(Optimized_constant_op_codes) : 
		Optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		Optimized_constant_pc));
	temp = FIXNUM_ADD1(Optimized_constant_pc);
	Optimized_constant_pc = temp;
	if (FIXNUM_GE(Optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    Optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(Optimized_constant_op_codes))
		Optimized_constant_op_codes = 
			M_CDR(Optimized_constant_op_codes);
	    else
		Optimized_constant_op_codes = Nil;
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
	vector_length = IFIX(read_optimized_constant());
	new_vector = make_array(1,FIX(vector_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = vector_length;
      next_loop_3:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_3;
	temp = read_optimized_constant();
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
	string_length = IFIX(read_optimized_constant());
	new_string = make_string(1,FIX(string_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_4:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_4;
	op_code_string = CONSP(Optimized_constant_op_codes) ? 
		M_CAR(Optimized_constant_op_codes) : 
		Optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		Optimized_constant_pc));
	temp = FIXNUM_ADD1(Optimized_constant_pc);
	Optimized_constant_pc = temp;
	if (FIXNUM_GE(Optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    Optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(Optimized_constant_op_codes))
		Optimized_constant_op_codes = 
			M_CDR(Optimized_constant_op_codes);
	    else
		Optimized_constant_op_codes = Nil;
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
	op_code_string = CONSP(Optimized_constant_op_codes) ? 
		M_CAR(Optimized_constant_op_codes) : 
		Optimized_constant_op_codes;
	op_code_char = CHARACTER_TO_CHAR(SCHAR(op_code_string,
		Optimized_constant_pc));
	temp = FIXNUM_ADD1(Optimized_constant_pc);
	Optimized_constant_pc = temp;
	if (FIXNUM_GE(Optimized_constant_pc,
		SIMPLE_ARRAY_ANY_1_LENGTH(op_code_string))) {
	    Optimized_constant_pc = FIX((SI_Long)0L);
	    if (CONSP(Optimized_constant_op_codes))
		Optimized_constant_op_codes = 
			M_CDR(Optimized_constant_op_codes);
	    else
		Optimized_constant_op_codes = Nil;
	}
	temp_1 = CHAR_TO_CHARACTER(op_code_char);
	break;
      case '7':
	string_length = IFIX(read_optimized_constant());
	new_string = make_string(1,FIX(string_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = string_length;
      next_loop_5:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_5;
	temp = CODE_CHAR(read_optimized_constant());
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
	temp_1 = Standard_symbols_for_optimized_constant_qm;
	temp_1 = ISVREF(temp_1,IFIX(read_optimized_constant()));
	break;
      case '9':
	temp_1 = Optimized_constant_vector;
	temp_1 = ISVREF(temp_1,IFIX(read_optimized_constant()));
	break;
      case '+':
	vector_length = IFIX(read_optimized_constant());
	new_vector = make_array(3,FIX(vector_length),Kelement_type,
		list_constant);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = vector_length;
      next_loop_6:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_6;
	aref_new_value = IFIX(read_optimized_constant());
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
	temp_1 = CHAR_GE(CHAR_TO_CHARACTER(dispatch_char),CHR('a')) && 
		CHAR_LE(CHAR_TO_CHARACTER(dispatch_char),CHR('z')) ? 
		FIX(IFIX(FIXNUM_MINUS(CHAR_CODE(CHAR_TO_CHARACTER(dispatch_char)),
		CHAR_CODE(CHR('a')))) - (SI_Long)10L) : error((SI_Long)2L,
		"Error reading constant, bad dispatch char = ~s",
		CHAR_TO_CHARACTER(dispatch_char));
	break;
    }
    return VALUES_1(temp_1);
}

void glbasics_INIT()
{
    Object integer, temp_1;
    SI_int64 long_1, zero;
    double temp;
    Object string_constant_131, string_constant_130, string_constant_129;
    Object string_constant_128, string_constant_127, string_constant_126;
    Object string_constant_125, string_constant_124, string_constant_123;
    Object string_constant_122, string_constant_121, string_constant_120;
    Object string_constant_119, string_constant_118, string_constant_117;
    Object string_constant_116, string_constant_115, string_constant_114;
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
    Object string_constant_2, Qoptimized_constant_vector_length, AB_package;
    Object float_constant_1, Qrational_float_epsilon, Qmost_negative_fixnum32;
    Object Qmost_positive_fixnum32, string_constant_1, string_constant;

    x_note_fn_call(7,29);
    SET_PACKAGE("AB");
    if (Debug_1 == UNBOUND)
	Debug_1 = Nil;
    if (Debug_2 == UNBOUND)
	Debug_2 = Nil;
    if (Debug_3 == UNBOUND)
	Debug_3 = Nil;
    if (Debug_4 == UNBOUND)
	Debug_4 = Nil;
    if (Debug_5 == UNBOUND)
	Debug_5 = Nil;
    if (Debug_6 == UNBOUND)
	Debug_6 = Nil;
    if (Debug_7 == UNBOUND)
	Debug_7 = Nil;
    if (Debug_8 == UNBOUND)
	Debug_8 = Nil;
    if (Debug_9 == UNBOUND)
	Debug_9 = Nil;
    if (Debug_10 == UNBOUND)
	Debug_10 = Nil;
    if (Debug_11 == UNBOUND)
	Debug_11 = Nil;
    if (Debug_12 == UNBOUND)
	Debug_12 = Nil;
    string_constant = STATIC_STRING("COMMON-LISP");
    if (Lisp_package_1 == UNBOUND)
	Lisp_package_1 = find_package(string_constant);
    string_constant_1 = STATIC_STRING("KEYWORD");
    if (Keyword_package_1 == UNBOUND)
	Keyword_package_1 = find_package(string_constant_1);
    if (Within_managed_object_scope == UNBOUND)
	Within_managed_object_scope = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qreusable_gensyms = STATIC_SYMBOL("REUSABLE-GENSYMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreusable_gensyms,Reusable_gensyms);
    SET_SYMBOL_FUNCTION(Qreusable_gensyms,STATIC_FUNCTION(reusable_gensyms,
	    NIL,FALSE,0,0));
    if (Available_reusable_gensyms == UNBOUND)
	Available_reusable_gensyms = Nil;
    Qmost_positive_fixnum32 = STATIC_SYMBOL("MOST-POSITIVE-FIXNUM32",
	    AB_package);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum32,FIX((SI_Long)536870911L));
    Qmost_negative_fixnum32 = STATIC_SYMBOL("MOST-NEGATIVE-FIXNUM32",
	    AB_package);
    SET_SYMBOL_VALUE(Qmost_negative_fixnum32,FIX((SI_Long)-536870912L));
    Most_positive_fixnum32_plus_one = add1(Most_positive_fixnum32);
    Negative_fifty_million = FIX((SI_Long)-50000000L);
    float_constant = STATIC_FLOAT(0.0);
    Most_positive_fixnum_as_float = 
	    coerce_to_gensym_float_function(Most_positive_fixnum);
    Most_negative_fixnum_as_float = 
	    coerce_to_gensym_float_function(Most_negative_fixnum);
    Most_positive_fixnum32_as_float = 
	    coerce_to_gensym_float_function(Most_positive_fixnum32);
    temp = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_as_float);
    Most_positive_fixnum32_plus_one_as_float = DOUBLE_TO_DOUBLE_FLOAT(temp 
	    + 1.0);
    Qrational_float_epsilon = STATIC_SYMBOL("RATIONAL-FLOAT-EPSILON",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrational_float_epsilon,Rational_float_epsilon);
    float_constant_1 = STATIC_FLOAT(1.0E-6);
    SET_SYMBOL_VALUE(Qrational_float_epsilon,float_constant_1);
    integer = sub1(ltimes(FIX((SI_Long)2097152L),
	    ltimes(FIX((SI_Long)2097152L),FIX((SI_Long)2097152L))));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    Most_positive_int64 = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
    Most_negative_int64 = sub1(negate(Most_positive_int64));
    if (Destination_for_symbol_with_preserved_cells == UNBOUND)
	Destination_for_symbol_with_preserved_cells = Nil;
    if (List_of_symbols_for_symbol_value == UNBOUND)
	List_of_symbols_for_symbol_value = Nil;
    if (List_of_funcalled_functions == UNBOUND)
	List_of_funcalled_functions = Nil;
    if (Special_variable_for_use_value_macro == UNBOUND)
	Special_variable_for_use_value_macro = Nil;
    Qoptimized_constant_vector_length = 
	    STATIC_SYMBOL("OPTIMIZED-CONSTANT-VECTOR-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qoptimized_constant_vector_length,FIX((SI_Long)1300L));
    if (Optimized_constant_vector == UNBOUND)
	Optimized_constant_vector = make_array(1,
		Optimized_constant_vector_length);
    if (Optimized_constant_vector_index == UNBOUND)
	Optimized_constant_vector_index = FIX((SI_Long)0L);
    if (Optimized_constant_pc == UNBOUND)
	Optimized_constant_pc = FIX((SI_Long)0L);
    if (Optimized_constant_op_codes == UNBOUND)
	Optimized_constant_op_codes = Nil;
    string_constant_2 = 
	    STATIC_STRING("37jy5vCOMMON-LISP5lTk53NyG2-DEFSTRUCT-STRUCTURE-NAME53MyTYPE-DESCRIPTION-G2-STRUCTk5mAB53IyNAMED-GENSYM-STRUCTUREk5rKEYWORD5vCON");
    string_constant_3 = 
	    STATIC_STRING("STRUCTORk5mAB5tSTRUCTUREk5rKEYWORD5rINCLUDE5tRECLAIMERk5mAB53HyGRAPHIC-CHARACTER-SET53cyGRAPHIC-CHARACTER-SET-CHARACTERS-PER-OCT");
    string_constant_4 = 
	    STATIC_STRING("ET53QyGRAPHIC-CHARACTER-SET-N-OCTETS53MyGRAPHIC-CHARACTER-SET-NAME53dyGRAPHIC-CHARACTER-SET-REGISTRATION-SEQUENCE53QyGRAPHIC-CHA");
    string_constant_5 = 
	    STATIC_STRING("RACTER-SET-SYNONYMS53DyISO-8859-ABSTRACT5uTRANSCODER53Cy8859-PART-NUMBER53JyREGULAR-EXPRESSION-NODE5vLRU-ELEMENTk5rKEYWORD53IyEL");
    string_constant_6 = 
	    STATIC_STRING("IMINATE-FOR-PRODUCTS5oTYPE53FyCREATIONS-AT-A-TIMEk5mAB5nGSI53DyASIAN-DOUBLE-BYTE53XyMULTIPLY-WILD-REGULAR-EXPRESSION-NODEk5vCOMM");
    string_constant_7 = 
	    STATIC_STRING("ON-LISP5xSIMPLE-VECTORk5rKEYWORD5yPRINT-FUNCTIONk5mAB5xNATIVE-WINDOW5xTEXT-SEQUENCEk5rKEYWORD5tPREDICATEk5mAB53CyPENDING-ACTIVIT");
    string_constant_8 = 
	    STATIC_STRING("Y53DyRING-BUFFER-STATE5qSOCKET53CyUTF-G-TRANSCODER5vWORKSTATION53LyCHARACTER-RECTANGLE-ARRAY53FyCHARACTER-SET-WIDTH53TyCONTINUAT");
    string_constant_9 = 
	    STATIC_STRING("ION-OF-PENDING-ACTIVITY\?53KyNAME-OF-PENDING-ACTIVITY5vNATIVE-VIEW53NyPARENT-OF-PENDING-ACTIVITY\?k5vCOMMON-LISP5wSIMPLE-ARRAYk5mA");
    string_constant_10 = 
	    STATIC_STRING("B53LyTEXT-SEQUENCE-STRING-TYPE53RyTRANSCODE-TEXT-CONVERSION-STYLE53IyWINDOW-FOR-WORKSTATION53FyBINARY-TREE-ELEMENT5wBITMAP-ARRAY");
    string_constant_11 = 
	    STATIC_STRING("53HyCHARACTER-DESCRIPTION5zCHARACTER-IMAGE5tCOLOR-MAP5xEQ-HASH-TABLE5uERROR-CODE53NyFILENAME-PARSER-INFORMATION53FyFOREIGN-STRUC");
    string_constant_12 = 
	    STATIC_STRING("T-INFO53KyFUTURE-TASK-QUEUE-HOLDER53FyG2-STREAM-STRUCTURE5rGB-231253GyGENSYM-STRING-STREAM53NyGENSYM-STRING-TEXT-SEQUENCE5xGENSY");
    string_constant_13 = 
	    STATIC_STRING("M-WINDOW5zGRAPH-RENDERING5tHALT-INFO5zI-AM-ALIVE-INFO5yICON-RENDERING5uICP-BUFFER5sICP-PORT5xICP-READ-TASK5uICP-SOCKET5yICP-WRIT");
    string_constant_14 = 
	    STATIC_STRING("E-TASK53NyIDENTIFIED-DRAWING-ACTIVITY5uIMAGE-DATA5zIMAGE-RENDERING5uIMAGE-TILE5vINDEX-SPACE5xINTERNED-LIST53FyISO-2022-TRANSCODE");
    string_constant_15 = 
	    STATIC_STRING("R5rISO-6465uISO-8859-15vISO-8859-105uISO-8859-25uISO-8859-35uISO-8859-45uISO-8859-55uISO-8859-65uISO-8859-75uISO-8859-85uISO-885");
    string_constant_16 = 
	    STATIC_STRING("9-953FyISO-8859-TRANSCODER5uJIS-X-02085tKS-C-560153KyLARGE-SCALED-FONT-BUCKET5vLOCAL-EVENT53DyMEMORY-LIMIT-INFO53PyMINIMAL-CHARA");
    string_constant_17 = 
	    STATIC_STRING("CTER-DESCRIPTION5vNATIVE-FONT5sNMS-MENU5xNMS-MENU-ITEM5qPIXMAP5pQUEUE5xQUEUE-ELEMENT53KyREGION-BOUNDS-AND-RASTER53fyREGULAR-EXPR");
    string_constant_18 = 
	    STATIC_STRING("ESSION-NODE-FOR-SET-OF-CHARACTERS53eyREGULAR-EXPRESSION-NODE-FOR-SINGLE-CHARACTER53jyREGULAR-EXPRESSION-NODE-FOR-SINGLE-WILD-CHA");
    string_constant_19 = 
	    STATIC_STRING("RACTER53byREGULAR-EXPRESSION-NODE-FOR-SUBEXPRESSION53dyREGULAR-EXPRESSION-NODE-FOR-WILD-CHARACTERS53HyRING-RASTER-FOR-GRAPH5vSCA");
    string_constant_20 = 
	    STATIC_STRING("LED-FONT5xSCHEDULE-TASK53GySHIFT-JIS-TRANSCODER5zSHREDDED-RASTER53DySKIP-LIST-ELEMENT5wSPARSE-ARRAY5vSYMBOL-TREE53JyTELEWINDOWS-");
    string_constant_21 = 
	    STATIC_STRING("WORKSTATION53EyTEMPORARY-CONSTANT53NyTHRASHING-RATIO-RING-BUFFER5wTILED-RASTER5yTILING-PATTERN53CyTYPE-DESCRIPTION5xUNICODE-BLOC");
    string_constant_22 = 
	    STATIC_STRING("K53RyUNICODE-BYTE-SWAPPED-TRANSCODER53EyUNICODE-TRANSCODER53KyUNICODE-UCS-2-TRANSCODERk5vCOMMON-LISP5xUNSIGNED-BYTEk5mAB53CyUTF-");
    string_constant_23 = 
	    STATIC_STRING("7-TRANSCODER53CyUTF-8-TRANSCODER53cyUTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER53LyWIDE-STRING-TEXT-SEQUENCE5yWORKSPACE-VIEW5rAB-");
    string_constant_24 = 
	    STATIC_STRING("FONT53CyAB-FONT-BASELINE53JyAB-FONT-FOR-SCALED-FONT53IyAB-FONT-MAXIMUM-HEIGHT53HyAB-FONT-MAXIMUM-WIDTH5wAB-FONT-NAME5wAB-FONT-SI");
    string_constant_25 = 
	    STATIC_STRING("ZE5wAB-FONT-TYPE5mAE53HyALLOCATE-SPARSE-ARRAY5rANSI3.45xANTIQUE-WHITE5uAQUAMARINE53UyARG-OF-IDENTIFIED-DRAWING-ACTIVITY53HyARRAY");
    string_constant_26 = 
	    STATIC_STRING("-OF-BITMAPS-USED5pASCII5pAZURE5qAacute5vAcircumflex5uAdiaeresis5tAdieresis5qAgrave5pAring5qAtilde5yBALANCE-FACTOR5pBEIGE53GyBINA");
    string_constant_27 = 
	    STATIC_STRING("RY-ELEMENT-ALIST53MyBINARY-ELEMENT-HASH-NUMBER5pBLACK5oBLUE53FyBOUNDING-BOX-HEIGHT53EyBOUNDING-BOX-WIDTH53HyBOUNDING-BOX-X-OFFSE");
    string_constant_28 = 
	    STATIC_STRING("T53HyBOUNDING-BOX-Y-OFFSET5pBROWN53FyByelorussian_SHORTU5uCADET-BLUE53IyCHARACTER-IMAGE-HEIGHT53SyCHARACTER-IMAGE-ORIENTATION-CO");
    string_constant_29 = 
	    STATIC_STRING("DE53ZyCHARACTER-IMAGE-SET-WIDTH-AS-TEXT-WIDTH53PyCHARACTER-IMAGE-TEXT-X-OFFSET53HyCHARACTER-IMAGE-WIDTH53KyCHARACTER-IMAGE-Y-OFF");
    string_constant_30 = 
	    STATIC_STRING("SET53CyCHARACTER-RASTER53IyCOLOR-MAP-TRUE-COLOR-P53IyCOLOR-VALUE-FOR-BLACK\?53IyCOLOR-VALUE-FOR-WHITE\?53DyCOLOR-VALUE-PLIST53EyCO");
    string_constant_31 = 
	    STATIC_STRING("LOR-VALUE-VECTOR53QyCOMPILED-REGULAR-SUBEXPRESSION53HyCOMPUTED-VALUES-PLIST5xCONSTANT-TYPE53JyCONSTANT-VALUE-INTERNAL5pCORAL53Uy");
    string_constant_32 = 
	    STATIC_STRING("CORRESPONDING-GRAPH-GRID-OR-CHART\?53RyCORRESPONDING-ICON-DESCRIPTION\?53YyCREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS5oCYAN5sCcedilla5");
    string_constant_33 = 
	    STATIC_STRING("uCyrillic_A5vCyrillic_BE5wCyrillic_CHE5vCyrillic_DE5xCyrillic_DZHE5uCyrillic_E5vCyrillic_EF5vCyrillic_EL5vCyrillic_EM5vCyrillic_");
    string_constant_34 = 
	    STATIC_STRING("EN5vCyrillic_ER5vCyrillic_ES5wCyrillic_GHE5vCyrillic_HA53DyCyrillic_HARDSIGN5uCyrillic_I5vCyrillic_IE5vCyrillic_IO5vCyrillic_JE5");
    string_constant_35 = 
	    STATIC_STRING("vCyrillic_KA5wCyrillic_LJE5wCyrillic_NJE5uCyrillic_O5vCyrillic_PE5wCyrillic_SHA5yCyrillic_SHCHA5zCyrillic_SHORTI53DyCyrillic_SOF");
    string_constant_36 = 
	    STATIC_STRING("TSIGN5vCyrillic_TE5wCyrillic_TSE5uCyrillic_U5vCyrillic_VE5vCyrillic_YA5xCyrillic_YERU5vCyrillic_YU5vCyrillic_ZE5wCyrillic_ZHE5uC");
    string_constant_37 = 
	    STATIC_STRING("yrillic_a5vCyrillic_be5wCyrillic_che5vCyrillic_de5xCyrillic_dzhe5uCyrillic_e5vCyrillic_ef5vCyrillic_el5vCyrillic_em5vCyrillic_en");
    string_constant_38 = 
	    STATIC_STRING("5vCyrillic_er5vCyrillic_es5wCyrillic_ghe5vCyrillic_ha53DyCyrillic_hardsign5uCyrillic_i5vCyrillic_ie5vCyrillic_io5vCyrillic_je5vC");
    string_constant_39 = 
	    STATIC_STRING("yrillic_ka5wCyrillic_lje5wCyrillic_nje5uCyrillic_o5vCyrillic_pe5wCyrillic_sha5yCyrillic_shcha5zCyrillic_shorti53DyCyrillic_softs");
    string_constant_40 = 
	    STATIC_STRING("ign5vCyrillic_te5wCyrillic_tse5uCyrillic_u5vCyrillic_ve5vCyrillic_ya5xCyrillic_yeru5vCyrillic_yu5vCyrillic_ze5wCyrillic_zhe5tDAR");
    string_constant_41 = 
	    STATIC_STRING("K-GRAY5zDARK-SLATE-BLUE5sDIM-GRAY53GyDO-NOTHING-RECLAIMER53FyERROR-FORMAT-STRING5yERROR-SEVERITY53CyEXTRA-LIGHT-GRAY5qEacute5vEc");
    string_constant_42 = 
	    STATIC_STRING("ircumflex5uEdiaeresis5tEdieresis5qEgrave5wFLORAL-WHITE5wFOREST-GREEN53VyFORMAT-OF-GRAPH-RENDERING-STRUCTURE53CyG2-STREAM-HANDLE5");
    string_constant_43 = 
	    STATIC_STRING("mGB5qGB23125wGENSYM-FLOAT53IyGENSYM-PATHNAME-DEVICE53LyGENSYM-PATHNAME-DIRECTORY53GyGENSYM-PATHNAME-HOST53GyGENSYM-PATHNAME-NAME");
    string_constant_44 = 
	    STATIC_STRING("53GyGENSYM-PATHNAME-TYPE53JyGENSYM-PATHNAME-VERSION5xGENSYM-STRING53PyGENSYM-WINDOW-FOR-SCALED-FONT53SyGENSYM-WINDOW-FOR-TILING-");
    string_constant_45 = 
	    STATIC_STRING("PATTERN53eyGENSYM-WINDOW-OF-IDENTIFIED-DRAWING-ACTIVITY5oGOLD5tGOLDENROD53JyGRAPH-RENDERING-PARENT\?5oGRAY53FyGREATER-THAN-BRANCH");
    string_constant_46 = 
	    STATIC_STRING("5pGREEN5wGREEN-YELLOW53DyGRID-BORDER-WIDTHk5rKEYWORD5nGSIk5mAB53VyHEIGHT-OF-GRAPH-RENDERING-STRUCTURE53KyHEIGHT-OF-RENDERED-GRAP");
    string_constant_47 = 
	    STATIC_STRING("H53JyHEIGHT-OF-RENDERED-ICON53PyHEIGHT-OF-RENDERING-STRUCTURE53DyICP-BUFFER-VECTOR53HyICP-CONNECTION-HANDLE53FyICP-CONNECTION-NA");
    string_constant_48 = 
	    STATIC_STRING("ME53GyICP-CONNECTION-STATE53EyICP-PORT-DIRECTION53eyICP-READ-TASK-CORRESPONDING-ICP-OBJECT-INDEX53OyICP-SOCKET-LOCAL-SYSTEM-NAME");
    string_constant_49 = 
	    STATIC_STRING("53OyICP-WRITE-TASK-ARGUMENT-LIST53ZyICP-WRITE-TASK-COMPLETION-ARGUMENT-LIST53UyICP-WRITE-TASK-COMPLETION-FUNCTION53fyICP-WRITE-T");
    string_constant_50 = 
	    STATIC_STRING("ASK-CORRESPONDING-ICP-OBJECT-INDEX53JyICP-WRITE-TASK-FUNCTION53UyICP-WRITE-TASK-RESUMABLE-ICP-STATE53HyICP-WRITE-TASK-STARTP53Ty");
    string_constant_51 = 
	    STATIC_STRING("ID-OF-IDENTIFIED-DRAWING-ACTIVITY53CyINDEX-SPACE-NAME53PyINDEX-SPACE-OBJECT-RECLAIMER\?5uINDIAN-RED53FyINTERNED-LIST--LIST5vISO-6");
    string_constant_52 = 
	    STATIC_STRING("46-IRV53QyISO-8859-GRAPHIC-CHARACTER-SET53GyISO-8859-PART-NUMBER5pIVORY5qIacute5vIcircumflex5uIdiaeresis5tIdieresis5qIgrave5nJIS");
    string_constant_53 = 
	    STATIC_STRING("5pKHAKI5mKS5nKSC53gyLARGE-SCALED-FONT-BUCKET-ORIENTED-BUCKET-INDEX5rLATIN-15rLATIN-25rLATIN-35rLATIN-45rLATIN-55rLATIN-65wLATIN-");
    string_constant_54 = 
	    STATIC_STRING("ARABIC5yLATIN-CYRILLIC5vLATIN-GREEK5wLATIN-HEBREW5sLAVENDER53CyLESS-THAN-BRANCH5uLIGHT-BLUE5uLIGHT-CYAN5zLIGHT-GOLDENROD53IyLIGH");
    string_constant_55 = 
	    STATIC_STRING("T-GOLDENROD-YELLOW5uLIGHT-GRAY5uLIGHT-PINK53CyLIGHT-STEEL-BLUE5wLIGHT-YELLOW5uLIME-GREEN53fyLINE-DRAWING-DESCRIPTION-FOR-GRAPH-R");
    string_constant_56 = 
	    STATIC_STRING("ENDERING\?53ZyLINE-DRAWING-DESCRIPTION-FOR-RENDERING\?5pLINEN5zLISTENER-SOCKET53KyLRU-ELEMENT-NEXT-ELEMENT5rMAGENTA53IyMAKE-AB-FON");
    string_constant_57 = 
	    STATIC_STRING("T-STRUCTURE53KyMAKE-BINARY-TREE-ELEMENT53MyMAKE-BITMAP-ARRAY-INTERNAL53MyMAKE-CHARACTER-DESCRIPTION53GyMAKE-CHARACTER-IMAGE53KyM");
    string_constant_58 = 
	    STATIC_STRING("AKE-COLOR-MAP-STRUCTURE53NyMAKE-EQ-HASH-TABLE-INTERNAL5zMAKE-ERROR-CODE53SyMAKE-FILENAME-PARSER-INFORMATION53RyMAKE-FUTURE-TASK-");
    string_constant_59 = 
	    STATIC_STRING("QUEUE-HOLDER-153TyMAKE-G2-STREAM-STRUCTURE-INTERNAL53WyMAKE-GENSYM-PATHNAME-STRUCTURE-MACRO53UyMAKE-GENSYM-STRING-STREAM-INTERNA");
    string_constant_60 = 
	    STATIC_STRING("L53NyMAKE-GENSYM-WINDOW-INTERNAL53PyMAKE-GRAPH-RENDERING-INTERNAL53OyMAKE-ICON-RENDERING-INTERNAL53KyMAKE-ICP-BUFFER-INTERNAL53J");
    string_constant_61 = 
	    STATIC_STRING("yMAKE-ICP-PORT-STRUCTURE53EyMAKE-ICP-READ-TASK53LyMAKE-ICP-SOCKET-STRUCTURE53FyMAKE-ICP-WRITE-TASK53UyMAKE-IDENTIFIED-DRAWING-AC");
    string_constant_62 = 
	    STATIC_STRING("TIVITY-153DyMAKE-IMAGE-DATA-153IyMAKE-IMAGE-RENDERING-153DyMAKE-IMAGE-TILE-153CyMAKE-INDEX-SPACE53EyMAKE-INTERNED-LIST53KyMAKE-I");
    string_constant_63 = 
	    STATIC_STRING("SO-8859-TRANSCODER53YyMAKE-LARGE-SCALED-FONT-BUCKET-INTERNAL53UyMAKE-MINIMAL-CHARACTER-DESCRIPTION53CyMAKE-NATIVE-FONT53GyMAKE-N");
    string_constant_64 = 
	    STATIC_STRING("ATIVE-WINDOW-153HyMAKE-PENDING-ACTIVITY5vMAKE-PIXMAP53EyMAKE-QUEUE-ELEMENT53FyMAKE-QUEUE-INTERNAL53kyMAKE-REGULAR-EXPRESSION-NOD");
    string_constant_65 = 
	    STATIC_STRING("E-FOR-SET-OF-CHARACTERS53jyMAKE-REGULAR-EXPRESSION-NODE-FOR-SINGLE-CHARACTER53oyMAKE-REGULAR-EXPRESSION-NODE-FOR-SINGLE-WILD-CHA");
    string_constant_66 = 
	    STATIC_STRING("RACTER53gyMAKE-REGULAR-EXPRESSION-NODE-FOR-SUBEXPRESSION53iyMAKE-REGULAR-EXPRESSION-NODE-FOR-WILD-CHARACTERS53IyMAKE-RING-BUFFER");
    string_constant_67 = 
	    STATIC_STRING("-STATE53LyMAKE-SCALED-FONT-INTERNAL53EyMAKE-SCHEDULE-TASK53IyMAKE-SHREDDED-RASTER-153IyMAKE-SKIP-LIST-ELEMENT53CyMAKE-SYMBOL-TRE");
    string_constant_68 = 
	    STATIC_STRING("E53OyMAKE-TELEWINDOWS-WORKSTATION53LyMAKE-TEMPORARY-CONSTANT-153NyMAKE-TEXT-SEQUENCE-INTERNAL53SyMAKE-THRASHING-RATIO-RING-BUFFE");
    string_constant_69 = 
	    STATIC_STRING("R53PyMAKE-TILING-PATTERN-STRUCTURE53EyMAKE-UNICODE-BLOCK53HyMAKE-WORKSPACE-VIEW-153CyMAKE-WORKSTATION5qMAROON53DyMEDIUM-AQUAMARI");
    string_constant_70 = 
	    STATIC_STRING("NE5vMEDIUM-BLUE53CyMEDIUM-GOLDENROD5xMEDIUM-ORCHID53IyMEMORY-USED-BY-BITMAPS5xMacedonia_DSE5xMacedonia_GJE5xMacedonia_KJE5xMaced");
    string_constant_71 = 
	    STATIC_STRING("onia_dse5xMacedonia_gje5xMacedonia_kje5yNATIVE-WINDOW\?53EyNMS-RECLAIM-MENU-153JyNMS-RECLAIM-MENU-ITEM-153YyNUMBER-OF-RENDERING-S");
    string_constant_72 = 
	    STATIC_STRING("TRUCTURE-ELEMENTS5qNtilde5mOE5qORANGE5qOacute5vOcircumflex5tOdieresis5qOgrave5qOslash5qOtilde5yPALE-GOLDENROD5uPALE-GREEN5yPALE-");
    string_constant_73 = 
	    STATIC_STRING("TURQUOISE53DyPARENT-ICP-SOCKET53hyPARENT-SCALED-FONT-FOR-LARGE-SCALED-FONT-BUCKET5oPINK5wPIXMAP-DEPTH5xPIXMAP-HEIGHT5yPIXMAP-POI");
    string_constant_74 = 
	    STATIC_STRING("NTER5wPIXMAP-WIDTH5oPLUM5vPOWDER-BLUE53DyPRINT-LOCAL-EVENT5vPRINT-QUEUE53DyPRINT-WORKSTATION5qPURPLE5vQUEUE-DATUM53FyQUEUE-HEAD-");
    string_constant_75 = 
	    STATIC_STRING("INTERNAL53EyQUEUE-NEXT-ELEMENT53IyQUEUE-PREVIOUS-ELEMENT53FyQUEUE-TAIL-INTERNAL53PyRECEIVE-OR-TRANSMIT-DIRECTLY\?53QyRECLAIM-EQ-H");
    string_constant_76 = 
	    STATIC_STRING("ASH-TABLE-INTERNAL53eyRECLAIM-FILENAME-PARSER-INFORMATION-INTERNAL53UyRECLAIM-FUTURE-TASK-QUEUE-HOLDER-153ZyRECLAIM-GENSYM-PATHN");
    string_constant_77 = 
	    STATIC_STRING("AME-STRUCTURE-MACRO53QyRECLAIM-GENSYM-WINDOW-INTERNAL53FyRECLAIM-HALT-INFO-153NyRECLAIM-ICP-BUFFER-INTERNAL53LyRECLAIM-ICP-PORT-");
    string_constant_78 = 
	    STATIC_STRING("INTERNAL53NyRECLAIM-ICP-SOCKET-INTERNAL53XyRECLAIM-IDENTIFIED-DRAWING-ACTIVITY-153GyRECLAIM-IMAGE-DATA-153LyRECLAIM-IMAGE-RENDER");
    string_constant_79 = 
	    STATIC_STRING("ING-153GyRECLAIM-IMAGE-TILE-153HyRECLAIM-LOCAL-EVENT-153JyRECLAIM-NATIVE-WINDOW-153CyRECLAIM-PIXMAP-153IyRECLAIM-QUEUE-INTERNAL5");
    string_constant_80 = 
	    STATIC_STRING("3nyRECLAIM-REGULAR-EXPRESSION-NODE-FOR-SET-OF-CHARACTERS53myRECLAIM-REGULAR-EXPRESSION-NODE-FOR-SINGLE-CHARACTER53ryRECLAIM-REGU");
    string_constant_81 = 
	    STATIC_STRING("LAR-EXPRESSION-NODE-FOR-SINGLE-WILD-CHARACTER53jyRECLAIM-REGULAR-EXPRESSION-NODE-FOR-SUBEXPRESSION53lyRECLAIM-REGULAR-EXPRESSION");
    string_constant_82 = 
	    STATIC_STRING("-NODE-FOR-WILD-CHARACTERS53HyRECLAIM-SCALED-FONT-153LyRECLAIM-SHREDDED-RASTER-153UyRECLAIM-SKIP-LIST-ELEMENT-INTERNAL53IyRECLAIM");
    string_constant_83 = 
	    STATIC_STRING("-SPARSE-ARRAY-153QyRECLAIM-TEXT-SEQUENCE-INTERNAL53PyRECLAIM-TILED-RASTER-INTERNAL53KyRECLAIM-WORKSPACE-VIEW-153OyRECLAIM-WORKST");
    string_constant_84 = 
	    STATIC_STRING("ATION-INTERNAL5nRED53WyREFLECTION-AND-ROTATION-OF-RENDERING53PyREGION-EXTREMA-FOR-RENDERING\?5qSALMON53TySCALED-FONT-CHARACTER-IM");
    string_constant_85 = 
	    STATIC_STRING("AGE-CACHE53FySCALED-FONT-X-SCALE53FySCALED-FONT-Y-SCALE53FySCHEDULE-TASK-ARG-153KySCHEDULE-TASK-ARG-OFFSET53aySCHEDULE-TASK-RECL");
    string_constant_86 = 
	    STATIC_STRING("AIMABLE-BY-SCHEDULER-P53DySHREDDED-RASTER-P5qSIENNA53YySINGLE-CHARACTER-IN-REGULAR-EXPRESSION53JySKIP-LIST-ELEMENT-ENTRY53PySKIP");
    string_constant_87 = 
	    STATIC_STRING("-LIST-ELEMENT-HASH-NUMBER53HySKIP-LIST-ELEMENT-KEY53NySKIP-LIST-ELEMENT-TOP-LEVEL5sSKY-BLUE5uSLATE-BLUEk5rKEYWORD5vSLOT-OFFSETk5");
    string_constant_88 = 
	    STATIC_STRING("mAB5pSMOKE5vSerbian_DJE5wSerbian_TSHE5vSerbian_dje5wSerbian_tshe5rTHISTLE53HyTILING-PATTERN-HEIGHT53XyTILING-PATTERN-ROWS-WITH-C");
    string_constant_89 = 
	    STATIC_STRING("OLOR-VALUES53PyTILING-PATTERN-STORED-RASTER\?53GyTILING-PATTERN-WIDTH53JyTOTAL-NUMBER-OF-BITMAPS53XyTRANSCODE-TEXT-CONVERSION-STY");
    string_constant_90 = 
	    STATIC_STRING("LE-COUNT5tTURQUOISE53IyTYPE-OF-ICP-CONNECTION53HyUNUSED-NODE-RECLAIMER5sUS-ASCII5qUacute5vUcircumflex5uUdiaeresis5tUdieresis5qUg");
    string_constant_91 = 
	    STATIC_STRING("rave5vUkrainian_I5wUkrainian_IE5wUkrainian_YI5vUkrainian_i5wUkrainian_ie5wUkrainian_yi5qVIOLET5uVIOLET-RED5pWHEAT5pWHITE5vWIDE-S");
    string_constant_92 = 
	    STATIC_STRING("TRING53UyWIDTH-OF-GRAPH-RENDERING-STRUCTURE53JyWIDTH-OF-RENDERED-GRAPH53IyWIDTH-OF-RENDERED-ICON53OyWIDTH-OF-RENDERING-STRUCTURE");
    string_constant_93 = 
	    STATIC_STRING("53MyWINDOW-FOR-GRAPH-RENDERING53LyWINDOW-FOR-ICON-RENDERING53MyX-SCALE-OF-GRAPH-RENDERING53GyX-SCALE-OF-RENDERING53MyY-SCALE-OF-");
    string_constant_94 = 
	    STATIC_STRING("GRAPH-RENDERING53GyY-SCALE-OF-RENDERING5qYELLOW5qaacute5vacircumflex5uadiaeresis5tadieresis5mae5qagrave5paring5uasciitilde5mat5q");
    string_constant_95 = 
	    STATIC_STRING("atilde5tbackslash5qbullet5sccedilla5ocent5tcopyright5qeacute5vecircumflex5uediaeresis5tedieresis5qegrave5uexclamdown5qflorin5uge");
    string_constant_96 = 
	    STATIC_STRING("rmandbls5xguillemotleft5yguillemotright5qiacute5vicircumflex5uidiaeresis5tidieresis5qigrave5qntilde5qoacute5vocircumflex5todiere");
    string_constant_97 = 
	    STATIC_STRING("sis5moe5qograve5qoslash5qotilde5wquestiondown5uregistered5ssterling5ttrademark5quacute5vucircumflex5uudiaeresis5tudieresis5qugra");
    string_constant_98 = 
	    STATIC_STRING("ve5nyen53hy8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS53SyADJUSTABLE-GENSYM-STRING-COUNTER53LyADJUSTABLE-GENSYM-STRINGS53SyA");
    string_constant_99 = 
	    STATIC_STRING("LLOCATED-BYTE-VECTOR-16-VECTORS53IyALLOCATED-BYTE-VECTORS53JyASIAN-DOUBLE-BYTE-COUNT53LyBINARY-TREE-ELEMENT-COUNT53EyBITMAP-ARRA");
    string_constant_100 = 
	    STATIC_STRING("Y-COUNT53FyBYTE-VECTOR-16-POOL53CyBYTE-VECTOR-POOL53NyCHARACTER-DESCRIPTION-COUNT53HyCHARACTER-IMAGE-COUNT5zCOLOR-MAP-COUNT53qyC");
    string_constant_101 = 
	    STATIC_STRING("OUNT-OF-8859-REVERSE-UNICODE-MAP-HASH-VECTOR-43-VECTORS53--yCOUNT-OF-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS53S");
    string_constant_102 = 
	    STATIC_STRING("yCOUNT-OF-INTERNED-GENSYM-STRINGS53eyCOUNT-OF-KANJI-FONT-CACHE-VECTOR-137-VECTORS53uyCOUNT-OF-NATIVE-FONT-SET-WIDTH-EQUIVALENCE-");
    string_constant_103 = 
	    STATIC_STRING("TABLE-256-VECTORS53kyCOUNT-OF-NMS-MENU-FOR-HMENU-HASH-VECTOR-43-VECTORS53cyCOUNT-OF-NON-KANJI-FONT-VECTOR-257-VECTORS53ryCOUNT-O");
    string_constant_104 = 
	    STATIC_STRING("F-SCALED-FONT-KANJI-FONT-CACHE-VECTOR-1096-VECTORS53pyCOUNT-OF-SCALED-FONT-NON-KANJI-FONT-VECTOR-2049-VECTORS53gyCOUNT-OF-VARIAB");
    string_constant_105 = 
	    STATIC_STRING("LE-FILL-ICP-BUFFER-4096-VECTORS53iyCREATED-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS53UyCREATED-SIMPLE-VECTOR-POOL-VECTORS5tDARK-");
    string_constant_106 = 
	    STATIC_STRING("GREY5sDIM-GREY53FyEQ-HASH-TABLE-COUNT53CyERROR-CODE-COUNT53CyEXTRA-LIGHT-GREY53TyFILENAME-PARSER-INFORMATION-COUNT53LyFOREIGN-ST");
    string_constant_107 = 
	    STATIC_STRING("RUCT-INFO-COUNT53qyFRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS53QyFUTURE-TASK-QUEUE-HOLDER-COUNT53LyG2-STREAM-STRUC");
    string_constant_108 = 
	    STATIC_STRING("TURE-COUNT5xGB-2312-COUNT53FyGENSYM-CONS-COUNTER5xGENSYM-CONSES5vGENSYM-LONG53HyGENSYM-PATHNAME-COUNT53MyGENSYM-STRING-STREAM-CO");
    string_constant_109 = 
	    STATIC_STRING("UNT53TyGENSYM-STRING-TEXT-SEQUENCE-COUNT53FyGENSYM-WINDOW-COUNT53HyGRAPH-RENDERING-COUNT53NyGRAPHIC-CHARACTER-SET-COUNT5oGREY5zH");
    string_constant_110 = 
	    STATIC_STRING("ALT-INFO-COUNT53HyI-AM-ALIVE-INFO-COUNT53GyICON-RENDERING-COUNT53CyICP-BUFFER-COUNT5yICP-PORT-COUNT53FyICP-READ-TASK-COUNT53CyIC");
    string_constant_111 = 
	    STATIC_STRING("P-SOCKET-COUNT53GyICP-WRITE-TASK-COUNT53TyIDENTIFIED-DRAWING-ACTIVITY-COUNT53CyIMAGE-DATA-COUNT53HyIMAGE-RENDERING-COUNT53CyIMAG");
    string_constant_112 = 
	    STATIC_STRING("E-TILE-COUNT53DyINDEX-SPACE-COUNT53FyINTERNED-LIST-COUNT53LyISO-2022-TRANSCODER-COUNT5xISO-646-COUNT53CyISO-8859-1-COUNT53DyISO-");
    string_constant_113 = 
	    STATIC_STRING("8859-10-COUNT53CyISO-8859-2-COUNT53CyISO-8859-3-COUNT53CyISO-8859-4-COUNT53CyISO-8859-5-COUNT53CyISO-8859-6-COUNT53CyISO-8859-7-");
    string_constant_114 = 
	    STATIC_STRING("COUNT53CyISO-8859-8-COUNT53CyISO-8859-9-COUNT53JyISO-8859-ABSTRACT-COUNT53LyISO-8859-TRANSCODER-COUNT53CyJIS-X-0208-COUNT53VyKAN");
    string_constant_115 = 
	    STATIC_STRING("JI-FONT-CACHE-VECTOR-137-VECTORS5zKS-C-5601-COUNT53QyLARGE-SCALED-FONT-BUCKET-COUNT5uLIGHT-GREY53DyLOCAL-EVENT-COUNT53DyLRU-ELEM");
    string_constant_116 = 
	    STATIC_STRING("ENT-COUNT53XyMANAGED-OVERSIZED-SIMPLE-FLOAT-ARRAYS53NyMANAGED-SIMPLE-FLOAT-ARRAYS53MyMANAGED-SIMPLE-LONG-ARRAYS53IyMANAGED-SIMPL");
    string_constant_117 = 
	    STATIC_STRING("E-VECTORS53JyMEMORY-LIMIT-INFO-COUNT53VyMINIMAL-CHARACTER-DESCRIPTION-COUNT53dyMULTIPLY-WILD-REGULAR-EXPRESSION-NODE-COUNT53OyNA");
    string_constant_118 = 
	    STATIC_STRING("MED-GENSYM-STRUCTURE-COUNT53DyNATIVE-FONT-COUNT53lyNATIVE-FONT-SET-WIDTH-EQUIVALENCE-TABLE-256-VECTORS53FyNATIVE-WINDOW-COUNT5yN");
    string_constant_119 = 
	    STATIC_STRING("MS-MENU-COUNT53byNMS-MENU-FOR-HMENU-HASH-VECTOR-43-VECTORS53FyNMS-MENU-ITEM-COUNT53TyNON-KANJI-FONT-VECTOR-257-VECTORS53IyPENDIN");
    string_constant_120 = 
	    STATIC_STRING("G-ACTIVITY-COUNT5wPIXMAP-COUNT5vQUEUE-COUNT53FyQUEUE-ELEMENT-COUNT53QyREGION-BOUNDS-AND-RASTER-COUNT53PyREGULAR-EXPRESSION-NODE-");
    string_constant_121 = 
	    STATIC_STRING("COUNT53lyREGULAR-EXPRESSION-NODE-FOR-SET-OF-CHARACTERS-COUNT53kyREGULAR-EXPRESSION-NODE-FOR-SINGLE-CHARACTER-COUNT53pyREGULAR-EX");
    string_constant_122 = 
	    STATIC_STRING("PRESSION-NODE-FOR-SINGLE-WILD-CHARACTER-COUNT53hyREGULAR-EXPRESSION-NODE-FOR-SUBEXPRESSION-COUNT53jyREGULAR-EXPRESSION-NODE-FOR-");
    string_constant_123 = 
	    STATIC_STRING("WILD-CHARACTERS-COUNT53JyRING-BUFFER-STATE-COUNT53NyRING-RASTER-FOR-GRAPH-COUNT5oROOT53DySCALED-FONT-COUNT53iySCALED-FONT-KANJI-");
    string_constant_124 = 
	    STATIC_STRING("FONT-CACHE-VECTOR-1096-VECTORS53gySCALED-FONT-NON-KANJI-FONT-VECTOR-2049-VECTORS53FySCHEDULE-TASK-COUNT53MySHIFT-JIS-TRANSCODER-");
    string_constant_125 = 
	    STATIC_STRING("COUNT53HySHREDDED-RASTER-COUNT53OySIMPLE-GENSYM-STRING-COUNTER53HySIMPLE-GENSYM-STRINGSk5vCOMMON-LISP5xSIMPLE-STRINGk5mAB53JySKI");
    string_constant_126 = 
	    STATIC_STRING("P-LIST-ELEMENT-COUNT5wSOCKET-COUNT53EySPARSE-ARRAY-COUNTk5vCOMMON-LISP5qSYMBOLk5mAB53DySYMBOL-TREE-COUNT53PyTELEWINDOWS-WORKSTAT");
    string_constant_127 = 
	    STATIC_STRING("ION-COUNT53KyTEMPORARY-CONSTANT-COUNT53FyTEXT-SEQUENCE-COUNT53TyTHRASHING-RATIO-RING-BUFFER-COUNT53EyTILED-RASTER-COUNT53GyTILIN");
    string_constant_128 = 
	    STATIC_STRING("G-PATTERN-COUNT53CyTRANSCODER-COUNT53IyTYPE-DESCRIPTION-COUNT53FyUNICODE-BLOCK-COUNT53XyUNICODE-BYTE-SWAPPED-TRANSCODER-COUNT53K");
    string_constant_129 = 
	    STATIC_STRING("yUNICODE-TRANSCODER-COUNT53QyUNICODE-UCS-2-TRANSCODER-COUNT53HyUSER-INTERNED-SYMBOLS53IyUTF-7-TRANSCODER-COUNT53IyUTF-8-TRANSCOD");
    string_constant_130 = 
	    STATIC_STRING("ER-COUNT53iyUTF-G-ASCII-AS-MUCH-AS-POSSIBLE-TRANSCODER-COUNT53IyUTF-G-TRANSCODER-COUNT53XyVARIABLE-FILL-ICP-BUFFER-4096-VECTORS5");
    string_constant_131 = 
	    STATIC_STRING("vWHITE-SMOKE53RyWIDE-STRING-TEXT-SEQUENCE-COUNT53GyWORKSPACE-VIEW-COUNT53DyWORKSTATION-COUNTkk");
    temp_1 = list(50,string_constant_2,string_constant_3,string_constant_4,
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
	    string_constant_50,string_constant_51);
    Standard_symbols_for_optimized_constant_qm = 
	    regenerate_standard_symbols(nconc2(temp_1,nconc2(list(50,
	    string_constant_52,string_constant_53,string_constant_54,
	    string_constant_55,string_constant_56,string_constant_57,
	    string_constant_58,string_constant_59,string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80,string_constant_81,
	    string_constant_82,string_constant_83,string_constant_84,
	    string_constant_85,string_constant_86,string_constant_87,
	    string_constant_88,string_constant_89,string_constant_90,
	    string_constant_91,string_constant_92,string_constant_93,
	    string_constant_94,string_constant_95,string_constant_96,
	    string_constant_97,string_constant_98,string_constant_99,
	    string_constant_100,string_constant_101),list(30,
	    string_constant_102,string_constant_103,string_constant_104,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110,
	    string_constant_111,string_constant_112,string_constant_113,
	    string_constant_114,string_constant_115,string_constant_116,
	    string_constant_117,string_constant_118,string_constant_119,
	    string_constant_120,string_constant_121,string_constant_122,
	    string_constant_123,string_constant_124,string_constant_125,
	    string_constant_126,string_constant_127,string_constant_128,
	    string_constant_129,string_constant_130,string_constant_131))));
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
}
