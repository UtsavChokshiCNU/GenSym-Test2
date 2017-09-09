/* g2mtrs.c
 * Input file:  g2-meters.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2mtrs.h"


static Object Qg2_region_memory_allocatable;  /* g2-region-memory-allocatable */

static Object Qg2_region_memory_available;  /* g2-region-memory-available */

static Object Qg2_memory_allocatable;  /* g2-memory-allocatable */

static Object Qg2_memory_available;  /* g2-memory-available */

static Object Qg2_meter_name;      /* g2-meter-name */

/* PUT-G2-METER-NAME */
Object put_g2_meter_name(g2_meter_data_service,new_value,initializing_qm)
    Object g2_meter_data_service, new_value, initializing_qm;
{
    x_note_fn_call(245,0);
    if (initializing_qm && Loading_kb_p &&  !(IFIX(Kb_flags) >= 
	    (SI_Long)246L) && CONSP(new_value)) {
	if (EQ(M_CAR(new_value),Qg2_region_memory_allocatable))
	    M_CAR(new_value) = Qg2_region_memory_available;
	else if (EQ(M_CAR(new_value),Qg2_memory_allocatable))
	    M_CAR(new_value) = Qg2_memory_available;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_meter_data_service,Qg2_meter_name);
    return set_lookup_slot_value_1(g2_meter_data_service,Qg2_meter_name,
	    new_value);
}

/* INSTALL-G2-METER-NAMES-AND-FORMS */
Object install_g2_meter_names_and_forms(list_of_name_and_symbol_pairs)
    Object list_of_name_and_symbol_pairs;
{
    Object name_and_symbol, ab_loop_list_, push_arg;
    Object g2_meter_names_and_forms_new_value;

    x_note_fn_call(245,1);
    name_and_symbol = Nil;
    ab_loop_list_ = list_of_name_and_symbol_pairs;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name_and_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(member_eql(name_and_symbol,G2_meter_names_and_forms))) {
	push_arg = copy_tree(name_and_symbol);
	g2_meter_names_and_forms_new_value = CONS(push_arg,
		G2_meter_names_and_forms);
	G2_meter_names_and_forms = g2_meter_names_and_forms_new_value;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "none" */

/* WRITE-G2-METER-NAME-FROM-SLOT */
Object write_g2_meter_name_from_slot(meter_name,gensymed_symbol)
    Object meter_name, gensymed_symbol;
{
    Object name_and_symbol_pair, ab_loop_list_, temp;

    x_note_fn_call(245,2);
    if ( !TRUEP(meter_name))
	return twrite(string_constant);
    else {
	name_and_symbol_pair = Nil;
	ab_loop_list_ = G2_meter_names_and_forms;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name_and_symbol_pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = SECOND(name_and_symbol_pair);
	if (EQUAL(meter_name,temp)) {
	    twrite(FIRST(name_and_symbol_pair));
	    return VALUES_1(Nil);
	}
	goto next_loop;
      end_loop:
	twrite(meter_name);
	return VALUES_1(Qnil);
    }
}

static Object Qnone;               /* none */

static Object string_constant_1;   /* "The name ~a is not among the set of defined G2 meter names." */

/* COMPILE-G2-METER-NAME-FOR-SLOT */
Object compile_g2_meter_name_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object name_and_form_pair, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(245,3);
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
    else {
	name_and_form_pair = assq_function(parse_result,
		G2_meter_names_and_forms);
	if (name_and_form_pair) {
	    temp = SECOND(name_and_form_pair);
	    if (ATOM(temp))
		return VALUES_1(SECOND(name_and_form_pair));
	    else
		return copy_list_using_phrase_conses(SECOND(name_and_form_pair));
	}
	else {
	    temp_1 = Bad_phrase;
	    temp = tformat_text_string(2,string_constant_1,parse_result);
	    return VALUES_2(temp_1,temp);
	}
    }
}

static Object Qg2_meter_data_server;  /* g2-meter-data-server */

static Object Qg2_meter_data_service;  /* g2-meter-data-service */

static Object Qtext;               /* text */

static Object Qunknown_g2_meter_data_type;  /* unknown-g2-meter-data-type */

static Object string_constant_2;   /* "The variable ~NF ~A, ~A" */

static Object string_constant_3;   /* "attempted to get a value from G2 meter data service" */

static Object string_constant_4;   /* "but its class has not been declared to have that capability." */

static Object string_constant_5;   /* "The variable ~NF attempted to get a value from the G2 ~
				    *                               meter data service, but it had no G2 meter name ~
				    *                               specified."
				    */

static Object list_constant;       /* # */

static Object string_constant_6;   /* "The variable ~NF attempted to get a value for the ~
				    *                           simulator time lag, but the simulator is not on."
				    */

static Object string_constant_7;   /* "The variable ~NF attempted to get a value from the G2 ~
				    *                           meter data service, but the meter's function failed ~
				    *                           to return a value.  This is a G2 internal error!"
				    */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_8;   /* "The variable ~NF attempted to get a value from ~
				    *                             the G2 meter data service for the meter "
				    */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_9;   /* "[deleted attribute]" */

static Object string_constant_10;  /* ", but failed since this meter was not defined.  ~
				    * ???    This is a G2 internal error!"
				    */

static Object string_constant_11;  /* "The variable ~NF attempted to get a value from the G2 Meter Data Server~
				    * ? , but the G2 Meter Data Server was not turned on.  Change the G2 ~
				    *          meter data service on? attribute of the data-server-parameters system ~
				    *          table to enable data service to the variable."
				    */

/* COLLECT-ONE-SHOT-DATA-FOR-G2-METERS */
Object collect_one_shot_data_for_g2_meters(variable)
    Object variable;
{
    Object data_server, gensymed_symbol, sub_class_bit_vector, meter_form;
    Object temp_1, meter_value_qm, current_computation_frame;
    Object current_computation_instance, code, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(9);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(245,4);
    data_server = lookup_kb_specific_property_value(Qg2_meter_data_server,
	    Data_server_kbprop);
    if (ISVREF(data_server,(SI_Long)6L)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qg2_meter_data_service,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    meter_form = temp ? get_slot_value_function(variable,
		    Qg2_meter_name,Nil) : Nil;
	    if (meter_form) {
		if (CONSP(meter_form)) {
		    if (fboundp(M_CAR(meter_form))) {
			temp_1 = M_CAR(meter_form);
			meter_value_qm = APPLY_1(temp_1,M_CDR(meter_form));
		    }
		    else
			meter_value_qm = Nil;
		}
		else
		    meter_value_qm = BOUNDP(meter_form) ? 
			    SYMBOL_VALUE(meter_form) : Nil;
	    }
	    else
		meter_value_qm = Nil;
	    if (meter_value_qm) {
		current_computation_frame = variable;
		current_computation_instance = data_server;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  0);
		    if (NUMBERP(meter_value_qm))
			temp_1 = Qnumber;
		    else if (SYMBOLP(meter_value_qm))
			temp_1 = Qsymbol;
		    else if (text_string_p(meter_value_qm))
			temp_1 = Qtext;
		    else
			temp_1 = Qunknown_g2_meter_data_type;
		    put_current_value(5,variable,meter_value_qm,temp_1,Nil,
			    Nil);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qg2_meter_data_service,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(variable,
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(5,FIX((SI_Long)1L),
				string_constant_2,variable,
				string_constant_3,string_constant_4);
		    Suppress_warning_message_header_qm = Nil;
		}
		else if ( !TRUEP(meter_form)) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)3L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)3L),
				string_constant_5,variable);
		    Suppress_warning_message_header_qm = Nil;
		}
		else {
		    if (EQUAL(meter_form,list_constant)) {
			if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
			    code = M_CAR(M_CDR(Edit_type_alias_mapping));
			    temp = FIXNUMP(code) ? (IFIX(code) & 
				    (SI_Long)4096L) != (SI_Long)0L : 
				    TRUEP(Qnil);
			    if (temp);
			    else
				temp = 
					TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
			    temp =  !temp;
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)1L <= IFIX(Warning_message_level))
			    give_warning_1(3,FIX((SI_Long)1L),
				    string_constant_6,variable);
			Suppress_warning_message_header_qm = Nil;
		    }
		    else if (CONSP(meter_form)) {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)1L <= IFIX(Warning_message_level))
			    give_warning_1(3,FIX((SI_Long)1L),
				    string_constant_7,variable);
			Suppress_warning_message_header_qm = Nil;
		    }
		    else if ((SI_Long)1L <= IFIX(Warning_message_level) && 
			     !TRUEP(Debugging_reset)) {
			if ( !TRUEP(Defer_notifications_qm))
			    break_out_of_debug_messages();
			snapshots_of_related_blocks = Nil;
			note_blocks_in_tformat = 
				SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				8);
			  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				  7);
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    6);
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
				      5);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					4);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  3);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    2);
				      tformat(2,string_constant_8,variable);
				      slot_value_writer_qm = 
					      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qg2_meter_name),
					      Qslot_value_writer);
				      if (slot_value_writer_qm) {
					  write_symbols_in_lower_case_qm = T;
					  write_symbols_parsably_qm = T;
					  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
						  1);
					    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
						    0);
					      inline_funcall_2(slot_value_writer_qm,
						      meter_form,variable);
					    POP_SPECIAL();
					  POP_SPECIAL();
				      }
				      else
					  twrite(string_constant_9);
				      tformat(1,string_constant_10);
				      temp_1 = copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			    notify_user_1(temp_1);
			    if (Snapshots_of_related_blocks) {
				reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				Snapshots_of_related_blocks = Nil;
			    }
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		}
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_11,variable);
	Suppress_warning_message_header_qm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qcollect_one_shot_data_for_g2_meters;  /* collect-one-shot-data-for-g2-meters */

/* BEGIN-COLLECTING-DATA-FOR-G2-METERS */
Object begin_collecting_data_for_g2_meters(sensor,interval)
    Object sensor, interval;
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(245,5);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(sensor,(SI_Long)40L);
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
	aref_new_value = FIXNUMP(interval) ? (double)IFIX(interval) : 
		DFLOAT_ISAREF_1(interval,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qcollect_one_shot_data_for_g2_meters;
	temp = SYMBOL_FUNCTION(Qcollect_one_shot_data_for_g2_meters);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = sensor;
	new_1 = task;
	if (CAS_SVREF(sensor,(SI_Long)40L,old,new_1)) {
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
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* STOP-COLLECTING-DATA-FOR-G2-METERS */
Object stop_collecting_data_for_g2_meters(sensor)
    Object sensor;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(245,6);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(sensor,(SI_Long)40L);
    if (CAS_SVREF(sensor,(SI_Long)40L,gensymed_symbol,Nil)) {
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
	return VALUES_1(T);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ACCEPT-DATA-FROM-G2-METERS */
Object accept_data_from_g2_meters()
{
    x_note_fn_call(245,7);
    return VALUES_1(T);
}

static Object Qg2_meter_data_service_on_qm;  /* g2-meter-data-service-on? */

/* INITIALIZE-G2-METER-DATA-SERVER */
Object initialize_g2_meter_data_server()
{
    Object svref_arg_1;

    x_note_fn_call(245,8);
    if (get_lookup_slot_value_given_default(Data_server_parameters,
	    Qg2_meter_data_service_on_qm,Nil)) {
	reset_g2_meters();
	svref_arg_1 = 
		lookup_kb_specific_property_value(Qg2_meter_data_server,
		Data_server_kbprop);
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = T;
    }
    else {
	svref_arg_1 = 
		lookup_kb_specific_property_value(Qg2_meter_data_server,
		Data_server_kbprop);
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = Nil;
    }
    return VALUES_1(Nil);
}

static Object string_constant_12;  /* "An attempt was made to set the external value of the sensor ~NF, " */

static Object string_constant_13;  /* "which gets data service through the G2 meter server for the meter " */

static Object string_constant_14;  /* ", to the value " */

static Object string_constant_15;  /* ".  The set operation is not allowed within this data server." */

/* SET-EXTERNAL-VARIABLE-FOR-G2-METER */
Object set_external_variable_for_g2_meter(sensor,value,data_type)
    Object sensor, value, data_type;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(245,9);
    SAVE_STACK();
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  5);
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    4);
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
		      3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_12,sensor);
		      twrite(string_constant_13);
		      write_data_server_map_from_slot(get_slot_value_if_any_function(sensor,
			      Qg2_meter_name,Nil),sensor);
		      twrite(string_constant_14);
		      write_evaluation_value(1,value);
		      twrite(string_constant_15);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* SHUT-DOWN-G2-METER-DATA-SERVER */
Object shut_down_g2_meter_data_server()
{
    Object svref_arg_1;

    x_note_fn_call(245,10);
    svref_arg_1 = lookup_kb_specific_property_value(Qg2_meter_data_server,
	    Data_server_kbprop);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* MAKE-BOXED-FLOATING-ZERO */
Object make_boxed_floating_zero()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(245,11);
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    return VALUES_1(new_float);
}

DEFINE_VARIABLE_WITH_SYMBOL(Percent_running, Qpercent_running);

/* PERCENT-RUNNING */
Object percent_running()
{
    x_note_fn_call(245,12);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Percent_running) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Percent_running)) == (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Percent_running,
		(SI_Long)0L)));
    else if (INLINE_LONG_VECTOR_P(Percent_running) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Percent_running)) == (SI_Long)1L)
	return aref1(Percent_running,FIX((SI_Long)0L));
    else
	return VALUES_1(Percent_running);
}

DEFINE_VARIABLE_WITH_SYMBOL(Metered_clock_tick_length, Qmetered_clock_tick_length);

/* METERED-CLOCK-TICK-LENGTH */
Object metered_clock_tick_length()
{
    x_note_fn_call(245,13);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Metered_clock_tick_length,
	    (SI_Long)0L)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_clock_tick_length, Qmaximum_clock_tick_length);

/* MAXIMUM-CLOCK-TICK-LENGTH */
Object maximum_clock_tick_length()
{
    x_note_fn_call(245,14);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Maximum_clock_tick_length) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_clock_tick_length)) == 
	    (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Maximum_clock_tick_length,
		(SI_Long)0L)));
    else if (INLINE_LONG_VECTOR_P(Maximum_clock_tick_length) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_clock_tick_length)) == 
	    (SI_Long)1L)
	return aref1(Maximum_clock_tick_length,FIX((SI_Long)0L));
    else
	return VALUES_1(Maximum_clock_tick_length);
}

static Object float_constant;      /* 0.0 */

/* RESET-G2-METERS */
Object reset_g2_meters()
{
    Object temp;

    x_note_fn_call(245,15);
    temp = store_managed_number_function(Maximum_clock_tick_length,
	    float_constant);
    Maximum_clock_tick_length = temp;
    Fixnum_time_units_of_sleep_this_clock_tick = FIX((SI_Long)0L);
    temp = store_managed_number_function(Percent_running,float_constant);
    Percent_running = temp;
    temp = Metered_clock_tick_length;
    DFLOAT_ISASET_1(temp,(SI_Long)0L,1.0);
    reset_all_scheduler_lag_time_variables();
    return VALUES_1(Nil);
}

static Object float_constant_1;    /* 1.0 */

