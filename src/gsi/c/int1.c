/* int1.c
 * Input file:  int1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int1.h"


/* COPY-LIST-USING-ICP-CONSES-FUNCTION */
Object g2int_copy_list_using_icp_conses_function(list_qm)
    Object list_qm;
{
    x_note_fn_call(36,0);
    if (list_qm)
	return g2int_copy_list_using_gensym_conses_1(list_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ICP-LIST-FUNCTION */
Object g2int_reclaim_icp_list_function(list_qm)
    Object list_qm;
{
    x_note_fn_call(36,1);
    if (list_qm)
	return g2int_reclaim_gensym_list_1(list_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ICP-TREE-WITH-TEXT-STRINGS */
Object g2int_reclaim_icp_tree_with_text_strings(tree)
    Object tree;
{
    Object tail, car_1, next_tail;

    x_note_fn_call(36,2);
    tail = tree;
    car_1 = Nil;
    next_tail = Nil;
  next_loop:
    if (ATOM(tail))
	goto end_loop;
    car_1 = CAR(tail);
    next_tail = CDR(tail);
    g2int_reclaim_icp_tree_with_text_strings(car_1);
    g2int_reclaim_gensym_cons_1(tail);
    tail = next_tail;
    goto next_loop;
  end_loop:
    if (g2int_text_string_p(tail))
	g2int_reclaim_text_string(tail);
    return VALUES_1(Nil);
}

Object G2int_blank_traced_icp_byte_column = UNBOUND;

Object G2int_trace_skip_data_service_i_am_alive_messages_p = UNBOUND;

Object G2int_icp_trace_print_message_series_p = UNBOUND;

Object G2int_function_for_icp_value_readerqm_prop = UNBOUND;

Object G2int_icp_read_trace_cutoff_levelqm = UNBOUND;

Object G2int_current_icp_read_trace_level = UNBOUND;

Object G2int_number_of_icp_bytes_left_in_message_series = UNBOUND;

Object G2int_number_of_icp_bytes_ready_to_read = UNBOUND;

/* INSTANTANEOUS-ICP-READER-BYTE-COUNT */
Object g2int_instantaneous_icp_reader_byte_count()
{
    Object temp;

    x_note_fn_call(36,3);
    temp = 
	    FIXNUM_NEGATE(FIXNUM_ADD(G2int_number_of_icp_bytes_left_in_message_series,
	    G2int_number_of_icp_bytes_ready_to_read));
    return VALUES_1(temp);
}

/* EMIT-ICP-READ-TRACE */
Object g2int_emit_icp_read_trace(this_is_prologue_p,byte_count_before_qm,
	    byte_count_after_qm,name_of_reader,qualifier_string_qm,
	    trace_type,report_icp_value_p,icp_value_qm,no_padding_p,message_p)
    Object this_is_prologue_p, byte_count_before_qm, byte_count_after_qm;
    Object name_of_reader, qualifier_string_qm, trace_type, report_icp_value_p;
    Object icp_value_qm, no_padding_p, message_p;
{
    x_note_fn_call(36,4);
    return VALUES_1(Nil);
}

Object G2int_function_for_icp_value_writerqm_prop = UNBOUND;

Object G2int_icp_write_trace_cutoff_levelqm = UNBOUND;

Object G2int_current_icp_write_trace_level = UNBOUND;

Object G2int_number_of_icp_bytes_for_message_series = UNBOUND;

Object G2int_number_of_icp_bytes_to_fill_buffer = UNBOUND;

/* INSTANTANEOUS-ICP-WRITER-BYTE-COUNT */
Object g2int_instantaneous_icp_writer_byte_count()
{
    Object temp;

    x_note_fn_call(36,5);
    temp = FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer);
    return VALUES_1(temp);
}

/* EMIT-ICP-WRITE-TRACE */
Object g2int_emit_icp_write_trace(this_is_prologue_p,byte_count_before_qm,
	    byte_count_after_qm,name_of_writer,qualifier_string_qm,
	    trace_type,report_icp_value_p,icp_value_qm,no_padding_p,message_p)
    Object this_is_prologue_p, byte_count_before_qm, byte_count_after_qm;
    Object name_of_writer, qualifier_string_qm, trace_type, report_icp_value_p;
    Object icp_value_qm, no_padding_p, message_p;
{
    x_note_fn_call(36,6);
    return VALUES_1(Nil);
}

Object G2int_data_service_i_am_alive_messages = UNBOUND;

Object G2int_equivalent_icp_value_type_prop = UNBOUND;

Object G2int_icp_value_reader_function_prop = UNBOUND;

Object G2int_icp_value_write_function_prop = UNBOUND;

Object G2int_icp_value_reclaimer_prop = UNBOUND;

Object G2int_name_of_corresponding_icp_object_index_space_prop = UNBOUND;

Object G2int_access_form_for_corresponding_icp_object_map_prop = UNBOUND;

Object G2int_reclaimer_for_icp_port_entry_prop = UNBOUND;

Object G2int_reclaimer_for_icp_object_prop = UNBOUND;

Object G2int_shutdown_reclaimer_for_icp_object_prop = UNBOUND;

Object G2int_delete_corresponding_objectqm = UNBOUND;

Object G2int_deregister_corresponding_objectqm = UNBOUND;

Object G2int_all_index_space_names = UNBOUND;

Object G2int_inhibit_corresponding_icp_object_making = UNBOUND;

static Object Qg2int_name_of_corresponding_icp_object_index_space;  /* name-of-corresponding-icp-object-index-space */

static Object Qg2int_access_form_for_corresponding_icp_object_map;  /* access-form-for-corresponding-icp-object-map */

/* INITIALIZE-ICP-OBJECT-TYPE-COMPILE */
Object g2int_initialize_icp_object_type_compile(icp_object_type,
	    name_of_corresponding_icp_object_index_space,
	    access_form_for_corresponding_icp_object_map)
    Object icp_object_type, name_of_corresponding_icp_object_index_space;
    Object access_form_for_corresponding_icp_object_map;
{
    x_note_fn_call(36,7);
    g2int_mutate_global_property(icp_object_type,
	    name_of_corresponding_icp_object_index_space,
	    Qg2int_name_of_corresponding_icp_object_index_space);
    g2int_mutate_global_property(icp_object_type,
	    access_form_for_corresponding_icp_object_map,
	    Qg2int_access_form_for_corresponding_icp_object_map);
    return VALUES_1(icp_object_type);
}

static Object Qg2int_reclaimer_for_icp_object;  /* reclaimer-for-icp-object */

static Object Qg2int_shutdown_reclaimer_for_icp_object;  /* shutdown-reclaimer-for-icp-object */

static Object Qg2int_reclaimer_for_icp_port_entry;  /* reclaimer-for-icp-port-entry */

/* INITIALIZE-ICP-OBJECT-TYPE */
Object g2int_initialize_icp_object_type(icp_object_type,
	    icp_object_reclaimer_qm,icp_object_shutdown_reclaimer_qm,
	    name_of_function_to_reclaim_icp_port_entry)
    Object icp_object_type, icp_object_reclaimer_qm;
    Object icp_object_shutdown_reclaimer_qm;
    Object name_of_function_to_reclaim_icp_port_entry;
{
    x_note_fn_call(36,8);
    g2int_mutate_global_property(icp_object_type,icp_object_reclaimer_qm ? 
	    SYMBOL_FUNCTION(icp_object_reclaimer_qm) : Nil,
	    Qg2int_reclaimer_for_icp_object);
    g2int_mutate_global_property(icp_object_type,
	    icp_object_shutdown_reclaimer_qm ? 
	    SYMBOL_FUNCTION(icp_object_shutdown_reclaimer_qm) : Nil,
	    Qg2int_shutdown_reclaimer_for_icp_object);
    g2int_mutate_global_property(icp_object_type,
	    SYMBOL_FUNCTION(name_of_function_to_reclaim_icp_port_entry),
	    Qg2int_reclaimer_for_icp_port_entry);
    return VALUES_1(icp_object_type);
}

static Object Qg2int_ab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_font_map;     /* font-map */

/* ICP-OBJECT-TYPE-GIVEN-ICP-OBJECT */
Object g2int_icp_object_type_given_icp_object(icp_object,
	    name_of_corresponding_icp_object_index_space)
    Object icp_object, name_of_corresponding_icp_object_index_space;
{
    Object type, temp;

    x_note_fn_call(36,9);
    if (SIMPLE_VECTOR_P(icp_object)) {
	type = ISVREF(icp_object,(SI_Long)0L);
	temp = SYMBOLP(type) && EQ(SYMBOL_PACKAGE(type),
		G2int_the_g2_defstruct_package) ? 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
		Qg2int_ab_name_of_unique_structure_type) : Nil;
	if (temp);
	else
	    temp = Nil;
    }
    else if (SYMBOLP(icp_object))
	temp = EQ(name_of_corresponding_icp_object_index_space,
		Qg2int_standard_icp_object_index_space) ? Qsymbol : Nil;
    else if (CONSP(icp_object))
	temp = Qg2int_font_map;
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_icp_message_handler_array = UNBOUND;

Object G2int_icp_message_handler_name_array = UNBOUND;

Object G2int_icp_printing_message_handler_array = UNBOUND;

Object G2int_icp_message_type_code_prop = UNBOUND;

Object G2int_priority_for_icp_priority_category_prop = UNBOUND;

Object G2int_icp_priority_category_for_message_prop = UNBOUND;

Object G2int_icp_priority_categories_for_gsi = UNBOUND;

static Object Qg2int_gspan;        /* gspan */

static Object Qg2int_icp_priority_category_for_message;  /* icp-priority-category-for-message */

static Object Qg2int_icp_message_type_code;  /* icp-message-type-code */

/* ADD-ICP-MESSAGE-TYPE-CODE */
Object g2int_add_icp_message_type_code(icp_message_type,
	    icp_message_type_code,category)
    Object icp_message_type, icp_message_type_code, category;
{
    x_note_fn_call(36,10);
    if ( !EQ(category,Qg2int_gspan))
	g2int_mutate_global_property(icp_message_type,category,
		Qg2int_icp_priority_category_for_message);
    return g2int_mutate_global_property(icp_message_type,
	    icp_message_type_code,Qg2int_icp_message_type_code);
}

/* ADD-ICP-MESSAGE-HANDLER */
Object g2int_add_icp_message_handler(handler_name,icp_message_type_code)
    Object handler_name, icp_message_type_code;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(36,11);
    svref_arg_1 = G2int_icp_message_handler_name_array;
    SVREF(svref_arg_1,icp_message_type_code) = handler_name;
    svref_arg_1 = G2int_icp_message_handler_array;
    svref_new_value = SYMBOL_FUNCTION(handler_name);
    SVREF(svref_arg_1,icp_message_type_code) = svref_new_value;
    return VALUES_1(handler_name);
}

Object G2int_active_icp_sockets = UNBOUND;

/* ADD-TO-ACTIVE-ICP-SOCKETS */
Object g2int_add_to_active_icp_sockets(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(36,12);
    G2int_active_icp_sockets = g2int_gensym_cons_1(icp_socket,
	    G2int_active_icp_sockets);
    return VALUES_1(G2int_active_icp_sockets);
}

Object G2int_maximum_object_passing_bandwidth = UNBOUND;

Object G2int_icp_socket_shutdown_handshake_timeout = UNBOUND;

Object G2int_icp_socket_connect_negotiation_timeout_default = UNBOUND;

Object G2int_icp_connection_closed = UNBOUND;

Object G2int_icp_connection_connect_in_progress = UNBOUND;

Object G2int_icp_connection_running = UNBOUND;

Object G2int_icp_connection_shutdown_acknowledgement_rundown = UNBOUND;

Object G2int_icp_connection_awaiting_acknowledgement = UNBOUND;

Object G2int_icp_socket_listening = UNBOUND;

Object G2int_icp_socket_error = UNBOUND;

Object G2int_newest_icp_version = UNBOUND;

Object G2int_gsi_connection_initializing = UNBOUND;

Object G2int_gsi_connection_established = UNBOUND;

Object G2int_the_type_description_of_socket = UNBOUND;

Object G2int_chain_of_available_sockets = UNBOUND;

Object G2int_socket_count = UNBOUND;

/* RECLAIM-SOCKET-1 */
Object g2int_reclaim_socket_1(socket_1)
    Object socket_1;
{
    Object svref_new_value;

    x_note_fn_call(36,13);
    inline_note_reclaim_cons(socket_1,Nil);
    svref_new_value = G2int_chain_of_available_sockets;
    SVREF(socket_1,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_sockets = socket_1;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SOCKET */
Object g2int_reclaim_structure_for_socket(socket_1)
    Object socket_1;
{
    x_note_fn_call(36,14);
    return g2int_reclaim_socket_1(socket_1);
}

static Object Qg2_defstruct_structure_name_socket_g2_struct;  /* g2-defstruct-structure-name::socket-g2-struct */

/* MAKE-PERMANENT-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_socket_structure_internal()
{
    Object def_structure_socket_variable, socket_count_new_value;
    Object defstruct_g2_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(36,15);
    def_structure_socket_variable = Nil;
    socket_count_new_value = FIXNUM_ADD1(G2int_socket_count);
    G2int_socket_count = socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_socket_variable = Nil;
	gensymed_symbol = (SI_Long)1L;
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
	defstruct_g2_socket_variable = the_array;
	SVREF(defstruct_g2_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_g2_struct;
	def_structure_socket_variable = defstruct_g2_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_socket_variable);
}

/* MAKE-SOCKET-1 */
Object g2int_make_socket_1()
{
    Object def_structure_socket_variable;

    x_note_fn_call(36,16);
    def_structure_socket_variable = G2int_chain_of_available_sockets;
    if (def_structure_socket_variable) {
	G2int_chain_of_available_sockets = 
		ISVREF(def_structure_socket_variable,(SI_Long)0L);
	SVREF(def_structure_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_g2_struct;
    }
    else
	def_structure_socket_variable = 
		g2int_make_permanent_socket_structure_internal();
    inline_note_allocate_cons(def_structure_socket_variable,Nil);
    return VALUES_1(def_structure_socket_variable);
}

Object G2int_the_type_description_of_icp_socket = UNBOUND;

Object G2int_chain_of_available_icp_sockets = UNBOUND;

Object G2int_icp_socket_count = UNBOUND;

/* RECLAIM-ICP-SOCKET-INTERNAL-1 */
Object g2int_reclaim_icp_socket_internal_1(icp_socket)
    Object icp_socket;
{
    Object old_structure_being_reclaimed, thing, schedule_task_qm;
    Object old_structure_being_reclaimed_1, svref_new_value;

    x_note_fn_call(36,17);
    inline_note_reclaim_cons(icp_socket,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = icp_socket;
    thing = ISVREF(icp_socket,(SI_Long)2L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	g2int_reclaim_wide_string(thing);
    SVREF(icp_socket,FIX((SI_Long)2L)) = Nil;
    g2int_reclaim_enclosing_interface_frame_serial_number(ISVREF(icp_socket,
	    (SI_Long)6L));
    SVREF(icp_socket,FIX((SI_Long)6L)) = Nil;
    g2int_reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)10L));
    SVREF(icp_socket,FIX((SI_Long)10L)) = Nil;
    g2int_reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)11L));
    SVREF(icp_socket,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)12L));
    SVREF(icp_socket,FIX((SI_Long)12L)) = Nil;
    g2int_reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)13L));
    SVREF(icp_socket,FIX((SI_Long)13L)) = Nil;
    g2int_reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)14L));
    SVREF(icp_socket,FIX((SI_Long)14L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)16L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)16L)) = Nil;
    g2int_reclaim_icp_version_info(ISVREF(icp_socket,(SI_Long)19L));
    SVREF(icp_socket,FIX((SI_Long)19L)) = Nil;
    g2int_reclaim_i_am_alive_infoqm(ISVREF(icp_socket,(SI_Long)24L));
    SVREF(icp_socket,FIX((SI_Long)24L)) = Nil;
    g2int_reclaim_gsi_extension_data_for_gsi(ISVREF(icp_socket,(SI_Long)29L));
    SVREF(icp_socket,FIX((SI_Long)29L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)34L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)34L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)34L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)35L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)35L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)35L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)36L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)36L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)36L)) = Nil;
    g2int_reclaim_resumable_icp_output_task_queue_vector(ISVREF(icp_socket,
	    (SI_Long)37L));
    SVREF(icp_socket,FIX((SI_Long)37L)) = Nil;
    g2int_reclaim_remote_procedure_call_start_map(ISVREF(icp_socket,
	    (SI_Long)41L));
    SVREF(icp_socket,FIX((SI_Long)41L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)43L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)43L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)44L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)44L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)45L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)45L)) = Nil;
    g2int_reclaim_gensym_tree_1(ISVREF(icp_socket,(SI_Long)46L));
    SVREF(icp_socket,FIX((SI_Long)46L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)47L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)47L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)47L)) = Nil;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)51L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)51L)) = svref_new_value;
    SVREF(icp_socket,FIX((SI_Long)51L)) = Nil;
    thing = ISVREF(icp_socket,(SI_Long)54L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	g2int_reclaim_wide_string(thing);
    SVREF(icp_socket,FIX((SI_Long)54L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_icp_sockets;
    SVREF(icp_socket,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_icp_sockets = icp_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-SOCKET */
Object g2int_reclaim_structure_for_icp_socket(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(36,18);
    return g2int_reclaim_icp_socket_internal_1(icp_socket);
}

static Object Qg2_defstruct_structure_name_icp_socket_g2_struct;  /* g2-defstruct-structure-name::icp-socket-g2-struct */

/* MAKE-PERMANENT-ICP-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_icp_socket_structure_internal()
{
    Object def_structure_icp_socket_variable, icp_socket_count_new_value;
    Object defstruct_g2_icp_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(36,19);
    def_structure_icp_socket_variable = Nil;
    icp_socket_count_new_value = FIXNUM_ADD1(G2int_icp_socket_count);
    G2int_icp_socket_count = icp_socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_socket_variable = Nil;
	gensymed_symbol = (SI_Long)56L;
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
	defstruct_g2_icp_socket_variable = the_array;
	SVREF(defstruct_g2_icp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_socket_g2_struct;
	def_structure_icp_socket_variable = defstruct_g2_icp_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_socket_variable);
}

static Object Qg2int_initial;      /* initial */

static Object Qg2int_unknown;      /* unknown */

/* MAKE-ICP-SOCKET-STRUCTURE-1 */
Object g2int_make_icp_socket_structure_1(type_of_icp_connection,
	    icp_connection_name,icp_connection_state,listener_socket,
	    icp_socket_local_system_name)
    Object type_of_icp_connection, icp_connection_name, icp_connection_state;
    Object listener_socket, icp_socket_local_system_name;
{
    Object def_structure_icp_socket_variable, svref_new_value;

    x_note_fn_call(36,20);
    def_structure_icp_socket_variable = G2int_chain_of_available_icp_sockets;
    if (def_structure_icp_socket_variable) {
	G2int_chain_of_available_icp_sockets = 
		ISVREF(def_structure_icp_socket_variable,(SI_Long)0L);
	SVREF(def_structure_icp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_socket_g2_struct;
    }
    else
	def_structure_icp_socket_variable = 
		g2int_make_permanent_icp_socket_structure_internal();
    inline_note_allocate_cons(def_structure_icp_socket_variable,Nil);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)1L)) = 
	    type_of_icp_connection;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)2L)) = 
	    icp_connection_name;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)15L)) = 
	    icp_connection_state;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)33L)) = 
	    listener_socket;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)49L)) = 
	    icp_socket_local_system_name;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)17L)) = T;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)18L)) = 
	    Qg2int_initial;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)20L)) = Nil;
    ISVREF(def_structure_icp_socket_variable,(SI_Long)21L) = FIX((SI_Long)0L);
    ISVREF(def_structure_icp_socket_variable,(SI_Long)22L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)25L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)27L)) = Nil;
    ISVREF(def_structure_icp_socket_variable,(SI_Long)28L) = FIX((SI_Long)1L);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)29L)) = Nil;
    svref_new_value = G2int_maximum_object_passing_bandwidth;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)30L)) = 
	    svref_new_value;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)37L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)38L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)41L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)42L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)43L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)44L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)46L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)48L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)50L)) = 
	    Qg2int_unknown;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)51L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)54L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)55L)) = Nil;
    return VALUES_1(def_structure_icp_socket_variable);
}

