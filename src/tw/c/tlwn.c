/* tlwn.c
 * Input file:  telewindows.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "tlwn.h"


Object Default_tw_tcp_connect_interval_in_ms = UNBOUND;

Object Default_g2_tcp_port = UNBOUND;

Object Default_g2_tcp_port_text_string = UNBOUND;

Object The_type_description_of_telewindows_workstation = UNBOUND;

Object Chain_of_available_telewindows_workstations = UNBOUND;

Object Telewindows_workstation_count = UNBOUND;

/* TELEWINDOWS-WORKSTATION-STRUCTURE-MEMORY-USAGE */
Object telewindows_workstation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(76,0);
    temp = Telewindows_workstation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)81L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TELEWINDOWS-WORKSTATION-COUNT */
Object outstanding_telewindows_workstation_count()
{
    Object def_structure_telewindows_workstation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(76,1);
    gensymed_symbol = IFIX(Telewindows_workstation_count);
    def_structure_telewindows_workstation_variable = 
	    Chain_of_available_telewindows_workstations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_telewindows_workstation_variable))
	goto end_loop;
    def_structure_telewindows_workstation_variable = 
	    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end;
    gensymed_symbol_1 = IFIX(Qnil);
  end:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TELEWINDOWS-WORKSTATION-1 */
Object reclaim_telewindows_workstation_1(telewindows_workstation)
    Object telewindows_workstation;
{
    Object old_structure_being_reclaimed, thing, schedule_task_qm;
    Object old_structure_being_reclaimed_1, svref_new_value;

    x_note_fn_call(76,2);
    inline_note_reclaim_cons(telewindows_workstation,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = telewindows_workstation;
    reclaim_window_for_workstation(ISVREF(telewindows_workstation,
	    (SI_Long)1L));
    SVREF(telewindows_workstation,FIX((SI_Long)1L)) = Nil;
    reclaim_workstation_event_queue_if_g2(ISVREF(telewindows_workstation,
	    (SI_Long)2L));
    SVREF(telewindows_workstation,FIX((SI_Long)2L)) = Nil;
    reclaim_mouse_pointers_if_g2(ISVREF(telewindows_workstation,(SI_Long)14L));
    SVREF(telewindows_workstation,FIX((SI_Long)14L)) = Nil;
    reclaim_mouse_pointers_if_g2(ISVREF(telewindows_workstation,(SI_Long)15L));
    SVREF(telewindows_workstation,FIX((SI_Long)15L)) = Nil;
    reclaim_workstation_context_stack_if_g2(ISVREF(telewindows_workstation,
	    (SI_Long)17L));
    SVREF(telewindows_workstation,FIX((SI_Long)17L)) = Nil;
    reclaim_if_managed_float(ISVREF(telewindows_workstation,(SI_Long)24L));
    SVREF(telewindows_workstation,FIX((SI_Long)24L)) = Nil;
    thing = ISVREF(telewindows_workstation,(SI_Long)26L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    SVREF(telewindows_workstation,FIX((SI_Long)26L)) = Nil;
    reclaim_non_kb_workspaces_for_this_workstation_only_if_g2(ISVREF(telewindows_workstation,
	    (SI_Long)32L));
    SVREF(telewindows_workstation,FIX((SI_Long)32L)) = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(telewindows_workstation,
	    (SI_Long)33L));
    SVREF(telewindows_workstation,FIX((SI_Long)33L)) = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(telewindows_workstation,
	    (SI_Long)34L));
    SVREF(telewindows_workstation,FIX((SI_Long)34L)) = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(telewindows_workstation,
	    (SI_Long)35L));
    SVREF(telewindows_workstation,FIX((SI_Long)35L)) = Nil;
    thing = ISVREF(telewindows_workstation,(SI_Long)38L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    SVREF(telewindows_workstation,FIX((SI_Long)38L)) = Nil;
    thing = ISVREF(telewindows_workstation,(SI_Long)39L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    SVREF(telewindows_workstation,FIX((SI_Long)39L)) = Nil;
    reclaim_block_near_mouse_cache_function(ISVREF(telewindows_workstation,
	    (SI_Long)42L));
    SVREF(telewindows_workstation,FIX((SI_Long)42L)) = Nil;
    schedule_task_qm = ISVREF(telewindows_workstation,(SI_Long)80L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = Structure_being_reclaimed;
	Structure_being_reclaimed = schedule_task_qm;
	reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = Chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(telewindows_workstation,FIX((SI_Long)80L)) = svref_new_value;
    SVREF(telewindows_workstation,FIX((SI_Long)80L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_telewindows_workstations;
    SVREF(telewindows_workstation,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_telewindows_workstations = telewindows_workstation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TELEWINDOWS-WORKSTATION */
Object reclaim_structure_for_telewindows_workstation(telewindows_workstation)
    Object telewindows_workstation;
{
    x_note_fn_call(76,3);
    return reclaim_telewindows_workstation_1(telewindows_workstation);
}

static Object Qg2_defstruct_structure_name_telewindows_workstation_g2_struct;  /* g2-defstruct-structure-name::telewindows-workstation-g2-struct */

/* MAKE-PERMANENT-TELEWINDOWS-WORKSTATION-STRUCTURE-INTERNAL */
Object make_permanent_telewindows_workstation_structure_internal()
{
    Object def_structure_telewindows_workstation_variable, temp;
    Object defstruct_g2_telewindows_workstation_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(76,4);
    def_structure_telewindows_workstation_variable = Nil;
    temp = FIXNUM_ADD1(Telewindows_workstation_count);
    Telewindows_workstation_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_telewindows_workstation_variable = Nil;
	gensymed_symbol_1 = (SI_Long)81L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_telewindows_workstation_variable = the_array;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_telewindows_workstation_g2_struct;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)21L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)22L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)23L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)24L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)25L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)26L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)27L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)28L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)29L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)30L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)31L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)32L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)33L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)34L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)35L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)36L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)37L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)38L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)39L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)40L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)41L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)42L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)43L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)44L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)45L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)46L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)47L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)48L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)49L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)50L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)51L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)52L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)53L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)54L)) = Nil;
	SVREF(defstruct_g2_telewindows_workstation_variable,
		FIX((SI_Long)55L)) = Nil;
	def_structure_telewindows_workstation_variable = 
		defstruct_g2_telewindows_workstation_variable;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)54L)) = Nil;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)55L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = Chain_of_available_telewindows_workstations;
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)0L)) = temp;
	Chain_of_available_telewindows_workstations = 
		def_structure_telewindows_workstation_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_telewindows_workstation_variable);
}

static Object Qnone;               /* none */

static Object Qg2_window;          /* g2-window */

static Object Qlogged_out;         /* logged-out */

static Object string_constant;     /* "localhost" */

static Object string_constant_1;   /* "TCP-IP" */

static Object Qdisconnected;       /* disconnected */

/* MAKE-TELEWINDOWS-WORKSTATION-1 */
Object make_telewindows_workstation_1(window_for_workstation)
    Object window_for_workstation;
{
    Object def_structure_telewindows_workstation_variable, temp;

    x_note_fn_call(76,5);
    def_structure_telewindows_workstation_variable = 
	    Chain_of_available_telewindows_workstations;
    if (def_structure_telewindows_workstation_variable) {
	Chain_of_available_telewindows_workstations = 
		ISVREF(def_structure_telewindows_workstation_variable,
		(SI_Long)0L);
	SVREF(def_structure_telewindows_workstation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_telewindows_workstation_g2_struct;
    }
    else
	def_structure_telewindows_workstation_variable = 
		make_permanent_telewindows_workstation_structure_internal();
    inline_note_allocate_cons(def_structure_telewindows_workstation_variable,
	    Nil);
    SVREF(def_structure_telewindows_workstation_variable,FIX((SI_Long)1L)) 
	    = window_for_workstation;
    temp = make_queue();
    SVREF(def_structure_telewindows_workstation_variable,FIX((SI_Long)2L)) 
	    = temp;
    SVREF(def_structure_telewindows_workstation_variable,FIX((SI_Long)3L)) 
	    = Nil;
    SVREF(def_structure_telewindows_workstation_variable,FIX((SI_Long)4L)) 
	    = Nil;
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)10L)) = Qnone;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)15L)) = Nil;
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)16L) = 
	    FIX((SI_Long)2L);
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)23L)) = Qg2_window;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)25L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)28L)) = Qlogged_out;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)29L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)33L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)36L)) = Nil;
    temp = add1(Last_session_id_for_g2);
    Last_session_id_for_g2 = temp;
    temp = Last_session_id_for_g2;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)37L)) = temp;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)38L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)41L)) = Nil;
    temp = make_block_near_mouse_cache();
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)42L)) = temp;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)43L)) = Nil;
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)44L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)46L)) = T;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)48L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)49L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)50L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)51L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)56L)) = string_constant;
    temp = Default_g2_tcp_port;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)57L)) = temp;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)58L)) = string_constant_1;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)59L)) = Nil;
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)60L) = 
	    FIX((SI_Long)10000L);
    ISVREF(def_structure_telewindows_workstation_variable,(SI_Long)61L) = 
	    FIX((SI_Long)40L);
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)62L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)63L)) = Qdisconnected;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)64L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)65L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)69L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)70L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)71L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)72L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)73L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)74L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)75L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)76L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)77L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)78L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)79L)) = Nil;
    SVREF(def_structure_telewindows_workstation_variable,
	    FIX((SI_Long)80L)) = Nil;
    return VALUES_1(def_structure_telewindows_workstation_variable);
}

/* TELEWINDOWS-ICP-SOCKET?-FUNCTION */
Object telewindows_icp_socket_qm_function(telewindows_workstation)
    Object telewindows_workstation;
{
    Object temp;

    x_note_fn_call(76,6);
    temp = ISVREF(telewindows_workstation,(SI_Long)62L);
    return VALUES_1(temp);
}

/* RECLAIM-TELEWINDOWS-WORKSTATION-FUNCTION */
Object reclaim_telewindows_workstation_function(telewindows_workstation)
    Object telewindows_workstation;
{
    x_note_fn_call(76,7);
    return reclaim_telewindows_workstation_1(telewindows_workstation);
}

/* GET-WORKSTATION-FOR-ICP-SOCKET */
Object get_workstation_for_icp_socket(icp_socket)
    Object icp_socket;
{
    Object workstation, ab_loop_list_;

    x_note_fn_call(76,8);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(workstation,(SI_Long)62L),icp_socket))
	return VALUES_1(workstation);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Minimum_telewindows_splashscreen_time_in_seconds = UNBOUND;

Object Maximum_telewindows_splashscreen_time_in_seconds = UNBOUND;

Object Default_telewindows_splashscreen_time_in_seconds = UNBOUND;

Object User_specified_telewindows_splashscreen_time_in_seconds_qm = UNBOUND;

static Object Qsplashtime;         /* splashtime */

/* INITIALIZE-USER-SPECIFIED-TELEWINDOWS-SPLASHSCREEN-TIME-IN-SECONDS? */
Object initialize_user_specified_telewindows_splashscreen_time_in_seconds_qm()
{
    x_note_fn_call(76,9);
    return getf(Command_line_arguments,Qsplashtime,_);
}

/* GET-TELEWINDOWS-SPLASHSCREEN-TIME-AS-FIXNUM-TIME-INTERVAL */
Object get_telewindows_splashscreen_time_as_fixnum_time_interval()
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(76,10);
    gensymed_symbol = IFIX(Fixnum_time_interval_for_one_second);
    if (User_specified_telewindows_splashscreen_time_in_seconds_qm)
	gensymed_symbol_1 = 
		IFIX(User_specified_telewindows_splashscreen_time_in_seconds_qm);
    else if (telewindows_multiwindow_ui_p() && telewindows_win32_window_p())
	gensymed_symbol_1 = (SI_Long)0L;
    else
	gensymed_symbol_1 = 
		IFIX(Default_telewindows_splashscreen_time_in_seconds);
    return VALUES_1(FIX(gensymed_symbol * gensymed_symbol_1));
}