/* UPDATE-METER-VALUES */
Object update_meter_values(fixnum_time_length_of_previous_tick_init)
    Object fixnum_time_length_of_previous_tick_init;
{
    Object meter_lag_time, tmp_float, temp, temp_1, gensymed_symbol_1;
    SI_Long fixnum_time_length_of_previous_tick, wait_period, incff_1_arg;
    SI_Long fixnum_time_units_of_sleep_this_clock_tick_new_value;
    double float_tick_length, float_tick_length_in_seconds, arg, arg_1;
    double store_managed_number_arg, aref_new_value, gensymed_symbol, temp_2;
    double beta, one_minus_beta, percent_running_calc;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(245,16);
    fixnum_time_length_of_previous_tick = 
	    IFIX(fixnum_time_length_of_previous_tick_init);
    if (fixnum_time_length_of_previous_tick != (SI_Long)0L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    meter_lag_time = ISVREF(Timing_parameters,(SI_Long)24L);
	    float_tick_length = (double)fixnum_time_length_of_previous_tick;
	    float_tick_length_in_seconds = float_tick_length / 
		    (double)IFIX(Fixnum_time_units_per_second);
	    tmp_float = float_constant;
	    arg = float_tick_length_in_seconds;
	    temp = normalize_to_gensym_float(Maximum_clock_tick_length);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		store_managed_number_arg = float_tick_length_in_seconds;
		temp_1 = 
			store_managed_number_function(Maximum_clock_tick_length,
			DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		Maximum_clock_tick_length = temp_1;
	    }
	    if (Record_fixnum_time_units_of_sleep_this_clock_tick_qm) {
		wait_period = g2ext_get_waited_period();
		incff_1_arg = wait_period;
		fixnum_time_units_of_sleep_this_clock_tick_new_value = 
			IFIX(Fixnum_time_units_of_sleep_this_clock_tick) + 
			incff_1_arg;
		Fixnum_time_units_of_sleep_this_clock_tick = 
			FIX(fixnum_time_units_of_sleep_this_clock_tick_new_value);
		g2ext_reset_waited_period();
	    }
	    tmp_float = 
		    DOUBLE_TO_DOUBLE_FLOAT((double)
		    (fixnum_time_length_of_previous_tick - 
		    IFIX(Fixnum_time_units_of_sleep_this_clock_tick)) / 
		    float_tick_length * 100.0);
	    if (IFIX(meter_lag_time) == (SI_Long)0L) {
		temp_1 = Percent_running;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(tmp_float);
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		Fixnum_time_units_of_sleep_this_clock_tick = FIX((SI_Long)0L);
		temp_1 = Metered_clock_tick_length;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
			float_tick_length_in_seconds);
		result = VALUES_1(Nil);
	    }
	    else {
		gensymed_symbol = float_tick_length_in_seconds / 
			(double)IFIX(meter_lag_time);
		gensymed_symbol_1 = float_constant_1;
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
		beta = MIN(gensymed_symbol,temp_2);
		one_minus_beta = 1.0 - beta;
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(tmp_float);
		percent_running_calc = DFLOAT_ISAREF_1(Percent_running,
			(SI_Long)0L) * one_minus_beta + temp_2 * beta;
		temp_1 = Percent_running;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,percent_running_calc);
		Fixnum_time_units_of_sleep_this_clock_tick = FIX((SI_Long)0L);
		temp_1 = Metered_clock_tick_length;
		aref_new_value = DFLOAT_ISAREF_1(Metered_clock_tick_length,
			(SI_Long)0L) * one_minus_beta + 
			float_tick_length_in_seconds * beta;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		result = VALUES_1(Nil);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_16;  /* "G2 Run Time Statistics" */

static Object string_constant_17;  /* "G2 " */

/* WRITE-G2-STATS-HEADER */
Object write_g2_stats_header(output)
    Object output;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object description, second_1, minute, hour, date, month, year, time_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(245,17);
    g2_stream_write_line(string_constant_16,output);
    g2_stream_terpri(output);
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
	      twrite_system_version(1,Current_system_version);
	      description = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    g2_stream_write_string(string_constant_17,output);
    g2_stream_write_line(description,output);
    reclaim_text_string(description);
    result = get_decoded_real_time();
    MVS_6(result,second_1,minute,hour,date,month,year);
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
	      print_decoded_time(second_1,minute,hour,date,month,year);
	      time_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    g2_stream_write_line(time_1,output);
    return reclaim_text_string(time_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_uo_memory_usage_information_hash_vector_43_vectors, Qavailable_uo_memory_usage_information_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_uo_memory_usage_information_hash_vector_43_vectors, Qcount_of_uo_memory_usage_information_hash_vector_43_vectors);

Object Available_uo_memory_usage_information_hash_vector_43_vectors_vector = UNBOUND;

/* UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object uo_memory_usage_information_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(245,18);
    temp = Count_of_uo_memory_usage_information_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTORS */
Object out_uo_memory_usage_information_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(245,19);
    temp = 
	    FIXNUM_MINUS(Count_of_uo_memory_usage_information_hash_vector_43_vectors,
	    length(Available_uo_memory_usage_information_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_uo_memory_usage_information_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(245,20);
    atomic_incff_symval(Qcount_of_uo_memory_usage_information_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR */
Object make_uo_memory_usage_information_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(245,21);
    if (ISVREF(Available_uo_memory_usage_information_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_uo_memory_usage_information_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_uo_memory_usage_information_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_uo_memory_usage_information_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_uo_memory_usage_information_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_uo_memory_usage_information_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR */
Object reclaim_uo_memory_usage_information_hash_vector(uo_memory_usage_information_hash_vector_43_vector)
    Object uo_memory_usage_information_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(245,22);
    svref_arg_1 = 
	    Available_uo_memory_usage_information_hash_vector_43_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = uo_memory_usage_information_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_uo_memory_usage_information_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qlookup;             /* lookup */

/* RECLAIM-UO-MEMORY-USAGE-INFORMATION-TREE-FOR-HASH-LEAVES */
Object reclaim_uo_memory_usage_information_tree_for_hash_leaves(uo_memory_usage_information_tree_for_hash_binary_tree)
    Object uo_memory_usage_information_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(245,23);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(uo_memory_usage_information_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(uo_memory_usage_information_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(uo_memory_usage_information_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(uo_memory_usage_information_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    reclaim_binary_tree_element_1(uo_memory_usage_information_tree_for_hash_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    M_CDR(alist_entry) = Nil;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_uo_memory_usage_information_tree_for_hash_leaves(less_than_branch_qm);
	uo_memory_usage_information_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	uo_memory_usage_information_tree_for_hash_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-UO-MEMORY-USAGE-INFORMATION-TREE */
Object clear_uo_memory_usage_information_tree(uo_memory_usage_information_tree_for_hash_binary_tree)
    Object uo_memory_usage_information_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(245,24);
    element_qm = CDR(uo_memory_usage_information_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_uo_memory_usage_information_tree_for_hash_leaves(element_qm);
	M_CDR(uo_memory_usage_information_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(uo_memory_usage_information_tree_for_hash_binary_tree);
}

static Object Quo_memory_usage_information_tree_for_hash;  /* uo-memory-usage-information-tree-for-hash */

/* MAKE-UO-MEMORY-USAGE-INFORMATION */
Object make_uo_memory_usage_information()
{
    Object new_vector, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(245,25);
    new_vector = make_uo_memory_usage_information_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Quo_memory_usage_information_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Uo_memory_usage_information_hash_table, Quo_memory_usage_information_hash_table);

/* FLATTEN-UO-MEMORY-USAGE-INFORMATION */
Object flatten_uo_memory_usage_information(uo_memory_usage_information_hash_table)
    Object uo_memory_usage_information_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(245,26);
    PUSH_SPECIAL_WITH_SYMBOL(Uo_memory_usage_information_hash_table,Quo_memory_usage_information_hash_table,uo_memory_usage_information_hash_table,
	    0);
      result_1 = Nil;
      index_1 = (SI_Long)0L;
    next_loop:
      if (index_1 >= (SI_Long)43L)
	  goto end_loop;
      subtree = ISVREF(Uo_memory_usage_information_hash_table,index_1);
      if (subtree) {
	  temp = flatten_binary_tree(CDR(subtree));
	  result_1 = nconc2(temp,result_1);
      }
      index_1 = index_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      result = VALUES_1(result_1);
    POP_SPECIAL();
    return result;
}

/* CLEAR-UO-MEMORY-USAGE-INFORMATION */
Object clear_uo_memory_usage_information(uo_memory_usage_information_hash_table)
    Object uo_memory_usage_information_hash_table;
{
    SI_Long index_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(245,27);
    PUSH_SPECIAL_WITH_SYMBOL(Uo_memory_usage_information_hash_table,Quo_memory_usage_information_hash_table,uo_memory_usage_information_hash_table,
	    0);
      index_1 = (SI_Long)0L;
    next_loop:
      if (index_1 >= (SI_Long)43L)
	  goto end_loop;
      clear_uo_memory_usage_information_tree(ISVREF(Uo_memory_usage_information_hash_table,
	      index_1));
      index_1 = index_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-UO-MEMORY-USAGE-INFORMATION */
Object reclaim_uo_memory_usage_information(uo_memory_usage_information_hash_table)
    Object uo_memory_usage_information_hash_table;
{
    Object uo_memory_usage_information_tree_for_hash_binary_tree, element_qm;
    Object temp, svref_arg_2, temp_1;
    SI_Long index_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(245,28);
    PUSH_SPECIAL_WITH_SYMBOL(Uo_memory_usage_information_hash_table,Quo_memory_usage_information_hash_table,uo_memory_usage_information_hash_table,
	    0);
      index_1 = (SI_Long)0L;
    next_loop:
      if (index_1 >= (SI_Long)43L)
	  goto end_loop;
      uo_memory_usage_information_tree_for_hash_binary_tree = 
	      ISVREF(Uo_memory_usage_information_hash_table,index_1);
      element_qm = 
	      M_CDR(uo_memory_usage_information_tree_for_hash_binary_tree);
      if (element_qm)
	  reclaim_uo_memory_usage_information_tree_for_hash_leaves(element_qm);
      inline_note_reclaim_cons(uo_memory_usage_information_tree_for_hash_binary_tree,
	      Qlookup);
      if (ISVREF(Available_lookup_conses_tail_vector,
	      IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_lookup_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = uo_memory_usage_information_tree_for_hash_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = 
		  uo_memory_usage_information_tree_for_hash_binary_tree;
      }
      else {
	  temp = Available_lookup_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = 
		  uo_memory_usage_information_tree_for_hash_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = 
		  uo_memory_usage_information_tree_for_hash_binary_tree;
      }
      M_CDR(uo_memory_usage_information_tree_for_hash_binary_tree) = Nil;
      temp = Uo_memory_usage_information_hash_table;
      ISVREF(temp,index_1) = Nil;
      index_1 = index_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      temp_1 = 
	      reclaim_uo_memory_usage_information_hash_vector(Uo_memory_usage_information_hash_table);
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_class_instances_memory_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_class_instances_memory_infos, Qchain_of_available_class_instances_memory_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Class_instances_memory_info_count, Qclass_instances_memory_info_count);

Object Chain_of_available_class_instances_memory_infos_vector = UNBOUND;

/* CLASS-INSTANCES-MEMORY-INFO-STRUCTURE-MEMORY-USAGE */
Object class_instances_memory_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(245,29);
    temp = Class_instances_memory_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-INSTANCES-MEMORY-INFO-COUNT */
Object outstanding_class_instances_memory_info_count()
{
    Object def_structure_class_instances_memory_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(245,30);
    gensymed_symbol = IFIX(Class_instances_memory_info_count);
    def_structure_class_instances_memory_info_variable = 
	    Chain_of_available_class_instances_memory_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_class_instances_memory_info_variable))
	goto end_loop;
    def_structure_class_instances_memory_info_variable = 
	    ISVREF(def_structure_class_instances_memory_info_variable,
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

/* RECLAIM-CLASS-INSTANCES-MEMORY-INFO-1 */
Object reclaim_class_instances_memory_info_1(class_instances_memory_info)
    Object class_instances_memory_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(245,31);
    inline_note_reclaim_cons(class_instances_memory_info,Nil);
    temp = ISVREF(Chain_of_available_class_instances_memory_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(class_instances_memory_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_class_instances_memory_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = class_instances_memory_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-INSTANCES-MEMORY-INFO */
Object reclaim_structure_for_class_instances_memory_info(class_instances_memory_info)
    Object class_instances_memory_info;
{
    x_note_fn_call(245,32);
    return reclaim_class_instances_memory_info_1(class_instances_memory_info);
}

static Object Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct;  /* g2-defstruct-structure-name::class-instances-memory-info-g2-struct */

/* MAKE-PERMANENT-CLASS-INSTANCES-MEMORY-INFO-STRUCTURE-INTERNAL */
Object make_permanent_class_instances_memory_info_structure_internal()
{
    Object def_structure_class_instances_memory_info_variable;
    Object defstruct_g2_class_instances_memory_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(245,33);
    def_structure_class_instances_memory_info_variable = Nil;
    atomic_incff_symval(Qclass_instances_memory_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_class_instances_memory_info_variable = Nil;
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
	defstruct_g2_class_instances_memory_info_variable = the_array;
	SVREF(defstruct_g2_class_instances_memory_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct;
	def_structure_class_instances_memory_info_variable = 
		defstruct_g2_class_instances_memory_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_class_instances_memory_info_variable);
}

/* MAKE-CLASS-INSTANCES-MEMORY-INFO-1 */
Object make_class_instances_memory_info_1()
{
    Object def_structure_class_instances_memory_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(245,34);
    def_structure_class_instances_memory_info_variable = 
	    ISVREF(Chain_of_available_class_instances_memory_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_class_instances_memory_info_variable) {
	svref_arg_1 = Chain_of_available_class_instances_memory_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_class_instances_memory_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_class_instances_memory_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct;
    }
    else
	def_structure_class_instances_memory_info_variable = 
		make_permanent_class_instances_memory_info_structure_internal();
    inline_note_allocate_cons(def_structure_class_instances_memory_info_variable,
	    Nil);
    return VALUES_1(def_structure_class_instances_memory_info_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Class_name_max_length, Qclass_name_max_length);

static Object Qitem;               /* item */

/* COLLECT-USER-OBJECTS-MEMORY-CONSUMPTION-DATA */
Object collect_user_objects_memory_consumption_data()
{
    Object instances_memory, instances_number, memory_usage_info, tmp;
    Object scope_conses, ab_loopvar_, class_1, temp, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_4, svref_new_value;
    Object ab_loopvar__1, ab_loopvar__2, instance, incff_1_arg;
    Object wide_string_bv16;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3, length_1;
    char temp_2;
    Declare_special(2);

    x_note_fn_call(245,35);
    instances_memory = FIX((SI_Long)0L);
    instances_number = FIX((SI_Long)0L);
    memory_usage_info = Nil;
    tmp = FIX((SI_Long)0L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qitem;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      instances_memory = FIX((SI_Long)0L);
      gensymed_symbol = IFIX(sxhashw(class_1));
      temp = Uo_memory_usage_information_hash_table;
      temp_1 = gensymed_symbol % (SI_Long)43L;
      temp = SVREF(temp,FIX(temp_1));
      gensymed_symbol_1 = CDR(temp);
      gensymed_symbol_2 = class_1;
      gensymed_symbol_3 = (SI_Long)0L;
    next_loop_1:
      if ( !TRUEP(gensymed_symbol_1))
	  goto end_loop_1;
      gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
      if (gensymed_symbol < gensymed_symbol_3)
	  gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
      else if (gensymed_symbol > gensymed_symbol_3)
	  gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
      else {
	  gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	  gensymed_symbol_4 = Nil;
	next_loop_2:
	  if ( !TRUEP(gensymed_symbol_1))
	      goto end_loop_2;
	  gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	  if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
	      memory_usage_info = M_CDR(M_CAR(gensymed_symbol_1));
	      goto end_1;
	  }
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  goto next_loop_2;
	end_loop_2:
	  memory_usage_info = Qnil;
	end_1:;
	  goto end_2;
      }
      goto next_loop_1;
    end_loop_1:
      memory_usage_info = Qnil;
    end_2:;
      if ( !TRUEP(memory_usage_info)) {
	  memory_usage_info = make_class_instances_memory_info_1();
	  svref_new_value = stringw(class_1);
	  SVREF(memory_usage_info,FIX((SI_Long)1L)) = svref_new_value;
      }
      scope_conses = Scope_conses;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      instance = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar__1 = collect_subclasses(class_1);
      next_loop_3:
	if ( !TRUEP(ab_loopvar__2)) {
	  next_loop_4:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop_3;
	    ab_loopvar__2 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar__1),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar__1 = M_CDR(ab_loopvar__1);
	    if (ab_loopvar__2)
		goto end_loop_3;
	    goto next_loop_4;
	  end_loop_3:
	    temp_2 =  !TRUEP(ab_loopvar__2);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    goto end_loop_4;
	instance = ab_loopvar__2;
	ab_loopvar__2 = ISVREF(ab_loopvar__2,(SI_Long)6L);
	incff_1_arg = g2_measure_memory_lisp_side(instance);
	instances_memory = FIXNUM_ADD(instances_memory,incff_1_arg);
	instances_number = FIXNUM_ADD1(instances_number);
	goto next_loop_3;
      end_loop_4:;
      POP_SPECIAL();
      wide_string_bv16 = ISVREF(memory_usage_info,(SI_Long)1L);
      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      tmp = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - (SI_Long)2L) 
	      + ((UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
	      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
      if (FIXNUM_GT(tmp,Class_name_max_length))
	  Class_name_max_length = tmp;
      tmp = ISVREF(memory_usage_info,(SI_Long)3L);
      SVREF(memory_usage_info,FIX((SI_Long)3L)) = instances_memory;
      svref_new_value =  !TRUEP(tmp) ? instances_memory : 
	      FIXNUM_MINUS(instances_memory,tmp);
      SVREF(memory_usage_info,FIX((SI_Long)4L)) = svref_new_value;
      tmp = ISVREF(memory_usage_info,(SI_Long)2L);
      svref_new_value =  !TRUEP(tmp) ? instances_number : 
	      FIXNUM_MINUS(instances_number,tmp);
      SVREF(memory_usage_info,FIX((SI_Long)5L)) = svref_new_value;
      SVREF(memory_usage_info,FIX((SI_Long)2L)) = instances_number;
      instances_number = FIX((SI_Long)0L);
      gensymed_symbol = IFIX(sxhashw(class_1));
      temp = Uo_memory_usage_information_hash_table;
      temp_1 = gensymed_symbol % (SI_Long)43L;
      set_balanced_binary_tree_entry(SVREF(temp,FIX(temp_1)),Qeq,Nil,T,
	      class_1,FIX(gensymed_symbol),memory_usage_info);
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(Class_name_max_length);
}

Object Class_name_column_title = UNBOUND;

Object Instances_count_column_title = UNBOUND;

Object Delta_instances_column_title = UNBOUND;

Object Consumed_memory_column_title = UNBOUND;

Object Delta_memory_column_title = UNBOUND;

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* WRITE-USER-OBJECTS-MEMORY-USAGE */
Object write_user_objects_memory_usage(output)
    Object output;
{
    Object len, len_diff, number_string, final_string_to_write;
    Object class_name_max_length, class_name_max_length_new_value;
    Object scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, memory_usage_info;
    Object ab_less_than_branch_qm_, gensymed_symbol_2, temp, wide_string_bv16;
    SI_Long length_1, instances_count_column_title_len;
    SI_Long delta_instances_column_title_len, consumed_memory_column_title_len;
    SI_Long gensymed_symbol, gensymed_symbol_1, ab_table_length_, ab_index_;
    SI_Long temp_2, tmpf, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(245,36);
    len = FIX((SI_Long)0L);
    len_diff = FIX((SI_Long)0L);
    number_string = Nil;
    final_string_to_write = Nil;
    class_name_max_length = FIX((SI_Long)0L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Instances_count_column_title));
    instances_count_column_title_len = 
	    UBYTE_16_ISAREF_1(Instances_count_column_title,length_1 - 
	    (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(Instances_count_column_title,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Delta_instances_column_title));
    delta_instances_column_title_len = 
	    UBYTE_16_ISAREF_1(Delta_instances_column_title,length_1 - 
	    (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(Delta_instances_column_title,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Consumed_memory_column_title));
    consumed_memory_column_title_len = 
	    UBYTE_16_ISAREF_1(Consumed_memory_column_title,length_1 - 
	    (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(Consumed_memory_column_title,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    PUSH_SPECIAL_WITH_SYMBOL(Class_name_max_length,Qclass_name_max_length,class_name_max_length,
	    1);
      if (ISVREF(Miscellaneous_parameters,(SI_Long)34L)) {
	  Class_name_max_length = 
		  collect_user_objects_memory_consumption_data();
	  class_name_max_length_new_value = 
		  FIXNUM_ADD(Class_name_max_length,Spaces_between_columns);
	  Class_name_max_length = class_name_max_length_new_value;
	  g2_stream_write_line(array_constant,output);
	  g2_stream_write_line(array_constant_1,output);
	  g2_stream_write_line(array_constant_1,output);
	  gensymed_symbol = IFIX(Class_name_max_length);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Class_name_column_title));
	  gensymed_symbol_1 = UBYTE_16_ISAREF_1(Class_name_column_title,
		  length_1 - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(Class_name_column_title,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	  len_diff = FIX(gensymed_symbol - gensymed_symbol_1);
	  final_string_to_write = 
		  add_text_to_string_with_align(Class_name_column_title,
		  Instances_count_column_title,len_diff,Nil,Nil);
	  final_string_to_write = 
		  add_text_to_string_with_align(final_string_to_write,
		  Delta_instances_column_title,Spaces_between_columns,T,Nil);
	  final_string_to_write = 
		  add_text_to_string_with_align(final_string_to_write,
		  Consumed_memory_column_title,Spaces_between_columns,T,Nil);
	  final_string_to_write = 
		  add_text_to_string_with_align(final_string_to_write,
		  Delta_memory_column_title,Spaces_between_columns,T,Nil);
	  g2_stream_write_line(final_string_to_write,output);
	  g2_stream_write_line(array_constant_1,output);
	  scope_conses = Scope_conses;
	  ab_hash_table_ = Uo_memory_usage_information_hash_table;
	  ab_table_length_ = (SI_Long)0L;
	  ab_index_ = (SI_Long)0L;
	  ab_tree_form_ = Nil;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_skip_list_p_ = Nil;
	  ab_tail_node_ = Nil;
	  memory_usage_info = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	  next_loop:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_current_node_ && ab_skip_list_p_) {
		ab_current_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			(SI_Long)0L),(SI_Long)0L));
		if (EQ(ab_current_node_,ab_tail_node_))
		    ab_current_node_ = Nil;
		else
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	    }
	    else if (ab_current_node_) {
		ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		if (ab_current_node_) {
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_1:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_1;
		  end_loop:;
		}
		else if (ab_node_stack_) {
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		if (ab_current_node_) {
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_)) {
	      next_loop_2:
		if ( !(ab_index_ < ab_table_length_))
		    goto end_loop_1;
		ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		if (ab_index_ == (SI_Long)0L) {
		    gensymed_symbol_2 = CDR(ab_tree_form_);
		    if (CONSP(gensymed_symbol_2)) {
			temp = M_CAR(gensymed_symbol_2);
			temp_1 = SIMPLE_VECTOR_P(temp);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			temp = M_CDR(gensymed_symbol_2);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		}
		ab_index_ = ab_index_ + (SI_Long)1L;
		if (ab_skip_list_p_) {
		    ab_current_node_ = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_tree_form_)),
			    (SI_Long)0L),(SI_Long)0L));
		    ab_tail_node_ = M_CDR(M_CDR(ab_tree_form_));
		    if (EQ(ab_current_node_,ab_tail_node_))
			ab_current_node_ = Nil;
		    else {
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
				(SI_Long)2L),ISVREF(ab_current_node_,
				(SI_Long)3L));
			goto end_loop_1;
		    }
		}
		else {
		    ab_current_node_ = CDR(ab_tree_form_);
		    if (ab_current_node_) {
			ab_less_than_branch_qm_ = Nil;
		      next_loop_3:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_2;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_3;
		      end_loop_2:;
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
			goto end_loop_1;
		    }
		}
		goto next_loop_2;
	      end_loop_1:;
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    memory_usage_info = M_CDR(ab_entry_cons_);
	    wide_string_bv16 = ISVREF(memory_usage_info,(SI_Long)1L);
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    len = FIX(UBYTE_16_ISAREF_1(wide_string_bv16,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string_bv16,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    len_diff = FIXNUM_MINUS(Class_name_max_length,len);
	    gensymed_symbol = IFIX(ISVREF(memory_usage_info,(SI_Long)2L));
	    if (gensymed_symbol == IFIX(Most_negative_fixnum))
		len = Length_of_most_negative_fixnum_as_string;
	    else if (gensymed_symbol <= (SI_Long)999999L && 
		    gensymed_symbol >= (SI_Long)-999999L) {
		gensymed_symbol_1 = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol = ABS(gensymed_symbol);
		gensymed_symbol = gensymed_symbol < (SI_Long)10000L ? 
			(gensymed_symbol < (SI_Long)100L ? 
			(gensymed_symbol < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol < (SI_Long)1000L ? 
			(SI_Long)3L : (SI_Long)4L) : gensymed_symbol < 
			(SI_Long)1000000L ? (gensymed_symbol < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol < (SI_Long)10000000L ? (SI_Long)7L 
			: gensymed_symbol < (SI_Long)100000000L ? 
			(SI_Long)8L : (SI_Long)9L;
		len = FIX(gensymed_symbol_1 + gensymed_symbol);
	    }
	    else {
		temp_2 = ABS(gensymed_symbol) / (SI_Long)1000000L;
		tmpf = temp_2;
		gensymed_symbol = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol_1 = (SI_Long)6L;
		gensymed_symbol_3 = tmpf;
		if (gensymed_symbol_3 <= (SI_Long)999999L)
		    gensymed_symbol_3 = gensymed_symbol_3 < 
			    (SI_Long)10000L ? (gensymed_symbol_3 < 
			    (SI_Long)100L ? (gensymed_symbol_3 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_3 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_3 
			    < (SI_Long)1000000L ? (gensymed_symbol_3 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_3 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_3 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		else {
		    temp_2 = gensymed_symbol_3 / (SI_Long)1000000L;
		    tmpf = temp_2;
		    gensymed_symbol_3 = (SI_Long)6L;
		    gensymed_symbol_4 = tmpf;
		    gensymed_symbol_4 = gensymed_symbol_4 < 
			    (SI_Long)10000L ? (gensymed_symbol_4 < 
			    (SI_Long)100L ? (gensymed_symbol_4 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_4 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_4 
			    < (SI_Long)1000000L ? (gensymed_symbol_4 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_4 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_4 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
		}
		len = FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_3);
	    }
	    number_string = make_stringw_function(len,Nil);
	    twrite_fixnum_into_wide_string(ISVREF(memory_usage_info,
		    (SI_Long)2L),number_string,FIX((SI_Long)0L));
	    final_string_to_write = 
		    add_text_to_string_with_align(ISVREF(memory_usage_info,
		    (SI_Long)1L),number_string,len_diff,Nil,T);
	    len_diff = FIX(IFIX(Spaces_between_columns) + 
		    instances_count_column_title_len - IFIX(len));
	    gensymed_symbol = IFIX(ISVREF(memory_usage_info,(SI_Long)5L));
	    if (gensymed_symbol == IFIX(Most_negative_fixnum))
		len = Length_of_most_negative_fixnum_as_string;
	    else if (gensymed_symbol <= (SI_Long)999999L && 
		    gensymed_symbol >= (SI_Long)-999999L) {
		gensymed_symbol_1 = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol = ABS(gensymed_symbol);
		gensymed_symbol = gensymed_symbol < (SI_Long)10000L ? 
			(gensymed_symbol < (SI_Long)100L ? 
			(gensymed_symbol < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol < (SI_Long)1000L ? 
			(SI_Long)3L : (SI_Long)4L) : gensymed_symbol < 
			(SI_Long)1000000L ? (gensymed_symbol < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol < (SI_Long)10000000L ? (SI_Long)7L 
			: gensymed_symbol < (SI_Long)100000000L ? 
			(SI_Long)8L : (SI_Long)9L;
		len = FIX(gensymed_symbol_1 + gensymed_symbol);
	    }
	    else {
		temp_2 = ABS(gensymed_symbol) / (SI_Long)1000000L;
		tmpf = temp_2;
		gensymed_symbol = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol_1 = (SI_Long)6L;
		gensymed_symbol_3 = tmpf;
		if (gensymed_symbol_3 <= (SI_Long)999999L)
		    gensymed_symbol_3 = gensymed_symbol_3 < 
			    (SI_Long)10000L ? (gensymed_symbol_3 < 
			    (SI_Long)100L ? (gensymed_symbol_3 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_3 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_3 
			    < (SI_Long)1000000L ? (gensymed_symbol_3 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_3 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_3 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		else {
		    temp_2 = gensymed_symbol_3 / (SI_Long)1000000L;
		    tmpf = temp_2;
		    gensymed_symbol_3 = (SI_Long)6L;
		    gensymed_symbol_4 = tmpf;
		    gensymed_symbol_4 = gensymed_symbol_4 < 
			    (SI_Long)10000L ? (gensymed_symbol_4 < 
			    (SI_Long)100L ? (gensymed_symbol_4 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_4 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_4 
			    < (SI_Long)1000000L ? (gensymed_symbol_4 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_4 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_4 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
		}
		len = FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_3);
	    }
	    number_string = make_stringw_function(len,Nil);
	    twrite_fixnum_into_wide_string(ISVREF(memory_usage_info,
		    (SI_Long)5L),number_string,FIX((SI_Long)0L));
	    final_string_to_write = 
		    add_text_to_string_with_align(final_string_to_write,
		    number_string,len_diff,T,T);
	    len_diff = FIX(IFIX(Spaces_between_columns) + 
		    delta_instances_column_title_len - IFIX(len));
	    gensymed_symbol = IFIX(ISVREF(memory_usage_info,(SI_Long)3L));
	    if (gensymed_symbol == IFIX(Most_negative_fixnum))
		len = Length_of_most_negative_fixnum_as_string;
	    else if (gensymed_symbol <= (SI_Long)999999L && 
		    gensymed_symbol >= (SI_Long)-999999L) {
		gensymed_symbol_1 = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol = ABS(gensymed_symbol);
		gensymed_symbol = gensymed_symbol < (SI_Long)10000L ? 
			(gensymed_symbol < (SI_Long)100L ? 
			(gensymed_symbol < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol < (SI_Long)1000L ? 
			(SI_Long)3L : (SI_Long)4L) : gensymed_symbol < 
			(SI_Long)1000000L ? (gensymed_symbol < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol < (SI_Long)10000000L ? (SI_Long)7L 
			: gensymed_symbol < (SI_Long)100000000L ? 
			(SI_Long)8L : (SI_Long)9L;
		len = FIX(gensymed_symbol_1 + gensymed_symbol);
	    }
	    else {
		temp_2 = ABS(gensymed_symbol) / (SI_Long)1000000L;
		tmpf = temp_2;
		gensymed_symbol = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol_1 = (SI_Long)6L;
		gensymed_symbol_3 = tmpf;
		if (gensymed_symbol_3 <= (SI_Long)999999L)
		    gensymed_symbol_3 = gensymed_symbol_3 < 
			    (SI_Long)10000L ? (gensymed_symbol_3 < 
			    (SI_Long)100L ? (gensymed_symbol_3 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_3 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_3 
			    < (SI_Long)1000000L ? (gensymed_symbol_3 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_3 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_3 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		else {
		    temp_2 = gensymed_symbol_3 / (SI_Long)1000000L;
		    tmpf = temp_2;
		    gensymed_symbol_3 = (SI_Long)6L;
		    gensymed_symbol_4 = tmpf;
		    gensymed_symbol_4 = gensymed_symbol_4 < 
			    (SI_Long)10000L ? (gensymed_symbol_4 < 
			    (SI_Long)100L ? (gensymed_symbol_4 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_4 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_4 
			    < (SI_Long)1000000L ? (gensymed_symbol_4 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_4 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_4 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
		}
		len = FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_3);
	    }
	    number_string = make_stringw_function(len,Nil);
	    twrite_fixnum_into_wide_string(ISVREF(memory_usage_info,
		    (SI_Long)3L),number_string,FIX((SI_Long)0L));
	    final_string_to_write = 
		    add_text_to_string_with_align(final_string_to_write,
		    number_string,len_diff,T,T);
	    len_diff = FIX(IFIX(Spaces_between_columns) + 
		    consumed_memory_column_title_len - IFIX(len));
	    gensymed_symbol = IFIX(ISVREF(memory_usage_info,(SI_Long)4L));
	    if (gensymed_symbol == IFIX(Most_negative_fixnum))
		len = Length_of_most_negative_fixnum_as_string;
	    else if (gensymed_symbol <= (SI_Long)999999L && 
		    gensymed_symbol >= (SI_Long)-999999L) {
		gensymed_symbol_1 = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol = ABS(gensymed_symbol);
		gensymed_symbol = gensymed_symbol < (SI_Long)10000L ? 
			(gensymed_symbol < (SI_Long)100L ? 
			(gensymed_symbol < (SI_Long)10L ? (SI_Long)1L : 
			(SI_Long)2L) : gensymed_symbol < (SI_Long)1000L ? 
			(SI_Long)3L : (SI_Long)4L) : gensymed_symbol < 
			(SI_Long)1000000L ? (gensymed_symbol < 
			(SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) : 
			gensymed_symbol < (SI_Long)10000000L ? (SI_Long)7L 
			: gensymed_symbol < (SI_Long)100000000L ? 
			(SI_Long)8L : (SI_Long)9L;
		len = FIX(gensymed_symbol_1 + gensymed_symbol);
	    }
	    else {
		temp_2 = ABS(gensymed_symbol) / (SI_Long)1000000L;
		tmpf = temp_2;
		gensymed_symbol = gensymed_symbol < (SI_Long)0L ? 
			(SI_Long)1L : (SI_Long)0L;
		gensymed_symbol_1 = (SI_Long)6L;
		gensymed_symbol_3 = tmpf;
		if (gensymed_symbol_3 <= (SI_Long)999999L)
		    gensymed_symbol_3 = gensymed_symbol_3 < 
			    (SI_Long)10000L ? (gensymed_symbol_3 < 
			    (SI_Long)100L ? (gensymed_symbol_3 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_3 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_3 
			    < (SI_Long)1000000L ? (gensymed_symbol_3 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_3 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_3 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		else {
		    temp_2 = gensymed_symbol_3 / (SI_Long)1000000L;
		    tmpf = temp_2;
		    gensymed_symbol_3 = (SI_Long)6L;
		    gensymed_symbol_4 = tmpf;
		    gensymed_symbol_4 = gensymed_symbol_4 < 
			    (SI_Long)10000L ? (gensymed_symbol_4 < 
			    (SI_Long)100L ? (gensymed_symbol_4 < 
			    (SI_Long)10L ? (SI_Long)1L : (SI_Long)2L) : 
			    gensymed_symbol_4 < (SI_Long)1000L ? 
			    (SI_Long)3L : (SI_Long)4L) : gensymed_symbol_4 
			    < (SI_Long)1000000L ? (gensymed_symbol_4 < 
			    (SI_Long)100000L ? (SI_Long)5L : (SI_Long)6L) :
			     gensymed_symbol_4 < (SI_Long)10000000L ? 
			    (SI_Long)7L : gensymed_symbol_4 < 
			    (SI_Long)100000000L ? (SI_Long)8L : (SI_Long)9L;
		    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
		}
		len = FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_3);
	    }
	    number_string = make_stringw_function(len,Nil);
	    twrite_fixnum_into_wide_string(ISVREF(memory_usage_info,
		    (SI_Long)4L),number_string,FIX((SI_Long)0L));
	    final_string_to_write = 
		    add_text_to_string_with_align(final_string_to_write,
		    number_string,len_diff,T,T);
	    g2_stream_write_line(final_string_to_write,output);
	    reclaim_wide_string(final_string_to_write);
	    goto next_loop;
	  end_loop_3:
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* LENGTH-OF-FRAME-VECTOR-CHAIN */
Object length_of_frame_vector_chain(frame_vector_qm)
    Object frame_vector_qm;
{
    Object vector_qm;
    SI_Long count_1;

    x_note_fn_call(245,37);
    count_1 = (SI_Long)0L;
    vector_qm = frame_vector_qm;
  next_loop:
    if ( !TRUEP(vector_qm))
	goto end_loop;
    count_1 = count_1 + (SI_Long)1L;
    vector_qm = ISVREF(vector_qm,(SI_Long)0L);
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(count_1));
    return VALUES_1(Qnil);
}

static Object string_constant_18;  /* "Frame Vector Pools (thread ~a)" */

static Object Qlength_of_frame_vector_chain;  /* length-of-frame-vector-chain */

/* WRITE-FRAME-VECTOR-POOL-STATISTICS */
Object write_frame_vector_pool_statistics(output)
    Object output;
{
    Object frame_vector_pool_vector, title_string, temp, temp_1;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(245,38);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Number_of_scheduler_workers);
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    frame_vector_pool_vector = ISVREF(Frame_vector_pool_array,i);
    title_string = tformat_text_string(2,string_constant_18,FIX(i));
    PUSH_SPECIAL_WITH_SYMBOL(Frame_vector_pool_vector,Qframe_vector_pool_vector,frame_vector_pool_vector,
	    0);
      temp = Frame_vector_pool_vector;
      temp_1 = Frame_vector_pool_counts_vector;
      write_array_pool_statistics_table(title_string,temp,temp_1,
	      gensym_list_integers(SIMPLE_ARRAY_ANY_1_LENGTH(Frame_vector_pool_vector),
	      FIX((SI_Long)1L),FIX((SI_Long)1L)),
	      SYMBOL_FUNCTION(Qlength_of_frame_vector_chain),output);
      g2_stream_terpri(output);
      reclaim_text_string(title_string);
    POP_SPECIAL();
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* LENGTH-OF-VECTOR-CHAIN */
Object length_of_vector_chain(simple_vector_qm)
    Object simple_vector_qm;
{
    Object vector_qm;
    SI_Long count_1;

    x_note_fn_call(245,39);
    count_1 = (SI_Long)0L;
    vector_qm = simple_vector_qm;
  next_loop:
    if ( !TRUEP(vector_qm))
	goto end_loop;
    count_1 = count_1 + (SI_Long)1L;
    vector_qm = ISVREF(vector_qm,(SI_Long)0L);
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(count_1));
    return VALUES_1(Qnil);
}

static Object string_constant_19;  /* "Simple Vector Pools" */

static Object Qlength_of_vector_chain;  /* length-of-vector-chain */

static Object string_constant_20;  /* "Oversized Simple Vector Pools" */

/* WRITE-SIMPLE-VECTOR-POOL-STATISTICS */
Object write_simple_vector_pool_statistics(output)
    Object output;
{
    Object temp, temp_1;

    x_note_fn_call(245,40);
    temp = Vector_of_simple_vector_pools;
    temp_1 = Simple_vector_pool_counts;
    write_array_pool_statistics_table(string_constant_19,temp,temp_1,
	    gensym_list_integers(SIMPLE_ARRAY_ANY_1_LENGTH(Vector_of_simple_vector_pools),
	    FIX((SI_Long)0L),FIX((SI_Long)1L)),
	    SYMBOL_FUNCTION(Qlength_of_vector_chain),output);
    temp = Vector_of_oversized_simple_vector_pools;
    temp_1 = Oversized_simple_vector_pool_counts;
    write_array_pool_statistics_table(string_constant_20,temp,temp_1,
	    gensym_list_integers(SIMPLE_ARRAY_ANY_1_LENGTH(Vector_of_oversized_simple_vector_pools),
	    FIX((SI_Long)0L),FIX((SI_Long)1024L)),
	    SYMBOL_FUNCTION(Qlength_of_vector_chain),output);
    return VALUES_1(Nil);
}

/* GENSYM-LIST-INTEGERS */
Object gensym_list_integers(length_1,base,multiplier)
    Object length_1, base, multiplier;
{
    Object list_1, cons_1, temp;
    SI_Long index_1, car_new_value;

    x_note_fn_call(245,41);
    list_1 = make_gensym_list_1(length_1);
    index_1 = IFIX(base);
    cons_1 = list_1;
  next_loop:
    if ( !TRUEP(cons_1))
	goto end_loop;
    car_new_value = index_1 * IFIX(multiplier);
    M_CAR(cons_1) = FIX(car_new_value);
    index_1 = index_1 + (SI_Long)1L;
    cons_1 = M_CDR(cons_1);
    goto next_loop;
  end_loop:
    temp = list_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object string_constant_21;  /* "Byte-vector-16 Pools" */

/* WRITE-BYTE-VECTOR-16-POOL-STATISTICS */
Object write_byte_vector_16_pool_statistics(output)
    Object output;
{
    Object temp, temp_1;

    x_note_fn_call(245,42);
    temp = Byte_vector_16_pools;
    temp_1 = Byte_vector_16_pool_counts;
    write_array_pool_statistics_table(string_constant_21,temp,temp_1,
	    gensym_list_maximum_buffer_sizes(Byte_vector_16_allocation_schemes),
	    SYMBOL_FUNCTION(Qlength),output);
    return VALUES_1(Nil);
}

static Object string_constant_22;  /* "Short Simple Text String Pools" */

static Object string_constant_23;  /* "Long Simple Text String Pools" */

static Object string_constant_24;  /* "Adjustable Text String Pools" */

/* WRITE-STRING-POOL-STATISTICS */
Object write_string_pool_statistics(output)
    Object output;
{
    Object temp, temp_1;

    x_note_fn_call(245,43);
    temp = Short_simple_gensym_strings;
    temp_1 = Short_simple_gensym_string_counts;
    write_array_pool_statistics_table(string_constant_22,temp,temp_1,
	    gensym_list_integers(SIMPLE_ARRAY_ANY_1_LENGTH(Short_simple_gensym_strings),
	    FIX((SI_Long)0L),FIX((SI_Long)1L)),SYMBOL_FUNCTION(Qlength),
	    output);
    g2_stream_terpri(output);
    temp = Long_simple_gensym_strings;
    temp_1 = Long_simple_gensym_string_counts;
    write_array_pool_statistics_table(string_constant_23,temp,temp_1,
	    gensym_list_maximum_buffer_sizes(String_allocation_schemes),
	    SYMBOL_FUNCTION(Qlength),output);
    g2_stream_terpri(output);
    temp = Adjustable_gensym_strings;
    temp_1 = Adjustable_gensym_string_counts;
    write_array_pool_statistics_table(string_constant_24,temp,temp_1,
	    gensym_list_maximum_buffer_sizes(String_allocation_schemes),
	    SYMBOL_FUNCTION(Qlength),output);
    return VALUES_1(Nil);
}

static Object string_constant_25;  /* "   " */

static Object string_constant_26;  /* "Length    Out Count %Out" */

/* WRITE-ARRAY-POOL-STATISTICS-TABLE */
Object write_array_pool_statistics_table(pool_title,pool_vector,
	    count_vector,max_sizes_list,length_function,output)
    Object pool_title, pool_vector, count_vector, max_sizes_list;
    Object length_function, output;
{
    Object max_size, ab_loop_list_, reclaimed, count_1, entries, ab_loopvar_;
    Object ab_loopvar__1, column, rows, columns, ab_loop_list__1, first_qm;
    Object out, percent_out, ab_loop_iter_flag_, temp;
    SI_Long column_count, pool, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(245,44);
    g2_stream_write_line(pool_title,output);
    column_count = (SI_Long)3L;
    pool = (SI_Long)0L;
    max_size = Nil;
    ab_loop_list_ = max_sizes_list;
    reclaimed = Nil;
    count_1 = Nil;
    entries = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    max_size = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaimed = FUNCALL_1(length_function,ISVREF(pool_vector,pool));
    count_1 = ISVREF(count_vector,pool);
    if ( !(IFIX(reclaimed) == (SI_Long)0L && IFIX(count_1) == (SI_Long)0L)) {
	ab_loopvar__1 = gensym_cons_1(gensym_list_3(max_size,reclaimed,
		count_1),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    entries = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    pool = pool + (SI_Long)1L;
    goto next_loop;
  end_loop:
    column = FIX((SI_Long)0L);
    ab_loop_bind_ = column_count;
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,0);
    next_loop_1:
      if (IFIX(Column) >= ab_loop_bind_)
	  goto end_loop_1;
      if ( !(IFIX(Column) == (SI_Long)0L))
	  g2_stream_write_string(string_constant_25,output);
      g2_stream_write_string(string_constant_26,output);
      Column = FIXNUM_ADD1(Column);
      goto next_loop_1;
    end_loop_1:;
    POP_SPECIAL();
    g2_stream_terpri(output);
    rows = split_list_into_rows_of_columns(entries,FIX(column_count));
    columns = Nil;
    ab_loop_list_ = rows;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    columns = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    column = Nil;
    ab_loop_list__1 = columns;
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,0);
      first_qm = T;
      max_size = Nil;
      reclaimed = Nil;
      count_1 = Nil;
      out = Nil;
      percent_out = Nil;
      ab_loop_iter_flag_ = T;
    next_loop_3:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_3;
      Column = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if ( !TRUEP(ab_loop_iter_flag_))
	  first_qm = Nil;
      max_size = CAR(Column);
      temp = CDR(Column);
      reclaimed = CAR(temp);
      temp = CDR(Column);
      temp = CDR(temp);
      count_1 = CAR(temp);
      out = FIXNUM_MINUS(count_1,reclaimed);
      percent_out = chestnut_floorf_function(FIX(IFIX(out) * 
	      (SI_Long)100L),FIX(MAX(IFIX(count_1),(SI_Long)1L)));
      if ( !TRUEP(first_qm))
	  g2_stream_write_string(string_constant_25,output);
      write_string_stats_field_value(max_size,FIX((SI_Long)7L),T,CHR('.'),
	      output);
      write_string_stats_field_value(out,FIX((SI_Long)6L),Nil,CHR(' '),output);
      write_string_stats_field_value(count_1,FIX((SI_Long)6L),Nil,CHR(' '),
	      output);
      write_string_stats_field_value(percent_out,FIX((SI_Long)4L),Nil,
	      CHR(' '),output);
      g2_stream_write_char(CHR('%'),output);
      reclaim_gensym_list_1(Column);
      ab_loop_iter_flag_ = Nil;
      goto next_loop_3;
    end_loop_3:;
    POP_SPECIAL();
    reclaim_gensym_list_1(columns);
    g2_stream_terpri(output);
    goto next_loop_2;
  end_loop_2:
    reclaim_gensym_list_1(rows);
    reclaim_gensym_list_1(max_sizes_list);
    return VALUES_1(Nil);
}

/* SPLIT-LIST-INTO-ROWS-OF-COLUMNS */
Object split_list_into_rows_of_columns(entries,columns)
    Object entries, columns;
{
    Object count_1, row_list, row_cons, entry_cons, next_entry, car_new_value;
    Object temp_1;
    SI_Long temp, row_count;

    x_note_fn_call(245,45);
    count_1 = length(entries);
    temp = IFIX(FIXNUM_ADD(count_1,FIXNUM_SUB1(columns))) / IFIX(columns);
    row_count = temp;
    row_list = fill(2,make_gensym_list_1(FIX(row_count)),Nil);
    row_cons = row_list;
    entry_cons = entries;
    next_entry = Nil;
  next_loop:
    if ( !TRUEP(entry_cons))
	goto end_loop;
    next_entry = M_CDR(entry_cons);
    M_CDR(entry_cons) = Nil;
    car_new_value = nconc2(CAR(row_cons),entry_cons);
    M_CAR(row_cons) = car_new_value;
    temp_1 = CDR(row_cons);
    if (temp_1);
    else
	temp_1 = row_list;
    row_cons = temp_1;
    entry_cons = next_entry;
    goto next_loop;
  end_loop:;
    return VALUES_1(row_list);
}

/* WRITE-STRING-STATS-FIELD-VALUE */
Object write_string_stats_field_value(fixnum_to_write_init,
	    field_width_init,right_pad_qm,pad_char,g2_output_stream)
    Object fixnum_to_write_init, field_width_init, right_pad_qm, pad_char;
    Object g2_output_stream;
{
    SI_Long fixnum_to_write, field_width, number_width, gensymed_symbol;
    SI_Long gensymed_symbol_1, ab_loop_repeat_;

    x_note_fn_call(245,46);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    field_width = IFIX(field_width_init);
    if (fixnum_to_write == (SI_Long)0L)
	number_width = (SI_Long)1L;
    else {
	gensymed_symbol = 
		IFIX(fixnum_order_of_magnitude(FIX(ABS(fixnum_to_write))));
	gensymed_symbol_1 = (SI_Long)0L > fixnum_to_write ? (SI_Long)2L : 
		(SI_Long)1L;
	number_width = gensymed_symbol + gensymed_symbol_1;
    }
    if (right_pad_qm)
	write_string_stats_fixnum(FIX(fixnum_to_write),g2_output_stream);
    ab_loop_repeat_ = field_width - number_width;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    g2_stream_write_char(pad_char,g2_output_stream);
    goto next_loop;
  end_loop:;
    if ( !TRUEP(right_pad_qm))
	write_string_stats_fixnum(FIX(fixnum_to_write),g2_output_stream);
    return VALUES_1(Nil);
}

/* WRITE-STRING-STATS-FIXNUM */
Object write_string_stats_fixnum(fixnum_to_write_init,g2_output_stream)
    Object fixnum_to_write_init, g2_output_stream;
{
    SI_Long fixnum_to_write;

    x_note_fn_call(245,47);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    if (fixnum_to_write == IFIX(Most_negative_fixnum))
	g2_stream_write_string(Most_negative_fixnum_as_string,
		g2_output_stream);
    else if (fixnum_to_write < (SI_Long)0L) {
	g2_stream_write_char(CHR('-'),g2_output_stream);
	write_string_stats_positive_fixnum(FIX( - fixnum_to_write),
		g2_output_stream);
    }
    else
	write_string_stats_positive_fixnum(FIX(fixnum_to_write),
		g2_output_stream);
    return VALUES_1(Nil);
}

/* WRITE-STRING-STATS-POSITIVE-FIXNUM */
Object write_string_stats_positive_fixnum(fixnum_to_write_init,
	    g2_output_stream)
    Object fixnum_to_write_init, g2_output_stream;
{
    SI_Long fixnum_to_write, temp, quotient, remainder_1;

    x_note_fn_call(245,48);
    fixnum_to_write = IFIX(fixnum_to_write_init);
    if (fixnum_to_write < (SI_Long)10L)
	g2_stream_write_char(digit_char(FIX(fixnum_to_write),_,_),
		g2_output_stream);
    else {
	temp = fixnum_to_write / (SI_Long)10L;
	quotient = temp;
	temp = fixnum_to_write % (SI_Long)10L;
	remainder_1 = temp;
	write_string_stats_positive_fixnum(FIX(quotient),g2_output_stream);
	g2_stream_write_char(digit_char(FIX(remainder_1),_,_),
		g2_output_stream);
    }
    return VALUES_1(Nil);
}

static Object string_constant_27;  /* "LRU Queue Statistics" */

static Object string_constant_28;  /* "Scaled Font LRU Queue Memory Usage             = ~a" */

static Object string_constant_29;  /* "Icon Rendering LRU Queue Memory Usage          = ~a" */

static Object string_constant_30;  /* "Graph Rendering LRU Queue Memory Usage         = ~a" */

/* WRITE-LRU-QUEUE-STATISTICS */
Object write_lru_queue_statistics(output)
    Object output;
{
    Object string_var;

    x_note_fn_call(245,49);
    g2_stream_write_line(string_constant_27,output);
    string_var = Nil;
    string_var = tformat_text_string(2,string_constant_28,
	    compute_memory_for_scaled_font_lru_queue());
    g2_stream_write_line(string_var,output);
    reclaim_text_string(string_var);
    string_var = tformat_text_string(2,string_constant_29,
	    compute_memory_for_icon_rendering_lru_queue());
    g2_stream_write_line(string_var,output);
    reclaim_text_string(string_var);
    string_var = tformat_text_string(2,string_constant_30,
	    compute_memory_for_graph_rendering_lru_queue());
    g2_stream_write_line(string_var,output);
    return reclaim_text_string(string_var);
}

static Object Qcompute_true_size_of_scaled_font;  /* compute-true-size-of-scaled-font */

/* COMPUTE-MEMORY-FOR-SCALED-FONT-LRU-QUEUE */
Object compute_memory_for_scaled_font_lru_queue()
{
    x_note_fn_call(245,50);
    return accumulate_lru_queue_memory_size(Scaled_font_lru_queue,
	    Qcompute_true_size_of_scaled_font);
}

static Object Qcompute_true_size_of_icon_rendering;  /* compute-true-size-of-icon-rendering */

/* COMPUTE-MEMORY-FOR-ICON-RENDERING-LRU-QUEUE */
Object compute_memory_for_icon_rendering_lru_queue()
{
    x_note_fn_call(245,51);
    return accumulate_lru_queue_memory_size(Icon_rendering_lru_queue,
	    Qcompute_true_size_of_icon_rendering);
}

static Object Qcompute_true_size_of_graph_rendering;  /* compute-true-size-of-graph-rendering */

/* COMPUTE-MEMORY-FOR-GRAPH-RENDERING-LRU-QUEUE */
Object compute_memory_for_graph_rendering_lru_queue()
{
    x_note_fn_call(245,52);
    return accumulate_lru_queue_memory_size(Graph_rendering_lru_queue,
	    Qcompute_true_size_of_graph_rendering);
}

/* ACCUMULATE-LRU-QUEUE-MEMORY-SIZE */
Object accumulate_lru_queue_memory_size(lru_queue,
	    lru_element_size_function_name)
    Object lru_queue, lru_element_size_function_name;
{
    Object queue_head, lru_element_qm, ab_loopvar_, temp;

    x_note_fn_call(245,53);
    queue_head = ISVREF(lru_queue,(SI_Long)1L);
    lru_element_qm =  !EQ(queue_head,lru_queue) ? queue_head : Nil;
    ab_loopvar_ = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(lru_element_qm))
	goto end_loop;
    if (EQ(lru_element_qm,lru_queue))
	goto end_loop;
    temp = FUNCALL_1(lru_element_size_function_name,lru_element_qm);
    ab_loopvar_ = add(temp,ab_loopvar_);
    lru_element_qm = ISVREF(lru_element_qm,(SI_Long)1L);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return ltimes(FIX((SI_Long)4L),temp);
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object Qab_structure;       /* structure */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* TWRITE-POOL-ENTRY-DATA-TYPE-TERSELY */
Object twrite_pool_entry_data_type_tersely(pool_entry_data_type_1)
    Object pool_entry_data_type_1;
{
    Object temp;

    x_note_fn_call(245,54);
    if (CONSP(pool_entry_data_type_1))
	pool_entry_data_type_1 = CAR(pool_entry_data_type_1);
    if (EQ(pool_entry_data_type_1,Qsymbol))
	temp = twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)6L));
    else if (EQ(pool_entry_data_type_1,Qcons))
	temp = twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)4L));
    else if (EQ(pool_entry_data_type_1,Qab_structure))
	temp = twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)6L));
    else if (EQ(pool_entry_data_type_1,Qsimple_vector))
	temp = twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)7L));
    else if (EQ(pool_entry_data_type_1,Qvector))
	temp = twrite_beginning_of_wide_string(array_constant_6,
		FIX((SI_Long)6L));
    else if (EQ(pool_entry_data_type_1,Qsimple_string))
	temp = twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)7L));
    else if (EQ(pool_entry_data_type_1,Qstring))
	temp = twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)6L));
    else if (EQ(pool_entry_data_type_1,Qsimple_array))
	temp = twrite_beginning_of_wide_string(array_constant_9,
		FIX((SI_Long)6L));
    else if (EQ(pool_entry_data_type_1,Qarray))
	temp = twrite_beginning_of_wide_string(array_constant_10,
		FIX((SI_Long)5L));
    else
	temp = write_s_expression(pool_entry_data_type_1);
    return VALUES_1(temp);
}

static Object string_constant_31;  /* "System Object Pool Usage Statistics" */

static Object string_constant_32;  /* "Pool Name" */

static Object string_constant_33;  /* "Type" */

static Object string_constant_34;  /* "Out" */

static Object string_constant_35;  /* "%Out" */

static Object string_constant_36;  /* "Count" */

static Object string_constant_37;  /* "dCount" */

static Object string_constant_38;  /* "Memory" */

static Object string_constant_39;  /* "dMemory" */

static Object string_constant_40;  /* "" */

/* WRITE-POOL-MEMORY-USAGE */
Object write_pool_memory_usage(output)
    Object output;
{
    Object string_var, meter_entry, ab_loop_list_, snapshot_entry;
    Object ab_loop_list__1, pool_name, out, count_1, old_count, bytes;
    Object old_bytes, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object delta;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(245,55);
    g2_stream_write_line(string_constant_31,output);
    write_padded_string(output,string_constant_32,CHR(' '),
	    FIX((SI_Long)29L),Nil);
    g2_stream_write_char(CHR(' '),output);
    write_padded_string(output,string_constant_33,CHR(' '),
	    FIX((SI_Long)8L),Nil);
    write_padded_string(output,string_constant_34,CHR(' '),
	    FIX((SI_Long)10L),T);
    write_padded_string(output,string_constant_35,CHR(' '),FIX((SI_Long)5L),T);
    write_padded_string(output,string_constant_36,CHR(' '),
	    FIX((SI_Long)10L),T);
    write_padded_string(output,string_constant_37,CHR(' '),FIX((SI_Long)8L),T);
    write_padded_string(output,string_constant_38,CHR(' '),
	    FIX((SI_Long)10L),T);
    write_padded_string(output,string_constant_39,CHR(' '),FIX((SI_Long)8L),T);
    g2_stream_terpri(output);
    string_var = Nil;
    meter_entry = Nil;
    ab_loop_list_ = Object_pool_meters;
    snapshot_entry = Nil;
    ab_loop_list__1 = Last_memory_stats_snapshot;
    pool_name = Nil;
    out = Nil;
    count_1 = Nil;
    old_count = Nil;
    bytes = Nil;
    old_bytes = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    meter_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    snapshot_entry = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    pool_name = pool_entry_name(meter_entry);
    out = pool_entry_outstanding_object_count(meter_entry);
    count_1 = pool_entry_object_count(meter_entry);
    old_count = SECOND(snapshot_entry);
    bytes = pool_entry_memory_usage_in_bytes(meter_entry);
    old_bytes = FIRST(snapshot_entry);
    if ( !(IFIX(count_1) == (SI_Long)0L && IFIX(out) == (SI_Long)0L && 
	    IFIX(bytes) == (SI_Long)0L)) {
	write_padded_string(output,SYMBOL_NAME(pool_name),CHR(' '),
		FIX((SI_Long)29L),Nil);
	g2_stream_write_char(CHR(' '),output);
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
		  twrite_pool_entry_data_type_tersely(pool_entry_data_type(meter_entry));
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)8L),Nil);
	reclaim_text_string(string_var);
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
		  twrite(out);
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)10L),T);
	reclaim_text_string(string_var);
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
		  twrite(chestnut_floorf_function(FIX(IFIX(out) * 
			  (SI_Long)100L),FIX(MAX(IFIX(count_1),(SI_Long)1L))));
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)5L),T);
	reclaim_text_string(string_var);
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
		  twrite(count_1);
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)10L),T);
	reclaim_text_string(string_var);
	delta = FIXNUM_MINUS(count_1,old_count);
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
		  twrite(IFIX(delta) == (SI_Long)0L ? string_constant_40 : 
			  delta);
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)8L),T);
	reclaim_text_string(string_var);
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
		  twrite(bytes);
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)10L),T);
	reclaim_text_string(string_var);
	delta = FIXNUM_MINUS(bytes,old_bytes);
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
		  twrite(IFIX(delta) == (SI_Long)0L ? string_constant_40 : 
			  delta);
		  string_var = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	write_padded_string(output,string_var,CHR(' '),FIX((SI_Long)8L),T);
	reclaim_text_string(string_var);
	g2_stream_terpri(output);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_string_stats_namestring, Qsimple_string_stats_namestring);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_string_stats_header_needed, Qsimple_string_stats_header_needed);

DEFINE_VARIABLE_WITH_SYMBOL(Reclaimed_strings_reported, Qreclaimed_strings_reported);

DEFINE_VARIABLE_WITH_SYMBOL(Allocated_strings_reported, Qallocated_strings_reported);

static Object Qg2_directory_pathname;  /* g2-directory-pathname */

static Object array_constant_11;   /* # */

static Object string_constant_41;  /* "Setting parameters for string allocation metering: reporting data on string allocations and reclamations in file ~a, for one string in every ~a longer than ~a characters, including first ~a characters of reclaimed string" */

/* G2-SET-SIMPLE-STRING-METERING-PARAMETERS */
Object g2_set_simple_string_metering_parameters(filename,min_string_length,
	    frequency,chars_to_print)
    Object filename, min_string_length, frequency, chars_to_print;
{
    x_note_fn_call(245,56);
    reclaim_text_string(Simple_string_stats_namestring);
    Simple_string_stats_namestring = export_text_string(2,filename,
	    Qg2_directory_pathname);
    Min_string_length_to_report = min_string_length;
    if ( !EQL(String_report_frequency,frequency)) {
	String_reclaims_until_next_report = FIX((SI_Long)0L);
	String_allocations_until_next_report = FIX((SI_Long)0L);
    }
    String_report_frequency = frequency;
    String_chars_to_print = chars_to_print;
    if (Log_simple_string_data)
	write_g2_string_stats_header(array_constant_11);
    notify_user_at_console_and_on_logbook(5,string_constant_41,filename,
	    frequency,min_string_length,chars_to_print);
    return reclaim_text_string(filename);
}

static Object array_constant_12;   /* # */

static Object string_constant_42;  /* "Turning on string allocation monitoring" */

/* G2-TURN-ON-SIMPLE-STRING-METERING */
Object g2_turn_on_simple_string_metering()
{
    x_note_fn_call(245,57);
    if (write_g2_string_stats_header(array_constant_12)) {
	Log_simple_string_data = T;
	return notify_user_at_console_and_on_logbook(1,string_constant_42);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_43;  /* "Turning off string allocation monitoring" */

static Object array_constant_13;   /* # */

/* G2-TURN-OFF-SIMPLE-STRING-METERING */
Object g2_turn_off_simple_string_metering()
{
    x_note_fn_call(245,58);
    Log_simple_string_data = Nil;
    notify_user_at_console_and_on_logbook(1,string_constant_43);
    return write_g2_string_stats_header(array_constant_13);
}

static Object array_constant_14;   /* # */

static Object string_constant_44;  /* "Turning on string reclaimation monitoring" */

/* G2-SIMPLE-STRING-METERING-INCLUDE-RECLAIMS */
Object g2_simple_string_metering_include_reclaims()
{
    x_note_fn_call(245,59);
    if ( !TRUEP(Log_simple_string_reclaims)) {
	Log_simple_string_reclaims = T;
	if (Log_simple_string_data)
	    write_g2_string_stats_header(array_constant_14);
    }
    return notify_user_at_console_and_on_logbook(1,string_constant_44);
}

static Object array_constant_15;   /* # */

static Object string_constant_45;  /* "Metering only allocations" */

/* G2-SIMPLE-STRING-METERING-EXCLUDE-RECLAIMS */
Object g2_simple_string_metering_exclude_reclaims()
{
    x_note_fn_call(245,60);
    if (Log_simple_string_reclaims) {
	Log_simple_string_reclaims = Nil;
	if (Log_simple_string_data)
	    write_g2_string_stats_header(array_constant_15);
    }
    return notify_user_at_console_and_on_logbook(1,string_constant_45);
}

/* REPORT-SIMPLE-STRING-ALLOCATION */
Object report_simple_string_allocation(length_1)
    Object length_1;
{
    x_note_fn_call(245,61);
    return report_simple_string_metering_data(length_1,Nil,T);
}

/* REPORT-SIMPLE-STRING-RECLAMATION */
Object report_simple_string_reclamation(string_1,length_1)
    Object string_1, length_1;
{
    x_note_fn_call(245,62);
    return report_simple_string_metering_data(length_1,string_1,Nil);
}

static Object Qgensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object Qg2_stream_error_string;  /* g2-stream-error-string */

static Object string_constant_46;  /* "Unable to open G2 statistics file ~s, ~a." */

static Object string_constant_47;  /* "Allocated string #~a: length is ~a" */

static Object string_constant_48;  /* "Reclaimed string #~a: length is ~a" */

static Object string_constant_49;  /* "Initial ~a characters: <~a>" */

static Object Qtformat_text_string;  /* tformat-text-string */

static Object string_constant_50;  /* "~a" */

/* REPORT-SIMPLE-STRING-METERING-DATA */
Object report_simple_string_metering_data(length_1,string_qm,allocation_qm)
    Object length_1, string_qm, allocation_qm;
{
    Object log_simple_string_data, inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p, namestring_1;
    volatile Object namestring_for_user;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object open_g2_stream_qm;
    volatile Object error_string_for_user;
    Object temp, temp_1, report_line, substring, result_from_body;
    Object gensymed_symbol_2, control_string, error_args, error_arg;
    Object ab_loop_list_, report_string;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_to_copy;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(3);
    Object result;

    x_note_fn_call(245,63);
    SAVE_STACK();
    log_simple_string_data = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Log_simple_string_data,Qlog_simple_string_data,log_simple_string_data,
	    2);
      inside_handling_gensym_file_errors_scope_p = T;
      gensym_file_error_occurred_p = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
		0);
	  if (PUSH_CATCH(Qgensym_file_error_catch_tag,3)) {
	      namestring_1 = Qunbound_in_protected_let;
	      namestring_for_user = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(2)) {
		  namestring_1 = Simple_string_stats_namestring;
		  namestring_for_user = copy_text_string(namestring_1);
		  if ( 
			  !TRUEP(g2_stream_probe_file_for_exist(Simple_string_stats_namestring))) 
			      {
		      pathname_used_p = Qunbound_in_protected_let;
		      namestring_2 = Qunbound_in_protected_let;
		      open_g2_stream_qm = Qunbound_in_protected_let;
		      if (PUSH_UNWIND_PROTECT(1)) {
			  pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ?
				   (EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? T : Nil) : Qnil;
			  namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
				  EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? gensym_namestring(1,namestring_1) : 
				  namestring_1;
			  open_g2_stream_qm = 
				  g2_stream_open_for_output(namestring_2);
			  if (open_g2_stream_qm) {
			      if (Simple_string_stats_header_needed) {
				  write_g2_string_stats_header_to_stream(open_g2_stream_qm,
					  Nil);
				  Simple_string_stats_header_needed = Nil;
			      }
			  }
			  else {
			      error_string_for_user = 
				      Qunbound_in_protected_let;
			      if (PUSH_UNWIND_PROTECT(0)) {
				  temp = 
					  assq_function(Internal_status_of_most_recent_file_operation,
					  G2_stream_error_string_table);
				  temp = CDR(temp);
				  if (temp);
				  else {
				      if (Cached_unknown_error_string_with_code_qm)
					  reclaim_text_string(Cached_unknown_error_string_with_code_qm);
				      Cached_unknown_error_string_with_code_qm 
					      = tformat_text_string(2,
					      Unknown_error_during_file_op_with_code_message,
					      Internal_status_of_most_recent_file_operation);
				      temp = 
					      Cached_unknown_error_string_with_code_qm;
				  }
				  error_string_for_user = 
					  import_text_string(2,temp,
					  Qg2_stream_error_string);
				  notify_user(3,string_constant_46,
					  namestring_for_user,
					  error_string_for_user);
			      }
			      POP_UNWIND_PROTECT(0);
			      if (error_string_for_user) {
				  if ( !EQ(error_string_for_user,
					  Qunbound_in_protected_let))
				      reclaim_text_string(error_string_for_user);
			      }
			      CONTINUE_UNWINDING(0);
			  }
		      }
		      POP_UNWIND_PROTECT(1);
		      if (open_g2_stream_qm) {
			  if ( !EQ(open_g2_stream_qm,
				  Qunbound_in_protected_let))
			      g2_stream_close(open_g2_stream_qm);
		      }
		      if (namestring_2) {
			  if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
			      if (pathname_used_p)
				  reclaim_text_string(namestring_2);
			  }
		      }
		      CONTINUE_UNWINDING(1);
		  }
		  pathname_used_p = Qunbound_in_protected_let;
		  namestring_2 = Qunbound_in_protected_let;
		  open_g2_stream_qm = Qunbound_in_protected_let;
		  if (PUSH_UNWIND_PROTECT(1)) {
		      pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
			      (EQ(ISVREF(namestring_1,(SI_Long)0L),
			      Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			      ? T : Nil) : Qnil;
		      namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
			      EQ(ISVREF(namestring_1,(SI_Long)0L),
			      Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			      ? gensym_namestring(1,namestring_1) : 
			      namestring_1;
		      open_g2_stream_qm = 
			      g2_stream_open_for_appending(namestring_2,
			      Kcreate);
		      if (open_g2_stream_qm) {
			  if (Simple_string_stats_header_needed) {
			      write_g2_string_stats_header_to_stream(open_g2_stream_qm,
				      Nil);
			      Simple_string_stats_header_needed = Nil;
			  }
			  if (allocation_qm) {
			      temp_1 = FIXNUM_ADD1(Allocated_strings_reported);
			      Allocated_strings_reported = temp_1;
			  }
			  else {
			      temp_1 = FIXNUM_ADD1(Reclaimed_strings_reported);
			      Reclaimed_strings_reported = temp_1;
			  }
			  report_line = allocation_qm ? 
				  tformat_text_string(3,string_constant_47,
				  Allocated_strings_reported,length_1) : 
				  tformat_text_string(3,string_constant_48,
				  Reclaimed_strings_reported,length_1);
			  g2_stream_write_line(report_line,open_g2_stream_qm);
			  reclaim_text_string(report_line);
			  print_backtrace_to_stream(open_g2_stream_qm);
			  if ( !TRUEP(allocation_qm) &&  
				  !TRUEP(zerop(String_chars_to_print))) {
			      temp = 
				      length_of_null_terminated_string(string_qm);
			      if (temp);
			      else
				  temp = String_chars_to_print;
			      gensymed_symbol = IFIX(temp);
			      gensymed_symbol_1 = IFIX(length_1);
			      length_to_copy = MIN(gensymed_symbol,
				      gensymed_symbol_1);
			      substring = 
				      gensym_string_substring(string_qm,
				      FIX((SI_Long)0L),FIX(length_to_copy));
			      report_line = tformat_text_string(3,
				      string_constant_49,
				      FIX(length_to_copy),
				      replace_nulls_by_spaces(substring));
			      g2_stream_write_line(report_line,
				      open_g2_stream_qm);
			      reclaim_text_string(report_line);
			      temp = reclaim_gensym_string(substring);
			  }
			  else
			      temp = Nil;
		      }
		      else {
			  error_string_for_user = Qunbound_in_protected_let;
			  if (PUSH_UNWIND_PROTECT(0)) {
			      temp = 
				      assq_function(Internal_status_of_most_recent_file_operation,
				      G2_stream_error_string_table);
			      temp = CDR(temp);
			      if (temp);
			      else {
				  if (Cached_unknown_error_string_with_code_qm)
				      reclaim_text_string(Cached_unknown_error_string_with_code_qm);
				  Cached_unknown_error_string_with_code_qm 
					  = tformat_text_string(2,
					  Unknown_error_during_file_op_with_code_message,
					  Internal_status_of_most_recent_file_operation);
				  temp = 
					  Cached_unknown_error_string_with_code_qm;
			      }
			      error_string_for_user = import_text_string(2,
				      temp,Qg2_stream_error_string);
			      temp = notify_user(3,string_constant_46,
				      namestring_for_user,
				      error_string_for_user);
			      SAVE_VALUES(VALUES_1(temp));
			  }
			  POP_UNWIND_PROTECT(0);
			  if (error_string_for_user) {
			      if ( !EQ(error_string_for_user,
				      Qunbound_in_protected_let))
				  reclaim_text_string(error_string_for_user);
			  }
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  temp = result;
		      }
		      SAVE_VALUES(VALUES_1(temp));
		  }
		  POP_UNWIND_PROTECT(1);
		  if (open_g2_stream_qm) {
		      if ( !EQ(open_g2_stream_qm,Qunbound_in_protected_let))
			  g2_stream_close(open_g2_stream_qm);
		  }
		  if (namestring_2) {
		      if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
			  if (pathname_used_p)
			      reclaim_text_string(namestring_2);
		      }
		  }
		  CONTINUE_UNWINDING(1);
		  result = RESTORE_VALUES();
		  SAVE_VALUES(VALUES_1(result));
	      }
	      POP_UNWIND_PROTECT(2);
	      if (namestring_for_user) {
		  if ( !EQ(namestring_for_user,Qunbound_in_protected_let))
		      reclaim_text_string(namestring_for_user);
	      }
	      CONTINUE_UNWINDING(2);
	      result = RESTORE_VALUES();
	      result_from_body = result;
	  }
	  else
	      result_from_body = CATCH_VALUES();
	  POP_CATCH(3);
	  if (Gensym_file_error_occurred_p) {
	      gensymed_symbol_2 = result_from_body;
	      control_string = CAR(gensymed_symbol_2);
	      error_args = CDR(gensymed_symbol_2);
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
	      notify_user(2,string_constant_50,report_string);
	      reclaim_text_string(report_string);
	      result = VALUES_1(Nil);
	  }
	  else
	      result = VALUES_1(result_from_body);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* WRITE-G2-STRING-STATS-HEADER */
Object write_g2_string_stats_header(message_1)
    Object message_1;
{
    Object log_simple_string_data, inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p, namestring_1;
    volatile Object namestring_for_user;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object open_g2_stream_qm;
    Object temp;
    volatile Object error_string_for_user;
    Object result_from_body, gensymed_symbol, control_string, error_args;
    Object error_arg, ab_loop_list_, report_string;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(3);
    Object result;

    x_note_fn_call(245,64);
    SAVE_STACK();
    log_simple_string_data = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Log_simple_string_data,Qlog_simple_string_data,log_simple_string_data,
	    2);
      inside_handling_gensym_file_errors_scope_p = T;
      gensym_file_error_occurred_p = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
		0);
	  if (PUSH_CATCH(Qgensym_file_error_catch_tag,3)) {
	      namestring_1 = Qunbound_in_protected_let;
	      namestring_for_user = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(2)) {
		  namestring_1 = Simple_string_stats_namestring;
		  namestring_for_user = copy_text_string(namestring_1);
		  if (g2_stream_probe_file_for_exist(Simple_string_stats_namestring)) 
			      {
		      pathname_used_p = Qunbound_in_protected_let;
		      namestring_2 = Qunbound_in_protected_let;
		      open_g2_stream_qm = Qunbound_in_protected_let;
		      if (PUSH_UNWIND_PROTECT(1)) {
			  pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ?
				   (EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? T : Nil) : Qnil;
			  namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
				  EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? gensym_namestring(1,namestring_1) : 
				  namestring_1;
			  open_g2_stream_qm = 
				  g2_stream_open_for_appending(namestring_2,
				  Nil);
			  if (open_g2_stream_qm) {
			      write_g2_string_stats_header_to_stream(open_g2_stream_qm,
				      message_1);
			      Simple_string_stats_header_needed = Nil;
			      temp = T;
			  }
			  else {
			      error_string_for_user = 
				      Qunbound_in_protected_let;
			      if (PUSH_UNWIND_PROTECT(0)) {
				  temp = 
					  assq_function(Internal_status_of_most_recent_file_operation,
					  G2_stream_error_string_table);
				  temp = CDR(temp);
				  if (temp);
				  else {
				      if (Cached_unknown_error_string_with_code_qm)
					  reclaim_text_string(Cached_unknown_error_string_with_code_qm);
				      Cached_unknown_error_string_with_code_qm 
					      = tformat_text_string(2,
					      Unknown_error_during_file_op_with_code_message,
					      Internal_status_of_most_recent_file_operation);
				      temp = 
					      Cached_unknown_error_string_with_code_qm;
				  }
				  error_string_for_user = 
					  import_text_string(2,temp,
					  Qg2_stream_error_string);
				  notify_user(3,string_constant_46,
					  namestring_for_user,
					  error_string_for_user);
			      }
			      POP_UNWIND_PROTECT(0);
			      if (error_string_for_user) {
				  if ( !EQ(error_string_for_user,
					  Qunbound_in_protected_let))
				      reclaim_text_string(error_string_for_user);
			      }
			      CONTINUE_UNWINDING(0);
			      temp = Nil;
			  }
			  SAVE_VALUES(VALUES_1(temp));
		      }
		      POP_UNWIND_PROTECT(1);
		      if (open_g2_stream_qm) {
			  if ( !EQ(open_g2_stream_qm,
				  Qunbound_in_protected_let))
			      g2_stream_close(open_g2_stream_qm);
		      }
		      if (namestring_2) {
			  if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
			      if (pathname_used_p)
				  reclaim_text_string(namestring_2);
			  }
		      }
		      CONTINUE_UNWINDING(1);
		      result = RESTORE_VALUES();
		      temp = result;
		  }
		  else {
		      pathname_used_p = Qunbound_in_protected_let;
		      namestring_2 = Qunbound_in_protected_let;
		      open_g2_stream_qm = Qunbound_in_protected_let;
		      if (PUSH_UNWIND_PROTECT(1)) {
			  pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ?
				   (EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? T : Nil) : Qnil;
			  namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
				  EQ(ISVREF(namestring_1,(SI_Long)0L),
				  Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
				  ? gensym_namestring(1,namestring_1) : 
				  namestring_1;
			  open_g2_stream_qm = 
				  g2_stream_open_for_output(namestring_2);
			  if (open_g2_stream_qm) {
			      write_g2_string_stats_header_to_stream(open_g2_stream_qm,
				      message_1);
			      Simple_string_stats_header_needed = Nil;
			      temp = T;
			  }
			  else {
			      error_string_for_user = 
				      Qunbound_in_protected_let;
			      if (PUSH_UNWIND_PROTECT(0)) {
				  temp = 
					  assq_function(Internal_status_of_most_recent_file_operation,
					  G2_stream_error_string_table);
				  temp = CDR(temp);
				  if (temp);
				  else {
				      if (Cached_unknown_error_string_with_code_qm)
					  reclaim_text_string(Cached_unknown_error_string_with_code_qm);
				      Cached_unknown_error_string_with_code_qm 
					      = tformat_text_string(2,
					      Unknown_error_during_file_op_with_code_message,
					      Internal_status_of_most_recent_file_operation);
				      temp = 
					      Cached_unknown_error_string_with_code_qm;
				  }
				  error_string_for_user = 
					  import_text_string(2,temp,
					  Qg2_stream_error_string);
				  notify_user(3,string_constant_46,
					  namestring_for_user,
					  error_string_for_user);
			      }
			      POP_UNWIND_PROTECT(0);
			      if (error_string_for_user) {
				  if ( !EQ(error_string_for_user,
					  Qunbound_in_protected_let))
				      reclaim_text_string(error_string_for_user);
			      }
			      CONTINUE_UNWINDING(0);
			      temp = Nil;
			  }
			  SAVE_VALUES(VALUES_1(temp));
		      }
		      POP_UNWIND_PROTECT(1);
		      if (open_g2_stream_qm) {
			  if ( !EQ(open_g2_stream_qm,
				  Qunbound_in_protected_let))
			      g2_stream_close(open_g2_stream_qm);
		      }
		      if (namestring_2) {
			  if ( !EQ(namestring_2,Qunbound_in_protected_let)) {
			      if (pathname_used_p)
				  reclaim_text_string(namestring_2);
			  }
		      }
		      CONTINUE_UNWINDING(1);
		      result = RESTORE_VALUES();
		      temp = result;
		  }
		  SAVE_VALUES(VALUES_1(temp));
	      }
	      POP_UNWIND_PROTECT(2);
	      if (namestring_for_user) {
		  if ( !EQ(namestring_for_user,Qunbound_in_protected_let))
		      reclaim_text_string(namestring_for_user);
	      }
	      CONTINUE_UNWINDING(2);
	      result = RESTORE_VALUES();
	      result_from_body = result;
	  }
	  else
	      result_from_body = CATCH_VALUES();
	  POP_CATCH(3);
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
	      notify_user(2,string_constant_50,report_string);
	      reclaim_text_string(report_string);
	      result = VALUES_1(Nil);
	  }
	  else
	      result = VALUES_1(result_from_body);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_51;  /* "Reporting one string in every ~a of length over ~a" */

static Object string_constant_52;  /* "Metering both allocations and reclamations" */

static Object string_constant_53;  /* "Printing out up to ~a characters from reclaimed strings" */

/* WRITE-G2-STRING-STATS-HEADER-TO-STREAM */
Object write_g2_string_stats_header_to_stream(stream,message_1)
    Object stream, message_1;
{
    Object summary_string;

    x_note_fn_call(245,65);
    write_g2_stats_header(stream);
    summary_string = tformat_text_string(3,string_constant_51,
	    String_report_frequency,Min_string_length_to_report);
    g2_stream_write_line(summary_string,stream);
    reclaim_text_string(summary_string);
    summary_string = tformat_text_string(1,Log_simple_string_reclaims ? 
	    string_constant_52 : string_constant_45);
    g2_stream_write_line(summary_string,stream);
    reclaim_text_string(summary_string);
    if (Log_simple_string_reclaims) {
	summary_string = tformat_text_string(2,string_constant_53,
		String_chars_to_print);
	g2_stream_write_line(summary_string,stream);
	reclaim_text_string(summary_string);
    }
    g2_stream_write_line(message_1,stream);
    if (message_1)
	return g2_stream_write_line(array_constant_1,stream);
    else
	return VALUES_1(Nil);
}

/* REPLACE-NULLS-BY-SPACES */
Object replace_nulls_by_spaces(string_1)
    Object string_1;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(245,66);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(string_1));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(CHR(ISCHAR(string_1,index_1)),CHR('\000')))
	SET_ISCHAR(string_1,index_1,' ');
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(string_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Input_string_for_backtrace_text_buffer_for_string_metering, Qinput_string_for_backtrace_text_buffer_for_string_metering);

