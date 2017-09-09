/* mice.c
 * Input file:  mice.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "mice.h"


Object The_type_description_of_workstation_context_frame = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstation_context_frames, Qchain_of_available_workstation_context_frames);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_context_frame_count, Qworkstation_context_frame_count);

Object Chain_of_available_workstation_context_frames_vector = UNBOUND;

/* WORKSTATION-CONTEXT-FRAME-STRUCTURE-MEMORY-USAGE */
Object workstation_context_frame_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,0);
    temp = Workstation_context_frame_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSTATION-CONTEXT-FRAME-COUNT */
Object outstanding_workstation_context_frame_count()
{
    Object def_structure_workstation_context_frame_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,1);
    gensymed_symbol = IFIX(Workstation_context_frame_count);
    def_structure_workstation_context_frame_variable = 
	    Chain_of_available_workstation_context_frames;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_workstation_context_frame_variable))
	goto end_loop;
    def_structure_workstation_context_frame_variable = 
	    ISVREF(def_structure_workstation_context_frame_variable,
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

/* RECLAIM-WORKSTATION-CONTEXT-FRAME-1 */
Object reclaim_workstation_context_frame_1(workstation_context_frame)
    Object workstation_context_frame;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,2);
    inline_note_reclaim_cons(workstation_context_frame,Nil);
    structure_being_reclaimed = workstation_context_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(workstation_context_frame,(SI_Long)1L));
      SVREF(workstation_context_frame,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(workstation_context_frame,
	      (SI_Long)2L));
      SVREF(workstation_context_frame,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_workstation_context_frames_vector,
	    IFIX(Current_thread_index));
    SVREF(workstation_context_frame,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workstation_context_frames_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workstation_context_frame;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSTATION-CONTEXT-FRAME */
Object reclaim_structure_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    x_note_fn_call(61,3);
    return reclaim_workstation_context_frame_1(workstation_context_frame);
}

static Object Qg2_defstruct_structure_name_workstation_context_frame_g2_struct;  /* g2-defstruct-structure-name::workstation-context-frame-g2-struct */

/* MAKE-PERMANENT-WORKSTATION-CONTEXT-FRAME-STRUCTURE-INTERNAL */
Object make_permanent_workstation_context_frame_structure_internal()
{
    Object def_structure_workstation_context_frame_variable;
    Object defstruct_g2_workstation_context_frame_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,4);
    def_structure_workstation_context_frame_variable = Nil;
    atomic_incff_symval(Qworkstation_context_frame_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workstation_context_frame_variable = Nil;
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
	defstruct_g2_workstation_context_frame_variable = the_array;
	SVREF(defstruct_g2_workstation_context_frame_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_context_frame_g2_struct;
	def_structure_workstation_context_frame_variable = 
		defstruct_g2_workstation_context_frame_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workstation_context_frame_variable);
}

/* MAKE-WORKSTATION-CONTEXT-FRAME-1 */
Object make_workstation_context_frame_1()
{
    Object def_structure_workstation_context_frame_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(61,5);
    def_structure_workstation_context_frame_variable = 
	    ISVREF(Chain_of_available_workstation_context_frames_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workstation_context_frame_variable) {
	temp = Chain_of_available_workstation_context_frames_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_workstation_context_frame_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workstation_context_frame_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_context_frame_g2_struct;
    }
    else
	def_structure_workstation_context_frame_variable = 
		make_permanent_workstation_context_frame_structure_internal();
    inline_note_allocate_cons(def_structure_workstation_context_frame_variable,
	    Nil);
    SVREF(def_structure_workstation_context_frame_variable,
	    FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_workstation_context_frame_variable,
	    FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_workstation_context_frame_variable);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* CLEAN-UP-WORKSTATION-CONTEXT-FUNCTION */
Object clean_up_workstation_context_function(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,6);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)1L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* SETUP-WORKSTATION-CONTEXT-FUNCTION */
Object setup_workstation_context_function(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,7);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)5L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* SUSPEND-WORKSTATION-CONTEXT-FUNCTION */
Object suspend_workstation_context_function(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,8);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)6L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RESUME-WORKSTATION-CONTEXT-FUNCTION */
Object resume_workstation_context_function(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,9);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)7L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

Object The_type_description_of_mouse_pointer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_mouse_pointers, Qchain_of_available_mouse_pointers);

DEFINE_VARIABLE_WITH_SYMBOL(Mouse_pointer_count, Qmouse_pointer_count);

Object Chain_of_available_mouse_pointers_vector = UNBOUND;

/* MOUSE-POINTER-STRUCTURE-MEMORY-USAGE */
Object mouse_pointer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,10);
    temp = Mouse_pointer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MOUSE-POINTER-COUNT */
Object outstanding_mouse_pointer_count()
{
    Object def_structure_mouse_pointer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,11);
    gensymed_symbol = IFIX(Mouse_pointer_count);
    def_structure_mouse_pointer_variable = Chain_of_available_mouse_pointers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_mouse_pointer_variable))
	goto end_loop;
    def_structure_mouse_pointer_variable = 
	    ISVREF(def_structure_mouse_pointer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MOUSE-POINTER-1 */
Object reclaim_mouse_pointer_1(mouse_pointer)
    Object mouse_pointer;
{
    Object structure_being_reclaimed, structure, gensymed_symbol;
    Object gensymed_symbol_1, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,12);
    inline_note_reclaim_cons(mouse_pointer,Nil);
    structure_being_reclaimed = mouse_pointer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      structure = ISVREF(mouse_pointer,(SI_Long)5L);
      gensymed_symbol = ISVREF(structure,(SI_Long)0L);
      gensymed_symbol = 
	      ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	      Qtype_description_of_unique_type_name_of_gensym_structure),
	      (SI_Long)9L),(SI_Long)3L);
      gensymed_symbol_1 = structure;
      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      SVREF(mouse_pointer,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_mouse_pointers_vector,
	    IFIX(Current_thread_index));
    SVREF(mouse_pointer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_mouse_pointers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = mouse_pointer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MOUSE-POINTER */
Object reclaim_structure_for_mouse_pointer(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(61,13);
    return reclaim_mouse_pointer_1(mouse_pointer);
}

static Object Qg2_defstruct_structure_name_mouse_pointer_g2_struct;  /* g2-defstruct-structure-name::mouse-pointer-g2-struct */

/* MAKE-PERMANENT-MOUSE-POINTER-STRUCTURE-INTERNAL */
Object make_permanent_mouse_pointer_structure_internal()
{
    Object def_structure_mouse_pointer_variable;
    Object defstruct_g2_mouse_pointer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,14);
    def_structure_mouse_pointer_variable = Nil;
    atomic_incff_symval(Qmouse_pointer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_mouse_pointer_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_mouse_pointer_variable = the_array;
	SVREF(defstruct_g2_mouse_pointer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_mouse_pointer_g2_struct;
	def_structure_mouse_pointer_variable = 
		defstruct_g2_mouse_pointer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_mouse_pointer_variable);
}

/* MAKE-MOUSE-POINTER-1 */
Object make_mouse_pointer_1(workstation_for_mouse_pointer,
	    key_code_of_mouse_pointer,fixnum_time_of_mouse_pointer,
	    x_of_mouse_pointer,y_of_mouse_pointer)
    Object workstation_for_mouse_pointer, key_code_of_mouse_pointer;
    Object fixnum_time_of_mouse_pointer, x_of_mouse_pointer;
    Object y_of_mouse_pointer;
{
    Object def_structure_mouse_pointer_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(61,15);
    def_structure_mouse_pointer_variable = 
	    ISVREF(Chain_of_available_mouse_pointers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_mouse_pointer_variable) {
	svref_arg_1 = Chain_of_available_mouse_pointers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_mouse_pointer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_mouse_pointer_g2_struct;
    }
    else
	def_structure_mouse_pointer_variable = 
		make_permanent_mouse_pointer_structure_internal();
    inline_note_allocate_cons(def_structure_mouse_pointer_variable,Nil);
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)1L)) = 
	    workstation_for_mouse_pointer;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)8L)) = 
	    key_code_of_mouse_pointer;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)7L)) = 
	    fixnum_time_of_mouse_pointer;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)2L)) = 
	    x_of_mouse_pointer;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)3L)) = 
	    y_of_mouse_pointer;
    ISVREF(def_structure_mouse_pointer_variable,(SI_Long)4L) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_mouse_pointer_variable,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_mouse_pointer_variable);
}

static Object Qmulti;              /* multi */

/* MOUSE-POINTER-IS-MULTI-P */
Object mouse_pointer_is_multi_p(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(61,16);
    return VALUES_1(EQ(ISVREF(mouse_pointer,(SI_Long)12L),Qmulti) ? T : Nil);
}

/* MOUSE-POINTER-IS-SYNTHETIC-P */
Object mouse_pointer_is_synthetic_p(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(61,17);
    return VALUES_1( ! !TRUEP(ISVREF(mouse_pointer,(SI_Long)12L)) ? T : Nil);
}

/* REFERENCE-MOUSE-POINTER */
Object reference_mouse_pointer(mouse_pointer)
    Object mouse_pointer;
{
    Object svref_new_value;

    x_note_fn_call(61,18);
    svref_new_value = FIXNUM_ADD1(ISVREF(mouse_pointer,(SI_Long)4L));
    SVREF(mouse_pointer,FIX((SI_Long)4L)) = svref_new_value;
    return VALUES_1(mouse_pointer);
}

