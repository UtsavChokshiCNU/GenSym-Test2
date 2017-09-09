/* gthrd.c
 * Input file:  gthread.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gthrd.h"


/* SLOWLY-LOOKUP-NEXT-METHOD */
Object g2int_slowly_lookup_next_method(name,path)
    Object name, path;
{
    Object type, method_qm, path_old_value, temp;

    x_note_fn_call(55,0);
    type = Nil;
    method_qm = Nil;
  next_loop:
    path_old_value = path;
    temp = FIRST(path_old_value);
    path = REST(path_old_value);
    type = temp;
    if ( !TRUEP(type))
	goto end_loop;
    method_qm = get(name,type,_);
    if (method_qm)
	return VALUES_2(method_qm,path);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_the_type_description_of_thread = UNBOUND;

Object G2int_chain_of_available_threads = UNBOUND;

Object G2int_thread_count = UNBOUND;

/* RECLAIM-THREAD-1 */
Object g2int_reclaim_thread_1(thread)
    Object thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(55,1);
    inline_note_reclaim_cons(thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = thread;
    g2int_reclaim_sockets(ISVREF(thread,(SI_Long)11L));
    SVREF(thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(thread,(SI_Long)12L));
    SVREF(thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_threads;
    SVREF(thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_threads = thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-THREAD */
Object g2int_reclaim_structure_for_thread(thread)
    Object thread;
{
    x_note_fn_call(55,2);
    return g2int_reclaim_thread_1(thread);
}

static Object Qg2_defstruct_structure_name_thread_g2_struct;  /* g2-defstruct-structure-name::thread-g2-struct */

/* MAKE-PERMANENT-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_thread_structure_internal()
{
    Object def_structure_thread_variable, thread_count_new_value;
    Object defstruct_g2_thread_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,3);
    def_structure_thread_variable = Nil;
    thread_count_new_value = FIXNUM_ADD1(G2int_thread_count);
    G2int_thread_count = thread_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_thread_variable = Nil;
	gensymed_symbol = (SI_Long)17L;
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
	defstruct_g2_thread_variable = the_array;
	SVREF(defstruct_g2_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_thread_g2_struct;
	def_structure_thread_variable = defstruct_g2_thread_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_thread_variable);
}

static Object Knew;                /* :new */

static Object Kallocated;          /* :allocated */

static Object Qg2int_null_thread_contour_wrapper;  /* null-thread-contour-wrapper */

/* MAKE-THREAD-1-1 */
Object g2int_make_thread_1_1(parent_of_thread,name_of_thread)
    Object parent_of_thread, name_of_thread;
{
    Object def_structure_thread_variable, svref_new_value;

    x_note_fn_call(55,4);
    def_structure_thread_variable = G2int_chain_of_available_threads;
    if (def_structure_thread_variable) {
	G2int_chain_of_available_threads = 
		ISVREF(def_structure_thread_variable,(SI_Long)0L);
	SVREF(def_structure_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_thread_g2_struct;
    }
    else
	def_structure_thread_variable = 
		g2int_make_permanent_thread_structure_internal();
    inline_note_allocate_cons(def_structure_thread_variable,Nil);
    SVREF(def_structure_thread_variable,FIX((SI_Long)5L)) = parent_of_thread;
    SVREF(def_structure_thread_variable,FIX((SI_Long)2L)) = name_of_thread;
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_thread_variable,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(def_structure_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_thread_variable,FIX((SI_Long)8L)) = Kallocated;
    SVREF(def_structure_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_thread_variable,(SI_Long)10L) = FIX((SI_Long)100L);
    SVREF(def_structure_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_thread_variable,FIX((SI_Long)14L)) = svref_new_value;
    SVREF(def_structure_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_thread_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_thread_variable);
}

Object G2int_the_last_thread_number = UNBOUND;

/* GENERATE-THREAD-NUMBER */
Object g2int_generate_thread_number()
{
    Object the_last_thread_number_new_value;

    x_note_fn_call(55,5);
    the_last_thread_number_new_value = add1(G2int_the_last_thread_number);
    G2int_the_last_thread_number = the_last_thread_number_new_value;
    return VALUES_1(G2int_the_last_thread_number);
}

/* RECLAIM-EVENT-TREE */
Object g2int_reclaim_event_tree(event_tree)
    Object event_tree;
{
    x_note_fn_call(55,6);
    return g2int_reclaim_plist_tree_of_resource_buffer(event_tree);
}

Object G2int_root_thread = UNBOUND;

static Object Qg2int_root;         /* root */

/* MAKE-ROOT-THREAD */
Object g2int_make_root_thread()
{
    x_note_fn_call(55,7);
    return g2int_make_thread_1_1(Nil,Qg2int_root);
}

Object G2int_current_thread = UNBOUND;

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

static Object Qg2int_thread_child_created;  /* thread-child-created */

/* THREAD-CHILD-CREATED */
Object g2int_thread_child_created(thread,child_thread)
    Object thread, child_thread;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(55,8);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_thread_child_created,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_3(method,next_path,thread,child_thread);
}

static Object Qg2int_thread_child_destroyed;  /* thread-child-destroyed */

/* THREAD-CHILD-DESTROYED */
Object g2int_thread_child_destroyed(thread,child_thread)
    Object thread, child_thread;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(55,9);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_thread_child_destroyed,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_3(method,next_path,thread,child_thread);
}

/* M-THREAD-CHILD-CREATED-THREAD-1 */
Object g2int_m_thread_child_created_thread_1(path,thread,child_thread)
    Object path, thread, child_thread;
{
    x_note_fn_call(55,10);
    return VALUES_1(Nil);
}

/* M-THREAD-CHILD-DESTROYED-THREAD-1 */
Object g2int_m_thread_child_destroyed_thread_1(path,thread,child_thread)
    Object path, thread, child_thread;
{
    x_note_fn_call(55,11);
    return VALUES_1(Nil);
}

static Object Qg2int_thread_initialize;  /* thread-initialize */

/* THREAD-INITIALIZE */
Object g2int_thread_initialize(thread)
    Object thread;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(55,12);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_thread_initialize,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_2(method,next_path,thread);
}

static Object Qg2int_thread_finalize;  /* thread-finalize */

/* THREAD-FINALIZE */
Object g2int_thread_finalize(thread)
    Object thread;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(55,13);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_thread_finalize,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_2(method,next_path,thread);
}

/* M-THREAD-INITIALIZE-THREAD-1 */
Object g2int_m_thread_initialize_thread_1(path,thread)
    Object path, thread;
{
    Object temp, gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(55,14);
    temp = G2int_current_thread;
    gensym_push_modify_macro_arg = thread;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(temp,(SI_Long)6L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    temp = G2int_current_thread;
    SVREF(thread,FIX((SI_Long)5L)) = temp;
    g2int_thread_child_created(G2int_current_thread,thread);
    return VALUES_1(thread);
}

static Object Kdead;               /* :dead */

static Object Kfinalized;          /* :finalized */

/* M-THREAD-FINALIZE-THREAD-1 */
Object g2int_m_thread_finalize_thread_1(path,thread)
    Object path, thread;
{
    Object child, temp, parent_of_thread, current_thread, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1;
    Declare_special(1);

    x_note_fn_call(55,15);
    child = Nil;
  next_loop:
    temp = ISVREF(thread,(SI_Long)6L);
    child = FIRST(temp);
    if ( !TRUEP(child))
	goto end_loop;
    g2int_thread_finalize(child);
    goto next_loop;
  end_loop:;
    g2int_cleanup_thread_if_necessary(thread);
    parent_of_thread = ISVREF(thread,(SI_Long)5L);
    current_thread = parent_of_thread;
    PUSH_SPECIAL(G2int_current_thread,current_thread,0);
      g2int_thread_child_destroyed(parent_of_thread,thread);
    POP_SPECIAL();
    svref_new_value = g2int_delete_gensym_element_1(thread,
	    ISVREF(parent_of_thread,(SI_Long)6L));
    SVREF(parent_of_thread,FIX((SI_Long)6L)) = svref_new_value;
    if (EQ(G2int_current_thread,thread))
	G2int_current_thread = parent_of_thread;
    SVREF(thread,FIX((SI_Long)7L)) = Kdead;
    SVREF(thread,FIX((SI_Long)8L)) = Kfinalized;
    g2int_clear_thread_pool(thread);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = thread;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* DO-PRINT-THREAD */
Object g2int_do_print_thread(thread)
    Object thread;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(55,16);
    gensymed_symbol = ISVREF(thread,(SI_Long)0L);
    temp = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)1L);
    return format((SI_Long)10L,T,"~a ~a#~d [~a, ~a] [~a ~a] (~s)",temp,
	    ISVREF(thread,(SI_Long)2L),ISVREF(thread,(SI_Long)1L),
	    ISVREF(thread,(SI_Long)7L),ISVREF(thread,(SI_Long)16L),
	    ISVREF(thread,(SI_Long)11L),ISVREF(thread,(SI_Long)12L),
	    ISVREF(thread,(SI_Long)15L));
}

