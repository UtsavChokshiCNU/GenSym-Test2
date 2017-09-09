/* frms2b.c
 * Input file:  frames2b.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms2b.h"


/* INITIAL-CLASS */
Object initial_class(class_1)
    Object class_1;
{
    x_note_fn_call(84,0);
    return VALUES_1(class_1);
}

/* GET-CLASS */
Object get_class(item)
    Object item;
{
    Object temp;

    x_note_fn_call(84,1);
    temp = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    return VALUES_1(temp);
}

static Object Qfoundation_class;   /* foundation-class */

/* INITIAL-FOUNDATION-CLASS */
Object initial_foundation_class(class_1)
    Object class_1;
{
    Object class_description_qm, temp;

    x_note_fn_call(84,2);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description_qm) {
	temp = assq_function(Qfoundation_class,ISVREF(class_description_qm,
		(SI_Long)12L));
	temp = SECOND(temp);
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = class_1;
    return VALUES_1(temp);
}

/* GET-FOUNDATION-CLASS */
Object get_foundation_class(item)
    Object item;
{
    Object class_description, temp;

    x_note_fn_call(84,3);
    class_description = ISVREF(item,(SI_Long)1L);
    temp = assq_function(Qfoundation_class,ISVREF(class_description,
	    (SI_Long)12L));
    return VALUES_1(SECOND(temp));
}

static Object Qinvocation_locking_this_object;  /* invocation-locking-this-object */

