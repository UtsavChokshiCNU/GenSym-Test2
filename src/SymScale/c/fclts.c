/* fclts.c
 * Input file:  facilities.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "fclts.h"


static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* WORKSPACE-CAN-BE-HIDDEN? */
Object workspace_can_be_hidden_qm(workspace)
    Object workspace;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(119,0);
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Non_kb_workspace_class_description,(SI_Long)18L));
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
    if (temp) {
	temp_1 = get_lookup_slot_value_given_default(workspace,
		Qname_or_names_for_frame,Nil);
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Logbook_page_class_description,(SI_Long)18L));
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
		return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(T);
}

static Object Qstore_hand_created_module_information_if_appropriate;  /* store-hand-created-module-information-if-appropriate */

static Object Qdelete_hand_created_module_information_if_appropriate;  /* delete-hand-created-module-information-if-appropriate */

static Object Qtop_level_kb_module_qm;  /* top-level-kb-module? */

static Object Qdelete_module_information_if_unspecified_module;  /* delete-module-information-if-unspecified-module */

/* HANDLE-CREATE-NEW-MODULE-WINDOW-MENU-CHOICE */
Object handle_create_new_module_window_menu_choice(x_in_window,y_in_window)
    Object x_in_window, y_in_window;
{
    Object new_module_information;

    x_note_fn_call(119,1);
    new_module_information = make_system_frame(Qmodule_information);
    put_up_attributes_table(3,new_module_information,x_in_window,y_in_window);
    establish_next_workstation_context_continuation(Nil,
	    Qstore_hand_created_module_information_if_appropriate,
	    slot_value_list_2(new_module_information,
	    copy_frame_serial_number(ISVREF(new_module_information,
	    (SI_Long)3L))),
	    Qdelete_hand_created_module_information_if_appropriate);
    enter_editing_context(2,new_module_information,Qtop_level_kb_module_qm);
    return VALUES_1(Qdelete_module_information_if_unspecified_module);
}

Object Use_new_load_kb_qm = UNBOUND;

static Object list_constant;       /* # */

/* HANDLE-FILE-RELATED-WINDOW-MENU-CHOICE */
Object handle_file_related_window_menu_choice(choice_symbol)
    Object choice_symbol;
{
    x_note_fn_call(119,2);
    if (native_file_dialog_p(Current_workstation_window) && 
	    memq_function(choice_symbol,list_constant))
	return native_handle_file_related_window_menu_choice(choice_symbol);
    else
	return classic_handle_file_related_window_menu_choice(choice_symbol);
}

static Object Qload_kb;            /* load-kb */

static Object Qmerge_kb;           /* merge-kb */

static Object Qdelete_frame_after_checking_serial_number_with_list;  /* delete-frame-after-checking-serial-number-with-list */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* CLASSIC-HANDLE-FILE-RELATED-WINDOW-MENU-CHOICE */
Object classic_handle_file_related_window_menu_choice(choice_symbol)
    Object choice_symbol;
{
    Object title_qm, symbolic_file_type_qm, inconsistent_so_save_all_qm;
    Object module_case_qm, temp, command_verb_string_qm, comment_string_qm;
    Object command_frame;
    Object result;

    x_note_fn_call(119,3);
    result = preflight_file_related_window_menu_choice(choice_symbol);
    MVS_7(result,title_qm,symbolic_file_type_qm,
	    inconsistent_so_save_all_qm,module_case_qm,temp,
	    command_verb_string_qm,comment_string_qm);
    if ( !TRUEP(title_qm));
    else if (Use_new_load_kb_qm && (EQ(choice_symbol,Qload_kb) || 
	    EQ(choice_symbol,Qmerge_kb))) {
	command_frame = 
		make_and_set_up_kb_load_file_command(EQ(choice_symbol,
		Qmerge_kb) ? T : Nil);
	establish_next_workstation_context_continuation(Nil,Nil,
		gensym_list_2(command_frame,
		copy_frame_serial_number(Current_frame_serial_number)),
		Qdelete_frame_after_checking_serial_number_with_list);
	enter_editing_context(2,command_frame,Qbox_translation_and_text);
    }
    else {
	temp = command_verb_string_qm;
	if (temp);
	else
	    temp = title_qm;
	handle_file_command(4,temp,symbolic_file_type_qm,
		inconsistent_so_save_all_qm,module_case_qm);
    }
    if (command_verb_string_qm)
	reclaim_text_string(command_verb_string_qm);
    if (comment_string_qm)
	return reclaim_text_string(comment_string_qm);
    else
	return VALUES_1(Nil);
}

static Object Qsave_kb;            /* save-kb */

static Object Qwrite_g2_stats;     /* write-g2-stats */

static Object string_constant;     /* "You cannot do file commands other than Save KB or Write G2 Stats while running." */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object Qconnect_to_foreign_image;  /* connect-to-foreign-image */

static Object array_constant_2;    /* # */

static Object Qforeign_image;      /* foreign-image */

static Object Qdisconnect_from_foreign_image;  /* disconnect-from-foreign-image */

static Object array_constant_3;    /* # */

static Object Qload_attribute_file;  /* load-attribute-file */

static Object array_constant_4;    /* # */

static Object Qattribute;          /* attribute */

static Object array_constant_5;    /* # */

static Object Qstatistics;         /* statistics */

static Object string_constant_1;   /* "Since this KB is not consistently modularized, you may ~
				    *            only save the KB in a single file!"
				    */

static Object string_constant_2;   /* "WARNING: since this KB is not consistently ~
				    *            ?   modularized, you may only save the KB in a single file!  ~
				    *                    See logbook messages for further information."
				    */

static Object string_constant_3;   /* "{Comment: ~a}~%~%Save current KB as" */

static Object array_constant_6;    /* # */

static Object string_constant_4;   /* "Save module ~A as" */

static Object Qsave_in_clear_text_by_default;  /* save-in-clear-text-by-default */

static Object Qxml;                /* xml */

static Object array_constant_7;    /* # */

static Object Qsave_module;        /* save-module */

static Object Qsource_code_control_update_file;  /* source-code-control-update-file */

static Object array_constant_8;    /* # */

static Object Qsource_control;     /* source-control */

static Object Qsource_code_control_edit_file;  /* source-code-control-edit-file */

static Object array_constant_9;    /* # */

static Object Qsource_code_control_unedit_file;  /* source-code-control-unedit-file */

static Object array_constant_10;   /* # */

static Object Qsource_code_control_commit_file;  /* source-code-control-commit-file */

static Object array_constant_11;   /* # */

static Object Qsource_code_control_revert_file;  /* source-code-control-revert-file */

static Object array_constant_12;   /* # */

/* PREFLIGHT-FILE-RELATED-WINDOW-MENU-CHOICE */
Object preflight_file_related_window_menu_choice(choice_symbol)
    Object choice_symbol;
{
    Object comment_string, command_verb_string, write_symbols_parsably_qm;
    Object module, symbolic_file_type;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,4);
    if (System_is_running &&  !EQ(choice_symbol,Qsave_kb) &&  
	    !EQ(choice_symbol,Qwrite_g2_stats)) {
	notify_user(1,string_constant);
	return VALUES_1(Nil);
    }
    if (EQ(choice_symbol,Qload_kb))
	return VALUES_1(array_constant);
    else if (EQ(choice_symbol,Qmerge_kb))
	return VALUES_1(array_constant_1);
    else if (EQ(choice_symbol,Qconnect_to_foreign_image))
	return VALUES_2(array_constant_2,Qforeign_image);
    else if (EQ(choice_symbol,Qdisconnect_from_foreign_image))
	return VALUES_2(array_constant_3,Qforeign_image);
    else if (EQ(choice_symbol,Qload_attribute_file))
	return VALUES_2(array_constant_4,Qattribute);
    else if (EQ(choice_symbol,Qwrite_g2_stats))
	return VALUES_2(array_constant_5,Qstatistics);
    else if (EQ(choice_symbol,Qsave_kb)) {
	if (check_savability_of_kb_in_terms_of_modularity(0)) {
	    notify_user(1,string_constant_1);
	    comment_string = tformat_text_string(1,string_constant_2);
	    command_verb_string = tformat_text_string(2,string_constant_3,
		    comment_string);
	    return VALUES_7(array_constant_6,Nil,T,Nil,Nil,
		    command_verb_string,comment_string);
	}
	else if (get_slot_value_function(Module_information,
		Qtop_level_kb_module_qm,Nil)) {
	    write_symbols_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		    0);
	      module = get_slot_value_function(Module_information,
		      Qtop_level_kb_module_qm,Nil);
	      command_verb_string = tformat_text_string(2,
		      string_constant_4,module);
	      symbolic_file_type = 
		      get_slot_value_if_any_function(get_saving_parameters(module),
		      Qsave_in_clear_text_by_default,Nil) &&  
		      !TRUEP(module_contains_text_stripped_frames_p(module)) 
		      ? Qxml : Nil;
	      result = VALUES_6(array_constant_7,symbolic_file_type,Nil,T,
		      Qsave_module,command_verb_string);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(array_constant_6);
    }
    else if (EQ(choice_symbol,Qsource_code_control_update_file))
	return VALUES_2(array_constant_8,Qsource_control);
    else if (EQ(choice_symbol,Qsource_code_control_edit_file))
	return VALUES_2(array_constant_9,Qsource_control);
    else if (EQ(choice_symbol,Qsource_code_control_unedit_file))
	return VALUES_2(array_constant_10,Qsource_control);
    else if (EQ(choice_symbol,Qsource_code_control_commit_file))
	return VALUES_2(array_constant_11,Qsource_control);
    else if (EQ(choice_symbol,Qsource_code_control_revert_file))
	return VALUES_2(array_constant_12,Qsource_control);
    else
	return VALUES_1(Nil);
}

/* G2-ABORT-CALLBACK-USERDEFINE */
Object g2_abort_callback_userdefine(callback_user_spec)
    Object callback_user_spec;
{
    x_note_fn_call(119,5);
    return VALUES_1(Nil);
}

Object Native_load_kb_file_dialog_buttons = UNBOUND;

Object Native_save_module_file_dialog_buttons = UNBOUND;

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

/* COMPUTE-PATHNAME-FILTER-FOR-FILE-TYPE */
Object compute_pathname_filter_for_file_type varargs_1(int, n)
{
    Object symbolic_file_type_qm;
    Object use_xml_mask_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,6);
    INIT_ARGS_nonrelocating();
    symbolic_file_type_qm = REQUIRED_ARG_nonrelocating();
    use_xml_mask_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(symbolic_file_type_qm,Qxml))
	temp = gensym_cons_1(list_constant_1,Nil);
    else if (EQ(symbolic_file_type_qm,Qforeign_image))
	temp = gensym_cons_1(list_constant_2,Nil);
    else if (EQ(symbolic_file_type_qm,Qattribute) || 
	    EQ(symbolic_file_type_qm,Qstatistics))
	temp = gensym_cons_1(list_constant_3,Nil);
    else if (EQ(symbolic_file_type_qm,Qlog))
	temp = gensym_cons_1(list_constant_4,Nil);
    else
	temp = nconc2(gensym_cons_1(list_constant_5,Nil),use_xml_mask_qm ? 
		gensym_cons_1(list_constant_6,Nil) : Nil);
    return VALUES_1(nconc2(temp,gensym_cons_1(list_constant_7,Nil)));
}

/* COMPUTE-LIST-OF-MODULES-PUTTING-TOP-IN-FRONT */
Object compute_list_of_modules_putting_top_in_front()
{
    Object module_information_table, ab_loop_list_, module_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object list_of_modules_in_random_order_sans_top, top_level_module_name_qm;

    x_note_fn_call(119,7);
    module_information_table = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module_information_table = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_qm = ISVREF(module_information_table,(SI_Long)23L);
    if (module_qm &&  !EQ(module_information_table,Module_information)) {
	ab_loopvar__2 = gensym_cons_1(module_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    list_of_modules_in_random_order_sans_top = ab_loopvar_;
    goto end_1;
    list_of_modules_in_random_order_sans_top = Qnil;
  end_1:;
    top_level_module_name_qm = ISVREF(Module_information,(SI_Long)23L);
    if (top_level_module_name_qm)
	return gensym_cons_1(top_level_module_name_qm,
		list_of_modules_in_random_order_sans_top);
    else
	return VALUES_1(list_of_modules_in_random_order_sans_top);
}

/* INTERESTING-DIRECTORIES */
Object interesting_directories()
{
    Object buffer, count_1, temp;
    SI_Long buflen;

    x_note_fn_call(119,8);
    buflen = (SI_Long)1024L;
    buffer = obtain_text_string(FIX(buflen));
    count_1 = c_get_places_bar(buffer,FIX(buflen));
    temp = IFIX(count_1) > (SI_Long)0L ? double_nul_string_to_list(buffer) 
	    : default_interesting_directories();
    reclaim_text_string(buffer);
    return VALUES_1(temp);
}

static Object array_constant_13;   /* # */

static Object Qmodule_search_path;  /* module-search-path */

static Object Qstring_equalw;      /* string-equalw */

/* DEFAULT-INTERESTING-DIRECTORIES */
Object default_interesting_directories()
{
    Object kb_gp_qm, home_qm, homedir_qm, dir, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, modules, temp, dirs, result_1;
    Object directories;

    x_note_fn_call(119,9);
    kb_gp_qm = current_kb_directory_qm();
    home_qm = get_gensym_environment_variable(array_constant_13);
    homedir_qm = home_qm ? coerce_to_directory_string(home_qm) : Nil;
    dir = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(Server_parameters,
	    Qmodule_search_path,Nil);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dir = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(copy_text_string(dir),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    modules = ab_loopvar_;
    goto end_1;
    modules = Qnil;
  end_1:;
    temp = homedir_qm ? gensym_cons_1(homedir_qm,Nil) : Nil;
    dirs = nconc2(temp,nconc2(kb_gp_qm ? gensym_cons_1(gensym_namestring(1,
	    kb_gp_qm),Nil) : Nil,modules));
    dir = Nil;
    ab_loop_list_ = dirs;
    result_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    dir = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(member(4,dir,result_1,Ktest,
		SYMBOL_FUNCTION(Qstring_equalw)))) {
	ab_loopvar__1 = gensym_cons_1(copy_text_string(dir),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop_1;
  end_loop_1:
    directories = result_1;
    goto end_2;
    directories = Qnil;
  end_2:;
    reclaim_gensym_tree_with_text_strings(dirs);
    if (kb_gp_qm)
	reclaim_gensym_pathname(kb_gp_qm);
    if (home_qm)
	reclaim_text_string(home_qm);
    return VALUES_1(directories);
}

/* C-GET-PLACES-BAR */
Object c_get_places_bar(buffer,buflen)
    Object buffer, buflen;
{
    Object temp;

    x_note_fn_call(119,10);
    temp = FIX(g2ext_get_places_bar(UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),
	    IFIX(buflen)));
    return VALUES_1(temp);
}

/* COERCE-TO-DIRECTORY-STRING */
Object coerce_to_directory_string(pathname_1)
    Object pathname_1;
{
    Object gensym_pathname_1, temp;

    x_note_fn_call(119,11);
    gensym_pathname_1 = gensym_file_as_directory(pathname_1);
    if (gensym_pathname_1);
    else
	gensym_pathname_1 = gensym_parse_namestring_function(pathname_1,
		Nil,Nil);
    temp = gensym_namestring(1,gensym_pathname_1);
    reclaim_gensym_pathname(gensym_pathname_1);
    return VALUES_1(temp);
}

static Object Qtelewindows;        /* telewindows */

static Object Qplaces;             /* places */

static Object Qdrives;             /* drives */

/* POST-FILE-DIALOG */
Object post_file_dialog varargs_1(int, n)
{
    Object gensym_window, handle, operation, flags, caption, initial_pathname;
    Object default_extension, filter, buttons;
    Object places, icp_output_port_qm, current_icp_port, current_icp_socket;
    Object temp, disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, dirs, places_values, drives_values;
    Object plist, dir, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    SI_Long places_buflen, drives_buflen;
    char server_dialog_p;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(12);
    Object result;

    x_note_fn_call(119,12);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    handle = REQUIRED_ARG_nonrelocating();
    operation = REQUIRED_ARG_nonrelocating();
    flags = REQUIRED_ARG_nonrelocating();
    caption = REQUIRED_ARG_nonrelocating();
    initial_pathname = REQUIRED_ARG_nonrelocating();
    default_extension = REQUIRED_ARG_nonrelocating();
    filter = REQUIRED_ARG_nonrelocating();
    buttons = REQUIRED_ARG_nonrelocating();
    places = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
    if (icp_output_port_qm && 
	    icp_connection_open_p(ISVREF(icp_output_port_qm,(SI_Long)2L))) {
	current_icp_port = icp_output_port_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    if (FIXNUM_LT(Icp_window_protocol_supports_file_dialog_ex,
					    ISVREF(gensym_window,
					    (SI_Long)11L))) {
					server_dialog_p = (IFIX(flags) & 
						(SI_Long)2L) != (SI_Long)0L;
					if (server_dialog_p) {
					    dirs = 
						    copy_gensym_tree_with_text_strings(places);
					    if (dirs);
					    else
						dirs = 
							interesting_directories();
					}
					else
					    dirs = Nil;
					places_buflen = (SI_Long)1280L;
					places_values = 
						obtain_text_string(FIX(places_buflen));
					drives_buflen = (SI_Long)300L;
					drives_values = 
						obtain_text_string(FIX(drives_buflen));
					plist = Nil;
					if (windows_platform_p()) {
					    c_get_system_drives_list(drives_values,
						    FIX(drives_buflen));
					    c_get_system_special_folders(places_values,
						    FIX(places_buflen));
					    temp = 
						    double_nul_string_to_list(places_values);
					    plist = gensym_list_4(Qplaces,
						    temp,Qdrives,
						    double_nul_string_to_list(drives_values));
					}
					else if (dirs) {
					    dir = Nil;
					    ab_loop_list_ = dirs;
					    ab_loopvar_ = Nil;
					    ab_loopvar__1 = Nil;
					    ab_loopvar__2 = Nil;
					  next_loop:
					    if ( !TRUEP(ab_loop_list_))
						goto end_loop;
					    dir = M_CAR(ab_loop_list_);
					    ab_loop_list_ = 
						    M_CDR(ab_loop_list_);
					    ab_loopvar__2 = 
						    gensym_cons_1(coerce_to_directory_string(dir),
						    Nil);
					    if (ab_loopvar__1)
						M_CDR(ab_loopvar__1) = 
							ab_loopvar__2;
					    else
						ab_loopvar_ = ab_loopvar__2;
					    ab_loopvar__1 = ab_loopvar__2;
					    goto next_loop;
					  end_loop:
					    temp = ab_loopvar_;
					    goto end_1;
					    temp = Qnil;
					  end_1:;
					    plist = gensym_list_2(Qplaces,
						    temp);
					}
					else
					    plist = Nil;
					send_icp_file_dialog_ex(gensym_window,
						handle,operation,flags,
						caption,initial_pathname,
						default_extension,filter,
						buttons,plist);
					reclaim_gensym_tree_with_text_strings(dirs);
					temp = 
						reclaim_gensym_tree_with_text_strings(plist);
				    }
				    else
					temp = 
						send_icp_file_dialog(gensym_window,
						handle,operation,flags,
						caption,initial_pathname,
						default_extension,filter,
						buttons);
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				}
				result = VALUES_1(temp);
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
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

static Object Qcomment;            /* comment */

static Object Qtext;               /* text */

static Object Qmodule;             /* module */

static Object Qcombobox;           /* combobox */

static Object array_constant_14;   /* # */

static Object Qspecial_string;     /* special-string */

static Object list_constant_9;     /* # */

static Object array_constant_15;   /* # */

/* POST-NATIVE-FILE-DIALOG */
Object post_native_file_dialog(gensym_window,operation,title,
	    symbolic_file_type_qm,inconsistent_so_save_all_qm,
	    module_case_qm,comment_qm)
    Object gensym_window, operation, title, symbolic_file_type_qm;
    Object inconsistent_so_save_all_qm, module_case_qm, comment_qm;
{
    Object gensym_pathname_1, pathname_1, use_xml_filter_qm, filter, temp;
    Object basic_buttons, all_filename_qm, temp_1, buttons, savep;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, flags;

    x_note_fn_call(119,13);
    gensym_pathname_1 = 
	    get_pathname_for_file_command(symbolic_file_type_qm,
	    inconsistent_so_save_all_qm,module_case_qm,T);
    pathname_1 = gensym_namestring(1,gensym_pathname_1);
    use_xml_filter_qm = memq_function(operation,list_constant_8);
    filter = compute_pathname_filter_for_file_type(2,symbolic_file_type_qm,
	    use_xml_filter_qm);
    if (EQ(operation,Qload_kb) || EQ(operation,Qmerge_kb))
	temp = Native_load_kb_file_dialog_buttons;
    else if (EQ(operation,Qsave_module))
	temp = Native_save_module_file_dialog_buttons;
    else
	temp = Qnil;
    basic_buttons = copy_gensym_tree_with_text_strings(temp);
    all_filename_qm = module_case_qm ? 
	    get_pathname_for_file_command(symbolic_file_type_qm,T,Nil,T) : 
	    Qnil;
    temp = comment_qm ? gensym_cons_1(gensym_list_3(Qcomment,Qtext,
	    copy_text_string(comment_qm)),Nil) : Nil;
    if (module_case_qm) {
	temp_1 = gensym_list_3(Qmodule,Qcombobox,
		copy_wide_string(array_constant_14));
	temp_1 = gensym_cons_1(nconc2(temp_1,
		compute_list_of_modules_putting_top_in_front()),Nil);
    }
    else
	temp_1 = Nil;
    buttons = nconc2(temp,nconc2(temp_1,all_filename_qm ? nsubst(3,
	    os_pathname_nondirectory(all_filename_qm,G2_operating_system),
	    Qspecial_string,basic_buttons) : basic_buttons));
    savep = memq_function(operation,list_constant_9);
    gensymed_symbol = savep ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = 
	    server_and_client_share_file_system_p(gensym_window) ? 
	    (SI_Long)0L : (SI_Long)2L;
    gensymed_symbol_2 = IFIX(encode_pathname_os(G2_operating_system)) << 
	    (SI_Long)2L;
    flags = gensymed_symbol | gensymed_symbol_1 | gensymed_symbol_2;
    temp = ISVREF(gensym_pathname_1,(SI_Long)5L);
    if (temp);
    else
	temp = array_constant_15;
    post_file_dialog(9,gensym_window,FIX((SI_Long)123L),operation,
	    FIX(flags),title,pathname_1,temp,filter,buttons);
    if (all_filename_qm)
	reclaim_gensym_pathname(all_filename_qm);
    reclaim_gensym_tree_with_text_strings(buttons);
    reclaim_gensym_list_1(filter);
    reclaim_text_string(pathname_1);
    return reclaim_gensym_pathname(gensym_pathname_1);
}

/* NATIVE-HANDLE-FILE-RELATED-WINDOW-MENU-CHOICE */
Object native_handle_file_related_window_menu_choice(choice_symbol)
    Object choice_symbol;
{
    Object title_qm, symbolic_file_type_qm, inconsistent_so_save_all_qm;
    Object module_case_qm, new_operation_symbol_qm, command_verb_string_qm;
    Object comment_string_qm, temp, temp_1;
    Object result;

    x_note_fn_call(119,14);
    result = preflight_file_related_window_menu_choice(choice_symbol);
    MVS_7(result,title_qm,symbolic_file_type_qm,
	    inconsistent_so_save_all_qm,module_case_qm,
	    new_operation_symbol_qm,command_verb_string_qm,comment_string_qm);
    if (title_qm) {
	temp = Current_workstation_window;
	temp_1 = new_operation_symbol_qm;
	if (temp_1);
	else
	    temp_1 = choice_symbol;
	post_native_file_dialog(temp,temp_1,title_qm,symbolic_file_type_qm,
		inconsistent_so_save_all_qm,module_case_qm,comment_string_qm);
    }
    if (command_verb_string_qm)
	reclaim_text_string(command_verb_string_qm);
    if (comment_string_qm)
	return reclaim_text_string(comment_string_qm);
    else
	return VALUES_1(Nil);
}

static Object Qclass_format;       /* class-format */

static Object string_constant_5;   /* "~a" */

static Object Qdefault_text_cell_format;  /* default-text-cell-format */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_6;   /* "~a~a" */

static Object Knetwork_type;       /* :network-type */

static Object Ksecure_p;           /* :secure-p */

static Object array_constant_16;   /* # */

static Object string_constant_7;   /* "," */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qdefault_table_format;  /* default-table-format */

static Object Qstretch_new_image_planes_for_caption_p;  /* stretch-new-image-planes-for-caption-p */

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qab_slot_value;      /* slot-value */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* PUT-UP-TABLE-OF-NETWORK-INFO */
Object put_up_table_of_network_info()
{
    Object host_name, port_list, local_host_aliases_qm, temp, type_of_network;
    Object address, secure_p, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp_1, temp_2;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_3, workspace, new_wide_string, temp_4, temp_5;
    Object gensym_list_of_wide_strings, string_1, new_cons, svref_new_value;
    Object gensymed_symbol, short_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(119,15);
    result = get_raw_network_info();
    MVS_3(result,host_name,port_list,local_host_aliases_qm);
    temp =  !TRUEP(New_g2_classic_ui_p) ? 
	    slot_value_cons_1(slot_value_list_2(Nil,make_text_cell(2,
	    slot_value_cons_1(copy_text_string(host_name),Nil),
	    Qclass_format)),Nil) : Nil;
    type_of_network = Nil;
    address = Nil;
    secure_p = Nil;
    ab_loop_list_ = port_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_of_network = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    address = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    secure_p = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_2 = make_text_cell(2,slot_value_cons_1(tformat_text_string(2,
	    string_constant_5,type_of_network),Nil),Qdefault_text_cell_format);
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
	      temp_1 = address;
	      tformat(3,string_constant_6,temp_1,secure_icp_string(4,
		      Knetwork_type,type_of_network,Ksecure_p,secure_p));
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = slot_value_cons_1(slot_value_list_2(temp_2,
	    make_text_cell(2,slot_value_cons_1(temp_1,Nil),
	    Qdefault_text_cell_format)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    if (local_host_aliases_qm) {
	temp_3 = make_text_cell(2,
		slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_16,
		FIX((SI_Long)7L)),Nil),Qdefault_text_cell_format);
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  write_symbol_list(2,local_host_aliases_qm,string_constant_7);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp_1 = slot_value_cons_1(slot_value_list_2(temp_3,
		make_text_cell(2,slot_value_cons_1(temp_1,Nil),
		Qdefault_text_cell_format)),Nil);
    }
    else
	temp_1 = Nil;
    workspace = make_workspace(4,Qtemporary_workspace,Nil,
	    make_or_reformat_table(3,nconc2(temp,nconc2(temp_2,temp_1)),
	    Qdefault_table_format,Nil),FIX((SI_Long)1L));
    if (New_g2_classic_ui_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,
		    Qstretch_new_image_planes_for_caption_p);
	set_lookup_slot_value_1(workspace,
		Qstretch_new_image_planes_for_caption_p,T);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qtitle_bar_caption_text);
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  current_wide_string = new_wide_string;
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
		  tformat(2,string_constant_5,host_name);
		  temp_4 = Current_wide_string;
		  temp_5 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_4));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(temp_5) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp_4,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(temp_5) >>  -  - 
			  (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp_4,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp_4,IFIX(temp_5),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list_ = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	string_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_4 = Available_slot_value_conses_vector;
	    temp_5 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_4,temp_5) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_4 = Available_slot_value_conses_tail_vector;
		temp_5 = Current_thread_index;
		SVREF(temp_4,temp_5) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_4 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol) = temp_4;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_4 = Available_slot_value_conses_vector;
	    temp_5 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_4,temp_5) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_4 = Available_slot_value_conses_tail_vector;
		temp_5 = Current_thread_index;
		SVREF(temp_4,temp_5) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp_4 = short_string;
	}
	else
	    temp_4 = string_1;
	M_CAR(gensymed_symbol) = temp_4;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
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
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
	set_lookup_slot_value_1(workspace,Qtitle_bar_caption_text,temp_1);
    }
    reclaim_raw_network_info(host_name,port_list);
    return put_workspace_on_pane_function(workspace,
	    Current_workstation_detail_pane,Qleft,Qtop,Nil,
	    FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

static Object Qworkspace;          /* workspace */

/* GET-WORKSPACE */
Object get_workspace(name)
    Object name;
{
    Object found_workspace_qm, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object workspace;
    char temp;
    Declare_special(1);

    x_note_fn_call(119,16);
    found_workspace_qm = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qworkspace);
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
      if ( !TRUEP(found_workspace_qm) && name_for_frame_p(name,workspace) 
	      && ( !TRUEP(Servicing_workstation_qm) || 
	      workspace_can_appear_on_workstation_p(workspace,
	      Current_workstation)))
	  found_workspace_qm = workspace;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(found_workspace_qm);
}

/* NEATLY-STACK-IMAGE-PLANES-IN-WINDOW */
Object neatly_stack_image_planes_in_window(gensym_window)
    Object gensym_window;
{
    Object pane, temp, top_plane;

    x_note_fn_call(119,17);
    pane = detail_pane(gensym_window);
    temp = ISVREF(pane,(SI_Long)5L);
    top_plane = CAR(temp);
    return neatly_stack_image_planes_in_pane(7,pane,Qleft,Qtop,
	    FIX(IFIX(ISVREF(top_plane,(SI_Long)6L)) + (SI_Long)25L),
	    FIX(IFIX(ISVREF(top_plane,(SI_Long)7L)) + (SI_Long)25L),
	    FIX((SI_Long)25L),FIX((SI_Long)25L));
}

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

/* NEATLY-STACK-IMAGE-PLANES-IN-PANE */
Object neatly_stack_image_planes_in_pane varargs_1(int, n)
{
    Object pane, left_or_right_qm, top_or_bottom_qm, x_in_window, y_in_window;
    Object delta_x_in_window, delta_y_in_window;
    Object workspace_class_qm, predicate_qm, image_plane, ab_loop_list_;
    Object workspace_qm, gensymed_symbol, sub_class_bit_vector;
    Object number_of_images, temp_1, temp_2;
    SI_Long ab_loopvar_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,18);
    INIT_ARGS_nonrelocating();
    pane = REQUIRED_ARG_nonrelocating();
    left_or_right_qm = REQUIRED_ARG_nonrelocating();
    top_or_bottom_qm = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    delta_x_in_window = REQUIRED_ARG_nonrelocating();
    delta_y_in_window = REQUIRED_ARG_nonrelocating();
    workspace_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    predicate_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
    workspace_qm = Nil;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	temp =  !TRUEP(workspace_class_qm);
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(workspace_class_qm,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !TRUEP(predicate_qm) || FUNCALL_2(predicate_qm,image_plane,
	    workspace_qm) : TRUEP(Nil))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    number_of_images = FIX(ab_loopvar_);
    goto end_1;
    number_of_images = Qnil;
  end_1:;
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
    workspace_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	temp =  !TRUEP(workspace_class_qm);
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(workspace_class_qm,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !TRUEP(predicate_qm) || FUNCALL_2(predicate_qm,image_plane,
	    workspace_qm) : TRUEP(Nil)) {
	temp_1 = image_plane;
	gensymed_symbol_1 = IFIX(FIXNUM_ADD(x_in_window,
		FIXNUM_TIMES(FIXNUM_SUB1(number_of_images),
		delta_x_in_window)));
	if (EQ(left_or_right_qm,Qleft))
	    gensymed_symbol_2 = IFIX(ISVREF(image_plane,(SI_Long)15L));
	else if (EQ(left_or_right_qm,Qright))
	    gensymed_symbol_2 = IFIX(ISVREF(image_plane,(SI_Long)17L));
	else
	    gensymed_symbol_2 = IFIX(FIXNUM_ADD(ISVREF(image_plane,
		    (SI_Long)15L),ISVREF(image_plane,(SI_Long)17L))) >>  - 
		     - (SI_Long)1L;
	temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(FIXNUM_ADD(y_in_window,
		FIXNUM_TIMES(FIXNUM_SUB1(number_of_images),
		delta_y_in_window)));
	if (EQ(top_or_bottom_qm,Qtop))
	    gensymed_symbol_2 = IFIX(ISVREF(image_plane,(SI_Long)16L));
	else if (EQ(top_or_bottom_qm,Qbottom))
	    gensymed_symbol_2 = IFIX(ISVREF(image_plane,(SI_Long)18L));
	else
	    gensymed_symbol_2 = IFIX(FIXNUM_ADD(ISVREF(image_plane,
		    (SI_Long)16L),ISVREF(image_plane,(SI_Long)18L))) >>  - 
		     - (SI_Long)1L;
	move_image_plane(temp_1,temp_2,FIX(gensymed_symbol_1 - 
		gensymed_symbol_2));
	number_of_images = FIXNUM_SUB1(number_of_images);
    }
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* COMPUTE-MODULE-DELETION-CHOICES */
Object compute_module_deletion_choices()
{
    Object module_information_table, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_;

    x_note_fn_call(119,19);
    module_information_table = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module_information_table = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( ! !TRUEP(get_slot_value_function(module_information_table,
	    Qtop_level_kb_module_qm,Nil))) {
	ab_loopvar__2 = 
		slot_value_cons_1(get_slot_value_function(module_information_table,
		Qtop_level_kb_module_qm,Nil),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object string_constant_8;   /* "Delete this ~(~a~)?" */

static Object string_constant_9;   /* "Delete this ~(~a~), with its one subworkspace?" */

static Object string_constant_10;  /* "Delete this ~(~a~), with its ~D subworkspaces?" */

static Object Qdelete_frame_after_checking_serial_number;  /* delete-frame-after-checking-serial-number */

/* DELETE-WORKSPACE-FOR-USER */
Object delete_workspace_for_user varargs_1(int, n)
{
    Object workspace;
    Object last_mouse_x_in_window_qm, last_mouse_y_in_window_qm;
    Object sub_class_bit_vector, number_of_subworkspaces, gensymed_symbol_3;
    Object ab_queue_form_, ab_next_queue_element_, subblock, incff_1_arg;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,20);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    last_mouse_x_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    last_mouse_y_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Temporary_workspace_class_description,(SI_Long)18L));
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Category_instance_menu_workspace_class_description,
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
    if (temp);
    else
	temp = 
		TRUEP(workspace_subblocks_may_be_deleted_without_prompting_p(workspace));
    if (temp)
	return delete_frame(workspace);
    else {
	number_of_subworkspaces = FIX((SI_Long)0L);
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol_3;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	if (temp ? TRUEP(ISVREF(subblock,(SI_Long)18L)) : TRUEP(Nil)) {
	    incff_1_arg = length(ISVREF(subblock,(SI_Long)18L));
	    number_of_subworkspaces = FIXNUM_ADD(number_of_subworkspaces,
		    incff_1_arg);
	}
	goto next_loop;
      end_loop:
	if (IFIX(number_of_subworkspaces) == (SI_Long)0L)
	    temp_1 = string_constant_8;
	else if (IFIX(number_of_subworkspaces) == (SI_Long)1L)
	    temp_1 = string_constant_9;
	else
	    temp_1 = string_constant_10;
	temp_1 = tformat_text_string(3,temp_1,ISVREF(ISVREF(workspace,
		(SI_Long)1L),(SI_Long)1L),number_of_subworkspaces);
	enter_dialog(9,temp_1,Nil,Nil,
		Qdelete_frame_after_checking_serial_number,
		slot_value_list_2(workspace,
		copy_frame_serial_number(Current_frame_serial_number)),Nil,
		Nil,last_mouse_x_in_window_qm,last_mouse_y_in_window_qm);
	return VALUES_1(Qnil);
    }
}

static Object Qole_ghost;          /* ole-ghost */