/* PS-1 */
Object g2int_ps_1(depth,thread)
    Object depth, thread;
{
    Object child, ab_loop_list_;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(55,17);
    terpri(_);
    ab_loop_repeat_ = IFIX(depth);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    write_char(CHR(' '),_);
    goto next_loop;
  end_loop:;
    g2int_do_print_thread(thread);
    child = Nil;
    ab_loop_list_ = ISVREF(thread,(SI_Long)6L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_ps_1(add1(depth),child);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* PS */
Object g2int_ps()
{
    x_note_fn_call(55,18);
    g2int_ps_1(FIX((SI_Long)0L),G2int_root_thread);
    return terpri(_);
}

/* CLEAR-THREAD-POOL */
Object g2int_clear_thread_pool(thread)
    Object thread;
{
    Object string_1, ab_loop_list_;

    x_note_fn_call(55,19);
    string_1 = Nil;
    ab_loop_list_ = ISVREF(thread,(SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_gensym_string(string_1);
    goto next_loop;
  end_loop:;
    g2int_reclaim_gensym_list_1(ISVREF(thread,(SI_Long)3L));
    SVREF(thread,FIX((SI_Long)3L)) = Nil;
    return g2int_reclaim_gensym_tree_1(ISVREF(thread,(SI_Long)4L));
}

/* COPY-FOR-THREAD-TREE */
Object g2int_copy_for_thread_tree(tree)
    Object tree;
{
    Object x, svref_arg_1, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(55,20);
    if (STRINGP(tree)) {
	x = g2int_copy_gensym_string(tree);
	svref_arg_1 = G2int_current_thread;
	gensym_push_modify_macro_arg = x;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(svref_arg_1,(SI_Long)3L);
	svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
	return VALUES_1(x);
    }
    else
	return VALUES_1(Nil);
}

/* THREAD-FORMAT */
Object g2int_thread_format varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, x;
    Object svref_arg_1, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(55,21);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    x = g2int_tformat_gensym_string(10,control_string,arg1,arg2,arg3,arg4,
	    arg5,arg6,arg7,arg8,arg9);
    svref_arg_1 = G2int_current_thread;
    gensym_push_modify_macro_arg = x;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)3L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(x);
}

/* THREAD-STRING-SUBSTRING */
Object g2int_thread_string_substring(text,start_qm,end_qm)
    Object text, start_qm, end_qm;
{
    Object x, svref_arg_1, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(55,22);
    x = g2int_gensym_string_substring(text,start_qm,end_qm);
    svref_arg_1 = G2int_current_thread;
    gensym_push_modify_macro_arg = x;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)3L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(x);
}

static Object Kinitialize;         /* :initialize */

/* PROLOG-THREAD-FUNCTION */
Object g2int_prolog_thread_function(return_continuation,microtask_function,
	    frame_size)
    Object return_continuation, microtask_function, frame_size;
{
    Object frame, temp;

    x_note_fn_call(55,23);
    frame = g2int_allocate_managed_simple_vector(frame_size);
    temp = ISVREF(G2int_current_thread,(SI_Long)13L);
    SVREF(frame,FIX((SI_Long)0L)) = temp;
    temp = ISVREF(G2int_current_thread,(SI_Long)15L);
    SVREF(frame,FIX((SI_Long)1L)) = temp;
    SVREF(frame,FIX((SI_Long)2L)) = return_continuation;
    temp = G2int_current_thread;
    SVREF(temp,FIX((SI_Long)13L)) = frame;
    temp = G2int_current_thread;
    SVREF(temp,FIX((SI_Long)15L)) = microtask_function;
    temp = G2int_current_thread;
    SVREF(temp,FIX((SI_Long)16L)) = Kinitialize;
    return VALUES_1(frame);
}

Object G2int_trace_quantum = UNBOUND;

static Object Kreturn;             /* :return */

/* GIVE-THREAD-QUANTUM */
Object g2int_give_thread_quantum()
{
    x_note_fn_call(55,24);
    if (G2int_trace_quantum)
	format((SI_Long)5L,T,"~%~S:~D ~S",ISVREF(G2int_current_thread,
		(SI_Long)2L),ISVREF(G2int_current_thread,(SI_Long)1L),
		ISVREF(G2int_current_thread,(SI_Long)16L));
    FUNCALL_0(ISVREF(G2int_current_thread,(SI_Long)14L));
    if (EQ(Kreturn,ISVREF(G2int_current_thread,(SI_Long)16L))) {
	g2int_cleanup_and_unwind_one_thread_frame_with_needed_contour(G2int_current_thread);
	if (ISVREF(G2int_current_thread,(SI_Long)15L))
	    return g2int_give_thread_quantum();
	else
	    return g2int_thread_finalize(G2int_current_thread);
    }
    else
	return VALUES_1(Nil);
}

/* NULL-THREAD-CONTOUR-WRAPPER */
Object g2int_null_thread_contour_wrapper()
{
    x_note_fn_call(55,25);
    return FUNCALL_0(ISVREF(G2int_current_thread,(SI_Long)15L));
}

static Object Kcleanup;            /* :cleanup */

/* CLEANUP-AND-UNWIND-ONE-THREAD-FRAME-WITH-NEEDED-CONTOUR */
Object g2int_cleanup_and_unwind_one_thread_frame_with_needed_contour(thread)
    Object thread;
{
    Object current_thread, svref_arg_1, old_frame, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,26);
    current_thread = thread;
    PUSH_SPECIAL(G2int_current_thread,current_thread,0);
      svref_arg_1 = G2int_current_thread;
      SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kcleanup;
      FUNCALL_0(ISVREF(G2int_current_thread,(SI_Long)14L));
      old_frame = ISVREF(G2int_current_thread,(SI_Long)13L);
      svref_arg_1 = G2int_current_thread;
      svref_new_value = ISVREF(old_frame,(SI_Long)0L);
      SVREF(svref_arg_1,FIX((SI_Long)13L)) = svref_new_value;
      svref_arg_1 = G2int_current_thread;
      svref_new_value = ISVREF(old_frame,(SI_Long)1L);
      SVREF(svref_arg_1,FIX((SI_Long)15L)) = svref_new_value;
      svref_arg_1 = G2int_current_thread;
      svref_new_value = ISVREF(old_frame,(SI_Long)2L);
      SVREF(svref_arg_1,FIX((SI_Long)16L)) = svref_new_value;
      result = g2int_reclaim_managed_simple_vector(old_frame);
    POP_SPECIAL();
    return result;
}

