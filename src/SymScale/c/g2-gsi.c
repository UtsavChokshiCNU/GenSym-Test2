/* g2-gsi.c
 * Input file:  g2-gsi.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2-gsi.h"


Object The_type_description_of_gsi_icp_interface = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_icp_interfaces, Qchain_of_available_gsi_icp_interfaces);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_icp_interface_count, Qgsi_icp_interface_count);

Object Chain_of_available_gsi_icp_interfaces_vector = UNBOUND;

/* GSI-ICP-INTERFACE-STRUCTURE-MEMORY-USAGE */
Object gsi_icp_interface_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(218,0);
    temp = Gsi_icp_interface_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GSI-ICP-INTERFACE-COUNT */
Object outstanding_gsi_icp_interface_count()
{
    Object def_structure_gsi_icp_interface_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(218,1);
    gensymed_symbol = IFIX(Gsi_icp_interface_count);
    def_structure_gsi_icp_interface_variable = 
	    Chain_of_available_gsi_icp_interfaces;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gsi_icp_interface_variable))
	goto end_loop;
    def_structure_gsi_icp_interface_variable = 
	    ISVREF(def_structure_gsi_icp_interface_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GSI-ICP-INTERFACE-1 */
Object reclaim_gsi_icp_interface_1(gsi_icp_interface)
    Object gsi_icp_interface;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(218,2);
    inline_note_reclaim_cons(gsi_icp_interface,Nil);
    structure_being_reclaimed = gsi_icp_interface;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(gsi_icp_interface,(SI_Long)2L));
      SVREF(gsi_icp_interface,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_gsi_icp_interfaces_vector,
	    IFIX(Current_thread_index));
    SVREF(gsi_icp_interface,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gsi_icp_interfaces_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gsi_icp_interface;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-ICP-INTERFACE */
Object reclaim_structure_for_gsi_icp_interface(gsi_icp_interface)
    Object gsi_icp_interface;
{
    x_note_fn_call(218,3);
    return reclaim_gsi_icp_interface_1(gsi_icp_interface);
}

static Object Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct;  /* g2-defstruct-structure-name::gsi-icp-interface-g2-struct */

/* MAKE-PERMANENT-GSI-ICP-INTERFACE-STRUCTURE-INTERNAL */
Object make_permanent_gsi_icp_interface_structure_internal()
{
    Object def_structure_gsi_icp_interface_variable;
    Object defstruct_g2_gsi_icp_interface_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(218,4);
    def_structure_gsi_icp_interface_variable = Nil;
    atomic_incff_symval(Qgsi_icp_interface_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_icp_interface_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_gsi_icp_interface_variable = the_array;
	SVREF(defstruct_g2_gsi_icp_interface_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct;
	def_structure_gsi_icp_interface_variable = 
		defstruct_g2_gsi_icp_interface_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_icp_interface_variable);
}

/* MAKE-GSI-ICP-INTERFACE-1 */
Object make_gsi_icp_interface_1(gsi_interface_frame,
	    gsi_interface_frame_serial_number,
	    gsi_interface_countdown_timer,gsi_interface_countdown_timer_limit)
    Object gsi_interface_frame, gsi_interface_frame_serial_number;
    Object gsi_interface_countdown_timer, gsi_interface_countdown_timer_limit;
{
    Object def_structure_gsi_icp_interface_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(218,5);
    def_structure_gsi_icp_interface_variable = 
	    ISVREF(Chain_of_available_gsi_icp_interfaces_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gsi_icp_interface_variable) {
	svref_arg_1 = Chain_of_available_gsi_icp_interfaces_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gsi_icp_interface_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct;
    }
    else
	def_structure_gsi_icp_interface_variable = 
		make_permanent_gsi_icp_interface_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_icp_interface_variable,Nil);
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)1L)) = 
	    gsi_interface_frame;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)2L)) = 
	    gsi_interface_frame_serial_number;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)3L)) = 
	    gsi_interface_countdown_timer;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)8L)) = 
	    gsi_interface_countdown_timer_limit;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gsi_icp_interface_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_gsi_icp_interface_variable);
}

/* RECLAIM-GSI-ICP-INTERFACE-FUNCTION */
Object reclaim_gsi_icp_interface_function(gsi_icp_interface)
    Object gsi_icp_interface;
{
    Object temp;

    x_note_fn_call(218,6);
    temp = reclaim_gsi_icp_interface_1(gsi_icp_interface);
    return VALUES_1(temp);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_gsi_icp_interface;  /* establish-new-object-index-for-gsi-icp-interface */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-GSI-ICP-INTERFACE */
Object establish_new_object_index_for_gsi_icp_interface varargs_1(int, n)
{
    Object gsi_icp_interface, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(218,7);
    INIT_ARGS_nonrelocating();
    gsi_icp_interface = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(gsi_icp_interface,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(gsi_icp_interface,(SI_Long)9L)));
	SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qestablish_new_object_index_for_gsi_icp_interface,top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_gsi_icp_interface,
			top,Nil);
	}
	gsi_icp_interface = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gsi_icp_interface;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(gsi_icp_interface,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(gsi_icp_interface,(SI_Long)9L)));
	SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_gsi_icp_interface;  /* make-corresponding-icp-gsi-icp-interface */

/* MAKE-CORRESPONDING-ICP-GSI-ICP-INTERFACE */
Object make_corresponding_icp_gsi_icp_interface(gsi_icp_interface)
    Object gsi_icp_interface;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,8);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(gsi_icp_interface,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(gsi_icp_interface,(SI_Long)9L)));
	  SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making))
	      send_icp_define_gsi_interface(corresponding_icp_object_index);
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_gsi_icp_interface,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_gsi_icp_interface,top,Nil);
	}
	gsi_icp_interface = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gsi_icp_interface;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(gsi_icp_interface,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(gsi_icp_interface,(SI_Long)9L)));
	      SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      if (EQ(icp_suspend_1,
		      send_icp_define_gsi_interface(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(corresponding_icp_object_index);
		  resumable_icp_push(Writing_resumable_icp_messages_p);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(gsi_icp_interface);
	    resumable_icp_push(Qmake_corresponding_icp_gsi_icp_interface);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-GSI-ICP-INTERFACE */
Object get_icp_object_index_for_gsi_icp_interface(gsi_icp_interface,icp_port)
    Object gsi_icp_interface, icp_port;
{
    x_note_fn_call(218,9);
    return getfq_function_no_default(ISVREF(gsi_icp_interface,(SI_Long)9L),
	    icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-GSI-ICP-INTERFACE */
Object set_icp_object_index_for_gsi_icp_interface(gsi_icp_interface,
	    corresponding_icp_object_index,icp_port)
    Object gsi_icp_interface, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(218,10);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(gsi_icp_interface,(SI_Long)9L)));
    return VALUES_1(SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-GSI-ICP-INTERFACE */
Object reclaim_icp_object_map_for_gsi_icp_interface(gsi_icp_interface)
    Object gsi_icp_interface;
{
    Object icp_object_map;

    x_note_fn_call(218,11);
    icp_object_map = ISVREF(gsi_icp_interface,(SI_Long)9L);
    if (icp_object_map)
	return reclaim_icp_object_map(gsi_icp_interface,icp_object_map,
		Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_gsi_icp_interface;  /* set-access-form-for-gsi-icp-interface */

/* RECLAIM-ICP-PORT-ENTRY-FOR-GSI-ICP-INTERFACE */
Object reclaim_icp_port_entry_for_gsi_icp_interface(gsi_icp_interface,icp_port)
    Object gsi_icp_interface, icp_port;
{
    x_note_fn_call(218,12);
    return reclaim_icp_port_entry(icp_port,gsi_icp_interface,
	    ISVREF(gsi_icp_interface,(SI_Long)9L),
	    Qset_access_form_for_gsi_icp_interface);
}

/* SET-ACCESS-FORM-FOR-GSI-ICP-INTERFACE */
Object set_access_form_for_gsi_icp_interface(gsi_icp_interface,new_value)
    Object gsi_icp_interface, new_value;
{
    x_note_fn_call(218,13);
    return VALUES_1(SVREF(gsi_icp_interface,FIX((SI_Long)9L)) = new_value);
}

static Object Qnetwork_interface;  /* network-interface */

static Object list_constant;       /* # */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qdo_not_save;        /* do-not-save */

static Object Qdo_not_put_in_attribute_tables;  /* do-not-put-in-attribute-tables */

/* ENABLE-CONTROL-OF-DISABLE-INTERLEAVING-OF-LARGE-MESSAGES */
Object enable_control_of_disable_interleaving_of_large_messages()
{
    Object scope_conses, ab_loopvar_, class_1, temp, slot_name, ab_loop_list_;
    Object slot_description, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, temp_2, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,14);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qnetwork_interface;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      slot_name = Nil;
      ab_loop_list_ = list_constant;
      slot_description = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      slot_name = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
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
    next_loop_2:
      if (level < ab_loop_bind_)
	  goto end_loop_2;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_3:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_4:
      if ( !TRUEP(marked))
	  goto end_loop_3;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_4;
    end_loop_3:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	  pred = curr;
	  curr = succ;
      }
      else
	  goto end_1;
      goto next_loop_3;
    end_loop_4:
    end_1:
      level = level - (SI_Long)1L;
      goto next_loop_2;
    end_loop_2:;
      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if ( !TRUEP(gensymed_symbol)) {
	  gensymed_symbol = class_1;
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
	      temp_2 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp_2,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp_2 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = Nil;
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
	      temp_2 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp_2,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp_2 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = Nil;
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
	  gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		  Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
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
    next_loop_5:
      if (level < ab_loop_bind_)
	  goto end_loop_5;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_6:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_7:
      if ( !TRUEP(marked))
	  goto end_loop_6;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_7;
    end_loop_6:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	  pred = curr;
	  curr = succ;
      }
      else
	  goto end_2;
      goto next_loop_6;
    end_loop_7:
    end_2:
      level = level - (SI_Long)1L;
      goto next_loop_5;
    end_loop_5:;
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
	next_loop_8:
	  if (level < ab_loop_bind_)
	      goto end_loop_8;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_9:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_10:
	  if ( !TRUEP(marked))
	      goto end_loop_9;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_10;
	end_loop_9:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_3;
	  goto next_loop_9;
	end_loop_10:
	end_3:
	  level = level - (SI_Long)1L;
	  goto next_loop_8;
	end_loop_8:;
	  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	next_loop_11:
	  if (level < ab_loop_bind_)
	      goto end_loop_11;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_12:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_13:
	  if ( !TRUEP(marked))
	      goto end_loop_12;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_13;
	end_loop_12:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_4;
	  goto next_loop_12;
	end_loop_13:
	end_4:
	  level = level - (SI_Long)1L;
	  goto next_loop_11;
	end_loop_11:;
	  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if (resulting_value);
	  else
	      resulting_value = Nil;
      }
      gensymed_symbol = resulting_value;
      slot_description = 
	      get_slot_description_of_class_description_function(slot_name,
	      gensymed_symbol,Nil);
      temp_2 = ldelete(4,Qdo_not_save,ldelete(4,
	      Qdo_not_put_in_attribute_tables,ISVREF(slot_description,
	      (SI_Long)9L),Kkey,SYMBOL_FUNCTION(Qcar)),Kkey,
	      SYMBOL_FUNCTION(Qcar));
      SVREF(slot_description,FIX((SI_Long)9L)) = temp_2;
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(Evaluation_true_value);
}

static Object Qgsi_interface;      /* gsi-interface */

static Object Qg2_to_g2_data_interface;  /* g2-to-g2-data-interface */

/* NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-NETWORK-INTERFACE */
Object note_runs_while_inactive_change_for_network_interface(network_interface)
    Object network_interface;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(218,15);
    frame = network_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)18L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qnetwork_interface)) {
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
    if ( !((SI_Long)0L != (IFIX(ISVREF(network_interface,(SI_Long)5L)) & 
	    (SI_Long)1L))) {
	if ((SI_Long)0L != (IFIX(ISVREF(network_interface,(SI_Long)4L)) & 
		(SI_Long)16777216L)) {
	    gensymed_symbol = ISVREF(network_interface,(SI_Long)1L);
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qgsi_interface,
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
		return activate_gsi_interface(network_interface,Nil);
	    else {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
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
		if (temp)
		    return activate_g2_to_g2_data_interface_with_or_without_configuration(network_interface);
		else
		    return VALUES_1(Qnil);
	    }
	}
	else {
	    gensymed_symbol = ISVREF(network_interface,(SI_Long)1L);
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qgsi_interface,
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
		return body_of_deactivate_for_gsi_interface(network_interface,
			T);
	    else {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qg2_to_g2_data_interface,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
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
		if (temp)
		    return body_of_deactivate_for_g2_to_g2_data_interface(network_interface);
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qcreation_attributes;  /* creation-attributes */

/* PUT-CREATION-ATTRIBUTES-WHERE-SLOT-IS-ABSENT */
Object put_creation_attributes_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(218,16);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,Qcreation_attributes,
	    new_value);
    return VALUES_1(Nil);
}

static Object Qitem_reference_options;  /* item-reference-options */

/* PUT-ITEM-REFERENCE-OPTIONS-WHERE-SLOT-IS-ABSENT */
Object put_item_reference_options_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(218,17);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,Qitem_reference_options,
	    new_value);
    return VALUES_1(Nil);
}

static Object Qnames_of_remote_interface;  /* names-of-remote-interface */

/* PUT-NAMES-OF-REMOTE-INTERFACE-WHERE-SLOT-IS-ABSENT */
Object put_names_of_remote_interface_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(218,18);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,
	    Qnames_of_remote_interface,new_value);
    return VALUES_1(Nil);
}

static Object Qclass_of_remote_interface;  /* class-of-remote-interface */

/* PUT-CLASS-OF-REMOTE-INTERFACE-WHERE-SLOT-IS-ABSENT */
Object put_class_of_remote_interface_where_slot_is_absent(item,new_value)
    Object item, new_value;
{
    x_note_fn_call(218,19);
    enable_references_for_item_passing();
    change_slot_value(3,Miscellaneous_parameters,
	    Qclass_of_remote_interface,new_value);
    return VALUES_1(Nil);
}

/* WRITE-GSI-INTERFACE-STATUS-CODE-FROM-SLOT */
Object write_gsi_interface_status_code_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(218,20);
    return twrite_fixnum(integer);
}

/* GSI-INTERFACE-STATUS-CODE-EVALUATION-GETTER */
Object gsi_interface_status_code_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(218,21);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_1;   /* "default to warning message level" */

static Object string_constant_2;   /* "0 (no warning or error messages)" */

static Object string_constant_3;   /* "1 (serious error messages only)" */

static Object string_constant_4;   /* "2 (all error messages)" */

static Object string_constant_5;   /* "3 (all error and warning messages)" */

/* WRITE-INTERFACE-WARNING-MESSAGE-LEVEL-FROM-SLOT */
Object write_interface_warning_message_level_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(218,22);
    if (EQ(value,Qwarning_message_level))
	temp = string_constant_1;
    else if (EQ(value,FIX((SI_Long)0L)))
	temp = string_constant_2;
    else if (EQ(value,FIX((SI_Long)1L)))
	temp = string_constant_3;
    else if (EQ(value,FIX((SI_Long)2L)))
	temp = string_constant_4;
    else if (EQ(value,FIX((SI_Long)3L)))
	temp = string_constant_5;
    else
	temp = Qnil;
    return twrite(temp);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* GSI-APPLICATION-NAME-SYMBOL-EVALUATION-SETTER */
Object gsi_application_name_symbol_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,23);
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
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_2,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gsi_application_name_symbol_evaluation_setter;
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
  end_gsi_application_name_symbol_evaluation_setter:
    return result;
}

/* GSI-APPLICATION-NAME-SYMBOL-EVALUATION-GETTER */
Object gsi_application_name_symbol_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(218,24);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* COMPILE-GSI-APPLICATION-NAME-SYMBOL-FOR-SLOT */
Object compile_gsi_application_name_symbol_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,25);
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
    return VALUES_1(parse_result);
}

/* WRITE-GSI-APPLICATION-NAME-SYMBOL-FROM-SLOT */
Object write_gsi_application_name_symbol_from_slot(symbol,gensymed_symbol)
    Object symbol, gensymed_symbol;
{
    x_note_fn_call(218,26);
    return twrite(symbol);
}

static Object Qlocalnet;           /* localnet */

/* LOCALNETP */
Object localnetp(x)
    Object x;
{
    Object temp;

    x_note_fn_call(218,27);
    temp = EQ(x,Qlocalnet) ? T : Nil;
    return VALUES_1(temp);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Qnetwork_transport;  /* network-transport */

static Object Qhostname;           /* hostname */

static Object string_constant_6;   /* "The supplied value for network-transport, ~NV, must be tcpip" */

static Object Qport;               /* port */

static Object string_constant_7;   /* "Both hostname and port must be supplied" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_8;   /* "~NT " */

static Object string_constant_9;   /* "~NV must be one of the following types: ~a" */

static Object Qnone;               /* none */

/* GSI-HOST-CONFIGURATION-EVALUATION-SETTER */
Object gsi_host_configuration_evaluation_setter(evaluation_value_qm,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value_qm, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,28);
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
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value_qm,
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value_qm,
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
		      goto end_gsi_host_configuration_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value_qm) {
	gensymed_symbol = evaluation_value_qm;
	if (type_specification_type_p(gensymed_symbol,list_constant_5)) {
	    gensymed_symbol = evaluation_value_qm;
	    temp_1 = estructure_slot(gensymed_symbol,Qnetwork_transport,Nil);
	    if (EQ(temp_1,Qlocalnet)) {
		if (Nil) {
		    temp_1 = estructure_slot(gensymed_symbol,
			    Qnetwork_transport,Nil);
		    result = phrase_cons(temp_1,
			    phrase_cons(estructure_slot(gensymed_symbol,
			    Qhostname,Nil),Nil));
		}
		else {
		    temp = Bad_phrase;
		    temp_1 = tformat_text_string(2,string_constant_6,
			    estructure_slot(gensymed_symbol,
			    Qnetwork_transport,Nil));
		    result = VALUES_2(temp,temp_1);
		}
	    }
	    else if ( !TRUEP(estructure_slot(gensymed_symbol,Qhostname,
		    Nil)) ||  !TRUEP(estructure_slot(gensymed_symbol,Qport,
		    Nil))) {
		temp = Bad_phrase;
		temp_1 = tformat_text_string(1,string_constant_7);
		result = VALUES_2(temp,temp_1);
	    }
	    else {
		temp = estructure_slot(gensymed_symbol,Qnetwork_transport,Nil);
		temp_1 = estructure_slot(gensymed_symbol,Qhostname,Nil);
		result = phrase_cons(temp,phrase_cons(temp_1,
			phrase_cons(estructure_slot(gensymed_symbol,Qport,
			Nil),Nil)));
	    }
	}
	else {
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
		      tformat(2,string_constant_8,list_constant_5);
		      type_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(3,string_constant_9,
		    gensymed_symbol,type_string);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else
	result = VALUES_1(Qnone);
  end_gsi_host_configuration_evaluation_setter:
    return result;
}

/* GSI-HOST-CONFIGURATION-EVALUATION-GETTER */
Object gsi_host_configuration_evaluation_getter(slot_value_qm,frame,
	    slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object gensymed_symbol, this_network_transport, this_hostname, this_port;
    Object temp;

    x_note_fn_call(218,29);
    if (slot_value_qm) {
	gensymed_symbol = slot_value_qm;
	this_network_transport = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	this_hostname = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	this_port = CAR(gensymed_symbol);
	if (EQ(this_network_transport,Qlocalnet)) {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qnetwork_transport,FIXNUMP(this_network_transport) || 
		    this_network_transport && 
		    SYMBOLP(this_network_transport) ? 
		    this_network_transport : 
		    copy_evaluation_value_1(this_network_transport));
	    set_evaluation_structure_slot(gensymed_symbol,Qhostname,
		    FIXNUMP(this_hostname) || this_hostname && 
		    SYMBOLP(this_hostname) ? this_hostname : 
		    copy_evaluation_value_1(this_hostname));
	    temp = gensymed_symbol;
	}
	else {
	    gensymed_symbol = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qnetwork_transport,FIXNUMP(this_network_transport) || 
		    this_network_transport && 
		    SYMBOLP(this_network_transport) ? 
		    this_network_transport : 
		    copy_evaluation_value_1(this_network_transport));
	    set_evaluation_structure_slot(gensymed_symbol,Qhostname,
		    FIXNUMP(this_hostname) || this_hostname && 
		    SYMBOLP(this_hostname) ? this_hostname : 
		    copy_evaluation_value_1(this_hostname));
	    set_evaluation_structure_slot(gensymed_symbol,Qport,
		    FIXNUMP(this_port) || this_port && SYMBOLP(this_port) ?
		     this_port : copy_evaluation_value_1(this_port));
	    temp = gensymed_symbol;
	}
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qwhole_string;       /* whole-string */

static Object array_constant;      /* # */

/* PROCESS-INITIALIZATION-STRING-EVALUATION-SETTER */
Object process_initialization_string_evaluation_setter(evaluation_value_qm,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value_qm, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,30);
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
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value_qm,
			  list_constant_6))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value_qm,
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
		      goto end_process_initialization_string_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value_qm;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
    }
    else
	result = VALUES_1(array_constant);
  end_process_initialization_string_evaluation_setter:
    return result;
}

/* PROCESS-INITIALIZATION-STRING-EVALUATION-GETTER */
Object process_initialization_string_evaluation_getter(slot_value_qm,frame,
	    slot_description)
    Object slot_value_qm, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(218,31);
    if (slot_value_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qwhole_string),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value_qm;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else
	temp = copy_as_wide_string(array_constant);
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qinterface_timeout_period;  /* interface-timeout-period */

/* PUT-GSI-INTERFACE-TIMEOUT-PERIOD-WHERE-SLOT-IS-ABSENT */
Object put_gsi_interface_timeout_period_where_slot_is_absent(gsi_interface,
	    new_gsi_interface_timeout_period)
    Object gsi_interface, new_gsi_interface_timeout_period;
{
    x_note_fn_call(218,32);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gsi_interface,Qinterface_timeout_period);
    set_lookup_slot_value_1(gsi_interface,Qinterface_timeout_period,
	    new_gsi_interface_timeout_period);
    return VALUES_1(Nil);
}

static Object Qinterval_to_poll_external_system;  /* interval-to-poll-external-system */

static Object Qtime_of_next_poll;  /* time-of-next-poll */

static Object Qfloat_array;        /* float-array */

/* PUT-INTERVAL-TO-POLL-EXTERNAL-SYSTEM */
Object put_interval_to_poll_external_system(gsi_interface,value,
	    initializing_qm)
    Object gsi_interface, value, initializing_qm;
{
    Object time_of_next_poll, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float;
    double temp, new_time_of_poll, arg, arg_1;

    x_note_fn_call(218,33);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gsi_interface,
		Qinterval_to_poll_external_system);
    set_lookup_slot_value_1(gsi_interface,
	    Qinterval_to_poll_external_system,value);
    time_of_next_poll = get_lookup_slot_value_given_default(gsi_interface,
	    Qtime_of_next_poll,Nil);
    temp = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
    new_time_of_poll = temp + (double)(FIXNUMP(value) ? IFIX(value) : 
	    (SI_Long)1L);
    if ( !TRUEP(time_of_next_poll)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	time_of_next_poll = new_float;
	set_non_savable_lookup_slot_value(gsi_interface,Qtime_of_next_poll,
		time_of_next_poll);
    }
    arg = new_time_of_poll;
    arg_1 = DFLOAT_ISAREF_1(time_of_next_poll,(SI_Long)0L);
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	DFLOAT_ISASET_1(time_of_next_poll,(SI_Long)0L,new_time_of_poll);
    return VALUES_1(value);
}

static Object Qdefault;            /* default */

static Object string_constant_10;  /* "Invalid interval ~NV should be the symbol default or a positive integer" */

/* G2-SET-GSI-INTERFACE-INTERVAL-TO-POLL-EXTERNAL-SYSTEM */
Object g2_set_gsi_interface_interval_to_poll_external_system(gsi_interface,
	    interval)
    Object gsi_interface, interval;
{
    Object top_of_stack, message_1;

    x_note_fn_call(218,34);
    if ( !(FIXNUMP(interval) && (SI_Long)0L < IFIX(interval) || 
	    EQ(interval,Qdefault))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_10,
		interval);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return change_slot_value(3,gsi_interface,
	    Qinterval_to_poll_external_system,interval);
}

/* GSI-INTERFACE-CONNECTS-WHILE-INACTIVE-P */
Object gsi_interface_connects_while_inactive_p(gsi_interface)
    Object gsi_interface;
{
    Object temp;

    x_note_fn_call(218,35);
    temp =  !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)8192L) || (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
	    (SI_Long)5L)) & (SI_Long)256L)) ? ((SI_Long)0L != 
	    (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & (SI_Long)16777216L) 
	    ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

static Object Qgsi_interface_status;  /* gsi-interface-status */

/* INITIALIZE-AFTER-READING-FOR-GSI-INTERFACE */
Object initialize_after_reading_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,36);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
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
    if (gsi_interface_connects_while_inactive_p(gsi_interface))
	activate_gsi_interface(gsi_interface,Nil);
    return update_representations_of_slot_value(2,gsi_interface,
	    Qgsi_interface_status);
}

static Object Qidentifying_attributes;  /* identifying-attributes */

/* PUT-ATTRIBUTES-WHICH-IDENTIFY-A-SENSOR-WHERE-SLOT-IS-ABSENT */
Object put_attributes_which_identify_a_sensor_where_slot_is_absent(interface_frame,
	    attributes_within_text)
    Object interface_frame, attributes_within_text;
{
    Object symbol_or_comma_headed_list, temp;

    x_note_fn_call(218,37);
    if (attributes_within_text) {
	symbol_or_comma_headed_list = CAR(attributes_within_text);
	temp = SYMBOLP(symbol_or_comma_headed_list) ? 
		slot_value_cons_1(symbol_or_comma_headed_list,Nil) : 
		copy_for_slot_value(CDR(symbol_or_comma_headed_list));
    }
    else
	temp = Nil;
    set_slot_value_function(interface_frame,Qidentifying_attributes,temp,Nil);
    reclaim_slot_value(attributes_within_text);
    return VALUES_1(Nil);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qcm;                 /* \, */

/* COMPILE-ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-FOR-SLOT */
Object compile_attributes_which_identify_a_network_item_reference_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object attribute_name_or_translation, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,38);
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
    else if (SYMBOLP(parse_result))
	return slot_value_cons_1(parse_result,Nil);
    else if (CONSP(parse_result) && EQ(M_CAR(parse_result),
	    Qclass_qualified_name))
	return slot_value_cons_1(slot_value_list_3(FIRST(parse_result),
		SECOND(parse_result),THIRD(parse_result)),Nil);
    else if (EQ(CAR(parse_result),Qcm)) {
	attribute_name_or_translation = Nil;
	ab_loop_list_ = CDR(parse_result);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute_name_or_translation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(attribute_name_or_translation))
	    temp = attribute_name_or_translation;
	else if (CONSP(attribute_name_or_translation) && 
		EQ(M_CAR(attribute_name_or_translation),Qclass_qualified_name))
	    temp = slot_value_list_3(FIRST(attribute_name_or_translation),
		    SECOND(attribute_name_or_translation),
		    THIRD(attribute_name_or_translation));
	else
	    temp = 
		    compile_network_class_attribute_translation(attribute_name_or_translation);
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
    else
	return slot_value_cons_1(compile_network_class_attribute_translation(parse_result),
		Nil);
}

/* COMPILE-NETWORK-ATTRIBUTE-TRANSLATION */
Object compile_network_attribute_translation(translation)
    Object translation;
{
    Object attr_name, thing, temp;

    x_note_fn_call(218,39);
    if (SYMBOLP(translation))
	return slot_value_cons_1(translation,Nil);
    else if (CONSP(translation) && EQ(M_CAR(translation),
	    Qclass_qualified_name)) {
	attr_name = translation;
	return slot_value_cons_1(slot_value_list_3(FIRST(attr_name),
		SECOND(attr_name),THIRD(attr_name)),Nil);
    }
    else {
	thing = FIRST(translation);
	if (CONSP(thing) && EQ(M_CAR(thing),Qclass_qualified_name)) {
	    attr_name = FIRST(translation);
	    temp = slot_value_list_3(FIRST(attr_name),SECOND(attr_name),
		    THIRD(attr_name));
	}
	else
	    temp = FIRST(translation);
	return slot_value_cons_1(temp,SECOND(translation));
    }
}

/* COMPILE-NETWORK-CLASS-ATTRIBUTE-TRANSLATION */
Object compile_network_class_attribute_translation(translation)
    Object translation;
{
    Object temp, translations, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1;

    x_note_fn_call(218,40);
    temp = SECOND(translation);
    translations = THIRD(translation);
    if (CONSP(translations) && EQ(FIRST(translations),Qcm)) {
	translation = Nil;
	ab_loop_list_ = CDR(translations);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	translation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		slot_value_cons_1(compile_network_attribute_translation(translation),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = 
		slot_value_cons_1(compile_network_attribute_translation(translations),
		Nil);
    temp_1 = slot_value_cons_1(temp,temp_1);
    return VALUES_1(temp_1);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* WRITE-ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-FROM-SLOT */
Object write_attributes_which_identify_a_network_item_reference_from_slot(identifying_attributes,
	    gensymed_symbol)
    Object identifying_attributes, gensymed_symbol;
{
    Object attribute, ab_loop_list_, attribute_cons, last_attribute_p;
    Object ab_loop_iter_flag_;

    x_note_fn_call(218,41);
    if (CONSP(identifying_attributes)) {
	attribute = Nil;
	ab_loop_list_ = identifying_attributes;
	attribute_cons = identifying_attributes;
	last_attribute_p = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    attribute_cons = M_CDR(attribute_cons);
	if ( !TRUEP(attribute_cons))
	    goto end_loop;
	last_attribute_p =  !TRUEP(CDR(attribute_cons)) ? T : Nil;
	if (SYMBOLP(attribute))
	    write_name_or_class_qualified_name(attribute);
	else
	    write_class_attribute_translation(attribute);
	if ( !TRUEP(last_attribute_p))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* WRITE-CLASS-ATTRIBUTE-TRANSLATION */
Object write_class_attribute_translation(translation)
    Object translation;
{
    Object translations, attribute, network_attribute, ab_loop_list_, tail;
    Object last_attribute_p, ab_loop_iter_flag_, ab_loop_desetq_;

    x_note_fn_call(218,42);
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)16L));
    write_name_denotation(CAR(translation));
    if (EQ(CAADR(translation),Qstar)) {
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)38L));
	write_name_denotation(CDADR(translation));
    }
    else {
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)17L));
	translations = CDR(translation);
	attribute = Nil;
	network_attribute = Nil;
	ab_loop_list_ = translations;
	tail = translations;
	last_attribute_p = Nil;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	attribute = CAR(ab_loop_desetq_);
	network_attribute = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    tail = M_CDR(tail);
	if ( !TRUEP(tail))
	    goto end_loop;
	last_attribute_p =  !TRUEP(CDR(tail)) ? T : Nil;
	write_name_denotation(attribute);
	if (network_attribute) {
	    twrite_beginning_of_wide_string(array_constant_6,
		    FIX((SI_Long)21L));
	    write_name_denotation(network_attribute);
	}
	if ( !TRUEP(last_attribute_p))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)1L));
    return VALUES_1(Nil);
}

static Object Qsc;                 /* \; */

/* COMPILE-OPTIONS-FOR-ITEM-REFERENCE-FOR-SLOT */
Object compile_options_for_item_reference_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,43);
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
    if (ATOM(parse_result))
	return VALUES_1(Nil);
    else if (EQ(CAR(parse_result),Qsc))
	return copy_tree_using_slot_value_conses_1(CDR(parse_result));
    else
	return slot_value_cons_1(copy_tree_using_slot_value_conses_1(parse_result),
		Nil);
}

static Object Qconvert_home_to_local;  /* convert-home-to-local */

static Object string_constant_11;  /* "serve items by proxy" */

static Object string_constant_12;  /* "no home conversion" */

static Object Qadd_home_to_name;   /* add-home-to-name */

static Object string_constant_13;  /* "name includes home" */

static Object Qunless_local;       /* unless-local */

static Object string_constant_14;  /* "name includes home unless local" */

static Object string_constant_15;  /* "no name conversion" */

static Object Qnon_local_item_class;  /* non-local-item-class */

static Object string_constant_16;  /* "use prefix ~S for the class of non local items,~
				    *                                     with default class ~NN"
				    */

static Object string_constant_17;  /* "use class ~NN for non local items" */

static Object string_constant_18;  /* "use prefix ~S for the class of non local items" */

static Object string_constant_19;  /* "no class conversion" */

static Object Qreference_lookup_option;  /* reference-lookup-option */

static Object string_constant_20;  /* "look up references using identifying attributes" */

static Object string_constant_21;  /* "do not look up references" */

static Object Qreference_creation_option;  /* reference-creation-option */

static Object string_constant_22;  /* "create references using creation attributes" */

static Object string_constant_23;  /* "do not create references" */

static Object array_constant_8;    /* # */

/* WRITE-OPTIONS-FOR-ITEM-REFERENCE-FROM-SLOT */
Object write_options_for_item_reference_from_slot(options,gensymed_symbol)
    Object options, gensymed_symbol;
{
    Object option, ab_loop_list_, tail, last_p, ab_loop_iter_flag_, temp;

    x_note_fn_call(218,44);
    if (options) {
	option = Nil;
	ab_loop_list_ = options;
	tail = options;
	last_p = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	option = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    tail = M_CDR(tail);
	if ( !TRUEP(tail))
	    goto end_loop;
	last_p =  !TRUEP(CDR(tail)) ? T : Nil;
	temp = FIRST(option);
	if (EQ(temp,Qconvert_home_to_local))
	    twrite_general_string(SECOND(option) ? string_constant_11 : 
		    string_constant_12);
	else if (EQ(temp,Qadd_home_to_name)) {
	    temp = SECOND(option);
	    if (EQ(temp,Qt))
		temp = string_constant_13;
	    else if (EQ(temp,Qunless_local))
		temp = string_constant_14;
	    else if (EQ(temp,Qnil))
		temp = string_constant_15;
	    else
		temp = Qnil;
	    twrite_general_string(temp);
	}
	else if (EQ(temp,Qnon_local_item_class)) {
	    if (SECOND(option)) {
		if (THIRD(option))
		    tformat(3,string_constant_16,THIRD(option),SECOND(option));
		else
		    tformat(2,string_constant_17,SECOND(option));
	    }
	    else if (THIRD(option))
		tformat(2,string_constant_18,THIRD(option));
	    else
		tformat(1,string_constant_19);
	}
	else if (EQ(temp,Qreference_lookup_option)) {
	    temp = SECOND(option);
	    if (EQ(temp,Qt))
		temp = string_constant_20;
	    else if (EQ(temp,Qnil))
		temp = string_constant_21;
	    else
		temp = Qnil;
	    twrite_general_string(temp);
	}
	else if (EQ(temp,Qreference_creation_option)) {
	    temp = SECOND(option);
	    if (EQ(temp,Qt))
		temp = string_constant_22;
	    else if (EQ(temp,Qnil))
		temp = string_constant_23;
	    else
		temp = Qnil;
	    twrite_general_string(temp);
	}
	if ( !TRUEP(last_p))
	    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)1L));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
}

DEFINE_VARIABLE_WITH_SYMBOL(No_grouping_tag_for_grouping_specification, Qno_grouping_tag_for_grouping_specification);

static Object Qno_grouping;        /* no-grouping */

/* COMPILE-GSI-VARIABLE-GROUPING-SPECIFICATION-FOR-SLOT */
Object compile_gsi_variable_grouping_specification_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,45);
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
    if (EQ(parse_result,Qno_grouping))
	return VALUES_1(Qno_grouping);
    else
	return VALUES_1(CDR(parse_result));
}

static Object Qgrouping_specification;  /* grouping-specification */

/* PUT-SENSOR-GROUPING-SPECIFICATION-WHERE-SLOT-IS-ABSENT */
Object put_sensor_grouping_specification_where_slot_is_absent(interface_frame,
	    grouping_specification_within_text)
    Object interface_frame, grouping_specification_within_text;
{
    Object old_value_within_text, temp, symbol_or_comma_headed_list;
    Object actual_value;

    x_note_fn_call(218,46);
    if (grouping_specification_within_text) {
	old_value_within_text = CAR(grouping_specification_within_text);
	if (EQ(Qno_grouping,old_value_within_text))
	    temp = No_grouping_tag_for_grouping_specification;
	else {
	    symbol_or_comma_headed_list = CADR(old_value_within_text);
	    actual_value = SYMBOLP(symbol_or_comma_headed_list) ? 
		    slot_value_cons_1(symbol_or_comma_headed_list,Nil) : 
		    copy_for_slot_value(CDR(symbol_or_comma_headed_list));
	    reclaim_slot_value(grouping_specification_within_text);
	    temp = actual_value;
	}
    }
    else
	temp = Nil;
    set_slot_value_function(interface_frame,Qgrouping_specification,temp,Nil);
    return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* WRITE-GSI-VARIABLE-GROUPING-SPECIFICATION-FROM-SLOT */
Object write_gsi_variable_grouping_specification_from_slot(grouping_specification,
	    gensymed_symbol)
    Object grouping_specification, gensymed_symbol;
{
    Object attribute, ab_loop_list_, attribute_cons, last_attribute_p;
    Object ab_loop_iter_flag_;

    x_note_fn_call(218,47);
    if (EQ(grouping_specification,No_grouping_tag_for_grouping_specification))
	return twrite_beginning_of_wide_string(array_constant_9,
		FIX((SI_Long)11L));
    else if (CONSP(grouping_specification)) {
	twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)18L));
	attribute = Nil;
	ab_loop_list_ = grouping_specification;
	attribute_cons = grouping_specification;
	last_attribute_p = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    attribute_cons = M_CDR(attribute_cons);
	if ( !TRUEP(attribute_cons))
	    goto end_loop;
	last_attribute_p =  !TRUEP(CDR(attribute_cons)) ? T : Nil;
	twrite_symbol(1,attribute);
	if ( !TRUEP(last_attribute_p))
	    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if ( !TRUEP(grouping_specification))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)0L));
    else
	return VALUES_1(Qnil);
}

static Object Qtcp_ip;             /* tcp-ip */

static Object string_constant_24;  /* "~A~A~A" */

static Object string_constant_25;  /* "" */

static Object string_constant_26;  /* "TCP/IP hostname must be text" */

static Object string_constant_27;  /* " and " */

static Object string_constant_28;  /* "TCP/IP port must be an integer" */

static Object Qlocalhost;          /* localhost */

static Object string_constant_29;  /* "LOCALNET hostname must be LOCALHOST" */

static Object string_constant_30;  /* "No port allowed in LOCALNET specification" */

static Object string_constant_31;  /* "LOCALNET is not a valid network transport" */

static Object string_constant_32;  /* "Network transport must be ~A" */

static Object string_constant_33;  /* "one of TCP-IP or LOCALNET" */

static Object string_constant_34;  /* "TCP-IP" */

/* VALID-ICP-CONNECTION-SPECIFICATION-FROM-PARSE */
Object valid_icp_connection_specification_from_parse(parse_result,
	    localnet_valid_p)
    Object parse_result, localnet_valid_p;
{
    Object gensymed_symbol, network_transport, hostname, port_qm;
    Object hostname_is_text_string_p, temp, temp_1;
    char port_is_fixnum_p, localnet_hostname_valid_p, localnet_port_valid_p;

    x_note_fn_call(218,48);
    gensymed_symbol = parse_result;
    network_transport = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    hostname = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    port_qm = CAR(gensymed_symbol);
    if (EQ(network_transport,Qtcp_ip)) {
	hostname_is_text_string_p = text_string_p(hostname);
	port_is_fixnum_p = FIXNUMP(port_qm);
	if (hostname_is_text_string_p && port_is_fixnum_p)
	    return VALUES_1(parse_result);
	else {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(4,string_constant_24,
		    hostname_is_text_string_p ? string_constant_25 : 
		    string_constant_26,hostname_is_text_string_p || 
		    port_is_fixnum_p ? string_constant_25 : 
		    string_constant_27,port_is_fixnum_p ? 
		    string_constant_25 : string_constant_28);
	    return VALUES_2(temp,temp_1);
	}
    }
    else if (EQ(network_transport,Qlocalnet)) {
	localnet_hostname_valid_p = EQ(hostname,Qlocalhost);
	localnet_port_valid_p =  !TRUEP(port_qm);
	if (localnet_valid_p && localnet_hostname_valid_p && 
		localnet_port_valid_p)
	    return VALUES_1(parse_result);
	else {
	    temp = Bad_phrase;
	    temp_1 = localnet_valid_p ? tformat_text_string(4,
		    string_constant_24,localnet_hostname_valid_p ? 
		    string_constant_25 : string_constant_29,
		    localnet_hostname_valid_p || localnet_port_valid_p ? 
		    string_constant_25 : string_constant_27,
		    localnet_port_valid_p ? string_constant_25 : 
		    string_constant_30) : copy_text_string(string_constant_31);
	    return VALUES_2(temp,temp_1);
	}
    }
    else {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_32,localnet_valid_p 
		? string_constant_33 : string_constant_34);
	return VALUES_2(temp,temp_1);
    }
}

/* COMPILE-GSI-HOST-CONFIGURATION-FOR-SLOT */
Object compile_gsi_host_configuration_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,49);
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
    if (EQ(Qnone,parse_result))
	return VALUES_1(Nil);
    else
	return valid_icp_connection_specification_from_parse(parse_result,Nil);
}

/* GSI-INTERFACE-P-FUNCTION */
Object gsi_interface_p_function(thing)
    Object thing;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(218,50);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_interface,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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

static Object array_constant_11;   /* # */

static Object string_constant_35;  /* "The interval must be less than 65535 seconds!" */

/* SLOT-VALUE-COMPILER-FOR-TIMEOUT-INTERVAL-OR-DEFAULT */
Object slot_value_compiler_for_timeout_interval_or_default(parse_result)
    Object parse_result;
{
    Object temp, temp_1;

    x_note_fn_call(218,51);
    if (EQ(parse_result,Qdefault))
	return VALUES_1(Qdefault);
    else if (IFIX(CAR(parse_result)) == (SI_Long)0L) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_11,
		FIX((SI_Long)30L));
	return VALUES_2(temp,temp_1);
    }
    else if (IFIX(integer_length(CAR(parse_result))) > (SI_Long)16L) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant_35);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(CAR(parse_result));
}

/* COMPILE-TIMEOUT-INTERVAL-OR-DEFAULT-FOR-SLOT */
Object compile_timeout_interval_or_default_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,52);
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
    return slot_value_compiler_for_timeout_interval_or_default(parse_result);
}

static Object Qunlimited;          /* unlimited */

/* COMPILE-TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-FOR-SLOT */
Object compile_timeout_interval_or_default_or_none_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,53);
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
    if (EQ(parse_result,Qunlimited))
	return VALUES_1(Nil);
    else
	return slot_value_compiler_for_timeout_interval_or_default(parse_result);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qseconds;            /* seconds */

static Object Quse_default;        /* use-default */

/* TIMEOUT-INTERVAL-OR-DEFAULT-EVALUATION-SETTER */
Object timeout_interval_or_default_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,54);
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
			  list_constant_8))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_9,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_timeout_interval_or_default_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value))
	result = phrase_cons(evaluation_value,Qseconds);
    else if (EQ(evaluation_value,Quse_default))
	result = VALUES_1(Qdefault);
    else
	result = VALUES_1(Qnil);
  end_timeout_interval_or_default_evaluation_setter:
    return result;
}

/* TIMEOUT-INTERVAL-OR-DEFAULT-EVALUATION-GETTER */
Object timeout_interval_or_default_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(218,55);
    GENSYM_RETURN_ONE( !TRUEP(slot_value) || EQ(slot_value,Qdefault) ? 
	    Quse_default : slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

/* TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-EVALUATION-SETTER */
Object timeout_interval_or_default_or_none_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,56);
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
			  list_constant_10))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_11,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_timeout_interval_or_default_or_none_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value))
	result = phrase_cons(evaluation_value,Qseconds);
    else if (EQ(evaluation_value,Quse_default))
	result = VALUES_1(Qdefault);
    else if (EQ(evaluation_value,Qunlimited))
	result = VALUES_1(Qunlimited);
    else
	result = VALUES_1(Qnil);
  end_timeout_interval_or_default_or_none_evaluation_setter:
    return result;
}

/* TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-EVALUATION-GETTER */
Object timeout_interval_or_default_or_none_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(218,57);
    if (EQ(slot_value,Qnil))
	temp = Qunlimited;
    else if (EQ(slot_value,Qdefault))
	temp = Quse_default;
    else
	temp = slot_value;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_36;  /* "use default" */

/* WRITE-TIMEOUT-INTERVAL-OR-DEFAULT-FROM-SLOT */
Object write_timeout_interval_or_default_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(218,58);
    if ( !TRUEP(value) || EQ(value,Qdefault))
	return twrite(string_constant_36);
    else if (NUMBERP(value))
	return print_constant(2,value,Qseconds);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_37;  /* "unlimited" */

/* WRITE-TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-FROM-SLOT */
Object write_timeout_interval_or_default_or_none_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(218,59);
    if ( !TRUEP(value))
	return twrite(string_constant_37);
    else if (EQ(value,Qdefault))
	return twrite(string_constant_36);
    else if (NUMBERP(value))
	return print_constant(2,value,Qseconds);
    else
	return VALUES_1(Qnil);
}

/* WRITE-GSI-VARIABLE-STATUS-CODE-FROM-SLOT */
Object write_gsi_variable_status_code_from_slot(integer,gensymed_symbol)
    Object integer, gensymed_symbol;
{
    x_note_fn_call(218,60);
    return twrite_fixnum(integer);
}

/* GSI-VARIABLE-STATUS-CODE-EVALUATION-GETTER */
Object gsi_variable_status_code_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(218,61);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

/* GSI-INTERFACE-NAME-EVALUATION-SETTER */
Object gsi_interface_name_evaluation_setter(evaluation_value_qm,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value_qm, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(218,62);
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
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value_qm,
			  list_constant_12))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value_qm,
			      list_constant_13,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_gsi_interface_name_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value_qm;
    if (temp_1)
	result = VALUES_1(temp_1);
    else
	result = VALUES_1(Qnone);
  end_gsi_interface_name_evaluation_setter:
    return result;
}

/* GSI-INTERFACE-NAME-EVALUATION-GETTER */
Object gsi_interface_name_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(218,63);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qgsi_collection_interval;  /* gsi-collection-interval */

/* RECLAIM-GSI-COLLECTION-INTERVAL-VALUE */
Object reclaim_gsi_collection_interval_value(gsi_collection_interval,
	    gsi_data_service)
    Object gsi_collection_interval, gsi_data_service;
{
    x_note_fn_call(218,64);
    reclaim_evaluation_quantity(gsi_collection_interval);
    set_non_savable_lookup_slot_value(gsi_data_service,
	    Qgsi_collection_interval,FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

static Object Qgsi_data_service;   /* gsi-data-service */

/* GSI-DATA-SERVICE-P-FUNCTION */
Object gsi_data_service_p_function(thing)
    Object thing;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(218,65);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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

static Object Qremote_process_initialization_string;  /* remote-process-initialization-string */

/* PUT-REMOTE-PROCESS-INITIALIZATION-STRING */
Object put_remote_process_initialization_string(gsi_data_service,value,
	    initializing_qm)
    Object gsi_data_service, value, initializing_qm;
{
    Object temp;

    x_note_fn_call(218,66);
    if (initializing_qm && CONSP(value)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gsi_data_service,
		    Qremote_process_initialization_string);
	temp = CAR(value);
	if (temp);
	else
	    temp = copy_constant_wide_string_given_length(array_constant,
		    FIX((SI_Long)0L));
	temp = set_lookup_slot_value_1(gsi_data_service,
		Qremote_process_initialization_string,temp);
	M_CAR(value) = Nil;
	reclaim_slot_value(value);
	return VALUES_1(temp);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gsi_data_service,
		    Qremote_process_initialization_string);
	return set_lookup_slot_value_1(gsi_data_service,
		Qremote_process_initialization_string,value);
    }
}

static Object string_constant_38;  /* "~s" */

/* WRITE-PROCESS-INITIALIZATION-STRING-FROM-SLOT */
Object write_process_initialization_string_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(218,67);
    return tformat(2,string_constant_38,value);
}

/* COMPILE-PROCESS-INITIALIZATION-STRING-FOR-SLOT */
Object compile_process_initialization_string_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,68);
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
    return VALUES_1(parse_result);
}

static Object string_constant_39;  /* "none" */

static Object array_constant_12;   /* # */

static Object string_constant_40;  /* "tcp-ip host ~S port-number ~A" */

static Object string_constant_41;  /* "[Unknown/Obsolete value: ~a / ~a / ~a]" */

/* WRITE-GSI-HOST-CONFIGURATION-FROM-SLOT */
Object write_gsi_host_configuration_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(218,69);
    if ( !TRUEP(value))
	return tformat(1,string_constant_39);
    else if (EQ(CAR(value),Qlocalnet))
	return twrite_beginning_of_wide_string(array_constant_12,
		FIX((SI_Long)14L));
    else if (EQ(CAR(value),Qtcp_ip))
	return tformat(3,string_constant_40,SECOND(value),THIRD(value));
    else
	return tformat(4,string_constant_41,FIRST(value),SECOND(value),
		THIRD(value));
}

static Object Qgsi_variable_status;  /* gsi-variable-status */

/* PUT-GSI-VARIABLE-STATUS */
Object put_gsi_variable_status(gsi_data_service,new_status,gensymed_symbol)
    Object gsi_data_service, new_status, gensymed_symbol;
{
    Object old_status, current_computation_frame;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,70);
    old_status = get_lookup_slot_value_given_default(gsi_data_service,
	    Qgsi_variable_status,FIX((SI_Long)0L));
    current_computation_frame = gsi_data_service;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(gsi_data_service,Qgsi_variable_status);
      set_lookup_slot_value_1(gsi_data_service,Qgsi_variable_status,
	      new_status);
      invoke_rules_for_attribute_change_chaining(gsi_data_service,
	      Qgsi_variable_status,old_status,Nil);
      result = VALUES_2(new_status,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qgsi_message_service;  /* gsi-message-service */

/* GSI-MESSAGE-SERVICE-P-FUNCTION */
Object gsi_message_service_p_function(thing)
    Object thing;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(218,71);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_message_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
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

static Object Qdata_server_for_messages;  /* data-server-for-messages */

/* PUT-DATA-SERVER-FOR-MESSAGES */
Object put_data_server_for_messages(gsi_message_service,new_server,
	    gensymed_symbol)
    Object gsi_message_service, new_server, gensymed_symbol;
{
    Object current_computation_frame, old_server;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,72);
    current_computation_frame = gsi_message_service;
    old_server = get_lookup_slot_value(gsi_message_service,
	    Qdata_server_for_messages);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(gsi_message_service,
		  Qdata_server_for_messages);
      set_lookup_slot_value_1(gsi_message_service,
	      Qdata_server_for_messages,new_server);
      invoke_rules_for_attribute_change_chaining(gsi_message_service,
	      Qdata_server_for_messages,old_server,Nil);
      result = VALUES_2(new_server,Nil);
    POP_SPECIAL();
    return result;
}

/* WRITE-GSI-INTERFACE-NAME-FROM-SLOT */
Object write_gsi_interface_name_from_slot(interface_name,gensymed_symbol)
    Object interface_name, gensymed_symbol;
{
    x_note_fn_call(218,73);
    if ( !TRUEP(interface_name))
	return twrite(string_constant_39);
    else
	return twrite(interface_name);
}

static Object Qgsi_interface_name;  /* gsi-interface-name */

static Object Qobject;             /* object */

static Object Qgsi_interface_icp_socket;  /* gsi-interface-icp-socket */

static Object Qexternal_system_has_a_scheduler;  /* external-system-has-a-scheduler */

/* HANDLE-UPDATE-TO-LOCATED-SENSOR-ATTRIBUTE */
Object handle_update_to_located_sensor_attribute varargs_1(int, n)
{
    Object sensor;
    Object gsi_interface_frame_qm, gsi_interface_name_qm, gsi_interface_qm;
    Object icp_socket_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,74);
    INIT_ARGS_nonrelocating();
    sensor = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    gsi_interface_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gsi_interface_name_qm = get_slot_value_if_any_function(sensor,
	    Qgsi_interface_name,Nil);
    if (gsi_interface_name_qm) {
	gsi_interface_qm = get_instance_with_name_if_any(Qobject,
		gsi_interface_name_qm);
	if (gsi_interface_qm) {
	    if (( !TRUEP(gsi_interface_frame_qm) || 
		    EQ(gsi_interface_frame_qm,gsi_interface_qm)) && 
		    (SI_Long)0L != (IFIX(ISVREF(gsi_interface_qm,
		    (SI_Long)5L)) & (SI_Long)1L)) {
		icp_socket_qm = 
			get_slot_value_if_any_function(gsi_interface_qm,
			Qgsi_interface_icp_socket,Nil);
		if (icp_socket_qm && icp_connection_open_p(icp_socket_qm) 
			&& FIXNUM_EQ(ISVREF(icp_socket_qm,(SI_Long)28L),
			Gsi_connection_established)) {
		    reconfigure_gsi_sensor_attribute(sensor);
		    if (get_slot_value_if_any_function(gsi_interface_qm,
			    Qexternal_system_has_a_scheduler,Nil))
			return gsi_collect_one_shot_data(sensor);
		    else
			return VALUES_1(Nil);
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
    else
	return VALUES_1(Nil);
}

static Object Qnames;              /* names */

/* NOTE-NAME-CHANGE-FOR-GSI-DATA-SERVICE */
Object note_name_change_for_gsi_data_service(gsi_data_service,old_names,
	    initializing_p)
    Object gsi_data_service, old_names, initializing_p;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,75);
    frame = gsi_data_service;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)10L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_data_service)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_3(method_function_qm,frame,old_names,initializing_p);
    return handle_update_to_located_sensor_attribute(2,gsi_data_service,
	    Qnames);
}

static Object Qparent_frame;       /* parent-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* HANDLE-UPDATE-TO-SENSOR-ATTRIBUTE */
Object handle_update_to_sensor_attribute(gsi_interface_frame,
	    ignored_extra_argument,parameter_or_sensor,attribute_name_qm,
	    old_value,class_if_specific_qm)
    Object gsi_interface_frame, ignored_extra_argument, parameter_or_sensor;
    Object attribute_name_qm, old_value, class_if_specific_qm;
{
    Object sensor_qm, gensymed_symbol, sub_class_bit_vector;
    Object real_attribute_name_qm, a, gensym_modify_macro_using_test_arg_1;
    Object car_1, cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object third_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(218,76);
    sensor_qm = attribute_name_qm ? parameter_or_sensor : 
	    get_lookup_slot_value_given_default(parameter_or_sensor,
	    Qparent_frame,Nil);
    if (sensor_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(sensor_qm,(SI_Long)1L),
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
    if (temp) {
	real_attribute_name_qm = attribute_name_qm;
	if (real_attribute_name_qm);
	else
	    real_attribute_name_qm = 
		    get_lookup_slot_value_given_default(parameter_or_sensor,
		    Qparent_attribute_name,Nil);
	if (real_attribute_name_qm) {
	    if (Collecting_updates_to_sensor_attributes_p) {
		a = assq_function(sensor_qm,
			Collected_updates_to_sensor_attributes);
		if ( !TRUEP(a)) {
		    a = gensym_list_3(sensor_qm,gsi_interface_frame,Nil);
		    Collected_updates_to_sensor_attributes = 
			    gensym_cons_1(a,
			    Collected_updates_to_sensor_attributes);
		}
		gensym_modify_macro_using_test_arg_1 = real_attribute_name_qm;
		car_1 = gensym_modify_macro_using_test_arg_1;
		cdr_1 = THIRD(a);
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
		third_new_value = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
		return VALUES_1(M_THIRD(a) = third_new_value);
	    }
	    else
		return handle_update_to_located_sensor_attribute(3,
			sensor_qm,real_attribute_name_qm,gsi_interface_frame);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLE-UPDATE-TO-SENSOR-DATA-TYPE */
Object handle_update_to_sensor_data_type(sensor)
    Object sensor;
{
    Object gensymed_symbol, sub_class_bit_vector, gsi_interface_name_qm;
    Object gsi_interface_qm, icp_socket_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(218,77);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)19L);
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
	gsi_interface_name_qm = get_slot_value_if_any_function(sensor,
		Qgsi_interface_name,Nil);
	if (gsi_interface_name_qm) {
	    gsi_interface_qm = get_instance_with_name_if_any(Qobject,
		    gsi_interface_name_qm);
	    if (gsi_interface_qm) {
		icp_socket_qm = 
			get_slot_value_if_any_function(gsi_interface_qm,
			Qgsi_interface_icp_socket,Nil);
		if (icp_socket_qm) {
		    if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface_qm,
			    (SI_Long)5L)) & (SI_Long)1L) && 
			    icp_connection_open_p(icp_socket_qm) && 
			    FIXNUM_EQ(ISVREF(icp_socket_qm,(SI_Long)28L),
			    Gsi_connection_established)) {
			reconfigure_gsi_sensor_attribute(sensor);
			if (get_slot_value_if_any_function(gsi_interface_qm,
				Qexternal_system_has_a_scheduler,Nil))
			    return gsi_collect_one_shot_data(sensor);
			else
			    return VALUES_1(Nil);
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
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_gsi_values_to_process_head, Qlist_of_gsi_values_to_process_head);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_gsi_values_to_process_tail, Qlist_of_gsi_values_to_process_tail);

DEFINE_VARIABLE_WITH_SYMBOL(Task_to_process_gsi_values, Qtask_to_process_gsi_values);

DEFINE_VARIABLE_WITH_SYMBOL(Task_to_process_gsi_interfaces, Qtask_to_process_gsi_interfaces);

DEFINE_VARIABLE_WITH_SYMBOL(Task_scheduled_to_process_gsi_values_qm, Qtask_scheduled_to_process_gsi_values_qm);

/* RECLAIM-GSI-LIST-WITH-EVALUATION-VALUES */
Object reclaim_gsi_list_with_evaluation_values(list_1)
    Object list_1;
{
    Object value, ab_loop_list_;

    x_note_fn_call(218,78);
    value = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	reclaim_if_evaluation_value_1(value);
    goto next_loop;
  end_loop:
    reclaim_gsi_list_1(list_1);
    return VALUES_1(Qnil);
}

static Object Qgsi_internal_collection_interval;  /* gsi-internal-collection-interval */

/* GET-OR-MAKE-GSI-SENSOR */
Object get_or_make_gsi_sensor(sensor,collection_interval)
    Object sensor, collection_interval;
{
    x_note_fn_call(218,79);
    set_slot_value_function(sensor,Qgsi_internal_collection_interval,
	    collection_interval,Nil);
    return VALUES_1(sensor);
}

DEFINE_VARIABLE_WITH_SYMBOL(Max_gsi_sensors_in_a_group, Qmax_gsi_sensors_in_a_group);

Object The_type_description_of_sensor_group = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sensor_groups, Qchain_of_available_sensor_groups);

DEFINE_VARIABLE_WITH_SYMBOL(Sensor_group_count, Qsensor_group_count);

Object Chain_of_available_sensor_groups_vector = UNBOUND;

/* SENSOR-GROUP-STRUCTURE-MEMORY-USAGE */
Object sensor_group_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(218,80);
    temp = Sensor_group_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SENSOR-GROUP-COUNT */
Object outstanding_sensor_group_count()
{
    Object def_structure_sensor_group_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(218,81);
    gensymed_symbol = IFIX(Sensor_group_count);
    def_structure_sensor_group_variable = Chain_of_available_sensor_groups;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_sensor_group_variable))
	goto end_loop;
    def_structure_sensor_group_variable = 
	    ISVREF(def_structure_sensor_group_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SENSOR-GROUP-1 */
Object reclaim_sensor_group_1(sensor_group)
    Object sensor_group;
{
    Object temp, svref_arg_2;

    x_note_fn_call(218,82);
    inline_note_reclaim_cons(sensor_group,Nil);
    temp = ISVREF(Chain_of_available_sensor_groups_vector,
	    IFIX(Current_thread_index));
    SVREF(sensor_group,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sensor_groups_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = sensor_group;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SENSOR-GROUP */
Object reclaim_structure_for_sensor_group(sensor_group)
    Object sensor_group;
{
    x_note_fn_call(218,83);
    return reclaim_sensor_group_1(sensor_group);
}

static Object Qg2_defstruct_structure_name_sensor_group_g2_struct;  /* g2-defstruct-structure-name::sensor-group-g2-struct */

/* MAKE-PERMANENT-SENSOR-GROUP-STRUCTURE-INTERNAL */
Object make_permanent_sensor_group_structure_internal()
{
    Object def_structure_sensor_group_variable;
    Object defstruct_g2_sensor_group_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(218,84);
    def_structure_sensor_group_variable = Nil;
    atomic_incff_symval(Qsensor_group_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_sensor_group_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_sensor_group_variable = the_array;
	SVREF(defstruct_g2_sensor_group_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sensor_group_g2_struct;
	def_structure_sensor_group_variable = 
		defstruct_g2_sensor_group_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_sensor_group_variable);
}

/* MAKE-SENSOR-GROUP-1 */
Object make_sensor_group_1(sensor_group_parameters,
	    sensor_group_setting_values_qm,sensor_group_collection_interval)
    Object sensor_group_parameters, sensor_group_setting_values_qm;
    Object sensor_group_collection_interval;
{
    Object def_structure_sensor_group_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(218,85);
    def_structure_sensor_group_variable = 
	    ISVREF(Chain_of_available_sensor_groups_vector,
	    IFIX(Current_thread_index));
    if (def_structure_sensor_group_variable) {
	svref_arg_1 = Chain_of_available_sensor_groups_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_sensor_group_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_sensor_group_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sensor_group_g2_struct;
    }
    else
	def_structure_sensor_group_variable = 
		make_permanent_sensor_group_structure_internal();
    inline_note_allocate_cons(def_structure_sensor_group_variable,Nil);
    SVREF(def_structure_sensor_group_variable,FIX((SI_Long)1L)) = 
	    sensor_group_parameters;
    SVREF(def_structure_sensor_group_variable,FIX((SI_Long)2L)) = 
	    sensor_group_setting_values_qm;
    SVREF(def_structure_sensor_group_variable,FIX((SI_Long)3L)) = 
	    sensor_group_collection_interval;
    ISVREF(def_structure_sensor_group_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_sensor_group_variable);
}

Object The_type_description_of_sensor_groups_header = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sensor_groups_headers, Qchain_of_available_sensor_groups_headers);

DEFINE_VARIABLE_WITH_SYMBOL(Sensor_groups_header_count, Qsensor_groups_header_count);

Object Chain_of_available_sensor_groups_headers_vector = UNBOUND;

/* SENSOR-GROUPS-HEADER-STRUCTURE-MEMORY-USAGE */
Object sensor_groups_header_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(218,86);
    temp = Sensor_groups_header_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SENSOR-GROUPS-HEADER-COUNT */
Object outstanding_sensor_groups_header_count()
{
    Object def_structure_sensor_groups_header_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(218,87);
    gensymed_symbol = IFIX(Sensor_groups_header_count);
    def_structure_sensor_groups_header_variable = 
	    Chain_of_available_sensor_groups_headers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_sensor_groups_header_variable))
	goto end_loop;
    def_structure_sensor_groups_header_variable = 
	    ISVREF(def_structure_sensor_groups_header_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SENSOR-GROUPS-HEADER-1 */
Object reclaim_sensor_groups_header_1(sensor_groups_header)
    Object sensor_groups_header;
{
    Object temp, svref_arg_2;

    x_note_fn_call(218,88);
    inline_note_reclaim_cons(sensor_groups_header,Nil);
    temp = ISVREF(Chain_of_available_sensor_groups_headers_vector,
	    IFIX(Current_thread_index));
    SVREF(sensor_groups_header,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sensor_groups_headers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = sensor_groups_header;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SENSOR-GROUPS-HEADER */
Object reclaim_structure_for_sensor_groups_header(sensor_groups_header)
    Object sensor_groups_header;
{
    x_note_fn_call(218,89);
    return reclaim_sensor_groups_header_1(sensor_groups_header);
}

static Object Qg2_defstruct_structure_name_sensor_groups_header_g2_struct;  /* g2-defstruct-structure-name::sensor-groups-header-g2-struct */

/* MAKE-PERMANENT-SENSOR-GROUPS-HEADER-STRUCTURE-INTERNAL */
Object make_permanent_sensor_groups_header_structure_internal()
{
    Object def_structure_sensor_groups_header_variable;
    Object defstruct_g2_sensor_groups_header_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(218,90);
    def_structure_sensor_groups_header_variable = Nil;
    atomic_incff_symval(Qsensor_groups_header_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_sensor_groups_header_variable = Nil;
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
	defstruct_g2_sensor_groups_header_variable = the_array;
	SVREF(defstruct_g2_sensor_groups_header_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_sensor_groups_header_g2_struct;
	def_structure_sensor_groups_header_variable = 
		defstruct_g2_sensor_groups_header_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_sensor_groups_header_variable);
}

/* MAKE-SENSOR-GROUPS-HEADER-1 */
Object make_sensor_groups_header_1()
{
    Object def_structure_sensor_groups_header_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(218,91);
    def_structure_sensor_groups_header_variable = 
	    ISVREF(Chain_of_available_sensor_groups_headers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_sensor_groups_header_variable) {
	svref_arg_1 = Chain_of_available_sensor_groups_headers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_sensor_groups_header_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_sensor_groups_header_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sensor_groups_header_g2_struct;
    }
    else
	def_structure_sensor_groups_header_variable = 
		make_permanent_sensor_groups_header_structure_internal();
    inline_note_allocate_cons(def_structure_sensor_groups_header_variable,Nil);
    return VALUES_1(def_structure_sensor_groups_header_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_all_gsi_interfaces, Qlist_of_all_gsi_interfaces);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_interfaces_to_process_head, Qgsi_interfaces_to_process_head);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_interfaces_to_process_tail, Qgsi_interfaces_to_process_tail);

/* GET-GSI-INTERFACE-FOR-GSI-SENSOR-IF-ANY */
Object get_gsi_interface_for_gsi_sensor_if_any(gsi_sensor)
    Object gsi_sensor;
{
    x_note_fn_call(218,92);
    return get_instance_with_name_if_any(Qgsi_interface,
	    get_slot_value_if_any_function(gsi_sensor,Qgsi_interface_name,
	    Nil));
}

/* RECONFIGURE-GSI-SENSOR-ATTRIBUTE */
Object reconfigure_gsi_sensor_attribute(sensor)
    Object sensor;
{
    Object gsi_interface_name, gsi_interface, gsi_icp_socket;
    Object deregister_and_register_item_p, temp;
    Declare_special(1);

    x_note_fn_call(218,93);
    gsi_interface_name = get_slot_value_if_any_function(sensor,
	    Qgsi_interface_name,Nil);
    gsi_interface = get_instance_with_name_if_any(Qobject,gsi_interface_name);
    gsi_icp_socket = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    if (gsi_interface && (SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) 
	    & (SI_Long)1L) && (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
	    (SI_Long)5L)) & (SI_Long)1L) && gsi_icp_socket && 
	    icp_connection_open_p(gsi_icp_socket) && 
	    FIXNUM_EQ(ISVREF(gsi_icp_socket,(SI_Long)28L),
	    Gsi_connection_established)) {
	deregister_and_register_item_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Deregister_and_register_item_p,Qderegister_and_register_item_p,deregister_and_register_item_p,
		0);
	  deregister_item_with_socket(sensor,gsi_icp_socket);
	  temp = register_item_with_socket(sensor,gsi_icp_socket,Nil);
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-GSI-IDENTIFYING-ATTRIBUTE-VALUES */
Object get_gsi_identifying_attribute_values(gsi_item,gsi_interface)
    Object gsi_item, gsi_interface;
{
    Object gsi_item_attribute_names, gsi_item_attribute_names_old_value, temp;
    Object temp_1, temp_2, temp_3, temp_4, temp_5;

    x_note_fn_call(218,94);
    gsi_item_attribute_names = 
	    get_slot_value_if_any_function(gsi_interface,
	    Qidentifying_attributes,Nil);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp_1 = gsi_item_attribute_value(temp,gsi_item);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp_2 = gsi_item_attribute_value(temp,gsi_item);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp_3 = gsi_item_attribute_value(temp,gsi_item);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp_4 = gsi_item_attribute_value(temp,gsi_item);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp_5 = gsi_item_attribute_value(temp,gsi_item);
    gsi_item_attribute_names_old_value = gsi_item_attribute_names;
    temp = FIRST(gsi_item_attribute_names_old_value);
    gsi_item_attribute_names = REST(gsi_item_attribute_names_old_value);
    temp = gsi_item_attribute_value(temp,gsi_item);
    return VALUES_6(temp_1,temp_2,temp_3,temp_4,temp_5,temp);
}

/* DEFINE-OR-CONFIGURE-GSI-SENSOR */
Object define_or_configure_gsi_sensor(sensor,
	    corresponding_icp_object_index,gsi_interface)
    Object sensor, corresponding_icp_object_index, gsi_interface;
{
    Object p0, p1, p2, p3, p4, p5, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(218,95);
    result = get_gsi_identifying_attribute_values(sensor,gsi_interface);
    MVS_6(result,p0,p1,p2,p3,p4,p5);
    send_icp_define_gsi_sensor(corresponding_icp_object_index,p0,p1,p2,p3,
	    p4,p5);
    gensymed_symbol = make_gsi_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = p0;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = p1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = p2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = p3;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = p4;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = p5;
    reclaim_gsi_list_with_evaluation_values(gensymed_symbol);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)2L)
	    result = collect_modifications_and_modify_gsi_sensor_definition(sensor,
		    corresponding_icp_object_index);
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* GSI-REGISTER-ITEM */
Object gsi_register_item(gsi_item,corresponding_icp_object_index,gsi_interface)
    Object gsi_item, corresponding_icp_object_index, gsi_interface;
{
    Object p0_qm, p1_qm, p2_qm, p3_qm, p4_qm, p5_qm, temp;
    Object result;

    x_note_fn_call(218,96);
    result = get_gsi_identifying_attribute_values(gsi_item,gsi_interface);
    MVS_6(result,p0_qm,p1_qm,p2_qm,p3_qm,p4_qm,p5_qm);
    temp = get_primary_name_for_frame_if_any(gsi_item);
    send_icp_register_corresponding_icp_object(corresponding_icp_object_index,
	    temp,ISVREF(ISVREF(gsi_item,(SI_Long)1L),(SI_Long)1L),p0_qm,
	    p1_qm,p2_qm,p3_qm,p4_qm,p5_qm);
    if ( !(FIXNUMP(p0_qm) || SYMBOLP(p0_qm) || SIMPLE_VECTOR_P(p0_qm)))
	reclaim_if_evaluation_value_1(p0_qm);
    if ( !(FIXNUMP(p1_qm) || SYMBOLP(p1_qm) || SIMPLE_VECTOR_P(p1_qm)))
	reclaim_if_evaluation_value_1(p1_qm);
    if ( !(FIXNUMP(p2_qm) || SYMBOLP(p2_qm) || SIMPLE_VECTOR_P(p2_qm)))
	reclaim_if_evaluation_value_1(p2_qm);
    if ( !(FIXNUMP(p3_qm) || SYMBOLP(p3_qm) || SIMPLE_VECTOR_P(p3_qm)))
	reclaim_if_evaluation_value_1(p3_qm);
    if ( !(FIXNUMP(p4_qm) || SYMBOLP(p4_qm) || SIMPLE_VECTOR_P(p4_qm)))
	reclaim_if_evaluation_value_1(p4_qm);
    if ( !(FIXNUMP(p5_qm) || SYMBOLP(p5_qm) || SIMPLE_VECTOR_P(p5_qm)))
	return reclaim_if_evaluation_value_1(p5_qm);
    else
	return VALUES_1(Nil);
}

static Object Qlong;               /* long */

static Object Qtext;               /* text */

static Object Qtruth_value;        /* truth-value */

/* COLLECT-MODIFICATIONS-AND-MODIFY-GSI-SENSOR-DEFINITION */
Object collect_modifications_and_modify_gsi_sensor_definition(sensor,
	    corresponding_icp_object_index)
    Object sensor, corresponding_icp_object_index;
{
    Object collection_interval, temp, value_type, name_of_item_qm;
    Object name_of_class;

    x_note_fn_call(218,97);
    collection_interval = get_slot_value_function(sensor,
	    Qgsi_collection_interval,Nil);
    temp = type_specification_of_variable_or_parameter_value(sensor);
    if (EQ(temp,Qnumber))
	value_type = Gsi_64bit_float_type_tag;
    else if (EQ(temp,Qinteger))
	value_type = Gsi_integer_type_tag;
    else if (EQ(temp,Qlong))
	value_type = Gsi_long_type_tag;
    else if (EQ(temp,Qfloat))
	value_type = Gsi_64bit_float_type_tag;
    else if (EQ(temp,Qsymbol))
	value_type = Gsi_symbol_type_tag;
    else if (EQ(temp,Qtext))
	value_type = Gsi_string_type_tag;
    else if (EQ(temp,Qtruth_value))
	value_type = Gsi_logical_type_tag;
    else
	value_type = Gsi_null_type_tag;
    name_of_item_qm = get_primary_name_for_frame_if_any(sensor);
    name_of_class = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)1L);
    send_icp_modify_gsi_sensor_definition(corresponding_icp_object_index,
	    collection_interval,value_type,name_of_item_qm,name_of_class);
    return VALUES_1(Nil);
}

static Object Qtelewindows;        /* telewindows */

/* MAYBE-DECLARE-ALL-GSI-SENSORS */
Object maybe_declare_all_gsi_sensors()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, sensor, gensymed_symbol;
    Object sub_class_bit_vector, gsi_interface_name, gsi_interface;
    Object sensor_icp_socket, output_port, corresponding_icp_object_index_qm;
    Object current_icp_port, current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(13);
    Object result;

    x_note_fn_call(218,98);
    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)2L) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	sensor = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,12);
	  ab_loopvar_ = collect_subclasses(Qvariable);
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
	  sensor = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ((SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) & 
		      (SI_Long)1L)) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      gsi_interface_name = get_slot_value_if_any_function(sensor,
		      Qgsi_interface_name,Nil);
	      gsi_interface = gsi_interface_name ? 
		      get_instance_with_name_if_any(Qobject,
		      gsi_interface_name) : Qnil;
	      sensor_icp_socket = gsi_interface ? 
		      get_slot_value_if_any_function(gsi_interface,
		      Qgsi_interface_icp_socket,Nil) : Qnil;
	      if (sensor_icp_socket && EQ(Current_icp_socket,
		      sensor_icp_socket)) {
		  output_port = ISVREF(Current_icp_socket,(SI_Long)4L);
		  corresponding_icp_object_index_qm = 
			  get_icp_object_index_for_registered_item(sensor,
			  output_port);
		  if (corresponding_icp_object_index_qm) {
		      current_icp_port = output_port;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			      11);
			current_icp_socket = ISVREF(Current_icp_port,
				(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
				10);
			  temp_1 = IFIX(ISVREF(Current_icp_socket,
				  (SI_Long)22L)) >= (SI_Long)17L ? 
				  ISVREF(Current_icp_socket,(SI_Long)53L) :
				   Nil;
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
					      gensymed_symbol_4 = 0.0;
					      gensymed_symbol_5 = 0.0;
					      if (Profiling_enabled_qm) {
						  gensymed_symbol = T;
						  gensymed_symbol_4 = 
							  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							  (SI_Long)2L),
							  (SI_Long)0L);
						  gensymed_symbol_5 = 
							  g2ext_unix_time_as_float();
						  aref_arg_1 = 
							  ISVREF(Profiling_enabled_qm,
							  (SI_Long)2L);
						  DFLOAT_ISASET_1(aref_arg_1,
							  (SI_Long)0L,
							  gensymed_symbol_5);
					      }
					      if (icp_connection_open_p(Current_icp_socket) 
						      &&  
						      !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
							  {
						  collect_modifications_and_modify_gsi_sensor_definition(sensor,
							  corresponding_icp_object_index_qm);
						  end_icp_message_group();
					      }
					      if (Profiling_enabled_qm) {
						  gensymed_symbol_6 = 
							  g2ext_unix_time_as_float();
						  gensymed_symbol_7 = 
							  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							  (SI_Long)2L),
							  (SI_Long)0L);
						  gensymed_symbol_8 = 
							  gensymed_symbol_6 
							  - gensymed_symbol_7;
						  aref_arg_1 = 
							  ISVREF(Profiling_enabled_qm,
							  (SI_Long)6L);
						  aref_new_value = 
							  gensymed_symbol_8 
							  + 
							  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							  (SI_Long)6L),
							  (SI_Long)0L);
						  DFLOAT_ISASET_1(aref_arg_1,
							  (SI_Long)0L,
							  aref_new_value);
						  aref_arg_1 = 
							  ISVREF(Profiling_enabled_qm,
							  (SI_Long)2L);
						  aref_new_value = 
							  gensymed_symbol ?
							   
							  gensymed_symbol_4 
							  + 
							  gensymed_symbol_8 
							  + 
							  (gensymed_symbol_7 
							  - 
							  gensymed_symbol_5) 
							  : gensymed_symbol_6;
						  DFLOAT_ISASET_1(aref_arg_1,
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
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qnever;              /* never */

static Object string_constant_42;  /* "GSI sensor ~NF received error code ~a" */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qprocess_gsi_sensor_values;  /* process-gsi-sensor-values */

/* GSI-RECEIVE-STATUS-FOR-GSI-SENSOR */
Object gsi_receive_status_for_gsi_sensor(gsi_sensor,error_code)
    Object gsi_sensor, error_code;
{
    Object sensor_status, simplep, x2, gensymed_symbol, sub_class_bit_vector;
    Object variablep, sensor_status_value, expiration_time, value, queue_entry;
    Object first_1, last_1, next, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char logical_qm, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(218,99);
    sensor_status = get_slot_value_if_any_function(gsi_sensor,
	    Qgsi_variable_status,Nil);
    simplep = FIXNUMP(sensor_status) ? T : Nil;
    if (simplep);
    else
	simplep = CONSP(sensor_status) ? T : Nil;
    if ( !TRUEP(simplep)) {
	if (SIMPLE_VECTOR_P(sensor_status) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sensor_status)) > 
		(SI_Long)2L &&  !EQ(ISVREF(sensor_status,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(sensor_status,(SI_Long)1L);
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
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		variablep = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	    }
	    else
		variablep = Nil;
	}
	else
	    variablep = Nil;
    }
    else
	variablep = Nil;
    if (simplep)
	sensor_status_value = sensor_status;
    else if (variablep) {
	expiration_time = ISVREF(sensor_status,(SI_Long)26L);
	if ( !TRUEP(expiration_time) || EQ(expiration_time,Qnever) || 
		FIXNUM_GE(expiration_time,Gensym_time)) {
	    logical_qm = EQ(ISVREF(sensor_status,(SI_Long)20L),Qtruth_value);
	    value = ISVREF(sensor_status,(SI_Long)23L);
	    if (logical_qm) {
		if (FIXNUM_EQ(value,Truth))
		    sensor_status_value = Evaluation_true_value;
		else if (FIXNUM_EQ(value,Falsity))
		    sensor_status_value = Evaluation_false_value;
		else
		    sensor_status_value = eval_cons_1(value,Qtruth_value);
	    }
	    else
		sensor_status_value = 
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			(SI_Long)0L ? copy_wide_string(value) : 
			FIXNUMP(value) || SYMBOLP(value) ? value : 
			copy_evaluation_value_1(value);
	}
	else
	    sensor_status_value = Nil;
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)3L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)3L),string_constant_42,
		    gsi_sensor,error_code);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    if ( !(FIXNUMP(sensor_status_value) && FIXNUM_EQ(sensor_status_value,
	    error_code))) {
	if (simplep)
	    change_slot_value(3,gsi_sensor,Qgsi_variable_status,error_code);
	else if (variablep) {
	    queue_entry = gsi_list_4(sensor_status,error_code,Qnever,Nil);
	    gensymed_symbol = queue_entry;
	    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
	  next_loop:
	    first_1 = List_of_gsi_values_to_process_head;
	    last_1 = List_of_gsi_values_to_process_tail;
	    next = CDR(List_of_gsi_values_to_process_tail);
	    if ( !TRUEP(first_1)) {
		if (CAS_SYMBOL(Qlist_of_gsi_values_to_process_head,first_1,
			gensymed_symbol)) {
		    CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,last_1,
			    gensymed_symbol);
		    goto end_1;
		}
	    }
	    else if (EQ(last_1,List_of_gsi_values_to_process_tail)) {
		if ( !TRUEP(next)) {
		    if (CAS_CDR(last_1,next,gensymed_symbol)) {
			CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,
				last_1,gensymed_symbol);
			goto end_1;
		    }
		}
		else
		    CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,last_1,
			    next);
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	    if ( !(Task_to_process_gsi_values && 
		    (ISVREF(Task_to_process_gsi_values,(SI_Long)6L) || 
		    EQ(Task_to_process_gsi_values,Current_schedule_task)))) {
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = Task_to_process_gsi_values;
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
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
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
		SVREF(task,FIX((SI_Long)7L)) = Qprocess_gsi_sensor_values;
		temp = SYMBOL_FUNCTION(Qprocess_gsi_sensor_values);
		SVREF(task,FIX((SI_Long)8L)) = temp;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)13L)) = T;
		new_1 = task;
		if (CAS_SYMBOL(Qtask_to_process_gsi_values,old,new_1)) {
		    task = new_1;
		    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		    if (ctask);
		    else
			ctask = System_is_running;
		    p = ISVREF(task,(SI_Long)4L);
		    v = ctask ? Current_task_queue_vector : 
			    Deferred_task_queue_vector;
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
	}
    }
    temp_1 = FIXNUM_EQ(error_code,No_error) ? T : Nil;
    return VALUES_1(temp_1);
}

static Object string_constant_43;  /* "GSI received a value for a sensor which does not exist or is ~
				    *             no longer active."
				    */

static Object string_constant_44;  /* "~a~NF received error code 0 with a NULL_TAG data type" */

static Object string_constant_45;  /* "GSI sensor " */

/* GSI-RECEIVE-VALUE-FOR-GSI-SENSOR */
Object gsi_receive_value_for_gsi_sensor(gsi_sensor,error_code,value_qm,
	    collection_time_qm,value_vector_qm)
    Object gsi_sensor, error_code, value_qm, collection_time_qm;
    Object value_vector_qm;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object g2_sensor_p, no_error_p, queue_entry, first_1, last_1, next, old;
    Object new_1, def_structure_schedule_task_variable, temp_1, svref_arg_2;
    Object svref_new_value_1, task, ctask, p, v, q, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long svref_new_value;
    char temp, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(218,100);
    if (SIMPLE_VECTOR_P(gsi_sensor) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_sensor)) > (SI_Long)2L &&  
	    !EQ(ISVREF(gsi_sensor,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(gsi_sensor,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    temp =  !(gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L));
    if (temp);
    else
	temp =  !((SI_Long)0L != (IFIX(ISVREF(gsi_sensor,(SI_Long)5L)) & 
		(SI_Long)1L));
    if (temp) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(2,FIX((SI_Long)2L),string_constant_43);
	Suppress_warning_message_header_qm = Nil;
	if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
		SIMPLE_VECTOR_P(value_qm)))
	    reclaim_if_evaluation_value_1(value_qm);
	if ( !(FIXNUMP(collection_time_qm) || SYMBOLP(collection_time_qm) 
		|| SIMPLE_VECTOR_P(collection_time_qm)))
	    reclaim_if_evaluation_value_1(collection_time_qm);
	reclaim_gsi_value_vector(value_vector_qm);
    }
    else {
	if (SIMPLE_VECTOR_P(gsi_sensor) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_sensor)) > (SI_Long)2L 
		&&  !EQ(ISVREF(gsi_sensor,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gsi_sensor,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
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
		    g2_sensor_p = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
		}
		else
		    g2_sensor_p = Nil;
	    }
	    else
		g2_sensor_p = Nil;
	}
	else
	    g2_sensor_p = Nil;
	if (g2_sensor_p) {
	    svref_new_value = IFIX(ISVREF(gsi_sensor,(SI_Long)5L)) &  
		    ~(SI_Long)4096L;
	    ISVREF(gsi_sensor,(SI_Long)5L) = FIX(svref_new_value);
	}
	no_error_p =  !TRUEP(g2_sensor_p) ? T : Nil;
	if (no_error_p);
	else
	    no_error_p = gsi_receive_status_for_gsi_sensor(gsi_sensor,
		    error_code);
	if (no_error_p && g2_sensor_p &&  !TRUEP(value_qm)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)3L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)3L),string_constant_44,
			g2_sensor_p ? string_constant_45 : 
			string_constant_25,gsi_sensor);
	    Suppress_warning_message_header_qm = Nil;
	}
	if (value_qm || value_vector_qm) {
	    queue_entry = gsi_list_4(gsi_sensor,value_qm,
		    collection_time_qm,value_vector_qm);
	    gensymed_symbol = queue_entry;
	    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
	  next_loop:
	    first_1 = List_of_gsi_values_to_process_head;
	    last_1 = List_of_gsi_values_to_process_tail;
	    next = CDR(List_of_gsi_values_to_process_tail);
	    if ( !TRUEP(first_1)) {
		if (CAS_SYMBOL(Qlist_of_gsi_values_to_process_head,first_1,
			gensymed_symbol)) {
		    CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,last_1,
			    gensymed_symbol);
		    goto end_1;
		}
	    }
	    else if (EQ(last_1,List_of_gsi_values_to_process_tail)) {
		if ( !TRUEP(next)) {
		    if (CAS_CDR(last_1,next,gensymed_symbol)) {
			CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,
				last_1,gensymed_symbol);
			goto end_1;
		    }
		}
		else
		    CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,last_1,
			    next);
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	    if ( !(Task_to_process_gsi_values && 
		    (ISVREF(Task_to_process_gsi_values,(SI_Long)6L) || 
		    EQ(Task_to_process_gsi_values,Current_schedule_task)))) {
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = Task_to_process_gsi_values;
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_1 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value_1 = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_1,svref_arg_2) = svref_new_value_1;
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
		temp_1 = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
		temp_1 = ISVREF(Data_server_parameters,(SI_Long)22L);
		SVREF(task,FIX((SI_Long)4L)) = temp_1;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		g2_p =  !TRUEP(Nil);
		SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		temp_1 = ISVREF(task,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
			Current_real_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		SVREF(task,FIX((SI_Long)7L)) = Qprocess_gsi_sensor_values;
		temp_1 = SYMBOL_FUNCTION(Qprocess_gsi_sensor_values);
		SVREF(task,FIX((SI_Long)8L)) = temp_1;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)13L)) = T;
		new_1 = task;
		if (CAS_SYMBOL(Qtask_to_process_gsi_values,old,new_1)) {
		    task = new_1;
		    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		    if (ctask);
		    else
			ctask = System_is_running;
		    p = ISVREF(task,(SI_Long)4L);
		    v = ctask ? Current_task_queue_vector : 
			    Deferred_task_queue_vector;
		    q = ISVREF(v,IFIX(p));
		    SVREF(task,FIX((SI_Long)11L)) = q;
		    temp_1 = constant_queue_push_right(q,task);
		    SVREF(task,FIX((SI_Long)6L)) = temp_1;
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
		    temp_1 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
		    temp_1 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = new_1;
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	}
	else if ( !(FIXNUMP(collection_time_qm) || 
		SYMBOLP(collection_time_qm) || 
		SIMPLE_VECTOR_P(collection_time_qm)))
	    reclaim_if_evaluation_value_1(collection_time_qm);
	if ( !(no_error_p || value_qm))
	    task_to_detect_failure(gsi_sensor);
    }
    return VALUES_1(Nil);
}

static Object Qgsi_data_server;    /* gsi-data-server */

static Object Qvalue;              /* value */

/* PROCESS-GSI-SENSOR-VALUES */
Object process_gsi_sensor_values(ok_to_put_values_qm)
    Object ok_to_put_values_qm;
{
    Object current_computation_instance, time_slice_check_p;
    Object g2_sensor_value_list, sensor, value_qm, collection_time_qm;
    Object value_vector_qm, current_computation_frame, first_1, last_1, next;
    Object gensymed_symbol, temp, x2, gensymed_symbol_1, sub_class_bit_vector;
    Object vector_element, ab_loop_list_, slot_name, new_slot_value_qm;
    Object new_slot_collection_time_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    SI_Long time_slice_check_count, counter, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp_1, g2_p;
    double aref_new_value;
    Declare_special(3);

    x_note_fn_call(218,101);
    current_computation_instance = 
	    lookup_kb_specific_property_value(Qgsi_data_server,
	    Data_server_kbprop);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
	    2);
      time_slice_check_count = (SI_Long)100L;
      counter = (SI_Long)1L;
      time_slice_check_p = Nil;
      g2_sensor_value_list = Nil;
      sensor = Nil;
      value_qm = Nil;
      collection_time_qm = Nil;
      value_vector_qm = Nil;
      current_computation_frame = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      1);
      next_loop:
	time_slice_check_p = counter >= time_slice_check_count ? T : Nil;
	if (time_slice_check_p && time_slice_expired_p())
	    goto end_loop;
	if ( !TRUEP(CAR(List_of_gsi_values_to_process_head)))
	    goto end_loop;
      next_loop_1:
	first_1 = List_of_gsi_values_to_process_head;
	last_1 = List_of_gsi_values_to_process_tail;
	next = CDR(first_1);
	if ( !TRUEP(first_1)) {
	    g2_sensor_value_list = Nil;
	    goto end_1;
	}
	else if (EQ(first_1,List_of_gsi_values_to_process_head)) {
	    if (EQ(first_1,last_1))
		CAS_SYMBOL(Qlist_of_gsi_values_to_process_tail,last_1,next);
	    else {
		gensymed_symbol = CAR(first_1);
		if (CAS_SYMBOL(Qlist_of_gsi_values_to_process_head,first_1,
			next)) {
		    reclaim_gsi_cons_1(first_1);
		    g2_sensor_value_list = gensymed_symbol;
		    goto end_1;
		}
	    }
	}
	goto next_loop_1;
      end_loop_1:
	g2_sensor_value_list = Qnil;
      end_1:
	sensor = CAR(g2_sensor_value_list);
	temp = CDR(g2_sensor_value_list);
	value_qm = CAR(temp);
	temp = CDR(g2_sensor_value_list);
	temp = CDR(temp);
	collection_time_qm = CAR(temp);
	temp = CDR(g2_sensor_value_list);
	temp = CDR(temp);
	temp = CDR(temp);
	value_vector_qm = CAR(temp);
	Current_computation_frame = sensor;
	reclaim_gsi_list_1(g2_sensor_value_list);
	temp_1 =  !TRUEP(ok_to_put_values_qm);
	if (temp_1);
	else {
	    if (SIMPLE_VECTOR_P(sensor) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sensor)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(sensor,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(sensor,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qgsi_data_service,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
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
			temp_1 = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? EQ(FIX((SI_Long)-1L),
		    get_slot_value_if_any_function(sensor,
		    Qgsi_internal_collection_interval,Nil)) : TRUEP(Nil);
	}
	if (temp_1) {
	    if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
		    SIMPLE_VECTOR_P(value_qm)))
		reclaim_if_evaluation_value_1(value_qm);
	    if ( !(FIXNUMP(collection_time_qm) || 
		    SYMBOLP(collection_time_qm) || 
		    SIMPLE_VECTOR_P(collection_time_qm)))
		reclaim_if_evaluation_value_1(collection_time_qm);
	    reclaim_gsi_value_vector(value_vector_qm);
	}
	else {
	    if (value_vector_qm) {
		vector_element = Nil;
		ab_loop_list_ = value_vector_qm;
		slot_name = Nil;
		new_slot_value_qm = Nil;
		new_slot_collection_time_qm = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		vector_element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		slot_name = CAR(vector_element);
		temp = CDR(vector_element);
		new_slot_value_qm = CAR(temp);
		temp = CDR(vector_element);
		temp = CDR(temp);
		new_slot_collection_time_qm = CAR(temp);
		if (new_slot_value_qm) {
		    gsi_ds_put_value(Current_computation_frame,slot_name,
			    new_slot_value_qm,new_slot_collection_time_qm);
		    M_CADR(vector_element) = Nil;
		    M_CADDR(vector_element) = Nil;
		}
		goto next_loop_2;
	      end_loop_2:;
		reclaim_gsi_value_vector(value_vector_qm);
	    }
	    if (value_qm)
		gsi_ds_put_value(Current_computation_frame,Qvalue,value_qm,
			collection_time_qm);
	    if (FIXNUM_LT(Priority_of_next_task,Priority_of_current_task))
		goto end_loop;
	}
	counter = time_slice_check_p ? (SI_Long)1L : counter + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (CAR(List_of_gsi_values_to_process_head)) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop_3:
	    old = Task_to_process_gsi_values;
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
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
	    temp_2 = ISVREF(Data_server_parameters,(SI_Long)22L);
	    SVREF(task,FIX((SI_Long)4L)) = temp_2;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    g2_p =  !TRUEP(Nil);
	    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		    Current_real_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
	    SVREF(task,FIX((SI_Long)7L)) = Qprocess_gsi_sensor_values;
	    temp_2 = SYMBOL_FUNCTION(Qprocess_gsi_sensor_values);
	    SVREF(task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = T;
	    new_1 = task;
	    if (CAS_SYMBOL(Qtask_to_process_gsi_values,old,new_1)) {
		task = new_1;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp_2 = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp_2;
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
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = new_1;
	    }
	    goto next_loop_3;
	  end_loop_3:
	  end_2:;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_46;  /* "Can not conclude a value into ~NF, ~
				    *                                            because it is not a variable or parameter"
				    */

static Object Qiteration_state;    /* iteration-state */

static Object string_constant_47;  /* "Can not conclude ~NF into ~NF, ~
				    *                                            because it is not a value"
				    */

static Object Qdatum;              /* datum */

static Object Qquantity;           /* quantity */

static Object string_constant_48;  /* "Can not conclude ~NV into ~NF, ~
				    *                                            because it is not of the correct type"
				    */

static Object string_constant_49;  /* "Problem receiving GSI value: ~a" */

static Object Qvector_element;     /* vector-element */

static Object string_constant_50;  /* "~NF is not an array" */

static Object string_constant_51;  /* "array index out of bounds" */

static Object Qlist_element;       /* list-element */

static Object string_constant_52;  /* "~NF is not an list" */

static Object string_constant_53;  /* "list index out of bounds" */

static Object string_constant_54;  /* "gsi_return_attrs into a list: not yet implemented" */

static Object Qg2_array_length;    /* g2-array-length */

/* GSI-DS-PUT-VALUE */
Object gsi_ds_put_value(frame,slot_name,value,collection_time_qm)
    Object frame, slot_name, value, collection_time_qm;
{
    Object gensymed_symbol, old_star_current_computation_frame_star;
    Object managed_float_collection_time_p, x2, sub_class_bit_vector;
    Object problem_string_qm, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, type, index_1;
    Object unqualified_name, class_qualifier, attribute_description_qm;
    Object current_value, error_string_qm, current_size;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, length_1;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(218,102);
    if (EQ(slot_name,Qvalue)) {
	gensymed_symbol = Nil;
	old_star_current_computation_frame_star = Current_computation_frame;
	Current_computation_frame = frame;
	managed_float_collection_time_p = 
		INLINE_DOUBLE_FLOAT_VECTOR_P(collection_time_qm) != 
		(SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_time_qm)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
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
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	if ( !temp)
	    problem_string_qm = tformat_text_string(2,string_constant_46,
		    frame);
	else {
	    gensymed_symbol = value;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
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
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		problem_string_qm = tformat_text_string(3,
			string_constant_47,value,frame);
	    else {
		type = get_effective_data_type(frame);
		if (EQ(type,Qvalue))
		    temp_2 = Qdatum;
		else if (EQ(type,Qquantity))
		    temp_2 = Qnumber;
		else
		    temp_2 = type;
		if ( !TRUEP(type_specification_type_p(value,temp_2)))
		    problem_string_qm = tformat_text_string(3,
			    string_constant_48,value,frame);
		else {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
			problem_string_qm = 
				put_current_evaluation_value(Current_computation_frame,
				value,Nil,managed_float_collection_time_p ?
				 collection_time_qm : Nil,Nil);
		    POP_LOCAL_ALLOCATION(0,0);
		}
	    }
	}
	if (managed_float_collection_time_p)
	    reclaim_managed_simple_float_array_of_length_1(collection_time_qm);
	if (problem_string_qm) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_49,
			problem_string_qm);
	    reclaim_text_string(problem_string_qm);
	    gensymed_symbol = reclaim_evaluation_value(value);
	}
	else
	    gensymed_symbol = Nil;
	Current_computation_frame = old_star_current_computation_frame_star;
	return VALUES_1(gensymed_symbol);
    }
    else if (CONSP(slot_name) && EQ(CAR(slot_name),Qvector_element)) {
	index_1 = FIXNUMP(slot_name) ? slot_name : SECOND(slot_name);
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	if ( !temp)
	    problem_string_qm = tformat_text_string(2,string_constant_50,
		    frame);
	else if ( !((SI_Long)0L <= IFIX(index_1) && FIXNUM_LT(index_1,
		ISVREF(frame,(SI_Long)20L))))
	    problem_string_qm = tformat_text_string(1,string_constant_51);
	else {
	    mutate_g2_array(frame,index_1,value,T,Nil);
	    problem_string_qm = Nil;
	}
	if (problem_string_qm) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_49,
			problem_string_qm);
	    return reclaim_text_string(problem_string_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(slot_name) && EQ(CAR(slot_name),Qlist_element)) {
	index_1 = FIXNUMP(slot_name) ? slot_name : SECOND(slot_name);
	length_1 = (SI_Long)0L;
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
	if ( !temp)
	    problem_string_qm = tformat_text_string(2,string_constant_52,
		    frame);
	else if ( !((SI_Long)0L <= IFIX(index_1) && IFIX(index_1) < length_1))
	    problem_string_qm = tformat_text_string(1,string_constant_53);
	else
	    problem_string_qm = tformat_text_string(1,string_constant_54);
	if (problem_string_qm) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_49,
			problem_string_qm);
	    return reclaim_text_string(problem_string_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	unqualified_name = CONSP(slot_name) ? 
		M_CAR(M_CDR(M_CDR(slot_name))) : slot_name;
	class_qualifier = CONSP(slot_name) ? M_CAR(M_CDR(slot_name)) : Nil;
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(Current_computation_frame,
		(SI_Long)1L),unqualified_name,class_qualifier);
	current_value = attribute_description_qm ? 
		get_attribute_description_evaluation_value(Current_computation_frame,
		attribute_description_qm) : Qnil;
	if ( !TRUEP(attribute_description_qm)) {
	    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
		reclaim_if_evaluation_value_1(value);
	    if ( !(FIXNUMP(collection_time_qm) || 
		    SYMBOLP(collection_time_qm) || 
		    SIMPLE_VECTOR_P(collection_time_qm)))
		return reclaim_if_evaluation_value_1(collection_time_qm);
	    else
		return VALUES_1(Nil);
	}
	else {
	    if (SIMPLE_VECTOR_P(current_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(current_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(current_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp) {
		if ( !(FIXNUMP(collection_time_qm) || 
			SYMBOLP(collection_time_qm) || 
			SIMPLE_VECTOR_P(collection_time_qm)))
		    reclaim_if_evaluation_value_1(collection_time_qm);
		if ( !(FIXNUMP(current_value) || SYMBOLP(current_value) || 
			SIMPLE_VECTOR_P(current_value)))
		    reclaim_if_evaluation_value_1(current_value);
		error_string_qm = 
			change_attribute_description_evaluation_value(Current_computation_frame,
			attribute_description_qm,value);
		if (error_string_qm) {
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)1L),
				string_constant_49,error_string_qm);
		    return reclaim_text_string(error_string_qm);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(current_value,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
		if (temp)
		    return gsi_ds_put_value(current_value,Qvalue,value,
			    collection_time_qm);
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(current_value,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(G2_list_class_description,
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
		    if (temp) {
			if ( !(FIXNUMP(collection_time_qm) || 
				SYMBOLP(collection_time_qm) || 
				SIMPLE_VECTOR_P(collection_time_qm)))
			    reclaim_if_evaluation_value_1(collection_time_qm);
			if (SIMPLE_VECTOR_P(value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
				(SI_Long)2L &&  !EQ(ISVREF(value,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(value,(SI_Long)1L);
			    gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				    EQ(ISVREF(x2,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    gensymed_symbol = Nil;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(G2_list_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_1 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_2 = (SI_Long)1L;
				gensymed_symbol_3 = 
					superior_class_bit_number & 
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
			if (temp)
			    return reclaim_evaluation_value(value);
			else if (datum_ok_for_g2_list_or_array_p(value,
				ISVREF(current_value,(SI_Long)21L)))
			    return g2_list_insert_at_end(2,value,
				    current_value);
			else
			    return reclaim_evaluation_value(value);
		    }
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(current_value,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(G2_array_class_description,
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
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if ( !(FIXNUMP(collection_time_qm) || 
				    SYMBOLP(collection_time_qm) || 
				    SIMPLE_VECTOR_P(collection_time_qm)))
				reclaim_if_evaluation_value_1(collection_time_qm);
			    if (SIMPLE_VECTOR_P(value) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) 
				    > (SI_Long)2L &&  !EQ(ISVREF(value,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(value,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(G2_array_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_1 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				return reclaim_evaluation_value(value);
			    else if (datum_ok_for_g2_list_or_array_p(value,
				    ISVREF(current_value,(SI_Long)21L))) {
				current_size = ISVREF(current_value,
					(SI_Long)20L);
				change_slot_value(3,current_value,
					Qg2_array_length,
					FIXNUM_ADD1(current_size));
				return mutate_g2_array(current_value,
					current_size,value,T,T);
			    }
			    else
				return reclaim_evaluation_value(value);
			}
			else {
			    reclaim_evaluation_value(value);
			    if ( !(FIXNUMP(collection_time_qm) || 
				    SYMBOLP(collection_time_qm) || 
				    SIMPLE_VECTOR_P(collection_time_qm)))
				return reclaim_if_evaluation_value_1(collection_time_qm);
			    else
				return VALUES_1(Nil);
			}
		    }
		}
	    }
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_sockets_now_initializing_gsi, Qicp_sockets_now_initializing_gsi);

/* WRITE-MESSAGE-GROUP-UPON-GSI-INTERFACE-ACTIVATION */
Object write_message_group_upon_gsi_interface_activation(icp_socket,
	    process_initialization_string,interface_struct)
    Object icp_socket, process_initialization_string, interface_struct;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, index_1, gensymed_symbol_3;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    double gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    double gensymed_symbol_8, aref_new_value;
    Declare_special(24);

    x_note_fn_call(218,103);
    current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    23);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      22);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		21);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  20);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    19);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      18);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			17);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  16);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    15);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      14);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				13);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  12);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = process_initialization_string;
				if (temp);
				else
				    temp = array_constant;
				send_icp_initialize_data_server(temp);
				if ( 
					!TRUEP(get_icp_object_index_for_gsi_icp_interface(interface_struct,
					Current_icp_port)))
				    make_corresponding_icp_gsi_icp_interface(interface_struct);
				temp = 
					get_icp_object_index_for_gsi_icp_interface(interface_struct,
					Current_icp_port);
				if (temp);
				else {
				    index_1 = FIX((SI_Long)0L);
				    current_icp_port = 
					    ISVREF(Current_icp_socket,
					    (SI_Long)4L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
					    11);
				      current_icp_socket = 
					      ISVREF(Current_icp_port,
					      (SI_Long)2L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
					      10);
					temp = 
						IFIX(ISVREF(Current_icp_socket,
						(SI_Long)22L)) >= 
						(SI_Long)17L ? 
						ISVREF(Current_icp_socket,
						(SI_Long)53L) : Nil;
					if (temp);
					else
					    temp = 
						    EQ(ISVREF(Current_icp_socket,
						    (SI_Long)25L),
						    Qtelewindows) ? T : Nil;
					disable_resumability = temp;
					PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
						9);
					  number_of_icp_bytes_for_message_series 
						  = FIX((SI_Long)0L);
					  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
						  8);
					    icp_buffers_for_message_group 
						    = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
						    7);
					      icp_buffer_of_start_of_message_series_qm 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
						      6);
						icp_byte_position_of_start_of_message_series_qm 
							= Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
							5);
						  number_of_icp_bytes_to_fill_buffer 
							  = FIX((SI_Long)0L);
						  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
							  4);
						    current_icp_buffer = Nil;
						    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
							    3);
						      current_write_icp_byte_position 
							      = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
							      2);
							number_of_icp_bytes_in_message_group 
								= 
								FIX((SI_Long)0L);
							PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
								1);
							  writing_icp_message_group 
								  = 
								  FIXNUM_ADD1(Writing_icp_message_group);
							  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
								  0);
							    gensymed_symbol_3 
								    = Nil;
							    gensymed_symbol_4 
								    = 0.0;
							    gensymed_symbol_5 
								    = 0.0;
							    if (Profiling_enabled_qm) 
									{
								gensymed_symbol_3 
									= T;
								gensymed_symbol_4 
									= 
									DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
									(SI_Long)2L),
									(SI_Long)0L);
								gensymed_symbol_5 
									= 
									g2ext_unix_time_as_float();
								temp_1 = 
									ISVREF(Profiling_enabled_qm,
									(SI_Long)2L);
								DFLOAT_ISASET_1(temp_1,
									(SI_Long)0L,
									gensymed_symbol_5);
							    }
							    if (icp_connection_open_p(Current_icp_socket) 
								    &&  
								    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
									{
								index_1 = 
									make_corresponding_icp_gsi_icp_interface(interface_struct);
								end_icp_message_group();
							    }
							    if (Profiling_enabled_qm) 
									{
								gensymed_symbol_6 
									= 
									g2ext_unix_time_as_float();
								gensymed_symbol_7 
									= 
									DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
									(SI_Long)2L),
									(SI_Long)0L);
								gensymed_symbol_8 
									= 
									gensymed_symbol_6 
									- 
									gensymed_symbol_7;
								temp_1 = 
									ISVREF(Profiling_enabled_qm,
									(SI_Long)6L);
								aref_new_value 
									= 
									gensymed_symbol_8 
									+ 
									DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
									(SI_Long)6L),
									(SI_Long)0L);
								DFLOAT_ISASET_1(temp_1,
									(SI_Long)0L,
									aref_new_value);
								temp_1 = 
									ISVREF(Profiling_enabled_qm,
									(SI_Long)2L);
								aref_new_value 
									= 
									gensymed_symbol_3 
									? 
									gensymed_symbol_4 
									+ 
									gensymed_symbol_8 
									+ 
									(gensymed_symbol_7 
									- 
									gensymed_symbol_5) 
									: 
									gensymed_symbol_6;
								DFLOAT_ISASET_1(temp_1,
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
				    temp = index_1;
				}
				send_icp_send_data_values_if_any(temp,
					FIX((SI_Long)0L),FIX((SI_Long)0L),
					FIX((SI_Long)0L),FIX((SI_Long)1L),
					FIX((SI_Long)1L),FIX((SI_Long)1970L));
				end_icp_message_group();
			    }
			    if (Profiling_enabled_qm) {
				gensymed_symbol_4 = g2ext_unix_time_as_float();
				gensymed_symbol_5 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_6 = gensymed_symbol_4 - 
					gensymed_symbol_5;
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_6 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					aref_new_value);
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_6 + 
					(gensymed_symbol_5 - 
					gensymed_symbol_2) : gensymed_symbol_4;
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
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
    SVREF(interface_struct,FIX((SI_Long)5L)) = Nil;
    temp_1 = Gsi_connection_initializing;
    return VALUES_1(SVREF(icp_socket,FIX((SI_Long)28L)) = temp_1);
}

/* ACTIVATE-FOR-GSI-INTERFACE */
Object activate_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object code, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,104);
    code = M_CAR(M_CDR(Overflow_byte_count));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)1L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gsi_semantics_graph))) : TRUEP(Nil)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
		(SI_Long)16777216L)))
	    activate_gsi_interface(gsi_interface,Nil);
	schedule_data_server_accept_data_calls();
	frame = gsi_interface;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
	    method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	method_function_qm = Qnil;
      end_1:;
	if (method_function_qm)
	    return inline_funcall_1(method_function_qm,frame);
	else
	    return VALUES_1(Nil);
    }
    else
	return parse_gsi_schedule_tree();
}

/* MANUALLY-ENABLE-FOR-GSI-INTERFACE */
Object manually_enable_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,105);
    if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	activate_gsi_interface(gsi_interface,Nil);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)48L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* GSI-ICP-SOCKET-CONNECTED-P */
Object gsi_icp_socket_connected_p(gsi_interface)
    Object gsi_interface;
{
    Object interface_icp_socket_qm, connected_p;

    x_note_fn_call(218,106);
    interface_icp_socket_qm = get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil);
    connected_p = interface_icp_socket_qm && 
	    icp_connection_open_p(interface_icp_socket_qm) ? ( 
	    !TRUEP(icp_connection_being_shutdown_qm(interface_icp_socket_qm)) 
	    ? T : Nil) : Qnil;
    return VALUES_1(connected_p);
}

/* NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-GSI-INTERFACE */
Object note_ancestor_manually_enabled_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    x_note_fn_call(218,107);
    if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)16777216L)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
		(SI_Long)8192L))) {
	    if ( !TRUEP(gsi_icp_socket_connected_p(gsi_interface)))
		return activate_gsi_interface(gsi_interface,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maintaining_gsi_interface_status_changed_p, Qmaintaining_gsi_interface_status_changed_p);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_interface_status_changed_p, Qgsi_interface_status_changed_p);

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_55;  /* "GSI interface ~NF has invalid status ~a" */

static Object Qgsi_interface_is_secure;  /* gsi-interface-is-secure */

/* CHANGE-GSI-INTERFACE-STATUS */
Object change_gsi_interface_status(gsi_interface_frame,new_status)
    Object gsi_interface_frame, new_status;
{
    Object gsi_interface_status_slot_value_qm, current_computation_frame, x2;
    Object sub_class_bit_vector, current_computation_instance;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(218,108);
    if (Maintaining_gsi_interface_status_changed_p)
	Gsi_interface_status_changed_p = T;
    gsi_interface_status_slot_value_qm = 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_status,Nil);
    if (INTEGERP(gsi_interface_status_slot_value_qm) || 
	    CONSP(gsi_interface_status_slot_value_qm)) {
	current_computation_frame = gsi_interface_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  change_slot_value(3,gsi_interface_frame,Qgsi_interface_status,
		  new_status);
	POP_SPECIAL();
    }
    else {
	if (SIMPLE_VECTOR_P(gsi_interface_status_slot_value_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_interface_status_slot_value_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(gsi_interface_status_slot_value_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gsi_interface_status_slot_value_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = 
		    ISVREF(ISVREF(gsi_interface_status_slot_value_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	    current_computation_frame = gsi_interface_status_slot_value_qm;
	    current_computation_instance = 
		    lookup_kb_specific_property_value(Qgsi_data_server,
		    Data_server_kbprop);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		put_current_value(5,gsi_interface_status_slot_value_qm,
			new_status,Qnumber,Nil,Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			  tformat(3,string_constant_55,gsi_interface_frame,
				  gsi_interface_status_slot_value_qm);
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
    change_slot_value(3,gsi_interface_frame,Qgsi_interface_is_secure,
	    icp_connection_is_secure(get_lookup_slot_value_given_default(gsi_interface_frame,
	    Qgsi_interface_icp_socket,Nil)));
    return VALUES_1(Nil);
}

/* GET-GSI-INTERFACE-STATUS */
Object get_gsi_interface_status(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object gsi_interface_status_slot_value_qm, x2, sub_class_bit_vector;
    Object current_computation_frame, current_computation_instance;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,109);
    SAVE_STACK();
    gsi_interface_status_slot_value_qm = 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_status,Nil);
    if (INTEGERP(gsi_interface_status_slot_value_qm) || 
	    CONSP(gsi_interface_status_slot_value_qm)) {
	RESTORE_STACK();
	return VALUES_1(gsi_interface_status_slot_value_qm);
    }
    else {
	if (SIMPLE_VECTOR_P(gsi_interface_status_slot_value_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_interface_status_slot_value_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(gsi_interface_status_slot_value_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(gsi_interface_status_slot_value_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = 
		    ISVREF(ISVREF(gsi_interface_status_slot_value_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	    current_computation_frame = gsi_interface_status_slot_value_qm;
	    current_computation_instance = 
		    lookup_kb_specific_property_value(Qgsi_data_server,
		    Data_server_kbprop);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		result = get_current_value(gsi_interface_status_slot_value_qm,
			T);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    RESTORE_STACK();
	    return result;
	}
	else if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			  tformat(3,string_constant_55,gsi_interface_frame,
				  gsi_interface_status_slot_value_qm);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		SAVE_VALUES(notify_user_1(temp_1));
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
}

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_connection_checkup_interval_in_ms, Qgsi_connection_checkup_interval_in_ms);

static Object string_constant_56;  /* "You must specify the identifying attributes for GSI interface ~NF." */

/* MAYBE-WARN-ABOUT-MISSING-IDENTIFYING-ATTRIBUTES */
Object maybe_warn_about_missing_identifying_attributes(interface_name_or_names_qm,
	    gsi_interface_frame)
    Object interface_name_or_names_qm, gsi_interface_frame;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, sensor;
    Object desired_interface_name, ab_loop_it_, gensymed_symbol;
    Object sub_class_bit_vector, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,110);
    SAVE_STACK();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    sensor = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      desired_interface_name = Nil;
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qvariable);
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
      sensor = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      desired_interface_name = get_slot_value_if_any_function(sensor,
	      Qgsi_interface_name,Nil);
      gensymed_symbol = 
	      lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	      Class_description_gkbprop);
      if (gensymed_symbol) {
	  sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),
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
      ab_loop_it_ = temp ? (CONSP(interface_name_or_names_qm) ? 
	      memq_function(desired_interface_name,
	      interface_name_or_names_qm) : EQ(desired_interface_name,
	      interface_name_or_names_qm) ? T : Nil) : Nil;
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if (temp) {
	if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			  tformat(2,string_constant_56,gsi_interface_frame);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		SAVE_VALUES(notify_user_1(temp_1));
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
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* ACTIVATE-VARIABLES-FOR-GSI-INTERFACE */
Object activate_variables_for_gsi_interface(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object interface_name_or_names_qm, attributes_which_identify_a_sensor_qm;

    x_note_fn_call(218,111);
    interface_name_or_names_qm = 
	    get_primary_name_for_frame_if_any(gsi_interface_frame);
    attributes_which_identify_a_sensor_qm = 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qidentifying_attributes,Nil);
    if (interface_name_or_names_qm) {
	if ( !TRUEP(attributes_which_identify_a_sensor_qm)) {
	    maybe_warn_about_missing_identifying_attributes(interface_name_or_names_qm,
		    gsi_interface_frame);
	    return VALUES_1(Nil);
	}
	return install_true_value_updates_for_gsi(gsi_interface_frame,Nil,
		attributes_which_identify_a_sensor_qm);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-BEGIN-COLLECTING-DATA-FOR-INTERFACE */
Object maybe_begin_collecting_data_for_interface(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object interface_name_or_names_qm, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, sensor, desired_interface_name, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, gensymed_symbol, sub_class_bit_vector;
    Object begin_collecting_data_list, gsi_variables_qm, gsi_variable_qm;
    Object gsi_variables_qm_old_value, temp_1, data_collection_interval;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long ab_loop_repeat_, svref_new_value;
    char temp;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(218,112);
    if (System_has_paused || System_is_running) {
	interface_name_or_names_qm = 
		get_primary_name_for_frame_if_any(gsi_interface_frame);
	if (interface_name_or_names_qm) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    sensor = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      desired_interface_name = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__3 = Nil;
	      ab_loopvar__4 = Nil;
	      ab_loopvar_ = collect_subclasses(Qvariable);
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
	      sensor = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      desired_interface_name = 
		      get_slot_value_if_any_function(sensor,
		      Qgsi_interface_name,Nil);
	      if ((SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) & 
		      (SI_Long)1L)) {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(Qgsi_data_service,
			  Class_description_gkbprop);
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(ISVREF(sensor,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ? (CONSP(interface_name_or_names_qm) ? 
		      TRUEP(memq_function(desired_interface_name,
		      interface_name_or_names_qm)) : 
		      EQ(desired_interface_name,
		      interface_name_or_names_qm)) : TRUEP(Nil)) {
		  ab_loopvar__4 = gsi_cons_1(sensor,Nil);
		  if (ab_loopvar__3)
		      M_CDR(ab_loopvar__3) = ab_loopvar__4;
		  else
		      ab_loopvar__2 = ab_loopvar__4;
		  ab_loopvar__3 = ab_loopvar__4;
	      }
	      goto next_loop;
	    end_loop_1:
	      begin_collecting_data_list = ab_loopvar__2;
	      goto end_1;
	      begin_collecting_data_list = Qnil;
	    end_1:;
	    POP_SPECIAL();
	}
	else
	    begin_collecting_data_list = Nil;
	gsi_variables_qm = begin_collecting_data_list;
      next_loop_2:
	if ( !TRUEP(gsi_variables_qm))
	    goto end_loop_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    ab_loop_repeat_ = 
		    IFIX(Iterations_for_gsi_temporary_float_processing);
	    gsi_variable_qm = Nil;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    gsi_variables_qm_old_value = gsi_variables_qm;
	    temp_1 = FIRST(gsi_variables_qm_old_value);
	    gsi_variables_qm = REST(gsi_variables_qm_old_value);
	    gsi_variable_qm = temp_1;
	    if ( !TRUEP(gsi_variable_qm))
		goto end_loop_3;
	    svref_new_value = IFIX(ISVREF(gsi_variable_qm,(SI_Long)5L)) &  
		    ~(SI_Long)4096L;
	    ISVREF(gsi_variable_qm,(SI_Long)5L) = FIX(svref_new_value);
	    data_collection_interval = 
		    get_slot_value_function(gsi_variable_qm,
		    Qgsi_collection_interval,Nil);
	    if (evaluation_quantity_gt(data_collection_interval,
		    FIX((SI_Long)0L)))
		gsi_begin_collecting_data(gsi_variable_qm,
			data_collection_interval);
	    goto next_loop_3;
	  end_loop_3:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	goto next_loop_2;
      end_loop_2:;
	return reclaim_gsi_list_1(begin_collecting_data_list);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-STOP-COLLECTING-DATA-FOR-INTERFACE */
Object maybe_stop_collecting_data_for_interface(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object interface_name_or_names_qm, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, sensor, desired_interface_name, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,113);
    interface_name_or_names_qm = 
	    get_primary_name_for_frame_if_any(gsi_interface_frame);
    if (interface_name_or_names_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	sensor = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  desired_interface_name = Nil;
	  ab_loopvar_ = collect_subclasses(Qvariable);
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
	  sensor = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  desired_interface_name = get_slot_value_if_any_function(sensor,
		  Qgsi_interface_name,Nil);
	  if ((SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) & 
		      (SI_Long)1L)) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ? (CONSP(interface_name_or_names_qm) ? 
		  TRUEP(memq_function(desired_interface_name,
		  interface_name_or_names_qm)) : EQ(desired_interface_name,
		  interface_name_or_names_qm)) : TRUEP(Nil))
	      deactivate_dataservice_for_gsi_data_service(sensor);
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* GSI-INTERFACE-CURRENT-ICP-SOCKET */
Object gsi_interface_current_icp_socket(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object icp_socket_qm, gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(218,114);
    icp_socket_qm = get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_icp_socket,Nil);
    if (icp_socket_qm) {
	if (EQ(ISVREF(icp_socket_qm,(SI_Long)5L),gsi_interface_frame)) {
	    gensymed_symbol = ISVREF(gsi_interface_frame,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(gsi_interface_frame) ? 
		    EQ(ISVREF(gsi_interface_frame,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(icp_socket_qm,(SI_Long)6L);
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
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	icp_socket_qm = Nil;
	set_slot_value_function(gsi_interface_frame,
		Qgsi_interface_icp_socket,Nil,Nil);
    }
    return VALUES_1(icp_socket_qm);
}

static Object Qgsi_interface_activate_after_shutdown;  /* gsi-interface-activate-after-shutdown */

static Object Qgsi_connection_configuration;  /* gsi-connection-configuration */

static Object Qinterface_initialization_timeout_period;  /* interface-initialization-timeout-period */

static Object Qgsi;                /* gsi */

static Object string_constant_57;  /* "Cannot make ICP connection for GSI data interface ~NF" */

static Object Qdisable_interleaving_of_large_messages;  /* disable-interleaving-of-large-messages */

static Object Qrequested;          /* requested */

/* ACTIVATE-GSI-INTERFACE */
Object activate_gsi_interface(gsi_interface_frame,already_initialized_p)
    Object gsi_interface_frame, already_initialized_p;
{
    Object icp_socket_qm, temp, interface_configuration_qm, application_name;
    Object var, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(218,115);
    icp_socket_qm = gsi_interface_current_icp_socket(gsi_interface_frame);
    if (icp_socket_qm && icp_connection_being_shutdown_qm(icp_socket_qm)) {
	set_slot_value_function(gsi_interface_frame,
		Qgsi_interface_activate_after_shutdown,T,Nil);
	return VALUES_1(Nil);
    }
    if ( !TRUEP(icp_socket_qm)) {
	temp = get_slot_value_if_any_function(gsi_interface_frame,
		Qgsi_connection_configuration,Nil);
	interface_configuration_qm = CAR(temp);
	application_name = 
		get_slot_value_if_any_function(gsi_interface_frame,
		Qgsi_application_name,Nil);
	if ( !TRUEP(interface_configuration_qm))
	    change_gsi_interface_status(gsi_interface_frame,
		    Gsi_interface_initializing);
	else {
	    var = get_slot_value_if_any_function(gsi_interface_frame,
		    Qinterface_initialization_timeout_period,Nil);
	    if (NUMBERP(var))
		temp = var;
	    else if ( !TRUEP(var))
		temp = Qnone;
	    else
		temp = Nil;
	    if (temp);
	    else {
		var = get_slot_value_if_any_function(gsi_interface_frame,
			Qinterface_timeout_period,Nil);
		temp = NUMBERP(var) ? var : Nil;
	    }
	    if (temp);
	    else
		temp = Default_gsi_interface_countdown_timer_limit;
	    icp_socket_qm = make_icp_connection(4,
		    interface_configuration_qm,Qgsi,application_name,temp);
	    if ( !TRUEP(icp_socket_qm)) {
		change_gsi_interface_status(gsi_interface_frame,
			Gsi_interface_icp_connection_dead);
		if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
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
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(2,string_constant_57,
					  gsi_interface_frame);
				  temp = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			notify_user_1(temp);
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
    if (icp_socket_qm) {
	if (get_slot_value_if_any_function(gsi_interface_frame,
		Qdisable_interleaving_of_large_messages,Nil))
	    SVREF(icp_socket_qm,FIX((SI_Long)53L)) = Qrequested;
	SVREF(icp_socket_qm,FIX((SI_Long)17L)) = Nil;
	return activate_gsi_interface_with_socket(gsi_interface_frame,
		icp_socket_qm,already_initialized_p);
    }
    else
	return VALUES_1(Nil);
}

static Object Qhandle_gsi_connect_attempt_failure;  /* handle-gsi-connect-attempt-failure */

static Object Qgsi_sensor_groups_header;  /* gsi-sensor-groups-header */

static Object Qgsi_interface_structure;  /* gsi-interface-structure */

static Object Qfinalize_gsi_connection_1;  /* finalize-gsi-connection-1 */

/* ACTIVATE-GSI-INTERFACE-WITH-SOCKET */
Object activate_gsi_interface_with_socket(gsi_interface_frame,icp_socket,
	    already_initialized_p)
    Object gsi_interface_frame, icp_socket, already_initialized_p;
{
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value, var;
    Object gsi_interface_countdown_timer_limit, temp, interface_struct;
    char svref_new_value_1;

    x_note_fn_call(218,116);
    register_icp_connection_loss_callback(Qhandle_gsi_connect_attempt_failure,
	    icp_socket);
    SVREF(icp_socket,FIX((SI_Long)25L)) = Qgsi;
    SVREF(icp_socket,FIX((SI_Long)5L)) = gsi_interface_frame;
    frame_serial_number_setf_arg = ISVREF(gsi_interface_frame,(SI_Long)3L);
    old = ISVREF(icp_socket,(SI_Long)6L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(icp_socket,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value_1 = (SI_Long)0L != (IFIX(ISVREF(gsi_interface_frame,
	    (SI_Long)4L)) & (SI_Long)16777216L);
    SVREF(icp_socket,FIX((SI_Long)48L)) = svref_new_value_1 ? T : Nil;
    change_gsi_interface_status(gsi_interface_frame,
	    Gsi_interface_waiting_for_response);
    set_slot_value_function(gsi_interface_frame,Qgsi_sensor_groups_header,
	    make_sensor_groups_header_1(),Nil);
    var = get_slot_value_if_any_function(gsi_interface_frame,
	    Qinterface_timeout_period,Nil);
    gsi_interface_countdown_timer_limit = NUMBERP(var) ? var : Nil;
    if (gsi_interface_countdown_timer_limit);
    else
	gsi_interface_countdown_timer_limit = 
		Default_gsi_interface_countdown_timer_limit;
    temp = copy_frame_serial_number(ISVREF(gsi_interface_frame,(SI_Long)3L));
    interface_struct = make_gsi_icp_interface_1(gsi_interface_frame,temp,
	    fixnum_time_interval(FIX((SI_Long)1000L * 
	    IFIX(gsi_interface_countdown_timer_limit))),
	    fixnum_time_interval(FIX((SI_Long)1000L * 
	    IFIX(gsi_interface_countdown_timer_limit))));
    set_slot_value_function(gsi_interface_frame,Qgsi_interface_structure,
	    interface_struct,Nil);
    SVREF(interface_struct,FIX((SI_Long)5L)) = T;
    set_slot_value_function(gsi_interface_frame,Qgsi_interface_icp_socket,
	    icp_socket,Nil);
    svref_new_value = get_slot_value_if_any_function(gsi_interface_frame,
	    Qdisable_interleaving_of_large_messages,Nil);
    SVREF(icp_socket,FIX((SI_Long)53L)) = svref_new_value;
    if (EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_running))
	return finalize_gsi_connection(icp_socket,already_initialized_p);
    else
	return setup_network_connection_for_connect(2,icp_socket,
		Qfinalize_gsi_connection_1);
}

/* FINALIZE-GSI-CONNECTION-1 */
Object finalize_gsi_connection_1(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(218,117);
    finalize_gsi_connection(icp_socket,Nil);
    return VALUES_1(Nil);
}

static Object Qhandle_gsi_shut_down_connection;  /* handle-gsi-shut-down-connection */

/* FINALIZE-GSI-CONNECTION */
Object finalize_gsi_connection(icp_socket,already_initialized_p)
    Object icp_socket, already_initialized_p;
{
    Object gsi_interface_frame;

    x_note_fn_call(218,118);
    gsi_interface_frame = ISVREF(icp_socket,(SI_Long)5L);
    List_of_all_gsi_interfaces = gsi_cons_1(gsi_interface_frame,
	    List_of_all_gsi_interfaces);
    icp_socket = get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_icp_socket,Nil);
    deregister_all_icp_connection_loss_callbacks(icp_socket);
    register_icp_connection_loss_callback(Qhandle_gsi_shut_down_connection,
	    icp_socket);
    if ( !TRUEP(already_initialized_p))
	write_message_group_upon_gsi_interface_activation(icp_socket,
		get_slot_value_if_any_function(gsi_interface_frame,
		Qremote_process_initialization_string,Nil),
		get_slot_value_if_any_function(gsi_interface_frame,
		Qgsi_interface_structure,Nil));
    return VALUES_1(Nil);
}

/* REMOVE-PENDING-REQUESTS-FROM-GSI-INTERFACE */
Object remove_pending_requests_from_gsi_interface(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object sensor_groups_header_qm, sensor_group_qm, first_1, last_1, next;
    Object gensymed_symbol, sensor_cons_qm, group_parameters_qm;
    Object evaluation_value, ab_loop_list_;

    x_note_fn_call(218,119);
    sensor_groups_header_qm = 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_sensor_groups_header,Nil);
    sensor_group_qm = Nil;
  next_loop:
    if (sensor_groups_header_qm) {
      next_loop_1:
	first_1 = ISVREF(sensor_groups_header_qm,(SI_Long)1L);
	last_1 = ISVREF(sensor_groups_header_qm,(SI_Long)2L);
	next = CDR(first_1);
	if ( !TRUEP(first_1)) {
	    sensor_group_qm = Nil;
	    goto end_1;
	}
	else if (EQ(first_1,ISVREF(sensor_groups_header_qm,(SI_Long)1L))) {
	    if (EQ(first_1,last_1))
		CAS_SVREF(sensor_groups_header_qm,(SI_Long)2L,last_1,next);
	    else {
		gensymed_symbol = CAR(first_1);
		if (CAS_SVREF(sensor_groups_header_qm,(SI_Long)1L,first_1,
			next)) {
		    reclaim_gsi_cons_1(first_1);
		    sensor_group_qm = gensymed_symbol;
		    goto end_1;
		}
	    }
	}
	goto next_loop_1;
      end_loop:
	sensor_group_qm = Qnil;
      end_1:;
    }
    else
	sensor_group_qm = Nil;
    if ( !TRUEP(sensor_group_qm))
	goto end_loop_1;
    sensor_cons_qm = Nil;
  next_loop_2:
  next_loop_3:
    first_1 = ISVREF(sensor_group_qm,(SI_Long)4L);
    last_1 = ISVREF(sensor_group_qm,(SI_Long)5L);
    next = CDR(first_1);
    if ( !TRUEP(first_1)) {
	sensor_cons_qm = Nil;
	goto end_2;
    }
    else if (EQ(first_1,ISVREF(sensor_group_qm,(SI_Long)4L))) {
	if (EQ(first_1,last_1))
	    CAS_SVREF(sensor_group_qm,(SI_Long)5L,last_1,next);
	else {
	    gensymed_symbol = CAR(first_1);
	    if (CAS_SVREF(sensor_group_qm,(SI_Long)4L,first_1,next)) {
		reclaim_gsi_cons_1(first_1);
		sensor_cons_qm = gensymed_symbol;
		goto end_2;
	    }
	}
    }
    goto next_loop_3;
  end_loop_2:
    sensor_cons_qm = Qnil;
  end_2:
    if ( !TRUEP(sensor_cons_qm))
	goto end_loop_3;
    reclaim_gsi_cons_1(sensor_cons_qm);
    goto next_loop_2;
  end_loop_3:;
    group_parameters_qm = ISVREF(sensor_group_qm,(SI_Long)1L);
    evaluation_value = Nil;
    ab_loop_list_ = group_parameters_qm;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    evaluation_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(FIXNUMP(evaluation_value) || SYMBOLP(evaluation_value) || 
	    SIMPLE_VECTOR_P(evaluation_value)))
	reclaim_if_evaluation_value_1(evaluation_value);
    goto next_loop_4;
  end_loop_4:
    SVREF(sensor_group_qm,FIX((SI_Long)1L)) = Nil;
    if (group_parameters_qm)
	reclaim_gsi_list_1(group_parameters_qm);
    reclaim_sensor_group_1(sensor_group_qm);
    goto next_loop;
  end_loop_1:
    set_slot_value_function(gsi_interface_frame,Qgsi_sensor_groups_header,
	    Nil,Nil);
    if (sensor_groups_header_qm)
	reclaim_sensor_groups_header_1(sensor_groups_header_qm);
    return VALUES_1(Nil);
}

static Object Qinterface_warning_message_level;  /* interface-warning-message-level */

static Object string_constant_58;  /* "GSI connection attempt failed for interface ~NF, error was ~a." */

static Object string_constant_59;  /* "GSI connection attempt failed for interface ~NF." */

/* HANDLE-GSI-CONNECT-ATTEMPT-FAILURE */
Object handle_gsi_connect_attempt_failure(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object gsi_interface_frame_qm, gensymed_symbol, x, y, xa, ya;
    Object reason_for_shutdown_qm, interface_warning_message_level;
    Object warning_message_level, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(8);

    x_note_fn_call(218,120);
    gsi_interface_frame_qm = ISVREF(icp_socket,(SI_Long)5L);
    if (framep_function(gsi_interface_frame_qm)) {
	gensymed_symbol = ISVREF(gsi_interface_frame_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(gsi_interface_frame_qm) ? 
		EQ(ISVREF(gsi_interface_frame_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icp_socket,(SI_Long)6L);
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
	reason_for_shutdown_qm = ISVREF(icp_socket,(SI_Long)9L);
	change_gsi_interface_status(gsi_interface_frame_qm,
		Gsi_interface_icp_connection_dead);
	disconnect_socket_from_gsi_interface(gsi_interface_frame_qm);
	if (reason_for_shutdown_qm) {
	    interface_warning_message_level = 
		    get_lookup_slot_value(gsi_interface_frame_qm,
		    Qinterface_warning_message_level);
	    warning_message_level = EQ(Qwarning_message_level,
		    interface_warning_message_level) ? 
		    Warning_message_level : interface_warning_message_level;
	    PUSH_SPECIAL_WITH_SYMBOL(Warning_message_level,Qwarning_message_level,warning_message_level,
		    7);
	      if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
		      !TRUEP(Debugging_reset)) {
		  if ( !TRUEP(Defer_notifications_qm))
		      break_out_of_debug_messages();
		  snapshots_of_related_blocks = Nil;
		  note_blocks_in_tformat = 
			  SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		  PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			  6);
		    PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			    5);
		      current_wide_string_list = Qdo_not_use;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			      4);
			wide_string_bv16 = 
				allocate_byte_vector_16(FIX((SI_Long)2048L 
				+ (SI_Long)3L));
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
			      current_twriting_output_type = Qwide_string;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				      0);
				tformat(3,string_constant_58,
					gsi_interface_frame_qm,
					reason_for_shutdown_qm);
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
	    POP_SPECIAL();
	}
	else {
	    interface_warning_message_level = 
		    get_lookup_slot_value(gsi_interface_frame_qm,
		    Qinterface_warning_message_level);
	    warning_message_level = EQ(Qwarning_message_level,
		    interface_warning_message_level) ? 
		    Warning_message_level : interface_warning_message_level;
	    PUSH_SPECIAL_WITH_SYMBOL(Warning_message_level,Qwarning_message_level,warning_message_level,
		    7);
	      if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
		      !TRUEP(Debugging_reset)) {
		  if ( !TRUEP(Defer_notifications_qm))
		      break_out_of_debug_messages();
		  snapshots_of_related_blocks = Nil;
		  note_blocks_in_tformat = 
			  SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		  PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			  6);
		    PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			    5);
		      current_wide_string_list = Qdo_not_use;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			      4);
			wide_string_bv16 = 
				allocate_byte_vector_16(FIX((SI_Long)2048L 
				+ (SI_Long)3L));
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
			      current_twriting_output_type = Qwide_string;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				      0);
				tformat(2,string_constant_59,
					gsi_interface_frame_qm);
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
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* DISCONNECT-SOCKET-FROM-GSI-INTERFACE */
Object disconnect_socket_from_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object interface_icp_socket_qm;

    x_note_fn_call(218,121);
    interface_icp_socket_qm = get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil);
    if (interface_icp_socket_qm) {
	SVREF(interface_icp_socket_qm,FIX((SI_Long)5L)) = Nil;
	set_slot_value_function(gsi_interface,Qgsi_interface_icp_socket,
		Nil,Nil);
    }
    return VALUES_1(Nil);
}

/* STOP-PROCESSING-ON-GSI-INTERFACE */
Object stop_processing_on_gsi_interface(gsi_interface_frame)
    Object gsi_interface_frame;
{
    Object next_one_qm, good_ones, ab_loopvar_, ab_loopvar__1, first_1, last_1;
    Object next, gensymed_symbol, good_one, ab_loop_list_;

    x_note_fn_call(218,122);
    next_one_qm = Nil;
    good_ones = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
  next_loop_1:
    first_1 = Gsi_interfaces_to_process_head;
    last_1 = Gsi_interfaces_to_process_tail;
    next = CDR(first_1);
    if ( !TRUEP(first_1)) {
	next_one_qm = Nil;
	goto end_1;
    }
    else if (EQ(first_1,Gsi_interfaces_to_process_head)) {
	if (EQ(first_1,last_1))
	    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,next);
	else {
	    gensymed_symbol = CAR(first_1);
	    if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,first_1,next)) {
		reclaim_gsi_cons_1(first_1);
		next_one_qm = gensymed_symbol;
		goto end_1;
	    }
	}
    }
    goto next_loop_1;
  end_loop:
    next_one_qm = Qnil;
  end_1:
    if ( !TRUEP(next_one_qm))
	goto end_loop_1;
    if ( !EQ(next_one_qm,gsi_interface_frame)) {
	ab_loopvar__1 = gsi_cons_1(next_one_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    good_ones = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop_1:
    good_one = Nil;
    ab_loop_list_ = good_ones;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    good_one = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = good_one;
    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
  next_loop_3:
    first_1 = Gsi_interfaces_to_process_head;
    last_1 = Gsi_interfaces_to_process_tail;
    next = CDR(Gsi_interfaces_to_process_tail);
    if ( !TRUEP(first_1)) {
	if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,first_1,
		gensymed_symbol)) {
	    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,gensymed_symbol);
	    goto end_2;
	}
    }
    else if (EQ(last_1,Gsi_interfaces_to_process_tail)) {
	if ( !TRUEP(next)) {
	    if (CAS_CDR(last_1,next,gensymed_symbol)) {
		CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,
			gensymed_symbol);
		goto end_2;
	    }
	}
	else
	    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,next);
    }
    goto next_loop_3;
  end_loop_3:
  end_2:;
    goto next_loop_2;
  end_loop_2:;
    reclaim_gsi_list_1(good_ones);
    List_of_all_gsi_interfaces = delete_gsi_element_1(gsi_interface_frame,
	    List_of_all_gsi_interfaces);
    disconnect_socket_from_gsi_interface(gsi_interface_frame);
    maybe_stop_collecting_data_for_interface(gsi_interface_frame);
    return remove_pending_requests_from_gsi_interface(gsi_interface_frame);
}

static Object Qeof_awaiting_shutdown_acknowledgement;  /* eof-awaiting-shutdown-acknowledgement */

static Object string_constant_60;  /* "GSI connection lost for interface ~NF, error was ~a." */

/* HANDLE-GSI-SHUT-DOWN-CONNECTION */
Object handle_gsi_shut_down_connection(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object gsi_interface_frame_qm, gensymed_symbol, x, y, xa, ya;
    Object gsi_interface_structure_qm, gsi_interface_countdown_timer_limit;
    Object reason_for_shutdown_qm, interface_warning_message_level;
    Object warning_message_level, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, svref_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(8);

    x_note_fn_call(218,123);
    gsi_interface_frame_qm = ISVREF(icp_socket,(SI_Long)5L);
    if (framep_function(gsi_interface_frame_qm)) {
	gensymed_symbol = ISVREF(gsi_interface_frame_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(gsi_interface_frame_qm) ? 
		EQ(ISVREF(gsi_interface_frame_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icp_socket,(SI_Long)6L);
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
	gsi_interface_structure_qm = 
		get_slot_value_if_any_function(gsi_interface_frame_qm,
		Qgsi_interface_structure,Nil);
	gsi_interface_countdown_timer_limit = 
		get_slot_value_if_any_function(gsi_interface_frame_qm,
		Qinterface_timeout_period,Nil);
	reason_for_shutdown_qm = ISVREF(icp_socket,(SI_Long)9L);
	change_gsi_interface_status(gsi_interface_frame_qm,
		Gsi_interface_icp_connection_dead);
	if (reason_for_shutdown_qm &&  !EQ(reason_for_shutdown_qm,
		Qeof_awaiting_shutdown_acknowledgement)) {
	    interface_warning_message_level = 
		    get_lookup_slot_value(gsi_interface_frame_qm,
		    Qinterface_warning_message_level);
	    warning_message_level = EQ(Qwarning_message_level,
		    interface_warning_message_level) ? 
		    Warning_message_level : interface_warning_message_level;
	    PUSH_SPECIAL_WITH_SYMBOL(Warning_message_level,Qwarning_message_level,warning_message_level,
		    7);
	      if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
		      !TRUEP(Debugging_reset)) {
		  if ( !TRUEP(Defer_notifications_qm))
		      break_out_of_debug_messages();
		  snapshots_of_related_blocks = Nil;
		  note_blocks_in_tformat = 
			  SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		  PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			  6);
		    PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			    5);
		      current_wide_string_list = Qdo_not_use;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			      4);
			wide_string_bv16 = 
				allocate_byte_vector_16(FIX((SI_Long)2048L 
				+ (SI_Long)3L));
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
			      current_twriting_output_type = Qwide_string;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				      0);
				tformat(3,string_constant_60,
					gsi_interface_frame_qm,
					reason_for_shutdown_qm);
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
	    POP_SPECIAL();
	}
	if ( !NUMBERP(gsi_interface_countdown_timer_limit))
	    gsi_interface_countdown_timer_limit = 
		    Default_gsi_interface_countdown_timer_limit;
	if (gsi_interface_structure_qm) {
	    reclaim_icp_object_map_for_gsi_icp_interface(gsi_interface_structure_qm);
	    svref_new_value = Gsi_connection_initializing;
	    SVREF(icp_socket,FIX((SI_Long)28L)) = svref_new_value;
	    reclaim_gsi_icp_interface_1(gsi_interface_structure_qm);
	    set_slot_value_function(gsi_interface_frame_qm,
		    Qgsi_interface_structure,Nil,Nil);
	}
	stop_processing_on_gsi_interface(gsi_interface_frame_qm);
	deregister_all_icp_connection_loss_callbacks(icp_socket);
	if (get_slot_value_if_any_function(gsi_interface_frame_qm,
		Qgsi_interface_activate_after_shutdown,Nil)) {
	    set_slot_value_function(gsi_interface_frame_qm,
		    Qgsi_interface_activate_after_shutdown,Nil,Nil);
	    activate_gsi_interface(gsi_interface_frame_qm,Nil);
	}
	else if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface_frame_qm,
		(SI_Long)4L)) & (SI_Long)1L)) && 
		memq_function(gsi_interface_frame_qm,
		Remote_gsi_interface_list)) {
	    Remote_gsi_interface_list = 
		    delete_icp_element_1(gsi_interface_frame_qm,
		    Remote_gsi_interface_list);
	    delete_frame(gsi_interface_frame_qm);
	}
    }
    return VALUES_1(Nil);
}

static Object Qdeactivated_while_attempting_connection;  /* deactivated-while-attempting-connection */

/* BODY-OF-DEACTIVATE-FOR-GSI-INTERFACE */
Object body_of_deactivate_for_gsi_interface(gsi_interface,deactivatep)
    Object gsi_interface, deactivatep;
{
    Object interface_icp_socket_qm, attributes_which_identify_a_sensor_qm;
    Object gsi_interface_structure_qm;

    x_note_fn_call(218,124);
    interface_icp_socket_qm = get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil);
    attributes_which_identify_a_sensor_qm = 
	    get_slot_value_if_any_function(gsi_interface,
	    Qidentifying_attributes,Nil);
    if (attributes_which_identify_a_sensor_qm)
	install_true_value_updates_for_gsi(gsi_interface,
		attributes_which_identify_a_sensor_qm,Nil);
    set_slot_value_function(gsi_interface,
	    Qgsi_interface_activate_after_shutdown,Nil,Nil);
    if (interface_icp_socket_qm && Deleting_ui_client_interfaces_for_clear_kb)
	stop_processing_on_gsi_interface(gsi_interface);
    else if (interface_icp_socket_qm && 
	    icp_connection_open_p(interface_icp_socket_qm)) {
	change_gsi_interface_status(gsi_interface,
		Gsi_interface_waiting_for_response);
	flush_and_shutdown_icp_socket(interface_icp_socket_qm);
    }
    else if (interface_icp_socket_qm && 
	    icp_connection_in_progress_p(interface_icp_socket_qm))
	shutdown_icp_socket_connection(2,interface_icp_socket_qm,
		Qdeactivated_while_attempting_connection);
    else {
	stop_processing_on_gsi_interface(gsi_interface);
	gsi_interface_structure_qm = 
		get_slot_value_if_any_function(gsi_interface,
		Qgsi_interface_structure,Nil);
	if (gsi_interface_structure_qm) {
	    reclaim_icp_object_map_for_gsi_icp_interface(gsi_interface_structure_qm);
	    reclaim_gsi_icp_interface_1(gsi_interface_structure_qm);
	    set_slot_value_function(gsi_interface,Qgsi_interface_structure,
		    Nil,Nil);
	}
    }
    return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-GSI-INTERFACE */
Object deactivate_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,125);
    if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)16777216L)))
	body_of_deactivate_for_gsi_interface(gsi_interface,T);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* MANUALLY-DISABLE-FOR-GSI-INTERFACE */
Object manually_disable_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,126);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)47L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
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
    if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	return body_of_deactivate_for_gsi_interface(gsi_interface,T);
    else
	return VALUES_1(Nil);
}

/* NOTE-ANCESTOR-NOT-ACTIVATABLE-FOR-GSI-INTERFACE */
Object note_ancestor_not_activatable_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,127);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)53L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
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
    if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)5L)) & 
	    (SI_Long)1L))) {
	if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
		(SI_Long)16777216L)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) 
		    & (SI_Long)8192L))) {
		if (gsi_icp_socket_connected_p(gsi_interface))
		    return body_of_deactivate_for_gsi_interface(gsi_interface,
			    T);
		else
		    return VALUES_1(Nil);
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

/* ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-GSI-INTERFACE */
Object activate_if_possible_and_propagate_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object old_status, maintaining_gsi_interface_status_changed_p;
    Object gsi_interface_status_changed_p, frame, sub_vector_qm;
    Object method_function_qm, current_computation_frame;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(3);
    Object result;

    x_note_fn_call(218,128);
    if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)5L)) & 
	    (SI_Long)1L))) {
	old_status = get_lookup_slot_value_given_default(gsi_interface,
		Qgsi_interface_status,FIX((SI_Long)0L));
	maintaining_gsi_interface_status_changed_p = T;
	gsi_interface_status_changed_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Gsi_interface_status_changed_p,Qgsi_interface_status_changed_p,gsi_interface_status_changed_p,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Maintaining_gsi_interface_status_changed_p,Qmaintaining_gsi_interface_status_changed_p,maintaining_gsi_interface_status_changed_p,
		  1);
	    frame = gsi_interface;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)11L),(SI_Long)30L);
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) 
		    - (SI_Long)3L;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
		method_function_qm = ISVREF(sub_vector_qm,index_1 + 
			(SI_Long)3L);
		goto end_1;
	    }
	    index_1 = index_1 + (SI_Long)2L;
	    goto next_loop;
	  end_loop:
	    method_function_qm = Qnil;
	  end_1:;
	    if (method_function_qm)
		inline_funcall_1(method_function_qm,frame);
	    if (Gsi_interface_status_changed_p) {
		current_computation_frame = gsi_interface;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			0);
		  result = invoke_rules_for_attribute_change_chaining(gsi_interface,
			  Qgsi_interface_status,old_status,Nil);
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-GSI-INTERFACE */
Object cleanup_for_gsi_interface(gsi_interface)
    Object gsi_interface;
{
    Object interface_icp_socket_qm, icp_socket_transacting_message_group;
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(218,129);
    if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	body_of_deactivate_for_gsi_interface(gsi_interface,T);
    if (memq_function(gsi_interface,Remote_gsi_interface_list))
	Remote_gsi_interface_list = delete_icp_element_1(gsi_interface,
		Remote_gsi_interface_list);
    if ( !(Deleting_ui_client_interfaces_for_clear_kb && (SI_Long)0L != 
	    (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & (SI_Long)16777216L))) {
	interface_icp_socket_qm = 
		get_slot_value_if_any_function(gsi_interface,
		Qgsi_interface_icp_socket,Nil);
	if (interface_icp_socket_qm &&  
		!FIXNUM_EQ(ISVREF(interface_icp_socket_qm,(SI_Long)15L),
		Icp_connection_closed)) {
	    icp_socket_transacting_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_socket_transacting_message_group,Qicp_socket_transacting_message_group,icp_socket_transacting_message_group,
		    0);
	      shutdown_icp_socket_connection(1,interface_icp_socket_qm);
	    POP_SPECIAL();
	}
    }
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* PUT-GSI-CONNECTION-CONFIGURATION */
Object put_gsi_connection_configuration(interface_object,
	    icp_connection_forms,initializing_p)
    Object interface_object, icp_connection_forms, initializing_p;
{
    Object interface_was_connected_p, value, do_not_reclaim_old_value_qm;
    Object result;

    x_note_fn_call(218,130);
    icp_connection_forms = 
	    fix_5_0_beta_icp_connection_forms_if_necessary(interface_object,
	    icp_connection_forms,initializing_p);
    if ( !TRUEP(initializing_p)) {
	interface_was_connected_p = (SI_Long)0L != 
		(IFIX(ISVREF(interface_object,(SI_Long)5L)) & (SI_Long)1L) 
		? T : Nil;
	if (interface_was_connected_p);
	else
	    interface_was_connected_p = 
		    gsi_interface_connects_while_inactive_p(interface_object);
    }
    else
	interface_was_connected_p = Nil;
    if (interface_was_connected_p)
	body_of_deactivate_for_gsi_interface(interface_object,Nil);
    result = put_attribute_value(4,interface_object,
	    Qgsi_connection_configuration,icp_connection_forms,initializing_p);
    MVS_2(result,value,do_not_reclaim_old_value_qm);
    if (interface_was_connected_p)
	activate_gsi_interface(interface_object,Nil);
    return VALUES_2(value,do_not_reclaim_old_value_qm);
}

/* FIX-5-0-BETA-ICP-CONNECTION-FORMS-IF-NECESSARY */
Object fix_5_0_beta_icp_connection_forms_if_necessary(interface_object,
	    icp_connection_forms,initializing_p)
    Object interface_object, icp_connection_forms, initializing_p;
{
    Object temp, temp_2, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object new_icp_connection_forms;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(218,131);
    if (initializing_p && Loading_kb_p && CONSP(icp_connection_forms) && 
	    CAR(icp_connection_forms)) {
	temp = CAR(icp_connection_forms);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = icp_connection_forms;
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
		  write_gsi_host_configuration_from_slot(icp_connection_forms,
			  interface_object);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	new_icp_connection_forms = slot_value_cons_1(temp_2,
		convert_text_string_to_text(temp));
	icp_connection_forms = new_icp_connection_forms;
    }
    return VALUES_1(icp_connection_forms);
}

static Object list_constant_14;    /* # */

static Object Qhandle_update_to_sensor_attribute;  /* handle-update-to-sensor-attribute */

/* INSTALL-TRUE-VALUE-UPDATES-FOR-GSI */
Object install_true_value_updates_for_gsi(gsi_interface,old_attributes,
	    new_attributes)
    Object gsi_interface, old_attributes, new_attributes;
{
    Object designation, attribute, ab_loop_list_;

    x_note_fn_call(218,132);
    designation = gsi_list_3(Qthe,Nil,list_constant_14);
    attribute = Nil;
    ab_loop_list_ = old_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(attribute) ? EQ(CAR(attribute),Qclass_qualified_name) &&  
	    !TRUEP(member_equal(attribute,new_attributes)) :  
	    !TRUEP(memq_function(attribute,new_attributes))) {
	M_SECOND(designation) = attribute;
	install_true_value_update(Qhandle_update_to_sensor_attribute,
		gsi_interface,Nil,designation,Nil);
    }
    goto next_loop;
  end_loop:;
    attribute = Nil;
    ab_loop_list_ = new_attributes;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(attribute) ? EQ(CAR(attribute),Qclass_qualified_name) &&  
	    !TRUEP(member_equal(attribute,old_attributes)) :  
	    !TRUEP(memq_function(attribute,old_attributes))) {
	M_SECOND(designation) = attribute;
	install_true_value_update(Qhandle_update_to_sensor_attribute,
		gsi_interface,Nil,Nil,designation);
    }
    goto next_loop_1;
  end_loop_1:;
    reclaim_gsi_list_1(designation);
    return VALUES_1(Nil);
}

/* PUT-IDENTIFYING-ATTRIBUTES */
Object put_identifying_attributes(interface_object,attributes,initializing_qm)
    Object interface_object, attributes, initializing_qm;
{
    x_note_fn_call(218,133);
    if ((SI_Long)0L != (IFIX(ISVREF(interface_object,(SI_Long)5L)) & 
	    (SI_Long)1L) || (SI_Long)0L != (IFIX(ISVREF(interface_object,
	    (SI_Long)4L)) & (SI_Long)16777216L) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(interface_object,(SI_Long)4L)) & (SI_Long)8192L)))
	install_true_value_updates_for_gsi(interface_object,
		get_slot_value_if_any_function(interface_object,
		Qidentifying_attributes,Nil),attributes);
    return put_attribute_value(4,interface_object,Qidentifying_attributes,
	    attributes,initializing_qm);
}

/* PUT-GROUPING-SPECIFICATION */
Object put_grouping_specification(interface_object,grouping_forms,
	    initializing_qm)
    Object interface_object, grouping_forms, initializing_qm;
{
    x_note_fn_call(218,134);
    return put_attribute_value(4,interface_object,Qgrouping_specification,
	    grouping_forms,initializing_qm);
}

/* PUT-GSI-INTERFACE-STATUS */
Object put_gsi_interface_status(gsi_interface_object,status,initializing_qm)
    Object gsi_interface_object, status, initializing_qm;
{
    Object old_status;

    x_note_fn_call(218,135);
    old_status = get_lookup_slot_value_given_default(gsi_interface_object,
	    Qgsi_interface_status,FIX((SI_Long)0L));
    set_non_savable_lookup_slot_value(gsi_interface_object,
	    Qgsi_interface_status,status);
    invoke_rules_for_attribute_change_chaining(gsi_interface_object,
	    Qgsi_interface_status,old_status,Nil);
    return VALUES_2(status,Nil);
}

/* ACTIVATE-FOR-GSI-DATA-SERVICE */
Object activate_for_gsi_data_service(gsi_data_service)
    Object gsi_data_service;
{
    Object code, sensor_status, x2, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(218,136);
    code = M_CAR(M_CDR(Overflow_byte_count));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)1L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gsi_semantics_graph))) : TRUEP(Nil)) {
	sensor_status = get_slot_value_if_any_function(gsi_data_service,
		Qgsi_variable_status,Nil);
	if (SIMPLE_VECTOR_P(sensor_status) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sensor_status)) > 
		(SI_Long)2L &&  !EQ(ISVREF(sensor_status,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(sensor_status,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    change_slot_value(3,gsi_data_service,Qgsi_variable_status,
		    FIX((SI_Long)0L));
	frame = gsi_data_service;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_data_service)) {
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
	return VALUES_1(gsi_data_service);
    }
    else
	return parse_gsi_schedule_tree();
}

/* DEACTIVATE-DATASERVICE-FOR-GSI-DATA-SERVICE */
Object deactivate_dataservice_for_gsi_data_service(gsi_data_service)
    Object gsi_data_service;
{
    Object sensor_status, gensymed_symbol, structure_being_reclaimed, temp;
    Object svref_arg_2, x2;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(218,137);
    sensor_status = get_slot_value_if_any_function(gsi_data_service,
	    Qgsi_variable_status,Nil);
    clear_pending_gsi_sensor_request(gsi_data_service);
    svref_new_value = IFIX(ISVREF(gsi_data_service,(SI_Long)5L)) &  
	    ~(SI_Long)4096L;
    ISVREF(gsi_data_service,(SI_Long)5L) = FIX(svref_new_value);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(gsi_data_service,(SI_Long)40L);
    if (CAS_SVREF(gsi_data_service,(SI_Long)40L,gensymed_symbol,Nil)) {
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
    gensymed_symbol = ISVREF(gsi_data_service,(SI_Long)30L);
    if (CAS_SVREF(gsi_data_service,(SI_Long)30L,gensymed_symbol,Nil)) {
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
    if (SIMPLE_VECTOR_P(sensor_status) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sensor_status)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(sensor_status,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(sensor_status,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	change_slot_value(3,gsi_data_service,Qgsi_variable_status,
		FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-GSI-DATA-SERVICE */
Object deactivate_for_gsi_data_service(gsi_data_service)
    Object gsi_data_service;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,138);
    frame = gsi_data_service;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_data_service)) {
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
    return deactivate_dataservice_for_gsi_data_service(gsi_data_service);
}

/* ACTIVATE-FOR-GSI-MESSAGE-SERVICE */
Object activate_for_gsi_message_service(gsi_message_service)
    Object gsi_message_service;
{
    Object code, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,139);
    code = M_CAR(M_CDR(Overflow_byte_count));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)1L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gsi_semantics_graph))) : TRUEP(Nil)) {
	frame = gsi_message_service;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_message_service)) {
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
	return VALUES_1(gsi_message_service);
    }
    else
	return parse_gsi_schedule_tree();
}

/* DEACTIVATE-FOR-GSI-MESSAGE-SERVICE */
Object deactivate_for_gsi_message_service(gsi_message_service)
    Object gsi_message_service;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,140);
    frame = gsi_message_service;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_message_service)) {
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
    return VALUES_1(gsi_message_service);
}

/* CLEAR-PENDING-GSI-SENSOR-REQUEST */
Object clear_pending_gsi_sensor_request(sensor)
    Object sensor;
{
    Object gsi_interface_name, gsi_interface_frame, sensor_groups_header;
    Object sensor_group, ab_loop_list_, gsi_sensor_cons, ab_loop_list__1;
    Object gsi_sensor, value_to_set_qm;

    x_note_fn_call(218,141);
    gsi_interface_name = get_slot_value_if_any_function(sensor,
	    Qgsi_interface_name,Nil);
    gsi_interface_frame = gsi_interface_name ? 
	    get_instance_with_name_if_any(Qobject,gsi_interface_name) : Nil;
    if (gsi_interface_frame && (SI_Long)0L != 
	    (IFIX(ISVREF(gsi_interface_frame,(SI_Long)5L)) & (SI_Long)1L) 
	    && (System_is_running || System_has_paused)) {
	sensor_groups_header = 
		get_slot_value_if_any_function(gsi_interface_frame,
		Qgsi_sensor_groups_header,Nil);
	sensor_group = Nil;
	ab_loop_list_ = sensor_groups_header ? ISVREF(sensor_groups_header,
		(SI_Long)1L) : Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sensor_group = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gsi_sensor_cons = Nil;
	ab_loop_list__1 = ISVREF(sensor_group,(SI_Long)4L);
	gsi_sensor = Nil;
	value_to_set_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	gsi_sensor_cons = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	gsi_sensor = CAR(gsi_sensor_cons);
	value_to_set_qm = CDR(gsi_sensor_cons);
	if (EQ(sensor,gsi_sensor)) {
	    M_CAR(gsi_sensor_cons) = Nil;
	    M_CDR(gsi_sensor_cons) = Nil;
	    if (value_to_set_qm)
		reclaim_evaluation_value(value_to_set_qm);
	}
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-GSI-INTERFACE-NAME */
Object put_gsi_interface_name(g2_variable,gsi_interface_name,initializing_qm)
    Object g2_variable, gsi_interface_name, initializing_qm;
{
    Object had_interface_p, already_activated_p, gensymed_symbol;
    Object sub_class_bit_vector, data_collection_interval;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(218,142);
    had_interface_p = get_slot_value_if_any_function(g2_variable,
	    Qgsi_interface_name,Nil);
    already_activated_p = Nil;
    put_attribute_value(4,g2_variable,Qgsi_interface_name,
	    gsi_interface_name,initializing_qm);
    if ((SI_Long)0L != (IFIX(ISVREF(g2_variable,(SI_Long)5L)) & 
	    (SI_Long)1L) && gsi_interface_name) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(g2_variable,(SI_Long)1L),
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
	    data_collection_interval = get_slot_value_function(g2_variable,
		    Qgsi_collection_interval,Nil);
	    if (had_interface_p)
		suspend_activation(g2_variable);
	    resume_activation(g2_variable);
	    already_activated_p = T;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		temp = 
			TRUEP(evaluation_quantity_gt(data_collection_interval,
			FIX((SI_Long)0L)));
	    POP_LOCAL_ALLOCATION(0,0);
	    if (temp)
		gsi_begin_collecting_data(g2_variable,
			data_collection_interval);
	}
	if ( !TRUEP(already_activated_p)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qgsi_message_service,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(g2_variable,
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
	    if (temp) {
		if (had_interface_p)
		    suspend_activation(g2_variable);
		resume_activation(g2_variable);
		return VALUES_2(gsi_interface_name,Nil);
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

/* COMPILE-GSI-INTERFACE-NAME-FOR-SLOT */
Object compile_gsi_interface_name_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(218,143);
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

/* GSI-DELIVER-MESSAGES */
Object gsi_deliver_messages(message_or_copy,urgency_qm,duration_qm,
	    inference_frame,destination)
    Object message_or_copy, urgency_qm, duration_qm, inference_frame;
    Object destination;
{
    Object gsi_interface_name, gsi_interface_frame, interface_icp_socket;
    Object gsi_interface_struct, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
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

    x_note_fn_call(218,144);
    gsi_interface_name = get_slot_value_if_any_function(destination,
	    Qgsi_interface_name,Nil);
    gsi_interface_frame = gsi_interface_name ? 
	    get_instance_with_name_if_any(Qobject,gsi_interface_name) : Nil;
    interface_icp_socket = gsi_interface_frame ? 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    gsi_interface_struct = gsi_interface_frame ? 
	    get_slot_value_if_any_function(gsi_interface_frame,
	    Qgsi_interface_structure,Nil) : Nil;
    if (gsi_interface_frame && interface_icp_socket && ((SI_Long)0L != 
	    (IFIX(ISVREF(gsi_interface_frame,(SI_Long)5L)) & (SI_Long)1L) 
	    || 
	    gsi_interface_connects_while_inactive_p(gsi_interface_frame)) 
	    && icp_connection_open_p(interface_icp_socket) &&  
	    !TRUEP(ISVREF(gsi_interface_struct,(SI_Long)4L))) {
	current_icp_port = ISVREF(interface_icp_socket,(SI_Long)4L);
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
				    send_icp_write_user_message_string(message_or_copy,
					    urgency_qm,duration_qm,Nil);
				    temp = 
					    reclaim_text_string(message_or_copy);
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
    else
	temp = post_on_message_board(5,message_or_copy,urgency_qm,
		duration_qm,inference_frame,destination);
    return VALUES_1(temp);
}

static Object Qpoll_external_system_for_data;  /* poll-external-system-for-data */

static Object string_constant_61;  /* "GSI interface ~NF has timed out." */

/* GSI-PROCESS-GSI-INTERFACES */
Object gsi_process_gsi_interfaces()
{
    Object list_of_all_gsi_interfaces__tail, gsi_interface_frame;
    Object next_list_of_all_gsi_interfaces__tail, icp_socket_qm;
    Object gsi_interface_structure_qm, gsi_interface_countdown_timer_limit_qm;
    Object countdown_timer_value_qm, temp, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object polling_interval, time_of_next_poll, amf_available_array_cons_qm;
    Object amf_array, temp_2, temp_3, amf_result, new_float, second_1, minute;
    Object hour, day, month, year, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_2, index_1, gensymed_symbol_5;
    SI_Long gensymed_symbol, gensymed_symbol_1, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp_1;
    double arg, arg_1, aref_new_value_1, gensymed_symbol_3, gensymed_symbol_4;
    double gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    double gensymed_symbol_9, gensymed_symbol_10;
    Declare_special(24);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(218,145);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	list_of_all_gsi_interfaces__tail = List_of_all_gsi_interfaces;
	gsi_interface_frame = Nil;
	next_list_of_all_gsi_interfaces__tail = Nil;
	icp_socket_qm = Nil;
      next_loop:
	if ( !TRUEP(list_of_all_gsi_interfaces__tail))
	    goto end_loop;
	gsi_interface_frame = CAR(list_of_all_gsi_interfaces__tail);
	next_list_of_all_gsi_interfaces__tail = 
		CDR(list_of_all_gsi_interfaces__tail);
	icp_socket_qm = get_slot_value_if_any_function(gsi_interface_frame,
		Qgsi_interface_icp_socket,Nil);
	if ((SI_Long)0L != (IFIX(ISVREF(gsi_interface_frame,(SI_Long)5L)) 
		& (SI_Long)1L) && 
		get_slot_value_if_any_function(gsi_interface_frame,
		Qpoll_external_system_for_data,Nil) && icp_socket_qm && 
		FIXNUM_EQ(ISVREF(icp_socket_qm,(SI_Long)15L),
		Icp_connection_running)) {
	    gsi_interface_structure_qm = 
		    get_slot_value_if_any_function(gsi_interface_frame,
		    Qgsi_interface_structure,Nil);
	    gsi_interface_countdown_timer_limit_qm = 
		    get_slot_value_if_any_function(gsi_interface_frame,
		    Qinterface_timeout_period,Nil);
	    countdown_timer_value_qm = gsi_interface_structure_qm ? 
		    ISVREF(gsi_interface_structure_qm,(SI_Long)3L) : Qnil;
	    if ( !NUMBERP(gsi_interface_countdown_timer_limit_qm))
		gsi_interface_countdown_timer_limit_qm = 
			Default_gsi_interface_countdown_timer_limit;
	    if (gsi_interface_structure_qm && 
		    ISVREF(gsi_interface_structure_qm,(SI_Long)5L) && 
		    countdown_timer_value_qm) {
		gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
		gensymed_symbol_1 = IFIX(countdown_timer_value_qm);
		if (gensymed_symbol >= gensymed_symbol_1)
		    temp = FIX(gensymed_symbol - gensymed_symbol_1);
		else {
		    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		    gensymed_symbol = gensymed_symbol + 
			    IFIX(Most_positive_fixnum);
		    temp = FIX(gensymed_symbol + (SI_Long)1L);
		}
		temp_1 = FIXNUM_GT(temp,
			fixnum_time_interval(FIX((SI_Long)1000L * 
			IFIX(gsi_interface_countdown_timer_limit_qm))));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		change_gsi_interface_status(gsi_interface_frame,
			Gsi_interface_assumed_dead);
		if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
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
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(2,string_constant_61,
					  gsi_interface_frame);
				  temp = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			notify_user_1(temp);
			if (Snapshots_of_related_blocks) {
			    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			    Snapshots_of_related_blocks = Nil;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		SVREF(gsi_interface_structure_qm,FIX((SI_Long)5L)) = Nil;
		SVREF(gsi_interface_structure_qm,FIX((SI_Long)4L)) = T;
	    }
	    else if (gsi_interface_structure_qm &&  
		    !TRUEP(ISVREF(gsi_interface_structure_qm,(SI_Long)5L)) 
		    &&  !TRUEP(ISVREF(gsi_interface_structure_qm,
			(SI_Long)4L))) {
		polling_interval = 
			get_lookup_slot_value(gsi_interface_frame,
			Qinterval_to_poll_external_system);
		time_of_next_poll = 
			get_lookup_slot_value_given_default(gsi_interface_frame,
			Qtime_of_next_poll,Nil);
		temp_1 =  !FIXNUMP(polling_interval);
		if (temp_1);
		else
		    temp_1 =  
			    !(INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_next_poll) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_next_poll)) 
			    == (SI_Long)1L);
		if (temp_1);
		else {
		    arg = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		    arg_1 = DFLOAT_ISAREF_1(time_of_next_poll,(SI_Long)0L);
		    temp_1 = arg >= arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    if (FIXNUMP(polling_interval)) {
			if ( !TRUEP(time_of_next_poll)) {
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
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
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_3 = Current_thread_index;
				    SVREF(temp_2,temp_3) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_3 = Current_thread_index;
				    SVREF(temp_2,temp_3) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_3 = Current_thread_index;
				    SVREF(temp_2,temp_3) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			    time_of_next_poll = new_float;
			    set_non_savable_lookup_slot_value(gsi_interface_frame,
				    Qtime_of_next_poll,time_of_next_poll);
			}
			aref_new_value_1 = DFLOAT_ISAREF_1(Current_g2_time,
				(SI_Long)0L) + (double)IFIX(polling_interval);
			DFLOAT_ISASET_1(time_of_next_poll,(SI_Long)0L,
				aref_new_value_1);
		    }
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			result = get_decoded_real_time();
			MVS_6(result,second_1,minute,hour,day,month,year);
			current_icp_port = ISVREF(icp_socket_qm,(SI_Long)4L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
				23);
			  current_icp_socket = ISVREF(Current_icp_port,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
				  22);
			    temp = IFIX(ISVREF(Current_icp_socket,
				    (SI_Long)22L)) >= (SI_Long)17L ? 
				    ISVREF(Current_icp_socket,
				    (SI_Long)53L) : Nil;
			    if (temp);
			    else
				temp = EQ(ISVREF(Current_icp_socket,
					(SI_Long)25L),Qtelewindows) ? T : Nil;
			    disable_resumability = temp;
			    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
				    21);
			      number_of_icp_bytes_for_message_series = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
				      20);
				icp_buffers_for_message_group = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
					19);
				  icp_buffer_of_start_of_message_series_qm 
					  = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
					  18);
				    icp_byte_position_of_start_of_message_series_qm 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
					    17);
				      number_of_icp_bytes_to_fill_buffer = 
					      FIX((SI_Long)0L);
				      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
					      16);
					current_icp_buffer = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
						15);
					  current_write_icp_byte_position 
						  = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
						  14);
					    number_of_icp_bytes_in_message_group 
						    = FIX((SI_Long)0L);
					    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
						    13);
					      writing_icp_message_group = 
						      FIXNUM_ADD1(Writing_icp_message_group);
					      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
						      12);
						gensymed_symbol_2 = Nil;
						gensymed_symbol_3 = 0.0;
						gensymed_symbol_4 = 0.0;
						if (Profiling_enabled_qm) {
						    gensymed_symbol_2 = T;
						    gensymed_symbol_3 = 
							    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							    (SI_Long)2L),
							    (SI_Long)0L);
						    gensymed_symbol_4 = 
							    g2ext_unix_time_as_float();
						    temp_2 = 
							    ISVREF(Profiling_enabled_qm,
							    (SI_Long)2L);
						    DFLOAT_ISASET_1(temp_2,
							    (SI_Long)0L,
							    gensymed_symbol_4);
						}
						if (icp_connection_open_p(Current_icp_socket) 
							&&  
							!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
							    {
						    temp = 
							    get_icp_object_index_for_gsi_icp_interface(gsi_interface_structure_qm,
							    Current_icp_port);
						    if (temp);
						    else {
							index_1 = 
								FIX((SI_Long)0L);
							current_icp_port = 
								ISVREF(Current_icp_socket,
								(SI_Long)4L);
							PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
								11);
							  current_icp_socket 
								  = 
								  ISVREF(Current_icp_port,
								  (SI_Long)2L);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
								  10);
							    temp = 
								    IFIX(ISVREF(Current_icp_socket,
								    (SI_Long)22L)) 
								    >= 
								    (SI_Long)17L 
								    ? 
								    ISVREF(Current_icp_socket,
								    (SI_Long)53L) 
								    : Nil;
							    if (temp);
							    else
								temp = 
									EQ(ISVREF(Current_icp_socket,
									(SI_Long)25L),
									Qtelewindows) 
									? 
									T : Nil;
							    disable_resumability 
								    = temp;
							    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
								    9);
							      number_of_icp_bytes_for_message_series 
								      = 
								      FIX((SI_Long)0L);
							      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
								      8);
								icp_buffers_for_message_group 
									= Nil;
								PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
									7);
								  icp_buffer_of_start_of_message_series_qm 
									  = 
									  Nil;
								  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
									  6);
								    icp_byte_position_of_start_of_message_series_qm 
									    = 
									    Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
									    5);
								      number_of_icp_bytes_to_fill_buffer 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
									      4);
									current_icp_buffer 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
										3);
									  current_write_icp_byte_position 
										  = 
										  Nil;
									  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
										  2);
									    number_of_icp_bytes_in_message_group 
										    = 
										    FIX((SI_Long)0L);
									    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
										    1);
									      writing_icp_message_group 
										      = 
										      FIXNUM_ADD1(Writing_icp_message_group);
									      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
										      0);
										gensymed_symbol_5 
											= 
											Nil;
										gensymed_symbol_6 
											= 
											0.0;
										gensymed_symbol_7 
											= 
											0.0;
										if (Profiling_enabled_qm) 
											    {
										    gensymed_symbol_5 
											    = 
											    T;
										    gensymed_symbol_6 
											    = 
											    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
											    (SI_Long)2L),
											    (SI_Long)0L);
										    gensymed_symbol_7 
											    = 
											    g2ext_unix_time_as_float();
										    temp_2 
											    = 
											    ISVREF(Profiling_enabled_qm,
											    (SI_Long)2L);
										    DFLOAT_ISASET_1(temp_2,
											    (SI_Long)0L,
											    gensymed_symbol_7);
										}
										if (icp_connection_open_p(Current_icp_socket) 
											&& 
											 
											!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
											    {
										    index_1 
											    = 
											    make_corresponding_icp_gsi_icp_interface(gsi_interface_structure_qm);
										    end_icp_message_group();
										}
										if (Profiling_enabled_qm) 
											    {
										    gensymed_symbol_8 
											    = 
											    g2ext_unix_time_as_float();
										    gensymed_symbol_9 
											    = 
											    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
											    (SI_Long)2L),
											    (SI_Long)0L);
										    gensymed_symbol_10 
											    = 
											    gensymed_symbol_8 
											    - 
											    gensymed_symbol_9;
										    temp_2 
											    = 
											    ISVREF(Profiling_enabled_qm,
											    (SI_Long)6L);
										    aref_new_value_1 
											    = 
											    gensymed_symbol_10 
											    + 
											    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
											    (SI_Long)6L),
											    (SI_Long)0L);
										    DFLOAT_ISASET_1(temp_2,
											    (SI_Long)0L,
											    aref_new_value_1);
										    temp_2 
											    = 
											    ISVREF(Profiling_enabled_qm,
											    (SI_Long)2L);
										    aref_new_value_1 
											    = 
											    gensymed_symbol_5 
											    ?
											     
											    gensymed_symbol_6 
											    + 
											    gensymed_symbol_10 
											    + 
											    (gensymed_symbol_9 
											    - 
											    gensymed_symbol_7) 
											    :
											     
											    gensymed_symbol_8;
										    DFLOAT_ISASET_1(temp_2,
											    (SI_Long)0L,
											    aref_new_value_1);
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
							temp = index_1;
						    }
						    send_icp_send_data_values_if_any(temp,
							    year,month,day,
							    hour,minute,
							    second_1);
						    end_icp_message_group();
						}
						if (Profiling_enabled_qm) {
						    gensymed_symbol_6 = 
							    g2ext_unix_time_as_float();
						    gensymed_symbol_7 = 
							    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							    (SI_Long)2L),
							    (SI_Long)0L);
						    gensymed_symbol_8 = 
							    gensymed_symbol_6 
							    - 
							    gensymed_symbol_7;
						    temp_2 = 
							    ISVREF(Profiling_enabled_qm,
							    (SI_Long)6L);
						    aref_new_value_1 = 
							    gensymed_symbol_8 
							    + 
							    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							    (SI_Long)6L),
							    (SI_Long)0L);
						    DFLOAT_ISASET_1(temp_2,
							    (SI_Long)0L,
							    aref_new_value_1);
						    temp_2 = 
							    ISVREF(Profiling_enabled_qm,
							    (SI_Long)2L);
						    aref_new_value_1 = 
							    gensymed_symbol_2 
							    ? 
							    gensymed_symbol_3 
							    + 
							    gensymed_symbol_8 
							    + 
							    (gensymed_symbol_7 
							    - 
							    gensymed_symbol_4) 
							    : 
							    gensymed_symbol_6;
						    DFLOAT_ISASET_1(temp_2,
							    (SI_Long)0L,
							    aref_new_value_1);
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
		    POP_LOCAL_ALLOCATION(0,0);
		    SVREF(gsi_interface_structure_qm,FIX((SI_Long)5L)) = T;
		    temp_2 = c_native_clock_ticks_or_cache(Nil,Nil);
		    SVREF(gsi_interface_structure_qm,FIX((SI_Long)3L)) = 
			    temp_2;
		}
	    }
	}
	list_of_all_gsi_interfaces__tail = 
		next_list_of_all_gsi_interfaces__tail;
	goto next_loop;
      end_loop:;
	temp = process_requests_for_gsi_interfaces();
    }
    POP_LOCAL_ALLOCATION(1,1);
    return VALUES_1(temp);
}

/* UPDATE-GSI-INTERFACE-COUNTDOWN-TIMER */
Object update_gsi_interface_countdown_timer(icp_socket)
    Object icp_socket;
{
    Object gsi_interface_frame_qm, gensymed_symbol, x, y, xa, ya;
    Object gsi_interface_structure_qm, svref_new_value;
    char temp;

    x_note_fn_call(218,146);
    gsi_interface_frame_qm = ISVREF(icp_socket,(SI_Long)5L);
    if (gsi_interface_frame_qm) {
	gensymed_symbol = ISVREF(gsi_interface_frame_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(gsi_interface_frame_qm) ? 
		EQ(ISVREF(gsi_interface_frame_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icp_socket,(SI_Long)6L);
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
	gsi_interface_structure_qm = 
		get_slot_value_if_any_function(gsi_interface_frame_qm,
		Qgsi_interface_structure,Nil);
	if (gsi_interface_structure_qm && 
		ISVREF(gsi_interface_structure_qm,(SI_Long)3L)) {
	    svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	    return VALUES_1(SVREF(gsi_interface_structure_qm,
		    FIX((SI_Long)3L)) = svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GSI-PAUSE-DATA-SERVER? */
Object gsi_pause_data_server_qm()
{
    Object gsi_interface, ab_loop_list_, icp_socket, interface_structure;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
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

    x_note_fn_call(218,147);
    gsi_interface = Nil;
    ab_loop_list_ = List_of_all_gsi_interfaces;
    icp_socket = Nil;
    interface_structure = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gsi_interface = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    icp_socket = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    interface_structure = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_structure,Nil) : Nil;
    if (gsi_interface && (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
	    (SI_Long)5L)) & (SI_Long)1L) && icp_socket && 
	    icp_connection_open_p(icp_socket)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
				    send_icp_pause_data_server();
				    end_icp_message_group();
				}
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
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* GSI-RESUME-DATA-SERVER? */
Object gsi_resume_data_server_qm()
{
    Object gsi_interface, ab_loop_list_, icp_socket, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
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

    x_note_fn_call(218,148);
    gsi_interface = Nil;
    ab_loop_list_ = List_of_all_gsi_interfaces;
    icp_socket = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gsi_interface = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    icp_socket = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    if (gsi_interface && (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
	    (SI_Long)5L)) & (SI_Long)1L) && icp_socket && 
	    icp_connection_open_p(icp_socket)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
				    send_icp_resume_data_server();
				    end_icp_message_group();
				}
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
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* GSI-START-DATA-SERVER? */
Object gsi_start_data_server_qm()
{
    Object gsi_interface, ab_loop_list_, icp_socket, temp, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(218,149);
    gsi_interface = Nil;
    ab_loop_list_ = List_of_all_gsi_interfaces;
    icp_socket = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gsi_interface = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    icp_socket = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    if (IFIX(ISVREF(icp_socket,(SI_Long)22L)) >= (SI_Long)15L) {
	if (gsi_interface) {
	    temp = ISVREF(gsi_interface,(SI_Long)8L);
	    temp_1 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != 
		    (IFIX(ISVREF(gsi_interface,(SI_Long)5L)) & 
		    (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) && 
		    (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
		    (SI_Long)4L)) & (SI_Long)16777216L) &&  !((SI_Long)0L 
		    != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
		    (SI_Long)8192L)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? TRUEP(icp_socket) : TRUEP(Nil)) ? 
		TRUEP(icp_connection_open_p(icp_socket)) : TRUEP(Nil)) {
	    current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
					send_icp_start_data_server();
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
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* GSI-RESET-DATA-SERVER? */
Object gsi_reset_data_server_qm()
{
    Object gsi_interface, ab_loop_list_, icp_socket, temp, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(218,150);
    gsi_interface = Nil;
    ab_loop_list_ = List_of_all_gsi_interfaces;
    icp_socket = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gsi_interface = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    icp_socket = gsi_interface ? 
	    get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    if (IFIX(ISVREF(icp_socket,(SI_Long)22L)) >= (SI_Long)15L) {
	if (gsi_interface) {
	    temp = ISVREF(gsi_interface,(SI_Long)8L);
	    temp_1 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != 
		    (IFIX(ISVREF(gsi_interface,(SI_Long)5L)) & 
		    (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) && 
		    (SI_Long)0L != (IFIX(ISVREF(gsi_interface,
		    (SI_Long)4L)) & (SI_Long)16777216L) &&  !((SI_Long)0L 
		    != (IFIX(ISVREF(gsi_interface,(SI_Long)4L)) & 
		    (SI_Long)8192L)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? TRUEP(icp_socket) : TRUEP(Nil)) ? 
		TRUEP(icp_connection_open_p(icp_socket)) : TRUEP(Nil)) {
	    current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
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
					send_icp_reset_data_server();
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
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* GSI-SHUT-DOWN-DATA-SERVER? */
Object gsi_shut_down_data_server_qm()
{
    Object new_list, interface_1, ab_loop_list_, interface_qm, first_1, last_1;
    Object next, gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(218,151);
    new_list = Qnil;
    interface_1 = Nil;
    ab_loop_list_ = List_of_all_gsi_interfaces;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    interface_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ((SI_Long)0L != (IFIX(ISVREF(interface_1,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	new_list = gsi_cons_1(interface_1,new_list);
    goto next_loop;
  end_loop:
    reclaim_gsi_list_1(List_of_all_gsi_interfaces);
    List_of_all_gsi_interfaces = new_list;
    interface_qm = Nil;
  next_loop_1:
  next_loop_2:
    first_1 = Gsi_interfaces_to_process_head;
    last_1 = Gsi_interfaces_to_process_tail;
    next = CDR(first_1);
    if ( !TRUEP(first_1)) {
	interface_qm = Nil;
	goto end_1;
    }
    else if (EQ(first_1,Gsi_interfaces_to_process_head)) {
	if (EQ(first_1,last_1))
	    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,next);
	else {
	    gensymed_symbol = CAR(first_1);
	    if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,first_1,next)) {
		reclaim_gsi_cons_1(first_1);
		interface_qm = gensymed_symbol;
		goto end_1;
	    }
	}
    }
    goto next_loop_2;
  end_loop_1:
    interface_qm = Qnil;
  end_1:
    if ( !TRUEP(interface_qm))
	goto end_loop_2;
    goto next_loop_1;
  end_loop_2:;
    process_gsi_sensor_values(Nil);
    gensymed_symbol = Nil;
  next_loop_3:
    gensymed_symbol = Task_to_process_gsi_values;
    if (CAS_SYMBOL(Qtask_to_process_gsi_values,gensymed_symbol,Nil)) {
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
    goto next_loop_3;
  end_loop_3:
  end_2:;
    gensymed_symbol = Nil;
  next_loop_4:
    gensymed_symbol = Task_to_process_gsi_interfaces;
    if (CAS_SYMBOL(Qtask_to_process_gsi_interfaces,gensymed_symbol,Nil)) {
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
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

/* GSI-REQUESTS-ACCEPT-DATA-CALLS-P */
Object gsi_requests_accept_data_calls_p()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, interface_1, ab_loop_it_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,152);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    interface_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qgsi_interface);
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
      interface_1 = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(interface_1,(SI_Long)5L)) 
	      & (SI_Long)1L) ? T : Nil;
      if (ab_loop_it_) {
	  result = VALUES_1(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* GSI-INITIALIZE-DATA-SERVER */
Object gsi_initialize_data_server()
{
    x_note_fn_call(218,153);
    return VALUES_1(Nil);
}

static Object string_constant_62;  /* "Sensor ~NF is not configured for GSI" */

/* GSI-COLLECT-ONE-SHOT-DATA */
Object gsi_collect_one_shot_data(sensor)
    Object sensor;
{
    Object gensymed_symbol, sub_class_bit_vector, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,154);
    SAVE_STACK();
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)19L);
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
	result = enqueue_gsi_request_for_sensor(sensor,No_value_to_set,
		Collect_one_now);
	RESTORE_STACK();
	return result;
    }
    else if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
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
		      tformat(2,string_constant_62,sensor);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp_1));
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

/* GSI-SET-EXTERNAL-VARIABLE */
Object gsi_set_external_variable(sensor,value,data_type)
    Object sensor, value, data_type;
{
    Object gensymed_symbol, sub_class_bit_vector, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,155);
    SAVE_STACK();
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)19L);
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
	result = enqueue_gsi_request_for_sensor(sensor,FIXNUMP(value) || 
		value && SYMBOLP(value) ? value : 
		copy_evaluation_value_1(value),Collect_one_now);
	RESTORE_STACK();
	return result;
    }
    else if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
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
		      tformat(2,string_constant_62,sensor);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp_1));
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

/* GSI-BEGIN-COLLECTING-DATA */
Object gsi_begin_collecting_data(sensor,collection_interval)
    Object sensor, collection_interval;
{
    Object gensymed_symbol, sub_class_bit_vector, old_collection_interval;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(218,156);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)19L);
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
    if ( !temp) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)2L),string_constant_62,sensor);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    if (get_slot_value_if_any_function(sensor,Qgsi_interface_name,Nil))
	enqueue_gsi_request_for_sensor(sensor,No_value_to_set,
		collection_interval);
    old_collection_interval = get_slot_value_function(sensor,
	    Qgsi_collection_interval,Nil);
    if ( !EQL(old_collection_interval,collection_interval)) {
	reclaim_evaluation_quantity(old_collection_interval);
	if (FIXNUMP(collection_interval))
	    temp_1 = collection_interval;
	else if (INLINE_LONG_VECTOR_P(collection_interval) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_interval)) == 
		(SI_Long)1L)
	    temp_1 = copy_managed_long(collection_interval);
	else
	    temp_1 = copy_managed_float(collection_interval);
	set_slot_value_function(sensor,Qgsi_collection_interval,temp_1,Nil);
	if (FIXNUMP(collection_interval))
	    temp_1 = collection_interval;
	else if (INLINE_LONG_VECTOR_P(collection_interval) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_interval)) == 
		(SI_Long)1L)
	    temp_1 = copy_managed_long(collection_interval);
	else
	    temp_1 = copy_managed_float(collection_interval);
	return set_slot_value_function(sensor,
		Qgsi_internal_collection_interval,temp_1,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_63;  /* "The GSI data server could not set a value ~
				    *                        for variable ~NF because ~a does not exist."
				    */

static Object string_constant_64;  /* "The GSI data server could not set a value ~
				    *                        for variable ~NF because no GSI interface was specified."
				    */

static Object string_constant_65;  /* "No GSI interface for sensor ~NF" */

static Object Qenqueue_gsi_request_for_sensor;  /* enqueue-gsi-request-for-sensor */

static Object string_constant_66;  /* "The GSI data server could not set a value for variable ~NF ~
				    *                    because ~NF is not active."
				    */

static Object string_constant_67;  /* "The GSI data server could not set a value for variable ~NF ~
				    *                  because ~NF failed to make an ICP connection."
				    */

static Object string_constant_68;  /* "The GSI data server ~
				    *                      could not set a value for variable ~NF ~
				    *                      because ~NF is not connected."
				    */

static Object string_constant_69;  /* "The GSI data server could not set a value for variable ~NF ~
				    *               because the ICP connection for ~NF has timed out."
				    */

static Object Qprocess_requests_for_gsi_interfaces;  /* process-requests-for-gsi-interfaces */

/* ENQUEUE-GSI-REQUEST-FOR-SENSOR */
Object enqueue_gsi_request_for_sensor(sensor,value_to_set_qm,
	    collection_interval)
    Object sensor, value_to_set_qm, collection_interval;
{
    Object gsi_interface_name_qm, gsi_interface_qm, gensymed_symbol;
    Object sub_class_bit_vector, raw_sensor_grouping_specification;
    Object sensor_grouping_specification, gsi_interface_icp_socket_qm;
    Object gsi_interface_structure, temp_1, expiration_time_of_current_value;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object structure_being_reclaimed, temp_3, svref_arg_2, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value, task;
    Object sensor_groups_header, existing_sensor_groups, gsi_sensor_group;
    Object ab_loop_list_, sensor_put_in_existing_group_qm, first_1, last_1;
    Object next, ctask, p, v, q;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, temp_2, aref_new_value, length_1;
    char temp, svref_new_value_1, g2_p;
    double aref_new_value_1, gensymed_symbol_4, gensymed_symbol_5;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(218,157);
    gsi_interface_name_qm = get_slot_value_if_any_function(sensor,
	    Qgsi_interface_name,Nil);
    gsi_interface_qm = gsi_interface_name_qm ? 
	    get_instance_with_name_if_any(Qobject,gsi_interface_name_qm) : 
	    Qnil;
    if (gsi_interface_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qgsi_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(gsi_interface_qm,
		    (SI_Long)1L),(SI_Long)19L);
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
    raw_sensor_grouping_specification = temp ? 
	    get_slot_value_if_any_function(gsi_interface_qm,
	    Qgrouping_specification,Nil) : Nil;
    sensor_grouping_specification = EQ(Qno_grouping,
	    raw_sensor_grouping_specification) ? Nil : 
	    raw_sensor_grouping_specification;
    gsi_interface_icp_socket_qm = gsi_interface_qm ? 
	    get_slot_value_if_any_function(gsi_interface_qm,
	    Qgsi_interface_icp_socket,Nil) : Qnil;
    gsi_interface_structure = gsi_interface_qm ? 
	    get_slot_value_if_any_function(gsi_interface_qm,
	    Qgsi_interface_structure,Nil) : Qnil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if ( !TRUEP(gsi_interface_qm)) {
	    if (value_to_set_qm) {
		if (gsi_interface_name_qm) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_63,sensor,
				gsi_interface_name_qm);
		    Suppress_warning_message_header_qm = Nil;
		}
		else {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)2L),
				string_constant_64,sensor);
		    Suppress_warning_message_header_qm = Nil;
		}
		temp_1 = reclaim_evaluation_value(value_to_set_qm);
	    }
	    else {
		expiration_time_of_current_value = ISVREF(sensor,(SI_Long)26L);
		if ( !(EQ(expiration_time_of_current_value,Qnever) || 
			FIXNUM_GE(expiration_time_of_current_value,
			Gensym_time)))
		    task_to_detect_failure(sensor);
		if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  temp_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,
				  aref_new_value);
			  temp_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,
				  aref_new_value);
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
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  tformat(2,string_constant_65,sensor);
				  temp_1 = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			temp_1 = notify_user_1(temp_1);
			if (Snapshots_of_related_blocks) {
			    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			    Snapshots_of_related_blocks = Nil;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    temp_1 = Nil;
	    }
	}
	else if ( !((SI_Long)0L != (IFIX(ISVREF(gsi_interface_qm,
		(SI_Long)5L)) & (SI_Long)1L))) {
	    if ( !TRUEP(value_to_set_qm)) {
		expiration_time_of_current_value = ISVREF(sensor,(SI_Long)26L);
		if ( !(EQ(expiration_time_of_current_value,Qnever) || 
			FIXNUM_GE(expiration_time_of_current_value,
			Gensym_time)))
		    task_to_detect_failure(sensor);
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
			  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
				  (SI_Long)9L));
			  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_3 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_3;
			temp_3 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = gensymed_symbol;
		    }
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		if (evaluation_quantity_gt(collection_interval,
			FIX((SI_Long)0L))) {
		    old = Nil;
		    new_1 = Nil;
		  next_loop_1:
		    old = ISVREF(sensor,(SI_Long)40L);
		    def_structure_schedule_task_variable = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    if (def_structure_schedule_task_variable) {
			temp_3 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = 
				ISVREF(def_structure_schedule_task_variable,
				(SI_Long)0L);
			SVREF(temp_3,svref_arg_2) = svref_new_value;
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
		    temp_3 = ISVREF(task,(SI_Long)1L);
		    aref_new_value_1 = DFLOAT_ISAREF_1(Current_g2_time,
			    (SI_Long)0L) + 1.0;
		    DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value_1);
		    temp_3 = ISVREF(task,(SI_Long)1L);
		    aref_new_value_1 = -1.0;
		    DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value_1);
		    svref_new_value_1 =  !TRUEP(Nil);
		    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)2L);
		    SVREF(task,FIX((SI_Long)5L)) = Nil;
		    SVREF(task,FIX((SI_Long)9L)) = Nil;
		    SVREF(task,FIX((SI_Long)10L)) = Nil;
		    SVREF(task,FIX((SI_Long)7L)) = 
			    Qenqueue_gsi_request_for_sensor;
		    temp_3 = SYMBOL_FUNCTION(Qenqueue_gsi_request_for_sensor);
		    SVREF(task,FIX((SI_Long)8L)) = temp_3;
		    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
		    SVREF(task,FIX((SI_Long)13L)) = sensor;
		    SVREF(task,FIX((SI_Long)14L)) = value_to_set_qm;
		    SVREF(task,FIX((SI_Long)15L)) = collection_interval;
		    new_1 = task;
		    if (CAS_SVREF(sensor,(SI_Long)40L,old,new_1)) {
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
			    temp_3 = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    SVREF(old,FIX((SI_Long)0L)) = temp_3;
			    temp_3 = Chain_of_available_schedule_tasks_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_3,svref_arg_2) = old;
			}
			future_task_schedule_2(new_1);
			temp_1 = new_1;
			goto end_2;
		    }
		    else {
			inline_note_reclaim_cons(new_1,Nil);
			structure_being_reclaimed = new_1;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(new_1,
				  (SI_Long)9L));
			  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_3 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
			temp_3 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = new_1;
		    }
		    goto next_loop_1;
		  end_loop_1:
		    temp_1 = Qnil;
		  end_2:;
		}
		else
		    temp_1 = Nil;
	    }
	    else {
		reclaim_evaluation_value(value_to_set_qm);
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)2L),string_constant_66,
			    sensor,gsi_interface_qm);
		Suppress_warning_message_header_qm = Nil;
		temp_1 = Suppress_warning_message_header_qm;
	    }
	}
	else if ( !TRUEP(gsi_interface_icp_socket_qm)) {
	    if (value_to_set_qm) {
		reclaim_evaluation_value(value_to_set_qm);
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)2L),string_constant_67,
			    sensor,gsi_interface_qm);
		Suppress_warning_message_header_qm = Nil;
		temp_1 = Suppress_warning_message_header_qm;
	    }
	    else {
		expiration_time_of_current_value = ISVREF(sensor,(SI_Long)26L);
		temp_1 =  !(EQ(expiration_time_of_current_value,Qnever) || 
			FIXNUM_GE(expiration_time_of_current_value,
			Gensym_time)) ? task_to_detect_failure(sensor) : Nil;
	    }
	}
	else if (FIXNUM_NE(ISVREF(gsi_interface_icp_socket_qm,
		(SI_Long)28L),Gsi_connection_established) || 
		FIXNUM_NE(ISVREF(gsi_interface_icp_socket_qm,(SI_Long)15L),
		Icp_connection_running)) {
	    if (value_to_set_qm) {
		reclaim_evaluation_value(value_to_set_qm);
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)2L),string_constant_68,
			    sensor,gsi_interface_qm);
		Suppress_warning_message_header_qm = Nil;
		temp_1 = Suppress_warning_message_header_qm;
	    }
	    else {
		expiration_time_of_current_value = ISVREF(sensor,(SI_Long)26L);
		temp = EQ(expiration_time_of_current_value,Qnever);
		if (temp);
		else
		    temp = FIXNUM_GE(expiration_time_of_current_value,
			    Gensym_time);
		if (temp);
		else
		    temp = 
			    TRUEP(icp_connection_open_p(gsi_interface_icp_socket_qm));
		if (temp);
		else
		    temp = FIXNUM_EQ(ISVREF(gsi_interface_icp_socket_qm,
			    (SI_Long)15L),
			    Icp_connection_awaiting_acknowledgement);
		temp_1 =  !temp ? task_to_detect_failure(sensor) : Nil;
	    }
	}
	else {
	    temp_1 = (SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) & 
		    (SI_Long)4096L) && 
		    evaluation_quantity_eq(collection_interval,
		    FIX((SI_Long)0L)) ? ( !TRUEP(value_to_set_qm) ? T : 
		    Nil) : Qnil;
	    if (temp_1);
	    else if (value_to_set_qm && ISVREF(gsi_interface_structure,
		    (SI_Long)4L)) {
		reclaim_evaluation_value(value_to_set_qm);
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)2L),string_constant_69,
			    sensor,gsi_interface_qm);
		Suppress_warning_message_header_qm = Nil;
		temp_1 = Suppress_warning_message_header_qm;
	    }
	    else {
		if ((SI_Long)0L != (IFIX(ISVREF(sensor,(SI_Long)5L)) & 
			(SI_Long)32L)) {
		    temp_2 = IFIX(ISVREF(sensor,(SI_Long)5L)) &  
			    ~(SI_Long)4096L;
		    ISVREF(sensor,(SI_Long)5L) = FIX(temp_2);
		    collection_interval = get_slot_value_function(sensor,
			    Qgsi_collection_interval,Nil);
		}
		if (evaluation_quantity_gt(collection_interval,
			FIX((SI_Long)0L)) &&  
			!TRUEP(get_slot_value_if_any_function(gsi_interface_qm,
			Qexternal_system_has_a_scheduler,Nil))) {
		    old = Nil;
		    new_1 = Nil;
		  next_loop_2:
		    old = ISVREF(sensor,(SI_Long)40L);
		    def_structure_schedule_task_variable = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    if (def_structure_schedule_task_variable) {
			temp_3 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = 
				ISVREF(def_structure_schedule_task_variable,
				(SI_Long)0L);
			SVREF(temp_3,svref_arg_2) = svref_new_value;
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
		    temp_3 = ISVREF(task,(SI_Long)1L);
		    gensymed_symbol_4 = DFLOAT_ISAREF_1(Current_g2_time,
			    (SI_Long)0L);
		    gensymed_symbol_5 = FIXNUMP(collection_interval) ? 
			    (double)IFIX(collection_interval) : 
			    DFLOAT_ISAREF_1(collection_interval,(SI_Long)0L);
		    aref_new_value_1 = gensymed_symbol_4 + gensymed_symbol_5;
		    DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value_1);
		    temp_3 = ISVREF(task,(SI_Long)1L);
		    aref_new_value_1 = FIXNUMP(collection_interval) ? 
			    (double)IFIX(collection_interval) : 
			    DFLOAT_ISAREF_1(collection_interval,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value_1);
		    svref_new_value_1 =  !TRUEP(Nil);
		    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
		    SVREF(task,FIX((SI_Long)5L)) = Nil;
		    SVREF(task,FIX((SI_Long)9L)) = Nil;
		    SVREF(task,FIX((SI_Long)10L)) = Nil;
		    SVREF(task,FIX((SI_Long)7L)) = 
			    Qenqueue_gsi_request_for_sensor;
		    temp_3 = SYMBOL_FUNCTION(Qenqueue_gsi_request_for_sensor);
		    SVREF(task,FIX((SI_Long)8L)) = temp_3;
		    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
		    SVREF(task,FIX((SI_Long)13L)) = sensor;
		    SVREF(task,FIX((SI_Long)14L)) = No_value_to_set;
		    SVREF(task,FIX((SI_Long)15L)) = Collect_one_now;
		    new_1 = task;
		    if (CAS_SVREF(sensor,(SI_Long)40L,old,new_1)) {
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
			    temp_3 = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    SVREF(old,FIX((SI_Long)0L)) = temp_3;
			    temp_3 = Chain_of_available_schedule_tasks_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_3,svref_arg_2) = old;
			}
			future_task_schedule_2(new_1);
			goto end_3;
		    }
		    else {
			inline_note_reclaim_cons(new_1,Nil);
			structure_being_reclaimed = new_1;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(new_1,
				  (SI_Long)9L));
			  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_3 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
			temp_3 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = new_1;
		    }
		    goto next_loop_2;
		  end_loop_2:
		  end_3:;
		}
		if (value_to_set_qm ||  !((SI_Long)0L != 
			(IFIX(ISVREF(sensor,(SI_Long)5L)) & 
			(SI_Long)4096L)) &&  !TRUEP(value_to_set_qm) || 
			evaluation_quantity_sl_eq(collection_interval,
			FIX((SI_Long)0L)) && 
			get_slot_value_if_any_function(gsi_interface_qm,
			Qexternal_system_has_a_scheduler,Nil)) {
		    if ( !TRUEP(value_to_set_qm)) {
			temp_2 = IFIX(ISVREF(sensor,(SI_Long)5L)) | 
				(SI_Long)4096L;
			ISVREF(sensor,(SI_Long)5L) = FIX(temp_2);
		    }
		    sensor_groups_header = 
			    get_slot_value_if_any_function(gsi_interface_qm,
			    Qgsi_sensor_groups_header,Nil);
		    existing_sensor_groups = ISVREF(sensor_groups_header,
			    (SI_Long)1L);
		    gsi_sensor_group = Nil;
		    ab_loop_list_ = existing_sensor_groups;
		    sensor_put_in_existing_group_qm = Nil;
		  next_loop_3:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_3;
		    gsi_sensor_group = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    sensor_put_in_existing_group_qm = 
			    add_sensor_to_group_if_it_fits(sensor_grouping_specification,
			    sensor,value_to_set_qm,collection_interval,
			    gsi_sensor_group);
		    if (sensor_put_in_existing_group_qm)
			goto end_loop_3;
		    goto next_loop_3;
		  end_loop_3:
		    if ( !TRUEP(sensor_put_in_existing_group_qm)) {
			if ( !TRUEP(ISVREF(sensor_groups_header,
				    (SI_Long)1L))) {
			    gensymed_symbol = gsi_interface_qm;
			    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
			  next_loop_4:
			    first_1 = Gsi_interfaces_to_process_head;
			    last_1 = Gsi_interfaces_to_process_tail;
			    next = CDR(Gsi_interfaces_to_process_tail);
			    if ( !TRUEP(first_1)) {
				if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,
					first_1,gensymed_symbol)) {
				    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
					    last_1,gensymed_symbol);
				    goto end_4;
				}
			    }
			    else if (EQ(last_1,
					Gsi_interfaces_to_process_tail)) {
				if ( !TRUEP(next)) {
				    if (CAS_CDR(last_1,next,gensymed_symbol)) {
					CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
						last_1,gensymed_symbol);
					goto end_4;
				    }
				}
				else
				    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
					    last_1,next);
			    }
			    goto next_loop_4;
			  end_loop_4:
			  end_4:;
			    if ( !(Task_to_process_gsi_interfaces && 
				    (ISVREF(Task_to_process_gsi_interfaces,
				    (SI_Long)6L) || 
				    EQ(Task_to_process_gsi_interfaces,
				    Current_schedule_task)))) {
				old = Nil;
				new_1 = Nil;
			      next_loop_5:
				old = Task_to_process_gsi_interfaces;
				def_structure_schedule_task_variable = 
					ISVREF(Chain_of_available_schedule_tasks_vector,
					IFIX(Current_thread_index));
				if (def_structure_schedule_task_variable) {
				    temp_3 = 
					    Chain_of_available_schedule_tasks_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = 
					    ISVREF(def_structure_schedule_task_variable,
					    (SI_Long)0L);
				    SVREF(temp_3,svref_arg_2) = 
					    svref_new_value;
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
				temp_3 = ISVREF(task,(SI_Long)1L);
				aref_new_value_1 = -1.0;
				DFLOAT_ISASET_1(temp_3,(SI_Long)1L,
					aref_new_value_1);
				temp_3 = ISVREF(Data_server_parameters,
					(SI_Long)22L);
				SVREF(task,FIX((SI_Long)4L)) = temp_3;
				SVREF(task,FIX((SI_Long)5L)) = Nil;
				SVREF(task,FIX((SI_Long)9L)) = Nil;
				SVREF(task,FIX((SI_Long)10L)) = Nil;
				g2_p =  !TRUEP(Nil);
				SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
				temp_3 = ISVREF(task,(SI_Long)1L);
				aref_new_value_1 = DFLOAT_ISAREF_1(g2_p ? 
					Current_g2_time : 
					Current_real_time,(SI_Long)0L);
				DFLOAT_ISASET_1(temp_3,(SI_Long)0L,
					aref_new_value_1);
				SVREF(task,FIX((SI_Long)7L)) = 
					Qprocess_requests_for_gsi_interfaces;
				temp_3 = 
					SYMBOL_FUNCTION(Qprocess_requests_for_gsi_interfaces);
				SVREF(task,FIX((SI_Long)8L)) = temp_3;
				ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
				new_1 = task;
				if (CAS_SYMBOL(Qtask_to_process_gsi_interfaces,
					old,new_1)) {
				    task = new_1;
				    ctask =  !TRUEP(ISVREF(task,
					    (SI_Long)3L)) ? T : Nil;
				    if (ctask);
				    else
					ctask = System_is_running;
				    p = ISVREF(task,(SI_Long)4L);
				    v = ctask ? Current_task_queue_vector :
					     Deferred_task_queue_vector;
				    q = ISVREF(v,IFIX(p));
				    SVREF(task,FIX((SI_Long)11L)) = q;
				    temp_3 = constant_queue_push_right(q,task);
				    SVREF(task,FIX((SI_Long)6L)) = temp_3;
				    if (ctask && FIXNUM_LT(p,
					    Priority_of_next_task))
					Priority_of_next_task = p;
				    goto end_5;
				}
				else {
				    inline_note_reclaim_cons(new_1,Nil);
				    structure_being_reclaimed = new_1;
				    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
					    0);
				      reclaim_schedule_task_args(ISVREF(new_1,
					      (SI_Long)9L));
				      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
				    POP_SPECIAL();
				    temp_3 = 
					    ISVREF(Chain_of_available_schedule_tasks_vector,
					    IFIX(Current_thread_index));
				    SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
				    temp_3 = 
					    Chain_of_available_schedule_tasks_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_3,svref_arg_2) = new_1;
				}
				goto next_loop_5;
			      end_loop_5:
			      end_5:;
			    }
			}
			put_sensor_in_new_sensor_group(sensor_groups_header,
				sensor_grouping_specification,sensor,
				value_to_set_qm,collection_interval);
		    }
		    temp_1 = Qnil;
		}
		else
		    temp_1 = Nil;
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp_1);
}

/* ADD-SENSOR-TO-GROUP-IF-IT-FITS */
Object add_sensor_to_group_if_it_fits(grouping_specification,sensor,
	    value_to_set_qm,interval_for_collection,sensor_group)
    Object grouping_specification, sensor, value_to_set_qm;
    Object interval_for_collection, sensor_group;
{
    Object parameter_values_match_qm, parameter_name, ab_loop_list_;
    Object group_parameter, ab_loop_list__1, sensor_attribute, temp;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, gsi_sensor, svref_new_value, first_1;
    Object last_1, next;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(218,158);
    if (FIXNUM_LT(ISVREF(sensor_group,(SI_Long)6L),
	    Max_gsi_sensors_in_a_group) && (value_to_set_qm ? 
	    TRUEP(ISVREF(sensor_group,(SI_Long)2L)) :  
	    !TRUEP(ISVREF(sensor_group,(SI_Long)2L))) && 
	    (evaluation_quantity_lt(interval_for_collection,
	    FIX((SI_Long)0L)) ? 
	    TRUEP(evaluation_quantity_lt(ISVREF(sensor_group,(SI_Long)3L),
	    FIX((SI_Long)0L))) : 
	    TRUEP(evaluation_quantity_gt_eq(ISVREF(sensor_group,
	    (SI_Long)3L),FIX((SI_Long)0L))))) {
	parameter_values_match_qm = T;
	parameter_name = Nil;
	ab_loop_list_ = grouping_specification;
	group_parameter = Nil;
	ab_loop_list__1 = ISVREF(sensor_group,(SI_Long)1L);
	sensor_attribute = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	parameter_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	group_parameter = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	sensor_attribute = gsi_item_attribute_value(parameter_name,sensor);
	temp =  !TRUEP(sensor_attribute) ? ( !TRUEP(group_parameter) ? T : 
		Nil) : Qnil;
	if (temp);
	else {
	    gensymed_symbol = group_parameter;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop_1:
		    if (level < ab_loop_bind_)
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_2:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_3:
		    if ( !TRUEP(marked))
			goto end_loop_2;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_3;
		  end_loop_2:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol = sensor_attribute;
		temp_1 = FIXNUMP(gensymed_symbol);
		if (temp_1);
		else
		    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_1);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_1 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_1);
		    else
			temp_1 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_1);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_5:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
		      next_loop_6:
			if ( !TRUEP(marked))
			    goto end_loop_5;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp);
			MVS_2(result,succ,marked);
			goto next_loop_6;
		      end_loop_5:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? evaluation_value_eql(2,group_parameter,
		    sensor_attribute) : Nil;
	}
	parameter_values_match_qm = temp;
	gensymed_symbol = sensor_attribute;
	temp_1 = FIXNUMP(gensymed_symbol);
	if (temp_1);
	else
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		     IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp_1);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp_1 = EQ(gensymed_symbol,Qtruth_value);
	    if (temp_1);
	    else
		temp_1 = EQ(gensymed_symbol,Qiteration_state);
	    if (temp_1);
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
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    reclaim_evaluation_value(sensor_attribute);
	if ( !TRUEP(parameter_values_match_qm))
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (parameter_values_match_qm) {
	    gsi_sensor = get_or_make_gsi_sensor(sensor,
		    interval_for_collection);
	    svref_new_value = FIXNUM_ADD1(ISVREF(sensor_group,(SI_Long)6L));
	    SVREF(sensor_group,FIX((SI_Long)6L)) = svref_new_value;
	    gensymed_symbol = gsi_cons_1(gsi_sensor,value_to_set_qm);
	    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
	  next_loop_10:
	    first_1 = ISVREF(sensor_group,(SI_Long)4L);
	    last_1 = ISVREF(sensor_group,(SI_Long)5L);
	    temp = ISVREF(sensor_group,(SI_Long)5L);
	    next = CDR(temp);
	    if ( !TRUEP(first_1)) {
		if (CAS_SVREF(sensor_group,(SI_Long)4L,first_1,
			gensymed_symbol)) {
		    CAS_SVREF(sensor_group,(SI_Long)5L,last_1,gensymed_symbol);
		    goto end_4;
		}
	    }
	    else if (EQ(last_1,ISVREF(sensor_group,(SI_Long)5L))) {
		if ( !TRUEP(next)) {
		    if (CAS_CDR(last_1,next,gensymed_symbol)) {
			CAS_SVREF(sensor_group,(SI_Long)5L,last_1,
				gensymed_symbol);
			goto end_4;
		    }
		}
		else
		    CAS_SVREF(sensor_group,(SI_Long)5L,last_1,next);
	    }
	    goto next_loop_10;
	  end_loop_10:
	  end_4:;
	    return VALUES_1(parameter_values_match_qm);
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* PUT-SENSOR-IN-NEW-SENSOR-GROUP */
Object put_sensor_in_new_sensor_group(sensor_groups_header,
	    grouping_specification,sensor,value_to_set_qm,
	    interval_for_collection)
    Object sensor_groups_header, grouping_specification, sensor;
    Object value_to_set_qm, interval_for_collection;
{
    Object sensor_attribute_list_head, sensor_attribute_list_tail;
    Object parameter_name, ab_loop_list_, sensor_attribute, gensymed_symbol;
    Object sensor_group_parameters, sensor_group, gsi_sensor, first_1, last_1;
    Object temp, next;

    x_note_fn_call(218,159);
    sensor_attribute_list_head = Nil;
    sensor_attribute_list_tail = Nil;
    parameter_name = Nil;
    ab_loop_list_ = grouping_specification;
    sensor_attribute = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    parameter_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sensor_attribute = gsi_item_attribute_value(parameter_name,sensor);
    gensymed_symbol = sensor_attribute;
    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
    if (sensor_attribute_list_head) {
	if ( !TRUEP(sensor_attribute_list_tail))
	    sensor_attribute_list_tail = last(sensor_attribute_list_head,_);
	M_CDR(sensor_attribute_list_tail) = gensymed_symbol;
    }
    else
	sensor_attribute_list_head = gensymed_symbol;
    sensor_attribute_list_tail = gensymed_symbol;
    goto next_loop;
  end_loop:
    sensor_group_parameters = sensor_attribute_list_head;
    goto end_1;
    sensor_group_parameters = Qnil;
  end_1:;
    sensor_group = make_sensor_group_1(sensor_group_parameters,
	    value_to_set_qm ? T : Nil,interval_for_collection);
    gsi_sensor = get_or_make_gsi_sensor(sensor,interval_for_collection);
    gensymed_symbol = gsi_cons_1(gsi_sensor,value_to_set_qm);
    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
  next_loop_1:
    first_1 = ISVREF(sensor_group,(SI_Long)4L);
    last_1 = ISVREF(sensor_group,(SI_Long)5L);
    temp = ISVREF(sensor_group,(SI_Long)5L);
    next = CDR(temp);
    if ( !TRUEP(first_1)) {
	if (CAS_SVREF(sensor_group,(SI_Long)4L,first_1,gensymed_symbol)) {
	    CAS_SVREF(sensor_group,(SI_Long)5L,last_1,gensymed_symbol);
	    goto end_2;
	}
    }
    else if (EQ(last_1,ISVREF(sensor_group,(SI_Long)5L))) {
	if ( !TRUEP(next)) {
	    if (CAS_CDR(last_1,next,gensymed_symbol)) {
		CAS_SVREF(sensor_group,(SI_Long)5L,last_1,gensymed_symbol);
		goto end_2;
	    }
	}
	else
	    CAS_SVREF(sensor_group,(SI_Long)5L,last_1,next);
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    gensymed_symbol = sensor_group;
    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
  next_loop_2:
    first_1 = ISVREF(sensor_groups_header,(SI_Long)1L);
    last_1 = ISVREF(sensor_groups_header,(SI_Long)2L);
    temp = ISVREF(sensor_groups_header,(SI_Long)2L);
    next = CDR(temp);
    if ( !TRUEP(first_1)) {
	if (CAS_SVREF(sensor_groups_header,(SI_Long)1L,first_1,
		gensymed_symbol)) {
	    CAS_SVREF(sensor_groups_header,(SI_Long)2L,last_1,gensymed_symbol);
	    return VALUES_1(gensymed_symbol);
	}
    }
    else if (EQ(last_1,ISVREF(sensor_groups_header,(SI_Long)2L))) {
	if ( !TRUEP(next)) {
	    if (CAS_CDR(last_1,next,gensymed_symbol)) {
		CAS_SVREF(sensor_groups_header,(SI_Long)2L,last_1,
			gensymed_symbol);
		return VALUES_1(gensymed_symbol);
	    }
	}
	else
	    CAS_SVREF(sensor_groups_header,(SI_Long)2L,last_1,next);
    }
    goto next_loop_2;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* RESET-GSI-COLLECTION-INTERVAL */
Object reset_gsi_collection_interval(gsi_variable)
    Object gsi_variable;
{
    x_note_fn_call(218,160);
    reclaim_evaluation_quantity(get_slot_value_function(gsi_variable,
	    Qgsi_collection_interval,Nil));
    set_slot_value_function(gsi_variable,Qgsi_collection_interval,
	    FIX((SI_Long)0L),Nil);
    return VALUES_1(Nil);
}

static Object string_constant_70;  /* "GSI interface not active for sensor ~NF" */

/* GSI-STOP-COLLECTING-DATA-FROM-KNOWN-INTERFACE */
Object gsi_stop_collecting_data_from_known_interface(sensor,gsi_interface)
    Object sensor, gsi_interface;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, schedule_task_qm, gensymed_symbol;
    Object structure_being_reclaimed, temp_2, svref_arg_2;
    SI_Long bv16_length, temp, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,161);
    SAVE_STACK();
    reset_gsi_collection_interval(sensor);
    if (System_is_running &&  !((SI_Long)0L != (IFIX(ISVREF(gsi_interface,
	    (SI_Long)5L)) & (SI_Long)1L))) {
	if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  temp = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
		  temp = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
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
			  tformat(2,string_constant_70,sensor);
			  temp_1 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		SAVE_VALUES(notify_user_1(temp_1));
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
    else {
	if (get_slot_value_if_any_function(gsi_interface,
		Qexternal_system_has_a_scheduler,Nil))
	    enqueue_gsi_request_for_sensor(sensor,Nil,Cancel_collection);
	else {
	    schedule_task_qm = ISVREF(sensor,(SI_Long)40L);
	    if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) 
		    || EQ(schedule_task_qm,Current_schedule_task))) {
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
			  reclaim_schedule_task_args(ISVREF(gensymed_symbol,
				  (SI_Long)9L));
			  SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_2 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_2;
			temp_2 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = gensymed_symbol;
		    }
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	}
	temp = IFIX(ISVREF(sensor,(SI_Long)5L)) &  ~(SI_Long)4096L;
	RESTORE_STACK();
	return VALUES_1(ISVREF(sensor,(SI_Long)5L) = FIX(temp));
    }
}

/* GSI-STOP-COLLECTING-DATA */
Object gsi_stop_collecting_data(sensor)
    Object sensor;
{
    Object gensymed_symbol, sub_class_bit_vector, gsi_interface_name_qm;
    Object gsi_interface_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(218,162);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgsi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sensor,(SI_Long)1L),(SI_Long)19L);
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
	gsi_interface_name_qm = get_slot_value_if_any_function(sensor,
		Qgsi_interface_name,Nil);
	gsi_interface_qm = get_instance_with_name_if_any(Qobject,
		gsi_interface_name_qm);
	if (gsi_interface_qm)
	    return gsi_stop_collecting_data_from_known_interface(sensor,
		    gsi_interface_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-GSI-VARIABLE-TO-INTERFACE-CONNECTIONS */
Object update_gsi_variable_to_interface_connections(interface_frame,
	    new_interface_name_or_names,old_interface_name_or_names)
    Object interface_frame, new_interface_name_or_names;
    Object old_interface_name_or_names;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, variable, gensymed_symbol;
    Object sub_class_bit_vector, name_of_variable_interface_qm;
    Object connecting_to_old_interface_p, connecting_to_new_interface_p;
    Object old_collection_interval_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(218,163);
    if ((SI_Long)0L != (IFIX(ISVREF(interface_frame,(SI_Long)5L)) & 
	    (SI_Long)1L)) {
	if ( !TRUEP(Nil)) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    variable = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qvariable);
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
	      variable = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(variable,
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
	      if (temp ? (SI_Long)0L != (IFIX(ISVREF(variable,
		      (SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil)) {
		  name_of_variable_interface_qm = 
			  get_slot_value_if_any_function(variable,
			  Qgsi_interface_name,Nil);
		  if (name_of_variable_interface_qm) {
		      connecting_to_old_interface_p = 
			      CONSP(old_interface_name_or_names) ? 
			      memq_function(name_of_variable_interface_qm,
			      old_interface_name_or_names) : 
			      EQ(name_of_variable_interface_qm,
			      old_interface_name_or_names) ? T : Nil;
		      connecting_to_new_interface_p = 
			      CONSP(new_interface_name_or_names) ? 
			      memq_function(name_of_variable_interface_qm,
			      new_interface_name_or_names) : 
			      EQ(name_of_variable_interface_qm,
			      new_interface_name_or_names) ? T : Nil;
		      if (connecting_to_old_interface_p || 
			      connecting_to_new_interface_p) {
			  gsi_stop_collecting_data_from_known_interface(variable,
				  interface_frame);
			  old_collection_interval_qm = ISVREF(variable,
				  (SI_Long)32L);
			  if (old_collection_interval_qm)
			      gsi_begin_collecting_data(variable,
				      old_collection_interval_qm);
		      }
		  }
	      }
	      goto next_loop;
	    end_loop_1:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* NOTE-NAME-CHANGE-FOR-GSI-INTERFACE */
Object note_name_change_for_gsi_interface(gsi_interface,old_names,
	    initializing_p)
    Object gsi_interface, old_names, initializing_p;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(218,164);
    frame = gsi_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)10L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgsi_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_3(method_function_qm,frame,old_names,initializing_p);
    return update_gsi_variable_to_interface_connections(gsi_interface,
	    get_lookup_slot_value_given_default(gsi_interface,
	    Qname_or_names_for_frame,Nil),old_names);
}

/* PROCESS-REQUESTS-FOR-GSI-INTERFACES */
Object process_requests_for_gsi_interfaces()
{
    Object more_processing_not_necessary_qm, count_of_interfaces_to_process;
    Object interface_to_process_qm, interface_icp_socket_qm;
    Object interface_structure_qm, interface_not_timed_out_qm;
    Object icp_socket_open_qm, first_1, last_1, next, gensymed_symbol;
    Object sensor_groups_header, gsi_request_to_send, temp;
    SI_Long count_1;

    x_note_fn_call(218,165);
    more_processing_not_necessary_qm = T;
    count_of_interfaces_to_process = length(Gsi_interfaces_to_process_head);
    count_1 = (SI_Long)1L;
    interface_to_process_qm = Nil;
    interface_icp_socket_qm = Nil;
    interface_structure_qm = Nil;
    interface_not_timed_out_qm = Nil;
    icp_socket_open_qm = Nil;
  next_loop:
  next_loop_1:
    first_1 = Gsi_interfaces_to_process_head;
    last_1 = Gsi_interfaces_to_process_tail;
    next = CDR(first_1);
    if ( !TRUEP(first_1)) {
	interface_to_process_qm = Nil;
	goto end_1;
    }
    else if (EQ(first_1,Gsi_interfaces_to_process_head)) {
	if (EQ(first_1,last_1))
	    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,next);
	else {
	    gensymed_symbol = CAR(first_1);
	    if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,first_1,next)) {
		reclaim_gsi_cons_1(first_1);
		interface_to_process_qm = gensymed_symbol;
		goto end_1;
	    }
	}
    }
    goto next_loop_1;
  end_loop:
    interface_to_process_qm = Qnil;
  end_1:
    interface_icp_socket_qm = interface_to_process_qm ? 
	    get_slot_value_if_any_function(interface_to_process_qm,
	    Qgsi_interface_icp_socket,Nil) : Nil;
    interface_structure_qm = interface_to_process_qm ? 
	    get_slot_value_if_any_function(interface_to_process_qm,
	    Qgsi_interface_structure,Nil) : Nil;
    interface_not_timed_out_qm = interface_structure_qm ? ( 
	    !TRUEP(ISVREF(interface_structure_qm,(SI_Long)4L)) ? T : Nil) :
	     Nil;
    icp_socket_open_qm = interface_icp_socket_qm && 
	    icp_connection_open_p(interface_icp_socket_qm) ? 
	    (FIXNUM_EQ(ISVREF(interface_icp_socket_qm,(SI_Long)28L),
	    Gsi_connection_established) ? T : Nil) : Qnil;
    if (interface_to_process_qm) {
	if (interface_icp_socket_qm && icp_socket_open_qm) {
	    if (interface_not_timed_out_qm && 
		    FIXNUM_EQ(ISVREF(interface_icp_socket_qm,(SI_Long)28L),
		    Gsi_connection_established)) {
		sensor_groups_header = 
			get_slot_value_if_any_function(interface_to_process_qm,
			Qgsi_sensor_groups_header,Nil);
		gsi_request_to_send = Nil;
	      next_loop_2:
	      next_loop_3:
		first_1 = ISVREF(sensor_groups_header,(SI_Long)1L);
		last_1 = ISVREF(sensor_groups_header,(SI_Long)2L);
		next = CDR(first_1);
		if ( !TRUEP(first_1)) {
		    gsi_request_to_send = Nil;
		    goto end_2;
		}
		else if (EQ(first_1,ISVREF(sensor_groups_header,
			    (SI_Long)1L))) {
		    if (EQ(first_1,last_1))
			CAS_SVREF(sensor_groups_header,(SI_Long)2L,last_1,
				next);
		    else {
			gensymed_symbol = CAR(first_1);
			if (CAS_SVREF(sensor_groups_header,(SI_Long)1L,
				first_1,next)) {
			    reclaim_gsi_cons_1(first_1);
			    gsi_request_to_send = gensymed_symbol;
			    goto end_2;
			}
		    }
		}
		goto next_loop_3;
	      end_loop_1:
		gsi_request_to_send = Qnil;
	      end_2:
		if (gsi_request_to_send)
		    send_message_series_for_gsi_request(gsi_request_to_send,
			    interface_to_process_qm);
		if ( !TRUEP(gsi_request_to_send) || time_slice_expired_p())
		    goto end_loop_2;
		goto next_loop_2;
	      end_loop_2:
		if (time_slice_expired_p() && ISVREF(sensor_groups_header,
			(SI_Long)1L)) {
		    more_processing_not_necessary_qm = Nil;
		    gensymed_symbol = interface_to_process_qm;
		    gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
		  next_loop_4:
		    first_1 = Gsi_interfaces_to_process_head;
		    last_1 = Gsi_interfaces_to_process_tail;
		    next = CDR(Gsi_interfaces_to_process_tail);
		    if ( !TRUEP(first_1)) {
			if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,
				first_1,gensymed_symbol)) {
			    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
				    last_1,gensymed_symbol);
			    goto end_3;
			}
		    }
		    else if (EQ(last_1,Gsi_interfaces_to_process_tail)) {
			if ( !TRUEP(next)) {
			    if (CAS_CDR(last_1,next,gensymed_symbol)) {
				CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
					last_1,gensymed_symbol);
				goto end_3;
			    }
			}
			else
			    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
				    last_1,next);
		    }
		    goto next_loop_4;
		  end_loop_3:
		  end_3:;
		}
	    }
	    else {
		gensymed_symbol = interface_to_process_qm;
		gensymed_symbol = gsi_cons_1(gensymed_symbol,Nil);
	      next_loop_5:
		first_1 = Gsi_interfaces_to_process_head;
		last_1 = Gsi_interfaces_to_process_tail;
		next = CDR(Gsi_interfaces_to_process_tail);
		if ( !TRUEP(first_1)) {
		    if (CAS_SYMBOL(Qgsi_interfaces_to_process_head,first_1,
			    gensymed_symbol)) {
			CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,
				gensymed_symbol);
			goto end_4;
		    }
		}
		else if (EQ(last_1,Gsi_interfaces_to_process_tail)) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol)) {
			    CAS_SYMBOL(Qgsi_interfaces_to_process_tail,
				    last_1,gensymed_symbol);
			    goto end_4;
			}
		    }
		    else
			CAS_SYMBOL(Qgsi_interfaces_to_process_tail,last_1,
				next);
		}
		goto next_loop_5;
	      end_loop_4:
	      end_4:;
	    }
	}
    }
    if ( !TRUEP(CAR(Gsi_interfaces_to_process_head)) || time_slice_expired_p())
	goto end_loop_5;
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop_5:
    temp = count_1 < IFIX(count_of_interfaces_to_process) ? Nil : 
	    more_processing_not_necessary_qm;
    goto end_5;
    temp = Qnil;
  end_5:;
    return VALUES_1(temp);
}

static Object string_constant_71;  /* "The value for identifying attribute ~A ~
				    *                       of GSI item ~NF ~
				    *                       is neither a constant value nor a parameter ~
				    *                       and will be ignored."
				    */

/* GSI-ITEM-ATTRIBUTE-VALUE */
Object gsi_item_attribute_value(parameter_name,gsi_item)
    Object parameter_name, gsi_item;
{
    Object gensymed_symbol, old_star_current_computation_frame_star;
    Object name_or_names_qm, parameter_value_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    Object sub_class_bit_vector, old_star_current_computation_frame_star_1;
    Object old_current_computation_flags;
    Object old_star_variables_that_did_not_have_values_star, value;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp, logical_qm;
    Declare_special(7);
    Object result;

    x_note_fn_call(218,166);
    if (ATOM(parameter_name) || EQ(CAR(parameter_name),
		Qclass_qualified_name)) {
	gensymed_symbol = Nil;
	old_star_current_computation_frame_star = Current_computation_frame;
	Current_computation_frame = gsi_item;
	if (EQ(parameter_name,Qnames)) {
	    name_or_names_qm = get_slot_value_if_any_function(gsi_item,
		    Qname_or_names_for_frame,Nil);
	    parameter_value_qm = CONSP(name_or_names_qm) ? 
		    CAR(name_or_names_qm) : name_or_names_qm;
	}
	else if (parameter_name)
	    parameter_value_qm = 
		    serve_unique_item_or_evaluation_value_of_role(parameter_name,
		    gsi_item,Nil,T);
	else
	    parameter_value_qm = Nil;
	if ( !TRUEP(parameter_value_qm))
	    gensymed_symbol = Nil;
	else {
	    gensymed_symbol = parameter_value_qm;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
		if (temp);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
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
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		gensymed_symbol = parameter_value_qm;
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(parameter_value_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		    gensymed_symbol = Nil;
		    old_star_current_computation_frame_star_1 = 
			    Current_computation_frame;
		    old_current_computation_flags = Current_computation_flags;
		    old_star_variables_that_did_not_have_values_star = 
			    Variables_that_did_not_have_values;
		    Current_computation_frame = parameter_value_qm;
		    Variables_that_did_not_have_values = Nil;
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)4L);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)256L);
		    logical_qm = EQ(ISVREF(parameter_value_qm,
			    (SI_Long)20L),Qtruth_value);
		    value = ISVREF(parameter_value_qm,(SI_Long)23L);
		    if (logical_qm) {
			if (FIXNUM_EQ(value,Truth))
			    gensymed_symbol = Evaluation_true_value;
			else if (FIXNUM_EQ(value,Falsity))
			    gensymed_symbol = Evaluation_false_value;
			else
			    gensymed_symbol = eval_cons_1(value,Qtruth_value);
		    }
		    else
			gensymed_symbol = 
				INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
				(SI_Long)0L ? copy_wide_string(value) : 
				FIXNUMP(value) || SYMBOLP(value) ? value : 
				copy_evaluation_value_1(value);
		    Current_computation_frame = 
			    old_star_current_computation_frame_star_1;
		    Current_computation_flags = old_current_computation_flags;
		    Variables_that_did_not_have_values = 
			    old_star_variables_that_did_not_have_values_star;
		}
		else {
		    if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
			    !TRUEP(Debugging_reset)) {
			if ( !TRUEP(Defer_notifications_qm))
			    break_out_of_debug_messages();
			snapshots_of_related_blocks = Nil;
			note_blocks_in_tformat = 
				SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				6);
			  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				  5);
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
				      tformat(3,string_constant_71,
					      parameter_name,gsi_item);
				      temp_2 = copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			    notify_user_1(temp_2);
			    if (Snapshots_of_related_blocks) {
				reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				Snapshots_of_related_blocks = Nil;
			    }
			  POP_SPECIAL();
			POP_SPECIAL();
		    }
		    gensymed_symbol = Nil;
		}
	    }
	}
	Current_computation_frame = old_star_current_computation_frame_star;
	return VALUES_1(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

static Object Qset_values_for_sensors;  /* set-values-for-sensors */

static Object Qget_values_for_sensors;  /* get-values-for-sensors */

static Object Qwrite_user_message_string;  /* write-user-message-string */

static Object Qstop_sending_values_for_sensors;  /* stop-sending-values-for-sensors */

/* SEND-MESSAGE-SERIES-FOR-GSI-REQUEST */
Object send_message_series_for_gsi_request(gsi_request_to_send,gsi_interface)
    Object gsi_request_to_send, gsi_interface;
{
    Object request_type, gsi_icp_socket;
    Object use_new_message_group_for_send_icp_enlarge_index_space_p;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, request_to_specify;
    Object sensor_list_element_cons, sensor_list_element, value_to_set_qm;
    Object first_1, last_1, next, gensymed_symbol_3, parameters_list;
    Object parameter, ab_loop_list_;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    double gensymed_symbol_5, gensymed_symbol_6, aref_new_value;
    Declare_special(13);

    x_note_fn_call(218,167);
    request_type = SIMPLE_VECTOR_P(gsi_request_to_send) && 
	    EQ(ISVREF(gsi_request_to_send,(SI_Long)0L),
	    Qg2_defstruct_structure_name_sensor_group_g2_struct) ? 
	    (ISVREF(gsi_request_to_send,(SI_Long)2L) ? 
	    Qset_values_for_sensors : Qget_values_for_sensors) : 
	    Qwrite_user_message_string;
    gsi_icp_socket = get_slot_value_if_any_function(gsi_interface,
	    Qgsi_interface_icp_socket,Nil);
    use_new_message_group_for_send_icp_enlarge_index_space_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Use_new_message_group_for_send_icp_enlarge_index_space_p,Quse_new_message_group_for_send_icp_enlarge_index_space_p,use_new_message_group_for_send_icp_enlarge_index_space_p,
	    12);
      if (gsi_icp_socket && icp_connection_open_p(gsi_icp_socket) && 
	      FIXNUM_EQ(ISVREF(gsi_icp_socket,(SI_Long)28L),
	      Gsi_connection_established)) {
	  current_icp_port = ISVREF(gsi_icp_socket,(SI_Long)4L);
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
				      DFLOAT_ISASET_1(aref_arg_1,
					      (SI_Long)0L,gensymed_symbol_2);
				  }
				  if (icp_connection_open_p(Current_icp_socket) 
					  &&  
					  !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					      {
				      send_icp_begin_sensor_list();
				      request_to_specify = Nil;
				      sensor_list_element_cons = Nil;
				      sensor_list_element = Nil;
				      value_to_set_qm = Nil;
				    next_loop:
				    next_loop_1:
				      first_1 = ISVREF(gsi_request_to_send,
					      (SI_Long)4L);
				      last_1 = ISVREF(gsi_request_to_send,
					      (SI_Long)5L);
				      next = CDR(first_1);
				      if ( !TRUEP(first_1)) {
					  sensor_list_element_cons = Nil;
					  goto end_1;
				      }
				      else if (EQ(first_1,
					      ISVREF(gsi_request_to_send,
					      (SI_Long)4L))) {
					  if (EQ(first_1,last_1))
					      CAS_SVREF(gsi_request_to_send,
						      (SI_Long)5L,last_1,next);
					  else {
					      gensymed_symbol_3 = CAR(first_1);
					      if (CAS_SVREF(gsi_request_to_send,
						      (SI_Long)4L,first_1,
						      next)) {
						  reclaim_gsi_cons_1(first_1);
						  sensor_list_element_cons 
							  = gensymed_symbol_3;
						  goto end_1;
					      }
					  }
				      }
				      goto next_loop_1;
				    end_loop:
				      sensor_list_element_cons = Qnil;
				    end_1:
				      if ( !TRUEP(sensor_list_element_cons))
					  goto end_loop_1;
				      sensor_list_element = 
					      CAR(sensor_list_element_cons);
				      value_to_set_qm = 
					      CDR(sensor_list_element_cons);
				      if (sensor_list_element && 
					      (SI_Long)0L != 
					      (IFIX(ISVREF(sensor_list_element,
					      (SI_Long)5L)) & (SI_Long)1L)) {
					  request_to_specify = request_type;
					  temp = 
						  register_item_with_socket(sensor_list_element,
						  gsi_icp_socket,T);
					  send_icp_load_sensor_list_element(temp,
						  get_slot_value_if_any_function(sensor_list_element,
						  Qgsi_internal_collection_interval,
						  Nil),value_to_set_qm);
				      }
				      if (value_to_set_qm)
					  reclaim_evaluation_value(value_to_set_qm);
				      reclaim_gsi_cons_1(sensor_list_element_cons);
				      goto next_loop;
				    end_loop_1:
				      parameters_list = 
					      ISVREF(gsi_request_to_send,
					      (SI_Long)1L);
				      parameter = Nil;
				      ab_loop_list_ = parameters_list;
				    next_loop_2:
				      if ( !TRUEP(ab_loop_list_))
					  goto end_loop_2;
				      parameter = M_CAR(ab_loop_list_);
				      ab_loop_list_ = M_CDR(ab_loop_list_);
				      if ( !(FIXNUMP(parameter) || 
					      SYMBOLP(parameter) || 
					      SIMPLE_VECTOR_P(parameter)))
					  reclaim_if_evaluation_value_1(parameter);
				      goto next_loop_2;
				    end_loop_2:
				      SVREF(gsi_request_to_send,
					      FIX((SI_Long)1L)) = Nil;
				      reclaim_gsi_list_1(parameters_list);
				      reclaim_sensor_group_1(gsi_request_to_send);
				      send_icp_end_sensor_list();
				      if (EQ(request_to_specify,
					      Qget_values_for_sensors))
					  send_icp_get_values_for_sensors_in_list();
				      else if (EQ(request_to_specify,
					      Qset_values_for_sensors))
					  send_icp_set_values_for_sensors_in_list();
				      else if (EQ(request_to_specify,
					      Qstop_sending_values_for_sensors))
					  send_icp_stop_sending_values_for_sensors_in_list();
				      temp = Qnil;
				      end_icp_message_group();
				  }
				  else
				      temp = Nil;
				  if (Profiling_enabled_qm) {
				      gensymed_symbol_4 = 
					      g2ext_unix_time_as_float();
				      gensymed_symbol_5 = 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L),(SI_Long)0L);
				      gensymed_symbol_6 = 
					      gensymed_symbol_4 - 
					      gensymed_symbol_5;
				      aref_arg_1 = 
					      ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L);
				      aref_new_value = gensymed_symbol_6 + 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L),(SI_Long)0L);
				      DFLOAT_ISASET_1(aref_arg_1,
					      (SI_Long)0L,aref_new_value);
				      aref_arg_1 = 
					      ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L);
				      aref_new_value = gensymed_symbol ? 
					      gensymed_symbol_1 + 
					      gensymed_symbol_6 + 
					      (gensymed_symbol_5 - 
					      gensymed_symbol_2) : 
					      gensymed_symbol_4;
				      DFLOAT_ISASET_1(aref_arg_1,
					      (SI_Long)0L,aref_new_value);
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
      else
	  temp = Nil;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* GSI-RECEIVE-VALUE-FOR-PING-REQUEST */
Object gsi_receive_value_for_ping_request(gsi_interface_qm,year,month,day,
	    hour,minute,second_1,status)
    Object gsi_interface_qm, year, month, day, hour, minute, second_1, status;
{
    Object invalid_timestamp_qm, temp, gsi_interface_frame;
    Object gsi_interface_socket, temp_1, gensymed_symbol_2;
    Object structure_being_reclaimed, svref_arg_2;
    double sending_timestamp, unix_time, arg, arg_1, gensymed_symbol;
    double gensymed_symbol_1, current_timestamp, time_difference_in_seconds;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(218,168);
    if (gsi_interface_qm) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    invalid_timestamp_qm = IFIX(year) == (SI_Long)0L ? T : Nil;
	    if (invalid_timestamp_qm);
	    else
		invalid_timestamp_qm = IFIX(month) == (SI_Long)0L ? T : Nil;
	    if (invalid_timestamp_qm);
	    else
		invalid_timestamp_qm = IFIX(day) == (SI_Long)0L ? T : Nil;
	    if (invalid_timestamp_qm)
		sending_timestamp = 0.0;
	    else {
		unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),
			IFIX(minute),IFIX(hour),IFIX(day),IFIX(month),
			IFIX(year));
		arg = unix_time;
		arg_1 = -1.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    temp = encode_unix_time_after_failure(second_1,minute,
			    hour,day,month,year);
		    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
		}
		else
		    gensymed_symbol = unix_time;
		gensymed_symbol_1 = (double)((SI_Long)60L * 
			IFIX(Global_daylight_saving_time_adjustment));
		sending_timestamp = gensymed_symbol - gensymed_symbol_1;
	    }
	    current_timestamp = invalid_timestamp_qm ? 0.0 : 
		    g2ext_unix_time_as_float();
	    time_difference_in_seconds = invalid_timestamp_qm ? 0.0 : 
		    current_timestamp - sending_timestamp;
	    gsi_interface_frame = ISVREF(gsi_interface_qm,(SI_Long)1L);
	    SVREF(gsi_interface_qm,FIX((SI_Long)6L)) = 
		    DOUBLE_TO_DOUBLE_FLOAT(time_difference_in_seconds);
	    if (FIXNUM_NE(get_gsi_interface_status(gsi_interface_frame),
		    status)) {
		gsi_interface_socket = 
			get_slot_value_if_any_function(gsi_interface_frame,
			Qgsi_interface_icp_socket,Nil);
		temp_1 = Gsi_connection_established;
		SVREF(gsi_interface_socket,FIX((SI_Long)28L)) = temp_1;
		gensymed_symbol_2 = Nil;
	      next_loop:
		gensymed_symbol_2 = ISVREF(gsi_interface_socket,(SI_Long)16L);
		if (CAS_SVREF(gsi_interface_socket,(SI_Long)16L,
			gensymed_symbol_2,Nil)) {
		    if (gensymed_symbol_2) {
			if (EQ(gensymed_symbol_2,Current_schedule_task))
			    Current_schedule_task = Nil;
			if (ISVREF(gensymed_symbol_2,(SI_Long)6L))
			    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol_2);
			inline_note_reclaim_cons(gensymed_symbol_2,Nil);
			structure_being_reclaimed = gensymed_symbol_2;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(gensymed_symbol_2,
				  (SI_Long)9L));
			  SVREF(gensymed_symbol_2,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_1 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(gensymed_symbol_2,FIX((SI_Long)0L)) = temp_1;
			temp_1 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
		    }
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		change_gsi_interface_status(gsi_interface_frame,status);
		if (FIXNUM_EQ(Gsi_interface_running_ok,status)) {
		    activate_variables_for_gsi_interface(gsi_interface_frame);
		    maybe_begin_collecting_data_for_interface(gsi_interface_frame);
		}
	    }
	    SVREF(gsi_interface_qm,FIX((SI_Long)4L)) = Nil;
	    SVREF(gsi_interface_qm,FIX((SI_Long)5L)) = Nil;
	    result = VALUES_1(SVREF(gsi_interface_qm,FIX((SI_Long)7L)) = 
		    DOUBLE_TO_DOUBLE_FLOAT(current_timestamp));
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

void g2_gsi_INIT()
{
    Object temp, temp_1, reclaim_structure_for_gsi_icp_interface_1, temp_2;
    Object gensymed_symbol, gsi_interface_status_code_evaluation_getter_1;
    Object gsi_application_name_symbol_evaluation_setter_1;
    Object gsi_application_name_symbol_evaluation_getter_1;
    Object gsi_host_configuration_evaluation_setter_1;
    Object gsi_host_configuration_evaluation_getter_1;
    Object process_initialization_string_evaluation_setter_1;
    Object process_initialization_string_evaluation_getter_1;
    Object timeout_interval_or_default_evaluation_setter_1;
    Object timeout_interval_or_default_evaluation_getter_1;
    Object timeout_interval_or_default_or_none_evaluation_setter_1;
    Object timeout_interval_or_default_or_none_evaluation_getter_1;
    Object gsi_variable_status_code_evaluation_getter_1;
    Object gsi_interface_name_evaluation_setter_1;
    Object gsi_interface_name_evaluation_getter_1;
    Object reclaim_structure_for_sensor_group_1;
    Object reclaim_structure_for_sensor_groups_header_1;
    Object AB_package, Qclasses_which_define, Qnote_name_change;
    Object Qnote_name_change_for_gsi_interface, Qgsi_stop_collecting_data;
    Object Qgsi_begin_collecting_data, Qgsi_set_external_variable;
    Object Qgsi_collect_one_shot_data, Qgsi_initialize_data_server;
    Object Qgsi_requests_accept_data_calls_p, Qgsi_shut_down_data_server_qm;
    Object Qgsi_reset_data_server_qm, Qgsi_start_data_server_qm;
    Object Qgsi_resume_data_server_qm, Qgsi_pause_data_server_qm;
    Object Qgsi_process_gsi_interfaces, Qgsi_deliver_messages;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_gsi_interface_name_for_slot;
    Object Qslot_putter, Qput_gsi_interface_name, Qdeactivate;
    Object Qdeactivate_for_gsi_message_service, Qactivate;
    Object Qactivate_for_gsi_message_service, Qdeactivate_for_gsi_data_service;
    Object Qactivate_for_gsi_data_service, list_constant_86, list_constant_85;
    Object list_constant_84, list_constant_83, Qdata_server_map;
    Object Qdata_server_spec, list_constant_82, list_constant_81;
    Object list_constant_80, list_constant_79, Qserver, Qdata;
    Object Qput_gsi_interface_status, Qput_grouping_specification;
    Object Qput_identifying_attributes, list_constant_72, Qany;
    Object Qput_gsi_connection_configuration, Qcleanup;
    Object Qcleanup_for_gsi_interface, Qactivate_if_possible_and_propagate;
    Object Qactivate_if_possible_and_propagate_for_gsi_interface;
    Object Qnote_ancestor_not_activatable;
    Object Qnote_ancestor_not_activatable_for_gsi_interface, Qmanually_disable;
    Object Qmanually_disable_for_gsi_interface, Qdeactivate_for_gsi_interface;
    Object Qnote_ancestor_manually_enabled;
    Object Qnote_ancestor_manually_enabled_for_gsi_interface, Qmanually_enable;
    Object Qmanually_enable_for_gsi_interface, Qactivate_for_gsi_interface;
    Object Qg2_gsi, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qsensor_groups_header;
    Object Qreclaim_structure, Qoutstanding_sensor_groups_header_count;
    Object Qsensor_groups_header_structure_memory_usage, Qutilities2;
    Object string_constant_142, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_141, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qsensor_group;
    Object Qoutstanding_sensor_group_count;
    Object Qsensor_group_structure_memory_usage, string_constant_140;
    Object string_constant_139, Qnote_name_change_for_gsi_data_service;
    Object string_constant_138, Qslot_value_writer;
    Object Qwrite_gsi_interface_name_from_slot, list_constant_78;
    Object list_constant_77, list_constant_76, list_constant_75;
    Object list_constant_74, Qput_data_server_for_messages;
    Object string_constant_137, list_constant_73, string_constant_136;
    Object string_constant_135, string_constant_134, Qitem;
    Object Qput_gsi_variable_status, Qwrite_gsi_host_configuration_from_slot;
    Object Qgsi_host_configuration, list_constant_67;
    Object Qprocess_initialization_string;
    Object Qcompile_process_initialization_string_for_slot;
    Object Qwrite_process_initialization_string_from_slot;
    Object Qput_remote_process_initialization_string, Qslot_value_reclaimer;
    Object Qreclaim_gsi_collection_interval_value, Qnamed;
    Object Qtype_specification_simple_expansion, list_constant_56;
    Object list_constant_53, Qab_or, Qgsi_variable_status_code;
    Object Qwrite_gsi_variable_status_code_from_slot, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object Qwrite_timeout_interval_or_default_or_none_from_slot;
    Object Qtimeout_interval_or_default_or_none;
    Object Qwrite_timeout_interval_or_default_from_slot;
    Object Qtimeout_interval_or_default, list_constant_70, list_constant_71;
    Object list_constant_68, list_constant_69;
    Object Qcompile_timeout_interval_or_default_or_none_for_slot;
    Object Qcompile_timeout_interval_or_default_for_slot, string_constant_123;
    Object Qgsi_interface_p_function, Qcompile_gsi_host_configuration_for_slot;
    Object Qwrite_gsi_variable_grouping_specification_from_slot;
    Object Qgsi_variable_grouping_specification, Qabsent_slot_putter;
    Object Qput_sensor_grouping_specification_where_slot_is_absent;
    Object Qsensor_grouping_specification;
    Object Qcompile_gsi_variable_grouping_specification_for_slot;
    Object string_constant_122, string_constant_121;
    Object Qsimplify_associative_operation;
    Object Qwrite_options_for_item_reference_from_slot;
    Object Qoptions_for_item_reference;
    Object Qcompile_options_for_item_reference_for_slot, string_constant_120;
    Object string_constant_119, string_constant_118, string_constant_117;
    Object string_constant_116, string_constant_115, string_constant_114;
    Object string_constant_113, Qhome;
    Object Qwrite_attributes_which_identify_a_network_item_reference_from_slot;
    Object Qattributes_which_identify_a_network_item_reference;
    Object Qcompile_attributes_which_identify_a_network_item_reference_for_slot;
    Object string_constant_112;
    Object Qput_attributes_which_identify_a_sensor_where_slot_is_absent;
    Object Qattributes_which_identify_a_sensor, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_gsi_interface;
    Object Qg2_set_gsi_interface_interval_to_poll_external_system;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qput_interval_to_poll_external_system;
    Object Qput_gsi_interface_timeout_period_where_slot_is_absent;
    Object Qgsi_interface_timeout_period, list_constant_66, list_constant_65;
    Object list_constant_64, Qab_structure, list_constant_63, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_59;
    Object list_constant_58, list_constant_57, list_constant_55;
    Object list_constant_54, Qno_item;
    Object Qwrite_gsi_application_name_symbol_from_slot;
    Object Qgsi_application_name_symbol;
    Object Qcompile_gsi_application_name_symbol_for_slot, string_constant_111;
    Object Qwrite_interface_warning_message_level_from_slot, list_constant_52;
    Object list_constant_51, list_constant_50, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_36;
    Object list_constant_46, list_constant_29, list_constant_21;
    Object list_constant_45, list_constant_28, list_constant_42;
    Object list_constant_31, list_constant_44, list_constant_43;
    Object list_constant_34, list_constant_41, Qall, list_constant_40;
    Object list_constant_27, list_constant_39, list_constant_26;
    Object list_constant_38, list_constant_37, Qonly, Qserious;
    Object list_constant_35, list_constant_33, list_constant_32;
    Object list_constant_30, list_constant_25, Qcp, Qmessages, Qab_no, Qop;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_20, list_constant_19, Qlevel, Qmessage, Qab_warning;
    Object Qto, Qgsi_interface_status_code;
    Object Qwrite_gsi_interface_status_code_from_slot, string_constant_110;
    Object string_constant_109, string_constant_108, string_constant_107;
    Object string_constant_106, string_constant_105, list_constant_18;
    Object Qremote_item, Qicon_color, Qcreate_icon_description;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, Qentity;
    Object Qput_class_of_remote_interface_where_slot_is_absent;
    Object Qput_names_of_remote_interface_where_slot_is_absent;
    Object Qput_item_reference_options_where_slot_is_absent;
    Object Qput_creation_attributes_where_slot_is_absent, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, list_constant_17, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_83;
    Object Qnote_runs_while_inactive_change;
    Object Qnote_runs_while_inactive_change_for_network_interface;
    Object Qenable_control_of_disable_interleaving_of_large_messages;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object list_constant_16, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, Qreclaim_icp_port_entry_for_gsi_icp_interface;
    Object Qreclaim_gsi_icp_interface_function, Qgsi_icp_interface;
    Object list_constant_15;
    Object Qcorresponding_icp_object_map_for_gsi_icp_interface;
    Object Qoutstanding_gsi_icp_interface_count;
    Object Qgsi_icp_interface_structure_memory_usage, string_constant_73;
    Object string_constant_72, Qoptional_modules, Qab, Qstring_or_symbol_equal;

    x_note_fn_call(218,169);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qoptional_modules = STATIC_SYMBOL("OPTIONAL-MODULES",AB_package);
    Qstring_or_symbol_equal = STATIC_SYMBOL("STRING-OR-SYMBOL-EQUAL",
	    AB_package);
    if ( !TRUEP(member(4,Qgsi,get(Qab,Qoptional_modules,_),Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal)))) {
	temp = get(Qab,Qoptional_modules,Nil);
	temp_1 = CONS(Qgsi,temp);
	set_get(Qab,Qoptional_modules,temp_1);
    }
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct = 
	    STATIC_SYMBOL("GSI-ICP-INTERFACE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgsi_icp_interface = STATIC_SYMBOL("GSI-ICP-INTERFACE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct,
	    Qgsi_icp_interface,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgsi_icp_interface,
	    Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gsi_icp_interface == UNBOUND)
	The_type_description_of_gsi_icp_interface = Nil;
    string_constant_72 = 
	    STATIC_STRING("43Dy8m83iHy1n83iHy8n8k1l8n0000001l1n8y83-48y1o83--sy83--ty83--qy83--rykuk0k0");
    temp = The_type_description_of_gsi_icp_interface;
    The_type_description_of_gsi_icp_interface = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_72));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gsi_icp_interface_g2_struct,
	    The_type_description_of_gsi_icp_interface,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgsi_icp_interface,
	    The_type_description_of_gsi_icp_interface,
	    Qtype_description_of_type);
    Qoutstanding_gsi_icp_interface_count = 
	    STATIC_SYMBOL("OUTSTANDING-GSI-ICP-INTERFACE-COUNT",AB_package);
    Qgsi_icp_interface_structure_memory_usage = 
	    STATIC_SYMBOL("GSI-ICP-INTERFACE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_73 = STATIC_STRING("1q83iHy8s83-XQy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gsi_icp_interface_count);
    push_optimized_constant(Qgsi_icp_interface_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_73));
    Qchain_of_available_gsi_icp_interfaces = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-ICP-INTERFACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gsi_icp_interfaces,
	    Chain_of_available_gsi_icp_interfaces);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gsi_icp_interfaces,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgsi_icp_interface_count = STATIC_SYMBOL("GSI-ICP-INTERFACE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_icp_interface_count,
	    Gsi_icp_interface_count);
    record_system_variable(Qgsi_icp_interface_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gsi_icp_interfaces_vector == UNBOUND)
	Chain_of_available_gsi_icp_interfaces_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgsi_icp_interface_structure_memory_usage,
	    STATIC_FUNCTION(gsi_icp_interface_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gsi_icp_interface_count,
	    STATIC_FUNCTION(outstanding_gsi_icp_interface_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gsi_icp_interface_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gsi_icp_interface,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgsi_icp_interface,
	    reclaim_structure_for_gsi_icp_interface_1);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_gsi_icp_interface = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-GSI-ICP-INTERFACE",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_gsi_icp_interface,
	    STATIC_FUNCTION(establish_new_object_index_for_gsi_icp_interface,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_gsi_icp_interface = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-GSI-ICP-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_gsi_icp_interface,
	    STATIC_FUNCTION(make_corresponding_icp_gsi_icp_interface,NIL,
	    FALSE,1,1));
    Qset_access_form_for_gsi_icp_interface = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-GSI-ICP-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_gsi_icp_interface,
	    STATIC_FUNCTION(set_access_form_for_gsi_icp_interface,NIL,
	    FALSE,2,2));
    Qcorresponding_icp_object_map_for_gsi_icp_interface = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-GSI-ICP-INTERFACE",
	    AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,
	    Qcorresponding_icp_object_map_for_gsi_icp_interface,
	    Qgsi_icp_interface);
    initialize_icp_object_type_compile(Qgsi_icp_interface,
	    Qstandard_icp_object_index_space,list_constant_15);
    Qreclaim_gsi_icp_interface_function = 
	    STATIC_SYMBOL("RECLAIM-GSI-ICP-INTERFACE-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gsi_icp_interface_function,
	    STATIC_FUNCTION(reclaim_gsi_icp_interface_function,NIL,FALSE,1,1));
    Qreclaim_icp_port_entry_for_gsi_icp_interface = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-GSI-ICP-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_gsi_icp_interface,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_gsi_icp_interface,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qgsi_icp_interface,
	    Qreclaim_gsi_icp_interface_function,Qnil,
	    Qreclaim_icp_port_entry_for_gsi_icp_interface);
    Qnetwork_interface = STATIC_SYMBOL("NETWORK-INTERFACE",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_16 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qnetwork_interface,list_constant_16);
    string_constant_74 = STATIC_STRING("1o1l83-8y1l83Iy1m8v8328y1l8t");
    string_constant_75 = 
	    STATIC_STRING("1t4z8r8347y8347y8328y8328y00001o1l8l1l8z1m8p832uy1l83Cy000004z8r8354y8354y8328y8328y00001p1l8l1l8z1l83Ny1m8p832uy1l83Cy000004z8r");
    string_constant_76 = 
	    STATIC_STRING("83DAy83DAy8328y8328y00001p1l8l1l8z1l83Ny1m8p839ay1l83Cy000004z8r83E=y83E=y8328y8328y00001p1l8l1l8z1l83Ny1m8p83-ky1l83Cy000004z8r");
    string_constant_77 = 
	    STATIC_STRING("83BCy83BCy8328y8328y00001p1l8l1l8z1l83Ny1m8p83-2y1l83Cy000004z8r8397y8397y8328y8328y0832Ty001o1l8l1m8p8397y1l8z1l83Cy000004z8r83");
    string_constant_78 = 
	    STATIC_STRING("3ty833ty8328y8328y00001o1l8l1l8z1m8p83Ky1l83Cy000004z8r83D4y83D4y8328y8328y00001p1l83Ey1l8l1l8z1m8p833by1l83Cy000004z8r83D2y83D2");
    string_constant_79 = 
	    STATIC_STRING("y8328y8328y00001p1l83Ey1l8l1l8z1m8p83AEy1l83Cy00000");
    string_constant_80 = 
	    STATIC_STRING("1v8q1q8328y1l83-Oy83-8y83Iy1m8v8328y8t1q8347y01l8l8z1m8p832uy1l83Cy1r8354y01l8l8z83Ny1m8p832uy1l83Cy1r83DAy01l8l8z83Ny1m8p839ay1");
    string_constant_81 = 
	    STATIC_STRING("l83Cy1r83E=y01l8l8z83Ny1m8p83-ky1l83Cy1r83BCy01l8l8z83Ny1m8p83-2y1l83Cy1q8397y832Ty1l8l1m8p8397y8z1l83Cy1q833ty01l8l8z1m8p83Ky1l");
    string_constant_82 = 
	    STATIC_STRING("83Cy1r83D4y01l83Ey1l8l8z1m8p833by1l83Cy1r83D2y01l83Ey1l8l8z1m8p83AEy1l83Cy");
    temp = regenerate_optimized_constant(string_constant_74);
    temp_2 = regenerate_optimized_constant(LIST_5(string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79));
    add_class_to_environment(9,Qnetwork_interface,list_constant_16,Nil,
	    temp,Nil,temp_2,list_constant_16,
	    regenerate_optimized_constant(LIST_3(string_constant_80,
	    string_constant_81,string_constant_82)),Nil);
    Qenable_control_of_disable_interleaving_of_large_messages = 
	    STATIC_SYMBOL("ENABLE-CONTROL-OF-DISABLE-INTERLEAVING-OF-LARGE-MESSAGES",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qenable_control_of_disable_interleaving_of_large_messages,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qdisable_interleaving_of_large_messages = 
	    STATIC_SYMBOL("DISABLE-INTERLEAVING-OF-LARGE-MESSAGES",AB_package);
    list_constant = STATIC_CONS(Qdisable_interleaving_of_large_messages,Qnil);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qdo_not_put_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    SET_SYMBOL_FUNCTION(Qenable_control_of_disable_interleaving_of_large_messages,
	    STATIC_FUNCTION(enable_control_of_disable_interleaving_of_large_messages,
	    NIL,FALSE,0,0));
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qg2_to_g2_data_interface = STATIC_SYMBOL("G2-TO-G2-DATA-INTERFACE",
	    AB_package);
    Qnote_runs_while_inactive_change_for_network_interface = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-NETWORK-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_network_interface,
	    STATIC_FUNCTION(note_runs_while_inactive_change_for_network_interface,
	    NIL,FALSE,1,1));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_network_interface);
    set_get(Qnetwork_interface,Qnote_runs_while_inactive_change,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_runs_while_inactive_change),
	    Qclasses_which_define);
    temp_1 = CONS(Qnetwork_interface,temp);
    mutate_global_property(Qnote_runs_while_inactive_change,temp_1,
	    Qclasses_which_define);
    list_constant_17 = STATIC_CONS(Qnetwork_interface,Qnil);
    check_if_superior_classes_are_defined(Qgsi_interface,list_constant_17);
    string_constant_83 = 
	    STATIC_STRING("1n1m8v83-Oy1o830by8301y8304y8305y1l8t");
    string_constant_84 = 
	    STATIC_STRING("13Cy4z8r83R1y83R1y83=8y83=8y01n02l835jyk+s3-gy3-hy3-gy3-Xykko3A++y001n1l8l1n8p83Cay83Gy1l83Cy000004z8r83C*y83C*y83=8y83=8y00001o");
    string_constant_85 = 
	    STATIC_STRING("1l8l1l8z1m8p83Ky1l83Cy000004z8r83ENy83ENy83=8y83=8y00001o1l8l1l8z1m8p83Ky1l83Cy000004z8r83CYy83CYy83=8y83=8y083E0y001o1l8l1l8z1m");
    string_constant_86 = 
	    STATIC_STRING("8p839=y1l83Cy000004z8r83Ejy83Ejy83=8y83=8y0+skkkkkkk3A++y001o1l8l1l8z1m8p839oy1l83Cy000004z8r83R=y83R=y83=8y83=8y083Py001o1l8l1l");
    string_constant_87 = 
	    STATIC_STRING("8z1m8p83CZy1l83Cy000004z8r83R4y83R4y83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r83RCy83RCy83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r");
    string_constant_88 = 
	    STATIC_STRING("83R9y83R9y83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r83R7y83R7y83=8y83=8y0k001o1l8l1m8p83R8y1l83Hy1l83Fy000004z8r83R5y83R5y83=8y83");
    string_constant_89 = 
	    STATIC_STRING("=8y00001o1l8l1m8p83Ky1l83Hy1l83Fy000004z8r83R3y83R3y83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r83D7y83D7y83=8y83=8y00001o1l8l1l8z1");
    string_constant_90 = 
	    STATIC_STRING("m8p833by1l83Cy000004z8r83c2y83c2y83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r83S3y83S3y83=8y83=8y00001n1l8l1l83Ny1l83Hy000004z8r83R");
    string_constant_91 = 
	    STATIC_STRING("6y83R6y83=8y83=8y00001o1l83Ey1l8l1l83Ny1l83Hy00000");
    string_constant_92 = 
	    STATIC_STRING("13Ey8q1p83=8y1l8328y1m8v83-Oy1o830by8301y8304y8305y8t1p83R1y1n02l835jyk5onone1l8l1n8p83Cay83Gy1l83Cy1q83C*y01l8l8z1m8p83Ky1l83Cy");
    string_constant_93 = 
	    STATIC_STRING("1q83ENy01l8l8z1m8p83Ky1l83Cy1q83CYy83E0y1l8l8z1m8p839=y1l83Cy1q83Ejy5k1l8l8z1m8p839oy1l83Cy1q83R=y83Py1l8l8z1m8p83CZy1l83Cy1p83R");
    string_constant_94 = 
	    STATIC_STRING("4y01l8l1l83Ny1l83Hy1p83RCy01l8l1l83Ny1l83Hy1p83R9y01l8l1l83Ny1l83Hy1q83R7yk1l8l1m8p83R8y1l83Hy1l83Fy1q83R5y01l8l1m8p83Ky1l83Hy1l");
    string_constant_95 = 
	    STATIC_STRING("83Fy1p83R3y01l8l1l83Ny1l83Hy1q83D7y01l8l8z1m8p833by1l83Cy1p83c2y01l8l1l83Ny1l83Hy1p83S3y08l1l83Ny1l83Hy1q83R6y01l83Ey1l8l1l83Ny1");
    string_constant_96 = STATIC_STRING("l83Hy");
    temp = regenerate_optimized_constant(string_constant_83);
    temp_2 = regenerate_optimized_constant(list(8,string_constant_84,
	    string_constant_85,string_constant_86,string_constant_87,
	    string_constant_88,string_constant_89,string_constant_90,
	    string_constant_91));
    add_class_to_environment(9,Qgsi_interface,list_constant_17,Nil,temp,
	    Nil,temp_2,list_constant_17,
	    regenerate_optimized_constant(LIST_5(string_constant_92,
	    string_constant_93,string_constant_94,string_constant_95,
	    string_constant_96)),Nil);
    Qcreation_attributes = STATIC_SYMBOL("CREATION-ATTRIBUTES",AB_package);
    Qput_creation_attributes_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CREATION-ATTRIBUTES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_creation_attributes_where_slot_is_absent,
	    STATIC_FUNCTION(put_creation_attributes_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qcreation_attributes,
	    SYMBOL_FUNCTION(Qput_creation_attributes_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qitem_reference_options = STATIC_SYMBOL("ITEM-REFERENCE-OPTIONS",
	    AB_package);
    Qput_item_reference_options_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-ITEM-REFERENCE-OPTIONS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_item_reference_options_where_slot_is_absent,
	    STATIC_FUNCTION(put_item_reference_options_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qitem_reference_options,
	    SYMBOL_FUNCTION(Qput_item_reference_options_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnames_of_remote_interface = STATIC_SYMBOL("NAMES-OF-REMOTE-INTERFACE",
	    AB_package);
    Qput_names_of_remote_interface_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NAMES-OF-REMOTE-INTERFACE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_names_of_remote_interface_where_slot_is_absent,
	    STATIC_FUNCTION(put_names_of_remote_interface_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnames_of_remote_interface,
	    SYMBOL_FUNCTION(Qput_names_of_remote_interface_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qclass_of_remote_interface = STATIC_SYMBOL("CLASS-OF-REMOTE-INTERFACE",
	    AB_package);
    Qput_class_of_remote_interface_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CLASS-OF-REMOTE-INTERFACE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_of_remote_interface_where_slot_is_absent,
	    STATIC_FUNCTION(put_class_of_remote_interface_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qclass_of_remote_interface,
	    SYMBOL_FUNCTION(Qput_class_of_remote_interface_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qremote_item = STATIC_SYMBOL("REMOTE-ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qentity,Qitem);
    check_if_superior_classes_are_defined(Qremote_item,list_constant_18);
    string_constant_97 = STATIC_STRING("1m1m8v839sy1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    string_constant_98 = 
	    STATIC_STRING("1o4z8r8u8u839sy839sy01p8w9k3-My3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3");
    string_constant_99 = 
	    STATIC_STRING("-Cy3ky83-ny1q83qy1q1mkk1m3-Cyk1m3-9yn1mnn1mn3hy1mk3ky1n1mkk1m3-Cyk1m3-9yn1n1mnn1mn3hy1mk3ky1n1mkk1m3-9yn1mnn1n1mnn1mk3ky1mkk83-m");
    string_constant_100 = 
	    STATIC_STRING("y1q83qy1q1m3-9yn1m3-Cyk1m3-Cy3ky1mk3ky1mn3hy1m3-9y3hy1n1m3-9yn1m3-Cyk1m3-Cy3ky1n1m3-Cy3ky1mk3ky1mn3hy1n1m3-9y3hy1m3-9yn1m3-Cy3ky");
    string_constant_101 = 
	    STATIC_STRING("1n1m3-Cy3ky1mn3hy1m3-9y3hy9l1p83Jy1mkk1mk3ky1m3-Cy3ky1m3-Cyk1o83Gy+3Cy3-Ey3-1y3-9y3-By3-Gy3-1ykkkkkkkkq3A++y1mu3Hy83-Vy1o83Gy+s3");
    string_constant_102 = 
	    STATIC_STRING("fy3-5y3-Gy3-1y3-9ykp3A++y1m3Ey3Vy83-Vy1o83Oy1m3-6yp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3-6y3fy1m3-6yp001o1l8l1l8o1l8z1m83Dy53YySee comm");
    string_constant_103 = 
	    STATIC_STRING("ent on ENTITY class definition000004z8r83Ssy83Ssy839sy839sy00001n1l8l1m8p83=Ky1l83Ny000004z8r83Sty83Sty839sy839sy00001n1l8l1m8p8");
    string_constant_104 = 
	    STATIC_STRING("3=oy1l83Ny000004z8r83Spy83Spy839sy839sy00001n1l8l1m8p83=oy1l83Ny00000");
    string_constant_105 = 
	    STATIC_STRING("1q8q1o839sy1m83-+y83Ry1m8v839sy8t1m8u1p8w9k3-My3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83");
    string_constant_106 = 
	    STATIC_STRING("-Ly1n83jy1mkk1m3-Cy3ky83-ny1q83qy1q1mkk1m3-Cyk1m3-9yn1mnn1mn3hy1mk3ky1n1mkk1m3-Cyk1m3-9yn1n1mnn1mn3hy1mk3ky1n1mkk1m3-9yn1mnn1n1m");
    string_constant_107 = 
	    STATIC_STRING("nn1mk3ky1mkk83-my1q83qy1q1m3-9yn1m3-Cyk1m3-Cy3ky1mk3ky1mn3hy1m3-9y3hy1n1m3-9yn1m3-Cyk1m3-Cy3ky1n1m3-Cy3ky1mk3ky1mn3hy1n1m3-9y3hy");
    string_constant_108 = 
	    STATIC_STRING("1m3-9yn1m3-Cy3ky1n1m3-Cy3ky1mn3hy1m3-9y3hy9l1p83Jy1mkk1mk3ky1m3-Cy3ky1m3-Cyk1o83Gy5qREMOTE1mu3Hy83-Vy1o83Gy5p-ITEM1m3Ey3Vy83-Vy1");
    string_constant_109 = 
	    STATIC_STRING("o83Oy1m3-6yp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3-6y3fy1m3-6yp1p83Ssy01l8l1m8p83=Ky1l83Ny1p83Sty01l8l1m8p83=oy1l83Ny1p83Spy01l8l1m8p83=");
    string_constant_110 = STATIC_STRING("oy1l83Ny");
    temp = regenerate_optimized_constant(string_constant_97);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_2 = regenerate_optimized_constant(list(7,string_constant_98,
	    string_constant_99,string_constant_100,string_constant_101,
	    string_constant_102,string_constant_103,string_constant_104));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qremote_item,list_constant_18,Nil,temp,Nil,
	    temp_2,list_constant_18,regenerate_optimized_constant(list(6,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110)),Nil);
    Qgsi_interface_status_code = STATIC_SYMBOL("GSI-INTERFACE-STATUS-CODE",
	    AB_package);
    Qwrite_gsi_interface_status_code_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-INTERFACE-STATUS-CODE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_interface_status_code_from_slot,
	    STATIC_FUNCTION(write_gsi_interface_status_code_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qgsi_interface_status_code,
	    SYMBOL_FUNCTION(Qwrite_gsi_interface_status_code_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgsi_interface_status_code),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qgsi_interface_status_code,
	    Qinteger);
    gsi_interface_status_code_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_interface_status_code_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_interface_status_code,
	    gsi_interface_status_code_evaluation_getter_1);
    Qinterface_warning_message_level = 
	    STATIC_SYMBOL("INTERFACE-WARNING-MESSAGE-LEVEL",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qquote,Qdefault);
    Qto = STATIC_SYMBOL("TO",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qquote,Qto);
    Qab_warning = STATIC_SYMBOL("WARNING",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qquote,Qab_warning);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qquote,Qmessage);
    Qlevel = STATIC_SYMBOL("LEVEL",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qquote,Qlevel);
    list_constant_24 = STATIC_LIST((SI_Long)5L,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23);
    Qwarning_message_level = STATIC_SYMBOL("WARNING-MESSAGE-LEVEL",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)3L,
	    Qinterface_warning_message_level,list_constant_24,
	    Qwarning_message_level);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)0L));
    Qop = STATIC_SYMBOL("(",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qquote,Qop);
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qquote,Qab_no);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qquote,Qab_or);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qquote,Qerror);
    Qmessages = STATIC_SYMBOL("MESSAGES",AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qquote,Qmessages);
    Qcp = STATIC_SYMBOL(")",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qcp);
    list_constant_27 = STATIC_CONS(list_constant_25,Qnil);
    list_constant_29 = STATIC_CONS(list_constant_26,list_constant_27);
    list_constant_34 = STATIC_CONS(list_constant_28,list_constant_29);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)6L,list_constant_30,
	    list_constant_31,list_constant_32,list_constant_21,
	    list_constant_33,list_constant_34);
    list_constant_36 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,
	    Qinterface_warning_message_level,list_constant_35,
	    list_constant_36);
    list_constant_37 = STATIC_CONS(Qquote,list_constant_36);
    Qserious = STATIC_SYMBOL("SERIOUS",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qquote,Qserious);
    Qonly = STATIC_SYMBOL("ONLY",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qquote,Qonly);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)7L,list_constant_37,
	    list_constant_31,list_constant_38,list_constant_28,
	    list_constant_26,list_constant_39,list_constant_27);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)3L,
	    Qinterface_warning_message_level,list_constant_40,
	    list_constant_36);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)2L));
    Qall = STATIC_SYMBOL("ALL",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qquote,Qall);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)4L,list_constant_41,
	    list_constant_31,list_constant_42,list_constant_34);
    list_constant_50 = STATIC_LIST_STAR((SI_Long)3L,
	    Qinterface_warning_message_level,list_constant_43,
	    list_constant_36);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)3L));
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qquote,Qand);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)7L,list_constant_44,
	    list_constant_31,list_constant_42,list_constant_28,
	    list_constant_45,list_constant_21,list_constant_29);
    list_constant_51 = STATIC_LIST_STAR((SI_Long)3L,
	    Qinterface_warning_message_level,list_constant_46,
	    list_constant_36);
    list_constant_52 = STATIC_LIST((SI_Long)5L,list_constant_47,
	    list_constant_48,list_constant_49,list_constant_50,
	    list_constant_51);
    add_grammar_rules_function(list_constant_52);
    string_constant_1 = STATIC_STRING("default to warning message level");
    string_constant_2 = STATIC_STRING("0 (no warning or error messages)");
    string_constant_3 = STATIC_STRING("1 (serious error messages only)");
    string_constant_4 = STATIC_STRING("2 (all error messages)");
    string_constant_5 = STATIC_STRING("3 (all error and warning messages)");
    Qwrite_interface_warning_message_level_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERFACE-WARNING-MESSAGE-LEVEL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interface_warning_message_level_from_slot,
	    STATIC_FUNCTION(write_interface_warning_message_level_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinterface_warning_message_level,
	    SYMBOL_FUNCTION(Qwrite_interface_warning_message_level_from_slot),
	    Qslot_value_writer);
    string_constant_111 = STATIC_STRING("1l1m83CZy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_111));
    Qgsi_application_name_symbol = 
	    STATIC_SYMBOL("GSI-APPLICATION-NAME-SYMBOL",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgsi_application_name_symbol),
	    Qtype_specification_simple_expansion,Qnil);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    define_type_specification_explicit_complex_type(Qgsi_application_name_symbol,
	    list_constant_2);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qgsi_application_name_symbol);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    gsi_application_name_symbol_evaluation_setter_1 = 
	    STATIC_FUNCTION(gsi_application_name_symbol_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qgsi_application_name_symbol,
	    gsi_application_name_symbol_evaluation_setter_1);
    gsi_application_name_symbol_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_application_name_symbol_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_application_name_symbol,
	    gsi_application_name_symbol_evaluation_getter_1);
    Qcompile_gsi_application_name_symbol_for_slot = 
	    STATIC_SYMBOL("COMPILE-GSI-APPLICATION-NAME-SYMBOL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gsi_application_name_symbol_for_slot,
	    STATIC_FUNCTION(compile_gsi_application_name_symbol_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qgsi_application_name_symbol,
	    SYMBOL_FUNCTION(Qcompile_gsi_application_name_symbol_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qgsi_application_name_symbol,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_gsi_application_name_symbol_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-APPLICATION-NAME-SYMBOL-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_application_name_symbol_from_slot,
	    STATIC_FUNCTION(write_gsi_application_name_symbol_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgsi_application_name_symbol,
	    SYMBOL_FUNCTION(Qwrite_gsi_application_name_symbol_from_slot),
	    Qslot_value_writer);
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    Qgsi_host_configuration = STATIC_SYMBOL("GSI-HOST-CONFIGURATION",
	    AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_53 = STATIC_CONS(Qno_item,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_5 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_53,
	    list_constant_5);
    set_property_value_function(get_symbol_properties_function(Qgsi_host_configuration),
	    Qtype_specification_simple_expansion,list_constant_54);
    Qnetwork_transport = STATIC_SYMBOL("NETWORK-TRANSPORT",AB_package);
    Qtcp_ip = STATIC_SYMBOL("TCP-IP",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qmember,Qtcp_ip);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qnetwork_transport,
	    list_constant_55);
    Qhostname = STATIC_SYMBOL("HOSTNAME",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_56 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_56);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qhostname,list_constant_57);
    Qport = STATIC_SYMBOL("PORT",AB_package);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_56);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qport,list_constant_58);
    list_constant_64 = STATIC_LIST((SI_Long)3L,list_constant_59,
	    list_constant_60,list_constant_61);
    list_constant_62 = STATIC_LIST((SI_Long)3L,Qand,Qhostname,Qport);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qab_or,list_constant_62);
    list_constant_65 = STATIC_LIST((SI_Long)3L,Qand,Qnetwork_transport,
	    list_constant_63);
    list_constant_66 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_64,list_constant_65);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_53,
	    list_constant_66);
    define_type_specification_explicit_complex_type(Qgsi_host_configuration,
	    list_constant_4);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qgsi_host_configuration);
    string_constant_6 = 
	    STATIC_STRING("The supplied value for network-transport, ~NV, must be tcpip");
    string_constant_7 = 
	    STATIC_STRING("Both hostname and port must be supplied");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_8 = STATIC_STRING("~NT ");
    string_constant_9 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    gsi_host_configuration_evaluation_setter_1 = 
	    STATIC_FUNCTION(gsi_host_configuration_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qgsi_host_configuration,
	    gsi_host_configuration_evaluation_setter_1);
    gsi_host_configuration_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_host_configuration_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_host_configuration,
	    gsi_host_configuration_evaluation_getter_1);
    Qprocess_initialization_string = 
	    STATIC_SYMBOL("PROCESS-INITIALIZATION-STRING",AB_package);
    set_property_value_function(get_symbol_properties_function(Qprocess_initialization_string),
	    Qtype_specification_simple_expansion,Qnil);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qwhole_string);
    define_type_specification_explicit_complex_type(Qprocess_initialization_string,
	    list_constant_7);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qprocess_initialization_string);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    process_initialization_string_evaluation_setter_1 = 
	    STATIC_FUNCTION(process_initialization_string_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qprocess_initialization_string,
	    process_initialization_string_evaluation_setter_1);
    process_initialization_string_evaluation_getter_1 = 
	    STATIC_FUNCTION(process_initialization_string_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qprocess_initialization_string,
	    process_initialization_string_evaluation_getter_1);
    Qinterface_timeout_period = STATIC_SYMBOL("INTERFACE-TIMEOUT-PERIOD",
	    AB_package);
    Qgsi_interface_timeout_period = 
	    STATIC_SYMBOL("GSI-INTERFACE-TIMEOUT-PERIOD",AB_package);
    Qput_gsi_interface_timeout_period_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-GSI-INTERFACE-TIMEOUT-PERIOD-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gsi_interface_timeout_period_where_slot_is_absent,
	    STATIC_FUNCTION(put_gsi_interface_timeout_period_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgsi_interface_timeout_period,
	    SYMBOL_FUNCTION(Qput_gsi_interface_timeout_period_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinterval_to_poll_external_system = 
	    STATIC_SYMBOL("INTERVAL-TO-POLL-EXTERNAL-SYSTEM",AB_package);
    Qtime_of_next_poll = STATIC_SYMBOL("TIME-OF-NEXT-POLL",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qput_interval_to_poll_external_system = 
	    STATIC_SYMBOL("PUT-INTERVAL-TO-POLL-EXTERNAL-SYSTEM",AB_package);
    SET_SYMBOL_FUNCTION(Qput_interval_to_poll_external_system,
	    STATIC_FUNCTION(put_interval_to_poll_external_system,NIL,FALSE,
	    3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qinterval_to_poll_external_system,
	    SYMBOL_FUNCTION(Qput_interval_to_poll_external_system),
	    Qslot_putter);
    Qg2_set_gsi_interface_interval_to_poll_external_system = 
	    STATIC_SYMBOL("G2-SET-GSI-INTERFACE-INTERVAL-TO-POLL-EXTERNAL-SYSTEM",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_gsi_interface_interval_to_poll_external_system,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_10 = 
	    STATIC_STRING("Invalid interval ~NV should be the symbol default or a positive integer");
    SET_SYMBOL_FUNCTION(Qg2_set_gsi_interface_interval_to_poll_external_system,
	    STATIC_FUNCTION(g2_set_gsi_interface_interval_to_poll_external_system,
	    NIL,FALSE,2,2));
    Qgsi_interface_status = STATIC_SYMBOL("GSI-INTERFACE-STATUS",AB_package);
    Qinitialize_after_reading_for_gsi_interface = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-GSI-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_gsi_interface,
	    STATIC_FUNCTION(initialize_after_reading_for_gsi_interface,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_gsi_interface);
    set_get(Qgsi_interface,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qidentifying_attributes = STATIC_SYMBOL("IDENTIFYING-ATTRIBUTES",
	    AB_package);
    Qattributes_which_identify_a_sensor = 
	    STATIC_SYMBOL("ATTRIBUTES-WHICH-IDENTIFY-A-SENSOR",AB_package);
    Qput_attributes_which_identify_a_sensor_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-ATTRIBUTES-WHICH-IDENTIFY-A-SENSOR-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_attributes_which_identify_a_sensor_where_slot_is_absent,
	    STATIC_FUNCTION(put_attributes_which_identify_a_sensor_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qattributes_which_identify_a_sensor,
	    SYMBOL_FUNCTION(Qput_attributes_which_identify_a_sensor_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_112 = 
	    STATIC_STRING("1p1m832uy1m9k83Zy1m832uy83-coy1m83-coy83-7Ky1o83-coy1n83-7Ky1m9k83vy83-coy1nmln9l1m83-7Ky836Iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_112));
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qattributes_which_identify_a_network_item_reference = 
	    STATIC_SYMBOL("ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE",
	    AB_package);
    Qcompile_attributes_which_identify_a_network_item_reference_for_slot = 
	    STATIC_SYMBOL("COMPILE-ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_attributes_which_identify_a_network_item_reference_for_slot,
	    STATIC_FUNCTION(compile_attributes_which_identify_a_network_item_reference_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qattributes_which_identify_a_network_item_reference,
	    SYMBOL_FUNCTION(Qcompile_attributes_which_identify_a_network_item_reference_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qattributes_which_identify_a_network_item_reference,
	    T,Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_1 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_attributes_which_identify_a_network_item_reference_from_slot = 
	    STATIC_SYMBOL("WRITE-ATTRIBUTES-WHICH-IDENTIFY-A-NETWORK-ITEM-REFERENCE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_attributes_which_identify_a_network_item_reference_from_slot,
	    STATIC_FUNCTION(write_attributes_which_identify_a_network_item_reference_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qattributes_which_identify_a_network_item_reference,
	    SYMBOL_FUNCTION(Qwrite_attributes_which_identify_a_network_item_reference_from_slot),
	    Qslot_value_writer);
    array_constant_3 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Qhome = STATIC_SYMBOL("HOME",AB_package);
    Qadd_home_to_name = STATIC_SYMBOL("ADD-HOME-TO-NAME",AB_package);
    string_constant_113 = 
	    STATIC_STRING("13Hy1m839ay1m9k83Zy1m839ay83-huy1o839ay1n83-huy1m9k83-Zy839ay1nmln9l1m83-huy83-YCy1m83-huy83-g=y1m83-huy83-MUy1m83-huy83-lNy1m83");
    string_constant_114 = 
	    STATIC_STRING("-huy83-lLy1n83-YCy1o1m9k83-oOy1m9k83jRy1m9k83*ty1m9k83-kdy1m83-Ofy8k1n83-YCy1n1m9k83=Ty1m9k9m1m9k83t4y1m83-Ofy01n83-g=y1n1m9k83=");
    string_constant_115 = 
	    STATIC_STRING("hy1m9k83-ZXy1m9k9m1m9n8k1n83-g=y1p1m9k83=hy1m9k83-ZXy1m9k9m1m9k83ALy1m9k83UIy1m9n83-vKy1n83-g=y1n1m9k83=Ty1m9k83=hy1m9k83t4y1m9n");
    string_constant_116 = 
	    STATIC_STRING("01n83-MUy1r1m9k83AMy1m9k83-Gy83jNy1m9k83=Iy1m9k83-gpy1m9k83UIy1m9k83jRy1n83-gtyn01n83-MUy1u1m9k83AMy1m9k83-jXy9o1m9k83=Iy1m9k9p1");
    string_constant_117 = 
	    STATIC_STRING("m9k83-Gy1m9k83-Ty1m9k83-gpy1m9k83UIy1m9k83jRy1n83-gty0n1n83-MUy1z1m9k83AMy1m9k83-jXy9o1m9k83=Iy1m9k9p1m9k83-Gy1m9k83-Ty1m9k83-gp");
    string_constant_118 = 
	    STATIC_STRING("y1m9k83UIy1m9k83jRy1m9k83vy1m9k83=Fy1m9k83Py1m9k83-Gy83jNy1n83-gtyzn1n83-MUy1n1m9k83=Ty1m9k83-Gy1m9k83t4y1n83-gty001n83-lNy1q1m9");
    string_constant_119 = 
	    STATIC_STRING("k83-2cy1m9k837by1m9k83-lQy1m9k83Fmy1m9k83-Ywy1m9k83Gry1m83-lMy8k1n83-lNy1p1m9k830Iy1m9k9q1m9k83-2cy1m9k837by1m9k83-lQy1m83-lMy01");
    string_constant_120 = 
	    STATIC_STRING("n83-lLy1p1m9k83Iqy1m9k83-lQy1m9k83Fmy1m9k83-PQy1m9k83Gry1m83-lKy8k1n83-lLy1o1m9k830Iy1m9k9q1m9k83Iqy1m9k83-lQy1m83-lKy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qhome);
    push_optimized_constant(Qadd_home_to_name);
    push_optimized_constant(Qstring);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(list(8,
	    string_constant_113,string_constant_114,string_constant_115,
	    string_constant_116,string_constant_117,string_constant_118,
	    string_constant_119,string_constant_120)));
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qoptions_for_item_reference = 
	    STATIC_SYMBOL("OPTIONS-FOR-ITEM-REFERENCE",AB_package);
    Qcompile_options_for_item_reference_for_slot = 
	    STATIC_SYMBOL("COMPILE-OPTIONS-FOR-ITEM-REFERENCE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_options_for_item_reference_for_slot,
	    STATIC_FUNCTION(compile_options_for_item_reference_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qoptions_for_item_reference,
	    SYMBOL_FUNCTION(Qcompile_options_for_item_reference_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qoptions_for_item_reference,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qconvert_home_to_local = STATIC_SYMBOL("CONVERT-HOME-TO-LOCAL",AB_package);
    string_constant_11 = STATIC_STRING("serve items by proxy");
    string_constant_12 = STATIC_STRING("no home conversion");
    string_constant_13 = STATIC_STRING("name includes home");
    Qunless_local = STATIC_SYMBOL("UNLESS-LOCAL",AB_package);
    string_constant_14 = STATIC_STRING("name includes home unless local");
    string_constant_15 = STATIC_STRING("no name conversion");
    Qnon_local_item_class = STATIC_SYMBOL("NON-LOCAL-ITEM-CLASS",AB_package);
    string_constant_16 = 
	    STATIC_STRING("use prefix ~S for the class of non local items,~\n                                    with default class ~NN");
    string_constant_17 = STATIC_STRING("use class ~NN for non local items");
    string_constant_18 = 
	    STATIC_STRING("use prefix ~S for the class of non local items");
    string_constant_19 = STATIC_STRING("no class conversion");
    Qreference_lookup_option = STATIC_SYMBOL("REFERENCE-LOOKUP-OPTION",
	    AB_package);
    string_constant_20 = 
	    STATIC_STRING("look up references using identifying attributes");
    string_constant_21 = STATIC_STRING("do not look up references");
    Qreference_creation_option = STATIC_SYMBOL("REFERENCE-CREATION-OPTION",
	    AB_package);
    string_constant_22 = 
	    STATIC_STRING("create references using creation attributes");
    string_constant_23 = STATIC_STRING("do not create references");
    array_constant_8 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_options_for_item_reference_from_slot = 
	    STATIC_SYMBOL("WRITE-OPTIONS-FOR-ITEM-REFERENCE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_options_for_item_reference_from_slot,
	    STATIC_FUNCTION(write_options_for_item_reference_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qoptions_for_item_reference,
	    SYMBOL_FUNCTION(Qwrite_options_for_item_reference_from_slot),
	    Qslot_value_writer);
    Qno_grouping = STATIC_SYMBOL("NO-GROUPING",AB_package);
    if (No_grouping_tag_for_grouping_specification == UNBOUND)
	No_grouping_tag_for_grouping_specification = Qno_grouping;
    string_constant_121 = 
	    STATIC_STRING("1r1o839=y1o1m9k83-XHy1m9k83-mMy1m9k83*ty83-d+y1m83vyo9l1n839=y1m1m9k83=Ty1m9k83-XJy83E0y1m83-KCy1m9k83Zy1m83-KCy83-d+y1m83-d+y83");
    string_constant_122 = 
	    STATIC_STRING("-XXy1o83-d+y1n83-XXy1m9k83vy83-d+y1nmln9l1m83-XXy83dey");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_121,
	    string_constant_122)));
    Qgsi_variable_grouping_specification = 
	    STATIC_SYMBOL("GSI-VARIABLE-GROUPING-SPECIFICATION",AB_package);
    Qcompile_gsi_variable_grouping_specification_for_slot = 
	    STATIC_SYMBOL("COMPILE-GSI-VARIABLE-GROUPING-SPECIFICATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gsi_variable_grouping_specification_for_slot,
	    STATIC_FUNCTION(compile_gsi_variable_grouping_specification_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qgsi_variable_grouping_specification,
	    SYMBOL_FUNCTION(Qcompile_gsi_variable_grouping_specification_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgsi_variable_grouping_specification,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgrouping_specification = STATIC_SYMBOL("GROUPING-SPECIFICATION",
	    AB_package);
    Qsensor_grouping_specification = 
	    STATIC_SYMBOL("SENSOR-GROUPING-SPECIFICATION",AB_package);
    Qput_sensor_grouping_specification_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SENSOR-GROUPING-SPECIFICATION-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_sensor_grouping_specification_where_slot_is_absent,
	    STATIC_FUNCTION(put_sensor_grouping_specification_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsensor_grouping_specification,
	    SYMBOL_FUNCTION(Qput_sensor_grouping_specification_where_slot_is_absent),
	    Qabsent_slot_putter);
    array_constant_9 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    Qwrite_gsi_variable_grouping_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-VARIABLE-GROUPING-SPECIFICATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_variable_grouping_specification_from_slot,
	    STATIC_FUNCTION(write_gsi_variable_grouping_specification_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgsi_variable_grouping_specification,
	    SYMBOL_FUNCTION(Qwrite_gsi_variable_grouping_specification_from_slot),
	    Qslot_value_writer);
    string_constant_24 = STATIC_STRING("~A~A~A");
    string_constant_25 = STATIC_STRING("");
    string_constant_26 = STATIC_STRING("TCP/IP hostname must be text");
    string_constant_27 = STATIC_STRING(" and ");
    string_constant_28 = STATIC_STRING("TCP/IP port must be an integer");
    Qlocalhost = STATIC_SYMBOL("LOCALHOST",AB_package);
    string_constant_29 = STATIC_STRING("LOCALNET hostname must be LOCALHOST");
    string_constant_30 = 
	    STATIC_STRING("No port allowed in LOCALNET specification");
    string_constant_31 = 
	    STATIC_STRING("LOCALNET is not a valid network transport");
    string_constant_32 = STATIC_STRING("Network transport must be ~A");
    string_constant_33 = STATIC_STRING("one of TCP-IP or LOCALNET");
    string_constant_34 = STATIC_STRING("TCP-IP");
    Qcompile_gsi_host_configuration_for_slot = 
	    STATIC_SYMBOL("COMPILE-GSI-HOST-CONFIGURATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gsi_host_configuration_for_slot,
	    STATIC_FUNCTION(compile_gsi_host_configuration_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qgsi_host_configuration,
	    SYMBOL_FUNCTION(Qcompile_gsi_host_configuration_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgsi_host_configuration,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgsi_interface_p_function = STATIC_SYMBOL("GSI-INTERFACE-P-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgsi_interface_p_function,
	    STATIC_FUNCTION(gsi_interface_p_function,NIL,FALSE,1,1));
    string_constant_123 = 
	    STATIC_STRING("1o1m83AEy833by1n83AEy1m9k83-Foy83-Foy1m833by83-oy1n833by1m1m9k83AMy1m9k83Py83Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_123));
    array_constant_11 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)57344L);
    string_constant_35 = 
	    STATIC_STRING("The interval must be less than 65535 seconds!");
    Qtimeout_interval_or_default = 
	    STATIC_SYMBOL("TIMEOUT-INTERVAL-OR-DEFAULT",AB_package);
    Qcompile_timeout_interval_or_default_for_slot = 
	    STATIC_SYMBOL("COMPILE-TIMEOUT-INTERVAL-OR-DEFAULT-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_timeout_interval_or_default_for_slot,
	    STATIC_FUNCTION(compile_timeout_interval_or_default_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtimeout_interval_or_default,
	    SYMBOL_FUNCTION(Qcompile_timeout_interval_or_default_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtimeout_interval_or_default,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qunlimited = STATIC_SYMBOL("UNLIMITED",AB_package);
    Qtimeout_interval_or_default_or_none = 
	    STATIC_SYMBOL("TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE",AB_package);
    Qcompile_timeout_interval_or_default_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_timeout_interval_or_default_or_none_for_slot,
	    STATIC_FUNCTION(compile_timeout_interval_or_default_or_none_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtimeout_interval_or_default_or_none,
	    SYMBOL_FUNCTION(Qcompile_timeout_interval_or_default_or_none_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtimeout_interval_or_default_or_none,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_68 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qinteger);
    set_property_value_function(get_symbol_properties_function(Qtimeout_interval_or_default),
	    Qtype_specification_simple_expansion,list_constant_68);
    Quse_default = STATIC_SYMBOL("USE-DEFAULT",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qmember,Quse_default);
    list_constant_70 = STATIC_CONS(Qinteger,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,list_constant_69,
	    list_constant_70);
    define_type_specification_explicit_complex_type(Qtimeout_interval_or_default,
	    list_constant_9);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtimeout_interval_or_default);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    timeout_interval_or_default_evaluation_setter_1 = 
	    STATIC_FUNCTION(timeout_interval_or_default_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtimeout_interval_or_default,
	    timeout_interval_or_default_evaluation_setter_1);
    timeout_interval_or_default_evaluation_getter_1 = 
	    STATIC_FUNCTION(timeout_interval_or_default_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtimeout_interval_or_default,
	    timeout_interval_or_default_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qtimeout_interval_or_default_or_none),
	    Qtype_specification_simple_expansion,list_constant_68);
    list_constant_71 = STATIC_LIST((SI_Long)3L,Qmember,Quse_default,
	    Qunlimited);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_71,list_constant_70);
    define_type_specification_explicit_complex_type(Qtimeout_interval_or_default_or_none,
	    list_constant_11);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtimeout_interval_or_default_or_none);
    timeout_interval_or_default_or_none_evaluation_setter_1 = 
	    STATIC_FUNCTION(timeout_interval_or_default_or_none_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtimeout_interval_or_default_or_none,
	    timeout_interval_or_default_or_none_evaluation_setter_1);
    timeout_interval_or_default_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(timeout_interval_or_default_or_none_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtimeout_interval_or_default_or_none,
	    timeout_interval_or_default_or_none_evaluation_getter_1);
    string_constant_36 = STATIC_STRING("use default");
    Qwrite_timeout_interval_or_default_from_slot = 
	    STATIC_SYMBOL("WRITE-TIMEOUT-INTERVAL-OR-DEFAULT-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_timeout_interval_or_default_from_slot,
	    STATIC_FUNCTION(write_timeout_interval_or_default_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtimeout_interval_or_default,
	    SYMBOL_FUNCTION(Qwrite_timeout_interval_or_default_from_slot),
	    Qslot_value_writer);
    string_constant_37 = STATIC_STRING("unlimited");
    Qwrite_timeout_interval_or_default_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-TIMEOUT-INTERVAL-OR-DEFAULT-OR-NONE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_timeout_interval_or_default_or_none_from_slot,
	    STATIC_FUNCTION(write_timeout_interval_or_default_or_none_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtimeout_interval_or_default_or_none,
	    SYMBOL_FUNCTION(Qwrite_timeout_interval_or_default_or_none_from_slot),
	    Qslot_value_writer);
    string_constant_124 = 
	    STATIC_STRING("1t1m83-*Jy83-6y1m83-7Ly83-6y1m83-EUy83Sy1m83wHy83-Uy1m83iVy83-Uy1m839oy83-Uy1m83Cay1m9k83Zy1n83Cay1p1m9k83bYy1m9k83Ray83iVy1m9k8");
    string_constant_125 = 
	    STATIC_STRING("3Xvy83-EUy1o83bYynp01n83Cay1r1m9k83bYy1m9k83Ray83iVy1m9k83Xvy83-EUy1m9k83-CUy83Ky1o83bYynpr");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_124,
	    string_constant_125)));
    Qgsi_data_service = STATIC_SYMBOL("GSI-DATA-SERVICE",AB_package);
    list_constant_72 = STATIC_CONS(Qvariable,Qnil);
    check_if_superior_classes_are_defined(Qgsi_data_service,list_constant_72);
    string_constant_126 = 
	    STATIC_STRING("1q1l8t1m830ky83*dy1m8v83*dy1l83-8y1l83Iy1l83Ly");
    string_constant_127 = 
	    STATIC_STRING("1r4z8r83*My83*My839-y839-y08345y001o1l8o1l8l1m8p83*My1l8z000004z8r831ay831ay839-y839-y00001p1l83Ey1l8l1l8z1m8p831ay1l83Cy000004z");
    string_constant_128 = 
	    STATIC_STRING("8r83=8y83=8y839-y839-y00001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83RBy83RBy839-y839-y00001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83R0y83R0y83");
    string_constant_129 = 
	    STATIC_STRING("9-y839-y0k001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83RAy83RAy839-y839-y00001o1l83Ey1l8l1l83Ny1l83Hy000004z8r83RDy83RDy839-y839-y0k001o");
    string_constant_130 = STATIC_STRING("1l83Ey1l8l1l83Fy1m8p83REy00000");
    string_constant_131 = 
	    STATIC_STRING("1t8q1s839-y1l83*dy8t1m830ky83*dy1m8v83*dy83-8y83Iy83Ly1p83*My8345y1l8o1l8l1m8p83*My1r831ay01l83Ey1l8l8z1m8p831ay1l83Cy1q83=8y01l");
    string_constant_132 = 
	    STATIC_STRING("83Ey1l8l1l83Ny1l83Hy1q83RBy01l83Ey1l8l1l83Ny1l83Hy1q83R0yk1l83Ey1l8l1l83Ny1l83Hy1q83RAy01l83Ey1l8l1l83Ny1l83Hy1q83RDyk1l83Ey1l8l");
    string_constant_133 = STATIC_STRING("83Fy1m8p83REy");
    temp = regenerate_optimized_constant(string_constant_126);
    temp_2 = regenerate_optimized_constant(LIST_4(string_constant_127,
	    string_constant_128,string_constant_129,string_constant_130));
    add_class_to_environment(9,Qgsi_data_service,list_constant_72,Nil,temp,
	    Nil,temp_2,list_constant_72,
	    regenerate_optimized_constant(LIST_3(string_constant_131,
	    string_constant_132,string_constant_133)),Nil);
    Qgsi_variable_status_code = STATIC_SYMBOL("GSI-VARIABLE-STATUS-CODE",
	    AB_package);
    Qwrite_gsi_variable_status_code_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-VARIABLE-STATUS-CODE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_variable_status_code_from_slot,
	    STATIC_FUNCTION(write_gsi_variable_status_code_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qgsi_variable_status_code,
	    SYMBOL_FUNCTION(Qwrite_gsi_variable_status_code_from_slot),
	    Qslot_value_writer);
    set_property_value_function(get_symbol_properties_function(Qgsi_variable_status_code),
	    Qtype_specification_simple_expansion,Qinteger);
    define_type_specification_explicit_complex_type(Qgsi_variable_status_code,
	    Qinteger);
    gsi_variable_status_code_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_variable_status_code_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_variable_status_code,
	    gsi_variable_status_code_evaluation_getter_1);
    Qgsi_interface_name = STATIC_SYMBOL("GSI-INTERFACE-NAME",AB_package);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_53,list_constant_56);
    set_property_value_function(get_symbol_properties_function(Qgsi_interface_name),
	    Qtype_specification_simple_expansion,list_constant_13);
    define_type_specification_explicit_complex_type(Qgsi_interface_name,
	    list_constant_13);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qnamed,Qgsi_interface_name);
    gsi_interface_name_evaluation_setter_1 = 
	    STATIC_FUNCTION(gsi_interface_name_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qgsi_interface_name,
	    gsi_interface_name_evaluation_setter_1);
    gsi_interface_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(gsi_interface_name_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qgsi_interface_name,
	    gsi_interface_name_evaluation_getter_1);
    Qgsi_collection_interval = STATIC_SYMBOL("GSI-COLLECTION-INTERVAL",
	    AB_package);
    Qreclaim_gsi_collection_interval_value = 
	    STATIC_SYMBOL("RECLAIM-GSI-COLLECTION-INTERVAL-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gsi_collection_interval_value,
	    STATIC_FUNCTION(reclaim_gsi_collection_interval_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qgsi_collection_interval,
	    SYMBOL_FUNCTION(Qreclaim_gsi_collection_interval_value),
	    Qslot_value_reclaimer);
    Qremote_process_initialization_string = 
	    STATIC_SYMBOL("REMOTE-PROCESS-INITIALIZATION-STRING",AB_package);
    Qput_remote_process_initialization_string = 
	    STATIC_SYMBOL("PUT-REMOTE-PROCESS-INITIALIZATION-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_remote_process_initialization_string,
	    STATIC_FUNCTION(put_remote_process_initialization_string,NIL,
	    FALSE,3,3));
    mutate_global_property(Qremote_process_initialization_string,
	    SYMBOL_FUNCTION(Qput_remote_process_initialization_string),
	    Qslot_putter);
    string_constant_38 = STATIC_STRING("~s");
    Qwrite_process_initialization_string_from_slot = 
	    STATIC_SYMBOL("WRITE-PROCESS-INITIALIZATION-STRING-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_process_initialization_string_from_slot,
	    STATIC_FUNCTION(write_process_initialization_string_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qprocess_initialization_string,
	    SYMBOL_FUNCTION(Qwrite_process_initialization_string_from_slot),
	    Qslot_value_writer);
    Qcompile_process_initialization_string_for_slot = 
	    STATIC_SYMBOL("COMPILE-PROCESS-INITIALIZATION-STRING-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_process_initialization_string_for_slot,
	    STATIC_FUNCTION(compile_process_initialization_string_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qprocess_initialization_string,
	    SYMBOL_FUNCTION(Qcompile_process_initialization_string_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qprocess_initialization_string,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_39 = STATIC_STRING("none");
    array_constant_12 = STATIC_ARRAY(list_constant_67,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    string_constant_40 = STATIC_STRING("tcp-ip host ~S port-number ~A");
    string_constant_41 = 
	    STATIC_STRING("[Unknown/Obsolete value: ~a / ~a / ~a]");
    Qwrite_gsi_host_configuration_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-HOST-CONFIGURATION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_host_configuration_from_slot,
	    STATIC_FUNCTION(write_gsi_host_configuration_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qgsi_host_configuration,
	    SYMBOL_FUNCTION(Qwrite_gsi_host_configuration_from_slot),
	    Qslot_value_writer);
    Qgsi_variable_status = STATIC_SYMBOL("GSI-VARIABLE-STATUS",AB_package);
    Qput_gsi_variable_status = STATIC_SYMBOL("PUT-GSI-VARIABLE-STATUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gsi_variable_status,
	    STATIC_FUNCTION(put_gsi_variable_status,NIL,FALSE,3,3));
    mutate_global_property(Qgsi_variable_status,
	    SYMBOL_FUNCTION(Qput_gsi_variable_status),Qslot_putter);
    Qgsi_message_service = STATIC_SYMBOL("GSI-MESSAGE-SERVICE",AB_package);
    list_constant_73 = STATIC_CONS(Qitem,Qnil);
    check_if_superior_classes_are_defined(Qgsi_message_service,
	    list_constant_73);
    string_constant_134 = STATIC_STRING("1p1l8t1m8v83Ry1l83-8y1l83Iy1l83Ly");
    string_constant_135 = 
	    STATIC_STRING("1m4z8r831ay831ay839*y839*y00001q1l83Ey1l83-4y1l8l1l8z1m8p831ay1l83Cy000004z8r833oy833oy839*y839*y08345y001o1l83Ey1l8l1l8z1m8p83-");
    string_constant_136 = STATIC_STRING("2y00000");
    string_constant_137 = 
	    STATIC_STRING("1o8q1r839*y1l83Ry8t1m8v83Ry83-8y83Iy83Ly1s831ay01l83Ey1l83-4y1l8l8z1m8p831ay1l83Cy1q833oy8345y1l83Ey1l8l8z1m8p83-2y");
    temp = regenerate_optimized_constant(string_constant_134);
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_135,
	    string_constant_136));
    add_class_to_environment(9,Qgsi_message_service,list_constant_73,Nil,
	    temp,Nil,temp_2,list_constant_73,
	    regenerate_optimized_constant(string_constant_137),Nil);
    Qdata_server_for_messages = STATIC_SYMBOL("DATA-SERVER-FOR-MESSAGES",
	    AB_package);
    Qput_data_server_for_messages = 
	    STATIC_SYMBOL("PUT-DATA-SERVER-FOR-MESSAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_server_for_messages,
	    STATIC_FUNCTION(put_data_server_for_messages,NIL,FALSE,3,3));
    mutate_global_property(Qdata_server_for_messages,
	    SYMBOL_FUNCTION(Qput_data_server_for_messages),Qslot_putter);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qquote,Qnone);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qgsi_interface_name,
	    list_constant_74);
    list_constant_75 = STATIC_CONS(Qunreserved_symbol,Qnil);
    list_constant_77 = STATIC_CONS(Qgsi_interface_name,list_constant_75);
    list_constant_78 = STATIC_LIST((SI_Long)2L,list_constant_76,
	    list_constant_77);
    add_grammar_rules_function(list_constant_78);
    Qwrite_gsi_interface_name_from_slot = 
	    STATIC_SYMBOL("WRITE-GSI-INTERFACE-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_gsi_interface_name_from_slot,
	    STATIC_FUNCTION(write_gsi_interface_name_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qgsi_interface_name,
	    SYMBOL_FUNCTION(Qwrite_gsi_interface_name_from_slot),
	    Qslot_value_writer);
    Qgsi_data_server = STATIC_SYMBOL("GSI-DATA-SERVER",AB_package);
    string_constant_138 = STATIC_STRING("GSI data server");
    def_data_server_pretty_printer(Qgsi_data_server,string_constant_138);
    Qgsi_interface_icp_socket = STATIC_SYMBOL("GSI-INTERFACE-ICP-SOCKET",
	    AB_package);
    Qexternal_system_has_a_scheduler = 
	    STATIC_SYMBOL("EXTERNAL-SYSTEM-HAS-A-SCHEDULER",AB_package);
    Qnames = STATIC_SYMBOL("NAMES",AB_package);
    Qnote_name_change_for_gsi_data_service = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-GSI-DATA-SERVICE",AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_gsi_data_service,
	    STATIC_FUNCTION(note_name_change_for_gsi_data_service,NIL,
	    FALSE,3,3));
    Qnote_name_change = STATIC_SYMBOL("NOTE-NAME-CHANGE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qnote_name_change_for_gsi_data_service);
    set_get(Qgsi_data_service,Qnote_name_change,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_data_service,temp);
    mutate_global_property(Qnote_name_change,temp_1,Qclasses_which_define);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qlist_of_gsi_values_to_process_head = 
	    STATIC_SYMBOL("LIST-OF-GSI-VALUES-TO-PROCESS-HEAD",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_gsi_values_to_process_head,
	    List_of_gsi_values_to_process_head);
    Qg2_gsi = STATIC_SYMBOL("G2-GSI",AB_package);
    record_system_variable(Qlist_of_gsi_values_to_process_head,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qlist_of_gsi_values_to_process_tail = 
	    STATIC_SYMBOL("LIST-OF-GSI-VALUES-TO-PROCESS-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_gsi_values_to_process_tail,
	    List_of_gsi_values_to_process_tail);
    record_system_variable(Qlist_of_gsi_values_to_process_tail,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qtask_to_process_gsi_values = 
	    STATIC_SYMBOL("TASK-TO-PROCESS-GSI-VALUES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_to_process_gsi_values,
	    Task_to_process_gsi_values);
    record_system_variable(Qtask_to_process_gsi_values,Qg2_gsi,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qtask_to_process_gsi_interfaces = 
	    STATIC_SYMBOL("TASK-TO-PROCESS-GSI-INTERFACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_to_process_gsi_interfaces,
	    Task_to_process_gsi_interfaces);
    record_system_variable(Qtask_to_process_gsi_interfaces,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qtask_scheduled_to_process_gsi_values_qm = 
	    STATIC_SYMBOL("TASK-SCHEDULED-TO-PROCESS-GSI-VALUES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_scheduled_to_process_gsi_values_qm,
	    Task_scheduled_to_process_gsi_values_qm);
    record_system_variable(Qtask_scheduled_to_process_gsi_values_qm,
	    Qg2_gsi,Nil,Qnil,Qnil,Qnil,Qnil);
    Qgsi_internal_collection_interval = 
	    STATIC_SYMBOL("GSI-INTERNAL-COLLECTION-INTERVAL",AB_package);
    Qmax_gsi_sensors_in_a_group = 
	    STATIC_SYMBOL("MAX-GSI-SENSORS-IN-A-GROUP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmax_gsi_sensors_in_a_group,
	    Max_gsi_sensors_in_a_group);
    record_system_variable(Qmax_gsi_sensors_in_a_group,Qg2_gsi,
	    FIX((SI_Long)20L),Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_sensor_group_g2_struct = 
	    STATIC_SYMBOL("SENSOR-GROUP-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsensor_group = STATIC_SYMBOL("SENSOR-GROUP",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_sensor_group_g2_struct,
	    Qsensor_group,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsensor_group,
	    Qg2_defstruct_structure_name_sensor_group_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_sensor_group == UNBOUND)
	The_type_description_of_sensor_group = Nil;
    string_constant_139 = 
	    STATIC_STRING("43Dy8m83mky1n83mky8n8k1l8n0000001l1n8y83-5ly1n83-CZy83-Cay83-CYykrk0k0");
    temp = The_type_description_of_sensor_group;
    The_type_description_of_sensor_group = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_139));
    mutate_global_property(Qg2_defstruct_structure_name_sensor_group_g2_struct,
	    The_type_description_of_sensor_group,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsensor_group,
	    The_type_description_of_sensor_group,Qtype_description_of_type);
    Qoutstanding_sensor_group_count = 
	    STATIC_SYMBOL("OUTSTANDING-SENSOR-GROUP-COUNT",AB_package);
    Qsensor_group_structure_memory_usage = 
	    STATIC_SYMBOL("SENSOR-GROUP-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_140 = STATIC_STRING("1q83mky8s83-oAy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sensor_group_count);
    push_optimized_constant(Qsensor_group_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_140));
    Qchain_of_available_sensor_groups = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SENSOR-GROUPS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sensor_groups,
	    Chain_of_available_sensor_groups);
    record_system_variable(Qchain_of_available_sensor_groups,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qsensor_group_count = STATIC_SYMBOL("SENSOR-GROUP-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsensor_group_count,Sensor_group_count);
    record_system_variable(Qsensor_group_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_sensor_groups_vector == UNBOUND)
	Chain_of_available_sensor_groups_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsensor_group_structure_memory_usage,
	    STATIC_FUNCTION(sensor_group_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_sensor_group_count,
	    STATIC_FUNCTION(outstanding_sensor_group_count,NIL,FALSE,0,0));
    reclaim_structure_for_sensor_group_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_sensor_group,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsensor_group,
	    reclaim_structure_for_sensor_group_1);
    Qg2_defstruct_structure_name_sensor_groups_header_g2_struct = 
	    STATIC_SYMBOL("SENSOR-GROUPS-HEADER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsensor_groups_header = STATIC_SYMBOL("SENSOR-GROUPS-HEADER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_sensor_groups_header_g2_struct,
	    Qsensor_groups_header,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsensor_groups_header,
	    Qg2_defstruct_structure_name_sensor_groups_header_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_sensor_groups_header == UNBOUND)
	The_type_description_of_sensor_groups_header = Nil;
    string_constant_141 = 
	    STATIC_STRING("43Dy8m83mly1n83mly8n8k1l8n0000001l1m8y83-5myknk0k0");
    temp = The_type_description_of_sensor_groups_header;
    The_type_description_of_sensor_groups_header = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_141));
    mutate_global_property(Qg2_defstruct_structure_name_sensor_groups_header_g2_struct,
	    The_type_description_of_sensor_groups_header,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsensor_groups_header,
	    The_type_description_of_sensor_groups_header,
	    Qtype_description_of_type);
    Qoutstanding_sensor_groups_header_count = 
	    STATIC_SYMBOL("OUTSTANDING-SENSOR-GROUPS-HEADER-COUNT",AB_package);
    Qsensor_groups_header_structure_memory_usage = 
	    STATIC_SYMBOL("SENSOR-GROUPS-HEADER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_142 = STATIC_STRING("1q83mly8s83-oBy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sensor_groups_header_count);
    push_optimized_constant(Qsensor_groups_header_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_142));
    Qchain_of_available_sensor_groups_headers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SENSOR-GROUPS-HEADERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sensor_groups_headers,
	    Chain_of_available_sensor_groups_headers);
    record_system_variable(Qchain_of_available_sensor_groups_headers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsensor_groups_header_count = 
	    STATIC_SYMBOL("SENSOR-GROUPS-HEADER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsensor_groups_header_count,
	    Sensor_groups_header_count);
    record_system_variable(Qsensor_groups_header_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_sensor_groups_headers_vector == UNBOUND)
	Chain_of_available_sensor_groups_headers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsensor_groups_header_structure_memory_usage,
	    STATIC_FUNCTION(sensor_groups_header_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_sensor_groups_header_count,
	    STATIC_FUNCTION(outstanding_sensor_groups_header_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_sensor_groups_header_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_sensor_groups_header,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsensor_groups_header,
	    reclaim_structure_for_sensor_groups_header_1);
    Qlist_of_all_gsi_interfaces = 
	    STATIC_SYMBOL("LIST-OF-ALL-GSI-INTERFACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_all_gsi_interfaces,
	    List_of_all_gsi_interfaces);
    record_system_variable(Qlist_of_all_gsi_interfaces,Qg2_gsi,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qgsi_interfaces_to_process_head = 
	    STATIC_SYMBOL("GSI-INTERFACES-TO-PROCESS-HEAD",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_interfaces_to_process_head,
	    Gsi_interfaces_to_process_head);
    record_system_variable(Qgsi_interfaces_to_process_head,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qgsi_interfaces_to_process_tail = 
	    STATIC_SYMBOL("GSI-INTERFACES-TO-PROCESS-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_interfaces_to_process_tail,
	    Gsi_interfaces_to_process_tail);
    record_system_variable(Qgsi_interfaces_to_process_tail,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    string_constant_42 = 
	    STATIC_STRING("GSI sensor ~NF received error code ~a");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qprocess_gsi_sensor_values = STATIC_SYMBOL("PROCESS-GSI-SENSOR-VALUES",
	    AB_package);
    string_constant_43 = 
	    STATIC_STRING("GSI received a value for a sensor which does not exist or is ~\n            no longer active.");
    string_constant_44 = 
	    STATIC_STRING("~a~NF received error code 0 with a NULL_TAG data type");
    string_constant_45 = STATIC_STRING("GSI sensor ");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qprocess_gsi_sensor_values,
	    STATIC_FUNCTION(process_gsi_sensor_values,NIL,FALSE,1,1));
    string_constant_46 = 
	    STATIC_STRING("Can not conclude a value into ~NF, ~\n                                           because it is not a variable or parameter");
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    string_constant_47 = 
	    STATIC_STRING("Can not conclude ~NF into ~NF, ~\n                                           because it is not a value");
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    string_constant_48 = 
	    STATIC_STRING("Can not conclude ~NV into ~NF, ~\n                                           because it is not of the correct type");
    string_constant_49 = STATIC_STRING("Problem receiving GSI value: ~a");
    Qvector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    string_constant_50 = STATIC_STRING("~NF is not an array");
    string_constant_51 = STATIC_STRING("array index out of bounds");
    Qlist_element = STATIC_SYMBOL("LIST-ELEMENT",AB_package);
    string_constant_52 = STATIC_STRING("~NF is not an list");
    string_constant_53 = STATIC_STRING("list index out of bounds");
    string_constant_54 = 
	    STATIC_STRING("gsi_return_attrs into a list: not yet implemented");
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qicp_sockets_now_initializing_gsi = 
	    STATIC_SYMBOL("ICP-SOCKETS-NOW-INITIALIZING-GSI",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_sockets_now_initializing_gsi,
	    Icp_sockets_now_initializing_gsi);
    record_system_variable(Qicp_sockets_now_initializing_gsi,Qg2_gsi,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qactivate_for_gsi_interface = 
	    STATIC_SYMBOL("ACTIVATE-FOR-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_gsi_interface,
	    STATIC_FUNCTION(activate_for_gsi_interface,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_gsi_interface);
    set_get(Qgsi_interface,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    Qmanually_enable_for_gsi_interface = 
	    STATIC_SYMBOL("MANUALLY-ENABLE-FOR-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_enable_for_gsi_interface,
	    STATIC_FUNCTION(manually_enable_for_gsi_interface,NIL,FALSE,1,1));
    Qmanually_enable = STATIC_SYMBOL("MANUALLY-ENABLE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qmanually_enable_for_gsi_interface);
    set_get(Qgsi_interface,Qmanually_enable,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_enable),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qmanually_enable,temp_1,Qclasses_which_define);
    Qnote_ancestor_manually_enabled_for_gsi_interface = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED-FOR-GSI-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_gsi_interface,
	    STATIC_FUNCTION(note_ancestor_manually_enabled_for_gsi_interface,
	    NIL,FALSE,1,1));
    Qnote_ancestor_manually_enabled = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED",AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qnote_ancestor_manually_enabled_for_gsi_interface);
    set_get(Qgsi_interface,Qnote_ancestor_manually_enabled,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_ancestor_manually_enabled),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qnote_ancestor_manually_enabled,temp_1,
	    Qclasses_which_define);
    if (Maintaining_gsi_interface_status_changed_p == UNBOUND)
	Maintaining_gsi_interface_status_changed_p = Nil;
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_55 = 
	    STATIC_STRING("GSI interface ~NF has invalid status ~a");
    Qgsi_interface_is_secure = STATIC_SYMBOL("GSI-INTERFACE-IS-SECURE",
	    AB_package);
    if (Gsi_connection_checkup_interval_in_ms == UNBOUND)
	Gsi_connection_checkup_interval_in_ms = FIX((SI_Long)100L);
    string_constant_56 = 
	    STATIC_STRING("You must specify the identifying attributes for GSI interface ~NF.");
    Qgsi_interface_activate_after_shutdown = 
	    STATIC_SYMBOL("GSI-INTERFACE-ACTIVATE-AFTER-SHUTDOWN",AB_package);
    Qgsi_connection_configuration = 
	    STATIC_SYMBOL("GSI-CONNECTION-CONFIGURATION",AB_package);
    Qgsi_application_name = STATIC_SYMBOL("GSI-APPLICATION-NAME",AB_package);
    Qinterface_initialization_timeout_period = 
	    STATIC_SYMBOL("INTERFACE-INITIALIZATION-TIMEOUT-PERIOD",
	    AB_package);
    string_constant_57 = 
	    STATIC_STRING("Cannot make ICP connection for GSI data interface ~NF");
    Qrequested = STATIC_SYMBOL("REQUESTED",AB_package);
    Qhandle_gsi_connect_attempt_failure = 
	    STATIC_SYMBOL("HANDLE-GSI-CONNECT-ATTEMPT-FAILURE",AB_package);
    Qgsi_sensor_groups_header = STATIC_SYMBOL("GSI-SENSOR-GROUPS-HEADER",
	    AB_package);
    Qgsi_interface_structure = STATIC_SYMBOL("GSI-INTERFACE-STRUCTURE",
	    AB_package);
    Qfinalize_gsi_connection_1 = STATIC_SYMBOL("FINALIZE-GSI-CONNECTION-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfinalize_gsi_connection_1,
	    STATIC_FUNCTION(finalize_gsi_connection_1,NIL,FALSE,1,1));
    Qhandle_gsi_shut_down_connection = 
	    STATIC_SYMBOL("HANDLE-GSI-SHUT-DOWN-CONNECTION",AB_package);
    string_constant_58 = 
	    STATIC_STRING("GSI connection attempt failed for interface ~NF, error was ~a.");
    string_constant_59 = 
	    STATIC_STRING("GSI connection attempt failed for interface ~NF.");
    SET_SYMBOL_FUNCTION(Qhandle_gsi_connect_attempt_failure,
	    STATIC_FUNCTION(handle_gsi_connect_attempt_failure,NIL,FALSE,2,2));
    Qeof_awaiting_shutdown_acknowledgement = 
	    STATIC_SYMBOL("EOF-AWAITING-SHUTDOWN-ACKNOWLEDGEMENT",AB_package);
    string_constant_60 = 
	    STATIC_STRING("GSI connection lost for interface ~NF, error was ~a.");
    SET_SYMBOL_FUNCTION(Qhandle_gsi_shut_down_connection,
	    STATIC_FUNCTION(handle_gsi_shut_down_connection,NIL,FALSE,2,2));
    Qdeactivated_while_attempting_connection = 
	    STATIC_SYMBOL("DEACTIVATED-WHILE-ATTEMPTING-CONNECTION",
	    AB_package);
    Qdeactivate_for_gsi_interface = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_gsi_interface,
	    STATIC_FUNCTION(deactivate_for_gsi_interface,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_gsi_interface);
    set_get(Qgsi_interface,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qmanually_disable_for_gsi_interface = 
	    STATIC_SYMBOL("MANUALLY-DISABLE-FOR-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_disable_for_gsi_interface,
	    STATIC_FUNCTION(manually_disable_for_gsi_interface,NIL,FALSE,1,1));
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qmanually_disable_for_gsi_interface);
    set_get(Qgsi_interface,Qmanually_disable,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_disable),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qmanually_disable,temp_1,Qclasses_which_define);
    Qnote_ancestor_not_activatable_for_gsi_interface = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-NOT-ACTIVATABLE-FOR-GSI-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_ancestor_not_activatable_for_gsi_interface,
	    STATIC_FUNCTION(note_ancestor_not_activatable_for_gsi_interface,
	    NIL,FALSE,1,1));
    Qnote_ancestor_not_activatable = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-NOT-ACTIVATABLE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qnote_ancestor_not_activatable_for_gsi_interface);
    set_get(Qgsi_interface,Qnote_ancestor_not_activatable,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_ancestor_not_activatable),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qnote_ancestor_not_activatable,temp_1,
	    Qclasses_which_define);
    Qactivate_if_possible_and_propagate_for_gsi_interface = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE-FOR-GSI-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_gsi_interface,
	    STATIC_FUNCTION(activate_if_possible_and_propagate_for_gsi_interface,
	    NIL,FALSE,1,1));
    Qactivate_if_possible_and_propagate = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE",AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qactivate_if_possible_and_propagate_for_gsi_interface);
    set_get(Qgsi_interface,Qactivate_if_possible_and_propagate,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_if_possible_and_propagate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qactivate_if_possible_and_propagate,temp_1,
	    Qclasses_which_define);
    Qcleanup_for_gsi_interface = STATIC_SYMBOL("CLEANUP-FOR-GSI-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_gsi_interface,
	    STATIC_FUNCTION(cleanup_for_gsi_interface,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcleanup_for_gsi_interface);
    set_get(Qgsi_interface,Qcleanup,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qcleanup,temp_1,Qclasses_which_define);
    Qput_gsi_connection_configuration = 
	    STATIC_SYMBOL("PUT-GSI-CONNECTION-CONFIGURATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gsi_connection_configuration,
	    STATIC_FUNCTION(put_gsi_connection_configuration,NIL,FALSE,3,3));
    mutate_global_property(Qgsi_connection_configuration,
	    SYMBOL_FUNCTION(Qput_gsi_connection_configuration),Qslot_putter);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    list_constant_14 = STATIC_CONS(Qany,list_constant_72);
    Qhandle_update_to_sensor_attribute = 
	    STATIC_SYMBOL("HANDLE-UPDATE-TO-SENSOR-ATTRIBUTE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_update_to_sensor_attribute,
	    STATIC_FUNCTION(handle_update_to_sensor_attribute,NIL,FALSE,6,6));
    Qput_identifying_attributes = 
	    STATIC_SYMBOL("PUT-IDENTIFYING-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_identifying_attributes,
	    STATIC_FUNCTION(put_identifying_attributes,NIL,FALSE,3,3));
    mutate_global_property(Qidentifying_attributes,
	    SYMBOL_FUNCTION(Qput_identifying_attributes),Qslot_putter);
    Qput_grouping_specification = 
	    STATIC_SYMBOL("PUT-GROUPING-SPECIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_grouping_specification,
	    STATIC_FUNCTION(put_grouping_specification,NIL,FALSE,3,3));
    mutate_global_property(Qgrouping_specification,
	    SYMBOL_FUNCTION(Qput_grouping_specification),Qslot_putter);
    Qput_gsi_interface_status = STATIC_SYMBOL("PUT-GSI-INTERFACE-STATUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gsi_interface_status,
	    STATIC_FUNCTION(put_gsi_interface_status,NIL,FALSE,3,3));
    mutate_global_property(Qgsi_interface_status,
	    SYMBOL_FUNCTION(Qput_gsi_interface_status),Qslot_putter);
    Qdata_server_spec = STATIC_SYMBOL("DATA-SERVER-SPEC",AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qquote,Qgsi);
    Qdata = STATIC_SYMBOL("DATA",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qquote,Qdata);
    Qserver = STATIC_SYMBOL("SERVER",AB_package);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qquote,Qserver);
    list_constant_82 = STATIC_LIST((SI_Long)3L,list_constant_79,
	    list_constant_80,list_constant_81);
    list_constant_83 = STATIC_LIST((SI_Long)2L,list_constant_82,
	    Qgsi_data_server);
    list_constant_84 = STATIC_CONS(Qdata_server_spec,list_constant_83);
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    list_constant_85 = STATIC_CONS(Qdata_server_map,list_constant_83);
    list_constant_86 = STATIC_LIST((SI_Long)2L,list_constant_84,
	    list_constant_85);
    add_grammar_rules_function(list_constant_86);
    Qactivate_for_gsi_data_service = 
	    STATIC_SYMBOL("ACTIVATE-FOR-GSI-DATA-SERVICE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_gsi_data_service,
	    STATIC_FUNCTION(activate_for_gsi_data_service,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_gsi_data_service);
    set_get(Qgsi_data_service,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_data_service,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    Qdeactivate_for_gsi_data_service = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-GSI-DATA-SERVICE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_gsi_data_service,
	    STATIC_FUNCTION(deactivate_for_gsi_data_service,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_gsi_data_service);
    set_get(Qgsi_data_service,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_data_service,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qactivate_for_gsi_message_service = 
	    STATIC_SYMBOL("ACTIVATE-FOR-GSI-MESSAGE-SERVICE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_gsi_message_service,
	    STATIC_FUNCTION(activate_for_gsi_message_service,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_gsi_message_service);
    set_get(Qgsi_message_service,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_message_service,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    Qdeactivate_for_gsi_message_service = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-GSI-MESSAGE-SERVICE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_gsi_message_service,
	    STATIC_FUNCTION(deactivate_for_gsi_message_service,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_gsi_message_service);
    set_get(Qgsi_message_service,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_message_service,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qput_gsi_interface_name = STATIC_SYMBOL("PUT-GSI-INTERFACE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gsi_interface_name,
	    STATIC_FUNCTION(put_gsi_interface_name,NIL,FALSE,3,3));
    mutate_global_property(Qgsi_interface_name,
	    SYMBOL_FUNCTION(Qput_gsi_interface_name),Qslot_putter);
    Qcompile_gsi_interface_name_for_slot = 
	    STATIC_SYMBOL("COMPILE-GSI-INTERFACE-NAME-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_gsi_interface_name_for_slot,
	    STATIC_FUNCTION(compile_gsi_interface_name_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qgsi_interface_name,
	    SYMBOL_FUNCTION(Qcompile_gsi_interface_name_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qgsi_interface_name,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qgsi_collect_one_shot_data = STATIC_SYMBOL("GSI-COLLECT-ONE-SHOT-DATA",
	    AB_package);
    Qgsi_begin_collecting_data = STATIC_SYMBOL("GSI-BEGIN-COLLECTING-DATA",
	    AB_package);
    Qgsi_stop_collecting_data = STATIC_SYMBOL("GSI-STOP-COLLECTING-DATA",
	    AB_package);
    Qgsi_process_gsi_interfaces = 
	    STATIC_SYMBOL("GSI-PROCESS-GSI-INTERFACES",AB_package);
    Qgsi_initialize_data_server = 
	    STATIC_SYMBOL("GSI-INITIALIZE-DATA-SERVER",AB_package);
    Qgsi_set_external_variable = STATIC_SYMBOL("GSI-SET-EXTERNAL-VARIABLE",
	    AB_package);
    Qgsi_shut_down_data_server_qm = 
	    STATIC_SYMBOL("GSI-SHUT-DOWN-DATA-SERVER\?",AB_package);
    Qgsi_deliver_messages = STATIC_SYMBOL("GSI-DELIVER-MESSAGES",AB_package);
    SET_SYMBOL_FUNCTION(Qgsi_deliver_messages,
	    STATIC_FUNCTION(gsi_deliver_messages,NIL,FALSE,5,5));
    Qgsi_pause_data_server_qm = STATIC_SYMBOL("GSI-PAUSE-DATA-SERVER\?",
	    AB_package);
    Qgsi_resume_data_server_qm = STATIC_SYMBOL("GSI-RESUME-DATA-SERVER\?",
	    AB_package);
    Qgsi_requests_accept_data_calls_p = 
	    STATIC_SYMBOL("GSI-REQUESTS-ACCEPT-DATA-CALLS-P",AB_package);
    Qgsi_start_data_server_qm = STATIC_SYMBOL("GSI-START-DATA-SERVER\?",
	    AB_package);
    Qgsi_reset_data_server_qm = STATIC_SYMBOL("GSI-RESET-DATA-SERVER\?",
	    AB_package);
    def_data_server(15,Qgsi_data_server,Qgsi_collect_one_shot_data,
	    Qgsi_begin_collecting_data,Qgsi_stop_collecting_data,
	    Qgsi_process_gsi_interfaces,T,Qgsi_initialize_data_server,
	    Qgsi_set_external_variable,Qgsi_shut_down_data_server_qm,
	    Qgsi_deliver_messages,Qgsi_pause_data_server_qm,
	    Qgsi_resume_data_server_qm,Qgsi_requests_accept_data_calls_p,
	    Qgsi_start_data_server_qm,Qgsi_reset_data_server_qm);
    Qpoll_external_system_for_data = 
	    STATIC_SYMBOL("POLL-EXTERNAL-SYSTEM-FOR-DATA",AB_package);
    string_constant_61 = STATIC_STRING("GSI interface ~NF has timed out.");
    SET_SYMBOL_FUNCTION(Qgsi_process_gsi_interfaces,
	    STATIC_FUNCTION(gsi_process_gsi_interfaces,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_pause_data_server_qm,
	    STATIC_FUNCTION(gsi_pause_data_server_qm,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_resume_data_server_qm,
	    STATIC_FUNCTION(gsi_resume_data_server_qm,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_start_data_server_qm,
	    STATIC_FUNCTION(gsi_start_data_server_qm,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_reset_data_server_qm,
	    STATIC_FUNCTION(gsi_reset_data_server_qm,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_shut_down_data_server_qm,
	    STATIC_FUNCTION(gsi_shut_down_data_server_qm,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_requests_accept_data_calls_p,
	    STATIC_FUNCTION(gsi_requests_accept_data_calls_p,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgsi_initialize_data_server,
	    STATIC_FUNCTION(gsi_initialize_data_server,NIL,FALSE,0,0));
    string_constant_62 = STATIC_STRING("Sensor ~NF is not configured for GSI");
    SET_SYMBOL_FUNCTION(Qgsi_collect_one_shot_data,
	    STATIC_FUNCTION(gsi_collect_one_shot_data,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qgsi_set_external_variable,
	    STATIC_FUNCTION(gsi_set_external_variable,NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qgsi_begin_collecting_data,
	    STATIC_FUNCTION(gsi_begin_collecting_data,NIL,FALSE,2,2));
    string_constant_63 = 
	    STATIC_STRING("The GSI data server could not set a value ~\n                       for variable ~NF because ~a does not exist.");
    string_constant_64 = 
	    STATIC_STRING("The GSI data server could not set a value ~\n                       for variable ~NF because no GSI interface was specified.");
    string_constant_65 = STATIC_STRING("No GSI interface for sensor ~NF");
    Qenqueue_gsi_request_for_sensor = 
	    STATIC_SYMBOL("ENQUEUE-GSI-REQUEST-FOR-SENSOR",AB_package);
    string_constant_66 = 
	    STATIC_STRING("The GSI data server could not set a value for variable ~NF ~\n                   because ~NF is not active.");
    string_constant_67 = 
	    STATIC_STRING("The GSI data server could not set a value for variable ~NF ~\n                 because ~NF failed to make an ICP connection.");
    string_constant_68 = 
	    STATIC_STRING("The GSI data server ~\n                     could not set a value for variable ~NF ~\n                     because ~NF is not connected.");
    string_constant_69 = 
	    STATIC_STRING("The GSI data server could not set a value for variable ~NF ~\n              because the ICP connection for ~NF has timed out.");
    Qprocess_requests_for_gsi_interfaces = 
	    STATIC_SYMBOL("PROCESS-REQUESTS-FOR-GSI-INTERFACES",AB_package);
    SET_SYMBOL_FUNCTION(Qenqueue_gsi_request_for_sensor,
	    STATIC_FUNCTION(enqueue_gsi_request_for_sensor,NIL,FALSE,3,3));
    string_constant_70 = 
	    STATIC_STRING("GSI interface not active for sensor ~NF");
    SET_SYMBOL_FUNCTION(Qgsi_stop_collecting_data,
	    STATIC_FUNCTION(gsi_stop_collecting_data,NIL,FALSE,1,1));
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qnote_name_change_for_gsi_interface = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_gsi_interface,
	    STATIC_FUNCTION(note_name_change_for_gsi_interface,NIL,FALSE,3,3));
    temp_1 = SYMBOL_FUNCTION(Qnote_name_change_for_gsi_interface);
    set_get(Qgsi_interface,Qnote_name_change,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp_1 = CONS(Qgsi_interface,temp);
    mutate_global_property(Qnote_name_change,temp_1,Qclasses_which_define);
    SET_SYMBOL_FUNCTION(Qprocess_requests_for_gsi_interfaces,
	    STATIC_FUNCTION(process_requests_for_gsi_interfaces,NIL,FALSE,
	    0,0));
    string_constant_71 = 
	    string_append2(STATIC_STRING("The value for identifying attribute ~A ~\n                      of GSI item ~NF ~\n                      is neither a constant value nor a parameter ~\n                      and "),
	    STATIC_STRING("will be ignored."));
    Qset_values_for_sensors = STATIC_SYMBOL("SET-VALUES-FOR-SENSORS",
	    AB_package);
    Qget_values_for_sensors = STATIC_SYMBOL("GET-VALUES-FOR-SENSORS",
	    AB_package);
    Qwrite_user_message_string = STATIC_SYMBOL("WRITE-USER-MESSAGE-STRING",
	    AB_package);
    Qstop_sending_values_for_sensors = 
	    STATIC_SYMBOL("STOP-SENDING-VALUES-FOR-SENSORS",AB_package);
}