/* BLOCK-MAY-BE-DELETED-WITHOUT-PROMPTING-P */
Object block_may_be_deleted_without_prompting_p(block)
    Object block;
{
    Object sub_class_bit_vector, temp_1, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(119,21);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
    temp_1 = temp ? ( !TRUEP(display_table_p(block)) ? T : Nil) : Nil;
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qole_ghost,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
		return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* WORKSPACE-SUBBLOCKS-MAY-BE-DELETED-WITHOUT-PROMPTING-P */
Object workspace_subblocks_may_be_deleted_without_prompting_p(workspace)
    Object workspace;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;

    x_note_fn_call(119,22);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    if ( !TRUEP(block_may_be_deleted_without_prompting_p(block)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qmessage_definition;  /* message-definition */

/* ITEM-DELETION-CAUSES-WORKSPACE-DELETION-P */
Object item_deletion_causes_workspace_deletion_p(item)
    Object item;
{
    Object temp, sub_class_bit_vector, class_name_qm, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object gensymed_symbol_3, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, scope_conses, ab_loopvar_, subclass, ab_loop_it_;
    Object ab_loopvar__1, instance;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,23);
    temp = ISVREF(item,(SI_Long)18L);
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	    class_name_qm = ISVREF(item,(SI_Long)20L);
	    if (SYMBOLP(class_name_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_name_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_name_qm) & 
			IFIX(Most_positive_fixnum);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol_3)) {
		    gensymed_symbol_3 = class_name_qm;
		    temp_2 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol_3 = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			    temp,gensymed_symbol_4);
		}
		global_properties = gensymed_symbol_3;
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		  next_loop_6:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_1 = TRUEP(resulting_value);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar_ = class_name_qm;
		subclass = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loop_it_ = Nil;
		  ab_loopvar_ = collect_subclasses(ab_loopvar_);
		next_loop_12:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_12;
		  temp = M_CAR(ab_loopvar_);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  subclass = temp;
		  temp = 
			  ISVREF(lookup_global_or_kb_specific_property_value(subclass,
			  Class_definition_gkbprop),(SI_Long)18L);
		  if (temp);
		  else {
		      temp_1 = EQ(ISVREF(ISVREF(item,(SI_Long)1L),
			      (SI_Long)1L),Qmessage_definition);
		      if (temp_1);
		      else {
			  skip_list = CDR(Symbol_properties_table);
			  key_value = class_name_qm;
			  key_hash_value = SXHASH_SYMBOL_1(class_name_qm) 
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
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp);
			  MVS_2(result,succ,marked);
			next_loop_15:
			  if ( !TRUEP(marked))
			      goto end_loop_14;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp);
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
			      goto end_5;
			  goto next_loop_14;
			end_loop_15:
			end_5:
			  level = level - (SI_Long)1L;
			  goto next_loop_13;
			end_loop_13:;
			  gensymed_symbol_3 = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			  if ( !TRUEP(gensymed_symbol_3)) {
			      gensymed_symbol_3 = class_name_qm;
			      temp_2 = Symbol_properties_table;
			      temp = 
				      FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
				      & IFIX(Most_positive_fixnum));
			      tail = 
				      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				      Nil);
			      head = 
				      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				      tail);
			      new_cons = 
				      ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index));
			      if (new_cons) {
				  svref_arg_1 = Available_lookup_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  svref_new_value = M_CDR(new_cons);
				  SVREF(svref_arg_1,svref_arg_2) = 
					  svref_new_value;
				  if ( 
					  !TRUEP(ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index)))) {
				      svref_arg_1 = 
					      Available_lookup_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(svref_arg_1,svref_arg_2) = Nil;
				  }
				  gensymed_symbol_4 = new_cons;
			      }
			      else
				  gensymed_symbol_4 = Nil;
			      if ( !TRUEP(gensymed_symbol_4))
				  gensymed_symbol_4 = 
					  replenish_lookup_cons_pool();
			      M_CAR(gensymed_symbol_4) = 
				      Qsymbol_properties_hash_table;
			      new_cons = 
				      ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index));
			      if (new_cons) {
				  svref_arg_1 = Available_lookup_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  svref_new_value = M_CDR(new_cons);
				  SVREF(svref_arg_1,svref_arg_2) = 
					  svref_new_value;
				  if ( 
					  !TRUEP(ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index)))) {
				      svref_arg_1 = 
					      Available_lookup_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(svref_arg_1,svref_arg_2) = Nil;
				  }
				  gensymed_symbol_5 = new_cons;
			      }
			      else
				  gensymed_symbol_5 = Nil;
			      if ( !TRUEP(gensymed_symbol_5))
				  gensymed_symbol_5 = 
					  replenish_lookup_cons_pool();
			      M_CAR(gensymed_symbol_5) = head;
			      M_CDR(gensymed_symbol_5) = tail;
			      inline_note_allocate_cons(gensymed_symbol_5,
				      Qlookup);
			      M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			      inline_note_allocate_cons(gensymed_symbol_4,
				      Qlookup);
			      gensymed_symbol_3 = 
				      set_skip_list_entry(temp_2,
				      FIX((SI_Long)31L),Qeq,Nil,T,
				      gensymed_symbol_3,temp,
				      gensymed_symbol_4);
			  }
			  global_properties = gensymed_symbol_3;
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
			next_loop_16:
			  if (level < ab_loop_bind_)
			      goto end_loop_16;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_17:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp);
			  MVS_2(result,succ,marked);
			next_loop_18:
			  if ( !TRUEP(marked))
			      goto end_loop_17;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp);
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
			      goto end_6;
			  goto next_loop_17;
			end_loop_18:
			end_6:
			  level = level - (SI_Long)1L;
			  goto next_loop_16;
			end_loop_16:;
			  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
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
			    next_loop_19:
			      if (level < ab_loop_bind_)
				  goto end_loop_19;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_20:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			    next_loop_21:
			      if ( !TRUEP(marked))
				  goto end_loop_20;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			      goto next_loop_21;
			    end_loop_20:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_7;
			      goto next_loop_20;
			    end_loop_21:
			    end_7:
			      level = level - (SI_Long)1L;
			      goto next_loop_19;
			    end_loop_19:;
			      kb_specific_value = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_specific_value);
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			  }
			  else
			      kb_specific_value = No_specific_property_value;
			  if ( !EQ(kb_specific_value,
				  No_specific_property_value))
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
			    next_loop_22:
			      if (level < ab_loop_bind_)
				  goto end_loop_22;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_23:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			    next_loop_24:
			      if ( !TRUEP(marked))
				  goto end_loop_23;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp);
			      MVS_2(result,succ,marked);
			      goto next_loop_24;
			    end_loop_23:
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
			      goto next_loop_23;
			    end_loop_24:
			    end_8:
			      level = level - (SI_Long)1L;
			      goto next_loop_22;
			    end_loop_22:;
			      resulting_value = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (resulting_value);
			      else
				  resulting_value = Nil;
			  }
			  gensymed_symbol_3 = resulting_value;
			  if (gensymed_symbol_3) {
			      sub_class_bit_vector = 
				      ISVREF(gensymed_symbol_3,(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Entity_class_description,
				      (SI_Long)18L));
			      sub_class_vector_index = 
				      superior_class_bit_number >>  -  - 
				      (SI_Long)3L;
			      if (sub_class_vector_index < 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					  {
				  gensymed_symbol = 
					  UBYTE_8_ISAREF_1(sub_class_bit_vector,
					  sub_class_vector_index);
				  gensymed_symbol_1 = (SI_Long)1L;
				  gensymed_symbol_2 = 
					  superior_class_bit_number & 
					  (SI_Long)7L;
				  gensymed_symbol_1 = gensymed_symbol_1 << 
					  gensymed_symbol_2;
				  gensymed_symbol = gensymed_symbol & 
					  gensymed_symbol_1;
				  temp_1 = (SI_Long)0L < gensymed_symbol;
			      }
			      else
				  temp_1 = TRUEP(Nil);
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  temp_1 =  !temp_1;
		      }
		      if ( !temp_1) {
			  ab_loopvar__1 = 
				  lookup_kb_specific_property_value(subclass,
				  Instances_specific_to_this_class_kbprop);
			  instance = Nil;
			  ab_loop_it_ = Nil;
			next_loop_25:
			  if ( !TRUEP(ab_loopvar__1))
			      goto end_loop_25;
			  instance = ab_loopvar__1;
			  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
			  ab_loop_it_ = ISVREF(instance,(SI_Long)18L);
			  if (ab_loop_it_) {
			      temp = ab_loop_it_;
			      goto end_9;
			  }
			  goto next_loop_25;
			end_loop_25:
			  temp = Qnil;
			end_9:;
		      }
		      else
			  temp = Nil;
		  }
		  ab_loop_it_ = temp;
		  if (ab_loop_it_) {
		      result = VALUES_1(ab_loop_it_);
		      goto end_10;
		  }
		  goto next_loop_12;
		end_loop_12:
		  result = VALUES_1(Qnil);
		end_10:;
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* DELETE-BLOCK-FOR-USER */
Object delete_block_for_user varargs_1(int, n)
{
    Object block;
    Object last_mouse_x_in_window_qm, last_mouse_y_in_window_qm, workspace_qm;
    Object gensymed_symbol, superblock_qm, sub_class_bit_vector;
    Object block_to_delete, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,24);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    last_mouse_x_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    last_mouse_y_in_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workspace_qm = get_workspace_if_any(block);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    if (workspace_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Non_kb_workspace_class_description,(SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    block_to_delete = ((temp ? TRUEP(superblock_qm) : TRUEP(Nil)) ? 
	    has_only_one_subblock_p(superblock_qm) || 
	    workspace_is_for_virtual_attribute_table_p(superblock_qm) : 
	    TRUEP(Nil)) ? workspace_qm : block;
    if (block_may_be_deleted_without_prompting_p(block))
	return delete_frame(block_to_delete);
    else {
	temp_1 = dialog_message_string_for_delete_block(block);
	return enter_dialog(9,temp_1,Nil,Nil,
		Qdelete_frame_after_checking_serial_number,
		slot_value_list_2(block_to_delete,
		copy_frame_serial_number(Current_frame_serial_number)),Nil,
		Nil,last_mouse_x_in_window_qm,last_mouse_y_in_window_qm);
    }
}

static Object string_constant_11;  /* "This action would cause the deletion of stable item(s).  " */

static Object Qg2gl_process;       /* g2gl-process */

static Object string_constant_12;  /* "This action would cause the deletion of ~d process instance~a.  " */

static Object string_constant_13;  /* "" */

static Object string_constant_14;  /* "s" */

static Object string_constant_15;  /* "Delete this class" */

static Object string_constant_16;  /* ", its instances, and its associated subworkspace(s)" */

static Object string_constant_17;  /* " and its instances" */

static Object string_constant_18;  /* " and its subworkspace(s)" */

static Object string_constant_19;  /* "?" */

static Object string_constant_20;  /* "Delete this class-definition" */

static Object string_constant_21;  /* "Delete this ~(~a~)" */

/* DIALOG-MESSAGE-STRING-FOR-DELETE-BLOCK */
Object dialog_message_string_for_delete_block(block)
    Object block;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, sub_class_bit_vector, count_1;
    Object workspace_deletion_qm, class_name_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(119,25);
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
	      if (destabilizing_item_deletion_p(block))
		  tformat(1,string_constant_11);
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qg2gl_process,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  count_1 = count_instances_of_g2gl_process(block);
		  if ( !(IFIX(count_1) == (SI_Long)0L))
		      tformat(3,string_constant_12,count_1,IFIX(count_1) 
			      == (SI_Long)1L ? string_constant_13 : 
			      string_constant_14);
	      }
	      sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp = TRUEP(Nil);
	      workspace_deletion_qm = temp ? 
		      item_deletion_causes_workspace_deletion_p(block) : Nil;
	      sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Class_definition_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  class_name_qm = ISVREF(block,(SI_Long)20L);
		  if (SYMBOLP(class_name_qm)) {
		      skip_list = CDR(Symbol_properties_table);
		      key_value = class_name_qm;
		      key_hash_value = SXHASH_SYMBOL_1(class_name_qm) & 
			      IFIX(Most_positive_fixnum);
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
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_1:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_2:
		      if ( !TRUEP(marked))
			  goto end_loop_1;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		      goto next_loop_2;
		    end_loop_1:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol)) {
			  gensymed_symbol = class_name_qm;
			  temp_1 = Symbol_properties_table;
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
			      gensymed_symbol_4 = new_cons;
			  }
			  else
			      gensymed_symbol_4 = Nil;
			  if ( !TRUEP(gensymed_symbol_4))
			      gensymed_symbol_4 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_4) = 
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
			      gensymed_symbol_5 = new_cons;
			  }
			  else
			      gensymed_symbol_5 = Nil;
			  if ( !TRUEP(gensymed_symbol_5))
			      gensymed_symbol_5 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_5) = head;
			  M_CDR(gensymed_symbol_5) = tail;
			  inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			  inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			  gensymed_symbol = set_skip_list_entry(temp_1,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol,temp_2,gensymed_symbol_4);
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
		    next_loop_3:
		      if (level < ab_loop_bind_)
			  goto end_loop_3;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_4:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_5:
		      if ( !TRUEP(marked))
			  goto end_loop_4;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		      goto next_loop_5;
		    end_loop_4:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			next_loop_6:
			  if (level < ab_loop_bind_)
			      goto end_loop_6;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_7:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_8:
			  if ( !TRUEP(marked))
			      goto end_loop_7;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_8;
			end_loop_7:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
			next_loop_9:
			  if (level < ab_loop_bind_)
			      goto end_loop_9;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_10:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_11:
			  if ( !TRUEP(marked))
			      goto end_loop_10;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_11;
			end_loop_10:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  if (temp) {
		      tformat(1,string_constant_15);
		      if (instantiated_class_p(class_name_qm)) {
			  if (workspace_deletion_qm)
			      tformat(1,string_constant_16);
			  else
			      tformat(1,string_constant_17);
		      }
		      else if (workspace_deletion_qm)
			  tformat(1,string_constant_18);
		      tformat(1,string_constant_19);
		  }
		  else {
		      tformat(1,string_constant_20);
		      if (workspace_deletion_qm)
			  tformat(1,string_constant_18);
		      tformat(1,string_constant_19);
		  }
	      }
	      else {
		  tformat(2,string_constant_21,ISVREF(ISVREF(block,
			  (SI_Long)1L),(SI_Long)1L));
		  sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp ? TRUEP(ISVREF(block,(SI_Long)18L)) : TRUEP(Nil))
		      tformat(1,string_constant_18);
		  tformat(1,string_constant_19);
	      }
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qsystem_table;       /* system-table */

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qicon_description;   /* icon-description */

static Object Qconnection_definition;  /* connection-definition */

/* PROBLEM-ITEM-IN-LIMBO-P */
Object problem_item_in_limbo_p(block)
    Object block;
{
    Object sub_class_bit_vector, gensymed_symbol_3, superior, ab_loop_list_;
    Object ab_loop_it_, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_4;
    Object gensymed_symbol_5, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, class_name_qm, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, connection_definition;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,26);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !TRUEP(superior_frame(block)) : TRUEP(Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_invocation_class_description,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qsystem_table,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	    if (get_lookup_slot_value_given_default(block,
		    Qclass_inheritance_path_of_definition,Nil)) {
		superior = Nil;
		ab_loop_list_ = ISVREF(block,(SI_Long)21L);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_3;
	      end_loop_2:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol_3)) {
		    gensymed_symbol_3 = superior;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol_3 = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			    temp_2,gensymed_symbol_4);
		}
		global_properties = gensymed_symbol_3;
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_5:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_6:
		if ( !TRUEP(marked))
		    goto end_loop_5;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_6;
	      end_loop_5:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		  next_loop_7:
		    if (level < ab_loop_bind_)
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_8:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_9:
		    if ( !TRUEP(marked))
			goto end_loop_8;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_3;
		    goto next_loop_8;
		  end_loop_9:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_7;
		  end_loop_7:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_10:
		    if (level < ab_loop_bind_)
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_11:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_12:
		    if ( !TRUEP(marked))
			goto end_loop_11;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_4;
		    goto next_loop_11;
		  end_loop_12:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_10;
		  end_loop_10:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol_3 = resulting_value;
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Entity_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
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
		  next_loop_13:
		    if (level < ab_loop_bind_)
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_14:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_15:
		    if ( !TRUEP(marked))
			goto end_loop_14;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_5;
		    goto next_loop_14;
		  end_loop_15:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_13;
		  end_loop_13:;
		    gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol_3)) {
			gensymed_symbol_3 = superior;
			temp_1 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_4) = 
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
			    gensymed_symbol_5 = new_cons;
			}
			else
			    gensymed_symbol_5 = Nil;
			if ( !TRUEP(gensymed_symbol_5))
			    gensymed_symbol_5 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_5) = head;
			M_CDR(gensymed_symbol_5) = tail;
			inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			gensymed_symbol_3 = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol_3,temp_2,gensymed_symbol_4);
		    }
		    global_properties = gensymed_symbol_3;
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
		  next_loop_16:
		    if (level < ab_loop_bind_)
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_17:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_18:
		    if ( !TRUEP(marked))
			goto end_loop_17;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_6;
		    goto next_loop_17;
		  end_loop_18:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_16;
		  end_loop_16:;
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
		      next_loop_19:
			if (level < ab_loop_bind_)
			    goto end_loop_19;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_20:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_21:
			if ( !TRUEP(marked))
			    goto end_loop_20;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
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
			    goto end_7;
			goto next_loop_20;
		      end_loop_21:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_19;
		      end_loop_19:;
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
		      next_loop_22:
			if (level < ab_loop_bind_)
			    goto end_loop_22;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_23:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_24:
			if ( !TRUEP(marked))
			    goto end_loop_23;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
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
			    goto end_8;
			goto next_loop_23;
		      end_loop_24:
		      end_8:
			level = level - (SI_Long)1L;
			goto next_loop_22;
		      end_loop_22:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol_3 = resulting_value;
		    if (gensymed_symbol_3) {
			sub_class_bit_vector = ISVREF(gensymed_symbol_3,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Connection_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
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
		  next_loop_25:
		    if (level < ab_loop_bind_)
			goto end_loop_25;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_26:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_27:
		    if ( !TRUEP(marked))
			goto end_loop_26;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_9;
		    goto next_loop_26;
		  end_loop_27:
		  end_9:
		    level = level - (SI_Long)1L;
		    goto next_loop_25;
		  end_loop_25:;
		    gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol_3)) {
			gensymed_symbol_3 = superior;
			temp_1 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_4) = 
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
			    gensymed_symbol_5 = new_cons;
			}
			else
			    gensymed_symbol_5 = Nil;
			if ( !TRUEP(gensymed_symbol_5))
			    gensymed_symbol_5 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_5) = head;
			M_CDR(gensymed_symbol_5) = tail;
			inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			gensymed_symbol_3 = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol_3,temp_2,gensymed_symbol_4);
		    }
		    global_properties = gensymed_symbol_3;
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
		  next_loop_28:
		    if (level < ab_loop_bind_)
			goto end_loop_28;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_29:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_30:
		    if ( !TRUEP(marked))
			goto end_loop_29;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_30;
		  end_loop_29:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_10;
		    goto next_loop_29;
		  end_loop_30:
		  end_10:
		    level = level - (SI_Long)1L;
		    goto next_loop_28;
		  end_loop_28:;
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
		      next_loop_31:
			if (level < ab_loop_bind_)
			    goto end_loop_31;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_32:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_33:
			if ( !TRUEP(marked))
			    goto end_loop_32;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_33;
		      end_loop_32:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_11;
			goto next_loop_32;
		      end_loop_33:
		      end_11:
			level = level - (SI_Long)1L;
			goto next_loop_31;
		      end_loop_31:;
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
		      next_loop_34:
			if (level < ab_loop_bind_)
			    goto end_loop_34;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_35:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_36:
			if ( !TRUEP(marked))
			    goto end_loop_35;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_36;
		      end_loop_35:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_12;
			goto next_loop_35;
		      end_loop_36:
		      end_12:
			level = level - (SI_Long)1L;
			goto next_loop_34;
		      end_loop_34:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol_3 = resulting_value;
		    if (gensymed_symbol_3) {
			sub_class_bit_vector = ISVREF(gensymed_symbol_3,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Meter_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
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
		  next_loop_37:
		    if (level < ab_loop_bind_)
			goto end_loop_37;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_38:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_39:
		    if ( !TRUEP(marked))
			goto end_loop_38;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_13;
		    goto next_loop_38;
		  end_loop_39:
		  end_13:
		    level = level - (SI_Long)1L;
		    goto next_loop_37;
		  end_loop_37:;
		    gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol_3)) {
			gensymed_symbol_3 = superior;
			temp_1 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_4) = 
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
			    gensymed_symbol_5 = new_cons;
			}
			else
			    gensymed_symbol_5 = Nil;
			if ( !TRUEP(gensymed_symbol_5))
			    gensymed_symbol_5 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_5) = head;
			M_CDR(gensymed_symbol_5) = tail;
			inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			gensymed_symbol_3 = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol_3,temp_2,gensymed_symbol_4);
		    }
		    global_properties = gensymed_symbol_3;
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
		  next_loop_40:
		    if (level < ab_loop_bind_)
			goto end_loop_40;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_41:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_42:
		    if ( !TRUEP(marked))
			goto end_loop_41;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_14;
		    goto next_loop_41;
		  end_loop_42:
		  end_14:
		    level = level - (SI_Long)1L;
		    goto next_loop_40;
		  end_loop_40:;
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
		      next_loop_43:
			if (level < ab_loop_bind_)
			    goto end_loop_43;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_44:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_45:
			if ( !TRUEP(marked))
			    goto end_loop_44;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_45;
		      end_loop_44:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_15;
			goto next_loop_44;
		      end_loop_45:
		      end_15:
			level = level - (SI_Long)1L;
			goto next_loop_43;
		      end_loop_43:;
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
		      next_loop_46:
			if (level < ab_loop_bind_)
			    goto end_loop_46;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_47:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_48:
			if ( !TRUEP(marked))
			    goto end_loop_47;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_48;
		      end_loop_47:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_16;
			goto next_loop_47;
		      end_loop_48:
		      end_16:
			level = level - (SI_Long)1L;
			goto next_loop_46;
		      end_loop_46:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol_3 = resulting_value;
		    ab_loop_it_ = 
			    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
			    gensymed_symbol_3,Nil),(SI_Long)6L);
		}
		else
		    ab_loop_it_ = Nil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_17;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Qnil);
	      end_17:;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	temp_2 =  !temp ? T : Nil;
	if (temp_2)
	    return VALUES_1(temp_2);
	else {
	    class_name_qm = ISVREF(block,(SI_Long)20L);
	    temp_2 =  !TRUEP(class_name_qm) ? T : Nil;
	    if (temp_2)
		return VALUES_1(temp_2);
	    else {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		connection_definition = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(Qconnection_definition);
		next_loop_49:
		  if ( !TRUEP(ab_loopvar__1)) {
		    next_loop_50:
		      if ( !TRUEP(ab_loopvar_))
			  goto end_loop_49;
		      ab_loopvar__1 = 
			      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			      Instances_specific_to_this_class_kbprop);
		      ab_loopvar_ = M_CDR(ab_loopvar_);
		      if (ab_loopvar__1)
			  goto end_loop_49;
		      goto next_loop_50;
		    end_loop_49:
		      temp =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      goto end_loop_50;
		  connection_definition = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  if (EQ(class_name_qm,ISVREF(connection_definition,
			  (SI_Long)32L))) {
		      result = VALUES_1(Nil);
		      goto end_18;
		  }
		  goto next_loop_49;
		end_loop_50:
		  result = VALUES_1(T);
		  goto end_18;
		  result = VALUES_1(Qnil);
		end_18:;
		POP_SPECIAL();
		return result;
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qrelation;           /* relation */

static Object Qrelation_is_symmetric;  /* relation-is-symmetric */

static Object list_constant_10;    /* # */

/* INCLUDE-YES-NO-MENU-CHOICE-P */
Object include_yes_no_menu_choice_p(text_cell)
    Object text_cell;
{
    Object frame_qm, slot_name_qm, x2;
    char temp;
    Object result;

    x_note_fn_call(119,27);
    result = get_slot_represented_by_text_cell_if_any(text_cell);
    MVS_2(result,frame_qm,slot_name_qm);
    if (SIMPLE_VECTOR_P(frame_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L &&  
	    !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(frame_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (((temp ? SYMBOLP(slot_name_qm) : TRUEP(Nil)) ? 
	    EQ(ISVREF(ISVREF(frame_qm,(SI_Long)1L),(SI_Long)1L),Qrelation) 
	    : TRUEP(Nil)) ? EQ(slot_name_qm,Qrelation_is_symmetric) : 
	    TRUEP(Nil)) {
	if (ISVREF(frame_qm,(SI_Long)23L) ||  
		!TRUEP(memq_function(ISVREF(frame_qm,(SI_Long)24L),
		list_constant_10)))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(T);
    }
    else {
	if (SIMPLE_VECTOR_P(frame_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L && 
		 !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (((temp ? TRUEP(slot_name_qm) : TRUEP(Nil)) ? 
		SYMBOLP(slot_name_qm) : TRUEP(Nil)) ?  
		!TRUEP(user_writable_slot_of_instance_p(frame_qm,
		slot_name_qm,Nil)) : TRUEP(Nil))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(T);
    }
}

static Object Qfull_editor;        /* full-editor */

static Object Qdo_not_clear_text_for_edit_in_place;  /* do-not-clear-text-for-edit-in-place */

static Object Qoption_buttons_for_edit_in_place;  /* option-buttons-for-edit-in-place */

static Object Qmenus_for_edit_in_place;  /* menus-for-edit-in-place */

static Object Qclass_qualified_name;  /* class-qualified-name */

/* ENTER-TEXT-EDITOR-ON-TEXT-CELL */
Object enter_text_editor_on_text_cell varargs_1(int, n)
{
    Object table, text_cell, image_plane, x_in_window, y_in_window;
    Object click_to_edit_line_index_qm, click_to_edit_cursor_index_qm;
    Object intercepted_text_cell_text_qm, frame_qm, slot_name_qm;
    Object defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, virtual_attribute_qm;
    Object exported_format_qm, left_edge_of_area, top_edge_of_area;
    Object right_edge_of_area, bottom_edge_of_area, cursor_line_index_qm;
    Object cursor_character_index_qm, temp, temp_1;
    char edit_in_place_qm, blank_for_type_in_qm;
    char do_not_have_edit_option_buttons_qm, do_not_have_edit_menus_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(119,28);
    INIT_ARGS_nonrelocating();
    table = REQUIRED_ARG_nonrelocating();
    text_cell = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    click_to_edit_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    click_to_edit_cursor_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    intercepted_text_cell_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = get_slot_represented_by_text_cell_if_any(text_cell);
    MVS_7(result,frame_qm,slot_name_qm,defining_class_qm,
	    slot_component_name_qm,slot_component_indicator_qm,
	    virtual_attribute_qm,exported_format_qm);
    if (frame_qm) {
	edit_in_place_qm =  
		!TRUEP(non_menu_choice_permitted_p(Qfull_editor,frame_qm));
	blank_for_type_in_qm =  
		!TRUEP(non_menu_choice_permitted_p(Qdo_not_clear_text_for_edit_in_place,
		frame_qm));
	do_not_have_edit_option_buttons_qm =  
		!TRUEP(non_menu_choice_permitted_p(Qoption_buttons_for_edit_in_place,
		frame_qm));
	do_not_have_edit_menus_qm =  
		!TRUEP(non_menu_choice_permitted_p(Qmenus_for_edit_in_place,
		frame_qm));
	result = get_table_cell_edges(table,text_cell);
	MVS_4(result,left_edge_of_area,top_edge_of_area,right_edge_of_area,
		bottom_edge_of_area);
	result = find_position_in_text_given_image_plane(9,table,Nil,
		text_cell,left_edge_of_area,top_edge_of_area,Nil,
		image_plane,x_in_window,y_in_window);
	MVS_2(result,cursor_line_index_qm,cursor_character_index_qm);
	if ( !edit_in_place_qm) {
	    temp = defining_class_qm ? 
		    slot_value_cons_1(Qclass_qualified_name,
		    slot_value_cons_1(defining_class_qm,
		    slot_value_cons_1(slot_name_qm,Nil))) : slot_name_qm;
	    temp_1 = intercepted_text_cell_text_qm ? 
		    add_intercepted_token_to_text(intercepted_text_cell_text_qm) 
		    : get_text_to_edit_from_text_cell(text_cell);
	    return enter_editing_context(24,frame_qm,temp,temp_1,Nil,Nil,
		    Nil, !blank_for_type_in_qm ? 
		    click_to_edit_line_index_qm : Nil, 
		    !blank_for_type_in_qm ? click_to_edit_cursor_index_qm :
		     Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,
		    slot_component_name_qm,slot_component_indicator_qm,
		    table,virtual_attribute_qm,exported_format_qm);
	}
	else {
	    temp = defining_class_qm ? 
		    slot_value_cons_1(Qclass_qualified_name,
		    slot_value_cons_1(defining_class_qm,
		    slot_value_cons_1(slot_name_qm,Nil))) : slot_name_qm;
	    temp_1 = intercepted_text_cell_text_qm ? 
		    add_intercepted_token_to_text(intercepted_text_cell_text_qm) 
		    : blank_for_type_in_qm ? make_empty_text() : 
		    get_text_to_edit_from_text_cell(text_cell);
	    return enter_editing_context(24,frame_qm,temp,temp_1,Nil,Nil,
		    Nil, !blank_for_type_in_qm ? cursor_line_index_qm : 
		    Nil, !blank_for_type_in_qm ? cursor_character_index_qm 
		    : Nil,image_plane,table,left_edge_of_area,
		    top_edge_of_area,right_edge_of_area,
		    bottom_edge_of_area,Nil,Nil,Nil,
		    do_not_have_edit_option_buttons_qm ? T : Nil,
		    do_not_have_edit_menus_qm ? T : Nil,
		    slot_component_name_qm,slot_component_indicator_qm,
		    table,virtual_attribute_qm,exported_format_qm);
	}
    }
    else
	return VALUES_1(Nil);
}

/* GET-TEXT-TO-EDIT-FROM-TEXT-CELL */
Object get_text_to_edit_from_text_cell(text_cell)
    Object text_cell;
{
    Object frame_qm, slot_name, defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, virtual_attribute_p, exported_format_p;
    Object text_summarized_p, display_format_qm, text_cell_text, temp;
    Object result;

    x_note_fn_call(119,29);
    result = get_slot_represented_by_text_cell_if_any(text_cell);
    MVS_9(result,frame_qm,slot_name,defining_class_qm,
	    slot_component_name_qm,slot_component_indicator_qm,
	    virtual_attribute_p,exported_format_p,text_summarized_p,
	    display_format_qm);
    text_cell_text = CDDDR(text_cell);
    temp = display_format_qm && frame_qm &&  !TRUEP(virtual_attribute_p) 
	    &&  !TRUEP(exported_format_p) &&  !TRUEP(text_summarized_p) && 
	     !TRUEP(slot_component_name_qm) &&  
	    !TRUEP(slot_component_indicator_qm) ? 
	    make_text_representation_for_slot_value(3,frame_qm,slot_name,
	    defining_class_qm) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return copy_text(text_cell_text);
}

/* DO-ADDITION-OF-OPTIONAL-SUBTABLE-FROM-MENU */
Object do_addition_of_optional_subtable_from_menu(class_1,image_plane,
	    x_in_window,y_in_window,frame,slot_name,class_qualifier_qm)
    Object class_1, image_plane, x_in_window, y_in_window, frame, slot_name;
    Object class_qualifier_qm;
{
    Object subtable;

    x_note_fn_call(119,30);
    subtable = make_frame(class_1);
    change_slot_value(4,frame,slot_name,subtable,class_qualifier_qm);
    return put_up_attributes_table(3,subtable,x_in_window,y_in_window);
}

static Object Qkb_workspace;       /* kb-workspace */

static Object Qkb_workspace_initial_width;  /* kb-workspace-initial-width */

static Object Qkb_workspace_initial_height;  /* kb-workspace-initial-height */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* GO-TO-MAYBE-NEWLY-CREATED-SUBWORKSPACE */
Object go_to_maybe_newly_created_subworkspace(entity,workspace_class_qm)
    Object entity, workspace_class_qm;
{
    Object temp;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object kb_workspace_class, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, temp_2, temp_3;
    Object workspace;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,31);
    if (ISVREF(entity,(SI_Long)18L)) {
	temp = ISVREF(entity,(SI_Long)18L);
	temp = CAR(temp);
    }
    else
	temp = entity;
    if (workspaces_can_be_shown_at_this_kb_level_p(temp,Current_workstation)) {
	if (ISVREF(entity,(SI_Long)18L)) {
	    temp = ISVREF(entity,(SI_Long)18L);
	    temp = FIRST(temp);
	}
	else {
	    inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
		    = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		    0);
	      kb_workspace_class = workspace_class_qm;
	      if (kb_workspace_class);
	      else
		  kb_workspace_class = Qkb_workspace;
	      skip_list = CDR(Symbol_properties_table);
	      key_value = kb_workspace_class;
	      key_hash_value = SXHASH_SYMBOL_1(kb_workspace_class) & 
		      IFIX(Most_positive_fixnum);
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	    next_loop_2:
	      if ( !TRUEP(marked))
		  goto end_loop_1;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_2;
	    end_loop_1:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
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
	      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  gensymed_symbol = kb_workspace_class;
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
		  gensymed_symbol = set_skip_list_entry(temp_1,
			  FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp,
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
	    next_loop_3:
	      if (level < ab_loop_bind_)
		  goto end_loop_3;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_4:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	    next_loop_5:
	      if ( !TRUEP(marked))
		  goto end_loop_4;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_5;
	    end_loop_4:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
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
		next_loop_6:
		  if (level < ab_loop_bind_)
		      goto end_loop_6;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_7:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_1,temp);
		  MVS_2(result,succ,marked);
		next_loop_8:
		  if ( !TRUEP(marked))
		      goto end_loop_7;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_1,temp);
		  MVS_2(result,succ,marked);
		  goto next_loop_8;
		end_loop_7:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		next_loop_9:
		  if (level < ab_loop_bind_)
		      goto end_loop_9;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_10:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_1,temp);
		  MVS_2(result,succ,marked);
		next_loop_11:
		  if ( !TRUEP(marked))
		      goto end_loop_10;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_1,temp);
		  MVS_2(result,succ,marked);
		  goto next_loop_11;
		end_loop_10:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      temp_1 = 
		      ISVREF(get_slot_description_of_class_description_function(Qkb_workspace_initial_width,
		      gensymed_symbol,Nil),(SI_Long)6L);
	      skip_list = CDR(Symbol_properties_table);
	      key_value = kb_workspace_class;
	      key_hash_value = SXHASH_SYMBOL_1(kb_workspace_class) & 
		      IFIX(Most_positive_fixnum);
	      bottom_level = (SI_Long)0L;
	      marked = Nil;
	      pred = M_CAR(skip_list);
	      curr = Nil;
	      succ = Nil;
	      level = (SI_Long)31L;
	      ab_loop_bind_ = bottom_level;
	    next_loop_12:
	      if (level < ab_loop_bind_)
		  goto end_loop_12;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_13:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_2 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_2,temp);
	      MVS_2(result,succ,marked);
	    next_loop_14:
	      if ( !TRUEP(marked))
		  goto end_loop_13;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_2 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_2,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_14;
	    end_loop_13:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_5;
	      goto next_loop_13;
	    end_loop_14:
	    end_5:
	      level = level - (SI_Long)1L;
	      goto next_loop_12;
	    end_loop_12:;
	      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  gensymed_symbol = kb_workspace_class;
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
		  gensymed_symbol = set_skip_list_entry(temp_2,
			  FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp,
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
	    next_loop_15:
	      if (level < ab_loop_bind_)
		  goto end_loop_15;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_16:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_2 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_2,temp);
	      MVS_2(result,succ,marked);
	    next_loop_17:
	      if ( !TRUEP(marked))
		  goto end_loop_16;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_2 = ATOMIC_REF_OBJECT(reference);
	      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_2,temp);
	      MVS_2(result,succ,marked);
	      goto next_loop_17;
	    end_loop_16:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_6;
	      goto next_loop_16;
	    end_loop_17:
	    end_6:
	      level = level - (SI_Long)1L;
	      goto next_loop_15;
	    end_loop_15:;
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
		next_loop_18:
		  if (level < ab_loop_bind_)
		      goto end_loop_18;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_19:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		next_loop_20:
		  if ( !TRUEP(marked))
		      goto end_loop_19;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		  goto next_loop_20;
		end_loop_19:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_7;
		  goto next_loop_19;
		end_loop_20:
		end_7:
		  level = level - (SI_Long)1L;
		  goto next_loop_18;
		end_loop_18:;
		  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		next_loop_21:
		  if (level < ab_loop_bind_)
		      goto end_loop_21;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_22:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		next_loop_23:
		  if ( !TRUEP(marked))
		      goto end_loop_22;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			   Nil;
		  result = VALUES_2(temp_2,temp);
		  MVS_2(result,succ,marked);
		  goto next_loop_23;
		end_loop_22:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_8;
		  goto next_loop_22;
		end_loop_23:
		end_8:
		  level = level - (SI_Long)1L;
		  goto next_loop_21;
		end_loop_21:;
		  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      temp = 
		      ISVREF(get_slot_description_of_class_description_function(Qkb_workspace_initial_height,
		      gensymed_symbol,Nil),(SI_Long)6L);
	      skip_list = CDR(Symbol_properties_table);
	      key_value = kb_workspace_class;
	      key_hash_value = SXHASH_SYMBOL_1(kb_workspace_class) & 
		      IFIX(Most_positive_fixnum);
	      bottom_level = (SI_Long)0L;
	      marked = Nil;
	      pred = M_CAR(skip_list);
	      curr = Nil;
	      succ = Nil;
	      level = (SI_Long)31L;
	      ab_loop_bind_ = bottom_level;
	    next_loop_24:
	      if (level < ab_loop_bind_)
		  goto end_loop_24;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_25:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_26:
	      if ( !TRUEP(marked))
		  goto end_loop_25;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_2);
	      MVS_2(result,succ,marked);
	      goto next_loop_26;
	    end_loop_25:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_9;
	      goto next_loop_25;
	    end_loop_26:
	    end_9:
	      level = level - (SI_Long)1L;
	      goto next_loop_24;
	    end_loop_24:;
	      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  gensymed_symbol = kb_workspace_class;
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
		  gensymed_symbol = set_skip_list_entry(temp_3,
			  FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			  temp_2,gensymed_symbol_1);
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
	    next_loop_27:
	      if (level < ab_loop_bind_)
		  goto end_loop_27;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_28:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_29:
	      if ( !TRUEP(marked))
		  goto end_loop_28;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_2);
	      MVS_2(result,succ,marked);
	      goto next_loop_29;
	    end_loop_28:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_10;
	      goto next_loop_28;
	    end_loop_29:
	    end_10:
	      level = level - (SI_Long)1L;
	      goto next_loop_27;
	    end_loop_27:;
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
		next_loop_30:
		  if (level < ab_loop_bind_)
		      goto end_loop_30;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_31:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_32:
		  if ( !TRUEP(marked))
		      goto end_loop_31;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_2);
		  MVS_2(result,succ,marked);
		  goto next_loop_32;
		end_loop_31:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_11;
		  goto next_loop_31;
		end_loop_32:
		end_11:
		  level = level - (SI_Long)1L;
		  goto next_loop_30;
		end_loop_30:;
		  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		next_loop_33:
		  if (level < ab_loop_bind_)
		      goto end_loop_33;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_34:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_35:
		  if ( !TRUEP(marked))
		      goto end_loop_34;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_2);
		  MVS_2(result,succ,marked);
		  goto next_loop_35;
		end_loop_34:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_12;
		  goto next_loop_34;
		end_loop_35:
		end_12:
		  level = level - (SI_Long)1L;
		  goto next_loop_33;
		end_loop_33:;
		  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      workspace = make_new_top_level_kb_workspace(7,
		      kb_workspace_class,Nil,Nil,Nil,temp_1,temp,
		      ISVREF(get_slot_description_of_class_description_function(Qmodule_this_is_part_of_qm,
		      gensymed_symbol,Nil),(SI_Long)6L));
	      add_subworkspace(workspace,entity);
	      if (subworkspace_connection_posts_p(entity))
		  add_subworkspace_connection_posts(workspace,entity);
	      temp = workspace;
	    POP_SPECIAL();
	}
	goto_frame_instance(temp);
	temp = ISVREF(entity,(SI_Long)18L);
	return VALUES_1(FIRST(temp));
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext_box_format;    /* text-box-format */

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

