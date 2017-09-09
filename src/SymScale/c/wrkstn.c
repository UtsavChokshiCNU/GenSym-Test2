/* wrkstn.c
 * Input file:  workstation.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "wrkstn.h"


/* PUSH-MORE-DETAILED-SPOT */
Object push_more_detailed_spot(mouse_pointer,spot,frame_represented_qm)
    Object mouse_pointer, spot, frame_represented_qm;
{
    Object stack_of_spots_qm, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value;

    x_note_fn_call(115,0);
    stack_of_spots_qm = ISVREF(mouse_pointer,(SI_Long)5L);
    SVREF(spot,FIX((SI_Long)4L)) = frame_represented_qm;
    frame_serial_number_setf_arg = frame_represented_qm ? 
	    ISVREF(frame_represented_qm,(SI_Long)3L) : Nil;
    old = ISVREF(spot,(SI_Long)5L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(spot,FIX((SI_Long)5L)) = svref_new_value;
    SVREF(spot,FIX((SI_Long)1L)) = mouse_pointer;
    SVREF(spot,FIX((SI_Long)2L)) = stack_of_spots_qm;
    SVREF(mouse_pointer,FIX((SI_Long)5L)) = spot;
    return VALUES_1(Nil);
}

/* PUSH-LAST-SPOT */
Object push_last_spot(mouse_pointer,spot,frame_represented_qm)
    Object mouse_pointer, spot, frame_represented_qm;
{
    x_note_fn_call(115,1);
    SVREF(spot,FIX((SI_Long)3L)) = Nil;
    push_more_detailed_spot(mouse_pointer,spot,frame_represented_qm);
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* VALIDATE-MOUSE-POINTERS */
Object validate_mouse_pointers(workstation)
    Object workstation;
{
    Object mouse_pointers, mouse_pointer, ab_loop_list_;
    Object deepest_invalid_spot_qm, spot_qm, frame_represented_qm;
    Object gensymed_symbol, x, y, xa, ya, type_description_of_spot;
    Object image_plane, reference_serial_number;
    SI_Long i;
    char temp;

    x_note_fn_call(115,2);
    mouse_pointers = ISVREF(workstation,(SI_Long)14L);
    i = (SI_Long)1L;
  next_loop:
    if (i > (SI_Long)2L)
	goto end_loop;
    mouse_pointer = Nil;
    ab_loop_list_ = mouse_pointers;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    mouse_pointer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    deepest_invalid_spot_qm = Nil;
    spot_qm = ISVREF(mouse_pointer,(SI_Long)5L);
    frame_represented_qm = Nil;
  next_loop_2:
    if ( !TRUEP(spot_qm))
	goto end_loop_2;
    frame_represented_qm = ISVREF(spot_qm,(SI_Long)4L);
    if (frame_represented_qm) {
	gensymed_symbol = ISVREF(frame_represented_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(frame_represented_qm) ? 
		EQ(ISVREF(frame_represented_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(spot_qm,(SI_Long)5L);
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	deepest_invalid_spot_qm = spot_qm;
    gensymed_symbol = ISVREF(spot_qm,(SI_Long)0L);
    type_description_of_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    if (EQ(type_description_of_spot,
	    The_type_description_of_kb_workspace_image_plane_spot) || 
	    EQ(type_description_of_spot,
	    The_type_description_of_non_kb_workspace_image_plane_spot) || 
	    EQ(type_description_of_spot,
	    The_type_description_of_image_plane_spot)) {
	image_plane = ISVREF(spot_qm,(SI_Long)6L);
	reference_serial_number = ISVREF(spot_qm,(SI_Long)7L);
	temp =  !FIXNUM_EQ(ISVREF(image_plane,(SI_Long)1L),
		reference_serial_number);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	deepest_invalid_spot_qm = spot_qm;
    spot_qm = ISVREF(spot_qm,(SI_Long)2L);
    goto next_loop_2;
  end_loop_2:
    if (deepest_invalid_spot_qm)
	invalidate_mouse_pointer(mouse_pointer,deepest_invalid_spot_qm);
    goto next_loop_1;
  end_loop_1:;
    mouse_pointers = ISVREF(workstation,(SI_Long)15L);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* INVALIDATE-MOUSE-POINTER */
Object invalidate_mouse_pointer(mouse_pointer,deepest_invalid_spot)
    Object mouse_pointer, deepest_invalid_spot;
{
    Object spot, svref_new_value, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(115,3);
    SVREF(mouse_pointer,FIX((SI_Long)6L)) = T;
    spot = Nil;
  next_loop:
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    svref_new_value = ISVREF(spot,(SI_Long)2L);
    SVREF(mouse_pointer,FIX((SI_Long)5L)) = svref_new_value;
    SVREF(spot,FIX((SI_Long)2L)) = Nil;
    gensymed_symbol = ISVREF(spot,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = spot;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    if (EQ(deepest_invalid_spot,spot))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:;
    push_more_detailed_spot(mouse_pointer,make_invalid_spot_1(),Nil);
    return VALUES_1(Nil);
}

Object The_type_description_of_workstation_event = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstation_events, Qchain_of_available_workstation_events);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_event_count, Qworkstation_event_count);

Object Chain_of_available_workstation_events_vector = UNBOUND;

/* WORKSTATION-EVENT-STRUCTURE-MEMORY-USAGE */
Object workstation_event_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(115,4);
    temp = Workstation_event_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSTATION-EVENT-COUNT */
Object outstanding_workstation_event_count()
{
    Object def_structure_workstation_event_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(115,5);
    gensymed_symbol = IFIX(Workstation_event_count);
    def_structure_workstation_event_variable = 
	    Chain_of_available_workstation_events;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_workstation_event_variable))
	goto end_loop;
    def_structure_workstation_event_variable = 
	    ISVREF(def_structure_workstation_event_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WORKSTATION-EVENT-1-1 */
Object reclaim_workstation_event_1_1(workstation_event)
    Object workstation_event;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(115,6);
    inline_note_reclaim_cons(workstation_event,Nil);
    structure_being_reclaimed = workstation_event;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(workstation_event,(SI_Long)8L));
      SVREF(workstation_event,FIX((SI_Long)8L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_workstation_events_vector,
	    IFIX(Current_thread_index));
    SVREF(workstation_event,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workstation_events_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workstation_event;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSTATION-EVENT */
Object reclaim_structure_for_workstation_event(workstation_event)
    Object workstation_event;
{
    x_note_fn_call(115,7);
    return reclaim_workstation_event_1_1(workstation_event);
}

static Object Qg2_defstruct_structure_name_workstation_event_g2_struct;  /* g2-defstruct-structure-name::workstation-event-g2-struct */

/* MAKE-PERMANENT-WORKSTATION-EVENT-STRUCTURE-INTERNAL */
Object make_permanent_workstation_event_structure_internal()
{
    Object def_structure_workstation_event_variable;
    Object defstruct_g2_workstation_event_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(115,8);
    def_structure_workstation_event_variable = Nil;
    atomic_incff_symval(Qworkstation_event_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workstation_event_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_workstation_event_variable = the_array;
	SVREF(defstruct_g2_workstation_event_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_event_g2_struct;
	def_structure_workstation_event_variable = 
		defstruct_g2_workstation_event_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workstation_event_variable);
}

/* MAKE-WORKSTATION-EVENT-1 */
Object make_workstation_event_1()
{
    Object def_structure_workstation_event_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(115,9);
    def_structure_workstation_event_variable = 
	    ISVREF(Chain_of_available_workstation_events_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workstation_event_variable) {
	svref_arg_1 = Chain_of_available_workstation_events_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_workstation_event_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workstation_event_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_event_g2_struct;
    }
    else
	def_structure_workstation_event_variable = 
		make_permanent_workstation_event_structure_internal();
    inline_note_allocate_cons(def_structure_workstation_event_variable,Nil);
    SVREF(def_structure_workstation_event_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_workstation_event_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_workstation_event_variable,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_workstation_event_variable);
}

/* RECLAIM-WORKSTATION-EVENT */
Object reclaim_workstation_event(workstation_event)
    Object workstation_event;
{
    Object event_detail_qm, element, ab_loop_list_;

    x_note_fn_call(115,10);
    event_detail_qm = ISVREF(workstation_event,(SI_Long)10L);
    if (CONSP(event_detail_qm)) {
	element = Nil;
	ab_loop_list_ = event_detail_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(element))
	    reclaim_text_string(element);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(event_detail_qm);
    }
    else if (text_string_p(event_detail_qm))
	reclaim_text_string(event_detail_qm);
    SVREF(workstation_event,FIX((SI_Long)10L)) = Nil;
    return reclaim_workstation_event_1_1(workstation_event);
}

/* COPY-WORKSTATION-EVENT */
Object copy_workstation_event(event)
    Object event;
{
    Object new_event, svref_new_value;

    x_note_fn_call(115,11);
    new_event = make_workstation_event_1();
    svref_new_value = ISVREF(event,(SI_Long)1L);
    SVREF(new_event,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)3L);
    SVREF(new_event,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)4L);
    SVREF(new_event,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)2L);
    SVREF(new_event,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)5L);
    SVREF(new_event,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)6L);
    SVREF(new_event,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = ISVREF(event,(SI_Long)7L);
    SVREF(new_event,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = copy_frame_serial_number(ISVREF(event,(SI_Long)8L));
    SVREF(new_event,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = copy_event_plist(ISVREF(event,(SI_Long)10L));
    SVREF(new_event,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(new_event);
}

/* EVENT-TIME-DIFFERENCE */
Object event_time_difference(later_event_time,earlier_event_time)
    Object later_event_time, earlier_event_time;
{
    x_note_fn_call(115,12);
    if (FIXNUM_GE(later_event_time,earlier_event_time))
	return VALUES_1(FIXNUM_MINUS(later_event_time,earlier_event_time));
    else {
	later_event_time = FIXNUM_MINUS(later_event_time,earlier_event_time);
	later_event_time = FIXNUM_ADD1(FIXNUM_ADD(later_event_time,
		Event_time_mask));
	return VALUES_1(FIXNUM_ADD1(later_event_time));
    }
}

/* RECLAIM-WORKSTATION-EVENT-QUEUE */
Object reclaim_workstation_event_queue(workstation_event_queue)
    Object workstation_event_queue;
{
    Object queue_sublist, workstation_event;

    x_note_fn_call(115,13);
    queue_sublist = ISVREF(workstation_event_queue,(SI_Long)1L);
    workstation_event = Nil;
  next_loop:
    if ( !TRUEP(queue_sublist))
	goto end_loop;
    workstation_event = M_CAR(queue_sublist);
    queue_sublist = M_CDR(queue_sublist);
    reclaim_workstation_event(workstation_event);
    goto next_loop;
  end_loop:;
    return reclaim_queue(workstation_event_queue);
}

/* ENQUEUE-WORKSTATION-EVENT */
Object enqueue_workstation_event varargs_1(int, n)
{
    Object workstation, key_code, cursor_x, cursor_y, timestamp, window_qm;
    Object pane_qm, image_plane_qm;
    Object event_detail_qm, workstation_event, workspace_qm;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value, queue;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,14);
    INIT_ARGS_nonrelocating();
    workstation = REQUIRED_ARG_nonrelocating();
    key_code = REQUIRED_ARG_nonrelocating();
    cursor_x = REQUIRED_ARG_nonrelocating();
    cursor_y = REQUIRED_ARG_nonrelocating();
    timestamp = REQUIRED_ARG_nonrelocating();
    window_qm = REQUIRED_ARG_nonrelocating();
    pane_qm = REQUIRED_ARG_nonrelocating();
    image_plane_qm = REQUIRED_ARG_nonrelocating();
    event_detail_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workstation_event = make_workstation_event_1();
    SVREF(workstation_event,FIX((SI_Long)1L)) = key_code;
    SVREF(workstation_event,FIX((SI_Long)3L)) = cursor_x;
    SVREF(workstation_event,FIX((SI_Long)4L)) = cursor_y;
    SVREF(workstation_event,FIX((SI_Long)2L)) = timestamp;
    SVREF(workstation_event,FIX((SI_Long)5L)) = window_qm;
    SVREF(workstation_event,FIX((SI_Long)6L)) = pane_qm;
    SVREF(workstation_event,FIX((SI_Long)7L)) = image_plane_qm;
    SVREF(workstation_event,FIX((SI_Long)10L)) = event_detail_qm;
    if (image_plane_qm) {
	workspace_qm = ISVREF(image_plane_qm,(SI_Long)5L);
	frame_serial_number_setf_arg = workspace_qm ? ISVREF(workspace_qm,
		(SI_Long)3L) : Nil;
    }
    else
	frame_serial_number_setf_arg = Nil;
    old = ISVREF(workstation_event,(SI_Long)8L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(workstation_event,FIX((SI_Long)8L)) = svref_new_value;
    queue = ISVREF(workstation,(SI_Long)2L);
    if (queue_empty_p(queue))
	maybe_schedule_service_workstation(workstation,T);
    queue_insert(queue,workstation_event);
    return VALUES_1(workstation_event);
}

DEFINE_VARIABLE_WITH_SYMBOL(Servicing_workstation_event, Qservicing_workstation_event);

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation_event, Qcurrent_workstation_event);

/* REQUEUE-WORKSTATION-EVENT */
Object requeue_workstation_event(workstation,workstation_event)
    Object workstation, workstation_event;
{
    Object pushed_back_workstation_event, queue;

    x_note_fn_call(115,15);
    pushed_back_workstation_event = copy_workstation_event(workstation_event);
    queue = ISVREF(workstation,(SI_Long)2L);
    SVREF(pushed_back_workstation_event,FIX((SI_Long)9L)) = T;
    if (queue_empty_p(queue))
	maybe_schedule_service_workstation(workstation,T);
    return queue_push(queue,pushed_back_workstation_event);
}

/* FLUSH-PENDING-MOUSE-MOTION-EVENTS */
Object flush_pending_mouse_motion_events(workstation)
    Object workstation;
{
    Object queue, event, key_code, unicode;
    SI_Long temp;
    char temp_1;

    x_note_fn_call(115,16);
    queue = ISVREF(workstation,(SI_Long)2L);
    event = Nil;
  next_loop:
    event = queue_peek(queue);
    if (event) {
	key_code = ISVREF(event,(SI_Long)1L);
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ?
		     IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    temp = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	temp_1 = temp == (SI_Long)771L;
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	goto end_loop;
    reclaim_workstation_event(queue_pop(queue));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qicp;                /* icp */

static Object Qtelewindows;        /* telewindows */

static Object Qnative;             /* native */

static Object Qx11_window;         /* x11-window */

/* START-TRACKING-MOUSE-IN-CURRENT-WORKSTATION-CONTEXT */
Object start_tracking_mouse_in_current_workstation_context()
{
    Object temp, icp_output_port_qm, current_icp_port, current_icp_socket;
    Object temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(115,17);
    temp = Current_workstation_context;
    SVREF(temp,FIX((SI_Long)7L)) = T;
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)4L))) {
	temp = Current_workstation;
	SVREF(temp,FIX((SI_Long)4L)) = T;
	if (printing_window_p(Current_workstation_window) || 
		FIXNUM_LT(Icp_window_protocol_supports_v4_mouse_messages,
		ISVREF(Current_workstation_window,(SI_Long)11L))) {
	    if (EQ(Type_of_current_workstation_window,Qicp)) {
		icp_output_port_qm = ISVREF(Current_workstation_window,
			(SI_Long)12L);
		if (icp_output_port_qm && 
			icp_connection_open_p(ISVREF(icp_output_port_qm,
			(SI_Long)2L))) {
		    current_icp_port = icp_output_port_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			    11);
		      current_icp_socket = ISVREF(Current_icp_port,
			      (SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			      10);
			temp_1 = IFIX(ISVREF(Current_icp_socket,
				(SI_Long)22L)) >= (SI_Long)17L ? 
				ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
			if (temp_1);
			else
			    temp_1 = EQ(ISVREF(Current_icp_socket,
				    (SI_Long)25L),Qtelewindows) ? T : Nil;
			disable_resumability = temp_1;
			PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
				9);
			  number_of_icp_bytes_for_message_series = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
				  8);
			    icp_buffers_for_message_group = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				    7);
			      icp_buffer_of_start_of_message_series_qm = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				      6);
				icp_byte_position_of_start_of_message_series_qm 
					= Nil;
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
					number_of_icp_bytes_in_message_group 
						= FIX((SI_Long)0L);
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
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_2 = 
							g2ext_unix_time_as_float();
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)2L);
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							gensymed_symbol_2);
					    }
					    if (icp_connection_open_p(Current_icp_socket) 
						    &&  
						    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
							{
						temp_1 = 
							start_mouse_tracking_in_window(Current_workstation_window);
						end_icp_message_group();
					    }
					    else
						temp_1 = Nil;
					    if (Profiling_enabled_qm) {
						gensymed_symbol_3 = 
							g2ext_unix_time_as_float();
						gensymed_symbol_4 = 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_5 = 
							gensymed_symbol_3 
							- gensymed_symbol_4;
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)6L);
						aref_new_value = 
							gensymed_symbol_5 
							+ 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)6L),
							(SI_Long)0L);
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							aref_new_value);
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)2L);
						aref_new_value = 
							gensymed_symbol ? 
							gensymed_symbol_1 
							+ 
							gensymed_symbol_5 
							+ 
							(gensymed_symbol_4 
							- 
							gensymed_symbol_2) 
							: gensymed_symbol_3;
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							aref_new_value);
					    }
					    result = VALUES_1(temp_1);
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
	    else {
		start_mouse_tracking_in_window(Current_workstation_window);
		return start_or_restart_native_window_heartbeat();
	    }
	}
	else if (EQ(Type_of_current_workstation_window,Qnative) || 
		EQ(Type_of_current_workstation_window,Qx11_window))
	    return start_mouse_tracking(Current_workstation_native_window_qm);
	else if (EQ(Type_of_current_workstation_window,Qicp)) {
	    icp_output_port_qm = ISVREF(Current_workstation_window,
		    (SI_Long)12L);
	    if (icp_output_port_qm && 
		    icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
		current_icp_port = icp_output_port_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(ISVREF(Current_icp_socket,
				(SI_Long)25L),Qtelewindows) ? T : Nil;
		    disable_resumability = temp_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			    9);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      8);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				7);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				  6);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
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
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp_1 = 
						    send_icp_telewindows_start_mouse_tracking();
					    end_icp_message_group();
					}
					else
					    temp_1 = Nil;
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					}
					result = VALUES_1(temp_1);
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
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* STOP-TRACKING-MOUSE-IN-CURRENT-WORKSTATION-CONTEXT */
Object stop_tracking_mouse_in_current_workstation_context()
{
    Object temp, icp_output_port_qm, current_icp_port, current_icp_socket;
    Object temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(115,18);
    temp = Current_workstation_context;
    SVREF(temp,FIX((SI_Long)7L)) = Nil;
    if (ISVREF(Current_workstation,(SI_Long)4L)) {
	temp = Current_workstation;
	SVREF(temp,FIX((SI_Long)4L)) = Nil;
	if (printing_window_p(Current_workstation_window) || 
		FIXNUM_LT(Icp_window_protocol_supports_v4_mouse_messages,
		ISVREF(Current_workstation_window,(SI_Long)11L))) {
	    if (EQ(Type_of_current_workstation_window,Qicp)) {
		icp_output_port_qm = ISVREF(Current_workstation_window,
			(SI_Long)12L);
		if (icp_output_port_qm && 
			icp_connection_open_p(ISVREF(icp_output_port_qm,
			(SI_Long)2L))) {
		    current_icp_port = icp_output_port_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			    11);
		      current_icp_socket = ISVREF(Current_icp_port,
			      (SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			      10);
			temp_1 = IFIX(ISVREF(Current_icp_socket,
				(SI_Long)22L)) >= (SI_Long)17L ? 
				ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
			if (temp_1);
			else
			    temp_1 = EQ(ISVREF(Current_icp_socket,
				    (SI_Long)25L),Qtelewindows) ? T : Nil;
			disable_resumability = temp_1;
			PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
				9);
			  number_of_icp_bytes_for_message_series = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
				  8);
			    icp_buffers_for_message_group = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				    7);
			      icp_buffer_of_start_of_message_series_qm = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				      6);
				icp_byte_position_of_start_of_message_series_qm 
					= Nil;
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
					number_of_icp_bytes_in_message_group 
						= FIX((SI_Long)0L);
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
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_2 = 
							g2ext_unix_time_as_float();
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)2L);
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							gensymed_symbol_2);
					    }
					    if (icp_connection_open_p(Current_icp_socket) 
						    &&  
						    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
							{
						stop_mouse_tracking_in_window(Current_workstation_window);
						end_icp_message_group();
					    }
					    if (Profiling_enabled_qm) {
						gensymed_symbol_3 = 
							g2ext_unix_time_as_float();
						gensymed_symbol_4 = 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_5 = 
							gensymed_symbol_3 
							- gensymed_symbol_4;
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)6L);
						aref_new_value = 
							gensymed_symbol_5 
							+ 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)6L),
							(SI_Long)0L);
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							aref_new_value);
						temp = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)2L);
						aref_new_value = 
							gensymed_symbol ? 
							gensymed_symbol_1 
							+ 
							gensymed_symbol_5 
							+ 
							(gensymed_symbol_4 
							- 
							gensymed_symbol_2) 
							: gensymed_symbol_3;
						DFLOAT_ISASET_1(temp,
							(SI_Long)0L,
							aref_new_value);
					    }
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
	    }
	    else {
		stop_mouse_tracking_in_window(Current_workstation_window);
		start_or_restart_native_window_heartbeat();
	    }
	}
	else if (EQ(Type_of_current_workstation_window,Qx11_window))
	    stop_mouse_tracking_in_local_window(Current_workstation_window);
	else if (EQ(Type_of_current_workstation_window,Qicp)) {
	    icp_output_port_qm = ISVREF(Current_workstation_window,
		    (SI_Long)12L);
	    if (icp_output_port_qm && 
		    icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
		current_icp_port = icp_output_port_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(ISVREF(Current_icp_socket,
				(SI_Long)25L),Qtelewindows) ? T : Nil;
		    disable_resumability = temp_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			    9);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      8);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				7);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				  6);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
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
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    send_icp_telewindows_stop_mouse_tracking();
					    end_icp_message_group();
					}
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					}
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
	}
    }
    return flush_pending_mouse_motion_events(Current_workstation);
}

/* PUSH-BACK-MOUSE-MOTION-EVENT */
Object push_back_mouse_motion_event()
{
    Object x, y, modifier_bits, timestamp, pane_qm, image_plane_qm, temp;
    Object temp_1;
    Object result;

    x_note_fn_call(115,19);
    x = ISVREF(Current_workstation,(SI_Long)5L);
    y = ISVREF(Current_workstation,(SI_Long)6L);
    modifier_bits = current_modifier_bits_for_workstation(Current_workstation);
    timestamp = ISVREF(ISVREF(Current_workstation,(SI_Long)11L),(SI_Long)7L);
    result = decode_window_position(Current_workstation_window,x,y);
    MVS_2(result,pane_qm,image_plane_qm);
    temp = Current_workstation;
    temp_1 = mouse_motion_key_code(modifier_bits);
    return enqueue_workstation_event(8,temp,temp_1,x,y,timestamp,
	    Current_workstation_window,pane_qm,image_plane_qm);
}

/* ADVANCED-BUTTON-STATE */
Object advanced_button_state(key_code,before_mouse_button_state,key_bits)
    Object key_code, before_mouse_button_state, key_bits;
{
    Object after_mouse_button_state, unicode, key;

    x_note_fn_call(115,20);
    after_mouse_button_state = before_mouse_button_state;
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)776L) {
	after_mouse_button_state = FIX((SI_Long)1L | 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)776L));
    }
    else if (IFIX(key) == (SI_Long)774L) {
	after_mouse_button_state = FIX((SI_Long)2L | 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)774L));
    }
    else if (IFIX(key) == (SI_Long)772L) {
	after_mouse_button_state = FIX((SI_Long)4L | 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)772L));
    }
    else if (IFIX(key) == (SI_Long)770L) {
	after_mouse_button_state = FIX((SI_Long)4L | 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)770L));
    }
    else if (IFIX(key) == (SI_Long)777L) {
	after_mouse_button_state = FIX((SI_Long)6L & 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)769L));
    }
    else if (IFIX(key) == (SI_Long)775L) {
	after_mouse_button_state = FIX((SI_Long)5L & 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)769L));
    }
    else if (IFIX(key) == (SI_Long)773L) {
	after_mouse_button_state = FIX((SI_Long)3L & 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)769L));
    }
    else if (IFIX(key) == (SI_Long)769L) {
	after_mouse_button_state = FIX((SI_Long)3L & 
		IFIX(after_mouse_button_state));
	key_code = FIXNUM_LOGIOR(key_bits,FIX((SI_Long)769L));
    }
    return VALUES_2(key_code,after_mouse_button_state);
}

/* MOUSE-DOWN-P */
Object mouse_down_p()
{
    x_note_fn_call(115,21);
    return VALUES_1((SI_Long)0L != IFIX(ISVREF(Current_workstation,
	    (SI_Long)9L)) ? T : Nil);
}

/* MOUSE-STILL-DOWN-P */
Object mouse_still_down_p()
{
    Object lookahead_mouse_button_state, queue_sublist, workstation_event;
    Object raw_key_code, canonical_key_code, key_bits;
    Object advanced_mouse_button_state;
    Object result;

    x_note_fn_call(115,22);
    if (mouse_down_p()) {
	lookahead_mouse_button_state = ISVREF(Current_workstation,(SI_Long)9L);
	queue_sublist = ISVREF(ISVREF(Current_workstation,(SI_Long)2L),
		(SI_Long)1L);
	workstation_event = Nil;
	raw_key_code = Nil;
	canonical_key_code = Nil;
	key_bits = Nil;
      next_loop:
	if ( !TRUEP(queue_sublist))
	    goto end_loop;
	workstation_event = M_CAR(queue_sublist);
	queue_sublist = M_CDR(queue_sublist);
	raw_key_code = ISVREF(workstation_event,(SI_Long)1L);
	canonical_key_code = canonicalize_key_code(raw_key_code);
	key_bits = FIXNUM_LOGAND(Key_modifier_bits,canonical_key_code);
	if ((SI_Long)0L != IFIX(lookahead_mouse_button_state))
	    return VALUES_1(Nil);
	result = advanced_button_state(canonical_key_code,
		lookahead_mouse_button_state,key_bits);
	advanced_mouse_button_state = NTH_VALUE((SI_Long)1L, result);
	lookahead_mouse_button_state = advanced_mouse_button_state;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qunknown_is_selection_style;  /* unknown-is-selection-style */

static Object list_constant;       /* # */

/* SELECTION-STYLE-MOUSE-TRACKING-P */
Object selection_style_mouse_tracking_p(selection_style)
    Object selection_style;
{
    x_note_fn_call(115,23);
    if (show_selection_handles_p(0))
	return VALUES_1( !EQ(selection_style,Qunknown_is_selection_style) ?
		 T : Nil);
    else
	return memq_function(selection_style,list_constant);
}

static Object list_constant_1;     /* # */

/* SELECTION-STYLE-WITH-FOCUS-P */
Object selection_style_with_focus_p(selection_style)
    Object selection_style;
{
    x_note_fn_call(115,24);
    return memq_function(selection_style,list_constant_1);
}

/* REMEMBER-LAST-ACTIVE-MOUSE-BUTTON */
Object remember_last_active_mouse_button varargs_1(int, n)
{
    Object key_code, old_mouse_state;
    Object unicode, temp, svref_arg_1, svref_new_value;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,25);
    INIT_ARGS_nonrelocating();
    key_code = REQUIRED_ARG_nonrelocating();
    old_mouse_state = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (IFIX(old_mouse_state) == (SI_Long)0L) {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ?
		     unicode : Illegal_key_index;
	}
	else
	    temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	temp_1 = EQ(temp,FIX((SI_Long)770L));
	if (temp_1);
	else
	    temp_1 = EQ(temp,FIX((SI_Long)772L));
	if (temp_1);
	else
	    temp_1 = EQ(temp,FIX((SI_Long)774L));
	if (temp_1);
	else
	    temp_1 = EQ(temp,FIX((SI_Long)776L));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	svref_arg_1 = Current_workstation;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ?
		     unicode : Illegal_key_index;
	}
	else
	    temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	svref_new_value = mouse_key_code_button_name_symbol(temp);
	SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* SYNCHRONIZE-SELECTION-STYLE */
Object synchronize_selection_style(old_selection_style,new_selection_style)
    Object old_selection_style, new_selection_style;
{
    Object svref_arg_1, svref_new_value, old_mouse_tracking_p;
    Object new_mouse_tracking_p;

    x_note_fn_call(115,26);
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = Nil;
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = Nil;
    if (selection_style_with_focus_p(new_selection_style)) {
	svref_arg_1 = Current_workstation;
	svref_new_value = 
		ISVREF(Specific_structure_for_current_workstation_context,
		(SI_Long)4L);
	SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
	svref_arg_1 = Current_workstation;
	svref_new_value = 
		ISVREF(Specific_structure_for_current_workstation_context,
		(SI_Long)3L);
	SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    }
    if ( !TRUEP(dummy_workstation_p(Current_workstation))) {
	old_mouse_tracking_p = 
		selection_style_mouse_tracking_p(old_selection_style);
	new_mouse_tracking_p = 
		selection_style_mouse_tracking_p(new_selection_style);
	if (new_mouse_tracking_p && BOUNDP(Qcurrent_workstation_window))
	    push_back_mouse_motion_event();
	if (new_mouse_tracking_p)
	    start_tracking_mouse_in_current_workstation_context();
	else
	    stop_tracking_mouse_in_current_workstation_context();
    }
    return VALUES_1(Nil);
}

/* CANONICALIZE-KEY-CODE */
Object canonicalize_key_code(key_code)
    Object key_code;
{
    Object unicode, key;
    SI_Long arg, arg_1, arg_2, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(115,27);
    if (IFIX(key_code) == (SI_Long)16777248L)
	return VALUES_1(FIX((SI_Long)32L));
    else if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L)
	return VALUES_1(key_code);
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
	if (arg <= arg_1 && arg_1 <= arg_2)
	    key_code = FIXNUM_LOGAND(key_code,FIXNUM_LOGNOT(Control_bit));
	if (IFIX(FIXNUM_LOGAND(key_code,Meta_bit)) != (SI_Long)0L || 
		IFIX(FIXNUM_LOGAND(key_code,Alternate_bit)) != (SI_Long)0L)
	    key_code = FIXNUM_LOGIOR(Alternate_bit,
		    FIXNUM_LOGAND(FIXNUM_LOGAND(key_code,
		    FIXNUM_LOGNOT(Meta_bit)),FIXNUM_LOGNOT(Alternate_bit)));
	gensymed_symbol = IFIX(FIXNUM_LOGAND(Key_modifier_bits,key_code));
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		    unicode : Illegal_key_index;
	}
	else
	    key = FIXNUM_LOGAND(Key_index_bits,key_code);
	if (IFIX(key) == (SI_Long)453L)
	    gensymed_symbol_1 = (SI_Long)32L;
	else if (IFIX(key) == (SI_Long)454L)
	    gensymed_symbol_1 = (SI_Long)279L;
	else if (IFIX(key) == (SI_Long)455L)
	    gensymed_symbol_1 = (SI_Long)660L;
	else if (IFIX(key) == (SI_Long)460L)
	    gensymed_symbol_1 = (SI_Long)61L;
	else if (IFIX(key) == (SI_Long)461L)
	    gensymed_symbol_1 = (SI_Long)42L;
	else if (IFIX(key) == (SI_Long)462L)
	    gensymed_symbol_1 = (SI_Long)43L;
	else if (IFIX(key) == (SI_Long)464L)
	    gensymed_symbol_1 = (SI_Long)45L;
	else if (IFIX(key) == (SI_Long)465L)
	    gensymed_symbol_1 = (SI_Long)46L;
	else if (IFIX(key) == (SI_Long)466L)
	    gensymed_symbol_1 = (SI_Long)47L;
	else if (IFIX(key) == (SI_Long)463L)
	    gensymed_symbol_1 = (SI_Long)44L;
	else if (IFIX(key) == (SI_Long)470L)
	    gensymed_symbol_1 = (SI_Long)48L;
	else if (IFIX(key) == (SI_Long)471L)
	    gensymed_symbol_1 = (SI_Long)49L;
	else if (IFIX(key) == (SI_Long)472L)
	    gensymed_symbol_1 = (SI_Long)50L;
	else if (IFIX(key) == (SI_Long)473L)
	    gensymed_symbol_1 = (SI_Long)51L;
	else if (IFIX(key) == (SI_Long)474L)
	    gensymed_symbol_1 = (SI_Long)52L;
	else if (IFIX(key) == (SI_Long)475L)
	    gensymed_symbol_1 = (SI_Long)53L;
	else if (IFIX(key) == (SI_Long)476L)
	    gensymed_symbol_1 = (SI_Long)54L;
	else if (IFIX(key) == (SI_Long)477L)
	    gensymed_symbol_1 = (SI_Long)55L;
	else if (IFIX(key) == (SI_Long)478L)
	    gensymed_symbol_1 = (SI_Long)56L;
	else if (IFIX(key) == (SI_Long)479L)
	    gensymed_symbol_1 = (SI_Long)57L;
	else
	    gensymed_symbol_1 = IFIX(key_code);
	key_code = FIX(gensymed_symbol | gensymed_symbol_1);
	return VALUES_1(key_code);
    }
}

