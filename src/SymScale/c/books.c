/* books.c
 * Input file:  books.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "books.h"


static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object array_constant;      /* # */

/* WRITE-FORMAT-FROM-SLOT */
Object write_format_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object names_for_frame_qm;

    x_note_fn_call(116,0);
    names_for_frame_qm = get_lookup_slot_value_given_default(slot_value,
	    Qname_or_names_for_frame,Nil);
    if (names_for_frame_qm)
	return twrite_symbol(1,ATOM(names_for_frame_qm) ? 
		names_for_frame_qm : CAR(names_for_frame_qm));
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

/* RECLAIM-STACK-OF-PAGES-VALUE */
Object reclaim_stack_of_pages_value(stack_of_pages,book)
    Object stack_of_pages, book;
{
    Object temp;

    x_note_fn_call(116,1);
  next_loop:
    if ( !TRUEP(ISVREF(book,(SI_Long)20L)))
	goto end_loop;
    temp = ISVREF(book,(SI_Long)20L);
    delete_frame(CAR(temp));
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
}

/* RECLAIM-BOOK-THIS-IS-PART-OF-VALUE */
Object reclaim_book_this_is_part_of_value(book,page)
    Object book, page;
{
    Object svref_new_value;

    x_note_fn_call(116,2);
    svref_new_value = delete_slot_value_element_1(page,ISVREF(book,
	    (SI_Long)20L));
    ISVREF(book,(SI_Long)20L) = svref_new_value;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Logbook_parameters, Qlogbook_parameters);

/* WRITE-DOCKING-POSITION-SPEC-FROM-SLOT */
Object write_docking_position_spec_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(116,3);
    return twrite_symbol(1,value);
}

static Object Qprefer_native_logbook;  /* prefer-native-logbook */

static Object Qprefer_native;      /* prefer-native */

/* PUT-PREFER-NATIVE-LOGBOOK */
Object put_prefer_native_logbook(logbook_parameters_instance,new_value,
	    initializing_qm)
    Object logbook_parameters_instance, new_value, initializing_qm;
{
    Object old_value;

    x_note_fn_call(116,4);
    old_value = ISVREF(logbook_parameters_instance,(SI_Long)39L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(logbook_parameters_instance,
		Qprefer_native_logbook);
    SVREF(logbook_parameters_instance,FIX((SI_Long)39L)) = new_value;
    if ( !EQ(old_value,new_value) && 
	    system_table_installed_p(logbook_parameters_instance) &&  
	    !TRUEP(initializing_qm))
	note_native_logbook_preference_changed(Qprefer_native,new_value);
    return VALUES_1(new_value);
}

static Object Qinclude_date_in_logbook_messages;  /* include-date-in-logbook-messages */

static Object Qinclude_date;       /* include-date */

/* PUT-INCLUDE-DATE-IN-LOGBOOK-MESSAGES */
Object put_include_date_in_logbook_messages(logbook_parameters_instance,
	    new_value,initializing_qm)
    Object logbook_parameters_instance, new_value, initializing_qm;
{
    Object old_value;

    x_note_fn_call(116,5);
    old_value = ISVREF(logbook_parameters_instance,(SI_Long)40L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(logbook_parameters_instance,
		Qinclude_date_in_logbook_messages);
    SVREF(logbook_parameters_instance,FIX((SI_Long)40L)) = new_value;
    if ( !EQ(old_value,new_value) && 
	    system_table_installed_p(logbook_parameters_instance) &&  
	    !TRUEP(initializing_qm))
	note_native_logbook_preference_changed(Qinclude_date,new_value);
    return VALUES_1(new_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Message_board_parameters, Qmessage_board_parameters);

static Object Qprefer_native_message_board;  /* prefer-native-message-board */

/* PUT-PREFER-NATIVE-MESSAGE-BOARD */
Object put_prefer_native_message_board(message_board_parameters_instance,
	    new_value,initializing_qm)
    Object message_board_parameters_instance, new_value, initializing_qm;
{
    Object old_value;

    x_note_fn_call(116,6);
    old_value = ISVREF(message_board_parameters_instance,(SI_Long)28L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(message_board_parameters_instance,
		Qprefer_native_message_board);
    SVREF(message_board_parameters_instance,FIX((SI_Long)28L)) = new_value;
    if ( !EQ(old_value,new_value) && 
	    system_table_installed_p(message_board_parameters_instance) && 
	     !TRUEP(initializing_qm))
	note_native_message_board_preference_changed(Qprefer_native,new_value);
    return VALUES_1(new_value);
}

static Object Qinclude_date_in_messages;  /* include-date-in-messages */

/* PUT-INCLUDE-DATE-IN-MESSAGES */
Object put_include_date_in_messages(message_board_parameters_instance,
	    new_value,initializing_qm)
    Object message_board_parameters_instance, new_value, initializing_qm;
{
    Object old_value;

    x_note_fn_call(116,7);
    old_value = ISVREF(message_board_parameters_instance,(SI_Long)29L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(message_board_parameters_instance,
		Qinclude_date_in_messages);
    SVREF(message_board_parameters_instance,FIX((SI_Long)29L)) = new_value;
    if ( !EQ(old_value,new_value) && 
	    system_table_installed_p(message_board_parameters_instance) && 
	     !TRUEP(initializing_qm))
	note_native_message_board_preference_changed(Qinclude_date,new_value);
    return VALUES_1(new_value);
}

static Object Qinitial_width_of_message_board;  /* initial-width-of-message-board */

/* PUT-WIDTH-OF-MESSAGE-BOARD-WHERE-SLOT-IS-ABSENT */
Object put_width_of_message_board_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,8);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qinitial_width_of_message_board);
    SVREF(frame,FIX((SI_Long)22L)) = slot_value;
    return VALUES_1(Nil);
}

static Object Qinitial_height_of_message_board;  /* initial-height-of-message-board */

/* PUT-HEIGHT-OF-MESSAGE-BOARD-WHERE-SLOT-IS-ABSENT */
Object put_height_of_message_board_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,9);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qinitial_height_of_message_board);
    SVREF(frame,FIX((SI_Long)23L)) = slot_value;
    return VALUES_1(Nil);
}

static Object Qmargin_for_pages;   /* margin-for-pages */

/* PUT-LEFT-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT */
Object put_left_margin_for_pages_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,10);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qmargin_for_pages);
    SVREF(frame,FIX((SI_Long)24L)) = slot_value;
    return VALUES_1(Nil);
}

/* PUT-TOP-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT */
Object put_top_margin_for_pages_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,11);
    return VALUES_1(Nil);
}

/* PUT-RIGHT-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT */
Object put_right_margin_for_pages_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,12);
    return VALUES_1(Nil);
}

/* PUT-BOTTOM-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT */
Object put_bottom_margin_for_pages_where_slot_is_absent(frame,slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(116,13);
    return VALUES_1(Nil);
}

static Object Qwidth_for_pages;    /* width-for-pages */

/* PUT-WIDTH-FOR-PAGES */
Object put_width_for_pages(logbook_parameters_instance,new_value,
	    initializing_qm)
    Object logbook_parameters_instance, new_value, initializing_qm;
{
    SI_Long temp, svref_new_value;

    x_note_fn_call(116,14);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(logbook_parameters_instance,Qwidth_for_pages);
    temp = MIN((SI_Long)1000L,IFIX(new_value));
    svref_new_value = MAX((SI_Long)50L,temp);
    ISVREF(logbook_parameters_instance,(SI_Long)22L) = FIX(svref_new_value);
    if (system_table_installed_p(logbook_parameters_instance) &&  
	    !TRUEP(initializing_qm))
	update_message_format_for_books_per_logbook_parameters();
    return VALUES_1(ISVREF(logbook_parameters_instance,(SI_Long)22L));
}

/* PUT-MARGIN-FOR-PAGES */
Object put_margin_for_pages(logbook_parameters_instance,new_value,
	    initializing_qm)
    Object logbook_parameters_instance, new_value, initializing_qm;
{
    SI_Long temp, svref_new_value;

    x_note_fn_call(116,15);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(logbook_parameters_instance,Qmargin_for_pages);
    temp = MIN((SI_Long)25L,IFIX(new_value));
    svref_new_value = MAX((SI_Long)0L,temp);
    ISVREF(logbook_parameters_instance,(SI_Long)24L) = FIX(svref_new_value);
    if (system_table_installed_p(logbook_parameters_instance) &&  
	    !TRUEP(initializing_qm))
	update_message_format_for_books_per_logbook_parameters();
    return VALUES_1(ISVREF(logbook_parameters_instance,(SI_Long)24L));
}

/* PUT-INITIAL-WIDTH-OF-MESSAGE-BOARD */
Object put_initial_width_of_message_board(message_board_parameters_instance,
	    new_value,initializing_qm)
    Object message_board_parameters_instance, new_value, initializing_qm;
{
    SI_Long temp, svref_new_value;

    x_note_fn_call(116,16);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(message_board_parameters_instance,
		Qinitial_width_of_message_board);
    temp = MIN((SI_Long)1000L,IFIX(new_value));
    svref_new_value = MAX((SI_Long)50L,temp);
    ISVREF(message_board_parameters_instance,(SI_Long)22L) = 
	    FIX(svref_new_value);
    if (system_table_installed_p(message_board_parameters_instance) &&  
	    !TRUEP(initializing_qm))
	update_message_format_for_message_board_per_message_board_parameters();
    return VALUES_1(ISVREF(message_board_parameters_instance,(SI_Long)22L));
}

/* INSTALL-SYSTEM-TABLE-FOR-LOGBOOK-PARAMETERS */
Object install_system_table_for_logbook_parameters(logbook_parameters)
    Object logbook_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,17);
    PUSH_SPECIAL_WITH_SYMBOL(Logbook_parameters,Qlogbook_parameters,logbook_parameters,
	    0);
      result = update_message_format_for_books_per_logbook_parameters();
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-LOGBOOK-PARAMETERS */
Object deinstall_system_table_for_logbook_parameters(logbook_parameters)
    Object logbook_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,18);
    PUSH_SPECIAL_WITH_SYMBOL(Logbook_parameters,Qlogbook_parameters,logbook_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qmessage_format_for_books;  /* message-format-for-books */

static Object Qminimum_format_width_for_text_cell;  /* minimum-format-width-for-text-cell */

/* UPDATE-MESSAGE-FORMAT-FOR-BOOKS-PER-LOGBOOK-PARAMETERS */
Object update_message_format_for_books_per_logbook_parameters()
{
    x_note_fn_call(116,19);
    return change_standard_format_frame_slot(Qmessage_format_for_books,
	    Qminimum_format_width_for_text_cell,
	    FIXNUM_MINUS(ISVREF(Logbook_parameters,(SI_Long)22L),
	    ISVREF(Logbook_parameters,(SI_Long)24L)));
}

/* INSTALL-SYSTEM-TABLE-FOR-MESSAGE-BOARD-PARAMETERS */
Object install_system_table_for_message_board_parameters(message_board_parameters)
    Object message_board_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,20);
    PUSH_SPECIAL_WITH_SYMBOL(Message_board_parameters,Qmessage_board_parameters,message_board_parameters,
	    0);
      result = update_message_format_for_message_board_per_message_board_parameters();
    POP_SPECIAL();
    return result;
}

static Object Qmessage_format_for_message_board;  /* message-format-for-message-board */

static Object Qmessage_board;      /* message-board */

static Object Qworkspace_margin;   /* workspace-margin */

/* UPDATE-MESSAGE-FORMAT-FOR-MESSAGE-BOARD-PER-MESSAGE-BOARD-PARAMETERS */
Object update_message_format_for_message_board_per_message_board_parameters()
{
    Object temp;

    x_note_fn_call(116,21);
    temp = ISVREF(Message_board_parameters,(SI_Long)22L);
    return change_standard_format_frame_slot(Qmessage_format_for_message_board,
	    Qminimum_format_width_for_text_cell,FIXNUM_MINUS(temp,
	    get_slot_init_form(2,Qmessage_board,Qworkspace_margin)));
}

static Object Qlogbook_page;       /* logbook-page */

/* POST-MESSAGE-IN-BOOK */
Object post_message_in_book(block,book)
    Object block, book;
{
    Object top_edge_for_block, last_page_qm, temp, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_maxmin_fl_, page, svref_new_value;
    Object gensymed_symbol_4, workstation, ab_loop_list_;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, current_workstation_context;
    Object type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, current_page;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(116,22);
    SAVE_STACK();
    top_edge_for_block = Nil;
    last_page_qm = Nil;
    temp = ISVREF(book,(SI_Long)20L);
    last_page_qm = CAR(temp);
    temp_1 =  !TRUEP(last_page_qm);
    if (temp_1);
    else
	temp_1 =  !TRUEP(same_gensym_date_p(ISVREF(last_page_qm,
		(SI_Long)30L),Gensym_time));
    if (temp_1);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(last_page_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loopvar__1 = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
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
	gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	ab_loopvar__1 = gensymed_symbol;
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    ab_loopvar_ = ab_loopvar__1;
	}
	else
	    ab_loopvar_ = FIXNUM_MAX(ab_loopvar_,ab_loopvar__1);
	goto next_loop;
      end_loop:
	gensymed_symbol_1 = IFIX(ab_loopvar_);
	goto end_1;
	gensymed_symbol_1 = IFIX(Qnil);
      end_1:;
	gensymed_symbol_2 = IFIX(ISVREF(Logbook_parameters,(SI_Long)35L));
	top_edge_for_block = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(top_edge_for_block);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(last_page_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(last_page_qm,(SI_Long)17L));
	temp_1 = FIXNUM_GT(temp,FIX(gensymed_symbol_1 - gensymed_symbol_2));
    }
    if (temp_1) {
	page = make_workspace(6,Qlogbook_page,Nil,Nil,
		ISVREF(Logbook_parameters,(SI_Long)24L),
		ISVREF(Logbook_parameters,(SI_Long)22L),
		ISVREF(Logbook_parameters,(SI_Long)23L));
	ISVREF(page,(SI_Long)28L) = book;
	svref_new_value = slot_value_cons_1(page,ISVREF(book,(SI_Long)20L));
	ISVREF(book,(SI_Long)20L) = svref_new_value;
      next_loop_1:
	gensymed_symbol = ISVREF(book,(SI_Long)21L);
	gensymed_symbol_4 = add1(gensymed_symbol);
	if (CAS_SVREF(book,(SI_Long)21L,gensymed_symbol,gensymed_symbol_4))
	    goto end_2;
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol_4 = Qnil;
      end_2:
	ISVREF(page,(SI_Long)29L) = gensymed_symbol_4;
	svref_new_value = Gensym_time;
	ISVREF(page,(SI_Long)30L) = svref_new_value;
	temp = add_running_head_elements(book,page);
	top_edge_for_block = FIXNUM_ADD(temp,ISVREF(Logbook_parameters,
		(SI_Long)35L));
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(use_native_logbook_p(ISVREF(workstation,(SI_Long)1L)))) {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = workstation;
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			11);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  10);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    9);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      8);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				7);
			  temp = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  6);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    5);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
				      (SI_Long)2L);
			      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				      4);
				current_workstation_detail_pane = 
					detail_pane(Current_workstation_window);
				PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					3);
				  current_g2_user_mode_qm = 
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  2);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    1);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      0);
					add_page_to_display_of_book(page,
						book,
						Current_workstation_detail_pane);
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
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	}
	goto next_loop_2;
      end_loop_2:;
	prune_logbook_pages_to_maximum(book);
	current_page = page;
    }
    else
	current_page = last_page_qm;
    gensymed_symbol = ISVREF(current_page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(current_page,(SI_Long)17L));
    add_to_workspace(6,block,current_page,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2),top_edge_for_block,T,T);
    append_message_to_all_native_logbooks(block);
    RESTORE_STACK();
    return VALUES_1(current_page);
}

static Object string_constant;     /* "" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qdown_arrow_button;  /* down-arrow-button */

static Object Qbutton_action_qm;   /* button-action? */

static Object Qdo_arrow_action;    /* do-arrow-action */

static Object Qbutton_action_data_qm;  /* button-action-data? */

static Object Qup_arrow_button;    /* up-arrow-button */

static Object string_constant_1;   /* "Page ~d" */