static Object Qformat_frame;       /* format-frame */

/* MAKE-COMMAND-FRAME */
Object make_command_frame varargs_1(int, n)
{
    Object command_class;
    Object initial_text_line_qm, command_frame, format_name, svref_new_value;
    Object temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,32);
    INIT_ARGS_nonrelocating();
    command_class = REQUIRED_ARG_nonrelocating();
    initial_text_line_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    command_frame = make_frame(command_class);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(command_frame,Qtext_box_format);
    format_name = get_lookup_slot_value(command_frame,
	    Qdefault_text_box_format_name);
    svref_new_value = get_instance_with_name_if_any(Qformat_frame,format_name);
    if (svref_new_value);
    else
	svref_new_value = make_format_frame(format_name);
    SVREF(command_frame,FIX((SI_Long)17L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(command_frame,Qbox_translation_and_text);
    temp = No_value;
    svref_new_value = slot_value_cons_1(temp,initial_text_line_qm ? 
	    convert_text_string_to_text(initial_text_line_qm) : 
	    make_empty_text());
    SVREF(command_frame,FIX((SI_Long)16L)) = svref_new_value;
    return VALUES_1(command_frame);
}

static Object Qexecute_command_on_return;  /* execute-command-on-return */

static Object Qdelete_frame;       /* delete-frame */

/* HANDLE-COMMAND */
Object handle_command(command_class,initial_text_line_qm)
    Object command_class, initial_text_line_qm;
{
    Object command_frame;

    x_note_fn_call(119,33);
    command_frame = make_command_frame(1,command_class);
    establish_next_workstation_context_continuation(Nil,
	    Qexecute_command_on_return,command_frame,Qdelete_frame);
    return enter_editing_context(3,command_frame,Qbox_translation_and_text,
	    initial_text_line_qm ? slot_value_cons_1(initial_text_line_qm,
	    Nil) : make_empty_text());
}

/* HANDLE-INSPECT-COMMAND */
Object handle_inspect_command varargs_1(int, n)
{
    Object inspect_command;
    Object cursor_line_index_qm, cursor_character_index_qm;
    Object edit_workspace_hidden_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,34);
    INIT_ARGS_nonrelocating();
    inspect_command = REQUIRED_ARG_nonrelocating();
    cursor_line_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cursor_character_index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    edit_workspace_hidden_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    establish_next_workstation_context_continuation(Nil,
	    Qexecute_command_on_return,inspect_command,Nil);
    enter_editing_context(8,inspect_command,Qbox_translation_and_text,Nil,
	    edit_workspace_hidden_qm,Nil,Nil,cursor_line_index_qm,
	    cursor_character_index_qm);
    if (edit_workspace_hidden_qm)
	return finish_parsing_insofar_as_possible();
    else
	return VALUES_1(Nil);
}

static Object Qediting;            /* editing */

/* EXECUTE-COMMAND-ON-RETURN */
Object execute_command_on_return(workstation_context)
    Object workstation_context;
{
    Object command_frame, command_name, frame_serial_number;
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, frame;
    Object sub_vector_qm, function_qm, gensymed_symbol, xa, ya;
    SI_Long method_index;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(119,35);
    command_frame = ISVREF(workstation_context,(SI_Long)5L);
    command_name = ISVREF(ISVREF(command_frame,(SI_Long)1L),(SI_Long)1L);
    SVREF(workstation_context,FIX((SI_Long)6L)) = Nil;
    exit_current_workstation_context_in_return_function(Qediting);
    frame_serial_number = copy_frame_serial_number(ISVREF(command_frame,
	    (SI_Long)3L));
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
	  SVREF(temp,svref_arg_2) = command_name;
      }
      method_index = (SI_Long)27L;
      frame = command_frame;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),method_index);
      function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
      if (function_qm)
	  inline_funcall_1(function_qm,frame);
    POP_SPECIAL();
    gensymed_symbol = ISVREF(command_frame,(SI_Long)3L);
    temp_1 = SIMPLE_VECTOR_P(command_frame) ? EQ(ISVREF(command_frame,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
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
    if (temp_1);
    else
	temp_1 = TRUEP(get_workspace_if_any(command_frame));
    if ( !temp_1)
	delete_frame(command_frame);
    return reclaim_frame_serial_number(frame_serial_number);
}

/* MANIFEST-ITEM-CREATION */
Object manifest_item_creation(item,image_plane,x_in_window,y_in_window)
    Object item, image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(119,36);
    set_cursor_position(x_in_window,y_in_window);
    return enter_transfer_dragging_context(1,item);
}

/* ACT-ON-CHOICE-OF-A-ENTITY */
Object act_on_choice_of_a_entity(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,37);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_entity(1,class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-MESSAGE */
Object act_on_choice_of_a_message(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,38);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_message(2,Nil,class_1),
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-READOUT-TABLE */
Object act_on_choice_of_a_readout_table(class_1,image_plane,x_in_window,
	    y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,39);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_readout_table(class_1),
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-DIAL */
Object act_on_choice_of_a_dial(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,40);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_dial(class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-METER */
Object act_on_choice_of_a_meter(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,41);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_meter(class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-BUTTON */
Object act_on_choice_of_a_button(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,42);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_button(1,class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-GRAPH */
Object act_on_choice_of_a_graph(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,43);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_graph(class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-CHART */
Object act_on_choice_of_a_chart(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,44);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_frame(class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ACT-ON-CHOICE-OF-A-FREEFORM-TABLE */
Object act_on_choice_of_a_freeform_table(class_1,image_plane,x_in_window,
	    y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,45);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_frame(class_1),image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

static Object string_constant_22;  /* "Creation of ~a instances is prohibited in run-time-only systems." */

static Object Qhand_place_on_return;  /* hand-place-on-return */

static Object Qreclaim_hand_placement_return_information;  /* reclaim-hand-placement-return-information */

/* ACT-ON-CHOICE-OF-A-TEXT-BOX */
Object act_on_choice_of_a_text_box(class_1,image_plane,x_in_window,y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, text_box;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,46);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (Nil)
	    return notify_user(2,string_constant_22,class_1);
	else if ( ! !TRUEP(ISVREF(image_plane,(SI_Long)5L))) {
	    text_box = make_text_box(class_1);
	    establish_next_workstation_context_continuation(Nil,
		    Qhand_place_on_return,gensym_list_4(text_box,
		    x_in_window,y_in_window,
		    copy_frame_serial_number(ISVREF(text_box,
		    (SI_Long)3L))),Qreclaim_hand_placement_return_information);
	    return enter_editing_context(3,text_box,
		    Qbox_translation_and_text,make_empty_text());
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfont_for_statements;  /* font-for-statements */

static Object Qfree_text;          /* free-text */

static Object Qborderless_free_text;  /* borderless-free-text */

static Object Qfont_for_free_text;  /* font-for-free-text */

/* MAKE-TEXT-BOX */
Object make_text_box(class_1)
    Object class_1;
{
    Object new_text_box, default_text_box_format_name, gensymed_symbol;
    Object sub_class_bit_vector, format_name, gensymed_symbol_4;
    Object svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(119,47);
    new_text_box = make_frame(class_1);
    default_text_box_format_name = get_lookup_slot_value(new_text_box,
	    Qdefault_text_box_format_name);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(new_text_box,Qtext_box_format);
    gensymed_symbol = lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Statement_class_description,
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
	format_name = 
		choose_font_format_per_fonts_table(default_text_box_format_name,
		Qfont_for_statements);
    else {
	gensymed_symbol_4 = 
		lookup_global_or_kb_specific_property_value(Qfree_text,
		Class_description_gkbprop);
	if (gensymed_symbol_4) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qborderless_free_text,
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
	if (temp)
	    format_name = 
		    choose_font_format_per_fonts_table(default_text_box_format_name,
		    Qfont_for_free_text);
	else
	    format_name = default_text_box_format_name;
    }
    svref_new_value = get_instance_with_name_if_any(Qformat_frame,format_name);
    if (svref_new_value);
    else
	svref_new_value = make_format_frame(format_name);
    SVREF(new_text_box,FIX((SI_Long)17L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(new_text_box,Qbox_translation_and_text);
    svref_new_value = make_incomplete_box_translation_and_text();
    SVREF(new_text_box,FIX((SI_Long)16L)) = svref_new_value;
    reformat_text_box_in_place(1,new_text_box);
    return VALUES_1(new_text_box);
}

static Object Qreenter_editor_if_not_hand_placed;  /* reenter-editor-if-not-hand-placed */

/* HAND-PLACE-ON-RETURN */
Object hand_place_on_return(workstation_context)
    Object workstation_context;
{
    Object workstation_context_return_information, text_box, x_in_window;
    Object y_in_window, frame_serial_number, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(119,48);
    workstation_context_return_information = ISVREF(workstation_context,
	    (SI_Long)5L);
    text_box = FIRST(workstation_context_return_information);
    x_in_window = SECOND(workstation_context_return_information);
    y_in_window = THIRD(workstation_context_return_information);
    frame_serial_number = 
	    copy_frame_serial_number(FOURTH(workstation_context_return_information));
    M_FIRST(workstation_context_return_information) = Nil;
    exit_current_workstation_context_in_return_function(Qediting);
    set_cursor_position(x_in_window,y_in_window);
    gensymed_symbol = ISVREF(text_box,(SI_Long)3L);
    gensymed_symbol_1 = frame_serial_number;
    if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	    FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) : 
	    FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
	    FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) && 
	    FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1))) {
	establish_next_workstation_context_continuation(Qreenter_editor_if_not_hand_placed,
		Nil,Nil,Nil);
	enter_transfer_dragging_context(1,text_box);
    }
    return reclaim_frame_serial_number(frame_serial_number);
}

/* RECLAIM-HAND-PLACEMENT-RETURN-INFORMATION */
Object reclaim_hand_placement_return_information(hand_placement_return_information)
    Object hand_placement_return_information;
{
    x_note_fn_call(119,49);
    if (FIRST(hand_placement_return_information))
	delete_frame(FIRST(hand_placement_return_information));
    reclaim_frame_serial_number(FOURTH(hand_placement_return_information));
    return reclaim_gensym_list_1(hand_placement_return_information);
}

/* HAND-PLACE-ON-RETURN-MOVE-STYLE */
Object hand_place_on_return_move_style(workstation_context)
    Object workstation_context;
{
    Object workstation_context_return_information, text_box, x_in_window;
    Object y_in_window, frame_serial_number, image_plane, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(119,50);
    workstation_context_return_information = ISVREF(workstation_context,
	    (SI_Long)5L);
    text_box = FIRST(workstation_context_return_information);
    x_in_window = SECOND(workstation_context_return_information);
    y_in_window = THIRD(workstation_context_return_information);
    frame_serial_number = 
	    copy_frame_serial_number(FOURTH(workstation_context_return_information));
    image_plane = FIFTH(workstation_context_return_information);
    M_FIRST(workstation_context_return_information) = Nil;
    exit_current_workstation_context_in_return_function(Qediting);
    set_cursor_position(x_in_window,y_in_window);
    gensymed_symbol = ISVREF(text_box,(SI_Long)3L);
    gensymed_symbol_1 = frame_serial_number;
    if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	    FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) : 
	    FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
	    FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) && 
	    FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1))) {
	establish_next_workstation_context_continuation(Qreenter_editor_if_not_hand_placed,
		Nil,Nil,Nil);
	enter_move_dragging_context(4,text_box,FIX((SI_Long)0L),
		FIX((SI_Long)0L),image_plane);
    }
    return reclaim_frame_serial_number(frame_serial_number);
}

/* RECLAIM-MOVE-STYLE-HAND-PLACEMENT-RETURN-INFORMATION */
Object reclaim_move_style_hand_placement_return_information(hand_placement_return_information)
    Object hand_placement_return_information;
{
    Object text_box_qm, reference_serial_number, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(119,51);
    text_box_qm = FIRST(hand_placement_return_information);
    reference_serial_number = FOURTH(hand_placement_return_information);
    if (text_box_qm) {
	gensymed_symbol = ISVREF(text_box_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(text_box_qm) ? EQ(ISVREF(text_box_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(incomplete_box_translation_and_text_p(text_box_qm)) : 
	    TRUEP(Nil))
	delete_frame(text_box_qm);
    reclaim_frame_serial_number(FOURTH(hand_placement_return_information));
    return reclaim_gensym_list_1(hand_placement_return_information);
}

/* ACT-ON-CHOICE-OF-A-TREND-CHART */
Object act_on_choice_of_a_trend_chart(class_1,image_plane,x_in_window,
	    y_in_window)
    Object class_1, image_plane, x_in_window, y_in_window;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(119,52);
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
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return manifest_item_creation(make_trend_chart(class_1),
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qtable_rows;         /* table-rows */

/* DESCRIBE-RESTRICTIONS-ON-TEMPORARY-WORKSPACE */
Object describe_restrictions_on_temporary_workspace(item,pane)
    Object item, pane;
{
    Object table, workspace, temp, first_row, cell_qm, ab_loop_list_;
    Object title_text_qm, ab_loop_it_, table_rows_old_value, svref_new_value;
    char temp_1;

    x_note_fn_call(119,53);
    table = make_table_describing_restrictions(item);
    workspace = make_workspace(4,Qtemporary_workspace,Nil,table,
	    FIX((SI_Long)2L));
    if (New_g2_classic_ui_p) {
	change_slot_value(3,workspace,Qworkspace_background_color_qm,
		get_ui_parameter(1,Qsystem_workspace_background_color));
	temp = ISVREF(table,(SI_Long)19L);
	first_row = FIRST(temp);
	cell_qm = Nil;
	ab_loop_list_ = first_row;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	cell_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (cell_qm && CONSP(cell_qm)) {
	    title_text_qm = copy_text(CDDDR(cell_qm));
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	title_text_qm = Qnil;
      end_1:;
	if (title_text_qm) {
	    temp = ISVREF(table,(SI_Long)19L);
	    temp_1 = TRUEP(CDR(temp));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cell_qm = Nil;
	    ab_loop_list_ = first_row;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    cell_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = cell_qm ? (ATOM(cell_qm) ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    table_rows_old_value = ISVREF(table,(SI_Long)19L);
	    svref_new_value = REST(table_rows_old_value);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(table,Qtable_rows);
	    SVREF(table,FIX((SI_Long)19L)) = svref_new_value;
	    reclaim_slot_value(first_row);
	    reformat_table_in_place(3,table,T,
		    FIX(IFIX(get_total_title_bar_text_width(title_text_qm)) 
		    + (SI_Long)33L));
	    change_slot_value(3,workspace,Qtitle_bar_caption_text,
		    title_text_qm);
	    shrink_wrap_workspace(workspace);
	}
	else if (title_text_qm)
	    reclaim_text(title_text_qm);
    }
    return put_workspace_on_pane_function(workspace,pane,Qleft,Qtop,Nil,
	    FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

Object The_type_description_of_meter_or_dial_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_meter_or_dial_spots, Qchain_of_available_meter_or_dial_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Meter_or_dial_spot_count, Qmeter_or_dial_spot_count);

Object Chain_of_available_meter_or_dial_spots_vector = UNBOUND;

/* METER-OR-DIAL-SPOT-STRUCTURE-MEMORY-USAGE */
Object meter_or_dial_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(119,54);
    temp = Meter_or_dial_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-METER-OR-DIAL-SPOT-COUNT */
Object outstanding_meter_or_dial_spot_count()
{
    Object def_structure_meter_or_dial_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(119,55);
    gensymed_symbol = IFIX(Meter_or_dial_spot_count);
    def_structure_meter_or_dial_spot_variable = 
	    Chain_of_available_meter_or_dial_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_meter_or_dial_spot_variable))
	goto end_loop;
    def_structure_meter_or_dial_spot_variable = 
	    ISVREF(def_structure_meter_or_dial_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-METER-OR-DIAL-SPOT-1 */
Object reclaim_meter_or_dial_spot_1(meter_or_dial_spot)
    Object meter_or_dial_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(119,56);
    inline_note_reclaim_cons(meter_or_dial_spot,Nil);
    structure_being_reclaimed = meter_or_dial_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(meter_or_dial_spot,(SI_Long)2L));
      SVREF(meter_or_dial_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_meter_or_dial_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(meter_or_dial_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_meter_or_dial_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = meter_or_dial_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-METER-OR-DIAL-SPOT */
Object reclaim_structure_for_meter_or_dial_spot(meter_or_dial_spot)
    Object meter_or_dial_spot;
{
    x_note_fn_call(119,57);
    return reclaim_meter_or_dial_spot_1(meter_or_dial_spot);
}

static Object Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct;  /* g2-defstruct-structure-name::meter-or-dial-spot-g2-struct */

/* MAKE-PERMANENT-METER-OR-DIAL-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_meter_or_dial_spot_structure_internal()
{
    Object def_structure_meter_or_dial_spot_variable;
    Object defstruct_g2_meter_or_dial_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(119,58);
    def_structure_meter_or_dial_spot_variable = Nil;
    atomic_incff_symval(Qmeter_or_dial_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_meter_or_dial_spot_variable = Nil;
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
	defstruct_g2_meter_or_dial_spot_variable = the_array;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_meter_or_dial_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_meter_or_dial_spot_variable = 
		defstruct_g2_meter_or_dial_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_meter_or_dial_spot_variable);
}

/* MAKE-METER-OR-DIAL-SPOT-1 */
Object make_meter_or_dial_spot_1()
{
    Object def_structure_meter_or_dial_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(119,59);
    def_structure_meter_or_dial_spot_variable = 
	    ISVREF(Chain_of_available_meter_or_dial_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_meter_or_dial_spot_variable) {
	svref_arg_1 = Chain_of_available_meter_or_dial_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_meter_or_dial_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct;
    }
    else
	def_structure_meter_or_dial_spot_variable = 
		make_permanent_meter_or_dial_spot_structure_internal();
    inline_note_allocate_cons(def_structure_meter_or_dial_spot_variable,Nil);
    SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_meter_or_dial_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_meter_or_dial_spot_variable);
}

Object The_type_description_of_dial_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_dial_spots, Qchain_of_available_dial_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Dial_spot_count, Qdial_spot_count);

Object Chain_of_available_dial_spots_vector = UNBOUND;

/* DIAL-SPOT-STRUCTURE-MEMORY-USAGE */
Object dial_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(119,60);
    temp = Dial_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DIAL-SPOT-COUNT */
Object outstanding_dial_spot_count()
{
    Object def_structure_dial_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(119,61);
    gensymed_symbol = IFIX(Dial_spot_count);
    def_structure_dial_spot_variable = Chain_of_available_dial_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_dial_spot_variable))
	goto end_loop;
    def_structure_dial_spot_variable = 
	    ISVREF(def_structure_dial_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DIAL-SPOT-1 */
Object reclaim_dial_spot_1(dial_spot)
    Object dial_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(119,62);
    inline_note_reclaim_cons(dial_spot,Nil);
    structure_being_reclaimed = dial_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(dial_spot,(SI_Long)2L));
      SVREF(dial_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_dial_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(dial_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_dial_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = dial_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DIAL-SPOT */
Object reclaim_structure_for_dial_spot(dial_spot)
    Object dial_spot;
{
    x_note_fn_call(119,63);
    return reclaim_dial_spot_1(dial_spot);
}

static Object Qg2_defstruct_structure_name_dial_spot_g2_struct;  /* g2-defstruct-structure-name::dial-spot-g2-struct */

/* MAKE-PERMANENT-DIAL-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_dial_spot_structure_internal()
{
    Object def_structure_dial_spot_variable, defstruct_g2_dial_spot_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(119,64);
    def_structure_dial_spot_variable = Nil;
    atomic_incff_symval(Qdial_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_dial_spot_variable = Nil;
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
	defstruct_g2_dial_spot_variable = the_array;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dial_spot_g2_struct;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_dial_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_dial_spot_variable = defstruct_g2_dial_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_dial_spot_variable);
}

/* MAKE-DIAL-SPOT-1 */
Object make_dial_spot_1()
{
    Object def_structure_dial_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(119,65);
    def_structure_dial_spot_variable = 
	    ISVREF(Chain_of_available_dial_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_dial_spot_variable) {
	svref_arg_1 = Chain_of_available_dial_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_dial_spot_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_dial_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dial_spot_g2_struct;
    }
    else
	def_structure_dial_spot_variable = 
		make_permanent_dial_spot_structure_internal();
    inline_note_allocate_cons(def_structure_dial_spot_variable,Nil);
    SVREF(def_structure_dial_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_dial_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_dial_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_dial_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_dial_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_dial_spot_variable);
}

Object The_type_description_of_meter_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_meter_spots, Qchain_of_available_meter_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Meter_spot_count, Qmeter_spot_count);

Object Chain_of_available_meter_spots_vector = UNBOUND;

/* METER-SPOT-STRUCTURE-MEMORY-USAGE */
Object meter_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(119,66);
    temp = Meter_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-METER-SPOT-COUNT */
Object outstanding_meter_spot_count()
{
    Object def_structure_meter_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(119,67);
    gensymed_symbol = IFIX(Meter_spot_count);
    def_structure_meter_spot_variable = Chain_of_available_meter_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_meter_spot_variable))
	goto end_loop;
    def_structure_meter_spot_variable = 
	    ISVREF(def_structure_meter_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-METER-SPOT-1 */
Object reclaim_meter_spot_1(meter_spot)
    Object meter_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(119,68);
    inline_note_reclaim_cons(meter_spot,Nil);
    structure_being_reclaimed = meter_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(meter_spot,(SI_Long)2L));
      SVREF(meter_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_meter_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(meter_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_meter_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = meter_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-METER-SPOT */
Object reclaim_structure_for_meter_spot(meter_spot)
    Object meter_spot;
{
    x_note_fn_call(119,69);
    return reclaim_meter_spot_1(meter_spot);
}

static Object Qg2_defstruct_structure_name_meter_spot_g2_struct;  /* g2-defstruct-structure-name::meter-spot-g2-struct */

/* MAKE-PERMANENT-METER-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_meter_spot_structure_internal()
{
    Object def_structure_meter_spot_variable, defstruct_g2_meter_spot_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(119,70);
    def_structure_meter_spot_variable = Nil;
    atomic_incff_symval(Qmeter_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_meter_spot_variable = Nil;
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
	defstruct_g2_meter_spot_variable = the_array;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_meter_spot_g2_struct;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_meter_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_meter_spot_variable = defstruct_g2_meter_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_meter_spot_variable);
}

/* MAKE-METER-SPOT-1 */
Object make_meter_spot_1()
{
    Object def_structure_meter_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(119,71);
    def_structure_meter_spot_variable = 
	    ISVREF(Chain_of_available_meter_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_meter_spot_variable) {
	svref_arg_1 = Chain_of_available_meter_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_meter_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_meter_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_meter_spot_g2_struct;
    }
    else
	def_structure_meter_spot_variable = 
		make_permanent_meter_spot_structure_internal();
    inline_note_allocate_cons(def_structure_meter_spot_variable,Nil);
    SVREF(def_structure_meter_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_meter_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_meter_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_meter_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_meter_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_meter_spot_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Color_parameters, Qcolor_parameters);

static Object Qdismiss_color_menu_after_choosing_qm;  /* dismiss-color-menu-after-choosing? */

/* PUT-DO-NOT-DISMISS-COLOR-MENU-AFTER-CHOOSING?-WHERE-SLOT-IS-ABSENT */
Object put_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent(color_parameters,
	    value)
    Object color_parameters, value;
{
    Object svref_arg_1;
    char svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,72);
    PUSH_SPECIAL_WITH_SYMBOL(Color_parameters,Qcolor_parameters,color_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Color_parameters,
		  Qdismiss_color_menu_after_choosing_qm);
      svref_arg_1 = Color_parameters;
      svref_new_value =  !TRUEP(value);
      SVREF(svref_arg_1,FIX((SI_Long)27L)) = svref_new_value ? T : Nil;
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* WRITE-COLOR-MENU-ORDERING-FROM-SLOT */
Object write_color_menu_ordering_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(119,73);
    return twrite_symbol(1,value);
}

static Object Qnone;               /* none */

/* COMPILE-COLOR-SET-SPEC-FOR-SLOT */
Object compile_color_set_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,74);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ATOM(parse_result)) {
	if (EQ(parse_result,Qnone))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(parse_result);
    }
    else
	return VALUES_1(CDR(parse_result));
}

static Object Qall_including_new_pastels;  /* all-including-new-pastels */

static Object string_constant_23;  /* "all, including the new pastels" */

static Object Qcm;                 /* \, */

/* WRITE-COLOR-SET-SPEC-FROM-SLOT */
Object write_color_set_spec_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(119,75);
    if (ATOM(value)) {
	if (EQ(value,Qall_including_new_pastels))
	    return tformat(1,string_constant_23);
	else {
	    temp = value;
	    if (temp);
	    else
		temp = Qnone;
	    return twrite_symbol(1,temp);
	}
    }
    else
	return write_symbol_list(3,value,Qcm,Nil);
}

static Object Qcolors_on_1st_level_color_menu;  /* colors-on-1st-level-color-menu */

/* PUT-COLORS-ON-1ST-LEVEL-COLOR-MENU */
Object put_colors_on_1st_level_color_menu(color_parameters_instance,value,
	    gensymed_symbol)
    Object color_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(119,76);
    if (EQ(value,Qnone))
	value = Nil;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(color_parameters_instance,
		Qcolors_on_1st_level_color_menu);
    return VALUES_1(SVREF(color_parameters_instance,FIX((SI_Long)23L)) = 
	    value);
}

static Object Qcolors_on_2nd_level_color_menu;  /* colors-on-2nd-level-color-menu */

/* PUT-COLORS-ON-2ND-LEVEL-COLOR-MENU */
Object put_colors_on_2nd_level_color_menu(color_parameters_instance,value,
	    gensymed_symbol)
    Object color_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(119,77);
    if (EQ(value,Qnone))
	value = Nil;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(color_parameters_instance,
		Qcolors_on_2nd_level_color_menu);
    return VALUES_1(SVREF(color_parameters_instance,FIX((SI_Long)24L)) = 
	    value);
}

/* WRITE-NUMBER-OF-MENU-COLUMNS-SPEC-FROM-SLOT */
Object write_number_of_menu_columns_spec_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(119,78);
    return twrite(value);
}

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

static Object Qbackground_color;   /* background-color */

static Object Qline_color;         /* line-color */

/* MAKE-TEXT-CELL-PLIST-FOR-COLOR-BACKGROUND */
Object make_text_cell_plist_for_color_background(color)
    Object color;
{
    Object temp;

    x_note_fn_call(119,79);
    temp = map_to_black_or_white(color);
    if (EQ(temp,Qwhite))
	temp = Qblack;
    else if (EQ(temp,Qblack))
	temp = Qwhite;
    else
	temp = Qnil;
    return slot_value_list_4(Qbackground_color,color,Qline_color,temp);
}

Object The_type_description_of_bounding_box_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_bounding_box_spots, Qchain_of_available_bounding_box_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Bounding_box_spot_count, Qbounding_box_spot_count);

Object Chain_of_available_bounding_box_spots_vector = UNBOUND;

/* BOUNDING-BOX-SPOT-STRUCTURE-MEMORY-USAGE */
Object bounding_box_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(119,80);
    temp = Bounding_box_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BOUNDING-BOX-SPOT-COUNT */
Object outstanding_bounding_box_spot_count()
{
    Object def_structure_bounding_box_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(119,81);
    gensymed_symbol = IFIX(Bounding_box_spot_count);
    def_structure_bounding_box_spot_variable = 
	    Chain_of_available_bounding_box_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_bounding_box_spot_variable))
	goto end_loop;
    def_structure_bounding_box_spot_variable = 
	    ISVREF(def_structure_bounding_box_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BOUNDING-BOX-SPOT-1 */
Object reclaim_bounding_box_spot_1(bounding_box_spot)
    Object bounding_box_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(119,82);
    inline_note_reclaim_cons(bounding_box_spot,Nil);
    structure_being_reclaimed = bounding_box_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(bounding_box_spot,(SI_Long)2L));
      SVREF(bounding_box_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_bounding_box_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(bounding_box_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_bounding_box_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = bounding_box_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BOUNDING-BOX-SPOT */
Object reclaim_structure_for_bounding_box_spot(bounding_box_spot)
    Object bounding_box_spot;
{
    x_note_fn_call(119,83);
    return reclaim_bounding_box_spot_1(bounding_box_spot);
}

static Object Qg2_defstruct_structure_name_bounding_box_spot_g2_struct;  /* g2-defstruct-structure-name::bounding-box-spot-g2-struct */

/* MAKE-PERMANENT-BOUNDING-BOX-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_bounding_box_spot_structure_internal()
{
    Object def_structure_bounding_box_spot_variable;
    Object defstruct_g2_bounding_box_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(119,84);
    def_structure_bounding_box_spot_variable = Nil;
    atomic_incff_symval(Qbounding_box_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_bounding_box_spot_variable = Nil;
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
	defstruct_g2_bounding_box_spot_variable = the_array;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bounding_box_spot_g2_struct;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_bounding_box_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_bounding_box_spot_variable = 
		defstruct_g2_bounding_box_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_bounding_box_spot_variable);
}

/* MAKE-BOUNDING-BOX-SPOT-1 */
Object make_bounding_box_spot_1()
{
    Object def_structure_bounding_box_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(119,85);
    def_structure_bounding_box_spot_variable = 
	    ISVREF(Chain_of_available_bounding_box_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_bounding_box_spot_variable) {
	svref_arg_1 = Chain_of_available_bounding_box_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_bounding_box_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bounding_box_spot_g2_struct;
    }
    else
	def_structure_bounding_box_spot_variable = 
		make_permanent_bounding_box_spot_structure_internal();
    inline_note_allocate_cons(def_structure_bounding_box_spot_variable,Nil);
    SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_bounding_box_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_bounding_box_spot_variable);
}

/* GENERATE-SPOT-FOR-BOUNDING-BOX */
Object generate_spot_for_bounding_box(bounding_box,mouse_pointer)
    Object bounding_box, mouse_pointer;
{
    x_note_fn_call(119,86);
    return push_last_spot(mouse_pointer,make_bounding_box_spot_1(),
	    bounding_box);
}

static Object Qbounding_box;       /* bounding-box */

/* MAKE-BOUNDING-BOX */
Object make_bounding_box(width,height)
    Object width, height;
{
    Object bounding_box;
    SI_Long doubled_border_width, svref_new_value;

    x_note_fn_call(119,87);
    bounding_box = make_free_text_box(2,
	    obtain_simple_text_string(FIX((SI_Long)0L)),Qbounding_box);
    doubled_border_width = IFIX(ISVREF(ISVREF(bounding_box,(SI_Long)17L),
	    (SI_Long)44L)) << (SI_Long)1L;
    set_edges_of_block(bounding_box,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    FIX(IFIX(width) + doubled_border_width),FIX(IFIX(height) + 
	    doubled_border_width));
    svref_new_value = IFIX(ISVREF(bounding_box,(SI_Long)5L)) | 
	    (SI_Long)524288L;
    ISVREF(bounding_box,(SI_Long)5L) = FIX(svref_new_value);
    return VALUES_1(bounding_box);
}

/* UPDATE-BORDER-OF-BOUNDING-BOX */
Object update_border_of_bounding_box(bounding_box,new_left_edge_qm,
	    new_top_edge_qm,new_right_edge_qm,new_bottom_edge_qm)
    Object bounding_box, new_left_edge_qm, new_top_edge_qm, new_right_edge_qm;
    Object new_bottom_edge_qm;
{
    x_note_fn_call(119,88);
    return update_border_of_text_box(bounding_box,new_left_edge_qm ? 
	    FIXNUM_MINUS(new_left_edge_qm,ISVREF(ISVREF(bounding_box,
	    (SI_Long)17L),(SI_Long)44L)) : Nil,new_top_edge_qm ? 
	    FIXNUM_MINUS(new_top_edge_qm,ISVREF(ISVREF(bounding_box,
	    (SI_Long)17L),(SI_Long)44L)) : Nil,new_right_edge_qm ? 
	    FIXNUM_ADD(new_right_edge_qm,ISVREF(ISVREF(bounding_box,
	    (SI_Long)17L),(SI_Long)44L)) : Nil,new_bottom_edge_qm ? 
	    FIXNUM_ADD(new_bottom_edge_qm,ISVREF(ISVREF(bounding_box,
	    (SI_Long)17L),(SI_Long)44L)) : Nil);
}

Object The_type_description_of_bounding_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_bounding_states, Qchain_of_available_bounding_states);

DEFINE_VARIABLE_WITH_SYMBOL(Bounding_state_count, Qbounding_state_count);

Object Chain_of_available_bounding_states_vector = UNBOUND;

/* BOUNDING-STATE-STRUCTURE-MEMORY-USAGE */
Object bounding_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(119,89);
    temp = Bounding_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BOUNDING-STATE-COUNT */
