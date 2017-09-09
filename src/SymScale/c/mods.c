/* mods.c
 * Input file:  modules.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "mods.h"


/* SORT-SLOT-VALUE-LIST-BY-EXAMPLE */
Object sort_slot_value_list_by_example(list_to_sort,list_in_default_order)
    Object list_to_sort, list_in_default_order;
{
    Object result_1, elements_to_put_on_end, element, ab_loop_list_, temp;

    x_note_fn_call(93,0);
    result_1 = Nil;
    elements_to_put_on_end = Nil;
    element = Nil;
    ab_loop_list_ = list_in_default_order;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(element,list_to_sort))
	result_1 = slot_value_cons_1(element,result_1);
    goto next_loop;
  end_loop:
    element = Nil;
    ab_loop_list_ = list_to_sort;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(element,result_1)))
	elements_to_put_on_end = slot_value_cons_1(element,
		elements_to_put_on_end);
    goto next_loop_1;
  end_loop_1:;
    reclaim_slot_value_list_1(list_to_sort);
    temp = nreverse(elements_to_put_on_end);
    return nreverse(nconc2(temp,result_1));
    return VALUES_1(Qnil);
}

Object Order_of_system_tables_in_menu = UNBOUND;

static Object Qthis_window;        /* this-window */

static Object Qlisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

static Object Qsystem_variable_descriptions;  /* system-variable-descriptions */

static Object Ksystem_frame;       /* :system-frame */

/* COMPUTE-SYSTEM-TABLE-CHOICES */
Object compute_system_table_choices varargs_1(int, n)
{
    Object exclude_this_window, g2_window_for_this_workstation_qm, temp;
    Object module_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, system_variable_name, initialization;
    Object ab_loop_list__1, ab_loopvar__3, ab_loopvar__4, ab_loop_desetq_;
    Object temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,1);
    INIT_ARGS_nonrelocating();
    exclude_this_window = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Servicing_workstation_qm &&  !TRUEP(exclude_this_window)) {
	g2_window_for_this_workstation_qm = ISVREF(Current_workstation,
		(SI_Long)25L);
	temp = g2_window_for_this_workstation_qm ? 
		slot_value_cons_1(Qthis_window,Nil) : Nil;
    }
    else
	temp = Nil;
    module_name = Nil;
    ab_loop_list_ = get(Current_system_name,Qlisp_modules_to_be_loaded,_);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    system_variable_name = Nil;
    initialization = Nil;
    ab_loop_list__1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qsystem_variable_descriptions);
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    system_variable_name = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    initialization = CAR(temp_1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(initialization,Ksystem_frame)) {
	ab_loopvar__4 = slot_value_cons_1(system_variable_name,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
    }
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
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(nconc2(temp,sort_slot_value_list_by_example(temp_1,
	    Order_of_system_tables_in_menu)));
}

static Object Qframe_flags;        /* frame-flags */

