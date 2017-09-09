/* expln.c
 * Input file:  explain.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "expln.h"


Object The_type_description_of_backward_chaining_display = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_backward_chaining_displays, Qchain_of_available_backward_chaining_displays);

DEFINE_VARIABLE_WITH_SYMBOL(Backward_chaining_display_count, Qbackward_chaining_display_count);

Object Chain_of_available_backward_chaining_displays_vector = UNBOUND;

/* BACKWARD-CHAINING-DISPLAY-STRUCTURE-MEMORY-USAGE */
Object backward_chaining_display_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(169,0);
    temp = Backward_chaining_display_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BACKWARD-CHAINING-DISPLAY-COUNT */
Object outstanding_backward_chaining_display_count()
{
    Object def_structure_backward_chaining_display_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(169,1);
    gensymed_symbol = IFIX(Backward_chaining_display_count);
    def_structure_backward_chaining_display_variable = 
	    Chain_of_available_backward_chaining_displays;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_backward_chaining_display_variable))
	goto end_loop;
    def_structure_backward_chaining_display_variable = 
	    ISVREF(def_structure_backward_chaining_display_variable,
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

/* RECLAIM-BACKWARD-CHAINING-DISPLAY-1 */
Object reclaim_backward_chaining_display_1(backward_chaining_display)
    Object backward_chaining_display;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(169,2);
    inline_note_reclaim_cons(backward_chaining_display,Nil);
    structure_being_reclaimed = backward_chaining_display;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_graph_display_1(ISVREF(backward_chaining_display,(SI_Long)2L));
      SVREF(backward_chaining_display,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_backward_chaining_displays_vector,
	    IFIX(Current_thread_index));
    SVREF(backward_chaining_display,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_backward_chaining_displays_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = backward_chaining_display;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BACKWARD-CHAINING-DISPLAY */
Object reclaim_structure_for_backward_chaining_display(backward_chaining_display)
    Object backward_chaining_display;
{
    x_note_fn_call(169,3);
    return reclaim_backward_chaining_display_1(backward_chaining_display);
}

static Object Qg2_defstruct_structure_name_backward_chaining_display_g2_struct;  /* g2-defstruct-structure-name::backward-chaining-display-g2-struct */

/* MAKE-PERMANENT-BACKWARD-CHAINING-DISPLAY-STRUCTURE-INTERNAL */
Object make_permanent_backward_chaining_display_structure_internal()
{
    Object def_structure_backward_chaining_display_variable;
    Object defstruct_g2_backward_chaining_display_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(169,4);
    def_structure_backward_chaining_display_variable = Nil;
    atomic_incff_symval(Qbackward_chaining_display_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_backward_chaining_display_variable = Nil;
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
	defstruct_g2_backward_chaining_display_variable = the_array;
	SVREF(defstruct_g2_backward_chaining_display_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_backward_chaining_display_g2_struct;
	SVREF(defstruct_g2_backward_chaining_display_variable,
		FIX((SI_Long)1L)) = Nil;
	def_structure_backward_chaining_display_variable = 
		defstruct_g2_backward_chaining_display_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_backward_chaining_display_variable);
}

/* MAKE-RAW-BACKWARD-CHAINING-DISPLAY-1 */
Object make_raw_backward_chaining_display_1(backward_chaining_graph_display)
    Object backward_chaining_graph_display;
{
    Object def_structure_backward_chaining_display_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(169,5);
    def_structure_backward_chaining_display_variable = 
	    ISVREF(Chain_of_available_backward_chaining_displays_vector,
	    IFIX(Current_thread_index));
    if (def_structure_backward_chaining_display_variable) {
	svref_arg_1 = Chain_of_available_backward_chaining_displays_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_backward_chaining_display_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_backward_chaining_display_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_backward_chaining_display_g2_struct;
    }
    else
	def_structure_backward_chaining_display_variable = 
		make_permanent_backward_chaining_display_structure_internal();
    inline_note_allocate_cons(def_structure_backward_chaining_display_variable,
	    Nil);
    SVREF(def_structure_backward_chaining_display_variable,
	    FIX((SI_Long)2L)) = backward_chaining_graph_display;
    SVREF(def_structure_backward_chaining_display_variable,
	    FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_backward_chaining_display_variable);
}

static Object Qbackward_chaining_display_hash;  /* backward-chaining-display-hash */

static Object Qsxhashw;            /* sxhashw */

static Object Qvertical;           /* vertical */

static Object Qdynamic_temporary_workspace;  /* dynamic-temporary-workspace */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qbackward_chaining_display_children;  /* backward-chaining-display-children */

static Object Qbackward_chaining_display_short_rep;  /* backward-chaining-display-short-rep */

static Object Qremove_backward_chaining_display;  /* remove-backward-chaining-display */

/* MAKE-BACKWARD-CHAINING-DISPLAY */
Object make_backward_chaining_display(variable)
    Object variable;
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, graph_display;
    Object dynamic_workspace, display;

    x_note_fn_call(169,6);
    temp = IDENTITY(Qbackward_chaining_display_hash);
    if (temp);
    else
	temp = Qsxhashw;
    temp_1 = IDENTITY(Nil);
    if (temp_1);
    else
	temp_1 = Qvertical;
    temp_2 = IDENTITY(Nil);
    if (temp_2);
    else
	temp_2 = FIX((SI_Long)50L);
    temp_3 = IDENTITY(Nil);
    if (temp_3);
    else
	temp_3 = FIX((SI_Long)50L);
    temp_4 = Current_workstation_detail_pane;
    temp_5 = IDENTITY(Qdynamic_temporary_workspace);
    if (temp_5);
    else
	temp_5 = Qtemporary_workspace;
    graph_display = graph_frame_hierarchy_function(variable,
	    Qbackward_chaining_display_children,Nil,
	    Qbackward_chaining_display_short_rep,temp,temp_1,temp_2,temp_3,
	    temp_4,temp_5,Nil,Nil,Nil);
    dynamic_workspace = ISVREF(graph_display,(SI_Long)20L);
    display = make_raw_backward_chaining_display_1(graph_display);
    SVREF(display,FIX((SI_Long)1L)) = Qremove_backward_chaining_display;
    ISVREF(dynamic_workspace,(SI_Long)28L) = display;
    Backward_chaining_displays = gensym_cons_1(display,
	    Backward_chaining_displays);
    return VALUES_1(T);
}

/* BACKWARD-CHAINING-DISPLAYS-OF-VARIABLE */
Object backward_chaining_displays_of_variable(variable)
    Object variable;
{
    Object display, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(169,7);
    display = Nil;
    ab_loop_list_ = Backward_chaining_displays;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    display = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(variable,ISVREF(ISVREF(display,(SI_Long)2L),(SI_Long)2L))) {
	ab_loopvar__2 = eval_cons_1(display,Nil);
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

/* DELETE-BACKWARD-CHAINING-DISPLAY-IF-ANY-FOR-VARIABLE */
Object delete_backward_chaining_display_if_any_for_variable(variable)
    Object variable;
{
    Object displays_to_delete, display, ab_loop_list_;

    x_note_fn_call(169,8);
    displays_to_delete = backward_chaining_displays_of_variable(variable);
    if (displays_to_delete) {
	display = Nil;
	ab_loop_list_ = displays_to_delete;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_backward_chaining_display(display);
	goto next_loop;
      end_loop:;
	return reclaim_eval_list_1(displays_to_delete);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-BACKWARD-CHAINING-DISPLAY */
Object delete_backward_chaining_display(backward_chaining_display)
    Object backward_chaining_display;
{
    x_note_fn_call(169,9);
    return delete_frame(ISVREF(ISVREF(backward_chaining_display,
	    (SI_Long)2L),(SI_Long)20L));
}

/* REMOVE-BACKWARD-CHAINING-DISPLAY */
Object remove_backward_chaining_display(backward_chaining_display)
    Object backward_chaining_display;
{
    x_note_fn_call(169,10);
    Backward_chaining_displays = 
	    delete_gensym_element_1(backward_chaining_display,
	    Backward_chaining_displays);
    return reclaim_backward_chaining_display_1(backward_chaining_display);
}

static Object Qdynamic_display_delay_in_milliseconds;  /* dynamic-display-delay-in-milliseconds */

/* UPDATE-BACKWARD-CHAINING-DISPLAYS-FUNCTION */
Object update_backward_chaining_displays_function(thing)
    Object thing;
{
    Object bcd, ab_loop_list_;

    x_note_fn_call(169,11);
    bcd = Nil;
    ab_loop_list_ = Backward_chaining_displays;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    bcd = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (represented_in_graph_display_p(thing,ISVREF(bcd,(SI_Long)2L))) {
	if (update_graph_display(ISVREF(bcd,(SI_Long)2L)) && 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qdynamic_display_delay_in_milliseconds,FIX((SI_Long)200L))) {
	    force_process_drawing();
	    g2ext_sys_sleep(IFIX(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qdynamic_display_delay_in_milliseconds,
		    FIX((SI_Long)200L))));
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

/* BACKWARD-CHAINING-DISPLAY-CHILDREN */
Object backward_chaining_display_children(thing,ignored)
    Object thing, ignored;
{
    Object kid, ab_loop_list_, collected_kids, ab_loopvar_, ab_loopvar__1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(169,12);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	kid = Nil;
	ab_loop_list_ = ISVREF(thing,(SI_Long)17L);
	collected_kids = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	kid = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(kid,collected_kids))) {
	    ab_loopvar__1 = gensym_cons_1(kid,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		collected_kids = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(collected_kids);
	return VALUES_1(Qnil);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    kid = Nil;
	    ab_loop_list_ = ISVREF(thing,(SI_Long)35L);
	    collected_kids = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    kid = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(kid,collected_kids))) {
		ab_loopvar__1 = gensym_cons_1(kid,Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    collected_kids = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(collected_kids);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qvar_spot;           /* var-spot */

static Object Kgeneral_description;  /* :general-description */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object array_constant;      /* # */

static Object string_constant;     /* "~NF" */

static Object array_constant_1;    /* # */

/* BACKWARD-CHAINING-DISPLAY-SHORT-REP */
Object backward_chaining_display_short_rep(thing)
    Object thing;
{
    Object context, rule, frame_serial_number, var_spot;
    Object environment_description, value, variable_name, variable_description;
    Object binding_description, ab_loopvar_, ab_loopvar__1, gensymed_symbol_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, x2, xa, ya, temp_2, sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, ab_loop_repeat_, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(169,13);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	if ( !TRUEP(ISVREF(thing,(SI_Long)10L)) ||  !TRUEP(ISVREF(thing,
		(SI_Long)2L)))
	    return make_explanation_table(2,ISVREF(thing,(SI_Long)8L),Nil);
	else {
	    context = ISVREF(thing,(SI_Long)2L);
	    rule = ISVREF(thing,(SI_Long)8L);
	    frame_serial_number = ISVREF(thing,(SI_Long)11L);
	    var_spot = proc_list_2(Qvar_spot,FIX((SI_Long)0L));
	    environment_description = ISVREF(ISVREF(rule,(SI_Long)31L),
		    (SI_Long)4L);
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(rule,(SI_Long)33L));
	    ab_loop_repeat_ = IFIX(var_count(environment_description));
	    value = Nil;
	    variable_name = Nil;
	    variable_description = Nil;
	    binding_description = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    value = ISVREF(context,index_1);
	    gensymed_symbol = index_1 * (SI_Long)2L;
	    variable_name = FIXNUM_LE(ISVREF(environment_description,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(environment_description,gensymed_symbol + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(environment_description,(gensymed_symbol 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol 
		    & (SI_Long)1023L);
	    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(environment_description,gensymed_symbol + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(environment_description,(gensymed_symbol 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol 
		    & (SI_Long)1023L);
	    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		    Kgeneral_description)) {
		gensymed_symbol_1 = CDR(gensymed_symbol_1);
		variable_description = gensymed_symbol_1;
	    }
	    else
		variable_description = Nil;
	    M_SECOND(var_spot) = FIX(index_1);
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
		      print_var_spot_for_stack_using_name_and_description(3,
			      var_spot,variable_name,variable_description);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      if (SIMPLE_VECTOR_P(value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(value,(SI_Long)1L);
			  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1) {
			  if (frame_serial_number) {
			      gensymed_symbol_1 = ISVREF(value,(SI_Long)3L);
			      temp_1 = SIMPLE_VECTOR_P(value) ? 
				      EQ(ISVREF(value,(SI_Long)1L),
				      Qavailable_frame_vector) : TRUEP(Qnil);
			      if (temp_1);
			      else
				  temp_1 = FIXNUMP(gensymed_symbol_1) ? 
					  IFIX(gensymed_symbol_1) == 
					  (SI_Long)-1L : TRUEP(Nil);
			      if (temp_1);
			      else if (FIXNUMP(frame_serial_number))
				  temp_1 = FIXNUMP(gensymed_symbol_1) ? 
					  FIXNUM_LT(frame_serial_number,
					  gensymed_symbol_1) : TRUEP(T);
			      else if (FIXNUMP(gensymed_symbol_1))
				  temp_1 = TRUEP(Nil);
			      else {
				  xa = M_CAR(frame_serial_number);
				  ya = M_CAR(gensymed_symbol_1);
				  temp_1 = FIXNUM_LT(xa,ya);
				  if (temp_1);
				  else
				      temp_1 = FIXNUM_EQ(xa,ya) ? 
					      FIXNUM_LT(M_CDR(frame_serial_number),
					      M_CDR(gensymed_symbol_1)) : 
					      TRUEP(Qnil);
			      }
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1)
			      copy_constant_wide_string_given_length(array_constant,
				      FIX((SI_Long)10L));
			  else
			      tformat(2,string_constant,value);
		      }
		      else
			  write_stored_value(value);
		      temp_2 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    ab_loopvar__1 = slot_value_cons_1(slot_value_list_2(temp,
		    temp_2),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		binding_description = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    reclaim_proc_list_1(var_spot);
	    return make_explanation_table(2,rule,binding_description);
	    return VALUES_1(Qnil);
	}
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return make_explanation_table(1,thing);
	else
	    return make_explanation_table(2,Nil,
		    slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_1,
		    FIX((SI_Long)12L)),Nil));
    }
}

/* BACKWARD-CHAINING-DISPLAY-HASH */
Object backward_chaining_display_hash(thing)
    Object thing;
{
    Object sub_class_bit_vector, fsn;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(169,14);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))
	return VALUES_1(ISVREF(thing,(SI_Long)22L));
    else {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    fsn = ISVREF(thing,(SI_Long)3L);
	    if (FIXNUMP(fsn))
		return VALUES_1(fsn);
	    else
		return VALUES_1(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
	}
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
}

static Object Qlarge;              /* large */

static Object Qinverted;           /* inverted */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* MAKE-STATIC-CHAINING-DISPLAY */
Object make_static_chaining_display(variable)
    Object variable;
{
    Object forward_chaining, backward_chaining, variable_short_rep, workspace;
    Object gensymed_symbol, total_width, block, ab_loop_list_;
    SI_Long spacing, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long y, x, gensymed_symbol_4;

    x_note_fn_call(169,15);
    spacing = (SI_Long)30L;
    forward_chaining = describe_forward_chaining_short_reps(variable);
    backward_chaining = describe_backward_chaining_short_reps(variable);
    variable_short_rep = make_short_representation(3,variable,Nil,Qlarge);
    workspace = make_workspace(1,Qtemporary_workspace);
    gensymed_symbol = ISVREF(variable_short_rep,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(variable_short_rep,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    add_to_workspace(6,variable_short_rep,workspace,FIX( - 
	    gensymed_symbol_1),FIX((SI_Long)0L),Nil,Nil);
    if (forward_chaining) {
	total_width = static_display_total_width(forward_chaining,
		FIX(spacing));
	gensymed_symbol = ISVREF(variable_short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = spacing;
	gensymed_symbol_3 = 
		IFIX(static_display_maximum_height(forward_chaining));
	y = gensymed_symbol_1 - gensymed_symbol_2 - gensymed_symbol_3;
	x =  - (IFIX(total_width) >>  -  - (SI_Long)1L);
	block = Nil;
	ab_loop_list_ = forward_chaining;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_to_workspace(6,block,workspace,FIX(x),FIX(y),Nil,Nil);
	gensymed_symbol_1 = x;
	gensymed_symbol_2 = spacing;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	x = gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3;
	goto next_loop;
      end_loop:;
	connect_superior_and_kid_frames(variable_short_rep,Qinverted,
		forward_chaining,workspace,FIX(spacing),FIX(spacing));
	reclaim_eval_list_1(forward_chaining);
    }
    if (backward_chaining) {
	total_width = static_display_total_width(backward_chaining,
		FIX(spacing));
	gensymed_symbol = ISVREF(variable_short_rep,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = spacing;
	y = gensymed_symbol_1 + gensymed_symbol_2;
	x =  - (IFIX(total_width) >>  -  - (SI_Long)1L);
	block = Nil;
	ab_loop_list_ = backward_chaining;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_to_workspace(6,block,workspace,FIX(x),FIX(y),Nil,Nil);
	gensymed_symbol_1 = x;
	gensymed_symbol_2 = spacing;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	x = gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3;
	goto next_loop_1;
      end_loop_1:;
	connect_superior_and_kid_frames(variable_short_rep,Qvertical,
		backward_chaining,workspace,FIX(spacing),FIX(spacing));
	reclaim_eval_list_1(backward_chaining);
    }
    put_workspace_on_pane_function(workspace,
	    Current_workstation_detail_pane,Qleft,Qtop,T,FIX((SI_Long)11L),
	    Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

/* STATIC-DISPLAY-TOTAL-WIDTH */
Object static_display_total_width(frames,spacing)
    Object frames, spacing;
{
    Object block, ab_loop_list_, ab_loopvar_, gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(169,16);
    gensymed_symbol = IFIX(FIXNUM_TIMES(spacing,FIXNUM_SUB1(length(frames))));
    block = Nil;
    ab_loop_list_ = frames;
    ab_loopvar_ = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
    ab_loopvar_ = add(FIX(gensymed_symbol_2 - gensymed_symbol_3),ab_loopvar_);
    goto next_loop;
  end_loop:
    gensymed_symbol_2 = IFIX(ab_loopvar_);
    goto end_1;
    gensymed_symbol_2 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_2));
}

/* STATIC-DISPLAY-MAXIMUM-HEIGHT */
Object static_display_maximum_height(frames)
    Object frames;
{
    Object block, ab_loop_list_, gensymed_symbol_1;
    SI_Long max_1, gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(169,17);
    max_1 = (SI_Long)0L;
    block = Nil;
    ab_loop_list_ = frames;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = max_1;
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    gensymed_symbol_1 = ISVREF(block,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    max_1 = MAX(gensymed_symbol,gensymed_symbol_2);
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(max_1));
    return VALUES_1(Qnil);
}

static Object Qsmall;              /* small */

/* DESCRIBE-FORWARD-CHAINING-SHORT-REPS */
Object describe_forward_chaining_short_reps(variable)
    Object variable;
{
    Object forward_chaining_rules_to_show, forward_chaining_rules, frame;
    Object ab_loop_list_, eval_cons, car_new_value;
    Object result;

    x_note_fn_call(169,18);
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L)) {
	result = collect_all_rules_for_forward_chaining(variable);
	MVS_2(result,forward_chaining_rules_to_show,forward_chaining_rules);
	frame = Nil;
	ab_loop_list_ = forward_chaining_rules_to_show;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_frame(frame);
	goto next_loop;
      end_loop:;
	reclaim_eval_list_1(forward_chaining_rules_to_show);
	eval_cons = forward_chaining_rules;
      next_loop_1:
	if ( !TRUEP(eval_cons))
	    goto end_loop_1;
	car_new_value = make_short_representation(3,CAR(eval_cons),Nil,Qsmall);
	M_CAR(eval_cons) = car_new_value;
	eval_cons = M_CDR(eval_cons);
	goto next_loop_1;
      end_loop_1:;
	return VALUES_1(forward_chaining_rules);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcomputation;        /* computation */

static Object list_constant;       /* # */

/* DESCRIBE-BACKWARD-CHAINING-SHORT-REPS */
Object describe_backward_chaining_short_reps(variable)
    Object variable;
{
    Object source_or_map, server_qm, frames_to_show, temp_1;
    Object specific_formula_qm, generic_formulas, data_type, links_and_objects;
    Object backward_chaining_link_and_objects, entry, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    char temp;
    Declare_special(1);

    x_note_fn_call(169,19);
    temp = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)16L);
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & 
		(SI_Long)32768L);
    if (temp);
    else {
	source_or_map = ISVREF(variable,(SI_Long)31L);
	server_qm = ATOM(source_or_map) ? 
		lookup_kb_specific_property_value(source_or_map,
		Data_server_or_alias_qm_kbprop) : Nil;
	temp =  !EQ(server_qm ? server_qm : 
		warn_of_undefined_data_server(variable,source_or_map),
		Qcomputation);
    }
    if ( !temp) {
	frames_to_show = Nil;
	temp_1 = ISVREF(variable,(SI_Long)28L);
	specific_formula_qm = CAR(temp_1);
	generic_formulas =  !TRUEP(specific_formula_qm) ? 
		collect_generic_formulas_for_variable(variable) : Nil;
	data_type = 
		type_specification_of_variable_or_parameter_value(variable);
	if ( !(specific_formula_qm || generic_formulas)) {
	    links_and_objects = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
		    0);
	      collect_rules_for_backward_chaining(variable,data_type);
	      backward_chaining_link_and_objects = Links_and_objects;
	    POP_SPECIAL();
	}
	else
	    backward_chaining_link_and_objects = Nil;
	if (specific_formula_qm)
	    frames_to_show = eval_cons_1(make_attributes_table(6,variable,
		    Nil,Nil,Nil,Nil,list_constant),Nil);
	else if (generic_formulas)
	    frames_to_show = eval_cons_1(make_short_representation(3,
		    CAR(generic_formulas),Nil,Qsmall),Nil);
	else if (backward_chaining_link_and_objects) {
	    entry = Nil;
	    ab_loop_list_ = backward_chaining_link_and_objects;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    entry = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = eval_cons_1(make_short_representation(3,
		    ISVREF(CAR(entry),(SI_Long)2L),Nil,Qsmall),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    frames_to_show = ab_loopvar_;
	    goto end_1;
	    frames_to_show = Qnil;
	  end_1:;
	}
	reclaim_eval_list_1(generic_formulas);
	reclaim_eval_tree_1(backward_chaining_link_and_objects);
	return VALUES_1(frames_to_show);
    }
    else
	return VALUES_1(Nil);
}

void explain_INIT()
{
    Object temp, reclaim_structure_for_backward_chaining_display_1;
    Object Qformula_qm, Qab_class, AB_package, list_constant_1;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qbackward_chaining_display;
    Object Qreclaim_structure, Qoutstanding_backward_chaining_display_count;
    Object Qbackward_chaining_display_structure_memory_usage, Qutilities2;
    Object string_constant_2, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_1, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qexplain;

    x_note_fn_call(169,20);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qbackward_chaining_displays = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackward_chaining_displays,
	    Backward_chaining_displays);
    Qexplain = STATIC_SYMBOL("EXPLAIN",AB_package);
    record_system_variable(Qbackward_chaining_displays,Qexplain,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_backward_chaining_display_g2_struct = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qbackward_chaining_display = STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_backward_chaining_display_g2_struct,
	    Qbackward_chaining_display,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qbackward_chaining_display,
	    Qg2_defstruct_structure_name_backward_chaining_display_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_backward_chaining_display == UNBOUND)
	The_type_description_of_backward_chaining_display = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8m83fJy1o83fJy836my8n8k1l836my0000001m1m8x836my1n8y83-5Gy1l83qIyknk0k0");
    temp = The_type_description_of_backward_chaining_display;
    The_type_description_of_backward_chaining_display = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_1));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_backward_chaining_display_g2_struct,
	    The_type_description_of_backward_chaining_display,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qbackward_chaining_display,
	    The_type_description_of_backward_chaining_display,
	    Qtype_description_of_type);
    Qoutstanding_backward_chaining_display_count = 
	    STATIC_SYMBOL("OUTSTANDING-BACKWARD-CHAINING-DISPLAY-COUNT",
	    AB_package);
    Qbackward_chaining_display_structure_memory_usage = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_2 = STATIC_STRING("1q83fJy8s83-KXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_backward_chaining_display_count);
    push_optimized_constant(Qbackward_chaining_display_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    Qchain_of_available_backward_chaining_displays = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BACKWARD-CHAINING-DISPLAYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_backward_chaining_displays,
	    Chain_of_available_backward_chaining_displays);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_backward_chaining_displays,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbackward_chaining_display_count = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbackward_chaining_display_count,
	    Backward_chaining_display_count);
    record_system_variable(Qbackward_chaining_display_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_backward_chaining_displays_vector == UNBOUND)
	Chain_of_available_backward_chaining_displays_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbackward_chaining_display_structure_memory_usage,
	    STATIC_FUNCTION(backward_chaining_display_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_backward_chaining_display_count,
	    STATIC_FUNCTION(outstanding_backward_chaining_display_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_backward_chaining_display_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_backward_chaining_display,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qbackward_chaining_display,
	    reclaim_structure_for_backward_chaining_display_1);
    Qbackward_chaining_display_hash = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-HASH",AB_package);
    Qsxhashw = STATIC_SYMBOL("SXHASHW",AB_package);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Qdynamic_temporary_workspace = 
	    STATIC_SYMBOL("DYNAMIC-TEMPORARY-WORKSPACE",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qbackward_chaining_display_children = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-CHILDREN",AB_package);
    Qbackward_chaining_display_short_rep = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-DISPLAY-SHORT-REP",AB_package);
    Qremove_backward_chaining_display = 
	    STATIC_SYMBOL("REMOVE-BACKWARD-CHAINING-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_backward_chaining_display,
	    STATIC_FUNCTION(remove_backward_chaining_display,NIL,FALSE,1,1));
    Qdynamic_display_delay_in_milliseconds = 
	    STATIC_SYMBOL("DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS",AB_package);
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qbackward_chaining_display_children,
	    STATIC_FUNCTION(backward_chaining_display_children,NIL,FALSE,2,2));
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    string_constant = STATIC_STRING("~NF");
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qbackward_chaining_display_short_rep,
	    STATIC_FUNCTION(backward_chaining_display_short_rep,NIL,FALSE,
	    1,1));
    SET_SYMBOL_FUNCTION(Qbackward_chaining_display_hash,
	    STATIC_FUNCTION(backward_chaining_display_hash,NIL,FALSE,1,1));
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qinverted = STATIC_SYMBOL("INVERTED",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qformula_qm = STATIC_SYMBOL("FORMULA\?",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qab_class,Qformula_qm);
}