/* COMMAND-LINE-PROCESS-REMOTE-HOST-NAME */
Object command_line_process_remote_host_name(host_arg_qm)
    Object host_arg_qm;
{
    SI_Long i, ab_loop_bind_;
    char temp;

    x_note_fn_call(76,11);
    if (host_arg_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(text_string_length(host_arg_qm));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if ( 
		!TRUEP(simple_symbol_character_p(FIX(UBYTE_16_ISAREF_1(host_arg_qm,
		i))))) {
	    temp = TRUEP(Nil);
	    goto end;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end;
	temp = TRUEP(Qnil);
      end:;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(host_arg_qm);
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qremote_host_name;   /* remote-host-name */

static Object Qcommand_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-REMOTE-HOST-NAME */
Object get_command_line_plist_element_for_remote_host_name()
{
    Object gensymed_symbol, host_arg_qm, temp;

    x_note_fn_call(76,12);
    gensymed_symbol = 
	    get_gensym_command_line_argument_as_text_string(FIX((SI_Long)1L));
    if (Used_positional_command_line_argument_default ||  
	    !TRUEP(gensymed_symbol) || 
		command_line_keyword_p(gensymed_symbol)) {
	Used_positional_command_line_argument_default = T;
	host_arg_qm = array_constant;
    }
    else
	host_arg_qm = gensymed_symbol;
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qremote_host_name),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,host_arg_qm);
}

/* COMMAND-LINE-PROCESS-REMOTE-PORT-NAME-OR-NUMBER */
Object command_line_process_remote_port_name_or_number(arg_qm)
    Object arg_qm;
{
    Object node_candidate_qm;
    SI_Long i, ab_loop_bind_, gensymed_symbol;
    char temp;

    x_note_fn_call(76,13);
    if (arg_qm) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(text_string_length(arg_qm));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = UBYTE_16_ISAREF_1(arg_qm,i);
	if ( !((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) :
		 TRUEP(Nil))) {
	    temp = TRUEP(Nil);
	    goto end;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end;
	temp = TRUEP(Qnil);
      end:;
	if (temp) {
	    node_candidate_qm = read_fixnum_from_string(1,arg_qm);
	    if (FIXNUMP(node_candidate_qm))
		return VALUES_1(node_candidate_qm);
	    else
		return VALUES_1(Nil);
	}
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(text_string_length(arg_qm));
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    if ( 
		    !TRUEP(simple_symbol_character_p(FIX(UBYTE_16_ISAREF_1(arg_qm,
		    i))))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp)
		return VALUES_1(arg_qm);
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object Qremote_port_name_or_number;  /* remote-port-name-or-number */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-REMOTE-PORT-NAME-OR-NUMBER */
Object get_command_line_plist_element_for_remote_port_name_or_number()
{
    Object gensymed_symbol, arg_qm, temp;

    x_note_fn_call(76,14);
    gensymed_symbol = 
	    get_gensym_command_line_argument_as_text_string(FIX((SI_Long)2L));
    if (Used_positional_command_line_argument_default ||  
	    !TRUEP(gensymed_symbol) || 
		command_line_keyword_p(gensymed_symbol)) {
	Used_positional_command_line_argument_default = T;
	arg_qm = array_constant_1;
    }
    else
	arg_qm = gensymed_symbol;
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qremote_port_name_or_number),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object string_constant_2;   /* "~%DECNet no longer supported." */

/* COMMAND-LINE-PROCESS-NETWORK */
Object command_line_process_network(value_qm)
    Object value_qm;
{
    x_note_fn_call(76,15);
    if (value_qm) {
	if (string_equalw(value_qm,array_constant_2))
	    return VALUES_1(array_constant_3);
	else if (string_equalw(value_qm,array_constant_4))
	    return notify_user_at_console(2,string_constant_2,Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object Qnetwork;            /* network */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETWORK */
Object get_command_line_plist_element_for_network()
{
    Object value_qm, temp;

    x_note_fn_call(76,16);
    value_qm = get_command_line_keyword_argument(1,array_constant_5);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnetwork),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

static Object string_constant_3;   /* "~%Bad TCP timeout argument: ~s should be an integer." */

static Object string_constant_4;   /* "~%Cannot use negative TCP timeout (~d). The default of ~
				    *            ~d ms will be used instead.~%"
				    */

/* COMMAND-LINE-PROCESS-TCPTIMEOUT */
Object command_line_process_tcptimeout(value_qm)
    Object value_qm;
{
    Object integer_qm;

    x_note_fn_call(76,17);
    if (value_qm) {
	integer_qm = read_fixnum_from_string(1,value_qm);
	if (integer_qm);
	else
	    integer_qm = notify_user_at_console(2,string_constant_3,value_qm);
    }
    else
	integer_qm = Nil;
    if (integer_qm) {
	if (IFIX(integer_qm) < (SI_Long)0L) {
	    notify_user_at_console(3,string_constant_4,integer_qm,
		    Default_tw_tcp_connect_interval_in_ms);
	    integer_qm = Default_tw_tcp_connect_interval_in_ms;
	}
	return VALUES_1(integer_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_6;    /* # */

static Object Qtcptimeout;         /* tcptimeout */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-TCPTIMEOUT */
Object get_command_line_plist_element_for_tcptimeout()
{
    Object value_qm, temp;

    x_note_fn_call(76,18);
    value_qm = get_command_line_keyword_argument(1,array_constant_6);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtcptimeout),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

static Object string_constant_5;   /* "~%Bad -spashtime argument: ~s should be an integer." */

/* COMMAND-LINE-PROCESS-SPLASHTIME */
Object command_line_process_splashtime(value_qm)
    Object value_qm;
{
    Object integer_qm;

    x_note_fn_call(76,19);
    if (value_qm) {
	integer_qm = read_fixnum_from_string(1,value_qm);
	if (integer_qm);
	else
	    integer_qm = notify_user_at_console(2,string_constant_5,value_qm);
    }
    else
	integer_qm = Nil;
    if (integer_qm) {
	if (FIXNUM_LT(integer_qm,
		Minimum_telewindows_splashscreen_time_in_seconds))
	    integer_qm = Minimum_telewindows_splashscreen_time_in_seconds;
	else if (FIXNUM_GT(integer_qm,
		Maximum_telewindows_splashscreen_time_in_seconds))
	    integer_qm = Maximum_telewindows_splashscreen_time_in_seconds;
	return VALUES_1(integer_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SPLASHTIME */
Object get_command_line_plist_element_for_splashtime()
{
    Object value_qm, temp;

    x_note_fn_call(76,20);
    value_qm = get_command_line_keyword_argument(1,array_constant_7);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsplashtime),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,value_qm);
}

/* COMMAND-LINE-PROCESS-WORKSPACE */
Object command_line_process_workspace(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(76,21);
    return VALUES_1(arg_qm);
}

static Object array_constant_8;    /* # */

static Object Qworkspace;          /* workspace */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WORKSPACE */
Object get_command_line_plist_element_for_workspace()
{
    Object arg_qm, temp;

    x_note_fn_call(76,22);
    arg_qm = get_command_line_keyword_argument(1,array_constant_8);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qworkspace),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-WORKSPACE-UUID */
Object command_line_process_workspace_uuid(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(76,23);
    return VALUES_1(arg_qm);
}

static Object array_constant_9;    /* # */

static Object Qworkspace_uuid;     /* workspace-uuid */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WORKSPACE-UUID */
Object get_command_line_plist_element_for_workspace_uuid()
{
    Object arg_qm, temp;

    x_note_fn_call(76,24);
    arg_qm = get_command_line_keyword_argument(1,array_constant_9);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qworkspace_uuid),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

Object Telewindows_session_id = UNBOUND;

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* MAKE-TELEWINDOWS-SESSION-ID */
Object make_telewindows_session_id()
{
    Object uuid, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(76,25);
    uuid = make_uuid();
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_uuid_printed_representation(uuid);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_wide_string(uuid);
    return VALUES_1(temp);
}

Object Telewindows_name_for_unknown_host = UNBOUND;

static Object Qnetwork_host_name;  /* network-host-name */

static Object Qos_user_name;       /* os-user-name */

static Object Qos_type;            /* os-type */

static Object Qui_toolkit;         /* ui-toolkit */

static Object Qnative_icons_limit;  /* native-icons-limit */

static Object Qtelewindows_authorized_products;  /* telewindows-authorized-products */

static Object Qtelewindows_license_level;  /* telewindows-license-level */

static Object Qtelewindows_session_id;  /* telewindows-session-id */

/* GET-TELEWINDOWS-MISCELLANEOUS-INFO */
Object get_telewindows_miscellaneous_info()
{
    Object gensymed_symbol, gensymed_symbol_1, temp, car_new_value;
    SI_Long car_new_value_1;

    x_note_fn_call(76,26);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)16L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qnetwork_host_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = get_local_host_name();
    if (temp);
    else
	temp = Telewindows_name_for_unknown_host;
    car_new_value = copy_text_string(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qos_user_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = foreign_get_user_name();
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qos_type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = G2_operating_system;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qui_toolkit;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = get_local_ui_toolkit_name();
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qnative_icons_limit;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value_1 = g2ext_native_icons_limit();
    M_CAR(gensymed_symbol_1) = FIX(car_new_value_1);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtelewindows_authorized_products;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Telewindows_authorized_products;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtelewindows_license_level;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Telewindows_license_level;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtelewindows_session_id;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_text_string(Telewindows_session_id);
    M_CAR(gensymed_symbol_1) = car_new_value;
    return VALUES_1(gensymed_symbol);
}

static Object Qsilent;             /* silent */

static Object string_constant_6;   /* "[Telewindows: Unable to set TCP connect timeout interval.  ~
				    *            The default of ~d ms will be used instead.]"
				    */

static Object Qverbose;            /* verbose */

static Object string_constant_7;   /* "[Telewindows: Using TCP connect timeout interval of ~d ms]" */

/* SET-UP-TELEWINDOWS-CONNECTION-TIMEOUT */
Object set_up_telewindows_connection_timeout()
{
    Object user_specified_timeout_qm, svref_arg_1, svref_new_value;

    x_note_fn_call(76,27);
    if (normalized_string_equal(2,array_constant_3,
	    ISVREF(Current_workstation,(SI_Long)73L))) {
	user_specified_timeout_qm = getf(Command_line_arguments,Qtcptimeout,_);
	if (user_specified_timeout_qm) {
	    svref_arg_1 = Current_workstation;
	    SVREF(svref_arg_1,FIX((SI_Long)60L)) = user_specified_timeout_qm;
	}
	if ( !(g2ext_set_tcp_connect_retry(IFIX(ISVREF(Current_workstation,
		(SI_Long)60L))) == (SI_Long)1L)) {
	    if ( !EQ(Verbosity_level,Qsilent))
		notify_user_at_console(2,string_constant_6,
			Default_tw_tcp_connect_interval_in_ms);
	    svref_arg_1 = Current_workstation;
	    svref_new_value = Default_tw_tcp_connect_interval_in_ms;
	    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)60L)) = 
		    svref_new_value);
	}
	else if ( !FIXNUM_EQ(ISVREF(Current_workstation,(SI_Long)60L),
		Default_tw_tcp_connect_interval_in_ms) && 
		EQ(Verbosity_level,Qverbose))
	    return notify_user_at_console(2,string_constant_7,
		    ISVREF(Current_workstation,(SI_Long)60L));
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-MESSAGE-GROUP-FOR-PASTE-FROM-TELEWINDOWS-TO-G2 */
Object write_message_group_for_paste_from_telewindows_to_g2(gensym_window,
	    text_string,request_id)
    Object gensym_window, text_string, request_id;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(76,28);
    current_icp_port = ISVREF(gensym_window,(SI_Long)13L);
    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = T;
	disable_resumability = temp;
	PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_paste_from_telewindows_to_g2(gensym_window,
					text_string,request_id);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    result = VALUES_1(temp);
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

/* PASTE-FOR-TELEWINDOWS */
Object paste_for_telewindows(gensym_window,text_string,request_id)
    Object gensym_window, text_string, request_id;
{
    Object temp;

    x_note_fn_call(76,29);
    temp =  !TRUEP(ISVREF(gensym_window,(SI_Long)13L)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return write_message_group_for_paste_from_telewindows_to_g2(gensym_window,
		text_string,request_id);
}

/* WRITE-MESSAGE-GROUP-FOR-UPDATE-PASTE-AVAILABILITY-STATUS */
Object write_message_group_for_update_paste_availability_status(gensym_window,
	    status)
    Object gensym_window, status;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(76,30);
    current_icp_port = ISVREF(gensym_window,(SI_Long)13L);
    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = T;
	disable_resumability = temp;
	PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_update_paste_availability_status(gensym_window,
					status);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    result = VALUES_1(temp);
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

/* UPDATE-PASTE-AVAILABILITY-STATUS-FOR-TELEWINDOWS */
Object update_paste_availability_status_for_telewindows(gensym_window,status)
    Object gensym_window, status;
{
    Object temp, svref_arg_1;

    x_note_fn_call(76,31);
    temp =  !TRUEP(ISVREF(gensym_window,(SI_Long)13L)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	svref_arg_1 = ISVREF(gensym_window,(SI_Long)2L);
	SVREF(svref_arg_1,FIX((SI_Long)45L)) = status;
	return write_message_group_for_update_paste_availability_status(gensym_window,
		status);
    }
}

/* WRITE-MESSAGE-GROUP-FOR-REFRESH-TELEWINDOW */
Object write_message_group_for_refresh_telewindow(gensym_window,
	    left_edge_of_update_area_qm,top_edge_of_update_area_qm,
	    right_edge_of_update_area_qm,bottom_edge_of_update_area_qm)
    Object gensym_window, left_edge_of_update_area_qm;
    Object top_edge_of_update_area_qm, right_edge_of_update_area_qm;
    Object bottom_edge_of_update_area_qm;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, temp_2, temp_3;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(76,32);
    current_icp_port = ISVREF(gensym_window,(SI_Long)13L);
    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = T;
	disable_resumability = temp;
	PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp_1 = left_edge_of_update_area_qm;
				if (temp_1);
				else
				    temp_1 = FIX((SI_Long)0L);
				temp_2 = top_edge_of_update_area_qm;
				if (temp_2);
				else
				    temp_2 = FIX((SI_Long)0L);
				temp_3 = right_edge_of_update_area_qm;
				if (temp_3);
				else
				    temp_3 = FIX((SI_Long)0L);
				temp = bottom_edge_of_update_area_qm;
				if (temp);
				else
				    temp = FIX((SI_Long)0L);
				temp = 
					send_icp_request_to_refresh_window(gensym_window,
					Nil,left_edge_of_update_area_qm ? 
					T : Nil,temp_1,temp_2,temp_3,temp);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    result = VALUES_1(temp);
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

/* REFRESH-TELEWINDOW */
Object refresh_telewindow varargs_1(int, n)
{
    Object gensym_window, native_window;
    Object left_edge_of_update_area_qm, top_edge_of_update_area_qm;
    Object right_edge_of_update_area_qm, bottom_edge_of_update_area_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(76,33);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    native_window = REQUIRED_ARG_nonrelocating();
    left_edge_of_update_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    top_edge_of_update_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    right_edge_of_update_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    bottom_edge_of_update_area_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(gensym_window,(SI_Long)13L))) {
	if ( !TRUEP(telewindows_mdi_frame_p()))
	    return paint_telewindows_window_with_credits(gensym_window);
	else
	    return VALUES_1(Nil);
    }
    else
	return write_message_group_for_refresh_telewindow(gensym_window,
		left_edge_of_update_area_qm,top_edge_of_update_area_qm,
		right_edge_of_update_area_qm,bottom_edge_of_update_area_qm);
}

/* WRITE-MESSAGE-GROUP-FOR-RESHAPE-TELEWINDOW */
Object write_message_group_for_reshape_telewindow(gensym_window)
    Object gensym_window;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, native_window, x, y;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(76,34);
    current_icp_port = ISVREF(gensym_window,(SI_Long)13L);
    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = T;
	disable_resumability = temp;
	PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				native_window = ISVREF(gensym_window,
					(SI_Long)17L);
				temp = 
					get_width_of_native_window(native_window);
				send_icp_request_to_reshape_window(gensym_window,
					FIX((SI_Long)0L),FIX((SI_Long)0L),
					temp,
					get_height_of_native_window(native_window));
				if (FIXNUM_LT(Icp_window_protocol_supports_move_telewindow,
					ISVREF(gensym_window,(SI_Long)11L))) {
				    x = 
					    get_x_position_of_native_window(native_window);
				    y = 
					    get_y_position_of_native_window(native_window);
				    temp =  !(FIXNUM_EQ(x,
					    ISVREF(gensym_window,
					    (SI_Long)5L)) && FIXNUM_EQ(y,
					    ISVREF(gensym_window,
					    (SI_Long)6L))) ? 
					    send_icp_request_to_move_window(gensym_window,
					    x,y) : Nil;
				}
				else
				    temp = Nil;
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    result = VALUES_1(temp);
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

/* RESHAPE-TELEWINDOW */
Object reshape_telewindow(gensym_window,native_window)
    Object gensym_window, native_window;
{
    x_note_fn_call(76,35);
    if ( !TRUEP(ISVREF(gensym_window,(SI_Long)13L))) {
	if ( !TRUEP(telewindows_mdi_frame_p()))
	    paint_telewindows_window_with_credits(gensym_window);
    }
    if ( !TRUEP(ISVREF(gensym_window,(SI_Long)13L))) {
	make_or_revise_window_per_native_window(gensym_window,native_window);
	return refresh_telewindow(2,gensym_window,native_window);
    }
    else
	return write_message_group_for_reshape_telewindow(gensym_window);
}

/* IDLE-TELEWINDOWS-WHILE-DISPLAYING-CREDITS */
Object idle_telewindows_while_displaying_credits(workstation)
    Object workstation;
{
    Object earliest_time_to_overwrite_qm, current_workstation;
    Object current_workstation_window, current_workstation_native_window_qm;
    Object type_of_current_workstation_window;
    Declare_special(4);

    x_note_fn_call(76,36);
    earliest_time_to_overwrite_qm = ISVREF(workstation,(SI_Long)65L);
    SVREF(workstation,FIX((SI_Long)65L)) = Nil;
    if ( !EQ(User_specified_telewindows_splashscreen_time_in_seconds_qm,
	    FIX((SI_Long)0L))) {
	if ( !TRUEP(telewindows_mdi_frame_p()))
	    paint_telewindows_window_with_credits(ISVREF(workstation,
		    (SI_Long)1L));
    }
  next_loop:
    if ( !TRUEP(earliest_time_to_overwrite_qm) || 
	    FIXNUM_GT(c_native_clock_ticks_or_cache(Nil,Nil),
	    earliest_time_to_overwrite_qm))
	goto end_loop;
    idle_telewindows(workstation);
    current_workstation = workstation;
    PUSH_SPECIAL(Current_workstation,current_workstation,3);
      current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
      PUSH_SPECIAL(Current_workstation_window,current_workstation_window,2);
	current_workstation_native_window_qm = 
		ISVREF(Current_workstation_window,(SI_Long)17L);
	PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		1);
	  type_of_current_workstation_window = 
		  ISVREF(Current_workstation_window,(SI_Long)1L);
	  PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		  0);
	    get_all_x11_events(ISVREF(System_window,(SI_Long)17L));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Allow_talking_to_a_pre_version_4_g2_p = UNBOUND;

static Object string_constant_8;   /* "TWNG" */

static Object string_constant_9;   /* "Telewindows" */

static Object string_constant_10;  /* "[Telewindows: ~a connection to ~a G2 denied]" */

/* TELEWINDOWS-CHECK-VERSION-OF-REMOTE-G2 */
Object telewindows_check_version_of_remote_g2(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(76,37);
    if (reason_to_reject_connection_to_g2_p(gensym_window)) {
	if ( !EQ(Verbosity_level,Qsilent)) {
	    temp = this_is_twng_p() ? string_constant_8 : string_constant_9;
	    notify_user_at_console(3,string_constant_10,temp,
		    reason_to_reject_connection_to_g2_p(gensym_window));
	}
	close_telewindows_connection(gensym_window);
    }
    else
	initialize_gensym_window_after_connection(gensym_window);
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "pre-8.3r0" */

static Object string_constant_12;  /* "pre-4.0" */

/* REASON-TO-REJECT-CONNECTION-TO-G2-P */
Object reason_to_reject_connection_to_g2_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(76,38);
    if (this_is_twng_p()) {
	if ( !FIXNUM_LT(Icp_window_protocol_supports_chart_views_in_panes,
		ISVREF(gensym_window,(SI_Long)11L)))
	    return VALUES_1(string_constant_11);
	else
	    return VALUES_1(Nil);
    }
    else if (talking_to_a_pre_version_4_g2_p(gensym_window)) {
	if ( !TRUEP(Allow_talking_to_a_pre_version_4_g2_p))
	    return VALUES_1(string_constant_12);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "~a:~a:~a" */

/* MAKE-TELEWINDOWS-NETWORK-PATHNAME */
Object make_telewindows_network_pathname(protocol,host,listener)
    Object protocol, host, listener;
{
    Object local_string, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value, modified_protocol, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(76,39);
    local_string = SYMBOLP(protocol) ? symbol_name_text_string(protocol) : 
	    protocol;
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(lengthw(local_string));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(local_string,i));
	      simple_or_wide_character = (SI_Long)45L == IFIX(c) ? 
		      FIX((SI_Long)95L) : c;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      modified_protocol = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_1 = tformat_text_string(4,string_constant_13,modified_protocol,
	    host,listener);
    reclaim_text_string(modified_protocol);
    return VALUES_1(temp_1);
}

/* MAKE-TELEWINDOWS-NETWORK-CONFIGURATION */
Object make_telewindows_network_configuration(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(76,40);
    temp = copy_text_string(ISVREF(workstation,(SI_Long)73L));
    return gensym_list_3(temp,ISVREF(workstation,(SI_Long)74L),
	    ISVREF(workstation,(SI_Long)75L));
}

Object Counter_for_throughput_adjustment = UNBOUND;

Object Legacy_heartbeat_adjustment_priority = UNBOUND;

Object Legacy_heartbeat_adjustment_interval = UNBOUND;

/* DO-LEGACY-HEARTBEAT-ADJUSTMENTS */
Object do_legacy_heartbeat_adjustments()
{
    x_note_fn_call(76,41);
    g2ext_cache_deferred_rules();
    return VALUES_1(Nil);
}

static Object Qdo_legacy_heartbeat_adjustments;  /* do-legacy-heartbeat-adjustments */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* SCHEDULE-TW-LEGACY-HEARTBEAT-TASKS-IF-NECESSARY */
Object schedule_tw_legacy_heartbeat_tasks_if_necessary()
{
    Object schedule_task_qm, current_task_schedule_modify_arg_2;
    Object current_task_schedule_modify_arg_3;
    Object current_task_schedule_modify_arg_8, old_structure_being_reclaimed;
    Object temp, svref_new_value, def_structure_schedule_task_variable, task;
    Object ctask, p, v, q, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(76,42);
    schedule_task_qm = Counter_for_throughput_adjustment;
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	current_task_schedule_modify_arg_2 = 
		Legacy_heartbeat_adjustment_priority;
	current_task_schedule_modify_arg_3 = 
		Legacy_heartbeat_adjustment_interval;
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qdo_legacy_heartbeat_adjustments);
	if (Counter_for_throughput_adjustment) {
	    if (EQ(Counter_for_throughput_adjustment,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(Counter_for_throughput_adjustment,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(Counter_for_throughput_adjustment);
	    inline_note_reclaim_cons(Counter_for_throughput_adjustment,Nil);
	    old_structure_being_reclaimed = Structure_being_reclaimed;
	    Structure_being_reclaimed = Counter_for_throughput_adjustment;
	    reclaim_schedule_task_args(ISVREF(Counter_for_throughput_adjustment,
		    (SI_Long)9L));
	    temp = Counter_for_throughput_adjustment;
	    SVREF(temp,FIX((SI_Long)9L)) = Nil;
	    Structure_being_reclaimed = old_structure_being_reclaimed;
	    temp = Counter_for_throughput_adjustment;
	    svref_new_value = Chain_of_available_schedule_tasks;
	    SVREF(temp,FIX((SI_Long)0L)) = svref_new_value;
	    Chain_of_available_schedule_tasks = 
		    Counter_for_throughput_adjustment;
	}
	def_structure_schedule_task_variable = 
		Chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    Chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
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
	aref_new_value = 
		DOUBLE_FLOAT_TO_DOUBLE(current_task_schedule_modify_arg_3);
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	SVREF(task,FIX((SI_Long)4L)) = current_task_schedule_modify_arg_2;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qdo_legacy_heartbeat_adjustments;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)0L);
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = System_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
	def_structure_queue_element_variable = 
		Chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    Chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    make_permanent_queue_element_structure_internal();
	inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = q;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,Priority_of_next_task))
	    Priority_of_next_task = p;
	Counter_for_throughput_adjustment = task;
    }
    return VALUES_1(Nil);
}

static Object Qfailed_to_connect;  /* failed-to-connect */

static Object Qdevelopment;        /* development */

static Object string_constant_14;  /* "[Telewindows: authorized for connection to any G2.]" */

static Object Qconnected;          /* connected */

static Object string_constant_15;  /* "[Telewindows: authorized for a ~a license; ~
				    *                  will attempt to obtain a Floating Telewindows license~a.]"
				    */

static Object Qfloating;           /* floating */

static Object string_constant_16;  /* "" */

static Object string_constant_17;  /* " if necessary" */

static Object Qconnected_and_awaiting_license_level;  /* connected-and-awaiting-license-level */

/* SUCCEED-AT-CONNECTING-TELEWINDOWS-WORKSTATION */
Object succeed_at_connecting_telewindows_workstation(icp_socket)
    Object icp_socket;
{
    Object workstation, window, current_workstation;
    Object current_workstation_window, current_workstation_native_window_qm;
    Object type_of_current_workstation_window, svref_new_value;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(76,43);
    workstation = ISVREF(icp_socket,(SI_Long)23L);
    window = ISVREF(workstation,(SI_Long)1L);
    deregister_all_icp_connect_callbacks(icp_socket);
    if ( !EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_running)) {
	SVREF(workstation,FIX((SI_Long)63L)) = Qfailed_to_connect;
	return VALUES_1(Nil);
    }
    SVREF(workstation,FIX((SI_Long)62L)) = icp_socket;
    initialize_telewindows_process_telewindows_icp_socket(icp_socket);
    if (icp_connection_open_p(icp_socket)) {
	g2ext_x11_set_window_is_connected(IFIX(ISVREF(window,(SI_Long)17L)));
	current_workstation = workstation;
	PUSH_SPECIAL(Current_workstation,current_workstation,3);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  2);
	    current_workstation_native_window_qm = 
		    ISVREF(Current_workstation_window,(SI_Long)17L);
	    PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		    1);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		      0);
		get_all_x11_events(ISVREF(window,(SI_Long)17L));
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	svref_new_value = ISVREF(icp_socket,(SI_Long)4L);
	SVREF(window,FIX((SI_Long)13L)) = svref_new_value;
	current_icp_port = ISVREF(window,(SI_Long)13L);
	PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = T;
	    disable_resumability = temp;
	    PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_initialize_telewindows_workstation(workstation,
					    window);
				    end_icp_message_group();
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
	SVREF(icp_socket,FIX((SI_Long)9L)) = Nil;
	if (EQ(window,System_window)) {
	    current_workstation = ISVREF(window,(SI_Long)2L);
	    PUSH_SPECIAL(Current_workstation,current_workstation,3);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		      2);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
			1);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
			  0);
		    idle_telewindows_while_displaying_credits(ISVREF(window,
			    (SI_Long)2L));
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	SVREF(workstation,FIX((SI_Long)78L)) = Nil;
	if (telewindows_licensed_for_product_p(Qdevelopment)) {
	    if (EQ(Verbosity_level,Qverbose))
		notify_user_at_console(1,string_constant_14);
	    handle_licensed_font_initializations_as_appropriate(window);
	    SVREF(workstation,FIX((SI_Long)63L)) = Qconnected;
	}
	else {
	    if (EQ(Verbosity_level,Qverbose)) {
		temp = 
			get_telewindows_product_name_from_level(Telewindows_license_level);
		temp_1 = 
			get_telewindows_product_name_from_level(Telewindows_license_level);
		notify_user_at_console(3,string_constant_15,temp,EQ(temp_1,
			Qfloating) ? string_constant_16 : string_constant_17);
	    }
	    SVREF(workstation,FIX((SI_Long)63L)) = 
		    Qconnected_and_awaiting_license_level;
	    temp = c_native_clock_ticks_or_cache(Nil,Nil);
	    svref_new_value = FIXNUM_ADD(temp,
		    FIXNUM_TIMES(Fixnum_time_interval_for_one_second,
		    ISVREF(workstation,(SI_Long)61L)));
	    SVREF(workstation,FIX((SI_Long)67L)) = svref_new_value;
	}
	return VALUES_1(icp_socket);
    }
    else
	return VALUES_1(Nil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object string_constant_18;  /* "[Telewindows: connecting to host ~s at port ~a via protocol ~a~a]" */

static Object Kuse_default;        /* :use-default */

static Object Qconnecting;         /* connecting */

static Object Qhandle_telewindows_shutdown;  /* handle-telewindows-shutdown */

static Object Qnot_established;    /* not-established */

static Object Qsucceed_at_connecting_telewindows_workstation;  /* succeed-at-connecting-telewindows-workstation */

/* TRY-TO-CONNECT-TELEWINDOWS-WORKSTATION */
Object try_to_connect_telewindows_workstation(workstation)
    Object workstation;
{
    Object system_time;
    volatile Object decrypted_primeval_timestamp_qm;
    Object decrypted_primeval_time_qm, timestamp_qm, encoded_timestamp_field;
    Object ab_loop_list_, timestamp_field_qm;
    volatile Object rotator_specs;
    Object gensymed_symbol, gensymed_symbol_1, temp_2, rotator, offset;
    Object ab_loop_list__1, ab_loop_desetq_, logrotate_in_place_arg_1;
    Object logrotate_in_place_arg_2;
    volatile Object filled_timestamp_field_components;
    Object key, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object component, rotator_spec, circularity_point, raw_field;
    Object timestamp_field, raw_field_list, time_1, temp_4, old_value_qm;
    Object timestamp, fix_time, temp_5, timestamp_cons;
    Object encrypted_timestamp_field, rotator_list, temp_6, temp_7;
    Object network_config, icp_socket_qm;
    SI_Long ab_loop_repeat_, index_1, shift_amount, ab_loop_repeat__1;
    SI_Long car_new_value, offset_1, logrotate_in_place_arg_2_1;
    char temp_3;
    double temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(76,44);
    SAVE_STACK();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	system_time = Qunbound_in_protected_let;
	decrypted_primeval_timestamp_qm = Qunbound_in_protected_let;
	decrypted_primeval_time_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(2)) {
	    temp = g2ext_unix_time_as_float();
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    system_time = DOUBLE_TO_DOUBLE_FLOAT(temp + temp_1);
	    timestamp_qm = Nil;
	    encoded_timestamp_field = Nil;
	    ab_loop_list_ = Minimal_fragmentation_seeds;
	    timestamp_field_qm = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    encoded_timestamp_field = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    rotator_specs = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(1)) {
		gensymed_symbol = make_gensym_list_1(FIX((SI_Long)9L));
		gensymed_symbol_1 = gensymed_symbol;
		temp_2 = 
			gensym_cons_1(FOURTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)0L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)3L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)6L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)9L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(THIRD(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)12L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(SIXTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)12L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)15L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)18L));
		M_CAR(gensymed_symbol_1) = temp_2;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_2 = 
			gensym_cons_1(SEVENTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)18L));
		M_CAR(gensymed_symbol_1) = temp_2;
		rotator_specs = gensymed_symbol;
		rotator = Nil;
		offset = Nil;
		ab_loop_list__1 = rotator_specs;
		ab_loop_desetq_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		rotator = CAR(ab_loop_desetq_);
		offset = CDR(ab_loop_desetq_);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		logrotate_in_place_arg_1 = rotator;
		logrotate_in_place_arg_2 = offset;
		encoded_timestamp_field = 
			assemble_uncached_compound_method_flags(encoded_timestamp_field,
			logrotate_in_place_arg_1,logrotate_in_place_arg_2,
			FIX((SI_Long)3L));
		goto next_loop_1;
	      end_loop_1:;
		filled_timestamp_field_components = Qunbound_in_protected_let;
		key = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    ab_loop_repeat_ = (SI_Long)3L;
		    index_1 = (SI_Long)2L;
		    shift_amount = (SI_Long)-14L;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_)) {
			index_1 = index_1 - (SI_Long)1L;
			shift_amount = shift_amount + (SI_Long)7L;
		    }
		    ab_loopvar__2 = 
			    gensym_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
			    index_1),encoded_timestamp_field),
			    FIX(shift_amount)),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_2;
		  end_loop_2:
		    filled_timestamp_field_components = ab_loopvar_;
		    goto end;
		    filled_timestamp_field_components = Qnil;
		  end:;
		    key = FIRST(filled_timestamp_field_components);
		    component = Nil;
		    ab_loop_list__1 = REST(filled_timestamp_field_components);
		  next_loop_3:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		    component = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    if ( !FIXNUM_EQ(key,component)) {
			temp_3 = TRUEP(Nil);
			goto end_1;
		    }
		    goto next_loop_3;
		  end_loop_3:
		    temp_3 = TRUEP(T);
		    goto end_1;
		    temp_3 = TRUEP(Qnil);
		  end_1:;
		    SAVE_VALUES(VALUES_1(temp_3 ? key : Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (filled_timestamp_field_components) {
		    if ( !EQ(filled_timestamp_field_components,
			    Qunbound_in_protected_let))
			reclaim_gensym_list_1(filled_timestamp_field_components);
		}
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		SAVE_VALUES(VALUES_1(result));
	    }
	    POP_UNWIND_PROTECT(1);
	    if (rotator_specs) {
		if ( !EQ(rotator_specs,Qunbound_in_protected_let)) {
		    rotator_spec = Nil;
		    ab_loop_list__1 = rotator_specs;
		  next_loop_4:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_4;
		    rotator_spec = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    reclaim_gensym_cons_1(rotator_spec);
		    goto next_loop_4;
		  end_loop_4:
		    reclaim_gensym_list_1(rotator_specs);
		}
	    }
	    CONTINUE_UNWINDING(1);
	    result = RESTORE_VALUES();
	    timestamp_field_qm = result;
	    timestamp_qm = gensym_cons_1(timestamp_field_qm,timestamp_qm);
	    goto next_loop;
	  end_loop:;
	    timestamp_field_qm = Nil;
	    ab_loop_list_ = timestamp_qm;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    timestamp_field_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(timestamp_field_qm)) {
		if (timestamp_qm)
		    reclaim_gensym_list_1(timestamp_qm);
		decrypted_primeval_timestamp_qm = Nil;
		goto end_2;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    decrypted_primeval_timestamp_qm = nreverse(timestamp_qm);
	    goto end_2;
	    decrypted_primeval_timestamp_qm = Qnil;
	  end_2:;
	    if (decrypted_primeval_timestamp_qm) {
		circularity_point = 
			FIXNUM_SUB1(length(decrypted_primeval_timestamp_qm));
		temp_2 = nthcdr(circularity_point,
			decrypted_primeval_timestamp_qm);
		M_CDR(temp_2) = decrypted_primeval_timestamp_qm;
		if (PUSH_UNWIND_PROTECT(0)) {
		    ab_loop_repeat_ = (SI_Long)5L;
		    raw_field = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_6:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_6;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    raw_field = FIX((SI_Long)0L);
		    ab_loop_repeat__1 = (SI_Long)7L;
		    timestamp_field = Nil;
		  next_loop_7:
		    if ( !((SI_Long)0L < ab_loop_repeat__1))
			goto end_loop_7;
		    ab_loop_repeat__1 = ab_loop_repeat__1 - (SI_Long)1L;
		    timestamp_field = CAR(decrypted_primeval_timestamp_qm);
		    raw_field = logtest(FIX((SI_Long)64L),timestamp_field) 
			    ? logior(ash(raw_field,FIX((SI_Long)-1L)),
			    FIX((SI_Long)64L)) : ash(raw_field,
			    FIX((SI_Long)-1L));
		    temp_2 = ash(timestamp_field,FIX((SI_Long)1L));
		    M_CAR(decrypted_primeval_timestamp_qm) = temp_2;
		    decrypted_primeval_timestamp_qm = 
			    CDR(decrypted_primeval_timestamp_qm);
		    goto next_loop_7;
		  end_loop_7:;
		    ab_loopvar__2 = gensym_cons_1(raw_field,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_6;
		  end_loop_6:
		    raw_field_list = ab_loopvar_;
		    goto end_3;
		    raw_field_list = Qnil;
		  end_3:;
		    raw_field = Nil;
		    ab_loop_list_ = raw_field_list;
		    shift_amount = (SI_Long)28L;
		    time_1 = FIX((SI_Long)0L);
		    ab_loop_iter_flag_ = T;
		  next_loop_8:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_8;
		    raw_field = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if ( !TRUEP(ab_loop_iter_flag_))
			shift_amount = shift_amount + (SI_Long)-7L;
		    time_1 = logior(ash(raw_field,FIX(shift_amount)),time_1);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_8;
		  end_loop_8:
		    reclaim_gensym_list_1(raw_field_list);
		    temp_4 = time_1;
		    goto end_4;
		    temp_4 = Qnil;
		  end_4:;
		    SAVE_VALUES(VALUES_1(temp_4));
		}
		POP_UNWIND_PROTECT(0);
		temp_2 = nthcdr(circularity_point,
			decrypted_primeval_timestamp_qm);
		M_CDR(temp_2) = Nil;
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		decrypted_primeval_time_qm = result;
	    }
	    else
		decrypted_primeval_time_qm = Nil;
	    temp_3 =  !TRUEP(decrypted_primeval_time_qm);
	    if (temp_3);
	    else {
		temp_4 = lfloat(decrypted_primeval_time_qm,_);
		temp_3 = NUM_LT(system_time,temp_4);
	    }
	    if (temp_3) {
		old_value_qm = THIRD(Master_hierarchy_reconciliation_switches);
		if (old_value_qm)
		    reclaim_gensym_list_1(old_value_qm);
		temp_2 = Master_hierarchy_reconciliation_switches;
		raw_field_list = Qunbound_in_protected_let;
		timestamp = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(1)) {
		    ab_loop_repeat_ = (SI_Long)5L;
		    temp = DOUBLE_FLOAT_TO_DOUBLE(system_time);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		    fix_time = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp + temp_1),_);
		    index_1 = (SI_Long)4L;
		    shift_amount = (SI_Long)-28L;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_9:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_9;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_)) {
			index_1 = index_1 - (SI_Long)1L;
			shift_amount = shift_amount + (SI_Long)7L;
		    }
		    ab_loopvar__2 = 
			    gensym_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
			    index_1),fix_time),FIX(shift_amount)),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_9;
		  end_loop_9:
		    raw_field_list = ab_loopvar_;
		    goto end_5;
		    raw_field_list = Qnil;
		  end_5:;
		    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
		    gensymed_symbol_1 = gensymed_symbol;
		    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
		    timestamp = gensymed_symbol;
		    circularity_point = FIXNUM_SUB1(length(timestamp));
		    temp_5 = nthcdr(circularity_point,timestamp);
		    M_CDR(temp_5) = timestamp;
		    if (PUSH_UNWIND_PROTECT(0)) {
			raw_field = Nil;
			ab_loop_list_ = raw_field_list;
		      next_loop_10:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_10;
			raw_field = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			ab_loop_repeat_ = (SI_Long)7L;
		      next_loop_11:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_11;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			timestamp_field = CAR(timestamp);
			car_new_value = oddp(raw_field) ? 
				IFIX(ash(timestamp_field,
				FIX((SI_Long)1L))) | (SI_Long)1L : 
				IFIX(timestamp_field) << (SI_Long)1L;
			M_CAR(timestamp) = FIX(car_new_value);
			timestamp = CDR(timestamp);
			raw_field = FIX(IFIX(raw_field) >>  -  - (SI_Long)1L);
			goto next_loop_11;
		      end_loop_11:;
			goto next_loop_10;
		      end_loop_10:
			temp_4 = timestamp;
			goto end_6;
			temp_4 = Qnil;
		      end_6:;
			SAVE_VALUES(VALUES_1(temp_4));
		    }
		    POP_UNWIND_PROTECT(0);
		    temp_5 = nthcdr(circularity_point,timestamp);
		    M_CDR(temp_5) = Nil;
		    CONTINUE_UNWINDING(0);
		    result = RESTORE_VALUES();
		    SAVE_VALUES(VALUES_1(result));
		}
		POP_UNWIND_PROTECT(1);
		if (raw_field_list) {
		    if ( !EQ(raw_field_list,Qunbound_in_protected_let))
			reclaim_gensym_list_1(raw_field_list);
		}
		CONTINUE_UNWINDING(1);
		result = RESTORE_VALUES();
		timestamp = result;
		timestamp_field = Nil;
		ab_loop_list_ = timestamp;
		timestamp_cons = timestamp;
		ab_loop_iter_flag_ = T;
	      next_loop_12:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_12;
		timestamp_field = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    timestamp_cons = M_CDR(timestamp_cons);
		if ( !TRUEP(timestamp_cons))
		    goto end_loop_12;
		encrypted_timestamp_field = logiorn(3,ash(timestamp_field,
			FIX((SI_Long)0L)),ash(timestamp_field,
			FIX((SI_Long)7L)),ash(timestamp_field,
			FIX((SI_Long)14L)));
		gensymed_symbol = make_gensym_list_1(FIX((SI_Long)7L));
		gensymed_symbol_1 = gensymed_symbol;
		temp_5 = THIRD(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SIXTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SEVENTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SECOND(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FIRST(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FIFTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FOURTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		rotator_list = gensymed_symbol;
		rotator = Nil;
		ab_loop_list__1 = rotator_list;
		offset_1 = (SI_Long)0L;
		ab_loop_iter_flag_ = T;
	      next_loop_13:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_13;
		rotator = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    offset_1 = offset_1 + (SI_Long)3L;
		logrotate_in_place_arg_1 = rotator;
		logrotate_in_place_arg_2_1 = offset_1;
		encrypted_timestamp_field = 
			assemble_uncached_compound_method_flags(encrypted_timestamp_field,
			logrotate_in_place_arg_1,
			FIX(logrotate_in_place_arg_2_1),FIX((SI_Long)3L));
		ab_loop_iter_flag_ = Nil;
		goto next_loop_13;
	      end_loop_13:;
		reclaim_gensym_list_1(rotator_list);
		M_CAR(timestamp_cons) = encrypted_timestamp_field;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_12;
	      end_loop_12:
		temp_5 = timestamp;
		goto end_7;
		temp_5 = Qnil;
	      end_7:;
		M_THIRD(temp_2) = temp_5;
	    }
	}
	POP_UNWIND_PROTECT(2);
	if (decrypted_primeval_timestamp_qm) {
	    if ( !EQ(decrypted_primeval_timestamp_qm,
		    Qunbound_in_protected_let))
		reclaim_gensym_list_1(decrypted_primeval_timestamp_qm);
	}
	CONTINUE_UNWINDING(2);
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !EQ(Verbosity_level,Qsilent)) {
	temp_4 = ISVREF(workstation,(SI_Long)74L);
	temp_6 = ISVREF(workstation,(SI_Long)75L);
	temp_7 = ISVREF(workstation,(SI_Long)73L);
	notify_user_at_console(5,string_constant_18,temp_4,temp_6,temp_7,
		secure_icp_string(2,Kuse_default,T));
    }
    if (SEVENTH(Consistency_tree_focus_shifts) && 
	    EIGHTH(SECOND(Icon_list_notes)) && T) {
	notify_user_at_console(1,Tw_system_time_too_early_goodbye_message);
	shut_down_ab_process(0);
    }
    set_up_telewindows_connection_timeout();
    network_config = make_telewindows_network_configuration(workstation);
    icp_socket_qm = make_network_connection(1,network_config);
    reclaim_gensym_list_1(network_config);
    temp_2 = icp_socket_qm ? Qconnecting : Qfailed_to_connect;
    SVREF(workstation,FIX((SI_Long)63L)) = temp_2;
    if (icp_socket_qm) {
	register_icp_connection_loss_callback(Qhandle_telewindows_shutdown,
		icp_socket_qm);
	SVREF(icp_socket_qm,FIX((SI_Long)9L)) = Qnot_established;
	SVREF(icp_socket_qm,FIX((SI_Long)23L)) = workstation;
	setup_network_connection_for_connect(2,icp_socket_qm,
		Qsucceed_at_connecting_telewindows_workstation);
    }
    RESTORE_STACK();
    return VALUES_1(icp_socket_qm);
}