/* RECLAIM-REMOTE-PROCEDURE-CALL-START-MAP */
Object g2int_reclaim_remote_procedure_call_start_map(map_1)
    Object map_1;
{
    x_note_fn_call(36,21);
    if (map_1)
	g2int_reclaim_index_space_1(map_1);
    return VALUES_1(Nil);
}

/* RECLAIM-ENCLOSING-INTERFACE-FRAME-SERIAL-NUMBER */
Object g2int_reclaim_enclosing_interface_frame_serial_number(frame_serial_number)
    Object frame_serial_number;
{
    x_note_fn_call(36,22);
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CALLBACKS */
Object g2int_reclaim_icp_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,23);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-CONNECTION-LOSS-CALLBACKS */
Object g2int_execute_icp_connection_loss_callbacks(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(36,24);
    callback_functions = ISVREF(icp_socket,(SI_Long)10L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,clean_qm);
    goto next_loop;
  end_loop:;
    g2int_deregister_all_icp_connection_loss_callbacks(icp_socket);
    return VALUES_1(Nil);
}

/* REGISTER-ICP-CONNECTION-LOSS-CALLBACK */
Object g2int_register_icp_connection_loss_callback(callback_function,
	    icp_socket)
    Object callback_function, icp_socket;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(36,25);
    gensym_push_modify_macro_arg = callback_function;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)10L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CONNECTION-LOSS-CALLBACKS */
Object g2int_reclaim_icp_connection_loss_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,26);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-CONNECTION-LOSS-CALLBACKS */
Object g2int_deregister_all_icp_connection_loss_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(36,27);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)10L);
    if (callback_functions_qm) {
	g2int_reclaim_gensym_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)10L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-CONNECT-CALLBACKS */
Object g2int_execute_icp_connect_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(36,28);
    callback_functions = ISVREF(icp_socket,(SI_Long)11L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_1(callback_function,icp_socket);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-CONNECT-CALLBACK */
Object g2int_register_icp_connect_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(36,29);
    gensym_push_modify_macro_arg = callback_function;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)11L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)11L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CONNECT-CALLBACKS */
Object g2int_reclaim_icp_connect_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,30);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-CONNECT-CALLBACKS */
Object g2int_deregister_all_icp_connect_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(36,31);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)11L);
    if (callback_functions_qm) {
	g2int_reclaim_gensym_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)11L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-ACCEPT-CALLBACKS */
Object g2int_execute_icp_accept_callbacks(icp_socket,nascent_socket)
    Object icp_socket, nascent_socket;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(36,32);
    callback_functions = ISVREF(icp_socket,(SI_Long)12L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,nascent_socket);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-ACCEPT-CALLBACK */
Object g2int_register_icp_accept_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(36,33);
    gensym_push_modify_macro_arg = callback_function;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)12L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-ACCEPT-CALLBACKS */
Object g2int_reclaim_icp_accept_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,34);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-ACCEPT-CALLBACKS */
Object g2int_deregister_all_icp_accept_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(36,35);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)12L);
    if (callback_functions_qm) {
	g2int_reclaim_gensym_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)12L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-READ-CALLBACKS */
Object g2int_execute_icp_read_callbacks(icp_socket,readable_qm)
    Object icp_socket, readable_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(36,36);
    callback_functions = ISVREF(icp_socket,(SI_Long)14L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,readable_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-READ-CALLBACK */
Object g2int_register_icp_read_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(36,37);
    gensym_push_modify_macro_arg = callback_function;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)14L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)14L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-READ-CALLBACKS */
Object g2int_reclaim_icp_read_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,38);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-READ-CALLBACKS */
Object g2int_deregister_all_icp_read_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(36,39);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)14L);
    if (callback_functions_qm) {
	g2int_reclaim_gensym_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)14L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-WRITE-CALLBACKS */
Object g2int_execute_icp_write_callbacks(icp_socket,writable_qm)
    Object icp_socket, writable_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(36,40);
    callback_functions = ISVREF(icp_socket,(SI_Long)13L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,writable_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-WRITE-CALLBACK */
Object g2int_register_icp_write_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(36,41);
    gensym_push_modify_macro_arg = callback_function;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)13L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)13L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-WRITE-CALLBACKS */
Object g2int_reclaim_icp_write_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(36,42);
    g2int_reclaim_gensym_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-WRITE-CALLBACKS */
Object g2int_deregister_all_icp_write_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(36,43);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)13L);
    if (callback_functions_qm) {
	g2int_reclaim_gensym_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)13L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* NOT-A-LISTENER-P */
Object g2int_not_a_listener_p(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(36,44);
    temp = FIXNUM_NE(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_socket_listening) ? T : Nil;
    return VALUES_1(temp);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object Qg2int_wide_string;  /* wide-string */

/* TWRITE-ICP-SOCKET-CONNECTION-NAME */
Object g2int_twrite_icp_socket_connection_name(icp_socket)
    Object icp_socket;
{
    Object name, accept_pos, pos, remote_name, char_1, code;
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;
    SI_Long limit1, length_1, name_length, i, ab_loop_bind_, thing_1;

    x_note_fn_call(36,45);
    name = g2int_stringw(ISVREF(icp_socket,(SI_Long)2L));
    limit1 = (SI_Long)8L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(name));
    name_length = UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    accept_pos = limit1 < name_length ? search(4,array_constant,name,Kend1,
	    FIX(limit1)) : Nil;
    pos = accept_pos;
    if (pos);
    else
	pos = search(4,array_constant_1,name,Kend1,FIX((SI_Long)1L));
    if (pos);
    else
	pos = FIX(name_length);
    remote_name = accept_pos ? g2int_get_remote_host_name(icp_socket) : Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(pos);
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
    if ( !(IFIX(char_1) == (SI_Long)95L)) {
	code = char_1;
	if (IFIX(code) < (SI_Long)127L)
	    simple_or_wide_character = (SI_Long)97L <= IFIX(code) && 
		    IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) + 
		    (SI_Long)-32L) : code;
	else {
	    simple_or_wide_character = 
		    g2int_unicode_uppercase_if_lowercase(code);
	    if (simple_or_wide_character);
	    else
		simple_or_wide_character = code;
	}
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (remote_name) {
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing_1 = (SI_Long)58L;
	    g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)58L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	g2int_twrite_general_string(remote_name);
    }
    else {
	i = IFIX(pos);
	ab_loop_bind_ = name_length;
	char_1 = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = char_1;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = char_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_do_not_use;   /* do-not-use */

static Object string_constant;     /* "ICP-SOCKET " */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object string_constant_1;   /* " in state ~D (~a)" */

/* ICP-SOCKET-DESCRIPTION */
Object g2int_icp_socket_description(icp_socket)
    Object icp_socket;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, icp_socket_state, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(36,46);
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
	      g2int_tformat(1,string_constant);
	      g2int_twrite_icp_socket_connection_name(icp_socket);
	      temp = ISVREF(icp_socket,(SI_Long)15L);
	      icp_socket_state = ISVREF(icp_socket,(SI_Long)15L);
	      temp_1 = g2int_assq_function(icp_socket_state,list_constant);
	      if (temp_1);
	      else
		  temp_1 = list_constant_1;
	      g2int_tformat(3,string_constant_1,temp,SECOND(temp_1));
	      temp = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* RECLAIM-GSI-EXTENSION-DATA-FOR-GSI */
Object g2int_reclaim_gsi_extension_data_for_gsi(extension_data)
    Object extension_data;
{
    x_note_fn_call(36,47);
    g2int_reclaim_gsi_extension_data(extension_data);
    return VALUES_1(Nil);
}

/* RECLAIM-I-AM-ALIVE-INFO? */
Object g2int_reclaim_i_am_alive_infoqm(i_am_alive_info_qm)
    Object i_am_alive_info_qm;
{
    x_note_fn_call(36,48);
    return VALUES_1(Nil);
}

/* RECLAIM-THINGS-TO-UPDATE-WHEN-UNCLOGGED? */
Object g2int_reclaim_things_to_update_when_uncloggedqm(things_to_update_when_unclogged_qm)
    Object things_to_update_when_unclogged_qm;
{
    x_note_fn_call(36,49);
    return g2int_reclaim_gensym_list_1(things_to_update_when_unclogged_qm);
}

Object G2int_highest_icp_socket_session_id = UNBOUND;

static Object Qg2int_temporary_output;  /* temporary-output */

static Object Qg2int_input;        /* input */

static Object Qg2int_output;       /* output */

static Object Qg2int_icp_connection_timeout_task_1;  /* icp-connection-timeout-task-1 */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* MAKE-ICP-SOCKET */
Object g2int_make_icp_socket(icp_connection_name,type_of_icp_connection,
	    icp_connection_input_handle,icp_connection_output_handle_qm,
	    receive_while_handling_icp_input_qm,
	    transmit_while_writing_icp_qm,icp_connection_open_p,
	    parent_listener_qm,local_system_name,connect_timeout)
    Object icp_connection_name, type_of_icp_connection;
    Object icp_connection_input_handle, icp_connection_output_handle_qm;
    Object receive_while_handling_icp_input_qm, transmit_while_writing_icp_qm;
    Object icp_connection_open_p, parent_listener_qm, local_system_name;
    Object connect_timeout;
{
    Object icp_connection_state, icp_socket, temp;
    Object current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11;
    Object current_task_schedule_modify_arg_12, schedule_task_qm;
    Object old_structure_being_reclaimed, def_structure_schedule_task_variable;
    Object task, ctask, p, v, q, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(36,50);
    icp_connection_state = icp_connection_open_p ? 
	    G2int_icp_connection_running : G2int_icp_connection_closed;
    icp_socket = g2int_make_icp_socket_structure_1(type_of_icp_connection,
	    icp_connection_name,icp_connection_state,parent_listener_qm,
	    local_system_name);
    temp =  !EQ(type_of_icp_connection,Qg2int_temporary_output) ? 
	    g2int_make_icp_port(icp_connection_input_handle,icp_socket,
	    Qg2int_input,receive_while_handling_icp_input_qm) : Nil;
    SVREF(icp_socket,FIX((SI_Long)3L)) = temp;
    temp = icp_connection_output_handle_qm || EQ(type_of_icp_connection,
	    Qg2int_temporary_output) ? 
	    g2int_make_icp_port(icp_connection_output_handle_qm,icp_socket,
	    Qg2int_output,transmit_while_writing_icp_qm) : Nil;
    SVREF(icp_socket,FIX((SI_Long)4L)) = temp;
    temp = FIXNUM_ADD1(G2int_highest_icp_socket_session_id);
    G2int_highest_icp_socket_session_id = temp;
    temp = G2int_highest_icp_socket_session_id;
    SVREF(icp_socket,FIX((SI_Long)40L)) = temp;
    if (FIXNUMP(connect_timeout)) {
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_icp_connection_timeout_task_1);
	current_task_schedule_modify_arg_11 = icp_socket;
	current_task_schedule_modify_arg_12 = connect_timeout;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,G2int_current_schedule_task))
		G2int_current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = schedule_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    temp = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	def_structure_schedule_task_variable = 
		G2int_chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    G2int_chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    g2int_make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	SVREF(task,FIX((SI_Long)4L)) = G2int_lowest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_icp_connection_timeout_task_1;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	SVREF(task,FIX((SI_Long)12L)) = current_task_schedule_modify_arg_12;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
	def_structure_queue_element_variable = 
		G2int_chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    G2int_chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    g2int_make_permanent_queue_element_structure_internal();
	inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = q;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)16L)) = task;
    }
    if (icp_connection_output_handle_qm)
	g2int_gsi_initialize_icp_socket(icp_socket);
    return VALUES_1(icp_socket);
}

static Object Qg2int_icp_connection_timeout_task_2;  /* icp-connection-timeout-task-2 */