/* MAKE-SYSTEM-FRAME */
Object make_system_frame(class_1)
    Object class_1;
{
    Object system_frame;
    SI_Long svref_new_value;

    x_note_fn_call(93,2);
    system_frame = make_frame(class_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(system_frame,Qframe_flags);
    svref_new_value = IFIX(ISVREF(system_frame,(SI_Long)4L)) | (SI_Long)1L;
    ISVREF(system_frame,(SI_Long)4L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	set_block_permanently_changed_function(system_frame);
    put_name_or_names_for_frame(system_frame,
	    compute_name_of_system_frame(class_1),T);
    return VALUES_1(system_frame);
}

/* CLONE-SYSTEM-FRAME */
Object clone_system_frame(old_system_frame)
    Object old_system_frame;
{
    Object system_frame;

    x_note_fn_call(93,3);
    system_frame = clone_frame(1,old_system_frame);
    put_name_or_names_for_frame(system_frame,
	    compute_name_of_system_frame(ISVREF(ISVREF(system_frame,
	    (SI_Long)1L),(SI_Long)1L)),T);
    return VALUES_1(system_frame);
}

static Object Qsystem_table;       /* system-table */

/* COMPUTE-NAME-OF-SYSTEM-FRAME */
Object compute_name_of_system_frame(class_1)
    Object class_1;
{
    Object class_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp, names;

    x_note_fn_call(93,4);
    class_name = class_1;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (EQ(class_name,Qsystem_table))
	goto end_loop;
    ab_loopvar__2 = slot_value_cons_1(class_name,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    temp = lookup_global_or_kb_specific_property_value(class_name,
	    Direct_superior_classes_gkbprop);
    class_name = FIRST(temp);
    goto next_loop;
  end_loop:
    names = ab_loopvar_;
    goto end_1;
    names = Qnil;
  end_1:;
    if (CONSP(names) &&  !TRUEP(CDR(names))) {
	temp = FIRST(names);
	reclaim_slot_value_cons_1(names);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(names);
}

static Object Qthis_system_table_is_installed_qm;  /* this-system-table-is-installed? */

/* INSTALL-SYSTEM-TABLE */
Object install_system_table(system_table)
    Object system_table;
{
    Object temp, class_1, frame, sub_vector_qm, function_qm, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long method_index;

    x_note_fn_call(93,5);
    set(ISVREF(ISVREF(system_table,(SI_Long)1L),(SI_Long)1L),system_table);
    temp = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(system_table,
	    (SI_Long)1L),(SI_Long)1L),Direct_superior_classes_gkbprop);
    class_1 = FIRST(temp);
  next_loop:
    if (EQ(class_1,Qsystem_table))
	goto end_loop;
    set(class_1,system_table);
    temp = lookup_global_or_kb_specific_property_value(class_1,
	    Direct_superior_classes_gkbprop);
    class_1 = FIRST(temp);
    goto next_loop;
  end_loop:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(system_table,
		Qthis_system_table_is_installed_qm);
    SVREF(system_table,FIX((SI_Long)20L)) = T;
    ensure_named_frame_is_first_fetched(system_table);
    method_index = (SI_Long)8L;
    frame = system_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    if (function_qm)
	inline_funcall_1(function_qm,frame);
    if (System_is_running || System_has_paused) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(system_table,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = system_table;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else
	return VALUES_1(Nil);
}

/* DEINSTALL-SYSTEM-TABLE */
Object deinstall_system_table(system_table)
    Object system_table;
{
    Object frame, sub_vector_qm, function_qm;
    SI_Long method_index;

    x_note_fn_call(93,6);
    set(ISVREF(ISVREF(system_table,(SI_Long)1L),(SI_Long)1L),Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(system_table,
		Qthis_system_table_is_installed_qm);
    SVREF(system_table,FIX((SI_Long)20L)) = Nil;
    method_index = (SI_Long)9L;
    frame = system_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    if (function_qm)
	return inline_funcall_1(function_qm,frame);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Modules_and_system_tables_a_list, Qmodules_and_system_tables_a_list);

/* INITIALIZE-MODULES-AND-SYSTEM-TABLES-A-LIST */
Object initialize_modules_and_system_tables_a_list()
{
    x_note_fn_call(93,7);
    Modules_and_system_tables_a_list = 
	    create_initialized_system_tables_suite(Module_information);
    return VALUES_1(Modules_and_system_tables_a_list);
}

/* CREATE-INITIALIZED-SYSTEM-TABLES-SUITE */
Object create_initialized_system_tables_suite(module_information_instance)
    Object module_information_instance;
{
    Object gensymed_symbol, scope_conses, gensymed_symbol_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, system_table_classes;
    Object result_1, class_1, system_table_instance, temp;
    Declare_special(1);

    x_note_fn_call(93,8);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qsystem_table,
	    Inferior_classes_gkbprop);
    scope_conses = Scope_conses;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol_1 = Nil;
      ab_loop_list_ = gensymed_symbol;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      gensymed_symbol_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !EQ(gensymed_symbol_1,Qserver_parameters)) {
	  ab_loopvar__2 = scope_cons(gensymed_symbol_1,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop:
      system_table_classes = ab_loopvar_;
      goto end_1;
      system_table_classes = Qnil;
    end_1:;
      result_1 = slot_value_cons_1(module_information_instance,Nil);
      class_1 = Nil;
      ab_loop_list_ = system_table_classes;
      system_table_instance = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      class_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      system_table_instance = SYMBOL_VALUE(class_1);
      if ( !(EQ(class_1,Qmodule_information) || 
	      memq_function(system_table_instance,result_1)))
	  nconc2(result_1,slot_value_cons_1(system_table_instance,Nil));
      goto next_loop_1;
    end_loop_1:
      temp = result_1;
      goto end_2;
      temp = Qnil;
    end_2:;
    POP_SPECIAL();
    return slot_value_cons_1(temp,Nil);
}

/* SYSTEM-TABLE-INSTALLED-P */
Object system_table_installed_p(system_table)
    Object system_table;
{
    x_note_fn_call(93,9);
    return VALUES_1(ISVREF(system_table,(SI_Long)20L));
}

static Object Qtop_level_kb_module_qm;  /* top-level-kb-module? */

/* SYSTEM-TABLE-SUITE-TEST */
Object system_table_suite_test(module_qm,module_information_instance)
    Object module_qm, module_information_instance;
{
    x_note_fn_call(93,10);
    return VALUES_1(EQ(module_qm,
	    get_slot_value_function(module_information_instance,
	    Qtop_level_kb_module_qm,Nil)) ? T : Nil);
}

static Object Qsystem_table_suite_test;  /* system-table-suite-test */

/* GET-SYSTEM-TABLE-SUITE-FOR-MODULE-OR-NIL */
Object get_system_table_suite_for_module_or_nil(module_qm)
    Object module_qm;
{
    x_note_fn_call(93,11);
    return assoc(4,module_qm,Modules_and_system_tables_a_list,Ktest,
	    SYMBOL_FUNCTION(Qsystem_table_suite_test));
}

/* GET-SYSTEM-TABLE-OF-CLASS-FOR-MODULE-OR-NIL */
Object get_system_table_of_class_for_module_or_nil(module_qm,class_1)
    Object module_qm, class_1;
{
    Object system_table_suite_qm, system_table, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(93,12);
    system_table_suite_qm = 
	    get_system_table_suite_for_module_or_nil(module_qm);
    if (system_table_suite_qm) {
	system_table = Nil;
	ab_loop_list_ = system_table_suite_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	system_table = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(system_table,(SI_Long)1L),
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
	if (temp)
	    return VALUES_1(system_table);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-SYSTEM-TABLE-CURRENTLY-IN-FORCE */
Object get_system_table_currently_in_force(class_1)
    Object class_1;
{
    x_note_fn_call(93,13);
    if (BOUNDP(class_1))
	return VALUES_1(SYMBOL_VALUE(class_1));
    else
	return VALUES_1(Nil);
}

/* GET-MODULE-FOR-SYSTEM-TABLE */
Object get_module_for_system_table(system_table)
    Object system_table;
{
    Object system_table_suite, ab_loop_list_;

    x_note_fn_call(93,14);
    system_table_suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table_suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (member_eql(system_table,system_table_suite) && T)
	return get_slot_value_function(FIRST(system_table_suite),
		Qtop_level_kb_module_qm,Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INSTANTIABLE-SYSTEM-TABLE-SUBCLASS-P */
Object instantiable_system_table_subclass_p(system_table_subclass)
    Object system_table_subclass;
{
    x_note_fn_call(93,15);
    return VALUES_1( 
	    !TRUEP(lookup_global_or_kb_specific_property_value(system_table_subclass,
	    Inferior_classes_gkbprop)) ? T : Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object string_constant;     /* "The module-information instance which has just been created is ~
				    *                 being discarded because it does not specify any top-level KB ~
				    *                 module."
				    */

static Object string_constant_1;   /* "There already is a module-information system table that specifies ~
				    *                 the module ~a as its top-level KB module.  Therefore, the ~
				    *                 module-information instance which has just been created is being ~
				    *                 discarded."
				    */

static Object Qediting;            /* editing */

/* STORE-HAND-CREATED-MODULE-INFORMATION-IF-APPROPRIATE */
Object store_hand_created_module_information_if_appropriate(workstation_context)
    Object workstation_context;
{
    Object workstation_context_return_information, module_information_instance;
    Object frame_serial_number, top_level_kb_module_qm, gensymed_symbol, xa;
    Object ya, temp_1;
    char temp;

    x_note_fn_call(93,16);
    workstation_context_return_information = ISVREF(workstation_context,
	    (SI_Long)5L);
    module_information_instance = 
	    FIRST(workstation_context_return_information);
    frame_serial_number = SECOND(workstation_context_return_information);
    top_level_kb_module_qm = 
	    get_slot_value_function(module_information_instance,
	    Qtop_level_kb_module_qm,Nil);
    gensymed_symbol = ISVREF(module_information_instance,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(module_information_instance) ? 
	    EQ(ISVREF(module_information_instance,(SI_Long)1L),
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
	if ( !TRUEP(top_level_kb_module_qm)) {
	    notify_user(1,string_constant);
	    temp_1 = T;
	}
	else if (get_system_table_suite_for_module_or_nil(top_level_kb_module_qm)) 
		    {
	    notify_user(2,string_constant_1,
		    get_slot_value_function(module_information_instance,
		    Qtop_level_kb_module_qm,Nil));
	    temp_1 = T;
	}
	else
	    temp_1 = Qnil;
	if (temp_1)
	    delete_frame(module_information_instance);
	else
	    finish_setup_of_system_table_suite_for_new_module(module_information_instance);
    }
    return exit_current_workstation_context_in_return_function(Qediting);
}

/* DELETE-HAND-CREATED-MODULE-INFORMATION-IF-APPROPRIATE */
Object delete_hand_created_module_information_if_appropriate(module_information_frame_serial_number)
    Object module_information_frame_serial_number;
{
    Object module_information_instance, frame_reference_serial_number;
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(93,17);
    module_information_instance = 
	    FIRST(module_information_frame_serial_number);
    frame_reference_serial_number = 
	    SECOND(module_information_frame_serial_number);
    gensymed_symbol = ISVREF(module_information_instance,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(module_information_instance) ? 
	    EQ(ISVREF(module_information_instance,(SI_Long)1L),
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
    if ( !temp ?  !TRUEP(assq_function(module_information_instance,
	    Modules_and_system_tables_a_list)) : TRUEP(Nil))
	delete_frame(module_information_instance);
    reclaim_frame_serial_number(frame_reference_serial_number);
    return reclaim_slot_value_list_1(module_information_frame_serial_number);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

/* INSTALL-SYSTEM-TABLE-FOR-MODULE-INFORMATION */
Object install_system_table_for_module_information(module_information)
    Object module_information;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,18);
    PUSH_SPECIAL_WITH_SYMBOL(Module_information,Qmodule_information,module_information,
	    0);
      change_slot_value(3,Module_information,Qframe_status_and_notes,Nil);
      result = update_module_related_frame_notes_for_all_workspaces(0);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-MODULE-INFORMATION */
Object deinstall_system_table_for_module_information(module_information)
    Object module_information;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,19);
    PUSH_SPECIAL_WITH_SYMBOL(Module_information,Qmodule_information,module_information,
	    0);
      result = change_slot_value(3,Module_information,
	      Qframe_status_and_notes,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qnone;               /* none */

/* COMPILE-FILE-NAME?-FOR-SLOT */
Object compile_file_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,20);
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

static Object string_constant_2;   /* "none" */

static Object string_constant_3;   /* "~s" */

static Object string_constant_4;   /* "~a" */

/* WRITE-FILE-NAME?-FROM-SLOT */
Object write_file_name_qm_from_slot(file_name_qm,gensymed_symbol)
    Object file_name_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(93,21);
    temp = file_name_qm;
    if (temp);
    else
	temp = string_constant_2;
    return tformat(2,file_name_qm ? string_constant_3 : string_constant_4,
	    temp);
}

static Object Qdefault;            /* default */

/* COMPILE-MODULE-FILE-NAME?-FOR-SLOT */
Object compile_module_file_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,22);
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

static Object string_constant_5;   /* "default" */

/* WRITE-MODULE-FILE-NAME?-FROM-SLOT */
Object write_module_file_name_qm_from_slot(file_name_qm,gensymed_symbol)
    Object file_name_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(93,23);
    temp = file_name_qm;
    if (temp);
    else
	temp = string_constant_5;
    return tformat(2,file_name_qm ? string_constant_3 : string_constant_4,
	    temp);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* MODULE-FILE-NAME?-EVALUATION-SETTER */
Object module_file_name_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(93,24);
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
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
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
		      goto end_module_file_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = copy_for_phrase(evaluation_value);
    else
	result = VALUES_1(Qdefault);
  end_module_file_name_qm_evaluation_setter:
    return result;
}

/* MODULE-FILE-NAME?-EVALUATION-GETTER */
Object module_file_name_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(93,25);
    if (text_string_p(slot_value))
	temp = copy_as_wide_string(slot_value);
    else if (SYMBOLP(slot_value))
	temp = slot_value;
    else
	temp = Qnil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* "~a is ~NV" */

static Object string_constant_7;   /* ";~%" */

/* WRITE-MODULE-ANNOTATIONS-FROM-SLOT */
Object write_module_annotations_from_slot(plist,gensymed_symbol)
    Object plist, gensymed_symbol;
{
    Object k, v, tail, ab_loop_list_, temp;

    x_note_fn_call(93,26);
    if (plist) {
	k = Nil;
	v = Nil;
	tail = Nil;
	ab_loop_list_ = plist;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	k = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	v = CAR(temp);
	temp = CDR(ab_loop_list_);
	tail = CDR(temp);
	tformat(3,string_constant_6,k,v);
	if (tail)
	    tformat(1,string_constant_7);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return tformat(1,string_constant_2);
}

static Object string_constant_8;   /* "Duplicate annotation for ~a found." */

/* COMPILE-MODULE-ANNOTATIONS-FOR-SLOT */
Object compile_module_annotations_for_slot varargs_1(int, n)
{
    Object plist, gensymed_symbol, gensymed_symbol_1;
    Object k, v, tail, ab_loop_list_, temp, k2, v2, t2, ab_loop_list__1;
    Object ab_loop_it_, duplicate_key_qm, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,27);
    INIT_ARGS_nonrelocating();
    plist = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    k = Nil;
    v = Nil;
    tail = Nil;
    ab_loop_list_ = plist;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    k = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    v = CAR(temp);
    temp = CDR(ab_loop_list_);
    tail = CDR(temp);
    k2 = Nil;
    v2 = Nil;
    t2 = Nil;
    ab_loop_list__1 = tail;
    ab_loop_it_ = Nil;
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
  next_loop_1:
    k2 = CAR(ab_loop_list__1);
    temp = CDR(ab_loop_list__1);
    v2 = CAR(temp);
    temp = CDR(ab_loop_list__1);
    t2 = CDR(temp);
    ab_loop_it_ = EQ(k,k2) ? T : Nil;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    ab_loop_list__1 = CDDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1) {
	duplicate_key_qm = k;
	goto end_2;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    duplicate_key_qm = Qnil;
  end_2:;
    if (duplicate_key_qm) {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_8,duplicate_key_qm);
	return VALUES_2(temp_2,temp);
    }
    else
	return VALUES_1(plist);
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Qannotation_name;    /* annotation-name */

static Object Qannotation_value;   /* annotation-value */

/* MODULE-ANNOTATIONS-EVALUATION-SETTER */
Object module_annotations_evaluation_setter(sequence,frame,
	    slot_description,gensymed_symbol)
    Object sequence, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object structure, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(93,28);
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
			  !TRUEP(type_specification_type_p__with_explanation(sequence,
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(sequence,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_module_annotations_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    structure = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    structure = validated_elt;
    ab_loopvar__2 = phrase_cons(estructure_slot(structure,Qannotation_name,
	    Nil),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = phrase_cons(copy_for_phrase(estructure_slot(structure,
	    Qannotation_value,Nil)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_module_annotations_evaluation_setter:
    return result;
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* MODULE-ANNOTATIONS-EVALUATION-GETTER */
Object module_annotations_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object k, v, tail, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, gensymed_symbol, temp_1, item_or_value, x2;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(93,29);
    k = Nil;
    v = Nil;
    tail = Nil;
    ab_loop_list_ = slot_value;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    k = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    v = CAR(temp);
    temp = CDR(ab_loop_list_);
    tail = CDR(temp);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qannotation_name;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Qannotation_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = k;
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
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = k;
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
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qannotation_value;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = Qannotation_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = FIXNUMP(v) || v && SYMBOLP(v) ? v : 
		copy_evaluation_value_1(v);
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
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = FIXNUMP(v) || v && SYMBOLP(v) ? v : 
		copy_evaluation_value_1(v);
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
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

Object Workspaces_belonging_to_this_module_kbprop = UNBOUND;

Object Module_information_instance_for_module_qm_kbprop = UNBOUND;

static Object Qmodule_system_table_belongs_to_qm;  /* module-system-table-belongs-to? */

static Object Qab_class;           /* class */

/* PUT-TOP-LEVEL-KB-MODULE? */
Object put_top_level_kb_module_qm(module_information_instance,new_value,
	    initializing_qm)
    Object module_information_instance, new_value, initializing_qm;
{
    Object system_table_suite_this_is_part_of, system_table, ab_loop_list_;

    x_note_fn_call(93,30);
    if ( !TRUEP(initializing_qm)) {
	system_table_suite_this_is_part_of = 
		assq_function(module_information_instance,
		Modules_and_system_tables_a_list);
	system_table = Nil;
	ab_loop_list_ = system_table_suite_this_is_part_of;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	system_table = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(system_table,
		    Qmodule_system_table_belongs_to_qm);
	SVREF(system_table,FIX((SI_Long)21L)) = new_value;
	goto next_loop;
      end_loop:;
	if (ISVREF(module_information_instance,(SI_Long)23L)) {
	    add_or_delete_module_name_from_directory_of_names(ISVREF(module_information_instance,
		    (SI_Long)23L),T);
	    if (EQ(lookup_kb_specific_property_value(ISVREF(module_information_instance,
		    (SI_Long)23L),
		    Module_information_instance_for_module_qm_kbprop),
		    module_information_instance))
		mutate_kb_specific_property_value(ISVREF(module_information_instance,
			(SI_Long)23L),Nil,
			Module_information_instance_for_module_qm_kbprop);
	}
    }
    if (new_value) {
	add_or_delete_module_name_from_directory_of_names(new_value,Nil);
	mutate_kb_specific_property_value(new_value,
		module_information_instance,
		Module_information_instance_for_module_qm_kbprop);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(module_information_instance,
		Qtop_level_kb_module_qm);
    SVREF(module_information_instance,FIX((SI_Long)23L)) = new_value;
    update_module_related_frame_notes_for_all_workspaces(0);
    update_representations_of_slot_value(2,module_information_instance,
	    Qab_class);
    return VALUES_1(new_value);
}

/* RECLAIM-TOP-LEVEL-KB-MODULE?-VALUE */
Object reclaim_top_level_kb_module_qm_value(module_qm,
	    module_information_instance)
    Object module_qm, module_information_instance;
{
    x_note_fn_call(93,31);
    if (module_qm) {
	add_or_delete_module_name_from_directory_of_names(module_qm,T);
	if (EQ(lookup_kb_specific_property_value(module_qm,
		Module_information_instance_for_module_qm_kbprop),
		module_information_instance))
	    mutate_kb_specific_property_value(module_qm,Nil,
		    Module_information_instance_for_module_qm_kbprop);
    }
    return VALUES_1(Nil);
}

static Object Qunspecified;        /* unspecified */

static Object string_constant_9;   /* "you cannot change the ~a attribute of a ~
				    *               non-top-level module-information system table ~
				    *               to UNSPECIFIED."
				    */

static Object string_constant_10;  /* "you cannot change the ~a attribute of a ~
				    *           module-information system table ~
				    *           to the name of an already existing module."
				    */

/* COMPILE-MODULE-NAME-FOR-MODULE-INFORMATION?-FOR-SLOT */
Object compile_module_name_for_module_information_qm_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object gensymed_symbol, sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,32);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qunspecified)) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qmodule_information,
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
	if ((temp ?  !TRUEP(system_table_installed_p(frame)) : TRUEP(Nil)) 
		? EQ(parse_result,Qunspecified) : TRUEP(Nil)) {
	    temp_1 = Bad_phrase;
	    temp_2 = get_alias_for_slot_name_if_any(slot_name,frame);
	    if (temp_2);
	    else
		temp_2 = slot_name;
	    temp_2 = tformat_text_string(2,string_constant_9,temp_2);
	    return VALUES_2(temp_1,temp_2);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qmodule_information,
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
	if ((temp ? TRUEP(module_exists_p(parse_result)) : TRUEP(Nil)) ?  
		!EQ(parse_result,get_slot_value_function(frame,slot_name,
		Nil)) : TRUEP(Nil)) {
	    temp_1 = Bad_phrase;
	    temp_2 = get_alias_for_slot_name_if_any(slot_name,frame);
	    if (temp_2);
	    else
		temp_2 = slot_name;
	    temp_2 = tformat_text_string(2,string_constant_10,temp_2);
	    return VALUES_2(temp_1,temp_2);
	}
	else
	    return VALUES_1(parse_result);
    }
}

/* WRITE-MODULE-NAME-FOR-MODULE-INFORMATION?-FROM-SLOT */
Object write_module_name_for_module_information_qm_from_slot(module_name_qm,
	    gensymed_symbol)
    Object module_name_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(93,33);
    temp = module_name_qm;
    if (temp);
    else
	temp = Qunspecified;
    return twrite_symbol(1,temp);
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

/* MODULE-NAME-FOR-MODULE-INFORMATION?-EVALUATION-SETTER */
Object module_name_for_module_information_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(93,34);
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
			  list_constant_4))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_5,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_module_name_for_module_information_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = VALUES_1(evaluation_value);
    else
	result = VALUES_1(Qunspecified);
  end_module_name_for_module_information_qm_evaluation_setter:
    return result;
}

/* MODULE-NAME-FOR-MODULE-INFORMATION?-EVALUATION-GETTER */
Object module_name_for_module_information_qm_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(93,35);
    GENSYM_RETURN_ONE(EQ(slot_value,Qunspecified) ? Nil : slot_value);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* WRITE-LIST-OF-MODULES?-FROM-SLOT */
Object write_list_of_modules_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object l;

    x_note_fn_call(93,36);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	l = value;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	tprin(CAR(l),T);
	if (CDR(l))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qcm;                 /* \, */

/* COMPILE-LIST-OF-MODULES?-FOR-SLOT */
Object compile_list_of_modules_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,37);
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
    else if (EQ(CAR(parse_result),Qcm))
	return VALUES_1(CDR(parse_result));
    else
	return VALUES_1(parse_result);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_11;  /* "~NT " */

static Object string_constant_12;  /* "~NV must be one of the following types: ~a" */

/* LIST-OF-MODULES?-EVALUATION-SETTER */
Object list_of_modules_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object module_name, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(93,38);
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
		      goto end_list_of_modules_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_8))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_9)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	module_name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
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
	module_name = validated_elt;
	ab_loopvar__2 = phrase_cons(module_name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_11,list_constant_8);
		  tformat(2,string_constant_11,list_constant_9);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_12,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_list_of_modules_qm_evaluation_setter:
    return result;
}

/* LIST-OF-MODULES?-EVALUATION-GETTER */
Object list_of_modules_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object module_name, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(93,39);
    if (slot_value) {
	module_name = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	module_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(module_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = allocate_evaluation_sequence(Qnil);
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qreclaim_slot_value_cons_function;  /* reclaim-slot-value-cons-function */

static Object Qdirectly_required_kb_modules;  /* directly-required-kb-modules */

/* PUT-DIRECTLY-REQUIRED-KB-MODULES */
Object put_directly_required_kb_modules(module_information_instance,value,
	    gensymed_symbol)
    Object module_information_instance, value, gensymed_symbol;
{
    Object module, ab_loop_list_;

    x_note_fn_call(93,40);
    if (value)
	value = delete_duplicates_from_list(2,value,
		Qreclaim_slot_value_cons_function);
    module = Nil;
    ab_loop_list_ = ISVREF(module_information_instance,(SI_Long)24L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_or_delete_module_name_from_directory_of_names(module,T);
    goto next_loop;
  end_loop:;
    module = Nil;
    ab_loop_list_ = value;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_or_delete_module_name_from_directory_of_names(module,Nil);
    goto next_loop_1;
  end_loop_1:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(module_information_instance,
		Qdirectly_required_kb_modules);
    SVREF(module_information_instance,FIX((SI_Long)24L)) = value;
    update_module_related_frame_notes_for_all_workspaces(0);
    return VALUES_1(value);
}

/* RECLAIM-DIRECTLY-REQUIRED-KB-MODULES-VALUE */
Object reclaim_directly_required_kb_modules_value(value,
	    module_information_instance)
    Object value, module_information_instance;
{
    Object module, ab_loop_list_;

    x_note_fn_call(93,41);
    module = Nil;
    ab_loop_list_ = value;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_or_delete_module_name_from_directory_of_names(module,T);
    goto next_loop;
  end_loop:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(module_information_instance,
		Qdirectly_required_kb_modules);
    SVREF(module_information_instance,FIX((SI_Long)24L)) = Nil;
    reclaim_slot_value(value);
    return VALUES_1(Nil);
}

static Object Qdelete_from_directory_of_names;  /* delete-from-directory-of-names */

static Object Qadd_to_directory_of_names;  /* add-to-directory-of-names */

static Object Qmodule_name;        /* module-name */

/* ADD-OR-DELETE-MODULE-NAME-FROM-DIRECTORY-OF-NAMES */
Object add_or_delete_module_name_from_directory_of_names(module_name,
	    delete_case_qm)
    Object module_name, delete_case_qm;
{
    Object temp;

    x_note_fn_call(93,42);
    temp = SYMBOL_FUNCTION(delete_case_qm ? 
	    Qdelete_from_directory_of_names : Qadd_to_directory_of_names);
    return FUNCALL_2(temp,module_name,Qmodule_name);
}

DEFINE_VARIABLE_WITH_SYMBOL(Modules_that_have_already_been_loaded, Qmodules_that_have_already_been_loaded);

DEFINE_VARIABLE_WITH_SYMBOL(Currently_loading_modules_qm, Qcurrently_loading_modules_qm);

static Object string_constant_13;  /* ", because \"Start KB after Load?\" is set in Miscellaneous Parameters" */

static Object Qload_grammar;       /* load-grammar */

static Object string_constant_14;  /* ", as specified in the last \"Load KB\" command" */

static Object Qmerge_grammar;      /* merge-grammar */

static Object string_constant_15;  /* ", as specified in the last \"Merge KB\" command" */

static Object Qload_in_init_file;  /* load-in-init-file */

static Object string_constant_16;  /* ", from the last \"Load KB\" line in the G2 Init file to specify this" */

static Object Qmerge_in_init_file;  /* merge-in-init-file */

static Object string_constant_17;  /* ", from the last \"Merge KB\" line in the G2 Init file to specify this" */

static Object Qload_from_command_line;  /* load-from-command-line */

static Object string_constant_18;  /* ", because the command line that launched G2 specified the \"-start\" option" */

static Object string_constant_19;  /* "" */

static Object string_constant_20;  /* "Starting to run G2 automatically~a.  ~
				    *      You may pause, reset, or restart at any time."
				    */

/* NOTIFY-USER-OF-AUTOSTART-AND-REASON */
Object notify_user_of_autostart_and_reason(kb_autostart_reason)
    Object kb_autostart_reason;
{
    Object temp;

    x_note_fn_call(93,43);
    if (EQ(kb_autostart_reason,Qsystem_table))
	temp = string_constant_13;
    else if (EQ(kb_autostart_reason,Qload_grammar))
	temp = string_constant_14;
    else if (EQ(kb_autostart_reason,Qmerge_grammar))
	temp = string_constant_15;
    else if (EQ(kb_autostart_reason,Qload_in_init_file))
	temp = string_constant_16;
    else if (EQ(kb_autostart_reason,Qmerge_in_init_file))
	temp = string_constant_17;
    else if (EQ(kb_autostart_reason,Qload_from_command_line))
	temp = string_constant_18;
    else
	temp = string_constant_19;
    return notify_user(2,string_constant_20,temp);
}

/* PARTITION-SYSTEM-TABLES-INTO-SEPARATE-MODULE-SUITES */
Object partition_system_tables_into_separate_module_suites(system_tables)
    Object system_tables;
{
    Object result_1, system_table, ab_loop_list_, server_parameters_qm;
    Object module_for_system_table_qm, entry_for_this_module_qm, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, entry;
    Object ab_loop_list__1, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object cdr_new_value, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(93,44);
    result_1 = Nil;
    system_table = Nil;
    ab_loop_list_ = system_tables;
    server_parameters_qm = Nil;
    module_for_system_table_qm = Nil;
    entry_for_this_module_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(system_table) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(system_table)) > (SI_Long)2L && 
	     !EQ(ISVREF(system_table,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(system_table,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qserver_parameters,
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
		server_parameters_qm = (SI_Long)0L < gensymed_symbol_2 ? T 
			: Nil;
	    }
	    else
		server_parameters_qm = Nil;
	}
	else
	    server_parameters_qm = Nil;
    }
    else
	server_parameters_qm = Nil;
    module_for_system_table_qm = ISVREF(system_table,(SI_Long)21L);
    entry = Nil;
    ab_loop_list__1 = result_1;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    entry = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(ISVREF(CAR(entry),(SI_Long)21L),module_for_system_table_qm)) {
	entry_for_this_module_qm = entry;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    entry_for_this_module_qm = Qnil;
  end_1:;
    if (server_parameters_qm)
	delete_frame(system_table);
    else if (entry_for_this_module_qm) {
	slot_value_push_modify_macro_arg = system_table;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = CDR(entry_for_this_module_qm);
	cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	M_CDR(entry_for_this_module_qm) = cdr_new_value;
    }
    else
	result_1 = slot_value_cons_1(slot_value_cons_1(system_table,Nil),
		result_1);
    goto next_loop;
  end_loop:
    temp = result_1;
    if (temp)
	return VALUES_1(temp);
    else
	return slot_value_cons_1(Nil,Nil);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_tables_read_for_this_module, Qsystem_tables_read_for_this_module);

DEFINE_VARIABLE_WITH_SYMBOL(Name_of_module_being_read_qm, Qname_of_module_being_read_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Main_kb_being_read_qm, Qmain_kb_being_read_qm);

/* SET-UP-MODULES-AND-SYSTEM-TABLES-A-LIST-AFTER-READING */
Object set_up_modules_and_system_tables_a_list_after_reading()
{
    Object do_not_note_permanent_changes_p, all_system_table_suites_read_in;
    Object entry, ab_loop_list_, suite_to_install;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,45);
    do_not_note_permanent_changes_p = T;
    all_system_table_suites_read_in = 
	    partition_system_tables_into_separate_module_suites(System_tables_read_for_this_module);
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      if (Name_of_module_being_read_qm ||  
	      !TRUEP(CDR(all_system_table_suites_read_in)))
	  merge_in_system_table_suite_read_in(2,
		  CAR(all_system_table_suites_read_in),Main_kb_being_read_qm);
      else {
	  entry = Nil;
	  ab_loop_list_ = all_system_table_suites_read_in;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  entry = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ISVREF(FIRST(entry),(SI_Long)20L)) {
	      suite_to_install = entry;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  suite_to_install = Qnil;
	end_1:;
	  merge_in_system_table_suite_read_in(2,suite_to_install,
		  Main_kb_being_read_qm);
	  entry = Nil;
	  ab_loop_list_ = all_system_table_suites_read_in;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  entry = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !EQ(entry,suite_to_install))
	      merge_in_system_table_suite_read_in(2,entry,Nil);
	  goto next_loop_1;
	end_loop_1:;
      }
      result = reclaim_slot_value_list_1(all_system_table_suites_read_in);
    POP_SPECIAL();
    return result;
}

/* MERGE-IN-SYSTEM-TABLE-SUITE-READ-IN */
Object merge_in_system_table_suite_read_in varargs_1(int, n)
{
    Object suite, installing_qm;
    Object system_table_suite_to_replace_qm, module_qm;
    Object matching_existing_suite_qm, suite_for_unspecified_module_qm;
    Object defer_notifications_qm;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(93,46);
    INIT_ARGS_nonrelocating();
    suite = REQUIRED_ARG_nonrelocating();
    installing_qm = REQUIRED_ARG_nonrelocating();
    system_table_suite_to_replace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    module_qm = get_module_assignment_of_system_table_suite_read_in(suite);
    matching_existing_suite_qm = 
	    find_system_table_suite_with_module_assignment(module_qm);
    suite_for_unspecified_module_qm =  !EQ(module_qm,Qnil) ? 
	    find_system_table_suite_with_module_assignment(Qnil) : Nil;
    if ( !TRUEP(installing_qm) && (matching_existing_suite_qm ||  
	    !TRUEP(module_qm)))
	delete_system_table_suite(3,suite,T,T);
    else {
	suite = make_fully_fleshed_out_system_table_suite(suite);
	store_system_table_suite(suite);
	if (installing_qm) {
	    defer_notifications_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
		    0);
	      deinstall_currently_installed_system_table_suite();
	      if (system_table_suite_to_replace_qm)
		  delete_system_table_suite(3,
			  system_table_suite_to_replace_qm,Nil,T);
	      install_system_table_suite(suite);
	      Defer_notifications_qm = Nil;
	      try_to_do_deferred_user_notifications();
	    POP_SPECIAL();
	    if (matching_existing_suite_qm)
		delete_system_table_suite(3,matching_existing_suite_qm,T,T);
	    if (suite_for_unspecified_module_qm)
		delete_system_table_suite(3,
			suite_for_unspecified_module_qm,T,T);
	}
	inform_ui_client_interfaces_of_module_creation(CAR(suite));
    }
    set_up_all_module_to_module_information_instance_backpointers();
    return update_module_related_frame_notes_for_all_workspaces(0);
}

/* GET-MODULE-ASSIGNMENT-OF-SYSTEM-TABLE-SUITE-READ-IN */
Object get_module_assignment_of_system_table_suite_read_in(suite)
    Object suite;
{
    Object system_table, ab_loop_list_, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(93,47);
    system_table = Nil;
    ab_loop_list_ = suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qmodule_information,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(system_table,(SI_Long)1L),
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
	return VALUES_1(ISVREF(system_table,(SI_Long)23L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* OBSOLETE-SYSTEM-TABLE-P */
Object obsolete_system_table_p(system_table)
    Object system_table;
{
    x_note_fn_call(93,48);
    return VALUES_1( !BOUNDP(ISVREF(ISVREF(system_table,(SI_Long)1L),
	    (SI_Long)1L)) ? T : Nil);
}

/* FIND-DUPLICATE-SYSTEM-TABLE-IN-LIST */
Object find_duplicate_system_table_in_list(system_table,list_of_system_tables)
    Object system_table, list_of_system_tables;
{
    Object system_table_in_list, ab_loop_list_;

    x_note_fn_call(93,49);
    system_table_in_list = Nil;
    ab_loop_list_ = list_of_system_tables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table_in_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(ISVREF(system_table,(SI_Long)1L),(SI_Long)1L),
	    ISVREF(ISVREF(system_table_in_list,(SI_Long)1L),(SI_Long)1L)))
	return VALUES_1(system_table_in_list);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAKE-FULLY-FLESHED-OUT-SYSTEM-TABLE-SUITE */
Object make_fully_fleshed_out_system_table_suite(suite)
    Object suite;
{
    x_note_fn_call(93,50);
    return propagate_module_assignment_throughout_system_table_suite(make_suite_be_headed_up_by_module_information_system_table(add_newer_system_tables_to_suite_if_necessary(delete_obsolete_or_duplicate_system_tables_in_suite(remove_any_trappings_of_installation_in_system_table_suite(suite)))));
}

/* REMOVE-ANY-TRAPPINGS-OF-INSTALLATION-IN-SYSTEM-TABLE-SUITE */
Object remove_any_trappings_of_installation_in_system_table_suite(suite)
    Object suite;
{
    Object system_table, ab_loop_list_;

    x_note_fn_call(93,51);
    system_table = Nil;
    ab_loop_list_ = suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(system_table,
		Qthis_system_table_is_installed_qm);
    SVREF(system_table,FIX((SI_Long)20L)) = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(suite);
}

/* DELETE-OBSOLETE-OR-DUPLICATE-SYSTEM-TABLES-IN-SUITE */
Object delete_obsolete_or_duplicate_system_tables_in_suite(suite)
    Object suite;
{
    Object copied_suite_list, copied_sublist, system_table, temp, sublist;
    Object suite_system_table, cdr_new_value;

    x_note_fn_call(93,52);
    copied_suite_list = copy_list_using_slot_value_conses_1(suite);
    copied_sublist = copied_suite_list;
    system_table = Nil;
  next_loop:
    if ( !TRUEP(copied_sublist))
	goto end_loop;
    system_table = CAR(copied_sublist);
    if (obsolete_system_table_p(system_table) || 
	    find_duplicate_system_table_in_list(system_table,
	    CDR(copied_sublist))) {
	if (EQ(CAR(suite),system_table)) {
	    temp = suite;
	    suite = CDR(suite);
	    reclaim_slot_value_cons_1(temp);
	}
	else {
	    sublist = suite;
	    suite_system_table = Nil;
	  next_loop_1:
	    if ( !TRUEP(sublist))
		goto end_loop_1;
	    suite_system_table = CADR(sublist);
	    if (EQ(suite_system_table,system_table)) {
		temp = CDR(sublist);
		cdr_new_value = CDDR(sublist);
		M_CDR(sublist) = cdr_new_value;
		reclaim_slot_value_cons_1(temp);
		goto end_loop_1;
	    }
	    sublist = M_CDR(sublist);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if (Reading_kb_p)
	    delete_block_after_reading_kb(system_table);
	else
	    delete_frame(system_table);
    }
    copied_sublist = M_CDR(copied_sublist);
    goto next_loop;
  end_loop:
    reclaim_slot_value_list_1(copied_suite_list);
    return VALUES_1(suite);
    return VALUES_1(Qnil);
}

/* DEINSTALL-CURRENTLY-INSTALLED-SYSTEM-TABLE-SUITE */
Object deinstall_currently_installed_system_table_suite()
{
    Object suite, ab_loop_list_;

    x_note_fn_call(93,53);
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(FIRST(suite),(SI_Long)20L))
	return deinstall_system_table_suite(suite);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-CURRENTLY-INSTALLED-SYSTEM-TABLE-SUITE */
Object find_currently_installed_system_table_suite()
{
    Object suite, ab_loop_list_;

    x_note_fn_call(93,54);
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(FIRST(suite),(SI_Long)20L))
	return VALUES_1(suite);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DEINSTALL-SYSTEM-TABLE-SUITE */
Object deinstall_system_table_suite(suite)
    Object suite;
{
    Object system_table, ab_loop_list_;

    x_note_fn_call(93,55);
    system_table = Nil;
    ab_loop_list_ = suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    deinstall_system_table(system_table);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ADD-NEWER-SYSTEM-TABLES-TO-SUITE-IF-NECESSARY */
Object add_newer_system_tables_to_suite_if_necessary(suite)
    Object suite;
{
    Object scope_conses, ab_loopvar_, class_1, temp, system_table;
    Object ab_loop_list_, gensymed_symbol, sub_class_bit_vector;
    Object new_system_table, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(93,56);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qsystem_table;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      if ( !EQ(class_1,Qserver_parameters) && 
	      instantiable_system_table_subclass_p(class_1)) {
	  system_table = Nil;
	  ab_loop_list_ = suite;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  system_table = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  if (gensymed_symbol) {
	      sub_class_bit_vector = ISVREF(ISVREF(system_table,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		  temp_1 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp_1 = TRUEP(Nil);
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_1 = TRUEP(T);
	  goto end_1;
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  new_system_table = make_system_frame(class_1);
	  if (System_is_running || System_has_paused) {
	      gensymed_symbol = 
		      ISVREF(ISVREF(ISVREF(ISVREF(new_system_table,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	      gensymed_symbol_4 = new_system_table;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_4);
	  }
	  suite = slot_value_cons_1(new_system_table,suite);
      }
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(suite);
}

/* MAKE-SUITE-BE-HEADED-UP-BY-MODULE-INFORMATION-SYSTEM-TABLE */
Object make_suite_be_headed_up_by_module_information_system_table(suite)
    Object suite;
{
    Object temp, elements, frame, symbol, gensymed_symbol;
    Object sub_class_bit_vector, car_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(93,57);
    temp = CAR(suite);
    elements = suite;
  next_loop:
    if ( !TRUEP(elements))
	goto end_loop;
    frame = CAR(elements);
    symbol = Qmodule_information;
    gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	car_new_value = CAR(elements);
	M_CAR(suite) = car_new_value;
	M_CAR(elements) = temp;
	goto end_1;
    }
    elements = M_CDR(elements);
    goto next_loop;
  end_loop:
  end_1:;
    return VALUES_1(suite);
}

/* PROPAGATE-MODULE-ASSIGNMENT-THROUGHOUT-SYSTEM-TABLE-SUITE */
Object propagate_module_assignment_throughout_system_table_suite(suite)
    Object suite;
{
    Object module_qm, system_table, ab_loop_list_;

    x_note_fn_call(93,58);
    module_qm = ISVREF(FIRST(suite),(SI_Long)23L);
    system_table = Nil;
    ab_loop_list_ = suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(system_table,
		Qmodule_system_table_belongs_to_qm);
    SVREF(system_table,FIX((SI_Long)21L)) = module_qm;
    goto next_loop;
  end_loop:;
    return VALUES_1(suite);
}

/* FIND-SYSTEM-TABLE-SUITE-WITH-MODULE-ASSIGNMENT */
Object find_system_table_suite_with_module_assignment(module_qm)
    Object module_qm;
{
    Object suite, ab_loop_list_, module_information_instance;

    x_note_fn_call(93,59);
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_information_instance = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_information_instance = FIRST(suite);
    if (EQ(ISVREF(module_information_instance,(SI_Long)23L),module_qm))
	return VALUES_1(suite);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INSTALL-SYSTEM-TABLE-SUITE */
Object install_system_table_suite(suite)
    Object suite;
{
    Object system_table, ab_loop_list_;

    x_note_fn_call(93,60);
    system_table = Nil;
    ab_loop_list_ = suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    install_system_table(system_table);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STORE-SYSTEM-TABLE-SUITE */
Object store_system_table_suite(suite)
    Object suite;
{
    x_note_fn_call(93,61);
    Modules_and_system_tables_a_list = slot_value_cons_1(suite,
	    Modules_and_system_tables_a_list);
    return VALUES_1(Modules_and_system_tables_a_list);
}

static Object Qab_modules;         /* modules */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* DELETE-SYSTEM-TABLE-SUITE */
Object delete_system_table_suite varargs_1(int, n)
{
    Object system_table_suite_or_module_information_therefor;
    Object delete_after_reading_qm;
    Object suppress_update_of_module_related_frame_notes_qm;
    Object system_table_suite, system_table, ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,62);
    INIT_ARGS_nonrelocating();
    system_table_suite_or_module_information_therefor = REQUIRED_ARG_nonrelocating();
    delete_after_reading_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    suppress_update_of_module_related_frame_notes_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    system_table_suite = 
	    ATOM(system_table_suite_or_module_information_therefor) ? 
	    assq_function(system_table_suite_or_module_information_therefor,
	    Modules_and_system_tables_a_list) : 
	    system_table_suite_or_module_information_therefor;
    Modules_and_system_tables_a_list = 
	    delete_slot_value_element_1(system_table_suite,
	    Modules_and_system_tables_a_list);
    decache_dynamic_menus(1,Qab_modules);
    inform_ui_client_interfaces_of_module_deletion(FIRST(system_table_suite));
    system_table = Nil;
    ab_loop_list_ = system_table_suite;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    change_slot_value(3,system_table,Qname_or_names_for_frame,Nil);
    goto next_loop;
  end_loop:;
    system_table = Nil;
    ab_loop_list_ = system_table_suite;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    system_table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (delete_after_reading_qm)
	delete_block_after_reading_kb(system_table);
    else
	delete_frame(system_table);
    goto next_loop_1;
  end_loop_1:;
    reclaim_slot_value_list_1(system_table_suite);
    if ( !TRUEP(suppress_update_of_module_related_frame_notes_qm))
	return update_module_related_frame_notes_for_all_workspaces(0);
    else
	return VALUES_1(Nil);
}

/* SET-UP-ALL-MODULE-TO-MODULE-INFORMATION-INSTANCE-BACKPOINTERS */
Object set_up_all_module_to_module_information_instance_backpointers()
{
    Object suite, ab_loop_list_, module_qm;

    x_note_fn_call(93,63);
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_qm = ISVREF(FIRST(suite),(SI_Long)23L);
    if (module_qm)
	mutate_kb_specific_property_value(module_qm,FIRST(suite),
		Module_information_instance_for_module_qm_kbprop);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FINISH-SETUP-OF-SYSTEM-TABLE-SUITE-FOR-NEW-MODULE */
Object finish_setup_of_system_table_suite_for_new_module(module_information_instance)
    Object module_information_instance;
{
    Object gensymed_symbol, scope_conses, gensymed_symbol_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, system_table_classes;
    Object system_table_class, system_table_in_force_qm, new_system_table;
    Object new_system_table_suite, temp, system_table_suite, temp_1, elements;
    Object frame, symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(93,64);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qsystem_table,
	    Inferior_classes_gkbprop);
    scope_conses = Scope_conses;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol_1 = Nil;
      ab_loop_list_ = gensymed_symbol;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      gensymed_symbol_1 = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !EQ(gensymed_symbol_1,Qserver_parameters)) {
	  ab_loopvar__2 = scope_cons(gensymed_symbol_1,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop:
      system_table_classes = ab_loopvar_;
      goto end_1;
      system_table_classes = Qnil;
    end_1:;
      system_table_class = Nil;
      ab_loop_list_ = system_table_classes;
      system_table_in_force_qm = Nil;
      new_system_table = Nil;
      new_system_table_suite = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      system_table_class = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      system_table_in_force_qm = 
	      get_system_table_currently_in_force(system_table_class);
      if (EQ(system_table_class,Qmodule_information))
	  new_system_table = module_information_instance;
      else if (system_table_in_force_qm)
	  new_system_table = clone_system_frame(system_table_in_force_qm);
      else
	  new_system_table = make_system_frame(system_table_class);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(new_system_table,
		  Qmodule_system_table_belongs_to_qm);
      temp = ISVREF(module_information_instance,(SI_Long)23L);
      SVREF(new_system_table,FIX((SI_Long)21L)) = temp;
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(new_system_table,
		  Qthis_system_table_is_installed_qm);
      SVREF(new_system_table,FIX((SI_Long)20L)) = Nil;
      if (ISVREF(new_system_table,(SI_Long)8L))
	  change_slot_value(3,new_system_table,Qframe_status_and_notes,Nil);
      if (System_is_running || System_has_paused) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(new_system_table,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	  gensymed_symbol_1 = new_system_table;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      }
      ab_loopvar__1 = slot_value_cons_1(new_system_table,Nil);
      if (ab_loopvar_)
	  M_CDR(ab_loopvar_) = ab_loopvar__1;
      else
	  new_system_table_suite = ab_loopvar__1;
      ab_loopvar_ = ab_loopvar__1;
      goto next_loop_1;
    end_loop_1:
      system_table_suite = new_system_table_suite;
      temp_1 = CAR(system_table_suite);
      elements = system_table_suite;
    next_loop_2:
      if ( !TRUEP(elements))
	  goto end_loop_2;
      frame = CAR(elements);
      symbol = Qmodule_information;
      gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
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
	      gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		      sub_class_vector_index);
	      gensymed_symbol_3 = (SI_Long)1L;
	      gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	      gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	      gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	      temp_2 = (SI_Long)0L < gensymed_symbol_2;
	  }
	  else
	      temp_2 = TRUEP(Nil);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2) {
	  temp = CAR(elements);
	  M_CAR(system_table_suite) = temp;
	  M_CAR(elements) = temp_1;
	  goto end_2;
      }
      elements = M_CDR(elements);
      goto next_loop_2;
    end_loop_2:
    end_2:;
      Modules_and_system_tables_a_list = 
	      slot_value_cons_1(new_system_table_suite,
	      Modules_and_system_tables_a_list);
      update_module_related_frame_notes_for_all_workspaces(0);
    POP_SPECIAL();
    decache_dynamic_menus(1,Qab_modules);
    return inform_ui_client_interfaces_of_module_creation(module_information_instance);
}

/* GET-SYSTEM-TABLE-INSTANCE-FOR-MODULE */
Object get_system_table_instance_for_module(system_frame_subclass,module)
    Object system_frame_subclass, module;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, instance;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,65);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(system_frame_subclass);
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
      if (EQ(ISVREF(instance,(SI_Long)21L),module)) {
	  result = VALUES_1(instance);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qmodule_name_unspecified;  /* module-name-unspecified */

static Object Qmodule_name_in_use;  /* module-name-in-use */

static Object Qreserved_word_p;    /* reserved-word-p */

static Object Qmodule_name_is_reserved_word;  /* module-name-is-reserved-word */

static Object Qmodule_creation_failed_for_unknown_reason;  /* module-creation-failed-for-unknown-reason */

/* CREATE-NEW-MODULE */
Object create_new_module(module_name)
    Object module_name;
{
    Object module_information_instance, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, module_text;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(93,66);
    if (EQ(module_name,Qunspecified))
	return VALUES_1(Qmodule_name_unspecified);
    else if (module_exists_p(module_name))
	return VALUES_1(Qmodule_name_in_use);
    else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qreserved_word_p))
	return VALUES_1(Qmodule_name_is_reserved_word);
    else {
	module_information_instance = make_system_frame(Qmodule_information);
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
		  twrite_parsably(module_name);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	module_text = convert_text_string_to_text(temp);
	parse_text_for_slot(3,module_text,module_information_instance,
		get_slot_description_of_class_description_function(Qtop_level_kb_module_qm,
		ISVREF(module_information_instance,(SI_Long)1L),Nil));
	if (ISVREF(module_information_instance,(SI_Long)23L)) {
	    finish_setup_of_system_table_suite_for_new_module(module_information_instance);
	    return VALUES_1(module_information_instance);
	}
	else {
	    delete_frame(module_information_instance);
	    return VALUES_1(Qmodule_creation_failed_for_unknown_reason);
	}
    }
}

static Object Qstack_change;       /* stack-change */

static Object Qworkspaces_belong_to_unrequired_modules;  /* workspaces-belong-to-unrequired-modules */

static Object Qworkspaces_belong_to_non_existant_modules;  /* workspaces-belong-to-non-existant-modules */

static Object list_constant_10;    /* # */

static Object Qkb_workspace;       /* kb-workspace */

static Object list_constant_11;    /* # */

static Object Qmodules_that_exist_are_not_required;  /* modules-that-exist-are-not-required */

static Object Qmodule_exists_but_is_unknown;  /* module-exists-but-is-unknown */

static Object Qmodule_required_but_does_not_exist;  /* module-required-but-does-not-exist */

static Object Qmodules_required_by_kb_do_not_exist;  /* modules-required-by-kb-do-not-exist */

static Object Qmodule_is_empty;    /* module-is-empty */

static Object Qmodule_is_empty_but_that_is_ok;  /* module-is-empty-but-that-is-ok */

/* UPDATE-MODULE-RELATED-FRAME-NOTES-FOR-ALL-WORKSPACES */
Object update_module_related_frame_notes_for_all_workspaces varargs_1(int, n)
{
    Object specific_workspace_with_module_assignment_change_qm;
    Object old_module_assignment_of_specific_workspace_qm, slot_description;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, stack_of_slot_value_changes;
    Object suppress_updating_of_slot_value_representations_qm, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, kb_workspace;
    Object module_information_instance, module_qm, slot_description_1;
    Object required_module, ab_loop_list_, frame_and_slot_or_atom, ab_loop_it_;
    Object temp_2, stack_change_pop_store, cons_1, next_cons, temp_3;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(93,67);
    INIT_ARGS_nonrelocating();
    specific_workspace_with_module_assignment_change_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    old_module_assignment_of_specific_workspace_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if ( 
	    !TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm) 
	    &&  !TRUEP(Releasing_kb_qm)) {
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(Module_information,(SI_Long)1L),Nil);
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
		    nconc2(stack_change_list_2(Module_information,
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
	    temp = Module_information;
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
		3);
	  suppress_updating_of_slot_value_representations_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
		  2);
	    if (specific_workspace_with_module_assignment_change_qm) {
		if (old_module_assignment_of_specific_workspace_qm &&  
			!TRUEP(lookup_kb_specific_property_value(old_module_assignment_of_specific_workspace_qm,
			Workspaces_belonging_to_this_module_kbprop))) {
		    delete_from_frame_note_particulars_list(old_module_assignment_of_specific_workspace_qm,
			    Qworkspaces_belong_to_unrequired_modules,
			    Module_information);
		    delete_from_frame_note_particulars_list(old_module_assignment_of_specific_workspace_qm,
			    Qworkspaces_belong_to_non_existant_modules,
			    Module_information);
		}
	    }
	    else
		delete_multiple_frame_notes_if_any(list_constant_10,
			Module_information);
	    propagate_kb_requires_module_p_to_all_modules();
	    if (specific_workspace_with_module_assignment_change_qm)
		update_module_related_frame_notes_of_workspace(specific_workspace_with_module_assignment_change_qm);
	    else {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		kb_workspace = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
		      temp_1 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      goto end_loop_1;
		  kb_workspace = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  update_module_related_frame_notes_of_workspace(kb_workspace);
		  goto next_loop;
		end_loop_1:;
		POP_SPECIAL();
	    }
	    if ( !TRUEP(specific_workspace_with_module_assignment_change_qm))
		update_module_related_circularity_frame_notes();
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    module_information_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    1);
	      module_qm = Nil;
	      ab_loopvar_ = collect_subclasses(Qmodule_information);
	      delete_multiple_frame_notes_if_any(list_constant_11,
		      Module_information);
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
	      module_information_instance = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      module_qm = ISVREF(module_information_instance,(SI_Long)23L);
	      slot_description_1 = 
		      get_slot_description_of_class_description_function(Qframe_status_and_notes,
		      ISVREF(module_information_instance,(SI_Long)1L),Nil);
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
			  nconc2(stack_change_list_2(module_information_instance,
			  slot_description_1),stack_change_cons_1(Nil,Nil));
	      else {
		  new_cons = ISVREF(Available_stack_change_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp = Available_stack_change_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_stack_change_conses_vector,
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
		  M_CAR(gensymed_symbol_1) = module_information_instance;
		  M_CDR(gensymed_symbol_1) = slot_description_1;
		  inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	      }
	      M_CAR(gensymed_symbol) = gensymed_symbol_1;
	      temp = Stack_of_slot_value_changes;
	      M_CDR(gensymed_symbol) = temp;
	      inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	      stack_of_slot_value_changes = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		      0);
		if (module_qm &&  
			!TRUEP(ISVREF(module_information_instance,
			(SI_Long)25L))) {
		    add_to_frame_note_particulars_list_if_necessary(module_qm,
			    Qmodules_that_exist_are_not_required,
			    Module_information);
		    add_frame_note(2,Qmodule_exists_but_is_unknown,
			    module_information_instance);
		}
		else
		    delete_frame_note_if_any(Qmodule_exists_but_is_unknown,
			    module_information_instance);
		delete_frame_note_if_any(Qmodule_required_but_does_not_exist,
			module_information_instance);
		required_module = Nil;
		ab_loop_list_ = ISVREF(module_information_instance,
			(SI_Long)24L);
	      next_loop_4:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_4;
		required_module = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(module_exists_p(required_module))) {
		    add_to_frame_note_particulars_list_if_necessary(required_module,
			    Qmodule_required_but_does_not_exist,
			    module_information_instance);
		    add_to_frame_note_particulars_list_if_necessary(required_module,
			    Qmodules_required_by_kb_do_not_exist,
			    Module_information);
		}
		goto next_loop_4;
	      end_loop_4:;
		delete_frame_note_if_any(Qmodule_is_empty,
			module_information_instance);
		if (module_qm &&  
			!TRUEP(lookup_kb_specific_property_value(module_qm,
			Workspaces_belonging_to_this_module_kbprop))) {
		    add_frame_note(2,Qmodule_is_empty,
			    module_information_instance);
		    if ( !TRUEP(ISVREF(module_information_instance,
			    (SI_Long)25L)))
			add_to_frame_note_particulars_list_if_necessary(module_qm,
				Qmodule_is_empty_but_that_is_ok,
				Module_information);
		}
		temp_1 = 
			TRUEP(Suppress_updating_of_slot_value_representations_qm);
		if (temp_1);
		else if (M_CDR(Stack_of_slot_value_changes)) {
		    frame_and_slot_or_atom = Nil;
		    ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		    ab_loop_it_ = Nil;
		  next_loop_5:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_5;
		    frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (ATOM(frame_and_slot_or_atom))
			goto end_loop_5;
		    temp_1 = EQ(slot_description_1,
			    M_CDR(frame_and_slot_or_atom));
		    if (temp_1);
		    else {
			temp_2 = M_CDR(frame_and_slot_or_atom);
			temp_1 = CONSP(temp_2) ? EQ(slot_description_1,
				SECOND(frame_and_slot_or_atom)) && EQ(Nil,
				THIRD(frame_and_slot_or_atom)) && EQ(Nil,
				CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		    }
		    ab_loop_it_ = temp_1 ? (EQ(module_information_instance,
			    M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		    if (ab_loop_it_) {
			temp_1 = TRUEP(ab_loop_it_);
			goto end_1;
		    }
		    goto next_loop_5;
		  end_loop_5:
		    temp_1 = TRUEP(Qnil);
		  end_1:;
		}
		else
		    temp_1 = TRUEP(Nil);
		if ( !temp_1)
		    update_all_representations_of_slot(module_information_instance,
			    slot_description_1,Nil,Nil);
		if (ISVREF(slot_description_1,(SI_Long)14L))
		    update_frame_name_references(module_information_instance);
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
			!TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			: TRUEP(Nil))
		    do_deferred_updates_to_representations_in_tables();
	      POP_SPECIAL();
	      goto next_loop_2;
	    end_loop_3:
	      temp_2 = Qnil;
	    POP_SPECIAL();
	  POP_SPECIAL();
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop_6:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_6;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop_6;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_3 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_3) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(Module_information,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_2;
	      }
	      goto next_loop_6;
	    end_loop_6:
	      temp_1 = TRUEP(Qnil);
	    end_2:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(Module_information,
		      slot_description,Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(Module_information);
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
	      temp_1 = ATOM(temp_3);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	  result = VALUES_1(temp_2);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qcircularity_in_module_hierarchy;  /* circularity-in-module-hierarchy */

/* UPDATE-MODULE-RELATED-CIRCULARITY-FRAME-NOTES */
Object update_module_related_circularity_frame_notes()
{
    Object cycles_qm;

    x_note_fn_call(93,68);
    cycles_qm = find_all_cycles_in_module_hierarchy(Module_information);
    if (cycles_qm)
	return add_frame_note(5,Qcircularity_in_module_hierarchy,
		Module_information,cycles_qm,T,Nil);
    else
	return delete_frame_note_if_any(Qcircularity_in_module_hierarchy,
		Module_information);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_module_frame_notes_for_workspaces, Qall_module_frame_notes_for_workspaces);

static Object Qworkspace_does_not_belong_to_any_module;  /* workspace-does-not-belong-to-any-module */

static Object Qworkspaces_belong_to_unspecified_module;  /* workspaces-belong-to-unspecified-module */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object Qkb_workspace_assigned_to_unrequired_module;  /* kb-workspace-assigned-to-unrequired-module */

static Object Qkb_workspace_is_part_of_non_existant_module;  /* kb-workspace-is-part-of-non-existant-module */

/* UPDATE-MODULE-RELATED-FRAME-NOTES-OF-WORKSPACE */
Object update_module_related_frame_notes_of_workspace(kb_workspace)
    Object kb_workspace;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object module_qm, temp_1, module_information_instance_qm;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,69);
    if (ISVREF(kb_workspace,(SI_Long)18L)) {
	if (ISVREF(kb_workspace,(SI_Long)8L)) {
	    if (frame_has_note_p(kb_workspace,
		    Qworkspace_does_not_belong_to_any_module)) {
		if (ISVREF(Module_information,(SI_Long)23L) && 
			frame_has_note_p(Module_information,
			Qworkspaces_belong_to_unspecified_module))
		    delete_from_frame_note_particulars_list(kb_workspace,
			    Qworkspaces_belong_to_unspecified_module,
			    Module_information);
	    }
	    return delete_multiple_frame_notes_if_any(All_module_frame_notes_for_workspaces,
		    kb_workspace);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(kb_workspace,(SI_Long)1L),Nil);
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
	    gensymed_symbol_1 = nconc2(stack_change_list_2(kb_workspace,
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
	    M_CAR(gensymed_symbol_1) = kb_workspace;
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
	  module_qm = get_lookup_slot_value(kb_workspace,
		  Qmodule_this_is_part_of_qm);
	  delete_from_frame_note_particulars_list(kb_workspace,
		  Qworkspaces_belong_to_unspecified_module,Module_information);
	  if (ISVREF(kb_workspace,(SI_Long)8L))
	      delete_multiple_frame_notes_if_any(All_module_frame_notes_for_workspaces,
		      kb_workspace);
	  if ( !TRUEP(module_qm)) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(kb_workspace,
		      (SI_Long)5L)) & (SI_Long)512L))) {
		  if (ISVREF(Module_information,(SI_Long)23L)) {
		      add_to_frame_note_particulars_list_if_necessary(kb_workspace,
			      Qworkspaces_belong_to_unspecified_module,
			      Module_information);
		      temp_1 = add_frame_note(2,
			      Qworkspace_does_not_belong_to_any_module,
			      kb_workspace);
		  }
		  else
		      temp_1 = Nil;
	      }
	      else
		  temp_1 = Nil;
	  }
	  else {
	      module_information_instance_qm = 
		      lookup_kb_specific_property_value(module_qm,
		      Module_information_instance_for_module_qm_kbprop);
	      if ( !(module_information_instance_qm && 
		      ISVREF(module_information_instance_qm,(SI_Long)25L))) {
		  add_to_frame_note_particulars_list_if_necessary(module_qm,
			  Qworkspaces_belong_to_unrequired_modules,
			  Module_information);
		  add_to_frame_note_particulars_list_if_necessary(module_qm,
			  Qkb_workspace_assigned_to_unrequired_module,
			  kb_workspace);
	      }
	      if ( !TRUEP(module_information_instance_qm)) {
		  add_to_frame_note_particulars_list_if_necessary(module_qm,
			  Qworkspaces_belong_to_non_existant_modules,
			  Module_information);
		  temp_1 = 
			  add_to_frame_note_particulars_list_if_necessary(module_qm,
			  Qkb_workspace_is_part_of_non_existant_module,
			  kb_workspace);
	      }
	      else
		  temp_1 = Nil;
	  }
	  temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_2);
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
	      temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp_3 = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp_3) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(kb_workspace,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_2 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_2 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2)
	      update_all_representations_of_slot(kb_workspace,
		      slot_description,Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(kb_workspace);
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
	return result;
    }
}

/* GET-MODULES-THAT-REQUIRE-THIS-MODULE */
Object get_modules_that_require_this_module(target_module)
    Object target_module;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1;
    Object module_information_instance, module_qm, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,70);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    module_information_instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      module_qm = Nil;
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
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      module_information_instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      module_qm = ISVREF(module_information_instance,(SI_Long)23L);
      if (module_qm &&  !EQ(module_qm,target_module) && 
	      module_requires_module_p(module_qm,target_module)) {
	  ab_loopvar__4 = gensym_cons_1(module_qm,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(ab_loopvar__2);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* TOP-LEVEL-KB-MODULE-P */
Object top_level_kb_module_p(module)
    Object module;
{
    x_note_fn_call(93,71);
    return VALUES_1(EQ(Module_information,
	    lookup_kb_specific_property_value(module,
	    Module_information_instance_for_module_qm_kbprop)) ? T : Nil);
}

static Object string_constant_21;  /* "~%~%Warning: this module is ~arequired by the KB, ~a is ~
				    *           required directly or indirectly by "
				    */

static Object string_constant_22;  /* "not " */

static Object string_constant_23;  /* "and in particular" */

static Object string_constant_24;  /* "but" */

static Object string_constant_25;  /* "~L,&." */

/* TFORMAT-WARNING-ABOUT-MODULES-THAT-REQUIRE-THIS-IF-NECESSARY */
Object tformat_warning_about_modules_that_require_this_if_necessary(module)
    Object module;
{
    Object kb_requires_module_p_1, modules_that_require_this;

    x_note_fn_call(93,72);
    kb_requires_module_p_1 = kb_requires_module_p(module);
    modules_that_require_this = get_modules_that_require_this_module(module);
    if (modules_that_require_this &&  !TRUEP(top_level_kb_module_p(module))) {
	tformat(3,string_constant_21,kb_requires_module_p_1 ? 
		string_constant_19 : string_constant_22,
		kb_requires_module_p_1 ? string_constant_23 : 
		string_constant_24);
	tformat(2,string_constant_25,modules_that_require_this);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* KB-HAS-MODULARITY-INFORMATION-P */
Object kb_has_modularity_information_p()
{
    Object temp;

    x_note_fn_call(93,73);
    temp = ISVREF(Module_information,(SI_Long)23L);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(ISVREF(Module_information,(SI_Long)8L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Obsolete_frame_note_types_from_modularity_development, Qobsolete_frame_note_types_from_modularity_development);

static Object string_constant_26;  /* "the module ~a is not required by the KB" */

/* WRITE-KB-WORKSPACE-ASSIGNED-TO-UNREQUIRED-MODULE-NOTE */
Object write_kb_workspace_assigned_to_unrequired_module_note(listed_module,
	    kb_workspace)
    Object listed_module, kb_workspace;
{
    x_note_fn_call(93,74);
    GENSYM_RETURN_ONE(tformat(2,string_constant_26,FIRST(listed_module)));
    return VALUES_1(Nil);
}

static Object Qframe_note_writer_1;  /* frame-note-writer-1 */

/* WRITE-KB-WORKSPACE-IS-PART-OF-UNKNOWN-MODULE-NOTE */
Object write_kb_workspace_is_part_of_unknown_module_note(listed_module,
	    kb_workspace)
    Object listed_module, kb_workspace;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(93,75);
    gensymed_symbol = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qkb_workspace_assigned_to_unrequired_module),
	    Qframe_note_writer_1);
    gensymed_symbol = gensymed_symbol ? gensymed_symbol : Nil;
    gensymed_symbol_1 = listed_module;
    gensymed_symbol_2 = kb_workspace;
    GENSYM_RETURN_ONE(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
    return VALUES_1(Nil);
}

/* WRITE-KB-WORKSPACE-IS-PART-OF-UNREQUIRED-MODULE-NOTE */
Object write_kb_workspace_is_part_of_unrequired_module_note(listed_module,
	    kb_workspace)
    Object listed_module, kb_workspace;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(93,76);
    gensymed_symbol = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qkb_workspace_assigned_to_unrequired_module),
	    Qframe_note_writer_1);
    gensymed_symbol = gensymed_symbol ? gensymed_symbol : Nil;
    gensymed_symbol_1 = listed_module;
    gensymed_symbol_2 = kb_workspace;
    GENSYM_RETURN_ONE(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
    return VALUES_1(Nil);
}

static Object string_constant_27;  /* "the module ~a does not exist" */

/* WRITE-KB-WORKSPACE-IS-PART-OF-NON-EXISTANT-MODULE-NOTE */
Object write_kb_workspace_is_part_of_non_existant_module_note(listed_module,
	    kb_workspace)
    Object listed_module, kb_workspace;
{
    x_note_fn_call(93,77);
    GENSYM_RETURN_ONE(tformat(2,string_constant_27,FIRST(listed_module)));
    return VALUES_1(Nil);
}

static Object string_constant_28;  /* "the top-level module is ~a, but this workspace is not assigned to any module" */

/* WRITE-WORKSPACE-DOES-NOT-BELONG-TO-ANY-MODULE-NOTE */
Object write_workspace_does_not_belong_to_any_module_note(particulars,
	    kb_workspace)
    Object particulars, kb_workspace;
{
    x_note_fn_call(93,78);
    GENSYM_RETURN_ONE(tformat(2,string_constant_28,
	    get_slot_value_function(Module_information,
	    Qtop_level_kb_module_qm,Nil)));
    return VALUES_1(Nil);
}

static Object string_constant_29;  /* "~a workspace~a ~a not assigned to any module" */

static Object string_constant_30;  /* "s" */

static Object string_constant_31;  /* "is" */

static Object string_constant_32;  /* "are" */

static Object string_constant_33;  /* "its" */

static Object string_constant_34;  /* "their" */

/* WRITE-WORKSPACES-BELONG-TO-UNSPECIFIED-MODULE-NOTE */
Object write_workspaces_belong_to_unspecified_module_note(particulars,
	    top_level_module_information)
    Object particulars, top_level_module_information;
{
    Object number;

    x_note_fn_call(93,79);
    number = length(particulars);
    GENSYM_RETURN_ONE(tformat(5,string_constant_29,number,IFIX(number) == 
	    (SI_Long)1L ? string_constant_19 : string_constant_30,
	    IFIX(number) == (SI_Long)1L ? string_constant_31 : 
	    string_constant_32,IFIX(number) == (SI_Long)1L ? 
	    string_constant_33 : string_constant_34));
    return VALUES_1(Nil);
}

static Object string_constant_35;  /* "the module~a " */

static Object string_constant_36;  /* "," */

static Object string_constant_37;  /* "and" */

static Object string_constant_38;  /* " ~a workspaces assigned to ~a but ~a not required by the KB" */

static Object string_constant_39;  /* "has" */

static Object string_constant_40;  /* "have" */

static Object string_constant_41;  /* "it" */

static Object string_constant_42;  /* "them" */

/* WRITE-WORKSPACES-BELONG-TO-UNREQUIRED-MODULES-NOTE */
Object write_workspaces_belong_to_unrequired_modules_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object number, write_symbols_in_lower_case_qm;
    Declare_special(1);

    x_note_fn_call(93,80);
    number = length(problem_modules);
    tformat(2,string_constant_35,IFIX(number) == (SI_Long)1L ? 
	    string_constant_19 : string_constant_30);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      write_symbol_list(3,problem_modules,string_constant_36,
	      string_constant_37);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(tformat(4,string_constant_38,IFIX(number) == 
	    (SI_Long)1L ? string_constant_39 : string_constant_40,
	    IFIX(number) == (SI_Long)1L ? string_constant_41 : 
	    string_constant_42,IFIX(number) == (SI_Long)1L ? 
	    string_constant_31 : string_constant_32));
    return VALUES_1(Nil);
}

/* WRITE-WORKSPACES-BELONG-TO-UNKNOWN-MODULES-NOTE */
Object write_workspaces_belong_to_unknown_modules_note(problem_modules,
	    gensymed_symbol)
    Object problem_modules, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(93,81);
    gensymed_symbol = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qworkspaces_belong_to_unrequired_modules),
	    Qframe_note_writer_1);
    gensymed_symbol = gensymed_symbol ? gensymed_symbol : Nil;
    gensymed_symbol_1 = problem_modules;
    gensymed_symbol_2 = Nil;
    GENSYM_RETURN_ONE(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
    return VALUES_1(Nil);
}

static Object string_constant_43;  /* "this KB cannot be saved because the modules are not consistent" */

/* WRITE-KB-UNSAVABLE-DUE-TO-MODULE-INCONCISTENCY-NOTE */
Object write_kb_unsavable_due_to_module_inconcistency_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(93,82);
    GENSYM_RETURN_ONE(tformat(1,string_constant_43));
    return VALUES_1(Nil);
}