/* ADD-RUNNING-HEAD-ELEMENTS */
Object add_running_head_elements(book,page)
    Object book, page;
{
    Object temp, title_heading, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, day, month, year, date_heading, down_arrow, up_arrow;
    Object page_number_heading, workspace_margin, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_maxmin_fl_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, top_edge_for_elements;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    Declare_special(5);
    Object result;

    x_note_fn_call(116,23);
    temp = ISVREF(book,(SI_Long)23L);
    if (temp);
    else
	temp = string_constant;
    title_heading = make_running_head(copy_text_string(temp));
    if (ISVREF(Logbook_parameters,(SI_Long)40L))
	temp = copy_text_string(string_constant);
    else {
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
		  if (System_is_running)
		      result = decode_gensym_time(Gensym_time);
		  else
		      result = get_decoded_real_time();
		  MVS_6(result,temp,temp,temp,day,month,year);
		  print_decoded_date(day,month,year);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    date_heading = make_running_head(temp);
    down_arrow = make_button(1,Qdown_arrow_button);
    set_slot_value_function(down_arrow,Qbutton_action_qm,Qdo_arrow_action,Nil);
    set_slot_value_function(down_arrow,Qbutton_action_data_qm,
	    slot_value_list_2(down_arrow,T),Nil);
    up_arrow = make_button(1,Qup_arrow_button);
    set_slot_value_function(up_arrow,Qbutton_action_qm,Qdo_arrow_action,Nil);
    set_slot_value_function(up_arrow,Qbutton_action_data_qm,
	    slot_value_list_2(up_arrow,Nil),Nil);
    page_number_heading = make_page_number(tformat_text_string(2,
	    string_constant_1,ISVREF(page,(SI_Long)29L)));
    workspace_margin = ISVREF(page,(SI_Long)17L);
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    top_edge_for_elements = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(title_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    add_to_workspace(4,title_heading,page,FIX(gensymed_symbol_1 - 
	    gensymed_symbol_2),FIX(top_edge_for_elements));
    gensymed_symbol = ISVREF(title_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)7L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_4 = (SI_Long)1L;
    gensymed_symbol_3 = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol = ISVREF(date_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(date_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_4 = (SI_Long)1L;
    gensymed_symbol_3 = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    add_to_workspace(4,date_heading,page,FIX(MAX(gensymed_symbol_1,
	    gensymed_symbol_2)),FIX(top_edge_for_elements));
    gensymed_symbol = ISVREF(date_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)7L;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(page,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = IFIX(workspace_margin);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol = ISVREF(down_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(down_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_4 = (SI_Long)5L;
    gensymed_symbol = ISVREF(up_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_5 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(up_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_6 = IFIX(gensymed_symbol);
    gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6;
    gensymed_symbol_6 = (SI_Long)8L;
    gensymed_symbol = ISVREF(page_number_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_7 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(page_number_heading,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_8 = IFIX(gensymed_symbol);
    gensymed_symbol_7 = gensymed_symbol_7 - gensymed_symbol_8;
    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4 + 
	    gensymed_symbol_5 + gensymed_symbol_6 + gensymed_symbol_7;
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    add_to_workspace(4,down_arrow,page,FIX(MAX(gensymed_symbol_1,
	    gensymed_symbol_2)),FIX(top_edge_for_elements));
    gensymed_symbol = ISVREF(down_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)5L;
    add_to_workspace(4,up_arrow,page,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2),FIX(top_edge_for_elements));
    gensymed_symbol = ISVREF(up_arrow,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)8L;
    add_to_workspace(4,page_number_heading,page,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2),FIX(top_edge_for_elements));
    gensymed_symbol = ACCESS_ONCE(ISVREF(page,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loopvar__1 = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    ab_loopvar__1 = gensymed_symbol;
    if (ab_loop_maxmin_fl_) {
	ab_loop_maxmin_fl_ = Nil;
	ab_loopvar_ = ab_loopvar__1;
    }
    else
	ab_loopvar_ = FIXNUM_MAX(ab_loopvar_,ab_loopvar__1);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_image_plane_for_button, Qcurrent_image_plane_for_button);

/* DO-ARROW-ACTION */
Object do_arrow_action(arrow,forward_qm)
    Object arrow, forward_qm;
{
    Object page, book, image_plane, pane, image_planes_with_pages_in_pane;
    Object stack_of_pages, temp, first_image_plane_displaying_page;
    Object first_page_displayed, ll, l, ab_loop_list_, ab_loop_list__1;
    Object ab_loop_iter_flag_;

    x_note_fn_call(116,24);
    page = get_workspace_if_any(arrow);
    book = ISVREF(page,(SI_Long)28L);
    image_plane = Current_image_plane_for_button;
    pane = ISVREF(image_plane,(SI_Long)2L);
    image_planes_with_pages_in_pane = 
	    get_image_planes_with_pages_in_pane(pane,book,T);
    stack_of_pages = ISVREF(book,(SI_Long)20L);
    temp = CDR(image_planes_with_pages_in_pane);
    first_image_plane_displaying_page = CAR(temp);
    first_page_displayed = ISVREF(first_image_plane_displaying_page,
	    (SI_Long)5L);
    temp = forward_qm ? stack_of_pages : last(stack_of_pages,_);
    if (EQ(CAR(temp),page));
    else if (forward_qm) {
	ll = Nil;
	l = stack_of_pages;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(CAR(l),first_page_displayed)) {
	    if (IFIX(length(ll)) < 
		    IFIX(length(image_planes_with_pages_in_pane)) >>  -  - 
		    (SI_Long)1L)
		rotate_logbook_pages(2,pane,T);
	    else {
		page = Nil;
		ab_loop_list_ = ll;
		image_plane = Nil;
		ab_loop_list__1 = image_planes_with_pages_in_pane;
		ab_loop_iter_flag_ = T;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		page = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ab_loop_iter_flag_) {
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_1;
		}
		else {
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_1;
		}
		temp = CDR(ab_loop_list__1);
		image_plane = CAR(temp);
		transform_image(10,image_plane,page,Nil,Nil,Nil,Nil,Nil,
			Nil,Nil,Nil);
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:
		goto end_1;
	      end_1:;
	    }
	    goto end_2;
	}
	ll = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
      end_2:;
    }
    else {
	l = stack_of_pages;
      next_loop_2:
	if ( !TRUEP(l))
	    goto end_loop_2;
	if (EQ(CAR(l),first_page_displayed)) {
	    if (IFIX(length(CDR(l))) < 
		    IFIX(length(image_planes_with_pages_in_pane)) >>  -  - 
		    (SI_Long)1L)
		rotate_logbook_pages(2,pane,Nil);
	    else {
		page = Nil;
		ab_loop_list_ = CDR(l);
		image_plane = Nil;
		ab_loop_list__1 = image_planes_with_pages_in_pane;
		ab_loop_iter_flag_ = T;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		page = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ab_loop_iter_flag_) {
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		}
		else {
		    ab_loop_list__1 = CDDR(ab_loop_list__1);
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		}
		temp = CDR(ab_loop_list__1);
		image_plane = CAR(temp);
		transform_image(10,image_plane,page,Nil,Nil,Nil,Nil,Nil,
			Nil,Nil,Nil);
		ab_loop_iter_flag_ = Nil;
		goto next_loop_3;
	      end_loop_3:
		goto end_3;
	      end_3:;
	    }
	    goto end_4;
	}
	l = M_CDR(l);
	goto next_loop_2;
      end_loop_2:
      end_4:;
    }
    return reclaim_gensym_list_1(image_planes_with_pages_in_pane);
}

/* ROTATE-LIST-OF-IMAGE-PLANES */
Object rotate_list_of_image_planes(list_of_image_planes)
    Object list_of_image_planes;
{
    Object image_plane, ab_loop_list_, list_of_workspaces, ab_loopvar_;
    Object ab_loopvar__1, l, workspace, temp;

    x_note_fn_call(116,25);
    image_plane = Nil;
    ab_loop_list_ = list_of_image_planes;
    list_of_workspaces = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = gensym_cons_1(ISVREF(image_plane,(SI_Long)5L),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	list_of_workspaces = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    l = list_of_image_planes;
    workspace = Nil;
    ab_loop_list_ = list_of_workspaces;
  next_loop_1:
    if ( !TRUEP(l))
	goto end_loop_1;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    workspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDR(l);
    if (temp);
    else
	temp = list_of_image_planes;
    transform_image(10,CAR(temp),workspace,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    l = M_CDR(l);
    goto next_loop_1;
  end_loop_1:;
    reclaim_gensym_list_1(list_of_workspaces);
    return VALUES_1(Qnil);
}

/* ROTATE-LOGBOOK-PAGES */
Object rotate_logbook_pages varargs_1(int, n)
{
    Object pane;
    Object backwards_qm, image_plane, ab_loop_list_, workspace_qm;
    Object list_of_image_planes, ab_loopvar_, ab_loopvar__1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(116,26);
    INIT_ARGS_nonrelocating();
    pane = REQUIRED_ARG_nonrelocating();
    backwards_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
    workspace_qm = Nil;
    list_of_image_planes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	ab_loopvar__1 = gensym_cons_1(image_plane,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    list_of_image_planes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if ( !TRUEP(backwards_qm))
	list_of_image_planes = nreverse(list_of_image_planes);
    rotate_list_of_image_planes(list_of_image_planes);
    reclaim_gensym_list_1(list_of_image_planes);
    return VALUES_1(Qnil);
}

/* GET-IMAGE-PLANES-WITH-PAGES-IN-PANE */
Object get_image_planes_with_pages_in_pane(pane,book,decreasing_qm)
    Object pane, book, decreasing_qm;
{
    Object page_numbers_and_image_planes_so_far_in_order, image_plane;
    Object ab_loop_list_, workspace_qm, page_number_qm, sub_class_bit_vector;
    Object listed_page_number_and_image_plane, ll, l, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(116,27);
    page_numbers_and_image_planes_so_far_in_order = Nil;
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
    workspace_qm = Nil;
    page_number_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Page_class_description,
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
    page_number_qm = (temp ? EQ(ISVREF(workspace_qm,(SI_Long)28L),book) : 
	    TRUEP(Nil)) ? ISVREF(workspace_qm,(SI_Long)29L) : Nil;
    if (page_number_qm) {
	listed_page_number_and_image_plane = gensym_list_2(page_number_qm,
		image_plane);
	ll = Nil;
	l = page_numbers_and_image_planes_so_far_in_order;
      next_loop_1:
	temp =  !TRUEP(l);
	if (temp);
	else if (decreasing_qm) {
	    temp_1 = CAR(l);
	    temp = NUM_GT(page_number_qm,temp_1);
	}
	else {
	    temp_1 = CAR(l);
	    temp = NUM_LT(page_number_qm,temp_1);
	}
	if (temp) {
	    M_CDDR(listed_page_number_and_image_plane) = l;
	    if (ll)
		M_CDDR(ll) = listed_page_number_and_image_plane;
	    else
		page_numbers_and_image_planes_so_far_in_order = 
			listed_page_number_and_image_plane;
	    goto end_1;
	}
	ll = l;
	l = CDDR(l);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(page_numbers_and_image_planes_so_far_in_order);
    return VALUES_1(Qnil);
}

static Object Qshow_operator_logbook_in_this_window_qm;  /* show-operator-logbook-in-this-window? */

static Object Qdefault_workspace_frame_style;  /* default-workspace-frame-style */

static Object Qabove;              /* above */

/* ADD-PAGE-TO-DISPLAY-OF-BOOK */
Object add_page_to_display_of_book(page,book,pane)
    Object page, book, pane;
{
    Object gensym_window, workstation, g2_window_qm;
    Object maximum_number_of_pages_to_show, x_offset_for_next_page;
    Object y_offset_for_next_page, x_offset_for_logbook, y_offset_for_logbook;
    Object number_of_pages_to_shed_at_limit;
    Object page_numbers_and_image_planes_in_order, image_plane;
    Object gensymed_symbol, x_in_workspace, y_in_workspace, temp;
    Object previous_image_plane, image_x_scale, image_y_scale, l;
    Object ab_loop_iter_flag_, trailer, workspaces_to_shift, ab_loopvar_;
    Object ab_loopvar__1, workspaces_to_remove_from_display, ab_loopvar__2;
    Object image_planes_to_delete_in_bottom_up_order_so_far, ab_loop_list_, ll;
    Object ab_loop_it_, workspace, existing_image_plane, ab_loop_list__1;
    SI_Long number_of_pages_on_image_planes, x_in_window, y_in_window;
    SI_Long screen_offset_between_pages, temp_1, temp_2, number_to_delete, i;
    SI_Long number_of_workspaces_to_keep, new_position_index;
    SI_Long old_position_index;
    char temp_3;

    x_note_fn_call(116,28);
    gensym_window = ISVREF(pane,(SI_Long)2L);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    g2_window_qm = ISVREF(workstation,(SI_Long)25L);
    if (g2_window_qm &&  
	    !TRUEP(get_lookup_slot_value_given_default(g2_window_qm,
	    Qshow_operator_logbook_in_this_window_qm,T)))
	return VALUES_1(Nil);
    maximum_number_of_pages_to_show = ISVREF(Logbook_parameters,(SI_Long)33L);
    x_offset_for_next_page = ISVREF(Logbook_parameters,(SI_Long)25L);
    y_offset_for_next_page = ISVREF(Logbook_parameters,(SI_Long)26L);
    x_offset_for_logbook = ISVREF(Logbook_parameters,(SI_Long)27L);
    y_offset_for_logbook = ISVREF(Logbook_parameters,(SI_Long)28L);
    number_of_pages_to_shed_at_limit = ISVREF(Logbook_parameters,(SI_Long)34L);
    page_numbers_and_image_planes_in_order = 
	    get_image_planes_with_pages_in_pane(pane,book,T);
    number_of_pages_on_image_planes = 
	    IFIX(length(page_numbers_and_image_planes_in_order)) >>  -  - 
	    (SI_Long)1L;
    if (number_of_pages_on_image_planes == (SI_Long)0L) {
	image_plane = get_available_image_plane(pane,
		lookup_frame_description_reference_of_frame_style(Qdefault_workspace_frame_style,
		Qdefault_workspace_frame_style),Nil);
	x_in_window = IFIX(x_offset_for_next_page) > (SI_Long)0L ? 
		IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),
		x_offset_for_logbook)) : 
		IFIX(FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		x_offset_for_logbook));
	y_in_window = IFIX(FIXNUM_NEGATE(y_offset_for_next_page)) >= 
		(SI_Long)0L ? IFIX(FIXNUM_ADD(ISVREF(image_plane,
		(SI_Long)7L),FIXNUM_NEGATE(y_offset_for_logbook))) : 
		IFIX(FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		FIXNUM_NEGATE(y_offset_for_logbook)));
	if (IFIX(x_offset_for_next_page) > (SI_Long)0L) {
	    gensymed_symbol = ISVREF(page,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    x_in_workspace = gensymed_symbol;
	}
	else {
	    gensymed_symbol = ISVREF(page,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    x_in_workspace = gensymed_symbol;
	}
	if (IFIX(FIXNUM_NEGATE(y_offset_for_next_page)) >= (SI_Long)0L) {
	    gensymed_symbol = ISVREF(page,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    y_in_workspace = gensymed_symbol;
	}
	else {
	    gensymed_symbol = ISVREF(page,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    y_in_workspace = gensymed_symbol;
	}
	transform_image(10,image_plane,page,Nil,Nil,Nil,Nil,x_in_workspace,
		y_in_workspace,FIX(x_in_window),FIX(y_in_window));
	require_that_image_plane_be_visible(1,image_plane);
    }
    else if (number_of_pages_on_image_planes < 
	    IFIX(maximum_number_of_pages_to_show)) {
	temp = CDR(page_numbers_and_image_planes_in_order);
	previous_image_plane = CAR(temp);
	image_x_scale = ISVREF(previous_image_plane,(SI_Long)11L);
	image_y_scale = ISVREF(previous_image_plane,(SI_Long)12L);
	image_plane = new_get_available_image_plane(pane,
		ISVREF(previous_image_plane,(SI_Long)10L),Qabove,
		previous_image_plane);
	screen_offset_between_pages = (SI_Long)3L;
	x_in_window = IFIX(ISVREF(previous_image_plane,(SI_Long)15L)) + 
		screen_offset_between_pages + IFIX(x_offset_for_next_page);
	y_in_window = IFIX(ISVREF(previous_image_plane,(SI_Long)16L)) + 
		screen_offset_between_pages - IFIX(y_offset_for_next_page);
	gensymed_symbol = ISVREF(page,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	x_in_workspace = gensymed_symbol;
	gensymed_symbol = ISVREF(page,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	y_in_workspace = gensymed_symbol;
	transform_image(10,image_plane,page,image_x_scale,image_y_scale,
		Nil,Nil,x_in_workspace,y_in_workspace,FIX(x_in_window),
		FIX(y_in_window));
	require_that_image_plane_be_visible(1,image_plane);
    }
    else {
	temp_1 = number_of_pages_on_image_planes - (SI_Long)1L;
	temp_2 = number_of_pages_on_image_planes - 
		IFIX(maximum_number_of_pages_to_show);
	temp_2 = MAX(temp_2,IFIX(number_of_pages_to_shed_at_limit));
	temp_2 = MIN(temp_1,temp_2);
	number_to_delete = MAX((SI_Long)0L,temp_2);
	l = page_numbers_and_image_planes_in_order;
	i = (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (i > number_to_delete)
	    goto end_loop;
	ab_loop_iter_flag_ = Nil;
	l = CDDR(l);
	goto next_loop;
      end_loop:
	trailer = page_numbers_and_image_planes_in_order;
	number_of_workspaces_to_keep = (IFIX(length(l)) >>  -  - 
		(SI_Long)1L) - (SI_Long)1L;
	i = (SI_Long)1L;
	workspaces_to_shift = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	workspaces_to_remove_from_display = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__1 = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(trailer))
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (i <= number_of_workspaces_to_keep) {
	    temp = CDR(trailer);
	    ab_loopvar__1 = gensym_cons_1(ISVREF(CAR(temp),(SI_Long)5L),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		workspaces_to_shift = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	else {
	    temp = CDR(trailer);
	    ab_loopvar__1 = gensym_cons_1(ISVREF(CAR(temp),(SI_Long)5L),Nil);
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__1;
	    else
		workspaces_to_remove_from_display = ab_loopvar__1;
	    ab_loopvar__2 = ab_loopvar__1;
	}
	ab_loop_iter_flag_ = Nil;
	trailer = CDDR(trailer);
	goto next_loop_1;
      end_loop_1:
	temp = CDR(l);
	transform_image(10,CAR(temp),page,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
	image_planes_to_delete_in_bottom_up_order_so_far = Nil;
	image_plane = Nil;
	ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	image_plane = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ll = page_numbers_and_image_planes_in_order;
	ab_loop_it_ = Nil;
      next_loop_3:
	if ( !TRUEP(ll))
	    goto end_loop_3;
	if (EQ(ll,l))
	    goto end_loop_3;
	temp = CDR(ll);
	ab_loop_it_ = EQ(CAR(temp),image_plane) ? T : Nil;
	if (ab_loop_it_) {
	    temp_3 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	ll = CDDR(ll);
	goto next_loop_3;
      end_loop_3:
	temp_3 = TRUEP(Qnil);
      end_1:;
	if (temp_3)
	    image_planes_to_delete_in_bottom_up_order_so_far = 
		    gensym_cons_1(image_plane,
		    image_planes_to_delete_in_bottom_up_order_so_far);
	goto next_loop_2;
      end_loop_2:
	image_plane = Nil;
	ab_loop_list_ = image_planes_to_delete_in_bottom_up_order_so_far;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	image_plane = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_image_plane(image_plane);
	goto next_loop_4;
      end_loop_4:;
	reclaim_gensym_list_1(image_planes_to_delete_in_bottom_up_order_so_far);
	workspace = Nil;
	ab_loop_list_ = workspaces_to_shift;
	ll = CDDR(l);
	ab_loop_iter_flag_ = T;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	workspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    ll = CDDR(ll);
	temp = CDR(ll);
	transform_image(10,CAR(temp),workspace,Nil,Nil,Nil,Nil,Nil,Nil,Nil,
		Nil);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_5;
      end_loop_5:;
	reclaim_gensym_list_1(workspaces_to_shift);
	reclaim_gensym_list_1(workspaces_to_remove_from_display);
    }
    reclaim_gensym_list_1(page_numbers_and_image_planes_in_order);
    if (ISVREF(Logbook_parameters,(SI_Long)38L)) {
	if (ISVREF(Logbook_parameters,(SI_Long)38L)) {
	    page_numbers_and_image_planes_in_order = 
		    get_image_planes_with_pages_in_pane(pane,book,T);
	    image_plane = Nil;
	    ab_loop_list_ = page_numbers_and_image_planes_in_order;
	    new_position_index = (SI_Long)0L;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    temp = CDR(ab_loop_list_);
	    image_plane = CAR(temp);
	  next_loop_6:
	    existing_image_plane = Nil;
	    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
	    old_position_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop_7:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_7;
	    existing_image_plane = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_iter_flag_))
		old_position_index = old_position_index + (SI_Long)1L;
	    if (EQ(existing_image_plane,image_plane)) {
		revise_pane(pane,image_plane,FIX(new_position_index - 
			old_position_index),Nil);
		goto end_2;
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_7;
	  end_loop_7:
	  end_2:;
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    temp = CDR(ab_loop_list_);
	    image_plane = CAR(temp);
	    new_position_index = new_position_index + (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:
	    reclaim_gensym_list_1(page_numbers_and_image_planes_in_order);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PRUNE-LOGBOOK-PAGES-TO-MAXIMUM */
Object prune_logbook_pages_to_maximum(book)
    Object book;
{
    Object temp, temp_1, maximum_number_of_pages_to_keep, page, ab_loop_list_;
    Object ab_loop_iter_flag_;
    SI_Long count_1;
    char temp_2;

    x_note_fn_call(116,29);
    temp = ISVREF(Logbook_parameters,(SI_Long)33L);
    temp_1 = ISVREF(Logbook_parameters,(SI_Long)37L);
    maximum_number_of_pages_to_keep = FIXNUM_MAX(temp,temp_1);
  next_loop:
    page = Nil;
    ab_loop_list_ = ISVREF(book,(SI_Long)20L);
    count_1 = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    page = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	count_1 = count_1 + (SI_Long)1L;
    if (count_1 > IFIX(maximum_number_of_pages_to_keep)) {
	delete_frame(page);
	temp_2 = TRUEP(T);
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop:
    temp_2 = TRUEP(Qnil);
  end_1:;
    if ( !temp_2)
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* NEATLY-STACK-LOGBOOK-PAGES-IN-PANE */
Object neatly_stack_logbook_pages_in_pane(pane,book)
    Object pane, book;
{
    Object page_qm;
    SI_Long index_1;

    x_note_fn_call(116,30);
    hide_all_logbook_pages_in_pane(pane);
    if ( !TRUEP(use_native_logbook_p(ISVREF(pane,(SI_Long)2L)))) {
	index_1 = IFIX(FIXNUM_SUB1(ISVREF(Logbook_parameters,(SI_Long)33L)));
	page_qm = Nil;
      next_loop:
	if (index_1 < (SI_Long)0L)
	    goto end_loop;
	page_qm = nth(FIX(index_1),ISVREF(book,(SI_Long)20L));
	if (page_qm)
	    add_page_to_display_of_book(page_qm,book,pane);
	index_1 = index_1 - (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_logbook_qm, Qcurrent_logbook_qm);

/* SHOW-LOGBOOK-IN-G2-WINDOW */
Object show_logbook_in_g2_window(g2_window)
    Object g2_window;
{
    Object workstation_qm, gensym_window_qm, pane_qm;

    x_note_fn_call(116,31);
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    gensym_window_qm = workstation_qm ? ISVREF(workstation_qm,(SI_Long)1L) 
	    : Nil;
    pane_qm = gensym_window_qm ? detail_pane(gensym_window_qm) : Nil;
    if (pane_qm) {
	provide_current_logbook();
	if (use_native_logbook_p(gensym_window_qm))
	    show_native_logbook(gensym_window_qm);
	return neatly_stack_logbook_pages_in_pane(pane_qm,Current_logbook_qm);
    }
    else
	return VALUES_1(Nil);
}

/* HIDE-ALL-LOGBOOK-PAGES-IN-PANE */
Object hide_all_logbook_pages_in_pane(pane)
    Object pane;
{
    Object image_planes_to_delete, image_plane, ab_loop_list_, frame, symbol;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,32);
    image_planes_to_delete = Nil;
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(image_plane,(SI_Long)5L)) {
	frame = ISVREF(image_plane,(SI_Long)5L);
	symbol = Qlogbook_page;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(symbol,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	image_planes_to_delete = gensym_cons_1(image_plane,
		image_planes_to_delete);
    goto next_loop;
  end_loop:
    image_plane = Nil;
    ab_loop_list_ = image_planes_to_delete;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_image_plane(image_plane);
    goto next_loop_1;
  end_loop_1:;
    reclaim_gensym_list_1(image_planes_to_delete);
    return VALUES_1(Qnil);
}

/* HIDE-LOGBOOK-IN-G2-WINDOW */
Object hide_logbook_in_g2_window(g2_window)
    Object g2_window;
{
    Object workstation_qm, gensym_window_qm, pane_qm;

    x_note_fn_call(116,33);
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    gensym_window_qm = workstation_qm ? ISVREF(workstation_qm,(SI_Long)1L) 
	    : Nil;
    pane_qm = gensym_window_qm ? detail_pane(gensym_window_qm) : Nil;
    if (pane_qm) {
	hide_native_logbook(gensym_window_qm);
	return hide_all_logbook_pages_in_pane(pane_qm);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_message_board_qm, Qcurrent_message_board_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_serial_number_of_current_message_board, Qframe_serial_number_of_current_message_board);

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* CURRENT-MESSAGE-BOARD? */
Object current_message_board_qm()
{
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(116,34);
    if (Current_message_board_qm && 
	    Frame_serial_number_of_current_message_board) {
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Current_message_board_qm);
    else
	return VALUES_1(Nil);
}

static Object Qlogged_in;          /* logged-in */

/* PROVIDE-CURRENT-MESSAGE-BOARD */
Object provide_current_message_board()
{
    Object gensymed_symbol, xa, ya, frame_serial_number_setf_arg;
    Object frame_serial_number_of_current_message_board_new_value;
    Object message_board, workstation, ab_loop_list_, gensym_window;
    char temp;

    x_note_fn_call(116,35);
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
    message_board = Current_message_board_qm;
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in) && 
	    workspaces_can_be_shown_at_this_kb_level_p(message_board,
	    workstation)) {
	if (use_native_message_board_p(gensym_window))
	    ensure_native_message_board(gensym_window);
	else
	    show_message_board_in_window(gensym_window);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(message_board);
    return VALUES_1(Qnil);
}

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* SHOW-MESSAGE-BOARD-IN-WINDOW */
Object show_message_board_in_window(gensym_window)
    Object gensym_window;
{
    Object workstation, detail_pane_1, message_board, image_plane;
    Object ab_loop_list_, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(116,36);
    SAVE_STACK();
    if (current_message_board_qm()) {
	workstation = ISVREF(gensym_window,(SI_Long)2L);
	detail_pane_1 = detail_pane(gensym_window);
	message_board = Current_message_board_qm;
	if (detail_pane_1) {
	    image_plane = Nil;
	    ab_loop_list_ = ISVREF(message_board,(SI_Long)16L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    image_plane = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(image_plane,(SI_Long)2L),detail_pane_1)) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = workstation;
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			11);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  10);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    9);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      8);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				7);
			  temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  6);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    5);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
				      (SI_Long)2L);
			      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				      4);
				current_workstation_detail_pane = 
					detail_pane(Current_workstation_window);
				PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					3);
				  current_g2_user_mode_qm = 
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  2);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    1);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      0);
					SAVE_VALUES(put_workspace_on_pane_function(message_board,
						detail_pane_1,Qleft,Qtop,
						Nil,FIX((SI_Long)11L),Nil,
						Nil,Nil,Nil,Nil,Nil,Nil));
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
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* WORKSPACE-SHOW-OR-HIDE-HOOK */
Object workspace_show_or_hide_hook(workspace,gensym_window,show_p)
    Object workspace, gensym_window, show_p;
{
    x_note_fn_call(116,37);
    if (current_message_board_qm() && EQ(workspace,
	    Current_message_board_qm) && 
	    use_native_message_board_p(gensym_window)) {
	if (show_p) {
	    if (workspaces_can_be_shown_at_this_kb_level_p(workspace,
		    ISVREF(gensym_window,(SI_Long)2L)))
		show_native_message_board(gensym_window);
	}
	else
	    hide_native_message_board(gensym_window);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Next_serial_number_to_be_generated, Qnext_serial_number_to_be_generated);

DEFINE_VARIABLE_WITH_SYMBOL(Current_message_unix_time_qm, Qcurrent_message_unix_time_qm);

/* INCREMENT-MESSAGE-SERIAL-NUMBER */
Object increment_message_serial_number()
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(116,38);
    temp = Next_serial_number_to_be_generated;
  next_loop:
    gensymed_symbol = Next_serial_number_to_be_generated;
    gensymed_symbol_1 = add1(gensymed_symbol);
    if (CAS_SYMBOL(Qnext_serial_number_to_be_generated,gensymed_symbol,
	    gensymed_symbol_1))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
    Current_message_serial_number = temp;
    return VALUES_1(Current_message_serial_number);
}

static Object Qfloat_array;        /* float-array */

/* COMPUTE-CURRENT-MESSAGE-TIME */
Object compute_current_message_time()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(116,39);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
	aref_new_value = System_is_running ? 
		(double)IFIX(FIXNUM_MINUS(Gensym_time,
		Gensym_time_at_start)) + DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L) : g2ext_unix_time_as_float();
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* SIMPLE-ENCODE-DATE */
Object simple_encode_date(unix_time_mf_qm)
    Object unix_time_mf_qm;
{
    Object temp, day, month, year;
    Object result;

    x_note_fn_call(116,40);
    if (unix_time_mf_qm) {
	result = decode_unix_time_as_managed_float(unix_time_mf_qm);
	MVS_6(result,temp,temp,temp,day,month,year);
	return VALUES_1(FIX(IFIX(day) | IFIX(month) << (SI_Long)5L | 
		IFIX(year) << (SI_Long)14L));
    }
    else
	return VALUES_1(Nil);
}

/* SIMPLE-DECODE-DATE */
Object simple_decode_date(date)
    Object date;
{
    x_note_fn_call(116,41);
    return VALUES_3(FIX(IFIX(date) & (SI_Long)31L),FIX(IFIX(date) >>  -  - 
	    (SI_Long)5L & (SI_Long)15L),FIX(IFIX(date) >>  -  - 
	    (SI_Long)14L & (SI_Long)4095L));
}

static Object string_constant_2;   /* "#~d   " */

static Object string_constant_3;   /* "   " */

/* PRINT-MESSAGE-HEADER */
Object print_message_header(unix_time_mf,logbook_p)
    Object unix_time_mf, logbook_p;
{
    Object seconds, minutes, hours, day, month, year;
    Object result;

    x_note_fn_call(116,42);
    tformat(2,string_constant_2,Current_message_serial_number);
    result = decode_unix_time_as_managed_float(unix_time_mf);
    MVS_6(result,seconds,minutes,hours,day,month,year);
    if (logbook_p && ISVREF(Logbook_parameters,(SI_Long)40L) ||  
	    !TRUEP(logbook_p) && ISVREF(Message_board_parameters,(SI_Long)29L))
	print_decoded_time(seconds,minutes,hours,day,month,year);
    else
	print_decoded_time_of_day(seconds,minutes,hours);
    return tformat(1,string_constant_3);
}

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_parameters, Qlog_file_parameters);

static Object Qwhen_to_back_up_log_file;  /* when-to-back-up-log-file */

/* PUT-WHEN-TO-BACKUP-LOG-FILE-WHERE-SLOT-IS-ABSENT */
Object put_when_to_backup_log_file_where_slot_is_absent(log_file_parameters,
	    value)
    Object log_file_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,43);
    PUSH_SPECIAL_WITH_SYMBOL(Log_file_parameters,Qlog_file_parameters,log_file_parameters,
	    0);
      change_slot_value(3,Log_file_parameters,Qwhen_to_back_up_log_file,value);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qseconds;            /* seconds */

/* INITIALIZE-LOG-FILE-UPDATE-FOR-SLOT */
Object initialize_log_file_update_for_slot(message_count,interval_in_seconds)
    Object message_count, interval_in_seconds;
{
    x_note_fn_call(116,44);
    return slot_value_list_2(message_count,
	    slot_value_cons_1(interval_in_seconds,Qseconds));
}

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_outputting_qm, Qlog_file_outputting_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_writing_message_qm, Qlog_file_writing_message_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_string, Qlog_file_string);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_stream, Qlog_file_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_default_pathname_qm, Qlog_file_default_pathname_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_count, Qlog_file_count);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_message_count, Qlog_file_message_count);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_message_count_at_last_update, Qlog_file_message_count_at_last_update);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_time_at_last_update, Qlog_file_time_at_last_update);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_time_at_open, Qlog_file_time_at_open);

DEFINE_VARIABLE_WITH_SYMBOL(Log_file_pathnames, Qlog_file_pathnames);

Object Log_file_name_extension = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_log_file_name_prefix_length_qm, Qmaximum_log_file_name_prefix_length_qm);

/* INITIALIZE-MAXIMUM-LOG-FILE-NAME-PREFIX-LENGTH? */
Object initialize_maximum_log_file_name_prefix_length_qm()
{
    Object temp;

    x_note_fn_call(116,45);
    if (Maximum_file_name_length_qm) {
	temp = Maximum_file_name_length_qm;
	return minusn(3,temp,lengthw(Log_file_name_extension),
		FIX((SI_Long)4L));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_4;   /* "Log file is being ~Aabled." */

static Object string_constant_5;   /* "en" */

static Object string_constant_6;   /* "dis" */

static Object Qlog_file_enabled_qm;  /* log-file-enabled? */

/* PUT-LOG-FILE-ENABLED? */
Object put_log_file_enabled_qm(log_file_parameters_instance,new_value,
	    initializing_qm)
    Object log_file_parameters_instance, new_value, initializing_qm;
{
    Object temp;

    x_note_fn_call(116,46);
    if (system_table_installed_p(log_file_parameters_instance)) {
	if (initializing_qm ||  !TRUEP(new_value)) {
	    close_log_file();
	    temp = initializing_qm;
	    if (temp);
	    else
		temp = new_value;
	    reset_log_file_information(temp,Nil);
	}
	if (new_value)
	    create_log_file_default_pathname_if_necessary(ISVREF(log_file_parameters_instance,
		    (SI_Long)23L),Nil);
	Log_file_outputting_qm = new_value;
	if (new_value ||  !TRUEP(initializing_qm)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_4,
			new_value ? string_constant_5 : string_constant_6);
	    Suppress_warning_message_header_qm = Nil;
	}
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qlog_file_enabled_qm);
    SVREF(log_file_parameters_instance,FIX((SI_Long)22L)) = new_value;
    return VALUES_1(new_value);
}

static Object Qdirectory_for_log_files;  /* directory-for-log-files */

/* PUT-DIRECTORY-FOR-LOG-FILES */
Object put_directory_for_log_files(log_file_parameters_instance,new_value,
	    gensymed_symbol)
    Object log_file_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(116,47);
    if (system_table_installed_p(log_file_parameters_instance))
	create_log_file_default_pathname_if_necessary(new_value,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qdirectory_for_log_files);
    SVREF(log_file_parameters_instance,FIX((SI_Long)23L)) = new_value;
    return VALUES_1(new_value);
}

static Object Qroot_name_for_log_files;  /* root-name-for-log-files */

/* PUT-ROOT-NAME-FOR-LOG-FILES */
Object put_root_name_for_log_files(log_file_parameters_instance,new_value,
	    gensymed_symbol)
    Object log_file_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(116,48);
    if (system_table_installed_p(log_file_parameters_instance))
	create_log_file_default_pathname_if_necessary(Nil,new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qroot_name_for_log_files);
    SVREF(log_file_parameters_instance,FIX((SI_Long)24L)) = new_value;
    return VALUES_1(new_value);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qgensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object Qtformat_text_string;  /* tformat-text-string */

static Object string_constant_7;   /* "~a" */

/* CREATE-LOG-FILE-DEFAULT-PATHNAME-IF-NECESSARY */
Object create_log_file_default_pathname_if_necessary(new_directory_qm,
	    new_root_name_qm)
    Object new_directory_qm, new_root_name_qm;
{
    volatile Object new_directory_string_in_target_charset_qm;
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p, current_system_pathname_qm;
    Object root_name_qm;
    volatile Object root_name_in_target_charset_qm;
    volatile Object directory_pathname_qm;
    Object temp, log_file_directory_qm;
    volatile Object log_file_directory_in_target_charset_qm;
    Object new_value, result_from_body, gensymed_symbol, control_string;
    Object error_args, error_arg, ab_loop_list_, report_string;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(2);
    Object result;

    x_note_fn_call(116,49);
    SAVE_STACK();
    new_directory_string_in_target_charset_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(3)) {
	new_directory_string_in_target_charset_qm = new_directory_qm ? 
		convert_text_string_to_ascii_filename_as_much_as_possible(new_directory_qm) 
		: Nil;
	if ( !TRUEP(Log_file_default_pathname_qm) ||  
		!TRUEP(new_directory_string_in_target_charset_qm) && 
		ISVREF(Log_file_parameters,(SI_Long)23L) || 
		new_directory_string_in_target_charset_qm &&  
		!(ISVREF(Log_file_parameters,(SI_Long)23L) && 
		string_equalw(new_directory_string_in_target_charset_qm,
		ISVREF(Log_file_parameters,(SI_Long)23L))) || 
		new_root_name_qm &&  !(ISVREF(Log_file_parameters,
		(SI_Long)24L) && string_equalw(new_root_name_qm,
		ISVREF(Log_file_parameters,(SI_Long)24L)))) {
	    inside_handling_gensym_file_errors_scope_p = T;
	    gensym_file_error_occurred_p = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
		      0);
		if (PUSH_CATCH(Qgensym_file_error_catch_tag,2)) {
		    current_system_pathname_qm = Qunbound_in_protected_let;
		    root_name_qm = Qunbound_in_protected_let;
		    root_name_in_target_charset_qm = Qunbound_in_protected_let;
		    directory_pathname_qm = Qunbound_in_protected_let;
		    if (PUSH_UNWIND_PROTECT(1)) {
			current_system_pathname_qm = 
				Process_specific_system_pathname;
			temp = new_root_name_qm;
			if (temp);
			else
			    temp = ISVREF(Log_file_parameters,(SI_Long)24L);
			root_name_qm = temp;
			root_name_in_target_charset_qm = root_name_qm ? 
				convert_text_string_to_ascii_filename_as_much_as_possible(root_name_qm) 
				: Nil;
			if (new_directory_string_in_target_charset_qm) {
			    temp = 
				    gensym_file_as_directory(new_directory_string_in_target_charset_qm);
			    if (temp);
			    else
				temp = 
					gensym_parse_namestring_function(new_directory_string_in_target_charset_qm,
					Nil,Nil);
			    directory_pathname_qm = temp;
			}
			else if (new_root_name_qm) {
			    log_file_directory_qm = Qunbound_in_protected_let;
			    log_file_directory_in_target_charset_qm = 
				    Qunbound_in_protected_let;
			    if (PUSH_UNWIND_PROTECT(0)) {
				log_file_directory_qm = 
					ISVREF(Log_file_parameters,
					(SI_Long)23L);
				log_file_directory_in_target_charset_qm = 
					log_file_directory_qm ? 
					convert_text_string_to_ascii_filename_as_much_as_possible(log_file_directory_qm) 
					: Nil;
				if (log_file_directory_in_target_charset_qm) {
				    temp = 
					    gensym_file_as_directory(log_file_directory_in_target_charset_qm);
				    if (temp);
				    else
					temp = 
						gensym_parse_namestring_function(log_file_directory_in_target_charset_qm,
						Nil,Nil);
				}
				else if (Current_kb_pathname_qm)
				    temp = 
					    copy_gensym_pathname(Current_kb_pathname_qm);
				else if (current_system_pathname_qm)
				    temp = 
					    copy_gensym_pathname(current_system_pathname_qm);
				else
				    temp = Nil;
				SAVE_VALUES(VALUES_1(temp));
			    }
			    POP_UNWIND_PROTECT(0);
			    if (log_file_directory_in_target_charset_qm) {
				if ( 
					!EQ(log_file_directory_in_target_charset_qm,
					Qunbound_in_protected_let))
				    reclaim_text_string(log_file_directory_in_target_charset_qm);
			    }
			    CONTINUE_UNWINDING(0);
			    result = RESTORE_VALUES();
			    directory_pathname_qm = result;
			}
			else if (Current_kb_pathname_qm)
			    directory_pathname_qm = 
				    copy_gensym_pathname(Current_kb_pathname_qm);
			else if (current_system_pathname_qm)
			    directory_pathname_qm = 
				    copy_gensym_pathname(current_system_pathname_qm);
			else
			    directory_pathname_qm = Nil;
			if (directory_pathname_qm) {
			    reset_log_file_information(T,T);
			    if (root_name_in_target_charset_qm) {
				new_value = 
					gensym_make_pathname_with_copied_components(Nil,
					Nil,Nil,
					root_name_in_target_charset_qm,
					Log_file_name_extension,Nil,
					directory_pathname_qm);
				reclaim_pathname_or_string(Log_file_default_pathname_qm);
				if (text_string_p(new_value)) {
				    temp = gensym_pathname(new_value);
				    reclaim_text_string(new_value);
				    Log_file_default_pathname_qm = temp;
				}
				else
				    Log_file_default_pathname_qm = new_value;
				temp = Log_file_default_pathname_qm;
			    }
			    else
				temp = Nil;
			}
			else
			    temp = Nil;
			SAVE_VALUES(VALUES_1(temp));
		    }
		    POP_UNWIND_PROTECT(1);
		    if (directory_pathname_qm) {
			if ( !EQ(directory_pathname_qm,
				Qunbound_in_protected_let))
			    reclaim_gensym_pathname(directory_pathname_qm);
		    }
		    if (root_name_in_target_charset_qm) {
			if ( !EQ(root_name_in_target_charset_qm,
				Qunbound_in_protected_let))
			    reclaim_text_string(root_name_in_target_charset_qm);
		    }
		    CONTINUE_UNWINDING(1);
		    result = RESTORE_VALUES();
		    result_from_body = result;
		}
		else
		    result_from_body = CATCH_VALUES();
		POP_CATCH(2);
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
		    notify_user(2,string_constant_7,report_string);
		    reclaim_text_string(report_string);
		    SAVE_VALUES(VALUES_1(Nil));
		}
		else
		    SAVE_VALUES(VALUES_1(result_from_body));
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(3);
    if (new_directory_string_in_target_charset_qm) {
	if ( !EQ(new_directory_string_in_target_charset_qm,
		Qunbound_in_protected_let))
	    reclaim_text_string(new_directory_string_in_target_charset_qm);
    }
    CONTINUE_UNWINDING(3);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qwhen_to_close_log_file;  /* when-to-close-log-file */

/* PUT-WHEN-TO-CLOSE-LOG-FILE */
Object put_when_to_close_log_file(log_file_parameters_instance,new_value,
	    gensymed_symbol)
    Object log_file_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(116,50);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qwhen_to_close_log_file);
    SVREF(log_file_parameters_instance,FIX((SI_Long)26L)) = new_value;
    return VALUES_1(new_value);
}

/* PUT-WHEN-TO-BACK-UP-LOG-FILE */
Object put_when_to_back_up_log_file(log_file_parameters_instance,new_value,
	    gensymed_symbol)
    Object log_file_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(116,51);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qwhen_to_back_up_log_file);
    SVREF(log_file_parameters_instance,FIX((SI_Long)27L)) = new_value;
    return VALUES_1(new_value);
}