DEFINE_VARIABLE_WITH_SYMBOL(Backtrace_text_buffer_for_string_metering, Qbacktrace_text_buffer_for_string_metering);

DEFINE_VARIABLE_WITH_SYMBOL(Input_gensym_string_for_buffer_for_string_metering, Qinput_gensym_string_for_buffer_for_string_metering);

DEFINE_VARIABLE_WITH_SYMBOL(Buffer_for_string_metering, Qbuffer_for_string_metering);

static Object string_constant_54;  /* "Backtrace:" */

static Object string_constant_55;  /* "~%  ~A" */

static Object string_constant_56;  /* "~%  " */

static Object string_constant_57;  /* "~%" */

/* PRINT-BACKTRACE-TO-STREAM */
Object print_backtrace_to_stream(stream)
    Object stream;
{
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object original_input_string, ch, temp, temp_1, schar_new_value;
    Object local_backtrace_stack_index, old_top_of_stack, temp_2;
    Object twrite_function_qm, number_of_args, index_of_top_of_backtrace_stack;
    Object gensymed_symbol, gensymed_symbol_2;
    SI_Long length_1, len, i, ab_loop_bind_, simple_or_wide_character, thing;
    SI_Long bv16_length, aref_arg_2, aref_new_value, arg, arg_1, arg_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;
    char temp_3;
    Declare_special(6);

    x_note_fn_call(245,67);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    5);
      current_wide_string = 
	      Input_string_for_backtrace_text_buffer_for_string_metering;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      4);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		3);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  2);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    1);
	      original_input_string = 
		      Input_string_for_backtrace_text_buffer_for_string_metering;
	      inline_get_backtrace();
	      len = 
		      inline_print_backtrace_into_string(ISTRING(Buffer_for_string_metering),
		      (SI_Long)0L);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = len;
	      ch = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      ch = CHR(ICHAR(Buffer_for_string_metering,i));
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
	      tformat(1,string_constant_54);
	      local_backtrace_stack_index = Index_of_top_of_backtrace_stack;
	    next_loop_1:
	      if (IFIX(local_backtrace_stack_index) < (SI_Long)0L)
		  goto end_loop_1;
	      old_top_of_stack = local_backtrace_stack_index;
	      if (IFIX(local_backtrace_stack_index) < (SI_Long)0L)
		  temp_2 = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(local_backtrace_stack_index));
		  local_backtrace_stack_index = 
			  FIXNUM_SUB1(local_backtrace_stack_index);
	      }
	      tformat(2,string_constant_55,temp_2);
	      if (IFIX(local_backtrace_stack_index) < (SI_Long)0L)
		  twrite_function_qm = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(local_backtrace_stack_index));
		  local_backtrace_stack_index = 
			  FIXNUM_SUB1(local_backtrace_stack_index);
		  twrite_function_qm = temp_2;
	      }
	      if (IFIX(local_backtrace_stack_index) < (SI_Long)0L)
		  number_of_args = Nil;
	      else {
		  temp_2 = ISVREF(Backtrace_stack_for_internal_error,
			  IFIX(local_backtrace_stack_index));
		  local_backtrace_stack_index = 
			  FIXNUM_SUB1(local_backtrace_stack_index);
		  number_of_args = temp_2;
	      }
	      if (twrite_function_qm) {
		  tformat(1,string_constant_56);
		  index_of_top_of_backtrace_stack = 
			  local_backtrace_stack_index;
		  PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			  0);
		    FUNCALL_0(twrite_function_qm);
		  POP_SPECIAL();
	      }
	      local_backtrace_stack_index = FIXNUM_MINUS(old_top_of_stack,
		      FIXNUM_ADD(number_of_args,
		      Size_of_basic_backtrace_information));
	      goto next_loop_1;
	    end_loop_1:
	      tformat(1,string_constant_57);
	      if ( !EQ(Current_wide_string,original_input_string))
		  Input_string_for_backtrace_text_buffer_for_string_metering 
			  = Current_wide_string;
	      temp = Backtrace_text_buffer_for_string_metering;
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
		      Backtrace_text_buffer_for_string_metering)) {
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
				  Backtrace_text_buffer_for_string_metering,
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
		  gensymed_symbol_2 = 
			  Backtrace_text_buffer_for_string_metering;
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
    return g2_stream_write_line(Backtrace_text_buffer_for_string_metering,
	    stream);
}