/* CLEANUP-THREAD-IF-NECESSARY */
Object g2int_cleanup_thread_if_necessary(thread)
    Object thread;
{
    x_note_fn_call(55,27);
    if ( !TRUEP(ISVREF(thread,(SI_Long)9L))) {
	SVREF(thread,FIX((SI_Long)9L)) = T;
      next_loop:
	if ( !TRUEP(ISVREF(thread,(SI_Long)13L)))
	    goto end_loop;
	g2int_cleanup_and_unwind_one_thread_frame_with_needed_contour(thread);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Kthread_exiting;     /* :thread-exiting */

/* THREAD-EXIT-1 */
Object g2int_thread_exit_1()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(55,28);
    svref_arg_1 = G2int_current_thread;
    svref_new_value = ISVREF(G2int_current_thread,(SI_Long)7L);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    svref_arg_1 = G2int_current_thread;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = Kthread_exiting;
    return g2int_thread_finalize(G2int_current_thread);
}

static Object list_constant;       /* # */

static Object Kmurdered;           /* :murdered */

/* THREAD-KILL */
Object g2int_thread_kill(thread)
    Object thread;
{
    x_note_fn_call(55,29);
    if ( !(EQ(ISVREF(thread,(SI_Long)7L),Kdead) || 
	    g2int_memq_function(ISVREF(thread,(SI_Long)8L),list_constant)))
	SVREF(thread,FIX((SI_Long)7L)) = Kmurdered;
    if ( !EQ(ISVREF(thread,(SI_Long)8L),Kfinalized))
	return g2int_thread_finalize(thread);
    else
	return VALUES_1(Nil);
}

static Object Knot_runnable;       /* :not-runnable */

static Object Ksuspended;          /* :suspended */

/* THREAD-SUSPEND */
Object g2int_thread_suspend(thread)
    Object thread;
{
    x_note_fn_call(55,30);
    SVREF(thread,FIX((SI_Long)7L)) = Knot_runnable;
    return VALUES_1(SVREF(thread,FIX((SI_Long)8L)) = Ksuspended);
}

static Object Krunnable;           /* :runnable */

static Object Kresumed;            /* :resumed */

/* THREAD-RESUME */
Object g2int_thread_resume(thread)
    Object thread;
{
    x_note_fn_call(55,31);
    SVREF(thread,FIX((SI_Long)7L)) = Krunnable;
    return VALUES_1(SVREF(thread,FIX((SI_Long)8L)) = Kresumed);
}

/* THREAD-RESUME-IF-NECESSARY */
Object g2int_thread_resume_if_necessary(thread)
    Object thread;
{
    x_note_fn_call(55,32);
    if (EQ(ISVREF(thread,(SI_Long)8L),Ksuspended) && EQ(ISVREF(thread,
	    (SI_Long)7L),Knot_runnable))
	return g2int_thread_resume(thread);
    else
	return VALUES_1(Nil);
}

Object G2int_thread_return_value_pad = UNBOUND;

/* THREAD-BACKTRACE */
Object g2int_thread_backtrace()
{
    Object frame;

    x_note_fn_call(55,33);
    format((SI_Long)4L,T,"~%Current thread: ~S ~S",G2int_current_thread,
	    ISVREF(G2int_current_thread,(SI_Long)7L));
    format((SI_Long)4L,T,"~%~S in ~S",ISVREF(G2int_current_thread,
	    (SI_Long)16L),ISVREF(G2int_current_thread,(SI_Long)15L));
    frame = ISVREF(G2int_current_thread,(SI_Long)13L);
  next_loop:
    if ( !TRUEP(frame))
	goto end_loop;
    if ( !TRUEP(ISVREF(frame,(SI_Long)2L)))
	format((SI_Long)3L,T,"~% ~S - Root -",frame);
    else
	format((SI_Long)5L,T,"~%~S ~S in ~S",frame,ISVREF(frame,
		(SI_Long)2L),ISVREF(frame,(SI_Long)1L));
    frame = ISVREF(frame,(SI_Long)0L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* THREAD-ENQUEUE-EVENT */
Object g2int_thread_enqueue_event(thread,event)
    Object thread, event;
{
    Object event_queue, listed_event, cdr_arg;

    x_note_fn_call(55,34);
    event_queue = ISVREF(thread,(SI_Long)12L);
    listed_event = g2int_gensym_cons_1(event,Nil);
    if (event_queue) {
	cdr_arg = last(event_queue,_);
	M_CDR(cdr_arg) = listed_event;
    }
    else
	SVREF(thread,FIX((SI_Long)12L)) = listed_event;
    return g2int_thread_resume_if_necessary(thread);
}

static Object Qg2int_gensym;       /* gensym */

/* THREAD-DEQUEUE-EVENT */
Object g2int_thread_dequeue_event(thread)
    Object thread;
{
    Object gensym_pop_store, cons_1, next_cons, cdr_new_value, result_1;

    x_note_fn_call(55,35);
    gensym_pop_store = Nil;
    cons_1 = ISVREF(thread,(SI_Long)12L);
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    SVREF(thread,FIX((SI_Long)12L)) = next_cons;
    result_1 = gensym_pop_store;
    return VALUES_1(result_1);
}

Object G2int_sum_of_running_threads = UNBOUND;

Object G2int_number_of_running_threads = UNBOUND;

/* FEED-RUNNING-THREADS */
Object g2int_feed_running_threads()
{
    x_note_fn_call(55,36);
    G2int_sum_of_running_threads = FIX((SI_Long)0L);
    g2int_feed_thread_tree(G2int_root_thread);
    G2int_number_of_running_threads = G2int_sum_of_running_threads;
    return VALUES_1(Nil);
}

/* FEED-THREAD-TREE */
Object g2int_feed_thread_tree(p)
    Object p;
{
    Object child, ab_loop_list_, sum_of_running_threads_new_value;
    Object current_thread;
    Declare_special(1);

    x_note_fn_call(55,37);
    child = Nil;
    ab_loop_list_ = ISVREF(p,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_feed_thread_tree(child);
    goto next_loop;
  end_loop:;
    if (EQ(Krunnable,ISVREF(p,(SI_Long)7L))) {
	sum_of_running_threads_new_value = add1(G2int_sum_of_running_threads);
	G2int_sum_of_running_threads = sum_of_running_threads_new_value;
	current_thread = p;
	PUSH_SPECIAL(G2int_current_thread,current_thread,0);
	  g2int_give_thread_quantum();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* END-IO-WAIT */
Object g2int_end_io_wait()
{
    x_note_fn_call(55,38);
    return g2int_end_io_wait_1(G2int_root_thread);
}

static Object Kio_wait;            /* :io-wait */

static Object Kend_io_wait;        /* :end-io-wait */

/* END-IO-WAIT-1 */
Object g2int_end_io_wait_1(p)
    Object p;
{
    Object child, ab_loop_list_;

    x_note_fn_call(55,39);
    child = Nil;
    ab_loop_list_ = ISVREF(p,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_end_io_wait_1(child);
    if (EQ(ISVREF(child,(SI_Long)8L),Kio_wait)) {
	SVREF(child,FIX((SI_Long)7L)) = Krunnable;
	SVREF(child,FIX((SI_Long)8L)) = Kend_io_wait;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SHUTDOWN-THREAD-TREE */
Object g2int_shutdown_thread_tree()
{
    Object child, temp;

    x_note_fn_call(55,40);
    child = Nil;
  next_loop:
    temp = ISVREF(G2int_root_thread,(SI_Long)6L);
    child = FIRST(temp);
    if ( !TRUEP(child))
	goto end_loop;
    g2int_shutdown_thread_tree_1(child);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SHUTDOWN-THREAD-TREE-1 */
Object g2int_shutdown_thread_tree_1(thread)
    Object thread;
{
    Object child, temp;

    x_note_fn_call(55,41);
    child = Nil;
  next_loop:
    temp = ISVREF(thread,(SI_Long)6L);
    child = FIRST(temp);
    if ( !TRUEP(child))
	goto end_loop;
    g2int_shutdown_thread_tree_1(child);
    goto next_loop;
  end_loop:;
    return g2int_thread_kill(thread);
}

Object G2int_the_type_description_of_weblink_socket = UNBOUND;

Object G2int_chain_of_available_weblink_sockets = UNBOUND;

Object G2int_weblink_socket_count = UNBOUND;

/* RECLAIM-WEBLINK-SOCKET-1 */
Object g2int_reclaim_weblink_socket_1(weblink_socket)
    Object weblink_socket;
{
    Object svref_new_value;

    x_note_fn_call(55,42);
    inline_note_reclaim_cons(weblink_socket,Nil);
    svref_new_value = G2int_chain_of_available_weblink_sockets;
    SVREF(weblink_socket,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_weblink_sockets = weblink_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-WEBLINK-SOCKET */
Object g2int_reclaim_structure_for_weblink_socket(weblink_socket)
    Object weblink_socket;
{
    x_note_fn_call(55,43);
    return g2int_reclaim_weblink_socket_1(weblink_socket);
}

static Object Qg2_defstruct_structure_name_weblink_socket_g2_struct;  /* g2-defstruct-structure-name::weblink-socket-g2-struct */

/* MAKE-PERMANENT-WEBLINK-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_weblink_socket_structure_internal()
{
    Object def_structure_weblink_socket_variable;
    Object weblink_socket_count_new_value;
    Object defstruct_g2_weblink_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,44);
    def_structure_weblink_socket_variable = Nil;
    weblink_socket_count_new_value = FIXNUM_ADD1(G2int_weblink_socket_count);
    G2int_weblink_socket_count = weblink_socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_weblink_socket_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_weblink_socket_variable = the_array;
	SVREF(defstruct_g2_weblink_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_weblink_socket_g2_struct;
	def_structure_weblink_socket_variable = 
		defstruct_g2_weblink_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_weblink_socket_variable);
}

static Object Kborn;               /* :born */

/* MAKE-WEBLINK-SOCKET-1 */
Object g2int_make_weblink_socket_1()
{
    Object def_structure_weblink_socket_variable, svref_new_value;

    x_note_fn_call(55,45);
    def_structure_weblink_socket_variable = 
	    G2int_chain_of_available_weblink_sockets;
    if (def_structure_weblink_socket_variable) {
	G2int_chain_of_available_weblink_sockets = 
		ISVREF(def_structure_weblink_socket_variable,(SI_Long)0L);
	SVREF(def_structure_weblink_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_weblink_socket_g2_struct;
    }
    else
	def_structure_weblink_socket_variable = 
		g2int_make_permanent_weblink_socket_structure_internal();
    inline_note_allocate_cons(def_structure_weblink_socket_variable,Nil);
    svref_new_value = G2int_current_thread;
    SVREF(def_structure_weblink_socket_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_weblink_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_weblink_socket_variable,FIX((SI_Long)3L)) = Kborn;
    ISVREF(def_structure_weblink_socket_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_weblink_socket_variable);
}

/* RECLAIM-SOCKETS */
Object g2int_reclaim_sockets(list_of_sockets)
    Object list_of_sockets;
{
    Object s, gensym_pop_store, cons_1, next_cons, cdr_new_value;
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,46);
    s = Nil;
  next_loop:
    gensym_pop_store = Nil;
    cons_1 = list_of_sockets;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	cdr_new_value = G2int_available_gensym_conses;
	M_CDR(cons_1) = cdr_new_value;
	G2int_available_gensym_conses = cons_1;
    }
    else
	next_cons = Nil;
    list_of_sockets = next_cons;
    s = gensym_pop_store;
    if ( !TRUEP(s))
	goto end_loop;
    gensymed_symbol = ISVREF(s,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = s;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_all_sockets = UNBOUND;

static Object Ksocket_issue;       /* :socket-issue */

/* NOTE-ISSUE-WITH-SOCKET */
Object g2int_note_issue_with_socket(socket_1,issue)
    Object socket_1, issue;
{
    Object svref_new_value;

    x_note_fn_call(55,47);
    if ( !TRUEP(ISVREF(socket_1,(SI_Long)3L))) {
	if (EQ(FIX((SI_Long)-1L),issue) && ISVREF(socket_1,(SI_Long)2L)) {
	    g2int_socket_poll_status(socket_1);
	    if ( !TRUEP(ISVREF(socket_1,(SI_Long)3L)))
		ISVREF(socket_1,(SI_Long)3L) = FIX((SI_Long)-1L);
	}
	else if (EQ(G2int_errno_would_block,issue) || EQ(G2int_errno_again,
		issue)) {
	    svref_new_value = FIXNUM_ADD1(ISVREF(socket_1,(SI_Long)4L));
	    SVREF(socket_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	else
	    SVREF(socket_1,FIX((SI_Long)3L)) = issue;
	if (ISVREF(socket_1,(SI_Long)3L))
	    return g2int_thread_enqueue_event(G2int_current_thread,
		    Ksocket_issue);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PEER-NAME-OF-SOCKET */
Object g2int_peer_name_of_socket(socket_1)
    Object socket_1;
{
    x_note_fn_call(55,48);
    g2int_c_get_peer_hostname(ISVREF(socket_1,(SI_Long)2L),
	    G2int_current_foreign_string_pad,FIX((SI_Long)10000L));
    return g2int_make_text_string_from_c_string_in_foreign_string_pad();
}

/* PEER-ADDRESS-STRING-OF-SOCKET */
Object g2int_peer_address_string_of_socket(socket_1)
    Object socket_1;
{
    x_note_fn_call(55,49);
    g2int_c_get_peer_address_string(ISVREF(socket_1,(SI_Long)2L),
	    G2int_current_foreign_string_pad,FIX((SI_Long)10000L));
    return g2int_make_text_string_from_c_string_in_foreign_string_pad();
}

/* SOCKET-POLL-STATUS */
Object g2int_socket_poll_status(socket_1)
    Object socket_1;
{
    int result_1;

    x_note_fn_call(55,50);
    result_1 = gw_socket_poll_status(IFIX(ISVREF(socket_1,(SI_Long)2L)));
    if ((SI_Long)0L == result_1)
	return VALUES_1(Nil);
    else {
	g2int_note_issue_with_socket(socket_1,INT_TO_INTEGER(result_1));
	return VALUES_1(INT_TO_INTEGER(result_1));
    }
}

/* SOCKET-INSTALL */
Object g2int_socket_install(socket_1,socket_number)
    Object socket_1, socket_number;
{
    Object svref_arg_1, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(55,51);
    SVREF(socket_1,FIX((SI_Long)3L)) = Nil;
    SVREF(socket_1,FIX((SI_Long)2L)) = socket_number;
    gsi_watch_fd(IFIX(ISVREF(socket_1,(SI_Long)2L)));
    g2pvt_tcpip_set_nodelay(IFIX(ISVREF(socket_1,(SI_Long)2L)));
    svref_arg_1 = G2int_current_thread;
    gensym_push_modify_macro_arg = socket_1;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(svref_arg_1,(SI_Long)11L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = svref_new_value;
    G2int_all_sockets = g2int_gensym_cons_1(socket_1,G2int_all_sockets);
    return VALUES_1(socket_1);
}

static Object Kuninstalled;        /* :uninstalled */

/* SOCKET-DEINSTALL */
Object g2int_socket_deinstall(socket_1)
    Object socket_1;
{
    Object thread, svref_new_value;

    x_note_fn_call(55,52);
    thread = ISVREF(socket_1,(SI_Long)1L);
    svref_new_value = g2int_delete_gensym_element_1(socket_1,ISVREF(thread,
	    (SI_Long)11L));
    SVREF(thread,FIX((SI_Long)11L)) = svref_new_value;
    G2int_all_sockets = g2int_delete_gensym_element_1(socket_1,
	    G2int_all_sockets);
    gsi_unwatch_fd(IFIX(ISVREF(socket_1,(SI_Long)2L)));
    SVREF(socket_1,FIX((SI_Long)3L)) = Kuninstalled;
    return VALUES_1(socket_1);
}

static Object Qg2int_socket_close_it;  /* socket-close-it */

/* SOCKET-CLOSE-IT */
Object g2int_socket_close_it(weblink_socket)
    Object weblink_socket;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(55,53);
    gensymed_symbol = ISVREF(weblink_socket,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_socket_close_it,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_2(method,next_path,weblink_socket);
}

/* M-SOCKET-CLOSE-IT-WEBLINK-SOCKET-1 */
Object g2int_m_socket_close_it_weblink_socket_1(path,weblink_socket)
    Object path, weblink_socket;
{
    int errcode;

    x_note_fn_call(55,54);
    g2int_socket_deinstall(weblink_socket);
    errcode = g2pvt_tcpip_close(IFIX(ISVREF(weblink_socket,(SI_Long)2L)));
    if ( !((SI_Long)0L == errcode))
	return g2int_note_issue_with_socket(weblink_socket,
		INT_TO_INTEGER(errcode));
    else
	return VALUES_1(Nil);
}

/* SOCKET-WRITE-REGION */
Object g2int_socket_write_region(socket_1,from_mark,to_mark)
    Object socket_1, from_mark, to_mark;
{
    Object from_pos, to_pos, text_of_chunk_qm, number_of_socket;
    Object chunk_left_mark, chunk_right_mark, chunk_left, chunk_right;
    Object chunk_size, c_safe_text;
    SI_Long temp;
    int result_1, errno_1;

    x_note_fn_call(55,55);
    from_pos = g2int_position_of_mark(from_mark);
    to_pos = g2int_position_of_mark(to_mark);
    text_of_chunk_qm = Nil;
    number_of_socket = ISVREF(socket_1,(SI_Long)2L);
    chunk_left_mark = g2int_mark_copy(from_mark);
    chunk_right_mark = g2int_mark_copy(chunk_left_mark);
    chunk_left = from_pos;
    chunk_right = Nil;
    chunk_size = Nil;
  next_loop:
    temp = IFIX(chunk_left) + (SI_Long)5000L;
    chunk_right = FIX(MIN(IFIX(to_pos),temp));
    chunk_size = FIXNUM_MINUS(chunk_right,chunk_left);
    if ( !((SI_Long)0L < IFIX(chunk_size)))
	goto end_loop;
    g2int_mark_move(chunk_right_mark,chunk_size);
    if (text_of_chunk_qm)
	g2int_reclaim_gensym_string(text_of_chunk_qm);
    text_of_chunk_qm = g2int_copy_text_between_marks(chunk_left_mark,
	    chunk_right_mark);
    g2int_socket_poll_status(socket_1);
    if (EQ(G2int_errno_would_block,ISVREF(socket_1,(SI_Long)3L))) {
	SVREF(socket_1,FIX((SI_Long)3L)) = Nil;
	goto end;
    }
    if (ISVREF(socket_1,(SI_Long)3L))
	goto end;
    c_safe_text = g2int_make_text_safe_for_c(text_of_chunk_qm);
    result_1 = gw_socket_write(INTEGER_TO_INT(number_of_socket),
	    ISTRING(c_safe_text),(SI_Long)0L,INTEGER_TO_INT(chunk_size));
    if ((SI_Long)0L <= result_1)
	g2int_mark_move(from_mark,INT_TO_INTEGER(result_1));
    if (result_1 < (SI_Long)0L) {
	errno_1 = gw_fetch_errno();
	if (IFIX(G2int_errno_would_block) == errno_1 || 
		IFIX(G2int_errno_again) == errno_1)
	    goto end;
	g2int_note_issue_with_socket(socket_1,INT_TO_INTEGER(errno_1));
    }
    else {
	g2int_socket_poll_status(socket_1);
	if (ISVREF(socket_1,(SI_Long)3L))
	    goto end;
    }
    if ( !(result_1 == IFIX(chunk_size)))
	goto end;
    g2int_mark_set(chunk_left_mark,chunk_right_mark);
    chunk_left = chunk_right;
    goto next_loop;
  end_loop:
  end:;
    g2int_mark_kill(chunk_right_mark);
    g2int_mark_kill(chunk_left_mark);
    if (text_of_chunk_qm)
	return g2int_reclaim_gensym_string(text_of_chunk_qm);
    else
	return VALUES_1(Nil);
}

Object G2int_lisp_process_cleanups = UNBOUND;

void gthread_INIT()
{
    Object temp, reclaim_structure_for_thread;
    Object reclaim_structure_for_weblink_socket;
    Object Qg2int_m_socket_close_it_weblink_socket_1, Qg2int_weblink_socket;
    Object AB_package, Qg2int_gthread, Qg2int_all_sockets;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_weblink_socket_count;
    Object Qg2int_chain_of_available_weblink_sockets;
    Object Qg2int_type_description_of_type, string_constant_1;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2int_m_thread_finalize_thread_1, Qg2int_thread;
    Object Qg2int_m_thread_initialize_thread_1;
    Object Qg2int_m_thread_child_destroyed_thread_1;
    Object Qg2int_m_thread_child_created_thread_1, list_constant_2;
    Object Qg2int_current_thread, Qg2int_root_thread, Ksymbol_value;
    Object Qg2int_make_root_thread, list_constant_1, Kfuncall;
    Object Qg2int_thread_count, Qg2int_chain_of_available_threads;
    Object string_constant;

    x_note_fn_call(55,56);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_thread_g2_struct = 
	    STATIC_SYMBOL("THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_thread = STATIC_SYMBOL("THREAD",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_thread_g2_struct,
	    Qg2int_thread,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_thread,
	    Qg2_defstruct_structure_name_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_thread == UNBOUND)
	G2int_the_type_description_of_thread = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8l83Cy1n83Cy8m8k1l8m0000001l1n8n83=Sy1m83=qy83=Xyk3Dyk0k0");
    temp = G2int_the_type_description_of_thread;
    G2int_the_type_description_of_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_thread_g2_struct,
	    G2int_the_type_description_of_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_thread,
	    G2int_the_type_description_of_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_threads,
	    G2int_chain_of_available_threads);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_thread_count = STATIC_SYMBOL("THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_thread_count,G2int_thread_count);
    g2int_record_system_variable(Qg2int_thread_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_thread,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_thread,reclaim_structure_for_thread);
    Knew = STATIC_SYMBOL("NEW",Pkeyword);
    Kallocated = STATIC_SYMBOL("ALLOCATED",Pkeyword);
    Qg2int_null_thread_contour_wrapper = 
	    STATIC_SYMBOL("NULL-THREAD-CONTOUR-WRAPPER",AB_package);
    if (G2int_the_last_thread_number == UNBOUND)
	G2int_the_last_thread_number = FIX((SI_Long)1000L);
    Qg2int_root_thread = STATIC_SYMBOL("ROOT-THREAD",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_root_thread,G2int_root_thread);
    Qg2int_gthread = STATIC_SYMBOL("GTHREAD",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_make_root_thread = STATIC_SYMBOL("MAKE-ROOT-THREAD",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_make_root_thread);
    g2int_record_system_variable(Qg2int_root_thread,Qg2int_gthread,
	    list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_root = STATIC_SYMBOL("ROOT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_root_thread,
	    STATIC_FUNCTION(g2int_make_root_thread,NIL,FALSE,0,0));
    Qg2int_current_thread = STATIC_SYMBOL("CURRENT-THREAD",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_thread,G2int_current_thread);
    Ksymbol_value = STATIC_SYMBOL("SYMBOL-VALUE",Pkeyword);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Ksymbol_value,
	    Qg2int_root_thread);
    g2int_record_system_variable(Qg2int_current_thread,Qg2int_gthread,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qg2int_thread_child_created = STATIC_SYMBOL("THREAD-CHILD-CREATED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_thread_child_created,
	    STATIC_FUNCTION(g2int_thread_child_created,NIL,FALSE,2,2));
    Qg2int_thread_child_destroyed = STATIC_SYMBOL("THREAD-CHILD-DESTROYED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_thread_child_destroyed,
	    STATIC_FUNCTION(g2int_thread_child_destroyed,NIL,FALSE,2,2));
    Qg2int_m_thread_child_created_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-CHILD-CREATED-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_child_created_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_child_created_thread_1,NIL,
	    FALSE,3,3));
    set_get(Qg2int_thread_child_created,Qg2int_thread,
	    Qg2int_m_thread_child_created_thread_1);
    Qg2int_m_thread_child_destroyed_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-CHILD-DESTROYED-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_child_destroyed_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_child_destroyed_thread_1,NIL,
	    FALSE,3,3));
    set_get(Qg2int_thread_child_destroyed,Qg2int_thread,
	    Qg2int_m_thread_child_destroyed_thread_1);
    Qg2int_thread_initialize = STATIC_SYMBOL("THREAD-INITIALIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_thread_initialize,
	    STATIC_FUNCTION(g2int_thread_initialize,NIL,FALSE,1,1));
    Qg2int_thread_finalize = STATIC_SYMBOL("THREAD-FINALIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_thread_finalize,
	    STATIC_FUNCTION(g2int_thread_finalize,NIL,FALSE,1,1));
    Qg2int_m_thread_initialize_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-INITIALIZE-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_initialize_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_initialize_thread_1,NIL,FALSE,2,2));
    set_get(Qg2int_thread_initialize,Qg2int_thread,
	    Qg2int_m_thread_initialize_thread_1);
    Kdead = STATIC_SYMBOL("DEAD",Pkeyword);
    Kfinalized = STATIC_SYMBOL("FINALIZED",Pkeyword);
    Qg2int_m_thread_finalize_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-FINALIZE-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_finalize_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_finalize_thread_1,NIL,FALSE,2,2));
    set_get(Qg2int_thread_finalize,Qg2int_thread,
	    Qg2int_m_thread_finalize_thread_1);
    Kinitialize = STATIC_SYMBOL("INITIALIZE",Pkeyword);
    if (G2int_trace_quantum == UNBOUND)
	G2int_trace_quantum = Nil;
    Kreturn = STATIC_SYMBOL("RETURN",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper,
	    STATIC_FUNCTION(g2int_null_thread_contour_wrapper,NIL,FALSE,0,0));
    Kcleanup = STATIC_SYMBOL("CLEANUP",Pkeyword);
    Kthread_exiting = STATIC_SYMBOL("THREAD-EXITING",Pkeyword);
    list_constant = STATIC_CONS(Kthread_exiting,Qnil);
    Kmurdered = STATIC_SYMBOL("MURDERED",Pkeyword);
    Knot_runnable = STATIC_SYMBOL("NOT-RUNNABLE",Pkeyword);
    Ksuspended = STATIC_SYMBOL("SUSPENDED",Pkeyword);
    Krunnable = STATIC_SYMBOL("RUNNABLE",Pkeyword);
    Kresumed = STATIC_SYMBOL("RESUMED",Pkeyword);
    if (G2int_thread_return_value_pad == UNBOUND)
	G2int_thread_return_value_pad = make_array(1,FIX((SI_Long)10L));
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    if (G2int_sum_of_running_threads == UNBOUND)
	G2int_sum_of_running_threads = FIX((SI_Long)0L);
    if (G2int_number_of_running_threads == UNBOUND)
	G2int_number_of_running_threads = FIX((SI_Long)0L);
    Kio_wait = STATIC_SYMBOL("IO-WAIT",Pkeyword);
    Kend_io_wait = STATIC_SYMBOL("END-IO-WAIT",Pkeyword);
    Qg2_defstruct_structure_name_weblink_socket_g2_struct = 
	    STATIC_SYMBOL("WEBLINK-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_weblink_socket = STATIC_SYMBOL("WEBLINK-SOCKET",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_weblink_socket_g2_struct,
	    Qg2int_weblink_socket,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_weblink_socket,
	    Qg2_defstruct_structure_name_weblink_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_weblink_socket == UNBOUND)
	G2int_the_type_description_of_weblink_socket = Nil;
    string_constant_1 = STATIC_STRING("43Dy8l83Ly1n83Ly8m8k1l8m0000000kpk0k0");
    temp = G2int_the_type_description_of_weblink_socket;
    G2int_the_type_description_of_weblink_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_1));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_weblink_socket_g2_struct,
	    G2int_the_type_description_of_weblink_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_weblink_socket,
	    G2int_the_type_description_of_weblink_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_weblink_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-WEBLINK-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_weblink_sockets,
	    G2int_chain_of_available_weblink_sockets);
    g2int_record_system_variable(Qg2int_chain_of_available_weblink_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_weblink_socket_count = STATIC_SYMBOL("WEBLINK-SOCKET-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_weblink_socket_count,
	    G2int_weblink_socket_count);
    g2int_record_system_variable(Qg2int_weblink_socket_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_weblink_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_weblink_socket,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_weblink_socket,reclaim_structure_for_weblink_socket);
    Kborn = STATIC_SYMBOL("BORN",Pkeyword);
    Qg2int_all_sockets = STATIC_SYMBOL("ALL-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_all_sockets,G2int_all_sockets);
    g2int_record_system_variable(Qg2int_all_sockets,Qg2int_gthread,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Ksocket_issue = STATIC_SYMBOL("SOCKET-ISSUE",Pkeyword);
    Kuninstalled = STATIC_SYMBOL("UNINSTALLED",Pkeyword);
    Qg2int_socket_close_it = STATIC_SYMBOL("SOCKET-CLOSE-IT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_socket_close_it,
	    STATIC_FUNCTION(g2int_socket_close_it,NIL,FALSE,1,1));
    Qg2int_m_socket_close_it_weblink_socket_1 = 
	    STATIC_SYMBOL("M-SOCKET-CLOSE-IT-WEBLINK-SOCKET-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_socket_close_it_weblink_socket_1,
	    STATIC_FUNCTION(g2int_m_socket_close_it_weblink_socket_1,NIL,
	    FALSE,2,2));
    set_get(Qg2int_socket_close_it,Qg2int_weblink_socket,
	    Qg2int_m_socket_close_it_weblink_socket_1);
    if (G2int_lisp_process_cleanups == UNBOUND)
	G2int_lisp_process_cleanups = Nil;
}