static Object Qmaximum_number_of_log_files;  /* maximum-number-of-log-files */

/* PUT-MAXIMUM-NUMBER-OF-LOG-FILES */
Object put_maximum_number_of_log_files(log_file_parameters_instance,
	    new_value,gensymed_symbol)
    Object log_file_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(116,52);
    if (system_table_installed_p(log_file_parameters_instance)) {
	if (new_value && FIXNUM_GT(Log_file_count,new_value))
	    Log_file_count = new_value;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(log_file_parameters_instance,
		Qmaximum_number_of_log_files);
    SVREF(log_file_parameters_instance,FIX((SI_Long)28L)) = new_value;
    return VALUES_1(new_value);
}

static Object Qcurrent_log_file;   /* current-log-file */

static Object string_constant_8;   /* "Error.  Could not open log file ~s: ~a." */

static Object string_constant_9;   /* "Error.  Could not open log file ~s." */

/* OPEN-LOG-FILE */
Object open_log_file(open_for_appending_qm)
    Object open_for_appending_qm;
{
    volatile Object log_file_string_in_target_charset;
    Object temp, error_text_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(116,53);
    SAVE_STACK();
    log_file_string_in_target_charset = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	log_file_string_in_target_charset = 
		convert_text_string_to_ascii_filename_as_much_as_possible(Log_file_string);
	if (Log_file_string) {
	    Log_file_stream = open_for_appending_qm ? 
		    g2_stream_open_for_appending_handling_file_errors(log_file_string_in_target_charset,
		    T) : 
		    g2_stream_open_for_output_handling_file_errors(log_file_string_in_target_charset);
	    if (g2_stream_p(Log_file_stream)) {
		if ( !TRUEP(open_for_appending_qm)) {
		    temp = Log_file_parameters;
		    change_slot_value(3,temp,Qcurrent_log_file,
			    copy_text_string(Log_file_string));
		}
		if ( !TRUEP(open_for_appending_qm))
		    Log_file_time_at_open = Gensym_time;
		SAVE_VALUES(VALUES_1(T));
	    }
	    else {
		error_text_qm = most_recent_file_operation_status_as_text();
		if (error_text_qm) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)1L),
				string_constant_8,Log_file_string,
				error_text_qm);
		    Suppress_warning_message_header_qm = Nil;
		}
		else {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)1L),
				string_constant_9,Log_file_string);
		    Suppress_warning_message_header_qm = Nil;
		}
		reclaim_text_string(error_text_qm);
		SAVE_VALUES(VALUES_1(Nil));
	    }
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (log_file_string_in_target_charset) {
	if ( !EQ(log_file_string_in_target_charset,Qunbound_in_protected_let))
	    reclaim_text_string(log_file_string_in_target_charset);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* RESET-LOG-FILE-INFORMATION */
Object reset_log_file_information(clear_current_file_information_qm,
	    clear_all_file_information_qm)
    Object clear_current_file_information_qm, clear_all_file_information_qm;
{
    Object log_file_pathname, ab_loop_list_;

    x_note_fn_call(116,54);
    if (clear_current_file_information_qm || clear_all_file_information_qm) {
	if (Log_file_string) {
	    Log_file_string = Nil;
	    change_slot_value(3,Log_file_parameters,Qcurrent_log_file,Nil);
	}
	Log_file_message_count = FIX((SI_Long)0L);
    }
    if (clear_all_file_information_qm) {
	Log_file_count = FIX((SI_Long)0L);
	log_file_pathname = Nil;
	ab_loop_list_ = Log_file_pathnames;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	log_file_pathname = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_gensym_pathname(log_file_pathname);
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(Log_file_pathnames);
	if (SIMPLE_VECTOR_P(Log_file_default_pathname_qm) && 
		EQ(ISVREF(Log_file_default_pathname_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	    reclaim_gensym_pathname(Log_file_default_pathname_qm);
	Log_file_default_pathname_qm = Nil;
	Log_file_pathnames = Nil;
    }
    Log_file_time_at_last_update = Gensym_time;
    Log_file_message_count_at_last_update = Log_file_message_count;
    return VALUES_1(Log_file_message_count_at_last_update);
}

/* INSTALL-SYSTEM-TABLE-FOR-LOG-FILE-PARAMETERS */
Object install_system_table_for_log_file_parameters(log_file_parameters)
    Object log_file_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,55);
    PUSH_SPECIAL_WITH_SYMBOL(Log_file_parameters,Qlog_file_parameters,log_file_parameters,
	    0);
      close_log_file();
      reset_log_file_information(ISVREF(Log_file_parameters,(SI_Long)22L),Nil);
      create_log_file_default_pathname_if_necessary(ISVREF(Log_file_parameters,
	      (SI_Long)23L),Nil);
      Log_file_outputting_qm = ISVREF(Log_file_parameters,(SI_Long)22L);
      result = VALUES_1(Log_file_outputting_qm);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-LOG-FILE-PARAMETERS */
Object deinstall_system_table_for_log_file_parameters(log_file_parameters)
    Object log_file_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(116,56);
    PUSH_SPECIAL_WITH_SYMBOL(Log_file_parameters,Qlog_file_parameters,log_file_parameters,
	    0);
      close_log_file();
      reset_log_file_information(Nil,T);
      Log_file_outputting_qm = Nil;
      result = VALUES_1(Log_file_outputting_qm);
    POP_SPECIAL();
    return result;
}

/* CLOSE-LOG-FILE */
Object close_log_file()
{
    x_note_fn_call(116,57);
    if (Log_file_stream) {
	g2_stream_close(Log_file_stream);
	Log_file_stream = Nil;
	return VALUES_1(Log_file_stream);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-LOG-FILE-IF-NECESSARY */
Object update_log_file_if_necessary()
{
    Object message_count_and_interval_qm, temp, temp_1;
    char temp_2;

    x_note_fn_call(116,58);
    message_count_and_interval_qm = ISVREF(Log_file_parameters,(SI_Long)26L);
    temp = FIRST(message_count_and_interval_qm);
    if (CONSP(temp) ? TRUEP(SECOND(message_count_and_interval_qm)) : 
	    TRUEP(FIRST(message_count_and_interval_qm))) {
	temp_1 = Log_file_message_count;
	message_count_and_interval_qm = ISVREF(Log_file_parameters,
		(SI_Long)26L);
	temp = FIRST(message_count_and_interval_qm);
	temp_2 = FIXNUM_GE(temp_1,CONSP(temp) ? 
		SECOND(message_count_and_interval_qm) : 
		FIRST(message_count_and_interval_qm));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	close_log_file();
	return reset_log_file_information(T,Nil);
    }
    else {
	message_count_and_interval_qm = ISVREF(Log_file_parameters,
		(SI_Long)26L);
	temp = FIRST(message_count_and_interval_qm);
	temp = CONSP(temp) ? FIRST(message_count_and_interval_qm) : 
		SECOND(message_count_and_interval_qm);
	if (FIRST(temp)) {
	    temp_1 = FIXNUM_MINUS(Gensym_time,Log_file_time_at_open);
	    message_count_and_interval_qm = ISVREF(Log_file_parameters,
		    (SI_Long)26L);
	    temp = FIRST(message_count_and_interval_qm);
	    temp = CONSP(temp) ? FIRST(message_count_and_interval_qm) : 
		    SECOND(message_count_and_interval_qm);
	    temp_2 = FIXNUM_GE(temp_1,FIRST(temp));
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    close_log_file();
	    return reset_log_file_information(T,Nil);
	}
	else {
	    message_count_and_interval_qm = ISVREF(Log_file_parameters,
		    (SI_Long)27L);
	    temp = FIRST(message_count_and_interval_qm);
	    if (CONSP(temp) ? TRUEP(SECOND(message_count_and_interval_qm)) 
		    : TRUEP(FIRST(message_count_and_interval_qm))) {
		temp_1 = FIXNUM_MINUS(Log_file_message_count,
			Log_file_message_count_at_last_update);
		message_count_and_interval_qm = ISVREF(Log_file_parameters,
			(SI_Long)27L);
		temp = FIRST(message_count_and_interval_qm);
		temp_2 = FIXNUM_GE(temp_1,CONSP(temp) ? 
			SECOND(message_count_and_interval_qm) : 
			FIRST(message_count_and_interval_qm));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		close_log_file();
		return reset_log_file_information(Nil,Nil);
	    }
	    else {
		message_count_and_interval_qm = ISVREF(Log_file_parameters,
			(SI_Long)27L);
		temp = FIRST(message_count_and_interval_qm);
		temp = CONSP(temp) ? FIRST(message_count_and_interval_qm) :
			 SECOND(message_count_and_interval_qm);
		if (FIRST(temp)) {
		    temp_1 = FIXNUM_MINUS(Gensym_time,
			    Log_file_time_at_last_update);
		    message_count_and_interval_qm = 
			    ISVREF(Log_file_parameters,(SI_Long)27L);
		    temp = FIRST(message_count_and_interval_qm);
		    temp = CONSP(temp) ? 
			    FIRST(message_count_and_interval_qm) : 
			    SECOND(message_count_and_interval_qm);
		    temp_2 = FIXNUM_GE(temp_1,FIRST(temp));
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    close_log_file();
		    return reset_log_file_information(Nil,Nil);
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

/* GET-NEXT-LOG-FILE */
Object get_next_log_file()
{
    Object file_root_name_qm;
    volatile Object file_root_name_in_target_charset_qm;
    volatile Object validated_pathname_qm;
    Object next_file_index_qm, new_value;
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p;
    volatile Object validated_filename_prefix_string_qm;
    volatile Object validated_pathname_name;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, temp_2, cdr_arg, cdr_new_value, result_from_body;
    Object gensymed_symbol, control_string, error_args, error_arg;
    Object ab_loop_list_, report_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(7);
    Object result;

    x_note_fn_call(116,59);
    SAVE_STACK();
    file_root_name_qm = Qunbound_in_protected_let;
    file_root_name_in_target_charset_qm = Qunbound_in_protected_let;
    validated_pathname_qm = Qunbound_in_protected_let;
    next_file_index_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(2)) {
	file_root_name_qm = ISVREF(Log_file_parameters,(SI_Long)24L);
	file_root_name_in_target_charset_qm = file_root_name_qm ? 
		convert_text_string_to_ascii_filename_as_much_as_possible(file_root_name_qm) 
		: Nil;
	validated_pathname_qm = Nil;
	next_file_index_qm = Nil;
	if (file_root_name_in_target_charset_qm) {
	    next_file_index_qm = 
		    find_next_log_file_index(file_root_name_in_target_charset_qm);
	    temp = TRUEP(next_file_index_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (nth(FIXNUM_SUB1(next_file_index_qm),Log_file_pathnames)) {
		validated_pathname_qm = 
			nth(FIXNUM_SUB1(next_file_index_qm),
			Log_file_pathnames);
		new_value = gensym_namestring_as_text_string(1,
			validated_pathname_qm);
		if (text_string_p(Log_file_string))
		    reclaim_text_string(Log_file_string);
		else if (SIMPLE_VECTOR_P(Log_file_string) && 
			EQ(ISVREF(Log_file_string,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
		    reclaim_gensym_pathname(Log_file_string);
		Log_file_string = new_value;
		Log_file_count = next_file_index_qm;
	    }
	    else if (Log_file_default_pathname_qm) {
		inside_handling_gensym_file_errors_scope_p = T;
		gensym_file_error_occurred_p = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
			6);
		  PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
			  5);
		    if (PUSH_CATCH(Qgensym_file_error_catch_tag,1)) {
			validated_filename_prefix_string_qm = 
				Qunbound_in_protected_let;
			validated_pathname_name = Qunbound_in_protected_let;
			if (PUSH_UNWIND_PROTECT(0)) {
			    validated_filename_prefix_string_qm = 
				    Maximum_log_file_name_prefix_length_qm 
				    && 
				    FIXNUM_LE(length(ISVREF(Log_file_default_pathname_qm,
				    (SI_Long)4L)),
				    Maximum_log_file_name_prefix_length_qm) 
				    ? 
				    copy_text_string(ISVREF(Log_file_default_pathname_qm,
				    (SI_Long)4L)) : 
				    text_string_substring(ISVREF(Log_file_default_pathname_qm,
				    (SI_Long)4L),FIX((SI_Long)0L),
				    Maximum_log_file_name_prefix_length_qm);
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      twrite_general_string(validated_filename_prefix_string_qm);
				      twrite(next_file_index_qm);
				      validated_pathname_name = 
					      copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			    temp_1 = validated_pathname_name;
			    temp_2 = ISVREF(Log_file_default_pathname_qm,
				    (SI_Long)5L);
			    if (temp_2);
			    else
				temp_2 = Log_file_name_extension;
			    validated_pathname_qm = 
				    gensym_make_pathname_with_copied_components(Nil,
				    Nil,Nil,temp_1,temp_2,Nil,
				    Log_file_default_pathname_qm);
			}
			POP_UNWIND_PROTECT(0);
			if (validated_pathname_name) {
			    if ( !EQ(validated_pathname_name,
				    Qunbound_in_protected_let))
				reclaim_text_string(validated_pathname_name);
			}
			if (validated_filename_prefix_string_qm) {
			    if ( !EQ(validated_filename_prefix_string_qm,
				    Qunbound_in_protected_let))
				reclaim_text_string(validated_filename_prefix_string_qm);
			}
			CONTINUE_UNWINDING(0);
			if (validated_pathname_qm) {
			    if (Log_file_pathnames) {
				cdr_arg = last(Log_file_pathnames,_);
				cdr_new_value = 
					gensym_cons_1(validated_pathname_qm,
					Nil);
				M_CDR(cdr_arg) = cdr_new_value;
			    }
			    else
				Log_file_pathnames = 
					gensym_cons_1(validated_pathname_qm,
					Nil);
			    new_value = gensym_namestring_as_text_string(1,
				    validated_pathname_qm);
			    if (text_string_p(Log_file_string))
				reclaim_text_string(Log_file_string);
			    else if (SIMPLE_VECTOR_P(Log_file_string) && 
				    EQ(ISVREF(Log_file_string,(SI_Long)0L),
				    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
				reclaim_gensym_pathname(Log_file_string);
			    Log_file_string = new_value;
			    Log_file_count = next_file_index_qm;
			    result_from_body = Log_file_count;
			}
			else
			    result_from_body = Nil;
		    }
		    else
			result_from_body = CATCH_VALUES();
		    POP_CATCH(1);
		    if (Gensym_file_error_occurred_p) {
			gensymed_symbol = result_from_body;
			control_string = CAR(gensymed_symbol);
			error_args = CDR(gensymed_symbol);
			temp_2 = SYMBOL_FUNCTION(Qtformat_text_string);
			temp_2 = APPLY_2(temp_2,control_string,error_args);
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
			report_string = temp_2;
			notify_user(2,string_constant_7,report_string);
			reclaim_text_string(report_string);
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	}
	if (validated_pathname_qm)
	    SAVE_VALUES(VALUES_1(T));
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(2);
    if (file_root_name_in_target_charset_qm) {
	if ( !EQ(file_root_name_in_target_charset_qm,
		Qunbound_in_protected_let))
	    reclaim_text_string(file_root_name_in_target_charset_qm);
    }
    CONTINUE_UNWINDING(2);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FIND-NEXT-LOG-FILE-INDEX */
Object find_next_log_file_index(pathname_prefix_string)
    Object pathname_prefix_string;
{
    x_note_fn_call(116,60);
    if (ISVREF(Log_file_parameters,(SI_Long)28L))
	return add1(chestnut_modf_function(Log_file_count,
		ISVREF(Log_file_parameters,(SI_Long)28L)));
    else
	return VALUES_1(FIXNUM_ADD1(Log_file_count));
}

/* WRITE-MESSAGE-TO-LOG-STREAM */
Object write_message_to_log_stream(message_text_string,stream)
    Object message_text_string, stream;
{
    Object log_file_message_count_new_value;

    x_note_fn_call(116,61);
    if (write_text_string_to_stream(message_text_string,stream)) {
	log_file_message_count_new_value = FIXNUM_ADD1(Log_file_message_count);
	Log_file_message_count = log_file_message_count_new_value;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_10;  /* "Error in opening Log File.  Invalid directory." */

static Object string_constant_11;  /* "Write to Log File ~a failed.  The file is being ~
				    *              closed."
				    */

/* WRITE-MESSAGE-TO-LOG-FILE */
Object write_message_to_log_file(message_text)
    Object message_text;
{
    x_note_fn_call(116,62);
    if ( !TRUEP(Log_file_outputting_qm) || Log_file_writing_message_qm)
	return VALUES_1(Nil);
    Log_file_writing_message_qm = T;
    if ( !TRUEP(Log_file_stream)) {
	if ( !TRUEP(Log_file_string)) {
	    if (get_next_log_file())
		open_log_file(Nil);
	    else {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(2,FIX((SI_Long)1L),string_constant_10);
		Suppress_warning_message_header_qm = Nil;
	    }
	}
	else
	    open_log_file(T);
	if ( !TRUEP(Log_file_stream)) {
	    reset_log_file_information(Nil,Nil);
	    Log_file_outputting_qm = Nil;
	    Log_file_writing_message_qm = Nil;
	    return VALUES_1(Nil);
	}
    }
    if ( !TRUEP(write_message_to_log_stream(message_text,Log_file_stream)) 
	    ||  !TRUEP(g2_stream_terpri(Log_file_stream)) ||  
	    !TRUEP(g2_stream_terpri(Log_file_stream))) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_11,
		    Log_file_string);
	Suppress_warning_message_header_qm = Nil;
	close_log_file();
	reset_log_file_information(Nil,Nil);
	Log_file_outputting_qm = Nil;
	Log_file_writing_message_qm = Nil;
	return VALUES_1(Nil);
    }
    update_log_file_if_necessary();
    Log_file_writing_message_qm = Nil;
    return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_logbook_serial_number_qm, Qcurrent_logbook_serial_number_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Allow_user_defined_logbook_handlers_p, Qallow_user_defined_logbook_handlers_p);

DEFINE_VARIABLE_WITH_SYMBOL(Currently_posting_message_on_logbook_p, Qcurrently_posting_message_on_logbook_p);

/* CURRENT-LOGBOOK? */
Object current_logbook_qm()
{
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(116,63);
    if (Current_logbook_qm && Current_logbook_serial_number_qm) {
	gensymed_symbol = ISVREF(Current_logbook_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(Current_logbook_qm) ? 
		EQ(ISVREF(Current_logbook_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(Current_logbook_serial_number_qm))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(Current_logbook_serial_number_qm,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(Current_logbook_serial_number_qm);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(Current_logbook_serial_number_qm),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Current_logbook_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_save_module_list, Qg2_save_module_list);

static Object string_constant_12;  /* "message: ~A" */

static Object Qtrace_outputting_to_file_qm;  /* trace-outputting-to-file? */

static Object Qtracing_file_stream;  /* tracing-file-stream */

static Object Qtracing_file_string;  /* tracing-file-string */

static Object Qadd_to_logbook;     /* add-to-logbook */

static Object string_constant_13;  /* "Error when writing to tracing file ~a.  The file is being closed." */

/* POST-MESSAGE-ON-LOGBOOK */
Object post_message_on_logbook(text_line,from_message_board_p)
    Object text_line, from_message_board_p;
{
    Object current_message_unix_time_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_text_line, currently_posting_message_on_logbook_p;
    Object tracing_file_string_if_error_qm, message_1, logbook_page;
    SI_Long bv16_length, temp, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(116,64);
    if (Send_logbook_messages_to_console_p && from_message_board_p &&  
	    !TRUEP(Send_messages_to_console_p))
	notify_user_at_console(2,string_constant_12,text_line);
    provide_current_logbook();
    current_message_unix_time_qm = compute_current_message_time();
    PUSH_SPECIAL_WITH_SYMBOL(Current_message_unix_time_qm,Qcurrent_message_unix_time_qm,current_message_unix_time_qm,
	    5);
      current_wide_string_list = Qdo_not_use;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	      4);
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	temp = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		print_message_header(Current_message_unix_time_qm,T);
		twrite_general_string(text_line);
		message_text_line = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      currently_posting_message_on_logbook_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(Currently_posting_message_on_logbook_p,Qcurrently_posting_message_on_logbook_p,currently_posting_message_on_logbook_p,
	      0);
	tracing_file_string_if_error_qm = Nil;
	if (registered_and_active_logbook_handling_procedure_p() && 
		pass_loop_check_for_logbook_handling_procedure_p() && 
		Allow_user_defined_logbook_handlers_p && 
		invoke_user_defined_logbook_handling_procedure(message_text_line));
	else {
	    if (get_lookup_slot_value_given_default(Debugging_parameters,
		    Qtrace_outputting_to_file_qm,Nil)) {
		if ( 
			!TRUEP(g2_stream_write_line_for_trace_to_file(message_text_line,
			get_lookup_slot_value_given_default(Debugging_parameters,
			Qtracing_file_stream,Nil))) ||  
			!TRUEP(g2_stream_terpri(get_lookup_slot_value_given_default(Debugging_parameters,
			Qtracing_file_stream,Nil))) ||  
			!TRUEP(g2_stream_terpri(get_lookup_slot_value_given_default(Debugging_parameters,
			Qtracing_file_stream,Nil)))) {
		    tracing_file_string_if_error_qm = 
			    copy_text_string(get_lookup_slot_value_given_default(Debugging_parameters,
			    Qtracing_file_string,Nil));
		    close_tracing_file();
		}
	    }
	    if (Log_file_outputting_qm)
		write_message_to_log_file(message_text_line);
	    message_1 = make_message(3,message_text_line,Nil,
		    Qmessage_format_for_books);
	    if (is_g2_save_module_flag_set())
		G2_save_module_list = 
			gensym_cons_1(Current_message_serial_number,
			G2_save_module_list);
	    inform_ui_client_interfaces_of_general_update(Qadd_to_logbook,
		    message_1);
	    temp = IFIX(ISVREF(message_1,(SI_Long)5L)) | (SI_Long)524288L;
	    ISVREF(message_1,(SI_Long)5L) = FIX(temp);
	    logbook_page = post_message_in_book(message_1,Current_logbook_qm);
	    if (tracing_file_string_if_error_qm) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(3,FIX((SI_Long)1L),string_constant_13,
			    tracing_file_string_if_error_qm);
		reclaim_text_string(tracing_file_string_if_error_qm);
	    }
	    force_workspace_drawing(logbook_page);
	}
	reclaim_managed_simple_float_array_of_length_1(Current_message_unix_time_qm);
	result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* G2-STREAM-WRITE-LINE-FOR-TRACE-TO-FILE */
Object g2_stream_write_line_for_trace_to_file(text_string,stream)
    Object text_string, stream;
{
    x_note_fn_call(116,65);
    if (write_text_string_to_stream(text_string,stream))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

/* MESSAGE-SERIAL-NUMBER-FUNCTION */
Object message_serial_number_function(message_1)
    Object message_1;
{
    x_note_fn_call(116,66);
    return VALUES_1(ISVREF(message_1,(SI_Long)20L));
}

static Object Qsnapshots_of_blocks_related_to_message;  /* snapshots-of-blocks-related-to-message */

/* RECLAIM-SNAPSHOTS-OF-BLOCKS-RELATED-TO-MESSAGE-VALUE */
Object reclaim_snapshots_of_blocks_related_to_message_value(snapshots,
	    message_1)
    Object snapshots, message_1;
{
    x_note_fn_call(116,67);
    reclaim_list_of_block_snapshots(snapshots);
    set_non_savable_lookup_slot_value(message_1,
	    Qsnapshots_of_blocks_related_to_message,Nil);
    return VALUES_1(Nil);
}

/* SNAPSHOTS-OF-VALID-BLOCKS-RELATED-TO-MESSAGE */
Object snapshots_of_valid_blocks_related_to_message(message_1)
    Object message_1;
{
    Object snapshots, snapshot, ab_loop_list_, ab_loop_it_, deceased_blocks_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(116,68);
    snapshots = get_lookup_slot_value_given_default(message_1,
	    Qsnapshots_of_blocks_related_to_message,Nil);
    snapshot = Nil;
    ab_loop_list_ = snapshots;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    snapshot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ =  !TRUEP(snapshot_of_block_valid_p(snapshot)) ? T : Nil;
    if (ab_loop_it_) {
	deceased_blocks_qm = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    deceased_blocks_qm = Qnil;
  end_1:;
    if (deceased_blocks_qm) {
	snapshot = Nil;
	ab_loop_list_ = snapshots;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	snapshot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (snapshot_of_block_valid_p(snapshot)) {
	    ab_loopvar__2 = slot_value_cons_1(snapshot,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	else
	    reclaim_snapshot_of_block_1(snapshot);
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	set_non_savable_lookup_slot_value(message_1,
		Qsnapshots_of_blocks_related_to_message,temp);
	reclaim_slot_value_list_1(snapshots);
    }
    return get_lookup_slot_value_given_default(message_1,
	    Qsnapshots_of_blocks_related_to_message,Nil);
}

Object The_type_description_of_inform_message_information = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_inform_message_informations, Qchain_of_available_inform_message_informations);

DEFINE_VARIABLE_WITH_SYMBOL(Inform_message_information_count, Qinform_message_information_count);

Object Chain_of_available_inform_message_informations_vector = UNBOUND;

/* INFORM-MESSAGE-INFORMATION-STRUCTURE-MEMORY-USAGE */
Object inform_message_information_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(116,69);
    temp = Inform_message_information_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INFORM-MESSAGE-INFORMATION-COUNT */
Object outstanding_inform_message_information_count()
{
    Object def_structure_inform_message_information_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(116,70);
    gensymed_symbol = IFIX(Inform_message_information_count);
    def_structure_inform_message_information_variable = 
	    Chain_of_available_inform_message_informations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_inform_message_information_variable))
	goto end_loop;
    def_structure_inform_message_information_variable = 
	    ISVREF(def_structure_inform_message_information_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INFORM-MESSAGE-INFORMATION-1 */
Object reclaim_inform_message_information_1(inform_message_information)
    Object inform_message_information;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(116,71);
    inline_note_reclaim_cons(inform_message_information,Nil);
    structure_being_reclaimed = inform_message_information;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_task_to_remove_inform_message(ISVREF(inform_message_information,
	      (SI_Long)0L));
      SVREF(inform_message_information,FIX((SI_Long)0L)) = Nil;
      reclaim_task_to_unhighlight_inform_message(ISVREF(inform_message_information,
	      (SI_Long)1L));
      SVREF(inform_message_information,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(inform_message_information,
	      (SI_Long)4L));
      SVREF(inform_message_information,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_inform_message_informations_vector,
	    IFIX(Current_thread_index));
    SVREF(inform_message_information,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_inform_message_informations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = inform_message_information;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INFORM-MESSAGE-INFORMATION */
Object reclaim_structure_for_inform_message_information(inform_message_information)
    Object inform_message_information;
{
    x_note_fn_call(116,72);
    return reclaim_inform_message_information_1(inform_message_information);
}

/* MAKE-PERMANENT-INFORM-MESSAGE-INFORMATION-STRUCTURE-INTERNAL */
Object make_permanent_inform_message_information_structure_internal()
{
    Object def_structure_inform_message_information_variable, the_array;
    Object defstruct_g2_inform_message_information_variable;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(116,73);
    def_structure_inform_message_information_variable = Nil;
    atomic_incff_symval(Qinform_message_information_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_inform_message_information_variable = the_array;
	def_structure_inform_message_information_variable = 
		defstruct_g2_inform_message_information_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_inform_message_information_variable);
}

/* MAKE-INFORM-MESSAGE-INFORMATION-1 */
Object make_inform_message_information_1(urgency_of_inform_message_qm,
	    origin_of_inform_message_qm,
	    frame_serial_number_of_origin_of_inform_message_qm,
	    destination_of_inform_message_qm,duration_of_inform_message_qm,
	    timestamp_of_inform_message_qm)
    Object urgency_of_inform_message_qm, origin_of_inform_message_qm;
    Object frame_serial_number_of_origin_of_inform_message_qm;
    Object destination_of_inform_message_qm, duration_of_inform_message_qm;
    Object timestamp_of_inform_message_qm;
{
    Object def_structure_inform_message_information_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(116,74);
    def_structure_inform_message_information_variable = 
	    ISVREF(Chain_of_available_inform_message_informations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_inform_message_information_variable) {
	svref_arg_1 = Chain_of_available_inform_message_informations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_inform_message_information_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_inform_message_information_variable = 
		make_permanent_inform_message_information_structure_internal();
    inline_note_allocate_cons(def_structure_inform_message_information_variable,
	    Nil);
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)2L)) = urgency_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)3L)) = origin_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)4L)) = 
	    frame_serial_number_of_origin_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)5L)) = destination_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)6L)) = duration_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)7L)) = timestamp_of_inform_message_qm;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)0L)) = Nil;
    SVREF(def_structure_inform_message_information_variable,
	    FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_inform_message_information_variable);
}

/* RECLAIM-INFORM-MESSAGE-INFORMATION?-VALUE */
Object reclaim_inform_message_information_qm_value(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(116,75);
    if (value)
	reclaim_inform_message_information_1(value);
    return VALUES_1(Nil);
}

/* RECLAIM-TASK-TO-REMOVE-INFORM-MESSAGE */
Object reclaim_task_to_remove_inform_message(task_qm)
    Object task_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(116,76);
    if (task_qm) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(Structure_being_reclaimed,(SI_Long)0L);
	if (CAS_SVREF(Structure_being_reclaimed,(SI_Long)0L,
		gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    return VALUES_1(T);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-TASK-TO-UNHIGHLIGHT-INFORM-MESSAGE */
Object reclaim_task_to_unhighlight_inform_message(task_qm)
    Object task_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(116,77);
    if (task_qm) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(Structure_being_reclaimed,(SI_Long)1L);
	if (CAS_SVREF(Structure_being_reclaimed,(SI_Long)1L,
		gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    return VALUES_1(T);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-ORIGIN-OF-MESSAGE-IF-APPROPRIATE */
Object get_origin_of_message_if_appropriate(message_1)
    Object message_1;
{
    Object sub_class_bit_vector, inform_message_information_qm;
    Object origin_of_message_qm, frame_serial_number, gensymed_symbol_3, xa;
    Object ya;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(116,78);
    sub_class_bit_vector = ISVREF(ISVREF(message_1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
    if (temp) {
	inform_message_information_qm = ISVREF(message_1,(SI_Long)19L);
	origin_of_message_qm = inform_message_information_qm ? 
		ISVREF(inform_message_information_qm,(SI_Long)3L) : Nil;
	if (origin_of_message_qm) {
	    inform_message_information_qm = ISVREF(message_1,(SI_Long)19L);
	    frame_serial_number = inform_message_information_qm ? 
		    ISVREF(inform_message_information_qm,(SI_Long)4L) : Nil;
	    gensymed_symbol_3 = ISVREF(origin_of_message_qm,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(origin_of_message_qm) ? 
		    EQ(ISVREF(origin_of_message_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol_3) ? 
			IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(frame_serial_number))
		temp = FIXNUMP(gensymed_symbol_3) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol_3) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_3))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol_3);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	    }
	    if ( !temp)
		return VALUES_1(origin_of_message_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object New_message_highlight_color = UNBOUND;

static Object array_constant_1;    /* # */

static Object Qmessage;            /* message */

static Object Qhighlight_color;    /* highlight-color */

/* MAKE-MESSAGE */
Object make_message varargs_1(int, n)
{
    Object text_line_qm, message_class_qm, text_box_format_name_qm;
    Object inform_message_qm, urgency_qm, duration_qm, origin_frame_qm;
    Object destination_qm, do_not_reformat_qm, temp, temp_1, message_1;
    Object svref_new_value;
    SI_Long svref_new_value_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(116,79);
    INIT_ARGS_nonrelocating();
    text_line_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    message_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_box_format_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    inform_message_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    urgency_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    duration_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    origin_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    destination_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_reformat_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = text_line_qm;
    if (temp);
    else
	temp = copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)0L));
    temp_1 = message_class_qm;
    if (temp_1);
    else
	temp_1 = Qmessage;
    message_1 = make_free_text_box(6,temp,temp_1,text_box_format_name_qm,
	    Nil,Nil,do_not_reformat_qm);
    svref_new_value = Current_message_serial_number;
    ISVREF(message_1,(SI_Long)20L) = svref_new_value;
    svref_new_value = simple_encode_date(Current_message_unix_time_qm);
    ISVREF(message_1,(SI_Long)21L) = svref_new_value;
    if (inform_message_qm) {
	svref_new_value_1 = IFIX(ISVREF(message_1,(SI_Long)5L)) | 
		(SI_Long)524288L;
	ISVREF(message_1,(SI_Long)5L) = FIX(svref_new_value_1);
	temp_1 = origin_frame_qm ? 
		copy_frame_serial_number(ISVREF(origin_frame_qm,
		(SI_Long)3L)) : Nil;
	svref_new_value = make_inform_message_information_1(urgency_qm,
		origin_frame_qm,temp_1,destination_qm,duration_qm,Gensym_time);
	ISVREF(message_1,(SI_Long)19L) = svref_new_value;
	if (ISVREF(Message_board_parameters,(SI_Long)26L))
	    change_text_box_property(message_1,Qhighlight_color,
		    New_message_highlight_color);
    }
    else if (Snapshots_of_related_blocks) {
	set_non_savable_lookup_slot_value(message_1,
		Qsnapshots_of_blocks_related_to_message,
		Snapshots_of_related_blocks);
	Snapshots_of_related_blocks = Nil;
    }
    return VALUES_1(message_1);
}

static Object Qtext;               /* text */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* CHANGE-TEXT-OF-MESSAGE */
Object change_text_of_message varargs_1(int, n)
{
    Object message_1, text_string;
    Object do_not_note_as_kb_state_change_qm, note_as_kb_state_change_qm;
    Object do_not_note_permanent_changes_p, temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(116,80);
    INIT_ARGS_nonrelocating();
    message_1 = REQUIRED_ARG_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    do_not_note_as_kb_state_change_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    note_as_kb_state_change_qm =  
	    !TRUEP(do_not_note_as_kb_state_change_qm) ? T : Nil;
    do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	      0);
	if ( !TRUEP(do_not_note_as_kb_state_change_qm))
	    note_kb_state_change(message_1,Qtext);
	temp = No_value;
	result = change_slot_value(3,message_1,Qbox_translation_and_text,
		slot_value_cons_1(temp,
		convert_text_string_to_text(text_string)));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

static Object Qminimum_width_of_text_box;  /* minimum-width-of-text-box */

static Object Qminimum_height_of_text_box;  /* minimum-height-of-text-box */

static Object Qformat_frame;       /* format-frame */

static Object Qtext_box_format;    /* text-box-format */

static Object Qformat_type;        /* format-type */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qtext_cell_plist_for_text_box;  /* text-cell-plist-for-text-box */

/* UPDATE-DEFAULT-MESSAGE-PROPERTIES-IF-INHERITED-IN-INSTANCES */
Object update_default_message_properties_if_inherited_in_instances(class_1,
	    subclass)
    Object class_1, subclass;
{
    Object format_name_qm, minimum_width_qm, minimum_height_qm, format_name;
    Object format_frame_qm, ab_loopvar_, message_1, message_class_description;
    Object temp, slot_description;
    Declare_special(1);
    Object result;

    x_note_fn_call(116,81);
    format_name_qm = slot_inherited_from_class_p(class_1,subclass,
	    Qdefault_text_box_format_name);
    minimum_width_qm = slot_inherited_from_class_p(class_1,subclass,
	    Qminimum_width_of_text_box);
    minimum_height_qm = slot_inherited_from_class_p(class_1,subclass,
	    Qminimum_height_of_text_box);
    if (format_name_qm) {
	format_name = get_slot_init_form(2,class_1,
		Qdefault_text_box_format_name);
	format_frame_qm = get_instance_with_name_if_any(Qformat_frame,
		format_name);
	if (format_frame_qm);
	else
	    format_frame_qm = make_format_frame(format_name);
    }
    else
	format_frame_qm = Nil;
    ab_loopvar_ = lookup_kb_specific_property_value(subclass,
	    Instances_specific_to_this_class_kbprop);
    message_1 = Nil;
    message_class_description = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Message_class_description,Qmessage_class_description,message_class_description,
	    0);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      message_1 = ab_loopvar_;
      ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
      Message_class_description = ISVREF(message_1,(SI_Long)1L);
      update_images_of_block(message_1,T,Nil);
      if (format_name_qm) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(message_1,Qtext_box_format);
	  SVREF(message_1,FIX((SI_Long)17L)) = format_frame_qm;
	  if (G2_has_v5_mode_windows_p) {
	      temp = message_1;
	      send_ws_representations_item_virtual_attribute_change(temp,
		      get_property_value_function(3,
		      get_symbol_properties_function(Qformat_type),
		      Qvirtual_attribute,Nil),Nil);
	  }
	  slot_description = 
		  get_slot_description_of_class_description_function(Qdefault_text_box_format_name,
		  Message_class_description,Nil);
	  set_slot_description_value_without_noting(message_1,
		  slot_description,ISVREF(slot_description,(SI_Long)6L));
      }
      if (minimum_width_qm) {
	  slot_description = 
		  get_slot_description_of_class_description_function(Qminimum_width_of_text_box,
		  Message_class_description,Nil);
	  set_slot_description_value_without_noting(message_1,
		  slot_description,ISVREF(slot_description,(SI_Long)6L));
      }
      if (minimum_height_qm) {
	  slot_description = 
		  get_slot_description_of_class_description_function(Qminimum_height_of_text_box,
		  Message_class_description,Nil);
	  set_slot_description_value_without_noting(message_1,
		  slot_description,ISVREF(slot_description,(SI_Long)6L));
      }
      slot_description = 
	      get_slot_description_of_class_description_function(Qtext_cell_plist_for_text_box,
	      Message_class_description,Nil);
      set_slot_description_value_without_noting(message_1,slot_description,
	      ISVREF(slot_description,(SI_Long)6L));
      reformat_text_box_in_place(1,message_1);
      update_images_of_block(message_1,Nil,Nil);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qworkspace;          /* workspace */

static Object Qadd_to_message_board;  /* add-to-message-board */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qreclaim_frame_serial_number;  /* reclaim-frame-serial-number */

static Object Qunhighlight_recent_message;  /* unhighlight-recent-message */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qexecute_message_removal_task;  /* execute-message-removal-task */

/* POST-ON-MESSAGE-BOARD */
Object post_on_message_board varargs_1(int, n)
{
    Object text_line, urgency_qm, duration_qm, origin_frame_qm, destination_qm;
    Object workspace_qm, target_block_qm, above_target_qm, do_not_reformat_qm;
    Object temp, current_message_serial_number, current_message_unix_time_qm;
    Object gensym_time, sub_class_bit_vector, message_board, gensymed_symbol_3;
    Object frame, symbol, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, maximum_number_of_entries, oldest_message_qm;
    Object oldest_message_timestamp, count_1, ab_queue_form_;
    Object ab_next_queue_element_, subblock, inform_message_information_qm;
    Object message_timestamp, old, new_1, def_structure_schedule_task_variable;
    Object temp_2, svref_arg_2, svref_new_value, task;
    Object structure_being_reclaimed, x2, real_time_duration_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp_1, svref_new_value_1;
    double aref_new_value_1;
    Declare_varargs_nonrelocating;
    Declare_special(8);
    Object result;

    x_note_fn_call(116,82);
    INIT_ARGS_nonrelocating();
    text_line = REQUIRED_ARG_nonrelocating();
    urgency_qm = REQUIRED_ARG_nonrelocating();
    duration_qm = REQUIRED_ARG_nonrelocating();
    origin_frame_qm = REQUIRED_ARG_nonrelocating();
    destination_qm = REQUIRED_ARG_nonrelocating();
    workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    target_block_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    above_target_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    do_not_reformat_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = registered_and_active_message_board_handling_procedure_p() && 
	    pass_loop_check_for_message_board_handling_procedure_p() ? 
	    invoke_user_defined_message_board_handling_procedure(text_line) 
	    : Qnil;
    if (temp)
	return VALUES_1(temp);
    else {
	current_message_serial_number = increment_message_serial_number();
	PUSH_SPECIAL_WITH_SYMBOL(Current_message_serial_number,Qcurrent_message_serial_number,current_message_serial_number,
		7);
	  current_message_unix_time_qm = compute_current_message_time();
	  PUSH_SPECIAL_WITH_SYMBOL(Current_message_unix_time_qm,Qcurrent_message_unix_time_qm,current_message_unix_time_qm,
		  6);
	    gensym_time = Gensym_time;
	    PUSH_SPECIAL_WITH_SYMBOL(Gensym_time,Qgensym_time,gensym_time,5);
	      if (workspace_qm) {
		  sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Workspace_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp_1 = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      message_board = temp_1 ? workspace_qm : Nil;
	      if (message_board);
	      else {
		  if (target_block_qm) {
		      gensymed_symbol_3 = 
			      ACCESS_ONCE(ISVREF(target_block_qm,
			      (SI_Long)14L));
		      gensymed_symbol_3 = gensymed_symbol_3 ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			      (SI_Long)5L)) : Nil;
		      frame = gensymed_symbol_3;
		      symbol = Qworkspace;
		      gensymed_symbol_3 = 
			      lookup_global_or_kb_specific_property_value(symbol,
			      Class_description_gkbprop);
		      if (gensymed_symbol_3) {
			  sub_class_bit_vector = ISVREF(ISVREF(frame,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
				      superior_class_bit_number & (SI_Long)7L;
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
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      gensymed_symbol_3 = 
			      ACCESS_ONCE(ISVREF(target_block_qm,
			      (SI_Long)14L));
		      gensymed_symbol_3 = gensymed_symbol_3 ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			      (SI_Long)5L)) : Nil;
		      message_board = gensymed_symbol_3;
		  }
		  else
		      message_board = Nil;
	      }
	      if (message_board);
	      else {
		  provide_current_message_board();
		  message_board = Current_message_board_qm;
	      }
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
			print_message_header(Current_message_unix_time_qm,Nil);
			if (do_not_reformat_qm)
			    twrite_line_separator();
			twrite_general_string(text_line);
			temp = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      sub_class_bit_vector = ISVREF(ISVREF(message_board,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Message_board_class_description,
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
		  temp_1 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      message_1 = make_message(9,temp,Nil,temp_1 ? 
		      Qmessage_format_for_message_board : Nil,T,urgency_qm,
		      duration_qm,origin_frame_qm,destination_qm,
		      do_not_reformat_qm);
	      maximum_number_of_entries = ISVREF(Message_board_parameters,
		      (SI_Long)25L);
	      inform_ui_client_interfaces_of_general_update(Qadd_to_message_board,
		      message_1);
	    next_loop:
	      oldest_message_qm = Nil;
	      oldest_message_timestamp = Nil;
	      count_1 = FIX((SI_Long)0L);
	      gensymed_symbol_3 = ACCESS_ONCE(ISVREF(message_board,
		      (SI_Long)14L));
	      gensymed_symbol_3 = gensymed_symbol_3 ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	      ab_queue_form_ = gensymed_symbol_3;
	      ab_next_queue_element_ = Nil;
	      subblock = Nil;
	      if (ab_queue_form_)
		  ab_next_queue_element_ = 
			  constant_queue_next(ISVREF(ab_queue_form_,
			  (SI_Long)2L),ab_queue_form_);
	    next_loop_1:
	      if ( !TRUEP(ab_next_queue_element_))
		  goto end_loop;
	      subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	      ab_next_queue_element_ = 
		      constant_queue_next(ab_next_queue_element_,
		      ab_queue_form_);
	      sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
		  inform_message_information_qm = ISVREF(subblock,
			  (SI_Long)19L);
		  temp_1 = inform_message_information_qm ? 
			  TRUEP(ISVREF(inform_message_information_qm,
			  (SI_Long)3L)) : TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  count_1 = FIXNUM_ADD1(count_1);
		  inform_message_information_qm = ISVREF(subblock,
			  (SI_Long)19L);
		  message_timestamp = inform_message_information_qm ? 
			  ISVREF(inform_message_information_qm,
			  (SI_Long)7L) : Nil;
		  if ( !TRUEP(oldest_message_qm) ||  
			  !TRUEP(message_timestamp) ||  
			  !TRUEP(oldest_message_timestamp) || 
			  FIXNUM_LE(message_timestamp,
			  oldest_message_timestamp)) {
		      oldest_message_qm = subblock;
		      oldest_message_timestamp = message_timestamp;
		  }
	      }
	      goto next_loop_1;
	    end_loop:
	      if (oldest_message_qm && FIXNUM_GE(count_1,
		      maximum_number_of_entries)) {
		  delete_frame(oldest_message_qm);
		  temp = FIXNUM_SUB1(count_1);
	      }
	      else
		  temp = count_1;
	      goto end_1;
	      temp = Qnil;
	    end_1:;
	      if (NUM_LT(temp,maximum_number_of_entries))
		  goto end_loop_1;
	      goto next_loop;
	    end_loop_1:
	      if (ISVREF(Message_board_parameters,(SI_Long)26L)) {
		  old = Nil;
		  new_1 = Nil;
		next_loop_2:
		  old = ISVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)1L);
		  def_structure_schedule_task_variable = 
			  ISVREF(Chain_of_available_schedule_tasks_vector,
			  IFIX(Current_thread_index));
		  if (def_structure_schedule_task_variable) {
		      temp_2 = Chain_of_available_schedule_tasks_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = 
			      ISVREF(def_structure_schedule_task_variable,
			      (SI_Long)0L);
		      SVREF(temp_2,svref_arg_2) = svref_new_value;
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)0L)) = 
			      Qg2_defstruct_structure_name_schedule_task_g2_struct;
		  }
		  else
		      def_structure_schedule_task_variable = 
			      make_permanent_schedule_task_structure_internal();
		  inline_note_allocate_cons(def_structure_schedule_task_variable,
			  Nil);
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)2L)) = Nil;
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)9L)) = Nil;
		  task = def_structure_schedule_task_variable;
		  temp_2 = ISVREF(task,(SI_Long)1L);
		  aref_new_value_1 = DFLOAT_ISAREF_1(Current_real_time,
			  (SI_Long)0L) + 1.0;
		  DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value_1);
		  temp_2 = ISVREF(task,(SI_Long)1L);
		  aref_new_value_1 = -1.0;
		  DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value_1);
		  svref_new_value_1 =  !TRUEP(T);
		  SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		  ISVREF(task,(SI_Long)4L) = FIX((SI_Long)2L);
		  SVREF(task,FIX((SI_Long)5L)) = Nil;
		  temp_2 = gensym_list_2(Nil,Qreclaim_frame_serial_number);
		  SVREF(task,FIX((SI_Long)9L)) = temp_2;
		  SVREF(task,FIX((SI_Long)10L)) = Nil;
		  SVREF(task,FIX((SI_Long)7L)) = Qunhighlight_recent_message;
		  temp_2 = SYMBOL_FUNCTION(Qunhighlight_recent_message);
		  SVREF(task,FIX((SI_Long)8L)) = temp_2;
		  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		  SVREF(task,FIX((SI_Long)13L)) = message_1;
		  temp_2 = copy_frame_serial_number(ISVREF(message_1,
			  (SI_Long)3L));
		  SVREF(task,FIX((SI_Long)14L)) = temp_2;
		  new_1 = task;
		  if (CAS_SVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)1L,
			  old,new_1)) {
		      if (old) {
			  if (EQ(old,Current_schedule_task))
			      Current_schedule_task = Nil;
			  if (ISVREF(old,(SI_Long)6L))
			      cancel_and_reclaim_scheduled_queue_element_1(old);
			  inline_note_reclaim_cons(old,Nil);
			  structure_being_reclaimed = old;
			  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				  0);
			    reclaim_schedule_task_args(ISVREF(old,
				    (SI_Long)9L));
			    SVREF(old,FIX((SI_Long)9L)) = Nil;
			  POP_SPECIAL();
			  temp_2 = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  SVREF(old,FIX((SI_Long)0L)) = temp_2;
			  temp_2 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_2,svref_arg_2) = old;
		      }
		      future_task_schedule_2(new_1);
		      goto end_2;
		  }
		  else {
		      inline_note_reclaim_cons(new_1,Nil);
		      structure_being_reclaimed = new_1;
		      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			      0);
			reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
			SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		      POP_SPECIAL();
		      temp_2 = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
			      IFIX(Current_thread_index));
		      SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
		      temp_2 = Chain_of_available_schedule_tasks_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = new_1;
		  }
		  goto next_loop_2;
		end_loop_2:
		end_2:;
	      }
	      if (target_block_qm) {
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(target_block_qm,
			  (SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)5L)) : Nil;
		  temp_1 = EQ(gensymed_symbol_3,message_board);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      target_block_qm = temp_1 ? target_block_qm : Nil;
	      if (current_message_board_qm() && EQ(message_board,
		      Current_message_board_qm) && 
		      ISVREF(Message_board_parameters,(SI_Long)28L))
		  append_message_to_all_native_message_boards(message_1);
	      post_message_on_message_board(message_1,message_board,
		      target_block_qm,target_block_qm ? above_target_qm : Nil);
	      if (duration_qm) {
		  if (SIMPLE_VECTOR_P(origin_frame_qm) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(origin_frame_qm)) 
			  > (SI_Long)2L &&  !EQ(ISVREF(origin_frame_qm,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(origin_frame_qm,(SI_Long)1L);
		      gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && 
			      EQ(ISVREF(x2,(SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      gensymed_symbol_3 = Nil;
		  if (gensymed_symbol_3) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Block_class_description,
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
			  gensymed_symbol_2 = superior_class_bit_number & 
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
		  real_time_duration_qm = temp_1 ? ((SI_Long)0L != 
			  (IFIX(ISVREF(origin_frame_qm,(SI_Long)4L)) & 
			  (SI_Long)16777216L) ? T : Nil) : Nil;
		  old = Nil;
		  new_1 = Nil;
		next_loop_3:
		  old = ISVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)0L);
		  def_structure_schedule_task_variable = 
			  ISVREF(Chain_of_available_schedule_tasks_vector,
			  IFIX(Current_thread_index));
		  if (def_structure_schedule_task_variable) {
		      temp_2 = Chain_of_available_schedule_tasks_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = 
			      ISVREF(def_structure_schedule_task_variable,
			      (SI_Long)0L);
		      SVREF(temp_2,svref_arg_2) = svref_new_value;
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)0L)) = 
			      Qg2_defstruct_structure_name_schedule_task_g2_struct;
		  }
		  else
		      def_structure_schedule_task_variable = 
			      make_permanent_schedule_task_structure_internal();
		  inline_note_allocate_cons(def_structure_schedule_task_variable,
			  Nil);
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)2L)) = Nil;
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)9L)) = Nil;
		  task = def_structure_schedule_task_variable;
		  temp_2 = ISVREF(task,(SI_Long)1L);
		  aref_new_value_1 = real_time_duration_qm ? 
			  DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
			  (double)IFIX(duration_qm) : 
			  DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 
			  (double)IFIX(duration_qm);
		  DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value_1);
		  temp_2 = ISVREF(task,(SI_Long)1L);
		  aref_new_value_1 = -1.0;
		  DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value_1);
		  svref_new_value_1 =  !TRUEP(real_time_duration_qm);
		  SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		  ISVREF(task,(SI_Long)4L) = FIX((SI_Long)2L);
		  SVREF(task,FIX((SI_Long)5L)) = Nil;
		  temp_2 = gensym_list_2(Nil,Qreclaim_frame_serial_number);
		  SVREF(task,FIX((SI_Long)9L)) = temp_2;
		  SVREF(task,FIX((SI_Long)10L)) = Nil;
		  SVREF(task,FIX((SI_Long)7L)) = Qexecute_message_removal_task;
		  temp_2 = SYMBOL_FUNCTION(Qexecute_message_removal_task);
		  SVREF(task,FIX((SI_Long)8L)) = temp_2;
		  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		  SVREF(task,FIX((SI_Long)13L)) = message_1;
		  temp_2 = copy_frame_serial_number(ISVREF(message_1,
			  (SI_Long)3L));
		  SVREF(task,FIX((SI_Long)14L)) = temp_2;
		  new_1 = task;
		  if (CAS_SVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)0L,
			  old,new_1)) {
		      if (old) {
			  if (EQ(old,Current_schedule_task))
			      Current_schedule_task = Nil;
			  if (ISVREF(old,(SI_Long)6L))
			      cancel_and_reclaim_scheduled_queue_element_1(old);
			  inline_note_reclaim_cons(old,Nil);
			  structure_being_reclaimed = old;
			  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				  0);
			    reclaim_schedule_task_args(ISVREF(old,
				    (SI_Long)9L));
			    SVREF(old,FIX((SI_Long)9L)) = Nil;
			  POP_SPECIAL();
			  temp_2 = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  SVREF(old,FIX((SI_Long)0L)) = temp_2;
			  temp_2 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_2,svref_arg_2) = old;
		      }
		      future_task_schedule_2(new_1);
		      goto end_3;
		  }
		  else {
		      inline_note_reclaim_cons(new_1,Nil);
		      structure_being_reclaimed = new_1;
		      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			      0);
			reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
			SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		      POP_SPECIAL();
		      temp_2 = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
			      IFIX(Current_thread_index));
		      SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
		      temp_2 = Chain_of_available_schedule_tasks_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = new_1;
		  }
		  goto next_loop_3;
		end_loop_3:
		end_3:;
	      }
	      if (ISVREF(Logbook_parameters,(SI_Long)36L) || 
		      Send_messages_to_logbook_p)
		  post_message_on_logbook(text_line,T);
	      if (Send_messages_to_console_p)
		  notify_user_at_console(2,string_constant_12,text_line);
	      reclaim_managed_simple_float_array_of_length_1(Current_message_unix_time_qm);
	      result = reclaim_text_string(text_line);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* UNHIGHLIGHT-RECENT-MESSAGE */