static Object string_constant_44;  /* "no workspaces are assigned to the module ~a" */

/* WRITE-MODULE-HAS-NO-WORKSPACES-ASSIGNED-TO-IT-NOTE */
Object write_module_has_no_workspaces_assigned_to_it_note(particulars,
	    module_information_instance)
    Object particulars, module_information_instance;
{
    Object write_symbols_in_lower_case_qm, temp;
    Declare_special(1);

    x_note_fn_call(93,83);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      temp = tformat(2,string_constant_44,
	      ISVREF(module_information_instance,(SI_Long)23L));
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_45;  /* " do~a not exist, but workspaces are assigned to ~a" */

static Object string_constant_46;  /* "es" */

/* WRITE-WORKSPACES-BELONG-TO-NON-EXISTANT-MODULES-NOTE */
Object write_workspaces_belong_to_non_existant_modules_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object number, write_symbols_in_lower_case_qm;
    Declare_special(1);

    x_note_fn_call(93,84);
    number = length(problem_modules);
    tformat(2,string_constant_35,IFIX(number) == (SI_Long)1L ? 
	    string_constant_19 : string_constant_30);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      write_symbol_list(3,problem_modules,string_constant_36,
	      string_constant_37);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(tformat(3,string_constant_45,IFIX(number) == 
	    (SI_Long)1L ? string_constant_46 : string_constant_19,
	    IFIX(number) == (SI_Long)1L ? string_constant_41 : 
	    string_constant_42));
    return VALUES_1(Nil);
}