/* SHIFT-LEXICAL-ANALYSIS-OF-CURRENT-WORKSTATION? */
Object shift_lexical_analysis_of_current_workstation_qm()
{
    Object gensym_window, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, queue;
    Object workstation_event, following_event_qm, key_code, key_bits;
    Object before_mouse_button_state, after_mouse_button_state, unicode;
    Object key_code_1, gensymed_symbol, normalized_key_code;
    Object new_mouse_button_state, mouse_pointer, svref_arg_1, svref_new_value;
    SI_Long temp, arg, arg_1, arg_2;
    char temp_1;
    Declare_special(8);
    Object result;

    x_note_fn_call(115,28);
    gensym_window = ISVREF(Current_workstation,(SI_Long)1L);
    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    7);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      6);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		5);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  4);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    3);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      2);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  0);
		    queue = ISVREF(Current_workstation,(SI_Long)2L);
		    workstation_event = Nil;
		    following_event_qm = Nil;
		    key_code = Nil;
		    key_bits = Nil;
		    before_mouse_button_state = Nil;
		    after_mouse_button_state = Nil;
		  next_loop:
		    workstation_event = queue_pop(queue);
		    following_event_qm = queue_peek(queue);
		    key_code = ISVREF(workstation_event,(SI_Long)1L);
		    key_bits = FIXNUM_LOGAND(Key_modifier_bits,key_code);
		    before_mouse_button_state = ISVREF(Current_workstation,
			    (SI_Long)9L);
		    after_mouse_button_state = before_mouse_button_state;
		    key_code = canonicalize_key_code(key_code);
		    key_bits = FIXNUM_LOGAND(Key_modifier_bits,key_code);
		    SVREF(workstation_event,FIX((SI_Long)1L)) = key_code;
		    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != 
			    (SI_Long)0L) {
			unicode = FIXNUM_LOGAND(Unicode_character_bits,
				key_code);
			temp = num_len(3,FIX((SI_Long)0L),unicode,
				FIX((SI_Long)127L)) ? IFIX(unicode) : 
				IFIX(Illegal_key_index);
		    }
		    else
			temp = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
		    if (temp == (SI_Long)771L) {
			if (following_event_qm) {
			    key_code_1 = ISVREF(following_event_qm,
				    (SI_Long)1L);
			    if (IFIX(FIXNUM_LOGAND(key_code_1,
				    Unicode_bit)) != (SI_Long)0L) {
				unicode = 
					FIXNUM_LOGAND(Unicode_character_bits,
					key_code_1);
				temp = num_len(3,FIX((SI_Long)0L),unicode,
					FIX((SI_Long)127L)) ? 
					IFIX(unicode) : 
					IFIX(Illegal_key_index);
			    }
			    else
				temp = IFIX(FIXNUM_LOGAND(Key_index_bits,
					key_code_1));
			    temp_1 = temp == (SI_Long)771L;
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    goto end_try_again;
			else if ( !TRUEP(ISVREF(Current_workstation,
				(SI_Long)4L))) {
			    reclaim_workstation_event(workstation_event);
			    result = VALUES_1(Nil);
			    goto end_1;
			}
		    }
		    else {
			arg = (SI_Long)769L;
			if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != 
				(SI_Long)0L) {
			    unicode = FIXNUM_LOGAND(Unicode_character_bits,
				    key_code);
			    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
				    FIX((SI_Long)127L)) ? IFIX(unicode) : 
				    IFIX(Illegal_key_index);
			}
			else
			    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,
				    key_code));
			arg_2 = (SI_Long)779L;
			temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
			if (temp_1);
			else {
			    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) 
				    != (SI_Long)0L) {
				unicode = 
					FIXNUM_LOGAND(Unicode_character_bits,
					key_code);
				gensymed_symbol = num_len(3,
					FIX((SI_Long)0L),unicode,
					FIX((SI_Long)127L)) ? unicode : 
					Illegal_key_index;
			    }
			    else
				gensymed_symbol = 
					FIXNUM_LOGAND(Key_index_bits,key_code);
			    temp_1 = IFIX(gensymed_symbol) == (SI_Long)779L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)812L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)813L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)814L;
			}
			if (temp_1);
			else {
			    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) 
				    != (SI_Long)0L) {
				unicode = 
					FIXNUM_LOGAND(Unicode_character_bits,
					key_code);
				gensymed_symbol = num_len(3,
					FIX((SI_Long)0L),unicode,
					FIX((SI_Long)127L)) ? unicode : 
					Illegal_key_index;
			    }
			    else
				gensymed_symbol = 
					FIXNUM_LOGAND(Key_index_bits,key_code);
			    temp_1 = IFIX(gensymed_symbol) == (SI_Long)778L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)815L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)816L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)817L;
			}
			if (temp_1) {
			    result = advanced_button_state(key_code,
				    before_mouse_button_state,key_bits);
			    MVS_2(result,normalized_key_code,
				    new_mouse_button_state);
			    remember_last_active_mouse_button(3,key_code,
				    before_mouse_button_state,
				    new_mouse_button_state);
			    key_code = normalized_key_code;
			    after_mouse_button_state = new_mouse_button_state;
			    SVREF(workstation_event,FIX((SI_Long)1L)) = 
				    key_code;
			}
		    }
		    mouse_pointer = 
			    make_next_event_mouse_pointer(Current_workstation,
			    key_code,ISVREF(workstation_event,(SI_Long)2L),
			    ISVREF(workstation_event,(SI_Long)3L),
			    ISVREF(workstation_event,(SI_Long)4L));
		    initialize_mouse_pointer_tracking_for_window(Current_workstation,
			    mouse_pointer,ISVREF(workstation_event,
			    (SI_Long)6L),ISVREF(workstation_event,
			    (SI_Long)7L));
		    if (interesting_input_event_p(key_code)) {
			release_mouse_pointer_if_any(ISVREF(Current_workstation,
				(SI_Long)54L));
			svref_arg_1 = Current_workstation;
			svref_new_value = 
				reference_mouse_pointer(mouse_pointer);
			SVREF(svref_arg_1,FIX((SI_Long)54L)) = svref_new_value;
		    }
		    if ( !(FIXNUM_EQ(before_mouse_button_state,
			    after_mouse_button_state) || 
			    ISVREF(workstation_event,(SI_Long)9L))) {
			svref_arg_1 = Current_workstation;
			SVREF(svref_arg_1,FIX((SI_Long)9L)) = 
				after_mouse_button_state;
			if ((SI_Long)0L == IFIX(before_mouse_button_state)) {
			    release_mouse_pointer_if_any(ISVREF(Current_workstation,
				    (SI_Long)13L));
			    svref_arg_1 = Current_workstation;
			    svref_new_value = 
				    reference_mouse_pointer(mouse_pointer);
			    SVREF(svref_arg_1,FIX((SI_Long)13L)) = 
				    svref_new_value;
			}
			else if ((SI_Long)0L == 
				    IFIX(after_mouse_button_state));
			else if (ISVREF(Current_workstation,(SI_Long)4L)) {
			    key_code = FIXNUM_LOGIOR(key_bits,
				    FIX((SI_Long)771L));
			    SVREF(workstation_event,FIX((SI_Long)1L)) = 
				    key_code;
			    SVREF(mouse_pointer,FIX((SI_Long)8L)) = key_code;
			}
			else if (following_event_qm)
			    goto end_try_again;
			else {
			    reclaim_workstation_event(workstation_event);
			    result = VALUES_1(Nil);
			    goto end_1;
			}
		    }
		    temp_1 = TRUEP(ISVREF(Current_workstation,(SI_Long)4L));
		    if (temp_1);
		    else {
			arg = (SI_Long)769L;
			if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != 
				(SI_Long)0L) {
			    unicode = FIXNUM_LOGAND(Unicode_character_bits,
				    key_code);
			    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,
				    FIX((SI_Long)127L)) ? IFIX(unicode) : 
				    IFIX(Illegal_key_index);
			}
			else
			    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,
				    key_code));
			arg_2 = (SI_Long)779L;
			temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
			if (temp_1);
			else {
			    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) 
				    != (SI_Long)0L) {
				unicode = 
					FIXNUM_LOGAND(Unicode_character_bits,
					key_code);
				gensymed_symbol = num_len(3,
					FIX((SI_Long)0L),unicode,
					FIX((SI_Long)127L)) ? unicode : 
					Illegal_key_index;
			    }
			    else
				gensymed_symbol = 
					FIXNUM_LOGAND(Key_index_bits,key_code);
			    temp_1 = IFIX(gensymed_symbol) == (SI_Long)779L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)812L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)813L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)814L;
			}
			if (temp_1);
			else {
			    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) 
				    != (SI_Long)0L) {
				unicode = 
					FIXNUM_LOGAND(Unicode_character_bits,
					key_code);
				gensymed_symbol = num_len(3,
					FIX((SI_Long)0L),unicode,
					FIX((SI_Long)127L)) ? unicode : 
					Illegal_key_index;
			    }
			    else
				gensymed_symbol = 
					FIXNUM_LOGAND(Key_index_bits,key_code);
			    temp_1 = IFIX(gensymed_symbol) == (SI_Long)778L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)815L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)816L;
			    if (temp_1);
			    else
				temp_1 = IFIX(gensymed_symbol) == 
					(SI_Long)817L;
			}
		    }
		    if (temp_1);
		    else
			temp_1 =  !FIXNUM_EQ(Illegal_key_code,key_code);
		    if (temp_1)
			track_mouse_pointer_till_done(mouse_pointer);
		    result = VALUES_1(workstation_event);
		    goto end_1;
		  end_try_again:
		    reclaim_workstation_event(workstation_event);
		    goto next_loop;
		  end_loop:
		    result = VALUES_1(Qnil);
		  end_1:;
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

/* INTERESTING-INPUT-EVENT-P */
Object interesting_input_event_p(key_code)
    Object key_code;
{
    Object unicode, key;

    x_note_fn_call(115,29);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)782L || IFIX(key) == (SI_Long)771L)
	return VALUES_1(Nil);
    else if (IFIX(key) == (SI_Long)787L)
	return VALUES_1(Nil);
    else
	return VALUES_1(T);
}

/* MAKE-NEXT-EVENT-MOUSE-POINTER */
Object make_next_event_mouse_pointer(workstation,key_code,fixnum_time,
	    mouse_x,mouse_y)
    Object workstation, key_code, fixnum_time, mouse_x, mouse_y;
{
    Object latest_event_mouse_pointer, focus_image_plane;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, temp, svref_new_value;
    Object gensym_push_modify_macro_arg, car_1, cdr_1;
    SI_Long temp_1;
    Declare_special(5);

    x_note_fn_call(115,30);
    latest_event_mouse_pointer = make_mouse_pointer_1(workstation,key_code,
	    fixnum_time,mouse_x,mouse_y);
    focus_image_plane = Nil;
    focus_image_plane = ISVREF(Current_workstation,(SI_Long)7L);
    if (focus_image_plane) {
	current_frame_transform_qm = Nil;
	current_image_x_scale = ISVREF(focus_image_plane,(SI_Long)11L);
	current_image_y_scale = ISVREF(focus_image_plane,(SI_Long)12L);
	current_x_origin_of_drawing = ISVREF(focus_image_plane,(SI_Long)13L);
	current_y_origin_of_drawing = ISVREF(focus_image_plane,(SI_Long)14L);
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
		  value = FIXNUM_MINUS(mouse_x,Current_x_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      temp = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      temp = inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L)
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		  }
		  SVREF(latest_event_mouse_pointer,FIX((SI_Long)9L)) = temp;
		  scale = Current_image_y_scale;
		  value = FIXNUM_MINUS(mouse_y,Current_y_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      temp = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      temp = inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L)
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		  }
		  SVREF(latest_event_mouse_pointer,FIX((SI_Long)10L)) = temp;
		  svref_new_value = ISVREF(Current_workstation,(SI_Long)8L);
		  SVREF(latest_event_mouse_pointer,FIX((SI_Long)11L)) = 
			  svref_new_value;
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensym_push_modify_macro_arg = latest_event_mouse_pointer;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(workstation,(SI_Long)14L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
    release_mouse_pointer_if_any(ISVREF(workstation,(SI_Long)12L));
    svref_new_value = ISVREF(workstation,(SI_Long)11L);
    SVREF(workstation,FIX((SI_Long)12L)) = svref_new_value;
    SVREF(workstation,FIX((SI_Long)11L)) = latest_event_mouse_pointer;
    push_more_detailed_spot(latest_event_mouse_pointer,
	    make_entire_g2_window_spot_1(),ISVREF(workstation,(SI_Long)25L));
    maybe_reclaim_some_mouse_pointers(workstation);
    return VALUES_1(latest_event_mouse_pointer);
}

/* MAYBE-RECLAIM-SOME-MOUSE-POINTERS */
Object maybe_reclaim_some_mouse_pointers(workstation)
    Object workstation;
{
    Object svref_new_value, mouse_pointers_to_consider_reclaiming;
    Object mouse_pointer, ab_loop_list_, gensym_push_modify_macro_arg, car_1;
    Object cdr_1;

    x_note_fn_call(115,31);
    svref_new_value = FIXNUM_SUB1(ISVREF(workstation,(SI_Long)16L));
    if (IFIX(SVREF(workstation,FIX((SI_Long)16L)) = svref_new_value) < 
	    (SI_Long)0L) {
	ISVREF(workstation,(SI_Long)16L) = FIX((SI_Long)2L);
	mouse_pointers_to_consider_reclaiming = ISVREF(workstation,
		(SI_Long)15L);
	svref_new_value = ISVREF(workstation,(SI_Long)14L);
	SVREF(workstation,FIX((SI_Long)15L)) = svref_new_value;
	SVREF(workstation,FIX((SI_Long)14L)) = Nil;
	mouse_pointer = Nil;
	ab_loop_list_ = mouse_pointers_to_consider_reclaiming;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	mouse_pointer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (IFIX(ISVREF(mouse_pointer,(SI_Long)4L)) <= (SI_Long)0L)
	    reclaim_mouse_pointer_1(mouse_pointer);
	else {
	    gensym_push_modify_macro_arg = mouse_pointer;
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = ISVREF(workstation,(SI_Long)14L);
	    svref_new_value = gensym_cons_1(car_1,cdr_1);
	    SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
	}
	goto next_loop;
      end_loop:;
	return reclaim_gensym_list_1(mouse_pointers_to_consider_reclaiming);
    }
    else
	return VALUES_1(Nil);
}

/* X-IN-WORKSPACE-COORDINATES */
Object x_in_workspace_coordinates(x_in_window,image_plane)
    Object x_in_window, image_plane;
{
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, temp_1;
    SI_Long temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(115,32);
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
		  result = VALUES_1(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  result = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  
			  -  - (SI_Long)1L)) / IFIX(scale);
		  result = VALUES_1(FIX(temp));
	      }
	      else {
		  temp = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = FIXNUM_NEGATE(FIX(temp));
		  result = VALUES_1(temp_1);
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* Y-IN-WORKSPACE-COORDINATES */
Object y_in_workspace_coordinates(y_in_window,image_plane)
    Object y_in_window, image_plane;
{
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, temp_1;
    SI_Long temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(115,33);
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
	      scale = Current_image_y_scale;
	      value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  result = VALUES_1(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  result = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  
			  -  - (SI_Long)1L)) / IFIX(scale);
		  result = VALUES_1(FIX(temp));
	      }
	      else {
		  temp = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = FIXNUM_NEGATE(FIX(temp));
		  result = VALUES_1(temp_1);
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* IMAGE-PLANE-OF-WORKSPACE-ON-WORKSTATION */
Object image_plane_of_workspace_on_workstation(workstation,workspace)
    Object workstation, workspace;
{
    Object image_plane, ab_loop_list_, window;

    x_note_fn_call(115,34);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
    window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    if ( !TRUEP(printing_window_p(window)) && EQ(workstation,ISVREF(window,
	    (SI_Long)2L)))
	return VALUES_1(image_plane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* IMAGE-PLANE-OF-WORKSPACE */
Object image_plane_of_workspace(workspace)
    Object workspace;
{
    x_note_fn_call(115,35);
    return image_plane_of_workspace_on_workstation(Current_workstation,
	    workspace);
}

/* IMAGE-PLANE-OF-WORKSPACE-ON-WINDOW */
Object image_plane_of_workspace_on_window(gensym_window,workspace)
    Object gensym_window, workspace;
{
    Object pane, ab_loop_list_, ab_loop_it_, image_plane, ab_loop_list__1;

    x_note_fn_call(115,36);
    pane = Nil;
    ab_loop_list_ = ISVREF(gensym_window,(SI_Long)3L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(ISVREF(image_plane,(SI_Long)5L),workspace)) {
	ab_loop_it_ = image_plane;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CURRENT-MODIFIER-BITS-FOR-WORKSTATION */
Object current_modifier_bits_for_workstation(workstation)
    Object workstation;
{
    Object mouse_pointer;

    x_note_fn_call(115,37);
    mouse_pointer = ISVREF(workstation,(SI_Long)11L);
    return VALUES_1(FIXNUM_LOGAND(Key_modifier_bits,ISVREF(mouse_pointer,
	    (SI_Long)8L)));
}

/* GET-IMAGE-PLANE-BY-FRAME */
Object get_image_plane_by_frame(workstation,frame)
    Object workstation, frame;
{
    Object wc, ab_loop_list_, edit_state_qm, frame_qm, edit_workspace;
    Object image_plane;

    x_note_fn_call(115,38);
    wc = Nil;
    ab_loop_list_ = ISVREF(workstation,(SI_Long)17L);
    edit_state_qm = Nil;
    frame_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    wc = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    edit_state_qm = ISVREF(wc,(SI_Long)2L);
    frame_qm = ISVREF(edit_state_qm,(SI_Long)3L);
    if (EQ(frame_qm,frame)) {
	edit_workspace = ISVREF(edit_state_qm,(SI_Long)12L);
	image_plane = image_plane_of_workspace(edit_workspace);
	return VALUES_1(image_plane);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qinternal;           /* internal */

/* MAKE-EVENT-INTERPRETATION */
Object make_event_interpretation(namespace,name,arguments)
    Object namespace, name, arguments;
{
    x_note_fn_call(115,39);
    if (arguments || namespace &&  !EQ(namespace,Qinternal))
	return slot_value_list_3(namespace,name,
		copy_tree_using_slot_value_conses_1(arguments));
    else
	return VALUES_1(name);
}

/* RECLAIM-EVENT-INTERPRETATION */
Object reclaim_event_interpretation(event_interpretation)
    Object event_interpretation;
{
    x_note_fn_call(115,40);
    if (CONSP(event_interpretation))
	return reclaim_slot_value_tree_1(event_interpretation);
    else
	return VALUES_1(Nil);
}

/* VALID-WORKSTATION-CONTEXT-P-FUNCTION */
Object valid_workstation_context_p_function(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(115,41);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)4L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-WORKSTATION-CONTEXT-FRAME */
Object valid_workstation_context_p_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    Object mouse_pointer, ab_loop_list_;

    x_note_fn_call(115,42);
    mouse_pointer = Nil;
    ab_loop_list_ = ISVREF(workstation_context_frame,(SI_Long)1L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mouse_pointer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(mouse_pointer,(SI_Long)6L))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS */
Object valid_workstation_context_p_for_workstation_context_with_selection_focus(workstation_context_with_selection_focus)
    Object workstation_context_with_selection_focus;
{
    Object gensymed_symbol, gensymed_symbol_1, image_plane;
    Object reference_serial_number, temp_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(115,43);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_workstation_context_with_selection_focus,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = workstation_context_with_selection_focus;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	image_plane = ISVREF(workstation_context_with_selection_focus,
		(SI_Long)4L);
	reference_serial_number = 
		ISVREF(workstation_context_with_selection_focus,(SI_Long)5L);
	temp = FIXNUM_EQ(ISVREF(image_plane,(SI_Long)1L),
		reference_serial_number);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 =  !TRUEP(ISVREF(workstation_context_with_selection_focus,
		(SI_Long)3L)) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    gensymed_symbol = 
		    ISVREF(ISVREF(workstation_context_with_selection_focus,
		    (SI_Long)3L),(SI_Long)3L);
	    x = ISVREF(workstation_context_with_selection_focus,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(workstation_context_with_selection_focus,
			(SI_Long)2L);
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
	    return VALUES_1( !temp ? T : Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qtop_level;          /* top-level */

/* INTERPRET-WORKSTATION-EVENT */
Object interpret_workstation_event(workstation_event,workstation)
    Object workstation_event, workstation;
{
    Object event_interpretation_qm, context_name_qm, temp;
    Object result;

    x_note_fn_call(115,44);
    result = find_event_interpretation(workstation_event,workstation);
    MVS_2(result,event_interpretation_qm,context_name_qm);
    temp =  !EQ(context_name_qm,Qtop_level) ? T : Nil;
    return VALUES_2(event_interpretation_qm,temp);
}

/* REMOVE-IMAGE-PLANE-POINTERS-IN-WORKSTATION-EVENT-QUEUE */
Object remove_image_plane_pointers_in_workstation_event_queue(workstation,
	    image_plane)
    Object workstation, image_plane;
{
    Object queue_sublist, workstation_event, image_plane_qm, x_in_window;
    Object y_in_window, image_plane_1, ab_loop_list_;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;

    x_note_fn_call(115,45);
    queue_sublist = ISVREF(ISVREF(workstation,(SI_Long)2L),(SI_Long)1L);
    workstation_event = Nil;
    image_plane_qm = Nil;
  next_loop:
    if ( !TRUEP(queue_sublist))
	goto end_loop;
    workstation_event = M_CAR(queue_sublist);
    queue_sublist = M_CDR(queue_sublist);
    image_plane_qm = ISVREF(workstation_event,(SI_Long)7L);
    if (EQ(image_plane_qm,image_plane)) {
	SVREF(workstation_event,FIX((SI_Long)7L)) = Nil;
	x_in_window = ISVREF(workstation_event,(SI_Long)3L);
	y_in_window = ISVREF(workstation_event,(SI_Long)4L);
	image_plane_1 = Nil;
	ab_loop_list_ = ISVREF(ISVREF(image_plane_qm,(SI_Long)2L),(SI_Long)5L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	image_plane_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(image_plane_1,image_plane_qm) && ISVREF(image_plane_1,
		(SI_Long)5L) && FIXNUM_GE(x_in_window,ISVREF(image_plane_1,
		(SI_Long)15L)) && FIXNUM_GE(y_in_window,
		ISVREF(image_plane_1,(SI_Long)16L)) && 
		FIXNUM_LT(x_in_window,ISVREF(image_plane_1,(SI_Long)17L)) 
		&& FIXNUM_LT(y_in_window,ISVREF(image_plane_1,(SI_Long)18L))) {
	    SVREF(workstation_event,FIX((SI_Long)7L)) = image_plane_1;
	    frame_serial_number_setf_arg = ISVREF(ISVREF(image_plane_1,
		    (SI_Long)5L),(SI_Long)3L);
	    old = ISVREF(workstation_event,(SI_Long)8L);
	    new_1 = frame_serial_number_setf_arg;
	    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(workstation_event,FIX((SI_Long)8L)) = svref_new_value;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-NON-KB-WORKSPACES-FOR-THIS-WORKSTATION-ONLY */
Object reclaim_non_kb_workspaces_for_this_workstation_only(list_of_non_kb_workspaces)
    Object list_of_non_kb_workspaces;
{
    Object svref_arg_1, non_kb_workspace, ab_loop_list_;

    x_note_fn_call(115,46);
    svref_arg_1 = Structure_being_reclaimed;
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = Nil;
    non_kb_workspace = Nil;
    ab_loop_list_ = list_of_non_kb_workspaces;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    non_kb_workspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_frame(non_kb_workspace);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(list_of_non_kb_workspaces);
}

/* CLOSE-TELEWINDOWS-CALLBACK */
Object close_telewindows_callback(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object workstation_qm, gensym_window_qm;

    x_note_fn_call(115,47);
    workstation_qm = ISVREF(icp_socket,(SI_Long)23L);
    if (workstation_qm) {
	maybe_schedule_service_workstation(workstation_qm,Nil);
	gensym_window_qm = ISVREF(workstation_qm,(SI_Long)1L);
	if (gensym_window_qm) {
	    reclaim_dynamic_dialogs_call_dismissed(gensym_window_qm);
	    SVREF(gensym_window_qm,FIX((SI_Long)12L)) = Nil;
	}
	return VALUES_1(SVREF(icp_socket,FIX((SI_Long)23L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Drawing_parameters, Qdrawing_parameters);

static Object Qimage_palette;      /* image-palette */

/* CLEANUP-FOR-DRAWING-PARAMETERS */
Object cleanup_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,48);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      frame = Drawing_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)1L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qdrawing_parameters)) {
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
      result = change_slot_value(3,Drawing_parameters,Qimage_palette,Nil);
    POP_SPECIAL();
    return result;
}

/* PUT-DRAWING-PRIORITY-WHERE-SLOT-IS-ABSENT */
Object put_drawing_priority_where_slot_is_absent(drawing_parameters,value)
    Object drawing_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,49);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-FOR-DRAWING-PARAMETERS */
Object initialize_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,50);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      frame = Drawing_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qdrawing_parameters)) {
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
      result = reset_paint_mode_if_needed(Drawing_parameters);
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-AFTER-READING-FOR-DRAWING-PARAMETERS */
Object initialize_after_reading_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,51);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      frame = Drawing_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)4L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qdrawing_parameters)) {
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
      result = reset_paint_mode_if_needed(Drawing_parameters);
    POP_SPECIAL();
    return result;
}

static Object Qdrawing_in_paint_mode_p;  /* drawing-in-paint-mode-p */

static Object Qallow_scheduled_drawing_qm;  /* allow-scheduled-drawing? */

/* RESET-PAINT-MODE-IF-NEEDED */
Object reset_paint_mode_if_needed(drawing_parameters)
    Object drawing_parameters;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,52);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Reading_kb_p && loading_version_3_or_earlier_kb_p()) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Drawing_parameters,
		      Qdrawing_in_paint_mode_p);
	  svref_arg_1 = Drawing_parameters;
	  SVREF(svref_arg_1,FIX((SI_Long)23L)) = Nil;
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Drawing_parameters,
		      Qallow_scheduled_drawing_qm);
	  svref_arg_1 = Drawing_parameters;
	  result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)22L)) = Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* PUT-ALLOW-SCHEDULED-DRAWING? */
Object put_allow_scheduled_drawing_qm(drawing_parameters,value,initializing_qm)
    Object drawing_parameters, value, initializing_qm;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,53);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,
		  Qallow_scheduled_drawing_qm);
      svref_arg_1 = Drawing_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)22L)) = value;
      if (value &&  !TRUEP(ISVREF(Drawing_parameters,(SI_Long)23L)))
	  change_slot_value(3,Drawing_parameters,Qdrawing_in_paint_mode_p,T);
      if ( !TRUEP(initializing_qm) && 
	      system_table_installed_p(Drawing_parameters))
	  propagate_allow_scheduled_drawing(value);
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

/* PUT-DRAWING-IN-PAINT-MODE-P */
Object put_drawing_in_paint_mode_p(drawing_parameters,painting,initializing_qm)
    Object drawing_parameters, painting, initializing_qm;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,54);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,Qdrawing_in_paint_mode_p);
      svref_arg_1 = Drawing_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)23L)) = painting;
      if ( !TRUEP(painting) && ISVREF(Drawing_parameters,(SI_Long)22L))
	  change_slot_value(3,Drawing_parameters,
		  Qallow_scheduled_drawing_qm,Nil);
      if ( !TRUEP(initializing_qm) && 
	      system_table_installed_p(Drawing_parameters))
	  propagate_drawing_transfer_mode_to_all_gensym_windows(painting);
      result = VALUES_1(painting);
    POP_SPECIAL();
    return result;
}

/* G2-GLOBAL-PAINT-MODE-P */
Object g2_global_paint_mode_p()
{
    x_note_fn_call(115,55);
    if (BOUNDP(Qdrawing_parameters) && Drawing_parameters)
	return VALUES_1(ISVREF(Drawing_parameters,(SI_Long)23L));
    else
	return VALUES_1(T);
}

static Object list_constant_2;     /* # */

/* PUT-DRAWING-TRANSFER-MODE-WHERE-SLOT-IS-ABSENT */
Object put_drawing_transfer_mode_where_slot_is_absent(drawing_parameters,value)
    Object drawing_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,56);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      change_slot_value(3,Drawing_parameters,Qdrawing_in_paint_mode_p,
	      memq_function(value,list_constant_2) ? T : Nil);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qshow_selection_handles;  /* show-selection-handles */

/* INSTALL-SYSTEM-TABLE-FOR-DRAWING-PARAMETERS */
Object install_system_table_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,57);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      propagate_allow_scheduled_drawing(ISVREF(Drawing_parameters,
	      (SI_Long)22L));
      propagate_drawing_transfer_mode_to_all_gensym_windows(ISVREF(Drawing_parameters,
	      (SI_Long)23L));
      propagate_image_palette_to_all_gensym_windows(ISVREF(Drawing_parameters,
	      (SI_Long)24L));
      result = propagate_show_selection_handles_to_all_gensym_windows(1,
	      get_lookup_slot_value_given_default(Drawing_parameters,
	      Qshow_selection_handles,T));
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-DRAWING-PARAMETERS */
Object deinstall_system_table_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,58);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qpropagate_allow_scheduled_drawing_1;  /* propagate-allow-scheduled-drawing-1 */