/* WRITE-PADDED-STRING */
Object write_padded_string(g2_stream,string_1,pad_char,field_size,pad_left_qm)
    Object g2_stream, string_1, pad_char, field_size, pad_left_qm;
{
    SI_Long length_1, string_length, index_1, ab_loop_bind_, ab_loop_repeat_;

    x_note_fn_call(245,68);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L) {
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	string_length = UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) 
		+ ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
		(SI_Long)8191L) << (SI_Long)16L);
    }
    else
	string_length = IFIX(length(string_1));
    if (string_length > IFIX(field_size)) {
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(field_size);
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    g2_stream_write_char(FIX(UBYTE_16_ISAREF_1(string_1,index_1)),
		    g2_stream);
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(field_size);
	  next_loop_1:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_1;
	    g2_stream_write_char(CHR(ICHAR(string_1,index_1)),g2_stream);
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
    }
    else {
	if ( !TRUEP(pad_left_qm))
	    g2_stream_write_string(string_1,g2_stream);
	ab_loop_repeat_ = IFIX(field_size) - string_length;
      next_loop_2:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_2;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	g2_stream_write_char(pad_char,g2_stream);
	goto next_loop_2;
      end_loop_2:;
	if (pad_left_qm)
	    return g2_stream_write_string(string_1,g2_stream);
	else
	    return VALUES_1(Nil);
    }
}

