/* osrrr.c
 * Input file:  os-error.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "osrrr.h"


DEFINE_VARIABLE_WITH_SYMBOL(Bombout_clean_up_functions, Qbombout_clean_up_functions);

/* DEF-BOMBOUT-CLEAN-UP-FUNCTION */
Object def_bombout_clean_up_function(function_name)
    Object function_name;
{
    Object push_arg, bombout_clean_up_functions_new_value;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(36,0);
    if ( !TRUEP(memq_function(function_name,Bombout_clean_up_functions))) {
	if (PUSH_AREA(Dynamic_area,0)) {
	    push_arg = function_name;
	    bombout_clean_up_functions_new_value = CONS(push_arg,
		    Bombout_clean_up_functions);
	    Bombout_clean_up_functions = bombout_clean_up_functions_new_value;
	    result = VALUES_1(Bombout_clean_up_functions);
	}
	POP_AREA(0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Signal_code_registry, Qsignal_code_registry);

DEFINE_VARIABLE_WITH_SYMBOL(Sigfpe, Qsigfpe);

static Object string_constant;     /* "unknown signal" */

/* GET-SIGNAL-DESCRIPTION-STRING */
Object get_signal_description_string(code_number)
    Object code_number;
{
    Object entry_qm;

    x_note_fn_call(36,1);
    entry_qm = assoc_eql(code_number,Signal_code_registry);
    if (entry_qm)
	return VALUES_1(THIRD(entry_qm));
    else
	return VALUES_1(string_constant);
}

/* GET-G2-SIGNAL-HANDLER */
Object get_g2_signal_handler(code_number)
    Object code_number;
{
    Object entry_qm;

    x_note_fn_call(36,2);
    entry_qm = assoc_eql(code_number,Signal_code_registry);
    if (entry_qm)
	return fifth(entry_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inside_avoid_arithmetic_errors_p, Qinside_avoid_arithmetic_errors_p);

DEFINE_VARIABLE_WITH_SYMBOL(Arithmetic_errors_are_stack_errors_p, Qarithmetic_errors_are_stack_errors_p);

static Object string_constant_1;   /* "pmsize" */

static Object string_constant_2;   /* "G2PMSIZE" */

/* INITIALIZE-POST-MORTEM-RING-BUFFER-LENGTH */
Object initialize_post_mortem_ring_buffer_length()
{
    Object temp;

    x_note_fn_call(36,3);
    temp = get_command_line_keyword_argument_as_integer(1,string_constant_1);
    if (temp);
    else
	temp = read_number_for_gensym_environment_variable(string_constant_2);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)50L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_post_mortem_ring_buffer_length, Qcurrent_post_mortem_ring_buffer_length);

/* INITIALIZE-POST-MORTEM-RING-BUFFER */
Object initialize_post_mortem_ring_buffer()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object new_post_mortem_ring_buffer, cdr_arg;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(36,4);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Current_post_mortem_ring_buffer_length);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = LIST_1(Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    new_post_mortem_ring_buffer = ab_loopvar_;
    goto end_1;
    new_post_mortem_ring_buffer = Qnil;
  end_1:;
    cdr_arg = last(new_post_mortem_ring_buffer,_);
    M_CDR(cdr_arg) = new_post_mortem_ring_buffer;
    return VALUES_1(new_post_mortem_ring_buffer);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_post_mortem_ring_buffer, Qcurrent_post_mortem_ring_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Log_post_mortem_ring_buffer_to_file_p, Qlog_post_mortem_ring_buffer_to_file_p);

DEFINE_VARIABLE_WITH_SYMBOL(Post_mortem_ring_buffer_logfile_namestring, Qpost_mortem_ring_buffer_logfile_namestring);

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* INITIALIZE-POST-MORTEM-RING-BUFFER-LOGFILE-NAMESTRING */
Object initialize_post_mortem_ring_buffer_logfile_namestring()
{
    Object thing, provided_logfile_name_qm;

    x_note_fn_call(36,5);
    thing = get_command_line_keyword_argument(1,array_constant);
    provided_logfile_name_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
	    (SI_Long)0L ? copy_text_string(thing) : thing;
    if (provided_logfile_name_qm);
    else
	provided_logfile_name_qm = 
		get_gensym_environment_variable(array_constant_1);
    if (provided_logfile_name_qm) {
	Log_post_mortem_ring_buffer_to_file_p = T;
	return VALUES_1(provided_logfile_name_qm);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_mortem_ring_buffer_logfile_stream, Qpost_mortem_ring_buffer_logfile_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Post_mortem_ring_buffer_logfile_line_count, Qpost_mortem_ring_buffer_logfile_line_count);

DEFINE_VARIABLE_WITH_SYMBOL(Depth_of_post_mortem_checkpoint_reporting, Qdepth_of_post_mortem_checkpoint_reporting);

/* INITIALIZE-POST-MORTEM-INTERNAL-BUFFER */
Object initialize_post_mortem_internal_buffer()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(36,6);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Depth_of_post_mortem_checkpoint_reporting);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = LIST_1(Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Post_mortem_internal_buffer, Qpost_mortem_internal_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Post_mortem_report_buffer, Qpost_mortem_report_buffer);

static Object string_constant_3;   /* "<- ..." */

static Object string_constant_4;   /* "<-" */

/* INITIALIZE-POST-MORTEM-REPORT-BUFFER */
Object initialize_post_mortem_report_buffer()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long final_index, index_1, ab_loop_bind_;

    x_note_fn_call(36,7);
    final_index = IFIX(FIXNUM_SUB1(Depth_of_post_mortem_checkpoint_reporting));
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = final_index;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = LIST_1(Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if (index_1 == final_index) {
	ab_loopvar__2 = LIST_1(string_constant_3);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else {
	ab_loopvar__2 = LIST_1(string_constant_4);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object string_constant_5;   /* "This G2 image is operating after an internal error occurred.  ~
				    *      It is not recommended that you continue using this image.  ~
				    *      A KB saved from this image should be used ~
				    *      for reference purposes only.  ~
				    *      Please shut down this image and start a fresh G2 image."
				    */

/* WARN-USER-OF-PREVIOUSLY-ABORTED-G2 */
Object warn_user_of_previously_aborted_g2()
{
    x_note_fn_call(36,8);
    return notify_user(1,string_constant_5);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_backtrace_conses, Qavailable_backtrace_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_backtrace_conses_tail, Qavailable_backtrace_conses_tail);

Object Available_backtrace_conses_vector = UNBOUND;

Object Available_backtrace_conses_tail_vector = UNBOUND;

Object Backtrace_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Backtrace_cons_counter, Qbacktrace_cons_counter);

/* OUTSTANDING-BACKTRACE-CONSES */
Object outstanding_backtrace_conses()
{
    Object temp;

    x_note_fn_call(36,9);
    temp = FIXNUM_MINUS(Backtrace_cons_counter,
	    length(Available_backtrace_conses));
    return VALUES_1(temp);
}

/* BACKTRACE-CONS-MEMORY-USAGE */
Object backtrace_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(36,10);
    temp = FIXNUM_TIMES(Backtrace_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-BACKTRACE-CONS-POOL */
Object replenish_backtrace_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(36,11);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qbacktrace_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_backtrace_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Backtrace_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qbacktrace;          /* backtrace */

/* BACKTRACE-CONS-1 */
Object backtrace_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(36,12);
    new_cons = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_backtrace_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_backtrace_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-BACKTRACE-LIST-POOL */
Object replenish_backtrace_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(36,13);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_backtrace_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qbacktrace_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-BACKTRACE-LIST-1 */
Object make_backtrace_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(36,14);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_backtrace_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_backtrace_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_backtrace_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* BACKTRACE-LIST-2 */
Object backtrace_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(36,15);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_backtrace_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbacktrace);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_backtrace_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* BACKTRACE-LIST-3 */
Object backtrace_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(36,16);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_backtrace_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbacktrace);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_backtrace_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* BACKTRACE-LIST-4 */
Object backtrace_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(36,17);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_backtrace_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbacktrace);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_backtrace_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* BACKTRACE-LIST-TRACE-HOOK */
Object backtrace_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(36,18);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-BACKTRACE-CONSES-1 */
Object copy_tree_using_backtrace_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(36,19);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_backtrace_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_backtrace_cons_pool();
	temp_1 = copy_tree_using_backtrace_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_backtrace_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_backtrace_cons_pool();
	temp_1 = 
		copy_tree_using_backtrace_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-BACKTRACE-CONSES-1 */
Object copy_list_using_backtrace_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(36,20);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_backtrace_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_backtrace_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_backtrace_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_backtrace_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_backtrace_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_backtrace_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbacktrace);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-BACKTRACE-CONS-1 */
Object reclaim_backtrace_cons_1(backtrace_cons)
    Object backtrace_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(36,21);
    inline_note_reclaim_cons(backtrace_cons,Qbacktrace);
    if (ISVREF(Available_backtrace_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_backtrace_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = backtrace_cons;
	temp = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = backtrace_cons;
    }
    else {
	temp = Available_backtrace_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = backtrace_cons;
	temp = Available_backtrace_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = backtrace_cons;
    }
    M_CDR(backtrace_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-BACKTRACE-LIST-1 */
Object reclaim_backtrace_list_1(backtrace_list)
    Object backtrace_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(36,22);
    if (backtrace_list) {
	last_1 = backtrace_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qbacktrace);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qbacktrace);
	if (ISVREF(Available_backtrace_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_backtrace_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = backtrace_list;
	    temp = Available_backtrace_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_backtrace_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = backtrace_list;
	    temp = Available_backtrace_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-BACKTRACE-LIST*-1 */
Object reclaim_backtrace_list_star_1(backtrace_list)
    Object backtrace_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(36,23);
    if (CONSP(backtrace_list)) {
	temp = last(backtrace_list,_);
	M_CDR(temp) = Nil;
	if (backtrace_list) {
	    last_1 = backtrace_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qbacktrace);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qbacktrace);
	    if (ISVREF(Available_backtrace_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_backtrace_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = backtrace_list;
		temp = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_backtrace_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = backtrace_list;
		temp = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-BACKTRACE-TREE-1 */
Object reclaim_backtrace_tree_1(tree)
    Object tree;
{
    Object e, e2, backtrace_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(36,24);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_backtrace_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		backtrace_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(backtrace_cons,Qbacktrace);
		if (EQ(backtrace_cons,e))
		    goto end_1;
		else if ( !TRUEP(backtrace_cons))
		    goto end_1;
		else
		    backtrace_cons = CDR(backtrace_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_backtrace_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_backtrace_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_backtrace_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-BACKTRACE-ELEMENT-1 */
Object delete_backtrace_element_1(element,backtrace_list)
    Object element, backtrace_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(36,25);
    if (backtrace_list) {
	if (EQ(element,M_CAR(backtrace_list))) {
	    temp = CDR(backtrace_list);
	    inline_note_reclaim_cons(backtrace_list,Qbacktrace);
	    if (ISVREF(Available_backtrace_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_backtrace_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = backtrace_list;
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = backtrace_list;
	    }
	    else {
		temp_1 = Available_backtrace_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = backtrace_list;
		temp_1 = Available_backtrace_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = backtrace_list;
	    }
	    M_CDR(backtrace_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = backtrace_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qbacktrace);
		if (ISVREF(Available_backtrace_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_backtrace_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_backtrace_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_backtrace_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_backtrace_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = backtrace_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-BACKTRACE-CONS-1 */
Object delete_backtrace_cons_1(backtrace_cons,backtrace_list)
    Object backtrace_cons, backtrace_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(36,26);
    if (EQ(backtrace_cons,backtrace_list))
	temp = CDR(backtrace_list);
    else {
	l_trailer_qm = Nil;
	l = backtrace_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,backtrace_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = backtrace_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_backtrace_cons_1(backtrace_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);

DEFINE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Input_string_for_backtrace_text_buffer_for_internal_error, Qinput_string_for_backtrace_text_buffer_for_internal_error);

DEFINE_VARIABLE_WITH_SYMBOL(Backtrace_text_buffer_for_internal_error, Qbacktrace_text_buffer_for_internal_error);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_for_internal_error_on_console, Qbuffer_for_internal_error_on_console);

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_6;   /* "Backtrace:" */

static Object string_constant_7;   /* "~%  ~A" */

static Object string_constant_8;   /* "~%  " */

static Object string_constant_9;   /* "~%" */

/* UPDATE-BACKTRACE-TEXT-BUFFER-FOR-INTERNAL-ERROR */
Object update_backtrace_text_buffer_for_internal_error()
{
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object original_input_string, ch, temp, temp_1, schar_new_value;
    Object old_top_of_stack, temp_2, twrite_function_qm, number_of_args;
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long length_1, len, i, ab_loop_bind_, simple_or_wide_character, thing;
    SI_Long bv16_length, aref_arg_2, aref_new_value, arg, arg_1, arg_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(36,27);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      current_wide_string = 
	      Input_string_for_backtrace_text_buffer_for_internal_error;
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
	      original_input_string = 
		      Input_string_for_backtrace_text_buffer_for_internal_error;
	      len = 
		      inline_print_backtrace_into_string(ISTRING(Buffer_for_internal_error_on_console),
		      (SI_Long)0L);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = len;
	      ch = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      ch = CHR(ICHAR(Buffer_for_internal_error_on_console,i));
	      simple_or_wide_character = CHAR_EQ(CHR('\n'),ch) ? 
		      (SI_Long)8232L : IFIX(CHAR_CODE(ch));
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  temp_1 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
		  SET_SCHAR(temp,temp_1,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      tformat(1,string_constant_6);
	    next_loop_1:
	      if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
		  goto end_loop_1;
	      old_top_of_stack = Index_of_top_of_backtrace_stack;
	      if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
		  temp_2 = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(Index_of_top_of_backtrace_stack));
		  temp = FIXNUM_SUB1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
	      }
	      tformat(2,string_constant_7,temp_2);
	      if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
		  twrite_function_qm = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(Index_of_top_of_backtrace_stack));
		  temp = FIXNUM_SUB1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
		  twrite_function_qm = temp_2;
	      }
	      if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
		  number_of_args = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(Index_of_top_of_backtrace_stack));
		  temp = FIXNUM_SUB1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
		  number_of_args = temp_2;
	      }
	      if (twrite_function_qm) {
		  tformat(1,string_constant_8);
		  FUNCALL_0(twrite_function_qm);
	      }
	      Index_of_top_of_backtrace_stack = 
		      FIXNUM_MINUS(old_top_of_stack,
		      FIXNUM_ADD(number_of_args,
		      Size_of_basic_backtrace_information));
	      goto next_loop_1;
	    end_loop_1:
	      tformat(1,string_constant_9);
	      if ( !EQ(Current_wide_string,original_input_string))
		  Input_string_for_backtrace_text_buffer_for_internal_error 
			  = Current_wide_string;
	      temp = Backtrace_text_buffer_for_internal_error;
	      temp_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_1) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(temp_1),(SI_Long)0L);
	      if (EQ(Current_wide_string,
		      Backtrace_text_buffer_for_internal_error)) {
		  if ((SI_Long)0L == 
			  IFIX(Fill_pointer_for_current_wide_string))
		      temp_3 = TRUEP(T);
		  else {
		      temp_3 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < 
			      IFIX(Fill_pointer_for_current_wide_string) : 
			      TRUEP(Qnil);
		      if (temp_3);
		      else {
			  arg = (SI_Long)0L;
			  arg_1 = (SI_Long)0L;
			  arg_2 = (SI_Long)0L + 
				  (IFIX(Fill_pointer_for_current_wide_string) 
				  - (SI_Long)0L);
			  temp_3 = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
		      }
		      if (temp_3) {
			  copy_byte_vector_16_portion_carefully(Current_wide_string,
				  FIX((SI_Long)0L),
				  Backtrace_text_buffer_for_internal_error,
				  FIX((SI_Long)0L),
				  FIX(IFIX(Fill_pointer_for_current_wide_string) 
				  - (SI_Long)0L));
			  temp_3 = TRUEP(T);
		      }
		      else
			  temp_3 = TRUEP(Qnil);
		  }
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3);
	      else {
		  gensymed_symbol = Current_wide_string;
		  gensymed_symbol_1 = (SI_Long)0L;
		  gensymed_symbol_2 = Backtrace_text_buffer_for_internal_error;
		  gensymed_symbol_3 = (SI_Long)0L;
		  gensymed_symbol_4 = 
			  IFIX(Fill_pointer_for_current_wide_string) - 
			  (SI_Long)0L;
		  INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			  gensymed_symbol_1,
			  UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			  gensymed_symbol_3,gensymed_symbol_4);
	      }
	      result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Error_within_error_p, Qerror_within_error_p);

DEFINE_VARIABLE_WITH_SYMBOL(Input_gensym_string_for_buffer_for_internal_error_on_console, Qinput_gensym_string_for_buffer_for_internal_error_on_console);

DEFINE_VARIABLE_WITH_SYMBOL(Input_string_for_buffer_for_internal_error_on_logbook, Qinput_string_for_buffer_for_internal_error_on_logbook);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_for_internal_error_on_logbook, Qbuffer_for_internal_error_on_logbook);

DEFINE_VARIABLE_WITH_SYMBOL(Idling_wait_state_string, Qidling_wait_state_string);

/* TWRITE-ASCII-FROM-GENSYM-STRING */
Object twrite_ascii_from_gensym_string(gensym_string)
    Object gensym_string;
{
    Object escape_character_qm, character_or_character_code, temp_1;
    Object gensymed_symbol, thing, temp_3, schar_arg_2, schar_new_value;
    Object kanji_code, octet_1_qm, code, quotient, remainder_1;
    Object simple_or_wide_character;
    SI_Long length_of_string, i, ascii_code, temp_2, octet_2, octet_3, thing_2;
    SI_Long simple_or_wide_character_1;
    char string_is_simple_qm, gensym_string_is_simple_qm;
    char temp, character_1;
    char gensymed_symbol_1;
    char thing_1;
    Object result;

    x_note_fn_call(36,28);
    escape_character_qm = Nil;
    string_is_simple_qm =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    length_of_string = string_is_simple_qm ? 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string)) : 
	    IFIX(length(gensym_string));
    i = (SI_Long)0L;
    character_or_character_code = Nil;
  next_loop:
    if ( !(i < length_of_string))
	goto end_loop;
    gensym_string_is_simple_qm = string_is_simple_qm;
    temp = gensym_string_is_simple_qm ? ISCHAR(gensym_string,i) : 
	    ICHAR(gensym_string,i);
    i = i + (SI_Long)1L;
    character_1 = temp;
    temp_1 = CHAR_CODE(CHAR_TO_CHARACTER(character_1));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
	    FIX((SI_Long)127L)))) {
	escape_character_qm = Nil;
	character_or_character_code = CHAR_TO_CHARACTER(character_1);
    }
    else
	switch (INTEGER_TO_CHAR(temp_1)) {
	  case 64:
	  case 126:
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
	    temp_1 = gensym_string_is_simple_qm ? CHR(ISCHAR(gensym_string,
		    i)) : CHR(ICHAR(gensym_string,i));
	    i = i + (SI_Long)1L;
	    character_or_character_code = temp_1;
	    break;
	  case 92:
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
	    gensymed_symbol = gensym_string;
	    gensymed_symbol_1 = gensym_string_is_simple_qm;
	    temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
		    ICHAR(gensymed_symbol,i);
	    i = i + (SI_Long)1L;
	    ascii_code = IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
	    if (ascii_code < (SI_Long)40L) {
		temp_2 = ascii_code << (SI_Long)13L;
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		temp_2 = temp_2 + (SI_Long)95L * 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp)));
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		character_or_character_code = FIX(temp_2 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp))) + 
			(SI_Long)-265976L);
	    }
	    else {
		temp_2 = (SI_Long)95L * ascii_code;
		temp = gensymed_symbol_1 ? ISCHAR(gensymed_symbol,i) : 
			ICHAR(gensymed_symbol,i);
		i = i + (SI_Long)1L;
		character_or_character_code = FIX(temp_2 + 
			IFIX(CHAR_INT(CHAR_TO_CHARACTER(temp))) + 
			(SI_Long)4360L);
	    }
	    break;
	  default:
	    escape_character_qm = Nil;
	    character_or_character_code = CHAR_TO_CHARACTER(character_1);
	    break;
	}
    if ( !TRUEP(escape_character_qm)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = character_or_character_code;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_3 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = character_or_character_code;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_3;
	}
    }
    else if (CHAR_EQ(escape_character_qm,CHR('~'))) {
	temp_1 = CHAR_CODE(character_or_character_code);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = '~';
		twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = '~';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 126:
	      case 64:
	      case 92:
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = character_or_character_code;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = character_or_character_code;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	      default:
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing_1 = '~';
		    twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing_1 = '~';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = character_or_character_code;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = character_or_character_code;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	    }
    }
    else if (CHAR_EQ(escape_character_qm,CHR('@'))) {
	temp_1 = CHAR_CODE(character_or_character_code);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing_1 = '@';
		twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing_1 = '@';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_or_character_code;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = character_or_character_code;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 76:
	      case 80:
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing_1 = '\n';
		    twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing_1 = '\n';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	      default:
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing_1 = '@';
		    twrite_wide_character(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing_1 = '@';
		    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing_1)) ? 
			    CHAR_CODE(CHR(thing_1)) : CHR(thing_1));
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		if (EQ(Current_twriting_output_type,Qwide_string)) {
		    thing = character_or_character_code;
		    twrite_wide_character(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		}
		else {
		    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			    Total_length_of_current_gensym_string))
			extend_current_gensym_string(0);
		    temp_3 = Current_gensym_string;
		    schar_arg_2 = Fill_pointer_for_current_gensym_string;
		    thing = character_or_character_code;
		    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			    CHAR_CODE(thing) : thing);
		    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		    temp_3 = 
			    FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		    Fill_pointer_for_current_gensym_string = temp_3;
		}
		break;
	    }
    }
    else if (CHAR_EQ(escape_character_qm,CHR('\\'))) {
	kanji_code = character_or_character_code;
	octet_1_qm = Nil;
	octet_2 = (SI_Long)0L;
	octet_3 = (SI_Long)0L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_2 = (SI_Long)92L;
	    twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_3 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_2 = (SI_Long)92L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_3;
	}
	code = kanji_code;
	result = chestnut_floorf_function(FIX(IFIX(code) & (SI_Long)8191L),
		FIX((SI_Long)95L));
	MVS_2(result,quotient,remainder_1);
	octet_2 = IFIX(quotient) + (SI_Long)40L;
	octet_3 = IFIX(remainder_1) + (SI_Long)32L;
	octet_1_qm =  !(IFIX(code) >>  -  - (SI_Long)13L == (SI_Long)1L) ? 
		FIX((IFIX(code) >>  -  - (SI_Long)13L) + (SI_Long)32L) : Nil;
	if (octet_1_qm) {
	    simple_or_wide_character = octet_1_qm;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = simple_or_wide_character;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_3 = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = simple_or_wide_character;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
		temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_3;
	    }
	}
	simple_or_wide_character_1 = octet_2;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_2 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_3 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_2 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_3;
	}
	simple_or_wide_character_1 = octet_3;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_2 = simple_or_wide_character_1;
	    twrite_wide_character(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_3 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_2 = simple_or_wide_character_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_2)) ? 
		    CHAR_CODE(FIX(thing_2)) : FIX(thing_2));
	    SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
	    temp_3 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_3;
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qgensym_string;      /* gensym-string */