Object outstanding_bounding_state_count()
{
    Object def_structure_bounding_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(119,90);
    gensymed_symbol = IFIX(Bounding_state_count);
    def_structure_bounding_state_variable = Chain_of_available_bounding_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_bounding_state_variable))
	goto end_loop;
    def_structure_bounding_state_variable = 
	    ISVREF(def_structure_bounding_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BOUNDING-STATE-1 */
Object reclaim_bounding_state_1(bounding_state)
    Object bounding_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(119,91);
    inline_note_reclaim_cons(bounding_state,Nil);
    structure_being_reclaimed = bounding_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(bounding_state,(SI_Long)1L));
      SVREF(bounding_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(bounding_state,(SI_Long)2L));
      SVREF(bounding_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_bounding_states_vector,
	    IFIX(Current_thread_index));
    SVREF(bounding_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_bounding_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = bounding_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BOUNDING-STATE */
Object reclaim_structure_for_bounding_state(bounding_state)
    Object bounding_state;
{
    x_note_fn_call(119,92);
    return reclaim_bounding_state_1(bounding_state);
}

static Object Qg2_defstruct_structure_name_bounding_state_g2_struct;  /* g2-defstruct-structure-name::bounding-state-g2-struct */

/* MAKE-PERMANENT-BOUNDING-STATE-STRUCTURE-INTERNAL */
Object make_permanent_bounding_state_structure_internal()
{
    Object def_structure_bounding_state_variable;
    Object defstruct_g2_bounding_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(119,93);
    def_structure_bounding_state_variable = Nil;
    atomic_incff_symval(Qbounding_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_bounding_state_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_bounding_state_variable = the_array;
	SVREF(defstruct_g2_bounding_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bounding_state_g2_struct;
	SVREF(defstruct_g2_bounding_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_bounding_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_bounding_state_variable = 
		defstruct_g2_bounding_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_bounding_state_variable);
}

/* MAKE-BOUNDING-STATE-1 */
Object make_bounding_state_1(bounding_dialog_workspace,
	    bounding_state_bounding_box,
	    bounding_state_constrained_width_qm,
	    bounding_state_constrained_height_qm,
	    edge_or_corner_of_bounding_box_qm,
	    x_offset_from_bounding_box_qm,y_offset_from_bounding_box_qm,
	    sizing_box_corner_x0,sizing_box_corner_y0,bounding_image_plane,
	    block_to_be_bounded_qm,workspace_for_bounding_box)
    Object bounding_dialog_workspace, bounding_state_bounding_box;
    Object bounding_state_constrained_width_qm;
    Object bounding_state_constrained_height_qm;
    Object edge_or_corner_of_bounding_box_qm, x_offset_from_bounding_box_qm;
    Object y_offset_from_bounding_box_qm, sizing_box_corner_x0;
    Object sizing_box_corner_y0, bounding_image_plane, block_to_be_bounded_qm;
    Object workspace_for_bounding_box;
{
    Object def_structure_bounding_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(119,94);
    def_structure_bounding_state_variable = 
	    ISVREF(Chain_of_available_bounding_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_bounding_state_variable) {
	temp = Chain_of_available_bounding_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_bounding_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_bounding_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bounding_state_g2_struct;
    }
    else
	def_structure_bounding_state_variable = 
		make_permanent_bounding_state_structure_internal();
    inline_note_allocate_cons(def_structure_bounding_state_variable,Nil);
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)3L)) = 
	    bounding_dialog_workspace;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)4L)) = 
	    bounding_state_bounding_box;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)5L)) = 
	    bounding_state_constrained_width_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)6L)) = 
	    bounding_state_constrained_height_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)7L)) = 
	    edge_or_corner_of_bounding_box_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)8L)) = 
	    x_offset_from_bounding_box_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)9L)) = 
	    y_offset_from_bounding_box_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)10L)) = 
	    sizing_box_corner_x0;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)11L)) = 
	    sizing_box_corner_y0;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)12L)) = 
	    bounding_image_plane;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)13L)) = 
	    block_to_be_bounded_qm;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)14L)) = 
	    workspace_for_bounding_box;
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_bounding_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_bounding_state_variable);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-BOUNDING-STATE */
Object valid_workstation_context_p_for_bounding_state(bounding_state)
    Object bounding_state;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(119,95);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_bounding_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = bounding_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)3L),
		(SI_Long)3L);
	x = ISVREF(bounding_state,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(bounding_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)4L),
		(SI_Long)3L);
	x = ISVREF(bounding_state,(SI_Long)4L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(bounding_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp =  !TRUEP(ISVREF(bounding_state,(SI_Long)13L));
	if (temp);
	else {
	    gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)13L),
		    (SI_Long)3L);
	    x = ISVREF(bounding_state,(SI_Long)13L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(bounding_state,(SI_Long)2L);
		if (FIXNUMP(y))
		    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp =  !temp;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)14L),
		(SI_Long)3L);
	x = ISVREF(bounding_state,(SI_Long)14L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(bounding_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return memq_function(ISVREF(bounding_state,(SI_Long)12L),
		ISVREF(ISVREF(bounding_state,(SI_Long)14L),(SI_Long)16L));
    else
	return VALUES_1(Nil);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-BOUNDING-STATE */
Object clean_up_workstation_context_for_bounding_state(bounding_state)
    Object bounding_state;
{
    Object gensymed_symbol, x, y, xa, ya, gensymed_symbol_1;
    char temp;

    x_note_fn_call(119,96);
    gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)3L),(SI_Long)3L);
    x = ISVREF(bounding_state,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(bounding_state,(SI_Long)2L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp)
	delete_frame(ISVREF(bounding_state,(SI_Long)3L));
    gensymed_symbol = ISVREF(ISVREF(bounding_state,(SI_Long)4L),(SI_Long)3L);
    x = ISVREF(bounding_state,(SI_Long)4L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(bounding_state,(SI_Long)2L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp)
	delete_frame(ISVREF(bounding_state,(SI_Long)4L));
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_bounding_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = bounding_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object string_constant_24;  /* "Select operation on area after moving its edges and corners" */

static Object list_constant_11;    /* # */

/* OPERATE-ON-AREA-OF-WORKSPACE */
Object operate_on_area_of_workspace(workspace,image_plane,
	    original_x_in_window,original_y_in_window)
    Object workspace, image_plane, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(119,97);
    return enter_bounding_dialog(8,string_constant_24,list_constant_11,Nil,
	    workspace,image_plane,original_x_in_window,
	    original_y_in_window,FIX((SI_Long)110L));
}

Object Sizing_dialog_message_string = UNBOUND;

static Object list_constant_12;    /* # */

/* ENTER-SIZING-DIALOG */
Object enter_sizing_dialog(block,image_plane,original_x_in_window,
	    original_y_in_window)
    Object block, image_plane, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(119,98);
    return enter_bounding_dialog(7,Sizing_dialog_message_string,
	    list_constant_12,block,get_workspace_if_any(block),image_plane,
	    original_x_in_window,original_y_in_window);
}

static Object list_constant_13;    /* # */

/* ENTER-MIN-SIZING-DIALOG */
Object enter_min_sizing_dialog(block,image_plane,original_x_in_window,
	    original_y_in_window)
    Object block, image_plane, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(119,99);
    return enter_bounding_dialog(7,Sizing_dialog_message_string,
	    list_constant_13,block,get_workspace_if_any(block),image_plane,
	    original_x_in_window,original_y_in_window);
}

static Object Qbounding;           /* bounding */

/* ENTER-BOUNDING-DIALOG */
Object enter_bounding_dialog varargs_1(int, n)
{
    Object message_string, rows_of_button_names, block_for_bounding_box_qm;
    Object workspace_for_bounding_box, image_plane, x_in_window, y_in_window;
    Object minimum_width_of_button_qm, gensymed_symbol, temp, temp_1;
    Object bounding_box, bounding_box_border_width, x_in_workspace;
    Object y_in_workspace, current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, workspace;
    Object sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3;
    char temp_3;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(119,100);
    INIT_ARGS_nonrelocating();
    message_string = REQUIRED_ARG_nonrelocating();
    rows_of_button_names = REQUIRED_ARG_nonrelocating();
    block_for_bounding_box_qm = REQUIRED_ARG_nonrelocating();
    workspace_for_bounding_box = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    minimum_width_of_button_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (block_for_bounding_box_qm) {
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else
	temp = FIX((SI_Long)100L);
    if (block_for_bounding_box_qm) {
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else
	temp_1 = FIX((SI_Long)100L);
    bounding_box = make_bounding_box(temp,temp_1);
    bounding_box_border_width = ISVREF(ISVREF(bounding_box,(SI_Long)17L),
	    (SI_Long)44L);
    x_in_workspace = Nil;
    y_in_workspace = Nil;
    current_frame_transform_qm = Nil;
    current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
    current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
		    0);
	      scale = Current_image_x_scale;
	      value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  x_in_workspace = value;
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  x_in_workspace = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		  x_in_workspace = temp_1;
	      }
	      else {
		  temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = FIXNUM_NEGATE(FIX(temp_2));
		  x_in_workspace = temp_1;
	      }
	      scale = Current_image_y_scale;
	      value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  y_in_workspace = value;
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  y_in_workspace = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		  y_in_workspace = temp_1;
	      }
	      else {
		  temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = FIXNUM_NEGATE(FIX(temp_2));
		  y_in_workspace = temp_1;
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (block_for_bounding_box_qm) {
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
    }
    else
	gensymed_symbol_1 = IFIX(x_in_workspace);
    gensymed_symbol_2 = IFIX(bounding_box_border_width);
    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    if (block_for_bounding_box_qm) {
	gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
    }
    else
	gensymed_symbol_1 = IFIX(y_in_workspace);
    gensymed_symbol_2 = IFIX(bounding_box_border_width);
    add_to_workspace(6,bounding_box,workspace_for_bounding_box,temp_1,
	    FIX(gensymed_symbol_1 - gensymed_symbol_2),T,T);
    workspace = make_workspace(4,Qtemporary_workspace,Nil,
	    make_dialog_message(message_string),FIX((SI_Long)10L));
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(workspace,(SI_Long)17L));
    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    set_up_bounding_dialog_ws(5,rows_of_button_names,workspace,temp_1,
	    gensymed_symbol,minimum_width_of_button_qm);
    put_workspace_on_pane_function(workspace,
	    Current_workstation_detail_pane,Qleft,Qtop,T,FIX((SI_Long)11L),
	    Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    if (block_for_bounding_box_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(block_for_bounding_box_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    temp_3 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_3 = TRUEP(Nil);
	if ( !temp_3) {
	    gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    if (block_for_bounding_box_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(block_for_bounding_box_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    temp_3 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_3 = TRUEP(Nil);
	if ( !temp_3) {
	    gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block_for_bounding_box_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return enter_context_in_current_workstation(2,Qbounding,
	    make_bounding_state_1(workspace,bounding_box,temp,temp_1,Nil,
	    Nil,Nil,Nil,Nil,image_plane,block_for_bounding_box_qm,
	    workspace_for_bounding_box));
}

/* SIZING-OK */
Object sizing_ok()
{
    Object bounding_state, block, bounding_box, text_box_format;
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box;

    x_note_fn_call(119,101);
    bounding_state = Specific_structure_for_current_workstation_context;
    block = ISVREF(bounding_state,(SI_Long)13L);
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    change_size_per_bounding_rectangle(5,block,
	    FIX(left_edge_of_bounding_box),FIX(top_edge_of_bounding_box),
	    FIX(right_edge_of_bounding_box),FIX(bottom_edge_of_bounding_box));
    return_from_current_workstation_context(1,Qbounding);
    return VALUES_1(Nil);
}

/* SIZING-QUIT */
Object sizing_quit()
{
    x_note_fn_call(119,102);
    return_from_current_workstation_context(1,Qbounding);
    return VALUES_1(Nil);
}

static Object Qtrend_chart;        /* trend-chart */

/* RESTORE-ITEM-TO-NORMAL-SIZE */
Object restore_item_to_normal_size(block)
    Object block;
{
    Object gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(119,103);
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	return magnify_icon(block,Nil,Nil,Nil,Nil,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	    return restore_graph_to_normal_size(block);
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qtrend_chart,
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
	    if (temp)
		return restore_trend_chart_to_normal_size(block);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Chart_class_description,(SI_Long)18L));
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
		if (temp)
		    return restore_chart_to_normal_size(block);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Text_box_class_description,
			    (SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			return restore_size_of_text_box(block);
		    else
			return VALUES_1(Qnil);
		}
	    }
	}
    }
}

/* SIZING-RESTORE */
Object sizing_restore()
{
    Object bounding_state, block, bounding_box, text_box_format;

    x_note_fn_call(119,104);
    bounding_state = Specific_structure_for_current_workstation_context;
    block = ISVREF(bounding_state,(SI_Long)13L);
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    restore_item_to_normal_size(block);
    fit_bounding_box_around_block(bounding_box,block,text_box_format);
    return VALUES_1(Nil);
}

/* SIZING-UPDATE */
Object sizing_update()
{
    Object bounding_state, block, bounding_box, text_box_format;
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box;

    x_note_fn_call(119,105);
    bounding_state = Specific_structure_for_current_workstation_context;
    block = ISVREF(bounding_state,(SI_Long)13L);
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    change_size_per_bounding_rectangle(5,block,
	    FIX(left_edge_of_bounding_box),FIX(top_edge_of_bounding_box),
	    FIX(right_edge_of_bounding_box),FIX(bottom_edge_of_bounding_box));
    fit_bounding_box_around_block(bounding_box,block,text_box_format);
    return VALUES_1(Nil);
}

/* SIZING-NO-MINIMUM */
Object sizing_no_minimum()
{
    Object bounding_state, block;

    x_note_fn_call(119,106);
    bounding_state = Specific_structure_for_current_workstation_context;
    block = ISVREF(bounding_state,(SI_Long)13L);
    restore_size_of_text_box(block);
    return VALUES_1(Nil);
}

static Object Qminimum_width_of_text_box;  /* minimum-width-of-text-box */

static Object Qminimum_height_of_text_box;  /* minimum-height-of-text-box */

/* RESTORE-SIZE-OF-TEXT-BOX */
Object restore_size_of_text_box(text_box)
    Object text_box;
{
    x_note_fn_call(119,107);
    update_images_of_block(text_box,T,T);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_box,Qminimum_width_of_text_box);
    set_lookup_slot_value_1(text_box,Qminimum_width_of_text_box,
	    FIX((SI_Long)0L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_box,Qminimum_height_of_text_box);
    set_lookup_slot_value_1(text_box,Qminimum_height_of_text_box,
	    FIX((SI_Long)0L));
    reformat_text_box_in_place(1,text_box);
    return update_images_of_block(text_box,Nil,T);
}

static Object Qmove;               /* move */

static Object Qtransfer;           /* transfer */

static Object Qclone;              /* clone */

/* MOVE-AREA */
Object move_area()
{
    Object bounding_state, bounding_box, text_box_format, gensymed_symbol;
    Object specific_image_plane_for_bounding_box, blocks_in_bounding_box;
    Object blocks_to_drag;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box, x_offset_from_dragger;
    SI_Long y_offset_from_dragger;

    x_note_fn_call(119,108);
    bounding_state = Specific_structure_for_current_workstation_context;
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    specific_image_plane_for_bounding_box = ISVREF(bounding_state,
	    (SI_Long)12L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    blocks_in_bounding_box = prepare_blocks_for_operation_on_area(7,
	    gensymed_symbol,FIX(left_edge_of_bounding_box),
	    FIX(top_edge_of_bounding_box),FIX(right_edge_of_bounding_box),
	    FIX(bottom_edge_of_bounding_box),EQ(Qmove,Qtransfer) ? T : Nil,
	    EQ(Qmove,Qclone) ? T : Nil);
    warp_cursor_for_bounding_state_button(bounding_state,Qmove);
    if (blocks_in_bounding_box) {
	blocks_to_drag = dragging_cons_function(bounding_box,
		blocks_in_bounding_box);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	x_offset_from_dragger = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	y_offset_from_dragger = gensymed_symbol_1 - gensymed_symbol_2;
	enter_move_dragging_context(5,blocks_to_drag,
		FIX(x_offset_from_dragger),FIX(y_offset_from_dragger),
		specific_image_plane_for_bounding_box,Nil);
    }
    return VALUES_1(Nil);
}

static Object Qfix_up_bounding_state_if_necessary_after_transfer;  /* fix-up-bounding-state-if-necessary-after-transfer */

static Object Qtransfer_source;    /* transfer-source */

/* TRANSFER-AREA */
Object transfer_area()
{
    Object bounding_state, bounding_box, text_box_format, gensymed_symbol;
    Object specific_image_plane_for_bounding_box, blocks_in_bounding_box;
    Object blocks_to_drag;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box, x_offset_from_dragger;
    SI_Long y_offset_from_dragger;

    x_note_fn_call(119,109);
    bounding_state = Specific_structure_for_current_workstation_context;
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    specific_image_plane_for_bounding_box = ISVREF(bounding_state,
	    (SI_Long)12L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    blocks_in_bounding_box = prepare_blocks_for_operation_on_area(7,
	    gensymed_symbol,FIX(left_edge_of_bounding_box),
	    FIX(top_edge_of_bounding_box),FIX(right_edge_of_bounding_box),
	    FIX(bottom_edge_of_bounding_box),EQ(Qtransfer,Qtransfer) ? T : 
	    Nil,EQ(Qtransfer,Qclone) ? T : Nil);
    warp_cursor_for_bounding_state_button(bounding_state,Qtransfer);
    if (blocks_in_bounding_box) {
	blocks_to_drag = dragging_cons_function(bounding_box,
		blocks_in_bounding_box);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	x_offset_from_dragger = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	y_offset_from_dragger = gensymed_symbol_1 - gensymed_symbol_2;
	establish_next_workstation_context_continuation(Qfix_up_bounding_state_if_necessary_after_transfer,
		Nil,Nil,Nil);
	if (ISVREF(specific_image_plane_for_bounding_box,(SI_Long)5L))
	    invoke_workspace_invalidation_handler_if_any(ISVREF(specific_image_plane_for_bounding_box,
		    (SI_Long)5L),Qtransfer_source);
	enter_transfer_dragging_context(6,blocks_to_drag,
		FIX(x_offset_from_dragger),FIX(y_offset_from_dragger),
		specific_image_plane_for_bounding_box,Nil,Nil);
    }
    return VALUES_1(Nil);
}

/* CLONE-AREA */
Object clone_area()
{
    Object bounding_state, bounding_box, text_box_format, gensymed_symbol;
    Object specific_image_plane_for_bounding_box, blocks_in_bounding_box;
    Object dragging_list_of_cloned_blocks, region_invalidation_is_preferred;
    Object temp, temp_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box;
    Declare_special(1);

    x_note_fn_call(119,110);
    bounding_state = Specific_structure_for_current_workstation_context;
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    specific_image_plane_for_bounding_box = ISVREF(bounding_state,
	    (SI_Long)12L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    blocks_in_bounding_box = prepare_blocks_for_operation_on_area(7,
	    gensymed_symbol,FIX(left_edge_of_bounding_box),
	    FIX(top_edge_of_bounding_box),FIX(right_edge_of_bounding_box),
	    FIX(bottom_edge_of_bounding_box),EQ(Qclone,Qtransfer) ? T : 
	    Nil,EQ(Qclone,Qclone) ? T : Nil);
    warp_cursor_for_bounding_state_button(bounding_state,Qclone);
    if (blocks_in_bounding_box) {
	dragging_list_of_cloned_blocks = clone_blocks(blocks_in_bounding_box);
	reclaim_dragging_list_function(blocks_in_bounding_box);
	region_invalidation_is_preferred = T;
	PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		0);
	  update_images_of_block(bounding_box,T,T);
	  remove_as_subblock_if_necessary(1,bounding_box);
	POP_SPECIAL();
	establish_next_workstation_context_continuation(Qfix_up_bounding_state_if_necessary_after_transfer,
		Nil,Nil,Nil);
	temp = dragging_cons_function(bounding_box,
		dragging_list_of_cloned_blocks);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	enter_transfer_dragging_context(4,temp,temp_1,
		FIX(gensymed_symbol_1 - gensymed_symbol_2),
		specific_image_plane_for_bounding_box);
    }
    return VALUES_1(Nil);
}

/* CLONE-BLOCKS */
Object clone_blocks(blocks)
    Object blocks;
{
    Object block, ab_loop_list_, new_block, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, plist_of_blocks_and_corresponding_clones;
    Object cloned_block, x_shift, y_shift, temp, gensymed_symbol, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object block_at_other_end, ab_less_than_branch_qm_;
    Object dragging_list_of_cloned_blocks, sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(119,111);
    block = Nil;
    ab_loop_list_ = blocks;
    new_block = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_block = clone_frame(2,block,blocks);
    set_neither_permanent_nor_transient_and_propagate(new_block,Nil);
    ab_loopvar__2 = gensym_list_2(block,new_block);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    plist_of_blocks_and_corresponding_clones = ab_loopvar_;
    goto end_1;
    plist_of_blocks_and_corresponding_clones = Qnil;
  end_1:;
    block = Nil;
    cloned_block = Nil;
    ab_loop_list_ = plist_of_blocks_and_corresponding_clones;
    x_shift = Nil;
    y_shift = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
  next_loop_1:
    block = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    cloned_block = CAR(temp);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(cloned_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    x_shift = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(cloned_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    y_shift = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    clone_connections_for_block(block,cloned_block,
	    plist_of_blocks_and_corresponding_clones);
    shift_block(cloned_block,x_shift,y_shift);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(cloned_block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
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
      block_at_other_end = Nil;
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
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_2;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_2;
      goto next_loop_3;
    end_loop_3:
    end_2:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_4;
      connection = ab_connection_;
      block_at_other_end = get_block_at_other_end_of_connection(connection,
	      cloned_block);
      if ( !TRUEP(memq_function(block_at_other_end,
	      plist_of_blocks_and_corresponding_clones)))
	  shift_block(block_at_other_end,x_shift,y_shift);
      goto next_loop_2;
    end_loop_4:;
    POP_SPECIAL();
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:
    cloned_block = Nil;
    ab_loop_list_ = plist_of_blocks_and_corresponding_clones;
    dragging_list_of_cloned_blocks = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
  next_loop_5:
    temp = CDR(ab_loop_list_);
    cloned_block = CAR(temp);
    sub_class_bit_vector = ISVREF(ISVREF(cloned_block,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	temp_1 = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1) {
	ab_loopvar__1 = dragging_cons_function(cloned_block,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    dragging_list_of_cloned_blocks = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    goto next_loop_5;
  end_loop_5:
    reclaim_gensym_list_1(plist_of_blocks_and_corresponding_clones);
    return VALUES_1(dragging_list_of_cloned_blocks);
    return VALUES_1(Qnil);
}

/* DELETE-AREA */
Object delete_area()
{
    Object bounding_state, bounding_box, text_box_format, gensymed_symbol;
    Object blocks_in_bounding_box;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box;

    x_note_fn_call(119,112);
    bounding_state = Specific_structure_for_current_workstation_context;
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    blocks_in_bounding_box = prepare_blocks_for_operation_on_area(7,
	    gensymed_symbol,FIX(left_edge_of_bounding_box),
	    FIX(top_edge_of_bounding_box),FIX(right_edge_of_bounding_box),
	    FIX(bottom_edge_of_bounding_box),EQ(Qdelete,Qtransfer) ? T : 
	    Nil,EQ(Qdelete,Qclone) ? T : Nil);
    delete_blocks_for_operate_on_area_after_confirmation(blocks_in_bounding_box);
    return VALUES_1(Nil);
}

/* ALIGN-FOR-OPERATE-ON-AREA */
Object align_for_operate_on_area(button_name)
    Object button_name;
{
    Object bounding_state, bounding_box, text_box_format, gensymed_symbol;
    Object blocks_in_bounding_box;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_bounding_box;
    SI_Long top_edge_of_bounding_box, right_edge_of_bounding_box;
    SI_Long bottom_edge_of_bounding_box;

    x_note_fn_call(119,113);
    bounding_state = Specific_structure_for_current_workstation_context;
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    text_box_format = ISVREF(bounding_box,(SI_Long)17L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    left_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    top_edge_of_bounding_box = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    right_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    bottom_edge_of_bounding_box = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    blocks_in_bounding_box = prepare_blocks_for_operation_on_area(7,
	    gensymed_symbol,FIX(left_edge_of_bounding_box),
	    FIX(top_edge_of_bounding_box),FIX(right_edge_of_bounding_box),
	    FIX(bottom_edge_of_bounding_box),EQ(button_name,Qtransfer) ? T 
	    : Nil,EQ(button_name,Qclone) ? T : Nil);
    if (blocks_in_bounding_box)
	align_blocks(blocks_in_bounding_box,button_name);
    return VALUES_1(Nil);
}

static Object Ql_r_center;         /* l-r-center */

static Object Qleft_sl_right_center;  /* left/right-center */

static Object Qt_b_center;         /* t-b-center */

static Object Qtop_sl_bottom_center;  /* top/bottom-center */

/* ALIGN-BLOCKS */
Object align_blocks(blocks,operation)
    Object blocks, operation;
{
    Object block, ab_loop_list_, extreme_left_edge, ab_loopvar_;
    Object ab_loop_maxmin_fl_, extreme_right_edge, ab_loop_maxmin_fl__1;
    Object extreme_top_edge, ab_loop_maxmin_fl__2, extreme_bottom_edge;
    Object ab_loop_maxmin_fl__3, gensymed_symbol, workspace, delta_x, delta_y;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(119,114);
    block = Nil;
    ab_loop_list_ = blocks;
    extreme_left_edge = FIX((SI_Long)0L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
    extreme_right_edge = FIX((SI_Long)0L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_maxmin_fl__1 = T;
    extreme_top_edge = FIX((SI_Long)0L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_maxmin_fl__2 = T;
    extreme_bottom_edge = FIX((SI_Long)0L);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_maxmin_fl__3 = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    ab_loopvar_ = gensymed_symbol;
    if (ab_loop_maxmin_fl_) {
	ab_loop_maxmin_fl_ = Nil;
	extreme_left_edge = ab_loopvar_;
    }
    else
	extreme_left_edge = FIXNUM_MIN(extreme_left_edge,ab_loopvar_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    ab_loopvar_ = gensymed_symbol;
    if (ab_loop_maxmin_fl__1) {
	ab_loop_maxmin_fl__1 = Nil;
	extreme_right_edge = ab_loopvar_;
    }
    else
	extreme_right_edge = FIXNUM_MAX(extreme_right_edge,ab_loopvar_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    ab_loopvar_ = gensymed_symbol;
    if (ab_loop_maxmin_fl__2) {
	ab_loop_maxmin_fl__2 = Nil;
	extreme_top_edge = ab_loopvar_;
    }
    else
	extreme_top_edge = FIXNUM_MIN(extreme_top_edge,ab_loopvar_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    ab_loopvar_ = gensymed_symbol;
    if (ab_loop_maxmin_fl__3) {
	ab_loop_maxmin_fl__3 = Nil;
	extreme_bottom_edge = ab_loopvar_;
    }
    else
	extreme_bottom_edge = FIXNUM_MAX(extreme_bottom_edge,ab_loopvar_);
    goto next_loop;
  end_loop:
    workspace = get_workspace_if_any(CAR(blocks));
    block = Nil;
    ab_loop_list_ = blocks;
    delta_x = Nil;
    delta_y = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(operation,Qleft)) {
	gensymed_symbol_1 = IFIX(extreme_left_edge);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_x = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(operation,Qright)) {
	gensymed_symbol_1 = IFIX(extreme_right_edge);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_x = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(operation,Ql_r_center) || EQ(operation,
		Qleft_sl_right_center)) {
	gensymed_symbol_1 = IFIX(FIXNUM_ADD(extreme_left_edge,
		extreme_right_edge)) >>  -  - (SI_Long)1L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	delta_x = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else
	delta_x = FIX((SI_Long)0L);
    if (EQ(operation,Qtop)) {
	gensymed_symbol_1 = IFIX(extreme_top_edge);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_y = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(operation,Qbottom)) {
	gensymed_symbol_1 = IFIX(extreme_bottom_edge);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_y = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(operation,Qt_b_center) || EQ(operation,
		Qtop_sl_bottom_center)) {
	gensymed_symbol_1 = IFIX(FIXNUM_ADD(extreme_top_edge,
		extreme_bottom_edge)) >>  -  - (SI_Long)1L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	delta_y = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else
	delta_y = FIX((SI_Long)0L);
    move_blocks_with_their_external_connections(block,workspace,delta_x,
	    delta_y);
    if (G2_has_v5_mode_windows_p)
	send_ws_representations_item_moved(block,delta_x,delta_y);
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(Qnil);
}

static Object Qhorizontally;       /* horizontally */

static Object Qmidline_x_of_block_function;  /* midline-x-of-block-function */

static Object Qvertically;         /* vertically */

static Object Qmidline_y_of_block_function;  /* midline-y-of-block-function */

/* DISTRIBUTE-BLOCKS */
Object distribute_blocks(blocks,operation)
    Object blocks, operation;
{
    Object temp, sorted_blocks, workspace, gensymed_symbol, min_1, max_1;
    Object blocks_to_move, block, ab_loop_list_, ab_loopvar_;
    Object ab_loop_iter_flag_, pos, sum_extents, delta;
    SI_Long n_1, gensymed_symbol_1, gensymed_symbol_2, ab_loop_bind_, i;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    double spacing;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(119,115);
    temp = IFIX(length(blocks)) <= (SI_Long)2L ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (EQ(operation,Qhorizontally)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    sorted_blocks = 
		    sort_list(copy_list_using_gensym_conses_1(blocks),
		    SYMBOL_FUNCTION(Qnum_lt),
		    SYMBOL_FUNCTION(Qmidline_x_of_block_function));
	    workspace = get_workspace_if_any(CAR(sorted_blocks));
	    gensymed_symbol = ISVREF(CAR(sorted_blocks),(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    min_1 = gensymed_symbol;
	    temp = last(sorted_blocks,_);
	    gensymed_symbol = ISVREF(CAR(temp),(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    max_1 = gensymed_symbol;
	    blocks_to_move = CDR(sorted_blocks);
	    n_1 = IFIX(length(sorted_blocks)) - (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(max_1);
	    gensymed_symbol_2 = IFIX(min_1);
	    block = Nil;
	    ab_loop_list_ = blocks_to_move;
	    ab_loop_bind_ = n_1;
	    i = (SI_Long)0L;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = IFIX(ab_loopvar_);
	    ab_loopvar_ = FIX(gensymed_symbol_3 + gensymed_symbol_4);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    gensymed_symbol_3 = IFIX(ab_loopvar_);
	    goto end_1;
	    gensymed_symbol_3 = IFIX(Qnil);
	  end_1:;
	    spacing = (double)(gensymed_symbol_1 - gensymed_symbol_2 - 
		    gensymed_symbol_3) / (double)((float)(n_1 + (SI_Long)1L));
	    block = Nil;
	    ab_loop_list_ = blocks_to_move;
	    i = (SI_Long)1L;
	    ab_loop_bind_ = n_1;
	    pos = Nil;
	    sum_extents = FIX((SI_Long)0L);
	    delta = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if (i > ab_loop_bind_)
		goto end_loop_1;
	    pos = l_round(addn(3,min_1,DOUBLE_TO_DOUBLE_FLOAT((double)i * 
		    spacing),sum_extents),_);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(sum_extents);
	    sum_extents = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(pos);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    delta = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    move_blocks_with_their_external_connections(block,workspace,
		    delta,FIX((SI_Long)0L));
	    if (G2_has_v5_mode_windows_p)
		send_ws_representations_item_moved(block,delta,
			FIX((SI_Long)0L));
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	    result = reclaim_gensym_list_1(sorted_blocks);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (EQ(operation,Qvertically)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    sorted_blocks = 
		    sort_list(copy_list_using_gensym_conses_1(blocks),
		    SYMBOL_FUNCTION(Qnum_lt),
		    SYMBOL_FUNCTION(Qmidline_y_of_block_function));
	    workspace = get_workspace_if_any(CAR(sorted_blocks));
	    gensymed_symbol = ISVREF(CAR(sorted_blocks),(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    min_1 = gensymed_symbol;
	    temp = last(sorted_blocks,_);
	    gensymed_symbol = ISVREF(CAR(temp),(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    max_1 = gensymed_symbol;
	    blocks_to_move = CDR(sorted_blocks);
	    n_1 = IFIX(length(sorted_blocks)) - (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(max_1);
	    gensymed_symbol_2 = IFIX(min_1);
	    block = Nil;
	    ab_loop_list_ = blocks_to_move;
	    ab_loop_bind_ = n_1;
	    i = (SI_Long)0L;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if (i >= ab_loop_bind_)
		goto end_loop_2;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = IFIX(ab_loopvar_);
	    ab_loopvar_ = FIX(gensymed_symbol_3 + gensymed_symbol_4);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_2;
	  end_loop_2:
	    gensymed_symbol_3 = IFIX(ab_loopvar_);
	    goto end_2;
	    gensymed_symbol_3 = IFIX(Qnil);
	  end_2:;
	    spacing = (double)(gensymed_symbol_1 - gensymed_symbol_2 - 
		    gensymed_symbol_3) / (double)((float)(n_1 + (SI_Long)1L));
	    block = Nil;
	    ab_loop_list_ = blocks_to_move;
	    i = (SI_Long)1L;
	    ab_loop_bind_ = n_1;
	    pos = Nil;
	    sum_extents = FIX((SI_Long)0L);
	    delta = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if (i > ab_loop_bind_)
		goto end_loop_3;
	    pos = l_round(addn(3,min_1,DOUBLE_TO_DOUBLE_FLOAT((double)i * 
		    spacing),sum_extents),_);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	    gensymed_symbol_2 = IFIX(sum_extents);
	    sum_extents = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(pos);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    delta = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    move_blocks_with_their_external_connections(block,workspace,
		    FIX((SI_Long)0L),delta);
	    if (G2_has_v5_mode_windows_p)
		send_ws_representations_item_moved(block,FIX((SI_Long)0L),
			delta);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:;
	    result = reclaim_gensym_list_1(sorted_blocks);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Qnil);
}

/* MOVE-AREA-TO-LEFT */
Object move_area_to_left()
{
    x_note_fn_call(119,116);
    align_for_operate_on_area(Qleft);
    return VALUES_1(Nil);
}

/* MOVE-AREA-TO-L-R-CENTER */
Object move_area_to_l_r_center()
{
    x_note_fn_call(119,117);
    align_for_operate_on_area(Ql_r_center);
    return VALUES_1(Nil);
}

/* MOVE-AREA-TO-RIGHT */
Object move_area_to_right()
{
    x_note_fn_call(119,118);
    align_for_operate_on_area(Qright);
    return VALUES_1(Nil);
}

/* MOVE-AREA-TO-TOP */
Object move_area_to_top()
{
    x_note_fn_call(119,119);
    align_for_operate_on_area(Qtop);
    return VALUES_1(Nil);
}

/* MOVE-AREA-TO-T-B-CENTER */
Object move_area_to_t_b_center()
{
    x_note_fn_call(119,120);
    align_for_operate_on_area(Qt_b_center);
    return VALUES_1(Nil);
}

/* MOVE-AREA-TO-BOTTOM */
Object move_area_to_bottom()
{
    x_note_fn_call(119,121);
    align_for_operate_on_area(Qbottom);
    return VALUES_1(Nil);
}

/* WARP-CURSOR-FOR-BOUNDING-STATE-BUTTON */
Object warp_cursor_for_bounding_state_button(bounding_state,button_name)
    Object bounding_state, button_name;
{
    Object bounding_box, specific_image_plane_for_bounding_box;
    Object gensymed_symbol, scale, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, x_in_workspace, value;
    SI_Long unshifted_result, y_in_workspace;

    x_note_fn_call(119,122);
    bounding_box = ISVREF(bounding_state,(SI_Long)4L);
    specific_image_plane_for_bounding_box = ISVREF(bounding_state,
	    (SI_Long)12L);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    gensymed_symbol_2 = EQ(button_name,Qclone) ? (SI_Long)2L : (SI_Long)0L;
    x_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(specific_image_plane_for_bounding_box,
	    (SI_Long)13L));
    scale = ISVREF(specific_image_plane_for_bounding_box,(SI_Long)11L);
    value = x_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    gensymed_symbol_2 = EQ(button_name,Qclone) ? (SI_Long)2L : (SI_Long)0L;
    y_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(specific_image_plane_for_bounding_box,
	    (SI_Long)14L));
    scale = ISVREF(specific_image_plane_for_bounding_box,(SI_Long)12L);
    value = y_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    return set_cursor_position(temp,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2));
}

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE */
Object change_size_per_bounding_rectangle varargs_1(int, n)
{
    Object block, left_edge, top_edge, right_edge, bottom_edge;
    Object mode, frame, sub_vector_qm, function_qm;
    SI_Long method_index;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,123);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    left_edge = REQUIRED_ARG_nonrelocating();
    top_edge = REQUIRED_ARG_nonrelocating();
    right_edge = REQUIRED_ARG_nonrelocating();
    bottom_edge = REQUIRED_ARG_nonrelocating();
    mode = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    method_index = (SI_Long)50L;
    frame = block;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    if (function_qm)
	return inline_funcall_6(function_qm,frame,left_edge,top_edge,
		right_edge,bottom_edge,mode);
    else
	return VALUES_1(Nil);
}

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-BLOCK */
Object change_size_per_bounding_rectangle_for_block(block,left_edge,
	    top_edge,right_edge,bottom_edge,mode)
    Object block, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(119,124);
    update_images_of_block(block,T,Nil);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(left_edge);
    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(top_edge);
    shift_block(block,temp,FIX(gensymed_symbol_1 - gensymed_symbol_2));
    enlarge_workspace_for_block_rectangle_if_necessary(block,Nil);
    return update_images_of_block(block,Nil,Nil);
}

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-KB-WORKSPACE */
Object change_size_per_bounding_rectangle_for_kb_workspace(kb_workspace,
	    left_edge,top_edge,right_edge,bottom_edge,mode)
    Object kb_workspace, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Declare_special(4);
    Object result;

    x_note_fn_call(119,125);
    gensymed_symbol = ISVREF(kb_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    gensymed_symbol = ISVREF(kb_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    extreme_top_edge_so_far = gensymed_symbol;
    gensymed_symbol = ISVREF(kb_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_right_edge_so_far = gensymed_symbol;
    gensymed_symbol = ISVREF(kb_workspace,(SI_Long)14L);
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
	    update_extreme_edges_from_elements_function(kb_workspace,Nil);
	    update_extreme_edges_from_background_images(kb_workspace);
	    change_workspace_edges_after_including_margin(kb_workspace,
		    FIXNUM_MIN(left_edge,Extreme_left_edge_so_far),
		    FIXNUM_MIN(top_edge,Extreme_top_edge_so_far),
		    FIXNUM_MAX(right_edge,Extreme_right_edge_so_far),
		    FIXNUM_MAX(bottom_edge,Extreme_bottom_edge_so_far));
	    result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-CONNECTION */
Object change_size_per_bounding_rectangle_for_connection(connection,
	    left_edge,top_edge,right_edge,bottom_edge,mode)
    Object connection, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    x_note_fn_call(119,126);
    return VALUES_1(Nil);
}

/* HEURISTIC-MAXIMUM-EDGE */
Object heuristic_maximum_edge(more_negative_edge,more_positive_edge,
	    default_width_or_height)
    Object more_negative_edge, more_positive_edge, default_width_or_height;
{
    SI_Long temp, temp_1;

    x_note_fn_call(119,127);
    temp = IFIX(more_positive_edge);
    temp_1 = IFIX(more_negative_edge) + 
	    (IFIX(FIXNUM_TIMES(default_width_or_height,
	    Greatest_magnification)) + (SI_Long)128L >>  -  - (SI_Long)8L);
    return VALUES_1(FIX(MIN(temp,temp_1)));
}

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-ACTION-BUTTON */
Object change_size_per_bounding_rectangle_for_action_button(action_button,
	    left_edge,top_edge,right_edge,bottom_edge,mode)
    Object action_button, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(119,128);
    right_edge = heuristic_maximum_edge(left_edge,right_edge,
	    ISVREF(ISVREF(action_button,(SI_Long)16L),(SI_Long)1L));
    bottom_edge = heuristic_maximum_edge(top_edge,bottom_edge,
	    ISVREF(ISVREF(action_button,(SI_Long)16L),(SI_Long)2L));
    gensymed_symbol = ACCESS_ONCE(ISVREF(action_button,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Button_label_class_description,
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
    if (temp) {
	temp_1 = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return fit_entity_around_text_box_or_bounding_rectangle(action_button,
	    temp_1,left_edge,top_edge,right_edge,bottom_edge);
}

DEFINE_VARIABLE_WITH_SYMBOL(Width_for_change_size_qm, Qwidth_for_change_size_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Height_for_change_size_qm, Qheight_for_change_size_qm);

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

static Object float_constant;      /* 0.0 */

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-ENTITY */
Object change_size_per_bounding_rectangle_for_entity(entity,left_edge,
	    top_edge,right_edge,bottom_edge,mode)
    Object entity, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object icon_description, width_of_icon, height_of_icon;
    Object height_of_icon_new_value, numerator_1, temp, temp_2;
    SI_Long denominator_1;
    double temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(119,129);
    icon_description = ISVREF(entity,(SI_Long)16L);
    width_of_icon = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
	    Qwidth);
    if (width_of_icon);
    else
	width_of_icon = ISVREF(icon_description,(SI_Long)1L);
    height_of_icon = getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
	    Qheight);
    if (height_of_icon);
    else
	height_of_icon = ISVREF(icon_description,(SI_Long)2L);
    if (rotated_by_90_p(getfq_function_no_default(ISVREF(entity,
	    (SI_Long)17L),Qreflection_and_rotation))) {
	height_of_icon_new_value = width_of_icon;
	width_of_icon = height_of_icon;
	height_of_icon = height_of_icon_new_value;
    }
    numerator_1 = Width_for_change_size_qm ? 
	    (INLINE_DOUBLE_FLOAT_VECTOR_P(Width_for_change_size_qm) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Width_for_change_size_qm)) == 
	    (SI_Long)1L ? 
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Width_for_change_size_qm,
	    (SI_Long)0L)) : Width_for_change_size_qm) : 
	    FIXNUM_MINUS(right_edge,left_edge);
    denominator_1 = MAX(IFIX(width_of_icon),(SI_Long)1L);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(numerator_1,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp_2 = convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 
		(double)denominator_1));
    }
    POP_LOCAL_ALLOCATION(0,0);
    numerator_1 = Height_for_change_size_qm ? 
	    (INLINE_DOUBLE_FLOAT_VECTOR_P(Height_for_change_size_qm) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Height_for_change_size_qm)) == 
	    (SI_Long)1L ? 
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Height_for_change_size_qm,
	    (SI_Long)0L)) : Height_for_change_size_qm) : 
	    FIXNUM_MINUS(bottom_edge,top_edge);
    denominator_1 = MAX(IFIX(height_of_icon),(SI_Long)1L);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(numerator_1,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 
		(double)denominator_1));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return magnify_icon(entity,temp_2,temp,left_edge,top_edge,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Force_change_to_minimum_size_p, Qforce_change_to_minimum_size_p);

static Object Qscale;              /* scale */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Qtext_x_magnification;  /* text-x-magnification */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qtext_y_magnification;  /* text-y-magnification */

static Object Qset_maximum;        /* set-maximum */

static Object Qtext_cell_desired_maximum_line_measure_for_text_box_qm;  /* text-cell-desired-maximum-line-measure-for-text-box? */

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-TEXT-BOX */
Object change_size_per_bounding_rectangle_for_text_box(text_box,left_edge,
	    top_edge,right_edge,bottom_edge,mode)
    Object text_box, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object width, height, numerator_1, gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, denominator_1;
    SI_Long delta_left_edge, delta_top_edge;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(119,130);
    update_images_of_block(text_box,T,Nil);
    width = FIXNUM_MINUS(right_edge,left_edge);
    height = FIXNUM_MINUS(bottom_edge,top_edge);
    if (EQ(mode,Qscale)) {
	numerator_1 = width;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	denominator_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    temp = 
		    convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(numerator_1) 
		    / (double)denominator_1));
	POP_LOCAL_ALLOCATION(0,0);
	change_text_box_property(text_box,Qx_magnification,temp);
	numerator_1 = height;
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	denominator_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    temp = 
		    convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(numerator_1) 
		    / (double)denominator_1));
	POP_LOCAL_ALLOCATION(0,0);
	change_text_box_property(text_box,Qy_magnification,temp);
	if (G2_has_v5_mode_windows_p) {
	    send_ws_representations_item_virtual_attribute_change(text_box,
		    get_property_value_function(3,
		    get_symbol_properties_function(Qtext_x_magnification),
		    Qvirtual_attribute,Nil),Nil);
	    send_ws_representations_item_virtual_attribute_change(text_box,
		    get_property_value_function(3,
		    get_symbol_properties_function(Qtext_y_magnification),
		    Qvirtual_attribute,Nil),Nil);
	}
    }
    else if (EQ(mode,Qset_maximum))
	change_slot_value(3,text_box,
		Qtext_cell_desired_maximum_line_measure_for_text_box_qm,
		FIXNUM_MINUS(right_edge,top_edge));
    else {
	temp_1 = FIXNUM_EQ(get_lookup_slot_value(text_box,
		Qminimum_width_of_text_box),width);
	if (temp_1);
	else if ( !TRUEP(Force_change_to_minimum_size_p)) {
	    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = FIXNUM_EQ(width,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(text_box,Qminimum_width_of_text_box);
	    set_lookup_slot_value_1(text_box,Qminimum_width_of_text_box,width);
	}
	temp_1 = FIXNUM_EQ(get_lookup_slot_value(text_box,
		Qminimum_height_of_text_box),height);
	if (temp_1);
	else if ( !TRUEP(Force_change_to_minimum_size_p)) {
	    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = FIXNUM_EQ(height,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(text_box,Qminimum_height_of_text_box);
	    set_lookup_slot_value_1(text_box,Qminimum_height_of_text_box,
		    height);
	}
    }
    gensymed_symbol_1 = IFIX(left_edge);
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    delta_left_edge = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(top_edge);
    gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    delta_top_edge = gensymed_symbol_1 - gensymed_symbol_2;
    shift_block(text_box,FIX(delta_left_edge),FIX(delta_top_edge));
    if (G2_has_v5_mode_windows_p &&  
	    !TRUEP(Ws_protocol_handle_moves_from_edge_change_p) && 
	    (delta_left_edge != (SI_Long)0L || delta_top_edge != (SI_Long)0L))
	send_ws_representations_item_moved(text_box,FIX(delta_left_edge),
		FIX(delta_top_edge));
    reformat_text_box_in_place(1,text_box);
    enlarge_workspace_for_block_rectangle_if_necessary(text_box,Nil);
    return update_images_of_block(text_box,Nil,Nil);
}

Object Default_trend_chart_width = UNBOUND;

Object Default_trend_chart_height = UNBOUND;

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-TREND-CHART */
Object change_size_per_bounding_rectangle_for_trend_chart(trend_chart,
	    left_edge,top_edge,right_edge,bottom_edge,mode)
    Object trend_chart, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    x_note_fn_call(119,131);
    right_edge = heuristic_maximum_edge(left_edge,right_edge,
	    Default_trend_chart_width);
    bottom_edge = heuristic_maximum_edge(top_edge,bottom_edge,
	    Default_trend_chart_height);
    return change_size_of_trend_chart(trend_chart,left_edge,top_edge,
	    right_edge,bottom_edge);
}

static Object Qgraph_format;       /* graph-format */

static Object Qminimum_graph_width;  /* minimum-graph-width */

static Object Qminimum_graph_height;  /* minimum-graph-height */

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-GRAPH */
Object change_size_per_bounding_rectangle_for_graph(graph,left_edge,
	    top_edge,right_edge,bottom_edge,mode)
    Object graph, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Object temp;

    x_note_fn_call(119,132);
    temp = right_edge;
    right_edge = heuristic_maximum_edge(left_edge,temp,
	    get_slot_init_form(2,Qgraph_format,Qminimum_graph_width));
    temp = bottom_edge;
    bottom_edge = heuristic_maximum_edge(top_edge,temp,
	    get_slot_init_form(2,Qgraph_format,Qminimum_graph_height));
    return change_size_of_graph(graph,left_edge,top_edge,right_edge,
	    bottom_edge);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart, Qchart);

Object Default_chart_width = UNBOUND;

Object Default_chart_height = UNBOUND;

/* CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-CHART */
Object change_size_per_bounding_rectangle_for_chart(chart,left_edge,
	    top_edge,right_edge,bottom_edge,mode)
    Object chart, left_edge, top_edge, right_edge, bottom_edge, mode;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(119,133);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      right_edge = heuristic_maximum_edge(left_edge,right_edge,
	      Default_chart_width);
      bottom_edge = heuristic_maximum_edge(left_edge,bottom_edge,
	      Default_chart_height);
      result = change_size_of_chart(Chart,left_edge,top_edge,right_edge,
	      bottom_edge);
    POP_SPECIAL();
    return result;
}

/* FIND-IMAGE-PLANE-SHOWING-WORKSPACE */
Object find_image_plane_showing_workspace(workspace)
    Object workspace;
{
    Object image_plane, ab_loop_list_;

    x_note_fn_call(119,134);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(Current_workstation_detail_pane,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(image_plane,(SI_Long)5L),workspace))
	return VALUES_1(image_plane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qclone_or_transfer_target;  /* clone-or-transfer-target */

/* FIX-UP-BOUNDING-STATE-IF-NECESSARY-AFTER-TRANSFER */
Object fix_up_bounding_state_if_necessary_after_transfer(bounding_context)
    Object bounding_context;
{
    Object transfer_return_information, bounding_state, temp, new_workspace_qm;
    Object new_image_plane_qm;

    x_note_fn_call(119,135);
    transfer_return_information = ISVREF(Current_workstation,(SI_Long)33L);
    bounding_state = ISVREF(bounding_context,(SI_Long)2L);
    temp = EQ(transfer_return_information,Kabort) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	new_workspace_qm = get_workspace_if_any(ISVREF(bounding_state,
		(SI_Long)4L));
	new_image_plane_qm = new_workspace_qm ? 
		find_image_plane_showing_workspace(new_workspace_qm) : Qnil;
	if (new_workspace_qm)
	    invoke_workspace_invalidation_handler_if_any(new_workspace_qm,
		    Qclone_or_transfer_target);
	temp = EQ(new_workspace_qm,ISVREF(bounding_state,(SI_Long)14L)) ? 
		T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (new_image_plane_qm) {
	    SVREF(bounding_state,FIX((SI_Long)12L)) = new_image_plane_qm;
	    return VALUES_1(SVREF(bounding_state,FIX((SI_Long)14L)) = 
		    new_workspace_qm);
	}
	else
	    return abort_current_workstation_context(Qbounding);
    }
}

/* FIT-BOUNDING-BOX-AROUND-BLOCK */
Object fit_bounding_box_around_block(bounding_box,block,text_box_format)
    Object bounding_box, block, text_box_format;
{
    Object gensymed_symbol, temp, temp_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(119,136);
    update_images_of_block(bounding_box,T,T);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)44L));
    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)45L));
    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)46L));
    temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(text_box_format,(SI_Long)47L));
    change_edges_of_block(bounding_box,temp,temp_1,temp_2,
	    FIX(gensymed_symbol_1 + gensymed_symbol_2));
    gensymed_symbol = ACCESS_ONCE(ISVREF(bounding_box,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    enlarge_workspace_for_block_rectangle_if_necessary(bounding_box,
	    gensymed_symbol);
    return update_images_of_block(bounding_box,Nil,T);
}

static Object Qdefault_action_button;  /* default-action-button */

/* ENTER-KEYS-IN-BOUNDING-STATE */
Object enter_keys_in_bounding_state(mouse_pointer)
    Object mouse_pointer;
{
    Object bounding_state, subblock, gensymed_symbol, ab_loop_list_;
    Object sub_class_bit_vector, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(119,137);
    bounding_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (bounding_state) {
	subblock = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(bounding_state,
		(SI_Long)3L),(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_loop_list_ = gensymed_symbol;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subblock = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qdefault_action_button,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    highlight_or_unhighlight_button(subblock,Nil);
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(subblock,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)23L),(SI_Long)1L);
	    gensymed_symbol_4 = subblock;
	    gensymed_symbol_5 = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol_5 = gensymed_symbol_5 ? 
		    ISVREF(gensymed_symbol_5,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_6 = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol_6 = gensymed_symbol_6 ? 
		    ISVREF(gensymed_symbol_6,(SI_Long)1L) : FIX((SI_Long)0L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6);
	    return VALUES_1(Nil);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtop_left;           /* top-left */

static Object Qbottom_left;        /* bottom-left */

static Object Qtop_right;          /* top-right */

/* MOUSE-DOWN-ON-IMAGE-PLANE-IN-BOUNDING-STATE */
Object mouse_down_on_image_plane_in_bounding_state(mouse_pointer)
    Object mouse_pointer;
{
    Object bounding_state, workspace, x_in_window, y_in_window;
    Object x_in_workspace_for_bounding_box, y_in_workspace_for_bounding_box;
    Object image_plane, mouse_pointer_1, bounding_box, put_back_and_exit_qm;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object x_in_workspace, image_plane_1, scale, value, y_in_workspace;
    Object edge_or_corner_qm, x_offset, y_offset, temp_1, sub_class_bit_vector;
    Object x_in_workspace_1, y_in_workspace_1, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, temp_2;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(119,138);
    bounding_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    x_in_workspace_for_bounding_box = 
	    x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace_for_bounding_box = 
	    y_in_workspace_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (bounding_state && workspace && x_in_window && y_in_window && 
	    x_in_workspace_for_bounding_box && 
	    y_in_workspace_for_bounding_box && image_plane && 
		mouse_pointer_1) {
	bounding_box = ISVREF(bounding_state,(SI_Long)4L);
	put_back_and_exit_qm = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (EQ(subblock,bounding_box)) {
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    x_in_workspace = gensymed_symbol;
	    image_plane_1 = ISVREF(bounding_state,(SI_Long)12L);
	    gensymed_symbol_1 = IFIX(ISVREF(image_plane_1,(SI_Long)13L));
	    scale = ISVREF(image_plane_1,(SI_Long)11L);
	    value = x_in_workspace;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)10L;
	    temp = FIXNUM_GT(x_in_window,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    y_in_workspace = gensymed_symbol;
	    image_plane_1 = ISVREF(bounding_state,(SI_Long)12L);
	    gensymed_symbol_1 = IFIX(ISVREF(image_plane_1,(SI_Long)14L));
	    scale = ISVREF(image_plane_1,(SI_Long)12L);
	    value = y_in_workspace;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)10L;
	    temp = FIXNUM_GT(y_in_window,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    x_in_workspace = gensymed_symbol;
	    image_plane_1 = ISVREF(bounding_state,(SI_Long)12L);
	    gensymed_symbol_1 = IFIX(ISVREF(image_plane_1,(SI_Long)13L));
	    scale = ISVREF(image_plane_1,(SI_Long)11L);
	    value = x_in_workspace;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)10L;
	    temp = FIXNUM_LT(x_in_window,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    y_in_workspace = gensymed_symbol;
	    image_plane_1 = ISVREF(bounding_state,(SI_Long)12L);
	    gensymed_symbol_1 = IFIX(ISVREF(image_plane_1,(SI_Long)14L));
	    scale = ISVREF(image_plane_1,(SI_Long)12L);
	    value = y_in_workspace;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)10L;
	    temp = FIXNUM_LT(y_in_window,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result = select_edge_or_corner_of_bounding_box(4,bounding_box,
		    x_in_window,y_in_window,ISVREF(bounding_state,
		    (SI_Long)12L));
	    MVS_3(result,edge_or_corner_qm,x_offset,y_offset);
	    if ( !TRUEP(edge_or_corner_qm)) {
		gensymed_symbol_1 = IFIX(x_in_workspace_for_bounding_box);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol_1 = IFIX(y_in_workspace_for_bounding_box);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		enter_move_dragging_context(5,bounding_box,temp_1,
			FIX(gensymed_symbol_1 - gensymed_symbol_2),
			image_plane,T);
	    }
	    else {
		start_tracking_mouse_in_current_workstation_context();
		push_back_mouse_motion_event();
		SVREF(bounding_state,FIX((SI_Long)7L)) = edge_or_corner_qm;
		SVREF(bounding_state,FIX((SI_Long)8L)) = x_offset;
		SVREF(bounding_state,FIX((SI_Long)9L)) = y_offset;
		if (EQ(edge_or_corner_qm,Qtop_left) || 
			EQ(edge_or_corner_qm,Qbottom_left)) {
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		}
		else {
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		}
		SVREF(bounding_state,FIX((SI_Long)10L)) = gensymed_symbol;
		SVREF(bounding_state,FIX((SI_Long)12L)) = image_plane;
		if (EQ(edge_or_corner_qm,Qtop_left) || 
			EQ(edge_or_corner_qm,Qtop_right)) {
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		}
		else {
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		}
		SVREF(bounding_state,FIX((SI_Long)11L)) = gensymed_symbol;
	    }
	    goto end_1;
	}
	else if (EQ(workspace,ISVREF(bounding_state,(SI_Long)3L))) {
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Button_class_description,(SI_Long)18L));
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
	    if (temp) {
		x_in_workspace_1 = Nil;
		y_in_workspace_1 = Nil;
		current_frame_transform_qm = Nil;
		current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
		current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
		current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
		current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			4);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  3);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			    2);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
				0);
			  scale = Current_image_x_scale;
			  value = FIXNUM_MINUS(x_in_window,
				  Current_x_origin_of_drawing);
			  if (IFIX(scale) == (SI_Long)4096L)
			      x_in_workspace_1 = value;
			  else if ( 
				  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)))
			      x_in_workspace_1 = 
				      inverse_scalef_function(scale,value);
			  else if (IFIX(value) >= (SI_Long)0L) {
			      temp_1 = FIX(((IFIX(value) << (SI_Long)12L) 
				      + (IFIX(scale) >>  -  - 
				      (SI_Long)1L)) / IFIX(scale));
			      x_in_workspace_1 = temp_1;
			  }
			  else {
			      temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
				      (SI_Long)12L) + (IFIX(scale) >>  -  
				      - (SI_Long)1L)) / IFIX(scale);
			      temp_1 = FIXNUM_NEGATE(FIX(temp_2));
			      x_in_workspace_1 = temp_1;
			  }
			  scale = Current_image_y_scale;
			  value = FIXNUM_MINUS(y_in_window,
				  Current_y_origin_of_drawing);
			  if (IFIX(scale) == (SI_Long)4096L)
			      y_in_workspace_1 = value;
			  else if ( 
				  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  value) && FIXNUM_LT(value,
				  Isqrt_of_most_positive_fixnum)))
			      y_in_workspace_1 = 
				      inverse_scalef_function(scale,value);
			  else if (IFIX(value) >= (SI_Long)0L) {
			      temp_1 = FIX(((IFIX(value) << (SI_Long)12L) 
				      + (IFIX(scale) >>  -  - 
				      (SI_Long)1L)) / IFIX(scale));
			      y_in_workspace_1 = temp_1;
			  }
			  else {
			      temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
				      (SI_Long)12L) + (IFIX(scale) >>  -  
				      - (SI_Long)1L)) / IFIX(scale);
			      temp_1 = FIXNUM_NEGATE(FIX(temp_2));
			      y_in_workspace_1 = temp_1;
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		temp = TRUEP(in_block_p(subblock,x_in_workspace_1,
			y_in_workspace_1));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		enter_button_down_context(subblock,image_plane);
		goto end_1;
	    }
	}
	goto next_loop;
      end_loop:
	if (EQ(workspace,ISVREF(bounding_state,(SI_Long)3L)))
	    enter_image_plane_dragging_context(4,image_plane,
		    FIXNUM_MINUS(x_in_window,ISVREF(image_plane,
		    (SI_Long)15L)),FIXNUM_MINUS(y_in_window,
		    ISVREF(image_plane,(SI_Long)16L)),T);
	else
	    put_back_and_exit_qm = T;
      end_1:;
	if (put_back_and_exit_qm)
	    return requeue_event_and_abort_workstation_context(mouse_pointer_1);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-UP-IN-BOUNDING-STATE */