Object unhighlight_recent_message(message_1,frame_reference_serial_number)
    Object message_1, frame_reference_serial_number;
{
    Object gensymed_symbol, xa, ya, structure_being_reclaimed, temp_1;
    Object svref_arg_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(116,83);
    gensymed_symbol = ISVREF(message_1,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(message_1) ? EQ(ISVREF(message_1,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(frame_reference_serial_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(frame_reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	highlight_or_unhighlight_for_slot(5,message_1,
		Qbox_translation_and_text,Nil,New_message_highlight_color,T);
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)1L);
	if (CAS_SVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)1L,
		gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(Nil);
}

/* POST-MESSAGE-ON-MESSAGE-BOARD */
Object post_message_on_message_board(message_1,message_board,
	    target_block_qm,above_target_qm)
    Object message_1, message_board, target_block_qm, above_target_qm;
{
    Object gensymed_symbol, workspace_margin, interspacing, temp;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loop_it_;
    Object sub_class_bit_vector, extreme_top_edge_of_target;
    Object extreme_bottom_edge_of_target, temp_2, left, top, bottom;
    Object extreme_left_edge_of_target, potential_left_edge;
    Object potential_top_edge, subblock_is_inform_message_qm;
    Object inform_message_information_qm, block, left_edge_in_workspace;
    Object extreme_left_edge, extreme_top_edge, extreme_right_edge;
    Object extreme_bottom_edge;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, height;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, potential_right_edge, top_edge_in_workspace;
    SI_Long right_edge_in_workspace, bottom_edge_in_workspace;
    char temp_1;
    Object result;

    x_note_fn_call(116,84);
    gensymed_symbol = ISVREF(message_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(message_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    height = gensymed_symbol_1 - gensymed_symbol_2;
    workspace_margin = ISVREF(message_board,(SI_Long)17L);
    interspacing = ISVREF(Message_board_parameters,(SI_Long)24L);
    temp = target_block_qm;
    if (temp);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(message_board,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	ab_loop_it_ = Nil;
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	ab_loop_it_ = temp_1 ? subblock : Nil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    target_block_qm = temp;
    extreme_top_edge_of_target = Nil;
    extreme_bottom_edge_of_target = Nil;
    if (target_block_qm) {
	result = determine_extreme_edges_of_block(target_block_qm);
	MVS_4(result,left,top,temp,bottom);
	extreme_top_edge_of_target = top;
	extreme_bottom_edge_of_target = bottom;
	extreme_left_edge_of_target = left;
    }
    else
	extreme_left_edge_of_target = Nil;
    potential_left_edge = target_block_qm ? extreme_left_edge_of_target : Nil;
    if (potential_left_edge);
    else {
	gensymed_symbol = ISVREF(message_board,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(workspace_margin);
	potential_left_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    gensymed_symbol_1 = IFIX(potential_left_edge);
    gensymed_symbol = ISVREF(message_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(message_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    potential_right_edge = gensymed_symbol_1 + gensymed_symbol_2;
    potential_top_edge = target_block_qm ? (above_target_qm ? 
	    FIX(IFIX(FIXNUM_MINUS(extreme_top_edge_of_target,
	    interspacing)) - height) : 
	    FIXNUM_ADD(extreme_bottom_edge_of_target,interspacing)) : Nil;
    if (potential_top_edge);
    else {
	gensymed_symbol = ISVREF(message_board,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(workspace_margin);
	potential_top_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
  next_loop_1:
    gensymed_symbol = ACCESS_ONCE(ISVREF(message_board,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    subblock_is_inform_message_qm = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_2:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_1;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
    if (temp_1) {
	inform_message_information_qm = ISVREF(subblock,(SI_Long)19L);
	subblock_is_inform_message_qm = inform_message_information_qm ? 
		ISVREF(inform_message_information_qm,(SI_Long)3L) : Nil;
    }
    else
	subblock_is_inform_message_qm = Nil;
    block = subblock;
    left_edge_in_workspace = potential_left_edge;
    gensymed_symbol_1 = IFIX(potential_top_edge);
    gensymed_symbol_2 = subblock_is_inform_message_qm ? IFIX(interspacing) 
	    : (SI_Long)0L;
    top_edge_in_workspace = gensymed_symbol_1 - gensymed_symbol_2;
    right_edge_in_workspace = potential_right_edge;
    gensymed_symbol_1 = IFIX(potential_top_edge);
    gensymed_symbol_2 = height;
    gensymed_symbol_3 = subblock_is_inform_message_qm ? IFIX(interspacing) 
	    : (SI_Long)0L;
    bottom_edge_in_workspace = gensymed_symbol_1 + gensymed_symbol_2 + 
	    gensymed_symbol_3;
    result = determine_extreme_edges_of_block(block);
    MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
	    extreme_bottom_edge);
    if (IFIX(FIXNUM_MAX(left_edge_in_workspace,extreme_left_edge)) < 
	    MIN(right_edge_in_workspace,IFIX(extreme_right_edge)) && 
	    MAX(top_edge_in_workspace,IFIX(extreme_top_edge)) < 
	    MIN(bottom_edge_in_workspace,IFIX(extreme_bottom_edge))) {
	if (above_target_qm) {
	    result = determine_extreme_edges_of_block(subblock);
	    gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
	    potential_top_edge = FIX(IFIX(gensymed_symbol) - height);
	}
	else {
	    result = determine_extreme_edges_of_block(subblock);
	    gensymed_symbol = NTH_VALUE((SI_Long)3L, result);
	    potential_top_edge = gensymed_symbol;
	}
	temp_1 = TRUEP(Nil);
	goto end_2;
    }
    goto next_loop_2;
  end_loop_1:
    temp_1 = TRUEP(T);
    goto end_2;
    temp_1 = TRUEP(Qnil);
  end_2:;
    if (temp_1)
	goto end_loop_2;
    potential_top_edge = above_target_qm ? FIXNUM_MINUS(potential_top_edge,
	    interspacing) : FIXNUM_ADD(potential_top_edge,interspacing);
    goto next_loop_1;
  end_loop_2:
    add_to_workspace(6,message_1,message_board,potential_left_edge,
	    potential_top_edge,T,T);
    return VALUES_1(Qnil);
}

/* CLEAR-INFORM-MESSAGES */
Object clear_inform_messages()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, message_1;
    Object inform_message_information_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(116,85);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    message_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qmessage);
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
      message_1 = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      inform_message_information_qm = ISVREF(message_1,(SI_Long)19L);
      if (inform_message_information_qm ? 
	      TRUEP(ISVREF(inform_message_information_qm,(SI_Long)3L)) : 
	      TRUEP(Nil))
	  delete_frame(message_1);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MAKE-MESSAGE-BOARD */
Object make_message_board()
{
    Object message_board, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(116,86);
    message_board = make_workspace(6,Qmessage_board,Qmessage_board,Nil,Nil,
	    ISVREF(Message_board_parameters,(SI_Long)22L),
	    ISVREF(Message_board_parameters,(SI_Long)23L));
    if (System_is_running || System_has_paused) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(message_board,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = message_board;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(message_board);
}

static Object Qlogbook;            /* logbook */

static Object Qtitle_of_book_qm;   /* title-of-book? */

static Object array_constant_2;    /* # */

/* PROVIDE-CURRENT-LOGBOOK */
Object provide_current_logbook()
{
    Object gensymed_symbol, gensymed_symbol_1, logbook;
    Object frame_serial_number_setf_arg, temp_1;
    char temp;

    x_note_fn_call(116,87);
    temp =  !TRUEP(Current_logbook_qm);
    if (temp);
    else {
	gensymed_symbol = ISVREF(Current_logbook_qm,(SI_Long)3L);
	gensymed_symbol_1 = Current_logbook_serial_number_qm;
	temp =  !(FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
		FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) 
		: FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
		FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) 
		&& FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1)));
    }
    if (temp) {
	logbook = make_entity(1,Qlogbook);
	frame_serial_number_setf_arg = ISVREF(logbook,(SI_Long)3L);
	temp_1 = (FIXNUMP(Current_logbook_serial_number_qm) ||  
		!TRUEP(Current_logbook_serial_number_qm)) && 
		(FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(Current_logbook_serial_number_qm,
		frame_serial_number_setf_arg);
	Current_logbook_serial_number_qm = temp_1;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(logbook,Qtitle_of_book_qm);
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)16L));
	SVREF(logbook,FIX((SI_Long)23L)) = temp_1;
	Current_logbook_qm = logbook;
	return VALUES_1(Current_logbook_qm);
    }
    else
	return VALUES_1(Nil);
}

/* EXECUTE-MESSAGE-REMOVAL-TASK */
Object execute_message_removal_task(message_1,message_frame_serial_number)
    Object message_1, message_frame_serial_number;
{
    Object gensymed_symbol, xa, ya, structure_being_reclaimed, temp_1;
    Object svref_arg_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(116,88);
    gensymed_symbol = ISVREF(message_1,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(message_1) ? EQ(ISVREF(message_1,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(message_frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(message_frame_serial_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(message_frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(message_frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)0L);
	if (CAS_SVREF(ISVREF(message_1,(SI_Long)19L),(SI_Long)0L,
		gensymed_symbol,Nil)) {
	    if (gensymed_symbol) {
		if (EQ(gensymed_symbol,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		structure_being_reclaimed = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
	delete_frame(message_1);
    }
    return VALUES_1(Nil);
}

/* CLOSE-LOGBOOKS */
Object close_logbooks()
{
    x_note_fn_call(116,89);
    Current_message_serial_number = FIX((SI_Long)1L);
    Next_serial_number_to_be_generated = FIX((SI_Long)1L);
    Current_message_board_qm = Nil;
    Current_logbook_qm = Nil;
    return VALUES_1(Current_logbook_qm);
}

/* REDISPLAY-LOGBOOK-IN-CURRENT-WORKSTATION */
Object redisplay_logbook_in_current_workstation()
{
    x_note_fn_call(116,90);
    if (Servicing_workstation_qm) {
	provide_current_logbook();
	if (use_native_logbook_p(Current_workstation_window) && 
		ISVREF(Current_logbook_qm,(SI_Long)20L))
	    show_native_logbook(Current_workstation_window);
	return neatly_stack_logbook_pages_in_pane(Current_workstation_detail_pane,
		Current_logbook_qm);
    }
    else
	return VALUES_1(Nil);
}

/* MESSAGE-ON-MESSAGE-BOARD-P */
Object message_on_message_board_p(block)
    Object block;
{
    Object gensymed_symbol, superblock_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,91);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
    if ((temp ? TRUEP(superblock_qm) : TRUEP(Nil)) ? 
	    TRUEP(current_message_board_qm()) : TRUEP(Nil))
	return VALUES_1(EQ(superblock_qm,Current_message_board_qm) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MESSAGE-ON-LOGBOOK-P */
Object message_on_logbook_p(block)
    Object block;
{
    Object gensymed_symbol, superblock_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,92);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
    if (temp ? TRUEP(superblock_qm) : TRUEP(Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Logbook_page_class_description,(SI_Long)18L));
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrunning_head;       /* running-head */

/* MAKE-RUNNING-HEAD */
Object make_running_head(text_line)
    Object text_line;
{
    x_note_fn_call(116,93);
    return make_free_text_box(2,text_line,Qrunning_head);
}

/* GENERATE-SPOT-FOR-RUNNING-HEAD */
Object generate_spot_for_running_head(running_head,mouse_pointer)
    Object running_head, mouse_pointer;
{
    x_note_fn_call(116,94);
    return generate_workspace_background_spot(mouse_pointer);
}

static Object Qpage_number;        /* page-number */

/* MAKE-PAGE-NUMBER */
Object make_page_number(text_line)
    Object text_line;
{
    x_note_fn_call(116,95);
    return make_free_text_box(2,text_line,Qpage_number);
}

/* GENERATE-SPOT-FOR-PAGE-NUMBER */
Object generate_spot_for_page_number(page_number,mouse_pointer)
    Object page_number, mouse_pointer;
{
    x_note_fn_call(116,96);
    return generate_workspace_background_spot(mouse_pointer);
}

static Object string_constant_14;  /* "~a-~a-~a" */

static Object Qab_format;          /* format */

/* NOTIFY-USER-2 */
Object notify_user_2(notification_string)
    Object notification_string;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, list_1, cons_1, pkg_name, d1, d2, d3, dd1, dd2, dd3, q1, q2;
    Object q3, q4, q5, q6, start_time, end_time, c1, c2, c3, c4, array, c6;
    Object machine_id, product_code, expiration_date_qm, packages, processes;
    Object floaters, t2_floaters, gensymed_symbol, j, pkg, ab_loop_list_, size;
    Object bunch_count, temp_3, r0, r1, r2, r3, r4, r5, r6, r7, s0, s1_1, s2_1;
    Object s3, s4, s5, s6, s7, offset;
    SI_Long bv16_length, temp, aref_new_value, length_1, i, ab_loop_bind_, i_1;
    SI_Long i_2, gensymed_symbol_1, k, gensymed_symbol_2;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(116,97);
    if (EQ(notification_string,Actual_arg)) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
		  tformat(4,string_constant_14,Qab_format,
			  CAR(Format_redefinition_list),
			  SECOND(Format_redefinition_list));
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	list_1 = SYMBOL_VALUE(intern_text_string(1,temp_1));
	cons_1 = list_1;
	i = (SI_Long)1L;
      next_loop:
	if (i > (SI_Long)14L)
	    goto end_loop;
	if (ATOM(cons_1)) {
	    temp_2 = TRUEP(Nil);
	    goto end_1;
	}
	cons_1 = CDR(cons_1);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	pkg_name = Nil;
	d1 = Nil;
	d2 = Nil;
	d3 = Nil;
	dd1 = Nil;
	dd2 = Nil;
	dd3 = Nil;
	q1 = Nil;
	q2 = Nil;
	q3 = Nil;
	q4 = Nil;
	q5 = Nil;
	q6 = Nil;
	start_time = Nil;
	end_time = Nil;
	c1 = SEVENTH(list_1);
	c2 = EIGHTH(list_1);
	c3 = NINTH(list_1);
	c4 = TENTH(list_1);
	array = FOURTH(list_1);
	c6 = FIFTH(list_1);
	machine_id = SIXTH(list_1);
	cons_1 = nth(FIX((SI_Long)10L),list_1);
	product_code = CONSP(cons_1) ? CAR(cons_1) : Nil;
	expiration_date_qm = nth(FIX((SI_Long)11L),list_1);
	packages = nth(FIX((SI_Long)12L),list_1);
	processes = nth(FIX((SI_Long)13L),list_1);
	floaters = nth(FIX((SI_Long)14L),list_1);
	t2_floaters = nth(FIX((SI_Long)15L),list_1);
	gensymed_symbol = Nil;
	gensymed_symbol =  !SIMPLE_VECTOR_P(array) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !SIMPLE_VECTOR_P(c6) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !FIXNUMP(c1) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !FIXNUMP(c2) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !FIXNUMP(c3) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !FIXNUMP(c4) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !(IFIX(length(array)) >= (SI_Long)8L) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !(IFIX(length(c6)) == (SI_Long)8L) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(array));
	j = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	j = ISVREF(array,i);
	if ( !(FIXNUMP(j) && (SI_Long)0L <= IFIX(j) && IFIX(j) <= 
		(SI_Long)255L)) {
	    temp_2 = TRUEP(Nil);
	    goto end_3;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = TRUEP(T);
	goto end_3;
	temp_2 = TRUEP(Qnil);
      end_3:;
	gensymed_symbol =  !temp_2 ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !FIXNUMP(product_code) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol = expiration_date_qm ? ( 
		!FIXNUMP(expiration_date_qm) ? T : Nil) : Qnil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !TRUEP(text_string_p(machine_id)) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	if (limited_true_list_p(packages,FIX((SI_Long)200L))) {
	    pkg = Nil;
	    ab_loop_list_ = packages;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    pkg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp_2 =  !TRUEP(assq_function(pkg_name,Control_sequence_record));
	    if (temp_2);
	    else {
		if ( !TRUEP(limited_true_list_p(pkg,FIX((SI_Long)4L)))) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		pkg_name = FIRST(pkg);
		if ( !TRUEP(pkg_name)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		d1 = SECOND(pkg);
		if ( !TRUEP(d1)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		d2 = THIRD(pkg);
		if ( !TRUEP(d2)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		d3 = FOURTH(pkg);
		if ( !TRUEP(d3)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		temp_1 = fifth(pkg);
		if (temp_1);
		else
		    temp_1 = FIX((SI_Long)0L);
		start_time = temp_1;
		if ( !TRUEP(start_time)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		temp_1 = SIXTH(pkg);
		if (temp_1);
		else
		    temp_1 = FIX((SI_Long)0L);
		start_time = temp_1;
		if ( !TRUEP(start_time)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !SYMBOLP(pkg_name)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !FIXNUMP(d1)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !FIXNUMP(d2)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !FIXNUMP(d3)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		pkg_name = symbol_name_text_string(pkg_name);
		if ( !TRUEP(pkg_name)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		result = color_match_p(pkg_name);
		MVS_2(result,q1,q2);
		if ( !TRUEP(q1)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		result = eval_sequence_2(pkg_name);
		MVS_2(result,q3,q4);
		if ( !TRUEP(q3)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		result = button_down_handler(machine_id);
		MVS_2(result,q5,q6);
		if ( !TRUEP(q5)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		result = procedure_recursive(q1,q2,q5,q6,start_time,end_time);
		MVS_2(result,dd1,dd2);
		if ( !TRUEP(dd1)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		dd3 = reverse_list_search(q3,q4,q5,q6,dd1,dd2,start_time,
			end_time);
		if ( !TRUEP(dd3)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !FIXNUM_EQ(d1,dd1)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		if ( !FIXNUM_EQ(d2,dd2)) {
		    temp_2 = TRUEP(Nil);
		    goto end_4;
		}
		temp_2 = FIXNUM_EQ(d3,dd3);
		goto end_4;
		temp_2 = TRUEP(Nil);
	      end_4:;
	    }
	    if ( !temp_2) {
		temp_2 = TRUEP(Nil);
		goto end_5;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_2 = TRUEP(T);
	    goto end_5;
	    temp_2 = TRUEP(Qnil);
	  end_5:;
	}
	else
	    temp_2 = TRUEP(Nil);
	gensymed_symbol =  !temp_2 ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !( !TRUEP(processes) || FIXNUMP(processes)) ? T 
		: Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !(FIXNUMP(floaters) && IFIX(floaters) >= 
		(SI_Long)0L && IFIX(floaters) <= (SI_Long)8000L) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol =  !(FIXNUMP(t2_floaters) && IFIX(t2_floaters) >= 
		(SI_Long)0L && IFIX(t2_floaters) <= (SI_Long)65535L) ? T : Nil;
	if (gensymed_symbol) {
	    temp_2 = TRUEP(gensymed_symbol);
	    goto end_2;
	}
      nil:
	temp_2 = TRUEP(Qnil);
      end_2:
	if (temp_2)
	    temp_2 = TRUEP(Nil);
	else {
	    size = length(array);
	    bunch_count = FIXNUM_SUB1(ceiling(size,FIX((SI_Long)8L)));
	    i = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(bunch_count);
	    i_1 = (SI_Long)0L;
	  next_loop_3:
	    if (i_1 > (SI_Long)7L)
		goto end_loop_3;
	    temp_3 = ISVREF(array,i_1);
	    ISVREF(c6,i_1) = temp_3;
	    i_1 = i_1 + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	  next_loop_4:
	    if (i > ab_loop_bind_)
		goto end_loop_4;
	    i_1 = (SI_Long)1L;
	  next_loop_5:
	    if (i_1 > (SI_Long)5L)
		goto end_loop_5;
	    i_2 = (SI_Long)0L;
	  next_loop_6:
	    if (i_2 > (SI_Long)7L)
		goto end_loop_6;
	    temp_3 = ISVREF(Keytab1,IFIX(ISVREF(c6,i_2)));
	    ISVREF(c6,i_2) = temp_3;
	    i_2 = i_2 + (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    r0 = ISVREF(c6,(SI_Long)0L);
	    r1 = ISVREF(c6,(SI_Long)1L);
	    r2 = ISVREF(c6,(SI_Long)2L);
	    r3 = ISVREF(c6,(SI_Long)3L);
	    r4 = ISVREF(c6,(SI_Long)4L);
	    r5 = ISVREF(c6,(SI_Long)5L);
	    r6 = ISVREF(c6,(SI_Long)6L);
	    r7 = ISVREF(c6,(SI_Long)7L);
	    s0 = FIX((SI_Long)0L);
	    s1_1 = FIX((SI_Long)0L);
	    s2_1 = FIX((SI_Long)0L);
	    s3 = FIX((SI_Long)0L);
	    s4 = FIX((SI_Long)0L);
	    s5 = FIX((SI_Long)0L);
	    s6 = FIX((SI_Long)0L);
	    s7 = FIX((SI_Long)0L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)1L);
	    gensymed_symbol_1 = IFIX(r0) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)2L);
	    gensymed_symbol_1 = IFIX(r1) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)4L);
	    gensymed_symbol_1 = IFIX(r2) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)8L);
	    gensymed_symbol_1 = IFIX(r3) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)16L);
	    gensymed_symbol_1 = IFIX(r4) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)32L);
	    gensymed_symbol_1 = IFIX(r5) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)64L);
	    gensymed_symbol_1 = IFIX(r6) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)128L);
	    gensymed_symbol_1 = IFIX(r7) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)128L);
	    SVREF(c6,FIX((SI_Long)0L)) = s0;
	    SVREF(c6,FIX((SI_Long)1L)) = s1_1;
	    SVREF(c6,FIX((SI_Long)2L)) = s2_1;
	    SVREF(c6,FIX((SI_Long)3L)) = s3;
	    SVREF(c6,FIX((SI_Long)4L)) = s4;
	    SVREF(c6,FIX((SI_Long)5L)) = s5;
	    SVREF(c6,FIX((SI_Long)6L)) = s6;
	    SVREF(c6,FIX((SI_Long)7L)) = s7;
	    i_1 = i_1 + (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	    k = (SI_Long)0L;
	    offset = Nil;
	    j = Nil;
	  next_loop_7:
	    if (k > (SI_Long)7L)
		goto end_loop_7;
	    offset = FIX((SI_Long)8L * i);
	    j = FIX(k + IFIX(offset));
	    gensymed_symbol_1 = IFIX(ISVREF(c6,k));
	    gensymed_symbol_2 = FIXNUM_LT(j,size) ? IFIX(ISVREF(array,
		    IFIX(j))) : IFIX(j);
	    temp = gensymed_symbol_1 ^ gensymed_symbol_2;
	    ISVREF(c6,k) = FIX(temp);
	    k = k + (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    i = i + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:
	    gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)7L));
	    gensymed_symbol_2 = IFIX(logand(product_code,FIX((SI_Long)255L)));
	    temp = gensymed_symbol_1 ^ gensymed_symbol_2;
	    ISVREF(c6,(SI_Long)7L) = FIX(temp);
	    gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)6L));
	    gensymed_symbol_2 = IFIX(product_code) >>  -  - (SI_Long)8L & 
		    (SI_Long)255L;
	    temp = gensymed_symbol_1 ^ gensymed_symbol_2;
	    ISVREF(c6,(SI_Long)6L) = FIX(temp);
	    if (expiration_date_qm) {
		gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)5L));
		gensymed_symbol_2 = IFIX(logand(expiration_date_qm,
			FIX((SI_Long)255L)));
		temp = gensymed_symbol_1 ^ gensymed_symbol_2;
		ISVREF(c6,(SI_Long)5L) = FIX(temp);
		gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)4L));
		gensymed_symbol_2 = IFIX(expiration_date_qm) >>  -  - 
			(SI_Long)8L & (SI_Long)255L;
		temp = gensymed_symbol_1 ^ gensymed_symbol_2;
		ISVREF(c6,(SI_Long)4L) = FIX(temp);
	    }
	    if (processes) {
		temp_3 = FIXNUM_LOGXOR(ISVREF(c6,(SI_Long)3L),processes);
		SVREF(c6,FIX((SI_Long)3L)) = temp_3;
	    }
	    if ( !(IFIX(floaters) == (SI_Long)0L)) {
		gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)2L));
		gensymed_symbol_2 = IFIX(logand(floaters,FIX((SI_Long)255L)));
		temp = gensymed_symbol_1 ^ gensymed_symbol_2;
		ISVREF(c6,(SI_Long)2L) = FIX(temp);
		gensymed_symbol_1 = IFIX(ISVREF(c6,(SI_Long)0L));
		gensymed_symbol_2 = IFIX(floaters) >>  -  - (SI_Long)8L & 
			(SI_Long)255L;
		temp = gensymed_symbol_1 ^ gensymed_symbol_2;
		ISVREF(c6,(SI_Long)0L) = FIX(temp);
	    }
	    if ( !(IFIX(t2_floaters) == (SI_Long)0L)) {
		gensymed_symbol_1 = IFIX(logand(t2_floaters,
			FIX((SI_Long)255L)));
		temp_3 = logxor(ISVREF(c6,(SI_Long)1L),FIX(gensymed_symbol_1));
		SVREF(c6,FIX((SI_Long)1L)) = temp_3;
		temp_1 = ISVREF(c6,(SI_Long)0L);
		gensymed_symbol_1 = IFIX(t2_floaters) >>  -  - (SI_Long)8L 
			& (SI_Long)255L;
		temp_3 = logxor(temp_1,FIX(gensymed_symbol_1));
		SVREF(c6,FIX((SI_Long)0L)) = temp_3;
	    }
	    i = (SI_Long)1L;
	  next_loop_8:
	    if (i > (SI_Long)5L)
		goto end_loop_8;
	    i_1 = (SI_Long)0L;
	  next_loop_9:
	    if (i_1 > (SI_Long)7L)
		goto end_loop_9;
	    temp_3 = ISVREF(Keytab1,IFIX(ISVREF(c6,i_1)));
	    ISVREF(c6,i_1) = temp_3;
	    i_1 = i_1 + (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    r0 = ISVREF(c6,(SI_Long)0L);
	    r1 = ISVREF(c6,(SI_Long)1L);
	    r2 = ISVREF(c6,(SI_Long)2L);
	    r3 = ISVREF(c6,(SI_Long)3L);
	    r4 = ISVREF(c6,(SI_Long)4L);
	    r5 = ISVREF(c6,(SI_Long)5L);
	    r6 = ISVREF(c6,(SI_Long)6L);
	    r7 = ISVREF(c6,(SI_Long)7L);
	    s0 = FIX((SI_Long)0L);
	    s1_1 = FIX((SI_Long)0L);
	    s2_1 = FIX((SI_Long)0L);
	    s3 = FIX((SI_Long)0L);
	    s4 = FIX((SI_Long)0L);
	    s5 = FIX((SI_Long)0L);
	    s6 = FIX((SI_Long)0L);
	    s7 = FIX((SI_Long)0L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r0) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)1L);
	    gensymed_symbol_1 = IFIX(r0) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)1L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r1) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)2L);
	    gensymed_symbol_1 = IFIX(r1) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)2L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r2) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)4L);
	    gensymed_symbol_1 = IFIX(r2) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)4L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r3) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)8L);
	    gensymed_symbol_1 = IFIX(r3) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)8L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r4) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)16L);
	    gensymed_symbol_1 = IFIX(r4) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)16L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r5) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)32L);
	    gensymed_symbol_1 = IFIX(r5) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)32L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r6) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)64L);
	    gensymed_symbol_1 = IFIX(r6) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)64L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)1L))
		s0 = FIX(IFIX(s0) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)2L))
		s1_1 = FIX(IFIX(s1_1) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)4L))
		s2_1 = FIX(IFIX(s2_1) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)8L))
		s3 = FIX(IFIX(s3) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)16L))
		s4 = FIX(IFIX(s4) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)32L))
		s5 = FIX(IFIX(s5) | (SI_Long)128L);
	    if ((SI_Long)0L != (IFIX(r7) & (SI_Long)64L))
		s6 = FIX(IFIX(s6) | (SI_Long)128L);
	    gensymed_symbol_1 = IFIX(r7) & (SI_Long)128L;
	    if ((SI_Long)0L != gensymed_symbol_1)
		s7 = FIX(IFIX(s7) | (SI_Long)128L);
	    SVREF(c6,FIX((SI_Long)0L)) = s0;
	    SVREF(c6,FIX((SI_Long)1L)) = s1_1;
	    SVREF(c6,FIX((SI_Long)2L)) = s2_1;
	    SVREF(c6,FIX((SI_Long)3L)) = s3;
	    SVREF(c6,FIX((SI_Long)4L)) = s4;
	    SVREF(c6,FIX((SI_Long)5L)) = s5;
	    SVREF(c6,FIX((SI_Long)6L)) = s6;
	    SVREF(c6,FIX((SI_Long)7L)) = s7;
	    i = i + (SI_Long)1L;
	    goto next_loop_8;
	  end_loop_8:;
	    temp_2 = IFIX(c1) == IFIX(ISVREF(c6,(SI_Long)0L)) + 
		    (SI_Long)256L * IFIX(ISVREF(c6,(SI_Long)1L)) && 
		    IFIX(c2) == IFIX(ISVREF(c6,(SI_Long)2L)) + 
		    (SI_Long)256L * IFIX(ISVREF(c6,(SI_Long)3L)) && 
		    IFIX(c3) == IFIX(ISVREF(c6,(SI_Long)4L)) + 
		    (SI_Long)256L * IFIX(ISVREF(c6,(SI_Long)5L)) ? 
		    IFIX(c4) == IFIX(ISVREF(c6,(SI_Long)6L)) + 
		    (SI_Long)256L * IFIX(ISVREF(c6,(SI_Long)7L)) : TRUEP(Qnil);
	    goto end_6;
	    temp_2 = TRUEP(Qnil);
	  end_6:;
	}
	goto end_1;
	temp_2 = TRUEP(Qnil);
      end_1:;
	if ( !temp_2) {
	    temp_3 = Default_format_structure;
	    M_THIRD(temp_3) = T;
	}
	return VALUES_1(Nil);
    }
    increment_message_serial_number();
    post_message_on_logbook(notification_string,Nil);
    return reclaim_text_string(notification_string);
}