static Object string_constant_10;  /* "~%------------------------------------" */

static Object string_constant_11;  /* "~%AN INTERNAL ERROR OCCURRED!~%" */

static Object Qsystem_alias;       /* system-alias */

static Object string_constant_12;  /* "~a " */

static Object Qsystem_version;     /* system-version */

static Object string_constant_13;  /* " (~a)~%" */

static Object string_constant_14;  /* "~%Raw internal error data follows:" */

static Object Qtformat;            /* tformat */

static Object string_constant_15;  /* "~%[~d ~a ~d" */

static Object list_constant;       /* # */

static Object string_constant_16;  /* "  ~d:~a~d:~a~d]" */

static Object string_constant_17;  /* "0" */

static Object string_constant_18;  /* "" */

/* NOTIFY-CONSOLE-OF-INTERNAL-ERROR */
Object notify_console_of_internal_error(raw_format_string,list_of_format_args)
    Object raw_format_string, list_of_format_args;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object original_input_string, gensymed_symbol, temp, second_1, minute;
    Object hour, date, month, year, temp_1, fill_pointer_new_value;
    Object length_of_buffer;
    Declare_special(4);
    Object result;

    x_note_fn_call(36,29);
    current_gensym_string = 
	    Input_gensym_string_for_buffer_for_internal_error_on_console;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    original_input_string = 
		    Input_gensym_string_for_buffer_for_internal_error_on_console;
	    tformat(1,string_constant_10);
	    tformat(1,string_constant_11);
	    gensymed_symbol = Current_system_name;
	    temp = get(gensymed_symbol,Qsystem_alias,_);
	    if (temp);
	    else
		temp = gensymed_symbol;
	    tformat(2,string_constant_12,temp);
	    twrite_system_version(1,get(Current_system_name,
		    Qsystem_version,_));
	    tformat(2,string_constant_13,Build_identification_string);
	    write_local_identification_info_text_string_1(Nil);
	    tformat(1,string_constant_14);
	    tformat(1,string_constant_9);
	    temp = SYMBOL_FUNCTION(Qtformat);
	    APPLY_2(temp,raw_format_string,list_of_format_args);
	    tformat(1,string_constant_9);
	    result = get_decoded_real_time();
	    MVS_6(result,second_1,minute,hour,date,month,year);
	    tformat(4,string_constant_15,date,nth(FIXNUM_SUB1(month),
		    list_constant),year);
	    tformat(6,string_constant_16,hour,IFIX(minute) < (SI_Long)10L ?
		     string_constant_17 : string_constant_18,minute,
		    IFIX(second_1) < (SI_Long)10L ? string_constant_17 : 
		    string_constant_18,second_1);
	    tformat(1,string_constant_10);
	    tformat(1,string_constant_9);
	    if ( !EQ(Current_gensym_string,original_input_string))
		Input_gensym_string_for_buffer_for_internal_error_on_console 
			= Current_gensym_string;
	    temp_1 = Buffer_for_internal_error_on_console;
	    fill_pointer_new_value = Fill_pointer_for_current_gensym_string;
	    SET_FILL_POINTER(temp_1,fill_pointer_new_value);
	    copy_portion_of_string_into_gensym_string(Current_gensym_string,
		    FIX((SI_Long)0L),
		    Fill_pointer_for_current_gensym_string,
		    Buffer_for_internal_error_on_console,FIX((SI_Long)0L));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    current_gensym_string = 
	    Input_gensym_string_for_buffer_for_internal_error_on_console;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
	    3);
      fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
	      2);
	total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		1);
	  current_twriting_output_type = Qgensym_string;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		  0);
	    original_input_string = 
		    Input_gensym_string_for_buffer_for_internal_error_on_console;
	    twrite_ascii_from_gensym_string(Buffer_for_internal_error_on_console);
	    if ( !EQ(Current_gensym_string,original_input_string))
		Input_gensym_string_for_buffer_for_internal_error_on_console 
			= Current_gensym_string;
	    temp_1 = Buffer_for_internal_error_on_console;
	    fill_pointer_new_value = Fill_pointer_for_current_gensym_string;
	    SET_FILL_POINTER(temp_1,fill_pointer_new_value);
	    copy_portion_of_string_into_gensym_string(Current_gensym_string,
		    FIX((SI_Long)0L),
		    Fill_pointer_for_current_gensym_string,
		    Buffer_for_internal_error_on_console,FIX((SI_Long)0L));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    length_of_buffer = length(Buffer_for_internal_error_on_console);
    if (FIXNUM_LT(length_of_buffer,
	    Length_of_buffer_for_internal_error_on_console)) {
	temp_1 = Buffer_for_internal_error_on_console;
	temp = CHR('\000');
	SET_CHAR(temp_1,length_of_buffer,temp);
    }
    return print_internal_error_data_on_console(Buffer_for_internal_error_on_console);
}

