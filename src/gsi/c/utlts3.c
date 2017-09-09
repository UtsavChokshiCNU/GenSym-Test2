/* utlts3.c
 * Input file:  utilities3.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts3.h"


Object G2int_no_arg = UNBOUND;

/* NOTIFY-USER-AT-CONSOLE-AND-ON-LOGBOOK */
Object g2int_notify_user_at_console_and_on_logbook varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,0);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    END_ARGS_nonrelocating();
    if (EQ(arg1,G2int_no_arg))
	g2int_notify_user_at_console(1,notification_as_format_string);
    else if (EQ(arg2,G2int_no_arg))
	g2int_notify_user_at_console(2,notification_as_format_string,arg1);
    else if (EQ(arg3,G2int_no_arg))
	g2int_notify_user_at_console(3,notification_as_format_string,arg1,
		arg2);
    else if (EQ(arg4,G2int_no_arg))
	g2int_notify_user_at_console(4,notification_as_format_string,arg1,
		arg2,arg3);
    else if (EQ(arg5,G2int_no_arg))
	g2int_notify_user_at_console(5,notification_as_format_string,arg1,
		arg2,arg3,arg4);
    else if (EQ(arg6,G2int_no_arg))
	g2int_notify_user_at_console(6,notification_as_format_string,arg1,
		arg2,arg3,arg4,arg5);
    else if (EQ(arg7,G2int_no_arg))
	g2int_notify_user_at_console(7,notification_as_format_string,arg1,
		arg2,arg3,arg4,arg5,arg6);
    else if (EQ(arg8,G2int_no_arg))
	g2int_notify_user_at_console(8,notification_as_format_string,arg1,
		arg2,arg3,arg4,arg5,arg6,arg7);
    else if (EQ(arg9,G2int_no_arg))
	g2int_notify_user_at_console(9,notification_as_format_string,arg1,
		arg2,arg3,arg4,arg5,arg6,arg7,arg8);
    else
	g2int_notify_user_at_console(10,notification_as_format_string,arg1,
		arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
    return VALUES_1(Nil);
}

Object G2int_starwrite_console_pstar = UNBOUND;

static Object Qg2int_iso_8859_1_gensym_string;  /* iso-8859-1-gensym-string */

/* NOTIFY-USER-AT-CONSOLE */
Object g2int_notify_user_at_console varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object formatted_text_string, gensym_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,1);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    END_ARGS_nonrelocating();
    formatted_text_string = g2int_tformat_text_string(10,
	    notification_as_format_string,arg1,arg2,arg3,arg4,arg5,arg6,
	    arg7,arg8,arg9);
    gensym_string = g2int_export_text_string(2,formatted_text_string,
	    Qg2int_iso_8859_1_gensym_string);
    g2int_c_write_string_to_console(gensym_string,
	    G2int_starwrite_console_pstar ? FIX((SI_Long)1L) : 
	    FIX((SI_Long)0L));
    g2int_reclaim_text_string(formatted_text_string);
    return g2int_reclaim_gensym_string(gensym_string);
}

/* NOTIFY-USER-IN-PARENT-WINDOW */
Object g2int_notify_user_in_parent_window varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,2);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    G2int_no_arg;
    END_ARGS_nonrelocating();
    return g2int_notify_user_at_console(10,notification_as_format_string,
	    arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
}

Object G2int_actual_arg = UNBOUND;

/* C-STRING-TO-GENSYM-STRING */
Object g2int_c_string_to_gensym_string(c_string)
    Object c_string;
{
    Object lisp_string, schar_new_value, temp;
    SI_Long length_1, i, ab_loop_bind_;

    x_note_fn_call(28,3);
    length_1 =  !TRUEP(c_string) ? (SI_Long)0L : 
	    IFIX(inline_get_length_of_c_string(c_string));
    lisp_string = g2int_obtain_simple_gensym_string(FIX(length_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    schar_new_value = inline_get_c_string_element(c_string,FIX(i));
    SET_ISCHAR(lisp_string,i,ICHAR_CODE(schar_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = lisp_string;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

Object G2int_floating_zero = UNBOUND;

static Object float_constant;      /* 0.0 */

/* GENERATE-FLOAT-VECTOR */
Object g2int_generate_float_vector(length_1)
    Object length_1;
{
    Object array;
    XDeclare_area(1);

    x_note_fn_call(28,4);
    if (PUSH_AREA(Dynamic_area,0))
	array = make_array(5,length_1,Kelement_type,Qdouble_float,
		Kinitial_element,float_constant);
    POP_AREA(0);
    return VALUES_1(array);
}

/* ALLOCATE-INITIAL-VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS */
Object g2int_allocate_initial_vector_of_simple_float_array_pools()
{
    x_note_fn_call(28,5);
    return make_array(3,
	    FIXNUM_ADD1(G2int_maximum_managed_simple_float_array_size),
	    Kinitial_element,Nil);
}

Object G2int_vector_of_simple_float_array_pools = UNBOUND;

Object G2int_vector_of_oversized_simple_float_array_pools = UNBOUND;

Object G2int_created_simple_float_array_pool_arrays = UNBOUND;

Object G2int_created_oversized_simple_float_array_pool_arrays = UNBOUND;

/* OUTSTANDING-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS */
Object g2int_outstanding_simple_float_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(28,6);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(G2int_maximum_managed_simple_float_array_size))
	goto end_loop;
    incff_1_arg = length(ISVREF(G2int_vector_of_simple_float_array_pools,
	    index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(G2int_created_simple_float_array_pool_arrays) 
	    - vectors_in_pools));
    return VALUES_1(Qnil);
}

/* OUTSTANDING-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS */
Object g2int_outstanding_oversized_simple_float_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(28,7);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(G2int_maximum_managed_simple_float_array_size))
	goto end_loop;
    incff_1_arg = 
	    length(ISVREF(G2int_vector_of_oversized_simple_float_array_pools,
	    index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(G2int_created_oversized_simple_float_array_pool_arrays) 
	    - vectors_in_pools));
    return VALUES_1(Qnil);
}

Object G2int_simple_float_array_pool_memory_usage = UNBOUND;

Object G2int_oversized_simple_float_array_pool_memory_usage = UNBOUND;

/* SFLAP-MEMORY-USAGE */
Object g2int_sflap_memory_usage()
{
    x_note_fn_call(28,8);
    return VALUES_1(G2int_simple_float_array_pool_memory_usage);
}

/* OVERSIZED-SFLAP-MEMORY-USAGE */
Object g2int_oversized_sflap_memory_usage()
{
    x_note_fn_call(28,9);
    return VALUES_1(G2int_oversized_simple_float_array_pool_memory_usage);
}

Object G2int_replenished_simple_float_array_size_limit = UNBOUND;

Object G2int_replenished_simple_float_arrays_to_make_at_a_time = UNBOUND;

static Object Qg2int_gensym;       /* gensym */

static Object Qg2int_managed_simple_float_array;  /* managed-simple-float-array */

/* ALLOCATE-MANAGED-SIMPLE-FLOAT-ARRAY */
Object g2int_allocate_managed_simple_float_array(requested_length_init)
    Object requested_length_init;
{
    Object vector_of_pools, available_array_cons_qm, array, temp, result_1;
    Object new_vector_list, new_vector_cons, incff_1_arg, temp_1;
    SI_Long requested_length, length_1, index_1;
    char oversized_qm;

    x_note_fn_call(28,10);
    requested_length = IFIX(requested_length_init);
    oversized_qm = requested_length > 
	    IFIX(G2int_maximum_managed_simple_float_array_size);
    length_1 = oversized_qm && (requested_length & (SI_Long)1023L) != 
	    (SI_Long)0L ? (requested_length & (SI_Long)-1024L) + 
	    (SI_Long)1024L : requested_length;
    vector_of_pools = oversized_qm ? 
	    G2int_vector_of_oversized_simple_float_array_pools : 
	    G2int_vector_of_simple_float_array_pools;
    index_1 = oversized_qm ? length_1 >>  -  - (SI_Long)10L : length_1;
    available_array_cons_qm = ISVREF(vector_of_pools,index_1);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = M_CDR(available_array_cons_qm);
	ISVREF(vector_of_pools,index_1) = temp;
	inline_note_reclaim_cons(available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(available_array_cons_qm) = temp;
	G2int_available_gensym_conses = available_array_cons_qm;
	result_1 = array;
    }
    else if (length_1 <= 
	    IFIX(G2int_replenished_simple_float_array_size_limit) && 
	    length_1 <= IFIX(G2int_maximum_managed_simple_float_array_size)) {
	new_vector_list = 
		g2int_make_gensym_list_1(FIXNUM_SUB1(G2int_replenished_simple_vectors_to_make_at_a_time));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = g2int_generate_float_vector(FIX(length_1));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	ISVREF(vector_of_pools,index_1) = new_vector_list;
	incff_1_arg = G2int_replenished_simple_float_arrays_to_make_at_a_time;
	temp = FIXNUM_ADD(G2int_created_simple_float_array_pool_arrays,
		incff_1_arg);
	G2int_created_simple_float_array_pool_arrays = temp;
	temp_1 = G2int_replenished_simple_float_arrays_to_make_at_a_time;
	incff_1_arg = FIXNUM_TIMES(temp_1,
		g2int_bytes_per_double_float_simple_array(FIX(length_1)));
	temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_float_array_pool_memory_usage = temp;
	result_1 = g2int_generate_float_vector(FIX(length_1));
    }
    else if ( !oversized_qm) {
	temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	G2int_created_simple_float_array_pool_arrays = temp;
	incff_1_arg = g2int_bytes_per_double_float_simple_array(FIX(length_1));
	temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_float_array_pool_memory_usage = temp;
	result_1 = g2int_generate_float_vector(FIX(length_1));
    }
    else {
	temp = 
		FIXNUM_ADD1(G2int_created_oversized_simple_float_array_pool_arrays);
	G2int_created_oversized_simple_float_array_pool_arrays = temp;
	incff_1_arg = g2int_bytes_per_double_float_simple_array(FIX(length_1));
	temp = 
		FIXNUM_ADD(G2int_oversized_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_oversized_simple_float_array_pool_memory_usage = temp;
	result_1 = g2int_generate_float_vector(FIX(length_1));
    }
    inline_note_allocate_cons(result_1,Qg2int_managed_simple_float_array);
    return VALUES_1(result_1);
}

/* ALLOCATE-MANAGED-SIMPLE-FLOAT-ARRAY-OF-LENGTH-1 */
Object g2int_allocate_managed_simple_float_array_of_length_1()
{
    Object available_array_cons_qm, array, temp, svref_new_value, result_1;
    Object new_vector_list, new_vector_cons;
    SI_Long temp_1, incff_1_arg;

    x_note_fn_call(28,11);
    available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = G2int_vector_of_simple_float_array_pools;
	svref_new_value = M_CDR(available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(available_array_cons_qm) = temp;
	G2int_available_gensym_conses = available_array_cons_qm;
	result_1 = array;
    }
    else {
	new_vector_list = g2int_make_gensym_list_1(FIX((SI_Long)9L));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = g2int_generate_float_vector(FIX((SI_Long)1L));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	temp = G2int_vector_of_simple_float_array_pools;
	SVREF(temp,FIX((SI_Long)1L)) = new_vector_list;
	temp_1 = IFIX(G2int_created_simple_float_array_pool_arrays) + 
		(SI_Long)10L;
	G2int_created_simple_float_array_pool_arrays = FIX(temp_1);
	incff_1_arg = (SI_Long)10L * 
		IFIX(g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	temp_1 = IFIX(G2int_simple_float_array_pool_memory_usage) + 
		incff_1_arg;
	G2int_simple_float_array_pool_memory_usage = FIX(temp_1);
	result_1 = g2int_generate_float_vector(FIX((SI_Long)1L));
    }
    inline_note_allocate_cons(result_1,Qg2int_managed_simple_float_array);
    return VALUES_1(result_1);
}

/* RECLAIM-MANAGED-SIMPLE-FLOAT-ARRAY */
Object g2int_reclaim_managed_simple_float_array(managed_simple_float_array)
    Object managed_simple_float_array;
{
    Object vector_of_pools, new_cons, gensymed_symbol, cdr_new_value;
    SI_Long length_1, index_1;
    char oversized_qm;

    x_note_fn_call(28,12);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_simple_float_array));
    oversized_qm = length_1 > 
	    IFIX(G2int_maximum_managed_simple_float_array_size);
    vector_of_pools = oversized_qm ? 
	    G2int_vector_of_oversized_simple_float_array_pools : 
	    G2int_vector_of_simple_float_array_pools;
    index_1 = oversized_qm ? length_1 >>  -  - (SI_Long)10L : length_1;
    inline_note_reclaim_cons(managed_simple_float_array,
	    Qg2int_managed_simple_float_array);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_float_array;
    cdr_new_value = ISVREF(vector_of_pools,index_1);
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    ISVREF(vector_of_pools,index_1) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-SIMPLE-FLOAT-ARRAY-OF-LENGTH-1 */
Object g2int_reclaim_managed_simple_float_array_of_length_1(managed_simple_float_array)
    Object managed_simple_float_array;
{
    Object svref_arg_1, new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(28,13);
    inline_note_reclaim_cons(managed_simple_float_array,
	    Qg2int_managed_simple_float_array);
    svref_arg_1 = G2int_vector_of_simple_float_array_pools;
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_float_array;
    cdr_new_value = ISVREF(G2int_vector_of_simple_float_array_pools,
	    (SI_Long)1L);
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol;
    return VALUES_1(Nil);
}

Object G2int_managed_float_array_unique_marker = UNBOUND;

/* ALLOCATE-MANAGED-FLOAT-ARRAY */
Object g2int_allocate_managed_float_array varargs_1(int, n)
{
    Object length_1;
    Object make_exactly, full_size_buffers, size_of_partial_buffer;
    Object spine_vector, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, total_buffers;
    SI_Long full_buffer_index, ab_loop_bind_, svref_arg_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(28,14);
    INIT_ARGS_nonrelocating();
    length_1 = REQUIRED_ARG_nonrelocating();
    make_exactly = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = g2int_chestnut_floorf_function(length_1,
	    G2int_maximum_managed_float_array_buffer_size);
    MVS_2(result,full_size_buffers,size_of_partial_buffer);
    gensymed_symbol = IFIX(full_size_buffers);
    gensymed_symbol_1 = IFIX(size_of_partial_buffer) > (SI_Long)0L ? 
	    (SI_Long)1L : (SI_Long)0L;
    total_buffers = gensymed_symbol + gensymed_symbol_1;
    spine_vector = 
	    g2int_allocate_managed_simple_vector_for_float_array(make_exactly 
	    ? FIX(total_buffers + (SI_Long)2L) : 
	    g2int_buffer_size_for_partial_buffer(FIX(total_buffers + 
	    (SI_Long)2L),G2int_managed_array_allocation_schemes));
    svref_new_value = G2int_managed_float_array_unique_marker;
    SVREF(spine_vector,FIX((SI_Long)0L)) = svref_new_value;
    SVREF(spine_vector,FIX((SI_Long)1L)) = length_1;
    full_buffer_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(full_size_buffers);
  next_loop:
    if (full_buffer_index >= ab_loop_bind_)
	goto end_loop;
    svref_arg_2 = full_buffer_index + (SI_Long)2L;
    svref_new_value = 
	    g2int_allocate_managed_simple_float_array(G2int_maximum_managed_float_array_buffer_size);
    ISVREF(spine_vector,svref_arg_2) = svref_new_value;
    full_buffer_index = full_buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (IFIX(size_of_partial_buffer) > (SI_Long)0L) {
	svref_arg_2 = total_buffers - (SI_Long)1L + (SI_Long)2L;
	svref_new_value = 
		g2int_allocate_managed_simple_float_array(make_exactly ? 
		size_of_partial_buffer : 
		g2int_buffer_size_for_partial_buffer(size_of_partial_buffer,
		G2int_managed_array_allocation_schemes));
	ISVREF(spine_vector,svref_arg_2) = svref_new_value;
    }
    return VALUES_1(spine_vector);
}

/* RECLAIM-MANAGED-FLOAT-ARRAY */
Object g2int_reclaim_managed_float_array(managed_float_array)
    Object managed_float_array;
{
    Object length_1, full_buffers, remainder_1, buffer;
    SI_Long buffer_count, buffer_index, ab_loop_bind_;
    Object result;

    x_note_fn_call(28,15);
    length_1 = ISVREF(managed_float_array,(SI_Long)1L);
    result = g2int_chestnut_floorf_function(length_1,
	    G2int_maximum_managed_float_array_buffer_size);
    MVS_2(result,full_buffers,remainder_1);
    buffer_count = IFIX(remainder_1) > (SI_Long)0L ? 
	    IFIX(FIXNUM_ADD1(full_buffers)) : IFIX(full_buffers);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = buffer_count;
    buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    g2int_reclaim_managed_simple_float_array(buffer);
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(managed_float_array,FIX((SI_Long)0L)) = Nil;
    g2int_reclaim_managed_simple_vector_for_float_array(managed_float_array);
    return VALUES_1(Nil);
}

/* FILL-MANAGED-FLOAT-ARRAY */
Object g2int_fill_managed_float_array(managed_float_array,gensym_float)
    Object managed_float_array, gensym_float;
{
    Object temp, temp_1, full_buffer, last_buffer;
    SI_Long length_1, partial_buffer, full_buffers, buffer_index;
    SI_Long ab_loop_bind_, index_1;
    double cached_float;
    Object result;

    x_note_fn_call(28,16);
    length_1 = IFIX(SVREF(managed_float_array,FIX((SI_Long)1L)));
    cached_float = DOUBLE_FLOAT_TO_DOUBLE(gensym_float);
    result = g2int_chestnut_floorf_function(FIX(length_1),
	    G2int_maximum_managed_float_array_buffer_size);
    MVS_2(result,temp,temp_1);
    partial_buffer = IFIX(temp_1);
    full_buffers = IFIX(temp);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = full_buffers;
    full_buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    full_buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    index_1 = (SI_Long)0L;
  next_loop_1:
    if (index_1 >= IFIX(G2int_maximum_managed_float_array_buffer_size))
	goto end_loop_1;
    DFLOAT_ISASET_1(full_buffer,index_1,cached_float);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (partial_buffer != (SI_Long)0L) {
	last_buffer = ISVREF(managed_float_array,full_buffers + (SI_Long)2L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = partial_buffer;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	DFLOAT_ISASET_1(last_buffer,index_1,cached_float);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(managed_float_array);
}

/* MANAGED-FLOAT-P-FUNCTION */
Object g2int_managed_float_p_function(thing)
    Object thing;
{
    x_note_fn_call(28,17);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MANAGED-FLOAT-VALUE-FUNCTION */
Object g2int_managed_float_value_function(managed_float)
    Object managed_float;
{
    x_note_fn_call(28,18);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_float,
	    (SI_Long)0L)));
}

Object G2int_bytes_per_double_float_simple_array_cached = UNBOUND;

/* ALLOCATE-MANAGED-FLOAT-BOX */
Object g2int_allocate_managed_float_box()
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg;

    x_note_fn_call(28,19);
    amf_available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = G2int_vector_of_simple_float_array_pools;
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	G2int_available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	G2int_created_simple_float_array_pool_arrays = temp;
	incff_1_arg = 
		g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_float_array_pool_memory_usage = temp;
	amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
    }
    return VALUES_1(amf_result);
}

/* COPY-MANAGED-FLOAT */
Object g2int_copy_managed_float(managed_float)
    Object managed_float;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float;
    double aref_new_value;

    x_note_fn_call(28,20);
    amf_available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = G2int_vector_of_simple_float_array_pools;
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	G2int_available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	G2int_created_simple_float_array_pool_arrays = temp;
	incff_1_arg = 
		g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_float_array_pool_memory_usage = temp;
	amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    aref_new_value = DFLOAT_ISAREF_1(managed_float,(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* RECLAIM-IF-MANAGED-FLOAT */
Object g2int_reclaim_if_managed_float(maybe_managed_float)
    Object maybe_managed_float;
{
    x_note_fn_call(28,21);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(maybe_managed_float) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maybe_managed_float)) == 
	    (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(maybe_managed_float);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* GENERATE-LONG-VECTOR */
Object g2int_generate_long_vector(length_1)
    Object length_1;
{
    Object vector_1;
    XDeclare_area(1);

    x_note_fn_call(28,22);
    if (PUSH_AREA(Dynamic_area,0))
	vector_1 = make_array(5,length_1,Kelement_type,list_constant,
		Kinitial_element,FIX((SI_Long)0L));
    POP_AREA(0);
    return VALUES_1(vector_1);
}

Object G2int_vector_of_simple_long_array_pools = UNBOUND;

Object G2int_created_simple_long_array_pool_arrays = UNBOUND;

/* OUTSTANDING-SIMPLE-LONG-ARRAY-POOL-ARRAYS */
Object g2int_outstanding_simple_long_array_pool_arrays()
{
    Object incff_1_arg;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(28,23);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(G2int_maximum_managed_simple_long_array_size))
	goto end_loop;
    incff_1_arg = length(ISVREF(G2int_vector_of_simple_long_array_pools,
	    index_1));
    vectors_in_pools = vectors_in_pools + IFIX(incff_1_arg);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(IFIX(G2int_created_simple_long_array_pool_arrays) 
	    - vectors_in_pools));
    return VALUES_1(Qnil);
}

Object G2int_simple_long_array_pool_memory_usage = UNBOUND;

/* SIMPLE-LONG-ARRAY-POOL-MEMORY-USAGE */
Object g2int_simple_long_array_pool_memory_usage()
{
    x_note_fn_call(28,24);
    return VALUES_1(G2int_simple_long_array_pool_memory_usage);
}

Object G2int_replenished_simple_long_array_size_limit = UNBOUND;

Object G2int_replenished_simple_long_arrays_to_make_at_a_time = UNBOUND;

static Object Qg2int_managed_simple_long_array;  /* managed-simple-long-array */

/* ALLOCATE-MANAGED-SIMPLE-LONG-ARRAY-OF-LENGTH-1 */
Object g2int_allocate_managed_simple_long_array_of_length_1()
{
    Object available_array_cons_qm, array, temp, svref_new_value, result_1;
    Object new_vector_list, new_vector_cons;
    SI_Long temp_1, incff_1_arg;

    x_note_fn_call(28,25);
    available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_long_array_pools,(SI_Long)1L);
    if (available_array_cons_qm) {
	array = M_CAR(available_array_cons_qm);
	temp = G2int_vector_of_simple_long_array_pools;
	svref_new_value = M_CDR(available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(available_array_cons_qm) = temp;
	G2int_available_gensym_conses = available_array_cons_qm;
	result_1 = array;
    }
    else {
	new_vector_list = g2int_make_gensym_list_1(FIX((SI_Long)9L));
	new_vector_cons = new_vector_list;
      next_loop:
	if ( !TRUEP(new_vector_cons))
	    goto end_loop;
	temp = g2int_generate_long_vector(FIX((SI_Long)1L));
	M_CAR(new_vector_cons) = temp;
	new_vector_cons = M_CDR(new_vector_cons);
	goto next_loop;
      end_loop:
	temp = G2int_vector_of_simple_long_array_pools;
	SVREF(temp,FIX((SI_Long)1L)) = new_vector_list;
	temp_1 = IFIX(G2int_created_simple_long_array_pool_arrays) + 
		(SI_Long)10L;
	G2int_created_simple_long_array_pool_arrays = FIX(temp_1);
	incff_1_arg = (SI_Long)10L * 
		IFIX(g2int_bytes_per_long_simple_array(FIX((SI_Long)1L)));
	temp_1 = IFIX(G2int_simple_long_array_pool_memory_usage) + incff_1_arg;
	G2int_simple_long_array_pool_memory_usage = FIX(temp_1);
	result_1 = g2int_generate_long_vector(FIX((SI_Long)1L));
    }
    inline_note_allocate_cons(result_1,Qg2int_managed_simple_long_array);
    return VALUES_1(result_1);
}

