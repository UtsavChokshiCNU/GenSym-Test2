/* vw-g2.c
 * Input file:  view-g2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "vw-g2.h"


/* ICP-SOCKET-REMOTE-GENSYM-WINDOW */
Object icp_socket_remote_gensym_window(icp_socket)
    Object icp_socket;
{
    Object icp_output_port, workstation, ab_loop_list_, gensym_window, temp;

    x_note_fn_call(228,0);
    icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if (EQ(icp_output_port,ISVREF(gensym_window,(SI_Long)12L))) {
	temp = gensym_window;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* USER-DEFINED-CLASS-NAMES-ON-WORKSPACE */
Object user_defined_class_names_on_workspace(ws)
    Object ws;
{
    Object result_1, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object item, class_name, class_description_qm;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_;
    char temp;

    x_note_fn_call(228,1);
    result_1 = Qnil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    item = Nil;
    class_name = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    item = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    class_name = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L))) {
	gensym_modify_macro_using_test_arg_1 = class_name;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = result_1;
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
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	result_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* CLASS-COUNT-ON-WORKSPACE */
Object class_count_on_workspace(ws,class_name)
    Object ws, class_name;
{
    Object result_1, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object item, item_class_name;

    x_note_fn_call(228,2);
    result_1 = FIX((SI_Long)0L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    item = Nil;
    item_class_name = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    item = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    item_class_name = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    if (EQ(item_class_name,class_name))
	result_1 = FIXNUM_ADD1(result_1);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object Qsocket;             /* socket */

static Object Qsession_id;         /* session-id */

/* REPRESENTATION-ADDRESS-VALID-P */
Object representation_address_valid_p(representation)
    Object representation;
{
    Object address, icp_socket, session_id_qm, temp;

    x_note_fn_call(228,3);
    address = ISVREF(representation,(SI_Long)8L);
    icp_socket = getfq_function_no_default(address,Qsocket);
    session_id_qm = getfq_function_no_default(address,Qsession_id);
    temp =  !TRUEP(session_id_qm) ? T : Nil;
    if (temp);
    else
	temp = FIXNUM_EQ(session_id_qm,ISVREF(icp_socket,(SI_Long)40L)) ? 
		T : Nil;
    return VALUES_1(temp);
}

static Object Qws_representation;  /* ws-representation */

/* GET-OBJECT-DEFINITION-REPRESENTATION */
Object get_object_definition_representation(definition,icp_socket)
    Object definition, icp_socket;
{
    Object frame_representations, representation, ab_loop_list_;
    Object gensymed_symbol, sub_class_bit_vector, address;
    Object representation_icp_socket;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,4);
    frame_representations = ISVREF(definition,(SI_Long)9L);
    representation = Nil;
    ab_loop_list_ = frame_representations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qws_representation,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	address = ISVREF(representation,(SI_Long)8L);
	representation_icp_socket = getf(address,Qsocket,_);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* NOTE-DISUSE-OF-OBJECT-DEFINITION-REPRESENTATION */
Object note_disuse_of_object_definition_representation(object_definition,
	    icp_socket,decrement)
    Object object_definition, icp_socket, decrement;
{
    Object representation, decff_1_arg, svref_new_value;

    x_note_fn_call(228,5);
    representation = 
	    get_object_definition_representation(object_definition,icp_socket);
    if (representation) {
	decff_1_arg = decrement;
	svref_new_value = FIXNUM_MINUS(ISVREF(representation,(SI_Long)10L),
		decff_1_arg);
	if (IFIX(ISVREF(representation,(SI_Long)10L) = svref_new_value) == 
		(SI_Long)0L)
	    return delete_representation(1,representation);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-USE-OF-OBJECT-DEFINITION-REPRESENTATION */
Object note_use_of_object_definition_representation(object_definition,
	    icp_socket,increment)
    Object object_definition, icp_socket, increment;
{
    Object representation, incff_1_arg, svref_new_value;

    x_note_fn_call(228,6);
    representation = 
	    get_object_definition_representation(object_definition,icp_socket);
    if (representation) {
	incff_1_arg = increment;
	svref_new_value = FIXNUM_ADD(ISVREF(representation,(SI_Long)10L),
		incff_1_arg);
	return VALUES_1(ISVREF(representation,(SI_Long)10L) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qobject_definition_representation;  /* object-definition-representation */

/* REPRESENT-CLASS */
Object represent_class(class_name,icp_socket)
    Object class_name, icp_socket;
{
    Object temp, new_representation, svref_new_value;
    char temp_1;

    x_note_fn_call(228,7);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_definition_gkbprop)) {
	if (lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop)) {
	    temp = lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	new_representation = make_representation(icp_socket,
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop),Qobject_definition_representation);
	svref_new_value = slot_value_list_4(Qsocket,icp_socket,Qsession_id,
		ISVREF(icp_socket,(SI_Long)40L));
	ISVREF(new_representation,(SI_Long)8L) = svref_new_value;
	return VALUES_1(ISVREF(new_representation,(SI_Long)10L) = 
		FIX((SI_Long)0L));
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* REPRESENT-WS */
Object represent_ws(ws,icp_socket,callback)
    Object ws, icp_socket, callback;
{
    Object workspace_was_showing_p, temp, representation, svref_new_value, x2;
    Object frame_serial_number_setf_arg, old, new_1;
    char temp_1;

    x_note_fn_call(228,8);
    workspace_was_showing_p = ISVREF(ws,(SI_Long)16L);
    if (workspace_was_showing_p);
    else
	workspace_was_showing_p =  !TRUEP(Nil) ? 
		workspace_showing_on_ui_client_p(ws) : Qnil;
    temp = icp_socket;
    if (temp);
    else
	temp = Local_pseudo_socket;
    representation = make_representation(temp,ws,Qws_representation);
    store_callback_representation(representation);
    svref_new_value = slot_value_list_4(Qsocket,icp_socket,Qsession_id,
	    ISVREF(icp_socket,(SI_Long)40L));
    ISVREF(representation,(SI_Long)8L) = svref_new_value;
    svref_new_value = 
	    demand_representation_callback_remote_procedure_name(callback);
    ISVREF(representation,(SI_Long)10L) = svref_new_value;
    if (SIMPLE_VECTOR_P(callback) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(callback)) > (SI_Long)2L &&  
	    !EQ(ISVREF(callback,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(callback,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = svref_new_value;
    }
    if ( !TRUEP(workspace_was_showing_p))
	event_update_status_of_block_showing(ws,Nil,T);
    return VALUES_1(representation);
}

static Object Qtc_representation;  /* tc-representation */

/* REPRESENT-TREND-CHART */
Object represent_trend_chart(item,icp_socket,callback)
    Object item, icp_socket, callback;
{
    Object temp, representation, svref_new_value, x2;
    Object frame_serial_number_setf_arg, old, new_1;
    char temp_1;

    x_note_fn_call(228,9);
    temp = icp_socket;
    if (temp);
    else
	temp = Local_pseudo_socket;
    representation = make_representation(temp,item,Qtc_representation);
    store_callback_representation(representation);
    svref_new_value = slot_value_list_4(Qsocket,icp_socket,Qsession_id,
	    ISVREF(icp_socket,(SI_Long)40L));
    ISVREF(representation,(SI_Long)8L) = svref_new_value;
    svref_new_value = 
	    demand_representation_callback_remote_procedure_name(callback);
    ISVREF(representation,(SI_Long)10L) = svref_new_value;
    if (SIMPLE_VECTOR_P(callback) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(callback)) > (SI_Long)2L &&  
	    !EQ(ISVREF(callback,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(callback,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = svref_new_value;
    }
    return VALUES_1(representation);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qconnection_style;   /* connection-style */

static Object Qstub_length;        /* stub-length */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qstyle;              /* style */

static Object Qab_structure;       /* structure */

/* CONNECTION-PROPERTY-GETTER */
Object connection_property_getter(connection_structure)
    Object connection_structure;
{
    Object x2, connection_class, connection_frame_or_class, style, stub_length;
    Object cross_section_pattern, gensymed_symbol, temp_1, item_or_value;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp;

    x_note_fn_call(228,10);
    if (SIMPLE_VECTOR_P(connection_structure) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_structure)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_structure,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_structure,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	connection_class = ISVREF(ISVREF(connection_structure,(SI_Long)1L),
		(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(connection_structure) && 
	    EQ(ISVREF(connection_structure,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	connection_frame_or_class = ISVREF(connection_structure,(SI_Long)1L);
	if (SYMBOLP(connection_frame_or_class))
	    connection_class = connection_frame_or_class;
	else {
	    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		connection_class = ISVREF(ISVREF(connection_frame_or_class,
			(SI_Long)1L),(SI_Long)1L);
	    else
		connection_class = Nil;
	}
    }
    else
	connection_class = type_of_named_structure(connection_structure);
    style = get_attribute_from_class(connection_class,Qconnection_style);
    stub_length = get_attribute_from_class(connection_class,Qstub_length);
    cross_section_pattern = get_attribute_from_class(connection_class,
	    Qcross_section_pattern);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qstyle;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Qstyle;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = style;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = style;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qstub_length;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = Qstub_length;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = stub_length;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = stub_length;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qcross_section_pattern;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)5L)) = Qcross_section_pattern;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = cross_section_pattern;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = cross_section_pattern;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qname;               /* name */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qfont;               /* font */

static Object Qhm14;               /* hm14 */

static Object Qtext_line_color;    /* text-line-color */

static Object Qforeground;         /* foreground */

static Object Qtext_background_color;  /* text-background-color */

static Object Qtransparent;        /* transparent */

static Object Qleft_margin;        /* left-margin */

static Object Qtop_margin;         /* top-margin */

static Object Qright_margin;       /* right-margin */

static Object Qbottom_margin;      /* bottom-margin */

static Object Qindentation_margin;  /* indentation-margin */

static Object Qtext_line_height;   /* text-line-height */

static Object Qtext_line_spacing;  /* text-line-spacing */

static Object Qborder_width;       /* border-width */

static Object Qborder_color;       /* border-color */

/* TEXT-BOX-FORMAT-PROPERTY-GETTER */
Object text_box_format_property_getter(text_box_format)
    Object text_box_format;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,11);
    if (text_box_format) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)26L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qname;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qname;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    get_lookup_slot_value_given_default(text_box_format,
		    Qname_or_names_for_frame,Nil);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = 
		    get_lookup_slot_value_given_default(text_box_format,
		    Qname_or_names_for_frame,Nil);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qfont;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qfont;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_2 = ISVREF(text_box_format,(SI_Long)22L);
	    item_or_value = CAR(temp_2);
	    if (item_or_value);
	    else
		item_or_value = Qhm14;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    temp_2 = ISVREF(text_box_format,(SI_Long)22L);
	    item_or_value = CAR(temp_2);
	    if (item_or_value);
	    else
		item_or_value = Qhm14;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtext_line_color;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)5L)) = Qtext_line_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)23L);
	    if (item_or_value);
	    else
		item_or_value = Qforeground;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)23L);
	    if (item_or_value);
	    else
		item_or_value = Qforeground;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qtext_background_color;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)7L)) = Qtext_background_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)24L);
	    if (item_or_value);
	    else
		item_or_value = Qtransparent;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)24L);
	    if (item_or_value);
	    else
		item_or_value = Qtransparent;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qleft_margin;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)9L)) = Qleft_margin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)27L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)12L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)27L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)12L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qtop_margin;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)11L)) = Qtop_margin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)28L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)9L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)28L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)9L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qright_margin;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)13L)) = Qright_margin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)29L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)12L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)29L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)12L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qbottom_margin;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)15L)) = Qbottom_margin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)30L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)8L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)30L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)8L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)19L)) = Qindentation_margin;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)17L)) = Qindentation_margin;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)38L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)24L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)20L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)38L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)24L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)18L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)21L)) = Qtext_line_height;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)19L)) = Qtext_line_height;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)31L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)15L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)22L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)31L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)15L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)20L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)23L)) = Qtext_line_spacing;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)21L)) = Qtext_line_spacing;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)33L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)5L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)24L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)33L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)5L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)22L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)25L)) = Qborder_width;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)23L)) = Qborder_width;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)44L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)0L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)26L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)44L);
	    if (item_or_value);
	    else
		item_or_value = FIX((SI_Long)0L);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)24L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)27L)) = Qborder_color;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)25L)) = Qborder_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(text_box_format,(SI_Long)48L);
	    if (item_or_value);
	    else
		item_or_value = Qforeground;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)28L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(text_box_format,(SI_Long)48L);
	    if (item_or_value);
	    else
		item_or_value = Qforeground;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)26L)) = svref_new_value;
	}
	return eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-TEXT-TO-TEXT-SEQUENCE */
Object convert_text_to_text_sequence(text)
    Object text;
{
    Object text_lines, elt_1, ab_loop_list_, temp;

    x_note_fn_call(228,12);
    text_lines = Nil;
    elt_1 = Nil;
    ab_loop_list_ = text;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (text_string_p(elt_1)) {
	temp = copy_text_string(elt_1);
	text_lines = eval_cons_1(temp,text_lines);
    }
    goto next_loop;
  end_loop:
    temp = nreverse(text_lines);
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp);
}

/* EXPORT-TEXT-BOX-OVERRIDES */
Object export_text_box_overrides(text_box)
    Object text_box;
{
    x_note_fn_call(228,13);
    return allocate_evaluation_structure(copy_tree_including_leaves_using_eval_conses(ISVREF(text_box,
	    (SI_Long)18L)));
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qtext_lines;         /* text-lines */

static Object Qempty;              /* empty */

static Object Qitem_overrides;     /* item-overrides */

static Object Qtext_box_format;    /* text-box-format */

/* TEXT-BOX-PROPERTY-GETTER */
Object text_box_property_getter(text_box)
    Object text_box;
{
    Object text, text_box_format, text_box_overrides;
    Object text_box_format_properties, gensymed_symbol, temp, item_or_value;
    Object x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,14);
    text = get_slot_value_function(text_box,Qbox_translation_and_text,Nil);
    text_box_format = ISVREF(text_box,(SI_Long)17L);
    text_box_overrides = export_text_box_overrides(text_box);
    text_box_format_properties = 
	    text_box_format_property_getter(text_box_format);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtext_lines;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtext_lines;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = text ? convert_text_to_text_sequence(text) : Qempty;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = text ? convert_text_to_text_sequence(text) : Qempty;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_overrides;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_overrides;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = text_box_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = text_box_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtext_box_format;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qtext_box_format;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = text_box_format_properties;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = text_box_format_properties;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qlow_value;          /* low-value */

static Object Qhigh_value;         /* high-value */

static Object Qincrement;          /* increment */

/* DIAL-PROPERTY-GETTER */
Object dial_property_getter(dial)
    Object dial;
{
    Object low_value, high_value, increment, low_value_number;
    Object high_value_number, increment_number, gensymed_symbol, temp;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,15);
    low_value = ISVREF(dial,(SI_Long)31L);
    high_value = ISVREF(dial,(SI_Long)32L);
    increment = ISVREF(dial,(SI_Long)33L);
    if (NUMBERP(low_value))
	low_value_number = FIX((SI_Long)0L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	low_value_number = FIX((SI_Long)0L);
    else
	low_value_number = FIX((SI_Long)1L);
    if (NUMBERP(high_value))
	high_value_number = FIX((SI_Long)0L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	high_value_number = FIX((SI_Long)0L);
    else
	high_value_number = FIX((SI_Long)1L);
    if (NUMBERP(increment))
	increment_number = FIX((SI_Long)0L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	increment_number = FIX((SI_Long)0L);
    else
	increment_number = FIX((SI_Long)1L);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlow_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlow_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = low_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = low_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhigh_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qhigh_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = high_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = high_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qincrement;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qincrement;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = increment_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = increment_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* METER-PROPERTY-GETTER */
Object meter_property_getter(meter)
    Object meter;
{
    Object low_value, high_value, increment, low_value_number;
    Object high_value_number, increment_number, gensymed_symbol, temp;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,16);
    low_value = ISVREF(meter,(SI_Long)29L);
    high_value = ISVREF(meter,(SI_Long)30L);
    increment = ISVREF(meter,(SI_Long)31L);
    if (NUMBERP(low_value))
	low_value_number = FIX((SI_Long)0L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	low_value_number = FIX((SI_Long)0L);
    else
	low_value_number = FIX((SI_Long)1L);
    if (NUMBERP(high_value))
	high_value_number = FIX((SI_Long)10L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	high_value_number = FIX((SI_Long)0L);
    else
	high_value_number = FIX((SI_Long)1L);
    if (NUMBERP(increment))
	increment_number = FIX((SI_Long)0L);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(increment) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(increment)) == (SI_Long)1L)
	increment_number = FIX((SI_Long)1L);
    else
	increment_number = FIX((SI_Long)1L);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlow_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlow_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = low_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = low_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhigh_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qhigh_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = high_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = high_value_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qincrement;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qincrement;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = increment_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = increment_number;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qtrend_chart_time_axis_grammar_spec;  /* trend-chart-time-axis-grammar-spec */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qtrend_chart_value_axes_grammar_spec;  /* trend-chart-value-axes-grammar-spec */

static Object Qtrend_chart_point_formats_grammar_spec;  /* trend-chart-point-formats-grammar-spec */

static Object Qtrend_chart_connector_formats_grammar_spec;  /* trend-chart-connector-formats-grammar-spec */

static Object Qtrend_chart_format_grammar_spec;  /* trend-chart-format-grammar-spec */

static Object Qtrend_chart_plots_grammar_spec;  /* trend-chart-plots-grammar-spec */

static Object Qtrend_chart_active;  /* trend-chart-active */

static Object Qtitle;              /* title */

static Object Qplots;              /* plots */

static Object Qvalue_axes;         /* value-axes */

static Object Qtime_axis;          /* time-axis */

static Object Qpoint_formats;      /* point-formats */

static Object Qconnector_formats;  /* connector-formats */

static Object Qtrend_chart_format;  /* trend-chart-format */

static Object Qtimespan;           /* timespan */

static Object Qvalue_axis_extrema;  /* value-axis-extrema */

static Object Qinitial_plot_data;  /* initial-plot-data */

/* TREND-CHART-PROPERTY-GETTER */
Object trend_chart_property_getter(trend_chart)
    Object trend_chart;
{
    Object label_to_display, title, category_evaluator_interface, function;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, time_axis, value_axes, point_formats;
    Object connector_formats, trend_chart_format, trend_chart_plots, active_p;
    Object temp, item_or_value, x2, svref_new_value, initial_info;
    SI_Long gensymed_symbol_4, svref_arg_2;
    char not_already_represented_p, temp_1;

    x_note_fn_call(228,17);
    label_to_display = ISVREF(trend_chart,(SI_Long)16L);
    title = label_to_display ? convert_text_to_text_string(1,
	    label_to_display) : Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_time_axis_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)19L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	time_axis = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	time_axis = Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_value_axes_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)18L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	value_axes = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	value_axes = Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_point_formats_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)20L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	point_formats = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	point_formats = Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_connector_formats_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)21L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	connector_formats = inline_funcall_3(gensymed_symbol,
		gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	connector_formats = Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_format_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)22L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	trend_chart_format = inline_funcall_3(gensymed_symbol,
		gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	trend_chart_format = Nil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtrend_chart_plots_grammar_spec),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = ISVREF(trend_chart,(SI_Long)17L);
	gensymed_symbol_2 = trend_chart;
	gensymed_symbol_3 = Nil;
	trend_chart_plots = inline_funcall_3(gensymed_symbol,
		gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	trend_chart_plots = Nil;
    not_already_represented_p =  
	    !TRUEP(item_has_remote_representation_p(trend_chart,
	    Qtc_representation));
    active_p = ISVREF(trend_chart,(SI_Long)32L);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)18L + 
	    (SI_Long)1L));
    gensymed_symbol_4 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_4 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_4 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtrend_chart_active;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtrend_chart_active;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = active_p ? Evaluation_true_value : 
		Evaluation_false_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = active_p ? Evaluation_true_value : 
		Evaluation_false_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtitle;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qtitle;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = title;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = title;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qplots;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qplots;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = trend_chart_plots;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = trend_chart_plots;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qvalue_axes;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qvalue_axes;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = value_axes;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = value_axes;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qtime_axis;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qtime_axis;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = time_axis;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = time_axis;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qpoint_formats;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)11L)) = Qpoint_formats;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = point_formats;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = point_formats;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qconnector_formats;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)13L)) = Qconnector_formats;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = connector_formats;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = connector_formats;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qtrend_chart_format;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)15L)) = Qtrend_chart_format;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = trend_chart_format;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = trend_chart_format;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)19L)) = Qcurrent_g2_time;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)17L)) = Qcurrent_g2_time;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = copy_managed_float(Current_g2_time);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)20L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = copy_managed_float(Current_g2_time);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)18L)) = svref_new_value;
    }
    initial_info = eval_cons_1(gensymed_symbol,Qab_structure);
    if (active_p) {
	if ( !TRUEP(ISVREF(trend_chart,(SI_Long)31L)) || 
		not_already_represented_p &&  !TRUEP(showing_p(trend_chart,T)))
	    update_active_trend_chart(trend_chart,T,Nil);
	set_evaluation_structure_slot(initial_info,Qtimespan,
		collect_time_bounds(trend_chart,T,
		not_already_represented_p ? T : Nil));
	set_evaluation_structure_slot(initial_info,Qvalue_axis_extrema,
		collect_value_axis_extrema(trend_chart,T,
		not_already_represented_p ? T : Nil));
	set_evaluation_structure_slot(initial_info,Qinitial_plot_data,
		get_current_plot_data(trend_chart,T,
		not_already_represented_p ? T : Nil));
    }
    return VALUES_1(initial_info);
}

/* CHART-PROPERTY-GETTER */
Object chart_property_getter(chart)
    Object chart;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(228,18);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qlabel;              /* label */

/* ACTION-BUTTON-PROPERTY-GETTER */
Object action_button_property_getter(action_button)
    Object action_button;
{
    Object label_qm, gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,19);
    label_qm = ISVREF(action_button,(SI_Long)20L);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlabel;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = label_qm ? (FIXNUMP(label_qm) || label_qm && 
		SYMBOLP(label_qm) ? label_qm : 
		copy_evaluation_value_1(label_qm)) : Nil;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = label_qm ? (FIXNUMP(label_qm) || label_qm && 
		SYMBOLP(label_qm) ? label_qm : 
		copy_evaluation_value_1(label_qm)) : Nil;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qstatus;             /* status */

/* RADIO-BUTTON-PROPERTY-GETTER */
Object radio_button_property_getter(radio_button)
    Object radio_button;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,20);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlabel;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(radio_button,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(radio_button,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qstatus;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qstatus;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = button_status(radio_button);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = button_status(radio_button);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* CHECK-BOX-PROPERTY-GETTER */
Object check_box_property_getter(check_box)
    Object check_box;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,21);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlabel;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(check_box,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(check_box,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qstatus;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qstatus;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = button_status(check_box);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = button_status(check_box);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qslider_readout_properties;  /* slider-readout-properties */

static Object Qminimum_value;      /* minimum-value */

static Object Qmaximum_value;      /* maximum-value */

/* SLIDER-PROPERTY-GETTER */
Object slider_property_getter(slider)
    Object slider;
{
    Object additional_properties, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector, temp_1;
    Object temp_2, item_or_value, x2, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(228,22);
    additional_properties = gensym_list_2(ISVREF(slider,(SI_Long)22L),
	    ISVREF(slider,(SI_Long)23L));
    gensymed_symbol = ACCESS_ONCE(ISVREF(slider,(SI_Long)14L));
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
    superior_class_bit_number = 
	    IFIX(ISVREF(Slider_readout_class_description,(SI_Long)18L));
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
	goto end_loop;
    goto next_loop;
  end_loop:
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Slider_readout_class_description,(SI_Long)18L));
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
	temp_1 = text_box_property_getter(subblock);
	additional_properties = gensym_cons_1(temp_1,additional_properties);
    }
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	additional_properties = gensym_cons_1(eval_cons_1(gensymed_symbol,
		Qab_structure),additional_properties);
    }
    additional_properties = gensym_cons_1(ISVREF(slider,(SI_Long)20L),
	    additional_properties);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)1L)) = Qlabel;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = FIRST(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_2 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = FIRST(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qslider_readout_properties;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)3L)) = Qslider_readout_properties;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = SECOND(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_2 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = SECOND(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qminimum_value;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)5L)) = Qminimum_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = THIRD(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_2 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = THIRD(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_2,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qmaximum_value;
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_2,FIX((SI_Long)7L)) = Qmaximum_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = FOURTH(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp_2 = temp ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_2;
    }
    else {
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = FOURTH(additional_properties);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	svref_new_value = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_2,FIX((SI_Long)8L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(Qnil);
}

static Object Qlast_value_displayed;  /* last-value-displayed */

/* TYPE-IN-BOX-PROPERTY-GETTER */
Object type_in_box_property_getter(type_in_box)
    Object type_in_box;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,23);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qlabel;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qlabel;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(type_in_box,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(type_in_box,(SI_Long)20L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qlast_value_displayed;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qlast_value_displayed;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(type_in_box,(SI_Long)23L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(type_in_box,(SI_Long)23L);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qtable_rows;         /* table-rows */

/* TABLE-PROPERTY-GETTER */
Object table_property_getter(table)
    Object table;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,24);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtable_rows;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtable_rows;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = export_table_rows(table);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = export_table_rows(table);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qline_color;         /* line-color */

static Object Qleft_text;          /* left-text */

static Object Qleft_text_line_color;  /* left-text-line-color */

static Object Qright_text;         /* right-text */

static Object Qright_text_line_color;  /* right-text-line-color */

/* EXPORT-TABLE-ROWS */
Object export_table_rows(table)
    Object table;
{
    Object result_1, table_rows, reverse_table_rows, left_cell, right_cell;
    Object ab_loop_list_, left_text, left_line_color_qm, right_text;
    Object right_line_color_qm, ab_loop_desetq_, temp, text_cell_plist;
    Object text_cell_format, gensymed_symbol, temp_1, item_or_value, x2;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(228,25);
    result_1 = Qnil;
    table_rows = copy_list_using_gensym_conses_1(ISVREF(table,(SI_Long)19L));
    reverse_table_rows = nreverse(table_rows);
    left_cell = Nil;
    right_cell = Nil;
    ab_loop_list_ = reverse_table_rows;
    left_text = Nil;
    left_line_color_qm = Nil;
    right_text = Nil;
    right_line_color_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    left_cell = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    right_cell = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    left_text = CONSP(left_cell) ? convert_text_to_text_string(1,
	    CDDDR(left_cell)) : Nil;
    if (left_text) {
	text_cell_plist = CADR(left_cell);
	text_cell_format = CAR(left_cell);
	temp = text_cell_plist ? getfq_function_no_default(text_cell_plist,
		Qline_color) : Nil;
	if (temp);
	else
	    temp = ISVREF(text_cell_format,(SI_Long)23L);
	if (temp);
	else
	    temp = Qforeground;
	left_line_color_qm = temp;
    }
    else
	left_line_color_qm = Nil;
    right_text = CONSP(right_cell) ? convert_text_to_text_string(1,
	    CDDDR(right_cell)) : Nil;
    if (right_text) {
	text_cell_plist = CADR(right_cell);
	text_cell_format = CAR(right_cell);
	temp = text_cell_plist ? getfq_function_no_default(text_cell_plist,
		Qline_color) : Nil;
	if (temp);
	else
	    temp = ISVREF(text_cell_format,(SI_Long)23L);
	if (temp);
	else
	    temp = Qforeground;
	right_line_color_qm = temp;
    }
    else
	right_line_color_qm = Nil;
    if (left_text && right_text) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qleft_text;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qleft_text;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = left_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = left_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qleft_text_line_color;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qleft_text_line_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = left_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = left_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qright_text;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qright_text;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = right_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = right_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qright_text_line_color;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)7L)) = Qright_text_line_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = right_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = right_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)8L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (right_text) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qright_text;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qright_text;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = right_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = right_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qright_text_line_color;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qright_text_line_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = right_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = right_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else if (left_text) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qleft_text;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qleft_text;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = left_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = left_text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qleft_text_line_color;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qleft_text_line_color;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = left_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = left_line_color_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	temp = Qnil;
    result_1 = eval_cons_1(temp,result_1);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(reverse_table_rows);
    return allocate_evaluation_sequence(result_1);
    return VALUES_1(Qnil);
}

/* INITIAL-TABLE-ROWS */
Object initial_table_rows(class_1)
    Object class_1;
{
    Object temp;

    x_note_fn_call(228,26);
    temp = allocate_evaluation_structure(Nil);
    return VALUES_1(temp);
}

/* GET-TABLE-ROWS */
Object get_table_rows(table)
    Object table;
{
    Object temp;

    x_note_fn_call(228,27);
    temp = export_table_rows(table);
    return VALUES_1(temp);
}

/* INITIAL-TABLE-FONT-SIZE */
Object initial_table_font_size(class_1)
    Object class_1;
{
    x_note_fn_call(228,28);
    return VALUES_1(Nil);
}

/* GET-TABLE-FONT-SIZE */
Object get_table_font_size(table_item)
    Object table_item;
{
    Object temp;

    x_note_fn_call(228,29);
    temp = get_a_text_cell(table_item);
    temp = ISVREF(CAR(temp),(SI_Long)22L);
    return VALUES_1(CAR(temp));
}

/* INITIAL-REPRESENTED-ITEM */
Object initial_represented_item(class_1)
    Object class_1;
{
    Object temp;

    x_note_fn_call(228,30);
    temp = allocate_evaluation_structure(Nil);
    return VALUES_1(temp);
}

static Object Qtable_item;         /* table-item */

/* GET-REPRESENTED-ITEM */
Object get_represented_item(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1, frame;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,31);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qtable_item,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	temp_1 = 
		get_slot_represented_by_text_cell_if_any(get_a_text_cell(item));
	frame = temp_1;
	temp_1 = frame;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
	if (temp) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_1 = gensymed_symbol;
	}
	else
	    temp_1 = Qnil;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-TABLE-LAYOUT */
Object initial_table_layout(class_1)
    Object class_1;
{
    Object temp;

    x_note_fn_call(228,32);
    temp = allocate_evaluation_structure(Nil);
    return VALUES_1(temp);
}

/* GET-TABLE-LAYOUT */
Object get_table_layout(table_item)
    Object table_item;
{
    Object temp;

    x_note_fn_call(228,33);
    temp = export_table_layout(table_item);
    return VALUES_1(temp);
}

/* INITIAL-TEXT-X-MAGNIFICATION */
Object initial_text_x_magnification(class_1)
    Object class_1;
{
    x_note_fn_call(228,34);
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* GET-TEXT-X-MAGNIFICATION */
Object get_text_x_magnification(text_box)
    Object text_box;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(228,35);
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
	temp_2 = 
		get_x_magnification_of_text_box_for_system_procedure(text_box);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

/* INITIAL-TEXT-Y-MAGNIFICATION */
Object initial_text_y_magnification(class_1)
    Object class_1;
{
    x_note_fn_call(228,36);
    return VALUES_1(Nil);
}

/* GET-TEXT-Y-MAGNIFICATION */
Object get_text_y_magnification(text_box)
    Object text_box;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(228,37);
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
	temp_2 = 
		get_y_magnification_of_text_box_for_system_procedure(text_box);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp_2 = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_2);
}

/* INITIAL-FORMAT-TYPE */
Object initial_format_type(class_1)
    Object class_1;
{
    x_note_fn_call(228,38);
    return VALUES_1(Nil);
}

static Object Qformat_change_qm;   /* format-change? */

/* GET-FORMAT-TYPE */
Object get_format_type(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, format_frame, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,39);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
	format_frame = ISVREF(item,(SI_Long)16L);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    format_frame = ISVREF(item,(SI_Long)17L);
	else
	    format_frame = Qnil;
    }
    if (format_frame) {
	temp_1 = get_lookup_slot_value_given_default(format_frame,
		Qname_or_names_for_frame,Nil);
	if (temp_1);
	else
	    temp_1 = get_lookup_slot_value_given_default(format_frame,
		    Qformat_change_qm,Nil);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* INITIAL-VALUE-TO-DISPLAY */
Object initial_value_to_display(class_1)
    Object class_1;
{
    x_note_fn_call(228,40);
    return VALUES_1(Nil);
}

/* GET-VALUE-TO-DISPLAY */
Object get_value_to_display(display_or_button)
    Object display_or_button;
{
    Object temp;

    x_note_fn_call(228,41);
    temp = export_value_to_display(display_or_button);
    return VALUES_1(temp);
}

static Object Qcell_array;         /* cell-array */

static Object Qobsolete_datum;     /* obsolete-datum */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* EXPORT-DISPLAY-VALUE */
Object export_display_value varargs_1(int, n)
{
    Object display;
    Object min_value, max_value, g2_cell_array, cell_array_value_qm;
    Object managed_number_or_value, value, value_1;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, gensymed_symbol, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_3, temp_4, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    double aref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(228,42);
    INIT_ARGS_nonrelocating();
    display = REQUIRED_ARG_nonrelocating();
    min_value = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    max_value = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    g2_cell_array = get_lookup_slot_value_given_default(display,
	    Qcell_array,Nil);
    cell_array_value_qm = g2_cell_array ? 
	    ISVREF(FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(SI_Long)2L),
	    (SI_Long)0L),(SI_Long)6L) : Qnil;
    if (cell_array_value_qm) {
	managed_number_or_value = CONSP(cell_array_value_qm) && 
		EQ(M_CDR(cell_array_value_qm),Qobsolete_datum) ? 
		M_CAR(cell_array_value_qm) : cell_array_value_qm;
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    value = copy_text_string(managed_number_or_value);
	else
	    value = managed_number_or_value;
    }
    else
	value = Nil;
    if ( !TRUEP(value))
	return VALUES_1(Nil);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value))
	return VALUES_1(value);
    else if (min_value && max_value && NUMBERP(value)) {
	value_1 = lmax(min_value,lmin(max_value,value));
	if (FIXNUMP(value_1))
	    return VALUES_1(value_1);
	else if ( !TRUEP(value_1))
	    return VALUES_1(Evaluation_false_value);
	else if (EQ(value_1,T))
	    return VALUES_1(Evaluation_true_value);
	else if (SYMBOLP(value_1))
	    return VALUES_1(value_1);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_1)) == (SI_Long)1L)
	    return copy_managed_float(value_1);
	else if (FLOATP(value_1)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value_1);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
	else if (INLINE_LONG_VECTOR_P(value_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_1)) == (SI_Long)1L)
	    return copy_managed_long(value_1);
	else if (INLINE_LONG_P(value_1) != (SI_Long)0L)
	    return make_evaluation_long(value_1);
	else if (text_string_p(value_1))
	    return copy_as_wide_string(value_1);
	else if (CONSP(value_1) && EQ(M_CDR(value_1),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value_1);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		return VALUES_1(Evaluation_true_value);
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		return VALUES_1(Evaluation_false_value);
	    else
		return eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    return error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value_1));
    }
    else {
	gensymed_symbol = value;
	temp_2 = FIXNUMP(gensymed_symbol);
	if (temp_2);
	else
	    temp_2 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_2);
	else
	    temp_2 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		     IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_2);
	else
	    temp_2 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp_2);
	else
	    temp_2 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp_2);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp_2 = EQ(gensymed_symbol,Qtruth_value);
	    if (temp_2);
	    else
		temp_2 = EQ(gensymed_symbol,Qiteration_state);
	    if (temp_2);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_4 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_4);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_4 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_4);
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
		temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    if (FIXNUMP(value) || value && SYMBOLP(value))
		return VALUES_1(value);
	    else
		return copy_evaluation_value_1(value);
	}
	else if (FIXNUMP(value))
	    return VALUES_1(value);
	else if ( !TRUEP(value))
	    return VALUES_1(Evaluation_false_value);
	else if (EQ(value,T))
	    return VALUES_1(Evaluation_true_value);
	else if (SYMBOLP(value))
	    return VALUES_1(value);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    return copy_managed_float(value);
	else if (FLOATP(value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    return copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    return make_evaluation_long(value);
	else if (text_string_p(value))
	    return copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		return VALUES_1(Evaluation_true_value);
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		return VALUES_1(Evaluation_false_value);
	    else
		return eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    return error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
    }
}

/* EXPORT-VALUE-TO-DISPLAY */
Object export_value_to_display(display)
    Object display;
{
    Object gensymed_symbol, sub_class_bit_vector, managed_number_or_value;
    Object min_value, max_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,43);
    gensymed_symbol = ISVREF(display,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Meter_class_description,
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
	managed_number_or_value = ISVREF(display,(SI_Long)29L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    min_value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    min_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    min_value = copy_text_string(managed_number_or_value);
	else
	    min_value = managed_number_or_value;
	managed_number_or_value = ISVREF(display,(SI_Long)30L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    max_value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    max_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    max_value = copy_text_string(managed_number_or_value);
	else
	    max_value = managed_number_or_value;
	return export_display_value(3,display,min_value,max_value);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Dial_class_description,
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
	if (temp) {
	    managed_number_or_value = ISVREF(display,(SI_Long)31L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		min_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		min_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		min_value = copy_text_string(managed_number_or_value);
	    else
		min_value = managed_number_or_value;
	    managed_number_or_value = ISVREF(display,(SI_Long)32L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		max_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		max_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		max_value = copy_text_string(managed_number_or_value);
	    else
		max_value = managed_number_or_value;
	    return export_display_value(3,display,min_value,max_value);
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* INITIAL-BUTTON-STATUS */
Object initial_button_status(class_1)
    Object class_1;
{
    x_note_fn_call(228,44);
    return VALUES_1(Nil);
}

/* GET-BUTTON-STATUS */
Object get_button_status(button)
    Object button;
{
    Object temp;

    x_note_fn_call(228,45);
    temp = button_status(button);
    return VALUES_1(temp);
}

/* SET-BUTTON-STATUS */
Object set_button_status(button,new_value)
    Object button, new_value;
{
    x_note_fn_call(228,46);
    set_button_status_internal(button,new_value);
    return VALUES_1(Nil);
}

static Object Qvalue_request_pending;  /* value-request-pending */

static Object Qtext;               /* text */

static Object Qcheck_box;          /* check-box */

static Object Qon;                 /* on */

static Object Qoff;                /* off */

static Object Qradio_button;       /* radio-button */

/* BUTTON-STATUS */
Object button_status(button)
    Object button;
{
    Object current_computation_flags, button_1, variable;
    volatile Object value;
    volatile Object expiration_qm;
    volatile Object type;
    Object gensymed_symbol;
    volatile Object gensymed_symbol_1;
    Object variables_that_did_not_have_values, current_computation_frame;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object pruned_interest_list, eval_cons, temp, temp_1, sub_class_bit_vector;
    Object temp_3, value_1, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    char temp_2;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(228,47);
    SAVE_STACK();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		2);
	  button_1 = button;
	  variable = get_variable_for_button_if_any(button_1);
	  value = Nil;
	  expiration_qm = Nil;
	  type = Nil;
	  gensymed_symbol = Nil;
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)256L);
	  gensymed_symbol_1 = Nil;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      variables_that_did_not_have_values = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
		      1);
		if (variable) {
		    current_computation_frame = button_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			    0);
		      result = get_current_value(variable,Nil);
		    POP_SPECIAL();
		}
		else
		    result = VALUES_3(Nil,Nil,Nil);
		MVS_3(result,value,expiration_qm,type);
		gensymed_symbol_1 = Variables_that_did_not_have_values;
	      POP_SPECIAL();
	  }
	  POP_UNWIND_PROTECT(0);
	  if (gensymed_symbol_1) {
	      gensymed_symbol_2 = gensymed_symbol_1;
	      gensymed_symbol_3 = Nil;
	      gensymed_symbol_4 = Nil;
	    next_loop:
	      gensymed_symbol_3 = CAR(gensymed_symbol_2);
	      gensymed_symbol_4 = CDR(gensymed_symbol_2);
	      pruned_interest_list = 
		      delete_eval_element_1(Qvalue_request_pending,
		      ISVREF(gensymed_symbol_3,(SI_Long)36L));
	      ISVREF(gensymed_symbol_3,(SI_Long)36L) = pruned_interest_list;
	      if ( !TRUEP(pruned_interest_list) &&  
		      !TRUEP(ISVREF(gensymed_symbol_3,(SI_Long)38L)))
		  withdraw_backward_chaining(gensymed_symbol_3);
	      if ( !TRUEP(gensymed_symbol_4))
		  goto end_loop;
	      gensymed_symbol_2 = gensymed_symbol_4;
	      goto next_loop;
	    end_loop:
	      if (gensymed_symbol_1 &&  !((SI_Long)0L == 
		      inline_debugging_consing())) {
		  eval_cons = gensymed_symbol_1;
		next_loop_1:
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (EQ(eval_cons,gensymed_symbol_2))
		      goto end_1;
		  else if ( !TRUEP(eval_cons))
		      goto end_1;
		  else
		      eval_cons = CDR(eval_cons);
		  goto next_loop_1;
		end_loop_1:
		end_1:;
	      }
	      if (ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = gensymed_symbol_1;
		  temp = Available_eval_conses_tail_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = gensymed_symbol_2;
	      }
	      else {
		  temp = Available_eval_conses_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = gensymed_symbol_1;
		  temp = Available_eval_conses_tail_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = gensymed_symbol_2;
	      }
	      M_CDR(gensymed_symbol_2) = Nil;
	  }
	  CONTINUE_UNWINDING(0);
	  if (expiration_qm && EQ(type,Qtext))
	      gensymed_symbol = value;
	  gensymed_symbol_1 = ISVREF(button,(SI_Long)1L);
	  gensymed_symbol_2 = 
		  lookup_global_or_kb_specific_property_value(Qcheck_box,
		  Class_description_gkbprop);
	  if (gensymed_symbol_2) {
	      sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_2,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_5 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_6 = (SI_Long)1L;
		  gensymed_symbol_7 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_6 = gensymed_symbol_6 << gensymed_symbol_7;
		  gensymed_symbol_5 = gensymed_symbol_5 & gensymed_symbol_6;
		  temp_2 = (SI_Long)0L < gensymed_symbol_5;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(button,(SI_Long)5L)) & 
		      (SI_Long)1L)) || (SI_Long)0L != (IFIX(ISVREF(button,
		      (SI_Long)4L)) & (SI_Long)8192L) ||  
		      !TRUEP(ISVREF(button,(SI_Long)22L)))
		  temp_3 = Nil;
	      else if (constant_attribute_value_equals_datum_p(ISVREF(button,
		      (SI_Long)22L),value,type))
		  temp_3 = Qon;
	      else if (constant_attribute_value_equals_datum_p(ISVREF(button,
		      (SI_Long)23L),value,type))
		  temp_3 = Qoff;
	      else
		  temp_3 = Nil;
	  }
	  else {
	      gensymed_symbol_2 = 
		      lookup_global_or_kb_specific_property_value(Qradio_button,
		      Class_description_gkbprop);
	      if (gensymed_symbol_2) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol_1,
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_2,(SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol_5 = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_6 = (SI_Long)1L;
		      gensymed_symbol_7 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_6 = gensymed_symbol_6 << 
			      gensymed_symbol_7;
		      gensymed_symbol_5 = gensymed_symbol_5 & 
			      gensymed_symbol_6;
		      temp_2 = (SI_Long)0L < gensymed_symbol_5;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  if ( !((SI_Long)0L != (IFIX(ISVREF(button,(SI_Long)5L)) 
			  & (SI_Long)1L)) || (SI_Long)0L != 
			  (IFIX(ISVREF(button,(SI_Long)4L)) & 
			  (SI_Long)8192L) ||  !TRUEP(ISVREF(button,
			  (SI_Long)22L)))
		      value_1 = Qoff;
		  else if (constant_attribute_value_equals_datum_p(ISVREF(button,
			  (SI_Long)22L),value,type))
		      value_1 = Qon;
		  else
		      value_1 = Qoff;
		  if (FIXNUMP(value_1))
		      temp_3 = value_1;
		  else if ( !TRUEP(value_1))
		      temp_3 = Evaluation_false_value;
		  else if (EQ(value_1,T))
		      temp_3 = Evaluation_true_value;
		  else if (SYMBOLP(value_1))
		      temp_3 = value_1;
		  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_1) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_1)) == 
			  (SI_Long)1L)
		      temp_3 = copy_managed_float(value_1);
		  else if (FLOATP(value_1)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp = Vector_of_simple_float_array_pools;
			  temp_1 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_float_array_conses_tail_vector,
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value_1);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      temp_3 = new_float;
		  }
		  else if (INLINE_LONG_VECTOR_P(value_1) != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_1)) == 
			  (SI_Long)1L)
		      temp_3 = copy_managed_long(value_1);
		  else if (INLINE_LONG_P(value_1) != (SI_Long)0L)
		      temp_3 = make_evaluation_long(value_1);
		  else if (text_string_p(value_1))
		      temp_3 = copy_as_wide_string(value_1);
		  else if (CONSP(value_1) && EQ(M_CDR(value_1),Qtruth_value)) {
		      gensymed_symbol_1 = M_CAR(value_1);
		      if (FIXNUM_EQ(gensymed_symbol_1,Truth))
			  temp_3 = Evaluation_true_value;
		      else if (FIXNUM_EQ(gensymed_symbol_1,Falsity))
			  temp_3 = Evaluation_false_value;
		      else
			  temp_3 = eval_cons_1(gensymed_symbol_1,Qtruth_value);
		  }
		  else
		      temp_3 = error((SI_Long)2L,
			      "Bad type ~a for make-evaluation-value-based-on-type.",
			      type_of(value_1));
	      }
	      else
		  temp_3 = Qnil;
	  }
	  if (gensymed_symbol)
	      reclaim_text_string(gensymed_symbol);
	  result = VALUES_1(temp_3);
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    RESTORE_STACK();
    return result;
}

/* SET-BUTTON-STATUS-INTERNAL */
Object set_button_status_internal(button,new_value)
    Object button, new_value;
{
    Object current_value, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,48);
    current_value = button_status(button);
    gensymed_symbol = ISVREF(button,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qcheck_box,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if ( !( !TRUEP(new_value) || EQ(new_value,current_value))) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(button,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)23L),(SI_Long)1L);
	    gensymed_symbol_1 = button;
	    gensymed_symbol_5 = ISVREF(button,(SI_Long)14L);
	    gensymed_symbol_5 = gensymed_symbol_5 ? 
		    ISVREF(gensymed_symbol_5,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_6 = ISVREF(button,(SI_Long)14L);
	    gensymed_symbol_6 = gensymed_symbol_6 ? 
		    ISVREF(gensymed_symbol_6,(SI_Long)1L) : FIX((SI_Long)0L);
	    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qradio_button,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (EQ(current_value,Qoff) && EQ(new_value,Qon)) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(button,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)23L),(SI_Long)1L);
		gensymed_symbol_1 = button;
		gensymed_symbol_5 = ISVREF(button,(SI_Long)14L);
		gensymed_symbol_5 = gensymed_symbol_5 ? 
			ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_6 = ISVREF(button,(SI_Long)14L);
		gensymed_symbol_6 = gensymed_symbol_6 ? 
			ISVREF(gensymed_symbol_6,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_5,gensymed_symbol_6);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* INITIAL-SLIDER-VALUE */
Object initial_slider_value(class_1)
    Object class_1;
{
    x_note_fn_call(228,49);
    return VALUES_1(Nil);
}

/* GET-SLIDER-VALUE */
Object get_slider_value(slider)
    Object slider;
{
    Object temp;

    x_note_fn_call(228,50);
    temp = get_slider_value_internal(slider);
    return VALUES_1(temp);
}

/* SET-SLIDER-VALUE */
Object set_slider_value(slider,new_value)
    Object slider, new_value;
{
    Object temp;

    x_note_fn_call(228,51);
    temp = set_slider_value_internal(slider,new_value);
    return VALUES_1(temp);
}

/* GET-SLIDER-VALUE-INTERNAL */
Object get_slider_value_internal(slider)
    Object slider;
{
    Object temp, current_computation_flags, button, variable;
    volatile Object value;
    volatile Object expiration_qm;
    volatile Object type;
    Object gensymed_symbol;
    volatile Object gensymed_symbol_1;
    Object variables_that_did_not_have_values, current_computation_frame;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object pruned_interest_list, eval_cons, temp_1, temp_2;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(228,52);
    SAVE_STACK();
    temp = ISVREF(slider,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(slider,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(slider,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(slider,
	    (SI_Long)4L)) & (SI_Long)8192L)))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    2);
	      button = slider;
	      variable = get_variable_for_button_if_any(button);
	      value = Nil;
	      expiration_qm = Nil;
	      type = Nil;
	      gensymed_symbol = Nil;
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)256L);
	      gensymed_symbol_1 = Nil;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  variables_that_did_not_have_values = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
			  1);
		    if (variable) {
			current_computation_frame = button;
			PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				0);
			  result = get_current_value(variable,Nil);
			POP_SPECIAL();
		    }
		    else
			result = VALUES_3(Nil,Nil,Nil);
		    MVS_3(result,value,expiration_qm,type);
		    gensymed_symbol_1 = Variables_that_did_not_have_values;
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      if (gensymed_symbol_1) {
		  gensymed_symbol_2 = gensymed_symbol_1;
		  gensymed_symbol_3 = Nil;
		  gensymed_symbol_4 = Nil;
		next_loop:
		  gensymed_symbol_3 = CAR(gensymed_symbol_2);
		  gensymed_symbol_4 = CDR(gensymed_symbol_2);
		  pruned_interest_list = 
			  delete_eval_element_1(Qvalue_request_pending,
			  ISVREF(gensymed_symbol_3,(SI_Long)36L));
		  ISVREF(gensymed_symbol_3,(SI_Long)36L) = 
			  pruned_interest_list;
		  if ( !TRUEP(pruned_interest_list) &&  
			  !TRUEP(ISVREF(gensymed_symbol_3,(SI_Long)38L)))
		      withdraw_backward_chaining(gensymed_symbol_3);
		  if ( !TRUEP(gensymed_symbol_4))
		      goto end_loop;
		  gensymed_symbol_2 = gensymed_symbol_4;
		  goto next_loop;
		end_loop:
		  if (gensymed_symbol_1 &&  !((SI_Long)0L == 
			  inline_debugging_consing())) {
		      eval_cons = gensymed_symbol_1;
		    next_loop_1:
		      inline_note_reclaim_cons(eval_cons,Qeval);
		      if (EQ(eval_cons,gensymed_symbol_2))
			  goto end_1;
		      else if ( !TRUEP(eval_cons))
			  goto end_1;
		      else
			  eval_cons = CDR(eval_cons);
		      goto next_loop_1;
		    end_loop_1:
		    end_1:;
		  }
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = gensymed_symbol_1;
		      temp_1 = Available_eval_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = gensymed_symbol_2;
		  }
		  else {
		      temp_1 = Available_eval_conses_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = gensymed_symbol_1;
		      temp_1 = Available_eval_conses_tail_vector;
		      temp_2 = Current_thread_index;
		      SVREF(temp_1,temp_2) = gensymed_symbol_2;
		  }
		  M_CDR(gensymed_symbol_2) = Nil;
	      }
	      CONTINUE_UNWINDING(0);
	      if (expiration_qm && EQ(type,Qtext))
		  gensymed_symbol = value;
	      if (FIXNUMP(value))
		  temp = value;
	      else if ( !TRUEP(value))
		  temp = Evaluation_false_value;
	      else if (EQ(value,T))
		  temp = Evaluation_true_value;
	      else if (SYMBOLP(value))
		  temp = value;
	      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
		      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		  temp = copy_managed_float(value);
	      else if (FLOATP(value)) {
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
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
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  temp = new_float;
	      }
	      else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		  temp = copy_managed_long(value);
	      else if (INLINE_LONG_P(value) != (SI_Long)0L)
		  temp = make_evaluation_long(value);
	      else if (text_string_p(value))
		  temp = copy_as_wide_string(value);
	      else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
		  gensymed_symbol_1 = M_CAR(value);
		  if (FIXNUM_EQ(gensymed_symbol_1,Truth))
		      temp = Evaluation_true_value;
		  else if (FIXNUM_EQ(gensymed_symbol_1,Falsity))
		      temp = Evaluation_false_value;
		  else
		      temp = eval_cons_1(gensymed_symbol_1,Qtruth_value);
	      }
	      else
		  temp = error((SI_Long)2L,
			  "Bad type ~a for make-evaluation-value-based-on-type.",
			  type_of(value));
	      if (gensymed_symbol)
		  reclaim_text_string(gensymed_symbol);
	      result = VALUES_1(temp);
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qassociated_frame_for_button_qm;  /* associated-frame-for-button? */

static Object Qassociated_slot_name_for_button_qm;  /* associated-slot-name-for-button? */

static Object Qassociated_frame_serial_number_for_button_qm;  /* associated-frame-serial-number-for-button? */

static Object Qnever;              /* never */

/* SET-SLIDER-VALUE-INTERNAL */
Object set_slider_value_internal(slider,new_managed_float_value)
    Object slider, new_managed_float_value;
{
    Object variable_qm, frame_qm, slot_name, minimum_value_for_slider;
    Object maximum_value_for_slider, new_value, temp, gensymed_symbol, x, y;
    Object xa, ya, temp_2, current_computation_frame;
    char temp_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(228,53);
    variable_qm = Nil;
    frame_qm = Nil;
    slot_name = Nil;
    minimum_value_for_slider = ISVREF(slider,(SI_Long)22L);
    maximum_value_for_slider = ISVREF(slider,(SI_Long)23L);
    new_value = Nil;
    temp = ISVREF(slider,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(slider,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(slider,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(slider,
	    (SI_Long)4L)) & (SI_Long)8192L))) || 
	    button_in_use_by_system_p(slider)) {
	frame_qm = get_lookup_slot_value_given_default(slider,
		Qassociated_frame_for_button_qm,Nil);
	if (frame_qm) {
	    slot_name = get_lookup_slot_value_given_default(slider,
		    Qassociated_slot_name_for_button_qm,Nil);
	    temp_1 = TRUEP(slot_name);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(frame_qm,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(frame_qm) ? EQ(ISVREF(frame_qm,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else {
		x = gensymed_symbol;
		y = get_lookup_slot_value_given_default(slider,
			Qassociated_frame_serial_number_for_button_qm,Nil);
		if (FIXNUMP(y))
		    temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp_1 = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp_1 = FIXNUM_LT(xa,ya);
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else {
	    temp = ISVREF(slider,(SI_Long)8L);
	    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(slider,
		    (SI_Long)5L)) & (SI_Long)1L) ||  
		    !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		    (IFIX(ISVREF(slider,(SI_Long)4L)) & 
		    (SI_Long)16777216L) &&  !((SI_Long)0L != 
		    (IFIX(ISVREF(slider,(SI_Long)4L)) & (SI_Long)8192L)))) {
		variable_qm = get_variable_for_button_if_any(slider);
		temp_1 = TRUEP(variable_qm);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	if (temp_1) {
	    if (minimum_value_for_slider && maximum_value_for_slider) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_managed_float_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_managed_float_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_managed_float_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(new_managed_float_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_managed_float_value)) 
			    == (SI_Long)1L)
			temp = aref1(new_managed_float_value,FIX((SI_Long)0L));
		    else if (text_string_p(new_managed_float_value))
			temp = copy_text_string(new_managed_float_value);
		    else
			temp = new_managed_float_value;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(minimum_value_for_slider) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(minimum_value_for_slider)) 
			    == (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(minimum_value_for_slider,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(minimum_value_for_slider) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(minimum_value_for_slider)) 
			    == (SI_Long)1L)
			temp_2 = aref1(minimum_value_for_slider,
				FIX((SI_Long)0L));
		    else if (text_string_p(minimum_value_for_slider))
			temp_2 = copy_text_string(minimum_value_for_slider);
		    else
			temp_2 = minimum_value_for_slider;
		    temp = lmax(temp,temp_2);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(maximum_value_for_slider) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maximum_value_for_slider)) 
			    == (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(maximum_value_for_slider,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(maximum_value_for_slider) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maximum_value_for_slider)) 
			    == (SI_Long)1L)
			temp_2 = aref1(maximum_value_for_slider,
				FIX((SI_Long)0L));
		    else if (text_string_p(maximum_value_for_slider))
			temp_2 = copy_text_string(maximum_value_for_slider);
		    else
			temp_2 = maximum_value_for_slider;
		    new_value = lmin(temp,temp_2);
		    if (frame_qm) {
			temp = frame_qm;
			temp_2 = slot_name;
			change_slot_value(3,temp,temp_2,
				read_or_write_slider(slider,new_value));
		    }
		    else {
			current_computation_frame = slider;
			PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				0);
			  temp = variable_qm;
			  put_current_value(5,temp,
				  read_or_write_slider(slider,new_value),
				  Qnumber,Qnever,Nil);
			POP_SPECIAL();
		    }
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* TYPE-IN-BOX-VALUE */
Object type_in_box_value(type_in_box)
    Object type_in_box;
{
    Object temp, current_computation_flags, button, variable;
    volatile Object value;
    volatile Object expiration_qm;
    volatile Object type;
    Object gensymed_symbol;
    volatile Object gensymed_symbol_1;
    Object variables_that_did_not_have_values, current_computation_frame;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object pruned_interest_list, eval_cons, temp_1, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(228,54);
    SAVE_STACK();
    temp = ISVREF(type_in_box,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(type_in_box,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(type_in_box,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(type_in_box,(SI_Long)4L)) & (SI_Long)8192L)))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    2);
	      button = type_in_box;
	      variable = get_variable_for_button_if_any(button);
	      value = Nil;
	      expiration_qm = Nil;
	      type = Nil;
	      gensymed_symbol = Nil;
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)256L);
	      gensymed_symbol_1 = Nil;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  variables_that_did_not_have_values = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
			  1);
		    if (variable) {
			current_computation_frame = button;
			PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				0);
			  result = get_current_value(variable,Nil);
			POP_SPECIAL();
		    }
		    else
			result = VALUES_3(Nil,Nil,Nil);
		    MVS_3(result,value,expiration_qm,type);
		    gensymed_symbol_1 = Variables_that_did_not_have_values;
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      if (gensymed_symbol_1) {
		  gensymed_symbol_2 = gensymed_symbol_1;
		  gensymed_symbol_3 = Nil;
		  gensymed_symbol_4 = Nil;
		next_loop:
		  gensymed_symbol_3 = CAR(gensymed_symbol_2);
		  gensymed_symbol_4 = CDR(gensymed_symbol_2);
		  pruned_interest_list = 
			  delete_eval_element_1(Qvalue_request_pending,
			  ISVREF(gensymed_symbol_3,(SI_Long)36L));
		  ISVREF(gensymed_symbol_3,(SI_Long)36L) = 
			  pruned_interest_list;
		  if ( !TRUEP(pruned_interest_list) &&  
			  !TRUEP(ISVREF(gensymed_symbol_3,(SI_Long)38L)))
		      withdraw_backward_chaining(gensymed_symbol_3);
		  if ( !TRUEP(gensymed_symbol_4))
		      goto end_loop;
		  gensymed_symbol_2 = gensymed_symbol_4;
		  goto next_loop;
		end_loop:
		  if (gensymed_symbol_1 &&  !((SI_Long)0L == 
			  inline_debugging_consing())) {
		      eval_cons = gensymed_symbol_1;
		    next_loop_1:
		      inline_note_reclaim_cons(eval_cons,Qeval);
		      if (EQ(eval_cons,gensymed_symbol_2))
			  goto end_1;
		      else if ( !TRUEP(eval_cons))
			  goto end_1;
		      else
			  eval_cons = CDR(eval_cons);
		      goto next_loop_1;
		    end_loop_1:
		    end_1:;
		  }
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_1 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_1) = gensymed_symbol_1;
		      temp_1 = Available_eval_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
		  }
		  else {
		      temp_1 = Available_eval_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = gensymed_symbol_1;
		      temp_1 = Available_eval_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
		  }
		  M_CDR(gensymed_symbol_2) = Nil;
	      }
	      CONTINUE_UNWINDING(0);
	      if (expiration_qm && EQ(type,Qtext))
		  gensymed_symbol = value;
	      if ( !TRUEP(value))
		  temp = Nil;
	      else {
		  temp = make_evaluation_value_1(value,type);
		  if (temp);
		  else
		      temp = Qnil;
	      }
	      if (gensymed_symbol)
		  reclaim_text_string(gensymed_symbol);
	      result = VALUES_1(temp);
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* INITIAL-TYPE-IN-BOX-VALUE */
Object initial_type_in_box_value(class_1)
    Object class_1;
{
    x_note_fn_call(228,55);
    return VALUES_1(Nil);
}

/* GET-TYPE-IN-BOX-VALUE */
Object get_type_in_box_value(type_in_box)
    Object type_in_box;
{
    Object temp;

    x_note_fn_call(228,56);
    temp = type_in_box_value(type_in_box);
    return VALUES_1(temp);
}

static Object Qtype_in_box_input_value;  /* type-in-box-input-value */

/* SET-TYPE-IN-BOX-VALUE */
Object set_type_in_box_value(type_in_box,new_value)
    Object type_in_box, new_value;
{
    x_note_fn_call(228,57);
    change_slot_value(3,type_in_box,Qtype_in_box_input_value,
	    CONSP(new_value) && EQ(M_CDR(new_value),Qtruth_value) ? 
	    make_slot_constant(CAR(new_value),CDR(new_value),Nil) : 
	    FIXNUMP(new_value) || new_value && SYMBOLP(new_value) ? 
	    new_value : copy_evaluation_value_1(new_value));
    return VALUES_1(Nil);
}

/* INITIAL-ITEM-COLOR-PATTERN */
Object initial_item_color_pattern(class_1)
    Object class_1;
{
    x_note_fn_call(228,58);
    return VALUES_1(Nil);
}

/* GET-ITEM-COLOR-PATTERN */
Object get_item_color_pattern(item)
    Object item;
{
    Object sub_class_bit_vector, temp_1, color_pattern, exported_color_pattern;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(228,59);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Type_in_box_class_description,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    if (temp)
	temp_1 = allocate_evaluation_structure(Nil);
    else {
	color_pattern = get_color_pattern_of_item(5,item,Nil,Nil,Nil,
		Item_color_pattern_returns_overrides_only_p);
	exported_color_pattern = export_color_pattern(color_pattern);
	reclaim_slot_value_tree_1(color_pattern);
	temp_1 = exported_color_pattern;
    }
    return VALUES_1(temp_1);
}

static Object Qmissing_color_region;  /* missing-color-region */

static Object Qunnamed_color_region;  /* unnamed-color-region */

static Object Qillegal_colors;     /* illegal-colors */

/* SET-ITEM-COLOR-PATTERN */
Object set_item_color_pattern(item,new_color_pattern_structure)
    Object item, new_color_pattern_structure;
{
    Object note_as_kb_state_change_qm, new_color_pattern_or_error, temp;
    Object color_change_error_qm, type_of_error, error_args;
    Declare_special(1);

    x_note_fn_call(228,60);
    note_as_kb_state_change_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      new_color_pattern_or_error = new_color_pattern_structure ? 
	      import_color_pattern(new_color_pattern_structure) : Qnil;
      temp = CAR(new_color_pattern_or_error);
      color_change_error_qm = SYMBOLP(temp) ? new_color_pattern_or_error : 
	      change_color_of_item(item,Note_as_kb_state_change_qm,Nil,
	      new_color_pattern_or_error);
      if ( !TRUEP(color_change_error_qm))
	  temp = reclaim_slot_value_tree_1(new_color_pattern_or_error);
      else {
	  type_of_error = M_CAR(color_change_error_qm);
	  error_args = M_CDR(color_change_error_qm);
	  reclaim_gensym_cons_1(color_change_error_qm);
	  if (EQ(type_of_error,Qmissing_color_region))
	      temp = missing_color_region_error(item,error_args);
	  else if (EQ(type_of_error,Qunnamed_color_region))
	      temp = unnamed_color_region_error(item,error_args);
	  else if (EQ(type_of_error,Qillegal_colors))
	      temp = illegal_colors_error(error_args);
	  else
	      temp = Nil;
      }
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant;     /* "Cannot change the ~a region of ~NF.  The class definition for ~a ~
				    *      does not have a region named ~a."
				    */

/* MISSING-COLOR-REGION-ERROR */
Object missing_color_region_error(entity,region)
    Object entity, region;
{
    x_note_fn_call(228,61);
    return tformat_text_string(5,string_constant,region,entity,
	    ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L),region);
}

static Object string_constant_1;   /* "Cannot change an unnamed color region in ~NF using its color name ~
				    *        (~a).  Unnamed color regions cannot be changed."
				    */

/* UNNAMED-COLOR-REGION-ERROR */
Object unnamed_color_region_error(entity,region)
    Object entity, region;
{
    x_note_fn_call(228,62);
    return tformat_text_string(3,string_constant_1,entity,region);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object string_constant_2;   /* " are illegal colors" */

static Object string_constant_3;   /* " is an illegal color" */

/* ILLEGAL-COLORS-ERROR */
Object illegal_colors_error(illegal_colors)
    Object illegal_colors;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object remaining_colors, remaining_colors_without_duplicates, ab_loopvar_;
    Object ab_loopvar__1, previous_illegal_colors, sublist;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(228,63);
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
	      remaining_colors = illegal_colors;
	      remaining_colors_without_duplicates = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	    next_loop:
	      if ( !TRUEP(remaining_colors))
		  goto end_loop;
	      previous_illegal_colors = illegal_colors;
	    next_loop_1:
	      if ( !TRUEP(previous_illegal_colors))
		  goto end_loop_1;
	      if (EQ(previous_illegal_colors,remaining_colors))
		  goto end_loop_1;
	      if (EQ(CAR(previous_illegal_colors),CAR(remaining_colors))) {
		  temp = TRUEP(Nil);
		  goto end_1;
	      }
	      previous_illegal_colors = M_CDR(previous_illegal_colors);
	      goto next_loop_1;
	    end_loop_1:
	      temp = TRUEP(T);
	      goto end_1;
	      temp = TRUEP(Qnil);
	    end_1:;
	      if (temp) {
		  ab_loopvar__1 = gensym_cons_1(CAR(remaining_colors),Nil);
		  if (ab_loopvar_)
		      M_CDR(ab_loopvar_) = ab_loopvar__1;
		  else
		      remaining_colors_without_duplicates = ab_loopvar__1;
		  ab_loopvar_ = ab_loopvar__1;
	      }
	      remaining_colors = M_CDR(remaining_colors);
	      goto next_loop;
	    end_loop:
	      sublist = remaining_colors_without_duplicates;
	    next_loop_2:
	      if ( !TRUEP(sublist))
		  goto end_loop_2;
	      write_evaluation_value(1,CAR(sublist));
	      if ( !TRUEP(CDR(sublist)));
	      else if ( !TRUEP(CDDR(sublist)))
		  twrite_beginning_of_wide_string(array_constant,
			  FIX((SI_Long)5L));
	      else
		  twrite_beginning_of_wide_string(array_constant_1,
			  FIX((SI_Long)2L));
	      sublist = M_CDR(sublist);
	      goto next_loop_2;
	    end_loop_2:;
	      twrite_general_string(CDR(remaining_colors_without_duplicates) 
		      ? string_constant_2 : string_constant_3);
	      reclaim_gensym_list_1(remaining_colors_without_duplicates);
	      reclaim_gensym_list_1(illegal_colors);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INITIAL-LAYER-POSITION */
Object initial_layer_position(class_1)
    Object class_1;
{
    x_note_fn_call(228,64);
    return VALUES_1(Nil);
}

/* GET-LAYER-POSITION */
Object get_layer_position(block)
    Object block;
{
    Object temp;

    x_note_fn_call(228,65);
    temp = g2_get_item_layer_position(block);
    return VALUES_1(temp);
}

/* INITIAL-NAME-BOX-ITEM */
Object initial_name_box_item(class_1)
    Object class_1;
{
    x_note_fn_call(228,66);
    return VALUES_1(Nil);
}

/* GET-NAME-BOX-ITEM */
Object get_name_box_item(entity)
    Object entity;
{
    Object temp;

    x_note_fn_call(228,67);
    temp = get_name_box_if_any_qm(entity);
    return VALUES_1(temp);
}

/* INITIAL-ATTRIBUTE-DISPLAY-ITEMS */
Object initial_attribute_display_items(class_1)
    Object class_1;
{
    x_note_fn_call(228,68);
    return VALUES_1(Nil);
}

/* GET-ATTRIBUTE-DISPLAY-ITEMS */
Object get_attribute_display_items(entity)
    Object entity;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object subblocks, ab_loopvar_, ab_loopvar__1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,69);
    gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    subblocks = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
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
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
    if ((temp ? TRUEP(attribute_display_p(subblock)) : TRUEP(Nil)) ? 
	    TRUEP(serve_item_p(subblock)) : TRUEP(Nil)) {
	ab_loopvar__1 = eval_cons_1(subblock,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    subblocks = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if (subblocks) {
	temp_1 = allocate_evaluation_sequence(subblocks);
	goto end_1;
    }
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* INITIAL-REPRESENTATION-TYPE */
Object initial_representation_type(class_1)
    Object class_1;
{
    x_note_fn_call(228,70);
    return VALUES_1(Nil);
}

static Object Qconnection;         /* connection */

/* GET-REPRESENTATION-TYPE */
Object get_representation_type(item)
    Object item;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, temp_1;
    char temp;

    x_note_fn_call(228,71);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)52L),(SI_Long)1L);
	gensymed_symbol_1 = item;
	temp_1 = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	temp_1 = Qconnection;
    else
	temp_1 = Qnil;
    return VALUES_1(temp_1);
}

/* INITIAL-CONNECTION-IS-DIRECTED */
Object initial_connection_is_directed(class_1)
    Object class_1;
{
    x_note_fn_call(228,72);
    return VALUES_1(Nil);
}

/* GET-CONNECTION-IS-DIRECTED */
Object get_connection_is_directed(connection)
    Object connection;
{
    Object temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(228,73);
    connection = ISVREF(connection,(SI_Long)21L);
    gensymed_symbol =  !((SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)1L)) ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	temp = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    return VALUES_1(temp);
}

/* INITIAL-CONNECTION-POSITION-SEQUENCE */
Object initial_connection_position_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(228,74);
    return VALUES_1(Nil);
}

/* GET-CONNECTION-POSITION-SEQUENCE */
Object get_connection_position_sequence(connection)
    Object connection;
{
    Object temp;

    x_note_fn_call(228,75);
    temp = export_connection_position_sequence(ISVREF(connection,
	    (SI_Long)21L));
    return VALUES_1(temp);
}

/* INITIAL-TEXT */
Object initial_text(class_1)
    Object class_1;
{
    x_note_fn_call(228,76);
    return VALUES_1(Nil);
}

/* GET-TEXT */
Object get_text(item)
    Object item;
{
    Object text_or_error;

    x_note_fn_call(228,77);
    text_or_error = get_text_of_attribute(item,Qtext,ISVREF(ISVREF(item,
	    (SI_Long)1L),(SI_Long)1L));
    return VALUES_1(SYMBOLP(text_or_error) ? Nil : text_or_error);
}

/* INITIAL-TYPE-IN-BOX-VARIABLE-OR-PARAMETER */
Object initial_type_in_box_variable_or_parameter(class_1)
    Object class_1;
{
    x_note_fn_call(228,78);
    return VALUES_1(Nil);
}

/* GET-TYPE-IN-BOX-VARIABLE-OR-PARAMETER */
Object get_type_in_box_variable_or_parameter(tib)
    Object tib;
{
    Object slot_value, current_computation_frame, temp;
    Declare_special(1);

    x_note_fn_call(228,79);
    slot_value = ISVREF(tib,(SI_Long)21L);
    current_computation_frame = tib;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      temp = evaluate_designation(slot_value,Nil);
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* INITIAL-STRIP-TEXT-MARK */
Object initial_strip_text_mark(class_1)
    Object class_1;
{
    x_note_fn_call(228,80);
    return VALUES_1(Nil);
}

/* GET-STRIP-TEXT-MARK */
Object get_strip_text_mark(item)
    Object item;
{
    x_note_fn_call(228,81);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)2097152L) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

/* SET-STRIP-TEXT-MARK */
Object set_strip_text_mark(item,new_state)
    Object item, new_state;
{
    x_note_fn_call(228,82);
    if (evaluation_truth_value_is_true_p(new_state))
	set_stripping_flags_as_specified(item,FIX((SI_Long)1L),
		FIX((SI_Long)0L));
    else
	set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

/* INITIAL-DO-NOT-STRIP-TEXT-MARK */
Object initial_do_not_strip_text_mark(class_1)
    Object class_1;
{
    x_note_fn_call(228,83);
    return VALUES_1(Nil);
}

/* GET-DO-NOT-STRIP-TEXT-MARK */
Object get_do_not_strip_text_mark(item)
    Object item;
{
    x_note_fn_call(228,84);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)4194304L) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

/* SET-DO-NOT-STRIP-TEXT-MARK */
Object set_do_not_strip_text_mark(item,new_state)
    Object item, new_state;
{
    x_note_fn_call(228,85);
    if (evaluation_truth_value_is_true_p(new_state))
	set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)1L));
    else
	set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-SYSTEM-ITEM */
Object get_workspace_representation_type_for_system_item(system_item)
    Object system_item;
{
    x_note_fn_call(228,86);
    return VALUES_1(Nil);
}

/* ACCEPTS-CONNECTIONS-P */
Object accepts_connections_p(entity)
    Object entity;
{
    Object class_description, inheritance_path, class_1, ab_loop_list_;
    Object ab_loop_it_;
    char temp;

    x_note_fn_call(228,87);
    class_description = ISVREF(entity,(SI_Long)1L);
    inheritance_path = ISVREF(class_description,(SI_Long)2L);
    class_1 = Nil;
    ab_loop_list_ = Classes_that_do_not_normally_connect;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = memq_function(class_1,inheritance_path);
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    return VALUES_1( !temp ? T : Nil);
}

static Object Qicon_with_connections;  /* icon-with-connections */

static Object Qicon_without_connections;  /* icon-without-connections */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-ENTITY */
Object get_workspace_representation_type_for_entity(entity)
    Object entity;
{
    x_note_fn_call(228,88);
    if (accepts_connections_p(entity))
	return VALUES_1(Qicon_with_connections);
    else
	return VALUES_1(Qicon_without_connections);
}

static Object Qloose_end;          /* loose-end */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-LOOSE-END */
Object get_workspace_representation_type_for_loose_end(loose_end)
    Object loose_end;
{
    x_note_fn_call(228,89);
    return VALUES_1(Qloose_end);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CONNECTION */
Object get_workspace_representation_type_for_connection(connection)
    Object connection;
{
    x_note_fn_call(228,90);
    return VALUES_1(Qconnection);
}

static Object Qtext_box;           /* text-box */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TEXT-BOX */
Object get_workspace_representation_type_for_text_box(text_box)
    Object text_box;
{
    x_note_fn_call(228,91);
    return VALUES_1(Qtext_box);
}

static Object Qattribute_display;  /* attribute-display */

static Object Qshort_representation;  /* short-representation */

static Object Qclassic_attribute_table;  /* classic-attribute-table */

static Object Qattribute_table_with_header;  /* attribute-table-with-header */

static Object Qattribute_table;    /* attribute-table */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TABLE */
Object get_workspace_representation_type_for_table(table)
    Object table;
{
    x_note_fn_call(228,92);
    if (attribute_display_p(table))
	return VALUES_1(Qattribute_display);
    else if (short_representation_p(table))
	return VALUES_1(Qshort_representation);
    else if (classic_attribute_table_p(table))
	return VALUES_1(Qclassic_attribute_table);
    else if (attribute_table_with_header_p(table))
	return VALUES_1(Qattribute_table_with_header);
    else if (attribute_table_p(table))
	return VALUES_1(Qattribute_table);
    else
	return VALUES_1(Qnil);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-READOUT-TABLE */
Object get_workspace_representation_type_for_readout_table(readout_table)
    Object readout_table;
{
    x_note_fn_call(228,93);
    return VALUES_1(Qattribute_table);
}

static Object Qdial;               /* dial */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-DIAL */
Object get_workspace_representation_type_for_dial(dial)
    Object dial;
{
    x_note_fn_call(228,94);
    return VALUES_1(Qdial);
}

static Object Qmeter;              /* meter */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-METER */
Object get_workspace_representation_type_for_meter(meter)
    Object meter;
{
    x_note_fn_call(228,95);
    return VALUES_1(Qmeter);
}

static Object Qtrend_chart;        /* trend-chart */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TREND-CHART */
Object get_workspace_representation_type_for_trend_chart(trend_chart)
    Object trend_chart;
{
    x_note_fn_call(228,96);
    return VALUES_1(Qtrend_chart);
}

static Object Qgraph;              /* graph */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-GRAPH */
Object get_workspace_representation_type_for_graph(graph)
    Object graph;
{
    x_note_fn_call(228,97);
    return VALUES_1(Qgraph);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CHART */
Object get_workspace_representation_type_for_chart(chart)
    Object chart;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(228,98);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      result = VALUES_1(Qchart);
    POP_SPECIAL();
    return result;
}

static Object Qfreeform_table;     /* freeform-table */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-FREEFORM-TABLE */
Object get_workspace_representation_type_for_freeform_table(freeform_table)
    Object freeform_table;
{
    x_note_fn_call(228,99);
    return VALUES_1(Qfreeform_table);
}

static Object Qaction_button;      /* action-button */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-ACTION-BUTTON */
Object get_workspace_representation_type_for_action_button(action_button)
    Object action_button;
{
    x_note_fn_call(228,100);
    return VALUES_1(Qaction_button);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-RADIO-BUTTON */
Object get_workspace_representation_type_for_radio_button(radio_button)
    Object radio_button;
{
    x_note_fn_call(228,101);
    return VALUES_1(Qradio_button);
}

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CHECK-BOX */
Object get_workspace_representation_type_for_check_box(check_box)
    Object check_box;
{
    x_note_fn_call(228,102);
    return VALUES_1(Qcheck_box);
}

static Object Qslider;             /* slider */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-SLIDER */
Object get_workspace_representation_type_for_slider(slider)
    Object slider;
{
    x_note_fn_call(228,103);
    return VALUES_1(Qslider);
}

static Object Qtype_in_box;        /* type-in-box */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TYPE-IN-BOX */
Object get_workspace_representation_type_for_type_in_box(type_in_box)
    Object type_in_box;
{
    x_note_fn_call(228,104);
    return VALUES_1(Qtype_in_box);
}

static Object Qkb_workspace;       /* kb-workspace */

/* GET-WORKSPACE-REPRESENTATION-TYPE-FOR-KB-WORKSPACE */
Object get_workspace_representation_type_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    x_note_fn_call(228,105);
    return VALUES_1(Qkb_workspace);
}

static Object Qws_representation_type;  /* ws-representation-type */

/* GET-THING-SPECIFIC-INFO */
Object get_thing_specific_info(thing,representation_type_name)
    Object thing, representation_type_name;
{
    Object ws_representation_type, property_getter, additional_properties;
    Object gensymed_symbol, svref_arg_1;
    SI_Long gensymed_symbol_1, svref_arg_2;

    x_note_fn_call(228,106);
    ws_representation_type = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(representation_type_name),
	    Qws_representation_type);
    property_getter = ws_representation_type ? 
	    ISVREF(ws_representation_type,(SI_Long)4L) : Qnil;
    if (property_getter)
	additional_properties = FUNCALL_1(property_getter,thing);
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	additional_properties = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    return VALUES_1(additional_properties);
}

/* GET-ITEM-SPECIFIC-INFO */
Object get_item_specific_info(item)
    Object item;
{
    Object gensymed_symbol, gensymed_symbol_1, representation_type_name;

    x_note_fn_call(228,107);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)52L),(SI_Long)1L);
    gensymed_symbol_1 = item;
    representation_type_name = inline_funcall_1(gensymed_symbol,
	    gensymed_symbol_1);
    return get_thing_specific_info(item,representation_type_name);
}

/* GET-BOUNDS-OF-THING */
Object get_bounds_of_thing(thing)
    Object thing;
{
    Object x2;
    char temp;

    x_note_fn_call(228,108);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return get_item_bounds(thing);
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* GET-ITEM-BOUNDS */
Object get_item_bounds(item)
    Object item;
{
    Object gensymed_symbol, temp, temp_1, temp_2;
    SI_Long gensymed_symbol_1;

    x_note_fn_call(228,109);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    temp_1 = FIX( - gensymed_symbol_1);
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    return make_structure_from_dimensions(temp,temp_1,temp_2,FIX( - 
	    gensymed_symbol_1));
}

/* GET-POSITION-OF-THING */
Object get_position_of_thing(thing)
    Object thing;
{
    Object x2;
    char temp;

    x_note_fn_call(228,110);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return get_item_position(thing);
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return export_connection_position_sequence(thing);
    else
	return VALUES_1(Nil);
}

/* EXPORT-CONNECTION-POSITION-SEQUENCE */
Object export_connection_position_sequence(connection)
    Object connection;
{
    Object connection_vertices_in_workspace_1, tmplist, result_1, x, y;
    Object ab_loop_list_, temp;

    x_note_fn_call(228,111);
    connection_vertices_in_workspace_1 = 
	    connection_vertices_in_workspace(connection);
    tmplist = Nil;
    result_1 = Nil;
    x = Nil;
    y = Nil;
    ab_loop_list_ = connection_vertices_in_workspace_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    x = CAR(temp);
    temp = CAR(ab_loop_list_);
    y = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tmplist = eval_cons_1(x,tmplist);
    tmplist = eval_cons_1(FIXNUM_NEGATE(y),tmplist);
    goto next_loop;
  end_loop:
    result_1 = allocate_evaluation_sequence(nreverse(tmplist));
    reclaim_gensym_tree_1(connection_vertices_in_workspace_1);
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object Qxpos;               /* xpos */

static Object Qypos;               /* ypos */

/* GET-ITEM-POSITION */
Object get_item_position(item)
    Object item;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,112);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qxpos;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qxpos;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = item_x_position(item);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = item_x_position(item);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qypos;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qypos;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = item_y_position(item);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = item_y_position(item);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* EXPORT-COLOR-PATTERN */
Object export_color_pattern(color_pattern)
    Object color_pattern;
{
    Object color_pattern_list, region, color, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(228,113);
    color_pattern_list = Nil;
    region = Nil;
    color = Nil;
    ab_loop_list_ = color_pattern;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region = CAR(ab_loop_desetq_);
    color = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (color) {
	color_pattern_list = eval_cons_1(region,color_pattern_list);
	color_pattern_list = eval_cons_1(color,color_pattern_list);
    }
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_structure(nreverse(color_pattern_list));
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qbackground;         /* background */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

/* IMPORT-COLOR-PATTERN */
Object import_color_pattern(color_pattern_structure)
    Object color_pattern_structure;
{
    Object color_pattern, bad_colors_qm, gensymed_symbol, held_vector, region;
    Object attribute_value, color, temp;
    SI_Long next_index, length_1, gensymed_symbol_1;

    x_note_fn_call(228,114);
    color_pattern = Nil;
    bad_colors_qm = Nil;
    gensymed_symbol = color_pattern_structure;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    region = Nil;
    attribute_value = Nil;
    color = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    region = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    color = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    if (SYMBOLP(color) && (EQ(color,Qforeground) || EQ(color,Qbackground) 
	    || EQ(color,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
	    Qcolor_value_vector_index_and_intensity) || rgb_color_p(color)))
	color_pattern = slot_value_cons_1(slot_value_cons_1(region,color),
		color_pattern);
    else
	bad_colors_qm = gensym_cons_1(color,bad_colors_qm);
    goto next_loop;
  end_loop:
    if (bad_colors_qm) {
	reclaim_slot_value(color_pattern);
	bad_colors_qm = gensym_cons_1(Qillegal_colors,bad_colors_qm);
	temp = bad_colors_qm;
	goto end_1;
    }
    else {
	temp = nreverse(color_pattern);
	goto end_1;
    }
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

static Object Qvariables;          /* variables */

static Object Qicon_color_pattern;  /* icon-color-pattern */

static Object Qorientation;        /* orientation */

static Object Qvariable_overrides;  /* variable-overrides */

static Object Qregion_overrides;   /* region-overrides */

/* EXPORT-ATTRIBUTES-PLIST */
Object export_attributes_plist(attributes_plist)
    Object attributes_plist;
{
    Object orientation, variable_overrides, region_overrides, gensymed_symbol;
    Object temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,115);
    orientation = getfq_function_no_default(attributes_plist,
	    Qreflection_and_rotation);
    variable_overrides = 
	    allocate_evaluation_structure(copy_tree_including_leaves_using_eval_conses(getfq_function_no_default(attributes_plist,
	    Qvariables)));
    region_overrides = 
	    export_color_pattern(getfq_function_no_default(attributes_plist,
	    Qicon_color_pattern));
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qorientation;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qorientation;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = orientation;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = orientation;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qvariable_overrides;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qvariable_overrides;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = variable_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = variable_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qregion_overrides;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qregion_overrides;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = region_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = region_overrides;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qicp;                /* icp */

/* GET-LIST-OF-V5-MODE-CLIENTS */
Object get_list_of_v5_mode_clients()
{
    Object workstation, ab_loop_list_, gensym_window, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(228,116);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if (ISVREF(gensym_window,(SI_Long)33L) && EQ(ISVREF(gensym_window,
	    (SI_Long)1L),Qicp)) {
	ab_loopvar__2 = gensym_cons_1(ISVREF(ISVREF(gensym_window,
		(SI_Long)12L),(SI_Long)2L),Nil);
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

/* MAYBE-RECLAIM-UPDATE-INFO */
Object maybe_reclaim_update_info(cons_containing_reference_count,update_info)
    Object cons_containing_reference_count, update_info;
{
    Object car_new_value;

    x_note_fn_call(228,117);
    car_new_value = FIXNUM_SUB1(CAR(cons_containing_reference_count));
    M_CAR(cons_containing_reference_count) = car_new_value;
    if ((SI_Long)0L == IFIX(M_CAR(cons_containing_reference_count))) {
	reclaim_gensym_tree_1(update_info);
	reclaim_gensym_cons_1(cons_containing_reference_count);
    }
    return VALUES_1(Nil);
}

/* GET-SLOT-INIT-FORM-DEFINED-BY-CLASS */
Object get_slot_init_form_defined_by_class(class_name,slot_name)
    Object class_name, slot_name;
{
    Object class_description, slot_description, slot_init_form;

    x_note_fn_call(228,118);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop) && (memq_function(slot_name,
	    ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)7L)) || 
	    memq_function(slot_name,
	    ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)8L)))) {
	class_description = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	slot_description = class_description ? 
		get_slot_description_of_class_description_function(slot_name,
		class_description,Nil) : Qnil;
	slot_init_form = slot_description ? ISVREF(slot_description,
		(SI_Long)6L) : Qnil;
	return VALUES_1(slot_init_form);
    }
    else
	return VALUES_1(Nil);
}

static Object Qicon_description;   /* icon-description */

/* GET-DRAWING-DESCRIPTION-SLOT-NAME-FOR-CLASS */
Object get_drawing_description_slot_name_for_class(class_name)
    Object class_name;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(228,119);
    sub_class_bit_vector = 
	    ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
    if (temp)
	return VALUES_1(Qcross_section_pattern);
    else
	return VALUES_1(Qicon_description);
}

/* SLOT-INIT-FORM-DRAWING-DESCRIPTION */
Object slot_init_form_drawing_description(slot_init_form,slot_name)
    Object slot_init_form, slot_name;
{
    Object line_drawing_description;

    x_note_fn_call(228,120);
    if (slot_init_form) {
	if (EQ(slot_name,Qicon_description)) {
	    line_drawing_description = 
		    copy_tree_using_gensym_conses_1(ISVREF(slot_init_form,
		    (SI_Long)8L));
	    line_drawing_description = gensym_cons_1(ISVREF(slot_init_form,
		    (SI_Long)2L),line_drawing_description);
	    line_drawing_description = gensym_cons_1(ISVREF(slot_init_form,
		    (SI_Long)1L),line_drawing_description);
	    return VALUES_1(line_drawing_description);
	}
	else if (EQ(slot_name,Qcross_section_pattern))
	    return copy_tree_using_gensym_conses_1(slot_init_form);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-DRAWING-DESCRIPTION-DEFINED-BY-CLASS */
Object get_drawing_description_defined_by_class(class_name)
    Object class_name;
{
    Object slot_name, slot_init_form, drawing_description;

    x_note_fn_call(228,121);
    slot_name = get_drawing_description_slot_name_for_class(class_name);
    slot_init_form = get_slot_init_form_defined_by_class(class_name,slot_name);
    drawing_description = 
	    slot_init_form_drawing_description(slot_init_form,slot_name);
    return VALUES_1(drawing_description);
}

static Object Qui_client_interface;  /* ui-client-interface */

/* UI-CLIENT-INTERFACE-P-FUNCTION */
Object ui_client_interface_p_function(interface_1)
    Object interface_1;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(228,122);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qui_client_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(interface_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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

static Object Qcallback_representation;  /* callback-representation */

/* RECLAIM-UI-CLIENT-INTERFACE-SESSIONS-VALUE */
Object reclaim_ui_client_interface_sessions_value(sessions,interface_1)
    Object sessions, interface_1;
{
    Object session, ab_loop_list_, representations_list, representation;
    Object ab_loop_list__1, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,123);
    session = Nil;
    ab_loop_list_ = sessions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    session = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    representations_list = copy_list_using_gensym_conses_1(ISVREF(session,
	    (SI_Long)9L));
    representation = Nil;
    ab_loop_list__1 = representations_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qcallback_representation,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp)
	delete_representation(1,representation);
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(representations_list);
    g2_release_ui_client_session(session);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(sessions);
    return VALUES_1(Nil);
}

/* RECLAIM-UI-CLIENT-SESSION-WORKSPACES-VALUE */
Object reclaim_ui_client_session_workspaces_value(workspaces,session)
    Object workspaces, session;
{
    x_note_fn_call(228,124);
    reclaim_slot_value_list_1(workspaces);
    return VALUES_1(Nil);
}

/* CLEANUP-PARENT-INTERFACE */
Object cleanup_parent_interface(interface_1,client_session)
    Object interface_1, client_session;
{
    Object temp;

    x_note_fn_call(228,125);
    if ( !((SI_Long)0L != (IFIX(ISVREF(interface_1,(SI_Long)5L)) & 
	    (SI_Long)512L))) {
	temp = delete_slot_value_element_1(client_session,
		ISVREF(interface_1,(SI_Long)26L));
	ISVREF(interface_1,(SI_Long)26L) = temp;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-UI-CLIENT-SESSION-PARENT-INTERFACE-VALUE */
Object reclaim_ui_client_session_parent_interface_value(interface_1,
	    client_session)
    Object interface_1, client_session;
{
    x_note_fn_call(228,126);
    cleanup_parent_interface(interface_1,client_session);
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "" */

/* ALREADY-IS-A-NAMED-UI-SESSION-FROM-THIS-CLIENT */
Object already_is_a_named_ui_session_from_this_client(gsi_interface,machine_id)
    Object gsi_interface, machine_id;
{
    Object sessions, session, ab_loop_list_, ab_loop_it_, list_1;

    x_note_fn_call(228,127);
    sessions = ISVREF(gsi_interface,(SI_Long)26L);
    if (sessions) {
	session = Nil;
	ab_loop_list_ = sessions;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	session = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ui_client_session_is_self_authorized_p(session)) {
	    list_1 = check_pulse_rate_limit(session);
	    ab_loop_it_ = string_equalw( !TRUEP(list_1) ? 
		    string_constant_4 : nth(FIX((SI_Long)10L),list_1),
		    machine_id);
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object Item_representation_slots_to_save_for_clear_kb = UNBOUND;

Object Callback_representation_slots_to_save_for_clear_kb = UNBOUND;

Object Showing_representation_slots_to_save_for_clear_kb = UNBOUND;

static Object Qitem_representation;  /* item-representation */

static Object Qshowing_representation;  /* showing-representation */

/* GET-SLOTS-TO-SAVE-IN-CLEAR-KB-FOR-REPRESENTATION */
Object get_slots_to_save_in_clear_kb_for_representation(representation)
    Object representation;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,128);
    gensymed_symbol = ISVREF(representation,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = Item_representation_slots_to_save_for_clear_kb;
    else {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qshowing_representation,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    temp_1 = Showing_representation_slots_to_save_for_clear_kb;
	else {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qcallback_representation,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		temp_1 = Callback_representation_slots_to_save_for_clear_kb;
	    else
		temp_1 = Qt;
	}
    }
    return VALUES_1(temp_1);
}

/* UI-CLIENT-INTERFACE-SESSIONS-FUNCTION */
Object ui_client_interface_sessions_function(interface_1)
    Object interface_1;
{
    x_note_fn_call(228,129);
    return VALUES_1(ISVREF(interface_1,(SI_Long)26L));
}

/* UI-CLIENT-SESSION-PARENT-INTERFACE-FUNCTION */
Object ui_client_session_parent_interface_function(session)
    Object session;
{
    x_note_fn_call(228,130);
    return VALUES_1(ISVREF(session,(SI_Long)26L));
}

/* UI-CLIENT-SESSION-LICENSE-LEVEL?-FUNCTION */
Object ui_client_session_license_level_qm_function(session)
    Object session;
{
    x_note_fn_call(228,131);
    return VALUES_1(ISVREF(session,(SI_Long)28L));
}

/* SET-UI-CLIENT-SESSION-LICENSE-LEVEL */
Object set_ui_client_session_license_level(session,level)
    Object session, level;
{
    x_note_fn_call(228,132);
    return VALUES_1(ISVREF(session,(SI_Long)28L) = level);
}

static Object Qui_client_session_user_is_valid;  /* ui-client-session-user-is-valid */

/* SET-UI-CLIENT-SESSION-USER-IS-VALID */
Object set_ui_client_session_user_is_valid(session,boolean_1)
    Object session, boolean_1;
{
    x_note_fn_call(228,133);
    return set_non_savable_lookup_slot_value(session,
	    Qui_client_session_user_is_valid,boolean_1);
}

static Object Qui_client_session_mode_is_valid;  /* ui-client-session-mode-is-valid */

/* SET-UI-CLIENT-SESSION-MODE-IS-VALID */
Object set_ui_client_session_mode_is_valid(session,boolean_1)
    Object session, boolean_1;
{
    x_note_fn_call(228,134);
    return set_non_savable_lookup_slot_value(session,
	    Qui_client_session_mode_is_valid,boolean_1);
}

/* UI-CLIENT-SESSION-STATUS-FUNCTION */
Object ui_client_session_status_function(session)
    Object session;
{
    x_note_fn_call(228,135);
    return VALUES_1(ISVREF(session,(SI_Long)29L));
}

static Object Qui_client_connection_status;  /* ui-client-connection-status */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* SET-UI-CLIENT-SESSION-STATUS */
Object set_ui_client_session_status(session,symbol)
    Object session, symbol;
{
    x_note_fn_call(228,136);
    ISVREF(session,(SI_Long)29L) = symbol;
    return update_subscriptions_from_virtual_attribute_change(session,
	    get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_connection_status),
	    Qvirtual_attribute,Nil),Nil);
}

/* UI-CLIENT-SESSION-NONCE-FUNCTION */
Object ui_client_session_nonce_function(session)
    Object session;
{
    x_note_fn_call(228,137);
    return VALUES_1(ISVREF(session,(SI_Long)30L));
}

static Object Kstack_error;        /* :stack-error */

static Object string_constant_5;   /* "Call to ~A not available to interface ~NF" */

static Object Qg2_allocate_session_id;  /* g2-allocate-session-id */

/* G2-ALLOCATE-SESSION-ID-SYSTEM-RPC-INTERNAL */
Object g2_allocate_session_id_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1, nonce;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,138);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_allocate_session_id,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    nonce = allocate_new_nonce();
	    result = copy_as_wide_string(ISVREF(nonce,(SI_Long)1L));
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* UI-CLIENT-SESSION-WORKSPACES-FUNCTION */
Object ui_client_session_workspaces_function(session)
    Object session;
{
    Object temp;

    x_note_fn_call(228,139);
    temp = ISVREF(session,(SI_Long)27L);
    return VALUES_1(temp);
}

/* G2-VALIDATE-NAMED-TW2-SYSTEM-RPC-INTERNAL */
Object g2_validate_named_tw2_system_rpc_internal(rpc_instance,nonce,
	    machine_id,code1,code2,code3,code4,code5,start_date,end_date,
	    desired_license_level)
    Object rpc_instance, nonce, machine_id, code1, code2, code3, code4, code5;
    Object start_date, end_date, desired_license_level;
{
    Object current_system_rpc_icp_socket_qm, gsi_interface_qm, authorized_qm;
    Object error_symbol_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,140);
    current_system_rpc_icp_socket_qm = ISVREF(rpc_instance,(SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
	    0);
      gsi_interface_qm = Current_system_rpc_icp_socket_qm ? 
	      ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : Qnil;
      result = compact_cons_pools_now_if_necessary(gsi_interface_qm,nonce,
	      machine_id,code1,code2,code3,code4,code5,start_date,end_date,
	      desired_license_level);
      MVS_2(result,authorized_qm,error_symbol_qm);
      return_from_system_defined_rpc(rpc_instance,
	      eval_cons_1(authorized_qm ? Evaluation_true_value : 
	      error_symbol_qm,Nil));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* G2-MAKE-UI-CLIENT-SESSION */
Object g2_make_ui_client_session(ui_client_interface,nonce,user_mode,
	    user_name,encoded_password,user_name_in_os_qm,language,
	    host_name,os_type,time_of_connection,workspace_showing_callback_qm)
    Object ui_client_interface, nonce, user_mode, user_name, encoded_password;
    Object user_name_in_os_qm, language, host_name, os_type;
    Object time_of_connection, workspace_showing_callback_qm;
{
    Object session_qm, error_symbol_qm, temp;
    Object result;

    x_note_fn_call(228,141);
    result = make_ui_client_session_fully_featured(ui_client_interface,
	    nonce,user_mode,user_name,encoded_password,user_name_in_os_qm,
	    language,host_name,os_type,time_of_connection);
    MVS_2(result,session_qm,error_symbol_qm);
    if (error_symbol_qm)
	return VALUES_2(session_qm,error_symbol_qm);
    else {
	temp =  !TRUEP(workspace_showing_callback_qm) ? Nil : 
		g2_subscribe_to_workspaces_showing(session_qm,
		workspace_showing_callback_qm,FIX((SI_Long)1L));
	return VALUES_3(session_qm,Nil,temp);
    }
}

static Object Qg2_make_ui_client_session;  /* g2-make-ui-client-session */

static Object Qsession_item;       /* session-item */

static Object Qerror_symbol;       /* error-symbol */

static Object Qworkspace_showing_handle;  /* workspace-showing-handle */

/* G2-MAKE-UI-CLIENT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_make_ui_client_session_system_rpc_internal(gensymed_symbol,nonce,
	    user_mode,user_name,encoded_password,user_name_in_os_qm,
	    language,host_name,os_type,workspace_showing_callback_qm)
    Object gensymed_symbol, nonce, user_mode, user_name, encoded_password;
    Object user_name_in_os_qm, language, host_name, os_type;
    Object workspace_showing_callback_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object gsi_interface, session, error_symbol_qm, showing_handle, temp_1;
    Object item_or_value, x2, svref_new_value, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp_2, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long svref_arg_2;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,142);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_make_ui_client_session,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gsi_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    result = g2_make_ui_client_session(gsi_interface,nonce,
		    user_mode,user_name,encoded_password,
		    user_name_in_os_qm,language,host_name,os_type,
		    Current_real_time,workspace_showing_callback_qm);
	    MVS_3(result,session,error_symbol_qm,showing_handle);
	    gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)6L + 
		    (SI_Long)1L));
	    gensymed_symbol_3 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_3 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(gensymed_symbol_3 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_3 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = Qsession_item;
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qsession_item;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = session;
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
		SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = session;
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
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = Qerror_symbol;
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qerror_symbol;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = error_symbol_qm;
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
		SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = error_symbol_qm;
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
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)7L)) = 
			Qworkspace_showing_handle;
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)5L)) = Qworkspace_showing_handle;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = showing_handle;
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
		SVREF(gensymed_symbol_1,FIX((SI_Long)8L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = showing_handle;
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
		SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    result = eval_cons_1(gensymed_symbol_1,Qab_structure);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_2 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_2;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qui_client_session;  /* ui-client-session */

/* MAKE-UI-CLIENT-SESSION-INTERNAL */
Object make_ui_client_session_internal()
{
    Object session, gensymed_symbol, gensymed_symbol_1;
    SI_Long svref_new_value;

    x_note_fn_call(228,143);
    session = make_frame(Qui_client_session);
    svref_new_value = IFIX(ISVREF(session,(SI_Long)5L)) | (SI_Long)524288L;
    ISVREF(session,(SI_Long)5L) = FIX(svref_new_value);
    set_permanent_and_propagate(session,Nil);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(session,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
    gensymed_symbol_1 = session;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(session);
}

static Object Qno_available_floating_licenses;  /* no-available-floating-licenses */

static Object Qui_client_session_user_mode;  /* ui-client-session-user-mode */

static Object Qspecific_language_for_this_ui_client_session_qm;  /* specific-language-for-this-ui-client-session? */

static Object Qui_client_session_time_of_last_connection;  /* ui-client-session-time-of-last-connection */

static Object Qtoo_many_login_attempts;  /* too-many-login-attempts */

/* MAKE-UI-CLIENT-SESSION-FULLY-FEATURED */
Object make_ui_client_session_fully_featured(client_interface,nonce,
	    user_mode,user_name,nonce_encoded_password,user_name_in_os_qm,
	    language,host_name,os_type,time_of_connection)
    Object client_interface, nonce, user_mode, user_name;
    Object nonce_encoded_password, user_name_in_os_qm, language, host_name;
    Object os_type, time_of_connection;
{
    Object session_from_previous_attempt_qm, session, error_symbol_qm;
    Object no_room_at_the_inn_qm, nonce_data;
    Object slot_value_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, svref_new_value;
    char temp;
    Object result;

    x_note_fn_call(228,144);
    session_from_previous_attempt_qm = ui_client_session_for_nonce(nonce);
    session = session_from_previous_attempt_qm;
    if (session);
    else
	session = make_ui_client_session_internal();
    error_symbol_qm = Nil;
    no_room_at_the_inn_qm = Nil;
    nonce_data = Nil;
    if ( !TRUEP(error_symbol_qm)) {
	result = data_for_valid_nonce(nonce);
	MVS_2(result,nonce_data,error_symbol_qm);
    }
    if ( !TRUEP(error_symbol_qm)) {
	ISVREF(session,(SI_Long)30L) = nonce;
	ISVREF(session,(SI_Long)26L) = client_interface;
	slot_value_modify_macro_using_test_arg_1 = session;
	car_1 = slot_value_modify_macro_using_test_arg_1;
	cdr_1 = ISVREF(client_interface,(SI_Long)26L);
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
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	svref_new_value = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
	ISVREF(client_interface,(SI_Long)26L) = svref_new_value;
    }
    if ( !(error_symbol_qm || 
		ui_client_session_is_self_authorized_p(session))) {
	no_room_at_the_inn_qm =  !TRUEP(some_floating_tw2_available_p()) ? 
		T : Nil;
	if (no_room_at_the_inn_qm)
	    error_symbol_qm = Qno_available_floating_licenses;
	else
	    set_ui_client_session_license_level(session,FIX((SI_Long)-1L));
    }
    if ( !TRUEP(error_symbol_qm)) {
	change_slot_value(3,session,Qui_client_session_user_mode,user_mode);
	ISVREF(session,(SI_Long)21L) = user_name;
	ISVREF(session,(SI_Long)23L) = nonce_encoded_password;
	ISVREF(session,(SI_Long)22L) = user_name_in_os_qm;
	change_slot_value(3,session,
		Qspecific_language_for_this_ui_client_session_qm,language);
	ISVREF(session,(SI_Long)24L) = host_name;
	ISVREF(session,(SI_Long)25L) = os_type;
	set_non_savable_lookup_slot_value(session,
		Qui_client_session_time_of_last_connection,
		copy_managed_float(time_of_connection));
    }
    if ( !TRUEP(error_symbol_qm)) {
	if ( !TRUEP(session_from_previous_attempt_qm))
	    SVREF(nonce_data,FIX((SI_Long)3L)) = session;
    }
    if ( !TRUEP(error_symbol_qm))
	error_symbol_qm = log_in_ui_client(nonce_data,session,user_name,
		nonce_encoded_password,user_mode);
    if (error_symbol_qm)
	set_ui_client_session_status(session,error_symbol_qm);
    if (no_room_at_the_inn_qm || EQ(error_symbol_qm,
		Qtoo_many_login_attempts)) {
	g2_release_ui_client_session(session);
	return VALUES_2(Nil,error_symbol_qm);
    }
    else if (error_symbol_qm)
	return VALUES_2(session,error_symbol_qm);
    else
	return VALUES_2(session,Nil);
}

/* G2-RELEASE-UI-CLIENT-SESSION */
Object g2_release_ui_client_session(client_session)
    Object client_session;
{
    x_note_fn_call(228,145);
    if ( !TRUEP(Deleting_ui_client_interfaces_for_clear_kb))
	log_out_ui_client(client_session);
    delete_frame(client_session);
    return VALUES_1(Nil);
}

static Object Qg2_release_ui_client_session;  /* g2-release-ui-client-session */

/* G2-RELEASE-UI-CLIENT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_release_ui_client_session_system_rpc_internal(gensymed_symbol,
	    client_session)
    Object gensymed_symbol, client_session;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp_1;
    Object error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,146);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_release_ui_client_session,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gensymed_symbol_1 = g2_release_ui_client_session(client_session);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* UI-CLIENT-SESSION-VALID-P */
Object ui_client_session_valid_p(session)
    Object session;
{
    Object temp;

    x_note_fn_call(228,147);
    temp = session_has_successfully_logged_in_p(session);
    return VALUES_1(temp);
}

static Object string_constant_6;   /* "session and interface do not match" */

static Object string_constant_7;   /* "session not logged in" */

/* CHECK-UI-CLIENT-SESSION-FOR-RPC-ACCESS */
Object check_ui_client_session_for_rpc_access(session)
    Object session;
{
    Object top_of_stack, message_1;

    x_note_fn_call(228,148);
    if (ui_client_session_doesnt_match_current_interface_p(session)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_6);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(ui_client_session_valid_p(session))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_7);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(Nil);
}

static Object Qinvalid_interface_class_for_rpc_call;  /* invalid-interface-class-for-rpc-call */

static Object string_constant_8;   /* "rpc call ~A not available to interface ~NF" */

/* RPC-INTERFACE-CLASS-OK? */
Object rpc_interface_class_ok_qm(rpc_instance,procedure_name,
	    interface_class_name)
    Object rpc_instance, procedure_name, interface_class_name;
{
    Object socket_qm, interface_1, gensymed_symbol, sub_class_bit_vector;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,149);
    socket_qm = ISVREF(rpc_instance,(SI_Long)2L);
    interface_1 = socket_qm ? ISVREF(socket_qm,(SI_Long)5L) : Qnil;
    temp =  !TRUEP(interface_1);
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(interface_class_name,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(interface_1,(SI_Long)1L),
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
	temp =  !temp;
    }
    if (temp) {
	system_rpc_error(rpc_instance,
		Qinvalid_interface_class_for_rpc_call,
		tformat_text_string(3,string_constant_8,procedure_name,
		interface_1));
	temp_1 = Nil;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

static Object Qsession_interface_mismatch;  /* session-interface-mismatch */

static Object string_constant_9;   /* "~S" */

static Object Qsession_not_logged_in;  /* session-not-logged-in */

/* UI-CLIENT-SESSION-OK-FOR-DEFUN-SYSTEM-RPC? */
Object ui_client_session_ok_for_defun_system_rpc_qm(session,rpc_instance,
	    call_sym)
    Object session, rpc_instance, call_sym;
{
    Object temp;

    x_note_fn_call(228,150);
    if ( !TRUEP(rpc_interface_class_ok_qm(rpc_instance,call_sym,
	    Qui_client_interface)))
	temp = Nil;
    else if (ui_client_session_doesnt_match_current_interface_p(session)) {
	system_rpc_error(rpc_instance,Qsession_interface_mismatch,
		tformat_text_string(2,string_constant_9,string_constant_6));
	temp = Nil;
    }
    else if ( !TRUEP(ui_client_session_valid_p(session))) {
	system_rpc_error(rpc_instance,Qsession_not_logged_in,
		tformat_text_string(2,string_constant_9,string_constant_7));
	temp = Nil;
    }
    else
	temp = T;
    return VALUES_1(temp);
}

/* UI-CLIENT-SESSION-DOESNT-MATCH-CURRENT-INTERFACE-P */
Object ui_client_session_doesnt_match_current_interface_p(session)
    Object session;
{
    Object temp;

    x_note_fn_call(228,151);
    temp = Current_system_rpc_icp_socket_qm ? ( 
	    !EQ(ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L),
	    ISVREF(session,(SI_Long)26L)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* FIND-FRAME-REPRESENTATION-FOR-THIS-SESSION */
Object find_frame_representation_for_this_session(session,frame,
	    representation_class)
    Object session, frame, representation_class;
{
    Object interface_1, representation, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,152);
    interface_1 = ISVREF(session,(SI_Long)26L);
    representation = Nil;
    ab_loop_list_ = ISVREF(frame,(SI_Long)9L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(representation_class,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp ? EQ(interface_1,
	    get_interface_from_representation(representation)) : TRUEP(Nil)) {
	temp_1 = representation;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* ANY-SESSION-WS-ASSOCIATIONS-REMAINING-P */
Object any_session_ws_associations_remaining_p(workspace,interface_1)
    Object workspace, interface_1;
{
    Object session, ab_loop_list_, ab_loop_it_, ws, ab_loop_list__1, temp;

    x_note_fn_call(228,153);
    session = Nil;
    ab_loop_list_ = ISVREF(interface_1,(SI_Long)26L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    session = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ws = Nil;
    ab_loop_list__1 = ISVREF(session,(SI_Long)27L);
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ws = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQ(ws,workspace) ? T : Nil;
    if (ab_loop_it_)
	goto end_1;
    goto next_loop_1;
  end_loop_1:
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* ASSOCIATE-WORKSPACE-WITH-UI-SESSION */
Object associate_workspace_with_ui_session(ui_client_session,workspace)
    Object ui_client_session, workspace;
{
    Object already_there_qm, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(228,154);
    already_there_qm = find(2,workspace,ISVREF(ui_client_session,
	    (SI_Long)27L));
    if ( !TRUEP(already_there_qm)) {
	slot_value_push_modify_macro_arg = workspace;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = ISVREF(ui_client_session,(SI_Long)27L);
	svref_new_value = slot_value_cons_1(car_1,cdr_1);
	ISVREF(ui_client_session,(SI_Long)27L) = svref_new_value;
    }
    return VALUES_1( !TRUEP(already_there_qm) ? T : Nil);
}

/* DISASSOCIATE-WORKSPACE-FROM-UI-SESSION */
Object disassociate_workspace_from_ui_session(ui_client_session,workspace)
    Object ui_client_session, workspace;
{
    Object svref_new_value;

    x_note_fn_call(228,155);
    if (find(2,workspace,ISVREF(ui_client_session,(SI_Long)27L))) {
	svref_new_value = delete_slot_value_element_1(workspace,
		ISVREF(ui_client_session,(SI_Long)27L));
	ISVREF(ui_client_session,(SI_Long)27L) = svref_new_value;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* INITIAL-UI-CLIENT-USER-MODE */
Object initial_ui_client_user_mode(class_1)
    Object class_1;
{
    x_note_fn_call(228,156);
    return VALUES_1(Nil);
}

static Object Qg2_user_mode;       /* g2-user-mode */

/* GET-UI-CLIENT-USER-MODE */
Object get_ui_client_user_mode(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,157);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = get_slot_value_function(client_item,
		Qui_client_session_user_mode,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = get_slot_value_function(client_item,Qg2_user_mode,Nil);
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* SET-UI-CLIENT-USER-MODE */
Object set_ui_client_user_mode(block,new_mode)
    Object block, new_mode;
{
    Object error_string_qm;
    Object result;

    x_note_fn_call(228,158);
    result = check_and_install_new_g2_user_mode_for_login(new_mode,block);
    error_string_qm = NTH_VALUE((SI_Long)1L, result);
    return VALUES_1(error_string_qm);
}

/* INITIAL-UI-CLIENT-USER-NAME */
Object initial_ui_client_user_name(class_1)
    Object class_1;
{
    x_note_fn_call(228,159);
    return VALUES_1(Nil);
}

static Object Qui_client_session_user_name;  /* ui-client-session-user-name */

static Object Qg2_user_name;       /* g2-user-name */

/* GET-UI-CLIENT-USER-NAME */
Object get_ui_client_user_name(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,160);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = get_slot_value_function(client_item,
		Qui_client_session_user_name,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = get_slot_value_function(client_item,Qg2_user_name,Nil);
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-REMOTE-HOST-NAME */
Object initial_ui_client_remote_host_name(class_1)
    Object class_1;
{
    x_note_fn_call(228,161);
    return VALUES_1(Nil);
}

static Object Qui_client_session_network_host_name_qm;  /* ui-client-session-network-host-name? */

static Object Qg2_window_network_host_name_qm;  /* g2-window-network-host-name? */

/* GET-UI-CLIENT-REMOTE-HOST-NAME */
Object get_ui_client_remote_host_name(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, host_text;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,162);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	host_text = get_slot_value_function(client_item,
		Qui_client_session_network_host_name_qm,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp)
	    host_text = get_slot_value_function(client_item,
		    Qg2_window_network_host_name_qm,Nil);
	else
	    host_text = Qt;
    }
    temp_1 = host_text ? copy_as_wide_string(host_text) : Qnil;
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-OPERATING-SYSTEM-TYPE */
Object initial_ui_client_operating_system_type(class_1)
    Object class_1;
{
    x_note_fn_call(228,163);
    return VALUES_1(Nil);
}

static Object Qui_client_session_os_type_qm;  /* ui-client-session-os-type? */

static Object Qg2_window_os_type_qm;  /* g2-window-os-type? */

/* GET-UI-CLIENT-OPERATING-SYSTEM-TYPE */
Object get_ui_client_operating_system_type(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,164);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = get_slot_value_function(client_item,
		Qui_client_session_os_type_qm,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = get_slot_value_function(client_item,
		    Qg2_window_os_type_qm,Nil);
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-TIME-OF-LAST-CONNECTION */
Object initial_ui_client_time_of_last_connection(class_1)
    Object class_1;
{
    x_note_fn_call(228,165);
    return VALUES_1(Nil);
}

static Object Qunix_time_qm;       /* unix-time? */

static Object Qg2_window_time_of_last_connection_qm;  /* g2-window-time-of-last-connection? */

/* GET-UI-CLIENT-TIME-OF-LAST-CONNECTION */
Object get_ui_client_time_of_last_connection(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object category_evaluator_interface, function, gensymed_symbol_5;
    Object gensymed_symbol_6, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,166);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunix_time_qm),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = get_slot_value_function(client_item,
		    Qui_client_session_time_of_last_connection,Nil);
	    gensymed_symbol_5 = client_item;
	    gensymed_symbol_6 = Nil;
	    temp_1 = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    temp_1 = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunix_time_qm),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol = function;
		gensymed_symbol_1 = get_slot_value_function(client_item,
			Qg2_window_time_of_last_connection_qm,Nil);
		gensymed_symbol_5 = client_item;
		gensymed_symbol_6 = Nil;
		temp_1 = inline_funcall_3(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_5,gensymed_symbol_6);
	    }
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM */
Object initial_ui_client_user_name_in_operating_system(class_1)
    Object class_1;
{
    x_note_fn_call(228,167);
    return VALUES_1(Nil);
}

static Object Qwhole_string_qm;    /* whole-string? */

static Object Qui_client_session_os_user_name_qm;  /* ui-client-session-os-user-name? */

static Object Qg2_window_os_user_name_qm;  /* g2-window-os-user-name? */

/* GET-UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM */
Object get_ui_client_user_name_in_operating_system(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object category_evaluator_interface, function, gensymed_symbol_5;
    Object gensymed_symbol_6, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,168);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string_qm),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = get_slot_value_function(client_item,
		    Qui_client_session_os_user_name_qm,Nil);
	    gensymed_symbol_5 = client_item;
	    gensymed_symbol_6 = Nil;
	    temp_1 = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    temp_1 = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string_qm),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol = function;
		gensymed_symbol_1 = get_slot_value_function(client_item,
			Qg2_window_os_user_name_qm,Nil);
		gensymed_symbol_5 = client_item;
		gensymed_symbol_6 = Nil;
		temp_1 = inline_funcall_3(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_5,gensymed_symbol_6);
	    }
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-SPECIFIC-LANGUAGE */
Object initial_ui_client_specific_language(class_1)
    Object class_1;
{
    x_note_fn_call(228,169);
    return VALUES_1(Nil);
}

static Object Qlanguage_qm;        /* language? */

static Object Qspecific_language_for_this_g2_window_qm;  /* specific-language-for-this-g2-window? */

/* GET-UI-CLIENT-SPECIFIC-LANGUAGE */
Object get_ui_client_specific_language(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object category_evaluator_interface, function, gensymed_symbol_5;
    Object gensymed_symbol_6, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,170);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlanguage_qm),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = get_slot_value_function(client_item,
		    Qspecific_language_for_this_ui_client_session_qm,Nil);
	    gensymed_symbol_5 = client_item;
	    gensymed_symbol_6 = Nil;
	    temp_1 = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else
	    temp_1 = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlanguage_qm),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol = function;
		gensymed_symbol_1 = get_slot_value_function(client_item,
			Qspecific_language_for_this_g2_window_qm,Nil);
		gensymed_symbol_5 = client_item;
		gensymed_symbol_6 = Nil;
		temp_1 = inline_funcall_3(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_5,gensymed_symbol_6);
	    }
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-CONNECTION-STATUS */
Object initial_ui_client_connection_status(class_1)
    Object class_1;
{
    x_note_fn_call(228,171);
    return VALUES_1(Nil);
}

static Object Qconnected;          /* connected */

static Object Qnot_connected;      /* not-connected */

static Object Qg2_connection_status;  /* g2-connection-status */

/* GET-UI-CLIENT-CONNECTION-STATUS */
Object get_ui_client_connection_status(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,172);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = ui_client_session_valid_p(client_item) ? Qconnected : 
		Qnot_connected;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = get_slot_value_function(client_item,
		    Qg2_connection_status,Nil);
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-USER-IS-VALID */
Object initial_ui_client_user_is_valid(class_1)
    Object class_1;
{
    x_note_fn_call(228,173);
    return VALUES_1(Nil);
}

static Object Qg2_window_user_is_valid;  /* g2-window-user-is-valid */

/* GET-UI-CLIENT-USER-IS-VALID */
Object get_ui_client_user_is_valid(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,174);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = get_slot_value_function(client_item,
		Qui_client_session_user_is_valid,Nil);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp_1 = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp_1 = Evaluation_false_value;
	else
	    temp_1 = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    gensymed_symbol = get_slot_value_function(client_item,
		    Qg2_window_user_is_valid,Nil);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp_1 = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp_1 = Evaluation_false_value;
	    else
		temp_1 = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-MODE-IS-VALID */
Object initial_ui_client_mode_is_valid(class_1)
    Object class_1;
{
    x_note_fn_call(228,175);
    return VALUES_1(Nil);
}

static Object Qg2_window_mode_is_valid;  /* g2-window-mode-is-valid */

/* GET-UI-CLIENT-MODE-IS-VALID */
Object get_ui_client_mode_is_valid(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,176);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = get_slot_value_function(client_item,
		Qui_client_session_mode_is_valid,Nil);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp_1 = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp_1 = Evaluation_false_value;
	else
	    temp_1 = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    gensymed_symbol = get_slot_value_function(client_item,
		    Qg2_window_mode_is_valid,Nil);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp_1 = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp_1 = Evaluation_false_value;
	    else
		temp_1 = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

/* INITIAL-UI-CLIENT-INTERFACE */
Object initial_ui_client_interface(class_1)
    Object class_1;
{
    x_note_fn_call(228,177);
    return VALUES_1(Nil);
}

/* GET-UI-CLIENT-INTERFACE */
Object get_ui_client_interface(client_session)
    Object client_session;
{
    Object temp;

    x_note_fn_call(228,178);
    temp = ISVREF(client_session,(SI_Long)26L);
    return VALUES_1(temp);
}

/* INITIAL-USES-FLOATING-LICENSE */
Object initial_uses_floating_license(class_1)
    Object class_1;
{
    x_note_fn_call(228,179);
    return VALUES_1(Nil);
}

/* GET-USES-FLOATING-LICENSE */
Object get_uses_floating_license(client_item)
    Object client_item;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    Object gensym_window_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(228,180);
    gensymed_symbol = ISVREF(client_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qui_client_session,
	    Class_description_gkbprop);
    if (gensymed_symbol_1) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = (SI_Long)-1L == 
		IFIX(ui_client_session_license_level_qm_function(client_item)) 
		? Evaluation_true_value : Evaluation_false_value;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	    gensym_window_qm = map_g2_window_to_gensym_window(client_item);
	    temp_1 = gensym_window_qm && (SI_Long)-1L == 
		    IFIX(ISVREF(gensym_window_qm,(SI_Long)16L)) ? 
		    Evaluation_true_value : Evaluation_false_value;
	}
	else
	    temp_1 = Qt;
    }
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_ui_client_test_mode_p, Qlocal_ui_client_test_mode_p);

/* WORKSPACE-SHOWING-ON-UI-CLIENT-P */
Object workspace_showing_on_ui_client_p(workspace)
    Object workspace;
{
    Object representation, ab_loop_list_, ab_loop_it_, gensymed_symbol;
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(228,181);
    representation = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)9L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qws_representation,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	    ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	}
	else
	    ab_loop_it_ = Nil;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qhide;               /* hide */

/* UPDATE-UI-CLIENT-FOR-HIDE */
Object update_ui_client_for_hide(client_session,workspace)
    Object client_session, workspace;
{
    Object current_frame_serial_number_on_entry, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations, representation, xa, ya;
    Object gensymed_symbol_4, car_new_value, argument_list, address, socket_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,182);
    if (Local_ui_client_test_mode_p)
	return VALUES_1(Nil);
    current_frame_serial_number_on_entry = 
	    copy_frame_serial_number(Current_frame_serial_number);
    frame_list = ISVREF(client_session,(SI_Long)9L);
    class_name = Qshowing_representation;
    new_list = Qnil;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp)
	new_list = gensym_cons_1(frame,new_list);
    goto next_loop;
  end_loop:
    representations = new_list;
    goto end_1;
    representations = Qnil;
  end_1:;
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(current_frame_serial_number_on_entry))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(current_frame_serial_number_on_entry,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(current_frame_serial_number_on_entry);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
	gensymed_symbol_4 = gensymed_symbol;
	M_CAR(gensymed_symbol_4) = Qhide;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	M_CAR(gensymed_symbol_4) = workspace;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	car_new_value = allocate_evaluation_structure(Nil);
	M_CAR(gensymed_symbol_4) = car_new_value;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	car_new_value = ISVREF(representation,(SI_Long)13L);
	M_CAR(gensymed_symbol_4) = car_new_value;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	car_new_value = ISVREF(representation,(SI_Long)12L);
	M_CAR(gensymed_symbol_4) = car_new_value;
	argument_list = gensymed_symbol;
	address = ISVREF(representation,(SI_Long)8L);
	socket_1 = getfq_function_no_default(address,Qsocket);
	callback_representation_fire_callback(representation,socket_1,
		argument_list);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(current_frame_serial_number_on_entry);
    reclaim_gensym_list_1(representations);
    return VALUES_1(Qnil);
}

static Object Qshow;               /* show */

static Object Qitem;               /* item */

static Object Qgo_to_item;         /* go-to-item */

static Object Qsymbolic_x_scale;   /* symbolic-x-scale */

static Object Qsymbolic_y_scale;   /* symbolic-y-scale */

static Object Qsymbolic_x_in_workspace;  /* symbolic-x-in-workspace */

static Object Qsymbolic_y_in_workspace;  /* symbolic-y-in-workspace */

static Object Qsymbolic_x_in_window;  /* symbolic-x-in-window */

static Object Qsymbolic_y_in_window;  /* symbolic-y-in-window */

static Object Qx_offset_units;     /* x-offset-units */

static Object Qy_offset_units;     /* y-offset-units */

static Object Qsymbolic_x_offset_direction;  /* symbolic-x-offset-direction */

static Object Qsymbolic_y_offset_direction;  /* symbolic-y-offset-direction */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Qx_in_workspace;     /* x-in-workspace */

static Object Qy_in_workspace;     /* y-in-workspace */

static Object Qx_in_window;        /* x-in-window */

static Object Qy_in_window;        /* y-in-window */

/* UPDATE-UI-CLIENT-FOR-SHOW */
Object update_ui_client_for_show varargs_1(int, n)
{
    Object block, workspace, client_session, go_to_block_qm;
    Object require_visibility_qm, symbolic_x_scale_qm, symbolic_y_scale_qm;
    Object symbolic_x_in_workspace_qm, symbolic_y_in_workspace_qm;
    Object symbolic_x_in_window_qm, symbolic_y_in_window_qm, x_offset_units_qm;
    Object symbolic_x_offset_direction_qm, y_offset_units_qm;
    Object symbolic_y_offset_direction_qm, x_magnification_qm;
    Object y_magnification_qm, x_in_workspace_qm, y_in_workspace_qm;
    Object x_in_window_qm, y_in_window_qm;
    Object current_frame_serial_number_on_entry, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations, representation, xa, ya;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_1, item_or_value, x2;
    Object temp_2, structure, temp_3, amf_available_array_cons_qm, amf_array;
    Object amf_result, new_float, argument_list, address, socket_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;
    double aref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(228,183);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    client_session = REQUIRED_ARG_nonrelocating();
    go_to_block_qm = REQUIRED_ARG_nonrelocating();
    require_visibility_qm = REQUIRED_ARG_nonrelocating();
    symbolic_x_scale_qm = REQUIRED_ARG_nonrelocating();
    symbolic_y_scale_qm = REQUIRED_ARG_nonrelocating();
    symbolic_x_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    symbolic_y_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    symbolic_x_in_window_qm = REQUIRED_ARG_nonrelocating();
    symbolic_y_in_window_qm = REQUIRED_ARG_nonrelocating();
    x_offset_units_qm = REQUIRED_ARG_nonrelocating();
    symbolic_x_offset_direction_qm = REQUIRED_ARG_nonrelocating();
    y_offset_units_qm = REQUIRED_ARG_nonrelocating();
    symbolic_y_offset_direction_qm = REQUIRED_ARG_nonrelocating();
    x_magnification_qm = REQUIRED_ARG_nonrelocating();
    y_magnification_qm = REQUIRED_ARG_nonrelocating();
    x_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    y_in_workspace_qm = REQUIRED_ARG_nonrelocating();
    x_in_window_qm = REQUIRED_ARG_nonrelocating();
    y_in_window_qm = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (Local_ui_client_test_mode_p)
	return VALUES_1(Nil);
    current_frame_serial_number_on_entry = 
	    copy_frame_serial_number(Current_frame_serial_number);
    frame_list = ISVREF(client_session,(SI_Long)9L);
    class_name = Qshowing_representation;
    new_list = Qnil;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp)
	new_list = gensym_cons_1(frame,new_list);
    goto next_loop;
  end_loop:
    representations = new_list;
    goto end_1;
    representations = Qnil;
  end_1:;
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(current_frame_serial_number_on_entry))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(current_frame_serial_number_on_entry,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(current_frame_serial_number_on_entry);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
	gensymed_symbol_4 = gensymed_symbol;
	M_CAR(gensymed_symbol_4) = Qshow;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	M_CAR(gensymed_symbol_4) = workspace;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	gensymed_symbol_5 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_5,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_5,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_5,FIX((SI_Long)3L)) = Qitem;
	else {
	    temp_1 = ISVREF(gensymed_symbol_5,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qitem;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = block;
	    if (item_or_value);
	    else
		item_or_value = Qnil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_1 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_5,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_5,(SI_Long)2L);
	    item_or_value = block;
	    if (item_or_value);
	    else
		item_or_value = Qnil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_2 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_5,FIX((SI_Long)5L)) = Qgo_to_item;
	else {
	    temp_1 = ISVREF(gensymed_symbol_5,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qgo_to_item;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_5,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = go_to_block_qm;
	    if (item_or_value);
	    else
		item_or_value = Nil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_1 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_5,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_5,(SI_Long)2L);
	    item_or_value = go_to_block_qm;
	    if (item_or_value);
	    else
		item_or_value = Nil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_2 = temp ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
	}
	structure = eval_cons_1(gensymed_symbol_5,Qab_structure);
	if (symbolic_x_scale_qm) {
	    if (FIXNUMP(symbolic_x_scale_qm))
		temp_3 = symbolic_x_scale_qm;
	    else if ( !TRUEP(symbolic_x_scale_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_x_scale_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_x_scale_qm))
		temp_3 = symbolic_x_scale_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_x_scale_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_scale_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_x_scale_qm);
	    else if (FLOATP(symbolic_x_scale_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(symbolic_x_scale_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_x_scale_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_scale_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_x_scale_qm);
	    else if (INLINE_LONG_P(symbolic_x_scale_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_x_scale_qm);
	    else if (text_string_p(symbolic_x_scale_qm))
		temp_3 = copy_as_wide_string(symbolic_x_scale_qm);
	    else if (CONSP(symbolic_x_scale_qm) && 
		    EQ(M_CDR(symbolic_x_scale_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_x_scale_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_x_scale_qm));
	    set_evaluation_structure_slot(structure,Qsymbolic_x_scale,temp_3);
	}
	if (symbolic_y_scale_qm) {
	    if (FIXNUMP(symbolic_y_scale_qm))
		temp_3 = symbolic_y_scale_qm;
	    else if ( !TRUEP(symbolic_y_scale_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_y_scale_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_y_scale_qm))
		temp_3 = symbolic_y_scale_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_y_scale_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_scale_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_y_scale_qm);
	    else if (FLOATP(symbolic_y_scale_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(symbolic_y_scale_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_y_scale_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_scale_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_y_scale_qm);
	    else if (INLINE_LONG_P(symbolic_y_scale_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_y_scale_qm);
	    else if (text_string_p(symbolic_y_scale_qm))
		temp_3 = copy_as_wide_string(symbolic_y_scale_qm);
	    else if (CONSP(symbolic_y_scale_qm) && 
		    EQ(M_CDR(symbolic_y_scale_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_y_scale_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_y_scale_qm));
	    set_evaluation_structure_slot(structure,Qsymbolic_y_scale,temp_3);
	}
	if (symbolic_x_in_workspace_qm) {
	    if (FIXNUMP(symbolic_x_in_workspace_qm))
		temp_3 = symbolic_x_in_workspace_qm;
	    else if ( !TRUEP(symbolic_x_in_workspace_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_x_in_workspace_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_x_in_workspace_qm))
		temp_3 = symbolic_x_in_workspace_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_x_in_workspace_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_in_workspace_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_x_in_workspace_qm);
	    else if (FLOATP(symbolic_x_in_workspace_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_x_in_workspace_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_x_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_in_workspace_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_x_in_workspace_qm);
	    else if (INLINE_LONG_P(symbolic_x_in_workspace_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_x_in_workspace_qm);
	    else if (text_string_p(symbolic_x_in_workspace_qm))
		temp_3 = copy_as_wide_string(symbolic_x_in_workspace_qm);
	    else if (CONSP(symbolic_x_in_workspace_qm) && 
		    EQ(M_CDR(symbolic_x_in_workspace_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_x_in_workspace_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_x_in_workspace_qm));
	    set_evaluation_structure_slot(structure,
		    Qsymbolic_x_in_workspace,temp_3);
	}
	if (symbolic_y_in_workspace_qm) {
	    if (FIXNUMP(symbolic_y_in_workspace_qm))
		temp_3 = symbolic_y_in_workspace_qm;
	    else if ( !TRUEP(symbolic_y_in_workspace_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_y_in_workspace_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_y_in_workspace_qm))
		temp_3 = symbolic_y_in_workspace_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_y_in_workspace_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_in_workspace_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_y_in_workspace_qm);
	    else if (FLOATP(symbolic_y_in_workspace_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_y_in_workspace_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_y_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_in_workspace_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_y_in_workspace_qm);
	    else if (INLINE_LONG_P(symbolic_y_in_workspace_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_y_in_workspace_qm);
	    else if (text_string_p(symbolic_y_in_workspace_qm))
		temp_3 = copy_as_wide_string(symbolic_y_in_workspace_qm);
	    else if (CONSP(symbolic_y_in_workspace_qm) && 
		    EQ(M_CDR(symbolic_y_in_workspace_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_y_in_workspace_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_y_in_workspace_qm));
	    set_evaluation_structure_slot(structure,
		    Qsymbolic_y_in_workspace,temp_3);
	}
	if (symbolic_x_in_window_qm) {
	    if (FIXNUMP(symbolic_x_in_window_qm))
		temp_3 = symbolic_x_in_window_qm;
	    else if ( !TRUEP(symbolic_x_in_window_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_x_in_window_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_x_in_window_qm))
		temp_3 = symbolic_x_in_window_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_x_in_window_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_in_window_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_x_in_window_qm);
	    else if (FLOATP(symbolic_x_in_window_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_x_in_window_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_x_in_window_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_in_window_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_x_in_window_qm);
	    else if (INLINE_LONG_P(symbolic_x_in_window_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_x_in_window_qm);
	    else if (text_string_p(symbolic_x_in_window_qm))
		temp_3 = copy_as_wide_string(symbolic_x_in_window_qm);
	    else if (CONSP(symbolic_x_in_window_qm) && 
		    EQ(M_CDR(symbolic_x_in_window_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_x_in_window_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_x_in_window_qm));
	    set_evaluation_structure_slot(structure,Qsymbolic_x_in_window,
		    temp_3);
	}
	if (symbolic_y_in_window_qm) {
	    if (FIXNUMP(symbolic_y_in_window_qm))
		temp_3 = symbolic_y_in_window_qm;
	    else if ( !TRUEP(symbolic_y_in_window_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_y_in_window_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_y_in_window_qm))
		temp_3 = symbolic_y_in_window_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_y_in_window_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_in_window_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_y_in_window_qm);
	    else if (FLOATP(symbolic_y_in_window_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_y_in_window_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_y_in_window_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_in_window_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_y_in_window_qm);
	    else if (INLINE_LONG_P(symbolic_y_in_window_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_y_in_window_qm);
	    else if (text_string_p(symbolic_y_in_window_qm))
		temp_3 = copy_as_wide_string(symbolic_y_in_window_qm);
	    else if (CONSP(symbolic_y_in_window_qm) && 
		    EQ(M_CDR(symbolic_y_in_window_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_y_in_window_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_y_in_window_qm));
	    set_evaluation_structure_slot(structure,Qsymbolic_y_in_window,
		    temp_3);
	}
	if (x_offset_units_qm) {
	    if (FIXNUMP(x_offset_units_qm))
		temp_3 = x_offset_units_qm;
	    else if ( !TRUEP(x_offset_units_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(x_offset_units_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(x_offset_units_qm))
		temp_3 = x_offset_units_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x_offset_units_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_offset_units_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(x_offset_units_qm);
	    else if (FLOATP(x_offset_units_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(x_offset_units_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(x_offset_units_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_offset_units_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(x_offset_units_qm);
	    else if (INLINE_LONG_P(x_offset_units_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(x_offset_units_qm);
	    else if (text_string_p(x_offset_units_qm))
		temp_3 = copy_as_wide_string(x_offset_units_qm);
	    else if (CONSP(x_offset_units_qm) && 
		    EQ(M_CDR(x_offset_units_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(x_offset_units_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(x_offset_units_qm));
	    set_evaluation_structure_slot(structure,Qx_offset_units,temp_3);
	}
	if (y_offset_units_qm) {
	    if (FIXNUMP(y_offset_units_qm))
		temp_3 = y_offset_units_qm;
	    else if ( !TRUEP(y_offset_units_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(y_offset_units_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(y_offset_units_qm))
		temp_3 = y_offset_units_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(y_offset_units_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_offset_units_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(y_offset_units_qm);
	    else if (FLOATP(y_offset_units_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(y_offset_units_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(y_offset_units_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_offset_units_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(y_offset_units_qm);
	    else if (INLINE_LONG_P(y_offset_units_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(y_offset_units_qm);
	    else if (text_string_p(y_offset_units_qm))
		temp_3 = copy_as_wide_string(y_offset_units_qm);
	    else if (CONSP(y_offset_units_qm) && 
		    EQ(M_CDR(y_offset_units_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(y_offset_units_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(y_offset_units_qm));
	    set_evaluation_structure_slot(structure,Qy_offset_units,temp_3);
	}
	if (symbolic_x_offset_direction_qm) {
	    if (FIXNUMP(symbolic_x_offset_direction_qm))
		temp_3 = symbolic_x_offset_direction_qm;
	    else if ( !TRUEP(symbolic_x_offset_direction_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_x_offset_direction_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_x_offset_direction_qm))
		temp_3 = symbolic_x_offset_direction_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_x_offset_direction_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_offset_direction_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_x_offset_direction_qm);
	    else if (FLOATP(symbolic_x_offset_direction_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_x_offset_direction_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_x_offset_direction_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_x_offset_direction_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_x_offset_direction_qm);
	    else if (INLINE_LONG_P(symbolic_x_offset_direction_qm) != 
		    (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_x_offset_direction_qm);
	    else if (text_string_p(symbolic_x_offset_direction_qm))
		temp_3 = copy_as_wide_string(symbolic_x_offset_direction_qm);
	    else if (CONSP(symbolic_x_offset_direction_qm) && 
		    EQ(M_CDR(symbolic_x_offset_direction_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_x_offset_direction_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_x_offset_direction_qm));
	    set_evaluation_structure_slot(structure,
		    Qsymbolic_x_offset_direction,temp_3);
	}
	if (symbolic_y_offset_direction_qm) {
	    if (FIXNUMP(symbolic_y_offset_direction_qm))
		temp_3 = symbolic_y_offset_direction_qm;
	    else if ( !TRUEP(symbolic_y_offset_direction_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(symbolic_y_offset_direction_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(symbolic_y_offset_direction_qm))
		temp_3 = symbolic_y_offset_direction_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(symbolic_y_offset_direction_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_offset_direction_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_float(symbolic_y_offset_direction_qm);
	    else if (FLOATP(symbolic_y_offset_direction_qm)) {
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
		aref_new_value = 
			DOUBLE_FLOAT_TO_DOUBLE(symbolic_y_offset_direction_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(symbolic_y_offset_direction_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(symbolic_y_offset_direction_qm)) 
		    == (SI_Long)1L)
		temp_3 = copy_managed_long(symbolic_y_offset_direction_qm);
	    else if (INLINE_LONG_P(symbolic_y_offset_direction_qm) != 
		    (SI_Long)0L)
		temp_3 = make_evaluation_long(symbolic_y_offset_direction_qm);
	    else if (text_string_p(symbolic_y_offset_direction_qm))
		temp_3 = copy_as_wide_string(symbolic_y_offset_direction_qm);
	    else if (CONSP(symbolic_y_offset_direction_qm) && 
		    EQ(M_CDR(symbolic_y_offset_direction_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(symbolic_y_offset_direction_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(symbolic_y_offset_direction_qm));
	    set_evaluation_structure_slot(structure,
		    Qsymbolic_y_offset_direction,temp_3);
	}
	if (x_magnification_qm) {
	    if (FIXNUMP(x_magnification_qm))
		temp_3 = x_magnification_qm;
	    else if ( !TRUEP(x_magnification_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(x_magnification_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(x_magnification_qm))
		temp_3 = x_magnification_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x_magnification_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_magnification_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(x_magnification_qm);
	    else if (FLOATP(x_magnification_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(x_magnification_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(x_magnification_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_magnification_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(x_magnification_qm);
	    else if (INLINE_LONG_P(x_magnification_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(x_magnification_qm);
	    else if (text_string_p(x_magnification_qm))
		temp_3 = copy_as_wide_string(x_magnification_qm);
	    else if (CONSP(x_magnification_qm) && 
		    EQ(M_CDR(x_magnification_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(x_magnification_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(x_magnification_qm));
	    set_evaluation_structure_slot(structure,Qx_magnification,temp_3);
	}
	if (y_magnification_qm) {
	    if (FIXNUMP(y_magnification_qm))
		temp_3 = y_magnification_qm;
	    else if ( !TRUEP(y_magnification_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(y_magnification_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(y_magnification_qm))
		temp_3 = y_magnification_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(y_magnification_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_magnification_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(y_magnification_qm);
	    else if (FLOATP(y_magnification_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(y_magnification_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(y_magnification_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_magnification_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(y_magnification_qm);
	    else if (INLINE_LONG_P(y_magnification_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(y_magnification_qm);
	    else if (text_string_p(y_magnification_qm))
		temp_3 = copy_as_wide_string(y_magnification_qm);
	    else if (CONSP(y_magnification_qm) && 
		    EQ(M_CDR(y_magnification_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(y_magnification_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(y_magnification_qm));
	    set_evaluation_structure_slot(structure,Qy_magnification,temp_3);
	}
	if (x_in_workspace_qm) {
	    if (FIXNUMP(x_in_workspace_qm))
		temp_3 = x_in_workspace_qm;
	    else if ( !TRUEP(x_in_workspace_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(x_in_workspace_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(x_in_workspace_qm))
		temp_3 = x_in_workspace_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_in_workspace_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(x_in_workspace_qm);
	    else if (FLOATP(x_in_workspace_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(x_in_workspace_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(x_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_in_workspace_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(x_in_workspace_qm);
	    else if (INLINE_LONG_P(x_in_workspace_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(x_in_workspace_qm);
	    else if (text_string_p(x_in_workspace_qm))
		temp_3 = copy_as_wide_string(x_in_workspace_qm);
	    else if (CONSP(x_in_workspace_qm) && 
		    EQ(M_CDR(x_in_workspace_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(x_in_workspace_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(x_in_workspace_qm));
	    set_evaluation_structure_slot(structure,Qx_in_workspace,temp_3);
	}
	if (y_in_workspace_qm) {
	    if (FIXNUMP(y_in_workspace_qm))
		temp_3 = y_in_workspace_qm;
	    else if ( !TRUEP(y_in_workspace_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(y_in_workspace_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(y_in_workspace_qm))
		temp_3 = y_in_workspace_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(y_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_in_workspace_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(y_in_workspace_qm);
	    else if (FLOATP(y_in_workspace_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(y_in_workspace_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(y_in_workspace_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_in_workspace_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(y_in_workspace_qm);
	    else if (INLINE_LONG_P(y_in_workspace_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(y_in_workspace_qm);
	    else if (text_string_p(y_in_workspace_qm))
		temp_3 = copy_as_wide_string(y_in_workspace_qm);
	    else if (CONSP(y_in_workspace_qm) && 
		    EQ(M_CDR(y_in_workspace_qm),Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(y_in_workspace_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(y_in_workspace_qm));
	    set_evaluation_structure_slot(structure,Qy_in_workspace,temp_3);
	}
	if (x_in_window_qm) {
	    if (FIXNUMP(x_in_window_qm))
		temp_3 = x_in_window_qm;
	    else if ( !TRUEP(x_in_window_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(x_in_window_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(x_in_window_qm))
		temp_3 = x_in_window_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x_in_window_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_in_window_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(x_in_window_qm);
	    else if (FLOATP(x_in_window_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(x_in_window_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(x_in_window_qm) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x_in_window_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(x_in_window_qm);
	    else if (INLINE_LONG_P(x_in_window_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(x_in_window_qm);
	    else if (text_string_p(x_in_window_qm))
		temp_3 = copy_as_wide_string(x_in_window_qm);
	    else if (CONSP(x_in_window_qm) && EQ(M_CDR(x_in_window_qm),
		    Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(x_in_window_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(x_in_window_qm));
	    set_evaluation_structure_slot(structure,Qx_in_window,temp_3);
	}
	if (y_in_window_qm) {
	    if (FIXNUMP(y_in_window_qm))
		temp_3 = y_in_window_qm;
	    else if ( !TRUEP(y_in_window_qm))
		temp_3 = Evaluation_false_value;
	    else if (EQ(y_in_window_qm,T))
		temp_3 = Evaluation_true_value;
	    else if (SYMBOLP(y_in_window_qm))
		temp_3 = y_in_window_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(y_in_window_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_in_window_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_float(y_in_window_qm);
	    else if (FLOATP(y_in_window_qm)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(y_in_window_qm);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_3 = new_float;
	    }
	    else if (INLINE_LONG_VECTOR_P(y_in_window_qm) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y_in_window_qm)) == 
		    (SI_Long)1L)
		temp_3 = copy_managed_long(y_in_window_qm);
	    else if (INLINE_LONG_P(y_in_window_qm) != (SI_Long)0L)
		temp_3 = make_evaluation_long(y_in_window_qm);
	    else if (text_string_p(y_in_window_qm))
		temp_3 = copy_as_wide_string(y_in_window_qm);
	    else if (CONSP(y_in_window_qm) && EQ(M_CDR(y_in_window_qm),
		    Qtruth_value)) {
		gensymed_symbol_5 = M_CAR(y_in_window_qm);
		if (FIXNUM_EQ(gensymed_symbol_5,Truth))
		    temp_3 = Evaluation_true_value;
		else if (FIXNUM_EQ(gensymed_symbol_5,Falsity))
		    temp_3 = Evaluation_false_value;
		else
		    temp_3 = eval_cons_1(gensymed_symbol_5,Qtruth_value);
	    }
	    else
		temp_3 = error((SI_Long)2L,
			"Bad type ~a for make-evaluation-value-based-on-type.",
			type_of(y_in_window_qm));
	    set_evaluation_structure_slot(structure,Qy_in_window,temp_3);
	}
	M_CAR(gensymed_symbol_4) = structure;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	temp_1 = ISVREF(representation,(SI_Long)13L);
	M_CAR(gensymed_symbol_4) = temp_1;
	gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	temp_1 = ISVREF(representation,(SI_Long)12L);
	M_CAR(gensymed_symbol_4) = temp_1;
	argument_list = gensymed_symbol;
	address = ISVREF(representation,(SI_Long)8L);
	socket_1 = getfq_function_no_default(address,Qsocket);
	callback_representation_fire_callback(representation,socket_1,
		argument_list);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(current_frame_serial_number_on_entry);
    reclaim_gensym_list_1(representations);
    return VALUES_1(Qnil);
}

static Object Qg2_window;          /* g2-window */

static Object Qlocal;              /* local */

static Object Qg2_window_management_type;  /* g2-window-management-type */

static Object string_constant_10;  /* "No local window for G2" */

/* G2-SUBSCRIBE-TO-WORKSPACES-SHOWING */
Object g2_subscribe_to_workspaces_showing(client_session,callback,user_data)
    Object client_session, callback, user_data;
{
    Object representation, scope_conses, ab_loopvar_, ab_loopvar__1, w;
    Object g2_window_qm, top_of_stack, message_1, svref_new_value;
    Object frame_serial_number_setf_arg, old, new_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,184);
    if (Current_system_rpc_icp_socket_qm)
	representation = 
		make_representation(Current_system_rpc_icp_socket_qm,
		client_session,Qshowing_representation);
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	w = Nil;
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
	  w = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (EQ(Qlocal,get_lookup_slot_value_given_default(w,
		  Qg2_window_management_type,Nil))) {
	      g2_window_qm = w;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop_1:
	  g2_window_qm = Qnil;
	end_1:;
	POP_SPECIAL();
	if ( !TRUEP(g2_window_qm)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_10);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	representation = make_representation(Local_pseudo_socket,
		g2_window_qm,Qshowing_representation);
    }
    svref_new_value = 
	    demand_representation_callback_remote_procedure_name(callback);
    ISVREF(representation,(SI_Long)10L) = svref_new_value;
    if (Current_system_rpc_icp_socket_qm) {
	svref_new_value = slot_value_list_4(Qsocket,
		Current_system_rpc_icp_socket_qm,Qsession_id,
		ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)40L));
	ISVREF(representation,(SI_Long)8L) = svref_new_value;
    }
    else {
	svref_new_value = slot_value_list_2(Qsocket,Local_pseudo_socket);
	ISVREF(representation,(SI_Long)8L) = svref_new_value;
	frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = svref_new_value;
    }
    svref_new_value = FIXNUMP(user_data) || user_data && 
	    SYMBOLP(user_data) ? user_data : 
	    copy_evaluation_value_1(user_data);
    ISVREF(representation,(SI_Long)13L) = svref_new_value;
    return store_callback_representation(representation);
}

static Object Qg2_subscribe_to_workspaces_showing;  /* g2-subscribe-to-workspaces-showing */

/* G2-SUBSCRIBE-TO-WORKSPACES-SHOWING-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_workspaces_showing_system_rpc_internal(gensymed_symbol,
	    client_item,callback,user_data)
    Object gensymed_symbol, client_item, callback, user_data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,185);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_subscribe_to_workspaces_showing,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_subscribe_to_workspaces_showing(client_item,
		    callback,user_data);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-UNSUBSCRIBE-TO-WORKSPACES-SHOWING */
Object g2_unsubscribe_to_workspaces_showing(subscription_index)
    Object subscription_index;
{
    Object representation_qm;

    x_note_fn_call(228,186);
    representation_qm = representation_handle_gethash(subscription_index);
    if (representation_qm)
	delete_representation(1,representation_qm);
    return VALUES_1(Evaluation_true_value);
}

static Object Qg2_unsubscribe_to_workspaces_showing;  /* g2-unsubscribe-to-workspaces-showing */

/* G2-UNSUBSCRIBE-TO-WORKSPACES-SHOWING-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_workspaces_showing_system_rpc_internal(gensymed_symbol,
	    subscription_handle)
    Object gensymed_symbol, subscription_handle;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,187);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_unsubscribe_to_workspaces_showing,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_unsubscribe_to_workspaces_showing(subscription_handle);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qfield_edit_representation;  /* field-edit-representation */

/* G2-SUBSCRIBE-TO-FIELD-EDIT-ACTIONS */
Object g2_subscribe_to_field_edit_actions(client_session,callback,user_data)
    Object client_session, callback, user_data;
{
    Object representation, scope_conses, ab_loopvar_, ab_loopvar__1, w;
    Object g2_window_qm, top_of_stack, message_1, svref_new_value;
    Object frame_serial_number_setf_arg, old, new_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,188);
    if (Current_system_rpc_icp_socket_qm)
	representation = 
		make_representation(Current_system_rpc_icp_socket_qm,
		client_session,Qfield_edit_representation);
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	w = Nil;
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
	  w = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (EQ(Qlocal,get_lookup_slot_value_given_default(w,
		  Qg2_window_management_type,Nil))) {
	      g2_window_qm = w;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop_1:
	  g2_window_qm = Qnil;
	end_1:;
	POP_SPECIAL();
	if ( !TRUEP(g2_window_qm)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_10);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	representation = make_representation(Local_pseudo_socket,
		g2_window_qm,Qfield_edit_representation);
    }
    svref_new_value = 
	    demand_representation_callback_remote_procedure_name(callback);
    ISVREF(representation,(SI_Long)10L) = svref_new_value;
    if (Current_system_rpc_icp_socket_qm) {
	svref_new_value = slot_value_list_4(Qsocket,
		Current_system_rpc_icp_socket_qm,Qsession_id,
		ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)40L));
	ISVREF(representation,(SI_Long)8L) = svref_new_value;
    }
    else {
	svref_new_value = slot_value_list_2(Qsocket,Local_pseudo_socket);
	ISVREF(representation,(SI_Long)8L) = svref_new_value;
	frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = svref_new_value;
    }
    svref_new_value = FIXNUMP(user_data) || user_data && 
	    SYMBOLP(user_data) ? user_data : 
	    copy_evaluation_value_1(user_data);
    ISVREF(representation,(SI_Long)13L) = svref_new_value;
    return store_callback_representation(representation);
}

static Object Qg2_subscribe_to_field_edit_actions;  /* g2-subscribe-to-field-edit-actions */

/* G2-SUBSCRIBE-TO-FIELD-EDIT-ACTIONS-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_field_edit_actions_system_rpc_internal(gensymed_symbol,
	    client_item,callback,user_data)
    Object gensymed_symbol, client_item, callback, user_data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,189);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_subscribe_to_field_edit_actions,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_subscribe_to_field_edit_actions(client_item,
		    callback,user_data);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-UNSUBSCRIBE-TO-FIELD-EDIT-ACTIONS */
Object g2_unsubscribe_to_field_edit_actions(subscription_index)
    Object subscription_index;
{
    Object representation_qm;

    x_note_fn_call(228,190);
    representation_qm = representation_handle_gethash(subscription_index);
    if (representation_qm)
	delete_representation(1,representation_qm);
    return VALUES_1(Evaluation_true_value);
}

static Object Qg2_unsubscribe_to_field_edit_actions;  /* g2-unsubscribe-to-field-edit-actions */

/* G2-UNSUBSCRIBE-TO-FIELD-EDIT-ACTIONS-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_field_edit_actions_system_rpc_internal(gensymed_symbol,
	    subscription_handle)
    Object gensymed_symbol, subscription_handle;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,191);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_unsubscribe_to_field_edit_actions,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_unsubscribe_to_field_edit_actions(subscription_handle);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qab_modules;         /* modules */

static Object Qlogbook;            /* logbook */

static Object Qmessage_board;      /* message-board */

/* G2-SUBSCRIBE-TO-MODULES */
Object g2_subscribe_to_modules(ui_client_interface,kb_callback,
	    kb_callback_data,module_information_callback,
	    module_information_callback_data)
    Object ui_client_interface, kb_callback, kb_callback_data;
    Object module_information_callback, module_information_callback_data;
{
    Object temp, gensymed_symbol, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object module_info, ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, temp_2;
    Object item_or_value, x2, svref_new_value, result_1;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(228,192);
    temp = demand_representation_callback_remote_procedure_name(kb_callback);
    ISVREF(ui_client_interface,(SI_Long)21L) = temp;
    ISVREF(ui_client_interface,(SI_Long)22L) = kb_callback_data;
    temp = 
	    demand_representation_callback_remote_procedure_name(module_information_callback);
    ISVREF(ui_client_interface,(SI_Long)23L) = temp;
    ISVREF(ui_client_interface,(SI_Long)24L) = 
	    module_information_callback_data;
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qab_modules;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qab_modules;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	module_info = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qmodule_information);
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
	      temp_1 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_loop_1;
	  module_info = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  ab_loopvar__4 = 
		  eval_cons_1(make_new_module_info_structure(module_info,
		  ui_client_interface),Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
	  goto next_loop;
	end_loop_1:
	  temp_2 = ab_loopvar__2;
	  goto end_1;
	  temp_2 = Qnil;
	end_1:;
	POP_SPECIAL();
	item_or_value = allocate_evaluation_sequence(temp_2);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	module_info = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qmodule_information);
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
	      temp_1 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_loop_3;
	  module_info = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  ab_loopvar__4 = 
		  eval_cons_1(make_new_module_info_structure(module_info,
		  ui_client_interface),Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
	  goto next_loop_2;
	end_loop_3:
	  temp_2 = ab_loopvar__2;
	  goto end_2;
	  temp_2 = Qnil;
	end_2:;
	POP_SPECIAL();
	item_or_value = allocate_evaluation_sequence(temp_2);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qlogbook;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qlogbook;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = get_current_logbook_sequence();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = get_current_logbook_sequence();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qmessage_board;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qmessage_board;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = get_current_message_board_sequence();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = get_current_message_board_sequence();
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    result_1 = eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(result_1);
}

static Object Qg2_subscribe_to_modules;  /* g2-subscribe-to-modules */

/* G2-SUBSCRIBE-TO-MODULES-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_modules_system_rpc_internal(gensymed_symbol,
	    module_callback,module_callback_data,
	    module_information_callback,module_information_callback_data)
    Object gensymed_symbol, module_callback, module_callback_data;
    Object module_information_callback, module_information_callback_data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object gsi_interface, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,193);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_subscribe_to_modules,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gsi_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    result = g2_subscribe_to_modules(gsi_interface,module_callback,
		    module_callback_data,module_information_callback,
		    module_information_callback_data);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* MAKE-EVALUATION-SEQUENCE-OF-TOP-LEVEL-MODULES */
Object make_evaluation_sequence_of_top_level_modules(module_name)
    Object module_name;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace, lst;
    Object ab_loopvar__2, ab_loopvar__3, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,194);
    if (module_name) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	workspace = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  lst = Nil;
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
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
	  if ( !TRUEP(ISVREF(workspace,(SI_Long)18L)) && EQ(module_name,
		  get_lookup_slot_value(workspace,
		      Qmodule_this_is_part_of_qm))) {
	      ab_loopvar__3 = eval_cons_1(workspace,Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__3;
	      else
		  lst = ab_loopvar__3;
	      ab_loopvar__2 = ab_loopvar__3;
	  }
	  goto next_loop;
	end_loop_1:
	  if (lst) {
	      temp_1 = allocate_evaluation_sequence(lst);
	      goto end_1;
	  }
	  temp_1 = Qnil;
	end_1:;
	POP_SPECIAL();
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qattribute;          /* attribute */

static Object Qtop_level_module;   /* top-level-module */

static Object Qdirectly_required_modules;  /* directly-required-modules */

static Object Qgsi_interface_icp_socket;  /* gsi-interface-icp-socket */

static Object Qsubscription_handle;  /* subscription-handle */

static Object Qis_top_level;       /* is-top-level */

static Object Qsubscription_handles;  /* subscription-handles */

static Object Qother_system_tables;  /* other-system-tables */

static Object Qsubscription_initial_value;  /* subscription-initial-value */

static Object Qinitial_value;      /* initial-value */

static Object Qtop_level_kb_workspaces;  /* top-level-kb-workspaces */

/* MAKE-NEW-MODULE-INFO-STRUCTURE */
Object make_new_module_info_structure(module_info,ui_client_interface)
    Object module_info, ui_client_interface;
{
    Object gensymed_symbol, temp, item_or_value, x2, temp_2;
    Object name_denotation_sequence, required_modules_denotation_sequence;
    Object current_system_rpc_icp_socket_qm, temp_3, thing, temp_4;
    Object name_subscription_result, required_modules_subscription_result;
    Object name_subscription_handle, required_modules_subscription_handle;
    Object table_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol_2, svref_new_value, module_structure;
    Object name_representation, required_modules_representation;
    Object slot_value_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_it_;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,195);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qattribute;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qattribute;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qname;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qtop_level_module;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qtop_level_module;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    name_denotation_sequence = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qattribute;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qattribute;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qname;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qname;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qdirectly_required_modules;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qdirectly_required_modules;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    required_modules_denotation_sequence = 
	    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
	    Qab_structure),Nil));
    current_system_rpc_icp_socket_qm = 
	    get_lookup_slot_value_given_default(ui_client_interface,
	    Qgsi_interface_icp_socket,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
	    0);
      temp_3 = ISVREF(ui_client_interface,(SI_Long)23L);
      thing = ISVREF(ui_client_interface,(SI_Long)24L);
      temp_4 = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	      SIMPLE_VECTOR_P(thing) ? thing : 
	      copy_if_evaluation_value_1(thing);
      name_subscription_result = g2_subscribe_to_item(module_info,
	      name_denotation_sequence,temp_3,temp_4,Evaluation_false_value);
      temp_3 = ISVREF(ui_client_interface,(SI_Long)23L);
      thing = ISVREF(ui_client_interface,(SI_Long)24L);
      temp_4 = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	      SIMPLE_VECTOR_P(thing) ? thing : 
	      copy_if_evaluation_value_1(thing);
      required_modules_subscription_result = 
	      g2_subscribe_to_item(module_info,
	      required_modules_denotation_sequence,temp_3,temp_4,
	      Evaluation_false_value);
      name_subscription_handle = estructure_slot(name_subscription_result,
	      Qsubscription_handle,Nil);
      required_modules_subscription_handle = 
	      estructure_slot(required_modules_subscription_result,
	      Qsubscription_handle,Nil);
      gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
	      (SI_Long)1L));
      gensymed_symbol_1 = (SI_Long)0L;
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	  ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
      }
      else {
	  temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	  ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size))
	  SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qmodule_information;
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)1L)) = Qmodule_information;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  item_or_value = module_info;
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	  SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
      }
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  item_or_value = module_info;
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		  item_or_value;
	  SVREF(temp,FIX((SI_Long)2L)) = temp_2;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size))
	  SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qis_top_level;
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)3L)) = Qis_top_level;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  item_or_value = EQ(module_info,
		  get_system_table_currently_in_force(Qmodule_information)) 
		  ? Evaluation_true_value : Evaluation_false_value;
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	  SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
      }
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  item_or_value = EQ(module_info,
		  get_system_table_currently_in_force(Qmodule_information)) 
		  ? Evaluation_true_value : Evaluation_false_value;
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		  item_or_value;
	  SVREF(temp,FIX((SI_Long)4L)) = temp_2;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size))
	  SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsubscription_handles;
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)5L)) = Qsubscription_handles;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  item_or_value = 
		  allocate_evaluation_sequence(eval_list_2(name_subscription_handle,
		  required_modules_subscription_handle));
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	  SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
      }
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  item_or_value = 
		  allocate_evaluation_sequence(eval_list_2(name_subscription_handle,
		  required_modules_subscription_handle));
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		  item_or_value;
	  SVREF(temp,FIX((SI_Long)6L)) = temp_2;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size))
	  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qother_system_tables;
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)7L)) = Qother_system_tables;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  table_name = Nil;
	  ab_loop_list_ = compute_system_table_choices(1,T);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  table_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !EQ(table_name,Qmodule_information)) {
	      ab_loopvar__2 = eval_cons_1(SYMBOL_VALUE(table_name),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	  }
	  goto next_loop;
	end_loop:
	  temp_4 = ab_loopvar_;
	  goto end_1;
	  temp_4 = Qnil;
	end_1:;
	  item_or_value = allocate_evaluation_sequence(temp_4);
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	  SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
      }
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  table_name = Nil;
	  ab_loop_list_ = compute_system_table_choices(1,T);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  table_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !EQ(table_name,Qmodule_information)) {
	      ab_loopvar__2 = eval_cons_1(SYMBOL_VALUE(table_name),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_4 = ab_loopvar_;
	  goto end_2;
	  temp_4 = Qnil;
	end_2:;
	  item_or_value = allocate_evaluation_sequence(temp_4);
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		  item_or_value;
	  SVREF(temp,FIX((SI_Long)8L)) = temp_2;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size))
	  SVREF(gensymed_symbol,FIX((SI_Long)11L)) = 
		  Qsubscription_initial_value;
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)9L)) = Qsubscription_initial_value;
      }
      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)6L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
	      ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  else {
	      temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	      ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qtop_level_module;
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qtop_level_module;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      thing = estructure_slot(name_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      thing = estructure_slot(name_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = 
		      Qdirectly_required_modules;
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qdirectly_required_modules;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      thing = estructure_slot(required_modules_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      thing = estructure_slot(required_modules_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)7L)) = 
		      Qtop_level_kb_workspaces;
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qtop_level_kb_workspaces;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = 
		      make_evaluation_sequence_of_top_level_modules(module_info 
		      ? ISVREF(module_info,(SI_Long)23L) : Qnil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)8L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      item_or_value = 
		      make_evaluation_sequence_of_top_level_modules(module_info 
		      ? ISVREF(module_info,(SI_Long)23L) : Qnil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(temp,FIX((SI_Long)6L)) = temp_2;
	  }
	  item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	  SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
      }
      else {
	  temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	  gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)6L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
	      ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  
		      - (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	      ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qtop_level_module;
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp_2,FIX((SI_Long)1L)) = Qtop_level_module;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      thing = estructure_slot(name_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	  }
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      thing = estructure_slot(name_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = 
		      Qdirectly_required_modules;
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp_2,FIX((SI_Long)3L)) = Qdirectly_required_modules;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      thing = estructure_slot(required_modules_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_2;
	  }
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      thing = estructure_slot(required_modules_subscription_result,
		      Qinitial_value,Nil);
	      item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		      SIMPLE_VECTOR_P(thing) ? thing : 
		      copy_if_evaluation_value_1(thing);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol_2,FIX((SI_Long)7L)) = 
		      Qtop_level_kb_workspaces;
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      SVREF(temp_2,FIX((SI_Long)5L)) = Qtop_level_kb_workspaces;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = 
		      make_evaluation_sequence_of_top_level_modules(module_info 
		      ? ISVREF(module_info,(SI_Long)23L) : Qnil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol_2,FIX((SI_Long)8L)) = temp_2;
	  }
	  else {
	      temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	      item_or_value = 
		      make_evaluation_sequence_of_top_level_modules(module_info 
		      ? ISVREF(module_info,(SI_Long)23L) : Qnil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp_2,FIX((SI_Long)6L)) = svref_new_value;
	  }
	  item_or_value = eval_cons_1(gensymed_symbol_2,Qab_structure);
	  if (SIMPLE_VECTOR_P(item_or_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		  item_or_value;
	  SVREF(temp,FIX((SI_Long)10L)) = temp_2;
      }
      module_structure = eval_cons_1(gensymed_symbol,Qab_structure);
      name_representation = 
	      representation_handle_gethash(name_subscription_handle);
      required_modules_representation = 
	      representation_handle_gethash(required_modules_subscription_handle);
      slot_value_modify_macro_using_test_arg_1 = name_representation;
      car_1 = slot_value_modify_macro_using_test_arg_1;
      cdr_1 = ISVREF(ui_client_interface,(SI_Long)25L);
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
	  temp_1 = TRUEP(ab_loop_it_);
	  goto end_3;
      }
      goto next_loop_2;
    end_loop_2:
      temp_1 = TRUEP(Qnil);
    end_3:;
      temp = temp_1 ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
      ISVREF(ui_client_interface,(SI_Long)25L) = temp;
      slot_value_modify_macro_using_test_arg_1 = 
	      required_modules_representation;
      car_1 = slot_value_modify_macro_using_test_arg_1;
      cdr_1 = ISVREF(ui_client_interface,(SI_Long)25L);
      key_result = car_1;
      x_element = Nil;
      ab_loop_list_ = cdr_1;
      ab_loop_it_ = Nil;
    next_loop_3:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_3;
      x_element = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
      if (ab_loop_it_) {
	  temp_1 = TRUEP(ab_loop_it_);
	  goto end_4;
      }
      goto next_loop_3;
    end_loop_3:
      temp_1 = TRUEP(Qnil);
    end_4:;
      temp = temp_1 ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
      ISVREF(ui_client_interface,(SI_Long)25L) = temp;
      reclaim_evaluation_structure(name_subscription_result);
      reclaim_evaluation_structure(required_modules_subscription_result);
      result = VALUES_1(module_structure);
    POP_SPECIAL();
    return result;
}

/* G2-UNSUBSCRIBE-TO-MODULES */
Object g2_unsubscribe_to_modules(ui_client_interface)
    Object ui_client_interface;
{
    Object thing, representation, ab_loop_list_;

    x_note_fn_call(228,196);
    ISVREF(ui_client_interface,(SI_Long)21L) = Nil;
    thing = ISVREF(ui_client_interface,(SI_Long)22L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    ISVREF(ui_client_interface,(SI_Long)22L) = Nil;
    thing = ISVREF(ui_client_interface,(SI_Long)22L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    ISVREF(ui_client_interface,(SI_Long)22L) = Nil;
    representation = Nil;
    ab_loop_list_ = ISVREF(ui_client_interface,(SI_Long)25L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_representation(1,representation);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(ISVREF(ui_client_interface,(SI_Long)25L));
    return VALUES_1(ISVREF(ui_client_interface,(SI_Long)25L) = Nil);
}

static Object Qg2_unsubscribe_to_modules;  /* g2-unsubscribe-to-modules */

/* G2-UNSUBSCRIBE-TO-MODULES-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_modules_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, gsi_interface;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,197);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_unsubscribe_to_modules,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gsi_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    gensymed_symbol_1 = g2_unsubscribe_to_modules(gsi_interface);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* INFORM-UI-CLIENT-INTERFACES-OF-MODULE-CREATION */
Object inform_ui_client_interfaces_of_module_creation(module_info)
    Object module_info;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object icp_socket_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,198);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      icp_socket_qm = get_slot_value_function(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,(SI_Long)15L),
	      Icp_connection_closed))
	  inform_ui_client_interface_of_module_creation(module_info,
		  ui_client_interface);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qcreate;             /* create */

/* INFORM-UI-CLIENT-INTERFACE-OF-MODULE-CREATION */
Object inform_ui_client_interface_of_module_creation(module_info,
	    ui_client_interface)
    Object module_info, ui_client_interface;
{
    Object callback_qm, arg_list;

    x_note_fn_call(228,199);
    callback_qm = ISVREF(ui_client_interface,(SI_Long)21L);
    if (callback_qm && 
	    get_lookup_slot_value_given_default(ui_client_interface,
	    Qgsi_interface_icp_socket,Nil)) {
	arg_list = eval_list_2(Qcreate,
		make_new_module_info_structure(module_info,
		ui_client_interface));
	return start_remote_representation_callback(get_lookup_slot_value_given_default(ui_client_interface,
		Qgsi_interface_icp_socket,Nil),callback_qm,arg_list);
    }
    else
	return VALUES_1(Nil);
}

/* INFORM-UI-CLIENT-INTERFACES-OF-MODULE-DELETION */
Object inform_ui_client_interfaces_of_module_deletion(module_info)
    Object module_info;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object callback_qm, icp_socket_qm, representations;
    Object representations_to_delete, representation, ab_loop_list_;
    Object svref_new_value, arg_list, temp_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,200);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      callback_qm = Nil;
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      callback_qm = ISVREF(ui_client_interface,(SI_Long)21L);
      icp_socket_qm = get_slot_value_function(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,(SI_Long)15L),
	      Icp_connection_closed)) {
	  representations = ISVREF(ui_client_interface,(SI_Long)25L);
	  representations_to_delete = Nil;
	  representation = Nil;
	  ab_loop_list_ = representations;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  representation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (EQ(module_info,ISVREF(representation,(SI_Long)9L)))
	      representations_to_delete = gensym_cons_1(representation,
		      representations_to_delete);
	  goto next_loop_2;
	end_loop_2:
	  representation = Nil;
	  ab_loop_list_ = representations_to_delete;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  representation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  svref_new_value = delete_slot_value_element_1(representation,
		  ISVREF(ui_client_interface,(SI_Long)25L));
	  ISVREF(ui_client_interface,(SI_Long)25L) = svref_new_value;
	  goto next_loop_3;
	end_loop_3:;
	  reclaim_gensym_list_1(representations_to_delete);
	  if (callback_qm && 
		  get_lookup_slot_value_given_default(ui_client_interface,
		  Qgsi_interface_icp_socket,Nil)) {
	      arg_list = eval_list_2(Qdelete,module_info);
	      temp_1 = 
		      get_lookup_slot_value_given_default(ui_client_interface,
		      Qgsi_interface_icp_socket,Nil);
	      start_remote_representation_callback(temp_1,callback_qm,
		      arg_list);
	  }
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qclear_kb;           /* clear-kb */

/* INFORM-UI-CLIENT-INTERFACES-OF-CLEAR-KB */
Object inform_ui_client_interfaces_of_clear_kb()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object callback_qm, icp_socket_qm, arg_list;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,201);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      callback_qm = Nil;
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      callback_qm = ISVREF(ui_client_interface,(SI_Long)21L);
      icp_socket_qm = 
	      get_lookup_slot_value_given_default(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      reclaim_slot_value_list_1(ISVREF(ui_client_interface,(SI_Long)25L));
      ISVREF(ui_client_interface,(SI_Long)25L) = Nil;
      if (callback_qm && icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
	      (SI_Long)15L),Icp_connection_closed)) {
	  arg_list = eval_list_2(Qclear_kb,Nil);
	  start_remote_representation_callback(icp_socket_qm,callback_qm,
		  arg_list);
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* INFORM-UI-CLIENT-INTERFACES-OF-TOP-LEVEL-WORKSPACE-ASSIGNMENT-CHANGE */
Object inform_ui_client_interfaces_of_top_level_workspace_assignment_change(kb_workspace,
	    newly_becoming_top_level_workspace_qm,module_name)
    Object kb_workspace, newly_becoming_top_level_workspace_qm, module_name;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object icp_socket_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,202);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      icp_socket_qm = get_slot_value_function(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,(SI_Long)15L),
	      Icp_connection_closed))
	  inform_ui_client_interface_of_top_level_workspace_assignment_change(kb_workspace,
		  newly_becoming_top_level_workspace_qm,module_name,
		  ui_client_interface);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qmodule_name;        /* module-name */

static Object Qadd_as_top_level_workspace;  /* add-as-top-level-workspace */

static Object Qremove_as_top_level_workspace;  /* remove-as-top-level-workspace */

/* INFORM-UI-CLIENT-INTERFACE-OF-TOP-LEVEL-WORKSPACE-ASSIGNMENT-CHANGE */
Object inform_ui_client_interface_of_top_level_workspace_assignment_change(kb_workspace,
	    newly_becoming_top_level_workspace_qm,module_name,
	    ui_client_interface)
    Object kb_workspace, newly_becoming_top_level_workspace_qm, module_name;
    Object ui_client_interface;
{
    Object callback_qm, icp_socket_qm, gensymed_symbol, temp, item_or_value;
    Object x2, svref_new_value, particulars, modfn_code, arg_list;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,203);
    callback_qm = ISVREF(ui_client_interface,(SI_Long)21L);
    icp_socket_qm = 
	    get_lookup_slot_value_given_default(ui_client_interface,
	    Qgsi_interface_icp_socket,Nil);
    if (callback_qm && icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
	    (SI_Long)15L),Icp_connection_closed)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qkb_workspace;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qkb_workspace;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = kb_workspace;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = kb_workspace;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qmodule_name;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qmodule_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = module_name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = module_name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	particulars = eval_cons_1(gensymed_symbol,Qab_structure);
	modfn_code = newly_becoming_top_level_workspace_qm ? 
		Qadd_as_top_level_workspace : Qremove_as_top_level_workspace;
	arg_list = eval_list_2(modfn_code,particulars);
	start_remote_representation_callback(icp_socket_qm,callback_qm,
		arg_list);
    }
    return VALUES_1(Nil);
}

/* INFORM-UI-CLIENT-INTERFACES-OF-GENERAL-UPDATE */
Object inform_ui_client_interfaces_of_general_update(update_type,data)
    Object update_type, data;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object callback_qm, icp_socket_qm, arg_list;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,204);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      callback_qm = Nil;
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      callback_qm = ISVREF(ui_client_interface,(SI_Long)21L);
      icp_socket_qm = 
	      get_lookup_slot_value_given_default(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      if (callback_qm && icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
	      (SI_Long)15L),Icp_connection_closed)) {
	  arg_list = eval_list_2(update_type,data);
	  start_remote_representation_callback(icp_socket_qm,callback_qm,
		  arg_list);
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object list_constant;       /* # */

/* FILE-PROGRESS-AS-STRUCTURE */
Object file_progress_as_structure(progress_frame)
    Object progress_frame;
{
    Object slot_description, class_description, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, thing;

    x_note_fn_call(228,205);
    slot_description = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(progress_frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(ISVREF(slot_description,(SI_Long)3L),list_constant)) {
	temp = ISVREF(slot_description,(SI_Long)2L);
	thing = get_slot_description_value(progress_frame,slot_description);
	ab_loopvar__2 = eval_list_2(temp,FIXNUMP(thing) || thing && 
		SYMBOLP(thing) || SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = allocate_evaluation_structure(temp);
    return VALUES_1(temp);
}

static Object array_constant_2;    /* # */

static Object Qoutput;             /* output */

static Object string_constant_11;  /* "Saving " */

static Object Qinput;              /* input */

static Object string_constant_12;  /* "Loading " */

static Object string_constant_13;  /* "~a~a" */

static Object string_constant_14;  /* "  ~d lines " */

static Object string_constant_15;  /* "  ~d%" */

static Object string_constant_16;  /* "  [~a]" */

static Object Qwriting;            /* writing */

/* NOTE-FILE-PROGRESS */
Object note_file_progress(progress_frame,delete_p)
    Object progress_frame, delete_p;
{
    Object filename_qm, direction_qm, bytes_qm, lines_qm, total_qm, status_qm;
    Object numerator_1, denominator_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, note;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(228,206);
    filename_qm = ISVREF(progress_frame,(SI_Long)21L);
    direction_qm = ISVREF(progress_frame,(SI_Long)25L);
    bytes_qm = ISVREF(progress_frame,(SI_Long)27L);
    lines_qm = ISVREF(progress_frame,(SI_Long)22L);
    total_qm = ISVREF(progress_frame,(SI_Long)23L);
    status_qm = ISVREF(progress_frame,(SI_Long)26L);
    if (delete_p)
	return note_progress(0);
    else if ( !TRUEP(direction_qm) &&  !TRUEP(total_qm))
	return note_progress(2,array_constant_2,FIX((SI_Long)0L));
    else if (bytes_qm || lines_qm || status_qm) {
	numerator_1 = bytes_qm;
	if (numerator_1);
	else
	    numerator_1 = total_qm;
	if (numerator_1);
	else
	    numerator_1 = EQ(lines_qm,FIX((SI_Long)0L)) ? FIX((SI_Long)0L) 
		    : Nil;
	if (numerator_1);
	else
	    numerator_1 = FIX((SI_Long)100L);
	denominator_1 = total_qm;
	if (denominator_1);
	else
	    denominator_1 = FIX((SI_Long)100L);
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
		  if (EQ(direction_qm,Qoutput))
		      temp = string_constant_11;
		  else if (EQ(direction_qm,Qinput) || total_qm)
		      temp = string_constant_12;
		  else
		      temp = string_constant_4;
		  tformat(3,string_constant_13,temp,filename_qm);
		  if (lines_qm && EQ(direction_qm,Qoutput))
		      tformat(2,string_constant_14,lines_qm);
		  else
		      tformat(2,string_constant_15,
			      compute_percentage(numerator_1,denominator_1));
		  if (status_qm)
		      tformat(2,string_constant_16,EQ(direction_qm,
			      Qoutput) && EQ(status_qm,Qopen) ? Qwriting : 
			      status_qm);
		  note = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	note_progress(3,note,numerator_1,denominator_1);
	return reclaim_text_string(note);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-UPDATE-TO-FILE-PROGRESS */
Object note_update_to_file_progress varargs_1(int, n)
{
    Object progress_frame;
    Object change, info_qm, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object ui_client_interface, callback_qm, icp_socket_qm, temp_1, temp_2;
    Object evaluation_value, temp_3;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(228,207);
    INIT_ARGS_nonrelocating();
    progress_frame = REQUIRED_ARG_nonrelocating();
    change = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    note_file_progress(progress_frame,EQ(change,Qdelete) ? T : Nil);
    info_qm = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      callback_qm = Nil;
      icp_socket_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      callback_qm = ISVREF(ui_client_interface,(SI_Long)27L);
      icp_socket_qm = get_slot_value_function(ui_client_interface,
	      Qgsi_interface_icp_socket,Nil);
      if (callback_qm && icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
	      (SI_Long)15L),Icp_connection_closed)) {
	  temp_1 = icp_socket_qm;
	  temp_2 = callback_qm;
	  evaluation_value = info_qm;
	  if (evaluation_value);
	  else {
	      info_qm = file_progress_as_structure(progress_frame);
	      evaluation_value = info_qm;
	  }
	  temp_3 = FIXNUMP(evaluation_value) || evaluation_value && 
		  SYMBOLP(evaluation_value) ? evaluation_value : 
		  copy_evaluation_value_1(evaluation_value);
	  start_remote_representation_callback(temp_1,temp_2,
		  eval_list_2(temp_3,EQ(change,Qdelete) ? 
		  Evaluation_true_value : Evaluation_false_value));
      }
      goto next_loop;
    end_loop_1:
      if ( !(FIXNUMP(info_qm) || SYMBOLP(info_qm) || SIMPLE_VECTOR_P(info_qm)))
	  reclaim_if_evaluation_value_1(info_qm);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_subscribe_to_file_progress_changes;  /* g2-subscribe-to-file-progress-changes */

/* G2-SUBSCRIBE-TO-FILE-PROGRESS-CHANGES-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_file_progress_changes_system_rpc_internal(gensymed_symbol,
	    progress_callback,progress_callback_data)
    Object gensymed_symbol, progress_callback, progress_callback_data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, ui_client_interface;
    Object svref_new_value, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,208);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_subscribe_to_file_progress_changes,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    ui_client_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    svref_new_value = 
		    demand_representation_callback_remote_procedure_name(progress_callback);
	    ISVREF(ui_client_interface,(SI_Long)27L) = svref_new_value;
	    ISVREF(ui_client_interface,(SI_Long)28L) = progress_callback_data;
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_unsubscribe_to_file_progress_changes;  /* g2-unsubscribe-to-file-progress-changes */

/* G2-UNSUBSCRIBE-TO-FILE-PROGRESS-CHANGES-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_file_progress_changes_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, ui_client_interface;
    Object thing, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,209);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_unsubscribe_to_file_progress_changes,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    ui_client_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    ISVREF(ui_client_interface,(SI_Long)27L) = Nil;
	    thing = ISVREF(ui_client_interface,(SI_Long)28L);
	    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
		reclaim_if_evaluation_value_1(thing);
	    ISVREF(ui_client_interface,(SI_Long)28L) = Nil;
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_t2_dialog_sequence_number, Qcurrent_t2_dialog_sequence_number);

/* GET-NEXT-SEQUENCE-NUMBER-FOR-DIALOG-FOR-T2 */
Object get_next_sequence_number_for_dialog_for_t2()
{
    Object temp, current_t2_dialog_sequence_number_new_value;

    x_note_fn_call(228,210);
    if (FIXNUM_EQ(Current_t2_dialog_sequence_number,Most_positive_fixnum))
	temp = FIX((SI_Long)0L);
    else {
	current_t2_dialog_sequence_number_new_value = 
		FIXNUM_ADD1(Current_t2_dialog_sequence_number);
	Current_t2_dialog_sequence_number = 
		current_t2_dialog_sequence_number_new_value;
	temp = Current_t2_dialog_sequence_number;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(T2_dialog_result_alist, Qt2_dialog_result_alist);

static Object Qvalue;              /* value */

/* ENTER-DIALOG-FOR-T2 */
Object enter_dialog_for_t2 varargs_1(int, n)
{
    Object dialog_name, dialog_as_eval_list, continuation;
    Object ui_client_interface_qm, client_item_qm;
    Object sequence_number, entry, ab_loop_list_, type, text, name, value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp, gensymed_symbol;
    Object temp_1, item_or_value, x2, svref_new_value, info;
    Object current_dialog_sequence_number, scope_conses, ui_client_interface;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(228,211);
    INIT_ARGS_nonrelocating();
    dialog_name = REQUIRED_ARG_nonrelocating();
    dialog_as_eval_list = REQUIRED_ARG_nonrelocating();
    continuation = REQUIRED_ARG_nonrelocating();
    ui_client_interface_qm = REQUIRED_ARG_nonrelocating();
    client_item_qm = REQUIRED_ARG_nonrelocating();
    sequence_number = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    entry = Nil;
    ab_loop_list_ = dialog_as_eval_list;
    type = Nil;
    text = Nil;
    name = Nil;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    type = CAR(entry);
    temp = CDR(entry);
    text = CAR(temp);
    temp = CDR(entry);
    temp = CDR(temp);
    name = CAR(temp);
    temp = CDR(entry);
    temp = CDR(temp);
    temp = CDR(temp);
    value = CAR(temp);
    if (EQ(type,Qitem)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qitem;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qname;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qname;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtype;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtext;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qtext;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = text;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qname;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qname;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = name;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qvalue;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)7L)) = Qvalue;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = value;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = value;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)8L)) = svref_new_value;
	}
	temp = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    ab_loopvar__2 = eval_cons_1(temp,Nil);
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
    info = allocate_evaluation_sequence(temp);
    current_dialog_sequence_number = sequence_number;
    if (current_dialog_sequence_number);
    else
	current_dialog_sequence_number = 
		get_next_sequence_number_for_dialog_for_t2();
    reclaim_eval_list_1(dialog_as_eval_list);
    if (ui_client_interface_qm)
	enter_dialog_for_ui_client_interface(dialog_name,info,continuation,
		ui_client_interface_qm,client_item_qm,
		current_dialog_sequence_number);
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ui_client_interface = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qui_client_interface);
	next_loop_1:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_2:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_1;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_1;
	      goto next_loop_2;
	    end_loop_1:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_2;
	  ui_client_interface = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  enter_dialog_for_ui_client_interface(dialog_name,info,
		  continuation,ui_client_interface,client_item_qm,
		  current_dialog_sequence_number);
	  goto next_loop_1;
	end_loop_2:;
	POP_SPECIAL();
    }
    if (CONSP(continuation))
	reclaim_slot_value_list_1(continuation);
    reclaim_evaluation_value(info);
    return VALUES_1(current_dialog_sequence_number);
}

/* SOME-DIALOG-FOR-T2-HAS-RETURNED-P */
Object some_dialog_for_t2_has_returned_p(sequence_number)
    Object sequence_number;
{
    x_note_fn_call(228,212);
    return assoc_eql(sequence_number,T2_dialog_result_alist);
}

/* LEAVE-DIALOG-FOR-T2 */
Object leave_dialog_for_t2(sequence_number)
    Object sequence_number;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    Object temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,213);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      leave_dialog_for_ui_client_interface(ui_client_interface,Nil,
	      sequence_number);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    temp_1 = get_values_for_t2_dialog(sequence_number);
    return VALUES_1(temp_1);
}

static Object Qbutton;             /* button */

/* GET-VALUES-FOR-T2-DIALOG */
Object get_values_for_t2_dialog(sequence_number)
    Object sequence_number;
{
    Object a, button, gensymed_symbol, held_vector, e, type, name, value;
    Object check_box_values, ab_loopvar_, ab_loopvar__1, elt_1, validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(228,214);
    a = assoc_eql(sequence_number,T2_dialog_result_alist);
    if (a) {
	T2_dialog_result_alist = delete_gensym_element_1(a,
		T2_dialog_result_alist);
	button = Nil;
	gensymed_symbol = CDR(a);
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	e = Nil;
	type = Nil;
	name = Nil;
	value = Nil;
	check_box_values = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	e = validated_elt;
	type = estructure_slot(e,Qtype,Nil);
	name = estructure_slot(e,Qname,Nil);
	value = estructure_slot(e,Qvalue,Nil);
	if (EQ(type,Qbutton))
	    button = name;
	if (EQ(type,Qcheck_box)) {
	    ab_loopvar__1 = slot_value_cons_1(slot_value_cons_1(name,
		    CONSP(value) && EQ(M_CDR(value),Qtruth_value) ? 
		    (EQ(M_CAR(value),Truth) ? T : Nil) : Qnil),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		check_box_values = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	reclaim_evaluation_value(CDR(a));
	reclaim_gensym_cons_1(a);
	return VALUES_2(button,check_box_values);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qenter;              /* enter */

/* ENTER-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object enter_dialog_for_ui_client_interface(dialog_name,info,continuation,
	    ui_client_interface,client_item_qm,sequence_number)
    Object dialog_name, info, continuation, ui_client_interface;
    Object client_item_qm, sequence_number;
{
    Object callback_qm, icp_socket_qm, slot_value_push_modify_macro_arg, car_1;
    Object cdr_1, temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(228,215);
    callback_qm = ISVREF(ui_client_interface,(SI_Long)29L);
    if (callback_qm) {
	icp_socket_qm = get_slot_value_function(ui_client_interface,
		Qgsi_interface_icp_socket,Nil);
	if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,(SI_Long)15L),
		Icp_connection_closed)) {
	    slot_value_push_modify_macro_arg = 
		    slot_value_list_3(sequence_number,dialog_name,
		    CONSP(continuation) ? 
		    copy_list_using_slot_value_conses_1(continuation) : 
		    continuation);
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = ISVREF(ui_client_interface,(SI_Long)31L);
	    temp = slot_value_cons_1(car_1,cdr_1);
	    ISVREF(ui_client_interface,(SI_Long)31L) = temp;
	    gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = sequence_number;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = client_item_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = dialog_name;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qenter;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = FIXNUMP(info) || info && SYMBOLP(info) ? info : 
		    copy_evaluation_value_1(info);
	    M_CAR(gensymed_symbol_1) = temp;
	    return start_remote_representation_callback(icp_socket_qm,
		    callback_qm,gensymed_symbol);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrecompile;          /* recompile */

static Object Qstatus_update;      /* status-update */

/* NOTIFY-T2-FOR-LOCAL-RECOMPILE */
Object notify_t2_for_local_recompile(new_info_list)
    Object new_info_list;
{
    x_note_fn_call(228,216);
    update_dialog_for_t2(Qrecompile,new_info_list,Qstatus_update);
    return VALUES_1(Nil);
}

/* UPDATE-DIALOG-FOR-T2 */
Object update_dialog_for_t2(dialog_name,new_info_list,update_type)
    Object dialog_name, new_info_list, update_type;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ui_client_interface;
    char temp;
    Declare_special(1);

    x_note_fn_call(228,217);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ui_client_interface = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qui_client_interface);
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
      ui_client_interface = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      update_dialog_for_ui_client_interface(ui_client_interface,Nil,
	      dialog_name,new_info_list,update_type);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* GET-DIALOG-INFO */
Object get_dialog_info(dialog_name,ui_client_interface)
    Object dialog_name, ui_client_interface;
{
    Object info, ab_loop_list_, temp;

    x_note_fn_call(228,218);
    info = Nil;
    ab_loop_list_ = ISVREF(ui_client_interface,(SI_Long)31L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(dialog_name,CADR(info))) {
	temp = info;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qupdate;             /* update */

static Object Qupdate_type;        /* update-type */

static Object Qupdate_info;        /* update-info */

/* UPDATE-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object update_dialog_for_ui_client_interface(ui_client_interface,
	    client_item_qm,dialog_name,new_info_list,update_type)
    Object ui_client_interface, client_item_qm, dialog_name, new_info_list;
    Object update_type;
{
    Object callback_qm, dialog_info, icp_socket_qm, sequence_number;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_3, svref_arg_2;
    char temp_1;

    x_note_fn_call(228,219);
    callback_qm = ISVREF(ui_client_interface,(SI_Long)29L);
    if (callback_qm) {
	dialog_info = get_dialog_info(dialog_name,ui_client_interface);
	if (dialog_info) {
	    icp_socket_qm = get_slot_value_function(ui_client_interface,
		    Qgsi_interface_icp_socket,Nil);
	    sequence_number = CAR(dialog_info);
	    if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
		    (SI_Long)15L),Icp_connection_closed)) {
		gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = sequence_number;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = client_item_qm;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = dialog_name;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Qupdate;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		gensymed_symbol_2 = allocate_managed_array(1,
			FIX((SI_Long)4L + (SI_Long)1L));
		gensymed_symbol_3 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_3 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_3 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_3 & (SI_Long)1023L;
		    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qupdate_type;
		else {
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)1L)) = Qupdate_type;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = update_type;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
		}
		else {
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		    item_or_value = update_type;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qupdate_info;
		else {
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)3L)) = Qupdate_info;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    allocate_evaluation_sequence(copy_list_using_eval_conses_1(new_info_list));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
		}
		else {
		    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		    item_or_value = 
			    allocate_evaluation_sequence(copy_list_using_eval_conses_1(new_info_list));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
		}
		temp = 
			allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol_2,
			Qab_structure),Nil));
		M_CAR(gensymed_symbol_1) = temp;
		start_remote_representation_callback(icp_socket_qm,
			callback_qm,gensymed_symbol);
	    }
	}
    }
    return VALUES_1(Nil);
}

static Object Qleave;              /* leave */

/* LEAVE-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object leave_dialog_for_ui_client_interface(ui_client_interface,
	    client_item_qm,sequence_number)
    Object ui_client_interface, client_item_qm, sequence_number;
{
    Object callback_qm, a, svref_new_value, dialog_name, continuation;
    Object icp_socket_qm, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(228,220);
    callback_qm = ISVREF(ui_client_interface,(SI_Long)29L);
    if (callback_qm) {
	a = assoc_eql(sequence_number,ISVREF(ui_client_interface,
		(SI_Long)31L));
	if (a) {
	    svref_new_value = delete_slot_value_element_1(a,
		    ISVREF(ui_client_interface,(SI_Long)31L));
	    ISVREF(ui_client_interface,(SI_Long)31L) = svref_new_value;
	    dialog_name = CADR(a);
	    continuation = CADDR(a);
	    if (CONSP(continuation))
		reclaim_slot_value_list_1(continuation);
	    reclaim_slot_value_list_1(a);
	    icp_socket_qm = get_slot_value_function(ui_client_interface,
		    Qgsi_interface_icp_socket,Nil);
	    if (icp_socket_qm && FIXNUM_NE(ISVREF(icp_socket_qm,
		    (SI_Long)15L),Icp_connection_closed)) {
		gensymed_symbol = make_eval_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = sequence_number;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = client_item_qm;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = dialog_name;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Qleave;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		return start_remote_representation_callback(icp_socket_qm,
			callback_qm,gensymed_symbol);
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

/* REMOVE-DIALOG-INFO-FROM-UI-CLIENT-INTERFACE-DIALOG-LIST */
Object remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
	    ui_client_interface)
    Object dialog_sequence_number, ui_client_interface;
{
    Object dialog_info, continuation, svref_new_value, temp;

    x_note_fn_call(228,221);
    dialog_info = assoc_eql(dialog_sequence_number,
	    ISVREF(ui_client_interface,(SI_Long)31L));
    continuation = CADDR(dialog_info);
    svref_new_value = delete_slot_value_element_1(dialog_info,
	    ISVREF(ui_client_interface,(SI_Long)31L));
    ISVREF(ui_client_interface,(SI_Long)31L) = svref_new_value;
    reclaim_slot_value_list_1(dialog_info);
    temp = CONSP(continuation) ? reclaim_slot_value_list_1(continuation) : Nil;
    return VALUES_1(temp);
}

static Object Qg2_return_values_to_unsolicited_dialog;  /* g2-return-values-to-unsolicited-dialog */

/* G2-RETURN-VALUES-TO-UNSOLICITED-DIALOG-SYSTEM-RPC-INTERNAL */
Object g2_return_values_to_unsolicited_dialog_system_rpc_internal(gensymed_symbol,
	    dialog_sequence_number,dialog_values,client_item)
    Object gensymed_symbol, dialog_sequence_number, dialog_values, client_item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, ui_client_interface;
    Object a, temp_1, continuation, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,222);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_return_values_to_unsolicited_dialog,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    ui_client_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    a = assoc_eql(dialog_sequence_number,
		    ISVREF(ui_client_interface,(SI_Long)31L));
	    if (a) {
		if ( !TRUEP(assoc_eql(dialog_sequence_number,
			T2_dialog_result_alist))) {
		    temp_1 = gensym_cons_1(dialog_sequence_number,
			    FIXNUMP(dialog_values) || dialog_values && 
			    SYMBOLP(dialog_values) ? dialog_values : 
			    copy_evaluation_value_1(dialog_values));
		    T2_dialog_result_alist = gensym_cons_1(temp_1,
			    T2_dialog_result_alist);
		}
		continuation = CADDR(a);
		if ( !TRUEP(continuation))
		    remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
			    ui_client_interface);
		else if (CONSP(continuation)) {
		    temp_1 = CAR(continuation);
		    APPLY_3(temp_1,dialog_sequence_number,client_item,
			    CDR(continuation));
		}
		else
		    FUNCALL_2(continuation,dialog_sequence_number,client_item);
	    }
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_subscribe_to_unsolicited_dialogs;  /* g2-subscribe-to-unsolicited-dialogs */

/* G2-SUBSCRIBE-TO-UNSOLICITED-DIALOGS-SYSTEM-RPC-INTERNAL */
Object g2_subscribe_to_unsolicited_dialogs_system_rpc_internal(gensymed_symbol,
	    dialog_callback,dialog_callback_data)
    Object gensymed_symbol, dialog_callback, dialog_callback_data;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, ui_client_interface;
    Object svref_new_value, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,223);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_subscribe_to_unsolicited_dialogs,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    ui_client_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    svref_new_value = 
		    demand_representation_callback_remote_procedure_name(dialog_callback);
	    ISVREF(ui_client_interface,(SI_Long)29L) = svref_new_value;
	    ISVREF(ui_client_interface,(SI_Long)30L) = dialog_callback_data;
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_unsubscribe_to_unsolicited_dialogs;  /* g2-unsubscribe-to-unsolicited-dialogs */

/* G2-UNSUBSCRIBE-TO-UNSOLICITED-DIALOGS-SYSTEM-RPC-INTERNAL */
Object g2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, ui_client_interface;
    Object thing, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,224);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,
			Qg2_unsubscribe_to_unsolicited_dialogs,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    ui_client_interface = ISVREF(Current_system_rpc_icp_socket_qm,
		    (SI_Long)5L);
	    ISVREF(ui_client_interface,(SI_Long)29L) = Nil;
	    thing = ISVREF(ui_client_interface,(SI_Long)30L);
	    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
		reclaim_if_evaluation_value_1(thing);
	    ISVREF(ui_client_interface,(SI_Long)30L) = Nil;
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_17;  /* "G2-FILES-IN-DIRECTORY() failed ~a" */

/* G2-FILES-IN-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_files_in_directory_system_rpc_internal(gensymed_symbol,
	    directory_string)
    Object gensymed_symbol, directory_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object file_names_list_frame, error_message, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,225);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = files_in_directory_lisp_side(directory_string);
	    MVS_2(result,file_names_list_frame,error_message);
	    if (string_eq_w(error_message,array_constant_2))
		result = VALUES_1(file_names_list_frame);
	    else {
		delete_frame(file_names_list_frame);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_17,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_18;  /* "G2-SUBDIRECTORIES-IN-DIRECTORY() failed ~a" */

/* G2-SUBDIRECTORIES-IN-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_subdirectories_in_directory_system_rpc_internal(gensymed_symbol,
	    directory_string)
    Object gensymed_symbol, directory_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object directory_names_list_frame, error_message, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,226);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = subdirectories_in_directory_lisp_side(directory_string);
	    MVS_2(result,directory_names_list_frame,error_message);
	    if (string_eq_w(error_message,array_constant_2))
		result = VALUES_1(directory_names_list_frame);
	    else {
		delete_frame(directory_names_list_frame);
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			tformat_text_string(2,string_constant_18,
			error_message));
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_19;  /* "GET-HOST-NAME() failed." */

/* G2-GET-HOST-NAME-SYSTEM-RPC-INTERNAL */
Object g2_get_host_name_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, host_name_qm;
    Object end1, end2, ab_loop_iter_flag_, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,227);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    host_name_qm = get_host_name_lisp_side();
	    end1 = text_string_length(host_name_qm);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(host_name_qm,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_19);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(host_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_20;  /* "GET-PORT-NUMBER-OR-NAME() failed." */

/* G2-GET-PORT-NUMBER-OR-NAME-SYSTEM-RPC-INTERNAL */
Object g2_get_port_number_or_name_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, port_name_qm;
    Object end1, end2, ab_loop_iter_flag_, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,228);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    port_name_qm = get_port_number_or_name_lisp_side();
	    end1 = text_string_length(port_name_qm);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(port_name_qm,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_20);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(port_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_21;  /* "GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX(~s) failed." */

/* G2-GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX-SYSTEM-RPC-INTERNAL */
Object g2_get_port_number_or_name_given_index_system_rpc_internal(gensymed_symbol,
	    index_1)
    Object gensymed_symbol, index_1;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, port_name_qm;
    Object end1, end2, ab_loop_iter_flag_, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,229);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    port_name_qm = 
		    get_port_number_or_name_given_index_lisp_side(index_1);
	    end1 = text_string_length(port_name_qm);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(port_name_qm,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_21,index_1);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(port_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_22;  /* "G2-GET-VERSION() failed." */

/* G2-GET-STRUCTURED-VERSION-SYSTEM-RPC-INTERNAL */
Object g2_get_structured_version_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object software_version_qm, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,230);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    software_version_qm = system_version_information_as_structure();
	    if ( !TRUEP(software_version_qm)) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_22);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(software_version_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_23;  /* "GET-SOFTWARE-VERSION() failed." */

/* G2-GET-SOFTWARE-VERSION-SYSTEM-RPC-INTERNAL */
Object g2_get_software_version_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object software_version_qm, end1, end2, ab_loop_iter_flag_, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,231);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    software_version_qm = get_software_version_lisp_side();
	    end1 = text_string_length(software_version_qm);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(software_version_qm,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_23);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(software_version_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_24;  /* "G2-GET-BUILD-VERSION() failed." */

/* G2-GET-BUILD-VERSION-SYSTEM-RPC-INTERNAL */
Object g2_get_build_version_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object software_version_qm, end1, end2, ab_loop_iter_flag_, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,232);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    software_version_qm = g2_get_build_version();
	    end1 = text_string_length(software_version_qm);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(software_version_qm,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_24);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(software_version_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-UNIX-TIME-SYSTEM-RPC-INTERNAL */
Object g2_unix_time_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,233);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = unix_time_lisp_side();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-UNIX-TIME-AT-START-SYSTEM-RPC-INTERNAL */
Object g2_unix_time_at_start_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,234);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = unix_time_at_start_lisp_side();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-KILL-PROCESS-SYSTEM-RPC-INTERNAL */
Object g2_kill_process_system_rpc_internal(gensymed_symbol,process_id)
    Object gensymed_symbol, process_id;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,235);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = kill_process_lisp_side(process_id);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_25;  /* "PROCESS-EXISTS([~s]) failed." */

/* G2-PROCESS-EXISTS-SYSTEM-RPC-INTERNAL */
Object g2_process_exists_system_rpc_internal(gensymed_symbol,process_id)
    Object gensymed_symbol, process_id;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, command_status, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,236);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    command_status = process_exists_lisp_side(process_id);
	    if ( !(FIXNUMP(command_status) && 
		    FIXNUM_LE(FIX((SI_Long)-128L),command_status) && 
		    FIXNUM_LE(command_status,FIX((SI_Long)127L)))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_25,process_id);
		gensymed_symbol_1 = 
			raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		switch (INTEGER_TO_CHAR(command_status)) {
		  case 1:
		    gensymed_symbol_1 = Evaluation_true_value;
		    break;
		  case 0:
		    gensymed_symbol_1 = Evaluation_false_value;
		    break;
		  default:
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(2,
			    string_constant_25,process_id);
		    gensymed_symbol_1 = 
			    raw_stack_error_named_error(top_of_stack,
			    message_1);
		    break;
		}
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_26;  /* "SPAWN-PROCESS-WITH_ARGUMENTS(~a) failed." */

/* G2-SPAWN-PROCESS-WITH-ARGUMENTS-SYSTEM-RPC-INTERNAL */
Object g2_spawn_process_with_arguments_system_rpc_internal(gensymed_symbol,
	    command)
    Object gensymed_symbol, command;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, new_process_id;
    Object top_of_stack, message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,237);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    new_process_id = spawn_process_with_arguments_lisp_side(command);
	    if (DFLOAT_ISAREF_1(new_process_id,(SI_Long)0L) == -1.0) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_26,command);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(new_process_id);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_27;  /* "SPAWN-PROCESS-TO-RUN-COMMAND-LINE(~a) failed." */

/* G2-SPAWN-PROCESS-TO-RUN-COMMAND-LINE-SYSTEM-RPC-INTERNAL */
Object g2_spawn_process_to_run_command_line_system_rpc_internal(gensymed_symbol,
	    command)
    Object gensymed_symbol, command;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, new_process_id;
    Object top_of_stack, message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,238);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    new_process_id = 
		    spawn_process_to_run_command_line_lisp_side(command);
	    if (DFLOAT_ISAREF_1(new_process_id,(SI_Long)0L) == -1.0) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_27,command);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(new_process_id);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DEVICES-ON-MACHINE-SYSTEM-RPC-INTERNAL */
Object g2_devices_on_machine_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,239);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = devices_on_machine_lisp_side();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_28;  /* "DISK-SPACE-AVAILABLE-IN-DIRECTORY(~a) failed.:~a" */

/* G2-DISK-SPACE-AVAILABLE-IN-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_disk_space_available_in_directory_system_rpc_internal(gensymed_symbol,
	    directory_string)
    Object gensymed_symbol, directory_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, available_space;
    Object error_message, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,240);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = disk_space_available_in_directory_lisp_side(directory_string);
	    MVS_2(result,available_space,error_message);
	    if (IFIX(available_space) == (SI_Long)-1L) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_28,directory_string,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(available_space);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_29;  /* "CHANGE-DEFAULT-DIRECTORY(~a) failed: ~a." */

/* G2-CHANGE-DEFAULT-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_change_default_directory_system_rpc_internal(gensymed_symbol,
	    new_default)
    Object gensymed_symbol, new_default;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, status, error_message, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,241);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = change_default_directory_lisp_side(new_default);
	    MVS_2(result,status,error_message);
	    if ( !TRUEP(evaluation_truth_value_is_true_p(status))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_29,new_default,error_message);
		gensymed_symbol_1 = 
			raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_30;  /* "DEFAULT-DIRECTORY() failed: ~A" */

/* G2-DEFAULT-DIRECTORY-SYSTEM-RPC-INTERNAL */
Object g2_default_directory_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, current_default;
    Object error_message, end1, end2, ab_loop_iter_flag_, top_of_stack;
    Object message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,242);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = default_directory_lisp_side();
	    MVS_2(result,current_default,error_message);
	    end1 = text_string_length(current_default);
	    end2 = text_string_length(array_constant_2);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if (index1 >= ab_loop_bind_)
		    goto end_loop;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop;
		if ( !(UBYTE_16_ISAREF_1(current_default,index1) == 
			UBYTE_16_ISAREF_1(array_constant_2,index2))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
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
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_30,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(current_default);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DIRECTORY-EXISTS-SYSTEM-RPC-INTERNAL */
Object g2_directory_exists_system_rpc_internal(gensymed_symbol,
	    directory_string)
    Object gensymed_symbol, directory_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,243);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = directory_exists_lisp_side(directory_string);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_31;  /* "LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED(~a): ~a" */

/* G2-LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED-SYSTEM-RPC-INTERNAL */
Object g2_latest_date_file_attributes_were_changed_system_rpc_internal(gensymed_symbol,
	    file_string)
    Object gensymed_symbol, file_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, change_data;
    Object error_message, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,244);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = latest_date_file_attributes_were_changed_lisp_side(file_string);
	    MVS_2(result,change_data,error_message);
	    if (DFLOAT_ISAREF_1(change_data,(SI_Long)0L) == -1.0) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_31,file_string,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(change_data);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_32;  /* "LATEST-DATE-FILE-WAS-ACCESSED(~a): ~a" */

/* G2-LATEST-DATE-FILE-WAS-ACCESSED-SYSTEM-RPC-INTERNAL */
Object g2_latest_date_file_was_accessed_system_rpc_internal(gensymed_symbol,
	    file_string)
    Object gensymed_symbol, file_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, access_date;
    Object error_message, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,245);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = latest_date_file_was_accessed_lisp_side(file_string);
	    MVS_2(result,access_date,error_message);
	    if (DFLOAT_ISAREF_1(access_date,(SI_Long)0L) == -1.0) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_32,file_string,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(access_date);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-LATEST-DATE-FILE-WAS-MODIFIED-SYSTEM-RPC-INTERNAL */
Object g2_latest_date_file_was_modified_system_rpc_internal(gensymed_symbol,
	    file_string)
    Object gensymed_symbol, file_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object modification_date, error_message, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,246);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = latest_date_file_was_modified_lisp_side(file_string);
	    MVS_2(result,modification_date,error_message);
	    if (DFLOAT_ISAREF_1(modification_date,(SI_Long)0L) == -1.0) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_32,file_string,error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(modification_date);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_33;  /* "LENGTH-OF-FILE(~a) failed: ~a" */

/* G2-LENGTH-OF-FILE-SYSTEM-RPC-INTERNAL */
Object g2_length_of_file_system_rpc_internal(gensymed_symbol,file_stream)
    Object gensymed_symbol, file_stream;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object file_length_or_signal, error_message, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,247);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = length_of_file_lisp_side(file_stream);
	    MVS_2(result,file_length_or_signal,error_message);
	    if (IFIX(file_length_or_signal) == (SI_Long)-1L) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_33,ISVREF(file_stream,
			(SI_Long)20L),error_message);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		result = VALUES_1(file_length_or_signal);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-NAMES-ARE-IDENTICAL-SYSTEM-RPC-INTERNAL */
Object g2_file_names_are_identical_system_rpc_internal(gensymed_symbol,
	    filestring1,filestring2)
    Object gensymed_symbol, filestring1, filestring2;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,248);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_names_are_identical_lisp_side(filestring1,
		    filestring2);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-EXISTS-SYSTEM-RPC-INTERNAL */
Object g2_file_exists_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,249);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_exists_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-TYPE-OF-FILE-SYSTEM-SYSTEM-RPC-INTERNAL */
Object g2_type_of_file_system_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,250);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = type_of_file_system_lisp_side();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-PARTITION-FILESTRING-SYSTEM-RPC-INTERNAL */
Object g2_partition_filestring_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7, return_list, gensymed_symbol_8;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,251);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	gensymed_symbol_6 = Nil;
	gensymed_symbol_7 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = partition_filestring_lisp_side(filestring);
	    MVS_7(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5,
		    gensymed_symbol_6,gensymed_symbol_7);
	    gensymed_symbol_7 = make_eval_list_1(FIX((SI_Long)6L));
	    gensymed_symbol_8 = gensymed_symbol_7;
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_1;
	    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_2;
	    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_3;
	    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_4;
	    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_5;
	    gensymed_symbol_8 = M_CDR(gensymed_symbol_8);
	    M_CAR(gensymed_symbol_8) = gensymed_symbol_6;
	    return_list = gensymed_symbol_7;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-COLLECT-INTO-FILESTRING-SYSTEM-RPC-INTERNAL */
Object g2_collect_into_filestring_system_rpc_internal(gensymed_symbol,host,
	    device,directory_1,root_name,extension,version)
    Object gensymed_symbol, host, device, directory_1, root_name, extension;
    Object version;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,252);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = collect_into_filestring_lisp_side(host,device,
		    directory_1,root_name,extension,version);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-VERSION-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_version_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,253);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_version_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-EXTENSION-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_extension_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,254);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_extension_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-BASE-NAME-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_base_name_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,255);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_base_name_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-DIRECTORY-LIST-TO-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_directory_list_to_string_system_rpc_internal(gensymed_symbol,
	    directory_list)
    Object gensymed_symbol, directory_list;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,256);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_directory_list_to_string_lisp_side(directory_list);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-DIRECTORY-STRING-TO-LIST-SYSTEM-RPC-INTERNAL */
Object g2_file_directory_string_to_list_system_rpc_internal(gensymed_symbol,
	    filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,257);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_directory_string_to_list_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-DIRECTORY-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_directory_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,258);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_directory_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-DEVICE-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_device_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,259);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_device_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FILE-HOST-STRING-SYSTEM-RPC-INTERNAL */
Object g2_file_host_string_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,260);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = file_host_string_lisp_side(filestring);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_34;  /* "DELETE-FILE(~s) failed: ~s" */

/* G2-DELETE-FILE-SYSTEM-RPC-INTERNAL */
Object g2_delete_file_system_rpc_internal(gensymed_symbol,filestring)
    Object gensymed_symbol, filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, status_of_operation, error_message;
    Object top_of_stack, message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,261);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = delete_file_lisp_side(filestring);
	    MVS_2(result,status_of_operation,error_message);
	    if ( 
			!TRUEP(evaluation_truth_value_is_true_p(status_of_operation))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			tformat_text_string(3,string_constant_34,
			filestring,error_message));
		gensymed_symbol_1 = 
			raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_35;  /* "RENAME-FILE(~a,~a) failed: ~a" */

/* G2-RENAME-FILE-SYSTEM-RPC-INTERNAL */
Object g2_rename_file_system_rpc_internal(gensymed_symbol,old_filestring,
	    new_filestring)
    Object gensymed_symbol, old_filestring, new_filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, status_of_operation, error_message;
    Object top_of_stack, message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,262);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = rename_file_lisp_side(old_filestring,new_filestring);
	    MVS_2(result,status_of_operation,error_message);
	    if ( 
			!TRUEP(evaluation_truth_value_is_true_p(status_of_operation))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_35,old_filestring,new_filestring,
			error_message);
		gensymed_symbol_1 = 
			raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_36;  /* "COPY-FILE(~a,~a) failed: ~a" */

/* G2-COPY-FILE-SYSTEM-RPC-INTERNAL */
Object g2_copy_file_system_rpc_internal(gensymed_symbol,old_filestring,
	    new_filestring)
    Object gensymed_symbol, old_filestring, new_filestring;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, status_of_operation, error_message;
    Object top_of_stack, message_1, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,263);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = copy_file_lisp_side(old_filestring,new_filestring);
	    MVS_2(result,status_of_operation,error_message);
	    if ( 
			!TRUEP(evaluation_truth_value_is_true_p(status_of_operation))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_36,old_filestring,new_filestring,
			error_message);
		gensymed_symbol_1 = 
			raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else
		gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-ENABLE-INLINING-SYSTEM-RPC-INTERNAL */
Object g2_enable_inlining_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,264);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_enable_inlining();
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DISABLE-INLINING-SYSTEM-RPC-INTERNAL */
Object g2_disable_inlining_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,265);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_disable_inlining();
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-ITEM-IS-EDITABLE-SYSTEM-RPC-INTERNAL */
Object g2_item_is_editable_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,266);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_item_is_editable(item);
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SET-ITEM-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL */
Object g2_set_item_explicitly_editable_system_rpc_internal(gensymed_symbol,
	    item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,267);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_set_item_explicitly_editable(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SET-ITEM-AND-ALL-ITS-SUBBLOCKS-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL */
Object g2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal(gensymed_symbol,
	    item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,268);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = 
		    g2_set_item_and_all_its_subblocks_explicitly_editable(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SET-ALL-ITEMS-IN-MODULE-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL */
Object g2_set_all_items_in_module_explicitly_editable_system_rpc_internal(gensymed_symbol,
	    item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,269);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = 
		    g2_set_all_items_in_module_explicitly_editable(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MODULES-WITH-UNSAVED-CHANGES-SYSTEM-RPC-INTERNAL */
Object g2_modules_with_unsaved_changes_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,270);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_modules_with_unsaved_changes();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-START-SAVE-MODULE-SYSTEM-RPC-INTERNAL */
Object g2_start_save_module_system_rpc_internal(gensymed_symbol,pathname_1,
	    file_progress_display,window_or_not,module,
	    include_required_modules)
    Object gensymed_symbol, pathname_1, file_progress_display, window_or_not;
    Object module, include_required_modules;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,271);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_save_module(pathname_1,file_progress_display,
		    window_or_not,module,include_required_modules);
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qfile_progress_display;  /* file-progress-display */

static Object Qinclude_required_modules;  /* include-required-modules */

static Object Qusing_clear_text;   /* using-clear-text */

static Object Qemitting_c_code;    /* emitting-c-code */

static Object Qlog_message_for_commit_after_saving;  /* log-message-for-commit-after-saving */

/* G2-START-SAVE-MODULE-1-SYSTEM-RPC-INTERNAL */
Object g2_start_save_module_1_system_rpc_internal(gensymed_symbol,
	    pathname_1,file_progress_display,window_or_not,module,
	    include_required_modules,using_clear_text,emitting_c_code,
	    log_message_for_commit_after_saving)
    Object gensymed_symbol, pathname_1, file_progress_display, window_or_not;
    Object module, include_required_modules, using_clear_text, emitting_c_code;
    Object log_message_for_commit_after_saving;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, temp, item_or_value, x2, svref_new_value, options;
    Object status_symbol, error_text_qm, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp_2, error_text_string;
    SI_Long gensymed_symbol_4, svref_arg_2;
    char temp_1;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,272);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)10L 
		    + (SI_Long)1L));
	    gensymed_symbol_4 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_4 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(gensymed_symbol_4 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = 
			Qfile_progress_display;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qfile_progress_display;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(file_progress_display) || 
			file_progress_display && 
			SYMBOLP(file_progress_display) ? 
			file_progress_display : 
			copy_evaluation_value_1(file_progress_display);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(file_progress_display) || 
			file_progress_display && 
			SYMBOLP(file_progress_display) ? 
			file_progress_display : 
			copy_evaluation_value_1(file_progress_display);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = 
			Qinclude_required_modules;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qinclude_required_modules;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(include_required_modules) || 
			include_required_modules && 
			SYMBOLP(include_required_modules) ? 
			include_required_modules : 
			copy_evaluation_value_1(include_required_modules);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(include_required_modules) || 
			include_required_modules && 
			SYMBOLP(include_required_modules) ? 
			include_required_modules : 
			copy_evaluation_value_1(include_required_modules);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)7L)) = Qusing_clear_text;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qusing_clear_text;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(using_clear_text) || 
			using_clear_text && SYMBOLP(using_clear_text) ? 
			using_clear_text : 
			copy_evaluation_value_1(using_clear_text);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)8L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(using_clear_text) || 
			using_clear_text && SYMBOLP(using_clear_text) ? 
			using_clear_text : 
			copy_evaluation_value_1(using_clear_text);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)9L)) = Qemitting_c_code;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)7L)) = Qemitting_c_code;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(emitting_c_code) || 
			emitting_c_code && SYMBOLP(emitting_c_code) ? 
			emitting_c_code : 
			copy_evaluation_value_1(emitting_c_code);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)10L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(emitting_c_code) || 
			emitting_c_code && SYMBOLP(emitting_c_code) ? 
			emitting_c_code : 
			copy_evaluation_value_1(emitting_c_code);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)11L)) = 
			Qlog_message_for_commit_after_saving;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)9L)) = 
			Qlog_message_for_commit_after_saving;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			FIXNUMP(log_message_for_commit_after_saving) || 
			log_message_for_commit_after_saving && 
			SYMBOLP(log_message_for_commit_after_saving) || 
			SIMPLE_VECTOR_P(log_message_for_commit_after_saving) 
			? log_message_for_commit_after_saving : 
			copy_if_evaluation_value_1(log_message_for_commit_after_saving);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)12L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = 
			FIXNUMP(log_message_for_commit_after_saving) || 
			log_message_for_commit_after_saving && 
			SYMBOLP(log_message_for_commit_after_saving) || 
			SIMPLE_VECTOR_P(log_message_for_commit_after_saving) 
			? log_message_for_commit_after_saving : 
			copy_if_evaluation_value_1(log_message_for_commit_after_saving);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	    }
	    options = eval_cons_1(gensymed_symbol_1,Qab_structure);
	    result = g2_save_module_extended(pathname_1,module,
		    window_or_not,options);
	    MVS_2(result,status_symbol,error_text_qm);
	    reclaim_evaluation_value(options);
	    result = VALUES_2(status_symbol,error_text_qm);
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_2 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_2;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-START-SAVE-KB-SYSTEM-RPC-INTERNAL */
Object g2_start_save_kb_system_rpc_internal(gensymed_symbol,pathname_1,
	    type_of_file,file_progress_display,window)
    Object gensymed_symbol, pathname_1, type_of_file, file_progress_display;
    Object window;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,273);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_save_kb(pathname_1,type_of_file,
		    file_progress_display,window);
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CONTINUE-SAVE-KB-SYSTEM-RPC-INTERNAL */
Object g2_continue_save_kb_system_rpc_internal(gensymed_symbol,
	    file_progress_display)
    Object gensymed_symbol, file_progress_display;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,274);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_continue_save_kb(file_progress_display);
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FINISH-SAVE-KB-SYSTEM-RPC-INTERNAL */
Object g2_finish_save_kb_system_rpc_internal(gensymed_symbol,
	    file_progress_display)
    Object gensymed_symbol, file_progress_display;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object return_list, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp, error_text_string;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,275);
    SAVE_STACK();
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    SAVE_VALUES(g2_finish_save_kb(file_progress_display));
	    terminate_kb_save_or_backup_if_error_occurs();
	    result = RESTORE_VALUES();
	    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3);
	    return_list = eval_list_2(gensymed_symbol_1,gensymed_symbol_2);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    RESTORE_STACK();
    return result;
}

/* G2-ABORT-SAVE-IN-PROGRESS */
Object g2_abort_save_in_progress()
{
    x_note_fn_call(228,276);
    return terminate_kb_save_or_backup_if_error_occurs();
}

/* G2-ABORT-SAVE-IN-PROGRESS-SYSTEM-RPC-INTERNAL */
Object g2_abort_save_in_progress_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,277);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_abort_save_in_progress();
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DELETE-MODULE-SYSTEM-RPC-INTERNAL */
Object g2_delete_module_system_rpc_internal(gensymed_symbol,module,
	    also_delete_associated_workspaces)
    Object gensymed_symbol, module, also_delete_associated_workspaces;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,278);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_delete_module(module,
		    also_delete_associated_workspaces);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CREATE-MODULE-SYSTEM-RPC-INTERNAL */
Object g2_create_module_system_rpc_internal(gensymed_symbol,module)
    Object gensymed_symbol, module;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,279);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_create_module(module);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qresolve_conflicts_automatically;  /* resolve-conflicts-automatically */

static Object Qbring_formats_up_to_date;  /* bring-formats-up-to-date */

static Object Qmerge_kb;           /* merge-kb */

static Object Qinstall_system_tables;  /* install-system-tables */

static Object Qupdate_before_loading;  /* update-before-loading */

/* G2-LOAD-KB-1-SYSTEM-RPC-INTERNAL */
Object g2_load_kb_1_system_rpc_internal(gensymed_symbol,path_name,
	    resolve_conflicts_automatically,bring_formats_up_to_date,
	    update_before_loading)
    Object gensymed_symbol, path_name, resolve_conflicts_automatically;
    Object bring_formats_up_to_date, update_before_loading;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, temp;
    Object item_or_value, x2, svref_new_value, options, temp_2;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object error_text_string;
    SI_Long gensymed_symbol_3, svref_arg_2;
    char temp_1;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,280);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)10L 
		    + (SI_Long)1L));
	    gensymed_symbol_3 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_3 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(gensymed_symbol_3 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_3 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = 
			Qresolve_conflicts_automatically;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = 
			Qresolve_conflicts_automatically;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(resolve_conflicts_automatically) 
			|| resolve_conflicts_automatically && 
			SYMBOLP(resolve_conflicts_automatically) ? 
			resolve_conflicts_automatically : 
			copy_evaluation_value_1(resolve_conflicts_automatically);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(resolve_conflicts_automatically) 
			|| resolve_conflicts_automatically && 
			SYMBOLP(resolve_conflicts_automatically) ? 
			resolve_conflicts_automatically : 
			copy_evaluation_value_1(resolve_conflicts_automatically);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = 
			Qbring_formats_up_to_date;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qbring_formats_up_to_date;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(bring_formats_up_to_date) || 
			bring_formats_up_to_date && 
			SYMBOLP(bring_formats_up_to_date) ? 
			bring_formats_up_to_date : 
			copy_evaluation_value_1(bring_formats_up_to_date);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(bring_formats_up_to_date) || 
			bring_formats_up_to_date && 
			SYMBOLP(bring_formats_up_to_date) ? 
			bring_formats_up_to_date : 
			copy_evaluation_value_1(bring_formats_up_to_date);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)7L)) = Qmerge_kb;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qmerge_kb;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Nil ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)8L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = Nil ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)9L)) = 
			Qinstall_system_tables;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)7L)) = Qinstall_system_tables;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = T ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)10L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = T ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)11L)) = 
			Qupdate_before_loading;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)9L)) = Qupdate_before_loading;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(update_before_loading) || 
			update_before_loading && 
			SYMBOLP(update_before_loading) ? 
			update_before_loading : 
			copy_evaluation_value_1(update_before_loading);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)12L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(update_before_loading) || 
			update_before_loading && 
			SYMBOLP(update_before_loading) ? 
			update_before_loading : 
			copy_evaluation_value_1(update_before_loading);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	    }
	    options = eval_cons_1(gensymed_symbol_1,Qab_structure);
	    temp_2 = g2_load_kb_extended(path_name,options);
	    reclaim_evaluation_value(options);
	    result = VALUES_1(temp_2);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_2 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_2;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-LOAD-KB-SYSTEM-RPC-INTERNAL */
Object g2_load_kb_system_rpc_internal(gensymed_symbol,path_name,
	    resolve_conflicts_automatically,bring_formats_up_to_date)
    Object gensymed_symbol, path_name, resolve_conflicts_automatically;
    Object bring_formats_up_to_date;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,281);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_load_kb(path_name,resolve_conflicts_automatically,
		    bring_formats_up_to_date);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MERGE-KB-1-SYSTEM-RPC-INTERNAL */
Object g2_merge_kb_1_system_rpc_internal(gensymed_symbol,path_name_string,
	    resolve_conflicts_automatically,bring_formats_up_to_date,
	    install_system_table_1,update_before_loading)
    Object gensymed_symbol, path_name_string, resolve_conflicts_automatically;
    Object bring_formats_up_to_date, install_system_table_1;
    Object update_before_loading;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, temp;
    Object item_or_value, x2, svref_new_value, options, temp_2;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object error_text_string;
    SI_Long gensymed_symbol_3, svref_arg_2;
    char temp_1;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,282);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = allocate_managed_array(1,FIX((SI_Long)10L 
		    + (SI_Long)1L));
	    gensymed_symbol_3 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_3 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(gensymed_symbol_3 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_3 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)3L)) = 
			Qresolve_conflicts_automatically;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = 
			Qresolve_conflicts_automatically;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(resolve_conflicts_automatically) 
			|| resolve_conflicts_automatically && 
			SYMBOLP(resolve_conflicts_automatically) ? 
			resolve_conflicts_automatically : 
			copy_evaluation_value_1(resolve_conflicts_automatically);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(resolve_conflicts_automatically) 
			|| resolve_conflicts_automatically && 
			SYMBOLP(resolve_conflicts_automatically) ? 
			resolve_conflicts_automatically : 
			copy_evaluation_value_1(resolve_conflicts_automatically);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)5L)) = 
			Qbring_formats_up_to_date;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qbring_formats_up_to_date;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(bring_formats_up_to_date) || 
			bring_formats_up_to_date && 
			SYMBOLP(bring_formats_up_to_date) ? 
			bring_formats_up_to_date : 
			copy_evaluation_value_1(bring_formats_up_to_date);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(bring_formats_up_to_date) || 
			bring_formats_up_to_date && 
			SYMBOLP(bring_formats_up_to_date) ? 
			bring_formats_up_to_date : 
			copy_evaluation_value_1(bring_formats_up_to_date);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)7L)) = Qmerge_kb;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qmerge_kb;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = T ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)8L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = T ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)9L)) = 
			Qinstall_system_tables;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)7L)) = Qinstall_system_tables;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(install_system_table_1) || 
			install_system_table_1 && 
			SYMBOLP(install_system_table_1) ? 
			install_system_table_1 : 
			copy_evaluation_value_1(install_system_table_1);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)10L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(install_system_table_1) || 
			install_system_table_1 && 
			SYMBOLP(install_system_table_1) ? 
			install_system_table_1 : 
			copy_evaluation_value_1(install_system_table_1);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_1,FIX((SI_Long)11L)) = 
			Qupdate_before_loading;
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)9L)) = Qupdate_before_loading;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = FIXNUMP(update_before_loading) || 
			update_before_loading && 
			SYMBOLP(update_before_loading) ? 
			update_before_loading : 
			copy_evaluation_value_1(update_before_loading);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_1,FIX((SI_Long)12L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		item_or_value = FIXNUMP(update_before_loading) || 
			update_before_loading && 
			SYMBOLP(update_before_loading) ? 
			update_before_loading : 
			copy_evaluation_value_1(update_before_loading);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	    }
	    options = eval_cons_1(gensymed_symbol_1,Qab_structure);
	    temp_2 = g2_merge_kb_extended(path_name_string,options);
	    reclaim_evaluation_value(options);
	    result = VALUES_1(temp_2);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_2 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_2;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MERGE-KB-SYSTEM-RPC-INTERNAL */
Object g2_merge_kb_system_rpc_internal(gensymed_symbol,path_name_string,
	    resolve_conflicts_automatically,bring_formats_up_to_date,
	    install_system_table_1)
    Object gensymed_symbol, path_name_string, resolve_conflicts_automatically;
    Object bring_formats_up_to_date, install_system_table_1;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,283);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_merge_kb(path_name_string,
		    resolve_conflicts_automatically,
		    bring_formats_up_to_date,Evaluation_false_value,
		    install_system_table_1);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-WARMBOOT-KB-SYSTEM-RPC-INTERNAL */
Object g2_warmboot_kb_system_rpc_internal(gensymed_symbol,path_name_string,
	    run_from_snapshot_time_as_fast_as_possible)
    Object gensymed_symbol, path_name_string;
    Object run_from_snapshot_time_as_fast_as_possible;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,284);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_warmboot_kb(path_name_string,
		    run_from_snapshot_time_as_fast_as_possible);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-LOAD-RUNTIME-DATA-SYSTEM-RPC-INTERNAL */
Object g2_load_runtime_data_system_rpc_internal(gensymed_symbol,
	    path_name_string,option)
    Object gensymed_symbol, path_name_string, option;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,285);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_load_runtime_data(path_name_string,option);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_source_code_control_update;  /* g2-source-code-control-update */

static Object Qscc_update;         /* scc-update */

static Object Qg2_source_code_control_edit;  /* g2-source-code-control-edit */

static Object Qscc_edit;           /* scc-edit */

static Object Qg2_source_code_control_unedit;  /* g2-source-code-control-unedit */

static Object Qscc_unedit;         /* scc-unedit */

static Object Qg2_source_code_control_revert;  /* g2-source-code-control-revert */

static Object Qscc_revert;         /* scc-revert */

static Object Qg2_source_code_control_commit;  /* g2-source-code-control-commit */

static Object Qscc_commit;         /* scc-commit */

static Object string_constant_37;  /* "Error in ~A: ~A" */

/* G2-SOURCE-CODE-CONTROL-OPERATION */
Object g2_source_code_control_operation varargs_1(int, n)
{
    Object function, pathname_1;
    Object log_message_for_commit_qm, operation, error_message_qm;
    Object top_of_stack, message_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(228,286);
    INIT_ARGS_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    log_message_for_commit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(function,Qg2_source_code_control_update))
	operation = Qscc_update;
    else if (EQ(function,Qg2_source_code_control_edit))
	operation = Qscc_edit;
    else if (EQ(function,Qg2_source_code_control_unedit))
	operation = Qscc_unedit;
    else if (EQ(function,Qg2_source_code_control_revert))
	operation = Qscc_revert;
    else if (EQ(function,Qg2_source_code_control_commit))
	operation = Qscc_commit;
    else
	operation = Qnil;
    error_message_qm = do_scc_command_1(3,operation,pathname_1,
	    log_message_for_commit_qm);
    if (error_message_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_37,
		function,error_message_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(Nil);
}

/* G2-SOURCE-CODE-CONTROL-UPDATE */
Object g2_source_code_control_update(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(228,287);
    return g2_source_code_control_operation(2,
	    Qg2_source_code_control_update,pathname_1);
}

/* G2-SOURCE-CODE-CONTROL-EDIT */
Object g2_source_code_control_edit(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(228,288);
    return g2_source_code_control_operation(2,Qg2_source_code_control_edit,
	    pathname_1);
}

/* G2-SOURCE-CODE-CONTROL-UNEDIT */
Object g2_source_code_control_unedit(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(228,289);
    return g2_source_code_control_operation(2,
	    Qg2_source_code_control_unedit,pathname_1);
}

/* G2-SOURCE-CODE-CONTROL-REVERT */
Object g2_source_code_control_revert(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(228,290);
    return g2_source_code_control_operation(2,
	    Qg2_source_code_control_revert,pathname_1);
}

/* G2-SOURCE-CODE-CONTROL-COMMIT */
Object g2_source_code_control_commit(pathname_1,log_message)
    Object pathname_1, log_message;
{
    x_note_fn_call(228,291);
    return g2_source_code_control_operation(3,
	    Qg2_source_code_control_commit,pathname_1,log_message);
}

/* G2-SOURCE-CODE-CONTROL-UPDATE-SYSTEM-RPC-INTERNAL */
Object g2_source_code_control_update_system_rpc_internal(gensymed_symbol,
	    path_name)
    Object gensymed_symbol, path_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,292);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_source_code_control_update(path_name);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SOURCE-CODE-CONTROL-EDIT-SYSTEM-RPC-INTERNAL */
Object g2_source_code_control_edit_system_rpc_internal(gensymed_symbol,
	    path_name)
    Object gensymed_symbol, path_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,293);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_source_code_control_edit(path_name);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SOURCE-CODE-CONTROL-UNEDIT-SYSTEM-RPC-INTERNAL */
Object g2_source_code_control_unedit_system_rpc_internal(gensymed_symbol,
	    path_name)
    Object gensymed_symbol, path_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,294);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_source_code_control_unedit(path_name);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SOURCE-CODE-CONTROL-REVERT-SYSTEM-RPC-INTERNAL */
Object g2_source_code_control_revert_system_rpc_internal(gensymed_symbol,
	    path_name)
    Object gensymed_symbol, path_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,295);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_source_code_control_revert(path_name);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SOURCE-CODE-CONTROL-COMMIT-SYSTEM-RPC-INTERNAL */
Object g2_source_code_control_commit_system_rpc_internal(gensymed_symbol,
	    path_name,log_message)
    Object gensymed_symbol, path_name, log_message;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,296);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_source_code_control_commit(path_name,
		    log_message);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-POST-MESSAGE */
Object g2_post_message(sequence_of_values,duration_or_other_ev)
    Object sequence_of_values, duration_or_other_ev;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, held_vector, x, elt_1, validated_elt, message_1;
    Object duration_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, next_index;
    SI_Long length_2;
    Declare_special(5);

    x_note_fn_call(228,297);
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
	      gensymed_symbol = sequence_of_values;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_2 = (SI_Long)0L;
	      x = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop:
	      if (next_index >= length_2)
		  goto end_loop;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      x = validated_elt;
	      write_block_or_evaluation_value(2,x,T);
	      goto next_loop;
	    end_loop:;
	      message_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    duration_qm = FIXNUMP(duration_or_other_ev) ? duration_or_other_ev : Qnil;
    reclaim_evaluation_value(sequence_of_values);
    reclaim_evaluation_value(duration_or_other_ev);
    return post_on_message_board(5,message_1,Nil,duration_qm,Nil,Nil);
}

static Object Qg2_post_message;    /* g2-post-message */

/* G2-POST-MESSAGE-SYSTEM-RPC-INTERNAL */
Object g2_post_message_system_rpc_internal(gensymed_symbol,
	    sequence_of_values,duration_or_false)
    Object gensymed_symbol, sequence_of_values, duration_or_false;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp_1;
    Object error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,298);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_5,Qg2_post_message,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    gensymed_symbol_1 = g2_post_message(sequence_of_values,
		    duration_or_false);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* EVAL-FLATTEN-SYMBOL-TREE-FOR-USER-MODES */
Object eval_flatten_symbol_tree_for_user_modes(symbol_tree)
    Object symbol_tree;
{
    Object flattened_tree, old_leaf, branch, ab_loop_list_, new_list, temp;

    x_note_fn_call(228,299);
    flattened_tree = Nil;
    old_leaf = Nil;
    branch = Nil;
    ab_loop_list_ = symbol_tree;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    branch = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(branch)) {
	if ( !EQ(branch,old_leaf)) {
	    old_leaf = branch;
	    flattened_tree = eval_cons_1(branch,flattened_tree);
	}
    }
    else if (LISTP(branch)) {
	new_list = eval_flatten_symbol_tree_for_user_modes(branch);
	if (new_list)
	    flattened_tree = nconc2(flattened_tree,new_list);
    }
    else;
    goto next_loop;
  end_loop:
    temp = flattened_tree;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qnon_built_in_g2_user_mode;  /* non-built-in-g2-user-mode */

static Object Qadministrator;      /* administrator */

/* G2-GET-KNOWN-USER-MODES */
Object g2_get_known_user_modes()
{
    Object directory_of_modes;

    x_note_fn_call(228,300);
    directory_of_modes = get_directory_contents(Qnon_built_in_g2_user_mode);
    if (SYMBOLP(directory_of_modes) && directory_of_modes)
	return allocate_evaluation_sequence(eval_list_2(Qadministrator,
		directory_of_modes));
    else
	return allocate_evaluation_sequence(eval_flatten_symbol_tree_for_user_modes(directory_of_modes));
}

/* G2-GET-KNOWN-USER-MODES-SYSTEM-RPC-INTERNAL */
Object g2_get_known_user_modes_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(228,301);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_known_user_modes();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* INITIAL-ACTIVE-STUBS */
Object initial_active_stubs(class_1)
    Object class_1;
{
    x_note_fn_call(228,302);
    return VALUES_1(Nil);
}

static Object Qactive_stubs;       /* active-stubs */

/* GET-ACTIVE-STUBS */
Object get_active_stubs(g2_foreign_object)
    Object g2_foreign_object;
{
    Object temp;

    x_note_fn_call(228,303);
    if ( !TRUEP(get_lookup_slot_value_given_default(g2_foreign_object,
	    Qactive_stubs,Nil)))
	set_non_savable_lookup_slot_value(g2_foreign_object,Qactive_stubs,
		allocate_evaluation_sequence(Nil));
    temp = 
	    copy_evaluation_sequence(get_lookup_slot_value_given_default(g2_foreign_object,
	    Qactive_stubs,Nil));
    return VALUES_1(temp);
}

/* SET-ACTIVE-STUBS */
Object set_active_stubs(g2_foreign_object,new_value)
    Object g2_foreign_object, new_value;
{
    Object old_value, temp;

    x_note_fn_call(228,304);
    old_value = get_lookup_slot_value_given_default(g2_foreign_object,
	    Qactive_stubs,Nil);
    set_non_savable_lookup_slot_value(g2_foreign_object,Qactive_stubs,
	    copy_evaluation_sequence(new_value));
    temp =  !(FIXNUMP(old_value) || SYMBOLP(old_value) || 
	    SIMPLE_VECTOR_P(old_value)) ? 
	    reclaim_if_evaluation_value_1(old_value) : Nil;
    return VALUES_1(temp);
}

/* INITIAL-LATENT-LISTENERS */
Object initial_latent_listeners(class_1)
    Object class_1;
{
    x_note_fn_call(228,305);
    return VALUES_1(Nil);
}

static Object Qlatent_listeners;   /* latent-listeners */

/* GET-LATENT-LISTENERS */
Object get_latent_listeners(g2_java_bean)
    Object g2_java_bean;
{
    Object temp;

    x_note_fn_call(228,306);
    temp = get_lookup_slot_value_given_default(g2_java_bean,
	    Qlatent_listeners,Nil) ? 
	    copy_evaluation_structure(get_lookup_slot_value_given_default(g2_java_bean,
	    Qlatent_listeners,Nil)) : Qnil;
    return VALUES_1(temp);
}

/* SET-LATENT-LISTENERS */
Object set_latent_listeners(g2_java_bean,new_value)
    Object g2_java_bean, new_value;
{
    Object old_value, temp;

    x_note_fn_call(228,307);
    old_value = get_lookup_slot_value_given_default(g2_java_bean,
	    Qlatent_listeners,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_java_bean,Qlatent_listeners);
    set_lookup_slot_value_1(g2_java_bean,Qlatent_listeners,new_value ? 
	    copy_evaluation_structure(new_value) : Qnil);
    temp = old_value ? reclaim_evaluation_structure(old_value) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-G2-JAVA-BEAN-MEDIA-BIN-VALUE */
Object reclaim_g2_java_bean_media_bin_value(media_bin,gensymed_symbol)
    Object media_bin, gensymed_symbol;
{
    x_note_fn_call(228,308);
    if (media_bin)
	delete_frame(media_bin);
    return VALUES_1(Nil);
}

/* INITIAL-INTERNAL-MEDIA-BIN */
Object initial_internal_media_bin(class_1)
    Object class_1;
{
    x_note_fn_call(228,309);
    return VALUES_1(Nil);
}

static Object Qg2_java_bean_media_bin;  /* g2-java-bean-media-bin */

/* GET-INTERNAL-MEDIA-BIN */
Object get_internal_media_bin(g2_java_bean)
    Object g2_java_bean;
{
    Object temp;

    x_note_fn_call(228,310);
    temp = get_lookup_slot_value_given_default(g2_java_bean,
	    Qg2_java_bean_media_bin,Nil);
    return VALUES_1(temp);
}

static Object Qg2_java_bean;       /* g2-java-bean */

static Object Qg2_foreign_serializable;  /* g2-foreign-serializable */

/* INITIALIZE-FOR-G2-JAVA-BEAN */
Object initialize_for_g2_java_bean(g2_java_bean)
    Object g2_java_bean;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object sub_class_bit_vector, media_bin;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;

    x_note_fn_call(228,311);
    frame = g2_java_bean;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_java_bean)) {
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
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qg2_foreign_serializable,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(g2_java_bean,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	media_bin = get_lookup_slot_value_given_default(g2_java_bean,
		Qg2_java_bean_media_bin,Nil);
	if ( !TRUEP(media_bin))
	    return make_media_bin_for_g2_java_bean(g2_java_bean);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

void view_g2_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qclasses_which_define, Qinitialize, Qinitialize_for_g2_java_bean;
    Object AB_package, string_constant_60, list_constant_199;
    Object string_constant_58, string_constant_57, Qg2_foreign_savable;
    Object string_constant_59, list_constant_198, Qget_internal_media_bin;
    Object Qinitial_internal_media_bin, list_constant_197, list_constant_195;
    Object Qinternal_media_bin, list_constant_196, list_constant_2, Qab_or;
    Object Qmedia_bin, Qab_class, Qvirtual_attributes_local_to_class;
    Object Qslot_value_reclaimer, Qreclaim_g2_java_bean_media_bin_value;
    Object Qset_latent_listeners, Qget_latent_listeners;
    Object Qinitial_latent_listeners, list_constant_76, string_constant_56;
    Object list_constant_194, string_constant_55, string_constant_54;
    Object Qg2_foreign_object, Qset_active_stubs, Qget_active_stubs;
    Object Qinitial_active_stubs, list_constant_1, list_constant_193;
    Object string_constant_53, list_constant_192, string_constant_52;
    Object string_constant_51, Qobject;
    Object Qg2_get_known_user_modes_system_rpc_internal;
    Object Qg2_get_known_user_modes, Qsystem_defined_rpc, list_constant_191;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_post_message_system_rpc_internal, list_constant_190;
    Object list_constant_189, list_constant_188, Qduration_or_false;
    Object list_constant_187, Qsequence_of_values;
    Object Qg2_source_code_control_commit_system_rpc_internal;
    Object list_constant_186, list_constant_185, list_constant_169;
    Object list_constant_41, Qlog_message;
    Object Qg2_source_code_control_revert_system_rpc_internal;
    Object list_constant_184;
    Object Qg2_source_code_control_unedit_system_rpc_internal;
    Object Qg2_source_code_control_edit_system_rpc_internal;
    Object Qg2_source_code_control_update_system_rpc_internal;
    Object Qg2_load_runtime_data_system_rpc_internal, Qg2_load_runtime_data;
    Object list_constant_77, list_constant_183, list_constant_182;
    Object list_constant_175, list_constant_10, Qoption;
    Object Qg2_warmboot_kb_system_rpc_internal, Qg2_warmboot_kb;
    Object list_constant_181, list_constant_180, list_constant_149;
    Object Qrun_from_snapshot_time_as_fast_as_possible;
    Object Qg2_merge_kb_system_rpc_internal, Qg2_merge_kb, list_constant_179;
    Object list_constant_176, list_constant_171, list_constant_170;
    Object Qg2_merge_kb_1_system_rpc_internal, Qg2_merge_kb_1;
    Object list_constant_178, list_constant_177, list_constant_172;
    Object Qinstall_system_table, Qpath_name_string;
    Object Qg2_load_kb_system_rpc_internal, Qg2_load_kb, list_constant_174;
    Object Qg2_load_kb_1_system_rpc_internal, Qg2_load_kb_1, list_constant_173;
    Object Qpath_name, Qg2_create_module_system_rpc_internal;
    Object Qg2_create_module, list_constant_168, list_constant_153;
    Object Qg2_delete_module_system_rpc_internal, Qg2_delete_module;
    Object list_constant_167, list_constant_166;
    Object Qalso_delete_associated_workspaces;
    Object Qg2_abort_save_in_progress_system_rpc_internal;
    Object Qg2_abort_save_in_progress, Qg2_finish_save_kb_system_rpc_internal;
    Object Qg2_finish_save_kb, list_constant_156, list_constant_165;
    Object Qg2_continue_save_kb_system_rpc_internal, Qg2_continue_save_kb;
    Object list_constant_151, Qg2_start_save_kb_system_rpc_internal;
    Object Qg2_start_save_kb, list_constant_164, list_constant_163;
    Object list_constant_162, list_constant_150, list_constant_161, Qwindow;
    Object Qitem_or_datum, list_constant_62, Qtype_of_file;
    Object Qg2_start_save_module_1_system_rpc_internal;
    Object Qg2_start_save_module_1, list_constant_160, list_constant_159;
    Object list_constant_158, list_constant_157, list_constant_154;
    Object list_constant_152, list_constant_61;
    Object Qg2_start_save_module_system_rpc_internal, Qg2_start_save_module;
    Object list_constant_155, list_constant_40, Qmodule, Qwindow_or_not;
    Object Qab_pathname, Qg2_modules_with_unsaved_changes_system_rpc_internal;
    Object Qg2_modules_with_unsaved_changes;
    Object Qg2_set_all_items_in_module_explicitly_editable_system_rpc_internal;
    Object Qg2_set_all_items_in_module_explicitly_editable, list_constant_147;
    Object Qg2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal;
    Object Qg2_set_item_and_all_its_subblocks_explicitly_editable;
    Object Qg2_set_item_explicitly_editable_system_rpc_internal;
    Object Qg2_set_item_explicitly_editable;
    Object Qg2_item_is_editable_system_rpc_internal, Qg2_item_is_editable;
    Object list_constant_148, list_constant_146, list_constant_7;
    Object list_constant_145, list_constant_30;
    Object Qg2_disable_inlining_system_rpc_internal, Qg2_disable_inlining;
    Object Qg2_enable_inlining_system_rpc_internal, Qg2_enable_inlining;
    Object Qg2_copy_file_system_rpc_internal, Qg2_copy_file, list_constant_144;
    Object Qg2_rename_file_system_rpc_internal, Qg2_rename_file;
    Object list_constant_143, list_constant_142, Qnew_filestring;
    Object Qold_filestring, Qg2_delete_file_system_rpc_internal;
    Object Qg2_delete_file, list_constant_131;
    Object Qg2_file_host_string_system_rpc_internal, Qg2_file_host_string;
    Object Qg2_file_device_string_system_rpc_internal, Qg2_file_device_string;
    Object Qg2_file_directory_string_system_rpc_internal;
    Object Qg2_file_directory_string;
    Object Qg2_file_directory_string_to_list_system_rpc_internal;
    Object Qg2_file_directory_string_to_list, list_constant_110;
    Object Qg2_file_directory_list_to_string_system_rpc_internal;
    Object Qg2_file_directory_list_to_string, list_constant_141;
    Object list_constant_140, Qdirectory_list;
    Object Qg2_file_base_name_string_system_rpc_internal;
    Object Qg2_file_base_name_string;
    Object Qg2_file_extension_string_system_rpc_internal;
    Object Qg2_file_extension_string;
    Object Qg2_file_version_string_system_rpc_internal;
    Object Qg2_file_version_string;
    Object Qg2_collect_into_filestring_system_rpc_internal;
    Object Qg2_collect_into_filestring, list_constant_139, list_constant_138;
    Object list_constant_137, list_constant_136, list_constant_135;
    Object list_constant_134, list_constant_133, Qversion, Qextension;
    Object Qroot_name, Qab_directory, Qdevice, Qhost;
    Object Qg2_partition_filestring_system_rpc_internal;
    Object Qg2_partition_filestring, list_constant_132;
    Object Qg2_type_of_file_system_system_rpc_internal;
    Object Qg2_type_of_file_system, list_constant_57;
    Object Qg2_file_exists_system_rpc_internal, Qg2_file_exists;
    Object list_constant_130, Qfilestring;
    Object Qg2_file_names_are_identical_system_rpc_internal;
    Object Qg2_file_names_are_identical, list_constant_129, list_constant_128;
    Object list_constant_127, Qfilestring2, Qfilestring1;
    Object Qg2_length_of_file_system_rpc_internal, Qg2_length_of_file;
    Object list_constant_84, list_constant_126, list_constant_125;
    Object list_constant_124, Qab_file_stream, Qg2_stream;
    Object Qg2_latest_date_file_was_modified_system_rpc_internal;
    Object Qg2_latest_date_file_was_modified, list_constant_113;
    Object list_constant_123;
    Object Qg2_latest_date_file_was_accessed_system_rpc_internal;
    Object Qg2_latest_date_file_was_accessed;
    Object Qg2_latest_date_file_attributes_were_changed_system_rpc_internal;
    Object Qg2_latest_date_file_attributes_were_changed, list_constant_122;
    Object Qfile_string, Qg2_directory_exists_system_rpc_internal;
    Object Qg2_directory_exists, list_constant_109;
    Object Qg2_default_directory_system_rpc_internal, Qg2_default_directory;
    Object Qg2_change_default_directory_system_rpc_internal;
    Object Qg2_change_default_directory, list_constant_121, list_constant_120;
    Object Qnew_default;
    Object Qg2_disk_space_available_in_directory_system_rpc_internal;
    Object Qg2_disk_space_available_in_directory;
    Object Qg2_devices_on_machine_system_rpc_internal, Qg2_devices_on_machine;
    Object Qg2_spawn_process_to_run_command_line_system_rpc_internal;
    Object Qg2_spawn_process_to_run_command_line, list_constant_119;
    Object Qg2_spawn_process_with_arguments_system_rpc_internal;
    Object Qg2_spawn_process_with_arguments, list_constant_118, Qcommand;
    Object Qg2_process_exists_system_rpc_internal, Qg2_process_exists;
    Object list_constant_117, list_constant_116, list_constant_42, Qprocess_id;
    Object Qg2_kill_process_system_rpc_internal, Qg2_kill_process;
    Object list_constant_115, list_constant_114;
    Object Qg2_unix_time_at_start_system_rpc_internal, Qg2_unix_time_at_start;
    Object Qg2_unix_time_system_rpc_internal, Qg2_unix_time;
    Object Qg2_get_build_version_system_rpc_internal, Qg2_get_build_version;
    Object Qg2_get_software_version_system_rpc_internal;
    Object Qg2_get_software_version;
    Object Qg2_get_structured_version_system_rpc_internal;
    Object Qg2_get_structured_version, list_constant_97;
    Object Qg2_get_port_number_or_name_given_index_system_rpc_internal;
    Object Qg2_get_port_number_or_name_given_index, list_constant_112;
    Object list_constant_111, Qindex;
    Object Qg2_get_port_number_or_name_system_rpc_internal;
    Object Qg2_get_port_number_or_name, Qg2_get_host_name_system_rpc_internal;
    Object Qg2_get_host_name;
    Object Qg2_subdirectories_in_directory_system_rpc_internal;
    Object Qg2_subdirectories_in_directory;
    Object Qg2_files_in_directory_system_rpc_internal, Qg2_files_in_directory;
    Object list_constant_108, Qtext_list, list_constant_107, Qdirectory_string;
    Object Qg2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal;
    Object Qg2_subscribe_to_unsolicited_dialogs_system_rpc_internal;
    Object list_constant_106, list_constant_105, list_constant_104;
    Object list_constant_91, Qdialog_callback_data, Qdialog_callback;
    Object Qg2_return_values_to_unsolicited_dialog_system_rpc_internal;
    Object list_constant_103, list_constant_88, list_constant_102;
    Object list_constant_101, Qdialog_values, Qdialog_sequence_number;
    Object Qnotify_t2_for_local_recompile;
    Object Qg2_unsubscribe_to_file_progress_changes_system_rpc_internal;
    Object Qg2_subscribe_to_file_progress_changes_system_rpc_internal;
    Object list_constant_100, list_constant_99, list_constant_98;
    Object Qprogress_callback_data, Qprogress_callback, list_constant_28;
    Object Qmodule_load_request, Qfile_progress;
    Object Qg2_unsubscribe_to_modules_system_rpc_internal;
    Object Qg2_subscribe_to_modules_system_rpc_internal, list_constant_96;
    Object list_constant_95, list_constant_94, list_constant_93;
    Object list_constant_92, Qmodule_information_callback_data;
    Object Qmodule_information_callback, Qmodule_callback_data;
    Object list_constant_43, Qmodule_callback;
    Object Qg2_unsubscribe_to_field_edit_actions_system_rpc_internal;
    Object list_constant_86;
    Object Qg2_subscribe_to_field_edit_actions_system_rpc_internal;
    Object list_constant_90, list_constant_89, list_constant_82;
    Object list_constant_81, list_constant_87, Qclient_item, list_constant_72;
    Object Qg2_unsubscribe_to_workspaces_showing_system_rpc_internal;
    Object list_constant_85;
    Object Qg2_subscribe_to_workspaces_showing_system_rpc_internal;
    Object list_constant_83, list_constant_80, Quser_data, Qcallback;
    Object list_constant_75, string_constant_50, list_constant_79;
    Object string_constant_49, string_constant_48, Qget_uses_floating_license;
    Object Qinitial_uses_floating_license, list_constant_78;
    Object Quses_floating_license, Qui_client_item, Qget_ui_client_interface;
    Object Qinitial_ui_client_interface, list_constant_9;
    Object Qget_ui_client_mode_is_valid, Qinitial_ui_client_mode_is_valid;
    Object Qui_client_mode_is_valid, Qget_ui_client_user_is_valid;
    Object Qinitial_ui_client_user_is_valid, Qui_client_user_is_valid;
    Object Qget_ui_client_connection_status;
    Object Qinitial_ui_client_connection_status, list_constant_31;
    Object list_constant_58, Qget_ui_client_specific_language;
    Object Qinitial_ui_client_specific_language, Qui_client_specific_language;
    Object Qget_ui_client_user_name_in_operating_system;
    Object Qinitial_ui_client_user_name_in_operating_system, list_constant_60;
    Object Qui_client_user_name_in_operating_system;
    Object Qget_ui_client_time_of_last_connection;
    Object Qinitial_ui_client_time_of_last_connection;
    Object Qui_client_time_of_last_connection;
    Object Qget_ui_client_operating_system_type;
    Object Qinitial_ui_client_operating_system_type;
    Object Qui_client_operating_system_type, Qget_ui_client_remote_host_name;
    Object Qinitial_ui_client_remote_host_name, Qui_client_remote_host_name;
    Object Qget_ui_client_user_name, Qinitial_ui_client_user_name;
    Object Qui_client_user_name, Qset_ui_client_user_mode;
    Object Qget_ui_client_user_mode, Qinitial_ui_client_user_mode;
    Object Qui_client_user_mode, Qdisassociate_workspace_from_ui_session;
    Object Qg2_release_ui_client_session_system_rpc_internal, list_constant_74;
    Object list_constant_73, Qclient_session;
    Object Qg2_make_ui_client_session_system_rpc_internal, list_constant_71;
    Object list_constant_70, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_65;
    Object list_constant_64, list_constant_63, list_constant_46;
    Object list_constant_59, Qworkspace_showing_callback_qm, Qos_type;
    Object Qhost_name, Qlanguage, Quser_name_in_os_qm, Qencoded_password;
    Object Quser_name, Quser_mode, Qg2_validate_named_tw2_system_rpc_internal;
    Object Qg2_validate_named_tw2, list_constant_56, list_constant_55;
    Object list_constant_54, list_constant_53, list_constant_52;
    Object list_constant_51, list_constant_50, list_constant_49;
    Object list_constant_48, list_constant_47, Qdesired_license_level;
    Object list_constant_45, Qend_date, Qstart_date, list_constant_44, Qdatum;
    Object Qcode5, Qcode4, Qcode3, Qcode2, Qcode1, Qmachine_id, Qnonce;
    Object Qg2_allocate_session_id_system_rpc_internal;
    Object Qui_client_session_user_name_in_operating_system;
    Object Qui_client_session_operating_system_type;
    Object Qui_client_session_network_host_name, list_constant_39;
    Object list_constant_38, Qshowing_representation_user_data_value;
    Object list_constant_36, Qcallback_representation_callback_serial_number;
    Object Qcallback_representation_callback_procedure;
    Object Qrepresentation_address, list_constant_37;
    Object Qcallback_representation_callback_subscription_handle;
    Object list_constant_35, Qitem_representation_user_data_value;
    Object Qitem_representation_denotation, list_constant_34;
    Object Qui_client_session_nonce, Qui_client_session_status;
    Object Qui_client_session_license_level_qm;
    Object Qui_client_session_encoded_password;
    Object Qreclaim_ui_client_session_parent_interface_value;
    Object Qui_client_session_parent_interface;
    Object Qreclaim_ui_client_session_workspaces_value;
    Object Qui_client_session_workspaces;
    Object Qreclaim_ui_client_interface_sessions_value;
    Object Qui_client_interface_sessions, string_constant_47;
    Object string_constant_46, string_constant_45, list_constant_33;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, Qgsi_interface;
    Object Qget_workspace_representation_type;
    Object Qget_workspace_representation_type_for_kb_workspace;
    Object Qget_workspace_representation_type_for_type_in_box;
    Object Qget_workspace_representation_type_for_slider;
    Object Qget_workspace_representation_type_for_check_box;
    Object Qget_workspace_representation_type_for_radio_button;
    Object Qget_workspace_representation_type_for_action_button;
    Object Qget_workspace_representation_type_for_freeform_table;
    Object Qget_workspace_representation_type_for_chart;
    Object Qget_workspace_representation_type_for_graph;
    Object Qget_workspace_representation_type_for_trend_chart;
    Object Qget_workspace_representation_type_for_meter;
    Object Qget_workspace_representation_type_for_dial, Qreadout_table;
    Object Qget_workspace_representation_type_for_readout_table, Qtable;
    Object Qget_workspace_representation_type_for_table;
    Object Qget_workspace_representation_type_for_text_box;
    Object Qget_workspace_representation_type_for_connection;
    Object Qget_workspace_representation_type_for_loose_end, Qentity;
    Object Qget_workspace_representation_type_for_entity, Qsystem_item;
    Object Qget_workspace_representation_type_for_system_item;
    Object Qgeneric_method_lambda_list, list_constant_32, Qframe;
    Object Qset_do_not_strip_text_mark, Qget_do_not_strip_text_mark;
    Object Qinitial_do_not_strip_text_mark, Qdo_not_strip_text_mark;
    Object Qset_strip_text_mark, Qget_strip_text_mark;
    Object Qinitial_strip_text_mark, Qstrip_text_mark, Kwithin_putter;
    Object Kevent_updates, Qget_type_in_box_variable_or_parameter;
    Object Qinitial_type_in_box_variable_or_parameter, list_constant_23;
    Object Qtype_in_box_variable_or_parameter, Qget_text, Qinitial_text;
    Object list_constant_6, Qname_box, Qget_connection_position_sequence;
    Object Qinitial_connection_position_sequence, list_constant_25;
    Object Qconnection_position_sequence, Qget_connection_is_directed;
    Object Qinitial_connection_is_directed, Qconnection_is_directed;
    Object Qget_representation_type, Qinitial_representation_type;
    Object Qrepresentation_type, Qget_attribute_display_items;
    Object Qinitial_attribute_display_items, list_constant_4, list_constant_26;
    Object Qattribute_display_items, Qget_name_box_item;
    Object Qinitial_name_box_item, Qname_box_item, Qget_layer_position;
    Object Qinitial_layer_position, list_constant_29, Qlayer_position;
    Object Qset_item_color_pattern, Qget_item_color_pattern;
    Object Qinitial_item_color_pattern, list_constant_27, Qitem_color_pattern;
    Object list_constant_12, Qset_type_in_box_value, Qget_type_in_box_value;
    Object Qinitial_type_in_box_value, list_constant_24, Qtype_in_box_value;
    Object Qset_slider_value, Qget_slider_value, Qinitial_slider_value;
    Object list_constant_22, Qslider_value, Qbutton_status, Qset_button_status;
    Object Qget_button_status, Qinitial_button_status, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, Qget_value_to_display, Qinitial_value_to_display;
    Object list_constant_16, Qvalue_to_display, list_constant_15;
    Object list_constant_14, Qget_format_type, Qinitial_format_type;
    Object list_constant_13, Qformat_type, list_constant_3;
    Object Qget_text_y_magnification, Qinitial_text_y_magnification;
    Object Qtext_y_magnification, Qget_text_x_magnification;
    Object Qinitial_text_x_magnification, Qtext_x_magnification;
    Object Qget_table_layout, Qinitial_table_layout, list_constant_11;
    Object list_constant_5, Qtable_layout, Qget_represented_item;
    Object Qinitial_represented_item, list_constant_8, Qrepresented_item;
    Object Qget_table_font_size, Qinitial_table_font_size, Qtable_font_size;
    Object Qget_table_rows, Qinitial_table_rows, Qno_item;
    Object Qtable_property_getter, Qtype_in_box_property_getter;
    Object Qslider_property_getter, Qcheck_box_property_getter;
    Object Qradio_button_property_getter, Qaction_button_property_getter;
    Object Qchart_property_getter, Qtrend_chart_property_getter;
    Object Qmeter_property_getter, Qdial_property_getter;
    Object Qtext_box_property_getter, Qconnection_property_getter;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(228,312);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qsession_id = STATIC_SYMBOL("SESSION-ID",AB_package);
    Qws_representation = STATIC_SYMBOL("WS-REPRESENTATION",AB_package);
    Qobject_definition_representation = 
	    STATIC_SYMBOL("OBJECT-DEFINITION-REPRESENTATION",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtc_representation = STATIC_SYMBOL("TC-REPRESENTATION",AB_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qstyle = STATIC_SYMBOL("STYLE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qconnection_property_getter = 
	    STATIC_SYMBOL("CONNECTION-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qconnection_property_getter,
	    STATIC_FUNCTION(connection_property_getter,NIL,FALSE,1,1));
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qfont = STATIC_SYMBOL("FONT",AB_package);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    Qtext_line_color = STATIC_SYMBOL("TEXT-LINE-COLOR",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qtext_background_color = STATIC_SYMBOL("TEXT-BACKGROUND-COLOR",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qleft_margin = STATIC_SYMBOL("LEFT-MARGIN",AB_package);
    Qtop_margin = STATIC_SYMBOL("TOP-MARGIN",AB_package);
    Qright_margin = STATIC_SYMBOL("RIGHT-MARGIN",AB_package);
    Qbottom_margin = STATIC_SYMBOL("BOTTOM-MARGIN",AB_package);
    Qindentation_margin = STATIC_SYMBOL("INDENTATION-MARGIN",AB_package);
    Qtext_line_height = STATIC_SYMBOL("TEXT-LINE-HEIGHT",AB_package);
    Qtext_line_spacing = STATIC_SYMBOL("TEXT-LINE-SPACING",AB_package);
    Qborder_width = STATIC_SYMBOL("BORDER-WIDTH",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qtext_lines = STATIC_SYMBOL("TEXT-LINES",AB_package);
    Qempty = STATIC_SYMBOL("EMPTY",AB_package);
    Qitem_overrides = STATIC_SYMBOL("ITEM-OVERRIDES",AB_package);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    Qtext_box_property_getter = STATIC_SYMBOL("TEXT-BOX-PROPERTY-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtext_box_property_getter,
	    STATIC_FUNCTION(text_box_property_getter,NIL,FALSE,1,1));
    Qlow_value = STATIC_SYMBOL("LOW-VALUE",AB_package);
    Qhigh_value = STATIC_SYMBOL("HIGH-VALUE",AB_package);
    Qincrement = STATIC_SYMBOL("INCREMENT",AB_package);
    Qdial_property_getter = STATIC_SYMBOL("DIAL-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qdial_property_getter,
	    STATIC_FUNCTION(dial_property_getter,NIL,FALSE,1,1));
    Qmeter_property_getter = STATIC_SYMBOL("METER-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qmeter_property_getter,
	    STATIC_FUNCTION(meter_property_getter,NIL,FALSE,1,1));
    Qtrend_chart_time_axis_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-TIME-AXIS-GRAMMAR-SPEC",AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qtrend_chart_value_axes_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-VALUE-AXES-GRAMMAR-SPEC",AB_package);
    Qtrend_chart_point_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-POINT-FORMATS-GRAMMAR-SPEC",AB_package);
    Qtrend_chart_connector_formats_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-CONNECTOR-FORMATS-GRAMMAR-SPEC",
	    AB_package);
    Qtrend_chart_format_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-FORMAT-GRAMMAR-SPEC",AB_package);
    Qtrend_chart_plots_grammar_spec = 
	    STATIC_SYMBOL("TREND-CHART-PLOTS-GRAMMAR-SPEC",AB_package);
    Qtrend_chart_active = STATIC_SYMBOL("TREND-CHART-ACTIVE",AB_package);
    Qtitle = STATIC_SYMBOL("TITLE",AB_package);
    Qplots = STATIC_SYMBOL("PLOTS",AB_package);
    Qvalue_axes = STATIC_SYMBOL("VALUE-AXES",AB_package);
    Qtime_axis = STATIC_SYMBOL("TIME-AXIS",AB_package);
    Qpoint_formats = STATIC_SYMBOL("POINT-FORMATS",AB_package);
    Qconnector_formats = STATIC_SYMBOL("CONNECTOR-FORMATS",AB_package);
    Qtrend_chart_format = STATIC_SYMBOL("TREND-CHART-FORMAT",AB_package);
    Qcurrent_g2_time = STATIC_SYMBOL("CURRENT-G2-TIME",AB_package);
    Qtimespan = STATIC_SYMBOL("TIMESPAN",AB_package);
    Qvalue_axis_extrema = STATIC_SYMBOL("VALUE-AXIS-EXTREMA",AB_package);
    Qinitial_plot_data = STATIC_SYMBOL("INITIAL-PLOT-DATA",AB_package);
    Qtrend_chart_property_getter = 
	    STATIC_SYMBOL("TREND-CHART-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtrend_chart_property_getter,
	    STATIC_FUNCTION(trend_chart_property_getter,NIL,FALSE,1,1));
    Qchart_property_getter = STATIC_SYMBOL("CHART-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qchart_property_getter,
	    STATIC_FUNCTION(chart_property_getter,NIL,FALSE,1,1));
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    Qaction_button_property_getter = 
	    STATIC_SYMBOL("ACTION-BUTTON-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qaction_button_property_getter,
	    STATIC_FUNCTION(action_button_property_getter,NIL,FALSE,1,1));
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    Qradio_button_property_getter = 
	    STATIC_SYMBOL("RADIO-BUTTON-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qradio_button_property_getter,
	    STATIC_FUNCTION(radio_button_property_getter,NIL,FALSE,1,1));
    Qcheck_box_property_getter = STATIC_SYMBOL("CHECK-BOX-PROPERTY-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_box_property_getter,
	    STATIC_FUNCTION(check_box_property_getter,NIL,FALSE,1,1));
    Qslider_readout_properties = STATIC_SYMBOL("SLIDER-READOUT-PROPERTIES",
	    AB_package);
    Qminimum_value = STATIC_SYMBOL("MINIMUM-VALUE",AB_package);
    Qmaximum_value = STATIC_SYMBOL("MAXIMUM-VALUE",AB_package);
    Qslider_property_getter = STATIC_SYMBOL("SLIDER-PROPERTY-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qslider_property_getter,
	    STATIC_FUNCTION(slider_property_getter,NIL,FALSE,1,1));
    Qlast_value_displayed = STATIC_SYMBOL("LAST-VALUE-DISPLAYED",AB_package);
    Qtype_in_box_property_getter = 
	    STATIC_SYMBOL("TYPE-IN-BOX-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtype_in_box_property_getter,
	    STATIC_FUNCTION(type_in_box_property_getter,NIL,FALSE,1,1));
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qtable_property_getter = STATIC_SYMBOL("TABLE-PROPERTY-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtable_property_getter,
	    STATIC_FUNCTION(table_property_getter,NIL,FALSE,1,1));
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qleft_text = STATIC_SYMBOL("LEFT-TEXT",AB_package);
    Qleft_text_line_color = STATIC_SYMBOL("LEFT-TEXT-LINE-COLOR",AB_package);
    Qright_text = STATIC_SYMBOL("RIGHT-TEXT",AB_package);
    Qright_text_line_color = STATIC_SYMBOL("RIGHT-TEXT-LINE-COLOR",AB_package);
    temp = CONS(Qtable_rows,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtable),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtable_rows,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtable),
	    Qvirtual_attributes_local_to_class,temp);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qab_class,Qtable);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_1 = STATIC_CONS(Qsequence,Qnil);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_2 = STATIC_CONS(Qno_item,Qnil);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_1,
	    list_constant_2);
    Qinitial_table_rows = STATIC_SYMBOL("INITIAL-TABLE-ROWS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_table_rows,
	    STATIC_FUNCTION(initial_table_rows,NIL,FALSE,1,1));
    Qget_table_rows = STATIC_SYMBOL("GET-TABLE-ROWS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_table_rows,STATIC_FUNCTION(get_table_rows,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qtable_rows,list_constant_3,list_constant_4,Qnil,
	    SYMBOL_FUNCTION(Qinitial_table_rows),
	    SYMBOL_FUNCTION(Qget_table_rows),Nil);
    Qtable_font_size = STATIC_SYMBOL("TABLE-FONT-SIZE",AB_package);
    temp = CONS(Qtable_font_size,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtable_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtable_font_size,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtable_item),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qab_class,Qtable_item);
    Qinitial_table_font_size = STATIC_SYMBOL("INITIAL-TABLE-FONT-SIZE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_table_font_size,
	    STATIC_FUNCTION(initial_table_font_size,NIL,FALSE,1,1));
    Qget_table_font_size = STATIC_SYMBOL("GET-TABLE-FONT-SIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_table_font_size,
	    STATIC_FUNCTION(get_table_font_size,NIL,FALSE,1,1));
    add_virtual_attribute(Qtable_font_size,list_constant_5,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_table_font_size),
	    SYMBOL_FUNCTION(Qget_table_font_size),Nil);
    Qrepresented_item = STATIC_SYMBOL("REPRESENTED-ITEM",AB_package);
    temp = CONS(Qrepresented_item,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qrepresented_item,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_class,Qname_box);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_5,
	    list_constant_6);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_7 = STATIC_CONS(list_constant_2,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_7);
    Qinitial_represented_item = STATIC_SYMBOL("INITIAL-REPRESENTED-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_represented_item,
	    STATIC_FUNCTION(initial_represented_item,NIL,FALSE,1,1));
    Qget_represented_item = STATIC_SYMBOL("GET-REPRESENTED-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qget_represented_item,
	    STATIC_FUNCTION(get_represented_item,NIL,FALSE,1,1));
    add_virtual_attribute(Qrepresented_item,list_constant_8,
	    list_constant_9,Qnil,
	    SYMBOL_FUNCTION(Qinitial_represented_item),
	    SYMBOL_FUNCTION(Qget_represented_item),Nil);
    Qtable_layout = STATIC_SYMBOL("TABLE-LAYOUT",AB_package);
    temp = CONS(Qtable_layout,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtable_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtable_layout,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtable_item),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_10 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_10,list_constant_7);
    Qinitial_table_layout = STATIC_SYMBOL("INITIAL-TABLE-LAYOUT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_table_layout,
	    STATIC_FUNCTION(initial_table_layout,NIL,FALSE,1,1));
    Qget_table_layout = STATIC_SYMBOL("GET-TABLE-LAYOUT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_table_layout,STATIC_FUNCTION(get_table_layout,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qtable_layout,list_constant_5,list_constant_11,
	    Qnil,SYMBOL_FUNCTION(Qinitial_table_layout),
	    SYMBOL_FUNCTION(Qget_table_layout),Nil);
    Qtext_x_magnification = STATIC_SYMBOL("TEXT-X-MAGNIFICATION",AB_package);
    temp = CONS(Qtext_x_magnification,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtext_x_magnification,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,temp);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_box);
    Qinitial_text_x_magnification = 
	    STATIC_SYMBOL("INITIAL-TEXT-X-MAGNIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_text_x_magnification,
	    STATIC_FUNCTION(initial_text_x_magnification,NIL,FALSE,1,1));
    Qget_text_x_magnification = STATIC_SYMBOL("GET-TEXT-X-MAGNIFICATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_text_x_magnification,
	    STATIC_FUNCTION(get_text_x_magnification,NIL,FALSE,1,1));
    add_virtual_attribute(Qtext_x_magnification,list_constant_12,Qnumber,
	    Qnil,SYMBOL_FUNCTION(Qinitial_text_x_magnification),
	    SYMBOL_FUNCTION(Qget_text_x_magnification),Nil);
    Qtext_y_magnification = STATIC_SYMBOL("TEXT-Y-MAGNIFICATION",AB_package);
    temp = CONS(Qtext_y_magnification,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtext_y_magnification,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtext_box),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_text_y_magnification = 
	    STATIC_SYMBOL("INITIAL-TEXT-Y-MAGNIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_text_y_magnification,
	    STATIC_FUNCTION(initial_text_y_magnification,NIL,FALSE,1,1));
    Qget_text_y_magnification = STATIC_SYMBOL("GET-TEXT-Y-MAGNIFICATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_text_y_magnification,
	    STATIC_FUNCTION(get_text_y_magnification,NIL,FALSE,1,1));
    add_virtual_attribute(Qtext_y_magnification,list_constant_12,Qnumber,
	    Qnil,SYMBOL_FUNCTION(Qinitial_text_y_magnification),
	    SYMBOL_FUNCTION(Qget_text_y_magnification),Nil);
    Qformat_type = STATIC_SYMBOL("FORMAT-TYPE",AB_package);
    temp = CONS(Qformat_type,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qformat_type,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qformat_change_qm = STATIC_SYMBOL("FORMAT-CHANGE\?",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,
	    list_constant_3);
    Qinitial_format_type = STATIC_SYMBOL("INITIAL-FORMAT-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_format_type,
	    STATIC_FUNCTION(initial_format_type,NIL,FALSE,1,1));
    Qget_format_type = STATIC_SYMBOL("GET-FORMAT-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_format_type,STATIC_FUNCTION(get_format_type,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qformat_type,list_constant_13,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_format_type),
	    SYMBOL_FUNCTION(Qget_format_type),Nil);
    Qvalue_to_display = STATIC_SYMBOL("VALUE-TO-DISPLAY",AB_package);
    temp = CONS(Qvalue_to_display,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qvalue_to_display,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qab_class,Qmeter);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qab_class,Qdial);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_14,
	    list_constant_15);
    Qinitial_value_to_display = STATIC_SYMBOL("INITIAL-VALUE-TO-DISPLAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_value_to_display,
	    STATIC_FUNCTION(initial_value_to_display,NIL,FALSE,1,1));
    Qget_value_to_display = STATIC_SYMBOL("GET-VALUE-TO-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qget_value_to_display,
	    STATIC_FUNCTION(get_value_to_display,NIL,FALSE,1,1));
    add_virtual_attribute(Qvalue_to_display,list_constant_16,Qnumber,Qnil,
	    SYMBOL_FUNCTION(Qinitial_value_to_display),
	    SYMBOL_FUNCTION(Qget_value_to_display),Nil);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qbutton_status = STATIC_SYMBOL("BUTTON-STATUS",AB_package);
    temp = CONS(Qbutton_status,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qbutton_status,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qab_class,Qcheck_box);
    Qradio_button = STATIC_SYMBOL("RADIO-BUTTON",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qab_class,Qradio_button);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_17,
	    list_constant_18);
    Qon = STATIC_SYMBOL("ON",AB_package);
    Qoff = STATIC_SYMBOL("OFF",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qmember,Qon,Qoff);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_19);
    Qinitial_button_status = STATIC_SYMBOL("INITIAL-BUTTON-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_button_status,
	    STATIC_FUNCTION(initial_button_status,NIL,FALSE,1,1));
    Qget_button_status = STATIC_SYMBOL("GET-BUTTON-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_button_status,
	    STATIC_FUNCTION(get_button_status,NIL,FALSE,1,1));
    Qset_button_status = STATIC_SYMBOL("SET-BUTTON-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qset_button_status,
	    STATIC_FUNCTION(set_button_status,NIL,FALSE,2,2));
    add_virtual_attribute(Qbutton_status,list_constant_20,list_constant_21,
	    Qnil,SYMBOL_FUNCTION(Qinitial_button_status),
	    SYMBOL_FUNCTION(Qget_button_status),
	    SYMBOL_FUNCTION(Qset_button_status));
    Qvalue_request_pending = STATIC_SYMBOL("VALUE-REQUEST-PENDING",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qbutton_status,STATIC_FUNCTION(button_status,NIL,
	    FALSE,1,1));
    Qslider_value = STATIC_SYMBOL("SLIDER-VALUE",AB_package);
    temp = CONS(Qslider_value,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qslider = STATIC_SYMBOL("SLIDER",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qslider),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qslider_value,temp_1);
    set_property_value_function(get_symbol_properties_function(Qslider),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qab_class,Qslider);
    Qinitial_slider_value = STATIC_SYMBOL("INITIAL-SLIDER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_slider_value,
	    STATIC_FUNCTION(initial_slider_value,NIL,FALSE,1,1));
    Qget_slider_value = STATIC_SYMBOL("GET-SLIDER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_slider_value,STATIC_FUNCTION(get_slider_value,
	    NIL,FALSE,1,1));
    Qset_slider_value = STATIC_SYMBOL("SET-SLIDER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_slider_value,STATIC_FUNCTION(set_slider_value,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qslider_value,list_constant_22,Qnumber,Qnil,
	    SYMBOL_FUNCTION(Qinitial_slider_value),
	    SYMBOL_FUNCTION(Qget_slider_value),
	    SYMBOL_FUNCTION(Qset_slider_value));
    Qassociated_frame_for_button_qm = 
	    STATIC_SYMBOL("ASSOCIATED-FRAME-FOR-BUTTON\?",AB_package);
    Qassociated_slot_name_for_button_qm = 
	    STATIC_SYMBOL("ASSOCIATED-SLOT-NAME-FOR-BUTTON\?",AB_package);
    Qassociated_frame_serial_number_for_button_qm = 
	    STATIC_SYMBOL("ASSOCIATED-FRAME-SERIAL-NUMBER-FOR-BUTTON\?",
	    AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qtype_in_box_value = STATIC_SYMBOL("TYPE-IN-BOX-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qtype_in_box_value,
	    STATIC_FUNCTION(type_in_box_value,NIL,FALSE,1,1));
    temp = CONS(Qtype_in_box_value,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qtype_in_box = STATIC_SYMBOL("TYPE-IN-BOX",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtype_in_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtype_in_box_value,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtype_in_box),
	    Qvirtual_attributes_local_to_class,temp);
    Qtype_in_box_input_value = STATIC_SYMBOL("TYPE-IN-BOX-INPUT-VALUE",
	    AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qab_class,Qtype_in_box);
    list_constant_24 = STATIC_LIST((SI_Long)5L,Qab_or,Qsymbol,Qtext,
	    Qnumber,Qtruth_value);
    Qinitial_type_in_box_value = STATIC_SYMBOL("INITIAL-TYPE-IN-BOX-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_type_in_box_value,
	    STATIC_FUNCTION(initial_type_in_box_value,NIL,FALSE,1,1));
    Qget_type_in_box_value = STATIC_SYMBOL("GET-TYPE-IN-BOX-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_type_in_box_value,
	    STATIC_FUNCTION(get_type_in_box_value,NIL,FALSE,1,1));
    Qset_type_in_box_value = STATIC_SYMBOL("SET-TYPE-IN-BOX-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_type_in_box_value,
	    STATIC_FUNCTION(set_type_in_box_value,NIL,FALSE,2,2));
    add_virtual_attribute(Qtype_in_box_value,list_constant_23,
	    list_constant_24,Qnil,
	    SYMBOL_FUNCTION(Qinitial_type_in_box_value),
	    SYMBOL_FUNCTION(Qget_type_in_box_value),
	    SYMBOL_FUNCTION(Qset_type_in_box_value));
    if (Item_color_pattern_returns_overrides_only_p == UNBOUND)
	Item_color_pattern_returns_overrides_only_p = Nil;
    Qitem_color_pattern = STATIC_SYMBOL("ITEM-COLOR-PATTERN",AB_package);
    temp = CONS(Qitem_color_pattern,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp = CONS(Qitem_color_pattern,Virtual_attributes_not_local_to_a_class);
    Virtual_attributes_not_local_to_a_class = temp;
    Qmissing_color_region = STATIC_SYMBOL("MISSING-COLOR-REGION",AB_package);
    Qunnamed_color_region = STATIC_SYMBOL("UNNAMED-COLOR-REGION",AB_package);
    Qillegal_colors = STATIC_SYMBOL("ILLEGAL-COLORS",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qab_class,Qentity);
    list_constant_27 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_25,
	    list_constant_12,list_constant_26);
    Qinitial_item_color_pattern = 
	    STATIC_SYMBOL("INITIAL-ITEM-COLOR-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_color_pattern,
	    STATIC_FUNCTION(initial_item_color_pattern,NIL,FALSE,1,1));
    Qget_item_color_pattern = STATIC_SYMBOL("GET-ITEM-COLOR-PATTERN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_color_pattern,
	    STATIC_FUNCTION(get_item_color_pattern,NIL,FALSE,1,1));
    Qset_item_color_pattern = STATIC_SYMBOL("SET-ITEM-COLOR-PATTERN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_item_color_pattern,
	    STATIC_FUNCTION(set_item_color_pattern,NIL,FALSE,2,2));
    add_virtual_attribute(Qitem_color_pattern,list_constant_27,
	    list_constant_10,Qnil,
	    SYMBOL_FUNCTION(Qinitial_item_color_pattern),
	    SYMBOL_FUNCTION(Qget_item_color_pattern),
	    SYMBOL_FUNCTION(Qset_item_color_pattern));
    string_constant = 
	    STATIC_STRING("Cannot change the ~a region of ~NF.  The class definition for ~a ~\n     does not have a region named ~a.");
    string_constant_1 = 
	    STATIC_STRING("Cannot change an unnamed color region in ~NF using its color name ~\n       (~a).  Unnamed color regions cannot be changed.");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_28,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_28,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING(" are illegal colors");
    string_constant_3 = STATIC_STRING(" is an illegal color");
    Qlayer_position = STATIC_SYMBOL("LAYER-POSITION",AB_package);
    temp = CONS(Qlayer_position,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qlayer_position,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qab_class,Qblock);
    Qinitial_layer_position = STATIC_SYMBOL("INITIAL-LAYER-POSITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_layer_position,
	    STATIC_FUNCTION(initial_layer_position,NIL,FALSE,1,1));
    Qget_layer_position = STATIC_SYMBOL("GET-LAYER-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_layer_position,
	    STATIC_FUNCTION(get_layer_position,NIL,FALSE,1,1));
    add_virtual_attribute(Qlayer_position,list_constant_29,Qinteger,Qnil,
	    SYMBOL_FUNCTION(Qinitial_layer_position),
	    SYMBOL_FUNCTION(Qget_layer_position),Nil);
    Qname_box_item = STATIC_SYMBOL("NAME-BOX-ITEM",AB_package);
    temp = CONS(Qname_box_item,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qname_box_item,temp_1);
    set_property_value_function(get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_name_box_item = STATIC_SYMBOL("INITIAL-NAME-BOX-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_name_box_item,
	    STATIC_FUNCTION(initial_name_box_item,NIL,FALSE,1,1));
    Qget_name_box_item = STATIC_SYMBOL("GET-NAME-BOX-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qget_name_box_item,
	    STATIC_FUNCTION(get_name_box_item,NIL,FALSE,1,1));
    add_virtual_attribute(Qname_box_item,list_constant_26,list_constant_9,
	    Qnil,SYMBOL_FUNCTION(Qinitial_name_box_item),
	    SYMBOL_FUNCTION(Qget_name_box_item),Nil);
    Qattribute_display_items = STATIC_SYMBOL("ATTRIBUTE-DISPLAY-ITEMS",
	    AB_package);
    temp = CONS(Qattribute_display_items,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qattribute_display_items,temp_1);
    set_property_value_function(get_symbol_properties_function(Qentity),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_attribute_display_items = 
	    STATIC_SYMBOL("INITIAL-ATTRIBUTE-DISPLAY-ITEMS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_attribute_display_items,
	    STATIC_FUNCTION(initial_attribute_display_items,NIL,FALSE,1,1));
    Qget_attribute_display_items = 
	    STATIC_SYMBOL("GET-ATTRIBUTE-DISPLAY-ITEMS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_attribute_display_items,
	    STATIC_FUNCTION(get_attribute_display_items,NIL,FALSE,1,1));
    add_virtual_attribute(Qattribute_display_items,list_constant_26,
	    list_constant_4,Qnil,
	    SYMBOL_FUNCTION(Qinitial_attribute_display_items),
	    SYMBOL_FUNCTION(Qget_attribute_display_items),Nil);
    Qrepresentation_type = STATIC_SYMBOL("REPRESENTATION-TYPE",AB_package);
    temp = CONS(Qrepresentation_type,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qrepresentation_type,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    Qinitial_representation_type = 
	    STATIC_SYMBOL("INITIAL-REPRESENTATION-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_representation_type,
	    STATIC_FUNCTION(initial_representation_type,NIL,FALSE,1,1));
    Qget_representation_type = STATIC_SYMBOL("GET-REPRESENTATION-TYPE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_representation_type,
	    STATIC_FUNCTION(get_representation_type,NIL,FALSE,1,1));
    add_virtual_attribute(Qrepresentation_type,list_constant_30,Qsymbol,
	    Qnil,SYMBOL_FUNCTION(Qinitial_representation_type),
	    SYMBOL_FUNCTION(Qget_representation_type),Nil);
    Qconnection_is_directed = STATIC_SYMBOL("CONNECTION-IS-DIRECTED",
	    AB_package);
    temp = CONS(Qconnection_is_directed,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_is_directed,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_connection_is_directed = 
	    STATIC_SYMBOL("INITIAL-CONNECTION-IS-DIRECTED",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_is_directed,
	    STATIC_FUNCTION(initial_connection_is_directed,NIL,FALSE,1,1));
    Qget_connection_is_directed = 
	    STATIC_SYMBOL("GET-CONNECTION-IS-DIRECTED",AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_is_directed,
	    STATIC_FUNCTION(get_connection_is_directed,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_is_directed,list_constant_25,
	    Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_is_directed),
	    SYMBOL_FUNCTION(Qget_connection_is_directed),Nil);
    Qconnection_position_sequence = 
	    STATIC_SYMBOL("CONNECTION-POSITION-SEQUENCE",AB_package);
    temp = CONS(Qconnection_position_sequence,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qconnection_position_sequence,temp_1);
    set_property_value_function(get_symbol_properties_function(Qconnection),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_connection_position_sequence = 
	    STATIC_SYMBOL("INITIAL-CONNECTION-POSITION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_connection_position_sequence,
	    STATIC_FUNCTION(initial_connection_position_sequence,NIL,FALSE,
	    1,1));
    Qget_connection_position_sequence = 
	    STATIC_SYMBOL("GET-CONNECTION-POSITION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_connection_position_sequence,
	    STATIC_FUNCTION(get_connection_position_sequence,NIL,FALSE,1,1));
    add_virtual_attribute(Qconnection_position_sequence,list_constant_25,
	    list_constant_1,Qnil,
	    SYMBOL_FUNCTION(Qinitial_connection_position_sequence),
	    SYMBOL_FUNCTION(Qget_connection_position_sequence),Nil);
    temp = CONS(Qtext,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qname_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtext,temp_1);
    set_property_value_function(get_symbol_properties_function(Qname_box),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_text = STATIC_SYMBOL("INITIAL-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_text,STATIC_FUNCTION(initial_text,NIL,
	    FALSE,1,1));
    Qget_text = STATIC_SYMBOL("GET-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_text,STATIC_FUNCTION(get_text,NIL,FALSE,1,1));
    add_virtual_attribute(Qtext,list_constant_6,Qtext,Qnil,
	    SYMBOL_FUNCTION(Qinitial_text),SYMBOL_FUNCTION(Qget_text),Nil);
    Qtype_in_box_variable_or_parameter = 
	    STATIC_SYMBOL("TYPE-IN-BOX-VARIABLE-OR-PARAMETER",AB_package);
    temp = CONS(Qtype_in_box_variable_or_parameter,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qtype_in_box),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtype_in_box_variable_or_parameter,temp_1);
    set_property_value_function(get_symbol_properties_function(Qtype_in_box),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_type_in_box_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-TYPE-IN-BOX-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_type_in_box_variable_or_parameter,
	    STATIC_FUNCTION(initial_type_in_box_variable_or_parameter,NIL,
	    FALSE,1,1));
    Qget_type_in_box_variable_or_parameter = 
	    STATIC_SYMBOL("GET-TYPE-IN-BOX-VARIABLE-OR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qget_type_in_box_variable_or_parameter,
	    STATIC_FUNCTION(get_type_in_box_variable_or_parameter,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qtype_in_box_variable_or_parameter,
	    list_constant_23,list_constant_9,Qnil,
	    SYMBOL_FUNCTION(Qinitial_type_in_box_variable_or_parameter),
	    SYMBOL_FUNCTION(Qget_type_in_box_variable_or_parameter),Nil);
    Qstrip_text_mark = STATIC_SYMBOL("STRIP-TEXT-MARK",AB_package);
    temp = CONS(Qstrip_text_mark,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qstrip_text_mark,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    Kevent_updates = STATIC_SYMBOL("EVENT-UPDATES",Pkeyword);
    Kwithin_putter = STATIC_SYMBOL("WITHIN-PUTTER",Pkeyword);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Kevent_updates,Kwithin_putter);
    Qinitial_strip_text_mark = STATIC_SYMBOL("INITIAL-STRIP-TEXT-MARK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_strip_text_mark,
	    STATIC_FUNCTION(initial_strip_text_mark,NIL,FALSE,1,1));
    Qget_strip_text_mark = STATIC_SYMBOL("GET-STRIP-TEXT-MARK",AB_package);
    SET_SYMBOL_FUNCTION(Qget_strip_text_mark,
	    STATIC_FUNCTION(get_strip_text_mark,NIL,FALSE,1,1));
    Qset_strip_text_mark = STATIC_SYMBOL("SET-STRIP-TEXT-MARK",AB_package);
    SET_SYMBOL_FUNCTION(Qset_strip_text_mark,
	    STATIC_FUNCTION(set_strip_text_mark,NIL,FALSE,2,2));
    add_virtual_attribute(Qstrip_text_mark,list_constant_30,Qtruth_value,
	    list_constant_31,SYMBOL_FUNCTION(Qinitial_strip_text_mark),
	    SYMBOL_FUNCTION(Qget_strip_text_mark),
	    SYMBOL_FUNCTION(Qset_strip_text_mark));
    Qdo_not_strip_text_mark = STATIC_SYMBOL("DO-NOT-STRIP-TEXT-MARK",
	    AB_package);
    temp = CONS(Qdo_not_strip_text_mark,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qdo_not_strip_text_mark,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_do_not_strip_text_mark = 
	    STATIC_SYMBOL("INITIAL-DO-NOT-STRIP-TEXT-MARK",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_do_not_strip_text_mark,
	    STATIC_FUNCTION(initial_do_not_strip_text_mark,NIL,FALSE,1,1));
    Qget_do_not_strip_text_mark = 
	    STATIC_SYMBOL("GET-DO-NOT-STRIP-TEXT-MARK",AB_package);
    SET_SYMBOL_FUNCTION(Qget_do_not_strip_text_mark,
	    STATIC_FUNCTION(get_do_not_strip_text_mark,NIL,FALSE,1,1));
    Qset_do_not_strip_text_mark = 
	    STATIC_SYMBOL("SET-DO-NOT-STRIP-TEXT-MARK",AB_package);
    SET_SYMBOL_FUNCTION(Qset_do_not_strip_text_mark,
	    STATIC_FUNCTION(set_do_not_strip_text_mark,NIL,FALSE,2,2));
    add_virtual_attribute(Qdo_not_strip_text_mark,list_constant_30,
	    Qtruth_value,list_constant_31,
	    SYMBOL_FUNCTION(Qinitial_do_not_strip_text_mark),
	    SYMBOL_FUNCTION(Qget_do_not_strip_text_mark),
	    SYMBOL_FUNCTION(Qset_do_not_strip_text_mark));
    Qget_workspace_representation_type = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE",AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    list_constant_32 = STATIC_CONS(Qframe,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qget_workspace_representation_type,
	    list_constant_32,Qgeneric_method_lambda_list);
    Qget_workspace_representation_type_for_system_item = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-SYSTEM-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_system_item,
	    STATIC_FUNCTION(get_workspace_representation_type_for_system_item,
	    NIL,FALSE,1,1));
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_system_item);
    set_get(Qsystem_item,Qget_workspace_representation_type,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qsystem_item,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qicon_with_connections = STATIC_SYMBOL("ICON-WITH-CONNECTIONS",AB_package);
    Qicon_without_connections = STATIC_SYMBOL("ICON-WITHOUT-CONNECTIONS",
	    AB_package);
    Qget_workspace_representation_type_for_entity = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-ENTITY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_entity,
	    STATIC_FUNCTION(get_workspace_representation_type_for_entity,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_entity);
    set_get(Qentity,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qentity,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qget_workspace_representation_type_for_loose_end = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-LOOSE-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_loose_end,
	    STATIC_FUNCTION(get_workspace_representation_type_for_loose_end,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_loose_end);
    set_get(Qloose_end,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qloose_end,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_connection = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_connection,
	    STATIC_FUNCTION(get_workspace_representation_type_for_connection,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_connection);
    set_get(Qconnection,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qconnection,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_text_box = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TEXT-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_text_box,
	    STATIC_FUNCTION(get_workspace_representation_type_for_text_box,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_text_box);
    set_get(Qtext_box,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qtext_box,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qattribute_display = STATIC_SYMBOL("ATTRIBUTE-DISPLAY",AB_package);
    Qshort_representation = STATIC_SYMBOL("SHORT-REPRESENTATION",AB_package);
    Qclassic_attribute_table = STATIC_SYMBOL("CLASSIC-ATTRIBUTE-TABLE",
	    AB_package);
    Qattribute_table_with_header = 
	    STATIC_SYMBOL("ATTRIBUTE-TABLE-WITH-HEADER",AB_package);
    Qattribute_table = STATIC_SYMBOL("ATTRIBUTE-TABLE",AB_package);
    Qget_workspace_representation_type_for_table = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_table,
	    STATIC_FUNCTION(get_workspace_representation_type_for_table,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_table);
    set_get(Qtable,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qtable,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_readout_table = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_readout_table,
	    STATIC_FUNCTION(get_workspace_representation_type_for_readout_table,
	    NIL,FALSE,1,1));
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    temp = 
	    SYMBOL_FUNCTION(Qget_workspace_representation_type_for_readout_table);
    set_get(Qreadout_table,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qreadout_table,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_dial = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_dial,
	    STATIC_FUNCTION(get_workspace_representation_type_for_dial,NIL,
	    FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_dial);
    set_get(Qdial,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qdial,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_meter = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_meter,
	    STATIC_FUNCTION(get_workspace_representation_type_for_meter,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_meter);
    set_get(Qmeter,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qmeter,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qget_workspace_representation_type_for_trend_chart = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TREND-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_trend_chart,
	    STATIC_FUNCTION(get_workspace_representation_type_for_trend_chart,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_trend_chart);
    set_get(Qtrend_chart,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qtrend_chart,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qget_workspace_representation_type_for_graph = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_graph,
	    STATIC_FUNCTION(get_workspace_representation_type_for_graph,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_graph);
    set_get(Qgraph,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qget_workspace_representation_type_for_chart = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_chart,
	    STATIC_FUNCTION(get_workspace_representation_type_for_chart,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_chart);
    set_get(Qchart,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qget_workspace_representation_type_for_freeform_table = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-FREEFORM-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_freeform_table,
	    STATIC_FUNCTION(get_workspace_representation_type_for_freeform_table,
	    NIL,FALSE,1,1));
    temp = 
	    SYMBOL_FUNCTION(Qget_workspace_representation_type_for_freeform_table);
    set_get(Qfreeform_table,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qfreeform_table,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qget_workspace_representation_type_for_action_button = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-ACTION-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_action_button,
	    STATIC_FUNCTION(get_workspace_representation_type_for_action_button,
	    NIL,FALSE,1,1));
    temp = 
	    SYMBOL_FUNCTION(Qget_workspace_representation_type_for_action_button);
    set_get(Qaction_button,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qaction_button,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_radio_button = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-RADIO-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_radio_button,
	    STATIC_FUNCTION(get_workspace_representation_type_for_radio_button,
	    NIL,FALSE,1,1));
    temp = 
	    SYMBOL_FUNCTION(Qget_workspace_representation_type_for_radio_button);
    set_get(Qradio_button,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qradio_button,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_check_box = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-CHECK-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_check_box,
	    STATIC_FUNCTION(get_workspace_representation_type_for_check_box,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_check_box);
    set_get(Qcheck_box,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qcheck_box,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_slider = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-SLIDER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_slider,
	    STATIC_FUNCTION(get_workspace_representation_type_for_slider,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_slider);
    set_get(Qslider,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qslider,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qget_workspace_representation_type_for_type_in_box = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-TYPE-IN-BOX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_type_in_box,
	    STATIC_FUNCTION(get_workspace_representation_type_for_type_in_box,
	    NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qget_workspace_representation_type_for_type_in_box);
    set_get(Qtype_in_box,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qtype_in_box,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qget_workspace_representation_type_for_kb_workspace = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE-FOR-KB-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_workspace_representation_type_for_kb_workspace,
	    STATIC_FUNCTION(get_workspace_representation_type_for_kb_workspace,
	    NIL,FALSE,1,1));
    temp = 
	    SYMBOL_FUNCTION(Qget_workspace_representation_type_for_kb_workspace);
    set_get(Qkb_workspace,Qget_workspace_representation_type,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qget_workspace_representation_type),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qget_workspace_representation_type,temp,
	    Qclasses_which_define);
    Qws_representation_type = STATIC_SYMBOL("WS-REPRESENTATION-TYPE",
	    AB_package);
    Qxpos = STATIC_SYMBOL("XPOS",AB_package);
    Qypos = STATIC_SYMBOL("YPOS",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qicon_color_pattern = STATIC_SYMBOL("ICON-COLOR-PATTERN",AB_package);
    Qorientation = STATIC_SYMBOL("ORIENTATION",AB_package);
    Qvariable_overrides = STATIC_SYMBOL("VARIABLE-OVERRIDES",AB_package);
    Qregion_overrides = STATIC_SYMBOL("REGION-OVERRIDES",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    list_constant_33 = STATIC_CONS(Qgsi_interface,Qnil);
    check_if_superior_classes_are_defined(Qui_client_interface,
	    list_constant_33);
    string_constant_38 = STATIC_STRING("1m1l83Iy1l8t");
    string_constant_39 = 
	    STATIC_STRING("1z4z8r8347y8347y83cxy83cxy01l1n83Ry1l83-Gy1l83=hy001o1l8l1l8z1m8p832uy1l83Cy000004z8r8354y8354y83cxy83cxy01l1m83Ry1l836fy001p1l8");
    string_constant_40 = 
	    STATIC_STRING("l1l8z1m8p832uy1l83Cy1l83Ny000004z8r833ty833ty83cxy83cxy08k001p1l8l1l8z1l83Ny1m8p83Ky1l83Cy000004z8r83d7y83d7y83cxy83cxy0833ey001");
    string_constant_41 = 
	    STATIC_STRING("m1l8o1l8l000004z8r83d-y83d-y83cxy83cxy00001m1l8o1l8l000004z8r83d+y83d+y83cxy83cxy00001m1l8o1l8l000004z8r83d2y83d2y83cxy83cxy0000");
    string_constant_42 = 
	    STATIC_STRING("1m1l8o1l8l000004z8r83d1y83d1y83cxy83cxy00001m1l8o1l8l000004z8r83d3y83d3y83cxy83cxy00001m1l8o1l8l000004z8r83d6y83d6y83cxy83cxy000");
    string_constant_43 = 
	    STATIC_STRING("01m1l8o1l8l000004z8r83d5y83d5y83cxy83cxy00001m1l8o1l8l000004z8r83d4y83d4y83cxy83cxy00001m1l8o1l8l000004z8r83d=y83d=y83cxy83cxy00");
    string_constant_44 = 
	    STATIC_STRING("001m1l8o1l8l000004z8r83d*y83d*y83cxy83cxy00001m1l8o1l8l000004z8r83d0y83d0y83cxy83cxy00001m1l8o1l8l00000");
    string_constant_45 = 
	    STATIC_STRING("13Dy8q1o83cxy1l83=8y83Iy8t1q8347y1l1n83Ry1l83-Gy1l83=hy1l8l8z1m8p832uy1l83Cy1q8354y1l1m83Ry1l836fy1l8l8z1m8p832uy1l83Cy1r833ty8k");
    string_constant_46 = 
	    STATIC_STRING("1l8l8z83Ny1m8p83Ky1l83Cy1o83d7y833ey8o8l1o83d-y08o8l1o83d+y08o8l1o83d2y08o8l1o83d1y08o8l1o83d3y08o8l1o83d6y08o8l1o83d5y08o8l1o83");
    string_constant_47 = 
	    STATIC_STRING("d4y08o8l1o83d=y08o8l1o83d*y08o8l1o83d0y08o8l");
    temp_1 = regenerate_optimized_constant(string_constant_38);
    temp_2 = regenerate_optimized_constant(list(6,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44));
    add_class_to_environment(9,Qui_client_interface,list_constant_33,Nil,
	    temp_1,Nil,temp_2,list_constant_33,
	    regenerate_optimized_constant(LIST_3(string_constant_45,
	    string_constant_46,string_constant_47)),Nil);
    Qcallback_representation = STATIC_SYMBOL("CALLBACK-REPRESENTATION",
	    AB_package);
    Qui_client_interface_sessions = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-SESSIONS",AB_package);
    Qreclaim_ui_client_interface_sessions_value = 
	    STATIC_SYMBOL("RECLAIM-UI-CLIENT-INTERFACE-SESSIONS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_ui_client_interface_sessions_value,
	    STATIC_FUNCTION(reclaim_ui_client_interface_sessions_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qui_client_interface_sessions,
	    SYMBOL_FUNCTION(Qreclaim_ui_client_interface_sessions_value),
	    Qslot_value_reclaimer);
    Qui_client_session_workspaces = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-WORKSPACES",AB_package);
    Qreclaim_ui_client_session_workspaces_value = 
	    STATIC_SYMBOL("RECLAIM-UI-CLIENT-SESSION-WORKSPACES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_ui_client_session_workspaces_value,
	    STATIC_FUNCTION(reclaim_ui_client_session_workspaces_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qui_client_session_workspaces,
	    SYMBOL_FUNCTION(Qreclaim_ui_client_session_workspaces_value),
	    Qslot_value_reclaimer);
    Qui_client_session_parent_interface = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-PARENT-INTERFACE",AB_package);
    Qreclaim_ui_client_session_parent_interface_value = 
	    STATIC_SYMBOL("RECLAIM-UI-CLIENT-SESSION-PARENT-INTERFACE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_ui_client_session_parent_interface_value,
	    STATIC_FUNCTION(reclaim_ui_client_session_parent_interface_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qui_client_session_parent_interface,
	    SYMBOL_FUNCTION(Qreclaim_ui_client_session_parent_interface_value),
	    Qslot_value_reclaimer);
    string_constant_4 = STATIC_STRING("");
    Qui_client_session_user_mode = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-MODE",AB_package);
    Qui_client_session_user_name = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-NAME",AB_package);
    Qui_client_session_encoded_password = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-ENCODED-PASSWORD",AB_package);
    Qspecific_language_for_this_ui_client_session_qm = 
	    STATIC_SYMBOL("SPECIFIC-LANGUAGE-FOR-THIS-UI-CLIENT-SESSION\?",
	    AB_package);
    Qui_client_session_time_of_last_connection = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-TIME-OF-LAST-CONNECTION",
	    AB_package);
    Qui_client_session_network_host_name_qm = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-NETWORK-HOST-NAME\?",AB_package);
    Qui_client_session_os_type_qm = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-OS-TYPE\?",AB_package);
    Qui_client_session_license_level_qm = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-LICENSE-LEVEL\?",AB_package);
    Qui_client_session_user_is_valid = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-IS-VALID",AB_package);
    Qui_client_session_mode_is_valid = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-MODE-IS-VALID",AB_package);
    Qui_client_session_status = STATIC_SYMBOL("UI-CLIENT-SESSION-STATUS",
	    AB_package);
    Qui_client_session_nonce = STATIC_SYMBOL("UI-CLIENT-SESSION-NONCE",
	    AB_package);
    Qui_client_session_os_user_name_qm = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-OS-USER-NAME\?",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)14L,Qname_or_names_for_frame,
	    Qui_client_session_user_mode,Qui_client_session_user_name,
	    Qui_client_session_encoded_password,
	    Qspecific_language_for_this_ui_client_session_qm,
	    Qui_client_session_time_of_last_connection,
	    Qui_client_session_network_host_name_qm,
	    Qui_client_session_os_type_qm,
	    Qui_client_session_license_level_qm,
	    Qui_client_session_user_is_valid,
	    Qui_client_session_mode_is_valid,Qui_client_session_status,
	    Qui_client_session_nonce,Qui_client_session_os_user_name_qm);
    Ui_client_session_slots_to_save_for_clear_kb = list_constant_34;
    Qitem_representation_denotation = 
	    STATIC_SYMBOL("ITEM-REPRESENTATION-DENOTATION",AB_package);
    Qitem_representation_user_data_value = 
	    STATIC_SYMBOL("ITEM-REPRESENTATION-USER-DATA-VALUE",AB_package);
    Qrepresentation_address = STATIC_SYMBOL("REPRESENTATION-ADDRESS",
	    AB_package);
    Qcallback_representation_callback_procedure = 
	    STATIC_SYMBOL("CALLBACK-REPRESENTATION-CALLBACK-PROCEDURE",
	    AB_package);
    Qcallback_representation_callback_serial_number = 
	    STATIC_SYMBOL("CALLBACK-REPRESENTATION-CALLBACK-SERIAL-NUMBER",
	    AB_package);
    Qcallback_representation_callback_subscription_handle = 
	    STATIC_SYMBOL("CALLBACK-REPRESENTATION-CALLBACK-SUBSCRIPTION-HANDLE",
	    AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)6L,
	    Qitem_representation_denotation,
	    Qitem_representation_user_data_value,Qrepresentation_address,
	    Qcallback_representation_callback_procedure,
	    Qcallback_representation_callback_serial_number,
	    Qcallback_representation_callback_subscription_handle);
    Item_representation_slots_to_save_for_clear_kb = list_constant_35;
    list_constant_36 = 
	    STATIC_CONS(Qcallback_representation_callback_subscription_handle,
	    Qnil);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)5L,
	    Qrepresentation_address,
	    Qcallback_representation_callback_procedure,
	    Qcallback_representation_callback_serial_number,
	    Qcallback_representation_callback_subscription_handle,
	    list_constant_36);
    Callback_representation_slots_to_save_for_clear_kb = list_constant_37;
    Qshowing_representation_user_data_value = 
	    STATIC_SYMBOL("SHOWING-REPRESENTATION-USER-DATA-VALUE",AB_package);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)4L,
	    Qrepresentation_address,
	    Qcallback_representation_callback_procedure,
	    Qcallback_representation_callback_serial_number,list_constant_36);
    list_constant_39 = STATIC_CONS(Qshowing_representation_user_data_value,
	    list_constant_38);
    Showing_representation_slots_to_save_for_clear_kb = list_constant_39;
    Qitem_representation = STATIC_SYMBOL("ITEM-REPRESENTATION",AB_package);
    Qshowing_representation = STATIC_SYMBOL("SHOWING-REPRESENTATION",
	    AB_package);
    Qui_client_specific_language = 
	    STATIC_SYMBOL("UI-CLIENT-SPECIFIC-LANGUAGE",AB_package);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    alias_slot_name(3,Qspecific_language_for_this_ui_client_session_qm,
	    Qui_client_specific_language,Qui_client_session);
    Qui_client_session_network_host_name = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-NETWORK-HOST-NAME",AB_package);
    alias_slot_name(3,Qui_client_session_network_host_name_qm,
	    Qui_client_session_network_host_name,Qui_client_session);
    Qui_client_session_operating_system_type = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-OPERATING-SYSTEM-TYPE",
	    AB_package);
    alias_slot_name(3,Qui_client_session_os_type_qm,
	    Qui_client_session_operating_system_type,Qui_client_session);
    Qui_client_session_user_name_in_operating_system = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-NAME-IN-OPERATING-SYSTEM",
	    AB_package);
    alias_slot_name(3,Qui_client_session_os_user_name_qm,
	    Qui_client_session_user_name_in_operating_system,
	    Qui_client_session);
    Qui_client_connection_status = 
	    STATIC_SYMBOL("UI-CLIENT-CONNECTION-STATUS",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qg2_allocate_session_id = STATIC_SYMBOL("G2-ALLOCATE-SESSION-ID",
	    AB_package);
    Qg2_allocate_session_id_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ALLOCATE-SESSION-ID-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_40 = STATIC_CONS(Qtext,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_allocate_session_id,
	    make_system_rpc_1(Qg2_allocate_session_id_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_allocate_session_id,System_defined_rpcs);
    System_defined_rpcs = temp;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    string_constant_5 = 
	    STATIC_STRING("Call to ~A not available to interface ~NF");
    SET_SYMBOL_FUNCTION(Qg2_allocate_session_id_system_rpc_internal,
	    STATIC_FUNCTION(g2_allocate_session_id_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_validate_named_tw2 = STATIC_SYMBOL("G2-VALIDATE-NAMED-TW2",AB_package);
    Qg2_validate_named_tw2_system_rpc_internal = 
	    STATIC_SYMBOL("G2-VALIDATE-NAMED-TW2-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qnonce = STATIC_SYMBOL("NONCE",AB_package);
    list_constant_41 = STATIC_CONS(Ktype,list_constant_40);
    list_constant_46 = STATIC_CONS(Qnonce,list_constant_41);
    Qmachine_id = STATIC_SYMBOL("MACHINE-ID",AB_package);
    list_constant_47 = STATIC_CONS(Qmachine_id,list_constant_41);
    Qcode1 = STATIC_SYMBOL("CODE1",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Ktype,Qinteger);
    list_constant_48 = STATIC_CONS(Qcode1,list_constant_42);
    Qcode2 = STATIC_SYMBOL("CODE2",AB_package);
    list_constant_49 = STATIC_CONS(Qcode2,list_constant_42);
    Qcode3 = STATIC_SYMBOL("CODE3",AB_package);
    list_constant_50 = STATIC_CONS(Qcode3,list_constant_42);
    Qcode4 = STATIC_SYMBOL("CODE4",AB_package);
    list_constant_51 = STATIC_CONS(Qcode4,list_constant_42);
    Qcode5 = STATIC_SYMBOL("CODE5",AB_package);
    list_constant_52 = STATIC_CONS(Qcode5,list_constant_42);
    Qstart_date = STATIC_SYMBOL("START-DATE",AB_package);
    list_constant_43 = STATIC_CONS(Qdatum,Qnil);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_43);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_44);
    list_constant_53 = STATIC_CONS(Qstart_date,list_constant_45);
    Qend_date = STATIC_SYMBOL("END-DATE",AB_package);
    list_constant_54 = STATIC_CONS(Qend_date,list_constant_45);
    Qdesired_license_level = STATIC_SYMBOL("DESIRED-LICENSE-LEVEL",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qdesired_license_level,
	    Ktype,Qsymbol);
    list_constant_56 = STATIC_LIST((SI_Long)10L,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49,
	    list_constant_50,list_constant_51,list_constant_52,
	    list_constant_53,list_constant_54,list_constant_55);
    mutate_global_property(Qg2_validate_named_tw2,
	    make_system_rpc_1(Qg2_validate_named_tw2_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_56,
	    Nil,T),list_constant_43),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_validate_named_tw2,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_validate_named_tw2_system_rpc_internal,
	    STATIC_FUNCTION(g2_validate_named_tw2_system_rpc_internal,NIL,
	    FALSE,11,11));
    Qg2_make_ui_client_session = STATIC_SYMBOL("G2-MAKE-UI-CLIENT-SESSION",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_ui_client_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_make_ui_client_session,
	    STATIC_FUNCTION(g2_make_ui_client_session,NIL,FALSE,11,11));
    Qg2_make_ui_client_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-UI-CLIENT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    list_constant_57 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_57);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_58);
    list_constant_63 = STATIC_CONS(Quser_mode,list_constant_59);
    Quser_name = STATIC_SYMBOL("USER-NAME",AB_package);
    list_constant_64 = STATIC_CONS(Quser_name,list_constant_59);
    Qencoded_password = STATIC_SYMBOL("ENCODED-PASSWORD",AB_package);
    list_constant_60 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_40);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_60);
    list_constant_65 = STATIC_CONS(Qencoded_password,list_constant_61);
    Quser_name_in_os_qm = STATIC_SYMBOL("USER-NAME-IN-OS\?",AB_package);
    list_constant_66 = STATIC_CONS(Quser_name_in_os_qm,list_constant_61);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    list_constant_62 = STATIC_CONS(Ktype,list_constant_57);
    list_constant_67 = STATIC_CONS(Qlanguage,list_constant_62);
    Qhost_name = STATIC_SYMBOL("HOST-NAME",AB_package);
    list_constant_68 = STATIC_CONS(Qhost_name,list_constant_41);
    Qos_type = STATIC_SYMBOL("OS-TYPE",AB_package);
    list_constant_69 = STATIC_CONS(Qos_type,list_constant_62);
    Qworkspace_showing_callback_qm = 
	    STATIC_SYMBOL("WORKSPACE-SHOWING-CALLBACK\?",AB_package);
    list_constant_70 = STATIC_CONS(Qworkspace_showing_callback_qm,
	    list_constant_59);
    list_constant_71 = STATIC_LIST((SI_Long)9L,list_constant_46,
	    list_constant_63,list_constant_64,list_constant_65,
	    list_constant_66,list_constant_67,list_constant_68,
	    list_constant_69,list_constant_70);
    mutate_global_property(Qg2_make_ui_client_session,
	    make_system_rpc_1(Qg2_make_ui_client_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_71,
	    Nil,T),list_constant_43),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_ui_client_session,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qsession_item = STATIC_SYMBOL("SESSION-ITEM",AB_package);
    Qerror_symbol = STATIC_SYMBOL("ERROR-SYMBOL",AB_package);
    Qworkspace_showing_handle = STATIC_SYMBOL("WORKSPACE-SHOWING-HANDLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_make_ui_client_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_ui_client_session_system_rpc_internal,
	    NIL,FALSE,10,10));
    Qno_available_floating_licenses = 
	    STATIC_SYMBOL("NO-AVAILABLE-FLOATING-LICENSES",AB_package);
    Qtoo_many_login_attempts = STATIC_SYMBOL("TOO-MANY-LOGIN-ATTEMPTS",
	    AB_package);
    Qg2_release_ui_client_session = 
	    STATIC_SYMBOL("G2-RELEASE-UI-CLIENT-SESSION",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_release_ui_client_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_release_ui_client_session,
	    STATIC_FUNCTION(g2_release_ui_client_session,NIL,FALSE,1,1));
    Qg2_release_ui_client_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-RELEASE-UI-CLIENT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclient_session = STATIC_SYMBOL("CLIENT-SESSION",AB_package);
    list_constant_72 = STATIC_LIST((SI_Long)2L,Qab_class,Qui_client_session);
    list_constant_73 = STATIC_LIST((SI_Long)3L,Qclient_session,Ktype,
	    list_constant_72);
    list_constant_74 = STATIC_CONS(list_constant_73,Qnil);
    mutate_global_property(Qg2_release_ui_client_session,
	    make_system_rpc_1(Qg2_release_ui_client_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_74,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_release_ui_client_session,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_release_ui_client_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_release_ui_client_session_system_rpc_internal,
	    NIL,FALSE,2,2));
    string_constant_6 = STATIC_STRING("session and interface do not match");
    string_constant_7 = STATIC_STRING("session not logged in");
    Qinvalid_interface_class_for_rpc_call = 
	    STATIC_SYMBOL("INVALID-INTERFACE-CLASS-FOR-RPC-CALL",AB_package);
    string_constant_8 = 
	    STATIC_STRING("rpc call ~A not available to interface ~NF");
    Qsession_interface_mismatch = 
	    STATIC_SYMBOL("SESSION-INTERFACE-MISMATCH",AB_package);
    string_constant_9 = STATIC_STRING("~S");
    Qsession_not_logged_in = STATIC_SYMBOL("SESSION-NOT-LOGGED-IN",AB_package);
    Qdisassociate_workspace_from_ui_session = 
	    STATIC_SYMBOL("DISASSOCIATE-WORKSPACE-FROM-UI-SESSION",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qdisassociate_workspace_from_ui_session,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdisassociate_workspace_from_ui_session,
	    STATIC_FUNCTION(disassociate_workspace_from_ui_session,NIL,
	    FALSE,2,2));
    Qui_client_user_mode = STATIC_SYMBOL("UI-CLIENT-USER-MODE",AB_package);
    temp = CONS(Qui_client_user_mode,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_user_mode,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qab_class,Qui_client_item);
    Qinitial_ui_client_user_mode = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_user_mode,
	    STATIC_FUNCTION(initial_ui_client_user_mode,NIL,FALSE,1,1));
    Qget_ui_client_user_mode = STATIC_SYMBOL("GET-UI-CLIENT-USER-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_user_mode,
	    STATIC_FUNCTION(get_ui_client_user_mode,NIL,FALSE,1,1));
    Qset_ui_client_user_mode = STATIC_SYMBOL("SET-UI-CLIENT-USER-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_ui_client_user_mode,
	    STATIC_FUNCTION(set_ui_client_user_mode,NIL,FALSE,2,2));
    add_virtual_attribute(Qui_client_user_mode,list_constant_75,
	    list_constant_58,list_constant_31,
	    SYMBOL_FUNCTION(Qinitial_ui_client_user_mode),
	    SYMBOL_FUNCTION(Qget_ui_client_user_mode),
	    SYMBOL_FUNCTION(Qset_ui_client_user_mode));
    Qui_client_user_name = STATIC_SYMBOL("UI-CLIENT-USER-NAME",AB_package);
    temp = CONS(Qui_client_user_name,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_user_name,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_user_name = STATIC_SYMBOL("G2-USER-NAME",AB_package);
    Qinitial_ui_client_user_name = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-USER-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_user_name,
	    STATIC_FUNCTION(initial_ui_client_user_name,NIL,FALSE,1,1));
    Qget_ui_client_user_name = STATIC_SYMBOL("GET-UI-CLIENT-USER-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_user_name,
	    STATIC_FUNCTION(get_ui_client_user_name,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_user_name,list_constant_75,
	    list_constant_58,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_user_name),
	    SYMBOL_FUNCTION(Qget_ui_client_user_name),Nil);
    Qui_client_remote_host_name = 
	    STATIC_SYMBOL("UI-CLIENT-REMOTE-HOST-NAME",AB_package);
    temp = CONS(Qui_client_remote_host_name,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_remote_host_name,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_window_network_host_name_qm = 
	    STATIC_SYMBOL("G2-WINDOW-NETWORK-HOST-NAME\?",AB_package);
    Qinitial_ui_client_remote_host_name = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-REMOTE-HOST-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_remote_host_name,
	    STATIC_FUNCTION(initial_ui_client_remote_host_name,NIL,FALSE,1,1));
    Qget_ui_client_remote_host_name = 
	    STATIC_SYMBOL("GET-UI-CLIENT-REMOTE-HOST-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_remote_host_name,
	    STATIC_FUNCTION(get_ui_client_remote_host_name,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_remote_host_name,list_constant_75,
	    list_constant_60,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_remote_host_name),
	    SYMBOL_FUNCTION(Qget_ui_client_remote_host_name),Nil);
    Qui_client_operating_system_type = 
	    STATIC_SYMBOL("UI-CLIENT-OPERATING-SYSTEM-TYPE",AB_package);
    temp = CONS(Qui_client_operating_system_type,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_operating_system_type,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_window_os_type_qm = STATIC_SYMBOL("G2-WINDOW-OS-TYPE\?",AB_package);
    Qinitial_ui_client_operating_system_type = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-OPERATING-SYSTEM-TYPE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_operating_system_type,
	    STATIC_FUNCTION(initial_ui_client_operating_system_type,NIL,
	    FALSE,1,1));
    Qget_ui_client_operating_system_type = 
	    STATIC_SYMBOL("GET-UI-CLIENT-OPERATING-SYSTEM-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_operating_system_type,
	    STATIC_FUNCTION(get_ui_client_operating_system_type,NIL,FALSE,
	    1,1));
    add_virtual_attribute(Qui_client_operating_system_type,
	    list_constant_75,list_constant_58,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_operating_system_type),
	    SYMBOL_FUNCTION(Qget_ui_client_operating_system_type),Nil);
    Qui_client_time_of_last_connection = 
	    STATIC_SYMBOL("UI-CLIENT-TIME-OF-LAST-CONNECTION",AB_package);
    temp = CONS(Qui_client_time_of_last_connection,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_time_of_last_connection,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qunix_time_qm = STATIC_SYMBOL("UNIX-TIME\?",AB_package);
    Qg2_window_time_of_last_connection_qm = 
	    STATIC_SYMBOL("G2-WINDOW-TIME-OF-LAST-CONNECTION\?",AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_10);
    Qinitial_ui_client_time_of_last_connection = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-TIME-OF-LAST-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_time_of_last_connection,
	    STATIC_FUNCTION(initial_ui_client_time_of_last_connection,NIL,
	    FALSE,1,1));
    Qget_ui_client_time_of_last_connection = 
	    STATIC_SYMBOL("GET-UI-CLIENT-TIME-OF-LAST-CONNECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_time_of_last_connection,
	    STATIC_FUNCTION(get_ui_client_time_of_last_connection,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qui_client_time_of_last_connection,
	    list_constant_75,list_constant_76,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_time_of_last_connection),
	    SYMBOL_FUNCTION(Qget_ui_client_time_of_last_connection),Nil);
    Qui_client_user_name_in_operating_system = 
	    STATIC_SYMBOL("UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM",
	    AB_package);
    temp = CONS(Qui_client_user_name_in_operating_system,
	    All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_user_name_in_operating_system,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qwhole_string_qm = STATIC_SYMBOL("WHOLE-STRING\?",AB_package);
    Qg2_window_os_user_name_qm = STATIC_SYMBOL("G2-WINDOW-OS-USER-NAME\?",
	    AB_package);
    Qinitial_ui_client_user_name_in_operating_system = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_user_name_in_operating_system,
	    STATIC_FUNCTION(initial_ui_client_user_name_in_operating_system,
	    NIL,FALSE,1,1));
    Qget_ui_client_user_name_in_operating_system = 
	    STATIC_SYMBOL("GET-UI-CLIENT-USER-NAME-IN-OPERATING-SYSTEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_user_name_in_operating_system,
	    STATIC_FUNCTION(get_ui_client_user_name_in_operating_system,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_user_name_in_operating_system,
	    list_constant_75,list_constant_60,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_user_name_in_operating_system),
	    SYMBOL_FUNCTION(Qget_ui_client_user_name_in_operating_system),Nil);
    temp = CONS(Qui_client_specific_language,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_specific_language,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qlanguage_qm = STATIC_SYMBOL("LANGUAGE\?",AB_package);
    Qspecific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",AB_package);
    Qinitial_ui_client_specific_language = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-SPECIFIC-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_specific_language,
	    STATIC_FUNCTION(initial_ui_client_specific_language,NIL,FALSE,
	    1,1));
    Qget_ui_client_specific_language = 
	    STATIC_SYMBOL("GET-UI-CLIENT-SPECIFIC-LANGUAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_specific_language,
	    STATIC_FUNCTION(get_ui_client_specific_language,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_specific_language,list_constant_75,
	    list_constant_58,list_constant_31,
	    SYMBOL_FUNCTION(Qinitial_ui_client_specific_language),
	    SYMBOL_FUNCTION(Qget_ui_client_specific_language),Nil);
    temp = CONS(Qui_client_connection_status,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_connection_status,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qconnected = STATIC_SYMBOL("CONNECTED",AB_package);
    Qnot_connected = STATIC_SYMBOL("NOT-CONNECTED",AB_package);
    Qg2_connection_status = STATIC_SYMBOL("G2-CONNECTION-STATUS",AB_package);
    Qinitial_ui_client_connection_status = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-CONNECTION-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_connection_status,
	    STATIC_FUNCTION(initial_ui_client_connection_status,NIL,FALSE,
	    1,1));
    Qget_ui_client_connection_status = 
	    STATIC_SYMBOL("GET-UI-CLIENT-CONNECTION-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_connection_status,
	    STATIC_FUNCTION(get_ui_client_connection_status,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_connection_status,list_constant_75,
	    list_constant_58,list_constant_31,
	    SYMBOL_FUNCTION(Qinitial_ui_client_connection_status),
	    SYMBOL_FUNCTION(Qget_ui_client_connection_status),Nil);
    Qui_client_user_is_valid = STATIC_SYMBOL("UI-CLIENT-USER-IS-VALID",
	    AB_package);
    temp = CONS(Qui_client_user_is_valid,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_user_is_valid,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_window_user_is_valid = STATIC_SYMBOL("G2-WINDOW-USER-IS-VALID",
	    AB_package);
    list_constant_77 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_77);
    Qinitial_ui_client_user_is_valid = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-USER-IS-VALID",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_user_is_valid,
	    STATIC_FUNCTION(initial_ui_client_user_is_valid,NIL,FALSE,1,1));
    Qget_ui_client_user_is_valid = 
	    STATIC_SYMBOL("GET-UI-CLIENT-USER-IS-VALID",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_user_is_valid,
	    STATIC_FUNCTION(get_ui_client_user_is_valid,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_user_is_valid,list_constant_75,
	    list_constant_78,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_user_is_valid),
	    SYMBOL_FUNCTION(Qget_ui_client_user_is_valid),Nil);
    Qui_client_mode_is_valid = STATIC_SYMBOL("UI-CLIENT-MODE-IS-VALID",
	    AB_package);
    temp = CONS(Qui_client_mode_is_valid,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_mode_is_valid,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qg2_window_mode_is_valid = STATIC_SYMBOL("G2-WINDOW-MODE-IS-VALID",
	    AB_package);
    Qinitial_ui_client_mode_is_valid = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-MODE-IS-VALID",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_mode_is_valid,
	    STATIC_FUNCTION(initial_ui_client_mode_is_valid,NIL,FALSE,1,1));
    Qget_ui_client_mode_is_valid = 
	    STATIC_SYMBOL("GET-UI-CLIENT-MODE-IS-VALID",AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_mode_is_valid,
	    STATIC_FUNCTION(get_ui_client_mode_is_valid,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_mode_is_valid,list_constant_75,
	    list_constant_78,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_mode_is_valid),
	    SYMBOL_FUNCTION(Qget_ui_client_mode_is_valid),Nil);
    temp = CONS(Qui_client_interface,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_session),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qui_client_interface,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_session),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_ui_client_interface = 
	    STATIC_SYMBOL("INITIAL-UI-CLIENT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_ui_client_interface,
	    STATIC_FUNCTION(initial_ui_client_interface,NIL,FALSE,1,1));
    Qget_ui_client_interface = STATIC_SYMBOL("GET-UI-CLIENT-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_ui_client_interface,
	    STATIC_FUNCTION(get_ui_client_interface,NIL,FALSE,1,1));
    add_virtual_attribute(Qui_client_interface,list_constant_72,
	    list_constant_9,Qnil,
	    SYMBOL_FUNCTION(Qinitial_ui_client_interface),
	    SYMBOL_FUNCTION(Qget_ui_client_interface),Nil);
    Quses_floating_license = STATIC_SYMBOL("USES-FLOATING-LICENSE",AB_package);
    temp = CONS(Quses_floating_license,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Quses_floating_license,temp_1);
    set_property_value_function(get_symbol_properties_function(Qui_client_item),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_uses_floating_license = 
	    STATIC_SYMBOL("INITIAL-USES-FLOATING-LICENSE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_uses_floating_license,
	    STATIC_FUNCTION(initial_uses_floating_license,NIL,FALSE,1,1));
    Qget_uses_floating_license = STATIC_SYMBOL("GET-USES-FLOATING-LICENSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_uses_floating_license,
	    STATIC_FUNCTION(get_uses_floating_license,NIL,FALSE,1,1));
    add_virtual_attribute(Quses_floating_license,list_constant_75,
	    list_constant_78,Qnil,
	    SYMBOL_FUNCTION(Qinitial_uses_floating_license),
	    SYMBOL_FUNCTION(Qget_uses_floating_license),Nil);
    if (Local_ui_client_test_mode_p == UNBOUND)
	Local_ui_client_test_mode_p = Nil;
    list_constant_79 = STATIC_CONS(Qcallback_representation,Qnil);
    check_if_superior_classes_are_defined(Qshowing_representation,
	    list_constant_79);
    string_constant_48 = STATIC_STRING("1l1l8t");
    string_constant_49 = 
	    STATIC_STRING("1l4z8r83a0y83a0y83a=y83a=y08k001m1l8l1l8o00000");
    string_constant_50 = STATIC_STRING("1n8q1n83a=y1l830Xy8t1n83a0y8k8o");
    temp_1 = regenerate_optimized_constant(string_constant_48);
    temp_2 = regenerate_optimized_constant(string_constant_49);
    add_class_to_environment(9,Qshowing_representation,list_constant_79,
	    Nil,temp_1,Nil,temp_2,list_constant_79,
	    regenerate_optimized_constant(string_constant_50),Nil);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qgo_to_item = STATIC_SYMBOL("GO-TO-ITEM",AB_package);
    Qsymbolic_x_scale = STATIC_SYMBOL("SYMBOLIC-X-SCALE",AB_package);
    Qsymbolic_y_scale = STATIC_SYMBOL("SYMBOLIC-Y-SCALE",AB_package);
    Qsymbolic_x_in_workspace = STATIC_SYMBOL("SYMBOLIC-X-IN-WORKSPACE",
	    AB_package);
    Qsymbolic_y_in_workspace = STATIC_SYMBOL("SYMBOLIC-Y-IN-WORKSPACE",
	    AB_package);
    Qsymbolic_x_in_window = STATIC_SYMBOL("SYMBOLIC-X-IN-WINDOW",AB_package);
    Qsymbolic_y_in_window = STATIC_SYMBOL("SYMBOLIC-Y-IN-WINDOW",AB_package);
    Qx_offset_units = STATIC_SYMBOL("X-OFFSET-UNITS",AB_package);
    Qy_offset_units = STATIC_SYMBOL("Y-OFFSET-UNITS",AB_package);
    Qsymbolic_x_offset_direction = 
	    STATIC_SYMBOL("SYMBOLIC-X-OFFSET-DIRECTION",AB_package);
    Qsymbolic_y_offset_direction = 
	    STATIC_SYMBOL("SYMBOLIC-Y-OFFSET-DIRECTION",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qx_in_workspace = STATIC_SYMBOL("X-IN-WORKSPACE",AB_package);
    Qy_in_workspace = STATIC_SYMBOL("Y-IN-WORKSPACE",AB_package);
    Qx_in_window = STATIC_SYMBOL("X-IN-WINDOW",AB_package);
    Qy_in_window = STATIC_SYMBOL("Y-IN-WINDOW",AB_package);
    Qg2_subscribe_to_workspaces_showing = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-WORKSPACES-SHOWING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_workspaces_showing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qlocal = STATIC_SYMBOL("LOCAL",AB_package);
    Qg2_window_management_type = STATIC_SYMBOL("G2-WINDOW-MANAGEMENT-TYPE",
	    AB_package);
    string_constant_10 = STATIC_STRING("No local window for G2");
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_workspaces_showing,
	    STATIC_FUNCTION(g2_subscribe_to_workspaces_showing,NIL,FALSE,3,3));
    Qg2_subscribe_to_workspaces_showing_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-WORKSPACES-SHOWING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclient_item = STATIC_SYMBOL("CLIENT-ITEM",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)3L,Qclient_item,Ktype,
	    list_constant_75);
    Qcallback = STATIC_SYMBOL("CALLBACK",AB_package);
    list_constant_81 = STATIC_CONS(Qcallback,list_constant_62);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    list_constant_82 = STATIC_LIST_STAR((SI_Long)3L,Quser_data,Ktype,
	    list_constant_43);
    list_constant_83 = STATIC_LIST((SI_Long)3L,list_constant_80,
	    list_constant_81,list_constant_82);
    list_constant_84 = STATIC_CONS(Qinteger,Qnil);
    mutate_global_property(Qg2_subscribe_to_workspaces_showing,
	    make_system_rpc_1(Qg2_subscribe_to_workspaces_showing_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_83,
	    Nil,T),list_constant_84),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subscribe_to_workspaces_showing,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_workspaces_showing_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_workspaces_showing_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_unsubscribe_to_workspaces_showing = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-WORKSPACES-SHOWING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unsubscribe_to_workspaces_showing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_workspaces_showing,
	    STATIC_FUNCTION(g2_unsubscribe_to_workspaces_showing,NIL,FALSE,
	    1,1));
    Qg2_unsubscribe_to_workspaces_showing_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-WORKSPACES-SHOWING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qsubscription_handle = STATIC_SYMBOL("SUBSCRIPTION-HANDLE",AB_package);
    list_constant_85 = STATIC_CONS(Qsubscription_handle,list_constant_42);
    list_constant_86 = STATIC_CONS(list_constant_85,Qnil);
    mutate_global_property(Qg2_unsubscribe_to_workspaces_showing,
	    make_system_rpc_1(Qg2_unsubscribe_to_workspaces_showing_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_86,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unsubscribe_to_workspaces_showing,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_workspaces_showing_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_workspaces_showing_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_subscribe_to_field_edit_actions = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-FIELD-EDIT-ACTIONS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_field_edit_actions,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qfield_edit_representation = STATIC_SYMBOL("FIELD-EDIT-REPRESENTATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_field_edit_actions,
	    STATIC_FUNCTION(g2_subscribe_to_field_edit_actions,NIL,FALSE,3,3));
    Qg2_subscribe_to_field_edit_actions_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-FIELD-EDIT-ACTIONS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_72);
    list_constant_88 = STATIC_CONS(Qclient_item,list_constant_87);
    list_constant_89 = STATIC_LIST((SI_Long)2L,list_constant_81,
	    list_constant_82);
    list_constant_90 = STATIC_CONS(list_constant_88,list_constant_89);
    mutate_global_property(Qg2_subscribe_to_field_edit_actions,
	    make_system_rpc_1(Qg2_subscribe_to_field_edit_actions_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_90,
	    Nil,T),list_constant_84),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subscribe_to_field_edit_actions,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_field_edit_actions_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_field_edit_actions_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_unsubscribe_to_field_edit_actions = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-FIELD-EDIT-ACTIONS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unsubscribe_to_field_edit_actions,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_field_edit_actions,
	    STATIC_FUNCTION(g2_unsubscribe_to_field_edit_actions,NIL,FALSE,
	    1,1));
    Qg2_unsubscribe_to_field_edit_actions_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-FIELD-EDIT-ACTIONS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_unsubscribe_to_field_edit_actions,
	    make_system_rpc_1(Qg2_unsubscribe_to_field_edit_actions_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_86,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unsubscribe_to_field_edit_actions,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_field_edit_actions_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_field_edit_actions_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_subscribe_to_modules = STATIC_SYMBOL("G2-SUBSCRIBE-TO-MODULES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_subscribe_to_modules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qab_modules = STATIC_SYMBOL("MODULES",AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    Qlogbook = STATIC_SYMBOL("LOGBOOK",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_modules,
	    STATIC_FUNCTION(g2_subscribe_to_modules,NIL,FALSE,5,5));
    Qg2_subscribe_to_modules_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-MODULES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qmodule_callback = STATIC_SYMBOL("MODULE-CALLBACK",AB_package);
    list_constant_92 = STATIC_CONS(Qmodule_callback,list_constant_62);
    Qmodule_callback_data = STATIC_SYMBOL("MODULE-CALLBACK-DATA",AB_package);
    list_constant_91 = STATIC_CONS(Ktype,list_constant_43);
    list_constant_93 = STATIC_CONS(Qmodule_callback_data,list_constant_91);
    Qmodule_information_callback = 
	    STATIC_SYMBOL("MODULE-INFORMATION-CALLBACK",AB_package);
    list_constant_94 = STATIC_CONS(Qmodule_information_callback,
	    list_constant_62);
    Qmodule_information_callback_data = 
	    STATIC_SYMBOL("MODULE-INFORMATION-CALLBACK-DATA",AB_package);
    list_constant_95 = STATIC_CONS(Qmodule_information_callback_data,
	    list_constant_91);
    list_constant_96 = STATIC_LIST((SI_Long)4L,list_constant_92,
	    list_constant_93,list_constant_94,list_constant_95);
    list_constant_97 = STATIC_CONS(list_constant_10,Qnil);
    mutate_global_property(Qg2_subscribe_to_modules,
	    make_system_rpc_1(Qg2_subscribe_to_modules_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_96,
	    Nil,T),list_constant_97),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subscribe_to_modules,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_modules_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_modules_system_rpc_internal,
	    NIL,FALSE,5,5));
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qtop_level_module = STATIC_SYMBOL("TOP-LEVEL-MODULE",AB_package);
    Qdirectly_required_modules = STATIC_SYMBOL("DIRECTLY-REQUIRED-MODULES",
	    AB_package);
    Qgsi_interface_icp_socket = STATIC_SYMBOL("GSI-INTERFACE-ICP-SOCKET",
	    AB_package);
    Qis_top_level = STATIC_SYMBOL("IS-TOP-LEVEL",AB_package);
    Qsubscription_handles = STATIC_SYMBOL("SUBSCRIPTION-HANDLES",AB_package);
    Qother_system_tables = STATIC_SYMBOL("OTHER-SYSTEM-TABLES",AB_package);
    Qsubscription_initial_value = 
	    STATIC_SYMBOL("SUBSCRIPTION-INITIAL-VALUE",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qtop_level_kb_workspaces = STATIC_SYMBOL("TOP-LEVEL-KB-WORKSPACES",
	    AB_package);
    Qg2_unsubscribe_to_modules = STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-MODULES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unsubscribe_to_modules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_modules,
	    STATIC_FUNCTION(g2_unsubscribe_to_modules,NIL,FALSE,1,1));
    Qg2_unsubscribe_to_modules_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-MODULES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_unsubscribe_to_modules,
	    make_system_rpc_1(Qg2_unsubscribe_to_modules_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unsubscribe_to_modules,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_modules_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_modules_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    Qclear_kb = STATIC_SYMBOL("CLEAR-KB",AB_package);
    Qmodule_name = STATIC_SYMBOL("MODULE-NAME",AB_package);
    Qadd_as_top_level_workspace = 
	    STATIC_SYMBOL("ADD-AS-TOP-LEVEL-WORKSPACE",AB_package);
    Qremove_as_top_level_workspace = 
	    STATIC_SYMBOL("REMOVE-AS-TOP-LEVEL-WORKSPACE",AB_package);
    Qfile_progress = STATIC_SYMBOL("FILE-PROGRESS",AB_package);
    Qmodule_load_request = STATIC_SYMBOL("MODULE-LOAD-REQUEST",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qfile_progress,
	    Qmodule_load_request);
    array_constant_2 = STATIC_ARRAY(list_constant_28,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    string_constant_11 = STATIC_STRING("Saving ");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    string_constant_12 = STATIC_STRING("Loading ");
    string_constant_13 = STATIC_STRING("~a~a");
    string_constant_14 = STATIC_STRING("  ~d lines ");
    string_constant_15 = STATIC_STRING("  ~d%");
    string_constant_16 = STATIC_STRING("  [~a]");
    Qwriting = STATIC_SYMBOL("WRITING",AB_package);
    Qg2_subscribe_to_file_progress_changes = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-FILE-PROGRESS-CHANGES",AB_package);
    Qg2_subscribe_to_file_progress_changes_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-FILE-PROGRESS-CHANGES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qprogress_callback = STATIC_SYMBOL("PROGRESS-CALLBACK",AB_package);
    list_constant_98 = STATIC_CONS(Qprogress_callback,list_constant_62);
    Qprogress_callback_data = STATIC_SYMBOL("PROGRESS-CALLBACK-DATA",
	    AB_package);
    list_constant_99 = STATIC_CONS(Qprogress_callback_data,list_constant_91);
    list_constant_100 = STATIC_LIST((SI_Long)2L,list_constant_98,
	    list_constant_99);
    mutate_global_property(Qg2_subscribe_to_file_progress_changes,
	    make_system_rpc_1(Qg2_subscribe_to_file_progress_changes_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_100,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subscribe_to_file_progress_changes,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_file_progress_changes_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_file_progress_changes_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_unsubscribe_to_file_progress_changes = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-FILE-PROGRESS-CHANGES",
	    AB_package);
    Qg2_unsubscribe_to_file_progress_changes_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-FILE-PROGRESS-CHANGES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_unsubscribe_to_file_progress_changes,
	    make_system_rpc_1(Qg2_unsubscribe_to_file_progress_changes_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unsubscribe_to_file_progress_changes,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_file_progress_changes_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_file_progress_changes_system_rpc_internal,
	    NIL,FALSE,1,1));
    if (Current_t2_dialog_sequence_number == UNBOUND)
	Current_t2_dialog_sequence_number = FIX((SI_Long)0L);
    if (T2_dialog_result_alist == UNBOUND)
	T2_dialog_result_alist = Nil;
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qenter = STATIC_SYMBOL("ENTER",AB_package);
    Qrecompile = STATIC_SYMBOL("RECOMPILE",AB_package);
    Qstatus_update = STATIC_SYMBOL("STATUS-UPDATE",AB_package);
    Qnotify_t2_for_local_recompile = 
	    STATIC_SYMBOL("NOTIFY-T2-FOR-LOCAL-RECOMPILE",AB_package);
    SET_SYMBOL_FUNCTION(Qnotify_t2_for_local_recompile,
	    STATIC_FUNCTION(notify_t2_for_local_recompile,NIL,FALSE,1,1));
    Qupdate = STATIC_SYMBOL("UPDATE",AB_package);
    Qupdate_type = STATIC_SYMBOL("UPDATE-TYPE",AB_package);
    Qupdate_info = STATIC_SYMBOL("UPDATE-INFO",AB_package);
    Qleave = STATIC_SYMBOL("LEAVE",AB_package);
    Qg2_return_values_to_unsolicited_dialog = 
	    STATIC_SYMBOL("G2-RETURN-VALUES-TO-UNSOLICITED-DIALOG",AB_package);
    Qg2_return_values_to_unsolicited_dialog_system_rpc_internal = 
	    STATIC_SYMBOL("G2-RETURN-VALUES-TO-UNSOLICITED-DIALOG-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdialog_sequence_number = STATIC_SYMBOL("DIALOG-SEQUENCE-NUMBER",
	    AB_package);
    list_constant_101 = STATIC_CONS(Qdialog_sequence_number,list_constant_42);
    Qdialog_values = STATIC_SYMBOL("DIALOG-VALUES",AB_package);
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qdialog_values,Ktype,
	    list_constant_1);
    list_constant_103 = STATIC_LIST((SI_Long)3L,list_constant_101,
	    list_constant_102,list_constant_88);
    mutate_global_property(Qg2_return_values_to_unsolicited_dialog,
	    make_system_rpc_1(Qg2_return_values_to_unsolicited_dialog_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_103,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_return_values_to_unsolicited_dialog,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_return_values_to_unsolicited_dialog_system_rpc_internal,
	    STATIC_FUNCTION(g2_return_values_to_unsolicited_dialog_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_subscribe_to_unsolicited_dialogs = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-UNSOLICITED-DIALOGS",AB_package);
    Qg2_subscribe_to_unsolicited_dialogs_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBSCRIBE-TO-UNSOLICITED-DIALOGS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdialog_callback = STATIC_SYMBOL("DIALOG-CALLBACK",AB_package);
    list_constant_104 = STATIC_CONS(Qdialog_callback,list_constant_62);
    Qdialog_callback_data = STATIC_SYMBOL("DIALOG-CALLBACK-DATA",AB_package);
    list_constant_105 = STATIC_CONS(Qdialog_callback_data,list_constant_91);
    list_constant_106 = STATIC_LIST((SI_Long)2L,list_constant_104,
	    list_constant_105);
    mutate_global_property(Qg2_subscribe_to_unsolicited_dialogs,
	    make_system_rpc_1(Qg2_subscribe_to_unsolicited_dialogs_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_106,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subscribe_to_unsolicited_dialogs,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_subscribe_to_unsolicited_dialogs_system_rpc_internal,
	    STATIC_FUNCTION(g2_subscribe_to_unsolicited_dialogs_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_unsubscribe_to_unsolicited_dialogs = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-UNSOLICITED-DIALOGS",AB_package);
    Qg2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNSUBSCRIBE-TO-UNSOLICITED-DIALOGS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_unsubscribe_to_unsolicited_dialogs,
	    make_system_rpc_1(Qg2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unsubscribe_to_unsolicited_dialogs,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal,
	    STATIC_FUNCTION(g2_unsubscribe_to_unsolicited_dialogs_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_files_in_directory = STATIC_SYMBOL("G2-FILES-IN-DIRECTORY",AB_package);
    Qg2_files_in_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILES-IN-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdirectory_string = STATIC_SYMBOL("DIRECTORY-STRING",AB_package);
    list_constant_107 = STATIC_CONS(Qdirectory_string,list_constant_41);
    list_constant_109 = STATIC_CONS(list_constant_107,Qnil);
    Qtext_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    list_constant_108 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_list);
    list_constant_110 = STATIC_CONS(list_constant_108,Qnil);
    mutate_global_property(Qg2_files_in_directory,
	    make_system_rpc_1(Qg2_files_in_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_109,
	    Nil,T),list_constant_110),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_files_in_directory,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_17 = STATIC_STRING("G2-FILES-IN-DIRECTORY() failed ~a");
    SET_SYMBOL_FUNCTION(Qg2_files_in_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_files_in_directory_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_subdirectories_in_directory = 
	    STATIC_SYMBOL("G2-SUBDIRECTORIES-IN-DIRECTORY",AB_package);
    Qg2_subdirectories_in_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SUBDIRECTORIES-IN-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_subdirectories_in_directory,
	    make_system_rpc_1(Qg2_subdirectories_in_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_109,
	    Nil,T),list_constant_110),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_subdirectories_in_directory,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_18 = 
	    STATIC_STRING("G2-SUBDIRECTORIES-IN-DIRECTORY() failed ~a");
    SET_SYMBOL_FUNCTION(Qg2_subdirectories_in_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_subdirectories_in_directory_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_host_name = STATIC_SYMBOL("G2-GET-HOST-NAME",AB_package);
    Qg2_get_host_name_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-HOST-NAME-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_get_host_name,
	    make_system_rpc_1(Qg2_get_host_name_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_host_name,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_19 = STATIC_STRING("GET-HOST-NAME() failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_host_name_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_host_name_system_rpc_internal,NIL,FALSE,
	    1,1));
    Qg2_get_port_number_or_name = 
	    STATIC_SYMBOL("G2-GET-PORT-NUMBER-OR-NAME",AB_package);
    Qg2_get_port_number_or_name_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PORT-NUMBER-OR-NAME-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_port_number_or_name,
	    make_system_rpc_1(Qg2_get_port_number_or_name_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_port_number_or_name,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_20 = STATIC_STRING("GET-PORT-NUMBER-OR-NAME() failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_port_number_or_name_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_port_number_or_name_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_get_port_number_or_name_given_index = 
	    STATIC_SYMBOL("G2-GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX",AB_package);
    Qg2_get_port_number_or_name_given_index_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    list_constant_111 = STATIC_CONS(Qindex,list_constant_42);
    list_constant_112 = STATIC_CONS(list_constant_111,Qnil);
    mutate_global_property(Qg2_get_port_number_or_name_given_index,
	    make_system_rpc_1(Qg2_get_port_number_or_name_given_index_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_112,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_port_number_or_name_given_index,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_21 = 
	    STATIC_STRING("GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX(~s) failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_port_number_or_name_given_index_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_port_number_or_name_given_index_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_structured_version = STATIC_SYMBOL("G2-GET-STRUCTURED-VERSION",
	    AB_package);
    Qg2_get_structured_version_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-STRUCTURED-VERSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_structured_version,
	    make_system_rpc_1(Qg2_get_structured_version_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_97),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_structured_version,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_22 = STATIC_STRING("G2-GET-VERSION() failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_structured_version_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_structured_version_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_get_software_version = STATIC_SYMBOL("G2-GET-SOFTWARE-VERSION",
	    AB_package);
    Qg2_get_software_version_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-SOFTWARE-VERSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_software_version,
	    make_system_rpc_1(Qg2_get_software_version_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_software_version,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_23 = STATIC_STRING("GET-SOFTWARE-VERSION() failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_software_version_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_software_version_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_get_build_version = STATIC_SYMBOL("G2-GET-BUILD-VERSION",AB_package);
    Qg2_get_build_version_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-BUILD-VERSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_build_version,
	    make_system_rpc_1(Qg2_get_build_version_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_build_version,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_24 = STATIC_STRING("G2-GET-BUILD-VERSION() failed.");
    SET_SYMBOL_FUNCTION(Qg2_get_build_version_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_build_version_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_unix_time = STATIC_SYMBOL("G2-UNIX-TIME",AB_package);
    Qg2_unix_time_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNIX-TIME-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_113 = STATIC_CONS(Qfloat,Qnil);
    mutate_global_property(Qg2_unix_time,
	    make_system_rpc_1(Qg2_unix_time_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unix_time,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unix_time_system_rpc_internal,
	    STATIC_FUNCTION(g2_unix_time_system_rpc_internal,NIL,FALSE,1,1));
    Qg2_unix_time_at_start = STATIC_SYMBOL("G2-UNIX-TIME-AT-START",AB_package);
    Qg2_unix_time_at_start_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNIX-TIME-AT-START-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_unix_time_at_start,
	    make_system_rpc_1(Qg2_unix_time_at_start_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unix_time_at_start,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_unix_time_at_start_system_rpc_internal,
	    STATIC_FUNCTION(g2_unix_time_at_start_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_kill_process = STATIC_SYMBOL("G2-KILL-PROCESS",AB_package);
    Qg2_kill_process_system_rpc_internal = 
	    STATIC_SYMBOL("G2-KILL-PROCESS-SYSTEM-RPC-INTERNAL",AB_package);
    Qprocess_id = STATIC_SYMBOL("PROCESS-ID",AB_package);
    list_constant_114 = STATIC_LIST_STAR((SI_Long)3L,Qprocess_id,Ktype,
	    list_constant_113);
    list_constant_115 = STATIC_CONS(list_constant_114,Qnil);
    mutate_global_property(Qg2_kill_process,
	    make_system_rpc_1(Qg2_kill_process_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_115,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_kill_process,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_kill_process_system_rpc_internal,
	    STATIC_FUNCTION(g2_kill_process_system_rpc_internal,NIL,FALSE,
	    2,2));
    Qg2_process_exists = STATIC_SYMBOL("G2-PROCESS-EXISTS",AB_package);
    Qg2_process_exists_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PROCESS-EXISTS-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_116 = STATIC_CONS(Qprocess_id,list_constant_42);
    list_constant_117 = STATIC_CONS(list_constant_116,Qnil);
    mutate_global_property(Qg2_process_exists,
	    make_system_rpc_1(Qg2_process_exists_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_117,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_process_exists,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_25 = STATIC_STRING("PROCESS-EXISTS([~s]) failed.");
    SET_SYMBOL_FUNCTION(Qg2_process_exists_system_rpc_internal,
	    STATIC_FUNCTION(g2_process_exists_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_spawn_process_with_arguments = 
	    STATIC_SYMBOL("G2-SPAWN-PROCESS-WITH-ARGUMENTS",AB_package);
    Qg2_spawn_process_with_arguments_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SPAWN-PROCESS-WITH-ARGUMENTS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    list_constant_118 = STATIC_CONS(Qcommand,list_constant_41);
    list_constant_119 = STATIC_CONS(list_constant_118,Qnil);
    mutate_global_property(Qg2_spawn_process_with_arguments,
	    make_system_rpc_1(Qg2_spawn_process_with_arguments_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_119,
	    Nil,T),list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_spawn_process_with_arguments,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_26 = 
	    STATIC_STRING("SPAWN-PROCESS-WITH_ARGUMENTS(~a) failed.");
    SET_SYMBOL_FUNCTION(Qg2_spawn_process_with_arguments_system_rpc_internal,
	    STATIC_FUNCTION(g2_spawn_process_with_arguments_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_spawn_process_to_run_command_line = 
	    STATIC_SYMBOL("G2-SPAWN-PROCESS-TO-RUN-COMMAND-LINE",AB_package);
    Qg2_spawn_process_to_run_command_line_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SPAWN-PROCESS-TO-RUN-COMMAND-LINE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_spawn_process_to_run_command_line,
	    make_system_rpc_1(Qg2_spawn_process_to_run_command_line_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_119,
	    Nil,T),list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_spawn_process_to_run_command_line,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_27 = 
	    STATIC_STRING("SPAWN-PROCESS-TO-RUN-COMMAND-LINE(~a) failed.");
    SET_SYMBOL_FUNCTION(Qg2_spawn_process_to_run_command_line_system_rpc_internal,
	    STATIC_FUNCTION(g2_spawn_process_to_run_command_line_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_devices_on_machine = STATIC_SYMBOL("G2-DEVICES-ON-MACHINE",AB_package);
    Qg2_devices_on_machine_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DEVICES-ON-MACHINE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_devices_on_machine,
	    make_system_rpc_1(Qg2_devices_on_machine_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_110),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_devices_on_machine,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_devices_on_machine_system_rpc_internal,
	    STATIC_FUNCTION(g2_devices_on_machine_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_disk_space_available_in_directory = 
	    STATIC_SYMBOL("G2-DISK-SPACE-AVAILABLE-IN-DIRECTORY",AB_package);
    Qg2_disk_space_available_in_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DISK-SPACE-AVAILABLE-IN-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_disk_space_available_in_directory,
	    make_system_rpc_1(Qg2_disk_space_available_in_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_109,
	    Nil,T),list_constant_84),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_disk_space_available_in_directory,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_28 = 
	    STATIC_STRING("DISK-SPACE-AVAILABLE-IN-DIRECTORY(~a) failed.:~a");
    SET_SYMBOL_FUNCTION(Qg2_disk_space_available_in_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_disk_space_available_in_directory_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_change_default_directory = 
	    STATIC_SYMBOL("G2-CHANGE-DEFAULT-DIRECTORY",AB_package);
    Qg2_change_default_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CHANGE-DEFAULT-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qnew_default = STATIC_SYMBOL("NEW-DEFAULT",AB_package);
    list_constant_120 = STATIC_CONS(Qnew_default,list_constant_41);
    list_constant_121 = STATIC_CONS(list_constant_120,Qnil);
    mutate_global_property(Qg2_change_default_directory,
	    make_system_rpc_1(Qg2_change_default_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_121,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_change_default_directory,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_29 = 
	    STATIC_STRING("CHANGE-DEFAULT-DIRECTORY(~a) failed: ~a.");
    SET_SYMBOL_FUNCTION(Qg2_change_default_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_change_default_directory_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_default_directory = STATIC_SYMBOL("G2-DEFAULT-DIRECTORY",AB_package);
    Qg2_default_directory_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DEFAULT-DIRECTORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_default_directory,
	    make_system_rpc_1(Qg2_default_directory_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_default_directory,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_30 = STATIC_STRING("DEFAULT-DIRECTORY() failed: ~A");
    SET_SYMBOL_FUNCTION(Qg2_default_directory_system_rpc_internal,
	    STATIC_FUNCTION(g2_default_directory_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_directory_exists = STATIC_SYMBOL("G2-DIRECTORY-EXISTS",AB_package);
    Qg2_directory_exists_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DIRECTORY-EXISTS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_directory_exists,
	    make_system_rpc_1(Qg2_directory_exists_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_109,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_directory_exists,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_directory_exists_system_rpc_internal,
	    STATIC_FUNCTION(g2_directory_exists_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_latest_date_file_attributes_were_changed = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED",
	    AB_package);
    Qg2_latest_date_file_attributes_were_changed_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qfile_string = STATIC_SYMBOL("FILE-STRING",AB_package);
    list_constant_122 = STATIC_CONS(Qfile_string,list_constant_41);
    list_constant_123 = STATIC_CONS(list_constant_122,Qnil);
    mutate_global_property(Qg2_latest_date_file_attributes_were_changed,
	    make_system_rpc_1(Qg2_latest_date_file_attributes_were_changed_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_123,
	    Nil,T),list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_latest_date_file_attributes_were_changed,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_31 = 
	    STATIC_STRING("LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED(~a): ~a");
    SET_SYMBOL_FUNCTION(Qg2_latest_date_file_attributes_were_changed_system_rpc_internal,
	    STATIC_FUNCTION(g2_latest_date_file_attributes_were_changed_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_latest_date_file_was_accessed = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-WAS-ACCESSED",AB_package);
    Qg2_latest_date_file_was_accessed_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-WAS-ACCESSED-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_latest_date_file_was_accessed,
	    make_system_rpc_1(Qg2_latest_date_file_was_accessed_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_123,
	    Nil,T),list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_latest_date_file_was_accessed,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_32 = 
	    STATIC_STRING("LATEST-DATE-FILE-WAS-ACCESSED(~a): ~a");
    SET_SYMBOL_FUNCTION(Qg2_latest_date_file_was_accessed_system_rpc_internal,
	    STATIC_FUNCTION(g2_latest_date_file_was_accessed_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_latest_date_file_was_modified = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-WAS-MODIFIED",AB_package);
    Qg2_latest_date_file_was_modified_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LATEST-DATE-FILE-WAS-MODIFIED-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_latest_date_file_was_modified,
	    make_system_rpc_1(Qg2_latest_date_file_was_modified_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_123,
	    Nil,T),list_constant_113),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_latest_date_file_was_modified,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_latest_date_file_was_modified_system_rpc_internal,
	    STATIC_FUNCTION(g2_latest_date_file_was_modified_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_length_of_file = STATIC_SYMBOL("G2-LENGTH-OF-FILE",AB_package);
    Qg2_length_of_file_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LENGTH-OF-FILE-SYSTEM-RPC-INTERNAL",AB_package);
    Qab_file_stream = STATIC_SYMBOL("FILE-STREAM",AB_package);
    Qg2_stream = STATIC_SYMBOL("G2-STREAM",AB_package);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_stream);
    list_constant_125 = STATIC_LIST((SI_Long)3L,Qab_file_stream,Ktype,
	    list_constant_124);
    list_constant_126 = STATIC_CONS(list_constant_125,Qnil);
    mutate_global_property(Qg2_length_of_file,
	    make_system_rpc_1(Qg2_length_of_file_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_126,
	    Nil,T),list_constant_84),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_length_of_file,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_33 = STATIC_STRING("LENGTH-OF-FILE(~a) failed: ~a");
    SET_SYMBOL_FUNCTION(Qg2_length_of_file_system_rpc_internal,
	    STATIC_FUNCTION(g2_length_of_file_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_file_names_are_identical = 
	    STATIC_SYMBOL("G2-FILE-NAMES-ARE-IDENTICAL",AB_package);
    Qg2_file_names_are_identical_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-NAMES-ARE-IDENTICAL-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qfilestring1 = STATIC_SYMBOL("FILESTRING1",AB_package);
    list_constant_127 = STATIC_CONS(Qfilestring1,list_constant_41);
    Qfilestring2 = STATIC_SYMBOL("FILESTRING2",AB_package);
    list_constant_128 = STATIC_CONS(Qfilestring2,list_constant_41);
    list_constant_129 = STATIC_LIST((SI_Long)2L,list_constant_127,
	    list_constant_128);
    mutate_global_property(Qg2_file_names_are_identical,
	    make_system_rpc_1(Qg2_file_names_are_identical_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_129,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_names_are_identical,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_names_are_identical_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_names_are_identical_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_file_exists = STATIC_SYMBOL("G2-FILE-EXISTS",AB_package);
    Qg2_file_exists_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-EXISTS-SYSTEM-RPC-INTERNAL",AB_package);
    Qfilestring = STATIC_SYMBOL("FILESTRING",AB_package);
    list_constant_130 = STATIC_CONS(Qfilestring,list_constant_41);
    list_constant_131 = STATIC_CONS(list_constant_130,Qnil);
    mutate_global_property(Qg2_file_exists,
	    make_system_rpc_1(Qg2_file_exists_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_exists,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_exists_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_exists_system_rpc_internal,NIL,FALSE,2,2));
    Qg2_type_of_file_system = STATIC_SYMBOL("G2-TYPE-OF-FILE-SYSTEM",
	    AB_package);
    Qg2_type_of_file_system_system_rpc_internal = 
	    STATIC_SYMBOL("G2-TYPE-OF-FILE-SYSTEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_type_of_file_system,
	    make_system_rpc_1(Qg2_type_of_file_system_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_57),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_type_of_file_system,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_type_of_file_system_system_rpc_internal,
	    STATIC_FUNCTION(g2_type_of_file_system_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_partition_filestring = STATIC_SYMBOL("G2-PARTITION-FILESTRING",
	    AB_package);
    Qg2_partition_filestring_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PARTITION-FILESTRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_132 = STATIC_LIST_STAR((SI_Long)6L,Qtext,Qtext,Qtext,
	    Qtext,Qtext,list_constant_40);
    mutate_global_property(Qg2_partition_filestring,
	    make_system_rpc_1(Qg2_partition_filestring_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_132),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_partition_filestring,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_partition_filestring_system_rpc_internal,
	    STATIC_FUNCTION(g2_partition_filestring_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_collect_into_filestring = 
	    STATIC_SYMBOL("G2-COLLECT-INTO-FILESTRING",AB_package);
    Qg2_collect_into_filestring_system_rpc_internal = 
	    STATIC_SYMBOL("G2-COLLECT-INTO-FILESTRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qhost = STATIC_SYMBOL("HOST",AB_package);
    list_constant_133 = STATIC_CONS(Qhost,list_constant_41);
    Qdevice = STATIC_SYMBOL("DEVICE",AB_package);
    list_constant_134 = STATIC_CONS(Qdevice,list_constant_41);
    Qab_directory = STATIC_SYMBOL("DIRECTORY",AB_package);
    list_constant_135 = STATIC_CONS(Qab_directory,list_constant_41);
    Qroot_name = STATIC_SYMBOL("ROOT-NAME",AB_package);
    list_constant_136 = STATIC_CONS(Qroot_name,list_constant_41);
    Qextension = STATIC_SYMBOL("EXTENSION",AB_package);
    list_constant_137 = STATIC_CONS(Qextension,list_constant_41);
    Qversion = STATIC_SYMBOL("VERSION",AB_package);
    list_constant_138 = STATIC_CONS(Qversion,list_constant_41);
    list_constant_139 = STATIC_LIST((SI_Long)6L,list_constant_133,
	    list_constant_134,list_constant_135,list_constant_136,
	    list_constant_137,list_constant_138);
    mutate_global_property(Qg2_collect_into_filestring,
	    make_system_rpc_1(Qg2_collect_into_filestring_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_139,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_collect_into_filestring,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_collect_into_filestring_system_rpc_internal,
	    STATIC_FUNCTION(g2_collect_into_filestring_system_rpc_internal,
	    NIL,FALSE,7,7));
    Qg2_file_version_string = STATIC_SYMBOL("G2-FILE-VERSION-STRING",
	    AB_package);
    Qg2_file_version_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-VERSION-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_version_string,
	    make_system_rpc_1(Qg2_file_version_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_version_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_version_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_version_string_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_file_extension_string = STATIC_SYMBOL("G2-FILE-EXTENSION-STRING",
	    AB_package);
    Qg2_file_extension_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-EXTENSION-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_extension_string,
	    make_system_rpc_1(Qg2_file_extension_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_extension_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_extension_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_extension_string_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_file_base_name_string = STATIC_SYMBOL("G2-FILE-BASE-NAME-STRING",
	    AB_package);
    Qg2_file_base_name_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-BASE-NAME-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_base_name_string,
	    make_system_rpc_1(Qg2_file_base_name_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_base_name_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_base_name_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_base_name_string_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_file_directory_list_to_string = 
	    STATIC_SYMBOL("G2-FILE-DIRECTORY-LIST-TO-STRING",AB_package);
    Qg2_file_directory_list_to_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-DIRECTORY-LIST-TO-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdirectory_list = STATIC_SYMBOL("DIRECTORY-LIST",AB_package);
    list_constant_140 = STATIC_LIST_STAR((SI_Long)3L,Qdirectory_list,Ktype,
	    list_constant_110);
    list_constant_141 = STATIC_CONS(list_constant_140,Qnil);
    mutate_global_property(Qg2_file_directory_list_to_string,
	    make_system_rpc_1(Qg2_file_directory_list_to_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_141,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_directory_list_to_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_directory_list_to_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_directory_list_to_string_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_file_directory_string_to_list = 
	    STATIC_SYMBOL("G2-FILE-DIRECTORY-STRING-TO-LIST",AB_package);
    Qg2_file_directory_string_to_list_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-DIRECTORY-STRING-TO-LIST-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_directory_string_to_list,
	    make_system_rpc_1(Qg2_file_directory_string_to_list_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_110),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_directory_string_to_list,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_directory_string_to_list_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_directory_string_to_list_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_file_directory_string = STATIC_SYMBOL("G2-FILE-DIRECTORY-STRING",
	    AB_package);
    Qg2_file_directory_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-DIRECTORY-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_directory_string,
	    make_system_rpc_1(Qg2_file_directory_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_directory_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_directory_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_directory_string_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_file_device_string = STATIC_SYMBOL("G2-FILE-DEVICE-STRING",AB_package);
    Qg2_file_device_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-DEVICE-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_device_string,
	    make_system_rpc_1(Qg2_file_device_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_device_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_device_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_device_string_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_file_host_string = STATIC_SYMBOL("G2-FILE-HOST-STRING",AB_package);
    Qg2_file_host_string_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FILE-HOST-STRING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_file_host_string,
	    make_system_rpc_1(Qg2_file_host_string_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_file_host_string,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_file_host_string_system_rpc_internal,
	    STATIC_FUNCTION(g2_file_host_string_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_delete_file = STATIC_SYMBOL("G2-DELETE-FILE",AB_package);
    Qg2_delete_file_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DELETE-FILE-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_delete_file,
	    make_system_rpc_1(Qg2_delete_file_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_131,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_delete_file,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_34 = STATIC_STRING("DELETE-FILE(~s) failed: ~s");
    SET_SYMBOL_FUNCTION(Qg2_delete_file_system_rpc_internal,
	    STATIC_FUNCTION(g2_delete_file_system_rpc_internal,NIL,FALSE,2,2));
    Qg2_rename_file = STATIC_SYMBOL("G2-RENAME-FILE",AB_package);
    Qg2_rename_file_system_rpc_internal = 
	    STATIC_SYMBOL("G2-RENAME-FILE-SYSTEM-RPC-INTERNAL",AB_package);
    Qold_filestring = STATIC_SYMBOL("OLD-FILESTRING",AB_package);
    list_constant_142 = STATIC_CONS(Qold_filestring,list_constant_41);
    Qnew_filestring = STATIC_SYMBOL("NEW-FILESTRING",AB_package);
    list_constant_143 = STATIC_CONS(Qnew_filestring,list_constant_41);
    list_constant_144 = STATIC_LIST((SI_Long)2L,list_constant_142,
	    list_constant_143);
    mutate_global_property(Qg2_rename_file,
	    make_system_rpc_1(Qg2_rename_file_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_144,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_rename_file,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_35 = STATIC_STRING("RENAME-FILE(~a,~a) failed: ~a");
    SET_SYMBOL_FUNCTION(Qg2_rename_file_system_rpc_internal,
	    STATIC_FUNCTION(g2_rename_file_system_rpc_internal,NIL,FALSE,3,3));
    Qg2_copy_file = STATIC_SYMBOL("G2-COPY-FILE",AB_package);
    Qg2_copy_file_system_rpc_internal = 
	    STATIC_SYMBOL("G2-COPY-FILE-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_copy_file,
	    make_system_rpc_1(Qg2_copy_file_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_144,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_copy_file,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_36 = STATIC_STRING("COPY-FILE(~a,~a) failed: ~a");
    SET_SYMBOL_FUNCTION(Qg2_copy_file_system_rpc_internal,
	    STATIC_FUNCTION(g2_copy_file_system_rpc_internal,NIL,FALSE,3,3));
    Qg2_enable_inlining = STATIC_SYMBOL("G2-ENABLE-INLINING",AB_package);
    Qg2_enable_inlining_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ENABLE-INLINING-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_enable_inlining,
	    make_system_rpc_1(Qg2_enable_inlining_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_enable_inlining,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_enable_inlining_system_rpc_internal,
	    STATIC_FUNCTION(g2_enable_inlining_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_disable_inlining = STATIC_SYMBOL("G2-DISABLE-INLINING",AB_package);
    Qg2_disable_inlining_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DISABLE-INLINING-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_disable_inlining,
	    make_system_rpc_1(Qg2_disable_inlining_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_disable_inlining,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_disable_inlining_system_rpc_internal,
	    STATIC_FUNCTION(g2_disable_inlining_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_item_is_editable = STATIC_SYMBOL("G2-ITEM-IS-EDITABLE",AB_package);
    Qg2_item_is_editable_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ITEM-IS-EDITABLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_145 = STATIC_LIST((SI_Long)3L,Qitem,Ktype,list_constant_30);
    list_constant_147 = STATIC_CONS(list_constant_145,Qnil);
    list_constant_146 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_7);
    list_constant_148 = STATIC_LIST((SI_Long)2L,Qtruth_value,
	    list_constant_146);
    mutate_global_property(Qg2_item_is_editable,
	    make_system_rpc_1(Qg2_item_is_editable_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_147,
	    Nil,T),list_constant_148),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_item_is_editable,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_item_is_editable_system_rpc_internal,
	    STATIC_FUNCTION(g2_item_is_editable_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_set_item_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ITEM-EXPLICITLY-EDITABLE",AB_package);
    Qg2_set_item_explicitly_editable_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-ITEM-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_set_item_explicitly_editable,
	    make_system_rpc_1(Qg2_set_item_explicitly_editable_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_147,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_item_explicitly_editable,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_item_explicitly_editable_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_item_explicitly_editable_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_set_item_and_all_its_subblocks_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ITEM-AND-ALL-ITS-SUBBLOCKS-EXPLICITLY-EDITABLE",
	    AB_package);
    Qg2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal 
	    = 
	    STATIC_SYMBOL("G2-SET-ITEM-AND-ALL-ITS-SUBBLOCKS-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_set_item_and_all_its_subblocks_explicitly_editable,
	    make_system_rpc_1(Qg2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_147,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_item_and_all_its_subblocks_explicitly_editable,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_item_and_all_its_subblocks_explicitly_editable_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_set_all_items_in_module_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ALL-ITEMS-IN-MODULE-EXPLICITLY-EDITABLE",
	    AB_package);
    Qg2_set_all_items_in_module_explicitly_editable_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-ALL-ITEMS-IN-MODULE-EXPLICITLY-EDITABLE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_set_all_items_in_module_explicitly_editable,
	    make_system_rpc_1(Qg2_set_all_items_in_module_explicitly_editable_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_147,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_all_items_in_module_explicitly_editable,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_all_items_in_module_explicitly_editable_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_all_items_in_module_explicitly_editable_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_modules_with_unsaved_changes = 
	    STATIC_SYMBOL("G2-MODULES-WITH-UNSAVED-CHANGES",AB_package);
    Qg2_modules_with_unsaved_changes_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MODULES-WITH-UNSAVED-CHANGES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_modules_with_unsaved_changes,
	    make_system_rpc_1(Qg2_modules_with_unsaved_changes_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_1),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_modules_with_unsaved_changes,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_modules_with_unsaved_changes_system_rpc_internal,
	    STATIC_FUNCTION(g2_modules_with_unsaved_changes_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_start_save_module = STATIC_SYMBOL("G2-START-SAVE-MODULE",AB_package);
    Qg2_start_save_module_system_rpc_internal = 
	    STATIC_SYMBOL("G2-START-SAVE-MODULE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qab_pathname = STATIC_SYMBOL("PATHNAME",AB_package);
    list_constant_150 = STATIC_CONS(Qab_pathname,list_constant_41);
    Qfile_progress_display = STATIC_SYMBOL("FILE-PROGRESS-DISPLAY",AB_package);
    list_constant_149 = STATIC_CONS(Ktype,list_constant_77);
    list_constant_151 = STATIC_CONS(Qfile_progress_display,list_constant_149);
    Qwindow_or_not = STATIC_SYMBOL("WINDOW-OR-NOT",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_152 = STATIC_LIST((SI_Long)3L,Qwindow_or_not,Ktype,
	    Qitem_or_datum);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    list_constant_153 = STATIC_CONS(Qmodule,list_constant_62);
    Qinclude_required_modules = STATIC_SYMBOL("INCLUDE-REQUIRED-MODULES",
	    AB_package);
    list_constant_154 = STATIC_CONS(Qinclude_required_modules,
	    list_constant_149);
    list_constant_155 = STATIC_LIST((SI_Long)5L,list_constant_150,
	    list_constant_151,list_constant_152,list_constant_153,
	    list_constant_154);
    list_constant_156 = STATIC_CONS(Qsymbol,list_constant_40);
    mutate_global_property(Qg2_start_save_module,
	    make_system_rpc_1(Qg2_start_save_module_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_155,
	    Nil,T),list_constant_156),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_start_save_module,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_start_save_module_system_rpc_internal,
	    STATIC_FUNCTION(g2_start_save_module_system_rpc_internal,NIL,
	    FALSE,6,6));
    Qg2_start_save_module_1 = STATIC_SYMBOL("G2-START-SAVE-MODULE-1",
	    AB_package);
    Qg2_start_save_module_1_system_rpc_internal = 
	    STATIC_SYMBOL("G2-START-SAVE-MODULE-1-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qusing_clear_text = STATIC_SYMBOL("USING-CLEAR-TEXT",AB_package);
    list_constant_157 = STATIC_CONS(Qusing_clear_text,list_constant_149);
    Qemitting_c_code = STATIC_SYMBOL("EMITTING-C-CODE",AB_package);
    list_constant_158 = STATIC_CONS(Qemitting_c_code,list_constant_149);
    Qlog_message_for_commit_after_saving = 
	    STATIC_SYMBOL("LOG-MESSAGE-FOR-COMMIT-AFTER-SAVING",AB_package);
    list_constant_159 = STATIC_CONS(Qlog_message_for_commit_after_saving,
	    list_constant_61);
    list_constant_160 = STATIC_LIST((SI_Long)8L,list_constant_150,
	    list_constant_151,list_constant_152,list_constant_153,
	    list_constant_154,list_constant_157,list_constant_158,
	    list_constant_159);
    mutate_global_property(Qg2_start_save_module_1,
	    make_system_rpc_1(Qg2_start_save_module_1_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_160,
	    Nil,T),list_constant_156),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_start_save_module_1,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_start_save_module_1_system_rpc_internal,
	    STATIC_FUNCTION(g2_start_save_module_1_system_rpc_internal,NIL,
	    FALSE,9,9));
    Qg2_start_save_kb = STATIC_SYMBOL("G2-START-SAVE-KB",AB_package);
    Qg2_start_save_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-START-SAVE-KB-SYSTEM-RPC-INTERNAL",AB_package);
    Qtype_of_file = STATIC_SYMBOL("TYPE-OF-FILE",AB_package);
    list_constant_162 = STATIC_CONS(Qtype_of_file,list_constant_62);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    list_constant_161 = STATIC_LIST((SI_Long)2L,Ktype,Qitem_or_datum);
    list_constant_163 = STATIC_CONS(Qwindow,list_constant_161);
    list_constant_164 = STATIC_LIST((SI_Long)4L,list_constant_150,
	    list_constant_162,list_constant_151,list_constant_163);
    mutate_global_property(Qg2_start_save_kb,
	    make_system_rpc_1(Qg2_start_save_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_164,
	    Nil,T),list_constant_156),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_start_save_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_start_save_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_start_save_kb_system_rpc_internal,NIL,FALSE,
	    5,5));
    Qg2_continue_save_kb = STATIC_SYMBOL("G2-CONTINUE-SAVE-KB",AB_package);
    Qg2_continue_save_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CONTINUE-SAVE-KB-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_165 = STATIC_CONS(list_constant_151,Qnil);
    mutate_global_property(Qg2_continue_save_kb,
	    make_system_rpc_1(Qg2_continue_save_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_165,
	    Nil,T),list_constant_156),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_continue_save_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_continue_save_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_continue_save_kb_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_finish_save_kb = STATIC_SYMBOL("G2-FINISH-SAVE-KB",AB_package);
    Qg2_finish_save_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FINISH-SAVE-KB-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_finish_save_kb,
	    make_system_rpc_1(Qg2_finish_save_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_165,
	    Nil,T),list_constant_156),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_finish_save_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_finish_save_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_finish_save_kb_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_abort_save_in_progress = STATIC_SYMBOL("G2-ABORT-SAVE-IN-PROGRESS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_abort_save_in_progress,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_abort_save_in_progress,
	    STATIC_FUNCTION(g2_abort_save_in_progress,NIL,FALSE,0,0));
    Qg2_abort_save_in_progress_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ABORT-SAVE-IN-PROGRESS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_abort_save_in_progress,
	    make_system_rpc_1(Qg2_abort_save_in_progress_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_abort_save_in_progress,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_abort_save_in_progress_system_rpc_internal,
	    STATIC_FUNCTION(g2_abort_save_in_progress_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_delete_module = STATIC_SYMBOL("G2-DELETE-MODULE",AB_package);
    Qg2_delete_module_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DELETE-MODULE-SYSTEM-RPC-INTERNAL",AB_package);
    Qalso_delete_associated_workspaces = 
	    STATIC_SYMBOL("ALSO-DELETE-ASSOCIATED-WORKSPACES",AB_package);
    list_constant_166 = STATIC_CONS(Qalso_delete_associated_workspaces,
	    list_constant_149);
    list_constant_167 = STATIC_LIST((SI_Long)2L,list_constant_153,
	    list_constant_166);
    mutate_global_property(Qg2_delete_module,
	    make_system_rpc_1(Qg2_delete_module_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_167,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_delete_module,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_delete_module_system_rpc_internal,
	    STATIC_FUNCTION(g2_delete_module_system_rpc_internal,NIL,FALSE,
	    3,3));
    Qg2_create_module = STATIC_SYMBOL("G2-CREATE-MODULE",AB_package);
    Qg2_create_module_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CREATE-MODULE-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_168 = STATIC_CONS(list_constant_153,Qnil);
    mutate_global_property(Qg2_create_module,
	    make_system_rpc_1(Qg2_create_module_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_168,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_create_module,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_create_module_system_rpc_internal,
	    STATIC_FUNCTION(g2_create_module_system_rpc_internal,NIL,FALSE,
	    2,2));
    Qg2_load_kb_1 = STATIC_SYMBOL("G2-LOAD-KB-1",AB_package);
    Qg2_load_kb_1_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LOAD-KB-1-SYSTEM-RPC-INTERNAL",AB_package);
    Qpath_name = STATIC_SYMBOL("PATH-NAME",AB_package);
    list_constant_169 = STATIC_CONS(Qpath_name,list_constant_41);
    Qresolve_conflicts_automatically = 
	    STATIC_SYMBOL("RESOLVE-CONFLICTS-AUTOMATICALLY",AB_package);
    list_constant_170 = STATIC_CONS(Qresolve_conflicts_automatically,
	    list_constant_149);
    Qbring_formats_up_to_date = STATIC_SYMBOL("BRING-FORMATS-UP-TO-DATE",
	    AB_package);
    list_constant_171 = STATIC_CONS(Qbring_formats_up_to_date,
	    list_constant_149);
    Qupdate_before_loading = STATIC_SYMBOL("UPDATE-BEFORE-LOADING",AB_package);
    list_constant_172 = STATIC_CONS(Qupdate_before_loading,list_constant_149);
    list_constant_173 = STATIC_LIST((SI_Long)4L,list_constant_169,
	    list_constant_170,list_constant_171,list_constant_172);
    mutate_global_property(Qg2_load_kb_1,
	    make_system_rpc_1(Qg2_load_kb_1_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_173,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_load_kb_1,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    Qinstall_system_tables = STATIC_SYMBOL("INSTALL-SYSTEM-TABLES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_load_kb_1_system_rpc_internal,
	    STATIC_FUNCTION(g2_load_kb_1_system_rpc_internal,NIL,FALSE,5,5));
    Qg2_load_kb = STATIC_SYMBOL("G2-LOAD-KB",AB_package);
    Qg2_load_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LOAD-KB-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_174 = STATIC_LIST((SI_Long)3L,list_constant_169,
	    list_constant_170,list_constant_171);
    mutate_global_property(Qg2_load_kb,
	    make_system_rpc_1(Qg2_load_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_174,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_load_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_load_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_load_kb_system_rpc_internal,NIL,FALSE,4,4));
    Qg2_merge_kb_1 = STATIC_SYMBOL("G2-MERGE-KB-1",AB_package);
    Qg2_merge_kb_1_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MERGE-KB-1-SYSTEM-RPC-INTERNAL",AB_package);
    Qpath_name_string = STATIC_SYMBOL("PATH-NAME-STRING",AB_package);
    list_constant_175 = STATIC_CONS(Qpath_name_string,list_constant_41);
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    list_constant_176 = STATIC_CONS(Qinstall_system_table,list_constant_149);
    list_constant_177 = STATIC_CONS(list_constant_172,Qnil);
    list_constant_178 = STATIC_LIST_STAR((SI_Long)5L,list_constant_175,
	    list_constant_170,list_constant_171,list_constant_176,
	    list_constant_177);
    mutate_global_property(Qg2_merge_kb_1,
	    make_system_rpc_1(Qg2_merge_kb_1_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_178,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_merge_kb_1,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_merge_kb_1_system_rpc_internal,
	    STATIC_FUNCTION(g2_merge_kb_1_system_rpc_internal,NIL,FALSE,6,6));
    Qg2_merge_kb = STATIC_SYMBOL("G2-MERGE-KB",AB_package);
    Qg2_merge_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MERGE-KB-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_179 = STATIC_LIST((SI_Long)4L,list_constant_175,
	    list_constant_170,list_constant_171,list_constant_176);
    mutate_global_property(Qg2_merge_kb,
	    make_system_rpc_1(Qg2_merge_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_179,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_merge_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_merge_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_merge_kb_system_rpc_internal,NIL,FALSE,5,5));
    Qg2_warmboot_kb = STATIC_SYMBOL("G2-WARMBOOT-KB",AB_package);
    Qg2_warmboot_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-WARMBOOT-KB-SYSTEM-RPC-INTERNAL",AB_package);
    Qrun_from_snapshot_time_as_fast_as_possible = 
	    STATIC_SYMBOL("RUN-FROM-SNAPSHOT-TIME-AS-FAST-AS-POSSIBLE",
	    AB_package);
    list_constant_180 = 
	    STATIC_CONS(Qrun_from_snapshot_time_as_fast_as_possible,
	    list_constant_149);
    list_constant_181 = STATIC_LIST((SI_Long)2L,list_constant_175,
	    list_constant_180);
    mutate_global_property(Qg2_warmboot_kb,
	    make_system_rpc_1(Qg2_warmboot_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_181,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_warmboot_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_warmboot_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_warmboot_kb_system_rpc_internal,NIL,FALSE,3,3));
    Qg2_load_runtime_data = STATIC_SYMBOL("G2-LOAD-RUNTIME-DATA",AB_package);
    Qg2_load_runtime_data_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LOAD-RUNTIME-DATA-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qoption = STATIC_SYMBOL("OPTION",AB_package);
    list_constant_182 = STATIC_LIST_STAR((SI_Long)3L,Qoption,Ktype,
	    list_constant_10);
    list_constant_183 = STATIC_LIST((SI_Long)2L,list_constant_175,
	    list_constant_182);
    mutate_global_property(Qg2_load_runtime_data,
	    make_system_rpc_1(Qg2_load_runtime_data_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_183,
	    Nil,T),list_constant_77),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_load_runtime_data,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_load_runtime_data_system_rpc_internal,
	    STATIC_FUNCTION(g2_load_runtime_data_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qg2_source_code_control_update = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-UPDATE",AB_package);
    Qscc_update = STATIC_SYMBOL("SCC-UPDATE",AB_package);
    Qg2_source_code_control_edit = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-EDIT",AB_package);
    Qscc_edit = STATIC_SYMBOL("SCC-EDIT",AB_package);
    Qg2_source_code_control_unedit = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-UNEDIT",AB_package);
    Qscc_unedit = STATIC_SYMBOL("SCC-UNEDIT",AB_package);
    Qg2_source_code_control_revert = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-REVERT",AB_package);
    Qscc_revert = STATIC_SYMBOL("SCC-REVERT",AB_package);
    Qg2_source_code_control_commit = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-COMMIT",AB_package);
    Qscc_commit = STATIC_SYMBOL("SCC-COMMIT",AB_package);
    string_constant_37 = STATIC_STRING("Error in ~A: ~A");
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_source_code_control_update,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_update,
	    STATIC_FUNCTION(g2_source_code_control_update,NIL,FALSE,1,1));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_source_code_control_edit,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_edit,
	    STATIC_FUNCTION(g2_source_code_control_edit,NIL,FALSE,1,1));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_source_code_control_unedit,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_unedit,
	    STATIC_FUNCTION(g2_source_code_control_unedit,NIL,FALSE,1,1));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_source_code_control_revert,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_revert,
	    STATIC_FUNCTION(g2_source_code_control_revert,NIL,FALSE,1,1));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_source_code_control_commit,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_commit,
	    STATIC_FUNCTION(g2_source_code_control_commit,NIL,FALSE,2,2));
    Qg2_source_code_control_update_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-UPDATE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_184 = STATIC_CONS(list_constant_169,Qnil);
    mutate_global_property(Qg2_source_code_control_update,
	    make_system_rpc_1(Qg2_source_code_control_update_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_184,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_source_code_control_update,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_update_system_rpc_internal,
	    STATIC_FUNCTION(g2_source_code_control_update_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_source_code_control_edit_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-EDIT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_source_code_control_edit,
	    make_system_rpc_1(Qg2_source_code_control_edit_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_184,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_source_code_control_edit,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_edit_system_rpc_internal,
	    STATIC_FUNCTION(g2_source_code_control_edit_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_source_code_control_unedit_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-UNEDIT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_source_code_control_unedit,
	    make_system_rpc_1(Qg2_source_code_control_unedit_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_184,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_source_code_control_unedit,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_unedit_system_rpc_internal,
	    STATIC_FUNCTION(g2_source_code_control_unedit_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_source_code_control_revert_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-REVERT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_source_code_control_revert,
	    make_system_rpc_1(Qg2_source_code_control_revert_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_184,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_source_code_control_revert,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_revert_system_rpc_internal,
	    STATIC_FUNCTION(g2_source_code_control_revert_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_source_code_control_commit_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SOURCE-CODE-CONTROL-COMMIT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qlog_message = STATIC_SYMBOL("LOG-MESSAGE",AB_package);
    list_constant_185 = STATIC_CONS(Qlog_message,list_constant_41);
    list_constant_186 = STATIC_LIST((SI_Long)2L,list_constant_169,
	    list_constant_185);
    mutate_global_property(Qg2_source_code_control_commit,
	    make_system_rpc_1(Qg2_source_code_control_commit_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_186,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_source_code_control_commit,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_source_code_control_commit_system_rpc_internal,
	    STATIC_FUNCTION(g2_source_code_control_commit_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_post_message = STATIC_SYMBOL("G2-POST-MESSAGE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_post_message,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_post_message,STATIC_FUNCTION(g2_post_message,
	    NIL,FALSE,2,2));
    Qg2_post_message_system_rpc_internal = 
	    STATIC_SYMBOL("G2-POST-MESSAGE-SYSTEM-RPC-INTERNAL",AB_package);
    Qsequence_of_values = STATIC_SYMBOL("SEQUENCE-OF-VALUES",AB_package);
    list_constant_187 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_1);
    list_constant_188 = STATIC_CONS(Qsequence_of_values,list_constant_187);
    Qduration_or_false = STATIC_SYMBOL("DURATION-OR-FALSE",AB_package);
    list_constant_189 = STATIC_LIST((SI_Long)3L,Qduration_or_false,Ktype,
	    Qvalue);
    list_constant_190 = STATIC_LIST((SI_Long)2L,list_constant_188,
	    list_constant_189);
    mutate_global_property(Qg2_post_message,
	    make_system_rpc_1(Qg2_post_message_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_190,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_post_message,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_post_message_system_rpc_internal,
	    STATIC_FUNCTION(g2_post_message_system_rpc_internal,NIL,FALSE,
	    3,3));
    Qg2_get_known_user_modes = STATIC_SYMBOL("G2-GET-KNOWN-USER-MODES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_known_user_modes,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qnon_built_in_g2_user_mode = STATIC_SYMBOL("NON-BUILT-IN-G2-USER-MODE",
	    AB_package);
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_known_user_modes,
	    STATIC_FUNCTION(g2_get_known_user_modes,NIL,FALSE,0,0));
    Qg2_get_known_user_modes_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-KNOWN-USER-MODES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_191 = STATIC_CONS(list_constant_1,Qnil);
    mutate_global_property(Qg2_get_known_user_modes,
	    make_system_rpc_1(Qg2_get_known_user_modes_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_191),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_known_user_modes,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_known_user_modes_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_known_user_modes_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_foreign_object = STATIC_SYMBOL("G2-FOREIGN-OBJECT",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_192 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qg2_foreign_object,
	    list_constant_192);
    string_constant_51 = STATIC_STRING("1o1m8v835Iy1l83-8y1l83Iy1l8t");
    string_constant_52 = 
	    STATIC_STRING("1l4z8r83GTy83GTy835Iy835Iy00001n1l8l1l83Uy1l83Hy00000");
    string_constant_53 = 
	    STATIC_STRING("1n8q1q835Iy1l83-Oy1m8v835Iy83-8y83Iy8t1p83GTy08l83Uy83Hy");
    temp_1 = regenerate_optimized_constant(string_constant_51);
    temp_2 = regenerate_optimized_constant(string_constant_52);
    add_class_to_environment(9,Qg2_foreign_object,list_constant_192,Nil,
	    temp_1,Nil,temp_2,list_constant_192,
	    regenerate_optimized_constant(string_constant_53),Nil);
    Qactive_stubs = STATIC_SYMBOL("ACTIVE-STUBS",AB_package);
    temp = CONS(Qactive_stubs,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_foreign_object),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qactive_stubs,temp_1);
    set_property_value_function(get_symbol_properties_function(Qg2_foreign_object),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_193 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_foreign_object);
    Qinitial_active_stubs = STATIC_SYMBOL("INITIAL-ACTIVE-STUBS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_active_stubs,
	    STATIC_FUNCTION(initial_active_stubs,NIL,FALSE,1,1));
    Qget_active_stubs = STATIC_SYMBOL("GET-ACTIVE-STUBS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_active_stubs,STATIC_FUNCTION(get_active_stubs,
	    NIL,FALSE,1,1));
    Qset_active_stubs = STATIC_SYMBOL("SET-ACTIVE-STUBS",AB_package);
    SET_SYMBOL_FUNCTION(Qset_active_stubs,STATIC_FUNCTION(set_active_stubs,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qactive_stubs,list_constant_193,list_constant_1,
	    Qnil,SYMBOL_FUNCTION(Qinitial_active_stubs),
	    SYMBOL_FUNCTION(Qget_active_stubs),
	    SYMBOL_FUNCTION(Qset_active_stubs));
    Qg2_java_bean = STATIC_SYMBOL("G2-JAVA-BEAN",AB_package);
    list_constant_194 = STATIC_CONS(Qg2_foreign_object,Qnil);
    check_if_superior_classes_are_defined(Qg2_java_bean,list_constant_194);
    string_constant_54 = STATIC_STRING("1n1m8v838Ty1l83Ly1l8t");
    string_constant_55 = 
	    STATIC_STRING("1m4z8r83N=y83N=y838Ty838Ty00001m1l8l1l83Cy000004z8r83Tgy83Tgy838Ty838Ty00001n1l8l1l83Cy1l83Uy00000");
    string_constant_56 = 
	    STATIC_STRING("1o8q1p838Ty1l835Iy1m8v838Ty83Ly8t1o83N=y08l83Cy1p83Tgy08l83Cy83Uy");
    temp_1 = regenerate_optimized_constant(string_constant_54);
    temp_2 = regenerate_optimized_constant(string_constant_55);
    add_class_to_environment(9,Qg2_java_bean,list_constant_194,Nil,temp_1,
	    Nil,temp_2,list_constant_194,
	    regenerate_optimized_constant(string_constant_56),Nil);
    Qlatent_listeners = STATIC_SYMBOL("LATENT-LISTENERS",AB_package);
    temp = CONS(Qlatent_listeners,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_java_bean),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qlatent_listeners,temp_1);
    set_property_value_function(get_symbol_properties_function(Qg2_java_bean),
	    Qvirtual_attributes_local_to_class,temp);
    list_constant_195 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_java_bean);
    Qinitial_latent_listeners = STATIC_SYMBOL("INITIAL-LATENT-LISTENERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_latent_listeners,
	    STATIC_FUNCTION(initial_latent_listeners,NIL,FALSE,1,1));
    Qget_latent_listeners = STATIC_SYMBOL("GET-LATENT-LISTENERS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_latent_listeners,
	    STATIC_FUNCTION(get_latent_listeners,NIL,FALSE,1,1));
    Qset_latent_listeners = STATIC_SYMBOL("SET-LATENT-LISTENERS",AB_package);
    SET_SYMBOL_FUNCTION(Qset_latent_listeners,
	    STATIC_FUNCTION(set_latent_listeners,NIL,FALSE,2,2));
    add_virtual_attribute(Qlatent_listeners,list_constant_195,
	    list_constant_76,Qnil,
	    SYMBOL_FUNCTION(Qinitial_latent_listeners),
	    SYMBOL_FUNCTION(Qget_latent_listeners),
	    SYMBOL_FUNCTION(Qset_latent_listeners));
    Qg2_java_bean_media_bin = STATIC_SYMBOL("G2-JAVA-BEAN-MEDIA-BIN",
	    AB_package);
    Qreclaim_g2_java_bean_media_bin_value = 
	    STATIC_SYMBOL("RECLAIM-G2-JAVA-BEAN-MEDIA-BIN-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_java_bean_media_bin_value,
	    STATIC_FUNCTION(reclaim_g2_java_bean_media_bin_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qg2_java_bean_media_bin,
	    SYMBOL_FUNCTION(Qreclaim_g2_java_bean_media_bin_value),
	    Qslot_value_reclaimer);
    Qinternal_media_bin = STATIC_SYMBOL("INTERNAL-MEDIA-BIN",AB_package);
    temp = CONS(Qinternal_media_bin,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qg2_java_bean),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qinternal_media_bin,temp_1);
    set_property_value_function(get_symbol_properties_function(Qg2_java_bean),
	    Qvirtual_attributes_local_to_class,temp);
    Qmedia_bin = STATIC_SYMBOL("MEDIA-BIN",AB_package);
    list_constant_196 = STATIC_LIST((SI_Long)2L,Qab_class,Qmedia_bin);
    list_constant_197 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_2,
	    list_constant_196);
    Qinitial_internal_media_bin = 
	    STATIC_SYMBOL("INITIAL-INTERNAL-MEDIA-BIN",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_internal_media_bin,
	    STATIC_FUNCTION(initial_internal_media_bin,NIL,FALSE,1,1));
    Qget_internal_media_bin = STATIC_SYMBOL("GET-INTERNAL-MEDIA-BIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_internal_media_bin,
	    STATIC_FUNCTION(get_internal_media_bin,NIL,FALSE,1,1));
    add_virtual_attribute(Qinternal_media_bin,list_constant_195,
	    list_constant_197,Qnil,
	    SYMBOL_FUNCTION(Qinitial_internal_media_bin),
	    SYMBOL_FUNCTION(Qget_internal_media_bin),Nil);
    Qg2_foreign_savable = STATIC_SYMBOL("G2-FOREIGN-SAVABLE",AB_package);
    list_constant_198 = STATIC_CONS(Qitem,Qnil);
    check_if_superior_classes_are_defined(Qg2_foreign_savable,
	    list_constant_198);
    string_constant_57 = STATIC_STRING("1o1m8v83Ry1l83Ly1l83-8y1l83Iy");
    string_constant_58 = STATIC_STRING("0");
    string_constant_59 = 
	    STATIC_STRING("1m8q1q83Mty1l83Ry1m8v83Ry83Ly83-8y83Iy");
    temp_1 = regenerate_optimized_constant(string_constant_57);
    temp_2 = regenerate_optimized_constant(string_constant_58);
    add_class_to_environment(9,Qg2_foreign_savable,list_constant_198,Nil,
	    temp_1,Nil,temp_2,list_constant_198,
	    regenerate_optimized_constant(string_constant_59),Nil);
    Qg2_foreign_serializable = STATIC_SYMBOL("G2-FOREIGN-SERIALIZABLE",
	    AB_package);
    list_constant_199 = STATIC_CONS(Qg2_foreign_savable,Qnil);
    check_if_superior_classes_are_defined(Qg2_foreign_serializable,
	    list_constant_199);
    string_constant_60 = 
	    STATIC_STRING("1m8q1q83xUy1l83Mty1m8v83Ry83Ly83-8y83Iy");
    temp_1 = regenerate_optimized_constant(string_constant_57);
    temp_2 = regenerate_optimized_constant(string_constant_58);
    add_class_to_environment(9,Qg2_foreign_serializable,list_constant_199,
	    Nil,temp_1,Nil,temp_2,list_constant_199,
	    regenerate_optimized_constant(string_constant_60),Nil);
    Qinitialize_for_g2_java_bean = 
	    STATIC_SYMBOL("INITIALIZE-FOR-G2-JAVA-BEAN",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_g2_java_bean,
	    STATIC_FUNCTION(initialize_for_g2_java_bean,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_for_g2_java_bean);
    set_get(Qg2_java_bean,Qinitialize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp = CONS(Qg2_java_bean,temp_1);
    mutate_global_property(Qinitialize,temp,Qclasses_which_define);
}