/* PRINT-INTERNAL-ERROR-DATA-ON-CONSOLE */
Object print_internal_error_data_on_console(error_report_string)
    Object error_report_string;
{
    x_note_fn_call(36,30);
    format((SI_Long)3L,T,"~a",error_report_string);
    maybe_write_abort_file(error_report_string);
    return maybe_email_error_report(error_report_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Abort_file_written_p, Qabort_file_written_p);

static Object string_constant_19;  /* "abort" */

static Object string_constant_20;  /* "G2_ABORT_DIRECTORY" */

/* MAYBE-WRITE-ABORT-FILE */
Object maybe_write_abort_file(error_report_string)
    Object error_report_string;
{
    x_note_fn_call(36,31);
    if ( !TRUEP(Abort_file_written_p)) {
	Abort_file_written_p = T;
	return maybe_write_string_to_directory(string_constant_19,
		get_gensym_environment_variable(string_constant_20),
		error_report_string);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_21;  /* "g2_internal_error_report" */

static Object string_constant_22;  /* "cd ~A;/usr/bin/mv -f ~A `date +~A-%y-%m-%d-%H-%M-%S`-~(~A~)-~A-~A.log" */

/* MAYBE-WRITE-STRING-TO-DIRECTORY */
Object maybe_write_string_to_directory(name,directory_1,string_1)
    Object name, directory_1, string_1;
{
    Object temporary_file, host_name, port_list, gensymed_symbol, temp, temp_1;
    Object command_string;
    Object result;

    x_note_fn_call(36,32);
    temporary_file = directory_1 ? 
	    write_string_to_temporary_file(string_constant_21,string_1) : Nil;
    if (temporary_file) {
	result = get_raw_network_info();
	MVS_2(result,host_name,port_list);
	gensymed_symbol = Current_system_name;
	temp = get(gensymed_symbol,Qsystem_alias,_);
	if (temp);
	else
	    temp = gensymed_symbol;
	temp_1 = FIRST(port_list);
	command_string = tformat_text_string(7,string_constant_22,
		directory_1,temporary_file,name,temp,host_name,SECOND(temp_1));
	c_spawn_command_line_process(command_string);
	reclaim_text_string(command_string);
	reclaim_raw_network_info(host_name,port_list);
	reclaim_text_string(temporary_file);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Email_abort_message_sent_p, Qemail_abort_message_sent_p);

static Object string_constant_23;  /* "G2 Internal Error Report" */

static Object string_constant_24;  /* "G2_ABORT_EMAIL_ADDRESS" */

/* MAYBE-EMAIL-ERROR-REPORT */
Object maybe_email_error_report(error_report_string)
    Object error_report_string;
{
    x_note_fn_call(36,33);
    if ( !TRUEP(Email_abort_message_sent_p)) {
	Email_abort_message_sent_p = T;
	return maybe_email_string_to_address(string_constant_23,
		get_gensym_environment_variable(string_constant_24),
		error_report_string);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_25;  /* "/usr/ucb/mail -s '~A' ~A < ~A ; rm ~A" */

/* MAYBE-EMAIL-STRING-TO-ADDRESS */
Object maybe_email_string_to_address(subject,address,string_1)
    Object subject, address, string_1;
{
    Object temporary_file, command_string;

    x_note_fn_call(36,34);
    temporary_file = address ? 
	    write_string_to_temporary_file(string_constant_21,string_1) : Nil;
    if (temporary_file) {
	command_string = tformat_text_string(5,string_constant_25,subject,
		address,temporary_file,temporary_file);
	c_spawn_command_line_process(command_string);
	reclaim_text_string(command_string);
	reclaim_text_string(temporary_file);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Temporary_file_count, Qtemporary_file_count);

static Object Qunix;               /* unix */

static Object string_constant_26;  /* "/tmp/~A_~D" */

static Object Qwin32;              /* win32 */

static Object string_constant_27;  /* "c:\\temp\\~A_~D.txt" */

static Object string_constant_28;  /* "~A_~D" */

static Object Qutf_8_gensym_string_with_newline;  /* utf-8-gensym-string-with-newline */

/* WRITE-STRING-TO-TEMPORARY-FILE */
Object write_string_to_temporary_file(name_prefix,string_1)
    Object name_prefix, string_1;
{
    Object temp, temporary_file_count_new_value, temporary_file;
    Object stream_or_error, gensym_string;

    x_note_fn_call(36,35);
    if (EQ(G2_operating_system,Qunix))
	temp = string_constant_26;
    else if (EQ(G2_operating_system,Qwin32))
	temp = string_constant_27;
    else
	temp = string_constant_28;
    temporary_file_count_new_value = FIXNUM_ADD1(Temporary_file_count);
    Temporary_file_count = temporary_file_count_new_value;
    temporary_file = tformat_text_string(3,temp,name_prefix,
	    Temporary_file_count);
    stream_or_error = c_g2_stream_open(temporary_file,
	    G2_stream_open_mode_for_output);
    if (FIXNUM_EQ(stream_or_error,G2_stream_foreign_file_op_failure)) {
	reclaim_text_string(temporary_file);
	return VALUES_1(Nil);
    }
    else {
	gensym_string = STRINGP(string_1) ? string_1 : 
		export_text_string(2,string_1,
		Qutf_8_gensym_string_with_newline);
	c_g2_stream_write_string(gensym_string,stream_or_error,
		FIX((SI_Long)0L));
	if ( !EQ(gensym_string,string_1))
	    reclaim_gensym_string(gensym_string);
	g2ext_str_close(IFIX(stream_or_error));
	return VALUES_1(temporary_file);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);

DEFINE_VARIABLE_WITH_SYMBOL(System_has_paused, Qsystem_has_paused);

static Object string_constant_29;  /* "~a" */

static Object string_constant_30;  /* "Error acknowledged." */

static Object string_constant_31;  /* "  System is now paused.  " */

static Object string_constant_32;  /* "You may resume, reset, or restart." */

/* INTERNAL-ERROR-GIVEN-FORMAT-INFO */
Object internal_error_given_format_info(raw_format_string,
	    list_of_format_args,sure_of_format_info_p)
    Object raw_format_string, list_of_format_args, sure_of_format_info_p;
{
    Object error_within_error_p, current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object original_input_string, aref_arg_1, aref_arg_2, gensymed_symbol;
    Object gensymed_symbol_2, bombout_function, ab_loop_list_;
    Object wide_string_bv16, temp_1;
    SI_Long length_1, bv16_length, aref_arg_2_1, aref_new_value, arg, arg_1;
    SI_Long arg_2, gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(6);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(36,36);
    if (PUSH_AREA(Dynamic_area,0)) {
	error_within_error_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Error_within_error_p,Qerror_within_error_p,error_within_error_p,
		5);
	  notify_console_of_internal_error(raw_format_string,
		  list_of_format_args);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    current_wide_string = 
		    Input_string_for_buffer_for_internal_error_on_logbook;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		    3);
	      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		      2);
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    original_input_string = 
			    Input_string_for_buffer_for_internal_error_on_logbook;
		    write_internal_error(raw_format_string,
			    list_of_format_args,sure_of_format_info_p);
		    if ( !EQ(Current_wide_string,original_input_string))
			Input_string_for_buffer_for_internal_error_on_logbook 
				= Current_wide_string;
		    aref_arg_1 = Buffer_for_internal_error_on_logbook;
		    aref_arg_2 = Fill_pointer_for_current_wide_string;
		    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(aref_arg_1));
		    aref_arg_2_1 = bv16_length - (SI_Long)2L;
		    aref_new_value = IFIX(aref_arg_2) & (SI_Long)65535L;
		    UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2_1,aref_new_value);
		    aref_arg_2_1 = bv16_length - (SI_Long)1L;
		    aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2) >> 
			     -  - (SI_Long)16L;
		    UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2_1,aref_new_value);
		    UBYTE_16_ISASET_1(aref_arg_1,IFIX(aref_arg_2),(SI_Long)0L);
		    if (EQ(Current_wide_string,
			    Buffer_for_internal_error_on_logbook)) {
			if ((SI_Long)0L == 
				IFIX(Fill_pointer_for_current_wide_string))
			    temp = TRUEP(T);
			else {
			    temp = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L 
				    < 
				    IFIX(Fill_pointer_for_current_wide_string) 
				    : TRUEP(Qnil);
			    if (temp);
			    else {
				arg = (SI_Long)0L;
				arg_1 = (SI_Long)0L;
				arg_2 = (SI_Long)0L + 
					(IFIX(Fill_pointer_for_current_wide_string) 
					- (SI_Long)0L);
				temp = arg < arg_1 ? arg_1 < arg_2 : 
					TRUEP(Qnil);
			    }
			    if (temp) {
				copy_byte_vector_16_portion_carefully(Current_wide_string,
					FIX((SI_Long)0L),
					Buffer_for_internal_error_on_logbook,
					FIX((SI_Long)0L),
					FIX(IFIX(Fill_pointer_for_current_wide_string) 
					- (SI_Long)0L));
				temp = TRUEP(T);
			    }
			    else
				temp = TRUEP(Qnil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp);
		    else {
			gensymed_symbol = Current_wide_string;
			gensymed_symbol_1 = (SI_Long)0L;
			gensymed_symbol_2 = 
				Buffer_for_internal_error_on_logbook;
			gensymed_symbol_3 = (SI_Long)0L;
			gensymed_symbol_4 = 
				IFIX(Fill_pointer_for_current_wide_string) 
				- (SI_Long)0L;
			INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
				gensymed_symbol_1,
				UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
				gensymed_symbol_3,gensymed_symbol_4);
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  notify_engineer(2,string_constant_29,
		  Buffer_for_internal_error_on_logbook);
	  if ( !TRUEP(exit_on_abort_p()))
	      pause_for_internal_error(Buffer_for_internal_error_on_logbook);
	  bombout_function = Nil;
	  ab_loop_list_ = Bombout_clean_up_functions;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  bombout_function = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  FUNCALL_0(bombout_function);
	  goto next_loop;
	end_loop:;
	  if (exit_on_abort_p())
	      g2ext_exit_from_lisp((SI_Long)-1L);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2_1 = bv16_length - (SI_Long)2L;
	    aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2_1,aref_new_value);
	    aref_arg_2_1 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2_1,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
	    current_wide_string = wide_string_bv16;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		    3);
	      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		      2);
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(1,string_constant_30);
		    if (System_is_running &&  !TRUEP(System_has_paused)) {
			tformat(1,string_constant_31);
			tformat(1,string_constant_32);
		    }
		    temp_1 = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  result = notify_engineer(2,string_constant_29,temp_1);
	POP_SPECIAL();
    }
    POP_AREA(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Input_string_for_buffer_for_write_internal_error, Qinput_string_for_buffer_for_write_internal_error);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_for_write_internal_error, Qbuffer_for_write_internal_error);