/* ICP-CONNECTION-TIMEOUT-TASK-1 */
Object g2int_icp_connection_timeout_task_1(icp_socket,connect_timeout)
    Object icp_socket, connect_timeout;
{
    Object schedule_task_qm, old_structure_being_reclaimed, temp;
    Object future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_11;
    Object def_structure_schedule_task_variable, task;
    char svref_new_value;
    double future_task_schedule_modify_arg_3, aref_new_value;

    x_note_fn_call(36,51);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	temp = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    temp = Nil;
    SVREF(icp_socket,FIX((SI_Long)16L)) = temp;
    future_task_schedule_modify_arg_3 = 
	    DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L) + 
	    (double)IFIX(connect_timeout);
    future_task_schedule_modify_arg_8 = 
	    SYMBOL_FUNCTION(Qg2int_icp_connection_timeout_task_2);
    future_task_schedule_modify_arg_11 = icp_socket;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	temp = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    def_structure_schedule_task_variable = 
	    G2int_chain_of_available_schedule_tasks;
    if (def_structure_schedule_task_variable) {
	G2int_chain_of_available_schedule_tasks = 
		ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_schedule_task_g2_struct;
    }
    else
	def_structure_schedule_task_variable = 
		g2int_make_permanent_schedule_task_structure_internal();
    inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
    task = def_structure_schedule_task_variable;
    temp = ISVREF(task,(SI_Long)1L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,future_task_schedule_modify_arg_3);
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = -1.0;
    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
    svref_new_value =  !TRUEP(T);
    SVREF(task,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
    SVREF(task,FIX((SI_Long)4L)) = G2int_lowest_system_priority;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)7L)) = Qg2int_icp_connection_timeout_task_2;
    SVREF(task,FIX((SI_Long)8L)) = future_task_schedule_modify_arg_8;
    ISVREF(task,(SI_Long)10L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)11L)) = future_task_schedule_modify_arg_11;
    g2int_future_task_schedule_2(task);
    SVREF(icp_socket,FIX((SI_Long)16L)) = task;
    return VALUES_1(Nil);
}

static Object Qg2int_connection_attempt_timed_out;  /* connection-attempt-timed-out */

/* ICP-CONNECTION-TIMEOUT-TASK-2 */
Object g2int_icp_connection_timeout_task_2(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(36,52);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)16L)) = svref_new_value;
    g2int_shutdown_icp_socket_connection(2,icp_socket,
	    Qg2int_connection_attempt_timed_out);
    return VALUES_1(Nil);
}

/* ICP-CONNECTION-OPEN-P */
Object g2int_icp_connection_open_p(icp_socket_structure)
    Object icp_socket_structure;
{
    Object icp_connection_state, temp;

    x_note_fn_call(36,53);
    icp_connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp =  !(FIXNUM_EQ(icp_connection_state,G2int_icp_connection_closed) 
	    || FIXNUM_EQ(icp_connection_state,
	    G2int_icp_connection_awaiting_acknowledgement) || 
	    FIXNUM_EQ(icp_connection_state,
	    G2int_icp_connection_connect_in_progress)) ? T : Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-IN-PROGRESS-P */
Object g2int_icp_connection_in_progress_p(icp_socket_structure)
    Object icp_socket_structure;
{
    Object icp_connection_state, temp;

    x_note_fn_call(36,54);
    icp_connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(icp_connection_state,
	    G2int_icp_connection_connect_in_progress) ? T : Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-BEING-SHUTDOWN? */
Object g2int_icp_connection_being_shutdownqm(icp_socket_structure)
    Object icp_socket_structure;
{
    Object connection_state, temp;

    x_note_fn_call(36,55);
    connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(connection_state,
	    G2int_icp_connection_awaiting_acknowledgement) ? T : Nil;
    if (temp);
    else
	temp = FIXNUM_EQ(connection_state,
		G2int_icp_connection_shutdown_acknowledgement_rundown) ? T 
		: Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-CAN-PROCESS-MESSAGES? */
Object g2int_icp_connection_can_process_messagesqm(icp_socket_structure)
    Object icp_socket_structure;
{
    Object connection_state, temp;

    x_note_fn_call(36,56);
    connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(connection_state,G2int_icp_connection_running) ? T : Nil;
    if (temp);
    else
	temp = FIXNUM_EQ(connection_state,
		G2int_icp_connection_awaiting_acknowledgement) ? T : Nil;
    return VALUES_1(temp);
}

Object G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors = UNBOUND;

Object G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors = UNBOUND;

/* FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTOR-MEMORY-USAGE */
Object g2int_frame_serial_number_to_item_table_hash_vector_67_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(36,57);
    temp = 
	    G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors;
    temp = FIXNUM_TIMES(temp,g2int_bytes_per_typed_simple_array(T,
	    FIX((SI_Long)67L)));
    return VALUES_1(temp);
}

/* OUT-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS */
Object g2int_out_frame_serial_number_to_item_table_hash_vector_67_vectors()
{
    Object temp;

    x_note_fn_call(36,58);
    temp = 
	    FIXNUM_MINUS(G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    length(G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTOR-INTERNAL */
Object g2int_make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal()
{
    Object count_of_frame_serial_number_to_item_table_hash_vector_67_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(36,59);
    count_of_frame_serial_number_to_item_table_hash_vector_67_vectors_new_value 
	    = 
	    FIXNUM_ADD1(G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors);
    G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors 
	    = 
	    count_of_frame_serial_number_to_item_table_hash_vector_67_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)67L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qg2int_gensym;       /* gensym */

/* MAKE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR */
Object g2int_make_frame_serial_number_to_item_table_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(36,60);
    if (G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors) 
		{
	temp = 
		M_CAR(G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors);
	temp_1 = 
		M_CDR(G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors);
	inline_note_reclaim_cons(G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors,
		Qg2int_gensym);
	cdr_arg = 
		G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors;
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	G2int_available_gensym_conses = 
		G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors;
	G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors 
		= temp_1;
    }
    else
	temp = 
		g2int_make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR */
Object g2int_reclaim_frame_serial_number_to_item_table_hash_vector(frame_serial_number_to_item_table_hash_vector_67_vector)
    Object frame_serial_number_to_item_table_hash_vector_67_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(36,61);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = 
	    frame_serial_number_to_item_table_hash_vector_67_vector;
    cdr_new_value = 
	    G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors 
	    = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MUTATE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH-TREE-ENTRY */
Object g2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry(entry_cons,
	    new_key,new_entry)
    Object entry_cons, new_key, new_entry;
{
    x_note_fn_call(36,62);
    g2int_note_item_deleted_from_frame_serial_number_table(M_CDR(entry_cons));
    M_CAR(entry_cons) = new_key;
    M_CDR(entry_cons) = new_entry;
    return VALUES_1(Nil);
}

Object G2int_fp_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry = UNBOUND;

/* CLEAR-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE */
Object g2int_clear_frame_serial_number_to_item_table_tree(frame_serial_number_to_item_table_tree_for_hash_binary_tree)
    Object frame_serial_number_to_item_table_tree_for_hash_binary_tree;
{
    Object element_qm, temp, gensymed_symbol, old_entry;
    Object result;

    x_note_fn_call(36,63);
    element_qm = Nil;
  next_loop:
    element_qm = 
	    CDR(frame_serial_number_to_item_table_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop;
    temp = ISVREF(element_qm,(SI_Long)3L);
    gensymed_symbol = CAAR(temp);
    result = g2int_delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,
	    frame_serial_number_to_item_table_tree_for_hash_binary_tree,
	    g2int_sxhashw(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    g2int_note_item_deleted_from_frame_serial_number_table(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(frame_serial_number_to_item_table_tree_for_hash_binary_tree);
}

static Object Qg2int_frame_serial_number_to_item_table_tree_for_hash;  /* frame-serial-number-to-item-table-tree-for-hash */

/* MAKE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_make_frame_serial_number_to_item_table()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(36,64);
    new_vector = g2int_make_frame_serial_number_to_item_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = 
	    Qg2int_frame_serial_number_to_item_table_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* FLATTEN-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_flatten_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(36,65);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    subtree = ISVREF(frame_serial_number_to_item_table_hash_table,index_1);
    if (subtree) {
	temp = g2int_flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_clear_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(36,66);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    g2int_clear_frame_serial_number_to_item_table_tree(ISVREF(frame_serial_number_to_item_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_reclaim_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    Object frame_serial_number_to_item_table_tree_for_hash_binary_tree;
    Object element_qm, gensymed_symbol, old_entry, cdr_new_value, temp;
    SI_Long index_1;
    Object result;

    x_note_fn_call(36,67);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    frame_serial_number_to_item_table_tree_for_hash_binary_tree = 
	    ISVREF(frame_serial_number_to_item_table_hash_table,index_1);
    element_qm = Nil;
  next_loop_1:
    element_qm = 
	    M_CDR(frame_serial_number_to_item_table_tree_for_hash_binary_tree);
    if ( !TRUEP(element_qm))
	goto end_loop_1;
    gensymed_symbol = M_CAR(M_CAR(ISVREF(element_qm,(SI_Long)3L)));
    result = g2int_delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
	    gensymed_symbol,
	    frame_serial_number_to_item_table_tree_for_hash_binary_tree,
	    g2int_sxhashw(gensymed_symbol));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    g2int_note_item_deleted_from_frame_serial_number_table(old_entry);
    goto next_loop_1;
  end_loop_1:
    inline_note_reclaim_cons(frame_serial_number_to_item_table_tree_for_hash_binary_tree,
	    Qg2int_gensym);
    cdr_new_value = G2int_available_gensym_conses;
    M_CDR(frame_serial_number_to_item_table_tree_for_hash_binary_tree) = 
	    cdr_new_value;
    G2int_available_gensym_conses = 
	    frame_serial_number_to_item_table_tree_for_hash_binary_tree;
    ISVREF(frame_serial_number_to_item_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    g2int_reclaim_frame_serial_number_to_item_table_hash_vector(frame_serial_number_to_item_table_hash_table);
    return VALUES_1(temp);
}

/* RECLAIM-IF-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_reclaim_if_frame_serial_number_to_item_table(table_qm)
    Object table_qm;
{
    x_note_fn_call(36,68);
    if (table_qm)
	g2int_reclaim_frame_serial_number_to_item_table(table_qm);
    return VALUES_1(Nil);
}

Object G2int_available_variable_fill_icp_buffer_4096_vectors = UNBOUND;

Object G2int_count_of_variable_fill_icp_buffer_4096_vectors = UNBOUND;

static Object list_constant_2;     /* # */

/* VARIABLE-FILL-ICP-BUFFER-4096-VECTOR-MEMORY-USAGE */
Object g2int_variable_fill_icp_buffer_4096_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(36,69);
    temp = G2int_count_of_variable_fill_icp_buffer_4096_vectors;
    temp = FIXNUM_TIMES(temp,
	    g2int_bytes_per_typed_simple_array(list_constant_2,
	    FIX((SI_Long)4096L)));
    return VALUES_1(temp);
}

/* OUT-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS */
Object g2int_out_variable_fill_icp_buffer_4096_vectors()
{
    Object temp;

    x_note_fn_call(36,70);
    temp = 
	    FIXNUM_MINUS(G2int_count_of_variable_fill_icp_buffer_4096_vectors,
	    length(G2int_available_variable_fill_icp_buffer_4096_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-VARIABLE-FILL-ICP-BUFFER-4096-VECTOR-INTERNAL */
Object g2int_make_permanent_variable_fill_icp_buffer_4096_vector_internal()
{
    Object count_of_variable_fill_icp_buffer_4096_vectors_new_value, temp;
    XDeclare_area(1);

    x_note_fn_call(36,71);
    count_of_variable_fill_icp_buffer_4096_vectors_new_value = 
	    FIXNUM_ADD1(G2int_count_of_variable_fill_icp_buffer_4096_vectors);
    G2int_count_of_variable_fill_icp_buffer_4096_vectors = 
	    count_of_variable_fill_icp_buffer_4096_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)4096L),Kelement_type,list_constant_2);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-VARIABLE-FILL-ICP-BUFFER */
Object g2int_make_variable_fill_icp_buffer()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(36,72);
    if (G2int_available_variable_fill_icp_buffer_4096_vectors) {
	temp = M_CAR(G2int_available_variable_fill_icp_buffer_4096_vectors);
	temp_1 = M_CDR(G2int_available_variable_fill_icp_buffer_4096_vectors);
	inline_note_reclaim_cons(G2int_available_variable_fill_icp_buffer_4096_vectors,
		Qg2int_gensym);
	cdr_arg = G2int_available_variable_fill_icp_buffer_4096_vectors;
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	G2int_available_gensym_conses = 
		G2int_available_variable_fill_icp_buffer_4096_vectors;
	G2int_available_variable_fill_icp_buffer_4096_vectors = temp_1;
    }
    else
	temp = 
		g2int_make_permanent_variable_fill_icp_buffer_4096_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-VARIABLE-FILL-ICP-BUFFER */
Object g2int_reclaim_variable_fill_icp_buffer(variable_fill_icp_buffer_4096_vector)
    Object variable_fill_icp_buffer_4096_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(36,73);
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = variable_fill_icp_buffer_4096_vector;
    cdr_new_value = G2int_available_variable_fill_icp_buffer_4096_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    G2int_available_variable_fill_icp_buffer_4096_vectors = gensymed_symbol;
    return VALUES_1(Nil);
}

Object G2int_recycled_variable_fill_icp_buffers = UNBOUND;

Object G2int_transmitted_variable_fill_icp_buffers = UNBOUND;

Object G2int_the_type_description_of_icp_buffer = UNBOUND;

Object G2int_chain_of_available_icp_buffers = UNBOUND;

Object G2int_icp_buffer_count = UNBOUND;

/* RECLAIM-ICP-BUFFER-INTERNAL-1 */
Object g2int_reclaim_icp_buffer_internal_1(icp_buffer)
    Object icp_buffer;
{
    Object old_structure_being_reclaimed, vector_1, svref_new_value;

    x_note_fn_call(36,74);
    inline_note_reclaim_cons(icp_buffer,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = icp_buffer;
    vector_1 = ISVREF(icp_buffer,(SI_Long)4L);
    if (vector_1)
	g2int_reclaim_variable_fill_icp_buffer(vector_1);
    SVREF(icp_buffer,FIX((SI_Long)4L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_icp_buffers;
    SVREF(icp_buffer,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_icp_buffers = icp_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-BUFFER */
Object g2int_reclaim_structure_for_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    x_note_fn_call(36,75);
    return g2int_reclaim_icp_buffer_internal_1(icp_buffer);
}

static Object Qg2_defstruct_structure_name_icp_buffer_g2_struct;  /* g2-defstruct-structure-name::icp-buffer-g2-struct */

/* MAKE-PERMANENT-ICP-BUFFER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_icp_buffer_structure_internal()
{
    Object def_structure_icp_buffer_variable, icp_buffer_count_new_value;
    Object defstruct_g2_icp_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(36,76);
    def_structure_icp_buffer_variable = Nil;
    icp_buffer_count_new_value = FIXNUM_ADD1(G2int_icp_buffer_count);
    G2int_icp_buffer_count = icp_buffer_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_buffer_variable = Nil;
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
	defstruct_g2_icp_buffer_variable = the_array;
	SVREF(defstruct_g2_icp_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_buffer_g2_struct;
	def_structure_icp_buffer_variable = defstruct_g2_icp_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_buffer_variable);
}

/* MAKE-ICP-BUFFER-INTERNAL-1 */
Object g2int_make_icp_buffer_internal_1(icp_buffer_vector)
    Object icp_buffer_vector;
{
    Object def_structure_icp_buffer_variable;

    x_note_fn_call(36,77);
    def_structure_icp_buffer_variable = G2int_chain_of_available_icp_buffers;
    if (def_structure_icp_buffer_variable) {
	G2int_chain_of_available_icp_buffers = 
		ISVREF(def_structure_icp_buffer_variable,(SI_Long)0L);
	SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_buffer_g2_struct;
    }
    else
	def_structure_icp_buffer_variable = 
		g2int_make_permanent_icp_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_icp_buffer_variable,Nil);
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)4L)) = 
	    icp_buffer_vector;
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_icp_buffer_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_icp_buffer_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_icp_buffer_variable);
}

Object G2int_recycled_icp_buffers = UNBOUND;

/* RECLAIM-ICP-BUFFER */
Object g2int_reclaim_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    Object ref, car_new_value;

    x_note_fn_call(36,78);
    ref = ISVREF(icp_buffer,(SI_Long)5L);
    if (ref) {
	car_new_value = FIXNUM_SUB1(CAR(ref));
	if ((SI_Long)0L == IFIX(M_CAR(ref) = car_new_value))
	    g2int_reclaim_gensym_cons_1(ref);
	else
	    SVREF(icp_buffer,FIX((SI_Long)4L)) = Nil;
	SVREF(icp_buffer,FIX((SI_Long)5L)) = Nil;
    }
    g2int_reclaim_icp_buffer_internal_1(icp_buffer);
    return VALUES_1(Nil);
}

/* COPY-ICP-BUFFER */
Object g2int_copy_icp_buffer(buffer)
    Object buffer;
{
    Object copy, temp, ref;

    x_note_fn_call(36,79);
    copy = g2int_make_icp_buffer_internal_1(ISVREF(buffer,(SI_Long)4L));
    temp = ISVREF(buffer,(SI_Long)2L);
    SVREF(copy,FIX((SI_Long)2L)) = temp;
    temp = ISVREF(buffer,(SI_Long)3L);
    SVREF(copy,FIX((SI_Long)3L)) = temp;
    ref = ISVREF(buffer,(SI_Long)5L);
    if ( !TRUEP(ref)) {
	ref = g2int_gensym_cons_1(FIX((SI_Long)1L),Nil);
	SVREF(buffer,FIX((SI_Long)5L)) = ref;
    }
    temp = FIXNUM_ADD1(CAR(ref));
    M_CAR(ref) = temp;
    SVREF(copy,FIX((SI_Long)5L)) = ref;
    return VALUES_1(copy);
}

/* ENSURE-ICP-BUFFER-VECTOR-WRITABILITY */
Object g2int_ensure_icp_buffer_vector_writability(buffer,ref)
    Object buffer, ref;
{
    Object temp;

    x_note_fn_call(36,80);
    if (ref) {
	temp = FIXNUM_SUB1(CAR(ref));
	M_CAR(ref) = temp;
	SVREF(buffer,FIX((SI_Long)5L)) = Nil;
	if ( !((SI_Long)0L == IFIX(CAR(ref)))) {
	    temp = g2int_copy_icp_buffer_vector(ISVREF(buffer,(SI_Long)4L),
		    g2int_make_variable_fill_icp_buffer(),ISVREF(buffer,
		    (SI_Long)2L),ISVREF(buffer,(SI_Long)3L));
	    SVREF(buffer,FIX((SI_Long)4L)) = temp;
	}
    }
    return VALUES_1(Nil);
}

/* COPY-ICP-BUFFER-VECTOR */
Object g2int_copy_icp_buffer_vector(buffer_vector,copy_vector,buffer_start,
	    buffer_end)
    Object buffer_vector, copy_vector, buffer_start, buffer_end;
{
    SI_Long icp_byte_index, ab_loop_bind_, aref_new_value;

    x_note_fn_call(36,81);
    icp_byte_index = IFIX(buffer_start);
    ab_loop_bind_ = IFIX(buffer_end);
  next_loop:
    if (icp_byte_index >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = UBYTE_8_ISAREF_1(buffer_vector,icp_byte_index);
    UBYTE_8_ISASET_1(copy_vector,icp_byte_index,aref_new_value);
    icp_byte_index = icp_byte_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(copy_vector);
}

/* COPY-ICP-BUFFER-CHAIN */
Object g2int_copy_icp_buffer_chain(buffer_chain)
    Object buffer_chain;
{
    Object first_copy, previous_buffer, buffer, previous_copy, copy;
    Object ab_loop_iter_flag_, temp;

    x_note_fn_call(36,82);
    if (buffer_chain) {
	first_copy = g2int_copy_icp_buffer(buffer_chain);
	previous_buffer = buffer_chain;
	buffer = Nil;
	previous_copy = first_copy;
	copy = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	buffer = ISVREF(previous_buffer,(SI_Long)1L);
	if ( !TRUEP(buffer))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    previous_copy = copy;
	copy = g2int_copy_icp_buffer(buffer);
	SVREF(previous_copy,FIX((SI_Long)1L)) = copy;
	ab_loop_iter_flag_ = Nil;
	previous_buffer = buffer;
	goto next_loop;
      end_loop:
	temp = first_copy;
	goto end;
	temp = Qnil;
      end:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_icp_port = UNBOUND;

Object G2int_chain_of_available_icp_ports = UNBOUND;

Object G2int_icp_port_count = UNBOUND;

/* RECLAIM-ICP-PORT-INTERNAL-1 */
Object g2int_reclaim_icp_port_internal_1(icp_port)
    Object icp_port;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(36,83);
    inline_note_reclaim_cons(icp_port,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = icp_port;
    g2int_reclaim_if_index_space(ISVREF(icp_port,(SI_Long)8L));
    SVREF(icp_port,FIX((SI_Long)8L)) = Nil;
    g2int_reclaim_if_index_space(ISVREF(icp_port,(SI_Long)9L));
    SVREF(icp_port,FIX((SI_Long)9L)) = Nil;
    g2int_reclaim_if_index_space(ISVREF(icp_port,(SI_Long)10L));
    SVREF(icp_port,FIX((SI_Long)10L)) = Nil;
    g2int_reclaim_if_frame_serial_number_to_item_table(ISVREF(icp_port,
	    (SI_Long)11L));
    SVREF(icp_port,FIX((SI_Long)11L)) = Nil;
    g2int_nil_out_car_of_cons(ISVREF(icp_port,(SI_Long)18L));
    SVREF(icp_port,FIX((SI_Long)18L)) = Nil;
    g2int_reclaim_if_index_space(ISVREF(icp_port,(SI_Long)19L));
    SVREF(icp_port,FIX((SI_Long)19L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_icp_ports;
    SVREF(icp_port,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_icp_ports = icp_port;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-PORT */
Object g2int_reclaim_structure_for_icp_port(icp_port)
    Object icp_port;
{
    x_note_fn_call(36,84);
    return g2int_reclaim_icp_port_internal_1(icp_port);
}

static Object Qg2_defstruct_structure_name_icp_port_g2_struct;  /* g2-defstruct-structure-name::icp-port-g2-struct */

/* MAKE-PERMANENT-ICP-PORT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_icp_port_structure_internal()
{
    Object def_structure_icp_port_variable, icp_port_count_new_value;
    Object defstruct_g2_icp_port_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(36,85);
    def_structure_icp_port_variable = Nil;
    icp_port_count_new_value = FIXNUM_ADD1(G2int_icp_port_count);
    G2int_icp_port_count = icp_port_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_port_variable = Nil;
	gensymed_symbol = (SI_Long)20L;
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
	defstruct_g2_icp_port_variable = the_array;
	SVREF(defstruct_g2_icp_port_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_port_g2_struct;
	def_structure_icp_port_variable = defstruct_g2_icp_port_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_port_variable);
}

/* MAKE-ICP-PORT-STRUCTURE-1 */
Object g2int_make_icp_port_structure_1(icp_connection_handle,
	    parent_icp_socket,icp_port_direction,
	    receive_or_transmit_directly_qm)
    Object icp_connection_handle, parent_icp_socket, icp_port_direction;
    Object receive_or_transmit_directly_qm;
{
    Object def_structure_icp_port_variable;

    x_note_fn_call(36,86);
    def_structure_icp_port_variable = G2int_chain_of_available_icp_ports;
    if (def_structure_icp_port_variable) {
	G2int_chain_of_available_icp_ports = 
		ISVREF(def_structure_icp_port_variable,(SI_Long)0L);
	SVREF(def_structure_icp_port_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_port_g2_struct;
    }
    else
	def_structure_icp_port_variable = 
		g2int_make_permanent_icp_port_structure_internal();
    inline_note_allocate_cons(def_structure_icp_port_variable,Nil);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)1L)) = 
	    icp_connection_handle;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)2L)) = 
	    parent_icp_socket;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)3L)) = 
	    icp_port_direction;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)5L)) = 
	    receive_or_transmit_directly_qm;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)11L)) = Nil;
    ISVREF(def_structure_icp_port_variable,(SI_Long)14L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)16L)) = Nil;
    ISVREF(def_structure_icp_port_variable,(SI_Long)17L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_icp_port_variable);
}