Object mouse_up_in_bounding_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, bounding_state;

    x_note_fn_call(119,139);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    bounding_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && bounding_state) {
	mouse_motion_in_bounding_state(mouse_pointer_1);
	stop_tracking_mouse_in_current_workstation_context();
	return VALUES_1(SVREF(bounding_state,FIX((SI_Long)7L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object float_constant_1;    /* 1.0 */

static Object Qtext_box;           /* text-box */

static Object Qbottom_right;       /* bottom-right */

/* MOUSE-MOTION-IN-BOUNDING-STATE */
Object mouse_motion_in_bounding_state(mouse_pointer)
    Object mouse_pointer;
{
    Object bounding_state, x_in_window, y_in_window, bounding_box;
    Object text_box_format, left_border_width, top_border_width;
    Object right_border_width, bottom_border_width, edge_or_corner;
    Object focus_workspace, focus_image_plane_qm;
    Object x_in_workspace_for_bounding_box, y_in_workspace_for_bounding_box;
    Object temp, gensymed_symbol, vertical_edge_of_bounding_box;
    Object horizontal_edge_of_bounding_box, x0, y0_1, negative_slope_qm;
    Object gensymed_symbol_1, x1, y1_1, new_vertical_edge_of_bounding_box;
    Object new_horizontal_edge_of_bounding_box, new_edge, frame, symbol;
    Object sub_class_bit_vector, text_box_to_be_bounded_qm, text_box_format_qm;
    Object maximum_text_box_width_qm;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_7, gensymed_symbol_8;
    char temp_2;
    double gensymed_symbol_2, gensymed_symbol_3, absolute_slope, m, x2, temp_1;
    double y2;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(119,140);
    bounding_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (bounding_state && x_in_window && y_in_window) {
	bounding_box = ISVREF(bounding_state,(SI_Long)4L);
	text_box_format = ISVREF(bounding_box,(SI_Long)17L);
	left_border_width = ISVREF(text_box_format,(SI_Long)44L);
	top_border_width = ISVREF(text_box_format,(SI_Long)45L);
	right_border_width = ISVREF(text_box_format,(SI_Long)46L);
	bottom_border_width = ISVREF(text_box_format,(SI_Long)47L);
	edge_or_corner = ISVREF(bounding_state,(SI_Long)7L);
	focus_workspace = ISVREF(bounding_state,(SI_Long)14L);
	focus_image_plane_qm = image_plane_of_workspace(focus_workspace);
	x_in_workspace_for_bounding_box = focus_image_plane_qm ? 
		x_in_workspace_coordinates(x_in_window,
		focus_image_plane_qm) : Qnil;
	y_in_workspace_for_bounding_box = focus_image_plane_qm ? 
		y_in_workspace_coordinates(y_in_window,
		focus_image_plane_qm) : Qnil;
	temp =  !TRUEP(focus_image_plane_qm) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (ISVREF(bounding_state,(SI_Long)6L) && 
		memq_function(edge_or_corner,list_constant_14)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (EQ(edge_or_corner,Qtop_left) || EQ(edge_or_corner,
			    Qbottom_left)) {
			gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)0L) : 
				FIX((SI_Long)0L);
			vertical_edge_of_bounding_box = gensymed_symbol;
		    }
		    else {
			gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)2L) : 
				FIX((SI_Long)0L);
			vertical_edge_of_bounding_box = gensymed_symbol;
		    }
		    if (EQ(edge_or_corner,Qtop_left) || EQ(edge_or_corner,
			    Qtop_right)) {
			gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			horizontal_edge_of_bounding_box = gensymed_symbol;
		    }
		    else {
			gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)3L) : 
				FIX((SI_Long)0L);
			horizontal_edge_of_bounding_box = gensymed_symbol;
		    }
		    x0 = ISVREF(bounding_state,(SI_Long)10L);
		    y0_1 = ISVREF(bounding_state,(SI_Long)11L);
		    negative_slope_qm = memq_function(edge_or_corner,
			    list_constant_15);
		    gensymed_symbol = lfloat(ISVREF(bounding_state,
			    (SI_Long)6L),float_constant);
		    gensymed_symbol_1 = float_constant_1;
		    temp = DOUBLE_FLOAT_MAX(gensymed_symbol,gensymed_symbol_1);
		    gensymed_symbol_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    gensymed_symbol = lfloat(ISVREF(bounding_state,
			    (SI_Long)5L),float_constant);
		    gensymed_symbol_1 = float_constant_1;
		    temp = DOUBLE_FLOAT_MAX(gensymed_symbol,gensymed_symbol_1);
		    gensymed_symbol_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    absolute_slope = gensymed_symbol_2 / gensymed_symbol_3;
		    m = negative_slope_qm ?  - absolute_slope : absolute_slope;
		    x1 = FIXNUM_MINUS(x_in_workspace_for_bounding_box,x0);
		    y1_1 = FIXNUM_MINUS(y_in_workspace_for_bounding_box,y0_1);
		    x2 = ((double)IFIX(y1_1) + (double)IFIX(x1) / m) / (m 
			    + 1.0 / m);
		    temp = lfloat(DOUBLE_TO_DOUBLE_FLOAT(x2),float_constant);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    y2 = m * temp_1;
		    new_vertical_edge_of_bounding_box = FIXNUM_ADD(x0,
			    l_round(DOUBLE_TO_DOUBLE_FLOAT(x2),_));
		    new_horizontal_edge_of_bounding_box = FIXNUM_ADD(y0_1,
			    l_round(DOUBLE_TO_DOUBLE_FLOAT(y2),_));
		    if ( !FIXNUM_EQ(horizontal_edge_of_bounding_box,
			    new_horizontal_edge_of_bounding_box)) {
			if (EQ(edge_or_corner,Qtop_left) || 
				EQ(edge_or_corner,Qtop_right)) {
			    gensymed_symbol = ISVREF(bounding_box,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)3L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_4 = IFIX(gensymed_symbol);
			    gensymed_symbol_5 = IFIX(bottom_border_width);
			    gensymed_symbol_6 = IFIX(top_border_width);
			    if (FIXNUM_LT(new_horizontal_edge_of_bounding_box,
				    FIX(gensymed_symbol_4 - 
				    gensymed_symbol_5 - gensymed_symbol_6)))
				update_border_of_text_box(bounding_box,Nil,
					new_horizontal_edge_of_bounding_box,
					Nil,Nil);
			}
			else {
			    gensymed_symbol = ISVREF(bounding_box,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)1L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_4 = IFIX(gensymed_symbol);
			    gensymed_symbol_5 = IFIX(bottom_border_width);
			    gensymed_symbol_6 = IFIX(top_border_width);
			    if (FIXNUM_GT(new_horizontal_edge_of_bounding_box,
				    FIX(gensymed_symbol_4 + 
				    gensymed_symbol_5 + gensymed_symbol_6)))
				update_border_of_text_box(bounding_box,Nil,
					Nil,Nil,
					new_horizontal_edge_of_bounding_box);
			}
		    }
		    if ( !FIXNUM_EQ(vertical_edge_of_bounding_box,
			    new_vertical_edge_of_bounding_box)) {
			if (EQ(edge_or_corner,Qtop_left) || 
				EQ(edge_or_corner,Qbottom_left)) {
			    gensymed_symbol = ISVREF(bounding_box,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)2L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_4 = IFIX(gensymed_symbol);
			    gensymed_symbol_5 = IFIX(left_border_width);
			    gensymed_symbol_6 = IFIX(right_border_width);
			    if (FIXNUM_LT(new_vertical_edge_of_bounding_box,
				    FIX(gensymed_symbol_4 - 
				    gensymed_symbol_5 - gensymed_symbol_6)))
				result = update_border_of_text_box(bounding_box,
					new_vertical_edge_of_bounding_box,
					Nil,Nil,Nil);
			    else
				result = VALUES_1(Nil);
			}
			else {
			    gensymed_symbol = ISVREF(bounding_box,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)0L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_4 = IFIX(gensymed_symbol);
			    gensymed_symbol_5 = IFIX(left_border_width);
			    gensymed_symbol_6 = IFIX(right_border_width);
			    if (FIXNUM_GT(new_vertical_edge_of_bounding_box,
				    FIX(gensymed_symbol_4 + 
				    gensymed_symbol_5 + gensymed_symbol_6)))
				result = update_border_of_text_box(bounding_box,
					Nil,Nil,
					new_vertical_edge_of_bounding_box,Nil);
			    else
				result = VALUES_1(Nil);
			}
		    }
		    else
			result = VALUES_1(Nil);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    POP_LOCAL_ALLOCATION(1,1);
	    return result;
	}
	else {
	    new_edge = Nil;
	    if (ISVREF(bounding_state,(SI_Long)13L)) {
		frame = ISVREF(bounding_state,(SI_Long)13L);
		symbol = Qtext_box;
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_4 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_5 = (SI_Long)1L;
			gensymed_symbol_6 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_5 = gensymed_symbol_5 << 
				gensymed_symbol_6;
			gensymed_symbol_4 = gensymed_symbol_4 & 
				gensymed_symbol_5;
			temp_2 = (SI_Long)0L < gensymed_symbol_4;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    text_box_to_be_bounded_qm = temp_2 ? ISVREF(bounding_state,
		    (SI_Long)13L) : Nil;
	    text_box_format_qm = text_box_to_be_bounded_qm ? 
		    ISVREF(text_box_to_be_bounded_qm,(SI_Long)17L) : Nil;
	    maximum_text_box_width_qm = text_box_format_qm ? 
		    Maximum_text_box_width_or_height : Nil;
	    if (EQ(edge_or_corner,Qleft) || EQ(edge_or_corner,Qtop_left) 
		    || EQ(edge_or_corner,Qbottom_left)) {
		gensymed_symbol_4 = IFIX(x_in_workspace_for_bounding_box);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol);
		gensymed_symbol_6 = IFIX(left_border_width);
		gensymed_symbol_7 = IFIX(right_border_width);
		gensymed_symbol_8 = (SI_Long)1L;
		gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6 
			- gensymed_symbol_7 - gensymed_symbol_8;
		new_edge = FIX(MIN(gensymed_symbol_4,gensymed_symbol_5));
		if (text_box_to_be_bounded_qm) {
		    gensymed_symbol_4 = IFIX(new_edge);
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_5 = IFIX(gensymed_symbol);
		    gensymed_symbol_6 = IFIX(right_border_width);
		    gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6;
		    gensymed_symbol_6 = IFIX(maximum_text_box_width_qm);
		    gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6;
		    new_edge = FIX(MAX(gensymed_symbol_4,gensymed_symbol_5));
		}
		temp = new_edge;
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		if ( !FIXNUM_EQ(temp,gensymed_symbol))
		    update_border_of_text_box(bounding_box,new_edge,Nil,
			    Nil,Nil);
	    }
	    else if (EQ(edge_or_corner,Qright) || EQ(edge_or_corner,
		    Qtop_right) || EQ(edge_or_corner,Qbottom_right)) {
		gensymed_symbol_4 = IFIX(x_in_workspace_for_bounding_box);
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_5 = IFIX(gensymed_symbol);
		gensymed_symbol_6 = IFIX(left_border_width);
		gensymed_symbol_7 = IFIX(right_border_width);
		gensymed_symbol_8 = (SI_Long)1L;
		gensymed_symbol_5 = gensymed_symbol_5 + gensymed_symbol_6 
			+ gensymed_symbol_7 + gensymed_symbol_8;
		new_edge = FIX(MAX(gensymed_symbol_4,gensymed_symbol_5));
		if (text_box_to_be_bounded_qm) {
		    gensymed_symbol_4 = IFIX(new_edge);
		    gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_5 = IFIX(gensymed_symbol);
		    gensymed_symbol_6 = IFIX(left_border_width);
		    gensymed_symbol_5 = gensymed_symbol_5 + gensymed_symbol_6;
		    gensymed_symbol_6 = IFIX(maximum_text_box_width_qm);
		    gensymed_symbol_5 = gensymed_symbol_5 + gensymed_symbol_6;
		    new_edge = FIX(MIN(gensymed_symbol_4,gensymed_symbol_5));
		}
		temp = new_edge;
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		if ( !FIXNUM_EQ(temp,gensymed_symbol))
		    update_border_of_text_box(bounding_box,Nil,Nil,
			    new_edge,Nil);
	    }
	    if (EQ(edge_or_corner,Qtop) || EQ(edge_or_corner,Qtop_left) || 
		    EQ(edge_or_corner,Qtop_right)) {
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol);
		gensymed_symbol_5 = IFIX(top_border_width);
		gensymed_symbol_6 = IFIX(bottom_border_width);
		gensymed_symbol_7 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5 
			- gensymed_symbol_6 - gensymed_symbol_7;
		gensymed_symbol_5 = IFIX(y_in_workspace_for_bounding_box);
		new_edge = FIX(MIN(gensymed_symbol_4,gensymed_symbol_5));
		temp = new_edge;
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		if ( !FIXNUM_EQ(temp,gensymed_symbol))
		    return update_border_of_text_box(bounding_box,Nil,
			    new_edge,Nil,Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else if (EQ(edge_or_corner,Qbottom) || EQ(edge_or_corner,
		    Qbottom_left) || EQ(edge_or_corner,Qbottom_right)) {
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol);
		gensymed_symbol_5 = IFIX(top_border_width);
		gensymed_symbol_6 = IFIX(bottom_border_width);
		gensymed_symbol_7 = (SI_Long)1L;
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5 
			+ gensymed_symbol_6 + gensymed_symbol_7;
		gensymed_symbol_5 = IFIX(y_in_workspace_for_bounding_box);
		new_edge = FIX(MAX(gensymed_symbol_4,gensymed_symbol_5));
		temp = new_edge;
		gensymed_symbol = ISVREF(bounding_box,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		if ( !FIXNUM_EQ(temp,gensymed_symbol))
		    return update_border_of_text_box(bounding_box,Nil,Nil,
			    Nil,new_edge);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-DOWN-ON-CLOSE-BOX-WIDGET-IN-BOUNDING-STATE */
Object mouse_down_on_close_box_widget_in_bounding_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, bounding_state, x_in_window, y_in_window;
    Object image_plane, workspace;

    x_note_fn_call(119,141);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    bounding_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    if (mouse_pointer_1 && bounding_state && x_in_window && y_in_window && 
	    image_plane && workspace) {
	if (EQ(workspace,ISVREF(bounding_state,(SI_Long)3L)))
	    return enter_close_box_widget_pending_context(workspace,
		    image_plane);
	else
	    return requeue_event_and_abort_workstation_context(mouse_pointer_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Kxor;                /* :xor */

static Object Qtransparent;        /* transparent */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

/* SELECT-EDGE-OR-CORNER-OF-BOUNDING-BOX */
Object select_edge_or_corner_of_bounding_box varargs_1(int, n)
{
    Object bounding_box, x_in_window, y_in_window, image_plane;
    Object no_leeway_p, gensym_window, left_edge_of_draw_area;
    Object top_edge_of_draw_area, right_edge_of_draw_area;
    Object bottom_edge_of_draw_area, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, temp, current_window_1;
    Object drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object current_frame_transform_qm, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, border_width, scale;
    Object gensymed_symbol_1, value, edge_or_corner_qm, x_offset, y_offset;
    Object temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_2, unshifted_result;
    SI_Long outside_left_edge, outside_top_edge, outside_right_edge;
    SI_Long outside_bottom_edge, gensymed_symbol_3, value_1, inside_left_edge;
    SI_Long inside_top_edge, inside_right_edge, inside_bottom_edge, leeway;
    SI_Long temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(33);
    Object result;

    x_note_fn_call(119,142);
    INIT_ARGS_nonrelocating();
    bounding_box = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    no_leeway_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    32);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      31);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		30);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  29);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    28);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      27);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			26);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  25);
		    left_edge_of_draw_area = Left_edge_of_draw_area;
		    top_edge_of_draw_area = Top_edge_of_draw_area;
		    right_edge_of_draw_area = Right_edge_of_draw_area;
		    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			    24);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			      23);
			PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				22);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				  21);
			    temp = ISVREF(image_plane,(SI_Long)6L);
			    Left_edge_of_draw_area = FIXNUM_MAX(temp,
				    Left_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)7L);
			    Top_edge_of_draw_area = FIXNUM_MAX(temp,
				    Top_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)8L);
			    Right_edge_of_draw_area = FIXNUM_MIN(temp,
				    Right_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)9L);
			    Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				    Bottom_edge_of_draw_area);
			    if (FIXNUM_LT(Left_edge_of_draw_area,
				    Right_edge_of_draw_area) && 
				    FIXNUM_LT(Top_edge_of_draw_area,
				    Bottom_edge_of_draw_area)) {
				LOCK(On_window_without_drawing);
				if (PUSH_UNWIND_PROTECT(1)) {
				    current_window_1 = 
					    ISVREF(ISVREF(image_plane,
					    (SI_Long)2L),(SI_Long)2L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
					    20);
				      drawing_on_window = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
					      19);
					current_drawing_transfer_mode = 
						EQ(Current_drawing_transfer_mode,
						Kxor) ? 
						Current_drawing_transfer_mode 
						: ISVREF(Current_window,
						(SI_Long)30L);
					PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
						18);
					  type_of_current_window = 
						  ISVREF(Current_window,
						  (SI_Long)1L);
					  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
						  17);
					    current_native_window_qm = 
						    ISVREF(Current_window,
						    (SI_Long)17L);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
						    16);
					      current_color_map = 
						      ISVREF(Current_window,
						      (SI_Long)20L);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
						      15);
						temp = 
							ISVREF(Current_color_map,
							(SI_Long)5L);
						if (temp);
						else
						    temp = 
							    map_to_color_value_1(Qwhite);
						current_background_color_value 
							= temp;
						PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
							14);
						  temp = 
							  ISVREF(Current_color_map,
							  (SI_Long)4L);
						  if (temp);
						  else
						      temp = 
							      map_to_color_value_1(Qblack);
						  current_foreground_color_value 
							  = temp;
						  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
							  13);
						    current_frame_transform_qm 
							    = Nil;
						    current_image_x_scale 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)11L);
						    current_image_y_scale 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)12L);
						    current_x_origin_of_drawing 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)13L);
						    current_y_origin_of_drawing 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)14L);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
							    12);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
							      11);
							PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
								10);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
								  9);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
								    8);
							      LOCK(For_image_plane);
							      if (PUSH_UNWIND_PROTECT(0)) 
									  {
								  current_pane 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)2L);
								  current_image_plane 
									  = 
									  image_plane;
								  loose_left_edge_of_visible_workspace_area 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)23L);
								  loose_top_edge_of_visible_workspace_area 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)24L);
								  loose_right_edge_of_visible_workspace_area 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)25L);
								  loose_bottom_edge_of_visible_workspace_area 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)26L);
								  color_or_metacolor 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)5L) 
									  ?
									   
									  ISVREF(ISVREF(image_plane,
									  (SI_Long)5L),
									  (SI_Long)22L) 
									  :
									   Nil;
								  if (color_or_metacolor);
								  else
								      color_or_metacolor 
									      = 
									      Qblack;
								  if (EQ(color_or_metacolor,
									  Qtransparent) 
									  || 
									  EQ(color_or_metacolor,
									  Qbackground)) 
									      {
								      background_color_or_metacolor 
									      = 
									      ISVREF(image_plane,
									      (SI_Long)5L) 
									      ?
									       
									      ISVREF(ISVREF(image_plane,
									      (SI_Long)5L),
									      (SI_Long)21L) 
									      :
									       
									      Nil;
								      if (background_color_or_metacolor);
								      else
									  background_color_or_metacolor 
										  = 
										  Qwhite;
								      if (EQ(background_color_or_metacolor,
									      Qforeground) 
									      || 
									      EQ(background_color_or_metacolor,
									      Qworkspace_foreground)) 
										  {
									  temp 
										  = 
										  ISVREF(Current_color_map,
										  (SI_Long)4L);
									  if (temp);
									  else
									      temp 
										      = 
										      map_to_color_value_1(Qblack);
									  current_foreground_color_value 
										  = 
										  temp;
								      }
								      else if (EQ(background_color_or_metacolor,
									      Qtransparent) 
									      || 
									      EQ(background_color_or_metacolor,
									      Qbackground)) 
										  {
									  temp 
										  = 
										  ISVREF(Current_color_map,
										  (SI_Long)5L);
									  if (temp);
									  else
									      temp 
										      = 
										      map_to_color_value_1(Qwhite);
									  current_foreground_color_value 
										  = 
										  temp;
								      }
								      else
									  current_foreground_color_value 
										  = 
										  EQ(background_color_or_metacolor,
										  ISVREF(Current_color_map,
										  (SI_Long)6L)) 
										  ?
										   
										  ISVREF(Current_color_map,
										  (SI_Long)7L) 
										  :
										   
										  map_to_color_value_1(background_color_or_metacolor);
								  }
								  else if (EQ(color_or_metacolor,
									  Qforeground) 
									  || 
									  EQ(color_or_metacolor,
									  Qworkspace_foreground)) 
									      {
								      temp 
									      = 
									      ISVREF(Current_color_map,
									      (SI_Long)4L);
								      if (temp);
								      else
									  temp 
										  = 
										  map_to_color_value_1(Qblack);
								      current_foreground_color_value 
									      = 
									      temp;
								  }
								  else
								      current_foreground_color_value 
									      = 
									      EQ(color_or_metacolor,
									      ISVREF(Current_color_map,
									      (SI_Long)6L)) 
									      ?
									       
									      ISVREF(Current_color_map,
									      (SI_Long)7L) 
									      :
									       
									      map_to_color_value_1(color_or_metacolor);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
									  7);
								    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
									    6);
								      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
									      5);
									PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
										4);
									  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
										  3);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
										    2);
									      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
										      1);
										color_or_metacolor 
											= 
											ISVREF(image_plane,
											(SI_Long)5L) 
											?
											 
											ISVREF(ISVREF(image_plane,
											(SI_Long)5L),
											(SI_Long)21L) 
											:
											 
											Nil;
										if (color_or_metacolor);
										else
										    color_or_metacolor 
											    = 
											    Qwhite;
										if (EQ(color_or_metacolor,
											Qtransparent) 
											|| 
											EQ(color_or_metacolor,
											Qbackground)) 
											    {
										    temp 
											    = 
											    ISVREF(Current_color_map,
											    (SI_Long)5L);
										    if (temp);
										    else
											temp 
												= 
												map_to_color_value_1(Qwhite);
										    current_background_color_value 
											    = 
											    temp;
										}
										else if (EQ(color_or_metacolor,
											Qforeground) 
											|| 
											EQ(color_or_metacolor,
											Qworkspace_foreground)) 
											    {
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)5L) 
											    ?
											     
											    ISVREF(ISVREF(image_plane,
											    (SI_Long)5L),
											    (SI_Long)22L) 
											    :
											     
											    Nil;
										    if (temp);
										    else
											temp 
												= 
												Qblack;
										    color_or_metacolor 
											    = 
											    temp;
										    if (EQ(color_or_metacolor,
											    Qtransparent) 
											    || 
											    EQ(color_or_metacolor,
											    Qbackground)) 
												{
											background_color_or_metacolor 
												= 
												ISVREF(image_plane,
												(SI_Long)5L) 
												?
												 
												ISVREF(ISVREF(image_plane,
												(SI_Long)5L),
												(SI_Long)21L) 
												:
												 
												Nil;
											if (background_color_or_metacolor);
											else
											    background_color_or_metacolor 
												    = 
												    Qwhite;
											if (EQ(background_color_or_metacolor,
												Qforeground) 
												|| 
												EQ(background_color_or_metacolor,
												Qworkspace_foreground)) 
												    {
											    temp 
												    = 
												    ISVREF(Current_color_map,
												    (SI_Long)4L);
											    if (temp);
											    else
												temp 
													= 
													map_to_color_value_1(Qblack);
											    current_background_color_value 
												    = 
												    temp;
											}
											else if (EQ(background_color_or_metacolor,
												Qtransparent) 
												|| 
												EQ(background_color_or_metacolor,
												Qbackground)) 
												    {
											    temp 
												    = 
												    ISVREF(Current_color_map,
												    (SI_Long)5L);
											    if (temp);
											    else
												temp 
													= 
													map_to_color_value_1(Qwhite);
											    current_background_color_value 
												    = 
												    temp;
											}
											else
											    current_background_color_value 
												    = 
												    EQ(background_color_or_metacolor,
												    ISVREF(Current_color_map,
												    (SI_Long)6L)) 
												    ?
												     
												    ISVREF(Current_color_map,
												    (SI_Long)7L) 
												    :
												     
												    map_to_color_value_1(background_color_or_metacolor);
										    }
										    else if (EQ(color_or_metacolor,
											    Qforeground) 
											    || 
											    EQ(color_or_metacolor,
											    Qworkspace_foreground)) 
												{
											temp 
												= 
												ISVREF(Current_color_map,
												(SI_Long)4L);
											if (temp);
											else
											    temp 
												    = 
												    map_to_color_value_1(Qblack);
											current_background_color_value 
												= 
												temp;
										    }
										    else
											current_background_color_value 
												= 
												EQ(color_or_metacolor,
												ISVREF(Current_color_map,
												(SI_Long)6L)) 
												?
												 
												ISVREF(Current_color_map,
												(SI_Long)7L) 
												:
												 
												map_to_color_value_1(color_or_metacolor);
										}
										else
										    current_background_color_value 
											    = 
											    EQ(color_or_metacolor,
											    ISVREF(Current_color_map,
											    (SI_Long)6L)) 
											    ?
											     
											    ISVREF(Current_color_map,
											    (SI_Long)7L) 
											    :
											     
											    map_to_color_value_1(color_or_metacolor);
										PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
											0);
										  border_width 
											  = 
											  ISVREF(ISVREF(bounding_box,
											  (SI_Long)17L),
											  (SI_Long)44L);
										  gensymed_symbol 
											  = 
											  IFIX(Current_x_origin_of_drawing);
										  scale 
											  = 
											  Current_image_x_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)0L) 
											  :
											   
											  FIX((SI_Long)0L);
										  value 
											  = 
											  gensymed_symbol_1;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      IFIX(value);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  value) 
											  && 
											  FIXNUM_LT(value,
											  Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(FIXNUM_TIMES(scale,
											      value)) 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      value));
										  outside_left_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_y_origin_of_drawing);
										  scale 
											  = 
											  Current_image_y_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)1L) 
											  :
											   
											  FIX((SI_Long)0L);
										  value 
											  = 
											  gensymed_symbol_1;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      IFIX(value);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  value) 
											  && 
											  FIXNUM_LT(value,
											  Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(FIXNUM_TIMES(scale,
											      value)) 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      value));
										  outside_top_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_x_origin_of_drawing);
										  scale 
											  = 
											  Current_image_x_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)2L) 
											  :
											   
											  FIX((SI_Long)0L);
										  value 
											  = 
											  gensymed_symbol_1;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      IFIX(value);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  value) 
											  && 
											  FIXNUM_LT(value,
											  Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(FIXNUM_TIMES(scale,
											      value)) 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      value));
										  outside_right_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_y_origin_of_drawing);
										  scale 
											  = 
											  Current_image_y_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)3L) 
											  :
											   
											  FIX((SI_Long)0L);
										  value 
											  = 
											  gensymed_symbol_1;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      IFIX(value);
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  value) 
											  && 
											  FIXNUM_LT(value,
											  Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(FIXNUM_TIMES(scale,
											      value)) 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      value));
										  outside_bottom_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_x_origin_of_drawing);
										  scale 
											  = 
											  Current_image_x_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)0L) 
											  :
											   
											  FIX((SI_Long)0L);
										  gensymed_symbol_2 
											  = 
											  IFIX(gensymed_symbol_1);
										  gensymed_symbol_3 
											  = 
											  IFIX(border_width);
										  value_1 
											  = 
											  gensymed_symbol_2 
											  + 
											  gensymed_symbol_3;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      value_1;
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  value_1 
											  && 
											  value_1 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(scale) 
											      * 
											      value_1 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      FIX(value_1)));
										  inside_left_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_y_origin_of_drawing);
										  scale 
											  = 
											  Current_image_y_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)1L) 
											  :
											   
											  FIX((SI_Long)0L);
										  gensymed_symbol_2 
											  = 
											  IFIX(gensymed_symbol_1);
										  gensymed_symbol_3 
											  = 
											  IFIX(border_width);
										  value_1 
											  = 
											  gensymed_symbol_2 
											  + 
											  gensymed_symbol_3;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      value_1;
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  value_1 
											  && 
											  value_1 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(scale) 
											      * 
											      value_1 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      FIX(value_1)));
										  inside_top_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_x_origin_of_drawing);
										  scale 
											  = 
											  Current_image_x_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)2L) 
											  :
											   
											  FIX((SI_Long)0L);
										  gensymed_symbol_2 
											  = 
											  IFIX(gensymed_symbol_1);
										  gensymed_symbol_3 
											  = 
											  IFIX(border_width);
										  value_1 
											  = 
											  gensymed_symbol_2 
											  - 
											  gensymed_symbol_3;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      value_1;
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  value_1 
											  && 
											  value_1 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(scale) 
											      * 
											      value_1 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      FIX(value_1)));
										  inside_right_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  gensymed_symbol 
											  = 
											  IFIX(Current_y_origin_of_drawing);
										  scale 
											  = 
											  Current_image_y_scale;
										  gensymed_symbol_1 
											  = 
											  ISVREF(bounding_box,
											  (SI_Long)14L);
										  gensymed_symbol_1 
											  = 
											  gensymed_symbol_1 
											  ?
											   
											  ISVREF(gensymed_symbol_1,
											  (SI_Long)3L) 
											  :
											   
											  FIX((SI_Long)0L);
										  gensymed_symbol_2 
											  = 
											  IFIX(gensymed_symbol_1);
										  gensymed_symbol_3 
											  = 
											  IFIX(border_width);
										  value_1 
											  = 
											  gensymed_symbol_2 
											  - 
											  gensymed_symbol_3;
										  if (IFIX(scale) 
											  == 
											  (SI_Long)4096L)
										      gensymed_symbol_2 
											      = 
											      value_1;
										  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											  scale) 
											  && 
											  FIXNUM_LT(scale,
											  Isqrt_of_most_positive_fixnum) 
											  && 
											  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
											  < 
											  value_1 
											  && 
											  value_1 
											  < 
											  IFIX(Isqrt_of_most_positive_fixnum)) 
											      {
										      unshifted_result 
											      = 
											      IFIX(scale) 
											      * 
											      value_1 
											      + 
											      (SI_Long)2048L;
										      gensymed_symbol_2 
											      = 
											      unshifted_result 
											      >> 
											       
											      - 
											       
											      - 
											      (SI_Long)12L;
										  }
										  else
										      gensymed_symbol_2 
											      = 
											      IFIX(scalef_function(scale,
											      FIX(value_1)));
										  inside_bottom_edge 
											  = 
											  gensymed_symbol 
											  + 
											  gensymed_symbol_2;
										  leeway 
											  = 
											  no_leeway_p 
											  ?
											   
											  (SI_Long)0L 
											  :
											   
											  (SI_Long)10L;
										  if (IFIX(x_in_window) 
											  < 
											  inside_left_edge 
											  + 
											  leeway) 
											      {
										      if (IFIX(y_in_window) 
											      < 
											      inside_top_edge 
											      + 
											      leeway)
											  result = VALUES_3(Qtop_left,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_left_edge),
												  FIX(IFIX(y_in_window) 
												  - 
												  outside_top_edge));
										      else if (IFIX(y_in_window) 
											      > 
											      inside_bottom_edge 
											      - 
											      leeway)
											  result = VALUES_3(Qbottom_left,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_left_edge),
												  FIX(IFIX(y_in_window) 
												  - 
												  outside_bottom_edge));
										      else
											  result = VALUES_3(Qleft,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_left_edge),
												  FIX((SI_Long)0L));
										  }
										  else if (IFIX(x_in_window) 
											  > 
											  inside_right_edge 
											  - 
											  leeway) 
											      {
										      if (IFIX(y_in_window) 
											      < 
											      inside_top_edge 
											      + 
											      leeway)
											  result = VALUES_3(Qtop_right,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_right_edge),
												  FIX(IFIX(y_in_window) 
												  - 
												  outside_top_edge));
										      else if (IFIX(y_in_window) 
											      > 
											      inside_bottom_edge 
											      - 
											      leeway)
											  result = VALUES_3(Qbottom_right,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_right_edge),
												  FIX(IFIX(y_in_window) 
												  - 
												  outside_bottom_edge));
										      else
											  result = VALUES_3(Qright,
												  FIX(IFIX(x_in_window) 
												  - 
												  outside_right_edge),
												  FIX((SI_Long)0L));
										  }
										  else if (IFIX(y_in_window) 
											  < 
											  inside_top_edge 
											  + 
											  leeway)
										      result = VALUES_3(Qtop,
											      FIX((SI_Long)0L),
											      FIX(IFIX(y_in_window) 
											      - 
											      outside_top_edge));
										  else if (IFIX(y_in_window) 
											  > 
											  inside_bottom_edge 
											  - 
											  leeway)
										      result = VALUES_3(Qbottom,
											      FIX((SI_Long)0L),
											      FIX(IFIX(y_in_window) 
											      - 
											      outside_bottom_edge));
										  else
										      result = VALUES_1(Nil);
										  MVS_3(result,
											  edge_or_corner_qm,
											  x_offset,
											  y_offset);
										  if (edge_or_corner_qm) 
											      {
										      if (IFIX(Current_image_x_scale) 
											      == 
											      (SI_Long)4096L)
											  temp 
												  = 
												  x_offset;
										      else if ( 
											      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											      x_offset) 
											      && 
											      FIXNUM_LT(x_offset,
											      Isqrt_of_most_positive_fixnum)))
											  temp 
												  = 
												  inverse_scalef_function(Current_image_x_scale,
												  x_offset);
										      else if (IFIX(x_offset) 
											      >= 
											      (SI_Long)0L)
											  temp 
												  = 
												  FIX(((IFIX(x_offset) 
												  << 
												  (SI_Long)12L) 
												  + 
												  (IFIX(Current_image_x_scale) 
												  >> 
												   
												  - 
												   
												  - 
												  (SI_Long)1L)) 
												  / 
												  IFIX(Current_image_x_scale));
										      else {
											  temp_1 
												  = 
												  ((IFIX(FIXNUM_NEGATE(x_offset)) 
												  << 
												  (SI_Long)12L) 
												  + 
												  (IFIX(Current_image_x_scale) 
												  >> 
												   
												  - 
												   
												  - 
												  (SI_Long)1L)) 
												  / 
												  IFIX(Current_image_x_scale);
											  temp 
												  = 
												  FIXNUM_NEGATE(FIX(temp_1));
										      }
										      if (IFIX(Current_image_y_scale) 
											      == 
											      (SI_Long)4096L)
											  temp_2 
												  = 
												  y_offset;
										      else if ( 
											      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
											      y_offset) 
											      && 
											      FIXNUM_LT(y_offset,
											      Isqrt_of_most_positive_fixnum)))
											  temp_2 
												  = 
												  inverse_scalef_function(Current_image_y_scale,
												  y_offset);
										      else if (IFIX(y_offset) 
											      >= 
											      (SI_Long)0L)
											  temp_2 
												  = 
												  FIX(((IFIX(y_offset) 
												  << 
												  (SI_Long)12L) 
												  + 
												  (IFIX(Current_image_y_scale) 
												  >> 
												   
												  - 
												   
												  - 
												  (SI_Long)1L)) 
												  / 
												  IFIX(Current_image_y_scale));
										      else {
											  temp_1 
												  = 
												  ((IFIX(FIXNUM_NEGATE(y_offset)) 
												  << 
												  (SI_Long)12L) 
												  + 
												  (IFIX(Current_image_y_scale) 
												  >> 
												   
												  - 
												   
												  - 
												  (SI_Long)1L)) 
												  / 
												  IFIX(Current_image_y_scale);
											  temp_2 
												  = 
												  FIXNUM_NEGATE(FIX(temp_1));
										      }
										      SAVE_VALUES(VALUES_3(edge_or_corner_qm,
											      temp,
											      temp_2));
										  }
										  else
										      SAVE_VALUES(VALUES_1(Nil));
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
							      }
							      POP_UNWIND_PROTECT(0);
							      UNLOCK(For_image_plane);
							      CONTINUE_UNWINDING(0);
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
				POP_UNWIND_PROTECT(1);
				UNLOCK(On_window_without_drawing);
				CONTINUE_UNWINDING(1);
				result = RESTORE_VALUES();
			    }
			    else
				result = VALUES_1(Nil);
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