static Object string_constant_19;  /* "~%[Telewindows: received word back from G2 . . . ~
				    *           Telewindows License Level: ~a]"
				    */

static Object Qg2_license_level;   /* g2-license-level */

static Object string_constant_20;  /* "[Telewindows: the target G2 is authorized for ~a Telewindows connections]" */

static Object Qunauthorized;       /* unauthorized */

static Object string_constant_21;  /* "[Telewindows: Connected.]" */

static Object string_constant_22;  /* "[Telewindows: Sorry.  Permission has been denied for access via this Telewindows.]" */

static Object string_constant_23;  /* "[Telewindows: Sorry.  Telewindows has timed out in its attempt to obtain ~
				    *              permission to connect to G2.]"
				    */

/* TRY-TO-OBTAIN-TELEWINDOWS-LICENSE-LEVEL */
Object try_to_obtain_telewindows_license_level(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(76,45);
    if (ISVREF(workstation,(SI_Long)78L)) {
	if (EQ(Verbosity_level,Qverbose)) {
	    notify_user_at_console(2,string_constant_19,
		    get_telewindows_product_name_from_level(Telewindows_license_level));
	    if (getf(ISVREF(workstation,(SI_Long)79L),Qg2_license_level,_))
		notify_user_at_console(2,string_constant_20,
			get_telewindows_product_from_level(getf(ISVREF(workstation,
			(SI_Long)79L),Qg2_license_level,_)));
	    handle_licensed_font_initializations_as_appropriate(ISVREF(workstation,
		    (SI_Long)1L));
	}
	temp = ISVREF(workstation,(SI_Long)78L);
	if (FIXNUM_GT(temp,
		telewindows_license_level_from_product(Qunauthorized))) {
	    if ( !EQ(Verbosity_level,Qsilent))
		notify_user_at_console(1,string_constant_21);
	    return VALUES_1(SVREF(workstation,FIX((SI_Long)63L)) = Qconnected);
	}
	else {
	    if ( !EQ(Verbosity_level,Qsilent))
		notify_user_at_console(1,string_constant_22);
	    return VALUES_1(SVREF(workstation,FIX((SI_Long)63L)) = 
		    Qfailed_to_connect);
	}
    }
    else {
	temp = c_native_clock_ticks_or_cache(Nil,Nil);
	if (FIXNUM_GT(temp,ISVREF(workstation,(SI_Long)67L))) {
	    if ( !EQ(Verbosity_level,Qsilent))
		notify_user_at_console(1,string_constant_23);
	    return VALUES_1(SVREF(workstation,FIX((SI_Long)63L)) = 
		    Qfailed_to_connect);
	}
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qbeing_rerouted;     /* being-rerouted */

/* SET-UP-INITIAL-TELEWINDOWS-ROUTING */
Object set_up_initial_telewindows_routing(telewindows_workstation)
    Object telewindows_workstation;
{
    Object value, svref_new_value;

    x_note_fn_call(76,46);
    value = ISVREF(telewindows_workstation,(SI_Long)58L);
    svref_new_value = STRINGP(value) || text_string_p(value) ? 
	    copy_text_string(value) : value;
    SVREF(telewindows_workstation,FIX((SI_Long)73L)) = svref_new_value;
    value = ISVREF(telewindows_workstation,(SI_Long)56L);
    svref_new_value = STRINGP(value) || text_string_p(value) ? 
	    copy_text_string(value) : value;
    SVREF(telewindows_workstation,FIX((SI_Long)74L)) = svref_new_value;
    value = ISVREF(telewindows_workstation,(SI_Long)57L);
    svref_new_value = STRINGP(value) || text_string_p(value) ? 
	    copy_text_string(value) : value;
    SVREF(telewindows_workstation,FIX((SI_Long)75L)) = svref_new_value;
    value = ISVREF(telewindows_workstation,(SI_Long)59L);
    svref_new_value = STRINGP(value) || text_string_p(value) ? 
	    copy_text_string(value) : value;
    SVREF(telewindows_workstation,FIX((SI_Long)76L)) = svref_new_value;
    return VALUES_1(SVREF(telewindows_workstation,FIX((SI_Long)63L)) = 
	    Qbeing_rerouted);
}

static Object string_constant_24;  /* "[Telewindows: Rerouting to host ~s at address ~a]" */

/* REROUTE-TELEWINDOWS-CONNECTION */
Object reroute_telewindows_connection(gensym_window,protocol,host,port,
	    init_string)
    Object gensym_window, protocol, host, port, init_string;
{
    Object telewindows_workstation, svref_new_value;

    x_note_fn_call(76,47);
    telewindows_workstation = ISVREF(gensym_window,(SI_Long)2L);
    if (text_string_p(ISVREF(telewindows_workstation,(SI_Long)69L)))
	reclaim_text_string(ISVREF(telewindows_workstation,(SI_Long)69L));
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)73L);
    SVREF(telewindows_workstation,FIX((SI_Long)69L)) = svref_new_value;
    if (text_string_p(ISVREF(telewindows_workstation,(SI_Long)70L)))
	reclaim_text_string(ISVREF(telewindows_workstation,(SI_Long)70L));
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)74L);
    SVREF(telewindows_workstation,FIX((SI_Long)70L)) = svref_new_value;
    if (text_string_p(ISVREF(telewindows_workstation,(SI_Long)71L)))
	reclaim_text_string(ISVREF(telewindows_workstation,(SI_Long)71L));
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)75L);
    SVREF(telewindows_workstation,FIX((SI_Long)71L)) = svref_new_value;
    if (text_string_p(ISVREF(telewindows_workstation,(SI_Long)72L)))
	reclaim_text_string(ISVREF(telewindows_workstation,(SI_Long)72L));
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)76L);
    SVREF(telewindows_workstation,FIX((SI_Long)72L)) = svref_new_value;
    SVREF(telewindows_workstation,FIX((SI_Long)73L)) = protocol;
    SVREF(telewindows_workstation,FIX((SI_Long)74L)) = host;
    SVREF(telewindows_workstation,FIX((SI_Long)75L)) = port;
    SVREF(telewindows_workstation,FIX((SI_Long)76L)) = init_string;
    if ( !EQ(Verbosity_level,Qsilent))
	notify_user_at_console(3,string_constant_24,host,port);
    return shutdown_icp_socket_connection(2,ISVREF(telewindows_workstation,
	    (SI_Long)62L),Qbeing_rerouted);
}