/* RELEASE-MOUSE-POINTER-IF-ANY */
Object release_mouse_pointer_if_any(mouse_pointer_qm)
    Object mouse_pointer_qm;
{
    Object svref_new_value;

    x_note_fn_call(61,19);
    if (mouse_pointer_qm) {
	svref_new_value = FIXNUM_SUB1(ISVREF(mouse_pointer_qm,(SI_Long)4L));
	SVREF(mouse_pointer_qm,FIX((SI_Long)4L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* RELEASE-MOUSE-POINTERS */
Object release_mouse_pointers(mouse_pointers)
    Object mouse_pointers;
{
    Object mouse_pointer, ab_loop_list_;

    x_note_fn_call(61,20);
    mouse_pointer = Nil;
    ab_loop_list_ = mouse_pointers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mouse_pointer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    release_mouse_pointer_if_any(mouse_pointer);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(mouse_pointers);
    return VALUES_1(Nil);
}

Object The_type_description_of_workstation_context_with_selection_focus = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstation_context_with_selection_focuss, Qchain_of_available_workstation_context_with_selection_focuss);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_context_with_selection_focus_count, Qworkstation_context_with_selection_focus_count);

Object Chain_of_available_workstation_context_with_selection_focuss_vector = UNBOUND;

/* WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-STRUCTURE-MEMORY-USAGE */
Object workstation_context_with_selection_focus_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,21);
    temp = Workstation_context_with_selection_focus_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-COUNT */
Object outstanding_workstation_context_with_selection_focus_count()
{
    Object def_structure_workstation_context_with_selection_focus_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,22);
    gensymed_symbol = IFIX(Workstation_context_with_selection_focus_count);
    def_structure_workstation_context_with_selection_focus_variable = 
	    Chain_of_available_workstation_context_with_selection_focuss;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_workstation_context_with_selection_focus_variable))
	goto end_loop;
    def_structure_workstation_context_with_selection_focus_variable = 
	    ISVREF(def_structure_workstation_context_with_selection_focus_variable,
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

/* RECLAIM-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-1 */
Object reclaim_workstation_context_with_selection_focus_1(workstation_context_with_selection_focus)
    Object workstation_context_with_selection_focus;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,23);
    inline_note_reclaim_cons(workstation_context_with_selection_focus,Nil);
    structure_being_reclaimed = workstation_context_with_selection_focus;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(workstation_context_with_selection_focus,
	      (SI_Long)1L));
      SVREF(workstation_context_with_selection_focus,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(workstation_context_with_selection_focus,
	      (SI_Long)2L));
      SVREF(workstation_context_with_selection_focus,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_workstation_context_with_selection_focuss_vector,
	    IFIX(Current_thread_index));
    SVREF(workstation_context_with_selection_focus,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workstation_context_with_selection_focuss_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workstation_context_with_selection_focus;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS */
Object reclaim_structure_for_workstation_context_with_selection_focus(workstation_context_with_selection_focus)
    Object workstation_context_with_selection_focus;
{
    x_note_fn_call(61,24);
    return reclaim_workstation_context_with_selection_focus_1(workstation_context_with_selection_focus);
}

static Object Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct;  /* g2-defstruct-structure-name::workstation-context-with-selection-focus-g2-struct */

/* MAKE-PERMANENT-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-STRUCTURE-INTERNAL */
Object make_permanent_workstation_context_with_selection_focus_structure_internal()
{
    Object def_structure_workstation_context_with_selection_focus_variable;
    Object defstruct_g2_workstation_context_with_selection_focus_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,25);
    def_structure_workstation_context_with_selection_focus_variable = Nil;
    atomic_incff_symval(Qworkstation_context_with_selection_focus_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workstation_context_with_selection_focus_variable = Nil;
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
	defstruct_g2_workstation_context_with_selection_focus_variable = 
		the_array;
	SVREF(defstruct_g2_workstation_context_with_selection_focus_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct;
	SVREF(defstruct_g2_workstation_context_with_selection_focus_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_workstation_context_with_selection_focus_variable,
		FIX((SI_Long)2L)) = Nil;
	def_structure_workstation_context_with_selection_focus_variable = 
		defstruct_g2_workstation_context_with_selection_focus_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workstation_context_with_selection_focus_variable);
}

/* MAKE-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-1 */
Object make_workstation_context_with_selection_focus_1()
{
    Object def_structure_workstation_context_with_selection_focus_variable;
    Object temp, svref_arg_2, svref_new_value;

    x_note_fn_call(61,26);
    def_structure_workstation_context_with_selection_focus_variable = 
	    ISVREF(Chain_of_available_workstation_context_with_selection_focuss_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workstation_context_with_selection_focus_variable) {
	temp = 
		Chain_of_available_workstation_context_with_selection_focuss_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_workstation_context_with_selection_focus_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workstation_context_with_selection_focus_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct;
    }
    else
	def_structure_workstation_context_with_selection_focus_variable = 
		make_permanent_workstation_context_with_selection_focus_structure_internal();
    inline_note_allocate_cons(def_structure_workstation_context_with_selection_focus_variable,
	    Nil);
    SVREF(def_structure_workstation_context_with_selection_focus_variable,
	    FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_workstation_context_with_selection_focus_variable,
	    FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_workstation_context_with_selection_focus_variable);
}

Object Selection_style_of_workstation_context_type_prop = UNBOUND;

static Object Qselection_style_of_workstation_context_type;  /* selection-style-of-workstation-context-type */

static Object Qtop_level_is_selection_style;  /* top-level-is-selection-style */

/* SELECTION-STYLE-OF-WORKSTATION-CONTEXT */
Object selection_style_of_workstation_context(workstation_context)
    Object workstation_context;
{
    Object type_description, gensymed_symbol, temp;

    x_note_fn_call(61,27);
    type_description = type_description_of(workstation_context);
    gensymed_symbol = ISVREF(type_description,(SI_Long)1L);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qselection_style_of_workstation_context_type);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Qtop_level_is_selection_style);
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_window_heartbeat_task, Qnative_window_heartbeat_task);

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qnative_window_heartbeat;  /* native-window-heartbeat */

/* START-OR-RESTART-NATIVE-WINDOW-HEARTBEAT */
Object start_or_restart_native_window_heartbeat()
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2, old;
    Object new_1, def_structure_schedule_task_variable, svref_new_value, task;
    char svref_new_value_1;
    double realtime_interval_of_heartbeat, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(61,28);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = Native_window_heartbeat_task;
    if (CAS_SYMBOL(Qnative_window_heartbeat_task,gensymed_symbol,Nil)) {
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
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	realtime_interval_of_heartbeat = 
		(double)IFIX(Native_window_polling_interval) / 1000.0;
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = Native_window_heartbeat_task;
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
	aref_new_value = g2ext_unix_time_as_float() + 
		realtime_interval_of_heartbeat;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	DFLOAT_ISASET_1(temp,(SI_Long)1L,realtime_interval_of_heartbeat);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qnative_window_heartbeat;
	temp = SYMBOL_FUNCTION(Qnative_window_heartbeat);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	temp = System_window;
	SVREF(task,FIX((SI_Long)13L)) = temp;
	new_1 = task;
	if (CAS_SYMBOL(Qnative_window_heartbeat_task,old,new_1)) {
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
	    result = VALUES_1(new_1);
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
	result = VALUES_1(Qnil);
      end_2:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* NATIVE-WINDOW-HEARTBEAT */
Object native_window_heartbeat(native_gensym_window)
    Object native_gensym_window;
{
    Object svref_arg_1;

    x_note_fn_call(61,29);
    svref_arg_1 = ISVREF(native_gensym_window,(SI_Long)2L);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)41L)) = T);
}

Object The_type_description_of_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_spots, Qchain_of_available_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Spot_count, Qspot_count);

Object Chain_of_available_spots_vector = UNBOUND;

/* SPOT-STRUCTURE-MEMORY-USAGE */
Object spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,30);
    temp = Spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SPOT-COUNT */
Object outstanding_spot_count()
{
    Object def_structure_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,31);
    gensymed_symbol = IFIX(Spot_count);
    def_structure_spot_variable = Chain_of_available_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_spot_variable))
	goto end_loop;
    def_structure_spot_variable = ISVREF(def_structure_spot_variable,
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

/* RECLAIM-SPOT-1 */
Object reclaim_spot_1(spot)
    Object spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,32);
    inline_note_reclaim_cons(spot,Nil);
    structure_being_reclaimed = spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(spot,(SI_Long)2L));
      SVREF(spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_spots_vector,IFIX(Current_thread_index));
    SVREF(spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SPOT */
Object reclaim_structure_for_spot(spot)
    Object spot;
{
    x_note_fn_call(61,33);
    return reclaim_spot_1(spot);
}

static Object Qg2_defstruct_structure_name_spot_g2_struct;  /* g2-defstruct-structure-name::spot-g2-struct */

/* MAKE-PERMANENT-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_spot_structure_internal()
{
    Object def_structure_spot_variable, defstruct_g2_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,34);
    def_structure_spot_variable = Nil;
    atomic_incff_symval(Qspot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_spot_variable = Nil;
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
	defstruct_g2_spot_variable = the_array;
	SVREF(defstruct_g2_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_spot_g2_struct;
	def_structure_spot_variable = defstruct_g2_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_spot_variable);
}

/* MAKE-SPOT-1 */
Object make_spot_1()
{
    Object def_structure_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(61,35);
    def_structure_spot_variable = ISVREF(Chain_of_available_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_spot_variable) {
	svref_arg_1 = Chain_of_available_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_spot_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_spot_g2_struct;
    }
    else
	def_structure_spot_variable = make_permanent_spot_structure_internal();
    inline_note_allocate_cons(def_structure_spot_variable,Nil);
    SVREF(def_structure_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_spot_variable);
}

Object The_type_description_of_entire_g2_window_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_entire_g2_window_spots, Qchain_of_available_entire_g2_window_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Entire_g2_window_spot_count, Qentire_g2_window_spot_count);

Object Chain_of_available_entire_g2_window_spots_vector = UNBOUND;

/* ENTIRE-G2-WINDOW-SPOT-STRUCTURE-MEMORY-USAGE */
Object entire_g2_window_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,36);
    temp = Entire_g2_window_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ENTIRE-G2-WINDOW-SPOT-COUNT */