static Object string_constant_47;  /* "there are workspaces assigned to the module ~a, but it is not required by the KB" */

/* WRITE-MODULE-NOT-REQUIRED-BUT-HAS-WORKSPACES-ASSIGNED-TO-IT-NOTE */
Object write_module_not_required_but_has_workspaces_assigned_to_it_note(particulars,
	    module_information_instance)
    Object particulars, module_information_instance;
{
    x_note_fn_call(93,85);
    GENSYM_RETURN_ONE(tformat(2,string_constant_47,
	    ISVREF(module_information_instance,(SI_Long)23L)));
    return VALUES_1(Nil);
}

/* WRITE-MODULE-EXISTS-BUT-IS-UNKNOWN-NOTE */
Object write_module_exists_but_is_unknown_note(particulars,
	    module_information_instance)
    Object particulars, module_information_instance;
{
    x_note_fn_call(93,86);
    GENSYM_RETURN_ONE(tformat(2,string_constant_26,
	    ISVREF(module_information_instance,(SI_Long)23L)));
    return VALUES_1(Nil);
}

static Object string_constant_48;  /* " exist~a but ~a not required by the KB" */

/* WRITE-MODULES-THAT-EXIST-ARE-NOT-REQUIRED-NOTE */
Object write_modules_that_exist_are_not_required_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object number, write_symbols_in_lower_case_qm, temp;
    Declare_special(1);

    x_note_fn_call(93,87);
    number = length(problem_modules);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      tformat(2,string_constant_35,IFIX(number) == (SI_Long)1L ? 
	      string_constant_19 : string_constant_30);
      write_symbol_list(3,problem_modules,string_constant_36,
	      string_constant_37);
      temp = tformat(3,string_constant_48,IFIX(number) == (SI_Long)1L ? 
	      string_constant_30 : string_constant_19,IFIX(number) == 
	      (SI_Long)1L ? string_constant_31 : string_constant_32);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-MODULES-THAT-EXIST-ARE-UNKNOWN-NOTE */
Object write_modules_that_exist_are_unknown_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(93,88);
    gensymed_symbol = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmodules_that_exist_are_not_required),
	    Qframe_note_writer_1);
    gensymed_symbol = gensymed_symbol ? gensymed_symbol : Nil;
    gensymed_symbol_1 = problem_modules;
    gensymed_symbol_2 = top_level_module_information;
    GENSYM_RETURN_ONE(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
    return VALUES_1(Nil);
}

/* WRITE-MODULE-IS-EMPTY-NOTE */
Object write_module_is_empty_note(particulars,module_information_instance)
    Object particulars, module_information_instance;
{
    x_note_fn_call(93,89);
    GENSYM_RETURN_ONE(tformat(2,string_constant_44,
	    ISVREF(module_information_instance,(SI_Long)23L)));
    return VALUES_1(Nil);
}

static Object string_constant_49;  /* "no workspaces are assigned to the module~a " */

static Object string_constant_50;  /* ", but since ~a ~a not required by this KB, it is probably best to ~
				    *        delete ~a module~a"
				    */

static Object string_constant_51;  /* "they" */

static Object string_constant_52;  /* "this" */

static Object string_constant_53;  /* "these" */

/* WRITE-MODULE-IS-EMPTY-BUT-THAT-IS-OK-NOTE */
Object write_module_is_empty_but_that_is_ok_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object number, write_symbols_in_lower_case_qm, temp;
    Declare_special(1);

    x_note_fn_call(93,90);
    number = length(problem_modules);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      tformat(2,string_constant_49,IFIX(number) == (SI_Long)1L ? 
	      string_constant_19 : string_constant_30);
      write_symbol_list(2,problem_modules,Nil);
      temp = tformat(5,string_constant_50,IFIX(number) == (SI_Long)1L ? 
	      string_constant_41 : string_constant_51,IFIX(number) == 
	      (SI_Long)1L ? string_constant_31 : string_constant_32,
	      IFIX(number) == (SI_Long)1L ? string_constant_52 : 
	      string_constant_53,IFIX(number) == (SI_Long)1L ? 
	      string_constant_19 : string_constant_30);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_54;  /* " ~a required here but do~a not exist" */

/* WRITE-MODULE-REQUIRED-BUT-DOES-NOT-EXIST-NOTE */
Object write_module_required_but_does_not_exist_note(problem_modules,
	    module_information_instance)
    Object problem_modules, module_information_instance;
{
    Object number, write_symbols_in_lower_case_qm, temp;
    Declare_special(1);

    x_note_fn_call(93,91);
    number = length(problem_modules);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      tformat(2,string_constant_35,IFIX(number) == (SI_Long)1L ? 
	      string_constant_19 : string_constant_30);
      write_symbol_list(3,problem_modules,string_constant_36,
	      string_constant_37);
      temp = tformat(3,string_constant_54,IFIX(number) == (SI_Long)1L ? 
	      string_constant_31 : string_constant_32,IFIX(number) == 
	      (SI_Long)1L ? string_constant_46 : string_constant_19);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_55;  /* " ~a required by the KB but do~a not exist" */

/* WRITE-MODULES-REQUIRED-BY-KB-DO-NOT-EXIST-NOTE */
Object write_modules_required_by_kb_do_not_exist_note(problem_modules,
	    top_level_module_information)
    Object problem_modules, top_level_module_information;
{
    Object number, write_symbols_in_lower_case_qm, temp;
    Declare_special(1);

    x_note_fn_call(93,92);
    number = length(problem_modules);
    write_symbols_in_lower_case_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      tformat(2,string_constant_35,IFIX(number) == (SI_Long)1L ? 
	      string_constant_19 : string_constant_30);
      write_symbol_list(3,problem_modules,string_constant_36,
	      string_constant_37);
      temp = tformat(3,string_constant_55,IFIX(number) == (SI_Long)1L ? 
	      string_constant_31 : string_constant_32,IFIX(number) == 
	      (SI_Long)1L ? string_constant_46 : string_constant_19);
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_56;  /* "the module hierarchy has the following ~a~acycle~a: " */

static Object string_constant_57;  /* " " */

static Object string_constant_58;  /* "--" */

static Object string_constant_59;  /* "; " */

/* WRITE-CIRCULARITY-IN-MODULE-HIERARCHY-NOTE */
Object write_circularity_in_module_hierarchy_note(cycles_qm,
	    top_level_module_information)
    Object cycles_qm, top_level_module_information;
{
    Object write_symbols_in_lower_case_qm, cycle, more_qm, ab_loop_list_, temp;
    Declare_special(1);

    x_note_fn_call(93,93);
    if (cycles_qm) {
	tformat(4,string_constant_56,CDR(cycles_qm) ? length(cycles_qm) : 
		string_constant_19,CDR(cycles_qm) ? string_constant_57 : 
		string_constant_19,CDR(cycles_qm) ? string_constant_30 : 
		string_constant_19);
	write_symbols_in_lower_case_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		0);
	  cycle = Nil;
	  more_qm = Nil;
	  ab_loop_list_ = cycles_qm;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  cycle = CAR(ab_loop_list_);
	  more_qm = CDR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  write_symbol_list(2,cycle,string_constant_58);
	  tformat(1,string_constant_58);
	  twrite_symbol(2,CAR(cycle), 
		  !TRUEP(Write_symbols_in_lower_case_qm) ? T : Nil);
	  if (more_qm)
	      tformat(1,string_constant_59);
	  goto next_loop;
	end_loop:
	  temp = Qnil;
	POP_SPECIAL();
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CHECK-MODULE-DEFINITION-CONSISTENCY */
Object check_module_definition_consistency(module)
    Object module;
{
    x_note_fn_call(93,94);
    return VALUES_1(Nil);
}

Object Format_string_for_kb_modularity_problem_prop = UNBOUND;

Object Format_args_for_kb_modularity_problem_prop = UNBOUND;

Object Particulars_printer_for_kb_modularity_problem_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Modularity_checking, Qmodularity_checking);

DEFINE_VARIABLE_WITH_SYMBOL(Current_modularity_problems, Qcurrent_modularity_problems);

DEFINE_VARIABLE_WITH_SYMBOL(Inspect_command_for_modularity_problems_qm, Qinspect_command_for_modularity_problems_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_modularity_problems_fatal_qm, Qcurrent_modularity_problems_fatal_qm);

/* RECLAIM-MODULARITY-PROBLEMS */
Object reclaim_modularity_problems()
{
    x_note_fn_call(93,95);
    return reclaim_gensym_tree_1(Current_modularity_problems);
}

static Object Qfatal;              /* fatal */

static Object Qadvisory;           /* advisory */

/* EMIT-KB-MODULARITY-PROBLEM */
Object emit_kb_modularity_problem varargs_1(int, n)
{
    Object seriousness, problem_name;
    Object listed_particulars_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(93,96);
    INIT_ARGS_nonrelocating();
    seriousness = REQUIRED_ARG_nonrelocating();
    problem_name = REQUIRED_ARG_nonrelocating();
    listed_particulars_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    Current_modularity_problems = gensym_cons_1(listed_particulars_qm,
	    Current_modularity_problems);
    Current_modularity_problems = gensym_cons_1(problem_name,
	    Current_modularity_problems);
    if (EQ(seriousness,Qfatal)) {
	Current_modularity_problems_fatal_qm = T;
	return VALUES_1(Current_modularity_problems_fatal_qm);
    }
    else if (EQ(seriousness,Qadvisory))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

static Object Qformat_string_for_kb_modularity_problem;  /* format-string-for-kb-modularity-problem */

static Object Qformat_args_for_kb_modularity_problem;  /* format-args-for-kb-modularity-problem */

static Object Qparticulars_printer_for_kb_modularity_problem;  /* particulars-printer-for-kb-modularity-problem */

static Object Qtformat_text_string;  /* tformat-text-string */

static Object Qnotify_user;        /* notify-user */

/* REPORT-ON-MODULARITY-CHECKING */
Object report_on_modularity_checking()
{
    Object inspect_messages, problem, listed_particulars, ab_loop_list_;
    Object format_string_qm, format_args_qm, particulars_printer_qm, temp;

    x_note_fn_call(93,97);
    inspect_messages = Qnil;
    problem = Nil;
    listed_particulars = Nil;
    ab_loop_list_ = Current_modularity_problems;
    format_string_qm = Nil;
    format_args_qm = Nil;
    particulars_printer_qm = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    problem = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    listed_particulars = CAR(temp);
    format_string_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(problem),
	    Qformat_string_for_kb_modularity_problem);
    format_args_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(problem),
	    Qformat_args_for_kb_modularity_problem);
    particulars_printer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(problem),
	    Qparticulars_printer_for_kb_modularity_problem);
    if (format_string_qm) {
	if (Inspect_command_for_modularity_problems_qm) {
	    temp = SYMBOL_FUNCTION(Qtformat_text_string);
	    temp = APPLY_2(temp,format_string_qm,format_args_qm);
	    inspect_messages = eval_cons_1(temp,inspect_messages);
	}
	else {
	    temp = SYMBOL_FUNCTION(Qnotify_user);
	    APPLY_2(temp,format_string_qm,format_args_qm);
	}
    }
    if (particulars_printer_qm)
	FUNCALL_1(particulars_printer_qm,listed_particulars);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    if (Inspect_command_for_modularity_problems_qm) {
	temp = nreverse(inspect_messages);
	multiple_add_to_results_for_inspect_command(temp,
		Inspect_command_for_modularity_problems_qm);
    }
    return VALUES_1(Qnil);
}