static Object string_constant_58;  /* "Overall Memory Usage Statistics" */

static Object string_constant_59;  /* "Total Memory Usage             = ~a" */

static Object string_constant_60;  /* "Total Pool Memory Usage        = ~a" */

static Object string_constant_61;  /* "Total Pool Objects Outstanding = ~a" */

static Object string_constant_62;  /* "Total Pool Objects Allocated   = ~a" */

/* WRITE-GLOBAL-MEMORY-STATISTICS */
Object write_global_memory_statistics(output)
    Object output;
{
    Object string_var;

    x_note_fn_call(245,69);
    g2_stream_write_line(string_constant_58,output);
    string_var = tformat_text_string(2,string_constant_59,g2_memory_usage());
    g2_stream_write_line(string_var,output);
    reclaim_text_string(string_var);
    string_var = tformat_text_string(2,string_constant_60,
	    total_pool_memory_usage());
    g2_stream_write_line(string_var,output);
    reclaim_text_string(string_var);
    string_var = tformat_text_string(2,string_constant_61,
	    total_pool_outstanding_object_count());
    g2_stream_write_line(string_var,output);
    reclaim_text_string(string_var);
    string_var = tformat_text_string(2,string_constant_62,
	    total_pool_object_count());
    g2_stream_write_line(string_var,output);
    return reclaim_text_string(string_var);
}