Object outstanding_entire_g2_window_spot_count()
{
    Object def_structure_entire_g2_window_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,37);
    gensymed_symbol = IFIX(Entire_g2_window_spot_count);
    def_structure_entire_g2_window_spot_variable = 
	    Chain_of_available_entire_g2_window_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_entire_g2_window_spot_variable))
	goto end_loop;
    def_structure_entire_g2_window_spot_variable = 
	    ISVREF(def_structure_entire_g2_window_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ENTIRE-G2-WINDOW-SPOT-1 */
Object reclaim_entire_g2_window_spot_1(entire_g2_window_spot)
    Object entire_g2_window_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,38);
    inline_note_reclaim_cons(entire_g2_window_spot,Nil);
    structure_being_reclaimed = entire_g2_window_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(entire_g2_window_spot,(SI_Long)2L));
      SVREF(entire_g2_window_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_entire_g2_window_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(entire_g2_window_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_entire_g2_window_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = entire_g2_window_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ENTIRE-G2-WINDOW-SPOT */
Object reclaim_structure_for_entire_g2_window_spot(entire_g2_window_spot)
    Object entire_g2_window_spot;
{
    x_note_fn_call(61,39);
    return reclaim_entire_g2_window_spot_1(entire_g2_window_spot);
}

static Object Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct;  /* g2-defstruct-structure-name::entire-g2-window-spot-g2-struct */

/* MAKE-PERMANENT-ENTIRE-G2-WINDOW-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_entire_g2_window_spot_structure_internal()
{
    Object def_structure_entire_g2_window_spot_variable;
    Object defstruct_g2_entire_g2_window_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,40);
    def_structure_entire_g2_window_spot_variable = Nil;
    atomic_incff_symval(Qentire_g2_window_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_entire_g2_window_spot_variable = Nil;
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
	defstruct_g2_entire_g2_window_spot_variable = the_array;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_entire_g2_window_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_entire_g2_window_spot_variable = 
		defstruct_g2_entire_g2_window_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_entire_g2_window_spot_variable);
}

/* MAKE-ENTIRE-G2-WINDOW-SPOT-1 */
Object make_entire_g2_window_spot_1()
{
    Object def_structure_entire_g2_window_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(61,41);
    def_structure_entire_g2_window_spot_variable = 
	    ISVREF(Chain_of_available_entire_g2_window_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_entire_g2_window_spot_variable) {
	svref_arg_1 = Chain_of_available_entire_g2_window_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_entire_g2_window_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_entire_g2_window_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct;
    }
    else
	def_structure_entire_g2_window_spot_variable = 
		make_permanent_entire_g2_window_spot_structure_internal();
    inline_note_allocate_cons(def_structure_entire_g2_window_spot_variable,
	    Nil);
    SVREF(def_structure_entire_g2_window_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_entire_g2_window_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_entire_g2_window_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_entire_g2_window_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_entire_g2_window_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_entire_g2_window_spot_variable);
}

Object The_type_description_of_invalid_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_invalid_spots, Qchain_of_available_invalid_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Invalid_spot_count, Qinvalid_spot_count);

Object Chain_of_available_invalid_spots_vector = UNBOUND;

/* INVALID-SPOT-STRUCTURE-MEMORY-USAGE */
Object invalid_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,42);
    temp = Invalid_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INVALID-SPOT-COUNT */
Object outstanding_invalid_spot_count()
{
    Object def_structure_invalid_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,43);
    gensymed_symbol = IFIX(Invalid_spot_count);
    def_structure_invalid_spot_variable = Chain_of_available_invalid_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_invalid_spot_variable))
	goto end_loop;
    def_structure_invalid_spot_variable = 
	    ISVREF(def_structure_invalid_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INVALID-SPOT-1 */
Object reclaim_invalid_spot_1(invalid_spot)
    Object invalid_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,44);
    inline_note_reclaim_cons(invalid_spot,Nil);
    structure_being_reclaimed = invalid_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(invalid_spot,(SI_Long)2L));
      SVREF(invalid_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_invalid_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(invalid_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_invalid_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = invalid_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INVALID-SPOT */
Object reclaim_structure_for_invalid_spot(invalid_spot)
    Object invalid_spot;
{
    x_note_fn_call(61,45);
    return reclaim_invalid_spot_1(invalid_spot);
}

static Object Qg2_defstruct_structure_name_invalid_spot_g2_struct;  /* g2-defstruct-structure-name::invalid-spot-g2-struct */

/* MAKE-PERMANENT-INVALID-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_invalid_spot_structure_internal()
{
    Object def_structure_invalid_spot_variable;
    Object defstruct_g2_invalid_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,46);
    def_structure_invalid_spot_variable = Nil;
    atomic_incff_symval(Qinvalid_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_invalid_spot_variable = Nil;
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
	defstruct_g2_invalid_spot_variable = the_array;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_invalid_spot_g2_struct;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_invalid_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_invalid_spot_variable = 
		defstruct_g2_invalid_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_invalid_spot_variable);
}

/* MAKE-INVALID-SPOT-1 */
Object make_invalid_spot_1()
{
    Object def_structure_invalid_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(61,47);
    def_structure_invalid_spot_variable = 
	    ISVREF(Chain_of_available_invalid_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_invalid_spot_variable) {
	svref_arg_1 = Chain_of_available_invalid_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_invalid_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_invalid_spot_g2_struct;
    }
    else
	def_structure_invalid_spot_variable = 
		make_permanent_invalid_spot_structure_internal();
    inline_note_allocate_cons(def_structure_invalid_spot_variable,Nil);
    SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_invalid_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_invalid_spot_variable);
}

/* RECLAIM-MOUSE-POINTERS */
Object reclaim_mouse_pointers(gensym_list_of_mouse_pointers)
    Object gensym_list_of_mouse_pointers;
{
    Object mouse_pointer, ab_loop_list_;

    x_note_fn_call(61,48);
    mouse_pointer = Nil;
    ab_loop_list_ = gensym_list_of_mouse_pointers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mouse_pointer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_mouse_pointer_1(mouse_pointer);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(gensym_list_of_mouse_pointers);
    return VALUES_1(Nil);
}

/* TRACK-MOUSE-INTO-SPOT-FUNCTION */
Object track_mouse_into_spot_function(spot)
    Object spot;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,49);
    gensymed_symbol = ISVREF(spot,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)2L);
    gensymed_symbol_1 = spot;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* TRACK-MOUSE-POINTER */
Object track_mouse_pointer(mouse_pointer)
    Object mouse_pointer;
{
    Object structure, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,50);
    structure = ISVREF(mouse_pointer,(SI_Long)5L);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)2L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

/* TRACK-MOUSE-POINTER-TILL-DONE */
Object track_mouse_pointer_till_done(mouse_pointer)
    Object mouse_pointer;
{
    Object most_detailed_spot, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,51);
    most_detailed_spot = Nil;
  next_loop:
    most_detailed_spot = ISVREF(mouse_pointer,(SI_Long)5L);
    if ( !TRUEP(ISVREF(most_detailed_spot,(SI_Long)3L)))
	goto end_loop;
    gensymed_symbol = ISVREF(most_detailed_spot,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)2L);
    gensymed_symbol_1 = most_detailed_spot;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MAKE-AN-INITIAL-MOUSE-POINTER */
Object make_an_initial_mouse_pointer(workstation)
    Object workstation;
{
    Object mouse_pointer;

    x_note_fn_call(61,52);
    mouse_pointer = make_mouse_pointer_1(workstation,Illegal_key_code,
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)0L));
    SVREF(mouse_pointer,FIX((SI_Long)6L)) = T;
    push_last_spot(mouse_pointer,make_invalid_spot_1(),Nil);
    return VALUES_1(mouse_pointer);
}

DEFINE_VARIABLE_WITH_SYMBOL(For_workstation, Qfor_workstation);

DEFINE_VARIABLE_WITH_SYMBOL(Servicing_workstation_qm, Qservicing_workstation_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_workstation_detail_pane, Qcurrent_workstation_detail_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm, Qcurrent_g2_window_for_this_workstation_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_g2_user_mode_qm, Qcurrent_g2_user_mode_qm);

DEFINE_VARIABLE_WITH_SYMBOL(New_g2_classic_ui_p, Qnew_g2_classic_ui_p);

Object New_g2_classic_ui_standard_system_workspace_background_color = UNBOUND;

static Object Qstandard_large;     /* standard-large */

static Object Qlarge;              /* large */

static Object Qsmall;              /* small */

static Object Qfont_for_editing;   /* font-for-editing */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qattributes_table_format;  /* attributes-table-format */

static Object Qnew_attributes_table_format;  /* new-attributes-table-format */

static Object Qfont_for_menus;     /* font-for-menus */

static Object Qmenu_item_format;   /* menu-item-format */

static Object Qright;              /* right */

static Object Qleft_arrow_left_aligned_menu_item_format_new_small;  /* left-arrow-left-aligned-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_menu_item_format_new_large;  /* left-arrow-left-aligned-menu-item-format-new-large */

static Object Qleft_aligned_menu_item_format_new_small;  /* left-aligned-menu-item-format-new-small */

static Object Qleft_aligned_menu_item_format_new_large;  /* left-aligned-menu-item-format-new-large */

static Object Qcascade_menu_item_format;  /* cascade-menu-item-format */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_small;  /* left-arrow-left-aligned-cascade-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_large;  /* left-arrow-left-aligned-cascade-menu-item-format-new-large */

static Object Qleft_aligned_cascade_menu_item_format_new_small;  /* left-aligned-cascade-menu-item-format-new-small */

static Object Qleft_aligned_cascade_menu_item_format_new_large;  /* left-aligned-cascade-menu-item-format-new-large */

static Object Qclose_box_x_offset;  /* close-box-x-offset */

static Object Qclose_box_y_offset;  /* close-box-y-offset */

static Object Qfont_for_title_bars;  /* font-for-title-bars */

static Object Qtitle_bar_format;   /* title-bar-format */

static Object Qworkspace_title_bar_frame_style;  /* workspace-title-bar-frame-style */

static Object Qworkspace_title_bar_frame_style_small;  /* workspace-title-bar-frame-style-small */

static Object Qworkspace_title_bar_frame_style_large;  /* workspace-title-bar-frame-style-large */