/* CHECK-FRAME-NOTE-BASED-MODULARITY-PROBLEMS */
Object check_frame_note_based_modularity_problems(seriousness,note_names)
    Object seriousness, note_names;
{
    Object note_name, ab_loop_list_;

    x_note_fn_call(93,98);
    note_name = Nil;
    ab_loop_list_ = note_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    note_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    check_one_frame_note_based_modularity_problem(seriousness,note_name);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHECK-ONE-FRAME-NOTE-BASED-MODULARITY-PROBLEM */
Object check_one_frame_note_based_modularity_problem(seriousness,note_name)
    Object seriousness, note_name;
{
    x_note_fn_call(93,99);
    if (frame_has_note_p(Module_information,note_name))
	return emit_kb_modularity_problem(2,seriousness,note_name);
    else
	return VALUES_1(Nil);
}

static Object string_constant_60;  /* "These class definitions are not assigned to any module." */

static Object string_constant_61;  /* "The following classes are not assigned to any module: ~L,&" */

static Object string_constant_62;  /* "There are ~d classes that are not assigned to any module." */

/* PRINT-CLASSES-NOT-DEFINED-IN-ANY-MODULE */
Object print_classes_not_defined_in_any_module(classes)
    Object classes;
{
    Object items, class_1, ab_loop_list_, class_definition, temp;

    x_note_fn_call(93,100);
    if (Inspect_command_for_modularity_problems_qm) {
	items = eval_cons_1(tformat_text_string(1,string_constant_60),Nil);
	class_1 = Nil;
	ab_loop_list_ = classes;
	class_definition = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_definition = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	items = eval_cons_1(class_definition,items);
	goto next_loop;
      end_loop:
	temp = nreverse(items);
	multiple_add_to_results_for_inspect_command(temp,
		Inspect_command_for_modularity_problems_qm);
	return VALUES_1(Qnil);
    }
    else if (IFIX(length(classes)) < (SI_Long)100L)
	return notify_user(2,string_constant_61,classes);
    else
	return notify_user(2,string_constant_62,length(classes));
}

static Object string_constant_63;  /* "These class definitions do not have their superior assigned to their module hierarchy." */

static Object string_constant_64;  /* "The following classes do not have their superior assigned to their module hierarchy: ~L,&" */

static Object string_constant_65;  /* "There are ~d classes that do not have their superior assigned to their module hierarchy." */

/* PRINT-CLASSES-WHOSE-SUPERIORS-ARE-NOT-DEFINED-IN-REQUIRED-MODULES */
Object print_classes_whose_superiors_are_not_defined_in_required_modules(classes)
    Object classes;
{
    Object items, class_1, ab_loop_list_, class_definition, temp;

    x_note_fn_call(93,101);
    if (Inspect_command_for_modularity_problems_qm) {
	items = eval_cons_1(tformat_text_string(1,string_constant_63),Nil);
	class_1 = Nil;
	ab_loop_list_ = classes;
	class_definition = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_definition = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	items = eval_cons_1(class_definition,items);
	goto next_loop;
      end_loop:
	temp = nreverse(items);
	multiple_add_to_results_for_inspect_command(temp,
		Inspect_command_for_modularity_problems_qm);
	return VALUES_1(Qnil);
    }
    else if (IFIX(length(classes)) < (SI_Long)100L)
	return notify_user(2,string_constant_64,classes);
    else
	return notify_user(2,string_constant_65,length(classes));
}

static Object string_constant_66;  /* "These class definitions are not in the module hierarchy of the indicated instances." */

static Object string_constant_67;  /* "The class ~a has ~a instance~a that do~a not reside in any module that ~
				    *                     requires the module of the class (~a)."
				    */

/* PRINT-CLASSES-WITH-INSTANCES-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM */
Object print_classes_with_instances_in_modules_that_do_not_require_them(a_list_of_classes)
    Object a_list_of_classes;
{
    Object items, class_1, instances, ab_loop_list_, class_definition;
    Object ab_loop_desetq_, instance, ab_loop_list__1, temp, number, temp_1;
    Object temp_2, temp_3;

    x_note_fn_call(93,102);
    if (Inspect_command_for_modularity_problems_qm) {
	items = eval_cons_1(tformat_text_string(1,string_constant_66),Nil);
	class_1 = Nil;
	instances = Nil;
	ab_loop_list_ = a_list_of_classes;
	class_definition = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	class_1 = CAR(ab_loop_desetq_);
	instances = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_definition = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	items = eval_cons_1(class_definition,items);
	instance = Nil;
	ab_loop_list__1 = instances;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	instance = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	items = eval_cons_1(instance,items);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	temp = nreverse(items);
	multiple_add_to_results_for_inspect_command(temp,
		Inspect_command_for_modularity_problems_qm);
	return VALUES_1(Qnil);
    }
    else {
	class_1 = Nil;
	instances = Nil;
	ab_loop_list_ = a_list_of_classes;
	number = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	class_1 = CAR(ab_loop_desetq_);
	instances = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	number = length(instances);
	temp = class_1;
	temp_1 = number;
	temp_2 = IFIX(number) == (SI_Long)1L ? string_constant_19 : 
		string_constant_30;
	temp_3 = IFIX(number) == (SI_Long)1L ? string_constant_46 : 
		string_constant_19;
	notify_user(6,string_constant_67,temp,temp_1,temp_2,temp_3,
		get_module_block_is_in(lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop)));
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_68;  /* "~NF has a table on workspace ~NF, which does not ~
				    *                  belong to the same module.  Tables must reside in ~
				    *                  the same module as the item they represent."
				    */

static Object string_constant_69;  /* "~NF has a table on workspace ~NF, which does not ~
				    *              belong to the same module.  Tables must reside in ~
				    *              the same module as the item they represent. This KB will ~
				    *              not be savable until this problem is resolved."
				    */

/* PRINT-TABLE-IN-DIFFERENT-MODULE-THAN-ITEM-REPRESENTED */
Object print_table_in_different_module_than_item_represented(listed_represented_frame_and_workspace)
    Object listed_represented_frame_and_workspace;
{
    Object represented_frame, workspace, temp;

    x_note_fn_call(93,103);
    represented_frame = FIRST(listed_represented_frame_and_workspace);
    workspace = SECOND(listed_represented_frame_and_workspace);
    if (Inspect_command_for_modularity_problems_qm) {
	temp = eval_cons_1(tformat_text_string(3,string_constant_68,
		represented_frame,workspace),Nil);
	return multiple_add_to_results_for_inspect_command(temp,
		Inspect_command_for_modularity_problems_qm);
    }
    else
	return notify_user(3,string_constant_69,represented_frame,workspace);
}

/* UNMARK-ALL-MODULE-INFORMATION-INSTANCES */
Object unmark_all_module_information_instances()
{
    Object ab_loopvar_, module_information_instance;
    SI_Long svref_new_value;

    x_note_fn_call(93,104);
    ab_loopvar_ = lookup_kb_specific_property_value(Qmodule_information,
	    Instances_specific_to_this_class_kbprop);
    module_information_instance = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    module_information_instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    svref_new_value = IFIX(ISVREF(module_information_instance,
	    (SI_Long)5L)) &  ~(SI_Long)32L;
    ISVREF(module_information_instance,(SI_Long)5L) = FIX(svref_new_value);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_cycles_found_so_far_in_module_hierarchy, Qall_cycles_found_so_far_in_module_hierarchy);

/* MODULE-HIERARCHY-CONTAINS-CYCLIC-DEPENDENCY-P */
Object module_hierarchy_contains_cyclic_dependency_p(module_information_instance)
    Object module_information_instance;
{
    Object all_cycles_found_so_far_in_module_hierarchy, result_1, temp;
    Declare_special(1);

    x_note_fn_call(93,105);
    if (module_information_instance) {
	all_cycles_found_so_far_in_module_hierarchy = Qnil;
	result_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(All_cycles_found_so_far_in_module_hierarchy,Qall_cycles_found_so_far_in_module_hierarchy,all_cycles_found_so_far_in_module_hierarchy,
		0);
	  find_all_cycles_in_module_hierarchy_1(module_information_instance,
		  Nil);
	  unmark_all_module_information_instances();
	  result_1 =  ! 
		  !TRUEP(All_cycles_found_so_far_in_module_hierarchy) ? T :
		   Nil;
	  reclaim_slot_value_tree_1(All_cycles_found_so_far_in_module_hierarchy);
	  temp = result_1;
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FIND-ALL-CYCLES-IN-MODULE-HIERARCHY */
Object find_all_cycles_in_module_hierarchy(module_information_instance)
    Object module_information_instance;
{
    Object all_cycles_found_so_far_in_module_hierarchy, cycle, ab_loop_list_;
    Object l, car_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,106);
    all_cycles_found_so_far_in_module_hierarchy = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(All_cycles_found_so_far_in_module_hierarchy,Qall_cycles_found_so_far_in_module_hierarchy,all_cycles_found_so_far_in_module_hierarchy,
	    0);
      find_all_cycles_in_module_hierarchy_1(module_information_instance,Nil);
      unmark_all_module_information_instances();
      cycle = Nil;
      ab_loop_list_ = All_cycles_found_so_far_in_module_hierarchy;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      cycle = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      l = cycle;
    next_loop_1:
      if ( !TRUEP(l))
	  goto end_loop_1;
      car_new_value = ISVREF(CAR(l),(SI_Long)23L);
      M_CAR(l) = car_new_value;
      l = M_CDR(l);
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:;
      result = VALUES_1(All_cycles_found_so_far_in_module_hierarchy);
    POP_SPECIAL();
    return result;
}

/* FIND-ALL-CYCLES-IN-MODULE-HIERARCHY-1 */
Object find_all_cycles_in_module_hierarchy_1(node,history_path)
    Object node, history_path;
{
    Object name_for_node_2, ab_loop_list_, node_2_qm, cycle_qm, temp;
    Object temporary_list_history_path_and_node;
    SI_Long svref_new_value;

    x_note_fn_call(93,107);
    svref_new_value = IFIX(ISVREF(node,(SI_Long)5L)) | (SI_Long)32L;
    ISVREF(node,(SI_Long)5L) = FIX(svref_new_value);
    name_for_node_2 = Nil;
    ab_loop_list_ = ISVREF(node,(SI_Long)24L);
    node_2_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name_for_node_2 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    node_2_qm = lookup_kb_specific_property_value(name_for_node_2,
	    Module_information_instance_for_module_qm_kbprop);
    if (node_2_qm) {
	cycle_qm = node_2_qm ? memq_function(node_2_qm,history_path) : Nil;
	if (cycle_qm) {
	    temp = nconc2(copy_list_using_slot_value_conses_1(cycle_qm),
		    slot_value_cons_1(node,Nil));
	    All_cycles_found_so_far_in_module_hierarchy = 
		    slot_value_cons_1(temp,
		    All_cycles_found_so_far_in_module_hierarchy);
	}
	else if ( !((SI_Long)0L != (IFIX(ISVREF(node_2_qm,(SI_Long)5L)) & 
		(SI_Long)32L))) {
	    temporary_list_history_path_and_node = 
		    nconc2(copy_list_using_slot_value_conses_1(history_path),
		    slot_value_cons_1(node,Nil));
	    find_all_cycles_in_module_hierarchy_1(node_2_qm,
		    temporary_list_history_path_and_node);
	    reclaim_slot_value_list_1(temporary_list_history_path_and_node);
	}
    }
    goto next_loop;
  end_loop:;
    return find_trivial_root_to_root_cycle_if_any(node);
}

/* FIND-TRIVIAL-ROOT-TO-ROOT-CYCLE-IF-ANY */
Object find_trivial_root_to_root_cycle_if_any(module_information_instance)
    Object module_information_instance;
{
    x_note_fn_call(93,108);
    if (memq_function(ISVREF(module_information_instance,(SI_Long)23L),
	    ISVREF(module_information_instance,(SI_Long)24L))) {
	All_cycles_found_so_far_in_module_hierarchy = 
		slot_value_cons_1(slot_value_cons_1(module_information_instance,
		Nil),All_cycles_found_so_far_in_module_hierarchy);
	return VALUES_1(All_cycles_found_so_far_in_module_hierarchy);
    }
    else
	return VALUES_1(Nil);
}

/* WITHIN-MODULE-HIERARCHY-P */
Object within_module_hierarchy_p(block,module)
    Object block, module;
{
    Object module_block_is_in_qm, temp;

    x_note_fn_call(93,109);
    module_block_is_in_qm = get_module_block_is_in(block);
    if (module_block_is_in_qm) {
	temp = EQ(module_block_is_in_qm,module) ? T : Nil;
	if (temp);
	else
	    temp = module_requires_module_p(module,module_block_is_in_qm);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-MODULE-BLOCK-IS-WITHIN-IF-REQUIRED */
Object get_module_block_is_within_if_required(block,module)
    Object block, module;
{
    Object module_block_is_in_qm, temp;

    x_note_fn_call(93,110);
    module_block_is_in_qm = get_module_block_is_in(block);
    temp = module_block_is_in_qm ? module_requires_module_p(module,
	    module_block_is_in_qm) : Qnil;
    return VALUES_1(temp);
}

/* WITHIN-MODULES-P */
Object within_modules_p(block,list_of_modules)
    Object block, list_of_modules;
{
    Object temp;

    x_note_fn_call(93,111);
    temp = memq_function(get_module_block_is_in(block),list_of_modules);
    return VALUES_1(temp);
}

/* ADD-OR-DELETE-AS-WORKSPACE-BELONGING-TO-MODULE */
Object add_or_delete_as_workspace_belonging_to_module(kb_workspace,module,
	    delete_case_qm)
    Object kb_workspace, module, delete_case_qm;
{
    Object temp, slot_value_modify_macro_using_test_arg_1, car_1, cdr_1;
    Object key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object workspaces_belonging_to_this_module_new_value;
    char temp_1;

    x_note_fn_call(93,112);
    if (delete_case_qm) {
	temp = delete_slot_value_element_1(kb_workspace,
		lookup_kb_specific_property_value(module,
		Workspaces_belonging_to_this_module_kbprop));
	return mutate_kb_specific_property_value(module,temp,
		Workspaces_belonging_to_this_module_kbprop);
    }
    else {
	slot_value_modify_macro_using_test_arg_1 = kb_workspace;
	car_1 = slot_value_modify_macro_using_test_arg_1;
	cdr_1 = lookup_kb_specific_property_value(module,
		Workspaces_belonging_to_this_module_kbprop);
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
	workspaces_belonging_to_this_module_new_value = temp_1 ? cdr_1 : 
		slot_value_cons_1(car_1,cdr_1);
	return mutate_kb_specific_property_value(module,
		workspaces_belonging_to_this_module_new_value,
		Workspaces_belonging_to_this_module_kbprop);
    }
}

/* MODULE-EXISTS-P */
Object module_exists_p(module)
    Object module;
{
    Object temp;

    x_note_fn_call(93,113);
    temp = lookup_kb_specific_property_value(module,
	    Module_information_instance_for_module_qm_kbprop);
    return VALUES_1(temp);
}

/* KB-REQUIRES-MODULE-P */
Object kb_requires_module_p(module)
    Object module;
{
    Object temp;

    x_note_fn_call(93,114);
    temp = EQ(module,ISVREF(Module_information,(SI_Long)23L)) ? T : Nil;
    if (temp);
    else {
	temp = module_required_p_1(module,Module_information);
	unmark_all_module_information_instances();
    }
    return VALUES_1(temp);
}

/* MODULE-REQUIRES-MODULE-P */
Object module_requires_module_p(module_1,module_2)
    Object module_1, module_2;
{
    Object module_information_instance_qm, temp;

    x_note_fn_call(93,115);
    module_information_instance_qm = 
	    lookup_kb_specific_property_value(module_1,
	    Module_information_instance_for_module_qm_kbprop);
    temp = module_information_instance_qm ? module_required_p_1(module_2,
	    module_information_instance_qm) : Nil;
    unmark_all_module_information_instances();
    return VALUES_1(temp);
}

/* MODULE-REQUIRED-P-1 */
Object module_required_p_1(module,node)
    Object module, node;
{
    Object directly_required_module, ab_loop_list_, ab_loop_it_, temp;
    Object module_information_instance_qm;
    SI_Long svref_new_value;

    x_note_fn_call(93,116);
    svref_new_value = IFIX(ISVREF(node,(SI_Long)5L)) | (SI_Long)32L;
    ISVREF(node,(SI_Long)5L) = FIX(svref_new_value);
    directly_required_module = Nil;
    ab_loop_list_ = ISVREF(node,(SI_Long)24L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directly_required_module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = EQ(module,directly_required_module) ? T : Nil;
    if (temp);
    else {
	module_information_instance_qm = 
		lookup_kb_specific_property_value(directly_required_module,
		Module_information_instance_for_module_qm_kbprop);
	temp = module_information_instance_qm &&  !((SI_Long)0L != 
		(IFIX(ISVREF(module_information_instance_qm,(SI_Long)5L)) 
		& (SI_Long)32L)) ? module_required_p_1(module,
		module_information_instance_qm) : Qnil;
    }
    ab_loop_it_ = temp;
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

/* PROPAGATE-KB-REQUIRES-MODULE-P-TO-ALL-MODULES */
Object propagate_kb_requires_module_p_to_all_modules()
{
    Object svref_arg_1;

    x_note_fn_call(93,117);
    propagate_module_requires_module_p_to_all_modules(ISVREF(Module_information,
	    (SI_Long)23L));
    svref_arg_1 = Module_information;
    ISVREF(svref_arg_1,(SI_Long)25L) = T;
    return VALUES_1(Nil);
}

/* PROPAGATE-MODULE-REQUIRES-MODULE-P-TO-ALL-MODULES */
Object propagate_module_requires_module_p_to_all_modules(module)
    Object module;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1;
    Object module_information_instance, instance_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(93,118);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    module_information_instance = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      module_information_instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ISVREF(module_information_instance,(SI_Long)25L) = Nil;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    instance_qm = lookup_kb_specific_property_value(module,
	    Module_information_instance_for_module_qm_kbprop);
    if (instance_qm)
	propagate_cached_module_is_required_p_1(instance_qm);
    return VALUES_1(Nil);
}

/* PROPAGATE-CACHED-MODULE-IS-REQUIRED-P-1 */
Object propagate_cached_module_is_required_p_1(module_information_instance)
    Object module_information_instance;
{
    Object module, ab_loop_list_, instance_qm;

    x_note_fn_call(93,119);
    module = Nil;
    ab_loop_list_ = ISVREF(module_information_instance,(SI_Long)24L);
    instance_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    instance_qm = lookup_kb_specific_property_value(module,
	    Module_information_instance_for_module_qm_kbprop);
    if (instance_qm &&  !TRUEP(ISVREF(instance_qm,(SI_Long)25L))) {
	ISVREF(instance_qm,(SI_Long)25L) = T;
	if (ISVREF(instance_qm,(SI_Long)24L))
	    propagate_cached_module_is_required_p_1(instance_qm);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MODULE-RELATIONSHIP-KEY-EQUAL */
Object module_relationship_key_equal(key_1,key_2)
    Object key_1, key_2;
{
    Object temp;

    x_note_fn_call(93,120);
    temp = EQ(M_CAR(key_1),M_CAR(key_2)) ? (EQ(M_CDR(key_1),M_CDR(key_2)) ?
	     T : Nil) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_module_required_by_relationships_hash_vector_43_vectors, Qavailable_module_required_by_relationships_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_module_required_by_relationships_hash_vector_43_vectors, Qcount_of_module_required_by_relationships_hash_vector_43_vectors);

Object Available_module_required_by_relationships_hash_vector_43_vectors_vector = UNBOUND;

/* MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object module_required_by_relationships_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(93,121);
    temp = Count_of_module_required_by_relationships_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTORS */
Object out_module_required_by_relationships_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(93,122);
    temp = 
	    FIXNUM_MINUS(Count_of_module_required_by_relationships_hash_vector_43_vectors,
	    length(Available_module_required_by_relationships_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_module_required_by_relationships_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(93,123);
    atomic_incff_symval(Qcount_of_module_required_by_relationships_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR */
Object make_module_required_by_relationships_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(93,124);
    if (ISVREF(Available_module_required_by_relationships_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_module_required_by_relationships_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_module_required_by_relationships_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_module_required_by_relationships_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_module_required_by_relationships_hash_vector_43_vectors_vector,
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
		make_permanent_module_required_by_relationships_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR */
Object reclaim_module_required_by_relationships_hash_vector(module_required_by_relationships_hash_vector_43_vector)
    Object module_required_by_relationships_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(93,125);
    svref_arg_1 = 
	    Available_module_required_by_relationships_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = 
	    module_required_by_relationships_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_module_required_by_relationships_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-MODULE-REQUIRED-BY-RELATIONSHIPS-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_module_required_by_relationships_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(93,126);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-MODULE-REQUIRED-BY-RELATIONSHIPS-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_module_required_by_relationships_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(93,127);
    reclaim_gensym_cons_1(ISVREF(node,(SI_Long)2L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_module_required_by_relationships_tree_for_hash_skip_list_entry = UNBOUND;

static Object Qmodule_relationship_key_equal;  /* module-relationship-key-equal */

/* CLEAR-MODULE-REQUIRED-BY-RELATIONSHIPS-TREE */
Object clear_module_required_by_relationships_tree(module_required_by_relationships_tree_for_hash_skip_list)
    Object module_required_by_relationships_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_key;

    x_note_fn_call(93,128);
    head = 
	    M_CAR(M_CDR(module_required_by_relationships_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(module_required_by_relationships_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    temp = 
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qmodule_relationship_key_equal),
	    temp,module_required_by_relationships_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),sxhashw(key_qm));
    old_key = temp;
    if (old_key)
	reclaim_gensym_cons_1(old_key);
    goto next_loop;
  end_loop:;
    return VALUES_1(module_required_by_relationships_tree_for_hash_skip_list);
}

static Object Qmodule_required_by_relationships_tree_for_hash;  /* module-required-by-relationships-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-MODULE-REQUIRED-BY-RELATIONSHIPS */
Object make_module_required_by_relationships()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(93,129);
    new_vector = make_module_required_by_relationships_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_module_required_by_relationships_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_module_required_by_relationships_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qmodule_required_by_relationships_tree_for_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
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

/* FLATTEN-MODULE-REQUIRED-BY-RELATIONSHIPS */
Object flatten_module_required_by_relationships(module_required_by_relationships_hash_table)
    Object module_required_by_relationships_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(93,130);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(module_required_by_relationships_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-MODULE-REQUIRED-BY-RELATIONSHIPS */
Object clear_module_required_by_relationships(module_required_by_relationships_hash_table)
    Object module_required_by_relationships_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(93,131);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_module_required_by_relationships_tree(ISVREF(module_required_by_relationships_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-MODULE-REQUIRED-BY-RELATIONSHIPS */
Object reclaim_module_required_by_relationships(module_required_by_relationships_hash_table)
    Object module_required_by_relationships_hash_table;
{
    Object module_required_by_relationships_tree_for_hash_skip_list, head;
    Object tail, element_qm, key_qm, temp, old_key, last_1, next_qm, temp_1;
    Object svref_arg_2;
    SI_Long index_1;

    x_note_fn_call(93,132);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    module_required_by_relationships_tree_for_hash_skip_list = 
	    ISVREF(module_required_by_relationships_hash_table,index_1);
    head = 
	    M_CAR(M_CDR(module_required_by_relationships_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(module_required_by_relationships_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    temp = 
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qmodule_relationship_key_equal),
	    temp,module_required_by_relationships_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),sxhashw(key_qm));
    old_key = temp;
    if (old_key)
	reclaim_gensym_cons_1(old_key);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(module_required_by_relationships_tree_for_hash_skip_list) = Nil;
    M_CADR(module_required_by_relationships_tree_for_hash_skip_list) = Nil;
    M_CAR(module_required_by_relationships_tree_for_hash_skip_list) = Nil;
    if (module_required_by_relationships_tree_for_hash_skip_list) {
	last_1 = module_required_by_relationships_tree_for_hash_skip_list;
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
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = 
		    module_required_by_relationships_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    module_required_by_relationships_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(module_required_by_relationships_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_module_required_by_relationships_hash_vector(module_required_by_relationships_hash_table);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Module_required_by_relationships, Qmodule_required_by_relationships);

/* PROPAGATE-MODULES-TO-SUBWORKSPACES */
Object propagate_modules_to_subworkspaces()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace, temp_1, temp_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,133);
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
      if ((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)4L)) & (SI_Long)1L)) {
	  temp_1 = ISVREF(workspace,(SI_Long)3L);
	  temp_2 = FIX((SI_Long)-1L);
	  temp =  !EQUAL(temp_1,temp_2);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  set_module_for_workspace(workspace);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SET-MODULE-FOR-WORKSPACE */
Object set_module_for_workspace(workspace)
    Object workspace;
{
    Object temp;

    x_note_fn_call(93,134);
    temp = get_lookup_slot_value(workspace,Qmodule_this_is_part_of_qm);
    if (temp)
	return VALUES_1(temp);
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qmodule_this_is_part_of_qm);
	return set_lookup_slot_value_1(workspace,
		Qmodule_this_is_part_of_qm,get_module_block_is_in(workspace));
    }
}

/* UNPROPAGATE-MODULES-TO-SUBWORKSPACES */
Object unpropagate_modules_to_subworkspaces()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,135);
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
      if ((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)4L)) & (SI_Long)1L)) {
	  if (ISVREF(workspace,(SI_Long)18L)) {
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(workspace,Qmodule_this_is_part_of_qm);
	      set_lookup_slot_value_1(workspace,Qmodule_this_is_part_of_qm,
		      Nil);
	  }
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* EFFICIENT-GET-MODULE-BLOCK-IS-IN */
Object efficient_get_module_block_is_in(block)
    Object block;
{
    Object superior_qm, temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(93,136);
    superior_qm = block;
  next_loop:
    if ( !TRUEP(superior_qm)) {
	temp = get_module_block_is_in(block);
	goto end_1;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(superior_qm,(SI_Long)1L),
		(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = get_lookup_slot_value(superior_qm,
		    Qmodule_this_is_part_of_qm);
	    goto end_1;
	}
    }
    superior_qm = superior_frame(superior_qm);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object string_constant_70;  /* "No module named ~a was found." */

static Object string_constant_71;  /* ", the top-level module," */

static Object string_constant_72;  /* "Module ~a~a is being deleted with its associated set of system tables~a. ~a" */

static Object string_constant_73;  /* " as well as its associated set of workspaces" */

static Object string_constant_74;  /* " A new set of system tables is being installed." */

/* DO-DELETION-OF-MODULE-AFTER-CONFIRMATION */
Object do_deletion_of_module_after_confirmation(module,
	    also_delete_assigned_workspaces_qm)
    Object module, also_delete_assigned_workspaces_qm;
{
    Object system_table_suite_qm;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object temp;
    Declare_special(1);

    x_note_fn_call(93,137);
    system_table_suite_qm = get_system_table_suite_for_module_or_nil(module);
    if ( !TRUEP(system_table_suite_qm)) {
	notify_user(2,string_constant_70,module);
	return VALUES_1(Nil);
    }
    else {
	inhibit_updating_module_related_frame_notes_for_all_workspaces_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		0);
	  temp = system_table_installed_p(FIRST(system_table_suite_qm)) ? 
		  string_constant_71 : string_constant_19;
	  notify_user(5,string_constant_72,module,temp,
		  also_delete_assigned_workspaces_qm ? string_constant_73 :
		   string_constant_19,
		  system_table_installed_p(FIRST(system_table_suite_qm)) ? 
		  string_constant_74 : string_constant_19);
	  if (also_delete_assigned_workspaces_qm)
	      delete_workspaces_of_module(module);
	  if (system_table_installed_p(FIRST(system_table_suite_qm)))
	      delete_top_level_module();
	  else
	      delete_system_table_suite(1,system_table_suite_qm);
	  temp = T;
	POP_SPECIAL();
	if ( 
		!TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm))
	    update_module_related_frame_notes_for_all_workspaces(0);
	return VALUES_1(temp);
    }
}

static Object Qclass_definition;   /* class-definition */

/* DELETE-WORKSPACES-OF-MODULE */
Object delete_workspaces_of_module(module)
    Object module;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, workspaces_belonging_to_this_module;
    Object definition, workspace_qm, frame_reference_serial_number;
    Object ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;
    Declare_special(1);

    x_note_fn_call(93,138);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
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
      if (EQ(get_module_block_is_in(workspace),module)) {
	  ab_loopvar__4 = gensym_cons_1(workspace,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      workspaces_belonging_to_this_module = ab_loopvar__2;
      goto end_1;
      workspaces_belonging_to_this_module = Qnil;
    end_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      workspace_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qclass_definition);
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
      definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      workspace_qm = get_workspace_if_any(definition);
      if ( !TRUEP(workspace_qm) && EQ(get_module_block_is_in(definition),
	      module))
	  delete_frame(definition);
      goto next_loop_2;
    end_loop_3:;
    POP_SPECIAL();
    frame_reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    workspace = Nil;
    ab_loop_list_ = workspaces_belonging_to_this_module;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    workspace = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,(SI_Long)1L),
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
    if ( !temp)
	delete_frame(workspace);
    goto next_loop_4;
  end_loop_4:
    reclaim_frame_serial_number(frame_reference_serial_number);
    return reclaim_gensym_list_1(workspaces_belonging_to_this_module);
}

/* DELETE-TOP-LEVEL-MODULE */
Object delete_top_level_module()
{
    Object installed_suite, module_information_instance, new_suite;

    x_note_fn_call(93,139);
    installed_suite = find_currently_installed_system_table_suite();
    module_information_instance = make_system_frame(Qmodule_information);
    new_suite = slot_value_cons_1(module_information_instance,Nil);
    return merge_in_system_table_suite_read_in(3,new_suite,T,installed_suite);
}

DEFINE_VARIABLE_WITH_SYMBOL(Module_search_path_tokenizer, Qmodule_search_path_tokenizer);

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* GET-G2-MODULE-SEARCH-PATH-STRING-FROM-ENVIRONMENT-OR-COMMAND-LINE */
Object get_g2_module_search_path_string_from_environment_or_command_line()
{
    Object thing, temp;

    x_note_fn_call(93,140);
    thing = get_command_line_keyword_argument(1,array_constant_2);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    copy_text_string(thing) : thing;
    if (temp);
    else {
	thing = get_command_line_keyword_argument(1,array_constant_3);
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
		copy_text_string(thing) : thing;
    }
    if (temp)
	return VALUES_1(temp);
    else
	return get_gensym_environment_variable(array_constant_4);
}

/* GET-G2-MODULE-SEARCH-PATH-AS-TOKEN-LIST-OF-TEXTS */
Object get_g2_module_search_path_as_token_list_of_texts()
{
    Object search_path_string_qm, token_list_of_text_strings;

    x_note_fn_call(93,141);
    search_path_string_qm = 
	    get_g2_module_search_path_string_from_environment_or_command_line();
    token_list_of_text_strings = 
	    tokenize_text_string(search_path_string_qm,
	    Module_search_path_tokenizer);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(search_path_string_qm) != (SI_Long)0L)
	reclaim_wide_string(search_path_string_qm);
    return VALUES_1(token_list_of_text_strings);
}

/* LIST-OF-TEXT-STRINGS->LIST-OF-PATHNAMES */
Object list_of_text_strings_gt_list_of_pathnames(list_of_text_strings)
    Object list_of_text_strings;
{
    Object text_string, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(93,142);
    text_string = Nil;
    ab_loop_list_ = list_of_text_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = gensym_file_as_directory(text_string);
    if (temp);
    else
	temp = gensym_pathname(text_string);
    ab_loopvar__2 = token_cons_1(temp,Nil);
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
    return VALUES_1(temp);
}

/* LIST-OF-PATHNAMES->LIST-OF-TEXT-STRINGS */
Object list_of_pathnames_gt_list_of_text_strings(list_of_pathnames)
    Object list_of_pathnames;
{
    Object pathname_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(93,143);
    pathname_1 = Nil;
    ab_loop_list_ = list_of_pathnames;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pathname_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = slot_value_cons_1(gensym_namestring(1,pathname_1),Nil);
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
    return VALUES_1(temp);
}

/* GET-INITIAL-VALUE-FOR-G2-MODULE-SEARCH-PATH */
Object get_initial_value_for_g2_module_search_path()
{
    Object token_list, list_of_pathnames;

    x_note_fn_call(93,144);
    token_list = get_g2_module_search_path_as_token_list_of_texts();
    list_of_pathnames = list_of_text_strings_gt_list_of_pathnames(token_list);
    reclaim_token_list_1(token_list);
    return VALUES_1(list_of_pathnames);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_module_search_path, Qg2_module_search_path);

DEFINE_VARIABLE_WITH_SYMBOL(G2_module_file_name_map, Qg2_module_file_name_map);

/* PARSE-MODULE-MAP-LINE-INTO-PARTS */
Object parse_module_map_line_into_parts(module_map_line)
    Object module_map_line;
{
    Object list_of_strings, module_name_qm, gensym_pathname_qm;
    Object converted_gensym_pathname_qm, temp, string_qm, ab_loop_list_;

    x_note_fn_call(93,145);
    list_of_strings = 
	    parse_space_delimited_text_line_into_list_of_text_strings(module_map_line);
    if (list_of_strings) {
	module_name_qm = read_symbol_from_text_string(1,
		FIRST(list_of_strings));
	gensym_pathname_qm = text_string_p(SECOND(list_of_strings)) ? 
		gensym_parse_namestring_function(SECOND(list_of_strings),
		Nil,Nil) : Nil;
	converted_gensym_pathname_qm = gensym_pathname_qm ? 
		gensym_pathname(gensym_pathname_qm) : Nil;
	if (gensym_pathname_qm)
	    reclaim_gensym_pathname(gensym_pathname_qm);
	if (module_name_qm && converted_gensym_pathname_qm)
	    temp = gensym_list_2(module_name_qm,converted_gensym_pathname_qm);
	else {
	    if (converted_gensym_pathname_qm)
		reclaim_gensym_pathname(converted_gensym_pathname_qm);
	    temp = Nil;
	}
	string_qm = Nil;
	ab_loop_list_ = list_of_strings;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	string_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (string_qm)
	    reclaim_text_string(string_qm);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(list_of_strings);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

Object Gensym_pathname_for_module_kbprop = UNBOUND;

Object Default_pathname_for_module_kbprop = UNBOUND;

Object Module_is_writable_p_kbprop = UNBOUND;

Object Module_is_locked_p_kbprop = UNBOUND;

Object Reason_module_is_not_editable_kbprop = UNBOUND;

Object Module_uses_crlf_p_kbprop = UNBOUND;

Object Initial_plist_for_loaded_module_prop = UNBOUND;

/* SET-GENSYM-PATHNAME-FOR-MODULE */
Object set_gensym_pathname_for_module(module_name,new_value)
    Object module_name, new_value;
{
    Object temp;

    x_note_fn_call(93,146);
    reclaim_if_gensym_pathname(lookup_kb_specific_property_value(module_name,
	    Gensym_pathname_for_module_kbprop));
    temp = copy_gensym_pathname(new_value);
    mutate_kb_specific_property_value(module_name,temp,
	    Gensym_pathname_for_module_kbprop);
    update_saving_parameters_status_attributes(1,module_name);
    return VALUES_1(new_value);
}

/* SET-DEFAULT-PATHNAME-FOR-MODULE */
Object set_default_pathname_for_module(module_name,new_value)
    Object module_name, new_value;
{
    Object temp;

    x_note_fn_call(93,147);
    reclaim_if_gensym_pathname(lookup_kb_specific_property_value(module_name,
	    Default_pathname_for_module_kbprop));
    temp = new_value ? copy_gensym_pathname(new_value) : Nil;
    temp = mutate_kb_specific_property_value(module_name,temp,
	    Default_pathname_for_module_kbprop);
    return VALUES_1(temp);
}

static Object Qunknown;            /* unknown */

/* SET-REASON-MODULE-IS-NOT-EDITABLE */
Object set_reason_module_is_not_editable(module_name,new_value)
    Object module_name, new_value;
{
    Object thing;

    x_note_fn_call(93,148);
    thing = lookup_kb_specific_property_value(module_name,
	    Reason_module_is_not_editable_kbprop);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    mutate_kb_specific_property_value(module_name,new_value,
	    Reason_module_is_not_editable_kbprop);
    if ( !EQ(Qunknown,new_value))
	update_saving_parameters_status_attributes(1,module_name);
    return VALUES_1(new_value);
}

static Object Qinitial_plist_for_loaded_module;  /* initial-plist-for-loaded-module */

/* SET-INITIAL-PLIST-FOR-LOADED-MODULE */
Object set_initial_plist_for_loaded_module(module_name,new_value)
    Object module_name, new_value;
{
    Object temp;

    x_note_fn_call(93,149);
    reclaim_slot_value(getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qinitial_plist_for_loaded_module));
    temp = mutate_global_property(module_name,new_value,
	    Qinitial_plist_for_loaded_module);
    return VALUES_1(temp);
}

/* GET-TRUE-PATHNAME-OF-MODULE-IF-ANY */
Object get_true_pathname_of_module_if_any(module_name)
    Object module_name;
{
    x_note_fn_call(93,150);
    return lookup_kb_specific_property_value(module_name,
	    Gensym_pathname_for_module_kbprop);
}

/* SET-TRUE-PATHNAME-OF-MODULE */
Object set_true_pathname_of_module(module_name,true_pathname,
	    default_pathname_qm)
    Object module_name, true_pathname, default_pathname_qm;
{
    x_note_fn_call(93,151);
    if ( !TRUEP(lookup_kb_specific_property_value(module_name,
	    Default_pathname_for_module_kbprop)))
	set_default_pathname_for_module(module_name,default_pathname_qm);
    return set_gensym_pathname_for_module(module_name,true_pathname);
}

/* GET-ENOUGH-PATHNAME-OF-MODULE-LOADED-IF-ANY */
Object get_enough_pathname_of_module_loaded_if_any(module_name)
    Object module_name;
{
    Object default_pathname_qm, enough_namestring_1, temp;

    x_note_fn_call(93,152);
    default_pathname_qm = lookup_kb_specific_property_value(module_name,
	    Default_pathname_for_module_kbprop);
    if (default_pathname_qm) {
	enough_namestring_1 = gensym_enough_namestring(2,
		lookup_kb_specific_property_value(module_name,
		Gensym_pathname_for_module_kbprop),default_pathname_qm);
	temp = gensym_pathname(enough_namestring_1);
	reclaim_text_string(enough_namestring_1);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_uses_crlf_p, Qkb_uses_crlf_p);

/* NOTE-CRLF-USE-IN-MODULE-OR-FILE */
Object note_crlf_use_in_module_or_file(module,kb_uses_crlf_p)
    Object module, kb_uses_crlf_p;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,153);
    PUSH_SPECIAL_WITH_SYMBOL(Kb_uses_crlf_p,Qkb_uses_crlf_p,kb_uses_crlf_p,0);
      result = mutate_kb_specific_property_value(module,Kb_uses_crlf_p,
	      Module_uses_crlf_p_kbprop);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Server_parameters, Qserver_parameters);

Object Default_g2_window_style = UNBOUND;

static Object Qdefault_window_style;  /* default-window-style */

/* GET-INITIAL-WINDOW-STYLE */
Object get_initial_window_style()
{
    Object temp;

    x_note_fn_call(93,154);
    temp = getf(Command_line_arguments,Qdefault_window_style,_);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_style_if_other_than_default, Qcurrent_style_if_other_than_default);

/* GET-WORKSTATION-G2-WINDOW-STYLE-IN-FORCE */
Object get_workstation_g2_window_style_in_force(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(93,155);
    temp = ISVREF(workstation,(SI_Long)50L);
    if (temp);
    else
	temp = get_kb_default_window_style_override_if_any();
    if (temp);
    else
	temp = Current_style_if_other_than_default;
    if (temp);
    else
	temp = Default_g2_window_style;
    return VALUES_1(temp);
}

/* RESET-CURRENT-WORKSTATION-NEW-G2-CLASSIC-UI-P */
Object reset_current_workstation_new_g2_classic_ui_p()
{
    x_note_fn_call(93,156);
    New_g2_classic_ui_p = 
	    get_value_for_current_workstation_new_g2_classic_ui_p();
    return VALUES_1(New_g2_classic_ui_p);
}

static Object Qg2_5_dot_x;         /* g2-5.x */

/* GET-VALUE-FOR-CURRENT-WORKSTATION-NEW-G2-CLASSIC-UI-P */
Object get_value_for_current_workstation_new_g2_classic_ui_p()
{
    Object style;

    x_note_fn_call(93,157);
    style = get_workstation_g2_window_style_in_force(Current_workstation);
    if (EQ(style,Qg2_5_dot_x))
	return VALUES_1(Nil);
    else
	return VALUES_1(style);
}

DEFINE_VARIABLE_WITH_SYMBOL(Miscellaneous_parameters, Qmiscellaneous_parameters);

/* GET-KB-DEFAULT-WINDOW-STYLE-OVERRIDE-IF-ANY */
Object get_kb_default_window_style_override_if_any()
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(93,158);
    if (BOUNDP(Qmiscellaneous_parameters) && Miscellaneous_parameters) {
	if (SIMPLE_VECTOR_P(Miscellaneous_parameters) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Miscellaneous_parameters)) 
		> (SI_Long)2L &&  !EQ(ISVREF(Miscellaneous_parameters,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(Miscellaneous_parameters,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? get_slot_value_function(Miscellaneous_parameters,
	    Qdefault_window_style,Nil) : Nil;
    return VALUES_1(temp_1);
}

/* GET-STYLE-FOR-CURRENT-WORKSTATION-IF-ANY */
Object get_style_for_current_workstation_if_any()
{
    Object temp;

    x_note_fn_call(93,159);
    temp = Servicing_workstation_qm ? ISVREF(Current_workstation,
	    (SI_Long)50L) : Nil;
    return VALUES_1(temp);
}

static Object string_constant_75;  /* "-default-window-style" */

/* COMMAND-LINE-PROCESS-DEFAULT-WINDOW-STYLE */
Object command_line_process_default_window_style(value_qm)
    Object value_qm;
{
    x_note_fn_call(93,160);
    if (value_qm)
	return validate_window_style_command_line_argument(value_qm,
		string_constant_75);
    else
	return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object Qcommand_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEFAULT-WINDOW-STYLE */
Object get_command_line_plist_element_for_default_window_style()
{
    Object value_qm, temp;

    x_note_fn_call(93,161);
    value_qm = get_command_line_keyword_argument(1,array_constant_5);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdefault_window_style),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* WRITE-MODULE-SEARCH-PATH-FROM-SLOT */
Object write_module_search_path_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object path_list;

    x_note_fn_call(93,162);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	path_list = value;
      next_loop:
	if ( !TRUEP(path_list))
	    goto end_loop;
	tprin(CAR(path_list),T);
	if (CDR(path_list))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	path_list = M_CDR(path_list);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Source_code_control_support_enabled_p, Qsource_code_control_support_enabled_p);

DEFINE_VARIABLE_WITH_SYMBOL(Restrict_edits_to_modules_having_read_only_files_p, Qrestrict_edits_to_modules_having_read_only_files_p);

static Object Qmodule_search_path;  /* module-search-path */

static Object Qsource_code_control_support_is_enabled;  /* source-code-control-support-is-enabled */

static Object Qrestrict_edits_to_read_only_files;  /* restrict-edits-to-read-only-files */

static Object Qcurrent_style_if_other_than_default_qm;  /* current-style-if-other-than-default? */

/* INITIALIZE-FOR-SERVER-PARAMETERS */
Object initialize_for_server_parameters(server_parameters)
    Object server_parameters;
{
    Object frame, sub_vector_qm, method_function_qm, temp;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,163);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      frame = Server_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qserver_parameters)) {
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
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,Qmodule_search_path);
      temp = Server_parameters;
      set_lookup_slot_value_1(temp,Qmodule_search_path,
	      list_of_pathnames_gt_list_of_text_strings(G2_module_search_path));
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qsource_code_control_support_is_enabled);
      set_lookup_slot_value_1(Server_parameters,
	      Qsource_code_control_support_is_enabled,
	      Source_code_control_support_enabled_p);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qrestrict_edits_to_read_only_files);
      set_lookup_slot_value_1(Server_parameters,
	      Qrestrict_edits_to_read_only_files,
	      Restrict_edits_to_modules_having_read_only_files_p);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qcurrent_style_if_other_than_default_qm);
      result = set_lookup_slot_value_1(Server_parameters,
	      Qcurrent_style_if_other_than_default_qm,
	      Current_style_if_other_than_default);
    POP_SPECIAL();
    return result;
}

/* PUT-MODULE-SEARCH-PATH */
Object put_module_search_path(server_parameters,new_path_list,initializing_qm)
    Object server_parameters, new_path_list, initializing_qm;
{
    Object gensym_pathname_1, ab_loop_list_, str, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(93,164);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      if ( !(initializing_qm || Called_within_clear_text_loading)) {
	  gensym_pathname_1 = Nil;
	  ab_loop_list_ = G2_module_search_path;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  gensym_pathname_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  reclaim_gensym_pathname(gensym_pathname_1);
	  goto next_loop;
	end_loop:;
	  reclaim_token_list_1(G2_module_search_path);
	  G2_module_search_path = EQ(new_path_list,Qnone) ? Nil : 
		  list_of_text_strings_gt_list_of_pathnames(new_path_list);
      }
      if (CONSP(new_path_list)) {
	  str = Nil;
	  ab_loop_list_ = new_path_list;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  str = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  reclaim_text_string(str);
	  goto next_loop_1;
	end_loop_1:
	  reclaim_slot_value_list_1(new_path_list);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,Qmodule_search_path);
      temp = Server_parameters;
      result = set_lookup_slot_value_1(temp,Qmodule_search_path,
	      list_of_pathnames_gt_list_of_text_strings(G2_module_search_path));
    POP_SPECIAL();
    return result;
}

/* PUT-SOURCE-CODE-CONTROL-SUPPORT-IS-ENABLED */
Object put_source_code_control_support_is_enabled(server_parameters,
	    new_value,initializing_qm)
    Object server_parameters, new_value, initializing_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,165);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      if ( !(initializing_qm || Called_within_clear_text_loading))
	  Source_code_control_support_enabled_p = new_value;
      if (Source_code_control_support_enabled_p)
	  add_source_code_control_grammar();
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qsource_code_control_support_is_enabled);
      set_lookup_slot_value_1(Server_parameters,
	      Qsource_code_control_support_is_enabled,
	      Source_code_control_support_enabled_p);
      enable_scc_check();
      recompute_editability_of_modules();
      update_saving_parameters_status_attributes(1,Qstar);
      result = VALUES_1(new_value);
    POP_SPECIAL();
    return result;
}

/* PUT-RESTRICT-EDITS-TO-READ-ONLY-FILES */
Object put_restrict_edits_to_read_only_files(server_parameters,new_value,
	    initializing_qm)
    Object server_parameters, new_value, initializing_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,166);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      if ( !(initializing_qm || Called_within_clear_text_loading))
	  Restrict_edits_to_modules_having_read_only_files_p = new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qrestrict_edits_to_read_only_files);
      set_lookup_slot_value_1(Server_parameters,
	      Qrestrict_edits_to_read_only_files,
	      Restrict_edits_to_modules_having_read_only_files_p);
      recompute_editability_of_modules();
      result = VALUES_1(new_value);
    POP_SPECIAL();
    return result;
}