static Object string_constant_25;  /* "[Telewindows: Attempting to return to host ~s at address ~a]" */

static Object string_constant_26;  /* "(unknown)" */

static Object string_constant_27;  /* "Unable to connect to host ~s at port ~a via protocol ~a~a" */

/* SEND-TELEWINDOWS-HOME */
Object send_telewindows_home(telewindows_workstation)
    Object telewindows_workstation;
{
    Object temp, temp_1, temp_2, svref_new_value;

    x_note_fn_call(76,48);
    if ( !EQ(Verbosity_level,Qsilent))
	notify_user_at_console(3,string_constant_25,
		ISVREF(telewindows_workstation,(SI_Long)74L),
		ISVREF(telewindows_workstation,(SI_Long)71L));
    temp = ISVREF(telewindows_workstation,(SI_Long)70L);
    if (temp);
    else
	temp = string_constant_26;
    temp_1 = ISVREF(telewindows_workstation,(SI_Long)71L);
    if (temp_1);
    else
	temp_1 = string_constant_26;
    temp_2 = ISVREF(telewindows_workstation,(SI_Long)73L);
    if (temp_2);
    else
	temp_2 = string_constant_26;
    svref_new_value = tformat_text_string(5,string_constant_27,temp,temp_1,
	    temp_2,secure_icp_string(2,Kuse_default,T));
    SVREF(telewindows_workstation,FIX((SI_Long)77L)) = svref_new_value;
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)69L);
    SVREF(telewindows_workstation,FIX((SI_Long)73L)) = svref_new_value;
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)70L);
    SVREF(telewindows_workstation,FIX((SI_Long)74L)) = svref_new_value;
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)71L);
    SVREF(telewindows_workstation,FIX((SI_Long)75L)) = svref_new_value;
    svref_new_value = ISVREF(telewindows_workstation,(SI_Long)72L);
    SVREF(telewindows_workstation,FIX((SI_Long)76L)) = svref_new_value;
    SVREF(telewindows_workstation,FIX((SI_Long)69L)) = Nil;
    SVREF(telewindows_workstation,FIX((SI_Long)70L)) = Nil;
    SVREF(telewindows_workstation,FIX((SI_Long)71L)) = Nil;
    SVREF(telewindows_workstation,FIX((SI_Long)72L)) = Nil;
    return get_telewindows_workstation_ready_to_connect(telewindows_workstation);
}

static Object Qtop_level_error_catcher;  /* top-level-error-catcher */

static Object Qerror_trapped;      /* error-trapped */

/* RUN-TELEWINDOWS */
Object run_telewindows(ignore_me)
    Object ignore_me;
{
    Object top_level_error_catcher_tag, error_occurred_p;
    Declare_catch(1);
    Declare_special(1);

    x_note_fn_call(76,49);
    Gc_silence = Nil;
    if (Do_error_trapping_qm) {
	top_level_error_catcher_tag = Qtop_level_error_catcher;
	PUSH_SPECIAL(Top_level_error_catcher_tag,top_level_error_catcher_tag,
		0);
	  if (PUSH_CATCH(Top_level_error_catcher_tag,0)) {
	      Top_level_error_seen = Nil;
	      register_all_signal_handlers();
	      run_telewindows_1();
	      error_occurred_p = Nil;
	  }
	  else
	      error_occurred_p = CATCH_VALUES();
	  POP_CATCH(0);
	POP_SPECIAL();
	if (error_occurred_p) {
	    minimal_internal_error_given_format_info(Gensym_error_format_string,
		    Gensym_error_argument_list,
		    Gensym_error_sure_of_format_info_p);
	    return abort_telewindows_top_level(Qerror_trapped);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return run_telewindows_1();
}

static Object Qdefault;            /* default */

static Object Qabort_level_0;      /* abort-level-0 */

/* RUN-TELEWINDOWS-1 */
Object run_telewindows_1()
{
    Object inner_abort_level_tag, scheduler_enabled_qm;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(76,50);
    SAVE_STACK();
    initialize_scheduler();
    initialize_gensym_time();
    change_login_box_size();
    if (secure_icp_requested_p())
	set_up_secure_icp(1,Qdefault);
    establish_new_telewindows_workstation();
    if (PUSH_CATCH(Qabort_level_0,1)) {
	inner_abort_level_tag = Qabort_level_0;
	PUSH_SPECIAL(Inner_abort_level_tag,inner_abort_level_tag,1);
	  display_events_were_enabled = (SI_Long)0L != 
		  ne_display_events_enabled();
	  ne_enable_display_events();
	  if (PUSH_UNWIND_PROTECT(0)) {
	      scheduler_enabled_qm = T;
	      PUSH_SPECIAL(Scheduler_enabled_qm,scheduler_enabled_qm,0);
		SAVE_VALUES(service_telewindows_workstations());
	      POP_SPECIAL();
	  }
	  POP_UNWIND_PROTECT(0);
	  if ( !display_events_were_enabled)
	      ne_disable_display_events();
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object Qtelewindows;        /* telewindows */

/* ESTABLISH-NEW-TELEWINDOWS-WORKSTATION */
Object establish_new_telewindows_workstation()
{
    Object gensym_window;

    x_note_fn_call(76,51);
    gensym_window = make_or_revise_window_per_native_window(Nil,
	    make_native_window(1,Qtelewindows));
    return set_up_telewindows_workstation(gensym_window);
}

static Object Qhandle_icp_messages;  /* handle-icp-messages */

/* TW-EVENT-LOOP */
Object tw_event_loop()
{
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(76,52);
    SAVE_STACK();
  next_loop:
    if (PUSH_UNWIND_PROTECT(1)) {
	if (PUSH_CATCH(Qhandle_icp_messages,0)) {
	    if (Scheduler_enabled_qm)
		enqueue_scheduler_events_if_necessary(Nil);
	  next_loop_1:
	    g2_event_cycle_handling_windows_quit();
	    tw_execute_deferred_actions();
	    goto next_loop_1;
	  end_loop:;
	}
	POP_CATCH(0);
    }
    POP_UNWIND_PROTECT(1);
    if (Icp_socket_for_handle_icp_messages && 
	    FIXNUM_EQ(ISVREF(Icp_socket_for_handle_icp_messages,
	    (SI_Long)15L),Icp_connection_closed))
	finalize_and_reclaim_icp_socket(Icp_socket_for_handle_icp_messages);
    CONTINUE_UNWINDING(1);
    goto next_loop;
  end_loop_1:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

static Object Quser_name;          /* user-name */

static Object Qmd5_password;       /* md5-password */

/* ADJUST-PASSWORD-HASH-IF-NECESSARY */
Object adjust_password_hash_if_necessary(window_parameters_plist,
	    password_in_clear_qm)
    Object window_parameters_plist, password_in_clear_qm;
{
    Object user_name_qm;

    x_note_fn_call(76,53);
    if (password_in_clear_qm) {
	user_name_qm = getf(window_parameters_plist,Quser_name,_);
	if (user_name_qm)
	    return VALUES_1(nconc2(window_parameters_plist,
		    gensym_list_2(Qmd5_password,
		    encode_password_via_md5(user_name_qm,
		    password_in_clear_qm,Nil))));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_28;  /* "[Telewindows: User-specified splashtime: ~d seconds (min/max/default: ~d/~d/~d)]" */

static Object Qdefault_pane_background_color_or_tiling_pattern_rows;  /* default-pane-background-color-or-tiling-pattern-rows */

static Object array_constant_10;   /* # */

static Object Qlanguage;           /* language */

static Object Kall;                /* :all */

static Object Qcjk_language;       /* cjk-language */

static Object Qinit_string;        /* init-string */

/* SET-UP-TELEWINDOWS-WORKSTATION */
Object set_up_telewindows_workstation(gensym_window)
    Object gensym_window;
{
    Object telewindows_workstation, current_workstation;
    Object current_workstation_window, current_workstation_native_window_qm;
    Object type_of_current_workstation_window, temp, temp_1, temp_2, thing;
    Object set_gensym_plist_element_arg_2;
    Object background_color_or_tiling_pattern_qm, value_qm;
    Declare_special(4);

    x_note_fn_call(76,54);
    telewindows_workstation = make_telewindows_workstation_1(gensym_window);
    SVREF(gensym_window,FIX((SI_Long)2L)) = telewindows_workstation;
    Workstations_in_service = gensym_cons_1(telewindows_workstation,
	    Workstations_in_service);
    if ( !TRUEP(telewindows_twaxl_mode_p()))
	make_window_visible(gensym_window);
    current_workstation = telewindows_workstation;
    PUSH_SPECIAL(Current_workstation,current_workstation,3);
      current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
      PUSH_SPECIAL(Current_workstation_window,current_workstation_window,2);
	current_workstation_native_window_qm = 
		ISVREF(Current_workstation_window,(SI_Long)17L);
	PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		1);
	  type_of_current_workstation_window = 
		  ISVREF(Current_workstation_window,(SI_Long)1L);
	  PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		  0);
	    get_all_x11_events(ISVREF(gensym_window,(SI_Long)17L));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if ( !TRUEP(System_window)) {
	System_window = gensym_window;
	refresh_telewindow(2,gensym_window,ISVREF(gensym_window,(SI_Long)17L));
	temp = c_native_clock_ticks_or_cache(Nil,Nil);
	temp_1 = FIXNUM_ADD(temp,
		get_telewindows_splashscreen_time_as_fixnum_time_interval());
	SVREF(telewindows_workstation,FIX((SI_Long)65L)) = temp_1;
	if (User_specified_telewindows_splashscreen_time_in_seconds_qm && 
		EQ(Verbosity_level,Qverbose))
	    notify_user_at_console(5,string_constant_28,
		    User_specified_telewindows_splashscreen_time_in_seconds_qm,
		    Minimum_telewindows_splashscreen_time_in_seconds,
		    Maximum_telewindows_splashscreen_time_in_seconds,
		    Default_telewindows_splashscreen_time_in_seconds);
    }
    temp_2 = ISVREF(gensym_window,(SI_Long)19L);
    temp = copy_gensym_window_parameters_plist(get_command_line_arguments());
    temp_1 = nconc2(temp_2,nconc2(temp,get_telewindows_miscellaneous_info()));
    SVREF(gensym_window,FIX((SI_Long)19L)) = temp_1;
    if ( !TRUEP(getf(ISVREF(gensym_window,(SI_Long)19L),Quser_name,_))) {
	temp_1 = ISVREF(gensym_window,(SI_Long)19L);
	thing = getf(ISVREF(gensym_window,(SI_Long)19L),Qos_user_name,_);
	set_gensym_plist_element_arg_2 = 
		INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
		copy_text_string(thing) : thing;
	temp_1 = mutate_gensym_plist(temp_1,Quser_name,
		set_gensym_plist_element_arg_2);
    }
    background_color_or_tiling_pattern_qm = 
	    get_background_color_or_tiling_pattern_from_command_line();
    if (background_color_or_tiling_pattern_qm) {
	temp_1 = ISVREF(gensym_window,(SI_Long)19L);
	set_gensym_plist_element_arg_2 = background_color_or_tiling_pattern_qm;
	temp_1 = mutate_gensym_plist(temp_1,
		Qdefault_pane_background_color_or_tiling_pattern_rows,
		set_gensym_plist_element_arg_2);
    }
    temp = ISVREF(gensym_window,(SI_Long)19L);
    adjust_password_hash_if_necessary(temp,
	    get_command_line_keyword_argument(1,array_constant_10));
    value_qm = get_gensym_window_parameter(gensym_window,Qlanguage);
    if (value_qm) {
	temp_1 = T ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)27L)) = temp_1;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qcjk_language);
    if (value_qm) {
	temp_1 = T ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)49L)) = temp_1;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qnetwork);
    if (value_qm) {
	temp_1 = Nil ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)58L)) = temp_1;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qremote_host_name);
    if (value_qm) {
	temp_1 = Nil ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)56L)) = temp_1;
    }
    value_qm = get_gensym_window_parameter(gensym_window,
	    Qremote_port_name_or_number);
    if (value_qm) {
	temp_1 = Nil ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)57L)) = temp_1;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qinit_string);
    if (value_qm) {
	temp_1 = Nil ? intern_text_string(1,
		copy_text_string_with_case_conversion(value_qm,Kall)) : 
		value_qm;
	SVREF(telewindows_workstation,FIX((SI_Long)59L)) = temp_1;
    }
    set_up_initial_telewindows_routing(telewindows_workstation);
    return VALUES_1(telewindows_workstation);
}

/* SET-TELEWINDOWS-WINDOW-PLIST-ELEMENT */
Object set_telewindows_window_plist_element(workstation,indicator,value)
    Object workstation, indicator, value;
{
    Object indicator_1, value_1, ab_loop_list_, temp, temp_1;
    Object set_gensym_plist_element_arg_1, set_gensym_plist_element_arg_2;
    Object svref_new_value;

    x_note_fn_call(76,55);
    indicator_1 = Nil;
    value_1 = Nil;
    ab_loop_list_ = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)19L);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    indicator_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value_1 = CAR(temp);
    if (EQ(indicator_1,indicator)) {
	if (text_string_p(value_1))
	    reclaim_text_string(value_1);
	temp_1 = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)19L);
	set_gensym_plist_element_arg_1 = indicator;
	set_gensym_plist_element_arg_2 = value;
	temp_1 = mutate_gensym_plist(temp_1,set_gensym_plist_element_arg_1,
		set_gensym_plist_element_arg_2);
	return VALUES_1(value);
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp_1 = ISVREF(workstation,(SI_Long)1L);
    svref_new_value = nconc2(gensym_list_2(indicator,value),
	    ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)19L));
    SVREF(temp_1,FIX((SI_Long)19L)) = svref_new_value;
    return VALUES_1(Qnil);
}

static Object Qreroute_problem_report;  /* reroute-problem-report */

static Object Qdesires_connection;  /* desires-connection */

/* GET-TELEWINDOWS-WORKSTATION-READY-TO-CONNECT */
Object get_telewindows_workstation_ready_to_connect(workstation)
    Object workstation;
{
    Object temp, temp_1, fixnum_time_now;

    x_note_fn_call(76,56);
    set_telewindows_window_plist_element(workstation,
	    Qreroute_problem_report,ISVREF(workstation,(SI_Long)77L) ? 
	    copy_text_string(ISVREF(workstation,(SI_Long)77L)) : Nil);
    set_telewindows_window_plist_element(workstation,Qinit_string,
	    ISVREF(workstation,(SI_Long)76L) ? 
	    copy_text_string(ISVREF(workstation,(SI_Long)76L)) : Nil);
    reclaim_gensym_list_1(ISVREF(workstation,(SI_Long)3L));
    SVREF(workstation,FIX((SI_Long)3L)) = Nil;
    SVREF(workstation,FIX((SI_Long)62L)) = Nil;
    temp = ISVREF(workstation,(SI_Long)1L);
    SVREF(temp,FIX((SI_Long)13L)) = Nil;
    temp_1 = Plist_of_corresponding_icp_object_maps_for_font_maps;
    Plist_of_corresponding_icp_object_maps_for_font_maps = Nil;
    reclaim_gensym_tree_1(temp_1);
    fixnum_time_now = c_native_clock_ticks_or_cache(Nil,Nil);
    temp = FIXNUM_ADD(fixnum_time_now,ISVREF(workstation,(SI_Long)61L));
    SVREF(workstation,FIX((SI_Long)67L)) = temp;
    ISVREF(workstation,(SI_Long)68L) = FIX((SI_Long)0L);
    temp_1 = copy_text_string(ISVREF(workstation,(SI_Long)73L));
    temp = make_telewindows_network_pathname(temp_1,ISVREF(workstation,
	    (SI_Long)74L),ISVREF(workstation,(SI_Long)75L));
    SVREF(workstation,FIX((SI_Long)64L)) = temp;
    return VALUES_1(SVREF(workstation,FIX((SI_Long)63L)) = 
	    Qdesires_connection);
}