/* NOTIFY-ENGINEER */
Object notify_engineer varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(116,98);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    if (EQ(arg1,No_arg))
	return notify_user(1,notification_as_format_string);
    else if (EQ(arg2,No_arg))
	return notify_user(2,notification_as_format_string,arg1);
    else if (EQ(arg3,No_arg))
	return notify_user(3,notification_as_format_string,arg1,arg2);
    else if (EQ(arg4,No_arg))
	return notify_user(4,notification_as_format_string,arg1,arg2,arg3);
    else if (EQ(arg5,No_arg))
	return notify_user(5,notification_as_format_string,arg1,arg2,arg3,
		arg4);
    else if (EQ(arg6,No_arg))
	return notify_user(6,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5);
    else if (EQ(arg7,No_arg))
	return notify_user(7,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6);
    else if (EQ(arg8,No_arg))
	return notify_user(8,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7);
    else if (EQ(arg9,No_arg))
	return notify_user(9,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7,arg8);
    else
	return notify_user(10,notification_as_format_string,arg1,arg2,arg3,
		arg4,arg5,arg6,arg7,arg8,arg9);
}

/* NOTIFY-USER-AT-WORKSTATION */
Object notify_user_at_workstation varargs_1(int, n)
{
    Object notification_as_format_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(116,99);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

Object Width_for_prominent_notification_workspaces = UNBOUND;

Object Height_for_prominent_notification_workspaces = UNBOUND;

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qcenter;             /* center */

/* POST-PROMINENT-NOTIFICATION */
Object post_prominent_notification varargs_1(int, n)
{
    Object text_line;
    Object width_qm, height_qm, disarm_qm, temp, temp_1, temp_2, workspace;
    Object workstation, ab_loop_list_, gensym_window;
    Declare_varargs_nonrelocating;

    x_note_fn_call(116,100);
    INIT_ARGS_nonrelocating();
    text_line = REQUIRED_ARG_nonrelocating();
    width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    height_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    disarm_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    notify_user(2,string_constant_7,text_line);
    temp = make_message(1,text_line);
    temp_1 = width_qm;
    if (temp_1);
    else
	temp_1 = Width_for_prominent_notification_workspaces;
    temp_2 = height_qm;
    if (temp_2);
    else
	temp_2 = Height_for_prominent_notification_workspaces;
    workspace = make_workspace(7,Qtemporary_workspace,Nil,temp,Nil,temp_1,
	    temp_2,disarm_qm ? FIX((SI_Long)-1L) : Nil);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in))
	put_workspace_on_pane_function(workspace,
		detail_pane(gensym_window),Qcenter,Qcenter,Nil,
		FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    goto next_loop;
  end_loop:;
    force_process_drawing();
    return VALUES_1(workspace);
}