static Object array_constant_17;   /* # */

static Object Qdelete_blocks_for_operate_on_area_upon_confirmation;  /* delete-blocks-for-operate-on-area-upon-confirmation */

static Object Qreclaim_dragging_list_function;  /* reclaim-dragging-list-function */

/* DELETE-BLOCKS-FOR-OPERATE-ON-AREA-AFTER-CONFIRMATION */
Object delete_blocks_for_operate_on_area_after_confirmation(blocks)
    Object blocks;
{
    Object temp;

    x_note_fn_call(119,143);
    temp = copy_constant_wide_string_given_length(array_constant_17,
	    FIX((SI_Long)32L));
    return enter_dialog(7,temp,Nil,Nil,
	    Qdelete_blocks_for_operate_on_area_upon_confirmation,
	    slot_value_cons_1(blocks,Nil),Qreclaim_dragging_list_function,
	    slot_value_cons_1(blocks,Nil));
}

/* DELETE-BLOCKS-FOR-OPERATE-ON-AREA-UPON-CONFIRMATION */
Object delete_blocks_for_operate_on_area_upon_confirmation(blocks)
    Object blocks;
{
    Object junction_blocks_not_to_be_deleted, serial_number, gensymed_symbol;
    Object workspace_qm, block, ab_loop_list_;
    Declare_special(1);

    x_note_fn_call(119,144);
    junction_blocks_not_to_be_deleted = blocks;
    PUSH_SPECIAL_WITH_SYMBOL(Junction_blocks_not_to_be_deleted,Qjunction_blocks_not_to_be_deleted,junction_blocks_not_to_be_deleted,
	    0);
      serial_number = copy_frame_serial_number(Current_frame_serial_number);
      if (CAR(blocks)) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(CAR(blocks),(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  workspace_qm = gensymed_symbol;
      }
      else
	  workspace_qm = Nil;
      block = Nil;
      ab_loop_list_ = blocks;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      delete_frame_after_checking_serial_number(block,serial_number);
      goto next_loop;
    end_loop:
      if (workspace_qm)
	  invoke_workspace_invalidation_handler_if_any(workspace_qm,Qdelete);
      reclaim_frame_serial_number(serial_number);
    POP_SPECIAL();
    return reclaim_dragging_list_function(blocks);
}

/* PREPARE-BLOCKS-FOR-OPERATION-ON-AREA */
Object prepare_blocks_for_operation_on_area varargs_1(int, n)
{
    Object workspace, left_edge, top_edge, right_edge, bottom_edge;
    Object transfer_case_qm, clone_case_qm, result_blocks;
    Declare_varargs_nonrelocating;

    x_note_fn_call(119,145);
    INIT_ARGS_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    left_edge = REQUIRED_ARG_nonrelocating();
    top_edge = REQUIRED_ARG_nonrelocating();
    right_edge = REQUIRED_ARG_nonrelocating();
    bottom_edge = REQUIRED_ARG_nonrelocating();
    transfer_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    clone_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Nil)) {
	result_blocks = list_blocks_within_area_of_workspace(workspace,
		left_edge,top_edge,right_edge,bottom_edge,transfer_case_qm,
		clone_case_qm);
	if (transfer_case_qm) {
	    delete_connections_of_blocks_within_area(result_blocks,
		    left_edge,top_edge,right_edge,bottom_edge);
	    reclaim_dragging_list_function(result_blocks);
	    return list_blocks_within_area_of_workspace(workspace,
		    left_edge,top_edge,right_edge,bottom_edge,
		    transfer_case_qm,clone_case_qm);
	}
	else
	    return VALUES_1(result_blocks);
    }
    else
	return VALUES_1(Nil);
}

static Object Qreclaim_dragging_cons_function;  /* reclaim-dragging-cons-function */