/* GET-UI-PARAMETER */
Object get_ui_parameter varargs_1(int, n)
{
    Object parameter_name;
    Object adjustment, font_for_editing, font_for_menus, font_for_title_bars;
    Object system_workspace_background_color;
    Declare_varargs_nonrelocating;

    x_note_fn_call(61,53);
    INIT_ARGS_nonrelocating();
    parameter_name = REQUIRED_ARG_nonrelocating();
    adjustment = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    font_for_editing = EQ(New_g2_classic_ui_p,Qstandard_large) ? Qlarge : 
	    Qsmall;
    font_for_menus = EQ(New_g2_classic_ui_p,Qstandard_large) ? Qlarge : Qsmall;
    font_for_title_bars = EQ(New_g2_classic_ui_p,Qstandard_large) ? Qlarge 
	    : Qsmall;
    system_workspace_background_color = 
	    New_g2_classic_ui_standard_system_workspace_background_color;
    if (EQ(parameter_name,Qfont_for_editing))
	return VALUES_1(font_for_editing);
    else if (EQ(parameter_name,Qsystem_workspace_background_color))
	return VALUES_1(system_workspace_background_color);
    else if (EQ(parameter_name,Qattributes_table_format))
	return VALUES_1(Qnew_attributes_table_format);
    else if (EQ(parameter_name,Qfont_for_menus))
	return VALUES_1(font_for_menus);
    else if (EQ(parameter_name,Qmenu_item_format)) {
	if (EQ(adjustment,Qright)) {
	    if (EQ(font_for_menus,Qsmall))
		return VALUES_1(Qleft_arrow_left_aligned_menu_item_format_new_small);
	    else
		return VALUES_1(Qleft_arrow_left_aligned_menu_item_format_new_large);
	}
	else if (EQ(font_for_menus,Qsmall))
	    return VALUES_1(Qleft_aligned_menu_item_format_new_small);
	else
	    return VALUES_1(Qleft_aligned_menu_item_format_new_large);
    }
    else if (EQ(parameter_name,Qcascade_menu_item_format)) {
	if (EQ(adjustment,Qright)) {
	    if (EQ(font_for_menus,Qsmall))
		return VALUES_1(Qleft_arrow_left_aligned_cascade_menu_item_format_new_small);
	    else
		return VALUES_1(Qleft_arrow_left_aligned_cascade_menu_item_format_new_large);
	}
	else if (EQ(font_for_menus,Qsmall))
	    return VALUES_1(Qleft_aligned_cascade_menu_item_format_new_small);
	else
	    return VALUES_1(Qleft_aligned_cascade_menu_item_format_new_large);
    }
    else if (EQ(parameter_name,Qclose_box_x_offset)) {
	if (EQ(font_for_menus,Qsmall))
	    return VALUES_1(FIX((SI_Long)10L));
	else
	    return VALUES_1(FIX((SI_Long)11L));
    }
    else if (EQ(parameter_name,Qclose_box_y_offset)) {
	if (EQ(font_for_menus,Qsmall))
	    return VALUES_1(FIX((SI_Long)7L));
	else
	    return VALUES_1(FIX((SI_Long)16L));
    }
    else if (EQ(parameter_name,Qfont_for_title_bars))
	return VALUES_1(font_for_title_bars);
    else if (EQ(parameter_name,Qtitle_bar_format)) {
	if (EQ(font_for_title_bars,Qsmall))
	    return VALUES_1(Qleft_aligned_menu_item_format_new_small);
	else
	    return VALUES_1(Qleft_aligned_menu_item_format_new_large);
    }
    else if (EQ(parameter_name,Qworkspace_title_bar_frame_style)) {
	if (EQ(font_for_title_bars,Qsmall))
	    return VALUES_1(Qworkspace_title_bar_frame_style_small);
	else
	    return VALUES_1(Qworkspace_title_bar_frame_style_large);
    }
    else
	return VALUES_1(Qnil);
}

Object The_type_description_of_workstation_context = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_workstation_contexts, Qchain_of_available_workstation_contexts);

DEFINE_VARIABLE_WITH_SYMBOL(Workstation_context_count, Qworkstation_context_count);

Object Chain_of_available_workstation_contexts_vector = UNBOUND;

/* WORKSTATION-CONTEXT-STRUCTURE-MEMORY-USAGE */
Object workstation_context_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,54);
    temp = Workstation_context_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-WORKSTATION-CONTEXT-COUNT */
Object outstanding_workstation_context_count()
{
    Object def_structure_workstation_context_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,55);
    gensymed_symbol = IFIX(Workstation_context_count);
    def_structure_workstation_context_variable = 
	    Chain_of_available_workstation_contexts;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_workstation_context_variable))
	goto end_loop;
    def_structure_workstation_context_variable = 
	    ISVREF(def_structure_workstation_context_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-WORKSTATION-CONTEXT-1 */
Object reclaim_workstation_context_1(workstation_context)
    Object workstation_context;
{
    Object temp, svref_arg_2;

    x_note_fn_call(61,56);
    inline_note_reclaim_cons(workstation_context,Nil);
    temp = ISVREF(Chain_of_available_workstation_contexts_vector,
	    IFIX(Current_thread_index));
    SVREF(workstation_context,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_workstation_contexts_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = workstation_context;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WORKSTATION-CONTEXT */
Object reclaim_structure_for_workstation_context(workstation_context)
    Object workstation_context;
{
    x_note_fn_call(61,57);
    return reclaim_workstation_context_1(workstation_context);
}

static Object Qg2_defstruct_structure_name_workstation_context_g2_struct;  /* g2-defstruct-structure-name::workstation-context-g2-struct */

/* MAKE-PERMANENT-WORKSTATION-CONTEXT-STRUCTURE-INTERNAL */
Object make_permanent_workstation_context_structure_internal()
{
    Object def_structure_workstation_context_variable;
    Object defstruct_g2_workstation_context_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,58);
    def_structure_workstation_context_variable = Nil;
    atomic_incff_symval(Qworkstation_context_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_workstation_context_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
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
	defstruct_g2_workstation_context_variable = the_array;
	SVREF(defstruct_g2_workstation_context_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_workstation_context_g2_struct;
	def_structure_workstation_context_variable = 
		defstruct_g2_workstation_context_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_workstation_context_variable);
}

/* MAKE-WORKSTATION-CONTEXT-1 */
Object make_workstation_context_1()
{
    Object def_structure_workstation_context_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(61,59);
    def_structure_workstation_context_variable = 
	    ISVREF(Chain_of_available_workstation_contexts_vector,
	    IFIX(Current_thread_index));
    if (def_structure_workstation_context_variable) {
	svref_arg_1 = Chain_of_available_workstation_contexts_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_workstation_context_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_workstation_context_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_workstation_context_g2_struct;
    }
    else
	def_structure_workstation_context_variable = 
		make_permanent_workstation_context_structure_internal();
    inline_note_allocate_cons(def_structure_workstation_context_variable,Nil);
    return VALUES_1(def_structure_workstation_context_variable);
}

/* RECLAIM-WORKSTATION-CONTEXT-STACK */
Object reclaim_workstation_context_stack(workstation_context_stack)
    Object workstation_context_stack;
{
    Object workstation_context, ab_loop_list_;

    x_note_fn_call(61,60);
    workstation_context = Nil;
    ab_loop_list_ = workstation_context_stack;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation_context = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_workstation_context_1(workstation_context);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(workstation_context_stack);
}

/* ESTABLISH-NEXT-WORKSTATION-CONTEXT-CONTINUATION */
Object establish_next_workstation_context_continuation(continuation_function_qm,
	    old_style_return_function_qm,info,info_reclaimer_qm)
    Object continuation_function_qm, old_style_return_function_qm, info;
    Object info_reclaimer_qm;
{
    x_note_fn_call(61,61);
    Next_continuation_function_qm = continuation_function_qm;
    Next_old_style_return_function_qm = old_style_return_function_qm;
    Next_info = info;
    Next_info_reclaimer_qm = info_reclaimer_qm;
    return VALUES_1(Next_info_reclaimer_qm);
}

static Object Qunknown_is_selection_style;  /* unknown-is-selection-style */

/* ENTER-CONTEXT-IN-CURRENT-WORKSTATION */
Object enter_context_in_current_workstation varargs_1(int, n)
{
    Object type_of_workstation_context;
    Object specific_structure_for_workstation_context;
    Object this_is_a_modal_context_qm, specific_structure_1, gensymed_symbol;
    Object gensymed_symbol_1, listed_new_workstation_context;
    Object new_workstation_context, specific_structure_2, temp;
    Object new_selection_style, old_selection_style;
    Declare_varargs_nonrelocating;

    x_note_fn_call(61,62);
    INIT_ARGS_nonrelocating();
    type_of_workstation_context = REQUIRED_ARG_nonrelocating();
    specific_structure_for_workstation_context = REQUIRED_ARG_nonrelocating();
    this_is_a_modal_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    specific_structure_1 = Specific_structure_for_current_workstation_context;
    if (specific_structure_1) {
	gensymed_symbol = ISVREF(specific_structure_1,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)6L);
	gensymed_symbol_1 = specific_structure_1;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    if ( !TRUEP(Available_workstation_contexts))
	Available_workstation_contexts = 
		gensym_cons_1(make_workstation_context_1(),
		Available_workstation_contexts);
    listed_new_workstation_context = Available_workstation_contexts;
    new_workstation_context = CAR(listed_new_workstation_context);
    specific_structure_2 = Specific_structure_for_current_workstation_context;
    Available_workstation_contexts = CDR(Available_workstation_contexts);
    temp = ISVREF(Current_workstation,(SI_Long)17L);
    M_CDR(listed_new_workstation_context) = temp;
    SVREF(new_workstation_context,FIX((SI_Long)1L)) = 
	    type_of_workstation_context;
    SVREF(new_workstation_context,FIX((SI_Long)2L)) = 
	    specific_structure_for_workstation_context;
    temp = Next_old_style_return_function_qm;
    SVREF(new_workstation_context,FIX((SI_Long)3L)) = temp;
    temp = Next_continuation_function_qm;
    SVREF(new_workstation_context,FIX((SI_Long)4L)) = temp;
    temp = Next_info;
    SVREF(new_workstation_context,FIX((SI_Long)5L)) = temp;
    temp = Next_info_reclaimer_qm;
    SVREF(new_workstation_context,FIX((SI_Long)6L)) = temp;
    Next_continuation_function_qm = Nil;
    Next_old_style_return_function_qm = Nil;
    Next_info = Nil;
    Next_info_reclaimer_qm = Nil;
    temp = Current_workstation;
    SVREF(temp,FIX((SI_Long)17L)) = listed_new_workstation_context;
    if (SVREF(new_workstation_context,FIX((SI_Long)8L)) = 
	    this_is_a_modal_context_qm) {
	temp = Current_workstation;
	SVREF(temp,FIX((SI_Long)18L)) = type_of_workstation_context;
    }
    Current_workstation_context = new_workstation_context;
    Type_of_current_workstation_context = type_of_workstation_context;
    new_selection_style = 
	    selection_style_of_workstation_context(specific_structure_for_workstation_context);
    old_selection_style = specific_structure_2 ? 
	    selection_style_of_workstation_context(specific_structure_2) : 
	    Qunknown_is_selection_style;
    Specific_structure_for_current_workstation_context = 
	    specific_structure_for_workstation_context;
    synchronize_selection_style(old_selection_style,new_selection_style);
    gensymed_symbol = 
	    ISVREF(Specific_structure_for_current_workstation_context,
	    (SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)5L);
    gensymed_symbol_1 = Specific_structure_for_current_workstation_context;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qspecific_structure_has_been_reclaimed;  /* specific-structure-has-been-reclaimed */

/* UNWIND-ONE-WORKSTATION-CONTEXT */
Object unwind_one_workstation_context()
{
    Object continuation_qm, old_selection_style, old_workstation_context_stack;
    Object workstation_context_return_information_reclaimer_qm;
    Object gensymed_symbol, gensymed_symbol_1, temp, temp_1, svref_new_value;
    Object workstation_context, ab_loop_list_, new_selection_style;

    x_note_fn_call(61,63);
    continuation_qm = ISVREF(Current_workstation_context,(SI_Long)4L);
    old_selection_style = 
	    selection_style_of_workstation_context(Specific_structure_for_current_workstation_context);
    old_workstation_context_stack = ISVREF(Current_workstation,(SI_Long)17L);
    workstation_context_return_information_reclaimer_qm = 
	    ISVREF(Current_workstation_context,(SI_Long)6L);
    gensymed_symbol = 
	    ISVREF(Specific_structure_for_current_workstation_context,
	    (SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)1L);
    gensymed_symbol_1 = Specific_structure_for_current_workstation_context;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    Specific_structure_for_current_workstation_context = 
	    Qspecific_structure_has_been_reclaimed;
    if (workstation_context_return_information_reclaimer_qm) {
	temp = 
		SYMBOL_FUNCTION(workstation_context_return_information_reclaimer_qm);
	FUNCALL_1(temp,ISVREF(Current_workstation_context,(SI_Long)5L));
    }
    temp_1 = Current_workstation;
    svref_new_value = CDR(old_workstation_context_stack);
    SVREF(temp_1,FIX((SI_Long)17L)) = svref_new_value;
    temp_1 = Current_workstation_context;
    SVREF(temp_1,FIX((SI_Long)5L)) = Nil;
    temp_1 = Available_workstation_contexts;
    M_CDR(old_workstation_context_stack) = temp_1;
    Available_workstation_contexts = old_workstation_context_stack;
    temp = ISVREF(Current_workstation,(SI_Long)17L);
    Current_workstation_context = CAR(temp);
    if (Current_workstation_context) {
	Type_of_current_workstation_context = 
		ISVREF(Current_workstation_context,(SI_Long)1L);
	Specific_structure_for_current_workstation_context = 
		ISVREF(Current_workstation_context,(SI_Long)2L);
	workstation_context = Nil;
	ab_loop_list_ = ISVREF(Current_workstation,(SI_Long)17L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation_context = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ISVREF(workstation_context,(SI_Long)8L)) {
	    temp_1 = Current_workstation;
	    svref_new_value = ISVREF(workstation_context,(SI_Long)1L);
	    SVREF(temp_1,FIX((SI_Long)18L)) = svref_new_value;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = Current_workstation;
	SVREF(temp_1,FIX((SI_Long)18L)) = Nil;
      end_1:;
	new_selection_style = 
		selection_style_of_workstation_context(Specific_structure_for_current_workstation_context);
	synchronize_selection_style(old_selection_style,new_selection_style);
	if (valid_workstation_context_p_function(Specific_structure_for_current_workstation_context)) 
		    {
	    gensymed_symbol = 
		    ISVREF(Specific_structure_for_current_workstation_context,
		    (SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)7L);
	    gensymed_symbol_1 = 
		    Specific_structure_for_current_workstation_context;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    if (continuation_qm) {
		temp = SYMBOL_FUNCTION(continuation_qm);
		FUNCALL_1(temp,Current_workstation_context);
	    }
	}
    }
    return reset_current_workstation_context_return_values();
}

/* RESET-CURRENT-WORKSTATION-CONTEXT-RETURN-VALUES */
Object reset_current_workstation_context_return_values()
{
    Object svref_arg_1, temp;

    x_note_fn_call(61,64);
    svref_arg_1 = Current_workstation;
    temp = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(Current_workstation,
	    (SI_Long)33L));
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = temp;
    svref_arg_1 = Current_workstation;
    temp = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(Current_workstation,
	    (SI_Long)34L));
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = temp;
    svref_arg_1 = Current_workstation;
    temp = Nil;
    reclaim_gensym_tree_with_text_strings(ISVREF(Current_workstation,
	    (SI_Long)35L));
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)35L)) = temp);
}