/* PROPAGATE-ALLOW-SCHEDULED-DRAWING */
Object propagate_allow_scheduled_drawing(scheduled_qm)
    Object scheduled_qm;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(1);

    x_note_fn_call(115,59);
    if (Nil) {
	if (EQ(Nil,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(Nil,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(Nil);
	inline_note_reclaim_cons(Nil,Nil);
	structure_being_reclaimed = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
	  SVREF(Nil,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(Nil,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = Nil;
    }
    def_structure_schedule_task_variable = 
	    ISVREF(Chain_of_available_schedule_tasks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_schedule_task_variable) {
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_schedule_task_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_schedule_task_g2_struct;
    }
    else
	def_structure_schedule_task_variable = 
		make_permanent_schedule_task_structure_internal();
    inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
    new_task = def_structure_schedule_task_variable;
    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
    SVREF(new_task,FIX((SI_Long)10L)) = Nil;
    SVREF(new_task,FIX((SI_Long)7L)) = Qpropagate_allow_scheduled_drawing_1;
    temp = SYMBOL_FUNCTION(Qpropagate_allow_scheduled_drawing_1);
    SVREF(new_task,FIX((SI_Long)8L)) = temp;
    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(new_task,FIX((SI_Long)13L)) = scheduled_qm;
    temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
    SVREF(new_task,FIX((SI_Long)11L)) = temp;
    temp = constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
	    (SI_Long)0L),new_task);
    SVREF(new_task,FIX((SI_Long)6L)) = temp;
    return VALUES_1(new_task);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* PROPAGATE-ALLOW-SCHEDULED-DRAWING-1 */
Object propagate_allow_scheduled_drawing_1(scheduled_qm)
    Object scheduled_qm;
{
    x_note_fn_call(115,60);
    if (scheduled_qm) {
	Current_drawing_priority = Kdraw_as_late_as_possible;
	return VALUES_1(Current_drawing_priority);
    }
    else {
	Current_drawing_priority = Kdraw_as_soon_as_possible;
	return VALUES_1(Current_drawing_priority);
    }
}

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

static Object Kxor;                /* :xor */

static Object Qrefresh_window;     /* refresh-window */

/* PROPAGATE-DRAWING-TRANSFER-MODE-TO-ALL-GENSYM-WINDOWS */
Object propagate_drawing_transfer_mode_to_all_gensym_windows(painting_p)
    Object painting_p;
{
    Object new_mode_name, workstation, ab_loop_list_, gensym_window;
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(1);

    x_note_fn_call(115,61);
    new_mode_name = painting_p ? Kpaint_infered_from_xor : Kxor;
    if (BOUNDP(Qcurrent_drawing_transfer_mode))
	Current_drawing_transfer_mode = new_mode_name;
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if ( !EQ(ISVREF(gensym_window,(SI_Long)30L),new_mode_name)) {
	SVREF(gensym_window,FIX((SI_Long)30L)) = new_mode_name;
	if (Nil) {
	    if (EQ(Nil,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(Nil,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(Nil);
	    inline_note_reclaim_cons(Nil,Nil);
	    structure_being_reclaimed = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
	      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(Nil,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	new_task = def_structure_schedule_task_variable;
	SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	SVREF(new_task,FIX((SI_Long)7L)) = Qrefresh_window;
	temp = SYMBOL_FUNCTION(Qrefresh_window);
	SVREF(new_task,FIX((SI_Long)8L)) = temp;
	ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(new_task,FIX((SI_Long)13L)) = gensym_window;
	temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	SVREF(new_task,FIX((SI_Long)11L)) = temp;
	temp = 
		constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		(SI_Long)0L),new_task);
	SVREF(new_task,FIX((SI_Long)6L)) = temp;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qdefault_primary_selection_color;  /* default-primary-selection-color */

static Object Qcolor;              /* color */

/* PUT-DEFAULT-PRIMARY-SELECTION-COLOR */
Object put_default_primary_selection_color(drawing_parameters,value,
	    initializing_qm)
    Object drawing_parameters, value, initializing_qm;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,62);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,
		  Qdefault_primary_selection_color);
      svref_arg_1 = Drawing_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)25L)) = value;
      if ( !TRUEP(initializing_qm)) {
	  if (system_table_installed_p(Drawing_parameters))
	      update_all_selection_highlights(Qcolor);
      }
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

static Object Qdefault_secondary_selection_color;  /* default-secondary-selection-color */

/* PUT-DEFAULT-SECONDARY-SELECTION-COLOR */
Object put_default_secondary_selection_color(drawing_parameters,value,
	    initializing_qm)
    Object drawing_parameters, value, initializing_qm;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,63);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,
		  Qdefault_secondary_selection_color);
      svref_arg_1 = Drawing_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)26L)) = value;
      if ( !TRUEP(initializing_qm)) {
	  if (system_table_installed_p(Drawing_parameters))
	      update_all_selection_highlights(Qcolor);
      }
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

/* PUT-SHOW-SELECTION-HANDLES */
Object put_show_selection_handles(drawing_parameters,value,initializing_qm)
    Object drawing_parameters, value, initializing_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,64);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,Qshow_selection_handles);
      set_lookup_slot_value_1(Drawing_parameters,Qshow_selection_handles,
	      value);
      if (system_table_installed_p(Drawing_parameters))
	  propagate_show_selection_handles_to_all_gensym_windows(2,value,
		  initializing_qm);
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

/* SHOW-SELECTION-HANDLES-P */
Object show_selection_handles_p varargs_1(int, n)
{
    Object gensym_window_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,65);
    INIT_ARGS_nonrelocating();
    gensym_window_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Drawing_parameters ? 
	    TRUEP(get_lookup_slot_value_given_default(Drawing_parameters,
	    Qshow_selection_handles,T)) : TRUEP(Nil)) {
	if (gensym_window_qm)
	    return selection_ui_p(gensym_window_qm);
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmode;               /* mode */

/* PROPAGATE-SHOW-SELECTION-HANDLES-TO-ALL-GENSYM-WINDOWS */
Object propagate_show_selection_handles_to_all_gensym_windows varargs_1(int, n)
{
    Object on_p;
    Object initializing_qm, workstation, ab_loop_list_, gensym_window;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(115,66);
    INIT_ARGS_nonrelocating();
    on_p = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    initializing_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
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
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				if ( !EQ(on_p,ISVREF(gensym_window,
					(SI_Long)68L))) {
				    SVREF(gensym_window,FIX((SI_Long)68L)) 
					    = on_p;
				    if ( !TRUEP(initializing_qm))
					update_selection_highlights_on_workstation(workstation,
						Qmode);
				    if (on_p) {
					push_back_mouse_motion_event();
					start_tracking_mouse_in_current_workstation_context();
				    }
				    else if ( 
					    !TRUEP(Specific_structure_for_current_workstation_context));
				    else if ( 
					    !TRUEP(selection_style_mouse_tracking_p(selection_style_of_workstation_context(Specific_structure_for_current_workstation_context))))
					stop_tracking_mouse_in_current_workstation_context();
				}
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
    goto next_loop;
  end_loop:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

Object Alignment_grid_default_spacing = UNBOUND;

Object Alignment_grid_default_line_color = UNBOUND;

Object Alignment_grid_default_line_pattern = UNBOUND;

Object Stock_line_pattern_type = UNBOUND;

/* TRANSFORM-ALIST-INTO-PLIST */
Object transform_alist_into_plist(alist)
    Object alist;
{
    Object elem, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(115,67);
    elem = Nil;
    ab_loop_list_ = alist;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elem = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(elem)) {
	ab_loopvar__2 = phrase_cons(CAR(elem),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = phrase_cons(CDR(elem),Nil);
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

static Object Qspacing;            /* spacing */

static Object Qline_color;         /* line-color */

static Object Qline_pattern;       /* line-pattern */

static Object Qsnap_to;            /* snap-to */

static Object string_constant;     /* ", line color: ~(~a~)" */

static Object string_constant_1;   /* ", line pattern: " */

static Object string_constant_2;   /* ", snap to " */

/* WRITE-ALIGNMENT-GRID-FROM-SLOT */
Object write_alignment_grid_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object spacing, line_color_qm, line_pattern_qm, snap_to_qm;

    x_note_fn_call(115,68);
    spacing = getf(value,Qspacing,Alignment_grid_default_spacing);
    line_color_qm = getf(value,Qline_color,_);
    line_pattern_qm = getf(value,Qline_pattern,_);
    snap_to_qm = getf(value,Qsnap_to,_);
    twrite_alignment_grid_spacing(spacing);
    if (line_color_qm)
	tformat(2,string_constant,line_color_qm);
    if (line_pattern_qm) {
	tformat(2,string_constant_1,line_pattern_qm);
	twrite_line_pattern_element(line_pattern_qm);
    }
    if (snap_to_qm) {
	tformat(1,string_constant_2);
	return twrite_alignment_grid_spacing(snap_to_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qalignment_grid;     /* alignment-grid */

/* PUT-ALIGNMENT-GRID */
Object put_alignment_grid(drawing_parameters,value,initializing_qm)
    Object drawing_parameters, value, initializing_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(115,69);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Drawing_parameters,Qalignment_grid);
      set_lookup_slot_value_1(Drawing_parameters,Qalignment_grid,value);
      if ( !TRUEP(initializing_qm)) {
	  if (system_table_installed_p(Drawing_parameters))
	      refresh_alignment_grid_on_all_windows();
      }
      result = VALUES_1(value);
    POP_SPECIAL();
    return result;
}

static Object string_constant_3;   /* "~d" */

static Object string_constant_4;   /* "(~d,~d)" */

/* TWRITE-ALIGNMENT-GRID-SPACING */
Object twrite_alignment_grid_spacing(spacing)
    Object spacing;
{
    Object dx, dy;

    x_note_fn_call(115,70);
    dx = CAR(spacing);
    dy = CDR(spacing);
    if (EQL(dx,dy))
	return tformat(2,string_constant_3,dx);
    else
	return tformat(3,string_constant_4,dx,dy);
}

/* ALIGNMENT-GRID-SPACING-PHRASE */
Object alignment_grid_spacing_phrase(spacing_ev)
    Object spacing_ev;
{
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1;

    x_note_fn_call(115,71);
    if (FIXNUMP(spacing_ev))
	return phrase_cons(spacing_ev,spacing_ev);
    else {
	gensymed_symbol = M_CAR(spacing_ev);
	gensymed_symbol_1 = (SI_Long)0L + (SI_Long)1L;
	temp = FIXNUM_LE(ISVREF(M_CAR(spacing_ev),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(M_CAR(spacing_ev),
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	gensymed_symbol = M_CAR(spacing_ev);
	gensymed_symbol_1 = (SI_Long)1L + (SI_Long)1L;
	return phrase_cons(temp,FIXNUM_LE(ISVREF(M_CAR(spacing_ev),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(M_CAR(spacing_ev),gensymed_symbol_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L));
    }
}

/* UNPACK-ALIGNMENT-GRID-VALUE */
Object unpack_alignment_grid_value(value)
    Object value;
{
    Object spacing, dx, dy, color, pattern, snap_to_qm, snap_dx_qm, snap_dy_qm;

    x_note_fn_call(115,72);
    spacing = getf(value,Qspacing,Alignment_grid_default_spacing);
    dx = CAR(spacing);
    dy = CDR(spacing);
    color = getf(value,Qline_color,Alignment_grid_default_line_color);
    pattern = getf(value,Qline_pattern,Alignment_grid_default_line_pattern);
    snap_to_qm = getf(value,Qsnap_to,_);
    snap_dx_qm = CAR(snap_to_qm);
    snap_dy_qm = CDR(snap_to_qm);
    return VALUES_6(dx,dy,color,pattern,snap_dx_qm,snap_dy_qm);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

/* ALIGNMENT-GRID-EVALUATION-SETTER */
Object alignment_grid_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(115,73);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_alignment_grid_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_2 = estructure_slot(gensymed_symbol,Qspacing,Nil) ? 
	    phrase_list_2(Qspacing,
	    alignment_grid_spacing_phrase(estructure_slot(gensymed_symbol,
	    Qspacing,Nil))) : Nil;
    temp = estructure_slot(gensymed_symbol,Qline_color,Nil) ? 
	    phrase_list_2(Qline_color,estructure_slot(gensymed_symbol,
	    Qline_color,Nil)) : Nil;
    temp_1 = estructure_slot(gensymed_symbol,Qline_pattern,Nil) ? 
	    phrase_list_2(Qline_pattern,estructure_slot(gensymed_symbol,
	    Qline_pattern,Nil)) : Nil;
    result = VALUES_1(nconc2(temp_2,nconc2(temp,nconc2(temp_1,
	    estructure_slot(gensymed_symbol,Qsnap_to,Nil) ? 
	    phrase_list_2(Qsnap_to,
	    alignment_grid_spacing_phrase(estructure_slot(gensymed_symbol,
	    Qsnap_to,Nil))) : Nil))));
  end_alignment_grid_evaluation_setter:
    return result;
}

/* ALIGNMENT-GRID-EVALUATION-GETTER */
Object alignment_grid_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object dx, dy, line_color, line_pattern, snap_dx_qm, snap_dy_qm;
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object result;

    x_note_fn_call(115,74);
    result = unpack_alignment_grid_value(slot_value);
    MVS_6(result,dx,dy,line_color,line_pattern,snap_dx_qm,snap_dy_qm);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qspacing;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = allocate_evaluation_sequence(eval_list_2(dx,dy));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qline_color;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = line_color;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qline_pattern;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = line_pattern;
    GENSYM_RETURN_ONE(allocate_evaluation_structure(nconc2(gensymed_symbol,
	    snap_dx_qm ? eval_list_2(Qsnap_to,
	    allocate_evaluation_sequence(eval_list_2(snap_dx_qm,
	    snap_dy_qm))) : Nil)));
    return VALUES_1(Nil);
}

/* GET-GLOBAL-SNAP-GRID */
Object get_global_snap_grid()
{
    Object temp, snap_dx_qm, snap_dy_qm;
    Object result;

    x_note_fn_call(115,75);
    result = unpack_alignment_grid_value(get_lookup_slot_value_given_default(Drawing_parameters,
	    Qalignment_grid,Nil));
    MVS_6(result,temp,temp,temp,temp,snap_dx_qm,snap_dy_qm);
    return VALUES_2(snap_dx_qm,snap_dy_qm);
}

static Object Qkb_workspace;       /* kb-workspace */

/* VISIBLE-GRID-PERMITTED-P */
Object visible_grid_permitted_p(image_plane)
    Object image_plane;
{
    Object frame, symbol, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(115,76);
    if (ISVREF(image_plane,(SI_Long)5L)) {
	frame = ISVREF(image_plane,(SI_Long)5L);
	symbol = Qkb_workspace;
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
		return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
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

static Object Qvisible_grid;       /* visible-grid */

/* VISIBLE-GRID-P */
Object visible_grid_p(image_plane)
    Object image_plane;
{
    x_note_fn_call(115,77);
    if (visible_grid_permitted_p(image_plane))
	return get_view_preference(ISVREF(image_plane,(SI_Long)41L),
		Qvisible_grid);
    else
	return VALUES_1(Nil);
}

/* SET-VISIBLE-GRID-P */
Object set_visible_grid_p(image_plane,value)
    Object image_plane, value;
{
    Object svref_new_value;

    x_note_fn_call(115,78);
    if (visible_grid_permitted_p(image_plane)) {
	svref_new_value = set_view_preference_1(ISVREF(image_plane,
		(SI_Long)41L),Qvisible_grid,value ? T : Nil);
	SVREF(image_plane,FIX((SI_Long)41L)) = svref_new_value;
	return VALUES_1(value);
    }
    else
	return VALUES_1(Nil);
}

/* REFRESH-ALIGNMENT-GRID */
Object refresh_alignment_grid(image_plane)
    Object image_plane;
{
    Object current_draw_paper_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,79);
    current_draw_paper_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
	    0);
      result = invalidate_image_plane(image_plane);
    POP_SPECIAL();
    return result;
}

/* REFRESH-ALIGNMENT-GRID-ON-ALL-WINDOWS */
Object refresh_alignment_grid_on_all_windows()
{
    Object workstation, ab_loop_list_, image_plane, ab_loop_list__1;

    x_note_fn_call(115,80);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(detail_pane_for_workstation(workstation),
	    (SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (visible_grid_p(image_plane))
	refresh_alignment_grid(image_plane);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TOGGLE-VISIBLE-GRID */
Object toggle_visible_grid(image_plane)
    Object image_plane;
{
    x_note_fn_call(115,81);
    if (visible_grid_permitted_p(image_plane)) {
	set_visible_grid_p(image_plane, 
		!TRUEP(visible_grid_p(image_plane)) ? T : Nil);
	return refresh_alignment_grid(image_plane);
    }
    else
	return VALUES_1(Nil);
}

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

/* DRAW-ALIGNMENT-GRID */
Object draw_alignment_grid(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object dx, dy, line_color, line_pattern, color_value, pattern_value, lcm_1;
    Object y1_1, scale, value, temp, x, x1, y;
    SI_Long line_width, gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long y_origin, y0_1, temp_1, k, ab_loop_bind_, value_1, x_origin, x0;
    Object result;

    x_note_fn_call(115,82);
    result = unpack_alignment_grid_value(get_lookup_slot_value_given_default(Drawing_parameters,
	    Qalignment_grid,Nil));
    MVS_4(result,dx,dy,line_color,line_pattern);
    if (EQ(line_color,Qbackground))
	color_value = Current_background_color_value;
    else if (EQ(line_color,Qforeground) || EQ(line_color,
	    Qworkspace_foreground))
	color_value = Current_foreground_color_value;
    else if (EQ(line_color,Qtransparent))
	color_value = Current_background_color_value;
    else
	color_value = map_to_color_value(line_color);
    pattern_value = lookup_stock_line_pattern_element(line_pattern);
    lcm_1 = Least_common_multiple_of_stock_line_pattern_lengths;
    line_width = (SI_Long)1L;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = (SI_Long)0L;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < (SI_Long)0L && 
	    (SI_Long)0L < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(Current_image_y_scale) * (SI_Long)0L + 
		(SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		FIX((SI_Long)0L)));
    y_origin = gensymed_symbol + gensymed_symbol_1;
    y0_1 = y_origin + IFIX(FIXNUM_TIMES(lcm_1,
	    chestnut_floorf_function(FIX(IFIX(top) - y_origin),lcm_1)));
    y1_1 = bottom;
    scale = Current_image_x_scale;
    value = FIXNUM_MINUS(left,Current_x_origin_of_drawing);
    if (IFIX(scale) == (SI_Long)4096L)
	temp = value;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	temp = inverse_scalef_function(scale,value);
    else if (IFIX(value) >= (SI_Long)0L)
	temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
    }
    k = IFIX(chestnut_floorf_function(temp,dx));
    scale = Current_image_x_scale;
    value = FIXNUM_MINUS(right,Current_x_origin_of_drawing);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	gensymed_symbol = IFIX(inverse_scalef_function(scale,value));
    else if (IFIX(value) >= (SI_Long)0L) {
	temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	gensymed_symbol = temp_1;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
	gensymed_symbol = temp_1;
    }
    gensymed_symbol_1 = IFIX(dx);
    ab_loop_bind_ = IFIX(ceiling(FIX(gensymed_symbol),FIX(gensymed_symbol_1)));
    x = Nil;
  next_loop:
    if (k > ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    scale = Current_image_x_scale;
    value_1 = k * IFIX(dx);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = value_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
	    value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value_1)));
    x = FIX(gensymed_symbol + gensymed_symbol_1);
    draw_patterned_line(x,FIX(y0_1),x,y1_1,color_value,FIX(line_width),
	    pattern_value);
    k = k + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = (SI_Long)0L;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < (SI_Long)0L && 
	    (SI_Long)0L < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(Current_image_x_scale) * (SI_Long)0L + 
		(SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		FIX((SI_Long)0L)));
    x_origin = gensymed_symbol + gensymed_symbol_1;
    x0 = x_origin + IFIX(FIXNUM_TIMES(lcm_1,
	    chestnut_floorf_function(FIX(IFIX(left) - x_origin),lcm_1)));
    x1 = right;
    scale = Current_image_y_scale;
    value = FIXNUM_MINUS(top,Current_y_origin_of_drawing);
    if (IFIX(scale) == (SI_Long)4096L)
	temp = value;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	temp = inverse_scalef_function(scale,value);
    else if (IFIX(value) >= (SI_Long)0L)
	temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
    }
    k = IFIX(chestnut_floorf_function(temp,dy));
    scale = Current_image_y_scale;
    value = FIXNUM_MINUS(bottom,Current_y_origin_of_drawing);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(value);
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	gensymed_symbol = IFIX(inverse_scalef_function(scale,value));
    else if (IFIX(value) >= (SI_Long)0L) {
	temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	gensymed_symbol = temp_1;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
	gensymed_symbol = temp_1;
    }
    gensymed_symbol_1 = IFIX(dy);
    ab_loop_bind_ = IFIX(ceiling(FIX(gensymed_symbol),FIX(gensymed_symbol_1)));
    y = Nil;
  next_loop_1:
    if (k > ab_loop_bind_)
	goto end_loop_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    scale = Current_image_y_scale;
    value_1 = k * IFIX(dy);
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_1 = value_1;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
	    value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value_1)));
    y = FIX(gensymed_symbol + gensymed_symbol_1);
    draw_patterned_line(FIX(x0),y,x1,y,color_value,FIX(line_width),
	    pattern_value);
    k = k + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

/* PUT-IMAGE-PALETTE */
Object put_image_palette(drawing_parameters,new_value,gensymed_symbol)
    Object drawing_parameters, new_value, gensymed_symbol;
{
    Object old_value, temp, result_1, current_flag_state_qm, slot_description;
    Object new_cons, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(115,83);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    1);
      old_value = ISVREF(Drawing_parameters,(SI_Long)24L);
      if (EQUAL(new_value,old_value)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Drawing_parameters,Qimage_palette);
	  temp = Drawing_parameters;
	  SVREF(temp,FIX((SI_Long)24L)) = new_value;
      }
      else {
	  result_1 = Nil;
	  current_flag_state_qm = Nil;
	  slot_description = 
		  get_slot_description_of_class_description_function(Qframe_status_and_notes,
		  ISVREF(Drawing_parameters,(SI_Long)1L),Nil);
	  new_cons = ISVREF(Available_stack_change_conses_vector,
		  IFIX(Current_thread_index));
	  if (new_cons) {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = Nil;
	      }
	      gensymed_symbol = new_cons;
	  }
	  else
	      gensymed_symbol = Nil;
	  if ( !TRUEP(gensymed_symbol))
	      gensymed_symbol = replenish_stack_change_cons_pool();
	  if (Nil)
	      gensymed_symbol_1 = 
		      nconc2(stack_change_list_2(Drawing_parameters,
		      slot_description),stack_change_cons_1(Nil,Nil));
	  else {
	      new_cons = ISVREF(Available_stack_change_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol_1 = new_cons;
	      }
	      else
		  gensymed_symbol_1 = Nil;
	      if ( !TRUEP(gensymed_symbol_1))
		  gensymed_symbol_1 = replenish_stack_change_cons_pool();
	      temp = Drawing_parameters;
	      M_CAR(gensymed_symbol_1) = temp;
	      M_CDR(gensymed_symbol_1) = slot_description;
	      inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	  }
	  M_CAR(gensymed_symbol) = gensymed_symbol_1;
	  temp = Stack_of_slot_value_changes;
	  M_CDR(gensymed_symbol) = temp;
	  inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	  stack_of_slot_value_changes = gensymed_symbol;
	  PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		  0);
	    current_flag_state_qm = (SI_Long)0L != 
		    (IFIX(ISVREF(Drawing_parameters,(SI_Long)5L)) & 
		    (SI_Long)16777216L) ? T : Nil;
	    if ( !TRUEP(current_flag_state_qm)) {
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(Drawing_parameters,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = Drawing_parameters;
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = T;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		temp = Drawing_parameters;
		svref_new_value_1 = IFIX(ISVREF(Drawing_parameters,
			(SI_Long)5L)) | (SI_Long)16777216L;
		ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Drawing_parameters,Qimage_palette);
	    temp = Drawing_parameters;
	    result_1 = SVREF(temp,FIX((SI_Long)24L)) = new_value;
	    if ( !TRUEP(current_flag_state_qm)) {
		temp = Drawing_parameters;
		svref_new_value_1 = IFIX(ISVREF(Drawing_parameters,
			(SI_Long)5L)) &  ~(SI_Long)16777216L;
		ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(Drawing_parameters,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = Drawing_parameters;
		gensymed_symbol_2 = T;
		gensymed_symbol_3 = Nil;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
	    }
	    temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	    if (temp_1);
	    else if (M_CDR(Stack_of_slot_value_changes)) {
		frame_and_slot_or_atom = Nil;
		ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ATOM(frame_and_slot_or_atom))
		    goto end_loop;
		temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		if (temp_1);
		else {
		    temp_2 = M_CDR(frame_and_slot_or_atom);
		    temp_1 = CONSP(temp_2) ? EQ(slot_description,
			    SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			    THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			    CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		}
		ab_loop_it_ = temp_1 ? (EQ(Drawing_parameters,
			M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		if (ab_loop_it_) {
		    temp_1 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		update_all_representations_of_slot(Drawing_parameters,
			slot_description,Nil,Nil);
	    if (ISVREF(slot_description,(SI_Long)14L))
		update_frame_name_references(Drawing_parameters);
	    stack_change_pop_store = Nil;
	    cons_1 = Stack_of_slot_value_changes;
	    if (cons_1) {
		stack_change_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qstack_change);
		if (ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = 
			    ISVREF(Available_stack_change_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    Stack_of_slot_value_changes = next_cons;
	    reclaim_stack_change_tree_1(stack_change_pop_store);
	    if (Stack_of_slot_value_changes) {
		temp_2 = M_CAR(Stack_of_slot_value_changes);
		temp_1 = ATOM(temp_2);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ?  
		    !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
		     TRUEP(Nil))
		do_deferred_updates_to_representations_in_tables();
	  POP_SPECIAL();
      }
      result = VALUES_1(new_value);
    POP_SPECIAL();
    return result;
}

static Object Qblack_and_white;    /* black-and-white */

static Object array_constant;      /* # */

static Object Qstandard_grays;     /* standard-grays */

static Object array_constant_1;    /* # */

static Object Qstandard_colors;    /* standard-colors */

static Object array_constant_2;    /* # */

static Object Qextended_grays;     /* extended-grays */

static Object array_constant_3;    /* # */

static Object Qextended_colors;    /* extended-colors */

static Object array_constant_4;    /* # */

static Object Qcustom_grays;       /* custom-grays */

static Object string_constant_5;   /* "custom grays from ~(~a~)" */

static Object Qcustom_colors;      /* custom-colors */

static Object string_constant_6;   /* "custom colors from ~(~a~)" */

/* WRITE-IMAGE-PALETTE-FROM-SLOT */
Object write_image_palette_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object palette_name, image_name_qm;

    x_note_fn_call(115,84);
    palette_name = car_or_atom(value);
    image_name_qm = CONSP(value) ? SECOND(value) : Qnil;
    if (EQ(palette_name,Qblack_and_white))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)15L));
    else if (EQ(palette_name,Qstandard_grays))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)14L));
    else if (EQ(palette_name,Qstandard_colors))
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)15L));
    else if (EQ(palette_name,Qextended_grays))
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)14L));
    else if (EQ(palette_name,Qextended_colors))
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)15L));
    else if (EQ(palette_name,Qcustom_grays))
	return tformat(2,string_constant_5,image_name_qm);
    else if (EQ(palette_name,Qcustom_colors))
	return tformat(2,string_constant_6,image_name_qm);
    else
	return VALUES_1(Nil);
}

/* IMAGE-PALETTE-COLOR-MAP? */
Object image_palette_color_map_qm(image_palette)
    Object image_palette;
{
    Object image_name_qm, image_definition_qm, image_data_qm, color_map_qm;

    x_note_fn_call(115,85);
    image_name_qm = CONSP(image_palette) ? SECOND(image_palette) : Qnil;
    image_definition_qm = image_name_qm ? find_image_named(image_name_qm) :
	     Qnil;
    image_data_qm = image_definition_qm ? 
	    image_definition_data_qm(image_definition_qm) : Qnil;
    color_map_qm = image_data_qm ? ISVREF(image_data_qm,(SI_Long)9L) : Qnil;
    return VALUES_1(color_map_qm);
}

static Object Qstandard_gray;      /* standard-gray */

static Object Qstandard_color;     /* standard-color */

static Object Qextended_gray;      /* extended-gray */

static Object Qextended_color;     /* extended-color */

static Object Qcustom_color;       /* custom-color */

static Object Qsome_image_name;    /* some-image-name */

static Object Qcustom_gray;        /* custom-gray */

/* PUT-IMAGE-RENDERING-QUALITY-WHERE-SLOT-IS-ABSENT */
Object put_image_rendering_quality_where_slot_is_absent(drawing_params,value)
    Object drawing_params, value;
{
    Object new_value;

    x_note_fn_call(115,86);
    if (EQ(value,Qstandard_gray))
	new_value = Qstandard_grays;
    else if (EQ(value,Qstandard_color))
	new_value = Qstandard_colors;
    else if (EQ(value,Qextended_gray))
	new_value = Qextended_grays;
    else if (EQ(value,Qextended_color))
	new_value = Qextended_colors;
    else if (EQ(value,Qcustom_color))
	new_value = slot_value_list_2(Qcustom_colors,Qsome_image_name);
    else if (EQ(value,Qcustom_gray))
	new_value = slot_value_list_2(Qcustom_grays,Qsome_image_name);
    else
	new_value = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(drawing_params,Qimage_palette);
    SVREF(drawing_params,FIX((SI_Long)24L)) = new_value;
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* "the image ~(~a~) is incomplete" */

/* WRITE-DRAWING-PARAMETERS-IMAGE-INCOMPLETE-NOTE */
Object write_drawing_parameters_image_incomplete_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object image_name;

    x_note_fn_call(115,87);
    gensymed_symbol = particulars;
    image_name = CAR(gensymed_symbol);
    GENSYM_RETURN_ONE(tformat(2,string_constant_7,image_name));
    return VALUES_1(Nil);
}

static Object Qdrawing_parameters_image_incomplete;  /* drawing-parameters-image-incomplete */