/* RECLAIM-MANAGED-SIMPLE-LONG-ARRAY-OF-LENGTH-1 */
Object g2int_reclaim_managed_simple_long_array_of_length_1(managed_simple_long_array)
    Object managed_simple_long_array;
{
    Object svref_arg_1, new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(28,26);
    inline_note_reclaim_cons(managed_simple_long_array,
	    Qg2int_managed_simple_long_array);
    svref_arg_1 = G2int_vector_of_simple_long_array_pools;
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = managed_simple_long_array;
    cdr_new_value = ISVREF(G2int_vector_of_simple_long_array_pools,
	    (SI_Long)1L);
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MANAGED-LONG-P-FUNCTION */
Object g2int_managed_long_p_function(thing)
    Object thing;
{
    x_note_fn_call(28,27);
    if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MANAGED-LONG-VALUE-FUNCTION */
Object g2int_managed_long_value_function(managed_long)
    Object managed_long;
{
    x_note_fn_call(28,28);
    return aref1(managed_long,FIX((SI_Long)0L));
}

Object G2int_bytes_per_long_simple_array_cached = UNBOUND;

/* ALLOCATE-MANAGED-LONG-BOX */
Object g2int_allocate_managed_long_box()
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg;

    x_note_fn_call(28,29);
    amf_available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_long_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = G2int_vector_of_simple_long_array_pools;
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	G2int_available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(G2int_created_simple_long_array_pool_arrays);
	G2int_created_simple_long_array_pool_arrays = temp;
	incff_1_arg = G2int_bytes_per_long_simple_array_cached;
	temp = FIXNUM_ADD(G2int_simple_long_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_long_array_pool_memory_usage = temp;
	amf_result = g2int_generate_long_vector(FIX((SI_Long)1L));
    }
    return VALUES_1(amf_result);
}

/* ALLOCATE-MANAGED-LONG-FUNCTION */
Object g2int_allocate_managed_long_function(gensym_long)
    Object gensym_long;
{
    Object new_long;
    SI_int64 aref_new_value;

    x_note_fn_call(28,30);
    new_long = g2int_allocate_managed_long_box();
    aref_new_value = INTEGER_TO_INT64(gensym_long);
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(new_long);
}

/* COPY-MANAGED-LONG */
Object g2int_copy_managed_long(managed_long)
    Object managed_long;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_long, temp_1;
    SI_int64 aref_new_value;

    x_note_fn_call(28,31);
    amf_available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_long_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = G2int_vector_of_simple_long_array_pools;
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	G2int_available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(G2int_created_simple_long_array_pool_arrays);
	G2int_created_simple_long_array_pool_arrays = temp;
	incff_1_arg = G2int_bytes_per_long_simple_array_cached;
	temp = FIXNUM_ADD(G2int_simple_long_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_long_array_pool_memory_usage = temp;
	amf_result = g2int_generate_long_vector(FIX((SI_Long)1L));
    }
    new_long = amf_result;
    temp_1 = aref1(managed_long,FIX((SI_Long)0L));
    aref_new_value = INTEGER_TO_INT64(temp_1);
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(new_long);
}

/* RECLAIM-IF-MANAGED-LONG */
Object g2int_reclaim_if_managed_long(maybe_managed_long)
    Object maybe_managed_long;
{
    x_note_fn_call(28,32);
    if (INLINE_LONG_VECTOR_P(maybe_managed_long) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maybe_managed_long)) == (SI_Long)1L)
	g2int_reclaim_managed_simple_long_array_of_length_1(maybe_managed_long);
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-NUMBER-OR-VALUE-FUNCTION */
Object g2int_reclaim_managed_number_or_value_function(managed_number_or_value)
    Object managed_number_or_value;
{
    x_note_fn_call(28,33);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(managed_number_or_value);
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	g2int_reclaim_managed_simple_long_array_of_length_1(managed_number_or_value);
    else if (g2int_text_string_p(managed_number_or_value))
	g2int_reclaim_text_string(managed_number_or_value);
    else if (FIXNUMP(managed_number_or_value) || 
	    SYMBOLP(managed_number_or_value));
    else
	g2int_reclaim_evaluation_value(managed_number_or_value);
    return VALUES_1(Nil);
}

/* RECLAIM-POSSIBLE-MANAGED-FLOAT */
Object g2int_reclaim_possible_managed_float(managed_float_qm)
    Object managed_float_qm;
{
    x_note_fn_call(28,34);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_qm)) == (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(managed_float_qm);
    return VALUES_1(Nil);
}

/* COERCE-NUMBER-TO-FIXNUM */
Object g2int_coerce_number_to_fixnum(number)
    Object number;
{
    Object temp, long_value;
    XDeclare_area(1);

    x_note_fn_call(28,35);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L)
	temp = l_round(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number,
		(SI_Long)0L)),_);
    else if (FLOATP(number))
	temp = l_round(number,_);
    else if (FIXNUMP(number))
	temp = number;
    else if (INLINE_LONG_VECTOR_P(number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number)) == (SI_Long)1L) {
	if (PUSH_AREA(Dynamic_area,0)) {
	    long_value = aref1(number,FIX((SI_Long)0L));
	    temp = coerce(long_value,Qfixnum);
	}
	POP_AREA(0);
    }
    else if (INLINE_LONG_P(number) != (SI_Long)0L) {
	if (PUSH_AREA(Dynamic_area,0))
	    temp = coerce(number,Qfixnum);
	POP_AREA(0);
    }
    else
	temp = FIX((SI_Long)0L);
    return VALUES_1(temp);
}

/* CONVERT-G2LONGINT-TO-DOUBLE */
Object g2int_convert_g2longint_to_double(gensym_long_init)
    Object gensym_long_init;
{
    Object temp;
    SI_int64 gensym_long;

    x_note_fn_call(28,36);
    gensym_long = INTEGER_TO_INT64(gensym_long_init);
    temp = lfloat(INT64_TO_INTEGER(gensym_long),float_constant);
    return VALUES_1(temp);
}

static Object Qg2int_gensym_float;  /* gensym-float */

/* NORMALIZE-TO-GENSYM-FLOAT */
Object g2int_normalize_to_gensym_float(x)
    Object x;
{
    Object gensymed_symbol, long_value;

    x_note_fn_call(28,37);
    gensymed_symbol = x;
    if (FIXNUMP(gensymed_symbol))
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(gensymed_symbol)));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gensymed_symbol,
		(SI_Long)0L)));
    else if (FLOATP(gensymed_symbol))
	return VALUES_1(gensymed_symbol);
    else if (INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == (SI_Long)1L) {
	long_value = aref1(gensymed_symbol,FIX((SI_Long)0L));
	return g2int_convert_g2longint_to_double(long_value);
    }
    else if (INLINE_LONG_P(gensymed_symbol) != (SI_Long)0L)
	return g2int_convert_g2longint_to_double(gensymed_symbol);
    else
	return coerce(gensymed_symbol,Qg2int_gensym_float);
}

/* STORE-MANAGED-NUMBER-OR-VALUE-FUNCTION */
Object g2int_store_managed_number_or_value_function(old_value,new_value)
    Object old_value, new_value;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, new_long;
    SI_int64 aref_new_value_1;
    double aref_new_value;

    x_note_fn_call(28,38);
    if (FIXNUMP(new_value) || SYMBOLP(new_value)) {
	if ( !(FIXNUMP(old_value) || SYMBOLP(old_value))) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
		g2int_reclaim_managed_simple_float_array_of_length_1(old_value);
	    else if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	}
	return VALUES_1(new_value);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == (SI_Long)1L) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DFLOAT_ISAREF_1(new_value,(SI_Long)0L);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	    return g2int_copy_managed_float(new_value);
	}
    }
    else if (FLOATP(new_value)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
    }
    else if (g2int_text_string_p(new_value)) {
	if (g2int_text_string_p(old_value))
	    g2int_reclaim_text_string(old_value);
	return g2int_copy_text_string(new_value);
    }
    else if (INLINE_LONG_VECTOR_P(new_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == (SI_Long)1L) {
	if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    temp = aref1(new_value,FIX((SI_Long)0L));
	    aref_new_value_1 = INTEGER_TO_INT64(temp);
	    set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(old_value);
	}
	else {
	    if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	    return g2int_copy_managed_long(new_value);
	}
    }
    else if (INLINE_LONG_P(new_value) != (SI_Long)0L) {
	if (INLINE_LONG_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value_1 = INTEGER_TO_INT64(new_value);
	    set_aref1(old_value,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(old_value);
	}
	else {
	    if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	    new_long = g2int_allocate_managed_long_box();
	    aref_new_value_1 = INTEGER_TO_INT64(new_value);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value_1));
	    return VALUES_1(new_long);
	}
    }
    else if (BIGNUMP(new_value)) {
	new_value = g2int_coerce_bignum_to_gensym_float(new_value);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(old_value);
	}
	else {
	    if (g2int_text_string_p(old_value))
		g2int_reclaim_text_string(old_value);
	    amf_available_array_cons_qm = 
		    ISVREF(G2int_vector_of_simple_float_array_pools,
		    (SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = G2int_vector_of_simple_float_array_pools;
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qg2int_gensym);
		temp = G2int_available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp;
		G2int_available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp = 
			FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		G2int_created_simple_float_array_pool_arrays = temp;
		incff_1_arg = 
			g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp = 
			FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			incff_1_arg);
		G2int_simple_float_array_pool_memory_usage = temp;
		amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
    }
    else
	return VALUES_1(new_value);
}

/* COERCE-BIGNUM-TO-GENSYM-FLOAT */
Object g2int_coerce_bignum_to_gensym_float(bignum)
    Object bignum;
{
    x_note_fn_call(28,39);
    return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

/* MAKE-PARTITION-FLOAT-OR-LONG-UNION */
Object g2int_make_partition_float_or_long_union()
{
    Object temp;

    x_note_fn_call(28,40);
    temp = make_array(3,FIX((SI_Long)4L),Kelement_type,list_constant_1);
    return VALUES_1(temp);
}

Object G2int_partition_float_union = UNBOUND;

Object G2int_partition_long_union = UNBOUND;

/* PARTITION-MANAGED-FLOAT */
Object g2int_partition_managed_float(managed_float)
    Object managed_float;
{
    SI_Long b0, b1, b2, b3;

    x_note_fn_call(28,41);
    g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_float,
	    (SI_Long)0L),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
    return VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
}

/* RECONSTRUCT-MANAGED-FLOAT */
Object g2int_reconstruct_managed_float(byte0,byte1,byte2,byte3)
    Object byte0, byte1, byte2, byte3;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, b0, b1, b2, b3;
    double aref_new_value;

    x_note_fn_call(28,42);
    amf_available_array_cons_qm = 
	    ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = G2int_vector_of_simple_float_array_pools;
	svref_new_value = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	temp = G2int_available_gensym_conses;
	M_CDR(amf_available_array_cons_qm) = temp;
	G2int_available_gensym_conses = amf_available_array_cons_qm;
	amf_result = amf_array;
    }
    else {
	temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	G2int_created_simple_float_array_pool_arrays = temp;
	incff_1_arg = 
		g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		incff_1_arg);
	G2int_simple_float_array_pool_memory_usage = temp;
	amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    b0 = byte0;
    b1 = byte1;
    b2 = byte2;
    b3 = byte3;
    aref_new_value = g2ext_foreign_reconstruct_float(IFIX(b0),IFIX(b1),
	    IFIX(b2),IFIX(b3));
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

static Object Qg2int_vms;          /* vms */