/* SET-SOCKET-DEBUG-STATUS */
Object g2int_set_socket_debug_status(icp_socket,status)
    Object icp_socket, status;
{
    x_note_fn_call(36,87);
    return VALUES_1(FIX(g2ext_set_debug_status(IFIX(ISVREF(ISVREF(icp_socket,
	    (SI_Long)3L),(SI_Long)1L)),IFIX(status))));
}

/* NIL-OUT-CAR-OF-CONS */
Object g2int_nil_out_car_of_cons(cons_qm)
    Object cons_qm;
{
    Object temp;

    x_note_fn_call(36,88);
    if (cons_qm)
	temp = M_CAR(cons_qm) = Nil;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2int_item_index_space;  /* item-index-space */

/* ITEM-INDEX-SPACE */
Object g2int_item_index_space(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(36,89);
    temp = ISVREF(icp_port,(SI_Long)9L);
    if (temp);
    else {
	temp = g2int_set_up_icp_object_index_space(Qg2int_item_index_space);
	SVREF(icp_port,FIX((SI_Long)9L)) = temp;
    }
    return VALUES_1(temp);
}

static Object Qg2int_item_with_handle_index_space;  /* item-with-handle-index-space */

/* ITEM-WITH-HANDLE-INDEX-SPACE */
Object g2int_item_with_handle_index_space(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(36,90);
    temp = ISVREF(icp_port,(SI_Long)10L);
    if (temp);
    else {
	temp = 
		g2int_set_up_icp_object_index_space(Qg2int_item_with_handle_index_space);
	SVREF(icp_port,FIX((SI_Long)10L)) = temp;
    }
    return VALUES_1(temp);
}

/* REGISTER-ITEM-WITH-HANDLE-ON-PORT */
Object g2int_register_item_with_handle_on_port(index_1,item,icp_port)
    Object index_1, item, icp_port;
{
    Object index_space, vector_1, object, svref_arg_1;
    SI_Long index_2, svref_arg_2;

    x_note_fn_call(36,91);
    index_space = g2int_item_with_handle_index_space(icp_port);
    vector_1 = ISVREF(index_space,(SI_Long)2L);
    index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil;
    index_2 = IFIX(index_1) & (SI_Long)1023L;
    object = g2int_gensym_cons_1(item,vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = object);
}

/* DEREGISTER-ITEM-WITH-HANDLE-ON-PORT */
Object g2int_deregister_item_with_handle_on_port(index_1,item,icp_port)
    Object index_1, item, icp_port;
{
    Object index_space, vector_1, object, svref_arg_1;
    SI_Long index_2, svref_arg_2;

    x_note_fn_call(36,92);
    index_space = g2int_item_with_handle_index_space(icp_port);
    vector_1 = ISVREF(index_space,(SI_Long)2L);
    index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil;
    index_2 = IFIX(index_1) & (SI_Long)1023L;
    object = g2int_delete_gensym_element_1(item,vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = object);
}

/* ITEMS-REGISTERED-WITH-HANDLE-ON-PORT */
Object g2int_items_registered_with_handle_on_port(index_1,icp_port)
    Object index_1, icp_port;
{
    Object index_space, vector_1, temp;
    SI_Long index_2;

    x_note_fn_call(36,93);
    if (ISVREF(icp_port,(SI_Long)10L)) {
	index_space = g2int_item_with_handle_index_space(icp_port);
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
	index_2 = IFIX(index_1) & (SI_Long)1023L;
	temp = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CLEAR-ITEMS-REGISTERED-WITH-HANDLE-ON-PORT */
Object g2int_clear_items_registered_with_handle_on_port(index_1,icp_port)
    Object index_1, icp_port;
{
    Object index_space, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(36,94);
    index_space = g2int_item_with_handle_index_space(icp_port);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = Nil);
}

/* FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object g2int_frame_serial_number_to_item_table(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(36,95);
    temp = ISVREF(icp_port,(SI_Long)11L);
    if (temp);
    else {
	temp = g2int_make_frame_serial_number_to_item_table();
	SVREF(icp_port,FIX((SI_Long)11L)) = temp;
    }
    return VALUES_1(temp);
}

Object G2int_current_icp_port = UNBOUND;

Object G2int_current_icp_socket = UNBOUND;

Object G2int_current_standard_icp_object_index_space = UNBOUND;

Object G2int_current_temporary_icp_object_index_space = UNBOUND;

static Object Qg2int_frame_serial_number;  /* frame-serial-number */

/* GET-FROM-ICP-PORT */
Object g2int_get_from_icp_port(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    SI_Long gensymed_symbol, temp_2, gensymed_symbol_3;

    x_note_fn_call(36,96);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	gensymed_symbol_1 = CDR(temp_1);
	gensymed_symbol_2 = icp_object_index;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		temp_1 = M_CDR(M_CAR(gensymed_symbol_1));
		goto end;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = Qnil;
	  end:;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
    }
    else {
	if (FIXNUM_GE(icp_object_index,ISVREF(index_space,(SI_Long)4L)))
	    g2int_enlarge_index_space(index_space,icp_object_index);
	temp_1 = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		IFIX(icp_object_index) >>  -  - (SI_Long)10L),
		IFIX(icp_object_index) & (SI_Long)1023L);
    }
    return VALUES_1(temp_1);
}

/* GET-FROM-ICP-PORT-IF-ANY */
Object g2int_get_from_icp_port_if_any(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4, vector_1;
    SI_Long gensymed_symbol, temp_2, gensymed_symbol_3, index_1;

    x_note_fn_call(36,97);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	gensymed_symbol_1 = CDR(temp_1);
	gensymed_symbol_2 = icp_object_index;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		temp_1 = M_CDR(M_CAR(gensymed_symbol_1));
		goto end;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = Qnil;
	  end:;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
    }
    else {
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_1 = IFIX(icp_object_index) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_1 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_1) : Qnil;
	index_1 = IFIX(icp_object_index) & (SI_Long)1023L;
	temp_1 = vector_1 && index_1 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_1) : Qnil;
    }
    return VALUES_1(temp_1);
}

/* SET-IN-ICP-PORT */
Object g2int_set_in_icp_port(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space,new_value)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space, new_value;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;

    x_note_fn_call(36,98);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = g2int_set_balanced_binary_tree_entry(SVREF(index_space,
		FIX(temp_2)),Qeq,
		G2int_fp_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry,
		T,icp_object_index,FIX(gensymed_symbol),new_value);
    }
    else {
	if (FIXNUM_GE(icp_object_index,ISVREF(index_space,(SI_Long)4L)))
	    g2int_enlarge_index_space(index_space,icp_object_index);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),
		IFIX(icp_object_index) >>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(icp_object_index) & (SI_Long)1023L;
	temp_1 = ISVREF(svref_arg_1,svref_arg_2) = new_value;
    }
    return VALUES_1(temp_1);
}

/* MAKE-ICP-PORT */
Object g2int_make_icp_port(icp_connection_handle,parent_icp_socket,
	    icp_port_direction,receive_or_transmit_directly_qm)
    Object icp_connection_handle, parent_icp_socket, icp_port_direction;
    Object receive_or_transmit_directly_qm;
{
    Object current_icp_port, icp_buffer, svref_arg_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(36,99);
    current_icp_port = 
	    g2int_make_icp_port_structure_1(icp_connection_handle,
	    parent_icp_socket,icp_port_direction,
	    receive_or_transmit_directly_qm);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,0);
      icp_buffer = 
	      g2int_make_icp_buffer_internal_1(g2int_make_variable_fill_icp_buffer());
      svref_arg_1 = G2int_current_icp_port;
      svref_new_value = 
	      g2int_set_up_icp_object_index_space(Qg2int_standard_icp_object_index_space);
      SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
      svref_arg_1 = G2int_current_icp_port;
      SVREF(svref_arg_1,FIX((SI_Long)12L)) = icp_buffer;
      svref_arg_1 = G2int_current_icp_port;
      SVREF(svref_arg_1,FIX((SI_Long)13L)) = icp_buffer;
      if (EQ(icp_port_direction,Qg2int_input)) {
	  svref_arg_1 = G2int_current_icp_port;
	  SVREF(svref_arg_1,FIX((SI_Long)4L)) = Qg2int_initial;
      }
      result = VALUES_1(G2int_current_icp_port);
    POP_SPECIAL();
    return result;
}

Object G2int_do_not_reclaim_runs_while_inactive_entries = UNBOUND;