static Object string_constant_33;  /* "G2 ABORTED DUE TO AN INTERNAL ERROR.  ~
				    *      For this reason, it may not be safe to run or save a knowledge base, ~
				    *      and you will be prevented from proceeding ~
				    *      until you acknowledge this warning.  ~
				    *      It is recommended that you ~
				    *      save out the current KB under a different name ~
				    *      (to avoid overwriting the original KB), ~
				    *      shut down G2, ~
				    *      restart G2 using the original KB (not the KB saved after the internal error), ~
				    *      and report the problem to Gensym.  ~
				    *      The internal error message was: \""
				    */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* WRITE-INTERNAL-ERROR */
Object write_internal_error(raw_format_string,list_of_format_args,
	    sure_of_format_info_p)
    Object raw_format_string, list_of_format_args, sure_of_format_info_p;
{
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object original_input_string, temp, aref_arg_1, aref_arg_2;
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long length_1, bv16_length, aref_arg_2_1, aref_new_value, arg, arg_1;
    SI_Long arg_2, gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(36,37);
    tformat(1,string_constant_33);
    if (sure_of_format_info_p) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  current_wide_string = 
		  Input_string_for_buffer_for_write_internal_error;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		  3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  original_input_string = 
			  Input_string_for_buffer_for_write_internal_error;
		  temp = SYMBOL_FUNCTION(Qtformat);
		  APPLY_2(temp,raw_format_string,list_of_format_args);
		  if ( !EQ(Current_wide_string,original_input_string))
		      Input_string_for_buffer_for_write_internal_error = 
			      Current_wide_string;
		  aref_arg_1 = Buffer_for_write_internal_error;
		  aref_arg_2 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(aref_arg_1));
		  aref_arg_2_1 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(aref_arg_2) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2_1,aref_new_value);
		  aref_arg_2_1 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2) >>  
			  -  - (SI_Long)16L;
		  UBYTE_16_ISASET_1(aref_arg_1,aref_arg_2_1,aref_new_value);
		  UBYTE_16_ISASET_1(aref_arg_1,IFIX(aref_arg_2),(SI_Long)0L);
		  if (EQ(Current_wide_string,
			      Buffer_for_write_internal_error)) {
		      if ((SI_Long)0L == 
			      IFIX(Fill_pointer_for_current_wide_string))
			  temp_1 = TRUEP(T);
		      else {
			  temp_1 = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L 
				  < 
				  IFIX(Fill_pointer_for_current_wide_string) 
				  : TRUEP(Qnil);
			  if (temp_1);
			  else {
			      arg = (SI_Long)0L;
			      arg_1 = (SI_Long)0L;
			      arg_2 = (SI_Long)0L + 
				      (IFIX(Fill_pointer_for_current_wide_string) 
				      - (SI_Long)0L);
			      temp_1 = arg < arg_1 ? arg_1 < arg_2 : 
				      TRUEP(Qnil);
			  }
			  if (temp_1) {
			      copy_byte_vector_16_portion_carefully(Current_wide_string,
				      FIX((SI_Long)0L),
				      Buffer_for_write_internal_error,
				      FIX((SI_Long)0L),
				      FIX(IFIX(Fill_pointer_for_current_wide_string) 
				      - (SI_Long)0L));
			      temp_1 = TRUEP(T);
			  }
			  else
			      temp_1 = TRUEP(Qnil);
		      }
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1);
		  else {
		      gensymed_symbol = Current_wide_string;
		      gensymed_symbol_1 = (SI_Long)0L;
		      gensymed_symbol_2 = Buffer_for_write_internal_error;
		      gensymed_symbol_3 = (SI_Long)0L;
		      gensymed_symbol_4 = 
			      IFIX(Fill_pointer_for_current_wide_string) - 
			      (SI_Long)0L;
		      INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			      gensymed_symbol_1,
			      UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			      gensymed_symbol_3,gensymed_symbol_4);
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	twrite_general_string(Buffer_for_write_internal_error);
    }
    else
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)48L));
    return twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)2L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_error_format_string, Qgensym_error_format_string);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_error_argument_list, Qgensym_error_argument_list);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_error_sure_of_format_info_p, Qgensym_error_sure_of_format_info_p);

DEFINE_VARIABLE_WITH_SYMBOL(All_signal_handlers_registered_p, Qall_signal_handlers_registered_p);