/* UNWIND-ONE-WORKSTATION-CONTEXT-SAFELY */
Object unwind_one_workstation_context_safely()
{
    Object temp;

    x_note_fn_call(61,65);
    temp = ISVREF(Current_workstation,(SI_Long)17L);
    if (CDR(temp))
	return unwind_one_workstation_context();
    else
	return VALUES_1(Nil);
}

/* ABORT-CURRENT-WORKSTATION-CONTEXT */
Object abort_current_workstation_context(context_name)
    Object context_name;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(61,66);
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = Kabort;
    svref_arg_1 = Current_workstation;
    svref_new_value = ISVREF(Current_workstation,(SI_Long)11L);
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = svref_new_value;
    return unwind_one_workstation_context_safely();
}

/* EXIT-CURRENT-WORKSTATION-CONTEXT-IN-RETURN-FUNCTION */
Object exit_current_workstation_context_in_return_function(context_name)
    Object context_name;
{
    x_note_fn_call(61,67);
    return unwind_one_workstation_context_safely();
}

/* RETURN-FROM-CURRENT-WORKSTATION-CONTEXT */
Object return_from_current_workstation_context varargs_1(int, n)
{
    Object context_name;
    Object v1, v2, v3, svref_arg_1, old_style_return_function_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(61,68);
    INIT_ARGS_nonrelocating();
    context_name = REQUIRED_ARG_nonrelocating();
    v1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    v2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    v3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = v1;
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = v2;
    svref_arg_1 = Current_workstation;
    SVREF(svref_arg_1,FIX((SI_Long)35L)) = v3;
    old_style_return_function_qm = ISVREF(Current_workstation_context,
	    (SI_Long)3L);
    if (old_style_return_function_qm) {
	temp = SYMBOL_FUNCTION(old_style_return_function_qm);
	return FUNCALL_1(temp,Current_workstation_context);
    }
    else
	return unwind_one_workstation_context_safely();
}

static Object Qunwind_all_workstation_contexts;  /* unwind-all-workstation-contexts */

/* UNWIND-ALL-WORKSTATION-CONTEXTS */
Object unwind_all_workstation_contexts(workstation)
    Object workstation;
{
    Object index_of_top_of_backtrace_stack, temp, temp_1;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_2;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(13);
    Object result;

    x_note_fn_call(61,69);
    SAVE_STACK();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    12);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Qunwind_all_workstation_contexts;
      }
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
			  ISVREF(Current_workstation_window,(SI_Long)17L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			  7);
		    temp_2 = ISVREF(Current_workstation,(SI_Long)17L);
		    current_workstation_context = CAR(temp_2);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			    6);
		      type_of_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)1L);
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
				next_loop:
				  if ( !TRUEP(ISVREF(Current_workstation,
					  (SI_Long)17L)))
				      goto end_loop;
				  temp = Current_workstation;
				  SVREF(temp,FIX((SI_Long)33L)) = Kabort;
				  temp = Current_workstation;
				  temp_1 = ISVREF(Current_workstation,
					  (SI_Long)11L);
				  SVREF(temp,FIX((SI_Long)34L)) = temp_1;
				  unwind_one_workstation_context();
				  goto next_loop;
				end_loop:
				  SAVE_VALUES(VALUES_1(Qnil));
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

static Object Qunwind_current_workstation_back_to_top_level;  /* unwind-current-workstation-back-to-top-level */

/* UNWIND-CURRENT-WORKSTATION-BACK-TO-TOP-LEVEL */
Object unwind_current_workstation_back_to_top_level()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(61,70);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
	  SVREF(temp,svref_arg_2) = 
		  Qunwind_current_workstation_back_to_top_level;
      }
    next_loop:
      temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
      if ( !TRUEP(CDR(temp_1)))
	  goto end_loop;
      abort_current_workstation_context(Type_of_current_workstation_context);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-WORKSTATION-CONTEXT-FRAME */
Object clean_up_workstation_context_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,71);
    gensymed_symbol = ISVREF(workstation_context_frame,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = workstation_context_frame;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* SETUP-WORKSTATION-CONTEXT-FOR-WORKSTATION-CONTEXT-FRAME */
Object setup_workstation_context_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    x_note_fn_call(61,72);
    return VALUES_1(Nil);
}

/* RESUME-WORKSTATION-CONTEXT-FOR-WORKSTATION-CONTEXT-FRAME */
Object resume_workstation_context_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    x_note_fn_call(61,73);
    return VALUES_1(Nil);
}

/* SUSPEND-WORKSTATION-CONTEXT-FOR-WORKSTATION-CONTEXT-FRAME */
Object suspend_workstation_context_for_workstation_context_frame(workstation_context_frame)
    Object workstation_context_frame;
{
    x_note_fn_call(61,74);
    return VALUES_1(Nil);
}

/* ADD-MOUSE-POINTER-TO-GUARDIANS-OF-WORKSTATION-CONTEXT */
Object add_mouse_pointer_to_guardians_of_workstation_context(mouse_pointer,
	    workstation_context_frame)
    Object mouse_pointer, workstation_context_frame;
{
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(61,75);
    gensym_modify_macro_using_test_arg_1 = 
	    reference_mouse_pointer(mouse_pointer);
    car_1 = gensym_modify_macro_using_test_arg_1;
    cdr_1 = ISVREF(workstation_context_frame,(SI_Long)1L);
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
    svref_new_value = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
    return VALUES_1(SVREF(workstation_context_frame,FIX((SI_Long)1L)) = 
	    svref_new_value);
}

Object The_type_description_of_top_level_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_top_level_states, Qchain_of_available_top_level_states);

DEFINE_VARIABLE_WITH_SYMBOL(Top_level_state_count, Qtop_level_state_count);

Object Chain_of_available_top_level_states_vector = UNBOUND;

/* TOP-LEVEL-STATE-STRUCTURE-MEMORY-USAGE */
Object top_level_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(61,76);
    temp = Top_level_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TOP-LEVEL-STATE-COUNT */