Object Priority_of_tw_workstation_service = UNBOUND;

/* SERVICE-TELEWINDOWS-WORKSTATIONS */
Object service_telewindows_workstations()
{
    x_note_fn_call(76,57);
    schedule_telewindows_workstations_service();
    return tw_event_loop();
}

Object Telewindows_service_workstations_task_qm = UNBOUND;

static Object Qservice_telewindows_workstations_once;  /* service-telewindows-workstations-once */

/* SCHEDULE-TELEWINDOWS-WORKSTATIONS-SERVICE */
Object schedule_telewindows_workstations_service()
{
    Object current_task_schedule_modify_arg_2;
    Object current_task_schedule_modify_arg_8, old_structure_being_reclaimed;
    Object temp, svref_new_value, def_structure_schedule_task_variable, task;
    Object ctask, p, v, q, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(76,58);
    current_task_schedule_modify_arg_2 = Priority_of_tw_workstation_service;
    current_task_schedule_modify_arg_8 = 
	    SYMBOL_FUNCTION(Qservice_telewindows_workstations_once);
    if (Telewindows_service_workstations_task_qm) {
	if (EQ(Telewindows_service_workstations_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(Telewindows_service_workstations_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(Telewindows_service_workstations_task_qm);
	inline_note_reclaim_cons(Telewindows_service_workstations_task_qm,Nil);
	old_structure_being_reclaimed = Structure_being_reclaimed;
	Structure_being_reclaimed = Telewindows_service_workstations_task_qm;
	reclaim_schedule_task_args(ISVREF(Telewindows_service_workstations_task_qm,
		(SI_Long)9L));
	temp = Telewindows_service_workstations_task_qm;
	SVREF(temp,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed;
	temp = Telewindows_service_workstations_task_qm;
	svref_new_value = Chain_of_available_schedule_tasks;
	SVREF(temp,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_schedule_tasks = 
		Telewindows_service_workstations_task_qm;
    }
    def_structure_schedule_task_variable = Chain_of_available_schedule_tasks;
    if (def_structure_schedule_task_variable) {
	Chain_of_available_schedule_tasks = 
		ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
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
    SVREF(task,FIX((SI_Long)4L)) = current_task_schedule_modify_arg_2;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    g2_p =  !TRUEP(T);
    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
	    Current_real_time,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    SVREF(task,FIX((SI_Long)7L)) = Qservice_telewindows_workstations_once;
    SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
    ISVREF(task,(SI_Long)10L) = FIX((SI_Long)0L);
    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
    if (ctask);
    else
	ctask = System_is_running;
    p = ISVREF(task,(SI_Long)4L);
    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
    q = ISVREF(v,IFIX(p));
    gensymed_symbol = ISVREF(q,(SI_Long)1L);
    def_structure_queue_element_variable = Chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	Chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = q;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
	    gensymed_symbol;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
    gensymed_symbol_1 = def_structure_queue_element_variable;
    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
    SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
    SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
	Priority_of_next_task = p;
    Telewindows_service_workstations_task_qm = task;
    return VALUES_1(Telewindows_service_workstations_task_qm);
}

/* SERVICE-TELEWINDOWS-WORKSTATIONS-ONCE */
Object service_telewindows_workstations_once()
{
    Object old_structure_being_reclaimed, temp, svref_new_value;
    Object more_events_in_queue_qm, fixnum_time_now, temp_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(76,59);
    if (Telewindows_service_workstations_task_qm) {
	if (EQ(Telewindows_service_workstations_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(Telewindows_service_workstations_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(Telewindows_service_workstations_task_qm);
	inline_note_reclaim_cons(Telewindows_service_workstations_task_qm,Nil);
	old_structure_being_reclaimed = Structure_being_reclaimed;
	Structure_being_reclaimed = Telewindows_service_workstations_task_qm;
	reclaim_schedule_task_args(ISVREF(Telewindows_service_workstations_task_qm,
		(SI_Long)9L));
	temp = Telewindows_service_workstations_task_qm;
	SVREF(temp,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed;
	temp = Telewindows_service_workstations_task_qm;
	svref_new_value = Chain_of_available_schedule_tasks;
	SVREF(temp,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_schedule_tasks = 
		Telewindows_service_workstations_task_qm;
    }
    temp = Nil;
    Telewindows_service_workstations_task_qm = temp;
    more_events_in_queue_qm = Nil;
    more_events_in_queue_qm = service_current_telewindows_workstation();
    fixnum_time_now = c_native_clock_ticks_or_cache(Nil,Nil);
    if (IFIX(Clogged_count) > (SI_Long)13455L) {
	Clogged_count = FIX((SI_Long)0L);
	enhance_graphics_colors();
    }
    if (FIXNUM_GE(fixnum_time_now,Time_of_last_expiration_check))
	temp_1 = FIXNUM_MINUS(fixnum_time_now,Time_of_last_expiration_check);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_expiration_check));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp_1 = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GT(temp_1,Tw_expiration_check_interval)) {
	warn_of_tw_expiration_if_necessary_1();
	Time_of_last_expiration_check = fixnum_time_now;
    }
    if (FIXNUM_GE(fixnum_time_now,Time_of_last_thrashing_cost_update))
	temp_1 = FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp_1 = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GT(temp_1,Decache_occurred_since_last_update_qm ? 
	    Thrashing_cost_update_interval : 
	    Long_thrashing_cost_update_interval))
	update_memory_limits_now(fixnum_time_now);
    if (more_events_in_queue_qm)
	return schedule_telewindows_workstations_service();
    else
	return VALUES_1(Nil);
}

Object Tw_scheduled_tasks_time_limit = UNBOUND;

/* RUN-ONE-TW-SCHEDULER-CYCLE */
Object run_one_tw_scheduler_cycle()
{
    Object task_scheduling_start_time, time_slice_start_time;
    Object no_tasks_were_executed_this_pass, temp_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp;
    Declare_special(1);
    XDeclare_area(2);
    XDeclare_frontier(2);

    x_note_fn_call(76,60);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	task_scheduling_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	time_slice_start_time = task_scheduling_start_time;
	PUSH_SPECIAL(Time_slice_start_time,time_slice_start_time,0);
	  no_tasks_were_executed_this_pass = Nil;
	next_loop:
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	      no_tasks_were_executed_this_pass =  
		      !TRUEP(dequeue_and_execute_next_task()) ? T : Nil;
	  POP_LOCAL_ALLOCATION(0,0);
	  temp = TRUEP(no_tasks_were_executed_this_pass);
	  if (temp);
	  else {
	      Time_slice_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	      gensymed_symbol = IFIX(Time_slice_start_time);
	      gensymed_symbol_1 = IFIX(task_scheduling_start_time);
	      if (gensymed_symbol >= gensymed_symbol_1)
		  temp_1 = FIX(gensymed_symbol - gensymed_symbol_1);
	      else {
		  gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		  gensymed_symbol = gensymed_symbol + 
			  IFIX(Most_positive_fixnum);
		  temp_1 = FIX(gensymed_symbol + (SI_Long)1L);
	      }
	      temp = FIXNUM_GE(temp_1,Tw_scheduled_tasks_time_limit);
	  }
	  if (temp)
	      goto end_loop;
	  goto next_loop;
	end_loop:
	  service_telewindows_workstations_once();
	  enqueue_scheduler_events_if_necessary( 
		  !TRUEP(no_tasks_were_executed_this_pass) ? T : Nil);
	  temp_1 = Qnil;
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(1,1);
    return VALUES_1(temp_1);
}

static Object Qab_gensym;          /* gensym */

/* SERVICE-CURRENT-TELEWINDOWS-WORKSTATION */
Object service_current_telewindows_workstation()
{
    Object workstation, more_to_do, w, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, new_cons, gensymed_symbol;
    Object copy_of_workstations_in_service, gensym_pop_store, cons_1;
    Object next_cons, cdr_new_value, current_workstation;
    Object current_workstation_window, current_workstation_native_window_qm;
    Object type_of_current_workstation_window, temp;
    Declare_special(4);

    x_note_fn_call(76,61);
    workstation = Nil;
    more_to_do = Nil;
    w = Nil;
    ab_loop_list_ = Workstations_in_service;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    w = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = w;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    copy_of_workstations_in_service = ab_loopvar_;
    goto end;
    copy_of_workstations_in_service = Qnil;
  end:;
  next_loop_1:
    if ( !TRUEP(copy_of_workstations_in_service))
	goto end_loop_1;
    gensym_pop_store = Nil;
    cons_1 = copy_of_workstations_in_service;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	Available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    copy_of_workstations_in_service = next_cons;
    workstation = gensym_pop_store;
    if (memq_function(workstation,Workstations_in_service)) {
	current_workstation = workstation;
	PUSH_SPECIAL(Current_workstation,current_workstation,3);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  2);
	    current_workstation_native_window_qm = 
		    ISVREF(Current_workstation_window,(SI_Long)17L);
	    PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		    1);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		      0);
		temp = service_current_telewindows_workstation_1();
		if (temp);
		else
		    temp = more_to_do;
		more_to_do = temp;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(more_to_do);
    return VALUES_1(Qnil);
}

static Object string_constant_29;  /* "[Telewindows: Unable to connect to host ~s at port ~a via protocol ~a~a]" */

static Object Qfailure_to_connect;  /* failure-to-connect */

/* SERVICE-CURRENT-TELEWINDOWS-WORKSTATION-1 */
Object service_current_telewindows_workstation_1()
{
    Object temp, socket_1, temp_1, temp_2;

    x_note_fn_call(76,62);
    if (IFIX(Clogged_count) >= (SI_Long)0L && 
	    EQ(ISVREF(Current_workstation,(SI_Long)78L),FIX((SI_Long)-1L)))
	Clogged_count = FIX((SI_Long)-1L);
    temp = ISVREF(Current_workstation,(SI_Long)63L);
    if (EQ(temp,Qbeing_rerouted)) {
	socket_1 = ISVREF(Current_workstation,(SI_Long)62L);
	if ( !(socket_1 && (member_eql(socket_1,Active_icp_sockets) || 
		icp_connection_open_p(socket_1))))
	    return get_telewindows_workstation_ready_to_connect(Current_workstation);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(temp,Qdesires_connection))
	return try_to_connect_telewindows_workstation(Current_workstation);
    else if (EQ(temp,Qconnected_and_awaiting_license_level))
	return try_to_obtain_telewindows_license_level(Current_workstation);
    else if (EQ(temp,Qconnected))
	return poll_workstation();
    else if (EQ(temp,Qconnecting))
	return get_all_x11_events(Current_workstation_native_window_qm);
    else if (EQ(temp,Qdisconnected))
	return VALUES_1(Nil);
    else if (EQ(temp,Qfailed_to_connect)) {
	if ( !EQ(Verbosity_level,Qsilent)) {
	    temp = ISVREF(Current_workstation,(SI_Long)74L);
	    if (temp);
	    else
		temp = string_constant_26;
	    temp_1 = ISVREF(Current_workstation,(SI_Long)75L);
	    if (temp_1);
	    else
		temp_1 = string_constant_26;
	    temp_2 = ISVREF(Current_workstation,(SI_Long)73L);
	    if (temp_2);
	    else
		temp_2 = string_constant_26;
	    notify_user_at_console(5,string_constant_29,temp,temp_1,temp_2,
		    secure_icp_string(2,Kuse_default,T));
	}
	if (ISVREF(Current_workstation,(SI_Long)69L))
	    return send_telewindows_home(Current_workstation);
	else
	    return abort_telewindows_top_level(Qfailure_to_connect);
    }
    else
	return VALUES_1(Qnil);
}

/* ACCEPT-TELEWINDOWS-CONNECTION-LICENSE-LEVEL */
Object accept_telewindows_connection_license_level(gensym_window,license_level)
    Object gensym_window, license_level;
{
    Object telewindows_workstation;

    x_note_fn_call(76,63);
    telewindows_workstation = ISVREF(gensym_window,(SI_Long)2L);
    return VALUES_1(SVREF(telewindows_workstation,FIX((SI_Long)78L)) = 
	    license_level);
}

static Object Qsession_id;         /* session-id */

/* ACCEPT-SAVED-USER-SETTINGS-FOR-TELEWINDOWS */
Object accept_saved_user_settings_for_telewindows(gensym_window,
	    user_settings_plist)
    Object gensym_window, user_settings_plist;
{
    Object workstation, indicator, value, ab_loop_list_, value_copy, temp;
    Object session_id_qm;

    x_note_fn_call(76,64);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    indicator = Nil;
    value = Nil;
    ab_loop_list_ = user_settings_plist;
    value_copy = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    indicator = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    value_copy = text_string_p(value) ? copy_text_string(value) : value;
    set_telewindows_window_plist_element(workstation,indicator,value_copy);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    session_id_qm = get_gensym_window_parameter(gensym_window,Qsession_id);
    if (session_id_qm)
	return VALUES_1(FIX(g2ext_x11_tell_control_our_session_id(IFIX(session_id_qm))));
    else
	return VALUES_1(Nil);
}

static Object Qtelewindows_connection_license_level;  /* telewindows-connection-license-level */

/* ACCEPT-TELEWINDOWS-CONNECTION-LICENSE-INFO */
Object accept_telewindows_connection_license_info(gensym_window,
	    telewindows_connection_license_info)
    Object gensym_window, telewindows_connection_license_info;
{
    Object telewindows_workstation, svref_new_value;

    x_note_fn_call(76,65);
    telewindows_workstation = ISVREF(gensym_window,(SI_Long)2L);
    svref_new_value = getf(telewindows_connection_license_info,
	    Qtelewindows_connection_license_level,_);
    SVREF(telewindows_workstation,FIX((SI_Long)78L)) = svref_new_value;
    return VALUES_1(SVREF(telewindows_workstation,FIX((SI_Long)79L)) = 
	    telewindows_connection_license_info);
}

/* IDLE-TELEWINDOWS */
Object idle_telewindows(workstation)
    Object workstation;
{
    x_note_fn_call(76,66);
    g2_event_wait();
    return VALUES_1(SVREF(workstation,FIX((SI_Long)41L)) = T);
}

/* TW-PRIORITY-OF-DATA-SERVICE-FUNCTION */
Object tw_priority_of_data_service_function()
{
    x_note_fn_call(76,67);
    return VALUES_1(FIX((SI_Long)4L));
}

static Object Qrun_telewindows;    /* run-telewindows */

/* RUN-TELEWINDOWS-PROCESS-TOP-LEVEL */
Object run_telewindows_process_top_level(native_window)
    Object native_window;
{
    x_note_fn_call(76,68);
    return run_system_process(Qtelewindows,native_window,Qrun_telewindows);
}

/* LAUNCH-TELEWINDOWS */
Object launch_telewindows()
{
    x_note_fn_call(76,69);
    return launch_system_process(Qtelewindows);
}

/* TW-HANDLE-SPAWN-REMOTE-COMMAND-LINE-PROCESS */
Object tw_handle_spawn_remote_command_line_process(index_of_result_parameter,
	    command_line)
    Object index_of_result_parameter, command_line;
{
    Object argument_simple_p, simple_command_line, amf_available_array_cons_qm;
    Object amf_array, temp, svref_new_value, amf_result, incff_1_arg;
    Object new_float, temp_1, process_id, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double aref_new_value, gensymed_symbol_1;
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(76,70);
    argument_simple_p = Nil;
    simple_command_line = argument_simple_p ? command_line : 
	    copy_text_string(command_line);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	temp_1 = c_spawn_command_line_process(simple_command_line);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	process_id = new_float;
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = T;
	    disable_resumability = temp_1;
	    PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_spawn_remote_process_reply(index_of_result_parameter,
					    process_id);
				    end_icp_message_group();
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
	reclaim_managed_simple_float_array_of_length_1(process_id);
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(argument_simple_p))
	return reclaim_text_string(simple_command_line);
    else
	return VALUES_1(Nil);
}

/* TW-HANDLE-SPAWN-REMOTE-EXECUTABLE-PROCESS */
Object tw_handle_spawn_remote_executable_process(index_of_result_parameter,
	    command_line)
    Object index_of_result_parameter, command_line;
{
    Object argument_simple_p, simple_command_line, amf_available_array_cons_qm;
    Object amf_array, temp, svref_new_value, amf_result, incff_1_arg;
    Object new_float, temp_1, process_id, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double aref_new_value, gensymed_symbol_1;
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(76,71);
    argument_simple_p = Nil;
    simple_command_line = argument_simple_p ? command_line : 
	    copy_text_string(command_line);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	temp_1 = c_spawn_executable_process(simple_command_line);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	process_id = new_float;
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = T;
	    disable_resumability = temp_1;
	    PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_spawn_remote_process_reply(index_of_result_parameter,
					    process_id);
				    end_icp_message_group();
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
	reclaim_managed_simple_float_array_of_length_1(process_id);
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(argument_simple_p))
	return reclaim_text_string(simple_command_line);
    else
	return VALUES_1(Nil);
}

/* TW-HANDLE-REMOTE-PROCESS-EXISTS-P */
Object tw_handle_remote_process_exists_p(index_of_result_parameter,process_id)
    Object index_of_result_parameter, process_id;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    SI_Long existence_status;
    double process_id_value, gensymed_symbol_1;
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(76,72);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id_value = DFLOAT_ISAREF_1(process_id,(SI_Long)0L);
	existence_status = g2ext_process_exists(process_id_value);
	reclaim_managed_simple_float_array_of_length_1(process_id);
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = T;
	    disable_resumability = temp;
	    PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    temp = 
					    send_icp_remote_process_exists_p_reply(index_of_result_parameter,
					    FIX(existence_status));
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				result = VALUES_1(temp);
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
    return result;
}

/* TW-HANDLE-KILL-REMOTE-PROCESS */
Object tw_handle_kill_remote_process(index_of_result_parameter,process_id)
    Object index_of_result_parameter, process_id;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    SI_Long kill_status;
    double process_id_value, arg, arg_1, gensymed_symbol_1;
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(76,73);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id_value = DFLOAT_ISAREF_1(process_id,(SI_Long)0L);
	arg = process_id_value;
	arg_1 = 0.0;
	kill_status = arg == arg_1 &&  !inline_nanp_for_comparison(arg) && 
		 !inline_nanp_for_comparison(arg_1) ? (SI_Long)-1L : 
		g2ext_kill_spawned_command_line(process_id_value);
	reclaim_managed_simple_float_array_of_length_1(process_id);
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = T;
	    disable_resumability = temp;
	    PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    temp = 
					    send_icp_kill_remote_process_reply(index_of_result_parameter,
					    FIX(kill_status));
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				result = VALUES_1(temp);
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
    return result;
}

/* ABORT-TELEWINDOWS-TOP-LEVEL */
Object abort_telewindows_top_level(reason_qm)
    Object reason_qm;
{
    x_note_fn_call(76,74);
    return shut_down_ab_process(1,reason_qm);
}

static Object string_constant_30;  /* "(unknown network type)" */

static Object string_constant_31;  /* "~%[Telewindows: no ~a listener at host ~s for port ~s]~%" */

static Object array_constant_11;   /* # */

static Object string_constant_32;  /* "Unable to connect to G2.  No ~a listener at host ~s for port ~s." */

static Object string_constant_33;  /* "~a connection to host ~s at port ~a" */

static Object Qrequested;          /* requested */

static Object string_constant_34;  /* "closed as requested." */

static Object Qbroken_while_receiving;  /* broken-while-receiving */

static Object string_constant_35;  /* "broken while receiving data." */

static Object Qbroken_while_transmitting;  /* broken-while-transmitting */

static Object string_constant_36;  /* "broken while transmitting data." */

static Object list_constant;       /* # */

static Object Qprotocol_out_of_synch_1;  /* protocol-out-of-synch-1 */

static Object Qprotocol_out_of_synch_2;  /* protocol-out-of-synch-2 */

static Object Qprotocol_out_of_synch_3;  /* protocol-out-of-synch-3 */

static Object Qprotocol_out_of_synch_4;  /* protocol-out-of-synch-4 */

static Object Qprotocol_out_of_synch_5;  /* protocol-out-of-synch-5 */

static Object Qprotocol_out_of_synch_6;  /* protocol-out-of-synch-6 */

static Object string_constant_37;  /* "broken: protocol out of synch (case ~s)." */

static Object Qunknown_message;    /* unknown-message */

static Object string_constant_38;  /* "broken: received a message of a type that is not known." */

static Object string_constant_39;  /* "broken." */

static Object string_constant_40;  /* "[Telewindows: ~a ~a]" */

static Object list_constant_1;     /* # */

/* HANDLE-TELEWINDOWS-SHUTDOWN */
Object handle_telewindows_shutdown(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object reason_qm, workstation_qm, host_name, network, port;
    volatile Object lead_in_text_string;
    volatile Object extra_text_string_1_qm;
    Object temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(76,75);
    SAVE_STACK();
    reason_qm = ISVREF(icp_socket,(SI_Long)9L);
    workstation_qm = get_workstation_for_icp_socket(icp_socket);
    if (workstation_qm);
    else
	workstation_qm = ISVREF(icp_socket,(SI_Long)23L);
    host_name = workstation_qm ? ISVREF(workstation_qm,(SI_Long)74L) : Nil;
    if (host_name);
    else
	host_name = string_constant_26;
    network = workstation_qm ? ISVREF(workstation_qm,(SI_Long)73L) : Nil;
    if (network);
    else
	network = string_constant_30;
    port = workstation_qm ? ISVREF(workstation_qm,(SI_Long)75L) : Nil;
    if (port);
    else
	port = string_constant_26;
    if (EQ(reason_qm,Qbeing_rerouted)) {
	if (workstation_qm)
	    SVREF(workstation_qm,FIX((SI_Long)63L)) = reason_qm;
    }
    else if (EQ(reason_qm,Qnot_established)) {
	if ( !EQ(Verbosity_level,Qsilent)) {
	    notify_user_at_console(4,string_constant_31,network,host_name,
		    port);
	    c_message_box(FIX((SI_Long)0L),array_constant_11,
		    tformat_text_string(4,string_constant_32,network,
		    host_name,port),Mb_ok,FIX((SI_Long)3L));
	}
	SVREF(workstation_qm,FIX((SI_Long)63L)) = Qfailed_to_connect;
    }
    else {
	lead_in_text_string = Qunbound_in_protected_let;
	extra_text_string_1_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    lead_in_text_string = tformat_text_string(4,string_constant_33,
		    network,host_name,port);
	    extra_text_string_1_qm = Nil;
	    SVREF(workstation_qm,FIX((SI_Long)63L)) = Qdisconnected;
	    if ( !EQ(Verbosity_level,Qsilent)) {
		temp = lead_in_text_string;
		if (EQ(reason_qm,Qrequested))
		    temp_1 = string_constant_34;
		else if (EQ(reason_qm,Qbroken_while_receiving))
		    temp_1 = string_constant_35;
		else if (EQ(reason_qm,Qbroken_while_transmitting))
		    temp_1 = string_constant_36;
		else if (member_eql(reason_qm,list_constant)) {
		    if (EQ(reason_qm,Qprotocol_out_of_synch_1))
			temp_1 = FIX((SI_Long)1L);
		    else if (EQ(reason_qm,Qprotocol_out_of_synch_2))
			temp_1 = FIX((SI_Long)2L);
		    else if (EQ(reason_qm,Qprotocol_out_of_synch_3))
			temp_1 = FIX((SI_Long)3L);
		    else if (EQ(reason_qm,Qprotocol_out_of_synch_4))
			temp_1 = FIX((SI_Long)4L);
		    else if (EQ(reason_qm,Qprotocol_out_of_synch_5))
			temp_1 = FIX((SI_Long)5L);
		    else if (EQ(reason_qm,Qprotocol_out_of_synch_6))
			temp_1 = FIX((SI_Long)6L);
		    else
			temp_1 = Qnil;
		    extra_text_string_1_qm = tformat_text_string(2,
			    string_constant_37,temp_1);
		    temp_1 = extra_text_string_1_qm;
		}
		else if (EQ(reason_qm,Qunknown_message))
		    temp_1 = string_constant_38;
		else
		    temp_1 = string_constant_39;
		notify_user_at_console(3,string_constant_40,temp,temp_1);
	    }
	}
	POP_UNWIND_PROTECT(0);
	if (extra_text_string_1_qm) {
	    if ( !EQ(extra_text_string_1_qm,Qunbound_in_protected_let))
		reclaim_text_string(extra_text_string_1_qm);
	}
	if (lead_in_text_string) {
	    if ( !EQ(lead_in_text_string,Qunbound_in_protected_let))
		reclaim_text_string(lead_in_text_string);
	}
	CONTINUE_UNWINDING(0);
    }
    if ( !TRUEP(memq_function(reason_qm,list_constant_1)))
	g2ext_x11_tell_control_our_session_id((SI_Long)-1L);
    schedule_telewindows_workstations_service();
    if ( !(EQ(reason_qm,Qbeing_rerouted) || EQ(reason_qm,Qnot_established))) {
	result = abort_telewindows_top_level(reason_qm);
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qauthorization_failure;  /* authorization-failure */

/* ABORT-TELEWINDOWS-FOR-PROTOCOL-OUT-OF-SYNCH-CASE-6 */
Object abort_telewindows_for_protocol_out_of_synch_case_6()
{
    Object icp_socket;

    x_note_fn_call(76,76);
    if (Workstations_in_service) {
	icp_socket = ISVREF(FIRST(Workstations_in_service),(SI_Long)62L);
	SVREF(icp_socket,FIX((SI_Long)9L)) = Qprotocol_out_of_synch_6;
	handle_telewindows_shutdown(icp_socket,Nil);
    }
    Workstations_in_service = Nil;
    return abort_telewindows_top_level(Qauthorization_failure);
}

/* SEND-TELEWINDOWS-WORKSTATION-EVENT */
Object send_telewindows_workstation_event(workstation,local_event)
    Object workstation, local_event;
{
    Object socket_qm, gensym_window, icp_port, code, x, y, timestamp, plist_qm;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);
    Object result;

    x_note_fn_call(76,77);
    socket_qm = ISVREF(workstation,(SI_Long)62L);
    if (socket_qm && icp_connection_open_p(socket_qm)) {
	gensym_window = ISVREF(workstation,(SI_Long)1L);
	icp_port = ISVREF(gensym_window,(SI_Long)13L);
	code = ISVREF(local_event,(SI_Long)1L);
	x = ISVREF(local_event,(SI_Long)3L);
	y = ISVREF(local_event,(SI_Long)4L);
	timestamp = ISVREF(local_event,(SI_Long)2L);
	plist_qm = ISVREF(local_event,(SI_Long)7L);
	if (plist_qm && 
		FIXNUM_LT(Icp_window_protocol_supports_event_plists,
		ISVREF(gensym_window,(SI_Long)11L))) {
	    current_icp_port = icp_port;
	    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = T;
		disable_resumability = temp;
		PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_1 = 0.0;
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					temp = 
						send_icp_extended_telewindows_workstation_event(workstation,
						code,x,y,timestamp,plist_qm);
					end_icp_message_group();
				    }
				    else
					temp = Nil;
				    result = VALUES_1(temp);
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
	else {
	    current_icp_port = icp_port;
	    PUSH_SPECIAL(Current_icp_port,current_icp_port,11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL(Current_icp_socket,current_icp_socket,10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = T;
		disable_resumability = temp;
		PUSH_SPECIAL(Disable_resumability,disable_resumability,9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL(Number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL(Icp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL(Icp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(Icp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL(Number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL(Current_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL(Current_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL(Number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL(Writing_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_1 = 0.0;
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					temp = 
						send_icp_telewindows_workstation_event(workstation,
						code,x,y,timestamp);
					end_icp_message_group();
				    }
				    else
					temp = Nil;
				    result = VALUES_1(temp);
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
    }
    else
	return VALUES_1(Nil);
}

Object Current_telewindows_baseline = UNBOUND;

static Object Qwhite;              /* white */

static Object Qwrite_list_of_text_lines_in_current_window;  /* write-list-of-text-lines-in-current-window */

/* WRITE-LIST-OF-TEXT-LINES-TO-GENSYM-WINDOW */
Object write_list_of_text_lines_to_gensym_window(gensym_window,
	    list_of_text_lines,font_size,clear_window_qm,new_paragraph_qm)
    Object gensym_window, list_of_text_lines, font_size, clear_window_qm;
    Object new_paragraph_qm;
{
    Object left_edge_of_window, top_edge_of_window, right_edge_of_window;
    Object bottom_edge_of_window;

    x_note_fn_call(76,78);
    left_edge_of_window = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_window = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_window = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_window = ISVREF(gensym_window,(SI_Long)10L);
    if (clear_window_qm) {
	clear_window(2,gensym_window,Qwhite);
	Current_telewindows_baseline = Default_telewindows_upper_margin;
    }
    return update_window(9,gensym_window,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    Qwrite_list_of_text_lines_in_current_window,list_of_text_lines,
	    font_size,new_paragraph_qm);
}

static Object Qblack;              /* black */

static Object Qsmall;              /* small */

static Object Qlarge;              /* large */

static Object Qextra_large;        /* extra-large */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

/* WRITE-LIST-OF-TEXT-LINES-IN-CURRENT-WINDOW */
Object write_list_of_text_lines_in_current_window(list_of_text_lines,
	    font_size,new_paragraph_qm)
    Object list_of_text_lines, font_size, new_paragraph_qm;
{
    Object left_edge_of_window, top_edge_of_window, right_edge_of_window;
    Object bottom_edge_of_window, color_value_1, color_value_2, word_spacing;
    Object line_spacing, font_map, text_line, ab_loop_list_;
    SI_Long color_difference, distance_from_left_edge_of_window;
    SI_Long paragraph_spacing;

    x_note_fn_call(76,79);
    left_edge_of_window = ISVREF(Current_window,(SI_Long)7L);
    top_edge_of_window = ISVREF(Current_window,(SI_Long)8L);
    right_edge_of_window = ISVREF(Current_window,(SI_Long)9L);
    bottom_edge_of_window = ISVREF(Current_window,(SI_Long)10L);
    color_value_1 = map_to_color_value(Qblack);
    color_value_2 = map_to_color_value(Qwhite);
    color_difference = IFIX(FIXNUM_LOGXOR(color_value_1,color_value_2));
    distance_from_left_edge_of_window = (SI_Long)50L;
    paragraph_spacing = (SI_Long)20L;
    if (EQ(font_size,Qsmall))
	word_spacing = FIX((SI_Long)5L);
    else if (EQ(font_size,Qlarge))
	word_spacing = FIX((SI_Long)6L);
    else if (EQ(font_size,Qextra_large))
	word_spacing = FIX((SI_Long)6L);
    else
	word_spacing = Qnil;
    if (EQ(font_size,Qsmall))
	line_spacing = FIX((SI_Long)20L);
    else if (EQ(font_size,Qlarge))
	line_spacing = FIX((SI_Long)24L);
    else if (EQ(font_size,Qextra_large))
	line_spacing = FIX((SI_Long)32L);
    else
	line_spacing = Qnil;
    if (EQ(font_size,Qsmall))
	font_map = list_constant_2;
    else if (EQ(font_size,Qlarge))
	font_map = list_constant_3;
    else if (EQ(font_size,Qextra_large))
	font_map = list_constant_4;
    else
	font_map = Qnil;
    if (new_paragraph_qm)
	Current_telewindows_baseline = 
		FIX(IFIX(Current_telewindows_baseline) + paragraph_spacing);
    text_line = Nil;
    ab_loop_list_ = list_of_text_lines;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_line = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    Current_telewindows_baseline = FIXNUM_ADD(Current_telewindows_baseline,
	    line_spacing);
    add_from_line_of_text_to_current_window(Nil,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    text_line,FIX(IFIX(word_spacing) << (SI_Long)8L),font_map,
	    FIX(color_difference),FIX((SI_Long)4096L),FIX((SI_Long)4096L),
	    FIX(IFIX(left_edge_of_window) + 
	    distance_from_left_edge_of_window),
	    FIXNUM_ADD(top_edge_of_window,Current_telewindows_baseline));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qpaint_telewindows_window_with_credits_in_current_window;  /* paint-telewindows-window-with-credits-in-current-window */

/* PAINT-TELEWINDOWS-WINDOW-WITH-CREDITS */
Object paint_telewindows_window_with_credits(gensym_window)
    Object gensym_window;
{
    Object left_edge_of_window, top_edge_of_window, right_edge_of_window;
    Object bottom_edge_of_window;

    x_note_fn_call(76,80);
    left_edge_of_window = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_window = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_window = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_window = ISVREF(gensym_window,(SI_Long)10L);
    clear_window(2,gensym_window,Qwhite);
    return update_window(6,gensym_window,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    Qpaint_telewindows_window_with_credits_in_current_window);
}

Object Tw_copyright_boilerplate_lines_of_text = UNBOUND;

static Object list_constant_5;     /* # */

static Object array_constant_12;   /* # */

static Object Qsystem_version;     /* system-version */

/* PAINT-TELEWINDOWS-WINDOW-WITH-CREDITS-IN-CURRENT-WINDOW */
Object paint_telewindows_window_with_credits_in_current_window()
{
    Object left_edge_of_window, top_edge_of_window, right_edge_of_window;
    Object bottom_edge_of_window, color_value_1, color_value_2;
    Object monumental_font_map, font_map, fine_print_font_map, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temporary_text_lines_cons, text_lines, text_line, ab_loop_list_;
    Object baseline_in_window, ab_loop_iter_flag_;
    SI_Long color_difference, word_spacing, scale, temp, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(76,81);
    left_edge_of_window = ISVREF(Current_window,(SI_Long)7L);
    top_edge_of_window = ISVREF(Current_window,(SI_Long)8L);
    right_edge_of_window = ISVREF(Current_window,(SI_Long)9L);
    bottom_edge_of_window = ISVREF(Current_window,(SI_Long)10L);
    color_value_1 = map_to_color_value(Qblack);
    color_value_2 = map_to_color_value(Qwhite);
    color_difference = IFIX(FIXNUM_LOGXOR(color_value_1,color_value_2));
    monumental_font_map = list_constant_5;
    font_map = list_constant_3;
    fine_print_font_map = list_constant_2;
    word_spacing = (SI_Long)6144L;
    scale = (SI_Long)4096L;
    add_from_line_of_text_to_current_window(Nil,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    array_constant_11,FIX((SI_Long)6144L),monumental_font_map,
	    FIX(color_difference),FIX(scale),FIX(scale),
	    FIX(IFIX(left_edge_of_window) + (SI_Long)100L),
	    FIX(IFIX(top_edge_of_window) + (SI_Long)150L));
    temp = IFIX(left_edge_of_window) + (SI_Long)100L;
    temp_1 = FIX(temp + IFIX(compute_width_of_text_line(5,
	    array_constant_11,Nil,Nil,monumental_font_map,FIX(word_spacing))));
    add_from_line_of_text_to_current_window(Nil,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    array_constant_12,FIX(word_spacing),font_map,
	    FIX(color_difference),FIX(scale),FIX(scale),temp_1,
	    FIX(IFIX(top_edge_of_window) + (SI_Long)150L - (SI_Long)41L));
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      twrite_system_version(1,get(Current_system_name,
		      Qsystem_version,_));
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temporary_text_lines_cons = gensym_cons_1(temp_1,Nil);
    text_lines = nconc2(temporary_text_lines_cons,
	    Tw_copyright_boilerplate_lines_of_text);
    text_line = Nil;
    ab_loop_list_ = text_lines;
    baseline_in_window = FIX(IFIX(top_edge_of_window) + (SI_Long)200L);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_line = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	baseline_in_window = FIX(IFIX(baseline_in_window) + (SI_Long)18L);
    add_from_line_of_text_to_current_window(Nil,left_edge_of_window,
	    top_edge_of_window,right_edge_of_window,bottom_edge_of_window,
	    text_line,FIX((SI_Long)1024L),fine_print_font_map,
	    FIX(color_difference),FIX(scale),FIX(scale),
	    FIX(IFIX(left_edge_of_window) + (SI_Long)150L),baseline_in_window);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    reclaim_text_string(FIRST(temporary_text_lines_cons));
    reclaim_gensym_cons_1(temporary_text_lines_cons);
    return VALUES_1(Qnil);
}

static Object string_constant_41;  /* "[Telewindows: connection to ~s ~s is clogged.]" */

/* TELEWINDOWS-CONNECTION-CLOGGED? */
Object telewindows_connection_clogged_qm(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    Object clogged_count_new_value, temp, temp_1, workstation_qm;
    char temp_2;

    x_note_fn_call(76,82);
    if (IFIX(Clogged_count) == (SI_Long)5000L)
	telewindows_screen_list_too_big();
    else if (IFIX(Clogged_count) == (SI_Long)10000L)
	cache_icon_in_system_table();
    if (IFIX(Clogged_count) > (SI_Long)0L) {
	clogged_count_new_value = FIXNUM_ADD1(Clogged_count);
	Clogged_count = clogged_count_new_value;
    }
    temp = ISVREF(icp_socket,(SI_Long)21L);
    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)9L ? TRUEP(T) : TRUEP(Nil))
	return VALUES_1(Nil);
    else {
	if ( !TRUEP(ISVREF(i_am_alive_info,(SI_Long)2L))) {
	    temp = number_of_outstanding_message_groups(i_am_alive_info);
	    temp_2 = FIXNUM_GT(temp,
		    Telewindows_max_number_of_message_groups_before_clogged);
	    if (temp_2);
	    else
		temp_2 = FIXNUM_GT(ISVREF(i_am_alive_info,(SI_Long)14L),
			Telewindows_max_number_of_icp_bytes_before_clogged);
	}
	else {
	    temp = number_of_outstanding_message_groups(i_am_alive_info);
	    temp_2 =  !(FIXNUM_LT(temp,
		    Telewindows_min_number_of_message_groups_before_unclogged) 
		    && FIXNUM_LT(ISVREF(i_am_alive_info,(SI_Long)14L),
		    Telewindows_min_number_of_icp_bytes_before_unclogged));
	}
	if (temp_2) {
	    workstation_qm = get_workstation_for_icp_socket(icp_socket);
	    if (workstation_qm) {
		if ( !EQ(Verbosity_level,Qsilent))
		    notify_user_at_console(3,string_constant_41,
			    ISVREF(workstation_qm,(SI_Long)74L),
			    ISVREF(workstation_qm,(SI_Long)75L));
	    }
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* TELEWINDOWS-AUTHORIZED-FOR-JAPANESE-P */
Object telewindows_authorized_for_japanese_p(gensym_window)
    Object gensym_window;
{
    Object workstation, level_qm, temp, code;
    SI_Long gensymed_symbol;

    x_note_fn_call(76,83);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    level_qm = ISVREF(workstation,(SI_Long)78L);
    temp = level_qm && 
	    EQ(get_telewindows_product_name_from_level(level_qm),
	    Qfloating) ? 
	    floating_telewindows_authorized_for_japanese_p(workstation) : Nil;
    if (temp);
    else {
	code = NINTH(SECOND(Graph_allocation_factor));
	if (FIXNUMP(code)) {
	    gensymed_symbol = IFIX(code) & (SI_Long)128L;
	    temp = gensymed_symbol != (SI_Long)0L ? T : Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qjapanese;           /* japanese */

static Object Qg2_authorized_optional_modules;  /* g2-authorized-optional-modules */

/* FLOATING-TELEWINDOWS-AUTHORIZED-FOR-JAPANESE-P */
Object floating_telewindows_authorized_for_japanese_p(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(76,84);
    temp = member_eql(Qjapanese,getf(ISVREF(workstation,(SI_Long)79L),
	    Qg2_authorized_optional_modules,_));
    return VALUES_1(temp);
}

/* TELEWINDOWS-AUTHORIZED-FOR-KOREAN-P */
Object telewindows_authorized_for_korean_p(gensym_window)
    Object gensym_window;
{
    Object workstation, level_qm, temp, code;

    x_note_fn_call(76,85);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    level_qm = ISVREF(workstation,(SI_Long)78L);
    temp = level_qm && 
	    EQ(get_telewindows_product_name_from_level(level_qm),
	    Qfloating) ? 
	    floating_telewindows_authorized_for_korean_p(workstation) : Nil;
    if (temp);
    else {
	code = NINTH(SECOND(Graph_allocation_factor));
	temp = FIXNUMP(code) ? ((IFIX(code) & (SI_Long)2048L) != 
		(SI_Long)0L ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

static Object Qkorean;             /* korean */

/* FLOATING-TELEWINDOWS-AUTHORIZED-FOR-KOREAN-P */
Object floating_telewindows_authorized_for_korean_p(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(76,86);
    temp = member_eql(Qkorean,getf(ISVREF(workstation,(SI_Long)79L),
	    Qg2_authorized_optional_modules,_));
    return VALUES_1(temp);
}

/* TELEWINDOWS-AUTHORIZED-FOR-CHINESE-P */
Object telewindows_authorized_for_chinese_p(gensym_window)
    Object gensym_window;
{
    Object workstation, level_qm, temp, code;

    x_note_fn_call(76,87);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    level_qm = ISVREF(workstation,(SI_Long)78L);
    temp = level_qm && 
	    EQ(get_telewindows_product_name_from_level(level_qm),
	    Qfloating) ? 
	    floating_telewindows_authorized_for_chinese_p(workstation) : Nil;
    if (temp);
    else {
	code = NINTH(SECOND(Graph_allocation_factor));
	temp = FIXNUMP(code) ? ((IFIX(code) & (SI_Long)32L) != (SI_Long)0L 
		? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

static Object Qchinese;            /* chinese */

/* FLOATING-TELEWINDOWS-AUTHORIZED-FOR-CHINESE-P */
Object floating_telewindows_authorized_for_chinese_p(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(76,88);
    temp = member_eql(Qchinese,getf(ISVREF(workstation,(SI_Long)79L),
	    Qg2_authorized_optional_modules,_));
    return VALUES_1(temp);
}

static Object string_constant_42;  /* "[Telewindows: authorized for Korean: loading Hangul Truetype font]" */

static Object string_constant_43;  /* "~%[Telewindows authorized for Chinese: loading Chinese Truetype font]~%" */

/* HANDLE-LICENSED-FONT-INITIALIZATIONS-AS-APPROPRIATE */
Object handle_licensed_font_initializations_as_appropriate(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(76,89);
    if (telewindows_authorized_for_korean_p(gensym_window)) {
	if (EQ(Verbosity_level,Qverbose))
	    notify_user_at_console(1,string_constant_42);
	load_hangul_font();
    }
    if (telewindows_authorized_for_chinese_p(gensym_window)) {
	if (EQ(Verbosity_level,Qverbose))
	    notify_user_at_console(1,string_constant_43);
	return load_chinese_font();
    }
    else
	return VALUES_1(Nil);
}

/* NETWORK-ACCESS-ALLOWED-P */
Object network_access_allowed_p varargs_1(int, n)
{
    Object access_agent, access_type;
    Declare_varargs_nonrelocating;

    x_note_fn_call(76,90);
    INIT_ARGS_nonrelocating();
    access_agent = REQUIRED_ARG_nonrelocating();
    access_type = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(T);
}

/* RECLAIM-EVALUATION-VALUE */
Object reclaim_evaluation_value(x)
    Object x;
{
    x_note_fn_call(76,91);
    return VALUES_1(Nil);
}

/* KILL-FOREIGN-IMAGE-UNCONDITIONALLY */
Object kill_foreign_image_unconditionally(x)
    Object x;
{
    x_note_fn_call(76,92);
    return VALUES_1(Nil);
}

/* WRITE-NAME-DENOTATION-FOR-SLOT */
Object write_name_denotation_for_slot(slot_description,class_description)
    Object slot_description, class_description;
{
    x_note_fn_call(76,93);
    return VALUES_1(Nil);
}

/* WRITE-TYPE-SPECIFICATION */
Object write_type_specification(system_name)
    Object system_name;
{
    x_note_fn_call(76,94);
    return VALUES_1(Nil);
}

/* WRITE-BLOCK-OR-EVALUATION-VALUE */
Object write_block_or_evaluation_value(x)
    Object x;
{
    x_note_fn_call(76,95);
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER */
Object reclaim_frame_serial_number(fsn)
    Object fsn;
{
    x_note_fn_call(76,96);
    return VALUES_1(Nil);
}

/* INITIALIZE-IMAGE-PALETTE-OF-NEW-GENSYM-WINDOW */
Object initialize_image_palette_of_new_gensym_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(76,97);
    return VALUES_1(Nil);
}

/* NEGOTIATE-TELEWINDOWS-LICENSING */
Object negotiate_telewindows_licensing(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(76,98);
    return VALUES_1(Nil);
}

/* RECLAIM-NATIVE-ICONS-TABLE */
Object reclaim_native_icons_table(table)
    Object table;
{
    x_note_fn_call(76,99);
    return VALUES_1(Nil);
}

/* REFRESH-RECTANGLE-OF-WINDOW */
Object refresh_rectangle_of_window(gensym_window,left_qm,top_qm,right_qm,
	    bottom_qm)
    Object gensym_window, left_qm, top_qm, right_qm, bottom_qm;
{
    x_note_fn_call(76,100);
    return VALUES_1(Nil);
}

/* CHECK-SHAPE-OF-WINDOW-WITHOUT-LOOKAHEAD-FOR-G2 */
Object check_shape_of_window_without_lookahead_for_g2(gensym_window,
	    native_window)
    Object gensym_window, native_window;
{
    x_note_fn_call(76,101);
    return VALUES_1(Nil);
}

/* POST-TELEWINDOWS-CONNECTION-CLOGGED */
Object post_telewindows_connection_clogged(g2_window_qm,clogged_qm)
    Object g2_window_qm, clogged_qm;
{
    x_note_fn_call(76,102);
    return VALUES_1(Nil);
}

/* SET-UP-WORKSTATION-ON-AB-SIDE */
Object set_up_workstation_on_ab_side(workstation,gensym_window,v5_mode_p)
    Object workstation, gensym_window, v5_mode_p;
{
    x_note_fn_call(76,103);
    return VALUES_1(Nil);
}

/* RECLAIM-PARTIAL-COMMAND */
Object reclaim_partial_command(pc)
    Object pc;
{
    x_note_fn_call(76,104);
    return VALUES_1(Nil);
}

/* PARTIAL-COMMAND-P-FUNCTION */
Object partial_command_p_function(thing)
    Object thing;
{
    x_note_fn_call(76,105);
    return VALUES_1(Nil);
}

/* HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR */
Object handle_extend_current_text_string_error()
{
    x_note_fn_call(76,106);
    return cerror((SI_Long)2L,"Continue",
	    "Trying to write a string longer than 2MB!");
}

void telewindows_INIT()
{
    Object temp, temp_1, reclaim_structure_for_telewindows_workstation_1;
    Object Qhandle_extend_current_text_string_error, AB_package;
    Object Qtelewindows_connection_clogged_qm, list_constant_7, Qhb72;
    Object list_constant_16, Qtw_copyright_boilerplate_lines_of_text;
    Object Qmake_copyright_boilerplate_lines_of_text_for_tw, Kfuncall, Qhm24;
    Object Qhm18, Qhm14, Qsystem_icon_title_string, string_constant_48;
    Object Qsystem_window_title_string, string_constant_47;
    Object Qlaunch_telewindows, Qlaunch_function_qm, Qsystem_run_function;
    Object Qsystem_top_level_function, Qrun_telewindows_process_top_level;
    Object Qtelewindows_service_workstations_task_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, float_constant;
    Object Qcounter_for_throughput_adjustment, array_constant_13;
    Object Qmake_telewindows_session_id, list_constant_15, list_constant_14;
    Object Qcommand_line_plist_element_getter;
    Object Qget_command_line_plist_element_for_workspace_uuid;
    Object Qcommand_line_process_workspace_uuid, list_constant_13;
    Object Qget_command_line_plist_element_for_workspace;
    Object Qcommand_line_process_workspace, list_constant_12;
    Object Qget_command_line_plist_element_for_splashtime;
    Object Qcommand_line_process_splashtime, list_constant_11;
    Object Qget_command_line_plist_element_for_tcptimeout;
    Object Qcommand_line_process_tcptimeout, list_constant_10;
    Object Qget_command_line_plist_element_for_network;
    Object Qcommand_line_process_network, list_constant_9;
    Object Qget_command_line_plist_element_for_remote_port_name_or_number;
    Object Qcommand_line_process_remote_port_name_or_number, list_constant_8;
    Object Qget_command_line_plist_element_for_remote_host_name;
    Object Qcommand_line_process_remote_host_name;
    Object Qinitialize_user_specified_telewindows_splashscreen_time_in_seconds_qm;
    Object list_constant_6;
    Object Quser_specified_telewindows_splashscreen_time_in_seconds_qm;
    Object Qdefault_telewindows_splashscreen_time_in_seconds;
    Object Qtelewindows_workstation, Qreclaim_structure;
    Object Qoutstanding_telewindows_workstation_count;
    Object Qtelewindows_workstation_structure_memory_usage, Qutilities2;
    Object Qtelewindows_workstation_count;
    Object Qchain_of_available_telewindows_workstations, string_constant_46;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_45, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, string_constant_44, Ktelewindows;

    x_note_fn_call(76,107);
    SET_PACKAGE("AB");
    Ktelewindows = STATIC_SYMBOL("TELEWINDOWS",Pkeyword);
    temp = adjoin(2,Ktelewindows,Features);
    Features = temp;
    Default_tw_tcp_connect_interval_in_ms = FIX((SI_Long)10000L);
    Default_g2_tcp_port = FIX((SI_Long)1111L);
    string_constant_44 = STATIC_STRING("~d");
    Default_g2_tcp_port_text_string = tformat_text_string(2,
	    string_constant_44,Default_g2_tcp_port);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_telewindows_workstation_g2_struct = 
	    STATIC_SYMBOL("TELEWINDOWS-WORKSTATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qtelewindows_workstation = STATIC_SYMBOL("TELEWINDOWS-WORKSTATION",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_telewindows_workstation_g2_struct,
	    Qtelewindows_workstation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtelewindows_workstation,
	    Qg2_defstruct_structure_name_telewindows_workstation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_telewindows_workstation == UNBOUND)
	The_type_description_of_telewindows_workstation = Nil;
    string_constant_45 = 
	    STATIC_STRING("43Dy8l83-jy1o83-jy83Ty8m8k1l83Ty0000001m1m8p83Ty1n8n832Ny1l83dyk3-Dyk0k0");
    temp_1 = The_type_description_of_telewindows_workstation;
    The_type_description_of_telewindows_workstation = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_45));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_telewindows_workstation_g2_struct,
	    The_type_description_of_telewindows_workstation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtelewindows_workstation,
	    The_type_description_of_telewindows_workstation,
	    Qtype_description_of_type);
    Qoutstanding_telewindows_workstation_count = 
	    STATIC_SYMBOL("OUTSTANDING-TELEWINDOWS-WORKSTATION-COUNT",
	    AB_package);
    Qtelewindows_workstation_structure_memory_usage = 
	    STATIC_SYMBOL("TELEWINDOWS-WORKSTATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_46 = STATIC_STRING("1q83-jy8o837Ny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_telewindows_workstation_count);
    push_optimized_constant(Qtelewindows_workstation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_46));
    Qchain_of_available_telewindows_workstations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TELEWINDOWS-WORKSTATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_telewindows_workstations,
	    Chain_of_available_telewindows_workstations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_telewindows_workstations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtelewindows_workstation_count = 
	    STATIC_SYMBOL("TELEWINDOWS-WORKSTATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtelewindows_workstation_count,
	    Telewindows_workstation_count);
    record_system_variable(Qtelewindows_workstation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qtelewindows_workstation_structure_memory_usage,
	    STATIC_FUNCTION(telewindows_workstation_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_telewindows_workstation_count,
	    STATIC_FUNCTION(outstanding_telewindows_workstation_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_telewindows_workstation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_telewindows_workstation,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qtelewindows_workstation,
	    reclaim_structure_for_telewindows_workstation_1);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qlogged_out = STATIC_SYMBOL("LOGGED-OUT",AB_package);
    string_constant = STATIC_STRING("localhost");
    string_constant_1 = STATIC_STRING("TCP-IP");
    Qdisconnected = STATIC_SYMBOL("DISCONNECTED",AB_package);
    Minimum_telewindows_splashscreen_time_in_seconds = FIX((SI_Long)0L);
    Maximum_telewindows_splashscreen_time_in_seconds = FIX((SI_Long)30L);
    Qdefault_telewindows_splashscreen_time_in_seconds = 
	    STATIC_SYMBOL("DEFAULT-TELEWINDOWS-SPLASHSCREEN-TIME-IN-SECONDS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_telewindows_splashscreen_time_in_seconds,
	    Default_telewindows_splashscreen_time_in_seconds);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    record_system_variable(Qdefault_telewindows_splashscreen_time_in_seconds,
	    Qtelewindows,FIX((SI_Long)2L),Qnil,Qnil,Qnil,Qnil);
    Quser_specified_telewindows_splashscreen_time_in_seconds_qm = 
	    STATIC_SYMBOL("USER-SPECIFIED-TELEWINDOWS-SPLASHSCREEN-TIME-IN-SECONDS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_specified_telewindows_splashscreen_time_in_seconds_qm,
	    User_specified_telewindows_splashscreen_time_in_seconds_qm);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_user_specified_telewindows_splashscreen_time_in_seconds_qm 
	    = 
	    STATIC_SYMBOL("INITIALIZE-USER-SPECIFIED-TELEWINDOWS-SPLASHSCREEN-TIME-IN-SECONDS\?",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_user_specified_telewindows_splashscreen_time_in_seconds_qm);
    record_system_variable(Quser_specified_telewindows_splashscreen_time_in_seconds_qm,
	    Qtelewindows,list_constant_6,Qnil,Qnil,Qnil,Qnil);
    Qsplashtime = STATIC_SYMBOL("SPLASHTIME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_user_specified_telewindows_splashscreen_time_in_seconds_qm,
	    STATIC_FUNCTION(initialize_user_specified_telewindows_splashscreen_time_in_seconds_qm,
	    NIL,FALSE,0,0));
    Qcommand_line_process_remote_host_name = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-REMOTE-HOST-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_remote_host_name,
	    STATIC_FUNCTION(command_line_process_remote_host_name,NIL,
	    FALSE,1,1));
    Qremote_host_name = STATIC_SYMBOL("REMOTE-HOST-NAME",AB_package);
    Qcommand_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    mutate_global_property(Qremote_host_name,
	    Qcommand_line_process_remote_host_name,
	    Qcommand_line_argument_processor);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_remote_host_name = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-REMOTE-HOST-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_remote_host_name,
	    STATIC_FUNCTION(get_command_line_plist_element_for_remote_host_name,
	    NIL,FALSE,0,0));
    Qcommand_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    mutate_global_property(Qremote_host_name,
	    Qget_command_line_plist_element_for_remote_host_name,
	    Qcommand_line_plist_element_getter);
    list_constant_8 = STATIC_CONS(Qremote_host_name,FIX((SI_Long)1L));
    temp = adjoin(2,list_constant_8,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    Qcommand_line_process_remote_port_name_or_number = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-REMOTE-PORT-NAME-OR-NUMBER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_remote_port_name_or_number,
	    STATIC_FUNCTION(command_line_process_remote_port_name_or_number,
	    NIL,FALSE,1,1));
    Qremote_port_name_or_number = 
	    STATIC_SYMBOL("REMOTE-PORT-NAME-OR-NUMBER",AB_package);
    mutate_global_property(Qremote_port_name_or_number,
	    Qcommand_line_process_remote_port_name_or_number,
	    Qcommand_line_argument_processor);
    array_constant_1 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_remote_port_name_or_number = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-REMOTE-PORT-NAME-OR-NUMBER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_remote_port_name_or_number,
	    STATIC_FUNCTION(get_command_line_plist_element_for_remote_port_name_or_number,
	    NIL,FALSE,0,0));
    mutate_global_property(Qremote_port_name_or_number,
	    Qget_command_line_plist_element_for_remote_port_name_or_number,
	    Qcommand_line_plist_element_getter);
    list_constant_9 = STATIC_CONS(Qremote_port_name_or_number,
	    FIX((SI_Long)2L));
    temp = adjoin(2,list_constant_9,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    array_constant_2 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING("~%DECNet no longer supported.");
    Qcommand_line_process_network = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-NETWORK",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_network,
	    STATIC_FUNCTION(command_line_process_network,NIL,FALSE,1,1));
    Qnetwork = STATIC_SYMBOL("NETWORK",AB_package);
    mutate_global_property(Qnetwork,Qcommand_line_process_network,
	    Qcommand_line_argument_processor);
    array_constant_5 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_network = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-NETWORK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_network,
	    STATIC_FUNCTION(get_command_line_plist_element_for_network,NIL,
	    FALSE,0,0));
    mutate_global_property(Qnetwork,
	    Qget_command_line_plist_element_for_network,
	    Qcommand_line_plist_element_getter);
    list_constant_10 = STATIC_CONS(Qnetwork,FIX((SI_Long)0L));
    temp = adjoin(2,list_constant_10,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    string_constant_3 = 
	    STATIC_STRING("~%Bad TCP timeout argument: ~s should be an integer.");
    string_constant_4 = 
	    STATIC_STRING("~%Cannot use negative TCP timeout (~d). The default of ~\n           ~d ms will be used instead.~%");
    Qcommand_line_process_tcptimeout = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-TCPTIMEOUT",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_tcptimeout,
	    STATIC_FUNCTION(command_line_process_tcptimeout,NIL,FALSE,1,1));
    Qtcptimeout = STATIC_SYMBOL("TCPTIMEOUT",AB_package);
    mutate_global_property(Qtcptimeout,Qcommand_line_process_tcptimeout,
	    Qcommand_line_argument_processor);
    array_constant_6 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_tcptimeout = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-TCPTIMEOUT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_tcptimeout,
	    STATIC_FUNCTION(get_command_line_plist_element_for_tcptimeout,
	    NIL,FALSE,0,0));
    mutate_global_property(Qtcptimeout,
	    Qget_command_line_plist_element_for_tcptimeout,
	    Qcommand_line_plist_element_getter);
    list_constant_11 = STATIC_CONS(Qtcptimeout,FIX((SI_Long)0L));
    temp = adjoin(2,list_constant_11,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    string_constant_5 = 
	    STATIC_STRING("~%Bad -spashtime argument: ~s should be an integer.");
    Qcommand_line_process_splashtime = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-SPLASHTIME",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_splashtime,
	    STATIC_FUNCTION(command_line_process_splashtime,NIL,FALSE,1,1));
    mutate_global_property(Qsplashtime,Qcommand_line_process_splashtime,
	    Qcommand_line_argument_processor);
    array_constant_7 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_splashtime = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-SPLASHTIME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_splashtime,
	    STATIC_FUNCTION(get_command_line_plist_element_for_splashtime,
	    NIL,FALSE,0,0));
    mutate_global_property(Qsplashtime,
	    Qget_command_line_plist_element_for_splashtime,
	    Qcommand_line_plist_element_getter);
    list_constant_12 = STATIC_CONS(Qsplashtime,FIX((SI_Long)0L));
    temp = adjoin(2,list_constant_12,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    Qcommand_line_process_workspace = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_workspace,
	    STATIC_FUNCTION(command_line_process_workspace,NIL,FALSE,1,1));
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    mutate_global_property(Qworkspace,Qcommand_line_process_workspace,
	    Qcommand_line_argument_processor);
    array_constant_8 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_workspace = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_workspace,
	    STATIC_FUNCTION(get_command_line_plist_element_for_workspace,
	    NIL,FALSE,0,0));
    mutate_global_property(Qworkspace,
	    Qget_command_line_plist_element_for_workspace,
	    Qcommand_line_plist_element_getter);
    list_constant_13 = STATIC_CONS(Qworkspace,FIX((SI_Long)0L));
    temp = adjoin(2,list_constant_13,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    Qcommand_line_process_workspace_uuid = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-WORKSPACE-UUID",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_workspace_uuid,
	    STATIC_FUNCTION(command_line_process_workspace_uuid,NIL,FALSE,
	    1,1));
    Qworkspace_uuid = STATIC_SYMBOL("WORKSPACE-UUID",AB_package);
    mutate_global_property(Qworkspace_uuid,
	    Qcommand_line_process_workspace_uuid,
	    Qcommand_line_argument_processor);
    array_constant_9 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_workspace_uuid = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-WORKSPACE-UUID",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_workspace_uuid,
	    STATIC_FUNCTION(get_command_line_plist_element_for_workspace_uuid,
	    NIL,FALSE,0,0));
    mutate_global_property(Qworkspace_uuid,
	    Qget_command_line_plist_element_for_workspace_uuid,
	    Qcommand_line_plist_element_getter);
    list_constant_14 = STATIC_CONS(Qworkspace_uuid,FIX((SI_Long)0L));
    temp = adjoin(2,list_constant_14,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = temp;
    Qtelewindows_session_id = STATIC_SYMBOL("TELEWINDOWS-SESSION-ID",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtelewindows_session_id,Telewindows_session_id);
    Qmake_telewindows_session_id = 
	    STATIC_SYMBOL("MAKE-TELEWINDOWS-SESSION-ID",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_telewindows_session_id);
    record_system_variable(Qtelewindows_session_id,Qtelewindows,
	    list_constant_15,Qnil,Qnil,Qnil,Qnil);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_telewindows_session_id,
	    STATIC_FUNCTION(make_telewindows_session_id,NIL,FALSE,0,0));
    array_constant_13 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Telewindows_name_for_unknown_host = array_constant_13;
    Qnetwork_host_name = STATIC_SYMBOL("NETWORK-HOST-NAME",AB_package);
    Qos_user_name = STATIC_SYMBOL("OS-USER-NAME",AB_package);
    Qos_type = STATIC_SYMBOL("OS-TYPE",AB_package);
    Qui_toolkit = STATIC_SYMBOL("UI-TOOLKIT",AB_package);
    Qnative_icons_limit = STATIC_SYMBOL("NATIVE-ICONS-LIMIT",AB_package);
    Qtelewindows_authorized_products = 
	    STATIC_SYMBOL("TELEWINDOWS-AUTHORIZED-PRODUCTS",AB_package);
    Qtelewindows_license_level = STATIC_SYMBOL("TELEWINDOWS-LICENSE-LEVEL",
	    AB_package);
    Qsilent = STATIC_SYMBOL("SILENT",AB_package);
    string_constant_6 = 
	    STATIC_STRING("[Telewindows: Unable to set TCP connect timeout interval.  ~\n           The default of ~d ms will be used instead.]");
    Qverbose = STATIC_SYMBOL("VERBOSE",AB_package);
    string_constant_7 = 
	    STATIC_STRING("[Telewindows: Using TCP connect timeout interval of ~d ms]");
    Allow_talking_to_a_pre_version_4_g2_p = T;
    string_constant_8 = STATIC_STRING("TWNG");
    string_constant_9 = STATIC_STRING("Telewindows");
    string_constant_10 = 
	    STATIC_STRING("[Telewindows: ~a connection to ~a G2 denied]");
    string_constant_11 = STATIC_STRING("pre-8.3r0");
    string_constant_12 = STATIC_STRING("pre-4.0");
    string_constant_13 = STATIC_STRING("~a:~a:~a");
    Qcounter_for_throughput_adjustment = 
	    STATIC_SYMBOL("COUNTER-FOR-THROUGHPUT-ADJUSTMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcounter_for_throughput_adjustment,
	    Counter_for_throughput_adjustment);
    record_system_variable(Qcounter_for_throughput_adjustment,Qtelewindows,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    if (Legacy_heartbeat_adjustment_priority == UNBOUND)
	Legacy_heartbeat_adjustment_priority = FIX((SI_Long)1L);
    float_constant = STATIC_FLOAT(2.0);
    if (Legacy_heartbeat_adjustment_interval == UNBOUND)
	Legacy_heartbeat_adjustment_interval = float_constant;
    Qdo_legacy_heartbeat_adjustments = 
	    STATIC_SYMBOL("DO-LEGACY-HEARTBEAT-ADJUSTMENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qdo_legacy_heartbeat_adjustments,
	    STATIC_FUNCTION(do_legacy_heartbeat_adjustments,NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfailed_to_connect = STATIC_SYMBOL("FAILED-TO-CONNECT",AB_package);
    Qdevelopment = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    string_constant_14 = 
	    STATIC_STRING("[Telewindows: authorized for connection to any G2.]");
    Qconnected = STATIC_SYMBOL("CONNECTED",AB_package);
    string_constant_15 = 
	    STATIC_STRING("[Telewindows: authorized for a ~a license; ~\n                 will attempt to obtain a Floating Telewindows license~a.]");
    Qfloating = STATIC_SYMBOL("FLOATING",AB_package);
    string_constant_16 = STATIC_STRING("");
    string_constant_17 = STATIC_STRING(" if necessary");
    Qconnected_and_awaiting_license_level = 
	    STATIC_SYMBOL("CONNECTED-AND-AWAITING-LICENSE-LEVEL",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    string_constant_18 = 
	    STATIC_STRING("[Telewindows: connecting to host ~s at port ~a via protocol ~a~a]");
    Kuse_default = STATIC_SYMBOL("USE-DEFAULT",Pkeyword);
    Qconnecting = STATIC_SYMBOL("CONNECTING",AB_package);
    Qhandle_telewindows_shutdown = 
	    STATIC_SYMBOL("HANDLE-TELEWINDOWS-SHUTDOWN",AB_package);
    Qnot_established = STATIC_SYMBOL("NOT-ESTABLISHED",AB_package);
    Qsucceed_at_connecting_telewindows_workstation = 
	    STATIC_SYMBOL("SUCCEED-AT-CONNECTING-TELEWINDOWS-WORKSTATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsucceed_at_connecting_telewindows_workstation,
	    STATIC_FUNCTION(succeed_at_connecting_telewindows_workstation,
	    NIL,FALSE,1,1));
    string_constant_19 = 
	    STATIC_STRING("~%[Telewindows: received word back from G2 . . . ~\n          Telewindows License Level: ~a]");
    Qg2_license_level = STATIC_SYMBOL("G2-LICENSE-LEVEL",AB_package);
    string_constant_20 = 
	    STATIC_STRING("[Telewindows: the target G2 is authorized for ~a Telewindows connections]");
    Qunauthorized = STATIC_SYMBOL("UNAUTHORIZED",AB_package);
    string_constant_21 = STATIC_STRING("[Telewindows: Connected.]");
    string_constant_22 = 
	    STATIC_STRING("[Telewindows: Sorry.  Permission has been denied for access via this Telewindows.]");
    string_constant_23 = 
	    STATIC_STRING("[Telewindows: Sorry.  Telewindows has timed out in its attempt to obtain ~\n             permission to connect to G2.]");
    Qbeing_rerouted = STATIC_SYMBOL("BEING-REROUTED",AB_package);
    string_constant_24 = 
	    STATIC_STRING("[Telewindows: Rerouting to host ~s at address ~a]");
    string_constant_25 = 
	    STATIC_STRING("[Telewindows: Attempting to return to host ~s at address ~a]");
    string_constant_26 = STATIC_STRING("(unknown)");
    string_constant_27 = 
	    STATIC_STRING("Unable to connect to host ~s at port ~a via protocol ~a~a");
    Qtop_level_error_catcher = STATIC_SYMBOL("TOP-LEVEL-ERROR-CATCHER",
	    AB_package);
    Qerror_trapped = STATIC_SYMBOL("ERROR-TRAPPED",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qabort_level_0 = STATIC_SYMBOL("ABORT-LEVEL-0",AB_package);
    Qhandle_icp_messages = STATIC_SYMBOL("HANDLE-ICP-MESSAGES",AB_package);
    Quser_name = STATIC_SYMBOL("USER-NAME",AB_package);
    Qmd5_password = STATIC_SYMBOL("MD5-PASSWORD",AB_package);
    string_constant_28 = 
	    STATIC_STRING("[Telewindows: User-specified splashtime: ~d seconds (min/max/default: ~d/~d/~d)]");
    Qdefault_pane_background_color_or_tiling_pattern_rows = 
	    STATIC_SYMBOL("DEFAULT-PANE-BACKGROUND-COLOR-OR-TILING-PATTERN-ROWS",
	    AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qcjk_language = STATIC_SYMBOL("CJK-LANGUAGE",AB_package);
    Qinit_string = STATIC_SYMBOL("INIT-STRING",AB_package);
    Qreroute_problem_report = STATIC_SYMBOL("REROUTE-PROBLEM-REPORT",
	    AB_package);
    Qdesires_connection = STATIC_SYMBOL("DESIRES-CONNECTION",AB_package);
    Priority_of_tw_workstation_service = FIX((SI_Long)2L);
    Qtelewindows_service_workstations_task_qm = 
	    STATIC_SYMBOL("TELEWINDOWS-SERVICE-WORKSTATIONS-TASK\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtelewindows_service_workstations_task_qm,
	    Telewindows_service_workstations_task_qm);
    record_system_variable(Qtelewindows_service_workstations_task_qm,
	    Qtelewindows,Nil,Qnil,Qnil,Qnil,Qnil);
    Qservice_telewindows_workstations_once = 
	    STATIC_SYMBOL("SERVICE-TELEWINDOWS-WORKSTATIONS-ONCE",AB_package);
    SET_SYMBOL_FUNCTION(Qservice_telewindows_workstations_once,
	    STATIC_FUNCTION(service_telewindows_workstations_once,NIL,
	    FALSE,0,0));
    Tw_scheduled_tasks_time_limit = fixnum_time_interval(FIX((SI_Long)200L));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    string_constant_29 = 
	    STATIC_STRING("[Telewindows: Unable to connect to host ~s at port ~a via protocol ~a~a]");
    Qfailure_to_connect = STATIC_SYMBOL("FAILURE-TO-CONNECT",AB_package);
    Qsession_id = STATIC_SYMBOL("SESSION-ID",AB_package);
    Qtelewindows_connection_license_level = 
	    STATIC_SYMBOL("TELEWINDOWS-CONNECTION-LICENSE-LEVEL",AB_package);
    Qrun_telewindows = STATIC_SYMBOL("RUN-TELEWINDOWS",AB_package);
    SET_SYMBOL_FUNCTION(Qrun_telewindows,STATIC_FUNCTION(run_telewindows,
	    NIL,FALSE,1,1));
    Qrun_telewindows_process_top_level = 
	    STATIC_SYMBOL("RUN-TELEWINDOWS-PROCESS-TOP-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qrun_telewindows_process_top_level,
	    STATIC_FUNCTION(run_telewindows_process_top_level,NIL,FALSE,1,1));
    Qsystem_top_level_function = STATIC_SYMBOL("SYSTEM-TOP-LEVEL-FUNCTION",
	    AB_package);
    mutate_global_property(Qtelewindows,Qrun_telewindows_process_top_level,
	    Qsystem_top_level_function);
    Qsystem_run_function = STATIC_SYMBOL("SYSTEM-RUN-FUNCTION",AB_package);
    mutate_global_property(Qtelewindows,Qrun_telewindows,Qsystem_run_function);
    Qlaunch_function_qm = STATIC_SYMBOL("LAUNCH-FUNCTION\?",AB_package);
    Qlaunch_telewindows = STATIC_SYMBOL("LAUNCH-TELEWINDOWS",AB_package);
    SET_SYMBOL_FUNCTION(Qlaunch_telewindows,
	    STATIC_FUNCTION(launch_telewindows,NIL,FALSE,0,0));
    set_get(Qtelewindows,Qlaunch_function_qm,Qlaunch_telewindows);
    string_constant_47 = STATIC_STRING("Telewindows Client");
    Qsystem_window_title_string = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-STRING",AB_package);
    mutate_global_property(Qtelewindows,string_constant_47,
	    Qsystem_window_title_string);
    string_constant_48 = STATIC_STRING("TW");
    Qsystem_icon_title_string = STATIC_SYMBOL("SYSTEM-ICON-TITLE-STRING",
	    AB_package);
    mutate_global_property(Qtelewindows,string_constant_48,
	    Qsystem_icon_title_string);
    string_constant_30 = STATIC_STRING("(unknown network type)");
    string_constant_31 = 
	    STATIC_STRING("~%[Telewindows: no ~a listener at host ~s for port ~s]~%");
    array_constant_11 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    string_constant_32 = 
	    STATIC_STRING("Unable to connect to G2.  No ~a listener at host ~s for port ~s.");
    string_constant_33 = STATIC_STRING("~a connection to host ~s at port ~a");
    Qrequested = STATIC_SYMBOL("REQUESTED",AB_package);
    string_constant_34 = STATIC_STRING("closed as requested.");
    Qbroken_while_receiving = STATIC_SYMBOL("BROKEN-WHILE-RECEIVING",
	    AB_package);
    string_constant_35 = STATIC_STRING("broken while receiving data.");
    Qbroken_while_transmitting = STATIC_SYMBOL("BROKEN-WHILE-TRANSMITTING",
	    AB_package);
    string_constant_36 = STATIC_STRING("broken while transmitting data.");
    Qprotocol_out_of_synch_1 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-1",
	    AB_package);
    Qprotocol_out_of_synch_2 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-2",
	    AB_package);
    Qprotocol_out_of_synch_3 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-3",
	    AB_package);
    Qprotocol_out_of_synch_4 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-4",
	    AB_package);
    Qprotocol_out_of_synch_5 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-5",
	    AB_package);
    list_constant = STATIC_LIST((SI_Long)5L,Qprotocol_out_of_synch_1,
	    Qprotocol_out_of_synch_2,Qprotocol_out_of_synch_3,
	    Qprotocol_out_of_synch_4,Qprotocol_out_of_synch_5);
    Qprotocol_out_of_synch_6 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-6",
	    AB_package);
    string_constant_37 = 
	    STATIC_STRING("broken: protocol out of synch (case ~s).");
    Qunknown_message = STATIC_SYMBOL("UNKNOWN-MESSAGE",AB_package);
    string_constant_38 = 
	    STATIC_STRING("broken: received a message of a type that is not known.");
    string_constant_39 = STATIC_STRING("broken.");
    string_constant_40 = STATIC_STRING("[Telewindows: ~a ~a]");
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qbeing_rerouted,
	    Qnot_established);
    SET_SYMBOL_FUNCTION(Qhandle_telewindows_shutdown,
	    STATIC_FUNCTION(handle_telewindows_shutdown,NIL,FALSE,2,2));
    Qauthorization_failure = STATIC_SYMBOL("AUTHORIZATION-FAILURE",AB_package);
    if (Current_telewindows_baseline == UNBOUND)
	Current_telewindows_baseline = Default_telewindows_upper_margin;
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qwrite_list_of_text_lines_in_current_window = 
	    STATIC_SYMBOL("WRITE-LIST-OF-TEXT-LINES-IN-CURRENT-WINDOW",
	    AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    list_constant_2 = STATIC_CONS(Qhm14,Qnil);
    Qhm18 = STATIC_SYMBOL("HM18",AB_package);
    list_constant_3 = STATIC_CONS(Qhm18,Qnil);
    Qhm24 = STATIC_SYMBOL("HM24",AB_package);
    list_constant_4 = STATIC_CONS(Qhm24,Qnil);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_text_lines_in_current_window,
	    STATIC_FUNCTION(write_list_of_text_lines_in_current_window,NIL,
	    FALSE,3,3));
    Qpaint_telewindows_window_with_credits_in_current_window = 
	    STATIC_SYMBOL("PAINT-TELEWINDOWS-WINDOW-WITH-CREDITS-IN-CURRENT-WINDOW",
	    AB_package);
    Qtw_copyright_boilerplate_lines_of_text = 
	    STATIC_SYMBOL("TW-COPYRIGHT-BOILERPLATE-LINES-OF-TEXT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_copyright_boilerplate_lines_of_text,
	    Tw_copyright_boilerplate_lines_of_text);
    Qmake_copyright_boilerplate_lines_of_text_for_tw = 
	    STATIC_SYMBOL("MAKE-COPYRIGHT-BOILERPLATE-LINES-OF-TEXT-FOR-TW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_copyright_boilerplate_lines_of_text_for_tw,
	    STATIC_FUNCTION(make_copyright_boilerplate_lines_of_text_for_tw,
	    NIL,FALSE,0,0));
    list_constant_16 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_copyright_boilerplate_lines_of_text_for_tw);
    record_system_variable(Qtw_copyright_boilerplate_lines_of_text,
	    Qtelewindows,list_constant_16,Qnil,Qnil,Qnil,Qnil);
    Qhb72 = STATIC_SYMBOL("HB72",AB_package);
    list_constant_5 = STATIC_CONS(Qhb72,Qnil);
    array_constant_12 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)8482L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    SET_SYMBOL_FUNCTION(Qpaint_telewindows_window_with_credits_in_current_window,
	    STATIC_FUNCTION(paint_telewindows_window_with_credits_in_current_window,
	    NIL,FALSE,0,0));
    string_constant_41 = 
	    STATIC_STRING("[Telewindows: connection to ~s ~s is clogged.]");
    Qtelewindows_connection_clogged_qm = 
	    STATIC_SYMBOL("TELEWINDOWS-CONNECTION-CLOGGED\?",AB_package);
    SET_SYMBOL_FUNCTION(Qtelewindows_connection_clogged_qm,
	    STATIC_FUNCTION(telewindows_connection_clogged_qm,NIL,FALSE,2,2));
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    Qg2_authorized_optional_modules = 
	    STATIC_SYMBOL("G2-AUTHORIZED-OPTIONAL-MODULES",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    string_constant_42 = 
	    STATIC_STRING("[Telewindows: authorized for Korean: loading Hangul Truetype font]");
    string_constant_43 = 
	    STATIC_STRING("~%[Telewindows authorized for Chinese: loading Chinese Truetype font]~%");
    Qhandle_extend_current_text_string_error = 
	    STATIC_SYMBOL("HANDLE-EXTEND-CURRENT-TEXT-STRING-ERROR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_extend_current_text_string_error,
	    STATIC_FUNCTION(handle_extend_current_text_string_error,NIL,
	    FALSE,0,0));
}