/* LIST-BLOCKS-WITHIN-AREA-OF-WORKSPACE */
Object list_blocks_within_area_of_workspace(workspace,left_edge,top_edge,
	    right_edge,bottom_edge,transfer_case_qm,clone_case_qm)
    Object workspace, left_edge, top_edge, right_edge, bottom_edge;
    Object transfer_case_qm, clone_case_qm;
{
    Object block_list_qm, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, block, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, sub_class_bit_vector, ab_loop_list_;
    Object blocks_to_delete_qm, x2, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, temp_1;
    Object ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(119,146);
    block_list_qm = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    if (FIXNUM_GE(gensymed_symbol,left_edge)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp = FIXNUM_GE(gensymed_symbol,top_edge);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp = FIXNUM_LE(gensymed_symbol,right_edge);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp = FIXNUM_LE(gensymed_symbol,bottom_edge);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp =  !(transfer_case_qm || clone_case_qm);
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_name_box_class_description,
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
	    temp =  !temp ?  !TRUEP(in_order_p(block)) : TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp = TRUEP(clone_case_qm);
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	    temp =  !temp;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	ab_loopvar__2 = dragging_cons_function(block,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    block_list_qm = ab_loopvar_;
    goto end_1;
    block_list_qm = Qnil;
  end_1:;
    block = Nil;
    ab_loop_list_ = block_list_qm;
    blocks_to_delete_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(block) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
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
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	      goto end_2;
	  goto next_loop_3;
	end_loop_3:
	end_2:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_4;
	  connection = ab_connection_;
	  temp_1 = get_block_at_other_end_of_connection(connection,block);
	  if ( !TRUEP(memq_function(temp_1,block_list_qm)))
	      blocks_to_delete_qm = gensym_cons_1(block,blocks_to_delete_qm);
	  goto next_loop_2;
	end_loop_4:;
	POP_SPECIAL();
    }
    goto next_loop_1;
  end_loop_1:
    if (blocks_to_delete_qm) {
	block = Nil;
	ab_loop_list_ = blocks_to_delete_qm;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	block_list_qm = 
		delete_item_from_list_and_reclaim_cons_cells(block_list_qm,
		block,Qreclaim_dragging_cons_function,Nil);
	goto next_loop_5;
      end_loop_5:;
	reclaim_gensym_list_1(blocks_to_delete_qm);
    }
    return VALUES_1(block_list_qm);
}

/* DELETE-CONNECTIONS-OF-BLOCKS-WITHIN-AREA */
Object delete_connections_of_blocks_within_area(blocks,left_edge,top_edge,
	    right_edge,bottom_edge)
    Object blocks, left_edge, top_edge, right_edge, bottom_edge;
{
    Object junction_blocks_not_to_be_deleted, frame_serial_number, block;
    Object ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(119,147);
    junction_blocks_not_to_be_deleted = blocks;
    PUSH_SPECIAL_WITH_SYMBOL(Junction_blocks_not_to_be_deleted,Qjunction_blocks_not_to_be_deleted,junction_blocks_not_to_be_deleted,
	    0);
      frame_serial_number = 
	      copy_frame_serial_number(Current_frame_serial_number);
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
	      temp = FIXNUM_EQ(xa,ya) ? 
		      FIXNUM_LT(M_CDR(frame_serial_number),
		      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
      }
      if ( !temp)
	  delete_connections_of_block_not_within_area_of_workspace(block,
		  left_edge,top_edge,right_edge,bottom_edge);
      goto next_loop;
    end_loop:
      reclaim_frame_serial_number(frame_serial_number);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* DELETE-CONNECTIONS-OF-BLOCK-NOT-WITHIN-AREA-OF-WORKSPACE */
Object delete_connections_of_block_not_within_area_of_workspace(block,
	    left_edge,top_edge,right_edge,bottom_edge)
    Object block, left_edge, top_edge, right_edge, bottom_edge;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, ab_less_than_branch_qm_, connections_to_check;
    Object ab_loop_list_, block_at_other_end;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(119,148);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
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
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
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
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
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
      connection = ab_connection_;
      ab_loopvar__2 = gensym_cons_1(connection,Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      goto next_loop;
    end_loop_2:
      connections_to_check = ab_loopvar_;
      goto end_2;
      connections_to_check = Qnil;
    end_2:;
    POP_SPECIAL();
    connection = Nil;
    ab_loop_list_ = connections_to_check;
    block_at_other_end = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    block_at_other_end = get_block_at_other_end_of_connection(connection,
	    block);
    gensymed_symbol = ISVREF(block_at_other_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    if (FIXNUM_GE(gensymed_symbol,left_edge)) {
	gensymed_symbol = ISVREF(block_at_other_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp_1 = FIXNUM_GE(gensymed_symbol,top_edge);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	gensymed_symbol = ISVREF(block_at_other_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp_1 = FIXNUM_LE(gensymed_symbol,right_edge);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	gensymed_symbol = ISVREF(block_at_other_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp_1 = FIXNUM_LE(gensymed_symbol,bottom_edge);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	delete_connection_to_stub(connection);
    goto next_loop_3;
  end_loop_3:
    reclaim_gensym_list_1(connections_to_check);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_procedure_qm, Qworkspace_invalidation_handling_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_procedure_fsn_qm, Qworkspace_invalidation_handling_procedure_fsn_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_workspace_queue, Qworkspace_invalidation_handling_workspace_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_fsn_queue, Qworkspace_invalidation_handling_fsn_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_window_queue, Qworkspace_invalidation_handling_window_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_invalidation_handling_event_type_queue, Qworkspace_invalidation_handling_event_type_queue);

/* G2-REGISTER-WORKSPACE-INVALIDATION-HANDLING-PROCEDURE */
Object g2_register_workspace_invalidation_handling_procedure(procedure)
    Object procedure;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object frame_serial_number_setf_arg;
    Object workspace_invalidation_handling_procedure_fsn_qm_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(119,149);
    if (SIMPLE_VECTOR_P(procedure) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure)) > (SI_Long)2L &&  
	    !EQ(ISVREF(procedure,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(procedure,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Workspace_invalidation_handling_procedure_qm = procedure;
	frame_serial_number_setf_arg = ISVREF(procedure,(SI_Long)3L);
	workspace_invalidation_handling_procedure_fsn_qm_new_value = 
		(FIXNUMP(Workspace_invalidation_handling_procedure_fsn_qm) 
		||  
		!TRUEP(Workspace_invalidation_handling_procedure_fsn_qm)) 
		&& (FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(Workspace_invalidation_handling_procedure_fsn_qm,
		frame_serial_number_setf_arg);
	Workspace_invalidation_handling_procedure_fsn_qm = 
		workspace_invalidation_handling_procedure_fsn_qm_new_value;
	return make_evaluation_truth_value_function(Truth);
    }
    else {
	Workspace_invalidation_handling_procedure_qm = Nil;
	return make_evaluation_truth_value_function(Falsity);
    }
}

/* G2-GET-INVALID-WORKSPACE-TO-HANDLE */
Object g2_get_invalid_workspace_to_handle()
{
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2, frame;
    Object fsn, gensymed_symbol, xa, ya, temp_2;
    char temp_1;

    x_note_fn_call(119,150);
    slot_value_pop_store = Nil;
    cons_1 = Workspace_invalidation_handling_workspace_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Workspace_invalidation_handling_workspace_queue = next_cons;
    frame = slot_value_pop_store;
    slot_value_pop_store = Nil;
    cons_1 = Workspace_invalidation_handling_fsn_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Workspace_invalidation_handling_fsn_queue = next_cons;
    fsn = slot_value_pop_store;
    if (frame) {
	gensymed_symbol = ISVREF(frame,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else if (FIXNUMP(fsn))
	    temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) {
	reclaim_frame_serial_number(fsn);
	temp_2 = frame;
    }
    else {
	reclaim_frame_serial_number(fsn);
	temp_2 = make_evaluation_truth_value_function(Falsity);
    }
    slot_value_pop_store = Nil;
    cons_1 = Workspace_invalidation_handling_event_type_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Workspace_invalidation_handling_event_type_queue = next_cons;
    return VALUES_2(temp_2,slot_value_pop_store);
}

/* G2-MORE-INVALID-WORKSPACES-TO-BE-HANDLED */
Object g2_more_invalid_workspaces_to_be_handled()
{
    x_note_fn_call(119,151);
    if (Workspace_invalidation_handling_workspace_queue)
	return make_evaluation_truth_value_function(Truth);
    else
	return make_evaluation_truth_value_function(Falsity);
}

/* INVOKE-WORKSPACE-INVALIDATION-HANDLER-IF-ANY */
Object invoke_workspace_invalidation_handler_if_any(workspace_qm,event_type)
    Object workspace_qm, event_type;
{
    Object gensymed_symbol, xa, ya, temp_1;
    char temp;

    x_note_fn_call(119,152);
    if (Workspace_invalidation_handling_procedure_qm) {
	gensymed_symbol = 
		ISVREF(Workspace_invalidation_handling_procedure_qm,
		(SI_Long)3L);
	temp = 
		SIMPLE_VECTOR_P(Workspace_invalidation_handling_procedure_qm) 
		? EQ(ISVREF(Workspace_invalidation_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(Workspace_invalidation_handling_procedure_fsn_qm))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(Workspace_invalidation_handling_procedure_fsn_qm,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(Workspace_invalidation_handling_procedure_fsn_qm);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(Workspace_invalidation_handling_procedure_fsn_qm),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (workspace_qm) {
	    Workspace_invalidation_handling_workspace_queue = 
		    nconc2(Workspace_invalidation_handling_workspace_queue,
		    slot_value_cons_1(workspace_qm,Nil));
	    temp_1 = Workspace_invalidation_handling_fsn_queue;
	    Workspace_invalidation_handling_fsn_queue = nconc2(temp_1,
		    slot_value_cons_1(copy_frame_serial_number(ISVREF(workspace_qm,
		    (SI_Long)3L)),Nil));
	    Workspace_invalidation_handling_event_type_queue = 
		    nconc2(Workspace_invalidation_handling_event_type_queue,
		    slot_value_cons_1(event_type,Nil));
	    return start_procedure_invocation_in_place(Workspace_invalidation_handling_procedure_qm,
		    Nil,Nil,Nil,FIX((SI_Long)0L),FIX((SI_Long)0L),Nil,Nil,
		    Nil,Nil,Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_dialog_title_qm, Qsimple_dialog_title_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_dialog_fill_text_p, Qsimple_dialog_fill_text_p);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_dialog_plist_qm, Qsimple_dialog_plist_qm);

static Object Qlistbox;            /* listbox */

/* POST-SIMPLE-DIALOG */
Object post_simple_dialog(gensym_window,handle,message_1,ok_string,
	    cancel_string,additional_string,default_button_qm)
    Object gensym_window, handle, message_1, ok_string, cancel_string;
    Object additional_string, default_button_qm;
{
    Object title, icp_output_port_qm, current_icp_port, current_icp_socket;
    Object temp, disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(119,153);
    if (native_simple_dialogs_p(gensym_window)) {
	title = Simple_dialog_title_qm;
	if (title);
	else
	    title = array_constant_15;
	icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
	if (icp_output_port_qm && 
		icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
	    current_icp_port = icp_output_port_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		      10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			    Qtelewindows) ? T : Nil;
		disable_resumability = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_2 = 0.0;
				    if (Profiling_enabled_qm) {
					gensymed_symbol = T;
					gensymed_symbol_1 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_2 = 
						g2ext_unix_time_as_float();
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,gensymed_symbol_2);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					if ( !TRUEP(Simple_dialog_plist_qm))
					    temp = 
						    send_icp_simple_dialog(gensym_window,
						    handle,title,message_1,
						    ok_string,
						    cancel_string,
						    additional_string,
						    default_button_qm,
						    FIX((SI_Long)0L));
					else if (FIXNUM_LT(Icp_window_protocol_supports_simple_dialog_ex,
						ISVREF(gensym_window,
						(SI_Long)11L)))
					    temp = 
						    send_icp_simple_dialog_ex(gensym_window,
						    Qlistbox,handle,title,
						    message_1,
						    Simple_dialog_plist_qm);
					else
					    temp = Nil;
					end_icp_message_group();
				    }
				    else
					temp = Nil;
				    if (Profiling_enabled_qm) {
					gensymed_symbol_3 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_4 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_5 = 
						gensymed_symbol_3 - 
						gensymed_symbol_4;
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_5 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol ? 
						gensymed_symbol_1 + 
						gensymed_symbol_5 + 
						(gensymed_symbol_4 - 
						gensymed_symbol_2) : 
						gensymed_symbol_3;
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
				    }
				    result = VALUES_1(temp);
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
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

void facilities_INIT()
{
    Object gensymed_symbol, temp, temp_1, temp_2;
    Object reclaim_structure_for_meter_or_dial_spot_1, type_description;
    Object reclaim_structure_for_dial_spot_1;
    Object reclaim_structure_for_meter_spot_1;
    Object reclaim_structure_for_bounding_box_spot_1;
    Object reclaim_structure_for_bounding_state_1;
    Object valid_workstation_context_p_for_bounding_state_1;
    Object clean_up_workstation_context_for_bounding_state_1;
    Object AB_package, Qg2_more_invalid_workspaces_to_be_handled;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_get_invalid_workspace_to_handle;
    Object Qg2_register_workspace_invalidation_handling_procedure;
    Object Qreclaim_slot_value_list_function, Qfacilities;
    Object Qreclaim_slot_value_fsn_queue, Qreclaim_frame_serial_number;
    Object list_constant_16, Qmouse_down_on_close_box_widget_in_bounding_state;
    Object Qnew_style_event_handler, Qmouse_motion_in_bounding_state;
    Object Qmouse_up_in_bounding_state;
    Object Qmouse_down_on_image_plane_in_bounding_state;
    Object Qenter_keys_in_bounding_state, Qclasses_which_define;
    Object Qchange_size_per_bounding_rectangle;
    Object Qchange_size_per_bounding_rectangle_for_chart, Qgraph;
    Object Qchange_size_per_bounding_rectangle_for_graph;
    Object Qchange_size_per_bounding_rectangle_for_trend_chart;
    Object Qchange_size_per_bounding_rectangle_for_text_box, Qentity;
    Object Qchange_size_per_bounding_rectangle_for_entity, Qaction_button;
    Object Qchange_size_per_bounding_rectangle_for_action_button, Qconnection;
    Object Qchange_size_per_bounding_rectangle_for_connection;
    Object Qchange_size_per_bounding_rectangle_for_kb_workspace;
    Object Qchange_size_per_bounding_rectangle_for_block;
    Object Qgeneric_method_lambda_list, list_constant_61, Qmode, Qbottom_edge;
    Object Qright_edge, Qtop_edge, Qleft_edge, Qmove_area_to_bottom;
    Object Qmove_area_to_t_b_center, Qmove_area_to_top, Qmove_area_to_right;
    Object Qmove_area_to_l_r_center, Qmove_area_to_left, Qdelete_area;
    Object Qclone_area, Qtransfer_area, Qmove_area, Qsizing_no_minimum;
    Object Qsizing_update, Qsizing_restore, Qsizing_quit, Qsizing_ok;
    Object list_constant_60, list_constant_56, list_constant_59;
    Object list_constant_58, list_constant_55, string_constant_73, Qno_minimum;
    Object list_constant_57, list_constant_54, string_constant_72, Qupdate_now;
    Object string_constant_71, Qrestore_to_normal_size, list_constant_53;
    Object list_constant_52, list_constant_51, string_constant_70, Qok;
    Object list_constant_50, string_constant_69, Qcancel, string_constant_68;
    Object Qsizing_dialog_message_string, list_constant_49, list_constant_48;
    Object list_constant_47, list_constant_46, list_constant_45;
    Object list_constant_44, string_constant_67, Qquit, string_constant_66;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object Qformat_description, string_constant_56, Qdialog_message_format;
    Object Qbounding_state, Qclean_up_workstation_context;
    Object Qvalid_workstation_context_p, Qinternal, string_constant_55;
    Object Qrequeue_event_and_abort_workstation_context;
    Object Qstart_dragging_title_bar_handler, Qsearch_for_mouse_drag;
    Object Qtop_level, Qselection_style_of_workstation_context_type;
    Object Qtop_level_is_selection_style, Qreclaim_structure;
    Object Qoutstanding_bounding_state_count;
    Object Qbounding_state_structure_memory_usage, Qutilities2;
    Object string_constant_54, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_53, string_constant_52;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qgenerate_spot;
    Object Qgenerate_spot_for_bounding_box, Qtype_of_frame_represented;
    Object Qabstract_type, Qimage_plane_spot, Qenclosing_spot_type;
    Object Qinnermost_spot_p, Qbounding_box_spot;
    Object Qoutstanding_bounding_box_spot_count;
    Object Qbounding_box_spot_structure_memory_usage, string_constant_51;
    Object string_constant_50, string_constant_49, Qbounding_box_format;
    Object string_constant_48, list_constant_32, string_constant_47;
    Object string_constant_25, string_constant_46, Qcolor_menu_table_format;
    Object string_constant_45, Qright_aligned_color_menu_item_format;
    Object Qcenter_aligned_color_menu_item_format, string_constant_44;
    Object Qleft_aligned_color_menu_item_format, Qslot_value_writer;
    Object Qwrite_number_of_menu_columns_spec_from_slot;
    Object Qnumber_of_menu_columns_spec, string_constant_43, Qslot_putter;
    Object Qput_colors_on_2nd_level_color_menu;
    Object Qput_colors_on_1st_level_color_menu;
    Object Qwrite_color_set_spec_from_slot, Qcolor_set_spec;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_color_set_spec_for_slot, Qcolor;
    Object Qlist_of_colors, string_constant_42;
    Object Qwrite_color_menu_ordering_from_slot, Qcolor_menu_ordering;
    Object string_constant_41, Qabsent_slot_putter;
    Object Qput_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent;
    Object Qdo_not_dismiss_color_menu_after_choosing_qm, Ksystem_frame;
    Object string_constant_40, string_constant_39, list_constant_34;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, Qmeter, Qmeter_spot;
    Object Qoutstanding_meter_spot_count, Qmeter_spot_structure_memory_usage;
    Object string_constant_34, string_constant_33, Qdial, Qdial_spot;
    Object Qoutstanding_dial_spot_count, Qdial_spot_structure_memory_usage;
    Object string_constant_32, string_constant_31, Qmeter_or_dial_spot;
    Object Qoutstanding_meter_or_dial_spot_count;
    Object Qmeter_or_dial_spot_structure_memory_usage, string_constant_30;
    Object string_constant_29, Qmenu_string, array_constant_52;
    Object Qclass_choice_action, Qact_on_choice_of_a_trend_chart;
    Object Qact_on_choice_of_a_text_box, Qact_on_choice_of_a_freeform_table;
    Object Qfreeform_table, Qact_on_choice_of_a_chart;
    Object Qact_on_choice_of_a_graph, Qact_on_choice_of_a_button, Qbutton;
    Object Qact_on_choice_of_a_meter, Qact_on_choice_of_a_dial;
    Object Qact_on_choice_of_a_readout_table, Qreadout_table;
    Object Qact_on_choice_of_a_message, Qmessage, Qact_on_choice_of_a_entity;
    Object list_constant_33, Qexecute_command, Qcommand, string_constant_28;
    Object string_constant_27, string_constant_26, array_constant_51;
    Object Qup_down_reflection, array_constant_50, Qleft_right_reflection;
    Object Qtype_of_syntactic_anomaly, Qnumeric, Q180, array_constant_49;
    Object Qchange_to_no, array_constant_48, Qchange_to_yes, Qyes_or_no;
    Object Qmany_to_many, Qone_to_one, Qrotate_sl_reflect, Qrotate_reflect;
    Object array_constant_47, array_constant_46, Qdrop_to_bottom;
    Object array_constant_45, Qlift_to_top, array_constant_44;
    Object Qchoose_a_module_to_delete, Qget_workspace, list_constant_31;
    Object Qwrite_attribute_file, array_constant_43, array_constant_42;
    Object list_constant_30, array_constant_41, array_constant_40;
    Object array_constant_39, array_constant_38, array_constant_37;
    Object array_constant_36, array_constant_35, array_constant_34;
    Object array_constant_33, array_constant_32, array_constant_31;
    Object array_constant_29, array_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object array_constant_28, Qcheckbox, Qsave_all_to_one_file;
    Object array_constant_27, Qsave_only_changed_modules, array_constant_26;
    Object Qincluding_all_required_modules, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, array_constant_25;
    Object Qautomatically_resolving_conflicts, array_constant_24;
    Object Qupdate_before_loading, array_constant_23;
    Object Qmerge_kb_and_install_system_tables, array_constant_22;
    Object array_constant_21, Qwarmbooting_afterwards_with_catch_up;
    Object array_constant_20, Qwarmbooting_afterwards, array_constant_19;
    Object Qnot_starting_afterwards, array_constant_18, Qstarting_afterwards;
    Object Qg2_abort_callback_userdefine;

    x_note_fn_call(119,154);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    Qstore_hand_created_module_information_if_appropriate = 
	    STATIC_SYMBOL("STORE-HAND-CREATED-MODULE-INFORMATION-IF-APPROPRIATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qstore_hand_created_module_information_if_appropriate,
	    STATIC_FUNCTION(store_hand_created_module_information_if_appropriate,
	    NIL,FALSE,1,1));
    Qdelete_hand_created_module_information_if_appropriate = 
	    STATIC_SYMBOL("DELETE-HAND-CREATED-MODULE-INFORMATION-IF-APPROPRIATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_hand_created_module_information_if_appropriate,
	    STATIC_FUNCTION(delete_hand_created_module_information_if_appropriate,
	    NIL,FALSE,1,1));
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    Qdelete_module_information_if_unspecified_module = 
	    STATIC_SYMBOL("DELETE-MODULE-INFORMATION-IF-UNSPECIFIED-MODULE",
	    AB_package);
    Use_new_load_kb_qm = T;
    Qload_kb = STATIC_SYMBOL("LOAD-KB",AB_package);
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qsave_module = STATIC_SYMBOL("SAVE-MODULE",AB_package);
    Qload_attribute_file = STATIC_SYMBOL("LOAD-ATTRIBUTE-FILE",AB_package);
    Qwrite_g2_stats = STATIC_SYMBOL("WRITE-G2-STATS",AB_package);
    list_constant = STATIC_LIST((SI_Long)6L,Qload_kb,Qmerge_kb,Qsave_kb,
	    Qsave_module,Qload_attribute_file,Qwrite_g2_stats);
    Qdelete_frame_after_checking_serial_number_with_list = 
	    STATIC_SYMBOL("DELETE-FRAME-AFTER-CHECKING-SERIAL-NUMBER-WITH-LIST",
	    AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    string_constant = 
	    STATIC_STRING("You cannot do file commands other than Save KB or Write G2 Stats while running.");
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qconnect_to_foreign_image = STATIC_SYMBOL("CONNECT-TO-FOREIGN-IMAGE",
	    AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)57344L);
    Qforeign_image = STATIC_SYMBOL("FOREIGN-IMAGE",AB_package);
    Qdisconnect_from_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-FOREIGN-IMAGE",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    Qstatistics = STATIC_SYMBOL("STATISTICS",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Since this KB is not consistently modularized, you may ~\n           only save the KB in a single file!");
    string_constant_2 = 
	    string_append2(STATIC_STRING("WARNING: since this KB is not consistently ~\n           \t   modularized, you may only save the KB in a single file!  ~\n                   See logbook messages for further info"),
	    STATIC_STRING("rmation."));
    string_constant_3 = STATIC_STRING("{Comment: ~a}~%~%Save current KB as");
    array_constant_6 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    string_constant_4 = STATIC_STRING("Save module ~A as");
    Qsave_in_clear_text_by_default = 
	    STATIC_SYMBOL("SAVE-IN-CLEAR-TEXT-BY-DEFAULT",AB_package);
    Qxml = STATIC_SYMBOL("XML",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qsource_code_control_update_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-UPDATE-FILE",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    Qsource_control = STATIC_SYMBOL("SOURCE-CONTROL",AB_package);
    Qsource_code_control_edit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-EDIT-FILE",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    Qsource_code_control_unedit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-UNEDIT-FILE",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    Qsource_code_control_commit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-COMMIT-FILE",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)57344L);
    Qsource_code_control_revert_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-REVERT-FILE",AB_package);
    array_constant_12 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)57344L);
    Qg2_abort_callback_userdefine = 
	    STATIC_SYMBOL("G2-ABORT-CALLBACK-USERDEFINE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_abort_callback_userdefine,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_abort_callback_userdefine,
	    STATIC_FUNCTION(g2_abort_callback_userdefine,NIL,FALSE,1,1));
    Qstarting_afterwards = STATIC_SYMBOL("STARTING-AFTERWARDS",AB_package);
    Qcheckbox = STATIC_SYMBOL("CHECKBOX",AB_package);
    array_constant_18 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)57344L);
    list_constant_17 = STATIC_LIST((SI_Long)3L,Qstarting_afterwards,
	    Qcheckbox,array_constant_18);
    Qnot_starting_afterwards = STATIC_SYMBOL("NOT-STARTING-AFTERWARDS",
	    AB_package);
    array_constant_19 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)57344L);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qnot_starting_afterwards,
	    Qcheckbox,array_constant_19);
    Qwarmbooting_afterwards = STATIC_SYMBOL("WARMBOOTING-AFTERWARDS",
	    AB_package);
    array_constant_20 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)57344L);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qwarmbooting_afterwards,
	    Qcheckbox,array_constant_20);
    Qwarmbooting_afterwards_with_catch_up = 
	    STATIC_SYMBOL("WARMBOOTING-AFTERWARDS-WITH-CATCH-UP",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)20L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)29L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)30L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)32L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)34L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)38L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)47L,(SI_Long)57344L);
    list_constant_20 = STATIC_LIST((SI_Long)3L,
	    Qwarmbooting_afterwards_with_catch_up,Qcheckbox,array_constant_21);
    array_constant_22 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)57344L);
    list_constant_21 = STATIC_LIST((SI_Long)4L,Qmerge_kb,Qcheckbox,
	    array_constant_22,Qmerge_kb);
    Qmerge_kb_and_install_system_tables = 
	    STATIC_SYMBOL("MERGE-KB-AND-INSTALL-SYSTEM-TABLES",AB_package);
    array_constant_23 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)34L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)38L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)41L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)42L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)54L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)55L,(SI_Long)57344L);
    list_constant_22 = STATIC_LIST((SI_Long)3L,
	    Qmerge_kb_and_install_system_tables,Qcheckbox,array_constant_23);
    Qupdate_before_loading = STATIC_SYMBOL("UPDATE-BEFORE-LOADING",AB_package);
    array_constant_24 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)57344L);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qupdate_before_loading,
	    Qcheckbox,array_constant_24);
    Qautomatically_resolving_conflicts = 
	    STATIC_SYMBOL("AUTOMATICALLY-RESOLVING-CONFLICTS",AB_package);
    array_constant_25 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)39L,(SI_Long)57344L);
    list_constant_24 = STATIC_LIST((SI_Long)4L,
	    Qautomatically_resolving_conflicts,Qcheckbox,array_constant_25,Qt);
    list_constant_25 = STATIC_LIST((SI_Long)8L,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24);
    Native_load_kb_file_dialog_buttons = list_constant_25;
    Qincluding_all_required_modules = 
	    STATIC_SYMBOL("INCLUDING-ALL-REQUIRED-MODULES",AB_package);
    array_constant_26 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)26L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)39L,(SI_Long)57344L);
    list_constant_26 = STATIC_LIST((SI_Long)3L,
	    Qincluding_all_required_modules,Qcheckbox,array_constant_26);
    Qsave_only_changed_modules = STATIC_SYMBOL("SAVE-ONLY-CHANGED-MODULES",
	    AB_package);
    array_constant_27 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)57344L);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qsave_only_changed_modules,
	    Qcheckbox,array_constant_27);
    Qsave_all_to_one_file = STATIC_SYMBOL("SAVE-ALL-TO-ONE-FILE",AB_package);
    array_constant_28 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)24L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)31L,(SI_Long)57344L);
    Qspecial_string = STATIC_SYMBOL("SPECIAL-STRING",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)5L,Qsave_all_to_one_file,
	    Qcheckbox,array_constant_28,Qnil,Qspecial_string);
    list_constant_29 = STATIC_LIST((SI_Long)3L,list_constant_26,
	    list_constant_27,list_constant_28);
    Native_save_module_file_dialog_buttons = list_constant_29;
    array_constant_29 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)57344L);
    list_constant_30 = STATIC_CONS(array_constant_30,Qnil);
    list_constant_1 = STATIC_CONS(array_constant_29,list_constant_30);
    array_constant_31 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)21L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)31L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)57344L);
    list_constant_2 = STATIC_LIST((SI_Long)2L,array_constant_31,
	    array_constant_32);
    array_constant_33 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)11L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)12L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)16L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)18L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)20L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)21L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)23L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)25L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)31L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)15L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    list_constant_3 = STATIC_LIST((SI_Long)3L,array_constant_33,
	    array_constant_34,array_constant_35);
    array_constant_36 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)10L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)11L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)12L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)16L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)23L,(SI_Long)57344L);
    array_constant_37 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57344L);
    list_constant_4 = STATIC_LIST((SI_Long)2L,array_constant_36,
	    array_constant_37);
    array_constant_38 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)10L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)16L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)17L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)18L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)19L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)21L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)23L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)24L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)25L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)27L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)31L,(SI_Long)57344L);
    array_constant_39 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    list_constant_5 = STATIC_LIST((SI_Long)3L,array_constant_38,
	    array_constant_39,array_constant_40);
    array_constant_41 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)14L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)20L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)21L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)23L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)26L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)31L,(SI_Long)57344L);
    list_constant_6 = STATIC_CONS(array_constant_41,list_constant_30);
    array_constant_42 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)11L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)12L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)13L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)23L,(SI_Long)57344L);
    array_constant_43 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)57344L);
    list_constant_7 = STATIC_LIST((SI_Long)2L,array_constant_42,
	    array_constant_43);
    array_constant_13 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Qmodule_search_path = STATIC_SYMBOL("MODULE-SEARCH-PATH",AB_package);
    Qstring_equalw = STATIC_SYMBOL("STRING-EQUALW",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qplaces = STATIC_SYMBOL("PLACES",AB_package);
    Qdrives = STATIC_SYMBOL("DRIVES",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)4L,Qload_kb,Qsave_kb,Qmerge_kb,
	    Qsave_module);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    Qcombobox = STATIC_SYMBOL("COMBOBOX",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_attribute_file = STATIC_SYMBOL("WRITE-ATTRIBUTE-FILE",AB_package);
    list_constant_31 = STATIC_CONS(Qwrite_g2_stats,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)4L,Qsave_kb,Qsave_module,
	    Qwrite_attribute_file,list_constant_31);
    array_constant_15 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    Qclass_format = STATIC_SYMBOL("CLASS-FORMAT",AB_package);
    string_constant_5 = STATIC_STRING("~a");
    Qdefault_text_cell_format = STATIC_SYMBOL("DEFAULT-TEXT-CELL-FORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_6 = STATIC_STRING("~a~a");
    Knetwork_type = STATIC_SYMBOL("NETWORK-TYPE",Pkeyword);
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    array_constant_16 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    string_constant_7 = STATIC_STRING(",");
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qdefault_table_format = STATIC_SYMBOL("DEFAULT-TABLE-FORMAT",AB_package);
    Qstretch_new_image_planes_for_caption_p = 
	    STATIC_SYMBOL("STRETCH-NEW-IMAGE-PLANES-FOR-CAPTION-P",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qget_workspace = STATIC_SYMBOL("GET-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace,STATIC_FUNCTION(get_workspace,NIL,
	    FALSE,1,1));
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qchoose_a_module_to_delete = STATIC_SYMBOL("CHOOSE-A-MODULE-TO-DELETE",
	    AB_package);
    array_constant_44 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)9L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)16L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)19L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)31L,(SI_Long)57344L);
    Qmenu_string = STATIC_SYMBOL("MENU-STRING",AB_package);
    mutate_global_property(Qchoose_a_module_to_delete,array_constant_44,
	    Qmenu_string);
    Qlift_to_top = STATIC_SYMBOL("LIFT-TO-TOP",AB_package);
    array_constant_45 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlift_to_top,array_constant_45,Qmenu_string);
    Qdrop_to_bottom = STATIC_SYMBOL("DROP-TO-BOTTOM",AB_package);
    array_constant_46 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qdrop_to_bottom,array_constant_46,Qmenu_string);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    array_constant_47 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qkb_workspace,array_constant_47,Qmenu_string);
    string_constant_8 = STATIC_STRING("Delete this ~(~a~)\?");
    string_constant_9 = 
	    STATIC_STRING("Delete this ~(~a~), with its one subworkspace\?");
    string_constant_10 = 
	    STATIC_STRING("Delete this ~(~a~), with its ~D subworkspaces\?");
    Qdelete_frame_after_checking_serial_number = 
	    STATIC_SYMBOL("DELETE-FRAME-AFTER-CHECKING-SERIAL-NUMBER",
	    AB_package);
    Qole_ghost = STATIC_SYMBOL("OLE-GHOST",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qmessage_definition = STATIC_SYMBOL("MESSAGE-DEFINITION",AB_package);
    string_constant_11 = 
	    STATIC_STRING("This action would cause the deletion of stable item(s).  ");
    Qg2gl_process = STATIC_SYMBOL("G2GL-PROCESS",AB_package);
    string_constant_12 = 
	    STATIC_STRING("This action would cause the deletion of ~d process instance~a.  ");
    string_constant_13 = STATIC_STRING("");
    string_constant_14 = STATIC_STRING("s");
    string_constant_15 = STATIC_STRING("Delete this class");
    string_constant_16 = 
	    STATIC_STRING(", its instances, and its associated subworkspace(s)");
    string_constant_17 = STATIC_STRING(" and its instances");
    string_constant_18 = STATIC_STRING(" and its subworkspace(s)");
    string_constant_19 = STATIC_STRING("\?");
    string_constant_20 = STATIC_STRING("Delete this class-definition");
    string_constant_21 = STATIC_STRING("Delete this ~(~a~)");
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qconnection_definition = STATIC_SYMBOL("CONNECTION-DEFINITION",AB_package);
    Qrotate_reflect = STATIC_SYMBOL("ROTATE-REFLECT",AB_package);
    Qrotate_sl_reflect = STATIC_SYMBOL("ROTATE/REFLECT",AB_package);
    mutate_global_property(Qrotate_reflect,Qrotate_sl_reflect,Qmenu_string);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qrelation_is_symmetric = STATIC_SYMBOL("RELATION-IS-SYMMETRIC",AB_package);
    Qone_to_one = STATIC_SYMBOL("ONE-TO-ONE",AB_package);
    Qmany_to_many = STATIC_SYMBOL("MANY-TO-MANY",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qone_to_one,Qmany_to_many);
    Qyes_or_no = STATIC_SYMBOL("YES-OR-NO",AB_package);
    temp = adjoin(2,Qyes_or_no,Grammar_categories_getting_yes_no_feature);
    Grammar_categories_getting_yes_no_feature = temp;
    Qchange_to_yes = STATIC_SYMBOL("CHANGE-TO-YES",AB_package);
    array_constant_48 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)10L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)14L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qchange_to_yes,array_constant_48,Qmenu_string);
    Qchange_to_no = STATIC_SYMBOL("CHANGE-TO-NO",AB_package);
    array_constant_49 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)10L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)13L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qchange_to_no,array_constant_49,Qmenu_string);
    Q180 = STATIC_SYMBOL("180",AB_package);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    Qtype_of_syntactic_anomaly = STATIC_SYMBOL("TYPE-OF-SYNTACTIC-ANOMALY",
	    AB_package);
    mutate_global_property(Q180,Qnumeric,Qtype_of_syntactic_anomaly);
    Qleft_right_reflection = STATIC_SYMBOL("LEFT-RIGHT-REFLECTION",AB_package);
    array_constant_50 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qleft_right_reflection,array_constant_50,
	    Qmenu_string);
    Qup_down_reflection = STATIC_SYMBOL("UP-DOWN-REFLECTION",AB_package);
    array_constant_51 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qup_down_reflection,array_constant_51,Qmenu_string);
    Qfull_editor = STATIC_SYMBOL("FULL-EDITOR",AB_package);
    Qdo_not_clear_text_for_edit_in_place = 
	    STATIC_SYMBOL("DO-NOT-CLEAR-TEXT-FOR-EDIT-IN-PLACE",AB_package);
    Qoption_buttons_for_edit_in_place = 
	    STATIC_SYMBOL("OPTION-BUTTONS-FOR-EDIT-IN-PLACE",AB_package);
    Qmenus_for_edit_in_place = STATIC_SYMBOL("MENUS-FOR-EDIT-IN-PLACE",
	    AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qkb_workspace_initial_width = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH",AB_package);
    Qkb_workspace_initial_height = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_32 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qcommand,list_constant_32);
    string_constant_25 = STATIC_STRING("0");
    string_constant_26 = 
	    STATIC_STRING("1m4z8r83xy83xy83=ny83=ny0830qy001n1l8l1l83Ey1m83Dy53CyExport, writable000004z8r83ry83ry83=ny83=ny00001o1l8l1n8p83=ny83Gy1l8o1l83");
    string_constant_27 = STATIC_STRING("-3y00000");
    string_constant_28 = 
	    STATIC_STRING("1o8q1m83=ny1l83-ly1m83xy830qy1n83ry01n8p83=ny83Gy");
    temp_1 = regenerate_optimized_constant(string_constant_25);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_26,
	    string_constant_27));
    add_class_to_environment(9,Qcommand,list_constant_32,Nil,temp_1,Nil,
	    temp_2,list_constant_32,
	    regenerate_optimized_constant(string_constant_28),Nil);
    Qexecute_command = STATIC_SYMBOL("EXECUTE-COMMAND",AB_package);
    list_constant_33 = STATIC_CONS(Qcommand,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qexecute_command,list_constant_33,
	    Qgeneric_method_lambda_list);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qexecute_command_on_return = STATIC_SYMBOL("EXECUTE-COMMAND-ON-RETURN",
	    AB_package);
    Qdelete_frame = STATIC_SYMBOL("DELETE-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_frame,STATIC_FUNCTION(delete_frame,NIL,
	    FALSE,1,1));
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_command_on_return,
	    STATIC_FUNCTION(execute_command_on_return,NIL,FALSE,1,1));
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qact_on_choice_of_a_entity = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-ENTITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_entity,
	    STATIC_FUNCTION(act_on_choice_of_a_entity,NIL,FALSE,4,4));
    Qclass_choice_action = STATIC_SYMBOL("CLASS-CHOICE-ACTION",AB_package);
    mutate_global_property(Qentity,Qact_on_choice_of_a_entity,
	    Qclass_choice_action);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qact_on_choice_of_a_message = 
	    STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-MESSAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_message,
	    STATIC_FUNCTION(act_on_choice_of_a_message,NIL,FALSE,4,4));
    mutate_global_property(Qmessage,Qact_on_choice_of_a_message,
	    Qclass_choice_action);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    Qact_on_choice_of_a_readout_table = 
	    STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_readout_table,
	    STATIC_FUNCTION(act_on_choice_of_a_readout_table,NIL,FALSE,4,4));
    mutate_global_property(Qreadout_table,
	    Qact_on_choice_of_a_readout_table,Qclass_choice_action);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qact_on_choice_of_a_dial = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_dial,
	    STATIC_FUNCTION(act_on_choice_of_a_dial,NIL,FALSE,4,4));
    mutate_global_property(Qdial,Qact_on_choice_of_a_dial,
	    Qclass_choice_action);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qact_on_choice_of_a_meter = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_meter,
	    STATIC_FUNCTION(act_on_choice_of_a_meter,NIL,FALSE,4,4));
    mutate_global_property(Qmeter,Qact_on_choice_of_a_meter,
	    Qclass_choice_action);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qact_on_choice_of_a_button = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_button,
	    STATIC_FUNCTION(act_on_choice_of_a_button,NIL,FALSE,4,4));
    mutate_global_property(Qbutton,Qact_on_choice_of_a_button,
	    Qclass_choice_action);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qact_on_choice_of_a_graph = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_graph,
	    STATIC_FUNCTION(act_on_choice_of_a_graph,NIL,FALSE,4,4));
    mutate_global_property(Qgraph,Qact_on_choice_of_a_graph,
	    Qclass_choice_action);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qact_on_choice_of_a_chart = STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_chart,
	    STATIC_FUNCTION(act_on_choice_of_a_chart,NIL,FALSE,4,4));
    mutate_global_property(Qchart,Qact_on_choice_of_a_chart,
	    Qclass_choice_action);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qact_on_choice_of_a_freeform_table = 
	    STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-FREEFORM-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_freeform_table,
	    STATIC_FUNCTION(act_on_choice_of_a_freeform_table,NIL,FALSE,4,4));
    mutate_global_property(Qfreeform_table,
	    Qact_on_choice_of_a_freeform_table,Qclass_choice_action);
    string_constant_22 = 
	    STATIC_STRING("Creation of ~a instances is prohibited in run-time-only systems.");
    Qhand_place_on_return = STATIC_SYMBOL("HAND-PLACE-ON-RETURN",AB_package);
    Qreclaim_hand_placement_return_information = 
	    STATIC_SYMBOL("RECLAIM-HAND-PLACEMENT-RETURN-INFORMATION",
	    AB_package);
    Qact_on_choice_of_a_text_box = 
	    STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_text_box,
	    STATIC_FUNCTION(act_on_choice_of_a_text_box,NIL,FALSE,4,4));
    mutate_global_property(Qtext_box,Qact_on_choice_of_a_text_box,
	    Qclass_choice_action);
    Qfont_for_statements = STATIC_SYMBOL("FONT-FOR-STATEMENTS",AB_package);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    Qfont_for_free_text = STATIC_SYMBOL("FONT-FOR-FREE-TEXT",AB_package);
    Qreenter_editor_if_not_hand_placed = 
	    STATIC_SYMBOL("REENTER-EDITOR-IF-NOT-HAND-PLACED",AB_package);
    SET_SYMBOL_FUNCTION(Qhand_place_on_return,
	    STATIC_FUNCTION(hand_place_on_return,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qreclaim_hand_placement_return_information,
	    STATIC_FUNCTION(reclaim_hand_placement_return_information,NIL,
	    FALSE,1,1));
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qact_on_choice_of_a_trend_chart = 
	    STATIC_SYMBOL("ACT-ON-CHOICE-OF-A-TREND-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qact_on_choice_of_a_trend_chart,
	    STATIC_FUNCTION(act_on_choice_of_a_trend_chart,NIL,FALSE,4,4));
    mutate_global_property(Qtrend_chart,Qact_on_choice_of_a_trend_chart,
	    Qclass_choice_action);
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    array_constant_52 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qkb_configuration,array_constant_52,Qmenu_string);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct = 
	    STATIC_SYMBOL("METER-OR-DIAL-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmeter_or_dial_spot = STATIC_SYMBOL("METER-OR-DIAL-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct,
	    Qmeter_or_dial_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qmeter_or_dial_spot,
	    Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_meter_or_dial_spot == UNBOUND)
	The_type_description_of_meter_or_dial_spot = Nil;
    string_constant_29 = 
	    STATIC_STRING("43Dy8m837By1o837By83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp_1 = The_type_description_of_meter_or_dial_spot;
    The_type_description_of_meter_or_dial_spot = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_29));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_meter_or_dial_spot_g2_struct,
	    The_type_description_of_meter_or_dial_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qmeter_or_dial_spot,
	    The_type_description_of_meter_or_dial_spot,
	    Qtype_description_of_type);
    Qoutstanding_meter_or_dial_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-METER-OR-DIAL-SPOT-COUNT",AB_package);
    Qmeter_or_dial_spot_structure_memory_usage = 
	    STATIC_SYMBOL("METER-OR-DIAL-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_30 = STATIC_STRING("1q837By8s83-eby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_meter_or_dial_spot_count);
    push_optimized_constant(Qmeter_or_dial_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_30));
    Qchain_of_available_meter_or_dial_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-METER-OR-DIAL-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_meter_or_dial_spots,
	    Chain_of_available_meter_or_dial_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_meter_or_dial_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qmeter_or_dial_spot_count = STATIC_SYMBOL("METER-OR-DIAL-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmeter_or_dial_spot_count,
	    Meter_or_dial_spot_count);
    record_system_variable(Qmeter_or_dial_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_meter_or_dial_spots_vector == UNBOUND)
	Chain_of_available_meter_or_dial_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmeter_or_dial_spot_structure_memory_usage,
	    STATIC_FUNCTION(meter_or_dial_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_meter_or_dial_spot_count,
	    STATIC_FUNCTION(outstanding_meter_or_dial_spot_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_meter_or_dial_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_meter_or_dial_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmeter_or_dial_spot,
	    reclaim_structure_for_meter_or_dial_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmeter_or_dial_spot),
	    Qtype_description_of_type);
    temp = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qentity),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp;
    Qg2_defstruct_structure_name_dial_spot_g2_struct = 
	    STATIC_SYMBOL("DIAL-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdial_spot = STATIC_SYMBOL("DIAL-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_dial_spot_g2_struct,
	    Qdial_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qdial_spot,
	    Qg2_defstruct_structure_name_dial_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_dial_spot == UNBOUND)
	The_type_description_of_dial_spot = Nil;
    string_constant_31 = 
	    STATIC_STRING("43Dy8m83gey1p83gey837By83Qy8n8k1l837By0000001l1m8x837Bykqk0k0");
    temp_1 = The_type_description_of_dial_spot;
    The_type_description_of_dial_spot = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_31));
    mutate_global_property(Qg2_defstruct_structure_name_dial_spot_g2_struct,
	    The_type_description_of_dial_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qdial_spot,The_type_description_of_dial_spot,
	    Qtype_description_of_type);
    Qoutstanding_dial_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-DIAL-SPOT-COUNT",AB_package);
    Qdial_spot_structure_memory_usage = 
	    STATIC_SYMBOL("DIAL-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_32 = STATIC_STRING("1q83gey8s83-RCy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_dial_spot_count);
    push_optimized_constant(Qdial_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_32));
    Qchain_of_available_dial_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DIAL-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_dial_spots,
	    Chain_of_available_dial_spots);
    record_system_variable(Qchain_of_available_dial_spots,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qdial_spot_count = STATIC_SYMBOL("DIAL-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdial_spot_count,Dial_spot_count);
    record_system_variable(Qdial_spot_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_dial_spots_vector == UNBOUND)
	Chain_of_available_dial_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdial_spot_structure_memory_usage,
	    STATIC_FUNCTION(dial_spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_dial_spot_count,
	    STATIC_FUNCTION(outstanding_dial_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_dial_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_dial_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdial_spot,
	    reclaim_structure_for_dial_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdial_spot),
	    Qtype_description_of_type);
    temp = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qdial),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp;
    Qg2_defstruct_structure_name_meter_spot_g2_struct = 
	    STATIC_SYMBOL("METER-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmeter_spot = STATIC_SYMBOL("METER-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_meter_spot_g2_struct,
	    Qmeter_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmeter_spot,
	    Qg2_defstruct_structure_name_meter_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_meter_spot == UNBOUND)
	The_type_description_of_meter_spot = Nil;
    string_constant_33 = 
	    STATIC_STRING("43Dy8m83kjy1p83kjy837By83Qy8n8k1l837By0000001l1m8x837Bykqk0k0");
    temp_1 = The_type_description_of_meter_spot;
    The_type_description_of_meter_spot = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_33));
    mutate_global_property(Qg2_defstruct_structure_name_meter_spot_g2_struct,
	    The_type_description_of_meter_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmeter_spot,The_type_description_of_meter_spot,
	    Qtype_description_of_type);
    Qoutstanding_meter_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-METER-SPOT-COUNT",AB_package);
    Qmeter_spot_structure_memory_usage = 
	    STATIC_SYMBOL("METER-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_34 = STATIC_STRING("1q83kjy8s83-ecy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_meter_spot_count);
    push_optimized_constant(Qmeter_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_34));
    Qchain_of_available_meter_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-METER-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_meter_spots,
	    Chain_of_available_meter_spots);
    record_system_variable(Qchain_of_available_meter_spots,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qmeter_spot_count = STATIC_SYMBOL("METER-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmeter_spot_count,Meter_spot_count);
    record_system_variable(Qmeter_spot_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_meter_spots_vector == UNBOUND)
	Chain_of_available_meter_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmeter_spot_structure_memory_usage,
	    STATIC_FUNCTION(meter_spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_meter_spot_count,
	    STATIC_FUNCTION(outstanding_meter_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_meter_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_meter_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmeter_spot,
	    reclaim_structure_for_meter_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmeter_spot),
	    Qtype_description_of_type);
    temp = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qmeter),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp;
    Qcolor_parameters = STATIC_SYMBOL("COLOR-PARAMETERS",AB_package);
    list_constant_34 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qcolor_parameters,list_constant_34);
    string_constant_35 = STATIC_STRING("1l1l83ey");
    string_constant_36 = 
	    STATIC_STRING("1q4z8r83BIy83BIy83ICy83ICy083Ciy001n1l8o1l8l1m8p83BIy000004z8r83IDy83IDy83ICy83ICy083FBy001n1l8o1l8l1m8p83BJy000004z8r83IEy83IEy");
    string_constant_37 = 
	    STATIC_STRING("83ICy83ICy0830*y001n1l8o1l8l1m8p83BJy000004z8r83Wdy83Wdy83ICy83ICy0l001n1l8o1l8l1m8p83E3y000004z8r83Wey83Wey83ICy83ICy0n001n1l8o");
    string_constant_38 = 
	    STATIC_STRING("1l8l1m8p83E3y000004z8r83K+y83K+y83ICy83ICy08k001n1l8o1l8l1m8p83Ky00000");
    string_constant_39 = 
	    STATIC_STRING("1s8q1n83ICy1l83-sy83ey1p83BIy83Ciy8o8l1m8p83BIy1p83IDy83FBy8o8l1m8p83BJy1p83IEy830*y8o8l1m8p83BJy1p83Wdyl8o8l1m8p83E3y1p83Weyn8o");
    string_constant_40 = STATIC_STRING("8l1m8p83E3y1p83K+y8k8o8l1m8p83Ky");
    temp_1 = regenerate_optimized_constant(string_constant_35);
    temp_2 = regenerate_optimized_constant(LIST_3(string_constant_36,
	    string_constant_37,string_constant_38));
    add_class_to_environment(9,Qcolor_parameters,list_constant_34,Nil,
	    temp_1,Nil,temp_2,list_constant_34,
	    regenerate_optimized_constant(LIST_2(string_constant_39,
	    string_constant_40)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_parameters,Color_parameters);
    Qfacilities = STATIC_SYMBOL("FACILITIES",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qcolor_parameters,Qfacilities,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qdismiss_color_menu_after_choosing_qm = 
	    STATIC_SYMBOL("DISMISS-COLOR-MENU-AFTER-CHOOSING\?",AB_package);
    Qdo_not_dismiss_color_menu_after_choosing_qm = 
	    STATIC_SYMBOL("DO-NOT-DISMISS-COLOR-MENU-AFTER-CHOOSING\?",
	    AB_package);
    Qput_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-DO-NOT-DISMISS-COLOR-MENU-AFTER-CHOOSING\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qdo_not_dismiss_color_menu_after_choosing_qm,
	    SYMBOL_FUNCTION(Qput_do_not_dismiss_color_menu_after_choosing_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    string_constant_41 = 
	    STATIC_STRING("1n1m83BIy1m9k83-aJy1m83BIy1m9k83-Jay1m83BIy1m9k83Ciy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_41));
    Qcolor_menu_ordering = STATIC_SYMBOL("COLOR-MENU-ORDERING",AB_package);
    Qwrite_color_menu_ordering_from_slot = 
	    STATIC_SYMBOL("WRITE-COLOR-MENU-ORDERING-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_color_menu_ordering_from_slot,
	    STATIC_FUNCTION(write_color_menu_ordering_from_slot,NIL,FALSE,
	    2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qcolor_menu_ordering,
	    SYMBOL_FUNCTION(Qwrite_color_menu_ordering_from_slot),
	    Qslot_value_writer);
    string_constant_42 = 
	    STATIC_STRING("1n1m83BJy1m9k830*y1n83BJy1m1m9k837Ry1m9k9l83FBy1m83BJy83-cqy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qset);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_42));
    Qlist_of_colors = STATIC_SYMBOL("LIST-OF-COLORS",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    add_grammar_rules_for_list(5,Qlist_of_colors,Qcolor,Qcm,Nil,Qnone);
    Qcolor_set_spec = STATIC_SYMBOL("COLOR-SET-SPEC",AB_package);
    Qcompile_color_set_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-COLOR-SET-SPEC-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_color_set_spec_for_slot,
	    STATIC_FUNCTION(compile_color_set_spec_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qcolor_set_spec,
	    SYMBOL_FUNCTION(Qcompile_color_set_spec_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qcolor_set_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qall_including_new_pastels = STATIC_SYMBOL("ALL-INCLUDING-NEW-PASTELS",
	    AB_package);
    string_constant_23 = STATIC_STRING("all, including the new pastels");
    Qwrite_color_set_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-COLOR-SET-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_color_set_spec_from_slot,
	    STATIC_FUNCTION(write_color_set_spec_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcolor_set_spec,
	    SYMBOL_FUNCTION(Qwrite_color_set_spec_from_slot),
	    Qslot_value_writer);
    Qcolors_on_1st_level_color_menu = 
	    STATIC_SYMBOL("COLORS-ON-1ST-LEVEL-COLOR-MENU",AB_package);
    Qput_colors_on_1st_level_color_menu = 
	    STATIC_SYMBOL("PUT-COLORS-ON-1ST-LEVEL-COLOR-MENU",AB_package);
    SET_SYMBOL_FUNCTION(Qput_colors_on_1st_level_color_menu,
	    STATIC_FUNCTION(put_colors_on_1st_level_color_menu,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qcolors_on_1st_level_color_menu,
	    SYMBOL_FUNCTION(Qput_colors_on_1st_level_color_menu),Qslot_putter);
    Qcolors_on_2nd_level_color_menu = 
	    STATIC_SYMBOL("COLORS-ON-2ND-LEVEL-COLOR-MENU",AB_package);
    Qput_colors_on_2nd_level_color_menu = 
	    STATIC_SYMBOL("PUT-COLORS-ON-2ND-LEVEL-COLOR-MENU",AB_package);
    SET_SYMBOL_FUNCTION(Qput_colors_on_2nd_level_color_menu,
	    STATIC_FUNCTION(put_colors_on_2nd_level_color_menu,NIL,FALSE,3,3));
    mutate_global_property(Qcolors_on_2nd_level_color_menu,
	    SYMBOL_FUNCTION(Qput_colors_on_2nd_level_color_menu),Qslot_putter);
    string_constant_43 = 
	    STATIC_STRING("1r1m83E3y1m9kl1m83E3y1m9km1m83E3y1m9kn1m83E3y1m9ko1m83E3y1m9kp1m83E3y1m9kq1m83E3y1m9kr");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_43));
    Qnumber_of_menu_columns_spec = 
	    STATIC_SYMBOL("NUMBER-OF-MENU-COLUMNS-SPEC",AB_package);
    Qwrite_number_of_menu_columns_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-NUMBER-OF-MENU-COLUMNS-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_number_of_menu_columns_spec_from_slot,
	    STATIC_FUNCTION(write_number_of_menu_columns_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnumber_of_menu_columns_spec,
	    SYMBOL_FUNCTION(Qwrite_number_of_menu_columns_spec_from_slot),
	    Qslot_value_writer);
    Qleft_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    string_constant_44 = 
	    STATIC_STRING("13Hy83*by83byl83ayl83Wyl83cyl83ny1l83-ry83ty3Dy83syx83uyk83wy083iy3-Wy");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qleft_aligned_color_menu_item_format,
	    regenerate_optimized_constant(string_constant_44),
	    Qformat_description);
    Qcenter_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    string_constant_45 = 
	    STATIC_STRING("13Hy83*by83byl83ayl83Wyl83cyl83ny1l83-ry83ty3Dy83syx83uyk83wy83-cy83iy3-Wy");
    mutate_global_property(Qcenter_aligned_color_menu_item_format,
	    regenerate_optimized_constant(string_constant_45),
	    Qformat_description);
    Qright_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    mutate_global_property(Qright_aligned_color_menu_item_format,
	    regenerate_optimized_constant(string_constant_45),
	    Qformat_description);
    Qcolor_menu_table_format = STATIC_SYMBOL("COLOR-MENU-TABLE-FORMAT",
	    AB_package);
    string_constant_46 = 
	    STATIC_STRING("13Fy83*ny83=wy83fy832Py83fy837Ty83fy8308ym830Aym8309ym8307ym83=Dyl83=Nyl");
    mutate_global_property(Qcolor_menu_table_format,
	    regenerate_optimized_constant(string_constant_46),
	    Qformat_description);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qbounding_box = STATIC_SYMBOL("BOUNDING-BOX",AB_package);
    check_if_superior_classes_are_defined(Qbounding_box,list_constant_32);
    string_constant_47 = 
	    STATIC_STRING("1l4z8r83xy83xy83HIy83HIy083HJy001n1l8l1l83Ey1m83Dy53CyExport, writable00000");
    string_constant_48 = STATIC_STRING("1n8q1m83HIy1l83-ly1m83xy83HJy");
    temp_1 = regenerate_optimized_constant(string_constant_25);
    temp_2 = regenerate_optimized_constant(string_constant_47);
    add_class_to_environment(9,Qbounding_box,list_constant_32,Nil,temp_1,
	    Nil,temp_2,list_constant_32,
	    regenerate_optimized_constant(string_constant_48),Nil);
    Bounding_box_class_description = 
	    lookup_global_or_kb_specific_property_value(Qbounding_box,
	    Class_description_gkbprop);
    Qbounding_box_format = STATIC_SYMBOL("BOUNDING-BOX-FORMAT",AB_package);
    string_constant_49 = STATIC_STRING("1t83-My83*=yp83*1yp83*0yp83**yp");
    mutate_global_property(Qbounding_box_format,
	    regenerate_optimized_constant(string_constant_49),
	    Qformat_description);
    Qg2_defstruct_structure_name_bounding_box_spot_g2_struct = 
	    STATIC_SYMBOL("BOUNDING-BOX-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbounding_box_spot = STATIC_SYMBOL("BOUNDING-BOX-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_bounding_box_spot_g2_struct,
	    Qbounding_box_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qbounding_box_spot,
	    Qg2_defstruct_structure_name_bounding_box_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_bounding_box_spot == UNBOUND)
	The_type_description_of_bounding_box_spot = Nil;
    string_constant_50 = 
	    STATIC_STRING("43Dy8m83fPy1o83fPy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp_1 = The_type_description_of_bounding_box_spot;
    The_type_description_of_bounding_box_spot = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_50));
    mutate_global_property(Qg2_defstruct_structure_name_bounding_box_spot_g2_struct,
	    The_type_description_of_bounding_box_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qbounding_box_spot,
	    The_type_description_of_bounding_box_spot,
	    Qtype_description_of_type);
    Qoutstanding_bounding_box_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-BOUNDING-BOX-SPOT-COUNT",AB_package);
    Qbounding_box_spot_structure_memory_usage = 
	    STATIC_SYMBOL("BOUNDING-BOX-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_51 = STATIC_STRING("1q83fPy8s83-Kxy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_bounding_box_spot_count);
    push_optimized_constant(Qbounding_box_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_51));
    Qchain_of_available_bounding_box_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BOUNDING-BOX-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_bounding_box_spots,
	    Chain_of_available_bounding_box_spots);
    record_system_variable(Qchain_of_available_bounding_box_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbounding_box_spot_count = STATIC_SYMBOL("BOUNDING-BOX-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbounding_box_spot_count,
	    Bounding_box_spot_count);
    record_system_variable(Qbounding_box_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_bounding_box_spots_vector == UNBOUND)
	Chain_of_available_bounding_box_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbounding_box_spot_structure_memory_usage,
	    STATIC_FUNCTION(bounding_box_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_bounding_box_spot_count,
	    STATIC_FUNCTION(outstanding_bounding_box_spot_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_bounding_box_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_bounding_box_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qbounding_box_spot,
	    reclaim_structure_for_bounding_box_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbounding_box_spot),
	    Qtype_description_of_type);
    temp = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qbounding_box),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp;
    Qgenerate_spot_for_bounding_box = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-BOUNDING-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_bounding_box,
	    STATIC_FUNCTION(generate_spot_for_bounding_box,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp = SYMBOL_FUNCTION(Qgenerate_spot_for_bounding_box);
    set_get(Qbounding_box,Qgenerate_spot,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp = CONS(Qbounding_box,temp_1);
    mutate_global_property(Qgenerate_spot,temp,Qclasses_which_define);
    Qg2_defstruct_structure_name_bounding_state_g2_struct = 
	    STATIC_SYMBOL("BOUNDING-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbounding_state = STATIC_SYMBOL("BOUNDING-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_bounding_state_g2_struct,
	    Qbounding_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qbounding_state,
	    Qg2_defstruct_structure_name_bounding_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_bounding_state == UNBOUND)
	The_type_description_of_bounding_state = Nil;
    string_constant_52 = 
	    STATIC_STRING("43Dy8m83fRy1o83fRy83-Sy8n8k1l83-Sy0000001m1n8y83-2vy1w83r+y83r*y83r0y83r=y83vQy83-H9y83-HFy83-D=y83-D0y83r-y83qdy83-H+y1m8x83-Sy");
    string_constant_53 = STATIC_STRING("kzk0k0");
    temp_1 = The_type_description_of_bounding_state;
    The_type_description_of_bounding_state = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(LIST_2(string_constant_52,
	    string_constant_53)));
    mutate_global_property(Qg2_defstruct_structure_name_bounding_state_g2_struct,
	    The_type_description_of_bounding_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qbounding_state,
	    The_type_description_of_bounding_state,Qtype_description_of_type);
    Qoutstanding_bounding_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-BOUNDING-STATE-COUNT",AB_package);
    Qbounding_state_structure_memory_usage = 
	    STATIC_SYMBOL("BOUNDING-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_54 = STATIC_STRING("1q83fRy8s83-L-y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_bounding_state_count);
    push_optimized_constant(Qbounding_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_54));
    Qchain_of_available_bounding_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BOUNDING-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_bounding_states,
	    Chain_of_available_bounding_states);
    record_system_variable(Qchain_of_available_bounding_states,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qbounding_state_count = STATIC_SYMBOL("BOUNDING-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbounding_state_count,Bounding_state_count);
    record_system_variable(Qbounding_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_bounding_states_vector == UNBOUND)
	Chain_of_available_bounding_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbounding_state_structure_memory_usage,
	    STATIC_FUNCTION(bounding_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_bounding_state_count,
	    STATIC_FUNCTION(outstanding_bounding_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_bounding_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_bounding_state,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qbounding_state,
	    reclaim_structure_for_bounding_state_1);
    Qtop_level_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-IS-SELECTION-STYLE",AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qbounding_state,Qtop_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qbounding = STATIC_SYMBOL("BOUNDING",AB_package);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    make_context_description(Qbounding,Qtop_level,Qnil,Qnil);
    Qenter_keys_in_bounding_state = 
	    STATIC_SYMBOL("ENTER-KEYS-IN-BOUNDING-STATE",AB_package);
    Qmouse_down_on_close_box_widget_in_bounding_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-ON-CLOSE-BOX-WIDGET-IN-BOUNDING-STATE",
	    AB_package);
    Qsearch_for_mouse_drag = STATIC_SYMBOL("SEARCH-FOR-MOUSE-DRAG",AB_package);
    Qstart_dragging_title_bar_handler = 
	    STATIC_SYMBOL("START-DRAGGING-TITLE-BAR-HANDLER",AB_package);
    Qmouse_down_on_image_plane_in_bounding_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-ON-IMAGE-PLANE-IN-BOUNDING-STATE",
	    AB_package);
    Qrequeue_event_and_abort_workstation_context = 
	    STATIC_SYMBOL("REQUEUE-EVENT-AND-ABORT-WORKSTATION-CONTEXT",
	    AB_package);
    Qmouse_motion_in_bounding_state = 
	    STATIC_SYMBOL("MOUSE-MOTION-IN-BOUNDING-STATE",AB_package);
    Qmouse_up_in_bounding_state = 
	    STATIC_SYMBOL("MOUSE-UP-IN-BOUNDING-STATE",AB_package);
    string_constant_55 = 
	    STATIC_STRING("1s1n83GMy8k9k1n830Dy836gy9l1n830Dy83AFy9m1n834xy83AFy9n1n830Dy8349y9o1n830Dy8k9p1n830+y8k9q1n830-y8k9r");
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qenter_keys_in_bounding_state);
    push_optimized_constant(Qmouse_down_on_close_box_widget_in_bounding_state);
    push_optimized_constant(Qsearch_for_mouse_drag);
    push_optimized_constant(Qstart_dragging_title_bar_handler);
    push_optimized_constant(Qmouse_down_on_image_plane_in_bounding_state);
    push_optimized_constant(Qrequeue_event_and_abort_workstation_context);
    push_optimized_constant(Qmouse_motion_in_bounding_state);
    push_optimized_constant(Qmouse_up_in_bounding_state);
    make_keymap(Qbounding,Qbounding,
	    regenerate_optimized_constant(string_constant_55),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qbounding,Qbounding);
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    valid_workstation_context_p_for_bounding_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_bounding_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qbounding_state,valid_workstation_context_p_for_bounding_state_1);
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_bounding_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_bounding_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qbounding_state,clean_up_workstation_context_for_bounding_state_1);
    Qdialog_message_format = STATIC_SYMBOL("DIALOG-MESSAGE-FORMAT",AB_package);
    string_constant_56 = 
	    STATIC_STRING("13Fy832Wy83byn83ayn83Wyn83cyn83ny1l83-uy83*=yk83*1yk83*0yk83**yk");
    mutate_global_property(Qdialog_message_format,
	    regenerate_optimized_constant(string_constant_56),
	    Qformat_description);
    string_constant_24 = 
	    STATIC_STRING("Select operation on area after moving its edges and corners");
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    string_constant_57 = STATIC_STRING("Move");
    Qmove_area = STATIC_SYMBOL("MOVE-AREA",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)3L,Qmove,string_constant_57,
	    Qmove_area);
    Qclone = STATIC_SYMBOL("CLONE",AB_package);
    string_constant_58 = STATIC_STRING("Clone");
    Qclone_area = STATIC_SYMBOL("CLONE-AREA",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)3L,Qclone,string_constant_58,
	    Qclone_area);
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    string_constant_59 = STATIC_STRING("Transfer");
    Qtransfer_area = STATIC_SYMBOL("TRANSFER-AREA",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qtransfer,
	    string_constant_59,Qtransfer_area);
    list_constant_46 = STATIC_LIST((SI_Long)3L,list_constant_35,
	    list_constant_36,list_constant_37);
    string_constant_60 = STATIC_STRING("Left");
    Qmove_area_to_left = STATIC_SYMBOL("MOVE-AREA-TO-LEFT",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)3L,Qleft,string_constant_60,
	    Qmove_area_to_left);
    Ql_r_center = STATIC_SYMBOL("L-R-CENTER",AB_package);
    string_constant_61 = STATIC_STRING("L/R Center");
    Qmove_area_to_l_r_center = STATIC_SYMBOL("MOVE-AREA-TO-L-R-CENTER",
	    AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)3L,Ql_r_center,
	    string_constant_61,Qmove_area_to_l_r_center);
    string_constant_62 = STATIC_STRING("Right");
    Qmove_area_to_right = STATIC_SYMBOL("MOVE-AREA-TO-RIGHT",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qright,string_constant_62,
	    Qmove_area_to_right);
    list_constant_47 = STATIC_LIST((SI_Long)3L,list_constant_38,
	    list_constant_39,list_constant_40);
    string_constant_63 = STATIC_STRING("Top");
    Qmove_area_to_top = STATIC_SYMBOL("MOVE-AREA-TO-TOP",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)3L,Qtop,string_constant_63,
	    Qmove_area_to_top);
    Qt_b_center = STATIC_SYMBOL("T-B-CENTER",AB_package);
    string_constant_64 = STATIC_STRING("T/B Center");
    Qmove_area_to_t_b_center = STATIC_SYMBOL("MOVE-AREA-TO-T-B-CENTER",
	    AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qt_b_center,
	    string_constant_64,Qmove_area_to_t_b_center);
    string_constant_65 = STATIC_STRING("Bottom");
    Qmove_area_to_bottom = STATIC_SYMBOL("MOVE-AREA-TO-BOTTOM",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)3L,Qbottom,string_constant_65,
	    Qmove_area_to_bottom);
    list_constant_48 = STATIC_LIST((SI_Long)3L,list_constant_41,
	    list_constant_42,list_constant_43);
    string_constant_66 = STATIC_STRING("Delete");
    Qdelete_area = STATIC_SYMBOL("DELETE-AREA",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)3L,Qdelete,string_constant_66,
	    Qdelete_area);
    Qquit = STATIC_SYMBOL("QUIT",AB_package);
    string_constant_67 = STATIC_STRING("Quit");
    Qsizing_quit = STATIC_SYMBOL("SIZING-QUIT",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qquit,string_constant_67,
	    Qsizing_quit);
    list_constant_49 = STATIC_LIST((SI_Long)2L,list_constant_44,
	    list_constant_45);
    list_constant_11 = STATIC_LIST((SI_Long)4L,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49);
    Qsizing_dialog_message_string = 
	    STATIC_SYMBOL("SIZING-DIALOG-MESSAGE-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsizing_dialog_message_string,
	    Sizing_dialog_message_string);
    string_constant_68 = STATIC_STRING("Done moving edges and corners\?");
    SET_SYMBOL_VALUE(Qsizing_dialog_message_string,string_constant_68);
    Qcancel = STATIC_SYMBOL("CANCEL",AB_package);
    string_constant_69 = STATIC_STRING("Cancel");
    list_constant_50 = STATIC_CONS(Qsizing_quit,Qnil);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)3L,Qcancel,
	    string_constant_69,list_constant_50);
    Qok = STATIC_SYMBOL("OK",AB_package);
    string_constant_70 = STATIC_STRING("Yes");
    Qsizing_ok = STATIC_SYMBOL("SIZING-OK",AB_package);
    list_constant_51 = STATIC_CONS(Qt,Qnil);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)4L,Qok,string_constant_70,
	    Qsizing_ok,list_constant_51);
    list_constant_56 = STATIC_LIST((SI_Long)2L,list_constant_52,
	    list_constant_53);
    Qrestore_to_normal_size = STATIC_SYMBOL("RESTORE-TO-NORMAL-SIZE",
	    AB_package);
    string_constant_71 = STATIC_STRING("Restore to Normal Size");
    Qsizing_restore = STATIC_SYMBOL("SIZING-RESTORE",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qrestore_to_normal_size,
	    string_constant_71,Qsizing_restore);
    Qupdate_now = STATIC_SYMBOL("UPDATE-NOW",AB_package);
    string_constant_72 = STATIC_STRING("Update Now");
    Qsizing_update = STATIC_SYMBOL("SIZING-UPDATE",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qupdate_now,
	    string_constant_72,Qsizing_update);
    list_constant_57 = STATIC_LIST((SI_Long)2L,list_constant_54,
	    list_constant_55);
    list_constant_12 = STATIC_LIST((SI_Long)2L,list_constant_56,
	    list_constant_57);
    Qno_minimum = STATIC_SYMBOL("NO-MINIMUM",AB_package);
    string_constant_73 = STATIC_STRING("No Minimum");
    Qsizing_no_minimum = STATIC_SYMBOL("SIZING-NO-MINIMUM",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qno_minimum,
	    string_constant_73,Qsizing_no_minimum);
    list_constant_59 = STATIC_CONS(list_constant_55,Qnil);
    list_constant_60 = STATIC_CONS(list_constant_58,list_constant_59);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_56,
	    list_constant_60);
    SET_SYMBOL_FUNCTION(Qsizing_ok,STATIC_FUNCTION(sizing_ok,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qsizing_quit,STATIC_FUNCTION(sizing_quit,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qsizing_restore,STATIC_FUNCTION(sizing_restore,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qsizing_update,STATIC_FUNCTION(sizing_update,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qsizing_no_minimum,
	    STATIC_FUNCTION(sizing_no_minimum,NIL,FALSE,0,0));
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qmove_area,STATIC_FUNCTION(move_area,NIL,FALSE,0,0));
    Qfix_up_bounding_state_if_necessary_after_transfer = 
	    STATIC_SYMBOL("FIX-UP-BOUNDING-STATE-IF-NECESSARY-AFTER-TRANSFER",
	    AB_package);
    Qtransfer_source = STATIC_SYMBOL("TRANSFER-SOURCE",AB_package);
    SET_SYMBOL_FUNCTION(Qtransfer_area,STATIC_FUNCTION(transfer_area,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qclone_area,STATIC_FUNCTION(clone_area,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qdelete_area,STATIC_FUNCTION(delete_area,NIL,FALSE,
	    0,0));
    Qleft_sl_right_center = STATIC_SYMBOL("LEFT/RIGHT-CENTER",AB_package);
    Qtop_sl_bottom_center = STATIC_SYMBOL("TOP/BOTTOM-CENTER",AB_package);
    Qhorizontally = STATIC_SYMBOL("HORIZONTALLY",AB_package);
    Qmidline_x_of_block_function = 
	    STATIC_SYMBOL("MIDLINE-X-OF-BLOCK-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmidline_x_of_block_function,
	    STATIC_FUNCTION(midline_x_of_block_function,NIL,FALSE,1,1));
    Qvertically = STATIC_SYMBOL("VERTICALLY",AB_package);
    Qmidline_y_of_block_function = 
	    STATIC_SYMBOL("MIDLINE-Y-OF-BLOCK-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmidline_y_of_block_function,
	    STATIC_FUNCTION(midline_y_of_block_function,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmove_area_to_left,
	    STATIC_FUNCTION(move_area_to_left,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmove_area_to_l_r_center,
	    STATIC_FUNCTION(move_area_to_l_r_center,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmove_area_to_right,
	    STATIC_FUNCTION(move_area_to_right,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmove_area_to_top,STATIC_FUNCTION(move_area_to_top,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmove_area_to_t_b_center,
	    STATIC_FUNCTION(move_area_to_t_b_center,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmove_area_to_bottom,
	    STATIC_FUNCTION(move_area_to_bottom,NIL,FALSE,0,0));
    Qchange_size_per_bounding_rectangle = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE",AB_package);
    Qleft_edge = STATIC_SYMBOL("LEFT-EDGE",AB_package);
    Qtop_edge = STATIC_SYMBOL("TOP-EDGE",AB_package);
    Qright_edge = STATIC_SYMBOL("RIGHT-EDGE",AB_package);
    Qbottom_edge = STATIC_SYMBOL("BOTTOM-EDGE",AB_package);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)6L,Qblock,Qleft_edge,Qtop_edge,
	    Qright_edge,Qbottom_edge,Qmode);
    mutate_global_property(Qchange_size_per_bounding_rectangle,
	    list_constant_61,Qgeneric_method_lambda_list);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle,NIL,TRUE,5,6));
    Qchange_size_per_bounding_rectangle_for_block = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_block,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_block,
	    NIL,FALSE,6,6));
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_block);
    set_get(Qblock,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qchange_size_per_bounding_rectangle_for_kb_workspace = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_kb_workspace,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_kb_workspace,
	    NIL,FALSE,6,6));
    temp = 
	    SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_kb_workspace);
    set_get(Qkb_workspace,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qchange_size_per_bounding_rectangle_for_connection = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_connection,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_connection,
	    NIL,FALSE,6,6));
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_connection);
    set_get(Qconnection,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qconnection,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qchange_size_per_bounding_rectangle_for_action_button = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-ACTION-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_action_button,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_action_button,
	    NIL,FALSE,6,6));
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    temp = 
	    SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_action_button);
    set_get(Qaction_button,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qaction_button,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    if (Width_for_change_size_qm == UNBOUND)
	Width_for_change_size_qm = Nil;
    if (Height_for_change_size_qm == UNBOUND)
	Height_for_change_size_qm = Nil;
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qchange_size_per_bounding_rectangle_for_entity = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-ENTITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_entity,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_entity,
	    NIL,FALSE,6,6));
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_entity);
    set_get(Qentity,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    if (Force_change_to_minimum_size_p == UNBOUND)
	Force_change_to_minimum_size_p = Nil;
    Qscale = STATIC_SYMBOL("SCALE",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qtext_x_magnification = STATIC_SYMBOL("TEXT-X-MAGNIFICATION",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qtext_y_magnification = STATIC_SYMBOL("TEXT-Y-MAGNIFICATION",AB_package);
    Qset_maximum = STATIC_SYMBOL("SET-MAXIMUM",AB_package);
    Qtext_cell_desired_maximum_line_measure_for_text_box_qm = 
	    STATIC_SYMBOL("TEXT-CELL-DESIRED-MAXIMUM-LINE-MEASURE-FOR-TEXT-BOX\?",
	    AB_package);
    Qchange_size_per_bounding_rectangle_for_text_box = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-TEXT-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_text_box,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_text_box,
	    NIL,FALSE,6,6));
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_text_box);
    set_get(Qtext_box,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qtext_box,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qchange_size_per_bounding_rectangle_for_trend_chart = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-TREND-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_trend_chart,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_trend_chart,
	    NIL,FALSE,6,6));
    temp = 
	    SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_trend_chart);
    set_get(Qtrend_chart,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qtrend_chart,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qgraph_format = STATIC_SYMBOL("GRAPH-FORMAT",AB_package);
    Qminimum_graph_width = STATIC_SYMBOL("MINIMUM-GRAPH-WIDTH",AB_package);
    Qminimum_graph_height = STATIC_SYMBOL("MINIMUM-GRAPH-HEIGHT",AB_package);
    Qchange_size_per_bounding_rectangle_for_graph = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_graph,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_graph,
	    NIL,FALSE,6,6));
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_graph);
    set_get(Qgraph,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    SET_SYMBOL_VALUE_LOCATION(Qchart,Chart);
    Qchange_size_per_bounding_rectangle_for_chart = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE-FOR-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_chart,
	    STATIC_FUNCTION(change_size_per_bounding_rectangle_for_chart,
	    NIL,FALSE,6,6));
    temp = SYMBOL_FUNCTION(Qchange_size_per_bounding_rectangle_for_chart);
    set_get(Qchart,Qchange_size_per_bounding_rectangle,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchange_size_per_bounding_rectangle),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qchange_size_per_bounding_rectangle,temp,
	    Qclasses_which_define);
    Qclone_or_transfer_target = STATIC_SYMBOL("CLONE-OR-TRANSFER-TARGET",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_up_bounding_state_if_necessary_after_transfer,
	    STATIC_FUNCTION(fix_up_bounding_state_if_necessary_after_transfer,
	    NIL,FALSE,1,1));
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qenter_keys_in_bounding_state,
	    Qenter_keys_in_bounding_state,Qnew_style_event_handler);
    Qdefault_action_button = STATIC_SYMBOL("DEFAULT-ACTION-BUTTON",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_keys_in_bounding_state,
	    STATIC_FUNCTION(enter_keys_in_bounding_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_on_image_plane_in_bounding_state,
	    Qmouse_down_on_image_plane_in_bounding_state,
	    Qnew_style_event_handler);
    Qtop_left = STATIC_SYMBOL("TOP-LEFT",AB_package);
    Qbottom_left = STATIC_SYMBOL("BOTTOM-LEFT",AB_package);
    Qtop_right = STATIC_SYMBOL("TOP-RIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_down_on_image_plane_in_bounding_state,
	    STATIC_FUNCTION(mouse_down_on_image_plane_in_bounding_state,
	    NIL,FALSE,1,1));
    mutate_global_property(Qmouse_up_in_bounding_state,
	    Qmouse_up_in_bounding_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_up_in_bounding_state,
	    STATIC_FUNCTION(mouse_up_in_bounding_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_motion_in_bounding_state,
	    Qmouse_motion_in_bounding_state,Qnew_style_event_handler);
    Qbottom_right = STATIC_SYMBOL("BOTTOM-RIGHT",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)4L,Qtop_left,Qtop_right,
	    Qbottom_left,Qbottom_right);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qbottom_left,Qtop_right);
    float_constant_1 = STATIC_FLOAT(1.0);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_bounding_state,
	    STATIC_FUNCTION(mouse_motion_in_bounding_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_on_close_box_widget_in_bounding_state,
	    Qmouse_down_on_close_box_widget_in_bounding_state,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_down_on_close_box_widget_in_bounding_state,
	    STATIC_FUNCTION(mouse_down_on_close_box_widget_in_bounding_state,
	    NIL,FALSE,1,1));
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    array_constant_17 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)63L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)57344L);
    Qdelete_blocks_for_operate_on_area_upon_confirmation = 
	    STATIC_SYMBOL("DELETE-BLOCKS-FOR-OPERATE-ON-AREA-UPON-CONFIRMATION",
	    AB_package);
    Qreclaim_dragging_list_function = 
	    STATIC_SYMBOL("RECLAIM-DRAGGING-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_blocks_for_operate_on_area_upon_confirmation,
	    STATIC_FUNCTION(delete_blocks_for_operate_on_area_upon_confirmation,
	    NIL,FALSE,1,1));
    Qreclaim_dragging_cons_function = 
	    STATIC_SYMBOL("RECLAIM-DRAGGING-CONS-FUNCTION",AB_package);
    Qworkspace_invalidation_handling_procedure_qm = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-PROCEDURE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_procedure_qm,
	    Workspace_invalidation_handling_procedure_qm);
    record_system_variable(Qworkspace_invalidation_handling_procedure_qm,
	    Qfacilities,Nil,Qnil,Qnil,Qnil,Qt);
    Qworkspace_invalidation_handling_procedure_fsn_qm = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-PROCEDURE-FSN\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_procedure_fsn_qm,
	    Workspace_invalidation_handling_procedure_fsn_qm);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    record_system_variable(Qworkspace_invalidation_handling_procedure_fsn_qm,
	    Qfacilities,Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    Qworkspace_invalidation_handling_workspace_queue = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-WORKSPACE-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_workspace_queue,
	    Workspace_invalidation_handling_workspace_queue);
    Qreclaim_slot_value_list_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-LIST-FUNCTION",AB_package);
    record_system_variable(Qworkspace_invalidation_handling_workspace_queue,
	    Qfacilities,Nil,Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qworkspace_invalidation_handling_fsn_queue = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-FSN-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_fsn_queue,
	    Workspace_invalidation_handling_fsn_queue);
    Qreclaim_slot_value_fsn_queue = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-FSN-QUEUE",AB_package);
    record_system_variable(Qworkspace_invalidation_handling_fsn_queue,
	    Qfacilities,Nil,Qnil,Qnil,Qreclaim_slot_value_fsn_queue,Qt);
    Qworkspace_invalidation_handling_window_queue = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-WINDOW-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_window_queue,
	    Workspace_invalidation_handling_window_queue);
    record_system_variable(Qworkspace_invalidation_handling_window_queue,
	    Qfacilities,Nil,Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qworkspace_invalidation_handling_event_type_queue = 
	    STATIC_SYMBOL("WORKSPACE-INVALIDATION-HANDLING-EVENT-TYPE-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_invalidation_handling_event_type_queue,
	    Workspace_invalidation_handling_event_type_queue);
    record_system_variable(Qworkspace_invalidation_handling_event_type_queue,
	    Qfacilities,Nil,Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qg2_register_workspace_invalidation_handling_procedure = 
	    STATIC_SYMBOL("G2-REGISTER-WORKSPACE-INVALIDATION-HANDLING-PROCEDURE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_register_workspace_invalidation_handling_procedure,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_register_workspace_invalidation_handling_procedure,
	    STATIC_FUNCTION(g2_register_workspace_invalidation_handling_procedure,
	    NIL,FALSE,1,1));
    Qg2_get_invalid_workspace_to_handle = 
	    STATIC_SYMBOL("G2-GET-INVALID-WORKSPACE-TO-HANDLE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_invalid_workspace_to_handle,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_invalid_workspace_to_handle,
	    STATIC_FUNCTION(g2_get_invalid_workspace_to_handle,NIL,FALSE,0,0));
    Qg2_more_invalid_workspaces_to_be_handled = 
	    STATIC_SYMBOL("G2-MORE-INVALID-WORKSPACES-TO-BE-HANDLED",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_more_invalid_workspaces_to_be_handled,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_more_invalid_workspaces_to_be_handled,
	    STATIC_FUNCTION(g2_more_invalid_workspaces_to_be_handled,NIL,
	    FALSE,0,0));
    if (Simple_dialog_title_qm == UNBOUND)
	Simple_dialog_title_qm = Nil;
    if (Simple_dialog_fill_text_p == UNBOUND)
	Simple_dialog_fill_text_p = T;
    if (Simple_dialog_plist_qm == UNBOUND)
	Simple_dialog_plist_qm = Nil;
    Qlistbox = STATIC_SYMBOL("LISTBOX",AB_package);
}