/* UPDATE-FRAME-STATUS-AND-NOTES-FOR-DRAWING-PARAMETERS */
Object update_frame_status_and_notes_for_drawing_parameters(drawing_parameters)
    Object drawing_parameters;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object frame, sub_vector_qm, method_function_qm, frame_status_qm;
    Object image_palette, image_name_qm, color_map_qm, temp_1;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long index_1, ab_loop_bind_;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(115,88);
    PUSH_SPECIAL_WITH_SYMBOL(Drawing_parameters,Qdrawing_parameters,drawing_parameters,
	    1);
      slot_description = 
	      get_slot_description_of_class_description_function(Qframe_status_and_notes,
	      ISVREF(Drawing_parameters,(SI_Long)1L),Nil);
      new_cons = ISVREF(Available_stack_change_conses_vector,
	      IFIX(Current_thread_index));
      if (new_cons) {
	  temp = Available_stack_change_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  svref_new_value = M_CDR(new_cons);
	  SVREF(temp,svref_arg_2) = svref_new_value;
	  if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		  IFIX(Current_thread_index)))) {
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = Nil;
	  }
	  gensymed_symbol = new_cons;
      }
      else
	  gensymed_symbol = Nil;
      if ( !TRUEP(gensymed_symbol))
	  gensymed_symbol = replenish_stack_change_cons_pool();
      if (Nil)
	  gensymed_symbol_1 = 
		  nconc2(stack_change_list_2(Drawing_parameters,
		  slot_description),stack_change_cons_1(Nil,Nil));
      else {
	  new_cons = ISVREF(Available_stack_change_conses_vector,
		  IFIX(Current_thread_index));
	  if (new_cons) {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = Nil;
	      }
	      gensymed_symbol_1 = new_cons;
	  }
	  else
	      gensymed_symbol_1 = Nil;
	  if ( !TRUEP(gensymed_symbol_1))
	      gensymed_symbol_1 = replenish_stack_change_cons_pool();
	  temp = Drawing_parameters;
	  M_CAR(gensymed_symbol_1) = temp;
	  M_CDR(gensymed_symbol_1) = slot_description;
	  inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
      }
      M_CAR(gensymed_symbol) = gensymed_symbol_1;
      temp = Stack_of_slot_value_changes;
      M_CDR(gensymed_symbol) = temp;
      inline_note_allocate_cons(gensymed_symbol,Qstack_change);
      stack_of_slot_value_changes = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	      0);
	frame = Drawing_parameters;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)19L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qdrawing_parameters)) {
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
	frame_status_qm = Nil;
	image_palette = ISVREF(Drawing_parameters,(SI_Long)24L);
	image_name_qm = CONSP(image_palette) ? SECOND(image_palette) : Qnil;
	color_map_qm = image_palette_color_map_qm(image_palette);
	delete_frame_note_if_any(Qdrawing_parameters_image_incomplete,
		Drawing_parameters);
	if (system_table_installed_p(Drawing_parameters)) {
	    if (image_name_qm && find_image_named(image_name_qm) &&  
		    !TRUEP(color_map_qm))
		add_frame_note(4,Qdrawing_parameters_image_incomplete,
			Drawing_parameters,slot_value_cons_1(image_name_qm,
			Nil),T);
	}
	temp_1 = update_frame_status(Drawing_parameters,frame_status_qm,Nil);
	temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	if (temp_2);
	else if (M_CDR(Stack_of_slot_value_changes)) {
	    frame_and_slot_or_atom = Nil;
	    ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ATOM(frame_and_slot_or_atom))
		goto end_loop_1;
	    temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	    if (temp_2);
	    else {
		temp_3 = M_CDR(frame_and_slot_or_atom);
		temp_2 = CONSP(temp_3) ? EQ(slot_description,
			SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	    }
	    ab_loop_it_ = temp_2 ? (EQ(Drawing_parameters,
		    M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_2:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    update_all_representations_of_slot(Drawing_parameters,
		    slot_description,Nil,Nil);
	if (ISVREF(slot_description,(SI_Long)14L))
	    update_frame_name_references(Drawing_parameters);
	stack_change_pop_store = Nil;
	cons_1 = Stack_of_slot_value_changes;
	if (cons_1) {
	    stack_change_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qstack_change);
	    if (ISVREF(Available_stack_change_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Stack_of_slot_value_changes = next_cons;
	reclaim_stack_change_tree_1(stack_change_pop_store);
	if (Stack_of_slot_value_changes) {
	    temp_3 = M_CAR(Stack_of_slot_value_changes);
	    temp_2 = ATOM(temp_3);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ?  
		!TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		TRUEP(Nil))
	    do_deferred_updates_to_representations_in_tables();
	result = VALUES_1(temp_1);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* PROPAGATE-IMAGE-PALETTE-TO-ALL-GENSYM-WINDOWS */
Object propagate_image_palette_to_all_gensym_windows(image_palette)
    Object image_palette;
{
    Object palette_name, color_map_qm, workstation, ab_loop_list_;
    Object gensym_window;

    x_note_fn_call(115,89);
    palette_name = car_or_atom(image_palette);
    color_map_qm = image_palette_color_map_qm(image_palette);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    set_image_palette_of_gensym_window(gensym_window,palette_name,
	    color_map_qm);
    goto next_loop;
  end_loop:;
    return invalidate_all_image_renderings();
}

static Object Qchange_image_palette_of_window;  /* change-image-palette-of-window */

/* SET-IMAGE-PALETTE-OF-GENSYM-WINDOW */
Object set_image_palette_of_gensym_window(gensym_window,palette_name,
	    color_map_qm)
    Object gensym_window, palette_name, color_map_qm;
{
    x_note_fn_call(115,90);
    SVREF(gensym_window,FIX((SI_Long)31L)) = palette_name;
    if ( !EQ(ISVREF(gensym_window,(SI_Long)1L),Qicp) || 
	    printing_window_p(gensym_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_scrolling,
	    ISVREF(gensym_window,(SI_Long)11L)))
	return update_window(9,gensym_window,ISVREF(gensym_window,
		(SI_Long)7L),ISVREF(gensym_window,(SI_Long)8L),
		ISVREF(gensym_window,(SI_Long)9L),ISVREF(gensym_window,
		(SI_Long)10L),Qchange_image_palette_of_window,
		gensym_window,palette_name,color_map_qm);
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-IMAGE-PALETTE-OF-NEW-GENSYM-WINDOW */
Object initialize_image_palette_of_new_gensym_window(gensym_window)
    Object gensym_window;
{
    Object image_palette, palette_name, color_map_qm;

    x_note_fn_call(115,91);
    image_palette = ISVREF(Drawing_parameters,(SI_Long)24L);
    palette_name = car_or_atom(image_palette);
    color_map_qm = image_palette_color_map_qm(image_palette);
    return set_image_palette_of_gensym_window(gensym_window,palette_name,
	    color_map_qm);
}

/* SET-UP-WORKSTATION */
Object set_up_workstation(gensym_window)
    Object gensym_window;
{
    Object workstation;

    x_note_fn_call(115,92);
    workstation = make_workstation_1(gensym_window);
    return set_up_workstation_on_ab_side(workstation,gensym_window,Nil);
}

static Object Qflush_workstation;  /* flush-workstation */

/* FLUSH-WORKSTATION */
Object flush_workstation(workstation)
    Object workstation;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Object delete_corresponding_object_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(115,93);
    SAVE_STACK();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    13);
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
	  SVREF(temp,svref_arg_2) = Qflush_workstation;
      }
      LOCK(For_workstation);
      if (PUSH_UNWIND_PROTECT(0)) {
	  current_workstation_1 = workstation;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		  12);
	    current_workstation_window = ISVREF(Current_workstation,
		    (SI_Long)1L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		    11);
	      current_g2_window_for_this_workstation_qm = 
		      ISVREF(Current_workstation,(SI_Long)25L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		      10);
		type_of_current_workstation_window = 
			ISVREF(Current_workstation_window,(SI_Long)1L);
		PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			9);
		  current_workstation_native_window_qm = 
			  ISVREF(Current_workstation_window,(SI_Long)17L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			  8);
		    temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
		    current_workstation_context = CAR(temp_1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			    7);
		      type_of_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			      6);
			specific_structure_for_current_workstation_context 
				= ISVREF(Current_workstation_context,
				(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				5);
			  current_workstation_detail_pane = 
				  detail_pane(Current_workstation_window);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				  4);
			    current_g2_user_mode_qm = 
				    ISVREF(Current_workstation,(SI_Long)19L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				    3);
			      new_g2_classic_ui_p = 
				      get_value_for_current_workstation_new_g2_classic_ui_p();
			      PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				      2);
				servicing_workstation_qm = T;
				PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					1);
				  if (System_is_running && 
					  twng_window_p(ISVREF(workstation,
					  (SI_Long)1L)))
				      call_twng_disconnect_callbacks(ISVREF(workstation,
					      (SI_Long)1L));
				  if ( !TRUEP(ISVREF(workstation,
					  (SI_Long)55L))) {
				      SVREF(workstation,FIX((SI_Long)55L)) = T;
				      log_out_workstation(workstation);
				      unwind_all_workstation_contexts(workstation);
				      delete_corresponding_object_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Delete_corresponding_object_qm,Qdelete_corresponding_object_qm,delete_corresponding_object_qm,
					      0);
					reclaim_icp_object_map_for_workstation(workstation);
				      POP_SPECIAL();
				      SAVE_VALUES(reclaim_workstation(workstation));
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
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(For_workstation);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qforce_process_drawing;  /* force-process-drawing */

/* FORCE-PROCESS-DRAWING */
Object force_process_drawing()
{
    Object workstation, ab_loop_list_;

    x_note_fn_call(115,94);
    if (Drawing_is_locked_qm) {
	Drawing_is_locked_qm = Qforce_process_drawing;
	return VALUES_1(Drawing_is_locked_qm);
    }
    else {
	do_some_icp_processing();
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(EQ(workstation,ISVREF(System_window,(SI_Long)2L)) && 
		no_local_window_p())) {
	    if (IFIX(Current_thread_index) == (SI_Long)0L)
		force_workstation_drawing(workstation);
	    else
		maybe_schedule_service_workstation(workstation,T);
	}
	goto next_loop;
      end_loop:;
	return flush_icp_output_ports();
    }
}

/* DO-SOME-ICP-PROCESSING */
Object do_some_icp_processing()
{
    Object scheduler_enabled_qm;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(115,95);
    SAVE_STACK();
    display_events_were_enabled = (SI_Long)0L != ne_display_events_enabled();
    ne_disable_display_events();
    if (PUSH_UNWIND_PROTECT(0)) {
	scheduler_enabled_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
		0);
	  SAVE_VALUES(get_pending_network_events());
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    if (display_events_were_enabled)
	ne_enable_display_events();
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FORCE-PROCESS-DRAWING-IF-APPROPRIATE */
Object force_process_drawing_if_appropriate()
{
    Object workstation, ab_loop_list_, current_workstation_1;
    Object current_workstation_window, current_workstation_native_window_qm;
    Object type_of_current_workstation_window;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(115,96);
    SAVE_STACK();
    if ( !(IFIX(Current_thread_index) == (SI_Long)0L)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    if ( !EQ(Current_drawing_priority,Kdraw_as_late_as_possible)) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(EQ(workstation,ISVREF(System_window,(SI_Long)2L)) && 
		no_local_window_p())) {
	    LOCK(For_workstation_polling);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = workstation;
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			3);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  2);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    1);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      0);
			drain_current_workstation_drawing_queue();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation_polling);
	    CONTINUE_UNWINDING(0);
	}
	goto next_loop;
      end_loop:;
	result = flush_icp_output_ports();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qsync_graphics_on_current_window;  /* sync-graphics-on-current-window */

/* FORCE-WORKSTATION-DRAWING */
Object force_workstation_drawing(workstation)
    Object workstation;
{
    Object current_workstation_1, current_workstation_window;
    Object current_workstation_native_window_qm;
    Object type_of_current_workstation_window;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(115,97);
    SAVE_STACK();
    LOCK(For_workstation_polling);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		3);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  2);
	    current_workstation_native_window_qm = 
		    ISVREF(Current_workstation_window,(SI_Long)17L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
		    1);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      0);
		poll_workstation();
		drain_current_workstation_drawing_queue();
		SAVE_VALUES(update_window(6,Current_workstation_window,
			ISVREF(Current_workstation_window,(SI_Long)7L),
			ISVREF(Current_workstation_window,(SI_Long)8L),
			ISVREF(Current_workstation_window,(SI_Long)9L),
			ISVREF(Current_workstation_window,(SI_Long)10L),
			Qsync_graphics_on_current_window));
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation_polling);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FORCE-SOME-PROCESS-DRAWING */
Object force_some_process_drawing()
{
    Object workstation, ab_loop_list_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(115,98);
    SAVE_STACK();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (time_slice_expired_p())
	goto end_loop;
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
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
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				work_on_drawing_window(ISVREF(Current_workstation,
					(SI_Long)1L),Nil);
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
    goto next_loop;
  end_loop:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trace_workstation_events, Qtrace_workstation_events);

/* TRACE-EVENTS */
Object trace_events()
{
    x_note_fn_call(115,99);
    Trace_workstation_events = T;
    Trace_reshape_events = T;
    return VALUES_1(Trace_reshape_events);
}

/* UNTRACE-EVENTS */
Object untrace_events()
{
    x_note_fn_call(115,100);
    Trace_workstation_events = Nil;
    Trace_reshape_events = Nil;
    return VALUES_1(Trace_reshape_events);
}

/* TRACE-WORKSTATION-EVENT */
Object trace_workstation_event(mouse_pointer,handler,context_of_handler)
    Object mouse_pointer, handler, context_of_handler;
{
    x_note_fn_call(115,101);
    return simple_trace_workstation_event(mouse_pointer,handler,
	    context_of_handler);
}

static Object Qg2;                 /* g2 */

static Object Qtw;                 /* tw */

static Object string_constant_8;   /* "" */

/* SIMPLE-TRACE-WORKSTATION-EVENT */
Object simple_trace_workstation_event(mouse_pointer,handler,context_of_handler)
    Object mouse_pointer, handler, context_of_handler;
{
    Object stack, top_of_stack, spot_qm, window_type, print_case, temp, temp_1;
    Object temp_2, temp_3, temp_4;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,102);
    stack = ISVREF(Current_workstation,(SI_Long)17L);
    top_of_stack = ISVREF(FIRST(stack),(SI_Long)1L);
    spot_qm = ISVREF(mouse_pointer,(SI_Long)5L);
    window_type = ISVREF(ISVREF(Current_workstation,(SI_Long)1L),(SI_Long)1L);
    print_case = Kdowncase;
    PUSH_SPECIAL_WITH_SYMBOL(Print_case,Qprint_case,print_case,0);
      if (EQ(window_type,Qx11_window))
	  temp = Qg2;
      else if (EQ(window_type,Qicp))
	  temp = Qtw;
      else
	  temp = window_type;
      temp_1 = ISVREF(mouse_pointer,(SI_Long)7L);
      temp_2 = ISVREF(mouse_pointer,(SI_Long)2L);
      temp_3 = ISVREF(mouse_pointer,(SI_Long)3L);
      temp_4 = symbol_from_key_code(ISVREF(mouse_pointer,(SI_Long)8L));
      result = format((SI_Long)10L,T,"~2a ~9d ~4d ~4d ~12a ~a ~a -> ~a~%",
	      temp,temp_1,temp_2,temp_3,temp_4,spot_qm ? 
	      ISVREF(type_description_of(spot_qm),(SI_Long)1L) : 
	      string_constant_8,top_of_stack,handler);
    POP_SPECIAL();
    return result;
}

/* CURRENT-WORKSTATION-HAS-PENDING-EVENTS-P */
Object current_workstation_has_pending_events_p()
{
    Object temp;

    x_note_fn_call(115,103);
    temp =  !TRUEP(queue_empty_p(ISVREF(Current_workstation,(SI_Long)2L))) 
	    ? T : Nil;
    if (temp);
    else
	temp = poll_workstation();
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Task_to_run_service_workstations_final, Qtask_to_run_service_workstations_final);

DEFINE_VARIABLE_WITH_SYMBOL(Future_task_to_run_propagate_all_workspace_changes_to_image_planes, Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes);

DEFINE_VARIABLE_WITH_SYMBOL(Current_task_to_run_propagate_all_workspace_changes_to_image_planes, Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes);

Object Service_workstations_final_interval = UNBOUND;

Object Service_workstation_interval = UNBOUND;

/* MAYBE-SCHEDULE-SERVICE-WORKSTATIONS */
Object maybe_schedule_service_workstations(both_future_and_current_p)
    Object both_future_and_current_p;
{
    Object workstation, ab_loop_list_;

    x_note_fn_call(115,104);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    maybe_schedule_service_workstation(workstation,both_future_and_current_p);
    goto next_loop;
  end_loop:;
    maybe_schedule_service_workstations_final();
    return VALUES_1(Nil);
}

static Object Qworkstation;        /* workstation */

static Object Qpropagate_all_workspace_changes_to_image_planes;  /* propagate-all-workspace-changes-to-image-planes */

/* MAYBE-SCHEDULE-TASK-TO-RUN-PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES */
Object maybe_schedule_task_to_run_propagate_all_workspace_changes_to_image_planes()
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed, ctask, p, v, q;
    char svref_new_value_1, temp_2, g2_p;
    double temp_1, aref_new_value, arg, arg_1;
    Declare_special(1);

    x_note_fn_call(115,105);
    if ( 
	    !(Future_task_to_run_propagate_all_workspace_changes_to_image_planes 
	    && 
	    ISVREF(Future_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    (SI_Long)6L))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = 
		Future_task_to_run_propagate_all_workspace_changes_to_image_planes;
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Service_workstation_interval);
	aref_new_value = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
		temp_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Qworkstation;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qpropagate_all_workspace_changes_to_image_planes;
	temp = 
		SYMBOL_FUNCTION(Qpropagate_all_workspace_changes_to_image_planes);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SYMBOL(Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes,
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
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    goto end_1;
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (Current_task_to_run_propagate_all_workspace_changes_to_image_planes 
	    && 
	    ISVREF(Current_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    (SI_Long)6L)) {
	arg = 
		DFLOAT_ISAREF_1(ISVREF(Current_task_to_run_propagate_all_workspace_changes_to_image_planes,
		(SI_Long)1L),(SI_Long)0L);
	arg_1 = 
		DFLOAT_ISAREF_1(ISVREF(Current_task_to_run_propagate_all_workspace_changes_to_image_planes,
		(SI_Long)3L) ? Current_g2_time : Current_real_time,
		(SI_Long)0L);
	temp_2 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2) {
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = 
		Current_task_to_run_propagate_all_workspace_changes_to_image_planes;
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)11L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Qworkstation;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = 
		Qpropagate_all_workspace_changes_to_image_planes;
	temp = 
		SYMBOL_FUNCTION(Qpropagate_all_workspace_changes_to_image_planes);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SYMBOL(Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes,
		old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_2:;
    }
    return VALUES_1(Nil);
}

static Object Qservice_workstations_final;  /* service-workstations-final */

/* MAYBE-SCHEDULE-SERVICE-WORKSTATIONS-FINAL */
Object maybe_schedule_service_workstations_final()
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double temp_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(115,106);
    if (Background_processes) {
	if ( !(Task_to_run_service_workstations_final && 
		ISVREF(Task_to_run_service_workstations_final,(SI_Long)6L))) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = Task_to_run_service_workstations_final;
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp,svref_arg_2) = svref_new_value;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp = ISVREF(task,(SI_Long)1L);
	    temp_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(Service_workstations_final_interval);
	    aref_new_value = DFLOAT_ISAREF_1(Current_real_time,
		    (SI_Long)0L) + temp_1;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !TRUEP(T);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Qworkstation;
	    SVREF(task,FIX((SI_Long)7L)) = Qservice_workstations_final;
	    temp = SYMBOL_FUNCTION(Qservice_workstations_final);
	    SVREF(task,FIX((SI_Long)8L)) = temp;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	    new_1 = task;
	    if (CAS_SYMBOL(Qtask_to_run_service_workstations_final,old,
			new_1)) {
		if (old) {
		    if (EQ(old,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(old,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(old);
		    inline_note_reclaim_cons(old,Nil);
		    structure_being_reclaimed = old;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		      SVREF(old,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = old;
		}
		future_task_schedule_2(new_1);
		goto end_1;
	    }
	    else {
		inline_note_reclaim_cons(new_1,Nil);
		structure_being_reclaimed = new_1;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
		  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = new_1;
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
    }
    return VALUES_1(Nil);
}

static Object Qservice_workstation;  /* service-workstation */

/* MAYBE-SCHEDULE-SERVICE-WORKSTATION */
Object maybe_schedule_service_workstation(workstation_qm,
	    both_future_and_current_p)
    Object workstation_qm, both_future_and_current_p;
{
    Object workstation, schedule_task_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed, ctask, p, v, q;
    char svref_new_value_1, temp_2, g2_p;
    double temp_1, aref_new_value, arg, arg_1;
    Declare_special(1);

    x_note_fn_call(115,107);
    if ( !TRUEP(workstation_qm) && System_window)
	workstation_qm = ISVREF(System_window,(SI_Long)2L);
    if ( !TRUEP(workstation_qm)) {
	maybe_schedule_service_workstations(Nil);
	return VALUES_1(Nil);
    }
    workstation = workstation_qm;
    schedule_task_qm = ISVREF(workstation,(SI_Long)48L);
    if ( !(schedule_task_qm && ISVREF(schedule_task_qm,(SI_Long)6L))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(workstation,(SI_Long)48L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Service_workstation_interval);
	aref_new_value = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
		temp_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Qworkstation;
	SVREF(task,FIX((SI_Long)7L)) = Qservice_workstation;
	temp = SYMBOL_FUNCTION(Qservice_workstation);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = workstation;
	new_1 = task;
	if (CAS_SVREF(workstation,(SI_Long)48L,old,new_1)) {
	    if (old) {
		if (EQ(old,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(old,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(old);
		inline_note_reclaim_cons(old,Nil);
		structure_being_reclaimed = old;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    goto end_1;
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    schedule_task_qm = ISVREF(workstation,(SI_Long)47L);
    if (schedule_task_qm && ISVREF(schedule_task_qm,(SI_Long)6L)) {
	arg = DFLOAT_ISAREF_1(ISVREF(schedule_task_qm,(SI_Long)1L),
		(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(ISVREF(schedule_task_qm,(SI_Long)3L) ? 
		Current_g2_time : Current_real_time,(SI_Long)0L);
	temp_2 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2 ? both_future_and_current_p || 
	    EQ(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)1L),
	    Qx11_window) && queue_non_empty_p(ISVREF(System_window,
	    (SI_Long)47L)) || queue_non_empty_p(ISVREF(workstation,
	    (SI_Long)2L)) || 
	    pending_drawing_for_workstation_p(workstation) : TRUEP(Nil)) {
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(workstation,(SI_Long)47L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)11L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Qworkstation;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qservice_workstation;
	temp = SYMBOL_FUNCTION(Qservice_workstation);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = workstation;
	new_1 = task;
	if (CAS_SVREF(workstation,(SI_Long)47L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
	    return VALUES_1(task);
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_9;   /* "[G2 internal warning] count-of-pending-workspace-drawing ended up non-zero after complete propagation! (= ~d)" */

/* PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES */
Object propagate_all_workspace_changes_to_image_planes()
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object workstation, ab_loop_list_, gensym_window;
    SI_Long arg, arg_1, arg_2;
    Declare_special(1);

    x_note_fn_call(115,108);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = 
	    Future_task_to_run_propagate_all_workspace_changes_to_image_planes;
    if (CAS_SYMBOL(Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes,
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
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = 
	    Current_task_to_run_propagate_all_workspace_changes_to_image_planes;
    if (CAS_SYMBOL(Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes,
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
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    if (IFIX(Count_of_pending_workspace_drawing) > (SI_Long)0L) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
	gensym_window = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensym_window = ISVREF(workstation,(SI_Long)1L);
	check_for_pending_drawing_on_window(gensym_window);
	goto next_loop_2;
      end_loop_2:;
	arg = IFIX(FIXNUM_NEGATE(Number_of_all_threads));
	arg_1 = IFIX(Count_of_pending_workspace_drawing) - (SI_Long)0L;
	arg_2 = IFIX(Number_of_all_threads);
	if ( !(arg < arg_1 && arg_1 < arg_2))
	    notify_user_at_console(2,string_constant_9,
		    Count_of_pending_workspace_drawing);
    }
    return VALUES_1(Nil);
}

Object Normal_workstation_servicing_time_limit = UNBOUND;

Object Prefer_interfaces_workstation_servicing_time_limit = UNBOUND;

/* SERVICE-WORKSTATIONS-FINAL */
Object service_workstations_final()
{
    x_note_fn_call(115,109);
    service_background_processes();
    return maybe_schedule_service_workstations_final();
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_g2_init_file_qm, Qdo_g2_init_file_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_in_which_to_launch_recompilation_qm, Qworkstation_in_which_to_launch_recompilation_qm);

Object Need_call_system_start = UNBOUND;

static Object string_constant_10;  /* "An incomplete workstation was encountered ~
				    *       and ignored by G2."
				    */

static Object Qservice_workstation_g2_init;  /* service-workstation-g2-init */

static Object Qlogged_out;         /* logged-out */

static Object Qchanging_kbs;       /* changing-kbs */

static Object Qlogging_in;         /* logging-in */

static Object Qservice_workstation_enter_login;  /* service-workstation-enter-login */

static Object Qreloading;          /* reloading */

static Object Qstarting;           /* starting */

static Object Qservice_workstation_launch_recompilation;  /* service-workstation-launch-recompilation */

static Object Qservice_workstation_event;  /* service-workstation-event */

static Object Qservice_workstation_keep_refreshing_image;  /* service-workstation-keep-refreshing-image */

static Object Qediting;            /* editing */

static Object Qservice_workstation_handle_search_states;  /* service-workstation-handle-search-states */

/* SERVICE-WORKSTATION-MAIN */
Object service_workstation_main(workstation)
    Object workstation;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    volatile Object work_was_done_qm;
    Object initial_time_slice_expired_p;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, gensymed_symbol_1;
    Object index_of_top_of_backtrace_stack, login_state, workstation_event_qm;
    Object current_workstation_event, in_edit_warning_context_p;
    Object items_warned_in_edit_warning_context, event_interpretation_qm;
    Object context_of_handler_qm, element, ab_loop_list_, kb_search_state;
    Object frame_serial_number, elements_to_delete, ab_loopvar_, ab_loopvar__1;
    Object xa, ya;
    volatile Object finished_qm;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(17);
    Object result;

    x_note_fn_call(115,110);
    SAVE_STACK();
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(workstation,(SI_Long)47L);
    if (CAS_SVREF(workstation,(SI_Long)47L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = ISVREF(workstation,(SI_Long)48L);
    if (CAS_SVREF(workstation,(SI_Long)48L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    if ( !TRUEP(ISVREF(workstation,(SI_Long)1L))) {
	notify_user_at_console(1,string_constant_10);
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    if (workstation_dead_p(workstation)) {
	flush_workstation(workstation);
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    work_was_done_qm = Nil;
    initial_time_slice_expired_p = time_slice_expired_p();
    outer_with_icp_buffer_coelescing_scope_qm = 
	    With_icp_buffer_coelescing_scope_qm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm,Qwith_icp_buffer_coelescing_scope_qm,with_icp_buffer_coelescing_scope_qm,
	    16);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
      LOCK(For_workstation);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_workstation_1 = workstation;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		  15);
	    current_workstation_window = ISVREF(Current_workstation,
		    (SI_Long)1L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		    14);
	      current_g2_window_for_this_workstation_qm = 
		      ISVREF(Current_workstation,(SI_Long)25L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		      13);
		type_of_current_workstation_window = 
			ISVREF(Current_workstation_window,(SI_Long)1L);
		PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			12);
		  current_workstation_native_window_qm = 
			  ISVREF(Current_workstation_window,(SI_Long)17L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			  11);
		    temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
		    current_workstation_context = CAR(temp_1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			    10);
		      type_of_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			      9);
			specific_structure_for_current_workstation_context 
				= ISVREF(Current_workstation_context,
				(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				8);
			  current_workstation_detail_pane = 
				  detail_pane(Current_workstation_window);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				  7);
			    current_g2_user_mode_qm = 
				    ISVREF(Current_workstation,(SI_Long)19L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				    6);
			      new_g2_classic_ui_p = 
				      get_value_for_current_workstation_new_g2_classic_ui_p();
			      PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				      5);
				servicing_workstation_qm = T;
				PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					4);
				  validate_mouse_pointers(workstation);
				next_loop_2:
				  gensymed_symbol = 
					  ISVREF(Specific_structure_for_current_workstation_context,
					  (SI_Long)0L);
				  gensymed_symbol = 
					  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
					  Qtype_description_of_unique_type_name_of_gensym_structure),
					  (SI_Long)9L),(SI_Long)4L);
				  gensymed_symbol_1 = 
					  Specific_structure_for_current_workstation_context;
				  if (inline_funcall_1(gensymed_symbol,
					  gensymed_symbol_1))
				      goto end_loop_2;
				  abort_current_workstation_context(Type_of_current_workstation_context);
				  goto next_loop_2;
				end_loop_2:
				  if (Do_g2_init_file_qm) {
				      Do_g2_init_file_qm = Nil;
				      if ( !EQ(Unevaluated_expression,
					      Within_side_limits)) {
					  index_of_top_of_backtrace_stack 
						  = 
						  Index_of_top_of_backtrace_stack;
					  PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
						  0);
					    if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						    Size_of_basic_backtrace_information),
						    Maximum_index_in_backtrace_stack_for_internal_error)) 
							{
						temp = 
							FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
						Index_of_top_of_backtrace_stack 
							= temp;
						temp = 
							Backtrace_stack_for_internal_error;
						svref_arg_2 = 
							Index_of_top_of_backtrace_stack;
						SVREF(temp,svref_arg_2) = 
							FIX((SI_Long)0L);
						temp = 
							FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
						Index_of_top_of_backtrace_stack 
							= temp;
						temp = 
							Backtrace_stack_for_internal_error;
						svref_arg_2 = 
							Index_of_top_of_backtrace_stack;
						SVREF(temp,svref_arg_2) = Nil;
						temp = 
							FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
						Index_of_top_of_backtrace_stack 
							= temp;
						temp = 
							Backtrace_stack_for_internal_error;
						svref_arg_2 = 
							Index_of_top_of_backtrace_stack;
						SVREF(temp,svref_arg_2) = 
							Qservice_workstation_g2_init;
					    }
					    if ( !TRUEP(Nil)) {
						if ( 
							!TRUEP(do_g2_kb_load_at_launch()))
						    enable_scc_check();
					    }
					  POP_SPECIAL();
				      }
				  }
				  login_state = ISVREF(workstation,
					  (SI_Long)28L);
				  if (EQ(login_state,Qlogged_out) || 
					  EQ(login_state,Qchanging_kbs)) {
				      SVREF(workstation,FIX((SI_Long)28L)) 
					      = Qlogging_in;
				      index_of_top_of_backtrace_stack = 
					      Index_of_top_of_backtrace_stack;
				      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					      0);
					if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						Size_of_basic_backtrace_information),
						Maximum_index_in_backtrace_stack_for_internal_error)) 
						    {
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    FIX((SI_Long)0L);
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = Nil;
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    Qservice_workstation_enter_login;
					}
					enter_user_settings_editor(EQ(login_state,
						Qchanging_kbs) ? 
						Qreloading : Qstarting);
				      POP_SPECIAL();
				  }
				  if (EQ(workstation,
					  Workstation_in_which_to_launch_recompilation_qm) 
					  && 
					  logged_in_workstation_session_p(workstation)) 
					      {
				      index_of_top_of_backtrace_stack = 
					      Index_of_top_of_backtrace_stack;
				      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					      0);
					if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						Size_of_basic_backtrace_information),
						Maximum_index_in_backtrace_stack_for_internal_error)) 
						    {
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    FIX((SI_Long)0L);
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = Nil;
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    Qservice_workstation_launch_recompilation;
					}
					launch_recompilation_for_this_kb();
				      POP_SPECIAL();
				  }
				  temp_2 =  
					  !TRUEP(queue_empty_p(ISVREF(Current_workstation,
					  (SI_Long)2L)));
				  if (temp_2);
				  else {
				      if (poll_workstation())
					  work_was_done_qm = T;
				      temp_2 =  
					      !TRUEP(queue_empty_p(ISVREF(Current_workstation,
					      (SI_Long)2L)));
				  }
				  if (temp_2) {
				      index_of_top_of_backtrace_stack = 
					      Index_of_top_of_backtrace_stack;
				      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					      3);
					if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						Size_of_basic_backtrace_information),
						Maximum_index_in_backtrace_stack_for_internal_error)) 
						    {
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    FIX((SI_Long)0L);
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = Nil;
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    Qservice_workstation_event;
					}
					workstation_event_qm = 
						shift_lexical_analysis_of_current_workstation_qm();
					if ( !(workstation_event_qm || 
						queue_empty_p(ISVREF(Current_workstation,
						(SI_Long)2L))))
					    work_was_done_qm = T;
					if (workstation_event_qm) {
					    LOCK(Servicing_workstation_event);
					    if (PUSH_UNWIND_PROTECT(0)) {
						current_workstation_event 
							= workstation_event_qm;
						PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_event,Qcurrent_workstation_event,current_workstation_event,
							2);
						  in_edit_warning_context_p 
							  = T;
						  items_warned_in_edit_warning_context 
							  = Nil;
						  PUSH_SPECIAL_WITH_SYMBOL(Items_warned_in_edit_warning_context,Qitems_warned_in_edit_warning_context,items_warned_in_edit_warning_context,
							  1);
						    PUSH_SPECIAL_WITH_SYMBOL(In_edit_warning_context_p,Qin_edit_warning_context_p,in_edit_warning_context_p,
							    0);
						      result = find_event_interpretation(Current_workstation_event,
							      workstation);
						      MVS_2(result,
							      event_interpretation_qm,
							      context_of_handler_qm);
						      if (Trace_workstation_events)
							  trace_workstation_event(ISVREF(Current_workstation,
								  (SI_Long)11L),
								  event_interpretation_qm,
								  context_of_handler_qm);
						      if (ISVREF(workstation,
							      (SI_Long)30L) 
							      &&  
							      !(event_handler_refreshes_image_plane_p(event_interpretation_qm) 
							      && 
							      EQ(ISVREF(workstation,
							      (SI_Long)30L),
							      ISVREF(Current_workstation_event,
							      (SI_Long)7L)))) {
							  continue_refreshing_image_plane(workstation);
							  requeue_workstation_event(Current_workstation_event,
								  workstation);
							  work_was_done_qm = T;
						      }
						      else if (event_interpretation_qm) 
								  {
							  run_event_handler(event_interpretation_qm,
								  ISVREF(Current_workstation,
								  (SI_Long)11L));
							  reclaim_workstation_event(Current_workstation_event);
							  work_was_done_qm = T;
						      }
						      else {
							  reclaim_workstation_event(Current_workstation_event);
							  work_was_done_qm = T;
						      }
						      if (event_interpretation_qm)
							  reclaim_event_interpretation(event_interpretation_qm);
						      reclaim_gensym_list_1(Items_warned_in_edit_warning_context);
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					    }
					    POP_UNWIND_PROTECT(0);
					    UNLOCK(Servicing_workstation_event);
					    CONTINUE_UNWINDING(0);
					}
				      POP_SPECIAL();
				  }
				  if ( !TRUEP(work_was_done_qm) && 
					  ISVREF(workstation,(SI_Long)30L)) {
				      index_of_top_of_backtrace_stack = 
					      Index_of_top_of_backtrace_stack;
				      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					      0);
					if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						Size_of_basic_backtrace_information),
						Maximum_index_in_backtrace_stack_for_internal_error)) 
						    {
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    FIX((SI_Long)0L);
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = Nil;
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    Qservice_workstation_keep_refreshing_image;
					}
					continue_refreshing_image_plane(workstation);
				      POP_SPECIAL();
				      work_was_done_qm = T;
				  }
				  if ( !TRUEP(work_was_done_qm) && 
					  EQ(Type_of_current_workstation_context,
					  Qediting) && 
					  extend_parsing_or_exit_editor_as_appropriate())
				      work_was_done_qm = T;
				  if (work_on_drawing_window(Current_workstation_window,
					  T))
				      work_was_done_qm = T;
				  if (ISVREF(workstation,(SI_Long)31L)) {
				      index_of_top_of_backtrace_stack = 
					      Index_of_top_of_backtrace_stack;
				      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					      0);
					if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
						Size_of_basic_backtrace_information),
						Maximum_index_in_backtrace_stack_for_internal_error)) 
						    {
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    FIX((SI_Long)0L);
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = Nil;
					    temp = 
						    FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					    Index_of_top_of_backtrace_stack 
						    = temp;
					    temp = 
						    Backtrace_stack_for_internal_error;
					    svref_arg_2 = 
						    Index_of_top_of_backtrace_stack;
					    SVREF(temp,svref_arg_2) = 
						    Qservice_workstation_handle_search_states;
					}
					element = Nil;
					ab_loop_list_ = ISVREF(workstation,
						(SI_Long)31L);
					kb_search_state = Nil;
					frame_serial_number = Nil;
					elements_to_delete = Nil;
					ab_loopvar_ = Nil;
					ab_loopvar__1 = Nil;
				      next_loop_3:
					if ( !TRUEP(ab_loop_list_))
					    goto end_loop_3;
					element = M_CAR(ab_loop_list_);
					ab_loop_list_ = M_CDR(ab_loop_list_);
					kb_search_state = CAR(element);
					frame_serial_number = CDR(element);
					gensymed_symbol = 
						ISVREF(kb_search_state,
						(SI_Long)3L);
					temp_2 = 
						SIMPLE_VECTOR_P(kb_search_state) 
						? 
						EQ(ISVREF(kb_search_state,
						(SI_Long)1L),
						Qavailable_frame_vector) : 
						TRUEP(Qnil);
					if (temp_2);
					else
					    temp_2 = 
						    FIXNUMP(gensymed_symbol) 
						    ? 
						    IFIX(gensymed_symbol) 
						    == (SI_Long)-1L : 
						    TRUEP(Nil);
					if (temp_2);
					else if (FIXNUMP(frame_serial_number))
					    temp_2 = 
						    FIXNUMP(gensymed_symbol) 
						    ? 
						    FIXNUM_LT(frame_serial_number,
						    gensymed_symbol) : 
						    TRUEP(T);
					else if (FIXNUMP(gensymed_symbol))
					    temp_2 = TRUEP(Nil);
					else {
					    xa = M_CAR(frame_serial_number);
					    ya = M_CAR(gensymed_symbol);
					    temp_2 = FIXNUM_LT(xa,ya);
					    if (temp_2);
					    else
						temp_2 = FIXNUM_EQ(xa,ya) ?
							 
							FIXNUM_LT(M_CDR(frame_serial_number),
							M_CDR(gensymed_symbol)) 
							: TRUEP(Qnil);
					}
					if (temp_2) {
					    ab_loopvar__1 = 
						    gensym_cons_1(element,Nil);
					    if (ab_loopvar_)
						M_CDR(ab_loopvar_) = 
							ab_loopvar__1;
					    else
						elements_to_delete = 
							ab_loopvar__1;
					    ab_loopvar_ = ab_loopvar__1;
					}
					else {
					    finished_qm = Nil;
					    if (PUSH_UNWIND_PROTECT(0)) {
						search_items_a_little(kb_search_state,
							Current_frame_serial_number);
						finished_qm = T;
					    }
					    POP_UNWIND_PROTECT(0);
					    if ( !TRUEP(finished_qm)) {
						delete_gensym_element_1(element,
							ISVREF(workstation,
							(SI_Long)31L));
						reclaim_frame_serial_number(CDR(element));
						reclaim_gensym_cons_1(element);
					    }
					    CONTINUE_UNWINDING(0);
					}
					goto next_loop_3;
				      end_loop_3:
					if (elements_to_delete) {
					    element = Nil;
					    ab_loop_list_ = elements_to_delete;
					  next_loop_4:
					    if ( !TRUEP(ab_loop_list_))
						goto end_loop_4;
					    element = M_CAR(ab_loop_list_);
					    ab_loop_list_ = 
						    M_CDR(ab_loop_list_);
					    temp = 
						    delete_gensym_element_1(element,
						    ISVREF(workstation,
						    (SI_Long)31L));
					    SVREF(workstation,
						    FIX((SI_Long)31L)) = temp;
					    reclaim_frame_serial_number(CDR(element));
					    reclaim_gensym_cons_1(element);
					    goto next_loop_4;
					  end_loop_4:
					    reclaim_gensym_list_1(elements_to_delete);
					}
					temp_2 = TRUEP(T);
					goto end_3;
					temp_2 = TRUEP(Qnil);
				      end_3:;
				      POP_SPECIAL();
				  }
				  else
				      temp_2 = TRUEP(Nil);
				  if (temp_2)
				      work_was_done_qm = T;
				  if (native_menu_bar_really_needs_updating_p(workstation)) 
					      {
				      update_native_menu_bar(workstation);
				      work_was_done_qm = T;
				  }
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
      UNLOCK(For_workstation);
      CONTINUE_UNWINDING(1);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
    POP_SPECIAL();
    if (work_was_done_qm) {
	if (EQ(ISVREF(workstation,(SI_Long)28L),Qchanging_kbs))
	    finish_changing_kb_for_workstations();
	if ( !TRUEP(initial_time_slice_expired_p))
	    Last_workstation_serviced = workstation;
    }
    if (work_was_done_qm)
	maybe_schedule_service_workstation(workstation,T);
    if (Need_call_system_start) {
	Need_call_system_start = Nil;
	system_start();
    }
    RESTORE_STACK();
    return VALUES_1(work_was_done_qm);
}