/* RECLAIM-ICP-OBJECT-MAP */
Object g2int_reclaim_icp_object_map(icp_object,icp_object_map,
	    name_of_corresponding_icp_object_index_space)
    Object icp_object, icp_object_map;
    Object name_of_corresponding_icp_object_index_space;
{
    Object map_tail, next_map_tail, icp_port, index_1, temp;

    x_note_fn_call(36,100);
    map_tail = icp_object_map;
    next_map_tail = Nil;
    icp_port = Nil;
    index_1 = Nil;
  next_loop:
    if ( !TRUEP(map_tail))
	goto end_loop;
    next_map_tail = CDDR(map_tail);
    icp_port = CAR(map_tail);
    temp = CDR(map_tail);
    index_1 = CAR(temp);
    if ( !(G2int_do_not_reclaim_runs_while_inactive_entries && 
	    ISVREF(ISVREF(icp_port,(SI_Long)2L),(SI_Long)48L)))
	g2int_reclaim_index_space_location_and_corresponding_objects(icp_object,
		icp_port,index_1,name_of_corresponding_icp_object_index_space);
    map_tail = next_map_tail;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-ICP-PORT-ENTRY */
Object g2int_reclaim_icp_port_entry(icp_port,icp_object,icp_object_map,
	    name_of_function_to_set_object_map)
    Object icp_port, icp_object, icp_object_map;
    Object name_of_function_to_set_object_map;
{
    Object map_entry_tail, rest_of_map_entries, cddr_new_value;

    x_note_fn_call(36,101);
    map_entry_tail = Nil;
    rest_of_map_entries = icp_object_map;
  next_loop:
    if ( !TRUEP(rest_of_map_entries))
	goto end_loop;
    if (EQ(CAR(rest_of_map_entries),icp_port)) {
	if (map_entry_tail) {
	    cddr_new_value = CDDR(rest_of_map_entries);
	    M_CDDR(map_entry_tail) = cddr_new_value;
	}
	else
	    FUNCALL_2(name_of_function_to_set_object_map,icp_object,
		    CDDR(rest_of_map_entries));
	g2int_reclaim_gensym_cons_1(CDR(rest_of_map_entries));
	g2int_reclaim_gensym_cons_1(rest_of_map_entries);
	goto end;
    }
    map_entry_tail = rest_of_map_entries;
    rest_of_map_entries = CDDR(rest_of_map_entries);
    goto next_loop;
  end_loop:
  end:;
    return VALUES_1(Nil);
}

Object G2int_icp_output_ports_to_flush = UNBOUND;

Object G2int_with_icp_buffer_coelescing_scopeqm = UNBOUND;

/* FLUSH-ICP-OUTPUT-PORTS */
Object g2int_flush_icp_output_ports()
{
    Object gensymed_symbol, ports_to_flush, icp_output_port_qm, ab_loop_list_;
    double gensymed_symbol_1;

    x_note_fn_call(36,102);
    if (G2int_icp_output_ports_to_flush) {
	gensymed_symbol = Nil;
	gensymed_symbol_1 = 0.0;
	gensymed_symbol_1 = 0.0;
	ports_to_flush = G2int_icp_output_ports_to_flush;
	G2int_icp_output_ports_to_flush = Nil;
	icp_output_port_qm = Nil;
	ab_loop_list_ = ports_to_flush;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	icp_output_port_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (icp_output_port_qm) {
	    SVREF(icp_output_port_qm,FIX((SI_Long)18L)) = Nil;
	    g2int_transmit_icp_output_if_ready(icp_output_port_qm,T);
	}
	goto next_loop;
      end_loop:;
	g2int_reclaim_gensym_list_1(ports_to_flush);
    }
    return VALUES_1(Nil);
}

Object G2int_disable_resumability = UNBOUND;

Object G2int_starresumable_icp_statestar = UNBOUND;

Object G2int_icp_suspend = UNBOUND;

/* RESUMABLE-ICP-PUSH */
Object g2int_resumable_icp_push(form)
    Object form;
{
    x_note_fn_call(36,103);
    G2int_starresumable_icp_statestar = g2int_gensym_cons_1(form,
	    G2int_starresumable_icp_statestar);
    return VALUES_1(form);
}

/* RESUMABLE-ICP-POP */
Object g2int_resumable_icp_pop()
{
    Object gensym_pop_store, cons_1, next_cons, cdr_new_value;

    x_note_fn_call(36,104);
    gensym_pop_store = Nil;
    cons_1 = G2int_starresumable_icp_statestar;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    G2int_starresumable_icp_statestar = next_cons;
    return VALUES_1(gensym_pop_store);
}

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* RESUMABLE-ICP-POP-LIST-IF-END-MARKER */
Object g2int_resumable_icp_pop_list_if_end_marker()
{
    Object gensym_pop_store, cons_1, next_cons, cdr_new_value, temp;

    x_note_fn_call(36,105);
    if (EQ(Qg2int_resumable_icp_list_end,
	    CAR(G2int_starresumable_icp_statestar))) {
	gensym_pop_store = Nil;
	cons_1 = G2int_starresumable_icp_statestar;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    cdr_new_value = G2int_available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    G2int_available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	G2int_starresumable_icp_statestar = next_cons;
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_trif_block_value_alist = UNBOUND;

void int1_INIT()
{
    Object the_array, temp, reclaim_structure_for_socket;
    Object reclaim_structure_for_icp_socket, reclaim_structure_for_icp_buffer;
    Object reclaim_structure_for_icp_port;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    Object AB_package, Qg2int_suspend, Qg2int_flush_icp_output_ports;
    Object Qg2int_int1, Qg2int_current_temporary_icp_object_index_space;
    Object Qg2int_current_standard_icp_object_index_space;
    Object Qg2int_current_icp_port, Qg2int_icp_port, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_icp_port_count;
    Object Qg2int_chain_of_available_icp_ports;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_6, Qg2int_unique_structure_type_of_ab_nameqm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_int2;
    Object Qg2int_recycled_icp_buffers, Qg2int_icp_buffer;
    Object Qg2int_icp_buffer_count, Qg2int_chain_of_available_icp_buffers;
    Object string_constant_5, Qg2int_transmitted_variable_fill_icp_buffers;
    Object Qg2int_recycled_variable_fill_icp_buffers;
    Object Qg2int_count_of_variable_fill_icp_buffer_4096_vectors;
    Object Qg2int_available_variable_fill_icp_buffer_4096_vectors;
    Object Qg2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry;
    Object Qg2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors;
    Object Qg2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors;
    Object Qg2int_highest_icp_socket_session_id, Qg2int_bizzare_state;
    Object list_constant_14, list_constant_13, list_constant_12;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_8, list_constant_7, Qg2int_listening;
    Object Qg2int_awaiting_acknowledgement;
    Object Qg2int_shutdown_acknowledgement_rundown, Qg2int_shutdown_requested;
    Object Qg2int_running, Qg2int_connect_in_progress, Qg2int_closed;
    Object list_constant_6, Qg2int_icp_socket, Qg2int_icp_socket_count;
    Object Qg2int_chain_of_available_icp_sockets, string_constant_4;
    Object Qg2int_socket, Qg2int_socket_count;
    Object Qg2int_chain_of_available_sockets, string_constant_3;
    Object Qg2int_native_long_icp_version;
    Object Qg2int_supports_font_in_grid_view_icp_version;
    Object Qg2int_dialog_component_with_font_icp_version;
    Object Qg2int_compressed_image_data_chunk_icp_version;
    Object Qg2int_transparent_color_index_icp_version;
    Object Qg2int_remote_procedure_include_all_system_attributes_except_icp_version;
    Object Qg2int_send_text_of_expressions_for_g2ds_icp_version;
    Object Qg2int_long_string_icp_version, Qg2int_intern_keyword_icp_version;
    Object Qg2int_no_frame_serial_index_space_icp_version;
    Object Qg2int_do_not_reformat_message_icp_version;
    Object Qg2int_t2_supports_item_layer_change;
    Object Qg2int_g2_supports_update_with_delete_icp_version;
    Object Qg2int_supports_new_references_icp_version;
    Object Qg2int_no_licence_icp_version;
    Object Qg2int_gsi_sends_returned_gsi_sensor_as_reference_icp_version;
    Object Qg2int_supports_non_resumability_icp_version;
    Object Qg2int_return_g2ds_version_sends_class_icp_version;
    Object Qg2int_by_copy_with_handle_supports_references_icp_version;
    Object Qg2int_data_servers_can_run_while_inactive_version;
    Object Qg2int_independent_layered_rendering_version;
    Object Qg2int_unsigned_short_vector_icp_version;
    Object Qg2int_deregister_icp_objects_icp_version;
    Object Qg2int_abort_icp_task_icp_version;
    Object Qg2int_acknowledge_deregister_corresponding_icp_object_icp_version;
    Object Qg2int_item_reference_icp_version;
    Object Qg2int_gsi_dataservice_uses_full_remote_value_protocol_icp_version;
    Object Qg2int_values_as_handle_icp_version;
    Object Qg2int_item_index_space_icp_version;
    Object Qg2int_deregister_original_icp_object_icp_version;
    Object Qg2int_deregister_corresponding_icp_object_index_space_name_icp_version;
    Object Qg2int_rpc_use_value_structure_using_unix_time_icp_version;
    Object Qg2int_new_remote_procedure_identifer_protocol_icp_version;
    Object Qg2int_remote_procedure_varargs_p_icp_version;
    Object Qg2int_no_telewindows_clogging_icp_version;
    Object Qg2int_remote_procedure_include_all_system_attributes_icp_version;
    Object Qg2int_resumable_gsi_ds_icp_version;
    Object Qg2int_rel4_rpc_protocol_supports_non_objects_icp_version;
    Object Qg2int_does_not_require_enlarge_corresponding_icp_object_index_space_icp_version;
    Object Qg2int_value_vector_names_are_symbols_icp_version;
    Object Qg2int_new_rpc_kinds_icp_version, Qg2int_resumable_icp_version;
    Object Qg2int_evaluation_sequences_and_structures_icp_version;
    Object Qg2int_supports_optional_remote_value_tags_icp_version;
    Object Qg2int_remote_value_supports_item_icp_version;
    Object Qg2int_supports_icp_version_protocol_icp_version;
    Object Qg2int_writing_coalesced_icp_message_group_icp_version;
    Object Qg2int_wide_strings_icp_version;
    Object Qg2int_g2_version_reply_to_gsi_icp_version;
    Object Qg2int_new_connect_scheme_icp_version;
    Object Qg2int_shutdown_protocol_icp_version;
    Object Qg2int_gsi_timestamp_as_float_icp_version;
    Object Qg2int_gsi_item_registration_icp_version;
    Object Qg2int_pass_item_as_copy_icp_version;
    Object Qg2int_pass_item_as_handle_icp_version;
    Object Qg2int_remote_procedure_include_attribute_icp_version;
    Object Qg2int_ds_update_interval_as_float_icp_version;
    Object Qg2int_release_4dot0_icp_version, Qg2int_release_3dot0_icp_version;
    Object Qg2int_double_float_icp_version;
    Object Qg2int_modify_gsi_sensor_definition_icp_version;
    Object Qg2int_reclaim_remote_corresponding_object_icp_version;
    Object Qg2int_release_2dot0_icp_version, Qg2int_release_1dot0_icp_version;
    Object Qg2int_gsi_uninitialized_context, Qg2int_gsi_undefined_context;
    Object Qg2int_gsi_ds, Qg2int_reset_data_server, Qg2int_start_data_server;
    Object Qg2int_rpc, Qg2int_create_item_reference;
    Object Qg2int_resumable_rpc_error_to_caller, Qg2int_resumable_rpc_error;
    Object Qg2int_define_resumable_remote_procedure_identifier;
    Object Qg2int_intern_list, Qg2int_gsi;
    Object Qg2int_return_initialize_gsi_interface_status;
    Object Qg2int_initialize_gsi_interface, Qg2int_icp;
    Object Qg2int_acknowledge_shutdown, Qg2int_deregister_icp_objects;
    Object Qg2int_acknowledge_deregister_corresponding_icp_object;
    Object Qg2int_deregister_original_icp_object;
    Object Qg2int_deregister_corresponding_icp_object;
    Object Qg2int_register_corresponding_icp_object;
    Object Qg2int_update_object_passing_network_resources;
    Object Qg2int_continue_building_resumable_object, Qg2int_no_license;
    Object Qg2int_connection_shutdown_imminent, Qg2int_connection_denied;
    Object Qg2int_release_temporary_index_space;
    Object Qg2int_define_temporary_index_space, Qg2int_abort_icp_task;
    Object Qg2int_resumable_rpc_return_values, Qg2int_resumable_rpc_call;
    Object Qg2int_resumable_rpc_start, Qg2int_resume_icp_task;
    Object Qg2int_start_icp_task, Qg2int_rpc_acknowledge_abort;
    Object Qg2int_rpc_resume, Qg2int_rpc_suspend, Qg2int_rpc_return_values;
    Object Qg2int_rpc_synchronous_abort, Qg2int_rpc_asynchronous_abort;
    Object Qg2int_rpc_continue_from_error, Qg2int_rpc_error_to_caller;
    Object Qg2int_rpc_error, Qg2int_rpc_call, Qg2int_rpc_start;
    Object Qg2int_define_remote_procedure_identifier;
    Object Qg2int_define_remote_procedure_name;
    Object Qg2int_delete_icp_object_for_process, Qg2int_intern_keyword;
    Object Qg2int_add_to_list_of_symbols;
    Object Qg2int_receive_values_for_gsi_sensors;
    Object Qg2int_receive_timestamped_gsi_sensor_value_vector;
    Object Qg2int_receive_gsi_sensor_value_vector, Qg2int_define_gsi_interface;
    Object Qg2int_receive_value_for_gsi_sensor_with_timestamp;
    Object Qg2int_define_gsi_sensor;
    Object Qg2int_stop_sending_values_for_sensors_in_list;
    Object Qg2int_send_data_values_if_any, Qg2int_resume_data_server;
    Object Qg2int_pause_data_server, Qg2int_shut_down_data_server;
    Object Qg2int_initialize_data_server, Qg2int_receive_value_for_gsi_sensor;
    Object Qg2int_receive_value_for_ping_request, Qg2int_return_peer_version;
    Object Qg2int_write_user_message_string;
    Object Qg2int_set_values_for_sensors_in_list;
    Object Qg2int_get_values_for_sensors_in_list, Qg2int_end_sensor_list;
    Object Qg2int_load_sensor_list_element, Qg2int_begin_sensor_list;
    Object Qg2int_modify_gsi_sensor_definition, Qg2int_end_message_block;
    Object Qg2int_nop, Qg2int_enlarge_corresponding_icp_object_index_space;
    Object list_constant_5, Qg2int_priority_for_icp_priority_category;
    Object Qg2int_ole, Qg2int_view, Qg2int_tw, Qg2int_data_service;
    Object Qg2int_g2_ds, Qg2int_i_am_alive;
    Object Qg2int_default_print_handler_for_icp_messages, list_constant_4;
    Object Qg2int_deregister_corresponding_objectqm;
    Object Qg2int_delete_corresponding_objectqm, Qg2int_icp_value_reclaimer;
    Object Qg2int_icp_value_write_function, Qg2int_icp_value_reader_function;
    Object Qg2int_equivalent_icp_value_type, list_constant_3;
    Object Qg2int_g2ds_server_status, Qg2int_g2ds_send_data_values_if_any;
    Object Qg2int_message_group_id, Qg2int_function_for_icp_value_writerqm;
    Object Qg2int_function_for_icp_value_readerqm, string_constant_2;
    Object Qg2int_blank_traced_icp_byte_column;

    x_note_fn_call(36,106);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_blank_traced_icp_byte_column = 
	    STATIC_SYMBOL("BLANK-TRACED-ICP-BYTE-COLUMN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_blank_traced_icp_byte_column,
	    G2int_blank_traced_icp_byte_column);
    string_constant_2 = STATIC_STRING("|  ");
    SET_SYMBOL_VALUE(Qg2int_blank_traced_icp_byte_column,string_constant_2);
    if (G2int_trace_skip_data_service_i_am_alive_messages_p == UNBOUND)
	G2int_trace_skip_data_service_i_am_alive_messages_p = Nil;
    if (G2int_icp_trace_print_message_series_p == UNBOUND)
	G2int_icp_trace_print_message_series_p = T;
    Qg2int_function_for_icp_value_readerqm = 
	    STATIC_SYMBOL("FUNCTION-FOR-ICP-VALUE-READER\?",AB_package);
    G2int_function_for_icp_value_readerqm_prop = 
	    Qg2int_function_for_icp_value_readerqm;
    if (G2int_icp_read_trace_cutoff_levelqm == UNBOUND)
	G2int_icp_read_trace_cutoff_levelqm = Nil;
    if (G2int_current_icp_read_trace_level == UNBOUND)
	G2int_current_icp_read_trace_level = FIX((SI_Long)0L);
    Qg2int_function_for_icp_value_writerqm = 
	    STATIC_SYMBOL("FUNCTION-FOR-ICP-VALUE-WRITER\?",AB_package);
    G2int_function_for_icp_value_writerqm_prop = 
	    Qg2int_function_for_icp_value_writerqm;
    if (G2int_icp_write_trace_cutoff_levelqm == UNBOUND)
	G2int_icp_write_trace_cutoff_levelqm = Nil;
    if (G2int_current_icp_write_trace_level == UNBOUND)
	G2int_current_icp_write_trace_level = FIX((SI_Long)0L);
    Qg2int_i_am_alive = STATIC_SYMBOL("I-AM-ALIVE",AB_package);
    Qg2int_message_group_id = STATIC_SYMBOL("MESSAGE-GROUP-ID",AB_package);
    Qg2int_g2ds_send_data_values_if_any = 
	    STATIC_SYMBOL("G2DS-SEND-DATA-VALUES-IF-ANY",AB_package);
    Qg2int_g2ds_server_status = STATIC_SYMBOL("G2DS-SERVER-STATUS",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)4L,Qg2int_i_am_alive,
	    Qg2int_message_group_id,Qg2int_g2ds_send_data_values_if_any,
	    Qg2int_g2ds_server_status);
    G2int_data_service_i_am_alive_messages = list_constant_3;
    Qg2int_equivalent_icp_value_type = 
	    STATIC_SYMBOL("EQUIVALENT-ICP-VALUE-TYPE",AB_package);
    G2int_equivalent_icp_value_type_prop = Qg2int_equivalent_icp_value_type;
    Qg2int_icp_value_reader_function = 
	    STATIC_SYMBOL("ICP-VALUE-READER-FUNCTION",AB_package);
    G2int_icp_value_reader_function_prop = Qg2int_icp_value_reader_function;
    Qg2int_icp_value_write_function = 
	    STATIC_SYMBOL("ICP-VALUE-WRITE-FUNCTION",AB_package);
    G2int_icp_value_write_function_prop = Qg2int_icp_value_write_function;
    Qg2int_icp_value_reclaimer = STATIC_SYMBOL("ICP-VALUE-RECLAIMER",
	    AB_package);
    G2int_icp_value_reclaimer_prop = Qg2int_icp_value_reclaimer;
    Qg2int_name_of_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("NAME-OF-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    G2int_name_of_corresponding_icp_object_index_space_prop = 
	    Qg2int_name_of_corresponding_icp_object_index_space;
    Qg2int_access_form_for_corresponding_icp_object_map = 
	    STATIC_SYMBOL("ACCESS-FORM-FOR-CORRESPONDING-ICP-OBJECT-MAP",
	    AB_package);
    G2int_access_form_for_corresponding_icp_object_map_prop = 
	    Qg2int_access_form_for_corresponding_icp_object_map;
    Qg2int_reclaimer_for_icp_port_entry = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-PORT-ENTRY",AB_package);
    G2int_reclaimer_for_icp_port_entry_prop = 
	    Qg2int_reclaimer_for_icp_port_entry;
    Qg2int_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-OBJECT",AB_package);
    G2int_reclaimer_for_icp_object_prop = Qg2int_reclaimer_for_icp_object;
    Qg2int_shutdown_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("SHUTDOWN-RECLAIMER-FOR-ICP-OBJECT",AB_package);
    G2int_shutdown_reclaimer_for_icp_object_prop = 
	    Qg2int_shutdown_reclaimer_for_icp_object;
    Qg2int_delete_corresponding_objectqm = 
	    STATIC_SYMBOL("DELETE-CORRESPONDING-OBJECT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_delete_corresponding_objectqm,
	    G2int_delete_corresponding_objectqm);
    Qg2int_int1 = STATIC_SYMBOL("INT1",AB_package);
    g2int_record_system_variable(Qg2int_delete_corresponding_objectqm,
	    Qg2int_int1,T,Qnil,Qnil,Qnil,Qnil);
    Qg2int_deregister_corresponding_objectqm = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-OBJECT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_deregister_corresponding_objectqm,
	    G2int_deregister_corresponding_objectqm);
    g2int_record_system_variable(Qg2int_deregister_corresponding_objectqm,
	    Qg2int_int1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qg2int_item_index_space,
	    Qg2int_standard_icp_object_index_space);
    if (G2int_all_index_space_names == UNBOUND)
	G2int_all_index_space_names = list_constant_4;
    if (G2int_inhibit_corresponding_icp_object_making == UNBOUND)
	G2int_inhibit_corresponding_icp_object_making = Nil;
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    Qg2int_font_map = STATIC_SYMBOL("FONT-MAP",AB_package);
    if (G2int_icp_message_handler_array == UNBOUND) {
	gensymed_symbol = (SI_Long)750L;
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
	G2int_icp_message_handler_array = the_array;
    }
    if (G2int_icp_message_handler_name_array == UNBOUND) {
	gensymed_symbol = (SI_Long)750L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	G2int_icp_message_handler_name_array = the_array;
    }
    Qg2int_default_print_handler_for_icp_messages = 
	    STATIC_SYMBOL("DEFAULT-PRINT-HANDLER-FOR-ICP-MESSAGES",AB_package);
    if (G2int_icp_printing_message_handler_array == UNBOUND)
	G2int_icp_printing_message_handler_array = make_array(3,
		FIX((SI_Long)750L),Kinitial_element,
		Qg2int_default_print_handler_for_icp_messages);
    Qg2int_icp_message_type_code = STATIC_SYMBOL("ICP-MESSAGE-TYPE-CODE",
	    AB_package);
    G2int_icp_message_type_code_prop = Qg2int_icp_message_type_code;
    Qg2int_priority_for_icp_priority_category = 
	    STATIC_SYMBOL("PRIORITY-FOR-ICP-PRIORITY-CATEGORY",AB_package);
    G2int_priority_for_icp_priority_category_prop = 
	    Qg2int_priority_for_icp_priority_category;
    Qg2int_icp_priority_category_for_message = 
	    STATIC_SYMBOL("ICP-PRIORITY-CATEGORY-FOR-MESSAGE",AB_package);
    G2int_icp_priority_category_for_message_prop = 
	    Qg2int_icp_priority_category_for_message;
    Qg2int_icp = STATIC_SYMBOL("ICP",AB_package);
    g2int_mutate_global_property(Qg2int_icp,Qg2int_icp,
	    Qg2int_priority_for_icp_priority_category);
    g2int_mutate_global_property(Qg2int_i_am_alive,Qg2int_i_am_alive,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_rpc = STATIC_SYMBOL("RPC",AB_package);
    g2int_mutate_global_property(Qg2int_rpc,Qg2int_rpc,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    g2int_mutate_global_property(Qg2int_gsi,Qg2int_gsi,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_gsi_ds = STATIC_SYMBOL("GSI-DS",AB_package);
    Qg2int_data_service = STATIC_SYMBOL("DATA-SERVICE",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_ds,Qg2int_data_service,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_g2_ds = STATIC_SYMBOL("G2-DS",AB_package);
    g2int_mutate_global_property(Qg2int_g2_ds,Qg2int_data_service,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_tw = STATIC_SYMBOL("TW",AB_package);
    g2int_mutate_global_property(Qg2int_tw,Qg2int_tw,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_gspan = STATIC_SYMBOL("GSPAN",AB_package);
    g2int_mutate_global_property(Qg2int_gspan,Qg2int_gspan,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_view = STATIC_SYMBOL("VIEW",AB_package);
    g2int_mutate_global_property(Qg2int_view,Qg2int_view,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_ole = STATIC_SYMBOL("OLE",AB_package);
    g2int_mutate_global_property(Qg2int_ole,Qg2int_ole,
	    Qg2int_priority_for_icp_priority_category);
    Qg2int_start_icp_task = STATIC_SYMBOL("START-ICP-TASK",AB_package);
    Qg2int_resume_icp_task = STATIC_SYMBOL("RESUME-ICP-TASK",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)6L,Qg2int_icp,
	    Qg2int_start_icp_task,Qg2int_resume_icp_task,Qg2int_rpc,
	    Qg2int_gsi,Qg2int_gsi_ds);
    if (G2int_icp_priority_categories_for_gsi == UNBOUND)
	G2int_icp_priority_categories_for_gsi = list_constant_5;
    Qg2int_enlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_enlarge_corresponding_icp_object_index_space,
	    FIX((SI_Long)15L),Qg2int_rpc);
    Qg2int_nop = STATIC_SYMBOL("NOP",AB_package);
    g2int_add_icp_message_type_code(Qg2int_nop,FIX((SI_Long)16L),Qg2int_icp);
    Qg2int_end_message_block = STATIC_SYMBOL("END-MESSAGE-BLOCK",AB_package);
    g2int_add_icp_message_type_code(Qg2int_end_message_block,
	    FIX((SI_Long)17L),Qg2int_icp);
    Qg2int_modify_gsi_sensor_definition = 
	    STATIC_SYMBOL("MODIFY-GSI-SENSOR-DEFINITION",AB_package);
    g2int_add_icp_message_type_code(Qg2int_modify_gsi_sensor_definition,
	    FIX((SI_Long)59L),Qg2int_gsi_ds);
    Qg2int_begin_sensor_list = STATIC_SYMBOL("BEGIN-SENSOR-LIST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_begin_sensor_list,
	    FIX((SI_Long)60L),Qg2int_gsi_ds);
    Qg2int_load_sensor_list_element = 
	    STATIC_SYMBOL("LOAD-SENSOR-LIST-ELEMENT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_load_sensor_list_element,
	    FIX((SI_Long)61L),Qg2int_gsi_ds);
    Qg2int_end_sensor_list = STATIC_SYMBOL("END-SENSOR-LIST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_end_sensor_list,
	    FIX((SI_Long)62L),Qg2int_gsi_ds);
    Qg2int_get_values_for_sensors_in_list = 
	    STATIC_SYMBOL("GET-VALUES-FOR-SENSORS-IN-LIST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_get_values_for_sensors_in_list,
	    FIX((SI_Long)63L),Qg2int_gsi_ds);
    Qg2int_set_values_for_sensors_in_list = 
	    STATIC_SYMBOL("SET-VALUES-FOR-SENSORS-IN-LIST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_set_values_for_sensors_in_list,
	    FIX((SI_Long)64L),Qg2int_gsi_ds);
    Qg2int_write_user_message_string = 
	    STATIC_SYMBOL("WRITE-USER-MESSAGE-STRING",AB_package);
    g2int_add_icp_message_type_code(Qg2int_write_user_message_string,
	    FIX((SI_Long)65L),Qg2int_gsi);
    Qg2int_return_peer_version = STATIC_SYMBOL("RETURN-PEER-VERSION",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_return_peer_version,
	    FIX((SI_Long)66L),Qg2int_gsi);
    Qg2int_receive_value_for_ping_request = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-PING-REQUEST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_value_for_ping_request,
	    FIX((SI_Long)67L),Qg2int_gsi_ds);
    Qg2int_receive_value_for_gsi_sensor = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-GSI-SENSOR",AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_value_for_gsi_sensor,
	    FIX((SI_Long)68L),Qg2int_gsi_ds);
    Qg2int_initialize_data_server = STATIC_SYMBOL("INITIALIZE-DATA-SERVER",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_initialize_data_server,
	    FIX((SI_Long)69L),Qg2int_gsi_ds);
    Qg2int_shut_down_data_server = STATIC_SYMBOL("SHUT-DOWN-DATA-SERVER",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_shut_down_data_server,
	    FIX((SI_Long)70L),Qg2int_icp);
    Qg2int_pause_data_server = STATIC_SYMBOL("PAUSE-DATA-SERVER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_pause_data_server,
	    FIX((SI_Long)71L),Qg2int_gsi_ds);
    Qg2int_resume_data_server = STATIC_SYMBOL("RESUME-DATA-SERVER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_resume_data_server,
	    FIX((SI_Long)72L),Qg2int_gsi_ds);
    Qg2int_send_data_values_if_any = 
	    STATIC_SYMBOL("SEND-DATA-VALUES-IF-ANY",AB_package);
    g2int_add_icp_message_type_code(Qg2int_send_data_values_if_any,
	    FIX((SI_Long)73L),Qg2int_gsi);
    Qg2int_stop_sending_values_for_sensors_in_list = 
	    STATIC_SYMBOL("STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_stop_sending_values_for_sensors_in_list,
	    FIX((SI_Long)74L),Qg2int_gsi_ds);
    Qg2int_define_gsi_sensor = STATIC_SYMBOL("DEFINE-GSI-SENSOR",AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_gsi_sensor,
	    FIX((SI_Long)75L),Qg2int_gsi_ds);
    Qg2int_receive_value_for_gsi_sensor_with_timestamp = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_value_for_gsi_sensor_with_timestamp,
	    FIX((SI_Long)76L),Qg2int_gsi_ds);
    Qg2int_define_gsi_interface = STATIC_SYMBOL("DEFINE-GSI-INTERFACE",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_gsi_interface,
	    FIX((SI_Long)77L),Qg2int_gsi_ds);
    Qg2int_receive_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("RECEIVE-GSI-SENSOR-VALUE-VECTOR",AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_gsi_sensor_value_vector,
	    FIX((SI_Long)78L),Qg2int_gsi_ds);
    Qg2int_receive_timestamped_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_timestamped_gsi_sensor_value_vector,
	    FIX((SI_Long)79L),Qg2int_gsi_ds);
    Qg2int_receive_values_for_gsi_sensors = 
	    STATIC_SYMBOL("RECEIVE-VALUES-FOR-GSI-SENSORS",AB_package);
    g2int_add_icp_message_type_code(Qg2int_receive_values_for_gsi_sensors,
	    FIX((SI_Long)80L),Qg2int_gsi_ds);
    g2int_add_icp_message_type_code(Qintern,FIX((SI_Long)81L),Qg2int_rpc);
    Qg2int_add_to_list_of_symbols = STATIC_SYMBOL("ADD-TO-LIST-OF-SYMBOLS",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_add_to_list_of_symbols,
	    FIX((SI_Long)82L),Qg2int_rpc);
    Qg2int_intern_keyword = STATIC_SYMBOL("INTERN-KEYWORD",AB_package);
    g2int_add_icp_message_type_code(Qg2int_intern_keyword,
	    FIX((SI_Long)86L),Qg2int_rpc);
    Qg2int_delete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    g2int_add_icp_message_type_code(Qg2int_delete_icp_object_for_process,
	    FIX((SI_Long)163L),Qg2int_rpc);
    Qg2int_define_remote_procedure_name = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-NAME",AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_remote_procedure_name,
	    FIX((SI_Long)221L),Qg2int_rpc);
    Qg2int_define_remote_procedure_identifier = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_remote_procedure_identifier,
	    FIX((SI_Long)222L),Qg2int_rpc);
    Qg2int_rpc_start = STATIC_SYMBOL("RPC-START",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_start,FIX((SI_Long)230L),
	    Qg2int_rpc);
    Qg2int_rpc_call = STATIC_SYMBOL("RPC-CALL",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_call,FIX((SI_Long)231L),
	    Qg2int_rpc);
    Qg2int_rpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_error,FIX((SI_Long)232L),
	    Qg2int_rpc);
    Qg2int_rpc_error_to_caller = STATIC_SYMBOL("RPC-ERROR-TO-CALLER",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_error_to_caller,
	    FIX((SI_Long)233L),Qg2int_rpc);
    Qg2int_rpc_continue_from_error = 
	    STATIC_SYMBOL("RPC-CONTINUE-FROM-ERROR",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_continue_from_error,
	    FIX((SI_Long)234L),Qg2int_rpc);
    Qg2int_rpc_asynchronous_abort = STATIC_SYMBOL("RPC-ASYNCHRONOUS-ABORT",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_asynchronous_abort,
	    FIX((SI_Long)235L),Qg2int_rpc);
    Qg2int_rpc_synchronous_abort = STATIC_SYMBOL("RPC-SYNCHRONOUS-ABORT",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_synchronous_abort,
	    FIX((SI_Long)236L),Qg2int_rpc);
    Qg2int_rpc_return_values = STATIC_SYMBOL("RPC-RETURN-VALUES",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_return_values,
	    FIX((SI_Long)237L),Qg2int_rpc);
    Qg2int_rpc_suspend = STATIC_SYMBOL("RPC-SUSPEND",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_suspend,FIX((SI_Long)238L),
	    Qg2int_rpc);
    Qg2int_rpc_resume = STATIC_SYMBOL("RPC-RESUME",AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_resume,FIX((SI_Long)239L),
	    Qg2int_rpc);
    Qg2int_rpc_acknowledge_abort = STATIC_SYMBOL("RPC-ACKNOWLEDGE-ABORT",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_rpc_acknowledge_abort,
	    FIX((SI_Long)240L),Qg2int_rpc);
    g2int_add_icp_message_type_code(Qg2int_start_icp_task,
	    FIX((SI_Long)245L),Qg2int_start_icp_task);
    g2int_add_icp_message_type_code(Qg2int_resume_icp_task,
	    FIX((SI_Long)246L),Qg2int_resume_icp_task);
    Qg2int_resumable_rpc_start = STATIC_SYMBOL("RESUMABLE-RPC-START",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_resumable_rpc_start,
	    FIX((SI_Long)247L),Qg2int_rpc);
    Qg2int_resumable_rpc_call = STATIC_SYMBOL("RESUMABLE-RPC-CALL",AB_package);
    g2int_add_icp_message_type_code(Qg2int_resumable_rpc_call,
	    FIX((SI_Long)248L),Qg2int_rpc);
    Qg2int_resumable_rpc_return_values = 
	    STATIC_SYMBOL("RESUMABLE-RPC-RETURN-VALUES",AB_package);
    g2int_add_icp_message_type_code(Qg2int_resumable_rpc_return_values,
	    FIX((SI_Long)249L),Qg2int_rpc);
    Qg2int_abort_icp_task = STATIC_SYMBOL("ABORT-ICP-TASK",AB_package);
    g2int_add_icp_message_type_code(Qg2int_abort_icp_task,
	    FIX((SI_Long)250L),Qg2int_icp);
    Qg2int_define_temporary_index_space = 
	    STATIC_SYMBOL("DEFINE-TEMPORARY-INDEX-SPACE",AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_temporary_index_space,
	    FIX((SI_Long)301L),Qg2int_rpc);
    Qg2int_release_temporary_index_space = 
	    STATIC_SYMBOL("RELEASE-TEMPORARY-INDEX-SPACE",AB_package);
    g2int_add_icp_message_type_code(Qg2int_release_temporary_index_space,
	    FIX((SI_Long)302L),Qg2int_rpc);
    Qg2int_connection_denied = STATIC_SYMBOL("CONNECTION-DENIED",AB_package);
    g2int_add_icp_message_type_code(Qg2int_connection_denied,
	    FIX((SI_Long)305L),Qg2int_icp);
    Qg2int_connection_shutdown_imminent = 
	    STATIC_SYMBOL("CONNECTION-SHUTDOWN-IMMINENT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_connection_shutdown_imminent,
	    FIX((SI_Long)306L),Qg2int_icp);
    Qg2int_no_license = STATIC_SYMBOL("NO-LICENSE",AB_package);
    g2int_add_icp_message_type_code(Qg2int_no_license,FIX((SI_Long)307L),
	    Qg2int_icp);
    Qg2int_continue_building_resumable_object = 
	    STATIC_SYMBOL("CONTINUE-BUILDING-RESUMABLE-OBJECT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_continue_building_resumable_object,
	    FIX((SI_Long)320L),Qg2int_rpc);
    Qg2int_update_object_passing_network_resources = 
	    STATIC_SYMBOL("UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_update_object_passing_network_resources,
	    FIX((SI_Long)321L),Qg2int_rpc);
    Qg2int_register_corresponding_icp_object = 
	    STATIC_SYMBOL("REGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_register_corresponding_icp_object,
	    FIX((SI_Long)322L),Qg2int_rpc);
    Qg2int_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_deregister_corresponding_icp_object,
	    FIX((SI_Long)323L),Qg2int_rpc);
    Qg2int_deregister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    g2int_add_icp_message_type_code(Qg2int_deregister_original_icp_object,
	    FIX((SI_Long)324L),Qg2int_rpc);
    Qg2int_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_acknowledge_deregister_corresponding_icp_object,
	    FIX((SI_Long)325L),Qg2int_rpc);
    Qg2int_deregister_icp_objects = STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_deregister_icp_objects,
	    FIX((SI_Long)326L),Qg2int_rpc);
    Qg2int_acknowledge_shutdown = STATIC_SYMBOL("ACKNOWLEDGE-SHUTDOWN",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_acknowledge_shutdown,
	    FIX((SI_Long)336L),Qg2int_icp);
    Qg2int_initialize_gsi_interface = 
	    STATIC_SYMBOL("INITIALIZE-GSI-INTERFACE",AB_package);
    g2int_add_icp_message_type_code(Qg2int_initialize_gsi_interface,
	    FIX((SI_Long)338L),Qg2int_gsi);
    Qg2int_return_initialize_gsi_interface_status = 
	    STATIC_SYMBOL("RETURN-INITIALIZE-GSI-INTERFACE-STATUS",AB_package);
    g2int_add_icp_message_type_code(Qg2int_return_initialize_gsi_interface_status,
	    FIX((SI_Long)339L),Qg2int_gsi);
    Qg2int_intern_list = STATIC_SYMBOL("INTERN-LIST",AB_package);
    g2int_add_icp_message_type_code(Qg2int_intern_list,FIX((SI_Long)351L),
	    Qg2int_rpc);
    Qg2int_define_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_define_resumable_remote_procedure_identifier,
	    FIX((SI_Long)352L),Qg2int_rpc);
    Qg2int_resumable_rpc_error = STATIC_SYMBOL("RESUMABLE-RPC-ERROR",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_resumable_rpc_error,
	    FIX((SI_Long)353L),Qg2int_rpc);
    Qg2int_resumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("RESUMABLE-RPC-ERROR-TO-CALLER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_resumable_rpc_error_to_caller,
	    FIX((SI_Long)354L),Qg2int_rpc);
    Qg2int_create_item_reference = STATIC_SYMBOL("CREATE-ITEM-REFERENCE",
	    AB_package);
    g2int_add_icp_message_type_code(Qg2int_create_item_reference,
	    FIX((SI_Long)355L),Qg2int_rpc);
    Qg2int_start_data_server = STATIC_SYMBOL("START-DATA-SERVER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_start_data_server,
	    FIX((SI_Long)363L),Qg2int_gsi_ds);
    Qg2int_reset_data_server = STATIC_SYMBOL("RESET-DATA-SERVER",AB_package);
    g2int_add_icp_message_type_code(Qg2int_reset_data_server,
	    FIX((SI_Long)364L),Qg2int_gsi_ds);
    if (G2int_active_icp_sockets == UNBOUND)
	G2int_active_icp_sockets = Nil;
    Qg2int_gsi_undefined_context = STATIC_SYMBOL("GSI-UNDEFINED-CONTEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_undefined_context,FIX((SI_Long)-1L));
    Qg2int_gsi_uninitialized_context = 
	    STATIC_SYMBOL("GSI-UNINITIALIZED-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_uninitialized_context,FIX((SI_Long)-2L));
    if (G2int_maximum_object_passing_bandwidth == UNBOUND)
	G2int_maximum_object_passing_bandwidth = FIX((SI_Long)8192L);
    G2int_icp_socket_shutdown_handshake_timeout = FIX((SI_Long)15L);
    if (G2int_icp_socket_connect_negotiation_timeout_default == UNBOUND)
	G2int_icp_socket_connect_negotiation_timeout_default = 
		FIX((SI_Long)60L * IFIX(G2int_fixnum_time_units_per_second));
    G2int_icp_connection_closed = FIX((SI_Long)0L);
    G2int_icp_connection_connect_in_progress = FIX((SI_Long)1L);
    G2int_icp_connection_running = FIX((SI_Long)2L);
    G2int_icp_connection_shutdown_acknowledgement_rundown = FIX((SI_Long)4L);
    G2int_icp_connection_awaiting_acknowledgement = FIX((SI_Long)5L);
    G2int_icp_socket_listening = FIX((SI_Long)6L);
    G2int_icp_socket_error = FIX((SI_Long)7L);
    Qg2int_release_1dot0_icp_version = 
	    STATIC_SYMBOL("RELEASE-1.0-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_1dot0_icp_version,FIX((SI_Long)1L));
    Qg2int_release_2dot0_icp_version = 
	    STATIC_SYMBOL("RELEASE-2.0-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_2dot0_icp_version,FIX((SI_Long)2L));
    Qg2int_reclaim_remote_corresponding_object_icp_version = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-CORRESPONDING-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_reclaim_remote_corresponding_object_icp_version,
	    FIX((SI_Long)2L));
    Qg2int_modify_gsi_sensor_definition_icp_version = 
	    STATIC_SYMBOL("MODIFY-GSI-SENSOR-DEFINITION-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_modify_gsi_sensor_definition_icp_version,
	    FIX((SI_Long)2L));
    Qg2int_double_float_icp_version = 
	    STATIC_SYMBOL("DOUBLE-FLOAT-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_double_float_icp_version,FIX((SI_Long)2L));
    Qg2int_release_3dot0_icp_version = 
	    STATIC_SYMBOL("RELEASE-3.0-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_3dot0_icp_version,FIX((SI_Long)4L));
    Qg2int_release_4dot0_icp_version = 
	    STATIC_SYMBOL("RELEASE-4.0-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_release_4dot0_icp_version,FIX((SI_Long)5L));
    Qg2int_ds_update_interval_as_float_icp_version = 
	    STATIC_SYMBOL("DS-UPDATE-INTERVAL-AS-FLOAT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ds_update_interval_as_float_icp_version,
	    FIX((SI_Long)5L));
    Qg2int_remote_procedure_include_attribute_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ATTRIBUTE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_remote_procedure_include_attribute_icp_version,
	    FIX((SI_Long)5L));
    Qg2int_pass_item_as_handle_icp_version = 
	    STATIC_SYMBOL("PASS-ITEM-AS-HANDLE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pass_item_as_handle_icp_version,FIX((SI_Long)5L));
    Qg2int_pass_item_as_copy_icp_version = 
	    STATIC_SYMBOL("PASS-ITEM-AS-COPY-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_pass_item_as_copy_icp_version,FIX((SI_Long)5L));
    Qg2int_gsi_item_registration_icp_version = 
	    STATIC_SYMBOL("GSI-ITEM-REGISTRATION-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_item_registration_icp_version,
	    FIX((SI_Long)5L));
    Qg2int_gsi_timestamp_as_float_icp_version = 
	    STATIC_SYMBOL("GSI-TIMESTAMP-AS-FLOAT-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_timestamp_as_float_icp_version,
	    FIX((SI_Long)5L));
    Qg2int_shutdown_protocol_icp_version = 
	    STATIC_SYMBOL("SHUTDOWN-PROTOCOL-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_shutdown_protocol_icp_version,FIX((SI_Long)5L));
    Qg2int_new_connect_scheme_icp_version = 
	    STATIC_SYMBOL("NEW-CONNECT-SCHEME-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_new_connect_scheme_icp_version,FIX((SI_Long)5L));
    Qg2int_g2_version_reply_to_gsi_icp_version = 
	    STATIC_SYMBOL("G2-VERSION-REPLY-TO-GSI-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_version_reply_to_gsi_icp_version,
	    FIX((SI_Long)5L));
    Qg2int_wide_strings_icp_version = 
	    STATIC_SYMBOL("WIDE-STRINGS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_wide_strings_icp_version,FIX((SI_Long)6L));
    Qg2int_writing_coalesced_icp_message_group_icp_version = 
	    STATIC_SYMBOL("WRITING-COALESCED-ICP-MESSAGE-GROUP-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_writing_coalesced_icp_message_group_icp_version,
	    FIX((SI_Long)7L));
    Qg2int_supports_icp_version_protocol_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-ICP-VERSION-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_supports_icp_version_protocol_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_remote_value_supports_item_icp_version = 
	    STATIC_SYMBOL("REMOTE-VALUE-SUPPORTS-ITEM-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_remote_value_supports_item_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_supports_optional_remote_value_tags_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-OPTIONAL-REMOTE-VALUE-TAGS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_supports_optional_remote_value_tags_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_evaluation_sequences_and_structures_icp_version = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCES-AND-STRUCTURES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_evaluation_sequences_and_structures_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_resumable_icp_version = STATIC_SYMBOL("RESUMABLE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_resumable_icp_version,FIX((SI_Long)8L));
    Qg2int_new_rpc_kinds_icp_version = 
	    STATIC_SYMBOL("NEW-RPC-KINDS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_new_rpc_kinds_icp_version,FIX((SI_Long)8L));
    Qg2int_value_vector_names_are_symbols_icp_version = 
	    STATIC_SYMBOL("VALUE-VECTOR-NAMES-ARE-SYMBOLS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_value_vector_names_are_symbols_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_does_not_require_enlarge_corresponding_icp_object_index_space_icp_version 
	    = 
	    STATIC_SYMBOL("DOES-NOT-REQUIRE-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_does_not_require_enlarge_corresponding_icp_object_index_space_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_rel4_rpc_protocol_supports_non_objects_icp_version = 
	    STATIC_SYMBOL("REL4-RPC-PROTOCOL-SUPPORTS-NON-OBJECTS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rel4_rpc_protocol_supports_non_objects_icp_version,
	    FIX((SI_Long)8L));
    Qg2int_resumable_gsi_ds_icp_version = 
	    STATIC_SYMBOL("RESUMABLE-GSI-DS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_resumable_gsi_ds_icp_version,FIX((SI_Long)9L));
    Qg2int_remote_procedure_include_all_system_attributes_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ALL-SYSTEM-ATTRIBUTES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_remote_procedure_include_all_system_attributes_icp_version,
	    FIX((SI_Long)9L));
    Qg2int_no_telewindows_clogging_icp_version = 
	    STATIC_SYMBOL("NO-TELEWINDOWS-CLOGGING-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_telewindows_clogging_icp_version,
	    FIX((SI_Long)9L));
    Qg2int_remote_procedure_varargs_p_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-VARARGS-P-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_remote_procedure_varargs_p_icp_version,
	    FIX((SI_Long)9L));
    Qg2int_new_remote_procedure_identifer_protocol_icp_version = 
	    STATIC_SYMBOL("NEW-REMOTE-PROCEDURE-IDENTIFER-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_new_remote_procedure_identifer_protocol_icp_version,
	    FIX((SI_Long)9L));
    Qg2int_rpc_use_value_structure_using_unix_time_icp_version = 
	    STATIC_SYMBOL("RPC-USE-VALUE-STRUCTURE-USING-UNIX-TIME-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_use_value_structure_using_unix_time_icp_version,
	    FIX((SI_Long)10L));
    Qg2int_deregister_corresponding_icp_object_index_space_name_icp_version 
	    = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_deregister_corresponding_icp_object_index_space_name_icp_version,
	    FIX((SI_Long)10L));
    Qg2int_deregister_original_icp_object_icp_version = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_deregister_original_icp_object_icp_version,
	    FIX((SI_Long)10L));
    Qg2int_item_index_space_icp_version = 
	    STATIC_SYMBOL("ITEM-INDEX-SPACE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_item_index_space_icp_version,FIX((SI_Long)10L));
    Qg2int_values_as_handle_icp_version = 
	    STATIC_SYMBOL("VALUES-AS-HANDLE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_values_as_handle_icp_version,FIX((SI_Long)10L));
    Qg2int_gsi_dataservice_uses_full_remote_value_protocol_icp_version = 
	    STATIC_SYMBOL("GSI-DATASERVICE-USES-FULL-REMOTE-VALUE-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_dataservice_uses_full_remote_value_protocol_icp_version,
	    FIX((SI_Long)11L));
    Qg2int_item_reference_icp_version = 
	    STATIC_SYMBOL("ITEM-REFERENCE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_item_reference_icp_version,FIX((SI_Long)12L));
    Qg2int_acknowledge_deregister_corresponding_icp_object_icp_version = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_acknowledge_deregister_corresponding_icp_object_icp_version,
	    FIX((SI_Long)12L));
    Qg2int_abort_icp_task_icp_version = 
	    STATIC_SYMBOL("ABORT-ICP-TASK-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_abort_icp_task_icp_version,FIX((SI_Long)13L));
    Qg2int_deregister_icp_objects_icp_version = 
	    STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_deregister_icp_objects_icp_version,
	    FIX((SI_Long)13L));
    Qg2int_unsigned_short_vector_icp_version = 
	    STATIC_SYMBOL("UNSIGNED-SHORT-VECTOR-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unsigned_short_vector_icp_version,
	    FIX((SI_Long)14L));
    Qg2int_independent_layered_rendering_version = 
	    STATIC_SYMBOL("INDEPENDENT-LAYERED-RENDERING-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_independent_layered_rendering_version,
	    FIX((SI_Long)15L));
    Qg2int_data_servers_can_run_while_inactive_version = 
	    STATIC_SYMBOL("DATA-SERVERS-CAN-RUN-WHILE-INACTIVE-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_data_servers_can_run_while_inactive_version,
	    FIX((SI_Long)15L));
    Qg2int_by_copy_with_handle_supports_references_icp_version = 
	    STATIC_SYMBOL("BY-COPY-WITH-HANDLE-SUPPORTS-REFERENCES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_by_copy_with_handle_supports_references_icp_version,
	    FIX((SI_Long)16L));
    Qg2int_return_g2ds_version_sends_class_icp_version = 
	    STATIC_SYMBOL("RETURN-G2DS-VERSION-SENDS-CLASS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_return_g2ds_version_sends_class_icp_version,
	    FIX((SI_Long)17L));
    Qg2int_supports_non_resumability_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-NON-RESUMABILITY-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_supports_non_resumability_icp_version,
	    FIX((SI_Long)17L));
    Qg2int_gsi_sends_returned_gsi_sensor_as_reference_icp_version = 
	    STATIC_SYMBOL("GSI-SENDS-RETURNED-GSI-SENSOR-AS-REFERENCE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_sends_returned_gsi_sensor_as_reference_icp_version,
	    FIX((SI_Long)18L));
    Qg2int_no_licence_icp_version = STATIC_SYMBOL("NO-LICENCE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_licence_icp_version,FIX((SI_Long)18L));
    Qg2int_supports_new_references_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-NEW-REFERENCES-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_supports_new_references_icp_version,
	    FIX((SI_Long)18L));
    Qg2int_g2_supports_update_with_delete_icp_version = 
	    STATIC_SYMBOL("G2-SUPPORTS-UPDATE-WITH-DELETE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_supports_update_with_delete_icp_version,
	    FIX((SI_Long)19L));
    Qg2int_t2_supports_item_layer_change = 
	    STATIC_SYMBOL("T2-SUPPORTS-ITEM-LAYER-CHANGE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_t2_supports_item_layer_change,FIX((SI_Long)20L));
    Qg2int_do_not_reformat_message_icp_version = 
	    STATIC_SYMBOL("DO-NOT-REFORMAT-MESSAGE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_do_not_reformat_message_icp_version,
	    FIX((SI_Long)21L));
    Qg2int_no_frame_serial_index_space_icp_version = 
	    STATIC_SYMBOL("NO-FRAME-SERIAL-INDEX-SPACE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_frame_serial_index_space_icp_version,
	    FIX((SI_Long)21L));
    Qg2int_intern_keyword_icp_version = 
	    STATIC_SYMBOL("INTERN-KEYWORD-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_intern_keyword_icp_version,FIX((SI_Long)22L));
    Qg2int_long_string_icp_version = 
	    STATIC_SYMBOL("LONG-STRING-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_long_string_icp_version,FIX((SI_Long)23L));
    Qg2int_send_text_of_expressions_for_g2ds_icp_version = 
	    STATIC_SYMBOL("SEND-TEXT-OF-EXPRESSIONS-FOR-G2DS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_send_text_of_expressions_for_g2ds_icp_version,
	    FIX((SI_Long)24L));
    Qg2int_remote_procedure_include_all_system_attributes_except_icp_version 
	    = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_remote_procedure_include_all_system_attributes_except_icp_version,
	    FIX((SI_Long)25L));
    Qg2int_transparent_color_index_icp_version = 
	    STATIC_SYMBOL("TRANSPARENT-COLOR-INDEX-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_transparent_color_index_icp_version,
	    FIX((SI_Long)26L));
    Qg2int_compressed_image_data_chunk_icp_version = 
	    STATIC_SYMBOL("COMPRESSED-IMAGE-DATA-CHUNK-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_compressed_image_data_chunk_icp_version,
	    FIX((SI_Long)27L));
    Qg2int_dialog_component_with_font_icp_version = 
	    STATIC_SYMBOL("DIALOG-COMPONENT-WITH-FONT-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_dialog_component_with_font_icp_version,
	    FIX((SI_Long)28L));
    Qg2int_supports_font_in_grid_view_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-FONT-IN-GRID-VIEW-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_supports_font_in_grid_view_icp_version,
	    FIX((SI_Long)29L));
    Qg2int_native_long_icp_version = 
	    STATIC_SYMBOL("NATIVE-LONG-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_native_long_icp_version,FIX((SI_Long)30L));
    G2int_newest_icp_version = FIX((SI_Long)30L);
    G2int_gsi_connection_initializing = FIX((SI_Long)1L);
    G2int_gsi_connection_established = FIX((SI_Long)2L);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_socket_g2_struct = 
	    STATIC_SYMBOL("SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_socket = STATIC_SYMBOL("SOCKET",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_socket_g2_struct,
	    Qg2int_socket,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_socket,
	    Qg2_defstruct_structure_name_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_socket == UNBOUND)
	G2int_the_type_description_of_socket = Nil;
    string_constant_3 = STATIC_STRING("43Dy8l83Jy1n83Jy8m8k1l8m0000000klk0k0");
    temp = G2int_the_type_description_of_socket;
    G2int_the_type_description_of_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_3));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_socket_g2_struct,
	    G2int_the_type_description_of_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_socket,
	    G2int_the_type_description_of_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_sockets,
	    G2int_chain_of_available_sockets);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_socket_count = STATIC_SYMBOL("SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_socket_count,G2int_socket_count);
    g2int_record_system_variable(Qg2int_socket_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_socket,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_socket,reclaim_structure_for_socket);
    Qg2_defstruct_structure_name_icp_socket_g2_struct = 
	    STATIC_SYMBOL("ICP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_socket = STATIC_SYMBOL("ICP-SOCKET",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    Qg2int_icp_socket,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_icp_socket,
	    Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_icp_socket == UNBOUND)
	G2int_the_type_description_of_icp_socket = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8l83-ay1o83-ay83Jy8m8k1l83Jy0000001n1m8o83Jy1n8n83*gy1p8304y83-Uy83-Vy83*Py83-by1m8p83=fyk3qyk0k0");
    temp = G2int_the_type_description_of_icp_socket;
    G2int_the_type_description_of_icp_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_4));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    G2int_the_type_description_of_icp_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_icp_socket,
	    G2int_the_type_description_of_icp_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_icp_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_icp_sockets,
	    G2int_chain_of_available_icp_sockets);
    g2int_record_system_variable(Qg2int_chain_of_available_icp_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_icp_socket_count = STATIC_SYMBOL("ICP-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_socket_count,G2int_icp_socket_count);
    g2int_record_system_variable(Qg2int_icp_socket_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_icp_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_icp_socket,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_icp_socket,reclaim_structure_for_icp_socket);
    Qg2int_initial = STATIC_SYMBOL("INITIAL",AB_package);
    Qg2int_unknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant = STATIC_STRING("ICP-SOCKET ");
    Qg2int_closed = STATIC_SYMBOL("CLOSED",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),Qg2int_closed);
    Qg2int_connect_in_progress = STATIC_SYMBOL("CONNECT-IN-PROGRESS",
	    AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1L),
	    Qg2int_connect_in_progress);
    Qg2int_running = STATIC_SYMBOL("RUNNING",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)2L),Qg2int_running);
    Qg2int_shutdown_requested = STATIC_SYMBOL("SHUTDOWN-REQUESTED",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)3L),
	    Qg2int_shutdown_requested);
    Qg2int_shutdown_acknowledgement_rundown = 
	    STATIC_SYMBOL("SHUTDOWN-ACKNOWLEDGEMENT-RUNDOWN",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4L),
	    Qg2int_shutdown_acknowledgement_rundown);
    Qg2int_awaiting_acknowledgement = 
	    STATIC_SYMBOL("AWAITING-ACKNOWLEDGEMENT",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)5L),
	    Qg2int_awaiting_acknowledgement);
    Qg2int_listening = STATIC_SYMBOL("LISTENING",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)6L),
	    Qg2int_listening);
    list_constant_14 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7L),Qerror);
    list_constant = STATIC_LIST((SI_Long)8L,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14);
    Qg2int_bizzare_state = STATIC_SYMBOL("BIZZARE-STATE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnil,Qg2int_bizzare_state);
    string_constant_1 = STATIC_STRING(" in state ~D (~a)");
    Qg2int_highest_icp_socket_session_id = 
	    STATIC_SYMBOL("HIGHEST-ICP-SOCKET-SESSION-ID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_highest_icp_socket_session_id,
	    G2int_highest_icp_socket_session_id);
    g2int_record_system_variable(Qg2int_highest_icp_socket_session_id,
	    Qg2int_int1,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_temporary_output = STATIC_SYMBOL("TEMPORARY-OUTPUT",AB_package);
    Qg2int_input = STATIC_SYMBOL("INPUT",AB_package);
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_icp_connection_timeout_task_1 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-1",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_connection_timeout_task_2 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-2",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_icp_connection_timeout_task_1,
	    STATIC_FUNCTION(g2int_icp_connection_timeout_task_1,NIL,FALSE,
	    2,2));
    Qg2int_connection_attempt_timed_out = 
	    STATIC_SYMBOL("CONNECTION-ATTEMPT-TIMED-OUT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_icp_connection_timeout_task_2,
	    STATIC_FUNCTION(g2int_icp_connection_timeout_task_2,NIL,FALSE,
	    1,1));
    Qg2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors 
	    = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    G2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors);
    g2int_record_system_variable(Qg2int_available_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors 
	    = 
	    STATIC_SYMBOL("COUNT-OF-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    G2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors);
    g2int_record_system_variable(Qg2int_count_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry 
	    = 
	    STATIC_SYMBOL("MUTATE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH-TREE-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry,
	    STATIC_FUNCTION(g2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry,
	    NIL,FALSE,3,3));
    G2int_fp_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry 
	    = 
	    SYMBOL_FUNCTION(Qg2int_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry);
    Qg2int_frame_serial_number_to_item_table_tree_for_hash = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH",
	    AB_package);
    Qg2int_available_variable_fill_icp_buffer_4096_vectors = 
	    STATIC_SYMBOL("AVAILABLE-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_available_variable_fill_icp_buffer_4096_vectors,
	    G2int_available_variable_fill_icp_buffer_4096_vectors);
    g2int_record_system_variable(Qg2int_available_variable_fill_icp_buffer_4096_vectors,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_count_of_variable_fill_icp_buffer_4096_vectors = 
	    STATIC_SYMBOL("COUNT-OF-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_variable_fill_icp_buffer_4096_vectors,
	    G2int_count_of_variable_fill_icp_buffer_4096_vectors);
    g2int_record_system_variable(Qg2int_count_of_variable_fill_icp_buffer_4096_vectors,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    Qg2int_recycled_variable_fill_icp_buffers = 
	    STATIC_SYMBOL("RECYCLED-VARIABLE-FILL-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_recycled_variable_fill_icp_buffers,
	    G2int_recycled_variable_fill_icp_buffers);
    Qg2int_int2 = STATIC_SYMBOL("INT2",AB_package);
    g2int_record_system_variable(Qg2int_recycled_variable_fill_icp_buffers,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_transmitted_variable_fill_icp_buffers = 
	    STATIC_SYMBOL("TRANSMITTED-VARIABLE-FILL-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_transmitted_variable_fill_icp_buffers,
	    G2int_transmitted_variable_fill_icp_buffers);
    g2int_record_system_variable(Qg2int_transmitted_variable_fill_icp_buffers,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_icp_buffer_g2_struct = 
	    STATIC_SYMBOL("ICP-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_buffer = STATIC_SYMBOL("ICP-BUFFER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    Qg2int_icp_buffer,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_icp_buffer,
	    Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_icp_buffer == UNBOUND)
	G2int_the_type_description_of_icp_buffer = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8l83-Ry1n83-Ry8m8k1l8m0000001m1n8n83*dy1l83-Sy1m8p83=dykqk0k0");
    temp = G2int_the_type_description_of_icp_buffer;
    G2int_the_type_description_of_icp_buffer = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    G2int_the_type_description_of_icp_buffer,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_icp_buffer,
	    G2int_the_type_description_of_icp_buffer,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_icp_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_icp_buffers,
	    G2int_chain_of_available_icp_buffers);
    g2int_record_system_variable(Qg2int_chain_of_available_icp_buffers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_icp_buffer_count = STATIC_SYMBOL("ICP-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_buffer_count,G2int_icp_buffer_count);
    g2int_record_system_variable(Qg2int_icp_buffer_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_icp_buffer = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_icp_buffer,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_icp_buffer,reclaim_structure_for_icp_buffer);
    Qg2int_recycled_icp_buffers = STATIC_SYMBOL("RECYCLED-ICP-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_recycled_icp_buffers,
	    G2int_recycled_icp_buffers);
    g2int_record_system_variable(Qg2int_recycled_icp_buffers,Qg2int_int2,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_icp_port_g2_struct = 
	    STATIC_SYMBOL("ICP-PORT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_icp_port = STATIC_SYMBOL("ICP-PORT",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_port_g2_struct,
	    Qg2int_icp_port,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_icp_port,
	    Qg2_defstruct_structure_name_icp_port_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_icp_port == UNBOUND)
	G2int_the_type_description_of_icp_port = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l83-Wy1n83-Wy8m8k1l8m0000001m1n8n83*ey1o83-Ty83=Ey83-Xy83=Qy1m8p83=eyk3Gyk0k0");
    temp = G2int_the_type_description_of_icp_port;
    G2int_the_type_description_of_icp_port = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_6));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_icp_port_g2_struct,
	    G2int_the_type_description_of_icp_port,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_icp_port,
	    G2int_the_type_description_of_icp_port,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_icp_ports = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-PORTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_icp_ports,
	    G2int_chain_of_available_icp_ports);
    g2int_record_system_variable(Qg2int_chain_of_available_icp_ports,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_icp_port_count = STATIC_SYMBOL("ICP-PORT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_port_count,G2int_icp_port_count);
    g2int_record_system_variable(Qg2int_icp_port_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_icp_port = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_icp_port,NIL,FALSE,
	    1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_icp_port,reclaim_structure_for_icp_port);
    SET_SYMBOL_FUNCTION(Qg2int_item_index_space,
	    STATIC_FUNCTION(g2int_item_index_space,NIL,FALSE,1,1));
    Qg2int_item_with_handle_index_space = 
	    STATIC_SYMBOL("ITEM-WITH-HANDLE-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_item_with_handle_index_space,
	    STATIC_FUNCTION(g2int_item_with_handle_index_space,NIL,FALSE,1,1));
    Qg2int_current_icp_port = STATIC_SYMBOL("CURRENT-ICP-PORT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_icp_port,G2int_current_icp_port);
    g2int_record_system_variable(Qg2int_current_icp_port,Qg2int_int1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    if (G2int_current_icp_socket == UNBOUND)
	G2int_current_icp_socket = Nil;
    Qg2int_current_standard_icp_object_index_space = 
	    STATIC_SYMBOL("CURRENT-STANDARD-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_standard_icp_object_index_space,
	    G2int_current_standard_icp_object_index_space);
    g2int_record_system_variable(Qg2int_current_standard_icp_object_index_space,
	    Qg2int_int1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_temporary_icp_object_index_space = 
	    STATIC_SYMBOL("CURRENT-TEMPORARY-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_temporary_icp_object_index_space,
	    G2int_current_temporary_icp_object_index_space);
    g2int_record_system_variable(Qg2int_current_temporary_icp_object_index_space,
	    Qg2int_int1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_frame_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",
	    AB_package);
    if (G2int_do_not_reclaim_runs_while_inactive_entries == UNBOUND)
	G2int_do_not_reclaim_runs_while_inactive_entries = Nil;
    if (G2int_icp_output_ports_to_flush == UNBOUND)
	G2int_icp_output_ports_to_flush = Nil;
    if (G2int_with_icp_buffer_coelescing_scopeqm == UNBOUND)
	G2int_with_icp_buffer_coelescing_scopeqm = Nil;
    Qg2int_flush_icp_output_ports = STATIC_SYMBOL("FLUSH-ICP-OUTPUT-PORTS",
	    AB_package);
    g2int_def_bombout_clean_up_function(Qg2int_flush_icp_output_ports);
    SET_SYMBOL_FUNCTION(Qg2int_flush_icp_output_ports,
	    STATIC_FUNCTION(g2int_flush_icp_output_ports,NIL,FALSE,0,0));
    if (G2int_disable_resumability == UNBOUND)
	G2int_disable_resumability = Nil;
    if (G2int_starresumable_icp_statestar == UNBOUND)
	G2int_starresumable_icp_statestar = Nil;
    Qg2int_suspend = STATIC_SYMBOL("SUSPEND",AB_package);
    if (G2int_icp_suspend == UNBOUND)
	G2int_icp_suspend = LIST_1(Qg2int_suspend);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    if (G2int_trif_block_value_alist == UNBOUND)
	G2int_trif_block_value_alist = Nil;
}
