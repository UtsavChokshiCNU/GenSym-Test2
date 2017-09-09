/* kbld1.c
 * Input file:  kb-load1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbld1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Break_if_name_inconsistency_qm, Qbreak_if_name_inconsistency_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Plist_has_been_checked_p, Qplist_has_been_checked_p);

DEFINE_VARIABLE_WITH_SYMBOL(Need_to_check_plist_p, Qneed_to_check_plist_p);

/* DO-PLIST-CHECKING */
Object do_plist_checking()
{
    x_note_fn_call(131,0);
    Need_to_check_plist_p = T;
    return VALUES_1(Evaluation_true_value);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* FILE-TYPES-FOR-MODULE */
Object file_types_for_module()
{
    x_note_fn_call(131,1);
    if (Need_to_check_plist_p)
	return VALUES_1(list_constant);
    else
	return VALUES_1(list_constant_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Complete_kb_name_qm, Qcomplete_kb_name_qm);

static Object Qab_class;           /* class */

static Object Qframe_flags;        /* frame-flags */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

static Object Qframe_change_log;   /* frame-change-log */

static Object Qchange_log_information;  /* change-log-information */

static Object Qframe_representations;  /* frame-representations */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qname_of_defined_class;  /* name-of-defined-class */

static Object Qicon_attributes_plist;  /* icon-attributes-plist */

static Object Quser_overridable_system_slots;  /* user-overridable-system-slots */

static Object Qsubworkspaces;      /* subworkspaces */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qindexed_attributes_for_definition;  /* indexed-attributes-for-definition */

static Object Qjunction_block_class_for_connection;  /* junction-block-class-for-connection */

static Object Qinclude_in_menus_qm;  /* include-in-menus? */

static Object Qinstantiate_qm;     /* instantiate? */

static Object Quuid;               /* uuid */

static Object Qrelation_instances;  /* relation-instances */

static Object Qicon_background_images;  /* icon-background-images */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

/* FIND-DIFFERENCES-IN-FRAMES-IF-ANY */
Object find_differences_in_frames_if_any varargs_1(int, n)
{
    Object frame_1, frame_2;
    Object just_see_if_there_are_any_qm, compatible_definition_classes_qm;
    Object slot_description, class_description, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, gensymed_symbol, vector_slot_index_qm;
    Object slot_value_1, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm, slot_value_2, slot_features;
    SI_Long max_i, i, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(131,2);
    INIT_ARGS_nonrelocating();
    frame_1 = REQUIRED_ARG_nonrelocating();
    frame_2 = REQUIRED_ARG_nonrelocating();
    just_see_if_there_are_any_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    compatible_definition_classes_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !EQ(ISVREF(ISVREF(frame_1,(SI_Long)1L),(SI_Long)1L),
	    ISVREF(ISVREF(frame_2,(SI_Long)1L),(SI_Long)1L)) &&  
	    !TRUEP(compatible_definition_classes_qm)) {
	if (just_see_if_there_are_any_qm)
	    return VALUES_1(T);
	else
	    return slot_value_cons_1(Qab_class,Nil);
    }
    else {
	slot_description = Nil;
	class_description = ISVREF(frame_1,(SI_Long)1L);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(slot_description,(SI_Long)2L);
	if ( !(EQ(gensymed_symbol,Qframe_flags) || EQ(gensymed_symbol,
		Qframe_status_and_notes) || EQ(gensymed_symbol,
		Qframe_author_or_authors) || EQ(gensymed_symbol,
		Qframe_change_log) || EQ(gensymed_symbol,
		Qchange_log_information) || EQ(gensymed_symbol,
		Qframe_representations) || EQ(gensymed_symbol,
		Qname_or_names_for_frame) || EQ(gensymed_symbol,
		Qname_of_defined_class) || EQ(gensymed_symbol,
		Qicon_attributes_plist) || EQ(gensymed_symbol,
		Quser_overridable_system_slots) || EQ(gensymed_symbol,
		Qsubworkspaces) || EQ(gensymed_symbol,
		Qslot_group_for_block_qm) || EQ(gensymed_symbol,
		Qindexed_attributes_for_definition) || EQ(gensymed_symbol,
		Qjunction_block_class_for_connection) || 
		EQ(gensymed_symbol,Qinclude_in_menus_qm) || 
		EQ(gensymed_symbol,Qinstantiate_qm) || EQ(gensymed_symbol,
		Quuid) || EQ(gensymed_symbol,Qrelation_instances) || 
		EQ(gensymed_symbol,Qicon_background_images)) ?  
		!TRUEP(ISVREF(slot_description,(SI_Long)8L)) : TRUEP(Nil)) {
	    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	    if (vector_slot_index_qm)
		slot_value_1 = ISVREF(frame_1,IFIX(vector_slot_index_qm));
	    else {
		user_vector_slot_index_qm = ISVREF(slot_description,
			(SI_Long)8L);
		if (user_vector_slot_index_qm)
		    slot_value_1 = ISVREF(ISVREF(frame_1,(SI_Long)0L),
			    IFIX(user_vector_slot_index_qm));
		else {
		    slot_name = ISVREF(slot_description,(SI_Long)1L);
		    lookup_structure_qm = ISVREF(frame_1,(SI_Long)0L);
		    if (lookup_structure_qm) {
			max_i = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			max_i = max_i - (SI_Long)1L;
			i = IFIX(ISVREF(ISVREF(frame_1,(SI_Long)1L),
				(SI_Long)15L));
			ab_loop_bind_ = max_i;
		      next_loop_1:
			if (i >= ab_loop_bind_)
			    goto end_loop_1;
			if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			    slot_index_qm = FIX(i + (SI_Long)1L);
			    goto end_1;
			}
			i = i + (SI_Long)2L;
			goto next_loop_1;
		      end_loop_1:
			slot_index_qm = Qnil;
		      end_1:;
			slot_value_1 = slot_index_qm ? 
				ISVREF(lookup_structure_qm,
				IFIX(slot_index_qm)) : 
				ISVREF(slot_description,(SI_Long)6L);
		    }
		    else
			slot_value_1 = ISVREF(slot_description,(SI_Long)6L);
		}
	    }
	    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	    if (vector_slot_index_qm)
		slot_value_2 = ISVREF(frame_2,IFIX(vector_slot_index_qm));
	    else {
		user_vector_slot_index_qm = ISVREF(slot_description,
			(SI_Long)8L);
		if (user_vector_slot_index_qm)
		    slot_value_2 = ISVREF(ISVREF(frame_2,(SI_Long)0L),
			    IFIX(user_vector_slot_index_qm));
		else {
		    slot_name = ISVREF(slot_description,(SI_Long)1L);
		    lookup_structure_qm = ISVREF(frame_2,(SI_Long)0L);
		    if (lookup_structure_qm) {
			max_i = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			max_i = max_i - (SI_Long)1L;
			i = IFIX(ISVREF(ISVREF(frame_2,(SI_Long)1L),
				(SI_Long)15L));
			ab_loop_bind_ = max_i;
		      next_loop_2:
			if (i >= ab_loop_bind_)
			    goto end_loop_2;
			if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			    slot_index_qm = FIX(i + (SI_Long)1L);
			    goto end_2;
			}
			i = i + (SI_Long)2L;
			goto next_loop_2;
		      end_loop_2:
			slot_index_qm = Qnil;
		      end_2:;
			slot_value_2 = slot_index_qm ? 
				ISVREF(lookup_structure_qm,
				IFIX(slot_index_qm)) : 
				ISVREF(slot_description,(SI_Long)6L);
		    }
		    else
			slot_value_2 = ISVREF(slot_description,(SI_Long)6L);
		}
	    }
	    if ( !EQ(slot_value_1,slot_value_2)) {
		slot_features = ISVREF(slot_description,(SI_Long)9L);
		temp = assq_function(Qtype,slot_features) ?  
			!TRUEP(assq_function(Qdo_not_save,slot_features)) :
			 TRUEP(assq_function(Qsave,slot_features));
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ?  !TRUEP(slot_value_equal_p(slot_value_1,
		    slot_value_2)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (just_see_if_there_are_any_qm)
		return VALUES_1(T);
	    else {
		ab_loopvar__2 = 
			slot_value_cons_1(denote_slot_using_slot_value_conses(slot_description,
			ISVREF(frame_1,(SI_Long)1L)),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_subseries_of_values_64_vectors, Qavailable_subseries_of_values_64_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_subseries_of_values_64_vectors, Qcount_of_subseries_of_values_64_vectors);

Object Available_subseries_of_values_64_vectors_vector = UNBOUND;

/* SUBSERIES-OF-VALUES-64-VECTOR-MEMORY-USAGE */
Object subseries_of_values_64_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(131,3);
    temp = Count_of_subseries_of_values_64_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)64L)));
    return VALUES_1(temp);
}