/* RECLAIM-INVOCATION-LOCKING-THIS-OBJECT-VALUE */
Object reclaim_invocation_locking_this_object_value(invocation,entity)
    Object invocation, entity;
{
    x_note_fn_call(84,4);
    set_non_savable_lookup_slot_value(entity,
	    Qinvocation_locking_this_object,Nil);
    release_lock(invocation);
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qcm;                 /* \, */

/* NAME-OR-NAMES-EVALUATION-SETTER */
Object name_or_names_evaluation_setter(new_names,frame,slot_description,
	    gensymed_symbol)
    Object new_names, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, length_1;
    Object held_vector, name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, names;
    SI_Long next_index, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(84,5);
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
			  !TRUEP(type_specification_type_p__with_explanation(new_names,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(new_names,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_name_or_names_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (CONSP(new_names) && EQ(M_CDR(new_names),Qsequence)) {
	length_1 = FIXNUM_SUB1(ISVREF(M_CAR(new_names),(SI_Long)1L));
	if (IFIX(length_1) == (SI_Long)1L)
	    result = evaluation_sequence_aref(new_names,FIX((SI_Long)0L));
	else if (IFIX(length_1) > (SI_Long)0L) {
	    gensymed_symbol = new_names;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    name = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    name = validated_elt;
	    ab_loopvar__2 = phrase_cons(name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    names = ab_loopvar_;
	    goto end_1;
	    names = Qnil;
	  end_1:;
	    names = phrase_cons(Qcm,names);
	    result = VALUES_1(names);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(new_names);
  end_name_or_names_evaluation_setter:
    return result;
}

/* NAME-OR-NAMES-EVALUATION-GETTER */
Object name_or_names_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(84,6);
    GENSYM_RETURN_ONE(CONSP(slot_value) ? 
	    allocate_evaluation_sequence(copy_list_using_eval_conses_1(slot_value)) 
	    : slot_value);
    return VALUES_1(Nil);
}

/* BLOCK-P-FUNCTION */
Object block_p_function(x)
    Object x;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(84,7);
    sub_class_bit_vector = ISVREF(ISVREF(x,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* FRAMEP-FUNCTION */
Object framep_function(x)
    Object x;
{
    Object x2;

    x_note_fn_call(84,8);
    if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(x,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct))
	    return VALUES_1(x2);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* IS-BLOCK-P */
Object is_block_p(thing)
    Object thing;
{
    Object x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(84,9);
    if (thing) {
	if (SIMPLE_VECTOR_P(thing) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L &&  
		!EQ(ISVREF(thing,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing,(SI_Long)1L);
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
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qincomplete;         /* incomplete */

static Object Qcell_array;         /* cell-array */

/* PUT-CELL-ARRAY */
Object put_cell_array(block,new_cell_array_qm,initializing_qm)
    Object block, new_cell_array_qm, initializing_qm;
{
    Object current_block_of_dependent_frame, remove_compilations_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(84,10);
    current_block_of_dependent_frame = block;
    remove_compilations_qm = initializing_qm && Loading_kb_p ? ( 
	    !TRUEP(compilations_up_to_date_p(block)) ? T : Nil) : Qnil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if (remove_compilations_qm) {
	  update_frame_status(block,Qincomplete,initializing_qm);
	  if (new_cell_array_qm)
	      remove_compilations_from_obsolete_cell_array(new_cell_array_qm);
	  note_frame_with_compilation_removed(block);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(block,Qcell_array);
      set_lookup_slot_value_1(block,Qcell_array,new_cell_array_qm);
      if (new_cell_array_qm)
	  rebuild_backpointers_of_g2_cell_array(block,new_cell_array_qm);
      result = VALUES_1(new_cell_array_qm);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-CELL-ARRAY-VALUE */
Object reclaim_cell_array_value(cell_array,parent_frame)
    Object cell_array, parent_frame;
{
    x_note_fn_call(84,11);
    if (cell_array)
	delete_frame(cell_array);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(parent_frame,Qcell_array);
    set_lookup_slot_value_1(parent_frame,Qcell_array,Nil);
    return VALUES_1(Nil);
}

void frames2b_INIT()
{
    Object temp, temp_1, temp_2, name_or_names_evaluation_setter_1;
    Object name_or_names_evaluation_getter_1;
    Object Qslot_value_reclaimer, Qreclaim_cell_array_value, AB_package;
    Object Qslot_putter, Qput_cell_array, Qoptions, Qframe_flags;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qitem_configuration;
    Object Qobject_configuration, Qname_or_names, Qnamed, list_constant_9;
    Object list_constant_8, Qab_or, list_constant_6, list_constant_7;
    Object Qtype_specification_simple_expansion, list_constant_5, Qno_item;
    Object Qreclaim_invocation_locking_this_object_value, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, list_constant_4, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant, Qsystem_item, Qkb_frame;
    Object Qget_foundation_class, Qinitial_foundation_class, list_constant_3;
    Object Qvirtual_attributes_local_to_class, Qroot, Qget_class;
    Object Qinitial_class, Qab_class, list_constant_2, string_constant_2;
    Object string_constant_1;

    x_note_fn_call(84,12);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    list_constant_2 = STATIC_CONS(Qroot,Qnil);
    check_if_superior_classes_are_defined(Qkb_frame,list_constant_2);
    string_constant = STATIC_STRING("1l1l8t");
    string_constant_1 = STATIC_STRING("0");
    string_constant_2 = STATIC_STRING("1m8q1n839Cy1l83Epy8t");
    temp = regenerate_optimized_constant(string_constant);
    temp_1 = regenerate_optimized_constant(string_constant_1);
    add_class_to_environment(9,Qkb_frame,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_2),Nil);
    Kb_frame_class_description = 
	    lookup_global_or_kb_specific_property_value(Qkb_frame,
	    Class_description_gkbprop);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    temp_2 = CONS(Qab_class,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qroot),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qab_class,temp);
    set_property_value_function(get_symbol_properties_function(Qroot),
	    Qvirtual_attributes_local_to_class,temp_2);
    list_constant_3 = STATIC_CONS(Qab_class,list_constant_2);
    Qinitial_class = STATIC_SYMBOL("INITIAL-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_class,STATIC_FUNCTION(initial_class,NIL,
	    FALSE,1,1));
    Qget_class = STATIC_SYMBOL("GET-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_class,STATIC_FUNCTION(get_class,NIL,FALSE,1,1));
    add_virtual_attribute(Qab_class,list_constant_3,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_class),SYMBOL_FUNCTION(Qget_class),Nil);
    Qfoundation_class = STATIC_SYMBOL("FOUNDATION-CLASS",AB_package);
    temp_2 = CONS(Qfoundation_class,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qroot),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qfoundation_class,temp);
    set_property_value_function(get_symbol_properties_function(Qroot),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qinitial_foundation_class = STATIC_SYMBOL("INITIAL-FOUNDATION-CLASS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_foundation_class,
	    STATIC_FUNCTION(initial_foundation_class,NIL,FALSE,1,1));
    Qget_foundation_class = STATIC_SYMBOL("GET-FOUNDATION-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_foundation_class,
	    STATIC_FUNCTION(get_foundation_class,NIL,FALSE,1,1));
    add_virtual_attribute(Qfoundation_class,list_constant_3,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_foundation_class),
	    SYMBOL_FUNCTION(Qget_foundation_class),Nil);
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qkb_frame,Qsystem_item);
    check_if_superior_classes_are_defined(Qblock,list_constant_4);
    string_constant_3 = 
	    STATIC_STRING("13Qy4z8r835Dy835Dy9k9k00001r1l8l1l8o1m8p835Dy1l83Cy1l83Uy1l83Fy1m83Dy53-VyFrame status and notes is broken into 2 attribute-mimi");
    string_constant_4 = 
	    STATIC_STRING("cs for export: ~\n       item-status and notes000004z8r83--y83--y9k9k00001o1l8l1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author");
    string_constant_5 = 
	    STATIC_STRING(" entries. each author entry may have a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defini");
    string_constant_6 = 
	    STATIC_STRING("ng-class: item, writable: true\n000004z8r83Hhy83Hhy9k9k00001p1l8l1l83Ey1m8p01l83Uy1l83Ny000004z8r83-0y83-0y9k9k00001p1l83Fy1l8l1l");
    string_constant_7 = 
	    STATIC_STRING("83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentation is available at this time)000004z8r83MCy83MCy9k9k0");
    string_constant_8 = 
	    STATIC_STRING("0001n1l8l1l83Cy1l8o000004z8r83Hly83Hly9k9k00001n1l8l1l8o1l83Hy000004z8r83MLy83MLy9k9k00001n1l8l1l83Ey1l83Hy000004z8r83Ypy83Ypy9k");
    string_constant_9 = 
	    STATIC_STRING("9k00001n1l8l1l83Ey1l83Cy000004z8r83dUy83dUy9k9k00001n1l8l1l83Ey1l83Hy000004z8r83XRy83XRy9k9k00001n1l8l1l83Ey1l83Hy000004z8r83HEy");
    string_constant_10 = 
	    STATIC_STRING("83HEy9k9k00001n1l8l1l8o1l83Hy000004z8r83Tky83Tky9k9k0k001n1l8l1l83Ey1l83Hy000004z8r83XGy83XGy9k9k00001n1l8l1l83Ey1m83Dy73-dy3-iy");
    string_constant_11 = 
	    STATIC_STRING("3-ey3-by3-ly3-my3Sy3-hy3-Yy3Sy3-dy3-Uy3Sy3-ly3-my3-Ty3-my3-Xy3Sy3-oy3-Ty3-ky3-by3-Ty3-Uy3-ey3-Xy3-ly3Sy3-Ty3-gy3-Wy3Sy3-my3-ay3-");
    string_constant_12 = 
	    STATIC_STRING("Xy3-by3-ky3Sy3-hy3-ky3-by3-Zy3-by3-gy3-Ty3-ey3Sy3-oy3-Ty3-ey3-ny3-Xy3-ly3gy3Sy3-5y3-gy3-my3-Xy3-ky3-gy3-Ty3-ey3Sy3-Yy3-hy3-ky3Sy");
    string_constant_13 = 
	    STATIC_STRING("3-gy3-hy3-py3xy3Sy3-wyut3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-dy3-Uy3fy3-ly3-my3-Ty3-my3-Xy3fy3-Ty3-Yy3-my3-Xy3-ky3fy3-ky3-Xy3");
    string_constant_14 = 
	    STATIC_STRING("-ly3-Xy3-my3xy000004z8r83TKy83TKy9k9k00001o1l8l1l83Ey1l83Uy1l83Hy000004z8r83VKy83VKy9k9k00001n1l8l1l83Ey1l83Hy000004z8r836Ry836R");
    string_constant_15 = 
	    STATIC_STRING("y9k9k00001q1l8l1l83Ey1m8p836Ry1l832Ey1l83Hy1m83Dy53-8yDeprecate the user-restrictions slot: don\'t show to the user and don\'t sav");
    string_constant_16 = 
	    STATIC_STRING("e.000004z8r830jy830jy9k9k00001o1l8l1l83Ey1m8p830jy1m83Dy53=EyObject-configuration is aliased to item-configuration. ~\nThe value ");
    string_constant_17 = 
	    STATIC_STRING("is a list of ( <I>configuration-expression</I> * ), writable = true. ~\nWill we read and write the individual configuration expre");
    string_constant_18 = 
	    STATIC_STRING("ssions as text\?000004z8r83-Fy83-Fy9k9k00001p1l8l1m8p83-ky1l83Uy1l83*-y1m83Dy53MySee comment in class block00008k4z8r83W7y83W7y9k");
    string_constant_19 = 
	    STATIC_STRING("9k00001n1l8l1l83Ey1m83Dy53qynames-for-debugging: ( <I>symbol</I> *), e.g. tank-xxx-1000004z8r83-py83-py9k9k00001q1l8l1l83Ey1l8z1");
    string_constant_20 = 
	    STATIC_STRING("l83Cy1m8p01m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;)");
    string_constant_21 = 
	    STATIC_STRING(", ~\nbreakpoint-level: (or default &lt;integer&gt;)]000004z8r83ZCy83ZCy9k9k00001m1l8l1l83Ey000004z8r83Ymy83Ymy9k9k00001q1m8p83Ymy");
    string_constant_22 = 
	    STATIC_STRING("1l8l1l8o1l83Cy1l83Ny1l83Uy000004z8r83U=y83U=y9k9k00001n1l8l1l8o1m83Dy53vyUsed to access the lists that this is a member of.  Int");
    string_constant_23 = 
	    STATIC_STRING("ernal.000004z8r83Hgy83Hgy9k9k00001n1l8l1l83Ey1l83Cy000004z8r83aQy83aQy9k9k00001n1l8l1l8o1l83Cy000004z8r83any83any9k9k00001m1l8l1");
    string_constant_24 = 
	    STATIC_STRING("l83Ey000004z8r83Yly83Yly9k9k00001n1l8l1l8o1m83Dy53Tycallbacks: ( <I>callback</I> * ),000004z8r83Y+y83Y+y9k9k0k001n1l8l1l83Ey1l83");
    string_constant_25 = 
	    STATIC_STRING("Cy000004z8r83Y-y83Y-y9k9k0k001n1l8l1l83Ey1l83Cy000004z8r83Soy83Soy9k9k00001n1l8l1l83Hy1l83Uy00000");
    string_constant_26 = 
	    STATIC_STRING("13Sy8q1n9k1m839Cy833ay8t1t835Dy08l8o1m8p835Dy83Cy83Uy83Fy1m83Dy53-VyFrame status and notes is broken into 2 attribute-mimics for");
    string_constant_27 = 
	    STATIC_STRING(" export: ~\n       item-status and notes1q83--y08l83Ey83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_28 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n1r");
    string_constant_29 = 
	    STATIC_STRING("83Hhy08l83Ey1m8p083Uy83Ny1r83-0y083Fy8l83Ey83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentation is available ");
    string_constant_30 = 
	    STATIC_STRING("at this time)1p83MCy08l83Cy8o1p83Hly08l8o83Hy1p83MLy08l83Ey83Hy1p83Ypy08l83Ey83Cy1p83dUy08l83Ey83Hy1p83XRy08l83Ey83Hy1p83HEy08l8");
    string_constant_31 = 
	    STATIC_STRING("o83Hy1p83Tkyk8l83Ey83Hy1p83XGy08l83Ey1m83Dy73-dy3-iy3-ey3-by3-ly3-my3Sy3-hy3-Yy3Sy3-dy3-Uy3Sy3-ly3-my3-Ty3-my3-Xy3Sy3-oy3-Ty3-ky");
    string_constant_32 = 
	    STATIC_STRING("3-by3-Ty3-Uy3-ey3-Xy3-ly3Sy3-Ty3-gy3-Wy3Sy3-my3-ay3-Xy3-by3-ky3Sy3-hy3-ky3-by3-Zy3-by3-gy3-Ty3-ey3Sy3-oy3-Ty3-ey3-ny3-Xy3-ly3gy3");
    string_constant_33 = 
	    STATIC_STRING("Sy3-5y3-gy3-my3-Xy3-ky3-gy3-Ty3-ey3Sy3-Yy3-hy3-ky3Sy3-gy3-hy3-py3xy3Sy3-wyut3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-dy3-Uy3fy3-l");
    string_constant_34 = 
	    STATIC_STRING("y3-my3-Ty3-my3-Xy3fy3-Ty3-Yy3-my3-Xy3-ky3fy3-ky3-Xy3-ly3-Xy3-my3xy1q83TKy08l83Ey83Uy83Hy1p83VKy08l83Ey83Hy1s836Ry08l83Ey1m8p836R");
    string_constant_35 = 
	    STATIC_STRING("y832Ey83Hy1m83Dy53-8yDeprecate the user-restrictions slot: don\'t show to the user and don\'t save.1q830jy08l83Ey1m8p830jy1m83Dy53");
    string_constant_36 = 
	    STATIC_STRING("=EyObject-configuration is aliased to item-configuration. ~\nThe value is a list of ( <I>configuration-expression</I> * ), writab");
    string_constant_37 = 
	    STATIC_STRING("le = true. ~\nWill we read and write the individual configuration expressions as text\?1r83-Fy08l1m8p83-ky83Uy83*-y1m83Dy53MySee c");
    string_constant_38 = 
	    STATIC_STRING("omment in class block1p83W7y08l83Ey1m83Dy53qynames-for-debugging: ( <I>symbol</I> *), e.g. tank-xxx-11s83-py08l83Ey8z83Cy1m8p01m");
    string_constant_39 = 
	    STATIC_STRING("83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;), ~\nbreakpoi");
    string_constant_40 = 
	    STATIC_STRING("nt-level: (or default &lt;integer&gt;)]1o83ZCy08l83Ey1s83Ymy01m8p83Ymy8l8o83Cy83Ny83Uy1p83U=y08l8o1m83Dy53vyUsed to access the l");
    string_constant_41 = 
	    STATIC_STRING("ists that this is a member of.  Internal.1p83Hgy08l83Ey83Cy1p83aQy08l8o83Cy1o83any08l83Ey1p83Yly08l8o1m83Dy53Tycallbacks: ( <I>c");
    string_constant_42 = 
	    STATIC_STRING("allback</I> * ),1p83Y+yk8l83Ey83Cy1p83Y-yk8l83Ey83Cy1p83Soy08l83Hy83Uy");
    temp = regenerate_optimized_constant(string_constant);
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    temp_1 = regenerate_optimized_constant(list(23,string_constant_3,
	    string_constant_4,string_constant_5,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qblock,list_constant_4,Nil,temp,Nil,temp_1,
	    list_constant_4,regenerate_optimized_constant(list(17,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37,
	    string_constant_38,string_constant_39,string_constant_40,
	    string_constant_41,string_constant_42)),Nil);
    Block_class_description = 
	    lookup_global_or_kb_specific_property_value(Qblock,
	    Class_description_gkbprop);
    Qinvocation_locking_this_object = 
	    STATIC_SYMBOL("INVOCATION-LOCKING-THIS-OBJECT",AB_package);
    Qreclaim_invocation_locking_this_object_value = 
	    STATIC_SYMBOL("RECLAIM-INVOCATION-LOCKING-THIS-OBJECT-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_invocation_locking_this_object_value,
	    STATIC_FUNCTION(reclaim_invocation_locking_this_object_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qinvocation_locking_this_object,
	    SYMBOL_FUNCTION(Qreclaim_invocation_locking_this_object_value),
	    Qslot_value_reclaimer);
    Qname_or_names = STATIC_SYMBOL("NAME-OR-NAMES",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_5 = STATIC_CONS(Qsequence,Qnil);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_6 = STATIC_CONS(Qno_item,Qnil);
    list_constant_7 = STATIC_LIST((SI_Long)4L,Qab_or,Qsymbol,
	    list_constant_5,list_constant_6);
    set_property_value_function(get_symbol_properties_function(Qname_or_names),
	    Qtype_specification_simple_expansion,list_constant_7);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qsequence,Qsymbol,
	    FIX((SI_Long)0L));
    list_constant_9 = STATIC_CONS(list_constant_6,Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,Qsymbol,
	    list_constant_8,list_constant_9);
    define_type_specification_explicit_complex_type(Qname_or_names,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qname_or_names);
    Qcm = STATIC_SYMBOL(",",AB_package);
    name_or_names_evaluation_setter_1 = 
	    STATIC_FUNCTION(name_or_names_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qname_or_names,
	    name_or_names_evaluation_setter_1);
    name_or_names_evaluation_getter_1 = 
	    STATIC_FUNCTION(name_or_names_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qname_or_names,
	    name_or_names_evaluation_getter_1);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qitem_configuration = STATIC_SYMBOL("ITEM-CONFIGURATION",AB_package);
    alias_slot_name(3,Qobject_configuration,Qitem_configuration,Qblock);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qoptions = STATIC_SYMBOL("OPTIONS",AB_package);
    alias_slot_name(3,Qframe_flags,Qoptions,Qnil);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qput_cell_array = STATIC_SYMBOL("PUT-CELL-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_cell_array,STATIC_FUNCTION(put_cell_array,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qcell_array,SYMBOL_FUNCTION(Qput_cell_array),
	    Qslot_putter);
    Qreclaim_cell_array_value = STATIC_SYMBOL("RECLAIM-CELL-ARRAY-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_cell_array_value,
	    STATIC_FUNCTION(reclaim_cell_array_value,NIL,FALSE,2,2));
    mutate_global_property(Qcell_array,
	    SYMBOL_FUNCTION(Qreclaim_cell_array_value),Qslot_value_reclaimer);
}