/* SERVICE-WORKSTATION */
Object service_workstation(workstation)
    Object workstation;
{
    Object queue, result_1, queue_size;

    x_note_fn_call(115,111);
    queue = ISVREF(workstation,(SI_Long)2L);
    result_1 = service_workstation_main(workstation);
    queue_size = queue_length(queue);
  next_loop:
    if ( !(IFIX(queue_size) > (SI_Long)0L))
	goto end_loop;
    result_1 = service_workstation_main(workstation);
    queue_size = FIXNUM_SUB1(queue_size);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
}

static Object Qservice_workstation_enter_login_2;  /* service-workstation-enter-login-2 */

/* FINISH-CHANGING-KB-FOR-WORKSTATIONS */
Object finish_changing_kb_for_workstations()
{
    Object workstation, ab_loop_list_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Object index_of_top_of_backtrace_stack, temp_1, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(13);
    Object result;

    x_note_fn_call(115,112);
    SAVE_STACK();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(workstation_dead_p(workstation)) && EQ(ISVREF(workstation,
	    (SI_Long)28L),Qchanging_kbs)) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    12);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      11);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			10);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  9);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    8);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      7);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				6);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  5);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    4);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      3);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					2);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  1);
				    SVREF(workstation,FIX((SI_Long)28L)) = 
					    Qlogging_in;
				    index_of_top_of_backtrace_stack = 
					    Index_of_top_of_backtrace_stack;
				    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
					    0);
				      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
					      Size_of_basic_backtrace_information),
					      Maximum_index_in_backtrace_stack_for_internal_error)) 
						  {
					  temp_1 = 
						  FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					  Index_of_top_of_backtrace_stack 
						  = temp_1;
					  temp_1 = 
						  Backtrace_stack_for_internal_error;
					  svref_arg_2 = 
						  Index_of_top_of_backtrace_stack;
					  SVREF(temp_1,svref_arg_2) = 
						  FIX((SI_Long)0L);
					  temp_1 = 
						  FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					  Index_of_top_of_backtrace_stack 
						  = temp_1;
					  temp_1 = 
						  Backtrace_stack_for_internal_error;
					  svref_arg_2 = 
						  Index_of_top_of_backtrace_stack;
					  SVREF(temp_1,svref_arg_2) = Nil;
					  temp_1 = 
						  FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
					  Index_of_top_of_backtrace_stack 
						  = temp_1;
					  temp_1 = 
						  Backtrace_stack_for_internal_error;
					  svref_arg_2 = 
						  Index_of_top_of_backtrace_stack;
					  SVREF(temp_1,svref_arg_2) = 
						  Qservice_workstation_enter_login_2;
				      }
				      enter_user_settings_editor(Qreloading);
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
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
    }
    goto next_loop;
  end_loop:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* TRACK-MOUSE-INTO-SPOT-FOR-SPOT */
Object track_mouse_into_spot_for_spot(spot)
    Object spot;
{
    Object frame_represented_qm, sub_class_bit_vector, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(115,113);
    if (ISVREF(spot,(SI_Long)3L)) {
	frame_represented_qm = ISVREF(spot,(SI_Long)4L);
	if (frame_represented_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame_represented_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    gensymed_symbol_3 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(frame_represented_qm,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)0L),(SI_Long)1L);
	    gensymed_symbol_4 = frame_represented_qm;
	    gensymed_symbol_5 = ISVREF(spot,(SI_Long)1L);
	    inline_funcall_2(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5);
	}
	return VALUES_1(SVREF(spot,FIX((SI_Long)3L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-DEFER-REFRESHING-IMAGE-PLANE-1 */
Object maybe_defer_refreshing_image_plane_1(image_plane)
    Object image_plane;
{
    Object workstation, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(115,114);
    SAVE_STACK();
    workstation = Workstation_with_image_plane_being_refreshed;
    if ( !TRUEP(queue_empty_p(ISVREF(workstation,(SI_Long)2L)))) {
	if (Servicing_workstation_qm && EQ(Current_workstation,workstation)) {
	    result = maybe_defer_refreshing_image_plane_2(image_plane,
		    workstation);
	    RESTORE_STACK();
	    return result;
	}
	else {
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
					SAVE_VALUES(maybe_defer_refreshing_image_plane_2(image_plane,
						workstation));
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
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* MAYBE-DEFER-REFRESHING-IMAGE-PLANE-2 */
Object maybe_defer_refreshing_image_plane_2(image_plane,workstation)
    Object image_plane, workstation;
{
    Object event, current_workstation_1, event_interpretation_qm;
    Object refreshing_qm;
    Declare_special(1);

    x_note_fn_call(115,115);
    event = queue_peek(ISVREF(workstation,(SI_Long)2L));
    current_workstation_1 = workstation;
    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
	    0);
      event_interpretation_qm = interpret_workstation_event(event,workstation);
    POP_SPECIAL();
    refreshing_qm = event_interpretation_qm && 
	    event_handler_refreshes_image_plane_p(event_interpretation_qm) 
	    ? (EQ(ISVREF(event,(SI_Long)7L),image_plane) ? T : Nil) : Qnil;
    reclaim_event_interpretation(event_interpretation_qm);
    if (refreshing_qm) {
	SVREF(workstation,FIX((SI_Long)30L)) = image_plane;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* CONTINUE-REFRESHING-IMAGE-PLANE */
Object continue_refreshing_image_plane(workstation)
    Object workstation;
{
    Object svref_old_value, temp;

    x_note_fn_call(115,116);
    svref_old_value = ISVREF(workstation,(SI_Long)30L);
    SVREF(workstation,FIX((SI_Long)30L)) = Nil;
    temp = svref_old_value;
    return invalidate_image_plane(temp);
}

static Object Qdefault;            /* default */

static Object string_constant_11;  /* "A millisecond sleep interval must be an integer from 0 through 1000." */

/* COMPILE-MILLISECOND-SLEEP-INTERVAL-FOR-SLOT */
Object compile_millisecond_sleep_interval_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,117);
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
    if (EQ(parse_result,Qdefault))
	return VALUES_1(Nil);
    else if ( !FIXNUMP(parse_result))
	return VALUES_1(Bad_phrase);
    else if (IFIX(parse_result) >= (SI_Long)0L && IFIX(parse_result) <= 
	    (SI_Long)1000L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_11);
	return VALUES_2(temp,temp_1);
    }
}

static Object array_constant_5;    /* # */

/* WRITE-MILLISECOND-SLEEP-INTERVAL-FROM-SLOT */
Object write_millisecond_sleep_interval_from_slot(fixnum_qm,gensymed_symbol)
    Object fixnum_qm, gensymed_symbol;
{
    x_note_fn_call(115,118);
    if (fixnum_qm)
	return twrite(fixnum_qm);
    else
	return twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)11L));
}

static Object array_constant_6;    /* # */

static Object Qseconds;            /* seconds */

/* WRITE-MINIMUM-SCHEDULING-INTERVAL?-FROM-SLOT */
Object write_minimum_scheduling_interval_qm_from_slot(interval_qm,
	    gensymed_symbol)
    Object interval_qm, gensymed_symbol;
{
    SI_Long temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(115,119);
    if ( !TRUEP(interval_qm))
	return twrite_beginning_of_wide_string(array_constant_6,
		FIX((SI_Long)10L));
    else {
	temp = IFIX(interval_qm) % (SI_Long)1000L;
	if (temp == (SI_Long)0L) {
	    temp = IFIX(interval_qm) / (SI_Long)1000L;
	    return print_constant(2,FIX(temp),Qseconds);
	}
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		result = print_constant(2,
			DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(interval_qm) / 
			1000.0),Qseconds);
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
    }
}

static Object Qcontinuous;         /* continuous */

static Object array_constant_7;    /* # */

/* COMPILE-MINIMUM-SCHEDULING-INTERVAL?-FOR-SLOT */
Object compile_minimum_scheduling_interval_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object interval, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,120);
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
    if (EQ(parse_result,Qcontinuous))
	return VALUES_1(Nil);
    else if (CONSP(parse_result) && phrase_number_p(M_CAR(parse_result)) 
	    && EQ(M_CDR(parse_result),Qseconds)) {
	interval = M_CAR(parse_result);
	if (FIXNUMP(interval) && IFIX(interval) <= (SI_Long)0L) {
	    temp = Bad_phrase;
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_7,
		    FIX((SI_Long)39L));
	    return VALUES_2(temp,temp_1);
	}
	else if ( !FIXNUMP(interval) &&  
		!(INLINE_DOUBLE_FLOAT_VECTOR_P(interval) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interval)) == (SI_Long)1L))
	    return VALUES_1(Bad_phrase);
	else
	    return adjust_scheduling_interval(interval);
    }
    else
	return VALUES_1(Bad_phrase);
}

static Object string_constant_12;  /* "The interval must be less than or equal to 6 days." */

static Object string_constant_13;  /* "The interval must be greater than 0." */

/* ADJUST-SCHEDULING-INTERVAL */
Object adjust_scheduling_interval(interval_in_seconds)
    Object interval_in_seconds;
{
    Object temp, temp_1;
    SI_Long temp_2, temp_3;
    double given_value, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(115,121);
    if (FIXNUMP(interval_in_seconds)) {
	if (IFIX(interval_in_seconds) > IFIX(Most_positive_fixnum) >>  -  
		- (SI_Long)10L) {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(string_constant_12);
	    return VALUES_2(temp,temp_1);
	}
	else
	    return VALUES_1(FIX(IFIX(interval_in_seconds) * (SI_Long)1000L));
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    given_value = 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(interval_in_seconds) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interval_in_seconds)) 
		    == (SI_Long)1L ? DFLOAT_ISAREF_1(interval_in_seconds,
		    (SI_Long)0L) : DFLOAT_ISAREF_1(interval_in_seconds,
		    (SI_Long)0L);
	    arg = given_value;
	    arg_1 = (double)(IFIX(Most_positive_fixnum) >>  -  - (SI_Long)10L);
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp = Bad_phrase;
		temp_1 = copy_text_string(string_constant_12);
		result = VALUES_2(temp,temp_1);
	    }
	    else {
		arg = given_value;
		arg_1 = 1.0;
		if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    result = VALUES_1(FIX(inline_ceiling_1(given_value) * 
			    (SI_Long)1000L));
		else {
		    arg = given_value;
		    arg_1 = 0.0;
		    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			arg = given_value;
			arg_1 = 
				DOUBLE_FLOAT_TO_DOUBLE(Minimum_minimum_float_scheduling_interval);
			if (arg < arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1))
			    result = VALUES_1(Minimum_minimum_fixnum_scheduling_interval);
			else {
			    temp_2 = 
				    IFIX(Minimum_minimum_fixnum_scheduling_interval);
			    temp_3 = inline_ceiling_1(1000.0 / 
				    inline_ffloor_1(1.0 / (given_value - 
				    0.001)));
			    result = VALUES_1(FIX(MAX(temp_2,temp_3)));
			}
		    }
		    else {
			temp = Bad_phrase;
			temp_1 = copy_text_string(string_constant_13);
			result = VALUES_2(temp,temp_1);
		    }
		}
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

static Object Qfloat_array;        /* float-array */

/* INVERT-ADJUSTED-SCHEDULING-INTERVAL */
Object invert_adjusted_scheduling_interval(interval)
    Object interval;
{
    Object temp, temp_1, amf_available_array_cons_qm, amf_array, temp_2;
    Object temp_3, amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(115,122);
    if ( !FIXNUMP(interval))
	temp = FIX((SI_Long)1L);
    else {
	temp_1 = FIX((SI_Long)0L);
	temp = chestnut_modf_function(interval,FIX((SI_Long)1000L));
	if (NUM_EQ(temp_1,temp))
	    temp = chestnut_floorf_function(interval,FIX((SI_Long)1000L));
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_2 = Vector_of_simple_float_array_pools;
		temp_3 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		}
		else {
		    temp_2 = Available_float_array_conses_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    temp_2 = Available_float_array_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    aref_new_value = 0.001 * (double)IFIX(interval);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
    }
    return VALUES_1(temp);
}

/* IDLE-TIME-WHEN-POLLING */
Object idle_time_when_polling()
{
    Object temp;

    x_note_fn_call(115,123);
    temp = ISVREF(Timing_parameters,(SI_Long)23L) ? 
	    ISVREF(Timing_parameters,(SI_Long)23L) : FIX((SI_Long)40L);
    return VALUES_1(temp);
}

/* ABSORB-LOCAL-EVENT-AB-SIDE */
Object absorb_local_event_ab_side(event)
    Object event;
{
    Object temp, temp_1, temp_2, temp_3, temp_4;

    x_note_fn_call(115,124);
    temp = Current_workstation;
    temp_1 = ISVREF(event,(SI_Long)1L);
    temp_2 = ISVREF(event,(SI_Long)3L);
    temp_3 = ISVREF(event,(SI_Long)4L);
    temp_4 = ISVREF(event,(SI_Long)2L);
    return absorb_local_event_ab_side_1(temp,temp_1,temp_2,temp_3,temp_4,
	    copy_event_plist(ISVREF(event,(SI_Long)7L)));
}

static Object Qwindow;             /* window */

static Object Qg2_defstruct_structure_name_workspace_view_g2_struct;  /* g2-defstruct-structure-name::workspace-view-g2-struct */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