/* SIGNAL-CODE-NUMBER-FROM-NAME-SYMBOL */
Object signal_code_number_from_name_symbol(name_symbol)
    Object name_symbol;
{
    Object signal_code_number, registry_name_symbol, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp;

    x_note_fn_call(36,38);
    signal_code_number = Nil;
    registry_name_symbol = Nil;
    ab_loop_list_ = Signal_code_registry;
    ab_loop_it_ = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    signal_code_number = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    registry_name_symbol = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(name_symbol,registry_name_symbol) ? 
	    signal_code_number : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qsigpipe;            /* sigpipe */

static Object Qsigchld;            /* sigchld */

static Object Qgsi;                /* gsi */

/* REGISTER-ALL-SIGNAL-HANDLERS */
Object register_all_signal_handlers()
{
    Object code_number, name_in_operating_system, causes_core_dump_p;
    Object g2_signal_handler_p, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(36,39);
    if (do_not_catch_aborts_p()) {
	g2ext_establish_signal_handler(IFIX(signal_code_number_from_name_symbol(Qsigpipe)));
	g2ext_establish_signal_handler(IFIX(signal_code_number_from_name_symbol(Qsigchld)));
	if ( !EQ(Current_system_name,Qgsi)) {
	    code_number = Nil;
	    name_in_operating_system = Nil;
	    causes_core_dump_p = Nil;
	    g2_signal_handler_p = Nil;
	    ab_loop_list_ = Signal_code_registry;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    code_number = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    name_in_operating_system = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    causes_core_dump_p = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    g2_signal_handler_p = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (causes_core_dump_p &&  !(EQ(name_in_operating_system,
		    Qsigpipe) || EQ(name_in_operating_system,Qsigchld)))
		g2ext_unestablish_signal_handler(IFIX(code_number));
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	g2ext_inhibit_core_dumping();
	if ( !(All_signal_handlers_registered_p || EQ(Current_system_name,
		Qgsi))) {
	    register_all_signal_handlers_unconditionally();
	    All_signal_handlers_registered_p = T;
	    return VALUES_1(All_signal_handlers_registered_p);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* REGISTER-ALL-SIGNAL-HANDLERS-UNCONDITIONALLY */
Object register_all_signal_handlers_unconditionally()
{
    Object code_number, causes_core_dump_p, g2_signal_handler_p, ab_loop_list_;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(36,40);
    code_number = Nil;
    causes_core_dump_p = Nil;
    g2_signal_handler_p = Nil;
    ab_loop_list_ = Signal_code_registry;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    code_number = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    causes_core_dump_p = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    g2_signal_handler_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (causes_core_dump_p || g2_signal_handler_p)
	g2ext_establish_signal_handler(IFIX(code_number));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Internal_signal_caught_format_string, Qinternal_signal_caught_format_string);

/* INITIALIZE-INFORMATION-FROM-CAUGHT-SIGNAL */
Object initialize_information_from_caught_signal()
{
    x_note_fn_call(36,41);
    return VALUES_1(LIST_3(Nil,Nil,Backtrace_text_buffer_for_internal_error));
}

DEFINE_VARIABLE_WITH_SYMBOL(Information_from_caught_signal, Qinformation_from_caught_signal);

Object Do_error_trapping_qm = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Top_level_error_catcher_tag, Qtop_level_error_catcher_tag);

DEFINE_VARIABLE_WITH_SYMBOL(Top_level_error_seen, Qtop_level_error_seen);

/* G2INT-SIGNAL-HANDLER */
Object g2int_signal_handler()
{
    Object temp, second_new_value, g2_signal_handler_qm;
    SI_Long signal_code;
    Object result;

    x_note_fn_call(36,42);
    if (Error_within_error_p) {
	format((SI_Long)2L,Terminal_io,
		"~%An error occurred while G2 was reporting a signal.~%");
	format((SI_Long)2L,Terminal_io,"Sorry, cannot continue.~%");
	maybe_wait_for_return_key(0);
	exit_lisp_process(0);
    }
    signal_code = g2ext_most_recent_signal_code();
    g2ext_establish_signal_handler(signal_code);
    if (signal_code == IFIX(Sigfpe) && Arithmetic_errors_are_stack_errors_p)
	return signal_floating_point_exception_stack_error();
    else {
	Gensym_error_format_string = Internal_signal_caught_format_string;
	Gensym_error_argument_list = Information_from_caught_signal;
	Gensym_error_sure_of_format_info_p = T;
	temp = Information_from_caught_signal;
	M_FIRST(temp) = FIX(signal_code);
	temp = Information_from_caught_signal;
	second_new_value = get_signal_description_string(FIX(signal_code));
	M_SECOND(temp) = second_new_value;
	update_backtrace_text_buffer_for_internal_error();
	g2_signal_handler_qm = get_g2_signal_handler(FIX(signal_code));
	if (g2_signal_handler_qm)
	    return FUNCALL_0(g2_signal_handler_qm);
	else if (Top_level_error_catcher_tag) {
	    Top_level_error_seen = T;
	    result = VALUES_1(T);
	    THROW(Top_level_error_catcher_tag,result);
	}
	else {
	    format((SI_Long)2L,Terminal_io,
		    "~%An error ocurred outside of the top-level-error-catcher:~%");
	    if (Error_within_error_p)
		format((SI_Long)2L,Terminal_io,
			"~%An error ocurred while reporting another error~%");
	    else
		minimal_internal_error_given_format_info(Gensym_error_format_string,
			Gensym_error_argument_list,
			Gensym_error_sure_of_format_info_p);
	    return shutdown_or_exit(0);
	}
    }
}

/* G2INT-HANDLE-BROKEN-PIPE-SIGNAL */
Object g2int_handle_broken_pipe_signal()
{
    x_note_fn_call(36,43);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Input_gensym_string_for_gensym_error_message_buffer, Qinput_gensym_string_for_gensym_error_message_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_error_message_buffer, Qgensym_error_message_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Internal_error_trapped_format_string, Qinternal_error_trapped_format_string);

DEFINE_VARIABLE_WITH_SYMBOL(Information_from_trapped_error, Qinformation_from_trapped_error);

/* INITIALIZE-INFORMATION-FROM-TRAPPED-ERROR */
Object initialize_information_from_trapped_error()
{
    x_note_fn_call(36,44);
    return VALUES_1(LIST_2(Gensym_error_message_buffer,
	    Backtrace_text_buffer_for_internal_error));
}

static Object Qarithmetic_error_catcher;  /* arithmetic-error-catcher */

/* G2-ERROR-HANDLER-GIVEN-UPDATED-MESSAGE-BUFFER */
Object g2_error_handler_given_updated_message_buffer()
{
    Object result;

    x_note_fn_call(36,45);
    if (Inside_avoid_arithmetic_errors_p) {
	result = VALUES_1(T);
	THROW(Qarithmetic_error_catcher,result);
    }
    else if (Top_level_error_catcher_tag) {
	Gensym_error_format_string = Internal_error_trapped_format_string;
	update_backtrace_text_buffer_for_internal_error();
	Gensym_error_argument_list = Information_from_trapped_error;
	Gensym_error_sure_of_format_info_p = T;
	if (Do_error_trapping_qm) {
	    Top_level_error_seen = T;
	    result = VALUES_1(T);
	    THROW(Top_level_error_catcher_tag,result);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return shutdown_or_exit(0);
}

DEFINE_VARIABLE_WITH_SYMBOL(Shutdown_catch_tag, Qshutdown_catch_tag);

Object Legacy_mode_p = UNBOUND;

Object Scheduler_worker_vector = UNBOUND;

/* SHUTDOWN-OR-EXIT */
Object shutdown_or_exit varargs_1(int, n)
{
    Object status, thread;
    SI_Long index_1, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(36,46);
    INIT_ARGS_nonrelocating();
    status = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Legacy_mode_p) && Scheduler_worker_vector) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(Number_of_all_threads);
	thread = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	thread = ISVREF(Scheduler_worker_vector,index_1);
	if (threadp(thread) && thread_alive_p(thread))
	    kill_thread(thread);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    if (Shutdown_catch_tag) {
	result = VALUES_1(status);
	THROW(Shutdown_catch_tag,result);
    }
    else
	return g2_unrecoverable_error_exit();
}

/* G2-UNRECOVERABLE-ERROR-EXIT */
Object g2_unrecoverable_error_exit()
{
    Object temp;

    x_note_fn_call(36,47);
    temp = exit_lisp_process(0);
    return VALUES_1(temp);
}

/* G2INT-ERROR-HANDLER */
Object g2int_error_handler()
{
    x_note_fn_call(36,48);
    if (Error_within_error_p) {
	format((SI_Long)2L,Terminal_io,
		"~%An error occurred while G2 was reporting an error.~%");
	format((SI_Long)2L,Terminal_io,"Sorry, cannot continue.~%");
	maybe_wait_for_return_key(0);
	exit_lisp_process(0);
    }
    inline_get_backtrace();
    return g2_error_handler_given_updated_message_buffer();
}

static Object string_constant_34;  /* "-do-not-catch-aborts" */

static Object string_constant_35;  /* "-DO-NOT-CATCH-ABORTS" */

/* DO-NOT-CATCH-ABORTS-P */
Object do_not_catch_aborts_p()
{
    Object temp;

    x_note_fn_call(36,49);
    temp = get_command_line_flag_argument(1,string_constant_34);
    if (temp)
	return VALUES_1(temp);
    else
	return get_command_line_flag_argument(1,string_constant_35);
}

DEFINE_VARIABLE_WITH_SYMBOL(Task_to_warn_user_of_previously_aborted_g2, Qtask_to_warn_user_of_previously_aborted_g2);

/* MINIMAL-INTERNAL-ERROR-GIVEN-FORMAT-INFO */
Object minimal_internal_error_given_format_info(raw_format_string,
	    list_of_format_args,sure_of_format_info_p)
    Object raw_format_string, list_of_format_args, sure_of_format_info_p;
{
    Object error_within_error_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(36,50);
    error_within_error_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Error_within_error_p,Qerror_within_error_p,error_within_error_p,
	    0);
      result = notify_console_of_internal_error(raw_format_string,
	      list_of_format_args);
    POP_SPECIAL();
    return result;
}

/* REGISTER-ALL-SIGNAL-HANDLERS-FOR-LAUNCH */
Object register_all_signal_handlers_for_launch()
{
    Object temp, code_number, causes_core_dump_p, ab_loop_list_;
    Object ab_loop_desetq_;

    x_note_fn_call(36,51);
    temp = do_not_catch_aborts_p();
    if (temp)
	return VALUES_1(temp);
    else {
	code_number = Nil;
	causes_core_dump_p = Nil;
	ab_loop_list_ = Signal_code_registry;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	code_number = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	causes_core_dump_p = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (causes_core_dump_p)
	    g2ext_establish_launch_sig_handler(IFIX(code_number));
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* G2INT-SIGNAL-HANDLER-FOR-LAUNCH */
Object g2int_signal_handler_for_launch()
{
    SI_Long signal_code;

    x_note_fn_call(36,52);
    signal_code = g2ext_most_recent_signal_code();
    g2ext_establish_launch_sig_handler(signal_code);
    format((SI_Long)3L,Terminal_io,
	    "~&Signal ~a caught during launch.~%Sorry, must exit.~%",
	    FIX(signal_code));
    maybe_wait_for_return_key(0);
    return exit_lisp_process(0);
}

void os_error_INIT()
{
    Object sighup, pushnew_arg_1, pushnew_arg_3;
    Object signal_code_registry_new_value, sigquit, sigtrap, sigiot, sigemt;
    Object sigkill, sigbus, sigsys, sigpipe, sigalrm, sigusr1, sigusr2;
    Object sigchld, sigpwr, sigvtalrm, sigprof, sigio, sigwindow, sigstop;
    Object sigtstp, sigcont, sigttin, sigttou, siglost, sig30, sig31, sigdil;
    Object wide_string_bv16;
    SI_Long sigint, sigill, sigsegv, sigterm, bv16_length, aref_arg_2;
    SI_Long aref_new_value;
    Object Qg2int_signal_handler_for_launch, AB_package, Qos_error;
    Object Qg2int_error_handler, Qinitialize_information_from_trapped_error;
    Object list_constant_10, Kfuncall, string_constant_82;
    Object Qlength_of_gensym_error_message_buffer;
    Object Qg2int_handle_broken_pipe_signal, Qg2int_signal_handler;
    Object list_constant_9, Qinitialize_information_from_caught_signal;
    Object string_constant_81, list_constant_4;
    Object Qlength_of_buffer_for_write_internal_error, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69;
    Object Qlength_of_buffer_for_internal_error_on_logbook;
    Object Qlength_of_buffer_for_internal_error_on_console;
    Object Qlength_of_backtrace_text_buffer_for_internal_error;
    Object string_constant_68, Qbacktrace_cons_memory_usage;
    Object Qoutstanding_backtrace_conses, Qutilities1, list_constant_8;
    Object Qbacktrace_cons_counter_vector, Qmake_thread_array, list_constant_7;
    Object Qavailable_backtrace_conses_tail_vector;
    Object Qavailable_backtrace_conses_vector;
    Object Qinitialize_post_mortem_report_buffer, list_constant_6;
    Object list_constant_5, Qinitialize_post_mortem_internal_buffer;
    Object Qinitialize_post_mortem_ring_buffer_logfile_namestring;
    Object list_constant_3, list_constant_2;
    Object Qinitialize_post_mortem_ring_buffer, list_constant_1;
    Object Qinitialize_post_mortem_ring_buffer_length, string_constant_67;
    Object Qsigdil, string_constant_66, Qsig31, string_constant_65, Qsig30;
    Object string_constant_64, Qsiglost, Qrs6000, Qalphaosf;
    Object string_constant_63, Qsigttou, string_constant_62, Qsigttin;
    Object string_constant_61, Qsigcont, string_constant_60, Qsigtstp;
    Object string_constant_59, Qsigstop, string_constant_58, Qsigwindow;
    Object string_constant_57, Qsigio, string_constant_56, Qsigprof;
    Object string_constant_55, Qsigvtalrm, string_constant_54, Qsigpwr;
    Object string_constant_53, Qlinux, Qintelsol, Qsparcsol, Qsparcstation;
    Object Qhp9000s700, string_constant_52, Qsigusr2, string_constant_51;
    Object Qsigusr1, string_constant_50, Qsigterm, string_constant_49;
    Object Qsigalrm, Qhandle_broken_pipe_signal, string_constant_48;
    Object string_constant_47, Qsigsys, string_constant_46, Qsigsegv;
    Object string_constant_45, Qsigbus, string_constant_44, Qsigkill;
    Object string_constant_43, string_constant_42, Qsigemt, string_constant_41;
    Object Qsigiot, string_constant_40, Qsigtrap, string_constant_39, Qsigill;
    Object string_constant_38, Qsigquit, string_constant_37, Qsigint;
    Object string_constant_36, Qsighup;
    Object Qreset_structure_being_reclaimed_after_bombout;

    x_note_fn_call(36,53);
    SET_PACKAGE("AB");
    if (Bombout_clean_up_functions == UNBOUND)
	Bombout_clean_up_functions = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qreset_structure_being_reclaimed_after_bombout = 
	    STATIC_SYMBOL("RESET-STRUCTURE-BEING-RECLAIMED-AFTER-BOMBOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreset_structure_being_reclaimed_after_bombout,
	    STATIC_FUNCTION(reset_structure_being_reclaimed_after_bombout,
	    NIL,FALSE,0,0));
    def_bombout_clean_up_function(Qreset_structure_being_reclaimed_after_bombout);
    if (Signal_code_registry == UNBOUND)
	Signal_code_registry = Nil;
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qsighup = STATIC_SYMBOL("SIGHUP",AB_package);
    string_constant_36 = STATIC_STRING("hangup");
    sighup = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)1L) : Nil;
    if (sighup) {
	pushnew_arg_1 = list(6,sighup,Qsighup,string_constant_36,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigint = STATIC_SYMBOL("SIGINT",AB_package);
    string_constant_37 = STATIC_STRING("interrupt");
    sigint = (SI_Long)2L;
    if (FIX(sigint)) {
	pushnew_arg_1 = list(6,FIX(sigint),Qsigint,string_constant_37,Nil,
		Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigquit = STATIC_SYMBOL("SIGQUIT",AB_package);
    string_constant_38 = STATIC_STRING("quit");
    sigquit = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)3L) : Nil;
    if (sigquit) {
	pushnew_arg_1 = list(6,sigquit,Qsigquit,string_constant_38,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigill = STATIC_SYMBOL("SIGILL",AB_package);
    string_constant_39 = STATIC_STRING("illegal instruction");
    sigill = (SI_Long)4L;
    if (FIX(sigill)) {
	pushnew_arg_1 = list(6,FIX(sigill),Qsigill,string_constant_39,T,
		Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigtrap = STATIC_SYMBOL("SIGTRAP",AB_package);
    string_constant_40 = STATIC_STRING("trace trap");
    sigtrap = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)5L) : Nil;
    if (sigtrap) {
	pushnew_arg_1 = list(6,sigtrap,Qsigtrap,string_constant_40,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigiot = STATIC_SYMBOL("SIGIOT",AB_package);
    string_constant_41 = STATIC_STRING("IOT instruction or abort");
    sigiot = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)6L) : Nil;
    if (sigiot) {
	pushnew_arg_1 = list(6,sigiot,Qsigiot,string_constant_41,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigemt = STATIC_SYMBOL("SIGEMT",AB_package);
    string_constant_42 = STATIC_STRING("EMT instruction");
    sigemt = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)7L) : Nil;
    if (sigemt) {
	pushnew_arg_1 = list(6,sigemt,Qsigemt,string_constant_42,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    if (Sigfpe == UNBOUND)
	Sigfpe = FIX((SI_Long)8L);
    Qsigfpe = STATIC_SYMBOL("SIGFPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsigfpe,Sigfpe);
    string_constant_43 = STATIC_STRING("floating point exception");
    if (Sigfpe) {
	pushnew_arg_1 = list(6,Sigfpe,Qsigfpe,string_constant_43,T,Nil,T);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigkill = STATIC_SYMBOL("SIGKILL",AB_package);
    string_constant_44 = STATIC_STRING("kill");
    sigkill = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)9L) : Nil;
    if (sigkill) {
	pushnew_arg_1 = list(6,sigkill,Qsigkill,string_constant_44,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigbus = STATIC_SYMBOL("SIGBUS",AB_package);
    string_constant_45 = STATIC_STRING("bus error");
    sigbus = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)10L) : Nil;
    if (sigbus) {
	pushnew_arg_1 = list(6,sigbus,Qsigbus,string_constant_45,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigsegv = STATIC_SYMBOL("SIGSEGV",AB_package);
    string_constant_46 = STATIC_STRING("segmentation violation");
    sigsegv = (SI_Long)11L;
    if (FIX(sigsegv)) {
	pushnew_arg_1 = list(6,FIX(sigsegv),Qsigsegv,string_constant_46,T,
		Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigsys = STATIC_SYMBOL("SIGSYS",AB_package);
    string_constant_47 = STATIC_STRING("bad argument to system call");
    sigsys = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)12L) : Nil;
    if (sigsys) {
	pushnew_arg_1 = list(6,sigsys,Qsigsys,string_constant_47,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigpipe = STATIC_SYMBOL("SIGPIPE",AB_package);
    string_constant_48 = 
	    STATIC_STRING("write on a pipe with no one to read it");
    Qhandle_broken_pipe_signal = STATIC_SYMBOL("HANDLE-BROKEN-PIPE-SIGNAL",
	    AB_package);
    sigpipe = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)13L) : Nil;
    if (sigpipe) {
	pushnew_arg_1 = list(6,sigpipe,Qsigpipe,string_constant_48,T,
		Qhandle_broken_pipe_signal,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigalrm = STATIC_SYMBOL("SIGALRM",AB_package);
    string_constant_49 = STATIC_STRING("alarm clock");
    sigalrm = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)14L) : Nil;
    if (sigalrm) {
	pushnew_arg_1 = list(6,sigalrm,Qsigalrm,string_constant_49,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigterm = STATIC_SYMBOL("SIGTERM",AB_package);
    string_constant_50 = 
	    STATIC_STRING("software termination signal from kill");
    sigterm = (SI_Long)15L;
    if (FIX(sigterm)) {
	pushnew_arg_1 = list(6,FIX(sigterm),Qsigterm,string_constant_50,
		Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigusr1 = STATIC_SYMBOL("SIGUSR1",AB_package);
    string_constant_51 = STATIC_STRING("user defined signal 1");
    sigusr1 = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)16L) : Nil;
    if (sigusr1) {
	pushnew_arg_1 = list(6,sigusr1,Qsigusr1,string_constant_51,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigusr2 = STATIC_SYMBOL("SIGUSR2",AB_package);
    string_constant_52 = STATIC_STRING("user defined signal 2");
    sigusr2 = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)17L) : Nil;
    if (sigusr2) {
	pushnew_arg_1 = list(6,sigusr2,Qsigusr2,string_constant_52,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qalphaosf = STATIC_SYMBOL("ALPHAOSF",AB_package);
    Qrs6000 = STATIC_SYMBOL("RS6000",AB_package);
    Qhp9000s700 = STATIC_SYMBOL("HP9000S700",AB_package);
    Qsparcstation = STATIC_SYMBOL("SPARCSTATION",AB_package);
    Qsparcsol = STATIC_SYMBOL("SPARCSOL",AB_package);
    Qintelsol = STATIC_SYMBOL("INTELSOL",AB_package);
    Qlinux = STATIC_SYMBOL("LINUX",AB_package);
    Qsigchld = STATIC_SYMBOL("SIGCHLD",AB_package);
    string_constant_53 = STATIC_STRING("death of a child");
    if (EQ(G2_machine_type,Qalphaosf) || EQ(G2_machine_type,Qrs6000))
	sigchld = FIX((SI_Long)20L);
    else if (EQ(G2_machine_type,Qhp9000s700) || EQ(G2_machine_type,
	    Qsparcstation) || EQ(G2_machine_type,Qsparcsol) || 
	    EQ(G2_machine_type,Qintelsol))
	sigchld = FIX((SI_Long)18L);
    else if (EQ(G2_machine_type,Qlinux))
	sigchld = FIX((SI_Long)17L);
    else
	sigchld = Nil;
    if (sigchld) {
	pushnew_arg_1 = list(6,sigchld,Qsigchld,string_constant_53,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigpwr = STATIC_SYMBOL("SIGPWR",AB_package);
    string_constant_54 = STATIC_STRING("power-fail restart");
    sigpwr = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)19L) : Nil;
    if (sigpwr) {
	pushnew_arg_1 = list(6,sigpwr,Qsigpwr,string_constant_54,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigvtalrm = STATIC_SYMBOL("SIGVTALRM",AB_package);
    string_constant_55 = STATIC_STRING("virtual time alarm");
    sigvtalrm = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)20L) : Nil;
    if (sigvtalrm) {
	pushnew_arg_1 = list(6,sigvtalrm,Qsigvtalrm,string_constant_55,Nil,
		Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigprof = STATIC_SYMBOL("SIGPROF",AB_package);
    string_constant_56 = STATIC_STRING("profiling time alarm");
    sigprof = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)21L) : Nil;
    if (sigprof) {
	pushnew_arg_1 = list(6,sigprof,Qsigprof,string_constant_56,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigio = STATIC_SYMBOL("SIGIO",AB_package);
    string_constant_57 = STATIC_STRING("input/output possible signal");
    sigio = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)22L) : Nil;
    if (sigio) {
	pushnew_arg_1 = list(6,sigio,Qsigio,string_constant_57,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigwindow = STATIC_SYMBOL("SIGWINDOW",AB_package);
    string_constant_58 = STATIC_STRING("window system signal");
    sigwindow = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)23L) : Nil;
    if (sigwindow) {
	pushnew_arg_1 = list(6,sigwindow,Qsigwindow,string_constant_58,Nil,
		Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigstop = STATIC_SYMBOL("SIGSTOP",AB_package);
    string_constant_59 = STATIC_STRING("sendable stop signal not from tty");
    sigstop = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)24L) : Nil;
    if (sigstop) {
	pushnew_arg_1 = list(6,sigstop,Qsigstop,string_constant_59,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigtstp = STATIC_SYMBOL("SIGTSTP",AB_package);
    string_constant_60 = STATIC_STRING("stop signal from tty");
    sigtstp = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)25L) : Nil;
    if (sigtstp) {
	pushnew_arg_1 = list(6,sigtstp,Qsigtstp,string_constant_60,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigcont = STATIC_SYMBOL("SIGCONT",AB_package);
    string_constant_61 = STATIC_STRING("continue a stopped process");
    sigcont = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)26L) : Nil;
    if (sigcont) {
	pushnew_arg_1 = list(6,sigcont,Qsigcont,string_constant_61,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigttin = STATIC_SYMBOL("SIGTTIN",AB_package);
    string_constant_62 = STATIC_STRING("background tty read");
    sigttin = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)27L) : Nil;
    if (sigttin) {
	pushnew_arg_1 = list(6,sigttin,Qsigttin,string_constant_62,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigttou = STATIC_SYMBOL("SIGTTOU",AB_package);
    string_constant_63 = STATIC_STRING("background tty write");
    sigttou = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)28L) : Nil;
    if (sigttou) {
	pushnew_arg_1 = list(6,sigttou,Qsigttou,string_constant_63,Nil,Nil,
		Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsiglost = STATIC_SYMBOL("SIGLOST",AB_package);
    string_constant_64 = STATIC_STRING("resource lost");
    siglost = EQ(G2_machine_type,Qalphaosf) || EQ(G2_machine_type,Qrs6000) 
	    ? FIX((SI_Long)29L) : Nil;
    if (siglost) {
	pushnew_arg_1 = list(6,siglost,Qsiglost,string_constant_64,T,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsig30 = STATIC_SYMBOL("SIG30",AB_package);
    string_constant_65 = STATIC_STRING("signal 30 (unknown error)");
    sig30 = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)30L) : Nil;
    if (sig30) {
	pushnew_arg_1 = list(6,sig30,Qsig30,string_constant_65,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsig31 = STATIC_SYMBOL("SIG31",AB_package);
    string_constant_66 = STATIC_STRING("signal 31 (unknown error)");
    sig31 = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)31L) : Nil;
    if (sig31) {
	pushnew_arg_1 = list(6,sig31,Qsig31,string_constant_66,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    Qsigdil = STATIC_SYMBOL("SIGDIL",AB_package);
    string_constant_67 = STATIC_STRING("DIL signal");
    sigdil = EQ(G2_operating_system,Qunix) ? FIX((SI_Long)32L) : Nil;
    if (sigdil) {
	pushnew_arg_1 = list(6,sigdil,Qsigdil,string_constant_67,Nil,Nil,Nil);
	pushnew_arg_3 = SYMBOL_FUNCTION(Qequal);
	signal_code_registry_new_value = adjoin(4,pushnew_arg_1,
		Signal_code_registry,Ktest,pushnew_arg_3);
	Signal_code_registry = signal_code_registry_new_value;
    }
    string_constant = STATIC_STRING("unknown signal");
    Qinside_avoid_arithmetic_errors_p = 
	    STATIC_SYMBOL("INSIDE-AVOID-ARITHMETIC-ERRORS-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinside_avoid_arithmetic_errors_p,
	    Inside_avoid_arithmetic_errors_p);
    Qos_error = STATIC_SYMBOL("OS-ERROR",AB_package);
    record_system_variable(Qinside_avoid_arithmetic_errors_p,Qos_error,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qarithmetic_errors_are_stack_errors_p = 
	    STATIC_SYMBOL("ARITHMETIC-ERRORS-ARE-STACK-ERRORS-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qarithmetic_errors_are_stack_errors_p,
	    Arithmetic_errors_are_stack_errors_p);
    record_system_variable(Qarithmetic_errors_are_stack_errors_p,Qos_error,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_1 = STATIC_STRING("pmsize");
    string_constant_2 = STATIC_STRING("G2PMSIZE");
    Qcurrent_post_mortem_ring_buffer_length = 
	    STATIC_SYMBOL("CURRENT-POST-MORTEM-RING-BUFFER-LENGTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_post_mortem_ring_buffer_length,
	    Current_post_mortem_ring_buffer_length);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_post_mortem_ring_buffer_length = 
	    STATIC_SYMBOL("INITIALIZE-POST-MORTEM-RING-BUFFER-LENGTH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_post_mortem_ring_buffer_length,
	    STATIC_FUNCTION(initialize_post_mortem_ring_buffer_length,NIL,
	    FALSE,0,0));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_post_mortem_ring_buffer_length);
    record_system_variable(Qcurrent_post_mortem_ring_buffer_length,
	    Qos_error,list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_post_mortem_ring_buffer = 
	    STATIC_SYMBOL("CURRENT-POST-MORTEM-RING-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_post_mortem_ring_buffer,
	    Current_post_mortem_ring_buffer);
    Qinitialize_post_mortem_ring_buffer = 
	    STATIC_SYMBOL("INITIALIZE-POST-MORTEM-RING-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_post_mortem_ring_buffer,
	    STATIC_FUNCTION(initialize_post_mortem_ring_buffer,NIL,FALSE,0,0));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_post_mortem_ring_buffer);
    record_system_variable(Qcurrent_post_mortem_ring_buffer,Qos_error,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qlog_post_mortem_ring_buffer_to_file_p = 
	    STATIC_SYMBOL("LOG-POST-MORTEM-RING-BUFFER-TO-FILE-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_post_mortem_ring_buffer_to_file_p,
	    Log_post_mortem_ring_buffer_to_file_p);
    record_system_variable(Qlog_post_mortem_ring_buffer_to_file_p,
	    Qos_error,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpost_mortem_ring_buffer_logfile_namestring = 
	    STATIC_SYMBOL("POST-MORTEM-RING-BUFFER-LOGFILE-NAMESTRING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_mortem_ring_buffer_logfile_namestring,
	    Post_mortem_ring_buffer_logfile_namestring);
    Qinitialize_post_mortem_ring_buffer_logfile_namestring = 
	    STATIC_SYMBOL("INITIALIZE-POST-MORTEM-RING-BUFFER-LOGFILE-NAMESTRING",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_post_mortem_ring_buffer_logfile_namestring);
    record_system_variable(Qpost_mortem_ring_buffer_logfile_namestring,
	    Qos_error,list_constant_3,Qnil,Qnil,Qnil,Qnil);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qinitialize_post_mortem_ring_buffer_logfile_namestring,
	    STATIC_FUNCTION(initialize_post_mortem_ring_buffer_logfile_namestring,
	    NIL,FALSE,0,0));
    Qpost_mortem_ring_buffer_logfile_stream = 
	    STATIC_SYMBOL("POST-MORTEM-RING-BUFFER-LOGFILE-STREAM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_mortem_ring_buffer_logfile_stream,
	    Post_mortem_ring_buffer_logfile_stream);
    record_system_variable(Qpost_mortem_ring_buffer_logfile_stream,
	    Qos_error,Nil,Qnil,Qnil,Qnil,Qnil);
    Qpost_mortem_ring_buffer_logfile_line_count = 
	    STATIC_SYMBOL("POST-MORTEM-RING-BUFFER-LOGFILE-LINE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_mortem_ring_buffer_logfile_line_count,
	    Post_mortem_ring_buffer_logfile_line_count);
    record_system_variable(Qpost_mortem_ring_buffer_logfile_line_count,
	    Qos_error,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (Depth_of_post_mortem_checkpoint_reporting == UNBOUND)
	Depth_of_post_mortem_checkpoint_reporting = FIX((SI_Long)5L);
    Qpost_mortem_internal_buffer = 
	    STATIC_SYMBOL("POST-MORTEM-INTERNAL-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_mortem_internal_buffer,
	    Post_mortem_internal_buffer);
    Qinitialize_post_mortem_internal_buffer = 
	    STATIC_SYMBOL("INITIALIZE-POST-MORTEM-INTERNAL-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_post_mortem_internal_buffer,
	    STATIC_FUNCTION(initialize_post_mortem_internal_buffer,NIL,
	    FALSE,0,0));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_post_mortem_internal_buffer);
    record_system_variable(Qpost_mortem_internal_buffer,Qos_error,
	    list_constant_5,Qnil,Qnil,Qnil,Qnil);
    Qpost_mortem_report_buffer = STATIC_SYMBOL("POST-MORTEM-REPORT-BUFFER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpost_mortem_report_buffer,
	    Post_mortem_report_buffer);
    Qinitialize_post_mortem_report_buffer = 
	    STATIC_SYMBOL("INITIALIZE-POST-MORTEM-REPORT-BUFFER",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_post_mortem_report_buffer);
    record_system_variable(Qpost_mortem_report_buffer,Qos_error,
	    list_constant_6,Qnil,Qnil,Qnil,Qnil);
    string_constant_3 = STATIC_STRING("<- ...");
    string_constant_4 = STATIC_STRING("<-");
    SET_SYMBOL_FUNCTION(Qinitialize_post_mortem_report_buffer,
	    STATIC_FUNCTION(initialize_post_mortem_report_buffer,NIL,FALSE,
	    0,0));
    string_constant_5 = 
	    string_append2(STATIC_STRING("This G2 image is operating after an internal error occurred.  ~\n     It is not recommended that you continue using this image.  ~\n     A KB saved from this image should be use"),
	    STATIC_STRING("d ~\n     for reference purposes only.  ~\n     Please shut down this image and start a fresh G2 image."));
    Qavailable_backtrace_conses = 
	    STATIC_SYMBOL("AVAILABLE-BACKTRACE-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_backtrace_conses,
	    Available_backtrace_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_backtrace_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_backtrace_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-BACKTRACE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_backtrace_conses_tail,
	    Available_backtrace_conses_tail);
    record_system_variable(Qavailable_backtrace_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_backtrace_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-BACKTRACE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_backtrace_conses_vector,
	    Available_backtrace_conses_vector);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_backtrace_conses_vector,Qutilities1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qavailable_backtrace_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-BACKTRACE-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_backtrace_conses_tail_vector,
	    Available_backtrace_conses_tail_vector);
    record_system_variable(Qavailable_backtrace_conses_tail_vector,
	    Qutilities1,list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qbacktrace_cons_counter_vector = 
	    STATIC_SYMBOL("BACKTRACE-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbacktrace_cons_counter_vector,
	    Backtrace_cons_counter_vector);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qbacktrace_cons_counter_vector,Qutilities1,
	    list_constant_8,Qnil,Qt,Qnil,Qnil);
    Qbacktrace_cons_counter = STATIC_SYMBOL("BACKTRACE-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbacktrace_cons_counter,Backtrace_cons_counter);
    record_system_variable(Qbacktrace_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_backtrace_conses = 
	    STATIC_SYMBOL("OUTSTANDING-BACKTRACE-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_backtrace_conses,
	    STATIC_FUNCTION(outstanding_backtrace_conses,NIL,FALSE,0,0));
    Qbacktrace_cons_memory_usage = 
	    STATIC_SYMBOL("BACKTRACE-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qbacktrace_cons_memory_usage,
	    STATIC_FUNCTION(backtrace_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_68 = STATIC_STRING("1q83-KWy9k83-KVy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_backtrace_conses);
    push_optimized_constant(Qbacktrace_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qbacktrace = STATIC_SYMBOL("BACKTRACE",AB_package);
    if (Backtrace_stack_for_internal_error == UNBOUND)
	Backtrace_stack_for_internal_error = make_array(5,
		Size_of_backtrace_stack_for_internal_error,Kelement_type,T,
		Kinitial_element,Nil);
    if (Index_of_top_of_backtrace_stack == UNBOUND)
	Index_of_top_of_backtrace_stack = FIX((SI_Long)-1L);
    Qlength_of_backtrace_text_buffer_for_internal_error = 
	    STATIC_SYMBOL("LENGTH-OF-BACKTRACE-TEXT-BUFFER-FOR-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qlength_of_backtrace_text_buffer_for_internal_error,
	    FIX((SI_Long)4000L));
    if (Input_string_for_backtrace_text_buffer_for_internal_error == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Input_string_for_backtrace_text_buffer_for_internal_error = 
		wide_string_bv16;
    }
    if (Backtrace_text_buffer_for_internal_error == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Backtrace_text_buffer_for_internal_error = wide_string_bv16;
    }
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_6 = STATIC_STRING("Backtrace:");
    string_constant_7 = STATIC_STRING("~%  ~A");
    string_constant_8 = STATIC_STRING("~%  ");
    string_constant_9 = STATIC_STRING("~%");
    Qerror_within_error_p = STATIC_SYMBOL("ERROR-WITHIN-ERROR-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qerror_within_error_p,Error_within_error_p);
    record_system_variable(Qerror_within_error_p,Qos_error,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qlength_of_buffer_for_internal_error_on_console = 
	    STATIC_SYMBOL("LENGTH-OF-BUFFER-FOR-INTERNAL-ERROR-ON-CONSOLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qlength_of_buffer_for_internal_error_on_console,
	    FIX((SI_Long)4000L));
    if (Input_gensym_string_for_buffer_for_internal_error_on_console == 
	    UNBOUND)
	Input_gensym_string_for_buffer_for_internal_error_on_console = 
		make_string(1,FIX((SI_Long)4000L));
    if (Buffer_for_internal_error_on_console == UNBOUND)
	Buffer_for_internal_error_on_console = make_array(5,
		FIX((SI_Long)4000L),Kelement_type,Qstring_char,
		Kfill_pointer,FIX((SI_Long)0L));
    Qlength_of_buffer_for_internal_error_on_logbook = 
	    STATIC_SYMBOL("LENGTH-OF-BUFFER-FOR-INTERNAL-ERROR-ON-LOGBOOK",
	    AB_package);
    SET_SYMBOL_VALUE(Qlength_of_buffer_for_internal_error_on_logbook,
	    FIX((SI_Long)4000L));
    if (Input_string_for_buffer_for_internal_error_on_logbook == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Input_string_for_buffer_for_internal_error_on_logbook = 
		wide_string_bv16;
    }
    if (Buffer_for_internal_error_on_logbook == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Buffer_for_internal_error_on_logbook = wide_string_bv16;
    }
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    string_constant_10 = 
	    STATIC_STRING("~%------------------------------------");
    string_constant_11 = STATIC_STRING("~%AN INTERNAL ERROR OCCURRED!~%");
    Qsystem_alias = STATIC_SYMBOL("SYSTEM-ALIAS",AB_package);
    string_constant_12 = STATIC_STRING("~a ");
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    string_constant_13 = STATIC_STRING(" (~a)~%");
    string_constant_14 = STATIC_STRING("~%Raw internal error data follows:");
    Qtformat = STATIC_SYMBOL("TFORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qtformat,STATIC_FUNCTION(tformat,NIL,TRUE,1,10));
    string_constant_15 = STATIC_STRING("~%[~d ~a ~d");
    string_constant_69 = STATIC_STRING("Jan");
    string_constant_70 = STATIC_STRING("Feb");
    string_constant_71 = STATIC_STRING("Mar");
    string_constant_72 = STATIC_STRING("Apr");
    string_constant_73 = STATIC_STRING("May");
    string_constant_74 = STATIC_STRING("Jun");
    string_constant_75 = STATIC_STRING("Jul");
    string_constant_76 = STATIC_STRING("Aug");
    string_constant_77 = STATIC_STRING("Sep");
    string_constant_78 = STATIC_STRING("Oct");
    string_constant_79 = STATIC_STRING("Nov");
    string_constant_80 = STATIC_STRING("Dec");
    list_constant = STATIC_LIST((SI_Long)12L,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80);
    string_constant_16 = STATIC_STRING("  ~d:~a~d:~a~d]");
    string_constant_17 = STATIC_STRING("0");
    string_constant_18 = STATIC_STRING("");
    if (Abort_file_written_p == UNBOUND)
	Abort_file_written_p = Nil;
    string_constant_19 = STATIC_STRING("abort");
    string_constant_20 = STATIC_STRING("G2_ABORT_DIRECTORY");
    string_constant_21 = STATIC_STRING("g2_internal_error_report");
    string_constant_22 = 
	    STATIC_STRING("cd ~A;/usr/bin/mv -f ~A `date +~A-%y-%m-%d-%H-%M-%S`-~(~A~)-~A-~A.log");
    if (Email_abort_message_sent_p == UNBOUND)
	Email_abort_message_sent_p = Nil;
    string_constant_23 = STATIC_STRING("G2 Internal Error Report");
    string_constant_24 = STATIC_STRING("G2_ABORT_EMAIL_ADDRESS");
    string_constant_25 = 
	    STATIC_STRING("/usr/ucb/mail -s \'~A\' ~A < ~A ; rm ~A");
    if (Temporary_file_count == UNBOUND)
	Temporary_file_count = FIX((SI_Long)0L);
    string_constant_26 = STATIC_STRING("/tmp/~A_~D");
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    string_constant_27 = STATIC_STRING("c:\\temp\\~A_~D.txt");
    string_constant_28 = STATIC_STRING("~A_~D");
    Qutf_8_gensym_string_with_newline = 
	    STATIC_SYMBOL("UTF-8-GENSYM-STRING-WITH-NEWLINE",AB_package);
    string_constant_29 = STATIC_STRING("~a");
    string_constant_30 = STATIC_STRING("Error acknowledged.");
    string_constant_31 = STATIC_STRING("  System is now paused.  ");
    string_constant_32 = STATIC_STRING("You may resume, reset, or restart.");
    Qlength_of_buffer_for_write_internal_error = 
	    STATIC_SYMBOL("LENGTH-OF-BUFFER-FOR-WRITE-INTERNAL-ERROR",
	    AB_package);
    SET_SYMBOL_VALUE(Qlength_of_buffer_for_write_internal_error,
	    FIX((SI_Long)4000L));
    if (Input_string_for_buffer_for_write_internal_error == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Input_string_for_buffer_for_write_internal_error = wide_string_bv16;
    }
    if (Buffer_for_write_internal_error == UNBOUND) {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)4000L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)4000L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)4000L,(SI_Long)0L);
	Buffer_for_write_internal_error = wide_string_bv16;
    }
    string_constant_33 = string_appendn(4,
	    STATIC_STRING("G2 ABORTED DUE TO AN INTERNAL ERROR.  ~\n     For this reason, it may not be safe to run or save a knowledge base, ~\n     and you will be prevented from proceeding ~\n     until"),
	    STATIC_STRING(" you acknowledge this warning.  ~\n     It is recommended that you ~\n     save out the current KB under a different name ~\n     (to avoid overwriting the original KB), ~\n     s"),
	    STATIC_STRING("hut down G2, ~\n     restart G2 using the original KB (not the KB saved after the internal error), ~\n     and report the problem to Gensym.  ~\n     The internal error message w"),
	    STATIC_STRING("as: \""));
    array_constant_2 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)44L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)45L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)54L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)55L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    if (Gensym_error_format_string == UNBOUND)
	Gensym_error_format_string = string_constant_18;
    if (Gensym_error_argument_list == UNBOUND)
	Gensym_error_argument_list = Nil;
    if (Gensym_error_sure_of_format_info_p == UNBOUND)
	Gensym_error_sure_of_format_info_p = Nil;
    Qall_signal_handlers_registered_p = 
	    STATIC_SYMBOL("ALL-SIGNAL-HANDLERS-REGISTERED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_signal_handlers_registered_p,
	    All_signal_handlers_registered_p);
    record_system_variable(Qall_signal_handlers_registered_p,Qos_error,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    string_constant_81 = STATIC_STRING("Signal ~a (`~a\') caught.~%~a");
    if (Internal_signal_caught_format_string == UNBOUND)
	Internal_signal_caught_format_string = string_constant_81;
    Qinformation_from_caught_signal = 
	    STATIC_SYMBOL("INFORMATION-FROM-CAUGHT-SIGNAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinformation_from_caught_signal,
	    Information_from_caught_signal);
    Qinitialize_information_from_caught_signal = 
	    STATIC_SYMBOL("INITIALIZE-INFORMATION-FROM-CAUGHT-SIGNAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_information_from_caught_signal,
	    STATIC_FUNCTION(initialize_information_from_caught_signal,NIL,
	    FALSE,0,0));
    list_constant_9 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_information_from_caught_signal);
    record_system_variable(Qinformation_from_caught_signal,Qos_error,
	    list_constant_9,Qnil,Qnil,Qnil,Qnil);
    Do_error_trapping_qm = T;
    if (Top_level_error_catcher_tag == UNBOUND)
	Top_level_error_catcher_tag = Nil;
    if (Top_level_error_seen == UNBOUND)
	Top_level_error_seen = Nil;
    Qg2int_signal_handler = STATIC_SYMBOL("G2INT-SIGNAL-HANDLER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_signal_handler,
	    STATIC_FUNCTION(g2int_signal_handler,NIL,FALSE,0,0));
    Qg2int_handle_broken_pipe_signal = 
	    STATIC_SYMBOL("G2INT-HANDLE-BROKEN-PIPE-SIGNAL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_broken_pipe_signal,
	    STATIC_FUNCTION(g2int_handle_broken_pipe_signal,NIL,FALSE,0,0));
    Qlength_of_gensym_error_message_buffer = 
	    STATIC_SYMBOL("LENGTH-OF-GENSYM-ERROR-MESSAGE-BUFFER",AB_package);
    SET_SYMBOL_VALUE(Qlength_of_gensym_error_message_buffer,
	    FIX((SI_Long)1000L));
    if (Input_gensym_string_for_gensym_error_message_buffer == UNBOUND)
	Input_gensym_string_for_gensym_error_message_buffer = 
		make_string(1,FIX((SI_Long)1000L));
    if (Gensym_error_message_buffer == UNBOUND)
	Gensym_error_message_buffer = make_array(5,FIX((SI_Long)1000L),
		Kelement_type,Qstring_char,Kfill_pointer,FIX((SI_Long)0L));
    string_constant_82 = STATIC_STRING("~a~%~a");
    if (Internal_error_trapped_format_string == UNBOUND)
	Internal_error_trapped_format_string = string_constant_82;
    Qinformation_from_trapped_error = 
	    STATIC_SYMBOL("INFORMATION-FROM-TRAPPED-ERROR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinformation_from_trapped_error,
	    Information_from_trapped_error);
    Qinitialize_information_from_trapped_error = 
	    STATIC_SYMBOL("INITIALIZE-INFORMATION-FROM-TRAPPED-ERROR",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_information_from_trapped_error);
    record_system_variable(Qinformation_from_trapped_error,Qos_error,
	    list_constant_10,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_information_from_trapped_error,
	    STATIC_FUNCTION(initialize_information_from_trapped_error,NIL,
	    FALSE,0,0));
    Qarithmetic_error_catcher = STATIC_SYMBOL("ARITHMETIC-ERROR-CATCHER",
	    AB_package);
    if (Shutdown_catch_tag == UNBOUND)
	Shutdown_catch_tag = Nil;
    Qg2int_error_handler = STATIC_SYMBOL("G2INT-ERROR-HANDLER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_error_handler,
	    STATIC_FUNCTION(g2int_error_handler,NIL,FALSE,0,0));
    string_constant_34 = STATIC_STRING("-do-not-catch-aborts");
    string_constant_35 = STATIC_STRING("-DO-NOT-CATCH-ABORTS");
    Qtask_to_warn_user_of_previously_aborted_g2 = 
	    STATIC_SYMBOL("TASK-TO-WARN-USER-OF-PREVIOUSLY-ABORTED-G2",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_to_warn_user_of_previously_aborted_g2,
	    Task_to_warn_user_of_previously_aborted_g2);
    record_system_variable(Qtask_to_warn_user_of_previously_aborted_g2,
	    Qos_error,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_signal_handler_for_launch = 
	    STATIC_SYMBOL("G2INT-SIGNAL-HANDLER-FOR-LAUNCH",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_signal_handler_for_launch,
	    STATIC_FUNCTION(g2int_signal_handler_for_launch,NIL,FALSE,0,0));
}