/* PUT-CURRENT-STYLE-IF-OTHER-THAN-DEFAULT? */
Object put_current_style_if_other_than_default_qm(server_parameters,
	    new_value,initializing_qm)
    Object server_parameters, new_value, initializing_qm;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(93,167);
    PUSH_SPECIAL_WITH_SYMBOL(Server_parameters,Qserver_parameters,server_parameters,
	    0);
      if ( !(initializing_qm || Called_within_clear_text_loading))
	  Current_style_if_other_than_default = new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Server_parameters,
		  Qcurrent_style_if_other_than_default_qm);
      set_lookup_slot_value_1(Server_parameters,
	      Qcurrent_style_if_other_than_default_qm,
	      Current_style_if_other_than_default);
      result = VALUES_1(Current_style_if_other_than_default);
    POP_SPECIAL();
    return result;
}

void modules_INIT()
{
    Object temp, temp_1, temp_2, module_file_name_qm_evaluation_setter_1;
    Object module_file_name_qm_evaluation_getter_1;
    Object module_annotations_evaluation_setter_1;
    Object module_annotations_evaluation_getter_1;
    Object module_name_for_module_information_qm_evaluation_setter_1;
    Object module_name_for_module_information_qm_evaluation_getter_1;
    Object list_of_modules_qm_evaluation_setter_1;
    Object list_of_modules_qm_evaluation_getter_1;
    Object write_kb_workspace_assigned_to_unrequired_module_note_1;
    Object write_kb_workspace_is_part_of_unknown_module_note_1;
    Object write_kb_workspace_is_part_of_unrequired_module_note_1;
    Object write_kb_workspace_is_part_of_non_existant_module_note_1;
    Object write_workspace_does_not_belong_to_any_module_note_1;
    Object write_workspaces_belong_to_unspecified_module_note_1;
    Object write_workspaces_belong_to_unrequired_modules_note_1;
    Object write_workspaces_belong_to_unknown_modules_note_1;
    Object write_kb_unsavable_due_to_module_inconcistency_note_1;
    Object write_module_has_no_workspaces_assigned_to_it_note_1;
    Object write_workspaces_belong_to_non_existant_modules_note_1;
    Object write_module_not_required_but_has_workspaces_assigned_to_it_note_1;
    Object write_module_exists_but_is_unknown_note_1;
    Object write_modules_that_exist_are_not_required_note_1;
    Object write_modules_that_exist_are_unknown_note_1;
    Object write_module_is_empty_note_1;
    Object write_module_is_empty_but_that_is_ok_note_1;
    Object write_module_required_but_does_not_exist_note_1;
    Object write_modules_required_by_kb_do_not_exist_note_1;
    Object write_circularity_in_module_hierarchy_note_1;
    Object named_dynamic_extent_description;
    Object Qslot_putter, Qput_current_style_if_other_than_default_qm;
    Object AB_package, Qput_restrict_edits_to_read_only_files;
    Object Qput_source_code_control_support_is_enabled;
    Object Qput_module_search_path, Qclasses_which_define, Qinitialize;
    Object Qinitialize_for_server_parameters, Qslot_value_writer;
    Object Qwrite_module_search_path_from_slot, list_constant_33;
    Object Qcommand_line_plist_element_getter;
    Object Qget_command_line_plist_element_for_default_window_style;
    Object list_constant_22, Qcommand_line_process_default_window_style;
    Object list_constant_32, Qget_initial_window_style, Kfuncall, Qab_standard;
    Object string_constant_109, string_constant_108, Qg2_window_style;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, list_constant_15, string_constant_103;
    Object string_constant_102, string_constant_85, Qmodule_uses_crlf_p;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qreason_module_is_not_editable;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_if_text_string_function, Qmodule_is_locked_p;
    Object Qmodule_is_writable_p, Qdefault_pathname_for_module;
    Object Qreclaim_if_gensym_pathname, Qgensym_pathname_for_module;
    Object list_constant_31, Qget_initial_value_for_g2_module_search_path;
    Object Qmutate_module_required_by_relationships_tree_for_hash_skip_list_entry;
    Object Qout_module_required_by_relationships_hash_vector_43_vectors;
    Object Qmodule_required_by_relationships_hash_vector_43_vector_memory_usage;
    Object string_constant_101, Qutilities2;
    Object Qprint_table_in_different_module_than_item_represented;
    Object Qtable_in_different_module_than_item_represented;
    Object Qprint_classes_with_instances_in_modules_that_do_not_require_them;
    Object Qclasses_with_instances_in_modules_that_do_not_require_them;
    Object Qprint_classes_whose_superiors_are_not_defined_in_required_modules;
    Object Qprint_classes_not_defined_in_any_module, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, Qnamed_dynamic_extent_description;
    Object string_constant_95, Qmodules_that_exist_are_unknown;
    Object list_constant_30;
    Object Qmodule_not_required_but_has_workspaces_assigned_to_it;
    Object Qmodule_has_no_workspaces_assigned_to_it;
    Object Qkb_unsavable_due_to_module_inconcistency;
    Object Qworkspaces_belong_to_unknown_modules, list_constant_29;
    Object Qkb_workspace_is_part_of_unrequired_module, list_constant_28;
    Object Qkb_workspace_is_part_of_unknown_module, list_constant_27;
    Object list_constant_26, Qreclaim_gensym_list_function;
    Object Qslot_value_reclaimer, Qreclaim_directly_required_kb_modules_value;
    Object Qput_directly_required_kb_modules, Qlist_of_modules_qm, Qnamed;
    Object list_constant_25, Qab_or, list_constant_24, list_constant_23;
    Object Qtype_specification_simple_expansion;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_list_of_modules_qm_for_slot;
    Object Qwrite_list_of_modules_qm_from_slot;
    Object Qmodule_name_for_module_information_qm, list_constant_16;
    Object Qwrite_module_name_for_module_information_qm_from_slot;
    Object Qcompile_module_name_for_module_information_qm_for_slot;
    Object string_constant_94, Qreclaim_top_level_kb_module_qm_value;
    Object Qput_top_level_kb_module_qm;
    Object Qmodule_information_instance_for_module_qm;
    Object Qworkspaces_belonging_to_this_module, Qreclaim_gensym_list_if_list;
    Object Qmodule_annotations, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_18, list_constant_17, Qdatum;
    Object Qcompile_module_annotations_for_slot;
    Object Qwrite_module_annotations_from_slot, string_constant_93;
    Object string_constant_92, Qmodule_file_name_qm, Qtext, Qno_item;
    Object Qwrite_module_file_name_qm_from_slot;
    Object Qcompile_module_file_name_qm_for_slot, string_constant_91;
    Object Qwrite_file_name_qm_from_slot, Qfile_name_qm;
    Object Qcompile_file_name_qm_for_slot, string_constant_90;
    Object Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_module_information;
    Object Qinstall_system_table, Qinstall_system_table_for_module_information;
    Object Qmodule_file_name, Qkb_module_file_name_qm;
    Object Qdirectly_required_modules, Qtop_level_module, string_constant_89;
    Object string_constant_88, string_constant_87;
    Object Qreclaim_slot_value_tree_function, Kno_initial_value;
    Object Qgeneric_method_lambda_list, list_constant_14;
    Object Qitem_reference_parameters, string_constant_86, list_constant_13;
    Object string_constant_76, Qsystem_frame, Qitem, string_constant_84;
    Object string_constant_83, list_constant_12, string_constant_82;
    Object string_constant_81, string_constant_80, string_constant_79;
    Object string_constant_78, string_constant_77, Qentity;

    x_note_fn_call(93,168);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_12 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qsystem_frame,list_constant_12);
    string_constant_76 = STATIC_STRING("0");
    string_constant_77 = 
	    STATIC_STRING("1p4z8r83-Fy83-Fy83A6y83A6y00001q1l8l1l83Ny1m8p83-ky1l83Uy1l83*-y1m83Dy53MySee comment in class block000004z8r83--y83--y83A6y83A6");
    string_constant_78 = 
	    STATIC_STRING("y00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date. ~\nauthors: ([");
    string_constant_79 = 
	    STATIC_STRING(" name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n000004z8r83-0y83-0y83A6y83A");
    string_constant_80 = 
	    STATIC_STRING("6y00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentation is available at this ");
    string_constant_81 = 
	    STATIC_STRING("time)000004z8r83bsy83bsy83A6y83A6y00001p1l83Ny1l8l1l8o1l83Cy1m83Dy53TyExport, boolean, writable = false000004z8r83Vwy83Vwy83A6y8");
    string_constant_82 = 
	    STATIC_STRING("3A6y00001p1l83Ny1l8l1l8o1l83Cy1m83Dy53SyExport, symbol, writable = false00000");
    string_constant_83 = 
	    STATIC_STRING("1r8q1m83A6y1l83-+y1n83-Fy083Ny1n83--y01m8p83-*y1n83-0y01m8p83-0y1r83bsy083Ny8l8o83Cy1m83Dy53TyExport, boolean, writable = false1");
    string_constant_84 = 
	    STATIC_STRING("r83Vwy083Ny8l8o83Cy1m83Dy53SyExport, symbol, writable = false");
    temp = regenerate_optimized_constant(string_constant_76);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_77,
	    string_constant_78,string_constant_79,string_constant_80,
	    string_constant_81,string_constant_82));
    add_class_to_environment(9,Qsystem_frame,list_constant_12,Nil,temp,Nil,
	    temp_1,list_constant_12,
	    regenerate_optimized_constant(LIST_2(string_constant_83,
	    string_constant_84)),Nil);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qitem,Qsystem_frame);
    check_if_superior_classes_are_defined(Qsystem_table,list_constant_13);
    string_constant_85 = STATIC_STRING("1l1l83ey");
    string_constant_86 = STATIC_STRING("1m8q1n83-sy1m83Ry83A6y83ey");
    temp = regenerate_optimized_constant(string_constant_85);
    temp_1 = regenerate_optimized_constant(string_constant_76);
    add_class_to_environment(9,Qsystem_table,list_constant_13,Nil,temp,Nil,
	    temp_1,list_constant_13,
	    regenerate_optimized_constant(string_constant_86),Nil);
    Qdebugging_parameters = STATIC_SYMBOL("DEBUGGING-PARAMETERS",AB_package);
    Qtiming_parameters = STATIC_SYMBOL("TIMING-PARAMETERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtiming_parameters,Timing_parameters);
    Qinference_engine_parameters = 
	    STATIC_SYMBOL("INFERENCE-ENGINE-PARAMETERS",AB_package);
    Qdata_server_parameters = STATIC_SYMBOL("DATA-SERVER-PARAMETERS",
	    AB_package);
    Qg2gl_parameters = STATIC_SYMBOL("G2GL-PARAMETERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2gl_parameters,G2gl_parameters);
    Qsimulation_parameters = STATIC_SYMBOL("SIMULATION-PARAMETERS",AB_package);
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    Qprinter_setup = STATIC_SYMBOL("PRINTER-SETUP",AB_package);
    Qmessage_board_parameters = STATIC_SYMBOL("MESSAGE-BOARD-PARAMETERS",
	    AB_package);
    Qlogbook_parameters = STATIC_SYMBOL("LOGBOOK-PARAMETERS",AB_package);
    Qlog_file_parameters = STATIC_SYMBOL("LOG-FILE-PARAMETERS",AB_package);
    Qcolor_parameters = STATIC_SYMBOL("COLOR-PARAMETERS",AB_package);
    Qlanguage_parameters = STATIC_SYMBOL("LANGUAGE-PARAMETERS",AB_package);
    Qfonts = STATIC_SYMBOL("FONTS",AB_package);
    Qeditor_parameters = STATIC_SYMBOL("EDITOR-PARAMETERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qeditor_parameters,Editor_parameters);
    Qmenu_parameters = STATIC_SYMBOL("MENU-PARAMETERS",AB_package);
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    Qitem_reference_parameters = STATIC_SYMBOL("ITEM-REFERENCE-PARAMETERS",
	    AB_package);
    Qdrawing_parameters = STATIC_SYMBOL("DRAWING-PARAMETERS",AB_package);
    Qsaving_parameters = STATIC_SYMBOL("SAVING-PARAMETERS",AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodule_information,Module_information);
    Qversion_control_parameters = 
	    STATIC_SYMBOL("VERSION-CONTROL-PARAMETERS",AB_package);
    Qserver_parameters = STATIC_SYMBOL("SERVER-PARAMETERS",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)23L,Qdebugging_parameters,
	    Qtiming_parameters,Qinference_engine_parameters,
	    Qdata_server_parameters,Qg2gl_parameters,
	    Qsimulation_parameters,Qkb_configuration,Qprinter_setup,
	    Qmessage_board_parameters,Qlogbook_parameters,
	    Qlog_file_parameters,Qcolor_parameters,Qlanguage_parameters,
	    Qfonts,Qeditor_parameters,Qmenu_parameters,
	    Qmiscellaneous_parameters,Qitem_reference_parameters,
	    Qdrawing_parameters,Qsaving_parameters,Qmodule_information,
	    Qversion_control_parameters,Qserver_parameters);
    Order_of_system_tables_in_menu = list_constant_14;
    Qthis_window = STATIC_SYMBOL("THIS-WINDOW",AB_package);
    Qlisp_modules_to_be_loaded = STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",
	    AB_package);
    Qsystem_variable_descriptions = 
	    STATIC_SYMBOL("SYSTEM-VARIABLE-DESCRIPTIONS",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qthis_system_table_is_installed_qm = 
	    STATIC_SYMBOL("THIS-SYSTEM-TABLE-IS-INSTALLED\?",AB_package);
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table,
	    STATIC_FUNCTION(install_system_table,NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table,
	    STATIC_FUNCTION(deinstall_system_table,NIL,FALSE,1,1));
    list_constant_15 = STATIC_CONS(Qsystem_table,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qinstall_system_table,list_constant_15,
	    Qgeneric_method_lambda_list);
    mutate_global_property(Qdeinstall_system_table,list_constant_15,
	    Qgeneric_method_lambda_list);
    Qmodules_and_system_tables_a_list = 
	    STATIC_SYMBOL("MODULES-AND-SYSTEM-TABLES-A-LIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodules_and_system_tables_a_list,
	    Modules_and_system_tables_a_list);
    Qab_modules = STATIC_SYMBOL("MODULES",AB_package);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    Qreclaim_slot_value_tree_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-TREE-FUNCTION",AB_package);
    record_system_variable(Qmodules_and_system_tables_a_list,Qab_modules,
	    Kno_initial_value,Qnil,Qnil,Qreclaim_slot_value_tree_function,Qt);
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    Qsystem_table_suite_test = STATIC_SYMBOL("SYSTEM-TABLE-SUITE-TEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_table_suite_test,
	    STATIC_FUNCTION(system_table_suite_test,NIL,FALSE,2,2));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    string_constant = 
	    STATIC_STRING("The module-information instance which has just been created is ~\n                being discarded because it does not specify any top-level KB ~\n                module.");
    string_constant_1 = 
	    string_append2(STATIC_STRING("There already is a module-information system table that specifies ~\n                the module ~a as its top-level KB module.  Therefore, the ~\n                module-informat"),
	    STATIC_STRING("ion instance which has just been created is being ~\n                discarded."));
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    check_if_superior_classes_are_defined(Qmodule_information,
	    list_constant_15);
    string_constant_87 = 
	    STATIC_STRING("1p4z8r83TDy83TDy83Vty83Vty00001n1m8p83Dty1l8o1l8l000004z8r83cDy83cDy83Vty83Vty00001n1m8p83Dvy1l8o1l8l000004z8r83Juy83Juy83Vty83V");
    string_constant_88 = 
	    STATIC_STRING("ty00001n1m8p835ey1l8o1l8l000004z8r83HWy83HWy83Vty83Vty00001n1l83Hy1l8o1l8l000004z8r83Dsy83Dsy83Vty83Vty00001m1m8p83Dsy1l8l00000");
    string_constant_89 = 
	    STATIC_STRING("1r8q1n83Vty1l83-sy83ey1p83TDy01m8p83Dty8o8l1p83cDy01m8p83Dvy8o8l1p83Juy01m8p835ey8o8l1p83HWy083Hy8o8l1o83Dsy01m8p83Dsy8l");
    temp = regenerate_optimized_constant(string_constant_85);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_87,
	    string_constant_88));
    add_class_to_environment(9,Qmodule_information,list_constant_15,Nil,
	    temp,Nil,temp_1,list_constant_15,
	    regenerate_optimized_constant(string_constant_89),Nil);
    record_system_variable(Qmodule_information,Qab_modules,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qtop_level_module = STATIC_SYMBOL("TOP-LEVEL-MODULE",AB_package);
    alias_slot_name(3,Qtop_level_kb_module_qm,Qtop_level_module,Qnil);
    Qdirectly_required_kb_modules = 
	    STATIC_SYMBOL("DIRECTLY-REQUIRED-KB-MODULES",AB_package);
    Qdirectly_required_modules = STATIC_SYMBOL("DIRECTLY-REQUIRED-MODULES",
	    AB_package);
    alias_slot_name(3,Qdirectly_required_kb_modules,
	    Qdirectly_required_modules,Qnil);
    Qkb_module_file_name_qm = STATIC_SYMBOL("KB-MODULE-FILE-NAME\?",
	    AB_package);
    Qmodule_file_name = STATIC_SYMBOL("MODULE-FILE-NAME",AB_package);
    alias_slot_name(3,Qkb_module_file_name_qm,Qmodule_file_name,Qnil);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qinstall_system_table_for_module_information = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-MODULE-INFORMATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_module_information,
	    STATIC_FUNCTION(install_system_table_for_module_information,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_module_information);
    set_get(Qmodule_information,Qinstall_system_table,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodule_information,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_module_information = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-MODULE-INFORMATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_module_information,
	    STATIC_FUNCTION(deinstall_system_table_for_module_information,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_module_information);
    set_get(Qmodule_information,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodule_information,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    string_constant_90 = STATIC_STRING("1m1m83-Tsy1m9k83Zy1m83-Tsy838Ky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_90));
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qfile_name_qm = STATIC_SYMBOL("FILE-NAME\?",AB_package);
    Qcompile_file_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-FILE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_file_name_qm_for_slot,
	    STATIC_FUNCTION(compile_file_name_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qfile_name_qm,
	    SYMBOL_FUNCTION(Qcompile_file_name_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qfile_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_2 = STATIC_STRING("none");
    string_constant_3 = STATIC_STRING("~s");
    string_constant_4 = STATIC_STRING("~a");
    Qwrite_file_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-FILE-NAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_file_name_qm_from_slot,
	    STATIC_FUNCTION(write_file_name_qm_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qfile_name_qm,
	    SYMBOL_FUNCTION(Qwrite_file_name_qm_from_slot),Qslot_value_writer);
    string_constant_91 = STATIC_STRING("1m1m83Dty1m9k83Py1m83Dty838Ky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_91));
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qmodule_file_name_qm = STATIC_SYMBOL("MODULE-FILE-NAME\?",AB_package);
    Qcompile_module_file_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-MODULE-FILE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_module_file_name_qm_for_slot,
	    STATIC_FUNCTION(compile_module_file_name_qm_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qmodule_file_name_qm,
	    SYMBOL_FUNCTION(Qcompile_module_file_name_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmodule_file_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_5 = STATIC_STRING("default");
    Qwrite_module_file_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-MODULE-FILE-NAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_module_file_name_qm_from_slot,
	    STATIC_FUNCTION(write_module_file_name_qm_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qmodule_file_name_qm,
	    SYMBOL_FUNCTION(Qwrite_module_file_name_qm_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_8 = STATIC_CONS(Qno_item,Qnil);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_8,Qtext,
	    Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qmodule_file_name_qm),
	    Qtype_specification_simple_expansion,list_constant_1);
    define_type_specification_explicit_complex_type(Qmodule_file_name_qm,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qmodule_file_name_qm);
    module_file_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(module_file_name_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qmodule_file_name_qm,
	    module_file_name_qm_evaluation_setter_1);
    module_file_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(module_file_name_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmodule_file_name_qm,
	    module_file_name_qm_evaluation_getter_1);
    string_constant_92 = 
	    STATIC_STRING("1q1m83Dsy83-fUy1n83Dsy1m9k83Zy01n83-fUy1n83-2y1m9k83*Iy83-fVy1mln1n83-fUy1p83-2y1m9k83*Iy83-fVy1m9k83-Zy83-fUy2mlnp1m83-fVy83Kky");
    string_constant_93 = STATIC_STRING("1m83-fVy83-2y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_92,
	    string_constant_93)));
    string_constant_6 = STATIC_STRING("~a is ~NV");
    string_constant_7 = STATIC_STRING(";~%");
    Qmodule_annotations = STATIC_SYMBOL("MODULE-ANNOTATIONS",AB_package);
    Qwrite_module_annotations_from_slot = 
	    STATIC_SYMBOL("WRITE-MODULE-ANNOTATIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_module_annotations_from_slot,
	    STATIC_FUNCTION(write_module_annotations_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmodule_annotations,
	    SYMBOL_FUNCTION(Qwrite_module_annotations_from_slot),
	    Qslot_value_writer);
    string_constant_8 = STATIC_STRING("Duplicate annotation for ~a found.");
    Qcompile_module_annotations_for_slot = 
	    STATIC_SYMBOL("COMPILE-MODULE-ANNOTATIONS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_module_annotations_for_slot,
	    STATIC_FUNCTION(compile_module_annotations_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qmodule_annotations,
	    SYMBOL_FUNCTION(Qcompile_module_annotations_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmodule_annotations,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_9 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qmodule_annotations),
	    Qtype_specification_simple_expansion,list_constant_9);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qannotation_name = STATIC_SYMBOL("ANNOTATION-NAME",AB_package);
    list_constant_16 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_17 = STATIC_CONS(Qannotation_name,list_constant_16);
    Qannotation_value = STATIC_SYMBOL("ANNOTATION-VALUE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qannotation_value,Qdatum);
    list_constant_19 = STATIC_LIST((SI_Long)2L,list_constant_17,
	    list_constant_18);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qand,Qannotation_name,
	    Qannotation_value);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_19,list_constant_20);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_21,
	    FIX((SI_Long)0L));
    define_type_specification_explicit_complex_type(Qmodule_annotations,
	    list_constant_3);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qmodule_annotations);
    module_annotations_evaluation_setter_1 = 
	    STATIC_FUNCTION(module_annotations_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qmodule_annotations,
	    module_annotations_evaluation_setter_1);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    module_annotations_evaluation_getter_1 = 
	    STATIC_FUNCTION(module_annotations_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qmodule_annotations,
	    module_annotations_evaluation_getter_1);
    Qworkspaces_belonging_to_this_module = 
	    STATIC_SYMBOL("WORKSPACES-BELONGING-TO-THIS-MODULE",AB_package);
    Kb_specific_property_names = CONS(Qworkspaces_belonging_to_this_module,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qworkspaces_belonging_to_this_module,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_gensym_list_if_list = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-IF-LIST",AB_package);
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qworkspaces_belonging_to_this_module,
	    Qreclaim_gensym_list_if_list,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Workspaces_belonging_to_this_module_kbprop = 
	    Qworkspaces_belonging_to_this_module;
    Qmodule_information_instance_for_module_qm = 
	    STATIC_SYMBOL("MODULE-INFORMATION-INSTANCE-FOR-MODULE\?",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qmodule_information_instance_for_module_qm,
	    Kb_specific_property_names);
    mutate_global_property(Qmodule_information_instance_for_module_qm,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_information_instance_for_module_qm_kbprop = 
	    Qmodule_information_instance_for_module_qm;
    Qmodule_system_table_belongs_to_qm = 
	    STATIC_SYMBOL("MODULE-SYSTEM-TABLE-BELONGS-TO\?",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qput_top_level_kb_module_qm = 
	    STATIC_SYMBOL("PUT-TOP-LEVEL-KB-MODULE\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_top_level_kb_module_qm,
	    STATIC_FUNCTION(put_top_level_kb_module_qm,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qtop_level_kb_module_qm,
	    SYMBOL_FUNCTION(Qput_top_level_kb_module_qm),Qslot_putter);
    Qreclaim_top_level_kb_module_qm_value = 
	    STATIC_SYMBOL("RECLAIM-TOP-LEVEL-KB-MODULE\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_top_level_kb_module_qm_value,
	    STATIC_FUNCTION(reclaim_top_level_kb_module_qm_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qtop_level_kb_module_qm,
	    SYMBOL_FUNCTION(Qreclaim_top_level_kb_module_qm_value),
	    Qslot_value_reclaimer);
    string_constant_94 = STATIC_STRING("1l1m83Dvy8313y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_94));
    Qunspecified = STATIC_SYMBOL("UNSPECIFIED",AB_package);
    string_constant_9 = 
	    STATIC_STRING("you cannot change the ~a attribute of a ~\n              non-top-level module-information system table ~\n              to UNSPECIFIED.");
    string_constant_10 = 
	    STATIC_STRING("you cannot change the ~a attribute of a ~\n          module-information system table ~\n          to the name of an already existing module.");
    Qmodule_name_for_module_information_qm = 
	    STATIC_SYMBOL("MODULE-NAME-FOR-MODULE-INFORMATION\?",AB_package);
    Qcompile_module_name_for_module_information_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-MODULE-NAME-FOR-MODULE-INFORMATION\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_module_name_for_module_information_qm_for_slot,
	    STATIC_FUNCTION(compile_module_name_for_module_information_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qmodule_name_for_module_information_qm,
	    SYMBOL_FUNCTION(Qcompile_module_name_for_module_information_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmodule_name_for_module_information_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_module_name_for_module_information_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-MODULE-NAME-FOR-MODULE-INFORMATION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_module_name_for_module_information_qm_from_slot,
	    STATIC_FUNCTION(write_module_name_for_module_information_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmodule_name_for_module_information_qm,
	    SYMBOL_FUNCTION(Qwrite_module_name_for_module_information_qm_from_slot),
	    Qslot_value_writer);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_16);
    set_property_value_function(get_symbol_properties_function(Qmodule_name_for_module_information_qm),
	    Qtype_specification_simple_expansion,list_constant_5);
    define_type_specification_explicit_complex_type(Qmodule_name_for_module_information_qm,
	    list_constant_5);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qmodule_name_for_module_information_qm);
    module_name_for_module_information_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(module_name_for_module_information_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmodule_name_for_module_information_qm,
	    module_name_for_module_information_qm_evaluation_setter_1);
    module_name_for_module_information_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(module_name_for_module_information_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmodule_name_for_module_information_qm,
	    module_name_for_module_information_qm_evaluation_getter_1);
    Qlist_of_modules_qm = STATIC_SYMBOL("LIST-OF-MODULES\?",AB_package);
    Qmodule_name = STATIC_SYMBOL("MODULE-NAME",AB_package);
    add_grammar_rules_for_list(5,Qlist_of_modules_qm,Qmodule_name,Nil,Nil,
	    Qnone);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_list_of_modules_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-MODULES\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_modules_qm_from_slot,
	    STATIC_FUNCTION(write_list_of_modules_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlist_of_modules_qm,
	    SYMBOL_FUNCTION(Qwrite_list_of_modules_qm_from_slot),
	    Qslot_value_writer);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qcompile_list_of_modules_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-MODULES\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_modules_qm_for_slot,
	    STATIC_FUNCTION(compile_list_of_modules_qm_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlist_of_modules_qm,
	    SYMBOL_FUNCTION(Qcompile_list_of_modules_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_modules_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_9);
    set_property_value_function(get_symbol_properties_function(Qlist_of_modules_qm),
	    Qtype_specification_simple_expansion,list_constant_23);
    list_constant_24 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_24);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_8,
	    list_constant_25);
    define_type_specification_explicit_complex_type(Qlist_of_modules_qm,
	    list_constant_7);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnamed,Qlist_of_modules_qm);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_11 = STATIC_STRING("~NT ");
    string_constant_12 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    list_of_modules_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(list_of_modules_qm_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qlist_of_modules_qm,
	    list_of_modules_qm_evaluation_setter_1);
    list_of_modules_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(list_of_modules_qm_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qlist_of_modules_qm,
	    list_of_modules_qm_evaluation_getter_1);
    Qreclaim_slot_value_cons_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-CONS-FUNCTION",AB_package);
    Qput_directly_required_kb_modules = 
	    STATIC_SYMBOL("PUT-DIRECTLY-REQUIRED-KB-MODULES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_directly_required_kb_modules,
	    STATIC_FUNCTION(put_directly_required_kb_modules,NIL,FALSE,3,3));
    mutate_global_property(Qdirectly_required_kb_modules,
	    SYMBOL_FUNCTION(Qput_directly_required_kb_modules),Qslot_putter);
    Qreclaim_directly_required_kb_modules_value = 
	    STATIC_SYMBOL("RECLAIM-DIRECTLY-REQUIRED-KB-MODULES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_directly_required_kb_modules_value,
	    STATIC_FUNCTION(reclaim_directly_required_kb_modules_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdirectly_required_kb_modules,
	    SYMBOL_FUNCTION(Qreclaim_directly_required_kb_modules_value),
	    Qslot_value_reclaimer);
    Qdelete_from_directory_of_names = 
	    STATIC_SYMBOL("DELETE-FROM-DIRECTORY-OF-NAMES",AB_package);
    SET_SYMBOL_FUNCTION(Qdelete_from_directory_of_names,
	    STATIC_FUNCTION(delete_from_directory_of_names,NIL,FALSE,2,2));
    Qadd_to_directory_of_names = STATIC_SYMBOL("ADD-TO-DIRECTORY-OF-NAMES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_to_directory_of_names,
	    STATIC_FUNCTION(add_to_directory_of_names,NIL,FALSE,2,2));
    Qmodules_that_have_already_been_loaded = 
	    STATIC_SYMBOL("MODULES-THAT-HAVE-ALREADY-BEEN-LOADED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodules_that_have_already_been_loaded,
	    Modules_that_have_already_been_loaded);
    Qreclaim_gensym_list_function = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-FUNCTION",AB_package);
    record_system_variable(Qmodules_that_have_already_been_loaded,
	    Qab_modules,Nil,Qnil,Qnil,Qreclaim_gensym_list_function,Qt);
    Qcurrently_loading_modules_qm = 
	    STATIC_SYMBOL("CURRENTLY-LOADING-MODULES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrently_loading_modules_qm,
	    Currently_loading_modules_qm);
    record_system_variable(Qcurrently_loading_modules_qm,Qab_modules,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    string_constant_13 = 
	    STATIC_STRING(", because \"Start KB after Load\?\" is set in Miscellaneous Parameters");
    Qload_grammar = STATIC_SYMBOL("LOAD-GRAMMAR",AB_package);
    string_constant_14 = 
	    STATIC_STRING(", as specified in the last \"Load KB\" command");
    Qmerge_grammar = STATIC_SYMBOL("MERGE-GRAMMAR",AB_package);
    string_constant_15 = 
	    STATIC_STRING(", as specified in the last \"Merge KB\" command");
    Qload_in_init_file = STATIC_SYMBOL("LOAD-IN-INIT-FILE",AB_package);
    string_constant_16 = 
	    STATIC_STRING(", from the last \"Load KB\" line in the G2 Init file to specify this");
    Qmerge_in_init_file = STATIC_SYMBOL("MERGE-IN-INIT-FILE",AB_package);
    string_constant_17 = 
	    STATIC_STRING(", from the last \"Merge KB\" line in the G2 Init file to specify this");
    Qload_from_command_line = STATIC_SYMBOL("LOAD-FROM-COMMAND-LINE",
	    AB_package);
    string_constant_18 = 
	    STATIC_STRING(", because the command line that launched G2 specified the \"-start\" option");
    string_constant_19 = STATIC_STRING("");
    string_constant_20 = 
	    STATIC_STRING("Starting to run G2 automatically~a.  ~\n     You may pause, reset, or restart at any time.");
    if (Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
	    == UNBOUND)
	Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
		= Nil;
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qmodule_name_unspecified = STATIC_SYMBOL("MODULE-NAME-UNSPECIFIED",
	    AB_package);
    Qmodule_name_in_use = STATIC_SYMBOL("MODULE-NAME-IN-USE",AB_package);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    Qmodule_name_is_reserved_word = 
	    STATIC_SYMBOL("MODULE-NAME-IS-RESERVED-WORD",AB_package);
    Qmodule_creation_failed_for_unknown_reason = 
	    STATIC_SYMBOL("MODULE-CREATION-FAILED-FOR-UNKNOWN-REASON",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qworkspaces_belong_to_unrequired_modules = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-UNREQUIRED-MODULES",
	    AB_package);
    Qworkspaces_belong_to_non_existant_modules = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-NON-EXISTANT-MODULES",
	    AB_package);
    Qworkspaces_belong_to_unknown_modules = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-UNKNOWN-MODULES",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)3L,
	    Qworkspaces_belong_to_unknown_modules,
	    Qworkspaces_belong_to_unrequired_modules,
	    Qworkspaces_belong_to_non_existant_modules);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qmodules_that_exist_are_unknown = 
	    STATIC_SYMBOL("MODULES-THAT-EXIST-ARE-UNKNOWN",AB_package);
    Qmodules_that_exist_are_not_required = 
	    STATIC_SYMBOL("MODULES-THAT-EXIST-ARE-NOT-REQUIRED",AB_package);
    Qmodules_required_by_kb_do_not_exist = 
	    STATIC_SYMBOL("MODULES-REQUIRED-BY-KB-DO-NOT-EXIST",AB_package);
    Qmodule_is_empty_but_that_is_ok = 
	    STATIC_SYMBOL("MODULE-IS-EMPTY-BUT-THAT-IS-OK",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)4L,
	    Qmodules_that_exist_are_unknown,
	    Qmodules_that_exist_are_not_required,
	    Qmodules_required_by_kb_do_not_exist,
	    Qmodule_is_empty_but_that_is_ok);
    Qmodule_exists_but_is_unknown = 
	    STATIC_SYMBOL("MODULE-EXISTS-BUT-IS-UNKNOWN",AB_package);
    Qmodule_required_but_does_not_exist = 
	    STATIC_SYMBOL("MODULE-REQUIRED-BUT-DOES-NOT-EXIST",AB_package);
    Qmodule_is_empty = STATIC_SYMBOL("MODULE-IS-EMPTY",AB_package);
    Qcircularity_in_module_hierarchy = 
	    STATIC_SYMBOL("CIRCULARITY-IN-MODULE-HIERARCHY",AB_package);
    Qworkspace_does_not_belong_to_any_module = 
	    STATIC_SYMBOL("WORKSPACE-DOES-NOT-BELONG-TO-ANY-MODULE",
	    AB_package);
    Qkb_workspace_is_part_of_unknown_module = 
	    STATIC_SYMBOL("KB-WORKSPACE-IS-PART-OF-UNKNOWN-MODULE",AB_package);
    Qkb_workspace_is_part_of_unrequired_module = 
	    STATIC_SYMBOL("KB-WORKSPACE-IS-PART-OF-UNREQUIRED-MODULE",
	    AB_package);
    Qkb_workspace_assigned_to_unrequired_module = 
	    STATIC_SYMBOL("KB-WORKSPACE-ASSIGNED-TO-UNREQUIRED-MODULE",
	    AB_package);
    Qkb_workspace_is_part_of_non_existant_module = 
	    STATIC_SYMBOL("KB-WORKSPACE-IS-PART-OF-NON-EXISTANT-MODULE",
	    AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)5L,
	    Qworkspace_does_not_belong_to_any_module,
	    Qkb_workspace_is_part_of_unknown_module,
	    Qkb_workspace_is_part_of_unrequired_module,
	    Qkb_workspace_assigned_to_unrequired_module,
	    Qkb_workspace_is_part_of_non_existant_module);
    if (All_module_frame_notes_for_workspaces == UNBOUND)
	All_module_frame_notes_for_workspaces = list_constant_26;
    Qworkspaces_belong_to_unspecified_module = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-UNSPECIFIED-MODULE",
	    AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    string_constant_21 = 
	    STATIC_STRING("~%~%Warning: this module is ~arequired by the KB, ~a is ~\n          required directly or indirectly by ");
    string_constant_22 = STATIC_STRING("not ");
    string_constant_23 = STATIC_STRING("and in particular");
    string_constant_24 = STATIC_STRING("but");
    string_constant_25 = STATIC_STRING("~L,&.");
    if (Obsolete_frame_note_types_from_modularity_development == UNBOUND)
	Obsolete_frame_note_types_from_modularity_development = Nil;
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_26 = 
	    STATIC_STRING("the module ~a is not required by the KB");
    write_kb_workspace_assigned_to_unrequired_module_note_1 = 
	    STATIC_FUNCTION(write_kb_workspace_assigned_to_unrequired_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qkb_workspace_assigned_to_unrequired_module,
	    write_kb_workspace_assigned_to_unrequired_module_note_1,
	    Qframe_note_writer_1);
    list_constant_27 = STATIC_CONS(Qkb_workspace_is_part_of_unknown_module,
	    Qkb_workspace_assigned_to_unrequired_module);
    if ( !TRUEP(assoc_eql(Qkb_workspace_is_part_of_unknown_module,
	    Obsolete_frame_note_types_from_modularity_development))) {
	temp_2 = CONS(list_constant_27,
		Obsolete_frame_note_types_from_modularity_development);
	Obsolete_frame_note_types_from_modularity_development = temp_2;
    }
    write_kb_workspace_is_part_of_unknown_module_note_1 = 
	    STATIC_FUNCTION(write_kb_workspace_is_part_of_unknown_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qkb_workspace_is_part_of_unknown_module,
	    write_kb_workspace_is_part_of_unknown_module_note_1,
	    Qframe_note_writer_1);
    list_constant_28 = 
	    STATIC_CONS(Qkb_workspace_is_part_of_unrequired_module,
	    Qkb_workspace_assigned_to_unrequired_module);
    if ( !TRUEP(assoc_eql(Qkb_workspace_is_part_of_unrequired_module,
	    Obsolete_frame_note_types_from_modularity_development))) {
	temp_2 = CONS(list_constant_28,
		Obsolete_frame_note_types_from_modularity_development);
	Obsolete_frame_note_types_from_modularity_development = temp_2;
    }
    write_kb_workspace_is_part_of_unrequired_module_note_1 = 
	    STATIC_FUNCTION(write_kb_workspace_is_part_of_unrequired_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qkb_workspace_is_part_of_unrequired_module,
	    write_kb_workspace_is_part_of_unrequired_module_note_1,
	    Qframe_note_writer_1);
    string_constant_27 = STATIC_STRING("the module ~a does not exist");
    write_kb_workspace_is_part_of_non_existant_module_note_1 = 
	    STATIC_FUNCTION(write_kb_workspace_is_part_of_non_existant_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qkb_workspace_is_part_of_non_existant_module,
	    write_kb_workspace_is_part_of_non_existant_module_note_1,
	    Qframe_note_writer_1);
    string_constant_28 = 
	    STATIC_STRING("the top-level module is ~a, but this workspace is not assigned to any module");
    write_workspace_does_not_belong_to_any_module_note_1 = 
	    STATIC_FUNCTION(write_workspace_does_not_belong_to_any_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qworkspace_does_not_belong_to_any_module,
	    write_workspace_does_not_belong_to_any_module_note_1,
	    Qframe_note_writer_1);
    string_constant_29 = 
	    STATIC_STRING("~a workspace~a ~a not assigned to any module");
    string_constant_30 = STATIC_STRING("s");
    string_constant_31 = STATIC_STRING("is");
    string_constant_32 = STATIC_STRING("are");
    string_constant_33 = STATIC_STRING("its");
    string_constant_34 = STATIC_STRING("their");
    write_workspaces_belong_to_unspecified_module_note_1 = 
	    STATIC_FUNCTION(write_workspaces_belong_to_unspecified_module_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qworkspaces_belong_to_unspecified_module,
	    write_workspaces_belong_to_unspecified_module_note_1,
	    Qframe_note_writer_1);
    string_constant_35 = STATIC_STRING("the module~a ");
    string_constant_36 = STATIC_STRING(",");
    string_constant_37 = STATIC_STRING("and");
    string_constant_38 = 
	    STATIC_STRING(" ~a workspaces assigned to ~a but ~a not required by the KB");
    string_constant_39 = STATIC_STRING("has");
    string_constant_40 = STATIC_STRING("have");
    string_constant_41 = STATIC_STRING("it");
    string_constant_42 = STATIC_STRING("them");
    write_workspaces_belong_to_unrequired_modules_note_1 = 
	    STATIC_FUNCTION(write_workspaces_belong_to_unrequired_modules_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qworkspaces_belong_to_unrequired_modules,
	    write_workspaces_belong_to_unrequired_modules_note_1,
	    Qframe_note_writer_1);
    list_constant_29 = STATIC_CONS(Qworkspaces_belong_to_unknown_modules,
	    Qworkspaces_belong_to_unrequired_modules);
    if ( !TRUEP(assoc_eql(Qworkspaces_belong_to_unknown_modules,
	    Obsolete_frame_note_types_from_modularity_development))) {
	temp_2 = CONS(list_constant_29,
		Obsolete_frame_note_types_from_modularity_development);
	Obsolete_frame_note_types_from_modularity_development = temp_2;
    }
    write_workspaces_belong_to_unknown_modules_note_1 = 
	    STATIC_FUNCTION(write_workspaces_belong_to_unknown_modules_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qworkspaces_belong_to_unknown_modules,
	    write_workspaces_belong_to_unknown_modules_note_1,
	    Qframe_note_writer_1);
    Qkb_unsavable_due_to_module_inconcistency = 
	    STATIC_SYMBOL("KB-UNSAVABLE-DUE-TO-MODULE-INCONCISTENCY",
	    AB_package);
    string_constant_43 = 
	    STATIC_STRING("this KB cannot be saved because the modules are not consistent");
    write_kb_unsavable_due_to_module_inconcistency_note_1 = 
	    STATIC_FUNCTION(write_kb_unsavable_due_to_module_inconcistency_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qkb_unsavable_due_to_module_inconcistency,
	    write_kb_unsavable_due_to_module_inconcistency_note_1,
	    Qframe_note_writer_1);
    Qmodule_has_no_workspaces_assigned_to_it = 
	    STATIC_SYMBOL("MODULE-HAS-NO-WORKSPACES-ASSIGNED-TO-IT",
	    AB_package);
    string_constant_44 = 
	    STATIC_STRING("no workspaces are assigned to the module ~a");
    write_module_has_no_workspaces_assigned_to_it_note_1 = 
	    STATIC_FUNCTION(write_module_has_no_workspaces_assigned_to_it_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmodule_has_no_workspaces_assigned_to_it,
	    write_module_has_no_workspaces_assigned_to_it_note_1,
	    Qframe_note_writer_1);
    string_constant_45 = 
	    STATIC_STRING(" do~a not exist, but workspaces are assigned to ~a");
    string_constant_46 = STATIC_STRING("es");
    write_workspaces_belong_to_non_existant_modules_note_1 = 
	    STATIC_FUNCTION(write_workspaces_belong_to_non_existant_modules_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qworkspaces_belong_to_non_existant_modules,
	    write_workspaces_belong_to_non_existant_modules_note_1,
	    Qframe_note_writer_1);
    Qmodule_not_required_but_has_workspaces_assigned_to_it = 
	    STATIC_SYMBOL("MODULE-NOT-REQUIRED-BUT-HAS-WORKSPACES-ASSIGNED-TO-IT",
	    AB_package);
    string_constant_47 = 
	    STATIC_STRING("there are workspaces assigned to the module ~a, but it is not required by the KB");
    write_module_not_required_but_has_workspaces_assigned_to_it_note_1 = 
	    STATIC_FUNCTION(write_module_not_required_but_has_workspaces_assigned_to_it_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmodule_not_required_but_has_workspaces_assigned_to_it,
	    write_module_not_required_but_has_workspaces_assigned_to_it_note_1,
	    Qframe_note_writer_1);
    write_module_exists_but_is_unknown_note_1 = 
	    STATIC_FUNCTION(write_module_exists_but_is_unknown_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmodule_exists_but_is_unknown,
	    write_module_exists_but_is_unknown_note_1,Qframe_note_writer_1);
    string_constant_48 = 
	    STATIC_STRING(" exist~a but ~a not required by the KB");
    write_modules_that_exist_are_not_required_note_1 = 
	    STATIC_FUNCTION(write_modules_that_exist_are_not_required_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmodules_that_exist_are_not_required,
	    write_modules_that_exist_are_not_required_note_1,
	    Qframe_note_writer_1);
    list_constant_30 = STATIC_CONS(Qmodules_that_exist_are_unknown,
	    Qmodules_that_exist_are_not_required);
    if ( !TRUEP(assoc_eql(Qmodules_that_exist_are_unknown,
	    Obsolete_frame_note_types_from_modularity_development))) {
	temp_2 = CONS(list_constant_30,
		Obsolete_frame_note_types_from_modularity_development);
	Obsolete_frame_note_types_from_modularity_development = temp_2;
    }
    write_modules_that_exist_are_unknown_note_1 = 
	    STATIC_FUNCTION(write_modules_that_exist_are_unknown_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmodules_that_exist_are_unknown,
	    write_modules_that_exist_are_unknown_note_1,Qframe_note_writer_1);
    write_module_is_empty_note_1 = 
	    STATIC_FUNCTION(write_module_is_empty_note,NIL,FALSE,2,2);
    mutate_global_property(Qmodule_is_empty,write_module_is_empty_note_1,
	    Qframe_note_writer_1);
    string_constant_49 = 
	    STATIC_STRING("no workspaces are assigned to the module~a ");
    string_constant_50 = 
	    STATIC_STRING(", but since ~a ~a not required by this KB, it is probably best to ~\n       delete ~a module~a");
    string_constant_51 = STATIC_STRING("they");
    string_constant_52 = STATIC_STRING("this");
    string_constant_53 = STATIC_STRING("these");
    write_module_is_empty_but_that_is_ok_note_1 = 
	    STATIC_FUNCTION(write_module_is_empty_but_that_is_ok_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qmodule_is_empty_but_that_is_ok,
	    write_module_is_empty_but_that_is_ok_note_1,Qframe_note_writer_1);
    string_constant_54 = STATIC_STRING(" ~a required here but do~a not exist");
    write_module_required_but_does_not_exist_note_1 = 
	    STATIC_FUNCTION(write_module_required_but_does_not_exist_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmodule_required_but_does_not_exist,
	    write_module_required_but_does_not_exist_note_1,
	    Qframe_note_writer_1);
    string_constant_55 = 
	    STATIC_STRING(" ~a required by the KB but do~a not exist");
    write_modules_required_by_kb_do_not_exist_note_1 = 
	    STATIC_FUNCTION(write_modules_required_by_kb_do_not_exist_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qmodules_required_by_kb_do_not_exist,
	    write_modules_required_by_kb_do_not_exist_note_1,
	    Qframe_note_writer_1);
    string_constant_56 = 
	    STATIC_STRING("the module hierarchy has the following ~a~acycle~a: ");
    string_constant_57 = STATIC_STRING(" ");
    string_constant_58 = STATIC_STRING("--");
    string_constant_59 = STATIC_STRING("; ");
    write_circularity_in_module_hierarchy_note_1 = 
	    STATIC_FUNCTION(write_circularity_in_module_hierarchy_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qcircularity_in_module_hierarchy,
	    write_circularity_in_module_hierarchy_note_1,Qframe_note_writer_1);
    Qformat_string_for_kb_modularity_problem = 
	    STATIC_SYMBOL("FORMAT-STRING-FOR-KB-MODULARITY-PROBLEM",
	    AB_package);
    Format_string_for_kb_modularity_problem_prop = 
	    Qformat_string_for_kb_modularity_problem;
    Qformat_args_for_kb_modularity_problem = 
	    STATIC_SYMBOL("FORMAT-ARGS-FOR-KB-MODULARITY-PROBLEM",AB_package);
    Format_args_for_kb_modularity_problem_prop = 
	    Qformat_args_for_kb_modularity_problem;
    Qparticulars_printer_for_kb_modularity_problem = 
	    STATIC_SYMBOL("PARTICULARS-PRINTER-FOR-KB-MODULARITY-PROBLEM",
	    AB_package);
    Particulars_printer_for_kb_modularity_problem_prop = 
	    Qparticulars_printer_for_kb_modularity_problem;
    string_constant_95 = STATIC_STRING("MODULARITY-CHECKING");
    if (Modularity_checking == UNBOUND)
	Modularity_checking = make_recursive_lock(2,Kname,string_constant_95);
    Qmodularity_checking = STATIC_SYMBOL("MODULARITY-CHECKING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodularity_checking,Modularity_checking);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qmodularity_checking,
	    Qab_modules,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qmodularity_checking,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qfatal = STATIC_SYMBOL("FATAL",AB_package);
    Qadvisory = STATIC_SYMBOL("ADVISORY",AB_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    Qnotify_user = STATIC_SYMBOL("NOTIFY-USER",AB_package);
    string_constant_96 = 
	    STATIC_STRING("There are cycles among the modules required by this KB; see the ~\n     installed module-information system table for further information.");
    mutate_global_property(Qcircularity_in_module_hierarchy,
	    string_constant_96,Qformat_string_for_kb_modularity_problem);
    string_constant_97 = 
	    STATIC_STRING("Modules that exist are not required by the KB; see the ~\n     installed module-information system table for further information.");
    mutate_global_property(Qmodules_that_exist_are_not_required,
	    string_constant_97,Qformat_string_for_kb_modularity_problem);
    string_constant_98 = 
	    STATIC_STRING("Workspaces exist whose module assignment is UNSPECIFIED; see the ~\n     installed module-information system table for further information.");
    mutate_global_property(Qworkspaces_belong_to_unspecified_module,
	    string_constant_98,Qformat_string_for_kb_modularity_problem);
    string_constant_99 = 
	    STATIC_STRING("Workspaces belong to modules that are not required by the KB; see the ~\n     installed module-information system table for further information.");
    mutate_global_property(Qworkspaces_belong_to_unrequired_modules,
	    string_constant_99,Qformat_string_for_kb_modularity_problem);
    string_constant_100 = 
	    STATIC_STRING("Modules required by the KB do not exist; see the ~\n     installed module-information system table for further information.");
    mutate_global_property(Qmodules_required_by_kb_do_not_exist,
	    string_constant_100,Qformat_string_for_kb_modularity_problem);
    string_constant_60 = 
	    STATIC_STRING("These class definitions are not assigned to any module.");
    string_constant_61 = 
	    STATIC_STRING("The following classes are not assigned to any module: ~L,&");
    string_constant_62 = 
	    STATIC_STRING("There are ~d classes that are not assigned to any module.");
    Qclasses_not_defined_in_any_module = 
	    STATIC_SYMBOL("CLASSES-NOT-DEFINED-IN-ANY-MODULE",AB_package);
    Qprint_classes_not_defined_in_any_module = 
	    STATIC_SYMBOL("PRINT-CLASSES-NOT-DEFINED-IN-ANY-MODULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_classes_not_defined_in_any_module,
	    STATIC_FUNCTION(print_classes_not_defined_in_any_module,NIL,
	    FALSE,1,1));
    mutate_global_property(Qclasses_not_defined_in_any_module,
	    Qprint_classes_not_defined_in_any_module,
	    Qparticulars_printer_for_kb_modularity_problem);
    string_constant_63 = 
	    STATIC_STRING("These class definitions do not have their superior assigned to their module hierarchy.");
    string_constant_64 = 
	    STATIC_STRING("The following classes do not have their superior assigned to their module hierarchy: ~L,&");
    string_constant_65 = 
	    STATIC_STRING("There are ~d classes that do not have their superior assigned to their module hierarchy.");
    Qclasses_whose_superiors_are_not_defined_in_required_modules = 
	    STATIC_SYMBOL("CLASSES-WHOSE-SUPERIORS-ARE-NOT-DEFINED-IN-REQUIRED-MODULES",
	    AB_package);
    Qprint_classes_whose_superiors_are_not_defined_in_required_modules = 
	    STATIC_SYMBOL("PRINT-CLASSES-WHOSE-SUPERIORS-ARE-NOT-DEFINED-IN-REQUIRED-MODULES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_classes_whose_superiors_are_not_defined_in_required_modules,
	    STATIC_FUNCTION(print_classes_whose_superiors_are_not_defined_in_required_modules,
	    NIL,FALSE,1,1));
    mutate_global_property(Qclasses_whose_superiors_are_not_defined_in_required_modules,
	    Qprint_classes_whose_superiors_are_not_defined_in_required_modules,
	    Qparticulars_printer_for_kb_modularity_problem);
    string_constant_66 = 
	    STATIC_STRING("These class definitions are not in the module hierarchy of the indicated instances.");
    string_constant_67 = 
	    STATIC_STRING("The class ~a has ~a instance~a that do~a not reside in any module that ~\n                    requires the module of the class (~a).");
    Qclasses_with_instances_in_modules_that_do_not_require_them = 
	    STATIC_SYMBOL("CLASSES-WITH-INSTANCES-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM",
	    AB_package);
    Qprint_classes_with_instances_in_modules_that_do_not_require_them = 
	    STATIC_SYMBOL("PRINT-CLASSES-WITH-INSTANCES-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_classes_with_instances_in_modules_that_do_not_require_them,
	    STATIC_FUNCTION(print_classes_with_instances_in_modules_that_do_not_require_them,
	    NIL,FALSE,1,1));
    mutate_global_property(Qclasses_with_instances_in_modules_that_do_not_require_them,
	    Qprint_classes_with_instances_in_modules_that_do_not_require_them,
	    Qparticulars_printer_for_kb_modularity_problem);
    string_constant_68 = 
	    string_append2(STATIC_STRING("~NF has a table on workspace ~NF, which does not ~\n                 belong to the same module.  Tables must reside in ~\n                 the same module as the item they repre"),
	    STATIC_STRING("sent."));
    string_constant_69 = 
	    string_append2(STATIC_STRING("~NF has a table on workspace ~NF, which does not ~\n             belong to the same module.  Tables must reside in ~\n             the same module as the item they represent. Th"),
	    STATIC_STRING("is KB will ~\n             not be savable until this problem is resolved."));
    Qtable_in_different_module_than_item_represented = 
	    STATIC_SYMBOL("TABLE-IN-DIFFERENT-MODULE-THAN-ITEM-REPRESENTED",
	    AB_package);
    Qprint_table_in_different_module_than_item_represented = 
	    STATIC_SYMBOL("PRINT-TABLE-IN-DIFFERENT-MODULE-THAN-ITEM-REPRESENTED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_table_in_different_module_than_item_represented,
	    STATIC_FUNCTION(print_table_in_different_module_than_item_represented,
	    NIL,FALSE,1,1));
    mutate_global_property(Qtable_in_different_module_than_item_represented,
	    Qprint_table_in_different_module_than_item_represented,
	    Qparticulars_printer_for_kb_modularity_problem);
    Qavailable_module_required_by_relationships_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_module_required_by_relationships_hash_vector_43_vectors,
	    Available_module_required_by_relationships_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_module_required_by_relationships_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_module_required_by_relationships_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_module_required_by_relationships_hash_vector_43_vectors,
	    Count_of_module_required_by_relationships_hash_vector_43_vectors);
    record_system_variable(Qcount_of_module_required_by_relationships_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_module_required_by_relationships_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_module_required_by_relationships_hash_vector_43_vectors_vector 
		= make_thread_array(Nil);
    Qout_module_required_by_relationships_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qmodule_required_by_relationships_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("MODULE-REQUIRED-BY-RELATIONSHIPS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_101 = STATIC_STRING("1q83-fXy83*9y83-P1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_module_required_by_relationships_hash_vector_43_vectors);
    push_optimized_constant(Qmodule_required_by_relationships_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_101));
    SET_SYMBOL_FUNCTION(Qmodule_required_by_relationships_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(module_required_by_relationships_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_module_required_by_relationships_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_module_required_by_relationships_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_module_required_by_relationships_tree_for_hash_skip_list_entry 
	    = 
	    STATIC_SYMBOL("MUTATE-MODULE-REQUIRED-BY-RELATIONSHIPS-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_module_required_by_relationships_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_module_required_by_relationships_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_module_required_by_relationships_tree_for_hash_skip_list_entry 
	    = 
	    SYMBOL_FUNCTION(Qmutate_module_required_by_relationships_tree_for_hash_skip_list_entry);
    Qmodule_relationship_key_equal = 
	    STATIC_SYMBOL("MODULE-RELATIONSHIP-KEY-EQUAL",AB_package);
    SET_SYMBOL_FUNCTION(Qmodule_relationship_key_equal,
	    STATIC_FUNCTION(module_relationship_key_equal,NIL,FALSE,2,2));
    Qmodule_required_by_relationships_tree_for_hash = 
	    STATIC_SYMBOL("MODULE-REQUIRED-BY-RELATIONSHIPS-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    string_constant_70 = STATIC_STRING("No module named ~a was found.");
    string_constant_71 = STATIC_STRING(", the top-level module,");
    string_constant_72 = 
	    STATIC_STRING("Module ~a~a is being deleted with its associated set of system tables~a. ~a");
    string_constant_73 = 
	    STATIC_STRING(" as well as its associated set of workspaces");
    string_constant_74 = 
	    STATIC_STRING(" A new set of system tables is being installed.");
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Module_search_path_tokenizer = 
	    compile_permanent_lexing_table(Module_search_path_tokens);
    array_constant_2 = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    Qg2_module_search_path = STATIC_SYMBOL("G2-MODULE-SEARCH-PATH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_module_search_path,G2_module_search_path);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qget_initial_value_for_g2_module_search_path = 
	    STATIC_SYMBOL("GET-INITIAL-VALUE-FOR-G2-MODULE-SEARCH-PATH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_initial_value_for_g2_module_search_path,
	    STATIC_FUNCTION(get_initial_value_for_g2_module_search_path,
	    NIL,FALSE,0,0));
    list_constant_31 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_initial_value_for_g2_module_search_path);
    record_system_variable(Qg2_module_search_path,Qab_modules,
	    list_constant_31,Qnil,Qnil,Qnil,Qnil);
    Qg2_module_file_name_map = STATIC_SYMBOL("G2-MODULE-FILE-NAME-MAP",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_module_file_name_map,
	    G2_module_file_name_map);
    record_system_variable(Qg2_module_file_name_map,Qab_modules,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qgensym_pathname_for_module = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-FOR-MODULE",AB_package);
    Kb_specific_property_names = CONS(Qgensym_pathname_for_module,
	    Kb_specific_property_names);
    mutate_global_property(Qgensym_pathname_for_module,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_if_gensym_pathname = 
	    STATIC_SYMBOL("RECLAIM-IF-GENSYM-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_if_gensym_pathname,
	    STATIC_FUNCTION(reclaim_if_gensym_pathname,NIL,FALSE,1,1));
    mutate_global_property(Qgensym_pathname_for_module,
	    Qreclaim_if_gensym_pathname,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Gensym_pathname_for_module_kbprop = Qgensym_pathname_for_module;
    Qdefault_pathname_for_module = 
	    STATIC_SYMBOL("DEFAULT-PATHNAME-FOR-MODULE",AB_package);
    Kb_specific_property_names = CONS(Qdefault_pathname_for_module,
	    Kb_specific_property_names);
    mutate_global_property(Qdefault_pathname_for_module,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    mutate_global_property(Qdefault_pathname_for_module,
	    Qreclaim_if_gensym_pathname,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Default_pathname_for_module_kbprop = Qdefault_pathname_for_module;
    Qmodule_is_writable_p = STATIC_SYMBOL("MODULE-IS-WRITABLE-P",AB_package);
    Kb_specific_property_names = CONS(Qmodule_is_writable_p,
	    Kb_specific_property_names);
    mutate_global_property(Qmodule_is_writable_p,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_is_writable_p_kbprop = Qmodule_is_writable_p;
    Qmodule_is_locked_p = STATIC_SYMBOL("MODULE-IS-LOCKED-P",AB_package);
    Kb_specific_property_names = CONS(Qmodule_is_locked_p,
	    Kb_specific_property_names);
    mutate_global_property(Qmodule_is_locked_p,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_is_locked_p_kbprop = Qmodule_is_locked_p;
    Qreason_module_is_not_editable = 
	    STATIC_SYMBOL("REASON-MODULE-IS-NOT-EDITABLE",AB_package);
    Kb_specific_property_names = CONS(Qreason_module_is_not_editable,
	    Kb_specific_property_names);
    mutate_global_property(Qreason_module_is_not_editable,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_if_text_string_function = 
	    STATIC_SYMBOL("RECLAIM-IF-TEXT-STRING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_if_text_string_function,
	    STATIC_FUNCTION(reclaim_if_text_string_function,NIL,FALSE,1,1));
    mutate_global_property(Qreason_module_is_not_editable,
	    Qreclaim_if_text_string_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Reason_module_is_not_editable_kbprop = Qreason_module_is_not_editable;
    Qmodule_uses_crlf_p = STATIC_SYMBOL("MODULE-USES-CRLF-P",AB_package);
    Kb_specific_property_names = CONS(Qmodule_uses_crlf_p,
	    Kb_specific_property_names);
    mutate_global_property(Qmodule_uses_crlf_p,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_uses_crlf_p_kbprop = Qmodule_uses_crlf_p;
    Qinitial_plist_for_loaded_module = 
	    STATIC_SYMBOL("INITIAL-PLIST-FOR-LOADED-MODULE",AB_package);
    Initial_plist_for_loaded_module_prop = Qinitial_plist_for_loaded_module;
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    check_if_superior_classes_are_defined(Qserver_parameters,list_constant_15);
    string_constant_102 = 
	    STATIC_STRING("1o4z8r83Dwy83Dwy83Zry83Zry00001m1l8l1m8p83Dwy000004z8r83aZy83aZy83Zry83Zry00001m1l8l1m8p0000004z8r83Z2y83Z2y83Zry83Zry00001m1l8l");
    string_constant_103 = 
	    STATIC_STRING("1m8p0000004z8r83J=y83J=y83Zry83Zry00001m1l8l1m8p830Ky00000");
    string_constant_104 = 
	    STATIC_STRING("1q8q1n83Zry1l83-sy83ey1n83Dwy01m8p83Dwy1n83aZy01m8p01n83Z2y01m8p01n83J=y01m8p830Ky");
    temp = regenerate_optimized_constant(string_constant_85);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_102,
	    string_constant_103));
    add_class_to_environment(9,Qserver_parameters,list_constant_15,Nil,
	    temp,Nil,temp_1,list_constant_15,
	    regenerate_optimized_constant(string_constant_104),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qserver_parameters,Server_parameters);
    record_system_variable(Qserver_parameters,Qab_modules,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    string_constant_105 = STATIC_STRING("1m1m83Dwy1m9k83Zy1m83Dwy83-6xy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_105));
    string_constant_106 = 
	    STATIC_STRING("1m1n83-6xy83-8ky1ll1n83-6xy1n83-8ky1m9k83vy83-6xy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_106));
    string_constant_107 = STATIC_STRING("1l1m83-8ky83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_107));
    Qcurrent_style_if_other_than_default_qm = 
	    STATIC_SYMBOL("CURRENT-STYLE-IF-OTHER-THAN-DEFAULT\?",AB_package);
    Qg2_window_style = STATIC_SYMBOL("G2-WINDOW-STYLE",AB_package);
    alias_slot_name(3,Qcurrent_style_if_other_than_default_qm,
	    Qg2_window_style,Qserver_parameters);
    string_constant_108 = 
	    STATIC_STRING("1n1m838Zy1m9k837Ry1m838Zy1m9k83-qgy1m838Zy1m9k83-VEy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_108));
    string_constant_109 = STATIC_STRING("1m1m830Ky1m9k83Py1m830Ky838Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_109));
    Qab_standard = STATIC_SYMBOL("STANDARD",AB_package);
    Default_g2_window_style = Qab_standard;
    Qdefault_window_style = STATIC_SYMBOL("DEFAULT-WINDOW-STYLE",AB_package);
    Qcurrent_style_if_other_than_default = 
	    STATIC_SYMBOL("CURRENT-STYLE-IF-OTHER-THAN-DEFAULT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_style_if_other_than_default,
	    Current_style_if_other_than_default);
    Qget_initial_window_style = STATIC_SYMBOL("GET-INITIAL-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_initial_window_style,
	    STATIC_FUNCTION(get_initial_window_style,NIL,FALSE,0,0));
    list_constant_32 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_initial_window_style);
    record_system_variable(Qcurrent_style_if_other_than_default,
	    Qab_modules,list_constant_32,Qnil,Qnil,Qnil,Qnil);
    Qg2_5_dot_x = STATIC_SYMBOL("G2-5.X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmiscellaneous_parameters,
	    Miscellaneous_parameters);
    string_constant_75 = STATIC_STRING("-default-window-style");
    Qcommand_line_process_default_window_style = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-DEFAULT-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_default_window_style,
	    STATIC_FUNCTION(command_line_process_default_window_style,NIL,
	    FALSE,1,1));
    Qcommand_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    mutate_global_property(Qdefault_window_style,
	    Qcommand_line_process_default_window_style,
	    Qcommand_line_argument_processor);
    array_constant_5 = STATIC_ARRAY(list_constant_22,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_default_window_style = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-DEFAULT-WINDOW-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_default_window_style,
	    STATIC_FUNCTION(get_command_line_plist_element_for_default_window_style,
	    NIL,FALSE,0,0));
    Qcommand_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    mutate_global_property(Qdefault_window_style,
	    Qget_command_line_plist_element_for_default_window_style,
	    Qcommand_line_plist_element_getter);
    list_constant_33 = STATIC_CONS(Qdefault_window_style,FIX((SI_Long)0L));
    temp_2 = adjoin(2,list_constant_33,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp_2;
    Qmodule_search_path = STATIC_SYMBOL("MODULE-SEARCH-PATH",AB_package);
    Qwrite_module_search_path_from_slot = 
	    STATIC_SYMBOL("WRITE-MODULE-SEARCH-PATH-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_module_search_path_from_slot,
	    STATIC_FUNCTION(write_module_search_path_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmodule_search_path,
	    SYMBOL_FUNCTION(Qwrite_module_search_path_from_slot),
	    Qslot_value_writer);
    Qsource_code_control_support_is_enabled = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-SUPPORT-IS-ENABLED",AB_package);
    Qrestrict_edits_to_read_only_files = 
	    STATIC_SYMBOL("RESTRICT-EDITS-TO-READ-ONLY-FILES",AB_package);
    Qinitialize_for_server_parameters = 
	    STATIC_SYMBOL("INITIALIZE-FOR-SERVER-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_server_parameters,
	    STATIC_FUNCTION(initialize_for_server_parameters,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_server_parameters);
    set_get(Qserver_parameters,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qserver_parameters,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qput_module_search_path = STATIC_SYMBOL("PUT-MODULE-SEARCH-PATH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_module_search_path,
	    STATIC_FUNCTION(put_module_search_path,NIL,FALSE,3,3));
    mutate_global_property(Qmodule_search_path,
	    SYMBOL_FUNCTION(Qput_module_search_path),Qslot_putter);
    Qput_source_code_control_support_is_enabled = 
	    STATIC_SYMBOL("PUT-SOURCE-CODE-CONTROL-SUPPORT-IS-ENABLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_source_code_control_support_is_enabled,
	    STATIC_FUNCTION(put_source_code_control_support_is_enabled,NIL,
	    FALSE,3,3));
    mutate_global_property(Qsource_code_control_support_is_enabled,
	    SYMBOL_FUNCTION(Qput_source_code_control_support_is_enabled),
	    Qslot_putter);
    Qput_restrict_edits_to_read_only_files = 
	    STATIC_SYMBOL("PUT-RESTRICT-EDITS-TO-READ-ONLY-FILES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_restrict_edits_to_read_only_files,
	    STATIC_FUNCTION(put_restrict_edits_to_read_only_files,NIL,
	    FALSE,3,3));
    mutate_global_property(Qrestrict_edits_to_read_only_files,
	    SYMBOL_FUNCTION(Qput_restrict_edits_to_read_only_files),
	    Qslot_putter);
    Qput_current_style_if_other_than_default_qm = 
	    STATIC_SYMBOL("PUT-CURRENT-STYLE-IF-OTHER-THAN-DEFAULT\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_current_style_if_other_than_default_qm,
	    STATIC_FUNCTION(put_current_style_if_other_than_default_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qcurrent_style_if_other_than_default_qm,
	    SYMBOL_FUNCTION(Qput_current_style_if_other_than_default_qm),
	    Qslot_putter);
}