/* ABSORB-LOCAL-EVENT-AB-SIDE-1 */
Object absorb_local_event_ab_side_1(workstation,key_code,x,y,timestamp,plist)
    Object workstation, key_code, x, y, timestamp, plist;
{
    Object gensym_window, window_handle_qm, native_window_qm;
    Object native_image_plane_qm, already_handled_p, pane_qm, image_plane_qm;
    Object left_qm, top_qm, width_qm, height_qm, incff_1_arg;
    Object result;

    x_note_fn_call(115,125);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    window_handle_qm = getf(plist,Qwindow,_);
    native_window_qm = find_native_window(2,gensym_window,window_handle_qm);
    native_image_plane_qm = SIMPLE_VECTOR_P(native_window_qm) && 
	    EQ(ISVREF(native_window_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_workspace_view_g2_struct) ? 
	    ISVREF(native_window_qm,(SI_Long)29L) : Qnil;
    already_handled_p = Nil;
    pane_qm = Nil;
    image_plane_qm = Nil;
    if (native_window_qm) {
	if (native_image_plane_qm) {
	    image_plane_qm = native_image_plane_qm;
	    pane_qm = ISVREF(native_image_plane_qm,(SI_Long)2L);
	    left_qm = getf(plist,Qleft,_);
	    top_qm = getf(plist,Qtop,_);
	    width_qm = getf(plist,Qwidth,_);
	    height_qm = getf(plist,Qheight,_);
	    if (left_qm && top_qm && width_qm && height_qm) {
		move_native_image_plane_to(native_image_plane_qm,left_qm,
			top_qm);
		pct_set_native_window_size(native_window_qm,width_qm,
			height_qm);
	    }
	}
	if ( 
		!TRUEP(control_event_uses_main_window_relative_coordinates_p(gensym_window,
		key_code,plist))) {
	    incff_1_arg = ISVREF(native_window_qm,(SI_Long)4L);
	    x = FIXNUM_ADD(x,incff_1_arg);
	    incff_1_arg = ISVREF(native_window_qm,(SI_Long)5L);
	    y = FIXNUM_ADD(y,incff_1_arg);
	}
	SVREF(workstation,FIX((SI_Long)5L)) = x;
	SVREF(workstation,FIX((SI_Long)6L)) = y;
	if (handle_native_window_event(native_window_qm,key_code,plist))
	    already_handled_p = T;
    }
    else if (window_handle_qm)
	pane_qm = detail_pane_for_workstation(workstation);
    else {
	result = decode_window_position(gensym_window,x,y);
	MVS_2(result,pane_qm,image_plane_qm);
    }
    if (already_handled_p)
	return reclaim_event_plist(plist);
    else
	return enqueue_workstation_event(9,workstation,key_code,x,y,
		timestamp,gensym_window,pane_qm,image_plane_qm,plist);
}

static Object Qcontrol_relative_coordinates;  /* control-relative-coordinates */

/* CONTROL-EVENT-USES-MAIN-WINDOW-RELATIVE-COORDINATES-P */
Object control_event_uses_main_window_relative_coordinates_p(gensym_window,
	    key_code,plist)
    Object gensym_window, key_code, plist;
{
    x_note_fn_call(115,126);
    if (IFIX(key_code) == (SI_Long)833L || IFIX(key_code) == (SI_Long)834L 
	    || IFIX(key_code) == (SI_Long)838L || IFIX(key_code) == 
	    (SI_Long)840L || IFIX(key_code) == (SI_Long)842L ? TRUEP(T) : 
	    TRUEP(Nil))
	return VALUES_1( !TRUEP(getf(plist,Qcontrol_relative_coordinates,
		_)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qg2_native_window;   /* g2-native-window */

/* CLEANUP-FOR-G2-NATIVE-WINDOW */
Object cleanup_for_g2_native_window(g2_native_window)
    Object g2_native_window;
{
    Object frame, sub_vector_qm, method_function_qm, native_window_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(115,127);
    frame = g2_native_window;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_native_window)) {
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
    native_window_qm = ISVREF(g2_native_window,(SI_Long)20L);
    if (native_window_qm) {
	ISVREF(g2_native_window,(SI_Long)20L) = Nil;
	SVREF(native_window_qm,FIX((SI_Long)15L)) = Nil;
	if (ISVREF(native_window_qm,(SI_Long)29L))
	    return delete_image_plane(ISVREF(native_window_qm,(SI_Long)29L));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-NATIVE-WINDOW-ITEM */
Object delete_native_window_item(native_window)
    Object native_window;
{
    Object item_qm;

    x_note_fn_call(115,128);
    item_qm = ISVREF(native_window,(SI_Long)15L);
    if (item_qm) {
	ISVREF(item_qm,(SI_Long)20L) = Nil;
	SVREF(native_window,FIX((SI_Long)15L)) = Nil;
	if ( !((SI_Long)0L != (IFIX(ISVREF(item_qm,(SI_Long)5L)) & 
		(SI_Long)512L)))
	    return delete_frame(item_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CREATE-NATIVE-WINDOW-ITEM */
Object create_native_window_item(native_window)
    Object native_window;
{
    Object item;

    x_note_fn_call(115,129);
    item = make_permanent_item(native_window_item_class(native_window));
    ISVREF(item,(SI_Long)20L) = native_window;
    return VALUES_1(item);
}

/* ENSURE-NATIVE-WINDOW-ITEM */
Object ensure_native_window_item(native_window)
    Object native_window;
{
    Object temp;

    x_note_fn_call(115,130);
    temp = ISVREF(native_window,(SI_Long)15L);
    if (temp)
	return VALUES_1(temp);
    else {
	temp = create_native_window_item(native_window);
	SVREF(native_window,FIX((SI_Long)15L)) = temp;
	synchronize_native_window_item(native_window);
	return VALUES_1(temp);
    }
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* NATIVE-WINDOW-ITEM-CLASS */
Object native_window_item_class(native_window)
    Object native_window;
{
    Object class_qm, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp, temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(115,131);
    class_qm = ISVREF(native_window,(SI_Long)14L);
    if (class_qm) {
	if (SYMBOLP(class_qm)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_qm;
	    key_hash_value = SXHASH_SYMBOL_1(class_qm) & 
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
		gensymed_symbol = class_qm;
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
    }
    else
	temp_2 = TRUEP(Nil);
    temp_1 = temp_2 ? class_qm : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(Qg2_native_window);
}

static Object Qnative_window_left;  /* native-window-left */

static Object Qnative_window_top;  /* native-window-top */

static Object Qnative_window_width;  /* native-window-width */

static Object Qnative_window_height;  /* native-window-height */

static Object Qnormal;             /* normal */

static Object Qnative_window_state;  /* native-window-state */

/* SYNCHRONIZE-NATIVE-WINDOW-ITEM */
Object synchronize_native_window_item(native_window)
    Object native_window;
{
    Object item_qm, do_not_note_permanent_changes_p, value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,132);
    if (ISVREF(native_window,(SI_Long)15L)) {
	item_qm = ISVREF(native_window,(SI_Long)15L);
	do_not_note_permanent_changes_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		0);
	  value = ISVREF(native_window,(SI_Long)4L);
	  temp = get_slot_value_function(item_qm,Qnative_window_left,Nil);
	  if ( !EQL(temp,value))
	      change_slot_value(3,item_qm,Qnative_window_left,value);
	  value = ISVREF(native_window,(SI_Long)5L);
	  temp = get_slot_value_function(item_qm,Qnative_window_top,Nil);
	  if ( !EQL(temp,value))
	      change_slot_value(3,item_qm,Qnative_window_top,value);
	  value = ISVREF(native_window,(SI_Long)6L);
	  temp = get_slot_value_function(item_qm,Qnative_window_width,Nil);
	  if ( !EQL(temp,value))
	      change_slot_value(3,item_qm,Qnative_window_width,value);
	  value = ISVREF(native_window,(SI_Long)7L);
	  temp = get_slot_value_function(item_qm,Qnative_window_height,Nil);
	  if ( !EQL(temp,value))
	      change_slot_value(3,item_qm,Qnative_window_height,value);
	  value = ISVREF(native_window,(SI_Long)8L);
	  if (value);
	  else
	      value = Qnormal;
	  temp = get_slot_value_function(item_qm,Qnative_window_state,Nil);
	  if ( !EQL(temp,value))
	      result = change_slot_value(3,item_qm,Qnative_window_state,value);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* G2-WINDOW-OF-NATIVE-WINDOW-ITEM? */
Object g2_window_of_native_window_item_qm(native_window_item)
    Object native_window_item;
{
    x_note_fn_call(115,133);
    if (ISVREF(native_window_item,(SI_Long)20L) && 
	    ISVREF(ISVREF(native_window_item,(SI_Long)20L),(SI_Long)1L))
	return g2_window_for_gensym_window_qm(ISVREF(ISVREF(native_window_item,
		(SI_Long)20L),(SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* INITIAL-G2-WINDOW-OF-VIEW */
Object initial_g2_window_of_view(class_1)
    Object class_1;
{
    x_note_fn_call(115,134);
    return VALUES_1(Nil);
}

/* GET-G2-WINDOW-OF-VIEW */
Object get_g2_window_of_view(g2_native_window)
    Object g2_native_window;
{
    Object temp;

    x_note_fn_call(115,135);
    temp = g2_window_of_native_window_item_qm(g2_native_window);
    return VALUES_1(temp);
}

/* IMAGE-PLANE-OF-WORKSPACE-VIEW? */
Object image_plane_of_workspace_view_qm(g2_workspace_view)
    Object g2_workspace_view;
{
    Object thing;

    x_note_fn_call(115,136);
    thing = ISVREF(g2_workspace_view,(SI_Long)20L);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_workspace_view_g2_struct))
	return VALUES_1(ISVREF(ISVREF(g2_workspace_view,(SI_Long)20L),
		(SI_Long)29L));
    else
	return VALUES_1(Nil);
}

/* WORKSPACE-OF-WORKSPACE-VIEW? */
Object workspace_of_workspace_view_qm(g2_workspace_view)
    Object g2_workspace_view;
{
    x_note_fn_call(115,137);
    if (image_plane_of_workspace_view_qm(g2_workspace_view))
	return VALUES_1(ISVREF(image_plane_of_workspace_view_qm(g2_workspace_view),
		(SI_Long)5L));
    else
	return VALUES_1(Nil);
}

/* INITIAL-WORKSPACE-OF-VIEW */
Object initial_workspace_of_view(class_1)
    Object class_1;
{
    x_note_fn_call(115,138);
    return VALUES_1(Nil);
}

/* GET-WORKSPACE-OF-VIEW */
Object get_workspace_of_view(g2_workspace_view)
    Object g2_workspace_view;
{
    Object temp;

    x_note_fn_call(115,139);
    temp = workspace_of_workspace_view_qm(g2_workspace_view);
    return VALUES_1(temp);
}

/* INITIAL-SCALE-OF-VIEW */
Object initial_scale_of_view(class_1)
    Object class_1;
{
    x_note_fn_call(115,140);
    return VALUES_1(Nil);
}

static Object Qx_scale;            /* x-scale */

static Object Qy_scale;            /* y-scale */

/* GET-SCALE-OF-VIEW */
Object get_scale_of_view(g2_workspace_view)
    Object g2_workspace_view;
{
    Object image_plane_qm, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, temp_2;

    x_note_fn_call(115,141);
    image_plane_qm = image_plane_of_workspace_view_qm(g2_workspace_view);
    if ( !TRUEP(image_plane_qm)) {
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
	temp_2 = new_float;
    }
    else if (FIXNUM_EQ(ISVREF(image_plane_qm,(SI_Long)11L),
	    ISVREF(image_plane_qm,(SI_Long)12L)))
	temp_2 = image_plane_x_scale_mf(image_plane_qm);
    else {
	temp_2 = image_plane_x_scale_mf(image_plane_qm);
	temp_2 = allocate_evaluation_structure(eval_list_4(Qx_scale,temp_2,
		Qy_scale,image_plane_y_scale_mf(image_plane_qm)));
    }
    return VALUES_1(temp_2);
}

/* PUT-CONTROL-REQUEST-FOR-G2-EXTENSION-WHERE-SLOT-IS-ABSENT */
Object put_control_request_for_g2_extension_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(115,142);
    delete_frame(value);
    return VALUES_1(Nil);
}

/* PUT-G2-CONNECTION-REQUEST-WHERE-SLOT-IS-ABSENT */
Object put_g2_connection_request_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(115,143);
    delete_frame(value);
    return VALUES_1(Nil);
}

static Object Qg2_connection_status;  /* g2-connection-status */

static Object Qui_client_connection_status;  /* ui-client-connection-status */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* PUT-G2-CONNECTION-STATUS */
Object put_g2_connection_status(g2_extension,value,initializing_p)
    Object g2_extension, value, initializing_p;
{
    x_note_fn_call(115,144);
    set_non_savable_lookup_slot_value(g2_extension,Qg2_connection_status,
	    value);
    if ( !TRUEP(initializing_p))
	update_subscriptions_from_virtual_attribute_change(g2_extension,
		get_property_value_function(3,
		get_symbol_properties_function(Qui_client_connection_status),
		Qvirtual_attribute,Nil),Nil);
    return VALUES_1(value);
}

/* COMPILE-G2-WINDOW-STYLE-OVERRIDE-FOR-SLOT */
Object compile_g2_window_style_override_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,145);
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
    if (EQ(parse_result,Qdefault))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-G2-WINDOW-STYLE-OVERRIDE-FROM-SLOT */
Object write_g2_window_style_override_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(115,146);
    temp = value;
    if (temp);
    else
	temp = Qdefault;
    return twrite_symbol(1,temp);
}

static Object Qg2_window_user_is_valid;  /* g2-window-user-is-valid */

/* G2-WINDOW-USER-IS-VALID-FUNCTION */
Object g2_window_user_is_valid_function(g2_window)
    Object g2_window;
{
    x_note_fn_call(115,147);
    return get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_user_is_valid,FIX((SI_Long)-1000L));
}

static Object Qg2_window_mode_is_valid;  /* g2-window-mode-is-valid */

/* G2-WINDOW-MODE-IS-VALID-FUNCTION */
Object g2_window_mode_is_valid_function(g2_window)
    Object g2_window;
{
    x_note_fn_call(115,148);
    return get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_mode_is_valid,FIX((SI_Long)-1000L));
}

/* WORKSTATION-FOR-G2-WINDOW?-FUNCTION */
Object workstation_for_g2_window_qm_function(g2_window)
    Object g2_window;
{
    x_note_fn_call(115,149);
    return VALUES_1(ISVREF(g2_window,(SI_Long)20L));
}

static Object Qg2_user_mode;       /* g2-user-mode */

static Object Qui_client_user_mode;  /* ui-client-user-mode */

/* PUT-G2-USER-MODE */
Object put_g2_user_mode(g2_window,value,initializing_p)
    Object g2_window, value, initializing_p;
{
    x_note_fn_call(115,150);
    set_non_savable_lookup_slot_value(g2_window,Qg2_user_mode,value);
    if ( !TRUEP(initializing_p))
	update_subscriptions_from_virtual_attribute_change(g2_window,
		get_property_value_function(3,
		get_symbol_properties_function(Qui_client_user_mode),
		Qvirtual_attribute,Nil),Nil);
    return VALUES_1(value);
}

static Object Qshow_operator_logbook_in_this_window_qm;  /* show-operator-logbook-in-this-window? */

/* PUT-SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW? */
Object put_show_operator_logbook_in_this_window_qm(g2_window,value,
	    initializing_qm)
    Object g2_window, value, initializing_qm;
{
    Object old_value, temp;

    x_note_fn_call(115,151);
    old_value = get_lookup_slot_value_given_default(g2_window,
	    Qshow_operator_logbook_in_this_window_qm,T);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_window,
		Qshow_operator_logbook_in_this_window_qm);
    temp = set_lookup_slot_value_1(g2_window,
	    Qshow_operator_logbook_in_this_window_qm,value);
    if ( !TRUEP(initializing_qm)) {
	if ( !EQ(old_value,value)) {
	    if (value)
		show_logbook_in_g2_window(g2_window);
	    else
		hide_logbook_in_g2_window(g2_window);
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_14;  /* "none" */

/* WRITE-UNIX-TIME?-FROM-SLOT */
Object write_unix_time_qm_from_slot(unix_time_qm,gensymed_symbol)
    Object unix_time_qm, gensymed_symbol;
{
    x_note_fn_call(115,152);
    if (unix_time_qm)
	return twrite_unix_time(1,unix_time_qm);
    else
	return tformat(1,string_constant_14);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_8;    /* # */

static Object Qminute;             /* minute */

static Object Qhour;               /* hour */

static Object Qdate;               /* date */

static Object Qmonth;              /* month */

static Object Qyear;               /* year */

static Object Qnone;               /* none */

/* UNIX-TIME?-EVALUATION-GETTER */
Object unix_time_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, evaluation_structure_slot_new_value;
    Object evaluation_structure_slot_new_value_1;
    Object evaluation_structure_slot_new_value_2;
    Object evaluation_structure_slot_new_value_3;
    Object evaluation_structure_slot_new_value_4;
    Object evaluation_structure_slot_new_value_5;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    double gensym_float_unix_time, arg, arg_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(115,153);
    if (slot_value) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    gensym_float_unix_time = DFLOAT_ISAREF_1(slot_value,(SI_Long)0L);
	    arg = gensym_float_unix_time;
	    arg_1 = -2.147483648E+9;
	    temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = gensym_float_unix_time;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(N_2_to_31_plus_62_years);
		temp = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Bad_phrase;
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
			  twrite_beginning_of_wide_string(array_constant_8,
				  FIX((SI_Long)26L));
			  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		gensymed_symbol = allocate_evaluation_structure(Nil);
		result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(gensym_float_unix_time));
		MVS_6(result,evaluation_structure_slot_new_value,
			evaluation_structure_slot_new_value_1,
			evaluation_structure_slot_new_value_2,
			evaluation_structure_slot_new_value_3,
			evaluation_structure_slot_new_value_4,
			evaluation_structure_slot_new_value_5);
		set_evaluation_structure_slot(gensymed_symbol,Qsecond,
			evaluation_structure_slot_new_value);
		set_evaluation_structure_slot(gensymed_symbol,Qminute,
			evaluation_structure_slot_new_value_1);
		set_evaluation_structure_slot(gensymed_symbol,Qhour,
			evaluation_structure_slot_new_value_2);
		set_evaluation_structure_slot(gensymed_symbol,Qdate,
			evaluation_structure_slot_new_value_3);
		set_evaluation_structure_slot(gensymed_symbol,Qmonth,
			evaluation_structure_slot_new_value_4);
		set_evaluation_structure_slot(gensymed_symbol,Qyear,
			evaluation_structure_slot_new_value_5);
		temp_1 = gensymed_symbol;
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp_1 = Qnone;
    GENSYM_RETURN_ONE(temp_1);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object Qreserved_word_p;    /* reserved-word-p */

static Object string_constant_15;  /* " ~s is a reserved-symbol" */

/* UNRESERVED-SYMBOL-EVALUATION-SETTER */
Object unreserved_symbol_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(115,154);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_unreserved_symbol_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(evaluation_value),
	    Qreserved_word_p)) {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_15,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
    else
	result = VALUES_1(evaluation_value);
  end_unreserved_symbol_evaluation_setter:
    return result;
}

/* UNRESERVED-SYMBOL-EVALUATION-GETTER */
Object unreserved_symbol_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(115,155);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* LANGUAGE?-EVALUATION-SETTER */
Object language_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(115,156);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_6))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_7,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_language_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
  end_language_qm_evaluation_setter:
    return result;
}

/* LANGUAGE?-EVALUATION-GETTER */
Object language_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(115,157);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-LANGUAGE?-FOR-SLOT */
Object compile_language_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(115,158);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-LANGUAGE?-FROM-SLOT */
Object write_language_qm_from_slot(language_qm,gensymed_symbol)
    Object language_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(115,159);
    temp = language_qm;
    if (temp);
    else
	temp = Qnone;
    return twrite(temp);
}

static Object Qspecific_language_for_this_g2_window_qm;  /* specific-language-for-this-g2-window? */

static Object Qlanguage;           /* language */

static Object Qui_client_specific_language;  /* ui-client-specific-language */

/* PUT-SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW? */
Object put_specific_language_for_this_g2_window_qm(g2_window,language_qm,
	    initializing_p)
    Object g2_window, language_qm, initializing_p;
{
    Object workstation_for_g2_window_qm;
    char changed;

    x_note_fn_call(115,160);
    add_or_delete_as_language_contributor(g2_window,
	    get_lookup_slot_value_given_default(g2_window,
	    Qspecific_language_for_this_g2_window_qm,Nil),T);
    add_or_delete_as_language_contributor(g2_window,language_qm,Nil);
    changed =  !EQ(get_lookup_slot_value_given_default(g2_window,
	    Qspecific_language_for_this_g2_window_qm,Nil),language_qm);
    set_non_savable_lookup_slot_value(g2_window,
	    Qspecific_language_for_this_g2_window_qm,language_qm);
    if ( !TRUEP(initializing_p)) {
	workstation_for_g2_window_qm = ISVREF(g2_window,(SI_Long)20L);
	if (workstation_for_g2_window_qm) {
	    SVREF(workstation_for_g2_window_qm,FIX((SI_Long)27L)) = 
		    language_qm;
	    if (changed)
		decache_dynamic_menus(2,Qlanguage,
			workstation_for_g2_window_qm);
	}
	update_subscriptions_from_virtual_attribute_change(g2_window,
		get_property_value_function(3,
		get_symbol_properties_function(Qui_client_specific_language),
		Qvirtual_attribute,Nil),Nil);
    }
    return VALUES_1(language_qm);
}

static Object Qg2_window_style;    /* g2-window-style */

/* PUT-G2-WINDOW-STYLE */
Object put_g2_window_style(g2_window,value,initializing_p)
    Object g2_window, value, initializing_p;
{
    Object workstation_for_g2_window_qm;

    x_note_fn_call(115,161);
    set_non_savable_lookup_slot_value(g2_window,Qg2_window_style,value);
    if ( !TRUEP(initializing_p)) {
	workstation_for_g2_window_qm = ISVREF(g2_window,(SI_Long)20L);
	if (workstation_for_g2_window_qm)
	    SVREF(workstation_for_g2_window_qm,FIX((SI_Long)50L)) = value;
    }
    return VALUES_1(value);
}

/* GET-I-AM-ALIVE-INFO-FOR-G2-WINDOW-IF-ANY */
Object get_i_am_alive_info_for_g2_window_if_any(g2_window)
    Object g2_window;
{
    Object icp_socket_qm;

    x_note_fn_call(115,162);
    icp_socket_qm = get_icp_socket_for_g2_window(g2_window);
    if (icp_socket_qm)
	return VALUES_1(ISVREF(icp_socket_qm,(SI_Long)24L));
    else
	return VALUES_1(Nil);
}

/* GET-ICP-SOCKET-FOR-G2-WINDOW */
Object get_icp_socket_for_g2_window(g2_window)
    Object g2_window;
{
    Object workstation_qm, icp_output_port_qm;

    x_note_fn_call(115,163);
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    icp_output_port_qm = workstation_qm ? ISVREF(ISVREF(workstation_qm,
	    (SI_Long)1L),(SI_Long)12L) : Nil;
    if (icp_output_port_qm)
	return VALUES_1(ISVREF(icp_output_port_qm,(SI_Long)2L));
    else
	return VALUES_1(Nil);
}

/* GET-GENSYM-WINDOW-FOR-G2-WINDOW */
Object get_gensym_window_for_g2_window(g2_window)
    Object g2_window;
{
    Object workstation_qm;

    x_note_fn_call(115,164);
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    if (workstation_qm)
	return VALUES_1(ISVREF(workstation_qm,(SI_Long)1L));
    else
	return VALUES_1(Nil);
}

static Object Qg2_window;          /* g2-window */

/* GET-G2-WINDOW-GIVEN-ICP-SOCKET */
Object get_g2_window_given_icp_socket(icp_socket)
    Object icp_socket;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_window;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(115,165);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_window = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      if (EQ(icp_socket,get_icp_socket_for_g2_window(g2_window))) {
	  result = VALUES_1(g2_window);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object string_constant_16;  /* "~A~%" */

/* PRINT-SCHEDULE-TO-STRING */
Object print_schedule_to_string(current_only_p)
    Object current_only_p;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object lines, line, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(115,166);
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
	      lines = print_schedule_to_string_list(current_only_p);
	      line = Nil;
	      ab_loop_list_ = lines;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      line = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      tformat(2,string_constant_16,line);
	      reclaim_text_string(line);
	      goto next_loop;
	    end_loop:
	      reclaim_gensym_list_1(lines);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* PRINT-SCHEDULE-TO-FILE */
Object print_schedule_to_file(file_name,current_only_p)
    Object file_name, current_only_p;
{
    Object stream, lines, line, ab_loop_list_, temp;

    x_note_fn_call(115,167);
    stream = g2_stream_open_for_output(file_name);
    if (stream) {
	lines = print_schedule_to_string_list(current_only_p);
	line = Nil;
	ab_loop_list_ = lines;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	line = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(write_text_string_to_stream(line,stream)))
	    goto end_loop;
	if ( !TRUEP(g2_stream_terpri(stream)))
	    goto end_loop;
	goto next_loop;
      end_loop:;
	line = Nil;
	ab_loop_list_ = lines;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	line = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_text_string(line);
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(lines);
	temp = g2_stream_close(stream);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* PRINT-SCHEDULE */
Object print_schedule()
{
    Object lines, line, ab_loop_list_, temp;

    x_note_fn_call(115,168);
    lines = print_schedule_to_string_list(Nil);
    line = Nil;
    ab_loop_list_ = lines;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    notify_user_at_console(2,string_constant_16,line);
    goto next_loop;
  end_loop:;
    line = Nil;
    ab_loop_list_ = lines;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    line = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(line);
    goto next_loop_1;
  end_loop_1:;
    temp = reclaim_gensym_list_1(lines);
    return VALUES_1(temp);
}

static Object Qtemporary_workspace;  /* temporary-workspace */

/* PRINT-SCHEDULE-ON-TEMPORARY-WORKSPACE */
Object print_schedule_on_temporary_workspace(current_only_p)
    Object current_only_p;
{
    Object box, temp;

    x_note_fn_call(115,169);
    box = make_description_box(print_schedule_to_string(current_only_p));
    temp = make_workspace(6,Qtemporary_workspace,Nil,box,FIX((SI_Long)50L),
	    Nil,Nil);
    return put_workspace_on_pane_function(temp,
	    Current_workstation_detail_pane,Qleft,Qtop,T,FIX((SI_Long)11L),
	    Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* G2-SHOW-SCHEDULE */
Object g2_show_schedule(g2_window_or_file_name,current_only_p)
    Object g2_window_or_file_name, current_only_p;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(115,170);
    SAVE_STACK();
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(g2_window_or_file_name) != 
	    (SI_Long)0L) {
	print_schedule_to_file(g2_window_or_file_name,
		evaluation_truth_value_is_true_p(current_only_p));
	reclaim_text_string(g2_window_or_file_name);
    }
    else {
	if (SIMPLE_VECTOR_P(g2_window_or_file_name) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window_or_file_name)) > 
		(SI_Long)2L &&  !EQ(ISVREF(g2_window_or_file_name,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(g2_window_or_file_name,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = ISVREF(g2_window_or_file_name,
			(SI_Long)20L);
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
					print_schedule_on_temporary_workspace(evaluation_truth_value_is_true_p(current_only_p));
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
    }
    if ( !(EQ(current_only_p,Evaluation_true_value) || EQ(current_only_p,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(current_only_p);
    RESTORE_STACK();
    return VALUES_1(Nil);
}

/* G2-DO-ABORT-WORKSPACE */
Object g2_do_abort_workspace()
{
    x_note_fn_call(115,171);
    return internal_error_given_format_info(Gensym_error_format_string,
	    Gensym_error_argument_list,Gensym_error_sure_of_format_info_p);
}

/* G2-CAUSE-SYNCHRONOUS-ABORT */
Object g2_cause_synchronous_abort()
{
    x_note_fn_call(115,172);
    return error((SI_Long)1L,"Called the wrong system procedure");
}

DEFINE_VARIABLE_WITH_SYMBOL(Intentionally_bogus_vector_for_g2_cause_asynchronous_abort, Qintentionally_bogus_vector_for_g2_cause_asynchronous_abort);

/* G2-CAUSE-ASYNCHRONOUS-ABORT */
Object g2_cause_asynchronous_abort()
{
    x_note_fn_call(115,173);
    return VALUES_1(ISVREF(Intentionally_bogus_vector_for_g2_cause_asynchronous_abort,
	    (SI_Long)14L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_ui_client_session, Qcurrent_ui_client_session);

/* PUT-UI-CLIENT-SESSION-USER-MODE */
Object put_ui_client_session_user_mode(ui_client_session,value,initializing_p)
    Object ui_client_session, value, initializing_p;
{
    x_note_fn_call(115,174);
    ISVREF(ui_client_session,(SI_Long)20L) = value;
    if ( !TRUEP(initializing_p))
	update_subscriptions_from_virtual_attribute_change(ui_client_session,
		get_property_value_function(3,
		get_symbol_properties_function(Qui_client_user_mode),
		Qvirtual_attribute,Nil),Nil);
    return VALUES_1(value);
}

static Object Qspecific_language_for_this_ui_client_session_qm;  /* specific-language-for-this-ui-client-session? */

/* PUT-SPECIFIC-LANGUAGE-FOR-THIS-UI-CLIENT-SESSION? */
Object put_specific_language_for_this_ui_client_session_qm(ui_client_session,
	    value,initializing_p)
    Object ui_client_session, value, initializing_p;
{
    x_note_fn_call(115,175);
    set_non_savable_lookup_slot_value(ui_client_session,
	    Qspecific_language_for_this_ui_client_session_qm,value);
    if ( !TRUEP(initializing_p))
	return update_subscriptions_from_virtual_attribute_change(ui_client_session,
		get_property_value_function(3,
		get_symbol_properties_function(Qui_client_specific_language),
		Qvirtual_attribute,Nil),Nil);
    else
	return VALUES_1(Nil);
}

void workstation_INIT()
{
    Object temp, reclaim_structure_for_workstation_event_1;
    Object named_dynamic_extent_description, temp_1, cdddr_new_value;
    Object valid_workstation_context_p_for_workstation_context_frame_1;
    Object valid_workstation_context_p_for_workstation_context_with_selection_focus_1;
    Object temp_2, alignment_grid_evaluation_setter_1;
    Object alignment_grid_evaluation_getter_1;
    Object write_drawing_parameters_image_incomplete_note_1;
    Object track_mouse_into_spot_for_spot_1, unix_time_qm_evaluation_getter_1;
    Object unreserved_symbol_evaluation_setter_1;
    Object unreserved_symbol_evaluation_getter_1;
    Object language_qm_evaluation_setter_1, language_qm_evaluation_getter_1;
    Object gensymed_symbol;
    Object Qslot_putter, Qput_specific_language_for_this_ui_client_session_qm;
    Object AB_package, Qput_ui_client_session_user_mode;
    Object Qui_client_session_user_mode, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object list_constant_61, Qui_client_session, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, list_constant_60, Qobject;
    Object Qui_client_item, Qg2_cause_asynchronous_abort;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_cause_synchronous_abort, Qg2_do_abort_workspace;
    Object Qg2_show_schedule, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object string_constant_74, list_constant_59, Qnetwork_wire;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object Qconnection, Qput_g2_window_style;
    Object Qput_specific_language_for_this_g2_window_qm, Qslot_value_writer;
    Object Qwrite_language_qm_from_slot, Qlanguage_qm;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_language_qm_for_slot, Qnamed;
    Object list_constant_29, Qab_or, list_constant_58;
    Object Qtype_specification_simple_expansion, string_constant_70;
    Object Qg2_window_reroute_problem_report;
    Object Qg2_window_reroute_problem_report_qm;
    Object Qg2_window_initial_window_configuration_string;
    Object Qg2_window_initial_window_configuration_string_qm;
    Object Qg2_window_time_of_last_connection;
    Object Qg2_window_time_of_last_connection_qm;
    Object Qg2_window_operating_system_type, Qg2_window_os_type_qm;
    Object Qg2_window_user_name_in_operating_system;
    Object Qg2_window_os_user_name_qm, Qg2_window_remote_host_name;
    Object Qg2_window_network_host_name_qm, Qg2_window_specific_language;
    Object Qunix_time_qm, list_constant_20, list_constant_57, list_constant_56;
    Object list_constant_55, list_constant_54, Qab_structure, list_constant_53;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_11, Qwrite_unix_time_qm_from_slot;
    Object Qput_show_operator_logbook_in_this_window_qm, Qput_g2_user_mode;
    Object Qwrite_g2_window_style_override_from_slot;
    Object Qg2_window_style_override;
    Object Qcompile_g2_window_style_override_for_slot;
    Object Qsubstitute_class_and_kb_flags, Qworkspace_view, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, list_constant_45;
    Object Qcreate_icon_description, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, Qg2_extension;
    Object Qput_g2_connection_status, Qsymbolic_parameter;
    Object Qg2_extension_parameter, Qabsent_slot_putter;
    Object Qput_g2_connection_request_where_slot_is_absent;
    Object Qg2_connection_request;
    Object Qput_control_request_for_g2_extension_where_slot_is_absent;
    Object Qcontrol_request_for_g2_extension, string_constant_50;
    Object list_constant_44, string_constant_49, string_constant_48;
    Object string_constant_47, Qget_scale_of_view, Qinitial_scale_of_view;
    Object list_constant_43, list_constant_36, Qscale_of_view;
    Object list_constant_42, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_38;
    Object Qvirtual_attributes_local_to_class, Qg2_workspace_view;
    Object Qget_workspace_of_view, Qinitial_workspace_of_view;
    Object list_constant_37, Qworkspace_of_view, list_constant_35, Qab_class;
    Object string_constant_46, list_constant_34, string_constant_43;
    Object string_constant_45, Qg2_native_view, string_constant_44;
    Object list_constant_33, string_constant_42, Qget_g2_window_of_view;
    Object Qinitial_g2_window_of_view, list_constant_32, list_constant_31;
    Object Qg2_window_of_view, list_constant_30, Qno_item;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_g2_native_window;
    Object string_constant_41, string_constant_40, list_constant_28;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, Qentity, Qitem, Qminimum_scheduling_interval_qm;
    Object Qcompile_minimum_scheduling_interval_qm_for_slot;
    Object Qwrite_minimum_scheduling_interval_qm_from_slot, string_constant_35;
    Object Qwrite_millisecond_sleep_interval_from_slot;
    Object Qmillisecond_sleep_interval;
    Object Qcompile_millisecond_sleep_interval_for_slot, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_21;
    Object list_constant_24, list_constant_23, list_constant_22, Quse, Qspot;
    Object Qtrack_mouse_into_spot, float_constant_1, float_constant;
    Object Qupdate_frame_status_and_notes;
    Object Qupdate_frame_status_and_notes_for_drawing_parameters;
    Object Qframe_note_writer_1;
    Object Qput_image_rendering_quality_where_slot_is_absent;
    Object Qimage_rendering_quality, Qwrite_image_palette_from_slot;
    Object Qput_image_palette, string_constant_34, string_constant_33;
    Object string_constant_32, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, list_constant_10, list_constant_13;
    Object list_constant_12, Qput_alignment_grid;
    Object Qwrite_alignment_grid_from_slot, string_constant_31;
    Object string_constant_30, string_constant_29, Qalignment_grid_option;
    Object Qalignment_grid_options, string_constant_28;
    Object Qtransform_alist_into_plist, string_constant_27, Qfine_dot;
    Object Qcoarse_dot, Qshort_dash, Qlong_dash, Qab_dot, Qdash, Qsolid;
    Object Qalignment_grid_default_line_pattern;
    Object Qalignment_grid_default_line_color, list_constant_9;
    Object Qalignment_grid_default_spacing, Qput_show_selection_handles;
    Object Qput_default_secondary_selection_color;
    Object Qput_default_primary_selection_color, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_drawing_parameters;
    Object Qinstall_system_table, Qinstall_system_table_for_drawing_parameters;
    Object Qput_drawing_transfer_mode_where_slot_is_absent;
    Object Qdrawing_transfer_mode, Qpainting, Qpaint;
    Object Qput_drawing_in_paint_mode_p, Qpaint_mode_qm;
    Object Qput_allow_scheduled_drawing_qm, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_drawing_parameters, Qinitialize;
    Object Qinitialize_for_drawing_parameters;
    Object Qput_drawing_priority_where_slot_is_absent, Qdrawing_priority;
    Object Qcleanup_for_drawing_parameters, Qsecondary_selection_color;
    Object Qprimary_selection_color, Ksystem_frame, string_constant_26;
    Object string_constant_25, list_constant_8;
    Object Qdefault_value_for_image_palette, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, Qsystem_table, Qclose_telewindows_callback;
    Object Qworkstation_context_with_selection_focus;
    Object Qvalid_workstation_context_p, Qworkstation_context_frame;
    Object Qtop_level_with_selection_focus_but_no_mouse_tracking_is_selection_style;
    Object Qtop_level_with_selection_focus_is_selection_style;
    Object Qtop_level_with_mouse_tracking_is_selection_style;
    Object Qnamed_dynamic_extent_description, Qunwind_qm, string_constant_19;
    Object Qworkstation_event, Qreclaim_structure;
    Object Qoutstanding_workstation_event_count;
    Object Qworkstation_event_structure_memory_usage, Qutilities2;
    Object string_constant_18, Qtype_description_of_type, string_constant_17;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;

    x_note_fn_call(115,176);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_workstation_event_g2_struct = 
	    STATIC_SYMBOL("WORKSTATION-EVENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qworkstation_event = STATIC_SYMBOL("WORKSTATION-EVENT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_event_g2_struct,
	    Qworkstation_event,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qworkstation_event,
	    Qg2_defstruct_structure_name_workstation_event_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workstation_event == UNBOUND)
	The_type_description_of_workstation_event = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83ogy1n83ogy8n8k1l8n0000001m1m83My83-BJy1n8y83-6Oy0kvk0k0");
    temp = The_type_description_of_workstation_event;
    The_type_description_of_workstation_event = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_workstation_event_g2_struct,
	    The_type_description_of_workstation_event,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qworkstation_event,
	    The_type_description_of_workstation_event,
	    Qtype_description_of_type);
    Qoutstanding_workstation_event_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSTATION-EVENT-COUNT",AB_package);
    Qworkstation_event_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSTATION-EVENT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83ogy8s83-xey09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workstation_event_count);
    push_optimized_constant(Qworkstation_event_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_workstation_events = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSTATION-EVENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workstation_events,
	    Chain_of_available_workstation_events);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_workstation_events,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qworkstation_event_count = STATIC_SYMBOL("WORKSTATION-EVENT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_event_count,
	    Workstation_event_count);
    record_system_variable(Qworkstation_event_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workstation_events_vector == UNBOUND)
	Chain_of_available_workstation_events_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkstation_event_structure_memory_usage,
	    STATIC_FUNCTION(workstation_event_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workstation_event_count,
	    STATIC_FUNCTION(outstanding_workstation_event_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_workstation_event_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workstation_event,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qworkstation_event,
	    reclaim_structure_for_workstation_event_1);
    string_constant_19 = STATIC_STRING("SERVICING-WORKSTATION-EVENT");
    if (Servicing_workstation_event == UNBOUND)
	Servicing_workstation_event = make_recursive_lock(2,Kname,
		string_constant_19);
    Qservicing_workstation_event = 
	    STATIC_SYMBOL("SERVICING-WORKSTATION-EVENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qservicing_workstation_event,
	    Servicing_workstation_event);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    Qunwind_qm = STATIC_SYMBOL("UNWIND\?",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qservicing_workstation_event,
	    Qworkstation,Nil,Qnil,Qnil,Qnil,Nil);
    temp_1 = CDDDR(named_dynamic_extent_description);
    cdddr_new_value = set_getf(CDDDR(temp_1),Qunwind_qm,T);
    M_CDDDR(temp_1) = cdddr_new_value;
    mutate_global_property(Qservicing_workstation_event,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qunknown_is_selection_style = 
	    STATIC_SYMBOL("UNKNOWN-IS-SELECTION-STYLE",AB_package);
    Qtop_level_with_mouse_tracking_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    Qtop_level_with_selection_focus_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-SELECTION-FOCUS-IS-SELECTION-STYLE",
	    AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qtop_level_with_selection_focus_is_selection_style);
    Qtop_level_with_selection_focus_but_no_mouse_tracking_is_selection_style 
	    = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-SELECTION-FOCUS-BUT-NO-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,
	    Qtop_level_with_selection_focus_is_selection_style,
	    Qtop_level_with_selection_focus_but_no_mouse_tracking_is_selection_style);
    Qcurrent_workstation_window = 
	    STATIC_SYMBOL("CURRENT-WORKSTATION-WINDOW",AB_package);
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    Qworkstation_context_frame = STATIC_SYMBOL("WORKSTATION-CONTEXT-FRAME",
	    AB_package);
    valid_workstation_context_p_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qworkstation_context_frame,
	    valid_workstation_context_p_for_workstation_context_frame_1);
    Qworkstation_context_with_selection_focus = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS",
	    AB_package);
    valid_workstation_context_p_for_workstation_context_with_selection_focus_1 
	    = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_workstation_context_with_selection_focus,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qworkstation_context_with_selection_focus,
	    valid_workstation_context_p_for_workstation_context_with_selection_focus_1);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qclose_telewindows_callback = 
	    STATIC_SYMBOL("CLOSE-TELEWINDOWS-CALLBACK",AB_package);
    SET_SYMBOL_FUNCTION(Qclose_telewindows_callback,
	    STATIC_FUNCTION(close_telewindows_callback,NIL,FALSE,2,2));
    Qdrawing_parameters = STATIC_SYMBOL("DRAWING-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_8 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qdrawing_parameters,list_constant_8);
    string_constant_20 = STATIC_STRING("1l1l83ey");
    Qdefault_value_for_image_palette = 
	    STATIC_SYMBOL("DEFAULT-VALUE-FOR-IMAGE-PALETTE",AB_package);
    SET_SYMBOL_FUNCTION(Qdefault_value_for_image_palette,
	    STATIC_FUNCTION(default_value_for_image_palette,NIL,FALSE,0,0));
    string_constant_21 = 
	    STATIC_STRING("1r4z8r83Gay83Gay83KAy83KAy08k001o1l8o1l8l1l83Cy1m8p83Ky000004z8r83K9y83K9y83KAy83KAy08k001o1l8o1l8l1l83Cy1m8p83Ky000004z8r83Cny8");
    string_constant_22 = 
	    STATIC_STRING("3Cny83KAy83KAy01m8w9k001o1l8o1l8l1l83Cy1m8p83Cny000004z8r83a-y83a-y83KAy83KAy08k001m1l8l1m8p83Ky000004z8r83JGy83JGy83KAy83KAy083");
    string_constant_23 = 
	    STATIC_STRING("9+y001n1l8l1l8o1m8p83*uy000004z8r83JJy83JJy83KAy83KAy0839+y001n1l8l1l8o1m8p83*uy000004z8r83Aey83Aey83KAy83KAy00001m1l8l1m8p83Aey");
    string_constant_24 = STATIC_STRING("00000");
    string_constant_25 = 
	    STATIC_STRING("1t8q1n83KAy1l83-sy83ey1q83Gay8k1l8o1l8l1l83Cy1m8p83Ky1q83K9y8k1l8o1l8l1l83Cy1m8p83Ky1q83Cny1m8w9k1l8o1l8l1l83Cy1m8p83Cny1n83a-y8");
    string_constant_26 = 
	    STATIC_STRING("k1m8p83Ky1o83JGy839+y1l8o1m8p83*uy1o83JJy839+y1l8o1m8p83*uy1n83Aey01m8p83Aey");
    temp = regenerate_optimized_constant(string_constant_20);
    clear_optimized_constants();
    push_optimized_constant(Qdefault_value_for_image_palette);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24));
    clear_optimized_constants();
    push_optimized_constant(Qdefault_value_for_image_palette);
    add_class_to_environment(9,Qdrawing_parameters,list_constant_8,Nil,
	    temp,Nil,temp_2,list_constant_8,
	    regenerate_optimized_constant(LIST_2(string_constant_25,
	    string_constant_26)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qdrawing_parameters,Drawing_parameters);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qdrawing_parameters,Qworkstation,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qdefault_primary_selection_color = 
	    STATIC_SYMBOL("DEFAULT-PRIMARY-SELECTION-COLOR",AB_package);
    Qprimary_selection_color = STATIC_SYMBOL("PRIMARY-SELECTION-COLOR",
	    AB_package);
    alias_slot_name(3,Qdefault_primary_selection_color,
	    Qprimary_selection_color,Qdrawing_parameters);
    Qdefault_secondary_selection_color = 
	    STATIC_SYMBOL("DEFAULT-SECONDARY-SELECTION-COLOR",AB_package);
    Qsecondary_selection_color = STATIC_SYMBOL("SECONDARY-SELECTION-COLOR",
	    AB_package);
    alias_slot_name(3,Qdefault_secondary_selection_color,
	    Qsecondary_selection_color,Qdrawing_parameters);
    Qimage_palette = STATIC_SYMBOL("IMAGE-PALETTE",AB_package);
    Qcleanup_for_drawing_parameters = 
	    STATIC_SYMBOL("CLEANUP-FOR-DRAWING-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_drawing_parameters,
	    STATIC_FUNCTION(cleanup_for_drawing_parameters,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcleanup_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qcleanup,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qcleanup,temp_1,Qclasses_which_define);
    Qdrawing_priority = STATIC_SYMBOL("DRAWING-PRIORITY",AB_package);
    Qput_drawing_priority_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-DRAWING-PRIORITY-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_drawing_priority_where_slot_is_absent,
	    STATIC_FUNCTION(put_drawing_priority_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qdrawing_priority,
	    SYMBOL_FUNCTION(Qput_drawing_priority_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitialize_for_drawing_parameters = 
	    STATIC_SYMBOL("INITIALIZE-FOR-DRAWING-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_drawing_parameters,
	    STATIC_FUNCTION(initialize_for_drawing_parameters,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qinitialize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qinitialize_after_reading_for_drawing_parameters = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-DRAWING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_drawing_parameters,
	    STATIC_FUNCTION(initialize_after_reading_for_drawing_parameters,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qdrawing_in_paint_mode_p = STATIC_SYMBOL("DRAWING-IN-PAINT-MODE-P",
	    AB_package);
    Qallow_scheduled_drawing_qm = 
	    STATIC_SYMBOL("ALLOW-SCHEDULED-DRAWING\?",AB_package);
    Qput_allow_scheduled_drawing_qm = 
	    STATIC_SYMBOL("PUT-ALLOW-SCHEDULED-DRAWING\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_allow_scheduled_drawing_qm,
	    STATIC_FUNCTION(put_allow_scheduled_drawing_qm,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qallow_scheduled_drawing_qm,
	    SYMBOL_FUNCTION(Qput_allow_scheduled_drawing_qm),Qslot_putter);
    Qpaint_mode_qm = STATIC_SYMBOL("PAINT-MODE\?",AB_package);
    alias_slot_name(3,Qdrawing_in_paint_mode_p,Qpaint_mode_qm,
	    Qdrawing_parameters);
    Qput_drawing_in_paint_mode_p = 
	    STATIC_SYMBOL("PUT-DRAWING-IN-PAINT-MODE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qput_drawing_in_paint_mode_p,
	    STATIC_FUNCTION(put_drawing_in_paint_mode_p,NIL,FALSE,3,3));
    mutate_global_property(Qdrawing_in_paint_mode_p,
	    SYMBOL_FUNCTION(Qput_drawing_in_paint_mode_p),Qslot_putter);
    Qpaint = STATIC_SYMBOL("PAINT",AB_package);
    Qpainting = STATIC_SYMBOL("PAINTING",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qpaint,Qpainting);
    Qdrawing_transfer_mode = STATIC_SYMBOL("DRAWING-TRANSFER-MODE",AB_package);
    Qput_drawing_transfer_mode_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-DRAWING-TRANSFER-MODE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_drawing_transfer_mode_where_slot_is_absent,
	    STATIC_FUNCTION(put_drawing_transfer_mode_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdrawing_transfer_mode,
	    SYMBOL_FUNCTION(Qput_drawing_transfer_mode_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qshow_selection_handles = STATIC_SYMBOL("SHOW-SELECTION-HANDLES",
	    AB_package);
    Qinstall_system_table_for_drawing_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-DRAWING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_drawing_parameters,
	    STATIC_FUNCTION(install_system_table_for_drawing_parameters,
	    NIL,FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinstall_system_table_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qinstall_system_table,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_1,Qclasses_which_define);
    Qdeinstall_system_table_for_drawing_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-DRAWING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_drawing_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_drawing_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qdeinstall_system_table,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_1,
	    Qclasses_which_define);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpropagate_allow_scheduled_drawing_1 = 
	    STATIC_SYMBOL("PROPAGATE-ALLOW-SCHEDULED-DRAWING-1",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    SET_SYMBOL_FUNCTION(Qpropagate_allow_scheduled_drawing_1,
	    STATIC_FUNCTION(propagate_allow_scheduled_drawing_1,NIL,FALSE,
	    1,1));
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qcurrent_drawing_transfer_mode = 
	    STATIC_SYMBOL("CURRENT-DRAWING-TRANSFER-MODE",AB_package);
    Qrefresh_window = STATIC_SYMBOL("REFRESH-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qrefresh_window,STATIC_FUNCTION(refresh_window,NIL,
	    FALSE,1,1));
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qput_default_primary_selection_color = 
	    STATIC_SYMBOL("PUT-DEFAULT-PRIMARY-SELECTION-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_primary_selection_color,
	    STATIC_FUNCTION(put_default_primary_selection_color,NIL,FALSE,
	    3,3));
    mutate_global_property(Qdefault_primary_selection_color,
	    SYMBOL_FUNCTION(Qput_default_primary_selection_color),
	    Qslot_putter);
    Qput_default_secondary_selection_color = 
	    STATIC_SYMBOL("PUT-DEFAULT-SECONDARY-SELECTION-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_secondary_selection_color,
	    STATIC_FUNCTION(put_default_secondary_selection_color,NIL,
	    FALSE,3,3));
    mutate_global_property(Qdefault_secondary_selection_color,
	    SYMBOL_FUNCTION(Qput_default_secondary_selection_color),
	    Qslot_putter);
    Qput_show_selection_handles = 
	    STATIC_SYMBOL("PUT-SHOW-SELECTION-HANDLES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_show_selection_handles,
	    STATIC_FUNCTION(put_show_selection_handles,NIL,FALSE,3,3));
    mutate_global_property(Qshow_selection_handles,
	    SYMBOL_FUNCTION(Qput_show_selection_handles),Qslot_putter);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    Qalignment_grid_default_spacing = 
	    STATIC_SYMBOL("ALIGNMENT-GRID-DEFAULT-SPACING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalignment_grid_default_spacing,
	    Alignment_grid_default_spacing);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)50L),FIX((SI_Long)50L));
    SET_SYMBOL_VALUE(Qalignment_grid_default_spacing,list_constant_9);
    Qalignment_grid_default_line_color = 
	    STATIC_SYMBOL("ALIGNMENT-GRID-DEFAULT-LINE-COLOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalignment_grid_default_line_color,
	    Alignment_grid_default_line_color);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    SET_SYMBOL_VALUE(Qalignment_grid_default_line_color,Qforeground);
    Qalignment_grid_default_line_pattern = 
	    STATIC_SYMBOL("ALIGNMENT-GRID-DEFAULT-LINE-PATTERN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qalignment_grid_default_line_pattern,
	    Alignment_grid_default_line_pattern);
    Qcoarse_dot = STATIC_SYMBOL("COARSE-DOT",AB_package);
    SET_SYMBOL_VALUE(Qalignment_grid_default_line_pattern,Qcoarse_dot);
    Qsolid = STATIC_SYMBOL("SOLID",AB_package);
    Qdash = STATIC_SYMBOL("DASH",AB_package);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    Qlong_dash = STATIC_SYMBOL("LONG-DASH",AB_package);
    Qshort_dash = STATIC_SYMBOL("SHORT-DASH",AB_package);
    Qfine_dot = STATIC_SYMBOL("FINE-DOT",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)8L,Qmember,Qsolid,Qdash,
	    Qab_dot,Qlong_dash,Qshort_dash,Qcoarse_dot,Qfine_dot);
    Stock_line_pattern_type = list_constant_10;
    Qtransform_alist_into_plist = 
	    STATIC_SYMBOL("TRANSFORM-ALIST-INTO-PLIST",AB_package);
    string_constant_27 = 
	    STATIC_STRING("1m1n83Aey83f3y1m83-qNyl1o83Aey1n83f3y1m9k83vy83-JQy2l2l83-qNyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qtransform_alist_into_plist);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    SET_SYMBOL_FUNCTION(Qtransform_alist_into_plist,
	    STATIC_FUNCTION(transform_alist_into_plist,NIL,FALSE,1,1));
    string_constant_28 = 
	    STATIC_STRING("1m1n83f3y83-ey2lll1n83f3y1p1m9k83-9y83-ey1m9k83vy83-ey1m9k83-Ay2lmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    Qalignment_grid_options = STATIC_SYMBOL("ALIGNMENT-GRID-OPTIONS",
	    AB_package);
    Qalignment_grid_option = STATIC_SYMBOL("ALIGNMENT-GRID-OPTION",AB_package);
    add_grammar_rules_for_list(5,Qalignment_grid_options,
	    Qalignment_grid_option,Qnil,Qnil,Qnil);
    string_constant_29 = 
	    STATIC_STRING("1n1n83-JPy1o1m9k83kUy1m9k83*xy1m9k83-Py83*uy2l83Tvyo1n83-JPy1o1m9k83kUy1m9k83-8ly1m9k83-Py83pby2l839Iyo1n83-JPy1n1m9k83-DHy1m9k8");
    string_constant_30 = STATIC_STRING("3=3y83f3y2l83-q7yn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_29,
	    string_constant_30)));
    string_constant_31 = STATIC_STRING("1m1m83pby1m9k83-DOy1m83pby83gCy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_31));
    Qspacing = STATIC_SYMBOL("SPACING",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qsnap_to = STATIC_SYMBOL("SNAP-TO",AB_package);
    string_constant = STATIC_STRING(", line color: ~(~a~)");
    string_constant_1 = STATIC_STRING(", line pattern: ");
    string_constant_2 = STATIC_STRING(", snap to ");
    Qalignment_grid = STATIC_SYMBOL("ALIGNMENT-GRID",AB_package);
    Qwrite_alignment_grid_from_slot = 
	    STATIC_SYMBOL("WRITE-ALIGNMENT-GRID-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_alignment_grid_from_slot,
	    STATIC_FUNCTION(write_alignment_grid_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qalignment_grid,
	    SYMBOL_FUNCTION(Qwrite_alignment_grid_from_slot),
	    Qslot_value_writer);
    Qput_alignment_grid = STATIC_SYMBOL("PUT-ALIGNMENT-GRID",AB_package);
    SET_SYMBOL_FUNCTION(Qput_alignment_grid,
	    STATIC_FUNCTION(put_alignment_grid,NIL,FALSE,3,3));
    mutate_global_property(Qalignment_grid,
	    SYMBOL_FUNCTION(Qput_alignment_grid),Qslot_putter);
    string_constant_3 = STATIC_STRING("~d");
    string_constant_4 = STATIC_STRING("(~d,~d)");
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_11 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qalignment_grid),
	    Qtype_specification_simple_expansion,list_constant_11);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)4L,Qsequence,Qinteger,
	    FIX((SI_Long)2L),FIX((SI_Long)3L));
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_12);
    list_constant_14 = STATIC_CONS(list_constant_13,Qnil);
    list_constant_15 = STATIC_CONS(Qspacing,list_constant_14);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qline_color,Qsymbol);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qline_pattern,list_constant_10);
    list_constant_18 = STATIC_CONS(Qsnap_to,list_constant_14);
    list_constant_19 = STATIC_LIST((SI_Long)4L,list_constant_15,
	    list_constant_16,list_constant_17,list_constant_18);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_19);
    define_type_specification_explicit_complex_type(Qalignment_grid,
	    list_constant_4);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qalignment_grid);
    alignment_grid_evaluation_setter_1 = 
	    STATIC_FUNCTION(alignment_grid_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qalignment_grid,
	    alignment_grid_evaluation_setter_1);
    alignment_grid_evaluation_getter_1 = 
	    STATIC_FUNCTION(alignment_grid_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qalignment_grid,
	    alignment_grid_evaluation_getter_1);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qvisible_grid = STATIC_SYMBOL("VISIBLE-GRID",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    string_constant_32 = 
	    STATIC_STRING("1r1n83Cny1n1m9k83fy1m9k83-ty1m9k83*2y837ny1n83Cny1m1m9k837Ry1m9k83sKy83-qdy1n83Cny1m1m9k837Ry1m9k83--Xy83-qfy1n83Cny1m1m9k83-TSy");
    string_constant_33 = 
	    STATIC_STRING("1m9k83sKy83-TTy1n83Cny1m1m9k83-TSy1m9k83--Xy83-TUy1n83Cny1o1m9k83J2y1m9k83sKy1m9k832+y835Uy1m83-PXyo1n83Cny1o1m9k83J2y1m9k83--Xy");
    string_constant_34 = STATIC_STRING("1m9k832+y835Uy1m83-Payo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_32,
	    string_constant_33,string_constant_34)));
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qput_image_palette = STATIC_SYMBOL("PUT-IMAGE-PALETTE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_image_palette,
	    STATIC_FUNCTION(put_image_palette,NIL,FALSE,3,3));
    mutate_global_property(Qimage_palette,
	    SYMBOL_FUNCTION(Qput_image_palette),Qslot_putter);
    Qblack_and_white = STATIC_SYMBOL("BLACK-AND-WHITE",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qstandard_grays = STATIC_SYMBOL("STANDARD-GRAYS",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qstandard_colors = STATIC_SYMBOL("STANDARD-COLORS",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    Qextended_grays = STATIC_SYMBOL("EXTENDED-GRAYS",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    Qextended_colors = STATIC_SYMBOL("EXTENDED-COLORS",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    Qcustom_grays = STATIC_SYMBOL("CUSTOM-GRAYS",AB_package);
    string_constant_5 = STATIC_STRING("custom grays from ~(~a~)");
    Qcustom_colors = STATIC_SYMBOL("CUSTOM-COLORS",AB_package);
    string_constant_6 = STATIC_STRING("custom colors from ~(~a~)");
    Qwrite_image_palette_from_slot = 
	    STATIC_SYMBOL("WRITE-IMAGE-PALETTE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_image_palette_from_slot,
	    STATIC_FUNCTION(write_image_palette_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qimage_palette,
	    SYMBOL_FUNCTION(Qwrite_image_palette_from_slot),
	    Qslot_value_writer);
    Qstandard_gray = STATIC_SYMBOL("STANDARD-GRAY",AB_package);
    Qstandard_color = STATIC_SYMBOL("STANDARD-COLOR",AB_package);
    Qextended_gray = STATIC_SYMBOL("EXTENDED-GRAY",AB_package);
    Qextended_color = STATIC_SYMBOL("EXTENDED-COLOR",AB_package);
    Qcustom_color = STATIC_SYMBOL("CUSTOM-COLOR",AB_package);
    Qsome_image_name = STATIC_SYMBOL("SOME-IMAGE-NAME",AB_package);
    Qcustom_gray = STATIC_SYMBOL("CUSTOM-GRAY",AB_package);
    Qimage_rendering_quality = STATIC_SYMBOL("IMAGE-RENDERING-QUALITY",
	    AB_package);
    Qput_image_rendering_quality_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-IMAGE-RENDERING-QUALITY-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_image_rendering_quality_where_slot_is_absent,
	    STATIC_FUNCTION(put_image_rendering_quality_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qimage_rendering_quality,
	    SYMBOL_FUNCTION(Qput_image_rendering_quality_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qdrawing_parameters_image_incomplete = 
	    STATIC_SYMBOL("DRAWING-PARAMETERS-IMAGE-INCOMPLETE",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_7 = STATIC_STRING("the image ~(~a~) is incomplete");
    write_drawing_parameters_image_incomplete_note_1 = 
	    STATIC_FUNCTION(write_drawing_parameters_image_incomplete_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qdrawing_parameters_image_incomplete,
	    write_drawing_parameters_image_incomplete_note_1,
	    Qframe_note_writer_1);
    Qupdate_frame_status_and_notes_for_drawing_parameters = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES-FOR-DRAWING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_drawing_parameters,
	    STATIC_FUNCTION(update_frame_status_and_notes_for_drawing_parameters,
	    NIL,FALSE,1,1));
    Qupdate_frame_status_and_notes = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES",AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_drawing_parameters);
    set_get(Qdrawing_parameters,Qupdate_frame_status_and_notes,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_frame_status_and_notes),
	    Qclasses_which_define);
    temp_1 = CONS(Qdrawing_parameters,temp);
    mutate_global_property(Qupdate_frame_status_and_notes,temp_1,
	    Qclasses_which_define);
    Qchange_image_palette_of_window = 
	    STATIC_SYMBOL("CHANGE-IMAGE-PALETTE-OF-WINDOW",AB_package);
    Qflush_workstation = STATIC_SYMBOL("FLUSH-WORKSTATION",AB_package);
    SET_SYMBOL_FUNCTION(Qflush_workstation,
	    STATIC_FUNCTION(flush_workstation,NIL,FALSE,1,1));
    Qforce_process_drawing = STATIC_SYMBOL("FORCE-PROCESS-DRAWING",AB_package);
    SET_SYMBOL_FUNCTION(Qforce_process_drawing,
	    STATIC_FUNCTION(force_process_drawing,NIL,FALSE,0,0));
    Qsync_graphics_on_current_window = 
	    STATIC_SYMBOL("SYNC-GRAPHICS-ON-CURRENT-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qsync_graphics_on_current_window,
	    STATIC_FUNCTION(sync_graphics_on_current_window,NIL,FALSE,0,0));
    if (Trace_workstation_events == UNBOUND)
	Trace_workstation_events = Nil;
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qtw = STATIC_SYMBOL("TW",AB_package);
    string_constant_8 = STATIC_STRING("");
    Qtask_to_run_service_workstations_final = 
	    STATIC_SYMBOL("TASK-TO-RUN-SERVICE-WORKSTATIONS-FINAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_to_run_service_workstations_final,
	    Task_to_run_service_workstations_final);
    record_system_variable(Qtask_to_run_service_workstations_final,
	    Qworkstation,Nil,Qnil,Qnil,Qnil,Qnil);
    Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes = 
	    STATIC_SYMBOL("FUTURE-TASK-TO-RUN-PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    Future_task_to_run_propagate_all_workspace_changes_to_image_planes);
    record_system_variable(Qfuture_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    Qworkstation,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes = 
	    STATIC_SYMBOL("CURRENT-TASK-TO-RUN-PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    Current_task_to_run_propagate_all_workspace_changes_to_image_planes);
    record_system_variable(Qcurrent_task_to_run_propagate_all_workspace_changes_to_image_planes,
	    Qworkstation,Nil,Qnil,Qnil,Qnil,Qnil);
    float_constant = STATIC_FLOAT(1.0);
    Service_workstations_final_interval = float_constant;
    float_constant_1 = STATIC_FLOAT(0.1);
    Service_workstation_interval = float_constant_1;
    Qpropagate_all_workspace_changes_to_image_planes = 
	    STATIC_SYMBOL("PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES",
	    AB_package);
    Qservice_workstations_final = 
	    STATIC_SYMBOL("SERVICE-WORKSTATIONS-FINAL",AB_package);
    Qservice_workstation = STATIC_SYMBOL("SERVICE-WORKSTATION",AB_package);
    string_constant_9 = 
	    STATIC_STRING("[G2 internal warning] count-of-pending-workspace-drawing ended up non-zero after complete propagation! (= ~d)");
    SET_SYMBOL_FUNCTION(Qpropagate_all_workspace_changes_to_image_planes,
	    STATIC_FUNCTION(propagate_all_workspace_changes_to_image_planes,
	    NIL,FALSE,0,0));
    Normal_workstation_servicing_time_limit = 
	    fixnum_time_interval(FIX((SI_Long)50L));
    Prefer_interfaces_workstation_servicing_time_limit = 
	    fixnum_time_interval(FIX((SI_Long)200L));
    SET_SYMBOL_FUNCTION(Qservice_workstations_final,
	    STATIC_FUNCTION(service_workstations_final,NIL,FALSE,0,0));
    string_constant_10 = 
	    STATIC_STRING("An incomplete workstation was encountered ~\n      and ignored by G2.");
    Qservice_workstation_g2_init = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-G2-INIT",AB_package);
    Qlogged_out = STATIC_SYMBOL("LOGGED-OUT",AB_package);
    Qchanging_kbs = STATIC_SYMBOL("CHANGING-KBS",AB_package);
    Qlogging_in = STATIC_SYMBOL("LOGGING-IN",AB_package);
    Qservice_workstation_enter_login = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-ENTER-LOGIN",AB_package);
    Qreloading = STATIC_SYMBOL("RELOADING",AB_package);
    Qstarting = STATIC_SYMBOL("STARTING",AB_package);
    Qservice_workstation_launch_recompilation = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-LAUNCH-RECOMPILATION",
	    AB_package);
    Qservice_workstation_event = STATIC_SYMBOL("SERVICE-WORKSTATION-EVENT",
	    AB_package);
    Qservice_workstation_keep_refreshing_image = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-KEEP-REFRESHING-IMAGE",
	    AB_package);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    Qservice_workstation_handle_search_states = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-HANDLE-SEARCH-STATES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qservice_workstation,
	    STATIC_FUNCTION(service_workstation,NIL,FALSE,1,1));
    Qservice_workstation_enter_login_2 = 
	    STATIC_SYMBOL("SERVICE-WORKSTATION-ENTER-LOGIN-2",AB_package);
    Qtrack_mouse_into_spot = STATIC_SYMBOL("TRACK-MOUSE-INTO-SPOT",AB_package);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    track_mouse_into_spot_for_spot_1 = 
	    STATIC_FUNCTION(track_mouse_into_spot_for_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qtrack_mouse_into_spot,Qspot,
	    track_mouse_into_spot_for_spot_1);
    Qmillisecond_sleep_interval = 
	    STATIC_SYMBOL("MILLISECOND-SLEEP-INTERVAL",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qmillisecond_sleep_interval,
	    Qinteger);
    Quse = STATIC_SYMBOL("USE",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qquote,Quse);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    list_constant_21 = STATIC_CONS(Qdefault,Qnil);
    list_constant_23 = STATIC_CONS(Qquote,list_constant_21);
    list_constant_24 = STATIC_LIST((SI_Long)2L,list_constant_22,
	    list_constant_23);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,
	    Qmillisecond_sleep_interval,list_constant_24,list_constant_21);
    list_constant_27 = STATIC_LIST((SI_Long)2L,list_constant_25,
	    list_constant_26);
    add_grammar_rules_function(list_constant_27);
    string_constant_11 = 
	    STATIC_STRING("A millisecond sleep interval must be an integer from 0 through 1000.");
    Qcompile_millisecond_sleep_interval_for_slot = 
	    STATIC_SYMBOL("COMPILE-MILLISECOND-SLEEP-INTERVAL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_millisecond_sleep_interval_for_slot,
	    STATIC_FUNCTION(compile_millisecond_sleep_interval_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qmillisecond_sleep_interval,
	    SYMBOL_FUNCTION(Qcompile_millisecond_sleep_interval_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qmillisecond_sleep_interval,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_5 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_millisecond_sleep_interval_from_slot = 
	    STATIC_SYMBOL("WRITE-MILLISECOND-SLEEP-INTERVAL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_millisecond_sleep_interval_from_slot,
	    STATIC_FUNCTION(write_millisecond_sleep_interval_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmillisecond_sleep_interval,
	    SYMBOL_FUNCTION(Qwrite_millisecond_sleep_interval_from_slot),
	    Qslot_value_writer);
    string_constant_35 = STATIC_STRING("1m1m83Dny1m9k83gIy1m83Dny83lcy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_35));
    array_constant_6 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qminimum_scheduling_interval_qm = 
	    STATIC_SYMBOL("MINIMUM-SCHEDULING-INTERVAL\?",AB_package);
    Qwrite_minimum_scheduling_interval_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-MINIMUM-SCHEDULING-INTERVAL\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_minimum_scheduling_interval_qm_from_slot,
	    STATIC_FUNCTION(write_minimum_scheduling_interval_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qminimum_scheduling_interval_qm,
	    SYMBOL_FUNCTION(Qwrite_minimum_scheduling_interval_qm_from_slot),
	    Qslot_value_writer);
    Qcontinuous = STATIC_SYMBOL("CONTINUOUS",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    Qcompile_minimum_scheduling_interval_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-MINIMUM-SCHEDULING-INTERVAL\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_minimum_scheduling_interval_qm_for_slot,
	    STATIC_FUNCTION(compile_minimum_scheduling_interval_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qminimum_scheduling_interval_qm,
	    SYMBOL_FUNCTION(Qcompile_minimum_scheduling_interval_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qminimum_scheduling_interval_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_12 = 
	    STATIC_STRING("The interval must be less than or equal to 6 days.");
    string_constant_13 = STATIC_STRING("The interval must be greater than 0.");
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qg2_defstruct_structure_name_workspace_view_g2_struct = 
	    STATIC_SYMBOL("WORKSPACE-VIEW-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qcontrol_relative_coordinates = 
	    STATIC_SYMBOL("CONTROL-RELATIVE-COORDINATES",AB_package);
    Qg2_native_window = STATIC_SYMBOL("G2-NATIVE-WINDOW",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qg2_native_window,list_constant_28);
    string_constant_36 = STATIC_STRING("1n1m8v835Ky1l83Ly1l83Iy");
    string_constant_37 = 
	    STATIC_STRING("1q4z8r83WLy83WLy835Ky835Ky00001m1l8o1l8l000004z8r83WJy83WJy835Ky835Ky0k001p1l8l1m8p8360y1l83Fy1l8o1l83-4y000004z8r83WMy83WMy835K");
    string_constant_38 = 
	    STATIC_STRING("y835Ky0k001p1l8l1m8p8360y1l83Fy1l8o1l83-4y000004z8r83WNy83WNy835Ky835Ky0k001p1l8l1m8p8361y1l83Fy1l8o1l83-4y000004z8r83WIy83WIy83");
    string_constant_39 = 
	    STATIC_STRING("5Ky835Ky0k001p1l8l1m8p8361y1l83Fy1l8o1l83-4y000004z8r83WKy83WKy835Ky835Ky083E2y001p1l8l1m8p83-2y1l83Fy1l8o1l83-4y00000");
    string_constant_40 = 
	    STATIC_STRING("1s8q1p835Ky1m83Ry83-+y1m8v835Ky83Ly83Iy1o83WLy08o8l1q83WJyk1m8p8360y83Fy8o83-4y1q83WMyk1m8p8360y83Fy8o83-4y1q83WNyk1m8p8361y83Fy");
    string_constant_41 = 
	    STATIC_STRING("8o83-4y1q83WIyk1m8p8361y83Fy8o83-4y1q83WKy83E2y1m8p83-2y83Fy8o83-4y");
    temp = regenerate_optimized_constant(string_constant_36);
    temp_2 = regenerate_optimized_constant(LIST_3(string_constant_37,
	    string_constant_38,string_constant_39));
    add_class_to_environment(9,Qg2_native_window,list_constant_28,Nil,temp,
	    Nil,temp_2,list_constant_28,
	    regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_41)),Nil);
    Qcleanup_for_g2_native_window = 
	    STATIC_SYMBOL("CLEANUP-FOR-G2-NATIVE-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_g2_native_window,
	    STATIC_FUNCTION(cleanup_for_g2_native_window,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qcleanup_for_g2_native_window);
    set_get(Qg2_native_window,Qcleanup,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_1 = CONS(Qg2_native_window,temp);
    mutate_global_property(Qcleanup,temp_1,Qclasses_which_define);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qnative_window_left = STATIC_SYMBOL("NATIVE-WINDOW-LEFT",AB_package);
    Qnative_window_top = STATIC_SYMBOL("NATIVE-WINDOW-TOP",AB_package);
    Qnative_window_width = STATIC_SYMBOL("NATIVE-WINDOW-WIDTH",AB_package);
    Qnative_window_height = STATIC_SYMBOL("NATIVE-WINDOW-HEIGHT",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qnative_window_state = STATIC_SYMBOL("NATIVE-WINDOW-STATE",AB_package);
    Qg2_window_of_view = STATIC_SYMBOL("G2-WINDOW-OF-VIEW",AB_package);
    temp_1 = CONS(Qg2_window_of_view,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_native_window),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_1 = CONS(Qg2_window_of_view,temp);
    set_property_value_function(get_symbol_properties_function(Qg2_native_window),
	    Qvirtual_attributes_local_to_class,temp_1);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_native_window);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_29 = STATIC_CONS(Qno_item,Qnil);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_window);
    list_constant_32 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_30);
    Qinitial_g2_window_of_view = STATIC_SYMBOL("INITIAL-G2-WINDOW-OF-VIEW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_window_of_view,
	    STATIC_FUNCTION(initial_g2_window_of_view,NIL,FALSE,1,1));
    Qget_g2_window_of_view = STATIC_SYMBOL("GET-G2-WINDOW-OF-VIEW",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_window_of_view,
	    STATIC_FUNCTION(get_g2_window_of_view,NIL,FALSE,1,1));
    add_virtual_attribute(Qg2_window_of_view,list_constant_31,
	    list_constant_32,Qnil,
	    SYMBOL_FUNCTION(Qinitial_g2_window_of_view),
	    SYMBOL_FUNCTION(Qget_g2_window_of_view),Nil);
    Qg2_native_view = STATIC_SYMBOL("G2-NATIVE-VIEW",AB_package);
    list_constant_33 = STATIC_CONS(Qg2_native_window,Qnil);
    check_if_superior_classes_are_defined(Qg2_native_view,list_constant_33);
    string_constant_42 = STATIC_STRING("1m1l83Ly1l83Iy");
    string_constant_43 = STATIC_STRING("0");
    string_constant_44 = STATIC_STRING("1m8q1o831Gy1l835Ky83Ly83Iy");
    temp = regenerate_optimized_constant(string_constant_42);
    temp_2 = regenerate_optimized_constant(string_constant_43);
    add_class_to_environment(9,Qg2_native_view,list_constant_33,Nil,temp,
	    Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(string_constant_44),Nil);
    Qg2_workspace_view = STATIC_SYMBOL("G2-WORKSPACE-VIEW",AB_package);
    list_constant_34 = STATIC_CONS(Qg2_native_view,Qnil);
    check_if_superior_classes_are_defined(Qg2_workspace_view,list_constant_34);
    string_constant_45 = STATIC_STRING("1n1m8v83Nmy1l83Ly1l83Iy");
    string_constant_46 = STATIC_STRING("1m8q1p83Nmy1l831Gy1m8v83Nmy83Ly83Iy");
    temp = regenerate_optimized_constant(string_constant_45);
    temp_2 = regenerate_optimized_constant(string_constant_43);
    add_class_to_environment(9,Qg2_workspace_view,list_constant_34,Nil,
	    temp,Nil,temp_2,list_constant_34,
	    regenerate_optimized_constant(string_constant_46),Nil);
    Qworkspace_of_view = STATIC_SYMBOL("WORKSPACE-OF-VIEW",AB_package);
    temp_1 = CONS(Qworkspace_of_view,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_workspace_view),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_1 = CONS(Qworkspace_of_view,temp);
    set_property_value_function(get_symbol_properties_function(Qg2_workspace_view),
	    Qvirtual_attributes_local_to_class,temp_1);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_workspace_view);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_35);
    Qinitial_workspace_of_view = STATIC_SYMBOL("INITIAL-WORKSPACE-OF-VIEW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_workspace_of_view,
	    STATIC_FUNCTION(initial_workspace_of_view,NIL,FALSE,1,1));
    Qget_workspace_of_view = STATIC_SYMBOL("GET-WORKSPACE-OF-VIEW",AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_of_view,
	    STATIC_FUNCTION(get_workspace_of_view,NIL,FALSE,1,1));
    add_virtual_attribute(Qworkspace_of_view,list_constant_36,
	    list_constant_37,Qnil,
	    SYMBOL_FUNCTION(Qinitial_workspace_of_view),
	    SYMBOL_FUNCTION(Qget_workspace_of_view),Nil);
    Qscale_of_view = STATIC_SYMBOL("SCALE-OF-VIEW",AB_package);
    temp_1 = CONS(Qscale_of_view,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_workspace_view),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_1 = CONS(Qscale_of_view,temp);
    set_property_value_function(get_symbol_properties_function(Qg2_workspace_view),
	    Qvirtual_attributes_local_to_class,temp_1);
    Qx_scale = STATIC_SYMBOL("X-SCALE",AB_package);
    Qy_scale = STATIC_SYMBOL("Y-SCALE",AB_package);
    list_constant_38 = STATIC_CONS(Qfloat,Qnil);
    list_constant_39 = STATIC_CONS(Qx_scale,list_constant_38);
    list_constant_40 = STATIC_CONS(Qy_scale,list_constant_38);
    list_constant_41 = STATIC_LIST((SI_Long)2L,list_constant_39,
	    list_constant_40);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_41);
    list_constant_43 = STATIC_LIST((SI_Long)3L,Qab_or,Qfloat,list_constant_42);
    Qinitial_scale_of_view = STATIC_SYMBOL("INITIAL-SCALE-OF-VIEW",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_scale_of_view,
	    STATIC_FUNCTION(initial_scale_of_view,NIL,FALSE,1,1));
    Qget_scale_of_view = STATIC_SYMBOL("GET-SCALE-OF-VIEW",AB_package);
    SET_SYMBOL_FUNCTION(Qget_scale_of_view,
	    STATIC_FUNCTION(get_scale_of_view,NIL,FALSE,1,1));
    add_virtual_attribute(Qscale_of_view,list_constant_36,list_constant_43,
	    Qnil,SYMBOL_FUNCTION(Qinitial_scale_of_view),
	    SYMBOL_FUNCTION(Qget_scale_of_view),Nil);
    Qg2_extension = STATIC_SYMBOL("G2-EXTENSION",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_44 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qg2_extension,list_constant_44);
    string_constant_47 = STATIC_STRING("1p1m8v835Hy1l8t1l83Iy1l83Ly1l83-8y");
    string_constant_48 = 
	    STATIC_STRING("1n4z8r83NWy83NWy835Hy835Hy00001o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Mby83Mby835Hy835Hy083Iiy001o1l8l1l83Fy1m8p83*iy1l83Hy000004z");
    string_constant_49 = 
	    STATIC_STRING("8r83NMy83NMy835Hy835Hy00001o1l8l1l83Fy1m8p83*iy1l83Hy00000");
    string_constant_50 = 
	    STATIC_STRING("1p8q1r835Hy1l83-Oy1m8v835Hy8t83Iy83Ly83-8y1p83NWy083Fy1m8p83*iy83Hy1p83Mby83Iiy83Fy1m8p83*iy83Hy1p83NMy083Fy1m8p83*iy83Hy");
    temp = regenerate_optimized_constant(string_constant_47);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_48,
	    string_constant_49));
    add_class_to_environment(9,Qg2_extension,list_constant_44,Nil,temp,Nil,
	    temp_2,list_constant_44,
	    regenerate_optimized_constant(string_constant_50),Nil);
    Qcontrol_request_for_g2_extension = 
	    STATIC_SYMBOL("CONTROL-REQUEST-FOR-G2-EXTENSION",AB_package);
    Qput_control_request_for_g2_extension_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONTROL-REQUEST-FOR-G2-EXTENSION-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_control_request_for_g2_extension_where_slot_is_absent,
	    STATIC_FUNCTION(put_control_request_for_g2_extension_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcontrol_request_for_g2_extension,
	    SYMBOL_FUNCTION(Qput_control_request_for_g2_extension_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qg2_connection_request = STATIC_SYMBOL("G2-CONNECTION-REQUEST",AB_package);
    Qput_g2_connection_request_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-G2-CONNECTION-REQUEST-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_connection_request_where_slot_is_absent,
	    STATIC_FUNCTION(put_g2_connection_request_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_connection_request,
	    SYMBOL_FUNCTION(Qput_g2_connection_request_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qg2_extension_parameter = STATIC_SYMBOL("G2-EXTENSION-PARAMETER",
	    AB_package);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qg2_extension_parameter,
	    CONS(Qsymbolic_parameter,temp),Qsubstitute_class_and_kb_flags);
    Qg2_connection_status = STATIC_SYMBOL("G2-CONNECTION-STATUS",AB_package);
    Qui_client_connection_status = 
	    STATIC_SYMBOL("UI-CLIENT-CONNECTION-STATUS",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qput_g2_connection_status = STATIC_SYMBOL("PUT-G2-CONNECTION-STATUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_connection_status,
	    STATIC_FUNCTION(put_g2_connection_status,NIL,FALSE,3,3));
    mutate_global_property(Qg2_connection_status,
	    SYMBOL_FUNCTION(Qput_g2_connection_status),Qslot_putter);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qg2_extension,Qui_client_item);
    check_if_superior_classes_are_defined(Qg2_window,list_constant_45);
    string_constant_51 = 
	    STATIC_STRING("1n1m8v836vy1m83Vy1p0833Uy083gy3Qy1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_52 = 
	    STATIC_STRING("13Hy4z8r8u8u836vy836vy01p8w9k3uy3py1n1p83Jy1mpk1m3pyk1m3py3ay1mp3ay1x83Jy1m3ayp1m83*Hy1m3hys1m3kyz1m3ky3Ly1m83*Hy1m3hy3Sy1m3ay3V");
    string_constant_53 = 
	    STATIC_STRING("y1m3Gy3Vy1m83*Hy1mx3Sy1mu3Ly1muz1m83*Hy1mxs1m3Gyp1p83Jy1mp3cy1m3py3cy1m3uy3py1mk3py001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTI");
    string_constant_54 = 
	    STATIC_STRING("TY class definition000004z8r83eby83eby836vy836vy00001m1l8o1l8l000004z8r836uy836uy836vy836vy00001n1l8l1m8p831=y1l83Hy000004z8r838");
    string_constant_55 = 
	    STATIC_STRING("Zy838Zy836vy836vy00001n1l8l1m8p830Ky1l83Hy000004z8r83aky83aky836vy836vy00001n1l8l1m8p831fy1l83Hy000004z8r83NZy83NZy836vy836vy000");
    string_constant_56 = 
	    STATIC_STRING("01o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Niy83Niy836vy836vy0k001n1l8l1m8p8360y1l83Fy000004z8r83Nky83Nky836vy836vy0k001n1l8l1m8p836");
    string_constant_57 = 
	    STATIC_STRING("0y1l83Fy000004z8r83Nhy83Nhy836vy836vy0k001n1l8l1m8p8361y1l83Fy000004z8r83NXy83NXy836vy836vy0k001n1l8l1m8p8361y1l83Fy000004z8r83N");
    string_constant_58 = 
	    STATIC_STRING("jy83Njy836vy836vy03-7y001n1l8l1m8p8361y1l83Fy000004z8r83Nly83Nly836vy836vy03-7y001n1l8l1m8p8361y1l83Fy000004z8r83Nby83Nby836vy83");
    string_constant_59 = 
	    STATIC_STRING("6vy00001o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Ndy83Ndy836vy836vy00001o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Nfy83Nfy836vy836vy00001");
    string_constant_60 = 
	    STATIC_STRING("o1l8l1l83Fy1m8p836Qy1l83Hy000004z8r83NYy83NYy836vy836vy00001o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Ney83Ney836vy836vy00001o1l8l1l8");
    string_constant_61 = 
	    STATIC_STRING("3Fy1m8p83*iy1l83Hy000004z8r83Ncy83Ncy836vy836vy00001o1l8l1l83Fy1m8p83*iy1l83Hy000004z8r83Zuy83Zuy836vy836vy08k001n1m8p83Ky1l83Ey");
    string_constant_62 = 
	    STATIC_STRING("1l8l000004z8r83Ngy83Ngy836vy836vy03Baz001o1l8l1l83Fy1n8p83-hy83*iy1l83Hy000004z8r83Nay83Nay836vy836vy03Baz001o1l8l1l83Fy1n8p83-h");
    string_constant_63 = STATIC_STRING("y83*iy1l83Hy00000");
    string_constant_64 = 
	    STATIC_STRING("13Jy8q1p836vy1m835Hy836Py1m8v836vy1m83Vy1p0833Uy083gy3Qy8t1m8u1p8w9k3uy3py1n1p83Jy1mpk1m3pyk1m3py3ay1mp3ay1x83Jy1m3ayp1m83*Hy1m3");
    string_constant_65 = 
	    STATIC_STRING("hys1m3kyz1m3ky3Ly1m83*Hy1m3hy3Sy1m3ay3Vy1m3Gy3Vy1m83*Hy1mx3Sy1mu3Ly1muz1m83*Hy1mxs1m3Gyp1p83Jy1mp3cy1m3py3cy1m3uy3py1mk3py1o83eb");
    string_constant_66 = 
	    STATIC_STRING("y08o8l1o836uy01m8p831=y83Hy1o838Zy01m8p830Ky83Hy1o83aky01m8p831fy83Hy1p83NZy083Fy1m8p83*iy83Hy1o83Niyk1m8p8360y83Fy1o83Nkyk1m8p8");
    string_constant_67 = 
	    STATIC_STRING("360y83Fy1o83Nhyk1m8p8361y83Fy1o83NXyk1m8p8361y83Fy1o83Njy3-7y1m8p8361y83Fy1o83Nly3-7y1m8p8361y83Fy1p83Nby083Fy1m8p83*iy83Hy1p83N");
    string_constant_68 = 
	    STATIC_STRING("dy083Fy1m8p83*iy83Hy1p83Nfy083Fy1m8p836Qy83Hy1p83NYy083Fy1m8p83*iy83Hy1p83Ney083Fy1m8p83*iy83Hy1p83Ncy083Fy1m8p83*iy83Hy1p83Zuy8");
    string_constant_69 = 
	    STATIC_STRING("k1m8p83Ky83Ey8l1p83Ngy3Baz83Fy1n8p83-hy83*iy83Hy1p83Nay3Baz83Fy1n8p83-hy83*iy83Hy");
    temp = regenerate_optimized_constant(string_constant_51);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_2 = regenerate_optimized_constant(list(12,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qg2_window,list_constant_45,Nil,temp,Nil,
	    temp_2,list_constant_45,regenerate_optimized_constant(list(6,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69)),Nil);
    G2_window_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_window,
	    Class_description_gkbprop);
    Qworkspace_view = STATIC_SYMBOL("WORKSPACE-VIEW",AB_package);
    temp = FIX((SI_Long)275L);
    mutate_global_property(Qworkspace_view,CONS(Qg2_window,temp),
	    Qsubstitute_class_and_kb_flags);
    Qg2_window_style_override = STATIC_SYMBOL("G2-WINDOW-STYLE-OVERRIDE",
	    AB_package);
    Qcompile_g2_window_style_override_for_slot = 
	    STATIC_SYMBOL("COMPILE-G2-WINDOW-STYLE-OVERRIDE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_g2_window_style_override_for_slot,
	    STATIC_FUNCTION(compile_g2_window_style_override_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qg2_window_style_override,
	    SYMBOL_FUNCTION(Qcompile_g2_window_style_override_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qg2_window_style_override,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_g2_window_style_override_from_slot = 
	    STATIC_SYMBOL("WRITE-G2-WINDOW-STYLE-OVERRIDE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_g2_window_style_override_from_slot,
	    STATIC_FUNCTION(write_g2_window_style_override_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qg2_window_style_override,
	    SYMBOL_FUNCTION(Qwrite_g2_window_style_override_from_slot),
	    Qslot_value_writer);
    Qg2_window_user_is_valid = STATIC_SYMBOL("G2-WINDOW-USER-IS-VALID",
	    AB_package);
    Qg2_window_mode_is_valid = STATIC_SYMBOL("G2-WINDOW-MODE-IS-VALID",
	    AB_package);
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    Qui_client_user_mode = STATIC_SYMBOL("UI-CLIENT-USER-MODE",AB_package);
    Qput_g2_user_mode = STATIC_SYMBOL("PUT-G2-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_user_mode,STATIC_FUNCTION(put_g2_user_mode,
	    NIL,FALSE,3,3));
    mutate_global_property(Qg2_user_mode,
	    SYMBOL_FUNCTION(Qput_g2_user_mode),Qslot_putter);
    Qshow_operator_logbook_in_this_window_qm = 
	    STATIC_SYMBOL("SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW\?",AB_package);
    Qput_show_operator_logbook_in_this_window_qm = 
	    STATIC_SYMBOL("PUT-SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_show_operator_logbook_in_this_window_qm,
	    STATIC_FUNCTION(put_show_operator_logbook_in_this_window_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qshow_operator_logbook_in_this_window_qm,
	    SYMBOL_FUNCTION(Qput_show_operator_logbook_in_this_window_qm),
	    Qslot_putter);
    string_constant_14 = STATIC_STRING("none");
    Qunix_time_qm = STATIC_SYMBOL("UNIX-TIME\?",AB_package);
    Qwrite_unix_time_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-UNIX-TIME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_unix_time_qm_from_slot,
	    STATIC_FUNCTION(write_unix_time_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qunix_time_qm,
	    SYMBOL_FUNCTION(Qwrite_unix_time_qm_from_slot),Qslot_value_writer);
    list_constant_46 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_11);
    set_property_value_function(get_symbol_properties_function(Qunix_time_qm),
	    Qtype_specification_simple_expansion,list_constant_46);
    list_constant_47 = STATIC_CONS(Qnumber,Qnil);
    list_constant_48 = STATIC_CONS(Qsecond,list_constant_47);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    list_constant_49 = STATIC_CONS(Qminute,list_constant_47);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    list_constant_50 = STATIC_CONS(Qhour,list_constant_47);
    Qdate = STATIC_SYMBOL("DATE",AB_package);
    list_constant_51 = STATIC_CONS(Qdate,list_constant_47);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    list_constant_52 = STATIC_CONS(Qmonth,list_constant_47);
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    list_constant_53 = STATIC_CONS(Qyear,list_constant_47);
    list_constant_54 = STATIC_LIST((SI_Long)6L,list_constant_48,
	    list_constant_49,list_constant_50,list_constant_51,
	    list_constant_52,list_constant_53);
    list_constant_55 = STATIC_LIST((SI_Long)7L,Qand,Qhour,Qminute,Qsecond,
	    Qmonth,Qdate,Qyear);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_54,list_constant_55);
    list_constant_57 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_56);
    define_type_specification_explicit_complex_type(Qunix_time_qm,
	    list_constant_57);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    unix_time_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(unix_time_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qunix_time_qm,
	    unix_time_qm_evaluation_getter_1);
    Qspecific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",AB_package);
    Qg2_window_specific_language = 
	    STATIC_SYMBOL("G2-WINDOW-SPECIFIC-LANGUAGE",AB_package);
    alias_slot_name(3,Qspecific_language_for_this_g2_window_qm,
	    Qg2_window_specific_language,Qg2_window);
    Qg2_window_network_host_name_qm = 
	    STATIC_SYMBOL("G2-WINDOW-NETWORK-HOST-NAME\?",AB_package);
    Qg2_window_remote_host_name = 
	    STATIC_SYMBOL("G2-WINDOW-REMOTE-HOST-NAME",AB_package);
    alias_slot_name(3,Qg2_window_network_host_name_qm,
	    Qg2_window_remote_host_name,Qg2_window);
    Qg2_window_os_user_name_qm = STATIC_SYMBOL("G2-WINDOW-OS-USER-NAME\?",
	    AB_package);
    Qg2_window_user_name_in_operating_system = 
	    STATIC_SYMBOL("G2-WINDOW-USER-NAME-IN-OPERATING-SYSTEM",
	    AB_package);
    alias_slot_name(3,Qg2_window_os_user_name_qm,
	    Qg2_window_user_name_in_operating_system,Qg2_window);
    Qg2_window_os_type_qm = STATIC_SYMBOL("G2-WINDOW-OS-TYPE\?",AB_package);
    Qg2_window_operating_system_type = 
	    STATIC_SYMBOL("G2-WINDOW-OPERATING-SYSTEM-TYPE",AB_package);
    alias_slot_name(3,Qg2_window_os_type_qm,
	    Qg2_window_operating_system_type,Qg2_window);
    Qg2_window_time_of_last_connection_qm = 
	    STATIC_SYMBOL("G2-WINDOW-TIME-OF-LAST-CONNECTION\?",AB_package);
    Qg2_window_time_of_last_connection = 
	    STATIC_SYMBOL("G2-WINDOW-TIME-OF-LAST-CONNECTION",AB_package);
    alias_slot_name(3,Qg2_window_time_of_last_connection_qm,
	    Qg2_window_time_of_last_connection,Qg2_window);
    Qg2_window_initial_window_configuration_string_qm = 
	    STATIC_SYMBOL("G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING\?",
	    AB_package);
    Qg2_window_initial_window_configuration_string = 
	    STATIC_SYMBOL("G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING",
	    AB_package);
    alias_slot_name(3,Qg2_window_initial_window_configuration_string_qm,
	    Qg2_window_initial_window_configuration_string,Qg2_window);
    Qg2_window_reroute_problem_report_qm = 
	    STATIC_SYMBOL("G2-WINDOW-REROUTE-PROBLEM-REPORT\?",AB_package);
    Qg2_window_reroute_problem_report = 
	    STATIC_SYMBOL("G2-WINDOW-REROUTE-PROBLEM-REPORT",AB_package);
    alias_slot_name(3,Qg2_window_reroute_problem_report_qm,
	    Qg2_window_reroute_problem_report,Qg2_window);
    string_constant_70 = STATIC_STRING("1m1m831fy1m9k83Zy1m831fy83Tby");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qunreserved_symbol),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qunreserved_symbol,
	    Qsymbol);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    string_constant_15 = STATIC_STRING(" ~s is a reserved-symbol");
    unreserved_symbol_evaluation_setter_1 = 
	    STATIC_FUNCTION(unreserved_symbol_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qunreserved_symbol,
	    unreserved_symbol_evaluation_setter_1);
    unreserved_symbol_evaluation_getter_1 = 
	    STATIC_FUNCTION(unreserved_symbol_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qunreserved_symbol,
	    unreserved_symbol_evaluation_getter_1);
    Qlanguage_qm = STATIC_SYMBOL("LANGUAGE\?",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,Qnil);
    set_property_value_function(get_symbol_properties_function(Qlanguage_qm),
	    Qtype_specification_simple_expansion,list_constant_58);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_29,
	    list_constant_5);
    define_type_specification_explicit_complex_type(Qlanguage_qm,
	    list_constant_7);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnamed,Qlanguage_qm);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    language_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(language_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlanguage_qm,
	    language_qm_evaluation_setter_1);
    language_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(language_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlanguage_qm,
	    language_qm_evaluation_getter_1);
    Qcompile_language_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-LANGUAGE\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_language_qm_for_slot,
	    STATIC_FUNCTION(compile_language_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlanguage_qm,
	    SYMBOL_FUNCTION(Qcompile_language_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlanguage_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_language_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-LANGUAGE\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_language_qm_from_slot,
	    STATIC_FUNCTION(write_language_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlanguage_qm,
	    SYMBOL_FUNCTION(Qwrite_language_qm_from_slot),Qslot_value_writer);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Qui_client_specific_language = 
	    STATIC_SYMBOL("UI-CLIENT-SPECIFIC-LANGUAGE",AB_package);
    Qput_specific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("PUT-SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_specific_language_for_this_g2_window_qm,
	    STATIC_FUNCTION(put_specific_language_for_this_g2_window_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qspecific_language_for_this_g2_window_qm,
	    SYMBOL_FUNCTION(Qput_specific_language_for_this_g2_window_qm),
	    Qslot_putter);
    Qg2_window_style = STATIC_SYMBOL("G2-WINDOW-STYLE",AB_package);
    Qput_g2_window_style = STATIC_SYMBOL("PUT-G2-WINDOW-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_window_style,
	    STATIC_FUNCTION(put_g2_window_style,NIL,FALSE,3,3));
    mutate_global_property(Qg2_window_style,
	    SYMBOL_FUNCTION(Qput_g2_window_style),Qslot_putter);
    Qnetwork_wire = STATIC_SYMBOL("NETWORK-WIRE",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_59 = STATIC_CONS(Qconnection,Qnil);
    check_if_superior_classes_are_defined(Qnetwork_wire,list_constant_59);
    string_constant_71 = STATIC_STRING("1l1m8v833Uy");
    string_constant_72 = 
	    STATIC_STRING("1l4z8r83=Hy83=Hy833Uy833Uy01l2l83Tyn001p1l8l1l83Cy1l8o1l8z1m83Dy53-=yExport: ( [color: color-symbol, width: integer] *), writabl");
    string_constant_73 = STATIC_STRING("e: true,00000");
    string_constant_74 = 
	    STATIC_STRING("1n8q1n833Uy1l83=+y1m8v833Uy1o83=Hy1l2l83Tyn8l83Cy");
    temp = regenerate_optimized_constant(string_constant_71);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_72,
	    string_constant_73));
    add_class_to_environment(9,Qnetwork_wire,list_constant_59,Nil,temp,Nil,
	    temp_2,list_constant_59,
	    regenerate_optimized_constant(string_constant_74),Nil);
    string_constant_16 = STATIC_STRING("~A~%");
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qg2_show_schedule = STATIC_SYMBOL("G2-SHOW-SCHEDULE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_show_schedule,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qg2_show_schedule,STATIC_FUNCTION(g2_show_schedule,
	    NIL,FALSE,2,2));
    Qg2_do_abort_workspace = STATIC_SYMBOL("G2-DO-ABORT-WORKSPACE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_do_abort_workspace,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_do_abort_workspace,
	    STATIC_FUNCTION(g2_do_abort_workspace,NIL,FALSE,0,0));
    Qg2_cause_synchronous_abort = 
	    STATIC_SYMBOL("G2-CAUSE-SYNCHRONOUS-ABORT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_cause_synchronous_abort,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_cause_synchronous_abort,
	    STATIC_FUNCTION(g2_cause_synchronous_abort,NIL,FALSE,0,0));
    if (Intentionally_bogus_vector_for_g2_cause_asynchronous_abort == UNBOUND)
	Intentionally_bogus_vector_for_g2_cause_asynchronous_abort = Nil;
    Qg2_cause_asynchronous_abort = 
	    STATIC_SYMBOL("G2-CAUSE-ASYNCHRONOUS-ABORT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_cause_asynchronous_abort,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_cause_asynchronous_abort,
	    STATIC_FUNCTION(g2_cause_asynchronous_abort,NIL,FALSE,0,0));
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    list_constant_60 = STATIC_CONS(Qui_client_item,Qnil);
    list_constant_61 = STATIC_CONS(Qobject,list_constant_60);
    check_if_superior_classes_are_defined(Qui_client_session,list_constant_61);
    string_constant_75 = STATIC_STRING("1o1l83Ly1l83Iy1l83ey1l8t");
    string_constant_76 = 
	    STATIC_STRING("13Cy4z8r83dLy83dLy83d8y83d8y00001o1m8p831=y1l8o1l8l1l83Hy000004z8r83dMy83dMy83d8y83d8y00001p1m8p83-2y1l83Fy1l8o1l8l1l83Hy000004z");
    string_constant_77 = 
	    STATIC_STRING("8r83dGy83dGy83d8y83d8y00001p1m8p83*iy1l83Fy1l8o1l8l1l83Hy000004z8r83d9y83d9y83d8y83d8y00001q1l8l1m8p831ny1l83Fy1l83Ny1l8o1l83Hy0");
    string_constant_78 = 
	    STATIC_STRING("00004z8r83aly83aly83d8y83d8y00001o1l8l1l83Fy1m8p831fy1l83Hy000004z8r83dJy83dJy83d8y83d8y00001o1l8l1l83Fy1m8p836Qy1l83Hy000004z8r");
    string_constant_79 = 
	    STATIC_STRING("83dDy83dDy83d8y83d8y00001p1l8l1m8p8365y1l83Fy1l8o1l83Hy000004z8r83dFy83dFy83d8y83d8y00001p1l8l1n8p83-2y83*iy1l83Fy1l8o1l83Hy0000");
    string_constant_80 = 
	    STATIC_STRING("04z8r83dHy83dHy83d8y83d8y00001m1l8o1l8l000004z8r83dNy83dNy83d8y83d8y00001m1l8o1l8l000004z8r83dBy83dBy83d8y83d8y0i001m1l8o1l8l000");
    string_constant_81 = 
	    STATIC_STRING("004z8r83dKy83dKy83d8y83d8y03Baz001o1l8l1l83Fy1n8p83-hy83*iy1l83Hy000004z8r83dCy83dCy83d8y83d8y03Baz001o1l8l1l83Fy1n8p83-hy83*iy1");
    string_constant_82 = 
	    STATIC_STRING("l83Hy000004z8r83dIy83dIy83d8y83d8y00001q1m8p83-2y1l83Fy1l83Ny1l8o1l8l1l83Hy000004z8r83dEy83dEy83d8y83d8y00001q1m8p8365y1l83Fy1l8");
    string_constant_83 = 
	    STATIC_STRING("3Ny1l8o1l8l1l83Hy000004z8r83dAy83dAy83d8y83d8y00001p1l83Fy1l83Ny1l8o1l8l1l83Hy00000");
    string_constant_84 = 
	    STATIC_STRING("13Ey8q1q83d8y1m83-Oy836Py83Ly83Iy83ey8t1q83dLy01m8p831=y8o8l83Hy1r83dMy01m8p83-2y83Fy8o8l83Hy1r83dGy01m8p83*iy83Fy8o8l83Hy1r83d9");
    string_constant_85 = 
	    STATIC_STRING("y01m8p831ny83Fy83Ny8o83Hy1p83aly083Fy1m8p831fy83Hy1p83dJy083Fy1m8p836Qy83Hy1q83dDy01m8p8365y83Fy8o83Hy1q83dFy01n8p83-2y83*iy83Fy");
    string_constant_86 = 
	    STATIC_STRING("8o83Hy1o83dHy08o8l1o83dNy08o8l1o83dByi8o8l1p83dKy3Baz83Fy1n8p83-hy83*iy83Hy1p83dCy3Baz83Fy1n8p83-hy83*iy83Hy1s83dIy01m8p83-2y83F");
    string_constant_87 = 
	    STATIC_STRING("y83Ny8o8l83Hy1s83dEy01m8p8365y83Fy83Ny8o8l83Hy1r83dAy083Fy83Ny8o8l83Hy");
    temp = regenerate_optimized_constant(string_constant_75);
    temp_2 = regenerate_optimized_constant(list(8,string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79,
	    string_constant_80,string_constant_81,string_constant_82,
	    string_constant_83));
    add_class_to_environment(9,Qui_client_session,list_constant_61,Nil,
	    temp,Nil,temp_2,list_constant_61,
	    regenerate_optimized_constant(LIST_4(string_constant_84,
	    string_constant_85,string_constant_86,string_constant_87)),Nil);
    Qcurrent_ui_client_session = STATIC_SYMBOL("CURRENT-UI-CLIENT-SESSION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_ui_client_session,
	    Current_ui_client_session);
    record_system_variable(Qcurrent_ui_client_session,Qworkstation,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qui_client_session_user_mode = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-MODE",AB_package);
    Qput_ui_client_session_user_mode = 
	    STATIC_SYMBOL("PUT-UI-CLIENT-SESSION-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_ui_client_session_user_mode,
	    STATIC_FUNCTION(put_ui_client_session_user_mode,NIL,FALSE,3,3));
    mutate_global_property(Qui_client_session_user_mode,
	    SYMBOL_FUNCTION(Qput_ui_client_session_user_mode),Qslot_putter);
    Qspecific_language_for_this_ui_client_session_qm = 
	    STATIC_SYMBOL("SPECIFIC-LANGUAGE-FOR-THIS-UI-CLIENT-SESSION\?",
	    AB_package);
    Qput_specific_language_for_this_ui_client_session_qm = 
	    STATIC_SYMBOL("PUT-SPECIFIC-LANGUAGE-FOR-THIS-UI-CLIENT-SESSION\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_specific_language_for_this_ui_client_session_qm,
	    STATIC_FUNCTION(put_specific_language_for_this_ui_client_session_qm,
	    NIL,FALSE,3,3));
    mutate_global_property(Qspecific_language_for_this_ui_client_session_qm,
	    SYMBOL_FUNCTION(Qput_specific_language_for_this_ui_client_session_qm),
	    Qslot_putter);
}