/* OUT-SUBSERIES-OF-VALUES-64-VECTORS */
Object out_subseries_of_values_64_vectors()
{
    Object temp;

    x_note_fn_call(131,4);
    temp = FIXNUM_MINUS(Count_of_subseries_of_values_64_vectors,
	    length(Available_subseries_of_values_64_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-SUBSERIES-OF-VALUES-64-VECTOR-INTERNAL */
Object make_permanent_subseries_of_values_64_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(131,5);
    atomic_incff_symval(Qcount_of_subseries_of_values_64_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(1,FIX((SI_Long)64L));
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-SUBSERIES-OF-VALUES */
Object make_subseries_of_values()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(131,6);
    if (ISVREF(Available_subseries_of_values_64_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_subseries_of_values_64_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = Available_subseries_of_values_64_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_subseries_of_values_64_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_subseries_of_values_64_vectors_vector,
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
	temp = make_permanent_subseries_of_values_64_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-SUBSERIES-OF-VALUES */
Object reclaim_subseries_of_values(subseries_of_values_64_vector)
    Object subseries_of_values_64_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(131,7);
    svref_arg_1 = Available_subseries_of_values_64_vectors_vector;
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
    M_CAR(gensymed_symbol) = subseries_of_values_64_vector;
    temp = ISVREF(Available_subseries_of_values_64_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* CONVERT-LIST-TO-SERIES-OF-VALUES */
Object convert_list_to_series_of_values(list_1)
    Object list_1;
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, subseries_of_values;
    Object list_old_value, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(131,8);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(list_1))
	goto end_loop;
    subseries_of_values = make_subseries_of_values();
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(subseries_of_values));
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    list_old_value = list_1;
    temp = FIRST(list_old_value);
    list_1 = REST(list_old_value);
    ISVREF(subseries_of_values,i) = temp;
    if ( !TRUEP(list_1))
	goto end_loop_1;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    temp = subseries_of_values;
    goto end_1;
    temp = Qnil;
  end_1:;
    ab_loopvar__2 = slot_value_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* CONVERT-SERIES-OF-VALUES-TO-LIST */
Object convert_series_of_values_to_list varargs_1(int, n)
{
    Object series_of_values, length_1;
    Object copy_values_qm, subseries_of_values, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loopvar__3, ab_loopvar__4;
    SI_Long i, ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(131,9);
    INIT_ARGS_nonrelocating();
    series_of_values = REQUIRED_ARG_nonrelocating();
    length_1 = REQUIRED_ARG_nonrelocating();
    copy_values_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    subseries_of_values = Nil;
    ab_loop_list_ = series_of_values;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subseries_of_values = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(subseries_of_values));
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    length_1 = FIXNUM_SUB1(length_1);
    if ( !(IFIX(length_1) >= (SI_Long)0L))
	goto end_loop_1;
    ab_loopvar__4 = slot_value_cons_1(copy_values_qm ? 
	    copy_for_slot_value(ISVREF(subseries_of_values,i)) : 
	    ISVREF(subseries_of_values,i),Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    goto end_1;
    ab_loopvar__2 = Qnil;
  end_1:;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* RECLAIM-SUBSERIES-OF-VALUES-AND-VALUES */
Object reclaim_subseries_of_values_and_values(subseries_of_values)
    Object subseries_of_values;
{
    Object value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(131,10);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(array_total_size(subseries_of_values));
    value = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    value = aref1(subseries_of_values,FIX(i));
    if (value) {
	reclaim_slot_value(value);
	set_aref1(subseries_of_values,FIX(i),Nil);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return reclaim_subseries_of_values(subseries_of_values);
}

/* RECLAIM-SERIES-OF-VALUES-AND-VALUES */
Object reclaim_series_of_values_and_values(series_of_values)
    Object series_of_values;
{
    Object subseries_of_values, ab_loop_list_;

    x_note_fn_call(131,11);
    subseries_of_values = Nil;
    ab_loop_list_ = series_of_values;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subseries_of_values = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_subseries_of_values_and_values(subseries_of_values);
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_list_1(series_of_values);
}

/* RECLAIM-SERIES-OF-VALUES */
Object reclaim_series_of_values(series_of_values)
    Object series_of_values;
{
    Object subseries_of_values, ab_loop_list_;

    x_note_fn_call(131,12);
    subseries_of_values = Nil;
    ab_loop_list_ = series_of_values;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subseries_of_values = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_subseries_of_values(subseries_of_values);
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_list_1(series_of_values);
}

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p, Qcollecting_updates_to_sensor_attributes_p);

DEFINE_VARIABLE_WITH_SYMBOL(Collected_updates_to_sensor_attributes, Qcollected_updates_to_sensor_attributes);

/* HANDLE-COLLECTED-UPDATES-TO-SENSOR-ATTRIBUTES */
Object handle_collected_updates_to_sensor_attributes()
{
    Object sensor, gsi_interface_frame, real_attribute_name_list;
    Object ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(131,13);
    sensor = Nil;
    gsi_interface_frame = Nil;
    real_attribute_name_list = Nil;
    ab_loop_list_ = Collected_updates_to_sensor_attributes;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    sensor = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    gsi_interface_frame = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    real_attribute_name_list = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    handle_update_to_located_sensor_attribute(3,sensor,
	    CAR(real_attribute_name_list),gsi_interface_frame);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qis_created;         /* is-created */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object Qdo_not_clone;       /* do-not-clone */

static Object Qlocal_name_or_names;  /* local-name-or-names */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qsimulation_formulas_qm;  /* simulation-formulas? */

static Object Qcolumn_of_args;     /* column-of-args */

static Object Qcolumn_of_values;   /* column-of-values */

static Object Qembedded_rule_qm;   /* embedded-rule? */

static Object Qembedded_rule_in_user_menu_choice_qm;  /* embedded-rule-in-user-menu-choice? */

static Object Qlist_of_plots;      /* list-of-plots */

static Object Qconnection_style;   /* connection-style */

static Object Qline_pattern;       /* line-pattern */

static Object Qconnection_arrows;  /* connection-arrows */

static Object Qcompound_slot_descriptor;  /* compound-slot-descriptor */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qincomplete;         /* incomplete */

/* CLONE-FRAME */
Object clone_frame varargs_1(int, n)
{
    Object old_frame;
    Object blocks_in_bounding_box_qm, superior_frame_being_cloned_qm;
    Object collecting_updates_to_sensor_attributes_p;
    Object collected_updates_to_sensor_attributes, current_computation_frame;
    Object current_computation_component_particulars, class_description;
    Object new_frame, gensymed_symbol, sub_class_bit_vector, new_value;
    Object ellipses_added_p, slot_description, ab_loop_list_, slot_name;
    Object do_not_clone_qm, slot_init_form, old_slot_value, temp_1;
    Object vector_slot_index_qm, user_vector_slot_index_qm, slot_name_1;
    Object lookup_structure_qm, slot_index_qm, representation_frame;
    Object ab_loop_list__1, ab_loopvar_, ab_loopvar__1, plot, ab_loopvar__2;
    Object temp_2, slot_features, new_slot_value, x2, x, new_embedded_rule_qm;
    Object old_embedded_rule_qm, result_1, current_flag_state_qm;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, max_i, i;
    SI_Long ab_loop_bind_, svref_new_value;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(6);
    Object result;

    x_note_fn_call(131,14);
    INIT_ARGS_nonrelocating();
    old_frame = REQUIRED_ARG_nonrelocating();
    blocks_in_bounding_box_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    superior_frame_being_cloned_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Superior_frame_being_cloned_qm,Qsuperior_frame_being_cloned_qm,superior_frame_being_cloned_qm,
	    5);
      END_ARGS_nonrelocating();
      collecting_updates_to_sensor_attributes_p = T;
      collected_updates_to_sensor_attributes = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Collected_updates_to_sensor_attributes,Qcollected_updates_to_sensor_attributes,collected_updates_to_sensor_attributes,
	      4);
	PUSH_SPECIAL_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p,Qcollecting_updates_to_sensor_attributes_p,collecting_updates_to_sensor_attributes_p,
		3);
	  current_computation_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  2);
	    current_computation_component_particulars = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		    1);
	      class_description = ISVREF(old_frame,(SI_Long)1L);
	      new_frame = 
		      make_frame_without_computed_initializations(class_description,
		      Nil,Nil);
	      schedule_task_to_invoke_existential_rules(new_frame,Qis_created);
	      gensymed_symbol = ISVREF(new_frame,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Kb_workspace_class_description,
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
		  if ( !TRUEP(Superior_frame_being_cloned_qm)) {
		      new_value = get_module_block_is_in(old_frame);
		      initialize_slot_description_value(new_frame,
			      get_slot_description_of_class_description_function(Qmodule_this_is_part_of_qm,
			      ISVREF(new_frame,(SI_Long)1L),Nil),new_value);
		  }
	      }
	      else {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
		  if (temp) {
		      new_value = copy_for_slot_value(ISVREF(old_frame,
			      (SI_Long)17L));
		      initialize_slot_description_value(new_frame,
			      get_slot_description_of_class_description_function(Qicon_attributes_plist,
			      ISVREF(new_frame,(SI_Long)1L),Nil),new_value);
		  }
		  else {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Table_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  copy_table(3,old_frame,new_frame,
				  Superior_frame_being_cloned_qm);
		  }
	      }
	      superior_frame_being_cloned_qm = new_frame;
	      PUSH_SPECIAL_WITH_SYMBOL(Superior_frame_being_cloned_qm,Qsuperior_frame_being_cloned_qm,superior_frame_being_cloned_qm,
		      0);
		ellipses_added_p = Nil;
		slot_description = Nil;
		ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
		slot_name = Nil;
		do_not_clone_qm = Nil;
		slot_init_form = Nil;
		old_slot_value = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		slot_description = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		slot_name = ISVREF(slot_description,(SI_Long)2L);
		if (assq_function(Qdo_not_clone,ISVREF(slot_description,
			(SI_Long)9L))) {
		    temp_1 =  !EQ(slot_name,Qname_or_names_for_frame) ? T :
			     Nil;
		    if (temp_1);
		    else
			temp_1 =  
				!TRUEP(assq_function(Qlocal_name_or_names,
				ISVREF(slot_description,(SI_Long)9L))) ? T 
				: Nil;
		    do_not_clone_qm = temp_1;
		}
		else
		    do_not_clone_qm = Nil;
		slot_init_form = ISVREF(slot_description,(SI_Long)6L);
		vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
		if (vector_slot_index_qm)
		    old_slot_value = ISVREF(old_frame,
			    IFIX(vector_slot_index_qm));
		else {
		    user_vector_slot_index_qm = ISVREF(slot_description,
			    (SI_Long)8L);
		    if (user_vector_slot_index_qm)
			old_slot_value = ISVREF(ISVREF(old_frame,
				(SI_Long)0L),IFIX(user_vector_slot_index_qm));
		    else {
			slot_name_1 = ISVREF(slot_description,(SI_Long)1L);
			lookup_structure_qm = ISVREF(old_frame,(SI_Long)0L);
			if (lookup_structure_qm) {
			    max_i = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			    max_i = max_i - (SI_Long)1L;
			    i = IFIX(ISVREF(ISVREF(old_frame,(SI_Long)1L),
				    (SI_Long)15L));
			    ab_loop_bind_ = max_i;
			  next_loop_1:
			    if (i >= ab_loop_bind_)
				goto end_loop_1;
			    if (EQ(ISVREF(lookup_structure_qm,i),
					slot_name_1)) {
				slot_index_qm = FIX(i + (SI_Long)1L);
				goto end_1;
			    }
			    i = i + (SI_Long)2L;
			    goto next_loop_1;
			  end_loop_1:
			    slot_index_qm = Qnil;
			  end_1:;
			    old_slot_value = slot_index_qm ? 
				    ISVREF(lookup_structure_qm,
				    IFIX(slot_index_qm)) : 
				    ISVREF(slot_description,(SI_Long)6L);
			}
			else
			    old_slot_value = ISVREF(slot_description,
				    (SI_Long)6L);
		    }
		}
		if ( !(EQ(old_slot_value,slot_init_form) || do_not_clone_qm)) {
		    if (EQ(slot_name,Qslot_group_for_block_qm))
			clone_slot_group_for_block_qm(old_slot_value,
				old_frame,new_frame,blocks_in_bounding_box_qm);
		    else if (EQ(slot_name,Qbox_translation_and_text) || 
			    EQ(slot_name,Qsimulation_formulas_qm))
			ellipses_added_p = clone_text_slot_value(new_frame,
				slot_description,old_slot_value);
		    else if (EQ(slot_name,Qframe_representations)) {
			representation_frame = Nil;
			ab_loop_list__1 = old_slot_value;
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar_ = Nil;
		      next_loop_2:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_2;
			representation_frame = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			if (EQ(representation_frame,old_frame)) {
			    ab_loopvar_ = slot_value_cons_1(new_frame,Nil);
			    if (ab_loopvar__1)
				M_CDR(ab_loopvar__1) = ab_loopvar_;
			    else;
			    ab_loopvar__1 = ab_loopvar_;
			}
			goto next_loop_2;
		      end_loop_2:
			goto end_2;
		      end_2:;
		    }
		    else if (EQ(slot_name,Qcolumn_of_args) || EQ(slot_name,
			    Qcolumn_of_values))
			clone_series_of_values(new_frame,slot_description,
				old_slot_value,old_frame);
		    else if (EQ(slot_name,Qembedded_rule_qm) || 
			    EQ(slot_name,
			    Qembedded_rule_in_user_menu_choice_qm))
			clone_embedded_rule(new_frame,slot_description,
				old_slot_value);
		    else if (EQ(slot_name,Qlist_of_plots)) {
			temp_1 = slot_description;
			plot = Nil;
			ab_loop_list__1 = old_slot_value;
			ab_loopvar__1 = Nil;
			ab_loopvar_ = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_3:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_3;
			plot = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			ab_loopvar__2 = slot_value_cons_1(clone_frame(1,
				plot),Nil);
			if (ab_loopvar_)
			    M_CDR(ab_loopvar_) = ab_loopvar__2;
			else
			    ab_loopvar__1 = ab_loopvar__2;
			ab_loopvar_ = ab_loopvar__2;
			goto next_loop_3;
		      end_loop_3:
			temp_2 = ab_loopvar__1;
			goto end_3;
			temp_2 = Qnil;
		      end_3:;
			initialize_slot_description_value(new_frame,temp_1,
				temp_2);
		    }
		    else if (EQ(slot_name,Qsubworkspaces))
			add_subworkspace(clone_frame(3,CAR(old_slot_value),
				Nil,old_frame),new_frame);
		    else {
			slot_features = ISVREF(slot_description,(SI_Long)9L);
			temp = (assq_function(Qtype,slot_features) ?  
				!TRUEP(assq_function(Qdo_not_save,
				slot_features)) : 
				TRUEP(assq_function(Qsave,slot_features))) 
				?  !EQ(slot_name,Qicon_attributes_plist) : 
				TRUEP(Nil);
			if (temp);
			else
			    temp = EQ(slot_name,Qframe_flags);
			if (temp);
			else {
			    temp = EQ(slot_name,Qconnection_style);
			    if (temp);
			    else
				temp = EQ(slot_name,Qline_pattern);
			    if (temp);
			    else
				temp = EQ(slot_name,Qconnection_arrows);
			}
			if (temp) {
			    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_name),
				    Qcompound_slot_descriptor))
				new_slot_value = 
					clone_compound_slot_value(old_slot_value,
					new_frame,slot_name);
			    else {
				if (SIMPLE_VECTOR_P(old_slot_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_slot_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(old_slot_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(old_slot_value,(SI_Long)1L);
				    temp = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp = TRUEP(Nil);
				temp =  !temp;
				if (temp);
				else {
				    if (SIMPLE_VECTOR_P(old_slot_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_slot_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(old_slot_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(old_slot_value,
						(SI_Long)1L);
					gensymed_symbol = 
						SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? x2 : Qnil;
				    }
				    else
					gensymed_symbol = Nil;
				    if (gensymed_symbol) {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(Dependent_frame_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
					if (sub_class_vector_index < 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						    {
					    gensymed_symbol_1 = 
						    UBYTE_8_ISAREF_1(sub_class_bit_vector,
						    sub_class_vector_index);
					    gensymed_symbol_2 = (SI_Long)1L;
					    gensymed_symbol_3 = 
						    superior_class_bit_number 
						    & (SI_Long)7L;
					    gensymed_symbol_2 = 
						    gensymed_symbol_2 << 
						    gensymed_symbol_3;
					    gensymed_symbol_1 = 
						    gensymed_symbol_1 & 
						    gensymed_symbol_2;
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
				    }
				    else
					temp = TRUEP(Nil);
				}
				if (temp)
				    new_slot_value = 
					    copy_for_slot_value(old_slot_value);
				else {
				    sub_class_bit_vector = 
					    ISVREF(ISVREF(old_slot_value,
					    (SI_Long)1L),(SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Format_frame_class_description,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_1 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_2 = (SI_Long)1L;
					gensymed_symbol_3 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_2 = 
						gensymed_symbol_2 << 
						gensymed_symbol_3;
					gensymed_symbol_1 = 
						gensymed_symbol_1 & 
						gensymed_symbol_2;
					temp = (SI_Long)0L < gensymed_symbol_1;
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp)
					new_slot_value = old_slot_value;
				    else {
					vector_slot_index_qm = 
						ISVREF(slot_description,
						(SI_Long)7L);
					if (vector_slot_index_qm)
					    x = ISVREF(new_frame,
						    IFIX(vector_slot_index_qm));
					else {
					    user_vector_slot_index_qm = 
						    ISVREF(slot_description,
						    (SI_Long)8L);
					    if (user_vector_slot_index_qm)
						x = 
							ISVREF(ISVREF(new_frame,
							(SI_Long)0L),
							IFIX(user_vector_slot_index_qm));
					    else {
						slot_name_1 = 
							ISVREF(slot_description,
							(SI_Long)1L);
						lookup_structure_qm = 
							ISVREF(new_frame,
							(SI_Long)0L);
						if (lookup_structure_qm) {
						    max_i = 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
						    max_i = max_i - 
							    (SI_Long)1L;
						    i = 
							    IFIX(ISVREF(ISVREF(new_frame,
							    (SI_Long)1L),
							    (SI_Long)15L));
						    ab_loop_bind_ = max_i;
						  next_loop_4:
						    if (i >= ab_loop_bind_)
							goto end_loop_4;
						    if (EQ(ISVREF(lookup_structure_qm,
							    i),slot_name_1)) {
							slot_index_qm = 
								FIX(i + 
								(SI_Long)1L);
							goto end_4;
						    }
						    i = i + (SI_Long)2L;
						    goto next_loop_4;
						  end_loop_4:
						    slot_index_qm = Qnil;
						  end_4:;
						    x = slot_index_qm ? 
							    ISVREF(lookup_structure_qm,
							    IFIX(slot_index_qm)) 
							    : 
							    ISVREF(slot_description,
							    (SI_Long)6L);
						}
						else
						    x = 
							    ISVREF(slot_description,
							    (SI_Long)6L);
					    }
					}
					if (SIMPLE_VECTOR_P(x) && 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) 
						> (SI_Long)2L &&  
						!EQ(ISVREF(x,(SI_Long)1L),
						Qavailable_frame_vector)) {
					    x2 = ISVREF(x,(SI_Long)1L);
					    temp = SIMPLE_VECTOR_P(x2) && 
						    EQ(ISVREF(x2,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_class_description_g2_struct) 
						    ? TRUEP(x2) : TRUEP(Qnil);
					}
					else
					    temp = TRUEP(Nil);
					if (temp)
					    goto end_simple_clone_slot_value;
					else
					    new_slot_value = clone_frame(3,
						    old_slot_value,Nil,
						    new_frame);
				    }
				}
			    }
			    initialize_slot_description_value(new_frame,
				    slot_description,new_slot_value);
			  end_simple_clone_slot_value:;
			}
		    }
		}
		goto next_loop;
	      end_loop:;
		initialize_slots_of_frame_needing_evaluation(new_frame);
		gensymed_symbol = ISVREF(new_frame,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_action_button_class_description,
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
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(User_menu_choice_class_description,
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
		}
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(new_frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Generic_action_button_class_description,
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
		    new_embedded_rule_qm = temp ? 
			    embedded_rule_qm_function(new_frame) : 
			    ISVREF(new_frame,(SI_Long)24L);
		    sub_class_bit_vector = ISVREF(ISVREF(old_frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Generic_action_button_class_description,
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
		    old_embedded_rule_qm = temp ? 
			    embedded_rule_qm_function(old_frame) : 
			    ISVREF(old_frame,(SI_Long)24L);
		    if (new_embedded_rule_qm && old_embedded_rule_qm) {
			temp_1 = ISVREF(old_embedded_rule_qm,(SI_Long)8L);
			update_frame_status(new_embedded_rule_qm,
				CAR(temp_1) ? Qincomplete : Nil,T);
		    }
		}
		else if (ellipses_added_p)
		    update_frame_status(new_frame,Qincomplete,Nil);
		sub_class_bit_vector = ISVREF(ISVREF(new_frame,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		if (temp) {
		    result_1 = Nil;
		    current_flag_state_qm = Nil;
		    current_flag_state_qm = (SI_Long)0L != 
			    (IFIX(ISVREF(new_frame,(SI_Long)5L)) & 
			    (SI_Long)16777216L) ? T : Nil;
		    if ( !TRUEP(current_flag_state_qm)) {
			svref_new_value = IFIX(ISVREF(new_frame,
				(SI_Long)5L)) | (SI_Long)16777216L;
			ISVREF(new_frame,(SI_Long)5L) = FIX(svref_new_value);
		    }
		    result_1 = initialize_frame(new_frame);
		    if ( !TRUEP(current_flag_state_qm)) {
			svref_new_value = IFIX(ISVREF(new_frame,
				(SI_Long)5L)) &  ~(SI_Long)16777216L;
			ISVREF(new_frame,(SI_Long)5L) = FIX(svref_new_value);
		    }
		    if ( !((SI_Long)0L != (IFIX(ISVREF(new_frame,
			    (SI_Long)5L)) & (SI_Long)16777216L))) {
			gensymed_symbol = 
				ISVREF(ISVREF(ISVREF(ISVREF(new_frame,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
				(SI_Long)1L);
			gensymed_symbol_4 = new_frame;
			gensymed_symbol_5 = T;
			gensymed_symbol_6 = Nil;
			inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
				gensymed_symbol_5,gensymed_symbol_6);
		    }
		}
		else
		    initialize_frame(new_frame);
		sub_class_bit_vector = ISVREF(ISVREF(new_frame,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(new_frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
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
			make_or_reformat_ruling_for_meter(Nil,new_frame);
		    update_representations(new_frame);
		    update_attribute_tables(3,new_frame,Nil,Nil);
		}
		temp_1 = new_frame;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  handle_collected_updates_to_sensor_attributes();
	  result = VALUES_1(temp_1);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CLONE-TEXT-SLOT-VALUE */
Object clone_text_slot_value(new_frame,slot_description,old_text_slot_value)
    Object new_frame, slot_description, old_text_slot_value;
{
    Object include_ellipsis_qm, temp, temp_1;

    x_note_fn_call(131,15);
    include_ellipsis_qm = old_text_slot_value ? ( 
	    !EQ(CAR(old_text_slot_value),No_value) ? T : Nil) : Qnil;
    if (old_text_slot_value) {
	temp = include_ellipsis_qm ? No_value : 
		copy_for_slot_value(CAR(old_text_slot_value));
	temp_1 = copy_text(CDR(old_text_slot_value));
	temp_1 = slot_value_cons_1(temp,nconc2(temp_1,include_ellipsis_qm ?
		 slot_value_cons_1(copy_text_string(Ellipsis_text_string),
		Nil) : Nil));
    }
    else
	temp_1 = Nil;
    initialize_slot_description_value(new_frame,slot_description,temp_1);
    return VALUES_1(include_ellipsis_qm);
}

static Object Qnumber_of_rows_in_table;  /* number-of-rows-in-table */

/* CLONE-SERIES-OF-VALUES */
Object clone_series_of_values(new_frame,slot_description,old_slot_value,
	    old_frame)
    Object new_frame, slot_description, old_slot_value, old_frame;
{
    Object slot_value_list;

    x_note_fn_call(131,16);
    slot_value_list = convert_series_of_values_to_list(3,old_slot_value,
	    get_slot_value_function(old_frame,Qnumber_of_rows_in_table,Nil),T);
    return initialize_slot_description_value(new_frame,slot_description,
	    slot_value_list);
}

/* CLONE-EMBEDDED-RULE */
Object clone_embedded_rule(new_frame,slot_description,old_slot_value)
    Object new_frame, slot_description, old_slot_value;
{
    Object embedded_rule_qm;

    x_note_fn_call(131,17);
    embedded_rule_qm = old_slot_value ? clone_frame(3,old_slot_value,Nil,
	    new_frame) : Nil;
    initialize_slot_description_value(new_frame,slot_description,
	    embedded_rule_qm);
    if (embedded_rule_qm) {
	put_rule_byte_code_body(embedded_rule_qm,
		copy_for_slot_value(rule_byte_code_body_function(old_slot_value)),
		Nil);
	return put_box_translation_and_text(embedded_rule_qm,
		copy_for_slot_value(ISVREF(old_slot_value,(SI_Long)16L)),Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLONE-SLOT-GROUP-FOR-BLOCK? */
Object clone_slot_group_for_block_qm(slot_group_for_block_qm,old_frame,
	    new_frame,blocks_in_bounding_box_qm)
    Object slot_group_for_block_qm, old_frame, new_frame;
    Object blocks_in_bounding_box_qm;
{
    x_note_fn_call(131,18);
    if (slot_group_for_block_qm)
	return clone_icon_slot_group(slot_group_for_block_qm,old_frame,
		new_frame,blocks_in_bounding_box_qm);
    else
	return VALUES_1(Nil);
}

/* CLONE-ICON-SLOT-GROUP */
Object clone_icon_slot_group(slot_group_for_block_qm,old_frame,new_frame,
	    blocks_in_bounding_box_qm)
    Object slot_group_for_block_qm, old_frame, new_frame;
    Object blocks_in_bounding_box_qm;
{
    x_note_fn_call(131,19);
    clone_edges_of_block(old_frame,new_frame);
    clone_subblocks_of_block(slot_group_for_block_qm,old_frame,new_frame);
    return clone_connections_of_block(slot_group_for_block_qm,old_frame,
	    new_frame,blocks_in_bounding_box_qm);
}

/* CLONE-EDGES-OF-BLOCK */
Object clone_edges_of_block(old_frame,new_frame)
    Object old_frame, new_frame;
{
    Object gensymed_symbol, temp, temp_1, temp_2;

    x_note_fn_call(131,20);
    gensymed_symbol = ISVREF(old_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(old_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(old_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(old_frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return change_edges_of_block(new_frame,temp,temp_1,temp_2,gensymed_symbol);
}

static Object Qworkspace_margin;   /* workspace-margin */

/* CLONE-SUBBLOCKS-OF-BLOCK */
Object clone_subblocks_of_block(slot_group_for_block_qm,old_frame,new_frame)
    Object slot_group_for_block_qm, old_frame, new_frame;
{
    Object old_value, sub_class_bit_vector, svref_new_value, workspace_case_qm;
    Object cloned_block, result_1, queue, next_queue_element;
    Object gensymed_symbol_3, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object blocks_in_bounding_box_qm, plist_of_blocks_and_corresponding_clones;
    Object ab_queue_form_, ab_next_queue_element_, subblock, class_description;
    Object block, ab_loop_list_, temp_1, reversed_list_of_cloned_subblocks;
    Object cloned_subblock, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(131,21);
    old_value = ISVREF(slot_group_for_block_qm,(SI_Long)4L);
    sub_class_bit_vector = ISVREF(ISVREF(old_frame,(SI_Long)1L),(SI_Long)19L);
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
    if ( !temp) {
	sub_class_bit_vector = ISVREF(ISVREF(old_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(new_frame,Qworkspace_margin);
	    svref_new_value = ISVREF(old_frame,(SI_Long)17L);
	    SVREF(new_frame,FIX((SI_Long)17L)) = svref_new_value;
	}
	sub_class_bit_vector = ISVREF(ISVREF(old_frame,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    workspace_case_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    workspace_case_qm = Nil;
	cloned_block = Nil;
	result_1 = Nil;
	if (old_value) {
	    queue = old_value;
	    next_queue_element = Nil;
	    gensymed_symbol_3 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    next_queue_element = constant_queue_next(ISVREF(queue,
		    (SI_Long)2L),queue);
	  next_loop:
	    if ( !TRUEP(next_queue_element))
		goto end_loop;
	    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)4L);
	    next_queue_element = constant_queue_next(next_queue_element,queue);
	    ab_loopvar__2 = slot_value_cons_1(gensymed_symbol_3,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    blocks_in_bounding_box_qm = ab_loopvar_;
	    goto end_1;
	    blocks_in_bounding_box_qm = Qnil;
	  end_1:;
	}
	else
	    blocks_in_bounding_box_qm = Nil;
	plist_of_blocks_and_corresponding_clones = Nil;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(old_frame,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol_3;
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(old_frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
	    class_description = ISVREF(old_frame,(SI_Long)1L);
	    temp =  !TRUEP(assq_function(Qlocal_name_or_names,
		    ISVREF(get_slot_description(2,Qname_or_names_for_frame,
		    ISVREF(class_description,(SI_Long)6L)),(SI_Long)9L)));
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    cloned_block = clone_frame(3,subblock,
		    blocks_in_bounding_box_qm,new_frame);
	    result_1 = gensym_cons_1(cloned_block,result_1);
	    if (workspace_case_qm)
		plist_of_blocks_and_corresponding_clones = 
			gensym_cons_1(subblock,gensym_cons_1(cloned_block,
			plist_of_blocks_and_corresponding_clones));
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_slot_value_list_1(blocks_in_bounding_box_qm);
	if (workspace_case_qm) {
	    block = Nil;
	    cloned_block = Nil;
	    ab_loop_list_ = plist_of_blocks_and_corresponding_clones;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	  next_loop_2:
	    block = CAR(ab_loop_list_);
	    temp_1 = CDR(ab_loop_list_);
	    cloned_block = CAR(temp_1);
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	    if (gensymed_symbol_3)
		clone_connections_for_block(block,cloned_block,
			plist_of_blocks_and_corresponding_clones);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    goto next_loop_2;
	  end_loop_2:;
	    reclaim_gensym_list_1(plist_of_blocks_and_corresponding_clones);
	}
	reversed_list_of_cloned_subblocks = result_1;
	goto end_2;
	reversed_list_of_cloned_subblocks = Qnil;
      end_2:;
	cloned_subblock = Nil;
	ab_loop_list_ = reversed_list_of_cloned_subblocks;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	cloned_subblock = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = cloned_subblock;
	gensymed_symbol_3 = ISVREF(cloned_subblock,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp_2 = gensymed_symbol_3;
	gensymed_symbol_3 = ISVREF(cloned_subblock,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	add_to_block(4,temp_1,new_frame,temp_2,gensymed_symbol_3);
	goto next_loop_3;
      end_loop_3:
	reclaim_gensym_list_1(reversed_list_of_cloned_subblocks);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CLONE-CONNECTIONS-OF-BLOCK */
Object clone_connections_of_block(slot_group_for_block_qm,old_frame,
	    new_frame,blocks_in_bounding_box_qm)
    Object slot_group_for_block_qm, old_frame, new_frame;
    Object blocks_in_bounding_box_qm;
{
    Object old_value;

    x_note_fn_call(131,22);
    old_value = ISVREF(slot_group_for_block_qm,(SI_Long)6L);
    if (old_value)
	return clone_connections_slot(old_value,old_frame,new_frame,
		blocks_in_bounding_box_qm);
    else
	return VALUES_1(Nil);
}

static Object Qabort_level_3;      /* abort-level-3 */

/* G2-STREAM-OPEN-FOR-OUTPUT-HANDLING-FILE-ERRORS */
Object g2_stream_open_for_output_handling_file_errors(namestring_1)
    Object namestring_1;
{
    Object inner_abort_level_tag;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(131,23);
    if (PUSH_CATCH(Qabort_level_3,0)) {
	inner_abort_level_tag = Qabort_level_3;
	PUSH_SPECIAL_WITH_SYMBOL(Inner_abort_level_tag,Qinner_abort_level_tag,inner_abort_level_tag,
		0);
	  result = g2_stream_open_for_output(namestring_1);
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

/* G2-STREAM-OPEN-FOR-APPENDING-HANDLING-FILE-ERRORS */
Object g2_stream_open_for_appending_handling_file_errors(namestring_1,
	    create_if_does_not_exist_qm)
    Object namestring_1, create_if_does_not_exist_qm;
{
    Object inner_abort_level_tag;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(131,24);
    if (PUSH_CATCH(Qabort_level_3,0)) {
	inner_abort_level_tag = Qabort_level_3;
	PUSH_SPECIAL_WITH_SYMBOL(Inner_abort_level_tag,Qinner_abort_level_tag,inner_abort_level_tag,
		0);
	  result = g2_stream_open_for_appending(namestring_1,
		  create_if_does_not_exist_qm);
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Attempting_save_via_system_procedure_qm, Qattempting_save_via_system_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(G2_window_for_save_via_system_procedure_qm, Qg2_window_for_save_via_system_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Default_kb_pathname_qm, Qdefault_kb_pathname_qm);

/* RECLAIM-RECENT-LOADED-KBS */
Object reclaim_recent_loaded_kbs(list_1)
    Object list_1;
{
    Object pathname_1, ab_loop_list_;

    x_note_fn_call(131,25);
    if (list_1) {
	pathname_1 = Nil;
	ab_loop_list_ = list_1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pathname_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_gensym_pathname(pathname_1);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(list_1);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Recent_loaded_kbs, Qrecent_loaded_kbs);

static Object Qwin32;              /* win32 */

static Object Qdos;                /* dos */

/* ADD-RECENT-LOADED-KB */
Object add_recent_loaded_kb(pathname_1)
    Object pathname_1;
{
    Object namestring_1, trailing_pointer, leading_pointer, cached_pathname;
    Object cached_namestring, equal_p, end1, end2, ab_loop_iter_flag_, temp;
    Object temp_1, cdr_new_value, p;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    SI_Long code;

    x_note_fn_call(131,26);
    if (pathname_1) {
	namestring_1 = gensym_namestring(1,pathname_1);
	trailing_pointer = Nil;
	leading_pointer = Recent_loaded_kbs;
	cached_pathname = Nil;
	cached_namestring = Nil;
	equal_p = Nil;
      next_loop:
	if ( !TRUEP(leading_pointer))
	    goto end_loop;
	cached_pathname = CAR(leading_pointer);
	cached_namestring = gensym_namestring(1,cached_pathname);
	if (EQ(Local_file_system,Qwin32) || EQ(Local_file_system,Qdos)) {
	    end1 = text_string_length(cached_namestring);
	    end2 = text_string_length(namestring_1);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop_1:
		if (index1 >= ab_loop_bind_)
		    goto end_loop_1;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop_1;
		code = UBYTE_16_ISAREF_1(cached_namestring,index1);
		if (code < (SI_Long)127L)
		    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			    FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp);
		    else
			temp = FIX(code);
		}
		code = UBYTE_16_ISAREF_1(namestring_1,index2);
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		if ( !NUM_EQ(temp,temp_1)) {
		    equal_p = Nil;
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		equal_p = T;
		goto end_1;
		equal_p = Qnil;
	      end_1:;
	    }
	    else
		equal_p = Nil;
	}
	else {
	    end1 = text_string_length(cached_namestring);
	    end2 = text_string_length(namestring_1);
	    length1 = IFIX(end1) - (SI_Long)0L;
	    length2 = IFIX(end2) - (SI_Long)0L;
	    if (length1 == length2) {
		index1 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(end1);
		index2 = (SI_Long)0L;
		ab_loop_bind__1 = IFIX(end2);
		ab_loop_iter_flag_ = T;
	      next_loop_2:
		if (index1 >= ab_loop_bind_)
		    goto end_loop_2;
		if ( !TRUEP(ab_loop_iter_flag_))
		    index2 = index2 + (SI_Long)1L;
		if (index2 >= ab_loop_bind__1)
		    goto end_loop_2;
		if ( !(UBYTE_16_ISAREF_1(cached_namestring,index1) == 
			UBYTE_16_ISAREF_1(namestring_1,index2))) {
		    equal_p = Nil;
		    goto end_2;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:
		equal_p = T;
		goto end_2;
		equal_p = Qnil;
	      end_2:;
	    }
	    else
		equal_p = Nil;
	}
	reclaim_text_string(cached_namestring);
	if (equal_p) {
	    reclaim_gensym_pathname(cached_pathname);
	    if (trailing_pointer) {
		cdr_new_value = CDR(leading_pointer);
		M_CDR(trailing_pointer) = cdr_new_value;
	    }
	    else
		Recent_loaded_kbs = CDR(Recent_loaded_kbs);
	    reclaim_gensym_cons_1(leading_pointer);
	    goto end_loop;
	}
	trailing_pointer = leading_pointer;
	leading_pointer = M_CDR(leading_pointer);
	goto next_loop;
      end_loop:
	reclaim_text_string(namestring_1);
	if (FIXNUM_GE(length(Recent_loaded_kbs),
		Plus_max_cached_recent_loaded_kbs_plus)) {
	    p = Recent_loaded_kbs;
	    Recent_loaded_kbs = CDR(Recent_loaded_kbs);
	    reclaim_gensym_pathname(CAR(p));
	    reclaim_gensym_cons_1(p);
	}
	temp = Recent_loaded_kbs;
	Recent_loaded_kbs = nconc2(temp,
		gensym_cons_1(copy_gensym_pathname(pathname_1),Nil));
    }
    return VALUES_1(Nil);
}

/* GET-RECENT-LOADED-KB */
Object get_recent_loaded_kb(name)
    Object name;
{
    Object pathname_1, ab_loop_list_, namestring_1, match_p, end1, end2;
    Object ab_loop_iter_flag_;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;

    x_note_fn_call(131,27);
    if (name) {
	pathname_1 = Nil;
	ab_loop_list_ = Recent_loaded_kbs;
	namestring_1 = Nil;
	match_p = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pathname_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	namestring_1 = gensym_namestring(1,pathname_1);
	end1 = text_string_length(name);
	end2 = text_string_length(namestring_1);
	length1 = IFIX(end1) - (SI_Long)0L;
	length2 = IFIX(end2) - (SI_Long)0L;
	if (length1 == length2) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(end1);
	    index2 = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(end2);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if (index1 >= ab_loop_bind_)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index2 = index2 + (SI_Long)1L;
	    if (index2 >= ab_loop_bind__1)
		goto end_loop_1;
	    if ( !(UBYTE_16_ISAREF_1(name,index1) == 
		    UBYTE_16_ISAREF_1(namestring_1,index2))) {
		match_p = Nil;
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    match_p = T;
	    goto end_1;
	    match_p = Qnil;
	  end_1:;
	}
	else
	    match_p = Nil;
	reclaim_text_string(namestring_1);
	if (match_p)
	    return VALUES_1(pathname_1);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Clear_text_grammar_rules_added_p, Qclear_text_grammar_rules_added_p);

static Object string_constant;     /* "1m1m83-CDy83dky1m83-CDy83g1y" */

/* DO-PLIST-CHECKING-AGAIN */
Object do_plist_checking_again()
{
    XDeclare_area(1);

    x_note_fn_call(131,28);
    if ( !TRUEP(Clear_text_grammar_rules_added_p)) {
	Clear_text_grammar_rules_added_p = T;
	if (PUSH_AREA(Dynamic_area,0))
	    add_grammar_rules_function(regenerate_optimized_constant(string_constant));
	POP_AREA(0);
    }
    return VALUES_1(Evaluation_true_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_code_grammar_rules_added_p, Qcompiled_code_grammar_rules_added_p);

static Object string_constant_1;   /* "1l1m83-CDy83vWy" */

/* ES-C-C */
Object es_c_c()
{
    XDeclare_area(1);

    x_note_fn_call(131,29);
    if ( !TRUEP(Compiled_code_grammar_rules_added_p)) {
	Compiled_code_grammar_rules_added_p = T;
	if (PUSH_AREA(Dynamic_area,0))
	    add_grammar_rules_function(regenerate_optimized_constant(string_constant_1));
	POP_AREA(0);
    }
    return VALUES_1(Evaluation_true_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Source_code_control_grammar_is_present_p, Qsource_code_control_grammar_is_present_p);

static Object string_constant_2;   /* "1y1m8335y1p83mby83LQy83iwy83dky83g1y1m8335y1o83mby83LQy83iwy83g1y1m8335y1p83mby83LQy83iwy83g1y83dky1m8335y1p83mby83LQy83dky83iwy" */

static Object string_constant_3;   /* "83g1y1m8335y1o83mby83LQy83dky83g1y1m8335y1p83mby83LQy83dky83g1y83iwy1m8335y1n83mby83LQy83g1y1m8335y1o83mby83LQy83g1y83iwy1m8335y" */

static Object string_constant_4;   /* "1p83mby83LQy83g1y83iwy83dky1m8335y1o83mby83LQy83g1y83dky1m8335y1p83mby83LQy83g1y83dky83iwy1m8335y1l83-DQy1n83-1Yy1r1m9k837cy1m9k" */

static Object string_constant_5;   /* "832+y1m9k83aWy1m9k83I2y1m9k83Ioy1m9k83HAy1m9k83-d2y83-vTy1n83-1Yy1t1m9k830Iy1m9k9l1m9k837cy1m9k832+y1m9k83aWy1m9k83I2y1m9k83Ioy1" */

static Object string_constant_6;   /* "m9k83HAy1m9k83-d2y83-Rjy" */

/* ADD-SOURCE-CODE-CONTROL-GRAMMAR */
Object add_source_code_control_grammar()
{
    XDeclare_area(1);

    x_note_fn_call(131,30);
    if ( !TRUEP(Source_code_control_grammar_is_present_p)) {
	Source_code_control_grammar_is_present_p = T;
	if (PUSH_AREA(Dynamic_area,0)) {
	    clear_optimized_constants();
	    push_optimized_constant(Qquote);
	    push_optimized_constant(Qnot);
	    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_2,
		    string_constant_3,string_constant_4,string_constant_5,
		    string_constant_6)));
	}
	POP_AREA(0);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

Object File_name_punctuation_alist = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(File_punctuation_mark_grammar_rules, Qfile_punctuation_mark_grammar_rules);

Object Token_menu_class_per_category_overrides = UNBOUND;

/* GET-TOKEN-MENU-CLASS-PER-CATEGORY-OVERRIDES-FOR-FILE-COMMAND */
Object get_token_menu_class_per_category_overrides_for_file_command()
{
    x_note_fn_call(131,31);
    return copy_tree_using_gensym_conses_1(Token_menu_class_per_category_overrides);
}

/* COMPILE-FILE-COMMAND-FOR-SLOT */
Object compile_file_command_for_slot varargs_1(int, n)
{
    Object file_command_parse, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(131,32);
    INIT_ARGS_nonrelocating();
    file_command_parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_init_file_or_file_command(file_command_parse,Nil);
}

/* COMPILE-INIT-FILE-COMMAND-FOR-SLOT */
Object compile_init_file_command_for_slot varargs_1(int, n)
{
    Object file_command_parse, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(131,33);
    INIT_ARGS_nonrelocating();
    file_command_parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_init_file_or_file_command(file_command_parse,T);
}

static Object Qstart_g2;           /* start-g2 */

static Object list_constant_2;     /* # */

static Object string_constant_7;   /* "~a" */

/* COMPILE-INIT-FILE-OR-FILE-COMMAND */
Object compile_init_file_or_file_command(file_command_parse,init_file_case_qm)
    Object file_command_parse, init_file_case_qm;
{
    Object temp, command_symbol, load_or_merge_case_p;
    Object failed_to_compile_and_why_qm;

    x_note_fn_call(131,34);
    if (EQ(file_command_parse,Qstart_g2))
	return VALUES_1(file_command_parse);
    else {
	temp = FIRST(file_command_parse);
	if (CONSP(temp)) {
	    temp = FIRST(file_command_parse);
	    command_symbol = CAR(temp);
	}
	else
	    command_symbol = FIRST(file_command_parse);
	load_or_merge_case_p = memq_function(command_symbol,list_constant_2);
	failed_to_compile_and_why_qm = 
		check_file_command_for_slot(file_command_parse,
		load_or_merge_case_p);
	if (failed_to_compile_and_why_qm) {
	    if (init_file_case_qm) {
		notify_user(2,string_constant_7,failed_to_compile_and_why_qm);
		reclaim_text_string(failed_to_compile_and_why_qm);
		return VALUES_1(Bad_phrase);
	    }
	    else
		return VALUES_2(Bad_phrase,failed_to_compile_and_why_qm);
	}
	else {
	    transform_load_or_merge_options_if_appropriate(file_command_parse,
		    command_symbol,load_or_merge_case_p);
	    return VALUES_1(file_command_parse);
	}
    }
}

static Object string_constant_8;   /* "The default file name ~s cannot be parsed on this platform." */

/* GET-ERROR-STRING-FOR-FILE-NAME-CANNOT-BE-PARSED */
Object get_error_string_for_file_name_cannot_be_parsed(file_name)
    Object file_name;
{
    x_note_fn_call(131,35);
    return tformat_text_string(2,string_constant_8,file_name);
}

static Object string_constant_9;   /* "The file name ~s contains an illegal wildcard." */

/* GET-ERROR-STRING-FOR-ILLEGAL-WILDCARDS-IN-FILENAME */
Object get_error_string_for_illegal_wildcards_in_filename(file_name)
    Object file_name;
{
    x_note_fn_call(131,36);
    return tformat_text_string(2,string_constant_9,file_name);
}

static Object string_constant_10;  /* "The KB-loading option `~a' is not consistent with `starting afterwards'" */

static Object Qnever_start_afterwards;  /* never-start-afterwards */

static Object string_constant_11;  /* "not starting afterwards" */

static Object string_constant_12;  /* "warmbooting afterwards" */

/* GET-ERROR-STRING-FOR-BAD-STARTING-AFTERWARDS-OPTION */
Object get_error_string_for_bad_starting_afterwards_option(options)
    Object options;
{
    x_note_fn_call(131,37);
    return tformat_text_string(2,string_constant_10,
	    memq_function(Qnever_start_afterwards,options) ? 
	    string_constant_11 : string_constant_12);
}

static Object string_constant_13;  /* "The KB-loading option `~a' is not consistent with `warmbooting afterwards'" */

static Object string_constant_14;  /* "starting afterwards" */

/* GET-ERROR-STRING-FOR-BAD-WARMBOOTING-AFTERWARDS-OPTION */
Object get_error_string_for_bad_warmbooting_afterwards_option(options)
    Object options;
{
    x_note_fn_call(131,38);
    return tformat_text_string(2,string_constant_13,
	    memq_function(Qnever_start_afterwards,options) ? 
	    string_constant_11 : string_constant_14);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qper_directory_menu;  /* per-directory-menu */

static Object Qstart_afterwards;   /* start-afterwards */

static Object Qwarmboot_afterwards;  /* warmboot-afterwards */

static Object Qwarmboot_afterwards_with_catch_up;  /* warmboot-afterwards-with-catch-up */

/* CHECK-FILE-COMMAND-FOR-SLOT */
Object check_file_command_for_slot(file_command_parse,load_or_merge_case_p)
    Object file_command_parse, load_or_merge_case_p;
{
    Object filename_spec, per_directory_p, default_file_name_qm;
    Object default_file_name_as_ascii_string_qm;
    volatile Object pathname_from_default_file_name_qm;
    Object namestring_qm, namestring_as_ascii_string_qm, options, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,39);
    SAVE_STACK();
    filename_spec = Qunbound_in_protected_let;
    per_directory_p = Qunbound_in_protected_let;
    default_file_name_qm = Qunbound_in_protected_let;
    default_file_name_as_ascii_string_qm = Qunbound_in_protected_let;
    pathname_from_default_file_name_qm = Qunbound_in_protected_let;
    namestring_qm = Qunbound_in_protected_let;
    namestring_as_ascii_string_qm = Qunbound_in_protected_let;
    options = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	filename_spec = SECOND(file_command_parse);
	per_directory_p = EQ(CONSP(filename_spec) ? SECOND(filename_spec) :
		 filename_spec,Qper_directory_menu) ? T : Nil;
	default_file_name_qm = CONSP(filename_spec) ? FIRST(filename_spec) 
		: Nil;
	default_file_name_as_ascii_string_qm = default_file_name_qm;
	pathname_from_default_file_name_qm = 
		default_file_name_as_ascii_string_qm ? 
		gensym_pathname(default_file_name_as_ascii_string_qm) : Nil;
	namestring_qm =  !TRUEP(per_directory_p) ? (CONSP(filename_spec) ? 
		SECOND(filename_spec) : filename_spec) : Nil;
	namestring_as_ascii_string_qm = namestring_qm;
	options = load_or_merge_case_p ? THIRD(file_command_parse) : Nil;
	if (per_directory_p && default_file_name_qm &&  
		!TRUEP(pathname_from_default_file_name_qm))
	    SAVE_VALUES(get_error_string_for_file_name_cannot_be_parsed(default_file_name_qm));
	else if ( !TRUEP(per_directory_p) && namestring_as_ascii_string_qm 
		&& gensym_wild_pathname_p(namestring_as_ascii_string_qm))
	    SAVE_VALUES(get_error_string_for_illegal_wildcards_in_filename(namestring_qm));
	else if (load_or_merge_case_p) {
	    temp = memq_function(Qstart_afterwards,options) ? 
		    (memq_function(Qnever_start_afterwards,options) || 
		    memq_function(Qwarmboot_afterwards,options) || 
		    memq_function(Qwarmboot_afterwards_with_catch_up,
		    options) ? 
		    get_error_string_for_bad_starting_afterwards_option(options) 
		    : Nil) : Nil;
	    if (temp)
		SAVE_VALUES(VALUES_1(temp));
	    else if (memq_function(Qwarmboot_afterwards,options) || 
		    memq_function(Qwarmboot_afterwards_with_catch_up,
			options)) {
		if (memq_function(Qnever_start_afterwards,options) || 
			memq_function(Qstart_afterwards,options))
		    SAVE_VALUES(get_error_string_for_bad_warmbooting_afterwards_option(options));
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	else
	    SAVE_VALUES(VALUES_1(Qnil));
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_from_default_file_name_qm) {
	if ( !EQ(pathname_from_default_file_name_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_from_default_file_name_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qwhat_to_do_after_loading_kb;  /* what-to-do-after-loading-kb */

static Object list_constant_5;     /* # */

static Object Qincluding_all_required_modules;  /* including-all-required-modules */

static Object Qusing_clear_text;   /* using-clear-text */

static Object Qcommit_after_saving;  /* commit-after-saving */

static Object Qemitting_c_code;    /* emitting-c-code */

/* TRANSFORM-LOAD-OR-MERGE-OPTIONS-IF-APPROPRIATE */
Object transform_load_or_merge_options_if_appropriate(file_command_parse,
	    command_symbol,load_or_merge_case_p)
    Object file_command_parse, command_symbol, load_or_merge_case_p;
{
    Object load_or_merge_options, load_or_merge_options_plist, indicator;
    Object ab_loop_list_, option, ab_loop_desetq_, temp;
    Object what_to_do_after_loading_kb_qm, tail, temp_1, e, log_1;
    Object cddr_new_value;

    x_note_fn_call(131,40);
    if (load_or_merge_case_p) {
	load_or_merge_options = THIRD(file_command_parse);
	load_or_merge_options_plist = Nil;
	indicator = Nil;
	ab_loop_list_ = list_constant_3;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	indicator = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(indicator,load_or_merge_options))
	    load_or_merge_options_plist = phrase_cons(indicator,
		    phrase_cons(Qt,load_or_merge_options_plist));
	goto next_loop;
      end_loop:;
	indicator = Nil;
	option = Nil;
	ab_loop_list_ = list_constant_4;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	indicator = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	option = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(option,load_or_merge_options))
	    load_or_merge_options_plist = phrase_cons(indicator,
		    phrase_cons(Qnil,load_or_merge_options_plist));
	goto next_loop_1;
      end_loop_1:;
	what_to_do_after_loading_kb_qm = 
		memq_function(Qwarmboot_afterwards,load_or_merge_options) ?
		 Qwarmboot_afterwards : 
		memq_function(Qwarmboot_afterwards_with_catch_up,
		load_or_merge_options) ? 
		Qwarmboot_afterwards_with_catch_up : 
		memq_function(Qnever_start_afterwards,
		load_or_merge_options) ? Qnever_start_afterwards : 
		memq_function(Qstart_afterwards,load_or_merge_options) ? 
		Qstart_afterwards : Nil;
	if (what_to_do_after_loading_kb_qm)
	    load_or_merge_options_plist = 
		    phrase_cons(Qwhat_to_do_after_loading_kb,
		    phrase_cons(what_to_do_after_loading_kb_qm,
		    load_or_merge_options_plist));
	M_THIRD(file_command_parse) = load_or_merge_options_plist;
    }
    else if (memq_function(command_symbol,list_constant_5)) {
	tail = CDDR(file_command_parse);
	temp_1 = memq_function(Qincluding_all_required_modules,tail) ? 
		phrase_list_2(Qincluding_all_required_modules,T) : Nil;
	temp = memq_function(Qusing_clear_text,tail) ? 
		phrase_list_2(Qusing_clear_text,T) : Nil;
	e = Nil;
	ab_loop_list_ = tail;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	e = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(e) && EQ(CAR(e),Qcommit_after_saving)) {
	    log_1 = CADR(e);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	log_1 = Qnil;
      end_1:;
	cddr_new_value = phrase_cons(nconc2(temp_1,nconc2(temp,
		nconc2(log_1 ? phrase_list_2(Qcommit_after_saving,log_1) : 
		Nil,memq_function(Qemitting_c_code,tail) ? 
		phrase_list_2(Qemitting_c_code,T) : Nil))),Nil);
	M_CDDR(file_command_parse) = cddr_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qattribute;          /* attribute */

static Object Qstatistics;         /* statistics */

static Object Qforeign_image;      /* foreign-image */

/* MAKE-DEFAULT-PATHNAME */
Object make_default_pathname(symbolic_file_type_qm)
    Object symbolic_file_type_qm;
{
    Object temp;

    x_note_fn_call(131,41);
    if (EQ(symbolic_file_type_qm,Qattribute))
	return VALUES_1(Current_attribute_file_pathname_qm);
    else if (EQ(symbolic_file_type_qm,Qstatistics))
	return VALUES_1(Current_statistics_file_pathname_qm);
    else if (EQ(symbolic_file_type_qm,Qforeign_image))
	return VALUES_1(Current_foreign_image_pathname_qm);
    else {
	temp = Default_kb_pathname_qm;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(Current_kb_pathname_qm);
    }
}

static Object Qxml;                /* xml */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* MAKE-DEFAULT-FILE-TYPE */
Object make_default_file_type(symbolic_file_type_qm)
    Object symbolic_file_type_qm;
{
    x_note_fn_call(131,42);
    if (EQ(symbolic_file_type_qm,Qxml))
	return VALUES_1(array_constant);
    else if (EQ(symbolic_file_type_qm,Qforeign_image))
	return VALUES_1(array_constant_1);
    else if (EQ(symbolic_file_type_qm,Qattribute) || 
	    EQ(symbolic_file_type_qm,Qstatistics))
	return VALUES_1(array_constant_2);
    else if (EQ(symbolic_file_type_qm,Qlog))
	return VALUES_1(array_constant_3);
    else
	return VALUES_1(array_constant_4);
}

static Object Quser;               /* user */

/* GET-CURRENT-USER-NAME */
Object get_current_user_name()
{
    Object foreign_user_name_qm;

    x_note_fn_call(131,43);
    foreign_user_name_qm = foreign_get_user_name();
    if (foreign_user_name_qm) {
	if (IFIX(text_string_length(foreign_user_name_qm)) > (SI_Long)0L)
	    return intern_text_string(1,foreign_user_name_qm);
	else {
	    reclaim_text_string(foreign_user_name_qm);
	    return VALUES_2(Quser,T);
	}
    }
    else
	return VALUES_2(Quser,T);
}

static Object string_constant_15;  /* "~a (~s by default), using clear text" */

static Object string_constant_16;  /* "~a (~s by default)" */

static Object Qfile_command;       /* file-command */

/* HANDLE-FILE-COMMAND */
Object handle_file_command varargs_1(int, n)
{
    Object command_verb;
    Object symbolic_file_type_qm, inconsistent_so_save_all_qm, module_case_qm;
    Object for_save_p;
    volatile Object pathname_for_file_command;
    Object xml_pathname_p;
    volatile Object namestring_for_file_command;
    Object user_readable_namestring_for_file_command;
    Object file_command_initial_text_line, temp;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,44);
    INIT_ARGS_nonrelocating();
    command_verb = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    symbolic_file_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    inconsistent_so_save_all_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    module_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    for_save_p = Qunbound_in_protected_let;
    pathname_for_file_command = Qunbound_in_protected_let;
    xml_pathname_p = Qunbound_in_protected_let;
    namestring_for_file_command = Qunbound_in_protected_let;
    user_readable_namestring_for_file_command = Qunbound_in_protected_let;
    file_command_initial_text_line = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	for_save_p = UBYTE_16_ISAREF_1(command_verb,(SI_Long)0L) == 
		(SI_Long)83L && UBYTE_16_ISAREF_1(command_verb,
		(SI_Long)1L) == (SI_Long)97L && 
		UBYTE_16_ISAREF_1(command_verb,(SI_Long)2L) == 
		(SI_Long)118L ? (UBYTE_16_ISAREF_1(command_verb,
		(SI_Long)3L) == (SI_Long)101L ? T : Nil) : Qnil;
	temp = inconsistent_so_save_all_qm;
	if (temp);
	else
	    temp = for_save_p ? ( !TRUEP(module_case_qm) ? T : Nil) : Qnil;
	pathname_for_file_command = 
		get_pathname_for_file_command(symbolic_file_type_qm,
		inconsistent_so_save_all_qm,module_case_qm,temp);
	xml_pathname_p = string_equalw(array_constant,
		ISVREF(pathname_for_file_command,(SI_Long)5L));
	namestring_for_file_command = gensym_namestring(1,
		pathname_for_file_command);
	user_readable_namestring_for_file_command = 
		namestring_for_file_command;
	file_command_initial_text_line = tformat_text_string(3,for_save_p 
		&& xml_pathname_p && module_case_qm ? string_constant_15 : 
		string_constant_16,command_verb,
		user_readable_namestring_for_file_command);
	SAVE_VALUES(handle_command(Qfile_command,
		file_command_initial_text_line));
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_for_file_command) {
	if ( !EQ(namestring_for_file_command,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_for_file_command);
    }
    if (pathname_for_file_command) {
	if ( !EQ(pathname_for_file_command,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_for_file_command);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object string_constant_17;  /* "ALL-~a" */

/* GET-PATHNAME-FOR-FILE-COMMAND */
Object get_pathname_for_file_command(symbolic_file_type_qm,
	    inconsistent_so_save_all_qm,module_case_qm,xml_prohibited_qm)
    Object symbolic_file_type_qm, inconsistent_so_save_all_qm, module_case_qm;
    Object xml_prohibited_qm;
{
    volatile Object pathname_for_file_command_1;
    Object base_name_pathname, base_name_string;
    volatile Object base_name_string_prefix;
    Object all_type_base_name_string_p;
    volatile Object derived_name_string;
    Object temp, module, pathname_qm, pathname_name_1, namestring_copy_qm;
    Object wide_string_bv16;
    SI_Long temp_1, bv16_length, aref_arg_2, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,45);
    SAVE_STACK();
    pathname_for_file_command_1 = Qunbound_in_protected_let;
    base_name_pathname = Qunbound_in_protected_let;
    base_name_string = Qunbound_in_protected_let;
    base_name_string_prefix = Qunbound_in_protected_let;
    all_type_base_name_string_p = Qunbound_in_protected_let;
    derived_name_string = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_for_file_command_1 = get_or_make_default_kb_pathname(2,
		symbolic_file_type_qm,xml_prohibited_qm);
	base_name_pathname = ISVREF(pathname_for_file_command_1,(SI_Long)4L);
	base_name_string = text_string_p(base_name_pathname) ? 
		base_name_pathname : array_constant_5;
	temp = base_name_string;
	temp_1 = IFIX(text_string_length(base_name_string));
	base_name_string_prefix = text_string_substring(temp,
		FIX((SI_Long)0L),FIX(MIN(temp_1,(SI_Long)4L)));
	all_type_base_name_string_p = 
		string_equalw(base_name_string_prefix,array_constant_6);
	if (inconsistent_so_save_all_qm)
	    derived_name_string = all_type_base_name_string_p ? 
		    copy_text_string(base_name_string) : 
		    tformat_text_string(2,string_constant_17,base_name_string);
	else if ( !(module_case_qm && ISVREF(Module_information,(SI_Long)23L)))
	    derived_name_string = copy_text_string(base_name_string);
	else if (ISVREF(Module_information,(SI_Long)22L))
	    derived_name_string = 
		    copy_text_string(stringw(ISVREF(Module_information,
		    (SI_Long)22L)));
	else {
	    module = ISVREF(Module_information,(SI_Long)23L);
	    pathname_qm = get_true_pathname_of_module_if_any(module);
	    if (pathname_qm) {
		pathname_name_1 = ISVREF(pathname_qm,(SI_Long)4L);
		if (text_string_p(pathname_name_1))
		    namestring_copy_qm = copy_text_string(pathname_name_1);
		else {
		    wide_string_bv16 = 
			    allocate_byte_vector_16(FIX((SI_Long)0L + 
			    (SI_Long)3L));
		    bv16_length = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		    aref_arg_2 = bv16_length - (SI_Long)2L;
		    aref_new_value = (SI_Long)0L & (SI_Long)65535L;
		    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			    aref_new_value);
		    aref_arg_2 = bv16_length - (SI_Long)1L;
		    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			    aref_new_value);
		    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,
			    (SI_Long)0L);
		    namestring_copy_qm = wide_string_bv16;
		}
	    }
	    else
		namestring_copy_qm = Nil;
	    derived_name_string = namestring_copy_qm ? namestring_copy_qm :
		     copy_symbol_name(2,module,Nil);
	}
	SAVE_VALUES(gensym_merge_pathnames_function(derived_name_string,
		pathname_for_file_command_1,Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (derived_name_string) {
	if ( !EQ(derived_name_string,Qunbound_in_protected_let))
	    reclaim_text_string(derived_name_string);
    }
    if (base_name_string_prefix) {
	if ( !EQ(base_name_string_prefix,Qunbound_in_protected_let))
	    reclaim_text_string(base_name_string_prefix);
    }
    if (pathname_for_file_command_1) {
	if ( !EQ(pathname_for_file_command_1,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_for_file_command_1);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* GET-OR-MAKE-DEFAULT-KB-PATHNAME */
Object get_or_make_default_kb_pathname varargs_1(int, n)
{
    Object symbolic_file_type_qm, xml_prohibited_qm;
    volatile Object user_name_as_file_name;
    Object current_default_pathname_qm, returned_pathname, type, temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,46);
    INIT_ARGS_nonrelocating();
    SAVE_STACK();
    symbolic_file_type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    xml_prohibited_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    user_name_as_file_name = Qunbound_in_protected_let;
    current_default_pathname_qm = Qunbound_in_protected_let;
    returned_pathname = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	user_name_as_file_name = tformat_text_string(2,string_constant_7,
		get_current_user_name());
	current_default_pathname_qm = 
		make_default_pathname(symbolic_file_type_qm);
	if (current_default_pathname_qm) {
	    type = ISVREF(current_default_pathname_qm,(SI_Long)5L);
	    temp = text_string_p(type) && string_equalw(type,
		    array_constant) && xml_prohibited_qm ? 
		    array_constant_4 : EQ(symbolic_file_type_qm,Qxml) ? 
		    array_constant : type;
	    returned_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,Nil,temp,Knewest,current_default_pathname_qm);
	}
	else if (Current_kb_pathname_qm) {
	    temp = make_default_file_type(symbolic_file_type_qm);
	    returned_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,Nil,temp,Knewest,Current_kb_pathname_qm);
	}
	else {
	    temp_1 = user_name_as_file_name;
	    temp = make_default_file_type(symbolic_file_type_qm);
	    returned_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,temp_1,temp,Knewest,Process_specific_system_pathname);
	}
	if ( !TRUEP(ISVREF(returned_pathname,(SI_Long)4L))) {
	    temp = gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		    user_name_as_file_name,Nil,Nil,returned_pathname);
	    reclaim_gensym_pathname(returned_pathname);
	    returned_pathname = temp;
	}
	SAVE_VALUES(VALUES_1(returned_pathname));
    }
    POP_UNWIND_PROTECT(0);
    if (user_name_as_file_name) {
	if ( !EQ(user_name_as_file_name,Qunbound_in_protected_let))
	    reclaim_text_string(user_name_as_file_name);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* RECLAIM-FILE-COMMAND-DIRECTORY-SEARCH-CACHE?-VALUE */
Object reclaim_file_command_directory_search_cache_qm_value(directory_search_cache_qm,
	    gensymed_symbol)
    Object directory_search_cache_qm, gensymed_symbol;
{
    x_note_fn_call(131,47);
    if (directory_search_cache_qm)
	reclaim_directory_search_cache(directory_search_cache_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-GENSYM-PATHNAMES-UNDER-CURRENT-DIRECTORY?-VALUE */
Object reclaim_gensym_pathnames_under_current_directory_qm_value(gensym_pathname_list,
	    gensymed_symbol)
    Object gensym_pathname_list, gensymed_symbol;
{
    x_note_fn_call(131,48);
    reclaim_path_list_of_gensym_pathnames(gensym_pathname_list);
    return VALUES_1(Nil);
}

/* ADD-ITEMS-TO-EDIT-WORKSPACE-FOR-KB-LOAD-FILE-COMMAND */
Object add_items_to_edit_workspace_for_kb_load_file_command(kb_load_file_command,
	    edit_workspace,edit_box,refresh_case_qm)
    Object kb_load_file_command, edit_workspace, edit_box, refresh_case_qm;
{
    x_note_fn_call(131,49);
    if (refresh_case_qm)
	return move_file_command_items_if_necessary(kb_load_file_command,
		edit_workspace,edit_box);
    else
	return make_load_command_items_and_add_to_workspace(kb_load_file_command,
		edit_workspace,edit_box);
}

static Object Qcheck_box;          /* check-box */

/* MOVE-FILE-COMMAND-ITEMS-IF-NECESSARY */
Object move_file_command_items_if_necessary(file_command,workspace,edit_box)
    Object file_command, workspace, edit_box;
{
    Object gensymed_symbol, left_edge, ab_queue_form_, ab_next_queue_element_;
    Object subblock, sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, top_edge;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, delta_y, delta_x;
    char temp;

    x_note_fn_call(131,50);
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)10L;
    top_edge = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
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
    if (temp ? TRUEP(memq_function(subblock,ISVREF(file_command,
	    (SI_Long)9L))) : TRUEP(Nil)) {
	gensymed_symbol_1 = top_edge;
	gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_y = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_1 = IFIX(left_edge);
	gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	delta_x = gensymed_symbol_1 - gensymed_symbol_2;
	if ( !(delta_y == (SI_Long)0L && delta_x == (SI_Long)0L)) {
	    move_block(subblock,FIX(delta_x),FIX(delta_y));
	    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_1;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qcheck_box,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
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
	    if (temp)
		move_block(subblock,FIX(delta_x),FIX(delta_y));
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qdo_pathname_component_conversion;  /* do-pathname-component-conversion */

static Object Qvms;                /* vms */

/* DO-PATHNAME-COMPONENT-CONVERSION */
Object do_pathname_component_conversion(original_pathname,
	    merged_pathname_qm,cursor_should_retreat_p)
    Object original_pathname, merged_pathname_qm, cursor_should_retreat_p;
{
    Object tag_temp, svref_new_value;
    volatile Object new_namestring_text;
    volatile Object new_namestring;
    Object text_tail, line_index, character_index, line_index_at_end;
    Object character_index_at_end;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(131,51);
    SAVE_STACK();
    tag_temp = UNIQUE_TAG(Qdo_pathname_component_conversion);
    if (PUSH_CATCH(tag_temp,1)) {
	if (merged_pathname_qm) {
	    if (EQ(Local_file_system,Qvms)) {
		if ( !TRUEP(ISVREF(merged_pathname_qm,(SI_Long)2L))) {
		    svref_new_value = 
			    copy_pathname_contents(ISVREF(original_pathname,
			    (SI_Long)2L));
		    SVREF(merged_pathname_qm,FIX((SI_Long)2L)) = 
			    svref_new_value;
		}
	    }
	    new_namestring_text = Qunbound_in_protected_let;
	    new_namestring = Qunbound_in_protected_let;
	    text_tail = Qunbound_in_protected_let;
	    line_index = Qunbound_in_protected_let;
	    character_index = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		new_namestring_text = gensym_namestring(1,merged_pathname_qm);
		new_namestring = copy_text_string(new_namestring_text);
		text_tail = ISVREF(Current_edit_state,(SI_Long)15L);
		line_index = FIX((SI_Long)1L);
		character_index = FIX((SI_Long)0L);
		result = find_end_of_text(2,text_tail,line_index);
		MVS_2(result,line_index_at_end,character_index_at_end);
		insert_text_string_in_text_being_edited(8,new_namestring,
			Nil,Nil,line_index,character_index,text_tail,
			line_index_at_end,character_index_at_end);
		if (cursor_should_retreat_p)
		    move_or_delete_from_cursor(3,Nil,T,Nil);
		result = VALUES_1(T);
		THROW(tag_temp,result);
	    }
	    POP_UNWIND_PROTECT(0);
	    if (new_namestring) {
		if ( !EQ(new_namestring,Qunbound_in_protected_let))
		    reclaim_text_string(new_namestring);
	    }
	    if (new_namestring_text) {
		if ( !EQ(new_namestring_text,Qunbound_in_protected_let))
		    reclaim_text_string(new_namestring_text);
	    }
	    CONTINUE_UNWINDING(0);
	}
	result = VALUES_1(Nil);
	THROW(tag_temp,result);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object Qgensym_pathnames_under_current_directory_qm;  /* gensym-pathnames-under-current-directory? */

static Object Qcurrent_directory_contents_statistics_qm;  /* current-directory-contents-statistics? */

/* CLEAR-LOAD-COMMAND-DIRECTORY-INFORMATION */
Object clear_load_command_directory_information(kb_load_file_command)
    Object kb_load_file_command;
{
    x_note_fn_call(131,52);
    reclaim_path_list_of_gensym_pathnames(get_lookup_slot_value_given_default(kb_load_file_command,
	    Qgensym_pathnames_under_current_directory_qm,Nil));
    set_non_savable_lookup_slot_value(kb_load_file_command,
	    Qgensym_pathnames_under_current_directory_qm,Nil);
    change_slot_value(3,kb_load_file_command,
	    Qcurrent_directory_contents_statistics_qm,Nil);
    clear_file_and_directory_name_directories(kb_load_file_command);
    return VALUES_1(Nil);
}

/* DO-PATHNAME-COMPONENT-CONVERSION-IF-NECESSARY */
Object do_pathname_component_conversion_if_necessary(text_tail_qm,
	    text_string_to_insert_qm)
    Object text_tail_qm, text_string_to_insert_qm;
{
    Object vms_directory_filenames_can_dangle_p;
    volatile Object pathname_text;
    volatile Object pathname_ascii;
    volatile Object ascii_to_insert;
    volatile Object merged_pathname_qm;
    Object kb_load_file_command;
    volatile Object original_pathname_qm;
    Object directory_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(131,53);
    SAVE_STACK();
    if (text_tail_qm && text_string_to_insert_qm) {
	vms_directory_filenames_can_dangle_p = Qunbound_in_protected_let;
	pathname_text = Qunbound_in_protected_let;
	pathname_ascii = Qunbound_in_protected_let;
	ascii_to_insert = Qunbound_in_protected_let;
	merged_pathname_qm = Qunbound_in_protected_let;
	kb_load_file_command = Qunbound_in_protected_let;
	PUSH_SPECIAL_WITH_SYMBOL(Vms_directory_filenames_can_dangle_p,Qvms_directory_filenames_can_dangle_p,vms_directory_filenames_can_dangle_p,
		0);
	  if (PUSH_UNWIND_PROTECT(1)) {
	      Vms_directory_filenames_can_dangle_p = T;
	      pathname_text = convert_text_to_text_string(1,
		      ISVREF(Current_edit_state,(SI_Long)15L));
	      pathname_ascii = copy_text_string(pathname_text);
	      ascii_to_insert = copy_text_string(text_string_to_insert_qm);
	      merged_pathname_qm = 
		      gensym_merge_pathnames_function(ascii_to_insert,
		      pathname_ascii,Nil);
	      kb_load_file_command = ISVREF(Current_edit_state,(SI_Long)3L);
	      if (merged_pathname_qm)
		  merged_pathname_qm = 
			  resolve_directory_sl_file_ambiguities_in_kb_load_file_command(kb_load_file_command,
			  merged_pathname_qm);
	      clear_load_command_directory_information(kb_load_file_command);
	      if (EQ(Local_file_system,Qvms) || 
		      gensym_wild_pathname_p(pathname_ascii)) {
		  original_pathname_qm = Qunbound_in_protected_let;
		  if (PUSH_UNWIND_PROTECT(0)) {
		      original_pathname_qm = gensym_pathname(pathname_ascii);
		      if (original_pathname_qm)
			  SAVE_VALUES(do_pathname_component_conversion(original_pathname_qm,
				  merged_pathname_qm,T));
		      else
			  SAVE_VALUES(VALUES_1(Nil));
		  }
		  POP_UNWIND_PROTECT(0);
		  if (original_pathname_qm) {
		      if ( !EQ(original_pathname_qm,Qunbound_in_protected_let))
			  reclaim_gensym_pathname(original_pathname_qm);
		  }
		  CONTINUE_UNWINDING(0);
	      }
	      else if (g2_stream_directory_p(pathname_ascii)) {
		  directory_pathname_qm = 
			  gensym_file_as_directory(pathname_ascii);
		  if (directory_pathname_qm)
		      SAVE_VALUES(do_pathname_component_conversion(directory_pathname_qm,
			      merged_pathname_qm,Nil));
		  else
		      SAVE_VALUES(VALUES_1(Nil));
	      }
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	  }
	  POP_UNWIND_PROTECT(1);
	  if (merged_pathname_qm) {
	      if ( !EQ(merged_pathname_qm,Qunbound_in_protected_let))
		  reclaim_gensym_pathname(merged_pathname_qm);
	  }
	  if (ascii_to_insert) {
	      if ( !EQ(ascii_to_insert,Qunbound_in_protected_let))
		  reclaim_text_string(ascii_to_insert);
	  }
	  if (pathname_ascii) {
	      if ( !EQ(pathname_ascii,Qunbound_in_protected_let))
		  reclaim_text_string(pathname_ascii);
	  }
	  if (pathname_text) {
	      if ( !EQ(pathname_text,Qunbound_in_protected_let))
		  reclaim_text_string(pathname_text);
	  }
	  CONTINUE_UNWINDING(1);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* MOVE-BLOCK */
Object move_block(block,delta_x,delta_y)
    Object block, delta_x, delta_y;
{
    x_note_fn_call(131,54);
    update_images_of_block(block,T,Nil);
    shift_block(block,delta_x,delta_y);
    enlarge_workspace_for_block_rectangle_if_necessary(block,Nil);
    return update_images_of_block(block,Nil,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Automatically_resolve_conflicts_by_default, Qautomatically_resolve_conflicts_by_default);

DEFINE_VARIABLE_WITH_SYMBOL(Update_before_loading_by_default, Qupdate_before_loading_by_default);

static Object Qfile_command_info_table_format;  /* file-command-info-table-format */

static Object Qfile_command_attribute_value_format;  /* file-command-attribute-value-format */

static Object Qfont_for_editing;   /* font-for-editing */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qupdate_before_loading;  /* update-before-loading */

static Object Qmerge_kb;           /* merge-kb */

static Object Qmerging_kb_is_the_default_qm;  /* merging-kb-is-the-default? */

static Object Qautomatically_resolving_conflicts;  /* automatically-resolving-conflicts */

/* MAKE-LOAD-COMMAND-ITEMS-AND-ADD-TO-WORKSPACE */
Object make_load_command_items_and_add_to_workspace(file_command,workspace,
	    edit_box)
    Object file_command, workspace, edit_box;
{
    Object gensymed_symbol, left_edge, top_edge;
    Object current_directory_information_text_table, svref_arg_1;
    Object svref_new_value, column_top_edge, column_right_edge_so_far, column;
    Object row, ab_loop_list_, label, name, check_box, ab_loop_desetq_, temp;
    Object temp_1, right_edge, bottom_edge;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value_1;
    SI_Long gensymed_symbol_3;
    Declare_special(2);
    Object result;

    x_note_fn_call(131,55);
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge = gensymed_symbol;
    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)10L;
    top_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    current_directory_information_text_table = make_attributes_table(8,
	    file_command,Qfile_command_info_table_format,Nil,
	    choose_font_format_per_fonts_table(Qfile_command_attribute_value_format,
	    Qfont_for_editing),Nil,list_constant_6,Nil,list_constant_6);
    add_to_workspace(6,current_directory_information_text_table,workspace,
	    left_edge,top_edge,T,T);
    svref_arg_1 = Current_edit_state;
    svref_new_value = 
	    get_token_menu_class_per_category_overrides_for_file_command();
    SVREF(svref_arg_1,FIX((SI_Long)74L)) = svref_new_value;
    svref_arg_1 = Current_edit_state;
    gensymed_symbol = ISVREF(current_directory_information_text_table,
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(current_directory_information_text_table,
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    svref_new_value_1 = gensymed_symbol_1 - gensymed_symbol_2;
    ISVREF(svref_arg_1,(SI_Long)70L) = FIX(svref_new_value_1);
    gensymed_symbol = ISVREF(current_directory_information_text_table,
	    (SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = (SI_Long)10L;
    top_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    svref_arg_1 = Current_edit_state;
    ISVREF(svref_arg_1,(SI_Long)71L) = FIX((SI_Long)100000L);
    svref_arg_1 = Current_edit_state;
    svref_new_value = File_name_punctuation_alist;
    SVREF(svref_arg_1,FIX((SI_Long)72L)) = svref_new_value;
    column_top_edge = top_edge;
    column_right_edge_so_far = left_edge;
    column = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,1);
    next_loop:
      if (IFIX(Column) > (SI_Long)1L)
	  goto end_loop;
      row = Nil;
      ab_loop_list_ = list_constant_7;
      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	label = Nil;
	name = Nil;
	check_box = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	Row = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_desetq_ = nthcdr(FIXNUM_ADD(Column,Column),Row);
	label = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	name = CAR(temp);
	if ( !( !TRUEP(label) || EQ(name,Qupdate_before_loading) &&  
		!TRUEP(Source_code_control_support_enabled_p))) {
	    temp = copy_text_string(label);
	    check_box = make_button(7,Qcheck_box,temp,name,T,Nil,Nil,T);
	}
	else
	    check_box = Nil;
	if (check_box) {
	    if (EQ(name,Qmerge_kb)) {
		if (get_lookup_slot_value_given_default(file_command,
			Qmerging_kb_is_the_default_qm,Nil))
		    change_on_sl_off_switch(check_box,T);
	    }
	    else if (EQ(name,Qautomatically_resolving_conflicts)) {
		if (Automatically_resolve_conflicts_by_default)
		    change_on_sl_off_switch(check_box,T);
	    }
	    else if (EQ(name,Qupdate_before_loading)) {
		if (Update_before_loading_by_default)
		    change_on_sl_off_switch(check_box,T);
	    }
	    add_to_workspace(6,check_box,workspace,left_edge,top_edge,T,Nil);
	    result = determine_extreme_edges_of_block(check_box);
	    MVS_4(result,temp,temp,right_edge,bottom_edge);
	    svref_arg_1 = Current_edit_state;
	    gensymed_symbol_1 = IFIX(ISVREF(Current_edit_state,(SI_Long)70L));
	    gensymed_symbol_2 = IFIX(bottom_edge) + (SI_Long)10L;
	    gensymed_symbol = ISVREF(edit_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    svref_new_value_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
	    ISVREF(svref_arg_1,(SI_Long)70L) = FIX(svref_new_value_1);
	    if ( !EQ(name,Qupdate_before_loading))
		column_right_edge_so_far = 
			FIXNUM_MAX(column_right_edge_so_far,right_edge);
	    gensymed_symbol = ISVREF(check_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)10L;
	    top_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	goto next_loop_1;
      end_loop_1:;
      POP_SPECIAL();
      left_edge = FIX(IFIX(column_right_edge_so_far) + (SI_Long)10L);
      top_edge = column_top_edge;
      Column = FIXNUM_ADD1(Column);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qcurrent_namestring_as_text_string_for_file_command_qm;  /* current-namestring-as-text-string-for-file-command? */

static Object Qunix;               /* unix */

static Object Qcurrent_directory_namestring_for_file_command_qm;  /* current-directory-namestring-for-file-command? */

static Object Qcurrent_directory_namestring_as_text_string_for_file_command_qm;  /* current-directory-namestring-as-text-string-for-file-command? */

/* RESOLVE-DIRECTORY/FILE-AMBIGUITIES-IN-KB-LOAD-FILE-COMMAND */
Object resolve_directory_sl_file_ambiguities_in_kb_load_file_command(kb_load_file_command,
	    gensym_pathname_1)
    Object kb_load_file_command, gensym_pathname_1;
{
    Object namestring_as_text_string, wild_pathname_p, truename_qm;
    Object temporary_namestring, temp;
    char temp_1;

    x_note_fn_call(131,56);
    namestring_as_text_string = gensym_namestring_as_text_string(1,
	    gensym_pathname_1);
    wild_pathname_p = gensym_wild_pathname_p(gensym_pathname_1);
    if ( !TRUEP(wild_pathname_p)) {
	if (ISVREF(gensym_pathname_1,(SI_Long)4L) && 
		get_lookup_slot_value_given_default(kb_load_file_command,
		Qcurrent_namestring_as_text_string_for_file_command_qm,Nil)) {
	    if (EQ(ISVREF(gensym_pathname_1,(SI_Long)8L),Qunix)) {
		truename_qm = gensym_probe_file(gensym_pathname_1);
		temporary_namestring = Nil;
		if (truename_qm) {
		    temporary_namestring = gensym_namestring(1,truename_qm);
		    reclaim_gensym_pathname(truename_qm);
		    temp = g2_stream_directory_p(temporary_namestring);
		    reclaim_text_string(temporary_namestring);
		    temp_1 = TRUEP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else {
		temporary_namestring = gensym_namestring(1,gensym_pathname_1);
		temp = g2_stream_directory_p(temporary_namestring);
		reclaim_text_string(temporary_namestring);
		temp_1 = TRUEP(temp);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = gensym_file_as_directory(gensym_pathname_1);
	    if (temp);
	    else
		temp = make_empty_gensym_pathname();
	    reclaim_gensym_pathname(gensym_pathname_1);
	    gensym_pathname_1 = temp;
	    temp = gensym_namestring_as_text_string(1,gensym_pathname_1);
	    reclaim_text_string(namestring_as_text_string);
	    namestring_as_text_string = temp;
	}
    }
    change_slot_value(3,kb_load_file_command,
	    Qcurrent_directory_namestring_for_file_command_qm,
	    gensym_directory_and_above_namestring(1,gensym_pathname_1));
    change_slot_value(3,kb_load_file_command,
	    Qcurrent_directory_namestring_as_text_string_for_file_command_qm,
	    wild_pathname_p ? gensym_namestring_as_text_string(1,
	    gensym_pathname_1) : 
	    gensym_directory_and_above_namestring_as_text_string(1,
	    gensym_pathname_1));
    change_slot_value(3,kb_load_file_command,
	    Qcurrent_namestring_as_text_string_for_file_command_qm,
	    namestring_as_text_string);
    return VALUES_1(gensym_pathname_1);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object string_constant_18;  /* "Cannot find ~s" */

static Object Kdisplay_notification;  /* :display-notification */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object Qretain_current_directory_menus_p;  /* retain-current-directory-menus-p */

static Object string_constant_19;  /* "~s is not a file or directory name" */

/* HANDLE-END-OPERATION-FOR-KB-LOAD-FILE-COMMAND */
Object handle_end_operation_for_kb_load_file_command(kb_load_file_command,
	    workstation_context)
    Object kb_load_file_command, workstation_context;
{
    Object edit_state, edit_text_as_string, token_value;
    Object token_type_or_partial_types, character_index_after_token, temp;
    Object edit_text_as_token_qm, dwimified_edit_text_as_string;
    Object filename_text_string, vms_directory_filenames_can_dangle_p;
    Object gensym_pathname_qm, probed_pathname_qm;
    Object possibly_new_gensym_pathname, new_namestring, text_tail;
    Object line_index_at_end, character_index_at_end, frame, sub_vector_qm;
    Object function_qm, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4;
    SI_Long line_index, character_index, method_index;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(131,57);
    edit_state = ISVREF(workstation_context,(SI_Long)2L);
    edit_text_as_string = convert_text_to_text_string(1,ISVREF(edit_state,
	    (SI_Long)15L));
    result = token_from_text_string(edit_text_as_string,Nil,Nil);
    MVS_3(result,token_value,token_type_or_partial_types,
	    character_index_after_token);
    if (CONSP(token_type_or_partial_types) || 
	    memq_function(token_type_or_partial_types,list_constant_8)) {
	temp = Nil;
	edit_text_as_token_qm = temp;
    }
    else {
	temp = token_value;
	edit_text_as_token_qm = temp;
    }
    dwimified_edit_text_as_string = text_string_p(edit_text_as_token_qm) ? 
	    edit_text_as_token_qm : copy_text_string(edit_text_as_string);
    filename_text_string = text_string_trim(list_constant_9,
	    dwimified_edit_text_as_string);
    vms_directory_filenames_can_dangle_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Vms_directory_filenames_can_dangle_p,Qvms_directory_filenames_can_dangle_p,vms_directory_filenames_can_dangle_p,
	    0);
      gensym_pathname_qm = 
	      gensym_merge_pathnames_function(filename_text_string,
	      get_lookup_slot_value_given_default(kb_load_file_command,
	      Qcurrent_directory_namestring_for_file_command_qm,Nil),Nil);
      probed_pathname_qm = Nil;
      reclaim_text_string(edit_text_as_string);
      reclaim_text_string(filename_text_string);
      if ( !TRUEP(text_string_p(edit_text_as_token_qm)))
	  reclaim_text_string(dwimified_edit_text_as_string);
      possibly_new_gensym_pathname = 
	      resolve_directory_sl_file_ambiguities_in_kb_load_file_command(kb_load_file_command,
	      gensym_pathname_qm);
      if ( !EQ(gensym_pathname_qm,possibly_new_gensym_pathname)) {
	  gensym_pathname_qm = possibly_new_gensym_pathname;
	  new_namestring = 
		  get_lookup_slot_value_given_default(kb_load_file_command,
		  Qcurrent_namestring_as_text_string_for_file_command_qm,Nil);
	  text_tail = ISVREF(Current_edit_state,(SI_Long)15L);
	  line_index = (SI_Long)1L;
	  character_index = (SI_Long)0L;
	  result = find_end_of_text(2,text_tail,FIX(line_index));
	  MVS_2(result,line_index_at_end,character_index_at_end);
	  insert_text_string_in_text_being_edited(8,new_namestring,Nil,Nil,
		  FIX(line_index),FIX(character_index),text_tail,
		  line_index_at_end,character_index_at_end);
	  if (EQ(Local_file_system,Qvms))
	      move_or_delete_from_cursor(3,Nil,T,Nil);
      }
      force_process_drawing();
      if (gensym_pathname_qm && 
	      (gensym_wild_pathname_p(gensym_pathname_qm) ||  
	      !TRUEP(ISVREF(gensym_pathname_qm,(SI_Long)4L)))) {
	  change_slot_value(3,kb_load_file_command,
		  Qcurrent_directory_contents_statistics_qm,FIX((SI_Long)0L));
	  force_process_drawing();
	  method_index = (SI_Long)42L;
	  frame = kb_load_file_command;
	  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),method_index);
	  function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) :
		   Nil;
	  if (function_qm) {
	      gensymed_symbol = function_qm;
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = ISVREF(Current_edit_state,(SI_Long)12L);
	      gensymed_symbol_3 = ISVREF(Current_edit_state,(SI_Long)13L);
	      gensymed_symbol_4 = T;
	      inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	  }
	  set_up_load_command_directory_information(2,kb_load_file_command,
		  gensym_pathname_qm);
	  reclaim_gensym_pathname(gensym_pathname_qm);
	  result = VALUES_1(T);
      }
      else {
	  if (gensym_pathname_qm) {
	      probed_pathname_qm = gensym_probe_file(gensym_pathname_qm);
	      temp_1 =  !TRUEP(probed_pathname_qm);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      display_editor_notification_1(tformat_text_string(2,
		      string_constant_18,
		      get_lookup_slot_value_given_default(kb_load_file_command,
		      Qcurrent_namestring_as_text_string_for_file_command_qm,
		      Nil)));
	      result = VALUES_1(Kdisplay_notification);
	  }
	  else if (gensym_pathname_qm) {
	      if (SIMPLE_VECTOR_P(probed_pathname_qm) && 
		      EQ(ISVREF(probed_pathname_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
		  reclaim_gensym_pathname(probed_pathname_qm);
	      set_non_savable_lookup_slot_value(kb_load_file_command,
		      Qretain_current_directory_menus_p,T);
	      result = load_or_merge_kb_from_file_command(gensym_pathname_qm,
		      ISVREF(Current_edit_state,(SI_Long)12L));
	  }
	  else {
	      if (SIMPLE_VECTOR_P(probed_pathname_qm) && 
		      EQ(ISVREF(probed_pathname_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
		  reclaim_gensym_pathname(probed_pathname_qm);
	      display_editor_notification_1(tformat_text_string(2,
		      string_constant_19,filename_text_string));
	      reclaim_text_string(filename_text_string);
	      result = VALUES_1(Kdisplay_notification);
	  }
      }
    POP_SPECIAL();
    return result;
}

static Object Qkb_load_file_command;  /* kb-load-file-command */

/* CLEANUP-FOR-KB-LOAD-FILE-COMMAND */
Object cleanup_for_kb_load_file_command(kb_load_file_command)
    Object kb_load_file_command;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(131,58);
    frame = kb_load_file_command;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_load_file_command)) {
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
    if ( !TRUEP(get_lookup_slot_value_given_default(kb_load_file_command,
	    Qretain_current_directory_menus_p,Nil)))
	return clear_load_command_directory_information(kb_load_file_command);
    else
	return VALUES_1(Nil);
}

static Object Qget_file_command_check_box_value;  /* get-file-command-check-box-value */

static Object Qediting;            /* editing */

/* LOAD-OR-MERGE-KB-FROM-FILE-COMMAND */
Object load_or_merge_kb_from_file_command(gensym_pathname_1,edit_workspace)
    Object gensym_pathname_1, edit_workspace;
{
    Object bring_formats_up_to_date_qm, warmboot_case_qm, auto_merge_case_qm;
    Object install_system_tables_if_merge_case_qm;
    Object what_to_do_after_loading_kb_qm, merge_kb_qm;
    Object update_before_loading_qm;
    Object result;

    x_note_fn_call(131,59);
    result = get_button_settings_for_file_command(SYMBOL_FUNCTION(Qget_file_command_check_box_value),
	    edit_workspace);
    MVS_7(result,bring_formats_up_to_date_qm,warmboot_case_qm,
	    auto_merge_case_qm,install_system_tables_if_merge_case_qm,
	    what_to_do_after_loading_kb_qm,merge_kb_qm,
	    update_before_loading_qm);
    abort_current_workstation_context(Qediting);
    return load_or_merge_kb_if_ok(8,gensym_pathname_1,merge_kb_qm ? Nil : 
	    empty_kb_p() ? T : Qreplace,bring_formats_up_to_date_qm,
	    warmboot_case_qm,auto_merge_case_qm,
	    install_system_tables_if_merge_case_qm,
	    what_to_do_after_loading_kb_qm,update_before_loading_qm);
}

/* GET-FILE-COMMAND-CHECK-BOX-VALUE */
Object get_file_command_check_box_value(edit_workspace,button_name)
    Object edit_workspace, button_name;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(131,60);
    gensymed_symbol = ACCESS_ONCE(ISVREF(edit_workspace,(SI_Long)14L));
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
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qcheck_box,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
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
    if (temp ? EQ(get_primary_name_for_frame_if_any(subblock),button_name) 
	    : TRUEP(Nil))
	return on_sl_off_switch_on_p(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qbring_formats_up_to_date;  /* bring-formats-up-to-date */

static Object Qwarmbooting_afterwards;  /* warmbooting-afterwards */

static Object Qwarmbooting_afterwards_with_catch_up;  /* warmbooting-afterwards-with-catch-up */

static Object Qstarting_afterwards;  /* starting-afterwards */

static Object Qnot_starting_afterwards;  /* not-starting-afterwards */

static Object Qmerge_kb_and_install_system_tables;  /* merge-kb-and-install-system-tables */

/* GET-BUTTON-SETTINGS-FOR-FILE-COMMAND */
Object get_button_settings_for_file_command(getter,arg)
    Object getter, arg;
{
    Object bring_formats_up_to_date_qm, auto_merge_case_qm, warmboot_case_qm;
    Object what_to_do_after_loading_kb_qm;
    Object merge_kb_and_install_system_tables_qm, merge_kb_qm;
    Object update_before_loading_qm;

    x_note_fn_call(131,61);
    bring_formats_up_to_date_qm = FUNCALL_2(getter,arg,
	    Qbring_formats_up_to_date);
    auto_merge_case_qm = FUNCALL_2(getter,arg,
	    Qautomatically_resolving_conflicts);
    warmboot_case_qm = FUNCALL_2(getter,arg,Qwarmbooting_afterwards) ? 
	    Qwarmboot_afterwards : FUNCALL_2(getter,arg,
	    Qwarmbooting_afterwards_with_catch_up) ? 
	    Qwarmboot_afterwards_with_catch_up : Nil;
    if (warmboot_case_qm)
	what_to_do_after_loading_kb_qm = warmboot_case_qm;
    else if (FUNCALL_2(getter,arg,Qstarting_afterwards))
	what_to_do_after_loading_kb_qm = Qstart_afterwards;
    else if (FUNCALL_2(getter,arg,Qnot_starting_afterwards))
	what_to_do_after_loading_kb_qm = Qnever_start_afterwards;
    else
	what_to_do_after_loading_kb_qm = Qnil;
    merge_kb_and_install_system_tables_qm = FUNCALL_2(getter,arg,
	    Qmerge_kb_and_install_system_tables);
    merge_kb_qm = merge_kb_and_install_system_tables_qm;
    if (merge_kb_qm);
    else
	merge_kb_qm = FUNCALL_2(getter,arg,Qmerge_kb);
    update_before_loading_qm = Source_code_control_support_enabled_p ? 
	    FUNCALL_2(getter,arg,Qupdate_before_loading) : Qnil;
    return VALUES_7(bring_formats_up_to_date_qm,warmboot_case_qm,
	    auto_merge_case_qm,merge_kb_and_install_system_tables_qm,
	    what_to_do_after_loading_kb_qm,merge_kb_qm,
	    update_before_loading_qm);
}

/* MAKE-AND-SET-UP-KB-LOAD-FILE-COMMAND */
Object make_and_set_up_kb_load_file_command(merge_case_qm)
    Object merge_case_qm;
{
    Object kb_load_file_command, default_pathname, temp, temp_1;
    Object svref_new_value;

    x_note_fn_call(131,62);
    kb_load_file_command = make_text_box(Qkb_load_file_command);
    default_pathname = get_or_make_default_kb_pathname(0);
    if (ISVREF(kb_load_file_command,(SI_Long)16L))
	reclaim_slot_value(ISVREF(kb_load_file_command,(SI_Long)16L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_load_file_command,Qbox_translation_and_text);
    temp = No_value;
    if ( !TRUEP(Current_kb_pathname_qm)) {
	temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	temp_1 = slot_value_list_2(temp_1,
		gensym_directory_and_above_namestring_as_text_string(1,
		default_pathname));
    }
    else {
	temp_1 =  !TRUEP(ISVREF(default_pathname,(SI_Long)4L)) ? 
		slot_value_cons_1(make_lost_spaces_text_element(FIX((SI_Long)0L)),
		Nil) : Nil;
	temp_1 = nconc2(temp_1,
		slot_value_cons_1(gensym_namestring_as_text_string(1,
		default_pathname),Nil));
    }
    svref_new_value = slot_value_cons_1(temp,temp_1);
    SVREF(kb_load_file_command,FIX((SI_Long)16L)) = svref_new_value;
    set_up_load_command_directory_information(4,kb_load_file_command,
	    default_pathname,T,merge_case_qm);
    reclaim_gensym_pathname(default_pathname);
    return VALUES_1(kb_load_file_command);
}

static Object Qfile_command_directory_search_cache_qm;  /* file-command-directory-search-cache? */

static Object string_constant_20;  /* "*" */

static Object string_constant_21;  /* "*.*" */

/* SET-UP-LOAD-COMMAND-DIRECTORY-INFORMATION */
Object set_up_load_command_directory_information varargs_1(int, n)
{
    Object kb_load_file_command, gensym_pathname_1;
    Object dont_search_directory_qm, merge_case_qm;
    Object file_system_directory_search_cache;
    Object file_system_directory_search_cache_active_p, temp;
    Object file_system_directory_search_cache_wildcard_string;
    Declare_varargs_nonrelocating;
    Declare_special(3);
    Object result;

    x_note_fn_call(131,63);
    INIT_ARGS_nonrelocating();
    kb_load_file_command = REQUIRED_ARG_nonrelocating();
    gensym_pathname_1 = REQUIRED_ARG_nonrelocating();
    dont_search_directory_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    merge_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    file_system_directory_search_cache = 
	    get_lookup_slot_value_given_default(kb_load_file_command,
	    Qfile_command_directory_search_cache_qm,Nil);
    file_system_directory_search_cache_active_p = T;
    temp = string_constant_20;
    if (temp);
    else
	temp = string_constant_21;
    file_system_directory_search_cache_wildcard_string = temp;
    PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_wildcard_string,Qfile_system_directory_search_cache_wildcard_string,file_system_directory_search_cache_wildcard_string,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_active_p,Qfile_system_directory_search_cache_active_p,file_system_directory_search_cache_active_p,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache,Qfile_system_directory_search_cache,file_system_directory_search_cache,
		0);
	  set_non_savable_lookup_slot_value(kb_load_file_command,
		  Qcurrent_directory_namestring_for_file_command_qm,
		  gensym_directory_and_above_namestring(1,gensym_pathname_1));
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(kb_load_file_command,
		      Qcurrent_directory_namestring_as_text_string_for_file_command_qm);
	  set_lookup_slot_value_1(kb_load_file_command,
		  Qcurrent_directory_namestring_as_text_string_for_file_command_qm,
		  gensym_wild_pathname_p(gensym_pathname_1) ? 
		  gensym_namestring_as_text_string(1,gensym_pathname_1) : 
		  gensym_directory_and_above_namestring_as_text_string(1,
		  gensym_pathname_1));
	  set_non_savable_lookup_slot_value(kb_load_file_command,
		  Qcurrent_namestring_as_text_string_for_file_command_qm,
		  gensym_namestring_as_text_string(1,gensym_pathname_1));
	  set_non_savable_lookup_slot_value(kb_load_file_command,
		  Qmerging_kb_is_the_default_qm,merge_case_qm);
	  if ( !TRUEP(dont_search_directory_qm)) {
	      reclaim_path_list_of_gensym_pathnames(get_lookup_slot_value_given_default(kb_load_file_command,
		      Qgensym_pathnames_under_current_directory_qm,Nil));
	      set_non_savable_lookup_slot_value(kb_load_file_command,
		      Qgensym_pathnames_under_current_directory_qm,
		      get_load_command_directory(kb_load_file_command,
		      gensym_wild_pathname_p(gensym_pathname_1) ? 
		      copy_gensym_pathname(gensym_pathname_1) : Qnil));
	      set_up_current_directory_information_text_based_on_other_slots(kb_load_file_command);
	      set_up_file_and_directory_name_directories(kb_load_file_command);
	      temp = 
		      set_non_savable_lookup_slot_value(kb_load_file_command,
		      Qfile_command_directory_search_cache_qm,
		      seize_file_system_directory_search_cache());
	  }
	  else
	      temp = Nil;
	  reclaim_file_system_directory_search_cache();
	  result = VALUES_1(temp);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object array_constant_7;    /* # */

/* NAMESTRING-IS-XML-FILE-P */
Object namestring_is_xml_file_p(text_string)
    Object text_string;
{
    Object temp;
    SI_Long length_4;

    x_note_fn_call(131,64);
    length_4 = IFIX(lengthw(text_string)) - (SI_Long)4L;
    temp = (SI_Long)1L <= length_4 ? text_string_search(array_constant_7,
	    text_string,FIX(length_4),Nil) : Qnil;
    reclaim_text_string(text_string);
    return VALUES_1(temp);
}

static Object Qnamestring_is_xml_file_p;  /* namestring-is-xml-file-p */

static Object Qload_command_file_types;  /* load-command-file-types */

/* GET-LOAD-COMMAND-DIRECTORY */
Object get_load_command_directory(load_command,user_supplied_wild_pathname_qm)
    Object load_command, user_supplied_wild_pathname_qm;
{
    Object current_directory_namestring;
    Object match_regular_expression_for_g2_stream_directory_hook, file_type;
    Object ab_loop_list_, wild_gensym_pathname, first_time_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Declare_special(1);
    Object result;

    x_note_fn_call(131,65);
    current_directory_namestring = 
	    get_lookup_slot_value_given_default(load_command,
	    Qcurrent_directory_namestring_for_file_command_qm,Nil);
    if (user_supplied_wild_pathname_qm)
	return gensym_directory_using_cache(2,
		user_supplied_wild_pathname_qm,T);
    else {
	match_regular_expression_for_g2_stream_directory_hook = 
		Need_to_check_plist_p ? Qnamestring_is_xml_file_p : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Match_regular_expression_for_g2_stream_directory_hook,Qmatch_regular_expression_for_g2_stream_directory_hook,match_regular_expression_for_g2_stream_directory_hook,
		0);
	  file_type = Nil;
	  ab_loop_list_ = get_lookup_slot_value(load_command,
		  Qload_command_file_types);
	  wild_gensym_pathname = Nil;
	  first_time_qm = T;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  file_type = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  wild_gensym_pathname = 
		  gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		  Kwild,file_type,Nil,current_directory_namestring);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      first_time_qm = Nil;
	  ab_loopvar__2 = gensym_directory_using_cache(2,
		  wild_gensym_pathname,first_time_qm);
	  if (ab_loopvar__2) {
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = last(ab_loopvar__2,_);
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(ab_loopvar_);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(All_file_namestrings_in_directory_of_names, Qall_file_namestrings_in_directory_of_names);

DEFINE_VARIABLE_WITH_SYMBOL(All_directory_namestrings_in_directory_of_names, Qall_directory_namestrings_in_directory_of_names);

DEFINE_VARIABLE_WITH_SYMBOL(Defaults_namestring_for_directory_of_names_qm, Qdefaults_namestring_for_directory_of_names_qm);

static Object Qfile_name;          /* file-name */

static Object Qdirectory_name;     /* directory-name */

/* CLEAR-FILE-AND-DIRECTORY-NAME-DIRECTORIES */
Object clear_file_and_directory_name_directories(file_command)
    Object file_command;
{
    Object namestring_1, ab_loop_list_, temp, current_directory_namestring_qm;

    x_note_fn_call(131,66);
    namestring_1 = Nil;
    ab_loop_list_ = All_file_namestrings_in_directory_of_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    namestring_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(namestring_1,Qfile_name);
    goto next_loop;
  end_loop:;
    namestring_1 = Nil;
    ab_loop_list_ = All_directory_namestrings_in_directory_of_names;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    namestring_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_from_directory_of_names(namestring_1,Qdirectory_name);
    goto next_loop_1;
  end_loop_1:;
    temp = Nil;
    reclaim_slot_value(All_directory_namestrings_in_directory_of_names);
    All_directory_namestrings_in_directory_of_names = temp;
    temp = Nil;
    reclaim_slot_value(All_file_namestrings_in_directory_of_names);
    All_file_namestrings_in_directory_of_names = temp;
    current_directory_namestring_qm = 
	    get_lookup_slot_value_given_default(file_command,
	    Qcurrent_directory_namestring_for_file_command_qm,Nil);
    if (current_directory_namestring_qm) {
	temp = copy_text_string(current_directory_namestring_qm);
	reclaim_slot_value(Defaults_namestring_for_directory_of_names_qm);
	Defaults_namestring_for_directory_of_names_qm = temp;
    }
    return VALUES_1(Nil);
}

/* SET-UP-FILE-AND-DIRECTORY-NAME-DIRECTORIES */
Object set_up_file_and_directory_name_directories(file_command)
    Object file_command;
{
    x_note_fn_call(131,67);
    clear_file_and_directory_name_directories(file_command);
    return update_name_directories_per_file_command(file_command);
}

static Object string_constant_22;  /* "~a~a" */

static Object array_constant_8;    /* # */

/* UPDATE-NAME-DIRECTORIES-PER-FILE-COMMAND */
Object update_name_directories_per_file_command(file_command)
    Object file_command;
{
    Object gensym_pathname_1, ab_loop_list_, enough_namestring_as_text_string;
    Object directory_p, temp, nicer_enough_namestring_as_text_string;

    x_note_fn_call(131,68);
    gensym_pathname_1 = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(file_command,
	    Qgensym_pathnames_under_current_directory_qm,Nil);
    enough_namestring_as_text_string = Nil;
    directory_p = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensym_pathname_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = gensym_pathname_1;
    enough_namestring_as_text_string = 
	    gensym_enough_namestring_as_text_string(2,temp,
	    get_lookup_slot_value_given_default(file_command,
	    Qcurrent_directory_namestring_for_file_command_qm,Nil));
    directory_p =  !TRUEP(ISVREF(gensym_pathname_1,(SI_Long)4L)) ? T : Nil;
    if (string_eq_w(enough_namestring_as_text_string,array_constant_5))
	reclaim_text_string(enough_namestring_as_text_string);
    else {
	nicer_enough_namestring_as_text_string = tformat_text_string(3,
		string_constant_22,enough_namestring_as_text_string,
		directory_p ? array_constant_5 : array_constant_8);
	reclaim_text_string(enough_namestring_as_text_string);
	add_to_directory_of_names(nicer_enough_namestring_as_text_string,
		directory_p ? Qdirectory_name : Qfile_name);
	if (directory_p)
	    All_directory_namestrings_in_directory_of_names = 
		    slot_value_cons_1(nicer_enough_namestring_as_text_string,
		    All_directory_namestrings_in_directory_of_names);
	else
	    All_file_namestrings_in_directory_of_names = 
		    slot_value_cons_1(nicer_enough_namestring_as_text_string,
		    All_file_namestrings_in_directory_of_names);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_23;  /* "(directory unknown)" */

/* WRITE-FILE-COMMAND-DIRECTORY-NAMESTRING-AS-TEXT-STRING?-FROM-SLOT */
Object write_file_command_directory_namestring_as_text_string_qm_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(131,69);
    if ( !TRUEP(value))
	return tformat(1,string_constant_23);
    else
	return tformat(2,string_constant_7,value);
}

static Object string_constant_24;  /* "(contents unknown~a)" */

static Object array_constant_9;    /* # */

static Object string_constant_25;  /* "~d Director~a, ~d File~a" */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

/* WRITE-DIRECTORY-CONTENTS-STATISTICS?-FROM-SLOT */
Object write_directory_contents_statistics_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object number_of_directories, number_of_files;

    x_note_fn_call(131,70);
    if ( !TRUEP(value) || EQ(value,FIX((SI_Long)0L)))
	return tformat(2,string_constant_24,EQ(value,FIX((SI_Long)0L)) ? 
		array_constant_9 : array_constant_5);
    else if (CONSP(value)) {
	number_of_directories = FIRST(value);
	number_of_files = SECOND(value);
	return tformat(5,string_constant_25,number_of_directories,
		IFIX(number_of_directories) == (SI_Long)1L ? 
		array_constant_10 : array_constant_11,number_of_files,
		IFIX(number_of_files) == (SI_Long)1L ? array_constant_5 : 
		array_constant_12);
    }
    else
	return VALUES_1(Qnil);
}

/* SET-UP-CURRENT-DIRECTORY-INFORMATION-TEXT-BASED-ON-OTHER-SLOTS */
Object set_up_current_directory_information_text_based_on_other_slots(kb_load_file_command)
    Object kb_load_file_command;
{
    Object gensym_pathname_1, ab_loop_list_, directory_p;
    SI_Long number_of_directories, number_of_files;

    x_note_fn_call(131,71);
    gensym_pathname_1 = Nil;
    ab_loop_list_ = 
	    get_lookup_slot_value_given_default(kb_load_file_command,
	    Qgensym_pathnames_under_current_directory_qm,Nil);
    directory_p = Nil;
    number_of_directories = (SI_Long)0L;
    number_of_files = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensym_pathname_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    directory_p =  !TRUEP(ISVREF(gensym_pathname_1,(SI_Long)4L)) ? T : Nil;
    if (directory_p)
	number_of_directories = number_of_directories + (SI_Long)1L;
    if ( !TRUEP(directory_p))
	number_of_files = number_of_files + (SI_Long)1L;
    goto next_loop;
  end_loop:
    change_slot_value(3,kb_load_file_command,
	    Qcurrent_directory_contents_statistics_qm,
	    slot_value_list_2(FIX(number_of_directories),
	    FIX(number_of_files)));
    return VALUES_1(Qnil);
}

/* EXECUTE-COMMAND-FOR-FILE-COMMAND */
Object execute_command_for_file_command(file_command)
    Object file_command;
{
    x_note_fn_call(131,72);
    return execute_file_command(file_command);
}

/* EXECUTE-COMMAND-FOR-INIT-FILE-COMMAND */
Object execute_command_for_init_file_command(init_file_command)
    Object init_file_command;
{
    Object temp;

    x_note_fn_call(131,73);
    temp = ISVREF(init_file_command,(SI_Long)16L);
    temp = CAR(temp);
    if (EQ(temp,Qstart_g2))
	return VALUES_1(Nil);
    else
	return execute_file_command(init_file_command);
}

/* MAKE-FIRST-TIME-DEFAULT-PATHNAME */
Object make_first_time_default_pathname(symbolic_file_type)
    Object symbolic_file_type;
{
    volatile Object user_name;
    Object temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,74);
    SAVE_STACK();
    user_name = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	user_name = tformat_text_string(2,string_constant_7,
		get_current_user_name());
	temp = user_name;
	temp_1 = make_default_file_type(symbolic_file_type);
	SAVE_VALUES(gensym_make_pathname_with_copied_components(Nil,Nil,
		Nil,temp,temp_1,Knewest,Process_specific_system_pathname));
    }
    POP_UNWIND_PROTECT(0);
    if (user_name) {
	if ( !EQ(user_name,Qunbound_in_protected_let))
	    reclaim_text_string(user_name);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PROBE-FOR-KB-NAMED-BY-TEXT-STRING */
Object probe_for_kb_named_by_text_string(text_string)
    Object text_string;
{
    volatile Object namestring_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(131,75);
    SAVE_STACK();
    namestring_1 = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	namestring_1 = copy_text_string(text_string);
	SAVE_VALUES(probe_for_kb_pathname(namestring_1));
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_1) {
	if ( !EQ(namestring_1,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_1);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PROBE-FOR-KB-PATHNAME */
Object probe_for_kb_pathname(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object mergeable_pathname;
    Object mergeable_pathname_with_home;
    volatile Object default_pathname;
    volatile Object merge_series;
    Object merged_pathname;
    volatile Object less_case_sensitive_pathname;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(131,76);
    SAVE_STACK();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      mergeable_pathname = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  mergeable_pathname = 
		  convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (mergeable_pathname) {
	      mergeable_pathname_with_home = Qunbound_in_protected_let;
	      default_pathname = Qunbound_in_protected_let;
	      merge_series = Qunbound_in_protected_let;
	      merged_pathname = Qunbound_in_protected_let;
	      less_case_sensitive_pathname = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  mergeable_pathname_with_home = 
			  maybe_supply_home_to_possible_unix_pathname(mergeable_pathname);
		  default_pathname = get_or_make_default_kb_pathname(0);
		  merge_series = 
			  gensym_list_2(mergeable_pathname_with_home,
			  default_pathname);
		  merged_pathname = merge_series_of_pathnames(merge_series);
		  temp = 
			  get_less_case_sensitive_gensym_pathname_if_any(merged_pathname);
		  if (temp);
		  else
		      temp = merged_pathname;
		  less_case_sensitive_pathname = temp;
		  SAVE_VALUES(gensym_probe_file(less_case_sensitive_pathname));
	      }
	      POP_UNWIND_PROTECT(0);
	      if (less_case_sensitive_pathname) {
		  if ( !EQ(less_case_sensitive_pathname,
			  Qunbound_in_protected_let))
		      reclaim_gensym_pathname(less_case_sensitive_pathname);
	      }
	      if (merge_series) {
		  if ( !EQ(merge_series,Qunbound_in_protected_let))
		      reclaim_gensym_list_1(merge_series);
	      }
	      if (default_pathname) {
		  if ( !EQ(default_pathname,Qunbound_in_protected_let))
		      reclaim_gensym_pathname(default_pathname);
	      }
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
      }
      POP_UNWIND_PROTECT(1);
      if (mergeable_pathname) {
	  if ( !EQ(mergeable_pathname,Qunbound_in_protected_let)) {
	      if (mergeable_pathname)
		  reclaim_gensym_pathname(mergeable_pathname);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_26;  /* "The filename ~s is too long ~
				    *                         to store in the file system.  Save KB as ~s?"
				    */

static Object string_constant_27;  /* "The filename ~s contains trailing spaces.  ~
				    *                    G2 will be unable to locate this file.  ~
				    *                    Save KB as ~s instead?"
				    */

/* MAYBE-MODIFY-CONFIRMATION-QUERY-AND-DEFAULT-PATHNAME */
Object maybe_modify_confirmation_query_and_default_pathname(default_pathname,
	    default_namestring_for_user,confirmation_query)
    Object default_pathname, default_namestring_for_user, confirmation_query;
{
    Object maximum_length_qm, file_type_qm, trimmed_file_type_p;
    Object trimmed_file_type, default_pathname_with_trimmed_type;
    volatile Object file_namestring_1;
    Object file_namestring_length;
    volatile Object file_namestring_for_user;
    Object file_base_namestring, file_base_namestring_length;
    volatile Object truncated_base_namestring;
    Object truncated_default_pathname, truncated_namestring_for_user, temp;
    Object new_confirmation_query;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(131,77);
    SAVE_STACK();
    maximum_length_qm = gensym_maximum_file_name_length(default_pathname);
    file_type_qm = ISVREF(default_pathname,(SI_Long)5L);
    trimmed_file_type_p = Nil;
    if (text_string_p(file_type_qm) && 
	    EQ(FIX(UBYTE_16_ISAREF_1(file_type_qm,
	    IFIX(FIXNUM_SUB1(lengthw(file_type_qm))))),FIX((SI_Long)32L))) {
	trimmed_file_type = text_string_right_trim(array_constant_8,
		file_type_qm);
	default_pathname_with_trimmed_type = 
		gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Nil,trimmed_file_type,Nil,default_pathname);
	reclaim_gensym_pathname(default_pathname);
	default_pathname = default_pathname_with_trimmed_type;
	trimmed_file_type_p = T;
    }
    if (maximum_length_qm) {
	file_namestring_1 = Qunbound_in_protected_let;
	file_namestring_length = Qunbound_in_protected_let;
	file_namestring_for_user = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    file_namestring_1 = gensym_file_namestring(1,default_pathname);
	    file_namestring_length = text_string_length(file_namestring_1);
	    file_namestring_for_user = copy_text_string(file_namestring_1);
	    if (FIXNUM_GT(file_namestring_length,maximum_length_qm)) {
		file_base_namestring = Qunbound_in_protected_let;
		file_base_namestring_length = Qunbound_in_protected_let;
		truncated_base_namestring = Qunbound_in_protected_let;
		truncated_default_pathname = Qunbound_in_protected_let;
		truncated_namestring_for_user = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    file_base_namestring = ISVREF(default_pathname,
			    (SI_Long)4L);
		    file_base_namestring_length = 
			    text_string_length(file_base_namestring);
		    truncated_base_namestring = 
			    text_string_substring(file_base_namestring,
			    FIX((SI_Long)0L),
			    FIXNUM_MINUS(maximum_length_qm,
			    FIXNUM_MINUS(file_namestring_length,
			    file_base_namestring_length)));
		    truncated_default_pathname = 
			    gensym_make_pathname_with_copied_components(Nil,
			    Nil,Nil,truncated_base_namestring,Nil,Nil,
			    default_pathname);
		    truncated_namestring_for_user = 
			    gensym_namestring_as_text_string(1,
			    truncated_default_pathname);
		    reclaim_gensym_pathname(default_pathname);
		    reclaim_text_string(default_namestring_for_user);
		    reclaim_text_string(confirmation_query);
		    temp = tformat_text_string(3,string_constant_26,
			    file_namestring_for_user,
			    truncated_namestring_for_user);
		    SAVE_VALUES(VALUES_3(temp,
			    truncated_namestring_for_user,
			    truncated_default_pathname));
		}
		POP_UNWIND_PROTECT(0);
		if (truncated_base_namestring) {
		    if ( !EQ(truncated_base_namestring,
			    Qunbound_in_protected_let))
			reclaim_text_string(truncated_base_namestring);
		}
		CONTINUE_UNWINDING(0);
	    }
	    else
		SAVE_VALUES(VALUES_3(confirmation_query,
			default_namestring_for_user,default_pathname));
	}
	POP_UNWIND_PROTECT(1);
	if (file_namestring_for_user) {
	    if ( !EQ(file_namestring_for_user,Qunbound_in_protected_let))
		reclaim_text_string(file_namestring_for_user);
	}
	if (file_namestring_1) {
	    if ( !EQ(file_namestring_1,Qunbound_in_protected_let))
		reclaim_text_string(file_namestring_1);
	}
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else if (trimmed_file_type_p) {
	file_namestring_for_user = gensym_namestring(1,default_pathname);
	new_confirmation_query = tformat_text_string(3,string_constant_27,
		default_namestring_for_user,file_namestring_for_user);
	reclaim_text_string(default_namestring_for_user);
	reclaim_text_string(confirmation_query);
	result = VALUES_3(new_confirmation_query,file_namestring_for_user,
		default_pathname);
	RESTORE_STACK();
	return result;
    }
    else {
	result = VALUES_3(confirmation_query,default_namestring_for_user,
		default_pathname);
	RESTORE_STACK();
	return result;
    }
}

static Object Qconnect_to_foreign_image;  /* connect-to-foreign-image */

static Object Qdisconnect_from_foreign_image;  /* disconnect-from-foreign-image */

static Object Qload_attribute_file;  /* load-attribute-file */

static Object Qwrite_g2_stats;     /* write-g2-stats */

/* SYMBOLIC-FILE-TYPE-FOR-FILE-COMMAND? */
Object symbolic_file_type_for_file_command_qm(command_symbol)
    Object command_symbol;
{
    x_note_fn_call(131,78);
    if (EQ(command_symbol,Qconnect_to_foreign_image) || EQ(command_symbol,
	    Qdisconnect_from_foreign_image))
	return VALUES_1(Qforeign_image);
    else if (EQ(command_symbol,Qload_attribute_file))
	return VALUES_1(Qattribute);
    else if (EQ(command_symbol,Qwrite_g2_stats))
	return VALUES_1(Qstatistics);
    else
	return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object Qsave_only_changed_modules;  /* save-only-changed-modules */

static Object Qscc_commit;         /* scc-commit */

static Object Qresolve_conflicts_automatically;  /* resolve-conflicts-automatically */

static Object Qdefault;            /* default */

static Object Qreformat_as_appropriate;  /* reformat-as-appropriate */

static Object Qinstall_system_tables;  /* install-system-tables */

static Object list_constant_12;    /* # */

/* EXECUTE-FILE-COMMAND */
Object execute_file_command(file_command)
    Object file_command;
{
    Object temp, command_translation, command_symbol, scc_command_p;
    Object options_plist, module_to_save_qm, include_required_modules_qm;
    Object only_changed_modules_qm, thing;
    Object log_message_for_commit_after_saving_qm, emit_c_code_qm;
    Object default_file_name_qm, file_or_directory_name_qm;
    Object per_directory_menu_if_loading_qm;
    Object resolve_conflicts_automatically_qm;
    Object reformat_as_appropriate_if_load_or_merge_case_qm;
    Object install_system_tables_if_merge_case_qm;
    Object what_to_do_after_loading_kb_qm, use_clear_text_qm;
    Object update_before_loading_qm, symbolic_file_type_qm;
    Object command_default_namestring_qm, command_default_pathname_qm;
    Object current_default_pathname_qm, default_pathname_qm;
    Object default_pathname_is_reclaimable_p, load_case_qm;
    Object connection_spec_slot_value, transport_type, host_name_slot_value;
    Object host_name, port_number_or_name_slot_value, port_number_or_name;
    Object external_foreign_image_connection_spec_qm;

    x_note_fn_call(131,79);
    temp = ISVREF(file_command,(SI_Long)16L);
    command_translation = copy_for_slot_value(FIRST(temp));
    temp = FIRST(command_translation);
    if (CONSP(temp)) {
	temp = FIRST(command_translation);
	command_symbol = CAR(temp);
    }
    else
	command_symbol = FIRST(command_translation);
    scc_command_p = memq_function(command_symbol,list_constant_10);
    if ( !TRUEP(scc_command_p)) {
	temp = THIRD(command_translation);
	options_plist = CONSP(temp) ? THIRD(command_translation) : Nil;
    }
    else
	options_plist = Nil;
    if (memq_function(command_symbol,list_constant_11)) {
	temp = FIRST(command_translation);
	module_to_save_qm = SECOND(temp);
    }
    else
	module_to_save_qm = Nil;
    include_required_modules_qm = module_to_save_qm ? getf(options_plist,
	    Qincluding_all_required_modules,_) : Nil;
    only_changed_modules_qm = module_to_save_qm ? getf(options_plist,
	    Qsave_only_changed_modules,_) : Nil;
    thing = scc_command_p ? (EQ(command_symbol,Qscc_commit) ? 
	    THIRD(command_translation) : Qnil) : getf(options_plist,
	    Qcommit_after_saving,_);
    log_message_for_commit_after_saving_qm = 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    copy_text_string(thing) : thing;
    emit_c_code_qm = getf(options_plist,Qemitting_c_code,_) ? T : Qnil;
    temp = SECOND(command_translation);
    if (CONSP(temp)) {
	temp = SECOND(command_translation);
	default_file_name_qm = FIRST(temp);
    }
    else
	default_file_name_qm = Nil;
    temp = SECOND(command_translation);
    if (CONSP(temp)) {
	temp = SECOND(command_translation);
	if ( !EQ(SECOND(temp),Qper_directory_menu)) {
	    temp = SECOND(command_translation);
	    file_or_directory_name_qm = SECOND(temp);
	}
	else
	    file_or_directory_name_qm = Nil;
    }
    else
	file_or_directory_name_qm =  !EQ(SECOND(command_translation),
		Qper_directory_menu) ? SECOND(command_translation) : Nil;
    temp = SECOND(command_translation);
    if (CONSP(temp)) {
	temp = SECOND(command_translation);
	per_directory_menu_if_loading_qm = EQ(SECOND(temp),
		Qper_directory_menu) ? T : Nil;
    }
    else
	per_directory_menu_if_loading_qm = EQ(SECOND(command_translation),
		Qper_directory_menu) ? T : Nil;
    resolve_conflicts_automatically_qm = getf(options_plist,
	    Qresolve_conflicts_automatically,Qdefault);
    reformat_as_appropriate_if_load_or_merge_case_qm = getf(options_plist,
	    Qreformat_as_appropriate,_);
    install_system_tables_if_merge_case_qm = getf(options_plist,
	    Qinstall_system_tables,_);
    what_to_do_after_loading_kb_qm = getf(options_plist,
	    Qwhat_to_do_after_loading_kb,_);
    use_clear_text_qm = getf(options_plist,Qusing_clear_text,_);
    update_before_loading_qm = getf(options_plist,Qupdate_before_loading,
	    Qdefault);
    symbolic_file_type_qm = 
	    symbolic_file_type_for_file_command_qm(command_symbol);
    command_default_namestring_qm = default_file_name_qm ? 
	    (SYMBOLP(default_file_name_qm) ? gensym_namestring(1,
	    default_file_name_qm) : 
	    copy_text_string(default_file_name_qm)) : Nil;
    if (command_default_namestring_qm) {
	temp = gensym_pathname(command_default_namestring_qm);
	reclaim_text_string(command_default_namestring_qm);
	command_default_pathname_qm = temp;
    }
    else
	command_default_pathname_qm = Nil;
    current_default_pathname_qm = make_default_pathname(symbolic_file_type_qm);
    default_pathname_qm = command_default_pathname_qm;
    if (default_pathname_qm);
    else
	default_pathname_qm = current_default_pathname_qm;
    if (default_pathname_qm);
    else
	default_pathname_qm = 
		make_first_time_default_pathname(symbolic_file_type_qm);
    default_pathname_is_reclaimable_p = command_default_pathname_qm;
    if (default_pathname_is_reclaimable_p);
    else
	default_pathname_is_reclaimable_p =  
		!TRUEP(current_default_pathname_qm) ? T : Nil;
    if (EQ(command_symbol,Qload))
	load_case_qm = empty_kb_p() ? T : Qreplace;
    else if (EQ(command_symbol,Qconnect_to_foreign_image))
	load_case_qm = Qconnect_to_foreign_image;
    else if (EQ(command_symbol,Qdisconnect_from_foreign_image))
	load_case_qm = Qdisconnect_from_foreign_image;
    else
	load_case_qm = Nil;
    if (memq_function(command_symbol,list_constant_12)) {
	connection_spec_slot_value = SECOND(command_translation);
	transport_type = FIRST(connection_spec_slot_value);
	host_name_slot_value = SECOND(connection_spec_slot_value);
	host_name = text_string_p(host_name_slot_value) ? 
		copy_text_string(host_name_slot_value) : host_name_slot_value;
	port_number_or_name_slot_value = THIRD(connection_spec_slot_value);
	port_number_or_name = 
		text_string_p(port_number_or_name_slot_value) ? 
		copy_text_string(port_number_or_name_slot_value) : 
		port_number_or_name_slot_value;
	external_foreign_image_connection_spec_qm = 
		icp_list_3(transport_type,host_name,port_number_or_name);
    }
    else
	external_foreign_image_connection_spec_qm = Nil;
    finish_executing_file_command(command_symbol,module_to_save_qm,
	    include_required_modules_qm,emit_c_code_qm,
	    file_or_directory_name_qm,use_clear_text_qm,
	    log_message_for_commit_after_saving_qm,
	    per_directory_menu_if_loading_qm,
	    resolve_conflicts_automatically_qm,
	    reformat_as_appropriate_if_load_or_merge_case_qm,
	    install_system_tables_if_merge_case_qm,
	    what_to_do_after_loading_kb_qm,symbolic_file_type_qm,
	    current_default_pathname_qm,default_pathname_qm,
	    default_pathname_is_reclaimable_p,load_case_qm,
	    external_foreign_image_connection_spec_qm,
	    update_before_loading_qm,only_changed_modules_qm);
    return reclaim_slot_value(command_translation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Autostart_after_doing_init_file_qm, Qautostart_after_doing_init_file_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Autostart_reason_in_init_file_qm, Qautostart_reason_in_init_file_qm);

static Object Qnever_autostart;    /* never-autostart */

static Object Qautostart;          /* autostart */

static Object Qdo_not_autostart;   /* do-not-autostart */

static Object Qmerge_in_init_file;  /* merge-in-init-file */

static Object Qload_in_init_file;  /* load-in-init-file */

static Object list_constant_13;    /* # */

static Object string_constant_28;  /* "~S is not a valid file name!" */

static Object list_constant_14;    /* # */

static Object QG2_INTERNAL_TOP_LEVEL;  /* |g2-internal-top-level| */

static Object string_constant_29;  /* "The module ~a does not exist and so cannot be saved.  ~
				    *                               NOTHING WAS SAVED!!"
				    */

static Object list_constant_15;    /* # */

static Object string_constant_30;  /* "Save KB as ~s?" */

static Object Qsave_kb;            /* save-kb */

static Object Qreclaim_gensym_pathname;  /* reclaim-gensym-pathname */

static Object Qdisconnect_from_all_foreign_images;  /* disconnect-from-all-foreign-images */

static Object Qconnect_to_external_foreign_image;  /* connect-to-external-foreign-image */

static Object Qdisconnect_from_external_foreign_image;  /* disconnect-from-external-foreign-image */

static Object Qscc_update;         /* scc-update */

static Object Qscc_edit;           /* scc-edit */

static Object Qscc_unedit;         /* scc-unedit */

static Object Qscc_revert;         /* scc-revert */

/* FINISH-EXECUTING-FILE-COMMAND */
Object finish_executing_file_command(command_symbol,module_to_save_qm,
	    include_required_modules_qm,emit_c_code_qm,
	    file_or_directory_name_qm,use_clear_text_qm,
	    log_message_for_commit_after_saving_qm,
	    per_directory_menu_if_loading_qm,
	    resolve_conflicts_automatically_qm,
	    reformat_as_appropriate_if_load_or_merge_case_qm,
	    install_system_tables_if_merge_case_qm,
	    what_to_do_after_loading_kb_qm,symbolic_file_type_qm,
	    current_default_pathname_qm,default_pathname_qm,
	    default_pathname_is_reclaimable_p,load_case_qm,
	    external_foreign_image_connection_spec_qm,
	    update_before_loading_qm,only_changed_modules_qm)
    Object command_symbol, module_to_save_qm, include_required_modules_qm;
    Object emit_c_code_qm, file_or_directory_name_qm, use_clear_text_qm;
    Object log_message_for_commit_after_saving_qm;
    Object per_directory_menu_if_loading_qm;
    Object resolve_conflicts_automatically_qm;
    Object reformat_as_appropriate_if_load_or_merge_case_qm;
    Object install_system_tables_if_merge_case_qm;
    Object what_to_do_after_loading_kb_qm, symbolic_file_type_qm;
    Object current_default_pathname_qm, default_pathname_qm;
    Object default_pathname_is_reclaimable_p, load_case_qm;
    Object external_foreign_image_connection_spec_qm, update_before_loading_qm;
    Object only_changed_modules_qm;
{
    Object temp, temp_1, name_from_command, mergeable_namestring;
    Object new_default_pathname_1, old_pathname, old_pathname_type;
    Object new_default_pathname, default_namestring_for_user, same_pathname_qm;
    Object confirmation_query, temp_2, gensymed_symbol, gensymed_symbol_1;
    char symbolic_filename_p;
    Object result;

    x_note_fn_call(131,80);
    if (Doing_g2_init_file_p) {
	if ( !EQ(Autostart_after_doing_init_file_qm,Qnever_autostart)) {
	    if (EQ(what_to_do_after_loading_kb_qm,Qstart_afterwards))
		Autostart_after_doing_init_file_qm = Qautostart;
	    else if (EQ(what_to_do_after_loading_kb_qm,
		    Qnever_start_afterwards))
		Autostart_after_doing_init_file_qm = Qdo_not_autostart;
	    if (EQ(what_to_do_after_loading_kb_qm,Qstart_afterwards) || 
		    EQ(what_to_do_after_loading_kb_qm,Qnever_start_afterwards))
		Autostart_reason_in_init_file_qm = EQ(command_symbol,
			Qmerge) ? Qmerge_in_init_file : Qload_in_init_file;
	}
    }
    if (per_directory_menu_if_loading_qm) {
	temp = default_pathname_qm;
	temp_1 = EQ(what_to_do_after_loading_kb_qm,Qwarmboot_afterwards) ? 
		T : Nil;
	if (temp_1);
	else
	    temp_1 = EQ(what_to_do_after_loading_kb_qm,
		    Qwarmboot_afterwards_with_catch_up) ? T : Nil;
	post_directory_menu(temp,load_case_qm,
		reformat_as_appropriate_if_load_or_merge_case_qm,
		symbolic_file_type_qm,temp_1,
		resolve_conflicts_automatically_qm,
		what_to_do_after_loading_kb_qm,EQ(command_symbol,
		Qdisconnect_from_foreign_image) ? T : Nil,
		install_system_tables_if_merge_case_qm,
		update_before_loading_qm);
	if (default_pathname_is_reclaimable_p)
	    return reclaim_gensym_pathname(default_pathname_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	name_from_command = file_or_directory_name_qm;
	symbolic_filename_p = SYMBOLP(name_from_command);
	mergeable_namestring = copy_text_string(symbolic_filename_p ? 
		symbol_name_text_string(name_from_command) : 
		name_from_command);
	temp = symbolic_filename_p ? 
		nstring_downcasew(mergeable_namestring) : mergeable_namestring;
	temp = 
		maybe_supply_home_to_possible_unix_pathname(gensym_merge_pathnames_function(temp,
		default_pathname_qm,Nil));
	reclaim_text_string(mergeable_namestring);
	if (default_pathname_is_reclaimable_p)
	    reclaim_gensym_pathname(default_pathname_qm);
	new_default_pathname_1 = temp;
	old_pathname = new_default_pathname_1;
	old_pathname_type = ISVREF(old_pathname,(SI_Long)5L);
	if (memq_function(command_symbol,list_constant_13) && 
		text_string_p(old_pathname_type) && 
		string_equalw(old_pathname_type,array_constant)) {
	    temp = gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		    Nil,array_constant_4,Nil,old_pathname);
	    reclaim_gensym_pathname(old_pathname);
	    new_default_pathname = temp;
	}
	else if (use_clear_text_qm && text_string_p(old_pathname_type) && 
		string_equalw(old_pathname_type,array_constant_4)) {
	    temp = gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		    Nil,array_constant,Nil,old_pathname);
	    reclaim_gensym_pathname(old_pathname);
	    new_default_pathname = temp;
	}
	else
	    new_default_pathname = new_default_pathname_1;
	default_namestring_for_user = gensym_namestring_as_text_string(1,
		new_default_pathname);
	default_pathname_qm = new_default_pathname;
	if ( !TRUEP(default_pathname_qm))
	    notify_user(2,string_constant_28,file_or_directory_name_qm);
	else if (EQ(command_symbol,Qload) || EQ(command_symbol,Qmerge)) {
	    temp = default_pathname_qm;
	    temp_1 = EQ(what_to_do_after_loading_kb_qm,
		    Qwarmboot_afterwards) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(what_to_do_after_loading_kb_qm,
			Qwarmboot_afterwards_with_catch_up) ? T : Nil;
	    load_or_merge_kb_if_ok(8,temp,load_case_qm,
		    reformat_as_appropriate_if_load_or_merge_case_qm,
		    temp_1,resolve_conflicts_automatically_qm,
		    install_system_tables_if_merge_case_qm,
		    what_to_do_after_loading_kb_qm,update_before_loading_qm);
	}
	else if (member_eql(command_symbol,list_constant_14)) {
	    same_pathname_qm = 
		    gensym_pathnames_equal_enough_p(default_pathname_qm,
		    current_default_pathname_qm);
	    if (same_pathname_qm || 
		    Attempting_save_via_system_procedure_qm || 
		    Do_g2_init_file_qm || memq_function(command_symbol,
		    list_constant_11)) {
		if (memq_function(command_symbol,list_constant_11)) {
		    if (EQ(module_to_save_qm,QG2_INTERNAL_TOP_LEVEL))
			module_to_save_qm = ISVREF(Module_information,
				(SI_Long)23L);
		    if ( !TRUEP(module_exists_p(module_to_save_qm)))
			notify_user(2,string_constant_29,module_to_save_qm);
		    else {
			if (use_clear_text_qm) {
			    old_pathname = default_pathname_qm;
			    default_pathname_qm = 
				    gensym_make_pathname_with_copied_components(Nil,
				    Nil,Nil,Nil,array_constant,Nil,
				    default_pathname_qm);
			    reclaim_gensym_pathname(old_pathname);
			}
			save_module_of_kb(7,default_pathname_qm,
				module_to_save_qm,
				include_required_modules_qm,
				use_clear_text_qm,emit_c_code_qm,
				log_message_for_commit_after_saving_qm,
				only_changed_modules_qm);
			reclaim_gensym_pathname(default_pathname_qm);
		    }
		}
		else if (memq_function(command_symbol,list_constant_15)) {
		    save_kb(4,default_pathname_qm,command_symbol,
			    emit_c_code_qm,
			    log_message_for_commit_after_saving_qm);
		    reclaim_gensym_pathname(default_pathname_qm);
		}
	    }
	    else {
		confirmation_query = tformat_text_string(2,
			string_constant_30,default_namestring_for_user);
		result = maybe_modify_confirmation_query_and_default_pathname(default_pathname_qm,
			default_namestring_for_user,confirmation_query);
		MVS_3(result,confirmation_query,
			default_namestring_for_user,default_pathname_qm);
		temp = confirmation_query;
		temp_1 = slot_value_list_3(default_pathname_qm,
			command_symbol,emit_c_code_qm);
		temp_2 = slot_value_cons_1(default_pathname_qm,Nil);
		gensymed_symbol = get_position_of_mouse();
		result = get_position_of_mouse();
		gensymed_symbol_1 = NTH_VALUE((SI_Long)1L, result);
		enter_dialog(9,temp,Nil,Nil,Qsave_kb,temp_1,
			Qreclaim_gensym_pathname,temp_2,gensymed_symbol,
			gensymed_symbol_1);
	    }
	}
	else if (EQ(command_symbol,Qload_attribute_file))
	    load_custom_software_file_if_ok(default_pathname_qm,
		    symbolic_file_type_qm);
	else if (EQ(command_symbol,Qconnect_to_foreign_image))
	    connect_to_foreign_image(default_pathname_qm);
	else if (EQ(command_symbol,Qdisconnect_from_foreign_image))
	    disconnect_from_foreign_image(default_pathname_qm);
	else if (EQ(command_symbol,Qdisconnect_from_all_foreign_images))
	    disconnect_from_all_foreign_images();
	else if (EQ(command_symbol,Qconnect_to_external_foreign_image))
	    connect_to_external_foreign_image(external_foreign_image_connection_spec_qm);
	else if (EQ(command_symbol,Qdisconnect_from_external_foreign_image))
	    disconnect_from_external_foreign_image(external_foreign_image_connection_spec_qm);
	else if (EQ(command_symbol,Qscc_update) || EQ(command_symbol,
		Qscc_edit) || EQ(command_symbol,Qscc_unedit) || 
		EQ(command_symbol,Qscc_revert))
	    do_scc_command(2,command_symbol,default_pathname_qm);
	else if (EQ(command_symbol,Qscc_commit))
	    do_scc_command(3,command_symbol,default_pathname_qm,
		    log_message_for_commit_after_saving_qm);
	else if (EQ(command_symbol,Qwrite_g2_stats))
	    write_g2_stats(default_pathname_qm);
	return reclaim_text_string(default_namestring_for_user);
    }
}

/* GET-LESS-CASE-SENSITIVE-GENSYM-PATHNAME-IF-ANY */
Object get_less_case_sensitive_gensym_pathname_if_any(gensym_pathname_1)
    Object gensym_pathname_1;
{
    Object truename_qm, resulting_new_pathname_qm, directory_pathname, temp;
    Object directory_qm, p, ab_loop_list_;

    x_note_fn_call(131,81);
    if (EQ(ISVREF(gensym_pathname_1,(SI_Long)8L),Qunix)) {
	truename_qm = gensym_probe_file(gensym_pathname_1);
	resulting_new_pathname_qm = Nil;
	if (truename_qm)
	    reclaim_gensym_pathname(truename_qm);
	else {
	    directory_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,Kwild,Kwild,Knewest,gensym_pathname_1);
	    temp = gensym_directory(1,directory_pathname);
	    reclaim_gensym_pathname(directory_pathname);
	    directory_qm = temp;
	    if (directory_qm) {
		resulting_new_pathname_qm = 
			get_less_case_sensitive_gensym_pathname_given_directory(gensym_pathname_1,
			directory_qm);
		p = Nil;
		ab_loop_list_ = directory_qm;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		p = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		reclaim_gensym_pathname(p);
		goto next_loop;
	      end_loop:;
		reclaim_path_list_1(directory_qm);
	    }
	}
	return VALUES_1(resulting_new_pathname_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_stream_error_string;  /* g2-stream-error-string */

static Object string_constant_31;  /* "G2 could not find the file ~s:  ~a." */

static Object string_constant_32;  /* "G2 could not find the file ~s." */

/* ABANDON-LOAD-OR-MERGE-KB-IF-OK */
Object abandon_load_or_merge_kb_if_ok(gensym_pathname_1,
	    namestring_for_pathname)
    Object gensym_pathname_1, namestring_for_pathname;
{
    Object old_gensym_pathname_name, old_gensym_pathname_type;
    Object old_gensym_pathname_version;
    volatile Object directory_pathname;
    volatile Object directory_namestring_1;
    Object temp, valid_directory_pathname_p, new_value;
    volatile Object error_string_for_user;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(131,82);
    SAVE_STACK();
    old_gensym_pathname_name = ISVREF(gensym_pathname_1,(SI_Long)4L);
    old_gensym_pathname_type = ISVREF(gensym_pathname_1,(SI_Long)5L);
    old_gensym_pathname_version = ISVREF(gensym_pathname_1,(SI_Long)6L);
    if (PUSH_UNWIND_PROTECT(1)) {
	SVREF(gensym_pathname_1,FIX((SI_Long)4L)) = Nil;
	SVREF(gensym_pathname_1,FIX((SI_Long)5L)) = Nil;
	SVREF(gensym_pathname_1,FIX((SI_Long)6L)) = Nil;
	directory_pathname = Qunbound_in_protected_let;
	directory_namestring_1 = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = gensym_directory_as_file(gensym_pathname_1);
	    if (temp);
	    else
		temp = make_empty_gensym_pathname();
	    directory_pathname = temp;
	    directory_namestring_1 = gensym_namestring(1,directory_pathname);
	    SAVE_VALUES(VALUES_1(g2_stream_directory_p(directory_namestring_1) 
		    && gensym_pathname_1 ? T : Qnil));
	}
	POP_UNWIND_PROTECT(0);
	if (directory_namestring_1) {
	    if ( !EQ(directory_namestring_1,Qunbound_in_protected_let))
		reclaim_text_string(directory_namestring_1);
	}
	if (directory_pathname) {
	    if ( !EQ(directory_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(directory_pathname);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	SAVE_VALUES(VALUES_1(result));
    }
    POP_UNWIND_PROTECT(1);
    SVREF(gensym_pathname_1,FIX((SI_Long)4L)) = old_gensym_pathname_name;
    SVREF(gensym_pathname_1,FIX((SI_Long)5L)) = old_gensym_pathname_type;
    SVREF(gensym_pathname_1,FIX((SI_Long)6L)) = old_gensym_pathname_version;
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    valid_directory_pathname_p = result;
    if (Current_kb_pathname_qm && valid_directory_pathname_p) {
	new_value = 
		gensym_merge_pathnames_function(ISVREF(Current_kb_pathname_qm,
		(SI_Long)4L),gensym_pathname_1,Nil);
	reclaim_pathname_or_string(Current_kb_pathname_qm);
	if (text_string_p(new_value)) {
	    temp = gensym_pathname(new_value);
	    reclaim_text_string(new_value);
	    Current_kb_pathname_qm = temp;
	}
	else
	    Current_kb_pathname_qm = new_value;
	add_recent_loaded_kb(Current_kb_pathname_qm);
	reclaim_gensym_pathname(gensym_pathname_1);
    }
    else if (valid_directory_pathname_p) {
	reclaim_pathname_or_string(Current_kb_pathname_qm);
	if (text_string_p(gensym_pathname_1)) {
	    temp = gensym_pathname(gensym_pathname_1);
	    reclaim_text_string(gensym_pathname_1);
	    Current_kb_pathname_qm = temp;
	}
	else
	    Current_kb_pathname_qm = gensym_pathname_1;
	add_recent_loaded_kb(Current_kb_pathname_qm);
    }
    else
	reclaim_gensym_pathname(gensym_pathname_1);
    if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
	    File_operation_succeeded_code)) {
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
		Cached_unknown_error_string_with_code_qm = 
			tformat_text_string(2,
			Unknown_error_during_file_op_with_code_message,
			Internal_status_of_most_recent_file_operation);
		temp = Cached_unknown_error_string_with_code_qm;
	    }
	    error_string_for_user = import_text_string(2,temp,
		    Qg2_stream_error_string);
	    SAVE_VALUES(notify_user(3,string_constant_31,
		    namestring_for_pathname,error_string_for_user));
	}
	POP_UNWIND_PROTECT(0);
	if (error_string_for_user) {
	    if ( !EQ(error_string_for_user,Qunbound_in_protected_let))
		reclaim_text_string(error_string_for_user);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	result = notify_user(2,string_constant_32,namestring_for_pathname);
	RESTORE_STACK();
	return result;
    }
}

static Object Qload_or_merge_kb_if_ok;  /* load-or-merge-kb-if-ok */

/* LOAD-OR-MERGE-KB-IF-OK */
Object load_or_merge_kb_if_ok varargs_1(int, n)
{
    Object gensym_pathname_1, load_case_qm, bring_formats_up_to_date_qm;
    Object warmboot_case_qm;
    Object auto_merge_case_qm, install_system_tables_if_merge_case_qm;
    Object what_to_do_after_loading_kb_qm, update_before_loading_qm, tag_temp;
    Object truename_qm;
    volatile Object namestring_for_pathname;
    Object temp;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(131,83);
    INIT_ARGS_nonrelocating();
    gensym_pathname_1 = REQUIRED_ARG_nonrelocating();
    load_case_qm = REQUIRED_ARG_nonrelocating();
    bring_formats_up_to_date_qm = REQUIRED_ARG_nonrelocating();
    warmboot_case_qm = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    auto_merge_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    install_system_tables_if_merge_case_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    what_to_do_after_loading_kb_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    update_before_loading_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qload_or_merge_kb_if_ok);
    if (PUSH_CATCH(tag_temp,1)) {
	truename_qm = Qunbound_in_protected_let;
	namestring_for_pathname = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = 
		    get_less_case_sensitive_gensym_pathname_if_any(gensym_pathname_1);
	    if (temp);
	    else
		temp = gensym_probe_file(gensym_pathname_1);
	    truename_qm = temp;
	    temp = truename_qm;
	    if (temp);
	    else
		temp = gensym_pathname_1;
	    namestring_for_pathname = gensym_namestring(1,temp);
	    if ( !TRUEP(truename_qm)) {
		temp = copy_gensym_pathname(gensym_pathname_1);
		abandon_load_or_merge_kb_if_ok(temp,namestring_for_pathname);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    reclaim_gensym_pathname(gensym_pathname_1);
	    inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
		    = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		    0);
	      temp = truename_qm;
	      temp_1 = load_case_qm;
	      if (temp_1);
	      else
		  temp_1 = install_system_tables_if_merge_case_qm;
	      temp = read_kb_or_group_thereof(temp,load_case_qm,temp_1,
		      bring_formats_up_to_date_qm,auto_merge_case_qm,
		      what_to_do_after_loading_kb_qm,
		      update_before_loading_qm,
		      get_current_workstation_or_ui_client_interface_if_any());
	      reclaim_gensym_pathname(truename_qm);
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp));
	    if ( 
		    !TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm))
		update_module_related_frame_notes_for_all_workspaces(0);
	}
	POP_UNWIND_PROTECT(0);
	if (namestring_for_pathname) {
	    if ( !EQ(namestring_for_pathname,Qunbound_in_protected_let))
		reclaim_text_string(namestring_for_pathname);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

/* GENSYM-PATHNAME-LESSP */
Object gensym_pathname_lessp(gensym_pathname1,gensym_pathname2)
    Object gensym_pathname1, gensym_pathname2;
{
    x_note_fn_call(131,84);
    return string_lesspw(ISVREF(gensym_pathname1,(SI_Long)4L),
	    ISVREF(gensym_pathname2,(SI_Long)4L));
}

static Object Qgensym_pathname_lessp;  /* gensym-pathname-lessp */

static Object array_constant_13;   /* # */

/* GET-DIRECTORY-FOR-KB-FILE-TYPE */
Object get_directory_for_kb_file_type varargs_1(int, n)
{
    Object default_pathname_qm, directory_pathname;
    Object include_subdirectories_qm;
    Object match_regular_expression_for_g2_stream_directory_hook;
    Object name_pathname, temp, wild_directory_pathname;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(131,85);
    INIT_ARGS_nonrelocating();
    default_pathname_qm = REQUIRED_ARG_nonrelocating();
    directory_pathname = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    include_subdirectories_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (default_pathname_qm && gensym_wild_pathname_p(default_pathname_qm))
	return sort_list(gensym_directory(2,default_pathname_qm,Nil),
		SYMBOL_FUNCTION(Qgensym_pathname_lessp),Nil);
    else {
	match_regular_expression_for_g2_stream_directory_hook = 
		Need_to_check_plist_p ? Qnamestring_is_xml_file_p : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Match_regular_expression_for_g2_stream_directory_hook,Qmatch_regular_expression_for_g2_stream_directory_hook,match_regular_expression_for_g2_stream_directory_hook,
		0);
	  name_pathname = gensym_make_pathname_with_copied_components(Nil,
		  Nil,Nil,Kwild,array_constant_13,Knewest,default_pathname_qm);
	  temp = gensym_merge_pathnames_function(name_pathname,
		  directory_pathname,Nil);
	  reclaim_gensym_pathname(name_pathname);
	  wild_directory_pathname = temp;
	  temp = gensym_directory(2,wild_directory_pathname,Nil);
	  temp = sort_list(nconc2(temp,include_subdirectories_qm ? 
		  gensym_subdirectories(2,wild_directory_pathname,Nil) : 
		  Nil),SYMBOL_FUNCTION(Qgensym_pathname_lessp),Nil);
	  reclaim_gensym_pathname(wild_directory_pathname);
	  result = VALUES_1(temp);
	POP_SPECIAL();
	return result;
    }
}

/* GET-DIRECTORY-FOR-NON-KB-FILE-TYPE */
Object get_directory_for_non_kb_file_type(default_pathname_qm,
	    symbolic_file_type_qm,load_case_qm,directory_pathname)
    Object default_pathname_qm, symbolic_file_type_qm, load_case_qm;
    Object directory_pathname;
{
    Object type_file_name_pathname, temp, pathname_with_type;
    Object unfiltered_directory, filtered_directory, directory_item;
    Object ab_loop_list_;

    x_note_fn_call(131,86);
    if (gensym_wild_pathname_p(default_pathname_qm))
	type_file_name_pathname = copy_gensym_pathname(default_pathname_qm);
    else {
	temp = ISVREF(default_pathname_qm,(SI_Long)5L);
	if (temp);
	else
	    temp = make_default_file_type(symbolic_file_type_qm);
	type_file_name_pathname = 
		gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Kwild,temp,Nil,default_pathname_qm);
    }
    temp = gensym_merge_pathnames_function(type_file_name_pathname,
	    directory_pathname,Nil);
    reclaim_gensym_pathname(type_file_name_pathname);
    pathname_with_type = temp;
    if (EQ(symbolic_file_type_qm,Qforeign_image)) {
	SVREF(pathname_with_type,FIX((SI_Long)6L)) = Knewest;
	temp = gensym_directory(2,pathname_with_type,Nil);
	reclaim_gensym_pathname(pathname_with_type);
	unfiltered_directory = sort_list(temp,Qgensym_pathname_lessp,Nil);
	filtered_directory = Nil;
	directory_item = Nil;
	ab_loop_list_ = unfiltered_directory;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	directory_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(load_case_qm,Qconnect_to_foreign_image)) {
	    if (pathname_of_a_connected_foreign_image_p(directory_item))
		reclaim_gensym_pathname(directory_item);
	    else
		filtered_directory = path_cons_1(directory_item,
			filtered_directory);
	}
	else if (EQ(load_case_qm,Qdisconnect_from_foreign_image)) {
	    if (pathname_of_a_connected_foreign_image_p(directory_item))
		filtered_directory = path_cons_1(directory_item,
			filtered_directory);
	    else
		reclaim_gensym_pathname(directory_item);
	}
	goto next_loop;
      end_loop:
	reclaim_path_list_1(unfiltered_directory);
	return nreverse(filtered_directory);
	return VALUES_1(Qnil);
    }
    else {
	temp = gensym_directory(2,pathname_with_type,Nil);
	reclaim_gensym_pathname(pathname_with_type);
	unfiltered_directory = sort_list(temp,Qgensym_pathname_lessp,Nil);
	return VALUES_1(unfiltered_directory);
    }
}

static Object Qgensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object string_constant_33;  /* "foreign image" */

static Object string_constant_34;  /* "KB and KL" */

static Object string_constant_35;  /* "~a Files on \"~a\"" */

static Object Qpathnames_in_directory;  /* pathnames-in-directory */

static Object Qforeign_images;     /* foreign-images */

static Object string_constant_36;  /* "Looking for ~a files in ~s" */

static Object string_constant_37;  /* "There are no ~a files in ~s" */

static Object string_constant_38;  /* "KB or KL" */

static Object Qhandle_choice_for_directory_menu;  /* handle-choice-for-directory-menu */

static Object Qtformat_text_string;  /* tformat-text-string */

/* POST-DIRECTORY-MENU */
Object post_directory_menu(default_pathname_qm,load_case_qm,
	    bring_formats_up_to_date_qm,symbolic_file_type_qm,
	    warmboot_case_qm,auto_merge_case_qm,
	    what_to_do_after_loading_kb_qm,
	    disconnect_from_external_foreign_image_p,
	    install_system_tables_if_merge_case_qm,update_before_loading_qm)
    Object default_pathname_qm, load_case_qm, bring_formats_up_to_date_qm;
    Object symbolic_file_type_qm, warmboot_case_qm, auto_merge_case_qm;
    Object what_to_do_after_loading_kb_qm;
    Object disconnect_from_external_foreign_image_p;
    Object install_system_tables_if_merge_case_qm, update_before_loading_qm;
{
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p;
    volatile Object directory_pathname;
    volatile Object menu_was_posted_qm;
    volatile Object directory_namestring_1;
    Object directory_namestring_for_notify_user, file_type_for_notify_user;
    volatile Object title;
    volatile Object parameters;
    Object menu_name, menu_qm, temp, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, choice_function_arguments, result_from_body;
    Object control_string, error_args, error_arg, ab_loop_list_, report_string;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(131,87);
    SAVE_STACK();
    inside_handling_gensym_file_errors_scope_p = T;
    gensym_file_error_occurred_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
	      0);
	if (PUSH_CATCH(Qgensym_file_error_catch_tag,1)) {
	    directory_pathname = Qunbound_in_protected_let;
	    menu_was_posted_qm = Qunbound_in_protected_let;
	    directory_namestring_1 = Qunbound_in_protected_let;
	    directory_namestring_for_notify_user = Qunbound_in_protected_let;
	    file_type_for_notify_user = Qunbound_in_protected_let;
	    title = Qunbound_in_protected_let;
	    parameters = Qunbound_in_protected_let;
	    menu_name = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		directory_pathname = 
			gensym_make_pathname_with_copied_components(Nil,
			Nil,Nil,Kwild,Nil,Knewest,default_pathname_qm);
		menu_was_posted_qm = Nil;
		directory_namestring_1 = default_pathname_qm && 
			gensym_wild_pathname_p(default_pathname_qm) ? 
			gensym_namestring(1,default_pathname_qm) : 
			gensym_device_and_directory_namestring(1,
			directory_pathname);
		directory_namestring_for_notify_user = directory_namestring_1;
		if (EQ(symbolic_file_type_qm,Qforeign_image))
		    file_type_for_notify_user = string_constant_33;
		else if (EQ(symbolic_file_type_qm,Qattribute))
		    file_type_for_notify_user = Qattribute;
		else
		    file_type_for_notify_user = string_constant_34;
		title = tformat_text_string(3,string_constant_35,
			file_type_for_notify_user,
			directory_namestring_for_notify_user);
		parameters = slot_value_list_4(directory_pathname,
			default_pathname_qm,symbolic_file_type_qm,
			load_case_qm);
		menu_name = disconnect_from_external_foreign_image_p ? 
			Qpathnames_in_directory : Qforeign_images;
		notify_user(3,string_constant_36,file_type_for_notify_user,
			directory_namestring_for_notify_user);
		menu_qm = make_menu_named_function(menu_name,Nil,Nil,Nil,
			parameters,Nil,Nil,title,Nil,Nil,Nil,Nil);
		if ( !TRUEP(menu_qm))
		    temp = notify_user(3,string_constant_37,
			    EQUAL(file_type_for_notify_user,
			    string_constant_34) ? string_constant_38 : 
			    file_type_for_notify_user,
			    directory_namestring_for_notify_user);
		else {
		    gensymed_symbol = 
			    make_slot_value_list_1(FIX((SI_Long)10L));
		    gensymed_symbol_1 = gensymed_symbol;
		    M_CAR(gensymed_symbol_1) = load_case_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    car_new_value = copy_gensym_pathname(default_pathname_qm);
		    M_CAR(gensymed_symbol_1) = car_new_value;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = directory_namestring_1;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = bring_formats_up_to_date_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = symbolic_file_type_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = warmboot_case_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = auto_merge_case_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = what_to_do_after_loading_kb_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = 
			    install_system_tables_if_merge_case_qm;
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = update_before_loading_qm;
		    choice_function_arguments = gensymed_symbol;
		    post_menu_function(menu_qm,
			    SYMBOL_FUNCTION(Qhandle_choice_for_directory_menu),
			    choice_function_arguments,
			    SYMBOL_FUNCTION(Qhandle_choice_for_directory_menu),
			    Nil,Nil,Nil);
		    menu_was_posted_qm = T;
		    temp = menu_was_posted_qm;
		}
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (parameters) {
		if ( !EQ(parameters,Qunbound_in_protected_let))
		    reclaim_slot_value_list_1(parameters);
	    }
	    if (title) {
		if ( !EQ(title,Qunbound_in_protected_let)) {
		    if ( !TRUEP(menu_was_posted_qm))
			reclaim_text_string(title);
		}
	    }
	    if (directory_namestring_1) {
		if ( !EQ(directory_namestring_1,Qunbound_in_protected_let)) {
		    if ( !TRUEP(menu_was_posted_qm))
			reclaim_text_string(directory_namestring_1);
		}
	    }
	    if (directory_pathname) {
		if ( !EQ(directory_pathname,Qunbound_in_protected_let))
		    reclaim_gensym_pathname(directory_pathname);
	    }
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    result_from_body = result;
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
	    notify_user(2,string_constant_7,report_string);
	    reclaim_text_string(report_string);
	    result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(result_from_body);
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object list_constant_16;    /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* COMPUTE-DIRECTORY-MENU-ITEMS */
Object compute_directory_menu_items(directory_pathname,default_pathname_qm,
	    symbolic_file_type_qm,load_case_qm)
    Object directory_pathname, default_pathname_qm, symbolic_file_type_qm;
    Object load_case_qm;
{
    Object pathnames, pathname_1, ab_loop_list_, file_namestring_1;
    Object ascii_filename, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ascii_pathnames, temp, image_info, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(131,88);
    pathnames = memq_function(symbolic_file_type_qm,list_constant_16) ? 
	    get_directory_for_kb_file_type(2,default_pathname_qm,
	    directory_pathname) : 
	    get_directory_for_non_kb_file_type(default_pathname_qm,
	    symbolic_file_type_qm,load_case_qm,directory_pathname);
    pathname_1 = Nil;
    ab_loop_list_ = pathnames;
    file_namestring_1 = Nil;
    ascii_filename = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pathname_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    file_namestring_1 = gensym_file_namestring(1,pathname_1);
    ascii_filename = copy_text_string(file_namestring_1);
    ab_loopvar__2 = slot_value_cons_1(ascii_filename,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    reclaim_text_string(file_namestring_1);
    reclaim_gensym_pathname(pathname_1);
    goto next_loop;
  end_loop:
    ascii_pathnames = ab_loopvar_;
    goto end_1;
    ascii_pathnames = Qnil;
  end_1:;
    reclaim_slot_value_list_1(pathnames);
    if (EQ(load_case_qm,Qdisconnect_from_foreign_image)) {
	temp = ascii_pathnames;
	image_info = Nil;
	ab_loop_list_ = All_external_foreign_function_images_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	image_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
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
		  twrite_foreign_image_connection_spec(connection_specification_to_foreign_image_function(image_info));
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	ab_loopvar__2 = slot_value_cons_1(temp_1,Nil);
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
	ascii_pathnames = nconc2(temp,temp_1);
    }
    return VALUES_1(ascii_pathnames);
}

/* EXTERNAL-FOREIGN-FUNCTION-IMAGES-COMPUTE-CHOICES */
Object external_foreign_function_images_compute_choices(mouse_pointer)
    Object mouse_pointer;
{
    Object image_info, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(131,89);
    image_info = Nil;
    ab_loop_list_ = All_external_foreign_function_images_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
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
	      twrite_foreign_image_connection_spec(connection_specification_to_foreign_image_function(image_info));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = slot_value_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* PATHNAMES-IN-DIRECTORY-COMPUTE-CHOICES */
Object pathnames_in_directory_compute_choices(mouse_pointer,
	    directory_pathname,default_pathname_qm,symbolic_file_type_qm,
	    load_case_qm)
    Object mouse_pointer, directory_pathname, default_pathname_qm;
    Object symbolic_file_type_qm, load_case_qm;
{
    x_note_fn_call(131,90);
    return compute_directory_menu_items(directory_pathname,
	    default_pathname_qm,symbolic_file_type_qm,load_case_qm);
}

static Object Qinit_file_command;  /* init-file-command */

static Object string_constant_39;  /* "disconnect from external foreign image at " */

/* HANDLE-CHOICE-FOR-DIRECTORY-MENU */
Object handle_choice_for_directory_menu(choice_menu,menu_item,choice,
	    load_case_qm,default_pathname,directory_namestring_1,
	    bring_formats_up_to_date_qm,symbolic_file_type_qm,
	    warmboot_case_qm,auto_merge_case_qm,
	    what_to_do_after_loading_kb_qm,
	    install_system_tables_if_merge_case_qm,update_before_loading_qm)
    Object choice_menu, menu_item, choice, load_case_qm, default_pathname;
    Object directory_namestring_1, bring_formats_up_to_date_qm;
    Object symbolic_file_type_qm, warmboot_case_qm, auto_merge_case_qm;
    Object what_to_do_after_loading_kb_qm;
    Object install_system_tables_if_merge_case_qm, update_before_loading_qm;
{
    volatile Object command_frame;
    Object text_to_parse, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1;
    volatile Object namestring_for_choice;
    volatile Object pathname_for_merge;
    volatile Object pathname_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(131,91);
    SAVE_STACK();
    if ( !TRUEP(choice)) {
	if (Doing_g2_init_file_p)
	    Autostart_after_doing_init_file_qm = Qnever_autostart;
	reclaim_text_string(directory_namestring_1);
	reclaim_gensym_pathname(default_pathname);
	result = delete_menu(choice_menu);
	RESTORE_STACK();
	return result;
    }
    else if (EQ(load_case_qm,Qdisconnect_from_foreign_image) && 
	    external_foreign_image_disconnection_spec_p(choice)) {
	command_frame = Qunbound_in_protected_let;
	text_to_parse = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    command_frame = make_command_frame(1,Qinit_file_command);
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
		      tformat(1,string_constant_39);
		      tformat(2,string_constant_7,choice);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    text_to_parse = convert_text_string_to_text(temp);
	    temp = text_to_parse;
	    temp_1 = command_frame;
	    if (parse_text_for_slot(3,temp,temp_1,
		    get_slot_description_of_class_description_function(Qbox_translation_and_text,
		    ISVREF(command_frame,(SI_Long)1L),Nil))) {
		delete_menu(choice_menu);
		temp = ISVREF(command_frame,(SI_Long)16L);
		temp = CAR(temp);
		disconnect_from_external_foreign_image(SECOND(temp));
	    }
	    reclaim_text_string(directory_namestring_1);
	    SAVE_VALUES(reclaim_gensym_pathname(default_pathname));
	}
	POP_UNWIND_PROTECT(0);
	if (command_frame) {
	    if ( !EQ(command_frame,Qunbound_in_protected_let))
		delete_frame(command_frame);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	namestring_for_choice = Qunbound_in_protected_let;
	pathname_for_merge = Qunbound_in_protected_let;
	pathname_1 = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    namestring_for_choice = copy_text_string(SYMBOLP(choice) ? 
		    symbol_name_text_string(choice) : choice);
	    pathname_for_merge = 
		    gensym_merge_pathnames_function(directory_namestring_1,
		    default_pathname,Nil);
	    pathname_1 = 
		    gensym_merge_pathnames_function(namestring_for_choice,
		    pathname_for_merge,Nil);
	    delete_menu(choice_menu);
	    if (EQ(symbolic_file_type_qm,Qattribute))
		load_custom_software_file_if_ok(copy_gensym_pathname(pathname_1),
			symbolic_file_type_qm);
	    else if (EQ(symbolic_file_type_qm,Qforeign_image)) {
		if (EQ(load_case_qm,Qconnect_to_foreign_image))
		    connect_to_foreign_image(copy_gensym_pathname(pathname_1));
		else if (EQ(load_case_qm,Qdisconnect_from_foreign_image))
		    disconnect_from_foreign_image(copy_gensym_pathname(pathname_1));
	    }
	    else
		load_or_merge_kb_if_ok(8,copy_gensym_pathname(pathname_1),
			load_case_qm,bring_formats_up_to_date_qm,
			warmboot_case_qm,auto_merge_case_qm,
			install_system_tables_if_merge_case_qm,
			what_to_do_after_loading_kb_qm,
			update_before_loading_qm);
	    reclaim_text_string(directory_namestring_1);
	    SAVE_VALUES(reclaim_gensym_pathname(default_pathname));
	}
	POP_UNWIND_PROTECT(0);
	if (pathname_1) {
	    if ( !EQ(pathname_1,Qunbound_in_protected_let))
		reclaim_gensym_pathname(pathname_1);
	}
	if (pathname_for_merge) {
	    if ( !EQ(pathname_for_merge,Qunbound_in_protected_let))
		reclaim_gensym_pathname(pathname_for_merge);
	}
	if (namestring_for_choice) {
	    if ( !EQ(namestring_for_choice,Qunbound_in_protected_let))
		reclaim_text_string(namestring_for_choice);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

static Object Kall;                /* :all */

/* MAKE-KB-NAME */
Object make_kb_name(gensym_pathname_1)
    Object gensym_pathname_1;
{
    Object temporary_text_string;

    x_note_fn_call(131,92);
    temporary_text_string = ISVREF(gensym_pathname_1,(SI_Long)4L);
    return copy_text_string_with_case_conversion(text_string_p(temporary_text_string) 
	    ? temporary_text_string : array_constant_5,Kall);
}

/* SPOT-GENERATOR-FOR-FILE-COMMAND-INFO-TABLE-FORMAT */
Object spot_generator_for_file_command_info_table_format(table,mouse_pointer)
    Object table, mouse_pointer;
{
    x_note_fn_call(131,93);
    generate_output_only_table_spot(table,mouse_pointer,
	    make_output_only_table_spot_1());
    return VALUES_1(Nil);
}

static Object string_constant_40;  /* "Loading ~a file \"~a\"" */

static Object string_constant_41;  /* "Done loading ~a file \"~a\"." */

static Object string_constant_42;  /* "~s does not exist." */

/* LOAD-CUSTOM-SOFTWARE-FILE-IF-OK */
Object load_custom_software_file_if_ok(gensym_pathname_to_load,
	    symbolic_file_type_qm)
    Object gensym_pathname_to_load, symbolic_file_type_qm;
{
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p, truename_qm, namestring_for_truename;
    Object success_qm, temp, result_from_body;
    Object namestring_for_attempted_pathname, gensymed_symbol, control_string;
    Object error_args, error_arg, ab_loop_list_, report_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(131,94);
    inside_handling_gensym_file_errors_scope_p = T;
    gensym_file_error_occurred_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_file_error_occurred_p,Qgensym_file_error_occurred_p,gensym_file_error_occurred_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p,Qinside_handling_gensym_file_errors_scope_p,inside_handling_gensym_file_errors_scope_p,
	      0);
	if (PUSH_CATCH(Qgensym_file_error_catch_tag,0)) {
	    truename_qm = gensym_probe_file(gensym_pathname_to_load);
	    if (truename_qm) {
		namestring_for_truename = gensym_namestring(1,truename_qm);
		success_qm = T;
		notify_user(3,string_constant_40,symbolic_file_type_qm,
			namestring_for_truename);
		if (EQ(symbolic_file_type_qm,Qattribute))
		    success_qm = load_attribute_file(gensym_pathname_to_load);
		if (EQ(symbolic_file_type_qm,Qattribute)) {
		    reclaim_pathname_or_string(Current_attribute_file_pathname_qm);
		    if (text_string_p(gensym_pathname_to_load)) {
			temp = gensym_pathname(gensym_pathname_to_load);
			reclaim_text_string(gensym_pathname_to_load);
			Current_attribute_file_pathname_qm = temp;
		    }
		    else
			Current_attribute_file_pathname_qm = 
				gensym_pathname_to_load;
		}
		if (success_qm)
		    notify_user(3,string_constant_41,symbolic_file_type_qm,
			    namestring_for_truename);
		reclaim_gensym_pathname(truename_qm);
		result_from_body = 
			reclaim_text_string(namestring_for_truename);
	    }
	    else {
		namestring_for_attempted_pathname = gensym_namestring(1,
			gensym_pathname_to_load);
		notify_user(2,string_constant_42,
			namestring_for_attempted_pathname);
		result_from_body = 
			reclaim_text_string(namestring_for_attempted_pathname);
	    }
	}
	else
	    result_from_body = CATCH_VALUES();
	POP_CATCH(0);
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
	    result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(result_from_body);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(System_statistics_writers, Qsystem_statistics_writers);

static Object string_constant_43;  /* "Writing G2 statistics file ~a ..." */

static Object string_constant_44;  /* "G2 statistics file completed." */

static Object string_constant_45;  /* "Unable to open G2 statistics file ~s, ~a." */

/* WRITE-G2-STATS */
Object write_g2_stats(pathname_1)
    Object pathname_1;
{
    Object inside_handling_gensym_file_errors_scope_p;
    Object gensym_file_error_occurred_p;
    volatile Object namestring_1;
    volatile Object namestring_for_user;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object open_g2_stream_qm;
    Object statistics_writer, ab_loop_list_, temp;
    volatile Object error_string_for_user;
    Object result_from_body, gensymed_symbol, control_string, error_args;
    Object error_arg, report_string;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(2);
    Object result;

    x_note_fn_call(131,95);
    SAVE_STACK();
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
		namestring_1 = gensym_namestring(1,pathname_1);
		namestring_for_user = copy_text_string(namestring_1);
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
			    ? gensym_namestring(1,namestring_1) : namestring_1;
		    open_g2_stream_qm = 
			    g2_stream_open_for_output(namestring_2);
		    if (open_g2_stream_qm) {
			notify_user(2,string_constant_43,namestring_for_user);
			write_g2_stats_header(open_g2_stream_qm);
			statistics_writer = Nil;
			ab_loop_list_ = System_statistics_writers;
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			statistics_writer = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			g2_stream_terpri(open_g2_stream_qm);
			FUNCALL_1(statistics_writer,open_g2_stream_qm);
			goto next_loop;
		      end_loop:;
			notify_user(1,string_constant_44);
			reclaim_pathname_or_string(Current_statistics_file_pathname_qm);
			if (text_string_p(pathname_1)) {
			    temp = gensym_pathname(pathname_1);
			    reclaim_text_string(pathname_1);
			    Current_statistics_file_pathname_qm = temp;
			}
			else
			    Current_statistics_file_pathname_qm = pathname_1;
			temp = Current_statistics_file_pathname_qm;
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
				Cached_unknown_error_string_with_code_qm = 
					tformat_text_string(2,
					Unknown_error_during_file_op_with_code_message,
					Internal_status_of_most_recent_file_operation);
				temp = 
					Cached_unknown_error_string_with_code_qm;
			    }
			    error_string_for_user = import_text_string(2,
				    temp,Qg2_stream_error_string);
			    temp = notify_user(3,string_constant_45,
				    namestring_for_user,error_string_for_user);
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
	    if (namestring_1) {
		if ( !EQ(namestring_1,Qunbound_in_protected_let))
		    reclaim_text_string(namestring_1);
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
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		error_arg = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (text_string_p(error_arg))
		    reclaim_text_string(error_arg);
		goto next_loop_1;
	      end_loop_1:
		reclaim_path_list_1(result_from_body);
	    }
	    report_string = temp;
	    notify_user(2,string_constant_7,report_string);
	    reclaim_text_string(report_string);
	}
      POP_SPECIAL();
    POP_SPECIAL();
    result = snapshot_memory_levels();
    RESTORE_STACK();
    return result;
}

/* G2-WRITE-STATS */
Object g2_write_stats(filename)
    Object filename;
{
    x_note_fn_call(131,96);
    return write_g2_stats(filename);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_flags_for_saving, Qkb_flags_for_saving);

Object Kb_flags_of_software = UNBOUND;

/* FRAME-FLAGS-REVISED-FUNCTION */
Object frame_flags_revised_function()
{
    x_note_fn_call(131,97);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)204L ? T : Nil);
}

/* CONNECTIONS-FOR-CLASS-SLOT-CORRECT-FORMAT-P */
Object connections_for_class_slot_correct_format_p()
{
    x_note_fn_call(131,98);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)216L ? T : Nil);
}

/* ICON-EDITOR-FIXED-P-FUNCTION */
Object icon_editor_fixed_p_function()
{
    x_note_fn_call(131,99);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)230L ? T : Nil);
}

/* LOADING-VERSION-3-OR-EARLIER-KB-P */
Object loading_version_3_or_earlier_kb_p()
{
    x_note_fn_call(131,100);
    return VALUES_1( !(IFIX(Kb_flags) >= (SI_Long)238L) ? T : Nil);
}

/* WORKSPACE-BACKGROUND-IMAGES-ARE-CENTERED-P */
Object workspace_background_images_are_centered_p()
{
    x_note_fn_call(131,101);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)244L ? T : Nil);
}

/* BAD-4-0-BETA-MAGNIFICATIONS-IN-TEXT-BOXES-REMOVED-P-FUNCTION */
Object bad_4_0_beta_magnifications_in_text_boxes_removed_p_function()
{
    x_note_fn_call(131,102);
    return VALUES_1(IFIX(Kb_flags) >= (SI_Long)248L ? T : Nil);
}

/* OLD-FORMAT-FOR-DEFAULT-OVERRIDES-P-FUNCTION */
Object old_format_for_default_overrides_p_function()
{
    x_note_fn_call(131,103);
    return VALUES_1(IFIX(Kb_flags) < (SI_Long)262L ? T : Nil);
}

/* LOADING-VERSION-5-OR-EARLIER-KB-P */
Object loading_version_5_or_earlier_kb_p()
{
    x_note_fn_call(131,104);
    return VALUES_1( !(IFIX(Kb_flags) >= (SI_Long)266L) ? T : Nil);
}

/* NEED-TO-NORMALIZE-MESSAGE-PROPERTIES-P-FUNCTION */
Object need_to_normalize_message_properties_p_function()
{
    x_note_fn_call(131,105);
    return VALUES_1(IFIX(Kb_flags) < (SI_Long)269L ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_flags_from_last_kb_read, Qkb_flags_from_last_kb_read);

DEFINE_VARIABLE_WITH_SYMBOL(System_version_from_last_kb_read, Qsystem_version_from_last_kb_read);

DEFINE_VARIABLE_WITH_SYMBOL(System_revision_from_last_kb_read, Qsystem_revision_from_last_kb_read);

DEFINE_VARIABLE_WITH_SYMBOL(System_quality_from_last_kb_read, Qsystem_quality_from_last_kb_read);

static Object Qobject;             /* object */

/* COUNT-AND-FIX-INVALID-ITEMS */
Object count_and_fix_invalid_items()
{
    Object cnt, scope_conses, ab_loopvar_, ab_loopvar__1, instance;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(131,106);
    cnt = FIX((SI_Long)0L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
	      (SI_Long)1L)) &&  !((SI_Long)0L != (IFIX(ISVREF(instance,
	      (SI_Long)5L)) & (SI_Long)262144L)) &&  
	      !TRUEP(g2gl_variable_compilation_p(instance))) {
	  cnt = FIXNUM_ADD1(cnt);
	  svref_new_value = IFIX(ISVREF(instance,(SI_Long)5L)) | 
		  (SI_Long)262144L;
	  ISVREF(instance,(SI_Long)5L) = FIX(svref_new_value);
	  format((SI_Long)3L,T,"Fixed the invalid frame number ~A~%",cnt);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(cnt);
}

void kb_load1_INIT()
{
    Object temp, gensymed_symbol, symbol, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp_1, temp_2;
    Object AB_package, Qg2_version_2015_beta_kb_flags;
    Object Qg2_version_2011_kb_flags, Qg2_version_8_3_alpha_0_kb_flags;
    Object Qg2_version_82r0_kb_flags, Qg2_version_81r0_kb_flags;
    Object Qg2_version_8_1_beta_0_kb_flags, Qg2_version_8_1_alpha_0_kb_flags;
    Object Qg2_version_8_beta_0_kb_flags, Qg2_version_7_beta_0_kb_flags;
    Object Qlast_kb_flags_saved_with_item_reference_parameters;
    Object Qg2_version_6_general_kb_flags;
    Object Qkb_flag_when_specific_procedure_method_died;
    Object Qkb_format_revision_for_kb_restrictions_reclassification;
    Object Qg2_write_stats, Qfunction_keeps_procedure_environment_valid_qm;
    Object Qcorresponding_extra_large_font_format_name;
    Object Qfile_command_extra_large_attribute_value_format;
    Object Qformat_description, string_constant_98;
    Object Qcorresponding_small_font_format_name;
    Object Qfile_command_small_attribute_value_format, string_constant_97;
    Object string_constant_96;
    Object Qspot_generator_for_file_command_info_table_format;
    Object Qtable_format_spot_generator, string_constant_95;
    Object string_constant_94, Qcommand_menu, string_constant_93;
    Object Qpathnames_in_directory_compute_choices;
    Object Qexternal_foreign_function_images;
    Object Qexternal_foreign_function_images_compute_choices, Qkb;
    Object list_constant_17, Qkb_load1, Qkb_save, Qruntime_data_only;
    Object Qkb_save_with_runtime_data, Qbackup, Qsave_module_into;
    Object Qsave_module, Qclasses_which_define, Qexecute_command;
    Object Qexecute_command_for_init_file_command;
    Object Qexecute_command_for_file_command, string_constant_92;
    Object list_constant_43, string_constant_91, string_constant_73;
    Object Qslot_value_writer;
    Object Qwrite_directory_contents_statistics_qm_from_slot;
    Object Qdirectory_contents_statistics_qm;
    Object Qwrite_file_command_directory_namestring_as_text_string_qm_from_slot;
    Object Qfile_command_directory_namestring_as_text_string_qm, Qcleanup;
    Object Qcleanup_for_kb_load_file_command, Qhandle_end_operation;
    Object Qhandle_end_operation_for_kb_load_file_command;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qsingle_line_comment, Qcomment;
    Object Qellipsis, Qquoted_character, list_constant_50, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_46;
    Object list_constant_45, string_constant_90, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object string_constant_85, string_constant_84, string_constant_83;
    Object string_constant_82, Qadd_items_to_edit_workspace;
    Object Qadd_items_to_edit_workspace_for_kb_load_file_command;
    Object Qslot_value_reclaimer;
    Object Qreclaim_gensym_pathnames_under_current_directory_qm_value;
    Object Qreclaim_file_command_directory_search_cache_qm_value;
    Object string_constant_81, string_constant_80, list_constant_44;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object Qcommand, list_constant_42, list_constant_41;
    Object Qdo_not_update_before_loading, Qresolve_conflicts_manually;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_init_file_command_for_slot;
    Object Qcompile_file_command_for_slot, list_constant_40, list_constant_39;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object Qpathname_component_token_menu, Qfile_name_punctuation_mark;
    Object Kall_token, list_constant_35, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18, Qtl_tl;
    Object Qtl_bs, Qex, array_constant_16, array_constant_15, Qqm, Qcbt, Qobt;
    Object Qsc, Qdol, Qcol, Qregistered_directory_of_names_p;
    Object string_constant_72, Qcm, Qkb_merge_option, Qkb_merge_options;
    Object Qkb_load_or_merge_option, Qkb_load_or_merge_options;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object Qmessage, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_57, string_constant_56, Qmenu, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52, Qes_c_c;
    Object Qdo_plist_checking_again, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object Qplus_max_cached_recent_loaded_kbs_plus, Qreclaim_recent_loaded_kbs;
    Object Qrun, Qout_subseries_of_values_64_vectors;
    Object Qsubseries_of_values_64_vector_memory_usage, string_constant_46;
    Object Qutilities2, Qreclaim_if_text_string_function, array_constant_14;
    Object Qdo_plist_checking, Qsubstitute_class_and_kb_flags;
    Object Qtemporary_workspace, Qcredits_workspace;

    x_note_fn_call(131,107);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qcredits_workspace = STATIC_SYMBOL("CREDITS-WORKSPACE",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qcredits_workspace,CONS(Qtemporary_workspace,
	    temp),Qsubstitute_class_and_kb_flags);
    Qbreak_if_name_inconsistency_qm = 
	    STATIC_SYMBOL("BREAK-IF-NAME-INCONSISTENCY\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbreak_if_name_inconsistency_qm,
	    Break_if_name_inconsistency_qm);
    Qkb_load1 = STATIC_SYMBOL("KB-LOAD1",AB_package);
    record_system_variable(Qbreak_if_name_inconsistency_qm,Qkb_load1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qneed_to_check_plist_p = STATIC_SYMBOL("NEED-TO-CHECK-PLIST-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qneed_to_check_plist_p,Need_to_check_plist_p);
    record_system_variable(Qneed_to_check_plist_p,Qkb_load1,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qdo_plist_checking = STATIC_SYMBOL("DO-PLIST-CHECKING",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qdo_plist_checking,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdo_plist_checking,
	    STATIC_FUNCTION(do_plist_checking,NIL,FALSE,0,0));
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    list_constant_1 = STATIC_LIST((SI_Long)2L,array_constant_14,
	    array_constant_4);
    list_constant = STATIC_CONS(array_constant,list_constant_1);
    Qcomplete_kb_name_qm = STATIC_SYMBOL("COMPLETE-KB-NAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcomplete_kb_name_qm,Complete_kb_name_qm);
    Qreclaim_if_text_string_function = 
	    STATIC_SYMBOL("RECLAIM-IF-TEXT-STRING-FUNCTION",AB_package);
    record_system_variable(Qcomplete_kb_name_qm,Qkb_load1,Nil,Qnil,Qnil,
	    Qreclaim_if_text_string_function,Qnil);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    Qframe_change_log = STATIC_SYMBOL("FRAME-CHANGE-LOG",AB_package);
    Qchange_log_information = STATIC_SYMBOL("CHANGE-LOG-INFORMATION",
	    AB_package);
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qname_of_defined_class = STATIC_SYMBOL("NAME-OF-DEFINED-CLASS",AB_package);
    Qicon_attributes_plist = STATIC_SYMBOL("ICON-ATTRIBUTES-PLIST",AB_package);
    Quser_overridable_system_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-SYSTEM-SLOTS",AB_package);
    Qsubworkspaces = STATIC_SYMBOL("SUBWORKSPACES",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qindexed_attributes_for_definition = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTES-FOR-DEFINITION",AB_package);
    Qjunction_block_class_for_connection = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CONNECTION",AB_package);
    Qinclude_in_menus_qm = STATIC_SYMBOL("INCLUDE-IN-MENUS\?",AB_package);
    Qinstantiate_qm = STATIC_SYMBOL("INSTANTIATE\?",AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
    Qicon_background_images = STATIC_SYMBOL("ICON-BACKGROUND-IMAGES",
	    AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qavailable_subseries_of_values_64_vectors = 
	    STATIC_SYMBOL("AVAILABLE-SUBSERIES-OF-VALUES-64-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_subseries_of_values_64_vectors,
	    Available_subseries_of_values_64_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_subseries_of_values_64_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_subseries_of_values_64_vectors = 
	    STATIC_SYMBOL("COUNT-OF-SUBSERIES-OF-VALUES-64-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_subseries_of_values_64_vectors,
	    Count_of_subseries_of_values_64_vectors);
    record_system_variable(Qcount_of_subseries_of_values_64_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_subseries_of_values_64_vectors_vector == UNBOUND)
	Available_subseries_of_values_64_vectors_vector = 
		make_thread_array(Nil);
    Qout_subseries_of_values_64_vectors = 
	    STATIC_SYMBOL("OUT-SUBSERIES-OF-VALUES-64-VECTORS",AB_package);
    Qsubseries_of_values_64_vector_memory_usage = 
	    STATIC_SYMBOL("SUBSERIES-OF-VALUES-64-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_46 = STATIC_STRING("1q83-rQy83*9y83-PCy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_subseries_of_values_64_vectors);
    push_optimized_constant(Qsubseries_of_values_64_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_46));
    SET_SYMBOL_FUNCTION(Qsubseries_of_values_64_vector_memory_usage,
	    STATIC_FUNCTION(subseries_of_values_64_vector_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_subseries_of_values_64_vectors,
	    STATIC_FUNCTION(out_subseries_of_values_64_vectors,NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    if (Collecting_updates_to_sensor_attributes_p == UNBOUND)
	Collecting_updates_to_sensor_attributes_p = Nil;
    if (Collected_updates_to_sensor_attributes == UNBOUND)
	Collected_updates_to_sensor_attributes = Nil;
    Qis_created = STATIC_SYMBOL("IS-CREATED",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qdo_not_clone = STATIC_SYMBOL("DO-NOT-CLONE",AB_package);
    Qlocal_name_or_names = STATIC_SYMBOL("LOCAL-NAME-OR-NAMES",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qsimulation_formulas_qm = STATIC_SYMBOL("SIMULATION-FORMULAS\?",
	    AB_package);
    Qcolumn_of_args = STATIC_SYMBOL("COLUMN-OF-ARGS",AB_package);
    Qcolumn_of_values = STATIC_SYMBOL("COLUMN-OF-VALUES",AB_package);
    Qembedded_rule_qm = STATIC_SYMBOL("EMBEDDED-RULE\?",AB_package);
    Qembedded_rule_in_user_menu_choice_qm = 
	    STATIC_SYMBOL("EMBEDDED-RULE-IN-USER-MENU-CHOICE\?",AB_package);
    Qlist_of_plots = STATIC_SYMBOL("LIST-OF-PLOTS",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qcompound_slot_descriptor = STATIC_SYMBOL("COMPOUND-SLOT-DESCRIPTOR",
	    AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qnumber_of_rows_in_table = STATIC_SYMBOL("NUMBER-OF-ROWS-IN-TABLE",
	    AB_package);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    Qabort_level_3 = STATIC_SYMBOL("ABORT-LEVEL-3",AB_package);
    Qdo_g2_init_file_qm = STATIC_SYMBOL("DO-G2-INIT-FILE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdo_g2_init_file_qm,Do_g2_init_file_qm);
    Qrun = STATIC_SYMBOL("RUN",AB_package);
    record_system_variable(Qdo_g2_init_file_qm,Qrun,T,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_kb_pathname_qm = STATIC_SYMBOL("CURRENT-KB-PATHNAME\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_kb_pathname_qm,Current_kb_pathname_qm);
    Qreclaim_gensym_pathname = STATIC_SYMBOL("RECLAIM-GENSYM-PATHNAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gensym_pathname,
	    STATIC_FUNCTION(reclaim_gensym_pathname,NIL,FALSE,1,1));
    record_system_variable(Qcurrent_kb_pathname_qm,Qkb_load1,Nil,Qnil,Qnil,
	    Qreclaim_gensym_pathname,Qnil);
    Qattempting_save_via_system_procedure_qm = 
	    STATIC_SYMBOL("ATTEMPTING-SAVE-VIA-SYSTEM-PROCEDURE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattempting_save_via_system_procedure_qm,
	    Attempting_save_via_system_procedure_qm);
    record_system_variable(Qattempting_save_via_system_procedure_qm,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_window_for_save_via_system_procedure_qm = 
	    STATIC_SYMBOL("G2-WINDOW-FOR-SAVE-VIA-SYSTEM-PROCEDURE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_window_for_save_via_system_procedure_qm,
	    G2_window_for_save_via_system_procedure_qm);
    record_system_variable(Qg2_window_for_save_via_system_procedure_qm,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qdefault_kb_pathname_qm = STATIC_SYMBOL("DEFAULT-KB-PATHNAME\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_kb_pathname_qm,Default_kb_pathname_qm);
    record_system_variable(Qdefault_kb_pathname_qm,Qkb_load1,Nil,Qnil,Qnil,
	    Qreclaim_gensym_pathname,Qnil);
    Qrecent_loaded_kbs = STATIC_SYMBOL("RECENT-LOADED-KBS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecent_loaded_kbs,Recent_loaded_kbs);
    Qreclaim_recent_loaded_kbs = STATIC_SYMBOL("RECLAIM-RECENT-LOADED-KBS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_recent_loaded_kbs,
	    STATIC_FUNCTION(reclaim_recent_loaded_kbs,NIL,FALSE,1,1));
    record_system_variable(Qrecent_loaded_kbs,Qkb_load1,Nil,Qnil,Qnil,
	    Qreclaim_recent_loaded_kbs,Qnil);
    Qplus_max_cached_recent_loaded_kbs_plus = 
	    STATIC_SYMBOL("+MAX-CACHED-RECENT-LOADED-KBS+",AB_package);
    SET_SYMBOL_VALUE(Qplus_max_cached_recent_loaded_kbs_plus,
	    FIX((SI_Long)10L));
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    string_constant_47 = STATIC_STRING("1m1m83=ny8335y1m83=ny832Gy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_47));
    Qwrite_g2_stats = STATIC_SYMBOL("WRITE-G2-STATS",AB_package);
    string_constant_48 = 
	    STATIC_STRING("13Fy1n8335y1m83-2Ny83wGy1nlm01n8335y1o83-2Ny83wGy1m9k83vy83-boy1nlmo1n8335y1o83Dgy83wGy1m9k83vy83-bqy1nlmo1m8335y1m83-CEy83LQy1m");
    string_constant_49 = 
	    STATIC_STRING("8335y1m83mby83LQy1m8335y1n83mby83LQy83iwy1m8335y1o83mby83LQy83iwy83dky1m8335y1n83mby83LQy83dky1m8335y1o83mby83LQy83dky83iwy1m833");
    string_constant_50 = 
	    STATIC_STRING("5y1m83-CCy83vAy1m8335y1n83-CCy83vAy83iwy1m8335y1o83-CCy83vAy83iwy83dky1m8335y1n83-CCy83vAy83dky1m8335y1o83-CCy83vAy83dky83iwy1m8");
    string_constant_51 = 
	    STATIC_STRING("335y1m9l838Ky1m8335y1m9l83uqy1m8335y1m9l1m9k83-VWy1n8335y1n9l83uqy838Ky1nlnm1m8335y83tIy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qwrite_g2_stats);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51)));
    if (Clear_text_grammar_rules_added_p == UNBOUND)
	Clear_text_grammar_rules_added_p = Nil;
    Qdo_plist_checking_again = STATIC_SYMBOL("DO-PLIST-CHECKING-AGAIN",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qdo_plist_checking_again,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant = STATIC_STRING("1m1m83-CDy83dky1m83-CDy83g1y");
    SET_SYMBOL_FUNCTION(Qdo_plist_checking_again,
	    STATIC_FUNCTION(do_plist_checking_again,NIL,FALSE,0,0));
    if (Compiled_code_grammar_rules_added_p == UNBOUND)
	Compiled_code_grammar_rules_added_p = Nil;
    Qes_c_c = STATIC_SYMBOL("ES-C-C",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qes_c_c,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_1 = STATIC_STRING("1l1m83-CDy83vWy");
    SET_SYMBOL_FUNCTION(Qes_c_c,STATIC_FUNCTION(es_c_c,NIL,FALSE,0,0));
    string_constant_52 = 
	    STATIC_STRING("1l1n83iwy1p1m9k83vy1m9k83-=Ky1m9k830*y1m9k83-mNy1m9k83-fYy83iwy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_52));
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_53 = 
	    STATIC_STRING("1l1n83g1y1s1m9k83vy1m9k83sLy1m9k835+y1m9k83-nSy1m9k83=Fy1m9k9l1m9k9m83-Uy1m83g1ys");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlog);
    push_optimized_constant(Qmessage);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_53));
    string_constant_54 = 
	    STATIC_STRING("1l1n83vWy1n1m9k83vy1m9k83-SZy1m9k83I2y83vWy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_54));
    string_constant_55 = 
	    STATIC_STRING("1l1n83dky1o1m9k83vy1m9k83Fmy1m9k83-Mgy1m9k83Gy83dky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_55));
    Qreformat_as_appropriate = STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE",
	    AB_package);
    Qdisconnect_from_all_foreign_images = 
	    STATIC_SYMBOL("DISCONNECT-FROM-ALL-FOREIGN-IMAGES",AB_package);
    Qconnect_to_foreign_image = STATIC_SYMBOL("CONNECT-TO-FOREIGN-IMAGE",
	    AB_package);
    Qconnect_to_external_foreign_image = 
	    STATIC_SYMBOL("CONNECT-TO-EXTERNAL-FOREIGN-IMAGE",AB_package);
    Qdisconnect_from_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-FOREIGN-IMAGE",AB_package);
    Qdisconnect_from_external_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-EXTERNAL-FOREIGN-IMAGE",AB_package);
    Qload_attribute_file = STATIC_SYMBOL("LOAD-ATTRIBUTE-FILE",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    string_constant_56 = 
	    STATIC_STRING("13cy1m83Cwy8335y1n83Cwy1m1m9k836Gy1m9k830Jy83-qjy1m83wGy83LQy1m83wGy83-iiy1m83wGy1m83uqy83-iiy1m83LQy838Ky1m83LQy83uqy1m83LQy1m8");
    string_constant_57 = 
	    STATIC_STRING("3uqy838Ky1m83vAy83v9y1m83vAy83-QVy1n83-1Yy1n1m9k83q2y1m9k83-mTy1m9k83-Npy83-mRy1n83-1Yy1n1m9k83-dfy1m9k83-mTy1m9k83-Npy83-mSy1n8");
    string_constant_58 = 
	    STATIC_STRING("3-1Yy1n1m9k83-L3y1m9k83-Uoy1m9k83-vQy9l1m83-1Yy83-Rcy1m83-bpy83-1Yy1n83-bpy1n1m9k83-aDy1m9k8l1m9k83-s5y83-aAy1n83-Rcy1m1m9k83-ql");
    string_constant_59 = 
	    STATIC_STRING("y1m9k83-JMy83-qiy1n83-Rcy1n1m9k9m1m9k83-qly1m9k83-JMy83-gUy1n83-Rcy1m1m9k83-wry1m9k83-JMy83-wny1n83-Rcy1v1m9k83-wry1m9k83-JMy1m9");
    string_constant_60 = 
	    STATIC_STRING("k83-ty1m9k83-nQy1m9k832+y1m9k83-q8y1m9k831Ay1m9k83*5y1m9k83hGy1m9k83*5y1m9k83ldy83-woy1n83mby1o1m9k83Cy1m9k83Vqy83Duy1m9k83*5y1m");
    string_constant_61 = 
	    STATIC_STRING("83mbyn1n83mby1o1m9k83Cy1m9k83-tZy1m9k83Vqy1m9k83*5y1m83mby83*+Oy1n83-CCy1o1m9k83Cy1m9k83Vqy83Duy1m9k83-=ny1m83-CCyn1n83-CCy1o1m9");
    string_constant_62 = 
	    STATIC_STRING("k83Cy1m9k83-tZy1m9k83Vqy1m9k83-=ny1m83-CCy83*+Oy1n9n1o1m9k9o1m9k830Jy1m9k83-qsy1m9k83*5y9n1n83-2Ny1m1m9k9p1m9k83k8y9p1n83-2Ny1m1");
    string_constant_63 = 
	    STATIC_STRING("m9k9q1m9k83k8y9q1n83Dgy1m1m9k9q1m9k83k8y9q1n83-CEy1o1m9k83Cy1m9k831Sy1m9k83k8y1m9k83*5y83TEy1m83tIy1m83-d=y83wGy1n83tIy1p1m9k83v");
    string_constant_64 = 
	    STATIC_STRING("Cy1m9k832+y1m9k830*y1m9k83wXy1m9k83-ZDy1l9r1n83-d=y1o1m9k836iy1m9k83=3y1m9k83wXy1m9k83Cmy9s1n83tIy1r1m9k836iy1m9k83=3y1m9k83w1y1");
    string_constant_65 = 
	    STATIC_STRING("m9k83wXy1m9k83Cmy1m9k83=Gy83-Ufy1m9tr1n83-Ufy1p1m9k83bYy1m9k83Ray83-Uy1m9k83Xvy83Sy1n83bYynp1n83-d=y1o1m9k83vCy1m9k832+y1m9k83wX");
    string_constant_66 = 
	    STATIC_STRING("y1m9k83Cmy9u1n83tIy1r1m9k83vCy1m9k832+y1m9k83w1y1m9k83wXy1m9k83Cmy1m9k83=Gy83-Ufy1m9vr1n83-d=y1n1m9k9p1m9k83-qy1m9k83LLy9w1n83-i");
    string_constant_67 = 
	    STATIC_STRING("iy1n1m9k83Xiy1m9k83v8y1m9k9x83-iiy1n83uqy1p1m9k83-9y838Ky1m9k83*ty1m9k83Py1m9k83-Aym1n83-QVy1p1m9k83-9y83v9y1m9k83*ty1m9k83Py1m9");
    string_constant_68 = STATIC_STRING("k83-Aym1m838Ky83-2y1m838Ky83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qreformat_as_appropriate);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qwrite_g2_stats);
    push_optimized_constant(Qwrite);
    push_optimized_constant(Qload);
    push_optimized_constant(Qmerge);
    push_optimized_constant(Qdisconnect_from_all_foreign_images);
    push_optimized_constant(Qconnect_to_foreign_image);
    push_optimized_constant(Qconnect_to_external_foreign_image);
    push_optimized_constant(Qdisconnect_from_foreign_image);
    push_optimized_constant(Qdisconnect_from_external_foreign_image);
    push_optimized_constant(Qload_attribute_file);
    push_optimized_constant(Qmenu);
    add_grammar_rules_function(regenerate_optimized_constant(list(13,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67,
	    string_constant_68)));
    if (Source_code_control_grammar_is_present_p == UNBOUND)
	Source_code_control_grammar_is_present_p = Nil;
    string_constant_2 = 
	    STATIC_STRING("1y1m8335y1p83mby83LQy83iwy83dky83g1y1m8335y1o83mby83LQy83iwy83g1y1m8335y1p83mby83LQy83iwy83g1y83dky1m8335y1p83mby83LQy83dky83iwy");
    string_constant_3 = 
	    STATIC_STRING("83g1y1m8335y1o83mby83LQy83dky83g1y1m8335y1p83mby83LQy83dky83g1y83iwy1m8335y1n83mby83LQy83g1y1m8335y1o83mby83LQy83g1y83iwy1m8335y");
    string_constant_4 = 
	    STATIC_STRING("1p83mby83LQy83g1y83iwy83dky1m8335y1o83mby83LQy83g1y83dky1m8335y1p83mby83LQy83g1y83dky83iwy1m8335y1l83-DQy1n83-1Yy1r1m9k837cy1m9k");
    string_constant_5 = 
	    STATIC_STRING("832+y1m9k83aWy1m9k83I2y1m9k83Ioy1m9k83HAy1m9k83-d2y83-vTy1n83-1Yy1t1m9k830Iy1m9k9l1m9k837cy1m9k832+y1m9k83aWy1m9k83I2y1m9k83Ioy1");
    string_constant_6 = STATIC_STRING("m9k83HAy1m9k83-d2y83-Rjy");
    string_constant_69 = 
	    STATIC_STRING("1p1n83-DQy1n83-DRy1m9k837cy83LQy1m83-njyn1n83-DQy1n83-DRy1m9k8331y83LQy1m83-ngyn1n83-DQy1n83-DRy1m9k83-uky83LQy1m83-niyn1n83-DQy");
    string_constant_70 = 
	    STATIC_STRING("1r83-DRy1m9k83sLy83LQy1m9k83=Fy1m9k9l1m9k9m83-Uy1n83-nfynr1n83-DQy1n83-DRy1m9k83-C=y83LQy1m83-nhyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlog);
    push_optimized_constant(Qmessage);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_69,
	    string_constant_70)));
    string_constant_71 = 
	    STATIC_STRING("1l1m83-DRy1n1m9k83aWy1m9k83I2y1m9k83Ioy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_71));
    Qkb_load_or_merge_options = STATIC_SYMBOL("KB-LOAD-OR-MERGE-OPTIONS",
	    AB_package);
    Qkb_load_or_merge_option = STATIC_SYMBOL("KB-LOAD-OR-MERGE-OPTION",
	    AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(3,Qkb_load_or_merge_options,
	    Qkb_load_or_merge_option,Qcm);
    Qkb_merge_options = STATIC_SYMBOL("KB-MERGE-OPTIONS",AB_package);
    Qkb_merge_option = STATIC_SYMBOL("KB-MERGE-OPTION",AB_package);
    add_grammar_rules_for_list(3,Qkb_merge_options,Qkb_merge_option,Qcm);
    string_constant_72 = 
	    STATIC_STRING("1r1m83CKy83-WAy1m83CKy1m83-WAy83CKy1m83-WAy838Ky1m83-WAy83v9y1m83-WAy83-Try1m83v9y83-2y1m83v9y83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_72));
    Qdirectory_name = STATIC_SYMBOL("DIRECTORY-NAME",AB_package);
    Qregistered_directory_of_names_p = 
	    STATIC_SYMBOL("REGISTERED-DIRECTORY-OF-NAMES-P",AB_package);
    mutate_global_property(Qdirectory_name,T,Qregistered_directory_of_names_p);
    Qfile_name = STATIC_SYMBOL("FILE-NAME",AB_package);
    mutate_global_property(Qfile_name,T,Qregistered_directory_of_names_p);
    list_constant_18 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)47L),Qslash);
    Qcol = STATIC_SYMBOL(":",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)58L),Qcol);
    Qdol = STATIC_SYMBOL("$",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)36L),Qdol);
    Qsc = STATIC_SYMBOL(";",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)59L),Qsc);
    list_constant_22 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)60L),Qnum_lt);
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)62L),Qnum_gt);
    Qobt = STATIC_SYMBOL("[",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)91L),Qobt);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)93L),Qcbt);
    list_constant_26 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)42L),Qstar);
    Qqm = STATIC_SYMBOL("\?",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)63L),Qqm);
    array_constant_15 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    list_constant_28 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)123L),
	    array_constant_15);
    array_constant_16 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    list_constant_29 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)125L),
	    array_constant_16);
    Qex = STATIC_SYMBOL("!",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)33L),Qex);
    Qtl_bs = STATIC_SYMBOL("~\\",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)92L),Qtl_bs);
    Qtl_tl = STATIC_SYMBOL("~~",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)126L),Qtl_tl);
    list_constant_33 = STATIC_LIST((SI_Long)15L,list_constant_18,
	    list_constant_19,list_constant_20,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25,list_constant_26,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30,
	    list_constant_31,list_constant_32);
    File_name_punctuation_alist = list_constant_33;
    Qfile_name_punctuation_mark = 
	    STATIC_SYMBOL("FILE-NAME-PUNCTUATION-MARK",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qfile_name_punctuation_mark,
	    Qnumber);
    list_constant_35 = STATIC_CONS(list_constant_34,Qnil);
    if (File_punctuation_mark_grammar_rules == UNBOUND) {
	symbol = Nil;
	ab_loop_list_ = File_name_punctuation_alist;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	temp = CDR(ab_loop_desetq_);
	symbol = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = LIST_1(LIST_2(Qfile_name_punctuation_mark,
		LIST_2(Qquote,symbol)));
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
	File_punctuation_mark_grammar_rules = nconc2(temp,list_constant_35);
    }
    add_grammar_rules_function(File_punctuation_mark_grammar_rules);
    Kall_token = STATIC_SYMBOL("ALL-TOKEN",Pkeyword);
    Qpathname_component_token_menu = 
	    STATIC_SYMBOL("PATHNAME-COMPONENT-TOKEN-MENU",AB_package);
    list_constant_36 = STATIC_CONS(Kall_token,Qpathname_component_token_menu);
    list_constant_37 = STATIC_CONS(Qfile_name,Qpathname_component_token_menu);
    list_constant_38 = STATIC_CONS(Qdirectory_name,
	    Qpathname_component_token_menu);
    list_constant_39 = STATIC_CONS(Qfile_name_punctuation_mark,
	    Qpathname_component_token_menu);
    list_constant_40 = STATIC_LIST((SI_Long)4L,list_constant_36,
	    list_constant_37,list_constant_38,list_constant_39);
    Token_menu_class_per_category_overrides = list_constant_40;
    Qfile_command = STATIC_SYMBOL("FILE-COMMAND",AB_package);
    Qcompile_file_command_for_slot = 
	    STATIC_SYMBOL("COMPILE-FILE-COMMAND-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_file_command_for_slot,
	    STATIC_FUNCTION(compile_file_command_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qfile_command,
	    SYMBOL_FUNCTION(Qcompile_file_command_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qfile_command,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qinit_file_command = STATIC_SYMBOL("INIT-FILE-COMMAND",AB_package);
    Qcompile_init_file_command_for_slot = 
	    STATIC_SYMBOL("COMPILE-INIT-FILE-COMMAND-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_init_file_command_for_slot,
	    STATIC_FUNCTION(compile_init_file_command_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qinit_file_command,
	    SYMBOL_FUNCTION(Qcompile_init_file_command_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qinit_file_command,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qstart_g2 = STATIC_SYMBOL("START-G2",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qload,Qmerge);
    string_constant_7 = STATIC_STRING("~a");
    string_constant_8 = 
	    STATIC_STRING("The default file name ~s cannot be parsed on this platform.");
    string_constant_9 = 
	    STATIC_STRING("The file name ~s contains an illegal wildcard.");
    string_constant_10 = 
	    STATIC_STRING("The KB-loading option `~a\' is not consistent with `starting afterwards\'");
    Qnever_start_afterwards = STATIC_SYMBOL("NEVER-START-AFTERWARDS",
	    AB_package);
    string_constant_11 = STATIC_STRING("not starting afterwards");
    string_constant_12 = STATIC_STRING("warmbooting afterwards");
    string_constant_13 = 
	    STATIC_STRING("The KB-loading option `~a\' is not consistent with `warmbooting afterwards\'");
    string_constant_14 = STATIC_STRING("starting afterwards");
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qper_directory_menu = STATIC_SYMBOL("PER-DIRECTORY-MENU",AB_package);
    Qstart_afterwards = STATIC_SYMBOL("START-AFTERWARDS",AB_package);
    Qwarmboot_afterwards = STATIC_SYMBOL("WARMBOOT-AFTERWARDS",AB_package);
    Qwarmboot_afterwards_with_catch_up = 
	    STATIC_SYMBOL("WARMBOOT-AFTERWARDS-WITH-CATCH-UP",AB_package);
    Qinstall_system_tables = STATIC_SYMBOL("INSTALL-SYSTEM-TABLES",AB_package);
    Qresolve_conflicts_automatically = 
	    STATIC_SYMBOL("RESOLVE-CONFLICTS-AUTOMATICALLY",AB_package);
    Qupdate_before_loading = STATIC_SYMBOL("UPDATE-BEFORE-LOADING",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)4L,Qinstall_system_tables,
	    Qreformat_as_appropriate,Qresolve_conflicts_automatically,
	    Qupdate_before_loading);
    Qresolve_conflicts_manually = 
	    STATIC_SYMBOL("RESOLVE-CONFLICTS-MANUALLY",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,
	    Qresolve_conflicts_automatically,Qresolve_conflicts_manually);
    Qdo_not_update_before_loading = 
	    STATIC_SYMBOL("DO-NOT-UPDATE-BEFORE-LOADING",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qupdate_before_loading,
	    Qdo_not_update_before_loading);
    list_constant_4 = STATIC_LIST((SI_Long)2L,list_constant_41,
	    list_constant_42);
    Qwhat_to_do_after_loading_kb = 
	    STATIC_SYMBOL("WHAT-TO-DO-AFTER-LOADING-KB",AB_package);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    Qsave_module = STATIC_SYMBOL("SAVE-MODULE",AB_package);
    Qsave_module_into = STATIC_SYMBOL("SAVE-MODULE-INTO",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)4L,Qkb_save,Qsave,Qsave_module,
	    Qsave_module_into);
    Qincluding_all_required_modules = 
	    STATIC_SYMBOL("INCLUDING-ALL-REQUIRED-MODULES",AB_package);
    Qusing_clear_text = STATIC_SYMBOL("USING-CLEAR-TEXT",AB_package);
    Qcommit_after_saving = STATIC_SYMBOL("COMMIT-AFTER-SAVING",AB_package);
    Qemitting_c_code = STATIC_SYMBOL("EMITTING-C-CODE",AB_package);
    Qcurrent_attribute_file_pathname_qm = 
	    STATIC_SYMBOL("CURRENT-ATTRIBUTE-FILE-PATHNAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_attribute_file_pathname_qm,
	    Current_attribute_file_pathname_qm);
    record_system_variable(Qcurrent_attribute_file_pathname_qm,Qkb_load1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_statistics_file_pathname_qm = 
	    STATIC_SYMBOL("CURRENT-STATISTICS-FILE-PATHNAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_statistics_file_pathname_qm,
	    Current_statistics_file_pathname_qm);
    record_system_variable(Qcurrent_statistics_file_pathname_qm,Qkb_load1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_foreign_image_pathname_qm = 
	    STATIC_SYMBOL("CURRENT-FOREIGN-IMAGE-PATHNAME\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_foreign_image_pathname_qm,
	    Current_foreign_image_pathname_qm);
    record_system_variable(Qcurrent_foreign_image_pathname_qm,Qkb_load1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qstatistics = STATIC_SYMBOL("STATISTICS",AB_package);
    Qforeign_image = STATIC_SYMBOL("FOREIGN-IMAGE",AB_package);
    Qxml = STATIC_SYMBOL("XML",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Quser = STATIC_SYMBOL("USER",AB_package);
    string_constant_15 = STATIC_STRING("~a (~s by default), using clear text");
    string_constant_16 = STATIC_STRING("~a (~s by default)");
    array_constant_5 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    string_constant_17 = STATIC_STRING("ALL-~a");
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    list_constant_43 = STATIC_CONS(Qcommand,Qnil);
    check_if_superior_classes_are_defined(Qfile_command,list_constant_43);
    string_constant_73 = STATIC_STRING("0");
    string_constant_74 = 
	    STATIC_STRING("1l4z8r83ry83ry8335y8335y00001o1l8l1n8p8335y83Gy1l8o1l83-3y00000");
    string_constant_75 = 
	    STATIC_STRING("1n8q1m8335y1l83=ny1n83ry01n8p8335y83Gy");
    temp = regenerate_optimized_constant(string_constant_73);
    temp_1 = regenerate_optimized_constant(string_constant_74);
    add_class_to_environment(9,Qfile_command,list_constant_43,Nil,temp,Nil,
	    temp_1,list_constant_43,
	    regenerate_optimized_constant(string_constant_75),Nil);
    Qkb_load_file_command = STATIC_SYMBOL("KB-LOAD-FILE-COMMAND",AB_package);
    list_constant_44 = STATIC_CONS(Qfile_command,Qnil);
    check_if_superior_classes_are_defined(Qkb_load_file_command,
	    list_constant_44);
    string_constant_76 = 
	    STATIC_STRING("1u4z8r83ry83ry83TCy83TCy00001o1l8l1n8p83CKy83Gy1l8o1l83-3y000004z8r83Iuy83Iuy83TCy83TCy00001n1l8l1m8p83LMy1l83Fy000004z8r83Ivy83");
    string_constant_77 = 
	    STATIC_STRING("Ivy83TCy83TCy00001l1l8l000004z8r83J-y83J-y83TCy83TCy00001l1l8l000004z8r83Ity83Ity83TCy83TCy00001n1l8l1m8p83Jvy1l83Fy000004z8r83Q");
    string_constant_78 = 
	    STATIC_STRING("1y83Q1y83TCy83TCy00001l1l8l000004z8r83LNy83LNy83TCy83TCy00001l1l8l000004z8r83UGy83UGy83TCy83TCy01l+3Cy3-ty3-dy3-7y3-vy3-ty3-Uy3-");
    string_constant_79 = 
	    STATIC_STRING("*y3-ey3-8y3-vykkkku3A++y001l1l8l000004z8r83VLy83VLy83TCy83TCy00001l1l8l000004z8r83Z5y83Z5y83TCy83TCy00001l1l8l00000");
    string_constant_80 = 
	    STATIC_STRING("1w8q1m83TCy1l8335y1n83ry01n8p83CKy83Gy1o83Iuy01m8p83LMy83Fy1m83Ivy01m83J-y01o83Ity01m8p83Jvy83Fy1m83Q1y01m83LNy01m83UGy1l5u{kK}{");
    string_constant_81 = STATIC_STRING("bBlL}1m83VLy01m83Z5y0");
    temp = regenerate_optimized_constant(string_constant_73);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79));
    add_class_to_environment(9,Qkb_load_file_command,list_constant_44,Nil,
	    temp,Nil,temp_1,list_constant_44,
	    regenerate_optimized_constant(LIST_2(string_constant_80,
	    string_constant_81)),Nil);
    Qfile_command_directory_search_cache_qm = 
	    STATIC_SYMBOL("FILE-COMMAND-DIRECTORY-SEARCH-CACHE\?",AB_package);
    Qreclaim_file_command_directory_search_cache_qm_value = 
	    STATIC_SYMBOL("RECLAIM-FILE-COMMAND-DIRECTORY-SEARCH-CACHE\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_file_command_directory_search_cache_qm_value,
	    STATIC_FUNCTION(reclaim_file_command_directory_search_cache_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qfile_command_directory_search_cache_qm,
	    SYMBOL_FUNCTION(Qreclaim_file_command_directory_search_cache_qm_value),
	    Qslot_value_reclaimer);
    Qgensym_pathnames_under_current_directory_qm = 
	    STATIC_SYMBOL("GENSYM-PATHNAMES-UNDER-CURRENT-DIRECTORY\?",
	    AB_package);
    Qreclaim_gensym_pathnames_under_current_directory_qm_value = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-PATHNAMES-UNDER-CURRENT-DIRECTORY\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gensym_pathnames_under_current_directory_qm_value,
	    STATIC_FUNCTION(reclaim_gensym_pathnames_under_current_directory_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgensym_pathnames_under_current_directory_qm,
	    SYMBOL_FUNCTION(Qreclaim_gensym_pathnames_under_current_directory_qm_value),
	    Qslot_value_reclaimer);
    Qadd_items_to_edit_workspace_for_kb_load_file_command = 
	    STATIC_SYMBOL("ADD-ITEMS-TO-EDIT-WORKSPACE-FOR-KB-LOAD-FILE-COMMAND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_items_to_edit_workspace_for_kb_load_file_command,
	    STATIC_FUNCTION(add_items_to_edit_workspace_for_kb_load_file_command,
	    NIL,FALSE,4,4));
    Qadd_items_to_edit_workspace = 
	    STATIC_SYMBOL("ADD-ITEMS-TO-EDIT-WORKSPACE",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qadd_items_to_edit_workspace_for_kb_load_file_command);
    set_get(Qkb_load_file_command,Qadd_items_to_edit_workspace,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qadd_items_to_edit_workspace),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_load_file_command,temp);
    mutate_global_property(Qadd_items_to_edit_workspace,temp_2,
	    Qclasses_which_define);
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    Qdo_pathname_component_conversion = 
	    STATIC_SYMBOL("DO-PATHNAME-COMPONENT-CONVERSION",AB_package);
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    SET_SYMBOL_FUNCTION(Qdo_pathname_component_conversion,
	    STATIC_FUNCTION(do_pathname_component_conversion,NIL,FALSE,3,3));
    Qcurrent_directory_contents_statistics_qm = 
	    STATIC_SYMBOL("CURRENT-DIRECTORY-CONTENTS-STATISTICS\?",
	    AB_package);
    Qfile_command_info_table_format = 
	    STATIC_SYMBOL("FILE-COMMAND-INFO-TABLE-FORMAT",AB_package);
    Qfile_command_attribute_value_format = 
	    STATIC_SYMBOL("FILE-COMMAND-ATTRIBUTE-VALUE-FORMAT",AB_package);
    Qfont_for_editing = STATIC_SYMBOL("FONT-FOR-EDITING",AB_package);
    Qcurrent_directory_namestring_as_text_string_for_file_command_qm = 
	    STATIC_SYMBOL("CURRENT-DIRECTORY-NAMESTRING-AS-TEXT-STRING-FOR-FILE-COMMAND\?",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,
	    Qcurrent_directory_contents_statistics_qm,
	    Qcurrent_directory_namestring_as_text_string_for_file_command_qm);
    string_constant_82 = STATIC_STRING("start afterwards");
    Qstarting_afterwards = STATIC_SYMBOL("STARTING-AFTERWARDS",AB_package);
    string_constant_83 = STATIC_STRING("never start afterwards");
    Qnot_starting_afterwards = STATIC_SYMBOL("NOT-STARTING-AFTERWARDS",
	    AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)4L,string_constant_82,
	    Qstarting_afterwards,string_constant_83,Qnot_starting_afterwards);
    string_constant_84 = STATIC_STRING("warmboot afterwards");
    Qwarmbooting_afterwards = STATIC_SYMBOL("WARMBOOTING-AFTERWARDS",
	    AB_package);
    string_constant_85 = 
	    STATIC_STRING("warmboot afterwards with catch-up feature");
    Qwarmbooting_afterwards_with_catch_up = 
	    STATIC_SYMBOL("WARMBOOTING-AFTERWARDS-WITH-CATCH-UP",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)4L,string_constant_84,
	    Qwarmbooting_afterwards,string_constant_85,
	    Qwarmbooting_afterwards_with_catch_up);
    string_constant_86 = STATIC_STRING("merge in this KB");
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    string_constant_87 = 
	    STATIC_STRING("merge in this KB and install its system tables");
    Qmerge_kb_and_install_system_tables = 
	    STATIC_SYMBOL("MERGE-KB-AND-INSTALL-SYSTEM-TABLES",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)4L,string_constant_86,
	    Qmerge_kb,string_constant_87,Qmerge_kb_and_install_system_tables);
    string_constant_88 = STATIC_STRING("bring formats up-to-date");
    Qbring_formats_up_to_date = STATIC_SYMBOL("BRING-FORMATS-UP-TO-DATE",
	    AB_package);
    string_constant_89 = STATIC_STRING("automatically resolve conflicts");
    Qautomatically_resolving_conflicts = 
	    STATIC_SYMBOL("AUTOMATICALLY-RESOLVING-CONFLICTS",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)4L,string_constant_88,
	    Qbring_formats_up_to_date,string_constant_89,
	    Qautomatically_resolving_conflicts);
    string_constant_90 = 
	    STATIC_STRING("update from source code control before loading");
    list_constant_45 = STATIC_CONS(Qupdate_before_loading,Qnil);
    list_constant_50 = STATIC_CONS(string_constant_90,list_constant_45);
    list_constant_7 = STATIC_LIST((SI_Long)5L,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49,
	    list_constant_50);
    Qmerging_kb_is_the_default_qm = 
	    STATIC_SYMBOL("MERGING-KB-IS-THE-DEFAULT\?",AB_package);
    Qcurrent_namestring_as_text_string_for_file_command_qm = 
	    STATIC_SYMBOL("CURRENT-NAMESTRING-AS-TEXT-STRING-FOR-FILE-COMMAND\?",
	    AB_package);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qcurrent_directory_namestring_for_file_command_qm = 
	    STATIC_SYMBOL("CURRENT-DIRECTORY-NAMESTRING-FOR-FILE-COMMAND\?",
	    AB_package);
    Qquoted_character = STATIC_SYMBOL("QUOTED-CHARACTER",AB_package);
    Qellipsis = STATIC_SYMBOL("ELLIPSIS",AB_package);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    Qsingle_line_comment = STATIC_SYMBOL("SINGLE-LINE-COMMENT",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)4L,Qquoted_character,Qellipsis,
	    Qcomment,Qsingle_line_comment);
    list_constant_9 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)10L));
    string_constant_18 = STATIC_STRING("Cannot find ~s");
    Kdisplay_notification = STATIC_SYMBOL("DISPLAY-NOTIFICATION",Pkeyword);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qretain_current_directory_menus_p = 
	    STATIC_SYMBOL("RETAIN-CURRENT-DIRECTORY-MENUS-P",AB_package);
    string_constant_19 = STATIC_STRING("~s is not a file or directory name");
    Qhandle_end_operation_for_kb_load_file_command = 
	    STATIC_SYMBOL("HANDLE-END-OPERATION-FOR-KB-LOAD-FILE-COMMAND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_end_operation_for_kb_load_file_command,
	    STATIC_FUNCTION(handle_end_operation_for_kb_load_file_command,
	    NIL,FALSE,2,2));
    Qhandle_end_operation = STATIC_SYMBOL("HANDLE-END-OPERATION",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qhandle_end_operation_for_kb_load_file_command);
    set_get(Qkb_load_file_command,Qhandle_end_operation,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qhandle_end_operation),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_load_file_command,temp);
    mutate_global_property(Qhandle_end_operation,temp_2,Qclasses_which_define);
    Qcleanup_for_kb_load_file_command = 
	    STATIC_SYMBOL("CLEANUP-FOR-KB-LOAD-FILE-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_kb_load_file_command,
	    STATIC_FUNCTION(cleanup_for_kb_load_file_command,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_kb_load_file_command);
    set_get(Qkb_load_file_command,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_load_file_command,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qget_file_command_check_box_value = 
	    STATIC_SYMBOL("GET-FILE-COMMAND-CHECK-BOX-VALUE",AB_package);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    SET_SYMBOL_FUNCTION(Qget_file_command_check_box_value,
	    STATIC_FUNCTION(get_file_command_check_box_value,NIL,FALSE,2,2));
    string_constant_20 = STATIC_STRING("*");
    string_constant_21 = STATIC_STRING("*.*");
    array_constant_7 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Qnamestring_is_xml_file_p = STATIC_SYMBOL("NAMESTRING-IS-XML-FILE-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnamestring_is_xml_file_p,
	    STATIC_FUNCTION(namestring_is_xml_file_p,NIL,FALSE,1,1));
    Qload_command_file_types = STATIC_SYMBOL("LOAD-COMMAND-FILE-TYPES",
	    AB_package);
    Qall_file_namestrings_in_directory_of_names = 
	    STATIC_SYMBOL("ALL-FILE-NAMESTRINGS-IN-DIRECTORY-OF-NAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_file_namestrings_in_directory_of_names,
	    All_file_namestrings_in_directory_of_names);
    record_system_variable(Qall_file_namestrings_in_directory_of_names,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qall_directory_namestrings_in_directory_of_names = 
	    STATIC_SYMBOL("ALL-DIRECTORY-NAMESTRINGS-IN-DIRECTORY-OF-NAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_directory_namestrings_in_directory_of_names,
	    All_directory_namestrings_in_directory_of_names);
    record_system_variable(Qall_directory_namestrings_in_directory_of_names,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qdefaults_namestring_for_directory_of_names_qm = 
	    STATIC_SYMBOL("DEFAULTS-NAMESTRING-FOR-DIRECTORY-OF-NAMES\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefaults_namestring_for_directory_of_names_qm,
	    Defaults_namestring_for_directory_of_names_qm);
    record_system_variable(Qdefaults_namestring_for_directory_of_names_qm,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_22 = STATIC_STRING("~a~a");
    array_constant_8 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    string_constant_23 = STATIC_STRING("(directory unknown)");
    Qfile_command_directory_namestring_as_text_string_qm = 
	    STATIC_SYMBOL("FILE-COMMAND-DIRECTORY-NAMESTRING-AS-TEXT-STRING\?",
	    AB_package);
    Qwrite_file_command_directory_namestring_as_text_string_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-FILE-COMMAND-DIRECTORY-NAMESTRING-AS-TEXT-STRING\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_file_command_directory_namestring_as_text_string_qm_from_slot,
	    STATIC_FUNCTION(write_file_command_directory_namestring_as_text_string_qm_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qfile_command_directory_namestring_as_text_string_qm,
	    SYMBOL_FUNCTION(Qwrite_file_command_directory_namestring_as_text_string_qm_from_slot),
	    Qslot_value_writer);
    string_constant_24 = STATIC_STRING("(contents unknown~a)");
    array_constant_9 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("~d Director~a, ~d File~a");
    array_constant_10 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qdirectory_contents_statistics_qm = 
	    STATIC_SYMBOL("DIRECTORY-CONTENTS-STATISTICS\?",AB_package);
    Qwrite_directory_contents_statistics_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-DIRECTORY-CONTENTS-STATISTICS\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_directory_contents_statistics_qm_from_slot,
	    STATIC_FUNCTION(write_directory_contents_statistics_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdirectory_contents_statistics_qm,
	    SYMBOL_FUNCTION(Qwrite_directory_contents_statistics_qm_from_slot),
	    Qslot_value_writer);
    check_if_superior_classes_are_defined(Qinit_file_command,list_constant_43);
    string_constant_91 = 
	    STATIC_STRING("1l4z8r83ry83ry83Cwy83Cwy00001o1l8l1n8p83Cwy83Gy1l8o1l83-3y00000");
    string_constant_92 = 
	    STATIC_STRING("1n8q1m83Cwy1l83=ny1n83ry01n8p83Cwy83Gy");
    temp = regenerate_optimized_constant(string_constant_73);
    temp_1 = regenerate_optimized_constant(string_constant_91);
    add_class_to_environment(9,Qinit_file_command,list_constant_43,Nil,
	    temp,Nil,temp_1,list_constant_43,
	    regenerate_optimized_constant(string_constant_92),Nil);
    Qexecute_command_for_file_command = 
	    STATIC_SYMBOL("EXECUTE-COMMAND-FOR-FILE-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_command_for_file_command,
	    STATIC_FUNCTION(execute_command_for_file_command,NIL,FALSE,1,1));
    Qexecute_command = STATIC_SYMBOL("EXECUTE-COMMAND",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qexecute_command_for_file_command);
    set_get(Qfile_command,Qexecute_command,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexecute_command),
	    Qclasses_which_define);
    temp_2 = CONS(Qfile_command,temp);
    mutate_global_property(Qexecute_command,temp_2,Qclasses_which_define);
    Qexecute_command_for_init_file_command = 
	    STATIC_SYMBOL("EXECUTE-COMMAND-FOR-INIT-FILE-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_command_for_init_file_command,
	    STATIC_FUNCTION(execute_command_for_init_file_command,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qexecute_command_for_init_file_command);
    set_get(Qinit_file_command,Qexecute_command,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexecute_command),
	    Qclasses_which_define);
    temp_2 = CONS(Qinit_file_command,temp);
    mutate_global_property(Qexecute_command,temp_2,Qclasses_which_define);
    Qconvert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    string_constant_26 = 
	    STATIC_STRING("The filename ~s is too long ~\n                        to store in the file system.  Save KB as ~s\?");
    string_constant_27 = 
	    STATIC_STRING("The filename ~s contains trailing spaces.  ~\n                   G2 will be unable to locate this file.  ~\n                   Save KB as ~s instead\?");
    Qscc_update = STATIC_SYMBOL("SCC-UPDATE",AB_package);
    Qscc_edit = STATIC_SYMBOL("SCC-EDIT",AB_package);
    Qscc_unedit = STATIC_SYMBOL("SCC-UNEDIT",AB_package);
    Qscc_revert = STATIC_SYMBOL("SCC-REVERT",AB_package);
    Qscc_commit = STATIC_SYMBOL("SCC-COMMIT",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)5L,Qscc_update,Qscc_edit,
	    Qscc_unedit,Qscc_revert,Qscc_commit);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qsave_module,Qsave_module_into);
    Qsave_only_changed_modules = STATIC_SYMBOL("SAVE-ONLY-CHANGED-MODULES",
	    AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,
	    Qconnect_to_external_foreign_image,
	    Qdisconnect_from_external_foreign_image);
    Qnever_autostart = STATIC_SYMBOL("NEVER-AUTOSTART",AB_package);
    Qautostart = STATIC_SYMBOL("AUTOSTART",AB_package);
    Qdo_not_autostart = STATIC_SYMBOL("DO-NOT-AUTOSTART",AB_package);
    Qmerge_in_init_file = STATIC_SYMBOL("MERGE-IN-INIT-FILE",AB_package);
    Qload_in_init_file = STATIC_SYMBOL("LOAD-IN-INIT-FILE",AB_package);
    Qbackup = STATIC_SYMBOL("BACKUP",AB_package);
    Qkb_save_with_runtime_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTIME-DATA",
	    AB_package);
    Qruntime_data_only = STATIC_SYMBOL("RUNTIME-DATA-ONLY",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qbackup,
	    Qkb_save_with_runtime_data,Qruntime_data_only);
    string_constant_28 = STATIC_STRING("~S is not a valid file name!");
    list_constant_14 = STATIC_LIST_STAR((SI_Long)5L,Qkb_save,Qbackup,
	    Qkb_save_with_runtime_data,Qruntime_data_only,list_constant_11);
    QG2_INTERNAL_TOP_LEVEL = STATIC_SYMBOL("g2-internal-top-level",AB_package);
    string_constant_29 = 
	    STATIC_STRING("The module ~a does not exist and so cannot be saved.  ~\n                              NOTHING WAS SAVED!!");
    list_constant_15 = STATIC_CONS(Qkb_save,list_constant_13);
    string_constant_30 = STATIC_STRING("Save KB as ~s\?");
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qwarmbooting_qm = STATIC_SYMBOL("WARMBOOTING\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmbooting_qm,Warmbooting_qm);
    record_system_variable(Qwarmbooting_qm,Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qwarmbooting_with_catch_up_qm = 
	    STATIC_SYMBOL("WARMBOOTING-WITH-CATCH-UP\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmbooting_with_catch_up_qm,
	    Warmbooting_with_catch_up_qm);
    record_system_variable(Qwarmbooting_with_catch_up_qm,Qkb_load1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_stream_error_string = STATIC_SYMBOL("G2-STREAM-ERROR-STRING",
	    AB_package);
    string_constant_31 = STATIC_STRING("G2 could not find the file ~s:  ~a.");
    string_constant_32 = STATIC_STRING("G2 could not find the file ~s.");
    Qload_or_merge_kb_if_ok = STATIC_SYMBOL("LOAD-OR-MERGE-KB-IF-OK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qload_or_merge_kb_if_ok,
	    STATIC_FUNCTION(load_or_merge_kb_if_ok,NIL,TRUE,4,8));
    Qgensym_pathname_lessp = STATIC_SYMBOL("GENSYM-PATHNAME-LESSP",AB_package);
    SET_SYMBOL_FUNCTION(Qgensym_pathname_lessp,
	    STATIC_FUNCTION(gensym_pathname_lessp,NIL,FALSE,2,2));
    array_constant_13 = STATIC_ARRAY(list_constant_17,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Qgensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    string_constant_33 = STATIC_STRING("foreign image");
    string_constant_34 = STATIC_STRING("KB and KL");
    string_constant_35 = STATIC_STRING("~a Files on \"~a\"");
    Qpathnames_in_directory = STATIC_SYMBOL("PATHNAMES-IN-DIRECTORY",
	    AB_package);
    Qforeign_images = STATIC_SYMBOL("FOREIGN-IMAGES",AB_package);
    string_constant_36 = STATIC_STRING("Looking for ~a files in ~s");
    string_constant_37 = STATIC_STRING("There are no ~a files in ~s");
    string_constant_38 = STATIC_STRING("KB or KL");
    Qhandle_choice_for_directory_menu = 
	    STATIC_SYMBOL("HANDLE-CHOICE-FOR-DIRECTORY-MENU",AB_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    Qkb = STATIC_SYMBOL("KB",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qkb,Qnil);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qexternal_foreign_function_images_compute_choices = 
	    STATIC_SYMBOL("EXTERNAL-FOREIGN-FUNCTION-IMAGES-COMPUTE-CHOICES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexternal_foreign_function_images_compute_choices,
	    STATIC_FUNCTION(external_foreign_function_images_compute_choices,
	    NIL,FALSE,1,1));
    Qexternal_foreign_function_images = 
	    STATIC_SYMBOL("EXTERNAL-FOREIGN-FUNCTION-IMAGES",AB_package);
    Qcommand_menu = STATIC_SYMBOL("COMMAND-MENU",AB_package);
    string_constant_93 = STATIC_STRING("9k");
    clear_optimized_constants();
    push_optimized_constant(Qexternal_foreign_function_images_compute_choices);
    make_menu_description(Qexternal_foreign_function_images,Qnil,Qnil,Qnil,
	    Qnil,Qnil,Qt,Qnil,Qt,Nil,Nil,Qnil,Qnil,Qnil,Qcommand_menu,
	    regenerate_optimized_constant(string_constant_93));
    Qpathnames_in_directory_compute_choices = 
	    STATIC_SYMBOL("PATHNAMES-IN-DIRECTORY-COMPUTE-CHOICES",AB_package);
    SET_SYMBOL_FUNCTION(Qpathnames_in_directory_compute_choices,
	    STATIC_FUNCTION(pathnames_in_directory_compute_choices,NIL,
	    FALSE,5,5));
    clear_optimized_constants();
    push_optimized_constant(Qpathnames_in_directory_compute_choices);
    make_menu_description(Qpathnames_in_directory,Qnil,Qnil,Qnil,Qnil,Qnil,
	    Qt,Qnil,Qt,Nil,Nil,Qnil,Qnil,Qnil,Qcommand_menu,
	    regenerate_optimized_constant(string_constant_93));
    string_constant_94 = STATIC_STRING("1m1m83*Yy83-iey1n83*Yy83-TWy0");
    make_menu_description(Qforeign_images,Qnil,Qnil,Qnil,Qnil,Qnil,Qt,Qnil,
	    Qt,Nil,Nil,Qnil,Qnil,Qnil,Qcommand_menu,
	    regenerate_optimized_constant(string_constant_94));
    string_constant_39 = 
	    STATIC_STRING("disconnect from external foreign image at ");
    SET_SYMBOL_FUNCTION(Qhandle_choice_for_directory_menu,
	    STATIC_FUNCTION(handle_choice_for_directory_menu,NIL,FALSE,13,13));
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    string_constant_95 = 
	    STATIC_STRING("13Jy83*ny837Ty083=wy08308yk830Ayk8309yk8307yk832Py083=Dyk836Ky083=Nyk836Jy0");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qfile_command_info_table_format,
	    regenerate_optimized_constant(string_constant_95),
	    Qformat_description);
    Qspot_generator_for_file_command_info_table_format = 
	    STATIC_SYMBOL("SPOT-GENERATOR-FOR-FILE-COMMAND-INFO-TABLE-FORMAT",
	    AB_package);
    Qtable_format_spot_generator = 
	    STATIC_SYMBOL("TABLE-FORMAT-SPOT-GENERATOR",AB_package);
    mutate_global_property(Qfile_command_info_table_format,
	    Qspot_generator_for_file_command_info_table_format,
	    Qtable_format_spot_generator);
    SET_SYMBOL_FUNCTION(Qspot_generator_for_file_command_info_table_format,
	    STATIC_FUNCTION(spot_generator_for_file_command_info_table_format,
	    NIL,FALSE,2,2));
    string_constant_96 = 
	    STATIC_STRING("13Ny83-Qy83-By083byo83aym83Wyo83cym83kyk83-=y3Gy83ny1l83-uy83ty3Gy83sy3Cy83uyn83-7y3C+y83iy3FUy");
    mutate_global_property(Qfile_command_attribute_value_format,
	    regenerate_optimized_constant(string_constant_96),
	    Qformat_description);
    Qfile_command_small_attribute_value_format = 
	    STATIC_SYMBOL("FILE-COMMAND-SMALL-ATTRIBUTE-VALUE-FORMAT",
	    AB_package);
    string_constant_97 = 
	    STATIC_STRING("13Ny83-Qy83-By083byo83aym83Wyo83cym83kyk83-=ys83ny1l83-ry83ty3Ey83syy83uyn83-7y3C+y83iy3Bay");
    mutate_global_property(Qfile_command_small_attribute_value_format,
	    regenerate_optimized_constant(string_constant_97),
	    Qformat_description);
    Qcorresponding_small_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-SMALL-FONT-FORMAT-NAME",AB_package);
    mutate_global_property(Qfile_command_attribute_value_format,
	    Qfile_command_small_attribute_value_format,
	    Qcorresponding_small_font_format_name);
    Qfile_command_extra_large_attribute_value_format = 
	    STATIC_SYMBOL("FILE-COMMAND-EXTRA-LARGE-ATTRIBUTE-VALUE-FORMAT",
	    AB_package);
    string_constant_98 = 
	    STATIC_STRING("13Ry83-Qy83-By083byp83aym83Wyp83cym83kyk83-=yy83ny1l8311y83ty3My83sy3Hy83uyn83-7y3V+y83*3y3O+y83*+y3-G+y83iy3JOy");
    mutate_global_property(Qfile_command_extra_large_attribute_value_format,
	    regenerate_optimized_constant(string_constant_98),
	    Qformat_description);
    Qcorresponding_extra_large_font_format_name = 
	    STATIC_SYMBOL("CORRESPONDING-EXTRA-LARGE-FONT-FORMAT-NAME",
	    AB_package);
    mutate_global_property(Qfile_command_attribute_value_format,
	    Qfile_command_extra_large_attribute_value_format,
	    Qcorresponding_extra_large_font_format_name);
    string_constant_40 = STATIC_STRING("Loading ~a file \"~a\"");
    string_constant_41 = STATIC_STRING("Done loading ~a file \"~a\".");
    string_constant_42 = STATIC_STRING("~s does not exist.");
    if (System_statistics_writers == UNBOUND)
	System_statistics_writers = Nil;
    string_constant_43 = STATIC_STRING("Writing G2 statistics file ~a ...");
    string_constant_44 = STATIC_STRING("G2 statistics file completed.");
    string_constant_45 = 
	    STATIC_STRING("Unable to open G2 statistics file ~s, ~a.");
    SET_SYMBOL_FUNCTION(Qwrite_g2_stats,STATIC_FUNCTION(write_g2_stats,NIL,
	    FALSE,1,1));
    Qg2_write_stats = STATIC_SYMBOL("G2-WRITE-STATS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_write_stats,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_write_stats,STATIC_FUNCTION(g2_write_stats,NIL,
	    FALSE,1,1));
    if (Kb_flags == UNBOUND)
	Kb_flags = FIX((SI_Long)282L);
    if (Kb_flags_for_saving == UNBOUND)
	Kb_flags_for_saving = FIX((SI_Long)282L);
    Kb_flags_of_software = Kb_flags;
    Qkb_format_revision_for_kb_restrictions_reclassification = 
	    STATIC_SYMBOL("KB-FORMAT-REVISION-FOR-KB-RESTRICTIONS-RECLASSIFICATION",
	    AB_package);
    SET_SYMBOL_VALUE(Qkb_format_revision_for_kb_restrictions_reclassification,
	    FIX((SI_Long)243L));
    Qkb_flag_when_specific_procedure_method_died = 
	    STATIC_SYMBOL("KB-FLAG-WHEN-SPECIFIC-PROCEDURE-METHOD-DIED",
	    AB_package);
    SET_SYMBOL_VALUE(Qkb_flag_when_specific_procedure_method_died,
	    FIX((SI_Long)245L));
    Qg2_version_6_general_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-6-GENERAL-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_6_general_kb_flags,FIX((SI_Long)270L));
    Qlast_kb_flags_saved_with_item_reference_parameters = 
	    STATIC_SYMBOL("LAST-KB-FLAGS-SAVED-WITH-ITEM-REFERENCE-PARAMETERS",
	    AB_package);
    SET_SYMBOL_VALUE(Qlast_kb_flags_saved_with_item_reference_parameters,
	    FIX((SI_Long)272L));
    Qg2_version_7_beta_0_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-7-BETA-0-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_7_beta_0_kb_flags,FIX((SI_Long)274L));
    Qg2_version_8_beta_0_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-8-BETA-0-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_8_beta_0_kb_flags,FIX((SI_Long)275L));
    Qg2_version_8_1_alpha_0_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-8-1-ALPHA-0-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_8_1_alpha_0_kb_flags,FIX((SI_Long)276L));
    Qg2_version_8_1_beta_0_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-8-1-BETA-0-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_8_1_beta_0_kb_flags,FIX((SI_Long)277L));
    Qg2_version_81r0_kb_flags = STATIC_SYMBOL("G2-VERSION-81R0-KB-FLAGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_version_81r0_kb_flags,FIX((SI_Long)278L));
    Qg2_version_82r0_kb_flags = STATIC_SYMBOL("G2-VERSION-82R0-KB-FLAGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_version_82r0_kb_flags,FIX((SI_Long)279L));
    Qg2_version_8_3_alpha_0_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-8-3-ALPHA-0-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_8_3_alpha_0_kb_flags,FIX((SI_Long)280L));
    Qg2_version_2011_kb_flags = STATIC_SYMBOL("G2-VERSION-2011-KB-FLAGS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_version_2011_kb_flags,FIX((SI_Long)281L));
    Qg2_version_2015_beta_kb_flags = 
	    STATIC_SYMBOL("G2-VERSION-2015-BETA-KB-FLAGS",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_2015_beta_kb_flags,FIX((SI_Long)282L));
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
}