Object outstanding_top_level_state_count()
{
    Object def_structure_top_level_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(61,77);
    gensymed_symbol = IFIX(Top_level_state_count);
    def_structure_top_level_state_variable = 
	    Chain_of_available_top_level_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_top_level_state_variable))
	goto end_loop;
    def_structure_top_level_state_variable = 
	    ISVREF(def_structure_top_level_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TOP-LEVEL-STATE-1 */
Object reclaim_top_level_state_1(top_level_state)
    Object top_level_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(61,78);
    inline_note_reclaim_cons(top_level_state,Nil);
    structure_being_reclaimed = top_level_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(top_level_state,(SI_Long)1L));
      SVREF(top_level_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(top_level_state,(SI_Long)2L));
      SVREF(top_level_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_top_level_states_vector,
	    IFIX(Current_thread_index));
    SVREF(top_level_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_top_level_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = top_level_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TOP-LEVEL-STATE */
Object reclaim_structure_for_top_level_state(top_level_state)
    Object top_level_state;
{
    x_note_fn_call(61,79);
    return reclaim_top_level_state_1(top_level_state);
}

static Object Qg2_defstruct_structure_name_top_level_state_g2_struct;  /* g2-defstruct-structure-name::top-level-state-g2-struct */

/* MAKE-PERMANENT-TOP-LEVEL-STATE-STRUCTURE-INTERNAL */
Object make_permanent_top_level_state_structure_internal()
{
    Object def_structure_top_level_state_variable;
    Object defstruct_g2_top_level_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(61,80);
    def_structure_top_level_state_variable = Nil;
    atomic_incff_symval(Qtop_level_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_top_level_state_variable = Nil;
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
	defstruct_g2_top_level_state_variable = the_array;
	SVREF(defstruct_g2_top_level_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_top_level_state_g2_struct;
	SVREF(defstruct_g2_top_level_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_top_level_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_top_level_state_variable = 
		defstruct_g2_top_level_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_top_level_state_variable);
}

/* MAKE-TOP-LEVEL-STATE-1 */
Object make_top_level_state_1()
{
    Object def_structure_top_level_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(61,81);
    def_structure_top_level_state_variable = 
	    ISVREF(Chain_of_available_top_level_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_top_level_state_variable) {
	temp = Chain_of_available_top_level_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_top_level_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_top_level_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_top_level_state_g2_struct;
    }
    else
	def_structure_top_level_state_variable = 
		make_permanent_top_level_state_structure_internal();
    inline_note_allocate_cons(def_structure_top_level_state_variable,Nil);
    SVREF(def_structure_top_level_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_top_level_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_top_level_state_variable);
}

/* PUT-GENSYM-WINDOW-IN-V5-MODE-INTERNAL */
Object put_gensym_window_in_v5_mode_internal(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(61,82);
    SVREF(gensym_window,FIX((SI_Long)33L)) = T;
    return set_v5_mode_state(T);
}

static Object Qtop_level;          /* top-level */

/* SET-UP-WORKSTATION-ON-AB-SIDE */
Object set_up_workstation_on_ab_side(workstation,gensym_window,v5_mode_p)
    Object workstation, gensym_window, v5_mode_p;
{
    Object current_workstation_1, current_workstation_window;
    Object type_of_current_workstation_window;
    Object specific_structure_for_current_workstation_context;
    Object type_of_current_workstation_context, current_workstation_context;
    Object svref_new_value, gensym_push_modify_macro_arg, car_1, cdr_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(61,83);
    current_workstation_1 = workstation;
    current_workstation_window = gensym_window;
    type_of_current_workstation_window = ISVREF(gensym_window,(SI_Long)1L);
    specific_structure_for_current_workstation_context = Nil;
    type_of_current_workstation_context = Nil;
    current_workstation_context = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
	    5);
      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
	      4);
	PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		      0);
		if (v5_mode_p)
		    put_gensym_window_in_v5_mode_internal(gensym_window);
		svref_new_value = make_an_initial_mouse_pointer(workstation);
		SVREF(workstation,FIX((SI_Long)11L)) = svref_new_value;
		svref_new_value = make_an_initial_mouse_pointer(workstation);
		SVREF(workstation,FIX((SI_Long)12L)) = svref_new_value;
		svref_new_value = make_an_initial_mouse_pointer(workstation);
		SVREF(workstation,FIX((SI_Long)13L)) = svref_new_value;
		svref_new_value = make_an_initial_mouse_pointer(workstation);
		SVREF(workstation,FIX((SI_Long)54L)) = svref_new_value;
		gensym_push_modify_macro_arg = ISVREF(workstation,
			(SI_Long)11L);
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = ISVREF(workstation,(SI_Long)14L);
		svref_new_value = gensym_cons_1(car_1,cdr_1);
		SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
		gensym_push_modify_macro_arg = ISVREF(workstation,
			(SI_Long)12L);
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = ISVREF(workstation,(SI_Long)14L);
		svref_new_value = gensym_cons_1(car_1,cdr_1);
		SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
		gensym_push_modify_macro_arg = ISVREF(workstation,
			(SI_Long)13L);
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = ISVREF(workstation,(SI_Long)14L);
		svref_new_value = gensym_cons_1(car_1,cdr_1);
		SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
		gensym_push_modify_macro_arg = ISVREF(workstation,
			(SI_Long)54L);
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = ISVREF(workstation,(SI_Long)14L);
		svref_new_value = gensym_cons_1(car_1,cdr_1);
		SVREF(workstation,FIX((SI_Long)14L)) = svref_new_value;
		svref_new_value = Current_workstation;
		SVREF(gensym_window,FIX((SI_Long)2L)) = svref_new_value;
		enter_context_in_current_workstation(2,Qtop_level,
			make_top_level_state_1());
		Workstations_in_service = 
			gensym_cons_1(Current_workstation,
			Workstations_in_service);
		set_session_info_in_workstation(gensym_window,workstation);
		if (EQ(gensym_window,System_window))
		    start_or_restart_native_window_heartbeat();
		svref_new_value = show_selection_handles_p(1,gensym_window);
		SVREF(gensym_window,FIX((SI_Long)68L)) = svref_new_value;
		result = VALUES_1(Current_workstation);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_system_dummy_workstation_qm, Qcurrent_system_dummy_workstation_qm);