/* PRIORITY-10-SCHEDULER-TIME-LAG */
Object priority_10_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,70);
    temp = scheduler_time_lag(FIX((SI_Long)10L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-9-SCHEDULER-TIME-LAG */
Object priority_9_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,71);
    temp = scheduler_time_lag(FIX((SI_Long)9L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-8-SCHEDULER-TIME-LAG */
Object priority_8_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,72);
    temp = scheduler_time_lag(FIX((SI_Long)8L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-7-SCHEDULER-TIME-LAG */
Object priority_7_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,73);
    temp = scheduler_time_lag(FIX((SI_Long)7L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-6-SCHEDULER-TIME-LAG */
Object priority_6_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,74);
    temp = scheduler_time_lag(FIX((SI_Long)6L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-5-SCHEDULER-TIME-LAG */
Object priority_5_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,75);
    temp = scheduler_time_lag(FIX((SI_Long)5L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-4-SCHEDULER-TIME-LAG */
Object priority_4_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,76);
    temp = scheduler_time_lag(FIX((SI_Long)4L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-3-SCHEDULER-TIME-LAG */
Object priority_3_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,77);
    temp = scheduler_time_lag(FIX((SI_Long)3L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-2-SCHEDULER-TIME-LAG */
Object priority_2_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,78);
    temp = scheduler_time_lag(FIX((SI_Long)2L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

/* PRIORITY-1-SCHEDULER-TIME-LAG */
Object priority_1_scheduler_time_lag()
{
    Object temp, gensymed_symbol_1;
    double temp_1, gensymed_symbol;

    x_note_fn_call(245,79);
    temp = scheduler_time_lag(FIX((SI_Long)1L));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    gensymed_symbol = temp_1 - 1.0;
    gensymed_symbol_1 = float_constant;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,temp_1)));
}

void g2_meters_INIT()
{
    Object temp, temp_1, reclaim_structure_for_class_instances_memory_info_1;
    Object system_statistics_writers_new_value, gensymed_symbol;
    Object wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    Object string_constant_98, string_constant_97;
    Object Qpriority_10_scheduler_time_lag, Qpriority_9_scheduler_time_lag;
    Object Qpriority_8_scheduler_time_lag, Qpriority_7_scheduler_time_lag;
    Object Qpriority_6_scheduler_time_lag, Qpriority_5_scheduler_time_lag;
    Object Qpriority_4_scheduler_time_lag, Qpriority_3_scheduler_time_lag;
    Object Qpriority_2_scheduler_time_lag, Qpriority_1_scheduler_time_lag;
    Object list_constant_116, list_constant_115, list_constant_114;
    Object list_constant_113, list_constant_112, list_constant_111;
    Object list_constant_110, list_constant_109, list_constant_108;
    Object list_constant_107, list_constant_106, list_constant_105, AB_package;
    Object list_constant_104, list_constant_103, list_constant_102;
    Object list_constant_101, list_constant_100, list_constant_99;
    Object list_constant_98, list_constant_97, list_constant_96;
    Object string_constant_96, list_constant_95, list_constant_94;
    Object list_constant_93, Qregion_3_memory_size_as_float, list_constant_56;
    Object Qg2_region_memory_size_as_float, string_constant_95;
    Object list_constant_92, list_constant_91, list_constant_90;
    Object Qregion_3_memory_size, Qg2_region_memory_size, string_constant_94;
    Object list_constant_89, list_constant_88, list_constant_87;
    Object Qregion_2_memory_size_as_float, list_constant_49;
    Object string_constant_93, list_constant_86, list_constant_85;
    Object list_constant_84, Qregion_2_memory_size, string_constant_92;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object Qregion_1_memory_size_as_float, list_constant_42;
    Object string_constant_91, list_constant_80, list_constant_79;
    Object list_constant_78, Qregion_1_memory_size, string_constant_90;
    Object list_constant_77, list_constant_76, list_constant_75;
    Object Qregion_3_memory_available_as_float;
    Object Qg2_region_memory_available_as_float, string_constant_89;
    Object list_constant_74, list_constant_73, list_constant_72;
    Object Qregion_3_memory_available, string_constant_88, list_constant_71;
    Object list_constant_70, list_constant_69;
    Object Qregion_2_memory_available_as_float, string_constant_87;
    Object list_constant_68, list_constant_67, list_constant_66;
    Object Qregion_2_memory_available, string_constant_86, list_constant_65;
    Object list_constant_64, list_constant_63;
    Object Qregion_1_memory_available_as_float, string_constant_85;
    Object list_constant_62, list_constant_61, list_constant_60;
    Object Qregion_1_memory_available, string_constant_84, list_constant_59;
    Object list_constant_58, list_constant_57, Qregion_3_memory_usage_as_float;
    Object Qg2_region_memory_usage_as_float, string_constant_83;
    Object list_constant_55, list_constant_54, list_constant_53;
    Object Qregion_3_memory_usage, Qg2_region_memory_usage, string_constant_82;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object Qregion_2_memory_usage_as_float, string_constant_81;
    Object list_constant_48, list_constant_47, list_constant_46;
    Object Qregion_2_memory_usage, string_constant_80, list_constant_45;
    Object list_constant_44, list_constant_43, Qregion_1_memory_usage_as_float;
    Object string_constant_79, list_constant_41, list_constant_40;
    Object list_constant_39, Qregion_1_memory_usage;
    Object Qmaximum_memory_regions_in_any_model, string_constant_78;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object Qmemory_available_as_float, Qg2_memory_available_as_float;
    Object string_constant_77, list_constant_35, list_constant_34;
    Object list_constant_33, Qmemory_available, string_constant_76;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object Qmemory_size_as_float, Qg2_memory_size_as_float, string_constant_75;
    Object list_constant_29, list_constant_28, list_constant_27, Qmemory_size;
    Object Qg2_memory_size, string_constant_74, list_constant_26;
    Object list_constant_25, list_constant_24, Qmemory_usage_as_float;
    Object Qg2_memory_usage_as_float, string_constant_73, list_constant_23;
    Object list_constant_22, list_constant_21, Qmemory_usage, Qg2_memory_usage;
    Object string_constant_72, list_constant_20, list_constant_19;
    Object list_constant_18, Qinstance_creation_count_as_float;
    Object Qg2_instance_creation_count_as_float, string_constant_71;
    Object Qsimulator_time_lag, list_constant_17, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object string_constant_70, list_constant_12, list_constant_11;
    Object list_constant_10, Qclock_tick_length, string_constant_69;
    Object list_constant_9, list_constant_8, list_constant_7;
    Object Qpercent_run_time, Qwrite_global_memory_statistics;
    Object Qlength_of_buffer_for_string_metering;
    Object Qlength_of_backtrace_text_buffer_for_string_metering;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_simple_string_metering_exclude_reclaims, list_constant_6;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_simple_string_metering_include_reclaims;
    Object Qg2_turn_off_simple_string_metering;
    Object Qg2_turn_on_simple_string_metering;
    Object Qg2_set_simple_string_metering_parameters, array_constant_21;
    Object Qwrite_pool_memory_usage, Qwrite_lru_queue_statistics;
    Object Qwrite_string_pool_statistics;
    Object Qwrite_byte_vector_16_pool_statistics;
    Object Qwrite_simple_vector_pool_statistics;
    Object Qwrite_frame_vector_pool_statistics;
    Object Qwrite_user_objects_memory_usage, array_constant_20;
    Object Qdelta_memory_column_title, array_constant_19;
    Object Qconsumed_memory_column_title, array_constant_18;
    Object Qdelta_instances_column_title, array_constant_17;
    Object Qinstances_count_column_title, array_constant_16;
    Object Qclass_name_column_title, Qspaces_between_columns;
    Object Qclass_instances_memory_info, Qreclaim_structure;
    Object Qoutstanding_class_instances_memory_info_count;
    Object Qclass_instances_memory_info_structure_memory_usage, Qutilities2;
    Object string_constant_68, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_67, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qout_uo_memory_usage_information_hash_vector_43_vectors;
    Object Quo_memory_usage_information_hash_vector_43_vector_memory_usage;
    Object string_constant_66, list_constant_5, Qrun;
    Object Qmake_boxed_floating_zero, Kfuncall;
    Object Qshut_down_g2_meter_data_server;
    Object Qset_external_variable_for_g2_meter;
    Object Qinitialize_g2_meter_data_server, Qaccept_data_from_g2_meters;
    Object Qstop_collecting_data_for_g2_meters;
    Object Qbegin_collecting_data_for_g2_meters, Qpost_on_message_board;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_g2_meter_name_for_slot;
    Object Qwrite_g2_meter_name_from_slot, list_constant_4, list_constant_3;
    Object list_constant_2, Qslot_putter, Qput_g2_meter_name;
    Object string_constant_65, list_constant_1, string_constant_64;
    Object string_constant_63;

    x_note_fn_call(245,80);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_meter_data_service = STATIC_SYMBOL("G2-METER-DATA-SERVICE",AB_package);
    list_constant_1 = STATIC_CONS(Qvariable,Qnil);
    check_if_superior_classes_are_defined(Qg2_meter_data_service,
	    list_constant_1);
    string_constant_63 = 
	    STATIC_STRING("1q1l8t1m830ky83*dy1m8v83*dy1l83-8y1l83Iy1l83Ly");
    string_constant_64 = 
	    STATIC_STRING("1m4z8r83*My83*My838Vy838Vy083CAy001o1l8o1l8l1m8p83*My1l8z000004z8r83*Dy83*Dy838Vy838Vy00001p1l83Ey1l8l1l8z1l83Cy1m8p83*Dy00000");
    string_constant_65 = 
	    STATIC_STRING("1o8q1s838Vy1l83*dy8t1m830ky83*dy1m8v83*dy83-8y83Iy83Ly1p83*My83CAy1l8o1l8l1m8p83*My1r83*Dy01l83Ey1l8l8z1l83Cy1m8p83*Dy");
    temp = regenerate_optimized_constant(string_constant_63);
    temp_1 = regenerate_optimized_constant(string_constant_64);
    add_class_to_environment(9,Qg2_meter_data_service,list_constant_1,Nil,
	    temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_65),Nil);
    Qg2_region_memory_allocatable = 
	    STATIC_SYMBOL("G2-REGION-MEMORY-ALLOCATABLE",AB_package);
    Qg2_region_memory_available = 
	    STATIC_SYMBOL("G2-REGION-MEMORY-AVAILABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_available,
	    STATIC_FUNCTION(g2_region_memory_available,NIL,FALSE,1,1));
    Qg2_memory_allocatable = STATIC_SYMBOL("G2-MEMORY-ALLOCATABLE",AB_package);
    Qg2_memory_available = STATIC_SYMBOL("G2-MEMORY-AVAILABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_available,
	    STATIC_FUNCTION(g2_memory_available,NIL,FALSE,0,0));
    Qg2_meter_name = STATIC_SYMBOL("G2-METER-NAME",AB_package);
    Qput_g2_meter_name = STATIC_SYMBOL("PUT-G2-METER-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_meter_name,
	    STATIC_FUNCTION(put_g2_meter_name,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qg2_meter_name,
	    SYMBOL_FUNCTION(Qput_g2_meter_name),Qslot_putter);
    if (G2_meter_names_and_forms == UNBOUND)
	G2_meter_names_and_forms = Nil;
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qquote,Qnone);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qg2_meter_name,list_constant_2);
    list_constant_4 = STATIC_CONS(list_constant_3,Qnil);
    add_grammar_rules_function(list_constant_4);
    string_constant = STATIC_STRING("none");
    Qwrite_g2_meter_name_from_slot = 
	    STATIC_SYMBOL("WRITE-G2-METER-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_g2_meter_name_from_slot,
	    STATIC_FUNCTION(write_g2_meter_name_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qg2_meter_name,
	    SYMBOL_FUNCTION(Qwrite_g2_meter_name_from_slot),
	    Qslot_value_writer);
    string_constant_1 = 
	    STATIC_STRING("The name ~a is not among the set of defined G2 meter names.");
    Qcompile_g2_meter_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-G2-METER-NAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_g2_meter_name_for_slot,
	    STATIC_FUNCTION(compile_g2_meter_name_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qg2_meter_name,
	    SYMBOL_FUNCTION(Qcompile_g2_meter_name_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qg2_meter_name,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qg2_meter_data_server = STATIC_SYMBOL("G2-METER-DATA-SERVER",AB_package);
    Qcollect_one_shot_data_for_g2_meters = 
	    STATIC_SYMBOL("COLLECT-ONE-SHOT-DATA-FOR-G2-METERS",AB_package);
    Qbegin_collecting_data_for_g2_meters = 
	    STATIC_SYMBOL("BEGIN-COLLECTING-DATA-FOR-G2-METERS",AB_package);
    Qstop_collecting_data_for_g2_meters = 
	    STATIC_SYMBOL("STOP-COLLECTING-DATA-FOR-G2-METERS",AB_package);
    Qaccept_data_from_g2_meters = 
	    STATIC_SYMBOL("ACCEPT-DATA-FROM-G2-METERS",AB_package);
    Qinitialize_g2_meter_data_server = 
	    STATIC_SYMBOL("INITIALIZE-G2-METER-DATA-SERVER",AB_package);
    Qset_external_variable_for_g2_meter = 
	    STATIC_SYMBOL("SET-EXTERNAL-VARIABLE-FOR-G2-METER",AB_package);
    Qshut_down_g2_meter_data_server = 
	    STATIC_SYMBOL("SHUT-DOWN-G2-METER-DATA-SERVER",AB_package);
    Qpost_on_message_board = STATIC_SYMBOL("POST-ON-MESSAGE-BOARD",AB_package);
    def_data_server(13,Qg2_meter_data_server,
	    Qcollect_one_shot_data_for_g2_meters,
	    Qbegin_collecting_data_for_g2_meters,
	    Qstop_collecting_data_for_g2_meters,
	    Qaccept_data_from_g2_meters,Nil,
	    Qinitialize_g2_meter_data_server,
	    Qset_external_variable_for_g2_meter,
	    Qshut_down_g2_meter_data_server,Qpost_on_message_board,Nil,Nil,
	    Nil);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qunknown_g2_meter_data_type = 
	    STATIC_SYMBOL("UNKNOWN-G2-METER-DATA-TYPE",AB_package);
    string_constant_2 = STATIC_STRING("The variable ~NF ~A, ~A");
    string_constant_3 = 
	    STATIC_STRING("attempted to get a value from G2 meter data service");
    string_constant_4 = 
	    STATIC_STRING("but its class has not been declared to have that capability.");
    string_constant_5 = 
	    string_append2(STATIC_STRING("The variable ~NF attempted to get a value from the G2 ~\n                              meter data service, but it had no G2 meter name ~\n                              specified"),
	    STATIC_STRING("."));
    Qsimulator_time_lag = STATIC_SYMBOL("SIMULATOR-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qsimulator_time_lag,
	    STATIC_FUNCTION(simulator_time_lag,NIL,FALSE,0,0));
    list_constant = STATIC_CONS(Qsimulator_time_lag,Qnil);
    string_constant_6 = 
	    STATIC_STRING("The variable ~NF attempted to get a value for the ~\n                          simulator time lag, but the simulator is not on.");
    string_constant_7 = 
	    string_append2(STATIC_STRING("The variable ~NF attempted to get a value from the G2 ~\n                          meter data service, but the meter\'s function failed ~\n                          to return a v"),
	    STATIC_STRING("alue.  This is a G2 internal error!"));
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_8 = 
	    STATIC_STRING("The variable ~NF attempted to get a value from ~\n                            the G2 meter data service for the meter ");
    string_constant_9 = STATIC_STRING("[deleted attribute]");
    string_constant_10 = 
	    STATIC_STRING(", but failed since this meter was not defined.  ~\n\t\t\t    This is a G2 internal error!");
    string_constant_11 = 
	    string_append2(STATIC_STRING("The variable ~NF attempted to get a value from the G2 Meter Data Server~\n\t , but the G2 Meter Data Server was not turned on.  Change the G2 ~\n         meter data service on\? a"),
	    STATIC_STRING("ttribute of the data-server-parameters system ~\n         table to enable data service to the variable."));
    SET_SYMBOL_FUNCTION(Qcollect_one_shot_data_for_g2_meters,
	    STATIC_FUNCTION(collect_one_shot_data_for_g2_meters,NIL,FALSE,
	    1,1));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qbegin_collecting_data_for_g2_meters,
	    STATIC_FUNCTION(begin_collecting_data_for_g2_meters,NIL,FALSE,
	    2,2));
    SET_SYMBOL_FUNCTION(Qstop_collecting_data_for_g2_meters,
	    STATIC_FUNCTION(stop_collecting_data_for_g2_meters,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qaccept_data_from_g2_meters,
	    STATIC_FUNCTION(accept_data_from_g2_meters,NIL,FALSE,0,0));
    Qg2_meter_data_service_on_qm = 
	    STATIC_SYMBOL("G2-METER-DATA-SERVICE-ON\?",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_g2_meter_data_server,
	    STATIC_FUNCTION(initialize_g2_meter_data_server,NIL,FALSE,0,0));
    string_constant_12 = 
	    STATIC_STRING("An attempt was made to set the external value of the sensor ~NF, ");
    string_constant_13 = 
	    STATIC_STRING("which gets data service through the G2 meter server for the meter ");
    string_constant_14 = STATIC_STRING(", to the value ");
    string_constant_15 = 
	    STATIC_STRING(".  The set operation is not allowed within this data server.");
    SET_SYMBOL_FUNCTION(Qset_external_variable_for_g2_meter,
	    STATIC_FUNCTION(set_external_variable_for_g2_meter,NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qshut_down_g2_meter_data_server,
	    STATIC_FUNCTION(shut_down_g2_meter_data_server,NIL,FALSE,0,0));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qpercent_running = STATIC_SYMBOL("PERCENT-RUNNING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpercent_running,Percent_running);
    Qrun = STATIC_SYMBOL("RUN",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_boxed_floating_zero = STATIC_SYMBOL("MAKE-BOXED-FLOATING-ZERO",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_boxed_floating_zero,
	    STATIC_FUNCTION(make_boxed_floating_zero,NIL,FALSE,0,0));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_boxed_floating_zero);
    record_system_variable(Qpercent_running,Qrun,list_constant_5,Qnil,Qnil,
	    Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qpercent_running,STATIC_FUNCTION(percent_running,
	    NIL,FALSE,0,0));
    Qmetered_clock_tick_length = STATIC_SYMBOL("METERED-CLOCK-TICK-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmetered_clock_tick_length,
	    Metered_clock_tick_length);
    record_system_variable(Qmetered_clock_tick_length,Qrun,list_constant_5,
	    Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qmetered_clock_tick_length,
	    STATIC_FUNCTION(metered_clock_tick_length,NIL,FALSE,0,0));
    Qmaximum_clock_tick_length = STATIC_SYMBOL("MAXIMUM-CLOCK-TICK-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_clock_tick_length,
	    Maximum_clock_tick_length);
    record_system_variable(Qmaximum_clock_tick_length,Qrun,list_constant_5,
	    Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qmaximum_clock_tick_length,
	    STATIC_FUNCTION(maximum_clock_tick_length,NIL,FALSE,0,0));
    float_constant = STATIC_FLOAT(0.0);
    float_constant_1 = STATIC_FLOAT(1.0);
    string_constant_16 = STATIC_STRING("G2 Run Time Statistics");
    string_constant_17 = STATIC_STRING("G2 ");
    Qavailable_uo_memory_usage_information_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_uo_memory_usage_information_hash_vector_43_vectors,
	    Available_uo_memory_usage_information_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_uo_memory_usage_information_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_uo_memory_usage_information_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_uo_memory_usage_information_hash_vector_43_vectors,
	    Count_of_uo_memory_usage_information_hash_vector_43_vectors);
    record_system_variable(Qcount_of_uo_memory_usage_information_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_uo_memory_usage_information_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_uo_memory_usage_information_hash_vector_43_vectors_vector 
		= make_thread_array(Nil);
    Qout_uo_memory_usage_information_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Quo_memory_usage_information_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("UO-MEMORY-USAGE-INFORMATION-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_66 = STATIC_STRING("1q83-vPy83*9y83-PGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_uo_memory_usage_information_hash_vector_43_vectors);
    push_optimized_constant(Quo_memory_usage_information_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_66));
    SET_SYMBOL_FUNCTION(Quo_memory_usage_information_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(uo_memory_usage_information_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_uo_memory_usage_information_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_uo_memory_usage_information_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Quo_memory_usage_information_tree_for_hash = 
	    STATIC_SYMBOL("UO-MEMORY-USAGE-INFORMATION-TREE-FOR-HASH",
	    AB_package);
    if (Uo_memory_usage_information_hash_table == UNBOUND)
	Uo_memory_usage_information_hash_table = 
		make_uo_memory_usage_information();
    Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct = 
	    STATIC_SYMBOL("CLASS-INSTANCES-MEMORY-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qclass_instances_memory_info = 
	    STATIC_SYMBOL("CLASS-INSTANCES-MEMORY-INFO",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct,
	    Qclass_instances_memory_info,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qclass_instances_memory_info,
	    Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_class_instances_memory_info == UNBOUND)
	The_type_description_of_class_instances_memory_info = Nil;
    string_constant_67 = 
	    STATIC_STRING("43Dy8m83fsy1n83fsy8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_class_instances_memory_info;
    The_type_description_of_class_instances_memory_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_67));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_instances_memory_info_g2_struct,
	    The_type_description_of_class_instances_memory_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qclass_instances_memory_info,
	    The_type_description_of_class_instances_memory_info,
	    Qtype_description_of_type);
    Qoutstanding_class_instances_memory_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-INSTANCES-MEMORY-INFO-COUNT",
	    AB_package);
    Qclass_instances_memory_info_structure_memory_usage = 
	    STATIC_SYMBOL("CLASS-INSTANCES-MEMORY-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_68 = STATIC_STRING("1q83fsy8s83-MZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_instances_memory_info_count);
    push_optimized_constant(Qclass_instances_memory_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qchain_of_available_class_instances_memory_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLASS-INSTANCES-MEMORY-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_class_instances_memory_infos,
	    Chain_of_available_class_instances_memory_infos);
    record_system_variable(Qchain_of_available_class_instances_memory_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qclass_instances_memory_info_count = 
	    STATIC_SYMBOL("CLASS-INSTANCES-MEMORY-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_instances_memory_info_count,
	    Class_instances_memory_info_count);
    record_system_variable(Qclass_instances_memory_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_class_instances_memory_infos_vector == UNBOUND)
	Chain_of_available_class_instances_memory_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclass_instances_memory_info_structure_memory_usage,
	    STATIC_FUNCTION(class_instances_memory_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_class_instances_memory_info_count,
	    STATIC_FUNCTION(outstanding_class_instances_memory_info_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_class_instances_memory_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_class_instances_memory_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qclass_instances_memory_info,
	    reclaim_structure_for_class_instances_memory_info_1);
    if (Class_name_max_length == UNBOUND)
	Class_name_max_length = FIX((SI_Long)0L);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qspaces_between_columns = STATIC_SYMBOL("SPACES-BETWEEN-COLUMNS",
	    AB_package);
    SET_SYMBOL_VALUE(Qspaces_between_columns,FIX((SI_Long)6L));
    Qclass_name_column_title = STATIC_SYMBOL("CLASS-NAME-COLUMN-TITLE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_name_column_title,
	    Class_name_column_title);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_16 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qclass_name_column_title,array_constant_16);
    Qinstances_count_column_title = 
	    STATIC_SYMBOL("INSTANCES-COUNT-COLUMN-TITLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinstances_count_column_title,
	    Instances_count_column_title);
    array_constant_17 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qinstances_count_column_title,array_constant_17);
    Qdelta_instances_column_title = 
	    STATIC_SYMBOL("DELTA-INSTANCES-COLUMN-TITLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdelta_instances_column_title,
	    Delta_instances_column_title);
    array_constant_18 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdelta_instances_column_title,array_constant_18);
    Qconsumed_memory_column_title = 
	    STATIC_SYMBOL("CONSUMED-MEMORY-COLUMN-TITLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconsumed_memory_column_title,
	    Consumed_memory_column_title);
    array_constant_19 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qconsumed_memory_column_title,array_constant_19);
    Qdelta_memory_column_title = STATIC_SYMBOL("DELTA-MEMORY-COLUMN-TITLE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdelta_memory_column_title,
	    Delta_memory_column_title);
    array_constant_20 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdelta_memory_column_title,array_constant_20);
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)44L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)54L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)55L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_user_objects_memory_usage = 
	    STATIC_SYMBOL("WRITE-USER-OBJECTS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_user_objects_memory_usage,
	    STATIC_FUNCTION(write_user_objects_memory_usage,NIL,FALSE,1,1));
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_user_objects_memory_usage,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    Qwrite_frame_vector_pool_statistics = 
	    STATIC_SYMBOL("WRITE-FRAME-VECTOR-POOL-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_frame_vector_pool_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_18 = STATIC_STRING("Frame Vector Pools (thread ~a)");
    Qlength_of_frame_vector_chain = 
	    STATIC_SYMBOL("LENGTH-OF-FRAME-VECTOR-CHAIN",AB_package);
    SET_SYMBOL_FUNCTION(Qlength_of_frame_vector_chain,
	    STATIC_FUNCTION(length_of_frame_vector_chain,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qwrite_frame_vector_pool_statistics,
	    STATIC_FUNCTION(write_frame_vector_pool_statistics,NIL,FALSE,1,1));
    Qwrite_simple_vector_pool_statistics = 
	    STATIC_SYMBOL("WRITE-SIMPLE-VECTOR-POOL-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_simple_vector_pool_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_19 = STATIC_STRING("Simple Vector Pools");
    Qlength_of_vector_chain = STATIC_SYMBOL("LENGTH-OF-VECTOR-CHAIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qlength_of_vector_chain,
	    STATIC_FUNCTION(length_of_vector_chain,NIL,FALSE,1,1));
    string_constant_20 = STATIC_STRING("Oversized Simple Vector Pools");
    SET_SYMBOL_FUNCTION(Qwrite_simple_vector_pool_statistics,
	    STATIC_FUNCTION(write_simple_vector_pool_statistics,NIL,FALSE,
	    1,1));
    Qwrite_byte_vector_16_pool_statistics = 
	    STATIC_SYMBOL("WRITE-BYTE-VECTOR-16-POOL-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_byte_vector_16_pool_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_21 = STATIC_STRING("Byte-vector-16 Pools");
    SET_SYMBOL_FUNCTION(Qwrite_byte_vector_16_pool_statistics,
	    STATIC_FUNCTION(write_byte_vector_16_pool_statistics,NIL,FALSE,
	    1,1));
    Qwrite_string_pool_statistics = 
	    STATIC_SYMBOL("WRITE-STRING-POOL-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_string_pool_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_22 = STATIC_STRING("Short Simple Text String Pools");
    string_constant_23 = STATIC_STRING("Long Simple Text String Pools");
    string_constant_24 = STATIC_STRING("Adjustable Text String Pools");
    SET_SYMBOL_FUNCTION(Qwrite_string_pool_statistics,
	    STATIC_FUNCTION(write_string_pool_statistics,NIL,FALSE,1,1));
    string_constant_25 = STATIC_STRING("   ");
    string_constant_26 = STATIC_STRING("Length    Out Count %Out");
    Qwrite_lru_queue_statistics = 
	    STATIC_SYMBOL("WRITE-LRU-QUEUE-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_lru_queue_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_27 = STATIC_STRING("LRU Queue Statistics");
    string_constant_28 = 
	    STATIC_STRING("Scaled Font LRU Queue Memory Usage             = ~a");
    string_constant_29 = 
	    STATIC_STRING("Icon Rendering LRU Queue Memory Usage          = ~a");
    string_constant_30 = 
	    STATIC_STRING("Graph Rendering LRU Queue Memory Usage         = ~a");
    SET_SYMBOL_FUNCTION(Qwrite_lru_queue_statistics,
	    STATIC_FUNCTION(write_lru_queue_statistics,NIL,FALSE,1,1));
    Qcompute_true_size_of_scaled_font = 
	    STATIC_SYMBOL("COMPUTE-TRUE-SIZE-OF-SCALED-FONT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_true_size_of_scaled_font,
	    STATIC_FUNCTION(compute_true_size_of_scaled_font,NIL,FALSE,1,1));
    Qcompute_true_size_of_icon_rendering = 
	    STATIC_SYMBOL("COMPUTE-TRUE-SIZE-OF-ICON-RENDERING",AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_true_size_of_icon_rendering,
	    STATIC_FUNCTION(compute_true_size_of_icon_rendering,NIL,FALSE,
	    1,1));
    Qcompute_true_size_of_graph_rendering = 
	    STATIC_SYMBOL("COMPUTE-TRUE-SIZE-OF-GRAPH-RENDERING",AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_true_size_of_graph_rendering,
	    STATIC_FUNCTION(compute_true_size_of_graph_rendering,NIL,FALSE,
	    1,1));
    Qwrite_pool_memory_usage = STATIC_SYMBOL("WRITE-POOL-MEMORY-USAGE",
	    AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_pool_memory_usage,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    array_constant_2 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    string_constant_31 = STATIC_STRING("System Object Pool Usage Statistics");
    string_constant_32 = STATIC_STRING("Pool Name");
    string_constant_33 = STATIC_STRING("Type");
    string_constant_34 = STATIC_STRING("Out");
    string_constant_35 = STATIC_STRING("%Out");
    string_constant_36 = STATIC_STRING("Count");
    string_constant_37 = STATIC_STRING("dCount");
    string_constant_38 = STATIC_STRING("Memory");
    string_constant_39 = STATIC_STRING("dMemory");
    string_constant_40 = STATIC_STRING("");
    SET_SYMBOL_FUNCTION(Qwrite_pool_memory_usage,
	    STATIC_FUNCTION(write_pool_memory_usage,NIL,FALSE,1,1));
    array_constant_21 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)24L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)31L,(SI_Long)57344L);
    if (Simple_string_stats_namestring == UNBOUND)
	Simple_string_stats_namestring = array_constant_21;
    if (Simple_string_stats_header_needed == UNBOUND)
	Simple_string_stats_header_needed = T;
    if (Reclaimed_strings_reported == UNBOUND)
	Reclaimed_strings_reported = FIX((SI_Long)0L);
    if (Allocated_strings_reported == UNBOUND)
	Allocated_strings_reported = FIX((SI_Long)0L);
    Qg2_set_simple_string_metering_parameters = 
	    STATIC_SYMBOL("G2-SET-SIMPLE-STRING-METERING-PARAMETERS",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_simple_string_metering_parameters,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_directory_pathname = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)57344L);
    string_constant_41 = 
	    string_append2(STATIC_STRING("Setting parameters for string allocation metering: reporting data on string allocations and reclamations in file ~a, for one string in every ~a longer than ~a characters, incl"),
	    STATIC_STRING("uding first ~a characters of reclaimed string"));
    SET_SYMBOL_FUNCTION(Qg2_set_simple_string_metering_parameters,
	    STATIC_FUNCTION(g2_set_simple_string_metering_parameters,NIL,
	    FALSE,4,4));
    Qg2_turn_on_simple_string_metering = 
	    STATIC_SYMBOL("G2-TURN-ON-SIMPLE-STRING-METERING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_turn_on_simple_string_metering,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_12 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)57344L);
    string_constant_42 = 
	    STATIC_STRING("Turning on string allocation monitoring");
    SET_SYMBOL_FUNCTION(Qg2_turn_on_simple_string_metering,
	    STATIC_FUNCTION(g2_turn_on_simple_string_metering,NIL,FALSE,0,0));
    Qg2_turn_off_simple_string_metering = 
	    STATIC_SYMBOL("G2-TURN-OFF-SIMPLE-STRING-METERING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_turn_off_simple_string_metering,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_43 = 
	    STATIC_STRING("Turning off string allocation monitoring");
    array_constant_13 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)28L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)31L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_turn_off_simple_string_metering,
	    STATIC_FUNCTION(g2_turn_off_simple_string_metering,NIL,FALSE,0,0));
    Qg2_simple_string_metering_include_reclaims = 
	    STATIC_SYMBOL("G2-SIMPLE-STRING-METERING-INCLUDE-RECLAIMS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_simple_string_metering_include_reclaims,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_14 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)39L,(SI_Long)57344L);
    string_constant_44 = 
	    STATIC_STRING("Turning on string reclaimation monitoring");
    SET_SYMBOL_FUNCTION(Qg2_simple_string_metering_include_reclaims,
	    STATIC_FUNCTION(g2_simple_string_metering_include_reclaims,NIL,
	    FALSE,0,0));
    Qg2_simple_string_metering_exclude_reclaims = 
	    STATIC_SYMBOL("G2-SIMPLE-STRING-METERING-EXCLUDE-RECLAIMS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_simple_string_metering_exclude_reclaims,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_15 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)31L,(SI_Long)57344L);
    string_constant_45 = STATIC_STRING("Metering only allocations");
    SET_SYMBOL_FUNCTION(Qg2_simple_string_metering_exclude_reclaims,
	    STATIC_FUNCTION(g2_simple_string_metering_exclude_reclaims,NIL,
	    FALSE,0,0));
    Qgensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_stream_error_string = STATIC_SYMBOL("G2-STREAM-ERROR-STRING",
	    AB_package);
    string_constant_46 = 
	    STATIC_STRING("Unable to open G2 statistics file ~s, ~a.");
    string_constant_47 = STATIC_STRING("Allocated string #~a: length is ~a");
    string_constant_48 = STATIC_STRING("Reclaimed string #~a: length is ~a");
    string_constant_49 = STATIC_STRING("Initial ~a characters: <~a>");
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    string_constant_50 = STATIC_STRING("~a");
    string_constant_51 = 
	    STATIC_STRING("Reporting one string in every ~a of length over ~a");
    string_constant_52 = 
	    STATIC_STRING("Metering both allocations and reclamations");
    string_constant_53 = 
	    STATIC_STRING("Printing out up to ~a characters from reclaimed strings");
    Qlength_of_backtrace_text_buffer_for_string_metering = 
	    STATIC_SYMBOL("LENGTH-OF-BACKTRACE-TEXT-BUFFER-FOR-STRING-METERING",
	    AB_package);
    SET_SYMBOL_VALUE(Qlength_of_backtrace_text_buffer_for_string_metering,
	    FIX((SI_Long)4000L));
    if (Input_string_for_backtrace_text_buffer_for_string_metering == 
		UNBOUND) {
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
	Input_string_for_backtrace_text_buffer_for_string_metering = 
		wide_string_bv16;
    }
    if (Backtrace_text_buffer_for_string_metering == UNBOUND) {
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
	Backtrace_text_buffer_for_string_metering = wide_string_bv16;
    }
    Qlength_of_buffer_for_string_metering = 
	    STATIC_SYMBOL("LENGTH-OF-BUFFER-FOR-STRING-METERING",AB_package);
    SET_SYMBOL_VALUE(Qlength_of_buffer_for_string_metering,
	    FIX((SI_Long)4000L));
    if (Input_gensym_string_for_buffer_for_string_metering == UNBOUND)
	Input_gensym_string_for_buffer_for_string_metering = make_string(1,
		FIX((SI_Long)4000L));
    if (Buffer_for_string_metering == UNBOUND)
	Buffer_for_string_metering = make_array(5,FIX((SI_Long)4000L),
		Kelement_type,Qstring_char,Kfill_pointer,FIX((SI_Long)0L));
    string_constant_54 = STATIC_STRING("Backtrace:");
    string_constant_55 = STATIC_STRING("~%  ~A");
    string_constant_56 = STATIC_STRING("~%  ");
    string_constant_57 = STATIC_STRING("~%");
    Qwrite_global_memory_statistics = 
	    STATIC_SYMBOL("WRITE-GLOBAL-MEMORY-STATISTICS",AB_package);
    system_statistics_writers_new_value = adjoin(2,
	    Qwrite_global_memory_statistics,System_statistics_writers);
    System_statistics_writers = system_statistics_writers_new_value;
    string_constant_58 = STATIC_STRING("Overall Memory Usage Statistics");
    string_constant_59 = STATIC_STRING("Total Memory Usage             = ~a");
    string_constant_60 = STATIC_STRING("Total Pool Memory Usage        = ~a");
    string_constant_61 = STATIC_STRING("Total Pool Objects Outstanding = ~a");
    string_constant_62 = STATIC_STRING("Total Pool Objects Allocated   = ~a");
    SET_SYMBOL_FUNCTION(Qwrite_global_memory_statistics,
	    STATIC_FUNCTION(write_global_memory_statistics,NIL,FALSE,1,1));
    Qpercent_run_time = STATIC_SYMBOL("PERCENT-RUN-TIME",AB_package);
    list_constant_7 = STATIC_CONS(Qpercent_running,Qnil);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qpercent_run_time,
	    list_constant_7);
    list_constant_9 = STATIC_CONS(list_constant_8,Qnil);
    install_g2_meter_names_and_forms(list_constant_9);
    string_constant_69 = STATIC_STRING("1l1m83*Dy1m9k83-ijy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_69));
    Qclock_tick_length = STATIC_SYMBOL("CLOCK-TICK-LENGTH",AB_package);
    list_constant_10 = STATIC_CONS(Qmetered_clock_tick_length,Qnil);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qclock_tick_length,
	    list_constant_10);
    list_constant_12 = STATIC_CONS(list_constant_11,Qnil);
    install_g2_meter_names_and_forms(list_constant_12);
    string_constant_70 = STATIC_STRING("1l1m83*Dy1m9k83-Miy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    list_constant_13 = STATIC_CONS(Qmaximum_clock_tick_length,Qnil);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qmaximum_clock_tick_length,
	    list_constant_13);
    list_constant_15 = STATIC_CONS(list_constant_14,Qnil);
    install_g2_meter_names_and_forms(list_constant_15);
    string_constant_71 = STATIC_STRING("1l1m83*Dy1m9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmaximum_clock_tick_length);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_71));
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qsimulator_time_lag,
	    list_constant);
    list_constant_17 = STATIC_CONS(list_constant_16,Qnil);
    install_g2_meter_names_and_forms(list_constant_17);
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimulator_time_lag);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_71));
    Qinstance_creation_count_as_float = 
	    STATIC_SYMBOL("INSTANCE-CREATION-COUNT-AS-FLOAT",AB_package);
    Qg2_instance_creation_count_as_float = 
	    STATIC_SYMBOL("G2-INSTANCE-CREATION-COUNT-AS-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_instance_creation_count_as_float,
	    STATIC_FUNCTION(g2_instance_creation_count_as_float,NIL,FALSE,
	    0,0));
    list_constant_18 = STATIC_CONS(Qg2_instance_creation_count_as_float,Qnil);
    list_constant_19 = STATIC_LIST((SI_Long)2L,
	    Qinstance_creation_count_as_float,list_constant_18);
    list_constant_20 = STATIC_CONS(list_constant_19,Qnil);
    install_g2_meter_names_and_forms(list_constant_20);
    string_constant_72 = STATIC_STRING("1l1m83*Dy1m9k83-aEy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_72));
    Qmemory_usage = STATIC_SYMBOL("MEMORY-USAGE",AB_package);
    Qg2_memory_usage = STATIC_SYMBOL("G2-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_usage,STATIC_FUNCTION(g2_memory_usage,
	    NIL,FALSE,0,0));
    list_constant_21 = STATIC_CONS(Qg2_memory_usage,Qnil);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qmemory_usage,list_constant_21);
    list_constant_23 = STATIC_CONS(list_constant_22,Qnil);
    install_g2_meter_names_and_forms(list_constant_23);
    string_constant_73 = STATIC_STRING("1l1m83*Dy1m9k83-eFy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_73));
    Qmemory_usage_as_float = STATIC_SYMBOL("MEMORY-USAGE-AS-FLOAT",AB_package);
    Qg2_memory_usage_as_float = STATIC_SYMBOL("G2-MEMORY-USAGE-AS-FLOAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_usage_as_float,
	    STATIC_FUNCTION(g2_memory_usage_as_float,NIL,FALSE,0,0));
    list_constant_24 = STATIC_CONS(Qg2_memory_usage_as_float,Qnil);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qmemory_usage_as_float,
	    list_constant_24);
    list_constant_26 = STATIC_CONS(list_constant_25,Qnil);
    install_g2_meter_names_and_forms(list_constant_26);
    string_constant_74 = STATIC_STRING("1l1m83*Dy1m9k83-eGy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_74));
    Qmemory_size = STATIC_SYMBOL("MEMORY-SIZE",AB_package);
    Qg2_memory_size = STATIC_SYMBOL("G2-MEMORY-SIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_size,STATIC_FUNCTION(g2_memory_size,NIL,
	    FALSE,0,0));
    list_constant_27 = STATIC_CONS(Qg2_memory_size,Qnil);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qmemory_size,list_constant_27);
    list_constant_29 = STATIC_CONS(list_constant_28,Qnil);
    install_g2_meter_names_and_forms(list_constant_29);
    string_constant_75 = STATIC_STRING("1l1m83*Dy1m9k83-eDy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_75));
    Qmemory_size_as_float = STATIC_SYMBOL("MEMORY-SIZE-AS-FLOAT",AB_package);
    Qg2_memory_size_as_float = STATIC_SYMBOL("G2-MEMORY-SIZE-AS-FLOAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_size_as_float,
	    STATIC_FUNCTION(g2_memory_size_as_float,NIL,FALSE,0,0));
    list_constant_30 = STATIC_CONS(Qg2_memory_size_as_float,Qnil);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qmemory_size_as_float,
	    list_constant_30);
    list_constant_32 = STATIC_CONS(list_constant_31,Qnil);
    install_g2_meter_names_and_forms(list_constant_32);
    string_constant_76 = STATIC_STRING("1l1m83*Dy1m9k83-eEy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_76));
    Qmemory_available = STATIC_SYMBOL("MEMORY-AVAILABLE",AB_package);
    list_constant_33 = STATIC_CONS(Qg2_memory_available,Qnil);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qmemory_available,
	    list_constant_33);
    list_constant_35 = STATIC_CONS(list_constant_34,Qnil);
    install_g2_meter_names_and_forms(list_constant_35);
    string_constant_77 = STATIC_STRING("1l1m83*Dy1m9k83-eAy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_77));
    Qmemory_available_as_float = STATIC_SYMBOL("MEMORY-AVAILABLE-AS-FLOAT",
	    AB_package);
    Qg2_memory_available_as_float = 
	    STATIC_SYMBOL("G2-MEMORY-AVAILABLE-AS-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_memory_available_as_float,
	    STATIC_FUNCTION(g2_memory_available_as_float,NIL,FALSE,0,0));
    list_constant_36 = STATIC_CONS(Qg2_memory_available_as_float,Qnil);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qmemory_available_as_float,
	    list_constant_36);
    list_constant_38 = STATIC_CONS(list_constant_37,Qnil);
    install_g2_meter_names_and_forms(list_constant_38);
    string_constant_78 = STATIC_STRING("1l1m83*Dy1m9k83-eBy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_78));
    Qmaximum_memory_regions_in_any_model = 
	    STATIC_SYMBOL("MAXIMUM-MEMORY-REGIONS-IN-ANY-MODEL",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_memory_regions_in_any_model,FIX((SI_Long)3L));
    Qregion_1_memory_usage = STATIC_SYMBOL("REGION-1-MEMORY-USAGE",AB_package);
    Qg2_region_memory_usage = STATIC_SYMBOL("G2-REGION-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_usage,
	    STATIC_FUNCTION(g2_region_memory_usage,NIL,FALSE,1,1));
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qg2_region_memory_usage,
	    FIX((SI_Long)1L));
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qregion_1_memory_usage,
	    list_constant_39);
    list_constant_41 = STATIC_CONS(list_constant_40,Qnil);
    install_g2_meter_names_and_forms(list_constant_41);
    string_constant_79 = STATIC_STRING("1l1m83*Dy1m9k83-lZy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_79));
    Qregion_1_memory_usage_as_float = 
	    STATIC_SYMBOL("REGION-1-MEMORY-USAGE-AS-FLOAT",AB_package);
    Qg2_region_memory_usage_as_float = 
	    STATIC_SYMBOL("G2-REGION-MEMORY-USAGE-AS-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_usage_as_float,
	    STATIC_FUNCTION(g2_region_memory_usage_as_float,NIL,FALSE,1,1));
    list_constant_42 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_43 = STATIC_CONS(Qg2_region_memory_usage_as_float,
	    list_constant_42);
    list_constant_44 = STATIC_LIST((SI_Long)2L,
	    Qregion_1_memory_usage_as_float,list_constant_43);
    list_constant_45 = STATIC_CONS(list_constant_44,Qnil);
    install_g2_meter_names_and_forms(list_constant_45);
    string_constant_80 = STATIC_STRING("1l1m83*Dy1m9k83-lay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_80));
    Qregion_2_memory_usage = STATIC_SYMBOL("REGION-2-MEMORY-USAGE",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qg2_region_memory_usage,
	    FIX((SI_Long)2L));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qregion_2_memory_usage,
	    list_constant_46);
    list_constant_48 = STATIC_CONS(list_constant_47,Qnil);
    install_g2_meter_names_and_forms(list_constant_48);
    string_constant_81 = STATIC_STRING("1l1m83*Dy1m9k83-lfy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_81));
    Qregion_2_memory_usage_as_float = 
	    STATIC_SYMBOL("REGION-2-MEMORY-USAGE-AS-FLOAT",AB_package);
    list_constant_49 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_50 = STATIC_CONS(Qg2_region_memory_usage_as_float,
	    list_constant_49);
    list_constant_51 = STATIC_LIST((SI_Long)2L,
	    Qregion_2_memory_usage_as_float,list_constant_50);
    list_constant_52 = STATIC_CONS(list_constant_51,Qnil);
    install_g2_meter_names_and_forms(list_constant_52);
    string_constant_82 = STATIC_STRING("1l1m83*Dy1m9k83-lgy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_82));
    Qregion_3_memory_usage = STATIC_SYMBOL("REGION-3-MEMORY-USAGE",AB_package);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qg2_region_memory_usage,
	    FIX((SI_Long)3L));
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qregion_3_memory_usage,
	    list_constant_53);
    list_constant_55 = STATIC_CONS(list_constant_54,Qnil);
    install_g2_meter_names_and_forms(list_constant_55);
    string_constant_83 = STATIC_STRING("1l1m83*Dy1m9k83-lly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_83));
    Qregion_3_memory_usage_as_float = 
	    STATIC_SYMBOL("REGION-3-MEMORY-USAGE-AS-FLOAT",AB_package);
    list_constant_56 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_57 = STATIC_CONS(Qg2_region_memory_usage_as_float,
	    list_constant_56);
    list_constant_58 = STATIC_LIST((SI_Long)2L,
	    Qregion_3_memory_usage_as_float,list_constant_57);
    list_constant_59 = STATIC_CONS(list_constant_58,Qnil);
    install_g2_meter_names_and_forms(list_constant_59);
    string_constant_84 = STATIC_STRING("1l1m83*Dy1m9k83-lmy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_84));
    Qregion_1_memory_available = STATIC_SYMBOL("REGION-1-MEMORY-AVAILABLE",
	    AB_package);
    list_constant_60 = STATIC_CONS(Qg2_region_memory_available,
	    list_constant_42);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qregion_1_memory_available,
	    list_constant_60);
    list_constant_62 = STATIC_CONS(list_constant_61,Qnil);
    install_g2_meter_names_and_forms(list_constant_62);
    string_constant_85 = STATIC_STRING("1l1m83*Dy1m9k83-lVy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    Qregion_1_memory_available_as_float = 
	    STATIC_SYMBOL("REGION-1-MEMORY-AVAILABLE-AS-FLOAT",AB_package);
    Qg2_region_memory_available_as_float = 
	    STATIC_SYMBOL("G2-REGION-MEMORY-AVAILABLE-AS-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_available_as_float,
	    STATIC_FUNCTION(g2_region_memory_available_as_float,NIL,FALSE,
	    1,1));
    list_constant_63 = STATIC_CONS(Qg2_region_memory_available_as_float,
	    list_constant_42);
    list_constant_64 = STATIC_LIST((SI_Long)2L,
	    Qregion_1_memory_available_as_float,list_constant_63);
    list_constant_65 = STATIC_CONS(list_constant_64,Qnil);
    install_g2_meter_names_and_forms(list_constant_65);
    string_constant_86 = STATIC_STRING("1l1m83*Dy1m9k83-lWy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_86));
    Qregion_2_memory_available = STATIC_SYMBOL("REGION-2-MEMORY-AVAILABLE",
	    AB_package);
    list_constant_66 = STATIC_CONS(Qg2_region_memory_available,
	    list_constant_49);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qregion_2_memory_available,
	    list_constant_66);
    list_constant_68 = STATIC_CONS(list_constant_67,Qnil);
    install_g2_meter_names_and_forms(list_constant_68);
    string_constant_87 = STATIC_STRING("1l1m83*Dy1m9k83-lby");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_87));
    Qregion_2_memory_available_as_float = 
	    STATIC_SYMBOL("REGION-2-MEMORY-AVAILABLE-AS-FLOAT",AB_package);
    list_constant_69 = STATIC_CONS(Qg2_region_memory_available_as_float,
	    list_constant_49);
    list_constant_70 = STATIC_LIST((SI_Long)2L,
	    Qregion_2_memory_available_as_float,list_constant_69);
    list_constant_71 = STATIC_CONS(list_constant_70,Qnil);
    install_g2_meter_names_and_forms(list_constant_71);
    string_constant_88 = STATIC_STRING("1l1m83*Dy1m9k83-lcy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_88));
    Qregion_3_memory_available = STATIC_SYMBOL("REGION-3-MEMORY-AVAILABLE",
	    AB_package);
    list_constant_72 = STATIC_CONS(Qg2_region_memory_available,
	    list_constant_56);
    list_constant_73 = STATIC_LIST((SI_Long)2L,Qregion_3_memory_available,
	    list_constant_72);
    list_constant_74 = STATIC_CONS(list_constant_73,Qnil);
    install_g2_meter_names_and_forms(list_constant_74);
    string_constant_89 = STATIC_STRING("1l1m83*Dy1m9k83-lhy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_89));
    Qregion_3_memory_available_as_float = 
	    STATIC_SYMBOL("REGION-3-MEMORY-AVAILABLE-AS-FLOAT",AB_package);
    list_constant_75 = STATIC_CONS(Qg2_region_memory_available_as_float,
	    list_constant_56);
    list_constant_76 = STATIC_LIST((SI_Long)2L,
	    Qregion_3_memory_available_as_float,list_constant_75);
    list_constant_77 = STATIC_CONS(list_constant_76,Qnil);
    install_g2_meter_names_and_forms(list_constant_77);
    string_constant_90 = STATIC_STRING("1l1m83*Dy1m9k83-liy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_90));
    Qregion_1_memory_size = STATIC_SYMBOL("REGION-1-MEMORY-SIZE",AB_package);
    Qg2_region_memory_size = STATIC_SYMBOL("G2-REGION-MEMORY-SIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_size,
	    STATIC_FUNCTION(g2_region_memory_size,NIL,FALSE,1,1));
    list_constant_78 = STATIC_CONS(Qg2_region_memory_size,list_constant_42);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qregion_1_memory_size,
	    list_constant_78);
    list_constant_80 = STATIC_CONS(list_constant_79,Qnil);
    install_g2_meter_names_and_forms(list_constant_80);
    string_constant_91 = STATIC_STRING("1l1m83*Dy1m9k83-lXy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_91));
    Qregion_1_memory_size_as_float = 
	    STATIC_SYMBOL("REGION-1-MEMORY-SIZE-AS-FLOAT",AB_package);
    Qg2_region_memory_size_as_float = 
	    STATIC_SYMBOL("G2-REGION-MEMORY-SIZE-AS-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_region_memory_size_as_float,
	    STATIC_FUNCTION(g2_region_memory_size_as_float,NIL,FALSE,1,1));
    list_constant_81 = STATIC_CONS(Qg2_region_memory_size_as_float,
	    list_constant_42);
    list_constant_82 = STATIC_LIST((SI_Long)2L,
	    Qregion_1_memory_size_as_float,list_constant_81);
    list_constant_83 = STATIC_CONS(list_constant_82,Qnil);
    install_g2_meter_names_and_forms(list_constant_83);
    string_constant_92 = STATIC_STRING("1l1m83*Dy1m9k83-lYy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_92));
    Qregion_2_memory_size = STATIC_SYMBOL("REGION-2-MEMORY-SIZE",AB_package);
    list_constant_84 = STATIC_CONS(Qg2_region_memory_size,list_constant_49);
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qregion_2_memory_size,
	    list_constant_84);
    list_constant_86 = STATIC_CONS(list_constant_85,Qnil);
    install_g2_meter_names_and_forms(list_constant_86);
    string_constant_93 = STATIC_STRING("1l1m83*Dy1m9k83-ldy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_93));
    Qregion_2_memory_size_as_float = 
	    STATIC_SYMBOL("REGION-2-MEMORY-SIZE-AS-FLOAT",AB_package);
    list_constant_87 = STATIC_CONS(Qg2_region_memory_size_as_float,
	    list_constant_49);
    list_constant_88 = STATIC_LIST((SI_Long)2L,
	    Qregion_2_memory_size_as_float,list_constant_87);
    list_constant_89 = STATIC_CONS(list_constant_88,Qnil);
    install_g2_meter_names_and_forms(list_constant_89);
    string_constant_94 = STATIC_STRING("1l1m83*Dy1m9k83-ley");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_94));
    Qregion_3_memory_size = STATIC_SYMBOL("REGION-3-MEMORY-SIZE",AB_package);
    list_constant_90 = STATIC_CONS(Qg2_region_memory_size,list_constant_56);
    list_constant_91 = STATIC_LIST((SI_Long)2L,Qregion_3_memory_size,
	    list_constant_90);
    list_constant_92 = STATIC_CONS(list_constant_91,Qnil);
    install_g2_meter_names_and_forms(list_constant_92);
    string_constant_95 = STATIC_STRING("1l1m83*Dy1m9k83-ljy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_95));
    Qregion_3_memory_size_as_float = 
	    STATIC_SYMBOL("REGION-3-MEMORY-SIZE-AS-FLOAT",AB_package);
    list_constant_93 = STATIC_CONS(Qg2_region_memory_size_as_float,
	    list_constant_56);
    list_constant_94 = STATIC_LIST((SI_Long)2L,
	    Qregion_3_memory_size_as_float,list_constant_93);
    list_constant_95 = STATIC_CONS(list_constant_94,Qnil);
    install_g2_meter_names_and_forms(list_constant_95);
    string_constant_96 = STATIC_STRING("1l1m83*Dy1m9k83-lky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_96));
    Qpriority_1_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-1-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_1_scheduler_time_lag,
	    STATIC_FUNCTION(priority_1_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_96 = STATIC_CONS(Qpriority_1_scheduler_time_lag,Qnil);
    list_constant_106 = STATIC_LIST((SI_Long)2L,
	    Qpriority_1_scheduler_time_lag,list_constant_96);
    Qpriority_2_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-2-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_2_scheduler_time_lag,
	    STATIC_FUNCTION(priority_2_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_97 = STATIC_CONS(Qpriority_2_scheduler_time_lag,Qnil);
    list_constant_107 = STATIC_LIST((SI_Long)2L,
	    Qpriority_2_scheduler_time_lag,list_constant_97);
    Qpriority_3_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-3-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_3_scheduler_time_lag,
	    STATIC_FUNCTION(priority_3_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_98 = STATIC_CONS(Qpriority_3_scheduler_time_lag,Qnil);
    list_constant_108 = STATIC_LIST((SI_Long)2L,
	    Qpriority_3_scheduler_time_lag,list_constant_98);
    Qpriority_4_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-4-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_4_scheduler_time_lag,
	    STATIC_FUNCTION(priority_4_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_99 = STATIC_CONS(Qpriority_4_scheduler_time_lag,Qnil);
    list_constant_109 = STATIC_LIST((SI_Long)2L,
	    Qpriority_4_scheduler_time_lag,list_constant_99);
    Qpriority_5_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-5-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_5_scheduler_time_lag,
	    STATIC_FUNCTION(priority_5_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_100 = STATIC_CONS(Qpriority_5_scheduler_time_lag,Qnil);
    list_constant_110 = STATIC_LIST((SI_Long)2L,
	    Qpriority_5_scheduler_time_lag,list_constant_100);
    Qpriority_6_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-6-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_6_scheduler_time_lag,
	    STATIC_FUNCTION(priority_6_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_101 = STATIC_CONS(Qpriority_6_scheduler_time_lag,Qnil);
    list_constant_111 = STATIC_LIST((SI_Long)2L,
	    Qpriority_6_scheduler_time_lag,list_constant_101);
    Qpriority_7_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-7-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_7_scheduler_time_lag,
	    STATIC_FUNCTION(priority_7_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_102 = STATIC_CONS(Qpriority_7_scheduler_time_lag,Qnil);
    list_constant_112 = STATIC_LIST((SI_Long)2L,
	    Qpriority_7_scheduler_time_lag,list_constant_102);
    Qpriority_8_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-8-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_8_scheduler_time_lag,
	    STATIC_FUNCTION(priority_8_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_103 = STATIC_CONS(Qpriority_8_scheduler_time_lag,Qnil);
    list_constant_113 = STATIC_LIST((SI_Long)2L,
	    Qpriority_8_scheduler_time_lag,list_constant_103);
    Qpriority_9_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-9-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_9_scheduler_time_lag,
	    STATIC_FUNCTION(priority_9_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_104 = STATIC_CONS(Qpriority_9_scheduler_time_lag,Qnil);
    list_constant_114 = STATIC_LIST((SI_Long)2L,
	    Qpriority_9_scheduler_time_lag,list_constant_104);
    Qpriority_10_scheduler_time_lag = 
	    STATIC_SYMBOL("PRIORITY-10-SCHEDULER-TIME-LAG",AB_package);
    SET_SYMBOL_FUNCTION(Qpriority_10_scheduler_time_lag,
	    STATIC_FUNCTION(priority_10_scheduler_time_lag,NIL,FALSE,0,0));
    list_constant_105 = STATIC_CONS(Qpriority_10_scheduler_time_lag,Qnil);
    list_constant_115 = STATIC_LIST((SI_Long)2L,
	    Qpriority_10_scheduler_time_lag,list_constant_105);
    list_constant_116 = STATIC_LIST((SI_Long)10L,list_constant_106,
	    list_constant_107,list_constant_108,list_constant_109,
	    list_constant_110,list_constant_111,list_constant_112,
	    list_constant_113,list_constant_114,list_constant_115);
    install_g2_meter_names_and_forms(list_constant_116);
    string_constant_97 = 
	    STATIC_STRING("1u1m83*Dy1m9k9l1m83*Dy1m9k9m1m83*Dy1m9k9n1m83*Dy1m9k9o1m83*Dy1m9k9p1m83*Dy1m9k9q1m83*Dy1m9k9r1m83*Dy1m9k9s1m83*Dy1m9k9t1m83*Dy1m");
    string_constant_98 = STATIC_STRING("9k9u");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qpriority_1_scheduler_time_lag);
    push_optimized_constant(Qpriority_2_scheduler_time_lag);
    push_optimized_constant(Qpriority_3_scheduler_time_lag);
    push_optimized_constant(Qpriority_4_scheduler_time_lag);
    push_optimized_constant(Qpriority_5_scheduler_time_lag);
    push_optimized_constant(Qpriority_6_scheduler_time_lag);
    push_optimized_constant(Qpriority_7_scheduler_time_lag);
    push_optimized_constant(Qpriority_8_scheduler_time_lag);
    push_optimized_constant(Qpriority_9_scheduler_time_lag);
    push_optimized_constant(Qpriority_10_scheduler_time_lag);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_97,
	    string_constant_98)));
}