DEFINE_VARIABLE_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm, Qlong_operation_notification_has_been_put_up_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification, Qfixnum_time_at_start_of_current_long_notification);

DEFINE_VARIABLE_WITH_SYMBOL(Current_long_operation_notification_workspace, Qcurrent_long_operation_notification_workspace);

DEFINE_VARIABLE_WITH_SYMBOL(Doing_long_operation_with_notification_qm, Qdoing_long_operation_with_notification_qm);

/* PUT-UP-LONG-OPERATION-NOTIFICATION */
Object put_up_long_operation_notification()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(116,101);
    if (Doing_long_operation_with_notification_qm &&  
	    !TRUEP(Long_operation_notification_has_been_put_up_qm)) {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = 
		IFIX(Fixnum_time_at_start_of_current_long_notification);
	if (gensymed_symbol >= gensymed_symbol_1)
	    temp = FIX(gensymed_symbol - gensymed_symbol_1);
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    temp = FIX(gensymed_symbol + (SI_Long)1L);
	}
	temp_1 = FIXNUM_GE(temp,fixnum_time_interval(FIX((SI_Long)0L)));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return put_up_long_operation_notification_now();
    else
	return VALUES_1(Nil);
}

/* PUT-UP-LONG-OPERATION-NOTIFICATION-NOW */
Object put_up_long_operation_notification_now()
{
    Object workstation, ab_loop_list_, gensym_window, temp;

    x_note_fn_call(116,102);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    temp = Current_long_operation_notification_workspace;
    put_workspace_on_pane_function(temp,detail_pane(gensym_window),Qcenter,
	    Qcenter,Nil,FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    goto next_loop;
  end_loop:;
    force_process_drawing();
    Long_operation_notification_has_been_put_up_qm = T;
    return VALUES_1(Long_operation_notification_has_been_put_up_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(User_defined_logbook_handling_procedure_qm, Quser_defined_logbook_handling_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(User_defined_logbook_handling_procedure_fsn, Quser_defined_logbook_handling_procedure_fsn);

/* G2-REGISTER-LOGBOOK-MESSAGE-HANDLER */
Object g2_register_logbook_message_handler(procedure)
    Object procedure;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object frame_serial_number_setf_arg;
    Object user_defined_logbook_handling_procedure_fsn_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,103);
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
	if (SIMPLE_VECTOR_P(procedure) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure)) > (SI_Long)2L 
		&&  !EQ(ISVREF(procedure,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(procedure,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_declaration_class_description,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ? 
	    TRUEP(check_user_defined_message_handler_arguments(procedure)) 
	    : TRUEP(Nil)) {
	User_defined_logbook_handling_procedure_qm = procedure;
	frame_serial_number_setf_arg = ISVREF(procedure,(SI_Long)3L);
	user_defined_logbook_handling_procedure_fsn_new_value = 
		(FIXNUMP(User_defined_logbook_handling_procedure_fsn) ||  
		!TRUEP(User_defined_logbook_handling_procedure_fsn)) && 
		(FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(User_defined_logbook_handling_procedure_fsn,
		frame_serial_number_setf_arg);
	User_defined_logbook_handling_procedure_fsn = 
		user_defined_logbook_handling_procedure_fsn_new_value;
	return VALUES_1(User_defined_logbook_handling_procedure_fsn);
    }
    else
	return VALUES_1(Nil);
}

/* G2-DEREGISTER-LOGBOOK-MESSAGE-HANDLER */
Object g2_deregister_logbook_message_handler()
{
    x_note_fn_call(116,104);
    reclaim_frame_serial_number(User_defined_logbook_handling_procedure_fsn);
    User_defined_logbook_handling_procedure_qm = Nil;
    User_defined_logbook_handling_procedure_fsn = Nil;
    return VALUES_1(User_defined_logbook_handling_procedure_fsn);
}

/* G2-GET-LOGBOOK-MESSAGE-HANDLER */
Object g2_get_logbook_message_handler()
{
    Object x2, gensymed_symbol, sub_class_bit_vector, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,105);
    if (User_defined_logbook_handling_procedure_qm) {
	if (SIMPLE_VECTOR_P(User_defined_logbook_handling_procedure_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_logbook_handling_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(User_defined_logbook_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(User_defined_logbook_handling_procedure_qm,
		    (SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (SIMPLE_VECTOR_P(User_defined_logbook_handling_procedure_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_logbook_handling_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(User_defined_logbook_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(User_defined_logbook_handling_procedure_qm,
		    (SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		ISVREF(User_defined_logbook_handling_procedure_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(User_defined_logbook_handling_procedure_qm) 
		? EQ(ISVREF(User_defined_logbook_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(User_defined_logbook_handling_procedure_fsn))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(User_defined_logbook_handling_procedure_fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(User_defined_logbook_handling_procedure_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(User_defined_logbook_handling_procedure_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(User_defined_logbook_handling_procedure_qm);
    else
	return make_evaluation_truth_value_function(Falsity);
}

/* INVOKE-USER-DEFINED-LOGBOOK-HANDLING-PROCEDURE */
Object invoke_user_defined_logbook_handling_procedure(message_text_line)
    Object message_text_line;
{
    x_note_fn_call(116,106);
    return invoke_user_defined_message_handler(message_text_line,
	    User_defined_logbook_handling_procedure_qm);
}

/* PASS-LOOP-CHECK-FOR-LOGBOOK-HANDLING-PROCEDURE-P */
Object pass_loop_check_for_logbook_handling_procedure_p()
{
    x_note_fn_call(116,107);
    return pass_loop_check_for_user_defined_message_handler_p(User_defined_logbook_handling_procedure_qm);
}

/* REGISTERED-AND-ACTIVE-LOGBOOK-HANDLING-PROCEDURE-P */
Object registered_and_active_logbook_handling_procedure_p()
{
    Object x2, gensymed_symbol, sub_class_bit_vector, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,108);
    if (SIMPLE_VECTOR_P(User_defined_logbook_handling_procedure_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_logbook_handling_procedure_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(User_defined_logbook_handling_procedure_qm,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(User_defined_logbook_handling_procedure_qm,(SI_Long)1L);
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
	gensymed_symbol = 
		ISVREF(User_defined_logbook_handling_procedure_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(User_defined_logbook_handling_procedure_qm) 
		? EQ(ISVREF(User_defined_logbook_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(User_defined_logbook_handling_procedure_fsn))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(User_defined_logbook_handling_procedure_fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(User_defined_logbook_handling_procedure_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(User_defined_logbook_handling_procedure_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return runnable_p_function(User_defined_logbook_handling_procedure_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(User_defined_message_board_handling_procedure_qm, Quser_defined_message_board_handling_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(User_defined_message_board_handling_procedure_fsn, Quser_defined_message_board_handling_procedure_fsn);

/* G2-REGISTER-MESSAGE-BOARD-MESSAGE-HANDLER */
Object g2_register_message_board_message_handler(procedure)
    Object procedure;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object frame_serial_number_setf_arg;
    Object user_defined_message_board_handling_procedure_fsn_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,109);
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
	if (SIMPLE_VECTOR_P(procedure) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure)) > (SI_Long)2L 
		&&  !EQ(ISVREF(procedure,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(procedure,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_declaration_class_description,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp ? 
	    TRUEP(check_user_defined_message_handler_arguments(procedure)) 
	    : TRUEP(Nil)) {
	User_defined_message_board_handling_procedure_qm = procedure;
	frame_serial_number_setf_arg = ISVREF(procedure,(SI_Long)3L);
	user_defined_message_board_handling_procedure_fsn_new_value = 
		(FIXNUMP(User_defined_message_board_handling_procedure_fsn) 
		||  
		!TRUEP(User_defined_message_board_handling_procedure_fsn)) 
		&& (FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(User_defined_message_board_handling_procedure_fsn,
		frame_serial_number_setf_arg);
	User_defined_message_board_handling_procedure_fsn = 
		user_defined_message_board_handling_procedure_fsn_new_value;
	return VALUES_1(User_defined_message_board_handling_procedure_fsn);
    }
    else
	return VALUES_1(Nil);
}

/* G2-DEREGISTER-MESSAGE-BOARD-MESSAGE-HANDLER */
Object g2_deregister_message_board_message_handler()
{
    x_note_fn_call(116,110);
    reclaim_frame_serial_number(User_defined_message_board_handling_procedure_fsn);
    User_defined_message_board_handling_procedure_qm = Nil;
    User_defined_message_board_handling_procedure_fsn = Nil;
    return VALUES_1(User_defined_message_board_handling_procedure_fsn);
}

/* G2-GET-MESSAGE-BOARD-MESSAGE-HANDLER */
Object g2_get_message_board_message_handler()
{
    Object x2, gensymed_symbol, sub_class_bit_vector, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,111);
    if (User_defined_message_board_handling_procedure_qm) {
	if (SIMPLE_VECTOR_P(User_defined_message_board_handling_procedure_qm) 
		&& 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_message_board_handling_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(User_defined_message_board_handling_procedure_qm,
		    (SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (SIMPLE_VECTOR_P(User_defined_message_board_handling_procedure_qm) 
		&& 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_message_board_handling_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(User_defined_message_board_handling_procedure_qm,
		    (SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)3L);
	temp = 
		SIMPLE_VECTOR_P(User_defined_message_board_handling_procedure_qm) 
		? 
		EQ(ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(User_defined_message_board_handling_procedure_fsn))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(User_defined_message_board_handling_procedure_fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(User_defined_message_board_handling_procedure_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(User_defined_message_board_handling_procedure_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(User_defined_message_board_handling_procedure_qm);
    else
	return make_evaluation_truth_value_function(Falsity);
}

/* INVOKE-USER-DEFINED-MESSAGE-BOARD-HANDLING-PROCEDURE */
Object invoke_user_defined_message_board_handling_procedure(message_text_line)
    Object message_text_line;
{
    x_note_fn_call(116,112);
    return invoke_user_defined_message_handler(message_text_line,
	    User_defined_message_board_handling_procedure_qm);
}

/* PASS-LOOP-CHECK-FOR-MESSAGE-BOARD-HANDLING-PROCEDURE-P */
Object pass_loop_check_for_message_board_handling_procedure_p()
{
    x_note_fn_call(116,113);
    return pass_loop_check_for_user_defined_message_handler_p(User_defined_message_board_handling_procedure_qm);
}

/* REGISTERED-AND-ACTIVE-MESSAGE-BOARD-HANDLING-PROCEDURE-P */
Object registered_and_active_message_board_handling_procedure_p()
{
    Object x2, gensymed_symbol, sub_class_bit_vector, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,114);
    if (SIMPLE_VECTOR_P(User_defined_message_board_handling_procedure_qm) 
	    && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(User_defined_message_board_handling_procedure_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(User_defined_message_board_handling_procedure_qm,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)1L);
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
	gensymed_symbol = 
		ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)3L);
	temp = 
		SIMPLE_VECTOR_P(User_defined_message_board_handling_procedure_qm) 
		? 
		EQ(ISVREF(User_defined_message_board_handling_procedure_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(User_defined_message_board_handling_procedure_fsn))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(User_defined_message_board_handling_procedure_fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(User_defined_message_board_handling_procedure_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(User_defined_message_board_handling_procedure_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return runnable_p_function(User_defined_message_board_handling_procedure_qm);
    else
	return VALUES_1(Nil);
}

static Object Qframe_serial_number_lt_function;  /* frame-serial-number-<-function */

static Object Qframe_serial_number_function;  /* frame-serial-number-function */

/* GET-CURRENT-LOGBOOK-SEQUENCE */
Object get_current_logbook_sequence()
{
    Object list_1, page, ab_loop_list_, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector, sequence;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,115);
    if (current_logbook_qm()) {
	list_1 = Qnil;
	page = Nil;
	ab_loop_list_ = ISVREF(Current_logbook_qm,(SI_Long)20L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	page = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ACCESS_ONCE(ISVREF(page,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
	    list_1 = eval_cons_1(subblock,list_1);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	list_1 = sort_list(list_1,
		SYMBOL_FUNCTION(Qframe_serial_number_lt_function),
		SYMBOL_FUNCTION(Qframe_serial_number_function));
	sequence = allocate_evaluation_sequence(list_1);
	return VALUES_1(sequence);
	return VALUES_1(Qnil);
    }
    else
	return allocate_evaluation_sequence(Nil);
}

/* GET-CURRENT-MESSAGE-BOARD-SEQUENCE */
Object get_current_message_board_sequence()
{
    Object list_1, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object subblock, sub_class_bit_vector, sequence;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(116,116);
    if (current_message_board_qm()) {
	list_1 = Qnil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(Current_message_board_qm,
		(SI_Long)14L));
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
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
	    list_1 = eval_cons_1(subblock,list_1);
	goto next_loop;
      end_loop:
	list_1 = sort_list(list_1,
		SYMBOL_FUNCTION(Qframe_serial_number_lt_function),
		SYMBOL_FUNCTION(Qframe_serial_number_function));
	sequence = allocate_evaluation_sequence(list_1);
	return VALUES_1(sequence);
	return VALUES_1(Qnil);
    }
    else
	return allocate_evaluation_sequence(Nil);
}

void books_INIT()
{
    Object temp, temp_1, temp_2;
    Object reclaim_structure_for_inform_message_information_1, gensymed_symbol;
    Object AB_package, Qg2_get_message_board_message_handler;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_deregister_message_board_message_handler;
    Object Qg2_register_message_board_message_handler, Qbooks;
    Object Qg2_get_logbook_message_handler;
    Object Qg2_deregister_logbook_message_handler;
    Object Qg2_register_logbook_message_handler, Qclasses_which_define;
    Object Qgenerate_spot, Qgenerate_spot_for_page_number, string_constant_91;
    Object list_constant_10, string_constant_88, string_constant_90;
    Object string_constant_15, Qgenerate_spot_for_running_head;
    Object string_constant_89, string_constant_87, Qtext_box;
    Object Qformat_description, string_constant_86, Qrunning_head_format;
    Object list_constant_2, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object string_constant_85, list_constant_9, string_constant_84;
    Object string_constant_26, list_constant_3, Qitem, string_constant_83;
    Object Qdefault_message_board_format, string_constant_82, list_constant_8;
    Object Qmessage_board_format, string_constant_81, Qforeground;
    Object Qslot_value_reclaimer, Qreclaim_inform_message_information_qm_value;
    Object Qinform_message_information_qm, Qinform_message_information;
    Object Qreclaim_structure, Qoutstanding_inform_message_information_count;
    Object Qinform_message_information_structure_memory_usage, Qutilities2;
    Object string_constant_80, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_inform_message_information_g2_struct;
    Object string_constant_79;
    Object Qreclaim_snapshots_of_blocks_related_to_message_value;
    Object string_constant_78, string_constant_77, string_constant_76;
    Object list_constant_7, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object Qsubstitute_class_and_kb_flags, Qmessage_box, string_constant_65;
    Object Qcorresponding_extra_large_font_format_name;
    Object Qextra_large_message_format, Qlarge_message_format;
    Object Qcorresponding_small_font_format_name, Qmessage_format;
    Object string_constant_67, string_constant_66, Qmessage_box_format;
    Object Qclose_log_file, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_log_file_parameters;
    Object Qinstall_system_table;
    Object Qinstall_system_table_for_log_file_parameters, Qslot_putter;
    Object Qput_maximum_number_of_log_files, Qput_when_to_back_up_log_file;
    Object Qput_when_to_close_log_file, Qput_root_name_for_log_files;
    Object Qput_directory_for_log_files, Qput_log_file_enabled_qm;
    Object Qinitialize_maximum_log_file_name_prefix_length_qm, list_constant_6;
    Object Kfuncall, array_constant_3, Qlog_file_name_extension;
    Object Qreclaim_pathname_or_string;
    Object Qwhen_to_back_up_current_log_file_other_than_when_closing;
    Object Qwhen_to_close_current_log_file_and_open_next_one;
    Object Qlog_file_enabled, Qabsent_slot_putter;
    Object Qput_when_to_backup_log_file_where_slot_is_absent;
    Object Qwhen_to_backup_log_file, Ksystem_frame, string_constant_64;
    Object string_constant_63, list_constant_5, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object Kno_initial_value;
    Object Qinstall_system_table_for_message_board_parameters;
    Object Qdeinstall_system_table_for_logbook_parameters;
    Object Qinstall_system_table_for_logbook_parameters;
    Object Qput_initial_width_of_message_board, Qput_margin_for_pages;
    Object Qput_width_for_pages, Qmaximum_number_of_entries;
    Object Qmaximum_number_of_message_board_entries, Qspacing_between_entries;
    Object Qspacing_between_message_board_entries;
    Object Qput_bottom_margin_for_pages_where_slot_is_absent;
    Object Qbottom_margin_for_pages;
    Object Qput_right_margin_for_pages_where_slot_is_absent;
    Object Qright_margin_for_pages;
    Object Qput_top_margin_for_pages_where_slot_is_absent;
    Object Qtop_margin_for_pages;
    Object Qput_left_margin_for_pages_where_slot_is_absent;
    Object Qleft_margin_for_pages;
    Object Qput_height_of_message_board_where_slot_is_absent;
    Object Qheight_of_message_board;
    Object Qput_width_of_message_board_where_slot_is_absent;
    Object Qwidth_of_message_board, Qput_include_date_in_messages;
    Object Qput_prefer_native_message_board, Qhighlight_new_messages;
    Object Qhighlight_new_messages_qm, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, Qput_include_date_in_logbook_messages;
    Object Qput_prefer_native_logbook, Qlog_inform_messages;
    Object Qlog_inform_messages_qm, Qslot_value_writer;
    Object Qwrite_docking_position_spec_from_slot, Qdocking_position_spec;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, Qsystem_table;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object list_constant_4, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, Qpage, Qreclaim_book_this_is_part_of_value;
    Object Qbook_this_is_part_of, Qreclaim_stack_of_pages_value;
    Object Qstack_of_pages, string_constant_25, string_constant_24;
    Object Qnon_kb_workspace, Qwrite_format_from_slot, string_constant_23;
    Object list_constant_1, Qdetail_pane, string_constant_22, Qbook;
    Object string_constant_21, string_constant_20, list_constant;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, Qentity;

    x_note_fn_call(116,117);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qbook = STATIC_SYMBOL("BOOK",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qbook,list_constant);
    string_constant_15 = STATIC_STRING("0");
    string_constant_16 = 
	    STATIC_STRING("1t4z8r83aqy83aqy837oy837oy00001m1l8o1l8l000004z8r83Tdy83Tdy837oy837oy0k001o1m8p83Sy1l83Hy1l8o1l8l000004z8r835py835py837oy837oy00");
    string_constant_17 = 
	    STATIC_STRING("001n1m8p839My1l8o1l8l000004z8r83c9y83c9y837oy837oy00001n1m8p9k1l8o1l8l000004z8r83HFy83HFy837oy837oy00001o1m8p838Py1l83Cy1l8o1l8l");
    string_constant_18 = 
	    STATIC_STRING("000004z8r83eiy83eiy837oy837oy0f001n1l83Ey1l8l1m8p83Sy000004z8r83eqy83eqy837oy837oy03Oz001n1l83Ey1l8l1m8p83Sy000004z8r83ejy83ejy8");
    string_constant_19 = 
	    STATIC_STRING("37oy837oy0u001n1l83Ey1l8l1m8p83Sy000004z8r83ery83ery837oy837oy0a001n1l83Ey1l8l1m8p83Sy00000");
    string_constant_20 = 
	    STATIC_STRING("1v8q1m837oy1l83-+y1o83aqy08o8l1q83Tdyk1m8p83Sy83Hy8o8l1p835py01m8p839My8o8l1p83c9y01m8p9k8o8l1q83HFy01m8p838Py83Cy8o8l1p83eiyf83");
    string_constant_21 = 
	    STATIC_STRING("Ey8l1m8p83Sy1p83eqy3Oz83Ey8l1m8p83Sy1p83ejyu83Ey8l1m8p83Sy1p83erya83Ey8l1m8p83Sy");
    temp = regenerate_optimized_constant(string_constant_15);
    clear_optimized_constants();
    push_optimized_constant(Qstring);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19));
    clear_optimized_constants();
    push_optimized_constant(Qstring);
    add_class_to_environment(9,Qbook,list_constant,Nil,temp,Nil,temp_1,
	    list_constant,
	    regenerate_optimized_constant(LIST_2(string_constant_20,
	    string_constant_21)),Nil);
    Qlogbook = STATIC_SYMBOL("LOGBOOK",AB_package);
    list_constant_1 = STATIC_CONS(Qbook,Qnil);
    check_if_superior_classes_are_defined(Qlogbook,list_constant_1);
    Qdetail_pane = STATIC_SYMBOL("DETAIL-PANE",AB_package);
    string_constant_22 = 
	    STATIC_STRING("1l4z8r835py835py83UNy83UNy01l9k001n1l8o1l8l1m8p839My00000");
    string_constant_23 = STATIC_STRING("1n8q1m83UNy1l837oy1o835py1l9k8o8l");
    temp = regenerate_optimized_constant(string_constant_15);
    clear_optimized_constants();
    push_optimized_constant(Qdetail_pane);
    temp_1 = regenerate_optimized_constant(string_constant_22);
    clear_optimized_constants();
    push_optimized_constant(Qdetail_pane);
    add_class_to_environment(9,Qlogbook,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_23),Nil);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    Qwrite_format_from_slot = STATIC_SYMBOL("WRITE-FORMAT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_format_from_slot,
	    STATIC_FUNCTION(write_format_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qab_format,
	    SYMBOL_FUNCTION(Qwrite_format_from_slot),Qslot_value_writer);
    Qpage = STATIC_SYMBOL("PAGE",AB_package);
    Qnon_kb_workspace = STATIC_SYMBOL("NON-KB-WORKSPACE",AB_package);
    list_constant_3 = STATIC_CONS(Qnon_kb_workspace,Qnil);
    check_if_superior_classes_are_defined(Qpage,list_constant_3);
    string_constant_24 = 
	    STATIC_STRING("1m4z8r83HGy83HGy839dy839dy00001m1l8o1l8l000004z8r835vy835vy839dy839dy00001m1l8o1l8l00000");
    string_constant_25 = 
	    STATIC_STRING("1o8q1m839dy1l832Ay1o83HGy08o8l1o835vy08o8l");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_24);
    add_class_to_environment(9,Qpage,list_constant_3,Nil,temp,Nil,temp_1,
	    list_constant_3,
	    regenerate_optimized_constant(string_constant_25),Nil);
    Page_class_description = 
	    lookup_global_or_kb_specific_property_value(Qpage,
	    Class_description_gkbprop);
    Qstack_of_pages = STATIC_SYMBOL("STACK-OF-PAGES",AB_package);
    Qreclaim_stack_of_pages_value = 
	    STATIC_SYMBOL("RECLAIM-STACK-OF-PAGES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_stack_of_pages_value,
	    STATIC_FUNCTION(reclaim_stack_of_pages_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qstack_of_pages,
	    SYMBOL_FUNCTION(Qreclaim_stack_of_pages_value),
	    Qslot_value_reclaimer);
    Qbook_this_is_part_of = STATIC_SYMBOL("BOOK-THIS-IS-PART-OF",AB_package);
    Qreclaim_book_this_is_part_of_value = 
	    STATIC_SYMBOL("RECLAIM-BOOK-THIS-IS-PART-OF-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_book_this_is_part_of_value,
	    STATIC_FUNCTION(reclaim_book_this_is_part_of_value,NIL,FALSE,2,2));
    mutate_global_property(Qbook_this_is_part_of,
	    SYMBOL_FUNCTION(Qreclaim_book_this_is_part_of_value),
	    Qslot_value_reclaimer);
    Qlogbook_page = STATIC_SYMBOL("LOGBOOK-PAGE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qitem,Qpage);
    check_if_superior_classes_are_defined(Qlogbook_page,list_constant_4);
    string_constant_26 = STATIC_STRING("1l1l83ey");
    string_constant_27 = 
	    STATIC_STRING("1l4z8r83J7y83J7y83UOy83UOy00001n1l8o1l8l1m83Dy73*cy3-1y3-qy3-iy3-hy3-ky3-my3sy3Sy3-my3-ry3-iy3-Xy3Sy3ay3-gy3-hy3-gy3-Xy3Sy3-hy3-");
    string_constant_28 = 
	    STATIC_STRING("ky3Sy3-my3-by3-fy3-Xy3by3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-Yy3-Ty3-ey3-ly3-Xy3gy3Sy3-5y3-gy3-my3-Xy3-ky3-gy3-Ty3-e");
    string_constant_29 = 
	    STATIC_STRING("y3-ey3-ry3Sy3-Vy3-Ty3-gy3Sy3-Uy3-Xy3Sy3-gy3-by3-ey3Sy3-hy3-ky3Sy3-Ty3Sy3-wyut3Sy3-Zy3-Xy3-gy3-ly3-ry3-fy3fy3-my3-by3-fy3-Xy3gy3S");
    string_constant_30 = 
	    STATIC_STRING("y3-5y3-Yy3Sy3-Ty3Sy3-my3-by3-fy3-Xy3ey3Sy3-Ty3-ey3-ey3Sy3-fy3-Xy3-ly3-ly3-Ty3-Zy3-Xy3-ly3Sy3-py3-by3-ey3-ey3Sy3-Uy3-Xy3Sy3-Yy3-h");
    string_constant_31 = 
	    STATIC_STRING("y3-ky3Sy3-my3-ay3-Ty3-my3Sy3-Wy3-Ty3-ry3Sy3-hy3-gy3-ey3-ry3gy3Sy3-Jy3-ay3-Ty3-my3Sy3-wyut3-ay3-Ty3-iy3-iy3-Xy3-gy3-ly3Sy3-Ty3-my");
    string_constant_32 = 
	    STATIC_STRING("3Sy3-fy3-by3-Wy3-gy3-by3-Zy3-ay3-my3xy00000");
    string_constant_33 = 
	    STATIC_STRING("1n8q1n83UOy1m83Ry839dy83ey1p83J7y08o8l1m83Dy73*cy3-1y3-qy3-iy3-hy3-ky3-my3sy3Sy3-my3-ry3-iy3-Xy3Sy3ay3-gy3-hy3-gy3-Xy3Sy3-hy3-ky");
    string_constant_34 = 
	    STATIC_STRING("3Sy3-my3-by3-fy3-Xy3by3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-Yy3-Ty3-ey3-ly3-Xy3gy3Sy3-5y3-gy3-my3-Xy3-ky3-gy3-Ty3-ey3");
    string_constant_35 = 
	    STATIC_STRING("-ey3-ry3Sy3-Vy3-Ty3-gy3Sy3-Uy3-Xy3Sy3-gy3-by3-ey3Sy3-hy3-ky3Sy3-Ty3Sy3-wyut3Sy3-Zy3-Xy3-gy3-ly3-ry3-fy3fy3-my3-by3-fy3-Xy3gy3Sy3");
    string_constant_36 = 
	    STATIC_STRING("-5y3-Yy3Sy3-Ty3Sy3-my3-by3-fy3-Xy3ey3Sy3-Ty3-ey3-ey3Sy3-fy3-Xy3-ly3-ly3-Ty3-Zy3-Xy3-ly3Sy3-py3-by3-ey3-ey3Sy3-Uy3-Xy3Sy3-Yy3-hy3");
    string_constant_37 = 
	    STATIC_STRING("-ky3Sy3-my3-ay3-Ty3-my3Sy3-Wy3-Ty3-ry3Sy3-hy3-gy3-ey3-ry3gy3Sy3-Jy3-ay3-Ty3-my3Sy3-wyut3-ay3-Ty3-iy3-iy3-Xy3-gy3-ly3Sy3-Ty3-my3S");
    string_constant_38 = STATIC_STRING("y3-fy3-by3-Wy3-gy3-by3-Zy3-ay3-my3xy");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32));
    add_class_to_environment(9,Qlogbook_page,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,regenerate_optimized_constant(list(6,
	    string_constant_33,string_constant_34,string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38)),Nil);
    Logbook_page_class_description = 
	    lookup_global_or_kb_specific_property_value(Qlogbook_page,
	    Class_description_gkbprop);
    Qlogbook_parameters = STATIC_SYMBOL("LOGBOOK-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_5 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qlogbook_parameters,list_constant_5);
    string_constant_39 = 
	    STATIC_STRING("13Gy4z8r83eQy83eQy83UPy83UPy031Ly001n1l8o1l8l1m8p83-ey000004z8r83RKy83RKy83UPy83UPy032Cy001n1l8o1l8l1m8p83-ey000004z8r83Uiy83Uiy");
    string_constant_40 = 
	    STATIC_STRING("83UPy83UPy0p001n1l8o1l8l1m8p83-ey000004z8r83ehy83ehy83UPy83UPy0f001n1l8o1l8l1m8p83Sy000004z8r83epy83epy83UPy83UPy03Oz001n1l8o1l8");
    string_constant_41 = 
	    STATIC_STRING("l1m8p83Sy000004z8r83egy83egy83UPy83UPy0u001n1l8o1l8l1m8p83Sy000004z8r83eoy83eoy83UPy83UPy0a001n1l8o1l8l1m8p83Sy000004z8r83ely83e");
    string_constant_42 = 
	    STATIC_STRING("ly83UPy83UPy03-++y001m1l8o1l8l000004z8r83ety83ety83UPy83UPy03-++y001m1l8o1l8l000004z8r83eky83eky83UPy83UPy03-++y001m1l8o1l8l0000");
    string_constant_43 = 
	    STATIC_STRING("04z8r83esy83esy83UPy83UPy03-++y001m1l8o1l8l000004z8r83Uxy83Uxy83UPy83UPy0n001n1l8o1l8l1m8p83-ey000004z8r83Wqy83Wqy83UPy83UPy0l00");
    string_constant_44 = 
	    STATIC_STRING("1n1l8o1l8l1m8p83*7y000004z8r83aby83aby83UPy83UPy0u001n1l8o1l8l1m8p83-ey000004z8r83UMy83UMy83UPy83UPy00001n1l8o1l8l1m8p83Ky000004");
    string_constant_45 = 
	    STATIC_STRING("z8r83Uwy83Uwy83UPy83UPy03=4y001n1l8o1l8l1m8p83*7y000004z8r83Tty83Tty83UPy83UPy08k001n1l8o1l8l1m8p83Ky000004z8r83Y0y83Y0y83UPy83U");
    string_constant_46 = 
	    STATIC_STRING("Py08k001o1m8p83Ky1l8o1l8l1l83Cy000004z8r83S1y83S1y83UPy83UPy00001n1l8o1l8l1m8p83Ky000004z8r83JDy83JDy83UPy83UPy083-by001o1m8p83B");
    string_constant_47 = STATIC_STRING("ry1l8o1l8l1l83Cy00000");
    string_constant_48 = 
	    STATIC_STRING("13Iy8q1n83UPy1l83-sy83ey1p83eQy31Ly8o8l1m8p83-ey1p83RKy32Cy8o8l1m8p83-ey1p83Uiyp8o8l1m8p83-ey1p83ehyf8o8l1m8p83Sy1p83epy3Oz8o8l1");
    string_constant_49 = 
	    STATIC_STRING("m8p83Sy1p83egyu8o8l1m8p83Sy1p83eoya8o8l1m8p83Sy1o83ely3-++y8o8l1o83ety3-++y8o8l1o83eky3-++y8o8l1o83esy3-++y8o8l1p83Uxyn8o8l1m8p8");
    string_constant_50 = 
	    STATIC_STRING("3-ey1p83Wqyl8o8l1m8p83*7y1p83abyu8o8l1m8p83-ey1p83UMy08o8l1m8p83Ky1p83Uwy3=4y8o8l1m8p83*7y1p83Tty8k8o8l1m8p83Ky1q83Y0y8k1m8p83Ky");
    string_constant_51 = 
	    STATIC_STRING("8o8l83Cy1p83S1y08o8l1m8p83Ky1q83JDy83-by1m8p83Bry8o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47));
    add_class_to_environment(9,Qlogbook_parameters,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_4(string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qlogbook_parameters,Logbook_parameters);
    Qbooks = STATIC_SYMBOL("BOOKS",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qlogbook_parameters,Qbooks,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    string_constant_52 = 
	    STATIC_STRING("1o1m83Bry1m9k83hy1m83Bry1m9k83gy1m83Bry1m9k83*hy1m83Bry1m9k83-by");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_52));
    Qdocking_position_spec = STATIC_SYMBOL("DOCKING-POSITION-SPEC",AB_package);
    Qwrite_docking_position_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-DOCKING-POSITION-SPEC-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_docking_position_spec_from_slot,
	    STATIC_FUNCTION(write_docking_position_spec_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdocking_position_spec,
	    SYMBOL_FUNCTION(Qwrite_docking_position_spec_from_slot),
	    Qslot_value_writer);
    Qlog_inform_messages_qm = STATIC_SYMBOL("LOG-INFORM-MESSAGES\?",
	    AB_package);
    Qlog_inform_messages = STATIC_SYMBOL("LOG-INFORM-MESSAGES",AB_package);
    alias_slot_name(3,Qlog_inform_messages_qm,Qlog_inform_messages,
	    Qlogbook_parameters);
    Qinclude_date_in_logbook_messages = 
	    STATIC_SYMBOL("INCLUDE-DATE-IN-LOGBOOK-MESSAGES",AB_package);
    Qinclude_date_in_messages = STATIC_SYMBOL("INCLUDE-DATE-IN-MESSAGES",
	    AB_package);
    alias_slot_name(3,Qinclude_date_in_logbook_messages,
	    Qinclude_date_in_messages,Qlogbook_parameters);
    Qprefer_native_logbook = STATIC_SYMBOL("PREFER-NATIVE-LOGBOOK",AB_package);
    Qprefer_native = STATIC_SYMBOL("PREFER-NATIVE",AB_package);
    Qput_prefer_native_logbook = STATIC_SYMBOL("PUT-PREFER-NATIVE-LOGBOOK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_prefer_native_logbook,
	    STATIC_FUNCTION(put_prefer_native_logbook,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qprefer_native_logbook,
	    SYMBOL_FUNCTION(Qput_prefer_native_logbook),Qslot_putter);
    Qinclude_date = STATIC_SYMBOL("INCLUDE-DATE",AB_package);
    Qput_include_date_in_logbook_messages = 
	    STATIC_SYMBOL("PUT-INCLUDE-DATE-IN-LOGBOOK-MESSAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_include_date_in_logbook_messages,
	    STATIC_FUNCTION(put_include_date_in_logbook_messages,NIL,FALSE,
	    3,3));
    mutate_global_property(Qinclude_date_in_logbook_messages,
	    SYMBOL_FUNCTION(Qput_include_date_in_logbook_messages),
	    Qslot_putter);
    Qmessage_board_parameters = STATIC_SYMBOL("MESSAGE-BOARD-PARAMETERS",
	    AB_package);
    check_if_superior_classes_are_defined(Qmessage_board_parameters,
	    list_constant_5);
    string_constant_53 = 
	    STATIC_STRING("1s4z8r83SEy83SEy83VNy83VNy031Ly001n1l8o1l8l1m8p83-ey000004z8r83S9y83S9y83VNy83VNy032Cy001n1l8o1l8l1m8p83-ey000004z8r83acy83acy83");
    string_constant_54 = 
	    STATIC_STRING("VNy83VNy0u001n1l8o1l8l1m8p83-ey000004z8r83Uuy83Uuy83VNy83VNy0u001n1l8o1l8l1m8p83-ey000004z8r83RTy83RTy83VNy83VNy08k001n1l8o1l8l1");
    string_constant_55 = 
	    STATIC_STRING("m8p83Ky000004z8r83VXy83VXy83VNy83VNy0832by001n1l8o1l8l1m8p834by000004z8r83Y2y83Y2y83VNy83VNy08k001o1m8p83Ky1l8o1l8l1l83Cy000004z");
    string_constant_56 = 
	    STATIC_STRING("8r83S2y83S2y83VNy83VNy00001n1l8o1l8l1m8p83Ky00000");
    string_constant_57 = 
	    STATIC_STRING("1u8q1n83VNy1l83-sy83ey1p83SEy31Ly8o8l1m8p83-ey1p83S9y32Cy8o8l1m8p83-ey1p83acyu8o8l1m8p83-ey1p83Uuyu8o8l1m8p83-ey1p83RTy8k8o8l1m8");
    string_constant_58 = 
	    STATIC_STRING("p83Ky1p83VXy832by8o8l1m8p834by1q83Y2y8k1m8p83Ky8o8l83Cy1p83S2y08o8l1m8p83Ky");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_53,
	    string_constant_54,string_constant_55,string_constant_56));
    add_class_to_environment(9,Qmessage_board_parameters,list_constant_5,
	    Nil,temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_57,
	    string_constant_58)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qmessage_board_parameters,
	    Message_board_parameters);
    record_system_variable(Qmessage_board_parameters,Qbooks,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qhighlight_new_messages_qm = STATIC_SYMBOL("HIGHLIGHT-NEW-MESSAGES\?",
	    AB_package);
    Qhighlight_new_messages = STATIC_SYMBOL("HIGHLIGHT-NEW-MESSAGES",
	    AB_package);
    alias_slot_name(3,Qhighlight_new_messages_qm,Qhighlight_new_messages,Qnil);
    Qprefer_native_message_board = 
	    STATIC_SYMBOL("PREFER-NATIVE-MESSAGE-BOARD",AB_package);
    Qput_prefer_native_message_board = 
	    STATIC_SYMBOL("PUT-PREFER-NATIVE-MESSAGE-BOARD",AB_package);
    SET_SYMBOL_FUNCTION(Qput_prefer_native_message_board,
	    STATIC_FUNCTION(put_prefer_native_message_board,NIL,FALSE,3,3));
    mutate_global_property(Qprefer_native_message_board,
	    SYMBOL_FUNCTION(Qput_prefer_native_message_board),Qslot_putter);
    Qput_include_date_in_messages = 
	    STATIC_SYMBOL("PUT-INCLUDE-DATE-IN-MESSAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_include_date_in_messages,
	    STATIC_FUNCTION(put_include_date_in_messages,NIL,FALSE,3,3));
    mutate_global_property(Qinclude_date_in_messages,
	    SYMBOL_FUNCTION(Qput_include_date_in_messages),Qslot_putter);
    Qinitial_width_of_message_board = 
	    STATIC_SYMBOL("INITIAL-WIDTH-OF-MESSAGE-BOARD",AB_package);
    Qwidth_of_message_board = STATIC_SYMBOL("WIDTH-OF-MESSAGE-BOARD",
	    AB_package);
    Qput_width_of_message_board_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-WIDTH-OF-MESSAGE-BOARD-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_width_of_message_board_where_slot_is_absent,
	    STATIC_FUNCTION(put_width_of_message_board_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qwidth_of_message_board,
	    SYMBOL_FUNCTION(Qput_width_of_message_board_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitial_height_of_message_board = 
	    STATIC_SYMBOL("INITIAL-HEIGHT-OF-MESSAGE-BOARD",AB_package);
    Qheight_of_message_board = STATIC_SYMBOL("HEIGHT-OF-MESSAGE-BOARD",
	    AB_package);
    Qput_height_of_message_board_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-HEIGHT-OF-MESSAGE-BOARD-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_height_of_message_board_where_slot_is_absent,
	    STATIC_FUNCTION(put_height_of_message_board_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qheight_of_message_board,
	    SYMBOL_FUNCTION(Qput_height_of_message_board_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qmargin_for_pages = STATIC_SYMBOL("MARGIN-FOR-PAGES",AB_package);
    Qleft_margin_for_pages = STATIC_SYMBOL("LEFT-MARGIN-FOR-PAGES",AB_package);
    Qput_left_margin_for_pages_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-LEFT-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_left_margin_for_pages_where_slot_is_absent,
	    STATIC_FUNCTION(put_left_margin_for_pages_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qleft_margin_for_pages,
	    SYMBOL_FUNCTION(Qput_left_margin_for_pages_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtop_margin_for_pages = STATIC_SYMBOL("TOP-MARGIN-FOR-PAGES",AB_package);
    Qput_top_margin_for_pages_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TOP-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_top_margin_for_pages_where_slot_is_absent,
	    STATIC_FUNCTION(put_top_margin_for_pages_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtop_margin_for_pages,
	    SYMBOL_FUNCTION(Qput_top_margin_for_pages_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qright_margin_for_pages = STATIC_SYMBOL("RIGHT-MARGIN-FOR-PAGES",
	    AB_package);
    Qput_right_margin_for_pages_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-RIGHT-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_right_margin_for_pages_where_slot_is_absent,
	    STATIC_FUNCTION(put_right_margin_for_pages_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qright_margin_for_pages,
	    SYMBOL_FUNCTION(Qput_right_margin_for_pages_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qbottom_margin_for_pages = STATIC_SYMBOL("BOTTOM-MARGIN-FOR-PAGES",
	    AB_package);
    Qput_bottom_margin_for_pages_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-BOTTOM-MARGIN-FOR-PAGES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_bottom_margin_for_pages_where_slot_is_absent,
	    STATIC_FUNCTION(put_bottom_margin_for_pages_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qbottom_margin_for_pages,
	    SYMBOL_FUNCTION(Qput_bottom_margin_for_pages_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qspacing_between_message_board_entries = 
	    STATIC_SYMBOL("SPACING-BETWEEN-MESSAGE-BOARD-ENTRIES",AB_package);
    Qspacing_between_entries = STATIC_SYMBOL("SPACING-BETWEEN-ENTRIES",
	    AB_package);
    alias_slot_name(3,Qspacing_between_message_board_entries,
	    Qspacing_between_entries,Qmessage_board_parameters);
    Qmaximum_number_of_message_board_entries = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-MESSAGE-BOARD-ENTRIES",
	    AB_package);
    Qmaximum_number_of_entries = STATIC_SYMBOL("MAXIMUM-NUMBER-OF-ENTRIES",
	    AB_package);
    alias_slot_name(3,Qmaximum_number_of_message_board_entries,
	    Qmaximum_number_of_entries,Qmessage_board_parameters);
    Qwidth_for_pages = STATIC_SYMBOL("WIDTH-FOR-PAGES",AB_package);
    Qput_width_for_pages = STATIC_SYMBOL("PUT-WIDTH-FOR-PAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_width_for_pages,
	    STATIC_FUNCTION(put_width_for_pages,NIL,FALSE,3,3));
    mutate_global_property(Qwidth_for_pages,
	    SYMBOL_FUNCTION(Qput_width_for_pages),Qslot_putter);
    Qput_margin_for_pages = STATIC_SYMBOL("PUT-MARGIN-FOR-PAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_margin_for_pages,
	    STATIC_FUNCTION(put_margin_for_pages,NIL,FALSE,3,3));
    mutate_global_property(Qmargin_for_pages,
	    SYMBOL_FUNCTION(Qput_margin_for_pages),Qslot_putter);
    Qput_initial_width_of_message_board = 
	    STATIC_SYMBOL("PUT-INITIAL-WIDTH-OF-MESSAGE-BOARD",AB_package);
    SET_SYMBOL_FUNCTION(Qput_initial_width_of_message_board,
	    STATIC_FUNCTION(put_initial_width_of_message_board,NIL,FALSE,3,3));
    mutate_global_property(Qinitial_width_of_message_board,
	    SYMBOL_FUNCTION(Qput_initial_width_of_message_board),Qslot_putter);
    Qinstall_system_table_for_logbook_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-LOGBOOK-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_logbook_parameters,
	    STATIC_FUNCTION(install_system_table_for_logbook_parameters,
	    NIL,FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_logbook_parameters);
    set_get(Qlogbook_parameters,Qinstall_system_table,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qlogbook_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_logbook_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-LOGBOOK-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_logbook_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_logbook_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_logbook_parameters);
    set_get(Qlogbook_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qlogbook_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qmessage_format_for_books = STATIC_SYMBOL("MESSAGE-FORMAT-FOR-BOOKS",
	    AB_package);
    Qminimum_format_width_for_text_cell = 
	    STATIC_SYMBOL("MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL",AB_package);
    Qinstall_system_table_for_message_board_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-MESSAGE-BOARD-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_message_board_parameters,
	    STATIC_FUNCTION(install_system_table_for_message_board_parameters,
	    NIL,FALSE,1,1));
    temp_2 = 
	    SYMBOL_FUNCTION(Qinstall_system_table_for_message_board_parameters);
    set_get(Qmessage_board_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qmessage_board_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qmessage_format_for_message_board = 
	    STATIC_SYMBOL("MESSAGE-FORMAT-FOR-MESSAGE-BOARD",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    string_constant = STATIC_STRING("");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qdown_arrow_button = STATIC_SYMBOL("DOWN-ARROW-BUTTON",AB_package);
    Qbutton_action_qm = STATIC_SYMBOL("BUTTON-ACTION\?",AB_package);
    Qdo_arrow_action = STATIC_SYMBOL("DO-ARROW-ACTION",AB_package);
    Qbutton_action_data_qm = STATIC_SYMBOL("BUTTON-ACTION-DATA\?",AB_package);
    Qup_arrow_button = STATIC_SYMBOL("UP-ARROW-BUTTON",AB_package);
    string_constant_1 = STATIC_STRING("Page ~d");
    SET_SYMBOL_FUNCTION(Qdo_arrow_action,STATIC_FUNCTION(do_arrow_action,
	    NIL,FALSE,2,2));
    Qshow_operator_logbook_in_this_window_qm = 
	    STATIC_SYMBOL("SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW\?",AB_package);
    Qdefault_workspace_frame_style = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-FRAME-STYLE",AB_package);
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    Qcurrent_message_board_qm = STATIC_SYMBOL("CURRENT-MESSAGE-BOARD\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_message_board_qm,
	    Current_message_board_qm);
    record_system_variable(Qcurrent_message_board_qm,Qbooks,Nil,Qnil,Qnil,
	    Qnil,Qt);
    Qframe_serial_number_of_current_message_board = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-OF-CURRENT-MESSAGE-BOARD",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_serial_number_of_current_message_board,
	    Frame_serial_number_of_current_message_board);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    record_system_variable(Qframe_serial_number_of_current_message_board,
	    Qbooks,Kno_initial_value,Qnil,Qnil,
	    Qreclaim_frame_serial_number,Qt);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcurrent_message_board_qm,
	    STATIC_FUNCTION(current_message_board_qm,NIL,FALSE,0,0));
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qnext_serial_number_to_be_generated = 
	    STATIC_SYMBOL("NEXT-SERIAL-NUMBER-TO-BE-GENERATED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnext_serial_number_to_be_generated,
	    Next_serial_number_to_be_generated);
    record_system_variable(Qnext_serial_number_to_be_generated,Qbooks,
	    FIX((SI_Long)1L),Qnil,Qnil,Qnil,Qt);
    Qcurrent_message_serial_number = 
	    STATIC_SYMBOL("CURRENT-MESSAGE-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_message_serial_number,
	    Current_message_serial_number);
    record_system_variable(Qcurrent_message_serial_number,Qbooks,
	    FIX((SI_Long)1L),Qnil,Qnil,Qnil,Qt);
    Qcurrent_message_unix_time_qm = 
	    STATIC_SYMBOL("CURRENT-MESSAGE-UNIX-TIME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_message_unix_time_qm,
	    Current_message_unix_time_qm);
    record_system_variable(Qcurrent_message_unix_time_qm,Qbooks,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    string_constant_2 = STATIC_STRING("#~d   ");
    string_constant_3 = STATIC_STRING("   ");
    Qlog_file_parameters = STATIC_SYMBOL("LOG-FILE-PARAMETERS",AB_package);
    check_if_superior_classes_are_defined(Qlog_file_parameters,
	    list_constant_5);
    Qclose_log_file = STATIC_SYMBOL("CLOSE-LOG-FILE",AB_package);
    string_constant_59 = 
	    STATIC_STRING("1r4z8r83UKy83UKy83ULy83ULy00001n1l8o1l8l1m8p83Ky000004z8r83Jwy83Jwy83ULy83ULy00001n1l8o1l8l1m8p83DUy000004z8r83ZDy83ZDy83ULy83UL");
    string_constant_60 = 
	    STATIC_STRING("y0+3Cy3-Zy3ky3fy3-ey3-hy3-Zy3fykkkkkkkr3A++y001n1l8o1l8l1m8p83DWy000004z8r83J+y83J+y83ULy83ULy00001p1l8o1l8l1l83Fy1m8p8365y1l83H");
    string_constant_61 = 
	    STATIC_STRING("y000004z8r83eOy83eOy83ULy83ULy01m3-Wy2l3H2+y832Ky001n1l8o1l8l1m8p9k000004z8r83eNy83eNy83ULy83ULy00001n1l8o1l8l1m8p83Aty000004z8r");
    string_constant_62 = 
	    STATIC_STRING("83Uty83Uty83ULy83ULy0u001n1l8o1l8l1m8p83DVy00000");
    string_constant_63 = 
	    STATIC_STRING("1t8q1n83ULy1l83-sy83ey1p83UKy08o8l1m8p83Ky1p83Jwy08o8l1m8p83DUy1p83ZDy5rg2-log-8o8l1m8p83DWy1r83J+y08o8l83Fy1m8p8365y83Hy1p83eOy");
    string_constant_64 = 
	    STATIC_STRING("1m3-Wy2l3H2+y832Ky8o8l1m8p9k1p83eNy08o8l1m8p83Aty1p83Utyu8o8l1m8p83DVy");
    temp = regenerate_optimized_constant(string_constant_26);
    clear_optimized_constants();
    push_optimized_constant(Qclose_log_file);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_59,
	    string_constant_60,string_constant_61,string_constant_62));
    clear_optimized_constants();
    push_optimized_constant(Qclose_log_file);
    add_class_to_environment(9,Qlog_file_parameters,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_63,
	    string_constant_64)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_parameters,Log_file_parameters);
    record_system_variable(Qlog_file_parameters,Qbooks,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    Qwhen_to_back_up_log_file = STATIC_SYMBOL("WHEN-TO-BACK-UP-LOG-FILE",
	    AB_package);
    Qwhen_to_backup_log_file = STATIC_SYMBOL("WHEN-TO-BACKUP-LOG-FILE",
	    AB_package);
    Qput_when_to_backup_log_file_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-WHEN-TO-BACKUP-LOG-FILE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_when_to_backup_log_file_where_slot_is_absent,
	    STATIC_FUNCTION(put_when_to_backup_log_file_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qwhen_to_backup_log_file,
	    SYMBOL_FUNCTION(Qput_when_to_backup_log_file_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qlog_file_enabled_qm = STATIC_SYMBOL("LOG-FILE-ENABLED\?",AB_package);
    Qlog_file_enabled = STATIC_SYMBOL("LOG-FILE-ENABLED",AB_package);
    alias_slot_name(3,Qlog_file_enabled_qm,Qlog_file_enabled,
	    Qlog_file_parameters);
    Qwhen_to_close_log_file = STATIC_SYMBOL("WHEN-TO-CLOSE-LOG-FILE",
	    AB_package);
    Qwhen_to_close_current_log_file_and_open_next_one = 
	    STATIC_SYMBOL("WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE",
	    AB_package);
    alias_slot_name(3,Qwhen_to_close_log_file,
	    Qwhen_to_close_current_log_file_and_open_next_one,
	    Qlog_file_parameters);
    Qwhen_to_back_up_current_log_file_other_than_when_closing = 
	    STATIC_SYMBOL("WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING",
	    AB_package);
    alias_slot_name(3,Qwhen_to_back_up_log_file,
	    Qwhen_to_back_up_current_log_file_other_than_when_closing,
	    Qlog_file_parameters);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qlog_file_outputting_qm = STATIC_SYMBOL("LOG-FILE-OUTPUTTING\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_outputting_qm,Log_file_outputting_qm);
    record_system_variable(Qlog_file_outputting_qm,Qbooks,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qlog_file_writing_message_qm = 
	    STATIC_SYMBOL("LOG-FILE-WRITING-MESSAGE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_writing_message_qm,
	    Log_file_writing_message_qm);
    record_system_variable(Qlog_file_writing_message_qm,Qbooks,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qlog_file_string = STATIC_SYMBOL("LOG-FILE-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_string,Log_file_string);
    record_system_variable(Qlog_file_string,Qbooks,Nil,Qnil,Qnil,Qnil,Qnil);
    Qlog_file_stream = STATIC_SYMBOL("LOG-FILE-STREAM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_stream,Log_file_stream);
    record_system_variable(Qlog_file_stream,Qbooks,Nil,Qnil,Qnil,Qnil,Qnil);
    Qlog_file_default_pathname_qm = 
	    STATIC_SYMBOL("LOG-FILE-DEFAULT-PATHNAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_default_pathname_qm,
	    Log_file_default_pathname_qm);
    Qreclaim_pathname_or_string = 
	    STATIC_SYMBOL("RECLAIM-PATHNAME-OR-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_pathname_or_string,
	    STATIC_FUNCTION(reclaim_pathname_or_string,NIL,FALSE,1,1));
    record_system_variable(Qlog_file_default_pathname_qm,Qbooks,Nil,Qnil,
	    Qnil,Qreclaim_pathname_or_string,Qnil);
    Qlog_file_count = STATIC_SYMBOL("LOG-FILE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_count,Log_file_count);
    record_system_variable(Qlog_file_count,Qbooks,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qlog_file_message_count = STATIC_SYMBOL("LOG-FILE-MESSAGE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_message_count,Log_file_message_count);
    record_system_variable(Qlog_file_message_count,Qbooks,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qlog_file_message_count_at_last_update = 
	    STATIC_SYMBOL("LOG-FILE-MESSAGE-COUNT-AT-LAST-UPDATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_message_count_at_last_update,
	    Log_file_message_count_at_last_update);
    record_system_variable(Qlog_file_message_count_at_last_update,Qbooks,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qlog_file_time_at_last_update = 
	    STATIC_SYMBOL("LOG-FILE-TIME-AT-LAST-UPDATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_time_at_last_update,
	    Log_file_time_at_last_update);
    record_system_variable(Qlog_file_time_at_last_update,Qbooks,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qlog_file_time_at_open = STATIC_SYMBOL("LOG-FILE-TIME-AT-OPEN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_time_at_open,Log_file_time_at_open);
    record_system_variable(Qlog_file_time_at_open,Qbooks,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qlog_file_pathnames = STATIC_SYMBOL("LOG-FILE-PATHNAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_pathnames,Log_file_pathnames);
    record_system_variable(Qlog_file_pathnames,Qbooks,Nil,Qnil,Qnil,Qnil,Qnil);
    Qlog_file_name_extension = STATIC_SYMBOL("LOG-FILE-NAME-EXTENSION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlog_file_name_extension,
	    Log_file_name_extension);
    array_constant_3 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qlog_file_name_extension,array_constant_3);
    Qmaximum_log_file_name_prefix_length_qm = 
	    STATIC_SYMBOL("MAXIMUM-LOG-FILE-NAME-PREFIX-LENGTH\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_log_file_name_prefix_length_qm,
	    Maximum_log_file_name_prefix_length_qm);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_maximum_log_file_name_prefix_length_qm = 
	    STATIC_SYMBOL("INITIALIZE-MAXIMUM-LOG-FILE-NAME-PREFIX-LENGTH\?",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_maximum_log_file_name_prefix_length_qm);
    record_system_variable(Qmaximum_log_file_name_prefix_length_qm,Qbooks,
	    list_constant_6,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_maximum_log_file_name_prefix_length_qm,
	    STATIC_FUNCTION(initialize_maximum_log_file_name_prefix_length_qm,
	    NIL,FALSE,0,0));
    string_constant_4 = STATIC_STRING("Log file is being ~Aabled.");
    string_constant_5 = STATIC_STRING("en");
    string_constant_6 = STATIC_STRING("dis");
    Qput_log_file_enabled_qm = STATIC_SYMBOL("PUT-LOG-FILE-ENABLED\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_log_file_enabled_qm,
	    STATIC_FUNCTION(put_log_file_enabled_qm,NIL,FALSE,3,3));
    mutate_global_property(Qlog_file_enabled_qm,
	    SYMBOL_FUNCTION(Qput_log_file_enabled_qm),Qslot_putter);
    Qdirectory_for_log_files = STATIC_SYMBOL("DIRECTORY-FOR-LOG-FILES",
	    AB_package);
    Qput_directory_for_log_files = 
	    STATIC_SYMBOL("PUT-DIRECTORY-FOR-LOG-FILES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_directory_for_log_files,
	    STATIC_FUNCTION(put_directory_for_log_files,NIL,FALSE,3,3));
    mutate_global_property(Qdirectory_for_log_files,
	    SYMBOL_FUNCTION(Qput_directory_for_log_files),Qslot_putter);
    Qroot_name_for_log_files = STATIC_SYMBOL("ROOT-NAME-FOR-LOG-FILES",
	    AB_package);
    Qput_root_name_for_log_files = 
	    STATIC_SYMBOL("PUT-ROOT-NAME-FOR-LOG-FILES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_root_name_for_log_files,
	    STATIC_FUNCTION(put_root_name_for_log_files,NIL,FALSE,3,3));
    mutate_global_property(Qroot_name_for_log_files,
	    SYMBOL_FUNCTION(Qput_root_name_for_log_files),Qslot_putter);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qgensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    string_constant_7 = STATIC_STRING("~a");
    Qput_when_to_close_log_file = 
	    STATIC_SYMBOL("PUT-WHEN-TO-CLOSE-LOG-FILE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_when_to_close_log_file,
	    STATIC_FUNCTION(put_when_to_close_log_file,NIL,FALSE,3,3));
    mutate_global_property(Qwhen_to_close_log_file,
	    SYMBOL_FUNCTION(Qput_when_to_close_log_file),Qslot_putter);
    Qput_when_to_back_up_log_file = 
	    STATIC_SYMBOL("PUT-WHEN-TO-BACK-UP-LOG-FILE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_when_to_back_up_log_file,
	    STATIC_FUNCTION(put_when_to_back_up_log_file,NIL,FALSE,3,3));
    mutate_global_property(Qwhen_to_back_up_log_file,
	    SYMBOL_FUNCTION(Qput_when_to_back_up_log_file),Qslot_putter);
    Qmaximum_number_of_log_files = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-LOG-FILES",AB_package);
    Qput_maximum_number_of_log_files = 
	    STATIC_SYMBOL("PUT-MAXIMUM-NUMBER-OF-LOG-FILES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_maximum_number_of_log_files,
	    STATIC_FUNCTION(put_maximum_number_of_log_files,NIL,FALSE,3,3));
    mutate_global_property(Qmaximum_number_of_log_files,
	    SYMBOL_FUNCTION(Qput_maximum_number_of_log_files),Qslot_putter);
    Qcurrent_log_file = STATIC_SYMBOL("CURRENT-LOG-FILE",AB_package);
    string_constant_8 = 
	    STATIC_STRING("Error.  Could not open log file ~s: ~a.");
    string_constant_9 = STATIC_STRING("Error.  Could not open log file ~s.");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinstall_system_table_for_log_file_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-LOG-FILE-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_log_file_parameters,
	    STATIC_FUNCTION(install_system_table_for_log_file_parameters,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_log_file_parameters);
    set_get(Qlog_file_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qlog_file_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_log_file_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-LOG-FILE-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_log_file_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_log_file_parameters,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_log_file_parameters);
    set_get(Qlog_file_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qlog_file_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    SET_SYMBOL_FUNCTION(Qclose_log_file,STATIC_FUNCTION(close_log_file,NIL,
	    FALSE,0,0));
    string_constant_10 = 
	    STATIC_STRING("Error in opening Log File.  Invalid directory.");
    string_constant_11 = 
	    STATIC_STRING("Write to Log File ~a failed.  The file is being ~\n             closed.");
    Qcurrent_logbook_qm = STATIC_SYMBOL("CURRENT-LOGBOOK\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_logbook_qm,Current_logbook_qm);
    record_system_variable(Qcurrent_logbook_qm,Qbooks,Nil,Qnil,Qnil,Qnil,Qt);
    Qcurrent_logbook_serial_number_qm = 
	    STATIC_SYMBOL("CURRENT-LOGBOOK-SERIAL-NUMBER\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_logbook_serial_number_qm,
	    Current_logbook_serial_number_qm);
    record_system_variable(Qcurrent_logbook_serial_number_qm,Qbooks,Nil,
	    Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    if (Allow_user_defined_logbook_handlers_p == UNBOUND)
	Allow_user_defined_logbook_handlers_p = T;
    if (Currently_posting_message_on_logbook_p == UNBOUND)
	Currently_posting_message_on_logbook_p = Nil;
    SET_SYMBOL_FUNCTION(Qcurrent_logbook_qm,
	    STATIC_FUNCTION(current_logbook_qm,NIL,FALSE,0,0));
    string_constant_12 = STATIC_STRING("message: ~A");
    Qtrace_outputting_to_file_qm = 
	    STATIC_SYMBOL("TRACE-OUTPUTTING-TO-FILE\?",AB_package);
    Qtracing_file_stream = STATIC_SYMBOL("TRACING-FILE-STREAM",AB_package);
    Qtracing_file_string = STATIC_SYMBOL("TRACING-FILE-STRING",AB_package);
    Qadd_to_logbook = STATIC_SYMBOL("ADD-TO-LOGBOOK",AB_package);
    string_constant_13 = 
	    STATIC_STRING("Error when writing to tracing file ~a.  The file is being closed.");
    Qmessage_box_format = STATIC_SYMBOL("MESSAGE-BOX-FORMAT",AB_package);
    Qmessage_format = STATIC_SYMBOL("MESSAGE-FORMAT",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qmessage_box_format,CONS(Qmessage_format,temp),
	    Qsubstitute_class_and_kb_flags);
    string_constant_65 = 
	    STATIC_STRING("13Ry83-My83*=yl83*1yl83*0yl83**yl83-By083kyk83-=yy83uyn83byq83ayp83Wyq83cyq83wy083iy31Gy83*ay3Bay");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qmessage_format_for_books,
	    regenerate_optimized_constant(string_constant_65),
	    Qformat_description);
    mutate_global_property(Qmessage_format,
	    regenerate_optimized_constant(string_constant_65),
	    Qformat_description);
    Qlarge_message_format = STATIC_SYMBOL("LARGE-MESSAGE-FORMAT",AB_package);
    string_constant_66 = 
	    STATIC_STRING("13Xy83-My83ny1l83-uy83ty3Gy83sy3Dy83*=yl83*1yl83*0yl83**yl83-By083kyk83-=yy83uyn83byq83ayp83Wyq83cyq83wy083iy31Gy83*ay3Bay");
    mutate_global_property(Qlarge_message_format,
	    regenerate_optimized_constant(string_constant_66),
	    Qformat_description);
    Qextra_large_message_format = 
	    STATIC_SYMBOL("EXTRA-LARGE-MESSAGE-FORMAT",AB_package);
    string_constant_67 = 
	    STATIC_STRING("13Xy83-My83ny1l8311y83sy3Ky83ty3Qy83*=yl83*1yl83*0yl83**yl83-By083kyk83-=yy83uyn83byq83ayp83Wyq83cyq83wy083iy31Gy83*ay3Bay");
    mutate_global_property(Qextra_large_message_format,
	    regenerate_optimized_constant(string_constant_67),
	    Qformat_description);
    Qcorresponding_small_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-SMALL-FONT-FORMAT-NAME",AB_package);
    mutate_global_property(Qlarge_message_format,Qmessage_format,
	    Qcorresponding_small_font_format_name);
    Qcorresponding_extra_large_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-EXTRA-LARGE-FONT-FORMAT-NAME",
	    AB_package);
    mutate_global_property(Qlarge_message_format,
	    Qextra_large_message_format,
	    Qcorresponding_extra_large_font_format_name);
    mutate_global_property(Qmessage_format_for_message_board,
	    regenerate_optimized_constant(string_constant_65),
	    Qformat_description);
    Qmessage_box = STATIC_SYMBOL("MESSAGE-BOX",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qmessage_box,CONS(Qmessage,temp),
	    Qsubstitute_class_and_kb_flags);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qitem,Qtext_box);
    check_if_superior_classes_are_defined(Qmessage,list_constant_7);
    string_constant_68 = 
	    STATIC_STRING("1m1m8v9k1m83-Cy53-DyThe width, height, and property attributes should be exported ~\n as with text-box");
    string_constant_69 = 
	    STATIC_STRING("1u4z8r83ry83ry9k9k00001o1l8l1n8p83-dy83Gy1l8o1l83-3y000004z8r83xy83xy9k9k0835ly001o1l8l1l8z1m83Dy5qExport1l83Ey000004z8r83=ky83=");
    string_constant_70 = 
	    STATIC_STRING("ky9k9k00001p1l8l1l8z1l8o1l83Cy1m83Dy53=cyThese values map to text-cell-plist-for-text-box.<br> ~\n<li>magnification: [x-magnifica");
    string_constant_71 = 
	    STATIC_STRING("tion: number, y-magnification: number], ~\n<li>highlight-color: color-symbol, ~\n<li>border-color: color-symbol, ~\n<li>line-color:");
    string_constant_72 = 
	    STATIC_STRING(" color-symbol, <br>000004z8r8327y8327y9k9k0k001q1m8p83Sy1l83Ey1l8l1l8z1l83Ny1m83Dy5rNew api000004z8r8326y8326y9k9k0k001q1m8p83Sy");
    string_constant_73 = 
	    STATIC_STRING("1l83Ey1l8l1l8z1l83Ny1m83Dy5rNew api000004z8r83S5y83S5y9k9k00001n1l8o1l8l1m83Dy5sExport: 000004z8r83Bay83Bay9k9k00001u1l83Ey1l8l1");
    string_constant_74 = 
	    STATIC_STRING("m8p833Sy1l830Yy1l83Hy1l83Fy1l83-4y1l83Ny1l8z1m83Dy5sExport: 000004z8r83aVy83aVy9k9k00001n1l83Ey1l8l1l83Hy000004z8r83VRy83VRy9k9k");
    string_constant_75 = 
	    STATIC_STRING("00001o1l8o1l8l1l83Ny1l83Hy000004z8r83VOy83VOy9k9k00001o1l8o1l8l1l83Ny1l83Hy00000");
    string_constant_76 = 
	    STATIC_STRING("1w8q1o9k1m83Ry83-ly1m8v9k1m83-Cy53-DyThe width, height, and property attributes should be exported ~\n as with text-box1n83ry01n8");
    string_constant_77 = 
	    STATIC_STRING("p83-dy83Gy1o83xy835ly8z1m83Dy5qExport1n83=ky08z1r8327yk1m8p83Sy83Ey8l8z83Ny1r8326yk1m8p83Sy83Ey8l8z83Ny1p83S5y08o8l1m83Dy5sExpor");
    string_constant_78 = 
	    STATIC_STRING("t: 1w83Bay083Ey8l1m8p833Sy830Yy83Hy83Fy83-4y83Ny8z1m83Dy5sExport: 1p83aVy083Ey8l83Hy1q83VRy08o8l83Ny83Hy1q83VOy08o8l83Ny83Hy");
    clear_optimized_constants();
    push_optimized_constant(Qmessage);
    temp = regenerate_optimized_constant(string_constant_68);
    clear_optimized_constants();
    push_optimized_constant(Qmessage);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75));
    clear_optimized_constants();
    push_optimized_constant(Qmessage);
    add_class_to_environment(9,Qmessage,list_constant_7,Nil,temp,Nil,
	    temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_3(string_constant_76,
	    string_constant_77,string_constant_78)),Nil);
    Message_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmessage,
	    Class_description_gkbprop);
    Qsnapshots_of_blocks_related_to_message = 
	    STATIC_SYMBOL("SNAPSHOTS-OF-BLOCKS-RELATED-TO-MESSAGE",AB_package);
    Qreclaim_snapshots_of_blocks_related_to_message_value = 
	    STATIC_SYMBOL("RECLAIM-SNAPSHOTS-OF-BLOCKS-RELATED-TO-MESSAGE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_snapshots_of_blocks_related_to_message_value,
	    STATIC_FUNCTION(reclaim_snapshots_of_blocks_related_to_message_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsnapshots_of_blocks_related_to_message,
	    SYMBOL_FUNCTION(Qreclaim_snapshots_of_blocks_related_to_message_value),
	    Qslot_value_reclaimer);
    if (The_type_description_of_inform_message_information == UNBOUND)
	The_type_description_of_inform_message_information = Nil;
    string_constant_79 = 
	    STATIC_STRING("43Dy8m83j=y1m83j=y8k1l8k0000001m1m83*gy9k1n8y83-4cy1q83-Fuy83-8Ey83wxy83v*y83vPy83-F2yksk0k0");
    temp = The_type_description_of_inform_message_information;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_inform_message_information = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_79));
    Qg2_defstruct_structure_name_inform_message_information_g2_struct = 
	    STATIC_SYMBOL("INFORM-MESSAGE-INFORMATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_inform_message_information_g2_struct,
	    The_type_description_of_inform_message_information,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qinform_message_information = 
	    STATIC_SYMBOL("INFORM-MESSAGE-INFORMATION",AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qinform_message_information,
	    The_type_description_of_inform_message_information,
	    Qtype_description_of_type);
    Qoutstanding_inform_message_information_count = 
	    STATIC_SYMBOL("OUTSTANDING-INFORM-MESSAGE-INFORMATION-COUNT",
	    AB_package);
    Qinform_message_information_structure_memory_usage = 
	    STATIC_SYMBOL("INFORM-MESSAGE-INFORMATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_80 = STATIC_STRING("1q83j=y8s83-Zsy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_inform_message_information_count);
    push_optimized_constant(Qinform_message_information_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_80));
    Qchain_of_available_inform_message_informations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INFORM-MESSAGE-INFORMATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_inform_message_informations,
	    Chain_of_available_inform_message_informations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_inform_message_informations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qinform_message_information_count = 
	    STATIC_SYMBOL("INFORM-MESSAGE-INFORMATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinform_message_information_count,
	    Inform_message_information_count);
    record_system_variable(Qinform_message_information_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_inform_message_informations_vector == UNBOUND)
	Chain_of_available_inform_message_informations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinform_message_information_structure_memory_usage,
	    STATIC_FUNCTION(inform_message_information_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_inform_message_information_count,
	    STATIC_FUNCTION(outstanding_inform_message_information_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_inform_message_information_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_inform_message_information,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qinform_message_information,
	    reclaim_structure_for_inform_message_information_1);
    Qinform_message_information_qm = 
	    STATIC_SYMBOL("INFORM-MESSAGE-INFORMATION\?",AB_package);
    Qreclaim_inform_message_information_qm_value = 
	    STATIC_SYMBOL("RECLAIM-INFORM-MESSAGE-INFORMATION\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_inform_message_information_qm_value,
	    STATIC_FUNCTION(reclaim_inform_message_information_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinform_message_information_qm,
	    SYMBOL_FUNCTION(Qreclaim_inform_message_information_qm_value),
	    Qslot_value_reclaimer);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    New_message_highlight_color = Qforeground;
    array_constant_1 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qhighlight_color = STATIC_SYMBOL("HIGHLIGHT-COLOR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qformat_type = STATIC_SYMBOL("FORMAT-TYPE",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    Qmessage_board_format = STATIC_SYMBOL("MESSAGE-BOARD-FORMAT",AB_package);
    list_constant_8 = STATIC_CONS(Qformat_frame,Qnil);
    check_if_superior_classes_are_defined(Qmessage_board_format,
	    list_constant_8);
    string_constant_81 = 
	    STATIC_STRING("1n4z8r83ady83ady83Dhy83Dhy0u001m1l8o1l8l000004z8r83SBy83SBy83Dhy83Dhy032Cy001l1l8l000004z8r83SAy83SAy83Dhy83Dhy032Cy001l1l8l0000");
    string_constant_82 = 
	    STATIC_STRING("1p8q1m83Dhy1l831Fy1o83adyu8o8l1m83SBy32Cy1m83SAy32Cy");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_81,
	    string_constant_15));
    add_class_to_environment(9,Qmessage_board_format,list_constant_8,Nil,
	    temp,Nil,temp_1,list_constant_8,
	    regenerate_optimized_constant(string_constant_82),Nil);
    Qdefault_message_board_format = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-BOARD-FORMAT",AB_package);
    string_constant_83 = STATIC_STRING("1l83Dhy");
    mutate_global_property(Qdefault_message_board_format,
	    regenerate_optimized_constant(string_constant_83),
	    Qformat_description);
    list_constant_9 = STATIC_CONS(Qitem,list_constant_3);
    check_if_superior_classes_are_defined(Qmessage_board,list_constant_9);
    string_constant_84 = 
	    STATIC_STRING("1l4z8r83*Ly83*Ly83VMy83VMy0p001n1l8l1l8o1m8p83*7y00000");
    string_constant_85 = STATIC_STRING("1n8q1n83VMy1m83Ry832Ay83ey1m83*Lyp");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(string_constant_84);
    add_class_to_environment(9,Qmessage_board,list_constant_9,Nil,temp,Nil,
	    temp_1,list_constant_9,
	    regenerate_optimized_constant(string_constant_85),Nil);
    Message_board_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmessage_board,
	    Class_description_gkbprop);
    if (Send_messages_to_logbook_p == UNBOUND)
	Send_messages_to_logbook_p = Nil;
    if (Send_messages_to_console_p == UNBOUND)
	Send_messages_to_console_p = Nil;
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qadd_to_message_board = STATIC_SYMBOL("ADD-TO-MESSAGE-BOARD",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunhighlight_recent_message = 
	    STATIC_SYMBOL("UNHIGHLIGHT-RECENT-MESSAGE",AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexecute_message_removal_task = 
	    STATIC_SYMBOL("EXECUTE-MESSAGE-REMOVAL-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qunhighlight_recent_message,
	    STATIC_FUNCTION(unhighlight_recent_message,NIL,FALSE,2,2));
    Qtitle_of_book_qm = STATIC_SYMBOL("TITLE-OF-BOOK\?",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qexecute_message_removal_task,
	    STATIC_FUNCTION(execute_message_removal_task,NIL,FALSE,2,2));
    Qrunning_head_format = STATIC_SYMBOL("RUNNING-HEAD-FORMAT",AB_package);
    string_constant_86 = 
	    STATIC_STRING("13Ny83-My83*=yk83*1yk83*0yk83**yk83byk83ayk83Wyk83cyk83kyk83-=yk83-By083iy32qy83*ay32qy");
    mutate_global_property(Qrunning_head_format,
	    regenerate_optimized_constant(string_constant_86),
	    Qformat_description);
    Qrunning_head = STATIC_SYMBOL("RUNNING-HEAD",AB_package);
    list_constant_10 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qrunning_head,list_constant_10);
    string_constant_87 = 
	    STATIC_STRING("1m4z8r83ry83ry83Zby83Zby00001o1l8l1n8p083Gy1l8o1l83-3y000004z8r83xy83xy83Zby83Zby0836Dy001n1l8l1l83Ey1m83Dy53CyExport, writable0");
    string_constant_88 = STATIC_STRING("0000");
    string_constant_89 = 
	    STATIC_STRING("1o8q1m83Zby1l83-ly1n83ry01n8p083Gy1m83xy836Dy");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_87,
	    string_constant_88));
    add_class_to_environment(9,Qrunning_head,list_constant_10,Nil,temp,Nil,
	    temp_1,list_constant_10,
	    regenerate_optimized_constant(string_constant_89),Nil);
    Qgenerate_spot_for_running_head = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-RUNNING-HEAD",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_running_head,
	    STATIC_FUNCTION(generate_spot_for_running_head,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_running_head);
    set_get(Qrunning_head,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qrunning_head,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qpage_number = STATIC_SYMBOL("PAGE-NUMBER",AB_package);
    check_if_superior_classes_are_defined(Qpage_number,list_constant_10);
    string_constant_90 = 
	    STATIC_STRING("1m4z8r83ry83ry835vy835vy00001o1l8l1n8p083Gy1l8o1l83-3y000004z8r83xy83xy835vy835vy0836Dy001n1l8l1l83Ey1m83Dy53CyExport, writable0");
    string_constant_91 = 
	    STATIC_STRING("1o8q1m835vy1l83-ly1n83ry01n8p083Gy1m83xy836Dy");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_90,
	    string_constant_88));
    add_class_to_environment(9,Qpage_number,list_constant_10,Nil,temp,Nil,
	    temp_1,list_constant_10,
	    regenerate_optimized_constant(string_constant_91),Nil);
    Qgenerate_spot_for_page_number = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-PAGE-NUMBER",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_page_number,
	    STATIC_FUNCTION(generate_spot_for_page_number,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_page_number);
    set_get(Qpage_number,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qpage_number,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    string_constant_14 = STATIC_STRING("~a-~a-~a");
    Width_for_prominent_notification_workspaces = FIX((SI_Long)400L);
    Height_for_prominent_notification_workspaces = FIX((SI_Long)100L);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    if (Long_operation_notification_has_been_put_up_qm == UNBOUND)
	Long_operation_notification_has_been_put_up_qm = Nil;
    if (Doing_long_operation_with_notification_qm == UNBOUND)
	Doing_long_operation_with_notification_qm = Nil;
    Quser_defined_logbook_handling_procedure_qm = 
	    STATIC_SYMBOL("USER-DEFINED-LOGBOOK-HANDLING-PROCEDURE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_defined_logbook_handling_procedure_qm,
	    User_defined_logbook_handling_procedure_qm);
    record_system_variable(Quser_defined_logbook_handling_procedure_qm,
	    Qbooks,Nil,Qnil,Qnil,Qnil,Qt);
    Quser_defined_logbook_handling_procedure_fsn = 
	    STATIC_SYMBOL("USER-DEFINED-LOGBOOK-HANDLING-PROCEDURE-FSN",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_defined_logbook_handling_procedure_fsn,
	    User_defined_logbook_handling_procedure_fsn);
    record_system_variable(Quser_defined_logbook_handling_procedure_fsn,
	    Qbooks,Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    Qg2_register_logbook_message_handler = 
	    STATIC_SYMBOL("G2-REGISTER-LOGBOOK-MESSAGE-HANDLER",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_register_logbook_message_handler,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_register_logbook_message_handler,
	    STATIC_FUNCTION(g2_register_logbook_message_handler,NIL,FALSE,
	    1,1));
    Qg2_deregister_logbook_message_handler = 
	    STATIC_SYMBOL("G2-DEREGISTER-LOGBOOK-MESSAGE-HANDLER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_deregister_logbook_message_handler,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_deregister_logbook_message_handler,
	    STATIC_FUNCTION(g2_deregister_logbook_message_handler,NIL,
	    FALSE,0,0));
    Qg2_get_logbook_message_handler = 
	    STATIC_SYMBOL("G2-GET-LOGBOOK-MESSAGE-HANDLER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_logbook_message_handler,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_logbook_message_handler,
	    STATIC_FUNCTION(g2_get_logbook_message_handler,NIL,FALSE,0,0));
    Quser_defined_message_board_handling_procedure_qm = 
	    STATIC_SYMBOL("USER-DEFINED-MESSAGE-BOARD-HANDLING-PROCEDURE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_defined_message_board_handling_procedure_qm,
	    User_defined_message_board_handling_procedure_qm);
    record_system_variable(Quser_defined_message_board_handling_procedure_qm,
	    Qbooks,Nil,Qnil,Qnil,Qnil,Qt);
    Quser_defined_message_board_handling_procedure_fsn = 
	    STATIC_SYMBOL("USER-DEFINED-MESSAGE-BOARD-HANDLING-PROCEDURE-FSN",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_defined_message_board_handling_procedure_fsn,
	    User_defined_message_board_handling_procedure_fsn);
    record_system_variable(Quser_defined_message_board_handling_procedure_fsn,
	    Qbooks,Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    Qg2_register_message_board_message_handler = 
	    STATIC_SYMBOL("G2-REGISTER-MESSAGE-BOARD-MESSAGE-HANDLER",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_register_message_board_message_handler,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_register_message_board_message_handler,
	    STATIC_FUNCTION(g2_register_message_board_message_handler,NIL,
	    FALSE,1,1));
    Qg2_deregister_message_board_message_handler = 
	    STATIC_SYMBOL("G2-DEREGISTER-MESSAGE-BOARD-MESSAGE-HANDLER",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_deregister_message_board_message_handler,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_deregister_message_board_message_handler,
	    STATIC_FUNCTION(g2_deregister_message_board_message_handler,
	    NIL,FALSE,0,0));
    Qg2_get_message_board_message_handler = 
	    STATIC_SYMBOL("G2-GET-MESSAGE-BOARD-MESSAGE-HANDLER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_message_board_message_handler,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_message_board_message_handler,
	    STATIC_FUNCTION(g2_get_message_board_message_handler,NIL,FALSE,
	    0,0));
    Qframe_serial_number_lt_function = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-<-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_serial_number_lt_function,
	    STATIC_FUNCTION(frame_serial_number_lt_function,NIL,FALSE,2,2));
    Qframe_serial_number_function = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_serial_number_function,
	    STATIC_FUNCTION(frame_serial_number_function,NIL,FALSE,1,1));
}