/* GET-OR-MAKE-DUMMY-WORKSTATION */
Object get_or_make_dummy_workstation()
{
    Object temp, workstation;
    Object specific_structure_for_current_workstation_context, svref_new_value;
    Object current_workstation_1, current_workstation_window;
    Object current_workstation_native_window_qm;
    Object type_of_current_workstation_window;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(61,84);
    SAVE_STACK();
    temp = Current_system_dummy_workstation_qm;
    if (temp) {
	RESTORE_STACK();
	return VALUES_1(temp);
    }
    else {
	workstation = make_workstation_1(Nil);
	specific_structure_for_current_workstation_context = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
		4);
	  Current_system_dummy_workstation_qm = workstation;
	  svref_new_value = make_gensym_window(Nil);
	  SVREF(workstation,FIX((SI_Long)1L)) = svref_new_value;
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
		      enter_context_in_current_workstation(2,Qtop_level,
			      make_top_level_state_1());
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_UNWIND_PROTECT(0);
	  UNLOCK(For_workstation_polling);
	  CONTINUE_UNWINDING(0);
	  result = VALUES_1(workstation);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

/* DUMMY-WORKSTATION-P */
Object dummy_workstation_p(workstation)
    Object workstation;
{
    Object temp;

    x_note_fn_call(61,85);
    temp = EQ(workstation,Current_system_dummy_workstation_qm) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(ISVREF(workstation,(SI_Long)1L)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1( !TRUEP(ISVREF(ISVREF(workstation,(SI_Long)1L),
		(SI_Long)2L)) ? T : Nil);
}

void mice_INIT()
{
    Object temp, reclaim_structure_for_workstation_context_frame_1;
    Object reclaim_structure_for_mouse_pointer_1;
    Object reclaim_structure_for_workstation_context_with_selection_focus_1;
    Object reclaim_structure_for_spot_1, type_description, temp_1;
    Object reclaim_structure_for_entire_g2_window_spot_1;
    Object reclaim_structure_for_invalid_spot_1;
    Object named_dynamic_extent_description, cdddr_new_value;
    Object reclaim_structure_for_workstation_context_1;
    Object clean_up_workstation_context_for_workstation_context_frame_1;
    Object setup_workstation_context_for_workstation_context_frame_1;
    Object resume_workstation_context_for_workstation_context_frame_1;
    Object suspend_workstation_context_for_workstation_context_frame_1;
    Object reclaim_structure_for_top_level_state_1;
    Object Qmice, AB_package, Qtop_level_state, Qreclaim_structure;
    Object Qoutstanding_top_level_state_count;
    Object Qtop_level_state_structure_memory_usage, Qutilities2;
    Object string_constant_16, Qtype_description_of_type, string_constant_15;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qworkstation_context_frame;
    Object Qsuspend_workstation_context, Qresume_workstation_context;
    Object Qsetup_workstation_context, Qclean_up_workstation_context;
    Object Qworkstation, Qworkstation_context;
    Object Qoutstanding_workstation_context_count;
    Object Qworkstation_context_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qsmoke, Qnamed_dynamic_extent_description;
    Object Qunwind_qm, list_constant, string_constant_12;
    Object Qtype_of_frame_represented, Qabstract_type, Qspot;
    Object Qenclosing_spot_type, Qinnermost_spot_p, Qinvalid_spot;
    Object Qoutstanding_invalid_spot_count;
    Object Qinvalid_spot_structure_memory_usage, string_constant_11;
    Object string_constant_10, Qg2_window, Qentire_g2_window_spot;
    Object Qoutstanding_entire_g2_window_spot_count;
    Object Qentire_g2_window_spot_structure_memory_usage, string_constant_9;
    Object string_constant_8, Qoutstanding_spot_count;
    Object Qspot_structure_memory_usage, string_constant_7, string_constant_6;
    Object Qworkstation_context_with_selection_focus;
    Object Qoutstanding_workstation_context_with_selection_focus_count;
    Object Qworkstation_context_with_selection_focus_structure_memory_usage;
    Object string_constant_5, string_constant_4, Qmouse_pointer;
    Object Qoutstanding_mouse_pointer_count;
    Object Qmouse_pointer_structure_memory_usage, string_constant_3;
    Object string_constant_2, Qoutstanding_workstation_context_frame_count;
    Object Qworkstation_context_frame_structure_memory_usage;
    Object string_constant_1, string_constant;

    x_note_fn_call(61,86);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_workstation_context_frame_g2_struct = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-FRAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qworkstation_context_frame = STATIC_SYMBOL("WORKSTATION-CONTEXT-FRAME",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_frame_g2_struct,
	    Qworkstation_context_frame,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qworkstation_context_frame,
	    Qg2_defstruct_structure_name_workstation_context_frame_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workstation_context_frame == UNBOUND)
	The_type_description_of_workstation_context_frame = Nil;
    string_constant = STATIC_STRING("43Dy8m83-Sy1n83-Sy8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_workstation_context_frame;
    The_type_description_of_workstation_context_frame = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_frame_g2_struct,
	    The_type_description_of_workstation_context_frame,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qworkstation_context_frame,
	    The_type_description_of_workstation_context_frame,
	    Qtype_description_of_type);
    Qoutstanding_workstation_context_frame_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSTATION-CONTEXT-FRAME-COUNT",
	    AB_package);
    Qworkstation_context_frame_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-FRAME-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q83-Sy8s83-xby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workstation_context_frame_count);
    push_optimized_constant(Qworkstation_context_frame_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_workstation_context_frames = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSTATION-CONTEXT-FRAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workstation_context_frames,
	    Chain_of_available_workstation_context_frames);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_workstation_context_frames,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qworkstation_context_frame_count = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-FRAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_context_frame_count,
	    Workstation_context_frame_count);
    record_system_variable(Qworkstation_context_frame_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workstation_context_frames_vector == UNBOUND)
	Chain_of_available_workstation_context_frames_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkstation_context_frame_structure_memory_usage,
	    STATIC_FUNCTION(workstation_context_frame_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workstation_context_frame_count,
	    STATIC_FUNCTION(outstanding_workstation_context_frame_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qworkstation_context_frame,
	    reclaim_structure_for_workstation_context_frame_1);
    Qg2_defstruct_structure_name_mouse_pointer_g2_struct = 
	    STATIC_SYMBOL("MOUSE-POINTER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmouse_pointer = STATIC_SYMBOL("MOUSE-POINTER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_mouse_pointer_g2_struct,
	    Qmouse_pointer,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmouse_pointer,
	    Qg2_defstruct_structure_name_mouse_pointer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_mouse_pointer == UNBOUND)
	The_type_description_of_mouse_pointer = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83ksy1n83ksy8n8k1l8n0000001m1n8y83-4sy1p83-H3y83-1by83wLy83-H7y83-HDy1m83=0y83-9Cykxk0k0");
    temp = The_type_description_of_mouse_pointer;
    The_type_description_of_mouse_pointer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    mutate_global_property(Qg2_defstruct_structure_name_mouse_pointer_g2_struct,
	    The_type_description_of_mouse_pointer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmouse_pointer,
	    The_type_description_of_mouse_pointer,Qtype_description_of_type);
    Qoutstanding_mouse_pointer_count = 
	    STATIC_SYMBOL("OUTSTANDING-MOUSE-POINTER-COUNT",AB_package);
    Qmouse_pointer_structure_memory_usage = 
	    STATIC_SYMBOL("MOUSE-POINTER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_3 = STATIC_STRING("1q83ksy8s83-fey09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_mouse_pointer_count);
    push_optimized_constant(Qmouse_pointer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_mouse_pointers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MOUSE-POINTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_mouse_pointers,
	    Chain_of_available_mouse_pointers);
    record_system_variable(Qchain_of_available_mouse_pointers,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qmouse_pointer_count = STATIC_SYMBOL("MOUSE-POINTER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmouse_pointer_count,Mouse_pointer_count);
    record_system_variable(Qmouse_pointer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_mouse_pointers_vector == UNBOUND)
	Chain_of_available_mouse_pointers_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmouse_pointer_structure_memory_usage,
	    STATIC_FUNCTION(mouse_pointer_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_mouse_pointer_count,
	    STATIC_FUNCTION(outstanding_mouse_pointer_count,NIL,FALSE,0,0));
    reclaim_structure_for_mouse_pointer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_mouse_pointer,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmouse_pointer,
	    reclaim_structure_for_mouse_pointer_1);
    Qmulti = STATIC_SYMBOL("MULTI",AB_package);
    Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct 
	    = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qworkstation_context_with_selection_focus = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct,
	    Qworkstation_context_with_selection_focus,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qworkstation_context_with_selection_focus,
	    Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workstation_context_with_selection_focus 
	    == UNBOUND)
	The_type_description_of_workstation_context_with_selection_focus = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8m830Vy1o830Vy83-Sy8n8k1l83-Sy0000001l1m8x83-Sykqk0k0");
    temp = The_type_description_of_workstation_context_with_selection_focus;
    The_type_description_of_workstation_context_with_selection_focus = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_with_selection_focus_g2_struct,
	    The_type_description_of_workstation_context_with_selection_focus,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qworkstation_context_with_selection_focus,
	    The_type_description_of_workstation_context_with_selection_focus,
	    Qtype_description_of_type);
    Qoutstanding_workstation_context_with_selection_focus_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-COUNT",
	    AB_package);
    Qworkstation_context_with_selection_focus_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_5 = STATIC_STRING("1q830Vy8s83-xcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workstation_context_with_selection_focus_count);
    push_optimized_constant(Qworkstation_context_with_selection_focus_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qchain_of_available_workstation_context_with_selection_focuss = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSTATION-CONTEXT-WITH-SELECTION-FOCUSS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workstation_context_with_selection_focuss,
	    Chain_of_available_workstation_context_with_selection_focuss);
    record_system_variable(Qchain_of_available_workstation_context_with_selection_focuss,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qworkstation_context_with_selection_focus_count = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-WITH-SELECTION-FOCUS-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_context_with_selection_focus_count,
	    Workstation_context_with_selection_focus_count);
    record_system_variable(Qworkstation_context_with_selection_focus_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workstation_context_with_selection_focuss_vector 
	    == UNBOUND)
	Chain_of_available_workstation_context_with_selection_focuss_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkstation_context_with_selection_focus_structure_memory_usage,
	    STATIC_FUNCTION(workstation_context_with_selection_focus_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workstation_context_with_selection_focus_count,
	    STATIC_FUNCTION(outstanding_workstation_context_with_selection_focus_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_workstation_context_with_selection_focus_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workstation_context_with_selection_focus,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qworkstation_context_with_selection_focus,
	    reclaim_structure_for_workstation_context_with_selection_focus_1);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    Selection_style_of_workstation_context_type_prop = 
	    Qselection_style_of_workstation_context_type;
    Qtop_level_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-IS-SELECTION-STYLE",AB_package);
    Qnative_window_heartbeat_task = 
	    STATIC_SYMBOL("NATIVE-WINDOW-HEARTBEAT-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnative_window_heartbeat_task,
	    Native_window_heartbeat_task);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    record_system_variable(Qnative_window_heartbeat_task,Qworkstation,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnative_window_heartbeat = STATIC_SYMBOL("NATIVE-WINDOW-HEARTBEAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnative_window_heartbeat,
	    STATIC_FUNCTION(native_window_heartbeat,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_spot_g2_struct = 
	    STATIC_SYMBOL("SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_spot_g2_struct,
	    Qspot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qspot,
	    Qg2_defstruct_structure_name_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_spot == UNBOUND)
	The_type_description_of_spot = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83Qy1n83Qy8n8k1l8n0000001l1m8x8nkqk0k0");
    temp = The_type_description_of_spot;
    The_type_description_of_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    mutate_global_property(Qg2_defstruct_structure_name_spot_g2_struct,
	    The_type_description_of_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qspot,The_type_description_of_spot,
	    Qtype_description_of_type);
    Qoutstanding_spot_count = STATIC_SYMBOL("OUTSTANDING-SPOT-COUNT",
	    AB_package);
    Qspot_structure_memory_usage = 
	    STATIC_SYMBOL("SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_7 = STATIC_STRING("1q83Qy8s83-qTy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_spot_count);
    push_optimized_constant(Qspot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_spots = STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_spots,
	    Chain_of_available_spots);
    record_system_variable(Qchain_of_available_spots,Qutilities2,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qspot_count = STATIC_SYMBOL("SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qspot_count,Spot_count);
    record_system_variable(Qspot_count,Qutilities2,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    if (Chain_of_available_spots_vector == UNBOUND)
	Chain_of_available_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qspot_structure_memory_usage,
	    STATIC_FUNCTION(spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_spot_count,
	    STATIC_FUNCTION(outstanding_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qspot,
	    reclaim_structure_for_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qspot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qspot),LIST_2(Qabstract_type,Qt),
	    LIST_2(Qtype_of_frame_represented,Qnull),
	    ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct = 
	    STATIC_SYMBOL("ENTIRE-G2-WINDOW-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qentire_g2_window_spot = STATIC_SYMBOL("ENTIRE-G2-WINDOW-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct,
	    Qentire_g2_window_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qentire_g2_window_spot,
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_entire_g2_window_spot == UNBOUND)
	The_type_description_of_entire_g2_window_spot = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83h2y1o83h2y83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_entire_g2_window_spot;
    The_type_description_of_entire_g2_window_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    mutate_global_property(Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct,
	    The_type_description_of_entire_g2_window_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qentire_g2_window_spot,
	    The_type_description_of_entire_g2_window_spot,
	    Qtype_description_of_type);
    Qoutstanding_entire_g2_window_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-ENTIRE-G2-WINDOW-SPOT-COUNT",
	    AB_package);
    Qentire_g2_window_spot_structure_memory_usage = 
	    STATIC_SYMBOL("ENTIRE-G2-WINDOW-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q83h2y8s83-Sqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_entire_g2_window_spot_count);
    push_optimized_constant(Qentire_g2_window_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_entire_g2_window_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ENTIRE-G2-WINDOW-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_entire_g2_window_spots,
	    Chain_of_available_entire_g2_window_spots);
    record_system_variable(Qchain_of_available_entire_g2_window_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qentire_g2_window_spot_count = 
	    STATIC_SYMBOL("ENTIRE-G2-WINDOW-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentire_g2_window_spot_count,
	    Entire_g2_window_spot_count);
    record_system_variable(Qentire_g2_window_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_entire_g2_window_spots_vector == UNBOUND)
	Chain_of_available_entire_g2_window_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qentire_g2_window_spot_structure_memory_usage,
	    STATIC_FUNCTION(entire_g2_window_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_entire_g2_window_spot_count,
	    STATIC_FUNCTION(outstanding_entire_g2_window_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_entire_g2_window_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_entire_g2_window_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qentire_g2_window_spot,
	    reclaim_structure_for_entire_g2_window_spot_1);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qentire_g2_window_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qnull),LIST_2(Qabstract_type,Qt),
	    LIST_2(Qtype_of_frame_represented,Qg2_window),
	    ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_invalid_spot_g2_struct = 
	    STATIC_SYMBOL("INVALID-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinvalid_spot = STATIC_SYMBOL("INVALID-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_invalid_spot_g2_struct,
	    Qinvalid_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qinvalid_spot,
	    Qg2_defstruct_structure_name_invalid_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_invalid_spot == UNBOUND)
	The_type_description_of_invalid_spot = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83j8y1o83j8y83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_invalid_spot;
    The_type_description_of_invalid_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_invalid_spot_g2_struct,
	    The_type_description_of_invalid_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qinvalid_spot,
	    The_type_description_of_invalid_spot,Qtype_description_of_type);
    Qoutstanding_invalid_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-INVALID-SPOT-COUNT",AB_package);
    Qinvalid_spot_structure_memory_usage = 
	    STATIC_SYMBOL("INVALID-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q83j8y8s83-aZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_invalid_spot_count);
    push_optimized_constant(Qinvalid_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_invalid_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INVALID-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_invalid_spots,
	    Chain_of_available_invalid_spots);
    record_system_variable(Qchain_of_available_invalid_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qinvalid_spot_count = STATIC_SYMBOL("INVALID-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinvalid_spot_count,Invalid_spot_count);
    record_system_variable(Qinvalid_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_invalid_spots_vector == UNBOUND)
	Chain_of_available_invalid_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinvalid_spot_structure_memory_usage,
	    STATIC_FUNCTION(invalid_spot_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_invalid_spot_count,
	    STATIC_FUNCTION(outstanding_invalid_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_invalid_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_invalid_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qinvalid_spot,
	    reclaim_structure_for_invalid_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinvalid_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qspot),LIST_2(Qabstract_type,Qt),
	    LIST_2(Qtype_of_frame_represented,Qnull),
	    ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    string_constant_12 = STATIC_STRING("FOR-WORKSTATION");
    if (For_workstation == UNBOUND)
	For_workstation = make_recursive_lock(2,Kname,string_constant_12);
    Qfor_workstation = STATIC_SYMBOL("FOR-WORKSTATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfor_workstation,For_workstation);
    Qfor_workstation_polling = STATIC_SYMBOL("FOR-WORKSTATION-POLLING",
	    AB_package);
    Qfor_workstation_context = STATIC_SYMBOL("FOR-WORKSTATION-CONTEXT",
	    AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qfor_workstation_polling,
	    Qfor_workstation_context);
    Qunwind_qm = STATIC_SYMBOL("UNWIND\?",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qfor_workstation,
	    Qworkstation,Nil,Qnil,Qnil,list_constant,Nil);
    temp_1 = CDDDR(named_dynamic_extent_description);
    cdddr_new_value = set_getf(CDDDR(temp_1),Qunwind_qm,T);
    M_CDDDR(temp_1) = cdddr_new_value;
    mutate_global_property(Qfor_workstation,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Servicing_workstation_qm == UNBOUND)
	Servicing_workstation_qm = Nil;
    Qnew_g2_classic_ui_p = STATIC_SYMBOL("NEW-G2-CLASSIC-UI-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_g2_classic_ui_p,New_g2_classic_ui_p);
    Qmice = STATIC_SYMBOL("MICE",AB_package);
    record_system_variable(Qnew_g2_classic_ui_p,Qmice,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsmoke = STATIC_SYMBOL("SMOKE",AB_package);
    New_g2_classic_ui_standard_system_workspace_background_color = Qsmoke;
    Qstandard_large = STATIC_SYMBOL("STANDARD-LARGE",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qfont_for_editing = STATIC_SYMBOL("FONT-FOR-EDITING",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qattributes_table_format = STATIC_SYMBOL("ATTRIBUTES-TABLE-FORMAT",
	    AB_package);
    Qnew_attributes_table_format = 
	    STATIC_SYMBOL("NEW-ATTRIBUTES-TABLE-FORMAT",AB_package);
    Qfont_for_menus = STATIC_SYMBOL("FONT-FOR-MENUS",AB_package);
    Qmenu_item_format = STATIC_SYMBOL("MENU-ITEM-FORMAT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qleft_arrow_left_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qcascade_menu_item_format = STATIC_SYMBOL("CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qclose_box_x_offset = STATIC_SYMBOL("CLOSE-BOX-X-OFFSET",AB_package);
    Qclose_box_y_offset = STATIC_SYMBOL("CLOSE-BOX-Y-OFFSET",AB_package);
    Qfont_for_title_bars = STATIC_SYMBOL("FONT-FOR-TITLE-BARS",AB_package);
    Qtitle_bar_format = STATIC_SYMBOL("TITLE-BAR-FORMAT",AB_package);
    Qworkspace_title_bar_frame_style = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE",AB_package);
    Qworkspace_title_bar_frame_style_small = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE-SMALL",AB_package);
    Qworkspace_title_bar_frame_style_large = 
	    STATIC_SYMBOL("WORKSPACE-TITLE-BAR-FRAME-STYLE-LARGE",AB_package);
    Qg2_defstruct_structure_name_workstation_context_g2_struct = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qworkstation_context = STATIC_SYMBOL("WORKSTATION-CONTEXT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_g2_struct,
	    Qworkstation_context,Qab_name_of_unique_structure_type);
    mutate_global_property(Qworkstation_context,
	    Qg2_defstruct_structure_name_workstation_context_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_workstation_context == UNBOUND)
	The_type_description_of_workstation_context = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83ofy1n83ofy8n8k1l8n0000001l1n8y83-6Ny0ktk0k0");
    temp = The_type_description_of_workstation_context;
    The_type_description_of_workstation_context = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_workstation_context_g2_struct,
	    The_type_description_of_workstation_context,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qworkstation_context,
	    The_type_description_of_workstation_context,
	    Qtype_description_of_type);
    Qoutstanding_workstation_context_count = 
	    STATIC_SYMBOL("OUTSTANDING-WORKSTATION-CONTEXT-COUNT",AB_package);
    Qworkstation_context_structure_memory_usage = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83ofy8s83-xay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_workstation_context_count);
    push_optimized_constant(Qworkstation_context_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_workstation_contexts = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WORKSTATION-CONTEXTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_workstation_contexts,
	    Chain_of_available_workstation_contexts);
    record_system_variable(Qchain_of_available_workstation_contexts,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qworkstation_context_count = STATIC_SYMBOL("WORKSTATION-CONTEXT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_context_count,
	    Workstation_context_count);
    record_system_variable(Qworkstation_context_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_workstation_contexts_vector == UNBOUND)
	Chain_of_available_workstation_contexts_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qworkstation_context_structure_memory_usage,
	    STATIC_FUNCTION(workstation_context_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_workstation_context_count,
	    STATIC_FUNCTION(outstanding_workstation_context_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_workstation_context_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_workstation_context,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qworkstation_context,
	    reclaim_structure_for_workstation_context_1);
    if (Next_continuation_function_qm == UNBOUND)
	Next_continuation_function_qm = Nil;
    if (Next_old_style_return_function_qm == UNBOUND)
	Next_old_style_return_function_qm = Nil;
    if (Next_info == UNBOUND)
	Next_info = Nil;
    if (Next_info_reclaimer_qm == UNBOUND)
	Next_info_reclaimer_qm = Nil;
    Qavailable_workstation_contexts = 
	    STATIC_SYMBOL("AVAILABLE-WORKSTATION-CONTEXTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_workstation_contexts,
	    Available_workstation_contexts);
    record_system_variable(Qavailable_workstation_contexts,Qworkstation,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qunknown_is_selection_style = 
	    STATIC_SYMBOL("UNKNOWN-IS-SELECTION-STYLE",AB_package);
    Qspecific_structure_has_been_reclaimed = 
	    STATIC_SYMBOL("SPECIFIC-STRUCTURE-HAS-BEEN-RECLAIMED",AB_package);
    Qunwind_all_workstation_contexts = 
	    STATIC_SYMBOL("UNWIND-ALL-WORKSTATION-CONTEXTS",AB_package);
    SET_SYMBOL_FUNCTION(Qunwind_all_workstation_contexts,
	    STATIC_FUNCTION(unwind_all_workstation_contexts,NIL,FALSE,1,1));
    Qunwind_current_workstation_back_to_top_level = 
	    STATIC_SYMBOL("UNWIND-CURRENT-WORKSTATION-BACK-TO-TOP-LEVEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qunwind_current_workstation_back_to_top_level,
	    STATIC_FUNCTION(unwind_current_workstation_back_to_top_level,
	    NIL,FALSE,0,0));
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qworkstation_context_frame,
	    clean_up_workstation_context_for_workstation_context_frame_1);
    Qsetup_workstation_context = STATIC_SYMBOL("SETUP-WORKSTATION-CONTEXT",
	    AB_package);
    setup_workstation_context_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(setup_workstation_context_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qsetup_workstation_context,
	    Qworkstation_context_frame,
	    setup_workstation_context_for_workstation_context_frame_1);
    Qresume_workstation_context = 
	    STATIC_SYMBOL("RESUME-WORKSTATION-CONTEXT",AB_package);
    resume_workstation_context_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(resume_workstation_context_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qresume_workstation_context,
	    Qworkstation_context_frame,
	    resume_workstation_context_for_workstation_context_frame_1);
    Qsuspend_workstation_context = 
	    STATIC_SYMBOL("SUSPEND-WORKSTATION-CONTEXT",AB_package);
    suspend_workstation_context_for_workstation_context_frame_1 = 
	    STATIC_FUNCTION(suspend_workstation_context_for_workstation_context_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qsuspend_workstation_context,
	    Qworkstation_context_frame,
	    suspend_workstation_context_for_workstation_context_frame_1);
    Qg2_defstruct_structure_name_top_level_state_g2_struct = 
	    STATIC_SYMBOL("TOP-LEVEL-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtop_level_state = STATIC_SYMBOL("TOP-LEVEL-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_top_level_state_g2_struct,
	    Qtop_level_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtop_level_state,
	    Qg2_defstruct_structure_name_top_level_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_top_level_state == UNBOUND)
	The_type_description_of_top_level_state = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83nvy1o83nvy83-Sy8n8k1l83-Sy0000001l1m8x83-Syknk0k0");
    temp = The_type_description_of_top_level_state;
    The_type_description_of_top_level_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_top_level_state_g2_struct,
	    The_type_description_of_top_level_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtop_level_state,
	    The_type_description_of_top_level_state,Qtype_description_of_type);
    Qoutstanding_top_level_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-TOP-LEVEL-STATE-COUNT",AB_package);
    Qtop_level_state_structure_memory_usage = 
	    STATIC_SYMBOL("TOP-LEVEL-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_16 = STATIC_STRING("1q83nvy8s83-tay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_top_level_state_count);
    push_optimized_constant(Qtop_level_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_top_level_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TOP-LEVEL-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_top_level_states,
	    Chain_of_available_top_level_states);
    record_system_variable(Qchain_of_available_top_level_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtop_level_state_count = STATIC_SYMBOL("TOP-LEVEL-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtop_level_state_count,Top_level_state_count);
    record_system_variable(Qtop_level_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_top_level_states_vector == UNBOUND)
	Chain_of_available_top_level_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtop_level_state_structure_memory_usage,
	    STATIC_FUNCTION(top_level_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_top_level_state_count,
	    STATIC_FUNCTION(outstanding_top_level_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_top_level_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_top_level_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtop_level_state,
	    reclaim_structure_for_top_level_state_1);
    mutate_global_property(Qtop_level_state,Qtop_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qcurrent_system_dummy_workstation_qm = 
	    STATIC_SYMBOL("CURRENT-SYSTEM-DUMMY-WORKSTATION\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_system_dummy_workstation_qm,
	    Current_system_dummy_workstation_qm);
    record_system_variable(Qcurrent_system_dummy_workstation_qm,Qmice,Nil,
	    Qnil,Qnil,Qnil,Qnil);
}