/* POSITIVE-INFINITY-P */
Object g2int_positive_infinity_p(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(28,43);
    if (FLOATP(thing)) {
	if (EQ(G2int_g2_machine_type,Qg2int_vms))
	    temp = Nil;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(thing);
	    g2ext_foreign_partition_float(temp_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
	    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	    MVS_4(result,byte0,byte1,byte2,byte3);
	    temp = FIXNUM_EQ(byte0,G2int_mask_for_ieee_exponent) && 
		    IFIX(byte1) == (SI_Long)0L && IFIX(byte2) == 
		    (SI_Long)0L ? (IFIX(byte3) == (SI_Long)0L ? T : Nil) : 
		    Qnil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NEGATIVE-INFINITY-P */
Object g2int_negative_infinity_p(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(28,44);
    if (FLOATP(thing)) {
	if (EQ(G2int_g2_machine_type,Qg2int_vms))
	    temp = Nil;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(thing);
	    g2ext_foreign_partition_float(temp_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
	    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	    MVS_4(result,byte0,byte1,byte2,byte3);
	    temp = IFIX(byte0) == (SI_Long)65520L && IFIX(byte1) == 
		    (SI_Long)0L && IFIX(byte2) == (SI_Long)0L ? 
		    (IFIX(byte3) == (SI_Long)0L ? T : Nil) : Qnil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NANP */
Object g2int_nanp(thing)
    Object thing;
{
    Object temp, byte0, byte1, byte2, byte3;
    SI_Long b0, b1, b2, b3;
    double temp_1;
    Object result;

    x_note_fn_call(28,45);
    if (FLOATP(thing)) {
	if (EQ(G2int_g2_machine_type,Qg2int_vms))
	    temp = Nil;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(thing);
	    g2ext_foreign_partition_float(temp_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
	    result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	    MVS_4(result,byte0,byte1,byte2,byte3);
	    if (FIXNUM_EQ(FIXNUM_LOGAND(byte0,
		    G2int_mask_for_ieee_exponent),
		    G2int_mask_for_ieee_exponent)) {
		temp = FIXNUM_PLUSP(byte1) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUM_PLUSP(byte2) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUM_PLUSP(byte3) ? T : Nil;
		if (temp);
		else
		    temp = (SI_Long)0L < (IFIX(byte0) & (SI_Long)15L) ? T :
			     Nil;
	    }
	    else
		temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXCEPTIONAL-FLOAT-P */
Object g2int_exceptional_float_p(thing)
    Object thing;
{
    Object temp, byte0;
    SI_Long b0, b1, b2, b3;
    double temp_1;

    x_note_fn_call(28,46);
    if (FLOATP(thing)) {
	if (EQ(G2int_g2_machine_type,Qg2int_vms))
	    temp = Nil;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(thing);
	    g2ext_foreign_partition_float(temp_1,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
	    temp = FIX(b0);
	    byte0 = temp;
	    temp = FIXNUM_EQ(FIXNUM_LOGAND(byte0,
		    G2int_mask_for_ieee_exponent),
		    G2int_mask_for_ieee_exponent) ? T : Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FILL-MANAGED-FLOAT-ARRAY-WITH-MANAGED-FLOAT */
Object g2int_fill_managed_float_array_with_managed_float(managed_float_array,
	    managed_float)
    Object managed_float_array, managed_float;
{
    Object full_buffer, last_buffer;
    SI_Long length_1, temp, full_buffers, partial_buffer, buffer_index;
    SI_Long ab_loop_bind_, index_1;
    double float_1;

    x_note_fn_call(28,47);
    length_1 = IFIX(SVREF(managed_float_array,FIX((SI_Long)1L)));
    temp = length_1 / IFIX(G2int_maximum_managed_float_array_buffer_size);
    full_buffers = temp;
    temp = length_1 % IFIX(G2int_maximum_managed_float_array_buffer_size);
    partial_buffer = temp;
    float_1 = DFLOAT_ISAREF_1(managed_float,(SI_Long)0L);
    buffer_index = (SI_Long)0L;
    ab_loop_bind_ = full_buffers;
    full_buffer = Nil;
  next_loop:
    if (buffer_index >= ab_loop_bind_)
	goto end_loop;
    full_buffer = ISVREF(managed_float_array,buffer_index + (SI_Long)2L);
    index_1 = (SI_Long)0L;
  next_loop_1:
    if (index_1 >= IFIX(G2int_maximum_managed_float_array_buffer_size))
	goto end_loop_1;
    DFLOAT_ISASET_1(full_buffer,index_1,float_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    buffer_index = buffer_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (partial_buffer != (SI_Long)0L) {
	last_buffer = ISVREF(managed_float_array,full_buffers + (SI_Long)2L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = partial_buffer;
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	DFLOAT_ISASET_1(last_buffer,index_1,float_1);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(managed_float_array);
}

Object G2int_managed_bignum_pool = UNBOUND;

/* GET-MANAGED-BIGNUM */
Object g2int_get_managed_bignum(length_1,value)
    Object length_1, value;
{
    Object available, gensym_pop_store, svref_arg_1, cons_1, next_cons, temp;
    SI_Long svref_arg_2;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(28,48);
    if (FIXNUM_GE(length_1,ISVREF(G2int_managed_bignum_pool,(SI_Long)1L)))
	G2int_managed_bignum_pool = g2int_adjust_managed_array(2,
		G2int_managed_bignum_pool,FIXNUM_ADD1(length_1));
    available = FIXNUM_LE(ISVREF(G2int_managed_bignum_pool,(SI_Long)1L),
	    G2int_maximum_in_place_array_size) ? 
	    ISVREF(G2int_managed_bignum_pool,IFIX(FIXNUM_ADD(length_1,
	    G2int_managed_array_index_offset))) : 
	    ISVREF(ISVREF(G2int_managed_bignum_pool,(IFIX(length_1) >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),IFIX(length_1) & (SI_Long)1023L);
    if (available) {
	gensym_pop_store = Nil;
	svref_arg_1 = G2int_managed_bignum_pool;
	cons_1 = FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
		G2int_maximum_in_place_array_size) ? ISVREF(svref_arg_1,
		IFIX(FIXNUM_ADD(length_1,
		G2int_managed_array_index_offset))) : 
		ISVREF(ISVREF(svref_arg_1,(IFIX(length_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(length_1) & (SI_Long)1023L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(cons_1) = temp;
	    G2int_available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	if (FIXNUM_LE(ISVREF(svref_arg_1,(SI_Long)1L),
		G2int_maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(length_1,G2int_managed_array_index_offset);
	    SVREF(svref_arg_1,temp) = next_cons;
	}
	else {
	    temp = ISVREF(svref_arg_1,(IFIX(length_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(length_1) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = next_cons;
	}
	return VALUES_1(gensym_pop_store);
    }
    else {
	if (PUSH_AREA(Dynamic_area,0))
	    result = copy_of_bignum(value);
	POP_AREA(0);
	return result;
    }
}

Object G2int_the_type_description_of_temporary_constant = UNBOUND;

Object G2int_chain_of_available_temporary_constants = UNBOUND;

Object G2int_temporary_constant_count = UNBOUND;

/* RECLAIM-TEMPORARY-CONSTANT-1 */
Object g2int_reclaim_temporary_constant_1(temporary_constant)
    Object temporary_constant;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(28,49);
    inline_note_reclaim_cons(temporary_constant,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = temporary_constant;
    svref_new_value = 
	    g2int_reclaim_managed_number_or_value_function(ISVREF(temporary_constant,
	    (SI_Long)1L));
    SVREF(temporary_constant,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(temporary_constant,FIX((SI_Long)1L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_temporary_constants;
    SVREF(temporary_constant,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_temporary_constants = temporary_constant;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEMPORARY-CONSTANT */
Object g2int_reclaim_structure_for_temporary_constant(temporary_constant)
    Object temporary_constant;
{
    x_note_fn_call(28,50);
    return g2int_reclaim_temporary_constant_1(temporary_constant);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* MAKE-PERMANENT-TEMPORARY-CONSTANT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_temporary_constant_structure_internal()
{
    Object def_structure_temporary_constant_variable;
    Object temporary_constant_count_new_value;
    Object defstruct_g2_temporary_constant_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,51);
    def_structure_temporary_constant_variable = Nil;
    temporary_constant_count_new_value = 
	    FIXNUM_ADD1(G2int_temporary_constant_count);
    G2int_temporary_constant_count = temporary_constant_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_temporary_constant_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_temporary_constant_variable = the_array;
	SVREF(defstruct_g2_temporary_constant_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_temporary_constant_g2_struct;
	def_structure_temporary_constant_variable = 
		defstruct_g2_temporary_constant_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-1-1 */
Object g2int_make_temporary_constant_1_1(constant_value_internal,constant_type)
    Object constant_value_internal, constant_type;
{
    Object def_structure_temporary_constant_variable;

    x_note_fn_call(28,52);
    def_structure_temporary_constant_variable = 
	    G2int_chain_of_available_temporary_constants;
    if (def_structure_temporary_constant_variable) {
	G2int_chain_of_available_temporary_constants = 
		ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		g2int_make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    constant_value_internal;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = 
	    constant_type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-NO-EXPIRATION */
Object g2int_make_temporary_constant_no_expiration(value,type)
    Object value, type;
{
    Object def_structure_temporary_constant_variable, new_float;
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_long, temp_1;
    SI_int64 aref_new_value_1;
    double aref_new_value;

    x_note_fn_call(28,53);
    def_structure_temporary_constant_variable = 
	    G2int_chain_of_available_temporary_constants;
    if (def_structure_temporary_constant_variable) {
	G2int_chain_of_available_temporary_constants = 
		ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		g2int_make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    if (FIXNUMP(value) || SYMBOLP(value))
	new_float = value;
    else if (FLOATP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = G2int_vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,
		    Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    G2int_available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	    G2int_created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_float_array_pool_memory_usage = temp;
	    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    }
    else if (INLINE_LONG_P(value) != (SI_Long)0L) {
	new_long = g2int_allocate_managed_long_box();
	aref_new_value_1 = INTEGER_TO_INT64(value);
	set_aref1(new_long,FIX((SI_Long)0L),
		INT64_TO_INTEGER(aref_new_value_1));
	new_float = new_long;
    }
    else if (g2int_text_string_p(value))
	new_float = g2int_copy_text_string(value);
    else if (BIGNUMP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = G2int_vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,
		    Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    G2int_available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	    G2int_created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    G2int_simple_float_array_pool_memory_usage = temp;
	    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	temp_1 = g2int_coerce_bignum_to_gensym_float(value);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    }
    else
	new_float = value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    new_float;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-GIVEN-MANAGED-VALUE-NO-EXPIRATION */
Object g2int_make_temporary_constant_given_managed_value_no_expiration(managed_value,
	    type)
    Object managed_value, type;
{
    Object def_structure_temporary_constant_variable;

    x_note_fn_call(28,54);
    def_structure_temporary_constant_variable = 
	    G2int_chain_of_available_temporary_constants;
    if (def_structure_temporary_constant_variable) {
	G2int_chain_of_available_temporary_constants = 
		ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		g2int_make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    managed_value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* MAKE-TEMPORARY-CONSTANT-COPYING-MANAGED-VALUE-NO-EXPIRATION */
Object g2int_make_temporary_constant_copying_managed_value_no_expiration(managed_value,
	    type)
    Object managed_value, type;
{
    Object def_structure_temporary_constant_variable, svref_new_value;

    x_note_fn_call(28,55);
    def_structure_temporary_constant_variable = 
	    G2int_chain_of_available_temporary_constants;
    if (def_structure_temporary_constant_variable) {
	G2int_chain_of_available_temporary_constants = 
		ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		g2int_make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) == (SI_Long)1L)
	svref_new_value = g2int_copy_managed_float(managed_value);
    else if (INLINE_LONG_VECTOR_P(managed_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) == (SI_Long)1L)
	svref_new_value = g2int_copy_managed_long(managed_value);
    else if (g2int_text_string_p(managed_value))
	svref_new_value = g2int_copy_text_string(managed_value);
    else
	svref_new_value = managed_value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = type;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* COPY-TEMPORARY-CONSTANT */
Object g2int_copy_temporary_constant(temporary_constant)
    Object temporary_constant;
{
    Object def_structure_temporary_constant_variable, managed_number_or_value;
    Object svref_new_value;

    x_note_fn_call(28,56);
    def_structure_temporary_constant_variable = 
	    G2int_chain_of_available_temporary_constants;
    if (def_structure_temporary_constant_variable) {
	G2int_chain_of_available_temporary_constants = 
		ISVREF(def_structure_temporary_constant_variable,(SI_Long)0L);
	SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_temporary_constant_g2_struct;
    }
    else
	def_structure_temporary_constant_variable = 
		g2int_make_permanent_temporary_constant_structure_internal();
    inline_note_allocate_cons(def_structure_temporary_constant_variable,Nil);
    managed_number_or_value = ISVREF(temporary_constant,(SI_Long)1L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	svref_new_value = g2int_copy_managed_float(managed_number_or_value);
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	svref_new_value = g2int_copy_managed_long(managed_number_or_value);
    else if (g2int_text_string_p(managed_number_or_value))
	svref_new_value = g2int_copy_text_string(managed_number_or_value);
    else
	svref_new_value = managed_number_or_value;
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    svref_new_value = ISVREF(temporary_constant,(SI_Long)2L);
    SVREF(def_structure_temporary_constant_variable,FIX((SI_Long)2L)) = 
	    svref_new_value;
    return VALUES_1(def_structure_temporary_constant_variable);
}

/* RECLAIM-IF-TEMPORARY-CONSTANT-FUNCTION */
Object g2int_reclaim_if_temporary_constant_function(thing)
    Object thing;
{
    x_note_fn_call(28,57);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	return g2int_reclaim_temporary_constant_1(thing);
    else
	return VALUES_1(Nil);
}

Object G2int_recycled_resumption_conses = UNBOUND;

Object G2int_count_of_interned_gensym_strings = UNBOUND;

Object G2int_memory_used_for_interned_gensym_strings = UNBOUND;

/* GENSYM-SYMBOL-NAME */
Object g2int_gensym_symbol_name(symbol)
    Object symbol;
{
    Object gensym_string;
    SI_Long ab_loop_bind_, i;
    char temp;
    char *name;
    int len;

    x_note_fn_call(28,58);
    name = isymbol_name(symbol);
    len = strlen(name);
    gensym_string = g2int_obtain_simple_gensym_string(INT_TO_FIXNUM(len));
    if (SIMPLE_STRING_P(gensym_string)) {
	ab_loop_bind_ = len;
	i = (SI_Long)0L;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	temp = name[i];
	SET_ISCHAR(gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	ab_loop_bind_ = len;
	i = (SI_Long)0L;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	temp = name[i];
	SET_ICHAR(gensym_string,i,temp);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(gensym_string);
}

Object G2int_nil_interned = UNBOUND;

/* INTERN-GENSYM-STRING */
Object g2int_intern_gensym_string varargs_1(int, n)
{
    Object gensym_string;
    Object package_qm, temp, symbol, pre_existing_symbol_p;
    Object count_of_interned_gensym_strings_new_value;
    SI_Long incff_1_arg, memory_used_for_interned_gensym_strings_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(28,59);
    INIT_ARGS_nonrelocating();
    gensym_string = REQUIRED_ARG_nonrelocating();
    package_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = package_qm;
    if (temp);
    else
	temp = Package;
    result = intern(gensym_string,temp);
    MVS_2(result,symbol,pre_existing_symbol_p);
    if ( !TRUEP(pre_existing_symbol_p)) {
	count_of_interned_gensym_strings_new_value = 
		FIXNUM_ADD1(G2int_count_of_interned_gensym_strings);
	G2int_count_of_interned_gensym_strings = 
		count_of_interned_gensym_strings_new_value;
	incff_1_arg = (SI_Long)25L + IFIX(length(gensym_string));
	memory_used_for_interned_gensym_strings_new_value = 
		IFIX(G2int_memory_used_for_interned_gensym_strings) + 
		incff_1_arg;
	G2int_memory_used_for_interned_gensym_strings = 
		FIX(memory_used_for_interned_gensym_strings_new_value);
    }
    if ( !EQ(INLINE_CACHED_SYMBOL_NAME(symbol),gensym_string))
	g2int_reclaim_gensym_string(gensym_string);
    if (EQ(symbol,G2int_nil_interned))
	return VALUES_1(Nil);
    else
	return VALUES_1(symbol);
}

/* INTERN-USING-STRING-BUFFER */
Object g2int_intern_using_string_buffer(string_buffer,length_1,package_qm)
    Object string_buffer, length_1, package_qm;
{
    Object temp, temp_1, symbol, pre_existing_symbol_p, incff_1_arg;
    Object result;

    x_note_fn_call(28,60);
    temp = CODE_CHAR(FIX((SI_Long)0L));
    SET_CHAR(string_buffer,length_1,temp);
    SET_FILL_POINTER(string_buffer,length_1);
    temp_1 = package_qm;
    if (temp_1);
    else
	temp_1 = Package;
    result = intern(string_buffer,temp_1);
    MVS_2(result,symbol,pre_existing_symbol_p);
    if ( !TRUEP(pre_existing_symbol_p)) {
	temp = FIXNUM_ADD1(G2int_count_of_interned_gensym_strings);
	G2int_count_of_interned_gensym_strings = temp;
	incff_1_arg = length_1;
	temp = FIXNUM_ADD(G2int_memory_used_for_interned_gensym_strings,
		incff_1_arg);
	G2int_memory_used_for_interned_gensym_strings = temp;
    }
    return VALUES_1(EQ(symbol,G2int_nil_interned) ? Nil : symbol);
}

/* POSITION-OF-TWO-COLONS */
Object g2int_position_of_two_colons(string_1)
    Object string_1;
{
    Object length_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,61);
    if (g2int_text_string_p(string_1)) {
	length_1 = g2int_lengthw(string_1);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (UBYTE_16_ISAREF_1(string_1,i) == (SI_Long)58L && 
		UBYTE_16_ISAREF_1(string_1,i + (SI_Long)1L) == (SI_Long)58L) {
	    temp = FIX(i);
	    goto end;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
    }
    else {
	length_1 = length(string_1);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (CHAR_EQ(CHR(ICHAR(string_1,i)),CHR(':')) && 
		CHAR_EQ(CHR(ICHAR(string_1,i + (SI_Long)1L)),CHR(':'))) {
	    temp = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* GET-MEMORY-USED-FOR-INTERNED-TEXT-STRINGS */
Object g2int_get_memory_used_for_interned_text_strings()
{
    x_note_fn_call(28,62);
    return VALUES_1(G2int_memory_used_for_interned_gensym_strings);
}

Object G2int_most_positive_fixnum_floor_10 = UNBOUND;

Object G2int_most_negative_fixnum_ceiling_10 = UNBOUND;

/* VALUE-TIMES-TEN-MINUS-WEIGHT->=-MOST-NEGATIVE-FIXNUM-P */
Object g2int_value_times_ten_minus_weight_gteq_most_negative_fixnum_p(value,
	    weight)
    Object value, weight;
{
    x_note_fn_call(28,63);
    return VALUES_1(FIXNUM_GE(FIXNUM_NEGATE(value),
	    G2int_most_negative_fixnum_ceiling_10) ? (IFIX(weight) <= 
	    IFIX(value) * (SI_Long)10L - IFIX(Most_negative_fixnum) ? T : 
	    Nil) : Qnil);
}

static Object string_constant;     /* "number is too large" */

/* READ-POSITIVE-FIXNUM-FROM-STRING */
Object g2int_read_positive_fixnum_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object digit_character, digit_qm;
    SI_Long string_index, fixnum_so_far, gensymed_symbol;

    x_note_fn_call(28,64);
    string_index = IFIX(start_index);
    digit_character = FIX((SI_Long)97L);
    digit_qm = Nil;
    fixnum_so_far = (SI_Long)0L;
  next_loop:
    if ( !(string_index < IFIX(end_index)))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,string_index));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (fixnum_so_far < IFIX(G2int_most_positive_fixnum_floor_10) || 
		fixnum_so_far <= IFIX(G2int_most_positive_fixnum_floor_10) 
		&& IFIX(digit_qm) <= IFIX(Most_positive_fixnum) - 
		fixnum_so_far * (SI_Long)10L)
	    fixnum_so_far = fixnum_so_far * (SI_Long)10L + IFIX(digit_qm);
	else
	    return VALUES_3(Nil,FIX(string_index + (SI_Long)1L),
		    string_constant);
    }
    else
	goto end_loop;
    string_index = string_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_3( !(string_index == IFIX(start_index)) ? 
	    FIX(fixnum_so_far) : Nil,FIX(string_index),Nil);
    return VALUES_1(Qnil);
}

static Object string_constant_1;   /* "negative number is too large" */

/* READ-NEGATIVE-FIXNUM-FROM-STRING */
Object g2int_read_negative_fixnum_from_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object string_index, digit_character, digit_qm, fixnum_so_far, temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(28,65);
    string_index = FIXNUM_ADD1(start_index);
    digit_character = Nil;
    digit_qm = Nil;
    fixnum_so_far = FIX((SI_Long)0L);
    if ( !(UBYTE_16_ISAREF_1(string_1,IFIX(start_index)) == (SI_Long)45L))
	return VALUES_3(Nil,start_index,Nil);
  next_loop:
    if ( !FIXNUM_LT(string_index,end_index))
	goto end_loop;
    digit_character = FIX(UBYTE_16_ISAREF_1(string_1,IFIX(string_index)));
    gensymed_symbol = IFIX(digit_character);
    digit_qm = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
    if (digit_qm) {
	if (FIXNUM_GT(fixnum_so_far,G2int_most_negative_fixnum_ceiling_10) 
		|| 
		g2int_value_times_ten_minus_weight_gteq_most_negative_fixnum_p(fixnum_so_far,
		digit_qm))
	    fixnum_so_far = FIX(IFIX(fixnum_so_far) * (SI_Long)10L - 
		    IFIX(digit_qm));
	else {
	    temp = FIXNUM_ADD1(string_index);
	    return VALUES_3(Nil,temp,string_constant_1);
	}
    }
    else
	goto end_loop;
    string_index = FIXNUM_ADD1(string_index);
    goto next_loop;
  end_loop:
    return VALUES_3( !FIXNUM_EQ(string_index,start_index) ? fixnum_so_far :
	     Nil,string_index,Nil);
    return VALUES_1(Qnil);
}

/* READ-FIXNUM-FROM-STRING */
Object g2int_read_fixnum_from_string varargs_1(int, n)
{
    Object string_1;
    Object start_index_qm, end_index_qm, start_index, end_index;
    SI_Long digit_character;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,66);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    end_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    start_index = start_index_qm;
    if (start_index);
    else
	start_index = FIX((SI_Long)0L);
    end_index = end_index_qm;
    if (end_index);
    else
	end_index = g2int_text_string_length(string_1);
    digit_character = UBYTE_16_ISAREF_1(string_1,IFIX(start_index));
    if (digit_character == (SI_Long)45L)
	return g2int_read_negative_fixnum_from_string(string_1,start_index,
		end_index);
    else if (digit_character == (SI_Long)43L)
	return g2int_read_positive_fixnum_from_string(string_1,
		FIXNUM_ADD1(start_index),end_index);
    else
	return g2int_read_positive_fixnum_from_string(string_1,start_index,
		end_index);
}

Object G2int_most_positive_int64_floor_10 = UNBOUND;

/* VALUE-TIMES-TEN-PLUS-WEIGHT-<=-MOST-POSITIVE-INT64-P */
Object g2int_value_times_ten_plus_weight_lteq_most_positive_int64_p(value_init,
	    weight_init)
    Object value_init, weight_init;
{
    Object temp;
    SI_int64 value, weight;

    x_note_fn_call(28,67);
    value = INTEGER_TO_INT64(value_init);
    weight = INTEGER_TO_INT64(weight_init);
    if (NUM_LE(INT64_TO_INTEGER(value),G2int_most_positive_int64_floor_10)) {
	temp = minus(G2int_most_positive_int64,
		ltimes(INT64_TO_INTEGER(value),FIX((SI_Long)10L)));
	temp = NUM_LE(INT64_TO_INTEGER(weight),temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_most_negative_int64_ceiling_10 = UNBOUND;

/* VALUE-TIMES-TEN-MINUS-WEIGHT->=-MOST-NEGATIVE-INT64-P */
Object g2int_value_times_ten_minus_weight_gteq_most_negative_int64_p(value_init,
	    weight_init)
    Object value_init, weight_init;
{
    Object temp;
    SI_int64 value, weight;

    x_note_fn_call(28,68);
    value = INTEGER_TO_INT64(value_init);
    weight = INTEGER_TO_INT64(weight_init);
    temp = negate(INT64_TO_INTEGER(value));
    if (NUM_GE(temp,G2int_most_negative_int64_ceiling_10)) {
	temp = minus(ltimes(INT64_TO_INTEGER(value),FIX((SI_Long)10L)),
		G2int_most_negative_int64);
	temp = NUM_LE(INT64_TO_INTEGER(weight),temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* C-READ_FLOAT_FROM_STRING */
Object g2int_c_read_float_from_string(string_1)
    Object string_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(28,69);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = DOUBLE_TO_DOUBLE_FLOAT(g2ext_read_float_from_string(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* READ-FLOAT-FROM-STRING */
Object g2int_read_float_from_string(string_1,inclusive_start_index,
	    exclusive_final_index)
    Object string_1, inclusive_start_index, exclusive_final_index;
{
    Object substring, temp;

    x_note_fn_call(28,70);
    substring = 
	    g2int_obtain_simple_gensym_string(FIXNUM_MINUS(exclusive_final_index,
	    inclusive_start_index));
    g2int_copy_portion_of_wide_string_octets_into_simple_gensym_string(string_1,
	    inclusive_start_index,exclusive_final_index,substring,
	    FIX((SI_Long)0L));
    temp = g2int_c_read_float_from_string(substring);
    g2int_reclaim_gensym_string(substring);
    return VALUES_1(temp);
}

Object G2int_most_positive_fixnum_floor_2 = UNBOUND;

static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

/* READ-TEXT-STRING-ENDING-IN-A-DELIMITTER-FROM-STRING */
Object g2int_read_text_string_ending_in_a_delimitter_from_string(string_1,
	    start_index,end_index,delimitter)
    Object string_1, start_index, end_index, delimitter;
{
    Object current_index, string_ends_in_delimitter_p;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_1, thing, temp, schar_arg_2, schar_new_value, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(28,71);
    current_index = start_index;
    string_ends_in_delimitter_p = Nil;
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      character_1 = Nil;
	    next_loop:
	      if ( !FIXNUM_LT(current_index,end_index))
		  goto end_loop;
	      character_1 = FIX(UBYTE_16_ISAREF_1(string_1,
		      IFIX(current_index)));
	      if (FIXNUM_EQ(character_1,delimitter)) {
		  string_ends_in_delimitter_p = T;
		  goto end;
	      }
	      current_index = FIXNUM_ADD1(current_index);
	      if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		  thing = character_1;
		  g2int_twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( 
			  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			  G2int_total_length_of_current_gensym_string))
		      g2int_extend_current_gensym_string(0);
		  temp = G2int_current_gensym_string;
		  schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		  thing = character_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = 
			  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		  G2int_fill_pointer_for_current_gensym_string = temp;
	      }
	      goto next_loop;
	    end_loop:
	      string_ends_in_delimitter_p = Nil;
	      goto end;
	      string_ends_in_delimitter_p = Qnil;
	    end:;
	      text_string = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_3(text_string,current_index,string_ends_in_delimitter_p);
}

Object G2int_large_mask = UNBOUND;

Object G2int_starrandom_state_arraystar = UNBOUND;

Object G2int_starrandom_state_array_current_pointerstar = UNBOUND;

Object G2int_starrandom_state_array_24_pointerstar = UNBOUND;

Object G2int_random_variation = UNBOUND;

Object G2int_random_variation_2 = UNBOUND;

Object G2int_user_random_seedqm = UNBOUND;

Object G2int_simple_type_specification_prop = UNBOUND;

static Object Qg2int_boolean;      /* boolean */

static Object Qg2int_managed_number;  /* managed-number */

static Object Qg2int_temporary_constant;  /* temporary-constant */

static Object Qg2int_simple_type_specification;  /* simple-type-specification */

static Object Qg2int_or;           /* or */

/* SIMPLE-TYPEP */
Object g2int_simple_typep(instance,type_spec)
    Object instance, type_spec;
{
    Object temp, simple_type_specification, spec, ab_loop_list_;

    x_note_fn_call(28,72);
    if (SYMBOLP(type_spec)) {
	if (EQ(type_spec,Qt))
	    return VALUES_1(T);
	else if (EQ(type_spec,Qnull))
	    return VALUES_1(Nil);
	else if (EQ(type_spec,Qfixnum))
	    return VALUES_1(FIXNUMP(instance) ? T : Nil);
	else if (EQ(type_spec,Qg2int_boolean)) {
	    temp =  !TRUEP(instance) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(EQ(instance,T) ? T : Nil);
	}
	else if (EQ(type_spec,Qg2int_gensym_float))
	    return VALUES_1(FLOATP(instance) ? T : Nil);
	else if (EQ(type_spec,Qg2int_managed_number)) {
	    temp = FIXNUMP(instance) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(instance) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(instance)) == 
			(SI_Long)1L ? T : Nil) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if (INLINE_LONG_VECTOR_P(instance) != (SI_Long)0L)
		return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(instance)) 
			== (SI_Long)1L ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(type_spec,Qg2int_temporary_constant)) {
	    if (SIMPLE_VECTOR_P(instance))
		return VALUES_1(EQ(ISVREF(instance,(SI_Long)0L),
			Qg2_defstruct_structure_name_temporary_constant_g2_struct) 
			? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else {
	    simple_type_specification = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(type_spec),
		    Qg2int_simple_type_specification);
	    if (simple_type_specification)
		return g2int_simple_typep(instance,simple_type_specification);
	    else
		return VALUES_1(Nil);
	}
    }
    else if (CONSP(type_spec)) {
	temp = FIRST(type_spec);
	if (EQ(temp,Qsatisfies)) {
	    temp = SECOND(type_spec);
	    return FUNCALL_1(temp,instance);
	}
	else if (EQ(temp,Qmember))
	    return g2int_memq_function(instance,REST(type_spec));
	else if (EQ(temp,Qg2int_or)) {
	    spec = Nil;
	    ab_loop_list_ = REST(type_spec);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    spec = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (g2int_simple_typep(instance,spec))
		return VALUES_1(T);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

Object G2int_type_error_printer_prop = UNBOUND;

Object G2int_simple_type_writer_prop = UNBOUND;

static Object Qg2int_simple_type_writer;  /* simple-type-writer */

static Object string_constant_2;   /* "~(~S~)" */

/* WRITE-INSTANCE-OF-SIMPLE-TYPE-1 */
Object g2int_write_instance_of_simple_type_1(simple_type_name,instance)
    Object simple_type_name, instance;
{
    Object type_writer, temp;

    x_note_fn_call(28,73);
    type_writer = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(simple_type_name),
	    Qg2int_simple_type_writer);
    if (type_writer) {
	temp = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(simple_type_name),
		Qg2int_simple_type_writer);
	return FUNCALL_1(temp,instance);
    }
    else
	return g2int_tformat(2,string_constant_2,instance);
}

/* MAKE-REGION-STRIP-FUNCTION */
Object g2int_make_region_strip_function(region_strip_top,
	    region_strip_intervals)
    Object region_strip_top, region_strip_intervals;
{
    Object new_cons, gensymed_symbol;

    x_note_fn_call(28,74);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = region_strip_top;
    M_CDR(gensymed_symbol) = region_strip_intervals;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    return VALUES_1(gensymed_symbol);
}

/* POINT-IN-REGION-BOUNDING-BOX-P */
Object g2int_point_in_region_bounding_box_p(box,x,y)
    Object box, x, y;
{
    Object interval, point;

    x_note_fn_call(28,75);
    interval = M_CAR(box);
    point = x;
    if (FIXNUM_GE(point,M_CAR(interval)) && FIXNUM_LT(point,M_CDR(interval))) {
	interval = M_CDR(box);
	point = y;
	if (FIXNUM_GE(point,M_CAR(interval)))
	    return VALUES_1(FIXNUM_LT(point,M_CDR(interval)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-REGION-FROM-RECTANGLE */
Object g2int_make_region_from_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    x_note_fn_call(28,76);
    return VALUES_1(Nil);
}

Object G2int_scratch_rectangle_region = UNBOUND;

Object G2int_the_type_description_of_pending_activity = UNBOUND;

Object G2int_chain_of_available_pending_activitys = UNBOUND;

Object G2int_pending_activity_count = UNBOUND;

/* RECLAIM-PENDING-ACTIVITY-1 */
Object g2int_reclaim_pending_activity_1(pending_activity)
    Object pending_activity;
{
    Object svref_new_value;

    x_note_fn_call(28,77);
    inline_note_reclaim_cons(pending_activity,Nil);
    svref_new_value = G2int_chain_of_available_pending_activitys;
    SVREF(pending_activity,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_pending_activitys = pending_activity;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PENDING-ACTIVITY */
Object g2int_reclaim_structure_for_pending_activity(pending_activity)
    Object pending_activity;
{
    x_note_fn_call(28,78);
    return g2int_reclaim_pending_activity_1(pending_activity);
}

static Object Qg2_defstruct_structure_name_pending_activity_g2_struct;  /* g2-defstruct-structure-name::pending-activity-g2-struct */

/* MAKE-PERMANENT-PENDING-ACTIVITY-STRUCTURE-INTERNAL */
Object g2int_make_permanent_pending_activity_structure_internal()
{
    Object def_structure_pending_activity_variable;
    Object pending_activity_count_new_value;
    Object defstruct_g2_pending_activity_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,79);
    def_structure_pending_activity_variable = Nil;
    pending_activity_count_new_value = 
	    FIXNUM_ADD1(G2int_pending_activity_count);
    G2int_pending_activity_count = pending_activity_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pending_activity_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_pending_activity_variable = the_array;
	SVREF(defstruct_g2_pending_activity_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pending_activity_g2_struct;
	def_structure_pending_activity_variable = 
		defstruct_g2_pending_activity_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pending_activity_variable);
}

/* MAKE-PENDING-ACTIVITY-1 */
Object g2int_make_pending_activity_1(parent_of_pending_activity_qm,
	    name_of_pending_activity,continuation_of_pending_activity_qm)
    Object parent_of_pending_activity_qm, name_of_pending_activity;
    Object continuation_of_pending_activity_qm;
{
    Object def_structure_pending_activity_variable;

    x_note_fn_call(28,80);
    def_structure_pending_activity_variable = 
	    G2int_chain_of_available_pending_activitys;
    if (def_structure_pending_activity_variable) {
	G2int_chain_of_available_pending_activitys = 
		ISVREF(def_structure_pending_activity_variable,(SI_Long)0L);
	SVREF(def_structure_pending_activity_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pending_activity_g2_struct;
    }
    else
	def_structure_pending_activity_variable = 
		g2int_make_permanent_pending_activity_structure_internal();
    inline_note_allocate_cons(def_structure_pending_activity_variable,Nil);
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)2L)) = 
	    parent_of_pending_activity_qm;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)1L)) = 
	    name_of_pending_activity;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)5L)) = 
	    continuation_of_pending_activity_qm;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_pending_activity_variable,FIX((SI_Long)4L)) = T;
    return VALUES_1(def_structure_pending_activity_variable);
}

/* BLOCK-PENDING-ACTIVITY */
Object g2int_block_pending_activity(parent_activity,child_activity)
    Object parent_activity, child_activity;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(28,81);
    gensym_push_modify_macro_arg = child_activity;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(parent_activity,(SI_Long)3L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(parent_activity,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(child_activity);
}

static Object Kfinished;           /* :finished */

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* FINISH-PENDING-ACTIVITY */
Object g2int_finish_pending_activity(pending_activity)
    Object pending_activity;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, parent_qm;
    Object svref_new_value;

    x_note_fn_call(28,82);
    if (ISVREF(pending_activity,(SI_Long)5L)) {
	gensymed_symbol = ISVREF(pending_activity,(SI_Long)5L);
	gensymed_symbol_1 = pending_activity;
	gensymed_symbol_2 = Kfinished;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    parent_qm = ISVREF(pending_activity,(SI_Long)2L);
    if (parent_qm) {
	svref_new_value = g2int_delete_gensym_element_1(pending_activity,
		ISVREF(parent_qm,(SI_Long)3L));
	SVREF(parent_qm,FIX((SI_Long)3L)) = svref_new_value;
	if ( !TRUEP(ISVREF(parent_qm,(SI_Long)3L)))
	    g2int_finish_pending_activity(parent_qm);
    }
    gensymed_symbol = ISVREF(pending_activity,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = pending_activity;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

/* CANCEL-PENDING-ACTIVITY */
Object g2int_cancel_pending_activity(pending_activity)
    Object pending_activity;
{
    x_note_fn_call(28,83);
    g2int_cancel_pending_activity_1(pending_activity);
    return VALUES_1(Nil);
}

static Object Kcanceled;           /* :canceled */

/* CANCEL-PENDING-ACTIVITY-1 */
Object g2int_cancel_pending_activity_1(pending_activity)
    Object pending_activity;
{
    Object child, ab_loop_list_, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;

    x_note_fn_call(28,84);
    child = Nil;
    ab_loop_list_ = ISVREF(pending_activity,(SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    SVREF(child,FIX((SI_Long)2L)) = Nil;
    g2int_cancel_pending_activity_1(child);
    goto next_loop;
  end_loop:;
    if (ISVREF(pending_activity,(SI_Long)5L)) {
	gensymed_symbol = ISVREF(pending_activity,(SI_Long)5L);
	gensymed_symbol_1 = pending_activity;
	gensymed_symbol_2 = Kcanceled;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    }
    gensymed_symbol = ISVREF(pending_activity,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = pending_activity;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* CANCEL-IDENTIFIED-DRAWING-ACTIVITY-IF-ANY */
Object g2int_cancel_identified_drawing_activity_if_any(pending_activity_qm)
    Object pending_activity_qm;
{
    x_note_fn_call(28,85);
    if (pending_activity_qm)
	return g2int_cancel_pending_activity(pending_activity_qm);
    else
	return VALUES_1(Nil);
}

/* CANCEL-LIST-OF-PENDING-ACTIVITY */
Object g2int_cancel_list_of_pending_activity(list_of_pending_activities)
    Object list_of_pending_activities;
{
    Object pending_activity, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, parents, parent;

    x_note_fn_call(28,86);
    pending_activity = Nil;
    ab_loop_list_ = list_of_pending_activities;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pending_activity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(pending_activity,(SI_Long)2L)) {
	ab_loopvar__2 = g2int_gensym_cons_1(pending_activity,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    parents = ab_loopvar_;
    goto end;
    parents = Qnil;
  end:;
    parent = Nil;
    ab_loop_list_ = parents;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    parent = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_cancel_pending_activity(parent);
    goto next_loop_1;
  end_loop_1:
    g2int_reclaim_gensym_list_1(list_of_pending_activities);
    g2int_reclaim_gensym_list_1(parents);
    return VALUES_1(Qnil);
}

/* TEXT-STRING=-GIVEN-INDICES */
Object g2int_text_stringeq_given_indices(string1,string2,start1,end1,
	    start2,end2)
    Object string1, string2, start1, end1, start2, end2;
{
    Object ab_loop_iter_flag_;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;

    x_note_fn_call(28,87);
    length1 = IFIX(FIXNUM_MINUS(end1,start1));
    length2 = IFIX(FIXNUM_MINUS(end2,start2));
    if (length1 != length2)
	return VALUES_1(Nil);
    else {
	index1 = IFIX(start1);
	ab_loop_bind_ = IFIX(end1);
	index2 = IFIX(start2);
	ab_loop_bind__1 = IFIX(end2);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index2 = index2 + (SI_Long)1L;
	if (index2 >= ab_loop_bind__1)
	    goto end_loop;
	if ( !(UBYTE_16_ISAREF_1(string1,index1) == 
		UBYTE_16_ISAREF_1(string2,index2)))
	    return VALUES_1(Nil);
	ab_loop_iter_flag_ = Nil;
	index1 = index1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-EQUAL-GIVEN-INDICES */
Object g2int_text_string_equal_given_indices(string1,string2,start1,end1,
	    start2,end2)
    Object string1, string2, start1, end1, start2, end2;
{
    Object ab_loop_iter_flag_, temp, temp_1;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    SI_Long code;

    x_note_fn_call(28,88);
    length1 = IFIX(FIXNUM_MINUS(end1,start1));
    length2 = IFIX(FIXNUM_MINUS(end2,start2));
    if (length1 != length2)
	return VALUES_1(Nil);
    else {
	index1 = IFIX(start1);
	ab_loop_bind_ = IFIX(end1);
	index2 = IFIX(start2);
	ab_loop_bind__1 = IFIX(end2);
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index2 = index2 + (SI_Long)1L;
	if (index2 >= ab_loop_bind__1)
	    goto end_loop;
	code = UBYTE_16_ISAREF_1(string1,index1);
	if (code < (SI_Long)127L)
	    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? FIX(code 
		    + (SI_Long)32L) : FIX(code);
	else {
	    temp = g2int_unicode_lowercase_if_uppercase(FIX(code));
	    if (temp);
	    else
		temp = FIX(code);
	}
	code = UBYTE_16_ISAREF_1(string2,index2);
	if (code < (SI_Long)127L)
	    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
		    FIX(code + (SI_Long)32L) : FIX(code);
	else {
	    temp_1 = g2int_unicode_lowercase_if_uppercase(FIX(code));
	    if (temp_1);
	    else
		temp_1 = FIX(code);
	}
	if ( !NUM_EQ(temp,temp_1))
	    return VALUES_1(Nil);
	ab_loop_iter_flag_ = Nil;
	index1 = index1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

/* TEXT-STRING-PARSE-INTEGER-FUNCTION */
Object g2int_text_string_parse_integer_function(string_1,start,end,
	    junk_allowed)
    Object string_1, start, end, junk_allowed;
{
    Object length_1, accum, parsing_started_p, this_char, this_digit_qm, temp;
    SI_Long index_1, ab_loop_bind_, index2;
    char temp_1;

    x_note_fn_call(28,89);
    length_1 = g2int_text_string_length(string_1);
    if ( !TRUEP(end))
	end = length_1;
    if (IFIX(start) < (SI_Long)0L || IFIX(end) < (SI_Long)0L || 
	    FIXNUM_GT(start,length_1) || FIXNUM_GT(end,length_1) || 
	    FIXNUM_GT(start,end))
	return VALUES_1(Nil);
    else {
	index_1 = IFIX(start);
	ab_loop_bind_ = IFIX(end);
	accum = FIX((SI_Long)0L);
	parsing_started_p = Nil;
	this_char = Nil;
	this_digit_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	this_char = FIX(UBYTE_16_ISAREF_1(string_1,index_1));
	temp = this_char;
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    this_digit_qm = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 48:
		this_digit_qm = FIX((SI_Long)0L);
		break;
	      case 49:
		this_digit_qm = FIX((SI_Long)1L);
		break;
	      case 50:
		this_digit_qm = FIX((SI_Long)2L);
		break;
	      case 51:
		this_digit_qm = FIX((SI_Long)3L);
		break;
	      case 52:
		this_digit_qm = FIX((SI_Long)4L);
		break;
	      case 53:
		this_digit_qm = FIX((SI_Long)5L);
		break;
	      case 54:
		this_digit_qm = FIX((SI_Long)6L);
		break;
	      case 55:
		this_digit_qm = FIX((SI_Long)7L);
		break;
	      case 56:
		this_digit_qm = FIX((SI_Long)8L);
		break;
	      case 57:
		this_digit_qm = FIX((SI_Long)9L);
		break;
	      default:
		this_digit_qm = Nil;
		break;
	    }
	if ( !TRUEP(parsing_started_p) && this_digit_qm)
	    parsing_started_p = T;
	if (g2int_blank_p(this_char)) {
	    if (parsing_started_p && junk_allowed)
		return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
	    else if (parsing_started_p) {
		index2 = index_1;
		ab_loop_bind_ = IFIX(end);
		this_char = Nil;
	      next_loop_1:
		if (index2 >= ab_loop_bind_)
		    goto end_loop_1;
		this_char = FIX(UBYTE_16_ISAREF_1(string_1,index2));
		if ( !TRUEP(g2int_blank_p(this_char))) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		index2 = index2 + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
		if (temp_1)
		    return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
		else
		    return VALUES_2(Nil,Nil);
	    }
	}
	else if (this_digit_qm)
	    accum = FIX(IFIX(accum) * (SI_Long)10L + IFIX(this_digit_qm));
	else if (junk_allowed && parsing_started_p)
	    return VALUES_2(accum,FIX(index_1 + (SI_Long)1L));
	else if (junk_allowed);
	else
	    return VALUES_2(Nil,Nil);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_2(accum,FIX(index_1));
	return VALUES_1(Qnil);
    }
}

/* COMMAND-LINE-TOKEN-EQUAL-GIVEN-INDICES */
Object g2int_command_line_token_equal_given_indices(token1,token2,start1,
	    end1,start2,end2)
    Object token1, token2, start1, end1, start2, end2;
{
    x_note_fn_call(28,90);
    if (EQ(G2int_g2_machine_type,Qg2int_vms))
	return g2int_text_string_equal_given_indices(token1,token2,start1,
		end1,start2,end2);
    else
	return g2int_text_stringeq_given_indices(token1,token2,start1,end1,
		start2,end2);
}

static Object array_constant;      /* # */

/* COMMAND-LINE-KEYWORD-P */
Object g2int_command_line_keyword_p(keyword_as_text_string)
    Object keyword_as_text_string;
{
    x_note_fn_call(28,91);
    return g2int_text_string_equal_given_indices(keyword_as_text_string,
	    array_constant,FIX((SI_Long)0L),FIX((SI_Long)1L),
	    FIX((SI_Long)0L),FIX((SI_Long)1L));
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT */
Object g2int_get_command_line_keyword_argument varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number, no_import_p, keyword_as_text_string;
    Object matching_keyword_instance, arg_qm, temp, temp_1;
    SI_Long keyword_comparison_start_index, i;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,92);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    no_import_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    keyword_as_text_string = g2int_copy_text_string(keyword);
    keyword_comparison_start_index = 
	    g2int_command_line_keyword_p(keyword_as_text_string) ? 
	    (SI_Long)1L : (SI_Long)0L;
    matching_keyword_instance = FIX((SI_Long)0L);
    i = (SI_Long)1L;
    arg_qm = Nil;
  next_loop:
    arg_qm = g2int_get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if (g2int_command_line_keyword_p(arg_qm)) {
	temp = arg_qm;
	temp_1 = g2int_text_string_length(arg_qm);
	if (g2int_text_string_equal_given_indices(temp,
		keyword_as_text_string,FIX((SI_Long)1L),temp_1,
		FIX(keyword_comparison_start_index),
		g2int_text_string_length(keyword_as_text_string))) {
	    matching_keyword_instance = FIXNUM_ADD1(matching_keyword_instance);
	    temp_2 = TRUEP(matching_keyword_instance);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_EQ(matching_keyword_instance,
	    keyword_instance_number) : TRUEP(Nil)) {
	temp = no_import_p ? g2int_get_gensym_command_line_argument(FIX(i 
		+ (SI_Long)1L)) : 
		g2int_get_gensym_command_line_argument_as_text_string(FIX(i 
		+ (SI_Long)1L));
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    g2int_reclaim_text_string(keyword_as_text_string);
    return VALUES_1(temp);
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT-AS-INTEGER */
Object g2int_get_command_line_keyword_argument_as_integer varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number_qm, arg_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,93);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    END_ARGS_nonrelocating();
    arg_qm = g2int_get_command_line_keyword_argument(2,keyword,
	    keyword_instance_number_qm);
    if (arg_qm)
	return g2int_text_string_parse_integer_function(arg_qm,
		FIX((SI_Long)0L),Nil,T);
    else
	return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-KEYWORD-ARGUMENT-AS-MEMORY-SIZE */
Object g2int_get_command_line_keyword_argument_as_memory_size varargs_1(int, n)
{
    Object keyword;
    Object keyword_instance_number_qm, arg_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,94);
    INIT_ARGS_nonrelocating();
    keyword = REQUIRED_ARG_nonrelocating();
    keyword_instance_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)1L);
    END_ARGS_nonrelocating();
    arg_qm = g2int_get_command_line_keyword_argument(2,keyword,
	    keyword_instance_number_qm);
    if (arg_qm)
	return g2int_read_memory_size_from_string(arg_qm);
    else
	return VALUES_1(Nil);
}

/* READ-MEMORY-SIZE-FROM-STRING */
Object g2int_read_memory_size_from_string(string_1)
    Object string_1;
{
    x_note_fn_call(28,95);
    return l_abs(g2int_read_float_from_string(string_1,FIX((SI_Long)0L),
	    length(string_1)));
}

/* GET-COMMAND-LINE-FLAG-ARGUMENT */
Object g2int_get_command_line_flag_argument varargs_1(int, n)
{
    Object flag;
    Object require_hyphen_qm, flag_as_text_string, arg_qm, temp, temp_1;
    SI_Long flag_comparison_start_index, i;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,96);
    INIT_ARGS_nonrelocating();
    flag = REQUIRED_ARG_nonrelocating();
    require_hyphen_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    flag_as_text_string = g2int_copy_text_string(flag);
    flag_comparison_start_index = 
	    g2int_command_line_keyword_p(flag_as_text_string) ? 
	    (SI_Long)1L : (SI_Long)0L;
    i = (SI_Long)1L;
    arg_qm = Nil;
  next_loop:
    arg_qm = g2int_get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if ( !TRUEP(g2int_command_line_keyword_p(arg_qm))) {
	if ( !TRUEP(require_hyphen_qm)) {
	    temp = arg_qm;
	    temp_1 = g2int_text_string_length(arg_qm);
	    temp_2 = TRUEP(g2int_text_string_equal_given_indices(temp,
		    flag_as_text_string,FIX((SI_Long)0L),temp_1,
		    FIX(flag_comparison_start_index),
		    g2int_text_string_length(flag_as_text_string)));
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else {
	temp = arg_qm;
	temp_1 = g2int_text_string_length(arg_qm);
	temp_2 = TRUEP(g2int_text_string_equal_given_indices(temp,
		flag_as_text_string,FIX((SI_Long)1L),temp_1,
		FIX(flag_comparison_start_index),
		g2int_text_string_length(flag_as_text_string)));
    }
    if (temp_2) {
	temp_1 = arg_qm;
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end:;
    g2int_reclaim_text_string(flag_as_text_string);
    return VALUES_1(temp_1);
}

/* GET-GENSYM-ENVIRONMENT-VARIABLE */
Object g2int_get_gensym_environment_variable(variable_name_string)
    Object variable_name_string;
{
    x_note_fn_call(28,97);
    return g2int_foreign_get_environment_variable(variable_name_string);
}

/* READ-NUMBER-FOR-GENSYM-ENVIRONMENT-VARIABLE */
Object g2int_read_number_for_gensym_environment_variable(variable_name)
    Object variable_name;
{
    Object string_to_parse_qm, temp;

    x_note_fn_call(28,98);
    string_to_parse_qm = g2int_get_gensym_environment_variable(variable_name);
    if (string_to_parse_qm) {
	temp = g2int_text_string_parse_integer_function(string_to_parse_qm,
		FIX((SI_Long)0L),Nil,T);
	g2int_reclaim_text_string(string_to_parse_qm);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* READ-MEMORY-SIZE-FOR-GENSYM-ENVIRONMENT-VARIABLE */
Object g2int_read_memory_size_for_gensym_environment_variable(variable_name)
    Object variable_name;
{
    Object string_to_parse_qm, temp;

    x_note_fn_call(28,99);
    string_to_parse_qm = g2int_get_gensym_environment_variable(variable_name);
    if (string_to_parse_qm) {
	temp = g2int_read_memory_size_from_string(string_to_parse_qm);
	g2int_reclaim_text_string(string_to_parse_qm);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_cached_gensym_user_home_directory = UNBOUND;

Object G2int_all_command_line_keyword_arguments = UNBOUND;

/* GET-ALL-COMMAND-LINE-KEYWORD-ARGUMENTS */
Object g2int_get_all_command_line_keyword_arguments(keyword)
    Object keyword;
{
    Object arg_qm, this_keyword_argument_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, temp_1;
    SI_Long keyword_comparison_start_index, i;
    char temp_2;

    x_note_fn_call(28,100);
    keyword_comparison_start_index = g2int_command_line_keyword_p(keyword) 
	    ? (SI_Long)1L : (SI_Long)0L;
    i = (SI_Long)1L;
    arg_qm = Nil;
    this_keyword_argument_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    arg_qm = g2int_get_gensym_command_line_argument_as_text_string(FIX(i));
    if ( !TRUEP(arg_qm))
	goto end_loop;
    if (g2int_command_line_keyword_p(arg_qm)) {
	temp = arg_qm;
	temp_1 = g2int_text_string_length(arg_qm);
	temp_2 = TRUEP(g2int_text_string_equal_given_indices(temp,keyword,
		FIX((SI_Long)1L),temp_1,
		FIX(keyword_comparison_start_index),
		g2int_text_string_length(keyword)));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	this_keyword_argument_qm = 
		g2int_get_gensym_command_line_argument_as_text_string(FIX(i 
		+ (SI_Long)1L));
	temp_2 = TRUEP(this_keyword_argument_qm);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	ab_loopvar__2 = g2int_gensym_cons_1(this_keyword_argument_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object G2int_command_line_plist_element_getter_prop = UNBOUND;

Object G2int_command_line_argument_processor_prop = UNBOUND;

Object G2int_all_known_command_line_plist_elements = UNBOUND;

Object G2int_used_positional_command_line_argument_default = UNBOUND;

static Object Qg2int_command_line_plist_element_getter;  /* command-line-plist-element-getter */

/* GET-COMMAND-LINE-ARGUMENTS */
Object g2int_get_command_line_arguments()
{
    Object used_positional_command_line_argument_default, indicator;
    Object ab_loop_list_, value_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_;
    Declare_special(1);
    Object result;

    x_note_fn_call(28,101);
    used_positional_command_line_argument_default = Nil;
    PUSH_SPECIAL(G2int_used_positional_command_line_argument_default,used_positional_command_line_argument_default,
	    0);
      indicator = Nil;
      ab_loop_list_ = G2int_all_known_command_line_plist_elements;
      value_qm = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      indicator = CAR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      value_qm = 
	      FUNCALL_0(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(indicator),
	      Qg2int_command_line_plist_element_getter));
      ab_loopvar__2 = value_qm ? g2int_gensym_list_2(indicator,value_qm) : Nil;
      if (ab_loopvar__2) {
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = last(ab_loopvar__2,_);
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar_);
      goto end;
      result = VALUES_1(Qnil);
    end:;
    POP_SPECIAL();
    return result;
}

/* GET-INITIAL-COMMAND-LINE-ARGUMENTS */
Object g2int_get_initial_command_line_arguments()
{
    x_note_fn_call(28,102);
    G2int_all_known_command_line_plist_elements = 
	    g2int_sort_list(G2int_all_known_command_line_plist_elements,
	    Qnum_lt,Qcdr);
    return g2int_get_command_line_arguments();
}

Object G2int_command_line_arguments = UNBOUND;

/* COMMAND-LINE-PROCESS-PASSWORD */
Object g2int_command_line_process_password(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,103);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PASSWORD */
Object g2int_get_command_line_plist_element_for_password()
{
    x_note_fn_call(28,104);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-LANGUAGE */
Object g2int_command_line_process_language(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,105);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LANGUAGE */
Object g2int_get_command_line_plist_element_for_language()
{
    x_note_fn_call(28,106);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-CJK-LANGUAGE */
Object g2int_command_line_process_cjk_language(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,107);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CJK-LANGUAGE */
Object g2int_get_command_line_plist_element_for_cjk_language()
{
    x_note_fn_call(28,108);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-INIT-STRING */
Object g2int_command_line_process_init_string(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,109);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-INIT-STRING */
Object g2int_get_command_line_plist_element_for_init_string()
{
    x_note_fn_call(28,110);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-DISCARD-USER-SETTINGS */
Object g2int_command_line_process_discard_user_settings(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,111);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DISCARD-USER-SETTINGS */
Object g2int_get_command_line_plist_element_for_discard_user_settings()
{
    x_note_fn_call(28,112);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-USER-MODE */
Object g2int_command_line_process_user_mode(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,113);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-MODE */
Object g2int_get_command_line_plist_element_for_user_mode()
{
    x_note_fn_call(28,114);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-WINDOW */
Object g2int_command_line_process_window(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,115);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW */
Object g2int_get_command_line_plist_element_for_window()
{
    x_note_fn_call(28,116);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-USER-NAME */
Object g2int_command_line_process_user_name(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,117);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-NAME */
Object g2int_get_command_line_plist_element_for_user_name()
{
    x_note_fn_call(28,118);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-WINDOWHANDLE */
Object g2int_command_line_process_windowhandle(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,119);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOWHANDLE */
Object g2int_get_command_line_plist_element_for_windowhandle()
{
    x_note_fn_call(28,120);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "windowhandle" */

static Object string_constant_4;   /* "" */

/* GET-PARENT-WINDOWHANDLE */
Object g2int_get_parent_windowhandle()
{
    Object temp;

    x_note_fn_call(28,121);
    temp = g2int_get_command_line_keyword_argument(1,string_constant_3);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_4);
}

/* COMMAND-LINE-PROCESS-WINDOW-STYLE */
Object g2int_command_line_process_window_style(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,122);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW-STYLE */
Object g2int_get_command_line_plist_element_for_window_style()
{
    x_note_fn_call(28,123);
    return VALUES_1(Nil);
}

static Object list_constant_2;     /* # */

static Object string_constant_5;   /* "The ~a argument ~s is not recognized. It should be one of ~L,|" */

/* VALIDATE-WINDOW-STYLE-COMMAND-LINE-ARGUMENT */
Object g2int_validate_window_style_command_line_argument(argument,
	    argument_string)
    Object argument, argument_string;
{
    Object styles, style, ab_loop_list_;

    x_note_fn_call(28,124);
    styles = list_constant_2;
    style = Nil;
    ab_loop_list_ = styles;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    style = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (g2int_string_equalw(argument,g2int_symbol_namew(style)))
	return VALUES_1(style);
    goto next_loop;
  end_loop:
    g2int_notify_user_at_console(4,string_constant_5,argument_string,
	    argument,styles);
    return VALUES_1(Qnil);
}

/* COMMAND-LINE-PROCESS-NO-NATIVE-FONTS */
Object g2int_command_line_process_no_native_fonts(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,125);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-FONTS */
Object g2int_get_command_line_plist_element_for_no_native_fonts()
{
    x_note_fn_call(28,126);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-NATIVE-FONTS */
Object g2int_command_line_process_native_fonts(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,127);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NATIVE-FONTS */
Object g2int_get_command_line_plist_element_for_native_fonts()
{
    x_note_fn_call(28,128);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-NO-NATIVE-CLIPBOARD */
Object g2int_command_line_process_no_native_clipboard(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,129);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-CLIPBOARD */
Object g2int_get_command_line_plist_element_for_no_native_clipboard()
{
    x_note_fn_call(28,130);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-G2PASSWDEXE */
Object g2int_command_line_process_g2passwdexe(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,131);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-G2PASSWDEXE */
Object g2int_get_command_line_plist_element_for_g2passwdexe()
{
    x_note_fn_call(28,132);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-NO-BACKING-STORE */
Object g2int_command_line_process_no_backing_store(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,133);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-BACKING-STORE */
Object g2int_get_command_line_plist_element_for_no_backing_store()
{
    x_note_fn_call(28,134);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-PRIVATE-COLORMAP */
Object g2int_command_line_process_private_colormap(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,135);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PRIVATE-COLORMAP */
Object g2int_get_command_line_plist_element_for_private_colormap()
{
    x_note_fn_call(28,136);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-FILE-OPERATION-TIMEOUT */
Object g2int_command_line_process_file_operation_timeout(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,137);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-FILE-OPERATION-TIMEOUT */
Object g2int_get_command_line_plist_element_for_file_operation_timeout()
{
    x_note_fn_call(28,138);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-USE-OS-EMULATION */
Object g2int_command_line_process_use_os_emulation(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,139);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-OS-EMULATION */
Object g2int_get_command_line_plist_element_for_use_os_emulation()
{
    x_note_fn_call(28,140);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-COPY-MESSAGES-ON-LOGBOOK */
Object g2int_command_line_process_copy_messages_on_logbook(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,141);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-MESSAGES-ON-LOGBOOK */
Object g2int_get_command_line_plist_element_for_copy_messages_on_logbook()
{
    x_note_fn_call(28,142);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-COPY-LOGBOOK-ON-CONSOLE */
Object g2int_command_line_process_copy_logbook_on_console(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,143);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-LOGBOOK-ON-CONSOLE */
Object g2int_get_command_line_plist_element_for_copy_logbook_on_console()
{
    x_note_fn_call(28,144);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-DEBUG-FRAME-REFERENCE-BALANCE */
Object g2int_command_line_process_debug_frame_reference_balance(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,145);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEBUG-FRAME-REFERENCE-BALANCE */
Object g2int_get_command_line_plist_element_for_debug_frame_reference_balance()
{
    x_note_fn_call(28,146);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-XCLIP */
Object g2int_command_line_process_xclip(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,147);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-XCLIP */
Object g2int_get_command_line_plist_element_for_xclip()
{
    x_note_fn_call(28,148);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-BACKGROUND */
Object g2int_command_line_process_background(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,149);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-BACKGROUND */
Object g2int_get_command_line_plist_element_for_background()
{
    x_note_fn_call(28,150);
    return VALUES_1(Nil);
}

Object G2int_known_ui_styles = UNBOUND;

/* COMMAND-LINE-PROCESS-UI */
Object g2int_command_line_process_ui(value_qm)
    Object value_qm;
{
    x_note_fn_call(28,151);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-UI */
Object g2int_get_command_line_plist_element_for_ui()
{
    x_note_fn_call(28,152);
    return VALUES_1(Nil);
}

/* PARSE-UI-STYLE */
Object g2int_parse_ui_style(value_qm)
    Object value_qm;
{
    Object ui, ab_loop_list_, temp;

    x_note_fn_call(28,153);
    if ( !TRUEP(value_qm))
	return g2int_gensym_default_ui();
    else {
	ui = Nil;
	ab_loop_list_ = G2int_known_ui_styles;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ui = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (g2int_string_equalw(value_qm,g2int_stringw(ui))) {
	    temp = ui;
	    goto end;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qg2int_standard;     /* standard */

/* GENSYM-DEFAULT-UI */
Object g2int_gensym_default_ui()
{
    x_note_fn_call(28,154);
    return VALUES_1(Qg2int_standard);
}

/* COMMAND-LINE-PROCESS-NETINFO */
Object g2int_command_line_process_netinfo(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,155);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETINFO */
Object g2int_get_command_line_plist_element_for_netinfo()
{
    x_note_fn_call(28,156);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-VERBOSE */
Object g2int_command_line_process_verbose(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,157);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-VERBOSE */
Object g2int_get_command_line_plist_element_for_verbose()
{
    x_note_fn_call(28,158);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-SILENT */
Object g2int_command_line_process_silent(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,159);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SILENT */
Object g2int_get_command_line_plist_element_for_silent()
{
    x_note_fn_call(28,160);
    return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-EXIT-ON-ABORT */
Object g2int_command_line_process_exit_on_abort(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,161);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-EXIT-ON-ABORT */
Object g2int_get_command_line_plist_element_for_exit_on_abort()
{
    x_note_fn_call(28,162);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

/* EXIT-ON-ABORT-P */
Object g2int_exit_on_abort_p()
{
    Object temp;

    x_note_fn_call(28,163);
    temp = g2int_get_command_line_flag_argument(1,array_constant_1);
    return VALUES_1(temp);
}

/* COMMAND-LINE-PROCESS-USE-JIT */
Object g2int_command_line_process_use_jit(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,164);
    return VALUES_1(Nil);
}

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-JIT */
Object g2int_get_command_line_plist_element_for_use_jit()
{
    x_note_fn_call(28,165);
    return VALUES_1(Nil);
}

Object G2int_use_jit_p = UNBOUND;

Object G2int_secure_icp_initialized_p = UNBOUND;

Object G2int_secure_icp_default_p = UNBOUND;

Object G2int_cache_server_cert_name = UNBOUND;

/* COMMAND-LINE-PROCESS-SECURE */
Object g2int_command_line_process_secure(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,166);
    return VALUES_1(arg_qm);
}

static Object array_constant_2;    /* # */

static Object Qg2int_secure;       /* secure */

static Object Qg2int_command_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SECURE */
Object g2int_get_command_line_plist_element_for_secure()
{
    Object arg_qm, temp;

    x_note_fn_call(28,167);
    arg_qm = g2int_get_command_line_flag_argument(2,array_constant_2,T);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_secure),
	    Qg2int_command_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object array_constant_3;    /* # */

/* SECURE-ICP-REQUESTED-P */
Object g2int_secure_icp_requested_p()
{
    x_note_fn_call(28,168);
    return g2int_get_command_line_flag_argument(1,array_constant_3);
}

/* COMMAND-LINE-PROCESS-CERT */
Object g2int_command_line_process_cert(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(28,169);
    return VALUES_1(arg_qm);
}

static Object array_constant_4;    /* # */

static Object Qg2int_cert;         /* cert */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CERT */
Object g2int_get_command_line_plist_element_for_cert()
{
    Object arg_qm, temp;

    x_note_fn_call(28,170);
    arg_qm = g2int_get_command_line_keyword_argument(1,array_constant_4);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_cert),
	    Qg2int_command_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* UPDATE-SERVER-CERTIFICATE */
Object g2int_update_server_certificate(newcert)
    Object newcert;
{
    x_note_fn_call(28,171);
    if ( !TRUEP(G2int_secure_icp_initialized_p)) {
	G2int_cache_server_cert_name = newcert;
	return VALUES_1(G2int_cache_server_cert_name);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_6;   /* "cert" */

static Object string_constant_7;   /* "G2_CERT" */

/* SERVER-CERTIFICATE-NAME */
Object g2int_server_certificate_name()
{
    Object temp;

    x_note_fn_call(28,172);
    temp = g2int_get_command_line_keyword_argument(1,string_constant_6);
    if (temp);
    else
	temp = G2int_cache_server_cert_name;
    if (temp)
	return VALUES_1(temp);
    else {
	G2int_cache_server_cert_name = 
		g2int_get_gensym_environment_variable(string_constant_7);
	return VALUES_1(G2int_cache_server_cert_name);
    }
}

/* STRING-PREFIX=W */
Object g2int_string_prefixeqw(prefix,string_1)
    Object prefix, string_1;
{
    SI_Long length_1, length_2, i, ab_loop_bind_;

    x_note_fn_call(28,173);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(prefix));
    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LE(FIX(UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    FIX(UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_2 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)))) {
	i = (SI_Long)0L;
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(prefix));
	ab_loop_bind_ = UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)2L) + 
		((UBYTE_16_ISAREF_1(prefix,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( !(UBYTE_16_ISAREF_1(prefix,i) == UBYTE_16_ISAREF_1(string_1,i)))
	    return VALUES_1(Nil);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Knetwork_type;       /* :network-type */

static Object Kuse_default;        /* :use-default */

static Object Ksecure_p;           /* :secure-p */

static Object array_constant_5;    /* # */

static Object string_constant_8;   /* "/SSL" */

/* SECURE-ICP-STRING */
Object g2int_secure_icp_string varargs_1(int, n)
{
    Object network_type_p, network_type, use_default_p, use_default;
    Object secure_p_p, secure_p;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(28,174);
    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    network_type_p = KEYWORD_ARG_P(Knetwork_type);
    network_type = network_type_p ? KEYWORD_ARG(network_type_p) : Nil;
    use_default_p = KEYWORD_ARG_P(Kuse_default);
    use_default = use_default_p ? KEYWORD_ARG(use_default_p) : Nil;
    secure_p_p = KEYWORD_ARG_P(Ksecure_p);
    secure_p = secure_p_p ? KEYWORD_ARG(secure_p_p) : T;
    if (secure_p && ( !TRUEP(network_type) || 
	    g2int_string_prefixeqw(array_constant_5,network_type)) && 
	    (use_default ? TRUEP(G2int_secure_icp_default_p) : 
	    TRUEP(G2int_secure_icp_initialized_p))) {
	RESTORE_STACK();
	return VALUES_1(string_constant_8);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(string_constant_4);
    }
}

/* C-SET-SECURE-ICP */
Object g2int_c_set_secure_icp(certificate)
    Object certificate;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(28,175);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(certificate);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = certificate;
    temp = FIX(g2ext_set_secure_icp(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

static Object string_constant_9;   /* "WARNING: SSL encryption is not available in this executable." */

/* SET-UP-SECURE-ICP */
Object g2int_set_up_secure_icp varargs_1(int, n)
{
    Object default_p, temp, rc;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,176);
    INIT_ARGS_nonrelocating();
    default_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(G2int_secure_icp_initialized_p)) {
	temp = g2int_server_certificate_name();
	if (temp);
	else
	    temp = string_constant_4;
	rc = g2int_c_set_secure_icp(temp);
	if (IFIX(rc) == (SI_Long)0L)
	    g2int_notify_user_at_console(1,string_constant_9);
	G2int_secure_icp_default_p = default_p;
	G2int_secure_icp_initialized_p = IFIX(rc) != (SI_Long)0L ? T : Nil;
	return VALUES_1(G2int_secure_icp_initialized_p);
    }
    else
	return VALUES_1(Nil);
}

/* COMMAND-LINE-PROCESS-ICP-LOG-INTENSITY */
Object g2int_command_line_process_icp_log_intensity(value_qm)
    Object value_qm;
{
    Object integer_qm;

    x_note_fn_call(28,177);
    if (value_qm) {
	integer_qm = g2int_read_fixnum_from_string(1,value_qm);
	if (integer_qm);
	else
	    integer_qm = FIX((SI_Long)7L);
    }
    else
	integer_qm = Nil;
    if (integer_qm) {
	if (IFIX(integer_qm) < (SI_Long)0L || IFIX(integer_qm) > (SI_Long)6L)
	    integer_qm = FIX((SI_Long)7L);
    }
    return VALUES_1(integer_qm);
}

static Object array_constant_6;    /* # */

static Object Qg2int_icp_log_intensity;  /* icp-log-intensity */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ICP-LOG-INTENSITY */
Object g2int_get_command_line_plist_element_for_icp_log_intensity()
{
    Object value_qm, temp;

    x_note_fn_call(28,178);
    value_qm = g2int_get_command_line_keyword_argument(1,array_constant_6);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2int_icp_log_intensity),
	    Qg2int_command_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

Object G2int_foreign_struct_info_prop = UNBOUND;

Object G2int_the_type_description_of_foreign_struct_info = UNBOUND;

Object G2int_chain_of_available_foreign_struct_infos = UNBOUND;

Object G2int_foreign_struct_info_count = UNBOUND;

/* RECLAIM-FOREIGN-STRUCT-INFO-1 */
Object g2int_reclaim_foreign_struct_info_1(foreign_struct_info)
    Object foreign_struct_info;
{
    Object svref_new_value;

    x_note_fn_call(28,179);
    inline_note_reclaim_cons(foreign_struct_info,Nil);
    svref_new_value = G2int_chain_of_available_foreign_struct_infos;
    SVREF(foreign_struct_info,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_foreign_struct_infos = foreign_struct_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FOREIGN-STRUCT-INFO */
Object g2int_reclaim_structure_for_foreign_struct_info(foreign_struct_info)
    Object foreign_struct_info;
{
    x_note_fn_call(28,180);
    return g2int_reclaim_foreign_struct_info_1(foreign_struct_info);
}

static Object Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;  /* g2-defstruct-structure-name::foreign-struct-info-g2-struct */

/* MAKE-PERMANENT-FOREIGN-STRUCT-INFO-STRUCTURE-INTERNAL */
Object g2int_make_permanent_foreign_struct_info_structure_internal()
{
    Object def_structure_foreign_struct_info_variable;
    Object foreign_struct_info_count_new_value;
    Object defstruct_g2_foreign_struct_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,181);
    def_structure_foreign_struct_info_variable = Nil;
    foreign_struct_info_count_new_value = 
	    FIXNUM_ADD1(G2int_foreign_struct_info_count);
    G2int_foreign_struct_info_count = foreign_struct_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_foreign_struct_info_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_foreign_struct_info_variable = the_array;
	SVREF(defstruct_g2_foreign_struct_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;
	def_structure_foreign_struct_info_variable = 
		defstruct_g2_foreign_struct_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_foreign_struct_info_variable);
}

/* MAKE-FOREIGN-STRUCT-INFO-1 */
Object g2int_make_foreign_struct_info_1()
{
    Object def_structure_foreign_struct_info_variable;

    x_note_fn_call(28,182);
    def_structure_foreign_struct_info_variable = 
	    G2int_chain_of_available_foreign_struct_infos;
    if (def_structure_foreign_struct_info_variable) {
	G2int_chain_of_available_foreign_struct_infos = 
		ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)0L);
	SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_foreign_struct_info_g2_struct;
    }
    else
	def_structure_foreign_struct_info_variable = 
		g2int_make_permanent_foreign_struct_info_structure_internal();
    inline_note_allocate_cons(def_structure_foreign_struct_info_variable,Nil);
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_foreign_struct_info_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_foreign_struct_info_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_foreign_struct_info_variable);
}

Object G2int_next_eq_hash_value = UNBOUND;

Object G2int_the_type_description_of_eq_hash_table = UNBOUND;

Object G2int_chain_of_available_eq_hash_tables = UNBOUND;

Object G2int_eq_hash_table_count = UNBOUND;

/* RECLAIM-EQ-HASH-TABLE-INTERNAL-1 */
Object g2int_reclaim_eq_hash_table_internal_1(eq_hash_table)
    Object eq_hash_table;
{
    Object svref_new_value;

    x_note_fn_call(28,183);
    inline_note_reclaim_cons(eq_hash_table,Nil);
    svref_new_value = G2int_chain_of_available_eq_hash_tables;
    SVREF(eq_hash_table,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_eq_hash_tables = eq_hash_table;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EQ-HASH-TABLE */
Object g2int_reclaim_structure_for_eq_hash_table(eq_hash_table)
    Object eq_hash_table;
{
    x_note_fn_call(28,184);
    return g2int_reclaim_eq_hash_table_internal_1(eq_hash_table);
}

static Object Qg2_defstruct_structure_name_eq_hash_table_g2_struct;  /* g2-defstruct-structure-name::eq-hash-table-g2-struct */

/* MAKE-PERMANENT-EQ-HASH-TABLE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_eq_hash_table_structure_internal()
{
    Object def_structure_eq_hash_table_variable, eq_hash_table_count_new_value;
    Object defstruct_g2_eq_hash_table_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(28,185);
    def_structure_eq_hash_table_variable = Nil;
    eq_hash_table_count_new_value = FIXNUM_ADD1(G2int_eq_hash_table_count);
    G2int_eq_hash_table_count = eq_hash_table_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_eq_hash_table_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_eq_hash_table_variable = the_array;
	SVREF(defstruct_g2_eq_hash_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_eq_hash_table_g2_struct;
	def_structure_eq_hash_table_variable = 
		defstruct_g2_eq_hash_table_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_eq_hash_table_variable);
}

/* MAKE-EQ-HASH-TABLE-INTERNAL-1 */
Object g2int_make_eq_hash_table_internal_1()
{
    Object def_structure_eq_hash_table_variable;

    x_note_fn_call(28,186);
    def_structure_eq_hash_table_variable = 
	    G2int_chain_of_available_eq_hash_tables;
    if (def_structure_eq_hash_table_variable) {
	G2int_chain_of_available_eq_hash_tables = 
		ISVREF(def_structure_eq_hash_table_variable,(SI_Long)0L);
	SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_eq_hash_table_g2_struct;
    }
    else
	def_structure_eq_hash_table_variable = 
		g2int_make_permanent_eq_hash_table_structure_internal();
    inline_note_allocate_cons(def_structure_eq_hash_table_variable,Nil);
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_eq_hash_table_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_eq_hash_table_variable);
}

/* MAKE-EQ-HASH-TABLE */
Object g2int_make_eq_hash_table(size,key_reclaimer_qm,value_reclaimer_qm)
    Object size, key_reclaimer_qm, value_reclaimer_qm;
{
    Object table, vec, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,187);
    table = g2int_make_eq_hash_table_internal_1();
    vec = g2int_allocate_managed_simple_vector(size);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(vec,i) = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    svref_new_value = vec;
    goto end;
    svref_new_value = Qnil;
  end:;
    SVREF(table,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(table,FIX((SI_Long)2L)) = size;
    ISVREF(table,(SI_Long)3L) = FIX((SI_Long)0L);
    SVREF(table,FIX((SI_Long)4L)) = key_reclaimer_qm;
    SVREF(table,FIX((SI_Long)5L)) = value_reclaimer_qm;
    return VALUES_1(table);
}

/* EQ-HASH-TABLE-KEYS */
Object g2int_eq_hash_table_keys(table)
    Object table;
{
    Object vector_1, length_1, result_1, chain, pair, ab_loop_list_, key;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,188);
    vector_1 = ISVREF(table,(SI_Long)1L);
    length_1 = ISVREF(table,(SI_Long)2L);
    result_1 = Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    chain = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    chain = ISVREF(vector_1,i);
    if (chain) {
	pair = Nil;
	ab_loop_list_ = chain;
	key = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	key = CAR(pair);
	result_1 = g2int_gensym_cons_1(key,result_1);
	goto next_loop_1;
      end_loop_1:;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* RECLAIM-EQ-HASH-TABLE */
Object g2int_reclaim_eq_hash_table(table)
    Object table;
{
    Object vector_1, length_1, key_reclaimer_qm, value_reclaimer_qm, chain;
    Object pair, ab_loop_list_, key, value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,189);
    vector_1 = ISVREF(table,(SI_Long)1L);
    length_1 = ISVREF(table,(SI_Long)2L);
    key_reclaimer_qm = ISVREF(table,(SI_Long)4L);
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    chain = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    chain = ISVREF(vector_1,i);
    if (chain) {
	if (key_reclaimer_qm && value_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    key = Nil;
	    value = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    key = CAR(pair);
	    value = CDR(pair);
	    FUNCALL_1(key_reclaimer_qm,key);
	    FUNCALL_1(value_reclaimer_qm,value);
	    g2int_reclaim_gensym_cons_1(pair);
	    goto next_loop_1;
	  end_loop_1:;
	    g2int_reclaim_gensym_list_1(chain);
	}
	else if (value_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    value = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    value = CDR(pair);
	    FUNCALL_1(value_reclaimer_qm,value);
	    g2int_reclaim_gensym_cons_1(pair);
	    goto next_loop_2;
	  end_loop_2:;
	    g2int_reclaim_gensym_list_1(chain);
	}
	else if (key_reclaimer_qm) {
	    pair = Nil;
	    ab_loop_list_ = chain;
	    key = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    key = CAR(pair);
	    FUNCALL_1(key_reclaimer_qm,key);
	    g2int_reclaim_gensym_cons_1(pair);
	    goto next_loop_3;
	  end_loop_3:;
	    g2int_reclaim_gensym_list_1(chain);
	}
	else {
	    pair = Nil;
	    ab_loop_list_ = chain;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    pair = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    g2int_reclaim_gensym_cons_1(pair);
	    goto next_loop_4;
	  end_loop_4:;
	    g2int_reclaim_gensym_list_1(chain);
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    g2int_reclaim_managed_simple_vector(vector_1);
    return g2int_reclaim_eq_hash_table_internal_1(table);
}

/* EQ-GETHASH */
Object g2int_eq_gethash(table,key_object,default_value_qm)
    Object table, key_object, default_value_qm;
{
    Object thing, hash_code, length_1, vector_1, chain, temp_1, pair;
    SI_Long temp;

    x_note_fn_call(28,190);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    chain = ISVREF(vector_1,temp);
  next_loop:
    if ( !TRUEP(chain) || ATOM(chain)) {
	temp_1 = default_value_qm;
	goto end;
    }
    pair = M_CAR(chain);
    if (CONSP(pair)) {
	if (EQ(M_CAR(pair),key_object)) {
	    temp_1 = M_CDR(pair);
	    goto end;
	}
    }
    chain = M_CDR(chain);
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end:;
    return VALUES_1(temp_1);
}

/* EQ-PUTHASH */
Object g2int_eq_puthash(table,key_object,value_object)
    Object table, key_object, value_object;
{
    Object thing, hash_code, length_1, vector_1, chain, tail;
    Object value_reclaimer_qm, svref_new_value, pair, old_value_object;
    SI_Long temp, index_1;

    x_note_fn_call(28,191);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    index_1 = temp;
    chain = ISVREF(vector_1,index_1);
    tail = chain;
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(tail)) {
	svref_new_value = 
		g2int_gensym_cons_1(g2int_gensym_cons_1(key_object,
		value_object),chain);
	ISVREF(vector_1,index_1) = svref_new_value;
	goto end;
    }
    pair = M_CAR(tail);
    if (EQ(M_CAR(pair),key_object)) {
	old_value_object = M_CDR(pair);
	M_CDR(pair) = value_object;
	if (value_reclaimer_qm)
	    FUNCALL_1(value_reclaimer_qm,old_value_object);
	goto end;
    }
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
  end:;
    return VALUES_1(value_object);
}

/* EQ-REMHASH */
Object g2int_eq_remhash(table,key_object)
    Object table, key_object;
{
    Object thing, hash_code, length_1, vector_1, chain, tail, prev_tail;
    Object key_reclaimer_qm, value_reclaimer_qm, temp_1, pair;
    Object old_value_object, temp_2;
    SI_Long temp, index_1;

    x_note_fn_call(28,192);
    thing = key_object;
    hash_code = FIXNUMP(thing) ? (IFIX(thing) < (SI_Long)0L ? 
	    FIXNUM_NEGATE(thing) : thing) : FIX(SXHASH_SYMBOL_1(thing) & 
	    IFIX(Most_positive_fixnum));
    length_1 = ISVREF(table,(SI_Long)2L);
    vector_1 = ISVREF(table,(SI_Long)1L);
    temp = IFIX(hash_code) % IFIX(length_1);
    index_1 = temp;
    chain = ISVREF(vector_1,index_1);
    tail = chain;
    prev_tail = Nil;
    key_reclaimer_qm = ISVREF(table,(SI_Long)4L);
    value_reclaimer_qm = ISVREF(table,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(tail)) {
	temp_1 = Nil;
	goto end;
    }
    pair = M_CAR(tail);
    if (EQ(M_CAR(pair),key_object)) {
	old_value_object = M_CDR(pair);
	if (prev_tail) {
	    temp_2 = M_CDR(tail);
	    M_CDR(prev_tail) = temp_2;
	}
	else {
	    temp_2 = M_CDR(tail);
	    ISVREF(vector_1,index_1) = temp_2;
	}
	if (key_reclaimer_qm)
	    FUNCALL_1(key_reclaimer_qm,key_object);
	if (value_reclaimer_qm)
	    FUNCALL_1(value_reclaimer_qm,old_value_object);
	g2int_reclaim_gensym_cons_1(tail);
	g2int_reclaim_gensym_cons_1(pair);
	temp_1 = Nil;
	goto end;
    }
    prev_tail = tail;
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end:;
    return VALUES_1(temp_1);
}

static Object string_constant_10;  /* "Version ~d." */

static Object string_constant_11;  /* "~d" */

static Object Qg2int_alpha_or_beta;  /* alpha-or-beta */

static Object Qg2int_patch_level;  /* patch-level */

static Object string_constant_12;  /* " ~a~c" */

static Object string_constant_13;  /* " ~a" */

static Object Qg2int_brief_description;  /* brief-description */

/* TWRITE-SYSTEM-VERSION */
Object g2int_twrite_system_version varargs_1(int, n)
{
    Object system_version;
    Object suppress_brief_description_of_system_version_qm, tenths, hundredths;
    Object temp, alpha_or_beta_qm, patch_level_qm, brief_description_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(28,193);
    INIT_ARGS_nonrelocating();
    system_version = REQUIRED_ARG_nonrelocating();
    suppress_brief_description_of_system_version_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    g2int_tformat(2,string_constant_10,FIRST(system_version));
    result = l_round(SECOND(system_version),FIX((SI_Long)10L));
    MVS_2(result,tenths,hundredths);
    g2int_tformat(2,string_constant_11,tenths);
    temp = FIX((SI_Long)0L);
    if (NUM_NE(hundredths,temp))
	g2int_tformat(2,string_constant_11,hundredths);
    alpha_or_beta_qm = getf(CDDR(system_version),Qg2int_alpha_or_beta,_);
    patch_level_qm = getf(CDDR(system_version),Qg2int_patch_level,_);
    if (alpha_or_beta_qm) {
	if (patch_level_qm)
	    g2int_tformat(3,string_constant_12,alpha_or_beta_qm,
		    CODE_CHAR(add(patch_level_qm,FIX((SI_Long)96L))));
	else
	    g2int_tformat(2,string_constant_13,alpha_or_beta_qm);
    }
    if ( !TRUEP(suppress_brief_description_of_system_version_qm)) {
	brief_description_qm = getf(CDDR(system_version),
		Qg2int_brief_description,_);
	if (brief_description_qm)
	    return g2int_tformat(2,string_constant_13,brief_description_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_14;  /* "Gensym.~a." */

static Object string_constant_15;  /* "Enterprise" */

static Object string_constant_16;  /* "Standard" */

static Object string_constant_17;  /* "~d." */

static Object array_constant_7;    /* # */

static Object string_constant_18;  /* ", ~a" */

/* TWRITE-SYSTEM-VERSION-IN-G2-TITLE */
Object g2int_twrite_system_version_in_g2_title varargs_1(int, n)
{
    Object system_version;
    Object suppress_brief_description_of_system_version_qm;
    Object brief_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(28,194);
    INIT_ARGS_nonrelocating();
    system_version = REQUIRED_ARG_nonrelocating();
    suppress_brief_description_of_system_version_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    g2int_tformat(2,string_constant_14,g2int_g2_enterprise_p() ? 
	    string_constant_15 : string_constant_16);
    g2int_tformat(2,string_constant_17,G2int_external_version);
    if (IFIX(G2int_revision_number_of_current_gensym_product_line) < 
	    (SI_Long)10L)
	g2int_twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)1L));
    g2int_tformat(2,string_constant_11,
	    G2int_revision_number_of_current_gensym_product_line);
    if ( !TRUEP(suppress_brief_description_of_system_version_qm)) {
	brief_description_qm = getf(CDDR(system_version),
		Qg2int_brief_description,_);
	if (brief_description_qm)
	    return g2int_tformat(2,string_constant_18,brief_description_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-LOCAL-IDENTIFICATION-INFO-TEXT-STRING */
Object g2int_write_local_identification_info_text_string()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(28,195);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_write_local_identification_info_text_string_1(T);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_starexpiration_date_for_display_in_titlestar = UNBOUND;

static Object string_constant_19;  /* "Host: ~a" */

static Object string_constant_20;  /* "; ~a: ~a~a" */

static Object string_constant_21;  /* "~%Expiration Day:~a~%" */

static Object string_constant_22;  /* "~%" */

/* WRITE-LOCAL-IDENTIFICATION-INFO-TEXT-STRING-1 */
Object g2int_write_local_identification_info_text_string_1(write_machine_id_p)
    Object write_machine_id_p;
{
    Object host_name, port_list, network_type, address, secure_p;
    Object ab_loop_list_, ab_loop_desetq_, temp, temp_1;
    Object result;

    x_note_fn_call(28,196);
    result = g2int_get_raw_network_info();
    MVS_2(result,host_name,port_list);
    g2int_tformat(2,string_constant_19,host_name);
    network_type = Nil;
    address = Nil;
    secure_p = Nil;
    ab_loop_list_ = port_list;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    network_type = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    address = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    secure_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = network_type;
    temp_1 = address;
    g2int_tformat(4,string_constant_20,temp,temp_1,
	    g2int_secure_icp_string(4,Ksecure_p,secure_p,Knetwork_type,
	    network_type));
    goto next_loop;
  end_loop:;
    g2int_reclaim_raw_network_info(host_name,port_list);
    if (G2int_starexpiration_date_for_display_in_titlestar)
	return g2int_tformat(2,string_constant_21,
		G2int_starexpiration_date_for_display_in_titlestar);
    else
	return g2int_tformat(1,string_constant_22);
}

static Object string_constant_23;  /* "(Unknown Host)" */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object string_constant_24;  /* "~a" */

/* GET-RAW-NETWORK-INFO */
Object g2int_get_raw_network_info()
{
    Object temp, temp_1, network_addresses, type_of_network, address, secure_p;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp_2;

    x_note_fn_call(28,197);
    temp = g2int_get_local_host_name();
    if (temp);
    else
	temp = string_constant_23;
    temp_1 = g2int_copy_text_string(temp);
    network_addresses = g2int_get_local_host_addresses();
    type_of_network = Nil;
    address = Nil;
    secure_p = Nil;
    ab_loop_list_ = network_addresses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_of_network = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    address = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    secure_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_2 = g2int_copy_text_string(g2int_equalw(type_of_network,
	    array_constant_8) ? array_constant_9 : array_constant_10);
    temp = g2int_tformat_text_string(2,string_constant_24,address);
    ab_loopvar__2 = g2int_gensym_cons_1(g2int_gensym_list_3(temp_2,temp,
	    secure_p),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    g2int_reclaim_network_addresses(network_addresses);
    temp = ab_loopvar_;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_2(temp_1,temp);
}

/* RECLAIM-RAW-NETWORK-INFO */
Object g2int_reclaim_raw_network_info(host_name,port_list)
    Object host_name, port_list;
{
    x_note_fn_call(28,198);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(host_name) != (SI_Long)0L)
	g2int_reclaim_wide_string(host_name);
    return g2int_reclaim_gensym_tree_with_text_strings(port_list);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-WITH-ZEROS */
Object g2int_allocate_managed_simple_vector_with_zeros(len)
    Object len;
{
    Object v;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(28,199);
    v = g2int_allocate_managed_simple_vector(len);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(sub1(len));
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    ISVREF(v,i) = FIX((SI_Long)0L);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(v);
}

/* READ-HEX-NUMBER-FROM-TEXT-STRING */
Object g2int_read_hex_number_from_text_string(str,si_init,ei_init)
    Object str, si_init, ei_init;
{
    Object number, result_1, temp, y, incf_arg;
    SI_Long si, ei, length_1, x, ab_loop_bind_, tmp, gensymed_symbol, i;
    SI_Long ab_loop_bind__1;

    x_note_fn_call(28,200);
    si = IFIX(si_init);
    ei = IFIX(ei_init);
    number = FIX((SI_Long)0L);
    ei = ei - (SI_Long)1L;
    si = si + (SI_Long)2L;
    if (UBYTE_16_ISAREF_1(str,(SI_Long)0L) == (SI_Long)48L && 
	    (UBYTE_16_ISAREF_1(str,(SI_Long)1L) == (SI_Long)120L || 
	    UBYTE_16_ISAREF_1(str,(SI_Long)1L) == (SI_Long)88L)) {
	result_1 = FIX((SI_Long)1L);
	length_1 = ei - si;
	x = (SI_Long)0L;
	ab_loop_bind_ = length_1;
      next_loop:
	if (x > ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(result_1))
	    goto end_loop;
	tmp = UBYTE_16_ISAREF_1(str,ei - x);
	gensymed_symbol = tmp;
	result_1 = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? FIX(gensymed_symbol - (SI_Long)48L) : Nil;
	if ( !TRUEP(result_1)) {
	    if (tmp == (SI_Long)97L || tmp == (SI_Long)65L)
		result_1 = FIX((SI_Long)10L);
	    else if (tmp == (SI_Long)98L || tmp == (SI_Long)66L)
		result_1 = FIX((SI_Long)11L);
	    else if (tmp == (SI_Long)99L || tmp == (SI_Long)67L)
		result_1 = FIX((SI_Long)12L);
	    else if (tmp == (SI_Long)100L || tmp == (SI_Long)68L)
		result_1 = FIX((SI_Long)13L);
	    else if (tmp == (SI_Long)101L || tmp == (SI_Long)69L)
		result_1 = FIX((SI_Long)14L);
	    else if (tmp == (SI_Long)102L || tmp == (SI_Long)70L)
		result_1 = FIX((SI_Long)15L);
	    else if ( !TRUEP(result_1))
		number = FIX((SI_Long)0L);
	}
	if (result_1) {
	    temp = result_1;
	    y = FIX((SI_Long)1L);
	    i = (SI_Long)1L;
	    ab_loop_bind__1 = x;
	  next_loop_1:
	    if (i > ab_loop_bind__1)
		goto end_loop_1;
	    y = ltimes(y,FIX((SI_Long)16L));
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    incf_arg = ltimes(temp,y);
	    number = add(number,incf_arg);
	}
	x = x + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(number);
}

void utilities3_INIT()
{
    Object temp, reclaim_structure_for_temporary_constant, integer;
    Object reclaim_structure_for_pending_activity;
    Object all_known_command_line_plist_elements_new_value;
    Object reclaim_structure_for_foreign_struct_info;
    Object reclaim_structure_for_eq_hash_table;
    SI_int64 long_1, zero;
    Object AB_package, Qg2int_eq_hash_table, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_eq_hash_table_count;
    Object Qg2int_chain_of_available_eq_hash_tables;
    Object Qg2int_type_description_of_type, string_constant_34;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_foreign_struct_info;
    Object Qg2int_foreign_struct_info_count;
    Object Qg2int_chain_of_available_foreign_struct_infos, string_constant_33;
    Object list_constant_41;
    Object Qg2int_get_command_line_plist_element_for_icp_log_intensity;
    Object Qg2int_command_line_process_icp_log_intensity, list_constant_40;
    Object Qg2int_get_command_line_plist_element_for_cert;
    Object Qg2int_command_line_process_cert, list_constant_39;
    Object Qg2int_get_command_line_plist_element_for_secure;
    Object Qg2int_command_line_process_secure, list_constant_38;
    Object Qg2int_use_jit, Qg2int_get_command_line_plist_element_for_use_jit;
    Object Qg2int_command_line_process_use_jit, list_constant_37;
    Object Qg2int_exit_on_abort;
    Object Qg2int_get_command_line_plist_element_for_exit_on_abort;
    Object Qg2int_command_line_process_exit_on_abort, list_constant_36;
    Object Qg2int_silent, Qg2int_get_command_line_plist_element_for_silent;
    Object Qg2int_command_line_process_silent, list_constant_35;
    Object Qg2int_verbose, Qg2int_get_command_line_plist_element_for_verbose;
    Object Qg2int_command_line_process_verbose, list_constant_34;
    Object Qg2int_netinfo, Qg2int_get_command_line_plist_element_for_netinfo;
    Object Qg2int_command_line_process_netinfo, list_constant_33, Qg2int_ui;
    Object Qg2int_get_command_line_plist_element_for_ui;
    Object Qg2int_command_line_process_ui, list_constant_32;
    Object Qg2int_known_ui_styles, Qg2int_classic, list_constant_31;
    Object Qg2int_background;
    Object Qg2int_get_command_line_plist_element_for_background;
    Object Qg2int_command_line_process_background, list_constant_30;
    Object Qg2int_xclip, Qg2int_get_command_line_plist_element_for_xclip;
    Object Qg2int_command_line_process_xclip, list_constant_29;
    Object Qg2int_debug_frame_reference_balance;
    Object Qg2int_get_command_line_plist_element_for_debug_frame_reference_balance;
    Object Qg2int_command_line_process_debug_frame_reference_balance;
    Object list_constant_28, Qg2int_copy_logbook_on_console;
    Object Qg2int_get_command_line_plist_element_for_copy_logbook_on_console;
    Object Qg2int_command_line_process_copy_logbook_on_console;
    Object list_constant_27, Qg2int_copy_messages_on_logbook;
    Object Qg2int_get_command_line_plist_element_for_copy_messages_on_logbook;
    Object Qg2int_command_line_process_copy_messages_on_logbook;
    Object list_constant_26, Qg2int_use_os_emulation;
    Object Qg2int_get_command_line_plist_element_for_use_os_emulation;
    Object Qg2int_command_line_process_use_os_emulation, list_constant_25;
    Object Qg2int_file_operation_timeout;
    Object Qg2int_get_command_line_plist_element_for_file_operation_timeout;
    Object Qg2int_command_line_process_file_operation_timeout;
    Object list_constant_24, Qg2int_private_colormap;
    Object Qg2int_get_command_line_plist_element_for_private_colormap;
    Object Qg2int_command_line_process_private_colormap, list_constant_23;
    Object Qg2int_no_backing_store;
    Object Qg2int_get_command_line_plist_element_for_no_backing_store;
    Object Qg2int_command_line_process_no_backing_store, list_constant_22;
    Object Qg2int_g2passwdexe;
    Object Qg2int_get_command_line_plist_element_for_g2passwdexe;
    Object Qg2int_command_line_process_g2passwdexe, list_constant_21;
    Object Qg2int_no_native_clipboard;
    Object Qg2int_get_command_line_plist_element_for_no_native_clipboard;
    Object Qg2int_command_line_process_no_native_clipboard, list_constant_20;
    Object Qg2int_native_fonts;
    Object Qg2int_get_command_line_plist_element_for_native_fonts;
    Object Qg2int_command_line_process_native_fonts, list_constant_19;
    Object Qg2int_no_native_fonts;
    Object Qg2int_get_command_line_plist_element_for_no_native_fonts;
    Object Qg2int_command_line_process_no_native_fonts, Qg2int_g2_5dotx;
    Object Qg2int_standard_large, list_constant_18, Qg2int_window_style;
    Object Qg2int_get_command_line_plist_element_for_window_style;
    Object Qg2int_command_line_process_window_style, list_constant_17;
    Object Qg2int_windowhandle;
    Object Qg2int_get_command_line_plist_element_for_windowhandle;
    Object Qg2int_command_line_process_windowhandle, list_constant_16;
    Object Qg2int_user_name;
    Object Qg2int_get_command_line_plist_element_for_user_name;
    Object Qg2int_command_line_process_user_name, list_constant_15;
    Object Qg2int_window, Qg2int_get_command_line_plist_element_for_window;
    Object Qg2int_command_line_process_window, list_constant_14;
    Object Qg2int_user_mode;
    Object Qg2int_get_command_line_plist_element_for_user_mode;
    Object Qg2int_command_line_process_user_mode, list_constant_13;
    Object Qg2int_discard_user_settings;
    Object Qg2int_get_command_line_plist_element_for_discard_user_settings;
    Object Qg2int_command_line_process_discard_user_settings, list_constant_12;
    Object Qg2int_init_string;
    Object Qg2int_get_command_line_plist_element_for_init_string;
    Object Qg2int_command_line_process_init_string, list_constant_11;
    Object Qg2int_cjk_language;
    Object Qg2int_get_command_line_plist_element_for_cjk_language;
    Object Qg2int_command_line_process_cjk_language, list_constant_10;
    Object Qg2int_language, Qg2int_get_command_line_plist_element_for_language;
    Object Qg2int_command_line_process_language, list_constant_9;
    Object Qg2int_password, Qg2int_get_command_line_plist_element_for_password;
    Object Qg2int_command_line_process_password, list_constant_8;
    Object Qg2int_utilities3, Qg2int_command_line_arguments;
    Object Qg2int_get_initial_command_line_arguments, Kfuncall;
    Object Qg2int_all_command_line_keyword_arguments, Qg2int_pending_activity;
    Object Qg2int_pending_activity_count;
    Object Qg2int_chain_of_available_pending_activitys, string_constant_32;
    Object list_constant_7, Qg2int_scratch_rectangle_region;
    Object Qg2int_make_region_from_rectangle, Qg2int_type_error_printer;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, list_constant_6, list_constant_5;
    Object Qg2int_random_seed_3, Qg2int_random_seed_2, Qg2int_random_seed_1;
    Object Qg2int_random_seed_0, Qg2int_large_shift, Qg2int_large_mask;
    Object Qg2int_maximum_length_of_g2_symbol_name;
    Object Qg2int_most_positive_fixnum_floor_2;
    Object Qg2int_most_negative_fixnum_ceiling_10;
    Object Qg2int_most_positive_fixnum_floor_10, Qg2int_falsity, Qg2int_truth;
    Object string_constant_27, Qg2int_memory_used_for_interned_gensym_strings;
    Object Qg2int_count_of_interned_gensym_strings, Qg2int_schedule;
    Object Qg2int_recycled_resumption_conses, Qg2int_temporary_constant_count;
    Object Qg2int_chain_of_available_temporary_constants, string_constant_26;
    Object list_constant_4, Qg2int_managed_bignum_pool;
    Object Qg2int_allocate_managed_array, Qg2int_mask_for_ieee_exponent;
    Object Qg2int_simple_long_array_pool_memory_usage, Qg2int_utilities0;
    Object Qg2int_created_simple_long_array_pool_arrays, list_constant_3;
    Object Qg2int_vector_of_simple_long_array_pools;
    Object Qg2int_maximum_managed_simple_long_array_size;
    Object Qg2int_maximum_managed_float_array_size;
    Object Qg2int_maximum_managed_float_array_buffer_size;
    Object Qg2int_managed_float_array;
    Object Qg2int_oversized_simple_float_array_pool_memory_usage;
    Object Qg2int_simple_float_array_pool_memory_usage;
    Object Qg2int_created_oversized_simple_float_array_pool_arrays;
    Object Qg2int_created_simple_float_array_pool_arrays;
    Object Qg2int_vector_of_oversized_simple_float_array_pools;
    Object Qg2int_vector_of_simple_float_array_pools;
    Object Qg2int_allocate_initial_vector_of_simple_float_array_pools;
    Object Qg2int_maximum_oversized_managed_simple_float_array_size;
    Object Qg2int_maximum_managed_simple_float_array_size, string_constant_25;
    Object Qg2int_no_arg;

    x_note_fn_call(28,201);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_no_arg = STATIC_SYMBOL("NO-ARG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_no_arg,G2int_no_arg);
    if (G2int_no_arg == UNBOUND)
	G2int_no_arg = LIST_1(Qg2int_no_arg);
    if (G2int_starwrite_console_pstar == UNBOUND)
	G2int_starwrite_console_pstar = Nil;
    Qg2int_iso_8859_1_gensym_string = 
	    STATIC_SYMBOL("ISO-8859-1-GENSYM-STRING",AB_package);
    string_constant_25 = STATIC_STRING("the ~(~A~) ");
    if (G2int_actual_arg == UNBOUND)
	G2int_actual_arg = string_constant_25;
    float_constant = STATIC_FLOAT(0.0);
    G2int_floating_zero = float_constant;
    Qg2int_maximum_managed_simple_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-FLOAT-ARRAY-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_simple_float_array_size,
	    FIX((SI_Long)1024L));
    Qg2int_maximum_oversized_managed_simple_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-OVERSIZED-MANAGED-SIMPLE-FLOAT-ARRAY-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_oversized_managed_simple_float_array_size,
	    FIX((SI_Long)1048576L));
    Qg2int_vector_of_simple_float_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_vector_of_simple_float_array_pools,
	    G2int_vector_of_simple_float_array_pools);
    Qg2int_utilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_allocate_initial_vector_of_simple_float_array_pools = 
	    STATIC_SYMBOL("ALLOCATE-INITIAL-VECTOR-OF-SIMPLE-FLOAT-ARRAY-POOLS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_allocate_initial_vector_of_simple_float_array_pools,
	    STATIC_FUNCTION(g2int_allocate_initial_vector_of_simple_float_array_pools,
	    NIL,FALSE,0,0));
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_allocate_initial_vector_of_simple_float_array_pools);
    g2int_record_system_variable(Qg2int_vector_of_simple_float_array_pools,
	    Qg2int_utilities0,list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qg2int_vector_of_oversized_simple_float_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_vector_of_oversized_simple_float_array_pools,
	    G2int_vector_of_oversized_simple_float_array_pools);
    g2int_record_system_variable(Qg2int_vector_of_oversized_simple_float_array_pools,
	    Qg2int_utilities0,list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qg2int_created_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_created_simple_float_array_pool_arrays,
	    G2int_created_simple_float_array_pool_arrays);
    g2int_record_system_variable(Qg2int_created_simple_float_array_pool_arrays,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_created_oversized_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_created_oversized_simple_float_array_pool_arrays,
	    G2int_created_oversized_simple_float_array_pool_arrays);
    g2int_record_system_variable(Qg2int_created_oversized_simple_float_array_pool_arrays,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_simple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_simple_float_array_pool_memory_usage,
	    G2int_simple_float_array_pool_memory_usage);
    g2int_record_system_variable(Qg2int_simple_float_array_pool_memory_usage,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_oversized_simple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("OVERSIZED-SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_oversized_simple_float_array_pool_memory_usage,
	    G2int_oversized_simple_float_array_pool_memory_usage);
    g2int_record_system_variable(Qg2int_oversized_simple_float_array_pool_memory_usage,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    G2int_replenished_simple_float_array_size_limit = FIX((SI_Long)10L);
    G2int_replenished_simple_float_arrays_to_make_at_a_time = 
	    FIX((SI_Long)10L);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_managed_simple_float_array = 
	    STATIC_SYMBOL("MANAGED-SIMPLE-FLOAT-ARRAY",AB_package);
    Qg2int_managed_float_array = STATIC_SYMBOL("MANAGED-FLOAT-ARRAY",
	    AB_package);
    if (G2int_managed_float_array_unique_marker == UNBOUND)
	G2int_managed_float_array_unique_marker = 
		CONS(Qg2int_managed_float_array,Nil);
    Qg2int_maximum_managed_float_array_buffer_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-FLOAT-ARRAY-BUFFER-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_float_array_buffer_size,
	    FIX((SI_Long)1024L));
    Qg2int_maximum_managed_float_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-FLOAT-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_float_array_size,
	    FIX((SI_Long)1046528L));
    if (G2int_bytes_per_double_float_simple_array_cached == UNBOUND)
	G2int_bytes_per_double_float_simple_array_cached = 
		g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
    list_constant = STATIC_LIST((SI_Long)2L,Qsigned_byte,FIX((SI_Long)64L));
    Qg2int_maximum_managed_simple_long_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-LONG-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_managed_simple_long_array_size,
	    FIX((SI_Long)1024L));
    Qg2int_vector_of_simple_long_array_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-LONG-ARRAY-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_vector_of_simple_long_array_pools,
	    G2int_vector_of_simple_long_array_pools);
    g2int_record_system_variable(Qg2int_vector_of_simple_long_array_pools,
	    Qg2int_utilities0,list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qg2int_created_simple_long_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-LONG-ARRAY-POOL-ARRAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_created_simple_long_array_pool_arrays,
	    G2int_created_simple_long_array_pool_arrays);
    g2int_record_system_variable(Qg2int_created_simple_long_array_pool_arrays,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_simple_long_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-LONG-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_simple_long_array_pool_memory_usage,
	    G2int_simple_long_array_pool_memory_usage);
    g2int_record_system_variable(Qg2int_simple_long_array_pool_memory_usage,
	    Qg2int_utilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qg2int_simple_long_array_pool_memory_usage,
	    STATIC_FUNCTION(g2int_simple_long_array_pool_memory_usage,NIL,
	    FALSE,0,0));
    G2int_replenished_simple_long_array_size_limit = FIX((SI_Long)10L);
    G2int_replenished_simple_long_arrays_to_make_at_a_time = FIX((SI_Long)10L);
    Qg2int_managed_simple_long_array = 
	    STATIC_SYMBOL("MANAGED-SIMPLE-LONG-ARRAY",AB_package);
    if (G2int_bytes_per_long_simple_array_cached == UNBOUND)
	G2int_bytes_per_long_simple_array_cached = 
		g2int_bytes_per_long_simple_array(FIX((SI_Long)1L));
    Qg2int_gensym_float = STATIC_SYMBOL("GENSYM-FLOAT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    if (G2int_partition_float_union == UNBOUND)
	G2int_partition_float_union = 
		g2int_make_partition_float_or_long_union();
    if (G2int_partition_long_union == UNBOUND)
	G2int_partition_long_union = 
		g2int_make_partition_float_or_long_union();
    Qg2int_mask_for_ieee_exponent = STATIC_SYMBOL("MASK-FOR-IEEE-EXPONENT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_mask_for_ieee_exponent,FIX((SI_Long)32752L));
    Qg2int_vms = STATIC_SYMBOL("VMS",AB_package);
    Qg2int_managed_bignum_pool = STATIC_SYMBOL("MANAGED-BIGNUM-POOL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_managed_bignum_pool,
	    G2int_managed_bignum_pool);
    Qg2int_utilities3 = STATIC_SYMBOL("UTILITIES3",AB_package);
    Qg2int_allocate_managed_array = STATIC_SYMBOL("ALLOCATE-MANAGED-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_allocate_managed_array,
	    STATIC_FUNCTION(g2int_allocate_managed_array,NIL,TRUE,1,3));
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_allocate_managed_array,FIX((SI_Long)10L));
    g2int_record_system_variable(Qg2int_managed_bignum_pool,
	    Qg2int_utilities3,list_constant_4,Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_temporary_constant = STATIC_SYMBOL("TEMPORARY-CONSTANT",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    Qg2int_temporary_constant,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_temporary_constant,
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_temporary_constant == UNBOUND)
	G2int_the_type_description_of_temporary_constant = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8l8302y1n8302y8m8k1l8m0000001l1n8n83*xy1m83by83ayknk0k0");
    temp = G2int_the_type_description_of_temporary_constant;
    G2int_the_type_description_of_temporary_constant = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_26));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_temporary_constant_g2_struct,
	    G2int_the_type_description_of_temporary_constant,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_temporary_constant,
	    G2int_the_type_description_of_temporary_constant,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_temporary_constants = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEMPORARY-CONSTANTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_temporary_constants,
	    G2int_chain_of_available_temporary_constants);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_temporary_constants,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_temporary_constant_count = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_temporary_constant_count,
	    G2int_temporary_constant_count);
    g2int_record_system_variable(Qg2int_temporary_constant_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_temporary_constant = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_temporary_constant,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_temporary_constant,
	    reclaim_structure_for_temporary_constant);
    Qg2int_recycled_resumption_conses = 
	    STATIC_SYMBOL("RECYCLED-RESUMPTION-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_recycled_resumption_conses,
	    G2int_recycled_resumption_conses);
    Qg2int_schedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    g2int_record_system_variable(Qg2int_recycled_resumption_conses,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_count_of_interned_gensym_strings = 
	    STATIC_SYMBOL("COUNT-OF-INTERNED-GENSYM-STRINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_interned_gensym_strings,
	    G2int_count_of_interned_gensym_strings);
    g2int_record_system_variable(Qg2int_count_of_interned_gensym_strings,
	    Qg2int_utilities3,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_memory_used_for_interned_gensym_strings = 
	    STATIC_SYMBOL("MEMORY-USED-FOR-INTERNED-GENSYM-STRINGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_memory_used_for_interned_gensym_strings,
	    G2int_memory_used_for_interned_gensym_strings);
    g2int_record_system_variable(Qg2int_memory_used_for_interned_gensym_strings,
	    Qg2int_utilities3,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    string_constant_27 = STATIC_STRING("NIL");
    if (G2int_nil_interned == UNBOUND)
	G2int_nil_interned = intern(string_constant_27,_);
    Qg2int_truth = STATIC_SYMBOL("TRUTH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_truth,FIX((SI_Long)1000L));
    Qg2int_falsity = STATIC_SYMBOL("FALSITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_falsity,FIX((SI_Long)-1000L));
    Qg2int_most_positive_fixnum_floor_10 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-FLOOR-10",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_positive_fixnum_floor_10,
	    G2int_most_positive_fixnum_floor_10);
    SET_SYMBOL_VALUE(Qg2int_most_positive_fixnum_floor_10,
	    g2int_chestnut_floorf_function(Most_positive_fixnum,
	    FIX((SI_Long)10L)));
    Qg2int_most_negative_fixnum_ceiling_10 = 
	    STATIC_SYMBOL("MOST-NEGATIVE-FIXNUM-CEILING-10",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_negative_fixnum_ceiling_10,
	    G2int_most_negative_fixnum_ceiling_10);
    SET_SYMBOL_VALUE(Qg2int_most_negative_fixnum_ceiling_10,
	    ceiling(Most_negative_fixnum,FIX((SI_Long)10L)));
    string_constant = STATIC_STRING("number is too large");
    string_constant_1 = STATIC_STRING("negative number is too large");
    integer = timesn(3,FIX((SI_Long)66024901L),FIX((SI_Long)77608531L),
	    FIX((SI_Long)180L));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    G2int_most_positive_int64_floor_10 = add(INT64_TO_INTEGER(long_1),
	    INT64_TO_INTEGER(zero));
    integer = ltimes(ltimes(FIX((SI_Long)66024901L),
	    FIX((SI_Long)77608531L)),FIX((SI_Long)-180L));
    long_1 = INTEGER_TO_INT64(integer);
    zero = (SI_int64)(SI_Long)0L;
    G2int_most_negative_int64_ceiling_10 = add(INT64_TO_INTEGER(long_1),
	    INT64_TO_INTEGER(zero));
    Qg2int_most_positive_fixnum_floor_2 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-FLOOR-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_most_positive_fixnum_floor_2,
	    G2int_most_positive_fixnum_floor_2);
    SET_SYMBOL_VALUE(Qg2int_most_positive_fixnum_floor_2,
	    g2int_chestnut_floorf_function(Most_positive_fixnum,
	    FIX((SI_Long)2L)));
    Qg2int_maximum_length_of_g2_symbol_name = 
	    STATIC_SYMBOL("MAXIMUM-LENGTH-OF-G2-SYMBOL-NAME",AB_package);
    SET_SYMBOL_VALUE(Qg2int_maximum_length_of_g2_symbol_name,
	    FIX((SI_Long)5000L));
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_large_mask = STATIC_SYMBOL("LARGE-MASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_large_mask,G2int_large_mask);
    SET_SYMBOL_VALUE(Qg2int_large_mask,FIXNUM_SUB1(FIX((SI_Long)8388608L)));
    Qg2int_large_shift = STATIC_SYMBOL("LARGE-SHIFT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_large_shift,FIX((SI_Long)23L));
    if (G2int_starrandom_state_arraystar == UNBOUND)
	G2int_starrandom_state_arraystar = Nil;
    if (G2int_starrandom_state_array_current_pointerstar == UNBOUND)
	G2int_starrandom_state_array_current_pointerstar = FIX((SI_Long)54L);
    if (G2int_starrandom_state_array_24_pointerstar == UNBOUND)
	G2int_starrandom_state_array_24_pointerstar = FIX((SI_Long)24L);
    Qg2int_random_seed_0 = STATIC_SYMBOL("RANDOM-SEED-0",AB_package);
    SET_SYMBOL_VALUE(Qg2int_random_seed_0,FIX((SI_Long)6460045L));
    Qg2int_random_seed_1 = STATIC_SYMBOL("RANDOM-SEED-1",AB_package);
    SET_SYMBOL_VALUE(Qg2int_random_seed_1,FIX((SI_Long)4757733L));
    Qg2int_random_seed_2 = STATIC_SYMBOL("RANDOM-SEED-2",AB_package);
    SET_SYMBOL_VALUE(Qg2int_random_seed_2,FIX((SI_Long)6397164L));
    Qg2int_random_seed_3 = STATIC_SYMBOL("RANDOM-SEED-3",AB_package);
    SET_SYMBOL_VALUE(Qg2int_random_seed_3,FIX((SI_Long)7884262L));
    if (G2int_random_variation == UNBOUND)
	G2int_random_variation = FIX((SI_Long)0L);
    if (G2int_random_variation_2 == UNBOUND)
	G2int_random_variation_2 = FIX((SI_Long)0L);
    if (G2int_user_random_seedqm == UNBOUND)
	G2int_user_random_seedqm = Nil;
    Qg2int_simple_type_specification = 
	    STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",AB_package);
    G2int_simple_type_specification_prop = Qg2int_simple_type_specification;
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qsymbolp);
    g2int_mutate_global_property(Qsymbol,list_constant_5,
	    Qg2int_simple_type_specification);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qconsp);
    g2int_mutate_global_property(Qcons,list_constant_6,
	    Qg2int_simple_type_specification);
    Qg2int_boolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qg2int_managed_number = STATIC_SYMBOL("MANAGED-NUMBER",AB_package);
    Qg2int_or = STATIC_SYMBOL("OR",AB_package);
    Qg2int_type_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    G2int_type_error_printer_prop = Qg2int_type_error_printer;
    string_constant_28 = STATIC_STRING("neither true nor false");
    g2int_mutate_global_property(Qg2int_boolean,string_constant_28,
	    Qg2int_type_error_printer);
    string_constant_29 = STATIC_STRING("not a symbol");
    g2int_mutate_global_property(Qsymbol,string_constant_29,
	    Qg2int_type_error_printer);
    string_constant_30 = STATIC_STRING("not a simple integer");
    g2int_mutate_global_property(Qfixnum,string_constant_30,
	    Qg2int_type_error_printer);
    string_constant_31 = STATIC_STRING("not a number");
    g2int_mutate_global_property(Qg2int_gensym_float,string_constant_31,
	    Qg2int_type_error_printer);
    g2int_mutate_global_property(Qg2int_managed_number,string_constant_31,
	    Qg2int_type_error_printer);
    g2int_mutate_global_property(Qg2int_temporary_constant,
	    string_constant_31,Qg2int_type_error_printer);
    Qg2int_simple_type_writer = STATIC_SYMBOL("SIMPLE-TYPE-WRITER",AB_package);
    G2int_simple_type_writer_prop = Qg2int_simple_type_writer;
    string_constant_2 = STATIC_STRING("~(~S~)");
    Qg2int_scratch_rectangle_region = 
	    STATIC_SYMBOL("SCRATCH-RECTANGLE-REGION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_scratch_rectangle_region,
	    G2int_scratch_rectangle_region);
    Qg2int_make_region_from_rectangle = 
	    STATIC_SYMBOL("MAKE-REGION-FROM-RECTANGLE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_region_from_rectangle,
	    STATIC_FUNCTION(g2int_make_region_from_rectangle,NIL,FALSE,4,4));
    list_constant_7 = STATIC_LIST((SI_Long)6L,Kfuncall,
	    Qg2int_make_region_from_rectangle,FIX((SI_Long)0L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)0L));
    g2int_record_system_variable(Qg2int_scratch_rectangle_region,
	    Qg2int_utilities3,list_constant_7,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_pending_activity_g2_struct = 
	    STATIC_SYMBOL("PENDING-ACTIVITY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_pending_activity = STATIC_SYMBOL("PENDING-ACTIVITY",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    Qg2int_pending_activity,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_pending_activity,
	    Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_pending_activity == UNBOUND)
	G2int_the_type_description_of_pending_activity = Nil;
    string_constant_32 = 
	    STATIC_STRING("43Dy8l83=Gy1n83=Gy8m8k1l8m0000001l1n8n83*ny1n83=Fy83=*y83cykqk0k0");
    temp = G2int_the_type_description_of_pending_activity;
    G2int_the_type_description_of_pending_activity = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_32));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_pending_activity_g2_struct,
	    G2int_the_type_description_of_pending_activity,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_pending_activity,
	    G2int_the_type_description_of_pending_activity,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_pending_activitys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PENDING-ACTIVITYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_pending_activitys,
	    G2int_chain_of_available_pending_activitys);
    g2int_record_system_variable(Qg2int_chain_of_available_pending_activitys,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_pending_activity_count = STATIC_SYMBOL("PENDING-ACTIVITY-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_pending_activity_count,
	    G2int_pending_activity_count);
    g2int_record_system_variable(Qg2int_pending_activity_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_pending_activity = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_pending_activity,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_pending_activity,reclaim_structure_for_pending_activity);
    Kfinished = STATIC_SYMBOL("FINISHED",Pkeyword);
    Kcanceled = STATIC_SYMBOL("CANCELED",Pkeyword);
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    if (G2int_cached_gensym_user_home_directory == UNBOUND)
	G2int_cached_gensym_user_home_directory = Nil;
    Qg2int_all_command_line_keyword_arguments = 
	    STATIC_SYMBOL("ALL-COMMAND-LINE-KEYWORD-ARGUMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_all_command_line_keyword_arguments,
	    G2int_all_command_line_keyword_arguments);
    g2int_record_system_variable(Qg2int_all_command_line_keyword_arguments,
	    Qg2int_utilities3,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_command_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    G2int_command_line_plist_element_getter_prop = 
	    Qg2int_command_line_plist_element_getter;
    Qg2int_command_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    G2int_command_line_argument_processor_prop = 
	    Qg2int_command_line_argument_processor;
    if (G2int_all_known_command_line_plist_elements == UNBOUND)
	G2int_all_known_command_line_plist_elements = Nil;
    Qg2int_command_line_arguments = STATIC_SYMBOL("COMMAND-LINE-ARGUMENTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_command_line_arguments,
	    G2int_command_line_arguments);
    Qg2int_get_initial_command_line_arguments = 
	    STATIC_SYMBOL("GET-INITIAL-COMMAND-LINE-ARGUMENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_initial_command_line_arguments,
	    STATIC_FUNCTION(g2int_get_initial_command_line_arguments,NIL,
	    FALSE,0,0));
    list_constant_8 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_get_initial_command_line_arguments);
    g2int_record_system_variable(Qg2int_command_line_arguments,
	    Qg2int_utilities3,list_constant_8,Qnil,Qnil,Qnil,Qnil);
    Qg2int_command_line_process_password = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-PASSWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_password,
	    STATIC_FUNCTION(g2int_command_line_process_password,NIL,FALSE,
	    1,1));
    Qg2int_password = STATIC_SYMBOL("PASSWORD",AB_package);
    g2int_mutate_global_property(Qg2int_password,
	    Qg2int_command_line_process_password,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_password = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PASSWORD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_password,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_password,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_password,
	    Qg2int_get_command_line_plist_element_for_password,
	    Qg2int_command_line_plist_element_getter);
    list_constant_9 = STATIC_CONS(Qg2int_password,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_9,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_language = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_language,
	    STATIC_FUNCTION(g2int_command_line_process_language,NIL,FALSE,
	    1,1));
    Qg2int_language = STATIC_SYMBOL("LANGUAGE",AB_package);
    g2int_mutate_global_property(Qg2int_language,
	    Qg2int_command_line_process_language,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_language = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LANGUAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_language,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_language,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_language,
	    Qg2int_get_command_line_plist_element_for_language,
	    Qg2int_command_line_plist_element_getter);
    list_constant_10 = STATIC_CONS(Qg2int_language,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_10,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_cjk_language = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-CJK-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_cjk_language,
	    STATIC_FUNCTION(g2int_command_line_process_cjk_language,NIL,
	    FALSE,1,1));
    Qg2int_cjk_language = STATIC_SYMBOL("CJK-LANGUAGE",AB_package);
    g2int_mutate_global_property(Qg2int_cjk_language,
	    Qg2int_command_line_process_cjk_language,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_cjk_language = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CJK-LANGUAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_cjk_language,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_cjk_language,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_cjk_language,
	    Qg2int_get_command_line_plist_element_for_cjk_language,
	    Qg2int_command_line_plist_element_getter);
    list_constant_11 = STATIC_CONS(Qg2int_cjk_language,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_11,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_init_string = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-INIT-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_init_string,
	    STATIC_FUNCTION(g2int_command_line_process_init_string,NIL,
	    FALSE,1,1));
    Qg2int_init_string = STATIC_SYMBOL("INIT-STRING",AB_package);
    g2int_mutate_global_property(Qg2int_init_string,
	    Qg2int_command_line_process_init_string,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_init_string = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-INIT-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_init_string,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_init_string,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_init_string,
	    Qg2int_get_command_line_plist_element_for_init_string,
	    Qg2int_command_line_plist_element_getter);
    list_constant_12 = STATIC_CONS(Qg2int_init_string,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_12,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_discard_user_settings = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DISCARD-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_discard_user_settings,
	    STATIC_FUNCTION(g2int_command_line_process_discard_user_settings,
	    NIL,FALSE,1,1));
    Qg2int_discard_user_settings = STATIC_SYMBOL("DISCARD-USER-SETTINGS",
	    AB_package);
    g2int_mutate_global_property(Qg2int_discard_user_settings,
	    Qg2int_command_line_process_discard_user_settings,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_discard_user_settings = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DISCARD-USER-SETTINGS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_discard_user_settings,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_discard_user_settings,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_discard_user_settings,
	    Qg2int_get_command_line_plist_element_for_discard_user_settings,
	    Qg2int_command_line_plist_element_getter);
    list_constant_13 = STATIC_CONS(Qg2int_discard_user_settings,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_13,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_user_mode = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_user_mode,
	    STATIC_FUNCTION(g2int_command_line_process_user_mode,NIL,FALSE,
	    1,1));
    Qg2int_user_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    g2int_mutate_global_property(Qg2int_user_mode,
	    Qg2int_command_line_process_user_mode,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_user_mode = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_user_mode,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_user_mode,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_user_mode,
	    Qg2int_get_command_line_plist_element_for_user_mode,
	    Qg2int_command_line_plist_element_getter);
    list_constant_14 = STATIC_CONS(Qg2int_user_mode,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_14,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_window = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_window,
	    STATIC_FUNCTION(g2int_command_line_process_window,NIL,FALSE,1,1));
    Qg2int_window = STATIC_SYMBOL("WINDOW",AB_package);
    g2int_mutate_global_property(Qg2int_window,
	    Qg2int_command_line_process_window,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_window = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_window,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_window,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_window,
	    Qg2int_get_command_line_plist_element_for_window,
	    Qg2int_command_line_plist_element_getter);
    list_constant_15 = STATIC_CONS(Qg2int_window,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_15,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_user_name = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USER-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_user_name,
	    STATIC_FUNCTION(g2int_command_line_process_user_name,NIL,FALSE,
	    1,1));
    Qg2int_user_name = STATIC_SYMBOL("USER-NAME",AB_package);
    g2int_mutate_global_property(Qg2int_user_name,
	    Qg2int_command_line_process_user_name,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_user_name = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USER-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_user_name,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_user_name,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_user_name,
	    Qg2int_get_command_line_plist_element_for_user_name,
	    Qg2int_command_line_plist_element_getter);
    list_constant_16 = STATIC_CONS(Qg2int_user_name,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_16,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_windowhandle = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOWHANDLE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_windowhandle,
	    STATIC_FUNCTION(g2int_command_line_process_windowhandle,NIL,
	    FALSE,1,1));
    Qg2int_windowhandle = STATIC_SYMBOL("WINDOWHANDLE",AB_package);
    g2int_mutate_global_property(Qg2int_windowhandle,
	    Qg2int_command_line_process_windowhandle,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_windowhandle = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOWHANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_windowhandle,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_windowhandle,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_windowhandle,
	    Qg2int_get_command_line_plist_element_for_windowhandle,
	    Qg2int_command_line_plist_element_getter);
    list_constant_17 = STATIC_CONS(Qg2int_windowhandle,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_17,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    string_constant_3 = STATIC_STRING("windowhandle");
    string_constant_4 = STATIC_STRING("");
    Qg2int_command_line_process_window_style = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WINDOW-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_window_style,
	    STATIC_FUNCTION(g2int_command_line_process_window_style,NIL,
	    FALSE,1,1));
    Qg2int_window_style = STATIC_SYMBOL("WINDOW-STYLE",AB_package);
    g2int_mutate_global_property(Qg2int_window_style,
	    Qg2int_command_line_process_window_style,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_window_style = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_window_style,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_window_style,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_window_style,
	    Qg2int_get_command_line_plist_element_for_window_style,
	    Qg2int_command_line_plist_element_getter);
    list_constant_18 = STATIC_CONS(Qg2int_window_style,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_18,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_standard_large = STATIC_SYMBOL("STANDARD-LARGE",AB_package);
    Qg2int_standard = STATIC_SYMBOL("STANDARD",AB_package);
    Qg2int_g2_5dotx = STATIC_SYMBOL("G2-5.X",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qg2int_standard_large,
	    Qg2int_standard,Qg2int_g2_5dotx);
    string_constant_5 = 
	    STATIC_STRING("The ~a argument ~s is not recognized. It should be one of ~L,|");
    Qg2int_command_line_process_no_native_fonts = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-NATIVE-FONTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_no_native_fonts,
	    STATIC_FUNCTION(g2int_command_line_process_no_native_fonts,NIL,
	    FALSE,1,1));
    Qg2int_no_native_fonts = STATIC_SYMBOL("NO-NATIVE-FONTS",AB_package);
    g2int_mutate_global_property(Qg2int_no_native_fonts,
	    Qg2int_command_line_process_no_native_fonts,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_no_native_fonts = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-FONTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_no_native_fonts,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_no_native_fonts,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_no_native_fonts,
	    Qg2int_get_command_line_plist_element_for_no_native_fonts,
	    Qg2int_command_line_plist_element_getter);
    list_constant_19 = STATIC_CONS(Qg2int_no_native_fonts,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_19,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_native_fonts = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NATIVE-FONTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_native_fonts,
	    STATIC_FUNCTION(g2int_command_line_process_native_fonts,NIL,
	    FALSE,1,1));
    Qg2int_native_fonts = STATIC_SYMBOL("NATIVE-FONTS",AB_package);
    g2int_mutate_global_property(Qg2int_native_fonts,
	    Qg2int_command_line_process_native_fonts,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_native_fonts = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NATIVE-FONTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_native_fonts,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_native_fonts,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_native_fonts,
	    Qg2int_get_command_line_plist_element_for_native_fonts,
	    Qg2int_command_line_plist_element_getter);
    list_constant_20 = STATIC_CONS(Qg2int_native_fonts,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_20,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_no_native_clipboard = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-NATIVE-CLIPBOARD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_no_native_clipboard,
	    STATIC_FUNCTION(g2int_command_line_process_no_native_clipboard,
	    NIL,FALSE,1,1));
    Qg2int_no_native_clipboard = STATIC_SYMBOL("NO-NATIVE-CLIPBOARD",
	    AB_package);
    g2int_mutate_global_property(Qg2int_no_native_clipboard,
	    Qg2int_command_line_process_no_native_clipboard,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_no_native_clipboard = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-NATIVE-CLIPBOARD",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_no_native_clipboard,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_no_native_clipboard,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_no_native_clipboard,
	    Qg2int_get_command_line_plist_element_for_no_native_clipboard,
	    Qg2int_command_line_plist_element_getter);
    list_constant_21 = STATIC_CONS(Qg2int_no_native_clipboard,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_21,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_g2passwdexe = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-G2PASSWDEXE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_g2passwdexe,
	    STATIC_FUNCTION(g2int_command_line_process_g2passwdexe,NIL,
	    FALSE,1,1));
    Qg2int_g2passwdexe = STATIC_SYMBOL("G2PASSWDEXE",AB_package);
    g2int_mutate_global_property(Qg2int_g2passwdexe,
	    Qg2int_command_line_process_g2passwdexe,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_g2passwdexe = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-G2PASSWDEXE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_g2passwdexe,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_g2passwdexe,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_g2passwdexe,
	    Qg2int_get_command_line_plist_element_for_g2passwdexe,
	    Qg2int_command_line_plist_element_getter);
    list_constant_22 = STATIC_CONS(Qg2int_g2passwdexe,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_22,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_no_backing_store = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NO-BACKING-STORE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_no_backing_store,
	    STATIC_FUNCTION(g2int_command_line_process_no_backing_store,
	    NIL,FALSE,1,1));
    Qg2int_no_backing_store = STATIC_SYMBOL("NO-BACKING-STORE",AB_package);
    g2int_mutate_global_property(Qg2int_no_backing_store,
	    Qg2int_command_line_process_no_backing_store,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_no_backing_store = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NO-BACKING-STORE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_no_backing_store,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_no_backing_store,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_no_backing_store,
	    Qg2int_get_command_line_plist_element_for_no_backing_store,
	    Qg2int_command_line_plist_element_getter);
    list_constant_23 = STATIC_CONS(Qg2int_no_backing_store,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_23,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_private_colormap = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-PRIVATE-COLORMAP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_private_colormap,
	    STATIC_FUNCTION(g2int_command_line_process_private_colormap,
	    NIL,FALSE,1,1));
    Qg2int_private_colormap = STATIC_SYMBOL("PRIVATE-COLORMAP",AB_package);
    g2int_mutate_global_property(Qg2int_private_colormap,
	    Qg2int_command_line_process_private_colormap,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_private_colormap = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-PRIVATE-COLORMAP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_private_colormap,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_private_colormap,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_private_colormap,
	    Qg2int_get_command_line_plist_element_for_private_colormap,
	    Qg2int_command_line_plist_element_getter);
    list_constant_24 = STATIC_CONS(Qg2int_private_colormap,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_24,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_file_operation_timeout = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-FILE-OPERATION-TIMEOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_file_operation_timeout,
	    STATIC_FUNCTION(g2int_command_line_process_file_operation_timeout,
	    NIL,FALSE,1,1));
    Qg2int_file_operation_timeout = STATIC_SYMBOL("FILE-OPERATION-TIMEOUT",
	    AB_package);
    g2int_mutate_global_property(Qg2int_file_operation_timeout,
	    Qg2int_command_line_process_file_operation_timeout,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_file_operation_timeout = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-FILE-OPERATION-TIMEOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_file_operation_timeout,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_file_operation_timeout,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_file_operation_timeout,
	    Qg2int_get_command_line_plist_element_for_file_operation_timeout,
	    Qg2int_command_line_plist_element_getter);
    list_constant_25 = STATIC_CONS(Qg2int_file_operation_timeout,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_25,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_use_os_emulation = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USE-OS-EMULATION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_use_os_emulation,
	    STATIC_FUNCTION(g2int_command_line_process_use_os_emulation,
	    NIL,FALSE,1,1));
    Qg2int_use_os_emulation = STATIC_SYMBOL("USE-OS-EMULATION",AB_package);
    g2int_mutate_global_property(Qg2int_use_os_emulation,
	    Qg2int_command_line_process_use_os_emulation,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_use_os_emulation = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-OS-EMULATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_use_os_emulation,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_use_os_emulation,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_use_os_emulation,
	    Qg2int_get_command_line_plist_element_for_use_os_emulation,
	    Qg2int_command_line_plist_element_getter);
    list_constant_26 = STATIC_CONS(Qg2int_use_os_emulation,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_26,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_copy_messages_on_logbook = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-COPY-MESSAGES-ON-LOGBOOK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_copy_messages_on_logbook,
	    STATIC_FUNCTION(g2int_command_line_process_copy_messages_on_logbook,
	    NIL,FALSE,1,1));
    Qg2int_copy_messages_on_logbook = 
	    STATIC_SYMBOL("COPY-MESSAGES-ON-LOGBOOK",AB_package);
    g2int_mutate_global_property(Qg2int_copy_messages_on_logbook,
	    Qg2int_command_line_process_copy_messages_on_logbook,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_copy_messages_on_logbook = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-MESSAGES-ON-LOGBOOK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_copy_messages_on_logbook,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_copy_messages_on_logbook,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_copy_messages_on_logbook,
	    Qg2int_get_command_line_plist_element_for_copy_messages_on_logbook,
	    Qg2int_command_line_plist_element_getter);
    list_constant_27 = STATIC_CONS(Qg2int_copy_messages_on_logbook,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_27,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_copy_logbook_on_console = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-COPY-LOGBOOK-ON-CONSOLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_copy_logbook_on_console,
	    STATIC_FUNCTION(g2int_command_line_process_copy_logbook_on_console,
	    NIL,FALSE,1,1));
    Qg2int_copy_logbook_on_console = 
	    STATIC_SYMBOL("COPY-LOGBOOK-ON-CONSOLE",AB_package);
    g2int_mutate_global_property(Qg2int_copy_logbook_on_console,
	    Qg2int_command_line_process_copy_logbook_on_console,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_copy_logbook_on_console = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-COPY-LOGBOOK-ON-CONSOLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_copy_logbook_on_console,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_copy_logbook_on_console,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_copy_logbook_on_console,
	    Qg2int_get_command_line_plist_element_for_copy_logbook_on_console,
	    Qg2int_command_line_plist_element_getter);
    list_constant_28 = STATIC_CONS(Qg2int_copy_logbook_on_console,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_28,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_debug_frame_reference_balance = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DEBUG-FRAME-REFERENCE-BALANCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_debug_frame_reference_balance,
	    STATIC_FUNCTION(g2int_command_line_process_debug_frame_reference_balance,
	    NIL,FALSE,1,1));
    Qg2int_debug_frame_reference_balance = 
	    STATIC_SYMBOL("DEBUG-FRAME-REFERENCE-BALANCE",AB_package);
    g2int_mutate_global_property(Qg2int_debug_frame_reference_balance,
	    Qg2int_command_line_process_debug_frame_reference_balance,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_debug_frame_reference_balance 
	    = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEBUG-FRAME-REFERENCE-BALANCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_debug_frame_reference_balance,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_debug_frame_reference_balance,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_debug_frame_reference_balance,
	    Qg2int_get_command_line_plist_element_for_debug_frame_reference_balance,
	    Qg2int_command_line_plist_element_getter);
    list_constant_29 = STATIC_CONS(Qg2int_debug_frame_reference_balance,
	    FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_29,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_xclip = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-XCLIP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_xclip,
	    STATIC_FUNCTION(g2int_command_line_process_xclip,NIL,FALSE,1,1));
    Qg2int_xclip = STATIC_SYMBOL("XCLIP",AB_package);
    g2int_mutate_global_property(Qg2int_xclip,
	    Qg2int_command_line_process_xclip,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_xclip = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-XCLIP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_xclip,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_xclip,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_xclip,
	    Qg2int_get_command_line_plist_element_for_xclip,
	    Qg2int_command_line_plist_element_getter);
    list_constant_30 = STATIC_CONS(Qg2int_xclip,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_30,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_background = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-BACKGROUND",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_background,
	    STATIC_FUNCTION(g2int_command_line_process_background,NIL,
	    FALSE,1,1));
    Qg2int_background = STATIC_SYMBOL("BACKGROUND",AB_package);
    g2int_mutate_global_property(Qg2int_background,
	    Qg2int_command_line_process_background,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_background = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-BACKGROUND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_background,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_background,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_background,
	    Qg2int_get_command_line_plist_element_for_background,
	    Qg2int_command_line_plist_element_getter);
    list_constant_31 = STATIC_CONS(Qg2int_background,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_31,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_known_ui_styles = STATIC_SYMBOL("KNOWN-UI-STYLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_known_ui_styles,G2int_known_ui_styles);
    Qg2int_classic = STATIC_SYMBOL("CLASSIC",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qg2int_classic,Qg2int_standard);
    SET_SYMBOL_VALUE(Qg2int_known_ui_styles,list_constant_32);
    Qg2int_command_line_process_ui = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-UI",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_ui,
	    STATIC_FUNCTION(g2int_command_line_process_ui,NIL,FALSE,1,1));
    Qg2int_ui = STATIC_SYMBOL("UI",AB_package);
    g2int_mutate_global_property(Qg2int_ui,Qg2int_command_line_process_ui,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_ui = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-UI",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_ui,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_ui,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_ui,
	    Qg2int_get_command_line_plist_element_for_ui,
	    Qg2int_command_line_plist_element_getter);
    list_constant_33 = STATIC_CONS(Qg2int_ui,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_33,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_netinfo = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NETINFO",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_netinfo,
	    STATIC_FUNCTION(g2int_command_line_process_netinfo,NIL,FALSE,1,1));
    Qg2int_netinfo = STATIC_SYMBOL("NETINFO",AB_package);
    g2int_mutate_global_property(Qg2int_netinfo,
	    Qg2int_command_line_process_netinfo,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_netinfo = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETINFO",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_netinfo,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_netinfo,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_netinfo,
	    Qg2int_get_command_line_plist_element_for_netinfo,
	    Qg2int_command_line_plist_element_getter);
    list_constant_34 = STATIC_CONS(Qg2int_netinfo,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_34,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_verbose = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-VERBOSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_verbose,
	    STATIC_FUNCTION(g2int_command_line_process_verbose,NIL,FALSE,1,1));
    Qg2int_verbose = STATIC_SYMBOL("VERBOSE",AB_package);
    g2int_mutate_global_property(Qg2int_verbose,
	    Qg2int_command_line_process_verbose,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_verbose = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-VERBOSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_verbose,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_verbose,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_verbose,
	    Qg2int_get_command_line_plist_element_for_verbose,
	    Qg2int_command_line_plist_element_getter);
    list_constant_35 = STATIC_CONS(Qg2int_verbose,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_35,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_silent = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-SILENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_silent,
	    STATIC_FUNCTION(g2int_command_line_process_silent,NIL,FALSE,1,1));
    Qg2int_silent = STATIC_SYMBOL("SILENT",AB_package);
    g2int_mutate_global_property(Qg2int_silent,
	    Qg2int_command_line_process_silent,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_silent = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SILENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_silent,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_silent,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_silent,
	    Qg2int_get_command_line_plist_element_for_silent,
	    Qg2int_command_line_plist_element_getter);
    list_constant_36 = STATIC_CONS(Qg2int_silent,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_36,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_command_line_process_exit_on_abort = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-EXIT-ON-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_exit_on_abort,
	    STATIC_FUNCTION(g2int_command_line_process_exit_on_abort,NIL,
	    FALSE,1,1));
    Qg2int_exit_on_abort = STATIC_SYMBOL("EXIT-ON-ABORT",AB_package);
    g2int_mutate_global_property(Qg2int_exit_on_abort,
	    Qg2int_command_line_process_exit_on_abort,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_exit_on_abort = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-EXIT-ON-ABORT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_exit_on_abort,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_exit_on_abort,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_exit_on_abort,
	    Qg2int_get_command_line_plist_element_for_exit_on_abort,
	    Qg2int_command_line_plist_element_getter);
    list_constant_37 = STATIC_CONS(Qg2int_exit_on_abort,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_37,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qg2int_command_line_process_use_jit = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-USE-JIT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_use_jit,
	    STATIC_FUNCTION(g2int_command_line_process_use_jit,NIL,FALSE,1,1));
    Qg2int_use_jit = STATIC_SYMBOL("USE-JIT",AB_package);
    g2int_mutate_global_property(Qg2int_use_jit,
	    Qg2int_command_line_process_use_jit,
	    Qg2int_command_line_argument_processor);
    Qg2int_get_command_line_plist_element_for_use_jit = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-USE-JIT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_use_jit,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_use_jit,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_use_jit,
	    Qg2int_get_command_line_plist_element_for_use_jit,
	    Qg2int_command_line_plist_element_getter);
    list_constant_38 = STATIC_CONS(Qg2int_use_jit,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_38,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    if (G2int_use_jit_p == UNBOUND)
	G2int_use_jit_p = Nil;
    G2int_secure_icp_initialized_p = Nil;
    G2int_secure_icp_default_p = Nil;
    G2int_cache_server_cert_name = Nil;
    Qg2int_command_line_process_secure = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-SECURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_secure,
	    STATIC_FUNCTION(g2int_command_line_process_secure,NIL,FALSE,1,1));
    Qg2int_secure = STATIC_SYMBOL("SECURE",AB_package);
    g2int_mutate_global_property(Qg2int_secure,
	    Qg2int_command_line_process_secure,
	    Qg2int_command_line_argument_processor);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qg2int_get_command_line_plist_element_for_secure = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SECURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_secure,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_secure,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_secure,
	    Qg2int_get_command_line_plist_element_for_secure,
	    Qg2int_command_line_plist_element_getter);
    list_constant_39 = STATIC_CONS(Qg2int_secure,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_39,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qg2int_command_line_process_cert = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-CERT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_cert,
	    STATIC_FUNCTION(g2int_command_line_process_cert,NIL,FALSE,1,1));
    Qg2int_cert = STATIC_SYMBOL("CERT",AB_package);
    g2int_mutate_global_property(Qg2int_cert,
	    Qg2int_command_line_process_cert,
	    Qg2int_command_line_argument_processor);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_get_command_line_plist_element_for_cert = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-CERT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_cert,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_cert,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_cert,
	    Qg2int_get_command_line_plist_element_for_cert,
	    Qg2int_command_line_plist_element_getter);
    list_constant_40 = STATIC_CONS(Qg2int_cert,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_40,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    string_constant_6 = STATIC_STRING("cert");
    string_constant_7 = STATIC_STRING("G2_CERT");
    Knetwork_type = STATIC_SYMBOL("NETWORK-TYPE",Pkeyword);
    Kuse_default = STATIC_SYMBOL("USE-DEFAULT",Pkeyword);
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    array_constant_5 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING("/SSL");
    string_constant_9 = 
	    STATIC_STRING("WARNING: SSL encryption is not available in this executable.");
    Qg2int_command_line_process_icp_log_intensity = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-ICP-LOG-INTENSITY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_command_line_process_icp_log_intensity,
	    STATIC_FUNCTION(g2int_command_line_process_icp_log_intensity,
	    NIL,FALSE,1,1));
    Qg2int_icp_log_intensity = STATIC_SYMBOL("ICP-LOG-INTENSITY",AB_package);
    g2int_mutate_global_property(Qg2int_icp_log_intensity,
	    Qg2int_command_line_process_icp_log_intensity,
	    Qg2int_command_line_argument_processor);
    array_constant_6 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    Qg2int_get_command_line_plist_element_for_icp_log_intensity = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-ICP-LOG-INTENSITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_command_line_plist_element_for_icp_log_intensity,
	    STATIC_FUNCTION(g2int_get_command_line_plist_element_for_icp_log_intensity,
	    NIL,FALSE,0,0));
    g2int_mutate_global_property(Qg2int_icp_log_intensity,
	    Qg2int_get_command_line_plist_element_for_icp_log_intensity,
	    Qg2int_command_line_plist_element_getter);
    list_constant_41 = STATIC_CONS(Qg2int_icp_log_intensity,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_41,G2int_all_known_command_line_plist_elements);
    G2int_all_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qg2int_foreign_struct_info = STATIC_SYMBOL("FOREIGN-STRUCT-INFO",
	    AB_package);
    G2int_foreign_struct_info_prop = Qg2int_foreign_struct_info;
    Qg2_defstruct_structure_name_foreign_struct_info_g2_struct = 
	    STATIC_SYMBOL("FOREIGN-STRUCT-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    Qg2int_foreign_struct_info,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_foreign_struct_info,
	    Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_foreign_struct_info == UNBOUND)
	G2int_the_type_description_of_foreign_struct_info = Nil;
    string_constant_33 = 
	    STATIC_STRING("43Dy8l83oy1n83oy8m8k1l8m0000000krk0k0");
    temp = G2int_the_type_description_of_foreign_struct_info;
    G2int_the_type_description_of_foreign_struct_info = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_33));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_foreign_struct_info_g2_struct,
	    G2int_the_type_description_of_foreign_struct_info,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_foreign_struct_info,
	    G2int_the_type_description_of_foreign_struct_info,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_foreign_struct_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FOREIGN-STRUCT-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_foreign_struct_infos,
	    G2int_chain_of_available_foreign_struct_infos);
    g2int_record_system_variable(Qg2int_chain_of_available_foreign_struct_infos,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_foreign_struct_info_count = 
	    STATIC_SYMBOL("FOREIGN-STRUCT-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_foreign_struct_info_count,
	    G2int_foreign_struct_info_count);
    g2int_record_system_variable(Qg2int_foreign_struct_info_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_foreign_struct_info = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_foreign_struct_info,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_foreign_struct_info,
	    reclaim_structure_for_foreign_struct_info);
    if (G2int_next_eq_hash_value == UNBOUND)
	G2int_next_eq_hash_value = FIX((SI_Long)0L);
    Qg2_defstruct_structure_name_eq_hash_table_g2_struct = 
	    STATIC_SYMBOL("EQ-HASH-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_eq_hash_table = STATIC_SYMBOL("EQ-HASH-TABLE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    Qg2int_eq_hash_table,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_eq_hash_table,
	    Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_eq_hash_table == UNBOUND)
	G2int_the_type_description_of_eq_hash_table = Nil;
    string_constant_34 = 
	    STATIC_STRING("43Dy8l83fy1n83fy8m8k1l8m0000001m1m8n83*Ry1m8p83=Tykqk0k0");
    temp = G2int_the_type_description_of_eq_hash_table;
    G2int_the_type_description_of_eq_hash_table = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_34));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_eq_hash_table_g2_struct,
	    G2int_the_type_description_of_eq_hash_table,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_eq_hash_table,
	    G2int_the_type_description_of_eq_hash_table,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_eq_hash_tables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EQ-HASH-TABLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_eq_hash_tables,
	    G2int_chain_of_available_eq_hash_tables);
    g2int_record_system_variable(Qg2int_chain_of_available_eq_hash_tables,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_eq_hash_table_count = STATIC_SYMBOL("EQ-HASH-TABLE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_eq_hash_table_count,
	    G2int_eq_hash_table_count);
    g2int_record_system_variable(Qg2int_eq_hash_table_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_eq_hash_table = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_eq_hash_table,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_eq_hash_table,reclaim_structure_for_eq_hash_table);
    string_constant_10 = STATIC_STRING("Version ~d.");
    string_constant_11 = STATIC_STRING("~d");
    Qg2int_alpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    Qg2int_patch_level = STATIC_SYMBOL("PATCH-LEVEL",AB_package);
    string_constant_12 = STATIC_STRING(" ~a~c");
    string_constant_13 = STATIC_STRING(" ~a");
    Qg2int_brief_description = STATIC_SYMBOL("BRIEF-DESCRIPTION",AB_package);
    string_constant_14 = STATIC_STRING("Gensym.~a.");
    string_constant_15 = STATIC_STRING("Enterprise");
    string_constant_16 = STATIC_STRING("Standard");
    string_constant_17 = STATIC_STRING("~d.");
    array_constant_7 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    string_constant_18 = STATIC_STRING(", ~a");
    G2int_starexpiration_date_for_display_in_titlestar = Nil;
    string_constant_19 = STATIC_STRING("Host: ~a");
    string_constant_20 = STATIC_STRING("; ~a: ~a~a");
    string_constant_21 = STATIC_STRING("~%Expiration Day:~a~%");
    string_constant_22 = STATIC_STRING("~%");
    string_constant_23 = STATIC_STRING("(Unknown Host)");
    array_constant_8 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    string_constant_24 = STATIC_STRING("~a");
}
