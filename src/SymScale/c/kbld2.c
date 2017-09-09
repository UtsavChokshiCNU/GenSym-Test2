/* kbld2.c
 * Input file:  kb-load2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbld2.h"


/* DELETE-BLOCK-AFTER-READING-KB */
Object delete_block_after_reading_kb(block)
    Object block;
{
    x_note_fn_call(132,0);
    Blocks_to_delete_after_reading_kb = gensym_cons_1(block,
	    Blocks_to_delete_after_reading_kb);
    return VALUES_1(Blocks_to_delete_after_reading_kb);
}

DEFINE_VARIABLE_WITH_SYMBOL(Connections_to_delete_after_reading_kb, Qconnections_to_delete_after_reading_kb);

/* DELETE-CONNECTION-AFTER-READING-KB */
Object delete_connection_after_reading_kb(connection)
    Object connection;
{
    x_note_fn_call(132,1);
    Connections_to_delete_after_reading_kb = gensym_cons_1(connection,
	    Connections_to_delete_after_reading_kb);
    return VALUES_1(Connections_to_delete_after_reading_kb);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_to_delete_after_unsquirreling, Qblocks_to_delete_after_unsquirreling);

/* DELETE-BLOCK-AFTER-UNSQUIRRELING */
Object delete_block_after_unsquirreling(block)
    Object block;
{
    x_note_fn_call(132,2);
    Blocks_to_delete_after_unsquirreling = gensym_cons_1(block,
	    Blocks_to_delete_after_unsquirreling);
    return VALUES_1(Blocks_to_delete_after_unsquirreling);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_with_bad_connections, Qblocks_with_bad_connections);

Object Switched_once_only_post_loads_are_after_conflict_resolution = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(List_of_module_pre_conflict_resolution_post_loading_functions, Qlist_of_module_pre_conflict_resolution_post_loading_functions);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_once_only_pre_conflict_resolution_post_loading_functions, Qlist_of_once_only_pre_conflict_resolution_post_loading_functions);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_once_only_switched_post_loading_functions, Qlist_of_once_only_switched_post_loading_functions);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_once_only_post_conflict_resolution_post_loading_functions, Qlist_of_once_only_post_conflict_resolution_post_loading_functions);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_switched_and_module_post_loading_functions, Qlist_of_switched_and_module_post_loading_functions);

Object Verbose_post_loading_p = UNBOUND;

/* SUM-LIST-LENGTHS */
Object sum_list_lengths(lists)
    Object lists;
{
    Object sum, list_1, ab_loop_list_, incf_arg;

    x_note_fn_call(132,3);
    sum = FIX((SI_Long)0L);
    list_1 = Nil;
    ab_loop_list_ = lists;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    list_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    incf_arg = length(SYMBOL_VALUE(list_1));
    sum = add(sum,incf_arg);
    goto next_loop;
  end_loop:;
    return VALUES_1(sum);
}

static Object Kerror_recovery;     /* :error-recovery */

static Object list_constant;       /* # */

static Object Kbefore_conflict_resolution;  /* :before-conflict-resolution */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Kafter_conflict_resolution;  /* :after-conflict-resolution */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object string_constant;     /* "~%Doing ~d ~apost-loading functions...." */

static Object string_constant_1;   /* "ERROR RECOVERY CASE " */

static Object string_constant_2;   /* "" */

static Object string_constant_3;   /* "KB name: \"~a\"" */

static Object string_constant_4;   /* "Module: \"~a\"" */

static Object string_constant_5;   /* "~%*** NOTE: once-only functions ARE enabled. ***" */

static Object string_constant_6;   /* "~%*** NOTE: pre-conflict-resolution post-loading functions only are enabled. ***" */

static Object string_constant_7;   /* "~%*** NOTE: post-conflict-resolution post-loading functions only are enabled. ***" */

static Object string_constant_8;   /* "~%Finished post-loading functions. Elapsed Time: ~d seconds.~%" */

/* DO-POST-LOADING-FUNCTIONS */
Object do_post_loading_functions(type)
    Object type;
{
    Object list_of_lists_of_functions, start_time, end_time;
    Object do_not_note_permanent_changes_p, list_of_functions, ab_loop_list_;
    Object position_1, function, ab_loop_list__1;
    char error_recovery_case;
    Declare_special(1);

    x_note_fn_call(132,4);
    if (EQ(type,Kerror_recovery))
	list_of_lists_of_functions = list_constant;
    else if (EQ(type,Kbefore_conflict_resolution))
	list_of_lists_of_functions = 
		Post_loading_functions_will_be_executed_again_later_qm ? 
		list_constant_1 : 
		Switched_once_only_post_loads_are_after_conflict_resolution 
		? list_constant_2 : list_constant_3;
    else if (EQ(type,Kafter_conflict_resolution))
	list_of_lists_of_functions = 
		Post_loading_functions_will_be_executed_again_later_qm ? 
		Qnil : 
		Switched_once_only_post_loads_are_after_conflict_resolution 
		? list_constant_4 : list_constant_5;
    else
	list_of_lists_of_functions = error((SI_Long)2L,
		"The value of TYPE (~s), is not one of (:ERROR-RECOVERY :BEFORE-CONFLICT-RESOLUTION :AFTER-CONFLICT-RESOLUTION).",
		type);
    error_recovery_case = EQ(type,Kerror_recovery);
    start_time = Nil;
    end_time = Nil;
    if (Verbose_post_loading_p) {
	start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	notify_user_at_console(3,string_constant,
		sum_list_lengths(list_of_lists_of_functions),
		error_recovery_case ? string_constant_1 : string_constant_2);
	if (Reading_kb_p) {
	    notify_user_at_console(2,string_constant_3,
		    Name_text_string_for_kb_being_read);
	    if (Name_of_module_being_read_qm)
		notify_user_at_console(2,string_constant_4,
			Name_of_module_being_read_qm);
	}
	if (error_recovery_case ||  
		!TRUEP(Post_loading_functions_will_be_executed_again_later_qm))
	    notify_user_at_console(1,string_constant_5);
	if (EQ(type,Kbefore_conflict_resolution))
	    notify_user_at_console(1,string_constant_6);
	if (EQ(type,Kafter_conflict_resolution))
	    notify_user_at_console(1,string_constant_7);
    }
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      list_of_functions = Nil;
      ab_loop_list_ = list_of_lists_of_functions;
      position_1 = FIX((SI_Long)1L);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      list_of_functions = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      function = Nil;
      ab_loop_list__1 = SYMBOL_VALUE(list_of_functions);
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      function = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      do_one_post_loading_function(function,position_1);
      position_1 = FIXNUM_ADD1(position_1);
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    if (Verbose_post_loading_p) {
	end_time = c_native_clock_ticks_or_cache(Nil,Nil);
	return notify_user_at_console(2,string_constant_8,
		fixnum_time_difference_in_seconds(end_time,start_time));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_9;   /* "~%(~d) Entering ~a function...." */

static Object string_constant_10;  /* "   !!!!!!!!!!" */

static Object string_constant_11;  /* "     Exiting ~a function.~%     Elapsed Time: ~d seconds~a" */

/* DO-ONE-POST-LOADING-FUNCTION */
Object do_one_post_loading_function(function,position_1)
    Object function, position_1;
{
    Object start_time, end_time, seconds, emphasis_string;

    x_note_fn_call(132,5);
    start_time = Nil;
    end_time = Nil;
    if (Verbose_post_loading_p) {
	start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	notify_user_at_console(3,string_constant_9,position_1,function);
    }
    FUNCALL_0(SYMBOL_FUNCTION(function));
    if (Verbose_post_loading_p) {
	end_time = c_native_clock_ticks_or_cache(Nil,Nil);
	seconds = fixnum_time_difference_in_seconds(end_time,start_time);
	emphasis_string = IFIX(seconds) > (SI_Long)0L ? string_constant_10 
		: string_constant_2;
	return notify_user_at_console(4,string_constant_11,function,
		seconds,emphasis_string);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_serial_number_map, Qframe_serial_number_map);

/* MAKE-FRAME-SERIAL-NUMBER-TO-FRAME-MAP */
Object make_frame_serial_number_to_frame_map()
{
    x_note_fn_call(132,6);
    Frame_serial_number_map = allocate_sparse_array_1();
    return VALUES_1(Frame_serial_number_map);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-MAP */
Object reclaim_frame_serial_number_map()
{
    x_note_fn_call(132,7);
    if (Frame_serial_number_map) {
	reclaim_sparse_array(Frame_serial_number_map);
	Frame_serial_number_map = Nil;
    }
    return VALUES_1(Nil);
}

/* ENTER-FRAME-INTO-FRAME-SERIAL-NUMBER-MAP */
Object enter_frame_into_frame_serial_number_map(frame_serial_number,frame)
    Object frame_serial_number, frame;
{
    x_note_fn_call(132,8);
    return aset_sparse_array(Frame_serial_number_map,frame_serial_number,
	    frame);
}

/* GET-FRAME-GIVEN-FRAME-SERIAL-NUMBER */
Object get_frame_given_frame_serial_number(frame_serial_number)
    Object frame_serial_number;
{
    x_note_fn_call(132,9);
    return aref_sparse_array(Frame_serial_number_map,frame_serial_number);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ignore_kb_flags_in_kbs_qm, Qignore_kb_flags_in_kbs_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Saved_detail_pane_description, Qsaved_detail_pane_description);

DEFINE_VARIABLE_WITH_SYMBOL(Reference_serial_number_for_saved_detail_pane_description, Qreference_serial_number_for_saved_detail_pane_description);

static Object Qkb_workspace;       /* kb-workspace */

static Object Qok;                 /* ok */

/* RESTORE-CURRENT-WORKSTATION-DETAIL-PANE */
Object restore_current_workstation_detail_pane varargs_1(int, n)
{
    Object clear_image_planes_of_other_kb_workspaces_qm, redisplay_logbook_qm;
    Object specific_module_qm, ok_workspace_qm, image_plane, ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(132,10);
    INIT_ARGS_nonrelocating();
    clear_image_planes_of_other_kb_workspaces_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    redisplay_logbook_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    specific_module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(inhibit_restore_detail_pane_p(Current_workstation_window))) {
	restore_image_planes_to_pane(6,Current_workstation_detail_pane,
		Saved_detail_pane_description,
		Reference_serial_number_for_saved_detail_pane_description,
		T,clear_image_planes_of_other_kb_workspaces_qm,
		specific_module_qm);
	if (redisplay_logbook_qm)
	    redisplay_logbook_in_current_workstation();
	if ( ! !EQ(Unevaluated_expression,Within_side_limits)) {
	    ok_workspace_qm = get_instance_with_name_if_any(Qkb_workspace,Qok);
	    if (ok_workspace_qm) {
		image_plane = Nil;
		ab_loop_list_ = ISVREF(ok_workspace_qm,(SI_Long)16L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		image_plane = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		raise_image_plane_to_top(1,image_plane);
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Refresh_all_windows_after_merging_qm, Qrefresh_all_windows_after_merging_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Reformat_as_appropriate_qm, Qreformat_as_appropriate_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Frames_with_substitute_classes, Qframes_with_substitute_classes);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_object_index_space, Qkb_object_index_space);

DEFINE_VARIABLE_WITH_SYMBOL(Next_character_for_kb_qm, Qnext_character_for_kb_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Read_kb_buffer, Qread_kb_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Read_kb_buffer_index, Qread_kb_buffer_index);

DEFINE_VARIABLE_WITH_SYMBOL(Read_kb_buffer_length, Qread_kb_buffer_length);

DEFINE_VARIABLE_WITH_SYMBOL(Read_kb_stream, Qread_kb_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Basis_kb_frame_serial_number, Qbasis_kb_frame_serial_number);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_format_identifier_read_qm, Qkb_format_identifier_read_qm);

/* READ-NEXT-CHAR-FOR-KB-FROM-REFILLED-BUFFER */
Object read_next_char_for_kb_from_refilled_buffer()
{
    Object incff_1_arg, number_of_kb_characters_so_far_qm_new_value;
    Object number_of_characters_in_buffer_qm, temp;

    x_note_fn_call(132,11);
    if (Number_of_kb_characters_so_far_qm) {
	incff_1_arg = Read_kb_buffer_index;
	number_of_kb_characters_so_far_qm_new_value = 
		FIXNUM_ADD(Number_of_kb_characters_so_far_qm,incff_1_arg);
	Number_of_kb_characters_so_far_qm = 
		number_of_kb_characters_so_far_qm_new_value;
    }
    number_of_characters_in_buffer_qm = 
	    g2_stream_read_into_buffer(Read_kb_buffer,
	    SIMPLE_ARRAY_ANY_1_LENGTH(Read_kb_buffer),Read_kb_stream);
    if (number_of_characters_in_buffer_qm && 
	    FIXNUM_PLUSP(number_of_characters_in_buffer_qm)) {
	Read_kb_buffer_length = number_of_characters_in_buffer_qm;
	Read_kb_buffer_index = FIX((SI_Long)1L);
	temp = SCHAR(Read_kb_buffer,FIX((SI_Long)0L));
    }
    else if (Plist_has_been_checked_p) {
	Read_kb_buffer_index = Nil;
	temp = Nil;
    }
    else if ( !TRUEP(Kb_format_identifier_read_qm))
	temp = CHR('Z');
    else
	temp = abort_on_bad_kb(0);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Newline_characters, Qnewline_characters);

/* READ-CHAR-FOR-KB-PAST-NEWLINE */
Object read_char_for_kb_past_newline()
{
    Object temp, read_kb_buffer_index_new_value, character_1, next_character;

    x_note_fn_call(132,12);
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    temp = CHAR_EQ(character_1,CHR('\n')) ? T : Nil;
    if (temp);
    else if (CHAR_EQ(character_1,CHR('\r'))) {
	Kb_uses_crlf_p = T;
	temp = T;
    }
    else {
	temp = CHAR_EQ(character_1,CHR('\f')) ? T : Nil;
	if (temp);
	else
	    temp = Qnil;
    }
    if (temp) {
	update_file_progress_display_for_newline_in_kb(0);
	next_character = Nil;
      next_loop:
	if ( !TRUEP(Read_kb_buffer_index))
	    next_character = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    next_character = temp;
	}
	else
	    next_character = read_next_char_for_kb_from_refilled_buffer();
	temp = CHAR_EQ(next_character,CHR('\n')) ? T : Nil;
	if (temp);
	else if (CHAR_EQ(next_character,CHR('\r'))) {
	    Kb_uses_crlf_p = T;
	    temp = T;
	}
	else {
	    temp = CHAR_EQ(next_character,CHR('\f')) ? T : Nil;
	    if (temp);
	    else
		temp = Qnil;
	}
	if ( !TRUEP(temp)) {
	    temp = next_character;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = character_1;
    return VALUES_1(temp);
}

Object Ignore_process_newline = UNBOUND;

/* READ-CHAR-FOR-KB-PAST-SPACES */
Object read_char_for_kb_past_spaces()
{
    Object temp, temp_1, character_1;

    x_note_fn_call(132,13);
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_1;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
  next_loop:
    if ( !CHAR_EQ(character_1,CHR(' ')) &&  !CHAR_EQ(character_1,
	    CHR('\t')) &&  !CHAR_EQ(character_1,CHR(';'))) {
	temp = CHAR_EQ(character_1,CHR('\n')) ? T : Nil;
	if (temp);
	else if (CHAR_EQ(character_1,CHR('\r'))) {
	    Kb_uses_crlf_p = T;
	    temp = T;
	}
	else {
	    temp = CHAR_EQ(character_1,CHR('\f')) ? T : Nil;
	    if (temp);
	    else
		temp = Qnil;
	}
	if (temp) {
	    if (IFIX(Ignore_process_newline) == (SI_Long)50000L) {
		Ignore_process_newline = FIX((SI_Long)0L);
		update_file_progress_display_for_newline_in_kb(0);
	    }
	    temp_1 = FIXNUM_ADD1(Ignore_process_newline);
	    Ignore_process_newline = temp_1;
	    temp_1 = FIXNUM_ADD1(Number_of_kb_lines_so_far);
	    Number_of_kb_lines_so_far = temp_1;
	}
	else {
	    temp = character_1;
	    goto end_1;
	}
    }
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_1;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* UPDATE-FILE-PROGRESS-DISPLAY-FOR-NEWLINE-IN-KB */
Object update_file_progress_display_for_newline_in_kb varargs_1(int, n)
{
    Object force_update_p, number_of_kb_lines_so_far_new_value;
    Object suppress_updating_of_slot_value_representations_qm;
    SI_Long temp_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,14);
    INIT_ARGS_nonrelocating();
    force_update_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Kb_file_progress) {
	temp = TRUEP(force_update_p);
	if (temp);
	else {
	    number_of_kb_lines_so_far_new_value = 
		    FIXNUM_ADD1(Number_of_kb_lines_so_far);
	    Number_of_kb_lines_so_far = number_of_kb_lines_so_far_new_value;
	    temp_1 = IFIX(Number_of_kb_lines_so_far) % (SI_Long)50L;
	    temp = temp_1 == (SI_Long)0L;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	suppress_updating_of_slot_value_representations_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
		0);
	  result = update_file_progress_display(3,Kb_file_progress,
		  Number_of_kb_lines_so_far,force_update_p);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* READ-PAST-BINARY-WORD-FOR-KB */
Object read_past_binary_word_for_kb(print_qm)
    Object print_qm;
{
    Object character_1, temp, read_kb_buffer_index_new_value;
    SI_Long i;

    x_note_fn_call(132,15);
    i = (SI_Long)1L;
    character_1 = Nil;
  next_loop:
    if (i > (SI_Long)5L)
	goto end_loop;
    if (i == (SI_Long)1L)
	character_1 = read_char_for_kb_past_newline();
    else if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    if (print_qm)
	format((SI_Long)3L,T,"~c",character_1);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (print_qm)
	format((SI_Long)2L,T," ");
    return VALUES_1(Nil);
}

static Object Qab_slot_value;      /* slot-value */

/* READ-LIST-ELEMENT-FOR-KB */
Object read_list_element_for_kb()
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol, l;
    Object l_tail, character_1, temp_1;

    x_note_fn_call(132,16);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp = read_element_for_kb(Nil);
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    l = gensymed_symbol;
    l_tail = l;
    character_1 = Nil;
  next_loop:
    character_1 = read_char_for_kb_past_spaces();
    temp_1 = CHAR_CODE(character_1);
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
	    FIX((SI_Long)127L)))) {
	temp = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp = read_element_for_kb(Nil);
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	l_tail = M_CDR(l_tail) = gensymed_symbol;
    }
    else
	switch (INTEGER_TO_CHAR(temp_1)) {
	  case 82:
	    temp_1 = l;
	    goto end_1;
	    break;
	  case 46:
	    temp = read_element_for_kb(Nil);
	    M_CDR(l_tail) = temp;
	    temp_1 = l;
	    goto end_1;
	    break;
	  default:
	    temp = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = temp;
	    new_cons = ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_slot_value_cons_pool();
	    temp = read_element_for_kb(Nil);
	    M_CAR(gensymed_symbol) = temp;
	    M_CDR(gensymed_symbol) = Nil;
	    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	    l_tail = M_CDR(l_tail) = gensymed_symbol;
	    break;
	}
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* READ-PAST-LIST-ELEMENT-FOR-KB */
Object read_past_list_element_for_kb(print_qm)
    Object print_qm;
{
    Object character_1, temp, read_kb_buffer_index_new_value;

    x_note_fn_call(132,17);
    read_past_element_for_kb(print_qm);
    character_1 = Nil;
  next_loop:
    character_1 = read_char_for_kb_past_spaces();
    temp = CHAR_CODE(character_1);
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	read_past_element_for_kb(print_qm);
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 82:
	    goto end_1;
	    break;
	  case 46:
	    if (print_qm)
		format((SI_Long)2L,T,"~%; Final dotted element: ~%");
	    read_past_element_for_kb(print_qm);
	    goto end_1;
	    break;
	  default:
	    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    read_past_element_for_kb(print_qm);
	    break;
	}
    goto next_loop;
  end_loop:
  end_1:;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Base_reference, Qbase_reference);

/* READ-UNENCRYPTED-CHARACTER-SEQUENCE-INTO-SIMPLE-GENSYM-STRING */
Object read_unencrypted_character_sequence_into_simple_gensym_string(number_of_characters,
	    simple_gensym_string)
    Object number_of_characters, simple_gensym_string;
{
    Object read_kb_buffer_index_new_value;
    SI_Long character_index;
    char character_1, temp;

    x_note_fn_call(132,18);
    character_1 = 'a';
    character_index = (SI_Long)0L;
  next_loop:
    if ( !(character_index < IFIX(number_of_characters)))
	goto end_loop;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = CHARACTER_TO_CHAR(SCHAR(Read_kb_buffer,Read_kb_buffer_index));
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = 
		CHARACTER_TO_CHAR(read_next_char_for_kb_from_refilled_buffer());
    if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\\')) && 
	    check_slash_extension_for_character_sequence(character_index + 
	    (SI_Long)1L == IFIX(number_of_characters) ? T : Nil));
    else {
	SET_ISCHAR(simple_gensym_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* READ-UNENCRYPTED-CHARACTER-SEQUENCE-INTO-WIDE-STRING */
Object read_unencrypted_character_sequence_into_wide_string(number_of_characters,
	    wide_string)
    Object number_of_characters, wide_string;
{
    Object complex_p, chrr, temp, read_kb_buffer_index_new_value;
    SI_Long character_1, character_index;

    x_note_fn_call(132,19);
    character_1 = (SI_Long)97L;
    character_index = (SI_Long)0L;
    complex_p = Nil;
    chrr = Nil;
  next_loop:
    if ( !(character_index < IFIX(number_of_characters)))
	goto end_loop;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	chrr = temp;
    }
    else
	chrr = read_next_char_for_kb_from_refilled_buffer();
    character_1 = IFIX(CHAR_CODE(chrr));
    if (character_1 == (SI_Long)92L && 
	    check_slash_extension_for_character_sequence(character_index + 
	    (SI_Long)1L == IFIX(number_of_characters) ? T : Nil));
    else {
	if ( !TRUEP(complex_p)) {
	    temp = character_1 == (SI_Long)126L ? T : Nil;
	    if (temp);
	    else
		temp = character_1 == (SI_Long)64L ? T : Nil;
	    if (temp);
	    else
		temp = character_1 == (SI_Long)92L ? T : Nil;
	    complex_p = temp;
	}
	UBYTE_16_ISASET_1(wide_string,character_index,character_1);
	character_index = character_index + (SI_Long)1L;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(complex_p);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* READ-CHARACTER-SEQUENCE-AS-TEXT-STRING */
Object read_character_sequence_as_text_string(number_of_characters_init,
	    decrypt_qm)
    Object number_of_characters_init, decrypt_qm;
{
    Object wide_string_bv16, wide_string, complex_p, chrr, temp, temp_1;
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_or_character_code, escape_character_qm;
    Object current_extended_utf_g_low_half_character_qm, row;
    Object simple_or_wide_character, thing, schar_arg_2, schar_new_value;
    SI_Long number_of_characters, bv16_length, aref_arg_2, aref_new_value;
    SI_Long local_base_reference, character_1, character_index, result_code;
    SI_Long length_1, end_1, i, gensym_character_code, temp_3, wide_character;
    SI_Long code, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, unicode_full_row;
    char temp_2;
    Declare_special(7);

    x_note_fn_call(132,20);
    number_of_characters = IFIX(number_of_characters_init);
    if (IFIX(Kb_flags) >= (SI_Long)238L) {
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(number_of_characters + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = number_of_characters & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | number_of_characters >>  -  - 
		(SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,number_of_characters,(SI_Long)0L);
	wide_string = wide_string_bv16;
	if (decrypt_qm) {
	    local_base_reference = IFIX(Standard_base_reference);
	    character_1 = (SI_Long)97L;
	    character_index = (SI_Long)0L;
	    complex_p = Nil;
	    chrr = Nil;
	  next_loop:
	    if ( !(character_index < number_of_characters))
		goto end_loop;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
		chrr = temp;
	    }
	    else
		chrr = read_next_char_for_kb_from_refilled_buffer();
	    result_code = IFIX(CHAR_CODE(chrr));
	    if (result_code != (SI_Long)92L && (SI_Long)32L <= result_code 
		    && result_code <= (SI_Long)126L) {
		local_base_reference = 
			g2ext_eval_base_ref_val(local_base_reference);
		result_code = 
			g2ext_characters_cipher(IFIX(CHAR_CODE(chrr)),
			local_base_reference,T ? (SI_Long)1L : (SI_Long)0L);
	    }
	    character_1 = result_code;
	    if (character_1 == (SI_Long)92L && 
		    check_slash_extension_for_character_sequence(character_index 
		    + (SI_Long)1L == number_of_characters ? T : Nil));
	    else {
		if ( !TRUEP(complex_p)) {
		    temp = character_1 == (SI_Long)126L ? T : Nil;
		    if (temp);
		    else
			temp = character_1 == (SI_Long)64L ? T : Nil;
		    if (temp);
		    else
			temp = character_1 == (SI_Long)92L ? T : Nil;
		    complex_p = temp;
		}
		UBYTE_16_ISASET_1(wide_string,character_index,character_1);
		character_index = character_index + (SI_Long)1L;
	    }
	    goto next_loop;
	  end_loop:;
	    temp_2 = TRUEP(complex_p);
	}
	else
	    temp_2 = 
		    TRUEP(read_unencrypted_character_sequence_into_wide_string(FIX(number_of_characters),
		    wide_string));
	if (temp_2) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    6);
	      wide_string_bv16 = 
		      allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
		      5);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			4);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  3);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    2);
		      temp = FIX(number_of_characters);
		      if (temp);
		      else {
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
			  temp = FIX(UBYTE_16_ISAREF_1(wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(wide_string,length_1 
				  - (SI_Long)1L) & (SI_Long)8191L) << 
				  (SI_Long)16L));
		      }
		      end_1 = IFIX(temp);
		      i = (SI_Long)0L;
		      character_or_character_code = Nil;
		      escape_character_qm = Nil;
		      gensym_character_code = (SI_Long)0L;
		    next_loop_1:
		      if ( !(i < end_1))
			  goto end_loop_1;
		      temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
		      i = i + (SI_Long)1L;
		      wide_character = temp_3;
		      temp_3 = wide_character;
		      if ( !((SI_Long)-128L <= temp_3 && temp_3 <= 
			      (SI_Long)127L)) {
			  escape_character_qm = Nil;
			  character_or_character_code = 
				  CODE_CHAR(FIX(wide_character));
		      }
		      else
			  switch ((char)temp_3) {
			    case 64:
			    case 126:
			      escape_character_qm = 
				      CODE_CHAR(FIX(wide_character));
			      temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
			      i = i + (SI_Long)1L;
			      character_or_character_code = 
				      CODE_CHAR(FIX(temp_3));
			      break;
			    case 92:
			      escape_character_qm = 
				      CODE_CHAR(FIX(wide_character));
			      temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
			      i = i + (SI_Long)1L;
			      code = temp_3;
			      if (code < (SI_Long)40L) {
				  gensymed_symbol = code << (SI_Long)13L;
				  gensymed_symbol_1 = (SI_Long)95L;
				  temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
				  i = i + (SI_Long)1L;
				  gensymed_symbol_2 = temp_3;
				  gensymed_symbol_1 = gensymed_symbol_1 * 
					  gensymed_symbol_2;
				  temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
				  i = i + (SI_Long)1L;
				  gensymed_symbol_2 = temp_3;
				  gensymed_symbol_3 = (SI_Long)-265976L;
				  character_or_character_code = 
					  FIX(gensymed_symbol + 
					  gensymed_symbol_1 + 
					  gensymed_symbol_2 + 
					  gensymed_symbol_3);
			      }
			      else {
				  gensymed_symbol = (SI_Long)95L * code;
				  temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
				  i = i + (SI_Long)1L;
				  gensymed_symbol_1 = temp_3;
				  gensymed_symbol_2 = (SI_Long)4360L;
				  character_or_character_code = 
					  FIX(gensymed_symbol + 
					  gensymed_symbol_1 + 
					  gensymed_symbol_2);
			      }
			      break;
			    default:
			      escape_character_qm = Nil;
			      character_or_character_code = 
				      CODE_CHAR(FIX(wide_character));
			      break;
			  }
		      if ( !TRUEP(escape_character_qm))
			  gensym_character_code = 
				  IFIX(CHAR_CODE(character_or_character_code));
		      else {
			  if (CHAR_EQ(escape_character_qm,CHR('~'))) {
			      temp = 
				      ISVREF(Reverse_iso_latin1_special_character_code_map,
				      IFIX(CHAR_CODE(character_or_character_code)));
			      if (temp);
			      else {
				  temp = 
					  CHAR_CODE(character_or_character_code);
				  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),
					  temp) && FIXNUM_LE(temp,
					  FIX((SI_Long)127L))))
				      temp = Nil;
				  else
				      switch (INTEGER_TO_CHAR(temp)) {
					case 87:
					  temp = 
						  Gensym_code_for_capital_ligature_oe;
					  break;
					case 119:
					  temp = 
						  Gensym_code_for_small_ligature_oe;
					  break;
					case 42:
					  temp = Gensym_code_for_bullet;
					  break;
					case 38:
					  temp = 
						  Gensym_code_for_small_letter_f_with_hook;
					  break;
					case 58:
					  temp = 
						  Gensym_code_for_trade_mark_sign;
					  break;
					default:
					  temp = Nil;
					  break;
				      }
			      }
			      gensym_character_code = IFIX(temp);
			  }
			  else
			      gensym_character_code = IFIX(Nil);
			  if (gensym_character_code);
			  else if ( !TRUEP(escape_character_qm) &&  
				  !TRUEP(Gensym_esc_for_linebreak_qm) ? 
				  CHAR_EQ(character_or_character_code,
				  Gensym_char_or_code_for_linebreak) : 
				  EQL(character_or_character_code,
				  Gensym_char_or_code_for_linebreak) && 
				  EQL(escape_character_qm,
				  Gensym_esc_for_linebreak_qm))
			      gensym_character_code = 
				      IFIX(Gensym_code_for_linebreak);
			  else if ( !TRUEP(escape_character_qm) &&  
				  !TRUEP(Gensym_esc_for_paragraph_break_qm) 
				  ? CHAR_EQ(character_or_character_code,
				  Gensym_char_or_code_for_paragraph_break) 
				  : EQL(character_or_character_code,
				  Gensym_char_or_code_for_paragraph_break) 
				  && EQL(escape_character_qm,
				  Gensym_esc_for_paragraph_break_qm))
			      gensym_character_code = 
				      IFIX(Gensym_code_for_paragraph_break);
			  else {
			      gensym_character_code =  
				      !EQ(escape_character_qm,CHR('\\')) ? 
				      (SI_Long)65535L : IFIX(Nil);
			      if (gensym_character_code);
			      else
				  gensym_character_code = 
					  IFIX(character_or_character_code);
			  }
		      }
		      if (gensym_character_code >>  -  - (SI_Long)8L == 
			      (SI_Long)247L) {
			  current_extended_utf_g_low_half_character_qm = 
				  FIX(gensym_character_code);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_extended_utf_g_low_half_character_qm,Qcurrent_extended_utf_g_low_half_character_qm,current_extended_utf_g_low_half_character_qm,
				  1);
			    if (i < end_1) {
				temp_3 = UBYTE_16_ISAREF_1(wide_string,i);
				i = i + (SI_Long)1L;
				wide_character = temp_3;
				temp_3 = wide_character;
				if ( !((SI_Long)-128L <= temp_3 && temp_3 
					<= (SI_Long)127L)) {
				    escape_character_qm = Nil;
				    character_or_character_code = 
					    CODE_CHAR(FIX(wide_character));
				}
				else
				    switch ((char)temp_3) {
				      case 64:
				      case 126:
					escape_character_qm = 
						CODE_CHAR(FIX(wide_character));
					temp_3 = 
						UBYTE_16_ISAREF_1(wide_string,
						i);
					i = i + (SI_Long)1L;
					character_or_character_code = 
						CODE_CHAR(FIX(temp_3));
					break;
				      case 92:
					escape_character_qm = 
						CODE_CHAR(FIX(wide_character));
					temp_3 = 
						UBYTE_16_ISAREF_1(wide_string,
						i);
					i = i + (SI_Long)1L;
					code = temp_3;
					if (code < (SI_Long)40L) {
					    gensymed_symbol = code << 
						    (SI_Long)13L;
					    gensymed_symbol_1 = (SI_Long)95L;
					    temp_3 = 
						    UBYTE_16_ISAREF_1(wide_string,
						    i);
					    i = i + (SI_Long)1L;
					    gensymed_symbol_2 = temp_3;
					    gensymed_symbol_1 = 
						    gensymed_symbol_1 * 
						    gensymed_symbol_2;
					    temp_3 = 
						    UBYTE_16_ISAREF_1(wide_string,
						    i);
					    i = i + (SI_Long)1L;
					    gensymed_symbol_2 = temp_3;
					    gensymed_symbol_3 = 
						    (SI_Long)-265976L;
					    character_or_character_code = 
						    FIX(gensymed_symbol + 
						    gensymed_symbol_1 + 
						    gensymed_symbol_2 + 
						    gensymed_symbol_3);
					}
					else {
					    gensymed_symbol = (SI_Long)95L 
						    * code;
					    temp_3 = 
						    UBYTE_16_ISAREF_1(wide_string,
						    i);
					    i = i + (SI_Long)1L;
					    gensymed_symbol_1 = temp_3;
					    gensymed_symbol_2 = (SI_Long)4360L;
					    character_or_character_code = 
						    FIX(gensymed_symbol + 
						    gensymed_symbol_1 + 
						    gensymed_symbol_2);
					}
					break;
				      default:
					escape_character_qm = Nil;
					character_or_character_code = 
						CODE_CHAR(FIX(wide_character));
					break;
				    }
				if ( !TRUEP(escape_character_qm))
				    gensym_character_code = 
					    IFIX(CHAR_CODE(character_or_character_code));
				else {
				    if (CHAR_EQ(escape_character_qm,
						CHR('~'))) {
					temp = 
						ISVREF(Reverse_iso_latin1_special_character_code_map,
						IFIX(CHAR_CODE(character_or_character_code)));
					if (temp);
					else {
					    temp = 
						    CHAR_CODE(character_or_character_code);
					    if ( 
						    !(FIXNUM_LE(FIX((SI_Long)-128L),
						    temp) && 
						    FIXNUM_LE(temp,
						    FIX((SI_Long)127L))))
						temp = Nil;
					    else
						switch (INTEGER_TO_CHAR(temp)) 
							    {
						  case 87:
						    temp = 
							    Gensym_code_for_capital_ligature_oe;
						    break;
						  case 119:
						    temp = 
							    Gensym_code_for_small_ligature_oe;
						    break;
						  case 42:
						    temp = 
							    Gensym_code_for_bullet;
						    break;
						  case 38:
						    temp = 
							    Gensym_code_for_small_letter_f_with_hook;
						    break;
						  case 58:
						    temp = 
							    Gensym_code_for_trade_mark_sign;
						    break;
						  default:
						    temp = Nil;
						    break;
						}
					}
					gensym_character_code = IFIX(temp);
				    }
				    else
					gensym_character_code = IFIX(Nil);
				    if (gensym_character_code);
				    else if ( !TRUEP(escape_character_qm) 
					    &&  
					    !TRUEP(Gensym_esc_for_linebreak_qm) 
					    ? 
					    CHAR_EQ(character_or_character_code,
					    Gensym_char_or_code_for_linebreak) 
					    : 
					    EQL(character_or_character_code,
					    Gensym_char_or_code_for_linebreak) 
					    && EQL(escape_character_qm,
					    Gensym_esc_for_linebreak_qm))
					gensym_character_code = 
						IFIX(Gensym_code_for_linebreak);
				    else if ( !TRUEP(escape_character_qm) 
					    &&  
					    !TRUEP(Gensym_esc_for_paragraph_break_qm) 
					    ? 
					    CHAR_EQ(character_or_character_code,
					    Gensym_char_or_code_for_paragraph_break) 
					    : 
					    EQL(character_or_character_code,
					    Gensym_char_or_code_for_paragraph_break) 
					    && EQL(escape_character_qm,
					    Gensym_esc_for_paragraph_break_qm))
					gensym_character_code = 
						IFIX(Gensym_code_for_paragraph_break);
				    else {
					gensym_character_code =  
						!EQ(escape_character_qm,
						CHR('\\')) ? 
						(SI_Long)65535L : IFIX(Nil);
					if (gensym_character_code);
					else
					    gensym_character_code = 
						    IFIX(character_or_character_code);
				    }
				}
				if (gensym_character_code >>  -  - 
					(SI_Long)8L == (SI_Long)248L) {
				    temp_2 = gensym_character_code < 
					    (SI_Long)256L ? 
					    TRUEP(ISVREF(Iso_latin1_special_character_code_map,
					    gensym_character_code)) : 
					    TRUEP(Nil);
				    if (temp_2);
				    else if (gensym_character_code == 
					    IFIX(Gensym_code_for_capital_ligature_oe))
					temp_2 = 'W';
				    else if (gensym_character_code == 
					    IFIX(Gensym_code_for_small_ligature_oe))
					temp_2 = 'w';
				    else if (gensym_character_code == 
					    IFIX(Gensym_code_for_bullet))
					temp_2 = '*';
				    else if (gensym_character_code == 
					    IFIX(Gensym_code_for_small_letter_f_with_hook))
					temp_2 = '&';
				    else if (gensym_character_code == 
					    IFIX(Gensym_code_for_trade_mark_sign))
					temp_2 = ':';
				    else
					temp_2 = TRUEP(Qnil);
				    if (temp_2) {
					row = FIX(gensym_character_code >> 
						 -  - (SI_Long)8L);
					PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,
						0);
					  unicode_full_row = 
						  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
						  IFIX(Row));
					  if ( !(unicode_full_row == 
						  IFIX(Invalid_unicode_full_row))) 
						      {
					      gensymed_symbol = 
						      unicode_full_row << 
						      (SI_Long)8L;
					      gensymed_symbol_1 = 
						      (SI_Long)255L & 
						      gensym_character_code;
					      simple_or_wide_character = 
						      FIX(gensymed_symbol 
						      + gensymed_symbol_1);
					  }
					  else
					      simple_or_wide_character = Nil;
					POP_SPECIAL();
				    }
				    else if ((SI_Long)8192L <= 
					    gensym_character_code && 
					    gensym_character_code <= 
					    (SI_Long)8447L) {
					row = FIX(gensym_character_code >> 
						 -  - (SI_Long)8L);
					PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,
						0);
					  unicode_full_row = 
						  UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
						  IFIX(Row));
					  if ( !(unicode_full_row == 
						  IFIX(Invalid_unicode_full_row))) 
						      {
					      gensymed_symbol = 
						      unicode_full_row << 
						      (SI_Long)8L;
					      gensymed_symbol_1 = 
						      (SI_Long)255L & 
						      gensym_character_code;
					      simple_or_wide_character = 
						      FIX(gensymed_symbol 
						      + gensymed_symbol_1);
					  }
					  else
					      simple_or_wide_character = Nil;
					POP_SPECIAL();
				    }
				    else {
					simple_or_wide_character = 
						map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
					if (simple_or_wide_character);
					else {
					    row = 
						    FIX(gensym_character_code 
						    >>  -  - (SI_Long)8L);
					    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,
						    0);
					      unicode_full_row = 
						      UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
						      IFIX(Row));
					      if ( !(unicode_full_row == 
						      IFIX(Invalid_unicode_full_row))) 
							  {
						  gensymed_symbol = 
							  unicode_full_row 
							  << (SI_Long)8L;
						  gensymed_symbol_1 = 
							  (SI_Long)255L & 
							  gensym_character_code;
						  simple_or_wide_character 
							  = 
							  FIX(gensymed_symbol 
							  + gensymed_symbol_1);
					      }
					      else
						  simple_or_wide_character 
							  = Nil;
					    POP_SPECIAL();
					    if (simple_or_wide_character);
					    else if (Current_extended_utf_g_low_half_character_qm)
						simple_or_wide_character = 
							map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
							FIX(gensym_character_code));
					    else
						simple_or_wide_character = 
							FIX((SI_Long)65535L);
					}
				    }
				    if (EQ(Current_twriting_output_type,
					    Qwide_string)) {
					thing = simple_or_wide_character;
					twrite_wide_character(CHARACTERP(thing) 
						? CHAR_CODE(thing) : thing);
				    }
				    else {
					if ( 
						!FIXNUM_LT(Fill_pointer_for_current_gensym_string,
						Total_length_of_current_gensym_string))
					    extend_current_gensym_string(0);
					temp_1 = Current_gensym_string;
					schar_arg_2 = 
						Fill_pointer_for_current_gensym_string;
					thing = simple_or_wide_character;
					schar_new_value = 
						CODE_CHAR(CHARACTERP(thing) 
						? CHAR_CODE(thing) : thing);
					SET_SCHAR(temp_1,schar_arg_2,
						schar_new_value);
					temp_1 = 
						FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
					Fill_pointer_for_current_gensym_string 
						= temp_1;
				    }
				}
			    }
			  POP_SPECIAL();
		      }
		      else {
			  temp_2 = gensym_character_code < (SI_Long)256L ? 
				  TRUEP(ISVREF(Iso_latin1_special_character_code_map,
				  gensym_character_code)) : TRUEP(Nil);
			  if (temp_2);
			  else if (gensym_character_code == 
				  IFIX(Gensym_code_for_capital_ligature_oe))
			      temp_2 = 'W';
			  else if (gensym_character_code == 
				  IFIX(Gensym_code_for_small_ligature_oe))
			      temp_2 = 'w';
			  else if (gensym_character_code == 
				  IFIX(Gensym_code_for_bullet))
			      temp_2 = '*';
			  else if (gensym_character_code == 
				  IFIX(Gensym_code_for_small_letter_f_with_hook))
			      temp_2 = '&';
			  else if (gensym_character_code == 
				  IFIX(Gensym_code_for_trade_mark_sign))
			      temp_2 = ':';
			  else
			      temp_2 = TRUEP(Qnil);
			  if (temp_2) {
			      row = FIX(gensym_character_code >>  -  - 
				      (SI_Long)8L);
			      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				unicode_full_row = 
					UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					IFIX(Row));
				if ( !(unicode_full_row == 
					IFIX(Invalid_unicode_full_row))) {
				    gensymed_symbol = unicode_full_row << 
					    (SI_Long)8L;
				    gensymed_symbol_1 = (SI_Long)255L & 
					    gensym_character_code;
				    simple_or_wide_character = 
					    FIX(gensymed_symbol + 
					    gensymed_symbol_1);
				}
				else
				    simple_or_wide_character = Nil;
			      POP_SPECIAL();
			  }
			  else if ((SI_Long)8192L <= gensym_character_code 
				  && gensym_character_code <= (SI_Long)8447L) {
			      row = FIX(gensym_character_code >>  -  - 
				      (SI_Long)8L);
			      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				unicode_full_row = 
					UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					IFIX(Row));
				if ( !(unicode_full_row == 
					IFIX(Invalid_unicode_full_row))) {
				    gensymed_symbol = unicode_full_row << 
					    (SI_Long)8L;
				    gensymed_symbol_1 = (SI_Long)255L & 
					    gensym_character_code;
				    simple_or_wide_character = 
					    FIX(gensymed_symbol + 
					    gensymed_symbol_1);
				}
				else
				    simple_or_wide_character = Nil;
			      POP_SPECIAL();
			  }
			  else {
			      simple_or_wide_character = 
				      map_gensym_han_character_code_to_unicode(FIX(gensym_character_code));
			      if (simple_or_wide_character);
			      else {
				  row = FIX(gensym_character_code >>  -  - 
					  (SI_Long)8L);
				  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
				    unicode_full_row = 
					    UBYTE_8_ISAREF_1(Gensym_to_unicode_full_row_map,
					    IFIX(Row));
				    if ( !(unicode_full_row == 
					    IFIX(Invalid_unicode_full_row))) {
					gensymed_symbol = unicode_full_row 
						<< (SI_Long)8L;
					gensymed_symbol_1 = (SI_Long)255L 
						& gensym_character_code;
					simple_or_wide_character = 
						FIX(gensymed_symbol + 
						gensymed_symbol_1);
				    }
				    else
					simple_or_wide_character = Nil;
				  POP_SPECIAL();
				  if (simple_or_wide_character);
				  else if (Current_extended_utf_g_low_half_character_qm)
				      simple_or_wide_character = 
					      map_extended_utf_g_characters_to_unicode(Current_extended_utf_g_low_half_character_qm,
					      FIX(gensym_character_code));
				  else
				      simple_or_wide_character = 
					      FIX((SI_Long)65535L);
			      }
			  }
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = simple_or_wide_character;
			      twrite_wide_character(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp_1 = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = simple_or_wide_character;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			      temp_1 = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp_1;
			  }
		      }
		      goto next_loop_1;
		    end_loop_1:;
		      reclaim_wide_string(wide_string);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = wide_string;
    }
    else
	temp =  !(IFIX(Kb_flags) >= (SI_Long)1L) ||  !(IFIX(Kb_flags) >= 
		(SI_Long)32L) ? 
		read_character_sequence_as_text_string_old_way(FIX(number_of_characters),
		decrypt_qm) : 
		read_character_sequence_as_text_string_for_any_recent_version(FIX(number_of_characters),
		decrypt_qm);
    return VALUES_1(temp);
}

/* READ-CHARACTER-SEQUENCE-AS-SYMBOL */
Object read_character_sequence_as_symbol(number_of_characters_init,
	    decrypt_qm,package)
    Object number_of_characters_init, decrypt_qm, package;
{
    Object simple_gensym_string, temp, read_kb_buffer_index_new_value, char_1;
    SI_Long number_of_characters, local_base_reference, character_index, code;
    SI_Long result_code;
    char character_1;

    x_note_fn_call(132,21);
    number_of_characters = IFIX(number_of_characters_init);
    if (IFIX(Kb_flags) >= (SI_Long)238L) {
	simple_gensym_string = 
		obtain_simple_gensym_string(FIX(number_of_characters));
	if (decrypt_qm) {
	    local_base_reference = IFIX(Standard_base_reference);
	    character_1 = 'a';
	    character_index = (SI_Long)0L;
	  next_loop:
	    if ( !(character_index < number_of_characters))
		goto end_loop;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		char_1 = temp;
	    }
	    else
		char_1 = read_next_char_for_kb_from_refilled_buffer();
	    code = IFIX(CHAR_CODE(char_1));
	    result_code = code;
	    if (result_code != (SI_Long)92L && (SI_Long)32L <= result_code 
		    && result_code <= (SI_Long)126L) {
		local_base_reference = 
			g2ext_eval_base_ref_val(local_base_reference);
		result_code = g2ext_characters_cipher(code,
			local_base_reference,T ? (SI_Long)1L : (SI_Long)0L);
	    }
	    code = result_code;
	    character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(code)));
	    if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\\')) && 
		    check_slash_extension_for_character_sequence(character_index 
		    + (SI_Long)1L == number_of_characters ? T : Nil));
	    else {
		SET_ISCHAR(simple_gensym_string,character_index,character_1);
		character_index = character_index + (SI_Long)1L;
	    }
	    goto next_loop;
	  end_loop:;
	}
	else
	    read_unencrypted_character_sequence_into_simple_gensym_string(FIX(number_of_characters),
		    simple_gensym_string);
	temp = intern_gensym_string(2,simple_gensym_string,package);
    }
    else
	temp =  !(IFIX(Kb_flags) >= (SI_Long)1L) ||  !(IFIX(Kb_flags) >= 
		(SI_Long)32L) ? intern_text_string(2,
		read_character_sequence_as_text_string_old_way(FIX(number_of_characters),
		decrypt_qm),package) : intern_text_string(2,
		read_character_sequence_as_text_string_for_any_recent_version(FIX(number_of_characters),
		decrypt_qm),package);
    return VALUES_1(temp);
}

/* CHECK-SLASH-EXTENSION-FOR-CHARACTER-SEQUENCE */
Object check_slash_extension_for_character_sequence(keep_slash_qm)
    Object keep_slash_qm;
{
    Object read_kb_buffer_index_new_value, temp_1;
    SI_Long arg, arg_1, arg_2;
    char next_character, temp;

    x_note_fn_call(132,22);
    if ( !TRUEP(Read_kb_buffer_index))
	next_character = CHARACTER_TO_CHAR(Nil);
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = CHARACTER_TO_CHAR(SCHAR(Read_kb_buffer,Read_kb_buffer_index));
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	next_character = temp;
    }
    else
	next_character = 
		CHARACTER_TO_CHAR(read_next_char_for_kb_from_refilled_buffer());
    arg = (SI_Long)32L;
    arg_1 = IFIX(CHAR_INT(CHAR_TO_CHARACTER(next_character)));
    arg_2 = (SI_Long)126L;
    if (arg <= arg_1 && arg_1 <= arg_2) {
	if ( !(keep_slash_qm && CHAR_EQ(CHAR_TO_CHARACTER(next_character),
		CHR('\\')))) {
	    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	temp_1 = Nil;
    }
    else {
      next_loop:
	if ( !TRUEP(Read_kb_buffer_index))
	    temp_1 = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp_1 = read_next_char_for_kb_from_refilled_buffer();
	if (CHAR_EQ(temp_1,CHR('\\')))
	    goto end_loop;
	goto next_loop;
      end_loop:
	temp_1 = T;
    }
    return VALUES_1(temp_1);
}

static Object Qnon_simple_character_code;  /* non-simple-character-code */

static Object Qbad_character_following_at;  /* bad-character-following-@ */

static Object Qbad_character_following_tl;  /* bad-character-following-~ */

static Object Qillegal_characters_following_bs;  /* ILLEGAL-CHARACTERS-FOLLOWING-\\ */

static Object Qincomplete_escape_sequence;  /* incomplete-escape-sequence */

/* READ-CHARACTER-SEQUENCE-AS-TEXT-STRING-FOR-ANY-RECENT-VERSION */
Object read_character_sequence_as_text_string_for_any_recent_version(number_of_characters,
	    decrypt_qm)
    Object number_of_characters, decrypt_qm;
{
    Object gensym_string, string_length_exceeded_p, bad_state_p;
    Object escape_character_qm, first_character_code_following_bs_qm;
    Object second_character_code_following_bs_qm;
    Object third_character_code_following_bs_qm, kanji_character_code_qm;
    Object last_character_p, skip_this_character_p;
    Object read_kb_buffer_index_new_value, temp_1, gensym_string_1;
    SI_Long local_base_reference, string_length, character_code;
    SI_Long last_char_index, character_index, code, result_code, arg, arg_1;
    SI_Long arg_2;
    char character_1;
    char string_is_simple_p;
    char temp, next_character;

    x_note_fn_call(132,23);
    if (decrypt_qm && IFIX(Kb_flags) >= (SI_Long)238L)
	Base_reference = Standard_base_reference;
    local_base_reference = IFIX(Base_reference);
    string_length = IFIX(number_of_characters);
    gensym_string = string_length > 
	    IFIX(Maximum_suggested_length_for_simple_gensym_strings) ? 
	    obtain_long_enough_adjustable_gensym_string(FIX(string_length)) 
	    : obtain_simple_gensym_string(FIX(string_length));
    string_length_exceeded_p = Nil;
    character_code = (SI_Long)0L;
    character_1 = 'a';
    string_is_simple_p =  !ARRAY_HAS_FILL_POINTER_P(gensym_string);
    bad_state_p = Nil;
    escape_character_qm = Nil;
    first_character_code_following_bs_qm = Nil;
    second_character_code_following_bs_qm = Nil;
    third_character_code_following_bs_qm = Nil;
    kanji_character_code_qm = Nil;
    last_char_index = string_length - (SI_Long)1L;
    character_index = (SI_Long)0L;
    last_character_p = Nil;
    skip_this_character_p = Nil;
  next_loop:
    if ( !(character_index < string_length))
	goto end_loop;
    last_character_p = character_index == last_char_index ? T : Nil;
    skip_this_character_p = Nil;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = CHARACTER_TO_CHAR(SCHAR(Read_kb_buffer,Read_kb_buffer_index));
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = 
		CHARACTER_TO_CHAR(read_next_char_for_kb_from_refilled_buffer());
    if (decrypt_qm) {
	code = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(character_1)));
	result_code = code;
	if (result_code != (SI_Long)92L && (SI_Long)32L <= result_code && 
		result_code <= (SI_Long)126L) {
	    local_base_reference = 
		    g2ext_eval_base_ref_val(local_base_reference);
	    result_code = g2ext_characters_cipher(code,
		    local_base_reference,T ? (SI_Long)1L : (SI_Long)0L);
	}
	code = result_code;
	character_code = code;
	character_1 = CHARACTER_TO_CHAR(CODE_CHAR(FIX(code)));
    }
    else
	character_code = IFIX(CHAR_CODE(CHAR_TO_CHARACTER(character_1)));
    if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\\'))) {
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = CHARACTER_TO_CHAR(SCHAR(Read_kb_buffer,
		    Read_kb_buffer_index));
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    next_character = temp;
	}
	else
	    next_character = 
		    CHARACTER_TO_CHAR(read_next_char_for_kb_from_refilled_buffer());
	arg = (SI_Long)32L;
	arg_1 = IFIX(CHAR_INT(CHAR_TO_CHARACTER(next_character)));
	arg_2 = (SI_Long)126L;
	if (arg <= arg_1 && arg_1 <= arg_2) {
	    if ( !(character_index + (SI_Long)1L == 
		    IFIX(number_of_characters) && 
		    CHAR_EQ(CHAR_TO_CHARACTER(next_character),CHR('\\')))) {
		read_kb_buffer_index_new_value = 
			FIXNUM_SUB1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	}
	else {
	  next_loop_1:
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    if (CHAR_EQ(temp_1,CHR('\\')))
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:
	    skip_this_character_p = T;
	}
    }
    if ( !TRUEP(skip_this_character_p)) {
	if (string_is_simple_p)
	    SET_ISCHAR(gensym_string,character_index,character_1);
	else
	    SET_ICHAR(gensym_string,character_index,character_1);
	if (bad_state_p);
	else if ( !((SI_Long)32L <= character_code && character_code <= 
		(SI_Long)126L))
	    bad_state_p = Qnon_simple_character_code;
	else if (escape_character_qm) {
	    if (! !CHARACTERP(escape_character_qm))
		switch (ICHAR_CODE(escape_character_qm)) {
		  case '@':
		    switch (character_1) {
		      case 'P':
		      case 'L':
			temp_1 = T;
			break;
		      default:
			temp_1 = Nil;
			break;
		    }
		    if (temp_1)
			escape_character_qm = Nil;
		    else
			bad_state_p = Qbad_character_following_at;
		    break;
		  case '~':
		    if (ISVREF(Roman_font_special_character_code_map,
			    IFIX(CHAR_INT(CHAR_TO_CHARACTER(character_1))) 
			    - (SI_Long)32L))
			escape_character_qm = Nil;
		    else
			bad_state_p = Qbad_character_following_tl;
		    break;
		  case '\\':
		    if ( !TRUEP(first_character_code_following_bs_qm))
			first_character_code_following_bs_qm = 
				FIX(character_code);
		    else if ( !TRUEP(second_character_code_following_bs_qm)) {
			second_character_code_following_bs_qm = 
				FIX(character_code);
			if ( !(IFIX(first_character_code_following_bs_qm) 
				< (SI_Long)40L))
			    kanji_character_code_qm = FIX((SI_Long)95L * 
				    IFIX(first_character_code_following_bs_qm) 
				    + 
				    IFIX(second_character_code_following_bs_qm) 
				    + (SI_Long)4360L);
		    }
		    else {
			third_character_code_following_bs_qm = 
				FIX(character_code);
			kanji_character_code_qm = 
				FIX((IFIX(first_character_code_following_bs_qm) 
				<< (SI_Long)13L) + (SI_Long)95L * 
				IFIX(second_character_code_following_bs_qm) 
				+ 
				IFIX(third_character_code_following_bs_qm) 
				+ (SI_Long)-265976L);
		    }
		    if (first_character_code_following_bs_qm && 
			    second_character_code_following_bs_qm && 
			    (third_character_code_following_bs_qm ||  
			    !(IFIX(first_character_code_following_bs_qm) < 
			    (SI_Long)40L))) {
			if ( !TRUEP(kanji_character_code_qm))
			    bad_state_p = Qillegal_characters_following_bs;
			else {
			    escape_character_qm = Nil;
			    first_character_code_following_bs_qm = Nil;
			    second_character_code_following_bs_qm = Nil;
			    third_character_code_following_bs_qm = Nil;
			    kanji_character_code_qm = Nil;
			}
		    }
		    break;
		  default:
		    break;
		}
	}
	else if (CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('@')) || 
		CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('~')) || 
		CHAR_EQ(CHAR_TO_CHARACTER(character_1),CHR('\\')))
	    escape_character_qm = CHAR_TO_CHARACTER(character_1);
    }
    if (last_character_p &&  !TRUEP(bad_state_p) && escape_character_qm)
	bad_state_p = Qincomplete_escape_sequence;
    character_index = skip_this_character_p ? character_index : 
	    character_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (bad_state_p) {
	temp_1 = 
		copy_illegal_gensym_string_without_bad_characters(gensym_string);
	reclaim_gensym_string(gensym_string);
	gensym_string = temp_1;
    }
    temp_1 = gensym_string;
    if (decrypt_qm)
	Base_reference = FIX(local_base_reference);
    gensym_string_1 = temp_1;
    temp_1 = gensym_string_to_wide_string(gensym_string_1);
    reclaim_gensym_string(gensym_string_1);
    return VALUES_1(temp_1);
}

/* READ-CHARACTER-SEQUENCE-AS-TEXT-STRING-OLD-WAY */
Object read_character_sequence_as_text_string_old_way(number_of_characters,
	    encrypt_qm)
    Object number_of_characters, encrypt_qm;
{
    Object gensym_string, gensym_string_2, temp;

    x_note_fn_call(132,24);
    gensym_string = 
	    read_character_sequence_as_gensym_string_old_way_1(number_of_characters,
	    encrypt_qm);
    if (legal_gensym_string_p(1,gensym_string))
	gensym_string_2 = gensym_string;
    else {
	temp = 
		copy_illegal_gensym_string_without_bad_characters(gensym_string);
	reclaim_gensym_string(gensym_string);
	gensym_string_2 = temp;
    }
    temp = gensym_string_to_wide_string(gensym_string_2);
    reclaim_gensym_string(gensym_string_2);
    return VALUES_1(temp);
}

/* READ-CHARACTER-SEQUENCE-AS-GENSYM-STRING-OLD-WAY-1 */
Object read_character_sequence_as_gensym_string_old_way_1(number_of_characters,
	    encrypt_qm)
    Object number_of_characters, encrypt_qm;
{
    Object gensym_string, number_of_unprefixed_escape_characters, i;
    Object character_1, char_1, temp, read_kb_buffer_index_new_value;
    Object new_gensym_string, j;
    SI_Long code, result_code, arg, arg_1, arg_2, i_1, ab_loop_bind_;
    char temp_1;

    x_note_fn_call(132,25);
    gensym_string = obtain_simple_gensym_string(number_of_characters);
    number_of_unprefixed_escape_characters = FIX((SI_Long)0L);
    i = FIX((SI_Long)0L);
    character_1 = Nil;
  next_loop:
    if ( !FIXNUM_LT(i,number_of_characters))
	goto end_loop;
    if (encrypt_qm) {
	if ( !TRUEP(Read_kb_buffer_index))
	    char_1 = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    char_1 = temp;
	}
	else
	    char_1 = read_next_char_for_kb_from_refilled_buffer();
	code = IFIX(CHAR_CODE(char_1));
	result_code = code;
	if (result_code != (SI_Long)92L && (SI_Long)32L <= result_code && 
		result_code <= (SI_Long)126L) {
	    Base_reference = 
		    FIX(g2ext_eval_base_ref_val(IFIX(Base_reference)));
	    result_code = g2ext_characters_cipher(code,
		    IFIX(Base_reference),T ? (SI_Long)1L : (SI_Long)0L);
	}
	code = result_code;
	character_1 = CODE_CHAR(FIX(code));
    }
    else if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    temp = character_1;
    if ( !CHARACTERP(temp)) {
	if (EQ(character_1,CHR('~')) &&  !(IFIX(Kb_flags) >= (SI_Long)32L))
	    number_of_unprefixed_escape_characters = 
		    FIXNUM_ADD1(number_of_unprefixed_escape_characters);
	SET_SCHAR(gensym_string,i,character_1);
	i = FIXNUM_ADD1(i);
    }
    else
	switch (ICHAR_CODE(temp)) {
	  case '\\':
	    temp_1 =  !(IFIX(Kb_flags) >= (SI_Long)1L);
	    if (temp_1);
	    else {
		if ( !TRUEP(Read_kb_buffer_index))
		    character_1 = Nil;
		else if (FIXNUM_LT(Read_kb_buffer_index,
			    Read_kb_buffer_length)) {
		    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		    read_kb_buffer_index_new_value = 
			    FIXNUM_ADD1(Read_kb_buffer_index);
		    Read_kb_buffer_index = read_kb_buffer_index_new_value;
		    character_1 = temp;
		}
		else
		    character_1 = read_next_char_for_kb_from_refilled_buffer();
		temp_1 = EQ(character_1,CHR('\\')) ?  !(IFIX(Kb_flags) >= 
			(SI_Long)32L) : TRUEP(Nil);
	    }
	    if (temp_1) {
		number_of_unprefixed_escape_characters = 
			FIXNUM_ADD1(number_of_unprefixed_escape_characters);
		SET_SCHAR(gensym_string,i,character_1);
		i = FIXNUM_ADD1(i);
	    }
	    else {
		arg = (SI_Long)32L;
		arg_1 = IFIX(CHAR_INT(character_1));
		arg_2 = (SI_Long)126L;
		temp_1 =  !(arg <= arg_1 && arg_1 <= arg_2);
		if (temp_1);
		else
		    temp_1 =  !(IFIX(Kb_flags) >= (SI_Long)32L);
		if (temp_1) {
		  next_loop_1:
		    if ( !TRUEP(Read_kb_buffer_index))
			temp = Nil;
		    else if (FIXNUM_LT(Read_kb_buffer_index,
			    Read_kb_buffer_length)) {
			temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
			read_kb_buffer_index_new_value = 
				FIXNUM_ADD1(Read_kb_buffer_index);
			Read_kb_buffer_index = read_kb_buffer_index_new_value;
		    }
		    else
			temp = read_next_char_for_kb_from_refilled_buffer();
		    if (EQ(temp,CHR('\\')))
			goto end_loop_1;
		    goto next_loop_1;
		  end_loop_1:;
		}
		else {
		    temp = CHR('\\');
		    SET_SCHAR(gensym_string,i,temp);
		    i = FIXNUM_ADD1(i);
		    if ( !(FIXNUM_EQ(i,number_of_characters) && 
			    EQ(character_1,CHR('\\')))) {
			read_kb_buffer_index_new_value = 
				FIXNUM_SUB1(Read_kb_buffer_index);
			Read_kb_buffer_index = read_kb_buffer_index_new_value;
		    }
		}
	    }
	    break;
	  default:
	    if (EQ(character_1,CHR('~')) &&  !(IFIX(Kb_flags) >= (SI_Long)32L))
		number_of_unprefixed_escape_characters = 
			FIXNUM_ADD1(number_of_unprefixed_escape_characters);
	    SET_SCHAR(gensym_string,i,character_1);
	    i = FIXNUM_ADD1(i);
	    break;
	}
    goto next_loop;
  end_loop:
    if (IFIX(number_of_unprefixed_escape_characters) > (SI_Long)0L) {
	new_gensym_string = 
		obtain_simple_gensym_string(FIXNUM_ADD(number_of_characters,
		number_of_unprefixed_escape_characters));
	j = FIX((SI_Long)0L);
	i_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(number_of_characters);
	character_1 = Nil;
      next_loop_2:
	if (i_1 >= ab_loop_bind_)
	    goto end_loop_2;
	character_1 = CHR(ISCHAR(gensym_string,i_1));
	if (! !CHARACTERP(character_1))
	    switch (ICHAR_CODE(character_1)) {
	      case '\\':
	      case '~':
		temp = CHR('~');
		SET_SCHAR(new_gensym_string,j,temp);
		j = FIXNUM_ADD1(j);
		break;
	      default:
		break;
	    }
	SET_SCHAR(new_gensym_string,j,character_1);
	j = FIXNUM_ADD1(j);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	reclaim_simple_gensym_string(gensym_string);
	return VALUES_1(new_gensym_string);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(gensym_string);
    return VALUES_1(Qnil);
}

Object Most_positive_fixnum_ash_minus_5_minus_1 = UNBOUND;

/* READ-REMAINDER-OF-INTEGER-FOR-KB */
Object read_remainder_of_integer_for_kb(value_so_far_init,weight)
    Object value_so_far_init, weight;
{
    Object character_1, temp, read_kb_buffer_index_new_value;
    SI_Long value_so_far, character_code;

    x_note_fn_call(132,26);
    value_so_far = IFIX(value_so_far_init);
    character_1 = Nil;
  next_loop:
    value_so_far = (value_so_far << (SI_Long)5L) + IFIX(weight);
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    character_code = IFIX(CHAR_CODE(character_1));
    if ((SI_Long)48L <= character_code && character_code <= (SI_Long)57L)
	weight = FIX(character_code - (SI_Long)48L);
    else if ((SI_Long)97L <= character_code && character_code <= (SI_Long)119L)
	weight = FIX(character_code - (SI_Long)97L + (SI_Long)10L);
    else
	weight = Qnil;
    if ( !TRUEP(weight))
	goto end_loop;
    if ( !(value_so_far <= IFIX(Most_positive_fixnum_ash_minus_5_minus_1))) {
	temp = read_bignum_remainder_of_integer_for_kb(FIX(value_so_far),
		weight);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
    Read_kb_buffer_index = read_kb_buffer_index_new_value;
    if (CHAR_EQ(character_1,CHR('-')) && EQ(FIX(value_so_far),
	    FIX((SI_Long)0L))) {
	value_so_far = IFIX(Most_negative_fixnum);
	temp = FIX(value_so_far);
    }
    else if (CHAR_EQ(character_1,CHR('-')))
	temp = FIX( - value_so_far);
    else
	temp = FIX(value_so_far);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* READ-BIGNUM-REMAINDER-OF-INTEGER-FOR-KB */
Object read_bignum_remainder_of_integer_for_kb(value_so_far,weight)
    Object value_so_far, weight;
{
    Object character_1, temp, read_kb_buffer_index_new_value;
    SI_Long character_code;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(132,27);
    character_1 = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop:
	value_so_far = add(ash(value_so_far,FIX((SI_Long)5L)),weight);
	if ( !TRUEP(Read_kb_buffer_index))
	    character_1 = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    character_1 = temp;
	}
	else
	    character_1 = read_next_char_for_kb_from_refilled_buffer();
	character_code = IFIX(CHAR_CODE(character_1));
	if ((SI_Long)48L <= character_code && character_code <= (SI_Long)57L)
	    weight = FIX(character_code - (SI_Long)48L);
	else if ((SI_Long)97L <= character_code && character_code <= 
		(SI_Long)119L)
	    weight = FIX(character_code - (SI_Long)97L + (SI_Long)10L);
	else
	    weight = Qnil;
	if ( !TRUEP(weight))
	    goto end_loop;
	goto next_loop;
      end_loop:
	value_so_far = make_permanent_integer(CHAR_EQ(character_1,
		CHR('-')) ? negate(value_so_far) : value_so_far);
    }
    POP_LOCAL_ALLOCATION(0,0);
    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
    Read_kb_buffer_index = read_kb_buffer_index_new_value;
    return VALUES_1(value_so_far);
}

/* READ-LONG-FOR-KB */
Object read_long_for_kb()
{
    Object integer_qm, temp, new_long;
    SI_int64 long_1, zero, long_value, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(132,28);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	integer_qm = read_element_for_kb(Nil);
	if (FIXNUMP(integer_qm)) {
	    long_1 = INTEGER_TO_INT64(integer_qm);
	    zero = (SI_int64)(SI_Long)0L;
	    temp = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
	    long_value = INTEGER_TO_INT64(temp);
	    new_long = allocate_managed_long_box();
	    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(long_value));
	    temp = new_long;
	}
	else if (INLINE_LONG_P(integer_qm) != (SI_Long)0L) {
	    new_long = allocate_managed_long_box();
	    aref_new_value = INTEGER_TO_INT64(integer_qm);
	    set_aref1(new_long,FIX((SI_Long)0L),
		    INT64_TO_INTEGER(aref_new_value));
	    temp = new_long;
	}
	else if (BIGNUMP(integer_qm)) {
	    long_1 = INTEGER_TO_INT64(integer_qm);
	    zero = (SI_int64)(SI_Long)0L;
	    temp = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
	    long_value = INTEGER_TO_INT64(temp);
	    new_long = allocate_managed_long_box();
	    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(long_value));
	    temp = new_long;
	}
	else {
	    long_1 = (SI_int64)(SI_Long)0L;
	    zero = (SI_int64)(SI_Long)0L;
	    temp = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
	    long_value = INTEGER_TO_INT64(temp);
	    new_long = allocate_managed_long_box();
	    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(long_value));
	    temp = new_long;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* READ-LEGACY-LONG-FOR-KB */
Object read_legacy_long_for_kb()
{
    Object temp, new_long, i64;
    SI_Long len, i, ab_loop_bind_;
    SI_int64 long_1, zero, long_value;

    x_note_fn_call(132,29);
    read_element_for_kb(Nil);
    len = IFIX(read_element_for_kb(Nil));
    long_1 = (SI_int64)(SI_Long)0L;
    zero = (SI_int64)(SI_Long)0L;
    temp = add(INT64_TO_INTEGER(long_1),INT64_TO_INTEGER(zero));
    long_value = INTEGER_TO_INT64(temp);
    new_long = allocate_managed_long_box();
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(long_value));
    i64 = new_long;
    i = (SI_Long)0L;
    ab_loop_bind_ = len;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    read_element_for_kb(Nil);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(i64);
}

DEFINE_VARIABLE_WITH_SYMBOL(Original_kb_state_plist_written_qm, Qoriginal_kb_state_plist_written_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Backup_case_qm, Qbackup_case_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Type_of_file_being_read, Qtype_of_file_being_read);

DEFINE_VARIABLE_WITH_SYMBOL(Previous_timestamp_qm, Qprevious_timestamp_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_description_for_slot_value_being_read_qm, Qslot_description_for_slot_value_being_read_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Frames_for_rendezvous_in_aggregate_values_qm, Qframes_for_rendezvous_in_aggregate_values_qm);

/* LOCK-TO-KB */
Object lock_to_kb(kb_identification)
    Object kb_identification;
{
    x_note_fn_call(132,30);
    return VALUES_1(Nil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qgensym_pathname_namestring;  /* gensym-pathname-namestring */

static Object Qg2_stream_error_string;  /* g2-stream-error-string */

static Object string_constant_12;  /* "G2 could not open the file \"~a\":  ~a." */

/* REJECT-GENSYM-PATHNAME-TO-READ */
Object reject_gensym_pathname_to_read(gensym_pathname_or_namestring_for_file)
    Object gensym_pathname_or_namestring_for_file;
{
    volatile Object namestring_for_file;
    volatile Object namestring_for_user;
    volatile Object error_string_for_user;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(132,31);
    SAVE_STACK();
    namestring_for_file = Qunbound_in_protected_let;
    namestring_for_user = Qunbound_in_protected_let;
    error_string_for_user = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	namestring_for_file = 
		text_string_p(gensym_pathname_or_namestring_for_file) ? 
		copy_text_string(gensym_pathname_or_namestring_for_file) : 
		gensym_namestring(1,gensym_pathname_or_namestring_for_file);
	namestring_for_user = import_text_string(2,namestring_for_file,
		Qgensym_pathname_namestring);
	temp = assq_function(Internal_status_of_most_recent_file_operation,
		G2_stream_error_string_table);
	temp = CDR(temp);
	if (temp);
	else {
	    if (Cached_unknown_error_string_with_code_qm)
		reclaim_text_string(Cached_unknown_error_string_with_code_qm);
	    Cached_unknown_error_string_with_code_qm = 
		    tformat_text_string(2,
		    Unknown_error_during_file_op_with_code_message,
		    Internal_status_of_most_recent_file_operation);
	    temp = Cached_unknown_error_string_with_code_qm;
	}
	error_string_for_user = import_text_string(2,temp,
		Qg2_stream_error_string);
	notify_user(3,string_constant_12,namestring_for_user,
		error_string_for_user);
	SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (error_string_for_user) {
	if ( !EQ(error_string_for_user,Qunbound_in_protected_let))
	    reclaim_text_string(error_string_for_user);
    }
    if (namestring_for_user) {
	if ( !EQ(namestring_for_user,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_for_user);
    }
    if (namestring_for_file) {
	if ( !EQ(namestring_for_file,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_for_file);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qgensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object Qtformat_text_string;  /* tformat-text-string */

static Object string_constant_13;  /* "~a" */

/* SIMPLE-KB-READ */
Object simple_kb_read(gensym_pathname_to_read,operation,
	    update_before_loading_qm,not_top_level_qm)
    Object gensym_pathname_to_read, operation, update_before_loading_qm;
    Object not_top_level_qm;
{
    Object message_qm, inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    Object read_kb_stream, temp, result_from_body, gensymed_symbol;
    Object control_string, error_args, error_arg, ab_loop_list_, report_string;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(3);
    Object result;

    x_note_fn_call(132,32);
    SAVE_STACK();
    message_qm = Nil;
    if (message_qm)
	notify_user_1(copy_text_string(message_qm));
    inside_handling_gensym_file_errors_scope_p = T;
    gensym_file_error_occurred_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
	      1);
	if (PUSH_CATCH(Qgensym_file_error_catch_tag,1)) {
	    pathname_used_p = Qunbound_in_protected_let;
	    namestring_1 = Qunbound_in_protected_let;
	    read_kb_stream = Qunbound_in_protected_let;
	    PUSH_SPECIAL_WITH_SYMBOL(Read_kb_stream,Qread_kb_stream,read_kb_stream,
		    0);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  pathname_used_p = 
			  SIMPLE_VECTOR_P(gensym_pathname_to_read) ? 
			  (EQ(ISVREF(gensym_pathname_to_read,(SI_Long)0L),
			  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			  ? T : Nil) : Qnil;
		  namestring_1 = SIMPLE_VECTOR_P(gensym_pathname_to_read) 
			  && EQ(ISVREF(gensym_pathname_to_read,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			  ? gensym_namestring(1,gensym_pathname_to_read) : 
			  gensym_pathname_to_read;
		  Read_kb_stream = 
			  g2_stream_open_for_binary_input(namestring_1);
		  temp =  !TRUEP(Read_kb_stream) ? 
			  reject_gensym_pathname_to_read(gensym_pathname_to_read) 
			  : simple_kb_read_1(Read_kb_stream,
			  gensym_pathname_to_read,operation,Nil);
		  SAVE_VALUES(VALUES_1(temp));
	      }
	      POP_UNWIND_PROTECT(0);
	      if (Read_kb_stream) {
		  if ( !EQ(Read_kb_stream,Qunbound_in_protected_let))
		      g2_stream_close(Read_kb_stream);
	      }
	      if (namestring_1) {
		  if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
		      if (pathname_used_p)
			  reclaim_text_string(namestring_1);
		  }
	      }
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	      result_from_body = result;
	    POP_SPECIAL();
	}
	else
	    result_from_body = CATCH_VALUES();
	POP_CATCH(1);
	if (Gensym_file_error_occurred_p) {
	    gensymed_symbol = result_from_body;
	    control_string = CAR(gensymed_symbol);
	    error_args = CDR(gensymed_symbol);
	    temp = SYMBOL_FUNCTION(Qtformat_text_string);
	    temp = APPLY_2(temp,control_string,error_args);
	    if (result_from_body) {
		error_arg = Nil;
		ab_loop_list_ = result_from_body;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		error_arg = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (text_string_p(error_arg))
		    reclaim_text_string(error_arg);
		goto next_loop;
	      end_loop:
		reclaim_path_list_1(result_from_body);
	    }
	    report_string = temp;
	    notify_user(2,string_constant_13,report_string);
	    reclaim_text_string(report_string);
	    temp = Nil;
	}
	else
	    temp = result_from_body;
      POP_SPECIAL();
    POP_SPECIAL();
    result = VALUES_2(temp,message_qm);
    RESTORE_STACK();
    return result;
}

static Object string_constant_14;  /* "a xml-object for module ~a" */

static Object string_constant_15;  /* "something" */

static Object Qplist;              /* plist */

static Object Qget_xml_kb;         /* get-xml-kb */

static Object Qrestore_xml_kb;     /* restore-xml-kb */

/* SIMPLE-KB-READ-1 */
Object simple_kb_read_1(read_kb_stream,gensym_pathname_to_read_qm,
	    operation,xml_object_qm)
    Object read_kb_stream, gensym_pathname_to_read_qm, operation;
    Object xml_object_qm;
{
    volatile Object truename_qm;
    Object namestring_for_kb_being_read, kb_object_index_space;
    Object name_text_string_for_kb_being_read, new_saved_kb_format_p;
    Object kb_uses_crlf_p, plist_has_been_checked_p, previous_timestamp_qm;
    Object next_character_for_kb_qm, read_kb_buffer_length;
    Object read_kb_buffer_index, base_reference, name_of_kb_being_read;
    Object reformat_as_appropriate_qm, auto_merge_case_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(132,33);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Read_kb_stream,Qread_kb_stream,read_kb_stream,13);
      truename_qm = Qunbound_in_protected_let;
      namestring_for_kb_being_read = Qunbound_in_protected_let;
      kb_object_index_space = Qunbound_in_protected_let;
      name_text_string_for_kb_being_read = Qunbound_in_protected_let;
      new_saved_kb_format_p = Qunbound_in_protected_let;
      kb_uses_crlf_p = Qunbound_in_protected_let;
      plist_has_been_checked_p = Qunbound_in_protected_let;
      previous_timestamp_qm = Qunbound_in_protected_let;
      next_character_for_kb_qm = Qunbound_in_protected_let;
      read_kb_buffer_length = Qunbound_in_protected_let;
      read_kb_buffer_index = Qunbound_in_protected_let;
      base_reference = Qunbound_in_protected_let;
      PUSH_SPECIAL_WITH_SYMBOL(Base_reference,Qbase_reference,base_reference,
	      12);
	PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_index,Qread_kb_buffer_index,read_kb_buffer_index,
		11);
	  PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_length,Qread_kb_buffer_length,read_kb_buffer_length,
		  10);
	    PUSH_SPECIAL_WITH_SYMBOL(Next_character_for_kb_qm,Qnext_character_for_kb_qm,next_character_for_kb_qm,
		    9);
	      PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
		      8);
		PUSH_SPECIAL_WITH_SYMBOL(Plist_has_been_checked_p,Qplist_has_been_checked_p,plist_has_been_checked_p,
			7);
		  PUSH_SPECIAL_WITH_SYMBOL(Kb_uses_crlf_p,Qkb_uses_crlf_p,kb_uses_crlf_p,
			  6);
		    PUSH_SPECIAL_WITH_SYMBOL(New_saved_kb_format_p,Qnew_saved_kb_format_p,new_saved_kb_format_p,
			    5);
		      PUSH_SPECIAL_WITH_SYMBOL(Name_text_string_for_kb_being_read,Qname_text_string_for_kb_being_read,name_text_string_for_kb_being_read,
			      4);
			PUSH_SPECIAL_WITH_SYMBOL(Kb_object_index_space,Qkb_object_index_space,kb_object_index_space,
				3);
			  PUSH_SPECIAL_WITH_SYMBOL(Namestring_for_kb_being_read,Qnamestring_for_kb_being_read,namestring_for_kb_being_read,
				  2);
			    if (PUSH_UNWIND_PROTECT(0)) {
				truename_qm = gensym_pathname_to_read_qm ? 
					gensym_truename(gensym_pathname_to_read_qm) 
					: Nil;
				if (truename_qm)
				    Namestring_for_kb_being_read = 
					    gensym_namestring(1,truename_qm);
				else if (xml_object_qm)
				    Namestring_for_kb_being_read = 
					    tformat_text_string(2,
					    string_constant_14,
					    module_name_string_for_xml_object(xml_object_qm));
				else
				    Namestring_for_kb_being_read = 
					    tformat_text_string(1,
					    string_constant_15);
				Kb_object_index_space = 
					make_index_space_1(Nil,Nil);
				Name_text_string_for_kb_being_read = 
					copy_text_string(Namestring_for_kb_being_read);
				New_saved_kb_format_p = Nil;
				Kb_uses_crlf_p = Nil;
				Plist_has_been_checked_p = Nil;
				Previous_timestamp_qm = Nil;
				Next_character_for_kb_qm = Nil;
				Read_kb_buffer_length = FIX((SI_Long)0L);
				Read_kb_buffer_index = FIX((SI_Long)0L);
				Base_reference = Nil;
				if (EQ(operation,Qplist)) {
				    if (read_format_identifier_for_kb())
					SAVE_VALUES(read_initial_plist_for_kb(0));
				    else
					SAVE_VALUES(VALUES_1(Nil));
				}
				else if (EQ(operation,Qget_xml_kb))
				    SAVE_VALUES(read_top_level_xml_element(gensym_pathname_to_read_qm,
					    T));
				else if (EQ(operation,Qrestore_xml_kb)) {
				    name_of_kb_being_read = Nil;
				    reformat_as_appropriate_qm = Nil;
				    auto_merge_case_qm = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
					    1);
				      PUSH_SPECIAL_WITH_SYMBOL(Name_of_kb_being_read,Qname_of_kb_being_read,name_of_kb_being_read,
					      0);
					SAVE_VALUES(continue_read_kb(Nil,
						Nil,Nil,Nil,
						Reformat_as_appropriate_qm,
						auto_merge_case_qm,Nil,
						xml_object_qm));
				      POP_SPECIAL();
				    POP_SPECIAL();
				}
				else
				    SAVE_VALUES(VALUES_1(Qnil));
			    }
			    POP_UNWIND_PROTECT(0);
			    if (Name_text_string_for_kb_being_read) {
				if ( 
					!EQ(Name_text_string_for_kb_being_read,
					Qunbound_in_protected_let))
				    reclaim_text_string(Name_text_string_for_kb_being_read);
			    }
			    if (Kb_object_index_space) {
				if ( !EQ(Kb_object_index_space,
					Qunbound_in_protected_let))
				    reclaim_index_space_1(Kb_object_index_space);
			    }
			    if (Namestring_for_kb_being_read) {
				if ( !EQ(Namestring_for_kb_being_read,
					Qunbound_in_protected_let))
				    reclaim_text_string(Namestring_for_kb_being_read);
			    }
			    if (truename_qm) {
				if ( !EQ(truename_qm,
					Qunbound_in_protected_let)) {
				    if (truename_qm)
					reclaim_gensym_pathname(truename_qm);
				}
			    }
			    CONTINUE_UNWINDING(0);
			    result = RESTORE_VALUES();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* READ-INITIAL-PLIST */
Object read_initial_plist(gensym_pathname_to_read,update_before_loading_qm,
	    not_top_level_qm)
    Object gensym_pathname_to_read, update_before_loading_qm, not_top_level_qm;
{
    x_note_fn_call(132,34);
    return simple_kb_read(gensym_pathname_to_read,Qplist,
	    update_before_loading_qm,not_top_level_qm);
}

static Object string_constant_16;  /* "File \"~A\" is not a KB or lacks a proper KB header." */

/* READ-FORMAT-IDENTIFIER-FOR-KB */
Object read_format_identifier_for_kb()
{
    Object non_empty_file_p, kb_file_comment_string_qm, character_qm, temp;
    Object read_kb_buffer_index_new_value;

    x_note_fn_call(132,35);
    Kb_format_identifier_read_qm = Nil;
    non_empty_file_p = g2_stream_file_non_empty(Read_kb_stream);
    kb_file_comment_string_qm = non_empty_file_p ? 
	    read_comment_string_if_any_for_kb() : Nil;
    character_qm = non_empty_file_p ? read_char_for_kb_past_spaces() : Nil;
    if (EQ(character_qm,CHR('J'))) {
	New_saved_kb_format_p = T;
	Kb_format_identifier_read_qm = T;
	temp = kb_file_comment_string_qm;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(T);
    }
    else if (EQ(character_qm,CHR('K'))) {
	Kb_format_identifier_read_qm = T;
	temp = kb_file_comment_string_qm;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(T);
    }
    else if (Need_to_check_plist_p &&  !TRUEP(kb_file_comment_string_qm) 
	    && EQ(character_qm,CHR('<'))) {
	Plist_has_been_checked_p = T;
	Kb_format_identifier_read_qm = T;
	read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	return VALUES_1(T);
    }
    else {
	notify_user(2,string_constant_16,Name_text_string_for_kb_being_read);
	return VALUES_1(Nil);
    }
}

static Object Qkb_file_comment_string;  /* kb-file-comment-string */

static Object Qtype_of_file;       /* type-of-file */

static Object Qsave_kb;            /* save-kb */

static Object Qkb_save;            /* kb-save */

static Object Qsave_kb_with_runtime_data;  /* save-kb-with-runtime-data */

static Object Qkb_save_with_runtine_data;  /* kb-save-with-runtine-data */

/* READ-INITIAL-PLIST-FOR-KB */
Object read_initial_plist_for_kb varargs_1(int, n)
{
    Object kb_file_comment_string_qm, plist, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(132,36);
    INIT_ARGS_nonrelocating();
    kb_file_comment_string_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Plist_has_been_checked_p)
	return read_initial_plist_for_clear_text_kb();
    else {
	plist = read_element_for_kb(T);
	if (kb_file_comment_string_qm)
	    plist = nconc2(slot_value_list_2(Qkb_file_comment_string,
		    kb_file_comment_string_qm),plist);
	temp = getf(plist,Qtype_of_file,_);
	if (EQ(temp,Qsave_kb))
	    plist = set_getf(plist,Qtype_of_file,Qkb_save);
	else if (EQ(temp,Qsave_kb_with_runtime_data))
	    plist = set_getf(plist,Qtype_of_file,Qkb_save_with_runtine_data);
	temp = getf(plist,Qkb_flags,_);
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	temp_1 = FIX((SI_Long)253L);
	if (NUM_EQ(temp,temp_1))
	    plist = set_getf(plist,Qkb_flags,FIX((SI_Long)252L));
	return VALUES_1(plist);
    }
}

static Object string_constant_17;  /* "~%" */

static Object array_constant;      /* # */

/* READ-COMMENT-STRING-IF-ANY-FOR-KB */
Object read_comment_string_if_any_for_kb()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_1, temp, temp_1, next_character, started_qm;
    Object simple_or_wide_character, thing, schar_arg_2, schar_new_value;
    Object result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(132,37);
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
	      if ( !TRUEP(Read_kb_buffer_index))
		  character_1 = Nil;
	      else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		  temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		  temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		  Read_kb_buffer_index = temp_1;
		  character_1 = temp;
	      }
	      else
		  character_1 = read_next_char_for_kb_from_refilled_buffer();
	    next_loop:
	      if (CHAR_EQ(character_1,CHR(' ')));
	      else if (CHAR_EQ(character_1,CHR('\t')));
	      else if (CHAR_EQ(character_1,CHR(';'))) {
		  next_character = Nil;
		  started_qm = Nil;
		next_loop_1:
		  if ( !TRUEP(Read_kb_buffer_index))
		      next_character = Nil;
		  else if (FIXNUM_LT(Read_kb_buffer_index,
			  Read_kb_buffer_length)) {
		      temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		      temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		      Read_kb_buffer_index = temp_1;
		      next_character = temp;
		  }
		  else
		      next_character = 
			      read_next_char_for_kb_from_refilled_buffer();
		  temp = CHAR_EQ(next_character,CHR('\n')) ? T : Nil;
		  if (temp);
		  else if (CHAR_EQ(next_character,CHR('\r'))) {
		      Kb_uses_crlf_p = T;
		      temp = T;
		  }
		  else {
		      temp = CHAR_EQ(next_character,CHR('\f')) ? T : Nil;
		      if (temp);
		      else
			  temp = Qnil;
		  }
		  if (temp) {
		      tformat(1,string_constant_17);
		      update_file_progress_display_for_newline_in_kb(0);
		      goto end_1;
		  }
		  else if ( !TRUEP(started_qm) && (CHAR_EQ(next_character,
			  CHR(' ')) || CHAR_EQ(next_character,CHR(';')))) {
		      if (CHAR_EQ(next_character,CHR(' ')))
			  started_qm = T;
		  }
		  else {
		      started_qm = T;
		      simple_or_wide_character = CHAR_CODE(next_character);
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = simple_or_wide_character;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = simple_or_wide_character;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		  }
		  goto next_loop_1;
		end_loop:
		end_1:;
	      }
	      else {
		  temp = CHAR_EQ(character_1,CHR('\n')) ? T : Nil;
		  if (temp);
		  else if (CHAR_EQ(character_1,CHR('\r'))) {
		      Kb_uses_crlf_p = T;
		      temp = T;
		  }
		  else {
		      temp = CHAR_EQ(character_1,CHR('\f')) ? T : Nil;
		      if (temp);
		      else
			  temp = Qnil;
		  }
		  if (temp)
		      update_file_progress_display_for_newline_in_kb(0);
		  else {
		      temp_1 = FIXNUM_SUB1(Read_kb_buffer_index);
		      Read_kb_buffer_index = temp_1;
		      goto end_2;
		  }
	      }
	      if ( !TRUEP(Read_kb_buffer_index))
		  character_1 = Nil;
	      else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		  temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		  temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		  Read_kb_buffer_index = temp_1;
		  character_1 = temp;
	      }
	      else
		  character_1 = read_next_char_for_kb_from_refilled_buffer();
	      goto next_loop;
	    end_loop_1:
	    end_2:;
	      result_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (string_eq_w(result_1,array_constant)) {
	reclaim_text_string(result_1);
	temp = Nil;
    }
    else
	temp = result_1;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(New_compiled_byte_code_body_list, Qnew_compiled_byte_code_body_list);

DEFINE_VARIABLE_WITH_SYMBOL(New_byte_code_body_list, Qnew_byte_code_body_list);

/* ADD-NEW-COMPILED-BYTE-CODE-BODY */
Object add_new_compiled_byte_code_body(function)
    Object function;
{
    x_note_fn_call(132,38);
    g2ext_show_function_address(function);
    New_compiled_byte_code_body_list = eval_cons_1(function,
	    New_compiled_byte_code_body_list);
    return VALUES_1(New_compiled_byte_code_body_list);
}

/* ADD-NEW-BYTE-CODE-BODY */
Object add_new_byte_code_body(byte_code_body)
    Object byte_code_body;
{
    x_note_fn_call(132,39);
    New_byte_code_body_list = eval_cons_1(byte_code_body,
	    New_byte_code_body_list);
    return VALUES_1(New_byte_code_body_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Recompile_on_next_load, Qrecompile_on_next_load);

static Object Qread_kb_internal;   /* read-kb-internal */

static Object string_constant_18;  /* "initialize_compiled_kb" */

static Object string_constant_19;  /* "Loading \"~A\" -- after clearing old KB" */

static Object string_constant_20;  /* "Clearing KB and merging in \"~A\"" */

static Object string_constant_21;  /* "Merging \"~A\" into current KB -- and installing its system tables" */

static Object string_constant_22;  /* "Merging \"~A\" into current KB" */

/* READ-KB */
Object read_kb(module_qm,gensym_pathname_to_read,clear_kb_qm,
	    install_system_tables_qm,reformat_as_appropriate_qm,
	    auto_merge_case_qm,default_kb_directory_qm)
    Object module_qm, gensym_pathname_to_read, clear_kb_qm;
    Object install_system_tables_qm, reformat_as_appropriate_qm;
    Object auto_merge_case_qm, default_kb_directory_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, kb_load_case_qm;
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p, temp_1;
    volatile Object namestring_for_file;
    Object new_compiled_byte_code_body_list, new_byte_code_body_list;
    Object loading_compiled_kb_p, compiled_file_pathname;
    Object namestring_as_gensym_string_1;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    Object read_kb_stream;
    volatile Object truename_1;
    Object name_of_kb_being_read, namestring_for_kb_being_read;
    Object name_text_string_for_kb_being_read, result_from_body;
    Object gensymed_symbol, control_string, error_args, error_arg;
    Object ab_loop_list_, report_string;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(12);
    Object result;

    x_note_fn_call(132,40);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    11);
      index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	      10);
	if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		Size_of_basic_backtrace_information),
		Maximum_index_in_backtrace_stack_for_internal_error)) {
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = Nil;
	    temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	    Index_of_top_of_backtrace_stack = temp;
	    temp = Backtrace_stack_for_internal_error;
	    svref_arg_2 = Index_of_top_of_backtrace_stack;
	    SVREF(temp,svref_arg_2) = Qread_kb_internal;
	}
	kb_load_case_qm = clear_kb_qm ? install_system_tables_qm : Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Kb_load_case_qm,Qkb_load_case_qm,kb_load_case_qm,
		9);
	  Noting_changes_to_kb_p = Nil;
	  inside_handling_gensym_file_errors_scope_p = T;
	  gensym_file_error_occurred_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
		  8);
	    PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
		    7);
	      if (PUSH_CATCH(Qgensym_file_error_catch_tag,3)) {
		  temp_1 = 
			  get_less_case_sensitive_gensym_pathname_if_any(gensym_pathname_to_read);
		  if (temp_1);
		  else
		      temp_1 = gensym_pathname_to_read;
		  gensym_pathname_to_read = temp_1;
		  namestring_for_file = Qunbound_in_protected_let;
		  new_compiled_byte_code_body_list = Qunbound_in_protected_let;
		  new_byte_code_body_list = Qunbound_in_protected_let;
		  loading_compiled_kb_p = Qunbound_in_protected_let;
		  PUSH_SPECIAL_WITH_SYMBOL(Loading_compiled_kb_p,Qloading_compiled_kb_p,loading_compiled_kb_p,
			  6);
		    PUSH_SPECIAL_WITH_SYMBOL(New_byte_code_body_list,Qnew_byte_code_body_list,new_byte_code_body_list,
			    5);
		      PUSH_SPECIAL_WITH_SYMBOL(New_compiled_byte_code_body_list,Qnew_compiled_byte_code_body_list,new_compiled_byte_code_body_list,
			      4);
			if (PUSH_UNWIND_PROTECT(2)) {
			    namestring_for_file = gensym_namestring(1,
				    gensym_pathname_to_read);
			    New_compiled_byte_code_body_list = Nil;
			    New_byte_code_body_list = Nil;
			    if (Enable_loading_compiled_kbs_p) {
				compiled_file_pathname = 
					pathname_gt_shared_file_pathname(gensym_pathname_to_read);
				if (gensym_probe_file(compiled_file_pathname)) 
					    {
				    namestring_as_gensym_string_1 = 
					    namestring_as_gensym_string(compiled_file_pathname);
				    if (T)
					load_library(namestring_as_gensym_string_1,
						string_constant_18,
						compiled_kb_initialization_argument());
				    reclaim_gensym_string(namestring_as_gensym_string_1);
				    Loading_compiled_kb_p = T;
				}
				else
				    Loading_compiled_kb_p = Nil;
			    }
			    else
				Loading_compiled_kb_p = Nil;
			    pathname_used_p = Qunbound_in_protected_let;
			    namestring_1 = Qunbound_in_protected_let;
			    read_kb_stream = Qunbound_in_protected_let;
			    PUSH_SPECIAL_WITH_SYMBOL(Read_kb_stream,Qread_kb_stream,read_kb_stream,
				    3);
			      if (PUSH_UNWIND_PROTECT(1)) {
				  pathname_used_p = 
					  SIMPLE_VECTOR_P(namestring_for_file) 
					  ? (EQ(ISVREF(namestring_for_file,
					  (SI_Long)0L),
					  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
					  ? T : Nil) : Qnil;
				  namestring_1 = 
					  SIMPLE_VECTOR_P(namestring_for_file) 
					  && EQ(ISVREF(namestring_for_file,
					  (SI_Long)0L),
					  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
					  ? gensym_namestring(1,
					  namestring_for_file) : 
					  namestring_for_file;
				  Read_kb_stream = 
					  g2_stream_open_for_binary_input(namestring_1);
				  if ( !TRUEP(Read_kb_stream))
				      temp_1 = 
					      reject_gensym_pathname_to_read(namestring_for_file);
				  else {
				      truename_1 = Qunbound_in_protected_let;
				      name_of_kb_being_read = 
					      Qunbound_in_protected_let;
				      namestring_for_kb_being_read = 
					      Qunbound_in_protected_let;
				      name_text_string_for_kb_being_read = 
					      Qunbound_in_protected_let;
				      PUSH_SPECIAL_WITH_SYMBOL(Name_text_string_for_kb_being_read,Qname_text_string_for_kb_being_read,name_text_string_for_kb_being_read,
					      2);
					PUSH_SPECIAL_WITH_SYMBOL(Namestring_for_kb_being_read,Qnamestring_for_kb_being_read,namestring_for_kb_being_read,
						1);
					  PUSH_SPECIAL_WITH_SYMBOL(Name_of_kb_being_read,Qname_of_kb_being_read,name_of_kb_being_read,
						  0);
					    if (PUSH_UNWIND_PROTECT(0)) {
						truename_1 = 
							gensym_truename(gensym_pathname_to_read);
						Name_of_kb_being_read = 
							make_kb_name(truename_1);
						Namestring_for_kb_being_read 
							= 
							gensym_namestring(1,
							truename_1);
						Name_text_string_for_kb_being_read 
							= 
							copy_text_string(Namestring_for_kb_being_read);
						if ( 
							!TRUEP(Do_not_notify_user_during_kb_load_qm)) 
							    {
						    if (clear_kb_qm && 
							    install_system_tables_qm)
							temp_1 = 
								string_constant_19;
						    else if (clear_kb_qm 
							    &&  
							    !TRUEP(install_system_tables_qm))
							temp_1 = 
								string_constant_20;
						    else if ( 
							    !TRUEP(clear_kb_qm) 
							    && 
							    install_system_tables_qm)
							temp_1 = 
								string_constant_21;
						    else if ( 
							    !TRUEP(clear_kb_qm) 
							    &&  
							    !TRUEP(install_system_tables_qm))
							temp_1 = 
								string_constant_22;
						    else
							temp_1 = Qnil;
						    notify_user(2,temp_1,
							    Name_text_string_for_kb_being_read);
						}
						force_process_drawing();
						if (clear_kb_qm)
						    clear_kb(1,T);
						temp_1 = 
							continue_read_kb(module_qm,
							Read_kb_stream,
							gensym_pathname_to_read,
							install_system_tables_qm,
							Reformat_as_appropriate_qm,
							auto_merge_case_qm,
							default_kb_directory_qm,
							Nil);
						Recompile_on_next_load = Nil;
						SAVE_VALUES(VALUES_1(temp_1));
					    }
					    POP_UNWIND_PROTECT(0);
					    if (Name_text_string_for_kb_being_read) 
							{
						if ( 
							!EQ(Name_text_string_for_kb_being_read,
							Qunbound_in_protected_let))
						    reclaim_text_string(Name_text_string_for_kb_being_read);
					    }
					    if (Namestring_for_kb_being_read) {
						if ( 
							!EQ(Namestring_for_kb_being_read,
							Qunbound_in_protected_let))
						    reclaim_text_string(Namestring_for_kb_being_read);
					    }
					    if (Name_of_kb_being_read) {
						if ( 
							!EQ(Name_of_kb_being_read,
							Qunbound_in_protected_let))
						    reclaim_text_string(Name_of_kb_being_read);
					    }
					    if (truename_1) {
						if ( !EQ(truename_1,
							Qunbound_in_protected_let))
						    reclaim_gensym_pathname(truename_1);
					    }
					    CONTINUE_UNWINDING(0);
					    result = RESTORE_VALUES();
					    temp_1 = result;
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				  }
				  SAVE_VALUES(VALUES_1(temp_1));
			      }
			      POP_UNWIND_PROTECT(1);
			      if (Read_kb_stream) {
				  if ( !EQ(Read_kb_stream,
					  Qunbound_in_protected_let))
				      g2_stream_close(Read_kb_stream);
			      }
			      if (namestring_1) {
				  if ( !EQ(namestring_1,
					  Qunbound_in_protected_let)) {
				      if (pathname_used_p)
					  reclaim_text_string(namestring_1);
				  }
			      }
			      CONTINUE_UNWINDING(1);
			      result = RESTORE_VALUES();
			      temp_1 = result;
			    POP_SPECIAL();
			    SAVE_VALUES(VALUES_1(temp_1));
			}
			POP_UNWIND_PROTECT(2);
			if (New_byte_code_body_list) {
			    if ( !EQ(New_byte_code_body_list,
				    Qunbound_in_protected_let))
				reclaim_eval_list_1(New_byte_code_body_list);
			}
			if (New_compiled_byte_code_body_list) {
			    if ( !EQ(New_compiled_byte_code_body_list,
				    Qunbound_in_protected_let))
				reclaim_eval_list_1(New_compiled_byte_code_body_list);
			}
			if (namestring_for_file) {
			    if ( !EQ(namestring_for_file,
				    Qunbound_in_protected_let))
				reclaim_text_string(namestring_for_file);
			}
			CONTINUE_UNWINDING(2);
			result = RESTORE_VALUES();
			result_from_body = result;
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  result_from_body = CATCH_VALUES();
	      POP_CATCH(3);
	      if (Gensym_file_error_occurred_p) {
		  gensymed_symbol = result_from_body;
		  control_string = CAR(gensymed_symbol);
		  error_args = CDR(gensymed_symbol);
		  temp_1 = SYMBOL_FUNCTION(Qtformat_text_string);
		  temp_1 = APPLY_2(temp_1,control_string,error_args);
		  if (result_from_body) {
		      error_arg = Nil;
		      ab_loop_list_ = result_from_body;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      error_arg = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (text_string_p(error_arg))
			  reclaim_text_string(error_arg);
		      goto next_loop;
		    end_loop:
		      reclaim_path_list_1(result_from_body);
		  }
		  report_string = temp_1;
		  notify_user(2,string_constant_13,report_string);
		  reclaim_text_string(report_string);
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = count_and_fix_invalid_items();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Class_name_read_while_reading_current_ghost_definition, Qclass_name_read_while_reading_current_ghost_definition);

DEFINE_VARIABLE_WITH_SYMBOL(Dont_load_if_definitions_have_changed_p, Qdont_load_if_definitions_have_changed_p);

DEFINE_VARIABLE_WITH_SYMBOL(Forward_referenced_format_frames, Qforward_referenced_format_frames);

DEFINE_VARIABLE_WITH_SYMBOL(Preexisting_frames, Qpreexisting_frames);

DEFINE_VARIABLE_WITH_SYMBOL(Plist_from_end_element_qm, Qplist_from_end_element_qm);

/* NOTE-AS-PREEXISTING-FRAME-IF-APPROPRIATE */
Object note_as_preexisting_frame_if_appropriate(frame)
    Object frame;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp;

    x_note_fn_call(132,41);
    if (Loading_kb_p) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !TRUEP(Plist_from_end_element_qm) : TRUEP(Nil)) {
	svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | (SI_Long)8192L;
	ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	Preexisting_frames = gensym_cons_1(frame,Preexisting_frames);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_warnings_p, Qcollecting_warnings_p);

DEFINE_VARIABLE_WITH_SYMBOL(Collected_items_with_warnings_alist, Qcollected_items_with_warnings_alist);

/* COLLECT-WARNING */
Object collect_warning(item,message_type)
    Object item, message_type;
{
    Object a, gensym_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;

    x_note_fn_call(132,42);
    a = assq_function(message_type,Collected_items_with_warnings_alist);
    if ( !TRUEP(a)) {
	a = gensym_cons_1(message_type,Nil);
	Collected_items_with_warnings_alist = gensym_cons_1(a,
		Collected_items_with_warnings_alist);
    }
    gensym_push_modify_macro_arg = item;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = CDR(a);
    cdr_new_value = gensym_cons_1(car_1,cdr_1);
    return VALUES_1(M_CDR(a) = cdr_new_value);
}

/* RECLAIM-COLLECTED-WARNINGS */
Object reclaim_collected_warnings(alist)
    Object alist;
{
    Object l, ab_loop_list_;

    x_note_fn_call(132,43);
    l = Nil;
    ab_loop_list_ = alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    l = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(l);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(alist);
}

Object Earliest_version_to_allow_kb_loading = UNBOUND;

/* SYSTEM-VERSION-MAJOR-DIFFERENCE */
Object system_version_major_difference(system_version_1,system_version_2)
    Object system_version_1, system_version_2;
{
    x_note_fn_call(132,44);
    return VALUES_1(FIXNUM_MINUS(FIRST(system_version_1),
	    FIRST(system_version_2)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Definitions_read_in_this_module, Qdefinitions_read_in_this_module);

static Object Qdefault;            /* default */

static Object Qinitial_plist_for_loaded_module;  /* initial-plist-for-loaded-module */

static Object Qsystem_version;     /* system-version */

static Object list_constant_6;     /* # */

static Object Qtop_level_module;   /* top-level-module */

static Object Qunknown;            /* unknown */

static Object Qtimestamp;          /* timestamp */

static Object string_constant_23;  /* "Invalid KB.  File contents are internally inconsistent." */

static Object Qreinitialize;       /* reinitialize */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qoriginal_kb_state_plist;  /* original-kb-state-plist */

static Object Qreformat;           /* reformat */

static Object Qkb_name;            /* kb-name */

static Object string_constant_24;  /* "Done loading \"~A\"~A" */

static Object string_constant_25;  /* "Done merging \"~A\"" */

static Object string_constant_26;  /* " -- and clearing old KB" */

static Object Qautomerge;          /* automerge */

static Object Qdetail_pane_description;  /* detail-pane-description */

static Object Qnumeric_symbols;    /* numeric-symbols */

static Object Qnumeric;            /* numeric */

static Object Qtype_of_syntactic_anomaly;  /* type-of-syntactic-anomaly */

static Object Qclass_definition;   /* class-definition */

static Object string_constant_27;  /* "\"~A\" cannot be loaded because it was created ~
				    *                     with a newer version of G2 than this one"
				    */

static Object string_constant_28;  /* "File \"~A\" is not a KB or lacks a proper KB header" */

static Object string_constant_29;  /* "\"~A\" cannot be loaded because it was saved in G2 " */

static Object string_constant_30;  /* ". The KB must be saved in G2 " */

static Object string_constant_31;  /* " or later in order to be loaded in this version of G2 (" */

static Object string_constant_32;  /* ")." */

static Object string_constant_33;  /* "READING HAS FAILED -- UNABLE TO PROCEED!" */

static Object Qpost_load;          /* post-load */

static Object Qautomerge2;         /* automerge2 */

static Object Qpost_load2;         /* post-load2 */

static Object Qrevert;             /* revert */

static Object Qfinished;           /* finished */

static Object Qpath;               /* path */

/* CONTINUE-READ-KB */
Object continue_read_kb(module_qm,read_kb_stream,gensym_pathname_to_read,
	    main_kb_being_read_qm,reformat_as_appropriate_qm,
	    auto_merge_case_qm,default_kb_directory_qm,xml_object_qm)
    Object module_qm, read_kb_stream, gensym_pathname_to_read;
    Object main_kb_being_read_qm, reformat_as_appropriate_qm;
    Object auto_merge_case_qm, default_kb_directory_qm, xml_object_qm;
{
    Object reading_kb_p;
    volatile Object reading_succeeded_qm;
    Object definitions_read_in_this_module, discrepancy_with_system_time1_p;
    Object discrepancy_with_system_time2_p, separate_imminent_actions_p;
    Object defer_notifications_qm, forward_referenced_format_frames;
    Object record_class_name_conflicts_qm;
    volatile Object kb_state_changes_for_module_being_read_qm;
    Object kb_object_index_space;
    volatile Object plist_from_initial_element_qm;
    Object name_of_module_being_read_qm, system_version_qm;
    volatile Object flag_in_kb_is_higher_than_g2_kb_flag_qm;
    volatile Object timestamp_qm;
    Object kb_file_progress, class_name_conflicts;
    Object blocks_to_delete_after_reading_kb;
    Object connections_to_delete_after_reading_kb, blocks_with_bad_connections;
    Object refresh_all_windows_after_merging_qm, new_saved_kb_format_p;
    Object kb_uses_crlf_p, plist_has_been_checked_p;
    Object original_kb_state_plist_written_qm, previous_timestamp_qm;
    Object file_length_qm;
    volatile Object local_kb_flags_from_last_kb_read;
    volatile Object local_system_version_from_last_kb_read;
    Object frame_serial_number_map;
    volatile Object blocks_to_activate_unless_reset;
    volatile Object frame_serial_number_for_blocks_to_activate;
    Object do_not_note_permanent_changes_p;
    volatile Object value_of_read_kb;
    volatile Object dot_unwind_abort_dot;
    Object current_frame_serial_number_before_reading, loading_kb_p;
    Object suppress_updating_of_slot_value_representations_qm;
    Object system_version_from_kb_being_read, system_quality_from_last_kb_read;
    Object system_revision_from_last_kb_read, kb_flags;
    Object deferred_class_definitions_alist, frames_with_substitute_classes;
    Object number_of_kb_lines_so_far, number_of_kb_characters_so_far_qm;
    Object next_character_for_kb_qm, read_kb_buffer_length;
    Object read_kb_buffer_index, plist_from_end_element_qm, preexisting_frames;
    Object base_reference, type_of_file_being_read, backup_case_qm;
    Object system_tables_read_for_this_module, comment_string_or_t_qm, temp_1;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ws, char_1, temp_2, frame;
    Object ab_loop_list_, gensymed_symbol, frame_serial_number_setf_arg, old;
    Object new_1, temp_4, frame_1, sub_vector_qm, function_qm;
    Object frame_serial_number_before_deleting;
    Object collect_kb_state_changes_for_module_qm, collecting_warnings_p;
    Object collected_items_with_warnings_alist, ab_sparse_array_;
    Object ab_vector_stack_, ab_next_value_qm_, kb_object, vector_1, x2, xa;
    Object ya, gensymed_symbol_1, sub_class_bit_vector;
    volatile Object earlier_p;
    volatile Object encrypted_timestamp;
    Object field;
    volatile Object decrypted_timestamp_qm;
    Object decrypted_time_qm, timestamp_qm_1, encoded_timestamp_field;
    Object timestamp_field_qm;
    volatile Object rotator_specs;
    Object rotator, offset, ab_loop_list__1, ab_loop_desetq_;
    Object logrotate_in_place_arg_1, logrotate_in_place_arg_2;
    volatile Object filled_timestamp_field_components;
    Object key, ab_loopvar__2, ab_loop_iter_flag_, component, rotator_spec;
    Object circularity_point, raw_field, timestamp_field, raw_field_list;
    Object time_1, old_value_qm, timestamp, fix_time, timestamp_cons;
    Object encrypted_timestamp_field, rotator_list, complete_name_from_kb_qm;
    Object compiled_function, byte_code_body, symbol, definition;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string, kb_flags_from_last_kb_read;
    Object system_version_from_last_kb_read, checksum_qm, ab_queue_form_;
    Object ab_next_queue_element_, subblock, frame_reference_serial_number;
    Object workstation, path_pop_store, cons_1, next_cons, svref_arg_2, block;
    SI_Long temp_3, method_index, ab_next_vector_index_, vector_length, i;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long ab_loop_repeat_, index_1, shift_amount, ab_loop_repeat__1;
    SI_Long offset_1, logrotate_in_place_arg_2_1, bv16_length, aref_new_value;
    SI_Long length_1;
    char temp, new_algorithm_qm, after_pkg_authorization_qm;
    double temp_5, temp_6, universal_time;
    Declare_stack_pointer;
    Declare_catch(5);
    Declare_special(48);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(132,45);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    47);
      PUSH_SPECIAL_WITH_SYMBOL(Main_kb_being_read_qm,Qmain_kb_being_read_qm,main_kb_being_read_qm,
	      46);
	PUSH_SPECIAL_WITH_SYMBOL(Read_kb_stream,Qread_kb_stream,read_kb_stream,
		45);
	  reading_kb_p = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Reading_kb_p,Qreading_kb_p,reading_kb_p,44);
	    reading_succeeded_qm = Nil;
	    definitions_read_in_this_module = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Definitions_read_in_this_module,Qdefinitions_read_in_this_module,definitions_read_in_this_module,
		    43);
	      discrepancy_with_system_time1_p = path_list_2(Nil,Nil);
	      discrepancy_with_system_time2_p = path_cons_1(Nil,
		      CDR(discrepancy_with_system_time1_p));
	      separate_imminent_actions_p = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Separate_imminent_actions_p,Qseparate_imminent_actions_p,separate_imminent_actions_p,
		      42);
		defer_notifications_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
			41);
		  forward_referenced_format_frames = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Forward_referenced_format_frames,Qforward_referenced_format_frames,forward_referenced_format_frames,
			  40);
		    record_class_name_conflicts_qm = EQ(auto_merge_case_qm,
			    Qdefault) ? 
			    Automatically_resolve_conflicts_by_default : 
			    auto_merge_case_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Record_class_name_conflicts_qm,Qrecord_class_name_conflicts_qm,record_class_name_conflicts_qm,
			    39);
		      kb_state_changes_for_module_being_read_qm = Nil;
		      kb_object_index_space = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Kb_object_index_space,Qkb_object_index_space,kb_object_index_space,
			      38);
			plist_from_initial_element_qm = Nil;
			name_of_module_being_read_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Name_of_module_being_read_qm,Qname_of_module_being_read_qm,name_of_module_being_read_qm,
				37);
			  system_version_qm = Nil;
			  flag_in_kb_is_higher_than_g2_kb_flag_qm = Nil;
			  timestamp_qm = Nil;
			  kb_file_progress = 
				  Kb_file_progress_is_currently_for_modules_p 
				  ? 
				  Current_kb_file_progress_for_modules_qm :
				   Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Kb_file_progress,Qkb_file_progress,kb_file_progress,
				  36);
			    class_name_conflicts = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Class_name_conflicts,Qclass_name_conflicts,class_name_conflicts,
				    35);
			      blocks_to_delete_after_reading_kb = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Blocks_to_delete_after_reading_kb,Qblocks_to_delete_after_reading_kb,blocks_to_delete_after_reading_kb,
				      34);
				connections_to_delete_after_reading_kb = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Connections_to_delete_after_reading_kb,Qconnections_to_delete_after_reading_kb,connections_to_delete_after_reading_kb,
					33);
				  blocks_with_bad_connections = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Blocks_with_bad_connections,Qblocks_with_bad_connections,blocks_with_bad_connections,
					  32);
				    refresh_all_windows_after_merging_qm = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Refresh_all_windows_after_merging_qm,Qrefresh_all_windows_after_merging_qm,refresh_all_windows_after_merging_qm,
					    31);
				      new_saved_kb_format_p = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(New_saved_kb_format_p,Qnew_saved_kb_format_p,new_saved_kb_format_p,
					      30);
					kb_uses_crlf_p = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Kb_uses_crlf_p,Qkb_uses_crlf_p,kb_uses_crlf_p,
						29);
					  plist_has_been_checked_p = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Plist_has_been_checked_p,Qplist_has_been_checked_p,plist_has_been_checked_p,
						  28);
					    original_kb_state_plist_written_qm 
						    = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Original_kb_state_plist_written_qm,Qoriginal_kb_state_plist_written_qm,original_kb_state_plist_written_qm,
						    27);
					      previous_timestamp_qm = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Previous_timestamp_qm,Qprevious_timestamp_qm,previous_timestamp_qm,
						      26);
						file_length_qm =  
							!TRUEP(xml_object_qm) 
							? 
							g2_stream_file_length(Read_kb_stream) 
							: Nil;
						local_kb_flags_from_last_kb_read 
							= Nil;
						local_system_version_from_last_kb_read 
							= Nil;
						frame_serial_number_map = Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Frame_serial_number_map,Qframe_serial_number_map,frame_serial_number_map,
							25);
						  blocks_to_activate_unless_reset 
							  = Nil;
						  frame_serial_number_for_blocks_to_activate 
							  = Nil;
						  do_not_note_permanent_changes_p 
							  = T;
						  PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
							  24);
						    value_of_read_kb = Nil;
						    dot_unwind_abort_dot = T;
						    Defer_notifications_qm = T;
						    reclaim_items_deleted_since_load_or_save();
						    current_frame_serial_number_before_reading 
							    = 
							    copy_frame_serial_number(Current_frame_serial_number);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_serial_number_before_reading,Qcurrent_frame_serial_number_before_reading,current_frame_serial_number_before_reading,
							    23);
						      if (PUSH_UNWIND_PROTECT(4)) 
								  {
							  loading_kb_p = T;
							  PUSH_SPECIAL_WITH_SYMBOL(Loading_kb_p,Qloading_kb_p,loading_kb_p,
								  22);
							    suppress_updating_of_slot_value_representations_qm 
								    = T;
							    PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
								    21);
							      system_version_from_kb_being_read 
								      = Nil;
							      PUSH_SPECIAL_WITH_SYMBOL(System_version_from_kb_being_read,Qsystem_version_from_kb_being_read,system_version_from_kb_being_read,
								      20);
								system_quality_from_last_kb_read 
									= Nil;
								PUSH_SPECIAL_WITH_SYMBOL(System_quality_from_last_kb_read,Qsystem_quality_from_last_kb_read,system_quality_from_last_kb_read,
									19);
								  system_revision_from_last_kb_read 
									  = 
									  Nil;
								  PUSH_SPECIAL_WITH_SYMBOL(System_revision_from_last_kb_read,Qsystem_revision_from_last_kb_read,system_revision_from_last_kb_read,
									  18);
								    kb_flags 
									    = 
									    Kb_flags;
								    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,
									    17);
								      deferred_class_definitions_alist 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Deferred_class_definitions_alist,Qdeferred_class_definitions_alist,deferred_class_definitions_alist,
									      16);
									frames_with_substitute_classes 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Frames_with_substitute_classes,Qframes_with_substitute_classes,frames_with_substitute_classes,
										15);
									  number_of_kb_lines_so_far 
										  = 
										  FIX((SI_Long)0L);
									  PUSH_SPECIAL_WITH_SYMBOL(Number_of_kb_lines_so_far,Qnumber_of_kb_lines_so_far,number_of_kb_lines_so_far,
										  14);
									    number_of_kb_characters_so_far_qm 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Number_of_kb_characters_so_far_qm,Qnumber_of_kb_characters_so_far_qm,number_of_kb_characters_so_far_qm,
										    13);
									      next_character_for_kb_qm 
										      = 
										      Nil;
									      PUSH_SPECIAL_WITH_SYMBOL(Next_character_for_kb_qm,Qnext_character_for_kb_qm,next_character_for_kb_qm,
										      12);
										read_kb_buffer_length 
											= 
											FIX((SI_Long)0L);
										PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_length,Qread_kb_buffer_length,read_kb_buffer_length,
											11);
										  read_kb_buffer_index 
											  = 
											  FIX((SI_Long)0L);
										  PUSH_SPECIAL_WITH_SYMBOL(Read_kb_buffer_index,Qread_kb_buffer_index,read_kb_buffer_index,
											  10);
										    plist_from_end_element_qm 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Plist_from_end_element_qm,Qplist_from_end_element_qm,plist_from_end_element_qm,
											    9);
										      preexisting_frames 
											      = 
											      Nil;
										      PUSH_SPECIAL_WITH_SYMBOL(Preexisting_frames,Qpreexisting_frames,preexisting_frames,
											      8);
											base_reference 
												= 
												Nil;
											PUSH_SPECIAL_WITH_SYMBOL(Base_reference,Qbase_reference,base_reference,
												7);
											  type_of_file_being_read 
												  = 
												  Nil;
											  PUSH_SPECIAL_WITH_SYMBOL(Type_of_file_being_read,Qtype_of_file_being_read,type_of_file_being_read,
												  6);
											    backup_case_qm 
												    = 
												    Nil;
											    PUSH_SPECIAL_WITH_SYMBOL(Backup_case_qm,Qbackup_case_qm,backup_case_qm,
												    5);
											      system_tables_read_for_this_module 
												      = 
												      Nil;
											      PUSH_SPECIAL_WITH_SYMBOL(System_tables_read_for_this_module,Qsystem_tables_read_for_this_module,system_tables_read_for_this_module,
												      4);
												comment_string_or_t_qm 
													= 
													Nil;
												Kb_object_index_space 
													= 
													make_index_space_1(Nil,
													Nil);
												temp 
													= 
													TRUEP(xml_object_qm);
												if (temp);
												else {
												    comment_string_or_t_qm 
													    = 
													    read_format_identifier_for_kb();
												    temp 
													    = 
													    TRUEP(comment_string_or_t_qm);
												}
												if ( 
													!temp)
												    abort_on_bad_kb(0);
												if ( 
													!TRUEP(text_string_p(comment_string_or_t_qm)))
												    comment_string_or_t_qm 
													    = 
													    Nil;
												if (xml_object_qm)
												    plist_from_initial_element_qm 
													    = 
													    Nil;
												else if (Plist_has_been_checked_p) 
													    {
												    if (module_qm) 
														{
													temp_1 
														= 
														getfq_function_no_default(INLINE_SYMBOL_PLIST(module_qm),
														Qinitial_plist_for_loaded_module);
													mutate_global_property(module_qm,
														Nil,
														Qinitial_plist_for_loaded_module);
													plist_from_initial_element_qm 
														= 
														temp_1;
												    }
												    else
													plist_from_initial_element_qm 
														= 
														Nil;
												}
												else
												    plist_from_initial_element_qm 
													    = 
													    read_initial_plist_for_kb(1,
													    comment_string_or_t_qm);
												Type_of_file_being_read 
													= 
													getf(plist_from_initial_element_qm,
													Qtype_of_file,
													_);
												prepare_to_read_snapshot_if_appropriate(plist_from_initial_element_qm);
												prepare_to_read_backup_if_appropriate(plist_from_initial_element_qm);
												if (System_has_paused 
													|| 
													System_is_running)
												    reclaim_all_indexed_attribute_hash_tables();
												read_kb_detail_2(plist_from_initial_element_qm);
												system_version_qm 
													= 
													getf(plist_from_initial_element_qm,
													Qsystem_version,
													_);
												System_version_from_kb_being_read 
													= 
													system_version_qm 
													&& 
													 
													!EQ(system_version_qm,
													FIX((SI_Long)0L)) 
													?
													 
													system_version_qm 
													:
													 list_constant_6;
												result = get_quality_and_revision_of_system_version(System_version_from_kb_being_read);
												MVS_2(result,
													System_quality_from_last_kb_read,
													System_revision_from_last_kb_read);
												local_system_version_from_last_kb_read 
													= 
													copy_for_slot_value(System_version_from_kb_being_read);
												if ( 
													!(xml_object_qm 
													|| 
													Plist_has_been_checked_p)) 
													    {
												    temp_1 
													    = 
													    getf(plist_from_initial_element_qm,
													    Qkb_flags,
													    _);
												    if (temp_1);
												    else
													temp_1 
														= 
														FIX((SI_Long)0L);
												    Kb_flags 
													    = 
													    temp_1;
												    new_algorithm_qm 
													    = 
													    IFIX(Kb_flags) 
													    >= 
													    (SI_Long)219L;
												    scope_conses 
													    = 
													    Scope_conses;
												    ab_loopvar_ 
													    = 
													    Nil;
												    ab_loopvar__1 
													    = 
													    Nil;
												    ws 
													    = 
													    Nil;
												    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
													    0);
												      ab_loopvar_ 
													      = 
													      collect_subclasses(Qkb_workspace);
												    next_loop:
												      if ( 
													      !TRUEP(ab_loopvar__1)) 
														  {
													next_loop_1:
													  if ( 
														  !TRUEP(ab_loopvar_))
													      goto end_loop;
													  ab_loopvar__1 
														  = 
														  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
														  Instances_specific_to_this_class_kbprop);
													  ab_loopvar_ 
														  = 
														  M_CDR(ab_loopvar_);
													  if (ab_loopvar__1)
													      goto end_loop;
													  goto next_loop_1;
													end_loop:
													  temp 
														  = 
														   
														  !TRUEP(ab_loopvar__1);
												      }
												      else
													  temp 
														  = 
														  TRUEP(Nil);
												      if (temp)
													  goto end_loop_1;
												      ws 
													      = 
													      ab_loopvar__1;
												      ab_loopvar__1 
													      = 
													      ISVREF(ab_loopvar__1,
													      (SI_Long)6L);
												      normalize_kb_workspace(ws,
													      new_algorithm_qm 
													      ?
													       
													      T : Nil);
												      goto next_loop;
												    end_loop_1:;
												    POP_SPECIAL();
												    flag_in_kb_is_higher_than_g2_kb_flag_qm 
													    = 
													     
													    !TRUEP(Ignore_kb_flags_in_kbs_qm) 
													    ?
													     
													    (FIXNUM_GT(Kb_flags,
													    Kb_flags_of_software) 
													    ?
													     
													    T 
													    :
													     Nil) : Nil;
												}
												Name_of_module_being_read_qm 
													= 
													getf(plist_from_initial_element_qm,
													Qtop_level_module,
													_);
												if (Name_of_module_being_read_qm)
												    mutate_kb_specific_property_value(Name_of_module_being_read_qm,
													    Qunknown,
													    Module_is_writable_p_kbprop);
												if ( 
													!TRUEP(flag_in_kb_is_higher_than_g2_kb_flag_qm)) 
													    {
												    temp 
													    = 
													    TRUEP(xml_object_qm);
												    if (temp);
												    else
													temp 
														= 
														TRUEP(Plist_has_been_checked_p);
												    if (temp);
												    else {
													timestamp_qm 
														= 
														getf(plist_from_initial_element_qm,
														Qtimestamp,
														_);
													temp 
														= 
														timestamp_qm 
														?
														 
														 
														!TRUEP(system_version_greater_p(Earliest_version_to_allow_kb_loading,
														local_system_version_from_last_kb_read)) 
														:
														 
														TRUEP(Qnil);
												    }
												}
												else
												    temp 
													    = 
													    TRUEP(Nil);
												if (temp) 
													    {
												    if ( 
													    !TRUEP(Kb_file_progress)) 
														{
													temp_1 
														= 
														copy_text_string(Name_text_string_for_kb_being_read);
													Kb_file_progress 
														= 
														put_up_file_progress_display(8,
														T,
														file_length_qm,
														temp_1,
														Nil,
														Nil,
														Nil,
														Nil,
														Name_of_module_being_read_qm);
													if (Kb_file_progress_is_currently_for_modules_p)
													    Current_kb_file_progress_for_modules_qm 
														    = 
														    Kb_file_progress;
												    }
												    else {
													temp_1 
														= 
														copy_text_string(Name_text_string_for_kb_being_read);
													put_up_file_progress_display(8,
														T,
														file_length_qm,
														temp_1,
														Nil,
														Nil,
														Nil,
														Kb_file_progress,
														Name_of_module_being_read_qm);
												    }
												    if (ISVREF(Kb_file_progress,
													    (SI_Long)23L))
													Number_of_kb_characters_so_far_qm 
														= 
														FIX((SI_Long)0L);
												    local_kb_flags_from_last_kb_read 
													    = 
													    Kb_flags;
												    if ( 
													    !(xml_object_qm 
													    || 
													    Plist_has_been_checked_p)) 
														{
													char_1 
														= 
														read_char_for_kb_past_spaces();
													if ( 
														!CHAR_EQ(char_1,
														CHR('*'))) 
														    {
													    temp_2 
														    = 
														    FIXNUM_SUB1(Read_kb_buffer_index);
													    Read_kb_buffer_index 
														    = 
														    temp_2;
													}
													else {
													    if ( 
														    !TRUEP(Read_kb_buffer_index))
														char_1 
															= 
															Nil;
													    else if (FIXNUM_LT(Read_kb_buffer_index,
														    Read_kb_buffer_length)) 
															{
														temp_1 
															= 
															SCHAR(Read_kb_buffer,
															Read_kb_buffer_index);
														temp_2 
															= 
															FIXNUM_ADD1(Read_kb_buffer_index);
														Read_kb_buffer_index 
															= 
															temp_2;
														char_1 
															= 
															temp_1;
													    }
													    else
														char_1 
															= 
															read_next_char_for_kb_from_refilled_buffer();
													    if ( 
														    !(CHAR_EQ(char_1,
														    CHR('1')) 
														    || 
														    CHAR_EQ(char_1,
														    CHR('3'))))
														abort_on_bad_kb(1,
															char_1);
													    read_ghost_definitions();
													    if (Dont_load_if_definitions_have_changed_p 
														    && 
														    Class_name_conflicts)
														terminate_load_when_definitions_have_changed();
													}
												    }
												    if (xml_object_qm) 
														{
													Some_module_is_clear_text_p 
														= 
														T;
													reading_succeeded_qm 
														= 
														read_clear_text_module_from_xml_object(xml_object_qm,
														auto_merge_case_qm);
												    }
												    else if (Plist_has_been_checked_p) 
														{
													Some_module_is_clear_text_p 
														= 
														T;
													reading_succeeded_qm 
														= 
														read_clear_text_module(gensym_pathname_to_read,
														auto_merge_case_qm);
												    }
												    else {
													read_all_top_level_kb_elements();
													set_up_modules_and_system_tables_a_list_after_reading();
												    }
												    if ( 
													    !(xml_object_qm 
													    || 
													    Plist_has_been_checked_p)) 
														{
													Plist_from_end_element_qm 
														= 
														read_element_for_kb(T);
													update_file_progress_display_for_newline_in_kb(1,
														T);
												    }
												    if (Name_of_module_being_read_qm)
													note_crlf_use_in_module_or_file(Name_of_module_being_read_qm,
														Kb_uses_crlf_p);
												    Original_kb_state_plist_written_qm 
													    = 
													    getf(Plist_from_end_element_qm,
													    Qoriginal_kb_state_plist_written_qm,
													    _);
												    if (Deferred_class_definitions_alist)
													install_deferred_class_definitions();
												    frame 
													    = 
													    Nil;
												    ab_loop_list_ 
													    = 
													    Preexisting_frames;
												  next_loop_2:
												    if ( 
													    !TRUEP(ab_loop_list_))
													goto end_loop_2;
												    frame 
													    = 
													    M_CAR(ab_loop_list_);
												    ab_loop_list_ 
													    = 
													    M_CDR(ab_loop_list_);
												    if ((SI_Long)0L 
													    != 
													    (IFIX(ISVREF(frame,
													    (SI_Long)5L)) 
													    & 
													    (SI_Long)8192L)) 
														{
													gensymed_symbol 
														= 
														ISVREF(frame,
														(SI_Long)3L);
													temp 
														= 
														 
														!(FIXNUMP(gensymed_symbol) 
														?
														 
														IFIX(gensymed_symbol) 
														== 
														(SI_Long)-1L 
														:
														 
														TRUEP(Nil));
												    }
												    else
													temp 
														= 
														TRUEP(Nil);
												    if (temp) 
														{
													frame_serial_number_setf_arg 
														= 
														increment_current_frame_serial_number();
													old 
														= 
														ISVREF(frame,
														(SI_Long)3L);
													new_1 
														= 
														frame_serial_number_setf_arg;
													temp_2 
														= 
														(FIXNUMP(old) 
														|| 
														 
														!TRUEP(old)) 
														&& 
														(FIXNUMP(new_1) 
														|| 
														 
														!TRUEP(new_1)) 
														?
														 
														new_1 
														:
														 
														frame_serial_number_setf_helper_1(old,
														new_1);
													ISVREF(frame,
														(SI_Long)3L) 
														= 
														temp_2;
													temp_3 
														= 
														IFIX(ISVREF(frame,
														(SI_Long)5L)) 
														& 
														 
														~
														(SI_Long)8192L;
													ISVREF(frame,
														(SI_Long)5L) 
														= 
														FIX(temp_3);
													if (EQ(frame,
														Current_logbook_qm)) 
														    {
													    frame_serial_number_setf_arg 
														    = 
														    ISVREF(frame,
														    (SI_Long)3L);
													    temp_2 
														    = 
														    (FIXNUMP(Current_logbook_serial_number_qm) 
														    || 
														     
														    !TRUEP(Current_logbook_serial_number_qm)) 
														    && 
														    (FIXNUMP(frame_serial_number_setf_arg) 
														    || 
														     
														    !TRUEP(frame_serial_number_setf_arg)) 
														    ?
														     
														    frame_serial_number_setf_arg 
														    :
														     
														    frame_serial_number_setf_helper_1(Current_logbook_serial_number_qm,
														    frame_serial_number_setf_arg);
													    Current_logbook_serial_number_qm 
														    = 
														    temp_2;
													}
												    }
												    goto next_loop_2;
												  end_loop_2:;
												    reclaim_gensym_list_1(Preexisting_frames);
												    if ((xml_object_qm 
													    || 
													    Plist_has_been_checked_p) 
													    && 
													     
													    !TRUEP(reading_succeeded_qm));
												    else {
													temp 
														= 
														TRUEP(xml_object_qm);
													if (temp);
													else
													    temp 
														    = 
														    TRUEP(Plist_has_been_checked_p);
													if (temp);
													else {
													    temp_4 
														    = 
														    read_element_for_kb(T);
													    temp_1 
														    = 
														    add1(ISVREF(Kb_object_index_space,
														    (SI_Long)3L));
													    temp 
														    = 
														    NUM_EQ(temp_4,
														    temp_1);
													}
													if ( 
														!temp)
													    notify_user(1,
														    string_constant_23);
													else {
													    Loading_kb_p 
														    = 
														    Nil;
													    Suppress_updating_of_slot_value_representations_qm 
														    = 
														    Nil;
													    frame 
														    = 
														    Nil;
													    ab_loop_list_ 
														    = 
														    Frames_with_substitute_classes;
													  next_loop_3:
													    if ( 
														    !TRUEP(ab_loop_list_))
														goto end_loop_3;
													    frame 
														    = 
														    M_CAR(ab_loop_list_);
													    ab_loop_list_ 
														    = 
														    M_CDR(ab_loop_list_);
													    method_index 
														    = 
														    (SI_Long)20L;
													    frame_1 
														    = 
														    frame;
													    sub_vector_qm 
														    = 
														    ISVREF(ISVREF(ISVREF(frame_1,
														    (SI_Long)1L),
														    (SI_Long)11L),
														    method_index);
													    function_qm 
														    = 
														    sub_vector_qm 
														    ?
														     
														    ISVREF(sub_vector_qm,
														    (SI_Long)1L) 
														    :
														     
														    Nil;
													    if (function_qm)
														inline_funcall_1(function_qm,
															frame_1);
													    goto next_loop_3;
													  end_loop_3:
													    reclaim_gensym_list_1(Frames_with_substitute_classes);
													    Frames_with_substitute_classes 
														    = 
														    Nil;
													    frame_serial_number_before_deleting 
														    = 
														    copy_frame_serial_number(Current_frame_serial_number);
													    collect_kb_state_changes_for_module_qm 
														    = 
														    Original_kb_state_plist_written_qm 
														    ?
														     
														    ( 
														    !TRUEP(Warmbooting_qm) 
														    ?
														     
														    T 
														    :
														     Nil) : Qnil;
													    frame_serial_number_for_blocks_to_activate 
														    = 
														    copy_frame_serial_number(frame_serial_number_before_deleting);
													    delete_blocks_and_connections_to_be_deleted_after_reading();
													    update_file_progress_display_after_reading(Kb_file_progress,
														    Qreinitialize);
													    collecting_warnings_p 
														    = 
														    T;
													    collected_items_with_warnings_alist 
														    = 
														    Nil;
													    PUSH_SPECIAL_WITH_SYMBOL(Collected_items_with_warnings_alist,Qcollected_items_with_warnings_alist,collected_items_with_warnings_alist,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Collecting_warnings_p,Qcollecting_warnings_p,collecting_warnings_p,
														      2);
														if (New_saved_kb_format_p) 
															    {
														    do_not_note_permanent_changes_p 
															    = 
															    T;
														    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
															    1);
														      scope_conses 
															      = 
															      Scope_conses;
														      ab_sparse_array_ 
															      = 
															      Frame_serial_number_map;
														      ab_vector_stack_ 
															      = 
															      Nil;
														      ab_next_vector_index_ 
															      = 
															      (SI_Long)0L;
														      ab_next_value_qm_ 
															      = 
															      Nil;
														      kb_object 
															      = 
															      Nil;
														      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
															      0);
															ab_vector_stack_ 
																= 
																collect_leaf_vectors(ISVREF(ab_sparse_array_,
																(SI_Long)3L),
																ISVREF(ab_sparse_array_,
																(SI_Long)2L));
														      next_loop_4:
															ab_next_value_qm_ 
																= 
																Nil;
															vector_1 
																= 
																Nil;
															vector_length 
																= 
																(SI_Long)0L;
														      next_loop_5:
															if ( 
																!TRUEP(ab_vector_stack_))
															    goto end_loop_4;
															vector_1 
																= 
																M_CAR(ab_vector_stack_);
															vector_length 
																= 
																IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
														      next_loop_6:
															if ( 
																!(ab_next_vector_index_ 
																< 
																vector_length))
															    goto end_loop_5;
															ab_next_value_qm_ 
																= 
																ISVREF(vector_1,
																ab_next_vector_index_);
															ab_next_vector_index_ 
																= 
																ab_next_vector_index_ 
																+ 
																(SI_Long)1L;
															if (ab_next_value_qm_)
															    goto end_find_value;
															goto next_loop_6;
														      end_loop_5:
															ab_next_vector_index_ 
																= 
																(SI_Long)0L;
															ab_vector_stack_ 
																= 
																M_CDR(ab_vector_stack_);
															goto next_loop_5;
														      end_loop_4:
														      end_find_value:;
															if ( 
																!TRUEP(ab_next_value_qm_))
															    goto end_loop_6;
															kb_object 
																= 
																ab_next_value_qm_;
															if (SIMPLE_VECTOR_P(kb_object) 
																&& 
																IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(kb_object)) 
																> 
																(SI_Long)2L 
																&& 
																 
																!EQ(ISVREF(kb_object,
																(SI_Long)1L),
																Qavailable_frame_vector)) 
																    {
															    x2 
																    = 
																    ISVREF(kb_object,
																    (SI_Long)1L);
															    temp 
																    = 
																    SIMPLE_VECTOR_P(x2) 
																    && 
																    EQ(ISVREF(x2,
																    (SI_Long)0L),
																    Qg2_defstruct_structure_name_class_description_g2_struct) 
																    ?
																     
																    TRUEP(x2) 
																    :
																     
																    TRUEP(Qnil);
															}
															else
															    temp 
																    = 
																    TRUEP(Nil);
															if (temp) 
																    {
															    gensymed_symbol 
																    = 
																    ISVREF(kb_object,
																    (SI_Long)3L);
															    temp 
																    = 
																    SIMPLE_VECTOR_P(kb_object) 
																    ?
																     
																    EQ(ISVREF(kb_object,
																    (SI_Long)1L),
																    Qavailable_frame_vector) 
																    :
																     
																    TRUEP(Qnil);
															    if (temp);
															    else
																temp 
																	= 
																	FIXNUMP(gensymed_symbol) 
																	?
																	 
																	IFIX(gensymed_symbol) 
																	== 
																	(SI_Long)-1L 
																	:
																	 
																	TRUEP(Nil);
															    if (temp);
															    else if (FIXNUMP(frame_serial_number_before_deleting))
																temp 
																	= 
																	FIXNUMP(gensymed_symbol) 
																	?
																	 
																	FIXNUM_LT(frame_serial_number_before_deleting,
																	gensymed_symbol) 
																	:
																	 
																	TRUEP(T);
															    else if (FIXNUMP(gensymed_symbol))
																temp 
																	= 
																	TRUEP(Nil);
															    else {
																xa 
																	= 
																	M_CAR(frame_serial_number_before_deleting);
																ya 
																	= 
																	M_CAR(gensymed_symbol);
																temp 
																	= 
																	FIXNUM_LT(xa,
																	ya);
																if (temp);
																else
																    temp 
																	    = 
																	    FIXNUM_EQ(xa,
																	    ya) 
																	    ?
																	     
																	    FIXNUM_LT(M_CDR(frame_serial_number_before_deleting),
																	    M_CDR(gensymed_symbol)) 
																	    :
																	     
																	    TRUEP(Qnil);
															    }
															    temp 
																    = 
																     
																    !temp;
															}
															else
															    temp 
																    = 
																    TRUEP(Nil);
															if (temp) 
																    {
															    if (block_needs_activation_upon_reading_p(kb_object))
																blocks_to_activate_unless_reset 
																	= 
																	gensym_cons_1(kb_object,
																	blocks_to_activate_unless_reset);
															    gensymed_symbol 
																    = 
																    ISVREF(ISVREF(ISVREF(ISVREF(kb_object,
																    (SI_Long)1L),
																    (SI_Long)11L),
																    (SI_Long)4L),
																    (SI_Long)1L);
															    gensymed_symbol_1 
																    = 
																    kb_object;
															    inline_funcall_1(gensymed_symbol,
																    gensymed_symbol_1);
															    if (collect_kb_state_changes_for_module_qm 
																    && 
																    get_lookup_slot_value_given_default(kb_object,
																    Qoriginal_kb_state_plist,
																    Nil))
																kb_state_changes_for_module_being_read_qm 
																	= 
																	gensym_cons_1(kb_object,
																	kb_state_changes_for_module_being_read_qm);
															}
															goto next_loop_4;
														      end_loop_6:;
														      POP_SPECIAL();
														    POP_SPECIAL();
														}
														else {
														    do_not_note_permanent_changes_p 
															    = 
															    T;
														    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
															    0);
														      i 
															      = 
															      (SI_Long)0L;
														      ab_loop_bind_ 
															      = 
															      IFIX(ISVREF(Kb_object_index_space,
															      (SI_Long)3L));
														      kb_object 
															      = 
															      Nil;
														    next_loop_7:
														      if (i 
															      > 
															      ab_loop_bind_)
															  goto end_loop_7;
														      if (i 
															      >= 
															      IFIX(ISVREF(Kb_object_index_space,
															      (SI_Long)4L)))
															  enlarge_index_space(Kb_object_index_space,
																  FIX(i));
														      kb_object 
															      = 
															      ISVREF(ISVREF(ISVREF(Kb_object_index_space,
															      (SI_Long)2L),
															      i 
															      >> 
															       
															      - 
															       
															      - 
															      (SI_Long)10L),
															      i 
															      & 
															      (SI_Long)1023L);
														      if (SIMPLE_VECTOR_P(kb_object) 
															      && 
															      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(kb_object)) 
															      > 
															      (SI_Long)2L 
															      && 
															       
															      !EQ(ISVREF(kb_object,
															      (SI_Long)1L),
															      Qavailable_frame_vector)) 
																  {
															  x2 
																  = 
																  ISVREF(kb_object,
																  (SI_Long)1L);
															  temp 
																  = 
																  SIMPLE_VECTOR_P(x2) 
																  && 
																  EQ(ISVREF(x2,
																  (SI_Long)0L),
																  Qg2_defstruct_structure_name_class_description_g2_struct) 
																  ?
																   
																  TRUEP(x2) 
																  :
																   
																  TRUEP(Qnil);
														      }
														      else
															  temp 
																  = 
																  TRUEP(Nil);
														      if (temp) 
																  {
															  sub_class_bit_vector 
																  = 
																  ISVREF(ISVREF(kb_object,
																  (SI_Long)1L),
																  (SI_Long)19L);
															  superior_class_bit_number 
																  = 
																  IFIX(ISVREF(Block_class_description,
																  (SI_Long)18L));
															  sub_class_vector_index 
																  = 
																  superior_class_bit_number 
																  >> 
																   
																  - 
																   
																  - 
																  (SI_Long)3L;
															  if (sub_class_vector_index 
																  < 
																  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
																      {
															      gensymed_symbol_2 
																      = 
																      UBYTE_8_ISAREF_1(sub_class_bit_vector,
																      sub_class_vector_index);
															      gensymed_symbol_3 
																      = 
																      (SI_Long)1L;
															      gensymed_symbol_4 
																      = 
																      superior_class_bit_number 
																      & 
																      (SI_Long)7L;
															      gensymed_symbol_3 
																      = 
																      gensymed_symbol_3 
																      << 
																      gensymed_symbol_4;
															      gensymed_symbol_2 
																      = 
																      gensymed_symbol_2 
																      & 
																      gensymed_symbol_3;
															      temp 
																      = 
																      (SI_Long)0L 
																      < 
																      gensymed_symbol_2;
															  }
															  else
															      temp 
																      = 
																      TRUEP(Nil);
														      }
														      else
															  temp 
																  = 
																  TRUEP(Nil);
														      if (temp) 
																  {
															  gensymed_symbol 
																  = 
																  ISVREF(kb_object,
																  (SI_Long)3L);
															  temp 
																  = 
																  SIMPLE_VECTOR_P(kb_object) 
																  ?
																   
																  EQ(ISVREF(kb_object,
																  (SI_Long)1L),
																  Qavailable_frame_vector) 
																  :
																   
																  TRUEP(Qnil);
															  if (temp);
															  else
															      temp 
																      = 
																      FIXNUMP(gensymed_symbol) 
																      ?
																       
																      IFIX(gensymed_symbol) 
																      == 
																      (SI_Long)-1L 
																      :
																       
																      TRUEP(Nil);
															  if (temp);
															  else if (FIXNUMP(frame_serial_number_before_deleting))
															      temp 
																      = 
																      FIXNUMP(gensymed_symbol) 
																      ?
																       
																      FIXNUM_LT(frame_serial_number_before_deleting,
																      gensymed_symbol) 
																      :
																       
																      TRUEP(T);
															  else if (FIXNUMP(gensymed_symbol))
															      temp 
																      = 
																      TRUEP(Nil);
															  else {
															      xa 
																      = 
																      M_CAR(frame_serial_number_before_deleting);
															      ya 
																      = 
																      M_CAR(gensymed_symbol);
															      temp 
																      = 
																      FIXNUM_LT(xa,
																      ya);
															      if (temp);
															      else
																  temp 
																	  = 
																	  FIXNUM_EQ(xa,
																	  ya) 
																	  ?
																	   
																	  FIXNUM_LT(M_CDR(frame_serial_number_before_deleting),
																	  M_CDR(gensymed_symbol)) 
																	  :
																	   
																	  TRUEP(Qnil);
															  }
															  temp 
																  = 
																   
																  !temp;
														      }
														      else
															  temp 
																  = 
																  TRUEP(Nil);
														      if (temp) 
																  {
															  if (block_needs_activation_upon_reading_p(kb_object))
															      blocks_to_activate_unless_reset 
																      = 
																      gensym_cons_1(kb_object,
																      blocks_to_activate_unless_reset);
															  gensymed_symbol 
																  = 
																  ISVREF(ISVREF(ISVREF(ISVREF(kb_object,
																  (SI_Long)1L),
																  (SI_Long)11L),
																  (SI_Long)4L),
																  (SI_Long)1L);
															  gensymed_symbol_1 
																  = 
																  kb_object;
															  inline_funcall_1(gensymed_symbol,
																  gensymed_symbol_1);
															  if (collect_kb_state_changes_for_module_qm 
																  && 
																  get_lookup_slot_value_given_default(kb_object,
																  Qoriginal_kb_state_plist,
																  Nil))
															      kb_state_changes_for_module_being_read_qm 
																      = 
																      gensym_cons_1(kb_object,
																      kb_state_changes_for_module_being_read_qm);
														      }
														      i 
															      = 
															      i 
															      + 
															      (SI_Long)1L;
														      goto next_loop_7;
														    end_loop_7:;
														    POP_SPECIAL();
														}
														Collecting_warnings_p 
															= 
															Nil;
														post_collected_warnings(Collected_items_with_warnings_alist);
														reclaim_collected_warnings(Collected_items_with_warnings_alist);
													      POP_SPECIAL();
													    POP_SPECIAL();
													    reclaim_frame_serial_number(frame_serial_number_before_deleting);
													    update_file_progress_display_after_reading(Kb_file_progress,
														    Qreformat);
													    reformat_as_appropriate_if_necessary();
													    reading_succeeded_qm 
														    = 
														    T;
													    if ( 
														    !(xml_object_qm 
														    || 
														    Plist_has_been_checked_p)) 
															{
														earlier_p 
															= 
															Qunbound_in_protected_let;
														encrypted_timestamp 
															= 
															Qunbound_in_protected_let;
														if (PUSH_UNWIND_PROTECT(3)) 
															    {
														    earlier_p 
															    = 
															    Nil;
														    gensymed_symbol 
															    = 
															    make_timestamp_list_1(FIX((SI_Long)5L));
														    gensymed_symbol_1 
															    = 
															    gensymed_symbol;
														    temp_2 
															    = 
															    ISVREF(Debugging_parameters,
															    (SI_Long)23L);
														    M_CAR(gensymed_symbol_1) 
															    = 
															    temp_2;
														    gensymed_symbol_1 
															    = 
															    M_CDR(gensymed_symbol_1);
														    temp_2 
															    = 
															    ISVREF(Debugging_parameters,
															    (SI_Long)24L);
														    M_CAR(gensymed_symbol_1) 
															    = 
															    temp_2;
														    gensymed_symbol_1 
															    = 
															    M_CDR(gensymed_symbol_1);
														    temp_2 
															    = 
															    ISVREF(Debugging_parameters,
															    (SI_Long)25L);
														    M_CAR(gensymed_symbol_1) 
															    = 
															    temp_2;
														    gensymed_symbol_1 
															    = 
															    M_CDR(gensymed_symbol_1);
														    temp_2 
															    = 
															    ISVREF(Debugging_parameters,
															    (SI_Long)26L);
														    M_CAR(gensymed_symbol_1) 
															    = 
															    temp_2;
														    gensymed_symbol_1 
															    = 
															    M_CDR(gensymed_symbol_1);
														    temp_2 
															    = 
															    ISVREF(Debugging_parameters,
															    (SI_Long)27L);
														    M_CAR(gensymed_symbol_1) 
															    = 
															    temp_2;
														    encrypted_timestamp 
															    = 
															    gensymed_symbol;
														    field 
															    = 
															    Nil;
														    ab_loop_list_ 
															    = 
															    encrypted_timestamp;
														  next_loop_8:
														    if ( 
															    !TRUEP(ab_loop_list_))
															goto end_loop_8;
														    field 
															    = 
															    M_CAR(ab_loop_list_);
														    ab_loop_list_ 
															    = 
															    M_CDR(ab_loop_list_);
														    if (field) 
																{
															temp 
																= 
																TRUEP(Nil);
															goto end_1;
														    }
														    goto next_loop_8;
														  end_loop_8:
														    temp 
															    = 
															    TRUEP(T);
														    goto end_1;
														    temp 
															    = 
															    TRUEP(Qnil);
														  end_1:;
														    if ( 
															    !temp) 
																{
															if (PUSH_LOCAL_ALLOCATION(Local_area,
																0,
																0)) 
																    {
															    decrypted_timestamp_qm 
																    = 
																    Qunbound_in_protected_let;
															    decrypted_time_qm 
																    = 
																    Qunbound_in_protected_let;
															    if (PUSH_UNWIND_PROTECT(2)) 
																	{
																timestamp_qm_1 
																	= 
																	Nil;
																encoded_timestamp_field 
																	= 
																	Nil;
																ab_loop_list_ 
																	= 
																	encrypted_timestamp;
																timestamp_field_qm 
																	= 
																	Nil;
															      next_loop_9:
																if ( 
																	!TRUEP(ab_loop_list_))
																    goto end_loop_9;
																encoded_timestamp_field 
																	= 
																	M_CAR(ab_loop_list_);
																ab_loop_list_ 
																	= 
																	M_CDR(ab_loop_list_);
																rotator_specs 
																	= 
																	Qunbound_in_protected_let;
																if (PUSH_UNWIND_PROTECT(1)) 
																	    {
																    gensymed_symbol 
																	    = 
																	    make_timestamp_list_1(FIX((SI_Long)9L));
																    gensymed_symbol_1 
																	    = 
																	    gensymed_symbol;
																    temp_2 
																	    = 
																	    timestamp_cons_1(FOURTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)0L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)3L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)6L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)9L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(THIRD(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)12L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(SIXTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)12L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)15L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)18L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    gensymed_symbol_1 
																	    = 
																	    M_CDR(gensymed_symbol_1);
																    temp_2 
																	    = 
																	    timestamp_cons_1(SEVENTH(Embedded_fuzzy_conditionals_list),
																	    FIX((SI_Long)18L));
																    M_CAR(gensymed_symbol_1) 
																	    = 
																	    temp_2;
																    rotator_specs 
																	    = 
																	    gensymed_symbol;
																    rotator 
																	    = 
																	    Nil;
																    offset 
																	    = 
																	    Nil;
																    ab_loop_list__1 
																	    = 
																	    rotator_specs;
																    ab_loop_desetq_ 
																	    = 
																	    Nil;
																  next_loop_10:
																    if ( 
																	    !TRUEP(ab_loop_list__1))
																	goto end_loop_10;
																    ab_loop_desetq_ 
																	    = 
																	    M_CAR(ab_loop_list__1);
																    rotator 
																	    = 
																	    CAR(ab_loop_desetq_);
																    offset 
																	    = 
																	    CDR(ab_loop_desetq_);
																    ab_loop_list__1 
																	    = 
																	    M_CDR(ab_loop_list__1);
																    logrotate_in_place_arg_1 
																	    = 
																	    rotator;
																    logrotate_in_place_arg_2 
																	    = 
																	    offset;
																    encoded_timestamp_field 
																	    = 
																	    assemble_uncached_compound_method_flags(encoded_timestamp_field,
																	    logrotate_in_place_arg_1,
																	    logrotate_in_place_arg_2,
																	    FIX((SI_Long)3L));
																    goto next_loop_10;
																  end_loop_10:;
																    filled_timestamp_field_components 
																	    = 
																	    Qunbound_in_protected_let;
																    key 
																	    = 
																	    Qunbound_in_protected_let;
																    if (PUSH_UNWIND_PROTECT(0)) 
																		{
																	ab_loop_repeat_ 
																		= 
																		(SI_Long)3L;
																	index_1 
																		= 
																		(SI_Long)2L;
																	shift_amount 
																		= 
																		(SI_Long)-14L;
																	ab_loopvar_ 
																		= 
																		Nil;
																	ab_loopvar__1 
																		= 
																		Nil;
																	ab_loopvar__2 
																		= 
																		Nil;
																	ab_loop_iter_flag_ 
																		= 
																		T;
																      next_loop_11:
																	if ( 
																		!((SI_Long)0L 
																		< 
																		ab_loop_repeat_))
																	    goto end_loop_11;
																	ab_loop_repeat_ 
																		= 
																		ab_loop_repeat_ 
																		- 
																		(SI_Long)1L;
																	if ( 
																		!TRUEP(ab_loop_iter_flag_)) 
																		    {
																	    index_1 
																		    = 
																		    index_1 
																		    - 
																		    (SI_Long)1L;
																	    shift_amount 
																		    = 
																		    shift_amount 
																		    + 
																		    (SI_Long)7L;
																	}
																	ab_loopvar__2 
																		= 
																		timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
																		index_1),
																		encoded_timestamp_field),
																		FIX(shift_amount)),
																		Nil);
																	if (ab_loopvar__1)
																	    M_CDR(ab_loopvar__1) 
																		    = 
																		    ab_loopvar__2;
																	else
																	    ab_loopvar_ 
																		    = 
																		    ab_loopvar__2;
																	ab_loopvar__1 
																		= 
																		ab_loopvar__2;
																	ab_loop_iter_flag_ 
																		= 
																		Nil;
																	goto next_loop_11;
																      end_loop_11:
																	filled_timestamp_field_components 
																		= 
																		ab_loopvar_;
																	goto end_2;
																	filled_timestamp_field_components 
																		= 
																		Qnil;
																      end_2:;
																	key 
																		= 
																		FIRST(filled_timestamp_field_components);
																	component 
																		= 
																		Nil;
																	ab_loop_list__1 
																		= 
																		REST(filled_timestamp_field_components);
																      next_loop_12:
																	if ( 
																		!TRUEP(ab_loop_list__1))
																	    goto end_loop_12;
																	component 
																		= 
																		M_CAR(ab_loop_list__1);
																	ab_loop_list__1 
																		= 
																		M_CDR(ab_loop_list__1);
																	if ( 
																		!FIXNUM_EQ(key,
																		component)) 
																		    {
																	    temp 
																		    = 
																		    TRUEP(Nil);
																	    goto end_3;
																	}
																	goto next_loop_12;
																      end_loop_12:
																	temp 
																		= 
																		TRUEP(T);
																	goto end_3;
																	temp 
																		= 
																		TRUEP(Qnil);
																      end_3:;
																	SAVE_VALUES(VALUES_1(temp 
																		?
																		 
																		key 
																		:
																		 
																		Nil));
																    }
																    POP_UNWIND_PROTECT(0);
																    if (filled_timestamp_field_components) 
																		{
																	if ( 
																		!EQ(filled_timestamp_field_components,
																		Qunbound_in_protected_let))
																	    reclaim_timestamp_list_1(filled_timestamp_field_components);
																    }
																    CONTINUE_UNWINDING(0);
																    result = RESTORE_VALUES();
																    SAVE_VALUES(VALUES_1(result));
																}
																POP_UNWIND_PROTECT(1);
																if (rotator_specs) 
																	    {
																    if ( 
																	    !EQ(rotator_specs,
																	    Qunbound_in_protected_let)) 
																		{
																	rotator_spec 
																		= 
																		Nil;
																	ab_loop_list__1 
																		= 
																		rotator_specs;
																      next_loop_13:
																	if ( 
																		!TRUEP(ab_loop_list__1))
																	    goto end_loop_13;
																	rotator_spec 
																		= 
																		M_CAR(ab_loop_list__1);
																	ab_loop_list__1 
																		= 
																		M_CDR(ab_loop_list__1);
																	reclaim_timestamp_cons_1(rotator_spec);
																	goto next_loop_13;
																      end_loop_13:
																	reclaim_timestamp_list_1(rotator_specs);
																    }
																}
																CONTINUE_UNWINDING(1);
																result = RESTORE_VALUES();
																timestamp_field_qm 
																	= 
																	result;
																timestamp_qm_1 
																	= 
																	timestamp_cons_1(timestamp_field_qm,
																	timestamp_qm_1);
																goto next_loop_9;
															      end_loop_9:;
																timestamp_field_qm 
																	= 
																	Nil;
																ab_loop_list_ 
																	= 
																	timestamp_qm_1;
															      next_loop_14:
																if ( 
																	!TRUEP(ab_loop_list_))
																    goto end_loop_14;
																timestamp_field_qm 
																	= 
																	M_CAR(ab_loop_list_);
																ab_loop_list_ 
																	= 
																	M_CDR(ab_loop_list_);
																if ( 
																	!TRUEP(timestamp_field_qm)) 
																	    {
																    if (timestamp_qm_1)
																	reclaim_timestamp_list_1(timestamp_qm_1);
																    decrypted_timestamp_qm 
																	    = 
																	    Nil;
																    goto end_4;
																}
																goto next_loop_14;
															      end_loop_14:
																decrypted_timestamp_qm 
																	= 
																	nreverse(timestamp_qm_1);
																goto end_4;
																decrypted_timestamp_qm 
																	= 
																	Qnil;
															      end_4:;
																if (decrypted_timestamp_qm) 
																	    {
																    circularity_point 
																	    = 
																	    FIXNUM_SUB1(length(decrypted_timestamp_qm));
																    temp_2 
																	    = 
																	    nthcdr(circularity_point,
																	    decrypted_timestamp_qm);
																    M_CDR(temp_2) 
																	    = 
																	    decrypted_timestamp_qm;
																    if (PUSH_UNWIND_PROTECT(0)) 
																		{
																	ab_loop_repeat_ 
																		= 
																		(SI_Long)5L;
																	raw_field 
																		= 
																		Nil;
																	ab_loopvar_ 
																		= 
																		Nil;
																	ab_loopvar__1 
																		= 
																		Nil;
																	ab_loopvar__2 
																		= 
																		Nil;
																      next_loop_15:
																	if ( 
																		!((SI_Long)0L 
																		< 
																		ab_loop_repeat_))
																	    goto end_loop_15;
																	ab_loop_repeat_ 
																		= 
																		ab_loop_repeat_ 
																		- 
																		(SI_Long)1L;
																	raw_field 
																		= 
																		FIX((SI_Long)0L);
																	ab_loop_repeat__1 
																		= 
																		(SI_Long)7L;
																	timestamp_field 
																		= 
																		Nil;
																      next_loop_16:
																	if ( 
																		!((SI_Long)0L 
																		< 
																		ab_loop_repeat__1))
																	    goto end_loop_16;
																	ab_loop_repeat__1 
																		= 
																		ab_loop_repeat__1 
																		- 
																		(SI_Long)1L;
																	timestamp_field 
																		= 
																		CAR(decrypted_timestamp_qm);
																	raw_field 
																		= 
																		logtest(FIX((SI_Long)64L),
																		timestamp_field) 
																		?
																		 
																		logior(ash(raw_field,
																		FIX((SI_Long)-1L)),
																		FIX((SI_Long)64L)) 
																		:
																		 
																		ash(raw_field,
																		FIX((SI_Long)-1L));
																	temp_2 
																		= 
																		ash(timestamp_field,
																		FIX((SI_Long)1L));
																	M_CAR(decrypted_timestamp_qm) 
																		= 
																		temp_2;
																	decrypted_timestamp_qm 
																		= 
																		CDR(decrypted_timestamp_qm);
																	goto next_loop_16;
																      end_loop_16:;
																	ab_loopvar__2 
																		= 
																		timestamp_cons_1(raw_field,
																		Nil);
																	if (ab_loopvar__1)
																	    M_CDR(ab_loopvar__1) 
																		    = 
																		    ab_loopvar__2;
																	else
																	    ab_loopvar_ 
																		    = 
																		    ab_loopvar__2;
																	ab_loopvar__1 
																		= 
																		ab_loopvar__2;
																	goto next_loop_15;
																      end_loop_15:
																	raw_field_list 
																		= 
																		ab_loopvar_;
																	goto end_5;
																	raw_field_list 
																		= 
																		Qnil;
																      end_5:;
																	raw_field 
																		= 
																		Nil;
																	ab_loop_list_ 
																		= 
																		raw_field_list;
																	shift_amount 
																		= 
																		(SI_Long)28L;
																	time_1 
																		= 
																		FIX((SI_Long)0L);
																	ab_loop_iter_flag_ 
																		= 
																		T;
																      next_loop_17:
																	if ( 
																		!TRUEP(ab_loop_list_))
																	    goto end_loop_17;
																	raw_field 
																		= 
																		M_CAR(ab_loop_list_);
																	ab_loop_list_ 
																		= 
																		M_CDR(ab_loop_list_);
																	if ( 
																		!TRUEP(ab_loop_iter_flag_))
																	    shift_amount 
																		    = 
																		    shift_amount 
																		    + 
																		    (SI_Long)-7L;
																	time_1 
																		= 
																		logior(ash(raw_field,
																		FIX(shift_amount)),
																		time_1);
																	ab_loop_iter_flag_ 
																		= 
																		Nil;
																	goto next_loop_17;
																      end_loop_17:
																	reclaim_timestamp_list_1(raw_field_list);
																	temp_1 
																		= 
																		time_1;
																	goto end_6;
																	temp_1 
																		= 
																		Qnil;
																      end_6:;
																	SAVE_VALUES(VALUES_1(temp_1));
																    }
																    POP_UNWIND_PROTECT(0);
																    temp_2 
																	    = 
																	    nthcdr(circularity_point,
																	    decrypted_timestamp_qm);
																    M_CDR(temp_2) 
																	    = 
																	    Nil;
																    CONTINUE_UNWINDING(0);
																    result = RESTORE_VALUES();
																    decrypted_time_qm 
																	    = 
																	    result;
																}
																else
																    decrypted_time_qm 
																	    = 
																	    Nil;
																if ( 
																	!TRUEP(decrypted_time_qm)) 
																	    {
																    earlier_p 
																	    = 
																	    T;
																    old_value_qm 
																	    = 
																	    Evaluator_tradeoff_info;
																    if (old_value_qm)
																	reclaim_timestamp_list_1(old_value_qm);
																    Evaluator_tradeoff_info 
																	    = 
																	    timestamp_cons_1(FIX((SI_Long)0L),
																	    Nil);
																}
																else {
																    temp_5 
																	    = 
																	    g2ext_unix_time_as_float();
																    temp_6 
																	    = 
																	    DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
																    universal_time 
																	    = 
																	    temp_5 
																	    + 
																	    temp_6;
																    temp_1 
																	    = 
																	    minus(decrypted_time_qm,
																	    FIX((SI_Long)90000L));
																    if (NUM_LT(DOUBLE_TO_DOUBLE_FLOAT(universal_time),
																	    temp_1)) 
																		{
																	temp_1 
																		= 
																		DOUBLE_TO_DOUBLE_FLOAT(5.0 
																		* 
																		universal_time);
																	earlier_p 
																		= 
																		NUM_LT(decrypted_time_qm,
																		temp_1) 
																		?
																		 T : Nil;
																    }
																    else
																	earlier_p 
																		= 
																		Nil;
																    if (earlier_p) 
																		{
																	old_value_qm 
																		= 
																		Evaluator_tradeoff_info;
																	if (old_value_qm)
																	    reclaim_timestamp_list_1(old_value_qm);
																	raw_field_list 
																		= 
																		Qunbound_in_protected_let;
																	timestamp 
																		= 
																		Qunbound_in_protected_let;
																	if (PUSH_UNWIND_PROTECT(1)) 
																		    {
																	    ab_loop_repeat_ 
																		    = 
																		    (SI_Long)5L;
																	    temp_6 
																		    = 
																		    DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
																	    fix_time 
																		    = 
																		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(universal_time 
																		    + 
																		    temp_6),
																		    _);
																	    index_1 
																		    = 
																		    (SI_Long)4L;
																	    shift_amount 
																		    = 
																		    (SI_Long)-28L;
																	    ab_loopvar_ 
																		    = 
																		    Nil;
																	    ab_loopvar__1 
																		    = 
																		    Nil;
																	    ab_loopvar__2 
																		    = 
																		    Nil;
																	    ab_loop_iter_flag_ 
																		    = 
																		    T;
																	  next_loop_18:
																	    if ( 
																		    !((SI_Long)0L 
																		    < 
																		    ab_loop_repeat_))
																		goto end_loop_18;
																	    ab_loop_repeat_ 
																		    = 
																		    ab_loop_repeat_ 
																		    - 
																		    (SI_Long)1L;
																	    if ( 
																		    !TRUEP(ab_loop_iter_flag_)) 
																			{
																		index_1 
																			= 
																			index_1 
																			- 
																			(SI_Long)1L;
																		shift_amount 
																			= 
																			shift_amount 
																			+ 
																			(SI_Long)7L;
																	    }
																	    ab_loopvar__2 
																		    = 
																		    timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
																		    index_1),
																		    fix_time),
																		    FIX(shift_amount)),
																		    Nil);
																	    if (ab_loopvar__1)
																		M_CDR(ab_loopvar__1) 
																			= 
																			ab_loopvar__2;
																	    else
																		ab_loopvar_ 
																			= 
																			ab_loopvar__2;
																	    ab_loopvar__1 
																		    = 
																		    ab_loopvar__2;
																	    ab_loop_iter_flag_ 
																		    = 
																		    Nil;
																	    goto next_loop_18;
																	  end_loop_18:
																	    raw_field_list 
																		    = 
																		    ab_loopvar_;
																	    goto end_7;
																	    raw_field_list 
																		    = 
																		    Qnil;
																	  end_7:;
																	    gensymed_symbol 
																		    = 
																		    make_timestamp_list_1(FIX((SI_Long)5L));
																	    gensymed_symbol_1 
																		    = 
																		    gensymed_symbol;
																	    M_CAR(gensymed_symbol_1) 
																		    = 
																		    FIX((SI_Long)0L);
																	    gensymed_symbol_1 
																		    = 
																		    M_CDR(gensymed_symbol_1);
																	    M_CAR(gensymed_symbol_1) 
																		    = 
																		    FIX((SI_Long)0L);
																	    gensymed_symbol_1 
																		    = 
																		    M_CDR(gensymed_symbol_1);
																	    M_CAR(gensymed_symbol_1) 
																		    = 
																		    FIX((SI_Long)0L);
																	    gensymed_symbol_1 
																		    = 
																		    M_CDR(gensymed_symbol_1);
																	    M_CAR(gensymed_symbol_1) 
																		    = 
																		    FIX((SI_Long)0L);
																	    gensymed_symbol_1 
																		    = 
																		    M_CDR(gensymed_symbol_1);
																	    M_CAR(gensymed_symbol_1) 
																		    = 
																		    FIX((SI_Long)0L);
																	    timestamp 
																		    = 
																		    gensymed_symbol;
																	    circularity_point 
																		    = 
																		    FIXNUM_SUB1(length(timestamp));
																	    temp_2 
																		    = 
																		    nthcdr(circularity_point,
																		    timestamp);
																	    M_CDR(temp_2) 
																		    = 
																		    timestamp;
																	    if (PUSH_UNWIND_PROTECT(0)) 
																			{
																		raw_field 
																			= 
																			Nil;
																		ab_loop_list_ 
																			= 
																			raw_field_list;
																	      next_loop_19:
																		if ( 
																			!TRUEP(ab_loop_list_))
																		    goto end_loop_19;
																		raw_field 
																			= 
																			M_CAR(ab_loop_list_);
																		ab_loop_list_ 
																			= 
																			M_CDR(ab_loop_list_);
																		ab_loop_repeat_ 
																			= 
																			(SI_Long)7L;
																	      next_loop_20:
																		if ( 
																			!((SI_Long)0L 
																			< 
																			ab_loop_repeat_))
																		    goto end_loop_20;
																		ab_loop_repeat_ 
																			= 
																			ab_loop_repeat_ 
																			- 
																			(SI_Long)1L;
																		timestamp_field 
																			= 
																			CAR(timestamp);
																		temp_3 
																			= 
																			oddp(raw_field) 
																			?
																			 
																			IFIX(ash(timestamp_field,
																			FIX((SI_Long)1L))) 
																			| 
																			(SI_Long)1L 
																			:
																			 
																			IFIX(timestamp_field) 
																			<< 
																			(SI_Long)1L;
																		M_CAR(timestamp) 
																			= 
																			FIX(temp_3);
																		timestamp 
																			= 
																			CDR(timestamp);
																		raw_field 
																			= 
																			FIX(IFIX(raw_field) 
																			>> 
																			 
																			- 
																			 
																			- 
																			(SI_Long)1L);
																		goto next_loop_20;
																	      end_loop_20:;
																		goto next_loop_19;
																	      end_loop_19:
																		temp_1 
																			= 
																			timestamp;
																		goto end_8;
																		temp_1 
																			= 
																			Qnil;
																	      end_8:;
																		SAVE_VALUES(VALUES_1(temp_1));
																	    }
																	    POP_UNWIND_PROTECT(0);
																	    temp_2 
																		    = 
																		    nthcdr(circularity_point,
																		    timestamp);
																	    M_CDR(temp_2) 
																		    = 
																		    Nil;
																	    CONTINUE_UNWINDING(0);
																	    result = RESTORE_VALUES();
																	    SAVE_VALUES(VALUES_1(result));
																	}
																	POP_UNWIND_PROTECT(1);
																	if (raw_field_list) 
																		    {
																	    if ( 
																		    !EQ(raw_field_list,
																		    Qunbound_in_protected_let))
																		reclaim_timestamp_list_1(raw_field_list);
																	}
																	CONTINUE_UNWINDING(1);
																	result = RESTORE_VALUES();
																	timestamp 
																		= 
																		result;
																	timestamp_field 
																		= 
																		Nil;
																	ab_loop_list_ 
																		= 
																		timestamp;
																	timestamp_cons 
																		= 
																		timestamp;
																	ab_loop_iter_flag_ 
																		= 
																		T;
																      next_loop_21:
																	if ( 
																		!TRUEP(ab_loop_list_))
																	    goto end_loop_21;
																	timestamp_field 
																		= 
																		M_CAR(ab_loop_list_);
																	ab_loop_list_ 
																		= 
																		M_CDR(ab_loop_list_);
																	if ( 
																		!TRUEP(ab_loop_iter_flag_))
																	    timestamp_cons 
																		    = 
																		    M_CDR(timestamp_cons);
																	if ( 
																		!TRUEP(timestamp_cons))
																	    goto end_loop_21;
																	encrypted_timestamp_field 
																		= 
																		logiorn(3,
																		ash(timestamp_field,
																		FIX((SI_Long)0L)),
																		ash(timestamp_field,
																		FIX((SI_Long)7L)),
																		ash(timestamp_field,
																		FIX((SI_Long)14L)));
																	gensymed_symbol 
																		= 
																		make_timestamp_list_1(FIX((SI_Long)7L));
																	gensymed_symbol_1 
																		= 
																		gensymed_symbol;
																	temp_2 
																		= 
																		THIRD(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		SIXTH(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		SEVENTH(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		SECOND(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		FIRST(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		FIFTH(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	gensymed_symbol_1 
																		= 
																		M_CDR(gensymed_symbol_1);
																	temp_2 
																		= 
																		FOURTH(Embedded_fuzzy_conditionals_list);
																	M_CAR(gensymed_symbol_1) 
																		= 
																		temp_2;
																	rotator_list 
																		= 
																		gensymed_symbol;
																	rotator 
																		= 
																		Nil;
																	ab_loop_list__1 
																		= 
																		rotator_list;
																	offset_1 
																		= 
																		(SI_Long)0L;
																	ab_loop_iter_flag_ 
																		= 
																		T;
																      next_loop_22:
																	if ( 
																		!TRUEP(ab_loop_list__1))
																	    goto end_loop_22;
																	rotator 
																		= 
																		M_CAR(ab_loop_list__1);
																	ab_loop_list__1 
																		= 
																		M_CDR(ab_loop_list__1);
																	if ( 
																		!TRUEP(ab_loop_iter_flag_))
																	    offset_1 
																		    = 
																		    offset_1 
																		    + 
																		    (SI_Long)3L;
																	logrotate_in_place_arg_1 
																		= 
																		rotator;
																	logrotate_in_place_arg_2_1 
																		= 
																		offset_1;
																	encrypted_timestamp_field 
																		= 
																		assemble_uncached_compound_method_flags(encrypted_timestamp_field,
																		logrotate_in_place_arg_1,
																		FIX(logrotate_in_place_arg_2_1),
																		FIX((SI_Long)3L));
																	ab_loop_iter_flag_ 
																		= 
																		Nil;
																	goto next_loop_22;
																      end_loop_22:;
																	reclaim_timestamp_list_1(rotator_list);
																	M_CAR(timestamp_cons) 
																		= 
																		encrypted_timestamp_field;
																	ab_loop_iter_flag_ 
																		= 
																		Nil;
																	goto next_loop_21;
																      end_loop_21:
																	Evaluator_tradeoff_info 
																		= 
																		timestamp;
																	goto end_9;
																	Evaluator_tradeoff_info 
																		= 
																		Qnil;
																      end_9:;
																    }
																}
															    }
															    POP_UNWIND_PROTECT(2);
															    if (decrypted_timestamp_qm) 
																	{
																if ( 
																	!EQ(decrypted_timestamp_qm,
																	Qunbound_in_protected_let))
																    reclaim_timestamp_list_1(decrypted_timestamp_qm);
															    }
															    CONTINUE_UNWINDING(2);
															}
															POP_LOCAL_ALLOCATION(0,0);
														    }
														    SAVE_VALUES(VALUES_1(earlier_p));
														}
														POP_UNWIND_PROTECT(3);
														if (encrypted_timestamp) 
															    {
														    if ( 
															    !EQ(encrypted_timestamp,
															    Qunbound_in_protected_let))
															reclaim_timestamp_list_1(encrypted_timestamp);
														}
														CONTINUE_UNWINDING(3);
														result = RESTORE_VALUES();
														temp 
															= 
															TRUEP(result);
													    }
													    else
														temp 
															= 
															TRUEP(Nil);
													    if (temp 
														    ?
														     
														    nth(FIX((SI_Long)11L),
														    Format_structure_description) 
														    && 
														    T 
														    :
														     
														    TRUEP(Nil))
														M_CADR(discrepancy_with_system_time2_p) 
															= 
															T;
													    if ( 
														    !TRUEP(xml_object_qm)) 
															{
														if (Main_kb_being_read_qm) 
															    {
														    reclaim_pathname_or_string(Current_kb_pathname_qm);
														    if (text_string_p(gensym_pathname_to_read)) 
																{
															temp_1 
																= 
																gensym_pathname(gensym_pathname_to_read);
															reclaim_text_string(gensym_pathname_to_read);
															Current_kb_pathname_qm 
																= 
																temp_1;
														    }
														    else
															Current_kb_pathname_qm 
																= 
																gensym_pathname_to_read;
														    add_recent_loaded_kb(Current_kb_pathname_qm);
														}
													    }
													    complete_name_from_kb_qm 
														    = 
														    getf(plist_from_initial_element_qm,
														    Qkb_name,
														    _);
													    temp_1 
														    = 
														    Main_kb_being_read_qm 
														    && 
														    reading_succeeded_qm 
														    && 
														    text_string_p(complete_name_from_kb_qm) 
														    ?
														     
														    complete_name_from_kb_qm 
														    :
														     Nil;
													    make_or_clear_complete_kb_name(4,
														    temp_1,
														    T,
														    Nil,
														    copy_for_slot_value(getf(plist_from_initial_element_qm,
														    Qkb_file_comment_string,
														    _)));
													    if (complete_name_from_kb_qm) 
															{
														if (text_string_p(complete_name_from_kb_qm))
														    reclaim_text_string(complete_name_from_kb_qm);
														plist_from_initial_element_qm 
															= 
															set_getf(plist_from_initial_element_qm,
															Qkb_name,
															Nil);
													    }
													    if ( 
														    !TRUEP(xml_object_qm)) 
															{
														set_gensym_pathname_for_module(Name_of_module_being_read_qm,
															gensym_pathname_to_read);
														set_default_pathname_for_module(Name_of_module_being_read_qm,
															default_kb_directory_qm);
														mutate_kb_specific_property_value(Name_of_module_being_read_qm,
															Qunknown,
															Module_is_writable_p_kbprop);
														set_reason_module_is_not_editable(Name_of_module_being_read_qm,
															Qunknown);
													    }
													    if ( 
														    !TRUEP(SECOND(discrepancy_with_system_time2_p))) 
															{
														if ( 
															!TRUEP(Do_not_notify_user_during_kb_load_qm))
														    notify_user(3,
															    Kb_load_case_qm 
															    ?
															     
															    string_constant_24 
															    :
															     
															    string_constant_25,
															    Name_text_string_for_kb_being_read,
															    Kb_load_case_qm 
															    ?
															     
															    string_constant_26 
															    :
															     
															    string_constant_2);
													    }
													    if (Loading_compiled_kb_p) 
															{
														compiled_function 
															= 
															Nil;
														ab_loop_list_ 
															= 
															New_compiled_byte_code_body_list;
														byte_code_body 
															= 
															Nil;
														ab_loop_list__1 
															= 
															New_byte_code_body_list;
													      next_loop_23:
														if ( 
															!TRUEP(ab_loop_list_))
														    goto end_loop_23;
														compiled_function 
															= 
															M_CAR(ab_loop_list_);
														ab_loop_list_ 
															= 
															M_CDR(ab_loop_list_);
														if ( 
															!TRUEP(ab_loop_list__1))
														    goto end_loop_23;
														byte_code_body 
															= 
															M_CAR(ab_loop_list__1);
														ab_loop_list__1 
															= 
															M_CDR(ab_loop_list__1);
														install_compiled_byte_code_body(byte_code_body,
															compiled_function);
														goto next_loop_23;
													      end_loop_23:;
													    }
													    if (Class_name_conflicts) 
															{
														update_file_progress_display_after_reading(Kb_file_progress,
															Qautomerge);
														kb_flags 
															= 
															local_kb_flags_from_last_kb_read;
														PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,
															0);
														  temp_1 
															  = 
															  IFIX(Kb_flags) 
															  >= 
															  (SI_Long)219L 
															  ?
															   T : Nil;
														POP_SPECIAL();
														deal_with_class_name_conflicts(auto_merge_case_qm,
															temp_1);
													    }
													    delete_blocks_and_connections_to_be_deleted_after_reading();
													    if ( 
														    !TRUEP(Do_not_restore_image_planes_qm))
														restore_image_planes_to_pane_now_or_later(3,
															getf(Plist_from_end_element_qm,
															Qdetail_pane_description,
															_),
															Main_kb_being_read_qm,
															Name_of_module_being_read_qm);
													    symbol 
														    = 
														    Nil;
													    ab_loop_list_ 
														    = 
														    getf(Plist_from_end_element_qm,
														    Qnumeric_symbols,
														    _);
													  next_loop_24:
													    if ( 
														    !TRUEP(ab_loop_list_))
														goto end_loop_24;
													    symbol 
														    = 
														    M_CAR(ab_loop_list_);
													    ab_loop_list_ 
														    = 
														    M_CDR(ab_loop_list_);
													    mutate_global_property(symbol,
														    Qnumeric,
														    Qtype_of_syntactic_anomaly);
													    goto next_loop_24;
													  end_loop_24:;
													    reclaim_slot_value(Plist_from_end_element_qm);
													    value_of_read_kb 
														    = 
														    reading_succeeded_qm 
														    ?
														     
														    Name_of_kb_being_read 
														    :
														     Nil;
													}
												    }
												}
												if (System_tables_read_for_this_module) 
													    {
												    reclaim_slot_value_list_1(System_tables_read_for_this_module);
												    System_tables_read_for_this_module 
													    = 
													    Nil;
												}
												dot_unwind_abort_dot 
													= 
													Nil;
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
						      }
						      POP_UNWIND_PROTECT(4);
						      if ( 
							      !TRUEP(reading_succeeded_qm))
							  make_or_clear_complete_kb_name(2,
								  Nil,Nil);
						      reclaim_items_deleted_since_load_or_save();
						      reclaim_slot_value(plist_from_initial_element_qm);
						      scope_conses = 
							      Scope_conses;
						      ab_loopvar_ = Nil;
						      ab_loopvar__1 = Nil;
						      definition = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
							      0);
							ab_loopvar_ = 
								collect_subclasses(Qclass_definition);
						      next_loop_25:
							if ( 
								!TRUEP(ab_loopvar__1)) 
								    {
							  next_loop_26:
							    if ( 
								    !TRUEP(ab_loopvar_))
								goto end_loop_25;
							    ab_loopvar__1 
								    = 
								    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
								    Instances_specific_to_this_class_kbprop);
							    ab_loopvar_ = 
								    M_CDR(ab_loopvar_);
							    if (ab_loopvar__1)
								goto end_loop_25;
							    goto next_loop_26;
							  end_loop_25:
							    temp =  
								    !TRUEP(ab_loopvar__1);
							}
							else
							    temp = TRUEP(Nil);
							if (temp)
							    goto end_loop_26;
							definition = 
								ab_loopvar__1;
							ab_loopvar__1 = 
								ISVREF(ab_loopvar__1,
								(SI_Long)6L);
							temp_3 = 
								IFIX(ISVREF(definition,
								(SI_Long)5L)) 
								&  
								~(SI_Long)32L;
							ISVREF(definition,
								(SI_Long)5L) 
								= FIX(temp_3);
							goto next_loop_25;
						      end_loop_26:;
						      POP_SPECIAL();
						      if (New_saved_kb_format_p)
							  reclaim_frame_serial_number_map();
						      reclaim_index_space_1(Kb_object_index_space);
						      reclaim_gensym_list_1(Forward_referenced_format_frames);
						      if ( 
							      !TRUEP(reading_succeeded_qm)) 
								  {
							  if (xml_object_qm 
								  || 
								  Plist_has_been_checked_p);
							  else if ( 
								  !TRUEP(timestamp_qm))
							      notify_user(2,
								      flag_in_kb_is_higher_than_g2_kb_flag_qm 
								      ? 
								      string_constant_27 
								      : 
								      string_constant_28,
								      Name_text_string_for_kb_being_read);
							  else if (system_version_greater_p(Earliest_version_to_allow_kb_loading,
								  local_system_version_from_last_kb_read)) 
								      {
							      current_wide_string_list 
								      = 
								      Qdo_not_use;
							      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
								      4);
								wide_string_bv16 
									= 
									allocate_byte_vector_16(FIX((SI_Long)2048L 
									+ 
									(SI_Long)3L));
								bv16_length 
									= 
									IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
								temp_3 = 
									bv16_length 
									- 
									(SI_Long)2L;
								aref_new_value 
									= 
									(SI_Long)2048L 
									& 
									(SI_Long)65535L;
								UBYTE_16_ISASET_1(wide_string_bv16,
									temp_3,
									aref_new_value);
								temp_3 = 
									bv16_length 
									- 
									(SI_Long)1L;
								aref_new_value 
									= 
									(SI_Long)57344L 
									| 
									(SI_Long)0L;
								UBYTE_16_ISASET_1(wide_string_bv16,
									temp_3,
									aref_new_value);
								UBYTE_16_ISASET_1(wide_string_bv16,
									(SI_Long)2048L,
									(SI_Long)0L);
								current_wide_string 
									= 
									wide_string_bv16;
								PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
									3);
								  fill_pointer_for_current_wide_string 
									  = 
									  FIX((SI_Long)0L);
								  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
									  2);
								    length_1 
									    = 
									    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
								    total_length_of_current_wide_string 
									    = 
									    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
									    length_1 
									    - 
									    (SI_Long)2L) 
									    + 
									    ((UBYTE_16_ISAREF_1(Current_wide_string,
									    length_1 
									    - 
									    (SI_Long)1L) 
									    & 
									    (SI_Long)8191L) 
									    << 
									    (SI_Long)16L));
								    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
									    1);
								      current_twriting_output_type 
									      = 
									      Qwide_string;
								      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
									      0);
									tformat(2,
										string_constant_29,
										Name_text_string_for_kb_being_read);
									twrite_system_version(2,
										local_system_version_from_last_kb_read,
										T);
									tformat(1,
										string_constant_30);
									twrite_system_version(2,
										Earliest_version_to_allow_kb_loading,
										T);
									tformat(1,
										string_constant_31);
									twrite_system_version(2,
										System_version_of_current_gensym_product_line,
										T);
									tformat(1,
										string_constant_32);
									text_string 
										= 
										copy_out_current_wide_string();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							      notify_user(2,
								      string_constant_13,
								      text_string);
							      reclaim_text_string(text_string);
							  }
							  else {
							      if (Top_level_error_seen)
								  notify_user_at_console(1,
									  string_constant_33);
							      else
								  error((SI_Long)1L,
									  "READING HAS FAILED -- UNABLE TO PROCEED!");
							      if ( 
								      !TRUEP(Top_level_error_seen)) 
									  {
								  clear_kb(0);
								  change_all_permanently_changed_things_are_marked(Nil);
							      }
							  }
						      }
						      else {
							  kb_flags_from_last_kb_read 
								  = 
								  local_kb_flags_from_last_kb_read;
							  PUSH_SPECIAL_WITH_SYMBOL(Kb_flags_from_last_kb_read,Qkb_flags_from_last_kb_read,kb_flags_from_last_kb_read,
								  3);
							    system_version_from_last_kb_read 
								    = 
								    local_system_version_from_last_kb_read;
							    PUSH_SPECIAL_WITH_SYMBOL(System_version_from_last_kb_read,Qsystem_version_from_last_kb_read,system_version_from_last_kb_read,
								    2);
							      if ( 
								      !(xml_object_qm 
								      || 
								      Plist_has_been_checked_p)) 
									  {
								  kb_flags 
									  = 
									  Kb_flags_from_last_kb_read;
								  PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,
									  1);
								    after_pkg_authorization_qm 
									    = 
									    IFIX(Kb_flags) 
									    >= 
									    (SI_Long)102L;
								    new_algorithm_qm 
									    = 
									    IFIX(Kb_flags) 
									    >= 
									    (SI_Long)219L;
								    scope_conses 
									    = 
									    Scope_conses;
								    ab_loopvar_ 
									    = 
									    Nil;
								    ab_loopvar__1 
									    = 
									    Nil;
								    ws = Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
									    0);
								      checksum_qm 
									      = 
									      Nil;
								      ab_loopvar_ 
									      = 
									      collect_subclasses(Qkb_workspace);
								    next_loop_27:
								      if ( 
									      !TRUEP(ab_loopvar__1)) 
										  {
									next_loop_28:
									  if ( 
										  !TRUEP(ab_loopvar_))
									      goto end_loop_27;
									  ab_loopvar__1 
										  = 
										  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
										  Instances_specific_to_this_class_kbprop);
									  ab_loopvar_ 
										  = 
										  M_CDR(ab_loopvar_);
									  if (ab_loopvar__1)
									      goto end_loop_27;
									  goto next_loop_28;
									end_loop_27:
									  temp 
										  = 
										   
										  !TRUEP(ab_loopvar__1);
								      }
								      else
									  temp 
										  = 
										  TRUEP(Nil);
								      if (temp)
									  goto end_loop_28;
								      ws = 
									      ab_loopvar__1;
								      ab_loopvar__1 
									      = 
									      ISVREF(ab_loopvar__1,
									      (SI_Long)6L);
								      checksum_qm 
									      = 
									      ISVREF(ws,
									      (SI_Long)27L);
								      if (checksum_qm) 
										  {
									  temp_1 
										  = 
										  checksum_qm;
									  if (FIXNUM_NE(temp_1,
										  normalize_kb_workspace(ws,
										  new_algorithm_qm 
										  ?
										   
										  T 
										  : Nil)))
									      replace_format_using_equivalent_font(Qvariable);
								      }
								      else if (after_pkg_authorization_qm)
									  replace_format_using_equivalent_font(Qvariable);
								      else {
									  gensymed_symbol 
										  = 
										  ACCESS_ONCE(ISVREF(ws,
										  (SI_Long)14L));
									  gensymed_symbol 
										  = 
										  gensymed_symbol 
										  ?
										   
										  ACCESS_ONCE(ISVREF(gensymed_symbol,
										  (SI_Long)4L)) 
										  :
										   
										  Nil;
									  ab_queue_form_ 
										  = 
										  gensymed_symbol;
									  ab_next_queue_element_ 
										  = 
										  Nil;
									  subblock 
										  = 
										  Nil;
									  if (ab_queue_form_)
									      ab_next_queue_element_ 
										      = 
										      constant_queue_next(ISVREF(ab_queue_form_,
										      (SI_Long)2L),
										      ab_queue_form_);
									next_loop_29:
									  if ( 
										  !TRUEP(ab_next_queue_element_))
									      goto end_loop_29;
									  subblock 
										  = 
										  ISVREF(ab_next_queue_element_,
										  (SI_Long)4L);
									  ab_next_queue_element_ 
										  = 
										  constant_queue_next(ab_next_queue_element_,
										  ab_queue_form_);
									  sub_class_bit_vector 
										  = 
										  ISVREF(ISVREF(subblock,
										  (SI_Long)1L),
										  (SI_Long)19L);
									  superior_class_bit_number 
										  = 
										  IFIX(ISVREF(Procedure_class_description,
										  (SI_Long)18L));
									  sub_class_vector_index 
										  = 
										  superior_class_bit_number 
										  >> 
										   
										  - 
										   
										  - 
										  (SI_Long)3L;
									  if (sub_class_vector_index 
										  < 
										  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
										      {
									      gensymed_symbol_2 
										      = 
										      UBYTE_8_ISAREF_1(sub_class_bit_vector,
										      sub_class_vector_index);
									      gensymed_symbol_3 
										      = 
										      (SI_Long)1L;
									      gensymed_symbol_4 
										      = 
										      superior_class_bit_number 
										      & 
										      (SI_Long)7L;
									      gensymed_symbol_3 
										      = 
										      gensymed_symbol_3 
										      << 
										      gensymed_symbol_4;
									      gensymed_symbol_2 
										      = 
										      gensymed_symbol_2 
										      & 
										      gensymed_symbol_3;
									      temp 
										      = 
										      (SI_Long)0L 
										      < 
										      gensymed_symbol_2;
									  }
									  else
									      temp 
										      = 
										      TRUEP(Nil);
									  if (temp 
										  ?
										   
										  (SI_Long)0L 
										  != 
										  (IFIX(ISVREF(subblock,
										  (SI_Long)4L)) 
										  & 
										  (SI_Long)2L) 
										  :
										   
										  TRUEP(Nil))
									      replace_format_using_equivalent_font(Qvariable);
									  goto next_loop_29;
									end_loop_29:;
								      }
								      goto next_loop_27;
								    end_loop_28:;
								    POP_SPECIAL();
								  POP_SPECIAL();
							      }
							      frame_reference_serial_number 
								      = 
								      copy_frame_serial_number(Current_frame_serial_number);
							      update_file_progress_display_after_reading(Kb_file_progress,
								      Qpost_load);
							      do_post_loading_functions(Kbefore_conflict_resolution);
							      update_file_progress_display_after_reading(Kb_file_progress,
								      Qautomerge2);
							      if (auto_merge_case_qm) 
									  {
								  resolve_class_name_conflicts();
								  resolve_definitional_name_conflicts();
							      }
							      update_file_progress_display_after_reading(Kb_file_progress,
								      Qpost_load2);
							      do_post_loading_functions(Kafter_conflict_resolution);
							      update_file_progress_display_after_reading(Kb_file_progress,
								      Qrevert);
							      frame = Nil;
							      ab_loop_list_ 
								      = 
								      kb_state_changes_for_module_being_read_qm;
							    next_loop_30:
							      if ( 
								      !TRUEP(ab_loop_list_))
								  goto end_loop_30;
							      frame = 
								      M_CAR(ab_loop_list_);
							      ab_loop_list_ 
								      = 
								      M_CDR(ab_loop_list_);
							      gensymed_symbol 
								      = 
								      ISVREF(frame,
								      (SI_Long)3L);
							      temp = 
								      SIMPLE_VECTOR_P(frame) 
								      ? 
								      EQ(ISVREF(frame,
								      (SI_Long)1L),
								      Qavailable_frame_vector) 
								      : 
								      TRUEP(Qnil);
							      if (temp);
							      else
								  temp = 
									  FIXNUMP(gensymed_symbol) 
									  ?
									   
									  IFIX(gensymed_symbol) 
									  == 
									  (SI_Long)-1L 
									  :
									   
									  TRUEP(Nil);
							      if (temp);
							      else if (FIXNUMP(frame_reference_serial_number))
								  temp = 
									  FIXNUMP(gensymed_symbol) 
									  ?
									   
									  FIXNUM_LT(frame_reference_serial_number,
									  gensymed_symbol) 
									  :
									   
									  TRUEP(T);
							      else if (FIXNUMP(gensymed_symbol))
								  temp = 
									  TRUEP(Nil);
							      else {
								  xa = 
									  M_CAR(frame_reference_serial_number);
								  ya = 
									  M_CAR(gensymed_symbol);
								  temp = 
									  FIXNUM_LT(xa,
									  ya);
								  if (temp);
								  else
								      temp 
									      = 
									      FIXNUM_EQ(xa,
									      ya) 
									      ?
									       
									      FIXNUM_LT(M_CDR(frame_reference_serial_number),
									      M_CDR(gensymed_symbol)) 
									      :
									       
									      TRUEP(Qnil);
							      }
							      if ( !temp) {
								  undo_kb_state_changes_for_frame(frame);
								  remove_as_frame_with_kb_state_changes(frame);
							      }
							      goto next_loop_30;
							    end_loop_30:
							      reclaim_gensym_list_1(kb_state_changes_for_module_being_read_qm);
							      update_file_progress_display_after_reading(Kb_file_progress,
								      Qfinished);
							      reclaim_frame_serial_number(frame_reference_serial_number);
							    POP_SPECIAL();
							  POP_SPECIAL();
						      }
						      if ( 
							      !TRUEP(Kb_file_progress_is_currently_for_modules_p)) 
								  {
							  note_update_to_file_progress(2,
								  Kb_file_progress,
								  Qdelete);
							  delete_frame(Kb_file_progress);
						      }
						      delete_all_title_block_workspaces();
						      if ( 
							      !TRUEP(Top_level_error_seen)) 
								  {
							  reclaim_slot_value(local_system_version_from_last_kb_read);
							  if (Refresh_all_windows_after_merging_qm) 
								      {
							      workstation 
								      = Nil;
							      ab_loop_list_ 
								      = 
								      Workstations_in_service;
							    next_loop_31:
							      if ( 
								      !TRUEP(ab_loop_list_))
								  goto end_loop_31;
							      workstation 
								      = 
								      M_CAR(ab_loop_list_);
							      ab_loop_list_ 
								      = 
								      M_CDR(ab_loop_list_);
							      refresh_window(ISVREF(workstation,
								      (SI_Long)1L));
							      goto next_loop_31;
							    end_loop_31:;
							  }
							  change_all_permanently_changed_things_are_marked(Kb_load_case_qm 
								  ? T : Nil);
							  Defer_notifications_qm 
								  = Nil;
							  try_to_do_deferred_user_notifications();
						      }
						      reclaim_frame_serial_number(Current_frame_serial_number_before_reading);
						      if (dot_unwind_abort_dot) 
								  {
							  temp_1 = 
								  frame_serial_number_for_blocks_to_activate;
							  frame_serial_number_for_blocks_to_activate 
								  = Nil;
							  reclaim_frame_serial_number(temp_1);
						      }
						      CONTINUE_UNWINDING(4);
						    POP_SPECIAL();
						    path_pop_store = Nil;
						    cons_1 = 
							    discrepancy_with_system_time2_p;
						    if (cons_1) {
							path_pop_store = 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpath);
							if (ISVREF(Available_path_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp_2 = 
								    ISVREF(Available_path_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp_2) 
								    = cons_1;
							    temp_2 = 
								    Available_path_conses_tail_vector;
							    svref_arg_2 = 
								    Current_thread_index;
							    SVREF(temp_2,
								    svref_arg_2) 
								    = cons_1;
							}
							else {
							    temp_2 = 
								    Available_path_conses_vector;
							    svref_arg_2 = 
								    Current_thread_index;
							    SVREF(temp_2,
								    svref_arg_2) 
								    = cons_1;
							    temp_2 = 
								    Available_path_conses_tail_vector;
							    svref_arg_2 = 
								    Current_thread_index;
							    SVREF(temp_2,
								    svref_arg_2) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    discrepancy_with_system_time2_p 
							    = next_cons;
						    if ( !(xml_object_qm 
							    || 
							    Plist_has_been_checked_p) 
							    && 
							    Limit_bignum_inner_loop_cache_p 
							    && 
							    CADR(discrepancy_with_system_time1_p)) 
								{
							clear_kb(0);
							notify_user(2,
								Refuse_load_at_discrepancy_with_system_clock_message,
								Name_text_string_for_kb_being_read);
						    }
						    reclaim_path_list_1(discrepancy_with_system_time1_p);
						    if (System_is_running 
							    || 
							    System_has_paused) 
								{
							make_all_indexed_attribute_hash_tables();
							scope_conses = 
								Scope_conses;
							ab_loopvar_ = Nil;
							ab_loopvar__1 = Nil;
							block = Nil;
							PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
								0);
							  ab_loopvar_ = 
								  collect_subclasses(Qblock);
							next_loop_32:
							  if ( 
								  !TRUEP(ab_loopvar__1)) 
								      {
							    next_loop_33:
							      if ( 
								      !TRUEP(ab_loopvar_))
								  goto end_loop_32;
							      ab_loopvar__1 
								      = 
								      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
								      Instances_specific_to_this_class_kbprop);
							      ab_loopvar_ 
								      = 
								      M_CDR(ab_loopvar_);
							      if (ab_loopvar__1)
								  goto end_loop_32;
							      goto next_loop_33;
							    end_loop_32:
							      temp =  
								      !TRUEP(ab_loopvar__1);
							  }
							  else
							      temp = 
								      TRUEP(Nil);
							  if (temp)
							      goto end_loop_33;
							  block = 
								  ab_loopvar__1;
							  ab_loopvar__1 = 
								  ISVREF(ab_loopvar__1,
								  (SI_Long)6L);
							  if ((SI_Long)0L 
								  != 
								  (IFIX(ISVREF(block,
								  (SI_Long)5L)) 
								  & 
								  (SI_Long)64L) 
								  && 
								  (SI_Long)0L 
								  != 
								  (IFIX(ISVREF(block,
								  (SI_Long)5L)) 
								  & 
								  (SI_Long)1L))
							      put_parent_for_its_indexed_attributes(2,
								      block,T);
							  goto next_loop_32;
							end_loop_33:;
							POP_SPECIAL();
							activate_roots_of_kb_hierarchy_just_read_in(blocks_to_activate_unless_reset,
								frame_serial_number_for_blocks_to_activate);
						    }
						    reclaim_gensym_list_1(blocks_to_activate_unless_reset);
						    temp_1 = 
							    frame_serial_number_for_blocks_to_activate;
						    frame_serial_number_for_blocks_to_activate 
							    = Nil;
						    reclaim_frame_serial_number(temp_1);
						    result = VALUES_1(value_of_read_kb);
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qsystem_table;       /* system-table */

/* BLOCK-NEEDS-ACTIVATION-UPON-READING-P */
Object block_needs_activation_upon_reading_p(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(132,46);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	temp = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 =  !TRUEP(ISVREF(block,(SI_Long)18L)) ? T : Nil;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Definition_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qsystem_table,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_1 =  !TRUEP(gensymed_symbol) ? T : Nil;
	}
	else
	    temp_1 = Qnil;
    }
    return VALUES_1(temp_1);
}

/* ACTIVATE-ROOTS-OF-KB-HIERARCHY-JUST-READ-IN */
Object activate_roots_of_kb_hierarchy_just_read_in(blocks,
	    reference_serial_number)
    Object blocks, reference_serial_number;
{
    Object block, ab_loop_list_, gensymed_symbol, xa, ya, gensymed_symbol_1;
    char temp;

    x_note_fn_call(132,47);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = block;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* READ-ALL-TOP-LEVEL-KB-ELEMENTS */
Object read_all_top_level_kb_elements()
{
    x_note_fn_call(132,48);
  next_loop:
    if ( !TRUEP(read_element_for_kb(T)))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TERMINATE-LOAD-WHEN-DEFINITIONS-HAVE-CHANGED */
Object terminate_load_when_definitions_have_changed()
{
    x_note_fn_call(132,49);
    return abort_g2(0);
}

static Object Qbase_time;          /* base-time */

static Object Qstart_time;         /* start-time */

static Object Qsimulated_time;     /* simulated-time */

static Object string_constant_34;  /* "KB saved in wrong version, and the current-time is ~
				    *                unavailable.  Therefore, we cannot run from snapshot time!"
				    */

/* PREPARE-TO-READ-SNAPSHOT-IF-APPROPRIATE */
Object prepare_to_read_snapshot_if_appropriate(initial_kb_plist)
    Object initial_kb_plist;
{
    Object base_time_qm, temp;

    x_note_fn_call(132,50);
    if (Warmbooting_qm) {
	base_time_qm = getf(initial_kb_plist,Qbase_time,_);
	if (base_time_qm) {
	    temp = copy_managed_float(base_time_qm);
	    if (Gensym_base_time_as_managed_float)
		reclaim_managed_simple_float_array_of_length_1(Gensym_base_time_as_managed_float);
	    Gensym_base_time_as_managed_float = temp;
	    Gensym_time_at_start = getf(initial_kb_plist,Qstart_time,_);
	    Warmboot_simulated_time = getf(initial_kb_plist,Qsimulated_time,_);
	    if (Warmbooting_with_catch_up_qm) {
		Warmboot_current_time = getf(initial_kb_plist,Qgensym_time,_);
		if ( !TRUEP(Warmboot_current_time)) {
		    notify_user(1,string_constant_34);
		    Warmbooting_with_catch_up_qm = Nil;
		    return VALUES_1(Warmbooting_with_catch_up_qm);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PREPARE-TO-READ-BACKUP-IF-APPROPRIATE */
Object prepare_to_read_backup_if_appropriate(initial_kb_plist)
    Object initial_kb_plist;
{
    x_note_fn_call(132,51);
    return VALUES_1(Nil);
}

static Object Qab_current_frame_serial_number;  /* current-frame-serial-number */

/* READ-KB-DETAIL-2 */
Object read_kb_detail_2(initial_kb_plist)
    Object initial_kb_plist;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, character_1, temp_1;
    Object read_kb_buffer_index_new_value;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(132,52);
    if (New_saved_kb_format_p) {
	make_frame_serial_number_to_frame_map();
	if (Kb_load_case_qm) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    frame = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar__2 = Nil;
	      ab_loopvar__3 = Nil;
	      ab_loopvar__4 = Nil;
	      ab_loopvar_ = collect_subclasses(Qblock);
	    next_loop:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_1:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop;
		  goto next_loop_1;
		end_loop:
		  temp =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  goto end_loop_1;
	      frame = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | 
		      (SI_Long)8192L;
	      ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	      ab_loopvar__4 = gensym_cons_1(frame,Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__4;
	      else
		  ab_loopvar__2 = ab_loopvar__4;
	      ab_loopvar__3 = ab_loopvar__4;
	      goto next_loop;
	    end_loop_1:
	      Preexisting_frames = ab_loopvar__2;
	      goto end_1;
	      Preexisting_frames = Qnil;
	    end_1:;
	    POP_SPECIAL();
	}
	if (Backup_case_qm)
	    enter_old_things_into_map();
	Base_reference = chestnut_modf_function(getf(initial_kb_plist,
		Qab_current_frame_serial_number,_),Base_modulus);
	if ( !TRUEP(Read_kb_buffer_index))
	    character_1 = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    character_1 = temp_1;
	}
	else
	    character_1 = read_next_char_for_kb_from_refilled_buffer();
	if (EQ(character_1,CHR('@')))
	    return read_past_element_for_kb(Nil);
	else {
	    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    return VALUES_1(Read_kb_buffer_index);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qformat_frame;       /* format-frame */

static Object Qformat_change_qm;   /* format-change? */

static Object Qworkspace;          /* workspace */

/* REFORMAT-AS-APPROPRIATE-IF-NECESSARY */
Object reformat_as_appropriate_if_necessary()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, format_frame;
    Object format_change_qm, ab_loop_it_, temp_1, workspace;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,53);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    format_frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      format_change_qm = Nil;
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qformat_frame);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      format_frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      format_change_qm = get_lookup_slot_value_given_default(format_frame,
	      Qformat_change_qm,Nil);
      if (format_change_qm) {
	  temp_1 = Reformat_as_appropriate_qm;
	  if (temp_1);
	  else
	      temp_1 = INTEGERP(format_change_qm) ? T : Nil;
	  ab_loop_it_ = temp_1;
      }
      else
	  ab_loop_it_ = Nil;
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if (temp) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	workspace = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qworkspace);
	next_loop_2:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_3:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_2;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_2;
	      goto next_loop_3;
	    end_loop_2:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_3;
	  workspace = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  reformat_as_appropriate(workspace,Nil);
	  goto next_loop_2;
	end_loop_3:;
	POP_SPECIAL();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	format_frame = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  format_change_qm = Nil;
	  ab_loopvar_ = collect_subclasses(Qformat_frame);
	next_loop_4:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_5:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_4;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_4;
	      goto next_loop_5;
	    end_loop_4:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_5;
	  format_frame = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  format_change_qm = 
		  get_lookup_slot_value_given_default(format_frame,
		  Qformat_change_qm,Nil);
	  if (format_change_qm && INTEGERP(format_change_qm)) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(format_frame,Qformat_change_qm);
	      set_lookup_slot_value_1(format_frame,Qformat_change_qm,Nil);
	  }
	  goto next_loop_4;
	end_loop_5:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_with_subblocks_from_kb_read, Qblocks_with_subblocks_from_kb_read);

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qobject_configuration;  /* object-configuration */

static Object Qcell_array;         /* cell-array */

/* INITIALIZE-AFTER-READING-FOR-BLOCK */
Object initialize_after_reading_for_block(block)
    Object block;
{
    Object gensymed_symbol, scope_conses, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, conn, ab_loop_it_, temp;
    Object ab_less_than_branch_qm_, cdr_arg, gensym_push_modify_macro_arg;
    Object car_1, cdr_1, cdr_new_value, cell_array_qm;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(132,54);
    if (ISVREF(block,(SI_Long)12L))
	Blocks_with_relation_instances_from_kb_read = gensym_cons_1(block,
		Blocks_with_relation_instances_from_kb_read);
    if (ISVREF(block,(SI_Long)9L)) {
	update_attribute_tables(3,block,FIXNUM_LT(Kb_flags,
		Kb_flags_of_software) ? T : Nil,Nil);
	update_representations_of_slot_value(2,block,Qframe_status_and_notes);
    }
    if (get_lookup_slot_value(block,Qobject_configuration) && 
	    IFIX(FIRST(System_version_from_kb_being_read)) == (SI_Long)7L 
	    && IFIX(SECOND(System_version_from_kb_being_read)) == 
	    (SI_Long)0L && IFIX(System_revision_from_last_kb_read) == 
	    (SI_Long)0L && FIXNUM_EQ(System_quality_from_last_kb_read,
	    Release_quality))
	fix_up_double_click_configuration_clauses(get_lookup_slot_value(block,
		Qobject_configuration));
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    if (gensymed_symbol) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	conn = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = CDR(ab_skip_list_form_);
	next_loop:
	next_loop_1:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
		end_loop:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	      goto end_1;
	  goto next_loop_1;
	end_loop_1:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  conn = ab_connection_;
	  temp =  !TRUEP(ISVREF(conn,(SI_Long)1L)) ? T : Nil;
	  if (temp);
	  else
	      temp =  !TRUEP(ISVREF(conn,(SI_Long)2L)) ? T : Nil;
	  if (temp);
	  else
	      temp =  !TRUEP(ISVREF(conn,(SI_Long)3L)) ? T : Nil;
	  ab_loop_it_ = temp;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop;
	end_loop_2:
	  temp_1 = TRUEP(Qnil);
	end_2:;
	POP_SPECIAL();
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if ( !TRUEP(Blocks_with_bad_connections))
	    Blocks_with_bad_connections = 
		    gensym_cons_1(copy_frame_serial_number(Current_frame_serial_number),
		    Nil);
	cdr_arg = Blocks_with_bad_connections;
	gensym_push_modify_macro_arg = block;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = CDR(cdr_arg);
	cdr_new_value = gensym_cons_1(car_1,cdr_1);
	M_CDR(cdr_arg) = cdr_new_value;
    }
    cell_array_qm = get_lookup_slot_value_given_default(block,Qcell_array,Nil);
    if (cell_array_qm)
	return initialize_g2_cell_array_after_reading(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-FOR-BLOCK */
Object initialize_for_block(block)
    Object block;
{
    Object cell_array_qm;

    x_note_fn_call(132,55);
    cell_array_qm = get_lookup_slot_value_given_default(block,Qcell_array,Nil);
    if (cell_array_qm)
	return initialize_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-BLOCK */
Object cleanup_for_block(block)
    Object block;
{
    Object frame, sub_vector_qm, method_function_qm, cell_array_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(132,56);
    frame = block;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qblock)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    remove_as_frame_with_kb_state_changes(block);
    cell_array_qm = get_lookup_slot_value_given_default(block,Qcell_array,Nil);
    if (cell_array_qm)
	return cleanup_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-BLOCK */
Object note_runs_while_inactive_change_for_block(block)
    Object block;
{
    Object cell_array_qm;

    x_note_fn_call(132,57);
    cell_array_qm = get_lookup_slot_value_given_default(block,Qcell_array,Nil);
    if (cell_array_qm)
	return note_g2_cell_array_runs_while_inactive_change(cell_array_qm,
		block);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Classes_needing_data_interface_initialization, Qclasses_needing_data_interface_initialization);

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* INITIALIZE-INSTANCES-WITH-DEFAULT-DATA-INTERFACE-VALUES */
Object initialize_instances_with_default_data_interface_values()
{
    Object class_1, data_interface_class, ab_loop_list_, ab_loop_desetq_, temp;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, scope_conses, ab_loopvar_, ab_loopvar__1, instance;
    Object slot_description, class_description, ab_loop_list__1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,58);
    class_1 = Nil;
    data_interface_class = Nil;
    ab_loop_list_ = Classes_needing_data_interface_initialization;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    data_interface_class = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(class_1)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_1:
	if (level < ab_loop_bind_)
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_2:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_2;
      end_loop_3:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
	    temp_1 = Symbol_properties_table;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_4:
	if (level < ab_loop_bind_)
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_5:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_5;
      end_loop_6:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_8;
	  end_loop_9:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_10:
	    if (level < ab_loop_bind_)
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_11;
	  end_loop_12:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_10;
	  end_loop_10:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	instance = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(class_1);
	next_loop_13:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_14:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_13;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_13;
	      goto next_loop_14;
	    end_loop_13:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_14;
	  instance = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  slot_description = Nil;
	  class_description = 
		  lookup_global_or_kb_specific_property_value(data_interface_class,
		  Class_description_gkbprop);
	  ab_loop_list__1 = ISVREF(class_description,(SI_Long)6L);
	next_loop_15:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_15;
	  slot_description = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  if (EQ(ISVREF(slot_description,(SI_Long)3L),data_interface_class))
	      set_slot_description_value_without_noting(instance,
		      slot_description,ISVREF(slot_description,(SI_Long)6L));
	  goto next_loop_15;
	end_loop_15:;
	  goto next_loop_13;
	end_loop_14:;
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:;
    reclaim_frame_tree_1(Classes_needing_data_interface_initialization);
    Classes_needing_data_interface_initialization = Nil;
    return VALUES_1(Nil);
}

static Object Qtable;              /* table */

/* INITIALIZE-AFTER-READING-FOR-TABLE */
Object initialize_after_reading_for_table(table)
    Object table;
{
    Object frame, sub_vector_qm, method_function_qm, sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(132,59);
    frame = table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtable)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    sub_class_bit_vector = ISVREF(ISVREF(table,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	if ((SI_Long)0L != (IFIX(ISVREF(table,(SI_Long)4L)) & 
		(SI_Long)8388608L) ||  !(IFIX(Kb_flags) >= (SI_Long)234L))
	    make_table_wysiwig_if_necessary_after_reading(table);
    }
    if (IFIX(FIRST(System_version_from_kb_being_read)) == (SI_Long)7L && 
	    IFIX(SECOND(System_version_from_kb_being_read)) == (SI_Long)0L 
	    && FIXNUM_LT(System_quality_from_last_kb_read,Release_quality))
	return remove_bogus_parent_property_from_text_cells(table);
    else
	return VALUES_1(Nil);
}

static Object Qparent;             /* parent */

/* REMOVE-BOGUS-PARENT-PROPERTY-FROM-TEXT-CELLS */
Object remove_bogus_parent_property_from_text_cells(table)
    Object table;
{
    Object row, ab_loop_list_, cell_qm, ab_loop_list__1;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,60);
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      cell_qm = Nil;
      ab_loop_list__1 = Row;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_qm = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (CONSP(cell_qm))
	  change_text_cell_property(cell_qm,Qparent,Nil);
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MAKE-TABLE-WYSIWIG-IF-NECESSARY-AFTER-READING */
Object make_table_wysiwig_if_necessary_after_reading(table)
    Object table;
{
    x_note_fn_call(132,61);
    update_images_of_block(table,T,Nil);
    reformat_table_in_place(1,table);
    return update_images_of_block(table,Nil,Nil);
}

/* DELETE-BLOCKS-AND-CONNECTIONS-TO-BE-DELETED-AFTER-READING */
Object delete_blocks_and_connections_to_be_deleted_after_reading()
{
    Object do_not_note_permanent_changes_p, reference_serial_number;
    Object rules_seen, frame, ab_loop_list_, gensymed_symbol, xa, ya;
    Object sub_class_bit_vector, rule, connection;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,62);
    do_not_note_permanent_changes_p = T;
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      rules_seen = Qnil;
      frame = Nil;
      ab_loop_list_ = Blocks_to_delete_after_reading_kb;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      frame = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = ISVREF(frame,(SI_Long)3L);
      temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
	      Qavailable_frame_vector) : TRUEP(Qnil);
      if (temp);
      else
	  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		  (SI_Long)-1L : TRUEP(Nil);
      if (temp);
      else if (FIXNUMP(reference_serial_number))
	  temp = FIXNUMP(gensymed_symbol) ? 
		  FIXNUM_LT(reference_serial_number,gensymed_symbol) : 
		  TRUEP(T);
      else if (FIXNUMP(gensymed_symbol))
	  temp = TRUEP(Nil);
      else {
	  xa = M_CAR(reference_serial_number);
	  ya = M_CAR(gensymed_symbol);
	  temp = FIXNUM_LT(xa,ya);
	  if (temp);
	  else
	      temp = FIXNUM_EQ(xa,ya) ? 
		      FIXNUM_LT(M_CDR(reference_serial_number),
		      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
      }
      if ( !temp) {
	  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
		  (SI_Long)18L));
	  sub_class_vector_index = superior_class_bit_number >>  -  - 
		  (SI_Long)3L;
	  if (sub_class_vector_index < 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	      gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		      sub_class_vector_index);
	      gensymed_symbol_2 = (SI_Long)1L;
	      gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	      gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	      gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
	      temp = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      rules_seen = gensym_cons_1(frame,rules_seen);
	  else
	      delete_frame(frame);
      }
      goto next_loop;
    end_loop:
      rule = Nil;
      ab_loop_list_ = rules_seen;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      rule = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = ISVREF(rule,(SI_Long)3L);
      temp = SIMPLE_VECTOR_P(rule) ? EQ(ISVREF(rule,(SI_Long)1L),
	      Qavailable_frame_vector) : TRUEP(Qnil);
      if (temp);
      else
	  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		  (SI_Long)-1L : TRUEP(Nil);
      if (temp);
      else if (FIXNUMP(reference_serial_number))
	  temp = FIXNUMP(gensymed_symbol) ? 
		  FIXNUM_LT(reference_serial_number,gensymed_symbol) : 
		  TRUEP(T);
      else if (FIXNUMP(gensymed_symbol))
	  temp = TRUEP(Nil);
      else {
	  xa = M_CAR(reference_serial_number);
	  ya = M_CAR(gensymed_symbol);
	  temp = FIXNUM_LT(xa,ya);
	  if (temp);
	  else
	      temp = FIXNUM_EQ(xa,ya) ? 
		      FIXNUM_LT(M_CDR(reference_serial_number),
		      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
      }
      if ( !temp)
	  delete_frame(rule);
      goto next_loop_1;
    end_loop_1:;
      reclaim_gensym_list_1(rules_seen);
      connection = Nil;
      ab_loop_list_ = Connections_to_delete_after_reading_kb;
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      connection = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = ISVREF(connection,(SI_Long)10L);
      temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
	      (SI_Long)-1L : TRUEP(Nil);
      if (temp);
      else if (FIXNUMP(reference_serial_number))
	  temp = FIXNUMP(gensymed_symbol) ? 
		  FIXNUM_LT(reference_serial_number,gensymed_symbol) : 
		  TRUEP(T);
      else if (FIXNUMP(gensymed_symbol))
	  temp = TRUEP(Nil);
      else {
	  xa = M_CAR(reference_serial_number);
	  ya = M_CAR(gensymed_symbol);
	  temp = FIXNUM_LT(xa,ya);
	  if (temp);
	  else
	      temp = FIXNUM_EQ(xa,ya) ? 
		      FIXNUM_LT(M_CDR(reference_serial_number),
		      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
      }
      if ( !temp)
	  delete_connection(1,connection);
      goto next_loop_2;
    end_loop_2:;
      reclaim_gensym_list_1(Connections_to_delete_after_reading_kb);
      Connections_to_delete_after_reading_kb = Nil;
      reclaim_gensym_list_1(Blocks_to_delete_after_reading_kb);
      reclaim_frame_serial_number(reference_serial_number);
      Blocks_to_delete_after_reading_kb = Nil;
      result = VALUES_1(Blocks_to_delete_after_reading_kb);
    POP_SPECIAL();
    return result;
}

/* ENTER-OLD-THINGS-INTO-MAP */
Object enter_old_things_into_map()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, x, y, xa, ya;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp_1, ab_less_than_branch_qm_;
    Object gensymed_symbol_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(132,63);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qblock);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L)) {
	  x = ISVREF(block,(SI_Long)3L);
	  y = Basis_kb_frame_serial_number;
	  if (FIXNUMP(x))
	      temp = FIXNUMP(y) ? FIXNUM_LE(x,y) : TRUEP(T);
	  else if (FIXNUMP(y))
	      temp = TRUEP(Nil);
	  else {
	      xa = M_CAR(x);
	      ya = M_CAR(y);
	      temp = FIXNUM_LT(xa,ya);
	      if (temp);
	      else
		  temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LE(M_CDR(x),M_CDR(y)) : 
			  TRUEP(Qnil);
	  }
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  enter_frame_into_frame_serial_number_map(ISVREF(block,
		  (SI_Long)3L),block);
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	  ab_skip_list_form_ = gensymed_symbol;
	  ab_skip_list_p_ = Nil;
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_connection_ = Nil;
	  ab_connection_item_ = Nil;
	  connection = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    gensymed_symbol = CDR(ab_skip_list_form_);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = CDR(ab_skip_list_form_);
	  next_loop_2:
	  next_loop_3:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_connection_ = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_skip_list_p_) {
		if (ab_next_node_) {
		    ab_current_node_ = ab_next_node_;
		    ab_next_node_ = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			    (SI_Long)0L),(SI_Long)0L));
		    if (EQ(ab_next_node_,ab_tail_node_))
			ab_next_node_ = Nil;
		    ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		    ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
		}
		else
		    ab_current_node_ = Nil;
	    }
	    else {
		if (ab_next_node_) {
		    ab_current_node_ = ab_next_node_;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_4:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_4;
		  end_loop_2:;
		}
		else if (ab_node_stack_) {
		    ab_next_node_ = ab_node_stack_;
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		else
		    ab_current_node_ = Nil;
		if (ab_current_node_) {
		    ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_connection_ = M_CAR(ab_entry_cons_);
		    ab_connection_item_ = M_CDR(ab_entry_cons_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		    ab_connection_ && EQ(ISVREF(ab_connection_,
		    (SI_Long)2L),block))
		goto end_1;
	    goto next_loop_3;
	  end_loop_3:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_4;
	    connection = ab_connection_;
	    if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)64L))) {
		x = ISVREF(connection,(SI_Long)10L);
		y = Basis_kb_frame_serial_number;
		if (FIXNUMP(x))
		    temp = FIXNUMP(y) ? FIXNUM_LT(x,y) : TRUEP(T);
		else if (FIXNUMP(y))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(x);
		    ya = M_CAR(y);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(x),
				M_CDR(y)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = ISVREF(connection,(SI_Long)10L);
		    gensymed_symbol_1 = Basis_kb_frame_serial_number;
		    temp = FIXNUMP(gensymed_symbol) ? 
			    (FIXNUMP(gensymed_symbol_1) ? 
			    FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
			    TRUEP(Nil)) : FIXNUMP(gensymed_symbol_1) ? 
			    TRUEP(Nil) : FIXNUM_EQ(M_CAR(gensymed_symbol),
			    M_CAR(gensymed_symbol_1)) && 
			    FIXNUM_EQ(M_CDR(gensymed_symbol),
			    M_CDR(gensymed_symbol_1));
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		enter_frame_into_frame_serial_number_map(ISVREF(connection,
			(SI_Long)10L),connection);
	    goto next_loop_2;
	  end_loop_4:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object float_constant;      /* 0.0 */

/* FINISH-READING-SLOT-VALUE-FLOAT */
Object finish_reading_slot_value_float(significand_1,postfix_character,
	    significand_might_be_a_bignum_qm)
    Object significand_1, postfix_character, significand_might_be_a_bignum_qm;
{
    Object exponent, temp;
    double positive_gensym_float;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(132,64);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	exponent = read_element_for_kb(Nil);
	if ( !TRUEP(significand_might_be_a_bignum_qm) ? 
		IFIX(significand_1) == (SI_Long)0L : TRUEP(Nil))
	    positive_gensym_float = 0.0;
	else {
	    temp = scale_float(lfloat(significand_1,float_constant),exponent);
	    positive_gensym_float = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	if ( !CHARACTERP(postfix_character))
	    temp = DOUBLE_TO_DOUBLE_FLOAT( - positive_gensym_float);
	else
	    switch (ICHAR_CODE(postfix_character)) {
	      case 'P':
		temp = DOUBLE_TO_DOUBLE_FLOAT(positive_gensym_float);
		break;
	      default:
		temp = DOUBLE_TO_DOUBLE_FLOAT( - positive_gensym_float);
		break;
	    }
	result = make_slot_value_float(temp);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qtable_item;         /* table-item */

static Object Qsubstitute_class_and_kb_flags;  /* substitute-class-and-kb-flags */

static Object Qframe_flags;        /* frame-flags */

static Object Qname_of_defined_class;  /* name-of-defined-class */

static Object Qsuperior_of_defined_class;  /* superior-of-defined-class */

static Object Qdirect_superiors_of_defined_class;  /* direct-superiors-of-defined-class */

static Object Qcapabilities_of_class;  /* capabilities-of-class */

static Object Qdefault_overrides_of_system_slots;  /* default-overrides-of-system-slots */

static Object Qattribute_descriptions_for_class;  /* attribute-descriptions-for-class */

static Object Qline_color_of_icon;  /* line-color-of-icon */

static Object Qicon_description_for_class_qm;  /* icon-description-for-class? */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qsystem_frame;       /* system-frame */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qabsent_slot_putter;  /* absent-slot-putter */

static Object string_constant_35;  /* "~S contains a value for attribute ~NQ in an instance ~
				    *                      of class ~NR, which does not have such an attribute.  The ~
				    *                      value will simply be discarded. Please notify Gensym Customer Support."
				    */

static Object Qcomputation_style;  /* computation-style */

static Object Qkb_save_with_runtime_data;  /* kb-save-with-runtime-data */

static Object Qui_client_item;     /* ui-client-item */

/* READ-FRAME-FOR-KB */
Object read_frame_for_kb(character_1,top_level_element_qm)
    Object character_1, top_level_element_qm;
{
    Object frame_serial_number_qm, class_1, class_was_substituted_qm, temp;
    Object substitute_class_and_kb_flags_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, gensymed_symbol;
    Object tail, head, new_cons, temp_3, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object sub_class_bit_vector, class_description, class_inheritance_path;
    Object frame_is_block_qm, definition_being_read_in_is_a_ghost_qm;
    Object kb_object_index_for_frame, frame_qm, frame, index_space, index_1;
    Object object, frame_being_read_qm;
    Object slot_description_for_slot_value_being_read_qm;
    Object name_of_defined_class_qm, capabilities_of_class_qm;
    Object attribute_descriptions_qm, default_overrides_of_system_slots_qm;
    Object superior_of_defined_class_qm, direct_superiors_of_defined_class_qm;
    Object format_name_qm, line_color_of_icon_qm;
    Object icon_description_for_class_qm, slot_denotation_or_left_edge;
    Object slot_name, class_qualifier_qm, slot_value;
    Object original_qualifier_name_qm, substitute_qualifier_name_qm, kb_flags;
    Object variables_spec_qm, variable_values_qm, slot_description_qm;
    Object absent_slot_putter_qm, adjusted_direct_superiors;
    Object old_format_frame_to_return_qm, existing_computation_style;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp_4;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(132,65);
    frame_serial_number_qm = New_saved_kb_format_p && CHAR_EQ(CHR('F'),
	    character_1) ? read_element_for_kb(Nil) : Nil;
    class_1 = read_element_for_kb(Nil);
    class_was_substituted_qm = Nil;
    if ( !TRUEP(New_saved_kb_format_p)) {
	read_past_element_for_kb(Nil);
	read_past_element_for_kb(Nil);
    }
    if ( !TRUEP(lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop)) && malformed_symbol_name_p(class_1))
	class_1 = find_similar_class_name(class_1);
    if (EQ(class_1,Qtable))
	class_1 = Qtable_item;
    if (Class_name_conflicts) {
	temp = assq_function(class_1,Class_name_conflicts);
	temp_1 = TRUEP(SECOND(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = assq_function(class_1,Class_name_conflicts);
	class_1 = SECOND(temp);
    }
    else {
	if (Loading_kb_p) {
	    substitute_class_and_kb_flags_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
		    Qsubstitute_class_and_kb_flags);
	    if (substitute_class_and_kb_flags_qm && FIXNUM_LT(Kb_flags,
		    M_CDR(substitute_class_and_kb_flags_qm))) {
		temp = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
			Qsubstitute_class_and_kb_flags);
		temp_1 = TRUEP(CAR(temp));
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (Loading_kb_p) {
		substitute_class_and_kb_flags_qm = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
			Qsubstitute_class_and_kb_flags);
		if (substitute_class_and_kb_flags_qm && FIXNUM_LT(Kb_flags,
			M_CDR(substitute_class_and_kb_flags_qm))) {
		    temp = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
			    Qsubstitute_class_and_kb_flags);
		    class_1 = CAR(temp);
		}
		else
		    class_1 = Nil;
	    }
	    else
		class_1 = Nil;
	    class_was_substituted_qm = T;
	}
    }
    if (top_level_element_qm && Deferred_class_definitions_alist) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_1;
      end_loop_2:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop;
      end_loop:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
	    temp_2 = Symbol_properties_table;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp_2,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Class_definition_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		temp_1 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	install_deferred_class_definitions();
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
    frame_is_block_qm = memq_function(Qblock,class_inheritance_path);
    definition_being_read_in_is_a_ghost_qm = Nil;
    kb_object_index_for_frame = Nil;
    if (New_saved_kb_format_p) {
	if (frame_serial_number_qm) {
	    frame_qm = 
		    get_frame_given_frame_serial_number(frame_serial_number_qm);
	    if (frame_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_1 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? (SI_Long)0L != (IFIX(ISVREF(frame_qm,
		    (SI_Long)5L)) & (SI_Long)32L) : TRUEP(Nil))
		definition_being_read_in_is_a_ghost_qm = T;
	    if ( !TRUEP(frame_qm) || definition_being_read_in_is_a_ghost_qm) {
		frame_qm = 
			make_frame_without_computed_initializations(class_description,
			Nil,Nil);
		if ( !TRUEP(definition_being_read_in_is_a_ghost_qm))
		    enter_frame_into_frame_serial_number_map(frame_serial_number_qm,
			    frame_qm);
	    }
	    frame = frame_qm;
	}
	else
	    frame = 
		    make_frame_without_computed_initializations(class_description,
		    Nil,Nil);
    }
    else {
	gensymed_symbol = assign_index_in_index_space(Kb_object_index_space);
	index_space = Kb_object_index_space;
	index_1 = gensymed_symbol;
	object = 
		make_frame_without_computed_initializations(class_description,
		Nil,Nil);
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,index_1);
	temp_3 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
		-  - (SI_Long)10L);
	temp_4 = IFIX(index_1) & (SI_Long)1023L;
	frame = ISVREF(temp_3,temp_4) = object;
	kb_object_index_for_frame = ISVREF(Kb_object_index_space,(SI_Long)3L);
    }
    frame_being_read_qm = frame;
    PUSH_SPECIAL_WITH_SYMBOL(Frame_being_read_qm,Qframe_being_read_qm,frame_being_read_qm,
	    2);
      slot_description_for_slot_value_being_read_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Slot_description_for_slot_value_being_read_qm,Qslot_description_for_slot_value_being_read_qm,slot_description_for_slot_value_being_read_qm,
	      1);
	name_of_defined_class_qm = Nil;
	capabilities_of_class_qm = Nil;
	attribute_descriptions_qm = Nil;
	default_overrides_of_system_slots_qm = Nil;
	superior_of_defined_class_qm = Nil;
	direct_superiors_of_defined_class_qm = Nil;
	format_name_qm = Nil;
	line_color_of_icon_qm = Nil;
	icon_description_for_class_qm = Nil;
	slot_denotation_or_left_edge = Nil;
	slot_name = Nil;
	class_qualifier_qm = Nil;
	slot_value = Nil;
	if (class_was_substituted_qm)
	    Frames_with_substitute_classes = gensym_cons_1(frame,
		    Frames_with_substitute_classes);
	if (frame_is_block_qm &&  !((SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)5L)) & (SI_Long)4194304L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qframe_flags);
	    temp_4 = IFIX(ISVREF(frame,(SI_Long)4L)) &  ~(SI_Long)1L;
	    ISVREF(frame,(SI_Long)4L) = FIX(temp_4);
	}
      next_loop_12:
	if ( !TRUEP(Read_kb_buffer_index))
	    character_1 = Nil;
	else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    temp_3 = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = temp_3;
	    character_1 = temp;
	}
	else
	    character_1 = read_next_char_for_kb_from_refilled_buffer();
	temp = CHAR_CODE(character_1);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L)))) {
	    temp_3 = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = temp_3;
	}
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 33:
		goto end_loop_12;
		break;
	      case 91:
		if (Warmbooting_qm)
		    read_runtime_data_for_block(frame);
		else
		    read_past_runtime_data_for_block(Nil);
		goto end_loop_12;
		break;
	      default:
		temp_3 = FIXNUM_SUB1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_3;
		break;
	    }
	slot_denotation_or_left_edge = read_element_for_kb(Nil);
	if (FIXNUMP(slot_denotation_or_left_edge)) {
	    read_final_block_data_in_old_format_kb(frame,
		    slot_denotation_or_left_edge);
	    goto end_loop_12;
	}
	else {
	    slot_name = CONSP(slot_denotation_or_left_edge) ? 
		    M_CAR(M_CDR(M_CDR(slot_denotation_or_left_edge))) : 
		    slot_denotation_or_left_edge;
	    original_qualifier_name_qm = 
		    CONSP(slot_denotation_or_left_edge) ? 
		    M_CAR(M_CDR(slot_denotation_or_left_edge)) : Nil;
	    temp = assq_function(original_qualifier_name_qm,
		    Class_name_conflicts);
	    substitute_qualifier_name_qm = SECOND(temp);
	    temp = substitute_qualifier_name_qm;
	    if (temp);
	    else
		temp = original_qualifier_name_qm;
	    class_qualifier_qm = temp;
	    Slot_description_for_slot_value_being_read_qm = 
		    get_slot_description_of_class_description_function(slot_name,
		    class_description,class_qualifier_qm);
	    reclaim_slot_value(slot_denotation_or_left_edge);
	}
	slot_value = read_element_for_kb(Nil);
	if (EQ(slot_name,Qname_of_defined_class))
	    name_of_defined_class_qm = slot_value;
	else if (EQ(slot_name,Qsuperior_of_defined_class))
	    superior_of_defined_class_qm = slot_value;
	else if (EQ(slot_name,Qdirect_superiors_of_defined_class))
	    direct_superiors_of_defined_class_qm = slot_value;
	else if (EQ(slot_name,Qcapabilities_of_class))
	    capabilities_of_class_qm = slot_value;
	else if (EQ(slot_name,Qdefault_overrides_of_system_slots))
	    default_overrides_of_system_slots_qm = slot_value;
	else if (EQ(slot_name,Qattribute_descriptions_for_class))
	    attribute_descriptions_qm = slot_value;
	else if (EQ(slot_name,Qline_color_of_icon)) {
	    if (SYMBOLP(slot_value) && color_or_metacolor_p(slot_value)) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_1 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		line_color_of_icon_qm = slot_value;
	}
	else if (EQ(slot_name,Qicon_description_for_class_qm)) {
	    kb_flags = FIX((SI_Long)0L);
	    variables_spec_qm = Nil;
	    variable_values_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
	      if ( !(IFIX(Kb_flags) >= (SI_Long)258L)) {
		  variables_spec_qm = 
			  get_variable_specification_if_any(slot_value);
		  variable_values_qm = CDR(variables_spec_qm);
		  if (variable_values_qm) {
		      temp = M_CAR(variable_values_qm);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      temp_3 = convert_alist_to_plist(variable_values_qm);
		      M_CDR(variables_spec_qm) = temp_3;
		  }
	      }
	    POP_SPECIAL();
	    icon_description_for_class_qm = slot_value;
	}
	else if (EQ(slot_name,Qname_or_names_for_frame)) {
	    if ( !(IFIX(Kb_flags) >= (SI_Long)3L) ? 
		    TRUEP(memq_function(Qclass_definition,
		    class_inheritance_path)) : TRUEP(Nil));
	    else if (memq_function(Qformat_frame,class_inheritance_path))
		format_name_qm = slot_value;
	    else if (memq_function(Qsystem_frame,class_inheritance_path)) {
		put_name_or_names_for_frame(frame,slot_value,T);
		System_tables_read_for_this_module = 
			slot_value_cons_1(frame,
			System_tables_read_for_this_module);
	    }
	    else
		put_name_or_names_for_frame(frame,slot_value,T);
	}
	else if (EQ(slot_name,Qslot_group_for_block_qm))
	    process_slot_group_for_block(frame,slot_value);
	else {
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(slot_name,
		    ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
	    if ( !TRUEP(slot_description_qm) && 
		    malformed_symbol_name_p(slot_name)) {
		slot_name = find_similar_slot_name(slot_name,class_1);
		slot_description_qm = 
			get_slot_description_of_class_description_function(slot_name,
			ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
	    }
	    if ( !TRUEP(slot_description_qm)) {
		absent_slot_putter_qm = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_name),
			Qabsent_slot_putter);
		if (absent_slot_putter_qm)
		    inline_funcall_2(absent_slot_putter_qm,frame,slot_value);
		else
		    notify_user(6,string_constant_35,
			    Name_text_string_for_kb_being_read,slot_name,
			    class_qualifier_qm,frame,class_1);
	    }
	    else {
		initialize_slot_description_value(frame,
			slot_description_qm,slot_value);
		if (EQ(slot_name,Qframe_flags)) {
		    temp_4 = IFIX(ISVREF(frame,(SI_Long)5L)) | 
			    (SI_Long)4194304L;
		    ISVREF(frame,(SI_Long)5L) = FIX(temp_4);
		}
	    }
	}
	goto next_loop_12;
      end_loop_12:
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_1 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = frame;
	    temp = gensym_cons_1(temp,
		    copy_frame_serial_number(Current_frame_serial_number));
	    Definitions_read_in_this_module = gensym_cons_1(temp,
		    Definitions_read_in_this_module);
	}
	else
	    initialize_slots_of_frame_needing_evaluation(frame);
	if (EQ(class_1,Qcomputation_style)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qframe_flags);
	    temp_4 = IFIX(ISVREF(frame,(SI_Long)4L)) | (SI_Long)1L;
	    ISVREF(frame,(SI_Long)4L) = FIX(temp_4);
	}
	if (icon_description_for_class_qm)
	    fixup_icon_description_for_class(frame,
		    icon_description_for_class_qm,line_color_of_icon_qm);
	else if (line_color_of_icon_qm && 
		get_lookup_slot_value_given_default(frame,
		Qicon_description_for_class_qm,Nil))
	    fix_icon_description_for_class_slot(frame,Nil,Nil,Nil,
		    line_color_of_icon_qm);
	if (name_of_defined_class_qm || superior_of_defined_class_qm || 
		direct_superiors_of_defined_class_qm) {
	    adjusted_direct_superiors = superior_of_defined_class_qm ? 
		    (ATOM(superior_of_defined_class_qm) ? 
		    slot_value_cons_1(superior_of_defined_class_qm,Nil) : 
		    superior_of_defined_class_qm) : 
		    direct_superiors_of_defined_class_qm;
	    adjust_direct_superiors_per_class_conflicts(adjusted_direct_superiors);
	    temp = frame;
	    initialize_slot_description_value(temp,
		    get_slot_description_of_class_description_function(Qdirect_superiors_of_defined_class,
		    ISVREF(frame,(SI_Long)1L),Nil),adjusted_direct_superiors);
	}
	if (attribute_descriptions_qm || 
		    default_overrides_of_system_slots_qm) {
	    if ( !LISTP(default_overrides_of_system_slots_qm))
		default_overrides_of_system_slots_qm = Nil;
	    process_pre_4_dot_0_attribute_descriptions_and_default_overrides(frame,
		    name_of_defined_class_qm,attribute_descriptions_qm,
		    ISVREF(frame,(SI_Long)21L),
		    default_overrides_of_system_slots_qm,Nil,Nil);
	}
	if (capabilities_of_class_qm && name_of_defined_class_qm) {
	    process_pre_4_dot_0_capabilities_of_class(frame,
		    name_of_defined_class_qm,capabilities_of_class_qm,Nil);
	    if (capabilities_of_class_qm && CONSP(capabilities_of_class_qm))
		reclaim_slot_value_tree_1(capabilities_of_class_qm);
	}
	if (frame_is_block_qm && get_lookup_slot_value_given_default(frame,
		Qname_or_names_for_frame,Nil)) {
	    temp = frame;
	    record_name_conflict_if_necessary(temp,
		    get_lookup_slot_value_given_default(frame,
		    Qname_or_names_for_frame,Nil));
	}
	if (name_of_defined_class_qm && Reading_ghost_definitions_p)
	    Class_name_read_while_reading_current_ghost_definition = 
		    name_of_defined_class_qm;
	else if (definition_being_read_in_is_a_ghost_qm)
	    delete_block_after_reading_kb(frame);
	else if (name_of_defined_class_qm) {
	    if (IFIX(Kb_flags) >= (SI_Long)3L)
		install_class_definition(name_of_defined_class_qm,frame,
			Nil,Nil,T);
	    else
		defer_class_definition(name_of_defined_class_qm,frame);
	}
	else if (format_name_qm || memq_function(Qformat_frame,
		class_inheritance_path)) {
	    old_format_frame_to_return_qm = 
		    finish_reading_format_frame_for_kb(frame,format_name_qm);
	    if (old_format_frame_to_return_qm) {
		frame = old_format_frame_to_return_qm;
		if (New_saved_kb_format_p)
		    enter_frame_into_frame_serial_number_map(frame_serial_number_qm,
			    frame);
		else {
		    if (FIXNUM_GE(kb_object_index_for_frame,
			    ISVREF(Kb_object_index_space,(SI_Long)4L)))
			enlarge_index_space(Kb_object_index_space,
				kb_object_index_for_frame);
		    temp_3 = ISVREF(ISVREF(Kb_object_index_space,
			    (SI_Long)2L),IFIX(kb_object_index_for_frame) 
			    >>  -  - (SI_Long)10L);
		    temp_4 = IFIX(kb_object_index_for_frame) & (SI_Long)1023L;
		    ISVREF(temp_3,temp_4) = frame;
		}
	    }
	}
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qcomputation_style,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_1 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		existing_computation_style = 
			get_or_make_entry_to_set_of_all_permanent_computation_styles(frame);
		if ( !EQ(frame,existing_computation_style)) {
		    delete_block_after_reading_kb(frame);
		    frame = existing_computation_style;
		    enter_frame_into_frame_serial_number_map(frame_serial_number_qm,
			    frame);
		}
	    }
	}
	if (EQ(Type_of_file_being_read,Qkb_save_with_runtime_data) && 
		frame_is_block_qm) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
		    (SI_Long)1L))) {
		temp_4 = IFIX(ISVREF(frame,(SI_Long)5L)) | (SI_Long)262144L;
		ISVREF(frame,(SI_Long)5L) = FIX(temp_4);
	    }
	    if (Warmbooting_qm) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_invocation_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_1 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1);
		else {
		    gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
		    gensymed_symbol = gensymed_symbol ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol,
			    (SI_Long)5L)) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(Qui_client_item,
				Class_description_gkbprop);
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(ISVREF(frame,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_3 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_4 = (SI_Long)1L;
				gensymed_symbol_5 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_4 = gensymed_symbol_4 << 
					gensymed_symbol_5;
				gensymed_symbol_3 = gensymed_symbol_3 & 
					gensymed_symbol_4;
				temp_1 = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		delete_block_after_unsquirreling(frame);
	    else if ( !TRUEP(Warmbooting_qm) && (SI_Long)0L != 
		    (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)262144L))
		delete_block_after_reading_kb(frame);
	}
	temp = frame;
	goto end_5;
	temp = Qnil;
      end_5:;
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* INITIALIZE-UNBOUND-SLOTS-IN-DEFINITIONS */
Object initialize_unbound_slots_in_definitions()
{
    Object definition_and_fsn, ab_loop_list_, definition, fsn, gensymed_symbol;
    Object xa, ya;
    char temp;

    x_note_fn_call(132,66);
    definition_and_fsn = Nil;
    ab_loop_list_ = Definitions_read_in_this_module;
    definition = Nil;
    fsn = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    definition_and_fsn = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    definition = CAR(definition_and_fsn);
    fsn = CDR(definition_and_fsn);
    gensymed_symbol = ISVREF(definition,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(definition) ? EQ(ISVREF(definition,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	initialize_slots_of_frame_needing_evaluation(definition);
    reclaim_frame_serial_number(fsn);
    reclaim_gensym_cons_1(definition_and_fsn);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(Definitions_read_in_this_module);
    return VALUES_1(Nil);
}

static Object Qfilled_polygon;     /* filled-polygon */

/* FIXUP-ICON-DESCRIPTION-FOR-CLASS */
Object fixup_icon_description_for_class(frame,icon_description_for_class_1,
	    line_color_of_icon_qm)
    Object frame, icon_description_for_class_1, line_color_of_icon_qm;
{
    Object thing, ab_loop_list_, second_thing, temp;

    x_note_fn_call(132,67);
    if ( !TRUEP(icon_editor_fixed_p_function())) {
	thing = Nil;
	ab_loop_list_ = CDDR(icon_description_for_class_1);
	second_thing = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(thing) && EQ(CAR(thing),Qfilled_polygon) &&  
		!TRUEP(clockwise_polygon_p(SECOND(thing)))) {
	    second_thing = SECOND(thing);
	    temp = nreverse(copy_for_slot_value(SECOND(thing)));
	    M_SECOND(thing) = temp;
	    reclaim_slot_value(second_thing);
	}
	goto next_loop;
      end_loop:;
    }
    if ( !(IFIX(Kb_flags) >= (SI_Long)252L && 
	    get_variable_specification_if_any(icon_description_for_class_1) 
	    && 
	    get_icon_background_layer_if_any(icon_description_for_class_1) 
	    && IFIX(Kb_flags) >= (SI_Long)240L &&  
	    !TRUEP(empty_layer_in_icon_description_p(CDDR(icon_description_for_class_1))))) 
		{
	temp = 
		fix_line_drawing_description_for_class(CDDR(icon_description_for_class_1),
		line_color_of_icon_qm);
	M_CDDR(icon_description_for_class_1) = temp;
    }
    return initialize_slot_description_value(frame,
	    get_slot_description_of_class_description_function(Qicon_description_for_class_qm,
	    ISVREF(frame,(SI_Long)1L),Nil),icon_description_for_class_1);
}

/* BLINKING-AREA-P */
Object blinking_area_p(icon_description_element)
    Object icon_description_element;
{
    Object temp;
    char temp_1;

    x_note_fn_call(132,68);
    if (CDR(icon_description_element)) {
	temp = CADR(icon_description_element);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = CADR(icon_description_element);
	temp = CAR(temp);
	return VALUES_1(SYMBOLP(temp) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* EMPTY-LAYER-IN-ICON-DESCRIPTION-P */
Object empty_layer_in_icon_description_p(line_drawing_description)
    Object line_drawing_description;
{
    Object previous_element_was_layer_name_p, element, ab_loop_list_;
    Object element_is_layer_name_p, ab_loop_it_;

    x_note_fn_call(132,69);
    previous_element_was_layer_name_p = Nil;
    element = Nil;
    ab_loop_list_ = line_drawing_description;
    element_is_layer_name_p = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    element_is_layer_name_p = SYMBOLP(element) ? T : Nil;
    ab_loop_it_ = previous_element_was_layer_name_p ? 
	    element_is_layer_name_p : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    previous_element_was_layer_name_p = element_is_layer_name_p;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qpolychrome;         /* polychrome */

static Object Qvariables;          /* variables */

static Object Qbackground_layer;   /* background-layer */

static Object Qicon_color;         /* icon-color */

static Object Qforeground;         /* foreground */

/* FIX-LINE-DRAWING-DESCRIPTION-FOR-CLASS */
Object fix_line_drawing_description_for_class(line_drawing_description,
	    line_color_of_icon_qm)
    Object line_drawing_description, line_color_of_icon_qm;
{
    Object first_element, slot_value_push_modify_macro_arg, car_1, cdr_1, temp;
    Object description_elements, description_element, l, temp_1;
    Object polychrome_header, last_cons, current_cons, next_cons;
    char temp_2;

    x_note_fn_call(132,70);
    first_element = CAR(line_drawing_description);
    if ( !(CONSP(first_element) && EQ(CAR(first_element),Qpolychrome) ? 
	    TRUEP(first_element) : TRUEP(Nil)))
	line_drawing_description = 
		slot_value_cons_1(slot_value_cons_1(Qpolychrome,Nil),
		line_drawing_description);
    if ( !TRUEP(get_variable_specification_if_any(line_drawing_description))) {
	slot_value_push_modify_macro_arg = slot_value_cons_1(Qvariables,Nil);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(line_drawing_description);
	temp = slot_value_cons_1(car_1,cdr_1);
	M_CDR(line_drawing_description) = temp;
    }
    if ( !TRUEP(get_icon_background_layer_if_any(line_drawing_description))) {
	slot_value_push_modify_macro_arg = 
		slot_value_cons_1(Qbackground_layer,Nil);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDDR(line_drawing_description);
	temp = slot_value_cons_1(car_1,cdr_1);
	M_CDDR(line_drawing_description) = temp;
    }
    description_elements = CDR(line_drawing_description);
    description_element = Nil;
  next_loop:
    if ( !TRUEP(description_elements))
	goto end_loop;
    description_element = CAR(description_elements);
    if (CONSP(description_element) && blinking_area_p(description_element)) {
	l = CDR(description_element);
      next_loop_1:
	if ( !TRUEP(l))
	    goto end_loop_1;
	temp_1 = CAR(l);
	temp_1 = CAR(temp_1);
	if ( !SYMBOLP(temp_1)) {
	    M_CDR(description_element) = l;
	    goto end_1;
	}
	l = M_CDR(l);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    description_elements = M_CDR(description_elements);
    goto next_loop;
  end_loop:;
    polychrome_header = CAR(line_drawing_description);
    if (line_color_of_icon_qm &&  !TRUEP(assq_function(Qicon_color,
	    CDR(polychrome_header)))) {
	slot_value_push_modify_macro_arg = slot_value_cons_1(Qicon_color,
		line_color_of_icon_qm);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(polychrome_header);
	temp = slot_value_cons_1(car_1,cdr_1);
	M_CDR(polychrome_header) = temp;
	car_1 = Qicon_color;
	cdr_1 = CDDDR(line_drawing_description);
	temp = slot_value_cons_1(car_1,cdr_1);
	M_CDDDR(line_drawing_description) = temp;
    }
    if (empty_layer_in_icon_description_p(CDDDR(line_drawing_description))) {
	last_cons = Nil;
	current_cons = CDDDR(line_drawing_description);
	next_cons = Nil;
      next_loop_2:
	if ( !TRUEP(current_cons))
	    goto end_loop_2;
	next_cons = CDR(current_cons);
	temp_1 = CAR(current_cons);
	if (SYMBOLP(temp_1)) {
	    temp_1 = CADR(current_cons);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    if (last_cons)
		M_CDR(last_cons) = next_cons;
	    else
		M_CDDDR(line_drawing_description) = next_cons;
	    reclaim_slot_value_cons_1(current_cons);
	}
	last_cons = current_cons;
	current_cons = next_cons;
	goto next_loop_2;
      end_loop_2:;
    }
    temp_1 = CDDDR(line_drawing_description);
    temp_1 = FIRST(temp_1);
    temp_2 =  !SYMBOLP(temp_1) ? TRUEP(CDR(polychrome_header)) : TRUEP(Nil);
    if (temp_2);
    else
	temp_2 = TRUEP(memq_function(Qforeground,
		CDR(line_drawing_description)));
    if (temp_2 ?  !TRUEP(assq_function(Qforeground,
	    CDR(polychrome_header))) : TRUEP(Nil)) {
	temp = slot_value_cons_1(slot_value_cons_1(Qforeground,
		Qforeground),CDR(polychrome_header));
	M_CDR(polychrome_header) = temp;
    }
  next_loop_3:
    if ( !TRUEP(memq_function(Qnil,CDR(polychrome_header))))
	goto end_loop_3;
    temp = delete_slot_value_element_1(Qnil,CDR(polychrome_header));
    M_CDR(polychrome_header) = temp;
    goto next_loop_3;
  end_loop_3:;
    return VALUES_1(line_drawing_description);
}

/* READ-FINAL-BLOCK-DATA-IN-OLD-FORMAT-KB */
Object read_final_block_data_in_old_format_kb(block,left_edge_of_block)
    Object block, left_edge_of_block;
{
    Object temp, temp_1, subblock, first_time_qm, character_1, subblocks;
    Object ab_loopvar_, ab_loopvar__1, temp_2, gensymed_symbol;
    Object gensymed_symbol_1, slot_group_qm;

    x_note_fn_call(132,71);
    temp = read_element_for_kb(Nil);
    temp_1 = read_element_for_kb(Nil);
    set_edges_of_block(block,left_edge_of_block,temp,temp_1,
	    read_element_for_kb(Nil));
    subblock = Nil;
    first_time_qm = T;
    character_1 = Nil;
    subblocks = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    character_1 = read_char_for_kb_past_spaces();
    if (CHAR_EQ(character_1,CHR('!')))
	goto end_loop;
    temp_2 = FIXNUM_SUB1(Read_kb_buffer_index);
    Read_kb_buffer_index = temp_2;
    subblock = read_element_for_kb(Nil);
    gensymed_symbol = subblock;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    gensymed_symbol_1 = block;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp_2 = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp_2,FIX((SI_Long)5L)) = gensymed_symbol_1;
    }
    ab_loopvar__1 = slot_value_cons_1(subblock,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	subblocks = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    first_time_qm = Nil;
    goto next_loop;
  end_loop:
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = upgrade_subblocks(subblocks);
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)4L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp_2 = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp_2,FIX((SI_Long)4L)) = gensymed_symbol_1;
    }
    return VALUES_1(Qnil);
}

static Object Quser_defined;       /* user-defined */

static Object Qindexed_attributes_for_definition;  /* indexed-attributes-for-definition */

static Object Qobject_definition;  /* object-definition */

static Object Qobject;             /* object */

static Object Qmessage_definition;  /* message-definition */

static Object Qmessage;            /* message */

static Object Qconnection_definition;  /* connection-definition */

static Object Qconnection;         /* connection */

static Object Qcar_eq;             /* car-eq */

static Object Kfuncall;            /* :funcall */

static Object string_constant_36;  /* "~%~% Urgent:  ~
				    *                           A class-specific attribute for ~a ~
				    *                           has the same name (~(~a~)) as a system-defined ~
				    *                           attribute. ~
				    *                           ~% It is extremely important to rename ~
				    *                           the ~a class-specific ~
				    *                           attribute before running this kb or doing any further ~
				    *                           development work to avoid a likely G2 failure."
				    */

static Object string_constant_37;  /* "~%~% Urgent:  ~
				    * ???  A class-specific attribute for an unnamed class ~
				    *                           has the same name (~(~a~)) as a system-defined ~
				    *                           attribute. ~
				    *                           ~% It is extremely important to rename the ~a class-specific ~
				    *                           attribute before running this kb or doing any further ~
				    *                           development work to avoid a likely G2 failure."
				    */

static Object Qab_or;              /* or */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qno_item;            /* no-item */

static Object Qclass_specific_attributes;  /* class-specific-attributes */

static Object Qdefault_overrides;  /* default-overrides */

/* PROCESS-PRE-4.0-ATTRIBUTE-DESCRIPTIONS-AND-DEFAULT-OVERRIDES */
Object process_pre_4_dot_0_attribute_descriptions_and_default_overrides(frame,
	    name_of_defined_class_qm,attribute_descriptions_qm,
	    direct_superiors_qm,default_overrides_qm,
	    change_the_text_of_attributes_qm,change_the_text_of_overrides_qm)
    Object frame, name_of_defined_class_qm, attribute_descriptions_qm;
    Object direct_superiors_qm, default_overrides_qm;
    Object change_the_text_of_attributes_qm, change_the_text_of_overrides_qm;
{
    Object class_specific_attributes_list, override, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, default_overrides_list;
    Object direct_superiors_are_defined_qm, indexed_attributes_for_definition;
    Object indexed_attributes_becoming_overrides_qm;
    Object new_superior_indexed_attributes_qm, attribute_description;
    Object attribute_name, superior_slot_description_qm;
    Object system_defined_slot_description_qm, superior, ab_loop_list__1;
    Object slot_description_qm, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, temp_2, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, definition_class;
    Object superior_class, superior_definition;
    Object list_holding_superior_information_qm, superior_information;
    Object attribute_initial_value, attribute_initial_type_qm;
    Object new_indexed_attributes_for_definition, new_indexed_attributes;
    Object superior_class_definition, ab_loop_desetq_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(132,72);
    class_specific_attributes_list = Nil;
    if (change_the_text_of_attributes_qm) {
	override = Nil;
	ab_loop_list_ = ISVREF(frame,(SI_Long)27L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(THIRD(override),Quser_defined)) {
	    ab_loopvar__2 = slot_value_cons_1(override,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	default_overrides_list = ab_loopvar_;
	goto end_1;
	default_overrides_list = Qnil;
      end_1:;
    }
    else if (change_the_text_of_overrides_qm) {
	override = Nil;
	ab_loop_list_ = ISVREF(frame,(SI_Long)27L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(THIRD(override),Quser_defined)) {
	    ab_loopvar__2 = 
		    slot_value_cons_1(copy_for_slot_value(override),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	default_overrides_list = ab_loopvar_;
	goto end_2;
	default_overrides_list = Qnil;
      end_2:;
    }
    else
	default_overrides_list = default_overrides_qm;
    direct_superiors_are_defined_qm = 
	    direct_superiors_are_defined_p(direct_superiors_qm);
    indexed_attributes_for_definition = 
	    get_lookup_slot_value_given_default(frame,
	    Qindexed_attributes_for_definition,Nil);
    indexed_attributes_becoming_overrides_qm = Nil;
    new_superior_indexed_attributes_qm = Nil;
    if (change_the_text_of_overrides_qm)
	default_overrides_list = nconc2(default_overrides_list,
		default_overrides_qm);
    else {
	attribute_description = Nil;
	ab_loop_list_ = attribute_descriptions_qm;
	attribute_name = Nil;
	superior_slot_description_qm = Nil;
	system_defined_slot_description_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	attribute_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_name = CAR(attribute_description);
	if (direct_superiors_are_defined_qm) {
	    superior = Nil;
	    ab_loop_list__1 = direct_superiors_qm;
	    slot_description_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    superior = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_4:
	    if (level < ab_loop_bind_)
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_5:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_6:
	    if ( !TRUEP(marked))
		goto end_loop_5;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_6;
	  end_loop_5:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_5;
	  end_loop_6:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_8;
	  end_loop_9:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_5;
		goto next_loop_11;
	      end_loop_12:
	      end_5:
		level = level - (SI_Long)1L;
		goto next_loop_10;
	      end_loop_10:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_13:
		if (level < ab_loop_bind_)
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_14:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_15:
		if ( !TRUEP(marked))
		    goto end_loop_14;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_15;
	      end_loop_14:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_6;
		goto next_loop_14;
	      end_loop_15:
	      end_6:
		level = level - (SI_Long)1L;
		goto next_loop_13;
	      end_loop_13:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = get_slot_name_for_alias_if_any(attribute_name,superior);
	    if (temp_1);
	    else
		temp_1 = attribute_name;
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(temp_1,
		    gensymed_symbol,Nil);
	    if (slot_description_qm) {
		superior_slot_description_qm = slot_description_qm;
		goto end_7;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    superior_slot_description_qm = Qnil;
	  end_7:;
	}
	else {
	    definition_class = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	    if (EQ(definition_class,Qobject_definition))
		superior_class = Qobject;
	    else if (EQ(definition_class,Qmessage_definition))
		superior_class = Qmessage;
	    else if (EQ(definition_class,Qconnection_definition))
		superior_class = Qconnection;
	    else
		superior_class = Qnil;
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior_class;
	    key_hash_value = SXHASH_SYMBOL_1(superior_class) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_16:
	    if (level < ab_loop_bind_)
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_17:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_18:
	    if ( !TRUEP(marked))
		goto end_loop_17;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_18;
	  end_loop_17:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_17;
	  end_loop_18:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_16;
	  end_loop_16:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior_class;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_19:
	    if (level < ab_loop_bind_)
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_20:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_21:
	    if ( !TRUEP(marked))
		goto end_loop_20;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_21;
	  end_loop_20:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_20;
	  end_loop_21:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_19;
	  end_loop_19:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_22:
		if (level < ab_loop_bind_)
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_23:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_24:
		if ( !TRUEP(marked))
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_24;
	      end_loop_23:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_23;
	      end_loop_24:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_22;
	      end_loop_22:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_25:
		if (level < ab_loop_bind_)
		    goto end_loop_25;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_26:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_27:
		if ( !TRUEP(marked))
		    goto end_loop_26;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_27;
	      end_loop_26:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_26;
	      end_loop_27:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_25;
	      end_loop_25:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = get_slot_name_for_alias_if_any(attribute_name,
		    superior_class);
	    if (temp_1);
	    else
		temp_1 = attribute_name;
	    superior_slot_description_qm = 
		    get_slot_description_of_class_description_function(temp_1,
		    gensymed_symbol,Nil);
	}
	system_defined_slot_description_qm = superior_slot_description_qm ?
		 ( !TRUEP(ISVREF(superior_slot_description_qm,
		(SI_Long)8L)) ? T : Nil) : Qnil;
	if (superior_slot_description_qm &&  
		!TRUEP(system_defined_slot_description_qm)) {
	    if (memq_function(attribute_name,
		    indexed_attributes_for_definition)) {
		superior_class = ISVREF(superior_slot_description_qm,
			(SI_Long)3L);
		superior_definition = 
			lookup_global_or_kb_specific_property_value(superior_class,
			Class_definition_gkbprop);
		temp_1 = attribute_name;
		if ( !TRUEP(memq_function(temp_1,
			get_lookup_slot_value_given_default(superior_definition,
			Qindexed_attributes_for_definition,Nil)))) {
		    list_holding_superior_information_qm = member(4,
			    superior_class,
			    new_superior_indexed_attributes_qm,Ktest,Qcar_eq);
		    if (list_holding_superior_information_qm) {
			superior_information = 
				CAR(list_holding_superior_information_qm);
			temp_2 = frame_cons_1(attribute_name,
				SECOND(superior_information));
			M_SECOND(superior_information) = temp_2;
		    }
		    else
			new_superior_indexed_attributes_qm = 
				frame_cons_1(frame_list_2(superior_class,
				frame_cons_1(attribute_name,Nil)),
				new_superior_indexed_attributes_qm);
		}
		indexed_attributes_becoming_overrides_qm = 
			frame_cons_1(attribute_name,
			indexed_attributes_becoming_overrides_qm);
	    }
	    attribute_initial_value = 
		    copy_for_slot_value(SECOND(attribute_description));
	    attribute_initial_type_qm = 
		    copy_for_slot_value(THIRD(attribute_description));
	    temp_1 = default_overrides_list;
	    if (CONSP(attribute_initial_value) && 
		    EQ(CAR(attribute_initial_value),Kfuncall))
		temp = 
			slot_value_cons_1(slot_value_list_3(FIRST(attribute_description),
			slot_value_cons_1(attribute_initial_value,Nil),
			Quser_defined),Nil);
	    else if (attribute_initial_value || attribute_initial_type_qm)
		temp = 
			slot_value_cons_1(slot_value_list_3(FIRST(attribute_description),
			attribute_initial_type_qm ? 
			slot_value_list_2(attribute_initial_value,
			attribute_initial_type_qm) : 
			attribute_initial_value,Quser_defined),Nil);
	    else
		temp = 
			slot_value_cons_1(slot_value_list_3(FIRST(attribute_description),
			Nil,Quser_defined),Nil);
	    default_overrides_list = nconc2(temp_1,temp);
	    reclaim_slot_value(attribute_description);
	}
	else {
	    if (system_defined_slot_description_qm) {
		if (name_of_defined_class_qm)
		    notify_user(4,string_constant_36,
			    name_of_defined_class_qm,attribute_name,
			    attribute_name);
		else
		    notify_user(3,string_constant_37,attribute_name,
			    attribute_name);
	    }
	    temp_2 = slot_value_cons_1(slot_value_list_3(Qab_or,
		    Qitem_or_datum,slot_value_cons_1(Qno_item,Nil)),
		    CDR(attribute_description));
	    M_CDR(attribute_description) = temp_2;
	    class_specific_attributes_list = 
		    nconc2(class_specific_attributes_list,
		    slot_value_cons_1(attribute_description,Nil));
	}
	goto next_loop_2;
      end_loop_2:;
    }
    if (indexed_attributes_becoming_overrides_qm) {
	attribute_name = Nil;
	ab_loop_list_ = indexed_attributes_for_definition;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_28:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_28;
	attribute_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(attribute_name,
		indexed_attributes_becoming_overrides_qm))) {
	    ab_loopvar__2 = slot_value_cons_1(attribute_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_28;
      end_loop_28:
	new_indexed_attributes_for_definition = ab_loopvar_;
	goto end_12;
	new_indexed_attributes_for_definition = Qnil;
      end_12:;
	prepare_for_indexed_attributes_moveage(frame,
		indexed_attributes_for_definition,
		new_indexed_attributes_for_definition);
	reclaim_frame_list_1(indexed_attributes_becoming_overrides_qm);
    }
    superior_class = Nil;
    new_indexed_attributes = Nil;
    ab_loop_list_ = new_superior_indexed_attributes_qm;
    superior_class_definition = Nil;
    indexed_attributes_for_definition = Nil;
    new_indexed_attributes_for_definition = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_29:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_29;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    superior_class = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    new_indexed_attributes = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    superior_class_definition = 
	    lookup_global_or_kb_specific_property_value(superior_class,
	    Class_definition_gkbprop);
    indexed_attributes_for_definition = 
	    get_lookup_slot_value_given_default(superior_class_definition,
	    Qindexed_attributes_for_definition,Nil);
    new_indexed_attributes_for_definition = 
	    nconc2(copy_for_slot_value(indexed_attributes_for_definition),
	    copy_for_slot_value(new_indexed_attributes));
    prepare_for_indexed_attributes_moveage(superior_class_definition,
	    indexed_attributes_for_definition,
	    new_indexed_attributes_for_definition);
    change_slot_value(3,superior_class_definition,
	    Qclass_specific_attributes,ISVREF(superior_class_definition,
	    (SI_Long)22L));
    goto next_loop_29;
  end_loop_29:;
    reclaim_frame_tree_1(new_superior_indexed_attributes_qm);
    if ( !TRUEP(change_the_text_of_overrides_qm))
	change_slot_value(3,frame,Qclass_specific_attributes,
		class_specific_attributes_list);
    temp_1 = ISVREF(frame,(SI_Long)27L);
    if ( !EQUAL(default_overrides_list,temp_1))
	change_slot_value(3,frame,Qdefault_overrides,default_overrides_list);
    if (CONSP(attribute_descriptions_qm))
	return reclaim_slot_value_list_1(attribute_descriptions_qm);
    else
	return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object Qgsi_interface_configuration;  /* gsi-interface-configuration */

static Object Qgsi_interface;      /* gsi-interface */

static Object string_constant_38;  /* "The class ~A had more than one data-interface capability. ~
				    *              This situation would make data connection-selection ambiguous. ~
				    *              One has been chosen to be the sole data-interface direct-superior ~
				    *              class, ~A, and the class instances, if any, have had their ~A ~
				    *              attributes set to the default values."
				    */

static Object Qinstance_configuration;  /* instance-configuration */

/* PROCESS-PRE-4.0-CAPABILITIES-OF-CLASS */
Object process_pre_4_dot_0_capabilities_of_class(frame,class_name,
	    capabilities_of_class,called_from_change_the_text_qm)
    Object frame, class_name, capabilities_of_class;
    Object called_from_change_the_text_qm;
{
    Object symbol, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, temp_1, capability_flat_list;
    Object former_data_service_capabilities;
    Object former_data_interface_capabilities, present_data_interface_classes;
    Object former_configuration_capabilities;
    Object chosen_data_interface_capability_qm;
    Object more_than_one_interface_capability_qm;
    Object direct_superiors_of_defined_class_qm;
    Object data_service_and_interface_capabilities_qm;
    Object instance_configuration_capabilities_qm, superior, present_symbol;
    Object ab_loop_list__1, class_description, new_direct_superior_classes;
    Object configuration_list, new_value;
    char temp_2;

    x_note_fn_call(132,73);
    symbol = Nil;
    ab_loop_list_ = CAR(capabilities_of_class);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = frame_cons_1(symbol,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    symbol = Nil;
    ab_loop_list_ = CDR(capabilities_of_class);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = frame_cons_1(symbol,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    capability_flat_list = nconc2(temp,temp_1);
    former_data_service_capabilities = list_constant_7;
    former_data_interface_capabilities = list_constant_8;
    present_data_interface_classes = list_constant_9;
    former_configuration_capabilities = list_constant_10;
    chosen_data_interface_capability_qm = Nil;
    more_than_one_interface_capability_qm = Nil;
    direct_superiors_of_defined_class_qm = ISVREF(frame,(SI_Long)21L);
    data_service_and_interface_capabilities_qm = Nil;
    instance_configuration_capabilities_qm = Nil;
    if (called_from_change_the_text_qm) {
	if (direct_superiors_of_defined_class_qm &&  
		!TRUEP(CDR(direct_superiors_of_defined_class_qm)) && 
		memq_function(CAR(direct_superiors_of_defined_class_qm),
		list_constant_9))
	    direct_superiors_of_defined_class_qm = 
		    slot_value_cons_1(Qobject,Nil);
	else {
	    superior = Nil;
	    ab_loop_list_ = direct_superiors_of_defined_class_qm;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(superior,list_constant_11))) {
		ab_loopvar__2 = slot_value_cons_1(superior,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    direct_superiors_of_defined_class_qm = ab_loopvar_;
	    goto end_3;
	    direct_superiors_of_defined_class_qm = Qnil;
	  end_3:;
	}
    }
    symbol = Nil;
    ab_loop_list_ = capability_flat_list;
    present_symbol = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    present_symbol = EQ(symbol,Qgsi_interface_configuration) ? 
	    Qgsi_interface : symbol;
    if (memq_function(symbol,former_data_interface_capabilities)) {
	superior = Nil;
	ab_loop_list__1 = direct_superiors_of_defined_class_qm;
      next_loop_4:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_4;
	superior = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (memq_function(present_symbol,ISVREF(class_description,
		(SI_Long)2L))) {
	    temp_2 = TRUEP(Nil);
	    goto end_4;
	}
	goto next_loop_4;
      end_loop_4:
	temp_2 = TRUEP(T);
	goto end_4;
	temp_2 = TRUEP(Qnil);
      end_4:;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (chosen_data_interface_capability_qm)
	    more_than_one_interface_capability_qm = T;
	chosen_data_interface_capability_qm = present_symbol;
    }
    else if (memq_function(symbol,former_data_service_capabilities)) {
	if ( !TRUEP(memq_function(symbol,
		data_service_and_interface_capabilities_qm))) {
	    superior = Nil;
	    ab_loop_list__1 = direct_superiors_of_defined_class_qm;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    superior = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    class_description = 
		    lookup_global_or_kb_specific_property_value(superior,
		    Class_description_gkbprop);
	    if (memq_function(present_symbol,ISVREF(class_description,
		    (SI_Long)2L))) {
		temp_2 = TRUEP(Nil);
		goto end_5;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    temp_2 = TRUEP(T);
	    goto end_5;
	    temp_2 = TRUEP(Qnil);
	  end_5:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    data_service_and_interface_capabilities_qm = 
		    frame_cons_1(symbol,
		    data_service_and_interface_capabilities_qm);
    }
    else if (memq_function(symbol,former_configuration_capabilities)) {
	if ( !TRUEP(memq_function(symbol,
		instance_configuration_capabilities_qm)))
	    instance_configuration_capabilities_qm = 
		    nconc2(instance_configuration_capabilities_qm,
		    frame_cons_1(symbol,Nil));
    }
    else;
    goto next_loop_3;
  end_loop_3:;
    if (chosen_data_interface_capability_qm && 
	    data_service_and_interface_capabilities_qm)
	data_service_and_interface_capabilities_qm = 
		nconc2(data_service_and_interface_capabilities_qm,
		frame_cons_1(chosen_data_interface_capability_qm,Nil));
    else if (chosen_data_interface_capability_qm)
	data_service_and_interface_capabilities_qm = 
		frame_cons_1(chosen_data_interface_capability_qm,Nil);
    else;
    if (data_service_and_interface_capabilities_qm) {
	if ( !TRUEP(CDR(data_service_and_interface_capabilities_qm)) && 
		memq_function(CAR(data_service_and_interface_capabilities_qm),
		present_data_interface_classes) && 
		EQ(CAR(direct_superiors_of_defined_class_qm),Qobject)) {
	    if (called_from_change_the_text_qm) {
		reclaim_slot_value_list_1(direct_superiors_of_defined_class_qm);
		direct_superiors_of_defined_class_qm = Nil;
	    }
	    new_direct_superior_classes = 
		    copy_for_slot_value(data_service_and_interface_capabilities_qm);
	}
	else
	    new_direct_superior_classes = 
		    nconc2(copy_for_slot_value(data_service_and_interface_capabilities_qm),
		    direct_superiors_of_defined_class_qm);
	if (called_from_change_the_text_qm)
	    change_slot_value(3,frame,Qdirect_superiors_of_defined_class,
		    new_direct_superior_classes);
	else
	    initialize_slot_description_value(frame,
		    get_slot_description_of_class_description_function(Qdirect_superiors_of_defined_class,
		    ISVREF(frame,(SI_Long)1L),Nil),
		    new_direct_superior_classes);
	if (more_than_one_interface_capability_qm) {
	    notify_user(4,string_constant_38,class_name,
		    chosen_data_interface_capability_qm,
		    chosen_data_interface_capability_qm);
	    if ( !TRUEP(called_from_change_the_text_qm))
		Classes_needing_data_interface_initialization = 
			frame_cons_1(frame_list_2(class_name,
			chosen_data_interface_capability_qm),
			Classes_needing_data_interface_initialization);
	}
	reclaim_frame_list_1(data_service_and_interface_capabilities_qm);
    }
    if (instance_configuration_capabilities_qm) {
	configuration_list = Nil;
	symbol = Nil;
	ab_loop_list_ = instance_configuration_capabilities_qm;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = configuration_list;
	configuration_list = nconc2(temp_1,
		slot_value_cons_1(make_declaration_clause_for_item_configuration(2,
		symbol,T),Nil));
	goto next_loop_6;
      end_loop_6:
	if (called_from_change_the_text_qm)
	    change_slot_value(3,frame,Qinstance_configuration,
		    configuration_list);
	else {
	    new_value = nconc2(ISVREF(frame,(SI_Long)23L),configuration_list);
	    initialize_slot_description_value(frame,
		    get_slot_description_of_class_description_function(Qinstance_configuration,
		    ISVREF(frame,(SI_Long)1L),Nil),new_value);
	}
	reclaim_frame_list_1(instance_configuration_capabilities_qm);
    }
    return reclaim_frame_list_1(capability_flat_list);
}

static Object string_constant_39;  /* "~%; slot ~s::~s:~%" */

static Object string_constant_40;  /* "~%; slot ~s:~%" */

/* READ-PAST-FRAME-FOR-KB */
Object read_past_frame_for_kb(character_1,print_qm)
    Object character_1, print_qm;
{
    Object temp, read_kb_buffer_index_new_value, slot_denotation_or_left_edge;
    Object slot_name, class_qualifier_qm, first_time_qm;

    x_note_fn_call(132,74);
    if (print_qm)
	format((SI_Long)2L,T,"~%; starting reading of frame~%");
    if (New_saved_kb_format_p && CHAR_EQ(CHR('F'),character_1))
	read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    if ( !TRUEP(New_saved_kb_format_p)) {
	read_past_element_for_kb(print_qm);
	read_past_element_for_kb(print_qm);
    }
    character_1 = Nil;
    if (print_qm)
	format((SI_Long)2L,T,"~%;slots:~%");
  next_loop:
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    temp = CHAR_CODE(character_1);
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 33:
	    goto end_loop;
	    break;
	  case 91:
	    read_past_runtime_data_for_block(print_qm);
	    goto end_loop;
	    break;
	  default:
	    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    break;
	}
    slot_denotation_or_left_edge = read_element_for_kb(Nil);
    slot_name = Nil;
    class_qualifier_qm = Nil;
    if (FIXNUMP(slot_denotation_or_left_edge)) {
	if (print_qm) {
	    format((SI_Long)2L,T,"~%; (old format) edges and subblocks:~%");
	    format((SI_Long)3L,T," ~d ",slot_denotation_or_left_edge);
	}
	read_past_element_for_kb(print_qm);
	read_past_element_for_kb(print_qm);
	read_past_element_for_kb(print_qm);
	first_time_qm = T;
	character_1 = Nil;
      next_loop_1:
	character_1 = read_char_for_kb_past_spaces();
	if (CHAR_EQ(character_1,CHR('!')))
	    goto end_loop_1;
	if (New_saved_kb_format_p && first_time_qm) {
	    read_kb_buffer_index_new_value = FIXNUM_SUB1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    read_past_element_for_kb(print_qm);
	}
	first_time_qm = Nil;
	goto next_loop_1;
      end_loop_1:;
	goto end_loop;
    }
    else {
	slot_name = CONSP(slot_denotation_or_left_edge) ? 
		M_CAR(M_CDR(M_CDR(slot_denotation_or_left_edge))) : 
		slot_denotation_or_left_edge;
	class_qualifier_qm = CONSP(slot_denotation_or_left_edge) ? 
		M_CAR(M_CDR(slot_denotation_or_left_edge)) : Nil;
	reclaim_slot_value(slot_denotation_or_left_edge);
    }
    if (print_qm)
	formatn(4,T,class_qualifier_qm ? string_constant_39 : 
		string_constant_40,slot_name,class_qualifier_qm);
    read_past_element_for_kb(print_qm);
    goto next_loop;
  end_loop:;
    if (print_qm)
	format((SI_Long)2L,T,"~%; finished reading frame~%");
    return VALUES_1(Nil);
}

Object Substitute_format_name_prop = UNBOUND;

static Object Qformat_description;  /* format-description */

static Object Qsubstitute_format_name;  /* substitute-format-name */

static Object string_constant_41;  /* "Warning: An internal constraint has been violated.  A format ~
				    *                       with the unknown name ~A was discovered. Please report this ~
				    *                       problem to Gensym Customer Support."
				    */

static Object string_constant_42;  /* "This KB has formatting problems! You should load with ~
				    *             with \", BRINGING FORMATS UP-TO-DATE\", and then save. ~
				    *             If you are a customer, please report this to software ~
				    *             support. If you work for Gensym, this KB should not be ~
				    *             released to customers until it's had its formats brought ~
				    *             up-to-date."
				    */

/* FINISH-READING-FORMAT-FRAME-FOR-KB */
Object finish_reading_format_frame_for_kb(new_format_frame,format_name_qm)
    Object new_format_frame, format_name_qm;
{
    Object do_not_note_permanent_changes_p, other_format_frame_qm;
    Object substitute_format_name_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,75);
    do_not_note_permanent_changes_p = T;
    if ( !TRUEP(format_name_qm))
	other_format_frame_qm = 
		find_existing_equivalent_format_frame(new_format_frame);
    else {
	if ( 
		!TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name_qm),
		Qformat_description))) {
	    substitute_format_name_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name_qm),
		    Qsubstitute_format_name);
	    if ( !TRUEP(substitute_format_name_qm) ||  
		    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(substitute_format_name_qm),
		    Qformat_description))) {
		temp = substitute_format_name_qm;
		if (temp);
		else
		    temp = format_name_qm;
		notify_user(2,string_constant_41,temp);
	    }
	    else
		format_name_qm = substitute_format_name_qm;
	}
	if ((Reformat_as_appropriate_qm || 
		get_lookup_slot_value_given_default(new_format_frame,
		Qformat_change_qm,Nil)) && 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name_qm),
		Qformat_description)) {
	    other_format_frame_qm = 
		    get_instance_with_name_if_any(Qformat_frame,
		    format_name_qm);
	    if (other_format_frame_qm);
	    else
		other_format_frame_qm = make_format_frame(format_name_qm);
	}
	else
	    other_format_frame_qm = 
		    get_instance_with_name_if_any(Qformat_frame,
		    format_name_qm);
    }
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      if ( !TRUEP(other_format_frame_qm)) {
	  put_name_or_names_for_frame(new_format_frame,format_name_qm,T);
	  temp = Nil;
      }
      else if ( !TRUEP(format_name_qm) ||  
	      !TRUEP(find_differences_in_frames_if_any(3,new_format_frame,
	      other_format_frame_qm,T)))
	  temp = T;
      else if (Reformat_as_appropriate_qm || 
	      get_lookup_slot_value_given_default(new_format_frame,
	      Qformat_change_qm,Nil)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(other_format_frame_qm,Qformat_change_qm);
	  set_lookup_slot_value_1(other_format_frame_qm,Qformat_change_qm,
		  FIX((SI_Long)0L));
	  temp = T;
      }
      else if (Kb_load_case_qm || Main_kb_being_read_qm) {
	  change_slot_value(3,other_format_frame_qm,
		  Qname_or_names_for_frame,Nil);
	  change_slot_value(3,other_format_frame_qm,Qformat_change_qm,
		  format_name_qm);
	  put_name_or_names_for_frame(new_format_frame,format_name_qm,T);
	  temp = Nil;
      }
      else {
	  change_slot_value(3,new_format_frame,Qformat_change_qm,
		  format_name_qm);
	  temp = Nil;
      }
      if (temp) {
	  if (memq_function(new_format_frame,
		      Forward_referenced_format_frames)) {
	      change_slot_value(3,new_format_frame,
		      Qname_or_names_for_frame,Nil);
	      change_slot_value(3,new_format_frame,Qformat_change_qm,
		      format_name_qm);
	      notify_user(1,string_constant_42);
	  }
	  else
	      delete_block_after_reading_kb(new_format_frame);
	  result = VALUES_1(other_format_frame_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Connection_classes_warned_about_for_this_kb, Qconnection_classes_warned_about_for_this_kb);

static Object string_constant_43;  /* "WARNING: When this KB (~s) was last saved, ~A was a ~
				    *          defined subclass of CONNECTION, but the class definition ~
				    *          was not saved with that KB due in part to a software ~
				    *          problem.  Unfortunately, instances of this class cannot ~
				    *          be properly restored.  "
				    */

static Object string_constant_44;  /* "Therefore, instances of the class ~A within this KB will ~
				    *          be turned into instances of the class CONNECTION.  ~
				    *          If you can restore the original definition of ~A, you ~
				    *          may wish to abandon the current KB, and then merge this ~
				    *          KB into a KB that contains the restored definition."
				    */

static Object string_constant_45;  /* "~a~a" */

/* WARN-OF-UNDEFINED-CONNECTION-SUBCLASS-IF-APPROPRIATE */
Object warn_of_undefined_connection_subclass_if_appropriate(class_1)
    Object class_1;
{
    Object problem, solution;

    x_note_fn_call(132,76);
    if ( !TRUEP(memq_function(class_1,
	    Connection_classes_warned_about_for_this_kb))) {
	Connection_classes_warned_about_for_this_kb = 
		gensym_cons_1(class_1,
		Connection_classes_warned_about_for_this_kb);
	problem = tformat_text_string(3,string_constant_43,
		Namestring_for_kb_being_read,class_1);
	solution = tformat_text_string(3,string_constant_44,class_1,class_1);
	notify_user(3,string_constant_45,problem,solution);
	reclaim_text_string(problem);
	return reclaim_text_string(solution);
    }
    else
	return VALUES_1(Nil);
}

/* READ-CONNECTION-FOR-KB */
Object read_connection_for_kb()
{
    Object connection, frame_serial_number, frame_serial_number_setf_arg, old;
    Object new_1, temp, gensymed_symbol, connection_frame_or_class, temp_1;
    Object class_1, substitute_class_and_kb_flags_qm, connections_flags, x2;
    SI_Long svref_arg_2, gensymed_symbol_1;
    char temp_2;

    x_note_fn_call(132,77);
    connection = Nil;
    frame_serial_number = Nil;
    if (New_saved_kb_format_p) {
	frame_serial_number = read_element_for_kb(Nil);
	connection = get_frame_given_frame_serial_number(frame_serial_number);
	if ( !TRUEP(connection)) {
	    connection = make_connection_1();
	    frame_serial_number_setf_arg = 
		    increment_current_frame_serial_number();
	    old = ISVREF(connection,(SI_Long)10L);
	    new_1 = frame_serial_number_setf_arg;
	    temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		    !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(connection,FIX((SI_Long)10L)) = temp;
	    enter_frame_into_frame_serial_number_map(frame_serial_number,
		    connection);
	}
    }
    else {
	connection = make_connection_1();
	frame_serial_number_setf_arg = increment_current_frame_serial_number();
	old = ISVREF(connection,(SI_Long)10L);
	new_1 = frame_serial_number_setf_arg;
	temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(connection,FIX((SI_Long)10L)) = temp;
	gensymed_symbol = assign_index_in_index_space(Kb_object_index_space);
	if (FIXNUM_GE(gensymed_symbol,ISVREF(Kb_object_index_space,
		(SI_Long)4L)))
	    enlarge_index_space(Kb_object_index_space,gensymed_symbol);
	temp = ISVREF(ISVREF(Kb_object_index_space,(SI_Long)2L),
		IFIX(gensymed_symbol) >>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(gensymed_symbol) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = connection;
    }
    connection_frame_or_class = read_element_for_kb(Nil);
    if (SYMBOLP(connection_frame_or_class)) {
	if (Class_name_conflicts) {
	    temp_1 = assq_function(connection_frame_or_class,
		    Class_name_conflicts);
	    class_1 = SECOND(temp_1);
	}
	else
	    class_1 = Nil;
	if (class_1);
	else {
	    if (Loading_kb_p) {
		substitute_class_and_kb_flags_qm = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(connection_frame_or_class),
			Qsubstitute_class_and_kb_flags);
		if (substitute_class_and_kb_flags_qm && FIXNUM_LT(Kb_flags,
			M_CDR(substitute_class_and_kb_flags_qm))) {
		    temp_1 = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(connection_frame_or_class),
			    Qsubstitute_class_and_kb_flags);
		    temp_2 = TRUEP(CAR(temp_1));
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ?  
		    !TRUEP(lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		    Class_definition_gkbprop)) : TRUEP(Nil)) {
		if (Loading_kb_p) {
		    substitute_class_and_kb_flags_qm = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(connection_frame_or_class),
			    Qsubstitute_class_and_kb_flags);
		    if (substitute_class_and_kb_flags_qm && 
			    FIXNUM_LT(Kb_flags,
			    M_CDR(substitute_class_and_kb_flags_qm))) {
			temp_1 = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(connection_frame_or_class),
				Qsubstitute_class_and_kb_flags);
			class_1 = CAR(temp_1);
		    }
		    else
			class_1 = Nil;
		}
		else
		    class_1 = Nil;
	    }
	    else
		class_1 = Nil;
	}
	if (class_1);
	else
	    class_1 = connection_frame_or_class;
	if ( !TRUEP(lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop))) {
	    warn_of_undefined_connection_subclass_if_appropriate(class_1);
	    temp = Qconnection;
	}
	else
	    temp = class_1;
    }
    else {
	ISVREF(connection_frame_or_class,(SI_Long)21L) = connection;
	temp = connection_frame_or_class;
    }
    SVREF(connection,FIX((SI_Long)1L)) = temp;
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection);
    temp = read_element_for_kb(Nil);
    SVREF(connection,FIX((SI_Long)3L)) = temp;
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection);
    temp = read_element_for_kb(Nil);
    SVREF(connection,FIX((SI_Long)2L)) = temp;
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection);
    temp = read_element_for_kb(Nil);
    SVREF(connection,FIX((SI_Long)5L)) = temp;
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection);
    temp = read_element_for_kb(Nil);
    SVREF(connection,FIX((SI_Long)4L)) = temp;
    temp_2 = TRUEP(Noting_changes_to_kb_p);
    if (temp_2);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_2 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_2)
	note_change_to_connection_1(connection);
    temp = read_element_for_kb(Nil);
    SVREF(connection,FIX((SI_Long)6L)) = temp;
    connections_flags = read_element_for_kb(Nil);
    if ( !TRUEP(connections_flags))
	temp = FIX((SI_Long)0L);
    else if (EQ(connections_flags,T))
	temp = FIX((SI_Long)1L);
    else
	temp = FIXNUM_LOGAND(connections_flags,Savable_connection_flags);
    SVREF(connection,FIX((SI_Long)7L)) = temp;
    if (IFIX(Kb_flags) >= (SI_Long)101L) {
	temp = read_element_for_kb(Nil);
	SVREF(connection,FIX((SI_Long)9L)) = temp;
	connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    copy_unsaved_slots_from_connection_to_connection_frame(connection,
		    connection_frame_or_class);
    }
    if (EQ(Type_of_file_being_read,Qkb_save_with_runtime_data) && 
	    (SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
	    (SI_Long)64L)) {
	if ( !TRUEP(Warmbooting_qm))
	    delete_connection_after_reading_kb(connection);
    }
    return VALUES_1(connection);
}

/* READ-PAST-CONNECTION-FOR-KB */
Object read_past_connection_for_kb(print_qm)
    Object print_qm;
{
    x_note_fn_call(132,78);
    if (New_saved_kb_format_p)
	read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    if (IFIX(Kb_flags) >= (SI_Long)101L)
	read_past_element_for_kb(print_qm);
    return VALUES_1(Nil);
}

static Object string_constant_46;  /* "Cannot find frame reference of class ~a." */

static Object Qkb_error;           /* kb-error */

/* READ-FRAME-OR-CONNECTION-REFERENCE-FOR-KB */
Object read_frame_or_connection_reference_for_kb(character_1)
    Object character_1;
{
    Object frame_serial_number, frame_or_connection_qm, class_qm, temp;
    Object substitute_class_and_kb_flags_qm, text_string;
    Object error_message_as_text_string, error_message_as_gensym_string;
    Object sub_class_bit_vector, gensym_modify_macro_using_test_arg_1, car_1;
    Object cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_, temp_2;
    Object connection, frame_serial_number_setf_arg, old, new_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(132,79);
    frame_serial_number = read_element_for_kb(Nil);
    frame_or_connection_qm = 
	    get_frame_given_frame_serial_number(frame_serial_number);
    class_qm = CHAR_EQ(character_1,CHR('G')) ? read_element_for_kb(Nil) : Nil;
    temp = frame_or_connection_qm;
    if (temp);
    else {
	if (class_qm) {
	    if (Class_name_conflicts) {
		temp = assq_function(class_qm,Class_name_conflicts);
		temp_1 = TRUEP(SECOND(temp));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = assq_function(class_qm,Class_name_conflicts);
		class_qm = SECOND(temp);
	    }
	    else {
		if (Loading_kb_p) {
		    substitute_class_and_kb_flags_qm = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_qm),
			    Qsubstitute_class_and_kb_flags);
		    if (substitute_class_and_kb_flags_qm && 
			    FIXNUM_LT(Kb_flags,
			    M_CDR(substitute_class_and_kb_flags_qm))) {
			temp = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(class_qm),
				Qsubstitute_class_and_kb_flags);
			temp_1 = TRUEP(CAR(temp));
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ?  
			!TRUEP(lookup_global_or_kb_specific_property_value(class_qm,
			Class_definition_gkbprop)) : TRUEP(Nil)) {
		    if (Loading_kb_p) {
			substitute_class_and_kb_flags_qm = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(class_qm),
				Qsubstitute_class_and_kb_flags);
			if (substitute_class_and_kb_flags_qm && 
				FIXNUM_LT(Kb_flags,
				M_CDR(substitute_class_and_kb_flags_qm))) {
			    temp = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_qm),
				    Qsubstitute_class_and_kb_flags);
			    class_qm = CAR(temp);
			}
			else
			    class_qm = Nil;
		    }
		    else
			class_qm = Nil;
		}
	    }
	    if (EQ(class_qm,Qtable))
		class_qm = Qtable_item;
	    if ( 
		    !TRUEP(lookup_global_or_kb_specific_property_value(class_qm,
		    Class_description_gkbprop))) {
		text_string = tformat_text_string(2,string_constant_46,
			class_qm);
		error_message_as_text_string = export_text_string(2,
			text_string,Qkb_error);
		error_message_as_gensym_string = 
			wide_string_to_string(error_message_as_text_string);
		error((SI_Long)2L,"~a",error_message_as_gensym_string);
	    }
	    frame_or_connection_qm = 
		    make_frame_without_computed_initializations(lookup_global_or_kb_specific_property_value(class_qm,
		    Class_description_gkbprop),Nil,Nil);
	    sub_class_bit_vector = ISVREF(ISVREF(frame_or_connection_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Format_frame_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensym_modify_macro_using_test_arg_1 = frame_or_connection_qm;
		car_1 = gensym_modify_macro_using_test_arg_1;
		cdr_1 = Forward_referenced_format_frames;
		key_result = car_1;
		x_element = Nil;
		ab_loop_list_ = cdr_1;
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		x_element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
		if (ab_loop_it_) {
		    temp_1 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(Qnil);
	      end_1:;
		temp_2 = temp_1 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
		Forward_referenced_format_frames = temp_2;
	    }
	}
	else if (CHAR_EQ(character_1,CHR('H')));
	else {
	    connection = make_connection_1();
	    frame_serial_number_setf_arg = 
		    increment_current_frame_serial_number();
	    old = ISVREF(connection,(SI_Long)10L);
	    new_1 = frame_serial_number_setf_arg;
	    temp_2 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		    !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(connection,FIX((SI_Long)10L)) = temp_2;
	    frame_or_connection_qm = connection;
	}
	enter_frame_into_frame_serial_number_map(frame_serial_number,
		frame_or_connection_qm);
	temp = frame_or_connection_qm;
    }
    return VALUES_1(temp);
}

/* READ-PAST-FRAME-OR-CONNECTION-REFERENCE-FOR-KB */
Object read_past_frame_or_connection_reference_for_kb(character_1,print_qm)
    Object character_1, print_qm;
{
    x_note_fn_call(132,80);
    read_past_element_for_kb(print_qm);
    if (CHAR_EQ(character_1,CHR('G')))
	read_past_element_for_kb(print_qm);
    return VALUES_1(Nil);
}

static Object Knil;                /* :nil */

static Object Qpunctuation_mark_p;  /* punctuation-mark-p */

static Object Qpunctuation_mark;   /* punctuation-mark */

static Object Qframe_denotation;   /* frame-denotation */

/* READ-ELEMENT-FOR-KB */
Object read_element_for_kb(top_level_element_qm)
    Object top_level_element_qm;
{
    Object character_1, weight_qm, integer_qm, temp, temp_1, symbol;
    Object ordinary_symbol_qm, gensymed_symbol, incff_1_arg, decff_1_arg;
    Object char_1;
    SI_Long character_code, svref_arg_2;

    x_note_fn_call(132,81);
    character_1 = read_char_for_kb_past_spaces();
    character_code = IFIX(CHAR_CODE(character_1));
    if ((SI_Long)48L <= character_code && character_code <= (SI_Long)57L)
	weight_qm = FIX(character_code - (SI_Long)48L);
    else if ((SI_Long)97L <= character_code && character_code <= (SI_Long)119L)
	weight_qm = FIX(character_code - (SI_Long)97L + (SI_Long)10L);
    else
	weight_qm = Qnil;
    if (weight_qm)
	integer_qm = read_remainder_of_integer_for_kb(FIX((SI_Long)0L),
		weight_qm);
    else {
	temp = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp;
	integer_qm = Nil;
    }
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp;
	character_1 = temp_1;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    if (integer_qm) {
	temp_1 = CHAR_CODE(character_1);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    if ( !TRUEP(New_saved_kb_format_p) && (CHAR_EQ(character_1,
		    CHR('P')) || CHAR_EQ(character_1,CHR('M'))))
		temp_1 = finish_reading_slot_value_float(integer_qm,
			character_1, !EQ(integer_qm,FIX((SI_Long)0L)) ? T :
			 Nil);
	    else {
		if ( !CHAR_EQ(character_1,CHR(' '))) {
		    temp = FIXNUM_SUB1(Read_kb_buffer_index);
		    Read_kb_buffer_index = temp;
		}
		if (FIXNUM_GE(integer_qm,ISVREF(Kb_object_index_space,
			(SI_Long)4L)))
		    enlarge_index_space(Kb_object_index_space,integer_qm);
		temp_1 = ISVREF(ISVREF(ISVREF(Kb_object_index_space,
			(SI_Long)2L),IFIX(integer_qm) >>  -  - 
			(SI_Long)10L),IFIX(integer_qm) & (SI_Long)1023L);
	    }
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 83:
	      case 39:
	      case 96:
	      case 58:
	      case 44:
		if (CHAR_EQ(character_1,CHR('S')))
		    temp_1 = 
			    read_character_sequence_as_text_string(integer_qm,
			    New_saved_kb_format_p ? Base_reference : Qnil);
		else {
		    temp_1 = New_saved_kb_format_p ? Base_reference : Qnil;
		    symbol = read_character_sequence_as_symbol(integer_qm,
			    temp_1,CHAR_EQ(character_1,CHR(':')) || 
			    CHAR_EQ(character_1,CHR(',')) ? 
			    Keyword_package_1 : Nil);
		    if (CHAR_EQ(character_1,CHR(':')) || 
			    CHAR_EQ(character_1,CHR(','))) {
			if (EQ(symbol,Qnil))
			    symbol = Knil;
			ordinary_symbol_qm = 
				find_symbol(SYMBOL_NAME(symbol),_);
			if (ordinary_symbol_qm && 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(ordinary_symbol_qm),
				Qpunctuation_mark_p))
			    mutate_global_property(symbol,
				    Qpunctuation_mark,
				    Qtype_of_syntactic_anomaly);
		    }
		    if (CHAR_EQ(character_1,CHR('\'')) || 
			    CHAR_EQ(character_1,CHR(':'))) {
			gensymed_symbol = 
				assign_index_in_index_space(Kb_object_index_space);
			if (FIXNUM_GE(gensymed_symbol,
				ISVREF(Kb_object_index_space,(SI_Long)4L)))
			    enlarge_index_space(Kb_object_index_space,
				    gensymed_symbol);
			temp = ISVREF(ISVREF(Kb_object_index_space,
				(SI_Long)2L),IFIX(gensymed_symbol) >>  -  
				- (SI_Long)10L);
			svref_arg_2 = IFIX(gensymed_symbol) & (SI_Long)1023L;
			ISVREF(temp,svref_arg_2) = symbol;
		    }
		    temp_1 = symbol;
		}
		break;
	      case 43:
	      case 45:
		temp_1 = integer_qm;
		break;
	      case 40:
		incff_1_arg = integer_qm;
		temp = FIXNUM_ADD(Previous_timestamp_qm,incff_1_arg);
		Previous_timestamp_qm = temp;
		temp_1 = Previous_timestamp_qm;
		break;
	      case 41:
		decff_1_arg = integer_qm;
		temp = FIXNUM_MINUS(Previous_timestamp_qm,decff_1_arg);
		Previous_timestamp_qm = temp;
		temp_1 = Previous_timestamp_qm;
		break;
	      case 87:
		temp_1 = finish_reading_managed_array_for_kb(integer_qm);
		break;
	      case 79:
		temp_1 = finish_reading_managed_float_array_for_kb(integer_qm);
		break;
	      default:
		if ( !TRUEP(New_saved_kb_format_p) && (CHAR_EQ(character_1,
			CHR('P')) || CHAR_EQ(character_1,CHR('M'))))
		    temp_1 = finish_reading_slot_value_float(integer_qm,
			    character_1, !EQ(integer_qm,FIX((SI_Long)0L)) ?
			     T : Nil);
		else {
		    if ( !CHAR_EQ(character_1,CHR(' '))) {
			temp = FIXNUM_SUB1(Read_kb_buffer_index);
			Read_kb_buffer_index = temp;
		    }
		    if (FIXNUM_GE(integer_qm,ISVREF(Kb_object_index_space,
			    (SI_Long)4L)))
			enlarge_index_space(Kb_object_index_space,integer_qm);
		    temp_1 = ISVREF(ISVREF(ISVREF(Kb_object_index_space,
			    (SI_Long)2L),IFIX(integer_qm) >>  -  - 
			    (SI_Long)10L),IFIX(integer_qm) & (SI_Long)1023L);
		}
		break;
	    }
    }
    else {
	temp_1 = CHAR_CODE(character_1);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L))))
	    temp_1 = abort_on_bad_kb(1,character_1);
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 78:
		temp_1 = Nil;
		break;
	      case 84:
		temp_1 = T;
		break;
	      case 90:
		temp_1 = FIX((SI_Long)0L);
		break;
	      case 88:
		temp_1 = No_value;
		break;
	      case 35:
		temp_1 = Simulation_no_value;
		break;
	      case 123:
		temp_1 = Most_negative_fixnum;
		break;
	      case 76:
		temp_1 = read_list_element_for_kb();
		break;
	      case 71:
	      case 72:
	      case 73:
		temp_1 = 
			read_frame_or_connection_reference_for_kb(character_1);
		break;
	      case 70:
	      case 89:
		temp_1 = read_frame_for_kb(character_1,top_level_element_qm);
		break;
	      case 67:
		temp_1 = read_connection_for_kb();
		break;
	      case 80:
	      case 77:
		temp_1 = read_slot_value_float_for_kb_from_binary(character_1);
		break;
	      case 66:
		temp_1 = read_byte_code_body_for_kb();
		break;
	      case 75:
		temp_1 = read_element_for_kb(Nil);
		break;
	      case 74:
		New_saved_kb_format_p = T;
		temp_1 = read_element_for_kb(Nil);
		break;
	      case 69:
		temp_1 = Nil;
		break;
	      case 36:
		symbol = read_element_for_kb(Nil);
		mutate_global_property(symbol,Qnumeric,
			Qtype_of_syntactic_anomaly);
		temp_1 = symbol;
		break;
	      case 38:
		Previous_timestamp_qm = read_previous_timestamp_for_kb();
		temp_1 = Previous_timestamp_qm;
		break;
	      case 65:
		temp_1 = read_readable_element_for_kb();
		break;
	      case 42:
		if ( !TRUEP(Read_kb_buffer_index))
		    char_1 = Nil;
		else if (FIXNUM_LT(Read_kb_buffer_index,
			    Read_kb_buffer_length)) {
		    temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		    temp = FIXNUM_ADD1(Read_kb_buffer_index);
		    Read_kb_buffer_index = temp;
		    char_1 = temp_1;
		}
		else
		    char_1 = read_next_char_for_kb_from_refilled_buffer();
		if (CHAR_EQ(char_1,CHR('2')) || CHAR_EQ(char_1,CHR('4')))
		    temp_1 = Nil;
		else
		    temp_1 = Qt;
		break;
	      case 37:
		temp_1 = read_aggregate_evaluation_value_for_kb();
		break;
	      case 85:
		temp_1 = read_truth_value_for_kb();
		break;
	      case 63:
		temp_1 = read_long_for_kb();
		break;
	      case 94:
		temp_1 = read_legacy_long_for_kb();
		break;
	      case 126:
		temp_1 = slot_value_list_2(Qframe_denotation,
			read_element_for_kb(Nil));
		break;
	      case 124:
		temp_1 = read_user_mode_alias_for_kb();
		break;
	      default:
		temp_1 = abort_on_bad_kb(1,character_1);
		break;
	    }
    }
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Create_frames_and_connections_reading_past_qm, Qcreate_frames_and_connections_reading_past_qm);

/* READ-PAST-ELEMENT-FOR-KB */
Object read_past_element_for_kb(print_qm)
    Object print_qm;
{
    Object character_1, weight_qm, integer_qm, temp, temp_1, string_or_symbol;
    Object symbol, ordinary_symbol_qm, gensymed_symbol;
    SI_Long character_code, svref_arg_2, ab_loop_repeat_;

    x_note_fn_call(132,82);
    character_1 = read_char_for_kb_past_spaces();
    character_code = IFIX(CHAR_CODE(character_1));
    if ((SI_Long)48L <= character_code && character_code <= (SI_Long)57L)
	weight_qm = FIX(character_code - (SI_Long)48L);
    else if ((SI_Long)97L <= character_code && character_code <= (SI_Long)119L)
	weight_qm = FIX(character_code - (SI_Long)97L + (SI_Long)10L);
    else
	weight_qm = Qnil;
    if (weight_qm)
	integer_qm = read_remainder_of_integer_for_kb(FIX((SI_Long)0L),
		weight_qm);
    else {
	temp = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp;
	integer_qm = Nil;
    }
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp;
	character_1 = temp_1;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    if (integer_qm) {
	temp_1 = CHAR_CODE(character_1);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L)))) {
	    if ( !TRUEP(New_saved_kb_format_p) && (EQ(character_1,
		    CHR('P')) || EQ(character_1,CHR('M'))) && T) {
		if (print_qm)
		    format((SI_Long)4L,T,"~% ~d ~c ",integer_qm,character_1);
		read_past_element_for_kb(print_qm);
	    }
	    else {
		if ( !CHAR_EQ(character_1,CHR(' '))) {
		    temp = FIXNUM_SUB1(Read_kb_buffer_index);
		    Read_kb_buffer_index = temp;
		}
		if (print_qm) {
		    if (FIXNUM_GE(integer_qm,ISVREF(Kb_object_index_space,
			    (SI_Long)4L)))
			enlarge_index_space(Kb_object_index_space,integer_qm);
		    format((SI_Long)4L,T,"~% ~d ; ~s~%",integer_qm,
			    ISVREF(ISVREF(ISVREF(Kb_object_index_space,
			    (SI_Long)2L),IFIX(integer_qm) >>  -  - 
			    (SI_Long)10L),IFIX(integer_qm) & (SI_Long)1023L));
		}
	    }
	}
	else
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 83:
	      case 39:
	      case 96:
	      case 58:
	      case 44:
		if (CHAR_EQ(character_1,CHR('S')))
		    string_or_symbol = 
			    read_character_sequence_as_text_string(integer_qm,
			    New_saved_kb_format_p ? Base_reference : Qnil);
		else {
		    temp_1 = New_saved_kb_format_p ? Base_reference : Qnil;
		    symbol = read_character_sequence_as_symbol(integer_qm,
			    temp_1,CHAR_EQ(character_1,CHR(':')) || 
			    CHAR_EQ(character_1,CHR(',')) ? 
			    Keyword_package_1 : Nil);
		    if (CHAR_EQ(character_1,CHR(':')) || 
			    CHAR_EQ(character_1,CHR(','))) {
			if (EQ(symbol,Qnil))
			    symbol = Knil;
			ordinary_symbol_qm = 
				find_symbol(SYMBOL_NAME(symbol),_);
			if (ordinary_symbol_qm && 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(ordinary_symbol_qm),
				Qpunctuation_mark_p))
			    mutate_global_property(symbol,
				    Qpunctuation_mark,
				    Qtype_of_syntactic_anomaly);
		    }
		    if (CHAR_EQ(character_1,CHR('\'')) || 
			    CHAR_EQ(character_1,CHR(':'))) {
			gensymed_symbol = 
				assign_index_in_index_space(Kb_object_index_space);
			if (FIXNUM_GE(gensymed_symbol,
				ISVREF(Kb_object_index_space,(SI_Long)4L)))
			    enlarge_index_space(Kb_object_index_space,
				    gensymed_symbol);
			temp = ISVREF(ISVREF(Kb_object_index_space,
				(SI_Long)2L),IFIX(gensymed_symbol) >>  -  
				- (SI_Long)10L);
			svref_arg_2 = IFIX(gensymed_symbol) & (SI_Long)1023L;
			ISVREF(temp,svref_arg_2) = symbol;
		    }
		    string_or_symbol = symbol;
		}
		if (print_qm) {
		    format((SI_Long)3L,T,"~% ~s ",string_or_symbol);
		    if ( !CHARACTERP(character_1))
			format((SI_Long)2L,T,
				"; not interned in index space~%");
		    else
			switch (ICHAR_CODE(character_1)) {
			  case 'S':
			    format((SI_Long)2L,T,"; string~%");
			    break;
			  case '\'':
			  case ':':
			    format((SI_Long)3L,T,"; index = ~d~%",
				    ISVREF(Kb_object_index_space,(SI_Long)3L));
			    break;
			  default:
			    format((SI_Long)2L,T,
				    "; not interned in index space~%");
			    break;
			}
		}
		if ( !SYMBOLP(string_or_symbol))
		    reclaim_text_string(string_or_symbol);
		break;
	      case 43:
	      case 45:
	      case 41:
	      case 40:
		if (print_qm) {
		    if ( !(CHAR_EQ(character_1,CHR('+')) || 
			    CHAR_EQ(character_1,CHR('-'))))
			format((SI_Long)3L,T,"~c",character_1);
		    format((SI_Long)3L,T," ~d ",integer_qm);
		}
		break;
	      case 87:
	      case 79:
		if (print_qm)
		    format((SI_Long)3L,T,"~% ~c ",character_1);
		ab_loop_repeat_ = IFIX(integer_qm);
	      next_loop:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		read_past_element_for_kb(print_qm);
		goto next_loop;
	      end_loop:;
		if (print_qm)
		    format((SI_Long)3L,T,"; end ~c~%",character_1);
		break;
	      default:
		if ( !TRUEP(New_saved_kb_format_p) && (EQ(character_1,
			CHR('P')) || EQ(character_1,CHR('M'))) && T) {
		    if (print_qm)
			format((SI_Long)4L,T,"~% ~d ~c ",integer_qm,
				character_1);
		    read_past_element_for_kb(print_qm);
		}
		else {
		    if ( !CHAR_EQ(character_1,CHR(' '))) {
			temp = FIXNUM_SUB1(Read_kb_buffer_index);
			Read_kb_buffer_index = temp;
		    }
		    if (print_qm) {
			if (FIXNUM_GE(integer_qm,
				ISVREF(Kb_object_index_space,(SI_Long)4L)))
			    enlarge_index_space(Kb_object_index_space,
				    integer_qm);
			format((SI_Long)4L,T,"~% ~d ; ~s~%",integer_qm,
				ISVREF(ISVREF(ISVREF(Kb_object_index_space,
				(SI_Long)2L),IFIX(integer_qm) >>  -  - 
				(SI_Long)10L),IFIX(integer_qm) & 
				(SI_Long)1023L));
		    }
		}
		break;
	    }
    }
    else {
	if (print_qm)
	    format((SI_Long)3L,T,"~% ~c",character_1);
	temp_1 = CHAR_CODE(character_1);
	if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && FIXNUM_LE(temp_1,
		FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(temp_1)) {
	      case 78:
	      case 84:
	      case 90:
	      case 88:
	      case 69:
	      case 35:
		break;
	      case 36:
	      case 75:
	      case 74:
		read_past_element_for_kb(print_qm);
		break;
	      case 76:
		if (print_qm)
		    format((SI_Long)2L,T,"; start of List element~%");
		read_past_list_element_for_kb(print_qm);
		if (print_qm)
		    format((SI_Long)2L,T,"; end of List element~%");
		break;
	      case 70:
	      case 89:
		if ( !TRUEP(print_qm) && 
			Create_frames_and_connections_reading_past_qm)
		    read_frame_for_kb(character_1,Nil);
		else
		    read_past_frame_for_kb(character_1,print_qm);
		break;
	      case 71:
	      case 72:
	      case 73:
		if ( !TRUEP(print_qm) && 
			Create_frames_and_connections_reading_past_qm)
		    read_frame_or_connection_reference_for_kb(character_1);
		else
		    read_past_frame_or_connection_reference_for_kb(character_1,
			    print_qm);
		break;
	      case 67:
		if ( !TRUEP(print_qm) && 
			Create_frames_and_connections_reading_past_qm)
		    read_connection_for_kb();
		else
		    read_past_connection_for_kb(print_qm);
		break;
	      case 80:
	      case 77:
		read_past_slot_value_float_for_kb_from_binary(character_1,
			print_qm);
		break;
	      case 66:
		read_past_byte_code_body_for_kb(print_qm);
		break;
	      case 38:
		read_past_previous_timestamp_for_kb(print_qm);
		break;
	      case 65:
		read_past_readable_element_for_kb(print_qm);
		break;
	      case 37:
		read_past_aggregate_evaluation_value_for_kb(print_qm);
		break;
	      case 42:
		if (print_qm) {
		    if ( !TRUEP(Read_kb_buffer_index))
			temp_1 = Nil;
		    else if (FIXNUM_LT(Read_kb_buffer_index,
			    Read_kb_buffer_length)) {
			temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
			temp = FIXNUM_ADD1(Read_kb_buffer_index);
			Read_kb_buffer_index = temp;
		    }
		    else
			temp_1 = read_next_char_for_kb_from_refilled_buffer();
		    format((SI_Long)4L,T,"~%~c~c~%",CHR('*'),temp_1);
		}
		break;
	      default:
		break;
	    }
    }
    return VALUES_1(Nil);
}

static Object Qab_structure;       /* structure */

/* READ-AGGREGATE-EVALUATION-VALUE-FOR-KB */
Object read_aggregate_evaluation_value_for_kb()
{
    Object aggregate_type, managed_array, next_character, temp, temp_1;
    Object element, svref_new_value, cons_holding_frame_qm;
    Object frame_serial_number_setf_arg, old, new_1;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, temp_3, x2;
    Object aggregate_evaluation_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_1, index_1;
    SI_Long ab_loop_bind_, svref_arg_2;
    char temp_2;

    x_note_fn_call(132,83);
    aggregate_type = read_element_for_kb(Nil);
    read_element_for_kb(Nil);
    gensymed_symbol = IFIX(read_element_for_kb(Nil));
    gensymed_symbol_1 = IFIX(Kb_flags) < (SI_Long)266L ? (SI_Long)1L : 
	    (SI_Long)0L;
    length_1 = gensymed_symbol - gensymed_symbol_1;
    managed_array = allocate_managed_array(1,FIX(length_1));
    if (EQ(aggregate_type,Qsequence))
	index_1 = (SI_Long)1L;
    else if (EQ(aggregate_type,Qab_structure))
	index_1 = (SI_Long)1L;
    else
	index_1 = IFIX(Qnil);
    ab_loop_bind_ = length_1;
    next_character = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_1;
	next_character = temp;
    }
    else
	next_character = read_next_char_for_kb_from_refilled_buffer();
    if (CHAR_EQ(next_character,CHR('~'))) {
	element = read_element_for_kb(Nil);
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    temp_1 = slot_value_list_2(Qframe_denotation,element);
	    ISVREF(managed_array,svref_arg_2) = temp_1;
	}
	else {
	    temp_1 = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    svref_new_value = slot_value_list_2(Qframe_denotation,element);
	    ISVREF(temp_1,svref_arg_2) = svref_new_value;
	}
	temp = member(4,Frame_being_read_qm,
		Frames_for_rendezvous_in_aggregate_values_qm,Ktest,Qcar_eq);
	cons_holding_frame_qm = CAR(temp);
	if (cons_holding_frame_qm) {
	    frame_serial_number_setf_arg = Current_frame_serial_number;
	    old = SECOND(cons_holding_frame_qm);
	    new_1 = frame_serial_number_setf_arg;
	    temp_1 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		    !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    M_SECOND(cons_holding_frame_qm) = temp_1;
	    gensym_modify_macro_using_test_arg_1 = 
		    Slot_description_for_slot_value_being_read_qm;
	    car_1 = gensym_modify_macro_using_test_arg_1;
	    cdr_1 = THIRD(cons_holding_frame_qm);
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list_ = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    x_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	    temp_1 = temp_2 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	    M_THIRD(cons_holding_frame_qm) = temp_1;
	}
	else {
	    temp_3 = Frame_being_read_qm;
	    temp = copy_frame_serial_number(Current_frame_serial_number);
	    Frames_for_rendezvous_in_aggregate_values_qm = 
		    gensym_cons_1(gensym_list_3(temp_3,temp,
		    gensym_cons_1(Slot_description_for_slot_value_being_read_qm,
		    Nil)),Frames_for_rendezvous_in_aggregate_values_qm);
	}
    }
    else {
	temp_1 = FIXNUM_SUB1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_1;
	element = read_element_for_kb(Nil);
	if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if ((temp_2 ? (SI_Long)0L != (IFIX(ISVREF(element,(SI_Long)5L)) & 
		(SI_Long)262144L) : TRUEP(Nil)) ?  !TRUEP(Warmbooting_qm) :
		 TRUEP(Nil)) {
	    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		ISVREF(managed_array,svref_arg_2) = Nil;
	    }
	    else {
		temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = Nil;
	    }
	}
	else {
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(element,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = member(4,Frame_being_read_qm,
			Frames_for_rendezvous_in_aggregate_values_qm,Ktest,
			Qcar_eq);
		cons_holding_frame_qm = CAR(temp);
		if (cons_holding_frame_qm) {
		    frame_serial_number_setf_arg = Current_frame_serial_number;
		    old = SECOND(cons_holding_frame_qm);
		    new_1 = frame_serial_number_setf_arg;
		    temp_1 = (FIXNUMP(old) ||  !TRUEP(old)) && 
			    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
			    frame_serial_number_setf_helper_1(old,new_1);
		    M_SECOND(cons_holding_frame_qm) = temp_1;
		    gensym_modify_macro_using_test_arg_1 = 
			    Slot_description_for_slot_value_being_read_qm;
		    car_1 = gensym_modify_macro_using_test_arg_1;
		    cdr_1 = THIRD(cons_holding_frame_qm);
		    key_result = car_1;
		    x_element = Nil;
		    ab_loop_list_ = cdr_1;
		    ab_loop_it_ = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    x_element = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
		    if (ab_loop_it_) {
			temp_2 = TRUEP(ab_loop_it_);
			goto end_2;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp_2 = TRUEP(Qnil);
		  end_2:;
		    temp_1 = temp_2 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
		    M_THIRD(cons_holding_frame_qm) = temp_1;
		}
		else {
		    temp_3 = Frame_being_read_qm;
		    temp = 
			    copy_frame_serial_number(Current_frame_serial_number);
		    Frames_for_rendezvous_in_aggregate_values_qm = 
			    gensym_cons_1(gensym_list_3(temp_3,temp,
			    gensym_cons_1(Slot_description_for_slot_value_being_read_qm,
			    Nil)),
			    Frames_for_rendezvous_in_aggregate_values_qm);
		}
	    }
	    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		ISVREF(managed_array,svref_arg_2) = element;
	    }
	    else {
		temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = element;
	    }
	}
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    aggregate_evaluation_value = eval_cons_1(managed_array,aggregate_type);
    temp_1 = M_CAR(aggregate_evaluation_value);
    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),Maximum_in_place_array_size))
	ISVREF(temp_1,(SI_Long)2L) = FIX((SI_Long)1L);
    else {
	temp_1 = ISVREF(temp_1,(SI_Long)2L);
	ISVREF(temp_1,(SI_Long)0L) = FIX((SI_Long)1L);
    }
    temp = aggregate_evaluation_value;
    goto end_3;
    temp = Qnil;
  end_3:;
    return VALUES_1(temp);
}

/* READ-PAST-AGGREGATE-EVALUATION-VALUE-FOR-KB */
Object read_past_aggregate_evaluation_value_for_kb(print_qm)
    Object print_qm;
{
    Object len;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(132,84);
    read_past_element_for_kb(print_qm);
    read_past_element_for_kb(print_qm);
    len = read_element_for_kb(Nil);
    i = (SI_Long)2L;
    ab_loop_bind_ = IFIX(len);
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    read_element_for_kb(Nil);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qfloat_array;        /* float-array */

/* READ-SLOT-VALUE-FLOAT-FOR-KB-FROM-BINARY */
Object read_slot_value_float_for_kb_from_binary(character_1)
    Object character_1;
{
    Object temp, temp_1, amf_available_array_cons_qm, amf_array, temp_2;
    Object amf_result, new_float;
    SI_Long x1, x2, x3, x4, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, b0, b1, b2, b3;
    char gensymed_symbol_3;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(132,85);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (CHAR_EQ(character_1,CHR('P'))) {
	    x1 = (SI_Long)0L;
	    x2 = (SI_Long)0L;
	    x3 = (SI_Long)0L;
	    x4 = (SI_Long)0L;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = (SI_Long)0L;
	    gensymed_symbol_3 = 'a';
	    gensymed_symbol_3 = 
		    CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	    gensymed_symbol = 
		    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) 
		    - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol = (SI_Long)94L * gensymed_symbol + 
		    gensymed_symbol_1;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    x1 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  
		    -  - (SI_Long)16L);
	    x2 = gensymed_symbol_1 & (SI_Long)65535L;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = (SI_Long)0L;
	    gensymed_symbol_3 = 'a';
	    gensymed_symbol_3 = 
		    CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	    gensymed_symbol = 
		    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) 
		    - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol = (SI_Long)94L * gensymed_symbol + 
		    gensymed_symbol_1;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
	    }
	    else
		temp = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    x3 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  
		    -  - (SI_Long)16L);
	    x4 = gensymed_symbol_1 & (SI_Long)65535L;
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    b0 = x1;
	    b1 = x2;
	    b2 = x3;
	    b3 = x4;
	    aref_new_value = g2ext_foreign_reconstruct_float(b0,b1,b2,b3);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = (double)IFIX(read_element_for_kb(Nil));
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* READ-PAST-SLOT-VALUE-FLOAT-FOR-KB-FROM-BINARY */
Object read_past_slot_value_float_for_kb_from_binary(character_1,print_qm)
    Object character_1, print_qm;
{
    x_note_fn_call(132,86);
    if (CHAR_EQ(character_1,CHR('P'))) {
	read_past_binary_word_for_kb(print_qm);
	read_past_binary_word_for_kb(print_qm);
    }
    else
	read_past_element_for_kb(print_qm);
    return VALUES_1(Nil);
}

/* FINISH-READING-MANAGED-FLOAT-ARRAY-FOR-KB */
Object finish_reading_managed_float_array_for_kb(length_init)
    Object length_init;
{
    SI_Long length_1;

    x_note_fn_call(132,87);
    length_1 = IFIX(length_init);
    return finish_reading_into_managed_float_array_for_kb(allocate_managed_float_array(1,
	    FIX(length_1)),FIX(length_1));
}

/* FINISH-READING-INTO-MANAGED-FLOAT-ARRAY-FOR-KB */
Object finish_reading_into_managed_float_array_for_kb(managed_float_array,
	    length_init)
    Object managed_float_array, length_init;
{
    Object char_1, aref_arg_1, temp_1, read_kb_buffer_index_new_value;
    SI_Long length_1, i, temp, ab_loop_repeat_, aref_arg_2, x1, x2, x3, x4;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, b0, b1, b2;
    SI_Long b3;
    char gensymed_symbol_3;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(132,88);
    length_1 = IFIX(length_init);
    i = (SI_Long)0L;
  next_loop:
    if (i == length_1)
	goto end_loop;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = length_1 - i;
	ab_loop_repeat_ = MIN((SI_Long)500L,temp);
	char_1 = Nil;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	char_1 = read_char_for_kb_past_spaces();
	aref_arg_1 = ISVREF(managed_float_array,(i >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	if (CHAR_EQ(char_1,CHR('P'))) {
	    x1 = (SI_Long)0L;
	    x2 = (SI_Long)0L;
	    x3 = (SI_Long)0L;
	    x4 = (SI_Long)0L;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = (SI_Long)0L;
	    gensymed_symbol_3 = 'a';
	    gensymed_symbol_3 = 
		    CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	    gensymed_symbol = 
		    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) 
		    - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol = (SI_Long)94L * gensymed_symbol + 
		    gensymed_symbol_1;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    x1 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  
		    -  - (SI_Long)16L);
	    x2 = gensymed_symbol_1 & (SI_Long)65535L;
	    gensymed_symbol = (SI_Long)0L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    gensymed_symbol_2 = (SI_Long)0L;
	    gensymed_symbol_3 = 'a';
	    gensymed_symbol_3 = 
		    CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	    gensymed_symbol = 
		    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) 
		    - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol = (SI_Long)94L * gensymed_symbol + 
		    gensymed_symbol_1;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
	    }
	    else
		temp_1 = read_next_char_for_kb_from_refilled_buffer();
	    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
	    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		    gensymed_symbol_2;
	    x3 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  
		    -  - (SI_Long)16L);
	    x4 = gensymed_symbol_1 & (SI_Long)65535L;
	    b0 = x1;
	    b1 = x2;
	    b2 = x3;
	    b3 = x4;
	    aref_new_value = g2ext_foreign_reconstruct_float(b0,b1,b2,b3);
	}
	else {
	    temp_1 = lfloat(read_element_for_kb(Nil),float_constant);
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	}
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    goto next_loop;
  end_loop:
    return VALUES_1(managed_float_array);
    return VALUES_1(Qnil);
}

/* FINISH-READING-MANAGED-ARRAY-FOR-KB */
Object finish_reading_managed_array_for_kb(length_init)
    Object length_init;
{
    SI_Long length_1;

    x_note_fn_call(132,89);
    length_1 = IFIX(length_init);
    return finish_reading_into_managed_array_for_kb(allocate_managed_array(1,
	    FIX(length_1)),FIX(length_1));
}

/* FINISH-READING-INTO-MANAGED-ARRAY-FOR-KB */
Object finish_reading_into_managed_array_for_kb(managed_array,length_init)
    Object managed_array, length_init;
{
    Object temp, svref_new_value;
    SI_Long length_1, i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(132,90);
    length_1 = IFIX(length_init);
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	temp = read_element_for_kb(Nil);
	ISVREF(managed_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = read_element_for_kb(Nil);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(managed_array);
    return VALUES_1(Qnil);
}

/* READ-PREVIOUS-TIMESTAMP-FOR-KB */
Object read_previous_timestamp_for_kb()
{
    Object temp, read_kb_buffer_index_new_value;
    SI_Long x1, x2, x3, x4, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, b0, b1, b2, b3;
    char gensymed_symbol_3;
    char temp_1;
    double gensymed_symbol_4, gensymed_symbol_5, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(132,91);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	x1 = (SI_Long)0L;
	x2 = (SI_Long)0L;
	x3 = (SI_Long)0L;
	x4 = (SI_Long)0L;
	gensymed_symbol = (SI_Long)0L;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = (SI_Long)0L;
	gensymed_symbol_3 = 'a';
	gensymed_symbol_3 = CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	gensymed_symbol = 
		IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) - 
		(SI_Long)33L;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol = (SI_Long)94L * gensymed_symbol + gensymed_symbol_1;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		gensymed_symbol_2;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		gensymed_symbol_2;
	x1 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  -  
		- (SI_Long)16L);
	x2 = gensymed_symbol_1 & (SI_Long)65535L;
	gensymed_symbol = (SI_Long)0L;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = (SI_Long)0L;
	gensymed_symbol_3 = 'a';
	gensymed_symbol_3 = CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
	gensymed_symbol = 
		IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) - 
		(SI_Long)33L;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol = (SI_Long)94L * gensymed_symbol + gensymed_symbol_1;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_1 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		gensymed_symbol_2;
	if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	    temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	    read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	    Read_kb_buffer_index = read_kb_buffer_index_new_value;
	}
	else
	    temp = read_next_char_for_kb_from_refilled_buffer();
	gensymed_symbol_2 = IFIX(CHAR_CODE(temp)) - (SI_Long)33L;
	gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + 
		gensymed_symbol_2;
	x3 = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  -  
		- (SI_Long)16L);
	x4 = gensymed_symbol_1 & (SI_Long)65535L;
	b0 = x1;
	b1 = x2;
	b2 = x3;
	b3 = x4;
	gensymed_symbol_4 = g2ext_foreign_reconstruct_float(b0,b1,b2,b3);
	gensymed_symbol_5 = DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
	gensymed_symbol_5 = (double)IFIX(Gensym_time_at_start);
	gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
	arg = gensymed_symbol_4;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_1);
	else {
	    arg = gensymed_symbol_4;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	    temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	temp = temp_1 ? Most_negative_fixnum : 
		LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_4));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* READ-PAST-PREVIOUS-TIMESTAMP-FOR-KB */
Object read_past_previous_timestamp_for_kb(print_qm)
    Object print_qm;
{
    x_note_fn_call(132,92);
    read_past_binary_word_for_kb(print_qm);
    read_past_binary_word_for_kb(print_qm);
    return VALUES_1(Nil);
}

static Object Qgensym_string;      /* gensym-string */

/* READ-READABLE-ELEMENT-FOR-KB */
Object read_readable_element_for_kb()
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object character_1, temp, temp_1, thing, temp_2, schar_new_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object readable_element, amf_available_array_cons_qm, amf_array;
    Object amf_result, new_float;
    double aref_new_value;
    Declare_special(4);
    Object result;

    x_note_fn_call(132,93);
    current_gensym_string = obtain_simple_gensym_string(FIX((SI_Long)2048L));
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
	    character_1 = Nil;
	  next_loop:
	    if ( !TRUEP(Read_kb_buffer_index))
		character_1 = Nil;
	    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		temp_1 = FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = temp_1;
		character_1 = temp;
	    }
	    else
		character_1 = read_next_char_for_kb_from_refilled_buffer();
	    if (CHAR_EQ(character_1,CHR(' ')))
		goto end_loop;
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = character_1;
		twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) 
			: thing);
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp_1 = Current_gensym_string;
		temp_2 = Fill_pointer_for_current_gensym_string;
		thing = character_1;
		schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			CHAR_CODE(thing) : thing);
		SET_SCHAR(temp_1,temp_2,schar_new_value);
		temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp_1;
	    }
	    goto next_loop;
	  end_loop:
	    result = read_from_string(5,Current_gensym_string,Nil,Nil,Kend,
		    Fill_pointer_for_current_gensym_string);
	    goto end_1;
	    result = VALUES_1(Qnil);
	  end_1:;
	    MVS_6(result,gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5);
	    reclaim_simple_gensym_string(Current_gensym_string);
	    temp = gensymed_symbol;
	    readable_element = temp;
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (FLOATP(readable_element)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
	    }
	    else {
		temp_1 = Available_float_array_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(readable_element);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (FLOATP(readable_element)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
	    }
	    else {
		temp_1 = Available_float_array_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	temp = lfloat(readable_element,float_constant);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else
	return VALUES_1(readable_element);
}

/* READ-PAST-READABLE-ELEMENT-FOR-KB */
Object read_past_readable_element_for_kb(print_qm)
    Object print_qm;
{
    Object character_1, temp, read_kb_buffer_index_new_value;

    x_note_fn_call(132,94);
    character_1 = Nil;
  next_loop:
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    if (print_qm)
	format((SI_Long)3L,T,"~c",character_1);
    if (CHAR_EQ(character_1,CHR(' ')))
	goto end_loop;
    goto next_loop;
  end_loop:
    if (print_qm)
	format((SI_Long)2L,T,"; end readable element~%");
    return VALUES_1(Nil);
}

/* READ-BYTE-CODE-BODY-FOR-KB */
Object read_byte_code_body_for_kb()
{
    Object body_vector_length, body_vector, constant_vector_qm;
    Object constant_vector_length_qm, environment_description;
    Object free_reference_vector_length_qm, free_references_qm;
    Object environment_description_as_read_qm, temp_1, temp_2, byte_code_body;
    SI_Long temp, length_in_words, left_half, right_half, i, ab_loop_bind_;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, aref_arg_2;
    SI_Long aref_new_value, index_1;
    char gensymed_symbol_3;

    x_note_fn_call(132,95);
    body_vector_length = read_element_for_kb(Nil);
    temp = (IFIX(body_vector_length) + ((SI_Long)4L - (SI_Long)1L)) / 
	    (SI_Long)4L;
    length_in_words = temp;
    body_vector = allocate_byte_vector(body_vector_length);
    constant_vector_qm = Nil;
    constant_vector_length_qm = Nil;
    environment_description = Nil;
    free_reference_vector_length_qm = Nil;
    free_references_qm = Nil;
    left_half = (SI_Long)0L;
    right_half = (SI_Long)0L;
    environment_description_as_read_qm = Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = length_in_words * (SI_Long)4L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)0L;
    gensymed_symbol_3 = 'a';
    gensymed_symbol_3 = CHARACTER_TO_CHAR(read_char_for_kb_past_newline());
    gensymed_symbol = 
	    IFIX(CHAR_CODE(CHAR_TO_CHARACTER(gensymed_symbol_3))) - 
	    (SI_Long)33L;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_2 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_2;
    }
    else
	temp_1 = read_next_char_for_kb_from_refilled_buffer();
    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
    gensymed_symbol = (SI_Long)94L * gensymed_symbol + gensymed_symbol_1;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_2 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_2;
    }
    else
	temp_1 = read_next_char_for_kb_from_refilled_buffer();
    gensymed_symbol_1 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_2 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_2;
    }
    else
	temp_1 = read_next_char_for_kb_from_refilled_buffer();
    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + gensymed_symbol_2;
    if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp_1 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	temp_2 = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = temp_2;
    }
    else
	temp_1 = read_next_char_for_kb_from_refilled_buffer();
    gensymed_symbol_2 = IFIX(CHAR_CODE(temp_1)) - (SI_Long)33L;
    gensymed_symbol_1 = (SI_Long)94L * gensymed_symbol_1 + gensymed_symbol_2;
    left_half = (gensymed_symbol << (SI_Long)3L) + (gensymed_symbol_1 >>  
	    -  - (SI_Long)16L);
    right_half = gensymed_symbol_1 & (SI_Long)65535L;
    gensymed_symbol = right_half & (SI_Long)255L;
    UBYTE_8_ISASET_1(body_vector,i,gensymed_symbol);
    aref_arg_2 = i + (SI_Long)1L;
    aref_new_value = right_half >>  -  - (SI_Long)8L;
    UBYTE_8_ISASET_1(body_vector,aref_arg_2,aref_new_value);
    aref_arg_2 = i + (SI_Long)2L;
    gensymed_symbol = left_half & (SI_Long)255L;
    UBYTE_8_ISASET_1(body_vector,aref_arg_2,gensymed_symbol);
    aref_arg_2 = i + (SI_Long)3L;
    aref_new_value = left_half >>  -  - (SI_Long)8L;
    UBYTE_8_ISASET_1(body_vector,aref_arg_2,aref_new_value);
    i = i + (SI_Long)4L;
    goto next_loop;
  end_loop:;
    constant_vector_length_qm = read_element_for_kb(Nil);
    if (constant_vector_length_qm) {
	constant_vector_qm = 
		allocate_managed_simple_vector(constant_vector_length_qm);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(constant_vector_length_qm);
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	temp_2 = read_element_for_kb(Nil);
	ISVREF(constant_vector_qm,index_1) = temp_2;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    environment_description_as_read_qm = read_element_for_kb(Nil);
    if (CONSP(environment_description_as_read_qm)) {
	environment_description = 
		convert_description_list_to_managed_array(1,
		environment_description_as_read_qm);
	reclaim_slot_value(environment_description_as_read_qm);
    }
    else
	environment_description = environment_description_as_read_qm;
    free_reference_vector_length_qm = read_element_for_kb(Nil);
    if (free_reference_vector_length_qm) {
	free_references_qm = 
		allocate_managed_simple_vector(free_reference_vector_length_qm);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(free_reference_vector_length_qm);
      next_loop_2:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_2;
	temp_2 = read_element_for_kb(Nil);
	ISVREF(free_references_qm,index_1) = temp_2;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    byte_code_body = make_byte_code_body_1(body_vector_length,body_vector,
	    constant_vector_qm,environment_description,free_references_qm);
    if (Loading_compiled_kb_p)
	add_new_byte_code_body(byte_code_body);
    return VALUES_1(byte_code_body);
}

/* READ-PAST-BYTE-CODE-BODY-FOR-KB */
Object read_past_byte_code_body_for_kb(print_qm)
    Object print_qm;
{
    Object length_in_words, constant_vector_length_qm, body_vector_length;
    Object free_reference_vector_length_qm, temp;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(132,96);
    length_in_words = Nil;
    constant_vector_length_qm = Nil;
    body_vector_length = Nil;
    free_reference_vector_length_qm = Nil;
    body_vector_length = read_element_for_kb(Nil);
    temp = FIX((IFIX(body_vector_length) + ((SI_Long)4L - (SI_Long)1L)) / 
	    (SI_Long)4L);
    length_in_words = temp;
    if (print_qm)
	format((SI_Long)3L,T,"~%; Byte code body; ~d words:~%",
		length_in_words);
    ab_loop_repeat_ = IFIX(length_in_words);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    read_past_binary_word_for_kb(print_qm);
    goto next_loop;
  end_loop:;
    constant_vector_length_qm = read_element_for_kb(Nil);
    if (constant_vector_length_qm) {
	if (print_qm)
	    format((SI_Long)3L,T,
		    "~%; Byte code body constant vector; ~d elements long:~%",
		    constant_vector_length_qm);
	ab_loop_repeat_ = IFIX(constant_vector_length_qm);
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	read_past_element_for_kb(print_qm);
	goto next_loop_1;
      end_loop_1:;
    }
    if (print_qm)
	format((SI_Long)2L,T,"~%; environment description:~%");
    read_past_element_for_kb(print_qm);
    free_reference_vector_length_qm = read_element_for_kb(Nil);
    if (free_reference_vector_length_qm) {
	if (print_qm)
	    format((SI_Long)3L,T,
		    "~%; Free reference vector; ~d elements long:~%",
		    free_reference_vector_length_qm);
	ab_loop_repeat_ = IFIX(free_reference_vector_length_qm);
      next_loop_2:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_2;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	read_past_element_for_kb(print_qm);
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

/* GHOST-DEFINITIONS-MAY-BE-SAVED-IN-WRONG-ORDER */
Object ghost_definitions_may_be_saved_in_wrong_order()
{
    x_note_fn_call(132,97);
    return VALUES_1( 
	    !TRUEP(system_version_greater_p(System_version_from_kb_being_read,
	    list_constant_12)) ? T : Nil);
}

/* READ-GHOST-DEFINITIONS */
Object read_ghost_definitions()
{
    Object reading_ghost_definitions_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,98);
    reading_ghost_definitions_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Reading_ghost_definitions_p,Qreading_ghost_definitions_p,reading_ghost_definitions_p,
	    0);
      if (ghost_definitions_may_be_saved_in_wrong_order())
	  result = read_ghost_definitions_2(order_ghost_definitions(read_ghost_definitions_1(Nil)));
      else
	  result = read_ghost_definitions_1(T);
    POP_SPECIAL();
    return result;
}

static Object Qab_gensym;          /* gensym */

/* ORDER-GHOST-DEFINITIONS */
Object order_ghost_definitions(definition_infos)
    Object definition_infos;
{
    Object result_1, definitions_with_ancestors;
    Object definitions_ready_to_be_processed, definitions_hash;
    Object definition_info, ab_loop_list_, definition_structure;
    Object definition_form, temp, definition, direct_superiors;
    Object possible_preceder, ab_loop_list__1, preceder_qm, temp_1;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, gensym_pop_store;
    Object cons_1, next_cons, svref_arg_2, next, ancestor;

    x_note_fn_call(132,99);
    result_1 = Nil;
    definitions_with_ancestors = Nil;
    definitions_ready_to_be_processed = Nil;
    definitions_hash = make_eq_hash_table(length(definition_infos),Nil,Nil);
    definition_info = Nil;
    ab_loop_list_ = definition_infos;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    definition_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    definition_structure = gensym_list_2(definition_info,FIX((SI_Long)0L));
    definitions_with_ancestors = gensym_cons_1(definition_structure,
	    definitions_with_ancestors);
    eq_puthash(definitions_hash,CAAR(definition_structure),
	    definition_structure);
    goto next_loop;
  end_loop:;
    definition_form = Nil;
    ab_loop_list_ = definitions_with_ancestors;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    definition_form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FIRST(definition_form);
    definition = THIRD(temp);
    direct_superiors = ISVREF(definition,(SI_Long)21L);
    possible_preceder = Nil;
    ab_loop_list__1 = direct_superiors;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    possible_preceder = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    preceder_qm = eq_gethash(definitions_hash,possible_preceder,Nil);
    if (preceder_qm) {
	temp_1 = FIXNUM_ADD1(CADR(definition_form));
	M_CADR(definition_form) = temp_1;
	gensym_push_modify_macro_arg = definition_form;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = CDDR(preceder_qm);
	temp_1 = gensym_cons_1(car_1,cdr_1);
	M_CDDR(preceder_qm) = temp_1;
    }
    goto next_loop_2;
  end_loop_2:;
    if (IFIX(CADR(definition_form)) == (SI_Long)0L)
	definitions_ready_to_be_processed = gensym_cons_1(definition_form,
		definitions_ready_to_be_processed);
    goto next_loop_1;
  end_loop_1:;
    reclaim_eq_hash_table(definitions_hash);
  next_loop_3:
    if ( !TRUEP(definitions_ready_to_be_processed))
	goto end_loop_3;
    gensym_pop_store = Nil;
    cons_1 = definitions_ready_to_be_processed;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    definitions_ready_to_be_processed = next_cons;
    next = gensym_pop_store;
    result_1 = gensym_cons_1(CAR(next),result_1);
    ancestor = Nil;
    ab_loop_list_ = CDDR(next);
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    ancestor = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = FIXNUM_SUB1(SECOND(ancestor));
    M_SECOND(ancestor) = temp_1;
    if (IFIX(SECOND(ancestor)) == (SI_Long)0L)
	definitions_ready_to_be_processed = gensym_cons_1(ancestor,
		definitions_ready_to_be_processed);
    goto next_loop_4;
  end_loop_4:;
    reclaim_gensym_list_1(next);
    goto next_loop_3;
  end_loop_3:
    reclaim_gensym_list_1(definitions_with_ancestors);
    return nreverse(result_1);
}

/* READ-GHOST-DEFINITIONS-1 */
Object read_ghost_definitions_1(install_qm)
    Object install_qm;
{
    Object information_on_ghost_definitions;
    Object class_name_read_while_reading_current_ghost_definition;
    Object definition_qm, new_name, second_arg, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,100);
    if (install_qm) {
	information_on_ghost_definitions = Nil;
	class_name_read_while_reading_current_ghost_definition = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Class_name_read_while_reading_current_ghost_definition,Qclass_name_read_while_reading_current_ghost_definition,class_name_read_while_reading_current_ghost_definition,
		0);
	  definition_qm = Nil;
	next_loop:
	  definition_qm = read_element_for_kb(T);
	  if ( !TRUEP(definition_qm))
	      goto end_loop;
	  information_on_ghost_definitions = 
		  slot_value_cons_1(slot_value_list_3(Class_name_read_while_reading_current_ghost_definition,
		  Nil,definition_qm),information_on_ghost_definitions);
	  new_name = 
		  read_ghost_definition_2(Class_name_read_while_reading_current_ghost_definition,
		  definition_qm,information_on_ghost_definitions);
	  second_arg = CAR(information_on_ghost_definitions);
	  M_SECOND(second_arg) = new_name;
	  goto next_loop;
	end_loop:
	  reclaim_slot_value_tree_1(information_on_ghost_definitions);
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else {
	class_name_read_while_reading_current_ghost_definition = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Class_name_read_while_reading_current_ghost_definition,Qclass_name_read_while_reading_current_ghost_definition,class_name_read_while_reading_current_ghost_definition,
		0);
	  definition_qm = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_1:
	  definition_qm = read_element_for_kb(T);
	  if ( !TRUEP(definition_qm))
	      goto end_loop_1;
	  ab_loopvar__2 = 
		  slot_value_cons_1(slot_value_list_3(Class_name_read_while_reading_current_ghost_definition,
		  Nil,definition_qm),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_1;
	end_loop_1:
	  result = VALUES_1(ab_loopvar_);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

/* READ-GHOST-DEFINITIONS-2 */
Object read_ghost_definitions_2(information_on_ghost_definitions_qm)
    Object information_on_ghost_definitions_qm;
{
    Object ghost_definition_information, ab_loop_list_, class_name;
    Object new_name_qm, new_definition, new_name, temp;

    x_note_fn_call(132,101);
    ghost_definition_information = Nil;
    ab_loop_list_ = information_on_ghost_definitions_qm;
    class_name = Nil;
    new_name_qm = Nil;
    new_definition = Nil;
    new_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ghost_definition_information = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_name = CAR(ghost_definition_information);
    temp = CDR(ghost_definition_information);
    new_name_qm = CAR(temp);
    temp = CDR(ghost_definition_information);
    temp = CDR(temp);
    new_definition = CAR(temp);
    new_name = read_ghost_definition_2(class_name,new_definition,
	    information_on_ghost_definitions_qm);
    if (new_name)
	M_SECOND(ghost_definition_information) = new_name;
    goto next_loop;
  end_loop:
    reclaim_slot_value_tree_1(information_on_ghost_definitions_qm);
    return VALUES_1(Qnil);
}

static Object Qjunction_block_class_for_connection;  /* junction-block-class-for-connection */

static Object list_constant_13;    /* # */

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

/* READ-GHOST-DEFINITION-2 */
Object read_ghost_definition_2(class_name,new_definition,
	    information_on_ghost_definitions_qm)
    Object class_name, new_definition, information_on_ghost_definitions_qm;
{
    Object old_definition_qm, old_class_definition_is_frame_p_qm;
    Object sub_class_bit_vector, definition_classes_are_compatible_qm;
    Object slot_differences_qm;
    Object add_junction_block_class_to_slot_differences_qm;
    Object names_of_differing_slots_qm, direct_superiors_qm;
    Object adjusted_direct_superiors_qm, changed_direct_superiors_qm, sublist;
    Object direct_superior, new_name_qm, temp_1, direct_superior_classes_qm;
    Object new_name;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp;

    x_note_fn_call(132,102);
    old_definition_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_definition_gkbprop);
    old_class_definition_is_frame_p_qm = old_definition_qm ? 
	    (ATOM(old_definition_qm) ? T : Nil) : Qnil;
    if (old_class_definition_is_frame_p_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(new_definition,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(old_definition_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Object_definition_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		definition_classes_are_compatible_qm = (SI_Long)0L < 
			gensymed_symbol ? T : Nil;
	    }
	    else
		definition_classes_are_compatible_qm = Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(new_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_definition_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(old_definition_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    definition_classes_are_compatible_qm = (SI_Long)0L < 
			    gensymed_symbol ? T : Nil;
		}
		else
		    definition_classes_are_compatible_qm = Nil;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(new_definition,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Message_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(old_definition_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Message_definition_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			definition_classes_are_compatible_qm = (SI_Long)0L 
				< gensymed_symbol ? T : Nil;
		    }
		    else
			definition_classes_are_compatible_qm = Nil;
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(new_definition,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Class_definition_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			definition_classes_are_compatible_qm =  
				!TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(old_definition_qm)) 
				? T : Nil;
		    else
			definition_classes_are_compatible_qm = Nil;
		}
	    }
	}
    }
    else
	definition_classes_are_compatible_qm = Nil;
    if (old_class_definition_is_frame_p_qm) {
	if (IFIX(Kb_flags) < (SI_Long)262L)
	    fix_up_default_overrides_for_5_0(new_definition);
	if (IFIX(Kb_flags) < (SI_Long)269L) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_definition_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    normalize_message_properties_for_message_definition(new_definition);
	slot_differences_qm = old_class_definition_is_frame_p_qm ? 
		find_differences_in_frames_if_any(4,old_definition_qm,
		new_definition,Nil,definition_classes_are_compatible_qm) : 
		Qnil;
	sub_class_bit_vector = ISVREF(ISVREF(old_definition_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_definition_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_definition_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  !EQ(ISVREF(old_definition_qm,(SI_Long)32L),
		ISVREF(new_definition,(SI_Long)32L)) : TRUEP(Nil)) {
	    add_junction_block_class_to_slot_differences_qm = 
		    deal_with_junction_block_class_differences(new_definition,
		    old_definition_qm,class_name);
	    if (add_junction_block_class_to_slot_differences_qm)
		slot_differences_qm = nconc2(slot_differences_qm,
			slot_value_cons_1(Qjunction_block_class_for_connection,
			Nil));
	}
	if (slot_differences_qm && 
		system_revision_greater_p(list_constant_13,
		System_version_from_kb_being_read) && IFIX(Kb_flags) < 
		(SI_Long)254L) {
	    if ( 
		    !TRUEP(fix_up_configuration_attribute_error(old_definition_qm,
		    new_definition,slot_differences_qm)))
		fix_up_configuration_attribute_error(new_definition,
			old_definition_qm,slot_differences_qm);
	}
	names_of_differing_slots_qm = slot_differences_qm;
    }
    else
	names_of_differing_slots_qm = Nil;
    svref_new_value = IFIX(ISVREF(new_definition,(SI_Long)5L)) | (SI_Long)32L;
    ISVREF(new_definition,(SI_Long)5L) = FIX(svref_new_value);
    if ( !TRUEP(old_definition_qm)) {
	if ( !TRUEP(Dont_load_if_definitions_have_changed_p))
	    install_class_definition(class_name,new_definition,Nil,Nil,T);
	if ( !TRUEP(assq_function(class_name,Class_name_conflicts)))
	    record_class_name_conflict(6,class_name,Nil,Nil,new_definition,
		    Nil,T);
	return VALUES_1(Nil);
    }
    else {
	if (old_class_definition_is_frame_p_qm) {
	    direct_superiors_qm = ISVREF(new_definition,(SI_Long)21L);
	    adjusted_direct_superiors_qm = direct_superiors_qm ? 
		    (ATOM(direct_superiors_qm) ? 
		    slot_value_cons_1(direct_superiors_qm,Nil) : 
		    direct_superiors_qm) : Qnil;
	    changed_direct_superiors_qm = Nil;
	    sublist = adjusted_direct_superiors_qm;
	    direct_superior = Nil;
	    new_name_qm = Nil;
	  next_loop:
	    if ( !TRUEP(sublist))
		goto end_loop;
	    direct_superior = FIRST(sublist);
	    temp_1 = assq_function(class_name,
		    information_on_ghost_definitions_qm);
	    new_name_qm = SECOND(temp_1);
	    if (new_name_qm) {
		changed_direct_superiors_qm = T;
		M_FIRST(sublist) = new_name_qm;
	    }
	    sublist = M_CDR(sublist);
	    goto next_loop;
	  end_loop:;
	    if (changed_direct_superiors_qm) {
		initialize_slot_description_value(new_definition,
			get_slot_description_of_class_description_function(Qdirect_superiors_of_defined_class,
			ISVREF(new_definition,(SI_Long)1L),Nil),
			adjusted_direct_superiors_qm);
		if ( 
			!TRUEP(memq_function(Qdirect_superiors_of_defined_class,
			names_of_differing_slots_qm)))
		    names_of_differing_slots_qm = 
			    nconc2(names_of_differing_slots_qm,
			    slot_value_cons_1(Qdirect_superiors_of_defined_class,
			    Nil));
	    }
	}
	if (old_class_definition_is_frame_p_qm &&  
		!TRUEP(names_of_differing_slots_qm)) {
	    delete_block_after_reading_kb(new_definition);
	    return VALUES_1(Nil);
	}
	else {
	    if (names_of_differing_slots_qm) {
		direct_superior_classes_qm = ISVREF(new_definition,
			(SI_Long)21L);
		reclaim_slot_value(get_lookup_slot_value_given_default(new_definition,
			Qclass_inheritance_path_of_definition,Nil));
		set_non_savable_lookup_slot_value(new_definition,
			Qclass_inheritance_path_of_definition,
			direct_superiors_are_defined_p(direct_superior_classes_qm) 
			? 
			make_class_inheritance_path_for_user_defined_class(Nil,
			direct_superior_classes_qm) : Nil);
		new_name = name_class_with_variant_name(class_name,
			new_definition);
	    }
	    else
		new_name = Nil;
	    if (Dont_load_if_definitions_have_changed_p)
		record_class_name_conflict(6,class_name,Nil,
			old_definition_qm,new_definition,
			names_of_differing_slots_qm,T);
	    else
		install_class_definition(class_name,new_definition,
			new_name,names_of_differing_slots_qm,Nil);
	    return VALUES_1(new_name);
	}
    }
}

static Object Qconfiguration;      /* configuration */

/* FIX-UP-CONFIGURATION-ATTRIBUTE-ERROR */
Object fix_up_configuration_attribute_error(definition1,definition2,
	    names_of_differing_slots)
    Object definition1, definition2, names_of_differing_slots;
{
    Object superior, ab_loop_list_, ab_loop_it_, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, definition1_attributes;
    Object definition1_configuration_attribute_description;
    Object copied_definition1_configuration_attribute_description;
    Object definition2_configuration_default_override, attribute_initial_value;
    Object attribute_initial_type_qm;
    Object proposed_definition1_configuration_default_override;
    Object definition1_default_overrides, new_definition1_default_overrides;
    Object new_override_added_qm, definition2_list, last_definition1_override;
    Object override, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Object result;

    x_note_fn_call(132,103);
    if (memq_function(Qclass_specific_attributes,names_of_differing_slots) 
	    && memq_function(Qdefault_overrides,names_of_differing_slots) 
	    && member(4,Qconfiguration,ISVREF(definition1,(SI_Long)22L),
	    Ktest,Qcar_eq) &&  !TRUEP(member(4,Qconfiguration,
	    ISVREF(definition2,(SI_Long)22L),Ktest,Qcar_eq)) && member(4,
	    Qconfiguration,ISVREF(definition2,(SI_Long)27L),Ktest,Qcar_eq)) {
	superior = Nil;
	ab_loop_list_ = ISVREF(definition1,(SI_Long)21L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = superior;
	key_hash_value = SXHASH_SYMBOL_1(superior) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_1:
	if (level < ab_loop_bind_)
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_2:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_2;
      end_loop_3:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_4:
	if (level < ab_loop_bind_)
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_5:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_5;
      end_loop_6:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_8;
	  end_loop_9:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_10:
	    if (level < ab_loop_bind_)
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_11;
	  end_loop_12:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_10;
	  end_loop_10:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	ab_loop_it_ = 
		get_slot_description_of_class_description_function(Qconfiguration,
		gensymed_symbol,Nil);
	if (ab_loop_it_) {
	    temp_3 = TRUEP(ab_loop_it_);
	    goto end_5;
	}
	goto next_loop;
      end_loop:
	temp_3 = TRUEP(Qnil);
      end_5:;
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	definition1_attributes = ISVREF(definition1,(SI_Long)22L);
	temp_1 = member(4,Qconfiguration,definition1_attributes,Ktest,Qcar_eq);
	definition1_configuration_attribute_description = CAR(temp_1);
	copied_definition1_configuration_attribute_description = 
		copy_for_slot_value(definition1_configuration_attribute_description);
	temp_1 = member(4,Qconfiguration,ISVREF(definition2,(SI_Long)27L),
		Ktest,Qcar_eq);
	definition2_configuration_default_override = CAR(temp_1);
	temp_1 = CDDR(copied_definition1_configuration_attribute_description);
	attribute_initial_value = copy_for_slot_value(CAR(temp_1));
	temp_1 = CDDDR(copied_definition1_configuration_attribute_description);
	attribute_initial_type_qm = copy_for_slot_value(CAR(temp_1));
	if (CONSP(attribute_initial_value) && 
		EQ(CAR(attribute_initial_value),Kfuncall))
	    temp_1 = 
		    slot_value_list_3(CAR(copied_definition1_configuration_attribute_description),
		    slot_value_cons_1(attribute_initial_value,Nil),
		    Quser_defined);
	else if (attribute_initial_value || attribute_initial_type_qm)
	    temp_1 = 
		    slot_value_list_3(CAR(copied_definition1_configuration_attribute_description),
		    attribute_initial_type_qm ? 
		    slot_value_list_2(attribute_initial_value,
		    attribute_initial_type_qm) : attribute_initial_value,
		    Quser_defined);
	else
	    temp_1 = Qnil;
	reclaim_slot_value(copied_definition1_configuration_attribute_description);
	proposed_definition1_configuration_default_override = temp_1;
	if (EQUAL(definition2_configuration_default_override,
		proposed_definition1_configuration_default_override)) {
	    definition1_default_overrides = ISVREF(definition1,(SI_Long)27L);
	    if ( !TRUEP(definition1_default_overrides))
		new_definition1_default_overrides = 
			slot_value_cons_1(proposed_definition1_configuration_default_override,
			Nil);
	    else {
		new_override_added_qm = Nil;
		definition2_list = ISVREF(definition2,(SI_Long)27L);
		temp_1 = last(definition1_default_overrides,_);
		last_definition1_override = CAR(temp_1);
		override = Nil;
		ab_loop_list_ = definition1_default_overrides;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_13:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_13;
		override = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(definition2_list))
		    ab_loopvar__2 =  !TRUEP(new_override_added_qm) && 
			    EQ(override,last_definition1_override) ? 
			    slot_value_list_2(override,
			    proposed_definition1_configuration_default_override) 
			    : slot_value_cons_1(override,Nil);
		else {
		    temp_1 = CAR(definition2_list);
		    if (EQ(CAR(temp_1),Qconfiguration)) {
			new_override_added_qm = T;
			definition2_list = Nil;
			ab_loopvar__2 = 
				slot_value_list_2(proposed_definition1_configuration_default_override,
				override);
		    }
		    else {
			definition2_list = CDR(definition2_list);
			ab_loopvar__2 = slot_value_cons_1(override,Nil);
		    }
		}
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		goto next_loop_13;
	      end_loop_13:
		new_definition1_default_overrides = ab_loopvar_;
		goto end_6;
		new_definition1_default_overrides = Qnil;
	      end_6:;
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(definition1,Qclass_specific_attributes);
	    temp_2 = 
		    delete_slot_value_element_1(definition1_configuration_attribute_description,
		    definition1_attributes);
	    SVREF(definition1,FIX((SI_Long)22L)) = temp_2;
	    reclaim_slot_value(definition1_configuration_attribute_description);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(definition1,Qdefault_overrides);
	    SVREF(definition1,FIX((SI_Long)27L)) = 
		    new_definition1_default_overrides;
	    return VALUES_1(T);
	}
	else {
	    reclaim_slot_value(proposed_definition1_configuration_default_override);
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_47;  /* "~A ~A~A~Aencountered while reading.  ~S either: (1) is not a KB, (2) has ~
				    *      been damaged, or (3) was not written properly due to a system software ~
				    *      error."
				    */

static Object string_constant_48;  /* "Bad character" */

static Object string_constant_49;  /* "End-of-file unexpectedly" */

static Object string_constant_50;  /* "(" */

static Object string_constant_51;  /* ") " */

static Object string_constant_52;  /* " " */

/* ABORT-ON-BAD-KB */
Object abort_on_bad_kb varargs_1(int, n)
{
    Object problem_character_unless_eof_qm, temp, text_string;
    Object error_message_as_text_string, error_message_as_gensym_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(132,104);
    INIT_ARGS_nonrelocating();
    problem_character_unless_eof_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = problem_character_unless_eof_qm;
    if (temp);
    else
	temp = string_constant_2;
    text_string = tformat_text_string(6,string_constant_47,
	    problem_character_unless_eof_qm ? string_constant_48 : 
	    string_constant_49,problem_character_unless_eof_qm ? 
	    string_constant_50 : string_constant_2,temp,
	    problem_character_unless_eof_qm ? string_constant_51 : 
	    string_constant_52,Name_text_string_for_kb_being_read);
    error_message_as_text_string = export_text_string(2,text_string,Qkb_error);
    error_message_as_gensym_string = 
	    wide_string_to_string(error_message_as_text_string);
    return error((SI_Long)2L,"~a",error_message_as_gensym_string);
}

/* PROCESS-SLOT-GROUP-FOR-BLOCK */
Object process_slot_group_for_block(block,slot_group_data)
    Object block, slot_group_data;
{
    Object left_edge, top_edge, right_edge, bottom_edge, subblocks;
    Object connections, slot_group_for_block, subblock, ab_loop_list_;
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, temp;

    x_note_fn_call(132,105);
    if (slot_group_data) {
	left_edge = FIRST(slot_group_data);
	top_edge = SECOND(slot_group_data);
	right_edge = THIRD(slot_group_data);
	bottom_edge = FOURTH(slot_group_data);
	subblocks = FIFTH(slot_group_data);
	connections = SIXTH(slot_group_data);
	if ( !( !TRUEP(ISVREF(block,(SI_Long)14L)) && IFIX(left_edge) == 
		(SI_Long)0L && IFIX(top_edge) == (SI_Long)0L && 
		IFIX(right_edge) == (SI_Long)0L && IFIX(bottom_edge) == 
		(SI_Long)0L && EQ(subblocks,Nil) && EQ(connections,Nil))) {
	    slot_group_for_block = ISVREF(block,(SI_Long)14L);
	    if (slot_group_for_block);
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(block,Qslot_group_for_block_qm);
		slot_group_for_block = make_icon_slot_group_1();
		SVREF(block,FIX((SI_Long)14L)) = slot_group_for_block;
	    }
	    SVREF(slot_group_for_block,FIX((SI_Long)0L)) = left_edge;
	    SVREF(slot_group_for_block,FIX((SI_Long)1L)) = top_edge;
	    SVREF(slot_group_for_block,FIX((SI_Long)2L)) = right_edge;
	    SVREF(slot_group_for_block,FIX((SI_Long)3L)) = bottom_edge;
	    subblock = Nil;
	    ab_loop_list_ = subblocks;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    subblock = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = subblock;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    gensymed_symbol_1 = block;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
		temp = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp,FIX((SI_Long)5L)) = gensymed_symbol_1;
	    }
	    goto next_loop;
	  end_loop:;
	    if (subblocks) {
		temp = upgrade_subblocks(subblocks);
		SVREF(slot_group_for_block,FIX((SI_Long)4L)) = temp;
	    }
	    if (connections) {
		temp = upgrade_connections(connections);
		SVREF(slot_group_for_block,FIX((SI_Long)6L)) = temp;
		Blocks_with_connections_from_kb_read = gensym_cons_1(block,
			Blocks_with_connections_from_kb_read);
	    }
	}
	reclaim_slot_value_list_1(slot_group_data);
    }
    return VALUES_1(Nil);
}

static Object string_constant_53;  /* ", " */

static Object string_constant_54;  /* "This KB, which was created before version 2.0, has ~
				    *                     subworkspaces that have the same names as their superior objects. The names of ~
				    *                     these subworkspaces have been removed. They are: ~(~a~)"
				    */

/* FIX-SUBWORKSPACE-NAMES */
Object fix_subworkspace_names()
{
    Object kb_flags, names_removed, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object kb_workspace, superior_item, kb_workspace_name;
    Object superior_item_name_or_names, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object listed_name, names_removed_as_text;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(132,106);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,6);
      if ( !(IFIX(Kb_flags) >= (SI_Long)33L)) {
	  names_removed = Nil;
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  kb_workspace = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,5);
	    superior_item = Nil;
	    ab_loopvar_ = collect_subclasses(Qkb_workspace);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    kb_workspace = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    superior_item = ISVREF(kb_workspace,(SI_Long)18L);
	    if (superior_item) {
		kb_workspace_name = 
			get_lookup_slot_value_given_default(kb_workspace,
			Qname_or_names_for_frame,Nil);
		superior_item_name_or_names = 
			get_lookup_slot_value_given_default(superior_item,
			Qname_or_names_for_frame,Nil);
		if (kb_workspace_name && superior_item_name_or_names && 
			(EQ(kb_workspace_name,superior_item_name_or_names) 
			|| CONSP(superior_item_name_or_names) && 
			memq_function(kb_workspace_name,
			superior_item_name_or_names))) {
		    names_removed = gensym_cons_1(kb_workspace_name,
			    names_removed);
		    change_slot_value(3,kb_workspace,
			    Qname_or_names_for_frame,Nil);
		}
	    }
	    goto next_loop;
	  end_loop_1:
	    if (names_removed) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
		  current_wide_string = wide_string_bv16;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			  3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  listed_name = names_removed;
			next_loop_2:
			  if ( !TRUEP(listed_name))
			      goto end_loop_2;
			  twrite(CAR(listed_name));
			  if (CDR(listed_name))
			      twrite(string_constant_53);
			  listed_name = M_CDR(listed_name);
			  goto next_loop_2;
			end_loop_2:;
			  names_removed_as_text = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_engineer(2,string_constant_54,names_removed_as_text);
		reclaim_text_string(names_removed_as_text);
		reclaim_gensym_list_1(names_removed);
	    }
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qdata_type_of_variable_or_parameter;  /* data-type-of-variable-or-parameter */

static Object Qinitial_value_of_variable_or_parameter;  /* initial-value-of-variable-or-parameter */

static Object Qg2_array_initial_values;  /* g2-array-initial-values */

/* FIX-UP-DEFAULT-OVERRIDES-FOR-5-0 */
Object fix_up_default_overrides_for_5_0(definition)
    Object definition;
{
    Object override, ab_loop_list_, slot_name, temp, cdr_new_value;

    x_note_fn_call(132,107);
    if (EQ(get_specialized_definition_class(definition),Qclass_definition) 
	    && IFIX(Kb_flags) < (SI_Long)262L && ISVREF(definition,
	    (SI_Long)27L)) {
	override = Nil;
	ab_loop_list_ = ISVREF(definition,(SI_Long)27L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(EQ(THIRD(override),Quser_defined) || THIRD(override))) {
	    slot_name = FIRST(override);
	    if (EQ(slot_name,Qdata_type_of_variable_or_parameter) || 
		    EQ(slot_name,Qinitial_value_of_variable_or_parameter) 
		    || EQ(slot_name,Qg2_array_initial_values)) {
		temp = CDR(override);
		cdr_new_value = nconc2(temp,
			slot_value_cons_1(most_refined_foundation_class_of_direct_superiors(2,
			ISVREF(definition,(SI_Long)21L),slot_name),Nil));
		M_CDR(override) = cdr_new_value;
	    }
	}
	goto next_loop;
      end_loop:;
	temp = make_text_representation_for_slot_value(3,definition,
		Qdefault_overrides,Nil);
	parse_text_for_slot(3,temp,definition,
		get_slot_description_of_class_description_function(Qdefault_overrides,
		ISVREF(definition,(SI_Long)1L),Nil));
    }
    return VALUES_1(Nil);
}

static Object Qdefinition;         /* definition */

/* INITIALIZE-AFTER-READING-FOR-DEFINITION */
Object initialize_after_reading_for_definition(definition)
    Object definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(132,108);
    frame = definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qdefinition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    if (ISVREF(definition,(SI_Long)23L) && 
	    IFIX(FIRST(System_version_from_kb_being_read)) == (SI_Long)7L 
	    && IFIX(SECOND(System_version_from_kb_being_read)) == 
	    (SI_Long)0L && IFIX(System_revision_from_last_kb_read) == 
	    (SI_Long)0L && FIXNUM_EQ(System_quality_from_last_kb_read,
	    Release_quality))
	return fix_up_double_click_configuration_clauses(ISVREF(definition,
		(SI_Long)23L));
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-AFTER-READING-FOR-OBJECT-DEFINITION */
Object initialize_after_reading_for_object_definition(object_definition)
    Object object_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(132,109);
    frame = object_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qobject_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* CLEAN-UP-ORPHAN-FRAME-REPRESENTATIONS */
Object clean_up_orphan_frame_representations()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, table, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, gensymed_symbol_5;
    Object ab_loop_list_, ab_loop_list__1, represented_frame, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(1);

    x_note_fn_call(132,110);
  next_loop:
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    table = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qtable);
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_2;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      table = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      gensymed_symbol = ACCESS_ONCE(ISVREF(table,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      temp =  !TRUEP(gensymed_symbol);
      if (temp);
      else {
	  gensymed_symbol = table;
	  gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
	  sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
	  superior_class_bit_number = IFIX(ISVREF(Table_class_description,
		  (SI_Long)18L));
	  sub_class_vector_index = superior_class_bit_number >>  -  - 
		  (SI_Long)3L;
	  if (sub_class_vector_index < 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	      gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		      sub_class_vector_index);
	      gensymed_symbol_3 = (SI_Long)1L;
	      gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	      gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	      gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	      temp = (SI_Long)0L < gensymed_symbol_2;
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      gensymed_symbol_1 = Nil;
	      gensymed_symbol_5 = Nil;
	      ab_loop_list_ = ISVREF(gensymed_symbol,(SI_Long)19L);
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      gensymed_symbol_5 = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol = Nil;
	      ab_loop_list__1 = gensymed_symbol_5;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_3;
	      gensymed_symbol = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      if (gensymed_symbol && CONSP(gensymed_symbol)) {
		  represented_frame = 
			  get_slot_represented_by_text_cell_if_any(gensymed_symbol);
		  if (represented_frame &&  !EQ(gensymed_symbol_1,
			  represented_frame)) {
		      gensymed_symbol_1 = represented_frame;
		      if (SIMPLE_VECTOR_P(represented_frame) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(represented_frame)) 
			      > (SI_Long)2L &&  
			      !EQ(ISVREF(represented_frame,(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(represented_frame,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp =  !temp;
		      if (temp);
		      else
			  temp = 
				  TRUEP(check_for_table_representing_recycled_definition(table));
		      if (temp) {
			  temp = TRUEP(T);
			  goto end_search;
		      }
		  }
	      }
	      goto next_loop_4;
	    end_loop_3:;
	      goto next_loop_3;
	    end_loop_2:
	      temp = TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	end_search:;
      }
      if (temp) {
	  delete_frame(table);
	  temp = TRUEP(T);
	  goto end_1;
      }
      goto next_loop_1;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if ( !temp)
	goto end_loop_4;
    goto next_loop;
  end_loop_4:
    return VALUES_1(Nil);
}

/* CHECK-FOR-TABLE-REPRESENTING-RECYCLED-DEFINITION */
Object check_for_table_representing_recycled_definition(table)
    Object table;
{
    Object row, ab_loop_list_, ab_loop_it_, cell_qm, ab_loop_list__1, frame_qm;
    Object slot_name_or_index, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(132,111);
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      ab_loop_it_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      cell_qm = Nil;
      ab_loop_list__1 = Row;
      ab_loop_it_ = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_qm = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (cell_qm && CONSP(cell_qm)) {
	  result = get_slot_represented_by_text_cell_if_any(cell_qm);
	  MVS_2(result,frame_qm,slot_name_or_index);
	  if (EQ(slot_name_or_index,Qdirect_superiors_of_defined_class)) {
	      sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Class_definition_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_1 = (SI_Long)1L;
		  gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		  gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		  temp = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp = TRUEP(Nil);
	      ab_loop_it_ =  !temp ? T : Nil;
	  }
	  else
	      ab_loop_it_ = Nil;
      }
      else
	  ab_loop_it_ = Nil;
      if (ab_loop_it_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
      ab_loop_it_ = Qnil;
    end_1:;
      if (ab_loop_it_) {
	  result = VALUES_1(ab_loop_it_);
	  goto end_2;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* MAKE-GRAPHS-OPAQUE */
Object make_graphs_opaque()
{
    Object kb_flags;
    Declare_special(1);

    x_note_fn_call(132,112);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !(IFIX(Kb_flags) >= (SI_Long)38L))
	  make_graphs_opaque_1();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qrule;               /* rule */

static Object Qtext_box_format;    /* text-box-format */

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

/* MAKE-ALL-RULE-BOXES-HAVE-TEXT-BOX-FORMAT */
Object make_all_rule_boxes_have_text_box_format()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, text_box;
    Object format_name, svref_new_value;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,113);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)39L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  text_box = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qrule);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    text_box = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if ( !TRUEP(ISVREF(text_box,(SI_Long)17L))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(text_box,Qtext_box_format);
		format_name = get_lookup_slot_value(text_box,
			Qdefault_text_box_format_name);
		svref_new_value = 
			get_instance_with_name_if_any(Qformat_frame,
			format_name);
		if (svref_new_value);
		else
		    svref_new_value = make_format_frame(format_name);
		SVREF(text_box,FIX((SI_Long)17L)) = svref_new_value;
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qjunction_block_class_for_class;  /* junction-block-class-for-class */

static Object Qincomplete;         /* incomplete */

/* FIX-UNIMPLEMENTED-DEFINITIONS */
Object fix_unimplemented_definitions()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, definition, class_qm;
    Object gensymed_symbol, temp_1, ab_loopvar__2, ab_loopvar__3, definition_1;
    Object class_name, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, temp_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(132,114);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      class_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qclass_definition);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      class_qm = ISVREF(definition,(SI_Long)20L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	      (SI_Long)262144L))) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(definition,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  temp =  !TRUEP(gensymed_symbol);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  temp_1 = ISVREF(definition,(SI_Long)8L);
	  temp =  !EQ(CAR(temp_1),Nil);
	  if (temp);
	  else {
	      scope_conses = Scope_conses;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__3 = Nil;
	      definition_1 = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		class_name = Nil;
		ab_loopvar__2 = collect_subclasses(Qclass_definition);
	      next_loop_2:
		if ( !TRUEP(ab_loopvar__3)) {
		  next_loop_3:
		    if ( !TRUEP(ab_loopvar__2))
			goto end_loop_2;
		    ab_loopvar__3 = 
			    lookup_kb_specific_property_value(M_CAR(ab_loopvar__2),
			    Instances_specific_to_this_class_kbprop);
		    ab_loopvar__2 = M_CDR(ab_loopvar__2);
		    if (ab_loopvar__3)
			goto end_loop_2;
		    goto next_loop_3;
		  end_loop_2:
		    temp =  !TRUEP(ab_loopvar__3);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    goto end_loop_3;
		definition_1 = ab_loopvar__3;
		ab_loopvar__3 = ISVREF(ab_loopvar__3,(SI_Long)6L);
		class_name = ISVREF(definition_1,(SI_Long)20L);
		if (SYMBOLP(class_name)) {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = class_name;
		    key_hash_value = SXHASH_SYMBOL_1(class_name) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_4:
		    if (level < ab_loop_bind_)
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_5:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_6:
		    if ( !TRUEP(marked))
			goto end_loop_5;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_6;
		  end_loop_5:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_1;
		    goto next_loop_5;
		  end_loop_6:
		  end_1:
		    level = level - (SI_Long)1L;
		    goto next_loop_4;
		  end_loop_4:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = class_name;
			temp_2 = Symbol_properties_table;
			temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			tail = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				Nil);
			head = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				tail);
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_2 = new_cons;
			}
			else
			    gensymed_symbol_2 = Nil;
			if ( !TRUEP(gensymed_symbol_2))
			    gensymed_symbol_2 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_2) = head;
			M_CDR(gensymed_symbol_2) = tail;
			inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
			M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
			gensymed_symbol = set_skip_list_entry(temp_2,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_1,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_7:
		    if (level < ab_loop_bind_)
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_8:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_9:
		    if ( !TRUEP(marked))
			goto end_loop_8;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_9;
		  end_loop_8:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_2;
		    goto next_loop_8;
		  end_loop_9:
		  end_2:
		    level = level - (SI_Long)1L;
		    goto next_loop_7;
		  end_loop_7:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_10:
			if (level < ab_loop_bind_)
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_11:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_12:
			if ( !TRUEP(marked))
			    goto end_loop_11;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_12;
		      end_loop_11:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_3;
			goto next_loop_11;
		      end_loop_12:
		      end_3:
			level = level - (SI_Long)1L;
			goto next_loop_10;
		      end_loop_10:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			skip_list = CDR(global_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_13:
			if (level < ab_loop_bind_)
			    goto end_loop_13;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_14:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_15:
			if ( !TRUEP(marked))
			    goto end_loop_14;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_15;
		      end_loop_14:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_4;
			goto next_loop_14;
		      end_loop_15:
		      end_4:
			level = level - (SI_Long)1L;
			goto next_loop_13;
		      end_loop_13:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    temp = TRUEP(resulting_value);
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? TRUEP(memq_function(Qconnection,
			get_lookup_slot_value_given_default(definition_1,
			Qclass_inheritance_path_of_definition,Nil))) : 
			TRUEP(Nil)) {
		    temp_1 = class_qm;
		    skip_list = CDR(Symbol_properties_table);
		    key_value = class_name;
		    key_hash_value = SXHASH_SYMBOL_1(class_name) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_16:
		    if (level < ab_loop_bind_)
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_17:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_18:
		    if ( !TRUEP(marked))
			goto end_loop_17;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_18;
		  end_loop_17:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_5;
		    goto next_loop_17;
		  end_loop_18:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_16;
		  end_loop_16:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = class_name;
			temp_3 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			tail = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				Nil);
			head = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				tail);
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_2 = new_cons;
			}
			else
			    gensymed_symbol_2 = Nil;
			if ( !TRUEP(gensymed_symbol_2))
			    gensymed_symbol_2 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_2) = head;
			M_CDR(gensymed_symbol_2) = tail;
			inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
			M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
			gensymed_symbol = set_skip_list_entry(temp_3,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_2,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_19:
		    if (level < ab_loop_bind_)
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_20:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_21:
		    if ( !TRUEP(marked))
			goto end_loop_20;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_3,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_21;
		  end_loop_20:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_6;
		    goto next_loop_20;
		  end_loop_21:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_19;
		  end_loop_19:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_22:
			if (level < ab_loop_bind_)
			    goto end_loop_22;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_23:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_24:
			if ( !TRUEP(marked))
			    goto end_loop_23;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_24;
		      end_loop_23:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_7;
			goto next_loop_23;
		      end_loop_24:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_22;
		      end_loop_22:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			skip_list = CDR(global_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_25:
			if (level < ab_loop_bind_)
			    goto end_loop_25;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_26:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_27:
			if ( !TRUEP(marked))
			    goto end_loop_26;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_3,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_27;
		      end_loop_26:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_8;
			goto next_loop_26;
		      end_loop_27:
		      end_8:
			level = level - (SI_Long)1L;
			goto next_loop_25;
		      end_loop_25:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    temp = EQ(temp_1,
			    ISVREF(get_slot_description_of_class_description_function(Qjunction_block_class_for_class,
			    gensymed_symbol,Nil),(SI_Long)6L));
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp = TRUEP(Nil);
		    goto end_9;
		}
		goto next_loop_2;
	      end_loop_3:
		temp = TRUEP(T);
		goto end_9;
		temp = TRUEP(Qnil);
	      end_9:;
	      POP_SPECIAL();
	  }
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  if (instantiated_class_p(class_qm)) {
	      put_wacko_definition_on_kb_workspace(definition);
	      if ( !TRUEP(complete_definition_p(definition)))
		  update_frame_status(definition,Qincomplete,Nil);
	  }
	  else
	      delete_frame(definition);
      }
      else if ( !TRUEP(complete_definition_p(definition)))
	  update_frame_status(definition,Qincomplete,Nil);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* FIX-CAPABILITIES-OF-OLD-KBS */
Object fix_capabilities_of_old_kbs()
{
    Object kb_flags;
    Declare_special(1);

    x_note_fn_call(132,115);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qpotential_class_note;  /* potential-class-note */

/* REMOVE-UNIMPLEMENTED-SUPERIORS */
Object remove_unimplemented_superiors()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, def;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,116);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)41L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  def = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qclass_definition);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    def = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    delete_frame_note_if_any(Qpotential_class_note,def);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* PROVIDE-MESSAGE-BOARD-AFTER-LOADING-KB */
Object provide_message_board_after_loading_kb()
{
    Object gensymed_symbol, xa, ya, frame_serial_number_setf_arg;
    Object frame_serial_number_of_current_message_board_new_value;
    char temp;

    x_note_fn_call(132,117);
    if (Main_kb_being_read_qm) {
	temp =  !TRUEP(Current_message_board_qm);
	if (temp);
	else {
	    gensymed_symbol = ISVREF(Current_message_board_qm,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(Current_message_board_qm) ? 
		    EQ(ISVREF(Current_message_board_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(Frame_serial_number_of_current_message_board))
		temp = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(Frame_serial_number_of_current_message_board,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(Frame_serial_number_of_current_message_board);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(Frame_serial_number_of_current_message_board),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Current_message_board_qm = make_message_board();
	frame_serial_number_setf_arg = ISVREF(Current_message_board_qm,
		(SI_Long)3L);
	frame_serial_number_of_current_message_board_new_value = 
		(FIXNUMP(Frame_serial_number_of_current_message_board) ||  
		!TRUEP(Frame_serial_number_of_current_message_board)) && 
		(FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(Frame_serial_number_of_current_message_board,
		frame_serial_number_setf_arg);
	Frame_serial_number_of_current_message_board = 
		frame_serial_number_of_current_message_board_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qgeneric_simulation_formula;  /* generic-simulation-formula */

static Object Qredundant_generic_simulation_formulas;  /* redundant-generic-simulation-formulas */

/* REMOVE-REDUNDANT-SIMULATION-FORMULAS-NOTES */
Object remove_redundant_simulation_formulas_notes()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, formula;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,118);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)202L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  formula = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qgeneric_simulation_formula);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    formula = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    delete_frame_note_if_any(Qredundant_generic_simulation_formulas,
		    formula);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* NOTE-FRAME-WITH-COMPILATION-REMOVED */
Object note_frame_with_compilation_removed(frame)
    Object frame;
{
    x_note_fn_call(132,119);
    Launch_recompile_for_compilations_removed_in_this_kb_qm = T;
    return VALUES_1(Launch_recompile_for_compilations_removed_in_this_kb_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ui_client_interface_in_which_to_launch_recompilation_qm, Qui_client_interface_in_which_to_launch_recompilation_qm);

static Object string_constant_55;  /* "Once you save the KB in this version ~
				    *        of G2, recompilation will no longer happen automatically."
				    */

/* LAUNCH-RECOMPILATION-FOR-THIS-KB */
Object launch_recompilation_for_this_kb()
{
    x_note_fn_call(132,120);
    Workstation_in_which_to_launch_recompilation_qm = Nil;
    Launch_recompile_for_compilations_removed_in_this_kb_qm = Nil;
    return launch_compile_to_bring_kb_up_to_date(1,tformat_text_string(1,
	    string_constant_55));
}

static Object Qui_client_interface;  /* ui-client-interface */

/* RECOMPILE-IF-COMPILATIONS-WERE-REMOVED */
Object recompile_if_compilations_were_removed()
{
    Object temp, interface_qm, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(132,121);
    if (Launch_recompile_for_compilations_removed_in_this_kb_qm) {
	if (Servicing_workstation_qm) {
	    temp = Current_workstation;
	    if (temp);
	    else {
		temp = last(Workstations_in_service,_);
		temp = CAR(temp);
	    }
	    Workstation_in_which_to_launch_recompilation_qm = temp;
	}
	else {
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    if (SIMPLE_VECTOR_P(interface_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interface_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(interface_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(interface_qm,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qui_client_interface,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(interface_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    Ui_client_interface_in_which_to_launch_recompilation_qm = 
		    temp_1 ? interface_qm : Nil;
	    temp = last(Workstations_in_service,_);
	    Workstation_in_which_to_launch_recompilation_qm = CAR(temp);
	}
    }
    return VALUES_1(Nil);
}

/* IDENTIFY-ALL-PERMANENT-BLOCKS */
Object identify_all_permanent_blocks()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,122);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)212L)) {
	  identify_all_savable_kb_workspaces();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    temp = TRUEP(savable_block_p(block));
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Format_frame_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(block,Qframe_flags);
		svref_new_value = IFIX(ISVREF(block,(SI_Long)4L)) | 
			(SI_Long)1L;
		ISVREF(block,(SI_Long)4L) = FIX(svref_new_value);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* INSTALL-EXTERNAL-SIMULATION */
Object install_external_simulation()
{
    x_note_fn_call(132,123);
    install_external_simulation_1();
    return VALUES_1(Nil);
}

/* INSTALL-CONNECTION-POSTS-AFTER-LOADING */
Object install_connection_posts_after_loading()
{
    x_note_fn_call(132,124);
    install_connection_posts_after_loading_1();
    return VALUES_1(Nil);
}

/* COLLECT-UNREPROCESSED-ITEMS */
Object collect_unreprocessed_items(list_1)
    Object list_1;
{
    Object item, frame_serial_number, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, gensymed_symbol, xa;
    Object ya, temp_1;
    char temp;

    x_note_fn_call(132,125);
    item = Nil;
    frame_serial_number = Nil;
    ab_loop_list_ = list_1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    item = CAR(ab_loop_desetq_);
    frame_serial_number = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(item,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	ab_loopvar__2 = gensym_cons_1(item,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* RECLAIM-ITEM-AND-FSN-LIST */
Object reclaim_item_and_fsn_list(list_1)
    Object list_1;
{
    Object cons_1, ab_loop_list_, item, fsn;

    x_note_fn_call(132,126);
    cons_1 = Nil;
    ab_loop_list_ = list_1;
    item = Nil;
    fsn = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cons_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    item = CAR(cons_1);
    fsn = CDR(cons_1);
    reclaim_frame_serial_number(fsn);
    reclaim_gensym_cons_1(cons_1);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(list_1);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiling_incomplete_items_after_analyze_p, Qcompiling_incomplete_items_after_analyze_p);

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_procedures_to_warn_about_p, Qcollecting_procedures_to_warn_about_p);

DEFINE_VARIABLE_WITH_SYMBOL(Procedures_to_warn_about_p, Qprocedures_to_warn_about_p);

DEFINE_VARIABLE_WITH_SYMBOL(Add_as_item_referring_to_name_qm, Qadd_as_item_referring_to_name_qm);

static Object Qanalyze;            /* analyze */

static Object Qedit;               /* edit */

/* ANALYZE-COMPILED-ITEMS-AFTER-LOADING */
Object analyze_compiled_items_after_loading()
{
    Object collecting_warnings_p, collected_items_with_warnings_alist;
    Object operation_around_record_of_items_made_incomplete;
    Object recording_items_made_incomplete_qm;
    Object items_made_incomplete_were_recorded_qm, procedures_to_warn_about_p;
    Object collecting_procedures_to_warn_about_p;
    Object compiling_incomplete_items_after_analyze_p, items, item;
    Object gensym_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object add_as_item_referring_to_name_qm;
    Declare_special(8);

    x_note_fn_call(132,127);
    collecting_warnings_p = T;
    collected_items_with_warnings_alist = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Collected_items_with_warnings_alist,Qcollected_items_with_warnings_alist,collected_items_with_warnings_alist,
	    7);
      PUSH_SPECIAL_WITH_SYMBOL(Collecting_warnings_p,Qcollecting_warnings_p,collecting_warnings_p,
	      6);
	if (Some_module_is_clear_text_p) {
	    operation_around_record_of_items_made_incomplete = Qanalyze;
	    PUSH_SPECIAL_WITH_SYMBOL(Operation_around_record_of_items_made_incomplete,Qoperation_around_record_of_items_made_incomplete,operation_around_record_of_items_made_incomplete,
		    5);
	      recording_items_made_incomplete_qm = 
		      EQ(Operation_around_record_of_items_made_incomplete,
		      Qedit) ? ( !TRUEP(ISVREF(Current_edit_state,
		      (SI_Long)57L)) ? T : Nil) : T;
	      PUSH_SPECIAL_WITH_SYMBOL(Recording_items_made_incomplete_qm,Qrecording_items_made_incomplete_qm,recording_items_made_incomplete_qm,
		      4);
		items_made_incomplete_were_recorded_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Items_made_incomplete_were_recorded_qm,Qitems_made_incomplete_were_recorded_qm,items_made_incomplete_were_recorded_qm,
			3);
		  reclaim_items_made_incomplete_list();
		  procedures_to_warn_about_p = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Procedures_to_warn_about_p,Qprocedures_to_warn_about_p,procedures_to_warn_about_p,
			  2);
		    collecting_procedures_to_warn_about_p = T;
		    PUSH_SPECIAL_WITH_SYMBOL(Collecting_procedures_to_warn_about_p,Qcollecting_procedures_to_warn_about_p,collecting_procedures_to_warn_about_p,
			    1);
		      compiling_incomplete_items_after_analyze_p = T;
		      PUSH_SPECIAL_WITH_SYMBOL(Compiling_incomplete_items_after_analyze_p,Qcompiling_incomplete_items_after_analyze_p,compiling_incomplete_items_after_analyze_p,
			      0);
			analyze_compiled_items_after_loading_1();
		      POP_SPECIAL();
		      if (Items_made_incomplete_were_recorded_qm) {
			  items = 
				  collect_unreprocessed_items(Items_made_incomplete);
			  item = Nil;
			next_loop:
			  if ( !TRUEP(items))
			      goto end_loop;
			  gensym_pop_store = Nil;
			  cons_1 = items;
			  if (cons_1) {
			      gensym_pop_store = M_CAR(cons_1);
			      next_cons = M_CDR(cons_1);
			      inline_note_reclaim_cons(cons_1,Qab_gensym);
			      if (ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp = 
					  ISVREF(Available_gensym_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp) = cons_1;
				  temp = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp,svref_arg_2) = cons_1;
			      }
			      else {
				  temp = Available_gensym_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp,svref_arg_2) = cons_1;
				  temp = Available_gensym_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp,svref_arg_2) = cons_1;
			      }
			      M_CDR(cons_1) = Nil;
			  }
			  else
			      next_cons = Nil;
			  items = next_cons;
			  item = gensym_pop_store;
			  recompile_item_1(item);
			  goto next_loop;
			end_loop:;
		      }
		    POP_SPECIAL();
		    add_as_item_referring_to_name_qm = T;
		    PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
			    0);
		      items = 
			      collect_unreprocessed_items(Procedures_to_warn_about_p);
		      item = Nil;
		    next_loop_1:
		      if ( !TRUEP(items))
			  goto end_loop_1;
		      gensym_pop_store = Nil;
		      cons_1 = items;
		      if (cons_1) {
			  gensym_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qab_gensym);
			  if (ISVREF(Available_gensym_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_gensym_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp) = cons_1;
			      temp = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  else {
			      temp = Available_gensym_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			      temp = Available_gensym_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      items = next_cons;
		      item = gensym_pop_store;
		      post_analyzer_warning_note_if_necessary(item);
		      goto next_loop_1;
		    end_loop_1:;
		    POP_SPECIAL();
		    reclaim_item_and_fsn_list(Procedures_to_warn_about_p);
		  POP_SPECIAL();
		  reclaim_items_made_incomplete_list();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    analyze_compiled_items_after_loading_1();
	Collecting_warnings_p = Nil;
	post_collected_warnings(Collected_items_with_warnings_alist);
	reclaim_collected_warnings(Collected_items_with_warnings_alist);
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Rendezvous_successful_blocks_qm, Qrendezvous_successful_blocks_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Additional_related_blocks, Qadditional_related_blocks);

static Object Qrelation_instance_tree;  /* relation-instance-tree */

static Object Qrelation_instances;  /* relation-instances */

static Object Qone_to_one;         /* one-to-one */

static Object Qone_to_many;        /* one-to-many */

static Object Qmany_to_one;        /* many-to-one */

/* RENDEZVOUS-FRAME-DENOTATIONS-IN-RELATION-INSTANCES */
Object rendezvous_frame_denotations_in_relation_instances()
{
    Object relations_with_changed_slots_qm, reference_serial_number, block;
    Object ab_loop_list_, gensymed_symbol, xa, ya, relation_instances;
    Object current_pointer, following_pointer, relation_instance;
    Object relation_name_reference, relation_reference, relation_frame_qm;
    Object duplicate_relation_instance_qm;
    Object item_references_with_possible_duplicates, item_references;
    Object item_frames_qm, x2, temp_1, other_relation_instance;
    Object ab_loop_list__1, ab_loop_it_, list_to_return, reference;
    Object other_reference, ab_loop_list__2, leading_pointer, trailing_pointer;
    Object item_reference, item_frame, temp_2, secret_inverse_name;
    Object inverse_of_relation, relation_name, temp_3, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, relation;
    Object ab_less_than_branch_qm_, other_relation_name_reference;
    Object object_frames, ab_node_stack__1, ab_current_node__1;
    Object ab_skip_list_p__1, ab_next_node__1, ab_tail_node__1;
    Object ab_current_alist__1, ab_entry_cons__1, object_frame;
    Object other_instances, corresponding_relation_qm, skip_list, key_value;
    Object marked, pred, curr, succ, reference_1, entry_hash, the_block;
    Object blocks, type_of_relation, copied_relation_instances;
    Object copied_relation_instance, copied_object_frames, inverse_instance;
    Object block_relevant_relation_instance, relevant_object_frames, item;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(132,128);
    relations_with_changed_slots_qm = Nil;
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    block = Nil;
    ab_loop_list_ = Blocks_with_relation_instances_from_kb_read;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	relation_instances = ISVREF(block,(SI_Long)12L);
	if ( !TRUEP(relation_instances) || CONSP(relation_instances) &&  
		!EQ(CAR(relation_instances),Qrelation_instance_tree)) {
	    current_pointer = relation_instances;
	    following_pointer = Nil;
	    relation_instance = Nil;
	    relation_name_reference = Nil;
	    relation_reference = Nil;
	    relation_frame_qm = Nil;
	    duplicate_relation_instance_qm = Nil;
	    item_references_with_possible_duplicates = Nil;
	    item_references = Nil;
	    item_frames_qm = Nil;
	  next_loop_1:
	    if ( !TRUEP(current_pointer))
		goto end_loop_1;
	    relation_instance = M_CAR(current_pointer);
	    relation_name_reference = M_CAR(relation_instance);
	    relation_reference = M_CAR(M_CDR(relation_instance));
	    if (SIMPLE_VECTOR_P(relation_reference) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(relation_reference)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(relation_reference,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(relation_reference,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_1 = temp ? relation_reference : Nil;
	    if (temp_1);
	    else
		temp_1 = find_frame_for_denotation(2,relation_reference,
			Qblock);
	    relation_frame_qm = temp_1;
	    if (relation_frame_qm) {
		other_relation_instance = Nil;
		ab_loop_list__1 = ISVREF(block,(SI_Long)12L);
		ab_loop_it_ = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_2;
		other_relation_instance = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if (EQ(other_relation_instance,relation_instance))
		    goto end_loop_2;
		ab_loop_it_ = EQ(relation_name_reference,
			M_CAR(other_relation_instance)) ? 
			(EQ(relation_frame_qm,
			M_CAR(M_CDR(other_relation_instance))) ? T : Nil) :
			 Qnil;
		if (ab_loop_it_) {
		    duplicate_relation_instance_qm = ab_loop_it_;
		    goto end_1;
		}
		goto next_loop_2;
	      end_loop_2:
		duplicate_relation_instance_qm = Qnil;
	      end_1:;
	    }
	    else
		duplicate_relation_instance_qm = Nil;
	    item_references_with_possible_duplicates = CDDR(relation_instance);
	    list_to_return = Nil;
	    reference = Nil;
	    ab_loop_list__1 = item_references_with_possible_duplicates;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    reference = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(reference) != (SI_Long)0L) {
		other_reference = Nil;
		ab_loop_list__2 = list_to_return;
		ab_loop_it_ = Nil;
	      next_loop_4:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_4;
		other_reference = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		ab_loop_it_ = 
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(other_reference) 
			!= (SI_Long)0L ? string_eq_w(reference,
			other_reference) : Qnil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_2;
		}
		goto next_loop_4;
	      end_loop_4:
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else
		temp = TRUEP(memq_function(reference,list_to_return));
	    if ( !temp)
		list_to_return = nconc2(list_to_return,
			slot_value_cons_1(reference,Nil));
	    goto next_loop_3;
	  end_loop_3:
	    item_references = list_to_return;
	    goto end_3;
	    item_references = Qnil;
	  end_3:;
	    if (relation_frame_qm &&  !TRUEP(duplicate_relation_instance_qm)) {
		leading_pointer = item_references;
		trailing_pointer = Nil;
		item_reference = Nil;
		item_frame = Nil;
	      next_loop_5:
		if ( !TRUEP(leading_pointer))
		    goto end_loop_5;
		item_reference = M_CAR(leading_pointer);
		if (SIMPLE_VECTOR_P(item_reference) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_reference)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_reference,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_reference,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? item_reference : Nil;
		if (temp_1);
		else
		    temp_1 = SYMBOLP(item_reference) || 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_reference) 
			    != (SI_Long)0L ? find_frame_for_denotation(2,
			    item_reference,Qblock) : Qnil;
		item_frame = temp_1;
		if (item_frame) {
		    M_CAR(leading_pointer) = item_frame;
		    trailing_pointer = leading_pointer;
		    leading_pointer = CDR(trailing_pointer);
		}
		else if (trailing_pointer) {
		    temp_2 = CDR(leading_pointer);
		    M_CDR(trailing_pointer) = temp_2;
		    reclaim_slot_value_cons_1(leading_pointer);
		    leading_pointer = CDR(trailing_pointer);
		}
		else {
		    temp_1 = item_references;
		    item_references = CDR(item_references);
		    reclaim_slot_value_cons_1(temp_1);
		    leading_pointer = item_references;
		}
		goto next_loop_5;
	      end_loop_5:
		M_CDDR(relation_instance) = item_references;
		reclaim_slot_value_list_1(item_references_with_possible_duplicates);
		item_frames_qm = item_references;
		goto end_4;
		item_frames_qm = Qnil;
	      end_4:;
	    }
	    else
		item_frames_qm = Nil;
	    if (item_frames_qm) {
		temp_2 = M_CDR(relation_instance);
		M_CAR(temp_2) = relation_frame_qm;
		following_pointer = current_pointer;
		current_pointer = CDR(following_pointer);
		secret_inverse_name = ISVREF(relation_frame_qm,(SI_Long)26L);
		inverse_of_relation = ISVREF(relation_frame_qm,(SI_Long)23L);
		relation_name = ISVREF(relation_frame_qm,(SI_Long)22L);
		if ( !EQ(relation_name_reference,relation_name) &&  
			!EQ(relation_name_reference,inverse_of_relation) 
			&&  !EQ(relation_name_reference,secret_inverse_name)) {
		    if ( !TRUEP(memq_function(relation_frame_qm,
			    relations_with_changed_slots_qm)))
			relations_with_changed_slots_qm = 
				frame_cons_1(relation_frame_qm,
				relations_with_changed_slots_qm);
		}
		else if (EQ(relation_name_reference,secret_inverse_name) 
			&& inverse_of_relation)
		    M_CAR(relation_instance) = inverse_of_relation;
	    }
	    else {
		if (following_pointer) {
		    temp_2 = CDR(current_pointer);
		    M_CDR(following_pointer) = temp_2;
		    reclaim_slot_value_cons_1(current_pointer);
		    current_pointer = CDR(following_pointer);
		}
		else {
		    temp_1 = ISVREF(block,(SI_Long)12L);
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(block,Qrelation_instances);
		    temp_3 = ISVREF(block,(SI_Long)12L);
		    temp_2 = CDR(temp_3);
		    SVREF(block,FIX((SI_Long)12L)) = temp_2;
		    current_pointer = ISVREF(block,(SI_Long)12L);
		    reclaim_slot_value_cons_1(temp_1);
		}
		reclaim_slot_value_list_1(relation_instance);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	    if ( !TRUEP(relation_instances_empty_p(ISVREF(block,
		    (SI_Long)12L))))
		Rendezvous_successful_blocks_qm = frame_cons_1(block,
			Rendezvous_successful_blocks_qm);
	}
    }
    goto next_loop;
  end_loop:;
    reclaim_frame_serial_number(reference_serial_number);
    upgrade_relation_instances(Blocks_with_relation_instances_from_kb_read);
    block = Nil;
    ab_loop_list_ = Rendezvous_successful_blocks_qm;
    relation_instances = Nil;
  next_loop_6:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_6;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    relation_instances = ISVREF(block,(SI_Long)12L);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = relation_instances;
    ab_binary_tree_form_ = relation_instances;
    gensymed_symbol = CDR(relation_instances);
    if (CONSP(gensymed_symbol)) {
	temp_1 = M_CAR(gensymed_symbol);
	temp = SIMPLE_VECTOR_P(temp_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = M_CDR(gensymed_symbol);
	ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
    }
    else
	ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    relation_instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      relation = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = M_CDR(ab_binary_tree_form_);
    next_loop_7:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
		      (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_8:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_7;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_8;
	    end_loop_7:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_8;
      relation_instance = M_CDR(ab_entry_cons_);
      relation = ISVREF(relation_instance,(SI_Long)1L);
      if ( !TRUEP(memq_function(relation,relations_with_changed_slots_qm))) {
	  relation_name_reference = ISVREF(relation_instance,(SI_Long)0L);
	  relation_name = ISVREF(relation,(SI_Long)22L);
	  if ( !EQ(relation_name_reference,relation_name))
	      other_relation_name_reference = relation_name;
	  else if (ISVREF(relation,(SI_Long)25L))
	      other_relation_name_reference = relation_name_reference;
	  else {
	      other_relation_name_reference = ISVREF(relation,(SI_Long)23L);
	      if (other_relation_name_reference);
	      else
		  other_relation_name_reference = ISVREF(relation,
			  (SI_Long)26L);
	  }
	  object_frames = ISVREF(relation_instance,(SI_Long)2L);
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  ab_skip_list_form_ = object_frames;
	  ab_binary_tree_form_ = object_frames;
	  gensymed_symbol = CDR(object_frames);
	  if (CONSP(gensymed_symbol)) {
	      temp_1 = M_CAR(gensymed_symbol);
	      temp = SIMPLE_VECTOR_P(temp_1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      temp_1 = M_CDR(gensymed_symbol);
	      ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	  }
	  else
	      ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons__1 = Nil;
	  object_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    other_instances = Nil;
	    corresponding_relation_qm = Nil;
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = M_CDR(ab_binary_tree_form_);
	  next_loop_9:
	    if (ab_current_alist__1) {
		ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L));
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_entry_cons__1 = 
			    scope_cons(ISVREF(ab_current_node__1,
			    (SI_Long)2L),ISVREF(ab_current_node__1,
			    (SI_Long)3L));
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_10:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_9;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_10;
		  end_loop_9:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_10;
	    object_frame = M_CDR(ab_entry_cons__1);
	    other_instances = object_frame ? ISVREF(object_frame,
		    (SI_Long)12L) : Nil;
	    if (other_instances) {
		skip_list = CDR(other_instances);
		key_value = other_relation_name_reference;
		key_hash_value = 
			SXHASH_SYMBOL_1(other_relation_name_reference) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_11:
		if (level < ab_loop_bind_)
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_12:
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference_1);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? 
			T : Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_13:
		if ( !TRUEP(marked))
		    goto end_loop_12;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference_1);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? 
			T : Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_13;
	      end_loop_12:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_5;
		goto next_loop_12;
	      end_loop_13:
	      end_5:
		level = level - (SI_Long)1L;
		goto next_loop_11;
	      end_loop_11:;
		corresponding_relation_qm = IFIX(ISVREF(curr,(SI_Long)1L)) 
			== key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    else
		corresponding_relation_qm = Nil;
	    if (object_frame) {
		if (corresponding_relation_qm) {
		    the_block = block;
		    blocks = ISVREF(corresponding_relation_qm,(SI_Long)2L);
		    skip_list = CDR(blocks);
		    key_value = the_block;
		    key_hash_value = SXHASH_SYMBOL_1(the_block) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)7L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_14:
		    if (level < ab_loop_bind_)
			goto end_loop_14;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_15:
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_16:
		    if ( !TRUEP(marked))
			goto end_loop_15;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_16;
		  end_loop_15:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_6;
		    goto next_loop_15;
		  end_loop_16:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_14;
		  end_loop_14:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if ((temp ? TRUEP(ISVREF(relation,(SI_Long)25L)) : 
			TRUEP(Nil)) ?  !EQ(relation_name_reference,
			relation_name) : TRUEP(Nil)) {
		    if ( !TRUEP(memq_function(relation,
			    relations_with_changed_slots_qm)))
			relations_with_changed_slots_qm = 
				frame_cons_1(relation,
				relations_with_changed_slots_qm);
		}
		else {
		    if (corresponding_relation_qm) {
			the_block = block;
			blocks = ISVREF(corresponding_relation_qm,(SI_Long)2L);
			skip_list = CDR(blocks);
			key_value = the_block;
			key_hash_value = SXHASH_SYMBOL_1(the_block) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)7L;
			ab_loop_bind_ = bottom_level;
		      next_loop_17:
			if (level < ab_loop_bind_)
			    goto end_loop_17;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_18:
			reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference_1);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference_1) ? T : Nil;
			result = VALUES_2(temp_3,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_19:
			if ( !TRUEP(marked))
			    goto end_loop_18;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_3 = ATOMIC_REF_OBJECT(reference_1);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference_1) ? T : Nil;
			result = VALUES_2(temp_3,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_19;
		      end_loop_18:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_7;
			goto next_loop_18;
		      end_loop_19:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_17;
		      end_loop_17:;
			temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if ( !temp) {
			if (EQ(relation_name_reference,relation_name) && 
				ISVREF(relation,(SI_Long)25L)) {
			    if (other_instances) {
				gensymed_symbol = ISVREF(relation,
					(SI_Long)23L);
				if (gensymed_symbol);
				else
				    gensymed_symbol = ISVREF(relation,
					    (SI_Long)26L);
				skip_list = CDR(other_instances);
				key_value = gensymed_symbol;
				key_hash_value = 
					SXHASH_SYMBOL_1(gensymed_symbol) & 
					IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)7L;
				ab_loop_bind_ = bottom_level;
			      next_loop_20:
				if (level < ab_loop_bind_)
				    goto end_loop_20;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_21:
				reference_1 = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_3 = ATOMIC_REF_OBJECT(reference_1);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference_1) ? T :
					 Nil;
				result = VALUES_2(temp_3,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_22:
				if ( !TRUEP(marked))
				    goto end_loop_21;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference_1 = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_3 = ATOMIC_REF_OBJECT(reference_1);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference_1) ? T :
					 Nil;
				result = VALUES_2(temp_3,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_22;
			      end_loop_21:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_8;
				goto next_loop_21;
			      end_loop_22:
			      end_8:
				level = level - (SI_Long)1L;
				goto next_loop_20;
			      end_loop_20:;
				temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
					key_hash_value ? (EQ(key_value,
					ISVREF(curr,(SI_Long)2L)) ? 
					TRUEP(ISVREF(curr,(SI_Long)3L)) : 
					TRUEP(Nil)) : TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if ( !TRUEP(memq_function(relation,
				    relations_with_changed_slots_qm)))
				relations_with_changed_slots_qm = 
					frame_cons_1(relation,
					relations_with_changed_slots_qm);
			}
			else {
			    if (EQ(relation_name_reference,relation_name) 
				    &&  !TRUEP(ISVREF(relation,
					(SI_Long)25L))) {
				skip_list = CDR(other_instances);
				key_value = relation_name;
				key_hash_value = 
					SXHASH_SYMBOL_1(relation_name) & 
					IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)7L;
				ab_loop_bind_ = bottom_level;
			      next_loop_23:
				if (level < ab_loop_bind_)
				    goto end_loop_23;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_24:
				reference_1 = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_3 = ATOMIC_REF_OBJECT(reference_1);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference_1) ? T :
					 Nil;
				result = VALUES_2(temp_3,temp_1);
				MVS_2(result,succ,marked);
			      next_loop_25:
				if ( !TRUEP(marked))
				    goto end_loop_24;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference_1 = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_3 = ATOMIC_REF_OBJECT(reference_1);
				temp_1 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference_1) ? T :
					 Nil;
				result = VALUES_2(temp_3,temp_1);
				MVS_2(result,succ,marked);
				goto next_loop_25;
			      end_loop_24:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_9;
				goto next_loop_24;
			      end_loop_25:
			      end_9:
				level = level - (SI_Long)1L;
				goto next_loop_23;
			      end_loop_23:;
				temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
					key_hash_value ? (EQ(key_value,
					ISVREF(curr,(SI_Long)2L)) ? 
					TRUEP(ISVREF(curr,(SI_Long)3L)) : 
					TRUEP(Nil)) : TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				if ( !TRUEP(memq_function(relation,
					relations_with_changed_slots_qm)))
				    relations_with_changed_slots_qm = 
					    frame_cons_1(relation,
					    relations_with_changed_slots_qm);
			    }
			    else;
			}
		    }
		}
	    }
	    goto next_loop_9;
	  end_loop_10:;
	  POP_SPECIAL();
      }
      goto next_loop_7;
    end_loop_8:;
    POP_SPECIAL();
    goto next_loop_6;
  end_loop_6:;
    block = Nil;
    ab_loop_list_ = Rendezvous_successful_blocks_qm;
    relation_instances = Nil;
  next_loop_26:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_26;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    relation_instances = ISVREF(block,(SI_Long)12L);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_skip_list_form_ = relation_instances;
    ab_binary_tree_form_ = relation_instances;
    gensymed_symbol = CDR(relation_instances);
    if (CONSP(gensymed_symbol)) {
	temp_1 = M_CAR(gensymed_symbol);
	temp = SIMPLE_VECTOR_P(temp_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = M_CDR(gensymed_symbol);
	ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
    }
    else
	ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    relation_instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      relation = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = M_CDR(ab_binary_tree_form_);
    next_loop_27:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
		      (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_28:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_27;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_28;
	    end_loop_27:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_28;
      relation_instance = M_CDR(ab_entry_cons_);
      relation = ISVREF(relation_instance,(SI_Long)1L);
      if ( !TRUEP(memq_function(relation,relations_with_changed_slots_qm))) {
	  relation_name_reference = ISVREF(relation_instance,(SI_Long)0L);
	  relation_name = ISVREF(relation,(SI_Long)22L);
	  type_of_relation = ISVREF(relation,(SI_Long)24L);
	  object_frames = ISVREF(relation_instance,(SI_Long)2L);
	  if ((EQ(type_of_relation,Qone_to_one) || EQ(type_of_relation,
		  Qone_to_many) && EQ(relation_name_reference,
		  relation_name) || EQ(type_of_relation,Qmany_to_one) &&  
		  !EQ(relation_name_reference,relation_name)) && 
		  more_than_one_related_item_p(object_frames)) {
	      if ( !TRUEP(memq_function(relation,
		      relations_with_changed_slots_qm)))
		  relations_with_changed_slots_qm = frame_cons_1(relation,
			  relations_with_changed_slots_qm);
	  }
      }
      goto next_loop_27;
    end_loop_28:;
    POP_SPECIAL();
    goto next_loop_26;
  end_loop_26:;
    block = Nil;
    ab_loop_list_ = Rendezvous_successful_blocks_qm;
    relation_instances = Nil;
  next_loop_29:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_29;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
	copied_relation_instances = 
		copy_list_of_relation_instances(relation_instances);
	copied_relation_instance = Nil;
	ab_loop_list__1 = copied_relation_instances;
	relation_name_reference = Nil;
	relation = Nil;
	relation_name = Nil;
	other_relation_name_reference = Nil;
	copied_object_frames = Nil;
	type_of_relation = Nil;
      next_loop_30:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_30;
	copied_relation_instance = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	relation_name_reference = M_CAR(copied_relation_instance);
	relation = M_CAR(M_CDR(copied_relation_instance));
	relation_name = ISVREF(relation,(SI_Long)22L);
	if ( !EQ(relation_name_reference,ISVREF(relation,(SI_Long)22L)))
	    other_relation_name_reference = ISVREF(relation,(SI_Long)22L);
	else if (ISVREF(relation,(SI_Long)25L))
	    other_relation_name_reference = relation_name_reference;
	else {
	    temp_1 = ISVREF(relation,(SI_Long)23L);
	    if (temp_1);
	    else
		temp_1 = ISVREF(relation,(SI_Long)26L);
	    other_relation_name_reference = temp_1;
	}
	copied_object_frames = CDDR(copied_relation_instance);
	type_of_relation = ISVREF(relation,(SI_Long)24L);
	if ( !TRUEP(memq_function(relation,relations_with_changed_slots_qm))) {
	    object_frame = Nil;
	    ab_loop_list__2 = copied_object_frames;
	    other_instances = Nil;
	    corresponding_relation_qm = Nil;
	  next_loop_31:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_31;
	    object_frame = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    other_instances = object_frame ? ISVREF(object_frame,
		    (SI_Long)12L) : Nil;
	    if (other_instances) {
		skip_list = CDR(other_instances);
		key_value = other_relation_name_reference;
		key_hash_value = 
			SXHASH_SYMBOL_1(other_relation_name_reference) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)7L;
		ab_loop_bind_ = bottom_level;
	      next_loop_32:
		if (level < ab_loop_bind_)
		    goto end_loop_32;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_33:
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference_1);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? 
			T : Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_34:
		if ( !TRUEP(marked))
		    goto end_loop_33;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference_1);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? 
			T : Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_34;
	      end_loop_33:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_33;
	      end_loop_34:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_32;
	      end_loop_32:;
		corresponding_relation_qm = IFIX(ISVREF(curr,(SI_Long)1L)) 
			== key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    else
		corresponding_relation_qm = Nil;
	    if ((EQ(type_of_relation,Qone_to_one) || EQ(type_of_relation,
		    Qone_to_many) &&  !EQ(relation_name_reference,
		    relation_name) || EQ(type_of_relation,Qmany_to_one) && 
		    EQ(relation_name_reference,relation_name)) && 
		    corresponding_relation_qm) {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = ISVREF(corresponding_relation_qm,
			(SI_Long)2L);
		ab_binary_tree_form_ = ISVREF(corresponding_relation_qm,
			(SI_Long)2L);
		temp_1 = ISVREF(corresponding_relation_qm,(SI_Long)2L);
		gensymed_symbol = CDR(temp_1);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		inverse_instance = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loop_it_ = Nil;
		  if (ab_skip_list_p_) {
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			      (SI_Long)0L),(SI_Long)0L));
		      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		  }
		  else
		      ab_next_node_ = M_CDR(ab_binary_tree_form_);
		next_loop_35:
		  if (ab_current_alist_) {
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
		  else if (ab_skip_list_p_) {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_next_node_ = 
				  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
				  (SI_Long)0L),(SI_Long)0L));
			  if (EQ(ab_next_node_,ab_tail_node_))
			      ab_next_node_ = Nil;
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
				  (SI_Long)2L),ISVREF(ab_current_node_,
				  (SI_Long)3L));
		      }
		      else
			  ab_current_node_ = Nil;
		  }
		  else {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_less_than_branch_qm_ = Nil;
			next_loop_36:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_35;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_36;
			end_loop_35:;
		      }
		      else if (ab_node_stack_) {
			  ab_next_node_ = ab_node_stack_;
			  ab_current_node_ = M_CAR(ab_node_stack_);
			  ab_node_stack_ = M_CDR(ab_node_stack_);
		      }
		      else
			  ab_current_node_ = Nil;
		      if (ab_current_node_) {
			  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_36;
		  inverse_instance = M_CDR(ab_entry_cons_);
		  ab_loop_it_ =  !EQ(inverse_instance,block) ? T : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_11;
		  }
		  goto next_loop_35;
		end_loop_36:
		  temp = TRUEP(Qnil);
		end_11:;
		POP_SPECIAL();
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if ( !TRUEP(memq_function(relation,
			relations_with_changed_slots_qm)))
		    relations_with_changed_slots_qm = 
			    frame_cons_1(relation,
			    relations_with_changed_slots_qm);
	    }
	    else {
		if (corresponding_relation_qm) {
		    the_block = block;
		    blocks = ISVREF(corresponding_relation_qm,(SI_Long)2L);
		    skip_list = CDR(blocks);
		    key_value = the_block;
		    key_hash_value = SXHASH_SYMBOL_1(the_block) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)7L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_37:
		    if (level < ab_loop_bind_)
			goto end_loop_37;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_38:
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_39:
		    if ( !TRUEP(marked))
			goto end_loop_38;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_39;
		  end_loop_38:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_12;
		    goto next_loop_38;
		  end_loop_39:
		  end_12:
		    level = level - (SI_Long)1L;
		    goto next_loop_37;
		  end_loop_37:;
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp) {
		    if ( !TRUEP(other_instances))
			Additional_related_blocks = 
				frame_cons_1(object_frame,
				Additional_related_blocks);
		    skip_list = CDR(relation_instances);
		    key_value = relation_name_reference;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(relation_name_reference) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)7L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_40:
		    if (level < ab_loop_bind_)
			goto end_loop_40;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_41:
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_42:
		    if ( !TRUEP(marked))
			goto end_loop_41;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference_1 = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_3 = ATOMIC_REF_OBJECT(reference_1);
		    temp_1 = (SI_Long)355L == 
			    ATOMIC_REF_STAMP(reference_1) ? T : Nil;
		    result = VALUES_2(temp_3,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_42;
		  end_loop_41:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_13;
		    goto next_loop_41;
		  end_loop_42:
		  end_13:
		    level = level - (SI_Long)1L;
		    goto next_loop_40;
		  end_loop_40:;
		    block_relevant_relation_instance = IFIX(ISVREF(curr,
			    (SI_Long)1L)) == key_hash_value ? 
			    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		    relevant_object_frames = 
			    ISVREF(block_relevant_relation_instance,
			    (SI_Long)2L);
		    if (more_than_one_related_item_p(relevant_object_frames)) {
			gensymed_symbol = object_frame;
			set_skip_list_entry(relevant_object_frames,
				FIX((SI_Long)7L),Qeq,Nil,T,gensymed_symbol,
				FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum)),Nil);
			temp_1 = object_frame;
			delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,
				relevant_object_frames,FIX((SI_Long)7L),
				FIX(SXHASH_SYMBOL_1(object_frame) & 
				IFIX(Most_positive_fixnum)));
		    }
		    else {
			gensymed_symbol = object_frame;
			set_skip_list_entry(relevant_object_frames,
				FIX((SI_Long)7L),Qeq,Nil,T,gensymed_symbol,
				FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum)),Nil);
			temp_1 = object_frame;
			delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,
				relevant_object_frames,FIX((SI_Long)7L),
				FIX(SXHASH_SYMBOL_1(object_frame) & 
				IFIX(Most_positive_fixnum)));
			temp =  !TRUEP(relevant_object_frames);
			if (temp);
			else {
			    gensymed_symbol = CDR(relevant_object_frames);
			    if (CONSP(gensymed_symbol)) {
				temp_1 = M_CAR(gensymed_symbol);
				temp = SIMPLE_VECTOR_P(temp_1);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				temp_1 = M_CDR(gensymed_symbol);
				temp = SIMPLE_VECTOR_P(temp_1);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				gensymed_symbol = 
					M_CDR(relevant_object_frames);
				temp_1 = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
					(SI_Long)0L),(SI_Long)0L));
				temp = EQ(temp_1,M_CDR(gensymed_symbol));
			    }
			    else
				temp =  !TRUEP(M_CDR(relevant_object_frames));
			    if (temp);
			    else {
				scope_conses = Scope_conses;
				ab_node_stack_ = Nil;
				ab_current_node_ = Nil;
				ab_skip_list_form_ = relevant_object_frames;
				ab_binary_tree_form_ = relevant_object_frames;
				gensymed_symbol = CDR(relevant_object_frames);
				if (CONSP(gensymed_symbol)) {
				    temp_1 = M_CAR(gensymed_symbol);
				    temp = SIMPLE_VECTOR_P(temp_1);
				}
				else
				    temp = TRUEP(Nil);
				if (temp) {
				    temp_1 = M_CDR(gensymed_symbol);
				    ab_skip_list_p_ = 
					    SIMPLE_VECTOR_P(temp_1) ? T : Nil;
				}
				else
				    ab_skip_list_p_ = Nil;
				ab_next_node_ = Nil;
				ab_tail_node_ = Nil;
				ab_current_alist_ = Nil;
				ab_entry_cons_ = Nil;
				item = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					0);
				  if (ab_skip_list_p_) {
				      ab_next_node_ = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
					      (SI_Long)0L),(SI_Long)0L));
				      ab_tail_node_ = 
					      M_CDR(M_CDR(ab_skip_list_form_));
				      if (EQ(ab_next_node_,ab_tail_node_))
					  ab_next_node_ = Nil;
				  }
				  else
				      ab_next_node_ = 
					      M_CDR(ab_binary_tree_form_);
				next_loop_43:
				  if (ab_current_alist_) {
				      ab_entry_cons_ = 
					      M_CAR(ab_current_alist_);
				      ab_current_alist_ = 
					      M_CDR(ab_current_alist_);
				  }
				  else if (ab_skip_list_p_) {
				      if (ab_next_node_) {
					  ab_current_node_ = ab_next_node_;
					  ab_next_node_ = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
						  (SI_Long)0L),(SI_Long)0L));
					  if (EQ(ab_next_node_,ab_tail_node_))
					      ab_next_node_ = Nil;
					  ab_entry_cons_ = 
						  scope_cons(ISVREF(ab_current_node_,
						  (SI_Long)2L),
						  ISVREF(ab_current_node_,
						  (SI_Long)3L));
				      }
				      else
					  ab_current_node_ = Nil;
				  }
				  else {
				      if (ab_next_node_) {
					  ab_current_node_ = ab_next_node_;
					  ab_less_than_branch_qm_ = Nil;
					next_loop_44:
					  ab_less_than_branch_qm_ = 
						  ISVREF(ab_current_node_,
						  (SI_Long)1L);
					  if ( !TRUEP(ab_less_than_branch_qm_))
					      goto end_loop_43;
					  ab_node_stack_ = 
						  scope_cons(ab_current_node_,
						  ab_node_stack_);
					  ab_current_node_ = 
						  ab_less_than_branch_qm_;
					  goto next_loop_44;
					end_loop_43:;
				      }
				      else if (ab_node_stack_) {
					  ab_next_node_ = ab_node_stack_;
					  ab_current_node_ = 
						  M_CAR(ab_node_stack_);
					  ab_node_stack_ = 
						  M_CDR(ab_node_stack_);
				      }
				      else
					  ab_current_node_ = Nil;
				      if (ab_current_node_) {
					  ab_next_node_ = 
						  ISVREF(ab_current_node_,
						  (SI_Long)2L);
					  ab_current_alist_ = 
						  ISVREF(ab_current_node_,
						  (SI_Long)3L);
					  ab_entry_cons_ = 
						  M_CAR(ab_current_alist_);
					  ab_current_alist_ = 
						  M_CDR(ab_current_alist_);
				      }
				  }
				  if ( !TRUEP(ab_current_node_))
				      goto end_loop_44;
				  item = M_CDR(ab_entry_cons_);
				  if (item) {
				      temp = TRUEP(Nil);
				      goto end_14;
				  }
				  goto next_loop_43;
				end_loop_44:
				  temp = TRUEP(T);
				  goto end_14;
				  temp = TRUEP(Qnil);
				end_14:;
				POP_SPECIAL();
			    }
			}
			if (temp) {
			    gensymed_symbol = relation_name_reference;
			    temp_1 = relation_instances;
			    set_skip_list_entry(temp_1,FIX((SI_Long)7L),
				    Qeq,Nil,T,gensymed_symbol,
				    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum)),Nil);
			    temp_1 = relation_name_reference;
			    temp_3 = relation_instances;
			    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
				    temp_1,temp_3,FIX((SI_Long)7L),
				    FIX(SXHASH_SYMBOL_1(relation_name_reference) 
				    & IFIX(Most_positive_fixnum)));
			    reclaim_relation_instance(block_relevant_relation_instance);
			}
		    }
		    if (EQ(relation_name,relation_name_reference))
			add_to_relation(relation_name_reference,
				object_frame,block,T,Nil,Nil);
		    else
			add_to_relation(other_relation_name_reference,
				block,object_frame,T,Nil,Nil);
		}
	    }
	    goto next_loop_31;
	  end_loop_31:;
	}
	goto next_loop_30;
      end_loop_30:
	reclaim_slot_value(copied_relation_instances);
    }
    goto next_loop_29;
  end_loop_29:;
    if (relations_with_changed_slots_qm) {
	remove_relations(relations_with_changed_slots_qm,
		Rendezvous_successful_blocks_qm);
	remove_relations(relations_with_changed_slots_qm,
		Additional_related_blocks);
    }
    reclaim_frame_list_1(relations_with_changed_slots_qm);
    temp_1 = copy_frame_serial_number(Current_frame_serial_number);
    Rendezvous_successful_blocks_qm = frame_cons_1(temp_1,
	    Rendezvous_successful_blocks_qm);
    temp_1 = copy_frame_serial_number(Current_frame_serial_number);
    Additional_related_blocks = frame_cons_1(temp_1,Additional_related_blocks);
    reclaim_gensym_list_1(Blocks_with_relation_instances_from_kb_read);
    Blocks_with_relation_instances_from_kb_read = Nil;
    return VALUES_1(Nil);
}

/* DELETE-TYPE-VIOLATING-RELATION-INSTANCES */
Object delete_type_violating_relation_instances()
{
    x_note_fn_call(132,129);
    delete_type_violating_relation_instances_1(Rendezvous_successful_blocks_qm);
    Rendezvous_successful_blocks_qm = Nil;
    delete_type_violating_relation_instances_1(Additional_related_blocks);
    Additional_related_blocks = Nil;
    return VALUES_1(Nil);
}

/* DELETE-TYPE-VIOLATING-RELATION-INSTANCES-1 */
Object delete_type_violating_relation_instances_1(blocks)
    Object blocks;
{
    Object fsn, block, ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(132,130);
    fsn = CAR(blocks);
    block = Nil;
    ab_loop_list_ = CDR(blocks);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	if (block_relation_instances_violate_class_type_p(block))
	    remove_invalid_relation_instances(block);
    }
    goto next_loop;
  end_loop:;
    reclaim_frame_serial_number(fsn);
    return reclaim_frame_list_1(blocks);
}

/* REMOVE-RELATIONS */
Object remove_relations(relations,blocks)
    Object relations, blocks;
{
    Object block, ab_loop_list_, relation_instances, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance, relation_name, relation, deleted_names;
    Object ab_less_than_branch_qm_, name, ab_loop_list__1, temp_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(132,131);
    block = Nil;
    ab_loop_list_ = blocks;
    relation_instances = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    relation_instances = ISVREF(block,(SI_Long)12L);
    if (relation_instances) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_skip_list_form_ = relation_instances;
	ab_binary_tree_form_ = relation_instances;
	gensymed_symbol = CDR(relation_instances);
	if (CONSP(gensymed_symbol)) {
	    temp = M_CAR(gensymed_symbol);
	    temp_1 = SIMPLE_VECTOR_P(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = M_CDR(gensymed_symbol);
	    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	}
	else
	    ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	relation_instance = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  relation_name = Nil;
	  relation = Nil;
	  deleted_names = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = M_CDR(ab_binary_tree_form_);
	next_loop_1:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_1;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
		end_loop_1:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  relation_instance = M_CDR(ab_entry_cons_);
	  relation_name = ISVREF(relation_instance,(SI_Long)0L);
	  relation = ISVREF(relation_instance,(SI_Long)1L);
	  if (memq_function(relation,relations)) {
	      gensymed_symbol = relation_name;
	      temp = relation_instances;
	      set_skip_list_entry(temp,FIX((SI_Long)7L),Qeq,Nil,T,
		      gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
		      & IFIX(Most_positive_fixnum)),Nil);
	      deleted_names = slot_value_cons_1(relation_name,deleted_names);
	      reclaim_relation_instance(relation_instance);
	  }
	  goto next_loop_1;
	end_loop_2:
	  if (deleted_names) {
	      name = Nil;
	      ab_loop_list__1 = deleted_names;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_3;
	      name = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      temp = name;
	      temp_2 = relation_instances;
	      delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,temp_2,
		      FIX((SI_Long)7L),FIX(SXHASH_SYMBOL_1(name) & 
		      IFIX(Most_positive_fixnum)));
	      goto next_loop_3;
	    end_loop_3:;
	      reclaim_slot_value_list_1(deleted_names);
	  }
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RENDEZVOUS-FRAMES-AND-DENOTATIONS-IN-AGGREGATE-EVALUATION-VALUES */
Object rendezvous_frames_and_denotations_in_aggregate_evaluation_values()
{
    Object info, ab_loop_list_, frame, frame_serial_number, slot_descriptions;
    Object temp, gensymed_symbol, xa, ya, slot_description, ab_loop_list__1;
    Object slot_value;
    char temp_1;

    x_note_fn_call(132,132);
    info = Nil;
    ab_loop_list_ = Frames_for_rendezvous_in_aggregate_values_qm;
    frame = Nil;
    frame_serial_number = Nil;
    slot_descriptions = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    frame = CAR(info);
    temp = CDR(info);
    frame_serial_number = CAR(temp);
    temp = CDR(info);
    temp = CDR(temp);
    slot_descriptions = CAR(temp);
    gensymed_symbol = ISVREF(frame,(SI_Long)3L);
    temp_1 = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp_1);
    else if (FIXNUMP(frame_serial_number))
	temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp_1 = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp_1 = FIXNUM_LT(xa,ya);
	if (temp_1);
	else
	    temp_1 = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp_1) {
	slot_description = Nil;
	ab_loop_list__1 = slot_descriptions;
	slot_value = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	slot_description = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	slot_value = get_slot_description_value(frame,slot_description);
	if (aggregate_evaluation_value_p(slot_value))
	    replace_frame_denotations_in_aggregate_evaluation_value(slot_value,
		    frame_serial_number);
	goto next_loop_1;
      end_loop_1:;
    }
    M_SECOND(info) = Nil;
    reclaim_frame_serial_number(frame_serial_number);
    goto next_loop;
  end_loop:;
    reclaim_gensym_tree_1(Frames_for_rendezvous_in_aggregate_values_qm);
    Frames_for_rendezvous_in_aggregate_values_qm = Nil;
    return VALUES_1(Nil);
}

/* REPLACE-FRAME-DENOTATIONS-IN-AGGREGATE-EVALUATION-VALUE */
Object replace_frame_denotations_in_aggregate_evaluation_value(evaluation_value,
	    frame_serial_number)
    Object evaluation_value, frame_serial_number;
{
    Object managed_array, managed_array_length, element, denotation;
    Object item_or_value, x2, temp_1, svref_new_value, thing, gensymed_symbol;
    Object xa, ya, temp_2, block_denotation, corresponding_frame_qm;
    SI_Long index_1, ab_loop_bind_, svref_arg_2;
    char temp;

    x_note_fn_call(132,133);
    managed_array = evaluation_value_value(evaluation_value);
    managed_array_length = ISVREF(managed_array,(SI_Long)1L);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qsequence)) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(managed_array_length);
	element = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	element = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (CONSP(element) && EQ(M_CAR(element),Qframe_denotation)) {
	    denotation = M_CAR(M_CDR(element));
	    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		item_or_value = find_frame_for_denotation(2,denotation,Qblock);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		ISVREF(managed_array,svref_arg_2) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		item_or_value = find_frame_for_denotation(2,denotation,Qblock);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		svref_new_value = temp ? 
			get_reference_to_item(item_or_value) : item_or_value;
		ISVREF(temp_1,svref_arg_2) = svref_new_value;
	    }
	    reclaim_slot_value_list_1(element);
	}
	else {
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L) {
		temp = EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector);
		if (temp);
		else {
		    thing = ISVREF(element,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = ISVREF(element,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(element) ? EQ(ISVREF(element,
			(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(frame_serial_number))
		    temp = FIXNUMP(gensymed_symbol) ? 
			    FIXNUM_LT(frame_serial_number,gensymed_symbol) 
			    : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(frame_serial_number);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(frame_serial_number),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp) {
		    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(managed_array,svref_arg_2) = Nil;
		    }
		    else {
			temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = Nil;
		    }
		}
		else if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    item_or_value = element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(managed_array,svref_arg_2) = temp_1;
		}
		else {
		    temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    item_or_value = element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    svref_new_value = temp ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(temp_1,svref_arg_2) = svref_new_value;
		}
	    }
	    else if (CONSP(element) && EQ(M_CDR(element),Qsequence) || 
		    CONSP(element) && EQ(M_CDR(element),Qab_structure))
		replace_frame_denotations_in_aggregate_evaluation_value(element,
			frame_serial_number);
	    else;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_2 = Qnil;
    }
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qab_structure)) {
	index_1 = (SI_Long)1L + (SI_Long)1L;
	ab_loop_bind_ = IFIX(managed_array_length);
	element = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	element = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (CONSP(element) && EQ(M_CAR(element),Qframe_denotation)) {
	    block_denotation = M_CAR(M_CDR(element));
	    corresponding_frame_qm = find_frame_for_denotation(2,
		    block_denotation,Qblock);
	    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		item_or_value = corresponding_frame_qm;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		ISVREF(managed_array,svref_arg_2) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		item_or_value = corresponding_frame_qm;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		svref_new_value = temp ? 
			get_reference_to_item(item_or_value) : item_or_value;
		ISVREF(temp_1,svref_arg_2) = svref_new_value;
	    }
	    reclaim_slot_value_list_1(element);
	}
	else {
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L) {
		temp = EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector);
		if (temp);
		else {
		    thing = ISVREF(element,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = ISVREF(element,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(element) ? EQ(ISVREF(element,
			(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(frame_serial_number))
		    temp = FIXNUMP(gensymed_symbol) ? 
			    FIXNUM_LT(frame_serial_number,gensymed_symbol) 
			    : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(frame_serial_number);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(frame_serial_number),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp) {
		    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(managed_array,svref_arg_2) = Nil;
		    }
		    else {
			temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = Nil;
		    }
		}
		else if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    item_or_value = element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(managed_array,svref_arg_2) = temp_1;
		}
		else {
		    temp_1 = ISVREF(managed_array,(index_1 >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    item_or_value = element;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    svref_new_value = temp ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    ISVREF(temp_1,svref_arg_2) = svref_new_value;
		}
	    }
	    else if (CONSP(element) && EQ(M_CDR(element),Qsequence) || 
		    CONSP(element) && EQ(M_CDR(element),Qab_structure))
		replace_frame_denotations_in_aggregate_evaluation_value(element,
			frame_serial_number);
	    else;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = Qnil;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* FIX-MODULE-RELATED-FRAME-NOTES-AFTER-LOADING */
Object fix_module_related_frame_notes_after_loading()
{
    x_note_fn_call(132,134);
    update_module_related_frame_notes_for_all_workspaces(0);
    return VALUES_1(Nil);
}

/* ASSURE-ALL-CHARTS-HAVE-STYLE */
Object assure_all_charts_have_style()
{
    x_note_fn_call(132,135);
    assure_all_charts_are_modern_1();
    return VALUES_1(Nil);
}

/* ENSURE-CONNECTIONS-HAVE-FRAMES-IF-NECESSARY */
Object ensure_connections_have_frames_if_necessary()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection_structure;
    Object connection_frame_or_class, temp_1, ab_less_than_branch_qm_;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(132,136);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,2);
      if ( !(IFIX(Kb_flags) >= (SI_Long)222L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol;
	    ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_connection_ = Nil;
	    ab_connection_item_ = Nil;
	    connection_structure = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      connection_frame_or_class = Nil;
	      gensymed_symbol = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol)) {
		  temp_1 = M_CAR(gensymed_symbol);
		  temp = SIMPLE_VECTOR_P(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp_1 = M_CDR(gensymed_symbol);
		  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	      }
	      else
		  ab_skip_list_p_ = Nil;
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = CDR(ab_skip_list_form_);
	    next_loop_2:
	    next_loop_3:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_connection_item_ = ISVREF(ab_current_node_,
			      (SI_Long)3L);
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
		    end_loop_2:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_)
		  goto end_1;
	      goto next_loop_3;
	    end_loop_3:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      connection_structure = ab_connection_;
	      connection_frame_or_class = ISVREF(connection_structure,
		      (SI_Long)1L);
	      if (SYMBOLP(connection_frame_or_class)) {
		  skip_list = CDR(Symbol_properties_table);
		  key_value = connection_frame_or_class;
		  key_hash_value = 
			  SXHASH_SYMBOL_1(connection_frame_or_class) & 
			  IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)31L;
		  ab_loop_bind_ = bottom_level;
		next_loop_5:
		  if (level < ab_loop_bind_)
		      goto end_loop_5;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_6:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_7:
		  if ( !TRUEP(marked))
		      goto end_loop_6;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_7;
		end_loop_6:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_2;
		  goto next_loop_6;
		end_loop_7:
		end_2:
		  level = level - (SI_Long)1L;
		  goto next_loop_5;
		end_loop_5:;
		  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if ( !TRUEP(gensymed_symbol)) {
		      gensymed_symbol = connection_frame_or_class;
		      temp_2 = Symbol_properties_table;
		      temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			      IFIX(Most_positive_fixnum));
		      tail = 
			      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			      Nil);
		      head = 
			      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			      tail);
		      new_cons = ISVREF(Available_lookup_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  svref_arg_1 = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      svref_arg_1 = 
				      Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(svref_arg_1,svref_arg_2) = Nil;
			  }
			  gensymed_symbol_1 = new_cons;
		      }
		      else
			  gensymed_symbol_1 = Nil;
		      if ( !TRUEP(gensymed_symbol_1))
			  gensymed_symbol_1 = replenish_lookup_cons_pool();
		      M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		      new_cons = ISVREF(Available_lookup_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  svref_arg_1 = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      svref_arg_1 = 
				      Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(svref_arg_1,svref_arg_2) = Nil;
			  }
			  gensymed_symbol_2 = new_cons;
		      }
		      else
			  gensymed_symbol_2 = Nil;
		      if ( !TRUEP(gensymed_symbol_2))
			  gensymed_symbol_2 = replenish_lookup_cons_pool();
		      M_CAR(gensymed_symbol_2) = head;
		      M_CDR(gensymed_symbol_2) = tail;
		      inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		      M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		      inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		      gensymed_symbol = set_skip_list_entry(temp_2,
			      FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			      temp_1,gensymed_symbol_1);
		  }
		  global_properties = gensymed_symbol;
		  skip_list = CDR(global_properties);
		  key_value = Current_kb_specific_property_list_property_name;
		  key_hash_value = 
			  SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			  & IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)31L;
		  ab_loop_bind_ = bottom_level;
		next_loop_8:
		  if (level < ab_loop_bind_)
		      goto end_loop_8;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_9:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_10:
		  if ( !TRUEP(marked))
		      goto end_loop_9;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_10;
		end_loop_9:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_3;
		  goto next_loop_9;
		end_loop_10:
		end_3:
		  level = level - (SI_Long)1L;
		  goto next_loop_8;
		end_loop_8:;
		  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (kb_properties);
		  else
		      kb_properties = Nil;
		  if (kb_properties) {
		      skip_list = CDR(kb_properties);
		      key_value = Class_description_gkbprop;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_11:
		      if (level < ab_loop_bind_)
			  goto end_loop_11;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_12:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_13:
		      if ( !TRUEP(marked))
			  goto end_loop_12;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_13;
		    end_loop_12:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_4;
		      goto next_loop_12;
		    end_loop_13:
		    end_4:
		      level = level - (SI_Long)1L;
		      goto next_loop_11;
		    end_loop_11:;
		      kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
		      if (kb_specific_value);
		      else
			  kb_specific_value = No_specific_property_value;
		  }
		  else
		      kb_specific_value = No_specific_property_value;
		  if ( !EQ(kb_specific_value,No_specific_property_value))
		      resulting_value = kb_specific_value;
		  else {
		      skip_list = CDR(global_properties);
		      key_value = Class_description_gkbprop;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_14:
		      if (level < ab_loop_bind_)
			  goto end_loop_14;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_15:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_16:
		      if ( !TRUEP(marked))
			  goto end_loop_15;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_16;
		    end_loop_15:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_5;
		      goto next_loop_15;
		    end_loop_16:
		    end_5:
		      level = level - (SI_Long)1L;
		      goto next_loop_14;
		    end_loop_14:;
		      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (resulting_value);
		      else
			  resulting_value = Nil;
		  }
		  temp = TRUEP(resulting_value);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ? 
		      TRUEP(always_instantiate_connection_frame_for_this_class_qm(connection_frame_or_class)) 
		      : TRUEP(Nil))
		  make_new_connection_frame_for_connection(connection_structure,
			  connection_frame_or_class);
	      goto next_loop_2;
	    end_loop_4:;
	    POP_SPECIAL();
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

/* ELIMINATE-PROCEDURE-INVOCATION-FRAME-NOTES */
Object eliminate_procedure_invocation_frame_notes()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,137);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)233L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(block,(SI_Long)8L))
		delete_all_frame_notes_for_component_particular(list_constant_14,
			block);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qg2_window;          /* g2-window */

static Object Qg2_user_mode;       /* g2-user-mode */

/* FIX-POSSIBLE-NON-SYMBOLS-IN-G2-USER-MODE */
Object fix_possible_non_symbols_in_g2_user_mode()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, g2_window;
    Object g2_user_mode_qm, x2;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,138);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)235L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  g2_window = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    g2_user_mode_qm = Nil;
	    ab_loopvar_ = collect_subclasses(Qg2_window);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    g2_window = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    g2_user_mode_qm = get_slot_value_function(g2_window,
		    Qg2_user_mode,Nil);
	    if (g2_user_mode_qm &&  !SYMBOLP(g2_user_mode_qm)) {
		if (SIMPLE_VECTOR_P(g2_user_mode_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_user_mode_qm)) > 
			(SI_Long)2L &&  !EQ(ISVREF(g2_user_mode_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(g2_user_mode_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    delete_frame(g2_user_mode_qm);
		set_slot_value_function(g2_window,Qg2_user_mode,Nil,Nil);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CONVERT-ALIST-TO-PLIST */
Object convert_alist_to_plist(variables_alist_qm)
    Object variables_alist_qm;
{
    Object temp, variables_plist, variable_name, variable_value, ab_loop_list_;
    Object ab_loop_desetq_;

    x_note_fn_call(132,139);
    temp = CAR(variables_alist_qm);
    if (CONSP(temp)) {
	variables_plist = Nil;
	variable_name = Nil;
	variable_value = Nil;
	ab_loop_list_ = variables_alist_qm;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	variable_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	variable_value = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	variables_plist = slot_value_cons_1(variable_name,variables_plist);
	variables_plist = slot_value_cons_1(variable_value,variables_plist);
	goto next_loop;
      end_loop:
	reclaim_slot_value_tree_1(variables_alist_qm);
	return nreverse(variables_plist);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(variables_alist_qm);
}

static Object Qentity;             /* entity */

/* FIX-ICON-VARIABLES-ALISTS-IN-ICON-ATTRIBUTES-PLIST */
Object fix_icon_variables_alists_in_icon_attributes_plist()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, entity;
    Object icon_attributes_plist, variables_qm, temp_1, getf_new_value;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,140);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)258L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  entity = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    icon_attributes_plist = Nil;
	    variables_qm = Nil;
	    ab_loopvar_ = collect_subclasses(Qentity);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    entity = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
	    variables_qm = getfq_function_no_default(icon_attributes_plist,
		    Qvariables);
	    if (variables_qm) {
		temp_1 = M_CAR(variables_qm);
		temp = CONSP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		getf_new_value = convert_alist_to_plist(variables_qm);
		icon_attributes_plist = set_getf(icon_attributes_plist,
			Qvariables,getf_new_value);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CENTER-WORKSPACE-BACKGROUND-IMAGES */
Object center_workspace_background_images()
{
    Object kb_flags;
    Declare_special(1);

    x_note_fn_call(132,141);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !TRUEP(workspace_background_images_are_centered_p()))
	  center_workspace_background_images_after_loading();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CHECK-INSERT-ACTION-DUPLICATE-ELEMENT-FLAG */
Object check_insert_action_duplicate_element_flag()
{
    Object kb_flags;
    Declare_special(1);

    x_note_fn_call(132,142);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !(IFIX(Kb_flags) >= (SI_Long)247L))
	  set_ignore_insert_action_duplicate_element();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CHECK-NEW-GET-CONNECTION-VERTEX-BEHAVIOR-FLAG */
Object check_new_get_connection_vertex_behavior_flag()
{
    Object kb_flags;
    Declare_special(1);

    x_note_fn_call(132,143);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !(IFIX(Kb_flags) >= (SI_Long)249L))
	  set_get_connection_vertices_backward_compatibility();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object list_constant_15;    /* # */

/* CHECK-PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS */
Object check_print_means_print_to_server_in_configurations()
{
    x_note_fn_call(132,144);
    if ( !TRUEP(system_version_greater_p(System_version_from_last_kb_read,
	    list_constant_15)))
	set_print_means_print_to_server_in_configurations();
    return VALUES_1(Nil);
}

/* CHECK-INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS */
Object check_inconsistent_behavior_of_move_in_configurations()
{
    x_note_fn_call(132,145);
    if ( !TRUEP(system_version_greater_p(System_version_from_last_kb_read,
	    list_constant_12)))
	set_inconsistent_behavior_of_move_in_configurations();
    return VALUES_1(Nil);
}

static Object Qab_class;           /* class */

/* UPDATE-REPRESENTATIONS-OF-CONFIGURATION-GRAMMAR */
Object update_representations_of_configuration_grammar()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, config, block;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,146);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)250L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  config = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qkb_configuration);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    config = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    update_representations_of_slot_value(2,config,Qab_class);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop_2:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_3:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_2;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_2;
		goto next_loop_3;
	      end_loop_2:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_3;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(block,(SI_Long)9L)) {
		if (get_lookup_slot_value(block,Qobject_configuration))
		    update_representations_of_slot_value(2,block,
			    Qobject_configuration);
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? TRUEP(ISVREF(block,(SI_Long)23L)) : TRUEP(Nil))
		    update_representations_of_slot_value(2,block,
			    Qinstance_configuration);
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

/* UPDATE-REPRESENTATIONS-OF-CLASS-SPECIFIC-ATTRIBUTES-GRAMMAR */
Object update_representations_of_class_specific_attributes_grammar()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object class_definition;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,147);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)253L || 
	      system_revision_greater_p(list_constant_16,
	      System_version_from_last_kb_read))) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  class_definition = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qclass_definition);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    class_definition = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(class_definition,(SI_Long)22L) && 
		    ISVREF(class_definition,(SI_Long)9L))
		update_representations_of_slot_value(2,class_definition,
			Qclass_specific_attributes);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* UPDATE-REPRESENTATIONS-OF-DEFAULT-OVERRIDES-GRAMMAR */
Object update_representations_of_default_overrides_grammar()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object class_definition;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,148);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !FIXNUM_GT(Kb_flags,G2_version_6_general_kb_flags)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  class_definition = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qclass_definition);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    class_definition = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(class_definition,(SI_Long)27L) && 
		    ISVREF(class_definition,(SI_Long)9L))
		update_representations_of_slot_value(2,class_definition,
			Qdefault_overrides);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qvariable_or_parameter;  /* variable-or-parameter */

/* UPDATE-REPRESENTATIONS-OF-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER */
Object update_representations_of_initial_value_of_variable_or_parameter()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, v_or_p;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,149);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !FIXNUM_GT(Kb_flags,G2_version_6_general_kb_flags)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  v_or_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qvariable_or_parameter);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    v_or_p = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(v_or_p,(SI_Long)9L))
		update_representations_of_slot_value(2,v_or_p,
			Qinitial_value_of_variable_or_parameter);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qparent_frame;       /* parent-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* REMOVE-BOGUS-STUBS-ON-FRAMES-IN-ATTRIBUTES */
Object remove_bogus_stubs_on_frames_in_attributes()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connections_to_delete;
    Object ab_loopvar__2, ab_loopvar__3, temp_1, ab_less_than_branch_qm_;
    Object connnection, ab_loop_list_, old, svref_new_value;
    SI_Long new_1;
    char temp;
    Declare_special(3);

    x_note_fn_call(132,150);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,2);
      if ( !(IFIX(Kb_flags) >= (SI_Long)251L && 
	      system_revision_greater_p(System_version_from_last_kb_read,
	      list_constant_16))) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    ab_loopvar_ = collect_subclasses(Qobject);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (get_lookup_slot_value_given_default(block,Qparent_frame,
		    Nil) && get_lookup_slot_value_given_default(block,
		    Qparent_attribute_name,Nil)) {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
		ab_skip_list_form_ = gensymed_symbol;
		ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		ab_connection_ = Nil;
		ab_connection_item_ = Nil;
		connection = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  connections_to_delete = Nil;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__3 = Nil;
		  gensymed_symbol = CDR(ab_skip_list_form_);
		  if (CONSP(gensymed_symbol)) {
		      temp_1 = M_CAR(gensymed_symbol);
		      temp = SIMPLE_VECTOR_P(temp_1);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      temp_1 = M_CDR(gensymed_symbol);
		      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		  }
		  else
		      ab_skip_list_p_ = Nil;
		  if (ab_skip_list_p_) {
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			      (SI_Long)0L),(SI_Long)0L));
		      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		  }
		  else
		      ab_next_node_ = CDR(ab_skip_list_form_);
		next_loop_2:
		next_loop_3:
		  if (ab_current_alist_) {
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_connection_ = M_CAR(ab_entry_cons_);
		      ab_connection_item_ = M_CDR(ab_entry_cons_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
		  else if (ab_skip_list_p_) {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_next_node_ = 
				  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
				  (SI_Long)0L),(SI_Long)0L));
			  if (EQ(ab_next_node_,ab_tail_node_))
			      ab_next_node_ = Nil;
			  ab_connection_ = ISVREF(ab_current_node_,
				  (SI_Long)2L);
			  ab_connection_item_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
		      }
		      else
			  ab_current_node_ = Nil;
		  }
		  else {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_less_than_branch_qm_ = Nil;
			next_loop_4:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_2;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_4;
			end_loop_2:;
		      }
		      else if (ab_node_stack_) {
			  ab_next_node_ = ab_node_stack_;
			  ab_current_node_ = M_CAR(ab_node_stack_);
			  ab_node_stack_ = M_CDR(ab_node_stack_);
		      }
		      else
			  ab_current_node_ = Nil;
		      if (ab_current_node_) {
			  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_connection_ = M_CAR(ab_entry_cons_);
			  ab_connection_item_ = M_CDR(ab_entry_cons_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
			  ab_connection_)
		      goto end_1;
		  goto next_loop_3;
		end_loop_3:
		end_1:
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_4;
		  connection = ab_connection_;
		  ab_loopvar__3 = gensym_cons_1(connection,Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__3;
		  else
		      connections_to_delete = ab_loopvar__3;
		  ab_loopvar__2 = ab_loopvar__3;
		  goto next_loop_2;
		end_loop_4:
		  connnection = Nil;
		  ab_loop_list_ = connections_to_delete;
		next_loop_5:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_5;
		  connnection = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ISVREF(connection,(SI_Long)3L) || ISVREF(connection,
			  (SI_Long)2L)) {
		      if (ISVREF(connection,(SI_Long)3L) && 
			      ISVREF(connection,(SI_Long)2L))
			  delete_connection(1,connection);
		      else;
		  }
		  else {
		      delete_connection_in_block(block,connection,T);
		      old = ISVREF(connection,(SI_Long)10L);
		      new_1 = (SI_Long)-1L;
		      svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
			      (FIXNUMP(FIX(new_1)) ||  !TRUEP(FIX(new_1))) 
			      ? FIX(new_1) : 
			      frame_serial_number_setf_helper_1(old,
			      FIX(new_1));
		      SVREF(connection,FIX((SI_Long)10L)) = svref_new_value;
		      reclaim_connection_1(connection);
		  }
		  goto next_loop_5;
		end_loop_5:;
		  reclaim_gensym_list_1(connections_to_delete);
		POP_SPECIAL();
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* FIX-KB-WORKSPACES-THAT-MIGHT-BE-TOO-BIG */
Object fix_kb_workspaces_that_might_be_too_big()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace;
    char temp;
    Declare_special(1);

    x_note_fn_call(132,151);
    if (T) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	workspace = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qkb_workspace);
	next_loop:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop;
	      goto next_loop_1;
	    end_loop:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_1;
	  workspace = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  shrink_wrap_workspace_around_maximum_rectangle(workspace);
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* DELETE-CONNECTION-FRAMES-WITHOUT-CONNECTION-STRUCTURES */
Object delete_connection_frames_without_connection_structures()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, connection_frame_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(132,152);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    connection_frame_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qconnection);
    next_loop:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_1;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      connection_frame_1 = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !TRUEP(ISVREF(connection_frame_1,(SI_Long)21L)))
	  delete_frame(connection_frame_1);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

/* FIXUP-ALL-AUTHOR-OR-AUTHORS */
Object fixup_all_author_or_authors()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, frame;
    Object author_or_authors, new_value_or_nil;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,153);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !(IFIX(Kb_flags) >= (SI_Long)268L)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    author_or_authors = Nil;
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    frame = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    author_or_authors = get_lookup_slot_value_given_default(frame,
		    Qframe_author_or_authors,Nil);
	    if (author_or_authors) {
		new_value_or_nil = 
			fixup_author_or_authors_value(author_or_authors);
		if (new_value_or_nil)
		    change_slot_value(3,frame,Qframe_author_or_authors,
			    new_value_or_nil);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qdigital_clock;      /* digital-clock */

/* FIXUP-ALL-DIGITAL-CLOCKS */
Object fixup_all_digital_clocks()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, frame;
    Object first_row, temp_1;
    char temp;
    Declare_special(2);

    x_note_fn_call(132,154);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !FIXNUM_GE(Kb_flags,G2_version_6_general_kb_flags)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    first_row = Nil;
	    ab_loopvar_ = collect_subclasses(Qdigital_clock);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    frame = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    temp_1 = ISVREF(frame,(SI_Long)19L);
	    first_row = FIRST(temp_1);
	    if (FIRST(first_row)) {
		reclaim_slot_value(FIRST(first_row));
		M_FIRST(first_row) = Nil;
		reformat_table_in_place(1,frame);
		update_images_of_block(frame,Nil,T);
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

static Object Qdefault_message_properties;  /* default-message-properties */

/* NORMALIZE-MESSAGE-PROPERTIES-FOR-MESSAGE-DEFINITION */
Object normalize_message_properties_for_message_definition(message_definition)
    Object message_definition;
{
    Object message_properties, sym, ab_loop_list_, value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, normalized_message_properties;

    x_note_fn_call(132,155);
    message_properties = ISVREF(message_definition,(SI_Long)30L);
    sym = Nil;
    ab_loop_list_ = list_constant_17;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sym = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = assq_function(sym,message_properties);
    value = CDR(temp);
    if (value) {
	ab_loopvar__2 = slot_value_cons_1(slot_value_cons_1(sym,value),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    normalized_message_properties = ab_loopvar_;
    goto end_1;
    normalized_message_properties = Qnil;
  end_1:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(message_definition,Qdefault_message_properties);
    SVREF(message_definition,FIX((SI_Long)30L)) = 
	    normalized_message_properties;
    reclaim_slot_value(message_properties);
    return VALUES_1(Nil);
}

/* GET-UPDATED-EDGES-FROM-ELEMENTS-AND-BACKGROUND */
Object get_updated_edges_from_elements_and_background(workspace,left,top,
	    right,bottom,margin)
    Object workspace, left, top, right, bottom, margin;
{
    Object new_left, new_top, new_right, new_bottom, gensymed_symbol;
    Object subblocks, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far, temp_1;
    char temp;
    Declare_special(4);

    x_note_fn_call(132,156);
    new_left = left;
    new_top = top;
    new_right = right;
    new_bottom = bottom;
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    temp = subblocks ?  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
	    (SI_Long)2L),subblocks)) : TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(has_background_images_p(workspace));
    if (temp) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	extreme_top_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_right_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	extreme_bottom_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		      0);
		gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		subblocks = gensymed_symbol;
		if (subblocks &&  ! 
			!TRUEP(constant_queue_next(ISVREF(subblocks,
			(SI_Long)2L),subblocks)))
		    update_extreme_edges_from_elements_function(workspace,Nil);
		update_extreme_edges_from_background_images(workspace);
		temp_1 = FIXNUM_MINUS(Extreme_left_edge_so_far,margin);
		new_left = FIXNUM_MIN(left,temp_1);
		temp_1 = FIXNUM_MINUS(Extreme_top_edge_so_far,margin);
		new_top = FIXNUM_MIN(top,temp_1);
		temp_1 = FIXNUM_ADD(Extreme_right_edge_so_far,margin);
		new_right = FIXNUM_MAX(right,temp_1);
		temp_1 = FIXNUM_ADD(Extreme_bottom_edge_so_far,margin);
		new_bottom = FIXNUM_MAX(bottom,temp_1);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_4(new_left,new_top,new_right,new_bottom);
}

/* MAYBE-NORMALIZE-WORKSPACE-EDGES */
Object maybe_normalize_workspace_edges()
{
    Object kb_flags, scope_conses, ab_loopvar_, ab_loopvar__1, workspace;
    Object gensymed_symbol, old_left, old_top, old_right, old_bottom, margin;
    Object new_left, new_top, new_right, new_bottom, gensymed_symbol_1;
    Object slot_group_qm, temp_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(132,157);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,1);
      if ( !FIXNUM_GE(Kb_flags,G2_version_6_general_kb_flags)) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  workspace = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qkb_workspace);
	  next_loop:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_1:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_1;
	    workspace = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    old_left = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    old_top = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    old_right = gensymed_symbol;
	    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    old_bottom = gensymed_symbol;
	    margin = ISVREF(workspace,(SI_Long)17L);
	    result = get_updated_edges_from_elements_and_background(workspace,
		    old_left,old_top,old_right,old_bottom,margin);
	    MVS_4(result,new_left,new_top,new_right,new_bottom);
	    gensymed_symbol = workspace;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = new_left;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)0L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_1 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_1,FIX((SI_Long)0L)) = gensymed_symbol_1;
	    }
	    gensymed_symbol = workspace;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = new_top;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_1 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_1,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    }
	    gensymed_symbol = workspace;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = new_right;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_1 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_1,FIX((SI_Long)2L)) = gensymed_symbol_1;
	    }
	    gensymed_symbol = workspace;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = new_bottom;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,FIX((SI_Long)0L))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_1 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_1;
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
	    }
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qdefault_window_style;  /* default-window-style */

static Object Qg2_5_dot_x;         /* g2-5.x */

/* RESET-DEFAULT-WINDOW-STYLE-IF-NEEDED */
Object reset_default_window_style_if_needed()
{
    Object kb_flags, misc_params_qm;
    Declare_special(1);

    x_note_fn_call(132,158);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if (loading_version_5_or_earlier_kb_p()) {
	  misc_params_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qmiscellaneous_parameters,
		  Name_of_module_being_read_qm) : Nil;
	  if (misc_params_qm);
	  else
	      misc_params_qm = Miscellaneous_parameters;
	  if (misc_params_qm)
	      change_slot_value(3,misc_params_qm,Qdefault_window_style,
		      Qg2_5_dot_x);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_56;  /* "s" */

static Object string_constant_57;  /* "KB" */

static Object string_constant_58;  /* "Cleared ~d unattached connection~a from ~a." */

/* DELETE-BAD-CONNECTION-STRUCTURES */
Object delete_bad_connection_structures()
{
    Object reference_fsn, blocks, count_1, temp, temp_1;

    x_note_fn_call(132,159);
    if (Blocks_with_bad_connections) {
	reference_fsn = CAR(Blocks_with_bad_connections);
	blocks = CDR(Blocks_with_bad_connections);
	count_1 = reclaim_bad_connections_of_blocks(blocks,reference_fsn);
	if (IFIX(count_1) > (SI_Long)0L) {
	    temp = IFIX(count_1) == (SI_Long)1L ? string_constant_2 : 
		    string_constant_56;
	    temp_1 = Name_of_module_being_read_qm;
	    if (temp_1);
	    else
		temp_1 = string_constant_57;
	    notify_user_at_console_and_on_logbook(4,string_constant_58,
		    count_1,temp,temp_1);
	}
	reclaim_gensym_list_1(Blocks_with_bad_connections);
	reclaim_frame_serial_number(reference_fsn);
	Blocks_with_bad_connections = Nil;
    }
    return VALUES_1(Nil);
}

/* UPGRADE-BLOCK-CONNECTIONS-TO-CONNECTIONS-V2 */
Object upgrade_block_connections_to_connections_v2()
{
    Object block, ab_loop_list_, x2;
    char temp;

    x_note_fn_call(132,160);
    if (Blocks_with_connections_from_kb_read) {
	block = Nil;
	ab_loop_list_ = Blocks_with_connections_from_kb_read;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(block) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L &&  
		!EQ(ISVREF(block,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    upgrade_block_connections(block);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(Blocks_with_connections_from_kb_read);
	Blocks_with_connections_from_kb_read = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qprefer_native_editor;  /* prefer-native-editor */

/* CLASSIC-KBS-PREFER-CLASSIC-EDITOR */
Object classic_kbs_prefer_classic_editor()
{
    Object kb_flags, editor_parameters_qm;
    Declare_special(1);

    x_note_fn_call(132,161);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !FIXNUM_GE(Kb_flags,G2_version_8_1_alpha_0_kb_flags)) {
	  editor_parameters_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qeditor_parameters,
		  Name_of_module_being_read_qm) : Editor_parameters;
	  if (editor_parameters_qm)
	      change_slot_value(3,editor_parameters_qm,
		      Qprefer_native_editor,Nil);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qprefer_native_logbook;  /* prefer-native-logbook */

static Object Qprefer_native_message_board;  /* prefer-native-message-board */

static Object Qprefer_native_login_dialog;  /* prefer-native-login-dialog */

/* CLASSIC-KBS-PREFER-CLASSIC-UI-FEATURES */
Object classic_kbs_prefer_classic_ui_features()
{
    Object kb_flags, logbook_parameters_qm, message_board_parameters_qm;
    Object miscellaneous_parameters_qm;
    Declare_special(1);

    x_note_fn_call(132,162);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !FIXNUM_GE(Kb_flags,G2_version_82r0_kb_flags)) {
	  logbook_parameters_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qlogbook_parameters,
		  Name_of_module_being_read_qm) : Logbook_parameters;
	  if (logbook_parameters_qm)
	      change_slot_value(3,logbook_parameters_qm,
		      Qprefer_native_logbook,Nil);
	  message_board_parameters_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qmessage_board_parameters,
		  Name_of_module_being_read_qm) : Message_board_parameters;
	  if (Message_board_parameters)
	      change_slot_value(3,message_board_parameters_qm,
		      Qprefer_native_message_board,Nil);
	  miscellaneous_parameters_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qmiscellaneous_parameters,
		  Name_of_module_being_read_qm) : Miscellaneous_parameters;
	  if (Miscellaneous_parameters)
	      change_slot_value(3,miscellaneous_parameters_qm,
		      Qprefer_native_login_dialog,Nil);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qshow_selection_handles;  /* show-selection-handles */

/* CLASSIC-KBS-PREFER-CLASSIC-SELECTION-HIGHLIGHTING */
Object classic_kbs_prefer_classic_selection_highlighting()
{
    Object kb_flags, drawing_parameters_qm;
    Declare_special(1);

    x_note_fn_call(132,163);
    kb_flags = Kb_flags_from_last_kb_read;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_flags,Qkb_flags,kb_flags,0);
      if ( !FIXNUM_GE(Kb_flags,G2_version_8_3_alpha_0_kb_flags)) {
	  drawing_parameters_qm = Name_of_module_being_read_qm ? 
		  get_system_table_instance_for_module(Qdrawing_parameters,
		  Name_of_module_being_read_qm) : Drawing_parameters;
	  if (drawing_parameters_qm)
	      change_slot_value(3,drawing_parameters_qm,
		      Qshow_selection_handles,Nil);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* CHECK-IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS */
Object check_ignore_snap_grid_in_transfer_operations()
{
    x_note_fn_call(132,164);
    if ( !FIXNUM_GE(Kb_flags,G2_version_8_3_alpha_0_kb_flags))
	set_ignore_snap_grid_in_transfer_operations();
    return VALUES_1(Nil);
}

void kb_load2_INIT()
{
    Object temp, temp_1, temp_2;
    Object Qcheck_ignore_snap_grid_in_transfer_operations, AB_package;
    Object Qclassic_kbs_prefer_classic_selection_highlighting;
    Object Qclassic_kbs_prefer_classic_ui_features;
    Object Qclassic_kbs_prefer_classic_editor;
    Object Qupgrade_block_connections_to_connections_v2;
    Object Qdelete_bad_connection_structures;
    Object Qreset_default_window_style_if_needed;
    Object Qmaybe_normalize_workspace_edges, Qfont, Qminimum_height;
    Object Qminimum_width, Qborder_color, Qbackground_color, Qline_color;
    Object Qfixup_all_digital_clocks, Qfixup_all_author_or_authors;
    Object Qdelete_connection_frames_without_connection_structures;
    Object Qfix_kb_workspaces_that_might_be_too_big;
    Object Qremove_bogus_stubs_on_frames_in_attributes;
    Object Qupdate_representations_of_initial_value_of_variable_or_parameter;
    Object Qupdate_representations_of_default_overrides_grammar;
    Object Qupdate_representations_of_class_specific_attributes_grammar;
    Object string_constant_59, Qalpha_or_beta;
    Object Qupdate_representations_of_configuration_grammar;
    Object Qcheck_inconsistent_behavior_of_move_in_configurations;
    Object Qcheck_print_means_print_to_server_in_configurations;
    Object list_constant_22, Qcheck_new_get_connection_vertex_behavior_flag;
    Object Qcheck_insert_action_duplicate_element_flag;
    Object Qcenter_workspace_background_images;
    Object Qfix_icon_variables_alists_in_icon_attributes_plist;
    Object Qfix_possible_non_symbols_in_g2_user_mode;
    Object Qeliminate_procedure_invocation_frame_notes, Qprocedure_invocation;
    Object Qensure_connections_have_frames_if_necessary;
    Object Qassure_all_charts_have_style;
    Object Qfix_module_related_frame_notes_after_loading;
    Object Qrendezvous_frames_and_denotations_in_aggregate_evaluation_values;
    Object Qdelete_type_violating_relation_instances;
    Object Qrendezvous_frame_denotations_in_relation_instances;
    Object Qanalyze_compiled_items_after_loading;
    Object Qinstall_connection_posts_after_loading;
    Object Qinstall_external_simulation, Qidentify_all_permanent_blocks;
    Object Qrecompile_if_compilations_were_removed, Qkb_load2;
    Object Qremove_redundant_simulation_formulas_notes;
    Object Qprovide_message_board_after_loading_kb;
    Object Qremove_unimplemented_superiors, Qfix_capabilities_of_old_kbs;
    Object Qfix_unimplemented_definitions;
    Object Qmake_all_rule_boxes_have_text_box_format, Qmake_graphs_opaque;
    Object Qclean_up_orphan_frame_representations, Qclasses_which_define;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_object_definition;
    Object Qinitialize_after_reading_for_definition, Qfix_subworkspace_names;
    Object string_constant_60, Qreclaim_gensym_list_function;
    Object Qgraph_horizontal_axis_heading_text_cell_format;
    Object Qgraph_horizonral_axis_heading_text_cell_format;
    Object Qgfi_output_interface, Qgfi_input_interface;
    Object Qg2_to_g2_data_interface, Qsubworkspace_connection_posts;
    Object Qno_manual_connections, Qexternal_simulation;
    Object Qactivatable_subworkspace, list_constant_21, Qg2_meter_data_service;
    Object Qg2_to_g2_data_service, Qgfi_data_service, Qgsi_message_service;
    Object Qgsi_data_service, Qinitialize_unbound_slots_in_definitions;
    Object Qinitialize_after_reading_for_table;
    Object Qinitialize_instances_with_default_data_interface_values;
    Object Qnote_runs_while_inactive_change;
    Object Qnote_runs_while_inactive_change_for_block, Qcleanup;
    Object Qcleanup_for_block, Qinitialize, Qinitialize_for_block;
    Object Qinitialize_after_reading_for_block;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qearliest_version_to_allow_kb_loading, list_constant_20;
    Object Qmost_positive_fixnum_ash_minus_5_minus_1, Qbase_modulus;
    Object Qstandard_base_reference, Qgeneric_method_lambda_list;
    Object list_constant_19, Qfix_frame_with_substitute_class;
    Object list_constant_18, Qreclaim_frame_serial_number, Qreclaim_slot_value;

    x_note_fn_call(132,165);
    SET_PACKAGE("AB");
    Switched_once_only_post_loads_are_after_conflict_resolution = T;
    if (List_of_module_pre_conflict_resolution_post_loading_functions == 
	    UNBOUND)
	List_of_module_pre_conflict_resolution_post_loading_functions = Nil;
    if (List_of_once_only_pre_conflict_resolution_post_loading_functions 
	    == UNBOUND)
	List_of_once_only_pre_conflict_resolution_post_loading_functions = Nil;
    if (List_of_once_only_switched_post_loading_functions == UNBOUND)
	List_of_once_only_switched_post_loading_functions = Nil;
    if (List_of_once_only_post_conflict_resolution_post_loading_functions 
	    == UNBOUND)
	List_of_once_only_post_conflict_resolution_post_loading_functions 
		= Nil;
    if (List_of_switched_and_module_post_loading_functions == UNBOUND)
	List_of_switched_and_module_post_loading_functions = Nil;
    if (Post_loading_functions_will_be_executed_again_later_qm == UNBOUND)
	Post_loading_functions_will_be_executed_again_later_qm = Nil;
    Verbose_post_loading_p = Nil;
    Kerror_recovery = STATIC_SYMBOL("ERROR-RECOVERY",Pkeyword);
    AB_package = STATIC_PACKAGE("AB");
    Qlist_of_once_only_pre_conflict_resolution_post_loading_functions = 
	    STATIC_SYMBOL("LIST-OF-ONCE-ONLY-PRE-CONFLICT-RESOLUTION-POST-LOADING-FUNCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_once_only_pre_conflict_resolution_post_loading_functions,
	    List_of_once_only_pre_conflict_resolution_post_loading_functions);
    Qlist_of_once_only_switched_post_loading_functions = 
	    STATIC_SYMBOL("LIST-OF-ONCE-ONLY-SWITCHED-POST-LOADING-FUNCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_once_only_switched_post_loading_functions,
	    List_of_once_only_switched_post_loading_functions);
    Qlist_of_once_only_post_conflict_resolution_post_loading_functions = 
	    STATIC_SYMBOL("LIST-OF-ONCE-ONLY-POST-CONFLICT-RESOLUTION-POST-LOADING-FUNCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_once_only_post_conflict_resolution_post_loading_functions,
	    List_of_once_only_post_conflict_resolution_post_loading_functions);
    list_constant_5 = 
	    STATIC_CONS(Qlist_of_once_only_post_conflict_resolution_post_loading_functions,
	    Qnil);
    list_constant_4 = 
	    STATIC_CONS(Qlist_of_once_only_switched_post_loading_functions,
	    list_constant_5);
    list_constant = 
	    STATIC_CONS(Qlist_of_once_only_pre_conflict_resolution_post_loading_functions,
	    list_constant_4);
    Kbefore_conflict_resolution = 
	    STATIC_SYMBOL("BEFORE-CONFLICT-RESOLUTION",Pkeyword);
    Qlist_of_module_pre_conflict_resolution_post_loading_functions = 
	    STATIC_SYMBOL("LIST-OF-MODULE-PRE-CONFLICT-RESOLUTION-POST-LOADING-FUNCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_module_pre_conflict_resolution_post_loading_functions,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    list_constant_1 = 
	    STATIC_CONS(Qlist_of_module_pre_conflict_resolution_post_loading_functions,
	    Qnil);
    list_constant_2 = 
	    STATIC_CONS(Qlist_of_once_only_pre_conflict_resolution_post_loading_functions,
	    list_constant_1);
    Qlist_of_switched_and_module_post_loading_functions = 
	    STATIC_SYMBOL("LIST-OF-SWITCHED-AND-MODULE-POST-LOADING-FUNCTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_switched_and_module_post_loading_functions,
	    List_of_switched_and_module_post_loading_functions);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qlist_of_once_only_pre_conflict_resolution_post_loading_functions,
	    Qlist_of_switched_and_module_post_loading_functions);
    Kafter_conflict_resolution = STATIC_SYMBOL("AFTER-CONFLICT-RESOLUTION",
	    Pkeyword);
    string_constant = STATIC_STRING("~%Doing ~d ~apost-loading functions....");
    string_constant_1 = STATIC_STRING("ERROR RECOVERY CASE ");
    string_constant_2 = STATIC_STRING("");
    string_constant_3 = STATIC_STRING("KB name: \"~a\"");
    string_constant_4 = STATIC_STRING("Module: \"~a\"");
    string_constant_5 = 
	    STATIC_STRING("~%*** NOTE: once-only functions ARE enabled. ***");
    string_constant_6 = 
	    STATIC_STRING("~%*** NOTE: pre-conflict-resolution post-loading functions only are enabled. ***");
    string_constant_7 = 
	    STATIC_STRING("~%*** NOTE: post-conflict-resolution post-loading functions only are enabled. ***");
    string_constant_8 = 
	    STATIC_STRING("~%Finished post-loading functions. Elapsed Time: ~d seconds.~%");
    string_constant_9 = STATIC_STRING("~%(~d) Entering ~a function....");
    string_constant_10 = STATIC_STRING("   !!!!!!!!!!");
    string_constant_11 = 
	    STATIC_STRING("     Exiting ~a function.~%     Elapsed Time: ~d seconds~a");
    if (Ignore_kb_flags_in_kbs_qm == UNBOUND)
	Ignore_kb_flags_in_kbs_qm = Nil;
    Qsaved_detail_pane_description = 
	    STATIC_SYMBOL("SAVED-DETAIL-PANE-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_detail_pane_description,
	    Saved_detail_pane_description);
    Qkb_load2 = STATIC_SYMBOL("KB-LOAD2",AB_package);
    Qreclaim_slot_value = STATIC_SYMBOL("RECLAIM-SLOT-VALUE",AB_package);
    record_system_variable(Qsaved_detail_pane_description,Qkb_load2,Nil,
	    Qnil,Qnil,Qreclaim_slot_value,Qt);
    Qreference_serial_number_for_saved_detail_pane_description = 
	    STATIC_SYMBOL("REFERENCE-SERIAL-NUMBER-FOR-SAVED-DETAIL-PANE-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreference_serial_number_for_saved_detail_pane_description,
	    Reference_serial_number_for_saved_detail_pane_description);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    record_system_variable(Qreference_serial_number_for_saved_detail_pane_description,
	    Qkb_load2,Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qreading_kb_p = STATIC_SYMBOL("READING-KB-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreading_kb_p,Reading_kb_p);
    record_system_variable(Qreading_kb_p,Qkb_load2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qloading_kb_p = STATIC_SYMBOL("LOADING-KB-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qloading_kb_p,Loading_kb_p);
    record_system_variable(Qloading_kb_p,Qkb_load2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsaving_kb_p = STATIC_SYMBOL("SAVING-KB-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaving_kb_p,Saving_kb_p);
    record_system_variable(Qsaving_kb_p,Qkb_load2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qread_kb_buffer = STATIC_SYMBOL("READ-KB-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qread_kb_buffer,Read_kb_buffer);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_string,
	    FIX((SI_Long)524288L));
    record_system_variable(Qread_kb_buffer,Qkb_load2,list_constant_18,Qnil,
	    Qnil,Qnil,Qnil);
    Qwarmboot_simulated_time = STATIC_SYMBOL("WARMBOOT-SIMULATED-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmboot_simulated_time,
	    Warmboot_simulated_time);
    record_system_variable(Qwarmboot_simulated_time,Qkb_load2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qwarmboot_current_time = STATIC_SYMBOL("WARMBOOT-CURRENT-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmboot_current_time,Warmboot_current_time);
    record_system_variable(Qwarmboot_current_time,Qkb_load2,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qread_kb_stream = STATIC_SYMBOL("READ-KB-STREAM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qread_kb_stream,Read_kb_stream);
    record_system_variable(Qread_kb_stream,Qkb_load2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qbasis_kb_frame_serial_number = 
	    STATIC_SYMBOL("BASIS-KB-FRAME-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbasis_kb_frame_serial_number,
	    Basis_kb_frame_serial_number);
    record_system_variable(Qbasis_kb_frame_serial_number,Qkb_load2,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qfix_frame_with_substitute_class = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS",AB_package);
    list_constant_19 = STATIC_CONS(Qblock,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qfix_frame_with_substitute_class,
	    list_constant_19,Qgeneric_method_lambda_list);
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    mutate_global_property(Qinitialize_after_reading,list_constant_19,
	    Qgeneric_method_lambda_list);
    if (Kb_format_identifier_read_qm == UNBOUND)
	Kb_format_identifier_read_qm = Nil;
    if (Newline_characters == UNBOUND) {
	temp = Nil;
	temp = adjoin(2,CHR('\n'),temp);
	temp = adjoin(2,CHR('\n'),temp);
	temp = adjoin(2,CHR('\n'),temp);
	temp = adjoin(2,CHR('\r'),temp);
	temp = adjoin(2,CHR('\r'),temp);
	temp = adjoin(2,CHR('\f'),temp);
	Newline_characters = nreverse(temp);
    }
    Ignore_process_newline = FIX((SI_Long)0L);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qstandard_base_reference = STATIC_SYMBOL("STANDARD-BASE-REFERENCE",
	    AB_package);
    SET_SYMBOL_VALUE(Qstandard_base_reference,FIX((SI_Long)27L));
    if (Base_reference == UNBOUND)
	Base_reference = Standard_base_reference;
    Qbase_modulus = STATIC_SYMBOL("BASE-MODULUS",AB_package);
    SET_SYMBOL_VALUE(Qbase_modulus,FIX((SI_Long)3989L));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qnon_simple_character_code = STATIC_SYMBOL("NON-SIMPLE-CHARACTER-CODE",
	    AB_package);
    Qbad_character_following_at = 
	    STATIC_SYMBOL("BAD-CHARACTER-FOLLOWING-@",AB_package);
    Qbad_character_following_tl = 
	    STATIC_SYMBOL("BAD-CHARACTER-FOLLOWING-~",AB_package);
    Qillegal_characters_following_bs = 
	    STATIC_SYMBOL("ILLEGAL-CHARACTERS-FOLLOWING-\\",AB_package);
    Qincomplete_escape_sequence = 
	    STATIC_SYMBOL("INCOMPLETE-ESCAPE-SEQUENCE",AB_package);
    Qmost_positive_fixnum_ash_minus_5_minus_1 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-ASH-MINUS-5-MINUS-1",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_ash_minus_5_minus_1,
	    Most_positive_fixnum_ash_minus_5_minus_1);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_ash_minus_5_minus_1,
	    FIX((IFIX(Most_positive_fixnum) >>  -  - (SI_Long)5L) - 
	    (SI_Long)1L));
    Qframes_for_rendezvous_in_aggregate_values_qm = 
	    STATIC_SYMBOL("FRAMES-FOR-RENDEZVOUS-IN-AGGREGATE-VALUES\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframes_for_rendezvous_in_aggregate_values_qm,
	    Frames_for_rendezvous_in_aggregate_values_qm);
    record_system_variable(Qframes_for_rendezvous_in_aggregate_values_qm,
	    Qkb_load2,Nil,Qnil,Qnil,Qnil,Qnil);
    if (Locked_to_kb_qm == UNBOUND)
	Locked_to_kb_qm = Nil;
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qgensym_pathname_namestring = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-NAMESTRING",AB_package);
    Qg2_stream_error_string = STATIC_SYMBOL("G2-STREAM-ERROR-STRING",
	    AB_package);
    string_constant_12 = 
	    STATIC_STRING("G2 could not open the file \"~a\":  ~a.");
    Qgensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    string_constant_13 = STATIC_STRING("~a");
    string_constant_14 = STATIC_STRING("a xml-object for module ~a");
    string_constant_15 = STATIC_STRING("something");
    Qplist = STATIC_SYMBOL("PLIST",AB_package);
    Qget_xml_kb = STATIC_SYMBOL("GET-XML-KB",AB_package);
    Qrestore_xml_kb = STATIC_SYMBOL("RESTORE-XML-KB",AB_package);
    string_constant_16 = 
	    STATIC_STRING("File \"~A\" is not a KB or lacks a proper KB header.");
    Qkb_file_comment_string = STATIC_SYMBOL("KB-FILE-COMMENT-STRING",
	    AB_package);
    Qtype_of_file = STATIC_SYMBOL("TYPE-OF-FILE",AB_package);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    Qsave_kb_with_runtime_data = STATIC_SYMBOL("SAVE-KB-WITH-RUNTIME-DATA",
	    AB_package);
    Qkb_save_with_runtine_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTINE-DATA",
	    AB_package);
    Qkb_flags = STATIC_SYMBOL("KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_flags,Kb_flags);
    string_constant_17 = STATIC_STRING("~%");
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    if (New_compiled_byte_code_body_list == UNBOUND)
	New_compiled_byte_code_body_list = Nil;
    if (New_byte_code_body_list == UNBOUND)
	New_byte_code_body_list = Nil;
    Qread_kb_internal = STATIC_SYMBOL("READ-KB-INTERNAL",AB_package);
    string_constant_18 = STATIC_STRING("initialize_compiled_kb");
    string_constant_19 = 
	    STATIC_STRING("Loading \"~A\" -- after clearing old KB");
    string_constant_20 = STATIC_STRING("Clearing KB and merging in \"~A\"");
    string_constant_21 = 
	    STATIC_STRING("Merging \"~A\" into current KB -- and installing its system tables");
    string_constant_22 = STATIC_STRING("Merging \"~A\" into current KB");
    if (Reading_ghost_definitions_p == UNBOUND)
	Reading_ghost_definitions_p = Nil;
    if (Dont_load_if_definitions_have_changed_p == UNBOUND)
	Dont_load_if_definitions_have_changed_p = Nil;
    if (Collecting_warnings_p == UNBOUND)
	Collecting_warnings_p = Nil;
    if (Collected_items_with_warnings_alist == UNBOUND)
	Collected_items_with_warnings_alist = Nil;
    Qearliest_version_to_allow_kb_loading = 
	    STATIC_SYMBOL("EARLIEST-VERSION-TO-ALLOW-KB-LOADING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qearliest_version_to_allow_kb_loading,
	    Earliest_version_to_allow_kb_loading);
    Qalpha_or_beta = STATIC_SYMBOL("ALPHA-OR-BETA",AB_package);
    string_constant_59 = STATIC_STRING("Rev. 0");
    SET_SYMBOL_VALUE(Qearliest_version_to_allow_kb_loading,
	    LIST_4(FIX((SI_Long)5L),FIX((SI_Long)10L),Qalpha_or_beta,
	    string_constant_59));
    if (Automatically_resolve_conflicts_by_default == UNBOUND)
	Automatically_resolve_conflicts_by_default = T;
    if (Update_before_loading_by_default == UNBOUND)
	Update_before_loading_by_default = T;
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qinitial_plist_for_loaded_module = 
	    STATIC_SYMBOL("INITIAL-PLIST-FOR-LOADED-MODULE",AB_package);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),
	    FIX((SI_Long)8L));
    Qtop_level_module = STATIC_SYMBOL("TOP-LEVEL-MODULE",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qoriginal_kb_state_plist_written_qm = 
	    STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST-WRITTEN\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoriginal_kb_state_plist_written_qm,
	    Original_kb_state_plist_written_qm);
    string_constant_23 = 
	    STATIC_STRING("Invalid KB.  File contents are internally inconsistent.");
    Qreinitialize = STATIC_SYMBOL("REINITIALIZE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qreformat = STATIC_SYMBOL("REFORMAT",AB_package);
    Qkb_name = STATIC_SYMBOL("KB-NAME",AB_package);
    string_constant_24 = STATIC_STRING("Done loading \"~A\"~A");
    string_constant_25 = STATIC_STRING("Done merging \"~A\"");
    string_constant_26 = STATIC_STRING(" -- and clearing old KB");
    Qautomerge = STATIC_SYMBOL("AUTOMERGE",AB_package);
    Qdetail_pane_description = STATIC_SYMBOL("DETAIL-PANE-DESCRIPTION",
	    AB_package);
    Qnumeric_symbols = STATIC_SYMBOL("NUMERIC-SYMBOLS",AB_package);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    string_constant_27 = 
	    STATIC_STRING("\"~A\" cannot be loaded because it was created ~\n                    with a newer version of G2 than this one");
    string_constant_28 = 
	    STATIC_STRING("File \"~A\" is not a KB or lacks a proper KB header");
    string_constant_29 = 
	    STATIC_STRING("\"~A\" cannot be loaded because it was saved in G2 ");
    string_constant_30 = STATIC_STRING(". The KB must be saved in G2 ");
    string_constant_31 = 
	    STATIC_STRING(" or later in order to be loaded in this version of G2 (");
    string_constant_32 = STATIC_STRING(").");
    string_constant_33 = 
	    STATIC_STRING("READING HAS FAILED -- UNABLE TO PROCEED!");
    Qpost_load = STATIC_SYMBOL("POST-LOAD",AB_package);
    Qautomerge2 = STATIC_SYMBOL("AUTOMERGE2",AB_package);
    Qpost_load2 = STATIC_SYMBOL("POST-LOAD2",AB_package);
    Qrevert = STATIC_SYMBOL("REVERT",AB_package);
    Qfinished = STATIC_SYMBOL("FINISHED",AB_package);
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    Qbase_time = STATIC_SYMBOL("BASE-TIME",AB_package);
    Qstart_time = STATIC_SYMBOL("START-TIME",AB_package);
    Qsimulated_time = STATIC_SYMBOL("SIMULATED-TIME",AB_package);
    Qgensym_time = STATIC_SYMBOL("GENSYM-TIME",AB_package);
    string_constant_34 = 
	    STATIC_STRING("KB saved in wrong version, and the current-time is ~\n               unavailable.  Therefore, we cannot run from snapshot time!");
    Qab_current_frame_serial_number = 
	    STATIC_SYMBOL("CURRENT-FRAME-SERIAL-NUMBER",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qformat_change_qm = STATIC_SYMBOL("FORMAT-CHANGE\?",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qblocks_with_relation_instances_from_kb_read = 
	    STATIC_SYMBOL("BLOCKS-WITH-RELATION-INSTANCES-FROM-KB-READ",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblocks_with_relation_instances_from_kb_read,
	    Blocks_with_relation_instances_from_kb_read);
    record_system_variable(Qblocks_with_relation_instances_from_kb_read,
	    Qkb_load2,Nil,Qnil,Qnil,Qnil,Qt);
    Qblocks_with_connections_from_kb_read = 
	    STATIC_SYMBOL("BLOCKS-WITH-CONNECTIONS-FROM-KB-READ",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblocks_with_connections_from_kb_read,
	    Blocks_with_connections_from_kb_read);
    record_system_variable(Qblocks_with_connections_from_kb_read,Qkb_load2,
	    Nil,Qnil,Qnil,Qnil,Qt);
    Qblocks_with_subblocks_from_kb_read = 
	    STATIC_SYMBOL("BLOCKS-WITH-SUBBLOCKS-FROM-KB-READ",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblocks_with_subblocks_from_kb_read,
	    Blocks_with_subblocks_from_kb_read);
    record_system_variable(Qblocks_with_subblocks_from_kb_read,Qkb_load2,
	    Nil,Qnil,Qnil,Qnil,Qt);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qinitialize_after_reading_for_block = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_block,
	    STATIC_FUNCTION(initialize_after_reading_for_block,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_block);
    set_get(Qblock,Qinitialize_after_reading,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_2 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp_2);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qinitialize_for_block = STATIC_SYMBOL("INITIALIZE-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_block,
	    STATIC_FUNCTION(initialize_for_block,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_block);
    set_get(Qblock,Qinitialize,temp_1);
    temp_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp_2);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qcleanup_for_block = STATIC_SYMBOL("CLEANUP-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_block,
	    STATIC_FUNCTION(cleanup_for_block,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcleanup_for_block);
    set_get(Qblock,Qcleanup,temp_1);
    temp_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp_2);
    mutate_global_property(Qcleanup,temp_1,Qclasses_which_define);
    Qnote_runs_while_inactive_change_for_block = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_block,
	    STATIC_FUNCTION(note_runs_while_inactive_change_for_block,NIL,
	    FALSE,1,1));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_block);
    set_get(Qblock,Qnote_runs_while_inactive_change,temp_1);
    temp_2 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_runs_while_inactive_change),
	    Qclasses_which_define);
    temp_1 = CONS(Qblock,temp_2);
    mutate_global_property(Qnote_runs_while_inactive_change,temp_1,
	    Qclasses_which_define);
    Qclasses_needing_data_interface_initialization = 
	    STATIC_SYMBOL("CLASSES-NEEDING-DATA-INTERFACE-INITIALIZATION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclasses_needing_data_interface_initialization,
	    Classes_needing_data_interface_initialization);
    record_system_variable(Qclasses_needing_data_interface_initialization,
	    Qkb_load2,Nil,Qnil,Qt,Qnil,Qt);
    Qinitialize_instances_with_default_data_interface_values = 
	    STATIC_SYMBOL("INITIALIZE-INSTANCES-WITH-DEFAULT-DATA-INTERFACE-VALUES",
	    AB_package);
    temp_1 = adjoin(2,
	    Qinitialize_instances_with_default_data_interface_values,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,
	    Qinitialize_instances_with_default_data_interface_values,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_instances_with_default_data_interface_values,
	    STATIC_FUNCTION(initialize_instances_with_default_data_interface_values,
	    NIL,FALSE,0,0));
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qinitialize_after_reading_for_table = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_table,
	    STATIC_FUNCTION(initialize_after_reading_for_table,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_table);
    set_get(Qtable,Qinitialize_after_reading,temp_1);
    temp_2 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qtable,temp_2);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qparent = STATIC_SYMBOL("PARENT",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qname_of_defined_class = STATIC_SYMBOL("NAME-OF-DEFINED-CLASS",AB_package);
    Qsuperior_of_defined_class = STATIC_SYMBOL("SUPERIOR-OF-DEFINED-CLASS",
	    AB_package);
    Qdirect_superiors_of_defined_class = 
	    STATIC_SYMBOL("DIRECT-SUPERIORS-OF-DEFINED-CLASS",AB_package);
    Qcapabilities_of_class = STATIC_SYMBOL("CAPABILITIES-OF-CLASS",AB_package);
    Qdefault_overrides_of_system_slots = 
	    STATIC_SYMBOL("DEFAULT-OVERRIDES-OF-SYSTEM-SLOTS",AB_package);
    Qattribute_descriptions_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTIONS-FOR-CLASS",AB_package);
    Qline_color_of_icon = STATIC_SYMBOL("LINE-COLOR-OF-ICON",AB_package);
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    string_constant_35 = 
	    string_append2(STATIC_STRING("~S contains a value for attribute ~NQ in an instance ~\n                     of class ~NR, which does not have such an attribute.  The ~\n                     value will simply "),
	    STATIC_STRING("be discarded. Please notify Gensym Customer Support."));
    Qcomputation_style = STATIC_SYMBOL("COMPUTATION-STYLE",AB_package);
    Qkb_save_with_runtime_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTIME-DATA",
	    AB_package);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    Qinitialize_unbound_slots_in_definitions = 
	    STATIC_SYMBOL("INITIALIZE-UNBOUND-SLOTS-IN-DEFINITIONS",
	    AB_package);
    temp_1 = adjoin(2,Qinitialize_unbound_slots_in_definitions,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qinitialize_unbound_slots_in_definitions,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qinitialize_unbound_slots_in_definitions,
	    STATIC_FUNCTION(initialize_unbound_slots_in_definitions,NIL,
	    FALSE,0,0));
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qbackground_layer = STATIC_SYMBOL("BACKGROUND-LAYER",AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Quser_defined = STATIC_SYMBOL("USER-DEFINED",AB_package);
    Qindexed_attributes_for_definition = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTES-FOR-DEFINITION",AB_package);
    Qobject_definition = STATIC_SYMBOL("OBJECT-DEFINITION",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qmessage_definition = STATIC_SYMBOL("MESSAGE-DEFINITION",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qconnection_definition = STATIC_SYMBOL("CONNECTION-DEFINITION",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    string_constant_36 = string_appendn(3,
	    STATIC_STRING("~%~% Urgent:  ~\n                          A class-specific attribute for ~a ~\n                          has the same name (~(~a~)) as a system-defined ~\n                      "),
	    STATIC_STRING("    attribute. ~\n                          ~% It is extremely important to rename ~\n                          the ~a class-specific ~\n                          attribute befor"),
	    STATIC_STRING("e running this kb or doing any further ~\n                          development work to avoid a likely G2 failure."));
    string_constant_37 = string_appendn(3,
	    STATIC_STRING("~%~% Urgent:  ~\n\t\t\t  A class-specific attribute for an unnamed class ~\n                          has the same name (~(~a~)) as a system-defined ~\n                          att"),
	    STATIC_STRING("ribute. ~\n                          ~% It is extremely important to rename the ~a class-specific ~\n                          attribute before running this kb or doing any furt"),
	    STATIC_STRING("her ~\n                          development work to avoid a likely G2 failure."));
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    Qclass_specific_attributes = STATIC_SYMBOL("CLASS-SPECIFIC-ATTRIBUTES",
	    AB_package);
    Qdefault_overrides = STATIC_SYMBOL("DEFAULT-OVERRIDES",AB_package);
    Qgsi_data_service = STATIC_SYMBOL("GSI-DATA-SERVICE",AB_package);
    Qgsi_message_service = STATIC_SYMBOL("GSI-MESSAGE-SERVICE",AB_package);
    Qgfi_data_service = STATIC_SYMBOL("GFI-DATA-SERVICE",AB_package);
    Qg2_to_g2_data_service = STATIC_SYMBOL("G2-TO-G2-DATA-SERVICE",AB_package);
    Qg2_meter_data_service = STATIC_SYMBOL("G2-METER-DATA-SERVICE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)5L,Qgsi_data_service,
	    Qgsi_message_service,Qgfi_data_service,Qg2_to_g2_data_service,
	    Qg2_meter_data_service);
    Qgsi_interface_configuration = 
	    STATIC_SYMBOL("GSI-INTERFACE-CONFIGURATION",AB_package);
    Qg2_to_g2_data_interface = STATIC_SYMBOL("G2-TO-G2-DATA-INTERFACE",
	    AB_package);
    Qgfi_input_interface = STATIC_SYMBOL("GFI-INPUT-INTERFACE",AB_package);
    Qgfi_output_interface = STATIC_SYMBOL("GFI-OUTPUT-INTERFACE",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qg2_to_g2_data_interface,
	    Qgfi_input_interface,Qgfi_output_interface);
    list_constant_8 = STATIC_CONS(Qgsi_interface_configuration,
	    list_constant_21);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    list_constant_9 = STATIC_CONS(Qgsi_interface,list_constant_21);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qexternal_simulation = STATIC_SYMBOL("EXTERNAL-SIMULATION",AB_package);
    Qno_manual_connections = STATIC_SYMBOL("NO-MANUAL-CONNECTIONS",AB_package);
    Qsubworkspace_connection_posts = 
	    STATIC_SYMBOL("SUBWORKSPACE-CONNECTION-POSTS",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)4L,Qactivatable_subworkspace,
	    Qexternal_simulation,Qno_manual_connections,
	    Qsubworkspace_connection_posts);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)5L,Qgsi_interface,
	    Qg2_to_g2_data_interface,Qgfi_input_interface,
	    Qgfi_output_interface,list_constant_7);
    string_constant_38 = 
	    string_append2(STATIC_STRING("The class ~A had more than one data-interface capability. ~\n             This situation would make data connection-selection ambiguous. ~\n             One has been chosen to b"),
	    STATIC_STRING("e the sole data-interface direct-superior ~\n             class, ~A, and the class instances, if any, have had their ~A ~\n             attributes set to the default values."));
    Qinstance_configuration = STATIC_SYMBOL("INSTANCE-CONFIGURATION",
	    AB_package);
    string_constant_39 = STATIC_STRING("~%; slot ~s::~s:~%");
    string_constant_40 = STATIC_STRING("~%; slot ~s:~%");
    Qsubstitute_format_name = STATIC_SYMBOL("SUBSTITUTE-FORMAT-NAME",
	    AB_package);
    Substitute_format_name_prop = Qsubstitute_format_name;
    Qgraph_horizonral_axis_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-HORIZONRAL-AXIS-HEADING-TEXT-CELL-FORMAT",
	    AB_package);
    Qgraph_horizontal_axis_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-HORIZONTAL-AXIS-HEADING-TEXT-CELL-FORMAT",
	    AB_package);
    mutate_global_property(Qgraph_horizonral_axis_heading_text_cell_format,
	    Qgraph_horizontal_axis_heading_text_cell_format,
	    Qsubstitute_format_name);
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    string_constant_41 = 
	    string_append2(STATIC_STRING("Warning: An internal constraint has been violated.  A format ~\n                      with the unknown name ~A was discovered. Please report this ~\n                      proble"),
	    STATIC_STRING("m to Gensym Customer Support."));
    string_constant_42 = string_appendn(3,
	    STATIC_STRING("This KB has formatting problems! You should load with ~\n            with \", BRINGING FORMATS UP-TO-DATE\", and then save. ~\n            If you are a customer, please report thi"),
	    STATIC_STRING("s to software ~\n            support. If you work for Gensym, this KB should not be ~\n            released to customers until it\'s had its formats brought ~\n            up-to-d"),
	    STATIC_STRING("ate."));
    Qconnection_classes_warned_about_for_this_kb = 
	    STATIC_SYMBOL("CONNECTION-CLASSES-WARNED-ABOUT-FOR-THIS-KB",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_classes_warned_about_for_this_kb,
	    Connection_classes_warned_about_for_this_kb);
    Qreclaim_gensym_list_function = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-FUNCTION",AB_package);
    record_system_variable(Qconnection_classes_warned_about_for_this_kb,
	    Qkb_load2,Nil,Qnil,Qnil,Qreclaim_gensym_list_function,Qt);
    string_constant_43 = 
	    string_append2(STATIC_STRING("WARNING: When this KB (~s) was last saved, ~A was a ~\n         defined subclass of CONNECTION, but the class definition ~\n         was not saved with that KB due in part to a "),
	    STATIC_STRING("software ~\n         problem.  Unfortunately, instances of this class cannot ~\n         be properly restored.  "));
    string_constant_44 = 
	    string_append2(STATIC_STRING("Therefore, instances of the class ~A within this KB will ~\n         be turned into instances of the class CONNECTION.  ~\n         If you can restore the original definition of"),
	    STATIC_STRING(" ~A, you ~\n         may wish to abandon the current KB, and then merge this ~\n         KB into a KB that contains the restored definition."));
    string_constant_45 = STATIC_STRING("~a~a");
    string_constant_46 = 
	    STATIC_STRING("Cannot find frame reference of class ~a.");
    Qkb_error = STATIC_SYMBOL("KB-ERROR",AB_package);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qpunctuation_mark_p = STATIC_SYMBOL("PUNCTUATION-MARK-P",AB_package);
    Qpunctuation_mark = STATIC_SYMBOL("PUNCTUATION-MARK",AB_package);
    Qframe_denotation = STATIC_SYMBOL("FRAME-DENOTATION",AB_package);
    if (Create_frames_and_connections_reading_past_qm == UNBOUND)
	Create_frames_and_connections_reading_past_qm = Nil;
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)8L),
	    FIX((SI_Long)0L));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qjunction_block_class_for_connection = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CONNECTION",AB_package);
    string_constant_60 = STATIC_STRING("Beta Rev. 3");
    list_constant_13 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)4L),
	    FIX((SI_Long)0L),Qalpha_or_beta,string_constant_60);
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qconfiguration = STATIC_SYMBOL("CONFIGURATION",AB_package);
    string_constant_47 = 
	    STATIC_STRING("~A ~A~A~Aencountered while reading.  ~S either: (1) is not a KB, (2) has ~\n     been damaged, or (3) was not written properly due to a system software ~\n     error.");
    string_constant_48 = STATIC_STRING("Bad character");
    string_constant_49 = STATIC_STRING("End-of-file unexpectedly");
    string_constant_50 = STATIC_STRING("(");
    string_constant_51 = STATIC_STRING(") ");
    string_constant_52 = STATIC_STRING(" ");
    Qfix_subworkspace_names = STATIC_SYMBOL("FIX-SUBWORKSPACE-NAMES",
	    AB_package);
    temp_1 = adjoin(2,Qfix_subworkspace_names,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_subworkspace_names,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    string_constant_53 = STATIC_STRING(", ");
    string_constant_54 = 
	    string_append2(STATIC_STRING("This KB, which was created before version 2.0, has ~\n                    subworkspaces that have the same names as their superior objects. The names of ~\n                    t"),
	    STATIC_STRING("hese subworkspaces have been removed. They are: ~(~a~)"));
    SET_SYMBOL_FUNCTION(Qfix_subworkspace_names,
	    STATIC_FUNCTION(fix_subworkspace_names,NIL,FALSE,0,0));
    Qdata_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    Qinitialize_after_reading_for_definition = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_definition,
	    STATIC_FUNCTION(initialize_after_reading_for_definition,NIL,
	    FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_definition);
    set_get(Qdefinition,Qinitialize_after_reading,temp_1);
    temp_2 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qdefinition,temp_2);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qinitialize_after_reading_for_object_definition = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-OBJECT-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_object_definition,
	    STATIC_FUNCTION(initialize_after_reading_for_object_definition,
	    NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_object_definition);
    set_get(Qobject_definition,Qinitialize_after_reading,temp_1);
    temp_2 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qobject_definition,temp_2);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qclean_up_orphan_frame_representations = 
	    STATIC_SYMBOL("CLEAN-UP-ORPHAN-FRAME-REPRESENTATIONS",AB_package);
    temp_1 = adjoin(2,Qclean_up_orphan_frame_representations,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qclean_up_orphan_frame_representations,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qclean_up_orphan_frame_representations,
	    STATIC_FUNCTION(clean_up_orphan_frame_representations,NIL,
	    FALSE,0,0));
    Qmake_graphs_opaque = STATIC_SYMBOL("MAKE-GRAPHS-OPAQUE",AB_package);
    temp_1 = adjoin(2,Qmake_graphs_opaque,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qmake_graphs_opaque,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qmake_graphs_opaque,
	    STATIC_FUNCTION(make_graphs_opaque,NIL,FALSE,0,0));
    Qmake_all_rule_boxes_have_text_box_format = 
	    STATIC_SYMBOL("MAKE-ALL-RULE-BOXES-HAVE-TEXT-BOX-FORMAT",
	    AB_package);
    temp_1 = adjoin(2,Qmake_all_rule_boxes_have_text_box_format,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qmake_all_rule_boxes_have_text_box_format,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_all_rule_boxes_have_text_box_format,
	    STATIC_FUNCTION(make_all_rule_boxes_have_text_box_format,NIL,
	    FALSE,0,0));
    Qfix_unimplemented_definitions = 
	    STATIC_SYMBOL("FIX-UNIMPLEMENTED-DEFINITIONS",AB_package);
    temp_1 = adjoin(2,Qfix_unimplemented_definitions,
	    List_of_once_only_post_conflict_resolution_post_loading_functions);
    List_of_once_only_post_conflict_resolution_post_loading_functions = temp_1;
    Qjunction_block_class_for_class = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CLASS",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_unimplemented_definitions,
	    STATIC_FUNCTION(fix_unimplemented_definitions,NIL,FALSE,0,0));
    Qfix_capabilities_of_old_kbs = 
	    STATIC_SYMBOL("FIX-CAPABILITIES-OF-OLD-KBS",AB_package);
    temp_1 = adjoin(2,Qfix_capabilities_of_old_kbs,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_capabilities_of_old_kbs,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qfix_capabilities_of_old_kbs,
	    STATIC_FUNCTION(fix_capabilities_of_old_kbs,NIL,FALSE,0,0));
    Qremove_unimplemented_superiors = 
	    STATIC_SYMBOL("REMOVE-UNIMPLEMENTED-SUPERIORS",AB_package);
    temp_1 = adjoin(2,Qremove_unimplemented_superiors,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qremove_unimplemented_superiors,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qpotential_class_note = STATIC_SYMBOL("POTENTIAL-CLASS-NOTE",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_unimplemented_superiors,
	    STATIC_FUNCTION(remove_unimplemented_superiors,NIL,FALSE,0,0));
    Qprovide_message_board_after_loading_kb = 
	    STATIC_SYMBOL("PROVIDE-MESSAGE-BOARD-AFTER-LOADING-KB",AB_package);
    temp_1 = adjoin(2,Qprovide_message_board_after_loading_kb,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qprovide_message_board_after_loading_kb,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qprovide_message_board_after_loading_kb,
	    STATIC_FUNCTION(provide_message_board_after_loading_kb,NIL,
	    FALSE,0,0));
    Qremove_redundant_simulation_formulas_notes = 
	    STATIC_SYMBOL("REMOVE-REDUNDANT-SIMULATION-FORMULAS-NOTES",
	    AB_package);
    temp_1 = adjoin(2,Qremove_redundant_simulation_formulas_notes,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qremove_redundant_simulation_formulas_notes,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qredundant_generic_simulation_formulas = 
	    STATIC_SYMBOL("REDUNDANT-GENERIC-SIMULATION-FORMULAS",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_redundant_simulation_formulas_notes,
	    STATIC_FUNCTION(remove_redundant_simulation_formulas_notes,NIL,
	    FALSE,0,0));
    Qlaunch_recompile_for_compilations_removed_in_this_kb_qm = 
	    STATIC_SYMBOL("LAUNCH-RECOMPILE-FOR-COMPILATIONS-REMOVED-IN-THIS-KB\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlaunch_recompile_for_compilations_removed_in_this_kb_qm,
	    Launch_recompile_for_compilations_removed_in_this_kb_qm);
    record_system_variable(Qlaunch_recompile_for_compilations_removed_in_this_kb_qm,
	    Qkb_load2,Nil,Qnil,Qnil,Qnil,Qt);
    Qworkstation_in_which_to_launch_recompilation_qm = 
	    STATIC_SYMBOL("WORKSTATION-IN-WHICH-TO-LAUNCH-RECOMPILATION\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_in_which_to_launch_recompilation_qm,
	    Workstation_in_which_to_launch_recompilation_qm);
    record_system_variable(Qworkstation_in_which_to_launch_recompilation_qm,
	    Qkb_load2,Nil,Qnil,Qnil,Qnil,Qt);
    Qui_client_interface_in_which_to_launch_recompilation_qm = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-IN-WHICH-TO-LAUNCH-RECOMPILATION\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qui_client_interface_in_which_to_launch_recompilation_qm,
	    Ui_client_interface_in_which_to_launch_recompilation_qm);
    record_system_variable(Qui_client_interface_in_which_to_launch_recompilation_qm,
	    Qkb_load2,Nil,Qnil,Qnil,Qnil,Qt);
    string_constant_55 = 
	    STATIC_STRING("Once you save the KB in this version ~\n       of G2, recompilation will no longer happen automatically.");
    Qrecompile_if_compilations_were_removed = 
	    STATIC_SYMBOL("RECOMPILE-IF-COMPILATIONS-WERE-REMOVED",AB_package);
    temp_1 = adjoin(2,Qrecompile_if_compilations_were_removed,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qrecompile_if_compilations_were_removed,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qrecompile_if_compilations_were_removed,
	    STATIC_FUNCTION(recompile_if_compilations_were_removed,NIL,
	    FALSE,0,0));
    Qidentify_all_permanent_blocks = 
	    STATIC_SYMBOL("IDENTIFY-ALL-PERMANENT-BLOCKS",AB_package);
    temp_1 = adjoin(2,Qidentify_all_permanent_blocks,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qidentify_all_permanent_blocks,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qidentify_all_permanent_blocks,
	    STATIC_FUNCTION(identify_all_permanent_blocks,NIL,FALSE,0,0));
    Qinstall_external_simulation = 
	    STATIC_SYMBOL("INSTALL-EXTERNAL-SIMULATION",AB_package);
    temp_1 = adjoin(2,Qinstall_external_simulation,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qinstall_external_simulation,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qinstall_external_simulation,
	    STATIC_FUNCTION(install_external_simulation,NIL,FALSE,0,0));
    Qinstall_connection_posts_after_loading = 
	    STATIC_SYMBOL("INSTALL-CONNECTION-POSTS-AFTER-LOADING",AB_package);
    temp_1 = adjoin(2,Qinstall_connection_posts_after_loading,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qinstall_connection_posts_after_loading,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qinstall_connection_posts_after_loading,
	    STATIC_FUNCTION(install_connection_posts_after_loading,NIL,
	    FALSE,0,0));
    if (Compiling_incomplete_items_after_analyze_p == UNBOUND)
	Compiling_incomplete_items_after_analyze_p = Nil;
    if (Collecting_procedures_to_warn_about_p == UNBOUND)
	Collecting_procedures_to_warn_about_p = Nil;
    Qanalyze_compiled_items_after_loading = 
	    STATIC_SYMBOL("ANALYZE-COMPILED-ITEMS-AFTER-LOADING",AB_package);
    temp_1 = adjoin(2,Qanalyze_compiled_items_after_loading,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qanalyze_compiled_items_after_loading,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qanalyze = STATIC_SYMBOL("ANALYZE",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_compiled_items_after_loading,
	    STATIC_FUNCTION(analyze_compiled_items_after_loading,NIL,FALSE,
	    0,0));
    if (Rendezvous_successful_blocks_qm == UNBOUND)
	Rendezvous_successful_blocks_qm = Nil;
    if (Additional_related_blocks == UNBOUND)
	Additional_related_blocks = Nil;
    Qrendezvous_frame_denotations_in_relation_instances = 
	    STATIC_SYMBOL("RENDEZVOUS-FRAME-DENOTATIONS-IN-RELATION-INSTANCES",
	    AB_package);
    temp_1 = adjoin(2,Qrendezvous_frame_denotations_in_relation_instances,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qrendezvous_frame_denotations_in_relation_instances,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qrelation_instance_tree = STATIC_SYMBOL("RELATION-INSTANCE-TREE",
	    AB_package);
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
    Qone_to_one = STATIC_SYMBOL("ONE-TO-ONE",AB_package);
    Qone_to_many = STATIC_SYMBOL("ONE-TO-MANY",AB_package);
    Qmany_to_one = STATIC_SYMBOL("MANY-TO-ONE",AB_package);
    SET_SYMBOL_FUNCTION(Qrendezvous_frame_denotations_in_relation_instances,
	    STATIC_FUNCTION(rendezvous_frame_denotations_in_relation_instances,
	    NIL,FALSE,0,0));
    Qdelete_type_violating_relation_instances = 
	    STATIC_SYMBOL("DELETE-TYPE-VIOLATING-RELATION-INSTANCES",
	    AB_package);
    temp_1 = adjoin(2,Qdelete_type_violating_relation_instances,
	    List_of_once_only_post_conflict_resolution_post_loading_functions);
    List_of_once_only_post_conflict_resolution_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qdelete_type_violating_relation_instances,
	    STATIC_FUNCTION(delete_type_violating_relation_instances,NIL,
	    FALSE,0,0));
    Qrendezvous_frames_and_denotations_in_aggregate_evaluation_values = 
	    STATIC_SYMBOL("RENDEZVOUS-FRAMES-AND-DENOTATIONS-IN-AGGREGATE-EVALUATION-VALUES",
	    AB_package);
    temp_1 = adjoin(2,
	    Qrendezvous_frames_and_denotations_in_aggregate_evaluation_values,
	    List_of_once_only_pre_conflict_resolution_post_loading_functions);
    List_of_once_only_pre_conflict_resolution_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qrendezvous_frames_and_denotations_in_aggregate_evaluation_values,
	    STATIC_FUNCTION(rendezvous_frames_and_denotations_in_aggregate_evaluation_values,
	    NIL,FALSE,0,0));
    Qfix_module_related_frame_notes_after_loading = 
	    STATIC_SYMBOL("FIX-MODULE-RELATED-FRAME-NOTES-AFTER-LOADING",
	    AB_package);
    temp_1 = adjoin(2,Qfix_module_related_frame_notes_after_loading,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_module_related_frame_notes_after_loading,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qfix_module_related_frame_notes_after_loading,
	    STATIC_FUNCTION(fix_module_related_frame_notes_after_loading,
	    NIL,FALSE,0,0));
    Qassure_all_charts_have_style = 
	    STATIC_SYMBOL("ASSURE-ALL-CHARTS-HAVE-STYLE",AB_package);
    temp_1 = adjoin(2,Qassure_all_charts_have_style,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qassure_all_charts_have_style,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qassure_all_charts_have_style,
	    STATIC_FUNCTION(assure_all_charts_have_style,NIL,FALSE,0,0));
    Qensure_connections_have_frames_if_necessary = 
	    STATIC_SYMBOL("ENSURE-CONNECTIONS-HAVE-FRAMES-IF-NECESSARY",
	    AB_package);
    temp_1 = adjoin(2,Qensure_connections_have_frames_if_necessary,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qensure_connections_have_frames_if_necessary,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qensure_connections_have_frames_if_necessary,
	    STATIC_FUNCTION(ensure_connections_have_frames_if_necessary,
	    NIL,FALSE,0,0));
    Qeliminate_procedure_invocation_frame_notes = 
	    STATIC_SYMBOL("ELIMINATE-PROCEDURE-INVOCATION-FRAME-NOTES",
	    AB_package);
    temp_1 = adjoin(2,Qeliminate_procedure_invocation_frame_notes,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qeliminate_procedure_invocation_frame_notes,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    list_constant_14 = STATIC_CONS(Qprocedure_invocation,Qnil);
    SET_SYMBOL_FUNCTION(Qeliminate_procedure_invocation_frame_notes,
	    STATIC_FUNCTION(eliminate_procedure_invocation_frame_notes,NIL,
	    FALSE,0,0));
    Qfix_possible_non_symbols_in_g2_user_mode = 
	    STATIC_SYMBOL("FIX-POSSIBLE-NON-SYMBOLS-IN-G2-USER-MODE",
	    AB_package);
    temp_1 = adjoin(2,Qfix_possible_non_symbols_in_g2_user_mode,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_possible_non_symbols_in_g2_user_mode,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_possible_non_symbols_in_g2_user_mode,
	    STATIC_FUNCTION(fix_possible_non_symbols_in_g2_user_mode,NIL,
	    FALSE,0,0));
    Qfix_icon_variables_alists_in_icon_attributes_plist = 
	    STATIC_SYMBOL("FIX-ICON-VARIABLES-ALISTS-IN-ICON-ATTRIBUTES-PLIST",
	    AB_package);
    temp_1 = adjoin(2,Qfix_icon_variables_alists_in_icon_attributes_plist,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_icon_variables_alists_in_icon_attributes_plist,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_icon_variables_alists_in_icon_attributes_plist,
	    STATIC_FUNCTION(fix_icon_variables_alists_in_icon_attributes_plist,
	    NIL,FALSE,0,0));
    Qcenter_workspace_background_images = 
	    STATIC_SYMBOL("CENTER-WORKSPACE-BACKGROUND-IMAGES",AB_package);
    temp_1 = adjoin(2,Qcenter_workspace_background_images,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qcenter_workspace_background_images,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qcenter_workspace_background_images,
	    STATIC_FUNCTION(center_workspace_background_images,NIL,FALSE,0,0));
    Qcheck_insert_action_duplicate_element_flag = 
	    STATIC_SYMBOL("CHECK-INSERT-ACTION-DUPLICATE-ELEMENT-FLAG",
	    AB_package);
    temp_1 = adjoin(2,Qcheck_insert_action_duplicate_element_flag,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qcheck_insert_action_duplicate_element_flag,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qcheck_insert_action_duplicate_element_flag,
	    STATIC_FUNCTION(check_insert_action_duplicate_element_flag,NIL,
	    FALSE,0,0));
    Qcheck_new_get_connection_vertex_behavior_flag = 
	    STATIC_SYMBOL("CHECK-NEW-GET-CONNECTION-VERTEX-BEHAVIOR-FLAG",
	    AB_package);
    temp_1 = adjoin(2,Qcheck_new_get_connection_vertex_behavior_flag,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qcheck_new_get_connection_vertex_behavior_flag,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qcheck_new_get_connection_vertex_behavior_flag,
	    STATIC_FUNCTION(check_new_get_connection_vertex_behavior_flag,
	    NIL,FALSE,0,0));
    Qcheck_print_means_print_to_server_in_configurations = 
	    STATIC_SYMBOL("CHECK-PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS",
	    AB_package);
    temp_1 = adjoin(2,Qcheck_print_means_print_to_server_in_configurations,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qcheck_print_means_print_to_server_in_configurations,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    list_constant_22 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)7L),list_constant_22);
    SET_SYMBOL_FUNCTION(Qcheck_print_means_print_to_server_in_configurations,
	    STATIC_FUNCTION(check_print_means_print_to_server_in_configurations,
	    NIL,FALSE,0,0));
    Qcheck_inconsistent_behavior_of_move_in_configurations = 
	    STATIC_SYMBOL("CHECK-INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS",
	    AB_package);
    temp_1 = adjoin(2,
	    Qcheck_inconsistent_behavior_of_move_in_configurations,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,
	    Qcheck_inconsistent_behavior_of_move_in_configurations,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qcheck_inconsistent_behavior_of_move_in_configurations,
	    STATIC_FUNCTION(check_inconsistent_behavior_of_move_in_configurations,
	    NIL,FALSE,0,0));
    Qupdate_representations_of_configuration_grammar = 
	    STATIC_SYMBOL("UPDATE-REPRESENTATIONS-OF-CONFIGURATION-GRAMMAR",
	    AB_package);
    temp_1 = adjoin(2,Qupdate_representations_of_configuration_grammar,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qupdate_representations_of_configuration_grammar,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_representations_of_configuration_grammar,
	    STATIC_FUNCTION(update_representations_of_configuration_grammar,
	    NIL,FALSE,0,0));
    Qupdate_representations_of_class_specific_attributes_grammar = 
	    STATIC_SYMBOL("UPDATE-REPRESENTATIONS-OF-CLASS-SPECIFIC-ATTRIBUTES-GRAMMAR",
	    AB_package);
    temp_1 = adjoin(2,
	    Qupdate_representations_of_class_specific_attributes_grammar,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,
	    Qupdate_representations_of_class_specific_attributes_grammar,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    list_constant_16 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)4L),
	    FIX((SI_Long)0L),Qalpha_or_beta,string_constant_59);
    SET_SYMBOL_FUNCTION(Qupdate_representations_of_class_specific_attributes_grammar,
	    STATIC_FUNCTION(update_representations_of_class_specific_attributes_grammar,
	    NIL,FALSE,0,0));
    Qupdate_representations_of_default_overrides_grammar = 
	    STATIC_SYMBOL("UPDATE-REPRESENTATIONS-OF-DEFAULT-OVERRIDES-GRAMMAR",
	    AB_package);
    temp_1 = adjoin(2,Qupdate_representations_of_default_overrides_grammar,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qupdate_representations_of_default_overrides_grammar,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qupdate_representations_of_default_overrides_grammar,
	    STATIC_FUNCTION(update_representations_of_default_overrides_grammar,
	    NIL,FALSE,0,0));
    Qupdate_representations_of_initial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("UPDATE-REPRESENTATIONS-OF-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",
	    AB_package);
    temp_1 = adjoin(2,
	    Qupdate_representations_of_initial_value_of_variable_or_parameter,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,
	    Qupdate_representations_of_initial_value_of_variable_or_parameter,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_representations_of_initial_value_of_variable_or_parameter,
	    STATIC_FUNCTION(update_representations_of_initial_value_of_variable_or_parameter,
	    NIL,FALSE,0,0));
    Qremove_bogus_stubs_on_frames_in_attributes = 
	    STATIC_SYMBOL("REMOVE-BOGUS-STUBS-ON-FRAMES-IN-ATTRIBUTES",
	    AB_package);
    temp_1 = adjoin(2,Qremove_bogus_stubs_on_frames_in_attributes,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qremove_bogus_stubs_on_frames_in_attributes,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_bogus_stubs_on_frames_in_attributes,
	    STATIC_FUNCTION(remove_bogus_stubs_on_frames_in_attributes,NIL,
	    FALSE,0,0));
    Qfix_kb_workspaces_that_might_be_too_big = 
	    STATIC_SYMBOL("FIX-KB-WORKSPACES-THAT-MIGHT-BE-TOO-BIG",
	    AB_package);
    temp_1 = adjoin(2,Qfix_kb_workspaces_that_might_be_too_big,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfix_kb_workspaces_that_might_be_too_big,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qfix_kb_workspaces_that_might_be_too_big,
	    STATIC_FUNCTION(fix_kb_workspaces_that_might_be_too_big,NIL,
	    FALSE,0,0));
    Qdelete_connection_frames_without_connection_structures = 
	    STATIC_SYMBOL("DELETE-CONNECTION-FRAMES-WITHOUT-CONNECTION-STRUCTURES",
	    AB_package);
    temp_1 = adjoin(2,
	    Qdelete_connection_frames_without_connection_structures,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,
	    Qdelete_connection_frames_without_connection_structures,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qdelete_connection_frames_without_connection_structures,
	    STATIC_FUNCTION(delete_connection_frames_without_connection_structures,
	    NIL,FALSE,0,0));
    Qfixup_all_author_or_authors = 
	    STATIC_SYMBOL("FIXUP-ALL-AUTHOR-OR-AUTHORS",AB_package);
    temp_1 = adjoin(2,Qfixup_all_author_or_authors,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfixup_all_author_or_authors,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfixup_all_author_or_authors,
	    STATIC_FUNCTION(fixup_all_author_or_authors,NIL,FALSE,0,0));
    Qfixup_all_digital_clocks = STATIC_SYMBOL("FIXUP-ALL-DIGITAL-CLOCKS",
	    AB_package);
    temp_1 = adjoin(2,Qfixup_all_digital_clocks,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qfixup_all_digital_clocks,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qdigital_clock = STATIC_SYMBOL("DIGITAL-CLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qfixup_all_digital_clocks,
	    STATIC_FUNCTION(fixup_all_digital_clocks,NIL,FALSE,0,0));
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qminimum_width = STATIC_SYMBOL("MINIMUM-WIDTH",AB_package);
    Qminimum_height = STATIC_SYMBOL("MINIMUM-HEIGHT",AB_package);
    Qfont = STATIC_SYMBOL("FONT",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)6L,Qline_color,
	    Qbackground_color,Qborder_color,Qminimum_width,Qminimum_height,
	    Qfont);
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    Qmaybe_normalize_workspace_edges = 
	    STATIC_SYMBOL("MAYBE-NORMALIZE-WORKSPACE-EDGES",AB_package);
    temp_1 = adjoin(2,Qmaybe_normalize_workspace_edges,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qmaybe_normalize_workspace_edges,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qmaybe_normalize_workspace_edges,
	    STATIC_FUNCTION(maybe_normalize_workspace_edges,NIL,FALSE,0,0));
    Qreset_default_window_style_if_needed = 
	    STATIC_SYMBOL("RESET-DEFAULT-WINDOW-STYLE-IF-NEEDED",AB_package);
    temp_1 = adjoin(2,Qreset_default_window_style_if_needed,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qreset_default_window_style_if_needed,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    Qdefault_window_style = STATIC_SYMBOL("DEFAULT-WINDOW-STYLE",AB_package);
    Qg2_5_dot_x = STATIC_SYMBOL("G2-5.X",AB_package);
    SET_SYMBOL_FUNCTION(Qreset_default_window_style_if_needed,
	    STATIC_FUNCTION(reset_default_window_style_if_needed,NIL,FALSE,
	    0,0));
    Qdelete_bad_connection_structures = 
	    STATIC_SYMBOL("DELETE-BAD-CONNECTION-STRUCTURES",AB_package);
    temp_1 = adjoin(2,Qdelete_bad_connection_structures,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qdelete_bad_connection_structures,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    string_constant_56 = STATIC_STRING("s");
    string_constant_57 = STATIC_STRING("KB");
    string_constant_58 = 
	    STATIC_STRING("Cleared ~d unattached connection~a from ~a.");
    SET_SYMBOL_FUNCTION(Qdelete_bad_connection_structures,
	    STATIC_FUNCTION(delete_bad_connection_structures,NIL,FALSE,0,0));
    Qupgrade_block_connections_to_connections_v2 = 
	    STATIC_SYMBOL("UPGRADE-BLOCK-CONNECTIONS-TO-CONNECTIONS-V2",
	    AB_package);
    temp_1 = adjoin(2,Qupgrade_block_connections_to_connections_v2,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qupgrade_block_connections_to_connections_v2,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qupgrade_block_connections_to_connections_v2,
	    STATIC_FUNCTION(upgrade_block_connections_to_connections_v2,
	    NIL,FALSE,0,0));
    Qclassic_kbs_prefer_classic_editor = 
	    STATIC_SYMBOL("CLASSIC-KBS-PREFER-CLASSIC-EDITOR",AB_package);
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_editor,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_editor,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qeditor_parameters = STATIC_SYMBOL("EDITOR-PARAMETERS",AB_package);
    Qprefer_native_editor = STATIC_SYMBOL("PREFER-NATIVE-EDITOR",AB_package);
    SET_SYMBOL_FUNCTION(Qclassic_kbs_prefer_classic_editor,
	    STATIC_FUNCTION(classic_kbs_prefer_classic_editor,NIL,FALSE,0,0));
    Qclassic_kbs_prefer_classic_ui_features = 
	    STATIC_SYMBOL("CLASSIC-KBS-PREFER-CLASSIC-UI-FEATURES",AB_package);
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_ui_features,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_ui_features,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qlogbook_parameters = STATIC_SYMBOL("LOGBOOK-PARAMETERS",AB_package);
    Qprefer_native_logbook = STATIC_SYMBOL("PREFER-NATIVE-LOGBOOK",AB_package);
    Qmessage_board_parameters = STATIC_SYMBOL("MESSAGE-BOARD-PARAMETERS",
	    AB_package);
    Qprefer_native_message_board = 
	    STATIC_SYMBOL("PREFER-NATIVE-MESSAGE-BOARD",AB_package);
    Qprefer_native_login_dialog = 
	    STATIC_SYMBOL("PREFER-NATIVE-LOGIN-DIALOG",AB_package);
    SET_SYMBOL_FUNCTION(Qclassic_kbs_prefer_classic_ui_features,
	    STATIC_FUNCTION(classic_kbs_prefer_classic_ui_features,NIL,
	    FALSE,0,0));
    Qclassic_kbs_prefer_classic_selection_highlighting = 
	    STATIC_SYMBOL("CLASSIC-KBS-PREFER-CLASSIC-SELECTION-HIGHLIGHTING",
	    AB_package);
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_selection_highlighting,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qclassic_kbs_prefer_classic_selection_highlighting,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    Qdrawing_parameters = STATIC_SYMBOL("DRAWING-PARAMETERS",AB_package);
    Qshow_selection_handles = STATIC_SYMBOL("SHOW-SELECTION-HANDLES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qclassic_kbs_prefer_classic_selection_highlighting,
	    STATIC_FUNCTION(classic_kbs_prefer_classic_selection_highlighting,
	    NIL,FALSE,0,0));
    Qcheck_ignore_snap_grid_in_transfer_operations = 
	    STATIC_SYMBOL("CHECK-IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS",
	    AB_package);
    temp_1 = adjoin(2,Qcheck_ignore_snap_grid_in_transfer_operations,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_1;
    temp_1 = adjoin(2,Qcheck_ignore_snap_grid_in_transfer_operations,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_1;
    SET_SYMBOL_FUNCTION(Qcheck_ignore_snap_grid_in_transfer_operations,
	    STATIC_FUNCTION(check_ignore_snap_grid_in_transfer_operations,
	    NIL,FALSE,0,0));
}
